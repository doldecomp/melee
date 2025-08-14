#ifndef MELEE_GR_FORWARD_H
#define MELEE_GR_FORWARD_H

#include <baselib/forward.h>

typedef struct grDynamicAttr_UnkStruct grDynamicAttr_UnkStruct;
typedef struct Ground Ground;
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
    InternalStageID_Unk01,

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

    SHRINEROUTE,

    STAGEKIND_UNK32,
    STAGEKIND_UNK33,
    STAGEKIND_UNK34,
    STAGEKIND_UNK35,
    STAGEKIND_UNK36,
    STAGEKIND_UNK37,
    STAGEKIND_UNK38,
    STAGEKIND_UNK39,

    /// Home run contest
    HOMERUN = 0x43,
} InternalStageId;

typedef struct unkCastle unkCastle;

typedef void (*unkCastleCallback)(void*, struct unkCastle*);
typedef void (*unkCastleCallback2)(void*, struct unkCastle*, Ground_GObj*);

#endif
