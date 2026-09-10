#ifndef MELEE_FT_FORWARD_H
#define MELEE_FT_FORWARD_H

#include <Runtime/platform.h>

#include <melee/gr/forward.h>
#include <melee/lb/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <dolphin/types.h>

#define HSD_GOBJ_CLASS_FIGHTER 4
#define HSD_GOBJ_PLINK_FIGHTER 8

#define FIGHTERVARS_SIZE 0xF8

typedef enum_t FtMotionId;
typedef struct ArticleDynamicBones ArticleDynamicBones;
typedef struct CostumeTObjList CostumeTObjList;
typedef struct DObjList DObjList;
typedef struct Fighter Fighter;
typedef struct Fighter_804D653C_t Fighter_804D653C_t;
typedef struct Fighter_CostumeStrings Fighter_CostumeStrings;
typedef struct Fighter_DemoStrings Fighter_DemoStrings;
typedef struct Fighter_x1670_t Fighter_x1670_t;
typedef struct FighterBone FighterBone;
typedef struct FighterPartsTable FighterPartsTable;
typedef struct ft_800898B4_t ft_800898B4_t;
typedef struct ftCo_803C6594_t ftCo_803C6594_t;
typedef struct ftCo_DatAttrs_xBC_t ftCo_DatAttrs_xBC_t;
typedef struct ftCommonData ftCommonData;
typedef struct ftData ftData;
typedef struct ftData_UnkCountStruct ftData_UnkCountStruct;
typedef struct ftData_x58_t ftData_x58_t;
typedef struct ftData_x8 ftData_x8;
typedef struct ftData_x8_x8 ftData_x8_x8;
typedef struct ftDynamics ftDynamics;
typedef struct ftLk_SpecialN_Vec3Group ftLk_SpecialN_Vec3Group;
typedef struct ftMaterial_UnkTevStruct ftMaterial_UnkTevStruct;
typedef struct FtPartsDesc FtPartsDesc;
typedef struct FtPartsVis FtPartsVis;
typedef struct FtPartsVisLookup FtPartsVisLookup;
typedef struct FtSFX FtSFX;
typedef struct gmScriptEventDefault gmScriptEventDefault;
typedef struct IKState IKState;
typedef struct KirbyHatStruct KirbyHatStruct;
typedef struct MotionState MotionState;
typedef struct TempS TempS;
typedef struct UnkCostumeStruct UnkCostumeStruct;
typedef struct UnkFloat6_Camera UnkFloat6_Camera;
typedef struct UnkPlBonusBits UnkPlBonusBits;
typedef u32 MotionFlags;

#ifdef M2C
typedef struct Fighter_GObj Fighter_GObj;
struct Fighter_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ Fighter_GObj* next;
    /*  +C */ Fighter_GObj* prev;
    /* +10 */ Fighter_GObj* next_gx;
    /* +14 */ Fighter_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(Fighter_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ Fighter* user_data;
    /* +30 */ void (*user_data_remove_func)(Fighter* data);
    /* +34 */ void* x34_unk;
};
#else
#include <sysdolphin/baselib/gobj.h>
typedef struct HSD_GObj Fighter_GObj;
#endif

typedef char* (*Fighter_MotionFileStringGetter)(enum_t arg0);
typedef void (*Fighter_ItemEvent)(HSD_GObj* gobj, bool arg1);
typedef void (*Fighter_ModelEvent)(Fighter* fp, int arg1, bool arg2);
typedef void (*Fighter_UnkMtxEvent)(HSD_GObj* gobj, int arg1, Mtx vmtx);
typedef void (*Fighter_UnkPtrEvent)(int arg0, int* arg1, int* arg2);
typedef void (*FighterEvent)(Fighter* fp);
typedef void (*FtCmd)(Fighter_GObj*, CommandInfo*);
typedef void (*FtCmd2)(Fighter_GObj*, CommandInfo*, int);
typedef bool (*ftDevice_Callback0)(Ground_GObj*, Fighter_GObj*, Vec3*);

typedef enum FighterKind {
    /* 00 */ Ft_Kind_Mario,
    /* 01 */ Ft_Kind_Fox,
    /* 02 */ Ft_Kind_Captain,
    /* 03 */ Ft_Kind_Donkey,
    /* 04 */ Ft_Kind_Kirby,
    /* 05 */ Ft_Kind_Koopa,
    /* 06 */ Ft_Kind_Link,
    /* 07 */ Ft_Kind_Seak,
    /* 08 */ Ft_Kind_Ness,
    /* 09 */ Ft_Kind_Peach,
    /* 0A */ Ft_Kind_Popo,
    /* 0B */ Ft_Kind_Nana,
    /* 0C */ Ft_Kind_Pikachu,
    /* 0D */ Ft_Kind_Samus,
    /* 0E */ Ft_Kind_Yoshi,
    /* 0F */ Ft_Kind_Purin,
    /* 10 */ Ft_Kind_Mewtwo,
    /* 11 */ Ft_Kind_Luigi,
    /* 12 */ Ft_Kind_Mars,
    /* 13 */ Ft_Kind_Zelda,
    /* 14 */ Ft_Kind_CLink,
    /* 15 */ Ft_Kind_DrMario,
    /* 16 */ Ft_Kind_Falco,
    /* 17 */ Ft_Kind_Pichu,
    /* 18 */ Ft_Kind_GameWatch,
    /* 19 */ Ft_Kind_Ganon,
    /* 1A */ Ft_Kind_Emblem,
    /* 1B */ Ft_Kind_MasterH,
    /* 1C */ Ft_Kind_CrezyH,
    /* 1D */ Ft_Kind_Boy,
    /* 1E */ Ft_Kind_Girl,
    /* 1F */ Ft_Kind_GKoops,
    /* 20 */ Ft_Kind_Sandbag,
    /* 21 */ Ft_Kind_None,
    /* 21 */ Ft_Kind_Max = Ft_Kind_None
} FighterKind;

typedef enum CharacterKind {
    /* 00 */ CKind_Captain,   // Captain Falcon (Captain)
    /* 01 */ CKind_Donkey,    // Donkey Kong (Donkey)
    /* 02 */ CKind_Fox,       // Fox
    /* 03 */ CKind_GameWatch, // Mr. Game & Watch (GameWatch)
    /* 04 */ CKind_Kirby,     // Kirby
    /* 05 */ CKind_Koopa,     // Bowser (Koopa)
    /* 06 */ CKind_Link,      // Link
    /* 07 */ CKind_Luigi,     // Luigi
    /* 08 */ CKind_Mario,     // Mario
    /* 09 */ CKind_Mars,      // Marth (Mars)
    /* 0A */ CKind_Mewtwo,    // Mewtwo
    /* 0B */ CKind_Ness,      // Ness
    /* 0C */ CKind_Peach,     // Peach
    /* 0D */ CKind_Pikachu,   // Pikachu
    /* 0E */ CKind_PopoNana,  // Ice Climbers (Popo & Nana)
    /* 0F */ CKind_Purin,     // Jigglypuff (Purin)
    /* 10 */ CKind_Samus,     // Samus
    /* 11 */ CKind_Yoshi,     // Yoshi
    /* 12 */ CKind_Zelda,     // Zelda (ZE->SE)
    /* 13 */ CKind_Seak,      // Sheik (SE->ZE)
    /* 14 */ CKind_Falco,     // Falco
    /* 15 */ CKind_CLink,     // Young Link (CLink)
    /* 16 */ CKind_DrMario,   // Dr. Mario
    /* 17 */ CKind_Emblem,    // Roy (Emblem)
    /* 18 */ CKind_Pichu,     // Pichu
    /* 19 */ CKind_Ganon,     // Ganondorf (Ganon)

    /* 1A */ CKind_Playable_Count,

    /* 1A */ CKind_MasterH = CKind_Playable_Count, // Master Hand (MasterH)
    /* 1B */ CKind_Boy,                            // Male Wireframe (Boy)
    /* 1C */ CKind_Girl,                           // Female Wireframe (Girl)
    /* 1D */ CKind_GKoops,                         // Giga Bowser (GKoops)
    /* 1E */ CKind_CrezyH,                         // Crazy Hand (CrezyH)
    /* 1F */ ChKind_Sandbag,                       // Sandbag
    /* 20 */ ChKind_Popo,                          // Popo
    /* 21 */ ChKind_None,                          // None
    /* 21 */ ChKind_Max = ChKind_None
} CharacterKind;

static MotionFlags const Ft_MF_None = 0;

static MotionFlags const Ft_MF_KeepFastFall = 1 << 0;

static MotionFlags const Ft_MF_KeepGfx = 1 << 1;

/// Preserve full body collision state
static MotionFlags const Ft_MF_KeepColAnimHitStatus = 1 << 2;

/// Keep hitboxes
static MotionFlags const Ft_MF_SkipHit = 1 << 3;

/// Ignore model state change ?
static MotionFlags const Ft_MF_SkipModel = 1 << 4;

static MotionFlags const Ft_MF_SkipAnimVel = 1 << 5;

static MotionFlags const Ft_MF_Unk06 = 1 << 6;

/// Ignore switching to character's "hurt" textures ?
static MotionFlags const Ft_MF_SkipMatAnim = 1 << 7;

/// Resets thrower GObj pointer to NULL if false?
static MotionFlags const Ft_MF_SkipThrowException = 1 << 8;

static MotionFlags const Ft_MF_KeepSfx = 1 << 9;

/// Ignore Parasol state change
static MotionFlags const Ft_MF_SkipParasol = 1 << 10;

/// Ignore rumble update?
static MotionFlags const Ft_MF_SkipRumble = 1 << 11;

static MotionFlags const Ft_MF_SkipColAnim = 1 << 12;

/// Keep respawn platform?
static MotionFlags const Ft_MF_KeepAccessory = 1 << 13;

/// Run all Subaction Events up to the current animation frame
static MotionFlags const Ft_MF_UpdateCmd = 1 << 14;

static MotionFlags const Ft_MF_SkipNametagVis = 1 << 15;

/// Assume this is for individual bones?
static MotionFlags const Ft_MF_KeepColAnimPartHitStatus = 1 << 16;

static MotionFlags const Ft_MF_KeepSwordTrail = 1 << 17;

/// Used by Ness during Up/Down Smash
static MotionFlags const Ft_MF_SkipItemVis = 1 << 18;

/// Skips updating bit 5 of #Fighter::x2222_flag?
static MotionFlags const Ft_MF_Unk19 = 1 << 19;

static MotionFlags const Ft_MF_UnkUpdatePhys = 1 << 20;

/// Sets anim rate to 0 and some other stuff
static MotionFlags const Ft_MF_FreezeState = 1 << 21;

static MotionFlags const Ft_MF_SkipModelPartVis = 1 << 22;

static MotionFlags const Ft_MF_SkipMetalB = 1 << 23;

static MotionFlags const Ft_MF_Unk24 = 1 << 24;

static MotionFlags const Ft_MF_SkipAttackCount = 1 << 25;

static MotionFlags const Ft_MF_SkipModelFlags = 1 << 26;

static MotionFlags const Ft_MF_Unk27 = 1 << 27;

static MotionFlags const Ft_MF_SkipHitStun = 1 << 28;

/// Keeps current fighter animation?
static MotionFlags const Ft_MF_SkipAnim = 1 << 29;

static MotionFlags const Ft_MF_Unk30 = 1 << 30;

/// Unused?
static MotionFlags const Ft_MF_Unk31 = 1 << 31;

/// Ledge Grab Macros

#define CLIFFCATCH_BOTH 0
#define CLIFFCATCH_LEFT -1
#define CLIFFCATCH_RIGHT 1

typedef enum Fighter_Part {
    FtPart_TopN,
    FtPart_TransN,
    FtPart_XRotN,
    FtPart_YRotN,
    FtPart_HipN,
    FtPart_WaistN,
    FtPart_LLegJA,
    FtPart_LLegJ,
    FtPart_LKneeJ,
    FtPart_LFootJA,
    FtPart_LFootJ,
    FtPart_RLegJA,
    FtPart_RLegJ,
    FtPart_RKneeJ,
    FtPart_RFootJA,
    FtPart_RFootJ,
    FtPart_BustN,
    FtPart_LShoulderN,
    FtPart_LShoulderJA,
    FtPart_LShoulderJ,
    FtPart_LArmJ,
    FtPart_LHandN,
    FtPart_L1stNa,
    FtPart_L1stNb,
    FtPart_L2ndNa,
    FtPart_L2ndNb,
    FtPart_L3rdNa,
    FtPart_L3rdNb,
    FtPart_L4thNa,
    FtPart_L4thNb,
    FtPart_LThumbNa,
    FtPart_LThumbNb,
    FtPart_LHandNb,
    FtPart_NeckN,
    FtPart_HeadN,
    FtPart_RShoulderN,
    FtPart_RShoulderJA,
    FtPart_RShoulderJ,
    FtPart_RArmJ,
    FtPart_RHandN,
    FtPart_R1stNa,
    FtPart_R1stNb,
    FtPart_R2ndNa,
    FtPart_R2ndNb,
    FtPart_R3rdNa,
    FtPart_R3rdNb,
    FtPart_R4thNa,
    FtPart_R4thNb,
    FtPart_RThumbNa,
    FtPart_RThumbNb,
    FtPart_RHandNb,
    FtPart_ThrowN,
    FtPart_TransN2,
    FtPart_56 = 56,
    FtPart_109 = 109,
} Fighter_Part;

typedef enum FtWalkType {
    FtWalkType_Slow,
    FtWalkType_Middle,
    FtWalkType_Fast,
} FtWalkType;

typedef enum FtMoveId {
    FtMoveId_None,
    FtMoveId_Default,
    FtMoveId_Attack11,
    FtMoveId_Attack12,
    FtMoveId_Attack13,
    FtMoveId_Attack100,
    FtMoveId_AttackDash,
    FtMoveId_AttackS3,
    FtMoveId_AttackHi3,
    FtMoveId_AttackLw3,
    FtMoveId_AttackS4,
    FtMoveId_AttackHi4,
    FtMoveId_AttackLw4,
    FtMoveId_AttackAirN,
    FtMoveId_AttackAirF,
    FtMoveId_AttackAirB,
    FtMoveId_AttackAirHi,
    FtMoveId_AttackAirLw,
    FtMoveId_SpecialN,
    FtMoveId_SpecialS,
    FtMoveId_SpecialHi,
    FtMoveId_SpecialLw,
    FtMoveId_KbSpecialNMr,
    FtMoveId_KbSpecialNFx,
    FtMoveId_KbSpecialNCa,
    FtMoveId_KbSpecialNDk,
    FtMoveId_KbSpecialNKp,
    FtMoveId_KbSpecialNLk,
    FtMoveId_KbSpecialNSk,
    FtMoveId_KbSpecialNNs,
    FtMoveId_KbSpecialNPe,
    FtMoveId_KbSpecialNPp,
    FtMoveId_KbSpecialNPk,
    FtMoveId_KbSpecialNSs,
    FtMoveId_KbSpecialNYs,
    FtMoveId_KbSpecialNPr,
    FtMoveId_KbSpecialNMt,
    FtMoveId_KbSpecialNLg,
    FtMoveId_KbSpecialNMs,
    FtMoveId_KbSpecialNZd,
    FtMoveId_KbSpecialNCl,
    FtMoveId_KbSpecialNDr,
    FtMoveId_KbSpecialNFc,
    FtMoveId_KbSpecialNPc,
    FtMoveId_KbSpecialNGw,
    FtMoveId_KbSpecialNGn,
    FtMoveId_KbSpecialNFe,
    FtMoveId_KbSpecialNGk,
    FtMoveId_Unk48,
    FtMoveId_Unk49,
    FtMoveId_DownAttackU,
    FtMoveId_DownAttackD,
    FtMoveId_CatchAttack,
    FtMoveId_ThrowF,
    FtMoveId_ThrowB,
    FtMoveId_ThrowHi,
    FtMoveId_ThrowLw,
    FtMoveId_CargoThrowF,
    FtMoveId_CargoThrowB,
    FtMoveId_CargoThrowHi,
    FtMoveId_CargoThrowLw,
    FtMoveId_CliffAttackSlow,
    FtMoveId_CliffAttackQuick,
    FtMoveId_SwordSwing1,
    FtMoveId_SwordSwing3,
    FtMoveId_SwordSwing4,
    FtMoveId_SwordSwingDash,
    FtMoveId_BatSwing1,
    FtMoveId_BatSwing3,
    FtMoveId_BatSwing4,
    FtMoveId_BatSwingDash,
    FtMoveId_ParasolSwing1,
    FtMoveId_ParasolSwing3,
    FtMoveId_ParasolSwing4,
    FtMoveId_ParasolSwingDash,
    FtMoveId_HarisenSwing1,
    FtMoveId_HarisenSwing3,
    FtMoveId_HarisenSwing4,
    FtMoveId_HarisenSwingDash,
    FtMoveId_StarRodSwing1,
    FtMoveId_StarRodSwing3,
    FtMoveId_StarRodSwing4,
    FtMoveId_StarRodSwingDash,
    FtMoveId_LipstickSwing1,
    FtMoveId_LipstickSwing3,
    FtMoveId_LipstickSwing4,
    FtMoveId_LipstickSwingDash,
    FtMoveId_Parasol,
    FtMoveId_LGunShoot,
    FtMoveId_FireFlowerShoot,
    FtMoveId_Screw,
    FtMoveId_ScopeRapid,
    FtMoveId_ScopeFire,
    FtMoveId_Hammer,
    FtMoveId_WarpStarFall,
} FtMoveId;

typedef enum SmashState {
    SmashState_None,
    SmashState_PreCharge,
    SmashState_Charging,
    SmashState_Release,
} SmashState;

typedef enum ftCommon_BuryType {
    BuryType_Unk0,
    BuryType_Unk1,
    BuryType_Unk2,
    BuryType_Unk3,
} ftCommon_BuryType;

enum {
    Ft_Dynamics_NumMax = 10,
};

enum EntityKind {
    EntityKind_None,
    EntityKind_Fighter,
    EntityKind_Item,
    EntityKind_UNKNOWN,
};

typedef enum GroundOrAir {
    GA_Ground,
    GA_Air,
} GroundOrAir;

/// @todo ::ftCo_800B2AFC
typedef enum CpuKind {
    CpuKind_0,
    CpuKind_1,
    CpuKind_2,
    CpuKind_3,
    CpuKind_4,
    CpuKind_5,
    CpuKind_Nana,
    CpuKind_7,
    CpuKind_8,
    CpuKind_9,
    CpuKind_10,
    CpuKind_11,
    CpuKind_12,
    CpuKind_13,
    CpuKind_14,
    CpuKind_15,
    CpuKind_16,
    CpuKind_17,
    CpuKind_18,
    CpuKind_19,
    CpuKind_20,
    CpuKind_21,
    CpuKind_22,
    CpuKind_23,
    CpuKind_24,
    CpuKind_25,
    CpuKind_26,
    CpuKind_27,
    CpuKind_28,
    CpuKind_29,
} CpuKind;

#endif
