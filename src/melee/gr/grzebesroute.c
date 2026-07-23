#include "grzebesroute.h"

#include "ground.h"
#include "grzakogenerator.h"
#include "inlines.h"
#include "placeholder.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "lb/lbspdisplay.h"
#include "mp/mplib.h"

#include <dolphin/mtx.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjproc.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

struct grZebesRoute_YakumonoParam {
    int camera_timer;
    int zako_spawn_chance;
};

/* 20B260 */ static Ground_GObj* grZebesRoute_8020B260(int);
/* 20B4D8 */ static void fn_8020B4D8(void* user_data, int joint_id,
                                     CollData* coll, int coll_x50,
                                     mpLib_GroundEnum ground_kind,
                                     float delta_y);

static struct grZebesRoute_LightData const grZe_Route_803B83A0 = {
    // clang-format off
    { 0.0f,   0.0f,   0.0f }, {  0.0f, -30.0f, 50.0f },
    { 0.0f, 680.0f, -20.0f }, { -5.0f, 980.0f,  5.0f },
    { 0.0f, 215.0f, -50.0f },
}; // clang-format on

StageCallbacks grZe_Route_StageCallbacks[] = {
    { grZebesRoute_8020B348, grZebesRoute_8020B374, grZebesRoute_8020B37C,
      grZebesRoute_8020B380, 0 },
    { grZebesRoute_8020B3C0, grZebesRoute_8020B424, grZebesRoute_8020B42C,
      grZebesRoute_8020B4D4, 0xC0000000 },
    { grZebesRoute_8020B384, grZebesRoute_8020B3B0, grZebesRoute_8020B3B8,
      grZebesRoute_8020B3BC, 0 },
    { NULL, NULL, NULL, NULL, 0 },
};

StageData grZe_Route_803E5E0C = {
    ZEBESROUTE,
    grZe_Route_StageCallbacks,
    "/GrNZr.dat",
    grZebesRoute_8020B164,
    grZebesRoute_8020B160,
    grZebesRoute_8020B1D4,
    grZebesRoute_8020B1F4,
    grZebesRoute_8020B258,
    grZebesRoute_8020B854,
    grZebesRoute_8020B85C,
    1,
    NULL,
    0,
};

static struct grZebesRoute_YakumonoParam* yakumono_param;

void grZebesRoute_8020B160(bool arg) {}

void grZebesRoute_8020B164(void)
{
    yakumono_param = Ground_GetYakumonoParam();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;
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
    val = yakumono_param->zako_spawn_chance;
    if (val != 0) {
        val = HSD_Randi(yakumono_param->zako_spawn_chance);
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

Ground_GObj* grZebesRoute_8020B260(int gobj_id)
{
    Ground_GObj* gobj;
    StageCallbacks* callbacks = &grZe_Route_StageCallbacks[gobj_id];
    gobj = Ground_GetStageGObj(gobj_id);

    if (gobj != NULL) {
        Ground_SetupStageCallbacks(gobj, callbacks);
    } else {
        OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 197, gobj_id);
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
    mpJointSetCb1(1, gp, fn_8020B4D8);
    gp->u.zebes2.xC4 = yakumono_param->camera_timer;
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
        if (pos.y < -50.0f) {
            pos.y = -50.0f;
        }
        pos.x = 0.0f;
        Ground_801C38BC(pos.x, pos.y);
    }

    timer = *(s16*) &gp->u.zebes2.xC4;
    if (timer > 0) {
        gp->u.zebes2.xC4 = timer - 1;
    } else {
        Camera_80030E44(1, NULL);
    }

    lb_800115F4();
}

void grZebesRoute_8020B4D4(Ground_GObj* arg) {}

/// @copydoc mpLib_JointCollisionCallback
void fn_8020B4D8(void* user_data, int joint_id, CollData* coll, int coll_x50,
                 mpLib_GroundEnum ground_kind, float delta_y)
{
    Ground* gp = user_data;
    PAD_STACK(8);
    if ((s32) coll->x34_flags.b1234 == 1) {
        if (Ground_801C57A4() == coll->x0_gobj) {
            if (ground_kind == 1) {
                stage_info.flags |= 0x10;
            }
        }
    }
}

/// @todo Useless wrapper
inline HSD_LObj* HSD_LObjGetNext_padstack(HSD_LObj* arg0)
{
    return HSD_LObjGetNext(arg0);
}

/// @todo ::HSD_LObjGetType
inline int HSD_LObjGetType_padstack(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

void grZebesRoute_8020B548(void)
{
    HSD_GObj* gobj = HSD_GObjGXLinkHead[4];
    HSD_ASSERT(361, gobj);
    {
        HSD_LObj* first_lobj = GET_LOBJ(gobj);
        float scale = Ground_801C0498();
        HSD_LObj* lobj = HSD_LObjGetNext(first_lobj);
        float spot_ref_dist = 600.0f * scale;
        float upper_ref_dist = 1000.0f * scale;
        float lower_ref_dist = 400.0f * scale;
        float split_y = 500.0f;
        int i;

        for (i = 0; i < 3 && lobj != NULL;
             i++, lobj = HSD_LObjGetNext_padstack(lobj))
        {
            Vec3 current_pos;
            u32 light_type;

            if (!HSD_LObjGetPosition(lobj, &current_pos)) {
                HSD_ASSERT(372, 0);
            }

            light_type = HSD_LObjGetType_padstack(lobj);
            if (light_type == LOBJ_SPOT) {
                GXColor color = { 0xFF, 0xFF, 0xCC, 0xFF };
                Vec3 pos = grZe_Route_803B83A0.spot_pos;
                Vec3 interest = grZe_Route_803B83A0.spot_interest;

                HSD_LObjSetColor(lobj, color);
                pos.x *= scale;
                pos.y *= scale;
                pos.z *= scale;
                HSD_LObjSetPosition(lobj, &pos);
                interest.x *= scale;
                interest.y *= scale;
                interest.z *= scale;
                HSD_LObjSetInterest(lobj, &interest);
                HSD_LObjSetSpot(lobj, 45.0f, 3);
                HSD_LObjSetDistAttn(lobj, spot_ref_dist, 0.99f, 3);
            } else if (light_type == LOBJ_POINT && current_pos.y > split_y) {
                GXColor color = { 0xFD, 0xFD, 0xBF, 0xFF };
                Vec3 pos = grZe_Route_803B83A0.upper_point_pos;

                HSD_LObjSetColor(lobj, color);
                pos.x *= scale;
                pos.y *= scale;
                pos.z *= scale;
                HSD_LObjSetPosition(lobj, &pos);
                HSD_LObjSetDistAttn(lobj, upper_ref_dist, 0.03f, 3);
            } else if (light_type == LOBJ_POINT && current_pos.y < split_y) {
                GXColor color = { 0x00, 0x00, 0xF7, 0xFF };
                Vec3 pos = grZe_Route_803B83A0.lower_point_pos;

                HSD_LObjSetColor(lobj, color);
                pos.x *= scale;
                pos.y *= scale;
                pos.z *= scale;
                HSD_LObjSetPosition(lobj, &pos);
                HSD_LObjSetDistAttn(lobj, lower_ref_dist, 0.03f, 3);
            }
        }
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
