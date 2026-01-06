#include "mncount.h"
#include <string.h> // For memmove in the first function

// --- Internal Structs ---

typedef struct CountEntry {
    u8 id;      // 0x0
    u8 pad[3];
    u32 val;    // 0x4
} CountEntry;

typedef struct LocalFighterData {
    char pad[0x54];
    u32 unk54;
} LocalFighterData;

// --- Externs for 8025072C ---
extern s32 GetFighterTotalKOs(s32);
extern s32 GetFighterTotalFalls(s32);

// --- Functions ---

// [Function 1: mnCount_8025035C - Status: ~89-100%]
s32 mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(s8)) {
    CountEntry sp18[25];
    CountEntry temp;
    s32 i, j, best_idx;
    s32 has_valid = 0;
    LocalFighterData* fdata;

    // 1. Validation Loop
    for (i = 0; i < 25; i++) {
        fdata = (LocalFighterData*)GetPersistentFighterData(i);
        if (fdata->unk54 != 0) {
            has_valid = 1;
        }
    }
    if (has_valid == 0) return 25;

    // 2. Populate Array
    for (i = 0; i < 25; i++) {
        sp18[i].id = i;
        sp18[i].val = get_val_func((s8)i);
    }

    // 3. Stable Selection Sort
    for (i = 0; i < 25; i++) {
        best_idx = i;
        for (j = i + 1; j < 25; j++) {
            if (sp18[j].val < sp18[best_idx].val) {
                best_idx = j;
            }
        }
        if (best_idx != i) {
            temp = sp18[best_idx];
            for (j = best_idx; j > i; j--) {
                sp18[j] = sp18[j - 1];
            }
            sp18[i] = temp;
        }
    }

    // 4. Selection Logic
    for (i = 0; i < 25; i++) {
        if (gm_80164840(gm_8016400C(sp18[i].id)) == 0) continue;

        if (skip_count != 0) {
            for (j = i + 1; j < 25; j++) {
                 if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) continue;
                 if (get_val_func((s8)sp18[i].id) == get_val_func((s8)sp18[j].id)) {
                     skip_count--;
                     i++;
                     if (skip_count == 0) return 25;
                     j = i;
                 }
            }
            skip_count--;
        } else {
            for (j = i + 1; j < 25; j++) {
                if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) continue;
                if (get_val_func((s8)sp18[i].id) == get_val_func((s8)sp18[j].id)) {
                    return 25;
                }
            }
            return sp18[i].id;
        }
    }
    return 25;
}

// [Function 2: mnCount_8025072C - Status: Attempting Fix]
s32 mnCount_8025072C(CountEntry* entries, s32 start_idx, s32 mode) {
    s32 i;
    s32 best_idx = start_idx;
    s32 found_tie = 0;
    s32 is_invalid = 0;
    s32 curr_stat, best_stat;

    for (i = start_idx + 1; i < 25; i++) {
        if (entries[i].val != entries[start_idx].val) break;

        curr_stat = GetFighterTotalKOs(entries[i].id);
        best_stat = GetFighterTotalKOs(entries[best_idx].id);

        if (mode == 0) {
            if (curr_stat > best_stat) best_idx = i;
        } else {
            if (curr_stat < best_stat) best_idx = i;
        }

        curr_stat = GetFighterTotalKOs(entries[i].id);
        best_stat = GetFighterTotalKOs(entries[best_idx].id);

        if (curr_stat == best_stat) {
            found_tie = 1;
        }
    }

    if (found_tie == 0) {
        return entries[best_idx].id;
    }

    for (i = start_idx + 1; i < 25; i++) {
        if (i == best_idx) continue;

        if (entries[i].val != entries[start_idx].val) break;

        curr_stat = GetFighterTotalKOs(entries[i].id);
        best_stat = GetFighterTotalKOs(entries[best_idx].id);
        if (curr_stat != best_stat) continue;

        curr_stat = GetFighterTotalFalls(entries[i].id);
        best_stat = GetFighterTotalFalls(entries[best_idx].id);

        if (curr_stat == best_stat) {
            is_invalid = 1;
            break;
        }

        if (mode == 0) {
            if (curr_stat < best_stat) best_idx = i;
        } else {
            if (curr_stat > best_stat) best_idx = i;
        }
    }

    if (is_invalid) return 25;
    return entries[best_idx].id;
}
