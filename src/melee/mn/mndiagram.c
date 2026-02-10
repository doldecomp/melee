#include "mndiagram.static.h"
#include "mndiagram2.static.h"

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
#include "mn/mndiagram2.h"
#include "mn/mndiagram3.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"

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

/// Archive asset pointers struct (for mnDiagram_Init)
/// Cast from &mnDiagram_804A0750 to access asset arrays
typedef struct mnDiagram_Assets {
    /* 0x00 */ u8 sorted_fighters[0x19];
    /* 0x19 */ u8 pad_19[3];
    /* 0x1C */ u8 sorted_names[0x78];
    /* 0x94 */ void* SubB1[4];
    /* 0xA4 */ void* ConB2[4];
    /* 0xB4 */ void* ConB3[4];
    /* 0xC4 */ void* CursorB3[4];
    /* 0xD4 */ void* ConB1[4];
    /* 0xE4 */ void* CursorB1_FaceB[4];
    /* 0xF4 */ void* FaceB_NmB[4];
    /* 0x104 */ void* NmB_shape[1];
} mnDiagram_Assets;
STATIC_ASSERT(sizeof(mnDiagram_Assets) == 0x108);

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
        return (u32) ((f64) distance / 30.4788F);
    }
    if (distance >= 0x186A0) {
        return distance / 100000;
    }
    return distance / 100;
}

s32 mnDiagram_GetHitPercentage(u8 is_name_mode, u8 player_index)
{
    f32 player_attacks;
    f32 tag_player_attacks;

    if (is_name_mode != 0) {
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

    if (is_name_mode != 0) {
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

s32 mnDiagram_GetAveragePlayerCount(u8 is_name_mode, u8 player_index)
{
    f32 temp_f31;
    f32 temp_f31_2;

    if (is_name_mode != 0) {
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
/// @param row_idx Fighter index (0-24).
/// @return Play time in seconds for this fighter under this name.
u32 mnDiagram_GetNamePlayTimeByFighter(int name_idx, int row_idx)
{
    return GetPersistentNameData(name_idx)->play_time_by_fighter[row_idx];
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
    int i;
    for (i = 0; i < 0x19; i++) {
        if (GetPersistentNameData(name_idx)->play_time_by_fighter[i] != 0U) {
            return 0;
        }
    }
    return 1;
}

// todo: this has gotta be fake - but i couldn't get the
// other one to work for both functions
static inline int CheckAllZeroPlayTime_u8(u8 name_idx)
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

u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx)
{
    int i;
    int min_fighter;
    int count;

    // Check if all play times are zero
    if (CheckAllZeroPlayTime_u8(name_idx) != 0) {
        return 0x19;
    }

    // Find fighter with minimum play time
    min_fighter = 0;
    for (i = 1; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i)) {
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

/// @brief Sorts fighters by total KOs in descending order.
/// @details Uses selection sort to rank fighters by their cumulative KO count
///          against all unlocked fighters. Results stored in sorted_fighters.
void mnDiagram_SortFightersByKOs(void)
{
    u32 totals[0x19];
    int i, j;
    u8* src = mnDiagram_803EE74C;
    u8* dst = mnDiagram_804A0750.sorted_fighters;

    for (i = 0; i < 0x19; i++) {
        u32 total = 0;
        dst[i] = src[i];
        for (j = 0; j < 0x19; j++) {
            if (mn_IsFighterUnlocked(j) != 0) {
                total += GetPersistentFighterData(src[i])->fighter_kos[j];
            }
        }
        totals[src[i]] = total;
    }

    for (i = 0; i < 0x19; i++) {
        int max_idx = i;
        for (j = i + 1; j < 0x19; j++) {
            if ((mn_IsFighterUnlocked(dst[j]) != 0) &&
                ((totals[dst[max_idx]] < totals[dst[j]]) ||
                 (mn_IsFighterUnlocked(dst[max_idx]) == 0)))
            {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            u8* p = &dst[max_idx];
            int n = max_idx - i;
            u8 temp = *p;
            while (n > 0) {
                *p = *(p - 1);
                p--;
                n--;
            }
            dst[i] = temp;
        }
    }
}

/// @brief Sorts player names by total KOs in descending order.
/// @details Uses selection sort to rank names by their cumulative KO count
///          against all valid names. Results stored in sorted_names.
void mnDiagram_SortNamesByKOs(void)
{
    u32 totals[0x78];
    int i, j;
    u8* dst = ((mnDiagram_Assets*) &mnDiagram_804A0750)->sorted_names;
    PAD_STACK(16);

    for (i = 0; i < 0x78; i++) {
        u32 total = 0;
        dst[i] = (u8) i;
        for (j = 0; j < 0x78; j++) {
            if (GetNameText((u8) j) != NULL) {
                total += GetPersistentNameData((u8) i)->vs_kos[(u8) j];
            }
        }
        totals[i] = total;
    }

    for (i = 0; i < 0x78; i++) {
        int max_idx = i;
        for (j = i + 1; j < 0x78; j++) {
            if ((GetNameText(dst[j]) != NULL) &&
                ((totals[dst[max_idx]] < totals[dst[j]]) ||
                 (GetNameText(dst[max_idx]) == NULL)))
            {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            u8* p = &dst[max_idx];
            int n = max_idx - i;
            u8 temp = *p;
            while (n > 0) {
                *p = *(p - 1);
                p--;
                n--;
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

void mnDiagram_PopupInputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    Diagram* data = mnDiagram_804D6C10->user_data;
    u32 input = mn_80229624(4);
    PAD_STACK(8);

    mn_804A04F0.buttons = input;

    if (input & 0x20) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(
            gobj, (void (*)(HSD_GObj*)) mnDiagram_InputProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_GObjPLink_80390228(data->popup_gobj);
        data->popup_gobj = NULL;
    }
}

void mnDiagram_InputProc(HSD_GObj* gobj)
{
    HSD_GObjProc* proc;
    u8* base = (u8*) &mnDiagram_804A0750;
    Diagram* data = mnDiagram_804D6C10->user_data;
    u32 input = mn_80229624(4);
    s32 is_name_mode = 0;
    s32 row_idx;
    s32 col_idx;
    s32 count;
    s32 new_pos;
    u8* ptr;
    u8* iter;
    u8 result;
    PAD_STACK(80);

    mn_804A04F0.buttons = input;

    if (input & 0x10) {
        // A button - open popup
        lbAudioAx_80024030(1);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(
            gobj, (void (*)(HSD_GObj*)) mnDiagram_PopupInputProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        if (data->is_name_mode != 0) {
            // Name mode - find position in sorted names
            row_idx = (u8) data->name_cursor_pos;
            col_idx = (u8) mn_804A04F0.hovered_selection;
            ptr = base + row_idx + 0x1C;
            while (col_idx > 0) {
                row_idx++;
                ptr++;
                if (row_idx >= 0x78) {
                    col_idx = 0x78;
                    goto name_col_done;
                }
                if (GetNameText(*ptr) != NULL) {
                    col_idx--;
                }
            }
            col_idx = base[row_idx + 0x1C];
        name_col_done:
            new_pos = (s32) mn_804A04F0.hovered_selection >> 8;
            row_idx = (s32) data->name_cursor_pos >> 8;
            ptr = base + row_idx + 0x1C;
            while (new_pos > 0) {
                row_idx++;
                ptr++;
                if (row_idx >= 0x78) {
                    result = 0x78;
                    goto name_row_done;
                }
                if (GetNameText(*ptr) != NULL) {
                    new_pos--;
                }
            }
            result = base[row_idx + 0x1C];
        name_row_done:
            mnDiagram_CreatePopup((u8) col_idx, result, 1);
        } else {
            // Fighter mode - find position in sorted fighters
            row_idx = (u8) data->fighter_cursor_pos;
            col_idx = (u8) mn_804A04F0.hovered_selection;
            ptr = base + row_idx;
            while (col_idx >= 0) {
                if (col_idx == 0) {
                    result = base[row_idx];
                    goto fighter_col_done;
                }
                iter = ptr;
                row_idx++;
                iter++;
                ptr++;
                if (row_idx >= 0x19) {
                    result = 0x19;
                    goto fighter_col_done;
                }
                if (mn_IsFighterUnlocked(*iter) != 0) {
                    col_idx--;
                }
            }
        fighter_col_done:
            new_pos = (s32) mn_804A04F0.hovered_selection >> 8;
            row_idx = (s32) data->fighter_cursor_pos >> 8;
            ptr = base + row_idx;
            while (new_pos >= 0) {
                if (new_pos == 0) {
                    col_idx = base[row_idx];
                    goto fighter_row_done;
                }
                iter = ptr;
                row_idx++;
                iter++;
                ptr++;
                if (row_idx >= 0x19) {
                    col_idx = 0x19;
                    goto fighter_row_done;
                }
                if (mn_IsFighterUnlocked(*iter) != 0) {
                    new_pos--;
                }
            }
        fighter_row_done:
            mnDiagram_CreatePopup(result, (u8) col_idx, 0);
        }
        return;
    }

    if (input & 0x20) {
        // B button - exit menu
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = is_name_mode;
        data = mnDiagram_804D6C10->user_data;
        gmMainLib_8015CC34()->xE = (u8) (data->fighter_cursor_pos >> 8);
        gmMainLib_8015CC34()->xF = (u8) data->fighter_cursor_pos;
        gmMainLib_8015CC34()->unk_x10 = (u8) (data->name_cursor_pos >> 8);
        gmMainLib_8015CC34()->x11 = (u8) data->name_cursor_pos;
        gmMainLib_8015CC34()->xD = data->is_name_mode;
        mn_80229894(0x1C, 0, 3);
        return;
    }

    if (input & 0xC0) {
        // L/R buttons - switch screens
        lbAudioAx_80024030(1);
        data = mnDiagram_804D6C10->user_data;
        gmMainLib_8015CC34()->xE = (u8) (data->fighter_cursor_pos >> 8);
        gmMainLib_8015CC34()->xF = (u8) data->fighter_cursor_pos;
        gmMainLib_8015CC34()->unk_x10 = (u8) (data->name_cursor_pos >> 8);
        gmMainLib_8015CC34()->x11 = (u8) data->name_cursor_pos;
        gmMainLib_8015CC34()->xD = data->is_name_mode;
        HSD_GObjPLink_80390228(gobj);
        if (input & 0x40) {
            mnDiagram3_8024714C(NULL);
        } else {
            mnDiagram2_Init();
        }
        return;
    }

    if (input & 0xC00) {
        // Toggle name/fighter mode
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        if (data->is_name_mode == 0) {
            is_name_mode = 1;
        }
        data->is_name_mode = is_name_mode;
        if (data->is_name_mode != 0) {
            count = GetNameCount();
            if ((u8) mn_804A04F0.hovered_selection >= count) {
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    (u8) (count - 1);
            }
            if ((s32) mn_804A04F0.hovered_selection >> 8 >= count) {
                mn_804A04F0.hovered_selection =
                    ((count - 1) << 8) | ((u8) mn_804A04F0.hovered_selection);
            }
            mnDiagram_UpdateScrollArrowVisibility(mnDiagram_804D6C10, count);
            mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                        (u8) data->name_cursor_pos,
                                        data->name_cursor_pos >> 8);
        } else {
            count = 0;
            for (col_idx = 0; col_idx < 0x19; col_idx++) {
                if (mn_IsFighterUnlocked(col_idx) != 0) {
                    count++;
                }
            }
            if ((u8) mn_804A04F0.hovered_selection >= count) {
                mn_804A04F0.hovered_selection =
                    (mn_804A04F0.hovered_selection & 0xFF00) |
                    (u8) (count - 1);
            }
            if ((s32) mn_804A04F0.hovered_selection >> 8 >= count) {
                mn_804A04F0.hovered_selection =
                    ((count - 1) << 8) | ((u8) mn_804A04F0.hovered_selection);
            }
            mnDiagram_UpdateScrollArrowVisibility(mnDiagram_804D6C10, count);
            mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                        (u8) data->fighter_cursor_pos,
                                        data->fighter_cursor_pos >> 8);
        }
        return;
    }

    // D-pad navigation
    if (data->is_name_mode != 0) {
        // Name mode navigation
        count = GetNameCount();
        if (input & 1) {
            // Left
            col_idx = (u8) mn_804A04F0.hovered_selection;
            if (col_idx > 0) {
                new_pos = col_idx - 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        (mn_804A04F0.hovered_selection & 0xFF00) |
                        (u8) new_pos;
                    return;
                }
            }
            if (count > 10) {
                row_idx = (u8) data->name_cursor_pos;
                new_pos = row_idx;
                while (new_pos > 0) {
                    new_pos--;
                    if (GetNameText((u8) new_pos) != NULL) {
                        break;
                    }
                    if (new_pos < 0) {
                        new_pos = row_idx;
                        break;
                    }
                }
                if (row_idx != new_pos) {
                    lbAudioAx_80024030(2);
                    data->name_cursor_pos =
                        (data->name_cursor_pos & 0xFF00) | (u8) new_pos;
                    mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                                (u8) data->name_cursor_pos,
                                                data->name_cursor_pos >> 8);
                }
            }
        } else if (input & 2) {
            // Right
            col_idx = (u8) mn_804A04F0.hovered_selection;
            if (col_idx < 9) {
                new_pos = col_idx + 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        (mn_804A04F0.hovered_selection & 0xFF00) |
                        (u8) new_pos;
                    return;
                }
            }
            if (count > 10) {
                row_idx = (u8) data->name_cursor_pos;
                new_pos = row_idx;
                while (new_pos < 0x78) {
                    new_pos++;
                    if (new_pos >= 0x78) {
                        new_pos = row_idx;
                        break;
                    }
                    if (GetNameText((u8) new_pos) != NULL) {
                        break;
                    }
                }
                result = (u8) new_pos;
                if (row_idx != result) {
                    // Check if we have enough items to scroll
                    col_idx = 10;
                    ptr = base + row_idx + 0x1C;
                    while (col_idx > 0) {
                        row_idx++;
                        ptr++;
                        if (row_idx >= 0x78) {
                            result = 0x78;
                            break;
                        }
                        if (GetNameText(*ptr) != NULL) {
                            col_idx--;
                            if (col_idx <= 0) {
                                result = base[row_idx + 0x1C];
                                break;
                            }
                        }
                    }
                    if (result != 0x78) {
                        lbAudioAx_80024030(2);
                        data->name_cursor_pos =
                            (data->name_cursor_pos & 0xFF00) | (u8) new_pos;
                        mnDiagram_UpdateGridDisplay(
                            mnDiagram_804D6C10, (u8) data->name_cursor_pos,
                            data->name_cursor_pos >> 8);
                    }
                }
            }
        } else if (input & 4) {
            // Up
            row_idx = (s32) mn_804A04F0.hovered_selection >> 8;
            if (row_idx > 0) {
                new_pos = row_idx - 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        ((u8) mn_804A04F0.hovered_selection) | (new_pos << 8);
                    return;
                }
            }
            if (count > 7) {
                row_idx = (s32) data->name_cursor_pos >> 8;
                new_pos = row_idx;
                while (new_pos > 0) {
                    new_pos--;
                    if (GetNameText((u8) new_pos) != NULL) {
                        break;
                    }
                    if (new_pos < 0) {
                        new_pos = row_idx;
                        break;
                    }
                }
                if (row_idx != new_pos) {
                    lbAudioAx_80024030(2);
                    data->name_cursor_pos =
                        ((u8) data->name_cursor_pos) | ((u8) new_pos << 8);
                    mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                                (u8) data->name_cursor_pos,
                                                data->name_cursor_pos >> 8);
                }
            }
        } else if (input & 8) {
            // Down
            row_idx = (s32) mn_804A04F0.hovered_selection >> 8;
            if (row_idx < 6) {
                new_pos = row_idx + 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        ((u8) mn_804A04F0.hovered_selection) | (new_pos << 8);
                    return;
                }
            }
            if (count > 7) {
                row_idx = (s32) data->name_cursor_pos >> 8;
                new_pos = row_idx;
                while (new_pos < 0x78) {
                    new_pos++;
                    if (new_pos >= 0x78) {
                        new_pos = row_idx;
                        break;
                    }
                    if (GetNameText((u8) new_pos) != NULL) {
                        break;
                    }
                }
                result = (u8) new_pos;
                if (row_idx != result) {
                    // Check boundary
                    col_idx = 7;
                    ptr = base + row_idx + 0x1C;
                    while (col_idx > 0) {
                        row_idx++;
                        ptr++;
                        if (row_idx >= 0x78) {
                            result = 0x78;
                            break;
                        }
                        if (GetNameText(*ptr) != NULL) {
                            col_idx--;
                            if (col_idx <= 0) {
                                result = base[row_idx + 0x1C];
                                break;
                            }
                        }
                    }
                    if (result != 0x78) {
                        lbAudioAx_80024030(2);
                        data->name_cursor_pos =
                            ((u8) data->name_cursor_pos) | ((u8) new_pos << 8);
                        mnDiagram_UpdateGridDisplay(
                            mnDiagram_804D6C10, (u8) data->name_cursor_pos,
                            data->name_cursor_pos >> 8);
                    }
                }
            }
        }
    } else {
        // Fighter mode navigation
        count = 0;
        for (col_idx = 0; col_idx < 0x19; col_idx++) {
            if (mn_IsFighterUnlocked(col_idx) != 0) {
                count++;
            }
        }
        if (input & 1) {
            // Left
            col_idx = (u8) mn_804A04F0.hovered_selection;
            if (col_idx > 0) {
                new_pos = col_idx - 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        (mn_804A04F0.hovered_selection & 0xFF00) |
                        (u8) new_pos;
                    return;
                }
            }
            if (count > 10) {
                row_idx = (u8) data->fighter_cursor_pos;
                ptr = base + row_idx;
                new_pos = row_idx;
                while (new_pos > 0) {
                    new_pos--;
                    ptr--;
                    if (mn_IsFighterUnlocked(*ptr) != 0) {
                        break;
                    }
                    if (new_pos < 0) {
                        new_pos = row_idx;
                        break;
                    }
                }
                if (row_idx != new_pos) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        (data->fighter_cursor_pos & 0xFF00) | (u8) new_pos;
                    mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                                (u8) data->fighter_cursor_pos,
                                                data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & 2) {
            // Right
            col_idx = (u8) mn_804A04F0.hovered_selection;
            if (col_idx < 9) {
                new_pos = col_idx + 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        (mn_804A04F0.hovered_selection & 0xFF00) |
                        (u8) new_pos;
                    return;
                }
            }
            if (count > 10) {
                row_idx = (u8) data->fighter_cursor_pos;
                ptr = base + row_idx;
                new_pos = row_idx;
                while (new_pos < 0x19) {
                    new_pos++;
                    ptr++;
                    if (new_pos >= 0x19) {
                        new_pos = row_idx;
                        break;
                    }
                    if (mn_IsFighterUnlocked(*ptr) != 0) {
                        break;
                    }
                }
                result = (u8) new_pos;
                if (row_idx != result) {
                    // Check boundary
                    col_idx = 10;
                    ptr = base + row_idx;
                    while (col_idx > 0) {
                        if (col_idx == 0) {
                            result = base[row_idx];
                            break;
                        }
                        row_idx++;
                        ptr++;
                        if (row_idx >= 0x19) {
                            result = 0x19;
                            break;
                        }
                        if (mn_IsFighterUnlocked(*ptr) != 0) {
                            col_idx--;
                        }
                    }
                    if (result != 0x19) {
                        lbAudioAx_80024030(2);
                        data->fighter_cursor_pos =
                            (data->fighter_cursor_pos & 0xFF00) | (u8) new_pos;
                        mnDiagram_UpdateGridDisplay(
                            mnDiagram_804D6C10, (u8) data->fighter_cursor_pos,
                            data->fighter_cursor_pos >> 8);
                    }
                }
            }
        } else if (input & 4) {
            // Up
            row_idx = (s32) mn_804A04F0.hovered_selection >> 8;
            if (row_idx > 0) {
                new_pos = row_idx - 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        ((u8) mn_804A04F0.hovered_selection) | (new_pos << 8);
                    return;
                }
            }
            if (count > 7) {
                row_idx = (s32) data->fighter_cursor_pos >> 8;
                ptr = base + row_idx;
                new_pos = row_idx;
                while (new_pos > 0) {
                    new_pos--;
                    ptr--;
                    if (mn_IsFighterUnlocked(*ptr) != 0) {
                        break;
                    }
                    if (new_pos < 0) {
                        new_pos = row_idx;
                        break;
                    }
                }
                if (row_idx != new_pos) {
                    lbAudioAx_80024030(2);
                    data->fighter_cursor_pos =
                        ((u8) data->fighter_cursor_pos) | ((u8) new_pos << 8);
                    mnDiagram_UpdateGridDisplay(mnDiagram_804D6C10,
                                                (u8) data->fighter_cursor_pos,
                                                data->fighter_cursor_pos >> 8);
                }
            }
        } else if (input & 8) {
            // Down
            row_idx = (s32) mn_804A04F0.hovered_selection >> 8;
            if (row_idx < 6) {
                new_pos = row_idx + 1;
                if (count > new_pos) {
                    lbAudioAx_80024030(2);
                    mn_804A04F0.hovered_selection =
                        ((u8) mn_804A04F0.hovered_selection) | (new_pos << 8);
                    return;
                }
            }
            if (count > 7) {
                row_idx = (s32) data->fighter_cursor_pos >> 8;
                ptr = base + row_idx;
                new_pos = row_idx;
                while (new_pos < 0x19) {
                    new_pos++;
                    ptr++;
                    if (new_pos >= 0x19) {
                        new_pos = row_idx;
                        break;
                    }
                    if (mn_IsFighterUnlocked(*ptr) != 0) {
                        break;
                    }
                }
                result = (u8) new_pos;
                if (row_idx != result) {
                    // Check boundary
                    col_idx = 7;
                    ptr = base + row_idx;
                    while (col_idx > 0) {
                        if (col_idx == 0) {
                            result = base[row_idx];
                            break;
                        }
                        row_idx++;
                        ptr++;
                        if (row_idx >= 0x19) {
                            result = 0x19;
                            break;
                        }
                        if (mn_IsFighterUnlocked(*ptr) != 0) {
                            col_idx--;
                        }
                    }
                    if (result != 0x19) {
                        lbAudioAx_80024030(2);
                        data->fighter_cursor_pos =
                            ((u8) data->fighter_cursor_pos) |
                            ((u8) new_pos << 8);
                        mnDiagram_UpdateGridDisplay(
                            mnDiagram_804D6C10, (u8) data->fighter_cursor_pos,
                            data->fighter_cursor_pos >> 8);
                    }
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
    /* 0x38 */ HSD_Text* text[6];
} mnDiagram_PopupData;

void mnDiagram_PopupAnimProc(void* arg0)
{
    mnDiagram_PopupData* data = ((HSD_GObj*) arg0)->user_data;
    Point3d pos;

    HSD_JObjAnimAll(data->jobjs[5]);
    lb_8000B1CC(data->jobjs[8], mnDiagram_803EE728, &pos);
    data->text[0]->pos_x = pos.x;
    data->text[0]->pos_y = -pos.y;
    data->text[0]->pos_z = pos.z;

    HSD_JObjAnim(data->jobjs[9]);
    if (data->text[1] != NULL) {
        lb_8000B1CC(data->jobjs[11], &mnDiagram_803EE728[1], &pos);
        data->text[1]->pos_x = pos.x;
        data->text[1]->pos_y = -pos.y;
        data->text[1]->pos_z = pos.z;
    }
    if (data->text[2] != NULL) {
        lb_8000B1CC(data->jobjs[10], &mnDiagram_803EE728[2], &pos);
        data->text[2]->pos_x = pos.x;
        data->text[2]->pos_y = -pos.y;
        data->text[2]->pos_z = pos.z;
    }

    HSD_JObjAnim(data->jobjs[1]);
    lb_8000B1CC(data->jobjs[3], &mnDiagram_803EE728[1], &pos);
    data->text[3]->pos_x = pos.x;
    data->text[3]->pos_y = -pos.y;
    data->text[3]->pos_z = pos.z;

    if (data->text[4] != NULL) {
        lb_8000B1CC(data->jobjs[2], &mnDiagram_803EE728[2], &pos);
        data->text[4]->pos_x = pos.x;
        data->text[4]->pos_y = -pos.y;
        data->text[4]->pos_z = pos.z;
    }

    mn_8022EFD8(data->jobjs[12],
                (AnimLoopSettings*) (mnDiagram_803EE728 + 0x64));
    lb_8000B1CC(data->jobjs[13], &mnDiagram_803EE728[1], &pos);
    data->text[3]->pos_x = pos.x;
    data->text[3]->pos_y = -pos.y;
    data->text[3]->pos_z = pos.z;
}

/// @brief Sets up text elements for the popup detail window.
/// @param gobj The popup GObj.
/// @param col_idx Column index (fighter/name index for column).
/// @param row_idx Row index (fighter/name index for row).
/// @param is_name_mode 1 for name mode, 0 for fighter mode.
void mnDiagram_PopupSetupText(void* gobj, s32 col_idx, s32 row_idx,
                              s32 is_name_mode)
{
    mnDiagram_PopupData* data = ((HSD_GObj*) gobj)->user_data;
    Point3d pos;
    char buf[8];
    u16 kos;
    u16 sd_count;

    HSD_Text* text = HSD_SisLib_803A6754(0, 1);
    data->text[0] = text;
    lb_8000B1CC(data->jobjs[8], mnDiagram_803EE728, &pos);
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    text->pos_x = pos.x;
    text->pos_y = -pos.y;
    text->pos_z = pos.z;
    text->default_alignment = 0;
    *(s32*) &text->text_color = mnDiagram_804D4FA0;

    if (is_name_mode != 0) {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) col_idx));
    } else {
        gm_80160C90(text, gm_8016400C((u8) col_idx), 0);
    }

    if ((is_name_mode != 0) && (col_idx != row_idx)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[2] = text;
        lb_8000B1CC(data->jobjs[10], &mnDiagram_803EE728[2], &pos);
        text->font_size.x = 0.035f;
        text->font_size.y = 0.05f;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;
        text->default_alignment = 1;
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) row_idx));

        text = HSD_SisLib_803A6754(0, 1);
        data->text[4] = text;
        lb_8000B1CC(data->jobjs[2], &mnDiagram_803EE728[2], &pos);
        text->font_size.x = 0.035f;
        text->font_size.y = 0.05f;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;
        text->default_alignment = 1;
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) row_idx));
    }

    if ((is_name_mode == 0) || (col_idx != row_idx)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[1] = text;
        lb_8000B1CC(data->jobjs[11], &mnDiagram_803EE728[1], &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;

        if (is_name_mode != 0) {
            kos = GetPersistentNameData(col_idx)->vs_kos[row_idx];
        } else {
            kos = GetPersistentFighterData(col_idx)->fighter_kos[row_idx];
        }
        mnDiagram_IntToStr(buf, kos);
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }

    text = HSD_SisLib_803A6754(0, 1);
    data->text[3] = text;
    if (col_idx == row_idx) {
        lb_8000B1CC(data->jobjs[13], &mnDiagram_803EE728[1], &pos);
        if (is_name_mode != 0) {
            sd_count = GetPersistentNameData(col_idx)->sd_count;
        } else {
            sd_count = GetPersistentFighterData(col_idx)->sd_count;
        }
        mnDiagram_IntToStr(buf, sd_count);
    } else {
        lb_8000B1CC(data->jobjs[3], &mnDiagram_803EE728[1], &pos);
        if (is_name_mode != 0) {
            kos = GetPersistentNameData((u8) row_idx)->vs_kos[col_idx];
        } else {
            kos = GetPersistentFighterData((u8) row_idx)->fighter_kos[col_idx];
        }
        mnDiagram_IntToStr(buf, kos);
    }
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    text->default_alignment = 1;
    text->pos_x = pos.x;
    text->pos_y = -pos.y;
    text->pos_z = pos.z;
    HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
}

/// @brief Creates the popup detail window showing KO stats for a cell.
/// @param col_idx Column index in the grid.
/// @param row_idx Row index in the grid.
/// @param is_name_mode 1 for name mode, 0 for fighter mode.
void mnDiagram_CreatePopup(s32 col_idx, s32 row_idx, s32 is_name_mode)
{
    Diagram* data;
    char* base;
    void** joint_data;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    mnDiagram_PopupData* popup_data;
    int i;
    PAD_STACK(8);

    data = mnDiagram_804D6C10->user_data;
    base = (char*) &mnDiagram_803EE728;
    joint_data = mnDiagram_804A07E4;

    gobj = GObj_Create(6, 7, 0x80);
    data->popup_gobj = gobj;
    jobj = HSD_JObjLoadJoint(joint_data[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);

    popup_data = HSD_MemAlloc(sizeof(mnDiagram_PopupData));
    if (popup_data == NULL) {
        OSReport(base + 0x70);
        __assert(base + 0x88, 0x5F8, base + 0x94);
    }
    GObj_InitUserData(gobj, 0, mnDiagram_PopupCleanup, popup_data);
    popup_data->text[4] = NULL;
    popup_data->text[3] = NULL;
    popup_data->text[2] = NULL;
    popup_data->text[1] = NULL;
    popup_data->text[0] = NULL;

    for (i = 0; i < 14; i++) {
        lb_80011E24(jobj, &popup_data->jobjs[i], i, -1);
    }

    HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) mnDiagram_PopupAnimProc,
                          0);
    mnDiagram_PopupSetupText(gobj, col_idx, row_idx, is_name_mode);

    if (is_name_mode != 0) {
        if (col_idx == row_idx) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[9], JOBJ_HIDDEN);
        }
        if (col_idx == row_idx) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[1], JOBJ_HIDDEN);
        }
        if (col_idx != row_idx) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[12], JOBJ_HIDDEN);
        }
    } else {
        HSD_JObj* icon = mnDiagram_CreateFighterIcon(col_idx, 1);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        mn_8022F3D8(icon, 0xA, TOBJ_MASK);
        HSD_JObjAddChild(popup_data->jobjs[7], icon);

        icon = mnDiagram_CreateFighterIcon(row_idx, 1);
        HSD_JObjSetTranslateX(icon, -1.0f);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        HSD_JObjAddChild(popup_data->jobjs[10], icon);

        if (col_idx == row_idx) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[1], JOBJ_HIDDEN);
        } else {
            icon = mnDiagram_CreateFighterIcon(row_idx, 1);
            HSD_JObjSetTranslateX(icon, -1.0f);
            mn_8022F3D8(icon, 1, TOBJ_MASK);
            HSD_JObjAddChild(popup_data->jobjs[2], icon);
        }
        if (col_idx != row_idx) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[12], JOBJ_HIDDEN);
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

/// @brief Clears grid content (JObj children and text labels).
/// @param gobj The diagram GObj.
void mnDiagram_ClearGridContent(void* gobj)
{
    mnDiagram_PopupData* data = mnDiagram_GetUserData(gobj);
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

/// @brief Updates the grid display when cursor moves.
/// @details Clears old content and redraws grid cells and headers.
/// @param gobj The diagram GObj.
/// @param col_idx Column scroll offset.
/// @param row_idx Row scroll offset.
void mnDiagram_UpdateGridDisplay(void* gobj, int col_idx, int row_idx)
{
    Diagram* data = ((HSD_GObj*) gobj)->user_data;
    mnDiagram_ClearGridContent(gobj);
    mnDiagram_DrawGridCells(gobj, col_idx, row_idx,
                            (u8) (data->is_name_mode == 1));
    if (data->is_name_mode == 0) {
        mnDiagram_DrawFighterHeaders(gobj, col_idx, row_idx);
    } else {
        mnDiagram_DrawNameHeaders(gobj, col_idx, row_idx);
    }
}

/// @brief Updates directional arrow visibility based on scroll position.
/// @details Runs every frame to show/hide the 4 navigation arrows:
///          - jobjs[3] (Right): Visible if more columns exist to the right
///          - jobjs[4] (Up): Visible if row_scroll > 0 (rows scrolled off top)
///          - jobjs[5] (Left): Visible if col_scroll > 0 (columns scrolled off left)
///          - jobjs[6] (Down): Visible if more rows exist below
///          The cursor_pos fields store scroll offset as (col_scroll << 8 | row_scroll),
///          not the cursor position within the visible grid.
#pragma push
#pragma dont_reuse_strings off
void mnDiagram_UpdateScrollArrows(HSD_GObj* gobj)
{
    u8 result2;
    Diagram* data = gobj->user_data;
    char* base = (char*) mnDiagram_803EE728;
    HSD_JObj* jobj;
    int i;
    u8* sorted = (u8*) &mnDiagram_804A0750;
    u8* ptr;
    u8* ptr2;
    int count;
    HSD_JObj* jobj2;
    u8 result;
    PAD_STACK(8);

    // Right arrow (jobjs[3])
    jobj = data->jobjs[3];
    mn_8022ED6C(jobj, (AnimLoopSettings*) (base + 0x58));
    if (data->is_name_mode != 0) {
        // Name mode - check if 10 more names exist
        count = 10;
        i = (u8) data->name_cursor_pos;
        ptr = sorted + i;
        ptr = ptr + 28;
        do {
            ptr2 = ptr;
            do {
                i++;
                ptr2++;
                ptr++;
                if (i >= 0x78) {
                    result = 0x78;
                    goto done_name;
                }
            } while (GetNameText(*ptr2) == NULL);
            count--;
        } while (count > 0);
        result = sorted[i + 28];
    done_name:
        if ((u8) result != 0x78) {
            HSD_JObjClearFlagsAll(jobj, 0x10U);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10U);
        }
    } else {
        // Fighter mode - check if 10 more fighters exist
        count = 10;
        i = (u8) data->fighter_cursor_pos;
        ptr = sorted + i;
    loop3:
        if (count == 0) {
            result = sorted[i];
        } else {
            ptr2 = ptr;
        loop4:
            i++;
            ptr2++;
            ptr++;
            if (i >= 0x19) {
                result = 0x19;
            } else if (mn_IsFighterUnlocked(*ptr2) == 0) {
                goto loop4;
            } else {
                count--;
                if (count >= 0) {
                    goto loop3;
                }
            }
        }
        if ((u8) result != 0x19) {
            HSD_JObjClearFlagsAll(jobj, 0x10U);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10U);
        }
    }

    // Up arrow (jobjs[4]) - visible when row_scroll > 0 (rows scrolled off top)
    jobj2 = data->jobjs[4];
    mn_8022ED6C(jobj2, (AnimLoopSettings*) (base + 0x58));
    if (data->is_name_mode != 0) {
        result = (u8) data->name_cursor_pos;
    } else {
        result = (u8) data->fighter_cursor_pos;
    }
    if (result != 0) {
        HSD_JObjClearFlagsAll(jobj2, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj2, 0x10U);
    }

    // Left arrow (jobjs[5]) - visible when col_scroll > 0 (columns scrolled off left)
    jobj2 = data->jobjs[5];
    mn_8022ED6C(jobj2, (AnimLoopSettings*) (base + 0x58));
    if (data->is_name_mode != 0) {
        i = data->name_cursor_pos >> 8;
    } else {
        i = data->fighter_cursor_pos >> 8;
    }
    if (i != 0) {
        HSD_JObjClearFlagsAll(jobj2, 0x10U);
    } else {
        HSD_JObjSetFlagsAll(jobj2, 0x10U);
    }

    // Down arrow (jobjs[6])
    jobj = data->jobjs[6];
    mn_8022ED6C(jobj, (AnimLoopSettings*) (base + 0x58));
    if (data->is_name_mode != 0) {
        // Name mode - check if 7 more rows exist
        count = 7;
        i = data->name_cursor_pos >> 8;
        ptr = sorted + i;
        ptr = ptr + 0x1C;
    loop5:
        ptr2 = ptr;
    loop6:
        i++;
        ptr2++;
        ptr++;
        if (i >= 0x78) {
            result2 = 0x78;
        } else if (GetNameText(*ptr2) == NULL) {
            goto loop6;
        } else {
            count--;
            if (count > 0) {
                goto loop5;
            }
            result2 = sorted[i + 0x1C];
        }
        if (result2 != 0x78) {
            HSD_JObjClearFlagsAll(jobj, 0x10U);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10U);
        }
    } else {
        // Fighter mode - check if 7 more rows exist
        count = 7;
        i = data->fighter_cursor_pos >> 8;
        ptr = sorted + i;
    loop7:
        if (count == 0) {
            result2 = sorted[i];
        } else {
            ptr2 = ptr;
        loop8:
            i++;
            ptr2++;
            ptr++;
            if (i >= 0x19) {
                result2 = 0x19;
            } else if (mn_IsFighterUnlocked(*ptr2) == 0) {
                goto loop8;
            } else {
                count--;
                if (count >= 0) {
                    goto loop7;
                }
            }
        }
        if (result2 != 0x19) {
            HSD_JObjClearFlagsAll(jobj, 0x10U);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10U);
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
    mnDiagram_UpdateScrollArrows(gobj);
    jobj = data->jobj;
    table = mnDiagram_803EE774;
    if (mn_8022ED6C(jobj, (AnimLoopSettings*) table) >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}

/// @brief Sets initial scroll arrow visibility based on total entry count.
/// @details Called once after intro animation. Sets visibility for:
///          - jobjs[7]/[8]: Hidden if count <= 7 (unknown visual elements)
///          - jobjs[5]/[6]: Hidden if count <= 10 (left/down arrows)
///          Note: jobjs[5]/[6] are also updated every frame by mnDiagram_802417D0
///          based on scroll position, which overrides this initial setting.
/// @param gobj The diagram GObj containing arrow JObjs in user_data.
/// @param count Number of entries (fighters or names) to display.
void mnDiagram_UpdateScrollArrowVisibility(void* gobj, int count)
{
    void* data = ((HSD_GObj*) gobj)->user_data;
    PAD_STACK(8);
    if (count <= 7) {
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[7], 0x10U);
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[8], 0x10U);
    } else {
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[7], 0x10U);
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[8], 0x10U);
    }
    if (count <= 10) {
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[6], 0x10U);
        HSD_JObjSetFlagsAll(((HSD_JObj**) data)[5], 0x10U);
    } else {
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[6], 0x10U);
        HSD_JObjClearFlagsAll(((HSD_JObj**) data)[5], 0x10U);
    }
}

void mnDiagram_OnFrame(HSD_GObj* gobj)
{
    Diagram* data = gobj->user_data;
    Diagram* data2;
    HSD_GObjProc* proc;
    u8 col_idx;
    s32 row_idx;
    int count;
    PAD_STACK(0x28);

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        if (mn_804A04F0.cur_menu == 0x1E) {
            mnDiagram_ClearGridContent(gobj);
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(gobj, mnDiagram_ExitAnimProc, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);
        mnDiagram_ClearGridContent(gobj);
        return;
    }

    if (data->anim_state == 1) {
        if (mn_8022ED6C(data->jobjs[1], &mnDiagram_803EE768) >=
            mnDiagram_803EE768.end_frame)
        {
            HSD_JObjClearFlagsAll(data->jobjs[2], 0x10);
            data->anim_state = 0;
            mnDiagram_CreateCursor();
            if (data->is_name_mode != 0) {
                u16 indices = data->name_cursor_pos;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_ClearGridContent(gobj);
                mnDiagram_DrawGridCells(gobj, col_idx, row_idx,
                                        (u8) (data2->is_name_mode == 1));
                if (data2->is_name_mode == 0) {
                    mnDiagram_DrawFighterHeaders(gobj, col_idx, row_idx);
                } else {
                    mnDiagram_DrawNameHeaders(gobj, col_idx, row_idx);
                }
            } else {
                u16 indices = data->fighter_cursor_pos;
                data2 = gobj->user_data;
                row_idx = indices >> 8;
                col_idx = (u8) indices;
                mnDiagram_ClearGridContent(gobj);
                mnDiagram_DrawGridCells(gobj, col_idx, row_idx,
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
                count = mnDiagram_CountUnlockedFighters();
            }
            mnDiagram_UpdateScrollArrowVisibility(gobj, count);
        } else {
            HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);
        }
    }
    mnDiagram_UpdateScrollArrows(gobj);
}

/// @brief Draws a number at a specific grid cell position.
/// @param gobj The diagram GObj.
/// @param col Column position in grid.
/// @param row Row position in grid.
/// @param value The number value to display.
void mnDiagram_DrawCellNumber(void* gobj, u8 col, u8 row, s32 value)
{
    Diagram* data;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    void** joint_data;
    s32 digit_count;
    s32 digit;
    s32 i;
    f32 x_spacing;
    f32 y_spacing;
    f32 y_offset;
    f32 base;
    f32 row_offset;
    f32 col_offset;
    f32 row_offset_adj;

    data = ((HSD_GObj*) gobj)->user_data;
    jobj = data->jobjs[11];
    jobj2 = data->jobjs[12];
    base = HSD_JObjGetTranslationX(jobj);
    x_spacing = HSD_JObjGetTranslationX(jobj2) - base;

    jobj = data->jobjs[7];
    jobj2 = data->jobjs[8];
    base = HSD_JObjGetTranslationX(jobj);
    y_spacing = HSD_JObjGetTranslationX(jobj2) - base;

    jobj = data->jobjs[9];
    jobj2 = data->jobjs[10];
    base = HSD_JObjGetTranslationY(jobj);
    y_offset = HSD_JObjGetTranslationY(jobj2) - base;

    digit_count = mn_GetDigitCount(value);
    row_offset = y_offset * (f32) row;
    col_offset = y_spacing * (f32) col;
    row_offset_adj = row_offset - 1.0f;

    joint_data = mnDiagram_804A07F4;
    for (i = 0; i < digit_count; i++) {
        digit = mn_GetDigitAt(value, i);
        jobj = HSD_JObjLoadJoint(joint_data[0]);
        HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
        HSD_JObjReqAnimAll(jobj, (f32) digit);
        HSD_JObjAnimAll(jobj);
        if (col < 7) {
            HSD_JObjSetTranslateX(jobj, (x_spacing * (f32) i) + col_offset);
        } else {
            HSD_JObjSetTranslateX(jobj,
                                  (x_spacing * (f32) i) + col_offset + 1.0f);
        }
        if (row < 10) {
            HSD_JObjSetTranslateY(jobj, row_offset);
        } else {
            HSD_JObjSetTranslateY(jobj, row_offset_adj);
        }
        HSD_JObjAddChild(data->jobjs[11], jobj);
    }
}

/// @brief Draws all visible KO values in the grid cells.
/// @param gobj The diagram GObj.
/// @param col_offset Column scroll offset.
/// @param row_offset Row scroll offset.
/// @param is_name_mode 1 for name mode, 0 for fighter mode.
void mnDiagram_DrawGridCells(void* arg0, s32 arg1, s32 arg2, u8 arg3)
{
    register void* gobj = arg0;
    register s32 col_offset = arg1;
    register s32 row_offset = arg2;
    register u8 is_name = arg3;
    register u8* base = (u8*) &mnDiagram_804A0750;
    register s32 cap = 0xF423F;
    s32 var_r16_6;
    s32 var_r17_10;
    s32 var_r17_11;
    s32 var_r17_5;
    s32 var_r17_7;
    s32 var_r17_8;
    s32 var_r17_9;
    s32 var_r18;
    s32 var_r18_10;
    s32 var_r18_11;
    s32 var_r18_12;
    s32 var_r18_3;
    s32 var_r18_4;
    s32 var_r18_5;
    s32 var_r18_6;
    s32 var_r18_8;
    s32 var_r18_9;
    s32 var_r19;
    s32 var_r19_2;
    s32 var_r19_3;
    s32 var_r19_4;
    s32 var_r19_6;
    s32 var_r22;
    s32 var_r22_2;
    s32 var_r22_3;
    s32 var_r30;
    s32 var_r3;
    s32 var_r17_4;
    s32 var_r19_5;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r17_6;
    u8 var_r18_2;
    u8 var_r18_7;
    u8 var_r21;
    u8 var_r23;
    u8 var_r24;
    u8* var_r15;
    u8* var_r15_2;
    u8* var_r15_3;
    u8* var_r16;
    u8* var_r16_2;
    u8* var_r16_3;
    u8* var_r16_4;
    u8* var_r16_5;
    u8* var_r16_7;
    u8* var_r17;
    u8* var_r17_2;
    u8* var_r17_3;

    var_r30 = 0;
    do {
        if (var_r30 == 0xA) {
            var_r22 = 0;
            do {
                if (is_name != 0) {
                    var_r3 = GetNameCount();
                    if (var_r3 > var_r22) {
                        var_r18 = var_r22;
                        var_r19 = row_offset;
                        var_r16 = base + row_offset + 0x1C;
                    loop_11:
                        if (var_r18 <= 0) {
                            var_r0 = *(base + var_r19 + 0x1C);
                        } else {
                            var_r17 = var_r16;
                        loop_7:
                            var_r19 += 1;
                            var_r17 += 1;
                            var_r16 += 1;
                            if (var_r19 >= 0x78) {
                                var_r0 = 0x78;
                            } else {
                                if (GetNameText((s32) *var_r17) != NULL) {
                                    var_r18 -= 1;
                                    goto loop_11;
                                }
                                goto loop_7;
                            }
                        }
                        var_r19_2 = 0;
                        var_r18_2 = 0;
                        do {
                            if (GetNameText((s32) var_r18_2) != NULL) {
                                var_r19_2 +=
                                    GetPersistentNameData((u8) var_r18_2)
                                        ->vs_kos[var_r0];
                            }
                            var_r18_2 += 1;
                        } while ((s32) var_r18_2 < 0x78);
                        if (var_r19_2 > cap) {
                            var_r19_2 = cap;
                        }
                        mnDiagram_DrawCellNumber(gobj, (u8) var_r22,
                                                 (u8) var_r30, var_r19_2);
                    }
                } else {
                    var_r18_3 = 0;
                    var_r19_3 = 0;
                    do {
                        var_r3 = mn_IsFighterUnlocked(var_r19_3);
                        if (var_r3 != 0) {
                            var_r18_3 += 1;
                        }
                        var_r19_3 += 1;
                    } while (var_r19_3 < 0x19);
                    if (var_r18_3 > var_r22) {
                        var_r19_4 = var_r22;
                        var_r18_4 = row_offset;
                        var_r17_2 = base + row_offset;
                    loop_33:
                        if (var_r19_4 >= 0) {
                            if (var_r19_4 == 0) {
                                var_r21 = *(base + var_r18_4);
                            } else {
                                var_r16_2 = var_r17_2;
                            loop_29:
                                var_r18_4 += 1;
                                var_r16_2 += 1;
                                var_r17_2 += 1;
                                if (var_r18_4 >= 0x19) {
                                    var_r21 = 0x19;
                                } else {
                                    if (mn_IsFighterUnlocked(
                                            (s32) *var_r16_2) != 0)
                                    {
                                        var_r19_4 -= 1;
                                        goto loop_33;
                                    }
                                    goto loop_29;
                                }
                            }
                        }
                        var_r19_5 = 0;
                        var_r18_5 = 0;
                        do {
                            if (mn_IsFighterUnlocked(var_r18_5) != 0) {
                                var_r19_5 +=
                                    GetPersistentFighterData((u8) var_r18_5)
                                        ->fighter_kos[var_r21];
                            }
                            var_r18_5 += 1;
                        } while (var_r18_5 < 0x19);
                        mnDiagram_DrawCellNumber(gobj, (u8) var_r22,
                                                 (u8) var_r30, var_r19_5);
                    }
                }
                var_r22 += 1;
            } while (var_r22 < 7);
        } else if (is_name != 0) {
            var_r3 = GetNameCount();
            if (var_r3 > var_r30) {
                var_r22_2 = 0;
                do {
                    if ((var_r22_2 == 7) ||
                        (var_r3 = GetNameCount(), (var_r3 > var_r22_2)))
                    {
                        var_r19_6 = var_r30;
                        var_r18_6 = col_offset;
                        var_r17_3 = base + col_offset + 0x1C;
                    loop_52:
                        if (var_r19_6 <= 0) {
                            var_r0_2 = *(base + var_r18_6 + 0x1C);
                        } else {
                            var_r16_3 = var_r17_3;
                        loop_48:
                            var_r18_6 += 1;
                            var_r16_3 += 1;
                            var_r17_3 += 1;
                            if (var_r18_6 >= 0x78) {
                                var_r0_2 = 0x78;
                            } else {
                                if (GetNameText((s32) *var_r16_3) != NULL) {
                                    var_r19_6 -= 1;
                                    goto loop_52;
                                }
                                goto loop_48;
                            }
                        }
                        if (var_r22_2 == 7) {
                            var_r17_4 = 0;
                            var_r18_7 = 0;
                            do {
                                if (GetNameText((s32) var_r18_7) != NULL) {
                                    var_r17_4 +=
                                        GetPersistentNameData((u8) var_r0_2)
                                            ->vs_kos[var_r18_7];
                                }
                                var_r18_7 += 1;
                            } while ((s32) var_r18_7 < 0x78);
                            mnDiagram_DrawCellNumber(gobj, (u8) var_r22_2,
                                                     (u8) var_r30, var_r17_4);
                        } else {
                            var_r18_8 = var_r22_2;
                            var_r17_5 = row_offset;
                            var_r15 = base + row_offset + 0x1C;
                        loop_66:
                            if (var_r18_8 <= 0) {
                                var_r17_6 = *(base + var_r17_5 + 0x1C);
                            } else {
                                var_r16_4 = var_r15;
                            loop_62:
                                var_r17_5 += 1;
                                var_r16_4 += 1;
                                var_r15 += 1;
                                if (var_r17_5 >= 0x78) {
                                    var_r17_6 = 0x78;
                                } else {
                                    if (GetNameText((s32) *var_r16_4) != NULL)
                                    {
                                        var_r18_8 -= 1;
                                        goto loop_66;
                                    }
                                    goto loop_62;
                                }
                            }
                            mnDiagram_DrawCellNumber(
                                gobj, (u8) var_r22_2, (u8) var_r30,
                                GetPersistentNameData((u8) var_r0_2)
                                    ->vs_kos[var_r17_6]);
                        }
                    }
                    var_r22_2 += 1;
                } while (var_r22_2 <= 7);
            }
        } else {
            var_r17_7 = 0;
            var_r18_9 = 0;
            do {
                var_r3 = mn_IsFighterUnlocked(var_r18_9);
                if (var_r3 != 0) {
                    var_r17_7 += 1;
                }
                var_r18_9 += 1;
            } while (var_r18_9 < 0x19);
            if (var_r17_7 > var_r30) {
                var_r22_3 = 0;
                do {
                    if (var_r22_3 != 7) {
                        var_r17_8 = 0;
                        var_r18_10 = 0;
                        do {
                            var_r3 = mn_IsFighterUnlocked(var_r18_10);
                            if (var_r3 != 0) {
                                var_r17_8 += 1;
                            }
                            var_r18_10 += 1;
                        } while (var_r18_10 < 0x19);
                        if (var_r17_8 > var_r22_3) {
                            goto block_83;
                        }
                    } else {
                    block_83:
                        var_r18_11 = var_r30;
                        var_r17_9 = col_offset;
                        var_r16_5 = base + col_offset;
                    loop_91:
                        if (var_r18_11 >= 0) {
                            if (var_r18_11 == 0) {
                                var_r23 = *(base + var_r17_9);
                            } else {
                                var_r15_2 = var_r16_5;
                            loop_87:
                                var_r17_9 += 1;
                                var_r15_2 += 1;
                                var_r16_5 += 1;
                                if (var_r17_9 >= 0x19) {
                                    var_r23 = 0x19;
                                } else {
                                    if (mn_IsFighterUnlocked(
                                            (s32) *var_r15_2) != 0)
                                    {
                                        var_r18_11 -= 1;
                                        goto loop_91;
                                    }
                                    goto loop_87;
                                }
                            }
                        }
                        if (var_r22_3 == 7) {
                            var_r16_6 = 0;
                            var_r17_10 = 0;
                            do {
                                if (mn_IsFighterUnlocked(var_r17_10) != 0) {
                                    var_r16_6 +=
                                        GetPersistentFighterData((u8) var_r23)
                                            ->fighter_kos[var_r17_10];
                                }
                                var_r17_10 += 1;
                            } while (var_r17_10 < 0x19);
                            if (var_r16_6 > cap) {
                                var_r16_6 = cap;
                            }
                            mnDiagram_DrawCellNumber(gobj, (u8) var_r22_3,
                                                     (u8) var_r30, var_r16_6);
                        } else {
                            var_r18_12 = var_r22_3;
                            var_r17_11 = row_offset;
                            var_r16_7 = base + row_offset;
                        loop_108:
                            if (var_r18_12 >= 0) {
                                if (var_r18_12 == 0) {
                                    var_r24 = *(base + var_r17_11);
                                } else {
                                    var_r15_3 = var_r16_7;
                                loop_104:
                                    var_r17_11 += 1;
                                    var_r15_3 += 1;
                                    var_r16_7 += 1;
                                    if (var_r17_11 >= 0x19) {
                                        var_r24 = 0x19;
                                    } else {
                                        if (mn_IsFighterUnlocked(
                                                (s32) *var_r15_3) != 0)
                                        {
                                            var_r18_12 -= 1;
                                            goto loop_108;
                                        }
                                        goto loop_104;
                                    }
                                }
                            }
                            mnDiagram_DrawCellNumber(
                                gobj, (u8) var_r22_3, (u8) var_r30,
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

/// @brief Draws name text for row and column headers.
/// @param gobj The diagram GObj.
/// @param col_offset Column scroll offset.
/// @param row_offset Row scroll offset.
void mnDiagram_DrawNameHeaders(void* gobj, s32 col_offset, s32 row_offset)
{
    Diagram* data = ((HSD_GObj*) gobj)->user_data;
    HSD_Text* text;
    int i;
    int count;
    u8 name_id;
    f32 x_spacing;
    f32 y_spacing;

    // Column headers
    text = HSD_SisLib_803A6754(0, 1);
    data->col_header_text = text;
    text->font_size.x = 0.02f;
    text->font_size.y = 0.03f;

    x_spacing = 1.0f;
    if (data->jobjs[9] != NULL && data->jobjs[10] != NULL) {
        x_spacing = data->jobjs[10]->translate.x - data->jobjs[9]->translate.x;
    }
    if (data->jobjs[9] != NULL) {
        text->pos_x = data->jobjs[9]->translate.x - 1.3f;
        text->pos_y = -data->jobjs[9]->translate.y - 0.5f;
        text->pos_z = data->jobjs[9]->translate.z;
    }

    count = GetNameCount();
    for (i = 0; i < 7; i++) {
        if (count > i) {
            name_id = mnDiagram_804A076C.sorted_names[row_offset + i];
            HSD_SisLib_803A6B98(text, (x_spacing * (f32) i) / 0.02f, 0.0f,
                                GetNameText(name_id));
        }
    }

    // Row headers
    text = HSD_SisLib_803A6754(0, 1);
    data->row_header_text = text;
    text->font_size.x = 0.02f;
    text->font_size.y = 0.03f;

    y_spacing = 1.0f;
    if (data->jobjs[11] != NULL && data->jobjs[12] != NULL) {
        y_spacing =
            data->jobjs[12]->translate.y - data->jobjs[11]->translate.y;
    }
    if (data->jobjs[11] != NULL) {
        text->pos_x = data->jobjs[11]->translate.x - 1.3f;
        text->pos_y = -data->jobjs[11]->translate.y - 0.5f;
        text->pos_z = data->jobjs[11]->translate.z;
    }

    for (i = 0; i < 0xA; i++) {
        if (count > i) {
            name_id = mnDiagram_804A076C.sorted_names[col_offset + i];
            HSD_SisLib_803A6B98(text, 0.0f, -((y_spacing * (f32) i) / 0.03f),
                                GetNameText(name_id));
        }
    }
}

/// @brief Creates a fighter icon JObj.
/// @param row_idx Fighter index (internal character ID).
/// @param mode Animation mode (0 or 1).
/// @return The created fighter icon JObj.
HSD_JObj* mnDiagram_CreateFighterIcon(int row_idx, int mode)
{
    HSD_JObj* sp10;
    void** joint_data = mnDiagram_804A0804;
    HSD_JObj* temp_r3;
    f32 var_f1;

    temp_r3 = HSD_JObjLoadJoint(joint_data[0]);
    HSD_JObjAddAnimAll(temp_r3, joint_data[1], joint_data[2], joint_data[3]);
    if (mode != 0) {
        var_f1 = 1.0f;
    } else {
        var_f1 = 0.0f;
    }
    HSD_JObjReqAnimAll(temp_r3, var_f1);
    HSD_JObjAnimAll(temp_r3);
    lb_80011E24(temp_r3, &sp10, 2, -1);
    HSD_JObjReqAnimAll(sp10, row_idx);
    HSD_JObjAnimAll(sp10);
    return temp_r3;
}

/// @brief Draws fighter icons for row and column headers.
/// @param gobj The diagram GObj.
/// @param col_offset Column scroll offset.
/// @param row_offset Row scroll offset.
void mnDiagram_DrawFighterHeaders(void* gobj, int col_offset, int row_offset)
{
    Diagram* data = ((HSD_GObj*) gobj)->user_data;
    void** joint_data;
    HSD_JObj* jobj;
    HSD_JObj* sp_jobj;
    int i;
    int count;
    u8 fighter_id;
    f32 x_spacing;
    f32 y_spacing;

    joint_data = (void**) &mnDiagram_804A0834;

    // Column headers (fighter icons)
    for (i = 0; i < 7; i++) {
        count = mnDiagram_CountUnlockedFighters();
        if (count > i) {
            fighter_id = mnDiagram_804A0750.sorted_fighters[row_offset + i];
            jobj = HSD_JObjLoadJoint(joint_data[0]);
            HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2],
                               joint_data[3]);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            lb_80011E24(jobj, &sp_jobj, 2, -1);
            HSD_JObjReqAnimAll(sp_jobj, (f32) fighter_id);
            HSD_JObjAnimAll(sp_jobj);

            if (data->jobjs[9] != NULL && data->jobjs[10] != NULL) {
                x_spacing =
                    data->jobjs[10]->translate.x - data->jobjs[9]->translate.x;
                HSD_JObjSetTranslateX(jobj, x_spacing * (f32) i);
            }
            HSD_JObjAddChild(data->jobjs[9], jobj);
        }
    }

    // Row headers (fighter icons)
    for (i = 0; i < 0xA; i++) {
        count = mnDiagram_CountUnlockedFighters();
        if (count > i) {
            fighter_id = mnDiagram_804A0750.sorted_fighters[col_offset + i];
            jobj = HSD_JObjLoadJoint(joint_data[0]);
            HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2],
                               joint_data[3]);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            lb_80011E24(jobj, &sp_jobj, 2, -1);
            HSD_JObjReqAnimAll(sp_jobj, (f32) fighter_id);
            HSD_JObjAnimAll(sp_jobj);

            if (data->jobjs[11] != NULL && data->jobjs[12] != NULL) {
                y_spacing = data->jobjs[12]->translate.y -
                            data->jobjs[11]->translate.y;
                HSD_JObjSetTranslateY(jobj, y_spacing * (f32) i);
            }
            HSD_JObjAddChild(data->jobjs[11], jobj);
        }
    }
}

void mnDiagram_CursorProc(HSD_GObj* gobj)
{
    Diagram* data;
    HSD_JObj* sp_jobj;
    int col;
    int row;
    f32 x_spacing;
    f32 y_spacing;
    f32 x_pos;
    f32 y_pos;

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        HSD_GObjPLink_80390228(gobj);
        return;
    }

    data = mnDiagram_804D6C10->user_data;
    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 3, -1);

    col = mn_804A04F0.hovered_selection >> 8;
    if (data->jobjs[9] != NULL && data->jobjs[10] != NULL) {
        x_spacing = data->jobjs[10]->translate.x - data->jobjs[9]->translate.x;
        x_pos = x_spacing * (f32) (col - 3);
        HSD_JObjSetTranslateX(sp_jobj, x_pos);
    }

    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 4, -1);
    row = (u8) mn_804A04F0.hovered_selection;
    if (data->jobjs[11] != NULL && data->jobjs[12] != NULL) {
        y_spacing =
            data->jobjs[12]->translate.y - data->jobjs[11]->translate.y;
        y_pos = (y_spacing * ((f32) row - 4.5f)) - 0.1f;
        HSD_JObjSetTranslateY(sp_jobj, y_pos);
    }

    lb_80011E24((HSD_JObj*) gobj->hsd_obj, &sp_jobj, 2, -1);
    HSD_JObjSetTranslateX(sp_jobj, x_pos);
    HSD_JObjSetTranslateY(sp_jobj, y_pos);
}

/// @brief Creates the cursor GObj for the diagram screen.
void mnDiagram_CreateCursor(void)
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
    HSD_GObjProc_8038FD54(gobj, mnDiagram_CursorProc, 0);
}

/// @brief Sets up the main diagram GObj and initializes state.
/// @param anim_state Animation state (0 = normal, 1 = intro animation).
void mnDiagram_Setup(u8 anim_state)
{
    HSD_GObj* gobj;
    HSD_GObj* cursor_gobj;
    HSD_JObj* jobj;
    Diagram* data;
    void** joint_data;
    HSD_GObjProc* proc;
    int i;
    int count;
    u16 indices;
    u8 col_idx;
    u8 row_idx;

    joint_data = (void**) &mnDiagram_804A0824;
    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram_804D6C10 = gobj;
    jobj = HSD_JObjLoadJoint(joint_data[0]);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, joint_data[1], joint_data[2], joint_data[3]);
    HSD_JObjReqAnimAll(jobj, 0.0f);

    data = HSD_MemAlloc(sizeof(Diagram));
    data->saved_menu = mn_804A04F0.cur_menu;
    data->saved_selection = mn_804A04F0.hovered_selection;
    data->anim_state = anim_state;
    data->fighter_cursor_pos = 0;
    data->name_cursor_pos = 0;
    data->popup_gobj = NULL;
    data->col_header_text = NULL;
    data->row_header_text = NULL;

    if (GetNameCount() != 0) {
        data->is_name_mode = gmMainLib_8015CC34()->xD;
    } else {
        gmMainLib_8015CC34()->xD = 0;
        data->is_name_mode = 0;
    }

    GObj_InitUserData(gobj, 0, HSD_Free, data);

    for (i = 0; i < 13; i++) {
        lb_80011E24(jobj, &data->jobjs[i], i, -1);
    }

    proc = HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) mnDiagram_OnFrame,
                                 0);

    if (anim_state == 0) {
        HSD_JObjReqAnimAll(data->jobjs[3], 9.0f);
        HSD_JObjAnimAll(data->jobjs[3]);

        cursor_gobj = GObj_Create(6, 7, 0x80);
        HSD_GObjObject_80390A70(
            cursor_gobj, HSD_GObj_804D7849,
            HSD_JObjLoadJoint((HSD_Joint*) mnDiagram_804A0814));
        GObj_SetupGXLink(cursor_gobj, HSD_GObj_JObjCallback, 4, 0x80);
        HSD_GObjProc_8038FD54(cursor_gobj, mnDiagram_CursorProc, 0);

        if (data->is_name_mode != 0) {
            count = GetNameCount();
        } else {
            count = mnDiagram_CountUnlockedFighters();
        }

        if (count <= 7) {
            HSD_JObjSetFlagsAll(data->jobjs[7], 0x10);
            HSD_JObjSetFlagsAll(data->jobjs[8], 0x10);
        } else {
            HSD_JObjClearFlagsAll(data->jobjs[7], 0x10);
            HSD_JObjClearFlagsAll(data->jobjs[8], 0x10);
        }

        if (count <= 0xA) {
            HSD_JObjSetFlagsAll(data->jobjs[6], 0x10);
            HSD_JObjSetFlagsAll(data->jobjs[5], 0x10);
        } else {
            HSD_JObjClearFlagsAll(data->jobjs[6], 0x10);
            HSD_JObjClearFlagsAll(data->jobjs[5], 0x10);
        }

        if (data->is_name_mode != 0) {
            indices = data->name_cursor_pos;
            col_idx = (u8) indices;
            row_idx = indices >> 8;
            mnDiagram_ClearGridContent(gobj);
            mnDiagram_DrawGridCells(gobj, col_idx, row_idx, 1);
            mnDiagram_DrawNameHeaders(gobj, col_idx, row_idx);
        } else {
            indices = data->fighter_cursor_pos;
            col_idx = (u8) indices;
            row_idx = indices >> 8;
            mnDiagram_ClearGridContent(gobj);
            mnDiagram_DrawGridCells(gobj, col_idx, row_idx, 0);
            mnDiagram_DrawFighterHeaders(gobj, col_idx, row_idx);
        }
    }
}

/// @brief Initializes the VS Records diagram screen.
/// @param load_dat If non-zero, load DAT archive symbols.
/// @param anim_state Initial animation state (0 = normal, 1 = intro).
void mnDiagram_Init(s32 load_dat, s32 anim_state)
{
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1E;
    mn_804A04F0.x10 = 0;
    mn_804A04F0.hovered_selection = 0;

    if (load_dat) {
        lbArchive_LoadSections(
            mn_804D6BB8, &assets->ConB1[0], "MenMainConB1_Top_joint",
            &assets->ConB1[1], "MenMainConB1_Top_animjoint", &assets->ConB1[2],
            "MenMainConB1_Top_matanim_joint", &assets->ConB1[3],
            "MenMainConB1_Top_shapeanim_joint", &assets->CursorB1_FaceB[0],
            "MenMainCursorB1_Top_joint", &assets->CursorB1_FaceB[1],
            "MenMainFaceB_Top_joint", &assets->CursorB1_FaceB[2],
            "MenMainFaceB_Top_animjoint", &assets->CursorB1_FaceB[3],
            "MenMainFaceB_Top_matanim_joint", &assets->FaceB_NmB[0],
            "MenMainFaceB_Top_shapeanim_joint", &assets->FaceB_NmB[1],
            "MenMainNmB_Top_joint", &assets->FaceB_NmB[2],
            "MenMainNmB_Top_animjoint", &assets->FaceB_NmB[3],
            "MenMainNmB_Top_matanim_joint", &assets->NmB_shape[0],
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

    mnDiagram_SortFightersByKOs();
    mnDiagram_SortNamesByKOs();
    mnDiagram_Setup(anim_state);

    proc = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                 (void (*)(HSD_GObj*)) mnDiagram_InputProc, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
