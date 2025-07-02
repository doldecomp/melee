#ifndef MELEE_FT_CHARA_FTKIRBY_TYPES_H
#define MELEE_FT_CHARA_FTKIRBY_TYPES_H

#include <placeholder.h>
#include <platform.h>

#include "ft/dobjlist.h"
#include "ftGameWatch/types.h"
#include "ftMars/types.h"
#include "ftNess/types.h"

#include "it/forward.h"
#include "lb/forward.h"

#include "lb/types.h"

#include <baselib/forward.h>

#include <common_structs.h>

struct ftKb_FighterVars {
    /* fp+222C */ struct ftKb_Hat {
        /*  +0   fp+222C */ UNK_T x0;
        /*  +4   fp+2230 */ s32 x4;
        /*  +8:0 fp+2234:0 */ u8 x8_b0 : 1;
        /*  +9   fp+2235 */ u8 x9[3];
        /*  +C   fp+2238 */ FighterKind kind;
        /* +10   fp+223C */ HSD_JObj* jobj;
        /* +14   fp+2240 */ DObjList x14;
        /* +1C   fp+2248 */ u32 x1C;
        /* +20   fp+224C */ UNK_T x20;
        /* +24   fp+2250 */ u32 x24;
    } hat;
    /* fp+224C   */ HSD_DObj** x28;
    /* fp+2250   */ u8 _2C[0x44 - 0x2C];
    /* fp+2270   */ struct KirbyFV_x44_t {
        int x0;
    } x44;
    /* fp+224C   */ u8 _48[0x60 - 0x48];
    /* fp+228C   */ UNK_T x60;
    /* fp+2290   */ bool x64;
    /* fp+2294   */ u8 _68[0x7C - 0x68];
    /* fp+22A8   */ Item_GObj* ns_flash_gobj;
    /* fp+2294   */ u8 x80[0x9C - 0x80];
    /* fp+22C8   */ int x9C;
    /* fp+22CC   */ UNK_T xA0;
    /* fp+22D0   */ UNK_T xA4;
    /* fp+22D4   */ int xA8;
    /* fp+22D8   */ UNK_T xAC;
    /* fp+22DC   */ UNK_T xB0;
    /* fp+22E0   */ int xB4;
    /* fp+22E4   */ UNK_T xB8;
    /* fp+22E8   */ int xBC;
    /* fp+22EC   */ UNK_T xC0;
    /* fp+22F0   */ bool xC4;
    /* fp+22F4   */ UNK_T xC8;
    /* fp+22F8   */ bool xCC;
    /* fp+22FC   */ Item_GObj* xD0;
    /* fp+2300   */ UNK_T xD4;
    /* fp+2304   */ UNK_T xD8;
    /* fp+2308   */ UNK_T xDC;
    /* fp+230C   */ int xE0;
    /* fp+2310   */ short xE4;
    /* fp+2314   */ float xE8;
    /* fp+2318   */ float xEC;
    /* fp+231C   */ float xF0;
    /* fp+2320:0 */ u8 xF4_b0 : 1;
};
STATIC_ASSERT(sizeof(struct ftKb_FighterVars) == FIGHTERVARS_SIZE);

struct ftKb_SpecialNMs_DatAttrs {
    /* da+35C */ u32 charge_iterations;
    /* da+360 */ u32 base_damage;
    /* da+364 */ u32 additional_damage_per_iteration;
    /* da+368 */ float air_horizontal_momentum_preservation;
    /* da+36C */ float air_horizontal_deceleration_rate;
};
STATIC_ASSERT(sizeof(struct ftKb_SpecialNMs_DatAttrs) == 0x14);

/// @todo Every hat is its own struct.
struct ftKb_DatAttrs {
    // Midair Jumps
    /*   +0 */ u32 jumpaerial_turn_duration;
    /*   +4 */ float jumpaerial_horizontal_momentum_backwards;
    /*   +8 */ float jumpaerial_horizontal_momentum_forwards;
    /*   +C */ float jumpaerial_momentum_from_turning;
    /*  +10 */ float jumpaerial_horizontal_momentum;
    /*  +14 */ float jumpaerial_jump1_vertical_momentum;
    /*  +18 */ float jumpaerial_jump2_vertical_momentum;
    /*  +1C */ float jumpaerial_jump3_vertical_momentum;
    /*  +20 */ float jumpaerial_jump4_vertical_momentum;
    /*  +24 */ float jumpaerial_jump5_vertical_momentum;
    /*  +28 */ u32 jumpaerial_number_of_jumps;
    /*  +2C */ u32 jumpaerial_first_jump_action_state;
    /*  +30 */ u32 jumpaerial_final_jump_action_state;
    /*  +34 */ s16 jumpaerial_unk;

    // Neutral B (no hat)
    /*  +38 */ float specialn_x_offset_inhaled;
    /*  +3C */ float specialn_y_offset_inhaled;
    /*  +40 */ float specialn_z_offset_inhaled;
    /*  +44 */ float specialn_gravity_of_inhaled;
    /*  +48 */ float specialn_velocity_outer_grab_box;
    /*  +4C */ float specialn_velocity_inner_grab_box;
    /*  +50 */ float specialn_inhale_velocity;
    /*  +54 */ float specialn_inhale_resistance;
    /*  +58 */ float specialn_duration_divisor;
    /*  +5C */ float specialn_base_duration;
    /*  +60 */ float specialn_star_deceleration_rate;
    /*  +64 */ float specialn_star_duration_divisor;
    /*  +68 */ float specialn_star_base_duration;
    /*  +6C */ float specialn_frames_in_swallow_star;
    /*  +70 */ float specialn_spit_spin;
    /*  +74 */ float specialn_x_axis_range_walk;
    /*  +78 */ float specialn_y_axis_range_jump;
    /*  +7C */ float specialn_walk_speed;
    /*  +80 */ float specialn_jump_height;
    /*  +84 */ float specialn_stop_momentum;
    /*  +88 */ float specialn_ground_spit_initial_horizontal_velocity;
    /*  +8C */ float specialn_spit_deceleration_rate;
    /*  +90 */ float specialn_spit_out_release_angle; // In radians
    /*  +94 */ float specialn_swallow_star_vertical_velocity;
    /*  +98 */ float specialn_swallow_star_gravity;
    /*  +9C */ float specialn_opponent_horizontal_velocity;
    /*  +A0 */ float specialn_opponent_vertical_velocity;
    /*  +A4 */ float specialn_ability_loss_star_x;
    /*  +A8 */ float specialn_ability_loss_star_y;
    /*  +AC */ float specialn_ability_loss_star_z;
    /*  +B0 */ float specialn_odds_lose_ability_on_hit;
    /*  +B4 */ float specialn_unk1;
    /*  +B8 */ float specialn_swallow_star_y_release;
    /*  +BC */ float specialn_unk2;
    /*  +C0 */ float specialn_unk3;
    /*  +C4 */ float specialn_unk4;
    /*  +C8 */ float specialn_unk5;

    // Side B
    /*  +CC */ float specials_aerial_vertical_momentum;
    /*  +D0 */ float specials_landing_lag;

    // Up B
    /*  +D4 */ float specialhi_vertical_momentum;
    /*  +D8 */ float specialhi_horizontal_momentum;
    /*  +DC */ float specialhi_projectile_spawn_x;
    /*  +E0 */ float specialhi_projectile_spawn_y;
    /*  +E4 */ float specialhi_reverse_upb_stick_range;
    /*  +E8 */ float specialhi_unk;

    // Down B
    /*  +EC */ u32 speciallw_max_time_in_stone;
    /*  +F0 */ u32 speciallw_min_time_in_stone;
    /*  +F4 */ float speciallw_min_slant_angle_slide;
    /*  +F8 */ float speciallw_max_slant_angle_slide;
    /*  +FC */ float speciallw_slide_acceleration;
    /* +100 */ float speciallw_slide_max_speed;
    /* +104 */ float speciallw_gravity;
    /* +108 */ s32 speciallw_hp;
    /* +10C */ u32 speciallw_resistance;
    /* +110 */ u32 speciallw_unk;
    /* +114 */ float speciallw_freefall_toggle;

    // Bowser
    // In frames, checked in this many frame intervals
    /* +118 */ u32 specialn_kp_b_button_check_frequency;
    /* +11C */ float specialn_kp_fuel_recharge_rate;
    /* +120 */ float specialn_kp_flame_size_recharge_rate;
    /* +124 */ float specialn_kp_max_fuel;
    /* +128 */ float specialn_kp_spew_flame_velocity;
    /* +12C */ float specialn_kp_flame_scale;
    /* +130 */ float specialn_kp_lowest_charge_graphic_size;
    /* +134 */ u32 specialn_kp_screen_shake_frequency;
    /* +138 */ float specialn_kp_breath_x_offset;
    // Values repeat below here
    /* +13C */ float specialn_kp_breath_y_offset;

    // Giga Bowser
    // In frames, checked in this many frame intervals
    /* +140 */ u32 specialn_gk_b_button_check_frequency;
    /* +144 */ float specialn_gk_fuel_recharge_rate;
    /* +148 */ float specialn_gk_flame_size_recharge_rate;
    /* +14C */ float specialn_gk_max_fuel;
    /* +150 */ float specialn_gk_spew_flame_velocity;
    /* +154 */ float specialn_gk_flame_scale;
    /* +158 */ float specialn_gk_lowest_charge_graphic_size;
    /* +15C */ u32 specialn_gk_screen_shake_frequency;
    /* +160 */ float specialn_gk_breath_x_offset;
    /* +164 */ float specialn_gk_breath_y_offset;

    // Samus
    /* +168 */ float specialn_ss_charge_time;
    /* +16C */ float specialn_ss_aerial_shot_recoil;
    /* +170 */ u32 specialn_ss_frames_per_charge_level;
    /* +174 */ float specialn_ss_freefall_toggle;

    // Peach
    /* +178 */ float specialn_pe_friction;
    /* +17C */ float specialn_pe_air_horizontal_momentum_preservation;
    /* +180 */ float specialn_pe_air_initial_vertical_momentum;
    /* +184 */ float specialn_pe_fall_acceleration;
    /* +188 */ float specialn_pe_unk2;
    /* +18C */ float specialn_pe_unk3;

    // Donkey Kong
    /* +190 */ int specialn_dk_swings_to_full_charge;
    /* +194 */ u32 specialn_dk_damage_increase_per_swing;
    /* +198 */ float specialn_dk_grounded_punch_horizontal_velocity;
    /* +19C */ float specialn_dk_freefall_toggle;

    // Ness
    /* +1A0 */ int specialn_ns_frames_to_loop_charge_ground;
    /* +1A4 */ int specialn_ns_frames_to_loop_charge_air;
    /* +1A8 */ int specialn_ns_falling_acceleration_delay;
    /* +1AC */ int specialn_ns_charge_release_delay;
    /* +1B0 */ float specialn_ns_unk1;
    /* +1B4 */ float specialn_ns_gravity;
    /* +1B8 */ float specialn_ns_unk2;
    /* +1BC */ float specialn_ns_freefall_toggle;

    // Pikachu
    /* +1C0 */ float specialn_pk_ground_spawn_offset_x;
    /* +1C4 */ float specialn_pk_ground_spawn_offset_y;
    /* +1C8 */ float specialn_pk_air_spawn_offset_x;
    /* +1CC */ float specialn_pk_air_spawn_offset_y;
    /* +1D0 */ float specialn_pk_freefall_toggle;
    /* +1D4 */ u32 specialn_pk_grounded_item_id;
    /* +1D8 */ u32 specialn_pk_air_item_id;

    // Pichu
    /* +1DC */ float specialn_pc_ground_spawn_offset_x;
    /* +1E0 */ float specialn_pc_ground_spawn_offset_y;
    /* +1E4 */ float specialn_pc_air_spawn_offset_x;
    /* +1E8 */ float specialn_pc_air_spawn_offset_y;
    /* +1EC */ float specialn_pc_freefall_toggle;
    /* +1F0 */ u32 specialn_pc_grounded_item_id;
    /* +1F4 */ u32 specialn_pc_air_item_id;

    // Captain Falcon
    /* +1F8 */ float specialn_ca_x_axis_range;
    /* +1FC */ float specialn_ca_y_axis_range;
    /* +200 */ float specialn_ca_angle_difference;
    /* +204 */ float specialn_ca_forward_momentum;
    /* +208 */ float specialn_ca_additional_vertical_momentum;

    // Ganondorf
    /* +20C */ float specialn_gn_x_axis_range;
    /* +210 */ float specialn_gn_y_axis_range;
    /* +214 */ float specialn_gn_angle_difference;
    /* +218 */ float specialn_gn_forward_momentum;
    /* +21C */ float specialn_gn_additional_vertical_momentum;

    // Fox
    /* +220 */ float specialn_fx_unk1;
    /* +224 */ float specialn_fx_unk2;
    /* +228 */ float specialn_fx_unk3;
    /* +22C */ float specialn_fx_unk4;
    /* +230 */ float specialn_fx_launch_angle;
    /* +234 */ float specialn_fx_launch_speed;
    /* +238 */ float specialn_fx_freefall_toggle;
    /* +23C */ u32 specialn_fx_blaster_projectile_id;
    /* +240 */ u32 specialn_fx_blaster_item_id;

    // Falco
    /* +244 */ float specialn_fc_unk1;
    /* +248 */ float specialn_fc_unk2;
    /* +24C */ float specialn_fc_unk3;
    /* +250 */ float specialn_fc_unk4;
    /* +254 */ float specialn_fc_launch_angle;
    /* +258 */ float specialn_fc_launch_speed;
    /* +25C */ float specialn_fc_freefall_toggle;
    /* +260 */ u32 specialn_fc_blaster_projectile_id;
    /* +264 */ u32 specialn_fc_blaster_item_id;

    // Link
    /// In frames
    /* +268 */ float specialn_lk_max_charge;
    /* +26C */ float specialn_lk_arrow_charge_speed;
    /* +270 */ float specialn_lk_freefall_toggle;
    /* +274 */ u32 specialn_lk_bow_item_loader_id;
    /* +278 */ u32 specialn_lk_bow_item_id;

    // Young Link
    // In frames
    /* +27C */ float specialn_cl_max_charge;
    /* +280 */ float specialn_cl_arrow_charge_speed;
    /* +284 */ float specialn_cl_freefall_toggle;
    /* +288 */ u32 specialn_cl_bow_item_loader_id;
    /* +28C */ u32 specialn_cl_bow_item_id;

    // Sheik
    /* +290 */ float specialn_sk_graphic_x_offset_ground;
    /* +294 */ float specialn_sk_graphic_y_offset_ground;
    /* +298 */ float specialn_sk_graphic_x_offset_air;
    /* +29C */ float specialn_sk_graphic_y_offset_air;
    /* +2A0 */ float specialn_sk_freefall_toggle;

    // Zelda
    /* +2A4 */ float specialn_zd_unk1;
    /* +2A8 */ u32 specialn_zd_frames_before_gravity;
    /* +2AC */ float specialn_zd_horizontal_momentum_preservation;
    /* +2B0 */ float specialn_zd_fall_acceleration;

    // Jigglypuff
    /* +2B4 */ u32 specialn_pr_duration;
    /* +2B8 */ u32 specialn_pr_unk;
    /* +2BC */ float specialn_pr_air_height_offset_at_start;
    /* +2C0 */ float specialn_pr_bounciness;
    /* +2C4 */ float specialn_pr_unk1;
    /* +2C8 */ float specialn_pr_gravity_during_roll;
    /* +2CC */ float specialn_pr_base_speed;
    /* +2D0 */ float specialn_pr_max_speed;
    /* +2D4 */ float specialn_pr_unk2;
    /* +2D8 */ float specialn_pr_air_x_axis_momentum;
    /* +2DC */ float specialn_pr_air_y_axis_momentum;
    /* +2E0 */ float specialn_pr_air_initial_momentum;
    /* +2E4 */ float specialn_pr_max_momentum;
    /* +2E8 */ float specialn_pr_spinning_speed;
    /* +2EC */ float specialn_pr_spinning_speed_turn;
    /* +2F0 */ u32 specialn_pr_delay_per_smoke;
    /* +2F4 */ float specialn_pr_unk3;
    /* +2F8 */ float specialn_pr_bounce1;
    /* +2FC */ float specialn_pr_bounce2;
    /* +300 */ float specialn_pr_base_damage;
    /* +304 */ float specialn_pr_damage_multiplier;
    /* +308 */ float specialn_pr_horizontal_bounce_momentum_on_hit;
    /* +30C */ float specialn_pr_vertical_bounce_momentum_on_hit;
    /* +310 */ float specialn_pr_forward_momentum_from_stick;
    /* +314 */ float specialn_pr_unk4;
    /* +318 */ float specialn_pr_unk5;
    /* +31C */ u32 specialn_pr_unk6;
    /* +320 */ float specialn_pr_charge_rate1;
    /* +324 */ float specialn_pr_charge_time;
    /* +328 */ float specialn_pr_charge_rate2;
    /* +32C */ float specialn_pr_charge_spin_animation;
    /* +330 */ float specialn_pr_unk7;
    /* +334 */ float specialn_pr_unk8;
    /* +338 */ float specialn_pr_some_speed_var;
    /* +33C */ float specialn_pr_spin_anim_speed_after_collision;
    /* +340 */ float specialn_pr_air_speed;
    /* +344 */ float specialn_pr_turn_rate_related;
    /* +348 */ float specialn_pr_unk9;
    /* +34C */ float specialn_pr_unk10;
    /* +350 */ float specialn_pr_unk11;
    /* +354 */ float specialn_pr_unk12;
    /* +358 */ float specialn_pr_freefall_toggle;

    struct ftKb_SpecialNMs_DatAttrs ms, fe;

    // Mewtwo
    /* +384 */ float specialn_mt_charge_time;
    /* +388 */ float specialn_mt_ground_horizontal_momentum;
    /* +38C */ float specialn_mt_air_horizontal_momentum;
    /* +390 */ u32 specialn_mt_loops_to_full_charge;
    /* +394 */ float specialn_mt_frames_to_transition;
    /* +398 */ float specialn_mt_freefall_toggle;

    // Ice Climbers
    /* +39C */ float specialn_pp_air_vertical_momentum;
    /* +3A0 */ float specialn_pp_landing_lag;
    /* +3A4 */ float specialn_pp_x_spawn;
    /* +3A8 */ float specialn_pp_y_spawn;

    // Yoshi
    /* +3AC */ float specialn_ys_initial_horizontal_momentum;
    /* +3B0 */ float specialn_ys_initial_vertical_momentum;
    /* +3B4 */ float specialn_ys_damage_multiplier;
    /* +3B8 */ float specialn_ys_unk;
    /* +3BC */ float specialn_ys_growth_time;
    /* +3C0 */ float specialn_ys_base_duration;
    /* +3C4 */ float specialn_ys_egg_breakout_resistance;
    /* +3C8 */ float specialn_ys_frames_reduced_per_input;
    /* +3CC */ float specialn_ys_unk1;
    /* +3D0 */ float specialn_ys_unk2;
    /* +3D4 */ u32 specialn_ys_iframes_on_release;
    /* +3D8 */ float specialn_ys_horizontal_velocity_on_breakout;
    /* +3DC */ float specialn_ys_vertical_velocity_on_breakout;
    /* +3E0 */ float specialn_ys_unk3;

    // Mr. Game & Watch
    /* +3E4 */ float specialn_gw_frame_on_repeat;
    /* +3E8 */ float specialn_gw_max_sausages_per_use;

    /* +3EC */ AbsorbDesc specialn_pe_absorbdesc;
    /* +400 */ ReflectDesc specialn_zd_reflectdesc;
};
STATIC_ASSERT(sizeof(struct ftKb_DatAttrs) == 0x424);

union ftKb_MotionVars {
    struct ftGameWatch_SpecialNVars specialn_gw;
    struct ftMars_SpecialNVars specialn_ms;
    struct ftNess_SpecialNVars specialn_ns;
    struct ftKb_SpecialNPe_Vars {
        /* fp+2340 */ int facing_dir;
    } specialn_pe;
    struct ftKb_SpecialHiVars {
        /* fp+2340 */ int x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ int x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ int x10;
        /* fp+2354 */ int x14;
        /* fp+2358 */ Vec3 x18;
        char pad1[0x60];
        /* fp+23C4 */ float xC4;
    } specialhi;
};

#endif
