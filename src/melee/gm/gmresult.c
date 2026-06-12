#include "gmresult.h"

#include "gm/gmresult.static.h"

#include "gm_unsplit.h"
#include "gmresultplayer.h"

#include "baselib/dobj.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/types.h"
#include "gm/gm_1601.h"
#include "gm/types.h"
#include "if/ifcoget.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbvector.h"
#include "mn/mnmain.h"
#include "pl/player.h"
#include "sc/types.h"

MatchEnd* fn_80174274(void)
{
    return lbl_8046DBE8.x94;
}

s32 fn_80174284_noinline(u8 slot);
s32 fn_80174284_noinline(u8 slot)
{
    return fn_80174284(slot);
}

s32 fn_80174284(u8 slot)
{
    s32 i;
    s32 count;
    bool do_call;
    u8* buf;
    struct UnkResultPlayerData* tmp = lbl_8046DBE8.x94->x44C;
    PAD_STACK(8);

    count = 0;
    if (lbl_8046DBE8.x94->player_standings[slot].slot_type == Gm_PKind_Human) {
        do_call = true;
    } else {
        do_call = false;
    }

    for (i = 0; i < 0x100; i++) {
        if (tmp[slot].x0[i] != 0) {
            if (do_call) {
                fn_8016F140(i);
            }
            count++;
        }
    }

    return count;
}

void fn_80174338(void)
{
    lbAudioAx_80024030(1);
}

void fn_8017435C(void)
{
    lbAudioAx_80024030(0);
}

void fn_80174380(void)
{
    lbAudioAx_80024030(2);
}

bool gm_801743A4(u8 outcome)
{
    if (outcome == OUTCOME_LRASTART || outcome == OUTCOME_RETRY) {
        return true;
    }
    return false;
}

typedef struct StatsEntry {
    /* 0x00 */ s16 value;
    /* 0x02 */ u8 pad_2[2];
    /* 0x04 */ s32 (*check)(s32);
    /* 0x08 */ u32 (*get)(s32);
    /* 0x0C */ void* xC;
} StatsEntry;

typedef struct StatsList {
    /* 0x00 */ u8 mode;
    /* 0x01 */ u8 count;
    /* 0x02 */ u8 pad_2[2];
    /* 0x04 */ StatsEntry* entries;
} StatsList;

bool fn_801743C4(s32 slot, StatsEntry* entry)
{
    if (entry->value >= 0) {
        return true;
    }
    if (entry->check != NULL) {
        if (entry->check(slot) == -1) {
            return false;
        }
    }
    if (entry->get == NULL) {
        goto null_get;
    }
    if (entry->get(slot) == 0) {
        return false;
    }
    goto return_true;

null_get:
    return false;

return_true:
    return true;
}

/// Find the nth non-zero byte in array, returning its index
/// 8x unrolled loop matching assembly pattern: lbz first, then lbzu for rest
static s32 find_nth_nonzero(u8* arr, s32 n)
{
    s32 i = 0;
    u8* ptr = arr;
    s32 outer = 32;
    u8 val;

    do {
        /* Iteration 1: lbz (no update) */
        val = *ptr;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 2: lbzu (update first, then load) */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 3 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 4 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 5 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 6 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 7 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Iteration 8 */
        val = *++ptr;
        i++;
        if (val != 0) {
            n--;
            if (n == 0) {
                return i;
            }
        }

        /* Final increment for next outer loop */
        ptr++;
        i++;
    } while (--outer > 0);

    return i;
}

void fn_80174468(u8 slot, HSD_Text* text1, HSD_Text* text2, HSD_Text* text3,
                 StatsList* list, s32 entry_idx)
{
    ResultsData* data = &lbl_8046DBE8;
    StatsEntry* entry;
    MatchEnd* me;
    s32 label_id;
    s32 value_id;
    s32 result;
    s32 idx;
    s32 stat_value;
    /* Variables for inlined unrolled loop */
    s32 loop_i;
    s32 loop_n;
    s32 loop_outer;
    u8* loop_ptr;
    u8 loop_val;
    /* Float constants preloaded into registers */
    f32 const_zero = 0.0F;
    f32 const_neg30 = -30.0F;
    PAD_STACK(8);

    label_id = -1;
    value_id = -1;
    entry = &list->entries[entry_idx];
    me = data->x94;

    if (list->mode != 2) {
        if (entry->value >= 0) {
            HSD_SisLib_803A6368(text1, entry->value);
        }
    } else {
        /// Mode 2: special handling for pairs
        if ((entry_idx & 1) == 1 && entry_idx < list->count) {
            /* Inlined 8x unrolled find_nth_nonzero */
            loop_n = entry_idx / 2;
            loop_outer = 32;
            loop_i = 0;
            loop_n++;
            loop_ptr = me->x44C[slot].x0;
            do {
                loop_val = *loop_ptr;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_val = *++loop_ptr;
                loop_i++;
                if (loop_val != 0) {
                    loop_n--;
                    if (loop_n == 0) {
                        goto found1;
                    }
                }
                loop_ptr++;
                loop_i++;
            } while (--loop_outer);
        found1:
            idx = fn_8016F1F0(loop_i);
            HSD_SisLib_803A6368(text1, (u16) fn_8016F280(idx) + 60);
        }
    }

    if (list->mode == 2 || entry->check != NULL) {
        if (list->mode != 2) {
            result = ((s32 (*)(u8))(Event) entry->check)(slot);
            if (result < 0) {
                value_id = HSD_SisLib_803A6B98(text3, const_zero, const_neg30,
                                               "%s", &lbl_804D3F8C);
            } else {
                value_id = HSD_SisLib_803A6B98(text3, const_zero, const_neg30,
                                               "%d", result);
            }
        } else if ((entry_idx & 1) == 0) {
            idx = (entry_idx / 2) - 1;
            if (idx >= 0) {
                /* Inlined 8x unrolled find_nth_nonzero */
                loop_n = idx;
                loop_outer = 32;
                loop_i = 0;
                loop_n++;
                loop_ptr = me->x44C[slot].x0;
                do {
                    loop_val = *loop_ptr;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_val = *++loop_ptr;
                    loop_i++;
                    if (loop_val != 0) {
                        loop_n--;
                        if (loop_n == 0) {
                            goto found2;
                        }
                    }
                    loop_ptr++;
                    loop_i++;
                } while (--loop_outer);
            found2:
                stat_value = *(s32*) &me->x44C[slot].x0[loop_i * 4 + 0x104];
                if (stat_value < 0) {
                    value_id = HSD_SisLib_803A6B98(text3, const_zero,
                                                   const_neg30, "%s%d",
                                                   &lbl_804D3FA0, -stat_value);
                } else {
                    value_id = HSD_SisLib_803A6B98(
                        text3, const_zero, const_neg30, "%d", stat_value);
                }
            } else {
                value_id = HSD_SisLib_803A6B98(text3, const_zero, const_neg30,
                                               "%s", &lbl_804D3FA0);
            }
        }
        if (list->mode != 2) {
            if (entry->get != NULL) {
                label_id = HSD_SisLib_803A6B98(
                    text2, const_zero, const_neg30, "%s",
                    ((u8 * (*) (u8))(Event) entry->get)(slot));
            }
        }
    } else if (list->mode != 2) {
        if (entry->get != NULL) {
            label_id =
                HSD_SisLib_803A6B98(text2, const_zero, const_neg30, "%s",
                                    ((u8 * (*) (u8))(Event) entry->get)(slot));
        }
    }

    if (label_id >= 0) {
        HSD_SisLib_803A7548(text2, label_id, 0.05F, 0.0546875F);
    }
    if (value_id >= 0) {
        HSD_SisLib_803A7548(text3, value_id, 0.059F, 0.0546875F);
    }
}

typedef struct ResultsStatsInfo {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 pad_2[2];
    /* 0x04 */ int x4;
} ResultsStatsInfo;

static ResultsStatsInfo lbl_8046E190[4];

void* fn_801748EC(void* list_, s32 mode, s32 idx)
{
    ResultsStatsInfo* list = list_;

    if (mode != 2) {
        goto loop_start;
        do {
            list++;
        loop_start:;
        } while (list->x0 != mode);
        return list;
    }
    return &lbl_8046E190[idx];
}

// Return clearly wrong but match is match
u8 fn_80174920(struct ResultsPlayerData* data)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        if (data->stats_text[0][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[0][i]);
            data->stats_text[0][i] = NULL;
        }
        if (data->stats_text[1][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[1][i]);
            data->stats_text[1][i] = NULL;
        }
        if (data->stats_text[2][i] != NULL) {
            HSD_SisLib_803A5CC4(data->stats_text[2][i]);
            data->stats_text[2][i] = NULL;
        }
    }
}

void fn_801749B8(HSD_GObj* unused)
{
    struct ResultsData* new_var2;
    Vec3 sp24;
    Vec3 sp18;
    u16 new_var;
    u16 new_var4;
    s32 new_var3;
    Vec3 spC;
    u32 temp_r4;
    if (0L != lbl_8046DBE8.cobj) {
        lbVector_WorldToScreen(lbl_8046DBE8.cobj,
                               &(&lbl_8046DBE8)->player_data[0].stats_position,
                               &sp24, 0);
        new_var2 = &lbl_8046DBE8;
        lb_8000B1CC((*new_var2).player_data[0].jobjs[0xD], 0L, &sp18);
        lbVector_WorldToScreen((*new_var2).cobj, &sp18, &spC, 0);
        temp_r4 = (new_var4 = (s32) sp24.y) & 0xFFFC;
        new_var = (u16) ((new_var3 = (s32) spC.y) & 0xFFDC);
        GXSetScissor(0U, temp_r4, 0x27FU, new_var - temp_r4);
    }
}

s32 fn_80174A60(StatsList* list, s32 slot)
{
    s32 i;
    s32 count;
    StatsEntry* entry;

    count = 0;
    if (list->mode != 2) {
        for (i = 0; i < list->count; i++) {
            entry = &list->entries[i];
            if (fn_801743C4(slot, entry)) {
                count++;
            }
        }
    } else {
        count = list->count;
    }
    return count;
}

/// Static data for stats lists
static StatsEntry lbl_803D6488[13] = {
    { 8, { 0 }, NULL, NULL, NULL },
    { 8, { 0 }, NULL, NULL, NULL },
    { -1, { 0 }, fn_8017AE70, (u32 (*)(s32))(Event) fn_8017BB94, NULL },
    { -1, { 0 }, fn_8017AED8, (u32 (*)(s32))(Event) fn_8017BC50, NULL },
    { -1, { 0 }, fn_8017AF40, (u32 (*)(s32))(Event) fn_8017BD0C, NULL },
    { -1, { 0 }, fn_8017AFA8, (u32 (*)(s32))(Event) fn_8017BDC8, NULL },
    { 9, { 0 }, NULL, NULL, NULL },
    { -1, { 0 }, fn_8017B07C, (u32 (*)(s32))(Event) fn_8017BB94, NULL },
    { -1, { 0 }, fn_8017B0E4, (u32 (*)(s32))(Event) fn_8017BC50, NULL },
    { -1, { 0 }, fn_8017B14C, (u32 (*)(s32))(Event) fn_8017BD0C, NULL },
    { -1, { 0 }, fn_8017B1B4, (u32 (*)(s32))(Event) fn_8017BDC8, NULL },
    { 12, { 0 }, fn_8017B21C, NULL, NULL },
    { 12, { 0 }, NULL, NULL, NULL },
};

static StatsEntry lbl_803D6558[48] = {
    { 10, { 0 }, NULL, NULL, NULL },
    { 10, { 0 }, NULL, NULL, NULL },
    { 11, { 0 }, fn_8017AE0C, NULL, NULL },
    { 14, { 0 }, NULL, NULL, NULL },
    { 15, { 0 }, fn_8017B010, NULL, NULL },
    { 12, { 0 }, NULL, NULL, NULL },
    { 13, { 0 }, fn_8017B21C, NULL, NULL },
    { 16, { 0 }, NULL, NULL, NULL },
    { 17, { 0 }, fn_8017B280, NULL, NULL },
    { 18, { 0 }, NULL, NULL, NULL },
    { 19, { 0 }, fn_8017B2E4, NULL, NULL },
    { 20, { 0 }, NULL, NULL, NULL },
    { 21, { 0 }, fn_8017B348, NULL, NULL },
    { 22, { 0 }, NULL, NULL, NULL },
    { 23, { 0 }, fn_8017B3AC, NULL, NULL },
    { 24, { 0 }, NULL, NULL, NULL },
    { 25, { 0 }, fn_8017B410, NULL, NULL },
    { 26, { 0 }, NULL, NULL, NULL },
    { 27, { 0 }, fn_8017B4D0, NULL, NULL },
    { 28, { 0 }, NULL, NULL, NULL },
    { 29, { 0 }, fn_8017B534, NULL, NULL },
    { 30, { 0 }, NULL, NULL, NULL },
    { 31, { 0 }, fn_8017B598, NULL, NULL },
    { 32, { 0 }, NULL, NULL, NULL },
    { 33, { 0 }, fn_8017B5FC, NULL, NULL },
    { 34, { 0 }, NULL, NULL, NULL },
    { 35, { 0 }, fn_8017B660, NULL, NULL },
    { 36, { 0 }, NULL, NULL, NULL },
    { 37, { 0 }, fn_8017B6C4, NULL, NULL },
    { 38, { 0 }, NULL, NULL, NULL },
    { 39, { 0 }, fn_8017B728, NULL, NULL },
    { 40, { 0 }, NULL, NULL, NULL },
    { 41, { 0 }, fn_8017B78C, NULL, NULL },
    { 42, { 0 }, NULL, NULL, NULL },
    { 43, { 0 }, fn_8017B7F0, NULL, NULL },
    { 44, { 0 }, NULL, NULL, NULL },
    { 45, { 0 }, fn_8017B854, NULL, NULL },
    { 46, { 0 }, NULL, NULL, NULL },
    { 47, { 0 }, fn_8017B8B8, NULL, NULL },
    { 48, { 0 }, NULL, NULL, NULL },
    { 49, { 0 }, fn_8017B91C, NULL, NULL },
    { 50, { 0 }, NULL, NULL, NULL },
    { 51, { 0 }, fn_8017B9F4, NULL, NULL },
    { 52, { 0 }, NULL, NULL, NULL },
    { 53, { 0 }, (s32 (*)(s32)) fn_8017BACC, NULL, NULL },
    { 54, { 0 }, NULL, NULL, NULL },
    { 55, { 0 }, (s32 (*)(s32)) fn_8017BB30, NULL, NULL },
    { 54, { 0 }, NULL, NULL, NULL },
};

static StatsEntry lbl_803D6858[2] = {
    { 8, { 0 }, NULL, NULL, NULL },
    { 8, { 0 }, NULL, NULL, NULL },
};

static StatsList lbl_803D6878[] = {
    { 0, 0x0D, { 0 }, lbl_803D6488 },
    { 1, 0x30, { 0 }, lbl_803D6558 },
    { 2, 0x02, { 0 }, lbl_803D6858 },
    { 3, 0x00, { 0 }, NULL },
};

static char lbl_803D6898[] =
    "Error : Cannot read archive file (File Name : %s).";

void fn_80174B4C(ResultsData* data, s32 slot)
{
    struct ResultsPlayerData* pdata;
    StatsList* list;
    s32 i;
    s32 entry_idx;
    s32 entry_offset;
    s32 count;
    s32 visible_count;
    Vec3 pos;
    f32 offset;
    s32 start_entry;
    PAD_STACK(56);

    pdata = &data->player_data[slot];
    list = lbl_803D6878;

    /// Clear existing stats text
    for (i = 0; i < 10; i++) {
        if (pdata->stats_text[0][i] != NULL) {
            HSD_SisLib_803A5CC4(pdata->stats_text[0][i]);
            pdata->stats_text[0][i] = NULL;
        }
        if (pdata->stats_text[1][i] != NULL) {
            HSD_SisLib_803A5CC4(pdata->stats_text[1][i]);
            pdata->stats_text[1][i] = NULL;
        }
        if (pdata->stats_text[2][i] != NULL) {
            HSD_SisLib_803A5CC4(pdata->stats_text[2][i]);
            pdata->stats_text[2][i] = NULL;
        }
    }

    /// Look up stats list
    if ((s32) pdata->page != 2) {
        while ((s32) list->mode != (s32) pdata->page) {
            list++;
        }
    } else {
        list = (StatsList*) &lbl_8046E190[slot];
    }

    count = 0;
    pos = pdata->stats_position;

    offset = pdata->scroll_offset;
    start_entry = (s32) (10.0F * offset) / 10;
    pos.y += 1.75F * (offset - (f32) (start_entry - 1));

    /// Set flags
    pdata->x0_3 = 1;
    pdata->x0_4 = 1;

    if (pdata->page == 0) {
        pdata->x0_3 = 0;
    }
    if (pdata->page >= data->num_pages - 1) {
        pdata->x0_4 = 0;
    }

    /// Count visible entries
    visible_count = fn_80174A60(list, 0);

    /// Set more flags based on scroll position
    if (pdata->scroll_offset < (f32) (visible_count - 10)) {
        pdata->x0_2 = 1;
    } else {
        pdata->x0_2 = 0;
    }

    entry_offset = start_entry * 0x10;

    if (pdata->scroll_offset > 0.0F) {
        pdata->x0_1 = 1;
    } else {
        pdata->x0_1 = 0;
    }

    /// Create text objects for visible entries
    entry_idx = start_entry;
    while (count < 10) {
        if (list->count <= entry_idx + 1) {
            break;
        }
        if (list->mode != 2) {
            if (!fn_801743C4(slot, &list->entries[entry_idx])) {
                entry_idx++;
                entry_offset += 0x10;
                continue;
            }
        }

        pdata->stats_text[0][count] =
            HSD_SisLib_803A5ACC(0, 0, pos.x, -pos.y, pos.z, 11.0F, 10.0F);
        pdata->stats_text[0][count]->default_fitting = 1;
        pdata->stats_text[0][count]->x34.x = 0.05F;
        pdata->stats_text[0][count]->x34.y = 0.0546875F;
        pdata->stats_text[0][count]->render_callback =
            (void (*)(void*)) fn_801749B8;

        pdata->stats_text[1][count] = HSD_SisLib_803A6754(0, 0);
        pdata->stats_text[1][count]->pos_x = pos.x;
        pdata->stats_text[1][count]->pos_y = -pos.y;
        pdata->stats_text[1][count]->pos_z = pos.z;
        pdata->stats_text[1][count]->render_callback =
            (void (*)(void*)) fn_801749B8;

        pdata->stats_text[2][count] = HSD_SisLib_803A6754(0, 0);
        pdata->stats_text[2][count]->pos_x = 11.0F + pos.x;
        pdata->stats_text[2][count]->pos_y = -pos.y;
        pdata->stats_text[2][count]->pos_z = pos.z;
        pdata->stats_text[2][count]->render_callback =
            (void (*)(void*)) fn_801749B8;
        pdata->stats_text[2][count]->default_alignment = 2;

        pos.y -= 1.75F;
        fn_80174468(slot, pdata->stats_text[0][count],
                    pdata->stats_text[1][count], pdata->stats_text[2][count],
                    list, entry_idx);
        entry_idx++;
        entry_offset += 0x10;
        count++;
    }
}

void fn_80174FD0(HSD_JObj* jobj, s32 arg1)
{
    HSD_TObj* tobj = jobj->u.dobj->mobj->tobj;

    HSD_AObjSetCurrentFrame(tobj->aobj, (f32) arg1);
    HSD_AObjSetRate(tobj->aobj, 0.0f);
    HSD_TObjAnim(tobj);
}

void fn_80175038(HSD_GObj* gobj, int flag)
{
    HSD_JObjDispAll(GET_JOBJ(gobj), NULL, HSD_GObj_80390EB8(flag), 0U);
}

GXColor fn_8017507C(s32 slot)
{
    f32 current_color;
    u8 _[8];
    GXColor color;

    if (lbl_8046DBE8.x94->is_teams == 1) {
        if (lbl_8046DBE8.x94->player_standings[slot].slot_type == Gm_PKind_NA)
        {
            color = gm_80160968(4);
        } else {
            switch (lbl_8046DBE8.x94->player_standings[slot].team) {
            case 0:
                color = gm_80160968(0);
                break;
            case 1:
                color = gm_80160968(1);
                break;
            case 2:
                color = gm_80160968(3);
                break;
            case 3:
                color = gm_80160968(2);
                break;
            default:
                color = gm_80160968(4);
                break;
            }
        }

        current_color = (0.9f * (f32) color.r) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.r = current_color;

        current_color = (0.9f * (f32) color.g) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.g = (s8) current_color;

        current_color = (0.9f * (f32) color.b) + 100.0f;
        if (current_color > 255.0f) {
            current_color = 255.0f;
        }
        color.b = (s8) current_color;
    } else {
        color.r = color.g = color.b = color.a = 0xFF;
    }
    return color;
}

void fn_80175240(s32 slot)
{
    GXColor sp2C;
    GXColor sp30;
    GXColor sp28;
    GXColor sp24;
    GXColor sp20;
    GXColor sp1C;
    GXColor sp18;
    HSD_Text** temp_r31;
    HSD_Text* ko_count;
    MatchEnd* me;
    f32 temp_f31;
    f32 temp_f30;
    s32 temp_r3;
    s32 var_r3;
    s32 var_r5;
    PAD_STACK(16);

    me = lbl_8046DBE8.x94;
    if (me->x5 != 3) {
        /// maybe x4C is an array of Vec2's
        temp_f31 = 1.14f * (lbl_8046DBE8.x4C[4].y - lbl_8046DBE8.x4C[0].y);
        temp_f30 = 1.12f * (lbl_8046DBE8.x4C[5].y - lbl_8046DBE8.x4C[4].y);
        sp30 = fn_8017507C(slot);
        ko_count = HSD_SisLib_803A6754(0, 0);
        ko_count = lbl_8046DBE8.player_data[slot].ko_count;
        ko_count->pos_x = lbl_8046DBE8.x4C[slot].x;
        ko_count->pos_y = -lbl_8046DBE8.x4C[slot].y - 30.0f;
        ko_count->pos_z = lbl_8046DBE8.x4C[slot].z;
        lbl_8046DBE8.player_data[slot].ko_count->default_alignment = 1;
        lbl_8046DBE8.player_data[slot].ko_count->default_kerning = 1;
        temp_r31 = &lbl_8046DBE8.player_data[slot].ko_count;
        if (me->player_standings[slot].slot_type != Gm_PKind_NA) {
            var_r3 = fn_8017AE0C(slot);
            if (var_r3 > 0x3E7) {
                var_r3 = 0x3E7;
            }
            temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, 0.0f, "%d", var_r3);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp2C = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp2C);
            var_r5 = fn_8017B010(slot);
            if (var_r5 > 0x3E7) {
                var_r5 = 0x3E7;
            }

            temp_r3 =
                HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31, "%d", var_r5);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp28 = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp28);
            var_r5 = fn_8017B21C(slot);
            if (var_r5 > 0x3E7) {
                var_r5 = 0x3E7;
            }
            temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f,
                                          -temp_f31 - temp_f30, "%d", var_r5);
            HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
            sp24 = sp30;
            HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp24);
            return;
        }
        sp30.r = 0xA0;
        sp30.g = 0xA0;
        sp30.b = 0xA0;
        temp_r3 =
            HSD_SisLib_803A6B98(*temp_r31, 0.0f, 0.0f, "%s", &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp20 = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp20);
        temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31, "%s",
                                      &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp1C = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp1C);
        temp_r3 = HSD_SisLib_803A6B98(*temp_r31, 0.0f, -temp_f31 - temp_f30,
                                      "%s", &lbl_804D3FA0);
        HSD_SisLib_803A7548(*temp_r31, temp_r3, 0.11f, 0.08f);
        sp18 = sp30;
        HSD_SisLib_803A74F0(*temp_r31, temp_r3, &sp18);
    }
}

void fn_8017556C(s32 slot)
{
    MatchEnd* me;
    s32 var_r28;
    s32 var_r6;
    GXColor sp10; /* compiler-managed */
    GXColor spC;
    GXColor* new_var;

    me = lbl_8046DBE8.x94;
    if (me && me) {
    }
    sp10 = fn_8017507C(slot);
    if (me->player_standings[slot].slot_type != Gm_PKind_NA) {
        var_r6 = fn_8017AD28(me->player_standings[slot].score);
        if (var_r6 < 0) {
            if (var_r6 < 0) {
                var_r6 = -var_r6;
            }
            var_r28 = HSD_SisLib_803A6B98(
                lbl_8046DBE8.player_data[slot].ko_time, 0.0F, -30.0F, "%s%d",
                &lbl_804D3FA0, var_r6);
        } else if (var_r6 > 0) {
            var_r28 = HSD_SisLib_803A6B98(
                lbl_8046DBE8.player_data[slot].ko_time, 0.0F, -30.0F, "%s%d",
                &lbl_804D3FA4, var_r6);
        } else {
            var_r28 =
                HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time,
                                    0.0F, -30.0F, "%d", var_r6);
        }
    } else {
        sp10.r = 0xA0;
        sp10.g = 0xA0;
        sp10.b = 0xA0;
        var_r28 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time,
                                      0.0F, -30.0F, "%s", &lbl_804D3FA0);
    }
    HSD_SisLib_803A7548(lbl_8046DBE8.player_data[slot].ko_time, var_r28, 0.11F,
                        0.08F);
    spC = sp10;
    new_var = &spC;
    HSD_SisLib_803A74F0(lbl_8046DBE8.player_data[slot].ko_time, var_r28,
                        new_var);
}

void fn_801756E0(s32 slot)
{
    MatchEnd* me;
    s32 var_r28;
    s32 var_r6;
    GXColor* new_var;
    s32 skip;
    GXColor sp10; /* compiler-managed */
    GXColor spC;

    me = lbl_8046DBE8.x94;
    if (me && me) {
    }
    sp10 = fn_8017507C(slot);
    if (me->player_standings[slot].slot_type == Gm_PKind_NA) {
        goto grey_out;
    }
    if (me->result == 7 || me->result == 8) {
        skip = 1;
    } else {
        skip = 0;
    }
    if (skip != 0) {
        goto grey_out;
    }
    var_r6 = fn_8017AD48(me->player_standings[slot].score);
    if (var_r6 < 0) {
        if (var_r6 < 0) {
            var_r6 = -var_r6;
        }
        var_r28 =
            HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                                -30.0F, "%s%d", &lbl_804D3FA0, var_r6);
    } else if (0 < var_r6) {
        var_r28 =
            HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                                -30.0F, "%s%d", &lbl_804D3FA4, var_r6);
    } else {
        var_r28 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time,
                                      0.0F, -30.0F, "%d", var_r6);
    }
    goto end_common;

grey_out:
    sp10.r = 0xA0;
    sp10.g = 0xA0;
    sp10.b = 0xA0;
    var_r28 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                                  -30.0F, "%s", &lbl_804D3FA0);
end_common:
    HSD_SisLib_803A7548(lbl_8046DBE8.player_data[slot].ko_time, var_r28, 0.08F,
                        0.08F);
    spC = sp10;
    new_var = &spC;
    HSD_SisLib_803A74F0(lbl_8046DBE8.player_data[slot].ko_time, var_r28,
                        new_var);
}

void fn_80175880(s32 slot)
{
    MatchEnd* me;
    u32 new_var2;
    s32 var_r30;
    u8 winner;
    GXColor sp10;
    GXColor spC;
    GXColor* new_var;
    s32 skip;
    u32 seconds;
    u32 minutes;

    me = lbl_8046DBE8.x94;
    sp10 = fn_8017507C(slot);
    if (me->player_standings[slot].slot_type == Gm_PKind_NA) {
        goto grey_out;
    }

    winner = lbl_8046DBE8.x6;
    if (winner == slot) {
        goto show_normal;
    }

    if (me->is_teams == 1) {
        if (me->team_standings[me->player_standings[slot].team].is_big_loser ==
            0)
        {
            if ((s8) me->player_standings[slot].stocks > 0) {
                goto show_normal;
            }
            if (me->player_standings[slot].x28 == me->frame_count) {
                if ((s8) me->player_standings[winner].stocks == 0) {
                    goto show_normal;
                }
            }
        }
    }

    if (me->result == 7 || me->result == 8) {
        skip = 1;
    } else {
        skip = 0;
    }

    if (skip != 0) {
        if ((s8) me->player_standings[slot].stocks > 0) {
            goto show_normal;
        }
        if (me->player_standings[slot].score ==
            me->player_standings[winner].score)
        {
            goto show_normal;
        }
    }

    seconds = me->player_standings[slot].x28 / 60;
    if (seconds > 5999) {
        seconds = 5999;
    }
    minutes = seconds / 60;
    new_var2 = minutes * 60;
    var_r30 =
        HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                            -30.0F, "%d\x81\x46%02d", minutes,
                            seconds - new_var2);
    goto end_common;

show_normal:
    var_r30 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                                  -30.0F, NULL);
    goto end_common;

grey_out:
    sp10.r = 0xA0;
    sp10.g = 0xA0;
    sp10.b = 0xA0;
    var_r30 = HSD_SisLib_803A6B98(lbl_8046DBE8.player_data[slot].ko_time, 0.0F,
                                  -30.0F, NULL, 0);

end_common:
    HSD_SisLib_803A7548(lbl_8046DBE8.player_data[slot].ko_time, var_r30, 0.11f,
                        0.08F);
    spC = sp10;
    new_var = &spC;
    HSD_SisLib_803A74F0(lbl_8046DBE8.player_data[slot].ko_time, var_r30,
                        new_var);
}

static char lbl_803D68D8[] = "SdRst.usd";
static char lbl_803D68E4[] = "SIS_ResultData";
static char lbl_803D68F4[] = "SdRst.dat";

void fn_80175A94(s32 slot, Vec3* position)
{
    MatchEnd* me;
    s32 var_r29;
    f32 x_pos;
    f32 new_var3;
    HSD_Text* new_var2;
    ResultsData* new_var;
    f32 new_var4;
    GXColor* color_ptr;
    Vec3 sp24;
    PAD_STACK(16);

    me = lbl_8046DBE8.x94;
    if (me->x5 == 3) {
        lb_8000B1CC(lbl_8046DBE8.player_data[slot].jobjs[12], NULL, &sp24);
        x_pos = 5.5F + sp24.x;
    } else {
        x_pos = lbl_8046DBE8.x4C[slot].x;
    }

    new_var = &lbl_8046DBE8;
    new_var->player_data[slot].ko_time = HSD_SisLib_803A6754(0, 0);
    new_var3 = position->z;
    new_var2 = new_var->player_data[slot].ko_time;
    new_var4 = -position->y;
    new_var2->pos_x = x_pos;
    new_var2->pos_y = new_var4;
    new_var2->pos_z = new_var3;
    new_var->player_data[slot].ko_time->default_alignment = 1;
    new_var->player_data[slot].ko_time->default_kerning = 1;

    if (me->x5 == 2) {
        GXColor sp14;
        GXColor sp18;
        me = lbl_8046DBE8.x94;
        sp14 = fn_8017507C(slot);
        if (me->player_standings[slot].slot_type != 3) {
            var_r29 = HSD_SisLib_803A6B98(new_var->player_data[slot].ko_time,
                                          0.0F, -30.0F, "%d",
                                          fn_8017AD78(fn_8017ADA8(slot)));
        } else {
            sp14.r = 0xA0;
            sp14.g = 0xA0;
            sp14.b = 0xA0;
            var_r29 = HSD_SisLib_803A6B98(new_var->player_data[slot].ko_time,
                                          0.0F, -30.0F, "%s", &lbl_804D3FA0);
        }
        HSD_SisLib_803A7548(new_var->player_data[slot].ko_time, var_r29, 0.09F,
                            0.08F);
        sp18 = sp14;
        color_ptr = &sp18;
        HSD_SisLib_803A74F0(new_var->player_data[slot].ko_time, var_r29,
                            color_ptr);
    } else if (me->x5 == 1) {
        fn_80175880(slot);
    } else if (me->x5 == 3) {
        fn_801756E0(slot);
    } else {
        fn_8017556C(slot);
    }
}

void fn_80175C5C(void)
{
    s32 i;
    u8 _[4];
    Vec3 position;
    PAD_STACK(4);

    lb_8000B1CC(lbl_8046DBE8.x24, NULL, &position);
    for (i = 0; i < 6; i++) {
        lb_8000B1CC(lbl_8046DBE8.x34[i], NULL, &lbl_8046DBE8.x4C[i]);
    }

    lbl_8046DBE8.xC = lbl_8046DBE8.x4C[0].y - position.y;
    HSD_SisLib_803A6754(0, 0);
    HSD_SisLib_803A6754(0, 0);
    for (i = 0; i < 4; i++) {
        fn_80175A94(i, &position);
        fn_80175240(i);
    }
}

void fn_80175D34(void)
{
    ResultsData* data;
    u8 _[12];
    Vec3 pos;
    HSD_Text* ko_count;
    HSD_Text* ko_time;
    s32 i;
    PAD_STACK(8); ///< @todo :: why does this have so much stack space

    lb_8000B1CC((data = &lbl_8046DBE8)->x24, NULL, &pos);

    for (i = 0; i < 4; i++) {
        if (data->player_data[i].ko_count != NULL) {
            HSD_SisLib_803A5CC4(data->player_data[i].ko_count);
            data->player_data[i].ko_count = NULL;
        }

        ko_time = data->player_data[i].ko_time;
        if (ko_time != NULL) {
            ko_time->pos_y = -pos.y;
        }
    }
}

static const struct {
    u8 lookup[34][2];
    Vec3 translate;
} lbl_803B7B18 = {
    {
        { 0x00, 0x0 }, { 0x01, 0x1 }, { 0x02, 0x2 }, { 0x03, 0x3 },
        { 0x04, 0x5 }, { 0x05, 0x6 }, { 0x06, 0xD }, { 0x07, 0x6 },
        { 0x08, 0x6 }, { 0x09, 0x7 }, { 0x0A, 0x9 }, { 0x0B, 0x8 },
        { 0x0C, 0x6 }, { 0x0D, 0x9 }, { 0x0E, 0x4 }, { 0x0F, 0x9 },
        { 0x10, 0xA }, { 0x11, 0xC }, { 0x12, 0xD }, { 0x13, 0xD },
        { 0x14, 0x2 }, { 0x15, 0xD }, { 0x16, 0x6 }, { 0x17, 0x7 },
        { 0x18, 0x9 }, { 0x19, 0xD }, { 0 },         { 0 },
        { 0 },         { 0 },         { 0 },         { 0 },
        { 0 },         { 0 },
    },
    { 0.0F, 4.0F, 0.0F },
};

void fn_80175DC8(HSD_GObj* gobj)
{
    HSD_JObj* sp108;
    HSD_JObj* sp104;
    HSD_JObj* sp100;
    HSD_JObj* spFC;
    HSD_JObj* spF4;
    HSD_JObj* spEC;
    HSD_JObj* spE4;
    HSD_JObj* spDC;
    HSD_JObj* spD4;
    HSD_JObj* spCC;
    HSD_JObj* spC4;
    HSD_JObj* spBC;
    HSD_JObj* spB4;
    HSD_JObj* spAC;
    HSD_JObj* spA4;
    HSD_JObj* sp9C;
    HSD_JObj* sp8C;
    HSD_JObj* sp94;
    HSD_JObj* sp84;
    Vec3 sp78;
    Point3d sp6C;
    Vec3 sp60;
    Point3d sp54;
    Vec3 sp48;
    Point3d sp3C;
    Vec3 sp30;
    Point3d sp24;
    ResultsData* data;
    DynamicModelDesc* model;
    HSD_JObj* jobj;
    MatchEnd* me;
    HSD_JObj* title_jobj;
    HSD_Text* title_text;
    s32 i;

    PAD_STACK(24);

    data = &lbl_8046DBE8;
    me = data->x94;
    model = data->pnlsce->models[0];
    jobj = HSD_JObjLoadJoint(model->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, fn_80175038, 11, 0);
    lb_8000C07C(jobj, 0, model->anims, model->matanims, model->shapeanims);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);

    lb_80011E24(jobj, &sp108, 0x41, -1);
    fn_80179F84(sp108);
    sp104 = jobj;
    lb_80011E24(jobj, &sp104, 0x68, -1);
    data->x24 = sp104;
    sp100 = jobj;
    lb_80011E24(jobj, &sp100, 0x69, -1);
    data->x28 = sp100;

    for (i = 0; i < 6; i++) {
        lb_80011E24(jobj, &data->x34[i], i + 0x62, -1);
    }

    spFC = jobj;
    lb_80011E24(jobj, &spFC, 0xA, -1);
    data->x30 = spFC;

    for (i = 0; i < 4; i++) {
        data->player_data[i].x0_0 = 0;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spF4, 0x42, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spF4, 0x43, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spF4, 0x44, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spF4, 0x45, -1);
            break;
        }
        data->player_data[i].jobjs[0] = spF4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spEC, 0x1D, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spEC, 0x25, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spEC, 0x2D, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spEC, 0x35, -1);
            break;
        }
        data->player_data[i].jobjs[1] = spEC;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spE4, 0x1E, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spE4, 0x26, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spE4, 0x2E, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spE4, 0x36, -1);
            break;
        }
        data->player_data[i].jobjs[2] = spE4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spDC, 0x3D, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spDC, 0x3E, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spDC, 0x3F, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spDC, 0x40, -1);
            break;
        }
        data->player_data[i].jobjs[3] = spDC;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spD4, 0x21, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spD4, 0x29, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spD4, 0x31, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spD4, 0x39, -1);
            break;
        }
        data->player_data[i].jobjs[5] = spD4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spCC, 0x46, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spCC, 0x49, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spCC, 0x4C, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spCC, 0x4F, -1);
            break;
        }
        data->player_data[i].jobjs[4] = spCC;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spC4, 0x52, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spC4, 0x53, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spC4, 0x54, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spC4, 0x55, -1);
            break;
        }
        data->player_data[i].jobjs[6] = spC4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spBC, 0x19, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spBC, 0x1A, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spBC, 0x1B, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spBC, 0x1C, -1);
            break;
        }
        data->player_data[i].jobjs[7] = spBC;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spB4, 0x6C, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spB4, 0x6E, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spB4, 0x70, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spB4, 0x72, -1);
            break;
        }
        data->player_data[i].jobjs[8] = spB4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spAC, 0x6B, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spAC, 0x6D, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spAC, 0x6F, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spAC, 0x71, -1);
            break;
        }
        data->player_data[i].jobjs[9] = spAC;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &spA4, 0x23, -1);
            break;
        case 1:
            lb_80011E24(jobj, &spA4, 0x2B, -1);
            break;
        case 2:
            lb_80011E24(jobj, &spA4, 0x33, -1);
            break;
        case 3:
            lb_80011E24(jobj, &spA4, 0x3B, -1);
            break;
        }
        data->player_data[i].jobjs[10] = spA4;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &sp9C, 0x24, -1);
            break;
        case 1:
            lb_80011E24(jobj, &sp9C, 0x2C, -1);
            break;
        case 2:
            lb_80011E24(jobj, &sp9C, 0x34, -1);
            break;
        case 3:
            lb_80011E24(jobj, &sp9C, 0x3C, -1);
            break;
        }
        data->player_data[i].jobjs[11] = sp9C;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &sp94, 0x56, -1);
            break;
        case 1:
            lb_80011E24(jobj, &sp94, 0x57, -1);
            break;
        case 2:
            lb_80011E24(jobj, &sp94, 0x58, -1);
            break;
        case 3:
            lb_80011E24(jobj, &sp94, 0x59, -1);
            break;
        }
        data->player_data[i].jobjs[12] = sp94;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &sp8C, 0x5A, -1);
            break;
        case 1:
            lb_80011E24(jobj, &sp8C, 0x5B, -1);
            break;
        case 2:
            lb_80011E24(jobj, &sp8C, 0x5C, -1);
            break;
        case 3:
            lb_80011E24(jobj, &sp8C, 0x5D, -1);
            break;
        }
        data->player_data[i].jobjs[13] = sp8C;
        switch (i) {
        case 0:
            lb_80011E24(jobj, &sp84, 0x5E, -1);
            break;
        case 1:
            lb_80011E24(jobj, &sp84, 0x5F, -1);
            break;
        case 2:
            lb_80011E24(jobj, &sp84, 0x60, -1);
            break;
        case 3:
            lb_80011E24(jobj, &sp84, 0x61, -1);
            break;
        }
        data->player_data[i].jobjs[14] = sp84;
        lb_8000B1CC(data->player_data[i].jobjs[12], NULL,
                    &data->player_data[i].stats_position);
    }

    fn_801785B0(gobj);
    if (me->x5 == 0) {
        title_text = data->x2C;
        title_jobj = data->x28;
        sp78 = lbl_803B7B18.translate;
        if (title_text != NULL) {
            HSD_SisLib_803A5CC4(title_text);
        }
        lb_8000B1CC(title_jobj, &sp78, &sp6C);
        HSD_SisLib_803A6368(
            HSD_SisLib_803A5ACC(0, 0, sp6C.x, -sp6C.y, sp6C.z, 12.0F,
                                300.0F),
            2);
    } else if (me->x5 == 1) {
        title_text = data->x2C;
        title_jobj = data->x28;
        sp60 = lbl_803B7B18.translate;
        if (title_text != NULL) {
            HSD_SisLib_803A5CC4(title_text);
        }
        lb_8000B1CC(title_jobj, &sp60, &sp54);
        HSD_SisLib_803A6368(
            HSD_SisLib_803A5ACC(0, 0, sp54.x, -sp54.y, sp54.z, 12.0F,
                                300.0F),
            3);
    } else if (me->x5 == 2) {
        title_text = data->x2C;
        title_jobj = data->x28;
        sp48 = lbl_803B7B18.translate;
        if (title_text != NULL) {
            HSD_SisLib_803A5CC4(title_text);
        }
        lb_8000B1CC(title_jobj, &sp48, &sp3C);
        HSD_SisLib_803A6368(
            HSD_SisLib_803A5ACC(0, 0, sp3C.x, -sp3C.y, sp3C.z, 12.0F,
                                300.0F),
            4);
    } else if (me->x5 == 3) {
        title_text = data->x2C;
        title_jobj = data->x28;
        sp30 = lbl_803B7B18.translate;
        if (title_text != NULL) {
            HSD_SisLib_803A5CC4(title_text);
        }
        lb_8000B1CC(title_jobj, &sp30, &sp24);
        HSD_SisLib_803A6368(
            HSD_SisLib_803A5ACC(0, 0, sp24.x, -sp24.y, sp24.z, 12.0F,
                                300.0F),
            5);
    }
}

void fn_80176A6C(void)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;

    gobj = GObj_Create(0x13U, 0x14U, 0U);
    if (gobj == NULL) {
        OSReport("Error : gobj dont\'t get (gmResultAddPanelCamera)\n");
        HSD_ASSERTMSG(0x662, 0, (char*) &lbl_804D3FB0);
    }

    cobj = HSD_CObjLoadDesc(lbl_8046DBE8.pnlsce->cameras->desc);
    if (cobj == NULL) {
        OSReport("Error : cobj dont\'t get (gmResultAddPanelCamera)\n");
        HSD_ASSERTMSG(0x668, 0, (char*) &lbl_804D3FB0);
    }

    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 8U);
    if (lbl_8046DBE8.x0_5) {
        gobj->gxlink_prios = 1;
    } else {
        gobj->gxlink_prios = 0x4D81;
    }

    HSD_SisLib_803A611C(0, gobj, 9U, 0xDU, 0U, 0xEU, 0U, 0x13U);
    if (lbLang_IsSavedLanguageUS() != 0) {
        HSD_SisLib_803A62A0(0, lbl_803D68D8, lbl_803D68E4);
    } else {
        HSD_SisLib_803A62A0(0, lbl_803D68F4, lbl_803D68E4);
    }
    lbl_8046DBE8.cobj = cobj;
}

static char lbl_803D6974[] = "Error : gobj dont't get (gmResultAddLight)\n";
static char lbl_803D69A0[] = "Error : lobj dont't get (gmResultAddLight)\n";
static char lbl_803D69CC[] = "Error : gobj dont't get (gmResultAddModel)\n";

void fn_80176BCC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
}

static inline int fn_80176BF0_inline(u8 arg1)
{
    int i;
    for (i = 0; i < 0x21; i++) {
        if (arg1 == lbl_803B7B18.lookup[i][0]) {
            return lbl_803B7B18.lookup[i][1];
        }
    }
    return -1;
}

HSD_JObj* fn_80176BF0(HSD_JObj* arg0, u8 arg1, int arg2)
{
    HSD_JObj* jobj;
    int var_r31;
    HSD_JObj* var_r30;
    int var_r29;

    var_r31 = 0;
    var_r30 = NULL;
    lb_80011E24(arg0, &jobj, 5, -1);
    if (arg2 != 0) {
        var_r29 = 11;
    } else {
        var_r29 = fn_80176BF0_inline(arg1);
    }
    for (jobj = HSD_JObjGetChild(jobj); jobj != NULL;
         jobj = HSD_JObjGetNext(jobj))
    {
        if (var_r31 != var_r29) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        } else {
            var_r30 = jobj;
        }
        var_r31++;
    }
    return var_r30;
}

void fn_80176D18(HSD_GObj* gobj)
{
    HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
}

void fn_80176D3C(Vec3* positions)
{
    ResultsData* data = &lbl_8046DBE8;
    MatchEnd* me;
    Vec3* pos;
    struct ResultsMatchPlayerIter {
        u8 pad_0[0x58];
        u8 slot_type;
        u8 pad_59[4];
        u8 is_big_loser;
        u8 pad_5E;
        u8 team;
        u8 pad_60[0xA8 - 0x60];
    }* p;
    u8 _[8];
    DynamicModelDesc* models[3];
    s32 i;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 winner;
    PAD_STACK(8);

    me = data->x94;
    pos = positions;
    p = (struct ResultsMatchPlayerIter*) me;
    if (p && p) {
    }
    models[0] = data->flmsce->models[3];
    models[1] = data->flmsce->models[2];
    models[2] = data->flmsce->models[1];

    i = 0;
    do {
        if (p->slot_type == Gm_PKind_NA) {
            goto loop_end;
        }

        if (me->is_teams == 0) {
            winner = p->is_big_loser;
        } else {
            winner = me->team_standings[p->team].is_big_loser;
        }

        if (winner > 3) {
            winner = 3;
        }

        if (me->result == 7) {
            winner = 1;
        } else if (winner == 0) {
            goto loop_end;
        }

        gobj = GObj_Create(14, 15, 0);
        jobj = HSD_JObjLoadJoint(models[winner - 1]->joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 11, 0);

        HSD_JObjSetTranslate(jobj, pos);

        gm_8016895C(jobj, models[winner - 1], 0);
        HSD_JObjReqAnimAll(jobj, 0.0F);
        HSD_JObjAnimAll(jobj);
        HSD_GObj_SetupProc(gobj, fn_80176D18, 1);
        fn_80179F6C(i, (int) gobj);

    loop_end:
        i++;
        p++;
        pos++;
    } while (i < 4);
}

void fn_80176F60(void)
{
    Vec3 sp8[4];

    ResultsData* data = &lbl_8046DBE8;
    HSD_AObj* aobj;
    HSD_AObj* new_var;
    MatchEnd* temp_r30;
    HSD_GObj* temp_r29;
    DynamicModelDesc* temp_r27;
    HSD_JObj* jobj;
    int i;
    u8 tmp;

    temp_r30 = data->x94;
    temp_r27 = *data->flmsce->models;
    temp_r29 = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(temp_r27->joint);
    HSD_GObjObject_80390A70(temp_r29, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(temp_r29, fn_80175038, 0xB, 0);
    lb_8000C0E8(jobj, 0, temp_r27);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    data->x20 =
        fn_80176BF0(jobj, temp_r30->player_standings[data->x6].character_kind,
                    gm_801743A4(temp_r30->result));
    aobj = data->x20->u.dobj->mobj->aobj;
    tmp = gm_80160854(data->x6, Player_GetTeam(data->x6),
                      temp_r30->is_teams == 1,
                      temp_r30->player_standings[data->x4].slot_type);
    new_var = aobj;
    HSD_AObjSetCurrentFrame(new_var, 1.0F + tmp);
    HSD_AObjSetRate(aobj, 0.0F);
    HSD_MObjAnim(data->x20->u.dobj->mobj);
    HSD_AObjSetCurrentFrame(aobj, 0.0F);
    HSD_AObjSetRate(aobj, 1.0F);
    mn_8022F3D8(data->x20, 4, MOBJ_MASK);
    mn_8022F3D8(data->x20, 5, MOBJ_MASK);
    mn_8022F3D8(data->x20, 6, MOBJ_MASK);
    HSD_GObj_SetupProc(temp_r29, fn_80176BCC, 0);
    if (jobj == NULL) {
        jobj = NULL;
    } else {
        jobj = jobj->child;
    }

    for (i = 0; i < 4; i++) {
        HSD_JObjGetTranslation(jobj, &sp8[i]);
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->next;
        }
    }
    fn_80176D3C(sp8);
}

void fn_801771C0(ResultsData* data)
{
    MatchEnd* me;
    MatchPlayerData* p;
    MatchPlayerData* q;
    s32 result;
    s32 i;
    s32 j;
    u8 our_team;

    me = data->x94;
    data->x4 = fn_80165418(me);
    data->x5 = fn_801654A0(me);

    if (me->is_teams != 1) {
        data->x6 = data->x4;
        return;
    }

    p = me->player_standings;
    i = 0;
    do {
        if (p->slot_type == Gm_PKind_NA) {
            goto next_iter;
        }
        our_team = data->x5;
        if (p->team != our_team) {
            goto next_iter;
        }

        result = i;
        q = me->player_standings;
        for (j = 0; j < 4; j++, q++) {
            if (q->slot_type == Gm_PKind_NA) {
                continue;
            }
            if (q->team != our_team) {
                continue;
            }
            if (i == j) {
                continue;
            }
            if (p->is_small_loser > q->is_small_loser) {
                result = -1;
                break;
            }
        }

        if (result >= 0) {
            data->x6 = result;
            return;
        }

    next_iter:
        p++;
        i++;
    } while (i < 4);
}

extern HSD_Archive* lbl_804D65B8;

typedef struct ResultsMatchEndPlayerIter {
    u8 pad_0[0x58];
    u8 slot_type;
    s8 character_kind;
    s8 character_id;
    u8 x3 : 6;
    u8 x3_6 : 1;
    u8 x3_7 : 1;
    u8 pad_5C[0xA8 - 0x5C];
} ResultsMatchEndPlayerIter;

typedef struct ResultsDataPlayerIter {
    u8 pad_0[0xA0];
    HSD_GObj* fighter_gobj;
    HSD_GObj* camera;
    u8 pad_A8[0xD8 - 0xA8];
} ResultsDataPlayerIter;

static char lbl_804D3F70[] = "GmRst";
static char lbl_804D3F78[] = "pnlsce";
static char lbl_804D3F80[] = "flmsce";

void gm_80177368_OnEnter(void* arg0_)
{
    ResultsMatchInfo* arg0 = arg0_;
    HSD_GObj* temp_r3_2;
    HSD_LObj* temp_r3_3;
    HSD_GObj* temp_r3_4;
    MatchEnd* temp_r29;
    ResultsData* data = &lbl_8046DBE8;
    int i;

    PAD_STACK(0x20);

    memzero(&lbl_8046DBE8, 0x5A8);
    lbl_8046DBE8.x1 = 0;
    lbl_8046DBE8.x0_0 = false;
    lbl_8046DBE8.x94 = &arg0->match_end;
    lbl_8046DBE8.x0_4 = arg0->x0_0;
    lbl_8046DBE8.x0_5 = arg0->x0_1;

    temp_r29 = lbl_8046DBE8.x94;
    if (gm_801743A4(lbl_8046DBE8.x94->result)) {
        lbl_8046DBE8.num_pages = 2;
    } else {
        lbl_8046DBE8.num_pages = 3;
        if (temp_r29->x5 == 3) {
            lbl_8046DBE8.player_data[0].page = 2;
            lbl_8046DBE8.player_data[1].page = 2;
            lbl_8046DBE8.player_data[2].page = 2;
            lbl_8046DBE8.player_data[3].page = 2;
        }
    }
    if (fn_801701B8() == 0) {
        ResultsStatsInfo* stats_info = lbl_8046E190;
        for (i = 0; i < 4; i++, stats_info++) {
            stats_info->x0 = 2;
            stats_info->x1 = fn_80174284_noinline(i) * 2 + 2;
        }
    } else {
        for (i = 0; i < 4; i++) {
            lbl_8046E190[i].x0 = 2;
            lbl_8046E190[i].x1 = 0;
        }
    }
    fn_801771C0(&lbl_8046DBE8);
    if (temp_r29->player_standings[data->x6].slot_type == Gm_PKind_Human) {
        if (!gm_801743A4(temp_r29->result) &&
            temp_r29->player_standings[data->x6].x3_6)
        {
            lb_80014574(data->x6, 3, 0x20, 0);
        }
    }
    un_802FF1B4();
    lbl_804D65B8 = lbArchive_80016DBC(lbl_804D3F70, &data->pnlsce,
                                      lbl_804D3F78, &data->flmsce,
                                      lbl_804D3F80, 0);
    if (data->pnlsce == NULL) {
        OSReport(lbl_803D6898, lbl_804D3F70);
    }
    if (data->flmsce == NULL) {
        OSReport(lbl_803D6898, lbl_804D3F70);
    }
    fn_80176A6C();
    temp_r3_2 = GObj_Create(0xB, 3, 0);
    if (temp_r3_2 == NULL) {
        OSReport(lbl_803D6974);
        HSD_ASSERTMSG(0x68C, 0, (char*) &lbl_804D3FB0);
    }
    temp_r3_3 = lb_80011AC4(data->pnlsce->lights);
    if (temp_r3_3 == NULL) {
        OSReport(lbl_803D69A0);
        HSD_ASSERTMSG(0x68F, 0, (char*) &lbl_804D3FB0);
    }
    HSD_GObjObject_80390A70(temp_r3_2, (u8) HSD_GObj_804D784A, temp_r3_3);
    GObj_SetupGXLink(temp_r3_2, HSD_GObj_LObjCallback, 0xA, 0);
    temp_r3_4 = GObj_Create(0xE, 0xF, 0);
    data->x18 = temp_r3_4;
    if (temp_r3_4 == NULL) {
        OSReport(lbl_803D69CC);
        HSD_ASSERTMSG(0x6A2, 0, (char*) &lbl_804D3FB0);
    }
    HSD_GObj_SetupProc(temp_r3_4, fn_80179350, 0);
    fn_80176F60();
    fn_8017AA78(&arg0->x1);
    fn_8017A004();
    if (!gm_801743A4(temp_r29->result)) {
        lbAudioAx_80023F28(
            fn_80160400(temp_r29->player_standings[data->x6].character_kind));
    }

    {
        ResultsMatchEndPlayerIter* p =
            (ResultsMatchEndPlayerIter*) temp_r29;
        ResultsDataPlayerIter* result_data = (ResultsDataPlayerIter*) data;
        for (i = 0; i < 4; i++, p++, result_data++) {
            if (p->slot_type != Gm_PKind_NA) {
                fn_8017A9B4(i);
                result_data->fighter_gobj =
                    fn_8017A67C(p->character_kind, p->x3, i);
                result_data->camera = fn_8017A318(i);
            }
        }
    }
}

void gm_80177704_OnLeave(void* unused)
{
    fn_801701AC();
}
