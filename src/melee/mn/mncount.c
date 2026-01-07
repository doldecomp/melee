#include "mncount.h"
#include <string.h>
#include "types.h"

extern s32 GetFighterTotalKOs(s32);
extern s32 GetFighterTotalFalls(s32);

// --- Internal Structs ---

typedef struct LocalFighterData {
    char pad[0x54];
    u32 unk54;
} LocalFighterData;

// --- Function Implementation ---

inline bool mnCount_8025035C_inline(void)
{
    s32 i;
    for (i = 0; i < 25; i++) {
        LocalFighterData *fdata = (LocalFighterData*)GetPersistentFighterData(i);
        if (fdata->unk54 != 0) {
            return false;
        }
    }
    return 1;
}

s32 mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(s8)) {
    PAD_STACK(4); // Replaces 'int stack_pad = 0' and '(void)stack_pad'

    s32 i;
    s32 j;
    s32 best_idx;
    CountEntry sp18[25];
    CountEntry temp;

    if (mnCount_8025035C_inline()) return ARRAY_SIZE(sp18);

    for (i = 0; i < ARRAY_SIZE(sp18); i++) {
        sp18[i].id = i;
        sp18[i].val = get_val_func((s8)i);
    }

    for (i = 0; i < ARRAY_SIZE(sp18); i++) {
        best_idx = i;

        for (j = i + 1; j < ARRAY_SIZE(sp18); j++) {
            if (sp18[best_idx].val < sp18[j].val) {
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

    for (i = 0; i < ARRAY_SIZE(sp18); i++) {
        if (gm_80164840(gm_8016400C(sp18[i].id)) == 0) continue;

        if (skip_count != 0) {
            skip_count--;
            j = i + 1;
            while (j < ARRAY_SIZE(sp18)) {
                if (gm_80164840(gm_8016400C(sp18[j].id)) != 0 &&
                    get_val_func((s8)sp18[i].id) == get_val_func((s8)sp18[j].id)) {
                    i++;
                    if (skip_count != 0) {
                        skip_count--;
                    } else {
                        return ARRAY_SIZE(sp18);
                    }
                }
                j++;
            }
        } else {
            for (j = i + 1; j < ARRAY_SIZE(sp18); j++) {
                if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) continue;

                if (get_val_func((s8)sp18[i].id) == get_val_func((s8)sp18[j].id)) {
                    return ARRAY_SIZE(sp18);
                }
            }
            return sp18[i].id;
        }
    }

    return ARRAY_SIZE(sp18);
}

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
