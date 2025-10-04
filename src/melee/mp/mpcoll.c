#include "mp/mpcoll.h"

#include "math.h"
#include "platform.h"
#include "stdbool.h"

#include <placeholder.h>

#include "db/db.h"
#include "ft/ftlib.h"

#include "ftCommon/forward.h"

#include "gr/grdynamicattr.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include "mp/forward.h"

#include "mp/mplib.h"

#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <MSL/trigf.h>

static bool mpColl_804D649C;
static bool (*mpColl_804D64A0)(Fighter_GObj*, int);
static Fighter_GObj* mpColl_804D64A4;
static Event mpColl_804D64A8;
int mpColl_804D64AC;

/// @todo float order hack
const float mpColl_804D7F9C = -F32_MAX;
const float mpColl_804D7FA0 = F32_MAX;
const float flt_804D7FF8 = 5.0f;
const f64 flt_804D8000 = -0.75;
const f64 flt_804D8008 = 0.75;
const float flt_804D8010 = -3.0f;

/// @todo float order hack
const float flt_804D7FD8 = 6.0f;

/// @todo This is the same as #MPCOLL_RIGHTWALL, etc. Pick a naming convention.
#define Collide_LeftWallPush 0x1
#define Collide_LeftWallHug 0x20
#define Collide_LeftWallMask 0x3F
#define Collide_RightWallPush 0x40
#define Collide_RightWallHug 0x800
#define Collide_RightWallMask 0xFC0
#define Collide_CeilingPush 0x2000
#define Collide_CeilingHug 0x4000
#define Collide_FloorPush 0x8000
#define Collide_FloorHug 0x10000
#define Collide_LeftEdge 0x100000
#define Collide_RightEdge 0x200000
#define Collide_Edge 0x800000
#define Collide_LeftLedgeGrab 0x1000000
#define Collide_RightLedgeGrab 0x2000000
#define Collide_LeftLedgeSlip 0x10000000
#define Collide_RightLedgeSlip 0x20000000

#define CollisionFlagAir_StayAirborne 0x1
#define CollisionFlagAir_PlatformPassCallback 0x2
#define CollisionFlagAir_CanGrabLedge 0x4

// 80041C78 https://decomp.me/scratch/V6eYQ
void mpColl_80041C78(void)
{
    mpColl_804D64A0 = NULL;
    mpColl_804D64A4 = NULL;
    mpColl_804D64A8 = 0;
}

// 80041C8C https://decomp.me/scratch/VvSaI
void mpCollPrev(CollData* cd)
{
    u8 _[8];

    mpColl_804D64A0 = NULL;
    mpColl_804D64A4 = NULL;
    if (g_debugLevel >= 3) {
        if (!(cd->cur_pos.x < 45000.0F) || !(cd->cur_pos.x > -45000.0F) ||
            !(cd->cur_pos.y < 45000.0F) || !(cd->cur_pos.y > -45000.0F))
        {
            if (ftLib_80086960(cd->x0_gobj)) {
                OSReport(
                    "%s:%d: Error: mpCollPrev() pos(%f,%f) player=%d ms=%d\n",
                    "mpcoll.c", 203, cd->cur_pos.x, cd->cur_pos.y,
                    ftLib_80086BE0(cd->x0_gobj), ftLib_800874BC(cd->x0_gobj));
            } else {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) gobj_id=%d\n",
                         "mpcoll.c", 212, cd->x0_gobj->classifier,
                         cd->cur_pos.x, cd->cur_pos.y);
                if (cd->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(cd->x0_gobj));
                }
            }
            HSD_ASSERT(228, 0);
        }
    }
    cd->x28_vec = cd->cur_pos;
}

// 80041DD0 https://decomp.me/scratch/1KPLe
inline void clamp_above(float* value, float min)
{
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below(float* value, float max)
{
    if (*value > max) {
        *value = max;
    }
}

void mpColl_80041DD0(CollData* cd, u32 flags)
{
    float left, bottom, right, top;

    left = cd->xA4_ecbCurrCorrect.left.x + cd->cur_pos.x;
    clamp_below(&left, cd->xC4_ecb.left.x + cd->cur_pos_correct.x);

    right = cd->xA4_ecbCurrCorrect.right.x + cd->cur_pos.x;
    clamp_above(&right, cd->xC4_ecb.right.x + cd->cur_pos_correct.x);

    bottom = cd->xA4_ecbCurrCorrect.bottom.y + cd->cur_pos.y;
    clamp_below(&bottom, cd->xC4_ecb.bottom.y + cd->cur_pos_correct.y);

    top = cd->xA4_ecbCurrCorrect.top.y + cd->cur_pos.y;
    clamp_above(&top, cd->xC4_ecb.top.y + cd->cur_pos_correct.y);

    if (flags & 0b100) {
        float x54 = cd->ledge_snap_x;
        float tmp = 0.5f * cd->ledge_snap_height;
        float offset;

        right += x54;
        left -= x54;

        clamp_below(&bottom, cd->ledge_snap_y - tmp + cd->cur_pos.y);
        clamp_below(&bottom, cd->ledge_snap_y - tmp + cd->cur_pos_correct.y);

        offset = cd->ledge_snap_y + tmp;
        clamp_above(&top, cd->cur_pos.y + offset);
        clamp_above(&top, cd->cur_pos_correct.y + offset);
    }

    mpLib_800588D0(left, bottom, right, top);
}

// 80041EE4 https://decomp.me/scratch/j2TXK
// CollDataInit
void mpColl_80041EE4(CollData* cd)
{
    cd->x0_gobj = NULL;
    cd->x34_flags.b0 = 1;
    cd->x34_flags.b6 = 0;
    cd->x34_flags.b7 = 0;
    cd->x35_flags.b0 = 1;
    cd->x34_flags.b1234 = 0;
    cd->env_flags = 0;
    cd->x130_flags = 0;
    cd->cur_pos_correct = cd->cur_pos;
    cd->prev_pos = cd->cur_pos;
    cd->x28_vec = cd->cur_pos;
    cd->x3C = -1;
    cd->ledge_id_unk0 = -1;
    cd->ledge_id_unk1 = -1;
    cd->floor.index = -1;
    cd->floor.unk = 0;
    cd->floor.normal.x = 0.0f;
    cd->floor.normal.y = 1.0f;
    cd->floor.normal.z = 0.0f;
    cd->ceiling.index = -1;
    cd->ceiling.unk = 0;
    cd->ceiling.normal.x = 0.0f;
    cd->ceiling.normal.y = -1.0f;
    cd->ceiling.normal.z = 0.0f;
    cd->left_wall.index = -1;
    cd->left_wall.unk = 0;
    cd->left_wall.normal.x = 0.0f;
    cd->left_wall.normal.y = 1.0f;
    cd->left_wall.normal.z = 0.0f;
    cd->right_wall.index = -1;
    cd->right_wall.unk = 0;
    cd->right_wall.normal.x = 0.0f;
    cd->right_wall.normal.y = -1.0f;
    cd->right_wall.normal.z = 0.0f;
    cd->x38 = mpColl_804D64AC;
    cd->x50 = 0.0f;
    cd->x48 = -1;
    cd->x4C = -1;
    cd->ledge_snap_x = 0.0f;
    cd->ledge_snap_y = 0.0f;
    cd->ledge_snap_height = 0.0f;
    memzero(&cd->xA4_ecbCurrCorrect, sizeof(ftECB));
    memzero(&cd->xC4_ecb, sizeof(ftECB));
    memzero(&cd->xE4_ecb, sizeof(ftECB));
    memzero(&cd->x104, 0x2C);
    memzero(&cd->x84_ecb, sizeof(ftECB));
    memzero(&cd->x64_ecb, sizeof(ftECB));
}

// 80042078 https://decomp.me/scratch/hM7h8
void mpColl_80042078(CollData* cd, HSD_GObj* gobj, HSD_JObj* arg1,
                     HSD_JObj* arg2, HSD_JObj* arg3, HSD_JObj* arg4,
                     HSD_JObj* arg5, HSD_JObj* arg6, HSD_JObj* arg7,
                     float arg9)
{
    cd->x0_gobj = gobj;
    cd->x104 = 1;
    cd->x108_joint = arg1;
    cd->x10C_joint[0] = arg2;
    cd->x10C_joint[1] = arg3;
    cd->x10C_joint[2] = arg4;
    cd->x10C_joint[3] = arg5;
    cd->x10C_joint[4] = arg6;
    cd->x10C_joint[5] = arg7;
    cd->x124 = arg9;
    cd->x128 = 10.0f;
    cd->x12C = 10.0f;
    if (cd->x34_flags.b0) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 8.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 4.0f;
        cd->xA4_ecbCurrCorrect.right.y = 4.0f;
        cd->xA4_ecbCurrCorrect.left.x = -4.0f;
        cd->xA4_ecbCurrCorrect.left.y = 4.0f;
        cd->xA4_ecbCurrCorrect = cd->xA4_ecbCurrCorrect;
        cd->xC4_ecb = cd->xA4_ecbCurrCorrect;
        cd->xE4_ecb = cd->xA4_ecbCurrCorrect;
        cd->x64_ecb = cd->xA4_ecbCurrCorrect;
        cd->x84_ecb = cd->xA4_ecbCurrCorrect;
    }
    cd->x36 = -1;
    cd->x50 = 0.0f;
}

// 8004220C https://decomp.me/scratch/nOinn
void mpColl_8004220C(CollData* cd, HSD_GObj* gobj, float arg1, float arg2,
                     float arg3, float arg4)
{
    cd->x0_gobj = gobj;
    cd->x104 = 2;
    cd->x108_f32 = arg1;
    cd->x10C_f32 = arg2;
    cd->x110_f32 = arg3;
    cd->x114_f32 = arg4;
    cd->x118_f32 = 0.0f;
    if (cd->x34_flags.b0) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 8.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 4.0f;
        cd->xA4_ecbCurrCorrect.right.y = 4.0f;
        cd->xA4_ecbCurrCorrect.left.x = -4.0f;
        cd->xA4_ecbCurrCorrect.left.y = 4.0f;
        cd->xC4_ecb = cd->xA4_ecbCurrCorrect;
        cd->xE4_ecb = cd->xA4_ecbCurrCorrect;
        cd->x64_ecb = cd->xA4_ecbCurrCorrect;
        cd->x84_ecb = cd->xA4_ecbCurrCorrect;
    }
    cd->x36 = -1;
}

// 80042374 https://decomp.me/scratch/SgKfv
void mpColl_SetLedgeSnap(CollData* coll, float ledge_snap_x,
                         float ledge_snap_y, float ledge_snap_height)
{
    coll->ledge_snap_x = ledge_snap_x;
    coll->ledge_snap_y = ledge_snap_y;
    coll->ledge_snap_height = ledge_snap_height;
}

// 80042384 https://decomp.me/scratch/P8djI
void mpColl_80042384(CollData* cd)
{
    float tmp, tmp2;

    if (ABS(cd->x84_ecb.top.y - cd->x84_ecb.bottom.y) < 1.0f) {
        cd->x84_ecb.top.y += 1.0f;
        tmp = 0.5f * (cd->x84_ecb.top.y + cd->x84_ecb.bottom.y);
        cd->x84_ecb.left.y = tmp;
        cd->x84_ecb.right.y = tmp;
    }
    if (cd->x84_ecb.top.y < 1.0f) {
        cd->x84_ecb.top.y = 1.0f;
    }
    if (cd->x84_ecb.left.x > -1.0f) {
        cd->x84_ecb.left.x = -1.0f;
    }
    if (cd->x84_ecb.right.x < 1.0f) {
        cd->x84_ecb.right.x = 1.0f;
    }
    if (cd->x84_ecb.top.y < cd->x84_ecb.bottom.y) {
        cd->x84_ecb.top.y = 1.0f + cd->x84_ecb.bottom.y;
    }
    if (cd->x84_ecb.right.y > cd->x84_ecb.top.y ||
        cd->x84_ecb.right.y < cd->x84_ecb.bottom.y)
    {
        tmp = 0.5f * (cd->x84_ecb.top.y + cd->x84_ecb.bottom.y);
        cd->x84_ecb.left.y = tmp;
        cd->x84_ecb.right.y = tmp;
    }
    tmp = cd->x84_ecb.top.y;
    tmp2 = cd->x84_ecb.right.y;
    if (tmp - tmp2 < 0.001f || tmp2 - cd->x84_ecb.bottom.y < 0.001f) {
        cd->x84_ecb.right.y = 0.5f * (tmp + cd->x84_ecb.bottom.y);
    }
    tmp = cd->x84_ecb.top.y;
    tmp2 = cd->x84_ecb.left.y;
    if (tmp - tmp2 < 0.001f || tmp2 - cd->x84_ecb.bottom.y < 0.001f) {
        cd->x84_ecb.left.y = 0.5f * (tmp + cd->x84_ecb.bottom.y);
    }
}

// 800424DC https://decomp.me/scratch/DhzDB
inline void update_min_max(float* min, float* max, float val)
{
    if (*min > val) {
        *min = val;
    } else if (*max < val) {
        *max = val;
    }
}

void mpColl_800424DC(CollData* cd, u32 flags)
{
    Vec3 vec;
    float left_x, bottom_y;
    float right_x, top_y;
    float dx, dy;

    float phi_f1, phi_f2;
    float mid_y;
    float tmpval;

    if (cd->x130_flags & 0b100000) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 0.0f;
        cd->xA4_ecbCurrCorrect.right.y = 0.0f;
        cd->xA4_ecbCurrCorrect.left.x = 0.0f;
        cd->xA4_ecbCurrCorrect.left.y = 0.0f;
        cd->x130_flags &= ~0b100000;
    }
    cd->xE4_ecb = cd->xA4_ecbCurrCorrect;

    // Loop through all collision data joints,
    // expanding the ECB to contain them all
    {
        float temp_x = cd->cur_pos.x;
        float temp_y = cd->cur_pos.y;
        lb_8000B1CC(cd->x10C_joint[0], NULL, &vec);
        left_x = right_x = vec.x - temp_x;
        bottom_y = top_y = vec.y - temp_y;

#define EXPAND_ECB_FOR(joint)                                                 \
    lb_8000B1CC(joint, NULL, &vec);                                           \
    dx = vec.x - temp_x;                                                      \
    dy = vec.y - temp_y;                                                      \
    update_min_max(&left_x, &right_x, dx);                                    \
    update_min_max(&bottom_y, &top_y, dy);

        EXPAND_ECB_FOR(cd->x10C_joint[1]);
        EXPAND_ECB_FOR(cd->x10C_joint[2]);
        EXPAND_ECB_FOR(cd->x10C_joint[3]);
        EXPAND_ECB_FOR(cd->x10C_joint[4]);
        EXPAND_ECB_FOR(cd->x10C_joint[5]);
    }

    if (!(flags & 0b100)) {
        left_x -= 2.0f;
        right_x += 2.0f;
        bottom_y -= 2.0f;
        top_y += 2.0f;
    }

    phi_f1 = 4.0f > cd->x12C ? 4.0f : cd->x12C;
    phi_f2 = ABS(right_x - left_x);

    if (phi_f2 < phi_f1) {
        right_x = 0.5f * phi_f2;
        left_x = -right_x;
    }

    phi_f1 = 4.0f > cd->x128 ? 4.0f : cd->x128;
    phi_f2 = ABS(top_y - bottom_y);

    if (phi_f2 < phi_f1) {
        tmpval = 0.5f * phi_f2;
        mid_y = 0.5f * (top_y + bottom_y);
        top_y = mid_y + tmpval;
        bottom_y = mid_y - tmpval;
    }

    if (flags & 0b1000) {
        left_x = -1.0f;
        right_x = +1.0f;
    } else {
        right_x = right_x < +2.0f ? +2.0f : right_x;
        left_x = left_x > -2.0f ? -2.0f : left_x;
    }

    if (flags & 1) {
        bottom_y = 0.0f;
        if (flags & 0b10000) {
            top_y = 2.0f;
        }
    } else {
        if (bottom_y < 0.0f) {
            bottom_y = 0.0f;
        }
        if (flags & 0b10000) {
            mid_y = 0.5f * (bottom_y + top_y);
            bottom_y = mid_y - 1.0f;
            top_y = mid_y + 1.0f;
            if (bottom_y < 0.0f) {
                bottom_y = 0.0f;
                top_y = 2.0f;
            }
        }
    }

    cd->x84_ecb.top.x = 0.0f;
    cd->x84_ecb.top.y = top_y;
    cd->x84_ecb.bottom.x = 0.0f;
    cd->x84_ecb.bottom.y = bottom_y;
    cd->x84_ecb.right.x = right_x;
    cd->x84_ecb.right.y = cd->x124 + 0.5f * (bottom_y + top_y);
    cd->x84_ecb.left.x = left_x;
    cd->x84_ecb.left.y = cd->x124 + 0.5f * (bottom_y + top_y);
    cd->x34_flags.b0 = 0;
}

// 8004293C https://decomp.me/scratch/H4EUT
inline void update_min_max_2(float* min, float* max, float val)
{
    if (*max < val) {
        *max = val;
    } else if (*min > val) {
        *min = val;
    }
}

inline void clamp_above_2(float* value, float min)
{
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below_2(float* value, float max)
{
    if (*value > max) {
        *value = max;
    }
}

void mpColl_8004293C(CollData* cd)
{
    float angle;
    float sin;
    float cos;

    float midpoint_x;
    float midpoint_y;

    float orig_top_y;
    float orig_bottom_y;
    float orig_right_x;
    float orig_left_x;

    float top_y;
    float bottom_y;
    float right_x;
    float left_x;

    float rot_top_x;
    float rot_top_y;
    float rot_bot_x;
    float rot_bot_y;
    float rot_right_x;
    float rot_right_y;
    float rot_left_y;
    float rot_left_x;

    angle = cd->x118_f32;
    if (cd->x130_flags & 0x20) {
        cd->xA4_ecbCurrCorrect.top.x = 0.0f;
        cd->xA4_ecbCurrCorrect.top.y = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        cd->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        cd->xA4_ecbCurrCorrect.right.x = 0.0f;
        cd->xA4_ecbCurrCorrect.right.y = 0.0f;
        cd->xA4_ecbCurrCorrect.left.x = 0.0f;
        cd->xA4_ecbCurrCorrect.left.y = 0.0f;
        cd->x130_flags &= 0xFFFFFFDF;
    }
    cd->xE4_ecb = cd->xA4_ecbCurrCorrect;

    bottom_y = -cd->x10C_f32;
    top_y = cd->x108_f32;

    if (cd->x36 == 1) {
        right_x = cd->x110_f32;
        left_x = -cd->x114_f32;
    } else {
        right_x = cd->x114_f32;
        left_x = -cd->x110_f32;
    }

    if (angle != 0.0f) {
        sin = sinf(angle);
        cos = cosf(angle);

        orig_top_y = top_y;
        orig_bottom_y = bottom_y;
        orig_right_x = right_x;
        orig_left_x = left_x;

        // fake
        rot_right_y = 0.5f * (orig_right_x + orig_left_x);
        midpoint_x = rot_right_y;

        top_y = right_x = bottom_y = left_x = 0.0f;

        rot_top_x = -orig_top_y * sin;
        rot_top_y = orig_top_y * cos;
        update_min_max_2(&left_x, &right_x, rot_top_x);
        update_min_max_2(&bottom_y, &top_y, rot_top_y);

        rot_bot_x = -orig_bottom_y * sin;
        rot_bot_y = orig_bottom_y * cos;
        update_min_max_2(&left_x, &right_x, rot_bot_x);
        update_min_max_2(&bottom_y, &top_y, rot_bot_y);

        rot_right_x = (orig_right_x * cos) - (midpoint_x * sin);
        rot_right_y = (orig_right_x * sin) + (midpoint_x * cos);
        update_min_max_2(&left_x, &right_x, rot_right_x);
        update_min_max_2(&bottom_y, &top_y, rot_right_y);

        rot_left_x = (orig_left_x * cos) - (midpoint_x * sin);
        rot_left_y = (orig_left_x * sin) + (midpoint_x * cos);
        update_min_max_2(&left_x, &right_x, rot_left_x);
        update_min_max_2(&bottom_y, &top_y, rot_left_y);
    }

    clamp_above_2(&top_y, 0.0f);
    clamp_below_2(&bottom_y, -0.0f);
    clamp_above_2(&right_x, 0.0f);
    clamp_below_2(&left_x, -0.0f);

    if ((top_y - bottom_y) < 3.0f) {
        top_y = 1.5f;
        bottom_y = -top_y;
    }
    if ((right_x - left_x) < 3.0f) {
        right_x = 1.5f;
        left_x = -right_x;
    }

    cd->x84_ecb.top.x = 0.0f;
    cd->x84_ecb.top.y = top_y;
    cd->x84_ecb.bottom.x = 0.0f;
    cd->x84_ecb.bottom.y = bottom_y;

    midpoint_y = 0.5f * (top_y + bottom_y);
    cd->x84_ecb.right.x = right_x;
    cd->x84_ecb.right.y = midpoint_y;
    cd->x84_ecb.left.x = left_x;
    cd->x84_ecb.left.y = midpoint_y;

    cd->x34_flags.b0 = 0;
}

void mpColl_80042C58(CollData* coll, ftCollisionBox* arg1)
{
    if (coll->x130_flags & 0x20) {
        coll->xA4_ecbCurrCorrect.top.x = 0.0f;
        coll->xA4_ecbCurrCorrect.top.y = 0.0f;
        coll->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        coll->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        coll->xA4_ecbCurrCorrect.right.x = 0.0f;
        coll->xA4_ecbCurrCorrect.right.y = 0.0f;
        coll->xA4_ecbCurrCorrect.left.x = 0.0f;
        coll->xA4_ecbCurrCorrect.left.y = 0.0f;
        coll->x130_flags &= 0xFFFFFFDF;
    }
    coll->xE4_ecb = coll->xA4_ecbCurrCorrect;
    coll->x84_ecb.top.x = 0.0f;
    coll->x84_ecb.top.y = arg1->top;
    coll->x84_ecb.bottom.x = 0.0f;
    coll->x84_ecb.bottom.y = arg1->bottom;
    coll->x84_ecb.right.x = arg1->right.x;
    coll->x84_ecb.right.y = arg1->right.y;
    coll->x84_ecb.left.x = arg1->left.x;
    coll->x84_ecb.left.y = arg1->left.y;
    coll->x34_flags.b0 = 0;
}

static inline void mpColl_80042D24_inline(CollData* coll, enum_t i)
{
    float saved_bottom_x;
    float saved_bottom_y;

    if (coll->x130_flags & 0x10) {
        saved_bottom_x = coll->x84_ecb.bottom.x;
        saved_bottom_y = coll->x84_ecb.bottom.y;
    }
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, i);
    } else {
        mpColl_8004293C(coll);
    }
    if (coll->x130_flags & 0x10) {
        coll->x84_ecb.bottom.x = saved_bottom_x;
        coll->x84_ecb.bottom.y = saved_bottom_y;
    }
    mpColl_80042384(coll);
}

// 80042D24 https://decomp.me/scratch/2MnVj
#pragma push
#pragma dont_inline on
void mpColl_80042D24(CollData* coll)
{
    float saved_bottom_x;
    float saved_bottom_y;

    if (coll->x130_flags & 0x10) {
        saved_bottom_x = coll->x84_ecb.bottom.x;
        saved_bottom_y = coll->x84_ecb.bottom.y;
    }
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 6);
    } else {
        mpColl_8004293C(coll);
    }
    if (coll->x130_flags & 0x10) {
        coll->x84_ecb.bottom.x = saved_bottom_x;
        coll->x84_ecb.bottom.y = saved_bottom_y;
    }
    mpColl_80042384(coll);
}
#pragma pop

// 80042DB0 https://decomp.me/scratch/GbMpk
inline void Vec2_Interpolate(float time, Vec2* dest, Vec2* src)
{
    dest->x += time * (src->x - dest->x);
    dest->y += time * (src->y - dest->y);
}

void mpColl_80042DB0(CollData* ecb, float time)
{
    ecb->xC4_ecb = ecb->xA4_ecbCurrCorrect;
    if (ecb->x34_flags.b6) {
        ecb->xA4_ecbCurrCorrect = ecb->x64_ecb;
        ecb->x34_flags.b6 = 0;
    }
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.top, &ecb->x84_ecb.top);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.bottom,
                     &ecb->x84_ecb.bottom);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.left, &ecb->x84_ecb.left);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.right,
                     &ecb->x84_ecb.right);
    if (fpclassify(ecb->xA4_ecbCurrCorrect.top.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.top.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.bottom.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.bottom.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.left.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.left.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.right.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.right.y) == FP_NAN)
    {
        HSD_ASSERTREPORT(1193, 0, "error\n");
    }
}

// 80043268 https://decomp.me/scratch/GNwej
void mpColl_80043268(CollData* coll, s32 arg1, s32 arg2, float arg8)
{
    mpLib_Callback sp1C;
    Ground* sp18;
    s32 temp_r31;

    temp_r31 = mpLib_80056B6C(arg1);
    if (temp_r31 != -1) {
        sp18 = NULL;
        mpLib_800580FC(temp_r31, &sp1C, &sp18);
        if (sp1C != 0) {
            s32 thing;
            if (arg2 == 0) {
                thing = 2;
            } else {
                thing = 1;
            }
            sp1C(sp18, temp_r31, coll, coll->x50, thing, arg8);
        }
    }
}

char dummy_string_data[] = "i<MPCOLL_WALLID_MAX";

static inline void func_80043324_inline2(CollData* coll, s32 arg1, s32 arg2,
                                         float arg8)
{ // see mpColl_80043268
    int dummy = 0;

    mpLib_Callback callback;
    Ground* thing;
    s32 temp_r29;

    temp_r29 = mpLib_80056B6C(arg1);
    if (temp_r29 != -1) {
        thing = NULL;
        mpLib_800581BC(temp_r29, &callback, &thing);

        if (callback != NULL) {
            callback(thing, temp_r29, coll, coll->x50, 0, arg8);
        }
    }
}

static inline void func_80043324_inline(CollData* coll, s32 arg1, s32 arg2,
                                        float arg8)
{
    // inhibit inlining
    mpColl_80043268(coll, arg1, arg2, arg8);
}

void mpCollEnd(CollData* coll, s32 arg1, s32 arg2)
{
    s32 temp_r3;

    u8 temp_r3_2[4];

    if (coll->floor.index != -1) {
        temp_r3 = grDynamicAttr_801CA284(&coll->cur_pos, coll->floor.index);
        if (temp_r3 != 0) {
            coll->floor.unk =
                (coll->floor.unk & 0xFFFFFF00) | (temp_r3 & 0xFF);
        }
    }
    if ((arg1 != 0) || (coll->env_flags & Collide_Edge) ||
        (coll->env_flags & Collide_LeftEdge) ||
        (coll->env_flags & Collide_RightEdge))
    {
        func_80043324_inline(coll, coll->floor.index, arg2,
                             coll->cur_pos.y - coll->prev_pos.y);
    }
    if (coll->env_flags & (Collide_CeilingHug | Collide_CeilingPush)) {
        func_80043324_inline2(coll, coll->ceiling.index, arg2,
                              coll->cur_pos.y - coll->prev_pos.y);
    }
    if (g_debugLevel >= 3) {
        if (!(coll->cur_pos.x < 45000.0f) || !(coll->cur_pos.x > -45000.0f) ||
            !(coll->cur_pos.y < 45000.0f) || !(coll->cur_pos.y > -45000.0f))
        {
            if (ftLib_80086960(coll->x0_gobj)) {
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "ply=%d ms=%d\n",
                         "mpcoll.c", 1350, coll->prev_pos.x, coll->prev_pos.y,
                         coll->cur_pos.x, coll->cur_pos.y,
                         ftLib_80086BE0(coll->x0_gobj),
                         ftLib_800874BC(coll->x0_gobj));
            } else {
                s32 gobjid = coll->x0_gobj->classifier;
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "gobjid=%d\n",
                         "mpcoll.c", 1358, coll->prev_pos.x, coll->prev_pos.y,
                         coll->cur_pos.x, coll->cur_pos.y, gobjid);
                if (coll->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(coll->x0_gobj));
                }
            }
            HSD_ASSERT(1374, 0);
        }
    }
}

#define SOLUTION 0
/// @todo dummy stack in #func_80043324_inline2 breaks this function
void mpColl_80043558(CollData* coll, s32 arg1)
{
#if SOLUTION == 0
    Ground* sp1C;
    mpLib_Callback sp18;
    Ground* sp14;
    mpLib_Callback sp10;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;

    temp_r3 = mpLib_80054C6C(arg1);
    if (temp_r3 == 1) {
        temp_r3_2 = mpLib_80056B6C(arg1);
        if (temp_r3_2 != -1) {
            sp1C = NULL;
            mpLib_800580FC(temp_r3_2, &sp18, &sp1C);
            if (sp18 != NULL) {
                (*sp18)(sp1C, temp_r3_2, coll, coll->x50, 2, 0.0f);
            }
        }
    } else if (temp_r3 == 2) {
        temp_r3_3 = mpLib_80056B6C(arg1);
        if (temp_r3_3 != -1) {
            sp14 = NULL;
            mpLib_800581BC(temp_r3_3, &sp10, &sp14);
            if (sp10 != NULL) {
                (*sp10)(sp14, temp_r3_3, coll, coll->x50, 0, 0.0f);
            }
        }
    }
#elif SOLUTION == 1
    enum_t temp_r3 = mpLib_80054C6C(arg1);

    if (temp_r3 == 1) {
        mpColl_80043268(coll, arg1, 0, 0.0f);
    } else if (temp_r3 == 2) {
        func_80043324_inline2(coll, arg1, 0, 0.0f);
    }
#endif
}
#undef SOLUTION

void mpColl_80043670(CollData* coll)
{
    coll->x130_flags |= 0x20;
}

void mpColl_80043680(CollData* coll, Vec3* arg1)
{
    coll->cur_pos = *arg1;
    coll->cur_pos_correct = coll->cur_pos;
    coll->prev_pos = coll->cur_pos_correct;
    coll->x130_flags |= 0x20;
}

void mpColl_800436D8(CollData* coll, int arg1)
{
    coll->x36 = arg1;
}

static float six(void)
{
    return flt_804D7FD8;
}

#define M_TAU 6.283185307179586
void mpColl_800436E4(CollData* coll, float arg1)
{
    float var_f1;

    var_f1 = arg1;
    if (coll->x104 == 2) {
        if (var_f1 > M_TAU) {
            var_f1 -= M_TAU;
        } else if (var_f1 < -M_TAU) {
            var_f1 += M_TAU;
        }
        coll->x118_f32 = var_f1;
    } else {
        OSReport("not support rotate at JObj type coll\n");
        while (1) {
            ;
        }
    }
}

// 80043754 https://decomp.me/scratch/JEEcj
inline float max_inline(float a, float b)
{
    return (a > b) ? a : b;
}

bool mpColl_80043754(mpColl_Callback arg0, CollData* arg1, u32 arg2)
{
    Vec3 vel;

    u8 _[4];

    float dist_right_x;
    float dist_right_y;
    float x;
    float y;
    float dist_left_x;
    float dist_top_y;
    s32 var_r31;
    s32 var_r30;
    s32 ret;

    lbVector_Diff(&arg1->cur_pos, &arg1->prev_pos, &vel);
    x = ABS(vel.x);
    y = ABS(vel.y);

    dist_left_x = arg1->x84_ecb.left.x - arg1->xA4_ecbCurrCorrect.left.x;
    // if (dist_left_x < 0) dist_left_x = -dist_left_x;
    dist_left_x = ABS(dist_left_x);

    dist_right_x = arg1->x84_ecb.right.x - arg1->xA4_ecbCurrCorrect.right.x;
    if (dist_right_x < 0) {
        dist_right_x = -dist_right_x;
    }

    if (dist_left_x < dist_right_x) {
        dist_left_x = dist_right_x;
    }

    dist_top_y = arg1->x84_ecb.top.y - arg1->xA4_ecbCurrCorrect.top.y;
    // if (dist_top_y < 0) dist_top_y = -dist_top_y;
    dist_top_y = ABS(dist_top_y);

    dist_right_y = arg1->x84_ecb.right.y - arg1->xA4_ecbCurrCorrect.right.y;
    if (dist_right_y < 0) {
        dist_right_y = -dist_right_y;
    }

    if (dist_top_y < dist_right_y) {
        dist_top_y = dist_right_y;
    }

    x = max_inline(x, dist_left_x);
    y = max_inline(y, dist_top_y);
    x = max_inline(x, y);

    if (x > flt_804D7FD8) {                 // 6.0f float order hack
        var_r30 = (s32) (x / flt_804D7FD8); // 6.0f float order hack
        var_r30 = var_r30 + 1;
        vel.x /= var_r30;
        vel.y /= var_r30;
        vel.z /= var_r30;
    } else {
        var_r30 = 1;
    }
    var_r31 = 0;
    arg1->cur_pos = arg1->prev_pos;
    arg1->x34_flags.b5 = 0;
    while ((var_r31 < var_r30) && !arg1->x34_flags.b5) {
        mpColl_80042DB0(arg1, 1.0f / (var_r30 - var_r31));
        arg1->cur_pos_correct = arg1->cur_pos;
        lbVector_Add(&arg1->cur_pos, &vel);
        mpColl_80041DD0(arg1, arg2);
        ret = (*arg0)(arg1, arg2);
        mpLib_80058AA0();
        var_r31 += 1;
        arg1->x38 = mpColl_804D64AC;
    }
    return ret;
}

// 800439FC https://decomp.me/scratch/T1yAJ
void mpColl_800439FC(CollData* arg0)
{
    Vec3 sp10;
    float spC;
    float temp_f3;
    float temp_f4;
    float var_f31;

    var_f31 = arg0->xA4_ecbCurrCorrect.right.x;
    temp_f3 = arg0->cur_pos.x + var_f31;
    temp_f4 = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.right.y;
    if (var_f31 < 0.0f) {
        var_f31 = -var_f31;
    }
    if (mpLib_800501CC((arg0->ceiling.normal.y * var_f31) + temp_f3,
                       -((arg0->ceiling.normal.x * var_f31) - temp_f4),
                       temp_f3, temp_f4, &arg0->x140, NULL, NULL, NULL,
                       arg0->x48, arg0->x4C))
    {
        sp10.x = arg0->x140.x - var_f31;
        sp10.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (mpLib_8004E090(arg0->ceiling.index, (Vec3*) &sp10, &spC,
                           (u32*) &arg0->ceiling.unk,
                           &arg0->ceiling.normal) != -1)
        {
            arg0->cur_pos.y += spC;
            arg0->cur_pos.x = sp10.x;
        }
    }
}

void mpColl_80043ADC(CollData* arg0)
{
    Vec3 sp10;
    float spC;
    float temp_f3;
    float temp_f4;
    float var_f31;

    var_f31 = arg0->xA4_ecbCurrCorrect.left.x;
    temp_f3 = arg0->cur_pos.x + var_f31;
    temp_f4 = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.left.y;
    if (var_f31 < 0.0f) {
        var_f31 = -var_f31;
    }
    if (mpLib_800509B8(-((arg0->ceiling.normal.y * var_f31) - temp_f3),
                       ((arg0->ceiling.normal.x * var_f31) + temp_f4), temp_f3,
                       temp_f4, &arg0->x140, NULL, NULL, NULL, arg0->x48,
                       arg0->x4C))
    {
        sp10.x = arg0->x140.x + var_f31;
        sp10.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (mpLib_8004E090(arg0->ceiling.index, &sp10, &spC,
                           &arg0->ceiling.unk, &arg0->ceiling.normal) != -1)
        {
            arg0->cur_pos.y += spC;
            arg0->cur_pos.x = sp10.x;
        }
    }
}

bool mpColl_80043BBC(CollData* arg0, s32* arg1)
{
    s32 sp10;
    s32 temp_r31;
    float new_var;

    temp_r31 = mpLib_80052700(arg0->floor.index);
    new_var = arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.bottom.x;
    if ((mpLib_800501CC(new_var,
                        arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y,
                        arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.right.x,
                        arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.right.y,
                        NULL, &sp10, NULL, NULL, arg0->x48, arg0->x4C)) &&
        (sp10 != temp_r31))
    {
        *arg1 = sp10;
        return true;
    }
    return false;
}

void mpColl_80043C6C(CollData* arg0, s32 arg1, s32 arg2)
{
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;
    float sp30;
    float temp_f2;
    float temp_f4;
    float var_f31;

    Vec3 sp20;
    s32 sp1C;

    temp_f1 = arg0->xA4_ecbCurrCorrect.right.x;
    if (temp_f1 < 0.0f) {
        var_f31 = -temp_f1;
    } else {
        var_f31 = temp_f1;
    }
    sp20.x = arg0->cur_pos.x + temp_f1;
    temp_f1_2 = arg0->cur_pos.y;
    sp20.y = temp_f1_2 + arg0->xA4_ecbCurrCorrect.right.y;
    if (mpLib_8004E398(arg1, &sp20, 0, 0, 0) != -1) {
        float x = -(arg0->floor.normal.y * var_f31 - sp20.x);
        float y = arg0->floor.normal.x * var_f31 + sp20.y;
        if (mpLib_800501CC(x, y, sp20.x, sp20.y, &arg0->x140, &sp1C, 0, 0,
                           arg0->x48, arg0->x4C))
        {
            sp20.x = arg0->x140.x - var_f31;
            if (arg2 != 0) {
                sp20.y = arg0->cur_pos.y;
            } else {
                sp20.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->cur_pos.y += sp30;
                arg0->cur_pos.x = sp20.x;
            }
        }
    } else {
        mpLib_80054584(arg1, &sp20);
        temp_f4 = 2.0f;
        temp_f2 = sp20.y;
        temp_f1_3 = sp20.x - temp_f4;
        sp20.x = -((temp_f4 * var_f31) - temp_f1_3);
        sp20.y = -((temp_f4 * (arg0->xA4_ecbCurrCorrect.right.y -
                               arg0->xA4_ecbCurrCorrect.bottom.y)) -
                   temp_f2);
        if (mpLib_8004F008(&arg0->x140, 0, 0, 0, temp_f1_3, temp_f2, sp20.x,
                           sp20.y, 0.0F, arg0->x3C, arg0->x48, arg0->x4C, 0,
                           0))
        {
            sp20.x = arg0->x140.x;
            if (arg2 != 0) {
                sp20.y = arg0->cur_pos.y;
            } else {
                sp20.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->cur_pos.y += sp30;
                arg0->cur_pos.x = sp20.x;
            }
        }
    }
}

bool mpColl_80043E90(CollData* coll, s32* arg1)
{
    s32 sp10;
    s32 temp_r31 = mpLib_80052534(coll->floor.index);

    f32 f1 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.bottom.x;
    f32 f2 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.bottom.y;
    f32 f3 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.left.x;
    f32 f4 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.left.y;

    if (mpLib_800509B8(f1, f2, f3, f4, NULL, &sp10, 0, NULL, coll->x48,
                       coll->x4C) &&
        sp10 != temp_r31)
    {
        *arg1 = sp10;
        return true;
    }
    return false;
}

void mpColl_80043F40(CollData* arg0, s32 arg1, s32 arg2)
{
    f32 sp30;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 var_f31;
    Vec3 sp20;
    int sp1C;

    var_f31 = ABS(arg0->xA4_ecbCurrCorrect.left.x);
    sp20.x = arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.left.x;
    sp20.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.left.y;
    if (mpLib_8004E684(arg1, &sp20, NULL, NULL, NULL) != -1) {
        f32 tmp2 = arg0->floor.normal.y * var_f31 + sp20.x;
        f32 tmp = -(arg0->floor.normal.x * var_f31 - sp20.y);
        if (mpLib_800509B8(tmp2, tmp, sp20.x, sp20.y, &arg0->x140, &sp1C, 0,
                           NULL, arg0->x48, arg0->x4C) != 0)
        {
            sp20.x = arg0->x140.x + var_f31;
            if (arg2 != 0) {
                sp20.y = arg0->cur_pos.y;
            } else {
                sp20.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->cur_pos.y += sp30;
                arg0->cur_pos.x = sp20.x;
            }
        }
    } else {
        mpLib_8005484C(arg1, &sp20);
        temp_f2 = sp20.y;
        temp_f1_2 = 2.0F + sp20.x;
        sp20.x = 2.0F * var_f31 + temp_f1_2;
        sp20.y = -(2.0F * (arg0->xA4_ecbCurrCorrect.left.y -
                           arg0->xA4_ecbCurrCorrect.bottom.y) -
                   temp_f2);
        if (mpLib_8004F008(&arg0->x140, NULL, NULL, NULL, temp_f1_2, temp_f2,
                           sp20.x, sp20.y, 0.0F, arg0->x3C, arg0->x48,
                           arg0->x4C, 0, 0))
        {
            sp20.x = arg0->x140.x;
            if (arg2 != 0) {
                sp20.y = arg0->cur_pos.y;
            } else {
                sp20.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->cur_pos.x = sp20.x;
                arg0->cur_pos.y += sp30;
            }
        }
    }
}

static inline bool mpColl_80044164_inline(CollData* cd, int* p_ledge_id)
{
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f6;

    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;

    s32 var_r31;
    bool temp_r31;
    s32 temp_r31_2;
    s32 temp_r3;
    int temp_r3_2;

    Vec3 sp14;
    int sp10;

    temp_f5 = cd->ledge_snap_x;
    temp_f4 = 0.5f * cd->ledge_snap_height;
    temp_f6 = cd->ledge_snap_y;
    if (cd->cur_pos_correct.x < cd->cur_pos.x) {
        var_f31 = cd->cur_pos_correct.x;
        var_f29 = temp_f5 + (cd->cur_pos.x + cd->xA4_ecbCurrCorrect.right.x);
    } else {
        var_f31 = cd->cur_pos.x;
        var_f29 =
            temp_f5 + (cd->cur_pos_correct.x + cd->xA4_ecbCurrCorrect.right.x);
    }
    if (cd->cur_pos_correct.y < cd->cur_pos.y) {
        var_f30 = (cd->cur_pos_correct.y + temp_f6) - temp_f4;
        var_f28 = temp_f4 + (cd->cur_pos.y + temp_f6);
    } else {
        var_f30 = (cd->cur_pos.y + temp_f6) - temp_f4;
        var_f28 = temp_f4 + (cd->cur_pos_correct.y + temp_f6);
    }
    temp_r3 = mpLib_800588C8();
    if (temp_r3 == 0) {
        mpLib_800588D0(var_f31, var_f30, var_f29, var_f28);
    }

    temp_r3_2 = mpLib_80051BA8(&cd->x140, cd->x3C, cd->x48, cd->x4C, 1,
                               var_f31, var_f30, var_f29, var_f28);

    if (temp_r3_2 != -1 &&
        (mpLib_80054158(temp_r3_2, &sp14), cd->x140.x - sp14.x < 5.0f) &&
        cd->cur_pos.x + cd->xA4_ecbCurrCorrect.bottom.x < sp14.x &&
        (cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y < sp14.y) &&
        (cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y > cd->x140.y ||
         ((!mpLib_80051EC8(NULL, &sp10, NULL, NULL, 6, cd->x48, cd->x4C,
                           cd->cur_pos.x + cd->xA4_ecbCurrCorrect.top.x,
                           cd->cur_pos.y + cd->xA4_ecbCurrCorrect.top.y,
                           cd->x140.x, cd->x140.y) ||
           mpLib_80056B6C(temp_r3_2) == mpLib_80056B6C(sp10)) &&
          (!mpLib_80051EC8(
               NULL, &sp10, NULL, NULL, 6, cd->x48, cd->x4C,
               cd->cur_pos.x + cd->xA4_ecbCurrCorrect.bottom.x,
               -2.0F + (cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y),
               cd->x140.x, cd->x140.y) ||
           mpLib_80056B6C(temp_r3_2) == mpLib_80056B6C(sp10)))))
    {
        if (p_ledge_id != NULL) {
            *p_ledge_id = temp_r3_2;
        }
        var_r31 = 1;
    } else {
        var_r31 = 0;
    }
    return var_r31;
}

bool mpColl_80044164(CollData* cd, int* p_ledge_id)
{
    f32 temp_f4;
    f32 temp_f5;
    f32 temp_f6;

    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;

    s32 var_r31;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r3;
    s32 temp_r3_2;

    Vec3 sp14;
    int sp10;

    temp_f5 = cd->ledge_snap_x;
    temp_f4 = 0.5f * cd->ledge_snap_height;
    temp_f6 = cd->ledge_snap_y;
    if (cd->cur_pos_correct.x < cd->cur_pos.x) {
        var_f31 = cd->cur_pos_correct.x;
        var_f29 = temp_f5 + (cd->cur_pos.x + cd->xA4_ecbCurrCorrect.right.x);
    } else {
        var_f31 = cd->cur_pos.x;
        var_f29 =
            temp_f5 + (cd->cur_pos_correct.x + cd->xA4_ecbCurrCorrect.right.x);
    }
    if (cd->cur_pos_correct.y < cd->cur_pos.y) {
        var_f30 = (cd->cur_pos_correct.y + temp_f6) - temp_f4;
        var_f28 = temp_f4 + (cd->cur_pos.y + temp_f6);
    } else {
        var_f30 = (cd->cur_pos.y + temp_f6) - temp_f4;
        var_f28 = temp_f4 + (cd->cur_pos_correct.y + temp_f6);
    }
    temp_r3 = mpLib_800588C8();
    if (temp_r3 == 0) {
        mpLib_800588D0(var_f31, var_f30, var_f29, var_f28);
    }
    temp_r3_2 = mpLib_80051BA8(&cd->x140, cd->x3C, cd->x48, cd->x4C, 1,
                               var_f31, var_f30, var_f29, var_f28);
    if (temp_r3_2 != -1 &&
        (mpLib_80054158(temp_r3_2, &sp14), cd->x140.x - sp14.x < 5.0f) &&
        cd->cur_pos.x + cd->xA4_ecbCurrCorrect.bottom.x < sp14.x &&
        cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y < sp14.y &&
        (cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y > cd->x140.y ||
         ((!mpLib_80051EC8(NULL, &sp10, NULL, NULL, 6, cd->x48, cd->x4C,
                           cd->cur_pos.x + cd->xA4_ecbCurrCorrect.top.x,
                           cd->cur_pos.y + cd->xA4_ecbCurrCorrect.top.y,
                           cd->x140.x, cd->x140.y) ||
           mpLib_80056B6C(temp_r3_2) == mpLib_80056B6C(sp10)) &&
          (!mpLib_80051EC8(
               NULL, &sp10, NULL, NULL, 6, cd->x48, cd->x4C,
               cd->cur_pos.x + cd->xA4_ecbCurrCorrect.bottom.x,
               -2.0F + (cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y),
               cd->x140.x, cd->x140.y) ||
           mpLib_80056B6C(temp_r3_2) == mpLib_80056B6C(sp10)))))
    {
        if (p_ledge_id != NULL) {
            *p_ledge_id = temp_r3_2;
        }
        var_r31 = 1;
    } else {
        var_r31 = 0;
    }
    if (temp_r3 == 0) {
        mpLib_80058AA0();
    }
    return var_r31;
}

/// #mpColl_800443C4

/// #mpColl_80044628

/// #mpColl_80044838

/// #mpColl_80044948

/// #mpColl_80044AD8

/// #mpColl_80044C74

/// #mpColl_80044E10

/// #mpColl_800454A4

/// #mpColl_80045B74

/// #mpColl_80046224

#pragma push
#pragma dont_inline on
bool mpColl_80046904(CollData* coll, u32 flags)
{ // Physics_CollisionAirCallback
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    float x_after_collide_left;
    float y_after_collide_ceiling;
    float x_after_collide_right;
    float y_after_collide_floor;
    s32 temp_r21;
    s32 temp_r21_2;
    s32 temp_r21_3;
    s32 temp_r21_4;
    s32 old_horizontal_squeeze_flags;
    s32 old_x34_flag_b6;
    s32 var_r0;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r21;
    s32 touched_floor;
    s32 horizontal_squeeze_flags_2;
    s32 horizontal_squeeze_flags_all;
    s32 horizontal_squeeze_flags;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r4;
    s32 not_touched_floor;
    s32 var_r5;
    s32 var_r5_2;
    float xy_arg_1;
    float xy_arg_2;
    float xy_arg_3;
    float xy_arg_4;

    horizontal_squeeze_flags_2 = 0;
    touched_floor = 0;
    horizontal_squeeze_flags_all = 0;
    horizontal_squeeze_flags = 0;
    do {
        x_after_collide_right = 0.0f;
        old_horizontal_squeeze_flags = horizontal_squeeze_flags;
        x_after_collide_left = 0.0f;
        old_x34_flag_b6 = coll->x34_flags.b6;
        horizontal_squeeze_flags = 0;
        if (mpColl_80045B74(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224(coll)) { // Physics_LeftWallCollideAir
                horizontal_squeeze_flags_2 |= 1;
                horizontal_squeeze_flags |= 8;
            }
            x_after_collide_left = coll->cur_pos.x;
        }
        if (mpColl_80044E10(coll)) {     // Physics_RightWallCheckAir
            if (mpColl_800454A4(coll)) { // Physics_RightWallCollideAir
                horizontal_squeeze_flags_2 |= 2;
                horizontal_squeeze_flags |= 4;
            }
            x_after_collide_right = coll->cur_pos.x;
        }
        if (mpColl_80045B74(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224(coll)) { // Physics_LeftWallCollideAir
                horizontal_squeeze_flags_2 |= 1;
                horizontal_squeeze_flags |= 8;
            }
            x_after_collide_left = coll->cur_pos.x;
        }
        if (mpColl_80044E10(coll)) {     // Physics_RightWallCheckAir
            if (mpColl_800454A4(coll)) { // Physics_RightWallCollideAir
                horizontal_squeeze_flags_2 |= 2;
                horizontal_squeeze_flags |= 4;
            }
            x_after_collide_right = coll->cur_pos.x;
        }
        if ((horizontal_squeeze_flags & 0xC) == 0xC) {
            mpColl_8004C864(coll, 1, x_after_collide_right,
                            x_after_collide_left); // Physics_SqueezeHorizontal
        }
        y_after_collide_ceiling = 0.0f;
        y_after_collide_floor = 0.0f;
        if (mpColl_80044AD8(coll, horizontal_squeeze_flags_2) &&
            mpColl_80044C74(coll))
        { // Physics_CeilingCheck, Physics_CeilingCollideAir
            temp_r21 = mpColl_80052A98(
                coll->ceiling.index); // Collision_GetNextNonCeilingLine
            xy_arg_1 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.top.x;
            xy_arg_2 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.top.y;
            xy_arg_3 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.right.x;
            xy_arg_4 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.right.y;
            if (mpLib_800501CC(xy_arg_1, xy_arg_2, xy_arg_3, xy_arg_4, NULL,
                               &sp1C, NULL, NULL, coll->x48, coll->x4C) &&
                sp1C != temp_r21)
            { // Collision_CheckLeftWallHug
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            if (var_r0) {
                // TODO: inhibit inlining
                mpColl_800439FC(coll); // Physics_LeftWallCeilingMultiCollide
            }
            temp_r21_2 = mpColl_800528CC(
                coll->ceiling.index); // Collision_GetPrevNonCeilingLine
            xy_arg_1 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.top.x;
            xy_arg_2 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.top.y;
            xy_arg_3 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.left.x;
            xy_arg_4 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.left.y;
            if (mpLib_800509B8(xy_arg_1, xy_arg_2, xy_arg_3, xy_arg_4, NULL,
                               &sp18, NULL, NULL, coll->x48, coll->x4C) &&
                sp18 != temp_r21_2)
            { // Collision_CheckRightWallHug
                var_r0_2 = 1;
            } else {
                var_r0_2 = 0;
            }
            if (var_r0_2) {
                // TODO: inhibit inlining
                mpColl_80043ADC(coll); // Physics_RightWallCeilingMultiCollide
            }
            horizontal_squeeze_flags |= 1;
            y_after_collide_ceiling = coll->cur_pos.y;
        }
        if (flags & CollisionFlagAir_PlatformPassCallback) {
            var_r3 = mpColl_80044628(
                coll, mpColl_804D64A0, mpColl_804D64A4,
                horizontal_squeeze_flags_2); // Physics_FloorCheckAir
        } else {
            var_r3 = mpColl_80044628(
                coll, NULL, NULL,
                horizontal_squeeze_flags_2); // Physics_FloorCheckAir
        }
        if (var_r3) {
            if (flags & CollisionFlagAir_StayAirborne) {
                if (mpColl_80044948(coll))
                { // Physics_FloorCollideStayAirborne
                    if (mpColl_80043BBC(coll, &sp24))
                    { // Physics_CheckFloorConnectedLeftWallHug
                        mpColl_80043C6C(
                            coll, sp24,
                            0); // Physics_LeftWallFloorMultiCollide
                    }
                    if (mpColl_80043E90(coll, &sp24))
                    { // Physics_CheckFloorConnectedRightWallHug
                        mpColl_80043F40(
                            coll, sp24,
                            0); // Physics_RightWallFloorMultiCollide
                    }
                }
            } else {
                var_r21 = 0;
                if (coll->xA4_ecbCurrCorrect.bottom.y > 0.0f) {
                    var_r21 = 1;
                }
                var_r4 = 0;
                if (var_r21 && !(horizontal_squeeze_flags & 1)) {
                    var_r4 = 1;
                }
                if (mpColl_80044838(coll, var_r4))
                { // Physics_SnapToFloorNoEdgePass
                    if (mpColl_80043BBC(coll, &sp20))
                    { // Physics_CheckFloorConnectedLeftWallHug
                        var_r5 = 0;
                        if (var_r21 && !(horizontal_squeeze_flags & 1)) {
                            var_r5 = 1;
                        }
                        // TODO: inhibit inlining
                        mpColl_80043C6C(
                            coll, sp20,
                            var_r5); // Physics_LeftWallFloorMultiCollide
                    }
                    if (mpColl_80043E90(coll, &sp20))
                    { // Physics_CheckFloorConnectedRightWallHug
                        var_r5_2 = 0;
                        if (var_r21 && !(horizontal_squeeze_flags & 1)) {
                            var_r5_2 = 1;
                        }
                        // TODO: inhibit inlining
                        mpColl_80043F40(
                            coll, sp20,
                            var_r5_2); // Physics_RightWallFloorMultiCollide
                    }
                    coll->x34_flags.b5 = 1;
                    touched_floor = 1;
                }
            }
            y_after_collide_floor = coll->cur_pos.y;
            horizontal_squeeze_flags |= 2;
            if (mpColl_80044AD8(coll, horizontal_squeeze_flags_2) &&
                mpColl_80044C74(coll))
            { // Physics_CeilingCheck, Physics_CeilingCollideAir
                temp_r21_3 = mpColl_80052A98(
                    coll->ceiling.index); // Collision_GetNextNonCeilingLine
                xy_arg_1 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.top.x;
                xy_arg_2 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.top.y;
                xy_arg_3 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.right.x;
                xy_arg_4 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.right.y;
                if (mpLib_800501CC(xy_arg_1, xy_arg_2, xy_arg_3, xy_arg_4,
                                   NULL, &sp14, NULL, NULL, coll->x48,
                                   coll->x4C) &&
                    sp14 != temp_r21_3)
                { // Collision_CheckLeftWallHug
                    var_r0_3 = 1;
                } else {
                    var_r0_3 = 0;
                }
                if (var_r0_3) {
                    // TODO: inhibit inlining
                    mpColl_800439FC(
                        coll); // Physics_LeftWallCeilingMultiCollide
                }
                temp_r21_4 = mpColl_800528CC(
                    coll->ceiling.index); // Collision_GetPrevNonCeilingLine
                xy_arg_1 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.top.x;
                xy_arg_2 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.top.y;
                xy_arg_3 = coll->cur_pos.x + coll->xA4_ecbCurrCorrect.left.x;
                xy_arg_4 = coll->cur_pos.y + coll->xA4_ecbCurrCorrect.left.y;
                if (mpLib_800509B8(xy_arg_1, xy_arg_2, xy_arg_3, xy_arg_4,
                                   NULL, &sp10, NULL, NULL, coll->x48,
                                   coll->x4C) &&
                    sp10 != temp_r21_4)
                { // Collision_CheckRightWallHug
                    var_r0_4 = 1;
                } else {
                    var_r0_4 = 0;
                }
                if (var_r0_4) {
                    // TODO: inhibit inlining
                    mpColl_80043ADC(
                        coll); // Physics_RightWallCeilingMultiCollide
                }
                horizontal_squeeze_flags |= 1;
                y_after_collide_ceiling = coll->cur_pos.y;
            }
        }
        if ((horizontal_squeeze_flags & 3) == 3) {
            if (touched_floor) {
                not_touched_floor = 0;
            } else {
                not_touched_floor = 1;
            }
            mpColl_8004C91C(coll, not_touched_floor, y_after_collide_ceiling,
                            y_after_collide_floor); // Physics_SqueezeVertical
        }
        horizontal_squeeze_flags_all |= horizontal_squeeze_flags;
    } while (old_x34_flag_b6 != coll->x34_flags.b6 ||
             horizontal_squeeze_flags != old_horizontal_squeeze_flags);
    if (!touched_floor && (flags & CollisionFlagAir_CanGrabLedge)) {
        var_r3_2 = 1;
        if (!(coll->env_flags & Collide_LeftEdge) &&
            !(coll->env_flags & Collide_RightEdge))
        {
            var_r3_2 = 0;
        }
        if (!var_r3_2 && coll->cur_pos.y < coll->cur_pos_correct.y) {
            if (coll->x36 == 1 || coll->x36 == 0) {
                if (mpColl_80044164(coll, (int*) &coll->ledge_id_unk1))
                { // Physics_CheckForLeftLedge
                    var_r3_3 = 1;
                    coll->env_flags |= Collide_LeftLedgeGrab;
                } else {
                    var_r3_3 = 0;
                }
                if (var_r3_3) {
                    coll->env_flags |= Collide_LeftLedgeGrab;
                }
            }
            if (coll->x36 == -1 || coll->x36 == 0) {
                if (mpColl_800443C4(coll, &coll->ledge_id_unk0))
                { // Physics_CheckForRightLedge
                    var_r3_4 = 1;
                    coll->env_flags |= Collide_RightLedgeGrab;
                } else {
                    var_r3_4 = 0;
                }
                if (var_r3_4) {
                    coll->env_flags |= Collide_RightLedgeGrab;
                }
            }
        }
    }
    if (!(horizontal_squeeze_flags_all & 8)) {
        coll->env_flags &= ~Collide_LeftWallMask;
    }
    if (!(horizontal_squeeze_flags_all & 4)) {
        coll->env_flags &= ~Collide_RightWallMask;
    }
    return touched_floor;
}
#pragma pop

static inline bool fn_80046F78_inline(CollData* coll, int* sp14)
{
    if (coll->x38 != mpColl_804D64AC) {
        float x0 = coll->cur_pos_correct.x;
        float y0 = coll->cur_pos_correct.y;
        float x1 = coll->cur_pos.x;
        float y1 = coll->cur_pos.y;
        return mpLib_800524DC(&coll->x140, sp14, NULL, NULL, (s32) coll->x48,
                              (s32) coll->x4C, x0, y0, x1, y1);
    } else {
        float x0 = coll->cur_pos_correct.x;
        float y0 = coll->cur_pos_correct.y;
        float x1 = coll->cur_pos.x;
        float y1 = coll->cur_pos.y;
        return mpLib_80052508(&coll->x140, sp14, NULL, NULL, coll->x48,
                              coll->x4C, x0, y0, x1, y1);
    }
}

bool fn_80046F78(CollData* coll, u32 arg1)
{
    int sp14;
    f32 sp10;
    s32 temp_r3;

    if (fn_80046F78_inline(coll, &sp14)) {
        temp_r3 = mpLib_80054C6C(sp14);
        if (temp_r3 == 1) {
            sp14 = mpLib_8004DD90(sp14, &coll->x140, &sp10, &coll->floor.unk,
                                  &coll->floor.normal);
            if (sp14 != -1) {
                coll->floor.index = sp14;
                coll->cur_pos.x = coll->x140.x;
                coll->cur_pos.y = coll->x140.y + sp10;
                coll->cur_pos.z = coll->x140.z;
                coll->env_flags |= Collide_FloorPush;
                return 1;
            }
            return 0;
        } else if (temp_r3 == 2) {
            sp14 = mpLib_8004E090(sp14, &coll->x140, &sp10, &coll->ceiling.unk,
                                  &coll->ceiling.normal);
            if (sp14 != -1) {
                coll->ceiling.index = sp14;
                coll->cur_pos.x = coll->x140.x;
                coll->cur_pos.y = coll->x140.y + sp10;
                coll->cur_pos.z = coll->x140.z;
                coll->env_flags |= Collide_CeilingPush;
                return 1;
            }
            return 0;
        } else if (temp_r3 == 8) {
            sp14 = mpLib_8004E398(sp14, &coll->x140, (s32) &sp10,
                                  (s32) &coll->right_wall.unk,
                                  (s32) &coll->right_wall.normal);
            if (sp14 != -1) {
                coll->right_wall.index = sp14;
                coll->cur_pos.x = coll->x140.x + sp10;
                coll->cur_pos.y = coll->x140.y;
                coll->cur_pos.z = coll->x140.z;
                coll->env_flags |= Collide_LeftWallPush;
                return 1;
            }
            return 0;
        } else if (temp_r3 == 4) {
            sp14 =
                mpLib_8004E684(sp14, &coll->x140, &sp10, &coll->left_wall.unk,
                               &coll->left_wall.normal);
            if (sp14 != -1) {
                coll->left_wall.index = sp14;
                coll->cur_pos.x = coll->x140.x + sp10;
                coll->cur_pos.y = coll->x140.y;
                coll->cur_pos.z = coll->x140.z;
                coll->env_flags |= Collide_RightWallPush;
                return 1;
            }
            return 0;
        } else {
            HSD_ASSERT(3685, 0);
            return;
        }
    }
    return 0;
}

static inline bool inline0(CollData* coll, int i, bool j)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->xA4_ecbCurrCorrect.top.y - coll->xA4_ecbCurrCorrect.bottom.y <
            6.0F &&
        coll->xA4_ecbCurrCorrect.right.y - coll->xA4_ecbCurrCorrect.left.y <
            6.0F)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    result = mpColl_80043754(mpColl_80046904, coll, i);
    mpCollEnd(coll, result, j);
    return result;
}

static inline bool inline4(CollData* coll, int i)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->xA4_ecbCurrCorrect.top.y - coll->xA4_ecbCurrCorrect.bottom.y <
            6.0F &&
        coll->xA4_ecbCurrCorrect.right.y - coll->xA4_ecbCurrCorrect.left.y <
            6.0F)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    result = mpColl_80043754(fn_80046F78, coll, i);
    mpCollEnd(coll, result, 1);
    return result;
}

static inline bool inline2(CollData* coll, int i)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->xA4_ecbCurrCorrect.top.y - coll->xA4_ecbCurrCorrect.bottom.y <
            6.0F &&
        coll->xA4_ecbCurrCorrect.right.y - coll->xA4_ecbCurrCorrect.left.y <
            6.0F)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    result = mpColl_80043754((void*) fn_8004ACE4, coll, i);
    mpCollEnd(coll, result, 0);
    return result;
}

static inline bool inline3(CollData* coll, int i)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->xA4_ecbCurrCorrect.top.y - coll->xA4_ecbCurrCorrect.bottom.y <
            6.0F &&
        coll->xA4_ecbCurrCorrect.right.y - coll->xA4_ecbCurrCorrect.left.y <
            6.0F)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    result = mpColl_80043754(fn_8004C534, coll, i);
    mpCollEnd(coll, result, 0);
    return result;
}

static inline bool inline1(CollData* coll, int i,
                           bool (*arg1)(Fighter_GObj*, int),
                           Fighter_GObj* arg2)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->xA4_ecbCurrCorrect.top.y - coll->xA4_ecbCurrCorrect.bottom.y <
            6.0F &&
        coll->xA4_ecbCurrCorrect.right.y - coll->xA4_ecbCurrCorrect.left.y <
            6.0F)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    mpColl_804D64A0 = arg1;
    mpColl_804D64A4 = arg2;
    result = mpColl_80043754(mpColl_80046904, coll, i);
    mpCollEnd(coll, result, 1);
    return result;
}

bool mpColl_800471F8(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline0(coll, 0, true);
}

bool mpColl_8004730C(CollData* coll, ftCollisionBox* arg1)
{
    mpCollPrev(coll);
    mpColl_80042C58(coll, arg1);
    return inline0(coll, 0, true);
}

bool mpColl_800473CC(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline0(coll, 4, true);
}

bool mpColl_800474E0(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline0(coll, 4, true);
}

bool mpColl_800475F4(CollData* coll, ftCollisionBox* arg1)
{
    mpCollPrev(coll);
    mpColl_80042C58(coll, arg1);
    return inline0(coll, 4, true);
}

bool mpColl_800476B4(CollData* coll, bool (*arg1)(Fighter_GObj*, enum_t),
                     Fighter_GObj* gobj)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline1(coll, 3, arg1, gobj);
}

bool mpColl_800477E0(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline0(coll, 1, true);
}

bool mpColl_800478F4(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline0(coll, 1, true);
}

bool mpColl_80047A08(CollData* coll, ftCollisionBox* arg1)
{
    mpCollPrev(coll);
    mpColl_80042C58(coll, arg1);
    return inline0(coll, 1, true);
}

bool mpColl_80047AC8(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047BF4(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 0xA);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047D20(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 0x12);
    } else {
        mpColl_8004293C(coll);
    }
    mpColl_80042384(coll);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047E14(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 6);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_80047F40(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 0xA);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_8004806C(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 0x12);
    } else {
        mpColl_8004293C(coll);
    }
    mpColl_80042384(coll);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_80048160(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 0xA);
    return inline0(coll, 0, true);
}

bool mpColl_80048274(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 0xA);
    return inline0(coll, 1, true);
}

bool mpColl_80048388(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 0x12);
    } else {
        mpColl_8004293C(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 1, true);
}

bool mpColl_80048464(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 0xA);
    return inline0(coll, 4, true);
}

bool mpColl_80048578(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 0x12);
    } else {
        mpColl_8004293C(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 4, true);
}

bool mpColl_80048654(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline0(coll, 0, true);
}

bool mpColl_80048768(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->x104 == 1) {
        mpColl_800424DC(coll, 0x12);
    } else {
        mpColl_8004293C(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 0, true);
}

bool mpColl_80048844(CollData* coll, f32 arg1)
{
    mpCollPrev(coll);
    return inline4(coll, 0);
}

bool mpColl_800488F4(CollData* arg0)
{
    Vec3 sp30;
    u8 _[0xC];
    f32 sp20;
    Vec3 sp14;

    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 var_r30;

    PAD_STACK(0x8);

    temp_r31 = arg0->floor.index;
    sp30.x = arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.bottom.x;
    sp30.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.bottom.y;
    if (!mpLib_80054ED8(arg0->floor.index) ||
        (mpLib_80054C6C(arg0->floor.index) != 1))
    {
        return false;
    }
    temp_r3 = mpLib_8004DD90(temp_r31, &sp30, &sp20, &arg0->floor.unk,
                             &arg0->floor.normal);
    if (temp_r3 != -1) {
        arg0->cur_pos.y += sp20;
        arg0->floor.index = temp_r3;
        return true;
    }
    var_r30 = false;
    mpLib_80054158(temp_r31, &sp14);
    if (arg0->cur_pos.x < sp14.x) {
        temp_r3_2 = mpLib_80052700(temp_r31);
        if ((temp_r3_2 != -1) && mpLib_80054ED8(temp_r3_2) &&
            (mpLib_80054C6C(temp_r3_2) & 4))
        {
            var_r30 = true;
        } else {
            arg0->env_flags |= Collide_LeftLedgeSlip;
        }
    } else {
        mpLib_80053FF4(temp_r31, &sp14);
        if (arg0->cur_pos.x > sp14.x) {
            temp_r3_3 = mpLib_80052534(temp_r31);
            if ((temp_r3_3 != -1) && mpLib_80054ED8(temp_r3_3) &&
                (mpLib_80054C6C(temp_r3_3) & 8))
            {
                var_r30 = true;
            } else {
                arg0->env_flags |= Collide_RightLedgeSlip;
            }
        }
    }
    if (var_r30) {
        arg0->cur_pos = sp14;
        return true;
    }
    return false;
}

/// #mpColl_80048AB0

/// #mpColl_800491C8

/// #mpColl_80049778

/// #mpColl_80049EAC

/// #mpColl_8004A45C

/// #mpColl_8004A678

/// #mpColl_8004A908

bool mpColl_8004AB80(CollData* arg0)
{
    Vec3 sp1C;
    f32 sp18;
    Vec3 spC;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_ret;
    s32 var_r31;

    sp1C.x = arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.top.x;
    sp1C.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.top.y;
    temp_r3 = mpLib_8004E090(arg0->ceiling.index, &sp1C, &sp18,
                             &arg0->ceiling.unk, &arg0->ceiling.normal);
    if (temp_r3 != -1) {
        arg0->ceiling.index = temp_r3;
        arg0->cur_pos.y += sp18;
    } else {
        var_r31 = 0;
        mpLib_80054420(arg0->ceiling.index, &spC);
        if (sp1C.x <= spC.x) {
            temp_r3_2 = mpLib_80052A98(arg0->ceiling.index);
            if ((temp_r3_2 != -1) && (mpLib_80054C6C(temp_r3_2) == 4)) {
                var_r31 = 1;
            }
        } else {
            mpLib_800542BC(arg0->ceiling.index, &spC);
            temp_r3_3 = mpLib_800528CC(arg0->ceiling.index);
            if ((temp_r3_3 != -1) && (mpLib_80054C6C(temp_r3_3) == 8)) {
                var_r31 = 1;
            }
        }
        arg0->cur_pos.y = spC.y - arg0->xA4_ecbCurrCorrect.top.y;
        if (var_r31 != 0) {
            arg0->cur_pos.x = spC.x;
            temp_ret =
                mpLib_8004E090(arg0->ceiling.index, &spC, NULL,
                               &arg0->ceiling.unk, &arg0->ceiling.normal);
            temp_r3_4 = temp_ret;
            if (temp_r3_4 != -1) {
                arg0->ceiling.index = temp_r3_4;
            } else {
                OSReport("%s:%d: oioi...\n", "mpcoll.c", 0x1671);
            }
        }
    }
    return true;
}

#pragma push
#pragma dont_inline on
bool fn_8004ACE4(CollData* arg0, int arg1)
{
    s32 sp14;
    s32 sp10;

    f32 var_f31;
    f32 var_f30;
    f32 var_f29;
    f32 var_f28;

    bool var_r29;
    u32 var_r28;
    bool temp_r27;
    bool var_r26;
    bool var_r25;
    bool var_r25_2;
    bool var_r26_2;
    int temp_r23;
    int temp_r22;
    bool var_r23;
    bool var_r4;

    var_r29 = false;
    var_r28 = 0;
    do {
        var_r25 = 0;
        temp_r27 = arg0->x34_flags.b6;
        var_r26 = 0;
        if (mpColl_80049778(arg0)) {
            var_r26 = mpColl_80049EAC(arg0);
            if (var_r26) {
                var_r28 |= 1;
            } else {
                arg0->env_flags &= 0xFFFFFFC0;
            }
            var_f30 = arg0->cur_pos.x;
            arg0->x34_flags.b5 = true;
        }
        if (mpColl_80048AB0(arg0)) {
            var_r25 = mpColl_800491C8(arg0);
            if (var_r25) {
                var_r28 |= 2;
            } else {
                arg0->env_flags &= 0xFFFFF03F;
            }
            var_f31 = arg0->cur_pos.x;
            arg0->x34_flags.b5 = true;
        }
        if (mpColl_80049778(arg0)) {
            var_r26 |= mpColl_80049EAC(arg0);
            if (var_r26) {
                var_r28 |= 1;
            }
            var_f30 = arg0->cur_pos.x;
            arg0->x34_flags.b5 = true;
        }
        if (mpColl_80048AB0(arg0)) {
            var_r25 |= mpColl_800491C8(arg0);
            if (var_r25) {
                var_r28 |= 2;
            }
            var_f31 = arg0->cur_pos.x;
            arg0->x34_flags.b5 = true;
        }
        if (var_r26 && var_r25) {
            mpColl_8004C864(arg0, 0, var_f31, var_f30);
        }
        var_r26_2 = 0;
        var_r25_2 = 0;
        if (mpColl_80044AD8(arg0, var_r28) && mpColl_8004AB80(arg0)) {
            var_r26_2 = 1;
            var_f29 = arg0->cur_pos.y;
        }
        if (mpColl_800488F4(arg0)) {
            if (mpColl_80043BBC(arg0, &sp14)) {
                mpColl_80043C6C(arg0, sp14, 0);
            }
            if (mpColl_80043E90(arg0, &sp14)) {
                mpColl_80043F40(arg0, sp14, 0);
            }
            var_f28 = arg0->cur_pos.y;
            var_r29 = 1;
            var_r25_2 = 1;
            if (mpColl_80044AD8(arg0, var_r28) && mpColl_8004AB80(arg0)) {
                var_f29 = arg0->cur_pos.y;
                var_r26_2 = 1;
            }
        } else {
            temp_r22 = arg0->floor.index;
            var_r23 = 0;
            if (mpLib_80054ED8(temp_r22) && mpLib_80054C6C(temp_r22) == 1) {
                if (arg1 & 1) {
                    if (mpColl_8004A678(arg0, temp_r22)) {
                        arg0->x34_flags.b5 = true;
                        var_r29 = 0;
                        var_r25_2 = 1;
                        var_f28 = arg0->cur_pos.y;
                    } else {
                        var_r23 = 1;
                    }
                } else if (arg1 & 2) {
                    if (mpColl_8004A45C(arg0, temp_r22)) {
                        arg0->x34_flags.b5 = true;
                        var_r29 = 1;
                        var_r25_2 = 1;
                        var_f28 = arg0->cur_pos.y;
                    } else {
                        var_r23 = 1;
                    }
                } else {
                    var_r23 = 1;
                }
                if (var_r23) {
                    temp_r23 = arg0->x3C;
                    arg0->x3C = temp_r22;
                    if (mpColl_80046904(arg0, 0U)) {
                        var_r29 = 1;
                    }
                    arg0->x3C = temp_r23;
                    arg0->x34_flags.b5 = true;
                }
            }
        }
        if (var_r25_2 && var_r26_2) {
            if (var_r29) {
                var_r4 = 0;
            } else {
                var_r4 = 1;
            }
            mpColl_8004C91C(arg0, var_r4, var_f29, var_f28);
        }
    } while (temp_r27 != arg0->x34_flags.b6);
    if (mpColl_8004A908(arg0, arg0->floor.index)) {
        if (mpColl_80044838(arg0, 0)) {
            if (mpColl_80043BBC(arg0, &sp10)) {
                mpColl_80043C6C(arg0, sp10, 0);
            }
            if (mpColl_80043E90(arg0, &sp10)) {
                mpColl_80043F40(arg0, sp10, 0);
            }
        }
        arg0->x34_flags.b5 = false;
        var_r29 = true;
    }
    if (var_r29) {
        arg0->env_flags |= Collide_FloorPush;
    }
    return var_r29;
}
#pragma pop

bool mpColl_8004B108(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline2(coll, 0);
}

bool mpColl_8004B21C(CollData* coll, ftCollisionBox* arg1)
{
    mpCollPrev(coll);
    mpColl_80042C58(coll, arg1);
    return inline2(coll, 0);
}

bool mpColl_8004B2DC(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline2(coll, 2);
}

bool mpColl_8004B3F0(CollData* coll, ftCollisionBox* arg1)
{
    mpCollPrev(coll);
    mpColl_80042C58(coll, arg1);
    return inline2(coll, 2);
}

bool mpColl_8004B4B0(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline2(coll, 1);
}

bool mpColl_8004B5C4(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 9);
    return inline2(coll, 1);
}

bool mpColl_8004B6D8(CollData* arg0)
{
    Vec3 sp30;
    u8 _[0xC];
    f32 sp20;
    Vec3 sp14;

    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    bool var_r30;

    PAD_STACK(0x8);

    temp_r31 = arg0->ceiling.index;
    sp30.x = arg0->cur_pos.x + arg0->xA4_ecbCurrCorrect.top.x;
    sp30.y = arg0->cur_pos.y + arg0->xA4_ecbCurrCorrect.top.y;
    if (!mpLib_80054ED8(arg0->ceiling.index) ||
        mpLib_80054C6C(arg0->ceiling.index) != 2)
    {
        return false;
    }
    temp_r3 = mpLib_8004E090(temp_r31, &sp30, &sp20, &arg0->ceiling.unk,
                             &arg0->ceiling.normal);
    if (temp_r3 != -1) {
        arg0->cur_pos.y += sp20;
        arg0->ceiling.index = temp_r3;
        return true;
    }
    var_r30 = false;
    mpLib_80054420(temp_r31, &sp14);
    if (arg0->cur_pos.x < sp14.x) {
        temp_r3_2 = mpLib_80052A98(temp_r31);
        if (temp_r3_2 != -1 && mpLib_80054ED8(temp_r3_2) &&
            (mpLib_80054C6C(temp_r3_2) & 4))
        {
            var_r30 = true;
        } else {
            arg0->env_flags |= Collide_LeftLedgeSlip;
        }
    } else {
        mpLib_800542BC(temp_r31, &sp14);
        if (arg0->cur_pos.x > sp14.x) {
            temp_r3_3 = mpLib_800528CC(temp_r31);
            if (temp_r3_3 != -1 && mpLib_80054ED8(temp_r3_3) &&
                (mpLib_80054C6C(temp_r3_3) & 8))
            {
                var_r30 = true;
            } else {
                arg0->env_flags |= Collide_RightLedgeSlip;
            }
        }
    }
    if (var_r30) {
        arg0->cur_pos = sp14;
        return true;
    }
    return false;
}

/// #mpColl_8004B894

/// #mpColl_8004BDD4

/// #mpColl_8004C328

/// #fn_8004C534

bool mpColl_8004C750(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_80042D24_inline(coll, 5);
    return inline3(coll, 2);
}

/// #mpColl_8004C864

/// #mpColl_8004C91C

float mpColl_8004CA6C(CollData* coll)
{
    float result = 1.0F;
    if (coll->floor.index != -1) {
        result = mpLib_800569EC(coll->floor.unk);
    }
    return result;
}

bool mpColl_8004CAA0(CollData* coll, Vec3* arg1)
{
    int index = coll->ceiling.index;
    Vec3 sp10;
    sp10.x = coll->xA4_ecbCurrCorrect.top.x;
    sp10.y = coll->xA4_ecbCurrCorrect.top.y;
    sp10.z = 0.0F;
    return mpLib_800567C0(index, &sp10, arg1);
}

bool mpColl_8004CAE8(CollData* coll, Vec3* arg1)
{
    int index = coll->right_wall.index;
    Vec3 sp10;
    sp10.x = coll->xA4_ecbCurrCorrect.top.x;
    sp10.y = coll->xA4_ecbCurrCorrect.top.y;
    sp10.z = 0.0F;
    return mpLib_800567C0(index, &sp10, arg1);
}

bool mpColl_8004CB30(CollData* coll, Vec3* arg1)
{
    int index = coll->left_wall.index;
    Vec3 sp10;
    sp10.x = coll->xA4_ecbCurrCorrect.top.x;
    sp10.y = coll->xA4_ecbCurrCorrect.top.y;
    sp10.z = 0.0F;
    return mpLib_800567C0(index, &sp10, arg1);
}

bool mpColl_8004CB78(CollData* coll, Vec3* arg1)
{
    int index = coll->floor.index;
    Vec3 sp10;
    sp10.x = coll->xA4_ecbCurrCorrect.top.x;
    sp10.y = coll->xA4_ecbCurrCorrect.top.y;
    sp10.z = 0.0F;
    return mpLib_800567C0(index, &sp10, arg1);
}

bool mpColl_8004CBC0(CollData* coll)
{
    return mpLib_80054CEC(coll->floor.index) & 0x100;
}

void mpColl_8004CBE8(CollData* coll)
{
    coll->x3C = coll->floor.index;
}

void mpColl_8004CBF4(CollData* coll)
{
    coll->x3C = -1;
}

/// #mpColl_8004CC00

bool mpColl_8004D024(Vec3* arg0)
{
    CollData spC;
    mpColl_80041EE4(&spC);
    spC.x34_flags.b1234 = 0;
    mpColl_8004220C(&spC, NULL, 10.0f, 10.0f, 10.0f, 10.0f);
    spC.prev_pos.x = arg0->x;
    spC.prev_pos.y = -3.0f + arg0->y;
    spC.prev_pos.z = arg0->z;
    spC.cur_pos = *arg0;
    spC.x130_flags |= 0x20;
    mpCollPrev(&spC);
    mpColl_80042D24(&spC);
    inline0(&spC, 0, true);
    if (spC.x34_flags.b6) {
        return true;
    }
    return false;
}
