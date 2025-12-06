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
#include "lb/types.h"

#include "mp/forward.h"

#include "mp/mplib.h"

#include <string.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <MSL/trigf.h>

struct mpColl_80458810_t {
    /*  +0 */ int right[9];
    /* +24 */ int left[9];
    /* +48 */ Vec3 normal;
    /* +54 */ u8 x54_pad[4];
};

static struct mpColl_80458810_t mpColl_80458810;
static bool mpColl_IsEcbTiny;
static bool (*mpColl_804D64A0)(Fighter_GObj*, int);
static Fighter_GObj* mpColl_804D64A4;
static Event mpColl_804D64A8;
int mpColl_804D64AC;
int mpColl_804D6488;
int mpColl_804D648C;

/// @todo float order hack
const float mpColl_804D7F9C = -F32_MAX;
const float mpColl_804D7FA0 = F32_MAX;
const float flt_804D7FF8 = 5.0F;
const f64 flt_804D8000 = -0.75;
const f64 flt_804D8008 = 0.75;
const float flt_804D8010 = -3.0F;

/// @todo float order hack
const float flt_804D7FD8 = 6.0F;

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

void mpCollCheckBounding(CollData* cd, u32 flags)
{
    float left, bottom, right, top;

    left = cd->ecb.left.x + cd->cur_pos.x;
    clamp_below(&left, cd->prev_ecb.left.x + cd->prev_pos.x);

    right = cd->ecb.right.x + cd->cur_pos.x;
    clamp_above(&right, cd->prev_ecb.right.x + cd->prev_pos.x);

    bottom = cd->ecb.bottom.y + cd->cur_pos.y;
    clamp_below(&bottom, cd->prev_ecb.bottom.y + cd->prev_pos.y);

    top = cd->ecb.top.y + cd->cur_pos.y;
    clamp_above(&top, cd->prev_ecb.top.y + cd->prev_pos.y);

    if (flags & 0b100) {
        float ledge_snap_x = cd->ledge_snap_x;
        float half_height = 0.5F * cd->ledge_snap_height;
        float offset;

        right += ledge_snap_x;
        left -= ledge_snap_x;

        clamp_below(&bottom, cd->ledge_snap_y - half_height + cd->cur_pos.y);
        clamp_below(&bottom, cd->ledge_snap_y - half_height + cd->prev_pos.y);

        offset = cd->ledge_snap_y + half_height;
        clamp_above(&top, cd->cur_pos.y + offset);
        clamp_above(&top, cd->prev_pos.y + offset);
    }

    mpBoundingCheck(left, bottom, right, top);
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
    cd->prev_pos = cd->cur_pos;
    cd->last_pos = cd->cur_pos;
    cd->x28_vec = cd->cur_pos;
    cd->floor_skip = -1;
    cd->ledge_id_right = -1;
    cd->ledge_id_left = -1;
    cd->floor.index = -1;
    cd->floor.flags = 0;
    cd->floor.normal.x = 0.0F;
    cd->floor.normal.y = 1.0F;
    cd->floor.normal.z = 0.0F;
    cd->ceiling.index = -1;
    cd->ceiling.flags = 0;
    cd->ceiling.normal.x = 0.0F;
    cd->ceiling.normal.y = -1.0F;
    cd->ceiling.normal.z = 0.0F;
    cd->right_facing_wall.index = -1;
    cd->right_facing_wall.flags = 0;
    cd->right_facing_wall.normal.x = 0.0F;
    cd->right_facing_wall.normal.y = 1.0F;
    cd->right_facing_wall.normal.z = 0.0F;
    cd->left_facing_wall.index = -1;
    cd->left_facing_wall.flags = 0;
    cd->left_facing_wall.normal.x = 0.0F;
    cd->left_facing_wall.normal.y = -1.0F;
    cd->left_facing_wall.normal.z = 0.0F;
    cd->x38 = mpColl_804D64AC;
    cd->x50 = 0.0F;
    cd->joint_id_skip = -1;
    cd->joint_id_only = -1;
    cd->ledge_snap_x = 0.0F;
    cd->ledge_snap_y = 0.0F;
    cd->ledge_snap_height = 0.0F;
    memzero(&cd->ecb, sizeof(ftECB));
    memzero(&cd->prev_ecb, sizeof(ftECB));
    memzero(&cd->xE4_ecb, sizeof(ftECB));
    memzero(&cd->ecb_source, sizeof(ECBSource));
    memzero(&cd->desired_ecb, sizeof(ftECB));
    memzero(&cd->x64_ecb, sizeof(ftECB));
}

// 80042078 https://decomp.me/scratch/hM7h8
void mpColl_SetECBSource_JObj(CollData* cd, HSD_GObj* gobj, HSD_JObj* arg1,
                              HSD_JObj* arg2, HSD_JObj* arg3, HSD_JObj* arg4,
                              HSD_JObj* arg5, HSD_JObj* arg6, HSD_JObj* arg7,
                              float arg9)
{
    cd->x0_gobj = gobj;
    cd->ecb_source.kind = ECBSource_JObj;
    cd->ecb_source.x108_joint = arg1;
    cd->ecb_source.x10C_joint[0] = arg2;
    cd->ecb_source.x10C_joint[1] = arg3;
    cd->ecb_source.x10C_joint[2] = arg4;
    cd->ecb_source.x10C_joint[3] = arg5;
    cd->ecb_source.x10C_joint[4] = arg6;
    cd->ecb_source.x10C_joint[5] = arg7;
    cd->ecb_source.x124 = arg9;
    cd->ecb_source.x128 = 10.0F;
    cd->ecb_source.x12C = 10.0F;
    if (cd->x34_flags.b0) {
        cd->ecb.top.x = 0.0F;
        cd->ecb.top.y = 8.0F;
        cd->ecb.bottom.x = 0.0F;
        cd->ecb.bottom.y = 0.0F;
        cd->ecb.right.x = 4.0F;
        cd->ecb.right.y = 4.0F;
        cd->ecb.left.x = -4.0F;
        cd->ecb.left.y = 4.0F;
        cd->ecb = cd->ecb;
        cd->prev_ecb = cd->ecb;
        cd->xE4_ecb = cd->ecb;
        cd->x64_ecb = cd->ecb;
        cd->desired_ecb = cd->ecb;
    }
    cd->facing_dir = -1;
    cd->x50 = 0.0F;
}

// 8004220C https://decomp.me/scratch/nOinn
void mpColl_SetECBSource_Fixed(CollData* cd, HSD_GObj* gobj, float arg1,
                               float arg2, float arg3, float arg4)
{
    cd->x0_gobj = gobj;
    cd->ecb_source.kind = ECBSource_Fixed;
    cd->ecb_source.up = arg1;
    cd->ecb_source.down = arg2;
    cd->ecb_source.front = arg3;
    cd->ecb_source.back = arg4;
    cd->ecb_source.angle = 0.0F;
    if (cd->x34_flags.b0) {
        cd->ecb.top.x = 0.0F;
        cd->ecb.top.y = 8.0F;
        cd->ecb.bottom.x = 0.0F;
        cd->ecb.bottom.y = 0.0F;
        cd->ecb.right.x = 4.0F;
        cd->ecb.right.y = 4.0F;
        cd->ecb.left.x = -4.0F;
        cd->ecb.left.y = 4.0F;
        cd->prev_ecb = cd->ecb;
        cd->xE4_ecb = cd->ecb;
        cd->x64_ecb = cd->ecb;
        cd->desired_ecb = cd->ecb;
    }
    cd->facing_dir = -1;
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
    if (ABS(cd->desired_ecb.top.y - cd->desired_ecb.bottom.y) < 1.0F) {
        float mid;
        cd->desired_ecb.top.y += 1.0F;
        mid = 0.5F * (cd->desired_ecb.top.y + cd->desired_ecb.bottom.y);
        cd->desired_ecb.left.y = mid;
        cd->desired_ecb.right.y = mid;
    }

    clamp_above(&cd->desired_ecb.top.y, 1.0F);
    clamp_below(&cd->desired_ecb.left.x, -1.0F);
    clamp_above(&cd->desired_ecb.right.x, 1.0F);

    if (cd->desired_ecb.top.y < cd->desired_ecb.bottom.y) {
        cd->desired_ecb.top.y = 1.0F + cd->desired_ecb.bottom.y;
    }

    if (cd->desired_ecb.right.y > cd->desired_ecb.top.y ||
        cd->desired_ecb.right.y < cd->desired_ecb.bottom.y)
    {
        float mid = 0.5F * (cd->desired_ecb.top.y + cd->desired_ecb.bottom.y);
        cd->desired_ecb.left.y = mid;
        cd->desired_ecb.right.y = mid;
    }

    if (cd->desired_ecb.top.y - cd->desired_ecb.right.y < 0.001F ||
        cd->desired_ecb.right.y - cd->desired_ecb.bottom.y < 0.001F)
    {
        cd->desired_ecb.right.y =
            0.5F * (cd->desired_ecb.top.y + cd->desired_ecb.bottom.y);
    }

    if (cd->desired_ecb.top.y - cd->desired_ecb.left.y < 0.001F ||
        cd->desired_ecb.left.y - cd->desired_ecb.bottom.y < 0.001F)
    {
        cd->desired_ecb.left.y =
            0.5F * (cd->desired_ecb.top.y + cd->desired_ecb.bottom.y);
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

void mpColl_LoadECB_JObj(CollData* coll, u32 flags)
{
    Vec3 vec;
    float left_x, bottom_y;
    float right_x, top_y;
    float dx, dy;

    float phi_f1, phi_f2;
    float mid_y;
    float tmpval;

    if (coll->x130_flags & CollData_X130_Clear) {
        coll->ecb.top.x = 0.0F;
        coll->ecb.top.y = 0.0F;
        coll->ecb.bottom.x = 0.0F;
        coll->ecb.bottom.y = 0.0F;
        coll->ecb.right.x = 0.0F;
        coll->ecb.right.y = 0.0F;
        coll->ecb.left.x = 0.0F;
        coll->ecb.left.y = 0.0F;
        coll->x130_flags &= ~CollData_X130_Clear;
    }
    coll->xE4_ecb = coll->ecb;

    // Loop through all collision data joints,
    // expanding the ECB to contain them all
    {
        float temp_x = coll->cur_pos.x;
        float temp_y = coll->cur_pos.y;
        lb_8000B1CC(coll->ecb_source.x10C_joint[0], NULL, &vec);
        left_x = right_x = vec.x - temp_x;
        bottom_y = top_y = vec.y - temp_y;

#define EXPAND_ECB_FOR(joint)                                                 \
    lb_8000B1CC(joint, NULL, &vec);                                           \
    dx = vec.x - temp_x;                                                      \
    dy = vec.y - temp_y;                                                      \
    update_min_max(&left_x, &right_x, dx);                                    \
    update_min_max(&bottom_y, &top_y, dy);

        EXPAND_ECB_FOR(coll->ecb_source.x10C_joint[1]);
        EXPAND_ECB_FOR(coll->ecb_source.x10C_joint[2]);
        EXPAND_ECB_FOR(coll->ecb_source.x10C_joint[3]);
        EXPAND_ECB_FOR(coll->ecb_source.x10C_joint[4]);
        EXPAND_ECB_FOR(coll->ecb_source.x10C_joint[5]);
    }

    if (!(flags & 0b100)) {
        left_x -= 2.0F;
        right_x += 2.0F;
        bottom_y -= 2.0F;
        top_y += 2.0F;
    }

    phi_f1 = 4.0F > coll->ecb_source.x12C ? 4.0F : coll->ecb_source.x12C;
    phi_f2 = ABS(right_x - left_x);

    if (phi_f2 < phi_f1) {
        right_x = 0.5F * phi_f2;
        left_x = -right_x;
    }

    phi_f1 = 4.0F > coll->ecb_source.x128 ? 4.0F : coll->ecb_source.x128;
    phi_f2 = ABS(top_y - bottom_y);

    if (phi_f2 < phi_f1) {
        tmpval = 0.5F * phi_f2;
        mid_y = 0.5F * (top_y + bottom_y);
        top_y = mid_y + tmpval;
        bottom_y = mid_y - tmpval;
    }

    if (flags & 0b1000) {
        left_x = -1.0F;
        right_x = +1.0F;
    } else {
        right_x = right_x < +2.0F ? +2.0F : right_x;
        left_x = left_x > -2.0F ? -2.0F : left_x;
    }

    if (flags & 1) {
        bottom_y = 0.0F;
        if (flags & 0b10000) {
            top_y = 2.0F;
        }
    } else {
        if (bottom_y < 0.0F) {
            bottom_y = 0.0F;
        }
        if (flags & 0b10000) {
            mid_y = 0.5F * (bottom_y + top_y);
            bottom_y = mid_y - 1.0F;
            top_y = mid_y + 1.0F;
            if (bottom_y < 0.0F) {
                bottom_y = 0.0F;
                top_y = 2.0F;
            }
        }
    }

    coll->desired_ecb.top.x = 0.0F;
    coll->desired_ecb.top.y = top_y;
    coll->desired_ecb.bottom.x = 0.0F;
    coll->desired_ecb.bottom.y = bottom_y;
    coll->desired_ecb.right.x = right_x;
    coll->desired_ecb.right.y =
        coll->ecb_source.x124 + 0.5F * (bottom_y + top_y);
    coll->desired_ecb.left.x = left_x;
    coll->desired_ecb.left.y =
        coll->ecb_source.x124 + 0.5F * (bottom_y + top_y);
    coll->x34_flags.b0 = 0;
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

void mpColl_LoadECB_Fixed(CollData* coll)
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

    angle = coll->ecb_source.angle;
    if (coll->x130_flags & CollData_X130_Clear) {
        coll->ecb.top.x = 0.0F;
        coll->ecb.top.y = 0.0F;
        coll->ecb.bottom.x = 0.0F;
        coll->ecb.bottom.y = 0.0F;
        coll->ecb.right.x = 0.0F;
        coll->ecb.right.y = 0.0F;
        coll->ecb.left.x = 0.0F;
        coll->ecb.left.y = 0.0F;
        coll->x130_flags &= ~CollData_X130_Clear;
    }
    coll->xE4_ecb = coll->ecb;

    bottom_y = -coll->ecb_source.down;
    top_y = coll->ecb_source.up;

    if (coll->facing_dir == 1) {
        right_x = coll->ecb_source.front;
        left_x = -coll->ecb_source.back;
    } else {
        right_x = coll->ecb_source.back;
        left_x = -coll->ecb_source.front;
    }

    if (angle != 0.0F) {
        sin = sinf(angle);
        cos = cosf(angle);

        orig_top_y = top_y;
        orig_bottom_y = bottom_y;
        orig_right_x = right_x;
        orig_left_x = left_x;

        // fake
        rot_right_y = 0.5F * (orig_right_x + orig_left_x);
        midpoint_x = rot_right_y;

        top_y = right_x = bottom_y = left_x = 0.0F;

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

    clamp_above_2(&top_y, 0.0F);
    clamp_below_2(&bottom_y, -0.0F);
    clamp_above_2(&right_x, 0.0F);
    clamp_below_2(&left_x, -0.0F);

    if ((top_y - bottom_y) < 3.0F) {
        top_y = 1.5F;
        bottom_y = -top_y;
    }
    if ((right_x - left_x) < 3.0F) {
        right_x = 1.5F;
        left_x = -right_x;
    }

    coll->desired_ecb.top.x = 0.0F;
    coll->desired_ecb.top.y = top_y;
    coll->desired_ecb.bottom.x = 0.0F;
    coll->desired_ecb.bottom.y = bottom_y;

    midpoint_y = 0.5F * (top_y + bottom_y);
    coll->desired_ecb.right.x = right_x;
    coll->desired_ecb.right.y = midpoint_y;
    coll->desired_ecb.left.x = left_x;
    coll->desired_ecb.left.y = midpoint_y;

    coll->x34_flags.b0 = 0;
}

void mpColl_80042C58(CollData* coll, ftCollisionBox* arg1)
{
    if (coll->x130_flags & CollData_X130_Clear) {
        coll->ecb.top.x = 0.0F;
        coll->ecb.top.y = 0.0F;
        coll->ecb.bottom.x = 0.0F;
        coll->ecb.bottom.y = 0.0F;
        coll->ecb.right.x = 0.0F;
        coll->ecb.right.y = 0.0F;
        coll->ecb.left.x = 0.0F;
        coll->ecb.left.y = 0.0F;
        coll->x130_flags &= ~CollData_X130_Clear;
    }
    coll->xE4_ecb = coll->ecb;
    coll->desired_ecb.top.x = 0.0F;
    coll->desired_ecb.top.y = arg1->top;
    coll->desired_ecb.bottom.x = 0.0F;
    coll->desired_ecb.bottom.y = arg1->bottom;
    coll->desired_ecb.right.x = arg1->right.x;
    coll->desired_ecb.right.y = arg1->right.y;
    coll->desired_ecb.left.x = arg1->left.x;
    coll->desired_ecb.left.y = arg1->left.y;
    coll->x34_flags.b0 = 0;
}

static inline void mpColl_LoadECB_inline(CollData* coll, enum_t i)
{
    float saved_bottom_x;
    float saved_bottom_y;

    if (coll->x130_flags & CollData_X130_Locked) {
        saved_bottom_x = coll->desired_ecb.bottom.x;
        saved_bottom_y = coll->desired_ecb.bottom.y;
    }
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, i);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    if (coll->x130_flags & CollData_X130_Locked) {
        coll->desired_ecb.bottom.x = saved_bottom_x;
        coll->desired_ecb.bottom.y = saved_bottom_y;
    }
    mpColl_80042384(coll);
}

// 80042D24 https://decomp.me/scratch/2MnVj
#pragma push
#pragma dont_inline on
void mpColl_LoadECB(CollData* coll)
{
    float saved_bottom_x;
    float saved_bottom_y;

    if (coll->x130_flags & CollData_X130_Locked) {
        saved_bottom_x = coll->desired_ecb.bottom.x;
        saved_bottom_y = coll->desired_ecb.bottom.y;
    }
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 6);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    if (coll->x130_flags & CollData_X130_Locked) {
        coll->desired_ecb.bottom.x = saved_bottom_x;
        coll->desired_ecb.bottom.y = saved_bottom_y;
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

void mpCollInterpolateECB(CollData* coll, float time)
{
    coll->prev_ecb = coll->ecb;
    if (coll->x34_flags.b6) {
        coll->ecb = coll->x64_ecb;
        coll->x34_flags.b6 = 0;
    }
    Vec2_Interpolate(time, &coll->ecb.top, &coll->desired_ecb.top);
    Vec2_Interpolate(time, &coll->ecb.bottom, &coll->desired_ecb.bottom);
    Vec2_Interpolate(time, &coll->ecb.left, &coll->desired_ecb.left);
    Vec2_Interpolate(time, &coll->ecb.right, &coll->desired_ecb.right);
    if (fpclassify(coll->ecb.top.x) == FP_NAN ||
        fpclassify(coll->ecb.top.y) == FP_NAN ||
        fpclassify(coll->ecb.bottom.x) == FP_NAN ||
        fpclassify(coll->ecb.bottom.y) == FP_NAN ||
        fpclassify(coll->ecb.left.x) == FP_NAN ||
        fpclassify(coll->ecb.left.y) == FP_NAN ||
        fpclassify(coll->ecb.right.x) == FP_NAN ||
        fpclassify(coll->ecb.right.y) == FP_NAN)
    {
        HSD_ASSERTREPORT(1193, 0, "error\n");
    }
}

static void mpColl_RightWall_inline(int line_id)
{
    int i;
    for (i = 0; i < mpColl_804D6488; i++) {
        int start_id = mpColl_80458810.right[i];
        if (line_id == start_id || mpLinesConnected(start_id, line_id)) {
            return;
        }
    }
    HSD_ASSERT(330, i<MPCOLL_WALLID_MAX);
    mpColl_80458810.right[i] = line_id;
    mpColl_804D6488++;
}

static void mpColl_LeftWall_inline(int line_id)
{
    int i = 0;
    int* arr = mpColl_80458810.left;
    for (; i < mpColl_804D648C; arr++, i++) {
        if (line_id == *arr || mpLinesConnected(*arr, line_id)) {
            return;
        }
    }
    HSD_ASSERT(345, i<MPCOLL_WALLID_MAX);
    mpColl_80458810.left[i] = line_id;
    mpColl_804D648C++;
}

static void mpColl_LeftWall_inline3(int line_id, int* arr)
{
    int i;
    for (i = 0; i < mpColl_804D648C; arr++, i++) {
        if (line_id == *arr || mpLinesConnected(*arr, line_id)) {
            return;
        }
    }
    HSD_ASSERT(345, i<MPCOLL_WALLID_MAX);
    mpColl_80458810.left[i] = line_id;
    mpColl_804D648C++;
}

// 80043268 https://decomp.me/scratch/GNwej
void mpColl_80043268(CollData* coll, int line_id, bool arg2, float dy)
{
    int joint_id; // r31

    joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        mpLib_Callback callback;
        Ground* ground = NULL;
        mpJointGetCb1(joint_id, &callback, &ground);
        if (callback != 0) {
            s32 thing;
            if (!arg2) {
                thing = 2;
            } else {
                thing = 1;
            }
            callback(ground, joint_id, coll, coll->x50, thing, dy);
        }
    }
}

static inline void mpCollEnd_inline2(CollData* coll, int line_id, bool arg2,
                                     float dy)
{ // see mpColl_80043268
    int dummy = 0;

    int joint_id; // r29

    joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        mpLib_Callback callback;
        Ground* ground = NULL;
        mpJointGetCb2(joint_id, &callback, &ground);

        if (callback != NULL) {
            callback(ground, joint_id, coll, coll->x50, 0, dy);
        }
    }
}

static inline void mpCollEnd_inline(CollData* coll, int line_id, bool arg2,
                                    float dy)
{
    // inhibit inlining
    mpColl_80043268(coll, line_id, arg2, dy);
}

void mpCollEnd(CollData* coll, bool arg1, bool arg2)
{
    PAD_STACK(4);
    if (coll->floor.index != -1) {
        int temp_r3 =
            grDynamicAttr_801CA284(&coll->cur_pos, coll->floor.index);
        if (temp_r3 != 0) {
            coll->floor.flags = (coll->floor.flags & ~0xFF) | (temp_r3 & 0xFF);
        }
    }
    if (arg1 || coll->env_flags & Collide_Edge ||
        coll->env_flags & Collide_LeftEdge ||
        coll->env_flags & Collide_RightEdge)
    {
        mpCollEnd_inline(coll, coll->floor.index, arg2,
                         coll->cur_pos.y - coll->last_pos.y);
    }
    if (coll->env_flags & (Collide_CeilingHug | Collide_CeilingPush)) {
        mpCollEnd_inline2(coll, coll->ceiling.index, arg2,
                          coll->cur_pos.y - coll->last_pos.y);
    }
    if (g_debugLevel >= 3) {
        if (!(coll->cur_pos.x < 45000.0F && coll->cur_pos.x > -45000.0F &&
              coll->cur_pos.y < 45000.0F && coll->cur_pos.y > -45000.0F))
        {
            if (ftLib_80086960(coll->x0_gobj)) {
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "ply=%d ms=%d\n",
                         __FILE__, 1350, coll->last_pos.x, coll->last_pos.y,
                         coll->cur_pos.x, coll->cur_pos.y,
                         ftLib_80086BE0(coll->x0_gobj),
                         ftLib_800874BC(coll->x0_gobj));
            } else {
                s32 gobjid = coll->x0_gobj->classifier;
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "gobjid=%d\n",
                         __FILE__, 1358, coll->last_pos.x, coll->last_pos.y,
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
/// @todo dummy stack in #mpCollEnd_inline2 breaks this function
void mpColl_80043558(CollData* coll, int line_id)
{
#if SOLUTION == 0
    enum_t kind;
    s32 joint_id;

    kind = mpLineGetKind(line_id);
    if (kind == CollLine_Floor) {
        joint_id = mpJointFromLine(line_id);
        if (joint_id != -1) {
            Ground* ground = NULL;
            mpLib_Callback callback;
            mpJointGetCb1(joint_id, &callback, &ground);
            if (callback != NULL) {
                callback(ground, joint_id, coll, coll->x50, 2, 0.0F);
            }
        }
    } else if (kind == CollLine_Ceiling) {
        joint_id = mpJointFromLine(line_id);
        if (joint_id != -1) {
            Ground* ground = NULL;
            mpLib_Callback callback;
            mpJointGetCb2(joint_id, &callback, &ground);
            if (callback != NULL) {
                callback(ground, joint_id, coll, coll->x50, 0, 0.0F);
            }
        }
    }
#elif SOLUTION == 1
    enum_t kind = mpLineGetKind(line_id);

    if (kind == CollLine_Floor) {
        mpColl_80043268(coll, line_id, false, 0.0F);
    } else if (kind == CollLine_Ceiling) {
        mpCollEnd_inline2(coll, line_id, false, 0.0F);
    }
#endif
}
#undef SOLUTION

void mpColl_80043670(CollData* coll)
{
    coll->x130_flags |= CollData_X130_Clear;
}

void mpColl_80043680(CollData* coll, Vec3* arg1)
{
    coll->cur_pos = *arg1;
    coll->prev_pos = coll->cur_pos;
    coll->last_pos = coll->prev_pos;
    coll->x130_flags |= CollData_X130_Clear;
}

void mpCollSetFacingDir(CollData* coll, int facing_dir)
{
    coll->facing_dir = facing_dir;
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
    if (coll->ecb_source.kind == ECBSource_Fixed) {
        if (var_f1 > M_TAU) {
            var_f1 -= M_TAU;
        } else if (var_f1 < -M_TAU) {
            var_f1 += M_TAU;
        }
        coll->ecb_source.angle = var_f1;
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

bool mpColl_80043754(mpColl_Callback cb, CollData* coll, u32 flags)
{
    Vec3 vel;

    u8 _[4];

    float dist_right_x;
    float dist_right_y;
    float x;
    float y;
    float dist_left_x;
    float dist_top_y;
    s32 step;  // r31
    s32 steps; // r30
    bool ret;

    lbVector_Diff(&coll->cur_pos, &coll->last_pos, &vel);
    x = ABS(vel.x);
    y = ABS(vel.y);

    dist_left_x = coll->desired_ecb.left.x - coll->ecb.left.x;
    // if (dist_left_x < 0) dist_left_x = -dist_left_x;
    dist_left_x = ABS(dist_left_x);

    dist_right_x = coll->desired_ecb.right.x - coll->ecb.right.x;
    if (dist_right_x < 0) {
        dist_right_x = -dist_right_x;
    }

    if (dist_left_x < dist_right_x) {
        dist_left_x = dist_right_x;
    }

    dist_top_y = coll->desired_ecb.top.y - coll->ecb.top.y;
    // if (dist_top_y < 0) dist_top_y = -dist_top_y;
    dist_top_y = ABS(dist_top_y);

    dist_right_y = coll->desired_ecb.right.y - coll->ecb.right.y;
    if (dist_right_y < 0) {
        dist_right_y = -dist_right_y;
    }

    if (dist_top_y < dist_right_y) {
        dist_top_y = dist_right_y;
    }

    x = max_inline(x, dist_left_x);
    y = max_inline(y, dist_top_y);
    x = max_inline(x, y);

    if (x > flt_804D7FD8) {       // 6.0F float order hack
        steps = x / flt_804D7FD8; // 6.0F float order hack
        steps = steps + 1;
        vel.x /= steps;
        vel.y /= steps;
        vel.z /= steps;
    } else {
        steps = 1;
    }
    step = 0;
    coll->cur_pos = coll->last_pos;
    coll->x34_flags.b5 = 0;
    while ((step < steps) && !coll->x34_flags.b5) {
        mpCollInterpolateECB(coll, 1.0F / (steps - step));
        coll->prev_pos = coll->cur_pos;
        lbVector_Add(&coll->cur_pos, &vel);
        mpCollCheckBounding(coll, flags);
        ret = (*cb)(coll, flags);
        mpUncheckBounding();
        step += 1;
        coll->x38 = mpColl_804D64AC;
    }
    return ret;
}

// 800439FC https://decomp.me/scratch/T1yAJ
void mpColl_800439FC(CollData* coll)
{
    float right_dx; // f31
    float f1;
    float f2;
    float right_x;
    float right_y;
    Vec3 sp10;
    float y;

    right_x = coll->cur_pos.x + coll->ecb.right.x;
    right_y = coll->cur_pos.y + coll->ecb.right.y;
    right_dx = ABS(coll->ecb.right.x);

    // recalculate ceiling direction from its normal
    f1 = (coll->ceiling.normal.y * right_dx) + right_x;
    f2 = -(coll->ceiling.normal.x * right_dx) + right_y;
    if (!mpCheckLeftWall(f1, f2, right_x, right_y, &coll->contact, NULL, NULL,
                         NULL, coll->joint_id_skip, coll->joint_id_only))
    {
        return;
    }

    sp10.x = coll->contact.x - right_dx;
    sp10.y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpLib_8004E090_Ceiling(coll->ceiling.index, &sp10, &y,
                               &coll->ceiling.flags,
                               &coll->ceiling.normal) == -1)
    {
        return;
    }

    coll->cur_pos.y += y;
    coll->cur_pos.x = sp10.x;
}

void mpColl_80043ADC(CollData* coll)
{
    float left_dx;
    float f1;
    float f2;
    float left_x;
    float left_y;
    Vec3 sp10;
    float y;

    left_x = coll->cur_pos.x + coll->ecb.left.x;
    left_y = coll->cur_pos.y + coll->ecb.left.y;
    left_dx = ABS(coll->ecb.left.x);

    // recalculate ceiling direction from its normal
    f1 = -(coll->ceiling.normal.y * left_dx) + left_x;
    f2 = (coll->ceiling.normal.x * left_dx) + left_y;
    if (!mpCheckRightWall(f1, f2, left_x, left_y, &coll->contact, NULL, NULL,
                          NULL, coll->joint_id_skip, coll->joint_id_only))
    {
        return;
    }

    sp10.x = coll->contact.x + left_dx;
    sp10.y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpLib_8004E090_Ceiling(coll->ceiling.index, &sp10, &y,
                               &coll->ceiling.flags,
                               &coll->ceiling.normal) == -1)
    {
        return;
    }

    coll->cur_pos.y += y;
    coll->cur_pos.x = sp10.x;
}

bool mpColl_80043BBC(CollData* coll, int* line_id_out)
{
    int line_id = mpLinePrevNonFloor(coll->floor.index);
    float bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    float bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    float right_x = coll->cur_pos.x + coll->ecb.right.x;
    float right_y = coll->cur_pos.y + coll->ecb.right.y;
    int wall_id;

    if (mpCheckLeftWall(bottom_x, bottom_y, right_x, right_y, NULL, &wall_id,
                        NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only) &&
        wall_id != line_id)
    {
        *line_id_out = wall_id;
        return true;
    }

    return false;
}

void mpColl_80043C6C(CollData* coll, int line_id, bool ignore_bottom)
{
    float f1;
    float f2;
    float y; // sp30
    float right_dx;
    Vec3 pos;    // sp20
    int wall_id; // sp1C

    right_dx = ABS(coll->ecb.right.x);
    pos.x = coll->cur_pos.x + coll->ecb.right.x;
    pos.y = coll->cur_pos.y + coll->ecb.right.y;
    if (mpLib_8004E398_LeftWall(line_id, &pos, NULL, NULL, NULL) != -1) {
        // recalculate floor direction from its normal
        float floor_x = -(coll->floor.normal.y * right_dx) + pos.x;
        float floor_y = (coll->floor.normal.x * right_dx) + pos.y;
        if (mpCheckLeftWall(floor_x, floor_y, pos.x, pos.y, &coll->contact,
                            &wall_id, NULL, NULL, coll->joint_id_skip,
                            coll->joint_id_only))
        {
            pos.x = coll->contact.x - right_dx;
            if (ignore_bottom) {
                pos.y = coll->cur_pos.y;
            } else {
                pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
            }
            if (mpLib_8004DD90_Floor(coll->floor.index, &pos, &y,
                                     &coll->floor.flags,
                                     &coll->floor.normal) != -1)
            {
                coll->cur_pos.y += y;
                coll->cur_pos.x = pos.x;
            }
        }
    } else {
        mpLeftWallGetTop(line_id, &pos);
        f1 = pos.x - 2.0F;
        f2 = pos.y;
        pos.x = -((2.0F * right_dx) - f1);
        pos.y = -((2.0F * (coll->ecb.right.y - coll->ecb.bottom.y)) - f2);
        if (mpCheckFloor(f1, f2, pos.x, pos.y, 0.0F, &coll->contact, NULL,
                         NULL, NULL, coll->floor_skip, coll->joint_id_skip,
                         coll->joint_id_only, NULL, NULL))
        {
            pos.x = coll->contact.x;
            if (ignore_bottom) {
                pos.y = coll->cur_pos.y;
            } else {
                pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
            }
            if (mpLib_8004DD90_Floor(coll->floor.index, &pos, &y,
                                     &coll->floor.flags,
                                     &coll->floor.normal) != -1)
            {
                coll->cur_pos.y += y;
                coll->cur_pos.x = pos.x;
            }
        }
    }
}

bool mpColl_80043E90(CollData* coll, int* line_id_out)
{
    int line_id = mpLineNextNonFloor(coll->floor.index);
    float bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    float bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    float left_x = coll->cur_pos.x + coll->ecb.left.x;
    float left_y = coll->cur_pos.y + coll->ecb.left.y;
    int wall_id;

    if (mpCheckRightWall(bottom_x, bottom_y, left_x, left_y, NULL, &wall_id,
                         NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only) &&
        wall_id != line_id)
    {
        *line_id_out = wall_id;
        return true;
    }

    return false;
}

void mpColl_80043F40(CollData* coll, int line_id, bool ignore_bottom)
{
    float f1;
    float f2;
    float y; // sp30
    float left_dx;
    Vec3 pos;    // sp20
    int wall_id; // sp1C

    left_dx = ABS(coll->ecb.left.x);
    pos.x = coll->cur_pos.x + coll->ecb.left.x;
    pos.y = coll->cur_pos.y + coll->ecb.left.y;
    if (mpLib_8004E684_RightWall(line_id, &pos, NULL, NULL, NULL) != -1) {
        // recalculate floor direction from its normal
        float floor_x = (coll->floor.normal.y * left_dx) + pos.x;
        float floor_y = -(coll->floor.normal.x * left_dx) + pos.y;
        if (mpCheckRightWall(floor_x, floor_y, pos.x, pos.y, &coll->contact,
                             &wall_id, NULL, NULL, coll->joint_id_skip,
                             coll->joint_id_only))
        {
            pos.x = coll->contact.x + left_dx;
            if (ignore_bottom) {
                pos.y = coll->cur_pos.y;
            } else {
                pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
            }
            if (mpLib_8004DD90_Floor(coll->floor.index, &pos, &y,
                                     &coll->floor.flags,
                                     &coll->floor.normal) != -1)
            {
                coll->cur_pos.y += y;
                coll->cur_pos.x = pos.x;
            }
        }
    } else {
        mpRightWallGetTop(line_id, &pos);
        f1 = 2.0F + pos.x;
        f2 = pos.y;
        // 2.0 * (ecb bottom -> ecb left).normal() + ecb left
        pos.x = 2.0F * left_dx + f1;
        pos.y = -(2.0F * (coll->ecb.left.y - coll->ecb.bottom.y)) + f2;
        if (mpCheckFloor(f1, f2, pos.x, pos.y, 0.0F, &coll->contact, NULL,
                         NULL, NULL, coll->floor_skip, coll->joint_id_skip,
                         coll->joint_id_only, NULL, NULL))
        {
            pos.x = coll->contact.x;
            if (ignore_bottom) {
                pos.y = coll->cur_pos.y;
            } else {
                pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
            }
            if (mpLib_8004DD90_Floor(coll->floor.index, &pos, &y,
                                     &coll->floor.flags,
                                     &coll->floor.normal) != -1)
            {
                coll->cur_pos.x = pos.x;
                coll->cur_pos.y += y;
            }
        }
    }
}

bool mpColl_80044164(CollData* cd, int* p_ledge_id)
{
    float left;
    float bottom;
    float right;
    float top;

    bool grabbed_ledge;
    bool already_checked;
    int ledge_id;

    u8 _[8];
    Vec3 edge;   // sp14
    int line_id; // sp10

    float half_height = 0.5F * cd->ledge_snap_height;
    float snap_x = cd->ledge_snap_x;
    float snap_y = cd->ledge_snap_y;

    if (cd->prev_pos.x < cd->cur_pos.x) {
        left = cd->prev_pos.x;
        right = snap_x + (cd->cur_pos.x + cd->ecb.right.x);
    } else {
        left = cd->cur_pos.x;
        right = snap_x + (cd->prev_pos.x + cd->ecb.right.x);
    }

    if (cd->prev_pos.y < cd->cur_pos.y) {
        bottom = (cd->prev_pos.y + snap_y) - half_height;
        top = half_height + (cd->cur_pos.y + snap_y);
    } else {
        bottom = (cd->cur_pos.y + snap_y) - half_height;
        top = half_height + (cd->prev_pos.y + snap_y);
    }

    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck(left, bottom, right, top);
    }
    ledge_id =
        mpLib_80051BA8_Floor(&cd->contact, cd->floor_skip, cd->joint_id_skip,
                             cd->joint_id_only, 1, left, bottom, right, top);
    if (ledge_id != -1 &&
        (mpFloorGetLeft(ledge_id, &edge), cd->contact.x - edge.x < 5.0F) &&
        cd->cur_pos.x + cd->ecb.bottom.x < edge.x &&
        cd->cur_pos.y + cd->ecb.bottom.y < edge.y &&
        (cd->cur_pos.y + cd->ecb.bottom.y > cd->contact.y ||
         ((!mpCheckMultiple(cd->cur_pos.x + cd->ecb.top.x,
                            cd->cur_pos.y + cd->ecb.top.y, cd->contact.x,
                            cd->contact.y, NULL, &line_id, NULL, NULL, 6,
                            cd->joint_id_skip, cd->joint_id_only) ||
           mpJointFromLine(ledge_id) == mpJointFromLine(line_id)) &&
          (!mpCheckMultiple(cd->cur_pos.x + cd->ecb.bottom.x,
                            -2.0F + (cd->cur_pos.y + cd->ecb.bottom.y),
                            cd->contact.x, cd->contact.y, NULL, &line_id, NULL,
                            NULL, 6, cd->joint_id_skip, cd->joint_id_only) ||
           mpJointFromLine(ledge_id) == mpJointFromLine(line_id)))))
    {
        if (p_ledge_id != NULL) {
            *p_ledge_id = ledge_id;
        }
        grabbed_ledge = true;
    } else {
        grabbed_ledge = false;
    }

    if (!already_checked) {
        mpUncheckBounding();
    }

    return grabbed_ledge;
}

bool mpColl_800443C4(CollData* cd, int* p_ledge_id)
{
    float left;
    float bottom;
    float right;
    float top;

    bool grabbed_ledge;
    bool already_checked;
    int ledge_id;

    u8 _[8];
    Vec3 edge;   // sp14
    int line_id; // sp10

    float half_height = 0.5F * cd->ledge_snap_height;
    float snap_x = cd->ledge_snap_x;
    float snap_y = cd->ledge_snap_y;
    snap_x = -snap_x;
    if (cd->prev_pos.x > cd->cur_pos.x) {
        right = cd->prev_pos.x;
        left = snap_x + (cd->cur_pos.x + cd->ecb.left.x);
    } else {
        right = cd->cur_pos.x;
        left = snap_x + (cd->prev_pos.x + cd->ecb.left.x);
    }

    if (cd->prev_pos.y < cd->cur_pos.y) {
        bottom = (cd->prev_pos.y + snap_y) - half_height;
        top = half_height + (cd->cur_pos.y + snap_y);
    } else {
        bottom = (cd->cur_pos.y + snap_y) - half_height;
        top = half_height + (cd->prev_pos.y + snap_y);
    }
    already_checked = mpCheckedBounding();
    if (!already_checked) {
        mpBoundingCheck(left, bottom, right, top);
    }
    ledge_id =
        mpLib_80051BA8_Floor(&cd->contact, cd->floor_skip, cd->joint_id_skip,
                             cd->joint_id_only, -1, left, bottom, right, top);
    if (ledge_id != -1 &&
        (mpFloorGetRight(ledge_id, &edge), edge.x - cd->contact.x < 5.0F) &&
        cd->cur_pos.x + cd->ecb.bottom.x > edge.x &&
        cd->cur_pos.y + cd->ecb.bottom.y < edge.y &&
        (cd->cur_pos.y + cd->ecb.bottom.y > cd->contact.y ||
         ((!mpCheckMultiple(cd->cur_pos.x + cd->ecb.top.x,
                            cd->cur_pos.y + cd->ecb.top.y, cd->contact.x,
                            cd->contact.y, NULL, &line_id, NULL, NULL, 10,
                            cd->joint_id_skip, cd->joint_id_only) ||
           mpJointFromLine(ledge_id) == mpJointFromLine(line_id)) &&
          (!mpCheckMultiple(cd->cur_pos.x + cd->ecb.bottom.x,
                            -2.0F + (cd->cur_pos.y + cd->ecb.bottom.y),
                            cd->contact.x, cd->contact.y, NULL, &line_id, NULL,
                            NULL, 10, cd->joint_id_skip, cd->joint_id_only) ||
           mpJointFromLine(ledge_id) == mpJointFromLine(line_id)))))
    {
        if (p_ledge_id != NULL) {
            *p_ledge_id = ledge_id;
        }
        grabbed_ledge = true;
    } else {
        grabbed_ledge = false;
    }
    if (!already_checked) {
        mpUncheckBounding();
    }
    return grabbed_ledge;
}

bool mpColl_80044628_Floor(CollData* coll, bool (*cb)(Fighter_GObj*, int),
                           Fighter_GObj* gobj, int left_right)
{
    float y;
    Vec3 bottom; // sp2C
    Vec3 prev_bottom;
    int line_id;
    bool hit_floor; // r3

    prev_bottom.x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_bottom.y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom.x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom.y = coll->cur_pos.y + coll->ecb.bottom.y;

    if (coll->x38 != mpColl_804D64AC) {
        hit_floor = mpCheckFloorRemap(
            prev_bottom.x, prev_bottom.y, bottom.x, bottom.y, 0.0F,
            &coll->contact, &coll->floor.index, &coll->floor.flags,
            &coll->floor.normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, cb, gobj);
    } else {
        hit_floor = mpCheckFloor(
            prev_bottom.x, prev_bottom.y, bottom.x, bottom.y, 0.0F,
            &coll->contact, &coll->floor.index, &coll->floor.flags,
            &coll->floor.normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, cb, gobj);
    }

    if (hit_floor) {
        if (!(coll->floor.flags & LINE_FLAG_PLATFORM) ||
            coll->floor.index != coll->floor_skip)
        {
            coll->env_flags |= Collide_FloorPush;
            coll->env_flags |= Collide_FloorHug;
            return true;
        }
    }

    if ((left_right & 1 &&
         (line_id = mpLinePrevNonLeftWall(coll->left_facing_wall.index),
          line_id != -1)) ||
        (left_right & 2 &&
         (line_id = mpLineNextNonRightWall(coll->right_facing_wall.index),
          line_id != -1)))
    {
        if (mpLib_80054ED8(line_id) &&
            mpLineGetKind(line_id) == CollLine_Floor)
        {
            int floor_id = mpLib_8004DD90_Floor(
                line_id, &bottom, &y, &coll->floor.flags, &coll->floor.normal);

            if (floor_id != -1 && y > 0.0F) {
                coll->floor.index = floor_id;
                if (!(coll->floor.flags & LINE_FLAG_PLATFORM) ||
                    coll->floor.index != coll->floor_skip)
                {
                    if (cb == NULL || cb(gobj, coll->floor.index)) {
                        coll->env_flags |= Collide_FloorPush;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool mpColl_80044838_Floor(CollData* coll, bool ignore_bottom)
{
    Vec3 bottom; // sp20
    float y;     // sp1C
    Vec3 edge;   // sp10
    int line_id;

    if (ignore_bottom) {
        bottom.x = coll->cur_pos.x;
        bottom.y = coll->cur_pos.y;
    } else {
        bottom.x = coll->cur_pos.x + coll->ecb.bottom.x;
        bottom.y = coll->cur_pos.y + coll->ecb.bottom.y;
    }

    line_id = mpLib_8004DD90_Floor(coll->floor.index, &bottom, &y,
                                   &coll->floor.flags, &coll->floor.normal);
    if (line_id != -1) {
        coll->floor.index = line_id;
        coll->cur_pos.y += y;
    } else {
        mpFloorGetLeft(coll->floor.index, &edge);
        if (edge.x <= bottom.x) {
            mpFloorGetRight(coll->floor.index, &edge);
        }
        coll->cur_pos.x = edge.x - coll->ecb.bottom.x;
        coll->cur_pos.y = edge.y - coll->ecb.bottom.y;
        line_id =
            mpLib_8004DD90_Floor(coll->floor.index, &edge, NULL,
                                 &coll->floor.flags, &coll->floor.normal);
        if (line_id != -1) {
            coll->floor.index = line_id;
        }
    }

    return true;
}

bool mpColl_80044948_Floor(CollData* coll)
{
    Vec3 bottom; // sp1C
    float y;     // sp18
    Vec3 edge;   // spC
    bool hit_wall;
    int line_id;

    hit_wall = false;
    if (coll->ecb.bottom.y <= 0.0F) {
        bottom.x = coll->cur_pos.x + coll->ecb.bottom.x;
        bottom.y = coll->cur_pos.y + coll->ecb.bottom.y;
    } else {
        bottom.x = coll->cur_pos.x;
        bottom.y = coll->cur_pos.y;
    }
    line_id = mpLib_8004DD90_Floor(coll->floor.index, &bottom, &y,
                                   &coll->floor.flags, &coll->floor.normal);
    if (line_id != -1) {
        coll->floor.index = line_id;
        hit_wall = true;
        coll->cur_pos.y += y;
    } else {
        mpFloorGetLeft(coll->floor.index, &edge);
        if (bottom.x < edge.x) {
            line_id = mpLinePrevNonFloor(coll->floor.index);
            if (line_id != -1 && mpLineGetKind(line_id) == CollLine_RightWall)
            {
                hit_wall = true;
            }
        } else {
            mpFloorGetRight(coll->floor.index, &edge);
            line_id = mpLineNextNonFloor(coll->floor.index);
            if (line_id != -1 && mpLineGetKind(line_id) == CollLine_LeftWall) {
                hit_wall = true;
            }
        }
        coll->cur_pos.y = edge.y - coll->ecb.bottom.y;
        if (hit_wall) {
            coll->cur_pos.x = edge.x;
            line_id =
                mpLib_8004DD90_Floor(coll->floor.index, &edge, NULL,
                                     &coll->floor.flags, &coll->floor.normal);
            if (line_id != -1) {
                coll->floor.index = line_id;
            } else {
                OSReport("%s:%d: Error:oioi... id=%d\n", __FILE__, 2488,
                         coll->floor.index);
            }
        }
    }

    return hit_wall;
}

bool mpColl_80044AD8_Ceiling(CollData* coll, int left_right)
{
    float y;
    Vec3 top;
    Vec3 prev_top;
    int ceiling_id;
    int line_id;
    int hit_ceiling;

    prev_top.x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_top.y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top.x = coll->cur_pos.x + coll->ecb.top.x;
    top.y = coll->cur_pos.y + coll->ecb.top.y;
    if (coll->x38 != mpColl_804D64AC) {
        hit_ceiling = mpCheckCeilingRemap(
            prev_top.x, prev_top.y, top.x, top.y, &coll->contact,
            &coll->ceiling.index, &coll->ceiling.flags, &coll->ceiling.normal,
            coll->joint_id_skip, coll->joint_id_only);
    } else {
        hit_ceiling = mpCheckCeiling(
            prev_top.x, prev_top.y, top.x, top.y, &coll->contact,
            &coll->ceiling.index, &coll->ceiling.flags, &coll->ceiling.normal,
            coll->joint_id_skip, coll->joint_id_only);
    }
    if (hit_ceiling) {
        coll->env_flags |= Collide_CeilingPush;
        coll->env_flags |= Collide_CeilingHug;
        return true;
    }

    if (((left_right & 1 && (line_id = mpLineNextNonLeftWall(
                                 coll->left_facing_wall.index)) != -1) ||
         (left_right & 2 && (line_id = mpLinePrevNonRightWall(
                                 coll->right_facing_wall.index)) != -1)) &&
        mpLib_80054ED8(line_id) && mpLineGetKind(line_id) == CollLine_Ceiling)
    {
        ceiling_id = mpLib_8004E090_Ceiling(
            line_id, &top, &y, &coll->ceiling.flags, &coll->ceiling.normal);
        if (ceiling_id != -1 && y < 0.0F) {
            coll->ceiling.index = ceiling_id;
            coll->env_flags |= Collide_CeilingPush;
            return true;
        }
    }

    return false;
}

bool mpColl_80044C74_Ceiling(CollData* coll)
{
    Vec3 top;         // sp1C
    float y;          // sp18
    Vec3 ceiling_end; // spC
    int line_id;
    bool hit_wall; // r30

    top.x = coll->cur_pos.x + coll->ecb.top.x;
    top.y = coll->cur_pos.y + coll->ecb.top.y;
    line_id =
        mpLib_8004E090_Ceiling(coll->ceiling.index, &top, &y,
                               &coll->ceiling.flags, &coll->ceiling.normal);

    if (line_id != -1) {
        coll->ceiling.index = line_id;
        coll->cur_pos.y += y;
    } else {
        hit_wall = false;
        mpCeilingGetLeft(coll->ceiling.index, &ceiling_end);
        if (top.x <= ceiling_end.x) {
            line_id = mpLineNextNonCeiling(coll->ceiling.index);
            if (line_id != -1 && mpLib_80054ED8(line_id) &&
                mpLineGetKind(line_id) == CollLine_RightWall)
            {
                hit_wall = true;
            }
        } else {
            mpCeilingGetRight(coll->ceiling.index, &ceiling_end);
            line_id = mpLinePrevNonCeiling(coll->ceiling.index);
            if (line_id != -1 && mpLib_80054ED8(line_id) &&
                mpLineGetKind(line_id) == CollLine_LeftWall)
            {
                hit_wall = true;
            }
        }
        coll->cur_pos.y = ceiling_end.y - coll->ecb.top.y;
        if (hit_wall) {
            coll->cur_pos.x = ceiling_end.x;
            line_id = mpLib_8004E090_Ceiling(coll->ceiling.index, &ceiling_end,
                                             NULL, &coll->ceiling.flags,
                                             &coll->ceiling.normal);
            if (line_id != -1) {
                coll->ceiling.index = line_id;
            } else {
                OSReport("%s:%d: oioi...\n", __FILE__, 2620);
            }
        }
    }

    return true;
}

static inline bool mpColl_RightWall_inline2(CollData* coll, float ax, float ay,
                                            float bx, float by,
                                            int* line_id_out)
{
    if (coll->x38 != mpColl_804D64AC) {
        return mpCheckRightWallRemap(ax, ay, bx, by, NULL, line_id_out, NULL,
                                     NULL, coll->joint_id_skip,
                                     coll->joint_id_only);
    }
    return mpCheckRightWall(ax, ay, bx, by, NULL, line_id_out, NULL, NULL,
                            coll->joint_id_skip, coll->joint_id_only);
}

bool mpColl_80044E10_RightWall(CollData* coll)
{
    int line_id;
    float left_x;      // f31
    float left_y;      // f30
    float prev_left_x; // f29
    float prev_left_y; // f28
    float vertical_y;  // f27
    float vertical_x;  // f26
    float prev_x;      // f1
    float prev_y;      // f2
    float top_x;       // f3
    float top_y;       // f4
    float bottom_x;    // f3
    float bottom_y;    // f4
    bool hit_wall;
    PAD_STACK(0x14);

    hit_wall = false;
    mpColl_804D6488 = 0;

    left_x = coll->cur_pos.x + coll->ecb.left.x;
    left_y = coll->cur_pos.y + coll->ecb.left.y;
    prev_x = coll->prev_pos.x + coll->prev_ecb.left.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.left.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, left_x, left_y,
                                 &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
        coll->env_flags |= Collide_RightWallHug;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, bottom_x, bottom_y,
                                 &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, top_x, top_y, &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    vertical_x = coll->cur_pos.x + coll->ecb.bottom.x;
    vertical_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckRightWall(vertical_x, vertical_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
        prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
        prev_left_x = coll->prev_pos.x + coll->prev_ecb.left.x;
        prev_left_y = coll->prev_pos.y + coll->prev_ecb.left.y;
        if (mpLib_800511A4_RightWall(prev_x, prev_y, prev_left_x, prev_left_y,
                                     vertical_x, vertical_y, left_x, left_y,
                                     &line_id, coll->joint_id_skip,
                                     coll->joint_id_only))
        {
            mpColl_RightWall_inline(line_id);
            hit_wall = true;
        }
    }

    vertical_x = coll->cur_pos.x + coll->ecb.top.x;
    vertical_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckRightWall(vertical_x, vertical_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
        float prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
        if (mpLib_800511A4_RightWall(prev_left_x, prev_left_y, prev_top_x,
                                     prev_top_y, left_x, left_y, vertical_x,
                                     vertical_y, &line_id, coll->joint_id_skip,
                                     coll->joint_id_only))
        {
            mpColl_RightWall_inline(line_id);
            hit_wall = true;
        }
    }

    if (hit_wall) {
        coll->env_flags |= Collide_RightWallPush;
    }

    return hit_wall;
}

float mpColl_804D6490_max_x;
int mpColl_804D6494_line_id;
u32 mpColl_804D6498_flags;

bool mpColl_800454A4_RightWall(CollData* coll)
{
    u32 flags;
    Vec3 pos;
    Vec3 normal;
    int line_id;
    int i;

    mpColl_804D6490_max_x = -F32_MAX;
    for (i = 0; i < mpColl_804D6488; i++) {
        float top;
        float mid;
        float bot;
        float f27;
        float f26;
        float f2;
        float f3;
        float f4;
        float f5;
        float f6;
        int wall_id;
        int j;
        float x; // sp68
        wall_id = mpColl_80458810.right[i];

        mpRightWallGetTop(wall_id, &pos);
        if (pos.y < coll->cur_pos.y + coll->ecb.bottom.y) {
            if (mpColl_804D6490_max_x < pos.x) {
                line_id = mpLib_8004E684_RightWall(wall_id, &pos, NULL, &flags,
                                                   &normal);
                if (line_id != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = line_id;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        mpRightWallGetBottom(wall_id, &pos);
        if (pos.y > coll->cur_pos.y + coll->ecb.top.y) {
            if (mpColl_804D6490_max_x < pos.x) {
                line_id = mpLib_8004E684_RightWall(wall_id, &pos, NULL, &flags,
                                                   &normal);
                if (line_id != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = line_id;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }
            continue;
        }

        pos.x = coll->cur_pos.x + coll->ecb.bottom.x;
        pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.left.x;
        pos.y = coll->cur_pos.y + coll->ecb.left.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.top.x;
        pos.y = coll->cur_pos.y + coll->ecb.top.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        line_id = mpLinePrevNonRightWall(wall_id);
        if (line_id != -1 && mpLib_80054ED8(line_id) &&
            mpLineGetKind(line_id) & CollLine_Ceiling)
        {
            Vec3 top;
            Vec3 nrm;
            PAD_STACK(0x44);
            mpRightWallGetTop(wall_id, &top);
            if (pos.y > top.y) {
                line_id = mpLineNextNonCeiling(line_id);
                if (line_id != -1 && mpLib_80054ED8(line_id) &&
                    mpLineGetKind(line_id) & CollLine_RightWall)
                {
                    mpLineGetNormal(line_id, &nrm);
                    x = (pos.y - top.y) / nrm.x * -nrm.y + top.x - pos.x +
                        0.5F;
                    if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                        u32 temp = mpLineGetFlags(line_id);
                        mpColl_804D6490_max_x = coll->cur_pos.x + x;
                        mpColl_804D6494_line_id = line_id;
                        mpColl_804D6498_flags = temp;
                        mpColl_80458810.normal = nrm;
                    }
                }
            }
        }

        f6 = coll->ecb.left.x;
        f5 = coll->ecb.top.y;
        f4 = coll->ecb.left.y;
        f3 = coll->ecb.bottom.y;
        f2 = coll->cur_pos.y;
        top = f2 + f5;
        mid = f2 + f4;
        bot = f2 + f3;
        f27 = f6 / (f4 - f3);
        f26 = f6 / (f4 - f5);
        for (j = wall_id; j != -1 && (mpLineGetKind(j) & LINE_FLAG_KIND) ==
                                         CollLine_RightWall;
             j = mpLineGetNext(j))
        {
            mpLineGetV1Pos(j, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = f27 * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = f26 * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y < bot) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x < x) {
                flags = mpLineGetFlags(j);
                mpLineGetNormal(j, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = j;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        for (; wall_id != -1 &&
               (mpLineGetKind(wall_id) & LINE_FLAG_KIND) == CollLine_RightWall;
             wall_id = mpLineGetPrev(wall_id))
        {
            mpLineGetV0Pos(wall_id, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = f27 * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = f26 * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y > top) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x < x) {
                flags = mpLineGetFlags(wall_id);
                mpLineGetNormal(wall_id, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = wall_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }
    }
    flags = mpColl_804D6498_flags;
    normal = mpColl_80458810.normal;
    line_id = mpColl_804D6494_line_id;

    if (coll->cur_pos.x < mpColl_804D6490_max_x) {
        coll->cur_pos.x = mpColl_804D6490_max_x;
        coll->right_facing_wall.index = line_id;
        coll->right_facing_wall.flags = flags;
        coll->right_facing_wall.normal = normal;
        return true;
    }
    return false;
}

static inline bool mpColl_LeftWall_inline2(CollData* coll, float ax, float ay,
                                           float bx, float by,
                                           int* line_id_out)
{
    if (coll->x38 != mpColl_804D64AC) {
        return mpCheckLeftWallRemap(ax, ay, bx, by, NULL, line_id_out, NULL,
                                    NULL, coll->joint_id_skip,
                                    coll->joint_id_only);
    }
    return mpCheckLeftWall(ax, ay, bx, by, NULL, line_id_out, NULL, NULL,
                           coll->joint_id_skip, coll->joint_id_only);
}

bool mpColl_80045B74_LeftWall(CollData* coll)
{
    int line_id;
    float right_x;      // f31
    float right_y;      // f30
    float prev_right_x; // f29
    float prev_right_y; // f28
    float vertical_y;   // f26
    float vertical_x;   // f27
    float prev_x;       // f1
    float prev_y;       // f2
    float bottom_x;     // f3
    float bottom_y;     // f4
    float top_x;        // f3
    float top_y;        // f4
    bool hit_wall;
    PAD_STACK(0x8);

    hit_wall = false;
    mpColl_804D648C = 0;

    right_x = coll->cur_pos.x + coll->ecb.right.x;
    right_y = coll->cur_pos.y + coll->ecb.right.y;
    prev_x = coll->prev_pos.x + coll->prev_ecb.right.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.right.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, right_x, right_y,
                                &line_id))
    {
        mpColl_LeftWall_inline3(line_id, mpColl_80458810.left);
        hit_wall = true;
        coll->env_flags |= Collide_LeftWallHug;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, bottom_x, bottom_y,
                                &line_id))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, top_x, top_y, &line_id))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    vertical_x = coll->cur_pos.x + coll->ecb.bottom.x;
    vertical_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckLeftWall(vertical_x, vertical_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }
    if (!mpColl_IsEcbTiny) {
        prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
        prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
        prev_right_x = coll->prev_pos.x + coll->prev_ecb.right.x;
        prev_right_y = coll->prev_pos.y + coll->prev_ecb.right.y;
        if (mpLib_800515A0_LeftWall(prev_right_x, prev_right_y, prev_x, prev_y,
                                    right_x, right_y, vertical_x, vertical_y,
                                    &line_id, coll->joint_id_skip,
                                    coll->joint_id_only))
        {
            mpColl_LeftWall_inline(line_id);
            hit_wall = true;
        }
    }

    vertical_x = coll->cur_pos.x + coll->ecb.top.x;
    vertical_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckLeftWall(vertical_x, vertical_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
        float prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
        if (mpLib_800515A0_LeftWall(prev_top_x, prev_top_y, prev_right_x,
                                    prev_right_y, vertical_x, vertical_y,
                                    right_x, right_y, &line_id,
                                    coll->joint_id_skip, coll->joint_id_only))
        {
            mpColl_LeftWall_inline(line_id);
            hit_wall = true;
        }
    }

    if (hit_wall) {
        coll->env_flags |= Collide_LeftWallPush;
    }

    return hit_wall;
}

bool mpColl_80046224_LeftWall(CollData* coll)
{
    u8 _[4];
    u32 flags;
    Vec3 pos;
    Vec3 normal;
    int line_id;
    int* arr = mpColl_80458810.left;
    int i;

    mpColl_804D6490_max_x = F32_MAX;
    for (i = 0; i < mpColl_804D648C; arr++, i++) {
        float f30;
        float f29;
        float f28;
        float f27;
        float f26;
        float f4;
        float f5;
        float f6;
        float f7;
        int j;
        int wall_id;
        float x;

        wall_id = *arr;

        mpLeftWallGetTop(wall_id, &pos);
        if (pos.y < coll->cur_pos.y + coll->ecb.bottom.y) {
            if (mpColl_804D6490_max_x > pos.x) {
                int line_id = mpLib_8004E398_LeftWall(wall_id, &pos, NULL,
                                                      &flags, &normal);
                if (line_id != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = line_id;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        mpLeftWallGetBottom(wall_id, &pos);
        if (pos.y > coll->cur_pos.y + coll->ecb.top.y) {
            if (mpColl_804D6490_max_x > pos.x) {
                int line_id = mpLib_8004E398_LeftWall(wall_id, &pos, NULL,
                                                      &flags, &normal);
                if (line_id != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = line_id;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }
            continue;
        }

        pos.x = coll->cur_pos.x + coll->ecb.bottom.x;
        pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.right.x;
        pos.y = coll->cur_pos.y + coll->ecb.right.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.top.x;
        pos.y = coll->cur_pos.y + coll->ecb.top.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        line_id = mpLineNextNonLeftWall(wall_id);
        if (line_id != -1 && mpLib_80054ED8(line_id) &&
            mpLineGetKind(line_id) & CollLine_Ceiling)
        {
            Vec3 vec;
            mpLeftWallGetTop(wall_id, &vec);
            if (pos.y > vec.y) {
                line_id = mpLinePrevNonCeiling(line_id);
                if (line_id != -1 && mpLib_80054ED8(line_id) &&
                    mpLineGetKind(line_id) & CollLine_LeftWall)
                {
                    Vec3 nrm;
                    PAD_STACK(0x44);
                    mpLineGetNormal(line_id, &nrm);
                    x = (pos.y - vec.y) / -nrm.x * nrm.y + vec.x - pos.x -
                        0.5F;
                    if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                        u32 temp = mpLineGetFlags(line_id);
                        mpColl_804D6490_max_x = coll->cur_pos.x + x;
                        mpColl_804D6494_line_id = line_id;
                        mpColl_804D6498_flags = temp;
                        mpColl_80458810.normal = nrm;
                    }
                }
            }
        }

        f7 = coll->ecb.top.y;
        f6 = coll->ecb.right.y;
        f5 = coll->ecb.bottom.y;
        f4 = coll->ecb.right.x;
        f27 = (f4 - coll->ecb.bottom.x) / (f6 - f5);
        f26 = (f4 - coll->ecb.top.x) / (f6 - f7);
        f30 = coll->cur_pos.y + f7;
        f29 = coll->cur_pos.y + f6;
        f28 = coll->cur_pos.y + f5;
        for (j = wall_id; j != -1 && (mpLineGetKind(j) & LINE_FLAG_KIND) ==
                                         CollLine_LeftWall;
             j = mpLineGetPrev(j))
        {
            mpLineGetV0Pos(j, &pos);

            if (f28 <= pos.y && pos.y <= f29) {
                x = f27 * (pos.y - f28) + coll->ecb.bottom.x;
            } else if (f29 <= pos.y && pos.y <= f30) {
                x = f26 * (pos.y - f30) + coll->ecb.top.x;
            } else if (pos.y < f28) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x > x) {
                flags = mpLineGetFlags(j);
                mpLineGetNormal(j, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = j;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        for (; wall_id != -1 &&
               (mpLineGetKind(wall_id) & LINE_FLAG_KIND) == CollLine_LeftWall;
             wall_id = mpLineGetNext(wall_id))
        {
            mpLineGetV1Pos(wall_id, &pos);

            if (f28 <= pos.y && pos.y <= f29) {
                x = f27 * (pos.y - f28) + coll->ecb.bottom.x;
            } else if (f29 <= pos.y && pos.y <= f30) {
                x = f26 * (pos.y - f30) + coll->ecb.top.x;
            } else if (pos.y > f30) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x > x) {
                flags = mpLineGetFlags(wall_id);
                mpLineGetNormal(wall_id, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = wall_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }
    }

    line_id = mpColl_804D6494_line_id;
    flags = mpColl_804D6498_flags;
    normal = mpColl_80458810.normal;
    if (coll->cur_pos.x > mpColl_804D6490_max_x) {
        coll->cur_pos.x = mpColl_804D6490_max_x;
        coll->left_facing_wall.index = line_id;
        coll->left_facing_wall.flags = flags;
        coll->left_facing_wall.normal = normal;
        return true;
    }
    return false;
}

static inline void mpCollCeilingInline(CollData* coll)
{
    int right_wall_id;
    int left_wall_id;
    float top_x;
    float top_y;
    float side_x;
    float side_y;
    bool hit_wall;
    int non_ceiling_id = mpLineNextNonCeiling(coll->ceiling.index);
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    side_x = coll->cur_pos.x + coll->ecb.right.x;
    side_y = coll->cur_pos.y + coll->ecb.right.y;
    if (mpCheckLeftWall(top_x, top_y, side_x, side_y, NULL, &left_wall_id,
                        NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only) &&
        left_wall_id != non_ceiling_id)
    { // Collision_CheckLeftWallHug
        hit_wall = true;
    } else {
        hit_wall = false;
    }
    if (hit_wall) {
        mpColl_800439FC(coll); // Physics_LeftWallCeilingMultiCollide
    }

    non_ceiling_id = mpLinePrevNonCeiling(coll->ceiling.index);
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    side_x = coll->cur_pos.x + coll->ecb.left.x;
    side_y = coll->cur_pos.y + coll->ecb.left.y;
    if (mpCheckRightWall(top_x, top_y, side_x, side_y, NULL, &right_wall_id,
                         NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only) &&
        right_wall_id != non_ceiling_id)
    { // Collision_CheckRightWallHug
        hit_wall = true;
    } else {
        hit_wall = false;
    }
    if (hit_wall) {
        mpColl_80043ADC(coll); // Physics_RightWallCeilingMultiCollide
    }
}

static inline void mpCollFloorInline(CollData* coll, bool ecb_unlocked,
                                     u32 squeeze_flags)
{
    int wall_id;
    if (mpColl_80043BBC(coll, &wall_id))
    { // Physics_CheckFloorConnectedLeftWallHug
        // Physics_LeftWallFloorMultiCollide
        mpColl_80043C6C(coll, wall_id, ecb_unlocked && !(squeeze_flags & 1));
    }

    if (mpColl_80043E90(coll, &wall_id))
    { // Physics_CheckFloorConnectedRightWallHug
        // Physics_RightWallFloorMultiCollide
        mpColl_80043F40(coll, wall_id, ecb_unlocked && !(squeeze_flags & 1));
    }
}

bool mpColl_80046904(CollData* coll, u32 flags)
{                          // Physics_CollisionAirCallback
    bool prev_b6;          // r31
    int squeeze_flags;     // r30
    int old_squeeze_flags; // r29
    int squeeze_flags_all; // r28
    bool stay_airborne;    // r24
    int left_right_flags;  // r23
    bool platform_pass;    // r25
    bool touched_floor;    // r22
    PAD_STACK(0x8);

    platform_pass = flags & CollisionFlagAir_PlatformPassCallback;
    stay_airborne = flags & CollisionFlagAir_StayAirborne;

    left_right_flags = 0;
    touched_floor = false;
    squeeze_flags_all = 0;
    squeeze_flags = 0;

    do {
        bool r3;
        float x_after_collide_right;
        float x_after_collide_left;
        float y_after_collide_floor;
        float y_after_collide_ceiling;

        x_after_collide_right = 0.0F;
        old_squeeze_flags = squeeze_flags;
        x_after_collide_left = 0.0F;
        prev_b6 = coll->x34_flags.b6;
        squeeze_flags = 0;
        if (mpColl_80045B74_LeftWall(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224_LeftWall(coll)) { // Physics_LeftWallCollideAir
                left_right_flags |= 1;
                squeeze_flags |= 8;
            }
            x_after_collide_left = coll->cur_pos.x;
        }

        if (mpColl_80044E10_RightWall(coll)) { // Physics_RightWallCheckAir
            if (mpColl_800454A4_RightWall(coll))
            { // Physics_RightWallCollideAir
                left_right_flags |= 2;
                squeeze_flags |= 4;
            }
            x_after_collide_right = coll->cur_pos.x;
        }

        if (mpColl_80045B74_LeftWall(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224_LeftWall(coll)) { // Physics_LeftWallCollideAir
                left_right_flags |= 1;
                squeeze_flags |= 8;
            }
            x_after_collide_left = coll->cur_pos.x;
        }

        if (mpColl_80044E10_RightWall(coll)) { // Physics_RightWallCheckAir
            if (mpColl_800454A4_RightWall(coll))
            { // Physics_RightWallCollideAir
                left_right_flags |= 2;
                squeeze_flags |= 4;
            }
            x_after_collide_right = coll->cur_pos.x;
        }

        if ((squeeze_flags & 0b1100) == 0b1100) {
            mpCollSqueezeHorizontal(coll, true, x_after_collide_right,
                                    x_after_collide_left);
        }

        y_after_collide_ceiling = 0.0F;
        y_after_collide_floor = 0.0F;

        if (mpColl_80044AD8_Ceiling(coll, left_right_flags) &&
            mpColl_80044C74_Ceiling(coll))
        { // Physics_CeilingCheck, Physics_CeilingCollideAir
            mpCollCeilingInline(coll);

            squeeze_flags |= 1;
            y_after_collide_ceiling = coll->cur_pos.y;
        }

        if (platform_pass) {
            r3 = mpColl_80044628_Floor(
                coll, mpColl_804D64A0, mpColl_804D64A4,
                left_right_flags); // Physics_FloorCheckAir
        } else {
            r3 = mpColl_80044628_Floor(
                coll, NULL, NULL,
                left_right_flags); // Physics_FloorCheckAir
        }

        if (r3) {
            if (stay_airborne) {
                if (mpColl_80044948_Floor(coll))
                { // Physics_FloorCollideStayAirborne
                    mpCollFloorInline(coll, false, squeeze_flags);
                }
            } else {
                bool ecb_unlocked = false;

                if (coll->ecb.bottom.y > 0.0F) {
                    ecb_unlocked = true;
                }

                if (mpColl_80044838_Floor(coll, ecb_unlocked &&
                                                    !(squeeze_flags & 1)))
                { // Physics_SnapToFloorNoEdgePass
                    mpCollFloorInline(coll, ecb_unlocked, squeeze_flags);

                    coll->x34_flags.b5 = true;
                    touched_floor = true;
                }
            }

            y_after_collide_floor = coll->cur_pos.y;
            squeeze_flags |= 2;
            if (mpColl_80044AD8_Ceiling(coll, left_right_flags) &&
                mpColl_80044C74_Ceiling(coll))
            { // Physics_CeilingCheck, Physics_CeilingCollideAir
                mpCollCeilingInline(coll);

                squeeze_flags |= 1;
                y_after_collide_ceiling = coll->cur_pos.y;
            }
        }
        if ((squeeze_flags & 0b0011) == 0b0011) {
            bool airborne;
            if (touched_floor) {
                airborne = false;
            } else {
                airborne = true;
            }
            mpCollSqueezeVertical(coll, airborne, y_after_collide_ceiling,
                                  y_after_collide_floor);
        }
        squeeze_flags_all |= squeeze_flags;
    } while (prev_b6 != coll->x34_flags.b6 ||
             squeeze_flags != old_squeeze_flags);

    if (!touched_floor && flags & CollisionFlagAir_CanGrabLedge) {
        bool on_edge = coll->env_flags & Collide_LeftEdge ||
                       coll->env_flags & Collide_RightEdge;

        if (!on_edge && coll->cur_pos.y < coll->prev_pos.y) {
            if (coll->facing_dir == 1 || coll->facing_dir == 0) {
                if (mpColl_80044164(coll, &coll->ledge_id_left))
                { // Physics_CheckForLeftLedge
                    on_edge = true;
                    coll->env_flags |= Collide_LeftLedgeGrab;
                } else {
                    on_edge = false;
                }
                if (on_edge) {
                    coll->env_flags |= Collide_LeftLedgeGrab;
                }
            }
            if (coll->facing_dir == -1 || coll->facing_dir == 0) {
                if (mpColl_800443C4(coll, &coll->ledge_id_right))
                { // Physics_CheckForRightLedge
                    on_edge = true;
                    coll->env_flags |= Collide_RightLedgeGrab;
                } else {
                    on_edge = false;
                }
                if (on_edge) {
                    coll->env_flags |= Collide_RightLedgeGrab;
                }
            }
        }
    }

    if (!(squeeze_flags_all & 0b1000)) {
        coll->env_flags &= ~Collide_LeftWallMask;
    }

    if (!(squeeze_flags_all & 0b0100)) {
        coll->env_flags &= ~Collide_RightWallMask;
    }

    return touched_floor;
}

static inline bool mpColl_80046F78_inline(CollData* coll, int* line_id_out)
{
    if (coll->x38 != mpColl_804D64AC) {
        float prev_x = coll->prev_pos.x;
        float prev_y = coll->prev_pos.y;
        float x = coll->cur_pos.x;
        float y = coll->cur_pos.y;
        return mpCheckAllRemap(&coll->contact, line_id_out, NULL, NULL,
                               coll->joint_id_skip, coll->joint_id_only,
                               prev_x, prev_y, x, y);
    } else {
        float prev_x = coll->prev_pos.x;
        float prev_y = coll->prev_pos.y;
        float x = coll->cur_pos.x;
        float y = coll->cur_pos.y;
        return mpCheckAll(&coll->contact, line_id_out, NULL, NULL,
                          coll->joint_id_skip, coll->joint_id_only, prev_x,
                          prev_y, x, y);
    }
}

bool mpColl_80046F78(CollData* coll, u32 _)
{
    int line_id;
    float y; // sp10

    if (mpColl_80046F78_inline(coll, &line_id)) {
        enum_t kind = mpLineGetKind(line_id);
        if (kind == CollLine_Floor) {
            line_id =
                mpLib_8004DD90_Floor(line_id, &coll->contact, &y,
                                     &coll->floor.flags, &coll->floor.normal);
            if (line_id != -1) {
                coll->floor.index = line_id;
                coll->cur_pos.x = coll->contact.x;
                coll->cur_pos.y = coll->contact.y + y;
                coll->cur_pos.z = coll->contact.z;
                coll->env_flags |= Collide_FloorPush;
                return true;
            }
            return false;
        } else if (kind == CollLine_Ceiling) {
            line_id = mpLib_8004E090_Ceiling(line_id, &coll->contact, &y,
                                             &coll->ceiling.flags,
                                             &coll->ceiling.normal);
            if (line_id != -1) {
                coll->ceiling.index = line_id;
                coll->cur_pos.x = coll->contact.x;
                coll->cur_pos.y = coll->contact.y + y;
                coll->cur_pos.z = coll->contact.z;
                coll->env_flags |= Collide_CeilingPush;
                return true;
            }
            return false;
        } else if (kind == CollLine_LeftWall) {
            line_id = mpLib_8004E398_LeftWall(line_id, &coll->contact, &y,
                                              &coll->left_facing_wall.flags,
                                              &coll->left_facing_wall.normal);
            if (line_id != -1) {
                coll->left_facing_wall.index = line_id;
                coll->cur_pos.x = coll->contact.x + y;
                coll->cur_pos.y = coll->contact.y;
                coll->cur_pos.z = coll->contact.z;
                coll->env_flags |= Collide_LeftWallPush;
                return true;
            }
            return false;
        } else if (kind == CollLine_RightWall) {
            line_id = mpLib_8004E684_RightWall(
                line_id, &coll->contact, &y, &coll->right_facing_wall.flags,
                &coll->right_facing_wall.normal);
            if (line_id != -1) {
                coll->right_facing_wall.index = line_id;
                coll->cur_pos.x = coll->contact.x + y;
                coll->cur_pos.y = coll->contact.y;
                coll->cur_pos.z = coll->contact.z;
                coll->env_flags |= Collide_RightWallPush;
                return true;
            }
            return false;
        } else {
            HSD_ASSERT(3685, 0);
            return;
        }
    }
    return false;
}

static inline bool inline0(CollData* coll, int i, bool j)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->ecb.top.y - coll->ecb.bottom.y < 6.0F &&
        coll->ecb.right.y - coll->ecb.left.y < 6.0F)
    {
        mpColl_IsEcbTiny = true;
    } else {
        mpColl_IsEcbTiny = false;
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
    if (coll->ecb.top.y - coll->ecb.bottom.y < 6.0F &&
        coll->ecb.right.y - coll->ecb.left.y < 6.0F)
    {
        mpColl_IsEcbTiny = true;
    } else {
        mpColl_IsEcbTiny = false;
    }
    result = mpColl_80043754(mpColl_80046F78, coll, i);
    mpCollEnd(coll, result, true);
    return result;
}

static inline bool inline2(CollData* coll, int i)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->ecb.top.y - coll->ecb.bottom.y < 6.0F &&
        coll->ecb.right.y - coll->ecb.left.y < 6.0F)
    {
        mpColl_IsEcbTiny = true;
    } else {
        mpColl_IsEcbTiny = false;
    }
    result = mpColl_80043754((void*) mpColl_8004ACE4, coll, i);
    mpCollEnd(coll, result, false);
    return result;
}

static inline bool inline3(CollData* coll, int i)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->ecb.top.y - coll->ecb.bottom.y < 6.0F &&
        coll->ecb.right.y - coll->ecb.left.y < 6.0F)
    {
        mpColl_IsEcbTiny = true;
    } else {
        mpColl_IsEcbTiny = false;
    }
    result = mpColl_80043754(mpColl_8004C534, coll, i);
    mpCollEnd(coll, result, false);
    return result;
}

static inline bool inline1(CollData* coll, int i,
                           bool (*floor_cb)(Fighter_GObj*, int),
                           Fighter_GObj* gobj)
{
    bool result;
    coll->prev_env_flags = coll->env_flags;
    coll->env_flags = 0;
    if (coll->ecb.top.y - coll->ecb.bottom.y < 6.0F &&
        coll->ecb.right.y - coll->ecb.left.y < 6.0F)
    {
        mpColl_IsEcbTiny = true;
    } else {
        mpColl_IsEcbTiny = false;
    }
    mpColl_804D64A0 = floor_cb;
    mpColl_804D64A4 = gobj;
    result = mpColl_80043754(mpColl_80046904, coll, i);
    mpCollEnd(coll, result, true);
    return result;
}

bool mpColl_800471F8(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 6);
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
    mpColl_LoadECB_inline(coll, 6);
    return inline0(coll, 4, true);
}

bool mpColl_800474E0(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 5);
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
    mpColl_LoadECB_inline(coll, 6);
    return inline1(coll, 3, arg1, gobj);
}

bool mpColl_800477E0(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 6);
    return inline0(coll, 1, true);
}

bool mpColl_800478F4(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 5);
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
    mpColl_LoadECB_inline(coll, 6);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047BF4(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 0xA);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047D20(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 0x12);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    mpColl_80042384(coll);
    return inline1(coll, 2, arg1, arg2);
}

bool mpColl_80047E14(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 6);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_80047F40(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 0xA);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_8004806C(CollData* coll, bool (*arg1)(Fighter_GObj*, int),
                     Fighter_GObj* arg2)
{
    mpCollPrev(coll);
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 0x12);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    mpColl_80042384(coll);
    return inline1(coll, 6, arg1, arg2);
}

bool mpColl_80048160(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 0xA);
    return inline0(coll, 0, true);
}

bool mpColl_80048274(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 0xA);
    return inline0(coll, 1, true);
}

bool mpColl_80048388(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 0x12);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 1, true);
}

bool mpColl_80048464(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 0xA);
    return inline0(coll, 4, true);
}

bool mpColl_80048578(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 0x12);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 4, true);
}

bool mpColl_80048654(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 5);
    return inline0(coll, 0, true);
}

bool mpColl_80048768(CollData* coll)
{
    mpCollPrev(coll);
    if (coll->ecb_source.kind == ECBSource_JObj) {
        mpColl_LoadECB_JObj(coll, 0x12);
    } else {
        mpColl_LoadECB_Fixed(coll);
    }
    mpColl_80042384(coll);
    return inline0(coll, 0, true);
}

bool mpColl_80048844(CollData* coll, f32 arg1)
{
    mpCollPrev(coll);
    return inline4(coll, 0);
}

bool mpColl_800488F4(CollData* coll)
{
    Vec3 bottom; // sp30
    u8 _[0xC];
    float y; // sp20
    Vec3 edge;

    int floor_id;
    int line_id;
    int hit_wall;

    PAD_STACK(0x8);

    floor_id = coll->floor.index;
    bottom.x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom.y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (!mpLib_80054ED8(coll->floor.index) ||
        (mpLineGetKind(coll->floor.index) != CollLine_Floor))
    {
        return false;
    }
    line_id = mpLib_8004DD90_Floor(floor_id, &bottom, &y, &coll->floor.flags,
                                   &coll->floor.normal);
    if (line_id != -1) {
        coll->cur_pos.y += y;
        coll->floor.index = line_id;
        return true;
    }
    hit_wall = false;
    mpFloorGetLeft(floor_id, &edge);
    if (coll->cur_pos.x < edge.x) {
        int non_floor_id = mpLinePrevNonFloor(floor_id);
        if (non_floor_id != -1 && mpLib_80054ED8(non_floor_id) &&
            mpLineGetKind(non_floor_id) & CollLine_RightWall)
        {
            hit_wall = true;
        } else {
            coll->env_flags |= Collide_LeftLedgeSlip;
        }
    } else {
        mpFloorGetRight(floor_id, &edge);
        if (coll->cur_pos.x > edge.x) {
            int non_floor_id = mpLineNextNonFloor(floor_id);
            if (non_floor_id != -1 && mpLib_80054ED8(non_floor_id) &&
                mpLineGetKind(non_floor_id) & CollLine_LeftWall)
            {
                hit_wall = true;
            } else {
                coll->env_flags |= Collide_RightLedgeSlip;
            }
        }
    }
    if (hit_wall) {
        coll->cur_pos = edge;
        return true;
    }
    return false;
}

// maybe a grounded version of `mpColl_80044E10_RightWall`
bool mpColl_80048AB0_RightWall(CollData* coll)
{
    int line_id;
    float left_x;      // f31
    float left_y;      // f30
    float prev_left_x; // f29
    float prev_left_y; // f28
    float vertical_y;  // f26
    float vertical_x;  // f27
    float prev_x;      // f1
    float prev_y;      // f2
    float top_x;       // f3
    float top_y;       // f4
    float bottom_x;    // f3
    float bottom_y;    // f4
    bool hit_wall;
    int line_id1;
    int line_id2;

    hit_wall = false;
    mpColl_804D6488 = 0;

    if (mpLib_80054ED8(coll->floor.index)) {
        int temp;
        line_id1 = mpLib_80053394_Floor(coll->floor.index);
        temp = mpLib_800536CC_Floor(coll->floor.index);
        line_id = temp;
        line_id2 = temp != -1 ? mpLib_80053394_Floor(line_id) : -1;
    } else {
        line_id2 = -1;
        line_id1 = -1;
    }

    left_x = coll->cur_pos.x + coll->ecb.left.x;
    left_y = coll->cur_pos.y + coll->ecb.left.y;
    prev_x = coll->prev_pos.x + coll->prev_ecb.left.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.left.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, left_x, left_y,
                                 &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
        coll->env_flags |= Collide_RightWallHug;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, bottom_x, bottom_y,
                                 &line_id) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_RightWall_inline2(coll, prev_x, prev_y, top_x, top_y, &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    vertical_x = coll->cur_pos.x + coll->ecb.bottom.x;
    vertical_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckRightWall(vertical_x, vertical_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_bottom_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
        float prev_bottom_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
        prev_left_x = coll->prev_pos.x + coll->prev_ecb.left.x;
        prev_left_y = coll->prev_pos.y + coll->prev_ecb.left.y;
        if (mpLib_800511A4_RightWall(
                prev_bottom_x, prev_bottom_y, prev_left_x, prev_left_y,
                vertical_x, vertical_y, left_x, left_y, &line_id,
                coll->joint_id_skip, coll->joint_id_only) &&
            line_id != line_id1 && line_id != line_id2)
        {
            mpColl_RightWall_inline(line_id);
            hit_wall = true;
        }
    }

    vertical_x = coll->cur_pos.x + coll->ecb.top.x;
    vertical_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckRightWall(vertical_x, vertical_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
        float prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
        if (mpLib_800511A4_RightWall(prev_left_x, prev_left_y, prev_top_x,
                                     prev_top_y, left_x, left_y, vertical_x,
                                     vertical_y, &line_id, coll->joint_id_skip,
                                     coll->joint_id_only))
        {
            mpColl_RightWall_inline(line_id);
            hit_wall = true;
        }
    }

    if (hit_wall) {
        coll->env_flags |= Collide_RightWallPush;
    }

    return hit_wall;
}

bool mpColl_800491C8_RightWall(CollData* coll)
{
    u32 flags;
    Vec3 pos;
    Vec3 normal;
    int line_id;
    int i;

    mpColl_804D6490_max_x = -F32_MAX;
    for (i = 0; i < mpColl_804D6488; i++) {
        float top;
        float mid;
        float bot;
        float bot_y_to_x; // f28
        float top_y_to_x; // f27
        float bottom_y;   // f3
        float left_y;     // f4
        float top_y;      // f5
        float left_x;     // f6
        int j;
        int wall_id;
        float x;
        PAD_STACK(0x38);

        wall_id = mpColl_80458810.right[i];

        mpRightWallGetTop(wall_id, &pos);
        if (pos.y < (coll->cur_pos.y + coll->ecb.bottom.y)) {
            if (mpColl_804D6490_max_x < pos.x) {
                int r3 = mpLib_8004E684_RightWall(wall_id, &pos, NULL, &flags,
                                                  &normal);
                if (r3 != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = r3;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        mpRightWallGetBottom(wall_id, &pos);
        if (pos.y > (coll->cur_pos.y + coll->ecb.top.y)) {
            if (mpColl_804D6490_max_x < pos.x) {
                int r3 = mpLib_8004E684_RightWall(wall_id, &pos, NULL, &flags,
                                                  &normal);
                if (r3 != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = r3;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        pos.x = coll->cur_pos.x + coll->ecb.bottom.x;
        pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.left.x;
        pos.y = coll->cur_pos.y + coll->ecb.left.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.top.x;
        pos.y = coll->cur_pos.y + coll->ecb.top.y;
        line_id = mpLib_8004E684_RightWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x < coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        left_x = coll->ecb.left.x;
        top_y = coll->ecb.top.y;
        left_y = coll->ecb.left.y;
        bottom_y = coll->ecb.bottom.y;
        top = coll->cur_pos.y + top_y;
        mid = coll->cur_pos.y + left_y;
        bot = coll->cur_pos.y + bottom_y;
        bot_y_to_x = left_x / (left_y - bottom_y);
        top_y_to_x = left_x / (left_y - top_y);

        for (j = wall_id; j != -1 && (mpLineGetKind(j) & LINE_FLAG_KIND) ==
                                         CollLine_RightWall;
             j = mpLineGetNext(j))
        {
            mpLineGetV1Pos(j, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = bot_y_to_x * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = top_y_to_x * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y < bot) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x < x) {
                flags = mpLineGetFlags(j);
                mpLineGetNormal(j, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = j;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        for (; wall_id != -1 &&
               (mpLineGetKind(wall_id) & LINE_FLAG_KIND) == CollLine_RightWall;
             wall_id = mpLineGetPrev(wall_id))
        {
            mpLineGetV0Pos(wall_id, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = bot_y_to_x * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = top_y_to_x * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y > top) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x < x) {
                flags = mpLineGetFlags(wall_id);
                mpLineGetNormal(wall_id, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = wall_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }
    }
    line_id = mpColl_804D6494_line_id;
    flags = mpColl_804D6498_flags;
    normal = mpColl_80458810.normal;
    if (coll->cur_pos.x < mpColl_804D6490_max_x) {
        coll->cur_pos.x = mpColl_804D6490_max_x;
        coll->right_facing_wall.index = line_id;
        coll->right_facing_wall.flags = flags;
        coll->right_facing_wall.normal = normal;
        return true;
    }
    return false;
}

bool mpColl_80049778_LeftWall(CollData* coll)
{
    int line_id;
    float right_x;      // f31
    float right_y;      // f30
    float prev_right_x; // f29
    float prev_right_y; // f28
    float vertical_y;   // f26
    float vertical_x;   // f27
    float prev_x;       // f1
    float prev_y;       // f2
    float bottom_x;     // f3
    float bottom_y;     // f4
    float top_x;        // f3
    float top_y;        // f4
    bool hit_wall;
    int line_id1;
    int line_id2;

    hit_wall = false;
    mpColl_804D648C = 0;

    if (mpLib_80054ED8(coll->floor.index)) {
        int temp;
        line_id1 = mpLib_80053448_Floor(coll->floor.index);
        temp = mpLib_800534FC_Floor(coll->floor.index);
        line_id = temp;
        line_id2 = temp != -1 ? mpLib_80053448_Floor(line_id) : -1;
    } else {
        line_id2 = -1;
        line_id1 = -1;
    }

    right_x = coll->cur_pos.x + coll->ecb.right.x;
    right_y = coll->cur_pos.y + coll->ecb.right.y;
    prev_x = coll->prev_pos.x + coll->prev_ecb.right.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.right.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, right_x, right_y,
                                &line_id))
    {
        mpColl_LeftWall_inline3(line_id, mpColl_80458810.left);
        hit_wall = true;
        coll->env_flags |= Collide_LeftWallHug;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, bottom_x, bottom_y,
                                &line_id) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    prev_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_LeftWall_inline2(coll, prev_x, prev_y, top_x, top_y, &line_id))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    vertical_x = coll->cur_pos.x + coll->ecb.bottom.x;
    vertical_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckLeftWall(vertical_x, vertical_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_bottom_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
        float prev_bottom_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
        prev_right_x = coll->prev_pos.x + coll->prev_ecb.right.x;
        prev_right_y = coll->prev_pos.y + coll->prev_ecb.right.y;
        if (mpLib_800515A0_LeftWall(
                prev_right_x, prev_right_y, prev_bottom_x, prev_bottom_y,
                right_x, right_y, vertical_x, vertical_y, &line_id,
                coll->joint_id_skip, coll->joint_id_only) &&
            line_id != line_id1 && line_id != line_id2)
        {
            mpColl_LeftWall_inline(line_id);
            hit_wall = true;
        }
    }

    vertical_x = coll->cur_pos.x + coll->ecb.top.x;
    vertical_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckLeftWall(vertical_x, vertical_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    if (!mpColl_IsEcbTiny) {
        float prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
        float prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
        if (mpLib_800515A0_LeftWall(prev_top_x, prev_top_y, prev_right_x,
                                    prev_right_y, vertical_x, vertical_y,
                                    right_x, right_y, &line_id,
                                    coll->joint_id_skip, coll->joint_id_only))
        {
            mpColl_LeftWall_inline(line_id);
            hit_wall = true;
        }
    }

    if (hit_wall) {
        coll->env_flags |= Collide_LeftWallPush;
    }

    return hit_wall;
}

bool mpColl_80049EAC_LeftWall(CollData* coll)
{
    u32 flags;
    Vec3 pos;
    Vec3 normal;
    int line_id;
    int* arr = mpColl_80458810.left;
    int i;

    mpColl_804D6490_max_x = F32_MAX;
    for (i = 0; i < mpColl_804D6488; arr++, i++) {
        float top;
        float mid;
        float bot;
        float bot_y_to_x; // f28
        float top_y_to_x; // f27
        float bottom_y;   // f3
        float right_y;    // f4
        float top_y;      // f5
        float right_x;    // f6
        int j;
        int wall_id;
        float x;
        PAD_STACK(0x38);

        wall_id = *arr;

        mpLeftWallGetTop(wall_id, &pos);
        if (pos.y < (coll->cur_pos.y + coll->ecb.bottom.y)) {
            if (mpColl_804D6490_max_x > pos.x) {
                int r3 = mpLib_8004E398_LeftWall(wall_id, &pos, NULL, &flags,
                                                 &normal);
                if (r3 != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = r3;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        mpLeftWallGetBottom(wall_id, &pos);
        if (pos.y > (coll->cur_pos.y + coll->ecb.top.y)) {
            if (mpColl_804D6490_max_x > pos.x) {
                int r3 = mpLib_8004E398_LeftWall(wall_id, &pos, NULL, &flags,
                                                 &normal);
                if (r3 != -1) {
                    mpColl_804D6490_max_x = pos.x;
                    mpColl_804D6494_line_id = r3;
                    mpColl_804D6498_flags = flags;
                    mpColl_80458810.normal = normal;
                }
            }

            continue;
        }

        pos.x = coll->cur_pos.x + coll->ecb.bottom.x;
        pos.y = coll->cur_pos.y + coll->ecb.bottom.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.right.x;
        pos.y = coll->cur_pos.y + coll->ecb.right.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        pos.x = coll->cur_pos.x + coll->ecb.top.x;
        pos.y = coll->cur_pos.y + coll->ecb.top.y;
        line_id = mpLib_8004E398_LeftWall(wall_id, &pos, &x, &flags, &normal);
        if (line_id != -1) {
            if (mpColl_804D6490_max_x > coll->cur_pos.x + x) {
                mpColl_804D6490_max_x = coll->cur_pos.x + x;
                mpColl_804D6494_line_id = line_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        right_x = coll->ecb.right.x;
        top_y = coll->ecb.top.y;
        right_y = coll->ecb.right.y;
        bottom_y = coll->ecb.bottom.y;
        top = coll->cur_pos.y + top_y;
        mid = coll->cur_pos.y + right_y;
        bot = coll->cur_pos.y + bottom_y;
        bot_y_to_x = right_x / (right_y - bottom_y);
        top_y_to_x = right_x / (right_y - top_y);

        for (j = wall_id; j != -1 && (mpLineGetKind(j) & LINE_FLAG_KIND) ==
                                         CollLine_LeftWall;
             j = mpLineGetPrev(j))
        {
            mpLineGetV0Pos(j, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = bot_y_to_x * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = top_y_to_x * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y < bot) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x > x) {
                flags = mpLineGetFlags(j);
                mpLineGetNormal(j, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = j;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }

        for (; wall_id != -1 &&
               (mpLineGetKind(wall_id) & LINE_FLAG_KIND) == CollLine_LeftWall;
             wall_id = mpLineGetNext(wall_id))
        {
            mpLineGetV1Pos(wall_id, &pos);

            if (bot <= pos.y && pos.y <= mid) {
                x = bot_y_to_x * (pos.y - bot) + coll->ecb.bottom.x;
            } else if (mid <= pos.y && pos.y <= top) {
                x = top_y_to_x * (pos.y - top) + coll->ecb.top.x;
            } else if (pos.y > top) {
                break;
            } else {
                continue;
            }

            x = pos.x - x;
            if (mpColl_804D6490_max_x > x) {
                flags = mpLineGetFlags(wall_id);
                mpLineGetNormal(wall_id, &normal);
                mpColl_804D6490_max_x = x;
                mpColl_804D6494_line_id = wall_id;
                mpColl_804D6498_flags = flags;
                mpColl_80458810.normal = normal;
            }
        }
    }

    line_id = mpColl_804D6494_line_id;
    flags = mpColl_804D6498_flags;
    normal = mpColl_80458810.normal;

    if (coll->cur_pos.x > mpColl_804D6490_max_x) {
        coll->cur_pos.x = mpColl_804D6490_max_x;
        coll->left_facing_wall.index = line_id;
        coll->left_facing_wall.flags = flags;
        coll->left_facing_wall.normal = normal;
        return true;
    }

    return false;
}

bool mpColl_8004A45C_Floor(CollData* coll, int line_id)
{
    u32 flags;
    float y;
    Vec3 normal;
    Vec3 edge;
    int floor_id;
    bool on_edge;

    on_edge = false;
    if (!mpLib_80054ED8(line_id) || mpLineGetKind(line_id) != CollLine_Floor) {
        return false;
    }
    mpFloorGetLeft(line_id, &edge);
    if (coll->cur_pos.x <= edge.x) {
        float edge_x;
        float edge_y;
        float right_x;
        float right_y;
        floor_id = mpLib_8004DD90_Floor(line_id, &edge, &y, &flags, &normal);
        edge_x = edge.x + 1.0F;
        edge_y = edge.y + 1.0F;
        right_x = edge.x + coll->ecb.right.x - coll->ecb.bottom.x;
        right_y = edge.y + coll->ecb.right.y - coll->ecb.bottom.y;
        // make sure a wall hasn't stopped us
        if (!mpCheckLeftWall(edge_x, edge_y, right_x, right_y, NULL, NULL,
                             NULL, NULL, coll->joint_id_skip,
                             coll->joint_id_only))
        {
            on_edge = true;
            coll->env_flags |= Collide_RightEdge;
        }
    } else {
        float edge_x;
        float edge_y;
        float left_x;
        float left_y;
        mpFloorGetRight(line_id, &edge);
        if (coll->cur_pos.x >= edge.x) {
            floor_id =
                mpLib_8004DD90_Floor(line_id, &edge, &y, &flags, &normal);
            edge_x = edge.x - 1.0F;
            edge_y = edge.y + 1.0F;
            left_x = edge.x + coll->ecb.left.x - coll->ecb.bottom.x;
            left_y = edge.y + coll->ecb.left.y - coll->ecb.bottom.y;
            // make sure a wall hasn't stopped us
            if (!mpCheckRightWall(edge_x, edge_y, left_x, left_y, NULL, NULL,
                                  NULL, NULL, coll->joint_id_skip,
                                  coll->joint_id_only))
            {
                on_edge = true;
                coll->env_flags |= Collide_LeftEdge;
            }
        }
    }

    if (on_edge) {
        coll->cur_pos.x = edge.x - coll->ecb.bottom.x;
        coll->cur_pos.y = edge.y - coll->ecb.bottom.y;
        coll->cur_pos.z = edge.z;
        coll->floor.index = floor_id;
        coll->floor.flags = flags;
        coll->floor.normal = normal;
        return true;
    }

    return false;
}

bool mpColl_8004A678_Floor(CollData* coll, int line_id)
{
    u32 flags;
    float y;
    Vec3 normal;
    Vec3 edge;
    int floor_id;
    bool on_edge = false; // r29

    if (!mpLib_80054ED8(line_id) || mpLineGetKind(line_id) != CollLine_Floor) {
        return false;
    }

    mpFloorGetLeft(line_id, &edge);
    if (coll->cur_pos.x <= edge.x) {
        if (!(coll->env_flags & Collide_LeftWallMask) &&
            coll->facing_dir == -1 && coll->lstick_x > -0.75)
        {
            float edge_x;
            float edge_y;
            float right_x;
            float right_y;
            floor_id =
                mpLib_8004DD90_Floor(line_id, &edge, &y, &flags, &normal);
            if (floor_id != -1) {
                edge.y += y;
            }

            edge_x = edge.x + 1.0F;
            edge_y = edge.y + 1.0F;
            right_x = edge.x + coll->ecb.right.x - coll->ecb.bottom.x;
            right_y = edge.y + coll->ecb.right.y - coll->ecb.bottom.y;
            // make sure a wall hasn't stopped us
            if (!mpCheckLeftWall(edge_x, edge_y, right_x, right_y, NULL, NULL,
                                 NULL, NULL, coll->joint_id_skip,
                                 coll->joint_id_only))
            {
                on_edge = true;
            }
        }
    } else {
        mpFloorGetRight(line_id, &edge);
        if (coll->cur_pos.x >= edge.x &&
            !(coll->env_flags & Collide_RightWallMask) &&
            coll->facing_dir == 1 && coll->lstick_x < 0.75)
        {
            float edge_x;
            float edge_y;
            float left_x;
            float left_y;
            floor_id =
                mpLib_8004DD90_Floor(line_id, &edge, &y, &flags, &normal);
            if (floor_id != -1) {
                edge.y += y;
            }

            edge_x = edge.x - 1.0F;
            edge_y = edge.y + 1.0F;
            left_x = edge.x + coll->ecb.left.x - coll->ecb.bottom.x;
            left_y = edge.y + coll->ecb.left.y - coll->ecb.bottom.y;
            // make sure a wall hasn't stopped us
            if (!mpCheckRightWall(edge_x, edge_y, left_x, left_y, NULL, NULL,
                                  NULL, NULL, coll->joint_id_skip,
                                  coll->joint_id_only))
            {
                on_edge = true;
            }
        }
    }

    if (on_edge) {
        coll->cur_pos.x = edge.x - coll->ecb.bottom.x;
        coll->cur_pos.y = edge.y - coll->ecb.bottom.y;
        coll->cur_pos.z = edge.z;
        coll->floor.index = floor_id;
        coll->floor.flags = flags;
        coll->floor.normal = normal;
        coll->env_flags |= Collide_Edge;
        return true;
    }

    return false;
}

bool mpColl_8004A908_Floor(CollData* coll, int line_id)
{
    int floor_id;
    u32 flags;
    Vec3 normal;
    float prev_bottom_x;
    float prev_bottom_y;
    float bottom_x;
    float bottom_y;
    bool hit_floor;

    prev_bottom_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_bottom_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (coll->x38 != mpColl_804D64AC) {
        hit_floor = mpCheckFloorRemap(
            prev_bottom_x, prev_bottom_y, bottom_x, bottom_y, 0.0F, NULL,
            &floor_id, &flags, &normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, NULL, NULL);
    } else {
        hit_floor = mpCheckFloor(
            prev_bottom_x, prev_bottom_y, bottom_x, bottom_y, 0.0F, NULL,
            &floor_id, &flags, &normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, NULL, NULL);
    }
    if (hit_floor && floor_id != -1 && floor_id != line_id &&
        (line_id == -1 || !mpLinesConnected(floor_id, line_id)))
    {
        coll->floor.index = floor_id;
        coll->floor.flags = flags;
        coll->floor.normal = normal;
        return true;
    }
    prev_bottom_y = 0.5F * (coll->prev_ecb.top.y + coll->prev_ecb.bottom.y) +
                    coll->prev_pos.y;
    if (coll->x38 != mpColl_804D64AC) {
        hit_floor = mpCheckFloorRemap(
            prev_bottom_x, prev_bottom_y, bottom_x, bottom_y, 0.0F, NULL,
            &floor_id, &flags, &normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, NULL, NULL);
    } else {
        hit_floor = mpCheckFloor(
            prev_bottom_x, prev_bottom_y, bottom_x, bottom_y, 0.0F, NULL,
            &floor_id, &flags, &normal, coll->floor_skip, coll->joint_id_skip,
            coll->joint_id_only, NULL, NULL);
    }
    if (hit_floor && floor_id != -1 && floor_id != line_id &&
        (line_id == -1 || !mpLinesConnected(floor_id, line_id)))
    {
        coll->floor.index = floor_id;
        coll->floor.flags = flags;
        coll->floor.normal = normal;
        return true;
    }

    return false;
}

// ceiling collide
bool mpColl_8004AB80(CollData* coll)
{
    Vec3 top;
    float y;
    Vec3 ceiling_end; // spC
    int line_id;
    bool hit_wall;

    top.x = coll->cur_pos.x + coll->ecb.top.x;
    top.y = coll->cur_pos.y + coll->ecb.top.y;
    line_id =
        mpLib_8004E090_Ceiling(coll->ceiling.index, &top, &y,
                               &coll->ceiling.flags, &coll->ceiling.normal);
    if (line_id != -1) {
        coll->ceiling.index = line_id;
        coll->cur_pos.y += y;
    } else {
        hit_wall = false;
        mpCeilingGetLeft(coll->ceiling.index, &ceiling_end);
        if (top.x <= ceiling_end.x) {
            int line_id = mpLineNextNonCeiling(coll->ceiling.index);
            if (line_id != -1 && mpLineGetKind(line_id) == CollLine_RightWall)
            {
                hit_wall = true;
            }
        } else {
            int line_id;
            mpCeilingGetRight(coll->ceiling.index, &ceiling_end);
            line_id = mpLinePrevNonCeiling(coll->ceiling.index);
            if (line_id != -1 && mpLineGetKind(line_id) == CollLine_LeftWall) {
                hit_wall = true;
            }
        }
        coll->cur_pos.y = ceiling_end.y - coll->ecb.top.y;
        if (hit_wall) {
            int line_id;
            coll->cur_pos.x = ceiling_end.x;
            line_id = mpLib_8004E090_Ceiling(coll->ceiling.index, &ceiling_end,
                                             NULL, &coll->ceiling.flags,
                                             &coll->ceiling.normal);
            if (line_id != -1) {
                coll->ceiling.index = line_id;
            } else {
                OSReport("%s:%d: oioi...\n", __FILE__, 5745);
            }
        }
    }

    return true;
}

bool mpColl_8004ACE4(CollData* coll, int flags)
{
    bool touching_floor; // r29
    u32 left_right;      // r28
    bool prev_b6;        // r27

    touching_floor = false;
    left_right = 0;
    do {
        float x_after_right;   // f31
        float x_after_left;    // f30
        float y_after_ceiling; // f29
        float y_after_floor;   // f28

        bool hit_left;    // r26
        bool hit_right;   // r25
        bool hit_floor;   // r25
        bool hit_ceiling; // r26
        hit_right = false;
        prev_b6 = coll->x34_flags.b6;
        hit_left = 0;
        if (mpColl_80049778_LeftWall(coll)) {
            hit_left = mpColl_80049EAC_LeftWall(coll);
            if (hit_left) {
                left_right |= 1;
            } else {
                coll->env_flags &= ~Collide_LeftWallMask;
            }
            x_after_left = coll->cur_pos.x;
            coll->x34_flags.b5 = true;
        }
        if (mpColl_80048AB0_RightWall(coll)) {
            hit_right = mpColl_800491C8_RightWall(coll);
            if (hit_right) {
                left_right |= 2;
            } else {
                coll->env_flags &= ~Collide_RightWallMask;
            }
            x_after_right = coll->cur_pos.x;
            coll->x34_flags.b5 = true;
        }
        if (mpColl_80049778_LeftWall(coll)) {
            hit_left |= mpColl_80049EAC_LeftWall(coll);
            if (hit_left) {
                left_right |= 1;
            }
            x_after_left = coll->cur_pos.x;
            coll->x34_flags.b5 = true;
        }
        if (mpColl_80048AB0_RightWall(coll)) {
            hit_right |= mpColl_800491C8_RightWall(coll);
            if (hit_right) {
                left_right |= 2;
            }
            x_after_right = coll->cur_pos.x;
            coll->x34_flags.b5 = true;
        }

        if (hit_left && hit_right) {
            mpCollSqueezeHorizontal(coll, false, x_after_right, x_after_left);
        }

        hit_ceiling = false;
        hit_floor = false;
        if (mpColl_80044AD8_Ceiling(coll, left_right) && mpColl_8004AB80(coll))
        {
            hit_ceiling = true;
            y_after_ceiling = coll->cur_pos.y;
        }
        if (mpColl_800488F4(coll)) {
            mpCollFloorInline(coll, false, 0);
            y_after_floor = coll->cur_pos.y;
            touching_floor = true;
            hit_floor = true;
            if (mpColl_80044AD8_Ceiling(coll, left_right) &&
                mpColl_8004AB80(coll))
            {
                y_after_ceiling = coll->cur_pos.y;
                hit_ceiling = true;
            }
        } else {
            int old_skip;                     // r23
            bool var_r23 = false;             // r23
            int floor_id = coll->floor.index; // r22
            if (mpLib_80054ED8(floor_id) &&
                mpLineGetKind(floor_id) == CollLine_Floor)
            {
                if (flags & 1) {
                    if (mpColl_8004A678_Floor(coll, floor_id)) {
                        coll->x34_flags.b5 = true;
                        touching_floor = false;
                        hit_floor = true;
                        y_after_floor = coll->cur_pos.y;
                    } else {
                        var_r23 = true;
                    }
                } else if (flags & 2) {
                    if (mpColl_8004A45C_Floor(coll, floor_id)) {
                        coll->x34_flags.b5 = true;
                        touching_floor = true;
                        hit_floor = true;
                        y_after_floor = coll->cur_pos.y;
                    } else {
                        var_r23 = true;
                    }
                } else {
                    var_r23 = true;
                }

                if (var_r23) {
                    old_skip = coll->floor_skip;
                    coll->floor_skip = floor_id;
                    if (mpColl_80046904(coll, 0U)) {
                        touching_floor = true;
                    }
                    coll->floor_skip = old_skip;
                    coll->x34_flags.b5 = true;
                }
            }
        }

        if (hit_floor && hit_ceiling) {
            bool airborne; // r4
            if (touching_floor) {
                airborne = false;
            } else {
                airborne = true;
            }
            mpCollSqueezeVertical(coll, airborne, y_after_ceiling,
                                  y_after_floor);
        }
    } while (prev_b6 != coll->x34_flags.b6);

    if (mpColl_8004A908_Floor(coll, coll->floor.index)) {
        if (mpColl_80044838_Floor(coll, false)) {
            mpCollFloorInline(coll, false, 0);
        }
        coll->x34_flags.b5 = false;
        touching_floor = true;
    }

    if (touching_floor) {
        coll->env_flags |= Collide_FloorPush;
    }

    return touching_floor;
}

bool mpColl_8004B108(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 5);
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
    mpColl_LoadECB_inline(coll, 5);
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
    mpColl_LoadECB_inline(coll, 5);
    return inline2(coll, 1);
}

bool mpColl_8004B5C4(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 9);
    return inline2(coll, 1);
}

bool mpColl_8004B6D8(CollData* coll)
{
    Vec3 top; // sp30
    u8 _[0xC];
    float y;          // sp20
    Vec3 ceiling_end; // sp14

    int ceiling_id; // r31
    int new_ceiling;
    bool hit_wall; // r30

    PAD_STACK(0x8);

    ceiling_id = coll->ceiling.index;
    top.x = coll->cur_pos.x + coll->ecb.top.x;
    top.y = coll->cur_pos.y + coll->ecb.top.y;
    if (!mpLib_80054ED8(coll->ceiling.index) ||
        mpLineGetKind(coll->ceiling.index) != CollLine_Ceiling)
    {
        return false;
    }
    new_ceiling = mpLib_8004E090_Ceiling(
        ceiling_id, &top, &y, &coll->ceiling.flags, &coll->ceiling.normal);
    if (new_ceiling != -1) {
        coll->cur_pos.y += y;
        coll->ceiling.index = new_ceiling;
        return true;
    }
    hit_wall = false;
    mpCeilingGetLeft(ceiling_id, &ceiling_end);
    if (coll->cur_pos.x < ceiling_end.x) {
        int non_ceiling_id = mpLineNextNonCeiling(ceiling_id);
        if (non_ceiling_id != -1 && mpLib_80054ED8(non_ceiling_id) &&
            (mpLineGetKind(non_ceiling_id) & CollLine_RightWall))
        {
            hit_wall = true;
        } else {
            coll->env_flags |= Collide_LeftLedgeSlip;
        }
    } else {
        mpCeilingGetRight(ceiling_id, &ceiling_end);
        if (coll->cur_pos.x > ceiling_end.x) {
            int non_ceiling_id = mpLinePrevNonCeiling(ceiling_id);
            if (non_ceiling_id != -1 && mpLib_80054ED8(non_ceiling_id) &&
                (mpLineGetKind(non_ceiling_id) & CollLine_LeftWall))
            {
                hit_wall = true;
            } else {
                coll->env_flags |= Collide_RightLedgeSlip;
            }
        }
    }
    if (hit_wall) {
        coll->cur_pos = ceiling_end;
        return true;
    }
    return false;
}

bool mpColl_8004B894_RightWall(CollData* coll)
{
    int line_id;
    float left_x;        // f31
    float left_y;        // f30
    float prev_left_x;   // f1
    float prev_left_y;   // f2
    float prev_bottom_x; // f1
    float prev_bottom_y; // f2
    float prev_top_x;    // f1
    float prev_top_y;    // f2
    float bottom_x;      // f3
    float bottom_y;      // f4
    float top_x;         // f3
    float top_y;         // f4
    bool hit_wall;
    int line_id1;
    int line_id2;

    hit_wall = false;
    mpColl_804D6488 = 0;
    if (mpLib_80054ED8(coll->ceiling.index)) {
        int temp;
        line_id1 = mpLib_8005389C_Ceiling(coll->ceiling.index);
        temp = mpLib_80053BD4_Ceiling(coll->ceiling.index);
        line_id = temp;
        line_id2 = temp != -1 ? mpLib_8005389C_Ceiling(line_id) : -1;
    } else {
        line_id2 = -1;
        line_id1 = -1;
    }

    left_x = coll->cur_pos.x + coll->ecb.left.x;
    left_y = coll->cur_pos.y + coll->ecb.left.y;
    prev_left_x = coll->prev_pos.x + coll->prev_ecb.left.x;
    prev_left_y = coll->prev_pos.y + coll->prev_ecb.left.y;
    if (mpColl_RightWall_inline2(coll, prev_left_x, prev_left_y, left_x,
                                 left_y, &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
        coll->env_flags |= Collide_RightWallHug;
    }

    prev_bottom_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_bottom_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_RightWall_inline2(coll, prev_bottom_x, prev_bottom_y, bottom_x,
                                 bottom_y, &line_id))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_RightWall_inline2(coll, prev_top_x, prev_top_y, top_x, top_y,
                                 &line_id) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    prev_bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    prev_bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckRightWall(prev_bottom_x, prev_bottom_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only))
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    prev_top_x = coll->cur_pos.x + coll->ecb.top.x;
    prev_top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckRightWall(prev_top_x, prev_top_y, left_x, left_y, NULL,
                         &line_id, NULL, NULL, coll->joint_id_skip,
                         coll->joint_id_only) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_RightWall_inline(line_id);
        hit_wall = true;
    }

    if (hit_wall) {
        coll->env_flags |= Collide_RightWallPush;
    }

    return hit_wall;
}

bool mpColl_8004BDD4_LeftWall(CollData* coll)
{
    int line_id;
    float right_x;       // f31
    float right_y;       // f30
    float prev_right_x;  // f1
    float prev_right_y;  // f2
    float prev_bottom_x; // f1
    float prev_bottom_y; // f2
    float prev_top_x;    // f1
    float prev_top_y;    // f2
    float bottom_x;      // f3
    float bottom_y;      // f4
    float top_x;         // f3
    float top_y;         // f4
    bool hit_wall;
    int line_id1;
    int line_id2;

    hit_wall = false;
    mpColl_804D6488 = 0;
    if (mpLib_80054ED8(coll->ceiling.index)) {
        int temp;
        line_id1 = mpLib_80053950_Ceiling(coll->ceiling.index);
        temp = mpLib_80053A04_Ceiling(coll->ceiling.index);
        line_id = temp;
        line_id2 = temp != -1 ? mpLib_80053950_Ceiling(line_id) : -1;
    } else {
        line_id2 = -1;
        line_id1 = -1;
    }

    right_x = coll->cur_pos.x + coll->ecb.right.x;
    right_y = coll->cur_pos.y + coll->ecb.right.y;
    prev_right_x = coll->prev_pos.x + coll->prev_ecb.right.x;
    prev_right_y = coll->prev_pos.y + coll->prev_ecb.right.y;
    if (mpColl_LeftWall_inline2(coll, prev_right_x, prev_right_y, right_x,
                                right_y, &line_id))
    {
        mpColl_LeftWall_inline3(line_id, mpColl_80458810.left);
        hit_wall = true;
        coll->env_flags |= Collide_LeftWallHug;
    }

    prev_bottom_x = coll->prev_pos.x + coll->prev_ecb.bottom.x;
    prev_bottom_y = coll->prev_pos.y + coll->prev_ecb.bottom.y;
    bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpColl_LeftWall_inline2(coll, prev_bottom_x, prev_bottom_y, bottom_x,
                                bottom_y, &line_id))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    prev_top_x = coll->prev_pos.x + coll->prev_ecb.top.x;
    prev_top_y = coll->prev_pos.y + coll->prev_ecb.top.y;
    top_x = coll->cur_pos.x + coll->ecb.top.x;
    top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpColl_LeftWall_inline2(coll, prev_top_x, prev_top_y, top_x, top_y,
                                &line_id) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    prev_bottom_x = coll->cur_pos.x + coll->ecb.bottom.x;
    prev_bottom_y = coll->cur_pos.y + coll->ecb.bottom.y;
    if (mpCheckLeftWall(prev_bottom_x, prev_bottom_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only))
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    prev_top_x = coll->cur_pos.x + coll->ecb.top.x;
    prev_top_y = coll->cur_pos.y + coll->ecb.top.y;
    if (mpCheckLeftWall(prev_top_x, prev_top_y, right_x, right_y, NULL,
                        &line_id, NULL, NULL, coll->joint_id_skip,
                        coll->joint_id_only) &&
        line_id != line_id1 && line_id != line_id2)
    {
        mpColl_LeftWall_inline(line_id);
        hit_wall = true;
    }

    if (hit_wall) {
        coll->env_flags |= Collide_LeftWallPush;
    }

    return hit_wall;
}

bool mpColl_8004C328_Ceiling(CollData* coll, int line_id)
{
    u32 flags;
    float y;
    Vec3 normal;
    Vec3 edge;
    int ceiling_id;
    bool result;
    float edge_x;
    float edge_y;
    float ecb_side_x;
    float ecb_side_y;

    result = false;
    if (!mpLib_80054ED8(line_id) || mpLineGetKind(line_id) != CollLine_Ceiling)
    {
        return false;
    }
    mpCeilingGetLeft(line_id, &edge);
    if (coll->cur_pos.x <= edge.x) {
        ceiling_id =
            mpLib_8004E090_Ceiling(line_id, &edge, &y, &flags, &normal);
        edge_x = edge.x + 1.0F;
        edge_y = edge.y - 1.0F;
        ecb_side_x = edge.x + coll->ecb.right.x - coll->ecb.top.x;
        ecb_side_y = edge.y + coll->ecb.right.y - coll->ecb.top.y;
        // make sure a wall hasn't stopped us
        if (!mpCheckLeftWall(edge_x, edge_y, ecb_side_x, ecb_side_y, NULL,
                             NULL, NULL, NULL, coll->joint_id_skip,
                             coll->joint_id_only))
        {
            result = true;
            coll->env_flags |= Collide_RightEdge;
        }
    } else {
        mpCeilingGetRight(line_id, &edge);
        if (coll->cur_pos.x >= edge.x) {
            ceiling_id =
                mpLib_8004E090_Ceiling(line_id, &edge, &y, &flags, &normal);
            edge_x = edge.x - 1.0F;
            edge_y = edge.y - 1.0F;
            ecb_side_x = edge.x + coll->ecb.left.x - coll->ecb.top.x;
            ecb_side_y = edge.y + coll->ecb.left.y - coll->ecb.top.y;
            // make sure a wall hasn't stopped us
            if (!mpCheckRightWall(edge_x, edge_y, ecb_side_x, ecb_side_y, NULL,
                                  NULL, NULL, NULL, coll->joint_id_skip,
                                  coll->joint_id_only))
            {
                result = true;
                coll->env_flags |= Collide_LeftEdge;
            }
        }
    }

    if (result) {
        coll->cur_pos = edge;
        coll->ceiling.index = ceiling_id;
        coll->ceiling.flags = flags;
        coll->ceiling.normal = normal;
        return true;
    }

    return false;
}

bool mpColl_8004C534(CollData* coll, u32 flags)
{
    bool hit_ceiling = false;

    if (mpColl_8004BDD4_LeftWall(coll)) {
        mpColl_80049EAC_LeftWall(coll);
        coll->x34_flags.b5 = true;
    }

    if (mpColl_8004B894_RightWall(coll)) {
        mpColl_800491C8_RightWall(coll);
        coll->x34_flags.b5 = true;
    }

    if (mpColl_8004B6D8(coll)) {
        mpCollCeilingInline(coll);
        hit_ceiling = true;
    } else if (mpLib_80054ED8(coll->ceiling.index)) {
        int ceiling_id = coll->ceiling.index;
        if (!(flags & 1)) {
            if (flags & 2) {
                if (mpColl_8004C328_Ceiling(coll, ceiling_id)) {
                    hit_ceiling = true;
                } else {
                    coll->x34_flags.b5 = true;
                }
            } else {
                coll->x34_flags.b5 = true;
            }
        }
    }

    if (hit_ceiling) {
        coll->env_flags |= Collide_CeilingPush;
    }

    return hit_ceiling;
}

bool mpColl_8004C750(CollData* coll)
{
    mpCollPrev(coll);
    mpColl_LoadECB_inline(coll, 5);
    return inline3(coll, 2);
}

void mpCollSqueezeHorizontal(CollData* coll, bool airborne, float left,
                             float right)
{
    float half_width =
        0.5F * (right - left + coll->ecb.right.x - coll->ecb.left.x);
    if (!coll->x34_flags.b6) {
        coll->x64_ecb = coll->ecb;
    }
    coll->x34_flags.b6 = true;
    coll->cur_pos.x = (right + coll->ecb.right.x) - half_width;
    coll->ecb.right.x = half_width;
    coll->ecb.left.x = -half_width;
    coll->desired_ecb.right.x = coll->ecb.right.x;
    coll->desired_ecb.left.x = coll->ecb.left.x;
    coll->x34_flags.b5 = false;
}

void mpCollSqueezeVertical(CollData* coll, bool airborne, float top,
                           float bottom)
{
    float height = top - bottom + coll->ecb.top.y - coll->ecb.bottom.y;
    float mid_y;

    if (!coll->x34_flags.b6) {
        coll->x64_ecb = coll->ecb;
    }
    coll->x34_flags.b6 = true;

    if (height < 3.0F) {
        float old_height = coll->ecb.top.y - coll->ecb.bottom.y;
        float new_height = coll->ecb.top.y + top - bottom;
        coll->ecb.top.y = MIN(old_height, new_height);
        coll->ecb.bottom.y = 0.0F;
        coll->cur_pos.y = bottom;
    } else if (!airborne) {
        coll->cur_pos.y = bottom;
        coll->ecb.top.y = height + coll->ecb.bottom.y;
    } else {
        coll->cur_pos.y = 0.5F * (top + bottom);
        coll->ecb.top.y =
            0.5F * (coll->ecb.top.y + coll->ecb.bottom.y + height);
        coll->ecb.bottom.y = coll->ecb.top.y - height;
    }
    mid_y = 0.5F * (coll->ecb.top.y + coll->ecb.bottom.y);
    coll->ecb.right.y = mid_y;
    coll->ecb.left.y = mid_y;
    coll->desired_ecb.top.y = coll->ecb.top.y;
    coll->desired_ecb.bottom.y = coll->ecb.bottom.y;
    coll->desired_ecb.left.y = coll->ecb.left.y;
    coll->desired_ecb.right.y = coll->ecb.right.y;
    coll->x34_flags.b5 = false;
}

float mpColl_8004CA6C(CollData* coll)
{
    float result = 1.0F;
    if (coll->floor.index != -1) {
        result = mpLib_800569EC(coll->floor.flags);
    }
    return result;
}

bool mpCollGetSpeedCeiling(CollData* coll, Vec3* speed)
{
    int index = coll->ceiling.index;
    Vec3 top; // sp10
    top.x = coll->ecb.top.x;
    top.y = coll->ecb.top.y;
    top.z = 0.0F;
    return mpGetSpeed(index, &top, speed);
}

bool mpCollGetSpeedLeftWall(CollData* coll, Vec3* speed)
{
    int index = coll->left_facing_wall.index;
    Vec3 top; // sp10
    top.x = coll->ecb.top.x;
    top.y = coll->ecb.top.y;
    top.z = 0.0F;
    return mpGetSpeed(index, &top, speed);
}

bool mpCollGetSpeedRightWall(CollData* coll, Vec3* speed)
{
    int index = coll->right_facing_wall.index;
    Vec3 top; // sp10
    top.x = coll->ecb.top.x;
    top.y = coll->ecb.top.y;
    top.z = 0.0F;
    return mpGetSpeed(index, &top, speed);
}

bool mpCollGetSpeedFloor(CollData* coll, Vec3* speed)
{
    int index = coll->floor.index;
    Vec3 top;
    top.x = coll->ecb.top.x;
    top.y = coll->ecb.top.y;
    top.z = 0.0F;
    return mpGetSpeed(index, &top, speed);
}

bool mpColl_IsOnPlatform(CollData* coll)
{
    return mpLineGetFlags(coll->floor.index) & LINE_FLAG_PLATFORM;
}

void mpUpdateFloorSkip(CollData* coll)
{
    coll->floor_skip = coll->floor.index;
}

void mpClearFloorSkip(CollData* coll)
{
    coll->floor_skip = -1;
}

void mpCopyCollData(CollData* src, CollData* dst, int arg2)
{
    if (arg2 == 1) {
        dst->x64_ecb = src->x64_ecb;
        dst->desired_ecb = src->desired_ecb;
        dst->ecb = src->ecb;
        dst->prev_ecb = src->prev_ecb;
        dst->xE4_ecb = src->xE4_ecb;
    }

    dst->cur_pos = src->cur_pos;
    dst->prev_pos = src->prev_pos;
    dst->last_pos = src->last_pos;

    dst->x34_flags.b0 = src->x34_flags.b0;
    dst->x34_flags.b1234 = src->x34_flags.b1234;
    dst->x34_flags.b5 = src->x34_flags.b5;
    dst->x34_flags.b6 = src->x34_flags.b6;

    dst->facing_dir = src->facing_dir;
    dst->x38 = src->x38;
    dst->floor_skip = src->floor_skip;
    dst->ledge_id_left = src->ledge_id_left;
    dst->ledge_id_right = src->ledge_id_right;
    dst->joint_id_skip = src->joint_id_skip;
    dst->lstick_x = src->lstick_x;

    dst->x64_ecb = src->x64_ecb;
    dst->desired_ecb = src->desired_ecb;
    dst->ecb = src->ecb;
    dst->prev_ecb = src->prev_ecb;
    dst->xE4_ecb = src->xE4_ecb;

    dst->x130_flags = src->x130_flags;
    dst->env_flags = src->env_flags;
    dst->prev_env_flags = src->prev_env_flags;
    dst->x13C = src->x13C;
    dst->contact = src->contact;

    dst->floor.index = src->floor.index;
    dst->floor.flags = src->floor.flags;
    dst->floor.normal = src->floor.normal;

    dst->left_facing_wall.index = src->left_facing_wall.index;
    dst->left_facing_wall.flags = src->left_facing_wall.flags;
    dst->left_facing_wall.normal = src->left_facing_wall.normal;

    dst->right_facing_wall.index = src->right_facing_wall.index;
    dst->right_facing_wall.flags = src->right_facing_wall.flags;
    dst->right_facing_wall.normal = src->right_facing_wall.normal;

    dst->ceiling.index = src->ceiling.index;
    dst->ceiling.flags = src->ceiling.flags;
    dst->ceiling.normal = src->ceiling.normal;
}

bool mpColl_8004D024(Vec3* arg0)
{
    CollData spC;
    mpColl_80041EE4(&spC);
    spC.x34_flags.b1234 = 0;
    mpColl_SetECBSource_Fixed(&spC, NULL, 10.0F, 10.0F, 10.0F, 10.0F);
    spC.last_pos.x = arg0->x;
    spC.last_pos.y = -3.0F + arg0->y;
    spC.last_pos.z = arg0->z;
    spC.cur_pos = *arg0;
    spC.x130_flags |= CollData_X130_Clear;
    mpCollPrev(&spC);
    mpColl_LoadECB(&spC);
    inline0(&spC, 0, true);
    if (spC.x34_flags.b6) {
        return true;
    }
    return false;
}
