#ifndef MELEE_GR_FORWARD_H
#define MELEE_GR_FORWARD_H

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

struct grCorneria_GroundVars;
typedef struct grDynamicAttr_UnkStruct grDynamicAttr_UnkStruct;
typedef struct GrJoint GrJoint;
typedef struct Ground Ground;
typedef struct GroundParam GroundParam;
typedef struct StageData StageData;
typedef struct StageInfo StageInfo;
typedef struct StageParam StageParam;
typedef struct UnkArchiveStruct UnkArchiveStruct;
typedef struct unkCastle unkCastle;
typedef struct UnkStageDat UnkStageDat;
typedef struct UnkStageDatInternal UnkStageDatInternal;

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

/** @remarks
 * Selects the @c Gr??.dat archive, indexing #stage_datas. Several #StKind
 * values can share one #GrKind.
 *
 * Member names follow the per-stage @c gr*.c module names the asserts embed.
 */
typedef enum GrKind {
    /* 0x00 */ Gr_Kind_Unk00,
    /* 0x01 */ Gr_Kind_Test,
    /* 0x02 */ Gr_Kind_Castle,   // Princess Peach's Castle
    /* 0x03 */ Gr_Kind_RCruise,  // Rainbow Cruise
    /* 0x04 */ Gr_Kind_Kongo,    // Kongo Jungle
    /* 0x05 */ Gr_Kind_Garden,   // Jungle Japes
    /* 0x06 */ Gr_Kind_GreatBay, // Great Bay
    /* 0x07 */ Gr_Kind_Shrine,   // Hyrule Temple
    /* 0x08 */ Gr_Kind_Zebes,    // Brinstar
    /* 0x09 */ Gr_Kind_Kraid,    // Brinstar Depths
    /* 0x0A */ Gr_Kind_Story,    // Yoshi's Story
    /* 0x0B */ Gr_Kind_Yorster,  // Yoshi's Island
    /* 0x0C */ Gr_Kind_Izumi,    // Fountain of Dreams
    /* 0x0D */ Gr_Kind_Greens,   // Green Greens
    /* 0x0E */ Gr_Kind_Corneria, // Corneria
    /* 0x0F */ Gr_Kind_Venom,    // Venom
    /* 0x10 */ Gr_Kind_PStadium, // Pokemon Stadium
    /* 0x11 */ Gr_Kind_Pura,     // Poke Floats
    /* 0x12 */ Gr_Kind_MuteCity, // Mute City
    /* 0x13 */ Gr_Kind_BigBlue,  // Big Blue
    /* 0x14 */ Gr_Kind_Onett,    // Onett
    /* 0x15 */ Gr_Kind_Fourside, // Fourside
    /* 0x16 */ Gr_Kind_Icemt,    // Icicle Mountain
    /* 0x17 */ Gr_Kind_Unk23,
    /* 0x18 */ Gr_Kind_Inishie1, // Mushroom Kingdom
    /* 0x19 */ Gr_Kind_Inishie2, // Mushroom Kingdom II
    /* 0x1A */ Gr_Kind_Unk26,
    /* 0x1B */ Gr_Kind_Flatzone,  // Flat Zone
    /* 0x1C */ Gr_Kind_OldPupupu, // Dream Land
    /* 0x1D */ Gr_Kind_OldYoshi,  // Yoshi's Island (64)
    /* 0x1E */ Gr_Kind_OldKongo,  // Kongo Jungle (64)
    /* 0x1F */ Gr_Kind_KinokoRoute,
    /* 0x20 */ Gr_Kind_ShrineRoute,
    /* 0x21 */ Gr_Kind_ZebesRoute,
    /* 0x22 */ Gr_Kind_BigBlueRoute,
    /* 0x23 */ Gr_Kind_Unk35,
    /* 0x24 */ Gr_Kind_Battle, // Battlefield
    /* 0x25 */ Gr_Kind_Last,   // Final Destination
    /* 0x26 */ Gr_Kind_FigureGet,
    /* 0x27 */ Gr_Kind_Pushon,
    /* 0x28 */ Gr_Kind_TMario,
    /* 0x29 */ Gr_Kind_TCaptain,
    /* 0x2A */ Gr_Kind_TClink,
    /* 0x2B */ Gr_Kind_TDonkey,
    /* 0x2C */ Gr_Kind_TDrmario,
    /* 0x2D */ Gr_Kind_TFalco,
    /* 0x2E */ Gr_Kind_TFox,
    /* 0x2F */ Gr_Kind_TIceclimber,
    /* 0x30 */ Gr_Kind_TKirby,
    /* 0x31 */ Gr_Kind_TKoopa,
    /* 0x32 */ Gr_Kind_TLink,
    /* 0x33 */ Gr_Kind_TLuigi,
    /* 0x34 */ Gr_Kind_TMars,
    /* 0x35 */ Gr_Kind_TMewtwo,
    /* 0x36 */ Gr_Kind_TNess,
    /* 0x37 */ Gr_Kind_TPeach,
    /* 0x38 */ Gr_Kind_TPichu,
    /* 0x39 */ Gr_Kind_TPikachu,
    /* 0x3A */ Gr_Kind_TPurin,
    /* 0x3B */ Gr_Kind_TSamus,
    /* 0x3C */ Gr_Kind_TSeak,
    /* 0x3D */ Gr_Kind_TYoshi,
    /* 0x3E */ Gr_Kind_TZelda,
    /* 0x3F */ Gr_Kind_TGamewatch,
    /* 0x40 */ Gr_Kind_TEmblem,
    /* 0x41 */ Gr_Kind_TGanon,
    /* 0x42 */ Gr_Kind_Heal,
    /* 0x43 */ Gr_Kind_Homerun, // Home run contest
    /* 0x44 */ Gr_Kind_Figure1,
    /* 0x45 */ Gr_Kind_Figure2,
    /* 0x46 */ Gr_Kind_Figure3,
} GrKind;

/** @remarks
 * The numbering used by #StartMeleeRules::xE and Stage_802251E8.
 * #stage_id_map converts it to #GrKind, and each archive's @c grGroundParam
 * list is keyed by it; entries 0x21+ are single-player, event, and other mode
 * variants.
 *
 * Both names come from ground.c's report
 * `not found stage param in DAT(grkind=%d stkind=%d,num=%d)`, which passes
 * #StageInfo::grkind and then this value. Member names follow the stage list
 * the develop-mode menu prints.
 */
typedef enum StKind {
    /* 0x00 */ St_Kind_Dummy,
    /* 0x01 */ St_Kind_Test,
    /* 0x02 */ St_Kind_Izumi,
    /* 0x03 */ St_Kind_PStadium,
    /* 0x04 */ St_Kind_Castle,
    /* 0x05 */ St_Kind_Kongo,
    /* 0x06 */ St_Kind_Zebes,
    /* 0x07 */ St_Kind_Corneria,
    /* 0x08 */ St_Kind_Story,
    /* 0x09 */ St_Kind_Onett,
    /* 0x0A */ St_Kind_MuteCity,
    /* 0x0B */ St_Kind_RCruise,
    /* 0x0C */ St_Kind_Garden,
    /* 0x0D */ St_Kind_GreatBay,
    /* 0x0E */ St_Kind_Shrine,
    /* 0x0F */ St_Kind_Kraid,
    /* 0x10 */ St_Kind_Yoster, // the gr module spells it yorster
    /* 0x11 */ St_Kind_Greens,
    /* 0x12 */ St_Kind_Fourside,
    /* 0x13 */ St_Kind_Inishie1,
    /* 0x14 */ St_Kind_Inishie2,
    /* 0x15 */ St_Kind_Akaneia,
    /* 0x16 */ St_Kind_Venom,
    /* 0x17 */ St_Kind_Pura,
    /* 0x18 */ St_Kind_BigBlue,
    /* 0x19 */ St_Kind_Icemt,
    /* 0x1A */ St_Kind_Icetop,
    /* 0x1B */ St_Kind_Flatzone,
    /* 0x1C */ St_Kind_OldPupupu,
    /* 0x1D */ St_Kind_OldYoshi,
    /* 0x1E */ St_Kind_OldKongo,
    /* 0x1F */ St_Kind_Battle,
    /* 0x20 */ St_Kind_Last,
    /* 0x49 */ St_Kind_BigBlueRoute = 0x49,
    /* 0x55 */ St_Kind_Heal = 0x55,
} StKind;

typedef enum StadiumGrType {
    PsType_Display = 1,
} StadiumGrType;

/// Size of the Home-Run Contest parts array, named by an assert in
/// #grHomeRun_8021CB20.
typedef enum Gr_Homerun_Parts {
    /* 0x40 */ Gr_Homerun_Parts_Max = 64,
} Gr_Homerun_Parts;

typedef void (*unkCastleCallback)(void*, struct unkCastle*);
typedef void (*unkCastleCallback2)(void*, struct unkCastle*, Ground_GObj*);
typedef int (*GrIceMtSegmentLookup)(Ground_GObj*);
typedef DynamicsDesc* (*GrTouchLineCallback)(int index);
typedef bool (*GrCheckShadowRenderCallback)(Vec3* fighter_pos, int,
                                            HSD_JObj* jobj);

#endif
