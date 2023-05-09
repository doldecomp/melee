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
    /* +0 */ f32 x0;
    /* +4 */ f32 x4;
    /* +8 */ f32 x8_someStickThreshold;
    /* +C */ f32 xC;
    /* +10 */ f32 x10;
    /* +14 */ f32 x14;
    /* +18 */ f32 x18;
    /* +1C */ f32 x1C;
    /* +20 */ f32 x20;
    /* +24 */ f32 x24;
    /* +28 */ f32 x28;
    /* +2C */ f32 x2C;
    /* +30 */ f32 x30;
    /* +34 */ u8 x34[0x70 - 0x34];
    /* +70 */ f32 x70_someLStickYMax;
    /* +74 */ u8 x74[0x78 - 0x74];
    /* +78 */ f32 x78;
    /* +7C */ u8 x7C[0x88 - 0x7C];
    /* +88 */ f32 x88;
    /* +8C */ s32 x8C;
    /* +90 */ u8 x90[0x98 - 0x90];
    /* +98 */ f32 x98_shieldHealthInit;
    /* +9C */ u8 x9C[0xEC - 0x9C];
    /* +EC */ f32 xEC;
    /* +F0 */ f32 xF0;
    /* +F4 */ u8 xF4[0x128 - 0xF4];
    /* +128 */ f32 x128;
    /* +12C */ f32 x12C;
    /* +130 */ f32 x130;
    /* +134 */ s32 x134;
    /* +138 */ f32 x138;
    /* +13C */ f32 x13C;
    /* +140 */ u8 x140[0x164 - 0x140];
    /* +164 */ f32 x164;
    /* +168 */ u8 x168[0x194 - 0x168];
    /* +194 */ f32 x194_unkHitLagFrames;
    /* +198 */ f32 x198;
    /* +19C */ f32 x19C;
    /* +1A0 */ f32 x1A0;
    /* +1A4 */ u8 x1A4[0x1FC - 0x1A4];
    /* +1FC */ f32 x1FC;
    /* +200 */ f32 x200;
    /* +204 */ f32 x204_knockbackFrameDecay;
    /* +208 */ u8 x208[0x21C - 0x208];
    /* +21C */ f32 x21C;
    /* +220 */ u8 x220[0x258 - 0x220];
    /* +258 */ f32 x258;
    /* +25C */ u8 x25C[0x260 - 0x25C];
    /* +260 */ f32 x260_startShieldHealth;
    /* +264 */ u8 x264[0x27C - 0x264];
    /* +27C */ f32 x27C;
    /* +280 */ f32 x280_unkShieldHealth;
    /* +284 */ f32 x284;
    /* +288 */ f32 x288;
    /* +28C */ u8 x28C[0x294 - 0x28C];
    /* +294 */ f32 x294;
    /* +298 */ u8 x298[0x2A4 - 0x298];
    /* +2A4 */ f32 x2A4;
    /* +2A8 */ u8 x2A8[0x2B4 - 0x2A8];
    /* +2B4 */ f32 x2B4;
    /* +2B8 */ u8 x2B8[0x2DC - 0x2B8];
    /* +2DC */ f32 x2DC;
    /* +2E0 */ f32 x2E0;
    /* +2E4 */ u8 x2E4[0x308 - 0x2E4];
    /* +308 */ f32 x308;
    /* +30C */ u8 x30C[0x3A8 - 0x30C];
    /* +3A8 */ f32 x3A8;
    /* +3AC */ u8 x3AC[0x3E0 - 0x3AC];
    /* +3E0 */ f32 x3E0;
    /* +3E4 */ f32 x3E4;
    /* +3E8 */ f32 x3E8_shieldKnockbackFrameDecay;
    /* +3EC */ f32 x3EC_shieldGroundFrictionMultiplier;
    /* +3F0 */ u8 x3F0[0x418 - 0x3F0];
    /* +418 */ s32 x418;
    /* +41C */ s32 x41C;
    /* +420 */ u8 x420[0x440 - 0x420];
    /* +440 */ f32 x440;
    /* +444 */ f32 x444;
    /* +448 */ f32 x448;
    /* +44C */ f32 x44C;
    /* +450 */ f32 x450;
    /* +454 */ f32 x454;
    /* +458 */ f32 x458;
    /* +45C */ f32 x45C;
    /* +460 */ f32 x460;
    /* +464 */ u8 x464[0x480 - 0x464];
    /* +480 */ f32 x480;
    /* +484 */ u8 x484[0x498 - 0x484];
    /* +498 */ u32 x498_ledgeCooldownTime;
    /* +49C */ u8 x49C[0x4C4 - 0x49C];
    /* +4C4 */ s32 x4C4;
    /* +4C8 */ s32 x4C8;
    /* +4CC */ s32 x4CC;
    /* +4D0 */ f32 x4D0;
    /* +4D4 */ f32 x4D4;
    /* +4D8 */ u32 x4D8;
    /* +4DC */ u8 x4DC[0x59C - 0x4DC];
    /* +59C */ f32 x59C;
    /* +5A0 */ u8 x5A0[0x5C0 - 0x5A0];
    /* +5F0 */ f32 x5C0;
    /* +5C4 */ u8 x5C4[0x5F0 - 0x5C4];
    /* +5F0 */ u32 x5F0;
    /* +5F4 */ u8 x5F4[0x6D8 - 0x5F4];
    /// @todo expand to actual size
    /* +6D8 */ void* x6D8[1];
    /* +6DC */ GXColor x6DC_colorsByPlayer[4];
    /* +6EC */ u8 x6EC[0x6F4 - 0x6EC];
    /* +6F4 */ s32 x6F4_unkDamage;
    /* +6F8 */ s32 x6F8;
    /* +6FC */ s32 x6FC;
    /* +700 */ s32 x700;
    /* +704 */ f32 x704;
    /* +708 */ f32 x708;
    /* +70C */ f32 x70C;
    /* +710 */ f32 x710;
    /* +714 */ f32 x714;
    /* +718 */ u8 x718[0x768 - 0x718];
    /* +768 */ f32 x768;
    /* +76C */ f32 x76C;
    /* +770 */ f32 x770;
    /* +774 */ s32 x774;
    /* +7A0 */ u8 x7A0_filler[0x7A0 - 0x778];
    /* +7A0 */ s32 x7A0;
    /* +7A4 */ s32 x7A4;
    /* +7A8 */ s32 x7A8;
    /* +7AC */ s32 x7AC;
    /* +7B0 */ s32 x7B0;
    /* +7B4 */ s32 x7B4_unkDamage;
    /* +7B8 */ f32 x7B8;
    /* +7BC */ f32 x7BC;
    /* +7C0 */ f32 x7C0;
    /* +7C4 */ s32 x7C4;
    /* +7C8 */ s32 x7C8;
    /* +7CC */ s32 x7CC;
    /* +7D0 */ s32 x7D0;
    /* +7D4 */ s32 x7D4;
    /* +7D8 */ s32 x7D8;
    /* +7DC */ s32 x7DC;
    /* +7E0 */ s32 x7E0;
    /* +7E4 */ f32 x7E4_scaleZ;
    /* +7E8 */ u8 x7E8_filler[0x814 - 0x7E8];
    /* +814 */ s32 x814;
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

typedef struct ftCo_DatAttrs {
    /* fp+110 */ f32 walk_init_vel;
    /* fp+114 */ f32 walk_accel;
    /* fp+118 */ f32 walk_max_vel;
    /* fp+11C */ f32 x11C_SlowWalkMax;
    /* fp+120 */ f32 x120_MidWalkPoint;
    /* fp+124 */ f32 x124_FastWalkMin;
    /* fp+128 */ f32 gr_friction; // used
    /* fp+12C */ f32 x12C_DashInitialVelocity;
    /* fp+130 */ f32 x130_DashrunAccelerationA;
    /* fp+134 */ f32 x134_DashrunAccelerationB;
    /* fp+138 */ f32 x138_DashrunTerminalVelocity;
    /* fp+13C */ f32 x13C_RunAnimationScaling;
    /* fp+140 */ f32 x140_MaxRunbrakeFrames;
    /* fp+144 */ f32 x144_GroundedMaxHorizontalVelocity;
    /* fp+148 */ f32 x148_JumpStartupTime;
    /* fp+14C */ f32 x14C_JumpHInitialVelocity;
    /* fp+150 */ f32 x150_JumpVInitialVelocity;
    /* fp+154 */ f32 x154_GroundToAirJumpMomentumMultiplier;
    /* fp+158 */ f32 x158_JumpHMaxVelocity;
    /* fp+15C */ f32 x15C_HopVInitialVelocity;
    /* fp+160 */ f32 x160_AirJumpVMultiplier;
    /* fp+164 */ f32 x164_AirJumpHMultiplier;
    /* fp+168 */ s32 x168_MaxJumps;
    /* fp+16C */ f32 grav;
    /* fp+170 */ f32 terminal_vel;
    /* fp+174 */ f32 air_drift_stick_mul;
    /* fp+178 */ f32 x178_AerialDriftBase;
    /* fp+17C */ f32 air_drift_max;
    /* fp+180 */ f32 x180_AerialFriction;
    /* fp+184 */ f32 x184_FastfallVelocity;
    /* fp+188 */ f32 x188_HorizontalAirMobilityConstant;
    /* fp+18C */ f32 x18C_Jab_2InputWindow;
    /* fp+190 */ s32 x190_Jab_3InputWindow;
    /* fp+194 */ s32 x194_FramesToChangeDirectionOnStandingTurn;
    /* fp+198 */ f32 x198_Weight;
    /* fp+19C */ f32 x19C_ModelScaling;
    /* fp+1A0 */ f32 x1A0_InitialShieldSize;
    /* fp+1A4 */ f32 x1A4_ShieldBreakInitialVelocity;
    /* fp+1A8 */ s32 x1A8_RapidJabWindow;
    /* fp+1AC */ s32 x1AC;
    /* fp+1B0 */ s32 x1B0;
    /* fp+1B4 */ s32 x1B4;
    /* fp+1B8 */ f32 x1B8_LedgeJumpHorizontalVelocity;
    /* fp+1BC */ f32 x1BC_LedgeJumpVerticalVelocity;
    /* fp+1C0 */ f32 x1C0_ItemThrowVelocityMultiplier;
    /* fp+1C4 */ s32 x1C4;
    /* fp+1C8 */ s32 x1C8;
    /* fp+1CC */ s32 x1CC;
    /* fp+1D0 */ s32 x1D0;
    /* fp+1D4 */ s32 x1D4;
    /* fp+1D8 */ s32 x1D8;
    /* fp+1DC */ s32 x1DC;
    /* fp+1E0 */ s32 x1E0;
    /* fp+1E4 */ s32 x1E4;
    /* fp+1E8 */ s32 x1E8;
    /* fp+1EC */ s32 x1EC;
    /* fp+1F0 */ f32 x1F0_KirbyBStarDamage;
    /* fp+1F4 */ f32 x1F4_NormalLandingLag;
    /* fp+1F8 */ f32 x1F8_NAirLandingLag;
    /* fp+1FC */ f32 x1FC_FAirLandingLag;
    /* fp+200 */ f32 x200_BAirLandingLag;
    /* fp+204 */ f32 x204_UAirLandingLag;
    /* fp+208 */ f32 x208_DAirLandingLag;
    /* fp+20C */ f32 x20C_NametagHeight;
    /* fp+210 */ s32 x210;
    /* fp+214 */ f32 x214_WallJumpHorizontalVelocity;
    /* fp+218 */ f32 x218_WallJumpVerticalVelocity;
    /* fp+21C */ s32 x21C;
    /* fp+220 */ f32 x220_TrophyScale;
    /* fp+224 */ Vec3 x224;
    /* fp+230 */ Vec3 x230;
    /* fp+23C */ f32 x23C;
    /* fp+240 */ Vec3 x240;
    /* fp+24C */ f32 x24C;
    /* fp+250 */ s32 x250;
    /* fp+254 */ s32 x254;
    /* fp+258 */ f32 x258; // used
    /* fp+25C */ f32 x25C_BubbleRatio;
    /* fp+260 */ s32 x260;
    /* fp+264 */ s32 x264;
    /* fp+268 */ s32 x268;
    /* fp+26C */ s32 x26C;
    /* fp+270 */ f32 x270_RespawnPlatformScale;
    /* fp+274 */ s32 x274;
    /* fp+278 */ s32 x278;
    /* fp+27C */ s32 x27C_CameraZoomTargetBone;
    /* fp+280 */ Vec3 x280;
    /* fp+28C */ s32 x28C;
    /* fp+290 */ s32 x290_WeightDependentThrowSpeedFlags;
} ftCo_DatAttrs;

typedef struct _FighterBone {
    /* +0 */ HSD_JObj* x0_jobj;
    /* +4 */ HSD_JObj* x4_jobj2; // used for interpolation
    /* +5 */ UnkFlagStruct flags;
    /* +6 */ u8 filler_x6[7];
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
    /* fp+6F0 */ HSD_GObj* x0_gobj;
    /* fp+6F4 */ Vec3 x4_vec;
    /* fp+700 */ Vec3 x10_vec;
    /* fp+70C */ Vec3 x1C_vec;
    /* fp+718 */ Vec3 x28_vec;
    /* fp+724 */ ECBFlagStruct x34_flags;
    /* fp+725 */ ECBFlagStruct x35_flags;
    /* fp+726 */ s16 x36;
    /* fp+728 */ s32 x38;
    /* fp+72C */ s32 x3C;
    /* fp+730 */ s32 x40;
    /* fp+734 */ u32 x44;
    /* fp+738 */ u32 x48;
    /* fp+73C */ u32 x4C;
    /* fp+740 */ f32 x50;
    /* fp+744 */ f32 x54;
    /* fp+748 */ f32 x58;
    /* fp+74C */ f32 x5C;
    /* fp+750 */ s32 x60;
    /* fp+754 */ ftECB x64_ecb;
    /* fp+774 */ ftECB x84_ecb;
    /* fp+794 */ ftECB xA4_ecbCurrCorrect;
    /* fp+7B4 */ ftECB xC4_ecb;
    /* fp+7D4 */ ftECB xE4_ecb;
    /// @todo this is the start of a substruct with size 0x2C
    /* fp+7F4 */ s32 x104;
    /* fp+7F8 */ union {
        /* fp+7F8 */ struct {
            /* fp+7F8 */ HSD_JObj* x108_joint;
            /* fp+7FC */ HSD_JObj* x10C_joint[6];
        };
        /* fp+7F8 */ struct {
            /* fp+7F8 */ f32 x108_f32;
            /* fp+7FC */ f32 x10C_f32;
            /* fp+800 */ f32 x110_f32;
            /* fp+804 */ f32 x114_f32;
            /* fp+808 */ f32 x118_f32;
            /* fp+80C */ f32 x11C_f32;
            /* fp+810 */ f32 x120_f32;
        };
    };
    /* fp+814 */ f32 x124;
    /* fp+818 */ f32 x128;
    /* fp+81C */ f32 x12C;
    /* fp+820 */ u32 x130_flags;
    /* fp+824 */ s32 env_flags;
    /* fp+828 */ s32 x138;
    /* fp+82C */ s32 x13C;
    /* fp+830 */ Vec3 x140;
    /* fp+83C */ SurfaceData x14C_ground;
    /* fp+850 */ SurfaceData x160_rightwall;
    /* fp+864 */ SurfaceData x174_leftwall;
    /* fp+878 */ SurfaceData x188_ceiling;
    /* fp+88C */ s32 x19C;
} CollData;

/* fp+2114 */ typedef struct _SmashAttr {
    /// 0 = none, 1 = pre-charge, 2 = charging, 3 = release
    /* fp+2114 */ enum_t x2114_state;
    /// number of frames fp has charged for
    /* fp+2118 */ f32 x2118_frames;
    /// frame that charge begins/ends
    /* fp+211C */ f32 x211C_holdFrame;
    /// damage multiplier
    /* fp+2120 */ f32 x2120_damageMul;
    /// speed multiplier?
    /* fp+2124 */ f32 x2124_frameSpeedMul;
    /* fp+2128 */ s32 x2128;
    /* fp+212C */ s8 x212C;
    /* fp+212D */ s8 x212D;
    /* fp+212E */ s8 x212E;
    /* fp+212F */ s8 x212F;
    /// bool for smash sfx?
    /* fp+2130 */ s32 x2130_sfxBool;
    /* fp+2134 */ s8 x2134_vibrateFrame;
    /* fp+2135 */ s8 x2135;
    /* fp+2136 */ s8 x2136;
    /* fp+2137 */ s8 x2137;
    /* fp+2138 */ f32 x2138_smashSinceHitbox;
} SmashAttr;

/* fp+294 */ typedef struct _itPickup {
    /* fp+294 */ Vec2 x0_ground_light_offset;
    /* fp+29C */ Vec2 x8;
    /* fp+2A4 */ Vec2 x10_ground_heavy_offset;
    /* fp+2AC */ Vec2 x18;
    /* fp+2B4 */ Vec2 x20_air_light_offset;
    /* fp+2BC */ Vec2 x28;
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

    enum_t x4_flags;

    union {
        /// @todo Try to match without this being a @c union.
        u32 _;
        struct {
            FtMoveId move_id : 8;
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
/* fp+2070 */ union Struct2070 {
    /* fp+2070 */ struct {
        /* fp+2070 */ s8 x2070;
        /* fp+2070:0 */ u8 x2071_b0_3 : 4;
        /* fp+2070:4 */ u8 x2071_b4 : 1;
        /* fp+2070:5 */ u8 x2071_b5 : 1;
        /* fp+2070:6 */ u8 x2071_b6 : 1;
        /* fp+2070:7 */ u8 x2071_b7 : 1;

        /* fp+2070:0 */ u8 x2072_b0_3 : 4;
        /* fp+2070:4 */ u8 x2072_b4 : 1;
        /* fp+2070:5 */ u8 x2072_b5 : 1;
        /* fp+2070:6 */ u8 x2072_b6 : 1;
        /* fp+2070:7 */ u8 x2072_b7 : 1;
        /* fp+2073 */ u8 x2073;
    };
    /* fp+2070 */ s32 x2070_int;
};

struct Fighter {
    /*    fp+0 */ HSD_GObj* gobj;
    /*    fp+4 */ FighterKind kind;
    /*    fp+8 */ s32 x8_spawnNum;
    /*    fp+C */ u8 xC_playerID;
    /*   fp+10 */ FtMotionId motion_id;
    /*   fp+14 */ enum_t anim_id;
    /*   fp+18 */ s32 x18;
    /*   fp+1C */ MotionState* x1C_actionStateList;
    /*   fp+20 */ MotionState* x20_actionStateList;
    /*   fp+24 */ struct S_TEMP4* x24;
    /*   fp+28 */ u8* x28;
    /*   fp+2C */ f32 facing_dir;
    /*   fp+30 */ f32 x30_facingDirectionRepeated;
    /*   fp+34 */ Vec3 x34_scale;
    /*   fp+40 */ f32 x40;
    /*   fp+44 */ Mtx x44_mtx;
    /*   fp+74 */ Vec3 x74_anim_vel;
    /*   fp+80 */ Vec3 self_vel;
    /*   fp+8C */ Vec3 x8c_kb_vel;
    /*   fp+98 */ Vec3 x98_atk_shield_kb;
    /*   fp+A4 */ Vec3 xA4_unk_vel;
    /*   fp+B0 */ Vec3 cur_pos;
    /*   fp+BC */ Vec3 prev_pos;
    /*   fp+C8 */ Vec3 pos_delta;
    /*   fp+D4 */ Vec3 xD4_unk_vel;
    /*   fp+E0 */ GroundOrAir ground_or_air;
    /*   fp+E4 */ f32 xE4_ground_accel_1;
    /*   fp+E8 */ f32 xE8_ground_accel_2;
    /*   fp+EC */ f32 gr_vel;
    /*   fp+F0 */ f32 xF0_ground_kb_vel;
    /*   fp+F4 */ f32 xF4_ground_attacker_shield_kb_vel;
    /*   fp+F8 */ Vec2 xF8_playerNudgeVel;
    /*  fp+100 */ f32 x100;
    /*  fp+104 */ u8 x104;
    /*  fp+105 */ s8 x105;
    /*  fp+106 */ s8 x106;
    /*  fp+107 */ s8 x107;
    /*  fp+108 */ HSD_Joint* x108_costume_joint;
    /*  fp+10C */ ftData* ft_data;
    /*  fp+110 */ ftCo_DatAttrs co_attrs;
    /*  fp+294 */ itPickup x294_itPickup;
    /*  fp+2C4 */ Vec2 x2C4;
    /*  fp+2CC */ void* x2CC;
    /*  fp+2D0 */ void* x2D0;
    /*  fp+2D4 */ void* dat_attrs;
    /*  fp+2D8 */ void* x2D8_specialAttributes2;
    /*  fp+2DC */ f32 x2DC;
    /*  fp+2E0 */ f32 x2E0;
    /*  fp+2E4 */ f32 x2E4;
    /*  fp+2E8 */ f32 x2E8;
    /*  fp+2EC */ f32 x2EC;
    /*  fp+2F0 */ u32 x2F0;
    /*  fp+2F4 */ unk_t x2F4;
    /*  fp+2F8 */ u8 filler_x2F0[0x3E0 - 0x2F8];
    /*  fp+3E0 */ u32 x3E0;
    /*  fp+3E4 */ f32 x3E4;
    /*  fp+3E8 */ f32 x3E8;
    /*  fp+3EC */ s32 x3EC;
    /*  fp+3F0 */ s32 x3F0;
    /*  fp+3F4 */ u8 filler_x3F4[0x588 - 0x3F4];
    /*  fp+588 */ HSD_LObj* x588;
    /*  fp+58C */ s32 x58C;
    /*  fp+590 */ s32 x590;
    /*  fp+594 */ union {
        struct {
            /* fp+594 */ UnkFlagStruct x594_animCurrFlags1;
            /* fp+596 */ struct {
                /* fp+596:0 */ u8 x0 : 7;
                /* fp+596:7 */ u16 x7 : 3;
            } x596_bits;
        };
        /* fp+594 */ s32 x594_s32;
    };
    /*  fp+598 */ s32 x598;
    /*  fp+59C */ UNK_T x59C;
    /*  fp+5A0 */ UNK_T x5A0;
    /*  fp+5A4 */ u8 filler_x5A4[0x5B8 - 0x5A4];
    /*  fp+5B8 */ s32 x5B8;
    /*  fp+5BC */ s32 x5BC;
    /*  fp+598 */ u8 filler_x598[0x5C8 - 0x5C0];
    /*  fp+5A0 */ void* x5C8;
    /*  fp+5CC */ u8 filler_x5CC[0x5E8 - 0x5CC];
    /*  fp+5E8 */ FighterBone* parts;
    /*  fp+5EC */ DObjList dobj_list;
    /*  fp+5F4 */ s8 x5F4;
    /*  fp+5F5 */ s8 x5F5;
    /*  fp+5F6 */ s8 x5F6;
    /*  fp+5F7 */ s8 x5F7;
    /*  fp+5F8 */ s8 x5F8;
    /*  fp+5FC */ u8 filler_x5FC[0x60C - 0x5F9];
    /*  fp+60C */ void* x60C;
    /*  fp+610 */ union {
        /* fp+610 */ GXColor x610_color_rgba[2];
        /* fp+610 */ struct {
            /* fp+610 */ s32 x610;
            /* fp+614 */ s32 x614;
        };
    };
    /*  fp+618 */ u8 x618_player_id;
    /*  fp+619 */ u8 x619_costume_id;
    /*  fp+61A */ u8 x61A_controller_index;
    /*  fp+61B */ u8 x61B_team;
    /*  fp+61C */ u8 x61C;
    /*  fp+61D */ u8 x61D;
    /*  fp+61E */ u8 filler_x61E[0x620 - 0x61E];
    /*  fp+620 */ struct {
        /*  fp+620 */ Vec2 lstick;
        /*  fp+628 */ Vec2 lstick1;
        /*  fp+630 */ f32 x630;
        /*  fp+634 */ f32 x634;
        /*  fp+638 */ Vec2 lsubstick;
        /*  fp+640 */ Vec2 lsubstick1;
        /*  fp+648 */ f32 x648;
        /*  fp+64C */ f32 x64C;
        /*  fp+650 */ f32 x650;
        /*  fp+654 */ f32 x654;
        /*  fp+658 */ f32 x658;
        /*  fp+65C */ HSD_Pad held_inputs;
        /*  fp+660 */ s32 x660;
        /*  fp+664 */ s32 x664;
        /*  fp+668 */ HSD_Pad x668;
        /*  fp+66C */ s32 x66C;
    } input;
    /*  fp+670 */ u8 x670_timer_lstick_tilt_x;
    /*  fp+671 */ u8 x671_timer_lstick_tilt_y;
    /*  fp+672 */ u8 x672_input_timer_counter;
    /*  fp+673 */ u8 x673;
    /*  fp+674 */ u8 x674;
    /*  fp+674 */ u8 x675;
    /*  fp+676 */ u8 x676_x;
    /*  fp+677 */ u8 x677_y;
    /*  fp+678 */ u8 x678;
    /*  fp+679 */ u8 x679_x;
    /*  fp+67A */ u8 x67A_y;
    /*  fp+67B */ u8 x67B;
    /*  fp+67C */ u8 x67C;
    /*  fp+67D */ u8 x67D;
    /*  fp+67E */ u8 x67E;
    /*  fp+67F */ u8 x67F;
    /*  fp+680 */ u8 x680;
    /*  fp+681 */ u8 x681;
    /*  fp+682 */ u8 x682;
    /*  fp+683 */ u8 x683;
    /*  fp+684 */ u8 x684;
    /*  fp+685 */ u8 x685;
    /*  fp+686 */ u8 x686;
    /*  fp+687 */ u8 x687;
    /*  fp+688 */ u8 x688;
    /*  fp+689 */ u8 x689;
    /*  fp+68A */ u8 x68A;
    /*  fp+68B */ u8 x68B;
    /*  fp+68C */ Vec3 x68C_transNPos;
    /*  fp+698 */ Vec3 x698;
    /*  fp+6A4 */ Vec3 x6A4_transNOffset;
    /*  fp+6B0 */ Vec3 x6B0;
    /*  fp+6BC */ f32 lstick_angle;
    /*  fp+6C0 */ Vec3 x6C0;
    /*  fp+6CC */ Vec3 x6CC;
    /*  fp+6D8 */ Vec3 x6D8;
    /*  fp+6E4 */ Vec3 x6E4;
    /*  fp+6F0 */ CollData coll_data;
    /*  fp+890 */ CameraBox* x890_cameraBox;
    /*  fp+894 */ f32 cur_anim_frame;
    /*  fp+898 */ f32 x898_unk;
    /*  fp+89C */ f32 x89C_frameSpeedMul;
    /*  fp+8A0 */ f32 x8A0_unk;
    /*  fp+8A4 */ f32 x8A4_animBlendFrames;
    /*  fp+8A8 */ f32 x8A8_unk;
    /*  fp+8AC */ HSD_JObj* x8AC_animSkeleton;
    /*  fp+8AC */ u8 filler_x8AC[0x914 - 0x8B0];
    /*  fp+914 */ HitCapsule x914[4];
    /*  fp+DF4 */ u8 filler_xDF4[0x1064 - 0xDF4];
    /* fp+1064 */ HitCapsule x1064_thrownHitbox;
    /* fp+119C */ u8 x119C_teamUnk;
    /* fp+119D */ u8 grabber_unk1;
    /* fp+119E */ u8 x119E_hurtboxNum;
    /* fp+119F */ u8 x119F;
    /* fp+11A0 */ HurtCapsule x11A0_fighterHurtbox[15];
    /* fp+1614 */ unk_t x1614;
    /* fp+1618 */ u8 filler_x1618[0x166C - 0x1618];
    /* fp+166C */ u32 x166C;
    /* fp+1670 */ unk_t x1670;
    /* fp+1674 */ u8 filler_x1674[0x1828 - 0x1674];
    /* fp+1828 */ s32 x1828;
    /* fp+182C */ struct dmg {
        /* fp+182C */ f32 x182c_behavior;
        /* fp+1830 */ f32 x1830_percent;
        /* fp+1834 */ f32 x1834;
        /* fp+1838 */ f32 x1838_percentTemp;
        /* fp+183C */ s32 x183C_applied;
        /* fp+1840 */ s32 x1840;
        /* fp+1844 */ f32 x1844_direction;
        /* fp+1848 */ s32 x1848_kb_angle;
        /* fp+184C */ s32 x184c_damaged_hurtbox;
        /* fp+1850 */ f32 x1850_forceApplied;
        /* fp+1854 */ Vec3 x1854_collpos;
        /* fp+1860 */ s32 x1860_dealt;
        /* fp+1864 */ s32 x1864;
        /* fp+1868 */ HSD_GObj* x1868_source;
        /* fp+186C */ s32 x186c;
        /* fp+1870 */ s32 x1870;
        /* fp+1874 */ s32 x1874;
        /* fp+1878 */ s32 x1878;
        /* fp+187C */ s32 x187c;
        /* fp+1880 */ s32 x1880;
        /* fp+1884 */ s32 x1884;
        /* fp+1888 */ s32 x1888;
        /* fp+188C */ s32 x188c;
        /* fp+1890 */ s32 x1890;
        /* fp+1894 */ s32 x1894;
        /* fp+1898 */ s32 x1898;
        /* fp+189C */ f32 x189C_unk_num_frames;
        /* fp+18A0 */ f32 x18a0;
        /// kb magnitude
        /* fp+18A4 */ f32 x18A4_knockbackMagnitude;
        /* fp+18A8 */ f32 x18A8;
        /// in frames
        /* fp+18AC */ s32 x18ac_time_since_hit;
        /* fp+18B0 */ f32 x18B0;
        /* fp+18B4 */ f32 x18B4_armor;
        /* fp+18B8 */ f32 x18B8;
        /* fp+18BC */ f32 x18BC;
        /* fp+18C0 */ s32 x18C0;
        /// damage source ply number
        /* fp+18C4 */ s32 x18c4_source_ply;
        /* fp+18C8 */ s32 x18C8;
        /* fp+18CC */ s32 x18CC;
        /* fp+18D0 */ s32 x18D0;
        /* fp+18D4 */ s32 x18d4;
        /* fp+18D8 */ s32 x18d8;
        /* fp+18DC */ s32 x18dc;
        /* fp+18E0 */ s32 x18e0;
        /* fp+18E4 */ s32 x18e4;
        /* fp+18E8 */ s32 x18e8;
        /// Last Move Instance This Player Was Hit by
        /* fp+18EC */ u16 x18ec_instancehitby;
        /* fp+18F0 */ s32 x18F0;
        /* fp+18F4 */ s32 x18F4;
        /* fp+18F8 */ u8 x18F8;
        /* fp+18F9 */ u8 x18f9;
        /* fp+18FA */ u16 x18fa_model_shift_frames;
        /* fp+18FC */ u8 x18FC;
        /* fp+18FD */ u8 x18FD;
        /* fp+1900 */ s32 x1900;
        /* fp+1904 */ s32 x1904;
        /* fp+1908 */ s32 x1908;
        /* fp+190C */ s32 x190C;
        /* fp+1910 */ s32 x1910;
        /* fp+1914 */ s32 x1914;
        /* fp+1918 */ s32 x1918;
        /* fp+191C */ f32 x191C;
        /* fp+1920 */ s32 x1920;
        /* fp+1924 */ s32 x1924;
        /* fp+1928 */ f32 x1928;
        /* fp+192C */ f32 x192c;
        /* fp+1930 */ s32 x1930;
        /* fp+1934 */ s32 x1934;
        /* fp+1938 */ s32 x1938;
        /* fp+193C */ s32 x193c;
        /* fp+1940 */ s32 x1940;
        /* fp+1944 */ s32 x1944;
        /* fp+1948 */ s32 x1948;
        /* fp+194C */ s32 x194C;
        /* fp+1950 */ s32 x1950;
        /* fp+1954 */ f32 x1954;
        /* fp+1958 */ f32 x1958;
        /* fp+195C */ f32 x195c_hitlag_frames;
    } dmg;
    /* fp+1960 */ f32 x1960_vibrateMult;
    /* fp+1964 */ f32 x1964;
    /* fp+1968 */ u8 x1968_jumpsUsed;
    /* fp+1969 */ u8 x1969_walljumpUsed;
    /* fp+196C */ f32 x196C_hitlag_mult;
    /* fp+1970 */ s32 x1970;
    /* fp+1974 */ HSD_GObj* item_gobj;
    /* fp+1978 */ HSD_GObj* x1978;
    /* fp+197C */ HSD_GObj* x197C;
    /* fp+1980 */ HSD_GObj* x1980;
    /* fp+1984 */ HSD_GObj* x1984_heldItemSpec;
    /* fp+1988 */ s32 x1988;
    /* fp+198C */ s32 x198C;
    /* fp+1990 */ s32 x1990;
    /* fp+1994 */ s32 x1994;
    /* fp+1998 */ f32 x1998_shieldHealth;
    /* fp+199C */ f32 x199C_shieldLightshieldAmt;
    /* fp+19A0 */ s32 x19A0_shieldDamageTaken;
    /* fp+19A4 */ s32 x19A4;
    /* fp+19A8 */ void* x19A8;
    /* fp+19AC */ float specialn_facing_dir;
    /* fp+19B0 */ s32 filler_x19B0;
    /* fp+19B4 */ f32 shield_unk0;
    /* fp+19B8 */ f32 shield_unk1;
    /* fp+19BC */ s32 x19BC_shieldDamageTaken3;
    /* fp+19C0 */ HitResult shield_hit;
    /* fp+19E4 */ HitResult reflect_hit;
    /* fp+1A08 */ HitResult absorb_hit;
    /* fp+1A2C */ struct {
        /* fp+1A2C */ f32 x1A2C_reflectHitDirection;
        /* fp+1A30 */ s32 x1A30_maxDamage;
        /* fp+1A34 */ f32 x1A34_damageMul;
        /* fp+1A38 */ f32 x1A38_speedMul;
        /// % damage over the maximum reflectable damage threshold
        /* fp+1A3C */ s32 x1A3C_damageOver;
    } ReflectAttr;
    /* fp+1A40 */ struct {
        /* fp+1A40 */ f32 x1A40_absorbHitDirection;
        /// unconfirmed?
        /* fp+1A44 */ s32 x1A44_damageTaken;
        /// unconfirmed?
        /* fp+1A48 */ s32 x1A48_hitsTaken;
    } AbsorbAttr;
    /* fp+1A4C */ f32 x1A4C;
    /* fp+1A50 */ s8 x1A50;
    /* fp+1A51 */ s8 x1A51;
    /* fp+1A52 */ u8 x1A52;
    /* fp+1A53 */ u8 x1A53;
    /* fp+1A54 */ s32 x1A54;
    /* fp+1A58 */ HSD_GObj* x1A58_interactedFighter;
    /* fp+1A5C */ HSD_GObj* x1A5C;
    /* fp+1A60 */ u32 x1A60;
    /* fp+1A64 */ s32 x1A64;
    /* fp+1A68 */ u16 x1A68;
    /* fp+1A6A */ u16 x1A6A;
    /* fp+1A6C */ f32 x1A6C;
    /* fp+1A70 */ Vec3 x1A70;
    /* fp+1A7C */ Vec3 x1A7C;
    /* fp+1A7C */ u8 filler_x1A7C[0x1A94 - 0x1A88];
    /* fp+1A94 */ u32 x1A94;
    /* fp+1A98 */ u32 x1A98;
    /* fp+1A9C */ s32 x1A9C;
    /* fp+1A9C */ u8 filler_x1A9C[0x2004 - 0x1AA0];
    /* fp+2008 */ s32 x2004;
    /* fp+2008 */ s32 x2008;
    /* fp+200C */ s32 x200C;
    /* fp+2010 */ s32 x2010;
    /* fp+2014 */ s32 x2014;
    /* fp+2018 */ s32 x2018;
    /* fp+201C */ s32 x201C;
    /* fp+2020 */ s8 x2020;
    /* fp+2021 */ s8 x2021;
    /* fp+2022 */ s8 x2022;
    /* fp+2024 */ s32 x2024;
    /* fp+2028 */ s32 x2028;
    /* fp+202C */ s32 x202C;
    /* fp+2030 */ s32 x2030;
    /* fp+2034 */ s32 x2034;
    /* fp+2038 */ s32 x2038;
    /* fp+203C */ s32 x203C;
    /* fp+2040 */ void* x2040;
    /* fp+203C */ u8 filler_x203C[0x2064 - 0x2044];
    /* fp+2064 */ s32 x2064_ledgeCooldown;
    /* fp+2068 */ s32 x2068_attackID;
    /* fp+206C */ u8 filler_x206C[0x2070 - 0x206C];
    /* fp+2070 */ union Struct2070 x2070;
    /* fp+2074 */ u8 filler_x2074[0x208C - 0x2074];
    /* fp+208C */ s32 x208C;
    /* fp+2090 */ u16 x2090;
    /* fp+2092 */ u16 x2092;
    /// GObj pointer of combo victim?
    /* fp+2094 */ HSD_GObj* x2094;
    /* fp+2098 */ u16 x2098;
    /* fp+209A */ u16 x209A;
    /* fp+209C */ s16 x209C;
    /* fp+20A0 */ HSD_JObj* x20A0_accessory;
    /* fp+20A4 */ s32 x20A4;
    /* fp+20A8 */ s32 x20A8;
    /* fp+20AC */ HSD_GObj* unk_gobj;
    /* fp+20B0 */ u8 filler_x20B0[0x2100 - 0x20B0];
    /* fp+2100 */ s8 x2100;
    /* fp+2101 */ u8 x2101_bits_0to6 : 7;
    /* fp+2101 */ u8 x2101_bits_8 : 1;
    /* fp+2102 */ s8 x2102;
    /* fp+2103 */ s8 x2103;
    /* fp+2104 */ s32 x2104;
    /* fp+2108 */ s32 x2108;
    /* fp+210C */ u8 x210C_walljumpInputTimer;
    /* fp+210C */ u8 filler_x210C[3];
    /* fp+2110 */ f32 x2110_walljumpWallSide;
    /* fp+2114 */ SmashAttr x2114_SmashAttr;
    /* fp+213C */ s32 x213C;
    /* fp+2140 */ f32 x2140;
    /* fp+2144 */ s32 x2144;
    /* fp+2148 */ s32 x2148;
    /* fp+214C */ s32 x214C;
    /* fp+2150 */ s32 x2150;
    /* fp+2154 */ s32 x2154;
    /* fp+2158 */ s32 x2158;
    /* fp+215C */ s32 x215C;
    /* fp+2160 */ s32 x2160;
    /* fp+2164 */ s32 x2164;
    /* fp+2168 */ s32 x2168;
    /* fp+216C */ f32 unk_grab_val;
    /* fp+2170 */ f32 x2170;
    /* fp+2174 */ u8 filler_x2174[0x2180 - 0x2174];
    /* fp+2180 */ s32 x2180;
    /* fp+2184 */ HSD_JObj* x2184;
    /* fp+2188 */ S32Vec2 x2188;
    /// callback struct. Not all of them used by fighter.c.
    struct cb {
        /* fp+2190 */ void (*x2190_callback_OnGrabFighter_Self)(HSD_GObj* fp);
        /* fp+2194 */ void (*x2194_callback)(HSD_GObj* fp);
        /* fp+2198 */ void (*x2198_callback_OnGrabFighter_Victim)(HSD_GObj*,
                                                                  HSD_GObj*);
        /* fp+219C */ void (*x219C_callback_IASA)(HSD_GObj* fp);
        /* fp+21A0 */ void (*x21A0_callback_Anim)(HSD_GObj* fp);
        /* fp+21A4 */ void (*x21A4_callback_Phys)(HSD_GObj* fp);
        /* fp+21A8 */ void (*x21A8_callback_Coll)(HSD_GObj* fp);
        /* fp+21AC */ void (*x21AC_callback_Cam)(HSD_GObj* fp);
        /* fp+21B0 */ void (*x21B0_callback_Accessory1)(HSD_GObj* fp);
        /* fp+21B4 */ void (*x21B4_callback_Accessory2)(HSD_GObj* fp);
        /* fp+21B8 */ void (*x21B8_callback_Accessory3)(HSD_GObj* fp);
        /* fp+21BC */ void (*x21BC_callback_Accessory4)(HSD_GObj* fp);
        /* fp+21C0 */ void (*x21C0_callback_OnGiveDamage)(HSD_GObj* fp);
        /* fp+21C4 */ void (*x21C4_callback_OnShieldHit)(HSD_GObj* fp);
        /* fp+21C8 */ void (*x21C8_callback_OnReflectHit)(HSD_GObj* fp);
        /* fp+21CC */ void (*x21CC_callback)(HSD_GObj* fp);
        /* fp+21D0 */ void (*x21D0_callback_EveryHitlag)(HSD_GObj* fp);
        /* fp+21D4 */ void (*x21D4_callback_EnterHitlag)(HSD_GObj* fp);
        /* fp+21D8 */ void (*x21D8_callback_ExitHitlag)(HSD_GObj* fp);
        /* fp+21DC */ void (*x21DC_callback_OnTakeDamage)(HSD_GObj* fp);
        /* fp+21E0 */ void (*x21E0_callback_OnDeath)(HSD_GObj* fp);
        /// @remarks Used. Internally Dead_Proc as evidenced by 800F5430.
        /* fp+21E4 */ void (*x21E4_callback_OnDeath2)(HSD_GObj* fp);
        /* fp+21E8 */ void (*x21E8_callback_OnDeath3)(HSD_GObj* fp);
        /* fp+21EC */ void (*x21EC_callback)(HSD_GObj* fp);
        /* fp+21F0 */ void (*x21F0_callback)(HSD_GObj* fp);
        /* fp+21F4 */ void (*x21F4_callback)(HSD_GObj* fp);
        /* fp+21F8 */ void (*x21F8_callback)(HSD_GObj* fp);
    } cb;
    /* fp+21FC */ UnkFlagStruct x21FC_flag;
    /* fp+21FC */ u8 filler_x21FC[0x2200 - 0x21FD];
    /* fp+2200 */ u32 cmd_vars[4];
    /* fp+2210 */ ThrowFlags throw_flags;
    /* fp+2214 */ f32 x2214;
    union {
        /* fp+2218 */ u8 x2218;
        /* fp+2218 */ struct {
            /* fp+2218:0 */ u8 x2218_b0 : 1;
            /* fp+2218:1 */ u8 x2218_b1 : 1;
            /* fp+2218:2 */ u8 x2218_b2 : 1;
            /* fp+2218:3 */ u8 x2218_b3 : 1;
            /* fp+2218:4 */ u8 x2218_b4 : 1;
            /* fp+2218:5 */ u8 x2218_b5 : 1;
            /* fp+2218:6 */ u8 x2218_b6 : 1;
            /* fp+2218:7 */ u8 x2218_b7 : 1;
        };
    };
    union {
        /* fp+2219 */ u8 x2219;
        /* fp+2219 */ struct {
            /* fp+2219:0 */ u8 x2219_b0 : 1;
            /* fp+2219:1 */ u8 x2219_b1 : 1;
            /* fp+2219:2 */ u8 x2219_b2 : 1;
            /* fp+2219:3 */ u8 x2219_b3 : 1;
            /* fp+2219:4 */ u8 x2219_b4 : 1;
            /* fp+2219:5 */ u8 x2219_b5 : 1;
            /* fp+2219:6 */ u8 x2219_b6 : 1;
            /* fp+2219:7 */ u8 x2219_b7 : 1;
        };
    };
    /* fp+221A */ UnkFlagStruct x221A_flag;
    /* fp+221B */ union {
        /* fp+221B */ u8 x221B;
        /* fp+221B */ struct {
            /* fp+221B:0 */ u8 x221B_b0 : 1;
            /* fp+221B:1 */ u8 x221B_b1 : 1;
            /* fp+221B:2 */ u8 x221B_b2 : 1;
            /* fp+221B:3 */ u8 x221B_b3 : 1;
            /* fp+221B:4 */ u8 x221B_b4 : 1;
            /* fp+221B:5 */ u8 x221B_b5 : 1;
            /* fp+221B:6 */ u8 x221B_b6 : 1;
            /* fp+221B:7 */ u8 x221B_b7 : 1;
        };
    };
    /* fp+221C */ union {
        /* fp+221C */ struct {
            /* fp+221C */ UnkFlagStruct x221C_flag;
            /* fp+221D */ UnkFlagStruct x221D_flag;
        };
        /* fp+221C */ struct {
            /* fp+221C:0 */ u16 x221C_u16_x : 7;
            /* fp+221C:7 */ u16 x221C_u16_y : 3;
            /* fp+221D:2 */ u16 x221C_u16_z : 6;
        };
    };
    /* fp+221E */ UnkFlagStruct x221E_flag;
    /* fp+221F */ UnkFlagStruct x221F_flag;
    /* fp+2220 */ union {
        /* fp+2220 */ struct {
            /* fp+2220:0 */ u8 b0 : 3;
            /* fp+2220:3 */ u8 b3 : 1;
            /* fp+2220:4 */ u8 b4 : 1;
            /* fp+2220:5 */ u8 b5 : 1;
            /* fp+2220:6 */ u8 b6 : 1;
            /* fp+2220:7 */ u8 b7 : 1;
        } bits;
        /* fp+2220 */ u8 flags;
    } x2220_flag;
    /* fp+2221 */ UnkFlagStruct x2221_flag;
    /* fp+2222:0 */ u8 x2222_b0 : 1;
    /* fp+2222:1 */ u8 x2222_b1 : 1;
    /* fp+2222:2 */ u8 x2222_b2 : 1;
    /* fp+2222:3 */ u8 x2222_b3 : 1;
    /* fp+2222:4 */ u8 x2222_b4 : 1;
    /* fp+2222:5 */ u8 x2222_b5 : 1;
    /* fp+2222:6 */ u8 x2222_b6 : 1;
    /* fp+2222:7 */ u8 x2222_b7 : 1;
    /* fp+2223 */ UnkFlagStruct x2223_flag;
    /* fp+2224 */ UnkFlagStruct x2224_flag;
    /* fp+2225:0 */ u8 x2225_b0 : 1;
    /* fp+2225:1 */ u8 x2225_b1 : 1;
    /* fp+2225:2 */ u8 x2225_b2 : 1;
    /* fp+2225:3 */ u8 x2225_b3 : 1;
    /* fp+2225:4 */ u8 x2225_b4 : 1;
    /* fp+2225:5 */ u8 x2225_b5 : 1;
    /* fp+2225:6 */ u8 x2225_b6 : 1;
    /* fp+2225:7 */ u8 x2225_b7 : 1;
    /* fp+2226 */ UnkFlagStruct x2226_flag;
    /* fp+2227 */ UnkFlagStruct x2227_flag;
    /// UnkFlagStruct does not quite work
    /* fp+2228 */ struct {
        /* fp+2228:0 */ u8 b0 : 1;
        /* fp+2228:1 */ u8 b1 : 1;
        /* fp+2228:2 */ u8 b2 : 1;
        /* fp+2228:3 */ u8 b3 : 2;
        /* fp+2228:5 */ u8 b5 : 1;
        /* fp+2228:6 */ u8 b6 : 1;
        /* fp+2228:7 */ u8 b7 : 1;
    } x2228_flag;
    /* fp+2229:0 */ u8 x2229_b0 : 1;
    /* fp+2229:1 */ u8 x2229_b1 : 1;
    /* fp+2229:2 */ u8 x2229_b2 : 1;
    /* fp+2229:3 */ u8 x2229_b3 : 1;
    /* fp+2229:4 */ u8 x2229_b4 : 1;
    /* fp+2229:5 */ u8 x2229_b5_no_normal_motion : 1;
    /* fp+2229:6 */ u8 x2229_b6 : 1;
    /* fp+2229:7 */ u8 x2229_b7 : 1;
    /* fp+222A */ UnkFlagStruct x222A_flag;
    /* fp+222B */ u8 filler_x222B;
    /* fp+222C */ union Fighter_FighterVars {
        /* fp+222C */ u8 _[FIGHTERVARS_SIZE];
        /* fp+222C */ struct ftCaptain_FighterVars ca, gn;
        /* fp+222C */ struct ftDonkey_FighterVars dk;
        /* fp+222C */ struct ftFox_FighterVars fx, fc;
        /* fp+222C */ struct ftGameWatch_FighterVars gw;
        /* fp+222C */ struct ftKirby_FighterVars kb;
        /* fp+222C */ struct ftKoopa_FighterVars kp, gk;
        /* fp+222C */ struct ftLink_FighterVars lk, cl;
        /* fp+222C */ struct ftLuigi_FighterVars lg;
        /* fp+222C */ struct ftMario_FighterVars mr;
        /* fp+222C */ struct ftMars_FighterVars ms;
        /* fp+222C */ struct ftMasterhand_FighterVars mh, ch;
        /* fp+222C */ struct ftMewtwo_FighterVars mt;
        /* fp+222C */ struct ftNess_FighterVars ns;
        /* fp+222C */ struct ftPeach_FighterVars pe;
        /* fp+222C */ struct ftPikachu_FighterVars pk, pc;
        /* fp+222C */ struct ftPopo_FighterVars pp, nn;
        /* fp+222C */ struct ftPurin_FighterVars pr;
        /* fp+222C */ struct ftSamus_FighterVars ss;
        /* fp+222C */ struct ftSandbag_FighterVars sb;
        /* fp+222C */ struct ftSeak_FighterVars sk;
        /* fp+222C */ struct ftYoshi_FighterVars ys;
        /* fp+222C */ struct ftZakoBoy_FighterVars bo, gl;
        /* fp+222C */ struct ftZelda_FighterVars zd;
    } fv;
    /* fp+232C */ s32 x232C;
    /* fp+2330 */ Vec2 x2330;
    /* fp+2338 */ Vec2 x2338;
    /// @at{2340} @sz{AC}
    /* fp+2340 */ union Fighter_MotionVars {
        /* fp+2340 */ u8 _[0x23EC - 0x2340];
        /* fp+2340 */ union ftCaptain_MotionVars ca, gn;
        /* fp+2340 */ union ftCommon_MotionVars co;
        /* fp+2340 */ union ftDonkey_MotionVars dk;
        /* fp+2340 */ union ftFox_MotionVars fx, fc;
        /* fp+2340 */ union ftGameWatch_MotionVars gw;
        /* fp+2340 */ union ftKoopa_MotionVars kp;
        /* fp+2340 */ union ftLuigi_MotionVars lg;
        /* fp+2340 */ union ftLk_MotionVars lk;
        /* fp+2340 */ union ftMario_MotionVars mr, dr;
        /* fp+2340 */ union ftMars_MotionVars ms, fe;
        /* fp+2340 */ union ftMasterHand_MotionVars mh, ch;
        /* fp+2340 */ union ftMewtwo_MotionVars mt;
        /* fp+2340 */ union ftNess_MotionVars ns;
        /* fp+2340 */ union ftPe_MotionVars pe;
        /* fp+2340 */ union ftPikachu_MotionVars pk, pc;
        /* fp+2340 */ union ftPurin_MotionVars pr;
        /* fp+2340 */ union ftSamus_MotionVars ss;
        /* fp+2340 */ union ftSeak_MotionVars sk;
        /* fp+2340 */ union ftYoshi_MotionVars ys;
        /* fp+2340 */ union ftZelda_MotionVars zd;
    } mv;
};

#endif
