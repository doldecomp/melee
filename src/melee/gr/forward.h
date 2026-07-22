#ifndef MELEE_GR_FORWARD_H
#define MELEE_GR_FORWARD_H

#include <baselib/forward.h>

struct grCorneria_GroundVars;

typedef struct grDynamicAttr_UnkStruct grDynamicAttr_UnkStruct;
typedef struct Ground Ground;
typedef struct IceMountainParams IceMountainParams;
typedef struct StageInfo StageInfo;
typedef struct UnkArchiveStruct UnkArchiveStruct;
typedef struct UnkBgmStruct UnkBgmStruct;
typedef struct UnkStage6B0 UnkStage6B0;
typedef struct UnkStageDatInternal UnkStageDatInternal;
typedef struct UnkStageDat UnkStageDat;

#ifdef M2C
typedef struct Ground_GObj Ground_GObj;
struct Ground_GObj {
    /*  +0 */ u16 classifier;
    /*  +2 */ u8 p_link;
    /*  +3 */ u8 gx_link;
    /*  +4 */ u8 p_priority;
    /*  +5 */ u8 render_priority;
    /*  +6 */ u8 obj_kind;
    /*  +7 */ u8 user_data_kind;
    /*  +8 */ Ground_GObj* next;
    /*  +C */ Ground_GObj* prev;
    /* +10 */ Ground_GObj* next_gx;
    /* +14 */ Ground_GObj* prev_gx;
    /* +18 */ HSD_GObjProc* proc;
    /* +1C */ void (*rendered)(Ground_GObj* gobj, s32 code);
    /* +20 */ u64 gxlink_prios;
    /* +28 */ HSD_JObj* hsd_obj;
    /* +2C */ Ground* user_data;
    /* +30 */ void (*user_data_remove_func)(Ground* data);
    /* +34 */ void* x34_unk;
};
#else
typedef HSD_GObj Ground_GObj;
#endif

/// @todo Finish values, use @c PascalCase
typedef enum InternalStageId {
    InternalStageID_Unk00,
    TEST,

    /// Princess Peach's Castle
    CASTLE,

    /// Rainbow Cruise
    RCRUISE,

    /// Kongo Jungle
    KONGO,

    /// Jungle Japes
    GARDEN,

    /// Great Bay
    GREATBAY,

    /// Hyrule Temple
    SHRINE,

    /// Brinstar
    ZEBES,

    /// Brinstar Depths
    KRAID,

    /// Yoshi's Story
    STORY,

    /// Yoshi's Island
    YORSTER,

    /// Fountain of Dreams
    IZUMI,

    /// Green Greens
    GREENS,

    /// Corneria
    CORNERIA,

    /// Venom
    VENOM,

    /// Pokemon Stadium
    PSTADIUM,

    /// Poke Floats
    PURA,

    /// Mute City
    MUTECITY,

    /// Big Blue
    BIGBLUE,

    /// Onett
    ONETT,

    /// Fourside
    FOURSIDE,

    /// Icicle Mountain
    ICEMTN,

    InternalStageID_Unk23,

    /// Mushroom Kingdom
    INISHIE1,

    /// Mushroom Kingdom II
    INISHIE2,

    InternalStageID_Unk26,

    /// Flat Zone
    FLATZONE,

    /// Dream Land
    OLDPUPUPU,

    /// Yoshi's Island (64)
    OLDYOSHI,

    /// Kongo Jungle (64)
    OLDKONGO,

    KINOKOROUTE,
    SHRINEROUTE,
    ZEBESROUTE,
    BIGBLUEROUTE,

    InternalStageID_Unk35,

    BATTLE,
    LAST,
    FIGUREGET,
    PUSHON,
    TMARIO,
    TCAPTAIN,
    TCLINK,
    TDONKEY,
    TDRMARIO,
    TFALCO,
    TFOX,
    TICECLIMBER,
    TKIRBY,
    TKOOPA,
    TLINK,
    TLUIGI,
    TMARS,
    TMEWTWO,
    TNESS,
    TPEACH,
    TPICHU,
    TPIKACHU,
    TPURIN,
    TSAMUS,
    TSEAK,
    TYOSHI,
    TZELDA,
    TGAMEWATCH,
    TEMBLEM,
    TGANON,
    HEAL,
    /// Home run contest
    HOMERUN,
    FIGURE1,
    FIGURE2,
    FIGURE3
} InternalStageId;

/// External stage IDs, the public stage numbering used by
/// #StartMeleeRules::xE and the Stage_802251E8 argument. #stage_id_map
/// converts them to #InternalStageId values; entries 0x21+ are
/// single-player, event, and other mode variants.
typedef enum ExternalStageId {
    ExternalStageID_Unk00,
    ExternalStageID_TEST,
    ExternalStageID_IZUMI,
    ExternalStageID_PSTADIUM,
    ExternalStageID_CASTLE,
    ExternalStageID_KONGO,
    ExternalStageID_ZEBES,
    ExternalStageID_CORNERIA,
    ExternalStageID_STORY,
    ExternalStageID_ONETT,
    ExternalStageID_MUTECITY,
    ExternalStageID_RCRUISE,
    ExternalStageID_GARDEN,
    ExternalStageID_GREATBAY,
    ExternalStageID_SHRINE,
    ExternalStageID_KRAID,
    ExternalStageID_YORSTER,
    ExternalStageID_GREENS,
    ExternalStageID_FOURSIDE,
    ExternalStageID_INISHIE1,
    ExternalStageID_INISHIE2,
    ExternalStageID_Unk21, // maps to InternalStageID_Unk26
    ExternalStageID_VENOM,
    ExternalStageID_PURA,
    ExternalStageID_BIGBLUE,
    ExternalStageID_ICEMTN,
    ExternalStageID_Unk26, // second Icicle Mountain entry
    ExternalStageID_FLATZONE,
    ExternalStageID_OLDPUPUPU,
    ExternalStageID_OLDYOSHI,
    ExternalStageID_OLDKONGO,
    ExternalStageID_BATTLE,
    ExternalStageID_LAST,

    ExternalStageID_BIGBLUEROUTE = 0x49,
    ExternalStageID_HEAL = 0x55,
} ExternalStageId;

typedef struct unkCastle unkCastle;

typedef void (*unkCastleCallback)(void*, struct unkCastle*);
typedef void (*unkCastleCallback2)(void*, struct unkCastle*, Ground_GObj*);
typedef int (*GrIceMtSegmentLookup)(Ground_GObj*);

#endif
