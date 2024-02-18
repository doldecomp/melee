#ifndef MELEE_IT_ITYOYO_H
#define MELEE_IT_ITYOYO_H

#include <platform.h>

typedef struct itYoyoAttributes {
    s32 x0_CHARGE_SPAWN_POS;
    s32 x4_UPSMASH_CHARGE_STRING_LENGTH;
    s32 x8_DOWNSMASH_CHARGE_STRING_LENGTH;
    float xC_SIZE;
    float x10_UNK1;
    float x14_UNK2_RAD;
    float x18_SPIN_TEXANIM_SPEED;
    float x1C_UNK_TEXANIM_SPEED;
    float x20_UNK_TEXANIM_MOD;
    float x24_YOYO_RELEASE_VEL_X;
    float x28_YOYO_PULL_STRENGTH;
    float x2C_UNK3_MOD; // Resistance multiplier?
    float x30_YOYO_RELEASE_VEL_Y;
    float x34_GRAVITY;
    float x38_GRAVITY_MOD;
    float x3C_YOYO_PULL_STRENGTH_2;
    s32 x40_UPSMASH_YOYO_ROT_FRAME;
    s32 x44_UPSMASH_YOYO_NUDGE_FRAME;
    s32 x48_DOWNSMASH_YOYO_ROT_FRAME;
    s32 x4C_DOWNSMASH_YOYO_NUDGE_FRAME;
    s32 x50_UNK4;
    s32 x54_UNK5;
    s32 x58_UNK6;
    s32 x5C_UNK7;
} itYoyoAttributes;

#endif
