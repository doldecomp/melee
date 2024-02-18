#include "ftCommon/forward.h"
#include "mp/forward.h"

#include "mp/mpcoll.h"

#include "math.h"

#include "db/db_2253.h"
#include "ft/ftlib.h"
#include "ft/types.h"
#include "gr/grdynamicattr.h"
#include "it/it_26B1.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <placeholder.h>
#include <dolphin/os/OSError.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <MSL/trigf.h>

static bool mpColl_804D649C;
static Event mpColl_804D64A0;
static Event mpColl_804D64A4;
static Event mpColl_804D64A8;
u32 mpColl_804D64AC;

// 80041C78 https://decomp.me/scratch/V6eYQ
void mpColl_80041C78(void)
{
    mpColl_804D64A0 = NULL;
    mpColl_804D64A4 = 0;
    mpColl_804D64A8 = 0;
}

char mpColl_804D3948[2] = "0";

// 80041C8C https://decomp.me/scratch/VvSaI
void mpColl_80041C8C(CollData* cd)
{
    u8 _[8];

    mpColl_804D64A0 = 0;
    mpColl_804D64A4 = 0;
    if (g_debugLevel >= 3) {
        if (!(cd->x4_vec.x < 45000.0f) || !(cd->x4_vec.x > -45000.0f) ||
            !(cd->x4_vec.y < 45000.0f) || !(cd->x4_vec.y > -45000.0f))
        {
            if (ftLib_80086960(cd->x0_gobj) != 0) {
                OSReport(
                    "%s:%d: Error: mpCollPrev() pos(%f,%f) player=%d ms=%d\n",
                    "mpcoll.c", 203, ftLib_80086BE0(cd->x0_gobj),
                    ftLib_800874BC(cd->x0_gobj), cd->x4_vec.x, cd->x4_vec.y);
            } else {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) gobj_id=%d\n",
                         "mpcoll.c", 212, cd->x0_gobj->classifier,
                         cd->x4_vec.x, cd->x4_vec.y);
                if (cd->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(cd->x0_gobj));
                }
            }
            __assert("mpcoll.c", 228, mpColl_804D3948);
        }
    }
    cd->x28_vec = cd->x4_vec;
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

    left = cd->xA4_ecbCurrCorrect.left.x + cd->x4_vec.x;
    clamp_below(&left, cd->xC4_ecb.left.x + cd->x10_vec.x);

    right = cd->xA4_ecbCurrCorrect.right.x + cd->x4_vec.x;
    clamp_above(&right, cd->xC4_ecb.right.x + cd->x10_vec.x);

    bottom = cd->xA4_ecbCurrCorrect.bottom.y + cd->x4_vec.y;
    clamp_below(&bottom, cd->xC4_ecb.bottom.y + cd->x10_vec.y);

    top = cd->xA4_ecbCurrCorrect.top.y + cd->x4_vec.y;
    clamp_above(&top, cd->xC4_ecb.top.y + cd->x10_vec.y);

    if (flags & 0b100) {
        float x54 = cd->x54;
        float tmp = 0.5f * cd->x5C;
        float offset;

        right += x54;
        left -= x54;

        clamp_below(&bottom, cd->x58 - tmp + cd->x4_vec.y);
        clamp_below(&bottom, cd->x58 - tmp + cd->x10_vec.y);

        offset = cd->x58 + tmp;
        clamp_above(&top, cd->x4_vec.y + offset);
        clamp_above(&top, cd->x10_vec.y + offset);
    }

    mpLib_800588D0(left, bottom, right, top);
}

/// @todo float order hack
const float mpColl_804D7F9C = -F32_MAX;
const float mpColl_804D7FA0 = F32_MAX;

// 80041EE4 https://decomp.me/scratch/j2TXK
// CollDataInit
void mpColl_80041EE4(CollData* cd)
{
    cd->x0_gobj = NULL;
    cd->x34_flags.bits.b0 = 1;
    cd->x34_flags.bits.b6 = 0;
    cd->x34_flags.bits.b7 = 0;
    cd->x35_flags.bits.b0 = 1;
    cd->x34_flags.bits.b1234 = 0;
    cd->env_flags = 0;
    cd->x130_flags = 0;
    cd->x10_vec = cd->x4_vec;
    cd->x1C_vec = cd->x4_vec;
    cd->x28_vec = cd->x4_vec;
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
    cd->x54 = 0.0f;
    cd->x58 = 0.0f;
    cd->x5C = 0.0f;
    lb_8000C160(&cd->xA4_ecbCurrCorrect, sizeof(ftECB));
    lb_8000C160(&cd->xC4_ecb, sizeof(ftECB));
    lb_8000C160(&cd->xE4_ecb, sizeof(ftECB));
    lb_8000C160(&cd->x104, 0x2C);
    lb_8000C160(&cd->x84_ecb, sizeof(ftECB));
    lb_8000C160(&cd->x64_ecb, sizeof(ftECB));
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
    if (cd->x34_flags.bits.b0) {
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
    if (cd->x34_flags.bits.b0) {
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
void mpColl_80042374(CollData* arg0, float arg8, float arg9, float argA)
{
    arg0->x54 = arg8;
    arg0->x58 = arg9;
    arg0->x5C = argA;
}

// 80042384 https://decomp.me/scratch/P8djI
void mpColl_80042384(CollData* cd)
{
    float tmp, tmp2;

    if (fabs_inline(cd->x84_ecb.top.y - cd->x84_ecb.bottom.y) < 1.0f) {
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
        float temp_x = cd->x4_vec.x;
        float temp_y = cd->x4_vec.y;
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
    phi_f2 = fabs_inline(right_x - left_x);

    if (phi_f2 < phi_f1) {
        right_x = 0.5f * phi_f2;
        left_x = -right_x;
    }

    phi_f1 = 4.0f > cd->x128 ? 4.0f : cd->x128;
    phi_f2 = fabs_inline(top_y - bottom_y);

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
    cd->x34_flags.bits.b0 = 0;
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
    if ((cd->x130_flags & 0x20) != 0) {
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

    cd->x34_flags.bits.b0 = 0;
}

void mpColl_80042C58(CollData* arg0, ftCollisionBox* arg1)
{
    if ((arg0->x130_flags & 0x20) != 0) {
        arg0->xA4_ecbCurrCorrect.top.x = 0.0f;
        arg0->xA4_ecbCurrCorrect.top.y = 0.0f;
        arg0->xA4_ecbCurrCorrect.bottom.x = 0.0f;
        arg0->xA4_ecbCurrCorrect.bottom.y = 0.0f;
        arg0->xA4_ecbCurrCorrect.right.x = 0.0f;
        arg0->xA4_ecbCurrCorrect.right.y = 0.0f;
        arg0->xA4_ecbCurrCorrect.left.x = 0.0f;
        arg0->xA4_ecbCurrCorrect.left.y = 0.0f;
        arg0->x130_flags &= 0xFFFFFFDF;
    }
    arg0->xE4_ecb = arg0->xA4_ecbCurrCorrect;
    arg0->x84_ecb.top.x = 0.0f;
    arg0->x84_ecb.top.y = arg1->top;
    arg0->x84_ecb.bottom.x = 0.0f;
    arg0->x84_ecb.bottom.y = arg1->bottom;
    arg0->x84_ecb.right.x = arg1->right.x;
    arg0->x84_ecb.right.y = arg1->right.y;
    arg0->x84_ecb.left.x = arg1->left.x;
    arg0->x84_ecb.left.y = arg1->left.y;
    arg0->x34_flags.bits.b0 = 0;
}

// 80042D24 https://decomp.me/scratch/2MnVj
void mpColl_80042D24(CollData* cd)
{
    float saved_bottom_x;
    float saved_bottom_y;

    if ((cd->x130_flags & 0x10) != 0) {
        saved_bottom_x = cd->x84_ecb.bottom.x;
        saved_bottom_y = cd->x84_ecb.bottom.y;
    }
    if (cd->x104 == 1) {
        mpColl_800424DC(cd, 6);
    } else {
        mpColl_8004293C(cd);
    }
    if ((cd->x130_flags & 0x10) != 0) {
        cd->x84_ecb.bottom.x = saved_bottom_x;
        cd->x84_ecb.bottom.y = saved_bottom_y;
    }
    mpColl_80042384(cd);
}

// 80042DB0 https://decomp.me/scratch/GbMpk
inline void Vec2_Interpolate(float time, Vec2* dest, Vec2* src)
{
    dest->x += time * (src->x - dest->x);
    dest->y += time * (src->y - dest->y);
}

void mpColl_80042DB0(CollData* ecb, float time)
{
    ecb->xC4_ecb = ecb->xA4_ecbCurrCorrect;
    if (ecb->x34_flags.bits.b6) {
        ecb->xA4_ecbCurrCorrect = ecb->x64_ecb;
        ecb->x34_flags.bits.b6 = 0;
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
        OSReport("error\n");
        __assert("mpcoll.c", 1193, mpColl_804D3948);
    }
}

// 80043268 https://decomp.me/scratch/GNwej
void mpColl_80043268(CollData* arg0, s32 arg1, s32 arg2, float arg8)
{
    mpLib_Callback sp1C;
    s32 sp18;
    s32 temp_r31;

    temp_r31 = mpLib_80056B6C(arg1);
    if (temp_r31 != -1) {
        sp18 = 0;
        mpLib_800580FC(temp_r31, &sp1C, &sp18);
        if (sp1C != 0) {
            s32 thing;
            if (arg2 == 0) {
                thing = 2;
            } else {
                thing = 1;
            }
            sp1C(sp18, temp_r31, arg0, arg0->x50, thing, arg8);
        }
    }
}

const char* dummy_string_data = "i<MPCOLL_WALLID_MAX";

void func_80043324_inline2(CollData* arg0, s32 arg1, s32 arg2, float arg8)
{ // see mpColl_80043268
    int dummy = 0;

    mpLib_Callback callback;
    s32 thing;
    s32 temp_r29;

    temp_r29 = mpLib_80056B6C(arg1);
    if (temp_r29 != -1) {
        thing = 0;
        mpLib_800581BC(temp_r29, &callback, &thing);

        if (callback != NULL) {
            callback(thing, temp_r29, arg0, arg0->x50, 0, arg8);
        }
    }
}

void func_80043324_inline(CollData* arg0, s32 arg1, s32 arg2, float arg8)
{
    // inhibit inlining
    mpColl_80043268(arg0, arg1, arg2, arg8);
}

void mpColl_80043324(CollData* arg0, s32 arg1, s32 arg2)
{
    s32 temp_r3;

    u8 temp_r3_2[4];

    if (arg0->floor.index != -1) {
        temp_r3 = grDynamicAttr_801CA284(&arg0->x4_vec, arg0->floor.index);
        if (temp_r3 != 0) {
            arg0->floor.unk =
                (arg0->floor.unk & 0xFFFFFF00) | (temp_r3 & 0xFF);
        }
    }
    if ((arg1 != 0) || (arg0->env_flags & 0x800000) ||
        (arg0->env_flags & 0x100000) || (arg0->env_flags & 0x200000))
    {
        func_80043324_inline(arg0, arg0->floor.index, arg2,
                             arg0->x4_vec.y - arg0->x1C_vec.y);
    }
    if (arg0->env_flags & 0x6000) {
        func_80043324_inline2(arg0, arg0->ceiling.index, arg2,
                              arg0->x4_vec.y - arg0->x1C_vec.y);
    }
    if (g_debugLevel >= 3) {
        if (!(arg0->x4_vec.x < 45000.0f) || !(arg0->x4_vec.x > -45000.0f) ||
            !(arg0->x4_vec.y < 45000.0f) || !(arg0->x4_vec.y > -45000.0f))
        {
            if (ftLib_80086960(arg0->x0_gobj)) {
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "ply=%d ms=%d\n",
                         "mpcoll.c", 1350, arg0->x1C_vec.x, arg0->x1C_vec.y,
                         arg0->x4_vec.x, arg0->x4_vec.y,
                         ftLib_80086BE0(arg0->x0_gobj),
                         ftLib_800874BC(arg0->x0_gobj));
            } else {
                s32 gobjid = arg0->x0_gobj->classifier;
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) "
                         "gobjid=%d\n",
                         "mpcoll.c", 1358, arg0->x1C_vec.x, arg0->x1C_vec.y,
                         arg0->x4_vec.x, arg0->x4_vec.y, gobjid);
                if (arg0->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(arg0->x0_gobj));
                }
            }
            __assert("mpcoll.c", 1374, mpColl_804D3948);
        }
    }
}

#define SOLUTION 0
/// @todo dummy stack in #func_80043324_inline2 breaks this function
void mpColl_80043558(CollData* arg0, s32 arg1)
{
#if SOLUTION == 0
    s32 sp1C;
    void (*sp18)(s32, s32, CollData*, s32, s32, float);
    s32 sp14;
    void (*sp10)(s32, s32, CollData*, s32, s32, float);
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;

    temp_r3 = mpLib_80054C6C(arg1);
    if (temp_r3 == 1) {
        temp_r3_2 = mpLib_80056B6C(arg1);
        if (temp_r3_2 != -1) {
            sp1C = 0;
            mpLib_800580FC(temp_r3_2, &sp18, &sp1C);
            if (sp18 != NULL) {
                (*sp18)(sp1C, temp_r3_2, arg0, arg0->x50, 2, 0.0f);
            }
        }
    } else if (temp_r3 == 2) {
        temp_r3_3 = mpLib_80056B6C(arg1);
        if (temp_r3_3 != -1) {
            sp14 = 0;
            mpLib_800581BC(temp_r3_3, &sp10, &sp14);
            if (sp10 != NULL) {
                (*sp10)(sp14, temp_r3_3, arg0, arg0->x50, 0, 0.0f);
            }
        }
    }
#elif SOLUTION == 1
    enum_t temp_r3 = mpLib_80054C6C(arg1);

    if (temp_r3 == 1) {
        mpColl_80043268(arg0, arg1, 0, 0.0f);
    } else if (temp_r3 == 2) {
        func_80043324_inline2(arg0, arg1, 0, 0.0f);
    }
#endif
}
#undef SOLUTION

void mpColl_80043670(CollData* arg0)
{
    arg0->x130_flags |= 0x20;
}

void mpColl_80043680(CollData* arg0, Vec3* arg1)
{
    arg0->x4_vec = *arg1;
    arg0->x10_vec = arg0->x4_vec;
    arg0->x1C_vec = arg0->x10_vec;
    arg0->x130_flags |= 0x20;
}

void mpColl_800436D8(CollData* arg0, int arg1)
{
    arg0->x36 = arg1;
}

// TODO: float order hack
const float flt_804D7FD8 = 6.0f;
static float six(void)
{
    return flt_804D7FD8;
}

#define M_TAU 6.283185307179586
void mpColl_800436E4(CollData* arg0, float arg1)
{
    float var_f1;

    var_f1 = arg1;
    if (arg0->x104 == 2) {
        if (var_f1 > M_TAU) {
            var_f1 -= M_TAU;
        } else if (var_f1 < -M_TAU) {
            var_f1 += M_TAU;
        }
        arg0->x118_f32 = var_f1;
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

    lbVector_Diff(&arg1->x4_vec, &arg1->x1C_vec, &vel);
    x = fabs_inline(vel.x);
    y = fabs_inline(vel.y);

    dist_left_x = arg1->x84_ecb.left.x - arg1->xA4_ecbCurrCorrect.left.x;
    // if (dist_left_x < 0) dist_left_x = -dist_left_x;
    dist_left_x = fabs_inline(dist_left_x);

    dist_right_x = arg1->x84_ecb.right.x - arg1->xA4_ecbCurrCorrect.right.x;
    if (dist_right_x < 0) {
        dist_right_x = -dist_right_x;
    }

    if (dist_left_x < dist_right_x) {
        dist_left_x = dist_right_x;
    }

    dist_top_y = arg1->x84_ecb.top.y - arg1->xA4_ecbCurrCorrect.top.y;
    // if (dist_top_y < 0) dist_top_y = -dist_top_y;
    dist_top_y = fabs_inline(dist_top_y);

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
    arg1->x4_vec = arg1->x1C_vec;
    arg1->x34_flags.bits.b5 = 0;
    while ((var_r31 < var_r30) && !arg1->x34_flags.bits.b5) {
        mpColl_80042DB0(arg1, 1.0f / (var_r30 - var_r31));
        arg1->x10_vec = arg1->x4_vec;
        lbVector_Add(&arg1->x4_vec, &vel);
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
    temp_f3 = arg0->x4_vec.x + var_f31;
    temp_f4 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.right.y;
    if (var_f31 < 0.0f) {
        var_f31 = -var_f31;
    }
    if (mpLib_800501CC((arg0->ceiling.normal.y * var_f31) + temp_f3,
                       -((arg0->ceiling.normal.x * var_f31) - temp_f4),
                       temp_f3, temp_f4, &arg0->x140, NULL, NULL, NULL,
                       arg0->x48, arg0->x4C) != 0)
    {
        sp10.x = arg0->x140.x - var_f31;
        sp10.y = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (mpLib_8004E090(arg0->ceiling.index, (Vec3*) &sp10, &spC,
                           (u32*) &arg0->ceiling.unk,
                           &arg0->ceiling.normal) != -1)
        {
            arg0->x4_vec.y += spC;
            arg0->x4_vec.x = sp10.x;
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
    temp_f3 = arg0->x4_vec.x + var_f31;
    temp_f4 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.left.y;
    if (var_f31 < 0.0f) {
        var_f31 = -var_f31;
    }
    if (mpLib_800509B8(-((arg0->ceiling.normal.y * var_f31) - temp_f3),
                       ((arg0->ceiling.normal.x * var_f31) + temp_f4), temp_f3,
                       temp_f4, &arg0->x140, NULL, NULL, NULL, arg0->x48,
                       arg0->x4C) != 0)
    {
        sp10.x = arg0->x140.x + var_f31;
        sp10.y = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (mpLib_8004E090(arg0->ceiling.index, &sp10, &spC,
                           &arg0->ceiling.unk, &arg0->ceiling.normal) != -1)
        {
            arg0->x4_vec.y += spC;
            arg0->x4_vec.x = sp10.x;
        }
    }
}

bool mpColl_80043BBC(CollData* arg0, s32* arg1)
{
    s32 sp10;
    s32 temp_r31;
    float new_var;

    temp_r31 = mpLib_80052700(arg0->floor.index);
    new_var = arg0->x4_vec.x + arg0->xA4_ecbCurrCorrect.bottom.x;
    if ((mpLib_800501CC(new_var,
                        arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y,
                        arg0->x4_vec.x + arg0->xA4_ecbCurrCorrect.right.x,
                        arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.right.y,
                        NULL, &sp10, NULL, NULL, arg0->x48, arg0->x4C) != 0) &&
        (sp10 != temp_r31))
    {
        *arg1 = sp10;
        return true;
    }
    return false;
}

void mpColl_80043C6C(CollData* arg0, s32 arg1, s32 arg2)
{
    float sp30;
    float sp24;
    float sp20;
    s32 sp1C;
    s32 sp8;
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;
    float temp_f2;
    float temp_f4;
    float var_f31;

    temp_f1 = arg0->xA4_ecbCurrCorrect.right.x;
    if (temp_f1 < 0.0f) {
        var_f31 = -temp_f1;
    } else {
        var_f31 = temp_f1;
    }
    sp20 = arg0->x4_vec.x + temp_f1;
    temp_f1_2 = arg0->x4_vec.y;
    sp24 = temp_f1_2 + arg0->xA4_ecbCurrCorrect.right.y;
    if (mpLib_8004E398(arg1, &sp20, 0, 0, 0, temp_f1_2) != -1) {
        /// @todo Fix signature of #mpLib_800501CC.
#if false
        if (mpLib_800501CC(&arg0->x140, (s32) &sp1C, 0, 0, arg0->x48,
                           arg0->x4C,
                           -((arg0->floor.normal.y * var_f31) - sp20),
                           (arg0->floor.normal.x * var_f31) + sp24, 0, 0) != 0)
#else
        if (true) {
#endif
            sp20 = arg0->x140.x - var_f31;
            if (arg2 != 0) {
                sp24 = arg0->x4_vec.y;
            } else {
                sp24 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->x4_vec.y += sp30;
                arg0->x4_vec.x = sp20;
            }
        }
    } else {
        mpLib_80054584(arg1, &sp20);
        temp_f4 = 2.0f;
        temp_f2 = sp24;
        temp_f1_3 = sp20 - temp_f4;
        sp20 = -((temp_f4 * var_f31) - temp_f1_3);
        sp24 = -((temp_f4 * (arg0->xA4_ecbCurrCorrect.right.y -
                             arg0->xA4_ecbCurrCorrect.bottom.y)) -
                 temp_f2);
        sp8 = 0;
        if (mpLib_8004F008(&arg0->x140, 0, 0, 0, arg0->x3C, arg0->x48,
                           arg0->x4C, 0, temp_f1_3, temp_f2, sp20, sp24, 0.0f,
                           /* TODO */ 0) != 0)
        {
            sp20 = arg0->x140.x;
            if (arg2 != 0) {
                sp24 = arg0->x4_vec.y;
            } else {
                sp24 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (mpLib_8004DD90(arg0->floor.index, &sp20, &sp30,
                               &arg0->floor.unk, &arg0->floor.normal) != -1)
            {
                arg0->x4_vec.y += sp30;
                arg0->x4_vec.x = sp20;
            }
        }
    }
}

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
        old_x34_flag_b6 = coll->x34_flags.bits.b6;
        horizontal_squeeze_flags = 0;
        if (mpColl_80045B74(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224(coll)) { // Physics_LeftWallCollideAir
                horizontal_squeeze_flags_2 |= 1;
                horizontal_squeeze_flags |= 8;
            }
            x_after_collide_left = coll->x4_vec.x;
        }
        if (mpColl_80044E10(coll)) {     // Physics_RightWallCheckAir
            if (mpColl_800454A4(coll)) { // Physics_RightWallCollideAir
                horizontal_squeeze_flags_2 |= 2;
                horizontal_squeeze_flags |= 4;
            }
            x_after_collide_right = coll->x4_vec.x;
        }
        if (mpColl_80045B74(coll)) {     // Physics_LeftWallCheckAir
            if (mpColl_80046224(coll)) { // Physics_LeftWallCollideAir
                horizontal_squeeze_flags_2 |= 1;
                horizontal_squeeze_flags |= 8;
            }
            x_after_collide_left = coll->x4_vec.x;
        }
        if (mpColl_80044E10(coll)) {     // Physics_RightWallCheckAir
            if (mpColl_800454A4(coll)) { // Physics_RightWallCollideAir
                horizontal_squeeze_flags_2 |= 2;
                horizontal_squeeze_flags |= 4;
            }
            x_after_collide_right = coll->x4_vec.x;
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
            xy_arg_1 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.top.x;
            xy_arg_2 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.top.y;
            xy_arg_3 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.right.x;
            xy_arg_4 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.right.y;
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
            xy_arg_1 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.top.x;
            xy_arg_2 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.top.y;
            xy_arg_3 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.left.x;
            xy_arg_4 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.left.y;
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
            y_after_collide_ceiling = coll->x4_vec.y;
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
                    coll->x34_flags.bits.b5 = 1;
                    touched_floor = 1;
                }
            }
            y_after_collide_floor = coll->x4_vec.y;
            horizontal_squeeze_flags |= 2;
            if (mpColl_80044AD8(coll, horizontal_squeeze_flags_2) &&
                mpColl_80044C74(coll))
            { // Physics_CeilingCheck, Physics_CeilingCollideAir
                temp_r21_3 = mpColl_80052A98(
                    coll->ceiling.index); // Collision_GetNextNonCeilingLine
                xy_arg_1 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.top.x;
                xy_arg_2 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.top.y;
                xy_arg_3 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.right.x;
                xy_arg_4 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.right.y;
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
                xy_arg_1 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.top.x;
                xy_arg_2 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.top.y;
                xy_arg_3 = coll->x4_vec.x + coll->xA4_ecbCurrCorrect.left.x;
                xy_arg_4 = coll->x4_vec.y + coll->xA4_ecbCurrCorrect.left.y;
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
                y_after_collide_ceiling = coll->x4_vec.y;
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
    } while (old_x34_flag_b6 != coll->x34_flags.bits.b6 ||
             horizontal_squeeze_flags != old_horizontal_squeeze_flags);
    if (!touched_floor && (flags & CollisionFlagAir_CanGrabLedge)) {
        var_r3_2 = 1;
        if (!(coll->env_flags & Collide_LeftEdge) &&
            !(coll->env_flags & Collide_RightEdge))
        {
            var_r3_2 = 0;
        }
        if (!var_r3_2 && coll->x4_vec.y < coll->x10_vec.y) {
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

bool mpColl_8004730C(CollData* cdata, ftCollisionBox* arg1)
{
    s32 ret;

    mpColl_80041C8C(cdata);
    mpColl_80042C58(cdata, arg1);
    cdata->prev_env_flags = cdata->env_flags;
    cdata->env_flags = 0;
    if (cdata->xA4_ecbCurrCorrect.top.y - cdata->xA4_ecbCurrCorrect.bottom.y <
            6 &&
        cdata->xA4_ecbCurrCorrect.right.y - cdata->xA4_ecbCurrCorrect.left.y <
            6)
    {
        mpColl_804D649C = true;
    } else {
        mpColl_804D649C = false;
    }
    ret = mpColl_80043754(mpColl_80046904, cdata, 0);
    mpColl_80043324(cdata, ret, true);
    return ret;
}

const float flt_804D7FF8 = 5.0f;
const f64 flt_804D8000 = -0.75;
const f64 flt_804D8008 = 0.75;
const float flt_804D8010 = -3.0f;

bool mpColl_800477E0(CollData* arg0)
{
    float ecb_y;
    float ecb_x;
    bool ret;

    mpColl_80041C8C(arg0);
    if (arg0->x130_flags & 0x10) {
        ecb_x = arg0->x84_ecb.bottom.x;
        ecb_y = arg0->x84_ecb.bottom.y;
    }
    if ((s32) arg0->x104 == 1) {
        mpColl_800424DC(arg0, 6U);
    } else {
        mpColl_8004293C(arg0);
    }
    if (arg0->x130_flags & 0x10) {
        arg0->x84_ecb.bottom.x = ecb_x;
        arg0->x84_ecb.bottom.y = ecb_y;
    }
    mpColl_80042384(arg0);
    arg0->prev_env_flags = arg0->env_flags;
    arg0->env_flags = 0;
    if (((arg0->xA4_ecbCurrCorrect.top.y - arg0->xA4_ecbCurrCorrect.bottom.y) <
         flt_804D7FD8) &&
        ((arg0->xA4_ecbCurrCorrect.right.y - arg0->xA4_ecbCurrCorrect.left.y) <
         flt_804D7FD8))
    {
        mpColl_804D649C = 1;
    } else {
        mpColl_804D649C = 0;
    }
    // mpColl_80043754's return value is mpColl_80046904's return value (the
    // passed in function, scratch here: https://decomp.me/scratch/NL2sf) i.e.
    // var_22, which is only ever set to 0 or 1. Probably a bool
    ret = mpColl_80043754(mpColl_80046904, arg0, 1U);
    mpColl_80043324(arg0, ret, 1);

    return ret;
}
