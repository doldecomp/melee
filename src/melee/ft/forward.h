#ifndef MELEE_FT_FORWARD_H
#define MELEE_FT_FORWARD_H

#include <platform.h>
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>

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

typedef enum Fighter_MotionStateChangeFlags {
    FtStateChange_None,
    FtStateChange_PreserveFastFall = (1 << 0),
    FtStateChange_PreserveGfx = (1 << 1),

    /// Preserve full body collision state
    FtStateChange_PreserveColAnimHitStatus = (1 << 2),

    /// Keep hitboxes
    FtStateChange_SkipUpdateHit = (1 << 3),

    /// Ignore model state change (?)
    FtStateChange_SkipUpdateModel = (1 << 4),

    FtStateChange_SkipUpdateAnimVel = (1 << 5),
    FtStateChange_Unk_6 = (1 << 6),

    /// Ignore switching to character's "hurt" textures (?)
    FtStateChange_SkipUpdateMatAnim = (1 << 7),

    /// Resets thrower GObj pointer to NULL if false?
    FtStateChange_SkipUpdateThrowException = (1 << 8),

    FtStateChange_PreserveSfx = (1 << 9),

    /// Ignore Parasol state change
    FtStateChange_SkipUpdateParasol = (1 << 10),

    /// Ignore rumble update?
    FtStateChange_SkipUpdateRumble = (1 << 11),

    FtStateChange_SkipUpdateColAnim = (1 << 12),

    /// Keep respawn platform?
    FtStateChange_PreserveAccessory = (1 << 13),

    /// Run all Subaction Events up to the current animation frame
    FtStateChange_UpdateCmd = (1 << 14),

    FtStateChange_SkipUpdateNametagVis = (1 << 15),

    /// Assume this is for individual bones?
    FtStateChange_PreserveColaNimPartHitStatus = (1 << 16),

    FtStateChange_PreserveSwordTrail = (1 << 17),

    /// Used by Ness during Up/Down Smash
    FtStateChange_SkipUpdateItemVis = (1 << 18),

    /// Skips updating bit 5 of #Fighter::x2222_flag?
    FtStateChange_Unk_19 = (1 << 19),

    FtStateChange_Unk_UpdatePhys = (1 << 20),

    /// Sets anim rate to 0 and some other stuff
    FtStateChange_FreezeState = (1 << 21),

    FtStateChange_SkipUpdateModelPartVis = (1 << 22),
    FtStateChange_SkipUpdateMetalB = (1 << 23),
    FtStateChange_Unk_24 = (1 << 24),
    FtStateChange_SkipUpdateAttackCount = (1 << 25),
    FtStateChange_SkipUpdateModelFlag = (1 << 26),
    FtStateChange_Unk_27 = (1 << 27),
    FtStateChange_SkipUpdateHitStunFlag = (1 << 28),

    /// Keeps current fighter animation?
    FtStateChange_SkipUpdateAnim = (1 << 29),

    FtStateChange_Unk_30 = (1 << 30),

    /// Unused?
    FtStateChange_Unk_31 = (1 << 31),
} Fighter_MotionStateChangeFlags;

// Ledge Grab Macros

#define CLIFFCATCH_BOTH 0
#define CLIFFCATCH_LEFT -1
#define CLIFFCATCH_RIGHT 1

typedef enum _ftPart {
    TopN,
    TransN,
    XRotN,
    YRotN,
    HipN,
    WaistN,
    LLegJA,
    LLegJ,
    LKneeJ,
    LFootJA,
    LFootJ,
    RLegJA,
    RLegJ,
    RKneeJ,
    RFootJA,
    RFootJ,
    BustN,
    LShoulderN,
    LShoulderJA,
    LShoulderJ,
    LArmJ,
    LHandN,
    L1stNa,
    L1stNb,
    L2ndNa,
    L2ndNb,
    L3rdNa,
    L3rdNb,
    L4thNa,
    L4thNb,
    LThumbNa,
    LThumbNb,
    LHandNb,
    NeckN,
    HeadN,
    RShoulderN,
    RShoulderJA,
    RShoulderJ,
    RArmJ,
    RHandN,
    R1stNa,
    R1stNb,
    R2ndNa,
    R2ndNb,
    R3rdNa,
    R3rdNb,
    R4thNa,
    R4thNb,
    RThumbNa,
    RThumbNb,
    RHandNb,
    ThrowN,
    TransN2
} ftPart;

#endif
