#ifndef MELEE_FT_CHARA_FTCAPTAIN_TYPES_H
#define MELEE_FT_CHARA_FTCAPTAIN_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCaptain/forward.h"

struct ftCaptain_FighterVars {
    /* 0x222C */ u32 during_specials_start;
    /* 0x2230 */ u32 during_specials;
    u8 _[FIGHTERVARS_SIZE - 8];
};

struct ftCaptain_DatAttrs {
    f32 specialn_stick_range_y_neg;
    f32 specialn_stick_range_y_pos;
    f32 specialn_angle_diff;
    f32 specialn_vel_x;
    f32 specialn_vel_mul;
    f32 specials_gr_vel_x;
    f32 specials_grav;
    f32 specials_terminal_vel;
    f32 specials_unk0;
    f32 specials_unk1;
    f32 specials_unk2;
    f32 specials_unk3;
    f32 specials_unk4;
    f32 specials_unk5;
    f32 specials_miss_landing_lag;
    f32 specials_hit_landing_lag;
    f32 specialhi_air_friction_mul;
    f32 specialhi_horz_vel;
    f32 specialhi_freefall_air_spd_mul;
    f32 specialhi_landing_lag;
    f32 specialhi_unk0;
    f32 specialhi_unk1;
    f32 specialhi_input_var;
    f32 specialhi_unk2;
    f32 specialhi_catch_grav;
    f32 specialhi_air_var;
    f32 x68;
    u32 speciallw_unk1;
    f32 speciallw_flame_particle_angle;
    f32 speciallw_on_hit_spd_modifier;
    u32 speciallw_unk2;
    f32 speciallw_ground_lag_mul;
    f32 speciallw_landing_lag_mul;
    f32 speciallw_ground_traction;
    f32 speciallw_air_landing_traction;
};

union ftCaptain_MotionVars {
    struct ftCaptainSpecialSVars {
        f32 grav;
    } specials;
};

#endif
