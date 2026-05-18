#include "grzebesroute.h"

#include <platform.h>

#include "baselib/debug.h"
#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/grdisplay.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"
#include "lb/lb_00F9.h"
#include "mp/mplib.h"

#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

typedef struct grZebesRoute_LightData {
    Vec3 player_pos;
    Vec3 spot_pos;
    Vec3 spot_interest;
    Vec3 upper_point_pos;
    Vec3 lower_point_pos;
    f32 pad;
} grZebesRoute_LightData;

typedef struct grZebesRoute_Params {
    int camera_timer;
    int zako_spawn_chance;
} grZebesRoute_Params;

typedef struct grZebesRoute_ParamStore {
    grZebesRoute_Params* params;
    u32 pad;
} grZebesRoute_ParamStore;

const grZebesRoute_LightData grZe_Route_803B83A0 = {
    { 0.0F, 0.0F, 0.0F },     { 0.0F, -30.0F, 50.0F },
    { 0.0F, 680.0F, -20.0F }, { -5.0F, 980.0F, 5.0F },
    { 0.0F, 215.0F, -50.0F }, 0.0F,
};

StageCallbacks grZe_Route_803E5DB0[] = {
    { grZebesRoute_8020B348, grZebesRoute_8020B374, grZebesRoute_8020B37C,
      grZebesRoute_8020B380, 0 },
    { grZebesRoute_8020B3C0, grZebesRoute_8020B424, grZebesRoute_8020B42C,
      grZebesRoute_8020B4D4, 0xC0000000 },
    { grZebesRoute_8020B384, grZebesRoute_8020B3B0, grZebesRoute_8020B3B8,
      grZebesRoute_8020B3BC, 0 },
    { NULL, NULL, NULL, NULL, 0 },
};

char grZe_Route_803E5E00[] = "/GrNZr.dat";

struct {
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
} grZe_Route_803E5E0C = {
    ZEBESROUTE,
    grZe_Route_803E5DB0,
    grZe_Route_803E5E00,
    grZebesRoute_8020B164,
    (void (*)(int)) grZebesRoute_8020B160,
    grZebesRoute_8020B1D4,
    grZebesRoute_8020B1F4,
    grZebesRoute_8020B258,
    grZebesRoute_8020B854,
    grZebesRoute_8020B85C,
    1,
    NULL,
    0,
    "%s:%d: couldn t get gobj(id=%d)\n",
};

char grZe_Route_803E5E64[] = "grzebesroute.c";

SDATA char grZe_Route_804D4840[] = "gobj";
SDATA char grZe_Route_804D4848[] = "0";

grZebesRoute_ParamStore grZe_Route_804D6A60;

const f32 grZe_Route_804DB918 = -50.0F;
const f32 grZe_Route_804DB91C = 0.0F;
const GXColor grZe_Route_804DB920 = { 0xFF, 0xFF, 0xCC, 0xFF };
const GXColor grZe_Route_804DB924 = { 0xFD, 0xFD, 0xBF, 0xFF };
const GXColor grZe_Route_804DB928 = { 0x00, 0x00, 0xF7, 0xFF };
const f32 grZe_Route_804DB92C = 600.0F;
const f32 grZe_Route_804DB930 = 1000.0F;
const f32 grZe_Route_804DB934 = 400.0F;
const f32 grZe_Route_804DB938 = 45.0F;
const f32 grZe_Route_804DB93C = 0.99F;
const f32 grZe_Route_804DB940 = 500.0F;
const f32 grZe_Route_804DB944 = 0.03F;

void grZebesRoute_8020B160(bool arg) {}

/// #grZebesRoute_8020B164
void grZebesRoute_8020B164(void)
{
    grZe_Route_804D6A60.params = Ground_801C49F8();
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 1;
    grZebesRoute_8020B260(0);
    grZebesRoute_8020B260(1);
    grZebesRoute_8020B260(2);
    Ground_801C39C0();
    Ground_801C3BB4();
}

void grZebesRoute_8020B1D4(void)
{
    grZebesRoute_8020B548();
}

void grZebesRoute_8020B1F4(void)
{
    int val;
    grZakoGenerator_801CAE04(NULL);
    val = grZe_Route_804D6A60.params->zako_spawn_chance;
    if (val != 0) {
        val = HSD_Randi(grZe_Route_804D6A60.params->zako_spawn_chance);
    } else {
        val = 0;
    }
    if (val == 0) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grZebesRoute_8020B258(void)
{
    return false;
}

HSD_GObj* grZebesRoute_8020B260(int gobj_id)
{
    HSD_GObj* gobj;
    StageCallbacks* callbacks = &grZe_Route_803E5DB0[gobj_id];

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
        OSReport(grZe_Route_803E5E0C.fmt, grZe_Route_803E5E64, 0xC5, gobj_id);
    }

    return gobj;
}

void grZebesRoute_8020B348(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebesRoute_8020B374(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B37C(Ground_GObj* arg) {}

void grZebesRoute_8020B380(Ground_GObj* arg) {}

void grZebesRoute_8020B384(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grZebesRoute_8020B3B0(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B3B8(Ground_GObj* arg) {}

void grZebesRoute_8020B3BC(Ground_GObj* arg) {}

void grZebesRoute_8020B3C0(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    mpJointSetCb1(1, gp, (mpLib_Callback) fn_8020B4D8);
    gp->gv.zebes2.xC4 = (s16) grZe_Route_804D6A60.params->camera_timer;
}

bool grZebesRoute_8020B424(Ground_GObj* arg)
{
    return false;
}

void grZebesRoute_8020B42C(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    Vec3 pos = grZe_Route_803B83A0.player_pos;
    HSD_GObj* fighter;
    s32 timer;

    fighter = Ground_801C57A4();
    if (fighter != NULL) {
        ftLib_80086644(fighter, &pos);
        if (pos.y < grZe_Route_804DB918) {
            pos.y = grZe_Route_804DB918;
        }
        pos.x = grZe_Route_804DB91C;
        Ground_801C38BC(pos.x, pos.y);
    }

    timer = *(s16*) &gp->gv.zebes2.xC4;
    if (timer > 0) {
        gp->gv.zebes2.xC4 = timer - 1;
    } else {
        Camera_80030E44(1, NULL);
    }

    lb_800115F4();
}

void grZebesRoute_8020B4D4(Ground_GObj* arg) {}

void fn_8020B4D8(Ground* gp, s32 arg1, CollData* coll, s32 arg3,
                 mpLib_GroundEnum kind, f32 arg5)
{
    PAD_STACK(16);
    if ((s32) coll->x34_flags.b1234 == 1) {
        if (Ground_801C57A4() == coll->x0_gobj) {
            if (kind == 1) {
                stage_info.flags |= 0x10;
            }
        }
    }
}

/// #grZebesRoute_8020B548
void grZebesRoute_8020B548(void)
{
    HSD_GObj* light_gobj = HSD_GObjGXLinkHead[4];
    HSD_LObj* first_lobj;
    HSD_LObj* lobj;
    f32 scale;
    f32 spot_ref_dist;
    f32 upper_ref_dist;
    f32 lower_ref_dist;
    f32 split_y;
    s32 i;

    if (light_gobj == NULL) {
        __assert(grZe_Route_803E5E64, 0x169U, grZe_Route_804D4840);
    }

    first_lobj = light_gobj->hsd_obj;
    scale = Ground_801C0498();
    lobj = HSD_LObjGetNext(first_lobj);
    spot_ref_dist = grZe_Route_804DB92C * scale;
    upper_ref_dist = grZe_Route_804DB930 * scale;
    lower_ref_dist = grZe_Route_804DB934 * scale;
    split_y = grZe_Route_804DB940;

    i = 0;
    while (i < 3 && lobj != NULL) {
        Vec3 current_pos;
        u32 light_type;

        if (!HSD_LObjGetPosition(lobj, &current_pos)) {
            __assert(grZe_Route_803E5E64, 0x174U, grZe_Route_804D4848);
        }

        light_type = lobj->flags & LOBJ_TYPE_MASK;
        if (light_type == LOBJ_SPOT) {
            GXColor color;
            Vec3 pos = grZe_Route_803B83A0.spot_pos;
            Vec3 interest = grZe_Route_803B83A0.spot_interest;

            color = grZe_Route_804DB920;
            HSD_LObjSetColor(lobj, color);
            pos.x *= scale;
            pos.y *= scale;
            pos.z *= scale;
            HSD_LObjSetPosition(lobj, &pos);
            interest.x *= scale;
            interest.y *= scale;
            interest.z *= scale;
            HSD_LObjSetInterest(lobj, &interest);
            HSD_LObjSetSpot(lobj, grZe_Route_804DB938, 3);
            HSD_LObjSetDistAttn(lobj, spot_ref_dist, grZe_Route_804DB93C, 3);
        } else if (light_type == LOBJ_POINT && current_pos.y > split_y) {
            GXColor color;
            Vec3 pos = grZe_Route_803B83A0.upper_point_pos;

            color = grZe_Route_804DB924;
            HSD_LObjSetColor(lobj, color);
            pos.x *= scale;
            pos.y *= scale;
            pos.z *= scale;
            HSD_LObjSetPosition(lobj, &pos);
            HSD_LObjSetDistAttn(lobj, upper_ref_dist, grZe_Route_804DB944, 3);
        } else if (light_type == LOBJ_POINT && current_pos.y < split_y) {
            GXColor color;
            Vec3 pos = grZe_Route_803B83A0.lower_point_pos;
            int pad[3];

            color = grZe_Route_804DB928;
            HSD_LObjSetColor(lobj, color);
            pos.x *= scale;
            pos.y *= scale;
            pos.z *= scale;
            HSD_LObjSetPosition(lobj, &pos);
            HSD_LObjSetDistAttn(lobj, lower_ref_dist, grZe_Route_804DB944, 3);
        }

        i++;
        lobj = HSD_LObjGetNext(lobj);
    }
}

DynamicsDesc* grZebesRoute_8020B854(enum_t arg)
{
    return false;
}

bool grZebesRoute_8020B85C(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
