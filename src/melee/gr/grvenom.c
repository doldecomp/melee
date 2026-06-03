#include "grvenom.h"

#include <platform.h>

#include "gr/grcorneria.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/stage.h"
#include "if/ifcoget.h"
#include "if/ifstatus.h"
#include "it/items/itarwinglaser.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <baselib/aobj.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>
#include <baselib/sislib.h>

/// Forward declaration of grVe_Data for use by multiple functions
/// @todo This struct should be defined in gr/types.h or a proper header
typedef struct grVe_Data {
    char x0[0x44];
    StageCallbacks callbacks[1]; // at offset 0x44
    char x58[0x1B8 - 0x58];
    char x1B8_file[0x1DC - 0x1B8]; // 0x1B8: "%s:%d..." string
    char x1DC_func[0x20];          // 0x1DC: function name or filename
} grVe_Data;

extern grVe_Data grVe_803E5348;

/// @todo Move these local structs to proper headers
typedef struct grVe_ExtData {
    char pad[0x20];
    void* x20[3];
    s32 x2C[3];
    s32 x38[3];
} grVe_ExtData;

#define VE_DATA ((grVe_ExtData*) &grVe_803E5348)

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

/// grVenom_8020362C

void grVenom_8020362C(void)
{
    grVe_ExtData* ext = VE_DATA;
    s32 i;
    s32 idx;
    s32 spawn;
    u32 ground_flags;
    s32 group_a;
    s32 group_b;
    s32 combined;
    s32 mode;
    s32 lo;
    s32 hi;
    s32 diff;
    s32 sub;
    s32 has_active;

    if (grVe_804D6A40 == 0) {
        if (ext->x20[0] == NULL) {
            grVe_804D6A38 = grVe_804D6A38 - 1;
            if (grVe_804D6A38 <= 0) {
                ground_flags =
                    ((grVe_Lighting*) Ground_801C2BA4(7)->user_data)->xE0;
                {
                    s32 b4 = (ground_flags >> 4) & 1;
                    s32 b3 = (ground_flags >> 3) & 1;
                    s32 b7 = (ground_flags >> 7) & 1;
                    s32 b6 = (ground_flags >> 6) & 1;
                    s32 b2;
                    s32 b5;
                    s32 ab;
                    ab = b4 | b3;
                    b2 = (ground_flags >> 2) & 1;
                    group_b = b7 | b6;
                    if ((ab | b2) != 0) {
                        group_a = 2;
                    } else {
                        group_a = 0;
                    }
                    b5 = (ground_flags >> 5) & 1;
                    if ((group_b | b5) != 0) {
                        group_b = 1;
                    } else {
                        group_b = 0;
                    }
                }
                combined = group_b | group_a;
                if (combined == 2) {
                    idx = ext->x2C[0];
                    do {
                        if (idx == ext->x2C[0]) {
                            idx = HSD_Randi(4) + 1;
                        }
                    } while (idx == ext->x2C[0]);
                    if (ext->x38[0] == 4) {
                        mode = 1;
                    } else {
                        mode = (HSD_Randf() > grVe_804D6A30->x10) ? 1 : 4;
                    }
                    grVe_804D6A34 = 0;
                    ext->x2C[0] = idx;
                    ext->x38[0] = mode;
                    ext->x20[grVe_804D6A34] = grVenom_80203EAC(2);
                } else if (combined < 2) {
                    if (combined == 0) {
                        idx = ext->x2C[0];
                        do {
                            if (idx == ext->x2C[0]) {
                                idx = HSD_Randi(0xB) + 1;
                            }
                        } while (idx == ext->x2C[0]);
                        if (ext->x38[0] == 4) {
                            mode = 1;
                        } else {
                            mode = (HSD_Randf() > grVe_804D6A30->x10) ? 1 : 4;
                        }
                        grVe_804D6A34 = 0;
                        ext->x2C[0] = idx;
                        ext->x38[0] = mode;
                        ext->x20[grVe_804D6A34] = grVenom_80203EAC(2);
                    }
                }
            }
        } else {
            lo = (s32) grVe_804D6A30->x8;
            hi = (s32) grVe_804D6A30->xC;
            spawn = hi;
            if (hi > lo) {
                diff = hi - lo;
                spawn = (diff != 0) ? HSD_Randi(diff) : 0;
                spawn = lo + spawn;
            } else if (hi < lo) {
                sub = lo - hi;
                spawn = (sub != 0) ? HSD_Randi(sub) : 0;
                spawn = hi + spawn;
            }
            grVe_804D6A38 = spawn;
        }
    } else {
        i = 0;
        if (ext->x20[0] != NULL) {
            i = 1;
            if (ext->x20[1] != NULL) {
                i = 2;
                if (ext->x20[2] != NULL) {
                    i = 3;
                }
            }
        }
        if (i < 3) {
            grVe_804D6A38 = grVe_804D6A38 - 1;
            if (grVe_804D6A38 <= 0) {
                has_active = 0;
                if (i != 0 && ext->x2C[0] < 8) {
                    if (ext->x2C[0] >= 1) {
                        if (ext->x20[0] != NULL) {
                            has_active = 1;
                        }
                    }
                }
                if (i != 1 && ext->x2C[1] < 8) {
                    if (ext->x2C[1] >= 1) {
                        if (ext->x20[1] != NULL) {
                            has_active = 1;
                        }
                    }
                }
                if (i != 2 && ext->x2C[2] < 8) {
                    if (ext->x2C[2] >= 1) {
                        if (ext->x20[2] != NULL) {
                            has_active = 1;
                        }
                    }
                }
                if (has_active == 0) {
                    idx = ext->x2C[i];
                    do {
                        if (idx == ext->x2C[0]) {
                            idx = HSD_Randi(0xB) + 1;
                            continue;
                        }
                        if (idx == ext->x2C[1]) {
                            idx = HSD_Randi(0xB) + 1;
                            continue;
                        }
                        if (idx == ext->x2C[2]) {
                            idx = HSD_Randi(0xB) + 1;
                            continue;
                        }
                        break;
                    } while (1);
                    grVe_804D6A34 = i;
                    ext->x2C[i] = idx;
                    ext->x38[i] = i + 1;
                    ext->x20[grVe_804D6A34] = grVenom_80203EAC(2);
                } else {
                    ground_flags =
                        ((grVe_Lighting*) Ground_801C2BA4(7)->user_data)->xE0;
                    {
                        s32 b4 = (ground_flags >> 4) & 1;
                        s32 b3 = (ground_flags >> 3) & 1;
                        s32 b7 = (ground_flags >> 7) & 1;
                        s32 b6 = (ground_flags >> 6) & 1;
                        s32 b2;
                        s32 b5;
                        s32 ab;
                        ab = b4 | b3;
                        b2 = (ground_flags >> 2) & 1;
                        group_b = b7 | b6;
                        if ((ab | b2) != 0) {
                            group_a = 2;
                        } else {
                            group_a = 0;
                        }
                        b5 = (ground_flags >> 5) & 1;
                        if ((group_b | b5) != 0) {
                            group_b = 1;
                        } else {
                            group_b = 0;
                        }
                    }
                    if ((group_b | group_a) == 0) {
                        idx = ext->x2C[i];
                        do {
                            if (idx == ext->x2C[0]) {
                                idx = HSD_Randi(4) + 8;
                                continue;
                            }
                            if (idx == ext->x2C[1]) {
                                idx = HSD_Randi(4) + 8;
                                continue;
                            }
                            if (idx == ext->x2C[2]) {
                                idx = HSD_Randi(4) + 8;
                                continue;
                            }
                            break;
                        } while (1);
                        grVe_804D6A34 = i;
                        ext->x2C[i] = idx;
                        ext->x38[i] = i + 1;
                        ext->x20[grVe_804D6A34] = grVenom_80203EAC(2);
                    }
                }
            }
        } else {
            grVe_804D6A38 = 0xA;
        }
    }
}

void grVenom_80203B14(bool arg) {}

/// grVenom_80203B18
/// @todo Currently 88.51% match - needs control flow/register allocation fix
/// Stage initialization function for Venom

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
    grZakoGenerator_801CAE04(NULL);
}

bool grVenom_80203EA4(void)
{
    return false;
}

/// grVenom_80203EAC

Ground_GObj* grVenom_80203EAC(int gobj_id)
{
    Ground_GObj* gobj;
    Ground* gp;
    grVe_Data* base = &grVe_803E5348;
    StageCallbacks* callbacks =
        &((StageCallbacks*) ((char*) base + 0x44))[gobj_id];

    gobj = Ground_GetStageGObj(gobj_id);

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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
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

/// @todo Currently 99.90% match - needs minor register allocation fix
void grVenom_80203FD4(Ground_GObj* gobj)
{
    HSD_JObj* jobj1;
    HSD_JObj* jobj4;
    HSD_JObj* jobj3;
    HSD_JObj* jobj2;
    HSD_JObj* jobj5;
    HSD_JObj* jobj6;
    Ground* gp = gobj->user_data;
    PAD_STACK(8);

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
    Ground* gp = GET_GROUND(gobj);
    if (Stage_80225194() == 0xE4) {
        gp->gv.venom.xC8 = 1;
    }
}

/// grVenom_802040F0

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

/// grVenom_80204284
/// @todo Currently 97.29% match - needs minor register allocation fix
void grVenom_80204284(Ground_GObj* gobj)
{
    Ground* gp;
    HSD_JObj* src_jobj;
    HSD_JObj* dst_jobj;
    u32 pad2;
    Ground_GObj* other_gobj;
    Vec3 pos;
    s32 timer;
    u32 pad;

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
                    grCorneria_801E25C4(other_gobj, &other_gp->gv.venom.xC4, 4,
                                        6, 0x6B6CC);
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

void grVenom_80204428(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    gp->gv.venom2.xC4 = Ground_801C3FA4(gobj, 4);
    gp->gv.venom2.xC8 = Ground_801C3FA4(gobj, 0xE);
    gp->gv.venom2.xCC = Ground_801C3FA4(gobj, 0x10);
    gp->gv.venom2.xD0 = Ground_801C3FA4(gobj, 0x11);
    gp->gv.venom2.xD4 = Ground_801C3FA4(gobj, 0x12);
    gp->gv.venom2.xD8 = Ground_801C3FA4(gobj, 0x13);
    gp->gv.venom2.xDC = Ground_801C3FA4(gobj, 0x15);

    gp->gv.venom2.xE0_state.b0 = 0;
    gp->gv.venom2.xE0_state.b1 = 0;
    gp->gv.venom2.xE0_state.b2 = 0;
    gp->gv.venom2.xE0_state.b3 = 0;
    gp->gv.venom2.xE0_state.b4 = 0;
    gp->gv.venom2.xE0_state.b5 = 0;
    gp->gv.venom2.xE0_state.b6 = 0;

    gp->gv.venom.xE4 = 0.0F;

    Ground_801C5440(gp, 0, 0x6B6C3);
    mpLib_80057BC0(2);
}

bool grVenom_80204544(Ground_GObj* arg)
{
    return false;
}

extern f64 grVe_804DB760; // 0.0 (double)
extern f32 grVe_804DB754; // 1000
extern f32 grVe_804DB758; // -60000
extern f32 grVe_804DB768; // 1033
extern f32 grVe_804DB76C; // 1086
extern f32 grVe_804DB770; // 1185
extern f32 grVe_804DB774; // 1238
extern f32 grVe_804DB778; // 1063
extern f32 grVe_804DB77C; // 1116
extern f32 grVe_804DB780; // 1215
extern f32 grVe_804DB784; // 1268
extern f32 grVe_804DB788; // 2460
extern f32 grVe_804DB78C; // 6440
extern f32 grVe_804DB790; // 9330
extern f32 grVe_804DB794; // 2747
extern f32 grVe_804DB798; // 3030
extern f32 grVe_804DB79C; // 3393
extern f32 grVe_804DB7A0; // 3727
extern f32 grVe_804DB7A4; // 6880
extern f32 grVe_804DB7A8; // 9600
extern f32 grVe_804DB7AC; // 9835
extern f32 grVe_804DB7B0; // 4070
extern f32 grVe_804DB7B4; // 7220
extern f32 grVe_804DB7B8; // 4200
extern f32 grVe_804DB7BC; // 3800
extern f32 grVe_804DB7C0; // 4400
extern f32 grVe_804DB7C4; // 6100
extern f32 grVe_804DB7C8; // 7210
extern f32 grVe_804DB7CC; // 6810
extern f32 grVe_804DB7D0; // 7410
extern f32 grVe_804DB7D4; // 9200

void grVenom_8020454C(Ground_GObj* gobj)
{
    Vec3 sp1C;
    s32 i = 0;
    Ground* gp = gobj->user_data;
    Ground* gp_save = gp;
    s32 visible;
    HSD_GObj* lgobj;
    HSD_LObj* lobj;
    f32 frame;
    f32 prev;
    f32 lo = grVe_804DB754;
    f32 hi = grVe_804DB758;
    PAD_STACK(8);

    do {
        if (gp->gv.venom2.xC4 != NULL) {
            lb_8000B1CC(gp->gv.venom2.xC4, NULL, &sp1C);
            visible = 1;
            if (!(sp1C.z < lo) && !(sp1C.z > hi)) {
                visible = 0;
            }
            if (HSD_JObjGetFlags(gp->gv.venom2.xC4) & 0x10) {
                if (visible != 0) {
                    HSD_JObjClearFlagsAll(gp->gv.venom2.xC4, 0x10);
                }
            } else if (visible == 0) {
                HSD_JObjSetFlagsAll(gp->gv.venom2.xC4, 0x10);
            }
        }
        i++;
        gp = (Ground*) ((char*) gp + 4);
    } while (i < 7);
    gp = gp_save;

    if (grAnime_801C84A4((HSD_GObj*) gobj, 0, 7)) {
        lgobj = Ground_801C498C();
        if (lgobj != NULL) {
            lobj = lgobj->hsd_obj;
            while (lobj != NULL) {
                if (lobj->aobj != NULL) {
                    HSD_AObjReqAnim(lobj->aobj, grVe_804DB740);
                }
                if (lobj->position != NULL) {
                    HSD_ForeachAnim(lobj->position, WOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF,
                                    grVe_804DB760);
                }
                if (lobj->interest != NULL) {
                    HSD_ForeachAnim(lobj->interest, WOBJ_TYPE, ALL_TYPE_MASK,
                                    HSD_AObjReqAnim, AOBJ_ARG_AF,
                                    grVe_804DB760);
                }
                if (lobj == NULL) {
                    lobj = NULL;
                } else {
                    lobj = lobj->next;
                }
            }
        }
    }

    {
        HSD_AObj* a = grAnime_801C8318((HSD_GObj*) gobj, 0, 7);
        if (a != NULL) {
            prev = gp->gv.venom.xE4;
            frame = HSD_AObjGetCurrFrame(a);
            if ((prev < grVe_804DB768 && grVe_804DB768 <= frame) ||
                (prev < grVe_804DB76C && grVe_804DB76C <= frame) ||
                (prev < grVe_804DB770 && grVe_804DB770 <= frame) ||
                (prev < grVe_804DB774 && grVe_804DB774 <= frame))
            {
                Ground_801C53EC(0x6B6C5);
            }
            if ((prev < grVe_804DB778 && grVe_804DB778 <= frame) ||
                (prev < grVe_804DB77C && grVe_804DB77C <= frame) ||
                (prev < grVe_804DB780 && grVe_804DB780 <= frame) ||
                (prev < grVe_804DB784 && grVe_804DB784 <= frame))
            {
                Ground_801C53EC(0x6B6C6);
            }
            if ((prev < grVe_804DB788 && grVe_804DB788 <= frame) ||
                (prev < grVe_804DB78C && grVe_804DB78C <= frame) ||
                (prev < grVe_804DB790 && grVe_804DB790 <= frame))
            {
                gp->gv.venom2.xE0_state.b6 = 1;
            }
            if ((prev < grVe_804DB788 && grVe_804DB788 <= frame) ||
                (prev < grVe_804DB794 && grVe_804DB794 <= frame) ||
                (prev < grVe_804DB798 && grVe_804DB798 <= frame) ||
                (prev < grVe_804DB79C && grVe_804DB79C <= frame) ||
                (prev < grVe_804DB7A0 && grVe_804DB7A0 <= frame) ||
                (prev < grVe_804DB78C && grVe_804DB78C <= frame) ||
                (prev < grVe_804DB7A4 && grVe_804DB7A4 <= frame) ||
                (prev < grVe_804DB790 && grVe_804DB790 <= frame) ||
                (prev < grVe_804DB7A8 && grVe_804DB7A8 <= frame) ||
                (prev < grVe_804DB7AC && grVe_804DB7AC <= frame))
            {
                Ground_801C53EC(0x6B6C7);
            }
            if ((prev < grVe_804DB7B0 && grVe_804DB7B0 <= frame) ||
                (prev < grVe_804DB7B4 && grVe_804DB7B4 <= frame) ||
                (prev > frame))
            {
                gp->gv.venom2.xE0_state.b6 = 0;
            }
            if (prev < grVe_804DB7B8 && grVe_804DB7B8 <= frame) {
                gp->gv.venom2.xE0_state.b0 = 1;
            }
            if (prev < grVe_804DB7BC && grVe_804DB7BC <= frame) {
                gp->gv.venom2.xE0_state.b1 = 1;
            }
            if (prev < grVe_804DB7C0 && grVe_804DB7C0 <= frame) {
                Ground_801C5440(gp, 0, 0x6B6C4);
                gp->gv.venom2.xE0_state.b2 = 1;
                mpJointListAdd(2);
            }
            if (prev < grVe_804DB7C4 && grVe_804DB7C4 <= frame) {
                Ground_801C5440(gp, 0, 0x6B6C3);
                gp->gv.venom2.xE0_state.b0 = 0;
                gp->gv.venom2.xE0_state.b1 = 0;
                gp->gv.venom2.xE0_state.b2 = 0;
                mpLib_80057BC0(2);
            }
            if (prev < grVe_804DB7C8 && grVe_804DB7C8 <= frame) {
                gp->gv.venom2.xE0_state.b3 = 1;
            }
            if (prev < grVe_804DB7CC && grVe_804DB7CC <= frame) {
                gp->gv.venom2.xE0_state.b4 = 1;
            }
            if (prev < grVe_804DB7D0 && grVe_804DB7D0 <= frame) {
                gp->gv.venom2.xE0_state.b5 = 1;
            }
            if (prev < grVe_804DB7D4 && grVe_804DB7D4 <= frame) {
                gp->gv.venom2.xE0_state.b3 = 0;
                gp->gv.venom2.xE0_state.b4 = 0;
                gp->gv.venom2.xE0_state.b5 = 0;
            }
            gp->gv.venom.xE4 = frame;
        }
    }

    lbAudioAx_80024D78(gp->gv.venom2.xE0_state.b2 ? 2 : 1);
    grVenom_80204B88(gobj);
}

void grVenom_80204B84(Ground_GObj* arg) {}

/// grVenom_80204B88
/// Updates Venom stage lighting colors based on environment state.

extern GXColor grVe_804DB7D8;
extern GXColor grVe_804DB7DC;
extern GXColor grVe_804DB7E0;
extern GXColor grVe_804DB7E4;

void grVenom_80204B88(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    u8 env_flags;
    GXColor color_set1;
    GXColor color_set2;
    GXColor color_neutral1;
    GXColor color_neutral2;

    env_flags = *(u8*) &gp->gv.venom2.xE0_state.xE0_state_pad;

    if ((env_flags >> 5) & 1) {
        if (gp->gv.venom2.xE0_state.xE0_state_pad.state != 1) {
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
            gp->gv.venom2.xE0_state.xE0_state_pad.state = 1;
        }
    } else if ((env_flags >> 1) & 1) {
        if (gp->gv.venom2.xE0_state.xE0_state_pad.state != 2) {
            color_set2 = grVe_804DB7DC;
            Ground_801C05BC(&color_set2);
            gp->gv.venom2.xE0_state.xE0_state_pad.state = 2;
        }
    } else {
        if (gp->gv.venom2.xE0_state.xE0_state_pad.state != 0) {
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
            gp->gv.venom2.xE0_state.xE0_state_pad.state = 0;
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

    ifStatus_802F6898();
    un_802FF570();

    if (Ground_801C2BA4(1) == NULL) {
        if (grCorneria_801E2598(gp->gv.venom.xC4, gp->gv.venom.xC8) != 0) {
            temp = gp->gv.venom.xCC;
            gp->gv.venom.xCC = temp - 1;
            if (temp < 0) {
                HSD_GObj* gobj = grVenom_80203EAC(1);
                Ground* gp2 = GET_GROUND(gobj);
                grCorneria_801E2738(gobj, &gp2->gv.venom.xC4, gp->gv.venom.xC4,
                                    gp->gv.venom.xC8);
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

/// grVenom_80204DD4
/// Unit: main/melee/gr/grvenom
/// Manual expansion of HSD_JObjSetScaleX/Y without using inline functions

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

void grVenom_80204F20(Ground_GObj* arg0)
{
    s32* base = (s32*) &grVe_803E5348;
    Ground* gp = arg0->user_data;
    HSD_JObj* jobj = arg0->hsd_obj;
    u32 idx = grVe_804D6A34;
    HSD_GObj* other;
    f32 scale;
    s32 state;

    gp->gv.venom.xC8 = idx;
    base[idx + 8] = (s32) arg0;

    other = grVenom_80203EAC(base[base[idx + 14] + 170]);
    if (other != NULL) {
        Ground* other_gp = other->user_data;
        other_gp->x10_flags.b2 = 0;
        other_gp = other->user_data;
        if (other_gp != NULL) {
            other_gp->gv.venom.xC8 = gp->gv.venom.xC8;
        } else {
            OSReport((char*) ((u8*) base + 0x2BC), other_gp, 0);
        }
    }

    scale = Ground_801C0498();
    state = base[idx + 11];
    if (state < 8) {
        if (state >= 1) {
            HSD_JObjSetScaleX(jobj, scale);
            HSD_JObjSetScaleY(jobj, scale);
            HSD_JObjSetScaleZ(jobj,
                              scale * *(f32*) ((u8*) grVe_804D6A30 + 0x34));
        }
    } else if (state < 12) {
        HSD_JObjSetScaleX(jobj, scale);
        HSD_JObjSetScaleY(jobj, scale);
        HSD_JObjSetScaleZ(jobj, scale);
    }

    gp->gv.venom.xD4 = 1;
    gp->gv.venom.xD8 = 0;
}

bool grVenom_802052D8(Ground_GObj* arg)
{
    return false;
}

/// @todo Currently 99.92% match - needs minor register allocation fix
/// @todo VenomSpawnData struct should be defined in gr/types.h or grvenom.h
typedef struct {
    u8 pad[0x218];
    f32 x;
    f32 y;
    f32 z;
} VenomSpawnData;

void grVenom_802052E0(Ground_GObj* gobj, Vec3* pos)
{
    u8* new_var2;
    Vec3 jobj_pos;
    s32* spawn_table = (s32*) &grVe_803E5348;
    Ground* gp;
    HSD_JObj* jobj;
    s32* new_var;
    s32* new_var4;
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
        new_var2 = (u8*) new_var4;
        new_var3 = &gp->gv.venom;
        spawn_idx = (*new_var3).xC8;
        data_idx = new_var[spawn_idx + 11];
        spawn_data = (VenomSpawnData*) (new_var2 + data_idx * 12);
        pos->x = jobj_pos.x + spawn_data->x;
        pos->y = jobj_pos.y + spawn_data->y;
        pos->z = jobj_pos.z + spawn_data->z;
    } else {
        pos->x = pos->y = pos->z = grVe_804DB740;
    }
}

/// grVenom_802053B0
/// @todo Currently 92.15% match - needs register allocation fix
/// Needs: grVe_804DB740 extern float

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
        if ((s32) gp->gv.venom.xD4 == 1) {
            gp->gv.venom.xD4 = 0;
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
                state = gp->gv.venom.xD8;
                switch (state) {
                case 0:
                    if (grVenom_80205DF8(&sp28) == 0) {
                        lbAudioAx_800237A8(0x6B6C0, 0x7F, 0x40);
                        gp->gv.venom.xD8 = 1;
                    }
                    break;
                case 1:
                    if (grVenom_80205E84(&sp28) == 0) {
                        gp->gv.venom.xD8 = 2;
                    }
                    break;
                case 2:
                    if (grVenom_80205E84(&sp28) == 1) {
                        lbAudioAx_800237A8(0x6B6C2, 0x7F, 0x40);
                        gp->gv.venom.xD8 = 3;
                    }
                    break;
                }
            }
        } else if (state < 12) {
            HSD_JObjSetRotationY(jobj, grVe_804DB740);

            gp2 = gobj->user_data;
            grVenom_802052E0(gobj, &sp1C);
            state = gp2->gv.venom.xD8;
            switch (state) {
            case 0:
                if (grVenom_80205DF8(&sp1C) == 0) {
                    lbAudioAx_800237A8(0x6B6C0, 0x7F, 0x40);
                    gp2->gv.venom.xD8 = 1;
                }
                break;
            case 1:
                if (grVenom_80205E84(&sp1C) == 0) {
                    gp2->gv.venom.xD8 = 2;
                }
                break;
            case 2:
                if (grVenom_80205E84(&sp1C) == 1) {
                    lbAudioAx_800237A8(0x6B6C2, 0x7F, 0x40);
                    gp2->gv.venom.xD8 = 3;
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

/// grVenom_802056B0

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

/// grVenom_80205758

extern f32 grVe_804DB7E8;
extern f64 grVe_804DB7F0;
extern f64 grVe_804DB7F8;
extern f64 grVe_804DB800;

void grVenom_80205758(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    s32* base = (s32*) &grVe_803E5348;
    HSD_JObj* jobj = gobj->hsd_obj;
    s32* entry = base + gp->gv.venom.xC8;
    f32 v;
    f32 scale;

    if ((u32) entry[8] != 0U) {
        v = gp->gv.venom.xE8;
        if (v < grVe_804DB740) {
            v = -v;
        }
        if (v < grVe_804DB7E8) {
            gp->gv.venom.xE8 = grVe_804DB740;
            while (gp->gv.venom.xDC < (f32) grVe_804DB7F8) {
                gp->gv.venom.xDC = gp->gv.venom.xDC + grVe_804DB7F0;
            }
            while (gp->gv.venom.xDC > (f32) grVe_804DB800) {
                gp->gv.venom.xDC = gp->gv.venom.xDC - grVe_804DB7F0;
            }
            v = gp->gv.venom.xDC;
            if (v < grVe_804DB740) {
                v = -v;
            }
            if (v < grVe_804DB744) {
                HSD_JObjClearFlagsAll(jobj, 0x10);
            } else {
                HSD_JObjSetFlagsAll(jobj, 0x10);
            }
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }

        HSD_JObjSetTranslate(jobj, (Vec3*) &gp->gv.venom.xE0);

        scale = Ground_801C0498();
        HSD_JObjSetScaleX(jobj, scale * *(f32*) ((u8*) grVe_804D6A30 + 0x34));
        HSD_JObjSetScaleY(jobj, scale * *(f32*) ((u8*) grVe_804D6A30 + 0x34));
        HSD_JObjSetScaleZ(jobj, scale * *(f32*) ((u8*) grVe_804D6A30 + 0x34));

        Ground_801C2FE0(gobj);
    } else {
        mpLib_80057BC0(base[entry[14] + 0xCE]);
        Ground_801C4A08(gobj);
    }
}

void grVenom_80205AD0(Ground_GObj* arg) {}

/// grVenom_80205AD4
/// @todo Currently 98.62% match - needs register allocation fixes
void grVenom_80205AD4(Ground_GObj* gobj)
{
    s32 zero;
    u8* base;
    HSD_JObj* jobj;
    Ground* gp;
    f32 scale;
    u8* data;
    s32 type;
    Ground_GObj* other;
    Ground* other_gp;
    HSD_JObj* jobj2;
    f32 scl;
    void* attr;

    zero = 0;
    base = (u8*) &grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    scale = Ground_801C0498();

    gp->gv.venom.xC8 = grVe_804D6A34;
    *(s32*) &gp->gv.venom.xEC = zero;
    *(s32*) &gp->gv.venom.xE8 = zero;
    *(s32*) &gp->gv.venom.xE4 = zero;
    *(s32*) &gp->gv.venom.xE0 = zero;

    grAnime_801C7FF8(gobj, 7, 7, 0, 0.0F, 1.0F);
    grAnime_801C7FF8(gobj, 8, 7, 0, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);

    data = base + gp->gv.venom.xC8 * 4;
    type = *(s32*) (data + 0x2C);

    if (type < 8) {
        if (type >= 1) {
            goto venom_80205AD4_spawn;
        }
        goto venom_80205AD4_default;
    }
    if (type >= 0xC) {
        goto venom_80205AD4_default;
    }
    goto venom_80205AD4_link;

venom_80205AD4_spawn: {
    s32 idx = *(s32*) (data + 0x38);
    u8* data2 = base + idx * 4;
    other = (Ground_GObj*) grVenom_80203EAC(*(s32*) (data2 + 0x324));
    *(s32*) &gp->gv.venom.xDC = (s32) other;
    if (other != NULL) {
        other = *(Ground_GObj**) &gp->gv.venom.xDC;
        other_gp = other->user_data;
        if (other_gp != NULL) {
            other_gp->gv.venom.xC8 = gp->gv.venom.xC8;
        }
    }
    goto venom_80205AD4_done;
}

venom_80205AD4_link:
    jobj2 = Ground_801C3FA4((HSD_GObj*) *(s32*) (data + 0x20), 5);
    lb_8000C2F8(Ground_801C3FA4(gobj, 0), jobj2);
    *(s32*) &gp->gv.venom.xDC = zero;
    goto venom_80205AD4_done;

venom_80205AD4_default:
    *(s32*) &gp->gv.venom.xE0 = -1;
    *(s32*) &gp->gv.venom.xE4 = -1;

venom_80205AD4_done:

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleX(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleY(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleZ(jobj, scl);

    ((struct grCorneria_GroundVars2*) &gp->gv.venom)->xC4.flags.b0 = false;
    *(s32*) &gp->gv.venom.xD4 = zero;
    gp->gv.venom.xF0 = zero;
    gp->gv.venom.xF4 = zero;

    attr = grVe_804D6A30;
    gp->gv.venom.xF8 = (s32) * (f32*) ((u8*) attr + 0x2C);
    gp->gv.venom.xFC = zero;
    gp->gv.venom.x100 = HSD_Randi(2);
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

/// grVenom_80205E84

float Stage_GetBlastZoneBottomOffset(void);
float Stage_GetBlastZoneLeftOffset(void);
float Stage_GetBlastZoneRightOffset(void);
float Stage_GetBlastZoneTopOffset(void);

s32 grVenom_80205E84(Vec3* pos)
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

/// grVenom_80205F30
/// @todo First attempt at decomp; complex 592-instruction function.

extern Vec3 grVe_803B82D0;
extern Vec3 grVe_803B82DC;

void grVenom_80205F30(Ground_GObj* gobj)
{
    Vec3 sp94;
    Vec3 sp88;
    Vec3 sp64;
    Vec3 sp50;
    Ground* gp;
    HSD_JObj* jobj;
    HSD_GObj* other;
    Ground* other_gp;
    HSD_JObj* tmp_jobj;
    s32* base;
    s32* entry;
    s32 state;
    s32 fire_kind;
    s32 slot;
    s32 retries;
    u8* base_b;
    s32 type_idx;
    HSD_JObj* helper;

    base = (s32*) &grVe_803E5348;
    base_b = (u8*) &grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    sp94 = grVe_803B82D0;
    sp88 = grVe_803B82DC;

    if (grVe_804D6A40 != 0) {
        return;
    }

    entry = base + gp->gv.venom.xC8;
    if ((u32) entry[8] != 0U) {
        if (entry[14] == 4) {
            tmp_jobj = Ground_801C3FA4((HSD_GObj*) gobj, 1);
            if (tmp_jobj == NULL) {
                __assert("jobj.h", 0x2A9, "jobj");
            }
            if (tmp_jobj->flags & 0x20000) {
                __assert("jobj.h", 0x2AA, (char*) base + 0x2D4);
            }
            tmp_jobj->rotate.z = 0.0F;
            if (!(tmp_jobj->flags & 0x02000000)) {
                if (tmp_jobj != NULL) {
                    s32 dirty = 0;
                    u32 f = tmp_jobj->flags;
                    if (!(f & 0x800000) && (f & 0x40)) {
                        dirty = 1;
                    }
                    if (dirty == 0) {
                        HSD_JObjSetMtxDirtySub(tmp_jobj);
                    }
                }
            }
        }

        state = base[gp->gv.venom.xC8 + 11];
        if (state < 8) {
            if (state >= 1) {
                if (jobj == NULL) {
                    __assert("jobj.h", 0x294, "jobj");
                }
                if (jobj->flags & 0x20000) {
                    __assert("jobj.h", 0x295, (char*) base + 0x2D4);
                }
                jobj->rotate.y = 0.0F;
                if (!(jobj->flags & 0x02000000)) {
                    if (jobj != NULL) {
                        s32 dirty = 0;
                        u32 f = jobj->flags;
                        if (!(f & 0x800000) && (f & 0x40)) {
                            dirty = 1;
                        }
                        if (dirty == 0) {
                            HSD_JObjSetMtxDirtySub(jobj);
                        }
                    }
                }

                if (gp->gv.venom.xF4 != 0) {
                    if (gp->gv.venom.xF4 < 0 || gp->gv.venom.xF4 >= 5) {
                        /* nothing */
                    } else {
                        if (grAnime_801C83D0((HSD_GObj*) gobj, 0, 7) != 0) {
                            gp->gv.venom.xF4 = 0;
                            gp->gv.venom.xF8 =
                                (s32) * (f32*) ((u8*) grVe_804D6A30 + 0x2C);
                        }
                    }
                } else {
                    if (gp->gv.venom.xF8 <= 0) {
                        gp->gv.venom.xF4 = HSD_Randi(4) + 1;
                        fire_kind = -1;
                        {
                            Ground* gp_re = gobj->user_data;
                            s32 v = base[gp_re->gv.venom.xC8 + 14];
                            if (v == 4) {
                                fire_kind = 1;
                            } else if (v >= 4) {
                                /* default branch (>= 4 but != 4 - shouldn't
                                 * happen for s32 == 4 case) */
                            } else if (v == 0) {
                                /* case 0: no change */
                            } else if (v >= 0) {
                                fire_kind = 0;
                            }
                        }
                        {
                            s32 idx0 = base[gp->gv.venom.xC8 + 14];
                            s32 anim_id =
                                base[idx0 * 4 +
                                     0xD6]; /* +0x358 = +0xD6 in s32 */
                            f32 frame = ((
                                f32*) ((u8*) base + gp->gv.venom.xF4 * 8 +
                                       fire_kind * 4))[0xBF]; /* 0x2FC offset;
                                                                 but better: */
                            (void) frame;
                            grAnime_801C8098((HSD_GObj*) gobj, anim_id, 7,
                                             *(s32*) ((u8*) base +
                                                      gp->gv.venom.xF4 * 8 +
                                                      fire_kind * 4 + 0x2FC),
                                             0.0F, 1.0F);
                        }
                    } else {
                        s32 idx0 = base[gp->gv.venom.xC8 + 14];
                        s32 anim_id = base[idx0 * 4 + 0xD6];
                        tmp_jobj = Ground_801C3FA4((HSD_GObj*) gobj, anim_id);
                        if (tmp_jobj == NULL) {
                            __assert("jobj.h", 0x2A9, "jobj");
                        }
                        if (tmp_jobj->flags & 0x20000) {
                            __assert("jobj.h", 0x2AA, (char*) base + 0x2D4);
                        }
                        tmp_jobj->rotate.z = 0.0F;
                        if (!(tmp_jobj->flags & 0x02000000)) {
                            if (tmp_jobj != NULL) {
                                s32 dirty = 0;
                                u32 f = tmp_jobj->flags;
                                if (!(f & 0x800000) && (f & 0x40)) {
                                    dirty = 1;
                                }
                                if (dirty == 0) {
                                    HSD_JObjSetMtxDirtySub(tmp_jobj);
                                }
                            }
                        }
                    }
                    gp->gv.venom.xF8 = gp->gv.venom.xF8 - 1;
                }

                other = (HSD_GObj*) base[gp->gv.venom.xC8 + 8];
                if (other != NULL) {
                    Ground* other_gp_local = other->user_data;
                    Ground_801C2BA4(5);
                    lb_8000B1CC(Ground_801C3FA4(other, 5), NULL, &sp64);
                    {
                        f32* tab =
                            (f32*) ((u8*) base +
                                    base[other_gp_local->gv.venom.xC8 + 11] *
                                        12);
                        sp94.x = sp64.x + tab[0x86]; /* +0x218 / 4 */
                        sp94.y = sp64.y + tab[0x87];
                        sp94.z = sp64.z + tab[0x88];
                    }
                } else {
                    sp94.x = 0.0F;
                    sp94.y = 0.0F;
                    sp94.z = 0.0F;
                }

                if (jobj == NULL) {
                    __assert("jobj.h", 0x394, "jobj");
                }
                jobj->translate.x = sp94.x;
                jobj->translate.y = sp94.y;
                jobj->translate.z = sp94.z;
                if (!(jobj->flags & 0x02000000)) {
                    if (jobj != NULL) {
                        s32 dirty = 0;
                        u32 f = jobj->flags;
                        if (!(f & 0x800000) && (f & 0x40)) {
                            dirty = 1;
                        }
                        if (dirty == 0) {
                            HSD_JObjSetMtxDirtySub(jobj);
                        }
                    }
                }

                {
                    s32 idx0 = base[gp->gv.venom.xC8 + 14];
                    s32 anim_id = base[idx0 * 4 + 0xD6];
                    lb_8000B1CC(Ground_801C3FA4((HSD_GObj*) gobj, anim_id),
                                NULL, &sp94);
                }
                if (*(u32*) &gp->gv.venom.xDC != 0U) {
                    void* sub =
                        *(void**) ((u8*) (*(u32*) &gp->gv.venom.xDC) + 0x2C);
                    if (sub != NULL) {
                        *(f32*) ((u8*) sub + 0xE0) = sp94.x;
                        *(f32*) ((u8*) sub + 0xE4) = sp94.y;
                        *(f32*) ((u8*) sub + 0xE8) = sp94.z;
                    }
                }

                {
                    s32 idx0 = base[gp->gv.venom.xC8 + 14];
                    s32 anim_id = base[idx0 * 4 + 0xD6];
                    helper = Ground_801C3FA4((HSD_GObj*) gobj, anim_id);
                    if (helper == NULL) {
                        __assert("jobj.h", 0x2E9, "jobj");
                    }
                    if (*(u32*) &gp->gv.venom.xDC != 0U) {
                        void* sub = *(
                            void**) ((u8*) (*(u32*) &gp->gv.venom.xDC) + 0x2C);
                        if (sub != NULL) {
                            *(f32*) ((u8*) sub + 0xDC) = helper->rotate.z;
                        }
                    }
                }
            }
        } else if (state < 0xC) {
            if (!(gp->gv.venom.xF0 & 7) && HSD_Randi(8) == 0) {
                gp->gv.venom.xFC = 0;
                type_idx = base[gp->gv.venom.xC8 + 11];
                switch (type_idx) {
                case 8:
                    if (gp->gv.venom.xF0 > 0x3C && gp->gv.venom.xF0 < 0xE6) {
                        gp->gv.venom.xFC = 1;
                    }
                    break;
                case 9:
                    if (gp->gv.venom.xF0 > 0x32 && gp->gv.venom.xF0 < 0xE6) {
                        gp->gv.venom.xFC = 1;
                    }
                    break;
                case 10:
                    if (gp->gv.venom.xF0 > 0x5A && gp->gv.venom.xF0 < 0x104) {
                        gp->gv.venom.xFC = 1;
                    }
                    break;
                case 11:
                    if (gp->gv.venom.xF0 > 0x46 && gp->gv.venom.xF0 < 0xF0) {
                        gp->gv.venom.xFC = 1;
                    }
                    break;
                }
            } else {
                gp->gv.venom.xFC = 0;
            }

            other = (HSD_GObj*) base[gp->gv.venom.xC8 + 8];
            if (other != NULL) {
                Ground* other_gp_local = other->user_data;
                Ground_801C2BA4(5);
                lb_8000B1CC(Ground_801C3FA4(other, 5), NULL, &sp50);
                {
                    f32* tab =
                        (f32*) ((u8*) base +
                                base[other_gp_local->gv.venom.xC8 + 11] * 12);
                    sp94.x = sp50.x + tab[0x86];
                    sp94.y = sp50.y + tab[0x87];
                    sp94.z = sp50.z + tab[0x88];
                }
            } else {
                sp94.x = 0.0F;
                sp94.y = 0.0F;
                sp94.z = 0.0F;
            }

            if (sp94.z < -100.0F && sp94.z > -2000.0F && gp->gv.venom.xFC != 0)
            {
                gp->gv.venom.xFC = 0;
                slot = HSD_Randi(4);
                retries = 0;
                do {
                    slot = (slot + retries) & 3;
                    if (Player_GetPlayerSlotType(slot) != 3) {
                        break;
                    }
                    retries++;
                } while (retries < 4);

                Player_LoadPlayerCoords(slot, &sp88);
                if ((sp88.x > 0.0F && sp94.x > 0.0F) ||
                    (sp88.x < 0.0F && sp94.x < 0.0F))
                {
                    sp88.y += 5.0F;
                    lbAudioAx_800237A8(0x6B6C9, 0x7F, 0x40);
                    fire_kind = -1;
                    {
                        Ground* gp_re = gobj->user_data;
                        s32 v = base[gp_re->gv.venom.xC8 + 14];
                        if (v == 4) {
                            fire_kind = 1;
                        } else if (v >= 4) {
                        } else if (v == 0) {
                        } else if (v >= 0) {
                            fire_kind = 0;
                        }
                    }
                    if (fire_kind == 1) {
                        it_802E7654(gobj, Ground_801C3FA4((HSD_GObj*) gobj, 7),
                                    &sp88, 3, 0,
                                    *(f32*) ((u8*) grVe_804D6A30 + 0x34));
                    } else {
                        if (gp->gv.venom.x100 != 0) {
                            it_802E7654(gobj,
                                        Ground_801C3FA4((HSD_GObj*) gobj, 5),
                                        &sp88, 1, 0,
                                        *(f32*) ((u8*) grVe_804D6A30 + 0x34));
                        } else {
                            it_802E7654(gobj,
                                        Ground_801C3FA4((HSD_GObj*) gobj, 6),
                                        &sp88, 1, 0,
                                        *(f32*) ((u8*) grVe_804D6A30 + 0x34));
                        }
                        gp->gv.venom.x100 = (gp->gv.venom.x100 + 1) & 1;
                    }
                    grMaterial_801C9604((HSD_GObj*) gobj,
                                        *(s32*) ((u8*) grVe_804D6A30 + 0x38),
                                        0);
                }
            }
        }

        gp->gv.venom.xF0 = gp->gv.venom.xF0 + 1;
    } else {
        if (*(u32*) &gp->gv.venom.xE0 != 0U) {
            Ground_801C4A08(*(HSD_GObj**) &gp->gv.venom.xE0);
        }
        if (*(u32*) &gp->gv.venom.xE4 != 0U) {
            Ground_801C4A08(*(HSD_GObj**) &gp->gv.venom.xE4);
        }
        if (*(u32*) &gp->gv.venom.xE8 != 0U) {
            Ground_801C4A08(*(HSD_GObj**) &gp->gv.venom.xE8);
        }
        if (*(u32*) &gp->gv.venom.xEC != 0U) {
            Ground_801C4A08(*(HSD_GObj**) &gp->gv.venom.xEC);
        }
        Ground_801C4A08((HSD_GObj*) gobj);
    }
}

/// #grVenom_80205F30

void grVenom_80206870(Ground_GObj* arg) {}

/// grVenom_80206874
/// @todo Currently 99.60% match - needs register allocation fixes
void grVenom_80206874(Ground_GObj* gobj)
{
    s32 zero;
    Ground* gp;
    HSD_JObj* jobj;
    f32 scale;
    u8* base;
    u8* data;
    s32 type;
    Ground_GObj* other;
    Ground* other_gp;
    HSD_JObj* jobj2;
    f32 scl;
    void* attr;

    zero = 0;
    base = (u8*) &grVe_803E5348;
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    scale = Ground_801C0498();

    gp->gv.venom.xC8 = grVe_804D6A34;
    *(s32*) &gp->gv.venom.xEC = zero;
    *(s32*) &gp->gv.venom.xE8 = zero;
    *(s32*) &gp->gv.venom.xE4 = zero;
    *(s32*) &gp->gv.venom.xE0 = zero;

    grAnime_801C7FF8(gobj, 0, 7, 1, 0.0F, 1.0F);
    grAnime_801C8098(gobj, 2, 7, 3, 0.0F, 1.0F);

    data = base + gp->gv.venom.xC8 * 4;
    type = *(s32*) (data + 0x2C);

    if (type < 8) {
        if (type >= 1) {
            goto venom_80206874_spawn;
        }
        goto venom_80206874_default;
    }
    if (type >= 0xC) {
        goto venom_80206874_default;
    }
    goto venom_80206874_link;

venom_80206874_spawn: {
    s32 idx = *(s32*) (data + 0x38);
    u8* data2 = base + idx * 4;

    other = (Ground_GObj*) grVenom_80203EAC(*(s32*) (data2 + 0x324));
    *(s32*) &gp->gv.venom.xDC = (s32) other;
    if (other != NULL) {
        other = *(Ground_GObj**) &gp->gv.venom.xDC;
        other_gp = other->user_data;
        if (other_gp != NULL) {
            other_gp->gv.venom.xC8 = gp->gv.venom.xC8;
        }
    }
    goto venom_80206874_done;
}

venom_80206874_link:
    jobj2 = Ground_801C3FA4((HSD_GObj*) *(s32*) (data + 0x20), 5);
    lb_8000C2F8(Ground_801C3FA4(gobj, 0), jobj2);
    *(s32*) &gp->gv.venom.xDC = zero;
    goto venom_80206874_done;

venom_80206874_default:
    *(s32*) &gp->gv.venom.xE0 = -1;
    *(s32*) &gp->gv.venom.xE4 = -1;

venom_80206874_done:

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleX(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleY(jobj, scl);

    attr = grVe_804D6A30;
    scl = scale * *(f32*) ((u8*) attr + 0x34);
    HSD_JObjSetScaleZ(jobj, scl);

    ((struct grCorneria_GroundVars2*) &gp->gv.venom)->xC4.flags.b0 = false;
    *(s32*) &gp->gv.venom.xD4 = zero;
    gp->gv.venom.xF0 = zero;
    gp->gv.venom.xF4 = zero;
    gp->gv.venom.xF8 = (s32) * (f32*) ((u8*) grVe_804D6A30 + 0x2C);
    gp->gv.venom.xFC = zero;
}

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
    grCorneria_801E277C(gobj, &gp->gv.smashtaunt);
}

void grVenom_80206BEC(Ground_GObj* arg) {}

extern char grVe_803E5524[];

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
    wgobj = (Ground_GObj*) grVenom_80203EAC(8);
    HSD_ASSERT(2244, wgobj);
    gp = wgobj->user_data;
    gp->gv.venom.xCC = 10;
    gp->gv.venom.xC8 = 0;
    gp->gv.venom.xC4 = var_r30;
    return 1;
}

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

bool grVenom_80206D7C(Vec3* pos, s32 arg1, HSD_JObj* arg2)
{
    Vec3 sp20;
    Vec3 sp14;
    HSD_GObj* gobj;
    Ground* gp;

    lb_8000B1CC(arg2, NULL, &sp20);
    gobj = Ground_801C2BA4(5);
    if (gobj != NULL) {
        gp = gobj->user_data;
        if (gp != NULL && (HSD_JObj*) gp->gv.venom.xD0 == arg2) {
            lb_8000B1CC((HSD_JObj*) gp->gv.venom.xCC, NULL, &sp14);
            if (pos->y > sp14.y) {
                return 0;
            }
        }
    }
    if (pos->y > sp20.y) {
        return 1;
    }
    return 0;
}
