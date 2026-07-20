#ifndef MELEE_MN_MNCOUNT_H
#define MELEE_MN_MNCOUNT_H

#include <placeholder.h>
#include <platform.h>

#include "mn/types.h"

#include <baselib/forward.h>
#include <melee/mn/forward.h>

#define MNCOUNT_VISIBLE_ROWS 10

typedef struct MnCountData {
    unsigned char scroll_pos;
    int expand_anim_duration;
    HSD_Text* labels[MNCOUNT_VISIBLE_ROWS];
    HSD_Text* values[MNCOUNT_VISIBLE_ROWS];
    HSD_Text* title;
} MnCountData;

#ifdef M2C
#define GET_MNCOUNT(gobj)                                                     \
    ((MnCountData*) HSD_GObjGetUserData((HSD_GObj*) gobj))
#else
#define GET_MNCOUNT(gobj) ((MnCountData*) HSD_GObjGetUserData(gobj))
#endif

typedef enum {
    POWER_COUNT,           // Power Count
    POWER_TIME,            // Power Time
    PLAY_TIME,             // Play Time
    SINGLEPLAYER_TIME,     // Single-Player Time
    VS_PLAY_TIME,          // VS. Play Time
    COMBINED_VS_PLAY_TIME, // Combined VS. Play Time
    VS_PLAY_MATCH_TOTAL,   // VS. Play Match Total
    TIME_MATCH_TOTAL,      // Time Match Total
    STOCK_MATCH_TOTAL,     // Stock Match Total
    COIN_MATCH_TOTAL,      // Coin Match Total
    BONUS_MATCH_TOTAL,     // Bonus Match Total
    VS_PLAY_CONTESTANTS,   // VS. Play Contestants
    MATCH_RESET_COUNTER,   // Match Reset Counter
    TOTAL_DAMAGE,          // Total Damage
    KO_TOTAL,              // KO Total
    SELFDESTRUCT_TOTAL,    // Self-Destruct Total
    AVAILABLE_CHARACTERS,  // Available Characters
    AVAILABLE_MAPS,        // Available Maps
    TROPHY_TOTAL,          // Trophy Total
    NAME_TOTAL,            // Name Total
    LONGEST_TIME,          // Longest Time
    SECOND_LONGEST_TIME,   // 2nd Longest Time
    SHORTEST_TIME,         // Shortest Time
    SMASH_CHAMP,           // Smash Champ
    SMASH_SAP,             // Smash Sap
    SLUG_MEISTER,          // Slug Meister
    PUNCHING_BAG,          // Punching Bag
    KO_KINGPIN,            // KO Kingpin
    NO_DEFENSE_NELLY,      // No-Defense Nelly
    DISASTER_MASTER,       // Disaster Master
} mnCount_row;

/* 2502CC */ u32 mnCount_GetMatchTime(SelectableCharacterKind);
/* 2502F0 */ u32 mnCount_GetKOKingpin(SelectableCharacterKind);
/* 250314 */ u32 mnCount_GetNoDefenseNelly(SelectableCharacterKind);
/* 250338 */ u32 mnCount_GetDisasterMaster(SelectableCharacterKind);
/* 25035C */ int
mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(SelectableCharacterKind));
/* 25069C */ u32 mnCount_GetSmashChamp(SelectableCharacterKind);
/* 2506C0 */ u32 mnCount_GetSmashSap(SelectableCharacterKind);
/* 2506E4 */ u32 mnCount_GetSlugMeister(SelectableCharacterKind);
/* 250708 */ u32 mnCount_GetPunchingBag(SelectableCharacterKind);
/* 25072C */ s32 mnCount_8025072C(CountEntry* entries, s32 start_idx,
                                  bool mode);
/* 25092C */ s32
mnCount_8025092C(s32 rank, u32 (*getVal)(SelectableCharacterKind), bool mode);
/* 250C7C */ SelectableCharacterKind
mnCount_GetRowValue_Character(mnCount_row row);
/* 250DE4 */ unsigned int mnCount_GetRowValue_Number(int);
/* 250FF8 */ void mnCount_CreateRow(HSD_GObj*, int, mnCount_row);
/* 251278 */ void mnCount_HandleUserInput(HSD_GObj* gobj);
/* 2513F4 */ void mnCount_UpdateArrowIndicators(HSD_GObj* gobj);
/* 2514B8 */ void fn_802514B8(HSD_GObj* gobj);
/* 2514D8 */ void fn_802514D8(HSD_GObj* gobj);
/* 251640 */ void fn_80251640(HSD_GObj* gobj);
/* 2517E0 */ void mnCount_InitUserData(MnCountData* arg0);
/* 25186C */ void mnCount_Create(void);

#endif
