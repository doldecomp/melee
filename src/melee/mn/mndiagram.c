#define MNDIAGRAM_SOURCE
#include "mndiagram.static.h"
#include "mndiagram2.static.h"

#include "baselib/debug.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "dolphin/types.h"
#include "gm/gm_1601.h"
#include "gm/gmmain_lib.h"
#include "gm/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mndiagram2.h"
#include "mn/mndiagram3.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"

#define GET_DIAGRAM(gobj) ((Diagram*) HSD_GObjGetUserData(gobj))

/// Sorted fighter indices array (25 fighters + padding)
typedef struct mnDiagram_804A0750_t {
    u8 sorted_fighters[0x19];
    u8 pad_19[3];
} mnDiagram_804A0750_t;
STATIC_ASSERT(sizeof(mnDiagram_804A0750_t) == 0x1C);

/// Sorted name indices array (120 names)
typedef struct mnDiagram_804A076C_t {
    u8 sorted_names[0x78];
} mnDiagram_804A076C_t;
STATIC_ASSERT(sizeof(mnDiagram_804A076C_t) == 0x78);

/// Archive asset pointers struct (for mnDiagram_802437E8)
/// Cast from &mnDiagram_804A0750 to access asset arrays
typedef struct mnDiagram_Assets {
    /* 0x00 */ u8 sorted_fighters[0x19];
    /* 0x19 */ u8 pad_19[3];
    /* 0x1C */ u8 sorted_names[0x78];
    /* 0x94 */ void* SubB1[4];
    /* 0xA4 */ void* NmB[4];
    /* 0xB4 */ void* FaceB[4];
    /* 0xC4 */ void* CursorB1[4];
    /* 0xD4 */ void* ConB1[4];
    /* 0xE4 */ void* ConB2[4];
    /* 0xF4 */ void* ConB3[4];
    /* 0x104 */ void* CursorB3[5];
} mnDiagram_Assets;
STATIC_ASSERT(sizeof(mnDiagram_Assets) == 0x118);

/// User data structure for mnDiagram_PopupCleanup callback.
/// Overlay of Diagram - only accesses text array.
typedef struct mnDiagram_CleanupData {
    /* 0x00 */ char jobjs_reserved[0x38]; ///< JObj array (unused by cleanup)
    /* 0x38 */ HSD_Text* text[6];         ///< Text objects to free
} mnDiagram_CleanupData;

/// User data structure for mnDiagram_ExitAnimProc callback.
/// Overlay of Diagram - only accesses jobj at offset 0x0C.
typedef struct mnDiagram_AnimData {
    /* 0x00 */ char header_reserved[0x0C]; ///< menu state (unused by anim)
    /* 0x0C */ HSD_JObj* jobj;             ///< JObj for exit animation
} mnDiagram_AnimData;

/// BSS variables - sorted player arrays
mnDiagram_804A0750_t mnDiagram_804A0750;
mnDiagram_804A076C_t mnDiagram_804A076C;

static AnimLoopSettings mnDiagram_803EE768 = { 0.0f, 9.0f, -0.1f };

static u8 mnDiagram_803EE74C[0x1C] = {
    8,    1,    6,    0x10, 0x11, 4,   2,   0xD, 0xB, 0,
    5,    0xC,  0xE,  0x12, 7,    0xF, 0xA, 9,   3,   0x15,
    0x18, 0x13, 0x14, 0x17, 0x16, 0,   0,   0,
};

static Point3d mnDiagram_803EE728[3] = {
    { 4.0F, 1.0F, 0.0F },
    { -3.0F, 0.8F, 0.0F },
    { -1.0F, 0.7F, 0.0F },
};

/// Overlay over &mnDiagram_803EE728 to reach the trailing
/// animation/text-layout data the popup/cursor procs read at fixed offsets.
typedef struct mnDiagram_AnimTable {
    /* 0x00 */ Point3d points[3];
    /* 0x24 */ u8 pad_24[0x1C];
    /* 0x40 */ AnimLoopSettings x40;
    /* 0x4C */ u8 pad_4C[0xC];
    /* 0x58 */ AnimLoopSettings arrow_anim;
    /* 0x64 */ AnimLoopSettings cursor_anim;
    /* 0x70 */ char x70[0x18];
    /* 0x88 */ char x88[0xC];
    /* 0x94 */ char x94[0x14];
} mnDiagram_AnimTable;

#define GET_DIAGRAM_ANIM_TABLE() ((mnDiagram_AnimTable*) &mnDiagram_803EE728)

static s32 mnDiagram_804D4FA0 = 0xFF;

/// @brief Gets the fighter ID at the given sorted index.
/// @param idx Index into the sorted fighter list
/// @return Fighter ID
u8 mnDiagram_GetFighterByIndex(int idx)
{
    return mnDiagram_804A0750.sorted_fighters[idx];
}

/// @brief Gets the name ID at the given sorted index.
/// @param idx Index into the sorted name list
/// @return Name ID
u8 mnDiagram_GetNameByIndex(int idx)
{
    return mnDiagram_804A076C.sorted_names[idx];
}

/// @brief Checks if a distance stat exceeds 1 mile (display cap).
/// @details Distance stats are stored in internal game units and converted
///          for display by dividing by ~30.5 to get feet. When the distance
///          exceeds these thresholds (~1 mile), the display caps at "1 mi."
///          instead of showing larger values.
/// @param distance The distance value in internal game units.
/// @return true if distance >= 1 mile, false otherwise.
bool mnDiagram_IsDistanceOverflow(u32 distance)
{
    if (lbLang_IsSavedLanguageUS() != 0) {
        /// 160,934 internal units / 30.5 = ~5,276 ft = 1 mile
        if (distance >= 0x274A6) {
            return true;
        }
        return false;
    } else {
        /// 100,000 internal units / 30.5 = ~3,278 meters
        if (distance >= 0x186A0) {
            return true;
        }
        return false;
    }
}

/// @brief Converts internal distance units to display units.
/// @details For US locale: Returns feet (or miles if >= 1 mile).
///          For other locales: Returns centimeters (or km if >= 1km).
/// @param distance Distance in internal game units.
/// @return Distance in display units (feet/cm or miles/km).
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

s32 mnDiagram_GetHitPercentage(int is_name_mode, u8 player_index)
{
    f32 player_attacks;
    f32 tag_player_attacks;

    if ((u8) is_name_mode != 0) {
        if (GetPersistentNameData(player_index)->attacks_total != 0) {
            tag_player_attacks =
                GetPersistentNameData(player_index)->attacks_total;
            return (
                100.0f *
                (100.0f * (GetPersistentNameData(player_index)->attacks_hit /
                           tag_player_attacks)));
        }
        return 0;
    }
    if (GetPersistentFighterData(player_index)->attacks_total != 0) {
        player_attacks = GetPersistentFighterData(player_index)->attacks_total;
        return (
            100.0f *
            (100.0f * (GetPersistentFighterData(player_index)->attacks_hit /
                       player_attacks)));
    }
    return 0;
}

s32 mnDiagram_GetPlayPercentage(u8 is_name_mode, u8 player_index)
{
    f32 total_play_time;
    s32 i;
    f32 zero = 0.0f;

    if ((u8) is_name_mode != 0) {
        total_play_time = 0.0f;
        i = 0;
        do {
            total_play_time += GetPersistentNameData(i)->play_time;
            i += 1;
        } while (i < 0x78);
        if (total_play_time != zero) {
            return (s32) (100.0f *
                          (100.0f *
                           (GetPersistentNameData(player_index)->play_time /
                            total_play_time)));
        }
        return 0;
    }
    total_play_time = 0.0f;
    i = 0;
    do {
        total_play_time += GetPersistentFighterData(i)->play_time;
        i += 1;
    } while (i < 0x19);
    if (total_play_time != zero) {
        return (s32) (100.0f *
                      (100.0f *
                       (GetPersistentFighterData(player_index)->play_time /
                        total_play_time)));
    }
    return 0;
}

s32 mnDiagram_GetAveragePlayerCount(int is_name_mode, u8 player_index)
{
    f32 temp_f31;
    f32 temp_f31_2;

    if ((u8) is_name_mode != 0) {
        if ((u16) GetPersistentNameData((s32) player_index)->match_count != 0)
        {
            temp_f31_2 =
                (f32) GetPersistentNameData((s32) player_index)->match_count;
            return (s32) (100.0f *
                          ((f32) GetPersistentNameData((s32) player_index)
                               ->total_player_count /
                           temp_f31_2));
        }
        return 0;
    }
    if ((u16) GetPersistentFighterData((s32) player_index)->match_count != 0) {
        temp_f31 =
            (f32) GetPersistentFighterData((s32) player_index)->match_count;
        return (s32) (100.0f *
                      ((f32) GetPersistentFighterData((s32) player_index)
                           ->total_player_count /
                       temp_f31));
    }
    return 0;
}

/// @brief Gets total KOs scored by a name against all other names.
/// @param field_index Index of the name tag to query.
/// @return Sum of KOs scored by this name against all existing names.
int mnDiagram_GetNameTotalKOs(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < 0x78; i++) {
        if (GetNameText(i & 0xFF)) {
            total += GetPersistentNameData(field_index)->vs_kos[(u8) i];
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
    for (i = 0; i < 0x78; i++) {
        if (GetNameText(i & 0xFF)) {
            total += GetPersistentNameData((u8) i)->vs_kos[field_index];
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
    int i;
    for (i = 0; i < 25; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            total +=
                GetPersistentFighterData(field_index)->fighter_kos[(u8) i];
        }
    }
    return total;
}

static inline int mnDiagram_SumFighterKOs(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < 25; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            total +=
                GetPersistentFighterData(field_index)->fighter_kos[(u8) i];
        }
    }
    return total;
}

static inline int mnDiagram_SumFighterKOsClamped(u8 field_index)
{
    int total = 0;
    int i;
    for (i = 0; i < 25; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            total +=
                GetPersistentFighterData(field_index)->fighter_kos[(u8) i];
        }
    }
    if (total > 999999) {
        total = 999999;
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
    for (i = 0; i < 25; i++) {
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

/// @brief Counts the number of unlocked fighters (inline-expanded form).
/// @return Number of unlocked fighters.
static inline int mnDiagram_CountUnlockedFightersInline(void)
{
    int count = 0;
    int i;
    for (i = 0; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i)) {
            count++;
        }
    }
    return count;
}

/// @brief Formats a number with optional decimal places.
/// @param buf Output buffer for the string.
/// @param val The value to format (treat last decimal_places digits as
/// decimal).
/// @param decimal_places Number of decimal places (0 = integer only).
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
    buf[digit_count] = mnDiagram_804D4FA4;
}

/// @brief Formats seconds as MM:SS string.
/// @param buf Output buffer for the string.
/// @param seconds Time in seconds.
void mnDiagram_FormatTime(char* buf, s32 seconds)
{
    int i;
    int digit_count;
    s32 minutes;
    s32 secs;

    minutes = seconds / 60;
    secs = seconds % 60;
    digit_count = mn_GetDigitCount(minutes);
    for (i = 0; i < digit_count; i++) {
        buf[i] = mn_GetDigitAt(minutes, (digit_count - 1) - i) + '0';
    }
    buf[digit_count++] = ':';
    buf[digit_count++] = (secs / 10) + '0';
    buf[digit_count++] = (secs % 10) + '0';
    buf[digit_count] = mnDiagram_804D4FA4;
}

/// @brief Converts a number to a null-terminated string.
/// @param buf Output buffer for the string.
/// @param val The number to convert.
void mnDiagram_IntToStr(char* buf, u32 val)
{
    int i;
    int digit_count;

    digit_count = mn_GetDigitCount(val);
    for (i = 0; i < digit_count; i++) {
        buf[i] = mn_GetDigitAt(val, (digit_count - 1) - i) + '0';
    }
    buf[digit_count] = mnDiagram_804D4FA4;
}

/// @brief Gets the previous valid name index.
/// @param idx Current name index.
/// @return Previous name index with a valid name, or original if none found.
u8 mnDiagram_GetPrevNameIndex(s32 idx)
{
    s32 original, i;

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
    s32 original, i;

    original = i = idx;

    do {
        i++;
        if (i >= 0x78) {
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
    s32 original;

    ptr = mnDiagram_804A0750.sorted_fighters + idx;
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
    s32 original;

    ptr = mnDiagram_804A0750.sorted_fighters + idx;
    original = idx;

    do {
        idx++;
        ptr++;
        if (idx >= 0x19) {
            return original;
        }
    } while (mn_IsFighterUnlocked(*ptr) == 0);

    return idx;
}

/// @brief Gets play time for a specific fighter under a name tag.
/// @param name_idx Name tag index.
/// @param fighter_idx Fighter index (0-24).
/// @return Play time in seconds for this fighter under this name.
u32 mnDiagram_GetNamePlayTimeByFighter(int name_idx, int fighter_idx)
{
    return GetPersistentNameData(name_idx)->play_time_by_fighter[fighter_idx];
}

typedef struct RankEntry {
    u8 fighter_id;
    u32 value;
} RankEntry;

static inline int CountTiedFighters(int name, int min_fighter, u32 min_time)
{
    int tie_count = 0;
    int i = tie_count;
    int offset = tie_count;
    do {
        if (mn_IsFighterUnlocked(i) != 0 && i != min_fighter) {
            if (GetPersistentNameData(name)->play_time_by_fighter[i] ==
                min_time)
            {
                tie_count++;
            }
        }
        i++;
        offset += 4;
    } while (i < 0x19);
    return tie_count;
}

static inline int CheckAllZeroPlayTime(int name_idx)
{
    int i = 0;
    int offset = i;
    while (1) {
        if (GetPersistentNameData(name_idx)->play_time_by_fighter[i] != 0U) {
            return 0;
        }
        i++;
        offset += 4;
        if (i >= 0x19) {
            return 1;
        }
    }
}

int mnDiagram_GetRankedFighterForName(int rank, int name_idx,
                                      u32 (*func)(int, int))
{
    int _pad[2];
    RankEntry entries[25];
    int i, j;

    (void) _pad;

    if (CheckAllZeroPlayTime(name_idx) != 0) {
        return 0x19;
    }

    // Fill entries array with fighter id and value from func
    for (i = 0; i < 0x19; i++) {
        entries[i].fighter_id = i;
        entries[i].value = func(name_idx, i);
    }

    // Selection sort by value (descending)
    for (i = 0; i < 0x19; i++) {
        int max_idx = i;
        for (j = i + 1; j < 0x19; j++) {
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
    for (i = 0; i < 0x19; i++) {
        if (gm_80164840(gm_8016400C(entries[i].fighter_id)) != 0) {
            if (rank != 0) {
                rank--;
                // Check for ties - skip fighters with same value
                for (j = i + 1; j < 0x19; j++) {
                    if (func(name_idx, entries[i].fighter_id) ==
                        func(name_idx, entries[j].fighter_id))
                    {
                        i++;
                        if (rank != 0) {
                            rank--;
                        } else {
                            return 0x19;
                        }
                    }
                }
            } else {
                // rank == 0, check if value is non-zero and no tie
                if (func(name_idx, entries[i].fighter_id) != 0U) {
                    if (i + 1 < 0x19) {
                        if (func(name_idx, entries[i].fighter_id) ==
                            func(name_idx, entries[i + 1].fighter_id))
                        {
                            return 0x19;
                        }
                    }
                    return entries[i].fighter_id;
                }
                return 0x19;
            }
        }
    }
    return 0x19;
}

static inline int mnDiagram_AllPlayTimesZero(u8 name)
{
    int i;
    int offset;

    i = 0;
    offset = i;
    for (;;) {
        if (GetPersistentNameData(name)->play_time_by_fighter[i] != 0U) {
            return 0;
        }
        i++;
        offset += 4;
        if (i >= 0x19) {
            return 1;
        }
    }
}

u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx)
{
    int i;
    int min_fighter;
    int count;

    if (mnDiagram_AllPlayTimesZero(name_idx)) {
        return 0x19;
    }

    // Find fighter with minimum play time
    min_fighter = 0;
    for (i = 1; i < 0x19; i++) {
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
    for (i = 0; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i) != 0 &&
            GetPersistentNameData(name_idx)->play_time_by_fighter[i] == 0U)
        {
            count++;
        }
    }
    if (count >= 2) {
        return 0x19;
    }

    // Check for ties
    count = 0;
    for (i = 0; i < 0x19; i++) {
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
        return 0x19;
    }

    return min_fighter;
}

void mnDiagram_8023FA6C(void)
{
    u32 totals[0x19];
    u8* dst = mnDiagram_804A0750.sorted_fighters;
    u8* dst_iter;
    u8* candidate;
    int i, j;
    PAD_STACK(12);

    dst_iter = dst;
    for (i = 0; i < 0x19; i++, dst_iter++) {
        u8 fighter;
        *dst_iter = mnDiagram_803EE74C[i];
        fighter = mnDiagram_803EE74C[i];
        totals[mnDiagram_803EE74C[i]] = mnDiagram_SumFighterKOs(fighter);
    }

    for (i = 0; i < 0x19; i++) {
        int max_idx;
        j = i;
        candidate = &dst[++j];
        max_idx = i;
        for (; j < 0x19; candidate++, j++) {
            if (mn_IsFighterUnlocked(*candidate) != 0) {
                if ((totals[mnDiagram_804A0750.sorted_fighters[max_idx]] <
                     totals[*candidate]) ||
                    ((mn_IsFighterUnlocked(
                          mnDiagram_804A0750.sorted_fighters[max_idx]) == 0) &&
                     (mn_IsFighterUnlocked(*candidate) != 0)))
                {
                    max_idx = j;
                }
            }
        }
        if (max_idx != i) {
            u8 temp = mnDiagram_804A0750.sorted_fighters[max_idx];
            while (max_idx > i) {
                mnDiagram_804A0750.sorted_fighters[max_idx] =
                    mnDiagram_804A0750.sorted_fighters[max_idx - 1];
                max_idx--;
            }
            mnDiagram_804A0750.sorted_fighters[i] = temp;
        }
    }
}

static inline int mnDiagram_SumNameKOs(u8 field_index)
{
    int total;
    int j;
    total = 0;
    for (j = total; j < 0x78; j++) {
        if (GetNameText(j & 0xFF)) {
            total += GetPersistentNameData(field_index)->vs_kos[(u8) j];
        }
    }
    return total;
}

void mnDiagram_8023FC28(void)
{
    u32 totals[0x78];
    int max_idx;
    u8* dst_iter;
    int i;
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
    u8* dst = assets->sorted_names;
    u32* tp;
    int n;
    int j;
    PAD_STACK(12);

    dst_iter = dst;
    tp = totals;
    for (n = 0; n < 0x78; n++, dst_iter++, tp++) {
        *dst_iter = (u8) n;
        *tp = mnDiagram_SumNameKOs(n & 0xFF);
    }

    for (i = 0; i < 0x78; i++) {
        max_idx = i;
        for (j = i + 1; j < 0x78; j++) {
            if ((GetNameText(mnDiagram_804A076C.sorted_names[j]) != NULL) &&
                ((totals[mnDiagram_804A076C.sorted_names[max_idx]] <
                  totals[mnDiagram_804A076C.sorted_names[j]]) ||
                 ((GetNameText(
                       (0, mnDiagram_804A076C.sorted_names[max_idx])) ==
                   NULL) &&
                  (GetNameText(mnDiagram_804A076C.sorted_names[j]) != NULL))))
            {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            u8* p = &assets->sorted_fighters[max_idx];
            u8 temp = *(p += sizeof(mnDiagram_804A0750_t));
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
#pragma dont_inline on
int mnDiagram_CountUnlockedFighters(void)
{
    int i;
    int count;
    i = 0;
    count = 0;
    for (; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            count++;
        }
    }
    return count;
}
#pragma dont_inline reset

void mnDiagram_PopupInputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    Diagram* data = mnDiagram_804D6C10->user_data;
    u64 input = Menu_GetAllInputs();
    if ((u32) input & 0x20) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(
            gobj, (void (*)(HSD_GObj*)) mnDiagram_InputProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_GObjPLink_80390228(data->popup_gobj);
        data->popup_gobj = NULL;
    }
}

static inline u8 mnDiagram_GetVisibleNameFrom(u8* sorted, int start, int rank)
{
    u8* p;
    u8* p2;
    int remaining;
    int idx;

    p = sorted;
    p = p + start;
    remaining = rank;
    idx = start;
    p = p + 0x1C;
    while (remaining > 0) {
        p2 = p;
    loop:
        idx++;
        p2++;
        p++;
        if (idx >= 0x78) {
            return 0x78;
        }
        if (GetNameText(*p2) == NULL) {
            goto loop;
        }
        remaining--;
    }
    p = sorted;
    p += idx;
    return p[0x1C];
}

static inline u8 mnDiagram_GetVisibleFighterFrom(u8* sorted, int start,
                                                 int rank)
{
    u8* p;
    u8* p2;
    int remaining;
    int idx;

    p = sorted + start;
    remaining = rank;
    idx = start;
    while (remaining > 0) {
        p2 = p;
    loop:
        idx++;
        p2++;
        p++;
        if (idx >= 0x19) {
            return 0x19;
        }
        if (mn_IsFighterUnlocked(*p2) == 0) {
            goto loop;
        }
        remaining--;
    }
    return sorted[idx];
}

static inline s32 mnDiagram_FindPrevFighter(u8* sorted, s32 cur)
{
    u8* p = sorted + cur;
    s32 found = cur;
loop:
    found--;
    p--;
    if (found < 0) {
        return cur;
    }
    if (mn_IsFighterUnlocked(*p) == 0) {
        goto loop;
    }
    return (u8) found;
}

static inline u8 mnDiagram_FindNextFighter(u8* sorted, s32 cur)
{
    u8* p = sorted + cur;
    s32 found = cur;
loop:
    found++;
    p++;
    if (found >= 0x19) {
        return cur;
    }
    if (mn_IsFighterUnlocked(*p) == 0) {
        goto loop;
    }
    return found;
}

static inline s32 mnDiagram_FindPrevName(s32 cur)
{
    s32 found = cur;
loop:
    found--;
    if (found < 0) {
        return cur;
    }
    if (GetNameText(found & 0xFF) == NULL) {
        goto loop;
    }
    return (u8) found;
}

static inline s32 mnDiagram_FindPrevNameWrap(s32 cur)
{
    s32 found = cur;
loop:
    found--;
    if (found < 0) {
        return (u8) cur;
    }
    if (GetNameText(found & 0xFF) == NULL) {
        goto loop;
    }
    return (u8) found;
}

static inline s32 mnDiagram_FindPrevFighterWrap(u8* sorted, s32 cur)
{
    u8* p = sorted + cur;
    s32 found = cur;
loop:
    found--;
    p--;
    if (found < 0) {
        return (u8) cur;
    }
    if (mn_IsFighterUnlocked(*p) == 0) {
        goto loop;
    }
    return (u8) found;
}

static inline u8 mnDiagram_FindNextName(s32 cur)
{
    s32 found = cur;
loop:
    found++;
    if (found >= 0x78) {
        return cur;
    }
    if (GetNameText(found & 0xFF) == NULL) {
        goto loop;
    }
    return found;
}

static inline int mnDiagram_GetVisibleNameCursorFrom(u8* sorted, int start,
                                                     int rank)
{
    u8* p;
    u8* p2;
    int remaining;
    int idx;

    p = sorted + start;
    remaining = rank;
    idx = start;
    p = p + 0x1C;
    while (remaining > 0) {
        p2 = p;
    loop:
        idx++;
        p2++;
        p++;
        if (idx >= 0x78) {
            return 0x78;
        }
        if (GetNameText(*p2) == NULL) {
            goto loop;
        }
        remaining--;
    }
    p = sorted;
    p += idx;
    return p[0x1C];
}

static inline u8 mnDiagram_GetVisibleFighterCursorFrom(u8* sorted, int start,
                                                       int rank)
{
    u8* p;
    u8* p2;
    int remaining;
    int idx;
    u8 result;

    remaining = rank;
    idx = start;
    p = sorted + start;
    while (remaining >= 0) {
        if (remaining == 0) {
            result = sorted[idx];
            break;
        }
        p2 = p;
    loop:
        idx++;
        p2++;
        p++;
        if (idx >= 0x19) {
            result = 0x19;
            break;
        }
        if (mn_IsFighterUnlocked(*p2) == 0) {
            goto loop;
        }
        remaining--;
    }
    return result;
}

/// @brief Persists the current name/fighter cursor positions and mode into
///        the shared GameRules block on menu exit / page change.
static inline void mnDiagram_SaveCursorToGameRules(Diagram* d)
{
    gmMainLib_8015CC34()->xE = (u8) (d->fighter_cursor_pos >> 8);
    gmMainLib_8015CC34()->xF = (u8) d->fighter_cursor_pos;
    gmMainLib_8015CC34()->unk_x10 = (u8) (d->name_cursor_pos >> 8);
    gmMainLib_8015CC34()->x11 = (u8) d->name_cursor_pos;
    gmMainLib_8015CC34()->xD = d->is_name_mode;
}

/// @brief Per-frame input handler for the VS Records "diagram" grid screen.
///
/// Dispatches the current frame's menu input:
///   - A (0x10):    open the detail popup (mnDiagram_PopupInputProc) for the
///                  highlighted cell, mapping the display cursor
///                  (mn_804A04F0.hovered_selection = row<<8 | col) to the
///                  underlying name/fighter id via the col-th/row-th visible
///                  entry, then enter the detail page (mnDiagram_80241310).
///   - B (0x20):    save cursor state and back out (mn_80229894).
///   - Start/Z (0xC0): save cursor state and advance to page 2
///                  (mnDiagram2_Init) or page 3 (mnDiagram3_8024714C).
///   - L/R (0xC00): toggle between name-tag and fighter axes, clamping the
///                  cursor to the valid entry count.
///   - D-pad (1/2/4/8): move the cursor within the grid, scrolling the data
///                  window by a page when moving past a visible edge.
///
/// The "visible entry" scans skip locked fighters / empty name slots, and are
/// factored into the mnDiagram_GetVisible*From /
/// mnDiagram_Get{Prev,Next}*Index helpers shared with mndiagram2.
void mnDiagram_InputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    u8 row_result;
    s32 i;
    u8* ptr2;
    u8* ptr3;
    short new_var;
    u8* sorted = mnDiagram_804A0750.sorted_fighters;
    Diagram* data = mnDiagram_804D6C10->user_data;
    u32 input = mn_80229624(4);
    s32 count = 0;
    u8* ptr;
    s32 col;
    s32 row;
    s32 row2;
    s32 new_var2;
    s32 row3;
    s32 row4;
    s32 row5;
    s32 row6;
    u8 col_result;
    u8 col_result2;
    u8 row_result2;
    u8 col_result3;
    u8 col_result4;
    u8 row_result3;
    u8 row_result4;
    s32 found;
    s32 cur;
    s32 count2;
    PAD_STACK(64);
    mn_804A04F0.buttons = input;
    count2 = 0;
    if (input & 0x10) {
        cur = 1;
        lbAudioAx_80024030(cur);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        i = 0;
        proc = HSD_GObj_SetupProc(
            gobj, (void (*)(HSD_GObj*)) mnDiagram_PopupInputProc, i);
        proc->flags_3 = HSD_GObj_804D783C;
        if (data->is_name_mode != 0) {
            col = mn_804A04F0.hovered_selection;
            cur = col;
            col_result = mnDiagram_GetVisibleNameFrom(
                sorted, (u8) data->name_cursor_pos, (u8) cur);
            row = mn_804A04F0.hovered_selection >> 8;
            row_result = mnDiagram_GetVisibleNameFrom(
                sorted, data->name_cursor_pos >> 8, row);
            mnDiagram_80241310(col_result, row_result, 1);
            return;
        }
        i = (u8) data->fighter_cursor_pos;
        col = (u8) mn_804A04F0.hovered_selection;
        ptr = sorted + i;
        goto fc_test;
    fc_outer:
        if (col == 0) {
            col_result2 = sorted[i];
        } else {
            ptr2 = ptr;
        fc_inner:
            i++;

            ptr2++;
            ptr++;
            if (i >= 0x19) {
                col_result2 = 0x19;
            } else if (mn_IsFighterUnlocked(*ptr2) != 0) {
                col--;
            fc_test:
                if (col >= 0) {
                    goto fc_outer;
                }

            } else {
                goto fc_inner;
            }
        }

        row2 = mn_804A04F0.hovered_selection >> 8;
        i = data->fighter_cursor_pos >> 8;
        ptr = sorted + i;
        goto fr_test;
    fr_outer:
        if (row2 == 0) {
            row_result2 = sorted[i];
        } else {
            ptr2 = ptr;
        fr_inner:
            i++;

            ptr2++;
            ptr++;
            if (i >= 0x19) {
                row_result2 = 0x19;
            } else if (mn_IsFighterUnlocked(*ptr2) != 0) {
                row2--;
            fr_test:
                if (row2 >= 0) {
                    goto fr_outer;
                }

            } else {
                goto fr_inner;
            }
        }

        mnDiagram_80241310(col_result2, row_result2, 0);
        return;
    }
    if (input & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = count2;
        {
            Diagram* d = mnDiagram_804D6C10->user_data;
            gmMainLib_8015CC34()->xE = (u8) (d->fighter_cursor_pos >> 8);
            gmMainLib_8015CC34()->xF = (u8) d->fighter_cursor_pos;
            gmMainLib_8015CC34()->unk_x10 = (u8) (d->name_cursor_pos >> 8);
            gmMainLib_8015CC34()->x11 = (u8) d->name_cursor_pos;
            gmMainLib_8015CC34()->xD = d->is_name_mode;
            mn_80229894(0x1C, 0, 3);
        }
        return;
    }
    if (input & 0xC0) {
        lbAudioAx_80024030(1);
        {
            Diagram* d = mnDiagram_804D6C10->user_data;
            gmMainLib_8015CC34()->xE = (u8) (d->fighter_cursor_pos >> 8);
            gmMainLib_8015CC34()->xF = (u8) d->fighter_cursor_pos;
            gmMainLib_8015CC34()->unk_x10 = (u8) (d->name_cursor_pos >> 8);
            gmMainLib_8015CC34()->x11 = (u8) d->name_cursor_pos;
            gmMainLib_8015CC34()->xD = d->is_name_mode;
            HSD_GObjPLink_80390228(gobj);
            if (input & 0x40) {
                mnDiagram3_8024714C(0L);
                return;
            }
            mnDiagram2_Init();
        }
        return;
    }
    if (input & 0xC00) {
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        data->is_name_mode = (data->is_name_mode == 0) ? (1) : (count2);
        if (data->is_name_mode != 0) {
            count = GetNameCount();
            if (((s32) ((u8) mn_804A04F0.hovered_selection)) >= count) {
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((u8) (count - 1));
            }
            if ((mn_804A04F0.hovered_selection >> 8) >= count) {
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((count - 1) << 8);
            }
            mnDiagram_UpdateScrollArrowVisibility(mnDiagram_804D6C10, count);
            mnDiagram_80241730(mnDiagram_804D6C10, (u8) data->name_cursor_pos,
                               data->name_cursor_pos >> 8);
            return;
        }
        count = 0;
        ptr3 = sorted;
        for (i = 0; i < 0x19; i++) {
            if (mn_IsFighterUnlocked(i) != 0) {
                count++;
            }
        }

        new_var2 = count;
        if (((s32) ((u8) mn_804A04F0.hovered_selection)) >= new_var2) {
            mn_804A04F0.hovered_selection =
                (mn_804A04F0.hovered_selection & 0xFF00) |
                ((u8) (new_var2 - 1));
        }
        if ((mn_804A04F0.hovered_selection >> 8) >= new_var2) {
            mn_804A04F0.hovered_selection =
                ((u8) mn_804A04F0.hovered_selection) | ((new_var2 - 1) << 8);
        }
        mnDiagram_UpdateScrollArrowVisibility(mnDiagram_804D6C10, new_var2);
        mnDiagram_80241730(mnDiagram_804D6C10, (u8) data->fighter_cursor_pos,
                           data->fighter_cursor_pos >> 8);
        return;
    }
    if (data->is_name_mode != 0) {
        count = GetNameCount();
        if (input & 1) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col > 0) && (count > (col - 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col - 1) & 0xFF);
                return;
            }
            if (count > 0xA) {
                cur = (u8) data->name_cursor_pos;
                found = (u8) mnDiagram_FindPrevName(cur);
                if (cur != found) {
                    lbAudioAx_80024030(2);
                    data->name_cursor_pos =
                        (data->name_cursor_pos & 0xFF00) | found;
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->name_cursor_pos,
                                       data->name_cursor_pos >> 8);
                }
            }
        } else if (input & 2) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col < 9) && (count > (col + 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col + 1) & 0xFF);
                return;
            }
            if (count > 0xA) {
                cur = (u8) data->name_cursor_pos;
                found = mnDiagram_FindNextName(cur);
                if (cur != found) {
                    row2 = 0xA;
                    ptr2 = sorted + cur;
                    ptr2 = ptr2 + 0x1C;
                dn_n_outer:
                    ptr = ptr2;

                dn_n_inner:
                    cur++;

                    ptr++;
                    ptr2++;
                    if (cur >= 0x78) {
                        col_result3 = 0x78;
                    } else if (GetNameText(*ptr) != 0L) {
                        row2--;
                        if (row2 <= 0) {
                            col_result3 = sorted[cur + 0x1C];
                        } else {
                            goto dn_n_outer;
                        }
                    } else {
                        goto dn_n_inner;
                    }
                    if (col_result3 != 0x78) {
                        lbAudioAx_80024030(2);
                        data->name_cursor_pos =
                            (data->name_cursor_pos & 0xFF00) | found;
                        mnDiagram_80241730(mnDiagram_804D6C10,
                                           (u8) data->name_cursor_pos,
                                           data->name_cursor_pos >> 8);
                    }
                }
            }
        } else if (input & 4) {
            row3 = mn_804A04F0.hovered_selection >> 8;
            if ((0 < row3) && (count > (row3 - 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row3 - 1) << 8);
                return;
            }
            if (count > 7) {
                cur = data->name_cursor_pos >> 8;
                found = (u8) mnDiagram_FindPrevNameWrap(cur);
                if (cur != found) {
                    lbAudioAx_80024030(2);
                    data->name_cursor_pos =
                        ((u8) data->name_cursor_pos) | (found << 8);
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->name_cursor_pos,
                                       data->name_cursor_pos >> 8);
                }
            }
        } else if (input & 8) {
            row4 = mn_804A04F0.hovered_selection >> 8;
            if ((row4 < 6) && (count > (row4 + 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row4 + 1) << 8);
                return;
            }
            if (count > 7) {
                cur = data->name_cursor_pos >> 8;
                found = mnDiagram_FindNextName(cur);
                if (cur != found) {
                    row2 = 7;
                    ptr2 = sorted + cur;
                    ptr2 = ptr2 + 0x1C;
                rt_n_outer:
                    ptr = ptr2;

                rt_n_inner:
                    cur++;

                    ptr++;
                    ptr2++;
                    if (cur >= 0x78) {
                        row_result3 = 0x78;
                    } else if (GetNameText(*ptr) != 0L) {
                        row2--;
                        if (row2 <= 0) {
                            row_result3 = sorted[cur + 0x1C];
                        } else {
                            goto rt_n_outer;
                        }
                    } else {
                        goto rt_n_inner;
                    }
                    if (row_result3 != 0x78) {
                        lbAudioAx_80024030(2);
                        data->name_cursor_pos =
                            ((u8) data->name_cursor_pos) | (found << 8);
                        mnDiagram_80241730(mnDiagram_804D6C10,
                                           (u8) data->name_cursor_pos,
                                           data->name_cursor_pos >> 8);
                    }
                }
            }
        }
    } else {
        new_var = 0;
        for (count = count2; count < 0x19; count++) {
            if (mn_IsFighterUnlocked(count) != new_var) {
                count2++;
            }
        }

        if (input & 1) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col > new_var) && (count2 > (col - 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col - 1) & 0xFF);
                return;
            }
            if (count2 > 0xA) {
                cur = (u8) data->fighter_cursor_pos;
                found = (u8) mnDiagram_FindPrevFighter(sorted, cur);
                if (cur != found) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        (data->fighter_cursor_pos & 0xFF00) | found;
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->fighter_cursor_pos,
                                       data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & 2) {
            col = (u8) mn_804A04F0.hovered_selection;
            if ((col < 9) && (count2 > (col + 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    ((col + 1) & 0xFF);
                return;
            }
            if (count2 > 0xA) {
                cur = (u8) data->fighter_cursor_pos;
                ptr = sorted + cur;
                row5 = mnDiagram_FindNextFighter(sorted, cur);
                found = row5;
                row2 = 0xA;
            dn_f_outer:
                if (row2 == new_var) {
                    col_result4 = sorted[cur];
                } else {
                    ptr3 = ptr;
                dn_f_inner:
                    cur++;

                    ptr3++;
                    ptr++;
                    if (cur >= 0x19) {
                        col_result4 = 0x19;
                    } else if (mn_IsFighterUnlocked(*ptr3) != new_var) {
                        row2--;
                        if (row2 >= new_var) {
                            goto dn_f_outer;
                        }
                    } else {
                        goto dn_f_inner;
                    }
                }

                if (col_result4 != 0x19) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        (data->fighter_cursor_pos & 0xFF00) | found;
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->fighter_cursor_pos,
                                       data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & 4) {
            row5 = mn_804A04F0.hovered_selection >> 8;
            if ((row5 > new_var) && (count2 > (row5 - 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row5 - 1) << 8);
                return;
            }
            if (count2 > 7) {
                cur = data->fighter_cursor_pos >> 8;
                found = (u8) mnDiagram_FindPrevFighterWrap(sorted, cur);
                if (cur != found) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        ((u8) data->fighter_cursor_pos) | (found << 8);
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->fighter_cursor_pos,
                                       data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & 8) {
            row6 = mn_804A04F0.hovered_selection >> 8;
            if ((row6 < 6) && (count2 > (row6 + 1))) {
                lbAudioAx_80024030(2);
                mn_804A04F0.hovered_selection =
                    ((u8) mn_804A04F0.hovered_selection) | ((row6 + 1) << 8);
                return;
            }
            if (count2 > 7) {
                cur = data->fighter_cursor_pos >> 8;
                ptr = sorted + cur;
                found = mnDiagram_FindNextFighter(sorted, cur);
                row2 = 7;
            rt_f_outer:
                if (row2 == new_var) {
                    row_result4 = sorted[cur];
                } else {
                    ptr3 = ptr;
                rt_f_inner:
                    cur++;

                    ptr3++;
                    ptr++;
                    if (cur >= 0x19) {
                        row_result4 = 0x19;
                    } else if (mn_IsFighterUnlocked(*ptr3) != new_var) {
                        row2--;
                        if (row2 >= new_var) {
                            goto rt_f_outer;
                        }
                    } else {
                        goto rt_f_inner;
                    }
                }

                if (row_result4 != 0x19) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        ((u8) data->fighter_cursor_pos) | (found << 8);
                    mnDiagram_80241730(mnDiagram_804D6C10,
                                       (u8) data->fighter_cursor_pos,
                                       data->fighter_cursor_pos >> 8);
                }
            }
        }
    }
}

void mnDiagram_PopupCleanup(void* arg0)
{
    mnDiagram_CleanupData* data = arg0;

    if (data->text[0] != NULL) {
        HSD_SisLib_803A5CC4(data->text[0]);
    }
    if (data->text[1] != NULL) {
        HSD_SisLib_803A5CC4(data->text[1]);
    }
    if (data->text[2] != NULL) {
        HSD_SisLib_803A5CC4(data->text[2]);
    }
    if (data->text[3] != NULL) {
        HSD_SisLib_803A5CC4(data->text[3]);
    }
    if (data->text[4] != NULL) {
        HSD_SisLib_803A5CC4(data->text[4]);
    }
    HSD_Free(arg0);
}

typedef struct mnDiagram_PopupData {
    /* 0x00 */ HSD_JObj* jobjs[14];
    /* 0x38 */ HSD_Text* text[5];
} mnDiagram_PopupData;
STATIC_ASSERT(sizeof(mnDiagram_PopupData) == 0x4C);

typedef struct mnDiagram_MainOverlay {
    /* 0x00 */ HSD_JObj* jobjs[14];
    /* 0x38 */ HSD_Text* text[6];
} mnDiagram_MainOverlay;

inline Vec3* mnDiagram_PopupAnimProc_Inline(mnDiagram_AnimTable* arg0,
                                            int arg1)
{
    return &arg0->points[arg1];
}

void mnDiagram_PopupAnimProc(void* arg0)
{
    mnDiagram_PopupData* data = ((HSD_GObj*) arg0)->user_data;
    HSD_Text* text;
    mnDiagram_AnimTable* tbl = (mnDiagram_AnimTable*) &mnDiagram_803EE728;
    Vec3 pos;
    float new_var;
    f32 anim_frame;
    PAD_STACK(0x18);

    HSD_JObjAnimAll(data->jobjs[5]);

    text = data->text[0];
    lb_8000B1CC(data->jobjs[8], mnDiagram_PopupAnimProc_Inline(tbl, 0), &pos);
    {
        f32 y = pos.y;
        f32 z = pos.z;
        text->pos_x = pos.x;
        text->pos_y = (new_var = -y);
        text->pos_z = z;
    }
    text->default_alignment = 0;

    HSD_JObjAnim(data->jobjs[9]);
    if (data->text[1] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[11], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = pos.y;
        z = pos.z;
        t = data->text[1];
        t->pos_x = pos.x;
        t->pos_y = (new_var = -y);
        t->pos_z = z;
        text->default_alignment = 1;
    }
    if (data->text[2] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[10], mnDiagram_PopupAnimProc_Inline(tbl, 2),
                    &pos);
        y = pos.y;
        z = pos.z;
        t = data->text[2];
        t->pos_x = pos.x;
        t->pos_y = (new_var = -y);
        t->pos_z = z;
        text->default_alignment = 1;
    }

    HSD_JObjAnim(data->jobjs[1]);
    {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[3], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = pos.y;
        z = pos.z;
        t = data->text[3];
        t->pos_x = pos.x;
        t->pos_y = (new_var = -y);
        t->pos_z = z;
    }
    text->default_alignment = 1;

    if (data->text[4] != NULL) {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[2], mnDiagram_PopupAnimProc_Inline(tbl, 2),
                    &pos);
        y = pos.y;
        z = pos.z;
        t = data->text[4];
        t->pos_x = pos.x;
        t->pos_y = (new_var = -y);
        t->pos_z = z;
        text->default_alignment = 1;
    }

    anim_frame = mn_8022EFD8(data->jobjs[12], &tbl->cursor_anim);
    {
        HSD_Text* t;
        f32 y;
        f32 z;
        lb_8000B1CC(data->jobjs[13], mnDiagram_PopupAnimProc_Inline(tbl, 1),
                    &pos);
        y = pos.y;
        z = pos.z;
        t = data->text[3];
        t->pos_x = pos.x;
        t->pos_y = (new_var = -y);
        t->pos_z = z;
    }
    text->default_alignment = 1;

    if (anim_frame == tbl->cursor_anim.end_frame) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    }
}

inline void mnDiagram_FormatPopupNumber(char* buf, u32 val)
{
    int digit_count = mn_GetDigitCount(val);
    int i;

    for (i = 0; i < digit_count; i++) {
        buf[digit_count - 1 - i] = mn_GetDigitAt(val, i) + '0';
    }
    buf[digit_count] = mnDiagram_804D4FA4;
}

void mnDiagram_80240D94(void* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    mnDiagram_PopupData* data = ((HSD_GObj*) arg0)->user_data;
    mnDiagram_AnimTable* tbl = (mnDiagram_AnimTable*) &mnDiagram_803EE728;
    Point3d pos;
    float new_var;
    char buf[8];
    u32 kos;
    u32 sd_count;

    HSD_Text* text = HSD_SisLib_803A6754(0, 1);
    PAD_STACK(24);
    data->text[0] = text;
    lb_8000B1CC(data->jobjs[8], &tbl->points[0], &pos);
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    {
        f32 y = pos.y;
        f32 z = pos.z;
        text->pos_x = pos.x;
        text->pos_y = (new_var = -y);
        text->pos_z = z;
    }
    text->default_alignment = 0;
    *(s32*) &text->text_color = mnDiagram_804D4FA0;

    if (arg3 != 0) {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) arg1));
    } else {
        gm_80160C90(text, gm_8016400C((u8) arg1), 0);
    }

    if ((arg3 != 0) && (arg1 != arg2)) {
        {
            HSD_Text* label_text;

            label_text = HSD_SisLib_803A6754(0, 1);
            data->text[2] = label_text;
            lb_8000B1CC(data->jobjs[10], &tbl->points[2], &pos);
            label_text->font_size.x = 0.035f;
            label_text->font_size.y = 0.05f;
            {
                f32 y = pos.y;
                f32 z = pos.z;
                label_text->pos_x = pos.x;
                label_text->pos_y = (new_var = -y);
                label_text->pos_z = z;
            }
            label_text->default_alignment = 1;
            HSD_SisLib_803A6B98(label_text, 0.0f, 0.0f,
                                GetNameText(arg2 & 0xFF));
        }

        {
            HSD_Text* label_text;

            label_text = HSD_SisLib_803A6754(0, 1);
            data->text[4] = label_text;
            lb_8000B1CC(data->jobjs[2], &tbl->points[2], &pos);
            label_text->font_size.x = 0.035f;
            label_text->font_size.y = 0.05f;
            {
                f32 y = pos.y;
                f32 z = pos.z;
                label_text->pos_x = pos.x;
                label_text->pos_y = (new_var = -y);
                label_text->pos_z = z;
            }
            label_text->default_alignment = 1;
            HSD_SisLib_803A6B98(label_text, 0.0f, 0.0f,
                                GetNameText((u8) arg2));
        }
    }

    if ((arg3 == 0) || (arg1 != arg2)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[1] = text;
        lb_8000B1CC(data->jobjs[11], &tbl->points[1], &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        {
            f32 y = pos.y;
            f32 z = pos.z;
            text->pos_x = pos.x;
            text->pos_y = (new_var = -y);
            text->pos_z = z;
        }

        if (arg3 != 0) {
            kos = GetPersistentNameData((u8) arg1)->vs_kos[(u8) arg2];
            mnDiagram_FormatPopupNumber(buf, kos);
        } else {
            kos = GetPersistentFighterData((u8) arg1)->fighter_kos[(u8) arg2];
            mnDiagram_FormatPopupNumber(buf, kos);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }

    if (arg1 == arg2) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[3] = text;
        lb_8000B1CC(data->jobjs[13], &tbl->points[1], &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        {
            f32 y = pos.y;
            f32 z = pos.z;
            text->pos_x = pos.x;
            text->pos_y = (new_var = -y);
            text->pos_z = z;
        }
        if (arg3 != 0) {
            sd_count = GetPersistentNameData((u8) arg1)->sd_count;
            mnDiagram_FormatPopupNumber(buf, sd_count);
        } else {
            sd_count = GetPersistentFighterData((u8) arg1)->sd_count;
            mnDiagram_FormatPopupNumber(buf, sd_count);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    } else {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[3] = text;
        {
            Point3d* point = &tbl->points[1];
            lb_8000B1CC(data->jobjs[3], point, &pos);
        }
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        {
            f32 y = pos.y;
            f32 z = pos.z;
            text->pos_x = pos.x;
            text->pos_y = (new_var = -y);
            text->pos_z = z;
        }
        if (arg3 != 0) {
            u32 count = GetPersistentNameData((u8) arg2)->vs_kos[(u8) arg1];
            mnDiagram_FormatPopupNumber(buf, count);
        } else {
            u32 count =
                GetPersistentFighterData((u8) arg2)->fighter_kos[(u8) arg1];
            mnDiagram_FormatPopupNumber(buf, count);
        }
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }
}

void mnDiagram_80241310(s32 arg0, s32 arg1, s32 arg2)
{
    int i;
    mnDiagram_AnimTable* tbl;
    void** joint_data;
    Diagram* data;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    mnDiagram_PopupData* user_data;

    tbl = (mnDiagram_AnimTable*) &mnDiagram_803EE728;
    joint_data = mnDiagram_804A07E4;
    data = GET_DIAGRAM(mnDiagram_804D6C10);

    gobj = GObj_Create(6, 7, 0x80);
    data->popup_gobj = gobj;
    jobj = HSD_JObjLoadJoint(joint_data[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
    HSD_JObjReqAnimAll(jobj, mnDiagram_804DBF84);
    HSD_JObjAnimAll(jobj);

    user_data = HSD_MemAlloc(sizeof(mnDiagram_PopupData));
    if (user_data == NULL) {
        OSReport(tbl->x70);
        __assert(tbl->x88, 0x5F8, tbl->x94);
    }

    GObj_InitUserData(gobj, 0, mnDiagram_PopupCleanup, user_data);
    user_data->text[4] = NULL;
    user_data->text[3] = NULL;
    user_data->text[2] = NULL;
    user_data->text[1] = NULL;
    user_data->text[0] = NULL;

    for (i = 0; i < 14; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }

    HSD_GObj_SetupProc(gobj, (void (*)(HSD_GObj*)) mnDiagram_PopupAnimProc, 0);
    mnDiagram_80240D94(gobj, arg0, arg1, arg2);

    if (arg2 != 0) {
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
        HSD_JObj* icon = mnDiagram_80242B38(arg0, 1);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        mn_8022F3D8(icon, 0xA, TOBJ_MASK);
        HSD_JObjAddChild(user_data->jobjs[7], icon);

        icon = mnDiagram_80242B38(arg1, 1);
        HSD_JObjSetTranslateX(icon, mnDiagram_804DBF94);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        HSD_JObjAddChild(user_data->jobjs[10], icon);

        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[1], JOBJ_HIDDEN);
        } else {
            icon = mnDiagram_80242B38(arg1, 1);
            HSD_JObjSetTranslateX(icon, mnDiagram_804DBF94);
            mn_8022F3D8(icon, 1, TOBJ_MASK);
            HSD_JObjAddChild(user_data->jobjs[2], icon);
        }
        if (arg0 != arg1) {
            HSD_JObjSetFlagsAll(user_data->jobjs[12], JOBJ_HIDDEN);
        }
    }
}

static inline void* mnDiagram_GetUserData(HSD_GObj* gobj)
{
    return gobj->user_data;
}

static inline HSD_JObj* mnDiagram_GetJObjChild(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->child;
}

void mnDiagram_80241668(void* arg0)
{
    mnDiagram_MainOverlay* data = mnDiagram_GetUserData(arg0);
    HSD_JObj* child;

    child = mnDiagram_GetJObjChild(data->jobjs[9]);
    if (child) {
        HSD_JObjRemoveAll(child);
    }

    child = mnDiagram_GetJObjChild(data->jobjs[11]);
    if (child) {
        HSD_JObjRemoveAll(child);
    }

    child = mnDiagram_GetJObjChild(data->jobjs[13]);
    if (child) {
        HSD_JObjRemoveAll(child);
    }

    if (data->text[4] != NULL) {
        HSD_SisLib_803A5CC4(data->text[4]);
        data->text[4] = NULL;
    }
    if (data->text[5] != NULL) {
        HSD_SisLib_803A5CC4(data->text[5]);
        data->text[5] = NULL;
    }
}

void mnDiagram_80241730(HSD_GObj* arg0, int arg1, int arg2)
{
    Diagram* data = GET_DIAGRAM(arg0);
    mnDiagram_80241668(arg0);
    mnDiagram_8024227C(arg0, arg1, arg2, (u8) (data->is_name_mode == 1));
    if (data->is_name_mode == 0) {
        mnDiagram_80242C0C(arg0, arg1, arg2);
    } else {
        mnDiagram_802427B4(arg0, arg1, arg2);
    }
}

#pragma push
#pragma dont_reuse_strings off
/// @brief Updates scroll arrow visibility based on cursor position and
///        available entries beyond the visible range.
/// @param[in] gobj The diagram GObj containing arrow JObjs in user_data.
/// @details Checks 4 arrows: right (10 more cols?), left (cursor > 0?),
///          up (cursor row > 0?), down (7 more rows?). Hides arrows when
///          there's nothing to scroll to, shows them when there is.
void mnDiagram_802417D0(HSD_GObj* gobj)
{
    u8 result2;
    Diagram* data = gobj->user_data;
    mnDiagram_AnimTable* tbl = (mnDiagram_AnimTable*) &mnDiagram_803EE728;
    HSD_JObj* jobj;
    u8* sorted = mnDiagram_804A0750.sorted_fighters;
    s32 i;
    u8* ptr;
    s32 count;
    s32 result;
    u8* ptr2;
    HSD_JObj* jobj2;
    PAD_STACK(8);

    // Right arrow (jobjs[3])
    jobj = data->jobjs[3];
    mn_8022ED6C(jobj, &tbl->arrow_anim);
    result = data->is_name_mode;
    if (result != 0) {
        // Name mode - check if 10 more names exist
        count = 10;
        i = data->name_cursor_pos;
        i = (u8) i;
        ptr = sorted + i;
        ptr = ptr + 0x1C;
        while (count > 0) {
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= 0x78) {
                    result = 0x78;
                    goto right_done;
                }
            } while (GetNameText(*ptr2) == NULL);
            count--;
        }
        result = sorted[i + 0x1C];
    right_done:;
        if ((u8) result != 0x78) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        // Fighter mode - check if 10 more fighters exist
        count = 10;
        i = (u8) data->fighter_cursor_pos;
        ptr = sorted + i;
        do {
            if (count == 0) {
                result = sorted[i];
                break;
            }
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= 0x19) {
                    result = 0x19;
                    goto fc_right_done;
                }
            } while (mn_IsFighterUnlocked(*ptr2) == 0);
            count--;
        } while (count >= 0);
    fc_right_done:
        if ((u8) result != 0x19) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }

    // Left arrow (jobjs[4])
    jobj2 = data->jobjs[4];
    mn_8022ED6C(jobj2, &tbl->arrow_anim);
    if (data->is_name_mode != 0) {
        result = (u8) data->name_cursor_pos;
    } else {
        result = (u8) data->fighter_cursor_pos;
    }
    if (result != 0) {
        HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(jobj2, JOBJ_HIDDEN);
    }

    // Up arrow (jobjs[5])
    jobj2 = data->jobjs[5];
    mn_8022ED6C(jobj2, &tbl->arrow_anim);
    if (data->is_name_mode != 0) {
        i = data->name_cursor_pos >> 8;
    } else {
        i = data->fighter_cursor_pos >> 8;
    }
    if (i != 0) {
        HSD_JObjClearFlagsAll(jobj2, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(jobj2, JOBJ_HIDDEN);
    }

    // Down arrow (jobjs[6])
    jobj = data->jobjs[6];
    mn_8022ED6C(jobj, &tbl->arrow_anim);
    if (data->is_name_mode != 0) {
        // Name mode - check if 7 more rows exist
        count = 7;
        i = data->name_cursor_pos >> 8;
        ptr = sorted + i;
        ptr = ptr + 0x1C;
        while (count > 0) {
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= 0x78) {
                    result2 = 0x78;
                    goto dn_name_done;
                }
            } while (GetNameText(*ptr2) == NULL);
            count--;
        }
        result2 = sorted[i + 0x1C];
    dn_name_done:
        if (result2 != 0x78) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        // Fighter mode - check if 7 more rows exist
        count = 7;
        i = data->fighter_cursor_pos >> 8;
        ptr = sorted + i;
        do {
            if (count == 0) {
                result2 = sorted[i];
                break;
            }
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= 0x19) {
                    result2 = 0x19;
                    goto dn_fc_done;
                }
            } while (mn_IsFighterUnlocked(*ptr2) == 0);
            count--;
        } while (count >= 0);
    dn_fc_done:
        if (result2 != 0x19) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
}
#pragma pop

void mnDiagram_ExitAnimProc(HSD_GObj* gobj)
{
    mnDiagram_AnimData* data;
    HSD_JObj* jobj;
    f32* table;

    data = gobj->user_data;
    mnDiagram_802417D0(gobj);
    jobj = data->jobj;
    table = mnDiagram_803EE774;
    if (mn_8022ED6C(jobj, (AnimLoopSettings*) table) >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}

/// @brief Updates scroll arrow visibility based on entry count.
/// @details Hides vertical arrows if count <= 7 (fits in visible rows).
///          Hides horizontal arrows if count <= 10 (fits in visible columns).
/// @param gobj The diagram GObj containing arrow JObjs in user_data.
/// @param count Number of entries (fighters or names) to display.
void mnDiagram_UpdateScrollArrowVisibility(void* gobj, int count)
{
    void* data = ((HSD_GObj*) gobj)->user_data;
    PAD_STACK(8);
    if (count <= 7) {
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[7], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[8], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[7], JOBJ_HIDDEN);
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[8], JOBJ_HIDDEN);
    }
    if (count <= 10) {
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[6], JOBJ_HIDDEN);
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[5], JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[6], JOBJ_HIDDEN);
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[5], JOBJ_HIDDEN);
    }
}

void mnDiagram_OnFrame(HSD_GObj* gobj)
{
    Diagram* data = GET_DIAGRAM(gobj);
    HSD_GObjProc* proc;
    Diagram* data2;
    int count;

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        if (mn_804A04F0.cur_menu == 0x1E) {
            mnDiagram_80241668(gobj);
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, mnDiagram_ExitAnimProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_JObjSetFlagsAll(data->jobjs[2], JOBJ_HIDDEN);
        mnDiagram_80241668(gobj);
        return;
    }

    if (data->anim_state == 1) {
        HSD_JObj* jobj;
        f32 frame;
        f32 end_frame;

        frame = mn_8022ED6C(data->jobjs[1], &mnDiagram_803EE768);
        end_frame = mnDiagram_803EE768.end_frame;
        jobj = data->jobjs[2];
        if (frame >= end_frame) {
            HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            data->anim_state = 0;
            mnDiagram_802433AC();
            if (data->is_name_mode != 0) {
                u16 indices = data->name_cursor_pos;
                s32 row_idx;
                u8 col_idx;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_80241668(gobj);
                mnDiagram_8024227C(gobj, col_idx, row_idx,
                                   (u8) (data2->is_name_mode == 1));
                if (data2->is_name_mode == 0) {
                    mnDiagram_80242C0C(gobj, col_idx, row_idx);
                } else {
                    mnDiagram_802427B4(gobj, col_idx, row_idx);
                }
            } else {
                u16 indices = data->fighter_cursor_pos;
                s32 row_idx;
                u8 col_idx;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_80241668(gobj);
                mnDiagram_8024227C(gobj, col_idx, indices >> 8,
                                   (u8) (data2->is_name_mode == 1));
                if (data2->is_name_mode == 0) {
                    mnDiagram_80242C0C(gobj, col_idx, row_idx);
                } else {
                    mnDiagram_802427B4(gobj, col_idx, row_idx);
                }
            }
            if (data->is_name_mode != 0) {
                count = GetNameCount();
            } else {
                count = mnDiagram_CountUnlockedFighters();
            }
            data2 = gobj->user_data;
            if (count <= 7) {
                HSD_JObjSetFlagsAll(((HSD_JObj**) data2)[7], JOBJ_HIDDEN);
                HSD_JObjSetFlagsAll(((HSD_JObj**) data2)[8], JOBJ_HIDDEN);
            } else {
                HSD_JObjClearFlagsAll(((HSD_JObj**) data2)[7], JOBJ_HIDDEN);
                HSD_JObjClearFlagsAll(((HSD_JObj**) data2)[8], JOBJ_HIDDEN);
            }
            if (count <= 10) {
                HSD_JObjSetFlagsAll(((HSD_JObj**) data2)[6], JOBJ_HIDDEN);
                HSD_JObjSetFlagsAll(((HSD_JObj**) data2)[5], JOBJ_HIDDEN);
            } else {
                HSD_JObjClearFlagsAll(((HSD_JObj**) data2)[6], JOBJ_HIDDEN);
                HSD_JObjClearFlagsAll(((HSD_JObj**) data2)[5], JOBJ_HIDDEN);
            }
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }
    mnDiagram_802417D0(gobj);
}

void mnDiagram_80241E78(void* arg0, u8 arg1, u8 arg2, int arg3)
{
    Diagram* data_alias;
    f32 row_offset_adj;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    Diagram* data;
    void** joint_data;
    s32 digit_count;
    s32 digit;
    s32 i;
    f32 x_spacing;
    f32 y_spacing;
    f32 base;
    f32 row_offset;
    f32 col_offset;
    u8 col = arg1;
    u8 row = arg2;
    f32 y_offset;

    data = ((HSD_GObj*) arg0)->user_data;
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
    y_offset = HSD_JObjGetTranslationY(jobj2);
    y_offset -= base;

    digit_count = mn_GetDigitCount(arg3);
    col_offset = y_spacing * (f32) col;
    row_offset = y_offset * (f32) row;
    row_offset_adj = row_offset - 0.4f;

    joint_data = mnDiagram_804A07F4;
    for (i = 0; i < digit_count; i++) {
        digit = mn_GetDigitAt(arg3, i);
        jobj = HSD_JObjLoadJoint(joint_data[0]);
        HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
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

void mnDiagram_8024227C(void* arg0, s32 arg1, s32 arg2, u8 arg3)
{
    s32 var_r22_2;
    s32 arg1_r = arg1;
    s32 arg2_r = arg2;
    u8 is_name = arg3;
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
    s32 cap = 0xF423F;
    s32 var_r16_6;
    s32 var_r17_7;
    s32 var_r17_8;
    s32 var_r18_3;
    s32 var_r19_2;
    s32 var_r22;
    s32 var_r22_3;
    s32 var_r30;
    s32 var_r3;
    s32 var_r17_4;
    s32 var_r19_5;
    unsigned long long var_r0_2;
    s32 var_r17_6;
    s32 var_r23;
    u8 var_r24;
    u8* sorted;

    var_r30 = 0;
    do {
        if (var_r30 == 0xA) {
            var_r22 = 0;
            do {
                sorted = (u8*) assets;
                if (is_name != 0) {
                    var_r3 = GetNameCount();
                    if (var_r3 > var_r22) {
                        var_r19_2 = mnDiagram_SumNameFalls(
                            mnDiagram_GetVisibleNameCursorFrom(sorted, arg2_r,
                                                               var_r22));
                        mnDiagram_80241E78(arg0, (u8) var_r22, (u8) var_r30,
                                           var_r19_2);
                    }
                } else {
                    var_r18_3 = mnDiagram_CountUnlockedFightersInline();
                    if (var_r18_3 > var_r22) {
                        var_r19_5 = mnDiagram_SumFighterFalls(
                            mnDiagram_GetVisibleFighterCursorFrom(
                                sorted, arg2_r, var_r22));
                        mnDiagram_80241E78(arg0, (u8) var_r22, (u8) var_r30,
                                           var_r19_5);
                    }
                }
                var_r22 += 1;
            } while (var_r22 < 7);
        } else if (is_name != 0) {
            var_r3 = GetNameCount();
            if (var_r3 > var_r30) {
                var_r22_2 = 0;
                do {
                    sorted = (u8*) assets;
                    if ((var_r22_2 == 7) ||
                        (var_r3 = GetNameCount(), (var_r3 > var_r22_2)))
                    {
                        var_r0_2 = (u8) mnDiagram_GetVisibleNameCursorFrom(
                            sorted, arg1_r, var_r30);
                        if (var_r22_2 == 7) {
                            var_r17_4 = mnDiagram_GetNameTotalKOs(var_r0_2);
                            mnDiagram_80241E78(arg0, (u8) var_r22_2,
                                               (u8) var_r30, var_r17_4);
                        } else {
                            var_r17_6 = mnDiagram_GetVisibleNameCursorFrom(
                                sorted, arg2_r, var_r22_2);
                            mnDiagram_80241E78(
                                arg0, (u8) var_r22_2, (u8) var_r30,
                                GetPersistentNameData((u8) var_r0_2)
                                    ->vs_kos[(u8) var_r17_6]);
                        }
                    }
                    var_r22_2 += 1;
                } while (var_r22_2 <= 7);
            }
        } else {
            var_r17_7 = mnDiagram_CountUnlockedFightersInline();
            if (var_r17_7 > var_r30) {
                var_r22_3 = 0;
                do {
                    sorted = (u8*) assets;
                    if (var_r22_3 != 7) {
                        var_r17_8 = mnDiagram_CountUnlockedFightersInline();
                        if (var_r17_8 > var_r22_3) {
                            goto block_83;
                        }
                    } else {
                    block_83:
                        var_r23 = mnDiagram_GetVisibleFighterCursorFrom(
                            sorted, arg1_r, var_r30);
                        if (var_r22_3 == 7) {
                            mnDiagram_80241E78(
                                arg0, (u8) var_r22_3, (u8) var_r30,
                                mnDiagram_SumFighterKOsClamped(var_r23));
                        } else {
                            var_r24 = mnDiagram_GetVisibleFighterCursorFrom(
                                sorted, arg2_r, var_r22_3);
                            mnDiagram_80241E78(
                                arg0, (u8) var_r22_3, (u8) var_r30,
                                GetPersistentFighterData((u8) var_r23)
                                    ->fighter_kos[var_r24]);
                        }
                    }
                    var_r22_3 += 1;
                } while (var_r22_3 <= 7);
            }
        }
        var_r30 += 1;
    } while (var_r30 <= 0xA);
}

void mnDiagram_802427B4(void* arg0, s32 arg1, s32 arg2)
{
    int i;
    Diagram* data = ((HSD_GObj*) arg0)->user_data;
    u8* sorted = mnDiagram_804A0750.sorted_fighters;
    HSD_Text* text;
    HSD_Text* row_text;
    Vec3 pos;
    f32 x_spacing;
    f32 y_spacing;

    // Column headers
    text = HSD_SisLib_803A6754(0, 1);
    data->col_header_text = text;
    text->font_size.x = 0.02f;
    text->font_size.y = 0.03f;
    {
        HSD_JObj* j = data->jobjs[7];
        pos.z = HSD_JObjGetTranslationZ(j);
        pos.y = -0.5f - HSD_JObjGetTranslationY(j);
        pos.x = -1.3f + HSD_JObjGetTranslationX(j);
        text->pos_x = pos.x;
        text->pos_y = pos.y;
        text->pos_z = pos.z;
    }

    for (i = 0; i < 7; i++) {
        if (GetNameCount() > i) {
            u8 name_byte;
            s32 name_id;
            name_byte = mnDiagram_GetVisibleNameFrom(sorted, arg2, i);
            name_id = name_byte;
            x_spacing = HSD_JObjGetTranslationX(data->jobjs[8]) -
                        HSD_JObjGetTranslationX(data->jobjs[7]);
            HSD_SisLib_803A6B98(text, (x_spacing * i) / 0.02f, 0.0f,
                                GetNameText(name_id));
        }
    }

    // Row headers
    row_text = HSD_SisLib_803A6754(0, 1);
    data->row_header_text = row_text;
    row_text->font_size.x = 0.02f;
    row_text->font_size.y = 0.03f;
    {
        HSD_JObj* j = data->jobjs[9];
        pos.z = HSD_JObjGetTranslationZ(j);
        pos.y = -0.5f - HSD_JObjGetTranslationY(j);
        pos.x = -1.3f + HSD_JObjGetTranslationX(j);
        row_text->pos_x = pos.x;
        row_text->pos_y = pos.y;
        row_text->pos_z = pos.z;
    }

    for (i = 0; i < 0xA; i++) {
        if (GetNameCount() > i) {
            u8 name_byte;
            s32 name_id;
            name_byte = mnDiagram_GetVisibleNameFrom(sorted, arg1, i);
            name_id = name_byte;
            y_spacing = HSD_JObjGetTranslationY(data->jobjs[10]) -
                        HSD_JObjGetTranslationY(data->jobjs[9]);
            HSD_SisLib_803A6B98(row_text, 0.0f, -((y_spacing * i) / 0.03f),
                                GetNameText(name_id));
        }
    }
}

HSD_JObj* mnDiagram_80242B38(int idx, int arg1)
{
    HSD_JObj* sp10;
    void** joint_data = mnDiagram_804A0804;
    HSD_JObj* temp_r3;
    f32 var_f1;

    temp_r3 = HSD_JObjLoadJoint(joint_data[0]);
    HSD_JObjAddAnimAll(temp_r3, joint_data[1], joint_data[2], joint_data[3]);
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

void mnDiagram_80242C0C(void* arg0, int arg1, int arg2)
{
    int count;
    u8* pr;
    u8* p2;
    int remr;
    HSD_JObj* jobj;
    Diagram* data = GET_DIAGRAM(arg0);
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
    void** joint_data;
    u8 stack_obj[8];
    HSD_JObj* sp_jobj;
    u8 stack_obj2[4];
    HSD_JObj* sp_jobj2;
    u8 stack_obj3[20];
    int k;
    int idx;
    int remaining;
    u8* p;
    u8* sorted;
    int fighter_id;
    u8* pr2;
    f32 x_spacing;
    f32 y_spacing;
    int fighter_idr;
    int i;

    (void) &stack_obj;
    (void) &stack_obj2;
    (void) &stack_obj3;

    // Column headers (fighter icons)
    joint_data = assets->FaceB;
    for (i = 0; i < 7; i++) {
        sorted = mnDiagram_804A0750.sorted_fighters;
        for (count = k = 0; k < 0x19; k++) {
            if (mn_IsFighterUnlocked(k) != 0) {
                count++;
            }
        }
        if (count > i) {
            remaining = i;
            idx = arg2;
            p = sorted + idx;
            while (remaining >= 0) {
                if (remaining == 0) {
                    fighter_id = sorted[idx];
                    goto col_found;
                }
                p2 = p;
            col_inner:
                idx++;
                p2++;
                p++;
                if (idx >= 0x19) {
                    fighter_id = 0x19;
                    goto col_found;
                }
                if (mn_IsFighterUnlocked(*p2) == 0) {
                    goto col_inner;
                }
                remaining--;
            }
        col_found:
            jobj = HSD_JObjLoadJoint(joint_data[0]);
            HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2],
                               joint_data[3]);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            lb_80011E24(jobj, &sp_jobj, 2, -1);
            HSD_JObjReqAnimAll(sp_jobj, (f32) (fighter_id & 0xFF));
            HSD_JObjAnimAll(sp_jobj);
            x_spacing = HSD_JObjGetTranslationX(data->jobjs[8]) -
                        HSD_JObjGetTranslationX(data->jobjs[7]);
            HSD_JObjSetTranslateX(jobj, x_spacing * i);
            HSD_JObjAddChild(data->jobjs[7], jobj);
        }
    }

    // Row headers (fighter icons)
    joint_data = assets->FaceB;
    for (i = 0; i < 0xA; i++) {
        sorted = mnDiagram_804A0750.sorted_fighters;
        count = 0;
        for (k = 0; k < 0x19; k++) {
            if (mn_IsFighterUnlocked(k) != 0) {
                count++;
            }
        }
        if (count > i) {
            remr = i;
            idx = arg1;
            pr = sorted + idx;
            while (remr >= 0) {
                if (remr == 0) {
                    fighter_idr = sorted[idx];
                    goto row_found;
                }
                pr2 = pr;
            row_inner:
                idx++;
                pr2++;
                pr++;
                if (idx >= 0x19) {
                    fighter_idr = 0x19;
                    goto row_found;
                }
                if (mn_IsFighterUnlocked(*pr2) == 0) {
                    goto row_inner;
                }
                remr--;
            }
        row_found:
            jobj = HSD_JObjLoadJoint(joint_data[0]);
            HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2],
                               joint_data[3]);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            lb_80011E24(jobj, &sp_jobj2, 2, -1);
            HSD_JObjReqAnimAll(sp_jobj2, (f32) (fighter_idr & 0xFF));
            HSD_JObjAnimAll(sp_jobj2);
            y_spacing = HSD_JObjGetTranslationY(data->jobjs[10]) -
                        HSD_JObjGetTranslationY(data->jobjs[9]);
            HSD_JObjSetTranslateY(jobj, y_spacing * i);
            HSD_JObjAddChild(data->jobjs[9], jobj);
        }
    }
}

static inline Diagram* mnDiagram_GetCurrentDiagramData(void)
{
    return mnDiagram_804D6C10->user_data;
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
    PAD_STACK(8);

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    data = mnDiagram_GetCurrentDiagramData();
    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 3, -1);

    selection = (u16*) &mn_804A04F0;
    col = *++selection >> 8;
    x_spacing = HSD_JObjGetTranslationX(data->jobjs[8]) -
                HSD_JObjGetTranslationX(data->jobjs[7]);
    HSD_JObjSetTranslateX(sp_jobj, x_spacing * (col - 3));

    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 4, -1);
    row = *selection & 0xFF;
    y_spacing = HSD_JObjGetTranslationY(data->jobjs[10]) -
                HSD_JObjGetTranslationY(data->jobjs[9]);
    HSD_JObjSetTranslateY(sp_jobj, y_spacing * (row - 4.5) - 0.1F);

    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 2, -1);
    HSD_JObjSetTranslateX(sp_jobj, x_spacing * (col - 3));
    HSD_JObjSetTranslateY(sp_jobj, y_spacing * (row - 4.5) - 0.1F);
}

void mnDiagram_802433AC(void)
{
    void** joint_data;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    PAD_STACK(40);

    joint_data = mnDiagram_804A0814;
    gobj = GObj_Create(6, 7, 0x80);
    jobj = HSD_JObjLoadJoint(*joint_data);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_GObj_SetupProc(gobj, mnDiagram_CursorProc, 0);
}

void mnDiagram_80243434(u8 arg0)
{
    int col_idx;
    s32 row_idx;
    Diagram* d;
    int col_idx2;
    s32 row_idx2;
    Diagram* d2;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* anim_jobj;
    Diagram* user_data;
    Diagram* data2;
    int count;
    void** joint_data;
    mnDiagram_AnimTable* tbl = GET_DIAGRAM_ANIM_TABLE();
    int i;
    u16 indices;
    u8 stack_obj[8];

    (void) &stack_obj;
    joint_data = (void**) &mnDiagram_804A0824;
    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram_804D6C10 = gobj;
    jobj = HSD_JObjLoadJoint(joint_data[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
    HSD_JObjReqAnimAll(jobj, mnDiagram_804DBF84);

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
        user_data->is_name_mode = gmMainLib_8015CC34()->xD;
    } else {
        gmMainLib_8015CC34()->xD = 0;
        user_data->is_name_mode = gmMainLib_8015CC34()->xD;
    }

    GObj_InitUserData(gobj, 0, HSD_Free, user_data);

    for (i = 0; i < 13; i++) {
        lb_80011E24(jobj, &user_data->jobjs[i], i, -1);
    }

    HSD_GObj_SetupProc(gobj, (void (*)(HSD_GObj*)) mnDiagram_OnFrame, 0);

    if (arg0 == 0) {
        anim_jobj = user_data->jobjs[1];
        HSD_JObjReqAnimAll(anim_jobj, tbl->x40.end_frame);
        HSD_JObjAnimAll(anim_jobj);

        mnDiagram_802433AC();

        if (user_data->is_name_mode != 0) {
            count = GetNameCount();
        } else {
            count = mnDiagram_CountUnlockedFighters();
        }

        data2 = GET_DIAGRAM(gobj);
        if (count <= 7) {
            HSD_JObjSetFlagsAll(data2->jobjs[5], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(data2->jobjs[6], JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlagsAll(data2->jobjs[5], JOBJ_HIDDEN);
            HSD_JObjClearFlagsAll(data2->jobjs[6], JOBJ_HIDDEN);
        }

        if (count <= 0xA) {
            HSD_JObjSetFlagsAll(data2->jobjs[4], JOBJ_HIDDEN);
            HSD_JObjSetFlagsAll(data2->jobjs[3], JOBJ_HIDDEN);
        } else {
            HSD_JObjClearFlagsAll(data2->jobjs[4], JOBJ_HIDDEN);
            HSD_JObjClearFlagsAll(data2->jobjs[3], JOBJ_HIDDEN);
        }

        if (user_data->is_name_mode != 0) {
            indices = user_data->name_cursor_pos;
            row_idx = indices >> 8;
            col_idx = indices & 0xFF;
            d = GET_DIAGRAM(gobj);
            mnDiagram_80241668(gobj);
            mnDiagram_8024227C(gobj, col_idx, row_idx,
                               (u8) (d->is_name_mode == 1));
            if (d->is_name_mode == 0) {
                mnDiagram_80242C0C(gobj, col_idx, row_idx);
            } else {
                mnDiagram_802427B4(gobj, col_idx, row_idx);
            }
        } else {
            indices = user_data->fighter_cursor_pos;
            row_idx2 = indices >> 8;
            col_idx2 = indices & 0xFF;
            d2 = GET_DIAGRAM(gobj);
            mnDiagram_80241668(gobj);
            mnDiagram_8024227C(gobj, col_idx2, row_idx2,
                               (u8) (d2->is_name_mode == 1));
            if (d2->is_name_mode == 0) {
                mnDiagram_80242C0C(gobj, col_idx2, row_idx2);
            } else {
                mnDiagram_802427B4(gobj, col_idx2, row_idx2);
            }
        }
    }
}

/// Initialize VS Records diagram screen.
/// @param arg0 If non-zero, load DAT archive symbols
/// @param arg1 Initial mode (passed to mnDiagram_80243434)
void mnDiagram_802437E8(u8 arg0, u8 arg1)
{
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
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
            archive, &assets->ConB1[0], "MenMainConB1_Top_joint",
            &assets->ConB1[1], "MenMainConB1_Top_animjoint", &assets->ConB1[2],
            "MenMainConB1_Top_matanim_joint", &assets->ConB1[3],
            "MenMainConB1_Top_shapeanim_joint", &assets->CursorB1[0],
            "MenMainCursorB1_Top_joint", &assets->FaceB[0],
            "MenMainFaceB_Top_joint", &assets->FaceB[1],
            "MenMainFaceB_Top_animjoint", &assets->FaceB[2],
            "MenMainFaceB_Top_matanim_joint", &assets->FaceB[3],
            "MenMainFaceB_Top_shapeanim_joint", &assets->NmB[0],
            "MenMainNmB_Top_joint", &assets->NmB[1],
            "MenMainNmB_Top_animjoint", &assets->NmB[2],
            "MenMainNmB_Top_matanim_joint", &assets->NmB[3],
            "MenMainNmB_Top_shapeanim_joint", &assets->SubB1[0],
            "MenMainSubB1_Top_joint", &assets->SubB1[1],
            "MenMainSubB1_Top_animjoint", &assets->SubB1[2],
            "MenMainSubB1_Top_matanim_joint", &assets->SubB1[3],
            "MenMainSubB1_Top_shapeanim_joint", &assets->ConB2[0],
            "MenMainConB2_Top_joint", &assets->ConB2[1],
            "MenMainConB2_Top_animjoint", &assets->ConB2[2],
            "MenMainConB2_Top_matanim_joint", &assets->ConB2[3],
            "MenMainConB2_Top_shapeanim_joint", &assets->ConB3[0],
            "MenMainConB3_Top_joint", &assets->ConB3[1],
            "MenMainConB3_Top_animjoint", &assets->ConB3[2],
            "MenMainConB3_Top_matanim_joint", &assets->ConB3[3],
            "MenMainConB3_Top_shapeanim_joint", &assets->CursorB3[0],
            "MenMainCursorB3_Top_joint", 0);
    }

    mnDiagram_8023FA6C();
    mnDiagram_8023FC28();
    mnDiagram_80243434(mode_storage[0]);

    gobj = GObj_Create(0, 1, 0x80);
    proc =
        HSD_GObj_SetupProc(gobj, (void (*)(HSD_GObj*)) mnDiagram_InputProc, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
