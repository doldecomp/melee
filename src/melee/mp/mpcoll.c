// python ../asm-differ/diff.py -mwobs func_X

#include <melee/mp/mpcoll.h>
#include "melee/ft/ftlib.h"
#include <melee/lb/lbunknown_001.h>
#include <melee/lb/lbvector.h>

// TODO: proper signatures, mplib.h
s32 func_80052700();
s32 func_8004F008();
s32 func_80054584();
s32 func_8004DD90();
s32 func_8004E398();

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

void func_80041DD0(CollData* cd, u32 flags) {
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

// TODO: float order hack
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

const char * dummy_string_data = "i<MPCOLL_WALLID_MAX";

// 80043324
void func_80043324_inline2(CollData* arg0, s32 arg1, s32 arg2, f32 arg8) { // see func_80043268
    s32 dummy = 0; // TODO: fake, breaks func_80043558
    void (*callback)(s32, s32, CollData*, s32, s32, f32);
    s32 thing;
    s32 temp_r29;

    temp_r29 = func_80056B6C(arg1);
    if (temp_r29 != -1) {
        thing = 0;
        func_800581BC(temp_r29, &callback, &thing);
        if (callback != 0) {
            (*callback)(thing, temp_r29, arg0, arg0->x50, 0, arg8);
        }
    }
}
void func_80043324_inline(CollData* arg0, s32 arg1, s32 arg2, f32 arg8) {
    // inhibit inlining
    func_80043268(arg0, arg1, arg2, arg8);
}
void func_80043324(CollData* arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    s32 temp_r3_2;

    if (arg0->x14C_ground.index != -1) {
        temp_r3 = func_801CA284(&arg0->x4_vec, arg0->x14C_ground.index);
        if (temp_r3 != 0) {
            arg0->x14C_ground.unk = (arg0->x14C_ground.unk & 0xFFFFFF00) | (temp_r3 & 0xFF);
        }
    }
    if ((arg1 != 0) || (arg0->x134_envFlags & 0x800000) || (arg0->x134_envFlags & 0x100000) || (arg0->x134_envFlags & 0x200000)) {
        func_80043324_inline(arg0, arg0->x14C_ground.index, arg2, arg0->x4_vec.y - arg0->x1C_vec.y);
    }
    if (arg0->x134_envFlags & 0x6000) {
        func_80043324_inline2(arg0, arg0->x188_ceiling.index, arg2, arg0->x4_vec.y - arg0->x1C_vec.y);
    }
    if (g_debugLevel >= 3) {
        if (!(arg0->x4_vec.x < 45000.0f) || !(arg0->x4_vec.x > -45000.0f) || !(arg0->x4_vec.y < 45000.0f) || !(arg0->x4_vec.y > -45000.0f)) {
            if (func_80086960(arg0->x0_gobj)) {
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) ply=%d ms=%d\n", "mpcoll.c", 1350, arg0->x1C_vec.x, arg0->x1C_vec.y, arg0->x4_vec.x, arg0->x4_vec.y, func_80086BE0(arg0->x0_gobj), func_800874BC(arg0->x0_gobj));
            } else {
                s32 gobjid = arg0->x0_gobj->classifier;
                OSReport("%s:%d: Error: mpCollEnd() last(%f,%f) pos(%f,%f) gobjid=%d\n", "mpcoll.c", 1358, arg0->x1C_vec.x, arg0->x1C_vec.y, arg0->x4_vec.x, arg0->x4_vec.y, gobjid);
                if (arg0->x0_gobj->p_link == 9) {
                    OSReport("itkind=%d\n", itGetKind(arg0->x0_gobj));
                }
            }
            __assert("mpcoll.c", 1374, "0");
        }
    }
}

// 80043558
void func_80043558(CollData* arg0, s32 arg1) {
#ifdef NON_MATCHING // TODO: dummy stack in func_80043324_inline2 breaks this function
    s32 temp_r3;

    temp_r3 = func_80054C6C(arg1);
    if (temp_r3 == 1) {
        func_80043268(arg0, arg1, 0, 0.0f);
    } else if (temp_r3 == 2) {
        func_80043324_inline2(arg0, arg1, 0, 0.0f);
    }
#else
    s32 sp1C;
    void (*sp18)(s32, s32, CollData*, s32, s32, f32);
    s32 sp14;
    void (*sp10)(s32, s32, CollData*, s32, s32, f32);
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;

    temp_r3 = func_80054C6C(arg1);
    if (temp_r3 == 1) {
        temp_r3_2 = func_80056B6C(arg1);
        if (temp_r3_2 != -1) {
            sp1C = 0;
            func_800580FC(temp_r3_2, &sp18, &sp1C);
            if (sp18 != NULL) {
                (*sp18)(sp1C, temp_r3_2, arg0, arg0->x50, 2, 0.0f);
            }
        }
    } else if (temp_r3 == 2) {
        temp_r3_3 = func_80056B6C(arg1);
        if (temp_r3_3 != -1) {
            sp14 = 0;
            func_800581BC(temp_r3_3, &sp10, &sp14);
            if (sp10 != NULL) {
                (*sp10)(sp14, temp_r3_3, arg0, arg0->x50, 0, 0.0f);
            }
        }
    }
#endif
}

// 80043670
void func_80043670(CollData* arg0) {
    arg0->x130_flags |= 0x20;
}

// 80043680
void func_80043680(CollData* arg0, Vec3* arg1) {
    arg0->x4_vec = *arg1;
    arg0->x10_vec = arg0->x4_vec;
    arg0->x1C_vec = arg0->x10_vec;
    arg0->x130_flags |= 0x20;
}

// 800436D8
void func_800436D8(CollData* arg0, s32 arg1) {
    arg0->x36 = arg1;
}

// TODO: float order hack
const f32 flt_804D7FD8 = 6.0f;
static f32 six(void) {
    return flt_804D7FD8;
}

// 800436E4
#define M_TAU 6.283185307179586
void func_800436E4(CollData* arg0, f32 arg1) {
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
inline f32 max_inline(f32 a, f32 b) {
    return (a > b) ? a : b;
}
s32 func_80043754(s32 (*arg0)(void*, u32), CollData* arg1, u32 arg2) {
    Vec3 vel;
    f32 unused;
    f32 dist_right_x;
    f32 dist_right_y;
    f32 x;
    f32 y;
    f32 dist_left_x;
    f32 dist_top_y;
    s32 var_r31;
    s32 var_r30;
    s32 ret;

    lbvector_Diff(&arg1->x4_vec, &arg1->x1C_vec, &vel);
    x = fabs_inline(vel.x);
    y = fabs_inline(vel.y);

    dist_left_x = arg1->x84_ecb.left.x - arg1->xA4_ecbCurrCorrect.left.x;
    // if (dist_left_x < 0) dist_left_x = -dist_left_x;
    dist_left_x = fabs_inline(dist_left_x);

    dist_right_x = arg1->x84_ecb.right.x - arg1->xA4_ecbCurrCorrect.right.x;
    if (dist_right_x < 0) dist_right_x = -dist_right_x;

    if (dist_left_x < dist_right_x) {
        dist_left_x = dist_right_x;
    }

    dist_top_y = arg1->x84_ecb.top.y - arg1->xA4_ecbCurrCorrect.top.y;
    // if (dist_top_y < 0) dist_top_y = -dist_top_y;
    dist_top_y = fabs_inline(dist_top_y);

    dist_right_y = arg1->x84_ecb.right.y - arg1->xA4_ecbCurrCorrect.right.y;
    if (dist_right_y < 0) dist_right_y = -dist_right_y;

    if (dist_top_y < dist_right_y) {
        dist_top_y = dist_right_y;
    }

    x = max_inline(x, dist_left_x);
    y = max_inline(y, dist_top_y);
    x = max_inline(x, y);

    if (x > flt_804D7FD8) { //6.0f float order hack
        var_r30 = (s32) (x / flt_804D7FD8); //6.0f float order hack
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
        func_80042DB0(arg1, 1.0f / (var_r30 - var_r31));
        arg1->x10_vec = arg1->x4_vec;
        lbvector_Add(&arg1->x4_vec, &vel);
        func_80041DD0(arg1, arg2);
        ret = (*arg0)(arg1, arg2);
        func_80058AA0();
        var_r31 += 1;
        arg1->x38 = lbl_804D64AC;
    }
    return ret;
}

// 800439FC https://decomp.me/scratch/T1yAJ
void func_800439FC(CollData* arg0) {
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
    if (func_800501CC(
            (arg0->x188_ceiling.normal.y * var_f31) + temp_f3,
            -((arg0->x188_ceiling.normal.x * var_f31) - temp_f4),
            temp_f3, temp_f4,
            &arg0->x140,
            NULL, NULL, NULL,
            arg0->x48, arg0->x4C) != 0) {
        sp10.x = arg0->x140.x - var_f31;
        sp10.y = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (func_8004E090(arg0->x188_ceiling.index, (Point3d* ) &sp10, &spC, (u32* ) &arg0->x188_ceiling.unk, &arg0->x188_ceiling.normal) != -1) {
            arg0->x4_vec.y += spC;
            arg0->x4_vec.x = sp10.x;
        }
    }
}

// 80043ADC
void func_80043ADC(CollData* arg0) {
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
    if (func_800509B8(-((arg0->x188_ceiling.normal.y * var_f31) - temp_f3), ((arg0->x188_ceiling.normal.x * var_f31) + temp_f4), temp_f3, temp_f4, &arg0->x140, NULL, NULL, NULL, arg0->x48, arg0->x4C) != 0) {
        sp10.x = arg0->x140.x + var_f31;
        sp10.y = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.top.y;
        if (func_8004E090(arg0->x188_ceiling.index, &sp10, &spC, &arg0->x188_ceiling.unk, &arg0->x188_ceiling.normal) != -1) {
            arg0->x4_vec.y += spC;
            arg0->x4_vec.x = sp10.x;
        }
    }
}

// 80043BBC
s32 func_80043BBC(CollData* arg0, s32* arg1) {
    s32 sp10;
    s32 temp_r31;
    f32 new_var;

    temp_r31 = func_80052700(arg0->x14C_ground.index);
    new_var = arg0->x4_vec.x + arg0->xA4_ecbCurrCorrect.bottom.x;
    if ((func_800501CC(
            new_var,
            arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y,
            arg0->x4_vec.x + arg0->xA4_ecbCurrCorrect.right.x,
            arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.right.y,
            NULL, &sp10, NULL, NULL, arg0->x48, arg0->x4C)
        != 0) && (sp10 != temp_r31)) {
        *arg1 = sp10;
        return 1;
    }
    return 0;
}

// 80043C6C
#ifdef NON_MATCHING
void func_80043C6C(CollData* arg0, s32 arg1, s32 arg2) {
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
    if (func_8004E398(arg1, &sp20, 0, 0, 0, temp_f1_2) != -1) {
        if (func_800501CC(&arg0->x140, (s32) &sp1C, 0, 0, arg0->x48, arg0->x4C, -((arg0->x14C_ground.normal.y * var_f31) - sp20), (arg0->x14C_ground.normal.x * var_f31) + sp24) != 0) {
            sp20 = arg0->x140.x - var_f31;
            if (arg2 != 0) {
                sp24 = arg0->x4_vec.y;
            } else {
                sp24 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (func_8004DD90(arg0->x14C_ground.index, &sp20, &sp30, &arg0->x14C_ground.unk, &arg0->x14C_ground.normal) != -1) {
                arg0->x4_vec.y += sp30;
                arg0->x4_vec.x = sp20;
            }
        }
    } else {
        func_80054584(arg1, &sp20);
        temp_f4 = 2.0f;
        temp_f2 = sp24;
        temp_f1_3 = sp20 - temp_f4;
        sp20 = -((temp_f4 * var_f31) - temp_f1_3);
        sp24 = -((temp_f4 * (arg0->xA4_ecbCurrCorrect.right.y - arg0->xA4_ecbCurrCorrect.bottom.y)) - temp_f2);
        sp8 = 0;
        if (func_8004F008(&arg0->x140, 0, 0, 0, arg0->x3C, arg0->x48, arg0->x4C, 0, temp_f1_3, temp_f2, sp20, sp24, 0.0f) != 0) {
            sp20 = arg0->x140.x;
            if (arg2 != 0) {
                sp24 = arg0->x4_vec.y;
            } else {
                sp24 = arg0->x4_vec.y + arg0->xA4_ecbCurrCorrect.bottom.y;
            }
            if (func_8004DD90(arg0->x14C_ground.index, &sp20, &sp30, &arg0->x14C_ground.unk, &arg0->x14C_ground.normal) != -1) {
                arg0->x4_vec.y += sp30;
                arg0->x4_vec.x = sp20;
            }
        }
    }
}
#else
asm void func_80043C6C() {
    nofralloc
/* 80043C6C 0004084C  7C 08 02 A6 */	mflr r0
/* 80043C70 00040850  90 01 00 04 */	stw r0, 4(r1)
/* 80043C74 00040854  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80043C78 00040858  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80043C7C 0004085C  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80043C80 00040860  3B E5 00 00 */	addi r31, r5, 0
/* 80043C84 00040864  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80043C88 00040868  3B C4 00 00 */	addi r30, r4, 0
/* 80043C8C 0004086C  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 80043C90 00040870  7C 7D 1B 78 */	mr r29, r3
/* 80043C94 00040874  C0 02 85 C4 */	lfs f0, 0.0f
/* 80043C98 00040878  C0 23 00 B4 */	lfs f1, 0xb4(r3)
/* 80043C9C 0004087C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80043CA0 00040880  40 80 00 0C */	bge lbl_80043CAC
/* 80043CA4 00040884  FF E0 08 50 */	fneg f31, f1
/* 80043CA8 00040888  48 00 00 08 */	b lbl_80043CB0
lbl_80043CAC:
/* 80043CAC 0004088C  FF E0 08 90 */	fmr f31, f1
lbl_80043CB0:
/* 80043CB0 00040890  C0 1D 00 04 */	lfs f0, 4(r29)
/* 80043CB4 00040894  7F C3 F3 78 */	mr r3, r30
/* 80043CB8 00040898  38 81 00 20 */	addi r4, r1, 0x20
/* 80043CBC 0004089C  EC 00 08 2A */	fadds f0, f0, f1
/* 80043CC0 000408A0  38 A0 00 00 */	li r5, 0
/* 80043CC4 000408A4  38 C0 00 00 */	li r6, 0
/* 80043CC8 000408A8  38 E0 00 00 */	li r7, 0
/* 80043CCC 000408AC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80043CD0 000408B0  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80043CD4 000408B4  C0 1D 00 B8 */	lfs f0, 0xb8(r29)
/* 80043CD8 000408B8  EC 01 00 2A */	fadds f0, f1, f0
/* 80043CDC 000408BC  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80043CE0 000408C0  48 00 A6 B9 */	bl func_8004E398
/* 80043CE4 000408C4  2C 03 FF FF */	cmpwi r3, -1
/* 80043CE8 000408C8  41 82 00 AC */	beq lbl_80043D94
/* 80043CEC 000408CC  C0 61 00 20 */	lfs f3, 0x20(r1)
/* 80043CF0 000408D0  38 7D 01 40 */	addi r3, r29, 0x140
/* 80043CF4 000408D4  C0 3D 01 58 */	lfs f1, 0x158(r29)
/* 80043CF8 000408D8  38 81 00 1C */	addi r4, r1, 0x1c
/* 80043CFC 000408DC  C0 81 00 24 */	lfs f4, 0x24(r1)
/* 80043D00 000408E0  C0 1D 01 54 */	lfs f0, 0x154(r29)
/* 80043D04 000408E4  EC 21 1F FC */	fnmsubs f1, f1, f31, f3
/* 80043D08 000408E8  80 FD 00 48 */	lwz r7, 0x48(r29)
/* 80043D0C 000408EC  38 A0 00 00 */	li r5, 0
/* 80043D10 000408F0  EC 40 27 FA */	fmadds f2, f0, f31, f4
/* 80043D14 000408F4  81 1D 00 4C */	lwz r8, 0x4c(r29)
/* 80043D18 000408F8  38 C0 00 00 */	li r6, 0
/* 80043D1C 000408FC  48 00 C4 B1 */	bl func_800501CC
/* 80043D20 00040900  2C 03 00 00 */	cmpwi r3, 0
/* 80043D24 00040904  41 82 01 4C */	beq lbl_80043E70
/* 80043D28 00040908  C0 1D 01 40 */	lfs f0, 0x140(r29)
/* 80043D2C 0004090C  2C 1F 00 00 */	cmpwi r31, 0
/* 80043D30 00040910  EC 00 F8 28 */	fsubs f0, f0, f31
/* 80043D34 00040914  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80043D38 00040918  41 82 00 10 */	beq lbl_80043D48
/* 80043D3C 0004091C  C0 1D 00 08 */	lfs f0, 8(r29)
/* 80043D40 00040920  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80043D44 00040924  48 00 00 14 */	b lbl_80043D58
lbl_80043D48:
/* 80043D48 00040928  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80043D4C 0004092C  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80043D50 00040930  EC 01 00 2A */	fadds f0, f1, f0
/* 80043D54 00040934  D0 01 00 24 */	stfs f0, 0x24(r1)
lbl_80043D58:
/* 80043D58 00040938  80 7D 01 4C */	lwz r3, 0x14c(r29)
/* 80043D5C 0004093C  38 81 00 20 */	addi r4, r1, 0x20
/* 80043D60 00040940  38 A1 00 30 */	addi r5, r1, 0x30
/* 80043D64 00040944  38 DD 01 50 */	addi r6, r29, 0x150
/* 80043D68 00040948  38 FD 01 54 */	addi r7, r29, 0x154
/* 80043D6C 0004094C  48 00 A0 25 */	bl func_8004DD90
/* 80043D70 00040950  2C 03 FF FF */	cmpwi r3, -1
/* 80043D74 00040954  41 82 00 FC */	beq lbl_80043E70
/* 80043D78 00040958  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80043D7C 0004095C  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80043D80 00040960  EC 01 00 2A */	fadds f0, f1, f0
/* 80043D84 00040964  D0 1D 00 08 */	stfs f0, 8(r29)
/* 80043D88 00040968  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80043D8C 0004096C  D0 1D 00 04 */	stfs f0, 4(r29)
/* 80043D90 00040970  48 00 00 E0 */	b lbl_80043E70
lbl_80043D94:
/* 80043D94 00040974  38 7E 00 00 */	addi r3, r30, 0
/* 80043D98 00040978  38 81 00 20 */	addi r4, r1, 0x20
/* 80043D9C 0004097C  48 01 07 E9 */	bl func_80054584
/* 80043DA0 00040980  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80043DA4 00040984  38 00 00 00 */	li r0, 0
/* 80043DA8 00040988  C0 82 85 E4 */	lfs f4, 2.0f
/* 80043DAC 0004098C  38 7D 01 40 */	addi r3, r29, 0x140
/* 80043DB0 00040990  C0 41 00 24 */	lfs f2, 0x24(r1)
/* 80043DB4 00040994  EC 20 20 28 */	fsubs f1, f0, f4
/* 80043DB8 00040998  38 80 00 00 */	li r4, 0
/* 80043DBC 0004099C  38 A0 00 00 */	li r5, 0
/* 80043DC0 000409A0  38 C0 00 00 */	li r6, 0
/* 80043DC4 000409A4  EC 04 0F FC */	fnmsubs f0, f4, f31, f1
/* 80043DC8 000409A8  39 40 00 00 */	li r10, 0
/* 80043DCC 000409AC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80043DD0 000409B0  C0 7D 00 B8 */	lfs f3, 0xb8(r29)
/* 80043DD4 000409B4  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80043DD8 000409B8  EC 03 00 28 */	fsubs f0, f3, f0
/* 80043DDC 000409BC  EC 04 10 3C */	fnmsubs f0, f4, f0, f2
/* 80043DE0 000409C0  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80043DE4 000409C4  90 01 00 08 */	stw r0, 8(r1)
/* 80043DE8 000409C8  C0 61 00 20 */	lfs f3, 0x20(r1)
/* 80043DEC 000409CC  C0 81 00 24 */	lfs f4, 0x24(r1)
/* 80043DF0 000409D0  C0 A2 85 C4 */	lfs f5, 0.0f
/* 80043DF4 000409D4  80 FD 00 3C */	lwz r7, 0x3c(r29)
/* 80043DF8 000409D8  81 1D 00 48 */	lwz r8, 0x48(r29)
/* 80043DFC 000409DC  81 3D 00 4C */	lwz r9, 0x4c(r29)
/* 80043E00 000409E0  48 00 B2 09 */	bl func_8004F008
/* 80043E04 000409E4  2C 03 00 00 */	cmpwi r3, 0
/* 80043E08 000409E8  41 82 00 68 */	beq lbl_80043E70
/* 80043E0C 000409EC  C0 1D 01 40 */	lfs f0, 0x140(r29)
/* 80043E10 000409F0  2C 1F 00 00 */	cmpwi r31, 0
/* 80043E14 000409F4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80043E18 000409F8  41 82 00 10 */	beq lbl_80043E28
/* 80043E1C 000409FC  C0 1D 00 08 */	lfs f0, 8(r29)
/* 80043E20 00040A00  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80043E24 00040A04  48 00 00 14 */	b lbl_80043E38
lbl_80043E28:
/* 80043E28 00040A08  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80043E2C 00040A0C  C0 1D 00 B0 */	lfs f0, 0xb0(r29)
/* 80043E30 00040A10  EC 01 00 2A */	fadds f0, f1, f0
/* 80043E34 00040A14  D0 01 00 24 */	stfs f0, 0x24(r1)
lbl_80043E38:
/* 80043E38 00040A18  80 7D 01 4C */	lwz r3, 0x14c(r29)
/* 80043E3C 00040A1C  38 81 00 20 */	addi r4, r1, 0x20
/* 80043E40 00040A20  38 A1 00 30 */	addi r5, r1, 0x30
/* 80043E44 00040A24  38 DD 01 50 */	addi r6, r29, 0x150
/* 80043E48 00040A28  38 FD 01 54 */	addi r7, r29, 0x154
/* 80043E4C 00040A2C  48 00 9F 45 */	bl func_8004DD90
/* 80043E50 00040A30  2C 03 FF FF */	cmpwi r3, -1
/* 80043E54 00040A34  41 82 00 1C */	beq lbl_80043E70
/* 80043E58 00040A38  C0 3D 00 08 */	lfs f1, 8(r29)
/* 80043E5C 00040A3C  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80043E60 00040A40  EC 01 00 2A */	fadds f0, f1, f0
/* 80043E64 00040A44  D0 1D 00 08 */	stfs f0, 8(r29)
/* 80043E68 00040A48  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80043E6C 00040A4C  D0 1D 00 04 */	stfs f0, 4(r29)
lbl_80043E70:
/* 80043E70 00040A50  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80043E74 00040A54  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80043E78 00040A58  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80043E7C 00040A5C  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80043E80 00040A60  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80043E84 00040A64  38 21 00 50 */	addi r1, r1, 0x50
/* 80043E88 00040A68  7C 08 03 A6 */	mtlr r0
/* 80043E8C 00040A6C  4E 80 00 20 */	blr 
}
#pragma peephole on
#endif

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

const f32 flt_804D7FF8 = 5.0f;
const f64 flt_804D8000 = -0.75;
const f64 flt_804D8008 = 0.75;
const f32 flt_804D8010 = -3.0f;
