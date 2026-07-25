#ifndef MELEE_GR_FORWARD_H
#define MELEE_GR_FORWARD_H

#include <baselib/forward.h>

struct grCorneria_GroundVars;

typedef struct grDynamicAttr_UnkStruct grDynamicAttr_UnkStruct;
typedef struct Ground Ground;
typedef struct StageInfo StageInfo;
typedef struct GroundParam GroundParam;
typedef struct StageParam StageParam;
typedef struct UnkArchiveStruct UnkArchiveStruct;
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

/// Selects the @c Gr??.dat archive, indexing #Ground_803DFEDC. Several #StKind
/// values can share one #GrKind.
///
/// @todo Finish values, use @c PascalCase
typedef enum GrKind {
    GrKind_Unk00,
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

    GrKind_Unk23,

    /// Mushroom Kingdom
    INISHIE1,

    /// Mushroom Kingdom II
    INISHIE2,

    GrKind_Unk26,

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

    GrKind_Unk35,

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
} GrKind;

/// The numbering used by #StartMeleeRules::xE and Stage_802251E8.
/// #stage_id_map converts it to #GrKind, and each archive's @c grGroundParam
/// list is keyed by it; entries 0x21+ are single-player, event, and other mode
/// variants.
///
/// Both names come from ground.c's report
/// `not found stage param in DAT(grkind=%d stkind=%d,num=%d)`, which passes
/// #StageInfo::internal_stage_id for grkind and this value for stkind.
typedef enum StKind {
    StKind_Unk00,
    StKind_TEST,
    StKind_IZUMI,
    StKind_PSTADIUM,
    StKind_CASTLE,
    StKind_KONGO,
    StKind_ZEBES,
    StKind_CORNERIA,
    StKind_STORY,
    StKind_ONETT,
    StKind_MUTECITY,
    StKind_RCRUISE,
    StKind_GARDEN,
    StKind_GREATBAY,
    StKind_SHRINE,
    StKind_KRAID,
    StKind_YORSTER,
    StKind_GREENS,
    StKind_FOURSIDE,
    StKind_INISHIE1,
    StKind_INISHIE2,
    StKind_Unk21, // maps to GrKind_Unk26
    StKind_VENOM,
    StKind_PURA,
    StKind_BIGBLUE,
    StKind_ICEMTN,
    /// Second Icicle Mountain entry. @c GrIm.dat has no stage-param row for
    /// it, so loading it spins in Ground_801C28CC's not-found loop.
    StKind_Unk26,
    StKind_FLATZONE,
    StKind_OLDPUPUPU,
    StKind_OLDYOSHI,
    StKind_OLDKONGO,
    StKind_BATTLE,
    StKind_LAST,

    StKind_BIGBLUEROUTE = 0x49,
    StKind_HEAL = 0x55,
} StKind;

typedef struct unkCastle unkCastle;

typedef void (*unkCastleCallback)(void*, struct unkCastle*);
typedef void (*unkCastleCallback2)(void*, struct unkCastle*, Ground_GObj*);
typedef int (*GrIceMtSegmentLookup)(Ground_GObj*);

#endif
