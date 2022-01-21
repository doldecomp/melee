#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/math.h>
#include <math.h>

#include "sysdolphin/baselib/gobj.h"

typedef struct _Vec2 { float x, y;    } Vec2;
typedef struct _Vec3 { float x, y, z; } Vec3;

typedef struct _CollData
{
    HSD_GObj *gobj;            // 0x0
    Vec3 topN_Curr;            // 0x4
    Vec3 topN_CurrCorrect;     // 0x10
    Vec3 topN_Prev;            // 0x1c
    Vec3 topN_Proj;            // 0x28
    int flags1;                // 0x34
    int coll_test;             // 0x38, is the ID of the most recent collision test for this object
    int ignore_line;           // 0x3c, ignores this line ID during collision
    int ledge_left;            // 0x40, ledge ID in contact with
    int ledge_right;           // 0x44, ledge ID in contact with
    int ignore_group;          // 0x48  ignores this line group during collision
    int check_group;           // 0x4c  checks only this line group during collision
    int x50;                   // 0x50
    int x54;                   // 0x54
    int x58;                   // 0x58
    int x5c;                   // 0x5c
    int x60;                   // 0x60
    int x64;                   // 0x64
    int x68;                   // 0x68
    int x6c;                   // 0x6c
    int x70;                   // 0x70
    int x74;                   // 0x74
    int x78;                   // 0x78
    int x7c;                   // 0x7c
    int x80;                   // 0x80
    Vec2 ecbCurr_top;          // 0x84
    Vec2 ecbCurr_bot;          // 0x8C
    Vec2 ecbCurr_right;        // 0x94
    Vec2 ecbCurr_left;         // 0x9C
    Vec2 ecbCurrCorrect_top;   // 0xA4
    Vec2 ecbCurrCorrect_bot;   // 0xAC
    Vec2 ecbCurrCorrect_right; // 0xB4
    Vec2 ecbCurrCorrect_left;  // 0xBC
    Vec2 ecbPrev_top;          // 0xC4
    Vec2 ecbPrev_bot;          // 0xCC
    Vec2 ecbPrev_right;        // 0xD4
    Vec2 ecbPrev_left;         // 0xDC
    Vec2 ecbProj_top;          // 0xE4
    Vec2 ecbProj_bot;          // 0xEC
    Vec2 ecbProj_right;        // 0xF4
    Vec2 ecbProj_left;         // 0xFC
    int x104;                  // 0x104
    void *joint_1;             // 0x108
    void *joint_2;             // 0x10c
    void *joint_3;             // 0x110
    void *joint_4;             // 0x114
    void *joint_5;             // 0x118
    void *joint_6;             // 0x11c
    void *joint_7;             // 0x120
    int x124;                  // 0x124
    int x128;                  // 0x128
    int x12c;                  // 0x12c
    int flags;                 // 0x130
    int envFlags;              // 0x134
    int envFlags_prev;         // 0x138
    int x13c;                  // 0x13c
    int x140;                  // 0x140
    int x144;                  // 0x144
    int x148;                  // 0x148
    int x83c_ground_index;          // 0x14c, ground
    u8 ground_info;            // 0x150
    u8 ground_unk;             // 0x151
    u8 ground_type;            // 0x152, platform/ledgegrab
    u8 ground_mat;             // 0x153, grass/ice etc
    Vec3 ground_normal;         // 0x154, points out of the ground surface
    int rightwall_index;       // 0x160
    u8 rightwall_info;         // 0x164
    u8 rightwall_unk;          // 0x165
    u8 rightwall_type;         // 0x166, platform/ledgegrab
    u8 rightwall_mat;          // 0x167, grass/ice etc
    Vec3 rightwall_slope;      // 0x168
    int leftwall_index;        // 0x174
    u8 leftwall_info;          // 0x178
    u8 leftwall_unk;           // 0x179
    u8 leftwall_type;          // 0x17A, platform/ledgegrab
    u8 leftwall_mat;           // 0x17B, grass/ice etc
    Vec3 leftwall_slope;       // 0x17C
    int ceil_index;            // 0x188
    u8 ceil_info;              // 0x18C
    u8 ceil_unk;               // 0x18D
    u8 ceil_type;              // 0x18E, platform/ledgegrab
    u8 ceil_mat;               // 0x18F, grass/ice etc
    Vec3 ceil_slope;           // 0x190
    int ecb_lock;              // 0x19c
} CollData;

typedef struct _Fighter
{
	u8 filler_0x74[0x74];
	// physics struct
	Vec3 x74_anim_vel;
	Vec3 x80_self_vel;
	Vec3 x8c_kb_vel;
	Vec3 x98_atk_shield_kb;
	Vec3 xa4_unk_vel;
	Vec3 xb0_position;
	Vec3 xbc_pos_prev;
	Vec3 xc8_pos_delta;
	Vec3 xd4_unk_vel;
	s32  xe0_airborne;
	float xe4_ground_accel_1;
	float xe8_ground_accel_2;
	float xec_ground_vel;
	float xf0_ground_kb_vel;
	float xf4_ground_attacker_shield_kb_vel;
	Vec2 xf8_player_nudge_vel;
	float x100_unk;
	// end physics struct

    struct attr
    {
        float x110_walk_initial_velocity;
        float x114_walk_acceleration;
        float x118_walk_maximum_velocity;
        float x11c_slow_walk_max;
        float x120_mid_walk_point;
        float x124_fast_walk_min;
        float x128_ground_friction; // used
        float x12c_dash_initial_velocity;
        float x130_dashrun_acceleration_a;
        float x134_dashrun_acceleration_b;
        float x138_dashrun_terminal_velocity;
        float x13c_run_animation_scaling;
        float x140_max_runbrake_frames;
        float x144_grounded_max_horizontal_velocity;
        float x148_jump_startup_time;
        float x14c_jump_h_initial_velocity;
        float x150_jump_v_initial_velocity;
        float x154_ground_to_air_jump_momentum_multiplier;
        float x158_jump_h_max_velocity;
        float x15c_hop_v_initial_velocity;
        float x160_air_jump_v_multiplier;
        float x164_air_jump_h_multiplier;
        int   x168_max_jumps;
        float x16c_gravity;
        float x170_terminal_velocity;
        float x174_aerialDriftStickMult;
        float x178_aerialDriftBase;
        float x17c_aerialDriftMax;
        float x180_aerialFriction;
        float x184_fastfall_velocity;
        float x188_horizontal_air_mobility_constant;
        int   x18c_jab_2_input_window;
        int   x190_jab_3_input_window;
        int   x194_frames_to_change_direction_on_standing_turn;
        float x198_weight;
        float x19c_model_scaling;
        float x1a0_initial_shield_size;
        float x1a4_shield_break_initial_velocity;
        int   x1a8_rapid_jab_window;
        int   x1ac_unk;
        int   x1b0_unk;
        int   x1b4_unk;
        float x1b8_ledge_jump_horizontal_velocity;
        float x1bc_ledge_jump_vertical_velocity;
        float x1c0_item_throw_velocity_multiplier;
        int   x1c4_unk;
        int   x1c8_unk;
        int   x1cc_unk;
        int   x1d0_unk;
        int   x1d4_unk;
        int   x1d8_unk;
        int   x1dc_unk;
        int   x1e0_unk;
        int   x1e4_unk;
        int   x1e8_unk;
        int   x1ec_unk;
        float x1f0_kirby_b_star_damage;
        float x1f4_normal_landing_lag;
        float x1f8_n_air_landing_lag;
        float x1fc_f_air_landing_lag;
        float x200_b_air_landing_lag;
        float x204_u_air_landing_lag;
        float x208_d_air_landing_lag;
        float x20c_nametag_height;
        int   x210_unk;
        float x214_wall_jump_horizontal_velocity;
        float x218_wall_jump_vertical_velocity;
        int   x21c_unknown21C;
        float x220_trophy_scale;
        int   x224_unk;
        int   x228_unk;
        int   x22c_unk;
        int   x230_unk;
        int   x234_unk;
        int   x238_unk;
        int   x23c_unk;
        int   x240_unk;
        int   x244_unk;
        int   x248_unk;
        int   x24c_unk;
        int   x250_unk;
        int   x254_unk;
        int   x258_unk;
        float x25c_bubble_ratio;
        int   x260_unk;
        int   x264_unk;
        int   x268_unk;
        int   x26c_unk;
        float x270_respawn_platform_scale;
        int   x274_unk;
        int   x278_unk;
        int   x27c_camera_zoom_target_bone;
        int   x280_unk;
        int   x284_unk;
        int   x288_unk;
        int   x28c_special_jump_action___1;
        int   x290_weight_dependent_throw_speed_flags;
    } attr;

	u8 x594_anim_curr_flags_1; // used

	CollData coll_data; // 0x6F0 -> 0x88C

	// damage struct
	int x182c_behavior;
	float x1830_percent;
	int x1834;
	float x1838_percent_temp;
	float x183c_applied;
	int x1840;
	float x1844_direction;
	int x1848_kb_angle;
	int x184c_damaged_hurtbox;
	float x1850_force_applied;
	Vec3 x1854_collpos;
	int x1860_dealt;
	int x1864;
	HSD_GObj *x1868_source;
	int x186c;
	int x1870;
	int x1874;
	int x1878;
	int x187c;
	int x1880;
	int x1884;
	int x1888;
	int x188c;
	int x1890;
	int x1894;
	int x1898;
	int x189c;
	int x18a0;
	float x18A4_knockbackMagnitude; // used
	int x18a8;
	int x18ac_time_since_hit;
	int x18b0;
	float x18b4_armor;
	int x18b8;
	int x18bc;
	int x18c0;
	int x18c4_source_ply;
	int x18c8;
	int x18cc;
	int x18d0;
	int x18d4;
	int x18d8;
	int x18dc;
	int x18e0;
	int x18e4;
	int x18e8;
	u16 x18ec_instancehitby; // Last Move Instance This Player Was Hit by
	int x18f0;
	int x18f4;
	u8 x18f8;
	u8 x18f9;
	u16 x18f8_model_shift_frames;
	u8 x18fc;
	u8 x18fd;
	int x1900;
	int x1904;
	int x1908;
	int x190c;
	int x1910;
	int x1914;
	int x1918;
	int x191c;
	int x1920;
	int x1924;
	int x1928;
	int x192c;
	int x1930;
	int x1934;
	int x1938;
	int x193c;
	int x1940;
	int x1944;
	int x1948; // used
	int x194C; // used
	int x1950;
	int x1954;
	int x1958;
	float x195c_hitlag_frames;
	// end damage struct

	// callback struct
	void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter);
	void (*x2194_callback_x2194)(HSD_GObj *fighter);
	void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj *fighter);
	void (*x219c_callback_IASA)(HSD_GObj *fighter);
	void (*x21a0_callback_Anim)(HSD_GObj *fighter);
	void (*x21a4_callback_Phys)(HSD_GObj *fighter); // used
	void (*x21a8_callback_Coll)(HSD_GObj *fighter);
	void (*x21ac_callback_Cam)(HSD_GObj *fighter);
	void (*x21b0_callback_Accessory1)(HSD_GObj *fighter);
	void (*x21b4_callback_Accessory2)(HSD_GObj *fighter);
	void (*x21b8_callback_Accessory3)(HSD_GObj *fighter);
	void (*x21bc_callback_Accessory4)(HSD_GObj *fighter);
	void (*x21c0_callback_OnGiveDamage)(HSD_GObj *fighter);
	void (*x21c4_callback_OnShieldHit)(HSD_GObj *fighter);
	void (*x21c8_callback_OnReflectHit)(HSD_GObj *fighter);
	void (*x21cc_callback_x21cc)(HSD_GObj *fighter);
	void (*x21d0_callback_EveryHitlag)(HSD_GObj *fighter); // used
	void (*x21d4_callback_EnterHitlag)(HSD_GObj *fighter);
	void (*x21d8_callback_ExitHitlag)(HSD_GObj *fighter);
	void (*x21dc_callback_OnTakeDamage)(HSD_GObj *fighter);
	void (*x21e0_callback_OnDeath)(HSD_GObj *fighter);
	void (*x21e4_callback_OnDeath2)(HSD_GObj *fighter); // internally Dead_Proc as evidenced by 800f5430
	void (*x21e8_callback_OnDeath3)(HSD_GObj *fighter);
	void (*x21ec_callback_OnActionStateChange)(HSD_GObj *fighter);
	void (*x21f0_callback_OnTakeDamage2)(HSD_GObj *fighter);
	void (*x21f4_callback_OnHurtboxDetect)(HSD_GObj *fighter);
	void (*x21f8_callback_OnSpin)(HSD_GObj *fighter);
	// end callback struct

	s32 x2064_ledge_cooldown;
	s32 x2108;
	u8 filler1[0x2210];
	// flags struct:
	u8 x2210_1 : 1;
	u8 x2210_2 : 1;
	u8 x2210_3_throw : 1;
	u8 x2210_4_throw_release : 1; // also used to change users direction during aerial attacks
	u8 x2210_5_throw_turn : 1;
	u8 x2210_6_throw : 1;
	u8 x2210_7 : 1;
	u8 x2210_8 : 1;

	float throw_timerval;                    // equal to script_event_timer of the attacker

	u8 x2218_1 : 1;
	u8 x2218_2 : 1;
	u8 x2218_3 : 1;
	u8 x2218_4 : 1;
	u8 x2218_5 : 1;
	u8 x2218_6 : 1;
	u8 x2218_7 : 1;
	u8 x2218_8 : 1;

	u8 x2219_1 : 1;
	u8 x2219_2 : 1;
	u8 x2219_3 : 1;
	u8 x2219_4 : 1;
	u8 x2219_5 : 1;
	u8 x2219_6_freeze : 1;
	u8 x2219_7 : 1;
	u8 x2219_8 : 1;

	u8 x221a_1 : 1;
	u8 x221a_2 : 1;
	u8 x221a_3 : 1; // hitlag
	u8 x221a_4 : 1;
	u8 x221a_5 : 1; // fastfall
	u8 x221a_6 : 1; // no_hurt_script
	u8 x221a_7 : 1;
	u8 x221a_8 : 1; // gfx_persist

	u8 x221b_1 : 1; // shield enable
	u8 x221b_2 : 1;
	u8 x221b_3 : 1;
	u8 x221b_4 : 1;
	u8 x221b_5 : 1;
	u8 x221b_6 : 1;
	u8 x221b_7 : 1;
	u8 x221b_8 : 1;

	u8 x221c_1 : 1;
	u8 x221c_2 : 1;
	u8 x221c_3 : 1;
	u8 x221c_4 : 1;
	u8 x221c_5 : 1;
	u8 x221c_6 : 1;
	u8 x221c_7_hitstun : 1; // used
	u8 x221c_8 : 1;

	u8 x221d_1 : 1;
	u8 x221d_2 : 1;
	u8 x221d_3 : 1;
	u8 x221d_4 : 1; // input enable
	u8 x221d_5 : 1;
	u8 x221d_6 : 1; // nudge disable
	u8 x221d_7 : 1; // ground ignore
	u8 x221d_8 : 1;

	u8 x221e_1 : 1; // invisible
	u8 x221e_2 : 1;
	u8 x221e_3 : 1;
	u8 x221e_4 : 1; // is item visible
	u8 x221e_5 : 1;
	u8 x221e_6 : 1;
	u8 x221e_7 : 1;
	u8 x221e_8 : 1;

	u8 x221f_1 : 1; // is offscreen
	u8 x221f_2 : 1; // dead
	u8 x221f_3 : 1;
	u8 x221f_4_sleep : 1;
	u8 x221f_5 : 1; // slave
	u8 x221f_6 : 1;
	u8 x221f_7 : 1;
	u8 x221f_8 : 1;
	u8 x2220_unk_flags;
	u8 x2221_unk_flags;
	u8 x2222_1 : 1;
	u8 x2222_2 : 1;
	u8 x2222_3 : 1;
	u8 x2222_4 : 1;
	u8 x2222_5 : 1;
	u8 x2222_6 : 1;
	u8 x2222_7 : 1;
	u8 x2222_8 : 1;
	u8 x2223_unk_flags;
	u8 x2224_unk_flags;
	u8 x2225_1 : 1;
	u8 x2225_2 : 1;
	u8 x2225_3 : 1;
	u8 x2225_4 : 1;
	u8 x2225_5 : 1;
	u8 x2225_6 : 1;
	u8 x2225_7 : 1;
	u8 x2225_8 : 1;
	u8 x2226_unk_flags;
	u8 x2227_unk_flags;
	u8 x2228_unk_flags;
	u8 x2229_unk_flags;
	u8 x222a_1 : 1;
	u8 x222a_2 : 1;
	u8 x222a_3 : 1;
	u8 x222a_4 : 1;
	u8 x222a_5 : 1;
	u8 x222a_6 : 1;
	u8 x222a_7 : 1;
	u8 x222a_8 : 1;
	u8 x222b_unk_flags;
    // fighter_var struct:
    u32 x222C;
    u32 x2230;
    u32 x2234;
    u32 x2238;
    u32 x223C;
    u32 x2240;
} Fighter;

typedef struct ftCommonData
{
    float x0;                     // 0x0
    float x4;                     // 0x4
    float x8;                     // 0x8
    float xc;                     // 0xc
    float x10;                    // 0x10
    float x14;                    // 0x14
    float x18;                    // 0x18
    float x1c;                    // 0x1c
    float lstick_tilt;            // 0x20
    float x24;                    // 0x24
    float x28;                    // 0x28
    float x2c;                    // 0x2c
    float x30;                    // 0x30
    float x34;                    // 0x34
    float x38;                    // 0x38
    float x3c;                    // 0x3c
    float x40;                    // 0x40
    float x44;                    // 0x44
    float x48;                    // 0x48
    float x4c;                    // 0x4c
    float x50;                    // 0x50
    float x54;                    // 0x54
    float x58;                    // 0x58
    float x5c;                    // 0x5c
    float x60;                    // 0x60
    float x64;                    // 0x64
    float x68;                    // 0x68
    float friction_mult;          // 0x6c
    float jumpaerial_lsticky;     // 0x70
    float jumpaerial_lsticktimer; // 0x74
    float x78;                    // 0x78
    float x7c;                    // 0x7c
    float x80;                    // 0x80
    float x84;                    // 0x84
    float x88;                    // 0x88
    float x8c;                    // 0x8c
    float lstick_rebirthfall;     // 0x90
    float x94;                    // 0x94
    float x98;                    // 0x98
    float x9c;                    // 0x9c
    float xa0;                    // 0xa0
    float xa4;                    // 0xa4
    float xa8;                    // 0xa8
    float xac;                    // 0xac
    float xb0;                    // 0xb0
    float xb4;                    // 0xb4
    float xb8;                    // 0xb8
    float xbc;                    // 0xbc
    float xc0;                    // 0xc0
    float xc4;                    // 0xc4
    float xc8;                    // 0xc8
    float xcc;                    // 0xcc
    float xd0;                    // 0xd0
    float xd4;                    // 0xd4
    float xd8;                    // 0xd8
    float xdc;                    // 0xdc
    float xe0;                    // 0xe0
    float xe4;                    // 0xe4
    float xe8;                    // 0xe8
    float xec;                    // 0xec
    float xf0;                    // 0xf0
    float xf4;                    // 0xf4
    float xf8;                    // 0xf8
    float xfc;                    // 0xfc
    float kb_mult;                // 0x100
    float x104;                   // 0x104
    float x108;                   // 0x108
    float x10c;                   // 0x10c
    float x110;                   // 0x110
    float x114;                   // 0x114
    float x118;                   // 0x118
    float x11c;                   // 0x11c
    float x120;                   // 0x120
    float x124;                   // 0x124
    float x128;                   // 0x128
    float x12c;                   // 0x12c
    float x130;                   // 0x130
    float x134;                   // 0x134
    float x138;                   // 0x138
    float x13c;                   // 0x13c
    float x140;                   // 0x140
    float x144;                   // 0x144
    float x148;                   // 0x148
    float x14c;                   // 0x14c
    float x150;                   // 0x150
    float x154;                   // 0x154
    float x158;                   // 0x158
    float x15c;                   // 0x15c
    float x160;                   // 0x160
    float x164;                   // 0x164
    float x168;                   // 0x168
    float kb_maxVelX;             // 0x16c
    float x170;                   // 0x170
    float x174;                   // 0x174
    float x178;                   // 0x178
    float x17c;                   // 0x17c
    float x180;                   // 0x180
    float x184;                   // 0x184
    float x188;                   // 0x188
    float x18c;                   // 0x18c
    float x190;                   // 0x190
    float x194;                   // 0x194
    float x198;                   // 0x198
    float x19c;                   // 0x19c
    float x1a0;                   // 0x1a0
    float x1a4;                   // 0x1a4
    float tdi_maxAngle;           // 0x1a8
    float x1ac;                   // 0x1ac
    float x1b0;                   // 0x1b0
    float x1b4;                   // 0x1b4
    float x1b8;                   // 0x1b8
    float kb_bounceDecay;         // 0x1bc
    float x1c0;                   // 0x1c0
    float x1c4;                   // 0x1c4
    float x1c8;                   // 0x1c8
    float x1cc;                   // 0x1cc
    float x1d0;                   // 0x1d0
    float x1d4;                   // 0x1d4
    float x1d8;                   // 0x1d8
    float x1dc;                   // 0x1dc
    float x1e0;                   // 0x1e0
    float x1e4;                   // 0x1e4
    float x1e8;                   // 0x1e8
    float x1ec;                   // 0x1ec
    float x1f0;                   // 0x1f0
    float x1f4;                   // 0x1f4
    float x1f8;                   // 0x1f8
    float x1fc;                   // 0x1fc
    float x200;                   // 0x200
    float kb_frameDecay;          // 0x204
    float x208;                   // 0x208
    float x20c;                   // 0x20c
    float x210;                   // 0x210
    float x214;                   // 0x214
    float x218;                   // 0x218
    float x21c;                   // 0x21c
    float x220;                   // 0x220
    float x224;                   // 0x224
    float x228;                   // 0x228
    float x22c;                   // 0x22c
    float x230;                   // 0x230
    float x234;                   // 0x234
    float x238;                   // 0x238
    float x23c;                   // 0x23c
    float x240;                   // 0x240
    float x244;                   // 0x244
    float x248;                   // 0x248
    float x24c;                   // 0x24c
    float x250;                   // 0x250
    float x254;                   // 0x254
    float x258;                   // 0x258
    float x25c;                   // 0x25c
    float x260;                   // 0x260
    float x264;                   // 0x264
    float x268;                   // 0x268
    float x26c;                   // 0x26c
    float x270;                   // 0x270
    float x274;                   // 0x274
    float x278;                   // 0x278
    float x27c;                   // 0x27c
    float x280;                   // 0x280
    float x284;                   // 0x284
    float x288;                   // 0x288
    float x28c;                   // 0x28c
    float x290;                   // 0x290
    float x294;                   // 0x294
    float x298;                   // 0x298
    float x29c;                   // 0x29c
    float x2a0;                   // 0x2a0
    float x2a4;                   // 0x2a4
    float x2a8;                   // 0x2a8
    float x2ac;                   // 0x2ac
    float x2b0;                   // 0x2b0
    float x2b4;                   // 0x2b4
    float x2b8;                   // 0x2b8
    float x2bc;                   // 0x2bc
    float x2c0;                   // 0x2c0
    float x2c4;                   // 0x2c4
    float x2c8;                   // 0x2c8
    float x2cc;                   // 0x2cc
    float x2d0;                   // 0x2d0
    float x2d4;                   // 0x2d4
    float x2d8;                   // 0x2d8
    float x2dc;                   // 0x2dc
    float x2e0;                   // 0x2e0
    float x2e4;                   // 0x2e4
    float x2e8;                   // 0x2e8
    float x2ec;                   // 0x2ec
    float x2f0;                   // 0x2f0
    float x2f4;                   // 0x2f4
    float x2f8;                   // 0x2f8
    float x2fc;                   // 0x2fc
    float x300;                   // 0x300
    float x304;                   // 0x304
    float x308;                   // 0x308
    float x30c;                   // 0x30c
    float x310;                   // 0x310
    float x314;                   // 0x314
    float x318;                   // 0x318
    float x31c;                   // 0x31c
    float x320;                   // 0x320
    float x324;                   // 0x324
    float x328;                   // 0x328
    float x32c;                   // 0x32c
    float x330;                   // 0x330
    float x334;                   // 0x334
    float escapeair_vel;          // 0x338
    float escapeair_veldecaymult; // 0x33c
    float x340;                   // 0x340
    float x344;                   // 0x344
    float x348;                   // 0x348
    float x34c;                   // 0x34c
    float x350;                   // 0x350
    float x354;                   // 0x354
    float x358;                   // 0x358
    float x35c;                   // 0x35c
    float x360;                   // 0x360
    float x364;                   // 0x364
    float x368;                   // 0x368
    float x36c;                   // 0x36c
    float x370;                   // 0x370
    float x374;                   // 0x374
    float x378;                   // 0x378
    float x37c;                   // 0x37c
    float x380;                   // 0x380
    float x384;                   // 0x384
    float x388;                   // 0x388
    float x38c;                   // 0x38c
    float x390;                   // 0x390
    float x394;                   // 0x394
    float x398;                   // 0x398
    float x39c;                   // 0x39c
    float x3a0;                   // 0x3a0
    float x3a4;                   // 0x3a4
    float x3a8;                   // 0x3a8
    float x3ac;                   // 0x3ac
    float x3b0;                   // 0x3b0
    float x3b4;                   // 0x3b4
    float x3b8;                   // 0x3b8
    float x3bc;                   // 0x3bc
    float x3c0;                   // 0x3c0
    float x3c4;                   // 0x3c4
    float x3c8;                   // 0x3c8
    float x3cc;                   // 0x3cc
    float x3d0;                   // 0x3d0
    float x3d4;                   // 0x3d4
    float x3d8;                   // 0x3d8
    float x3dc;                   // 0x3dc
    float x3e0;                   // 0x3e0
    float x3e4;                   // 0x3e4
    float x3e8_shield_kb_frameDecay;                   // 0x3e8
    float x3ec;                   // 0x3ec
    float x3f0;                   // 0x3f0
    float x3f4;                   // 0x3f4
    float x3f8;                   // 0x3f8
    float x3fc;                   // 0x3fc
    float x400;                   // 0x400
    float x404;                   // 0x404
    float x408;                   // 0x408
    float x40c;                   // 0x40c
    float x410;                   // 0x410
    float x414;                   // 0x414
    float x418;                   // 0x418
    float x41c;                   // 0x41c
    float x420;                   // 0x420
    float x424;                   // 0x424
    float x428;                   // 0x428
    float x42c;                   // 0x42c
    float x430;                   // 0x430
    float x434;                   // 0x434
    float x438;                   // 0x438
    float x43c;                   // 0x43c
    float x440;                   // 0x440
    float x444;                   // 0x444
    float x448;                   // 0x448
    float x44c;                   // 0x44c
    float x450;                   // 0x450
    float zjostle_frame;          // 0x45c
    float zjostle_max;            // 0x460
    float ms_zjostle_frame;       // 0x45c
    float ms_zjostle_max;         // 0x460
    float x464;                   // 0x464
    float x468;                   // 0x468
    float x46c;                   // 0x46c
    float x470;                   // 0x470
    float x474;                   // 0x474
    float x478;                   // 0x478
    float x47c;                   // 0x47c
    float x480;                   // 0x480
    float x484;                   // 0x484
    float x488;                   // 0x488
    float x48c;                   // 0x48c
    float x490;                   // 0x490
    float x494;                   // 0x494
    float x498;                   // 0x498
    int cliff_invuln_time;        // 0x49c
    float x4a0;                   // 0x4a0
    float x4a4;                   // 0x4a4
    float x4a8;                   // 0x4a8
    float x4ac;                   // 0x4ac
    float asdi_mag;               // 0x4b0
    float x4b4;                   // 0x4b4
    float x4b8;                   // 0x4b8
    float asdi_units;             // 0x4bc
    float x4c0;                   // 0x4c0
    float x4c4;                   // 0x4c4
    float x4c8;                   // 0x4c8
    float x4cc;                   // 0x4cc
    float x4d0;                   // 0x4d0
    float x4d4;                   // 0x4d4
    float x4d8;                   // 0x4d8
    float x4dc;                   // 0x4dc
    float x4e0;                   // 0x4e0
    float x4e4;                   // 0x4e4
    float x4e8;                   // 0x4e8
    float x4ec;                   // 0x4ec
    float x4f0;                   // 0x4f0
    float x4f4;                   // 0x4f4
    float x4f8;                   // 0x4f8
    float x4fc;                   // 0x4fc
    float x500;                   // 0x500
    float x504;                   // 0x504
    float x508;                   // 0x508
    float x50c;                   // 0x50c
    float x510;                   // 0x510
    float x514;                   // 0x514
    float x518;                   // 0x518
    float x51c;                   // 0x51c
    float x520;                   // 0x520
    float x524;                   // 0x524
    float x528;                   // 0x528
    float x52c;                   // 0x52c
    float x530;                   // 0x530
    float x534;                   // 0x534
    float x538;                   // 0x538
    float x53c;                   // 0x53c
    float x540;                   // 0x540
    float x544;                   // 0x544
    float x548;                   // 0x548
    float x54c;                   // 0x54c
    float x550;                   // 0x550
    float x554;                   // 0x554
    float x558;                   // 0x558
    float x55c;                   // 0x55c
    float x560;                   // 0x560
    float x564;                   // 0x564
    float x568;                   // 0x568
    float x56c;                   // 0x56c
    float x570;                   // 0x570
    float x574;                   // 0x574
    float x578;                   // 0x578
    float x57c;                   // 0x57c
    float x580;                   // 0x580
    float x584;                   // 0x584
    float x588;                   // 0x588
    float x58c;                   // 0x58c
    float x590;                   // 0x590
    float x594;                   // 0x594
    float x598;                   // 0x598
    float x59c;                   // 0x59c
    float x5a0;                   // 0x5a0
    float x5a4;                   // 0x5a4
    float x5a8;                   // 0x5a8
    float x5ac;                   // 0x5ac
    float x5b0;                   // 0x5b0
    float x5b4;                   // 0x5b4
    float x5b8;                   // 0x5b8
    float x5bc;                   // 0x5bc
    float x5c0;                   // 0x5c0
    float x5c4;                   // 0x5c4
    float x5c8;                   // 0x5c8
    float x5cc;                   // 0x5cc
    float x5d0;                   // 0x5d0
    float x5d4;                   // 0x5d4
    float x5d8;                   // 0x5d8
    float x5dc;                   // 0x5dc
    float x5e0;                   // 0x5e0
    float x5e4;                   // 0x5e4
    float x5e8;                   // 0x5e8
    float x5ec;                   // 0x5ec
    float x5f0;                   // 0x5f0
    float x5f4;                   // 0x5f4
    float x5f8;                   // 0x5f8
    float x5fc;                   // 0x5fc
    float x600;                   // 0x600
    float x604;                   // 0x604
    float x608;                   // 0x608
    float x60c;                   // 0x60c
    float x610;                   // 0x610
    float x614;                   // 0x614
    float x618;                   // 0x618
    float x61c;                   // 0x61c
    float x620;                   // 0x620
    float x624;                   // 0x624
    float x628;                   // 0x628
    float x62c;                   // 0x62c
    float x630;                   // 0x630
    float x634;                   // 0x634
    float x638;                   // 0x638
    float x63c;                   // 0x63c
    float x640;                   // 0x640
    float x644;                   // 0x644
    float x648;                   // 0x648
    float x64c;                   // 0x64c
    float x650;                   // 0x650
    float x654;                   // 0x654
    float x658;                   // 0x658
    float x65c;                   // 0x65c
    float x660;                   // 0x660
    float x664;                   // 0x664
    float x668;                   // 0x668
    float x66c;                   // 0x66c
    float x670;                   // 0x670
    float x674;                   // 0x674
    float x678;                   // 0x678
    float x67c;                   // 0x67c
    float x680;                   // 0x680
    float x684;                   // 0x684
    float x688;                   // 0x688
    float x68c;                   // 0x68c
    float x690;                   // 0x690
    float x694;                   // 0x694
    float x698;                   // 0x698
    float x69c;                   // 0x69c
    float x6a0;                   // 0x6a0
    float x6a4;                   // 0x6a4
    float x6a8;                   // 0x6a8
    float x6ac;                   // 0x6ac
    float x6b0;                   // 0x6b0
    float x6b4;                   // 0x6b4
    float x6b8;                   // 0x6b8
    float x6bc;                   // 0x6bc
    float x6c0;                   // 0x6c0
    float x6c4;                   // 0x6c4
    float x6c8;                   // 0x6c8
    float x6cc;                   // 0x6cc
    float x6d0;                   // 0x6d0
    float x6d4;                   // 0x6d4
    float x6d8;                   // 0x6d8
    float x6dc;                   // 0x6dc
    float x6e0;                   // 0x6e0
    float x6e4;                   // 0x6e4
    float x6e8;                   // 0x6e8
    float x6ec;                   // 0x6ec
    float x6f0;                   // 0x6f0
    float x6f4;                   // 0x6f4
    float x6f8;                   // 0x6f8
    float x6fc;                   // 0x6fc
    float x700;                   // 0x700
    float x704;                   // 0x704
    float x708;                   // 0x708
    float x70c;                   // 0x70c
    float x710;                   // 0x710
    float x714;                   // 0x714
    float x718;                   // 0x718
    float x71c;                   // 0x71c
    float x720;                   // 0x720
    float x724;                   // 0x724
    float x728;                   // 0x728
    float x72c;                   // 0x72c
    float x730;                   // 0x730
    float x734;                   // 0x734
    float x738;                   // 0x738
    float x73c;                   // 0x73c
    float x740;                   // 0x740
    float x744;                   // 0x744
    float x748;                   // 0x748
    float x74c;                   // 0x74c
    float x750;                   // 0x750
    float x754;                   // 0x754
    float x758;                   // 0x758
    float x75c;                   // 0x75c
    float x760;                   // 0x760
    float x764;                   // 0x764
    float x768;                   // 0x768
    float x76c;                   // 0x76c
    float x770;                   // 0x770
    float x774;                   // 0x774
    float x778;                   // 0x778
    float x77c;                   // 0x77c
    float x780;                   // 0x780
    float x784;                   // 0x784
    float x788;                   // 0x788
    float x78c;                   // 0x78c
    float x790;                   // 0x790
    float x794;                   // 0x794
    float x798;                   // 0x798
    float x79c;                   // 0x79c
    float x7a0;                   // 0x7a0
    float x7a4;                   // 0x7a4
    float x7a8;                   // 0x7a8
    float x7ac;                   // 0x7ac
    float x7b0;                   // 0x7b0
    float x7b4;                   // 0x7b4
    float x7b8;                   // 0x7b8
    float x7bc;                   // 0x7bc
    float x7c0;                   // 0x7c0
    float x7c4;                   // 0x7c4
    float x7c8;                   // 0x7c8
    float x7cc;                   // 0x7cc
    float x7d0;                   // 0x7d0
    float x7d4;                   // 0x7d4
    float x7d8;                   // 0x7d8
    float x7dc;                   // 0x7dc
    float x7e0;                   // 0x7e0
    float x7e4;                   // 0x7e4
    float x7e8;                   // 0x7e8
    float x7ec;                   // 0x7ec
    float x7f0;                   // 0x7f0
    float x7f4;                   // 0x7f4
    float x7f8;                   // 0x7f8
    float x7fc;                   // 0x7fc
    float x800;                   // 0x800
    float x804;                   // 0x804
    float x808;                   // 0x808
    float x80c;                   // 0x80c
    float x810;                   // 0x810
} ftCommonData;

extern ftCommonData* p_stc_ftcommon;// = (R13 + -0x514C);

void FtChkDevice_DecrementImmunity_800C0A98(HSD_GObj* pPlayerEntityStruct); // @0x800C0A98
float getVec0x2D4_X_assertPlayerIndex_0x8007CDA4(Fighter* pFighter);
float getVec0x2D4_Y_assertPlayerIndex_0x8007cdf8(Fighter* pFighter);
float reduceMagnitude_0x8007CD6C(float value, float delta);
float Stage_GetGroundFrictionMultiplier_0x80084A40(Fighter* pFighter);
void reduceGroundKnockbackVel_0x8007CCA0(Fighter* pFighter, float delta);
float reduceGroundShieldKnockbackVel_0x8007CE4C(Fighter* pFighter, float delta);
float StageInfo_CrowdGaspHeight_0x80224BC4();
float StageInfo_OffscreenBottomLoad_0x80224B98();
void DataOffset_ComboCount_TopNAttackerModify_0x80076528(HSD_GObj* pPlayerEntityStruct);
void SFX_PlayCharacterSFX_0x80088148(Fighter* pFighter, u32 a, u32 b, u32 c);

//void PSVECAdd_0x80342D54(Vec3* v1, Vec3* v2, Vec3* result);

void OSReport_0x803456A8(char* fmt_str, ...);
void __assert(char* filename, u32 line, char* message);

#endif
