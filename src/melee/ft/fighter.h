#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include "sysdolphin/baselib/gobj.h"

// Points to data in PiCo.dat
typedef struct _ftCommonData {
    u8 data_filler_1[0x480];
    f32 x480;
    u8 data_filler_2[0x498-0x484];
    u32 x498_ledgeCooldownTime;
    u8 data_filler_3[0x5F0-0x49C];
    u32 x5F0;
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
    /* 0x00 */ s32 filler_x0;
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
    u32 x40;
    u32 x44;
    u8 filler_x48[0xB4-0x48];
    /* 0xB4 */ Vec2 xB4_ecbCurrCorrect_right;
    /* 0xBC */ Vec2 xBC_ecbCurrCorrect_left;
    u8 filler_xBC[0x134 - 0xBC - 8];
    u32 x134_envFlags;
    u8 filler_x134[0x160 - 0x134 - 4];
    /* 0x160 */ int x160_rightwall_index;
    u8 filler_x160[0x174 - 0x160 - 4];
    /* 0x174 */ int x174_leftwall_index;
    u8 filler_x174[0x1A0 - 0x174 - 4];
} CollData;

typedef struct _Fighter {
    u8 filler_x0[0xC - 0x0];
    u8 xC;
    u8 xD;
    u8 xE;
    u8 xF;
    u32 x10;
    u8 data_filler_x10[0x2C - 0x14];
    float x2C_facing_direction;
    u8 filler_x2C[0xB0 - 0x30];
    /* 0xB0 */ Vec3 xB0_pos;
    u8 filler_xB0[0xC8 - 0xB0 - 12];
    /* 0xC8 */ Vec3 xC8_pos_delta;
    u8 filler_xC8[0xE0 - 0xC8 - 12];
    u32 xE0_airState;
    u8 filler_xE0[0x108 - 0xE4];
    /* 0x108 */ int* x108_costume_archive;
    /* 0x10C */ ftData* x10C_ftData;
    u8 filler_x10C[0x258 - 0x110];
    /* 0x258 */ f32 x258;
    u8 filler_x258[0x2D4 - 0x25C];
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
    u8 filler_x2D8[0x5E8 - 0x2DC];
    /* 0x5E8 */ FighterBone* x5E8_fighterBones;
    u8 filler_x5E8[0x60C - 0x5EC];
    /* 0x60C */ void* x60C;
    u8 filler_x60C[0x618 - 0x610];
    /* 0x618 */ s8 x618_flag;
    /* 0x619 */ s8 x619_flag;
    u8 filler_x619[0x620 - 0x61A];
    /* 0x620 */ f32 x620_lstick_x;
    f32 x624;
    u8 filler_x624[0x670 - 0x628];
    /* 0x670 */ u8 x670_timer_lstick_tilt_x;
    u8 filler_x670[0x68C - 0x671];
    /* 0x68C */ Vec x68C;
    u8 filler_x68C[0x6F0 - 0x698];
    /* 0x6F0 */ CollData x6F0_collData;
    /* 0x890 */ CameraBox* x890;
    /* 0x894 */ f32 x894;
    u8 filler_x894[0x8AC - 0x898];
    /* 0x8AC */ s32 x8AC_animSkeleton;
    u8 filler_x8AC[0x914 - 0x8B0];
    /* 0x914 */ f32 x914;
    u8 filler_x914[0x18B0 - 0x918];
    /* 0x18B0 */ f32 x18B0;
    u8 filler_x18B0[0x1969 - 0x18B4];
    /* 0x1969 */ u8 x1969_walljumpUsed;
    /* 0x196C */ int x196C;
    /* 0x1970 */ int x1970;
    /* 0x1974 */ void* x1974_heldItem;
    u8 filler_x1974[0x1A58 - 0x1978];
    /* 0x1A58 */ HSD_GObj* x1A58;
    u8 filler_x1A58[0x2064 - 0x1A5C];
    u32 x2064_ledgeCooldown;
    u8 filler_x2064[0x210C - 0x2068];
    /* 0x210C */ u8 x210C_walljumpInputTimer;
    u8 filler_x210C[3];
    /* 0x2110 */ f32 x2110_walljumpWallSide;
    u8 filler_x2110[0x213C - 0x2114];
    /* 0x213C */ u32 x213C;
    u8 filler_x2114[0x21DC - 0x2140];
    /* 0x21DC */ u32 x21DC;
    /* 0x21E0 */ u32 x21E0;
    /* 0x21E4 */ u32 x21E4;
    u8 filler_x2138[0x2200 - 0x21E8];
	  /* 0x2200 */ u32 x2200_ftcmd_var0;
    /* 0x2204 */ u32 x2200_ftcmd_var1;
    /* 0x2208 */ u32 x2200_ftcmd_var2;
    /* 0x220C */ u32 x2200_ftcmd_var3;
    /* 0x2210 */ ThrowFlags x2210_ThrowFlags;
    /* 0x2214 */ u32 x2214;
    /* 0x2218 */ u32 x2218;
    /* 0x221C */ u8 x221C;
    UnkFlagStruct x221D_flag;
    u8 filler_x221E;
    UnkFlagStruct x221F_flag;
    u8 filler_x2220;
    u8 filler_x2221;
    /* 0x2222 */ UnkFlagStruct x2222_flag;
    u8 filler_x2223;
    /* 0x2224 */ UnkFlagStruct x2224_flag;
    u8 filler_x2225;
    /* 0x2226 */ UnkFlagStruct x2226_flag;
    u8 filler_x2227;
    /* 0x2228 */ UnkFlagStruct x2228_flag;
    u8 filler_x2229;
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

#endif
