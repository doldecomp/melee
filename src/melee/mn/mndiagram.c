#include "mndiagram.static.h"

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

/// Archive asset pointers struct (for mnDiagram_802437E8)
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

/// Main user data struct for VS Records diagram (0x50 bytes)
typedef struct mnDiagram_Data {
    /* 0x00 */ u8 saved_menu; ///< Saved menu ID on entry
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 saved_selection; ///< Saved hovered selection on entry
    /* 0x04 */ u8 anim_state;       ///< 0 = idle, 1 = intro anim playing
    /* 0x05 */ u8 pad_5[3];
    /* 0x08 */ HSD_JObj* jobjs[13]; ///< JObj references, filled by lb_80011E24
    /* 0x3C */ u16
        fighter_cursor_pos;          ///< Fighter mode cursor (row << 8 | col)
    /* 0x3E */ u16 name_cursor_pos;  ///< Name mode cursor (row << 8 | col)
    /* 0x40 */ HSD_GObj* popup_gobj; ///< Popup window GObj (or NULL)
    /* 0x44 */ u8 is_name_mode;      ///< 0 = fighter mode, 1 = name mode
    /* 0x45 */ u8 pad_45[3];
    /* 0x48 */ HSD_Text* col_header_text; ///< Column header text object
    /* 0x4C */ HSD_Text* row_header_text; ///< Row header text object
} mnDiagram_Data;
STATIC_ASSERT(sizeof(mnDiagram_Data) == 0x50);

/// User data structure for mnDiagram_PopupCleanup callback.
/// Overlay of mnDiagram_PopupData - only accesses text array.
typedef struct mnDiagram_CleanupData {
    /* 0x00 */ char jobjs_reserved[0x38]; ///< JObj array (unused by cleanup)
    /* 0x38 */ HSD_Text* text[6];         ///< Text objects to free
} mnDiagram_CleanupData;

/// User data structure for mnDiagram_ExitAnimProc callback.
/// Overlay of mnDiagram_Data - only accesses jobj at offset 0x0C.
typedef struct mnDiagram_AnimData {
    /* 0x00 */ char header_reserved[0x0C]; ///< menu state (unused by anim)
    /* 0x0C */ HSD_JObj* jobj;             ///< JObj for exit animation
} mnDiagram_AnimData;

/// BSS variables - sorted player arrays
mnDiagram_804A0750_t mnDiagram_804A0750;
mnDiagram_804A076C_t mnDiagram_804A076C;

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
    s32 i;
    for (i = 0; i < 0x78; i++) {
        if (GetNameText(i) != NULL) {
            struct NameTagData* data = GetPersistentNameData(field_index);
            total += data->vs_kos[(u8) i];
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
int mnDiagram_GetNameTotalFalls(u8 field_index)
{
    int i;
    int total = 0;
    PAD_STACK(16);
    for (i = 0; i < 0x78; i++) {
        if (GetNameText(i) != 0) {
            struct NameTagData* data = GetPersistentNameData(i);
            total += data->vs_kos[field_index];
        }
    }
    if (total > 999999) {
        total = 999999;
    }
    return total;
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
    struct FighterData* data;
    for (i = 0; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            data = GetPersistentFighterData(field_index);
            total += data->fighter_kos[i];
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
int mnDiagram_GetFighterTotalFalls(u8 field_index)
{
    int i;
    int total = 0;
    struct FighterData* data;
    PAD_STACK(16);
    for (i = 0; i < 0x19; i++) {
        if (mn_IsFighterUnlocked(i) != 0) {
            data = GetPersistentFighterData(i);
            total += data->fighter_kos[field_index];
        }
    }
    return total;
}

/// @brief Formats a number with optional decimal places.
/// @param buf Output buffer for the string.
/// @param val The value to format (treat last decimal_places digits as
/// decimal).
/// @param decimal_places Number of decimal places (0 = integer only).
void mnDiagram_FormatDecimalNumber(char* buf, u32 val, int decimal_places)
{
    int digit_count;
    int i;
    char* ptr;
    u32 integer_part;

    integer_part = val / powi(10, decimal_places);
    digit_count = mn_GetDigitCount(integer_part);
    ptr = buf;
    i = 0;
    for (; i < digit_count; i++) {
        *ptr = mn_GetDigitAt(integer_part, (digit_count - 1) - i) + '0';
        ptr++;
    }
    if (decimal_places != 0) {
        int decimal_part;
        int j;
        buf[digit_count] = '.';
        digit_count++;
        decimal_part = val % powi(10, decimal_places);
        j = 0;
        for (; j < decimal_places; j++) {
            buf[digit_count] =
                mn_GetDigitAt(decimal_part, (decimal_places - 1) - j) + '0';
            digit_count++;
        }
    }
    buf[digit_count] = mnDiagram_804D4FA4;
}

/// @brief Formats seconds as MM:SS string.
/// @param buf Output buffer for the string.
/// @param seconds Time in seconds.
void mnDiagram_FormatTime(char* buf, u32 seconds)
{
    int digit_count;
    int last;
    char* ptr;
    int i;
    u32 minutes;

    minutes = seconds / 60;
    digit_count = mn_GetDigitCount(minutes);
    ptr = buf;
    last = digit_count - 1;
    i = 0;
    for (; i < digit_count; i++) {
        *ptr = mn_GetDigitAt(minutes, last - i) + '0';
        ptr++;
    }
    buf[digit_count] = ':';
    digit_count++;
    buf[digit_count] = ((seconds % 60) / 10) + '0';
    buf[digit_count + 1] = ((seconds % 60) % 10) + '0';
    buf[digit_count + 2] = mnDiagram_804D4FA4;
}

/// @brief Converts a number to a null-terminated string.
/// @param buf Output buffer for the string.
/// @param val The number to convert.
void mnDiagram_IntToStr(char* buf, u32 val)
{
    int digit_count;
    int last;
    char* ptr;
    int i;

    digit_count = mn_GetDigitCount(val);
    ptr = buf;
    last = digit_count - 1;
    i = 0;
    while (i < digit_count) {
        *ptr = mn_GetDigitAt(val, last - i) + '0';
        i++;
        ptr++;
    }
    buf[digit_count] = mnDiagram_804D4FA4;
}

/// @brief Gets the previous valid name index.
/// @param idx Current name index.
/// @return Previous name index with a valid name, or original if none found.
u8 mnDiagram_GetPrevNameIndex(u8 idx)
{
    s32 original, i;

    original = i = idx;

    do {
        if (--i < 0) {
            return original;
        }
    } while ((u32) GetNameText(i) == 0);

    return i;
}

u8 mnDiagram_GetNextNameIndex(u8 idx)
{
    int i;
    u8 original;

    original = i = (int) idx;

    do {
        i++;
        if (i >= 0x78) {
            return original;
        }
    } while ((u32) GetNameText(i) == 0);

    return (u8) i;
}

/// @brief Gets the previous valid fighter index.
/// @param idx Current fighter index.
/// @return Previous fighter index that's unlocked, or original if none found.
u8 mnDiagram_GetPrevFighterIndex(u8 idx)
{
    int i;
    u8 original;
    u8* ptr;

    ptr = mnDiagram_804A0750.sorted_fighters + idx;
    i = idx;
    original = idx;
    do {
        i--;
        ptr--;
        if (i < 0) {
            return original;
        }
    } while (mn_IsFighterUnlocked(*ptr) == 0);
    return (u8) i;
}

u8 mnDiagram_GetNextFighterIndex(u8 idx)
{
    int i;
    u8 original;
    u8* ptr;

    ptr = mnDiagram_804A0750.sorted_fighters + idx;
    i = idx;
    original = idx;
    do {
        i++;
        ptr++;
        if (i >= 0x19) {
            return original;
        }
    } while (mn_IsFighterUnlocked(*ptr) == 0);
    return (u8) i;
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
    s32 fighter_id;
    u32 value;
} RankEntry;

int mnDiagram_GetRankedFighterForName(int rank, int name_idx,
                                      u32 (*func)(int, int))
{
    RankEntry entries[25];
    int i, j;
    int var_r0;

    // Check if all fighters have 0 play time
    i = 0;
    while (1) {
        if (GetPersistentNameData(name_idx)->play_time_by_fighter[i] != 0U) {
            var_r0 = 0;
            break;
        }
        i++;
        if (i >= 0x19) {
            var_r0 = 1;
            break;
        }
    }
    if (var_r0 != 0) {
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
        u8 fighter_id = (u8) entries[i].fighter_id;
        if (gm_80164840(gm_8016400C(fighter_id)) != 0) {
            if (rank != 0) {
                // Check for ties - skip fighters with same value
                for (j = i + 1; j < 0x19; j++) {
                    if (func(name_idx, (u8) entries[i].fighter_id) !=
                        func(name_idx, (u8) entries[j].fighter_id))
                    {
                        break;
                    }
                    i++;
                    if (rank != 0) {
                        rank--;
                    } else {
                        return 0x19;
                    }
                }
                rank--;
            } else {
                // rank == 0, check if value is non-zero and no tie
                if (func(name_idx, fighter_id) != 0U) {
                    if (i + 1 < 0x19) {
                        if (func(name_idx, fighter_id) ==
                            func(name_idx, (u8) entries[i + 1].fighter_id))
                        {
                            return 0x19;
                        }
                    }
                    return fighter_id;
                }
                return 0x19;
            }
        }
    }
    return 0x19;
}

u8 mnDiagram_GetLeastPlayedFighter(u8 name_idx)
{
    int var_r0;
    int var_r29;
    int var_r30_2;
    int var_r30;
    int var_r25;
    int var_r28;
    int var_r25_2;
    int var_r26;
    int var_r28_2;
    int var_r25_3;
    int var_r26_2;
    int var_r28_3;
    u32 temp_r29;
    u32 temp_r29_2;

    var_r29 = 0;
    var_r30_2 = 0;
    while (1) {
        if (GetPersistentNameData(name_idx)->play_time_by_fighter[var_r29] !=
            0U)
        {
            var_r0 = 0;
            break;
        }
        var_r29 += 1;
        var_r30_2 += 4;
        if (var_r29 >= 0x19) {
            var_r0 = 1;
            break;
        }
    }
    if (var_r0 != 0) {
        return 0x19U;
    }
    var_r30 = 0;
    var_r25 = 1;
    var_r28 = 4;
    do {
        if (mn_IsFighterUnlocked(var_r25) != 0) {
            temp_r29 =
                GetPersistentNameData(name_idx)->play_time_by_fighter[var_r25];
            if (GetPersistentNameData(name_idx)
                    ->play_time_by_fighter[var_r30] > temp_r29)
            {
                var_r30 = var_r25;
            }
        }
        var_r25 += 1;
        var_r28 += 4;
    } while (var_r25 < 0x19);
    var_r26 = 0;
    var_r28_2 = 0;
    var_r25_2 = 0;
    do {
        if (mn_IsFighterUnlocked(var_r26) != 0 &&
            GetPersistentNameData(name_idx)->play_time_by_fighter[var_r26] ==
                0U)
        {
            var_r25_2 += 1;
        }
        var_r26 += 1;
        var_r28_2 += 4;
    } while (var_r26 < 0x19);
    if (var_r25_2 >= 2) {
        return 0x19U;
    }
    var_r25_3 = 0;
    var_r26_2 = 0;
    var_r28_3 = 0;
    do {
        if (mn_IsFighterUnlocked(var_r26_2) != 0 && var_r26_2 != var_r30) {
            temp_r29_2 =
                GetPersistentNameData(name_idx)->play_time_by_fighter[var_r30];
            if (GetPersistentNameData(name_idx)
                    ->play_time_by_fighter[var_r26_2] == temp_r29_2)
            {
                var_r25_3 += 1;
            }
        }
        var_r26_2 += 1;
        var_r28_3 += 4;
    } while (var_r26_2 < 0x19);
    if (var_r25_3 != 0) {
        return 0x19U;
    }
    return (u8) var_r30;
}

static u8 mnDiagram_803EE74C[0x1C] = {
    8,    1,    6,    0x10, 0x11, 4,   2,   0xD, 0xB, 0,
    5,    0xC,  0xE,  0x12, 7,    0xF, 0xA, 9,   3,   0x15,
    0x18, 0x13, 0x14, 0x17, 0x16, 0,   0,   0,
};

void mnDiagram_8023FA6C(void)
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
            u8 temp = dst[max_idx];
            int k;
            for (k = max_idx; k > i; k--) {
                dst[k] = dst[k - 1];
            }
            dst[i] = temp;
        }
    }
}

void mnDiagram_8023FC28(void)
{
    u32 totals[0x78];
    int i, j;
    u8* dst = mnDiagram_804A076C.sorted_names;

    for (i = 0; i < 0x78; i++) {
        u32 total = 0;
        dst[i] = (u8) i;
        for (j = 0; j < 0x78; j++) {
            if (GetNameText(j) != NULL) {
                total += GetPersistentNameData(i)->vs_kos[j];
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
            u8 temp = dst[max_idx];
            int k;
            for (k = max_idx; k > i; k--) {
                dst[k] = dst[k - 1];
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
    mnDiagram_Data* data = mnDiagram_804D6C10->user_data;
    u32 input = mn_80229624(4);
    if (input & 0x20) {
        lbAudioAx_80024030(0);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) mnDiagram_InputProc,
                              0);
        HSD_GObjPLink_80390228(data->popup_gobj);
        data->popup_gobj = NULL;
    }
}

void mnDiagram_InputProc(HSD_GObj* gobj)
{
    mnDiagram_Data* data = mnDiagram_804D6C10->user_data;
    u32 input = mn_80229624(4);

    if (input & 0x10) {
        lbAudioAx_80024030(1);
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        HSD_GObjProc_8038FD54(
            gobj, (void (*)(HSD_GObj*)) mnDiagram_PopupInputProc, 0);
        if (data->is_name_mode != 0) {
            u8 col_idx = (u8) data->name_cursor_pos;
            u8 row_idx = data->name_cursor_pos >> 8;
            mnDiagram_80241310(col_idx, row_idx, 1);
        } else {
            u8 col_idx = (u8) data->fighter_cursor_pos;
            u8 row_idx = data->fighter_cursor_pos >> 8;
            mnDiagram_80241310(col_idx, row_idx, 0);
        }
        return;
    }
    if (input & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        gmMainLib_8015CC34()->xE = (u8) (data->fighter_cursor_pos >> 8);
        gmMainLib_8015CC34()->xF = (u8) data->fighter_cursor_pos;
        gmMainLib_8015CC34()->unk_x10 = (u8) (data->name_cursor_pos >> 8);
        gmMainLib_8015CC34()->x11 = (u8) data->name_cursor_pos;
        gmMainLib_8015CC34()->xD = data->is_name_mode;
        mn_80229894(0x1C, 0, 3);
        return;
    }
    if (input & 0xC0) {
        lbAudioAx_80024030(1);
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
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        data->is_name_mode = (data->is_name_mode == 0) ? 1 : 0;
        mnDiagram_UpdateScrollArrowVisibility(
            mnDiagram_804D6C10, mnDiagram_CountUnlockedFighters());
        if (data->is_name_mode != 0) {
            mnDiagram_80241730(mnDiagram_804D6C10, (u8) data->name_cursor_pos,
                               data->name_cursor_pos >> 8);
        } else {
            mnDiagram_80241730(mnDiagram_804D6C10,
                               (u8) data->fighter_cursor_pos,
                               data->fighter_cursor_pos >> 8);
        }
        return;
    }
    // D-pad navigation
    if (data->is_name_mode != 0) {
        if (input & 1) {
            lbAudioAx_80024030(2);
        } else if (input & 2) {
            lbAudioAx_80024030(2);
        } else if (input & 4) {
            lbAudioAx_80024030(2);
        } else if (input & 8) {
            lbAudioAx_80024030(2);
        }
    } else {
        if (input & 1) {
            lbAudioAx_80024030(2);
        } else if (input & 2) {
            lbAudioAx_80024030(2);
        } else if (input & 4) {
            lbAudioAx_80024030(2);
        } else if (input & 8) {
            lbAudioAx_80024030(2);
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

static Point3d mnDiagram_803EE728[3] = {
    { 4.0f, 1.0f, 0.0f },
    { -3.0f, 0.8f, 0.0f },
    { -1.0f, 0.7f, 0.0f },
};
static s32 mnDiagram_804D4FA0 = 0xFF;

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

void mnDiagram_80240D94(void* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    mnDiagram_PopupData* data = ((HSD_GObj*) arg0)->user_data;
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

    if (arg3 != 0) {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText(arg1));
    } else {
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "Fighter");
    }

    if ((arg3 != 0) && (arg1 != arg2)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[2] = text;
        lb_8000B1CC(data->jobjs[10], &mnDiagram_803EE728[2], &pos);
        text->font_size.x = 0.035f;
        text->font_size.y = 0.05f;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;
        text->default_alignment = 1;
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) arg2));

        text = HSD_SisLib_803A6754(0, 1);
        data->text[4] = text;
        lb_8000B1CC(data->jobjs[2], &mnDiagram_803EE728[2], &pos);
        text->font_size.x = 0.035f;
        text->font_size.y = 0.05f;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;
        text->default_alignment = 1;
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText((u8) arg2));
    }

    if ((arg3 == 0) || (arg1 != arg2)) {
        text = HSD_SisLib_803A6754(0, 1);
        data->text[1] = text;
        lb_8000B1CC(data->jobjs[11], &mnDiagram_803EE728[1], &pos);
        text->font_size.x = 0.0521f;
        text->font_size.y = 0.0521f;
        text->default_alignment = 1;
        text->pos_x = pos.x;
        text->pos_y = -pos.y;
        text->pos_z = pos.z;

        if (arg3 != 0) {
            kos = GetPersistentNameData(arg1)->vs_kos[arg2];
        } else {
            kos = GetPersistentFighterData(arg1)->fighter_kos[arg2];
        }
        mnDiagram_IntToStr(buf, kos);
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, buf);
    }

    text = HSD_SisLib_803A6754(0, 1);
    data->text[3] = text;
    if (arg1 == arg2) {
        lb_8000B1CC(data->jobjs[13], &mnDiagram_803EE728[1], &pos);
        if (arg3 != 0) {
            sd_count = GetPersistentNameData(arg1)->sd_count;
        } else {
            sd_count = GetPersistentFighterData(arg1)->sd_count;
        }
        mnDiagram_IntToStr(buf, sd_count);
    } else {
        lb_8000B1CC(data->jobjs[3], &mnDiagram_803EE728[1], &pos);
        if (arg3 != 0) {
            kos = GetPersistentNameData((u8) arg2)->vs_kos[arg1];
        } else {
            kos = GetPersistentFighterData((u8) arg2)->fighter_kos[arg1];
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

void mnDiagram_80241310(s32 arg0, s32 arg1, s32 arg2)
{
    mnDiagram_Data* data;
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
    mnDiagram_80240D94(gobj, arg0, arg1, arg2);

    if (arg2 != 0) {
        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[9], JOBJ_HIDDEN);
        }
        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[1], JOBJ_HIDDEN);
        }
        if (arg0 != arg1) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[12], JOBJ_HIDDEN);
        }
    } else {
        HSD_JObj* icon = mnDiagram_80242B38(arg0, 1);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        mn_8022F3D8(icon, 0xA, TOBJ_MASK);
        HSD_JObjAddChild(popup_data->jobjs[7], icon);

        icon = mnDiagram_80242B38(arg1, 1);
        HSD_JObjSetTranslateX(icon, -1.0f);
        mn_8022F3D8(icon, 1, TOBJ_MASK);
        HSD_JObjAddChild(popup_data->jobjs[10], icon);

        if (arg0 == arg1) {
            HSD_JObjSetFlagsAll(popup_data->jobjs[1], JOBJ_HIDDEN);
        } else {
            icon = mnDiagram_80242B38(arg1, 1);
            HSD_JObjSetTranslateX(icon, -1.0f);
            mn_8022F3D8(icon, 1, TOBJ_MASK);
            HSD_JObjAddChild(popup_data->jobjs[2], icon);
        }
        if (arg0 != arg1) {
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

void mnDiagram_80241668(void* arg0)
{
    mnDiagram_PopupData* data = mnDiagram_GetUserData(arg0);
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

void mnDiagram_80241730(void* arg0, int arg1, int arg2)
{
    mnDiagram_Data* data = ((HSD_GObj*) arg0)->user_data;
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
void mnDiagram_802417D0(HSD_GObj* gobj)
{
    u8 result2;
    mnDiagram_Data* data = gobj->user_data;
    char* base = (char*) mnDiagram_803EE728;
    HSD_JObj* jobj;
    u8* sorted = (u8*) &mnDiagram_804A0750;
    s32 i;
    u8* ptr;
    u8* ptr2;
    s32 count;
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
        ptr = ptr + 0x1C;
    loop1:
        ptr2 = ptr;
    loop2:
        i++;
        ptr2++;
        ptr++;
        if (i >= 0x78) {
            result = 0x78;
        } else if (GetNameText(*ptr2) == NULL) {
            goto loop2;
        } else {
            count--;
            if (count > 0) {
                goto loop1;
            }
            result = sorted[i + 0x1C];
        }
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

    // Left arrow (jobjs[4])
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

    // Up arrow (jobjs[5])
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

static AnimLoopSettings mnDiagram_803EE768 = { 0.0f, 9.0f, -0.1f };

void mnDiagram_OnFrame(HSD_GObj* gobj)
{
    mnDiagram_Data* data = gobj->user_data;
    mnDiagram_Data* data2;
    HSD_GObjProc* proc;
    u8 col_idx;
    s32 row_idx;
    int count;
    PAD_STACK(0x28);

    if ((mn_804A04F0.cur_menu != 0x1E) || (mn_804A04F0.x10 != 0)) {
        if (mn_804A04F0.cur_menu == 0x1E) {
            mnDiagram_80241668(gobj);
            HSD_GObjPLink_80390228(gobj);
            return;
        }
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(gobj, mnDiagram_ExitAnimProc, 0);
        proc->flags_4 = HSD_GObj_804D783C;
        HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);
        mnDiagram_80241668(gobj);
        return;
    }

    if (data->anim_state == 1) {
        if (mn_8022ED6C(data->jobjs[1], &mnDiagram_803EE768) >=
            mnDiagram_803EE768.end_frame)
        {
            HSD_JObjClearFlagsAll(data->jobjs[2], 0x10);
            data->anim_state = 0;
            mnDiagram_802433AC();
            if (data->is_name_mode != 0) {
                u16 indices = data->name_cursor_pos;
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
            }
            if (data->is_name_mode != 0) {
                count = GetNameCount();
            } else {
                count = mnDiagram_CountUnlockedFighters();
            }
            if (count <= 7) {
                HSD_JObjSetFlagsAll(data->jobjs[5], 0x10);
                HSD_JObjSetFlagsAll(data->jobjs[6], 0x10);
            } else {
                HSD_JObjClearFlagsAll(data->jobjs[5], 0x10);
                HSD_JObjClearFlagsAll(data->jobjs[6], 0x10);
            }
            if (count <= 0xA) {
                HSD_JObjSetFlagsAll(data->jobjs[4], 0x10);
                HSD_JObjSetFlagsAll(data->jobjs[3], 0x10);
            } else {
                HSD_JObjClearFlagsAll(data->jobjs[4], 0x10);
                HSD_JObjClearFlagsAll(data->jobjs[3], 0x10);
            }
        } else {
            HSD_JObjSetFlagsAll(data->jobjs[2], 0x10);
        }
    }
    mnDiagram_802417D0(gobj);
}

void mnDiagram_80241E78(void* arg0, u8 arg1, u8 arg2, s32 arg3)
{
    mnDiagram_Data* data;
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
    u8 col = arg1;
    u8 row = arg2;

    data = ((HSD_GObj*) arg0)->user_data;
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

    digit_count = mn_GetDigitCount(arg3);
    row_offset = y_offset * (f32) row;
    col_offset = y_spacing * (f32) col;
    row_offset_adj = row_offset - 1.0f;

    joint_data = mnDiagram_804A07F4;
    for (i = 0; i < digit_count; i++) {
        digit = mn_GetDigitAt(arg3, i);
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

void mnDiagram_8024227C(void* arg0, s32 arg1, s32 arg2, u8 arg3)
{
    register void* gobj = arg0;
    register s32 arg1_r = arg1;
    register s32 arg2_r = arg2;
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
                        var_r19 = arg2_r;
                        var_r16 = base + arg2_r + 0x1C;
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
                        mnDiagram_80241E78(gobj, (u8) var_r22, (u8) var_r30,
                                           var_r19_2);
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
                        var_r18_4 = arg2_r;
                        var_r17_2 = base + arg2_r;
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
                        mnDiagram_80241E78(gobj, (u8) var_r22, (u8) var_r30,
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
                    if ((var_r22_2 == 7) ||
                        (var_r3 = GetNameCount(), (var_r3 > var_r22_2)))
                    {
                        var_r19_6 = var_r30;
                        var_r18_6 = arg1_r;
                        var_r17_3 = base + arg1_r + 0x1C;
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
                            mnDiagram_80241E78(gobj, (u8) var_r22_2,
                                               (u8) var_r30, var_r17_4);
                        } else {
                            var_r18_8 = var_r22_2;
                            var_r17_5 = arg2_r;
                            var_r15 = base + arg2_r + 0x1C;
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
                            mnDiagram_80241E78(
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
                        var_r17_9 = arg1_r;
                        var_r16_5 = base + arg1_r;
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
                            mnDiagram_80241E78(gobj, (u8) var_r22_3,
                                               (u8) var_r30, var_r16_6);
                        } else {
                            var_r18_12 = var_r22_3;
                            var_r17_11 = arg2_r;
                            var_r16_7 = base + arg2_r;
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
                            mnDiagram_80241E78(
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

void mnDiagram_802427B4(void* arg0, s32 arg1, s32 arg2)
{
    mnDiagram_Data* data = ((HSD_GObj*) arg0)->user_data;
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
            name_id = mnDiagram_804A076C.sorted_names[arg2 + i];
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
            name_id = mnDiagram_804A076C.sorted_names[arg1 + i];
            HSD_SisLib_803A6B98(text, 0.0f, -((y_spacing * (f32) i) / 0.03f),
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
    mnDiagram_Data* data = ((HSD_GObj*) arg0)->user_data;
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
            fighter_id = mnDiagram_804A0750.sorted_fighters[arg2 + i];
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
            fighter_id = mnDiagram_804A0750.sorted_fighters[arg1 + i];
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
    mnDiagram_Data* data;
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
    HSD_GObjProc_8038FD54(gobj, mnDiagram_CursorProc, 0);
}

void mnDiagram_80243434(u8 arg0)
{
    HSD_GObj* gobj;
    HSD_GObj* cursor_gobj;
    HSD_JObj* jobj;
    mnDiagram_Data* data;
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

    data = HSD_MemAlloc(sizeof(mnDiagram_Data));
    data->saved_menu = mn_804A04F0.cur_menu;
    data->saved_selection = mn_804A04F0.hovered_selection;
    data->anim_state = arg0;
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

    if (arg0 == 0) {
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
            mnDiagram_80241668(gobj);
            mnDiagram_8024227C(gobj, col_idx, row_idx, 1);
            mnDiagram_802427B4(gobj, col_idx, row_idx);
        } else {
            indices = data->fighter_cursor_pos;
            col_idx = (u8) indices;
            row_idx = indices >> 8;
            mnDiagram_80241668(gobj);
            mnDiagram_8024227C(gobj, col_idx, row_idx, 0);
            mnDiagram_80242C0C(gobj, col_idx, row_idx);
        }
    }
}

/// Initialize VS Records diagram screen.
/// @param arg0 If non-zero, load DAT archive symbols
/// @param arg1 Initial mode (passed to mnDiagram_80243434)
void mnDiagram_802437E8(s32 arg0, s32 arg1)
{
    mnDiagram_Assets* assets = (mnDiagram_Assets*) &mnDiagram_804A0750;
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1E;
    mn_804A04F0.x10 = 0;
    mn_804A04F0.hovered_selection = 0;

    if (arg0) {
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

    mnDiagram_8023FA6C();
    mnDiagram_8023FC28();
    mnDiagram_80243434((u8) arg1);

    proc = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                 (void (*)(HSD_GObj*)) mnDiagram_InputProc, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
