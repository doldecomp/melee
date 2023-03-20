#ifndef MELEE_FT_CHARA_FTMARIO_TYPES_H
#define MELEE_FT_CHARA_FTMARIO_TYPES_H

#include "it/forward.h"

#include <common_structs.h>
#include <platform.h>
#include <dolphin/mtx/types.h>

typedef struct ftMario_DatAttrs {
    struct ftMario_SpecialS_DatAttrs {
        f32 vel_x_decay;
        Vec2 vel;
        f32 grav;
        f32 terminal_vel;
        ItemKind cape_kind;
    } specials;

    struct ftMario_SpecialHi_DatAttrs {
        f32 freefall_mobility;
        f32 landing_lag;
        f32 reverse_stick_range;
        f32 momentum_stick_range;
        f32 angle_diff;
        f32 vel_x;
        f32 grav;
        f32 vel_mul;
    } specialhi;

    // DOWN SPECIAL - MARIO TORNADO / DR. TORNADO //

    /* 0x38 */ f32 speciallw_vel_y; // Vertical momentum from
                                    // inital grounded B-tap
    /* 0x3C */ f32 speciallw_momentum_x;
    /* 0x40 */ f32 specialairlw_momentum_x;
    /* 0x44 */ f32 speciallw_momentum_x_mul;
    /* 0x48 */ f32 specialairlw_momentum_x_mul;
    /* 0x4C */ f32 speciallw_friction_end;
    /* 0x50 */ s32 speciallw_unk0;
    /* 0x54 */ f32 speciallw_tap_y_vel_max;
    /* 0x58 */ f32 speciallw_tap_grav;
    /* 0x5C */ s32 speciallw_landing_lag;

    // CAPE / SUPER SHEET REFLECTION //

    /* 0x60 */ ReflectDesc specials_reflection;

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
