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

// 80041C78 https://decomp.me/scratch/V6eYQ
void mpColl_80041C78(void)
{
    mpColl_804D64A0 = 0;
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
inline void clamp_above(f32* value, f32 min)
{
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below(f32* value, f32 max)
{
    if (*value > max) {
        *value = max;
    }
}

void mpColl_80041DD0(CollData* cd, u32 flags)
{
    f32 left, bottom, right, top;

    left = cd->xA4_ecbCurrCorrect.left.x + cd->x4_vec.x;
    clamp_below(&left, cd->xC4_ecb.left.x + cd->x10_vec.x);

    right = cd->xA4_ecbCurrCorrect.right.x + cd->x4_vec.x;
    clamp_above(&right, cd->xC4_ecb.right.x + cd->x10_vec.x);

    bottom = cd->xA4_ecbCurrCorrect.bottom.y + cd->x4_vec.y;
    clamp_below(&bottom, cd->xC4_ecb.bottom.y + cd->x10_vec.y);

    top = cd->xA4_ecbCurrCorrect.top.y + cd->x4_vec.y;
    clamp_above(&top, cd->xC4_ecb.top.y + cd->x10_vec.y);

    if (flags & 0b100) {
        f32 x54 = cd->x54;
        f32 tmp = 0.5f * cd->x5C;
        f32 offset;

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
const f32 mpColl_804D7F9C = -F32_MAX;
const f32 mpColl_804D7FA0 = F32_MAX;

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
                     HSD_JObj* arg5, HSD_JObj* arg6, HSD_JObj* arg7, f32 arg9)
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
void mpColl_8004220C(CollData* cd, HSD_GObj* gobj, f32 arg1, f32 arg2,
                     f32 arg3, f32 arg4)
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
void mpColl_80042374(CollData* arg0, f32 arg8, f32 arg9, f32 argA)
{
    arg0->x54 = arg8;
    arg0->x58 = arg9;
    arg0->x5C = argA;
}

// 80042384 https://decomp.me/scratch/P8djI
void mpColl_80042384(CollData* cd)
{
    f32 tmp, tmp2;

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
inline void update_min_max(f32* min, f32* max, f32 val)
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
    f32 left_x, bottom_y;
    f32 right_x, top_y;
    f32 dx, dy;

    f32 phi_f1, phi_f2;
    f32 mid_y;
    f32 tmpval;

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
        f32 temp_x = cd->x4_vec.x;
        f32 temp_y = cd->x4_vec.y;
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
inline void update_min_max_2(f32* min, f32* max, f32 val)
{
    if (*max < val) {
        *max = val;
    } else if (*min > val) {
        *min = val;
    }
}

inline void clamp_above_2(f32* value, f32 min)
{
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below_2(f32* value, f32 max)
{
    if (*value > max) {
        *value = max;
    }
}

void mpColl_8004293C(CollData* cd)
{
    f32 angle;
    f32 sin;
    f32 cos;

    f32 midpoint_x;
    f32 midpoint_y;

    f32 orig_top_y;
    f32 orig_bottom_y;
    f32 orig_right_x;
    f32 orig_left_x;

    f32 top_y;
    f32 bottom_y;
    f32 right_x;
    f32 left_x;

    f32 rot_top_x;
    f32 rot_top_y;
    f32 rot_bot_x;
    f32 rot_bot_y;
    f32 rot_right_x;
    f32 rot_right_y;
    f32 rot_left_y;
    f32 rot_left_x;

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

// 80042C58 https://decomp.me/scratch/pqafT
void mpColl_80042C58(CollData* arg0, ftECB* arg1)
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
    arg0->x84_ecb.top.y = arg1->top.x;
    arg0->x84_ecb.bottom.x = 0.0f;
    arg0->x84_ecb.bottom.y = arg1->top.y;
    arg0->x84_ecb.right.x = arg1->right.x;
    arg0->x84_ecb.right.y = arg1->right.y;
    arg0->x84_ecb.left.x = arg1->bottom.x;
    arg0->x84_ecb.left.y = arg1->bottom.y;
    arg0->x34_flags.bits.b0 = 0;
}

// 80042D24 https://decomp.me/scratch/2MnVj
void mpColl_80042D24(CollData* cd)
{
    f32 saved_bottom_x;
    f32 saved_bottom_y;

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
inline void Vec2_Interpolate(f32 time, Vec2* dest, Vec2* src)
{
    dest->x += time * (src->x - dest->x);
    dest->y += time * (src->y - dest->y);
}

void mpColl_80042DB0(CollData* ecb, f32 time)
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
void mpColl_80043268(CollData* arg0, s32 arg1, s32 arg2, f32 arg8)
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

void func_80043324_inline2(CollData* arg0, s32 arg1, s32 arg2, f32 arg8)
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

void func_80043324_inline(CollData* arg0, s32 arg1, s32 arg2, f32 arg8)
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
    void (*sp18)(s32, s32, CollData*, s32, s32, f32);
    s32 sp14;
    void (*sp10)(s32, s32, CollData*, s32, s32, f32);
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
const f32 flt_804D7FD8 = 6.0f;
static f32 six(void)
{
    return flt_804D7FD8;
}

#define M_TAU 6.283185307179586
void mpColl_800436E4(CollData* arg0, f32 arg1)
{
    f32 var_f1;

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
inline f32 max_inline(f32 a, f32 b)
{
    return (a > b) ? a : b;
}
s32 mpColl_80043754(s32 (*arg0)(void*, u32), CollData* arg1, u32 arg2)
{
    Vec3 vel;

    u8 _[4];

    f32 dist_right_x;
    f32 dist_right_y;
    f32 x;
    f32 y;
    f32 dist_left_x;
    f32 dist_top_y;
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
    f32 spC;
    f32 temp_f3;
    f32 temp_f4;
    f32 var_f31;

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
    f32 spC;
    f32 temp_f3;
    f32 temp_f4;
    f32 var_f31;

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
    f32 new_var;

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
    f32 sp30;
    f32 sp24;
    f32 sp20;
    s32 sp1C;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f2;
    f32 temp_f4;
    f32 var_f31;

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
                           arg0->x4C, 0, temp_f1_3, temp_f2, sp20, sp24,
                           0.0f) != 0)
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

const f32 flt_804D7FF8 = 5.0f;
const f64 flt_804D8000 = -0.75;
const f64 flt_804D8008 = 0.75;
const f32 flt_804D8010 = -3.0f;

bool mpColl_800477E0(CollData* arg0)
{
    f32 ecb_y;
    f32 ecb_x;
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
    arg0->x138 = arg0->env_flags;
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
