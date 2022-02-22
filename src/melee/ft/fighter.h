#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include "sysdolphin/baselib/gobj.h"

typedef enum
{
	FighterID_Mario,
	FighterID_Fox,
	FighterID_CFalcon,
	FighterID_Donkey,
	FighterID_Kirby,
	FighterID_Koopa,
	FighterID_Link,
	FighterID_Seak,
	FighterID_Ness,
	FighterID_Peach,
	FighterID_Popo,
	FighterID_Nana,
	FighterID_Pikachu,
	FighterID_Samus,
	FighterID_Yoshi,
	FighterID_Purin,
	FighterID_Mewtwo,
	FighterID_Luigi,
	FighterID_Mars,
	FighterID_Zelda,
	FighterID_CLink,
	FighterID_DrMario,
	FighterID_Falco,
	FighterID_Pichu,
	FighterID_GameWatch,
	FighterID_Ganon,
	FighterID_Roy,
	FighterID_Masterhand,
	FighterID_Crazyhand,
	FighterID_ZakoBoy,
	FighterID_ZakoGirl,
	FighterID_GKoopa,
	FighterID_Sandbag,
} FighterID;

// Points to data in PiCo.dat
typedef struct _ftCommonData {
	u8 filler_x0[0x98];
	/* 0x98 */ f32 x98_shieldHealthInit;
	u8 filler_x9C[0x200-0x9C];
	/* 0x200 */ f32 x200;
	/* 0x204 */ f32 x204_knockbackFrameDecay;
	u8 filler_x208[0x3E8-0x208];
	/* 0x3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
	/* 0x3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
	u8 filler_x3F0[0x480-0x3F0];
	/* 0x480 */ f32 x480;
	u8 filler_x484[0x498-0x484];
	/* 0x498 */ u32 x498_ledgeCooldownTime;
	u8 filler_x49C[0x5F0-0x49C];
	/* 0x5F0 */ u32 x5F0;
	u8 filler_x5F4[0x768-0x5F4];
	/* 0x768 */ f32 x768;
	/* 0x76C */ f32 x76C;
	/* 0x770 */ f32 x770;
	/* 0x774 */ s32 x774;
	// lots of more data following, exact size to be determined
} ftCommonData;

typedef struct _FtCollisionData
{
    u8 data_filler_0[0x28];
    u32 x28;
} FtCollisionData;

typedef struct _ftData
{
    s32 filler_x0;
    /* 0x04 */ s32* ext_attr;
    s32 filler_x4[16];
    /* 0x48 */ void* x48_items;
    FtCollisionData* x4C_collisionData;
    s32 filler_x50[2];
    void* x58;
} ftData;

typedef struct _Vec2 { float x, y; } Vec2;
typedef Vec Vec3;

typedef struct _UnkFlagStruct {
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    } bits;
} UnkFlagStruct;

typedef struct _ThrowFlags
{
  union {
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
    };
    u32 flags;
  };
} ThrowFlags;

typedef struct _FighterBone
{
  /* 0x0 */ u32* x0_joint;
  /* 0x4 */ u32* x4_joint2; // used for interpolation
  u32 data_filler[2];
} FighterBone;

typedef struct _CameraBox
{
  u32 data_filler[3];
  struct {
        u8 b0 : 1;
        u8 b1 : 1;
        u8 b2 : 1;
        u8 b3 : 1;
        u8 b4 : 1;
        u8 b5 : 1;
        u8 b6 : 1;
        u8 b7 : 1;
  } xC_flag;
} CameraBox;

typedef struct _CollData
{
	u8 filler_x0[0x40];
	/* 0x40 */ u32 x40;
	/* 0x44 */ u32 x44;
	u8 filler_x48[0xB4-0x48];
	/* 0xB4 */ Vec2 xB4_ecbCurrCorrect_right;
	/* 0xBC */ Vec2 xBC_ecbCurrCorrect_left;
	u8 filler_xBC[0x134 - 0xBC - 8];
	/* 0x134 */ s32 x134_envFlags;
	u8 filler_x138[0x14C - 0x138];
	/* 0x14C */ s32 x14C_groundIndex;
	s32 filler_x150;
        /* 0x154 */ Vec3 x154_groundNormal; // points out of the ground surface
	/* 0x160 */ int x160_rightwall_index;
	u8 filler_x160[0x174 - 0x160 - 4];
	/* 0x174 */ int x174_leftwall_index;
	u8 filler_x174[0x1A0 - 0x174 - 4];
} CollData;

typedef struct _HitVictim
{
	void *data; // userdata of the object that was hit
	int timer;  // items use this to wait until hitting this gobj again
} HitVictim;

typedef struct _ftHit
{
	u8 filler_x0[0x134];
	int x134;                     // 0x134, flags of some sort
} ftHit;

typedef struct _Fighter {
	/* 0x0 */ HSD_GObj *x0_fighter;
	/* 0x4 */ FighterID x4_fighterID;
	/* 0x8 */ s32 x8_spawnNum;
	/* 0xC */ u8 xC_playerID;
	u8 xD;
	u8 xE;
	u8 xF;
	u32 x10;
	u8 data_filler_x10[0x2C - 0x14];
	/* 0x2C */ f32 x2C_facing_direction;
	/* 0x30 */ f32 x30_facingDirectionRepeated;
	/* 0x34 */ Vec3 x34_scale;
	u8 filler_x40[0x74 - 0x40];
	/* 0x74 */ Vec3 x74_animVel;
	/* 0x80 */ Vec3 x80_selfVel;
	/* 0x8C */ Vec3 x8C_knockbackVel;
	/* 0x98 */ Vec3 x98_AtkShieldKnockback;
	/* 0xA4 */ Vec3 xA4_unkVel;
	/* 0xB0 */ Vec3 xB0_pos;
	/* 0xBC */ Vec3 xBC_prevPos;
	/* 0xC8 */ Vec3 xC8_pos_delta;
	/* 0xD4 */ Vec3 xD4_unkVel;
	/* 0xE0 */ s32 xE0_airState;
	/* 0xE4 */ f32 xE4_groundAccel1;
	/* 0xE8 */ f32 xE8_groundAccel2;
	/* 0xEC */ f32 xEC_groundVel;
	/* 0xF0 */ f32 xF0_knockbackGroundVel;
	/* 0xF4 */ f32 xF4_groundAttackerShieldKnockbackVel;
	/* 0xF8 */ Vec2 xF8_playerNudgeVel;
	/* 0x100 */ f32 x100;
	s32 filler_x104;
	/* 0x108 */ int* x108_costume_archive;
	/* 0x10C */ ftData* x10C_ftData;
	// TODO: Ask Psi how many of those are confirmed
	struct attr
	{
		/* 0x110 */ f32 x110_walk_initial_velocity;
		/* 0x114 */ f32 x114_walk_acceleration;
		/* 0x118 */ f32 x118_walk_maximum_velocity;
		/* 0x11C */ f32 x11C_slow_walk_max;
		/* 0x120 */ f32 x120_mid_walk_point;
		/* 0x124 */ f32 x124_fast_walk_min;
		/* 0x128 */ f32 x128_ground_friction; // used
		/* 0x12C */ f32 x12C_dash_initial_velocity;
		/* 0x130 */ f32 x130_dashrun_acceleration_a;
		/* 0x134 */ f32 x134_dashrun_acceleration_b;
		/* 0x138 */ f32 x138_dashrun_terminal_velocity;
		/* 0x13C */ f32 x13C_run_animation_scaling;
		/* 0x140 */ f32 x140_max_runbrake_frames;
		/* 0x144 */ f32 x144_grounded_max_horizontal_velocity;
		/* 0x148 */ f32 x148_jump_startup_time;
		/* 0x14C */ f32 x14C_jump_h_initial_velocity;
		/* 0x150 */ f32 x150_jump_v_initial_velocity;
		/* 0x154 */ f32 x154_ground_to_air_jump_momentum_multiplier;
		/* 0x158 */ f32 x158_jump_h_max_velocity;
		/* 0x15C */ f32 x15C_hop_v_initial_velocity;
		/* 0x160 */ f32 x160_air_jump_v_multiplier;
		/* 0x164 */ f32 x164_air_jump_h_multiplier;
		/* 0x168 */ int x168_max_jumps;
		/* 0x16C */ f32 x16C_gravity;
		/* 0x170 */ f32 x170_terminal_velocity;
		/* 0x174 */ f32 x174_aerialDriftStickMult;
		/* 0x178 */ f32 x178_aerialDriftBase;
		/* 0x17C */ f32 x17C_aerialDriftMax;
		/* 0x180 */ f32 x180_aerialFriction;
		/* 0x184 */ f32 x184_fastfall_velocity;
		/* 0x188 */ f32 x188_horizontal_air_mobility_constant;
		/* 0x18C */ int x18C_jab_2_input_window;
		/* 0x190 */ int x190_jab_3_input_window;
		/* 0x194 */ int x194_frames_to_change_direction_on_standing_turn;
		/* 0x198 */ f32 x198_weight;
		/* 0x19C */ f32 x19C_model_scaling;
		/* 0x1A0 */ f32 x1A0_initial_shield_size;
		/* 0x1A4 */ f32 x1A4_shield_break_initial_velocity;
		/* 0x1A8 */ int x1A8_rapid_jab_window;
		/* 0x1AC */ int x1AC_unknown1AC;
		/* 0x1B0 */ int x1B0_unknown1B0;
		/* 0x1B4 */ int x1B4_unknown1B4;
		/* 0x1B8 */ f32 x1B8_ledge_jump_horizontal_velocity;
		/* 0x1BC */ f32 x1BC_ledge_jump_vertical_velocity;
		/* 0x1C0 */ f32 x1C0_item_throw_velocity_multiplier;
		/* 0x1C4 */ int x1C4_unknown1C4;
		/* 0x1C8 */ int x1C8_unknown1C8;
		/* 0x1CC */ int x1CC_unknown1CC;
		/* 0x1D0 */ int x1D0_unknown1D0;
		/* 0x1D4 */ int x1D4_unknown1D4;
		/* 0x1D8 */ int x1D8_unknown1D8;
		/* 0x1DC */ int x1DC_unknown1DC;
		/* 0x1E0 */ int x1E0_unknown1E0;
		/* 0x1E4 */ int x1E4_unknown1E4;
		/* 0x1E8 */ int x1E8_unknown1E8;
		/* 0x1EC */ int x1EC_unknown1EC;
		/* 0x1F0 */ f32 x1F0_kirby_b_star_damage;
		/* 0x1F4 */ f32 x1F4_normal_landing_lag;
		/* 0x1F8 */ f32 x1F8_n_air_landing_lag;
		/* 0x1FC */ f32 x1FC_f_air_landing_lag;
		/* 0x200 */ f32 x200_b_air_landing_lag;
		/* 0x204 */ f32 x204_u_air_landing_lag;
		/* 0x208 */ f32 x208_d_air_landing_lag;
		/* 0x20C */ f32 x20C_nametag_height;
		/* 0x210 */ int x210_unknown210;
		/* 0x214 */ f32 x214_wall_jump_horizontal_velocity;
		/* 0x218 */ f32 x218_wall_jump_vertical_velocity;
		/* 0x21C */ int x21C_unknown21C;
		/* 0x220 */ f32 x220_trophy_scale;
		/* 0x224 */ int x224_unknown224;
		/* 0x228 */ int x228_unknown228;
		/* 0x22C */ int x22C_unknown22C;
		/* 0x230 */ int x230_unknown230;
		/* 0x234 */ int x234_unknown234;
		/* 0x238 */ int x238_unknown238;
		/* 0x23C */ int x23C_unknown23C;
		/* 0x240 */ int x240_unknown240;
		/* 0x244 */ int x244_unknown244;
		/* 0x248 */ int x248_unknown248;
		/* 0x24C */ int x24C_unknown24C;
		/* 0x250 */ int x250_unknown250;
		/* 0x254 */ int x254_unknown254;
		/* 0x258 */ f32 x258; // used
		/* 0x25C */ f32 x25C_bubble_ratio;
		/* 0x260 */ int x260_unknown260;
		/* 0x264 */ int x264_unknown264;
		/* 0x268 */ int x268_unknown268;
		/* 0x26C */ int x26C_unknown26C;
		/* 0x270 */ f32 x270_respawn_platform_scale;
		/* 0x274 */ int x274_unknown274;
		/* 0x278 */ int x278_unknown278;
		/* 0x27C */ int x27C_camera_zoom_target_bone;
		/* 0x280 */ int x280_unknown280;
		/* 0x284 */ int x284_unknown284;
		/* 0x288 */ int x288_unknown288;
		/* 0x28C */ int x28C_special_jump_action___1;
		/* 0x290 */ int x290_weight_dependent_throw_speed_flags;
	} x110_attr;
	u8 filler_x294[0x2D4 - 0x294];
	/* 0x2D4 */ void* x2D4_specialAttributes;
	/* 0x2D8 */ void* x2D8_specialAttributes2;
	u8 filler_x2D8[0x594 - 0x2DC];
	/* 0x594 */ u8 x594_animCurrFlags1;
	u8 filler_x595[0x5E8 - 0x595];
	/* 0x5E8 */ FighterBone* x5E8_fighterBones;
	u8 filler_x5EC[0x60C - 0x5EC];
	s32 x60C;
	u8 filler_x610[0x618 - 0x610];
	/* 0x618 */ s8 x618_flag;
	/* 0x619 */ s8 x619_flag;
	u8 filler_x61A[0x61D - 0x61A];
	/* 0x61D */ s8 x61D;
	u8 filler_x61E[0x620 - 0x61E];
	/* 0x620 */ f32 x620_lstick_x;
	f32 x624;
	u8 filler_x624[0x670 - 0x628];
	/* 0x670 */ u8 x670_timer_lstick_tilt_x;
	u8 filler_x670[0x68C - 0x671];
	/* 0x68C */ Vec3 x68C;
	u8 filler_x698[0x6A4-0x698];
	/* 0x6A4 */ Vec3 x6A4_transNOffset;
	u8 filler_x6B0[0x6BC-0x6B0];
	/* 0x6BC */ f32 x6BC_inputStickangle;
	/* 0x6C0 */ f32 x6C0;
	/* 0x6C4 */ f32 x6C4;
	/* 0x6C8 */ f32 x6C8;
	u8 filler_x6CC[0x6D8-0x6CC];
	/* 0x6D8 */ f32 x6D8;
	/* 0x6DC */ f32 x6DC;
	/* 0x6E0 */ f32 x6E0;
	u8 filler_x6E4[0x6F0 - 0x6E4];
	/* 0x6F0 */ CollData x6F0_collData;
	/* 0x890 */ CameraBox* x890;
	/* 0x894 */ f32 x894;
	/* 0x898 */ f32 x898;
	/* 0x89C */ f32 x89C;
	/* 0x8A0 */ f32 x8A0;
	s32 filler_x8A4[2];
	/* 0x8AC */ s32 x8AC_animSkeleton;
	u8 filler_x8AC[0x914 - 0x8B0];
	/* 0x914 */ f32 x914;
	u8 filler_x918[0x1064 - 0x918];
	/* 0x1064 */ ftHit x1064_thrownHitbox;
	u8 filler_x1064[0x1828 - 0x1064 - sizeof(ftHit)];
	/* 0x1828 */ s32 x1828;
	s32 filler_x182C;
	/* 0x1830 */ f32 x1830_percent;
	/* 0x1834 */ f32 x1834;
	/* 0x1838 */ f32 x1838_percentTemp;
	/* 0x183C */ s32 x183C;
	/* 0x1840 */ s32 x1840;
	u8 filler_x1844[0x1850 - 0x1844];
	/* 0x1850 */ f32 x1850_forceApplied;
	u8 filler_x1854[0x189C - 0x1854];
	/* 0x189C */ f32 x189C;
	/* 0x18A0 */ f32 x18A0;
	/* 0x18A4 */ f32 x18A4_knockbackMagnitude;
	/* 0x18A8 */ f32 x18A8;
	/* 0x18A8 */ f32 x18AC_timeSinceHit;
	/* 0x18B0 */ f32 x18B0;
	/* 0x18B4 */ f32 x18B4_armor;
	/* 0x18B8 */ f32 x18B8;
	/* 0x18BC */ f32 x18BC;
	/* 0x18C0 */ s32 x18C0;
	/* 0x18C4 */ s32 x18C4;
	/* 0x18C8 */ s32 x18C8;
	/* 0x18CC */ s32 x18CC;
	/* 0x18D0 */ s32 x18D0;
	u8 filler_x18D4[0x18F0 - 0x18D4];
	/* 0x18F0 */ s32 x18F0;
	/* 0x18F4 */ s32 x18F4;
	/* 0x18F8 */ u8 x18F8;
	u8 filler_x18F9;
	/* 0x18FA */ u16 x18FA;
	/* 0x18FC */ u8 x18FC;
	/* 0x18FD */ u8 x18FD;
	u8 filler_x18FE[0x1908 - 0x18FE];
	/* 0x1908 */ s32 x1908;
	/* 0x190C */ s32 x190C;
	/* 0x1910 */ s32 x1910;
	/* 0x1914 */ s32 x1914;
	/* 0x1918 */ s32 x1918;
	/* 0x191C */ f32 x191C;
	s32 filler_x1920;
	/* 0x1924 */ s32 x1924;
	/* 0x1928 */ f32 x1928;
	u8 filler_x192C[0x1948 - 0x192C];
	/* 0x1948 */ s32 x1948;
	/* 0x194C */ s32 x194C;
	/* 0x1948 */ s32 x1950;
	/* 0x1954 */ f32 x1954;
	/* 0x1958 */ f32 x1958;
	/* 0x195C */ f32 x195C_hitlagFrames;
	/* 0x1960 */ f32 x1960_vibrateMult;
	/* 0x1964 */ f32 x1964;
	/* 0x1968 */ u8 x1968_jumpsUsed;
	/* 0x1969 */ u8 x1969_walljumpUsed;
	/* 0x196C */ int x196C;
	/* 0x1970 */ int x1970;
	/* 0x1974 */ void* x1974_heldItem;
	/* 0x1978 */ HSD_GObj* x1978;
	/* 0x197C */ s32 x197C;
	/* 0x1980 */ HSD_GObj* x1980;
	/* 0x1984 */ HSD_GObj* x1984_heldItemSpec;
	/* 0x1988 */ s32 x1988;
	/* 0x198C */ s32 x198C;
	/* 0x1990 */ s32 x1990;
	/* 0x1994 */ s32 x1994;
	/* 0x1998 */ f32 x1998_shieldHealth;
	/* 0x199C */ f32 x199C_shieldLightshieldAmt;
	/* 0x19A0 */ s32 x19A0_shieldDamageTaken;
	/* 0x19A4 */ s32 x19A4_shieldDamageTaken2;
	/* 0x19A8 */ HSD_GObj* x19A8_shieldDamageSource;
	s32 filler_x19AC[2];
	/* 0x19B4 */ f32 x19B4_shieldUnk;
	/* 0x19B8 */ f32 x19B8_shieldUnk;
	/* 0x19BC */ s32 x19BC_shieldDamageTaken3;
	u8 filler_x19C0[0x1A2C - 0x19C0];
	/* 0x1A2C */ f32 x1A2C_reflectHitDirection;
	s32 filler_x1A30[3];
	/* 0x1A3C */ s32 x1A3C;
	/* 0x1A40 */ f32 x1A40;
	/* 0x1A44 */ s32 x1A44;
	/* 0x1A48 */ s32 x1A48;
	u8 filler_x1A4C[0x1A52 - 0x1A4C];
	/* 0x1A52 */ s8 x1A52;
	/* 0x1A53 */ s8 x1A53;
	s32 filler_x1A54;
	/* 0x1A58 */ HSD_GObj* x1A58; // grabAttacker?
	/* 0x1A5C */ HSD_GObj* x1A5C; // grabVictim?
	/* 0x1A60 */ s32 x1A60;
	/* 0x1A64 */ s32 x1A64;
	u8 filler_x1A68[0x2008-0x1A68];
	/* 0x2008 */ s32 x2008;
	/* 0x200C */ s32 x200C;
	/* 0x2010 */ s32 x2010;
	u8 filler_x2014[0x2028 - 0x2014];
	/* 0x2028 */ s32 x2028;
	/* 0x202C */ s32 x202C;
	s32 filler_x2030;
	/* 0x2034 */ s32 x2034;
	/* 0x2038 */ s32 x2038;
	u8 filler_x203C[0x2064 - 0x203C];
	/* 0x2064 */ s32 x2064_ledgeCooldown;
	u8 filler_x2068[0x208C - 0x2068];
	/* 0x208C */ s32 x208C;
	/* 0x2090 */ s16 x2090;
	/* 0x2092 */ s16 x2092;
	/* 0x2094 */ s32 x2094;
	/* 0x2098 */ s16 x2098;
	s16 filler_x209A;
	/* 0x209C */ s16 x209C;
	/* 0x20A0 */ s32 x20A0;
	s32 filler_x20A4[2];
	/* 0x20AC */ s32 x20AC;
	u8 filler_x20B0[0x2100 - 0x20B0];
	/* 0x2100 */ s8 x2100;
	/* 0x2101 */ u8 x2101_bits_0to6 : 7;
	/* 0x2101 */ u8 x2101_bits_8 : 1;
	u8 filler_x2102[0x2108 - 0x2102];
	/* 0x2108 */ s32 x2108;
	/* 0x210C */ u8 x210C_walljumpInputTimer;
	u8 filler_x210C[3];
	/* 0x2110 */ f32 x2110_walljumpWallSide;
	u8 filler_x2114[0x2135 - 0x2114];
	/* 0x2135 */ s8 x2135;
	s16 filler_x2136;
	/* 0x2138 */ f32 x2138_smashSinceHitbox;
	/* 0x213C */ s32 x213C;
	/* 0x2140 */ f32 x2140;
	/* 0x2144 */ s32 x2144;
	/* 0x2148 */ s32 x2148;
	/* 0x214C */ s32 x214C;
	/* 0x2150 */ s32 x2150;
	/* 0x2154 */ s32 x2154;
	/* 0x2158 */ s32 x2158;
	/* 0x215C */ s32 x215C;
	/* 0x2160 */ s32 x2160;
	/* 0x2164 */ s32 x2164;
	/* 0x2168 */ s32 x2168;
	s32 filler_x216C;
	/* 0x2170 */ f32 x2170;
	u8 filler_x2174[0x2180 - 0x2174];
	/* 0x2180 */ s32 x2180;
	u8 filler_x2184[0x2190 - 0x2184];
	// callback struct. Not all of them used by fighter.c, but I'm leaving them in for now.
	void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter); // used
	void (*x2194_callback_x2194)(HSD_GObj *fighter); // used
	void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj *fighter); // used
	void (*x219C_callback_IASA)(HSD_GObj *fighter); // used
	void (*x21A0_callback_Anim)(HSD_GObj *fighter);
	void (*x21A4_callback_Phys)(HSD_GObj *fighter); // xused
	void (*x21A8_callback_Coll)(HSD_GObj *fighter);
	void (*x21AC_callback_Cam)(HSD_GObj *fighter);
	void (*x21B0_callback_Accessory1)(HSD_GObj *fighter);
	void (*x21B4_callback_Accessory2)(HSD_GObj *fighter); // used
	void (*x21B8_callback_Accessory3)(HSD_GObj *fighter); // used
	void (*x21BC_callback_Accessory4)(HSD_GObj *fighter);
	void (*x21C0_callback_OnGiveDamage)(HSD_GObj *fighter);
	void (*x21C4_callback_OnShieldHit)(HSD_GObj *fighter);
	void (*x21C8_callback_OnReflectHit)(HSD_GObj *fighter);
	void (*x21CC_callback_x21cc)(HSD_GObj *fighter);
	void (*x21D0_callback_EveryHitlag)(HSD_GObj *fighter); // xused
	void (*x21D4_callback_EnterHitlag)(HSD_GObj *fighter);
	void (*x21D8_callback_ExitHitlag)(HSD_GObj *fighter);
	void (*x21DC_callback_OnTakeDamage)(HSD_GObj *fighter);
	void (*x21E0_callback_OnDeath)(HSD_GObj *fighter); // used
	void (*x21E4_callback_OnDeath2)(HSD_GObj *fighter); // used. internally Dead_Proc as evidenced by 800f5430
	void (*x21E8_callback_OnDeath3)(HSD_GObj *fighter); // used
	u8 filler_x21EC[0x2200 - 0x21EC];
	/* 0x2200 */ u32 x2200_ftcmd_var0;
	/* 0x2204 */ u32 x2200_ftcmd_var1;
	/* 0x2208 */ u32 x2200_ftcmd_var2;
	/* 0x220C */ u32 x2200_ftcmd_var3;
	/* 0x2210 */ ThrowFlags x2210_ThrowFlags;
	/* 0x2214 */ f32 x2214;
	/* 0x2218 */ UnkFlagStruct x2218_flag;
	/* 0x2219 */ UnkFlagStruct x2219_flag;
	/* 0x221A */ UnkFlagStruct x221A_flag;
	/* 0x221B */ UnkFlagStruct x221B_flag;
	/* 0x221C */
	union
	{
		struct
		{
			UnkFlagStruct x221C_flag;
			UnkFlagStruct x221D_flag;
		};
		struct
		{
			u16 x221C_u16_x : 7;
			u16 x221C_u16_y : 3;
			u16 x221C_u16_z : 6;
		};
	};
	/* 0x221E */ UnkFlagStruct x221E_flag;
	/* 0x221F */ UnkFlagStruct x221F_flag;
	/* 0x2220 */ UnkFlagStruct x2220_flag;
	/* 0x2221 */ UnkFlagStruct x2221_flag;
	/* 0x2222 */ UnkFlagStruct x2222_flag;
	/* 0x2224 */ UnkFlagStruct x2223_flag;
	/* 0x2224 */ UnkFlagStruct x2224_flag;
	/* 0x2224 */ UnkFlagStruct x2225_flag;
	/* 0x2226 */ UnkFlagStruct x2226_flag;
	/* 0x2227 */ UnkFlagStruct x2227_flag;
	/* 0x2228 */ UnkFlagStruct x2228_flag;
	/* 0x2229 */ UnkFlagStruct x2229_flag;
	/* 0x222A */ UnkFlagStruct x222A_flag;
	u8 filler_x222B;
	/* 0x222C */ u32 x222C;
	/* 0x2230 */ u32 x2230;
	/* 0x2234 */ u32 x2234;
	/* 0x2238 */ u32 x2238;
	/* 0x223C */ u32 x223C;
	/* 0x2240 */ u32 x2240;
	/* 0x2244 */ u32 x2244;
	/* 0x2248 */ u32 x2248;
	/* 0x224C */ u32 x224C;
	u8 filler_x224C[0x2340-0x2250];
	/* 0x2340 */ u32 x2340_stateVar1;
	/* 0x2344 */ u32 x2344_stateVar2;
	/* 0x2348 */ u32 x2348_stateVar3;
	/* 0x234C */ u32 x234C_stateVar4;
	/* 0x2350 */ u32 x2350_stateVar5;
	/* 0x2354 */ float x2354_stateVar6;
	/* 0x2358 */ float x2358_stateVar7;
} Fighter;

// functions from fighter.s
void func_800679B0();
void func_80067A84();
void func_80067ABC();
void func_80067BB4(HSD_GObj* pPlayerEntity);
void func_80067C98(Fighter*);
void func_80068354();
void func_800686E4();
void func_8006876C();
void func_80068854();
void func_80068914();
void func_80068E64();
void func_80068E98();
void func_800693AC(void*, s32, s32, s32, f32, f32, f32);
void func_8006A1BC();
void func_8006A360();
void func_8006ABA0();
void func_8006ABEC();
void func_8006AD10();
void func_8006B82C();
void func_8006C0F0(HSD_GObj* fighterObj);
void func_8006C27C();
void func_8006C5F4(HSD_GObj* pPlayerEntityStruct);
void func_8006C624();
void func_8006C80C();
void func_8006CA5C();
void func_8006CB94();
void func_8006CC30();
void func_8006CC7C();
void func_8006CDA4();
void func_8006CF5C();
void func_8006CFBC();
void func_8006CFE0();
void func_8006D044();
void func_8006D10C();
void func_8006D1EC();
void func_8006D9AC();
void func_8006D9EC();
void func_8006DA4C();
void func_8006DABC();

#endif
