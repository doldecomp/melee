#include "grvenom.h"

#include <platform.h>

#include "gr/grcorneria.h"
#include "gr/grdisplay.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mplib.h"

#include <baselib/aobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

// Forward declaration of grVe_Data for use by multiple functions
// TODO: This struct should be defined in gr/types.h or a proper header
typedef struct grVe_Data {
    char x0[0x44];
    StageCallbacks callbacks[1]; // at offset 0x44
    char x58[0x1B8 - 0x58];
    char x1B8_file[0x1DC - 0x1B8]; // 0x1B8: "%s:%d..." string
    char x1DC_func[0x20];          // 0x1DC: function name or filename
} grVe_Data;

extern grVe_Data grVe_803E5348;

// @TODO: Currently 81.23% match - needs register allocation and control flow fixes
// TODO: Move these local structs to proper headers
typedef struct grVe_ExtData {
    char pad[0x20];
    void* x20[3];
    s32 x2C[3];
    s32 x38[3];
} grVe_ExtData;

#define VE_DATA ((grVe_ExtData*)&grVe_803E5348)

typedef struct grVe_TimingData {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
} grVe_TimingData;

extern u32 grVe_804D6A34;
extern grVe_TimingData* grVe_804D6A30;
extern s32 grVe_804D6A38;
extern s32 grVe_804D6A40;

typedef struct grVe_Lighting {
    char pad[0xE0];
    u8 xE0;
} grVe_Lighting;

typedef struct grVe_GroundData {
    char pad[0x2C];
    grVe_Lighting* x2C;
} grVe_GroundData;

void grVenom_8020362C(void)
{
    grVe_ExtData* data;
    s32 slot;
    s32 r28;
    s32* r29;
    s32* r30;
    s32 r0, r3, r4, r6;

    data = VE_DATA;

    if (grVe_804D6A40 == 0) {
        if ((u32)data->x20[0] == 0U) {
            grVe_804D6A38 -= 1;
            if (grVe_804D6A38 <= 0) {
                grVe_GroundData* gdata;
                u8 flags;

                gdata = (grVe_GroundData*)Ground_801C2BA4(7);
                flags = gdata->x2C->xE0;

                r3 = (flags >> 4U) & 1;
                r0 = (flags >> 3U) & 1;
                r6 = r3 | r0;
                r0 = (flags >> 2U) & 1;
                r4 = (flags >> 7U) & 1;
                r3 = (flags >> 6U) & 1;
                r6 = r6 | r0;
                r3 = r4 | r3;
                r0 = (flags >> 5U) & 1;
                r3 = r3 | r0;

                if (r6 != 0) {
                    r0 = 2;
                } else {
                    r0 = 0;
                }

                if (r3 != 0) {
                    r3 = 1;
                } else {
                    r3 = 0;
                }

                r0 = r3 | r0;

                if (r0 == 2) {
                    goto case_2;
                }
                if (r0 >= 2) {
                    return;
                }
                if (r0 == 0) {
                    goto case_0;
                }
                return;

            case_0:
                r30 = &data->x2C[0];
                r28 = data->x2C[0];
                goto loop_0_check;

            loop_0:
                r28 = HSD_Randi(0xB) + 1;
            loop_0_check:
                if (r28 == *r30) {
                    goto loop_0;
                }

                r29 = &data->x38[0];
                if (*r29 == 4) {
                    r4 = 1;
                } else {
                    grVe_TimingData* timing;
                    timing = grVe_804D6A30;
                    if (HSD_Randf() > timing->x10) {
                        r0 = 1;
                    } else {
                        r0 = 4;
                    }
                    r4 = r0;
                }

                grVe_804D6A34 = 0;
                *r30 = r28;
                *r29 = r4;
                data->x20[grVe_804D6A34] = (void*)grVenom_80203EAC(2);
                return;

            case_2:
                r29 = &data->x2C[0];
                r28 = data->x2C[0];
                goto loop_2_check;

            loop_2:
                r28 = HSD_Randi(4) + 1;
            loop_2_check:
                if (r28 == *r29) {
                    goto loop_2;
                }

                r30 = &data->x38[0];
                if (*r30 == 4) {
                    r4 = 1;
                } else {
                    grVe_TimingData* timing;
                    timing = grVe_804D6A30;
                    if (HSD_Randf() > timing->x10) {
                        r4 = 1;
                    } else {
                        r4 = 4;
                    }
                }

                grVe_804D6A34 = 0;
                *r29 = r28;
                *r30 = r4;
                data->x20[grVe_804D6A34] = (void*)grVenom_80203EAC(2);
                return;
            }
        } else {
            grVe_TimingData* timing;
            f32 f0, f2;

            timing = grVe_804D6A30;
            f0 = timing->x8;
            f2 = timing->xC;
            r3 = (s32)f0;
            r0 = (s32)f2;

            if (r0 > r3) {
                r4 = r0 - r3;
                if (r4 != 0) {
                    r4 = HSD_Randi(r4);
                } else {
                    r4 = 0;
                }
                r0 = r3 + r4;
            } else if (r0 < r3) {
                r4 = r3 - r0;
                if (r4 != 0) {
                    r4 = HSD_Randi(r4);
                } else {
                    r4 = 0;
                }
                r0 = r0 + r4;
            }

            grVe_804D6A38 = r0;
        }
    } else {
        r0 = 0;
        if ((u32)data->x20[0] != 0U) {
            r0 = 1;
            if ((u32)data->x20[1] != 0U) {
                r0 = 2;
                if ((u32)data->x20[2] != 0U) {
                    r0 = 3;
                }
            }
        }
        slot = r0;

        if (slot >= 3) {
            grVe_804D6A38 = 10;
        } else {
            grVe_804D6A38 -= 1;
            if (grVe_804D6A38 <= 0) {
                r4 = 0;
                r3 = (s32)&data->x2C[0];
                r6 = (s32)&data->x20[0];

                if (0 != slot) {
                    r0 = *(s32*)r3;
                    if (r0 < 8) {
                        if (r0 >= 1) {
                            if ((u32)*(s32*)r6 != 0U) {
                                r4 = 1;
                            }
                        }
                    }
                }

                r3 += 4;
                r6 += 4;

                if (1 != slot) {
                    r0 = *(s32*)r3;
                    if (r0 < 8) {
                        if (r0 >= 1) {
                            if ((u32)*(s32*)r6 != 0U) {
                                r4 = 1;
                            }
                        }
                    }
                }

                r3 += 4;
                r6 += 4;

                if (2 != slot) {
                    r0 = *(s32*)r3;
                    if (r0 < 8) {
                        if (r0 >= 1) {
                            if ((u32)*(s32*)r6 != 0U) {
                                r4 = 1;
                            }
                        }
                    }
                }

                if (r4 == 0) {
                    r28 = slot << 2;
                    r29 = (s32*)((u8*)data + 0x2C + r28);
                    r3 = *r29;
                    goto spawn_normal_check;

                spawn_normal:
                    r3 = HSD_Randi(0xB) + 1;
                spawn_normal_check:
                    if (r3 == data->x2C[0]) {
                        goto spawn_normal;
                    }
                    if (r3 == data->x2C[1]) {
                        goto spawn_normal;
                    }
                    if (r3 == data->x2C[2]) {
                        goto spawn_normal;
                    }

                    grVe_804D6A34 = slot;
                    r0 = slot + 1;
                    r6 = (s32)((u8*)data + 0x38 + r28);
                    *r29 = r3;
                    *(s32*)r6 = r0;
                    data->x20[grVe_804D6A34] = (void*)grVenom_80203EAC(2);
                } else {
                    grVe_GroundData* gdata;
                    u8 flags;

                    gdata = (grVe_GroundData*)Ground_801C2BA4(7);
                    flags = gdata->x2C->xE0;

                    r3 = (flags >> 4U) & 1;
                    r0 = (flags >> 3U) & 1;
                    r6 = r3 | r0;
                    r0 = (flags >> 2U) & 1;
                    r4 = (flags >> 7U) & 1;
                    r3 = (flags >> 6U) & 1;
                    r6 = r6 | r0;
                    r3 = r4 | r3;
                    r0 = (flags >> 5U) & 1;
                    r3 = r3 | r0;

                    if (r6 != 0) {
                        r0 = 2;
                    } else {
                        r0 = 0;
                    }

                    if (r3 != 0) {
                        r3 = 1;
                    } else {
                        r3 = 0;
                    }

                    if ((r3 | r0) == 0) {
                        r29 = (s32*)((u8*)data + 0x2C + (slot << 2));
                        r28 = (s32)((u8*)data + 0x38 + (slot << 2));
                        r3 = *r29;
                        goto spawn_restricted_check;

                    spawn_restricted:
                        r3 = HSD_Randi(4) + 8;
                    spawn_restricted_check:
                        if (r3 == data->x2C[0]) {
                            goto spawn_restricted;
                        }
                        if (r3 == data->x2C[1]) {
                            goto spawn_restricted;
                        }
                        if (r3 == data->x2C[2]) {
                            goto spawn_restricted;
                        }

                        grVe_804D6A34 = slot;
                        r0 = slot + 1;
                        *r29 = r3;
                        *(s32*)r28 = r0;
                        data->x20[grVe_804D6A34] = (void*)grVenom_80203EAC(2);
                    }
                }
            }
        }
    }
}

void grVenom_80203B14(bool arg) {}

// Decompilation of grVenom_80203B18
// @TODO: Currently 88.51% match - needs control flow/register allocation fix
// Stage initialization function for Venom

extern f32 grVe_804DB738;
extern f32 grVe_804DB73C;
extern f32 grVe_804DB740;
extern f32 grVe_804DB744;
extern f32 grVe_804DB748;
extern f32 grVe_804DB74C;
extern f32 grVe_804DB750;

void grVenom_80203B18(void)
{
    Vec3 sp1C;
    s32* data;
    Ground_GObj* obj;
    Ground_GObj* temp;
    Ground* gp;
    f32 f0;
    f32 f2;
    s32 i0;
    s32 i1;
    s32 flag;
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    data = (s32*) &grVe_803E5348;
    grVe_804D6A30 = Ground_801C49F8();
    grVenom_80203EAC(4);
    stage_info.unk8C.b4 = 0;
    flag = 1;
    stage_info.unk8C.b5 = flag;
    obj = (Ground_GObj*) grVenom_80203EAC(0);
    data[8] = 0;
    data[11] = 0;
    data[14] = 0;
    data[9] = 0;
    data[12] = 0;
    data[15] = 0;
    data[10] = 0;
    data[13] = 0;
    data[16] = 0;
    if (Stage_80225194() == 0xE9) {
        goto skip;
    }
    flag = 0;
skip:
    grVe_804D6A40 = flag;
    if (flag == 1) {
        grVe_804D6A38 = 0x78;
    } else {
        f0 = grVe_804D6A30->x0;
        f2 = grVe_804D6A30->x4;
        i0 = (s32) f0;
        i1 = (s32) f2;
        if (i1 > i0) {
            i1 = i1 - i0;
            if (i1 != 0) {
                i1 = HSD_Randi(i1);
            } else {
                i1 = 0;
            }
            i1 = i0 + i1;
        } else if (i1 < i0) {
            s32 diff = i0 - i1;
            if (diff != 0) {
                diff = HSD_Randi(diff);
            } else {
                diff = 0;
            }
            i1 = i1 + diff;
        }
        grVe_804D6A38 = i1;
    }
    temp = (Ground_GObj*) grVenom_80203EAC(5);
    gp = GET_GROUND(temp);
    gp->gv.venom.xC4 = (u32) obj;
    grVenom_80203EAC(9);
    temp = (Ground_GObj*) grVenom_80203EAC(7);
    grAnime_801C8138(temp, 7, 0);
    Ground_801C39C0();
    Ground_801C3BB4();
    sp1C.x = grVe_804DB738;
    sp1C.y = grVe_804DB73C;
    sp1C.z = grVe_804DB738;
    lb_80011A50(&sp1C, -1, grVe_804DB73C, grVe_804DB740, grVe_804DB744,
                grVe_804DB748, grVe_804DB74C, grVe_804DB740, grVe_804DB748);
    sp1C.x = grVe_804DB73C;
    sp1C.y = grVe_804DB73C;
    sp1C.z = grVe_804DB738;
    lb_80011A50(&sp1C, -1, grVe_804DB73C, grVe_804DB740, grVe_804DB744,
                grVe_804DB740, grVe_804DB74C, grVe_804DB750, grVe_804DB748);
    mpLib_80057BC0(3);
    mpLib_80057BC0(4);
    gobj = Ground_801C498C();
    if (gobj != NULL) {
        lobj = gobj->hsd_obj;
        if (lobj != NULL) {
            while (lobj != NULL) {
                if (lobj->aobj != NULL) {
                    HSD_AObjSetFlags(lobj->aobj, AOBJ_LOOP);
                }
                if (lobj->position != NULL) {
                    HSD_ForeachAnim(lobj->position, WOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                }
                if (lobj->interest != NULL) {
                    HSD_ForeachAnim(lobj->interest, WOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                }
                if (lobj == NULL) {
                    lobj = NULL;
                } else {
                    lobj = lobj->next;
                }
            }
        }
    }
}

void grVenom_80203DD0(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = HSD_GObj_Entities->xC;
    while (gobj != NULL) {
        if (HSD_GObjGetClassifier(gobj) == 0xC) {
            lobj = GET_LOBJ(gobj);
            while (lobj != NULL) {
                HSD_ForeachAnim(lobj, LOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                lobj = HSD_LObjGetNext(lobj);
            }
            return;
        }
        gobj = HSD_GObjGetNext(gobj);
    }
}

void grVenom_80203E80(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grVenom_80203EA4(void)
{
    return false;
}

// Decompilation of grVenom_80203EAC

Ground_GObj* grVenom_80203EAC(int gobj_id)
{
    Ground_GObj* gobj;
    Ground* gp;
    grVe_Data* base = &grVe_803E5348;
    StageCallbacks* callbacks = &((StageCallbacks*)((char*)base + 0x44))[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        gp = gobj->user_data;
        gp->x8_callback = NULL;
        gp->xC_callback = NULL;
        GObj_SetupGXLink(gobj, grDisplay_801C5DB0, 3, 0);
        if (callbacks->callback3 != NULL) {
            gp->x1C_callback = callbacks->callback3;
        }
        if (callbacks->callback0 != NULL) {
            callbacks->callback0(gobj);
        }
        if (callbacks->callback2 != NULL) {
            HSD_GObjProc_8038FD54(gobj, callbacks->callback2, 4);
        }
    } else {
        OSReport(&base->x1B8_file[0], &base->x1DC_func[0], 0x23B, gobj_id);
    }

    return gobj;
}

void grVenom_80203F98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grVenom_80203FC4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80203FCC(Ground_GObj* arg) {}

void grVenom_80203FD0(Ground_GObj* arg) {}

// Decompilation of grVenom_80203FD4

#include "gr/grvenom.h"
#include "gr/inlines.h"
#include "gr/ground.h"
#include "gr/granime.h"

void grVenom_80203FD4(Ground_GObj* gobj)
{
    HSD_JObj* jobj1;
    HSD_JObj* jobj4;
    HSD_JObj* jobj3;
    HSD_JObj* jobj2;
    HSD_JObj* jobj5;
    HSD_JObj* jobj6;
    Ground* gp = gobj->user_data;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
    jobj6 = Ground_801C3FA4(gobj, 6);
    jobj5 = Ground_801C3FA4(gobj, 5);
    jobj2 = Ground_801C3FA4(gobj, 2);
    jobj3 = Ground_801C3FA4(gobj, 3);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj1 = Ground_801C3FA4(gobj, 1);
    Ground_801C4E70(jobj1, jobj4, jobj3, jobj2, jobj5, jobj6);
    gp = gobj->user_data;
    gp->x10_flags.b2 = 0;
}

bool grVenom_802040A4(Ground_GObj* arg)
{
    return false;
}

void grVenom_802040AC(Ground_GObj* arg) {}

void grVenom_802040B0(Ground_GObj* arg) {}

enum_t Stage_80225194(void);

void fn_802040B4(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    if (Stage_80225194() == 0xE4) {
        gp->gv.venom.xC8 = 1;
    }
}

// Decompilation of grVenom_802040F0

void grVenom_802040F0(Ground_GObj* gobj)
{
    Vec3 pos1;
    Vec3 pos2;
    HSD_JObj* temp;
    Ground* new_var;
    Ground* gp = GET_GROUND(gobj);

    Ground_801C2ED0(gobj->hsd_obj, gp->map_id);
    grAnime_801C7FF8(gobj, 0, 7, 0, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 0, 7, 1, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xB, 7, 2, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xD, 7, 2, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 0xF, 7, 2, 0.0F, 1.0F);
    new_var = gp;
    grAnime_801C7FF8(gobj, 4, 7, 3, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 7, 7, 3, 0.0F, 1.0F);
    Ground_801C10B8(gobj, (HSD_GObjEvent) fn_802040B4);
    gp->gv.venom.xC8 = -1;
    gp->gv.venom.xCC = (u32) Ground_801C3FA4(gobj, 2);
    gp->gv.venom.xD0 = (u32) Ground_801C3FA4(gobj, 3);
    lb_8000B1CC((HSD_JObj*) gp->gv.venom.xCC, NULL, &pos1);
    lb_8000B1CC((HSD_JObj*) gp->gv.venom.xD0, NULL, &pos2);
    if (pos2.y > pos1.y) {
        temp = (HSD_JObj*) gp->gv.venom.xCC;
        gp->gv.venom.xCC = new_var->gv.venom.xD0;
        gp->gv.venom.xD0 = (u32) temp;
    }
    gp->x10_flags.b5 = 1;
}

bool grVenom_8020427C(Ground_GObj* arg)
{
    return false;
}

// Decompilation of grVenom_80204284
// @TODO: Currently 97.29% match - needs minor register allocation fix
void grVenom_80204284(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* src_jobj;
    HSD_JObj* dst_jobj;
    Ground_GObj* other_gobj;
    Vec3 pos;
    s32 timer;

    gp = GET_GROUND(gobj);
    src_jobj = GET_JOBJ(gobj);
    dst_jobj = (HSD_JObj*) ((HSD_GObj*) gp->gv.venom.xC4)->hsd_obj;

    HSD_JObjGetTranslation(src_jobj, &pos);
    HSD_JObjSetTranslate(dst_jobj, &pos);

    Ground_801C39C0();
    Ground_801C3BB4();

    timer = gp->gv.venom.xC8;
    if (timer > 0) {
        gp->gv.venom.xC8 = timer + 1;
        if ((s32) gp->gv.venom.xC8 >= 0x3C) {
            if ((s32) gp->gv.venom.xC8 == 0x3C) {
                ifStatus_802F6898();
                un_802FF570();
                other_gobj = (Ground_GObj*) grVenom_80203EAC(1);
                if (other_gobj != NULL) {
                    Ground* other_gp = GET_GROUND(other_gobj);
                    grCorneria_801E25C4(&other_gp->gv.venom.xC4, 4, 6, 0x6B6CC);
                }
            } else {
                ifStatus_802F6898();
                un_802FF570();
                if (Ground_801C2BA4(1) == NULL) {
                    ifStatus_802F68F0();
                    un_802FF620();
                    gp->gv.venom.xC8 = -1;
                }
            }
        }
    }

    lb_800115F4();
    grVenom_8020362C();
    Ground_801C2FE0(gobj);
}

void grVenom_80204424(Ground_GObj* arg) {}

// Decompilation of grVenom_80204428
// FAKE MATCH: grVenom_GroundVars has wrong types for this function

#include <platform.h>
#include "gr/ground.h"
#include "gr/inlines.h"
#include "mp/mplib.h"

void grVenom_80204428(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);

    gp->gv.venom.xC4 = (u32)Ground_801C3FA4(gobj, 4);
    gp->gv.venom.xC8 = (u32)Ground_801C3FA4(gobj, 0xE);
    gp->gv.venom.xCC = (u32)Ground_801C3FA4(gobj, 0x10);
    gp->gv.venom.xD0 = (u32)Ground_801C3FA4(gobj, 0x11);
    *(u32*)&gp->gv.venom.xD4 = (u32)Ground_801C3FA4(gobj, 0x12);
    *(u32*)&gp->gv.venom.xD8 = (u32)Ground_801C3FA4(gobj, 0x13);
    *(u32*)&gp->gv.venom.xDC = (u32)Ground_801C3FA4(gobj, 0x15);

    // Access bitfields using mutecity2 which has 8 bitfields at xC4_flags
    // xC4_flags is at offset 0, we need offset 0x1C, so shift by 7 u32s
    gp->gv.mutecity2.xC4_flags.b0 = 0;
    gp->gv.mutecity2.xC4_flags.b1 = 0;
    gp->gv.mutecity2.xC4_flags.b2 = 0;
    gp->gv.mutecity2.xC4_flags.b3 = 0;
    gp->gv.mutecity2.xC4_flags.b4 = 0;
    gp->gv.mutecity2.xC4_flags.b5 = 0;
    gp->gv.mutecity2.xC4_flags.b6 = 0;

    gp->gv.venom.xE4 = 0.0F;

    Ground_801C5440(gp, 0, 0x6B6C3);
    mpLib_80057BC0(2);
}

bool grVenom_80204544(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_8020454C

void grVenom_80204B84(Ground_GObj* arg) {}

// Decompilation of grVenom_80204B88
// Updates Venom stage lighting colors based on environment state.

extern GXColor grVe_804DB7D8;
extern GXColor grVe_804DB7DC;
extern GXColor grVe_804DB7E0;
extern GXColor grVe_804DB7E4;

// TODO: grVenom_GroundVars in types.h has xE0 as f32, but this function
// treats it as a bitfield. The struct needs to be updated.
typedef struct GroundVenom_ForLighting {
    char pad[0xE0];
    struct {
        u16 padding1 : 7;
        u16 state : 2;
        u16 padding2 : 7;
    } xE0;
} GroundVenom_ForLighting;

void grVenom_80204B88(Ground_GObj* gobj)
{
    GroundVenom_ForLighting* gp = (GroundVenom_ForLighting*) GET_GROUND(gobj);
    u8 env_flags;
    GXColor color_set1;
    GXColor color_set2;
    GXColor color_neutral1;
    GXColor color_neutral2;

    env_flags = *(u8*) &gp->xE0;

    if ((env_flags >> 5) & 1) {
        if (gp->xE0.state != 1) {
            color_set1 = grVe_804DB7D8;
            Ground_801C052C(&color_set1);
            Ground_801C05D4(&color_set1);
            Ground_801C0544(&color_set1);
            Ground_801C058C(&color_set1);
            Ground_801C05EC(&color_set1);
            Ground_801C05A4(&color_set1);
            Ground_801C055C(&color_set1);
            Ground_801C05BC(&color_set1);
            Ground_801C0574(&color_set1);
            gp->xE0.state = 1;
        }
    } else if ((env_flags >> 1) & 1) {
        if (gp->xE0.state != 2) {
            color_set2 = grVe_804DB7DC;
            Ground_801C05BC(&color_set2);
            gp->xE0.state = 2;
        }
    } else {
        if (gp->xE0.state != 0) {
            color_neutral1 = grVe_804DB7E0;
            color_neutral2 = grVe_804DB7E4;
            Ground_801C052C(&color_neutral1);
            Ground_801C05D4(&color_neutral1);
            Ground_801C0544(&color_neutral1);
            Ground_801C058C(&color_neutral1);
            Ground_801C05EC(&color_neutral1);
            Ground_801C05A4(&color_neutral1);
            Ground_801C055C(&color_neutral2);
            Ground_801C05BC(&color_neutral2);
            Ground_801C0574(&color_neutral2);
            gp->xE0.state = 0;
        }
    }
}

void grVenom_80204CE0(Ground_GObj* arg) {}

bool grVenom_80204CE4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80204CEC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 temp;
    PAD_STACK(8);

    ifStatus_802F6898();
    un_802FF570();

    if (Ground_801C2BA4(1) == NULL) {
        if (grCorneria_801E2598(gp->gv.venom.xC4, gp->gv.venom.xC8) != 0) {
            temp = gp->gv.venom.xCC;
            gp->gv.venom.xCC = temp - 1;
            if (temp < 0) {
                HSD_GObj* other = (HSD_GObj*) grVenom_80203EAC(1);
                Ground* other_gp = other->user_data;
                grCorneria_801E2738(other, &other_gp->gv.venom.xC4, gp->gv.venom.xC4, gp->gv.venom.xC8);
                gp->gv.venom.xC8 = gp->gv.venom.xC8 + 1;
                gp->gv.venom.xCC = 0;
            }
        } else {
            temp = gp->gv.venom.xCC;
            gp->gv.venom.xCC = temp - 1;
            if (temp < 0) {
                Ground_801C4A08(gobj);
            }
        }
    }
}

void grVenom_80204DB0(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

// Decompilation of grVenom_80204DD4
// Unit: main/melee/gr/grvenom
// Manual expansion of HSD_JObjSetScaleX/Y without using inline functions

void grVenom_80204DD4(Ground_GObj* gobj)
{
    int new_var;
    int new_var3;
    HSD_JObj* new_var2;
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;

    Ground_801C2ED0(jobj, gp->map_id);

    // HSD_JObjSetScaleX(jobj, 1.0F) expanded:
    ((jobj) ? ((void) 0) : __assert("jobj.h", 0x308, "jobj"));
    jobj->scale.x = 1.0F;
    new_var3 = !(jobj->flags & (1 << 25));
    if (new_var3) {
        if (jobj != 0L && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }

    new_var = 1 << 25;
    // HSD_JObjSetScaleY(jobj, 1.0F) expanded:
    ((jobj) ? ((void) 0) : __assert("jobj.h", 0x317, "jobj"));
    jobj->scale.y = 1.0F;
    new_var2 = jobj;
    if (!(new_var2->flags & new_var)) {
        if (new_var2 != 0L && !HSD_JObjMtxIsDirty(new_var2)) {
            HSD_JObjSetMtxDirtySub(new_var2);
        }
    }
}

bool grVenom_80204EF4(Ground_GObj* arg)
{
    return false;
}

bool grVenom_80204EFC(Ground_GObj* arg)
{
    return Ground_801C2FE0(arg);
}

void grVenom_80204F1C(Ground_GObj* arg) {}

/// #grVenom_80204F20

bool grVenom_802052D8(Ground_GObj* arg)
{
    return false;
}

// Decompilation of grVenom_802052E0
// TODO: VenomSpawnData struct should be defined in gr/types.h or grvenom.h
typedef struct {
    u8 pad[0x218];
    f32 x;
    f32 y;
    f32 z;
} VenomSpawnData;

void grVenom_802052E0(Ground_GObj* gobj, Vec3* pos)
{
    s32* spawn_table = (s32*)&grVe_803E5348;
    Ground* gp;
    HSD_JObj* jobj;
    Vec3 jobj_pos;
    s32* new_var;
    s32* new_var4;
    u8* new_var2;
    u32 spawn_idx;
    struct grVenom_GroundVars* new_var3;
    s32 data_idx;
    VenomSpawnData* spawn_data;

    if (gobj != NULL) {
        gp = gobj->user_data;
        Ground_801C2BA4(5);
        jobj = Ground_801C3FA4(gobj, 5);
        lb_8000B1CC(jobj, NULL, &jobj_pos);
        new_var = spawn_table;
        new_var4 = spawn_table;
        new_var2 = (u8*)new_var4;
        new_var3 = &gp->gv.venom;
        spawn_idx = (*new_var3).xC8;
        data_idx = new_var[spawn_idx + 11];
        spawn_data = (VenomSpawnData*)(new_var2 + data_idx * 12);
        pos->x = jobj_pos.x + spawn_data->x;
        pos->y = jobj_pos.y + spawn_data->y;
        pos->z = jobj_pos.z + spawn_data->z;
    } else {
        pos->z = 0.0F;
        pos->y = 0.0F;
        pos->x = 0.0F;
    }
}

// Decompilation of grVenom_802053B0
// @TODO: Currently 92.15% match - needs register allocation fix
// Needs: grVe_804DB740 extern float

extern f32 grVe_804DB740;

void grVenom_802053B0(Ground_GObj* gobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    s32* ptr;
    Ground* gp2;
    s32 state;
    HSD_JObj* jobj;
    s32* base;
    Ground* gp;

    gp = gobj->user_data;
    base = (s32*) &grVe_803E5348;
    jobj = gobj->hsd_obj;
    ptr = base + gp->gv.venom.xC8;

    if ((u32) ptr[8] == (u32) gobj) {
        if (*(s32*) &gp->gv.venom.xD4 == 1) {
            *(s32*) &gp->gv.venom.xD4 = 0;
            grAnime_801C8138(gobj, gp->map_id,
                             *(s32*) ((char*) base +
                                      base[gp->gv.venom.xC8 + 11] * 4 +
                                      0x1E8));
            return;
        }

        state = ptr[11];
        if (state < 8) {
            if (state >= 1) {
                grVenom_802052E0(gobj, &sp28);
                state = *(s32*) &gp->gv.venom.xD8;
                switch (state) {
                case 0:
                    if (grVenom_80205DF8(&sp28) == 0) {
                        lbAudioAx_800237A8(0x6B6C0, 0x7F, 0x40);
                        *(s32*) &gp->gv.venom.xD8 = 1;
                    }
                    break;
                case 1:
                    if (grVenom_80205E84((Vec2*) &sp28) == 0) {
                        *(s32*) &gp->gv.venom.xD8 = 2;
                    }
                    break;
                case 2:
                    if (grVenom_80205E84((Vec2*) &sp28) == 1) {
                        lbAudioAx_800237A8(0x6B6C2, 0x7F, 0x40);
                        *(s32*) &gp->gv.venom.xD8 = 3;
                    }
                    break;
                }
            }
        } else if (state < 12) {
            ((jobj) ? ((void) 0) : __assert("jobj.h", 0x294, "jobj"));
            if (jobj->flags & 0x20000) {
                __assert("jobj.h", 0x295, (char*) base + 0x2D4);
            }
            jobj->rotate.z = grVe_804DB740;
            if (!(jobj->flags & (1 << 25))) {
                HSD_JObjSetMtxDirty(jobj);
            }
            gp2 = gobj->user_data;
            grVenom_802052E0(gobj, &sp1C);
            state = *(s32*) &gp2->gv.venom.xD8;
            switch (state) {
            case 0:
                if (grVenom_80205DF8(&sp1C) == 0) {
                    lbAudioAx_800237A8(0x6B6C0, 0x7F, 0x40);
                    *(s32*) &gp2->gv.venom.xD8 = 1;
                }
                break;
            case 1:
                if (grVenom_80205E84((Vec2*) &sp1C) == 0) {
                    *(s32*) &gp2->gv.venom.xD8 = 2;
                }
                break;
            case 2:
                if (grVenom_80205E84((Vec2*) &sp1C) == 1) {
                    lbAudioAx_800237A8(0x6B6C2, 0x7F, 0x40);
                    *(s32*) &gp2->gv.venom.xD8 = 3;
                }
                break;
            }
        }

        if (grAnime_801C83D0(gobj, 0, 7) != 0) {
            *(s32*) ((char*) base + gp->gv.venom.xC8 * 4 + 0x20) = 0;
            Ground_801C4A08(gobj);
        }
    } else {
        Ground_801C4A08(gobj);
    }
}

void grVenom_802056AC(Ground_GObj* arg) {}

// Decompilation of grVenom_802056B0

extern int grVe_803E5380[];
extern int grVe_803E5680[];
extern u32 grVe_804D6A34;

void grVenom_802056B0(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* jobj = gobj->hsd_obj;
    int* joint_idx;
    int joint_offset;
    int* joints;
    int joint_id;

    Ground_801C2ED0(jobj, gp->map_id);
    gp->gv.venom.xC8 = grVe_804D6A34;
    joint_idx = grVe_803E5380;
    joints = grVe_803E5680;
    gp->gv.venom.xD0 = 0;
    gp->gv.venom.xDC = 0.0F;
    gp->gv.venom.xE8 = 0.0F;
    gp->gv.venom.xE4 = 0.0F;
    gp->gv.venom.xE0 = 0.0F;
    joint_offset = joint_idx[gp->gv.venom.xC8];
    joint_id = joints[joint_offset];
    mpJointListAdd(joint_id);

    Ground_801C2ED0(jobj, gp->map_id);
}

bool grVenom_80205750(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80205758

void grVenom_80205AD0(Ground_GObj* arg) {}

// Decompilation of grVenom_80205AD4
// @TODO: Currently 92.66% match - needs minor code ordering fix
void grVenom_80205AD4(Ground_GObj* gobj)
{
    u8* base;
    HSD_JObj* jobj;
    Ground* gp;
    s32 zero;
    f32 scale;
    u8* data;
    s32 type;
    Ground_GObj* other;
    Ground* other_gp;
    HSD_JObj* jobj2;
    f32 scl;
    void* attr;

    base = (u8*)&grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    scale = Ground_801C0498();

    gp->gv.venom.xC8 = grVe_804D6A34;
    zero = 0;
    *(s32*)&gp->gv.venom.xEC = zero;
    *(s32*)&gp->gv.venom.xE8 = zero;
    *(s32*)&gp->gv.venom.xE4 = zero;
    *(s32*)&gp->gv.venom.xE0 = zero;

    grAnime_801C7FF8(gobj, 7, 7, 0, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 8, 7, 0, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);

    data = base + gp->gv.venom.xC8 * 4;
    type = *(s32*)(data + 0x2C);

    if (type < 8) {
        if (type < 1) {
            *(s32*)&gp->gv.venom.xE0 = -1;
            *(s32*)&gp->gv.venom.xE4 = -1;
        } else {
            s32 idx = *(s32*)(data + 0x38);
            u8* data2 = base + idx * 4;
            other = (Ground_GObj*)grVenom_80203EAC(*(s32*)(data2 + 0x324));
            *(s32*)&gp->gv.venom.xDC = (s32)other;
            if (other != NULL) {
                other_gp = other->user_data;
                if (other_gp != NULL) {
                    other_gp->gv.venom.xC8 = gp->gv.venom.xC8;
                }
            }
        }
    } else {
        if (type < 0xC) {
            jobj2 = Ground_801C3FA4((HSD_GObj*)*(s32*)(data + 0x20), 5);
            lb_8000C2F8(jobj2, Ground_801C3FA4(gobj, 0));
            *(s32*)&gp->gv.venom.xDC = zero;
        } else {
            *(s32*)&gp->gv.venom.xE0 = -1;
            *(s32*)&gp->gv.venom.xE4 = -1;
        }
    }

    attr = grVe_804D6A30;
    scl = scale * *(f32*)((u8*)attr + 0x34);
    HSD_JObjSetScaleX(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*)((u8*)attr + 0x34);
    HSD_JObjSetScaleY(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*)((u8*)attr + 0x34);
    HSD_JObjSetScaleZ(jobj, scl);

    gp->gv.venom.xC4 &= ~0x80;
    gp->gv.venom.xD4 = zero;
    *(s32*)((u8*)gp + 0xF0) = zero;
    *(s32*)((u8*)gp + 0xF4) = zero;

    attr = grVe_804D6A30;
    *(s32*)((u8*)gp + 0xF8) = (s32)*(f32*)((u8*)attr + 0x2C);
    *(s32*)((u8*)gp + 0xFC) = zero;
    *(s32*)((u8*)gp + 0x100) = HSD_Randi(2);
}

bool grVenom_80205DF0(Ground_GObj* arg)
{
    return false;
}

s32 grVenom_80205DF8(Vec3* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return 1;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}

// Decompilation of grVenom_80205E84

float Stage_GetBlastZoneBottomOffset(void);
float Stage_GetBlastZoneLeftOffset(void);
float Stage_GetBlastZoneRightOffset(void);
float Stage_GetBlastZoneTopOffset(void);

s32 grVenom_80205E84(Vec2* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset() - 20.0F) {
        return 1;
    }
    if (pos->x < 20.0F + Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset() - 20.0F) {
        return 1;
    }
    if (pos->y < 20.0F + Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}

/// #grVenom_80205F30

void grVenom_80206870(Ground_GObj* arg) {}

#if 0
// Decompilation of grVenom_80206874
// @TODO: Currently 32.92% match - below 50% threshold, needs significant work
void grVenom_80206874(Ground_GObj* gobj)
{
    u8* base;
    Ground* gp;
    HSD_JObj* jobj;
    s32 zero;
    f32 scale_factor;
    u8* entry;
    f32 scaled;
    s32 case_val;
    Ground_GObj* child_gobj;
    Ground* child_gp;
    HSD_JObj* jobj2;
    s32 idx;
    u8* ptr;

    base = (u8*)&grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    scale_factor = Ground_801C0498();

    gp->gv.venom.xC8 = grVe_804D6A34;
    zero = 0;
    gp->gv.venom.xEC = 0;
    gp->gv.venom.xE8 = 0;
    gp->gv.venom.xE4 = 0;
    gp->gv.venom.xE0 = 0;

    grAnime_801C7FF8(gobj, 0, 7, 1, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);

    entry = base + gp->gv.venom.xC8 * 4;
    case_val = *(s32*)(entry + 0x2C);

    if (case_val < 8) {
        if (case_val >= 1) {
            idx = *(s32*)(entry + 0x38);
            ptr = base + idx * 4;
            child_gobj = (Ground_GObj*)grVenom_80203EAC(*(s32*)(ptr + 0x324));
            *(s32*)&gp->gv.venom.xDC = (s32)child_gobj;
            if (child_gobj != NULL) {
                child_gp = child_gobj->user_data;
                if (child_gp != NULL) {
                    child_gp->gv.venom.xC8 = gp->gv.venom.xC8;
                }
            }
        } else {
            *(s32*)&gp->gv.venom.xE0 = -1;
            *(s32*)&gp->gv.venom.xE4 = -1;
        }
    } else if (case_val < 0xC) {
        jobj2 = Ground_801C3FA4((HSD_GObj*)*(s32*)(entry + 0x20), 5);
        lb_8000C2F8(Ground_801C3FA4(gobj, 0), jobj2);
        *(s32*)&gp->gv.venom.xDC = zero;
    } else {
        *(s32*)&gp->gv.venom.xE0 = -1;
        *(s32*)&gp->gv.venom.xE4 = -1;
    }

    // TODO: Need grVe_804D6A30 struct with cam_zoom_rate at 0x34
    // scaled = scale_factor * grVe_804D6A30->cam_zoom_rate;
    // HSD_JObjSetScaleX/Y/Z(jobj, scaled);
}
#endif

/// #grVenom_80206874

bool grVenom_80206B68(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206B70(Ground_GObj* arg)
{
    grVenom_80205F30(arg);
}

void grVenom_80206B90(Ground_GObj* arg) {}

void grVenom_80206B94(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    smashTaunt_801E2550(gobj, &gp->gv.smashtaunt);
}

bool grVenom_80206BBC(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206BC4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gp->gv.corneria);
}

void grVenom_80206BEC(Ground_GObj* arg) {}

bool grVenom_80206BF0(int arg0)
{
    s32 var_r30;
    Ground_GObj* wgobj;
    Ground* gp;
    PAD_STACK(32);

    if (Ground_801C2BA4(8) != NULL) {
        return 0;
    }
    if (arg0 == 2) {
        var_r30 = HSD_Randi(5) + 8;
    } else if (arg0 == 20) {
        var_r30 = HSD_Randi(5) + 13;
    } else {
        return 0;
    }
    wgobj = (Ground_GObj*)grVenom_80203EAC(8);
    if (wgobj == NULL) {
        __assert("grvenom.c", 0x8C4, "wgobj");
    }
    gp = wgobj->user_data;
    gp->gv.venom.xCC = 10;
    gp->gv.venom.xC8 = 0;
    gp->gv.venom.xC4 = var_r30;
    return 1;
}

// Decompilation of grVenom_80206CB0

void grVenom_80206CB0(s32 arg0)
{
    HSD_GObj* gobj;

    gobj = Ground_801C2BA4(8);
    if (gobj != NULL) {
        if (arg0 != 0) {
            Ground_801C4A08(gobj);
        }
        gobj = Ground_801C2BA4(1);
        if (gobj != NULL) {
            Ground_801C4A08(gobj);
        }
        HSD_SisLib_803A5F50(1);
    }
}

// Decompilation of grVenom_80206D10
// Unit: main/melee/gr/grvenom

int mpJointFromLine(int line_id);

s32 grVenom_80206D10(s32 arg0)
{
    s32 in_range;
    s32 result;
    u32 diff;

    if (stage_info.internal_stage_id == VENOM && arg0 != -1) {
        result = mpJointFromLine(arg0);
        diff = result - 3;
        in_range = 1;
        if (diff > 1U) {
            in_range = 0;
        }
        if (in_range != 0) {
            return 1;
        }
    }
    return 0;
}

DynamicsDesc* grVenom_80206D74(enum_t arg)
{
    return false;
}

// Decompilation of grVenom_80206D7C
// Unit: main/melee/gr/grvenom

// arg0 appears to be some struct with a float at offset 0x4
// arg1 is unused
// arg2 is an HSD_JObj* that gets passed to lb_8000B1CC

bool grVenom_80206D7C(void* arg0, s32 arg1, HSD_JObj* arg2)
{
    Vec3 sp20;
    Vec3 sp14;
    HSD_GObj* gobj;
    Ground* gp;

    lb_8000B1CC(arg2, NULL, &sp20);
    gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL && (HSD_JObj*)gp->gv.venom.xD0 == arg2) {
            lb_8000B1CC((HSD_JObj*)gp->gv.venom.xCC, NULL, &sp14);
            if (*(f32*)((u8*)arg0 + 0x4) > sp14.y) {
                return 0;
            }
        }
    }
    if (*(f32*)((u8*)arg0 + 0x4) > sp20.y) {
        return 1;
    }
    return 0;
}
