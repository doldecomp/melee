#ifndef MELEE_FT_CHARA_FTMARIO_TYPES_H
#define MELEE_FT_CHARA_FTMARIO_TYPES_H

#include <common_structs.h>
#include <platform.h>

typedef struct ftMario_DatAttrs {
    // SIDE SPECIAL - CAPE / SUPER SHEET //

    /* 0x00 */ f32 vel_x_decay;
    /* 0x04 */ f32 x4_MARIO_CAPE_VEL_X;
    /* 0x08 */ f32 x8_MARIO_CAPE_VEL_Y;
    /* 0x0C */ f32 xC_MARIO_CAPE_GRAVITY;
    /* 0x10 */ f32 x10_MARIO_CAPE_TERMINAL_VELOCITY;
    /* 0x14 */ s32 x14_MARIO_CAPE_IT_KIND;

    // UP SPECIAL - SUPER JUMP PUNCH //

    /* 0x18 */ f32 x18_MARIO_SUPERJUMP_FREEFALL_MOBILITY;
    /* 0x1C */ f32 x1C_MARIO_SUPERJUMP_LANDING_LAG;
    /* 0x20 */ f32 x20_MARIO_SUPERJUMP_REVERSE_STICK_RANGE;
    /* 0x24 */ f32 x24_MARIO_SUPERJUMP_MOMENTUM_STICK_RANGE;
    /* 0x28 */ f32 x28_MARIO_SUPERJUMP_ANGLE_DIFF;
    /* 0x2C */ f32 x2C_MARIO_SUPERJUMP_VEL_X;
    /* 0x30 */ f32 x30_MARIO_SUPERJUMP_GRAVITY;
    /* 0x34 */ f32 x34_MARIO_SUPERJUMP_VEL_MUL;

    // DOWN SPECIAL - MARIO TORNADO / DR. TORNADO //

    /* 0x38 */ f32 x38_MARIO_TORNADO_GROUND_VEL_Y; // Vertical momentum from
                                                   // inital grounded B-tap
    /* 0x3C */ f32 x3C_MARIO_TORNADO_MOMENTUM_X_GROUND;
    /* 0x40 */ f32 x40_MARIO_TORNADO_MOMENTUM_X_AIR;
    /* 0x44 */ f32 x44_MARIO_TORNADO_MOMENTUM_X_MUL_GROUND;
    /* 0x48 */ f32 x48_MARIO_TORNADO_MOMENTUM_X_MUL_AIR;
    /* 0x4C */ f32 x4C_MARIO_TORNADO_FRICTION_END;
    /* 0x50 */ s32 x50_MARIO_TORNADO_UNK;
    /* 0x54 */ f32 x54_MARIO_TORNADO_TAP_Y_VEL_MAX;
    /* 0x58 */ f32 x58_MARIO_TORNADO_TAP_GRAVITY;
    /* 0x5C */ s32 x5C_MARIO_TORNADO_LANDING_LAG;

    // CAPE / SUPER SHEET REFLECTION //

    /* 0x60 */ ReflectDesc x60_MARIO_CAPE_REFLECTION;

} ftMario_DatAttrs;

typedef struct ftMario_SpecialLw_ECB {
    u8 x0_str_arr[3];
    u8 x3_balign;
    u32 x4;
    u32 x8;
    u32 xC;
    u32 x10;
    u32 x14;
} ftMario_SpecialLw_ECB;

#endif
