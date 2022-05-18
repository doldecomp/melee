#ifndef _fighter_h_
#define _fighter_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <functions.h>
#include <melee/pl/player.h>
#include <melee/gr/stage.h>
#include <math.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>
#include "sysdolphin/baselib/controller.h"

typedef Vec Vec3;

typedef enum FighterKind
{
    FTKIND_MARIO,
    FTKIND_FOX,
    FTKIND_FALCON,
    FTKIND_DK,
    FTKIND_KIRBY,
    FTKIND_BOWSER,
    FTKIND_LINK,
    FTKIND_SHEIK,
    FTKIND_NESS,
    FTKIND_PEACH,
    FTKIND_POPO,
    FTKIND_NANA,
    FTKIND_PIKACHU,
    FTKIND_SAMUS,
    FTKIND_YOSHI,
    FTKIND_JIGGLYPUFF,
    FTKIND_MEWTWO,
    FTKIND_LUIGI,
    FTKIND_MARTH,
    FTKIND_ZELDA,
    FTKIND_YOUNGLINK,
    FTKIND_DRMARIO,
    FTKIND_FALCO,
    FTKIND_PICHU,
    FTKIND_GAW,
    FTKIND_GANONDORF,
    FTKIND_ROY,
    FTKIND_MASTERHAND,
    FTKIND_CRAZYHAND,
    FTKIND_BOY,
    FTKIND_GIRL,
    FTKIND_GIGABOWSER,
    FTKIND_SANDBAG,
} FighterKind;

typedef enum CharacterKind
{
    CKIND_FALCON,
    CKIND_DK,
    CKIND_FOX,
    CKIND_GAW,
    CKIND_KIRBY,
    CKIND_BOWSER,
    CKIND_LINK,
    CKIND_LUIGI,
    CKIND_MARIO,
    CKIND_MARTH,
    CKIND_MEWTWO,
    CKIND_NESS,
    CKIND_PEACH,
    CKIND_PIKACHU,
    CKIND_ICECLIMBERS,
    CKIND_JIGGLYPUFF,
    CKIND_SAMUS,
    CKIND_YOSHI,
    CKIND_ZELDA,
    CKIND_SHEIK,
    CKIND_FALCO,
    CKIND_YOUNGLINK,
    CKIND_DRMARIO,
    CKIND_ROY,
    CKIND_PICHU,
    CKIND_GANONDORF,
    CKIND_MASTERHAND,
    CKIND_BOY,
    CKIND_GIRL,
    CKIND_GIGABOWSER,
    CKIND_CRAZYHAND,
    CKIND_SANDBAG,
    CKIND_POPO,
} CharacterKind;


struct RGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

// Points to data in PiCo.dat
typedef struct _ftCommonData {
    /* 0x0 */ f32 x0;
    /* 0x4 */ f32 x4;
    /* 0x8 */ f32 x8_someStickThreshold;
    /* 0xC */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    u8 filler_x4[0x88 - 0x1C];
    /* 0x88 */ f32 x88;
    /* 0x8C */ s32 x8C;
    u8 filler_x90[0x98 - 0x90];
    /* 0x98 */ f32 x98_shieldHealthInit;
    u8 filler_x9C[0xEC-0x9C];
    /* 0xEC */ f32 xEC;
    /* 0xF0 */ f32 xF0;
    u8 filler_xF4[0x134-0xF4];
    /* 0x134 */ s32 x134;
    /* 0x138 */ f32 x138;
    /* 0x13C */ f32 x13C;
    u8 filler_x140[0x164-0x140];
    /* 0x164 */ f32 x164;
    u8 filler_x168[0x194-0x168];
    /* 0x194 */ f32 x194_unkHitLagFrames;
    /* 0x198 */ f32 x198;
    /* 0x19C */ f32 x19C;
    /* 0x1A0 */ f32 x1A0;
    u8 filler_x1A4[0x1FC-0x1A4];
    /* 0x1FC */ f32 x1FC;
    /* 0x200 */ f32 x200;
    /* 0x204 */ f32 x204_knockbackFrameDecay;
    u8 filler_x208[0x21C-0x208];
    /* 0x21C */ f32 x21C;
    u8 filler_x220[0x260-0x220];
    /* 0x260 */ f32 x260_startShieldHealth;
    u8 filler_x264[0x27C-0x264];
    /* 0x27C */ f32 x27C;
    /* 0x280 */ f32 x280_unkShieldHealth;
    /* 0x284 */ f32 x284;
    /* 0x288 */ f32 x288;
    u8 filler_x28C[0x294-0x28C];
    /* 0x294 */ f32 x294;
    u8 filler_x298[0x2DC-0x298];
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    u8 filler_x2E4[0x308-0x2E4];
    /* 0x308 */ f32 x308;
    u8 filler_x30C[0x3A8-0x30C];
    /* 0x3A8 */ f32 x3A8;
    u8 filler_x3AC[0x3E0-0x3AC];
    /* 0x3E0 */ f32 x3E0;
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
    /* 0x3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
    u8 filler_x3F0[0x418-0x3F0];
    /* 0x418 */ s32 x418;
    /* 0x41C */ s32 x41C;
    u8 filler_x420[0x454-0x420];
    /* 0x454 */ f32 x454;
    /* 0x458 */ f32 x458;
    /* 0x45C */ f32 x45C;
    /* 0x460 */ f32 x460;
    u8 filler_x464[0x480-0x464];
    /* 0x480 */ f32 x480;
    u8 filler_x484[0x498-0x484];
    /* 0x498 */ u32 x498_ledgeCooldownTime;
    u8 filler_x49C[0x4CC-0x49C];
    /* 0x4CC */ s32 x4CC;
    u8 filler_x4D0[0x5C0-0x4D0];
    /* 0x5F0 */ f32 x5C0;
    u8 filler_x5C4[0x5F0-0x5C4];
    /* 0x5F0 */  u32 x5F0;
    u8 filler_x5F4[0x6D8-0x5F4];
   /* 0x6D8 */ void* x6D8[1]; // TODO expand to actual size
    struct RGBA x6DC_colorsByPlayer[4];
    u8 filler_x6EC[0x6F4 - 0x6EC];
    /* 0x6F4 */ s32 x6F4_unkDamage;
    /* 0x6F8 */ s32 x6F8;
    /* 0x6FC */ s32 x6FC;
    /* 0x700 */ s32 x700;
    /* 0x704 */ f32 x704;
    /* 0x708 */ f32 x708;
    /* 0x70C */ f32 x70C;
    /* 0x710 */ f32 x710;
    u8 filler_x714[0x768-0x714];
    /* 0x768 */ f32 x768;
    /* 0x76C */ f32 x76C;
    /* 0x770 */ f32 x770;
    /* 0x774 */ s32 x774;
    u8 x7A0_filler[0x7A0 - 0x778];
    /* 0x7A0 */ s32 x7A0;
    /* 0x7A4 */ s32 x7A4;
    /* 0x7A8 */ s32 x7A8;
    /* 0x7AC */ s32 x7AC;
    /* 0x7B0 */ s32 x7B0;
    /* 0x7B4 */ s32 x7B4_unkDamage;
    /* 0x7B8 */ f32 x7B8;
    /* 0x7BC */ f32 x7BC;
    /* 0x7C0 */ f32 x7C0;
    /* 0x7C4 */ s32 x7C4;
    /* 0x7C8 */ s32 x7C8;
    /* 0x7CC */ s32 x7CC;
    /* 0x7D0 */ s32 x7D0;
    /* 0x7D4 */ s32 x7D4;
    /* 0x7D8 */ s32 x7D8;
    /* 0x7DC */ s32 x7DC;

    /* 0x7E0 */ s32 x7E0;
    /* 0x7E4 */ f32 x7E4_scaleZ;
    u8 x7E8_filler[0x814 - 0x7E8];
    /* 0x814 */ s32 x814;
    // lots of more data following, exact size to be determined
} ftCommonData;

typedef struct _FtCollisionData
{
    u8 data_filler_0[0x28];
    u32 x28;
    u8 data_filler_2C[0x30 - 0x2C];
    s32 x30;
    s32 x34;
} FtCollisionData;

typedef struct _ftData
{
    struct {
        u8 x0_fill[0x8C];
        f32 x8C;
        u8 x90_fill[0xFC - 0x90];
        f32 xFC;
        u8 x100_fill[0x16C - 0x100];
        s32 x16C_idx;
    }* x0;
    /* 0x04 */ void* ext_attr;
    struct {
        u8 x0_fill[0x10];
        u8 unk10, unk11, unk12;
    }* x8;
    struct S_TEMP4* xC;
    u8* x10;
    s32 filler_x14[13];
    /* 0x48 */ void** x48_items;
    FtCollisionData* x4C_collisionData;
    s32 filler_x50[2];
    void* x58;
} ftData;

typedef struct _Vec2 { float x, y; } Vec2;

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
  /* 0x0 */ HSD_JObj* x0_jobj;
  /* 0x4 */ HSD_JObj* x4_jobj2; // used for interpolation
  u32 data_filler[2];
} FighterBone;


typedef struct _Hitbox {
    s32 x0;
    u8 filler[0x134];
} Hitbox;

typedef struct _CameraBox
{
  u32 data_filler[3];
  UnkFlagStruct xC_flag;
  u8 xD_fill[0x10 - 0xD];
  Vec3 x10; // might be Vec2?
  Vec3 x1C;
  u8 x10_fill[0x50 - 0x28];
  f32 x50;
} CameraBox;

typedef struct _CollData
{
    u8 filler_x0[0x40];
    /* 0x40 */ u32 x40;
    /* 0x44 */ u32 x44;
    u8 filler_x48[0xA8-0x48];
    /* 0xA8 */ f32 xA8;
    /* 0xAC */ f32 xAC;
    /* 0xB0 */ f32 xB0;
    /* 0xB4 */ Vec2 xB4_ecbCurrCorrect_right;
    /* 0xBC */ Vec2 xBC_ecbCurrCorrect_left;
    u8 filler_xBC[0x130 - 0xBC - 8];
    /* 0x130 */ u32 x130;
    /* 0x134 */ s32 x134_envFlags;
    u8 filler_x138[0x14C - 0x138];
    /* 0x14C */ s32 x14C_groundIndex;
    s32 filler_x150;
    /* 0x154 */ Vec3 x154_groundNormal; // points out of the ground surface
    /* 0x160 */ s32 x160_rightwall_index;
    /* 0x164 */ s32 x164;
    /* 0x168 */ Vec x168_vec;
    /* 0x174 */ s32 x174_leftwall_index;
    /* 0x178 */ s32 x178;
    /* 0x17C */ Vec x17C_vec;
    u32 filler_x188[2];
    /* 0x190 */ Vec x190;
    /* 0x19C */ s32 x19C;
} CollData;

typedef struct _ftHit
{
    u8 filler_x0[0x134];
    s32 x134;
} ftHit;

typedef struct _S32Pair {
    s32 x, y;
} S32Pair;

// Ground/air state for Fighter.xE0_ground_or_air
enum {
    GA_Ground = 0,
    GA_Air = 1,
};

typedef struct {
    HSD_Joint* joint;
    u8 padding[20];
} UnkCostumeStruct;

struct UnkCostumeList {
    UnkCostumeStruct* costume_list;
    u8 numCostumes;
};


struct S_TEMP1 {
    FighterKind fighterKind;
    u8 playerID;
    u8 unk5;
    UnkFlagStruct flags;
};

struct ActionState {
    s32 action_id; 

    s32 x4_flags;

    u8 move_id;
    UnkFlagStruct x9_flags;
    UnkFlagStruct flagsA;
    UnkFlagStruct flagsB;

    void* cb_Anim;
    void* cb_Input;
    void* cb_Physics;
    void* cb_Collision;
    void* cb_Camera;
};

struct S_TEMP4 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10_animCurrFlags;
    s32 x14;
};

// --------------------------------------------------------------------------------
// UNION DEFS FOR FIGHTER STRUCTS. TODO: Maybe move these to per-fighter
// header includes or something.
// --------------------------------------------------------------------------------
struct SpecialAttrs_Mario {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ HSD_GObj* x223C;
    /* 0x2240 */ u32 x2240;
};

struct SpecialAttrs_Fox {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_Captain {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
};

struct SpecialAttrs_DK {
    char filler0[0x100];
};

struct SpecialAttrs_Kirby {
    char filler0[0x100];
};

struct SpecialAttrs_Koopa {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_Link {
    char filler0[0x100];
};

struct SpecialAttrs_Seak {
    char filler0[0x100];
};

struct SpecialAttrs_Ness {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u32 x224C;
};

struct SpecialAttrs_Peach {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
};

struct SpecialAttrs_Popo {
    char filler0[0x100];
};

struct SpecialAttrs_Nana {
    char filler0[0x100];
};

struct SpecialAttrs_Pikachu {
    char filler0[0x100];
};

struct SpecialAttrs_Samus {
    char filler0[0x100];
};

struct SpecialAttrs_Yoshi {
    char filler0[0x100];
};

struct SpecialAttrs_Purin {
    char filler0[0x100];
};

struct SpecialAttrs_Mewtwo {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
};

struct SpecialAttrs_Luigi {
    char filler0[0x100];
};

struct SpecialAttrs_Mars {
    /* 0x222C */ u32 x222C;
};

struct SpecialAttrs_Zelda {
    char filler0[0x100];
};

struct SpecialAttrs_CLink {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
};

struct SpecialAttrs_Pichu {
    char filler0[0x100];
};

struct SpecialAttrs_Gaw {
    char filler0[0x100];
};

struct SpecialAttrs_Masterhand {
    /* 0x222C */ HSD_GObj* x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ f32 x2238;
    /* 0x223C */ f32 x223C;
    /* 0x2240 */ Vec3 x2240_pos;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ s32 x2250;
    /* 0x2254 */ s32 x2254;
    /* 0x2258 */ s32 x2258;
};

struct SpecialAttrs_Crazyhand {
    char filler0[0x100];
};

struct SpecialAttrs_Boy {
    char filler0[0x100];
};

struct SpecialAttrs_Girl {
    char filler0[0x100];
};

struct SpecialAttrs_GKoopa {
    char filler0[0x100];
};

struct SpecialAttrs_Sandbag {
    char filler0[0x100];
};

typedef struct _Fighter {
    /* 0x0 */ HSD_GObj *x0_fighter;
    /* 0x4 */ FighterKind x4_fighterKind;
    /* 0x8 */ s32 x8_spawnNum;
    /* 0xC */ u8 xC_playerID;
    /* 0x10 */ s32 x10_action_state_index;
    /* 0x14 */ s32 x14_action_id;
    /* 0x18 */ s32 x18;
    /* 0x1C */ struct ActionState* x1C_actionStateList;
    /* 0x20 */ struct ActionState* x20_actionStateList;
    /* 0x24 */ struct S_TEMP4* x24;
    /* 0x28 */ u8* x28;
    /* 0x2C */ f32 x2C_facing_direction;
    /* 0x30 */ f32 x30_facingDirectionRepeated;
    /* 0x34 */ Vec3 x34_scale;
    /* 0x40 */ f32 x40;
    /* 0x44 */ Mtx x44_mtx;
    Vec3 x74_anim_vel;                                         // 0x74
    Vec3 x80_self_vel;                                         // 0x80
    Vec3 x8c_kb_vel;                                           // 0x8C
    Vec3 x98_atk_shield_kb;                                // 0x98
    Vec3 xA4_unk_vel;                                      // 0xA4
    Vec3 xB0_pos;                                          // 0xb0
    Vec3 xBC_prevPos;                                     // 0xBC
    Vec3 xC8_pos_delta;                                        // 0xC8
    Vec3 xD4_unk_vel;                                        // 0xD4
    s32 xE0_ground_or_air;                                         // 0xE0
    f32 xE4_ground_accel_1; // 0xE4
    f32 xE8_ground_accel_2;   // 0xE8
    f32 xEC_ground_vel;                                    // 0xEC
    f32 xF0_ground_kb_vel;
    f32 xF4_ground_attacker_shield_kb_vel;
    Vec2 xF8_playerNudgeVel;
    /* 0x100 */ f32 x100;
    /* 0x104 */ u8 x104;
    /* 0x105 */ s8 x105;
    /* 0x106 */ s8 x106;
    /* 0x107 */ s8 x107;
    /* 0x108 */ HSD_Joint* x108_costume_joint;
    /* 0x10C */ ftData* x10C_ftData;
    // TODO: Ask Psi how many of those are confirmed, only a fraction of them is used right now
    struct attr
    {
        /* 0x110 */ f32 x110_WalkInitialVelocity;
        /* 0x114 */ f32 x114_WalkAcceleration;
        /* 0x118 */ f32 x118_WalkMaximumVelocity;
        /* 0x11C */ f32 x11C_SlowWalkMax;
        /* 0x120 */ f32 x120_MidWalkPoint;
        /* 0x124 */ f32 x124_FastWalkMin;
        /* 0x128 */ f32 x128_GroundFriction; // used
        /* 0x12C */ f32 x12C_DashInitialVelocity;
        /* 0x130 */ f32 x130_DashrunAccelerationA;
        /* 0x134 */ f32 x134_DashrunAccelerationB;
        /* 0x138 */ f32 x138_DashrunTerminalVelocity;
        /* 0x13C */ f32 x13C_RunAnimationScaling;
        /* 0x140 */ f32 x140_MaxRunbrakeFrames;
        /* 0x144 */ f32 x144_GroundedMaxHorizontalVelocity;
        /* 0x148 */ f32 x148_JumpStartupTime;
        /* 0x14C */ f32 x14C_JumpHInitialVelocity;
        /* 0x150 */ f32 x150_JumpVInitialVelocity;
        /* 0x154 */ f32 x154_GroundToAirJumpMomentumMultiplier;
        /* 0x158 */ f32 x158_JumpHMaxVelocity;
        /* 0x15C */ f32 x15C_HopVInitialVelocity;
        /* 0x160 */ f32 x160_AirJumpVMultiplier;
        /* 0x164 */ f32 x164_AirJumpHMultiplier;
        /* 0x168 */ s32 x168_MaxJumps;
        /* 0x16C */ f32 x16C_Gravity;
        /* 0x170 */ f32 x170_TerminalVelocity;
        /* 0x174 */ f32 x174_AerialDriftStickMult;
        /* 0x178 */ f32 x178_AerialDriftBase;
        /* 0x17C */ f32 x17C_AerialDriftMax;
        /* 0x180 */ f32 x180_AerialFriction;
        /* 0x184 */ f32 x184_FastfallVelocity;
        /* 0x188 */ f32 x188_HorizontalAirMobilityConstant;
        /* 0x18C */ s32 x18C_Jab_2InputWindow;
        /* 0x190 */ s32 x190_Jab_3InputWindow;
        /* 0x194 */ s32 x194_FramesToChangeDirectionOnStandingTurn;
        /* 0x198 */ f32 x198_Weight;
        /* 0x19C */ f32 x19C_ModelScaling;
        /* 0x1A0 */ f32 x1A0_InitialShieldSize;
        /* 0x1A4 */ f32 x1A4_ShieldBreakInitialVelocity;
        /* 0x1A8 */ s32 x1A8_RapidJabWindow;
        /* 0x1AC */ s32 x1AC;
        /* 0x1B0 */ s32 x1B0;
        /* 0x1B4 */ s32 x1B4;
        /* 0x1B8 */ f32 x1B8_LedgeJumpHorizontalVelocity;
        /* 0x1BC */ f32 x1BC_LedgeJumpVerticalVelocity;
        /* 0x1C0 */ f32 x1C0_ItemThrowVelocityMultiplier;
        /* 0x1C4 */ s32 x1C4;
        /* 0x1C8 */ s32 x1C8;
        /* 0x1CC */ s32 x1CC;
        /* 0x1D0 */ s32 x1D0;
        /* 0x1D4 */ s32 x1D4;
        /* 0x1D8 */ s32 x1D8;
        /* 0x1DC */ s32 x1DC;
        /* 0x1E0 */ s32 x1E0;
        /* 0x1E4 */ s32 x1E4;
        /* 0x1E8 */ s32 x1E8;
        /* 0x1EC */ s32 x1EC;
        /* 0x1F0 */ f32 x1F0_KirbyBStarDamage;
        /* 0x1F4 */ f32 x1F4_NormalLandingLag;
        /* 0x1F8 */ f32 x1F8_NAirLandingLag;
        /* 0x1FC */ f32 x1FC_FAirLandingLag;
        /* 0x200 */ f32 x200_BAirLandingLag;
        /* 0x204 */ f32 x204_UAirLandingLag;
        /* 0x208 */ f32 x208_DAirLandingLag;
        /* 0x20C */ f32 x20C_NametagHeight;
        /* 0x210 */ s32 x210;
        /* 0x214 */ f32 x214_WallJumpHorizontalVelocity;
        /* 0x218 */ f32 x218_WallJumpVerticalVelocity;
        /* 0x21C */ s32 x21C;
        /* 0x220 */ f32 x220_TrophyScale;
        /* 0x224 */ Vec3 x224;
        /* 0x230 */ Vec3 x230;
        /* 0x23C */ f32 x23C;
        /* 0x240 */ Vec3 x240;
        /* 0x24C */ f32 x24C;
        /* 0x250 */ s32 x250;
        /* 0x254 */ s32 x254;
        /* 0x258 */ f32 x258; // used
        /* 0x25C */ f32 x25C_BubbleRatio;
        /* 0x260 */ s32 x260;
        /* 0x264 */ s32 x264;
        /* 0x268 */ s32 x268;
        /* 0x26C */ s32 x26C;
        /* 0x270 */ f32 x270_RespawnPlatformScale;
        /* 0x274 */ s32 x274;
        /* 0x278 */ s32 x278;
        /* 0x27C */ s32 x27C_CameraZoomTargetBone;
        /* 0x280 */ Vec3 x280;
        /* 0x28C */ s32 x28C;
        /* 0x290 */ s32 x290_WeightDependentThrowSpeedFlags;
    } x110_attr;
    u8 filler_x294[0x2CC - 0x294];
    /* 0x2CC */ s32 x2CC;
    /* 0x2D0 */ s32 x2D0;
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    /* 0x2E4 */ f32 x2E4;
    /* 0x2E8 */ f32 x2E8;
    /* 0x2EC */ f32 x2EC;
    u8 filler_x2F0[0x3E4 - 0x2F0];
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8;
    /* 0x3EC */ s32 x3EC;
    /* 0x3F0 */ s32 x3F0;
    u8 filler_x3F4[0x588 - 0x3F4];
    /* 0x588 */ s32 x588;
    /* 0x58C */ s32 x58C;
    /* 0x590 */ s32 x590;
    /* 0x594 */ union {
                    struct {
                        UnkFlagStruct x594_animCurrFlags1;
                        struct {
                            u8 x0: 7;
                            u16 x7: 3;
                        } x596_bits;
                    };
                    s32 x594_s32;
                };
    /* 0x598 */ s32 x598;
    /* 0x59C */ void* x59C;
    /* 0x5A0 */ void* x5A0;
    u8 filler_x598[0x5E8 - 0x5A4];
    /* 0x5E8 */ FighterBone* x5E8_fighterBones;
    u8 filler_x5EC[0x5F0 - 0x5EC];
    /* 0x5F0 */ void* x5F0;
    /* 0x5F4 */ s32 x5F4;
    /* 0x5F8 */ s8 x5F8;
    u8 filler_x5FC[0x60C - 0x5F9];
    /* 0x60C */ void* x60C;
    /* 0x610 */ struct RGBA x610_color_rgba[2];
    /* 0x618 */ u8 x618_player_id;
    /* 0x619 */ u8 x619_costume_id;
    /* 0x61A */ u8 x61A_controller_index;
    /* 0x61B */ u8 x61B_team;
    /* 0x61C */ u8 x61C;
    /* 0x61D */ u8 x61D;
    u8 filler_x61E[0x620 - 0x61E];

    struct {
        /* 0x620 */ f32 x620_lstick_x;
        /* 0x624 */ f32 x624_lstick_y;
        /* 0x628 */ f32 x628_lstick_x2;
        /* 0x62C */ f32 x62C_lstick_y2;

        /* 0x630 */ f32 x630;
        /* 0x634 */ f32 x634;

        /* 0x638 */ f32 x638_lsubStick_x;
        /* 0x63C */ f32 x63C_lsubStick_y;
        /* 0x640 */ f32 x640_lsubStick_x2;
        /* 0x644 */ f32 x644_lsubStick_y2;
                    
        /* 0x648 */ f32 x648;
        /* 0x64C */ f32 x64C;
                    
        /* 0x650 */ f32 x650;
        /* 0x654 */ f32 x654;

        /* 0x658 */ f32 x658;

        /* 0x65C */ s32 x65C;
        /* 0x660 */ s32 x660;
        /* 0x664 */ s32 x664;
        /* 0x668 */ s32 x668;
        /* 0x66C */ s32 x66C;
    } input; // 0x620 to 0x670

    /* 0x670 */ u8 x670_timer_lstick_tilt_x;
    /* 0x671 */ u8 x671_timer_lstick_tilt_y;
    /* 0x672 */ u8 x672_input_timer_counter;

    /* 0x673 */ u8 x673;
    /* 0x674 */ u8 x674;
    /* 0x674 */ u8 x675;

    /* 0x676 */ u8 x676_x;
    /* 0x677 */ u8 x677_y;
    /* 0x678 */ u8 x678;

    /* 0x679 */ u8 x679_x;
    /* 0x67A */ u8 x67A_y;
    /* 0x67B */ u8 x67B;

    /* 0x67C */ u8 x67C;
    /* 0x67D */ u8 x67D;
    /* 0x67E */ u8 x67E;
    /* 0x67F */ u8 x67F;
    /* 0x680 */ u8 x680;
    /* 0x681 */ u8 x681;
    /* 0x682 */ u8 x682;
    /* 0x683 */ u8 x683;
    /* 0x684 */ u8 x684;
    /* 0x685 */ u8 x685;
    /* 0x686 */ u8 x686;
    /* 0x687 */ u8 x687;
    /* 0x688 */ u8 x688;
    /* 0x689 */ u8 x689;
    /* 0x68A */ u8 x68A;
    /* 0x68B */ u8 x68B;

    /* 0x68C */ Vec x68C_transNPos;
    /* 0x698 */  Vec x698;
    /* 0x6A4 */  Vec3 x6A4_transNOffset;
    /* 0x6B0 */  Vec3 x6B0;
    /* 0x6BC */  f32 x6BC_inputStickangle;
    /* 0x6C0 */  Vec x6C0;
    /* 0x6CC */  Vec x6CC;
    /* 0x6D8 */  Vec3 x6D8;
    /* 0x6E4 */  Vec3 x6E4;
    /* 0x6F0 */ CollData x6F0_collData;
    /* 0x890 */ CameraBox* x890_cameraBox;
    /* 0x894 */ f32 x894;
    /* 0x898 */ f32 x898;
    /* 0x89C */ f32 x89C;
    /* 0x8A0 */ f32 x8A0;
    /* 0x8A4 */ f32 x8A4;
    /* 0x8A8 */ f32 x8A8;
    /* 0x8AC */ HSD_JObj* x8AC_animSkeleton;
    u8 filler_x8AC[0x914 - 0x8B0];
    /* 0x914 */ Hitbox x914[4];
    u8 filler_xDF4[0x1064 - 0xDF4];
    /* 0x1064 */ ftHit x1064_thrownHitbox;
    u8 filler_x1198[0x1828 - 0x119C];
    /* 0x1828 */ s32 x1828;
    struct dmg                                                 // 0x182c
    {                                                          //
        f32 x182c_behavior;                                    // 0x182c
        f32 x1830_percent;                                     // 0x1830
        f32 x1834;                                             // 0x1834
        f32 x1838_percentTemp;                                 // 0x1838
        s32 x183C_applied;                                     // 0x183c
        s32 x1840;                                             // 0x1840
        f32 x1844_direction;                                   // 0x1844
        s32 x1848_kb_angle;                                    // 0x1848
        s32 x184c_damaged_hurtbox;                             // 0x184c
        f32 x1850_forceApplied;                                // 0x1850
        Vec3 x1854_collpos;                                    // 0x1854
        s32 x1860_dealt;                                       // 0x1860
        s32 x1864;                                             // 0x1864
        HSD_GObj *x1868_source;                                // 0x1868
        s32 x186c;                                             // 0x186c
        s32 x1870;                                             // 0x1870
        s32 x1874;                                             // 0x1874
        s32 x1878;                                             // 0x1878
        s32 x187c;                                             // 0x187c
        s32 x1880;                                             // 0x1880
        s32 x1884;                                             // 0x1884
        s32 x1888;                                             // 0x1888
        s32 x188c;                                             // 0x188c
        s32 x1890;                                             // 0x1890
        s32 x1894;                                             // 0x1894
        s32 x1898;                                             // 0x1898
        f32 x189C_unk_num_frames;                                             // 0x189c
        f32 x18a0;                                             // 0x18a0
        f32 x18A4_knockbackMagnitude;                          // 0x18a4  kb magnitude
        f32 x18A8;                                             // 0x18a8
        s32 x18ac_time_since_hit;                              // 0x18ac   in frames
        f32 x18B0;                                             // 0x18b0
        f32 x18B4_armor;                                       // 0x18b4
        f32 x18B8;                                             // 0x18b8
        f32 x18BC;                                             // 0x18bc
        s32 x18C0;                                             // 0x18c0
        s32 x18c4_source_ply;                                  // 0x18c4   damage source ply number
        s32 x18C8;                                             // 0x18c8
        s32 x18CC;                                             // 0x18cc
        s32 x18D0;                                             // 0x18d0
        s32 x18d4;                                             // 0x18d4
        s32 x18d8;                                             // 0x18d8
        s32 x18dc;                                             // 0x18dc
        s32 x18e0;                                             // 0x18e0
        s32 x18e4;                                             // 0x18e4
        s32 x18e8;                                             // 0x18e8
        u16 x18ec_instancehitby;                               // 0x18ec. Last Move Instance This Player Was Hit by
        s32 x18F0;                                             // 0x18f0
        s32 x18F4;                                             // 0x18f4
        u8 x18F8;                                              // 0x18f8
        u8 x18f9;                                              // 0x18f9
        u16 x18fa_model_shift_frames;                          // 0x18fa
        u8 x18FC;                                              // 0x18fc
        u8 x18FD;                                              // 0x18fd
        s32 x1900;                                             // 0x1900
        s32 x1904;                                             // 0x1904
        s32 x1908;                                             // 0x1908
        s32 x190C;                                             // 0x190c
        s32 x1910;                                             // 0x1910
        s32 x1914;                                             // 0x1914
        s32 x1918;                                             // 0x1918
        f32 x191C;                                             // 0x191c
        s32 x1920;                                             // 0x1920
        s32 x1924;                                             // 0x1924
        f32 x1928;                                             // 0x1928
        f32 x192c;                                             // 0x192c
        s32 x1930;                                             // 0x1930
        s32 x1934;                                             // 0x1934
        s32 x1938;                                             // 0x1938
        s32 x193c;                                             // 0x193c
        s32 x1940;                                             // 0x1940
        s32 x1944;                                             // 0x1944
        s32 x1948;                                             // 0x1948
        s32 x194C;                                             // 0x194c
        s32 x1950;                                             // 0x1950
        f32 x1954;                                             // 0x1954
        f32 x1958;                                             // 0x1958
        f32 x195c_hitlag_frames;                               // 0x195c
    } dmg;    
    /* 0x1960 */ f32 x1960_vibrateMult;
    /* 0x1964 */ f32 x1964;
    /* 0x1968 */ u8 x1968_jumpsUsed;
    /* 0x1969 */ u8 x1969_walljumpUsed;
    /* 0x196C */ f32 x196C_hitlag_mult;
    /* 0x1970 */ s32 x1970;
    /* 0x1974 */ HSD_GObj* x1974_heldItem;
    /* 0x1978 */ HSD_GObj* x1978;
    /* 0x197C */ HSD_GObj* x197C;
    /* 0x1980 */ HSD_GObj* x1980;
    /* 0x1984 */ HSD_GObj* x1984_heldItemSpec;
    /* 0x1988 */ s32 x1988;
    /* 0x198C */ s32 x198C;
    /* 0x1990 */ s32 x1990;
    /* 0x1994 */ s32 x1994;
    /* 0x1998 */ f32 x1998_shieldHealth;
    /* 0x199C */ f32 x199C_shieldLightshieldAmt;
    /* 0x19A0 */ s32 x19A0_shieldDamageTaken;
    /* 0x19A4 */ s32 x19A4;
    /* 0x19A8 */ void* x19A8;
    /* 0x19AC */ f32 x19AC;
    s32 filler_x19B0;
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
    /* 0x1A4C */ f32 x1A4C;
    /* 0x1A50 */ s8 x1A50;
    /* 0x1A51 */ s8 x1A51;
    /* 0x1A52 */ u8 x1A52;
    /* 0x1A53 */ u8 x1A53;
    /* 0x1A54 */ s32 x1A54;
    /* 0x1A58 */ HSD_GObj* x1A58_interactedFighter;
    /* 0x1A5C */ HSD_GObj* x1A5C;
    /* 0x1A60 */ u32 x1A60;
    /* 0x1A64 */ s32 x1A64;
    /* 0x1A68 */ s16 x1A68;
    /* 0x1A6A */ s16 x1A6A;
    /* 0x1A6C */ f32 x1A6C;
    /* 0x1A70 */ Vec x1A70;
    /* 0x1A7C */ Vec x1A7C;
    u8 filler_x1A7C[0x1A98-0x1A88];
    /* 0x1A98 */ u32 x1A98;
    u8 filler_x1A9C[0x2004-0x1A9C];
    /* 0x2008 */ s32 x2004;
    /* 0x2008 */ s32 x2008;
    /* 0x200C */ s32 x200C;
    /* 0x2010 */ s32 x2010;
    /* 0x2014 */ s32 x2014;
    /* 0x2018 */ s32 x2018;
    /* 0x201C */ s32 x201C;
    /* 0x2020 */ s8 x2020;
    /* 0x2021 */ s8 x2021;
    /* 0x2022 */ s8 x2022;
    /* 0x2024 */ s32 x2024;
    /* 0x2028 */ s32 x2028;
    /* 0x202C */ s32 x202C;
    /* 0x2030 */ s32 x2030;
    /* 0x2034 */ s32 x2034;
    /* 0x2038 */ s32 x2038;
    /* 0x203C */ s32 x203C;
    /* 0x2040 */ void* x2040;
    u8 filler_x203C[0x2064 - 0x2044];
    /* 0x2064 */ s32 x2064_ledgeCooldown;
    u8 filler_x2068[0x2070 - 0x2068];
    /* 0x2068 */ union {
                    struct {
                        UnkFlagStruct x2070;
                        UnkFlagStruct x2071;
                        UnkFlagStruct x2072;
                        u8 x2073;
                    };
                    s32 x2070_int;
                };
    u8 filler_x2074[0x208C - 0x2074];
    /* 0x208C */ s32 x208C;
    /* 0x2090 */ s16 x2090;
    /* 0x2092 */ s16 x2092;
    /* 0x2094 */ s32 x2094;
    /* 0x2098 */ u16 x2098;
    /* 0x209A */ u16 x209A;
    /* 0x209C */ s16 x209C;
    /* 0x20A0 */ struct _HSD_JObj* x20A0_accessory;
    /* 0x20A4 */ s32 x20A4;
    /* 0x20A8 */ s32 x20A8;
    /* 0x20AC */ u32 x20AC;
    u8 filler_x20B0[0x2100 - 0x20B0];
    /* 0x2100 */ s8 x2100;
    /* 0x2101 */ u8 x2101_bits_0to6 : 7;
    /* 0x2101 */ u8 x2101_bits_8 : 1;
    /* 0x2102 */ s8 x2102;
    /* 0x2103 */ s8 x2103;
    /* 0x2104 */ s32 x2104;
    /* 0x2108 */ s32 x2108;
    /* 0x210C */ u8 x210C_walljumpInputTimer;
    u8 filler_x210C[3];
    /* 0x2110 */ f32 x2110_walljumpWallSide;
    /* 0x2114 */ s32 x2114;
    u8 filler_x2114[0x2135 - 0x2118];
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
    /* 0x2184 */ HSD_JObj* x2184;
    /* 0x2188 */ S32Pair x2188;
    // callback struct. Not all of them used by fighter.c, but I'm leaving them in for now.
    struct cb {
        void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter); // used
        void (*x2194_callback)(HSD_GObj *fighter); // used
        void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj*, HSD_GObj*); // used
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
        void (*x21CC_callback)(HSD_GObj *fighter);
        void (*x21D0_callback_EveryHitlag)(HSD_GObj *fighter); // xused
        void (*x21D4_callback_EnterHitlag)(HSD_GObj *fighter);
        void (*x21D8_callback_ExitHitlag)(HSD_GObj *fighter);
        void (*x21DC_callback_OnTakeDamage)(HSD_GObj *fighter);
        void (*x21E0_callback_OnDeath)(HSD_GObj *fighter); // used
        void (*x21E4_callback_OnDeath2)(HSD_GObj *fighter); // used. internally Dead_Proc as evidenced by 800f5430
        void (*x21E8_callback_OnDeath3)(HSD_GObj *fighter); // used
        void (*x21EC_callback)(HSD_GObj *fighter);
        void (*x21F0_callback)(HSD_GObj *fighter);
        void (*x21F4_callback)(HSD_GObj *fighter);
        void (*x21F8_callback)(HSD_GObj *fighter);
    } cb;
    /* 0x21FC */ u8 x21FC;
    u8 filler_x21FC[0x2200 - 0x21FD];
    /* 0x2200 */ u32 x2200_ftcmd_var0;
    /* 0x2204 */ u32 x2204_ftcmd_var1;
    /* 0x2208 */ u32 x2208_ftcmd_var2;
    /* 0x220C */ u32 x220C_ftcmd_var3;
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
                struct {
                    struct {
                        u8 b0 : 3;
                        u8 b3 : 1;
                        u8 b4 : 1;
                        u8 b5 : 1;
                        u8 b6 : 1;
                        u8 b7 : 1;
                    } bits;
                } x2220_flag;
    /* 0x2221 */ UnkFlagStruct x2221_flag;
    /* 0x2222 */ UnkFlagStruct x2222_flag;
    /* 0x2224 */ UnkFlagStruct x2223_flag;
    /* 0x2224 */ UnkFlagStruct x2224_flag;
    /* 0x2224 */ UnkFlagStruct x2225_flag;
    /* 0x2226 */ UnkFlagStruct x2226_flag;
    /* 0x2227 */ UnkFlagStruct x2227_flag;
    /* 0x2228 */ struct {  ///UnkFlagStruct does not quite work
                    struct {
                        u8 b0 : 1;
                        u8 b1 : 1;
                        u8 b2 : 1;
                        u8 b3 : 2;
                        u8 b5 : 1;
                        u8 b6 : 1;
                        u8 b7 : 1;
                    } bits;
                } x2228_flag;
                
    /* 0x2229 */ u8 x2229_b0 : 1;
                 u8 x2229_b1 : 1;
                 u8 x2229_b2 : 1;
                 u8 x2229_b3 : 1;
                 u8 x2229_b4 : 1;
                 u8 x2229_b5_no_normal_motion : 1;
                 u8 x2229_b6 : 1;
                 u8 x2229_b7 : 1;

                 
    /* 0x222A */ UnkFlagStruct x222A_flag;
    u8 filler_x222B;
    // Some of these are clones of each other (they just use another struct)
    // and some of them dont have specials so dont exist in the union. TODO: Clean-up
    union {
        struct SpecialAttrs_Mario mario;
        struct SpecialAttrs_Fox fox;
        struct SpecialAttrs_Captain captain;
        struct SpecialAttrs_DK dk;
        struct SpecialAttrs_Kirby kirby;
        struct SpecialAttrs_Koopa koopa;
        struct SpecialAttrs_Link link;
        struct SpecialAttrs_Seak seak;
        struct SpecialAttrs_Ness ness;
        struct SpecialAttrs_Peach peach;
        struct SpecialAttrs_Popo popo;
        struct SpecialAttrs_Nana nana;
        struct SpecialAttrs_Pikachu pikachu;
        struct SpecialAttrs_Samus samus;
        struct SpecialAttrs_Yoshi yoshi;
        struct SpecialAttrs_Purin purin;
        struct SpecialAttrs_Mewtwo mewtwo;
        struct SpecialAttrs_Luigi luigi;
        struct SpecialAttrs_Mars mars;
        struct SpecialAttrs_Zelda zelda;
        struct SpecialAttrs_CLink clink;
        // Mario SpecialAttrs struct is used for DrMario
        // Fox SpecialAttrs struct is used for Falco
        struct SpecialAttrs_Pichu pichu;
        struct SpecialAttrs_Gaw gaw;
        // Cpt Falcon SpecialAttrs struct is used for Ganondorf
        // Mars (Marth) struct is used for Emblem (Roy)
        struct SpecialAttrs_Masterhand masterhand;
        struct SpecialAttrs_Crazyhand crazyhand;
        struct SpecialAttrs_Boy boy;
        struct SpecialAttrs_Girl girl;
        struct SpecialAttrs_GKoopa gkoopa;
        struct SpecialAttrs_Sandbag sandbag;

    } sa;
    /* 0x232C */ s32 x232C;
    /* 0x2330 */ Vec2 x2330;
    /* 0x2338 */ Vec2 x2338;
    union {
    /* 0x2340 */ s32 x2340_stateVar1;
    /* 0x2340 */ f32 x2340_f32;
    };
    union {
    /* 0x2344 */ u32 x2344_stateVar2;
    /* 0x2344 */ s32 x2344_stateVar2_s32;
    /* 0x2344 */ void (*x2344_callback)(HSD_GObj*);
    /* 0x2344 */ f32 x2344_f32;
    };
    union {
        /* 0x2348 */ u32 x2348_stateVar3;
        /* 0x2348 */ s32 x2348_stateVar3_s32;
    };
    union {
        struct {
            /* 0x234C */ u32 x234C_stateVar4;
            /* 0x2350 */ u32 x2350_stateVar5;
            /* 0x2354 */ f32 x2354_stateVar6;
        };
        /* 0x234C */ Vec3 x234C_pos;
    };
    union {
        /* 0x2358 */ f32 x2358_stateVar7;
        /* 0x2358 */ s32 x2358_stateVar7_s32;

    };
    /* 0x235C */ f32 x235C;
    union {
        /* 0x2360 */ s32 x2360;
        /* 0x2360 */ f32 x2360_f32;
    };
    /* 0x2364 */ f32 x2364;
    /* 0x2368 */ u32 x2368;
    /* 0x236C */ u32 x236C;
    /* 0x2370 */ u32 x2370;
    /* 0x2374 */ u32 x2374;
    /* 0x2378 */ u32 x2378;
    /* 0x237C */ u32 x237C;
    /* 0x2380 */ u32 x2380;
    u8 filler_x2384[0x2390-0x2384];
    /* 0x2390 */ f32 x2390;
    /* 0x2394 */ s32 x2394;
    /* 0x2394 */ Vec3 x2398;
    /* 0x2394 */ Vec3 x23A4;
    /* 0x23B0 */ s32 x23B0;
    /* 0x23B4 */ s32 x23B4;
    /* 0x23B8 */ s32 x23B8;
} Fighter;


// functions in fighter.c
void Fighter_800679B0();
void Fighter_FirstInitialize_80067A84();
void Fighter_LoadCommonData();
void Fighter_UpdateModelScale(HSD_GObj* fighterObj);
void Fighter_UnkInitReset_80067C98(Fighter*);
void Fighter_UnkProcessDeath_80068354(HSD_GObj* fighterObj);
void Fighter_UnkUpdateCostumeJoint_800686E4(HSD_GObj* fighterObj);
void Fighter_UnkUpdateVecFromBones_8006876C(Fighter* fighter);
void Fighter_ResetInputData_80068854(HSD_GObj* fighterObj);
void Fighter_UnkInitLoad_80068914(HSD_GObj* fighterObj, struct S_TEMP1* argdata);
u32 Fighter_NewSpawn_80068E40();
void Fighter_80068E64(HSD_GObj* fighterObj);
HSD_GObj* Fighter_80068E98(struct S_TEMP1* input);
void Fighter_ActionStateChange_800693AC(HSD_GObj* fighterObj, s32 new_action_state_index, s32 arg2, HSD_GObj* otherObj, f32 arg8, f32 arg9, f32 argA);
void Fighter_8006A1BC(HSD_GObj* fighterObj);
void Fighter_8006A360(HSD_GObj* fighterObj);
void Fighter_8006ABA0(HSD_GObj* fighterObj);
void Fighter_UnkIncrementCounters_8006ABEC(HSD_GObj* fighterObj);
void Fighter_Spaghetti_8006AD10(HSD_GObj* fighterObj);
void Fighter_procUpdate(HSD_GObj* fighterObj, s32 dummy);
void Fighter_UnkApplyTransformation_8006C0F0(HSD_GObj* fighterObj);
void Fighter_8006C27C(HSD_GObj* fighterObj, s32 unused, s32 unused2, s32 unused3);
void Fighter_8006C5F4(HSD_GObj* fighterObj);
void Fighter_CallAcessoryCallbacks_8006C624(HSD_GObj* fighterObj);
void Fighter_8006C80C(HSD_GObj* fighterObj);
void Fighter_UnkProcessGrab_8006CA5C(HSD_GObj* fighterObj);
void Fighter_8006CB94(HSD_GObj* fighterObj);
void Fighter_UnkTakeDamage_8006CC30(Fighter* fighter, f32 damage_amount);
void Fighter_TakeDamage_8006CC7C(Fighter*, f32);
void Fighter_8006CDA4(Fighter* fighter, s32 arg1, s32 arg2, s32 arg3);
void Fighter_8006CF5C(Fighter* fighter, s32 arg1);
void Fighter_UnkSetFlag_8006CFBC(HSD_GObj* fighterObj);
void Fighter_8006CFE0(HSD_GObj* fighterObj);
void Fighter_UnkRecursiveFunc_8006D044(HSD_GObj* fighterObj);
void Fighter_8006D10C(HSD_GObj* fighterObj);
void Fighter_UnkProcessShieldHit_8006D1EC(HSD_GObj* fighterObj);
void Fighter_8006D9AC(HSD_GObj* fighterObj);
void Fighter_UnkCallCameraCallback_8006D9EC(HSD_GObj* fighterObj);
void Fighter_8006DA4C(HSD_GObj* fighterObj);
void Fighter_Unload_8006DABC(Fighter* fighter);

#endif
