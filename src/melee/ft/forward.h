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

static u32 const FtStateChange_None ATTRIBUTE_USED = 0;

static u32 const FtStateChange_PreserveFastFall ATTRIBUTE_USED = 1 << 0;

static u32 const FtStateChange_PreserveGfx ATTRIBUTE_USED = 1 << 1;

/// Preserve full body collision state
static u32 const FtStateChange_PreserveColAnimHitStatus ATTRIBUTE_USED = 1
                                                                         << 2;

/// Keep hitboxes
static u32 const FtStateChange_SkipUpdateHit ATTRIBUTE_USED = 1 << 3;

/// Ignore model state change ?
static u32 const FtStateChange_SkipUpdateModel ATTRIBUTE_USED = 1 << 4;

static u32 const FtStateChange_SkipUpdateAnimVel ATTRIBUTE_USED = 1 << 5;

static u32 const FtStateChange_Unk_6 ATTRIBUTE_USED = 1 << 6;

/// Ignore switching to character's "hurt" textures ?
static u32 const FtStateChange_SkipUpdateMatAnim ATTRIBUTE_USED = 1 << 7;

/// Resets thrower GObj pointer to NULL if false?
static u32 const FtStateChange_SkipUpdateThrowException ATTRIBUTE_USED = 1
                                                                         << 8;

static u32 const FtStateChange_PreserveSfx ATTRIBUTE_USED = 1 << 9;

/// Ignore Parasol state change
static u32 const FtStateChange_SkipUpdateParasol ATTRIBUTE_USED = 1 << 10;

/// Ignore rumble update?
static u32 const FtStateChange_SkipUpdateRumble ATTRIBUTE_USED = 1 << 11;

static u32 const FtStateChange_SkipUpdateColAnim ATTRIBUTE_USED = 1 << 12;

/// Keep respawn platform?
static u32 const FtStateChange_PreserveAccessory ATTRIBUTE_USED = 1 << 13;

/// Run all Subaction Events up to the current animation frame
static u32 const FtStateChange_UpdateCmd ATTRIBUTE_USED = 1 << 14;

static u32 const FtStateChange_SkipUpdateNametagVis ATTRIBUTE_USED = 1 << 15;

/// Assume this is for individual bones?
static u32 const FtStateChange_PreserveColaNimPartHitStatus ATTRIBUTE_USED =
    1 << 16;

static u32 const FtStateChange_PreserveSwordTrail ATTRIBUTE_USED = 1 << 17;

/// Used by Ness during Up/Down Smash
static u32 const FtStateChange_SkipUpdateItemVis ATTRIBUTE_USED = 1 << 18;

/// Skips updating bit 5 of #Fighter::x2222_flag?
static u32 const FtStateChange_Unk_19 ATTRIBUTE_USED = 1 << 19;

static u32 const FtStateChange_Unk_UpdatePhys ATTRIBUTE_USED = 1 << 20;

/// Sets anim rate to 0 and some other stuff
static u32 const FtStateChange_FreezeState ATTRIBUTE_USED = 1 << 21;

static u32 const FtStateChange_SkipUpdateModelPartVis ATTRIBUTE_USED = 1 << 22;

static u32 const FtStateChange_SkipUpdateMetalB ATTRIBUTE_USED = 1 << 23;

static u32 const FtStateChange_Unk_24 ATTRIBUTE_USED = 1 << 24;

static u32 const FtStateChange_SkipUpdateAttackCount ATTRIBUTE_USED = 1 << 25;

static u32 const FtStateChange_SkipUpdateModelFlag ATTRIBUTE_USED = 1 << 26;

static u32 const FtStateChange_Unk_27 ATTRIBUTE_USED = 1 << 27;

static u32 const FtStateChange_SkipUpdateHitStunFlag ATTRIBUTE_USED = 1 << 28;

/// Keeps current fighter animation?
static u32 const FtStateChange_SkipUpdateAnim ATTRIBUTE_USED = 1 << 29;

static u32 const FtStateChange_Unk_30 ATTRIBUTE_USED = 1 << 30;

/// Unused?
static u32 const FtStateChange_Unk_31 ATTRIBUTE_USED = 1 << 31;

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
    FtMoveId_Unk00,
    FtMoveId_Unk01,
    FtMoveId_Attack11,
    FtMoveId_Unk03,
    FtMoveId_Unk04,
    FtMoveId_Attack100,
    FtMoveId_Unk06,
    FtMoveId_Unk07,
    FtMoveId_Unk08,
    FtMoveId_AttackLw3,
    FtMoveId_AttackS4,
    FtMoveId_AttackHi4,
    FtMoveId_AttackLw4,
    FtMoveId_AttackAirN,
    FtMoveId_Unk14,
    FtMoveId_AttackAirB,
    FtMoveId_AttackAirHi,
    FtMoveId_Unk17,
    FtMoveId_SpecialN,
    FtMoveId_SpecialS,
    FtMoveId_SpecialHi,
    FtMoveId_SpecialLw,
    FtMoveId_Unk22,
    FtMoveId_Unk23,
    FtMoveId_Unk24,
    FtMoveId_Unk25,
    FtMoveId_Unk26,
    FtMoveId_Unk27,
    FtMoveId_Unk28,
    FtMoveId_Unk29,
    FtMoveId_Unk30,
    FtMoveId_Unk31,
    FtMoveId_Unk32,
    FtMoveId_Unk33,
    FtMoveId_Unk34,
    FtMoveId_Unk35,
    FtMoveId_Unk36,
    FtMoveId_Unk37,
    FtMoveId_Unk38,
    FtMoveId_Unk39,
    FtMoveId_Unk40,
    FtMoveId_Unk41,
    FtMoveId_Unk42,
    FtMoveId_Unk43,
    FtMoveId_Unk44,
    FtMoveId_Unk45,
    FtMoveId_Unk46,
    FtMoveId_Unk47,
    FtMoveId_Unk48,
    FtMoveId_Unk49,
    FtMoveId_Unk50,
    FtMoveId_Unk51,
    FtMoveId_Unk52,
    FtMoveId_Unk53,
    FtMoveId_Unk54,
    FtMoveId_Unk55,
    FtMoveId_Unk56,
    FtMoveId_Unk57,
    FtMoveId_Unk58,
    FtMoveId_Unk59,
    FtMoveId_Unk60,
    FtMoveId_Unk61,
    FtMoveId_Unk62,
    FtMoveId_Unk63,
    FtMoveId_Unk64,
    FtMoveId_SwordSwing,
    FtMoveId_Unk66,
    FtMoveId_Unk67,
    FtMoveId_Unk68,
    FtMoveId_BatSwing,
    FtMoveId_Unk70,
    FtMoveId_Unk71,
    FtMoveId_Unk72,
    FtMoveId_ParasolSwing,
    FtMoveId_Unk74,
    FtMoveId_Unk75,
    FtMoveId_Unk76,
    FtMoveId_HarisenSwing,
    FtMoveId_Unk78,
    FtMoveId_Unk79,
    FtMoveId_Unk80,
    FtMoveId_StarRodSwing,
    FtMoveId_Unk82,
    FtMoveId_Unk83,
    FtMoveId_Unk84,
    FtMoveId_LipstickSwing,
    FtMoveId_Unk86,
    FtMoveId_Unk87,
    FtMoveId_Unk88,
    FtMoveId_Unk89,
} FtMoveId;

#endif
