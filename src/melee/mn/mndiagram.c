#include "mndiagram.h"

#include <melee/gm/forward.h>

#include "inlines.h"
#include "mndiagram2.h"
#include "mndiagram3.h"
#include "mnmain.h"
#include "mnname.h"
#include "types.h"
#include <dolphin/types.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00CE.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lblanguage.h>
#include <melee/lb/lbspdisplay.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>

StaticModelDesc MenMainCursorB1_Top;
StaticModelDesc MenMainSubB1_Top;
StaticModelDesc MenMainNmB_Top;
StaticModelDesc MenMainFaceB_Top;
StaticModelDesc MenMainConB1_Top;
HSD_GObj* mnDiagram_ScreenGObj;
StaticModelDesc MenMainCursorB3_Top;
StaticModelDesc MenMainConB3_Top;
StaticModelDesc MenMainConB2_Top;

/// Matching overlay for the separately declared fighter and name order tables.
typedef struct mnDiagram_Assets {
    /* 0x00 */ u8 sorted_fighters[SELKIND_COUNT];
    /* 0x19 */ u8 pad_19[3];
    /* 0x1C */ u8 sorted_names[GM_NAMETAG_COUNT];
} mnDiagram_Assets;
ASSERT_SIZE(mnDiagram_Assets, 0x94);

typedef struct mnDiagram_PopupData {
    /* 0x00 */ HSD_JObj* jobjs[14];
    /* 0x38 */ HSD_Text* text[5];
} mnDiagram_PopupData;
ASSERT_SIZE(mnDiagram_PopupData, 0x4C);

/// Head label for the contiguous mnDiagram popup animation data run.
typedef struct mnDiagram_PopupAnimTableHead {
    /* 0x00 */ Point3d points[3];
} mnDiagram_PopupAnimTableHead;

u8 mnDiagram_FighterDisplayOrder[0x1C];
u8 mnDiagram_NameDisplayOrder[GM_NAMETAG_COUNT];

static mnDiagram_PopupAnimTableHead mnDiagram_PopupTextOffsets = {
    {
        { 4.0F, 1.0F, 0.0F },
        { -3.0F, 0.8F, 0.0F },
        { -1.0F, 0.7F, 0.0F },
    },
};

static u8 mnDiagram_DefaultFighterOrder[0x1C] = {
    SELKIND_MARIO,
    SELKIND_DONKEY,
    SELKIND_LINK,
    SELKIND_SAMUS,
    SELKIND_YOSHI,
    SELKIND_KIRBY,
    SELKIND_FOX,
    SELKIND_PIKACHU,
    SELKIND_NESS,
    SELKIND_CAPTAIN,
    SELKIND_KOOPA,
    SELKIND_PEACH,
    SELKIND_POPONANA,
    SELKIND_ZELDA_SEAK,
    SELKIND_LUIGI,
    SELKIND_PURIN,
    SELKIND_MEWTWO,
    SELKIND_MARS,
    SELKIND_GAMEWATCH,
    SELKIND_DRMARIO,
    SELKIND_GANON,
    SELKIND_FALCO,
    SELKIND_CLINK,
    SELKIND_PICHU,
    SELKIND_EMBLEM,
    0,
    0,
    0,
};

static AnimLoopSettings mnDiagram_IntroAnim = { 0.0f, 9.0f, -0.1f };

static AnimLoopSettings mnDiagram_PopupExitAnim = { 10.0f, 19.0f, -0.1f };
static AnimLoopSettings mnDiagram_ArrowAnim = { 0.0f, 199.0f, 0.0f };
static AnimLoopSettings mnDiagram_CursorAnim = { 0.0f, 10.0f, -0.1f };

/// Overlay over the contiguous .data run starting at
/// mnDiagram_PopupTextOffsets. The compiler addresses a few of these from that
/// base rather than from their own symbols: the popup text offsets in
/// mnDiagram_PopupAnimProc and mnDiagram_CreatePopupTexts, and cursor_anim.
/// Everything else is accessed through its own symbol.
typedef struct mnDiagram_AnimTable {
    /* 0x00 */ Point3d points[3]; ///< mnDiagram_PopupTextOffsets
    /* 0x24 */ u8
        default_fighter_order[0x1C];         ///< mnDiagram_DefaultFighterOrder
    /* 0x40 */ AnimLoopSettings intro_anim;  ///< mnDiagram_IntroAnim
    /* 0x4C */ AnimLoopSettings exit_anim;   ///< mnDiagram_PopupExitAnim
    /* 0x58 */ AnimLoopSettings arrow_anim;  ///< mnDiagram_ArrowAnim
    /* 0x64 */ AnimLoopSettings cursor_anim; ///< mnDiagram_CursorAnim
} mnDiagram_AnimTable;

#define GET_DIAGRAM_ANIM_TABLE()                                              \
    ((mnDiagram_AnimTable*) &mnDiagram_PopupTextOffsets)

static GXColor mnDiagram_PopupTextColor = { 0, 0, 0, 0xFF };
char mnDiagram_StringTerminator[1] = "";

/// @brief Gets the fighter ID at the given sorted index.
/// @param idx Index into the sorted fighter list
/// @return Fighter ID
u8 mnDiagram_GetFighterByIndex(int idx)
{
    return mnDiagram_FighterDisplayOrder[idx];
}

/// @brief Gets the name ID at the given sorted index.
/// @param idx Index into the sorted name list
/// @return Name ID
u8 mnDiagram_GetNameByIndex(int idx)
{
    return mnDiagram_NameDisplayOrder[idx];
}

bool mnDiagram_IsDistanceOverflow(u32 distance)
{
    if (lbLang_IsSavedLanguageUS() != 0) {
        if (distance >= 0x274A6) {
            return true;
        }
        return false;
    } else {
        if (distance >= 0x186A0) {
            return true;
        }
        return false;
    }
}

u32 mnDiagram_ConvertDistanceForDisplay(u32 distance)
{
    if (lbLang_IsSavedLanguageUS() != 0) {
        if (distance >= 0x274A6) {
            return distance / 160934;
        }
        return (u32) ((f64) distance / 30.4788);
    }
    if (distance >= 0x186A0) {
        return distance / 100000;
    }
    return distance / 100;
}

s32 mnDiagram_GetHitPercentage(u8 is_name_mode, u8 player_index)
{
    f32 total_attacks;

    if (is_name_mode != 0) {
        if (GetPersistentNameData(player_index)->stats.attacks_total != 0) {
            total_attacks =
                GetPersistentNameData(player_index)->stats.attacks_total;
            return (100.0f *
                    (100.0f *
                     (GetPersistentNameData(player_index)->stats.attacks_hit /
                      total_attacks)));
        }
        return 0;
    }
    if (GetPersistentFighterData(player_index)->stats.attacks_total != 0) {
        total_attacks =
            GetPersistentFighterData(player_index)->stats.attacks_total;
        return (100.0f *
                (100.0f *
                 (GetPersistentFighterData(player_index)->stats.attacks_hit /
                  total_attacks)));
    }
    return 0;
}

s32 mnDiagram_GetPlayPercentage(u8 is_name_mode, u8 player_index)
{
    f32 total_play_time;
    int i;
    f32 zero = 0.0f;

    if (is_name_mode != 0) {
        total_play_time = 0.0f;
        for (i = 0; i < GM_NAMETAG_COUNT; i++) {
            total_play_time += GetPersistentNameData(i)->stats.play_time;
        }
        if (total_play_time != zero) {
            return (
                s32) (100.0f *
                      (100.0f *
                       (GetPersistentNameData(player_index)->stats.play_time /
                        total_play_time)));
        }
        return 0;
    }
    total_play_time = 0.0f;
    for (i = 0; i < SELKIND_COUNT; i++) {
        total_play_time += GetPersistentFighterData(i)->stats.play_time;
    }
    if (total_play_time != zero) {
        return (
            s32) (100.0f *
                  (100.0f *
                   (GetPersistentFighterData(player_index)->stats.play_time /
                    total_play_time)));
    }
    return 0;
}

s32 mnDiagram_GetAveragePlayerCount(u8 is_name_mode, u8 player_index)
{
    f32 match_count;

    if (is_name_mode != 0) {
        if (GetPersistentNameData(player_index)->stats.match_count != 0) {
            match_count =
                (f32) GetPersistentNameData(player_index)->stats.match_count;
            return (s32) (100.0f * ((f32) GetPersistentNameData(player_index)
                                        ->stats.total_player_count /
                                    match_count));
        }
        return 0;
    }
    if (GetPersistentFighterData(player_index)->stats.match_count != 0) {
        match_count =
            (f32) GetPersistentFighterData(player_index)->stats.match_count;
        return (s32) (100.0f * ((f32) GetPersistentFighterData(player_index)
                                    ->stats.total_player_count /
                                match_count));
    }
    return 0;
}

static inline int getNamePairKOs(u8 name, u8 opponent)
{
    return GetPersistentNameData(name)->vs_kos[opponent];
}

/// @brief Gets total KOs scored by a name against all other names.
/// @param field_index Index of the name tag to query.
/// @return Sum of KOs scored by this name against all existing names.
int mnDiagram_GetNameTotalKOs(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < GM_NAMETAG_COUNT; i++) {
        if (GetNameText(i & 0xFF)) {
            total += getNamePairKOs(field_index, (u8) i);
        }
    }
    return total;
}

/// @brief Gets total falls (deaths) of a name against all other names.
/// @details Iterates through all names and sums how many times each name
///          KO'd the target name. This is the column sum of the KO matrix.
///          Accesses vs_kos[field_index] in each name's data.
/// @param field_index Index of the name tag to query.
/// @return Sum of times this name was KO'd by all existing names (capped at
/// 999999).
static inline int mnDiagram_SumNameFalls(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < GM_NAMETAG_COUNT; i++) {
        if (GetNameText(i & 0xFF)) {
            total += getNamePairKOs((u8) i, field_index);
        }
    }
    if (total > 999999) {
        total = 999999;
    }
    return total;
}

int mnDiagram_GetNameTotalFalls(u8 field_index)
{
    PAD_STACK(16);
    return mnDiagram_SumNameFalls(field_index);
}

/// @brief Gets total KOs scored by a fighter against all other fighters.
/// @details Iterates through all unlocked fighters and sums how many times
///          the target fighter KO'd each one. Fighter data uses a similar
///          matrix layout to name data.
/// @param field_index Index of the fighter to query (0-24).
/// @return Sum of KOs scored by this fighter against all unlocked fighters.
int mnDiagram_GetFighterTotalKOs(u8 field_index)
{
    int total = 0;
    int selkind;
    for (selkind = 0; selkind < SELKIND_COUNT; selkind++) {
        if (mn_IsFighterUnlocked(selkind) != 0) {
            total += GetPersistentFighterData(field_index)
                         ->fighter_kos[(u8) selkind];
        }
    }
    return total;
}

/// @brief Gets total falls (deaths) of a fighter against all other fighters.
/// @details Iterates through all unlocked fighters and sums how many times
///          each fighter KO'd the target fighter. This is the column sum
///          of the fighter KO matrix.
/// @param field_index Index of the fighter to query (0-24).
/// @return Sum of times this fighter was KO'd by all unlocked fighters.
static inline int mnDiagram_SumFighterFalls(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (mn_IsFighterUnlocked(i)) {
            total +=
                GetPersistentFighterData(i & 0xFF)->fighter_kos[field_index];
        }
    }
    return total;
}

int mnDiagram_GetFighterTotalFalls(u8 field_index)
{
    PAD_STACK(16);
    return mnDiagram_SumFighterFalls(field_index);
}

void mnDiagram_FormatDecimalNumber(char* buf, u32 val, int decimal_places)
{
    int i;
    int digit_count;
    u32 integer_part;

    integer_part = val / powi(10, decimal_places);
    digit_count = mn_GetDigitCount(integer_part);
    for (i = 0; i < digit_count; i++) {
        buf[i] = mn_GetDigitAt(integer_part, (digit_count - 1) - i) + '0';
    }
    if (decimal_places != 0) {
        int decimal_part;
        buf[digit_count++] = '.';
        decimal_part = val % powi(10, decimal_places);
        for (i = 0; i < decimal_places; i++) {
            buf[digit_count++] =
                mn_GetDigitAt(decimal_part, (decimal_places - 1) - i) + '0';
        }
    }
    buf[digit_count] = *mnDiagram_StringTerminator;
}

static inline void writeIntegerDigits(char* buf, s32 value, int count)
{
    int i;
    for (i = 0; i < count; i++) {
        buf[i] = mn_GetDigitAt(value, (count - 1) - i) + '0';
    }
}

void mnDiagram_FormatTime(char* buf, s32 seconds)
{
    int digit_count;
    int minutes;
    int secs;

    minutes = seconds / 60;
    secs = seconds % 60;
    digit_count = mn_GetDigitCount(minutes);
    writeIntegerDigits(buf, minutes, digit_count);
    buf[digit_count++] = ':';
    buf[digit_count++] = (secs / 10) + '0';
    buf[digit_count++] = (secs % 10) + '0';
    buf[digit_count] = *mnDiagram_StringTerminator;
}

void mnDiagram_IntToStr(char* buf, u32 val)
{
    int digit_count;

    digit_count = mn_GetDigitCount(val);
    writeIntegerDigits(buf, val, digit_count);
    buf[digit_count] = *mnDiagram_StringTerminator;
}

/// @brief Gets the previous valid name index.
/// @param idx Current name index.
/// @return Previous name index with a valid name, or original if none found.
u8 mnDiagram_GetPrevNameIndex(s32 idx)
{
    int original, i;

    original = i = idx;

    do {
        if (--i < 0) {
            return original;
        }
    } while (GetNameText(i & 0xFF) == NULL);

    return i;
}

u8 mnDiagram_GetNextNameIndex(s32 idx)
{
    int original, i;

    original = i = idx;

    do {
        i++;
        if (i >= GM_NAMETAG_COUNT) {
            return original;
        }
    } while (GetNameText(i & 0xFF) == NULL);

    return i;
}

/// @brief Gets the previous valid fighter index.
/// @param idx Current fighter index.
/// @return Previous fighter index that's unlocked, or original if none found.
u8 mnDiagram_GetPrevFighterIndex(s32 idx)
{
    u8* ptr;
    int original;

    ptr = mnDiagram_FighterDisplayOrder + idx;
    original = idx;

    do {
        idx--;
        ptr--;
        if (idx < 0) {
            return original;
        }
    } while (mn_IsFighterUnlocked(*ptr) == 0);

    return idx;
}

u8 mnDiagram_GetNextFighterIndex(s32 idx)
{
    u8* ptr;
    int original;

    ptr = mnDiagram_FighterDisplayOrder + idx;
    original = idx;

    do {
        idx++;
        ptr++;
        if (idx >= SELKIND_COUNT) {
            return original;
        }
    } while (mn_IsFighterUnlocked(*ptr) == 0);

    return idx;
}

/// @brief Gets play time for a specific fighter under a name tag.
/// @param name_idx Name tag index.
/// @param fighter_idx Fighter index (0-24).
/// @return Play time in seconds for this fighter under this name.
u32 mnDiagram_GetNamePlayTimeByFighter(int name_idx,
                                       SelectableCharacterKind selkind)
{
    return GetPersistentNameData(name_idx)->play_time_by_fighter[selkind];
}

typedef struct RankEntry {
    u8 selkind; ///< SelectableCharacterKind
    u32 value;
} RankEntry;

static inline bool allPlayTimesZero(s32 name_idx)
{
    int i;
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (GetPersistentNameData(name_idx)->play_time_by_fighter[i] != 0U) {
            return false;
        }
    }
    return true;
}

int mnDiagram_GetRankedFighterForName(int rank, int name_idx,
                                      u32 (*func)(int, int))
{
    int _pad[2];
    RankEntry entries[SELKIND_COUNT];
    int i, j;

    (void) _pad;

    if (allPlayTimesZero(name_idx) != 0) {
        return SELKIND_COUNT;
    }

    // Fill entries array with fighter id and value from func
    for (i = 0; i < SELKIND_COUNT; i++) {
        entries[i].selkind = i;
        entries[i].value = func(name_idx, i);
    }

    // Selection sort by value (descending)
    for (i = 0; i < SELKIND_COUNT; i++) {
        int max_idx = i;
        for (j = i + 1; j < SELKIND_COUNT; j++) {
            if (entries[max_idx].value < entries[j].value) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            // Shift elements down and insert at position i
            RankEntry temp = entries[max_idx];
            for (j = max_idx; j > i; j--) {
                entries[j] = entries[j - 1];
            }
            entries[i] = temp;
        }
    }

    // Find the rank-th unlocked fighter
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (gm_IsCKindUnlocked(gm_SelKindToCKind(entries[i].selkind)) != 0) {
            if (rank != 0) {
                rank--;
                // Check for ties - skip fighters with same value
                for (j = i + 1; j < SELKIND_COUNT; j++) {
                    if (func(name_idx, entries[i].selkind) ==
                        func(name_idx, entries[j].selkind))
                    {
                        i++;
                        if (rank != 0) {
                            rank--;
                        } else {
                            return SELKIND_COUNT;
                        }
                    }
                }
            } else {
                // rank == 0, check if value is non-zero and no tie
                if (func(name_idx, entries[i].selkind) != 0U) {
                    if (i + 1 < SELKIND_COUNT) {
                        if (func(name_idx, entries[i].selkind) ==
                            func(name_idx, entries[i + 1].selkind))
                        {
                            return SELKIND_COUNT;
                        }
                    }
                    return entries[i].selkind;
                }
                return SELKIND_COUNT;
            }
        }
    }
    return SELKIND_COUNT;
}

u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx)
{
    int i;
    int min_fighter;
    int count;

    if (allPlayTimesZero(name_idx)) {
        return SELKIND_COUNT;
    }

    // Find fighter with minimum play time
    min_fighter = 0;
    for (i = 1; i < SELKIND_COUNT; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            if (GetPersistentNameData(name_idx)
                    ->play_time_by_fighter[min_fighter] >
                GetPersistentNameData(name_idx)->play_time_by_fighter[i])
            {
                min_fighter = i;
            }
        }
    }

    // Count unlocked fighters with zero play time
    count = 0;
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (mn_IsFighterUnlocked(i) != 0 &&
            GetPersistentNameData(name_idx)->play_time_by_fighter[i] == 0U)
        {
            count++;
        }
    }
    if (count >= 2) {
        return SELKIND_COUNT;
    }

    // Check for ties
    count = 0;
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (mn_IsFighterUnlocked(i) != 0 && i != min_fighter) {
            if (GetPersistentNameData(name_idx)->play_time_by_fighter[i] ==
                GetPersistentNameData(name_idx)
                    ->play_time_by_fighter[min_fighter])
            {
                count++;
            }
        }
    }
    if (count != 0) {
        return SELKIND_COUNT;
    }

    return min_fighter;
}

void mnDiagram_SortFightersByKOs(void)
{
    u32 totals[SELKIND_COUNT];
    u8* dst = mnDiagram_FighterDisplayOrder;
    u8* dst_iter;
    u8* candidate;
    int i, j;
    u8 sp[12];

    dst_iter = dst;
    for (i = 0; i < SELKIND_COUNT; i++, dst_iter++) {
        u8 fighter;
        *dst_iter = mnDiagram_DefaultFighterOrder[i];
        fighter = mnDiagram_DefaultFighterOrder[i];
        totals[mnDiagram_DefaultFighterOrder[i]] =
            mnDiagram_GetFighterTotalKOs(fighter);
    }

    for (i = 0; i < SELKIND_COUNT; i++) {
        int max_idx;
        j = i;
        candidate = &dst[++j];
        max_idx = i;
        for (; j < SELKIND_COUNT; candidate++, j++) {
            if (mn_IsFighterUnlocked(*candidate) != 0) {
                if ((totals[mnDiagram_FighterDisplayOrder[max_idx]] <
                     totals[*candidate]) ||
                    ((mn_IsFighterUnlocked(
                          mnDiagram_FighterDisplayOrder[max_idx]) == 0) &&
                     (mn_IsFighterUnlocked(*candidate) != 0)))
                {
                    max_idx = j;
                }
            }
        }
        if (max_idx != i) {
            u8 temp = mnDiagram_FighterDisplayOrder[max_idx];
            while (max_idx > i) {
                mnDiagram_FighterDisplayOrder[max_idx] =
                    mnDiagram_FighterDisplayOrder[max_idx - 1];
                max_idx--;
            }
            mnDiagram_FighterDisplayOrder[i] = temp;
        }
    }
}

void mnDiagram_SortNamesByKOs(void)
{
    int j;
    int max_idx;
    u8* dst_iter;
    int i;
    mnDiagram_Assets* assets =
        (mnDiagram_Assets*) &mnDiagram_FighterDisplayOrder;
    u8* dst = assets->sorted_names;
    u32* tp;
    u8* candidate;
    int n;
    u32 totals[GM_NAMETAG_COUNT];

    dst_iter = dst;
    tp = totals;
    for (n = 0; n < GM_NAMETAG_COUNT; n++, dst_iter++, tp++) {
        *dst_iter = (u8) n;
        *tp = mnDiagram_GetNameTotalKOs(n & 0xFF);
    }

    for (i = 0; i < GM_NAMETAG_COUNT; i++) {
        j = i;
        candidate = &mnDiagram_NameDisplayOrder[++j];
        max_idx = i;
        for (; j < GM_NAMETAG_COUNT; candidate++, j++) {
            if ((GetNameText(*candidate) != NULL) &&
                ((totals[mnDiagram_GetNameByIndex(max_idx)] <
                  totals[*candidate]) ||
                 ((GetNameText(mnDiagram_GetNameByIndex(max_idx)) == NULL) &&
                  (GetNameText(*candidate) != NULL))))
            {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            u8* p = &assets->sorted_fighters[max_idx];
            u8 temp = *(p += sizeof(mnDiagram_FighterDisplayOrder));
            while (max_idx > i) {
                *p = *(p - 1);
                p--;
                max_idx--;
            }
            dst[i] = temp;
        }
    }
}

/// @brief Counts the number of unlocked fighters.
/// @return Number of unlocked fighters.
int mnDiagram_CountUnlockedFighters(void)
{
    int i;
    int count = 0;
    for (i = 0; i < SELKIND_COUNT; i++) {
        if (mn_IsFighterUnlocked(i)) {
            count++;
        }
    }
    return count;
}

void mnDiagram_PopupInputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    Diagram* data = mnDiagram_ScreenGObj->user_data;
    u64 input = Menu_GetAllInputs();
    if ((u32) input & MenuInput_Back) {
        sfxBack();
        HSD_GObjProc_RemoveProc(HSD_GObj_CurrentInvokedProc);
        proc = HSD_GObj_SetupProc(gobj, mnDiagram_InputProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_GObjFree(data->popup_gobj);
        data->popup_gobj = NULL;
    }
}

static inline u8 mnDiagram_GetVisibleNameFrom(int start, int rank)
{
    u8* p;
    u8* p2;
    int remaining;
    int idx;

    p = mnDiagram_NameDisplayOrder + start;
    remaining = rank;
    idx = start;
    while (remaining > 0) {
        p2 = p;
        do {
            idx++;
            p2++;
            p++;
            if (idx >= GM_NAMETAG_COUNT) {
                return GM_NAMETAG_COUNT;
            }
        } while (GetNameText(*p2) == NULL);
        remaining--;
    }
    return mnDiagram_GetNameByIndex(idx);
}

static inline s32 mnDiagram_FindPrevFighter(u8* sorted,
                                            SelectableCharacterKind cur)
{
    u8* p = sorted + cur;
    SelectableCharacterKind found = cur;
    do {
        found--;
        p--;
        if (found < 0) {
            return cur;
        }
    } while (mn_IsFighterUnlocked(*p) == 0);
    return (u8) found;
}

static inline u8 mnDiagram_FindNextFighter(u8* sorted,
                                           SelectableCharacterKind cur)
{
    u8* p;
    SelectableCharacterKind found;

    found = cur;
    p = sorted + cur;
    do {
        found++;
        p++;
        if (found >= SELKIND_COUNT) {
            return cur;
        }
    } while (mn_IsFighterUnlocked(*p) == 0);
    return found;
}

static inline s32 mnDiagram_FindPrevName(s32 cur)
{
    int found = cur;
    do {
        found--;
        if (found < 0) {
            return cur;
        }
    } while (GetNameText(found & 0xFF) == NULL);
    return (u8) found;
}

static inline s32 mnDiagram_FindPrevNameWrap(s32 cur)
{
    int found = cur;
    do {
        found--;
        if (found < 0) {
            return (u8) cur;
        }
    } while (GetNameText(found & 0xFF) == NULL);
    return (u8) found;
}

static inline s32 mnDiagram_FindPrevFighterWrap(u8* sorted, s32 cur)
{
    u8* p = sorted + cur;
    int found = cur;
    do {
        found--;
        p--;
        if (found < 0) {
            return (u8) cur;
        }
    } while (mn_IsFighterUnlocked(*p) == 0);
    return (u8) found;
}

static inline int mnDiagram_FindNextName(s32 cur)
{
    int found = cur;
    do {
        found++;
        if (found >= GM_NAMETAG_COUNT) {
            return (u8) cur;
        }
    } while (GetNameText(found & 0xFF) == NULL);
    return (u8) found;
}

static inline u8 mnDiagram_GetVisibleNameCursorFrom(int start, int rank)
{
    while (rank > 0) {
        do {
            start++;
            if (start >= GM_NAMETAG_COUNT) {
                return GM_NAMETAG_COUNT;
            }
        } while (GetNameText(mnDiagram_GetNameByIndex(start)) == NULL);
        rank--;
    }
    return mnDiagram_GetNameByIndex(start);
}

static inline u8 mnDiagram_GetVisibleFighterCursorFrom(u8* sorted, int start,
                                                       int rank)
{
    u8 result;
    int remaining;
    u8* p2;
    u8* p;
    int idx;

    remaining = rank;
    idx = start;
    p = sorted + start;
    while (remaining >= 0) {
        if (remaining == 0) {
            result = sorted[idx];
            break;
        }
        p2 = p;
        do {
            idx++;
            p2++;
            p++;
            if (idx >= SELKIND_COUNT) {
                return SELKIND_COUNT;
            }
        } while (mn_IsFighterUnlocked(*p2) == 0);
        remaining--;
    }
    return result;
}

static inline u8 mnDiagram_GetVisibleFighterColumnForInput(u8* sorted,
                                                           int start, int rank,
                                                           int* index)
{
    u8 result;
    u8* p;
    u8* p2;
    int remaining;

    remaining = rank;
    *index = start;
    p = sorted + start;
    while (remaining >= 0) {
        if (remaining == 0) {
            result = sorted[*index];
            break;
        }
        p2 = p;
        do {
            (*index)++;
            p2++;
            p++;
            if (*index >= SELKIND_COUNT) {
                return SELKIND_COUNT;
            }
        } while (mn_IsFighterUnlocked(*p2) == 0);
        remaining--;
    }
    return result;
}

static inline u8 mnDiagram_GetVisibleFighterRowForInput(u8* sorted,
                                                        Diagram* data,
                                                        const u16* selection,
                                                        int* index)
{
    u16 selected_word;
    u16 cursor_word;
    u8 result;
    u8* p;
    u8* p2;
    int remaining;

    selected_word = *selection;
    cursor_word = data->fighter_cursor_pos;
    remaining = selected_word >> 8;
    *index = cursor_word >> 8;
    p = sorted + *index;
    while (remaining >= 0) {
        if (remaining == 0) {
            result = sorted[*index];
            break;
        }
        p2 = p;
        do {
            (*index)++;
            p2++;
            p++;
            if (*index >= SELKIND_COUNT) {
                return SELKIND_COUNT;
            }
        } while (mn_IsFighterUnlocked(*p2) == 0);
        remaining--;
    }
    return result;
}

static inline u8 mnDiagram_GetVisibleFighterFromPointer(const u8* sorted,
                                                        u8* p, int start,
                                                        int rank)
{
    u8 result;
    u8* p2;
    int remaining;
    int idx;

    remaining = rank;
    idx = start;
    while (remaining >= 0) {
        if (remaining == 0) {
            result = sorted[idx];
            break;
        }
        p2 = p;
        do {
            idx++;
            p2++;
            p++;
            if (idx >= SELKIND_COUNT) {
                return SELKIND_COUNT;
            }
        } while (mn_IsFighterUnlocked(*p2) == 0);
        remaining--;
    }
    return result;
}

static inline u8 mnDiagram_GetVisibleFighterCursorFrom2(int start, int rank)
{
    while (rank >= 0) {
        if (rank == 0) {
            return mnDiagram_GetFighterByIndex(start);
        }
        do {
            start++;
            if (start >= SELKIND_COUNT) {
                return SELKIND_COUNT;
            }
        } while (mn_IsFighterUnlocked(mnDiagram_GetFighterByIndex(start)) ==
                 0);
        rank--;
    }
}

static inline Diagram* mnDiagram_GetCurrentDiagramData(void)
{
    return mnDiagram_ScreenGObj->user_data;
}

static inline void saveCursorPositions(Diagram* data)
{
    gmMainLib_GetGameRules()->xE = (u8) (data->fighter_cursor_pos >> 8);
    gmMainLib_GetGameRules()->xF = (u8) data->fighter_cursor_pos;
    gmMainLib_GetGameRules()->unk_x10 = (u8) (data->name_cursor_pos >> 8);
    gmMainLib_GetGameRules()->x11 = (u8) data->name_cursor_pos;
    gmMainLib_GetGameRules()->xD = data->is_name_mode;
}

/// @brief Per-frame input handler for the VS Records "diagram" grid screen.
///
/// Dispatches the current frame's menu input:
///   - A (0x10):    open the detail popup (mnDiagram_PopupInputProc) for the
///                  highlighted cell, mapping the display cursor
///                  (mn_804A04F0.hovered_selection = row<<8 | col) to the
///                  underlying name/fighter id via the col-th/row-th visible
///                  entry, then enter the detail page (mnDiagram_CreatePopup).
///   - B (0x20):    save cursor state and back out (mn_80229894).
///   - Start/Z (0xC0): save cursor state and advance to page 2
///                  (mnDiagram2_Init) or page 3 (mnDiagram3_Init).
///   - L/R (0xC00): toggle between name-tag and fighter axes, clamping the
///                  cursor to the valid entry count.
///   - D-pad (1/2/4/8): move the cursor within the grid, scrolling the data
///                  window by a page when moving past a visible edge.
///
/// The visible-entry scans skip locked fighters and empty name slots.
void mnDiagram_InputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    u8 row_result;
    int i;
    u16* selection;
    u8* sorted = mnDiagram_FighterDisplayOrder;
    Diagram* data = mnDiagram_GetCurrentDiagramData();
    u32 input = mn_80229624(4);
    int count;
    int col;
    int row;
    int row3;
    int row4;
    int row5;
    int row6;
    u8 col_result;
    u8 col_result2;
    u8 row_result2;
    u8 col_result3;
    u8 col_result4;
    u8 row_result3;
    u8 row_result4;
    int found;
    int cur;
    int cursor_pos;
    int count2;
    // Preserve the original 0x80-byte frame.
    PAD_STACK(32);
    mn_804A04F0.buttons = input;
    count2 = 0;
    if (input & MenuInput_Confirm) {
        sfxForward();
        HSD_GObjProc_RemoveProc(HSD_GObj_CurrentInvokedProc);
        i = 0;
        proc = HSD_GObj_SetupProc(gobj, mnDiagram_PopupInputProc, i);
        proc->flags_3 = HSD_GObj_804D783C;
        if (data->is_name_mode != 0) {
            col = mn_804A04F0.hovered_selection;
            cur = col;
            col_result = mnDiagram_GetVisibleNameCursorFrom(
                (u8) data->name_cursor_pos, (u8) cur);
            row = mn_804A04F0.hovered_selection >> 8;
            cursor_pos = data->name_cursor_pos;
            row_result =
                mnDiagram_GetVisibleNameCursorFrom(cursor_pos >> 8, row);
            mnDiagram_CreatePopup(col_result, row_result, 1);
            return;
        }
        selection = &mn_804A04F0.hovered_selection;
        row_result2 = (u8) data->fighter_cursor_pos;
        col_result2 = mnDiagram_GetVisibleFighterColumnForInput(
            sorted, row_result2, (u8) *selection, &i);
        row_result2 = mnDiagram_GetVisibleFighterRowForInput(sorted, data,
                                                             selection, &col);

        mnDiagram_CreatePopup(col_result2, row_result2, 0);
        return;
    }
    if (input & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = count2;
        saveCursorPositions(mnDiagram_GetCurrentDiagramData());
        mn_80229894(0x1C, 0, 3);
        return;
    }
    if (input & (MenuInput_LTrigger | MenuInput_RTrigger)) {
        sfxForward();
        saveCursorPositions(mnDiagram_GetCurrentDiagramData());
        HSD_GObjFree(gobj);
        if (input & MenuInput_LTrigger) {
            mnDiagram3_Init(0L);
            return;
        }
        mnDiagram2_Init();
        return;
    }
    if (input & (MenuInput_XButton | MenuInput_YButton)) {
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        sfxForward();
        data->is_name_mode = (data->is_name_mode == 0) ? 1 : count2;
        if (data->is_name_mode != 0) {
            cur = GetNameCount();
            if (((u8) mn_804A04F0.hovered_selection) >= cur) {
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((u8) (cur - 1));
            }
            if ((mn_804A04F0.hovered_selection >> 8) >= cur) {
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((cur - 1) << 8);
            }
            mnDiagram_UpdateScrollArrowVisibility(mnDiagram_ScreenGObj, cur);
            mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                  (u8) data->name_cursor_pos,
                                  data->name_cursor_pos >> 8);
            return;
        }
        count = mnDiagram_CountUnlockedFighters();

        if (((u8) mn_804A04F0.hovered_selection) >= count) {
            mn_804A04F0.hovered_selection =
                (mn_804A04F0.hovered_selection & 0xFF00) | ((u8) (count - 1));
        }
        if ((mn_804A04F0.hovered_selection >> 8) >= count) {
            mn_804A04F0.hovered_selection =
                ((u8) mn_804A04F0.hovered_selection) | ((count - 1) << 8);
        }
        mnDiagram_UpdateScrollArrowVisibility(mnDiagram_ScreenGObj, count);
        mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                              (u8) data->fighter_cursor_pos,
                              data->fighter_cursor_pos >> 8);
        return;
    }
    if (data->is_name_mode != 0) {
        count = GetNameCount();
        if (input & MenuInput_Up) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col > 0) && (count > (col - 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col - 1) & 0xFF);
                return;
            }
            if (count > 0xA) {
                cur = (u8) data->name_cursor_pos;
                found = (u8) mnDiagram_FindPrevName(cur);
                if (cur != found) {
                    sfxMove();
                    data->name_cursor_pos =
                        (data->name_cursor_pos & 0xFF00) | found;
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->name_cursor_pos,
                                          data->name_cursor_pos >> 8);
                }
            }
        } else if (input & MenuInput_Down) {
            u8 next_name;
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col < 9) && (count > (col + 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col + 1) & 0xFF);
                return;
            }
            if (count > 0xA) {
                cur = (u8) data->name_cursor_pos;
                next_name = (u8) mnDiagram_FindNextName(cur);
                if (cur != next_name) {
                    col_result3 = mnDiagram_GetVisibleNameCursorFrom(cur, 0xA);
                    if (col_result3 != GM_NAMETAG_COUNT) {
                        sfxMove();
                        data->name_cursor_pos =
                            (data->name_cursor_pos & 0xFF00) | next_name;
                        mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                              (u8) data->name_cursor_pos,
                                              data->name_cursor_pos >> 8);
                    }
                }
            }
        } else if (input & MenuInput_Left) {
            row3 = mn_804A04F0.hovered_selection >> 8;
            if ((0 < row3) && (count > (row3 - 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row3 - 1) << 8);
                return;
            }
            if (count > 7) {
                found = (u8) mnDiagram_FindPrevNameWrap(
                    cur = data->name_cursor_pos >> 8);
                if (cur != found) {
                    sfxMove();
                    data->name_cursor_pos =
                        ((u8) data->name_cursor_pos) | (found << 8);
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->name_cursor_pos,
                                          data->name_cursor_pos >> 8);
                }
            }
        } else if (input & MenuInput_Right) {
            u8 next_name;
            row4 = mn_804A04F0.hovered_selection >> 8;
            if ((row4 < 6) && (count > (row4 + 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row4 + 1) << 8);
                return;
            }
            if (count > 7) {
                cur = data->name_cursor_pos >> 8;
                next_name = (u8) mnDiagram_FindNextName(cur);
                if (cur != next_name) {
                    row_result3 = mnDiagram_GetVisibleNameCursorFrom(cur, 7);
                    if (row_result3 != GM_NAMETAG_COUNT) {
                        sfxMove();
                        data->name_cursor_pos =
                            ((u8) data->name_cursor_pos) | (next_name << 8);
                        mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                              (u8) data->name_cursor_pos,
                                              data->name_cursor_pos >> 8);
                    }
                }
            }
        }
    } else {
        count2 = mnDiagram_CountUnlockedFighters();

        if (input & MenuInput_Up) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col > 0) && (count2 > (col - 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col - 1) & 0xFF);
                return;
            }
            if (count2 > 0xA) {
                cur = (u8) data->fighter_cursor_pos;
                found = (u8) mnDiagram_FindPrevFighter(sorted, cur);
                if (cur != found) {
                    sfxMove();
                    data->fighter_cursor_pos =
                        (data->fighter_cursor_pos & 0xFF00) | found;
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->fighter_cursor_pos,
                                          data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & MenuInput_Down) {
            u8* nav_ptr;
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col < 9) && (count2 > (col + 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col + 1) & 0xFF);
                return;
            }
            if (count2 > 0xA) {
                cur = (u8) data->fighter_cursor_pos;
                nav_ptr = sorted + cur;
                row5 = mnDiagram_FindNextFighter(sorted, cur);
                found = row5;
                col_result4 = mnDiagram_GetVisibleFighterFromPointer(
                    sorted, nav_ptr, cur, 0xA);

                if (col_result4 != SELKIND_COUNT) {
                    sfxMove();
                    data->fighter_cursor_pos =
                        (data->fighter_cursor_pos & 0xFF00) | found;
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->fighter_cursor_pos,
                                          data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & MenuInput_Left) {
            row5 = mn_804A04F0.hovered_selection >> 8;
            if ((row5 > 0) && (count2 > (row5 - 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row5 - 1) << 8);
                return;
            }
            if (count2 > 7) {
                cur = data->fighter_cursor_pos >> 8;
                found = (u8) mnDiagram_FindPrevFighterWrap(sorted, cur);
                if (cur != found) {
                    sfxMove();
                    data->fighter_cursor_pos =
                        ((u8) data->fighter_cursor_pos) | (found << 8);
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->fighter_cursor_pos,
                                          data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & MenuInput_Right) {
            u8* nav_ptr;
            row6 = mn_804A04F0.hovered_selection >> 8;
            if ((row6 < 6) && (count2 > (row6 + 1))) {
                sfxMove();
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row6 + 1) << 8);
                return;
            }
            if (count2 > 7) {
                cur = data->fighter_cursor_pos >> 8;
                nav_ptr = sorted + cur;
                found = mnDiagram_FindNextFighter(sorted, cur);
                row_result4 = mnDiagram_GetVisibleFighterFromPointer(
                    sorted, nav_ptr, cur, 7);

                if (row_result4 != SELKIND_COUNT) {
                    sfxMove();
                    data->fighter_cursor_pos =
                        ((u8) data->fighter_cursor_pos) | (found << 8);
                    mnDiagram_RefreshGrid(mnDiagram_ScreenGObj,
                                          (u8) data->fighter_cursor_pos,
                                          data->fighter_cursor_pos >> 8);
                }
            }
        }
    }
}

static inline void removeText(HSD_Text* text)
{
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
    }
}

void mnDiagram_PopupCleanup(void* arg0)
{
    mnDiagram_PopupData* data = arg0;

    removeText(data->text[0]);
    removeText(data->text[1]);
    removeText(data->text[2]);
    removeText(data->text[3]);
    removeText(data->text[4]);
    HSD_Free(arg0);
}

static inline Vec3* mnDiagram_PopupAnimProc_Inline(mnDiagram_AnimTable* arg0,
                                                   int arg1)
{
    return &arg0->points[arg1];
}

static inline void mnDiagram_TextSetPos(HSD_Text* text, f32 x, f32 y, f32 z)
{
    text->pos_x = x;
    text->pos_y = y;
    text->pos_z = z;
}

void mnDiagram_PopupAnimProc(HSD_GObj* arg0)
{
    mnDiagram_PopupData* data = arg0->user_data;
    HSD_Text* text;
    mnDiagram_AnimTable* tbl = GET_DIAGRAM_ANIM_TABLE();
    Vec3 pos;
    f32 anim_frame;

    HSD_JObjAnimAll(data->jobjs[5]);

    text = data->text[0];
    lb_8000B1CC(data->jobjs[8], mnDiagram_PopupAnimProc_Inline(tbl, 0), &pos);
    {
        f32 y = -pos.y;
        f32 z = pos.z;
        mnDiagram_TextSetPos(text, pos.x, y, z);
    }
    text->default_alignment = 0;

    HSD_JObjAnim(data->jobjs[9]);
    if (data->text[1] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[11], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = -pos.y;
        z = pos.z;
        t = data->text[1];
        mnDiagram_TextSetPos(t, pos.x, y, z);
        text->default_alignment = 1;
    }
    if (data->text[2] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[10], mnDiagram_PopupAnimProc_Inline(tbl, 2),
                    &pos);
        y = -pos.y;
        z = pos.z;
        t = data->text[2];
        mnDiagram_TextSetPos(t, pos.x, y, z);
        text->default_alignment = 1;
    }

    HSD_JObjAnim(data->jobjs[1]);
    {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[3], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = -pos.y;
        z = pos.z;
        t = data->text[3];
        mnDiagram_TextSetPos(t, pos.x, y, z);
    }
    text->default_alignment = 1;

    if (data->text[4] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[2], mnDiagram_PopupAnimProc_Inline(tbl, 2),
                    &pos);
        y = -pos.y;
        z = pos.z;
        t = data->text[4];
        mnDiagram_TextSetPos(t, pos.x, y, z);
        text->default_alignment = 1;
    }

    anim_frame = mn_8022EFD8(data->jobjs[12], &tbl->cursor_anim);
    {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[13], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = -pos.y;
        z = pos.z;
        t = data->text[3];
        mnDiagram_TextSetPos(t, pos.x, y, z);
    }
    text->default_alignment = 1;

    if (anim_frame == tbl->cursor_anim.end_frame) {
        HSD_GObjProc_RemoveProc(HSD_GObj_CurrentInvokedProc);
    }
}

static inline void mnDiagram_FormatPopupNumber(char* buf, u32 val)
{
    int digit_count = mn_GetDigitCount(val);
    int i;

    for (i = 0; i < digit_count; i++) {
        buf[digit_count - 1 - i] = mn_GetDigitAt(val, i) + '0';
    }
    buf[digit_count] = *mnDiagram_StringTerminator;
}

static inline void setPopupTextPosition(HSD_Text* text, const Vec3* pos)
{
    f32 y = -pos->y;
    f32 z = pos->z;
    text->pos_x = pos->x;
    text->pos_y = y;
    text->pos_z = z;
}

void mnDiagram_CreatePopupTexts(HSD_GObj* arg0, s32 selkind_or_nametag_slot_id,
                                s32 arg2, s32 use_nametag)
{
    mnDiagram_PopupData* data = arg0->user_data;
    Point3d pos;
    char buf[8];
    u32 kos;
    u32 sd_count;

    HSD_Text* text = HSD_SisLib_803A6754(0, 1);
    u8 sp[24];
    data->text[0] = text;
    lb_8000B1CC(data->jobjs[8], &mnDiagram_PopupTextOffsets.points[0], &pos);
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    setPopupTextPosition(text, &pos);
    text->default_alignment = 0;
    text->text_color = mnDiagram_PopupTextColor;

    if (use_nametag != 0) {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f,
                            GetNameText((u8) selkind_or_nametag_slot_id));
    } else {
        gm_80160C90(text, gm_SelKindToCKind((u8) selkind_or_nametag_slot_id),
                    0);
    }

    if ((use_nametag != 0) && (selkind_or_nametag_slot_id != arg2)) {
        {
            HSD_Text* label_text;

            label_text = HSD_SisLib_803A6754(0, 1);
            data->text[2] = label_text;
            lb_8000B1CC(data->jobjs[10], &mnDiagram_PopupTextOffsets.points[2],
                        &pos);
            label_text->font_size.x = 0.035f;
            label_text->font_size.y = 0.05f;
            setPopupTextPosition(label_text, &pos);
            label_text->default_alignment = 1;
            HSD_SisLib_803A6B98(label_text, 0.0f, 0.0f,
                                GetNameText(arg2 & 0xFF));
        }

        {
            HSD_Text* label_text;

            label_text = HSD_SisLib_803A6754(0, 1);
            data->text[4] = label_text;
            lb_8000B1CC(data->jobjs[2], &GET_DIAGRAM_ANIM_TABLE()->points[2],
                        &pos);
            label_text->font_size.x = 0.035f;
            label_text->font_size.y = 0.05f;
            setPopupTextPosition(label_text, &pos);
            label_text->default_alignment = 1;
            HSD_SisLib_803A6B98(label_text, 0.0f, 0.0f,
                                GetNameText((u8) arg2));
        }
    }

    if ((use_nametag == 0) || (selkind_or_nametag_slot_id != arg2)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[1] = text;
        lb_8000B1CC(data->jobjs[11], &mnDiagram_PopupTextOffsets.points[1],
                    &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        setPopupTextPosition(text, &pos);

        if (use_nametag != 0) {
            kos = GetPersistentNameData((u8) selkind_or_nametag_slot_id)
                      ->vs_kos[(u8) arg2];
            mnDiagram_FormatPopupNumber(buf, kos);
        } else {
            kos = GetPersistentFighterData((u8) selkind_or_nametag_slot_id)
                      ->fighter_kos[(u8) arg2];
            mnDiagram_FormatPopupNumber(buf, kos);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }

    if (selkind_or_nametag_slot_id == arg2) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[3] = text;
        lb_8000B1CC(data->jobjs[13], &mnDiagram_PopupTextOffsets.points[1],
                    &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        setPopupTextPosition(text, &pos);
        if (use_nametag != 0) {
            sd_count = GetPersistentNameData((u8) selkind_or_nametag_slot_id)
                           ->stats.sd_count;
            mnDiagram_FormatPopupNumber(buf, sd_count);
        } else {
            sd_count =
                GetPersistentFighterData((u8) selkind_or_nametag_slot_id)
                    ->stats.sd_count;
            mnDiagram_FormatPopupNumber(buf, sd_count);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    } else {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[3] = text;
        lb_8000B1CC(data->jobjs[3], &mnDiagram_PopupTextOffsets.points[1],
                    &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        setPopupTextPosition(text, &pos);
        if (use_nametag != 0) {
            u32 count = GetPersistentNameData((u8) arg2)
                            ->vs_kos[(u8) selkind_or_nametag_slot_id];
            mnDiagram_FormatPopupNumber(buf, count);
        } else {
            u32 count = GetPersistentFighterData((u8) arg2)
                            ->fighter_kos[(u8) selkind_or_nametag_slot_id];
            mnDiagram_FormatPopupNumber(buf, count);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }
}

/// @todo .sdata2 order hack
#ifdef MUST_MATCH
static void order_sdata2(void)
{
    (void) -1.0f;
    (void) S32_TO_F32;
}
#endif

void mnDiagram_CreatePopup(s32 arg0, s32 arg1, s32 use_nametag)
{
    int i;
    StaticModelDesc* model;
    Diagram* data;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    mnDiagram_PopupData* user_data;

    model = &MenMainSubB1_Top;
    data = GET_DIAGRAM(mnDiagram_ScreenGObj);

    gobj = GObj_Create(6, 7, 0x80);
    data->popup_gobj = gobj;
    jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, model->animjoint, model->matanim_joint,
                       model->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    user_data = HSD_MemAlloc(sizeof(mnDiagram_PopupData));
    HSD_ASSERTREPORT(0x5F8, user_data, "Can't get user_data.\n");

    GObj_InitUserData(gobj, 0, mnDiagram_PopupCleanup, user_data);
    user_data->text[4] = NULL;
    user_data->text[3] = NULL;
    user_data->text[2] = NULL;
    user_data->text[1] = NULL;
    user_data->text[0] = NULL;

    for (i = 0; i < 14; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }

    HSD_GObj_SetupProc(gobj, mnDiagram_PopupAnimProc, 0);
    mnDiagram_CreatePopupTexts(gobj, arg0, arg1, use_nametag);

    if (use_nametag != 0) {
        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[9], JOBJ_HIDDEN);
        }
        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[1], JOBJ_HIDDEN);
        }
        if (arg0 != arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[12], JOBJ_HIDDEN);
        }
    } else {
        HSD_JObj* icon = mnDiagram_CreateFighterIcon(arg0, 1);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        mn_8022F3D8(icon, 0xA, TOBJ_MASK);
        HSD_JObjAddChild(user_data->jobjs[7], icon);

        icon = mnDiagram_CreateFighterIcon(arg1, 1);
        HSD_JObjSetTranslateX(icon, -1.0f);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        HSD_JObjAddChild(user_data->jobjs[10], icon);

        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[1], JOBJ_HIDDEN);
        } else {
            icon = mnDiagram_CreateFighterIcon(arg1, 1);
            HSD_JObjSetTranslateX(icon, -1.0f);
            mn_8022F3D8(icon, 1, TOBJ_MASK);
            HSD_JObjAddChild(user_data->jobjs[2], icon);
        }
        if (arg0 != arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[12], JOBJ_HIDDEN);
        }
    }
}

void mnDiagram_ClearGrid(HSD_GObj* arg0)
{
    Diagram* data = arg0->user_data;
    HSD_JObj* child;

    child = HSD_JObjGetChild(data->jobjs[7]);
    if (child != NULL) {
        HSD_JObjRemoveAll(child);
    }

    child = HSD_JObjGetChild(data->jobjs[9]);
    if (child != NULL) {
        HSD_JObjRemoveAll(child);
    }

    child = HSD_JObjGetChild(data->jobjs[11]);
    if (child != NULL) {
        HSD_JObjRemoveAll(child);
    }

    if (data->col_header_text != NULL) {
        HSD_SisLib_803A5CC4(data->col_header_text);
        data->col_header_text = NULL;
    }
    if (data->row_header_text != NULL) {
        HSD_SisLib_803A5CC4(data->row_header_text);
        data->row_header_text = NULL;
    }
}

static inline void refreshGrid(HSD_GObj* gobj, int row_start, int col_start,
                               Diagram* data)
{
    mnDiagram_ClearGrid(gobj);
    mnDiagram_DrawGridValues(gobj, row_start, col_start,
                             (u8) (data->is_name_mode == 1));
    if (data->is_name_mode == 0) {
        mnDiagram_DrawFighterHeaders(gobj, row_start, col_start);
    } else {
        mnDiagram_DrawNameHeaders(gobj, row_start, col_start);
    }
}

void mnDiagram_RefreshGrid(HSD_GObj* arg0, int arg1, int arg2)
{
    refreshGrid(arg0, arg1, arg2, GET_DIAGRAM(arg0));
}

static inline void setArrowVisible(HSD_JObj* arrow, bool visible)
{
    if (visible) {
        HSD_JObjClearFlagsAll(arrow, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(arrow, JOBJ_HIDDEN);
    }
}

/// @brief Updates scroll arrow visibility based on cursor position and
///        available entries beyond the visible range.
/// @param[in] gobj The diagram GObj containing arrow JObjs in user_data.
/// @details Checks 4 arrows: right (10 more cols?), left (cursor > 0?),
///          up (cursor row > 0?), down (7 more rows?). Hides arrows when
///          there's nothing to scroll to, shows them when there is.
void mnDiagram_UpdateScrollArrows(HSD_GObj* gobj)
{
    u8 result2;
    Diagram* data = gobj->user_data;
    HSD_JObj* jobj;
    u8* ptr2;
    u8* ptr;
    int count;
    int i;
    u8* sorted = mnDiagram_FighterDisplayOrder;
    int result;
    int name_count;
    HSD_JObj* jobj2;
    HSD_JObj* jobj3;

    // Right arrow (jobjs[3])
    jobj = data->jobjs[3];
    mn_8022ED6C(jobj, &mnDiagram_ArrowAnim);
    if (data->is_name_mode != 0) {
        result = mnDiagram_GetVisibleNameFrom((u8) data->name_cursor_pos, 10);
        setArrowVisible(jobj, (u8) result != GM_NAMETAG_COUNT);
    } else {
        result = mnDiagram_GetVisibleFighterCursorFrom(
            sorted, (u8) data->fighter_cursor_pos, 10);
        setArrowVisible(jobj, (u8) result != SELKIND_COUNT);
    }

    // Left arrow (jobjs[4])
    jobj2 = data->jobjs[4];
    mn_8022ED6C(jobj2, &mnDiagram_ArrowAnim);
    if (data->is_name_mode != 0) {
        result = (u8) data->name_cursor_pos;
    } else {
        result = (u8) data->fighter_cursor_pos;
    }
    setArrowVisible(jobj2, result != 0);

    // Up arrow (jobjs[5])
    jobj2 = data->jobjs[5];
    mn_8022ED6C(jobj2, &mnDiagram_ArrowAnim);
    if (data->is_name_mode != 0) {
        i = data->name_cursor_pos >> 8;
    } else {
        i = data->fighter_cursor_pos >> 8;
    }
    setArrowVisible(jobj2, i != 0);

    // Down arrow (jobjs[6])
    jobj3 = data->jobjs[6];
    mn_8022ED6C(jobj3, &mnDiagram_ArrowAnim);
    if (data->is_name_mode != 0) {
        name_count = 7;
        i = data->name_cursor_pos >> 8;
        ptr = mnDiagram_NameDisplayOrder + i;
        while (name_count > 0) {
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= GM_NAMETAG_COUNT) {
                    result = GM_NAMETAG_COUNT;
                    goto dn_name_done;
                }
            } while (GetNameText(*ptr2) == NULL);
            name_count--;
        }
        result = mnDiagram_GetNameByIndex(i);
    dn_name_done:
        setArrowVisible(jobj3, (u8) result != GM_NAMETAG_COUNT);
    } else {
        // Fighter mode - check if 7 more rows exist
        count = 7;
        i = data->fighter_cursor_pos >> 8;
        ptr2 = sorted + i;
        do {
            if (count == 0) {
                result2 = sorted[i];
                break;
            }
            ptr = ptr2;
            do {
                i++;
                ptr++;
                ptr2++;
                if (i >= SELKIND_COUNT) {
                    result2 = SELKIND_COUNT;
                    goto dn_fc_done;
                }
            } while (mn_IsFighterUnlocked(*ptr) == 0);
            count--;
        } while (count >= 0);
    dn_fc_done:
        setArrowVisible(jobj3, result2 != SELKIND_COUNT);
    }
}

void mnDiagram_ExitAnimProc(HSD_GObj* gobj)
{
    Diagram* data;
    HSD_JObj* jobj;

    data = gobj->user_data;
    mnDiagram_UpdateScrollArrows(gobj);
    jobj = data->jobjs[1];
    if (mn_8022ED6C(jobj, &mnDiagram_PopupExitAnim) >=
        mnDiagram_PopupExitAnim.end_frame)
    {
        HSD_GObjFree(gobj);
    }
}

static inline void updateScrollArrowVisibility(Diagram* data, int count)
{
    if (count <= 7) {
        HSD_JObjSetFlagsAll(data->jobjs[5], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->jobjs[6], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(data->jobjs[5], JOBJ_HIDDEN);
        HSD_JObjClearFlagsAll(data->jobjs[6], JOBJ_HIDDEN);
    }
    if (count <= 10) {
        HSD_JObjSetFlagsAll(data->jobjs[4], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(data->jobjs[3], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(data->jobjs[4], JOBJ_HIDDEN);
        HSD_JObjClearFlagsAll(data->jobjs[3], JOBJ_HIDDEN);
    }
}

/// @brief Updates scroll arrow visibility based on entry count.
/// @details Hides vertical arrows if count <= 7 (fits in visible rows).
///          Hides horizontal arrows if count <= 10 (fits in visible columns).
/// @param gobj The diagram GObj containing arrow JObjs in user_data.
/// @param count Number of entries (fighters or names) to display.
void mnDiagram_UpdateScrollArrowVisibility(HSD_GObj* gobj, int count)
{
    Diagram* data = gobj->user_data;
    PAD_STACK(8);
    updateScrollArrowVisibility(data, count);
}

static inline int getEntryCount(Diagram* data)
{
    return data->is_name_mode != 0 ? GetNameCount()
                                   : mnDiagram_CountUnlockedFighters();
}

static inline int getFighterCount(void)
{
    return mnDiagram_CountUnlockedFighters();
}

void mnDiagram_OnFrame(HSD_GObj* gobj)
{
    Diagram* data = GET_DIAGRAM(gobj);
    HSD_GObjProc* proc;
    Diagram* data2;
    int count;

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        if (mn_804A04F0.cur_menu == 0x1E) {
            mnDiagram_ClearGrid(gobj);
            HSD_GObjFree(gobj);
            return;
        }
        HSD_GObjProc_RemoveProc(HSD_GObj_CurrentInvokedProc);
        proc = HSD_GObj_SetupProc(gobj, mnDiagram_ExitAnimProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_JObjSetFlagsAll(data->jobjs[2], JOBJ_HIDDEN);
        mnDiagram_ClearGrid(gobj);
        return;
    }

    if (data->anim_state == 1) {
        HSD_JObj* jobj;
        f32 frame;
        f32 end_frame;

        frame = mn_8022ED6C(data->jobjs[1], &mnDiagram_IntroAnim);
        end_frame = mnDiagram_IntroAnim.end_frame;
        jobj = data->jobjs[2];
        if (frame >= end_frame) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            data->anim_state = 0;
            mnDiagram_CreateCursor();
            if (data->is_name_mode != 0) {
                u16 indices = data->name_cursor_pos;
                int row_idx;
                u8 col_idx;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_ClearGrid(gobj);
                mnDiagram_DrawGridValues(gobj, col_idx, row_idx,
                                         (u8) (data2->is_name_mode == 1));
                if (data2->is_name_mode == 0) {
                    mnDiagram_DrawFighterHeaders(gobj, col_idx, row_idx);
                } else {
                    mnDiagram_DrawNameHeaders(gobj, col_idx, row_idx);
                }
            } else {
                u16 indices = data->fighter_cursor_pos;
                int row_idx;
                u8 col_idx;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_ClearGrid(gobj);
                mnDiagram_DrawGridValues(gobj, col_idx, indices >> 8,
                                         (u8) (data2->is_name_mode == 1));
                if (data2->is_name_mode == 0) {
                    mnDiagram_DrawFighterHeaders(gobj, col_idx, row_idx);
                } else {
                    mnDiagram_DrawNameHeaders(gobj, col_idx, row_idx);
                }
            }
            if (data->is_name_mode != 0) {
                count = GetNameCount();
            } else {
                count = getFighterCount();
            }
            data2 = gobj->user_data;
            updateScrollArrowVisibility(data2, count);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    mnDiagram_UpdateScrollArrows(gobj);
}

void mnDiagram_DrawCellValue(HSD_GObj* arg0, u8 arg1, u8 arg2, int arg3)
{
    Diagram* data_alias;
    f32 row_offset_adj;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Diagram* data;
    StaticModelDesc* model;
    int digit_count;
    int digit;
    int i;
    f32 x_spacing;
    f32 y_spacing;
    f32 base;
    f32 rowf;
    f32 row_offset;
    f32 col_offset;
    u8 col = arg1;
    u8 row = arg2;
    f32 y_offset;

    data = arg0->user_data;
    data_alias = data;

    jobj = data->jobjs[11];
    base = HSD_JObjGetTranslationX(jobj);
    jobj2 = data->jobjs[12];
    x_spacing = HSD_JObjGetTranslationX(jobj2) - base;

    jobj = data->jobjs[7];
    base = HSD_JObjGetTranslationX(jobj);
    jobj2 = data->jobjs[8];
    y_spacing = HSD_JObjGetTranslationX(jobj2) - base;

    jobj = data->jobjs[9];
    base = HSD_JObjGetTranslationY(jobj);
    jobj2 = data->jobjs[10];
    y_offset = HSD_JObjGetTranslationY(jobj2) - base;

    (void) y_offset;
    digit_count = mn_GetDigitCount(arg3);
    col_offset = y_spacing * (f32) col;
    rowf = (f32) row;
    row_offset = y_offset * rowf;
    (void) row_offset;
    (void) col_offset;
    row_offset_adj = row_offset - 0.4f;

    model = &MenMainNmB_Top;
    for (i = 0; i < digit_count; i++) {
        digit = mn_GetDigitAt(arg3, i);
        jobj = HSD_JObjLoadJoint(model->joint);
        HSD_JObjAddAnimAll(jobj, model->animjoint, model->matanim_joint,
                           model->shapeanim_joint);
        base = (f32) digit;
        HSD_JObjReqAnimAll(jobj, base);
        HSD_JObjAnimAll(jobj);
        if (col < 7) {
            HSD_JObjSetTranslateX(jobj, (x_spacing * (f32) i) + col_offset);
        } else {
            HSD_JObjSetTranslateX(jobj,
                                  (x_spacing * (f32) i) + col_offset + 0.4f);
        }
        if (row < 10) {
            HSD_JObjSetTranslateY(jobj, row_offset);
        } else {
            HSD_JObjSetTranslateY(jobj, row_offset_adj);
        }
        HSD_JObjAddChild(data_alias->jobjs[11], jobj);
    }
}

static inline int mnDiagram_GetFighterPairKOs(u8 fighter, u8 opponent)
{
    SelectableCharacterKind kind = fighter;
    return GetPersistentFighterData(kind)->fighter_kos[opponent];
}

void mnDiagram_DrawGridValues(HSD_GObj* arg0, s32 row_start, s32 col_start,
                              u8 arg3)
{
    int name_col;
    u8 is_name_mode = arg3;
    int unlocked_count;
    int col_unlocked_count;
    int bottom_unlocked_count;
    int bottom_col;
    int fighter_col;
    int row;
    int entry_count;
    s32 total_kos;
    int row_name;
    int col_name;
    int row_fighter;
    u8 col_fighter;

    for (row = 0; row <= 0xA; row += 1) {
        if (row == 0xA) {
            for (bottom_col = 0; bottom_col < 7; bottom_col++) {
                if (is_name_mode != 0) {
                    entry_count = GetNameCount();
                    if (entry_count > bottom_col) {
                        mnDiagram_DrawCellValue(
                            arg0, (u8) bottom_col, (u8) row,
                            mnDiagram_SumNameFalls(
                                mnDiagram_GetVisibleNameCursorFrom(
                                    col_start, bottom_col)));
                    }
                } else {
                    bottom_unlocked_count = mnDiagram_CountUnlockedFighters();
                    if (bottom_unlocked_count > bottom_col) {
                        mnDiagram_DrawCellValue(
                            arg0, (u8) bottom_col, (u8) row,
                            mnDiagram_SumFighterFalls(
                                mnDiagram_GetVisibleFighterCursorFrom2(
                                    col_start, bottom_col)));
                    }
                }
            }
        } else if (is_name_mode != 0) {
            entry_count = GetNameCount();
            if (entry_count > row) {
                for (name_col = 0; name_col <= 7; name_col += 1) {
                    if ((name_col == 7) || (entry_count = GetNameCount(),
                                            (entry_count > name_col)))
                    {
                        row_name =
                            mnDiagram_GetVisibleNameCursorFrom(row_start, row);
                        if (name_col == 7) {
                            total_kos = mnDiagram_GetNameTotalKOs(row_name);
                            mnDiagram_DrawCellValue(arg0, (u8) name_col,
                                                    (u8) row, total_kos);
                        } else {
                            int ko_count;
                            col_name = mnDiagram_GetVisibleNameCursorFrom(
                                col_start, name_col);
                            ko_count = getNamePairKOs((u8) row_name, col_name);
                            mnDiagram_DrawCellValue(arg0, (u8) name_col,
                                                    (u8) row, ko_count);
                        }
                    }
                }
            }
        } else {
            unlocked_count = mnDiagram_CountUnlockedFighters();
            if (unlocked_count > row) {
                for (fighter_col = 0; fighter_col <= 7; fighter_col += 1) {
                    if ((fighter_col == 7) ||
                        (col_unlocked_count =
                             mnDiagram_CountUnlockedFighters(),
                         (col_unlocked_count > fighter_col)))
                    {
                        row_fighter = mnDiagram_GetVisibleFighterCursorFrom2(
                            row_start, row);
                        if (fighter_col == 7) {
                            total_kos =
                                mnDiagram_GetFighterTotalKOs(row_fighter);
                            total_kos =
                                total_kos > 999999 ? 999999 : total_kos;
                            mnDiagram_DrawCellValue(arg0, (u8) fighter_col,
                                                    (u8) row, total_kos);
                        } else {
                            col_fighter =
                                mnDiagram_GetVisibleFighterCursorFrom2(
                                    col_start, fighter_col);
                            mnDiagram_DrawCellValue(
                                arg0, (u8) fighter_col, (u8) row,
                                mnDiagram_GetFighterPairKOs(row_fighter,
                                                            col_fighter));
                        }
                    }
                }
            }
        }
    }
}

static inline f32 getColumnReferenceX(Diagram* data)
{
    return HSD_JObjGetTranslationX(data->jobjs[7]);
}

static inline f32 getRowReferenceY(Diagram* data)
{
    return HSD_JObjGetTranslationY(data->jobjs[9]);
}

void mnDiagram_DrawNameHeaders(HSD_GObj* arg0, s32 arg1, s32 arg2)
{
    Diagram* data = arg0->user_data;
    HSD_Text* row_text;
    int name_id;

    // Column headers
    {
        HSD_Text* text;
        text = HSD_SisLib_803A6754(0, 1);
        data->col_header_text = text;
        text->font_size.x = 0.02f;
        text->font_size.y = 0.03f;
        {
            HSD_JObj* j = data->jobjs[7];
            mnDiagram_TextSetPos(text, -1.3f + HSD_JObjGetTranslationX(j),
                                 -0.5f - HSD_JObjGetTranslationY(j),
                                 HSD_JObjGetTranslationZ(j));
        }

        {
            int i;
            for (i = 0; i < 7; i++) {
                if (GetNameCount() > i) {
                    f32 x_spacing;
                    name_id = mnDiagram_GetVisibleNameCursorFrom(arg2, i);
                    x_spacing = getColumnReferenceX(data);
                    x_spacing =
                        HSD_JObjGetTranslationX(data->jobjs[8]) - x_spacing;
                    HSD_SisLib_803A6B98(text, (x_spacing * i) / 0.02f, 0.0f,
                                        GetNameText(name_id));
                }
            }
        }
    }

    // Row headers
    row_text = HSD_SisLib_803A6754(0, 1);
    data->row_header_text = row_text;
    row_text->font_size.x = 0.02f;
    row_text->font_size.y = 0.03f;
    {
        HSD_JObj* j = data->jobjs[9];
        f32 z = HSD_JObjGetTranslationZ(j);
        f32 y = -0.5f - HSD_JObjGetTranslationY(j);
        row_text->pos_x = -1.3f + HSD_JObjGetTranslationX(j);
        row_text->pos_y = y;
        row_text->pos_z = z;
    }

    {
        int i;
        for (i = 0; i < 0xA; i++) {
            if (GetNameCount() > i) {
                f32 y_spacing;
                name_id = mnDiagram_GetVisibleNameCursorFrom(arg1, i);
                y_spacing = getRowReferenceY(data);
                y_spacing =
                    HSD_JObjGetTranslationY(data->jobjs[10]) - y_spacing;
                HSD_SisLib_803A6B98(row_text, 0.0f, -((y_spacing * i) / 0.03f),
                                    GetNameText(name_id));
            }
        }
    }
}

HSD_JObj* mnDiagram_CreateFighterIcon(int idx, int arg1)
{
    HSD_JObj* sp10;
    StaticModelDesc* model = &MenMainFaceB_Top;
    HSD_JObj* temp_r3;
    f32 var_f1;

    temp_r3 = HSD_JObjLoadJoint(model->joint);
    HSD_JObjAddAnimAll(temp_r3, model->animjoint, model->matanim_joint,
                       model->shapeanim_joint);
    if (arg1 != 0) {
        var_f1 = 1.0f;
    } else {
        var_f1 = 0.0f;
    }
    HSD_JObjReqAnimAll(temp_r3, var_f1);
    HSD_JObjAnimAll(temp_r3);
    lb_80011E24(temp_r3, &sp10, 2, -1);
    HSD_JObjReqAnimAll(sp10, idx);
    HSD_JObjAnimAll(sp10);
    return temp_r3;
}

static inline HSD_JObj* mnDiagram_LoadHeaderIcon(StaticModelDesc* joint_data,
                                                 int fighter_id,
                                                 HSD_JObj** child)
{
    HSD_JObj* jobj = HSD_JObjLoadJoint(joint_data->joint);
    HSD_JObjAddAnimAll(jobj, joint_data->animjoint, joint_data->matanim_joint,
                       joint_data->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, child, 2, -1);
    HSD_JObjReqAnimAll(*child, (f32) (fighter_id & 0xFF));
    HSD_JObjAnimAll(*child);
    return jobj;
}

/// @pre rank is nonnegative.
static inline void getVisibleFighter(int start, int rank, int* fighter)
{
    while (rank >= 0) {
        if (rank == 0) {
            *fighter = mnDiagram_FighterDisplayOrder[start];
            return;
        }
        do {
            start++;
            if (start >= SELKIND_COUNT) {
                *fighter = SELKIND_COUNT;
                return;
            }
        } while (mn_IsFighterUnlocked(mnDiagram_GetFighterByIndex(start)) ==
                 0);
        rank--;
    }
}

void mnDiagram_DrawFighterHeaders(HSD_GObj* arg0, int arg1, int arg2)
{
    int row_fighter;
    s32 unlocked_count;
    StaticModelDesc* joint_data;
    Diagram* data = GET_DIAGRAM(arg0);
    int col_fighter;
    HSD_JObj* col_jobj;
    HSD_JObj* row_jobj;
    f32 x_spacing;
    f32 y_spacing;
    int i;
    // Preserve the original gap before the integer-to-float conversion slot.
    PAD_STACK(8);

    // Column headers (fighter icons)
    for (i = 0; i < 7; i++) {
        joint_data = &MenMainFaceB_Top;
        unlocked_count = mnDiagram_CountUnlockedFighters();
        if (unlocked_count > i) {
            HSD_JObj* child;
            getVisibleFighter(arg2, i, &col_fighter);
            col_jobj =
                mnDiagram_LoadHeaderIcon(joint_data, col_fighter, &child);
            {
                f32 reference_x = HSD_JObjGetTranslationX(data->jobjs[7]);
                x_spacing =
                    HSD_JObjGetTranslationX(data->jobjs[8]) - reference_x;
            }
            HSD_JObjSetTranslateX(col_jobj, x_spacing * i);
            HSD_JObjAddChild(data->jobjs[7], col_jobj);
        }
    }

    // Row headers (fighter icons)
    joint_data = &MenMainFaceB_Top;
    for (i = 0; i < 10; i++) {
        unlocked_count = mnDiagram_CountUnlockedFighters();
        if (unlocked_count > i) {
            HSD_JObj* row_child;
            getVisibleFighter(arg1, i, &row_fighter);
            row_jobj = HSD_JObjLoadJoint(joint_data->joint);
            HSD_JObjAddAnimAll(row_jobj, joint_data->animjoint,
                               joint_data->matanim_joint,
                               joint_data->shapeanim_joint);
            HSD_JObjReqAnimAll(row_jobj, 0.0f);
            HSD_JObjAnimAll(row_jobj);
            lb_80011E24(row_jobj, &row_child, 2, -1);
            HSD_JObjReqAnimAll(row_child, (f32) (row_fighter & 0xFF));
            HSD_JObjAnimAll(row_child);
            {
                f32 reference_y = HSD_JObjGetTranslationY(data->jobjs[9]);
                y_spacing =
                    HSD_JObjGetTranslationY(data->jobjs[10]) - reference_y;
            }
            HSD_JObjSetTranslateY(row_jobj, y_spacing * i);
            HSD_JObjAddChild(data->jobjs[9], row_jobj);
        }
    }
}

void mnDiagram_CursorProc(HSD_GObj* gobj)
{
    HSD_JObj* sp_jobj;
    u16* selection;
    int col;
    int row;
    f32 x_spacing;
    f32 y_spacing;
    Diagram* data;

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        HSD_GObjFree(gobj);
        return;
    }

    data = mnDiagram_GetCurrentDiagramData();
    lb_80011E24(gobj->hsd_obj, &sp_jobj, 3, -1);

    col = *(selection = &mn_804A04F0.hovered_selection) >> 8;
    x_spacing = getColumnReferenceX(data);
    x_spacing = HSD_JObjGetTranslationX(data->jobjs[8]) - x_spacing;
    HSD_JObjSetTranslateX(sp_jobj, x_spacing * (col - 3));

    lb_80011E24(gobj->hsd_obj, &sp_jobj, 4, -1);
    row = *selection & 0xFF;
    y_spacing = getRowReferenceY(data);
    y_spacing = HSD_JObjGetTranslationY(data->jobjs[10]) - y_spacing;
    HSD_JObjSetTranslateY(sp_jobj, y_spacing * (row - 4.5) - 0.1F);

    lb_80011E24(gobj->hsd_obj, &sp_jobj, 2, -1);
    HSD_JObjSetTranslateX(sp_jobj, x_spacing * (col - 3));
    HSD_JObjSetTranslateY(sp_jobj, y_spacing * (row - 4.5) - 0.1F);
}

void mnDiagram_CreateCursor(void)
{
    StaticModelDesc* model;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    PAD_STACK(40);

    model = &MenMainCursorB1_Top;
    gobj = GObj_Create(6, 7, 0x80);
    jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, mnDiagram_CursorProc, 0);
}

void mnDiagram_CreateScreen(u8 arg0)
{
    int col_idx;
    int row_idx;
    Diagram* d;
    int col_idx2;
    int row_idx2;
    Diagram* d2;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* anim_jobj;
    Diagram* user_data;
    Diagram* data2;
    int count;
    StaticModelDesc* model;
    int i;
    u16 indices;

    model = &MenMainConB1_Top;
    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram_ScreenGObj = gobj;
    jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, model->animjoint, model->matanim_joint,
                       model->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);

    user_data = HSD_MemAlloc(sizeof(Diagram));
    HSD_ASSERTREPORT(0x90E, user_data, "Can't get user_data.\n");
    user_data->saved_menu = mn_804A04F0.cur_menu;
    user_data->saved_selection = mn_804A04F0.hovered_selection;
    user_data->anim_state = arg0;
    user_data->fighter_cursor_pos = (u8) user_data->fighter_cursor_pos;
    user_data->fighter_cursor_pos &= 0xFF00;
    user_data->name_cursor_pos = (u8) user_data->name_cursor_pos;
    user_data->name_cursor_pos &= 0xFF00;
    user_data->popup_gobj = NULL;
    user_data->row_header_text = NULL;
    user_data->col_header_text = NULL;

    if (GetNameCount() != 0) {
        user_data->is_name_mode = gmMainLib_GetGameRules()->xD;
    } else {
        gmMainLib_GetGameRules()->xD = 0;
        user_data->is_name_mode = gmMainLib_GetGameRules()->xD;
    }

    GObj_InitUserData(gobj, 0, HSD_Free, user_data);

    for (i = 0; i < 13; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }

    HSD_GObj_SetupProc(gobj, mnDiagram_OnFrame, 0);

    if (arg0 == 0) {
        anim_jobj = user_data->jobjs[1];
        HSD_JObjReqAnimAll(anim_jobj, mnDiagram_IntroAnim.end_frame);
        HSD_JObjAnimAll(anim_jobj);

        mnDiagram_CreateCursor();

        count = getEntryCount(user_data);

        updateScrollArrowVisibility(GET_DIAGRAM(gobj), count);

        if (user_data->is_name_mode != 0) {
            indices = user_data->name_cursor_pos;
            row_idx = indices >> 8;
            col_idx = indices & 0xFF;
            d = GET_DIAGRAM(gobj);
            refreshGrid(gobj, col_idx, row_idx, d);
        } else {
            indices = user_data->fighter_cursor_pos;
            row_idx2 = indices >> 8;
            col_idx2 = indices & 0xFF;
            d2 = GET_DIAGRAM(gobj);
            refreshGrid(gobj, col_idx2, row_idx2, d2);
        }
    }
}

/// Initialize VS Records diagram screen.
/// @param arg0 If non-zero, load DAT archive symbols
/// @param arg1 Initial mode (passed to mnDiagram_CreateScreen)
void mnDiagram_Init(u8 arg0, u8 arg1)
{
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_Archive* archive;
    u8 mode_storage[4];

    mode_storage[0] = arg1;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1E;
    mn_804A04F0.x10 = 0;
    mn_804A04F0.hovered_selection = 0;

    if (arg0) {
        archive = mn_804D6BB8;
        lbArchive_LoadSections(
            archive, &MenMainConB1_Top.joint, "MenMainConB1_Top_joint",
            &MenMainConB1_Top.animjoint, "MenMainConB1_Top_animjoint",
            &MenMainConB1_Top.matanim_joint, "MenMainConB1_Top_matanim_joint",
            &MenMainConB1_Top.shapeanim_joint,
            "MenMainConB1_Top_shapeanim_joint", &MenMainCursorB1_Top.joint,
            "MenMainCursorB1_Top_joint", &MenMainFaceB_Top.joint,
            "MenMainFaceB_Top_joint", &MenMainFaceB_Top.animjoint,
            "MenMainFaceB_Top_animjoint", &MenMainFaceB_Top.matanim_joint,
            "MenMainFaceB_Top_matanim_joint",
            &MenMainFaceB_Top.shapeanim_joint,
            "MenMainFaceB_Top_shapeanim_joint", &MenMainNmB_Top.joint,
            "MenMainNmB_Top_joint", &MenMainNmB_Top.animjoint,
            "MenMainNmB_Top_animjoint", &MenMainNmB_Top.matanim_joint,
            "MenMainNmB_Top_matanim_joint", &MenMainNmB_Top.shapeanim_joint,
            "MenMainNmB_Top_shapeanim_joint", &MenMainSubB1_Top.joint,
            "MenMainSubB1_Top_joint", &MenMainSubB1_Top.animjoint,
            "MenMainSubB1_Top_animjoint", &MenMainSubB1_Top.matanim_joint,
            "MenMainSubB1_Top_matanim_joint",
            &MenMainSubB1_Top.shapeanim_joint,
            "MenMainSubB1_Top_shapeanim_joint", &MenMainConB2_Top.joint,
            "MenMainConB2_Top_joint", &MenMainConB2_Top.animjoint,
            "MenMainConB2_Top_animjoint", &MenMainConB2_Top.matanim_joint,
            "MenMainConB2_Top_matanim_joint",
            &MenMainConB2_Top.shapeanim_joint,
            "MenMainConB2_Top_shapeanim_joint", &MenMainConB3_Top.joint,
            "MenMainConB3_Top_joint", &MenMainConB3_Top.animjoint,
            "MenMainConB3_Top_animjoint", &MenMainConB3_Top.matanim_joint,
            "MenMainConB3_Top_matanim_joint",
            &MenMainConB3_Top.shapeanim_joint,
            "MenMainConB3_Top_shapeanim_joint", &MenMainCursorB3_Top.joint,
            "MenMainCursorB3_Top_joint", 0);
    }

    mnDiagram_SortFightersByKOs();
    mnDiagram_SortNamesByKOs();
    mnDiagram_CreateScreen(mode_storage[0]);

    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObj_SetupProc(gobj, mnDiagram_InputProc, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
