#ifndef MELEE_FT_CHARA_FTMARIO_TYPES_H
#define MELEE_FT_CHARA_FTMARIO_TYPES_H

#include <platform.h>

#include "forward.h" // IWYU pragma: export
#include "ft/forward.h"
#include "ftMario/forward.h" // IWYU pragma: export
#include "it/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "lb/types.h"

#include <common_structs.h>

struct ftMario_FighterVars {
    /// Current Megavitamin color combo
    /* 0x222C */ int x222C_vitaminCurr;
    /// Previous Megavitamin color combo
    /* 0x2230 */ int x2230_vitaminPrev;
    /* 0x2234 */ bool x2234_tornadoCharge;
    /* 0x2238 */ bool x2238_isCapeBoost;
    /* 0x223C */ HSD_GObj* x223C_capeGObj;
    /* 0x2240 */ uint x2240;
    u8 _[FIGHTERVARS_SIZE - 0x18];
};

typedef struct ftMario_DatAttrs {
    struct ftMario_SpecialS_DatAttrs {
        float vel_x_decay;
        Vec2 vel;
        float grav;
        float terminal_vel;
        ItemKind cape_kind;
    } specials;

    struct ftMario_SpecialHi_DatAttrs {
        float freefall_mobility;
        float landing_lag;
        float reverse_stick_range;
        float momentum_stick_range;
        float angle_diff;
        float vel_x;
        float grav;
        float vel_mul;
    } specialhi;

    struct ftMario_SpecialLw_DatAttrs {
        float vel_y;
        float momentum_x;
        float air_momentum_x;
        float momentum_x_mul;
        float air_momentum_x_mul;
        float friction_end;
        s32 unk0;
        float tap_y_vel_max;
        float tap_grav;
        s32 landing_lag;
    } speciallw;

    ReflectDesc cape_reflection;
} ftMario_DatAttrs;

typedef struct ftMario_SpecialLw_ECB {
    u8 x0_str_arr[3];
    u8 x3_balign;
    uint x4;
    uint x8;
    uint xC;
    uint x10;
    uint x14;
} ftMario_SpecialLw_ECB;

typedef struct ftMarioSpecialS {
    /// 0x2340 - bool to check if reflect bubble should be enabled
    bool reflecting;
} ftMarioSpecialS;

typedef struct ftMarioSpecialLw {
    /// 0x2340 - Grounded momentum of Mario / Dr. Tornado
    float groundVelX;
    /// 0x2344 - Set but never used?
    s32 unk;
    /// 0x2348 - Skipped entirely
    s32 _;
    /// 0x234C - Checked in collision, related to some angle calculation
    bool isUnkColl;
} ftMarioSpecialLw;

typedef union ftMario_MotionVars {
    ftMarioSpecialS SpecialS;
    ftMarioSpecialLw SpecialLw;
} ftMario_MotionVars;

#endif
