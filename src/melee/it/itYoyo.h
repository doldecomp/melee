#ifndef _itYoyo_h_
#define _itYoyo_h_

#include <dolphin/types.h>

typedef struct itYoyoAttributes
{
    s32 x0_CHARGE_SPAWN_POS;
    s32 x4_UPSMASH_CHARGE_STRING_LENGTH;
    s32 x8_DOWNSMASH_CHARGE_STRING_LENGTH;
    f32 xC_SIZE;
    f32 x10_UNK1;
    f32 x14_UNK2_RAD;
    f32 x18_SPIN_TEXANIM_SPEED;
    f32 x1C_UNK_TEXANIM_SPEED;
    f32 x20_UNK_TEXANIM_MOD;
    f32 x24_YOYO_RELEASE_VEL_X;
    f32 x28_YOYO_PULL_STRENGTH;
    f32 x2C_UNK3_MOD; // Resistance multiplier? //
    f32 x30_YOYO_RELEASE_VEL_Y;
    f32 x34_GRAVITY;
    f32 x38_GRAVITY_MOD;
    f32 x3C_YOYO_PULL_STRENGTH_2;
    s32 x40_UPSMASH_YOYO_ROT_FRAME;
    s32 x44_UPSMASH_YOYO_NUDGE_FRAME;
    s32 x48_DOWNSMASH_YOYO_ROT_FRAME;
    s32 x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
    s32 x50_UNK4;
    s32 x54_UNK5;
    s32 x58_UNK6;
    s32 x5C_UNK7;
}itYoyoAttributes;

#endif