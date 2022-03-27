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




// Points to data in PiCo.dat
typedef struct _ftCommonData {
    u8 filler_x0[0x98];
    /* 0x98 */ f32 x98_shieldHealthInit;
    u8 filler_x9C[0x200-0x9C];
    /* 0x200 */ f32 x200;
    /* 0x204 */ f32 x204_knockbackFrameDecay;
    u8 filler_x208[0x21C-0x208];
    /* 0x21C */ f32 x21C;
    u8 filler_x220[0x260-0x220];
    /* 0x260 */ f32 x260;
    u8 filler_x264[0x294-0x264];
    /* 0x294 */ f32 x294;
    u8 filler_0x3E8[0x3E8-0x298];
    /* 0x3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
    /* 0x3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
    u8 filler_x3F0[0x480-0x3F0];
    /* 0x480 */ f32 x480;
    u8 filler_x484[0x498-0x484];
    /* 0x498 */ u32 x498_ledgeCooldownTime;
    u8 filler_x49C[0x5F0-0x49C];
    /* 0x5F0 */  u32 x5F0;
    u8 filler_x5F4[0x6D8-0x5F4];
   /* 0x6D8 */ void* x6D8[1]; // TODO expand to actual size
    u8 filler_x6DC[0x768-0x6DC];
    /* 0x768 */ f32 x768;
    /* 0x76C */ f32 x76C;
    /* 0x770 */ f32 x770;
    /* 0x774 */ s32 x774;
                u8 x780_filler[0x7E4 - 0x778];
    /* 0x7E4 */ f32 x7E4;
    // lots of more data following, exact size to be determined
} ftCommonData;

typedef struct _FtCollisionData
{
    u8 data_filler_0[0x28];
    u32 x28;
    u8 data_filler_2C[0x34 - 0x2C];
    s32 x34;
} FtCollisionData;

typedef struct _ftData
{
    struct {
        u8 x0_fill[0xFC];
        f32 xFC;
        u8 x100_fill[0x16C - 0x100];
        s32 x16C_idx;
    }* x0;
    /* 0x04 */ void* ext_attr;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 filler_x14[13];
    /* 0x48 */ void* x48_items;
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
    u8 filler_xBC[0x134 - 0xBC - 8];
    /* 0x134 */ s32 x134_envFlags;
    u8 filler_x138[0x14C - 0x138];
    /* 0x14C */ s32 x14C_groundIndex;
    s32 filler_x150;
    /* 0x154 */ Vec3 x154_groundNormal; // points out of the ground surface
    /* 0x160 */ s32 x160_rightwall_index;
    u8 filler_x160[0x174 - 0x160 - 4];
    /* 0x174 */ s32 x174_leftwall_index;
    u8 filler_x174[0x1A0 - 0x174 - 8];
    s32 x1A0;
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



typedef struct _Fighter {
    /* 0x0 */ HSD_GObj *x0_fighter;
    /* 0x4 */ FighterKind x4_fighterKind;
    /* 0x8 */ s32 x8_spawnNum;
    /* 0xC */ u8 xC_playerID;
    u8 xD;
    u8 xE;
    u8 xF;
    s32 x10;
    s32 x14;
    s32 x18;
    s32* x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    /* 0x2C */ f32 x2C_facing_direction;
    /* 0x30 */ f32 x30_facingDirectionRepeated;
    /* 0x34 */ Vec3 x34_scale;
    f32 x40;
    u8 filler_x40[0x74 - 0x44];

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
    f32 x100;
 
    s32 filler_x104;
    /* 0x108 */ void* x108_costume_archive;
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
        /* 0x224 */ s32 x224;
        /* 0x228 */ s32 x228;
        /* 0x22C */ s32 x22C;
        /* 0x230 */ s32 x230;
        /* 0x234 */ s32 x234;
        /* 0x238 */ s32 x238;
        /* 0x23C */ s32 x23C;
        /* 0x240 */ s32 x240;
        /* 0x244 */ s32 x244;
        /* 0x248 */ s32 x248;
        /* 0x24C */ s32 x24C;
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
        /* 0x280 */ s32 x280;
        /* 0x284 */ s32 x284;
        /* 0x288 */ s32 x288;
        /* 0x28C */ s32 x28C;
        /* 0x290 */ s32 x290_WeightDependentThrowSpeedFlags;
    } x110_attr;
    u8 filler_x294[0x2CC - 0x294];
    /* 0x2CC */ s32 x2CC;
    /* 0x2D0 */ s32 x2D0;
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
                f32 x2DC;
                f32 x2E0;
                f32 x2E4;
                f32 x2E8;

                f32 x2EC;
    u8 filler_x2D8[0x594 - 0x2F0];
    /* 0x594 */ s32 x594_animCurrFlags1;
    u8 filler_x595[0x5E8 - 0x598];
    /* 0x5E8 */ FighterBone* x5E8_fighterBones;
    u8 filler_x5EC[0x5F8 - 0x5EC];
    /* 0x5F8 */ s8 x5F8;
    u8 filler_x5FC[0x60C - 0x5F9];
    /* 0x60C */ void* x60C;
    u8 filler_x610[0x618 - 0x610];
    /* 0x618 */ s8 x618_player_id;
    /* 0x619 */ u8 x619_costume_id;
    /* 0x61A */ u8 x61A_controller_index;
    /* 0x61B */ u8 x61B_team;
    /* 0x61C */ u8 x61C;
    /* 0x61D */ u8 x61D;
    u8 filler_x61E[0x620 - 0x61E];
    /* 0x620 */ f32 x620_lstick_x;
                f32 x624_lstick_y;
                f32 x628_lstick_z;
                f32 x62C;

                f32 x630;
                f32 x634;

                f32 x638;
                f32 x63C;
                f32 x640;
                f32 x644;
                
                f32 x648;
                f32 x64C;
                
                f32 x650;
                f32 x654;

                f32 x658;

                s32 x65C;
                s32 x660;
                s32 x664;
                s32 x668;
                s32 x66C;

                u8 x670_timer_lstick_tilt_x;
                u8 x671_timer_lstick_tilt_y;
                u8 x672_timer_lstick_tilt_z;

                u8 x673_x;
                u8 x674_y;
                u8 x675_z;

                u8 x676_x;
                u8 x677_y;
                u8 x678_z;

                u8 x679_x;
                u8 x67A_y;
                u8 x67B_z;

                u8 x67C;
                u8 x67D;
                u8 x67E;
                u8 x67F;
                u8 x680;
                u8 x681;
                u8 x682;
                u8 x683;
                u8 x684;
                u8 x685;
                u8 x686;
                u8 x687;
                u8 x688;
                u8 x689;
                u8 x68A;
                u8 x68B;

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
    /* 0x890 */ CameraBox* x890;
    /* 0x894 */ f32 x894;
    /* 0x898 */ f32 x898;
    /* 0x89C */ f32 x89C;
    /* 0x8A0 */ f32 x8A0;
    s32 filler_x8A4[2];
    /* 0x8AC */ s32 x8AC_animSkeleton;
    u8 filler_x8AC[0x914 - 0x8B0];
    /* 0x914 */ Hitbox x914[4];
    u8 filler_xDF4[0x1064 - 0xDF4];
    /* 0x1064 */ ftHit x1064_thrownHitbox;
    u8 filler_x1064[0x1828 - 0x1064 - sizeof(ftHit)];
    /* 0x1828 */ s32 x1828;
    struct dmg                                                 // 0x182c
    {                                                          //
        s32 x182c_behavior;                                    // 0x182c
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
        f32 x189C;                                             // 0x189c
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
        s32 x192c;                                             // 0x192c
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
    /* 0x1974 */ void* x1974_heldItem;
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
    /* 0x19A4 */ void* x19A4;
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
    u8 filler_x1A4C[0x1A52 - 0x1A4C];
    /* 0x1A52 */ s8 x1A52;
    /* 0x1A53 */ s8 x1A53;
    s32 filler_x1A54;
                 HSD_GObj* x1A58;
                 HSD_GObj* x1A5C;
                 s32 x1A60;
                 s32 x1A64;
                 s32 x1A68;
                 f32 x1A6C;
                 Vec x1A70;
    u8 filler_x1A6C[0x2008-0x1A7C];
                 s32 x2008;
                 s32 x200C;
                 s32 x2010;
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
    /* 0x209A */ u16 x209A;
    /* 0x209C */ s16 x209C;
    /* 0x20A0 */ s32 x20A0;
    /* 0x20A4 */ s32 x20A4;
    /* 0x20A8 */ s32 x20A8;
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
    /* 0x2184 */ s32 x2184;
    /* 0x2188 */ S32Pair x2188;
    // callback struct. Not all of them used by fighter.c, but I'm leaving them in for now.
    struct cb {
        void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj *fighter); // used
        void (*x2194_callback_x2194)(HSD_GObj *fighter); // used
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
        void (*x21CC_callback_x21cc)(HSD_GObj *fighter);
        void (*x21D0_callback_EveryHitlag)(HSD_GObj *fighter); // xused
        void (*x21D4_callback_EnterHitlag)(HSD_GObj *fighter);
        void (*x21D8_callback_ExitHitlag)(HSD_GObj *fighter);
        void (*x21DC_callback_OnTakeDamage)(HSD_GObj *fighter);
        void (*x21E0_callback_OnDeath)(HSD_GObj *fighter); // used
        void (*x21E4_callback_OnDeath2)(HSD_GObj *fighter); // used. internally Dead_Proc as evidenced by 800f5430
        void (*x21E8_callback_OnDeath3)(HSD_GObj *fighter); // used
        void (*x21EC_callback)(HSD_GObj *fighter);
    } cb;
    u8 filler_x21EC[0x21FC - 0x21F0];
    u8 x21FC;
    u8 filler_x21FC[0x2200 - 0x21FD];
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
    /* 0x2354 */ f32 x2354_stateVar6;
    /* 0x2358 */ f32 x2358_stateVar7;
} Fighter;

///// 
typedef struct {
    HSD_Joint* joint;
    u8 padding[20];
} UnkFighterJointStruct;

struct Pair_Pointer_and_Flag {
    UnkFighterJointStruct* unk_fighter_struct;
    u8 flag;
};

struct S_TEMP1 {
    FighterKind fighterKind;
    u8 playerID;
    u8 unk5;
    UnkFlagStruct unk6;
};



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
HSD_GObj* func_80068E98(struct S_TEMP1* input);
void func_800693AC(HSD_GObj*, s32, s32, s32, f32, f32, f32);
void func_8006A1BC();
void func_8006A360();
void func_8006ABA0();
void func_8006ABEC();
void func_8006AD10();
void Fighter_procUpdate();
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
