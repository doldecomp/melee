#include "gmregclear.h"
#include <Runtime/platform.h>

#include <dolphin/pad.h>

#include "forward.h"

#include <melee/mn/inlines.h>

#include <sysdolphin/baselib/forward.h>

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/tobj.h>
#include <melee/cm/camera.h>
#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include "types.h"
#include <melee/if/ifnametag.h>
#include <melee/if/ifstock.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/pl/player.h>

typedef struct RegClearSpawnEntry {
    /* 0x00 */ s32 x0;
    /* 0x04 */ u8 x4;
    /* 0x05 */ u8 x5;
    /* 0x06 */ u8 x6;
    /* 0x07 */ u8 x7;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
} RegClearSpawnEntry;

typedef struct RegClearCharEntry {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 x1;
    /* 0x02 */ u8 x2;
    /* 0x03 */ u8 x3;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
} RegClearCharEntry;

typedef struct RegClearRecordState {
    /* 0x00 */ u8 x0;
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 x2;
    /* 0x04 */ int x4;
    /* 0x08 */ int x8;
    /* 0x0C */ int xC;
    /* 0x10 */ s8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 pad_12[2];
} RegClearRecordState;
ASSERT_SIZE(RegClearRecordState, 0x14);

typedef struct lbl_80472ED8_t {
    /* 0x000 */ s32 x0;
    /* 0x004 */ s32 x4;
    /* 0x008 */ s32 x8;
    /* 0x00C */ PlayerInitData xC;
    /* 0x030 */ u8 pad_30[0x24];
    /* 0x054 */ RegClearSpawnEntry x54[101];
    /* 0x6A4 */ RegClearSpawnEntry* x6A4;
    /* 0x6A8 */ RegClearSpawnEntry* x6A8;
    /* 0x6AC */ RegClearSpawnEntry* x6AC;
    /* 0x6B0 */ RegClearSpawnEntry* x6B0;
    /* 0x6B4 */ RegClearSpawnEntry* x6B4;
    /* 0x6B8 */ RegClearSpawnEntry* x6B8;
    /* 0x6BC */ RegClearRecordState record[0];
} lbl_80472ED8_t;
ASSERT_SIZE(lbl_80472ED8_t, 0x6BC);

typedef struct RegClearRecordOverlay {
    u8 pad[0x6BC];
    RegClearRecordState record[1];
} RegClearRecordOverlay;

typedef struct {
    /* 0x00 */ u32 scores[27];
    /* 0x6C */ u8 icons[28];
    /* 0x88 */ u16 times[28];
} RecordBlock; /* 0xC0 */

static RecordBlock lbl_803D8D08[6] = {
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
    { { 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF,
        0x0FFFFFFF, 0x0FFFFFFF } },
};

lbl_80472ED8_t lbl_80472ED8;
RegClearRecordState lbl_80473594;

int gm_80181A14(void)
{
    (void) &lbl_80472ED8;
    return lbl_80473594.x0;
}

u32 gm_80181A24(void)
{
    return lbl_80473594.x2;
}

s32 gm_80181A34(void)
{
    return lbl_80473594.x4;
}

void gm_80181A44(int c_kind, int arg1, bool arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].icons[c_kind] = arg2;
        break;
    case 0x22:
        base[1].icons[c_kind] = arg2;
        break;
    case 0x23:
        base[2].icons[c_kind] = arg2;
        break;
    case 0x24:
        base[3].icons[c_kind] = arg2;
        break;
    case 0x25:
        base[4].icons[c_kind] = arg2;
        break;
    case 0x26:
        base[5].icons[c_kind] = arg2;
        break;
    }
}

void gm_80181AC8(int c_kind, int arg1, u16 arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].times[c_kind] = arg2;
        break;
    case 0x22:
        base[1].times[c_kind] = arg2;
        break;
    case 0x23:
        base[2].times[c_kind] = arg2;
        break;
    case 0x24:
        base[3].times[c_kind] = arg2;
        break;
    case 0x25:
        base[4].times[c_kind] = arg2;
        break;
    case 0x26:
        base[5].times[c_kind] = arg2;
        break;
    }
}

void gm_80181B64(int c_kind, int arg1, s32 arg2)
{
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 0x21:
        base[0].scores[c_kind] = arg2;
        break;
    case 0x22:
        base[1].scores[c_kind] = arg2;
        break;
    case 0x23:
        base[2].scores[c_kind] = arg2;
        break;
    case 0x24:
        base[3].scores[c_kind] = arg2;
        break;
    case 0x25:
        base[4].scores[c_kind] = arg2;
        break;
    case 0x26:
        base[5].scores[c_kind] = arg2;
        break;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
int fn_80181BFC(int* arg0)
{
    int i;
    int count = 0;

    for (i = 1; i < 6; i++) {
        if (Player_GetFalls(i) == 0 &&
            Player_GetPlayerSlotType(i) != Gm_PKind_NA)
        {
            count += 1;
        } else if (arg0 != NULL) {
            *arg0 = i;
        }
    }
    return count;
}
#ifdef MUST_MATCH
#pragma pop
#endif

static inline s32 fn_80181C80_CountPlayers(volatile s32* out)
{
    s32 i;
    s32 count = 0;

    for (i = 1; i < 6; i++) {
        if (Player_GetFalls(i) == 0 &&
            Player_GetPlayerSlotType(i) != Gm_PKind_NA)
        {
            count++;
        } else {
            *out = i;
        }
    }
    return count;
}

void fn_80181C80(s32 arg0)
{
    lbl_80472ED8_t* data = &lbl_80472ED8;
    s32 count;
    volatile s32 sp38;
    volatile s32 sp3C;
    PlayerInitData sp10;

    gm_GetCurrentGameMode();
    sp10 = data->xC;
    count = fn_80181C80_CountPlayers(&sp38);

    if (data->x54[arg0].x4 > count && data->x8 > 0x5A) {
        if (Player_GetPlayerSlotType(sp38) != Gm_PKind_NA) {
            Player_SetFalls(sp38, 0);
            Player_SetSuicideCount(sp38, 0);
            fn_8016EF98(sp38);
        }
        data->x54[arg0].x0 = -2;
        sp10.team = !Player_GetTeam(0);
        sp10.ckind = data->x54[arg0].x5;
        sp10.cpu_level = data->x54[arg0].x6;
        sp10.cpu_kind = data->x54[arg0].x7;
        sp10.x18 = data->x54[arg0].x8;
        sp10.x1C = data->x54[arg0].xC;
        gm_8016EDDC(sp38, &sp10);
        Player_SetNametagSlotID(sp38, 0x78);
        un_802FD28C(sp38);
        data->x0++;
    }
}

static inline s32 fn_80181E18_ComputeRemaining100(const s32* x4, s32 count)
{
    return 0x64 - (count + *x4);
}

void fn_80181E18(void)
{
    lbl_80472ED8_t* data = &lbl_80472ED8;
    s32* x4;
    s32* field;
    RegClearSpawnEntry* entry;
    RegClearSpawnEntry* entries;
    s32 entry_idx;
    s32 next;
    s32 temp;
    s32 count;
    s32 i;
    s32 mode = gm_GetCurrentGameMode();

    field = &data->x8;
    if (data->x8 <= 0x5A) {
        *field += 1;
    }

    switch (mode) {
    case 0x21:
    case 0x22:
        Player_GetFalls(0);
        break;
    case 0x23:
    case 0x24:
        if (gm_8016AEEC() == 0 && gm_8016AEFC() == 0x3B) {
            data->record[0].x0 = 1;
            gm_8016B33C(7);
            gm_8016B328();
        }
        break;
    case 0x25:
    case 0x26:
        if (Player_GetFalls(0) != 0) {
            gm_8016B33C(5);
            gm_8016B328();
        }
        break;
    }

    entry = data->x54;
    for (entry_idx = 0; entry_idx < 101; entry++, entry_idx++) {
        if (entry->x0 == -2) {
            continue;
        }

        switch (data->record[0].x8) {
        case 0x21:
        case 0x22:
            data->record[0].x4 = gm_8016AEDC();
            break;
        }

        temp = entry_idx - fn_80181BFC(NULL);
        if (temp < 0) {
            temp = 0;
        }
        field = &data->x4;
        x4 = field;
        next = *x4;
        data->record[0].x2 = (s16) (temp + next);

        switch (mode) {
        case 0x21:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(0xA - (temp + *x4));
            break;
        case 0x22:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(fn_80181E18_ComputeRemaining100(x4, temp));
            break;
        default:
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(temp + *x4);
            break;
        }

        next = data->x54[entry_idx].x0;

        if (next == -1) {
            fn_80181C80(entry_idx);
            return;
        }

        if (next == 0x3E7) {
            count = 0;
            for (i = 1; i < 6; i++) {
                if (Player_GetFalls(i) == 0 &&
                    Player_GetPlayerSlotType(i) != Gm_PKind_NA)
                {
                    count += 1;
                }
            }
            if (count == 0) {
                data->record[0].x0 = 1;
                gm_8016B33C(7);
                gm_8016B328();
            }
        } else {
            s32 k;
            entries = data->x54;
            for (k = next; k < entry_idx; k++) {
                entries[k].x0 = -1;
                *x4 += 1;
            }
            fn_80181C80(data->x54[entry_idx].x0);
            temp = entry_idx - fn_80181BFC(NULL);
            if (temp < 0) {
                temp = 0;
            }
            ifStock_802FA2D0(temp + *x4);
        }
        break;
    }
    PAD_STACK(8);
}

void gm_80182174(void)
{
    s32 i;
    RegClearSpawnEntry* src;
    RegClearSpawnEntry* dst;
    RegClearSpawnEntry** spawn_table_22;
    RegClearSpawnEntry** spawn_table_23;
    RegClearSpawnEntry** spawn_table_24;
    RegClearSpawnEntry** spawn_table_25;
    RegClearSpawnEntry** spawn_table_26;
    s32 mode;

    mode = gm_GetCurrentGameMode();

    lbArchive_80016DBC(
        "GmKumite.dat", &lbl_80472ED8.x6A4, "gmKumiteSystemTable10man",
        (spawn_table_22 = &lbl_80472ED8.x6A8), "gmKumiteSystemTable100man",
        (spawn_table_23 = &lbl_80472ED8.x6AC), "gmKumiteSystemTable10min",
        (spawn_table_24 = &lbl_80472ED8.x6B0), "gmKumiteSystemTable60min",
        (spawn_table_25 = &lbl_80472ED8.x6B4), "gmKumiteSystemTableEndless",
        (spawn_table_26 = &lbl_80472ED8.x6B8),
        "gmKumiteSystemTableMercilessly", 0);

    lbl_80472ED8.x0 = 0;
    lbl_80472ED8.x4 = 0;
    lbl_80472ED8.x8 = 0;

    gm_SetupPlayerDefaults(&lbl_80472ED8.xC);

    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.ckind = CKIND_BOY;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.slot_type = 1;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.stocks = 1;
    ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->xC.xD_b4 = 1;

    switch (mode) {
    case 0x21:
        src = ((volatile lbl_80472ED8_t*) &lbl_80472ED8)->x6A4;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x22:
        src = *spawn_table_22;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x23:
        src = *spawn_table_23;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x24:
        src = *spawn_table_24;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x25:
        src = *spawn_table_25;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    case 0x26:
        src = *spawn_table_26;
        dst = lbl_80472ED8.x54;
        for (i = 0; i < 101; i++) {
            dst->x0 = src->x0;
            dst->x4 = src->x4;
            dst->x5 = src->x5;
            dst->x8 = src->x8;
            dst->xC = src->xC;
            dst->x6 = src->x6;
            dst->x7 = src->x7;
            if (src->x0 == 0x3E7) {
                break;
            }
            src++;
            dst++;
        }
        break;
    }

    lbl_80473594.x10 = Player_GetPlayerId(0);
    lbl_80473594.x11 = Player_GetNametagSlotID(0);
    HSD_GObj_SetupProc(GObj_Create(0xFU, 0x11U, 0U),
                       (HSD_GObjEvent) fn_80181E18, 0x15U);
    gm_80168F88();
    PAD_STACK(8);
}

bool gm_IsMultimanSmashMode(void)
{
    switch (gm_GetCurrentGameMode()) {
    case GM_10MAN_VS:
    case GM_100MAN_VS:
    case GM_3MIN_VS:
    case GM_15MIN_VS:
    case GM_ENDLESS_VS:
    case GM_CRUEL_VS:
        return true;
    }
    return false;
}

/// @todo Original addresses these fields relative to #lbl_80472ED8 (reference
/// relocations are lbl_80472ED8+0x6BC..+0x6C8): lbl_80473594 overlays
/// lbl_80472ED8+0x6BC (0x80472ED8 + 0x6BC == 0x80473594), and gm_80182578
/// below already reads the same storage via lbl_80473594.
void gm_80182554(int arg0, int arg1)
{
    typedef struct {
        u8 pad_0[0x6BC];
        u8 x6BC;
        u8 pad_6BD;
        u16 x6BE;
        int x6C0;
        int x6C4;
        int x6C8;
    } regclear_record_state;
    regclear_record_state* s = (regclear_record_state*) &lbl_80472ED8;

    s->x6C8 = arg0;
    s->x6C4 = arg1;
    s->x6BC = 0;
    s->x6C0 = 0;
    s->x6BE = 0;
}

static inline u16 gm_80182578_GetTimeFromData(RegClearRecordOverlay* data)
{
    return data->record[0].x2;
}

static inline int gm_80182578_GetRecordTime(RecordBlock* blocks, int idx,
                                            int mode)
{
    switch (mode) {
    case 33:
        return blocks[0].times[idx];
    case 34:
        return blocks[1].times[idx];
    case 35:
        return blocks[2].times[idx];
    case 36:
        return blocks[3].times[idx];
    case 37:
        return blocks[4].times[idx];
    case 38:
        return blocks[5].times[idx];
    default:
        return 0;
    }
}

static inline u32 gm_80182578_GetRecordScore(RecordBlock* blocks, int idx,
                                             int mode)
{
    switch (mode) {
    case 33:
        return blocks[0].scores[idx];
    case 34:
        return blocks[1].scores[idx];
    case 35:
        return blocks[2].scores[idx];
    case 36:
        return blocks[3].scores[idx];
    case 37:
        return blocks[4].scores[idx];
    case 38:
        return blocks[5].scores[idx];
    default:
        return 0;
    }
}

static inline int gm_80182578_GetIndexFromPointer(const int* idx_ptr)
{
    return *idx_ptr;
}

inline void gm_80182578_SetTime(RecordBlock* blocks, int idx, int mode,
                                u16 value)
{
    switch (mode) {
    case 33:
        blocks[0].times[idx] = value;
        break;
    case 34:
        blocks[1].times[idx] = value;
        break;
    case 35:
        blocks[2].times[idx] = value;
        break;
    case 36:
        blocks[3].times[idx] = value;
        break;
    case 37:
        blocks[4].times[idx] = value;
        break;
    case 38:
        blocks[5].times[idx] = value;
        break;
    }
}

void gm_80182578(void)
{
    RegClearRecordOverlay* data = (RegClearRecordOverlay*) &lbl_80472ED8;
    int* idx_ptr;
    int* mode_ptr;
    RecordBlock* blocks;
    int time_val;
    int idx;
    s32 mode;
    u32 score_val;

    mode_ptr = &data->record[0].x8;
    idx_ptr = &data->record[0].xC;
    blocks = lbl_803D8D08;
    mode = data->record[0].x8;
    idx = gm_80182578_GetIndexFromPointer(idx_ptr);
    time_val = gm_80182578_GetRecordTime(blocks, idx, mode);

    score_val = gm_80182578_GetRecordScore(blocks, idx, mode);

    switch (mode) {
    case 0x21:
    case 0x22:
        if (mode == 0x21) {
            mode = gmMainLib_8015D6BC(gm_CKindToSelKind((u8) idx));
        } else {
            mode = gmMainLib_8015D710(gm_CKindToSelKind((u8) idx));
        }
        if (data->record[0].x0 != 0) {
            u32 score_store = (u32) data->record[0].x4;
            if (score_store < score_val) {
                int i = gm_80182578_GetIndexFromPointer(idx_ptr);
                int m = *mode_ptr;
                switch (m) {
                case 33:
                    blocks[0].icons[i] = data->record[0].x0;
                    break;
                case 34:
                    blocks[1].icons[i] = data->record[0].x0;
                    break;
                case 35:
                    blocks[2].icons[i] = data->record[0].x0;
                    break;
                case 36:
                    blocks[3].icons[i] = data->record[0].x0;
                    break;
                case 37:
                    blocks[4].icons[i] = data->record[0].x0;
                    break;
                case 38:
                    blocks[5].icons[i] = data->record[0].x0;
                    break;
                }
                switch (m) {
                case 33:
                    blocks[0].scores[i] = score_store;
                    break;
                case 34:
                    blocks[1].scores[i] = score_store;
                    break;
                case 35:
                    blocks[2].scores[i] = score_store;
                    break;
                case 36:
                    blocks[3].scores[i] = score_store;
                    break;
                case 37:
                    blocks[4].scores[i] = score_store;
                    break;
                case 38:
                    blocks[5].scores[i] = score_store;
                    break;
                }
                gm_80182578_SetTime(blocks, i, m, data->record[0].x2);
            }
        } else if ((s32) data->record[0].x2 > (s32) time_val && mode == 0) {
            int i = *idx_ptr;
            int m = *mode_ptr;
            switch (m) {
            case 33:
                blocks[0].times[i] = data->record[0].x2;
                break;
            case 34:
                blocks[1].times[i] = data->record[0].x2;
                break;
            case 35:
                blocks[2].times[i] = data->record[0].x2;
                break;
            case 36:
                blocks[3].times[i] = data->record[0].x2;
                break;
            case 37:
                blocks[4].times[i] = data->record[0].x2;
                break;
            case 38:
                blocks[5].times[i] = data->record[0].x2;
                break;
            }
        }
        break;
    case 0x23:
    case 0x24:
        if (data->record[0].x0 != 0) {
            u16 time_store = gm_80182578_GetTimeFromData(data);
            if ((s32) time_store > (s32) time_val) {
                switch (mode) {
                case 33:
                    blocks[0].icons[idx] = data->record[0].x0;
                    break;
                case 34:
                    blocks[1].icons[idx] = data->record[0].x0;
                    break;
                case 35:
                    blocks[2].icons[idx] = data->record[0].x0;
                    break;
                case 36:
                    blocks[3].icons[idx] = data->record[0].x0;
                    break;
                case 37:
                    blocks[4].icons[idx] = data->record[0].x0;
                    break;
                case 38:
                    blocks[5].icons[idx] = data->record[0].x0;
                    break;
                }
                switch (mode) {
                case 33:
                    blocks[0].times[idx] = time_store;
                    break;
                case 34:
                    blocks[1].times[idx] = time_store;
                    break;
                case 35:
                    blocks[2].times[idx] = time_store;
                    break;
                case 36:
                    blocks[3].times[idx] = time_store;
                    break;
                case 37:
                    blocks[4].times[idx] = time_store;
                    break;
                case 38:
                    blocks[5].times[idx] = time_store;
                    break;
                }
            }
        }
        break;
    case 0x25:
    case 0x26:
        if ((s32) data->record[0].x2 > (s32) time_val) {
            switch (mode) {
            case 33:
                blocks[0].times[idx] = data->record[0].x2;
                break;
            case 34:
                blocks[1].times[idx] = data->record[0].x2;
                break;
            case 35:
                blocks[2].times[idx] = data->record[0].x2;
                break;
            case 36:
                blocks[3].times[idx] = data->record[0].x2;
                break;
            case 37:
                blocks[4].times[idx] = data->record[0].x2;
                break;
            case 38:
                blocks[5].times[idx] = data->record[0].x2;
                break;
            }
        }
        break;
    }

    PAD_STACK(0x38);
}

static inline RecordBlock* fn_80182B5C_GetRecordBlocks(void)
{
    return lbl_803D8D08;
}

static inline u32 fn_80182B5C_GetScore(RecordBlock* blocks,
                                       RegClearRecordOverlay* data)
{
    int idx = data->record[0].xC;
    int mode = data->record[0].x8;

    switch (mode) {
    case 33:
        return blocks[0].scores[idx];
    case 34:
        return blocks[1].scores[idx];
    case 35:
        return blocks[2].scores[idx];
    case 36:
        return blocks[3].scores[idx];
    case 37:
        return blocks[4].scores[idx];
    case 38:
        return blocks[5].scores[idx];
    default:
        return 0;
    }
}

static inline int fn_80182B5C_GetTime(RecordBlock* blocks,
                                      RegClearRecordOverlay* data)
{
    int idx = data->record[0].xC;
    int mode = data->record[0].x8;

    switch (mode) {
    case 33:
        return blocks[0].times[idx];
    case 34:
        return blocks[1].times[idx];
    case 35:
        return blocks[2].times[idx];
    case 36:
        return blocks[3].times[idx];
    case 37:
        return blocks[4].times[idx];
    case 38:
        return blocks[5].times[idx];
    default:
        return 0;
    }
}

void fn_80182B5C(void)
{
    RegClearRecordOverlay* data = (RegClearRecordOverlay*) &lbl_80472ED8;
    RecordBlock* blocks = fn_80182B5C_GetRecordBlocks();
    int time;
    int idx = data->record[0].xC;
    u32 score;
    int mode = data->record[0].x8;

    time = fn_80182B5C_GetTime(blocks, data);
    score = fn_80182B5C_GetScore(blocks, data);

    switch (mode) {
    case 0x21:
    case 0x22:
        if (mode == 0x21) {
            gmMainLib_8015D6BC(gm_CKindToSelKind((u8) idx));
        } else {
            gmMainLib_8015D710(gm_CKindToSelKind((u8) idx));
        }
        if (data->record[0].x0 != 0) {
            if ((u32) data->record[0].x4 < score) {
                gm_8016B350(0x9C40);
                gm_8016B364(0x144);
                gm_80167858((s32) data->record[0].x10,
                            (s32) data->record[0].x11, 0xD, 0x5A);
            }
        } else {
            gm_8016B364(0x148);
            gm_8016B378(0x28);
        }
        break;
    case 0x23:
    case 0x24:
        if (data->record[0].x0 != 0 && (s32) data->record[0].x2 > time) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) data->record[0].x10, (s32) data->record[0].x11,
                        0xD, 0x5A);
        }
        break;
    case 0x25:
    case 0x26:
        if ((s32) data->record[0].x2 > time) {
            gm_8016B350(0x9C40);
            gm_8016B364(0x144);
            gm_80167858((s32) data->record[0].x10, (s32) data->record[0].x11,
                        0xD, 0x5A);
        }
        break;
    }
}

static UnkMultimanData lbl_804D65E0;

UnkMultimanData* gm_80182DF0(int c_kind, int arg1)
{
    UnkMultimanData* result = &lbl_804D65E0;
    RecordBlock* base = lbl_803D8D08;

    switch (arg1) {
    case 33:
        result->x0_0 = base[0].icons[c_kind];
        result->x2 = base[0].times[c_kind];
        result->x4 = base[0].scores[c_kind];
        break;
    case 34:
        result->x0_0 = base[1].icons[c_kind];
        result->x2 = base[1].times[c_kind];
        result->x4 = base[1].scores[c_kind];
        break;
    case 35:
        result->x0_0 = base[2].icons[c_kind];
        result->x2 = base[2].times[c_kind];
        break;
    case 36:
        result->x0_0 = base[3].icons[c_kind];
        result->x2 = base[3].times[c_kind];
        break;
    case 37:
        result->x0_0 = base[4].icons[c_kind];
        result->x2 = base[4].times[c_kind];
        break;
    case 38:
        result->x0_0 = base[5].icons[c_kind];
        result->x2 = base[5].times[c_kind];
        break;
    }
    return result;
}

u8 lbl_804D65E8;

void fn_80182F40(HSD_GObj* unused)
{
    int i;
    int temp_r31;
    int temp_r31_2;

    if (gm_GetButtonsTriggered(PAD_MAX_CONTROLLERS) &
        (HSD_PAD_START | HSD_PAD_A))
    {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        sfxForward();
        gm_801A4B60();
        gm_SetPendingGameMode(GM_TITLE);
        gm_SetNewGameModePending();
        return;
    }
    if (gm_801A4BA8() >= 0x4B0) {
        lbAudioAx_80024C84();
        lbAudioAx_80023694();
        if (gm_GetCurrentSceneIndex() == 3 && gmMainLib_8015DB00() % 2 == 0) {
            gmMainLib_8015DB18();
            gm_SetNextGameModeStateId(0);
        }
        gm_801A4B60();
        return;
    }
    switch (lbl_804D65E8) {
    case 0:
        if (gm_801A4BA8() == 0x190) {
            lbl_804D65E8 = 1;
            temp_r31 = gm_801BF6D8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6D8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
                Player_SetMoreFlagsBit4(i, 1);
            }
        }
        break;
    case 1:
        if (gm_801A4BA8() == 0x280 || Player_800368F8(gm_801BF6D8()) == 0) {
            lbl_804D65E8 = 2;
            temp_r31_2 = gm_801BF6F8();
            Camera_8002EEC8(60.0F);
            Camera_8002E6FC(temp_r31_2);
            Camera_8002ED9C(30.0F);
            Camera_8002EC7C(0.017453292F * (HSD_Randi(0x47) - 0x23));
            Camera_8002EB5C(0.017453292F * HSD_Randi(0x10));
            Player_SetPlayerAndEntityCpuLevel(gm_801BF6F8(), 9);
            for (i = 0; i < 4; i++) {
                if (i != gm_801BF6F8()) {
                    Player_SetPlayerAndEntityCpuLevel(i, 2);
                }
            }
        }
        break;
    case 2:
        if (gm_801A4BA8() == 0x370 || Player_800368F8(gm_801BF6F8()) == 0) {
            Camera_SetModeToStandard();
            for (i = 0; i < 4; i++) {
                Player_SetPlayerAndEntityCpuLevel(i, 9);
                Player_SetMoreFlagsBit4(i, 0);
            }
        }
        break;
    case 3:
        break;
    }
}

void gm_80183218(void)
{
    lbl_804D65E8 = 0;
    HSD_GObj_SetupProc(GObj_Create(0xF, 0x11, 0), fn_80182F40, 0x15);
}
