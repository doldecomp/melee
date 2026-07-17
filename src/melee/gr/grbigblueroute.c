#include "grbigblueroute.h"

#include <platform.h>

#include "baselib/debug.h"
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
#include "lb/lbshadow.h"
#include "lb/lbspdisplay.h"
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

/// @todo Emitted only to lay out the .sdata2 literal pool in retail order.
static void sdata2_order(void)
{
    (void) 30.0f;
    (void) 4000.0f;
    (void) 0.0f;
    (void) 1.0f;
    (void) 0.5f;
    (void) 5.23598766f;
    (void) 2.61799383f;
    (void) S32_TO_F32;
    (void) 1.57079637f;
    (void) 45.0f;
    (void) 0.00999999978f;
    (void) 0.966000021f;
    (void) 0.0174532924f;
    (void) 0.967000008f;
    (void) 260.0f;
    (void) 100.0f;
    (void) -1.0f;
    (void) -1140.0f;
    (void) 20.0f;
    (void) 250.0f;
    (void) -3.0f;
}

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
    gp->u.car.xC4 = grBigBlueRoute_8020B9D4(4);
}

void grBigBlueRoute_8020BC68(Ground_GObj* gobj)
{
    Vec3 origin;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* reb0_jobj;

    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x10_flags.b5 = 1;
    gp->gv.bigblueroute2.xC8 = 0;

    if (Ground_801C2D24(148, &origin)) {
        reb0_jobj = Ground_801C2CF4(127);
        gp->gv.bigblueroute2.tracks[0].jobj = reb0_jobj;
        if (reb0_jobj != NULL) {
            reb0_jobj = gp->gv.bigblueroute2.tracks[0].jobj;
            HSD_JObjGetTranslation(reb0_jobj,
                                   &gp->gv.bigblueroute2.tracks[0].offset);
            lbVector_Sub(&gp->gv.bigblueroute2.tracks[0].offset, &origin);
        }

        reb0_jobj = Ground_801C2CF4(128);
        gp->gv.bigblueroute2.tracks[1].jobj = reb0_jobj;
        if (reb0_jobj != NULL) {
            reb0_jobj = gp->gv.bigblueroute2.tracks[1].jobj;
            HSD_JObjGetTranslation(reb0_jobj,
                                   &gp->gv.bigblueroute2.tracks[1].offset);
            lbVector_Sub(&gp->gv.bigblueroute2.tracks[1].offset, &origin);
        }

        reb0_jobj = Ground_801C2CF4(129);
        gp->gv.bigblueroute2.tracks[2].jobj = reb0_jobj;
        if (reb0_jobj != NULL) {
            reb0_jobj = gp->gv.bigblueroute2.tracks[2].jobj;
            HSD_JObjGetTranslation(reb0_jobj,
                                   &gp->gv.bigblueroute2.tracks[2].offset);
            lbVector_Sub(&gp->gv.bigblueroute2.tracks[2].offset, &origin);
        }

        reb0_jobj = Ground_801C2CF4(130);
        gp->gv.bigblueroute2.tracks[3].jobj = reb0_jobj;
        if (reb0_jobj != NULL) {
            reb0_jobj = gp->gv.bigblueroute2.tracks[3].jobj;
            HSD_JObjGetTranslation(reb0_jobj,
                                   &gp->gv.bigblueroute2.tracks[3].offset);
            lbVector_Sub(&gp->gv.bigblueroute2.tracks[3].offset, &origin);
        }
    } else {
        gp->gv.bigblueroute2.tracks[0].jobj = NULL;
        gp->gv.bigblueroute2.tracks[1].jobj = NULL;
        gp->gv.bigblueroute2.tracks[2].jobj = NULL;
        gp->gv.bigblueroute2.tracks[3].jobj = NULL;
    }

    reb0_jobj = Ground_801C2CF4(4);
    HSD_ASSERT(452, reb0_jobj);
    HSD_JObjGetTranslation(reb0_jobj, &gp->gv.bigblueroute2.xCC);
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
    HSD_JObj* jobj;

    fighter = Ground_801C57A4();
    Ground_801C3D44(0, 30.0f, 4000.0f);

    if (fighter != NULL) {
        ftLib_80086644(fighter, &fighter_pos);

        if (ftLib_80086EC0(fighter) == 0) {
            grBigBlueRoute_8020DED4(&fighter_pos);

            for (i = 0; i < 3; i++) {
                if (gp->gv.bigblueroute2.tracks[i].jobj != NULL) {
                    jobj = gp->gv.bigblueroute2.tracks[i].jobj;
                    HSD_JObjSetTranslateX(
                        jobj, gp->gv.bigblueroute2.tracks[i].offset.x +
                                  fighter_pos.x);

                    jobj = gp->gv.bigblueroute2.tracks[i].jobj;
                    HSD_JObjSetTranslateY(
                        jobj, gp->gv.bigblueroute2.tracks[i].offset.y +
                                  fighter_pos.y);
                }
            }

            Camera_80030AE0(true);
        }

        {
            s32 idx = gp->gv.bigblueroute2.xC8 + 5;
            if (gp->gv.bigblueroute2.xC8 + 5 <= 7) {
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

static s16 grBb_Route_carJObjIds[30] = {
    4,  5,  6,  8,  9,  10, 11, 12, 13, 14, 3,  15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 34, 35, 36, 37,
};

void grBigBlueRoute_8020C140(Ground_GObj* gobj)
{
    Ground* gp = gobj->user_data;

    grFZeroCar_801CAFBC(gobj, grBb_Route_carJObjIds, 30, 0);
    gp->u.car.xCC = (HSD_Spline*) Ground_801C247C(33, 1);
    gp->u.car.xD0 = (HSD_Spline*) Ground_801C247C(33, 0);
    gp->u.car.xD4 = (HSD_Spline*) Ground_801C247C(33, 2);
    grBigBlueRoute_8020C238(gobj);
    ((UnkFlagStruct*) &gp->u.car.xC4)->b0 = 0;
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
    HSD_Free((void*) gp->u.car.car_info);
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

    gp->u.car.car_info = HSD_MemAlloc(0x554);
    HSD_ASSERT(0x2A2, gp->u.car.car_info);
    memzero(gp->u.car.car_info, 0x554);

    gp->u.car.x10A = 0;
    gp->u.car.x108 = 0;

    splGetSplinePoint(&gp->u.car.xD8, gp->u.car.xCC, 0.0F);
    splGetSplinePoint(&gp->u.car.xE4, gp->u.car.xCC, 1.0F);

    splGetSplinePoint(&gp->u.car.xF0, gp->u.car.xD0, 0.0F);
    splGetSplinePoint(&spline_pt, gp->u.car.xD4, 0.0F);
    lbVector_Add(&gp->u.car.xF0, &spline_pt);

    gp->u.car.xF0.x *= 0.5F;
    gp->u.car.xF0.y *= 0.5F;
    gp->u.car.xF0.z *= 0.5F;

    splGetSplinePoint(&gp->u.car.xFC, gp->u.car.xD0, 1.0F);
    splGetSplinePoint(&spline_pt, gp->u.car.xD4, 1.0F);
    lbVector_Add(&gp->u.car.xFC, &spline_pt);

    gp->u.car.xFC.x *= 0.5F;
    gp->u.car.xFC.y *= 0.5F;
    gp->u.car.xFC.z *= 0.5F;
}

s32 grBigBlueRoute_8020C530(Ground_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    s32 count;
    s32 i;

    count = 0;
    for (i = 0; i < 30; i++) {
        if (!((RouteEntry*) gp->u.car.car_info)[i].flags.b0) {
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
        if (!((RouteEntry*) gp->u.car.car_info)[i].flags.b0) {
            if (--count < 0) {
                return i;
            }
        }
    }
    HSD_ASSERT(0X2E5, 0);
}

/// @todo Register allocation and addressing-mode choices for RouteEntry
/// stores.
static inline void grBigBlueRoute_SpawnRoute(s32 route_idx, Ground* gp,
                                             Ground_GObj* gobj)
{
    PAD_STACK(8);

    if (route_idx == 0) {
        route_idx = 30;
        ((RouteEntry*) gp->u.car.car_info)[30].flags.b1 = 1;
        gp->u.car.x10A = grBb_Route_804D6A68->x4C;
    } else {
        s32 max_val;
        s32 min_val;
        s32 new_timer;

        route_idx = grBigBlueRoute_8020C530(gobj);

        ((RouteEntry*) gp->u.car.car_info)[route_idx].flags.b1 = 0;

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
        gp->u.car.x10A = (s16) new_timer;
    }

    if (route_idx != -1) {
        // probably an inline of some sort
        RouteEntry* re = &((RouteEntry*) gp->u.car.car_info)[route_idx];

        (&((RouteEntry*) gp->u.car.car_info)[route_idx])->flags.b0 = 1;
        (&((RouteEntry*) gp->u.car.car_info)[route_idx])->flags.b6 = 0;
        (&((RouteEntry*) gp->u.car.car_info)[route_idx])->flags.b2_5 = 1;

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        re->x4 = 1.0F;

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        re->x8 = grBb_Route_804D6A68->x20;

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        re->xC = 0.5F;

        {
            f32 rand = HSD_Randf();
            re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
            re->x10 = rand;
        }

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        re->x14 = 0.0F;

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        re->x18 = grBb_Route_804D6A68->x3C;

        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
        (void) re;
        re->x1C = 0.0F;

        {
            f32 rand = HSD_Randf();
            re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
            (void) re;
            re->x20 = 5.2359877f * rand - 2.6179938f;
        }

        if (!((RouteEntry*) gp->u.car.car_info)[route_idx].flags.b1) {
            HSD_JObj* root = gobj->hsd_obj;
            if (root != NULL) {
                HSD_JObj* jobj;
                if (root == NULL) {
                    jobj = NULL;
                } else {
                    jobj = root->child;
                }

                if (jobj != NULL) {
                    s32 i = 0;
                    while (i < route_idx && jobj != NULL) {
                        i++;
                        if (jobj != NULL) {
                            jobj = jobj->next;
                        } else {
                            jobj = NULL;
                        }
                    }

                    HSD_ASSERT(901, jobj);
                    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

                    HSD_JObjSetRotationX(jobj, 0.0F);
                    HSD_JObjSetRotationY(jobj, 0.0F);
                    HSD_JObjSetRotationZ(jobj, 0.0F);

                    {
                        Item_GObj* item = grMaterial_801C8CFC(
                            0, 1, gp, jobj,
                            (void (*)(Item_GObj*, Ground*)) fn_8020DEAC, NULL,
                            NULL);
                        re = &((RouteEntry*) gp->u.car.car_info)[route_idx];
                        re->x28 = (void*) item;
                        if (item != NULL) {
                            grMaterial_801C8E28((HSD_GObj*) re->x28);
                        }
                    }
                }
            }
        }
    }

    gp->u.car.x108++;
}

static inline int grBigBlueRoute_DelayRoute(Ground* gp)
{
    return gp->u.car.x10A-- >= 0;
}

void grBigBlueRoute_8020C85C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    PAD_STACK(8);

    if (!((f32) gp->u.car.x108 < 1.0f + grBb_Route_804D6A68->x40)) {
        return;
    }

    if (grBigBlueRoute_DelayRoute(gp)) {
        return;
    }

    grBigBlueRoute_SpawnRoute(gp->u.car.x108, gp, gobj);
}

static const Vec3 grBb_Route_803B83E0 = { 0.0f, 1.0f, 0.0f };

#define RE_ENTRY (&((RouteEntry*) gp->u.car.car_info)[i])
void grBigBlueRoute_8020CD20(Ground_GObj* gobj)
{
    HSD_JObj* jobj;
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* root_jobj = gobj->hsd_obj;
    HSD_GObj* fighter;
    int i;
    Vec3 pos;
    Vec3 rot;
    Vec3 fighter_pos;
    UNUSED u8 pad0[4];
    Vec3 c2_road;
    Vec3 c2_air;
    Vec3 c2_road_rot;
    UNUSED u8 pad1[12];
    Vec3 c3_air;
    Vec3 c3_road;
    Vec3 c3_air_rot;
    UNUSED u8 pad2[12];
    Vec3 c0_tangent;
    Vec3 c0_p1;
    Vec3 c0_p0;
    Vec3 c1_orient;
    Vec3 c1_side;
    Vec3 c1_up;
    Vec3 c1_tangent;
    Vec3 c2_road_tan;
    Vec3 c2_p1;
    Vec3 c2_p0;
    Vec3 c2_orient;
    Vec3 c2_side;
    Vec3 c2_up;
    Vec3 c2_tangent;
    Vec3 c3_orient;
    Vec3 c3_side;
    Vec3 c3_up;
    Vec3 c3_tangent;
    Vec3 c3_road_tan;
    Vec3 c3_p1;
    Vec3 c3_p0;
    f32 t;
    f32 frac;
    UNUSED u8 pad3[20];

    fighter = Ground_801C57A4();
    if (fighter != NULL) {
        ftLib_80086644(fighter, &fighter_pos);
    } else {
        return;
    }

    if (root_jobj == NULL) {
        return;
    }
    if (root_jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = root_jobj->child;
    }
    if (jobj == NULL) {
        return;
    }

    i = 0;
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
                splGetSplinePoint(&c0_p0, gp->u.car.xD0, t);
                splGetSplinePoint(&c0_p1, gp->u.car.xD4, t);
                lbShadow_8000E9F0(&c0_tangent, gp->u.car.xD0, t);
                lbVector_Diff(&c0_p1, &c0_p0, &pos);
                pos.x *= frac;
                pos.y *= frac;
                pos.z *= frac;
                lbVector_Add(&pos, &c0_p0);
                rot.x = -atan2f(c0_tangent.y, c0_tangent.x);
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
                c1_up = grBb_Route_803B83E0;
                splGetSplinePoint(&pos, gp->u.car.xCC, t);
                lbShadow_8000E9F0(&c1_tangent, gp->u.car.xCC, t);
                grBigBlueRoute_8020DD64(&c1_tangent);
                PSVECCrossProduct(&c1_up, &c1_tangent, &c1_side);
                lbVector_RotateAboutUnitAxis(&c1_side, &c1_tangent, angle);
                grBigBlueRoute_8020DD64(&c1_side);
                PSVECCrossProduct(&c1_tangent, &c1_side, &c1_up);
                grBigBlueRoute_8020DD64(&c1_up);
                Ground_801C5AEC(&c1_orient, &c1_tangent, &c1_side, &c1_up);
                rot = c1_orient;
                {
                    f32 s = 45.0f * Ground_801C0498();
                    c1_up.x *= s;
                    c1_up.y *= s;
                    c1_up.z *= s;
                }
                lbVector_Add(&pos, &c1_up);

                if (RE_ENTRY->x14 > 0.967f) {
                    RE_ENTRY->flags.b2_5 = 3;
                    RE_ENTRY->x4 = 0.0f;
                    RE_ENTRY->xC = 0.5f;
                    RE_ENTRY->x10 = HSD_Randf();
                    RE_ENTRY->x24 = RE_ENTRY->x14;
                    RE_ENTRY->flags.b6 = 0;
                    if (RE_ENTRY->flags.b1) {
                        ((UnkFlagStruct*) &gp->gv.bigblue.x0)->b1 = 0;
                    }
                }
                break;
            }
            case 2: {
                f32 t;
                f32 prog;
                f32 frac;
                f32 angle;

                prog = ((t = RE_ENTRY->x4) - RE_ENTRY->x24) /
                       (1.0f - RE_ENTRY->x24);
                frac = ((1.0f - prog) * (RE_ENTRY->xC - 0.5f)) + 0.5f;
                splGetSplinePoint(&c2_p0, gp->u.car.xD0, t);
                splGetSplinePoint(&c2_p1, gp->u.car.xD4, t);
                lbShadow_8000E9F0(&c2_road_tan, gp->u.car.xD0, t);
                lbVector_Diff(&c2_p1, &c2_p0, &c2_road);
                c2_road.x *= frac;
                c2_road.y *= frac;
                c2_road.z *= frac;
                lbVector_Add(&c2_road, &c2_p0);
                c2_road_rot.x = -atan2f(c2_road_tan.y, c2_road_tan.x);
                c2_road_rot.y = 1.5707964f;
                c2_road_rot.z = 0.0f;

                t = RE_ENTRY->x14;
                angle = RE_ENTRY->x1C;
                c2_up = grBb_Route_803B83E0;
                splGetSplinePoint(&c2_air, gp->u.car.xCC, t);
                lbShadow_8000E9F0(&c2_tangent, gp->u.car.xCC, t);
                grBigBlueRoute_8020DD64(&c2_tangent);
                PSVECCrossProduct(&c2_up, &c2_tangent, &c2_side);
                lbVector_RotateAboutUnitAxis(&c2_side, &c2_tangent, angle);
                grBigBlueRoute_8020DD64(&c2_side);
                PSVECCrossProduct(&c2_tangent, &c2_side, &c2_up);
                grBigBlueRoute_8020DD64(&c2_up);
                Ground_801C5AEC(&c2_orient, &c2_tangent, &c2_side, &c2_up);
                {
                    f32 s = 45.0f * Ground_801C0498();
                    c2_up.x *= s;
                    c2_up.y *= s;
                    c2_up.z *= s;
                }
                lbVector_Add(&c2_air, &c2_up);
                lbVector_Diff(&c2_air, &c2_road, &pos);
                pos.x *= prog;
                pos.y *= prog;
                pos.z *= prog;
                lbVector_Add(&pos, &c2_road);
                rot = c2_road_rot;

                if (RE_ENTRY->x4 == 1.0f) {
                    RE_ENTRY->flags.b2_5 = 1;
                }
                break;
            }
            case 3: {
                f32 prog;
                f32 angle;
                f32 road_t;

                (void) t;
                prog = ((t = RE_ENTRY->x14) - RE_ENTRY->x24) /
                       (1.0f - RE_ENTRY->x24);
                angle = (1.0f - prog) * RE_ENTRY->x1C;
                c3_up = grBb_Route_803B83E0;
                splGetSplinePoint(&c3_air, gp->u.car.xCC, t);
                lbShadow_8000E9F0(&c3_tangent, gp->u.car.xCC, t);
                grBigBlueRoute_8020DD64(&c3_tangent);
                PSVECCrossProduct(&c3_up, &c3_tangent, &c3_side);
                lbVector_RotateAboutUnitAxis(&c3_side, &c3_tangent, angle);
                grBigBlueRoute_8020DD64(&c3_side);
                PSVECCrossProduct(&c3_tangent, &c3_side, &c3_up);
                grBigBlueRoute_8020DD64(&c3_up);
                Ground_801C5AEC(&c3_orient, &c3_tangent, &c3_side, &c3_up);
                c3_air_rot = c3_orient;
                {
                    f32 s = 45.0f * Ground_801C0498();
                    c3_up.x *= s;
                    c3_up.y *= s;
                    c3_up.z *= s;
                }
                lbVector_Add(&c3_air, &c3_up);

                road_t = RE_ENTRY->x4;
                frac = RE_ENTRY->xC;
                splGetSplinePoint(&c3_p0, gp->u.car.xD0, road_t);
                splGetSplinePoint(&c3_p1, gp->u.car.xD4, road_t);
                lbShadow_8000E9F0(&c3_road_tan, gp->u.car.xD0, road_t);
                lbVector_Diff(&c3_p1, &c3_p0, &c3_road);
                c3_road.x *= frac;
                c3_road.y *= frac;
                c3_road.z *= frac;
                lbVector_Add(&c3_road, &c3_p0);
                atan2f(c3_road_tan.y, c3_road_tan.x);
                lbVector_Diff(&c3_road, &c3_air, &pos);
                pos.x *= prog;
                pos.y *= prog;
                pos.z *= prog;
                lbVector_Add(&pos, &c3_air);
                rot = c3_air_rot;

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
                fighter_pos.z < 260.0f + pos.z && !RE_ENTRY->flags.b1)
            {
                if (!((UnkFlagStruct*) &gp->gv.bigblue.x0)->b1) {
                    ((UnkFlagStruct*) &gp->gv.bigblue.x0)->b1 = 1;
                    Ground_801C53EC(0x77A16);
                }
            }

            if (pos.x - 100.0f < fighter_pos.x &&
                fighter_pos.x < 100.0f + pos.x &&
                pos.z - 100.0f < fighter_pos.z &&
                fighter_pos.z < 100.0f + pos.z)
            {
                if (RE_ENTRY->flags.b1) {
                    if (!((UnkFlagStruct*) &gp->gv.bigblue.x0)->b0) {
                        un_802FD604((s32) grBb_Route_804D6A68->x4C);
                        Ground_801C53EC(0x77A11);
                        ((UnkFlagStruct*) &gp->gv.bigblue.x0)->b0 = 1;
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
                if (((UnkFlagStruct*) &gp->gv.bigblue.x0)->b0) {
                    ((UnkFlagStruct*) &gp->gv.bigblue.x0)->b0 = 0;
                }
            }
        }

        i++;
        jobj = (jobj != NULL) ? (HSD_JObj*) grBigBlueRoute_8020DA9C(
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
    HSD_JObj** arr;
    int i;
    int countdown = 30;
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
            break;
        }

        random_idx = (countdown != 0) ? HSD_Randi(countdown) : 0;

        jobj = HSD_GObjGetHSDObj(gobj);
        HSD_ASSERT(1434, jobj);

        jobj = HSD_JObjGetChild(jobj);

        while (random_idx != 0) {
            HSD_ASSERT(1437, jobj);
            random_idx--;
            jobj = HSD_JObjGetNext(jobj);
        }

        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

        HSD_JObjSetScaleX(jobj, scale);
        HSD_JObjSetScaleY(jobj, scale);
        HSD_JObjSetScaleZ(jobj, scale);

        HSD_JObjReparent(jobj, *arr);
    }

    Ground_801C4A08(gobj);
}

f32 grBigBlueRoute_8020DD64(Vec3* v)
{
    f32 mag = lbVector_Normalize(v);
    f32 x = v->x;

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

    return mag;
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

    if (x < -1140 * Ground_801C0498()) {
        x = -1140 * Ground_801C0498();
    }

    if (y < 20.0f * Ground_801C0498()) {
        y = 20.0f * Ground_801C0498();
    } else if (y > 250 * Ground_801C0498()) {
        y = 250 * Ground_801C0498();
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
