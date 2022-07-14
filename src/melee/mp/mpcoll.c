#include "mpcoll.h"
#include "melee/ft/ftlib.h"
#include "melee/lb/code_8000B074.h"

extern s32 lbl_804D64A0;
extern s32 lbl_804D64A4;
extern s32 lbl_804D64A8;
extern u32 lbl_804D64AC;

// 80041C78 https://decomp.me/scratch/V6eYQ
void func_80041C78(void) {
    lbl_804D64A0 = 0;
    lbl_804D64A4 = 0;
    lbl_804D64A8 = 0;
}

// 80041C8C https://decomp.me/scratch/VvSaI
void func_80041C8C(CollData* cd) {
    u32 unused[2];

    lbl_804D64A0 = 0;
    lbl_804D64A4 = 0;
    if (g_debugLevel >= 3) {
        if (!(cd->x4_vec.x < 45000.0f) || !(cd->x4_vec.x > -45000.0f) ||
            !(cd->x4_vec.y < 45000.0f) || !(cd->x4_vec.y > -45000.0f)) {

            if (func_80086960(cd->x0_gobj) != 0) {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) player=%d ms=%d\n",
                    "mpcoll.c", 203,
                    func_80086BE0(cd->x0_gobj), func_800874BC(cd->x0_gobj),
                    cd->x4_vec.x, cd->x4_vec.y);
            } else {
                OSReport("%s:%d: Error: mpCollPrev() pos(%f,%f) gobj_id=%d\n",
                    "mpcoll.c", 212, cd->x0_gobj->classifier,
                    cd->x4_vec.x, cd->x4_vec.y);
                if (cd->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(cd->x0_gobj));
                }
            }
            __assert("mpcoll.c", 228, "0");
        }
    }
    cd->x28_vec = cd->x4_vec;
}

// 80041DD0 https://decomp.me/scratch/1KPLe
inline void clamp_above(f32* value, f32 min) {
    if (*value < min) {
        *value = min;
    }
}

inline void clamp_below(f32* value, f32 max) {
    if (*value > max) {
        *value = max;
    }
}

void func_80041DD0(CollData* cd, u8 flags) {
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

    func_800588D0(left, bottom, right, top);
}

// dummy float order hack
const f32 lbl_804D7F9C = -FLT_MAX;
const f32 lbl_804D7FA0 = FLT_MAX;

// 80041EE4 https://decomp.me/scratch/j2TXK
// CollDataInit
void func_80041EE4(CollData* cd) {
    cd->x0_gobj = NULL;
    cd->x34_flags.bits.b0 = 1;
    cd->x34_flags.bits.b6 = 0;
    cd->x34_flags.bits.b7 = 0;
    cd->x35_flags.bits.b0 = 1;
    cd->x34_flags.bits.b1234 = 0;
    cd->x134_envFlags = 0;
    cd->x130_flags = 0;
    cd->x10_vec = cd->x4_vec;
    cd->x1C_vec = cd->x4_vec;
    cd->x28_vec = cd->x4_vec;
    cd->x3C = -1;
    cd->x40 = -1;
    cd->x44 = -1;
    cd->x14C_ground.index = -1;
    cd->x14C_ground.unk = 0;
    cd->x14C_ground.normal.x = 0.0f;
    cd->x14C_ground.normal.y = 1.0f;
    cd->x14C_ground.normal.z = 0.0f;
    cd->x188_ceiling.index = -1;
    cd->x188_ceiling.unk = 0;
    cd->x188_ceiling.normal.x = 0.0f;
    cd->x188_ceiling.normal.y = -1.0f;
    cd->x188_ceiling.normal.z = 0.0f;
    cd->x174_leftwall.index = -1;
    cd->x174_leftwall.unk = 0;
    cd->x174_leftwall.normal.x = 0.0f;
    cd->x174_leftwall.normal.y = 1.0f;
    cd->x174_leftwall.normal.z = 0.0f;
    cd->x160_rightwall.index = -1;
    cd->x160_rightwall.unk = 0;
    cd->x160_rightwall.normal.x = 0.0f;
    cd->x160_rightwall.normal.y = -1.0f;
    cd->x160_rightwall.normal.z = 0.0f;
    cd->x38 = lbl_804D64AC;
    cd->x50 = 0.0f;
    cd->x48 = -1;
    cd->x4C = -1;
    cd->x54 = 0.0f;
    cd->x58 = 0.0f;
    cd->x5C = 0.0f;
    func_8000C160(&cd->xA4_ecbCurrCorrect, sizeof(ftECB));
    func_8000C160(&cd->xC4_ecb, sizeof(ftECB));
    func_8000C160(&cd->xE4_ecb, sizeof(ftECB));
    func_8000C160(&cd->x104, 0x2C);
    func_8000C160(&cd->x84_ecb, sizeof(ftECB));
    func_8000C160(&cd->x64_ecb, sizeof(ftECB));
}

// 80042078 https://decomp.me/scratch/hM7h8
void func_80042078(CollData* cd, HSD_GObj* gobj,
        HSD_JObj* arg1, HSD_JObj* arg2, HSD_JObj* arg3, HSD_JObj* arg4,
        HSD_JObj* arg5, HSD_JObj* arg6, HSD_JObj* arg7, f32 arg9) {
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
        cd->x64_ecb  = cd->xA4_ecbCurrCorrect;
        cd->x84_ecb = cd->xA4_ecbCurrCorrect;
    }
    cd->x36 = -1;
    cd->x50 = 0.0f;
}

// 8004220C https://decomp.me/scratch/nOinn
void func_8004220C(CollData* cd, HSD_GObj* gobj, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
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
void func_80042374(CollData* arg0, f32 arg8, f32 arg9, f32 argA) {
    arg0->x54 = arg8;
    arg0->x58 = arg9;
    arg0->x5C = argA;
}

// 80042384 https://decomp.me/scratch/P8djI
void func_80042384(CollData* cd) {
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
    if (tmp - tmp2 < 0.001f ||
        tmp2 - cd->x84_ecb.bottom.y < 0.001f)
    {
        cd->x84_ecb.right.y = 0.5f * (tmp + cd->x84_ecb.bottom.y);
    }
    tmp = cd->x84_ecb.top.y;
    tmp2 = cd->x84_ecb.left.y;
    if (tmp - tmp2 < 0.001f ||
        tmp2 - cd->x84_ecb.bottom.y < 0.001f)
    {
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

void func_800424DC(CollData* cd, u32 flags) {
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
        func_8000B1CC(cd->x10C_joint[0], NULL, &vec);
        left_x = right_x = vec.x - temp_x;
        bottom_y = top_y = vec.y - temp_y;

        #define EXPAND_ECB_FOR(joint) \
        func_8000B1CC(joint, NULL, &vec);\
        dx = vec.x - temp_x;\
        dy = vec.y - temp_y;\
        update_min_max(&left_x, &right_x, dx);\
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

void func_8004293C(CollData* cd) {
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
void func_80042C58(CollData* arg0, ftECB* arg1) {
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
void func_80042D24(CollData* cd) {
    f32 saved_bottom_x;
    f32 saved_bottom_y;

    if ((cd->x130_flags & 0x10) != 0) {
        saved_bottom_x = cd->x84_ecb.bottom.x;
        saved_bottom_y = cd->x84_ecb.bottom.y;
    }
    if (cd->x104 == 1) {
        func_800424DC(cd, 6);
    } else {
        func_8004293C(cd);
    }
    if ((cd->x130_flags & 0x10) != 0) {
        cd->x84_ecb.bottom.x = saved_bottom_x;
        cd->x84_ecb.bottom.y = saved_bottom_y;
    }
    func_80042384(cd);
}

// 80042DB0 https://decomp.me/scratch/GbMpk
inline void Vec2_Interpolate(f32 time, Vec2 *dest, Vec2 *src) {
    dest->x += time * (src->x - dest->x);
    dest->y += time * (src->y - dest->y);
}

void func_80042DB0(CollData* ecb, f32 time) {
    ecb->xC4_ecb = ecb->xA4_ecbCurrCorrect;
    if (ecb->x34_flags.bits.b6) {
        ecb->xA4_ecbCurrCorrect = ecb->x64_ecb;
        ecb->x34_flags.bits.b6 = 0;
    }
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.top, &ecb->x84_ecb.top);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.bottom, &ecb->x84_ecb.bottom);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.left, &ecb->x84_ecb.left);
    Vec2_Interpolate(time, &ecb->xA4_ecbCurrCorrect.right, &ecb->x84_ecb.right);
    if (fpclassify(ecb->xA4_ecbCurrCorrect.top.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.top.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.bottom.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.bottom.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.left.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.left.y) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.right.x) == FP_NAN ||
        fpclassify(ecb->xA4_ecbCurrCorrect.right.y) == FP_NAN
    ) {
        OSReport("error\n");
        __assert("mpcoll.c", 1193, "0");
    }
}

// 80043268 https://decomp.me/scratch/GNwej
void func_80043268(CollData* arg0, s32 arg1, s32 arg2, f32 arg8) {
    void (*sp1C)(s32, s32, CollData*, s32, s32, f32);
    s32 sp18;
    s32 temp_r31;

    temp_r31 = func_80056B6C(arg1);
    if (temp_r31 != -1) {
        sp18 = 0;
        func_800580FC(temp_r31, &sp1C, &sp18);
        if (sp1C != 0) {
            s32 thing;
            if (arg2 == 0) {
                thing = 2;
            } else {
                thing = 1;
            }
            (*sp1C)(sp18, temp_r31, arg0, arg0->x50, thing, arg8);
        }
    }
}

// 80043324 https://decomp.me/scratch/NKVUX !
// 80043558
// 80043670
// 80043680
// 800436D8
// 800436E4
// 80043754
// 800439FC
// 80043ADC
// 80043BBC
// 80043C6C
// 80043E90
// 80043F40
// 80044164
// 800443C4
// 80044628
// 80044838
// 80044948
// 80044AD8
// 80044C74
// 80044E10
// 800454A4
// 80045B74
// 80046224
// 80046904
// 800471F8
// 8004730C
// 800473CC
// 800474E0
// 800475F4
// 800476B4
// 800477E0
// 800478F4
// 80047A08
// 80047AC8
// 80047BF4
// 80047D20
// 80047E14
// 80047F40
// 8004806C
// 80048160
// 80048274
// 80048388
// 80048464
// 80048578
// 80048654
// 80048768
// 80048844
// 800488F4
// 80048AB0
// 800491C8
// 80049778
// 80049EAC
// 8004A45C
// 8004A678
// 8004A908
// 8004AB80
// 8004B108
// 8004B21C
// 8004B2DC
// 8004B3F0
// 8004B4B0
// 8004B5C4
// 8004B6D8
// 8004B894
// 8004BDD4
// 8004C328
// 8004C750
// 8004C864
// 8004C91C
// 8004CA6C
// 8004CAA0
// 8004CAE8
// 8004CB30
// 8004CB78
// 8004CBC0
// 8004CBE8
// 8004CBF4
// 8004CC00
// 8004D024

const f32 lbl_804D7FD8 = 6.0f;
const f64 lbl_804D7FE0 = 6.283185307179586; // 2 * PI
const f64 lbl_804D7FE8 = -6.283185307179586; // -2 * PI
const f64 lbl_804D7FF0 = 4503601774854144.0; // magic signed conversion constant
const f32 lbl_804D7FF8 = 5.0f;
const f64 lbl_804D8000 = -0.75;
const f64 lbl_804D8008 = 0.75;
const f32 lbl_804D8010 = -3.0f;
