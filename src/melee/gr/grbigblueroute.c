#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/memory.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_16AE.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grmaterial.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "gr/types.h"
#include "if/ifhazard.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <dolphin/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <baselib/spline.h>

void grBigBlue_801E8D04(Ground_GObj*);

extern StageCallbacks grBb_Route_803E5E78[];

static struct {
    int x0;
    f32 x4;
    u8 pad_8[0x20 - 0x8];
    f32 x20;
    u8 pad_24[0x3C - 0x24];
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
}* grBb_Route_804D6A68;

void grBigBlueRoute_8020B864(bool arg)
{
    HSD_GObj* gobj;
    gobj = Ground_801C2BA4(0x1F);
    if (gobj != NULL) {
        Ground_801C4A08(gobj);
    }
    grBigBlueRoute_8020B9D4(1);
}

void grBigBlueRoute_8020B89C(void)
{
    grBb_Route_804D6A68 = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grBigBlueRoute_8020B9D4(0);
    grBigBlueRoute_8020B9D4(0x20);
    grBigBlueRoute_8020B9D4(0x1F);
    Ground_801C39C0();
    Ground_801C3BB4();
    Camera_80030AE0(true);
    un_802FD8E8(grBigBlueRoute_8020DE48());
    un_802FD65C();
}

void grBigBlueRoute_8020B920(void)
{
    Point3d fighter_pos;
    HSD_GObj* fighter;

    fighter = Ground_801C57A4();
    if (fighter != NULL) {
        ftLib_80086644(fighter, &fighter_pos);
        grBigBlueRoute_8020DED4(&fighter_pos);
        Camera_8002F3AC();
    }
}

void grBigBlueRoute_8020B95C(void)
{
    int val;
    grZakoGenerator_801CAE04(NULL);
    if (gm_8016B3D8() == false) {
        return;
    }

    val = grBb_Route_804D6A68->x0;
    if (val != 0) {
        val = HSD_Randi(grBb_Route_804D6A68->x0);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grBigBlueRoute_8020B9CC(void)
{
    return false;
}

HSD_GObj* grBigBlueRoute_8020B9D4(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grBb_Route_803E5E78[gobj_id];

    gobj = Ground_801C14D0(gobj_id);

    if (gobj != NULL) {
        Ground* gp = gobj->user_data;
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
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", "grbigblueroute.c", 279,
                 gobj_id);
    }

    return gobj;
}

void grBigBlueRoute_8020BABC(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x11_flags.b012 = 2;
}

bool grBigBlueRoute_8020BB00(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BB08(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB0C(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB10(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
}

bool grBigBlueRoute_8020BB58(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BB60(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB64(Ground_GObj* arg) {}

void grBigBlueRoute_8020BB68(Ground_GObj* gobj)
{
    HSD_JObj *jobj, *jobj2, *jobj3, *jobj4, *jobj5, *jobj6;

    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    grAnime_801C77FC(gobj, 0, 7);
    jobj6 = Ground_801C3FA4(gobj, 7);
    jobj5 = Ground_801C3FA4(gobj, 8);
    jobj4 = Ground_801C3FA4(gobj, 4);
    jobj3 = Ground_801C3FA4(gobj, 5);
    jobj2 = Ground_801C3FA4(gobj, 3);
    jobj = Ground_801C3FA4(gobj, 6);
    Ground_801C4E70(jobj, jobj2, jobj3, jobj4, jobj5, jobj6);
}

bool grBigBlueRoute_8020BC24(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020BC2C(Ground_GObj* arg) {}

void grBigBlueRoute_8020BC30(Ground_GObj* arg) {}

void grBigBlueRoute_8020BC34(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    gp->gv.bigblueroute.xC4 = grBigBlueRoute_8020B9D4(4);
}

/// @todo Currently 90.72% match - HSD_JObjGetTranslation inline hoists dest
/// pointer to r27 (target uses r0 for addic. + r30+offset for stores)
void grBigBlueRoute_8020BC68(Ground_GObj* gobj)
{
    Vec3 origin;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;
    *(s16*) ((u8*) gp + 0xC8) = 0;

    if (Ground_801C2D24(148, &origin)) {
        jobj = Ground_801C2CF4(127);
        *(HSD_JObj**) ((u8*) gp + 0xE4) = jobj;
        if (jobj != NULL) {
            jobj = *(HSD_JObj**) ((u8*) gp + 0xE4);
            HSD_JObjGetTranslation(jobj, (Vec3*) ((u8*) gp + 0xD8));
            lbVector_Sub((Vec3*) ((u8*) gp + 0xD8), &origin);
        }

        jobj = Ground_801C2CF4(128);
        *(HSD_JObj**) ((u8*) gp + 0xF4) = jobj;
        if (jobj != NULL) {
            jobj = *(HSD_JObj**) ((u8*) gp + 0xF4);
            HSD_JObjGetTranslation(jobj, (Vec3*) ((u8*) gp + 0xE8));
            lbVector_Sub((Vec3*) ((u8*) gp + 0xE8), &origin);
        }

        jobj = Ground_801C2CF4(129);
        *(HSD_JObj**) ((u8*) gp + 0x104) = jobj;
        if (jobj != NULL) {
            jobj = *(HSD_JObj**) ((u8*) gp + 0x104);
            HSD_JObjGetTranslation(jobj, (Vec3*) ((u8*) gp + 0xF8));
            lbVector_Sub((Vec3*) ((u8*) gp + 0xF8), &origin);
        }

        jobj = Ground_801C2CF4(130);
        *(HSD_JObj**) ((u8*) gp + 0x114) = jobj;
        if (jobj != NULL) {
            jobj = *(HSD_JObj**) ((u8*) gp + 0x114);
            HSD_JObjGetTranslation(jobj, (Vec3*) ((u8*) gp + 0x108));
            lbVector_Sub((Vec3*) ((u8*) gp + 0x108), &origin);
        }
    } else {
        *(HSD_JObj**) ((u8*) gp + 0xE4) = NULL;
        *(HSD_JObj**) ((u8*) gp + 0xF4) = NULL;
        *(HSD_JObj**) ((u8*) gp + 0x104) = NULL;
        *(HSD_JObj**) ((u8*) gp + 0x114) = NULL;
    }

    jobj = Ground_801C2CF4(4);
    HSD_ASSERT(452, jobj != NULL);
    HSD_JObjGetTranslation(jobj, (Vec3*) ((u8*) gp + 0xCC));
    Ground_801C10B8(gobj, grBigBlueRoute_8020BC34);
}

bool grBigBlueRoute_8020BF30(Ground_GObj* arg)
{
    return false;
}

extern f32 grBb_Route_804DB948;
extern f32 grBb_Route_804DB94C;
extern s16 grBb_Route_804D49EC;

/// @todo Currently 95.33% match - address caching in counter section,
/// minor register allocation in loop jobj load
void grBigBlueRoute_8020BF38(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* fighter;
    Vec3 checkpoint;
    Vec3 fighter_pos;
    int i;
    u8* car;
    HSD_JObj* jobj;
    PAD_STACK(4);

    fighter = Ground_801C57A4();
    Ground_801C3D44(0, grBb_Route_804DB948, grBb_Route_804DB94C);

    if (fighter != NULL) {
        ftLib_80086644(fighter, &fighter_pos);

        if (ftLib_80086EC0(fighter) == 0) {
            grBigBlueRoute_8020DED4(&fighter_pos);

            for (i = 0, car = (u8*) gp; i < 3; i++, car += 0x10) {
                jobj = *(HSD_JObj**) (car + 0xE4);
                if (jobj != NULL) {
                    HSD_JObjSetTranslateX(jobj, *(f32*) (car + 0xD8) +
                                                    fighter_pos.x);

                    jobj = *(HSD_JObj**) (car + 0xE4);
                    HSD_JObjSetTranslateY(jobj, *(f32*) (car + 0xDC) +
                                                    fighter_pos.y);
                }
            }

            Camera_80030AE0(true);
        }

        {
            s32 idx = *(s16*) ((u8*) gp + 0xC8) + 5;
            if (idx <= 7) {
                if (mpLib_8004DBB4(idx, &checkpoint) != 0) {
                    if (fighter_pos.x > checkpoint.x) {
                        *(s16*) ((u8*) gp + 0xC8) =
                            *(s16*) ((u8*) gp + 0xC8) + 1;
                    }
                }
            }
        }
        grBb_Route_804D49EC = *(s16*) ((u8*) gp + 0xC8);
    }

    lb_800115F4();
}

void grBigBlueRoute_8020C13C(Ground_GObj* arg) {}

extern StageCallbacks grBb_Route_803E5E7C[];

void grBigBlueRoute_8020C140(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    Ground_801C3BA8(gobj, grBb_Route_803E5E7C, 30, 0);
    *(s32*) ((u8*) gp + 0xCC) = mpColl_8004F42C(33, 1);
    *(s32*) ((u8*) gp + 0xD0) = mpColl_8004F42C(33, 0);
    *(s32*) ((u8*) gp + 0xD4) = mpColl_8004F42C(33, 2);
    grBigBlue_801E8D04(gobj);
    ((UnkFlagStruct*) ((u8*) gp + 0xC4))->b0 = 0;
}

bool grBigBlueRoute_8020C1D4(Ground_GObj* arg)
{
    return false;
}

void grBigBlueRoute_8020C1DC(Ground_GObj* gobj)
{
    grBigBlueRoute_8020C85C(gobj);
    grBigBlueRoute_8020CD20(gobj);
}

void grBigBlueRoute_8020C210(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_Free((void*) gp->gv.bigblueroute.xC8);
}

/// @todo Currently 96.39% match - r30/r31 register swap
void grBigBlueRoute_8020C238(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* root_jobj = gobj->hsd_obj;
    Vec3 spline_pt;
    PAD_STACK(8);

    if (root_jobj != NULL) {
        f32 val;
        HSD_JObj* jobj = root_jobj->child;

        while (jobj != NULL) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleX(jobj, val);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleY(jobj, val);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleZ(jobj, val);

            if (jobj != NULL) {
                jobj = jobj->next;
            } else {
                jobj = NULL;
            }
        }
    }

    gp->gv.bigblueroute.xC8 = HSD_MemAlloc(0x554);
    HSD_ASSERT(674, gp->gv.bigblueroute.xC8);
    memzero(gp->gv.bigblueroute.xC8, 0x554);

    gp->gv.bigblueroute.x10A = 0;
    gp->gv.bigblueroute.x108 = 0;

    splGetSplinePoint(&gp->gv.bigblueroute.xD8, gp->gv.bigblueroute.xCC, 0.0F);
    splGetSplinePoint(&gp->gv.bigblueroute.xE4, gp->gv.bigblueroute.xCC, 1.0F);

    splGetSplinePoint(&gp->gv.bigblueroute.xF0, gp->gv.bigblueroute.xD0, 0.0F);
    splGetSplinePoint(&spline_pt, gp->gv.bigblueroute.xD4, 0.0F);
    lbVector_Add(&gp->gv.bigblueroute.xF0, &spline_pt);

    gp->gv.bigblueroute.xF0.x *= 0.5F;
    gp->gv.bigblueroute.xF0.y *= 0.5F;
    gp->gv.bigblueroute.xF0.z *= 0.5F;

    splGetSplinePoint(&gp->gv.bigblueroute.xFC, gp->gv.bigblueroute.xD0, 1.0F);
    splGetSplinePoint(&spline_pt, gp->gv.bigblueroute.xD4, 1.0F);
    lbVector_Add(&gp->gv.bigblueroute.xFC, &spline_pt);

    gp->gv.bigblueroute.xFC.x *= 0.5F;
    gp->gv.bigblueroute.xFC.y *= 0.5F;
    gp->gv.bigblueroute.xFC.z *= 0.5F;
}

/// #grBigBlueRoute_8020C530

/// @todo Currently 91.77% match - register allocation (gp in r30 vs r31)
/// and cror+beq vs bge for float >= comparison.
void grBigBlueRoute_8020C85C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 route_idx;
    PAD_STACK(8);

    if ((f32) gp->gv.bigblueroute.x108 >= 0.5F + grBb_Route_804D6A68->x40) {
        return;
    }

    if (gp->gv.bigblueroute.x10A-- >= 0) {
        return;
    }

    if (gp->gv.bigblueroute.x108 == 0) {
        route_idx = 30;
        /* RouteEntry array at xC8, each entry 44 bytes */
        ((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + 30 * 44))->b1 = 1;
        gp->gv.bigblueroute.x10A = grBb_Route_804D6A68->x4C;
    } else {
        s32 min_val;
        s32 max_val;
        s32 new_timer;

        route_idx = grBigBlueRoute_8020C530(gobj);

        ((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + route_idx * 44))
            ->b1 = 0;

        min_val = (s32) grBb_Route_804D6A68->x44;
        max_val = (s32) grBb_Route_804D6A68->x48;

        if (max_val > min_val) {
            s32 range = max_val - min_val;
            new_timer = min_val + ((range != 0) ? HSD_Randi(range) : 0);
        } else if (max_val < min_val) {
            s32 range = min_val - max_val;
            new_timer = max_val + ((range != 0) ? HSD_Randi(range) : 0);
        } else {
            new_timer = max_val;
        }
        gp->gv.bigblueroute.x10A = (s16) new_timer;
    }

    if (route_idx != -1) {
        s32 offset = route_idx * 44;
        RouteEntry* re;

        ((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + offset))->b0 = 1;
        ((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + offset))->b6 = 0;
        ((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + offset))->b2_5 =
            1;

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->x4 = 0.0F;

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->x8 = grBb_Route_804D6A68->x20;

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->xC = 0.0F;

        {
            f32 rand = HSD_Randf();
            re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
            re->x10 = rand;
        }

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->x14 = 0.0F;

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->x18 = grBb_Route_804D6A68->x3C;

        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
        re->x1C = 0.0F;

        {
            f32 rand = HSD_Randf();
            re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset);
            re->x20 = 2.0F * rand - 1.0F;
        }

        if (!((RouteEntryFlags*) ((u8*) gp->gv.bigblueroute.xC8 + offset))->b1)
        {
            HSD_JObj* root = gobj->hsd_obj;
            if (root != NULL) {
                HSD_JObj* jobj;
                if (root != NULL) {
                    jobj = root->child;
                } else {
                    jobj = NULL;
                }

                if (jobj != NULL) {
                    s32 i = 0;
                    while (i < route_idx && jobj != NULL) {
                        if (jobj != NULL) {
                            jobj = jobj->next;
                        } else {
                            jobj = NULL;
                        }
                        i++;
                    }

                    HSD_ASSERT(901, jobj);
                    HSD_JObjClearFlagsAll(jobj, 16);

                    HSD_JObjSetRotationX(jobj, 0.0F);
                    HSD_JObjSetRotationY(jobj, 0.0F);
                    HSD_JObjSetRotationZ(jobj, 0.0F);

                    {
                        Item_GObj* item = grMaterial_801C8CFC(
                            0, 1, gp, jobj,
                            (void (*)(Item_GObj*, Ground*)) fn_8020DEAC, NULL,
                            NULL);
                        re = (RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 +
                                            offset);
                        re->x28 = (void*) item;
                        if (item != NULL) {
                            grMaterial_801C8E28((HSD_GObj*) item);
                        }
                    }
                }
            }
        }
    }

    gp->gv.bigblueroute.x108++;
}

/// #grBigBlueRoute_8020CD20

int grBigBlueRoute_8020DA9C(struct grBigBlueRoute_8020DA9C_t* desc)
{
    if (desc == NULL) {
        return 0;
    }
    return desc->x8;
}

/// @todo Currently 97.71% match - needs register allocation fix (r27/r30 swap
/// for arr/jobj)
void grBigBlueRoute_8020DAB4(HSD_JObj** jobjs, f32 scale, int count)
{
    int i;
    int countdown = 30;
    HSD_JObj** arr;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    PAD_STACK(8);

    if (jobjs == NULL) {
        return;
    }

    gobj = grBigBlueRoute_8020B9D4(4);
    HSD_ASSERT(1414, gobj);
    {
        Ground* gp = GET_GROUND(gobj);
        HSD_ASSERT(1415, gp);
    }

    for (arr = jobjs, i = 0; i < count; countdown--, arr++, i++) {
        int random_idx;

        if (*arr == NULL) {
            continue;
        }

        random_idx = (countdown != 0) ? HSD_Randi(countdown) : 0;

        jobj = gobj->hsd_obj;
        HSD_ASSERT(1434, jobj);

        jobj = HSD_JObjGetChild(jobj);

        while (random_idx != 0) {
            HSD_ASSERT(1437, jobj);
            random_idx--;
            jobj = HSD_JObjGetNext(jobj);
        }

        HSD_JObjClearFlagsAll(jobj, 16);

        HSD_JObjSetScaleX(jobj, scale);
        HSD_JObjSetScaleY(jobj, scale);
        HSD_JObjSetScaleZ(jobj, scale);

        HSD_JObjReparent(jobj, *arr);
    }

    Ground_801C4A08(gobj);
}

void grBigBlueRoute_8020DD64(Vec3* v)
{
    f32 x;

    lbVector_Normalize(v);
    x = v->x;

    if (x > 1.0F) {
        v->x = 1.0F;
        v->z = 0.0F;
        v->y = 0.0F;
    } else if (x < -1.0F) {
        v->x = -1.0F;
        v->z = 0.0F;
        v->y = 0.0F;
    } else if (v->y > 1.0F) {
        v->y = 1.0F;
        v->z = 0.0F;
        v->x = 0.0F;
    } else if (v->y < -1.0F) {
        v->y = -1.0F;
        v->z = 0.0F;
        v->x = 0.0F;
    } else if (v->z > 1.0F) {
        v->z = 1.0F;
        v->y = 0.0F;
        v->x = 0.0F;
    } else if (v->z < -1.0F) {
        v->z = -1.0F;
        v->y = 0.0F;
        v->x = 0.0F;
    }
}

DynamicModelDesc* grBigBlueRoute_8020DE48(void)
{
    UnkArchiveStruct* archive = grDatFiles_801C6330(0x2);
    UnkStageDat* dat;
    HSD_ASSERT(1495, archive);
    dat = archive->unk4;
    if (dat != NULL) {
        return (DynamicModelDesc*) ((char*) dat->unk8 + 0x68);
    }
    return NULL;
}

void fn_8020DEAC(void)
{
    Ground_801C53EC(0x77A12);
}

/* Clamp camera position to stage bounds */
void grBigBlueRoute_8020DED4(Vec3* pos)
{
    f32 x = pos->x;
    f32 y = pos->y;

    if (x < -3.0F * Ground_801C0498()) {
        x = -3.0F * Ground_801C0498();
    }

    /* Both branches clamp y to the same value - this is how the
     * original code compiles (y is always clamped to -3*scale) */
    if (y < -3.0F * Ground_801C0498()) {
        y = -3.0F * Ground_801C0498();
    } else if (y > -3.0F * Ground_801C0498()) {
        y = -3.0F * Ground_801C0498();
    }

    Camera_8002A278(x, y);
}

DynamicsDesc* grBigBlueRoute_8020DF78(enum_t arg)
{
    return NULL;
}

bool grBigBlueRoute_8020DF80(Vec3* a, int arg, HSD_JObj* joint)
{
    Vec3 b;

    lb_8000B1CC(joint, NULL, &b);

    if (a->y > b.y + -3.0F) {
        return true;
    } else {
        return false;
    }
}
