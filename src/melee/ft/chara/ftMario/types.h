#ifndef MELEE_FT_CHARA_FTMARIO_TYPES_H
#define MELEE_FT_CHARA_FTMARIO_TYPES_H

#include <platform.h>
#include "it/forward.h"
#include <baselib/forward.h>

#include <common_structs.h>
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

    struct ftMario_SpecialLw_DatAttrs {
        f32 vel_y;

        f32 momentum_x;
        f32 air_momentum_x;
        f32 momentum_x_mul;
        f32 air_momentum_x_mul;
        f32 friction_end;
        s32 unk0;
        f32 tap_y_vel_max;
        f32 tap_grav;
        s32 landing_lag;
    } speciallw;

    ReflectDesc cape_reflection;
} ftMario_DatAttrs;

struct ftMario_FighterVars {
    /// Current Megavitamin color combo
    /* 0x222C */ int x222C_vitaminCurr;
    /// Previous Megavitamin color combo
    /* 0x2230 */ int x2230_vitaminPrev;
    /* 0x2234 */ bool x2234_tornadoCharge;
    /* 0x2238 */ bool x2238_isCapeBoost;
    /* 0x223C */ HSD_GObj* x223C_capeGObj;
    /* 0x2240 */ uint x2240;
};

typedef struct ftMario_SpecialLw_ECB {
    u8 x0_str_arr[3];
    u8 x3_balign;
    uint x4;
    uint x8;
    uint xC;
    uint x10;
    uint x14;
} ftMario_SpecialLw_ECB;

#endif
