#ifndef MELEE_FT_TYPES_H
#define MELEE_FT_TYPES_H

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ft/ftanim.h"
#include "ftCaptain/types.h"
#include "ftCommon/types.h"
#include "ftDonkey/types.h"
#include "ftFox/types.h"
#include "ftGameWatch/types.h"
#include "ftKirby/types.h"
#include "ftKoopa/types.h"
#include "ftLink/types.h"
#include "ftLuigi/types.h"
#include "ftMario/types.h"
#include "ftMars/types.h"
#include "ftMasterHand/types.h"
#include "ftMewtwo/types.h"
#include "ftNess/types.h"
#include "ftPeach/types.h"
#include "ftPikachu/types.h"
#include "ftPopo/types.h"
#include "ftPurin/types.h"
#include "ftSamus/types.h"
#include "ftSandbag/types.h"
#include "ftSeak/types.h"
#include "ftYoshi/types.h"
#include "ftZakoBoy/types.h"
#include "ftZelda/types.h"
#include "gr/stage.h"
#include "lb/lbcollision.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <common_structs.h>
#include <math.h>
#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>
#include <baselib/archive.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/random.h>

// Table in PlCo.dat
typedef struct _FighterPartsTable {
    u8* joint_to_part;
    u8* part_to_joint;
    u32 parts_num;
} FighterPartsTable;

// Points to data in PlCo.dat
typedef struct _ftCommonData {
    /* 0x0 */ f32 x0;
    /* 0x4 */ f32 x4;
    /* 0x8 */ f32 x8_someStickThreshold;
    /* 0xC */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ f32 x20;
    /* 0x24 */ f32 x24;
    /* 0x28 */ f32 x28;
    /* 0x2C */ f32 x2C;
    /* 0x30 */ f32 x30;
    u8 filler_x34[0x70 - 0x34];
    /* 0x70 */ f32 x70_someLStickYMax;
    u8 filler_x74[0x88 - 0x74];
    /* 0x88 */ f32 x88;
    /* 0x8C */ s32 x8C;
    u8 filler_x90[0x98 - 0x90];
    /* 0x98 */ f32 x98_shieldHealthInit;
    u8 filler_x9C[0xEC - 0x9C];
    /* 0xEC */ f32 xEC;
    /* 0xF0 */ f32 xF0;
    u8 filler_xF4[0x128 - 0xF4];
    /* 0x128 */ f32 x128;
    /* 0x12C */ f32 x12C;
    /* 0x130 */ f32 x130;
    /* 0x134 */ s32 x134;
    /* 0x138 */ f32 x138;
    /* 0x13C */ f32 x13C;
    u8 filler_x140[0x164 - 0x140];
    /* 0x164 */ f32 x164;
    u8 filler_x168[0x194 - 0x168];
    /* 0x194 */ f32 x194_unkHitLagFrames;
    /* 0x198 */ f32 x198;
    /* 0x19C */ f32 x19C;
    /* 0x1A0 */ f32 x1A0;
    u8 filler_x1A4[0x1FC - 0x1A4];
    /* 0x1FC */ f32 x1FC;
    /* 0x200 */ f32 x200;
    /* 0x204 */ f32 x204_knockbackFrameDecay;
    u8 filler_x208[0x21C - 0x208];
    /* 0x21C */ f32 x21C;
    u8 filler_x220[0x260 - 0x220];
    /* 0x260 */ f32 x260_startShieldHealth;
    u8 filler_x264[0x27C - 0x264];
    /* 0x27C */ f32 x27C;
    /* 0x280 */ f32 x280_unkShieldHealth;
    /* 0x284 */ f32 x284;
    /* 0x288 */ f32 x288;
    u8 filler_x28C[0x294 - 0x28C];
    /* 0x294 */ f32 x294;
    u8 filler_x298[0x2A4 - 0x298];
    /* 0x2A4 */ f32 x2A4;
    u8 filler_x2A8[0x2B4 - 0x2A8];
    /* 0x2B4 */ f32 x2B4;
    u8 filler_x2B8[0x2DC - 0x2B8];
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    u8 filler_x2E4[0x308 - 0x2E4];
    /* 0x308 */ f32 x308;
    u8 filler_x30C[0x3A8 - 0x30C];
    /* 0x3A8 */ f32 x3A8;
    u8 filler_x3AC[0x3E0 - 0x3AC];
    /* 0x3E0 */ f32 x3E0;
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
    /* 0x3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
    u8 filler_x3F0[0x418 - 0x3F0];
    /* 0x418 */ s32 x418;
    /* 0x41C */ s32 x41C;
    u8 filler_x420[0x440 - 0x420];
    /* 0x440 */ f32 x440;
    /* 0x444 */ f32 x444;
    /* 0x448 */ f32 x448;
    /* 0x44C */ f32 x44C;
    /* 0x450 */ f32 x450;
    /* 0x454 */ f32 x454;
    /* 0x458 */ f32 x458;
    /* 0x45C */ f32 x45C;
    /* 0x460 */ f32 x460;
    u8 filler_x464[0x480 - 0x464];
    /* 0x480 */ f32 x480;
    u8 filler_x484[0x498 - 0x484];
    /* 0x498 */ u32 x498_ledgeCooldownTime;
    u8 filler_x49C[0x4C4 - 0x49C];
    s32 x4C4;
    s32 x4C8;
    s32 x4CC;
    f32 x4D0;
    f32 x4D4;
    u32 x4D8;
    u8 filler_x4D0[0x5C0 - 0x4DC];
    /* 0x5F0 */ f32 x5C0;
    u8 filler_x5C4[0x5F0 - 0x5C4];
    /* 0x5F0 */ u32 x5F0;
    u8 filler_x5F4[0x6D8 - 0x5F4];
    /* 0x6D8 */ void* x6D8[1]; // TODO expand to actual size
    GXColor x6DC_colorsByPlayer[4];
    u8 filler_x6EC[0x6F4 - 0x6EC];
    /* 0x6F4 */ s32 x6F4_unkDamage;
    /* 0x6F8 */ s32 x6F8;
    /* 0x6FC */ s32 x6FC;
    /* 0x700 */ s32 x700;
    /* 0x704 */ f32 x704;
    /* 0x708 */ f32 x708;
    /* 0x70C */ f32 x70C;
    /* 0x710 */ f32 x710;
    /* 0x714 */ f32 x714;
    u8 filler_x718[0x768 - 0x718];
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

typedef struct _FtCollisionData {
    u8 x0[0x28];
    u32 x28;
    u8 x2C[0x30 - 0x2C];
    s32 x30;
    s32 x34;
} FtCollisionData;

typedef struct _DObjList {
    usize_t count;
    HSD_DObj** data;
} DObjList;

struct UnkFloat6_Camera;

typedef struct _ftData {
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
    s32 filler_x14[10];
    struct UnkFloat6_Camera* x3C;
    s32 filler_x40[2];
    /* 0x48 */ UNK_T* x48_items;
    FtCollisionData* x4C_collisionData;
    s32 filler_x50[2];
    void* x58;
} ftData;

typedef struct _ThrowFlags {
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

typedef struct attr {
    /* 0x110 */ f32 walk_init_vel;
    /* 0x114 */ f32 walk_accel;
    /* 0x118 */ f32 walk_max_vel;
    /* 0x11C */ f32 x11C_SlowWalkMax;
    /* 0x120 */ f32 x120_MidWalkPoint;
    /* 0x124 */ f32 x124_FastWalkMin;
    /* 0x128 */ f32 gr_friction; // used
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
    /* 0x18C */ f32 x18C_Jab_2InputWindow;
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
} attr;

typedef struct _FighterBone {
    /* 0x0 */ HSD_JObj* x0_jobj;
    /* 0x4 */ HSD_JObj* x4_jobj2; // used for interpolation
    /* 0x5 */ UnkFlagStruct flags;
    /* 0x6 */ u8 filler_x6[7];
} FighterBone;

typedef struct _CameraBox {
    u32 data_filler[2];
    s32 x8;
    UnkFlagStruct xC_flag;
    u8 xD_fill[0x10 - 0xD];
    Vec3 x10; // might be Vec2?
    Vec3 x1C;
    f32 x28;
    Vec2 x2C;
    Vec3 x34;
    Vec2 x40;
    Vec3 x48;
} CameraBox;

typedef struct _ftECB {
    Vec2 top;
    Vec2 bottom;
    Vec2 right;
    Vec2 left;
} ftECB;

typedef struct _ftCollisionBox {
    f32 top;
    f32 bottom;
    Vec2 left;
    Vec2 right;

} ftCollisionBox;

typedef struct _ECBFlagStruct {
    union {
        struct {
            u8 b0 : 1;
            u8 b1234 : 4;
            u8 b5 : 1;
            u8 b6 : 1;
            u8 b7 : 1;
        } bits;
        u8 raw;
    };
} ECBFlagStruct;

typedef struct SurfaceData {
    s32 index;
    u32 unk;
    Vec3 normal;
} SurfaceData;

typedef struct _CollData {
    HSD_GObj* x0_gobj;
    Vec3 x4_vec;
    Vec3 x10_vec;
    Vec3 x1C_vec;
    Vec3 x28_vec;
    ECBFlagStruct x34_flags;
    ECBFlagStruct x35_flags;
    s16 x36;
    s32 x38;
    s32 x3C;
    s32 x40;
    u32 x44;
    u32 x48;
    u32 x4C;
    f32 x50;
    f32 x54;
    f32 x58;
    f32 x5C;
    s32 x60;
    ftECB x64_ecb;
    ftECB x84_ecb;
    ftECB xA4_ecbCurrCorrect;
    ftECB xC4_ecb;
    ftECB xE4_ecb;
    s32 x104; // TODO: this is the start of a substruct with size 0x2C
    union {
        struct {
            HSD_JObj* x108_joint;
            HSD_JObj* x10C_joint[6];
        };
        struct {
            f32 x108_f32;
            f32 x10C_f32;
            f32 x110_f32;
            f32 x114_f32;
            f32 x118_f32;
            f32 x11C_f32;
            f32 x120_f32;
        };
    };
    f32 x124;
    f32 x128;
    f32 x12C;
    u32 x130_flags;
    s32 x134_envFlags;
    s32 filler138;
    s32 filler13C;
    Vec3 x140;
    SurfaceData x14C_ground;
    SurfaceData x160_rightwall;
    SurfaceData x174_leftwall;
    SurfaceData x188_ceiling;
    /* 0x19C */ s32 x19C;
} CollData;

typedef struct _SmashAttr {
    s32 x2114_state;     // 0x2114 0 = none, 1 = pre-charge, 2 = charging, 3 =
                         // release
    f32 x2118_frames;    // 0x2118 number of frames fp has charged for
    f32 x211C_holdFrame; // 0x211c frame that charge begins/ends
    f32 x2120_damageMul; // 0x2120 damage multiplier
    f32 x2124_frameSpeedMul;    // 0x2124 speed multiplier?
    s32 x2128;                  // 0x2128
    s8 x212C;                   // 0x212C
    s8 x212D;                   // 0x212D
    s8 x212E;                   // 0x212E
    s8 x212F;                   // 0x212F
    s32 x2130_sfxBool;          // 0x2130 bool for smash sfx?
    s8 x2134_vibrateFrame;      // 0x2134
    s8 x2135;                   // 0x2135
    s8 x2136;                   // 0x2136
    s8 x2137;                   // 0x2137
    f32 x2138_smashSinceHitbox; // 0x2138
} SmashAttr;

typedef struct _itPickup // 0x294
{
    Vec2 x0_ground_light_offset;  // 0x294
    Vec2 x8;                      // 0x29C
    Vec2 x10_ground_heavy_offset; // 0x2A4
    Vec2 x18;                     // 0x2AC
    Vec2 x20_air_light_offset;    // 0x2B4
    Vec2 x28;                     // 0x2BC
} itPickup;

typedef struct {
    HSD_Joint* joint;
    u8 padding[0x10];
    HSD_Archive* x14_archive;
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

struct MotionState {
    enum_t anim_id;

    s32 x4_flags;

    union {
        u32 x8_flags;
        struct {
            u8 move_id;
            UnkFlagStruct x9_flags;
            UnkFlagStruct flagsA;
            UnkFlagStruct flagsB;
        };
    };

    HSD_GObjEvent animated;
    HSD_GObjEvent input_updated;
    HSD_GObjEvent physics_updated;
    HSD_GObjEvent collided;
    HSD_GObjEvent camera_updated;
};

struct S_TEMP4 {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xC;
    s32 x10_animCurrFlags;
    s32 x14;
};

struct Fighter_CostumeStrings {
    char* dat_filename;
    char* joint_name;
    char* matanim_joint_name;
};

struct Fighter_DemoStrings {
    char* result_filename;
    char* intro_filename;
    char* ending_filename;
    char* vi_wait_filename;
};

/// @todo Rename this and its members; investigate using it elsewhere.
union Struct2070 {
    struct {
        s8 x2070;

        u8 x2071_b0_3 : 4;
        u8 x2071_b4 : 1;
        u8 x2071_b5 : 1;
        u8 x2071_b6 : 1;
        u8 x2071_b7 : 1;

        u8 x2072_b0_3 : 4;
        u8 x2072_b4 : 1;
        u8 x2072_b5 : 1;
        u8 x2072_b6 : 1;
        u8 x2072_b7 : 1;

        u8 x2073;
    };
    s32 x2070_int;
};

struct Fighter {
    /* 0x0 */ HSD_GObj* gobj;
    /* 0x4 */ FighterKind x4_fighterKind;
    /* 0x8 */ s32 x8_spawnNum;
    /* 0xC */ u8 xC_playerID;
    /* 0x10 */ enum_t motion_id;
    /* 0x14 */ enum_t anim_id;
    /* 0x18 */ s32 x18;
    /* 0x1C */ MotionState* x1C_actionStateList;
    /* 0x20 */ MotionState* x20_actionStateList;
    /* 0x24 */ struct S_TEMP4* x24;
    /* 0x28 */ u8* x28;
    /* 0x2C */ f32 facing_dir;
    /* 0x30 */ f32 x30_facingDirectionRepeated;
    /* 0x34 */ Vec3 x34_scale;
    /* 0x40 */ f32 x40;
    /* 0x44 */ Mtx x44_mtx;
    Vec3 x74_anim_vel;         // 0x74
    Vec3 x80_self_vel;         // 0x80
    Vec3 x8c_kb_vel;           // 0x8C
    Vec3 x98_atk_shield_kb;    // 0x98
    Vec3 xA4_unk_vel;          // 0xA4
    Vec3 cur_pos;              // 0xb0
    Vec3 prev_pos;             // 0xBC
    Vec3 pos_delta;            // 0xC8
    Vec3 xD4_unk_vel;          // 0xD4
    GroundOrAir ground_or_air; // 0xE0
    f32 xE4_ground_accel_1;    // 0xE4
    f32 xE8_ground_accel_2;    // 0xE8
    f32 gr_vel;                // 0xEC
    f32 xF0_ground_kb_vel;
    f32 xF4_ground_attacker_shield_kb_vel;
    Vec2 xF8_playerNudgeVel;
    /* 0x100 */ f32 x100;
    /* 0x104 */ u8 x104;
    /* 0x105 */ s8 x105;
    /* 0x106 */ s8 x106;
    /* 0x107 */ s8 x107;
    /* 0x108 */ HSD_Joint* x108_costume_joint;
    /* 0x10C */ ftData* ft_data;
    /* 0x110 */ attr x110_attr;
    /* 0x294 */ itPickup x294_itPickup;
    /* 0x2C4 */ Vec2 x2C4;
    /* 0x2CC */ void* x2CC;
    /* 0x2D0 */ void* x2D0;
    /* 0x2D4 */ void* x2D4_specialAttributes;
    /* 0x2D8 */ void* x2D8_specialAttributes2;
    /* 0x2DC */ f32 x2DC;
    /* 0x2E0 */ f32 x2E0;
    /* 0x2E4 */ f32 x2E4;
    /* 0x2E8 */ f32 x2E8;
    /* 0x2EC */ f32 x2EC;
    /* 0x2F0 */ u32 x2F0;
    /* 0x2F4 */ unk_t x2F4;
    u8 filler_x2F0[0x3E0 - 0x2F8];
    /* 0x3E0 */ u32 x3E0;
    /* 0x3E4 */ f32 x3E4;
    /* 0x3E8 */ f32 x3E8;
    /* 0x3EC */ s32 x3EC;
    /* 0x3F0 */ s32 x3F0;
    u8 filler_x3F4[0x588 - 0x3F4];
    /* 0x588 */ HSD_LObj* x588;
    /* 0x58C */ s32 x58C;
    /* 0x590 */ s32 x590;
    /* 0x594 */ union {
        struct {
            UnkFlagStruct x594_animCurrFlags1;
            struct {
                u8 x0 : 7;
                u16 x7 : 3;
            } x596_bits;
        };
        s32 x594_s32;
    };
    /* 0x598 */ s32 x598;
    /* 0x59C */ void* x59C;
    /* 0x5A0 */ void* x5A0;
    u8 filler_x5A4[0x5B8 - 0x5A4];
    /* 0x5B8 */ s32 x5B8;
    /* 0x5BC */ s32 x5BC;
    u8 filler_x598[0x5C8 - 0x5C0];
    /* 0x5A0 */ void* x5C8;
    u8 filler_x5CC[0x5E8 - 0x5CC];
    /* 0x5E8 */ FighterBone* ft_bones;
    /* 0x5EC */ DObjList dobj_list;
    /* 0x5F4 */ s8 x5F4;
    /* 0x5F5 */ s8 x5F5;
    /* 0x5F6 */ s8 x5F6;
    /* 0x5F7 */ s8 x5F7;
    /* 0x5F8 */ s8 x5F8;
    u8 filler_x5FC[0x60C - 0x5F9];
    /* 0x60C */ void* x60C;
    union {
        /* 0x610 */ GXColor x610_color_rgba[2];
        struct {
            /* 0x610 */ s32 x610;
            /* 0x614 */ s32 x614;
        };
    };
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

        /* 0x65C */ u32 x65C_heldInputs;
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

    /* 0x68C */ Vec3 x68C_transNPos;
    /* 0x698 */ Vec3 x698;
    /* 0x6A4 */ Vec3 x6A4_transNOffset;
    /* 0x6B0 */ Vec3 x6B0;
    /* 0x6BC */ f32 x6BC_inputStickangle;
    /* 0x6C0 */ Vec3 x6C0;
    /* 0x6CC */ Vec3 x6CC;
    /* 0x6D8 */ Vec3 x6D8;
    /* 0x6E4 */ Vec3 x6E4;
    /* 0x6F0 */ CollData x6F0_collData;
    /* 0x890 */ CameraBox* x890_cameraBox;
    /* 0x894 */ f32 x894_currentAnimFrame;
    /* 0x898 */ f32 x898_unk;
    /* 0x89C */ f32 x89C_frameSpeedMul;
    /* 0x8A0 */ f32 x8A0_unk;
    /* 0x8A4 */ f32 x8A4_animBlendFrames;
    /* 0x8A8 */ f32 x8A8_unk;
    /* 0x8AC */ HSD_JObj* x8AC_animSkeleton;
    u8 filler_x8AC[0x914 - 0x8B0];
    /* 0x914 */ HitCapsule x914[4];
    u8 filler_xDF4[0x1064 - 0xDF4];
    /* 0x1064 */ HitCapsule x1064_thrownHitbox;
    /* 0x119C */ u8 x119C_teamUnk;
    /* 0x119D */ u8 grabber_unk1;
    /* 0x119E */ u8 x119E_hurtboxNum;
    /* 0x119F */ u8 x119F;
    /* 0x11A0 */ HurtCapsule x11A0_fighterHurtbox[15];
    /* 0x1614 */ unk_t x1614;
    /* 0x1618 */ u8 filler_x1618[0x166C - 0x1618];
    /* 0x166C */ u32 x166C;
    /* 0x1670 */ unk_t x1670;
    /* 0x1674 */ u8 filler_x1674[0x1828 - 0x1674];
    /* 0x1828 */ s32 x1828;
    struct dmg // 0x182c
    {
        f32 x182c_behavior;           // 0x182c
        f32 x1830_percent;            // 0x1830
        f32 x1834;                    // 0x1834
        f32 x1838_percentTemp;        // 0x1838
        s32 x183C_applied;            // 0x183c
        s32 x1840;                    // 0x1840
        f32 x1844_direction;          // 0x1844
        s32 x1848_kb_angle;           // 0x1848
        s32 x184c_damaged_hurtbox;    // 0x184c
        f32 x1850_forceApplied;       // 0x1850
        Vec3 x1854_collpos;           // 0x1854
        s32 x1860_dealt;              // 0x1860
        s32 x1864;                    // 0x1864
        HSD_GObj* x1868_source;       // 0x1868
        s32 x186c;                    // 0x186c
        s32 x1870;                    // 0x1870
        s32 x1874;                    // 0x1874
        s32 x1878;                    // 0x1878
        s32 x187c;                    // 0x187c
        s32 x1880;                    // 0x1880
        s32 x1884;                    // 0x1884
        s32 x1888;                    // 0x1888
        s32 x188c;                    // 0x188c
        s32 x1890;                    // 0x1890
        s32 x1894;                    // 0x1894
        s32 x1898;                    // 0x1898
        f32 x189C_unk_num_frames;     // 0x189c
        f32 x18a0;                    // 0x18a0
        f32 x18A4_knockbackMagnitude; // 0x18a4  kb magnitude
        f32 x18A8;                    // 0x18a8
        s32 x18ac_time_since_hit;     // 0x18ac   in frames
        f32 x18B0;                    // 0x18b0
        f32 x18B4_armor;              // 0x18b4
        f32 x18B8;                    // 0x18b8
        f32 x18BC;                    // 0x18bc
        s32 x18C0;                    // 0x18c0
        s32 x18c4_source_ply;         // 0x18c4   damage source ply number
        s32 x18C8;                    // 0x18c8
        s32 x18CC;                    // 0x18cc
        s32 x18D0;                    // 0x18d0
        s32 x18d4;                    // 0x18d4
        s32 x18d8;                    // 0x18d8
        s32 x18dc;                    // 0x18dc
        s32 x18e0;                    // 0x18e0
        s32 x18e4;                    // 0x18e4
        s32 x18e8;                    // 0x18e8
        u16 x18ec_instancehitby; // 0x18ec. Last Move Instance This Player Was
                                 // Hit by
        s32 x18F0;               // 0x18f0
        s32 x18F4;               // 0x18f4
        u8 x18F8;                // 0x18f8
        u8 x18f9;                // 0x18f9
        u16 x18fa_model_shift_frames; // 0x18fa
        u8 x18FC;                     // 0x18fc
        u8 x18FD;                     // 0x18fd
        s32 x1900;                    // 0x1900
        s32 x1904;                    // 0x1904
        s32 x1908;                    // 0x1908
        s32 x190C;                    // 0x190c
        s32 x1910;                    // 0x1910
        s32 x1914;                    // 0x1914
        s32 x1918;                    // 0x1918
        f32 x191C;                    // 0x191c
        s32 x1920;                    // 0x1920
        s32 x1924;                    // 0x1924
        f32 x1928;                    // 0x1928
        f32 x192c;                    // 0x192c
        s32 x1930;                    // 0x1930
        s32 x1934;                    // 0x1934
        s32 x1938;                    // 0x1938
        s32 x193c;                    // 0x193c
        s32 x1940;                    // 0x1940
        s32 x1944;                    // 0x1944
        s32 x1948;                    // 0x1948
        s32 x194C;                    // 0x194c
        s32 x1950;                    // 0x1950
        f32 x1954;                    // 0x1954
        f32 x1958;                    // 0x1958
        f32 x195c_hitlag_frames;      // 0x195c
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
    /* 0x19C0 */ HitResult shield_hit;
    /* 0x19E4 */ HitResult reflect_hit;
    /* 0x1A08 */ HitResult absorb_hit;
    struct {
        f32 x1A2C_reflectHitDirection;
        s32 x1A30_maxDamage;
        f32 x1A34_damageMul;
        f32 x1A38_speedMul;
        s32 x1A3C_damageOver; // % damage over the maximum reflectable damage
                              // threshold
    } ReflectAttr;
    struct {
        f32 x1A40_absorbHitDirection;
        s32 x1A44_damageTaken; // unconfirmred?
        s32 x1A48_hitsTaken;   // unconfirmed?
    } AbsorbAttr;
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
    /* 0x1A68 */ u16 x1A68;
    /* 0x1A6A */ u16 x1A6A;
    /* 0x1A6C */ f32 x1A6C;
    /* 0x1A70 */ Vec3 x1A70;
    /* 0x1A7C */ Vec3 x1A7C;
    u8 filler_x1A7C[0x1A94 - 0x1A88];
    /* 0x1A94 */ u32 x1A94;
    /* 0x1A98 */ u32 x1A98;
    /* 0x1A9C */ s32 x1A9C;
    u8 filler_x1A9C[0x2004 - 0x1AA0];
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
    /* 0x2068 */ s32 x2068_attackID;
    u8 filler_x206C[0x2070 - 0x206C];
    /* 0x2070 */ union Struct2070 x2070;
    u8 filler_x2074[0x208C - 0x2074];
    /* 0x208C */ s32 x208C;
    /* 0x2090 */ u16 x2090;
    /* 0x2092 */ u16 x2092;
    /* 0x2094 */ HSD_GObj* x2094; // GObj pointer of combo victim?
    /* 0x2098 */ u16 x2098;
    /* 0x209A */ u16 x209A;
    /* 0x209C */ s16 x209C;
    /* 0x20A0 */ HSD_JObj* x20A0_accessory;
    /* 0x20A4 */ s32 x20A4;
    /* 0x20A8 */ s32 x20A8;
    /* 0x20AC */ HSD_GObj* x20AC;
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
    /* 0x2114 */ SmashAttr x2114_SmashAttr;
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
    /* 0x216C */ f32 unk_grab_val;
    /* 0x2170 */ f32 x2170;
    u8 filler_x2174[0x2180 - 0x2174];
    /* 0x2180 */ s32 x2180;
    /* 0x2184 */ HSD_JObj* x2184;
    /* 0x2188 */ S32Vec2 x2188;
    // callback struct. Not all of them used by fighter.c, but I'm leaving them
    // in for now.
    struct cb {
        void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj* fp); // used
        void (*x2194_callback)(HSD_GObj* fp);                    // used
        void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj*,
                                                    HSD_GObj*); // used
        void (*x219C_callback_IASA)(HSD_GObj* fp);              // used
        void (*x21A0_callback_Anim)(HSD_GObj* fp);
        void (*x21A4_callback_Phys)(HSD_GObj* fp); // xused
        void (*x21A8_callback_Coll)(HSD_GObj* fp);
        void (*x21AC_callback_Cam)(HSD_GObj* fp);
        void (*x21B0_callback_Accessory1)(HSD_GObj* fp);
        void (*x21B4_callback_Accessory2)(HSD_GObj* fp); // used
        void (*x21B8_callback_Accessory3)(HSD_GObj* fp); // used
        void (*x21BC_callback_Accessory4)(HSD_GObj* fp);
        void (*x21C0_callback_OnGiveDamage)(HSD_GObj* fp);
        void (*x21C4_callback_OnShieldHit)(HSD_GObj* fp);
        void (*x21C8_callback_OnReflectHit)(HSD_GObj* fp);
        void (*x21CC_callback)(HSD_GObj* fp);
        void (*x21D0_callback_EveryHitlag)(HSD_GObj* fp); // xused
        void (*x21D4_callback_EnterHitlag)(HSD_GObj* fp);
        void (*x21D8_callback_ExitHitlag)(HSD_GObj* fp);
        void (*x21DC_callback_OnTakeDamage)(HSD_GObj* fp);
        void (*x21E0_callback_OnDeath)(HSD_GObj* fp); // used
        void (*x21E4_callback_OnDeath2)(
            HSD_GObj*
                fp); // used. internally Dead_Proc as evidenced by 800f5430
        void (*x21E8_callback_OnDeath3)(HSD_GObj* fp); // used
        void (*x21EC_callback)(HSD_GObj* fp);
        void (*x21F0_callback)(HSD_GObj* fp);
        void (*x21F4_callback)(HSD_GObj* fp);
        void (*x21F8_callback)(HSD_GObj* fp);
    } cb;
    /* 0x21FC */ UnkFlagStruct x21FC_flag;
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
    /* 0x221B */
    union {
        u8 x221B;
        struct {
            u8 x221B_b0 : 1;
            u8 x221B_b1 : 1;
            u8 x221B_b2 : 1;
            u8 x221B_b3 : 1;
            u8 x221B_b4 : 1;
            u8 x221B_b5 : 1;
            u8 x221B_b6 : 1;
            u8 x221B_b7 : 1;
        };
    };
    /* 0x221C */
    union {
        struct {
            UnkFlagStruct x221C_flag;
            UnkFlagStruct x221D_flag;
        };
        struct {
            u16 x221C_u16_x : 7;
            u16 x221C_u16_y : 3;
            u16 x221C_u16_z : 6;
        };
    };
    /* 0x221E */ UnkFlagStruct x221E_flag;
    /* 0x221F */ UnkFlagStruct x221F_flag;
    struct {
        union {
            struct {
                u8 b0 : 3;
                u8 b3 : 1;
                u8 b4 : 1;
                u8 b5 : 1;
                u8 b6 : 1;
                u8 b7 : 1;
            } bits;
            u8 flags;
        };
    } x2220_flag;
    /* 0x2221 */ UnkFlagStruct x2221_flag;
    /* 0x2222 */ UnkFlagStruct x2222_flag;
    /* 0x2223 */ UnkFlagStruct x2223_flag;
    /* 0x2224 */ UnkFlagStruct x2224_flag;
    /* 0x2225 b0 */ u8 x2225_b0 : 1;
    /* 0x2225 b1 */ u8 x2225_b1 : 1;
    /* 0x2225 b2 */ u8 x2225_b2 : 1;
    /* 0x2225 b3 */ u8 x2225_b3 : 1;
    /* 0x2225 b4 */ u8 x2225_b4 : 1;
    /* 0x2225 b5 */ u8 x2225_b5 : 1;
    /* 0x2225 b6 */ u8 x2225_b6 : 1;
    /* 0x2225 b7 */ u8 x2225_b7 : 1;
    /* 0x2226 */ UnkFlagStruct x2226_flag;
    /* 0x2227 */ UnkFlagStruct x2227_flag;
    /* 0x2228 */ struct { /// UnkFlagStruct does not quite work
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

    union Fighter_FighterVars {
        u8 _[FighterVars_Size];
        struct ftCaptain_FighterVars ca, gn;
        struct ftDonkey_FighterVars dk;
        struct ftFox_FighterVars fx, fc;
        struct ftGameWatch_FighterVars gw;
        struct ftKirby_FighterVars kb;
        struct ftKoopa_FighterVars kp, gk;
        struct ftLink_FighterVars lk, cl;
        struct ftLuigi_FighterVars lg;
        struct ftMario_FighterVars mr;
        struct ftMars_FighterVars ms;
        struct ftMasterhand_FighterVars mh, ch;
        struct ftMewtwo_FighterVars mt;
        struct ftNess_FighterVars ns;
        struct ftPeach_FighterVars pe;
        struct ftPikachu_FighterVars pk, pc;
        struct ftPopo_FighterVars pp, nn;
        struct ftPurin_FighterVars pr;
        struct ftSamus_FighterVars ss;
        struct ftSandbag_FighterVars sb;
        struct ftSeak_FighterVars sk;
        struct ftYoshi_FighterVars ys;
        struct ftZakoBoy_FighterVars bo, gl;
        struct ftZelda_FighterVars zd;
    } fv;

    /* 0x232C */ s32 x232C;
    /* 0x2330 */ Vec2 x2330;
    /* 0x2338 */ Vec2 x2338;

    /// @at{2340} @sz{AC}
    union Fighter_MotionVars {
        u8 _[0x23EC - 0x2340];
        union ftCaptain_MotionVars ca, gn;
        union ftCommon_MotionVars co;
        union ftDonkey_MotionVars dk;
        union ftFox_MotionVars fx, fc;
        union ftGameWatch_MotionVars gw;
        union ftKoopa_MotionVars kp;
        union ftLuigi_MotionVars lg;
        union ftMario_MotionVars mr, dr;
        union ftMars_MotionVars ms, fe;
        union ftMasterHand_MotionVars mh, ch;
        union ftMewtwo_MotionVars mt;
        union ftNess_MotionVars ns;
        union ftPikachu_MotionVars pk, pc;
        union ftPurin_MotionVars pr;
        union ftSamus_MotionVars ss;
        union ftSeak_MotionVars sk;
        union ftYoshi_MotionVars ys;
        union ftZelda_MotionVars zd;
    } mv;
};

#endif
