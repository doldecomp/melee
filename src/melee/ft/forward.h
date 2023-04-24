#ifndef MELEE_FT_FORWARD_H
#define MELEE_FT_FORWARD_H

#include <platform.h>
#include <baselib/forward.h>

#include <stddef.h>
#include <dolphin/mtx/types.h>

#define FIGHTERVARS_SIZE 0x100

typedef struct MotionState MotionState;
typedef struct Fighter Fighter;
typedef struct Fighter_CostumeStrings Fighter_CostumeStrings;
typedef struct Fighter_DemoStrings Fighter_DemoStrings;
typedef struct UnkFloat6_Camera UnkFloat6_Camera;
typedef u32 MotionFlags;

typedef void (*Fighter_ItemEvent)(HSD_GObj* this, bool arg1);
typedef void (*Fighter_UnkMtxEvent)(HSD_GObj* this, int arg1, Mtx vmtx);
typedef void (*Fighter_ModelEvent)(Fighter* fp, int arg1, bool arg2);
typedef char* (*Fighter_MotionFileStringGetter)(enum_t arg0);
typedef void (*Fighter_UnkPtrEvent)(s32 arg0, s32* arg1, s32* arg2);

typedef enum FighterKind {
    FTKIND_MARIO,
    FTKIND_FOX,
    FTKIND_CAPTAIN,
    FTKIND_DONKEY,
    FTKIND_KIRBY,
    FTKIND_KOOPA,
    FTKIND_LINK,
    FTKIND_SEAK,
    FTKIND_NESS,
    FTKIND_PEACH,
    FTKIND_POPO,
    FTKIND_NANA,
    FTKIND_PIKACHU,
    FTKIND_SAMUS,
    FTKIND_YOSHI,
    FTKIND_PURIN,
    FTKIND_MEWTWO,
    FTKIND_LUIGI,
    FTKIND_MARS,
    FTKIND_ZELDA,
    FTKIND_CLINK,
    FTKIND_DRMARIO,
    FTKIND_FALCO,
    FTKIND_PICHU,
    FTKIND_GAMEWATCH,
    FTKIND_GANON,
    FTKIND_EMBLEM,
    FTKIND_MASTERH,
    FTKIND_CREZYH,
    FTKIND_BOY,
    FTKIND_GIRL,
    FTKIND_GKOOPS,
    FTKIND_SANDBAG,
    FTKIND_NONE,
    FTKIND_MAX = FTKIND_NONE
} FighterKind;

typedef enum CharacterKind {
    CKIND_CAPTAIN,   // Captain Falcon (Captain)
    CKIND_DONKEY,    // Donkey Kong (Donkey)
    CKIND_FOX,       // Fox
    CKIND_GAMEWATCH, // Mr. Game & Watch (GameWatch)
    CKIND_KIRBY,     // Kirby
    CKIND_KOOPA,     // Bowser (Koopa)
    CKIND_LINK,      // Link
    CKIND_LUIGI,     // Luigi
    CKIND_MARIO,     // Mario
    CKIND_MARS,      // Marth (Mars)
    CKIND_MEWTWO,    // Mewtwo
    CKIND_NESS,      // Ness
    CKIND_PEACH,     // Peach
    CKIND_PIKACHU,   // Pikachu
    CKIND_POPONANA,  // Ice Climbers (Popo & Nana)
    CKIND_PURIN,     // Jigglypuff (Purin)
    CKIND_SAMUS,     // Samus
    CKIND_YOSHI,     // Yoshi
    CKIND_ZELDA,     // Zelda (ZE->SE)
    CKIND_SEAK,      // Sheik (SE->ZE)
    CKIND_FALCO,     // Falco
    CKIND_CLINK,     // Young Link (CLink)
    CKIND_DRMARIO,   // Dr. Mario
    CKIND_EMBLEM,    // Roy (Emblem)
    CKIND_PICHU,     // Pichu
    CKIND_GANON,     // Ganondorf (Ganon)
    CKIND_MASTERH,   // Master Hand (MasterH)
    CKIND_BOY,       // Male Wireframe (Boy)
    CKIND_GIRL,      // Female Wireframe (Girl)
    CKIND_GKOOPS,    // Giga Bowser (GKoops)
    CKIND_CREZYH,    // Crazy Hand (CrezyH)
    CHKIND_SANDBAG,  // Sandbag
    CHKIND_POPO,     // Popo
    CHKIND_NONE,     // None
    CHKIND_MAX = CHKIND_NONE
} CharacterKind;

static MotionFlags const Ft_MF_None ATTRIBUTE_USED = 0;

static MotionFlags const Ft_MF_KeepFastFall ATTRIBUTE_USED = 1 << 0;

static MotionFlags const Ft_MF_KeepGfx ATTRIBUTE_USED = 1 << 1;

/// Preserve full body collision state
static MotionFlags const Ft_MF_KeepColAnimHitStatus ATTRIBUTE_USED = 1 << 2;

/// Keep hitboxes
static MotionFlags const Ft_MF_SkipHit ATTRIBUTE_USED = 1 << 3;

/// Ignore model state change ?
static MotionFlags const Ft_MF_SkipModel ATTRIBUTE_USED = 1 << 4;

static MotionFlags const Ft_MF_SkipAnimVel ATTRIBUTE_USED = 1 << 5;

static MotionFlags const Ft_MF_Unk06 ATTRIBUTE_USED = 1 << 6;

/// Ignore switching to character's "hurt" textures ?
static MotionFlags const Ft_MF_SkipMatAnim ATTRIBUTE_USED = 1 << 7;

/// Resets thrower GObj pointer to NULL if false?
static MotionFlags const Ft_MF_SkipThrowException ATTRIBUTE_USED = 1 << 8;

static MotionFlags const Ft_MF_KeepSfx ATTRIBUTE_USED = 1 << 9;

/// Ignore Parasol state change
static MotionFlags const Ft_MF_SkipParasol ATTRIBUTE_USED = 1 << 10;

/// Ignore rumble update?
static MotionFlags const Ft_MF_SkipRumble ATTRIBUTE_USED = 1 << 11;

static MotionFlags const Ft_MF_SkipColAnim ATTRIBUTE_USED = 1 << 12;

/// Keep respawn platform?
static MotionFlags const Ft_MF_KeepAccessory ATTRIBUTE_USED = 1 << 13;

/// Run all Subaction Events up to the current animation frame
static MotionFlags const Ft_MF_UpdateCmd ATTRIBUTE_USED = 1 << 14;

static MotionFlags const Ft_MF_SkipNametagVis ATTRIBUTE_USED = 1 << 15;

/// Assume this is for individual bones?
static MotionFlags const Ft_MF_KeepColAnimPartHitStatus ATTRIBUTE_USED = 1
                                                                         << 16;

static MotionFlags const Ft_MF_KeepSwordTrail ATTRIBUTE_USED = 1 << 17;

/// Used by Ness during Up/Down Smash
static MotionFlags const Ft_MF_SkipItemVis ATTRIBUTE_USED = 1 << 18;

/// Skips updating bit 5 of #Fighter::x2222_flag?
static MotionFlags const Ft_MF_Unk19 ATTRIBUTE_USED = 1 << 19;

static MotionFlags const Ft_MF_UnkUpdatePhys ATTRIBUTE_USED = 1 << 20;

/// Sets anim rate to 0 and some other stuff
static MotionFlags const Ft_MF_FreezeState ATTRIBUTE_USED = 1 << 21;

static MotionFlags const Ft_MF_SkipModelPartVis ATTRIBUTE_USED = 1 << 22;

static MotionFlags const Ft_MF_SkipMetalB ATTRIBUTE_USED = 1 << 23;

static MotionFlags const Ft_MF_Unk24 ATTRIBUTE_USED = 1 << 24;

static MotionFlags const Ft_MF_SkipAttackCount ATTRIBUTE_USED = 1 << 25;

static MotionFlags const Ft_MF_SkipModelFlags ATTRIBUTE_USED = 1 << 26;

static MotionFlags const Ft_MF_Unk27 ATTRIBUTE_USED = 1 << 27;

static MotionFlags const Ft_MF_SkipHitStun ATTRIBUTE_USED = 1 << 28;

/// Keeps current fighter animation?
static MotionFlags const Ft_MF_SkipAnim ATTRIBUTE_USED = 1 << 29;

static MotionFlags const Ft_MF_Unk30 ATTRIBUTE_USED = 1 << 30;

/// Unused?
static MotionFlags const Ft_MF_Unk31 ATTRIBUTE_USED = 1 << 31;

// Ledge Grab Macros

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
    FtPart_TransN2
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

#endif
