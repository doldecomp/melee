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

/**
 * Selects the @c Gr??.dat archive, indexing #Ground_803DFEDC. Several #StKind
 * values can share one #GrKind.
 *
 * Member names follow the per-stage @c gr*.c module names the asserts embed.
 */
typedef enum GrKind {
    /* 00 */ Gr_Kind_Unk00,
    /* 01 */ Gr_Kind_Test,
    /* 02 */ Gr_Kind_Castle,   // Princess Peach's Castle
    /* 03 */ Gr_Kind_RCruise,  // Rainbow Cruise
    /* 04 */ Gr_Kind_Kongo,    // Kongo Jungle
    /* 05 */ Gr_Kind_Garden,   // Jungle Japes
    /* 06 */ Gr_Kind_GreatBay, // Great Bay
    /* 07 */ Gr_Kind_Shrine,   // Hyrule Temple
    /* 08 */ Gr_Kind_Zebes,    // Brinstar
    /* 09 */ Gr_Kind_Kraid,    // Brinstar Depths
    /* 0A */ Gr_Kind_Story,    // Yoshi's Story
    /* 0B */ Gr_Kind_Yorster,  // Yoshi's Island
    /* 0C */ Gr_Kind_Izumi,    // Fountain of Dreams
    /* 0D */ Gr_Kind_Greens,   // Green Greens
    /* 0E */ Gr_Kind_Corneria, // Corneria
    /* 0F */ Gr_Kind_Venom,    // Venom
    /* 10 */ Gr_Kind_PStadium, // Pokemon Stadium
    /* 11 */ Gr_Kind_Pura,     // Poke Floats
    /* 12 */ Gr_Kind_MuteCity, // Mute City
    /* 13 */ Gr_Kind_BigBlue,  // Big Blue
    /* 14 */ Gr_Kind_Onett,    // Onett
    /* 15 */ Gr_Kind_Fourside, // Fourside
    /* 16 */ Gr_Kind_Icemt,    // Icicle Mountain
    /* 17 */ Gr_Kind_Unk23,
    /* 18 */ Gr_Kind_Inishie1, // Mushroom Kingdom
    /* 19 */ Gr_Kind_Inishie2, // Mushroom Kingdom II
    /* 1A */ Gr_Kind_Unk26,
    /* 1B */ Gr_Kind_Flatzone,  // Flat Zone
    /* 1C */ Gr_Kind_OldPupupu, // Dream Land
    /* 1D */ Gr_Kind_OldYoshi,  // Yoshi's Island (64)
    /* 1E */ Gr_Kind_OldKongo,  // Kongo Jungle (64)
    /* 1F */ Gr_Kind_KinokoRoute,
    /* 20 */ Gr_Kind_ShrineRoute,
    /* 21 */ Gr_Kind_ZebesRoute,
    /* 22 */ Gr_Kind_BigBlueRoute,
    /* 23 */ Gr_Kind_Unk35,
    /* 24 */ Gr_Kind_Battle, // Battlefield
    /* 25 */ Gr_Kind_Last,   // Final Destination
    /* 26 */ Gr_Kind_FigureGet,
    /* 27 */ Gr_Kind_Pushon,
    /* 28 */ Gr_Kind_TMario,
    /* 29 */ Gr_Kind_TCaptain,
    /* 2A */ Gr_Kind_TClink,
    /* 2B */ Gr_Kind_TDonkey,
    /* 2C */ Gr_Kind_TDrmario,
    /* 2D */ Gr_Kind_TFalco,
    /* 2E */ Gr_Kind_TFox,
    /* 2F */ Gr_Kind_TIceclimber,
    /* 30 */ Gr_Kind_TKirby,
    /* 31 */ Gr_Kind_TKoopa,
    /* 32 */ Gr_Kind_TLink,
    /* 33 */ Gr_Kind_TLuigi,
    /* 34 */ Gr_Kind_TMars,
    /* 35 */ Gr_Kind_TMewtwo,
    /* 36 */ Gr_Kind_TNess,
    /* 37 */ Gr_Kind_TPeach,
    /* 38 */ Gr_Kind_TPichu,
    /* 39 */ Gr_Kind_TPikachu,
    /* 3A */ Gr_Kind_TPurin,
    /* 3B */ Gr_Kind_TSamus,
    /* 3C */ Gr_Kind_TSeak,
    /* 3D */ Gr_Kind_TYoshi,
    /* 3E */ Gr_Kind_TZelda,
    /* 3F */ Gr_Kind_TGamewatch,
    /* 40 */ Gr_Kind_TEmblem,
    /* 41 */ Gr_Kind_TGanon,
    /* 42 */ Gr_Kind_Heal,
    /* 43 */ Gr_Kind_Homerun, // Home run contest
    /* 44 */ Gr_Kind_Figure1,
    /* 45 */ Gr_Kind_Figure2,
    /* 46 */ Gr_Kind_Figure3,
} GrKind;

/**
 * The numbering used by #StartMeleeRules::xE and Stage_802251E8. #stage_id_map
 * converts it to #GrKind, and each archive's @c grGroundParam list is keyed by
 * it; entries 0x21+ are single-player, event, and other mode variants.
 *
 * Both names come from ground.c's report
 * `not found stage param in DAT(grkind=%d stkind=%d,num=%d)`, which passes
 * #StageInfo::grkind and then this value. Member names follow the stage list
 * the develop-mode menu prints.
 */
typedef enum StKind {
    /* 00 */ St_Kind_Dummy,
    /* 01 */ St_Kind_Test,
    /* 02 */ St_Kind_Izumi,
    /* 03 */ St_Kind_PStadium,
    /* 04 */ St_Kind_Castle,
    /* 05 */ St_Kind_Kongo,
    /* 06 */ St_Kind_Zebes,
    /* 07 */ St_Kind_Corneria,
    /* 08 */ St_Kind_Story,
    /* 09 */ St_Kind_Onett,
    /* 0A */ St_Kind_MuteCity,
    /* 0B */ St_Kind_RCruise,
    /* 0C */ St_Kind_Garden,
    /* 0D */ St_Kind_GreatBay,
    /* 0E */ St_Kind_Shrine,
    /* 0F */ St_Kind_Kraid,
    /* 10 */ St_Kind_Yoster, // the gr module spells it yorster
    /* 11 */ St_Kind_Greens,
    /* 12 */ St_Kind_Fourside,
    /* 13 */ St_Kind_Inishie1,
    /* 14 */ St_Kind_Inishie2,
    /* 15 */ St_Kind_Akaneia,
    /* 16 */ St_Kind_Venom,
    /* 17 */ St_Kind_Pura,
    /* 18 */ St_Kind_BigBlue,
    /* 19 */ St_Kind_Icemt,
    /* 1A */ St_Kind_Icetop,
    /* 1B */ St_Kind_Flatzone,
    /* 1C */ St_Kind_OldPupupu,
    /* 1D */ St_Kind_OldYoshi,
    /* 1E */ St_Kind_OldKongo,
    /* 1F */ St_Kind_Battle,
    /* 20 */ St_Kind_Last,
    /* 49 */ St_Kind_BigBlueRoute = 0x49,
    /* 55 */ St_Kind_Heal = 0x55,
} StKind;

typedef struct unkCastle unkCastle;

typedef void (*unkCastleCallback)(void*, struct unkCastle*);
typedef void (*unkCastleCallback2)(void*, struct unkCastle*, Ground_GObj*);
typedef int (*GrIceMtSegmentLookup)(Ground_GObj*);

#endif
