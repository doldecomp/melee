#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/memory.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gm/gm_16AE.h"
#include "gr/grdatfiles.h"
#include "gr/grdisplay.h"
#include "gr/grfzerocar.h"
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

#include <trigf.h>

#include <dolphin/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/random.h>
#include <baselib/spline.h>

void grBigBlue_801E8D04(Ground_GObj*);

StageCallbacks grBb_Route_803E5E78[38] = {
    { grBigBlueRoute_8020BABC, grBigBlueRoute_8020BB00,
      grBigBlueRoute_8020BB08, grBigBlueRoute_8020BB0C, 0 },
    { grBigBlueRoute_8020BB68, grBigBlueRoute_8020BC24,
      grBigBlueRoute_8020BC2C, grBigBlueRoute_8020BC30, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { grBigBlueRoute_8020C140, grBigBlueRoute_8020C1D4,
      grBigBlueRoute_8020C1DC, grBigBlueRoute_8020C210, 0x80000000 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { grBigBlueRoute_8020BC68, grBigBlueRoute_8020BF30,
      grBigBlueRoute_8020BF38, grBigBlueRoute_8020C13C, 0x40000000 },
    { grBigBlueRoute_8020BB10, grBigBlueRoute_8020BB58,
      grBigBlueRoute_8020BB60, grBigBlueRoute_8020BB64, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
    { NULL, NULL, NULL, NULL, 0 },
};

char grBb_Route_803E6170[] = "/GrNBr.dat";

static struct {
    u32 internal_stage_id;
    StageCallbacks* callbacks;
    char* data1;
    void (*OnInit)(void);
    void (*OnDemoInit)(int);
    void (*OnLoad)(void);
    void (*OnStart)(void);
    bool (*callback4)(void);
    DynamicsDesc* (*callback5)(enum_t);
    bool (*callback6)(Vec3*, int, HSD_JObj*);
    u32 flags2;
    S16Vec3* x2C;
    size_t x30;
    char fmt[0x24];
} grBb_Route_803E617C = {
    BIGBLUEROUTE,
    grBb_Route_803E5E78,
    grBb_Route_803E6170,
    grBigBlueRoute_8020B89C,
    grBigBlueRoute_8020B864,
    grBigBlueRoute_8020B920,
    grBigBlueRoute_8020B95C,
    grBigBlueRoute_8020B9CC,
    grBigBlueRoute_8020DF78,
    grBigBlueRoute_8020DF80,
    1,
    NULL,
    0,
    "%s:%d: couldn t get gobj(id=%d)\n",
};

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
    Vec3 fighter_pos;
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

    gobj = Ground_GetStageGObj(gobj_id);

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
            HSD_GObj_SetupProc(gobj, callbacks->callback2, 4);
        }

    } else {
        OSReport(grBb_Route_803E617C.fmt, __FILE__, 0x117, gobj_id);
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

/// @todo Currently 99.83% match - remaining diffs are anonymous string-pool
/// symbols (translate/reb0_jobj) vs the target's single grBb_Route_803E61D4
void grBigBlueRoute_8020BC68(Ground_GObj* gobj)
{
    Vec3 origin;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;
    gp->gv.bigblueroute2.xC8 = 0;

    if (Ground_801C2D24(148, &origin)) {
        jobj = Ground_801C2CF4(127);
        gp->gv.bigblueroute2.xE4 = jobj;
        if (jobj != NULL) {
            jobj = gp->gv.bigblueroute2.xE4;
            HSD_JObjGetTranslation(jobj, &gp->gv.bigblueroute2.xD8);
            lbVector_Sub(&gp->gv.bigblueroute2.xD8, &origin);
        }

        jobj = Ground_801C2CF4(128);
        gp->gv.bigblueroute2.xF4 = jobj;
        if (jobj != NULL) {
            jobj = gp->gv.bigblueroute2.xF4;
            HSD_JObjGetTranslation(jobj, &gp->gv.bigblueroute2.xE8);
            lbVector_Sub(&gp->gv.bigblueroute2.xE8, &origin);
        }

        jobj = Ground_801C2CF4(129);
        gp->gv.bigblueroute2.x104 = jobj;
        if (jobj != NULL) {
            jobj = gp->gv.bigblueroute2.x104;
            HSD_JObjGetTranslation(jobj, &gp->gv.bigblueroute2.xF8);
            lbVector_Sub(&gp->gv.bigblueroute2.xF8, &origin);
        }

        jobj = Ground_801C2CF4(130);
        gp->gv.bigblueroute2.x114 = jobj;
        if (jobj != NULL) {
            jobj = gp->gv.bigblueroute2.x114;
            HSD_JObjGetTranslation(jobj, &gp->gv.bigblueroute2.x108);
            lbVector_Sub(&gp->gv.bigblueroute2.x108, &origin);
        }
    } else {
        gp->gv.bigblueroute2.xE4 = NULL;
        gp->gv.bigblueroute2.xF4 = NULL;
        gp->gv.bigblueroute2.x104 = NULL;
        gp->gv.bigblueroute2.x114 = NULL;
    }

    jobj = Ground_801C2CF4(4);
    HSD_ASSERT(452, jobj != NULL);
    HSD_JObjGetTranslation(jobj, &gp->gv.bigblueroute2.xCC);
    Ground_801C10B8(gobj, grBigBlueRoute_8020BC34);
}

bool grBigBlueRoute_8020BF30(Ground_GObj* arg)
{
    return false;
}

/// @todo Currently 98.29% match - register allocation only (extra mr through
/// r0 for first loop jobj load and idx computation)
void grBigBlueRoute_8020BF38(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_GObj* fighter;
    Vec3 checkpoint;
    Vec3 fighter_pos;
    int i;
    u8* car;
    HSD_JObj* jobj;

    fighter = Ground_801C57A4();
    Ground_801C3D44(0, 30.0f, 4000.0f);

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
            s32 idx = gp->gv.bigblueroute2.xC8 + 5;
            if (idx <= 7) {
                if (Ground_801C2D24(idx, &checkpoint) != 0) {
                    if (fighter_pos.x > checkpoint.x) {
                        gp->gv.bigblueroute2.xC8 =
                            gp->gv.bigblueroute2.xC8 + 1;
                    }
                }
            }
        }
        stage_info.x6DC = gp->gv.bigblueroute2.xC8;
    }

    lb_800115F4();
}

void grBigBlueRoute_8020C13C(Ground_GObj* arg) {}

extern u8 grBb_Route_803E6200[0x3C];

void grBigBlueRoute_8020C140(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    grFZeroCar_801CAFBC(gobj, grBb_Route_803E6200, 30, 0);
    *(s32*) ((u8*) gp + 0xCC) = (s32) Ground_801C247C(33, 1);
    *(s32*) ((u8*) gp + 0xD0) = (s32) Ground_801C247C(33, 0);
    *(s32*) ((u8*) gp + 0xD4) = (s32) Ground_801C247C(33, 2);
    grBigBlueRoute_8020C238(gobj);
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

void grBigBlueRoute_8020C238(Ground_GObj* gobj)
{
    HSD_JObj* root_jobj = gobj->hsd_obj;
    HSD_JObj* jobj;
    Ground* gp = gobj->user_data;
    Vec3 spline_pt;
    PAD_STACK(8);

    if (root_jobj != NULL) {
        f32 val;

        if (root_jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = root_jobj->child;
        }

        while (jobj != NULL) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleX(jobj, val);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleY(jobj, val);

            val = grBb_Route_804D6A68->x4;
            HSD_JObjSetScaleZ(jobj, val);

            if (jobj == NULL) {
                jobj = NULL;
            } else {
                jobj = jobj->next;
            }
        }
    }

    gp->gv.bigblueroute.xC8 = HSD_MemAlloc(0x554);
    ((gp->gv.bigblueroute.xC8)
         ? ((void) 0)
         : __assert(__FILE__, 674, "gp->u.car.car_info"));
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

s32 grBigBlueRoute_8020C530(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 30; i++) {
        if (!(*((u8*) gp->gv.bigblueroute.xC8 + i * 0x2C) >> 7 & 1)) {
            count++;
        }
    }

    if (count == 0) {
        return -1;
    }

    if (count != 0) {
        count = HSD_Randi(count);
    } else {
        count = 0;
    }

    for (i = 0; i < 30; i++) {
        if (!(*((u8*) gp->gv.bigblueroute.xC8 + i * 0x2C) >> 7 & 1)) {
            if (--count < 0) {
                return i;
            }
        }
    }
    __assert(__FILE__, 0x2E5, "0");
}

/// @todo Currently 92.06% match - register allocation (gp in r30 vs r31)
/// and addressing-mode choices for RouteEntry stores.
void grBigBlueRoute_8020C85C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    s32 route_idx;
    PAD_STACK(8);

    if (!((f32) gp->gv.bigblueroute.x108 < 1.0f + grBb_Route_804D6A68->x40)) {
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
            re->x20 = 5.2359877f * rand - 2.6179938f;
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

static const Vec3 grBb_Route_803B83E0 = { 0.0f, 1.0f, 0.0f };

/// @todo Currently 89.41% match - SYSTEMIC: float-constant hoisting order and
/// register pressure differ (target spills rot to stack; we keep it in FPRs).
#define RE_ENTRY ((RouteEntry*) ((u8*) gp->gv.bigblueroute.xC8 + offset))
void grBigBlueRoute_8020CD20(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;
    HSD_JObj* root_jobj = gobj->hsd_obj;
    HSD_GObj* fighter;
    Vec3 fighter_pos;
    HSD_JObj* jobj;
    int i;
    int offset;
    Vec3 pos;
    Vec3 rot;

    fighter = Ground_801C57A4();
    if (fighter == NULL) {
        return;
    }
    ftLib_80086644(fighter, &fighter_pos);

    if (root_jobj == NULL) {
        return;
    }
    jobj = HSD_JObjGetChild(root_jobj);
    if (jobj == NULL) {
        return;
    }

    i = 0;
    offset = 0;
    do {
        if (RE_ENTRY->flags.b0) {
            RE_ENTRY->x4 += RE_ENTRY->x8;
            if (RE_ENTRY->x4 > 1.0f) {
                RE_ENTRY->x4 = 1.0f;
            }
            RE_ENTRY->x14 += RE_ENTRY->x18;
            if (RE_ENTRY->x14 > 1.0f) {
                RE_ENTRY->x14 = 1.0f;
            }

            switch (RE_ENTRY->flags.b2_5) {
            case 0: {
                f32 t = RE_ENTRY->x4;
                f32 frac;
                Vec3 p0;
                Vec3 p1;
                Vec3 tangent;

                if (RE_ENTRY->xC < RE_ENTRY->x10) {
                    RE_ENTRY->xC += 0.01f;
                    if (RE_ENTRY->xC > RE_ENTRY->x10) {
                        RE_ENTRY->xC = RE_ENTRY->x10;
                    }
                } else if (RE_ENTRY->xC > RE_ENTRY->x10) {
                    RE_ENTRY->xC -= 0.01f;
                    if (RE_ENTRY->xC < RE_ENTRY->x10) {
                        RE_ENTRY->xC = RE_ENTRY->x10;
                    }
                }

                t = RE_ENTRY->x4;
                frac = RE_ENTRY->xC;
                splGetSplinePoint(&p0, gp->gv.bigblueroute.xD0, t);
                splGetSplinePoint(&p1, gp->gv.bigblueroute.xD4, t);
                lbShadow_8000E9F0(&tangent, gp->gv.bigblueroute.xD0, t);
                lbVector_Diff(&p1, &p0, &pos);
                pos.x *= frac;
                pos.y *= frac;
                pos.z *= frac;
                lbVector_Add(&pos, &p0);
                rot.x = -atan2f(tangent.y, tangent.x);
                rot.y = 1.5707964f;
                rot.z = 0.0f;

                if (RE_ENTRY->x4 > 0.966f) {
                    RE_ENTRY->flags.b2_5 = 2;
                    RE_ENTRY->x14 = 0.0f;
                    RE_ENTRY->x1C = 0.0f;
                    RE_ENTRY->x20 = 5.2359877f * HSD_Randf() - 2.6179938f;
                    RE_ENTRY->x24 = RE_ENTRY->x4;
                }
                break;
            }
            case 1: {
                f32 t;
                f32 angle;
                Vec3 up;
                Vec3 tangent;
                Vec3 side;
                Vec3 orient;

                if (RE_ENTRY->x1C < RE_ENTRY->x20) {
                    RE_ENTRY->x1C += 0.017453292f;
                    if (RE_ENTRY->x1C > RE_ENTRY->x20) {
                        RE_ENTRY->x1C = RE_ENTRY->x20;
                    }
                } else if (RE_ENTRY->x1C > RE_ENTRY->x20) {
                    RE_ENTRY->x1C -= 0.017453292f;
                    if (RE_ENTRY->x1C < RE_ENTRY->x20) {
                        RE_ENTRY->x1C = RE_ENTRY->x20;
                    }
                }

                t = RE_ENTRY->x14;
                angle = RE_ENTRY->x1C;
                up = grBb_Route_803B83E0;
                splGetSplinePoint(&pos, gp->gv.bigblueroute.xCC, t);
                lbShadow_8000E9F0(&tangent, gp->gv.bigblueroute.xCC, t);
                grBigBlueRoute_8020DD64(&tangent);
                PSVECCrossProduct(&up, &tangent, &side);
                lbVector_RotateAboutUnitAxis(&side, &tangent, angle);
                grBigBlueRoute_8020DD64(&side);
                PSVECCrossProduct(&tangent, &side, &up);
                grBigBlueRoute_8020DD64(&up);
                Ground_801C5AEC(&orient, &tangent, &side, &up);
                rot.x = orient.x;
                rot.y = orient.y;
                rot.z = orient.z;
                {
                    f32 s = 45.0f * Ground_801C0498();
                    up.x *= s;
                    up.y *= s;
                    up.z *= s;
                }
                lbVector_Add(&pos, &up);

                if (RE_ENTRY->x14 > 0.967f) {
                    RE_ENTRY->flags.b2_5 = 3;
                    RE_ENTRY->x4 = 0.0f;
                    RE_ENTRY->xC = 0.5f;
                    RE_ENTRY->x10 = HSD_Randf();
                    RE_ENTRY->x24 = RE_ENTRY->x14;
                    RE_ENTRY->flags.b6 = 0;
                    if (RE_ENTRY->flags.b1) {
                        gp->gv.bigblue.x0 &= ~0x40;
                    }
                }
                break;
            }
            case 2: {
                f32 prog;
                f32 frac;
                f32 t;
                f32 angle;
                Vec3 road;
                Vec3 road_tan;
                Vec3 p0;
                Vec3 p1;
                Vec3 up;
                Vec3 air;
                Vec3 tangent;
                Vec3 side;
                Vec3 orient;

                prog = (RE_ENTRY->x4 - RE_ENTRY->x24) / (1.0f - RE_ENTRY->x24);
                frac = ((1.0f - prog) * (RE_ENTRY->xC - 0.5f)) + 0.5f;
                splGetSplinePoint(&p0, gp->gv.bigblueroute.xD0, RE_ENTRY->x4);
                splGetSplinePoint(&p1, gp->gv.bigblueroute.xD4, RE_ENTRY->x4);
                lbShadow_8000E9F0(&road_tan, gp->gv.bigblueroute.xD0, RE_ENTRY->x4);
                lbVector_Diff(&p1, &p0, &road);
                road.x *= frac;
                road.y *= frac;
                road.z *= frac;
                lbVector_Add(&road, &p0);
                rot.x = -atan2f(road_tan.y, road_tan.x);
                rot.y = 1.5707964f;
                rot.z = 0.0f;

                t = RE_ENTRY->x14;
                angle = RE_ENTRY->x1C;
                up = grBb_Route_803B83E0;
                splGetSplinePoint(&air, gp->gv.bigblueroute.xCC, t);
                lbShadow_8000E9F0(&tangent, gp->gv.bigblueroute.xCC, t);
                grBigBlueRoute_8020DD64(&tangent);
                PSVECCrossProduct(&up, &tangent, &side);
                lbVector_RotateAboutUnitAxis(&side, &tangent, angle);
                grBigBlueRoute_8020DD64(&side);
                PSVECCrossProduct(&tangent, &side, &up);
                grBigBlueRoute_8020DD64(&up);
                Ground_801C5AEC(&orient, &tangent, &side, &up);
                {
                    f32 s = 45.0f * Ground_801C0498();
                    up.x *= s;
                    up.y *= s;
                    up.z *= s;
                }
                lbVector_Add(&air, &up);
                lbVector_Diff(&air, &road, &pos);
                pos.x *= prog;
                pos.y *= prog;
                pos.z *= prog;
                lbVector_Add(&pos, &road);
                rot.x = -atan2f(road_tan.y, road_tan.x);
                rot.y = 1.5707964f;
                rot.z = 0.0f;

                if (RE_ENTRY->x4 == 1.0f) {
                    RE_ENTRY->flags.b2_5 = 1;
                }
                break;
            }
            case 3: {
                f32 prog;
                f32 angle;
                f32 t;
                f32 frac;
                Vec3 up;
                Vec3 air;
                Vec3 tangent;
                Vec3 side;
                Vec3 orient;
                Vec3 p0;
                Vec3 p1;
                Vec3 road_tan;
                Vec3 road;

                prog = (RE_ENTRY->x14 - RE_ENTRY->x24) / (1.0f - RE_ENTRY->x24);
                up = grBb_Route_803B83E0;
                angle = (1.0f - prog) * RE_ENTRY->x1C;
                splGetSplinePoint(&air, gp->gv.bigblueroute.xCC, RE_ENTRY->x14);
                lbShadow_8000E9F0(&tangent, gp->gv.bigblueroute.xCC, RE_ENTRY->x14);
                grBigBlueRoute_8020DD64(&tangent);
                PSVECCrossProduct(&up, &tangent, &side);
                lbVector_RotateAboutUnitAxis(&side, &tangent, angle);
                grBigBlueRoute_8020DD64(&side);
                PSVECCrossProduct(&tangent, &side, &up);
                grBigBlueRoute_8020DD64(&up);
                Ground_801C5AEC(&orient, &tangent, &side, &up);
                rot.x = orient.x;
                rot.y = orient.y;
                rot.z = orient.z;
                {
                    f32 s = 45.0f * Ground_801C0498();
                    up.x *= s;
                    up.y *= s;
                    up.z *= s;
                }
                lbVector_Add(&air, &up);

                t = RE_ENTRY->x4;
                frac = RE_ENTRY->xC;
                splGetSplinePoint(&p0, gp->gv.bigblueroute.xD0, t);
                splGetSplinePoint(&p1, gp->gv.bigblueroute.xD4, t);
                lbShadow_8000E9F0(&road_tan, gp->gv.bigblueroute.xD0, t);
                lbVector_Diff(&p1, &p0, &road);
                road.x *= frac;
                road.y *= frac;
                road.z *= frac;
                lbVector_Add(&road, &p0);
                atan2f(road_tan.y, road_tan.x);
                lbVector_Diff(&road, &air, &pos);
                pos.x *= prog;
                pos.y *= prog;
                pos.z *= prog;
                lbVector_Add(&pos, &air);

                if (RE_ENTRY->x14 == 1.0f) {
                    RE_ENTRY->flags.b2_5 = 0;
                }
                break;
            }
            }

            if (!RE_ENTRY->flags.b1) {
                HSD_JObjSetTranslate(jobj, &pos);
                HSD_JObjSetRotationX(jobj, rot.x);
                HSD_JObjSetRotationY(jobj, rot.y);
                HSD_JObjSetRotationZ(jobj, rot.z);
            }

            if (pos.x - 260.0f < fighter_pos.x &&
                fighter_pos.x < 260.0f + pos.x &&
                pos.z - 260.0f < fighter_pos.z &&
                fighter_pos.z < 260.0f + pos.z && !RE_ENTRY->flags.b1) {
                if (!((gp->gv.bigblue.x0 >> 6) & 1)) {
                    gp->gv.bigblue.x0 |= 0x40;
                    Ground_801C53EC(0x77A16);
                }
            }

            if (pos.x - 100.0f < fighter_pos.x &&
                fighter_pos.x < 100.0f + pos.x &&
                pos.z - 100.0f < fighter_pos.z &&
                fighter_pos.z < 100.0f + pos.z) {
                if (RE_ENTRY->flags.b1) {
                    if (!((gp->gv.bigblue.x0 >> 7) & 1)) {
                        un_802FD604((s32) grBb_Route_804D6A68->x4C);
                        Ground_801C53EC(0x77A11);
                        gp->gv.bigblue.x0 |= 0x80;
                    }
                } else {
                    Camera_80030E44(1, NULL);
                    if (!RE_ENTRY->flags.b6) {
                        RE_ENTRY->flags.b6 = 1;
                        if (HSD_Randi(100) < 40) {
                            switch (HSD_Randi(3)) {
                            case 0:
                                Ground_801C53EC(0x77A15);
                                break;
                            case 1:
                                Ground_801C53EC(0x77A14);
                                break;
                            case 2:
                                Ground_801C53EC(0x77A13);
                                break;
                            }
                        }
                    }
                }
            } else if (RE_ENTRY->flags.b1) {
                if ((gp->gv.bigblue.x0 >> 7) & 1) {
                    gp->gv.bigblue.x0 &= ~0x80;
                }
            }
        }

        offset += 0x2C;
        i++;
        jobj = (jobj != NULL)
                   ? (HSD_JObj*) grBigBlueRoute_8020DA9C(
                         (struct grBigBlueRoute_8020DA9C_t*) jobj)
                   : NULL;
    } while (i < 31);
}
#undef RE_ENTRY

int grBigBlueRoute_8020DA9C(struct grBigBlueRoute_8020DA9C_t* desc)
{
    if (desc == NULL) {
        return 0;
    }
    return desc->x8;
}

/// @todo Currently 97.73% match - needs register allocation fix (r27/r30 swap
/// for arr/jobj)
void grBigBlueRoute_8020DAB4(HSD_JObj** jobjs, f32 scale, int count)
{
    int i;
    int countdown = 30;
    HSD_JObj** arr;
    HSD_JObj* jobj;
    HSD_GObj* gobj;

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

extern f32 grBb_Route_804DB994;
extern f32 grBb_Route_804DB998;
extern f32 grBb_Route_804DB99C;

/* Clamp camera position to stage bounds */
void grBigBlueRoute_8020DED4(Vec3* pos)
{
    f32 x = pos->x;
    f32 y = pos->y;

    if (x < grBb_Route_804DB994 * Ground_801C0498()) {
        x = grBb_Route_804DB994 * Ground_801C0498();
    }

    if (y < grBb_Route_804DB998 * Ground_801C0498()) {
        y = grBb_Route_804DB998 * Ground_801C0498();
    } else if (y > grBb_Route_804DB99C * Ground_801C0498()) {
        y = grBb_Route_804DB99C * Ground_801C0498();
    }

    Ground_801C38BC(x, y);
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
