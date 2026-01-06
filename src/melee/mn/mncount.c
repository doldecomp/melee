#include "mncount.h"
#include <string.h>

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

// --- Function Implementation ---

s32 mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(s32)) {
    CountEntry sp18[25];
    CountEntry temp;
    s32 i, j, best_idx;
    LocalFighterData* fdata;
    s32 no_valid;

    // 1. Validation Loop using goto for early exit
    for (i = 0; i < 25; i++) {
        fdata = (LocalFighterData*)GetPersistentFighterData(i);
        if (fdata->unk54 != 0) {
            no_valid = 0;
            goto check;
        }
    }
    no_valid = 1;

check:
    if (no_valid) return 25;

    // 2. Populate Array
    for (i = 0; i < 25; i++) {
        sp18[i].id = i;
        sp18[i].val = get_val_func(i);
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
            j = i + 1;
            skip_count--;
            while (j < 25) {
                if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) {
                    j++;
                    continue;
                }

                if (get_val_func(sp18[i].id) == get_val_func(sp18[j].id)) {
                    i++;
                    if (skip_count != 0) {
                        skip_count--;
                    } else {
                        return 25;
                    }
                }
                j++;
            }
        } else {
            for (j = i + 1; j < 25; j++) {
                if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) continue;

                if (get_val_func(sp18[i].id) == get_val_func(sp18[j].id)) {
                    return 25;
                }
            }
            return sp18[i].id;
        }
    }

    return 25;
}
