#ifndef MELEE_FT_CHARA_FTCAPTAIN_TYPES_H
#define MELEE_FT_CHARA_FTCAPTAIN_TYPES_H

#include <platform.h>

#include "ft/forward.h"
#include "ftCaptain/forward.h" // IWYU pragma: export

#include <dolphin/mtx.h>

struct ftCaptain_FighterVars {
    /* 0x222C */ u32 during_specials_start;
    /* 0x2230 */ u32 during_specials;
    u8 _[FIGHTERVARS_SIZE - 8];
};

struct ftCaptain_DatAttrs {
    /* +0 */ float specialn_stick_range_y_neg;
    /* +4 */ float specialn_stick_range_y_pos;
    /* +8 */ float specialn_angle_diff;
    /* +C */ float specialn_vel_x;
    /* +10 */ float specialn_vel_mul;
    /* +14 */ float specials_gr_vel_x;
    /* +18 */ float specials_grav;
    /* +1C */ float specials_terminal_vel;
    /* +20 */ float specials_unk0;
    /* +24 */ float specials_unk1;
    /* +28 */ float specials_unk2;
    /* +2C */ float specials_unk3;
    /* +30 */ float specials_unk4;
    /* +34 */ float specials_unk5;
    /* +38 */ float specials_miss_landing_lag;
    /* +3C */ float specials_hit_landing_lag;
    /* +40 */ float specialhi_air_friction_mul;
    /* +44 */ float specialhi_horz_vel;
    /* +48 */ float specialhi_freefall_air_spd_mul;
    /* +4C */ float specialhi_landing_lag;
    /* +50 */ float specialhi_unk0;
    /* +54 */ float specialhi_unk1;
    /* +58 */ float specialhi_input_var;
    /* +5C */ float specialhi_unk2;
    /* +60 */ float specialhi_catch_grav;
    /* +64 */ s32 specialhi_air_var;
    /* +68 */ float x68;
    /* +6C */ u32 speciallw_unk1;
    /* +70 */ float speciallw_flame_particle_angle;
    /* +74 */ float speciallw_on_hit_spd_modifier;
    /* +78 */ s32 speciallw_unk2;
    /* +7C */ float speciallw_ground_lag_mul;
    /* +80 */ float speciallw_landing_lag_mul;
    /* +84 */ float speciallw_ground_traction;
    /* +88 */ float speciallw_air_landing_traction;
};

union ftCaptain_MotionVars {
    struct ftCaptainSpecialSVars {
        /* fp+2340 */ float grav;
    } specials;
    struct ftCaptainSpecialHiVars {
        /* fp+2340 */ u16 x0;
        /* fp+2342:0 */ u8 x2_b0 : 1;
        /* fp+2342:1 */ u8 x2_b1 : 1;
        /* fp+2342:2 */ u8 x2_b2 : 1;
        /* fp+2342:3 */ u8 x2_b3 : 1;
        /* fp+2342:4 */ u8 x2_b4 : 1;
        /* fp+2342:5 */ u8 x2_b5 : 1;
        /* fp+2342:6 */ u8 x2_b6 : 1;
        /* fp+2342:7 */ u8 x2_b7 : 1;
        /* fp+2343 */ u8 x3;
        /* fp+2344 */ Vec2 vel;
    } specialhi;
    struct ftCaptainSpecialLwVars {
        /* fp+2340 */ u16 x0;
        /* fp+2342 */ u16 x2;
        /* fp+2344 */ float friction;
    } speciallw;
};

#endif
