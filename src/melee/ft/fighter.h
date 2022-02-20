#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include "sysdolphin/baselib/gobj.h"

typedef struct { float x, y;    } Vec2;
typedef Vec Vec3;

typedef struct _ftData
{
	s32 filler_x0;
	/* 0x04 */ s32* ext_attr;
	s32 filler_x4[16];
	/* 0x48 */ void* x48_items;
	s32 filler_x48[4];
} ftData;

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

typedef struct _CollData
{
	u8 filler_x0[0xB4];
	/* 0xB4 */ Vec2 xB4_ecbCurrCorrect_right;
	/* 0xBC */ Vec2 xBC_ecbCurrCorrect_left;
	u8 filler_xBC[0x134 - 0xBC - 8];
	/* 0x134 */ int x134_envFlags;
	u8 filler_x134[0x160 - 0x134 - 4];
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
	HSD_GObj *x0_fighter;
	s32 filler_x4;
	/* 0x8 */ s32 x8_spawnNum;
	u8 xC_playerID;
	u8 filler_xD[0x2C - 0xD];
	/* 0x2C */ f32 x2C_facing_direction;
	/* 0x30 */ f32 x30_facingDirectionRepeated;
	/* 0x34 */ Vec3 x34_scale;
	u8 filler_x40[0xB0 - 0x40];
	/* 0xB0 */ Vec3 xB0_pos;
	/* 0xBC */ Vec3 xBC_prevPos;
	/* 0xC8 */ Vec3 xC8_pos_delta;
	u8 filler_xC8[0xE0 - 0xC8 - 12];
	/* 0xE0 */ u32 xE0_airState;
	u8 filler_xE0[0xF8 - 0xE4];
	/* 0xF8 */ Vec2 xF8_playerNudgeVel;
	/* 0x100 */ f32 x100;
	s32 filler_x104;
	/* 0x108 */ int* x108_costume_archive;
	/* 0x10C */ ftData* x10C_ftData;
	u8 filler_x10C[0x258 - 0x110];
	/* 0x258 */ f32 x258;
	u8 filler_x258[0x2D4 - 0x25C];
	/* 0x2D4 */ void* x2D4_specialAttributes;
	/* 0x2D8 */ void* x2D8_specialAttributes2;
	u8 filler_x2D8[0x5E8 - 0x2DC];
	/* 0x5E8 */ FighterBone* x5E8_fighterBones;
	u8 filler_x5E8[0x618 - 0x5EC];
	/* 0x618 */ s8 x618_flag;
	/* 0x619 */ s8 x619_flag;
	u8 filler_x61A[0x61D - 0x61A];
	/* 0x61D */ s8 x61D;
	u8 filler_x61E[0x620 - 0x61E];
	/* 0x620 */ f32 x620_lstick_x;
	u8 filler_x620[0x670 - 0x624];
	/* 0x670 */ u8 x670_timer_lstick_tilt_x;
	u8 filler_x670[0x68C - 0x671];
	/* 0x68C */ Vec3 x68C_transNPos;
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
	u8 filler_x6F0[0x894 - 0x6F0 - sizeof(CollData)];
	/* 0x894 */ f32 x894_animFrame;
	/* 0x898 */ f32 x898_animUnk;
	/* 0x89C */ f32 x89C_animRate;
	/* 0x8A0 */ f32 x8A0_animUnk;
	s32 filler_x8A4[2];
	/* 0x8AC */ s32 x8AC_animSkeleton;
	u8 filler_x8AC[0x1064 - 0x8B0];
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
	s32 filler_x194C;
	/* 0x1948 */ s32 x1950;
	/* 0x1954 */ f32 x1954;
	/* 0x1958 */ f32 x1958;
	/* 0x195C */ f32 x195C_hitlagFrames;
	/* 0x1960 */ f32 x1960_vibrateMult;
	/* 0x1964 */ f32 x1964;
	/* 0x1968 */ u8 x1968_jumpsUsed;
	/* 0x1969 */ u8 x1969_walljumpUsed;
	/* 0x196C */ f32 x196C_hitlagMult;
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
	/* 0x1A58 */ u32 x1A58; // HSD_GObj* grabAttacker ?
	/* 0x1A5C */ u32 x1A5C; // HSD_GObj* grabVictim ?
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
	u8 filler_x2114[0x2138 - 0x2114];
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
	// callback struct
	void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter);
	void (*x2194_callback_x2194)(HSD_GObj *fighter);
	void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj *fighter);
	void (*x219C_callback_IASA)(HSD_GObj *fighter);
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
	void (*x21EC_callback_OnActionStateChange)(HSD_GObj *fighter);
	void (*x21F0_callback_OnTakeDamage2)(HSD_GObj *fighter);
	void (*x21F4_callback_OnHurtboxDetect)(HSD_GObj *fighter);
	void (*x21F8_callback_OnSpin)(HSD_GObj *fighter);
	u8 filler_x21FC[0x2200 - 0x21FC];
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
			u8 x221C_0 : 1;
			u8 x221C_1 : 1;
			u8 x221C_2 : 1;
			u8 x221C_3 : 1;
			u8 x221C_4 : 1;
			u8 x221C_5 : 1;
			u8 x221C_6_hitstun : 1; // used
			u8 x221C_7 : 1;

			u8 x221D_0 : 1;
			u8 x221D_1 : 1;
			u8 x221D_2 : 1;
			u8 x221D_3 : 1; // input enable
			u8 x221D_4 : 1;
			u8 x221D_5 : 1; // nudge disable
			u8 x221D_6 : 1; // ground ignore
			u8 x221D_7 : 1;
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


typedef struct // ftCommonData
{
	u8 filler_x0[0x768-0x0];
	/* 0x768 */ float x768;
	/* 0x76C */ float x76C;
	/* 0x770 */ float x770;
	/* 0x774 */ s32 x774;
	// lots of more data following, exact size to be determined
} ftCommonData;

// TODO: check which functions belong to fighter.h and which functions must be imported
void func_8000B1CC();
void func_8000D148();
void func_8000ED54();
void func_8000EE8C();
void func_80016C64(char*, s32**, char*, s32, ...); // from lbarchive.s
void func_80022C30();
void func_80029020();
void func_800290D4();
void func_80031144();
void func_80037C60();
void func_8003E058();
void func_8003EC9C();
void func_8003FAA8();
void func_8003FE1C();
void func_80040330();
void func_80040B8C();
void func_800411C4();
void func_80041280();
void func_8004CBF4();
void func_8006737C();
void func_80067624();
void func_80067688();
void func_800679B0();
void func_80067A84();
void func_80067ABC();
void func_80067BB4();
void func_80067C98();
void func_80068354();
void func_800686E4();
void func_8006876C();
void func_80068854();
void func_80068914();
u32 func_80068E40();
void func_80068E64();
void func_80068E98();
void func_800693AC(void*, s32, s32, s32, f32, f32, f32);
void func_8006A1BC();
void func_8006A360();
void func_8006ABA0();
void func_8006ABEC();
void func_8006AD10();
void func_8006B82C();
void func_8006C0F0();
void func_8006C27C();
void func_8006C5F4();
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
void func_8006E9B4();
void func_8006EBA4();
void func_8006EBE8();
void func_8006F0FC();
void func_8006FE48();
void func_80070308();
void func_80070654();
void func_80070758();
void func_8007077C();
void func_80070E74();
void func_80070F28();
void func_80070FD0();
void func_80073240();
void func_80073354();
void func_8007349C();
void func_80073758();
void func_80074148();
void func_80074170();
void func_800743E0();
void func_800749CC();
void func_80074A8C();
void func_80074E58();
void func_8007500C();
void func_8007584C();
void func_8007592C();
void func_80075AF0();
void func_80075CB4();
void func_80076064();
void func_800764DC();
void func_80076528();
void func_800765AC();
void func_800765E0();
void func_80078754();
void func_80078A2C();
void func_80078C70();
void func_8007925C();
void func_8007AB48();
void func_8007AB80();
void func_8007AE80();
void func_8007AF28();
void func_8007AFF8();
void func_8007B0C0();
void func_8007B320();
void func_8007B4E0();
void func_8007B62C();
void func_8007B6EC();
void func_8007B760();
void func_8007B8CC();
void func_8007B8E8();
void func_8007B924();
void func_8007BA0C();
void func_8007BAC0();
void func_8007BBCC();
void func_8007BC90();
void func_8007BE3C();
void func_8007C114();
void func_8007C17C();
void func_8007C224();
void func_8007C4BC();
void func_8007C630();
void func_8007C6DC();
void func_8007C77C();
void func_8007CC78();
void func_8007CCA0();
void func_8007CD6C();
void func_8007CDA4();
void func_8007CDF8();
void func_8007CE4C();
void func_8007D5BC();
void func_8007D5D4();
void func_8007D6A4();
void func_8007D92C();
void func_8007DA74();
void func_8007DB24();
void func_8007DB58();
void func_8007E0E4();
void func_8007E2A4();
void func_8007E2FC();
void func_8007E83C();
void func_8007E994();
void func_8007EA90();
void func_8007EBAC();
void func_8007ECD4();
void func_8007ED50();
void func_8007EE0C();
void func_8007F578();
f32 func_8007F694(Fighter*); // ftcommon.s PlayerLoadModelScale
void func_8007F8E8();
void func_8007F9B4();
void func_8007FC7C();
void func_8007FF74();
void func_8007FFD8();
void func_8008021C();
void func_8008031C();
f32 func_800804EC(Fighter*); // DataOffset_PlayerScale_MultiplyBySomething, returns fighter->x40*fighter->x34
void func_800804FC();
void func_80080E18();
void func_80081938();
void func_800819A8();
void func_80081B38();
void func_80082A68();
void func_80084A40();
void func_800852B0();
void func_8008549C();
void func_8008572C();
void func_80085820();
void func_800859A8();
void func_80085B10();
void func_80085CD8();
void func_800867E8();
void func_800880D8();
void func_80088148();
void func_80088640();
void func_800887CC();
void func_80088884();
void func_800888E0();
void func_80088A50();
void func_80088C5C();
void func_800890BC();
void func_800890D0();
void func_800892D4();
void func_800895E0();
void func_80089B08(HSD_GObj* pPlayerEntityStruct);
void func_8008D930();
void func_8008E908();
void func_8008E984();
void func_8008E9D0();
void func_8008EB58();
void func_8008EC90();
void func_80090594();
void func_80090718();
void func_80095744();
void func_800964FC();
void func_800968C8();
void func_80098B20();
void func_80098C9C();
void func_80099D9C();
void func_8009CF84();
void func_8009E0A8();
void func_8009E0D4();
void func_8009E7B4();
void func_8009F4A4();
void func_8009F578();
void func_800A0DA4();
void func_800A101C();
void func_800A17E4();
void func_800A1874();
void func_800A1904();
void func_800A1948();
void func_800A198C();
void func_800A1994();
void func_800A1A24();
void func_800A2040();
void func_800B3900();
void func_800BFD04();
void func_800BFFAC();
void func_800BFFD0();
void func_800C0074();
void func_800C0134();
void func_800C0200();
void func_800C0408();
void func_800C0694();
void func_800C09B4();
void func_800C0A98();
void func_800C2FD8();
void func_800C37A0();
void func_800C511C();
void func_800C61B0();
void func_800C8064();
void func_800C8438();
void func_800C8540();
void func_800C884C();
void func_800C88A0();
void func_800C89A0();
void func_800C8A64();
void func_800C8B2C();
void func_800C8C84();
void func_800C8D00();
void func_800C8F6C();
void func_800C8FC4();
void func_800C9034();
void func_800CAE80();
void func_800D0FA0();
void func_800D105C();
void func_800D14E4();
void func_800D1A8C();
void func_800D1E80();
void func_800D237C();
void func_800D3158();
void func_800D67C4();
void func_800D688C();
void func_800D6928();
void func_800D71D8();
void func_800DEEA8();
void func_800DEF38();
void func_800DF0D0();
void func_800F1D24();
void func_800F5BA4();
void func_800F5C34();
void func_8014FE10();
void func_8014FE58();
void func_80155FCC();
void func_80156014();
void func_8016B0FC();
void func_8016B1C4();
void func_8016B41C();
void func_801A45E8();
void func_8026A8EC();
void func_8026ABD8();
void func_8026B300();
void func_8026B30C();
void func_8026B588();
void func_8026B594();
void func_8026B7F8();
void func_8027B4A4();
void func_802FB6E8();
void func_802FC998();
void func_80322258();
void cosf();
void sinf();
void func_80366BD4();
void func_80379310();
void func_8037A250();
void func_8038FD54();
void func_803901F0();
void func_80390A70();

void func_800679B0();
void func_80067A84();
void func_80067ABC();
void func_80067BB4(HSD_GObj* pPlayerEntity);
void func_80067BB4();
void func_80067C98();
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
void func_8006C0F0();
void func_8006C27C();
void func_8006C5F4(HSD_GObj* pPlayerEntityStruct/*r3*/);
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
