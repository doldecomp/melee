#include "gmtou_1.h"

#include "gm_1601.h"
#include "gm_1A3F.h"
#include "gm_1A45.h"
#include "gm_unsplit.h"
#include "gmtou_1.h"
#include "gmtoulib.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/fog.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbdvd.h"
#include "lb/types.h"
#include "mn/mnmain.h"
#include "sc/types.h"

#include <printf.h>
#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/particle.h>
#include <baselib/random.h>
#include <baselib/sislib.h>

/* 4799D8 */ struct Lbl804799D8_t lbl_804799D8;
/* 4799B8 */ struct Lbl804799B8_t lbl_804799B8;
/* 4D6670 */ extern SceneDesc* lbl_804D6670;

/* 3DA0D0 */ struct lbl_803DA0D0_t lbl_803DA0D0 = {
    0,  1,  2,  3,  5,  6,  12, 6,  6,  7,  9,  8,  6,  9,  4,  9,  10, 11, 12,
    2,  12, 6,  7,  9,  12, 0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  3,  3,  0,
    0,  0,  5,  6,  4,  0,  0,  0,  6,  7,  6,  10, 0,  0,  12, 13, 8,  12, 0,
    0,  14, 15, 12, 18, 21, 0,  23, 24, 16, 24, 28, 0,  30, 31, 24, 36, 42, 46,
    48, 49, 32, 48, 56, 60, 62, 63, 2,  0,  0,  0,  0,  3,  3,  0,  0,  0,  0,
    4,  4,  0,  0,  0,  6,  7,  6,  0,  0,  0,  8,  9,  9,  0,  0,  0,  12, 13,
    2,  0,  0,  0,  0,  3,  3,  0,  0,  0,  0,  4,  4,  0,  0,  0,  0,  5,  4,
    0,  0,  0,  6,  7,  5,  0,  0,  0,  7,  8,  6,  0,  0,  0,  8,  9,  7,  0,
    0,  0,  9,  10, 8,  0,  0,  0,  10, 11, 8,  12, 0,  0,  14, 15, 9,  0,  0,
    0,  12, 13, 10, 0,  0,  0,  14, 15, 11, 0,  0,  0,  15, 16, 12, 0,  0,  0,
    16, 17, 13, 0,  0,  0,  17, 18, 14, 0,  0,  0,  18, 19, 15, 0,  0,  0,  19,
    20, 16, 0,  0,  0,  20, 21, 16, 20, 0,  0,  22, 23
};

/* 4D4190 */ static s32 lbl_804D4190 = 0xFFFFFFFF;
/* 4D4194 */ static s32 lbl_804D4194 = -1;

/* 4D663C */ HSD_GObj* lbl_804D663C;

void fn_80196510(void)
{
    int stage;

    gm_8018F634();

    while (1) {
        stage = fn_8018F4A0();
        lbl_804D4190 = stage;
        if (lbl_804D4194 != lbl_804D4190) {
            break;
        }
        if (fn_801642A0() != 0) {
            break;
        }
    }

    lbl_804D4194 = lbl_804D4190;
}

s32 fn_8019655C(void)
{
    return lbl_804D4190;
}

bool fn_80196564(TmData* arg0)
{
    if ((arg0->stage_selection_type == 0 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 1)
    {
        return true;
    }
    return false;
}

bool fn_80196594(TmData* arg0)
{
    if ((arg0->stage_selection_type == 2 && arg0->x32 == 0) ||
        arg0->stage_selection_type == 3)
    {
        return true;
    }
    return false;
}

void fn_801965C4(void)
{
    TmData* temp_r3;
    int temp_r4;

    temp_r3 = gm_8018F634();
    temp_r3->x2D = 1;
    temp_r4 = temp_r3->stage_selection_type;

    if (fn_80196594(temp_r3)) {
        temp_r3->x32 = 1;
        gm_SetPendingScene(3);
        gm_801A4B60();
        return;
    }
    if (fn_80196564(temp_r3)) {
        temp_r3->x32 = 1;
        temp_r3->x28 = lbl_804D4190;
    }
    gm_SetPendingScene(4);
    gm_801A4B60();
}

/// Randomly assigns bracket positions for tournament seeding.
void fn_80196684(s32 bracket_idx)
{
    s32 rand_val = HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                             lbl_80473AB8[bracket_idx].x7D +
                             lbl_80473AB8[bracket_idx].xA9);

    if (rand_val < (s32) lbl_80473AB8[bracket_idx].x51) {
        lbl_80473AB8[bracket_idx].x4C = 0;
        if (HSD_Randi(lbl_80473AB8[bracket_idx].x7D +
                      lbl_80473AB8[bracket_idx].xA9) <
            (s32) lbl_80473AB8[bracket_idx].x7D)
        {
            lbl_80473AB8[bracket_idx].x78 = 1;
            lbl_80473AB8[bracket_idx].xA4 = 2;
            return;
        }
        lbl_80473AB8[bracket_idx].x78 = 2;
        lbl_80473AB8[bracket_idx].xA4 = 1;
        return;
    }
    if (rand_val <
        (s32) (lbl_80473AB8[bracket_idx].x51 + lbl_80473AB8[bracket_idx].x7D))
    {
        lbl_80473AB8[bracket_idx].x78 = 0;
        if (HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                      lbl_80473AB8[bracket_idx].xA9) <
            (s32) lbl_80473AB8[bracket_idx].x51)
        {
            lbl_80473AB8[bracket_idx].x4C = 1;
            lbl_80473AB8[bracket_idx].xA4 = 2;
            return;
        }
        lbl_80473AB8[bracket_idx].x4C = 2;
        lbl_80473AB8[bracket_idx].xA4 = 1;
        return;
    }
    lbl_80473AB8[bracket_idx].xA4 = 0;
    if (HSD_Randi(lbl_80473AB8[bracket_idx].x51 +
                  lbl_80473AB8[bracket_idx].x7D) <
        (s32) lbl_80473AB8[bracket_idx].x51)
    {
        lbl_80473AB8[bracket_idx].x4C = 1;
        lbl_80473AB8[bracket_idx].x78 = 2;
        return;
    }
    lbl_80473AB8[bracket_idx].x4C = 2;
    lbl_80473AB8[bracket_idx].x78 = 1;
}

void fn_801967E0(s32 arg0)
{
    s32 rand;
    rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D +
                     lbl_80473AB8[arg0].xA9 + lbl_80473AB8[arg0].xD5);

    if (rand < (s32) lbl_80473AB8[arg0].x51) {
        lbl_80473AB8[arg0].x4C = 0;
        rand = HSD_Randi(lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xA9 +
                         lbl_80473AB8[arg0].xD5);
        if (rand < (s32) lbl_80473AB8[arg0].x7D) {
            lbl_80473AB8[arg0].x78 = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].xA9 + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].xA9) {
                lbl_80473AB8[arg0].xA4 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].xA4 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        if (rand < (s32) (lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xA9)) {
            lbl_80473AB8[arg0].xA4 = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].x7D) {
                lbl_80473AB8[arg0].x78 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].x78 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xA9);
        if (rand < (s32) lbl_80473AB8[arg0].xA9) {
            lbl_80473AB8[arg0].x78 = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return;
        }
        lbl_80473AB8[arg0].x78 = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return;
    }

    if (rand < (s32) (lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D)) {
        lbl_80473AB8[arg0].x78 = 0;
        rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xA9 +
                         lbl_80473AB8[arg0].xD5);
        if (rand < (s32) lbl_80473AB8[arg0].x51) {
            lbl_80473AB8[arg0].x4C = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].xA9 + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].xA9) {
                lbl_80473AB8[arg0].xA4 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].xA4 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        if (rand < (s32) (lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xA9)) {
            lbl_80473AB8[arg0].xA4 = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].x51) {
                lbl_80473AB8[arg0].x4C = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].x4C = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xA9);
        if (rand < (s32) lbl_80473AB8[arg0].x51) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return;
    }

    if (rand < (s32) (lbl_80473AB8[arg0].xA9 +
                      (lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D)))
    {
        lbl_80473AB8[arg0].xA4 = 0;
        rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D +
                         lbl_80473AB8[arg0].xD5);
        if (rand < (s32) lbl_80473AB8[arg0].x51) {
            lbl_80473AB8[arg0].x4C = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].x7D) {
                lbl_80473AB8[arg0].x78 = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].x78 = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        if (rand < (s32) (lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D)) {
            lbl_80473AB8[arg0].x78 = 1;
            rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xD5);
            if (rand < (s32) lbl_80473AB8[arg0].x51) {
                lbl_80473AB8[arg0].x4C = 2;
                lbl_80473AB8[arg0].xD0 = 3;
                return;
            }
            lbl_80473AB8[arg0].x4C = 3;
            lbl_80473AB8[arg0].xD0 = 2;
            return;
        }
        lbl_80473AB8[arg0].xD0 = 1;
        rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D);
        if (rand < (s32) lbl_80473AB8[arg0].x51) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].x78 = 3;
            return;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].x78 = 2;
        return;
    }

    lbl_80473AB8[arg0].xD0 = 0;
    rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D +
                     lbl_80473AB8[arg0].xA9);
    if (rand < (s32) lbl_80473AB8[arg0].x51) {
        lbl_80473AB8[arg0].x4C = 1;
        rand = HSD_Randi(lbl_80473AB8[arg0].x7D + lbl_80473AB8[arg0].xA9);
        if (rand < (s32) lbl_80473AB8[arg0].x7D) {
            lbl_80473AB8[arg0].x78 = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return;
        }
        lbl_80473AB8[arg0].x78 = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return;
    }
    if (rand < (s32) (lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D)) {
        lbl_80473AB8[arg0].x78 = 1;
        rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].xA9);
        if (rand < (s32) lbl_80473AB8[arg0].x51) {
            lbl_80473AB8[arg0].x4C = 2;
            lbl_80473AB8[arg0].xA4 = 3;
            return;
        }
        lbl_80473AB8[arg0].x4C = 3;
        lbl_80473AB8[arg0].xA4 = 2;
        return;
    }
    lbl_80473AB8[arg0].xA4 = 1;
    rand = HSD_Randi(lbl_80473AB8[arg0].x51 + lbl_80473AB8[arg0].x7D);
    if (rand < (s32) lbl_80473AB8[arg0].x51) {
        lbl_80473AB8[arg0].x4C = 2;
        lbl_80473AB8[arg0].x78 = 3;
        return;
    }
    lbl_80473AB8[arg0].x4C = 3;
    lbl_80473AB8[arg0].x78 = 2;
    return;
}

#pragma push
#pragma dont_inline on
s32 fn_80196CF8(void)
{
    TmData* tmdata;
    s32 x24;
    s32 result;
    s32 entrants;
    s32 i;

    tmdata = gm_8018F634();
    entrants = tmdata->entrants;
    x24 = tmdata->x24;

    result = 0;
    if (x24 > (s32) lbl_803DA0D0.rank_thresholds[entrants][5]) {
        return 6;
    }

    for (i = 5; i >= 0; i--) {
        if (x24 <= (s32) lbl_803DA0D0.rank_thresholds[entrants][i]) {
            result = i;
        }
    }

    return result;
}
#pragma pop

/// Cycles animation frame counter and updates JObj animation.
void fn_80196DBC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u16* counter = &lbl_804799D8.x10;

    jobj = gobj->hsd_obj;
    if (*counter > 0x320U) {
        *counter = 0;
    }
    fn_8019044C(jobj, (f32) *counter);
    *counter = *counter + 1;
}

/// Updates the tournament UI animation frame counter.
void fn_80196E30(HSD_GObj* gobj)
{
    u8* base_ptr;
    s32 cur_option;
    HSD_JObj* jobj;
    u8* x1A_ptr;
    u8 val;

    base_ptr = (u8*) &lbl_804799D8;
    cur_option = gm_8018F634()->cur_option;
    jobj = gobj->hsd_obj;

    if (cur_option <= 0x1A || cur_option >= 0x1F) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x77U) {
            *x1A_ptr = 0x5A;
        }
    } else if (cur_option <= 0x1E) {
        if ((u8) * (x1A_ptr = base_ptr + 0x1A) > 0x9FU) {
            *x1A_ptr = 0x82;
        }
    }

    val = *(base_ptr += 0x1A);
    fn_8019044C(jobj, (f32) val);
    *base_ptr = *base_ptr + 1;
}

/// Tournament mode JObj visibility/animation callback.
void fn_80196EEC(HSD_GObj* gobj)
{
    TmData* tmdata;
    HSD_JObj* jobj;
    u8* counter;
    int in_range;

    tmdata = gm_8018F634();
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x1B;

    if (*counter != 0) {
        *counter = *counter - 1;
        HSD_JObjAnimAll(jobj);
        if (tmdata->x33 == tmdata->pad_x34[0]) {
            if (*counter > 2) {
                *counter = 2;
            }
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        if (tmdata->cur_option == 0x14) {
            tmdata->cur_option = 0x15;
        }
    }
}

typedef struct TmPlayerAnimFrames {
    u16 start;
    u16 end;
    u16 loop;
} TmPlayerAnimFrames;
STATIC_ASSERT(sizeof(TmPlayerAnimFrames) == 6);

typedef union TmPlayerAnimFrameTable {
    s32 words[9];
    TmPlayerAnimFrames states[6];
} TmPlayerAnimFrameTable;
STATIC_ASSERT(sizeof(TmPlayerAnimFrameTable) == sizeof(s32) * 9);

extern TmPlayerAnimFrameTable lbl_803B7CE0;

void fn_80196FFC(HSD_GObj* gobj)
{
    TmPlayerAnimFrameTable table;
    TmData* tm;
    HSD_JObj* jobj;
    s32 pnum;
    s32 in_range;
    f32 x;
    u8 players;
    u8 state;
    u8 start_frame, cur_frame, end_frame, loop_flag;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    {
        HSD_JObj* jobj_tmp = gobj->hsd_obj;
        jobj = jobj_tmp;
    }

    table = lbl_803B7CE0;

    if ((s32) gm_8018F634()->cur_option >= 0x1B &&
        (s32) gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        (u8) tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 0.0f, 0.0f);
        return;
    }

    state = lbl_804799D8.x2A[pnum].state;
    if (state == 4) {
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 0.0f, 0.0f);
    } else {
        HSD_SisLib_803A7548(tm->x524[2], (s32) pnum, 1.0f, 1.0f);
    }

    players = tm->x30;
    if ((s32) players == 4) {
        x = (13.0f * (f32) pnum) + -19.5f;
    } else if ((s32) players == 3) {
        x = 6.5f + ((13.0f * (f32) pnum) - 19.5f);
    } else {
        x = 6.5f + ((13.0f * (2.0f * (f32) pnum)) - 19.5f);
    }

    HSD_JObjSetTranslateX(jobj, x);

    tm->x524[2]->hidden = 0;

    lbl_804799D8.x2A[pnum].start =
        table.states[lbl_804799D8.x2A[pnum].state].start;
    lbl_804799D8.x2A[pnum].end =
        table.states[lbl_804799D8.x2A[pnum].state].end;
    lbl_804799D8.x2A[pnum].loop =
        table.states[lbl_804799D8.x2A[pnum].state].loop;

    if (lbl_804799D8.x2A[pnum].cur < lbl_804799D8.x2A[pnum].start) {
        lbl_804799D8.x2A[pnum].cur = lbl_804799D8.x2A[pnum].start;
    }

    if (lbl_804799D8.x2A[pnum].cur < lbl_804799D8.x2A[pnum].end) {
        lbl_804799D8.x2A[pnum].cur++;
    } else {
        lbl_804799D8.x2A[pnum].done = 1;
        if (lbl_804799D8.x2A[pnum].loop != 0) {
            lbl_804799D8.x2A[pnum].cur = lbl_804799D8.x2A[pnum].start;
        } else {
            lbl_804799D8.x2A[pnum].cur = lbl_804799D8.x2A[pnum].end;
        }
    }

    state = lbl_804799D8.x2A[pnum].state;
    if (state == 0 && lbl_804799D8.x44[pnum] == 6) {
        if (lbl_804799D8.x2A[pnum].done != 0 && (u8) tm->x4B8[pnum].x0 != 0) {
            lbl_804799D8.x2A[pnum].state = 1;
            lbl_804799D8.x2A[pnum].done = 0;
        }
    }

    state = lbl_804799D8.x2A[pnum].state;
    if (state == 1) {
        if (lbl_804799D8.x2A[pnum].done != 0) {
            lbl_804799D8.x2A[pnum].state = 2;
            lbl_804799D8.x2A[pnum].done = 0;
        }
    }

    fn_8019044C(jobj, (f32) lbl_804799D8.x2A[pnum].cur);
}

extern f32 lbl_804DA7E0; // -19.5f
extern f32 lbl_804DA7E4; // 13.0f
extern f32 lbl_804DA7E8; // 6.5f
extern f32 lbl_804DA7EC; // 19.5f
extern f32 lbl_804DA7F0; // 2.0f
extern f32 lbl_804DA810; // 4.5f
extern f32 lbl_804DA814; // 5.5f
extern f32 lbl_804DA818; // 666.0f
extern f32 lbl_804DA81C; // 0.3f
extern f32 lbl_804DA820; // 12.6f

/// Updates visibility and position of a tournament menu JObj.

void fn_801973F8(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    f32 x;
    s32 cond;
    u8 player_count;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    player_count = tm->x30;
    if ((s32) player_count == 4) {
        x = (lbl_804DA7E4 * (f32) pnum) + lbl_804DA7E0;
    } else if ((s32) player_count == 3) {
        x = lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) pnum) - lbl_804DA7EC);
    } else {
        x = lbl_804DA7E8 +
            ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
    }

    fn_8018FDC4(jobj, lbl_804DA810 + x, lbl_804DA814, lbl_804DA818);

    if (lbl_804799D8.x2A[pnum].state == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

/// Updates visibility of a tournament menu JObj based on current menu state.
void fn_801975C8(HSD_GObj* gobj)
{
    TmData* tmdata;
    u32 idx;
    HSD_JObj* jobj;
    s32 in_range;

    tmdata = gm_8018F634();
    idx = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (HSD_PadMasterStatus[(u8) idx].err != 0 && tmdata->x4B8[idx].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if (lbl_804799D8.x2A[idx].state == 4) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

/// Updates visibility and animation of tournament menu JObj.
void fn_801976D4(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    s32 is_in_range;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        is_in_range = 1;
    } else {
        is_in_range = 0;
    }
    if (is_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        counter = &lbl_804799D8.x1C;
        if (*counter > 0x3C) {
            *counter = 0x3C;
        }
        fn_8019044C(jobj, (f32) *counter);
        *counter = *counter + 1;
    }
}

void fn_801977AC(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    s32 in_range;
    f32 x;
    u8 players;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    players = tm->x30;
    if ((s32) players == 4) {
        x = (lbl_804DA7E4 * (f32) pnum) + lbl_804DA7E0;
    } else if ((s32) players == 3) {
        x = lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) pnum) - lbl_804DA7EC);
    } else {
        x = lbl_804DA7E8 +
            ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
    }

    fn_8018FDC4(jobj, lbl_804DA81C + x, lbl_804DA820, lbl_804DA818);

    if (lbl_804799D8.x2A[pnum].state == 4) {
        u8* counter_ptr;
        u8 counter;

        counter_ptr = &lbl_804799D8.x1D[pnum];
        (void) counter_ptr;
        counter = *counter_ptr;
        if (counter < 0x28) {
            *counter_ptr = counter + 1;
        }
        counter = *counter_ptr;

        HSD_JObjSetTranslateY(jobj, lbl_803DA0D0.bounce_y[counter]);
    } else {
        lbl_804799D8.x1D[pnum] = 0;
    }

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err != 0 &&
        tm->x4B8[pnum].x0 != 1)
    {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

        players = tm->x30;
        if ((s32) players == 4) {
            x = (lbl_804DA7E4 * (f32) pnum) + lbl_804DA7E0;
        } else if ((s32) players == 3) {
            x = lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) pnum) - lbl_804DA7EC);
        } else {
            x = lbl_804DA7E8 +
                ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
        }

        fn_8018FDC4(jobj, lbl_804DA81C + x, lbl_804DA820, lbl_804DA818);
    }
}

void fn_80197AF0(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    s32 in_range;
    f32 x;
    u8 players;
    u8 state;
    u16* counter;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (((s32) gm_8018F634()->cur_option >= 0x1B) &&
        ((s32) gm_8018F634()->cur_option <= 0x1E))
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (((s8) HSD_PadMasterStatus[(u8) pnum].err != 0) &&
        ((u8) tm->x4B8[pnum].x0 != 1))
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if ((u8) tm->x4B8[pnum].x0 == 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }

    players = tm->x30;
    if ((s32) players == 4) {
        x = (lbl_804DA7E4 * (f32) pnum) + lbl_804DA7E0;
    } else if ((s32) players == 3) {
        x = lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) pnum) - lbl_804DA7EC);
    } else {
        x = lbl_804DA7E8 +
            ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
    }

    fn_8018FDC4(jobj, x, lbl_804DA818, lbl_804DA818);

    if (lbl_804799D8.x44[pnum] != 6 || lbl_804799D8.x2A[pnum].state == 1 ||
        lbl_804799D8.x2A[pnum].state == 2 || lbl_804799D8.x2A[pnum].state == 4)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }

    counter = &lbl_804799D8.x12[pnum];
    if (*counter < 0x258U) {
        *counter = (u16) (*counter + 1);
    } else {
        *counter = 0U;
    }
    fn_8019044C(jobj, (f32) *counter);
}

/// Updates visibility of a menu JObj based on current menu option.
void fn_80197D4C(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    u8* counter;
    int cond;
    PAD_STACK(8);

    gm_8018F634();
    jobj = gobj->hsd_obj;
    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    counter = &lbl_804799D8.x29;
    fn_8019044C(jobj, (float) lbl_804799D8.x29);
    if (*counter < 10U) {
        *counter = *counter + 1;
    }
}

/// @todo Currently 69.71% match - needs register allocation fix
/// Updates player HUD element visibility and position.
void fn_80197E18(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    TmData* data;
    s32 pnum;
    s32 in_range;
    f32 x_pos;

    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 && data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if (data->x4B8[pnum].x0 != 1) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (lbl_804DA7E4 * pnum) + (lbl_804DA7E0);
    } else if ((s32) data->x30 == 3) {
        x_pos = lbl_804DA7E8 + ((lbl_804DA7E4 * pnum) - lbl_804DA7EC);
    } else {
        x_pos = lbl_804DA7E8 +
                ((lbl_804DA7E4 * (lbl_804DA7F0 * pnum)) - lbl_804DA7EC);
    }
    fn_8018FDC4(jobj, x_pos, lbl_804DA818, lbl_804DA818);
}

/// @todo Currently 70.24% match - needs register allocation fix
/// Updates JObj visibility based on menu option and player state.
void fn_80197FD8(HSD_GObj* gobj)
{
    TmData* tm_data;
    s32 port;
    HSD_JObj* jobj;
    s32 option_in_range;
    u8 port_u8;

    tm_data = gm_8018F634();
    port = fn_8018F62C(gobj);
    jobj = (HSD_JObj*) gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        option_in_range = 1;
    } else {
        option_in_range = 0;
    }

    if (option_in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    port_u8 = (u8) port;
    if ((s8) HSD_PadMasterStatus[port_u8].err != 0) {
        if (tm_data->x4B8[port].x0 != 1) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            return;
        }
    } else {
        if (lbl_804799D8.x2A[port].state == 4) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }
    }

    {
        f32 x_position;
        u8 num_players = tm_data->x30;

        if ((s32) num_players == 4) {
            x_position = (lbl_804DA7E4 * (f32) port) + lbl_804DA7E0;
        } else if ((s32) num_players == 3) {
            x_position =
                lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) port) - lbl_804DA7EC);
        } else {
            x_position =
                lbl_804DA7E8 +
                ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) port)) - lbl_804DA7EC);
        }

        fn_8018FDC4(jobj, x_position, lbl_804DA818, lbl_804DA818);
    }
}

extern f32 lbl_804DA824; // 0.01f

/// @todo Down to linking
/// Updates player cursor animation and position.
void fn_801981A0(HSD_GObj* gobj)
{
    TmData* data;
    s32 pnum;
    HSD_JObj* jobj;
    struct Lbl804799D8_t* state;
    f32 x_pos;
    s32 in_range;
    u8 counter;

    state = &lbl_804799D8;
    data = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if (HSD_PadMasterStatus[(u8) pnum].err != 0 && state->x2A[pnum].state != 4)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    if (state->x44[pnum] == 6) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }

    if ((s32) data->x30 == 4) {
        x_pos = (lbl_804DA7E4 * (f32) pnum) + (lbl_804DA7E0);
    } else if ((s32) data->x30 == 3) {
        x_pos = lbl_804DA7E4;
        x_pos = lbl_804DA7E8 + ((x_pos * (f32) pnum) - lbl_804DA7EC);
    } else {
        x_pos = lbl_804DA7E8 +
                ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
    }

    fn_8018FDC4(jobj, x_pos, lbl_804DA818, lbl_804DA824);

    counter = state->x21[pnum];
    counter = (counter + 1) % 11;
    state->x21[pnum] = counter;

    if (state->x44[pnum] == 7) {
        fn_8019044C(jobj, (f32) state->x21[pnum]);
        return;
    }

    fn_8019044C(jobj, (f32) (state->x21[pnum] + 0x14));
}

/// Updates the visibility and position of a player's controller indicator.
void fn_801983E4(HSD_GObj* gobj)
{
    TmData* tm;
    s32 pnum;
    HSD_JObj* jobj;
    f32 x;
    s32 cond;
    u8 player_count;

    tm = gm_8018F634();
    pnum = fn_8018F62C(gobj);
    jobj = gobj->hsd_obj;

    if (gm_8018F634()->cur_option >= 0x1B && gm_8018F634()->cur_option <= 0x1E)
    {
        cond = 1;
    } else {
        cond = 0;
    }

    if (cond == 0) {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    if ((s8) (u8) HSD_PadMasterStatus[(u8) pnum].err == 0 ||
        tm->x4B8[pnum].x0 == 1)
    {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }

    player_count = tm->x30;
    if ((s32) player_count == 4) {
        x = (lbl_804DA7E4 * (f32) pnum) + lbl_804DA7E0;
    } else if ((s32) player_count == 3) {
        x = lbl_804DA7E8 + ((lbl_804DA7E4 * (f32) pnum) - lbl_804DA7EC);
    } else {
        x = lbl_804DA7E8 +
            ((lbl_804DA7E4 * (lbl_804DA7F0 * (f32) pnum)) - lbl_804DA7EC);
    }

    fn_8018FDC4(jobj, x, lbl_804DA818, lbl_804DA824);
}

void fn_80198584(ResultsData* results)
{
    HSD_JObj* jobj;
    int cur_option;

    cur_option = gm_8018F634()->cur_option;
    jobj = results->x28;
    if (cur_option == 0x1D) {
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

extern s32 lbl_804D667C;

void fn_801985D4(HSD_GObj* gobj)
{
    struct Lbl804799D8_t* d8 = &lbl_804799D8;
    HSD_JObj* jobj;
    HSD_JObj* child;
    s32 in_range;

    gm_8018F634();
    jobj = gobj->hsd_obj;

    if ((s32) gm_8018F634()->cur_option >= 0x1F &&
        (s32) gm_8018F634()->cur_option <= 0x27)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
    } else {
        HSD_JObjSetTranslateZ(jobj, 0.0f);

        if (d8->x0 < 0xAU) {
            lbl_804D667C = 1;
            return;
        }

        HSD_JObjAnimAll(jobj);
        child = HSD_JObjGetChild(jobj);

        if (HSD_DObjGetFlags(HSD_JObjGetDObj(child)) & 1) {
            lbl_804D667C = 1;
        } else {
            lbl_804D667C = 0;
        }

        HSD_JObjGetTranslation(child, &d8->x64);
        HSD_JObjGetScale(child, &d8->x70);
    }
}

/// Animates and positions the tournament bracket results overlay JObj.
/// Uses HSD_JObjSetTranslateZ for visibility, HSD_JObjSetTranslate/SetScale
/// for positioning from lbl_804799D8 cached values.
void fn_80198824(HSD_GObj* gobj)
{
    struct Lbl804799D8_t* d8 = &lbl_804799D8;
    HSD_JObj* jobj;
    s32 in_range;

    gm_8018F634();
    jobj = gobj->hsd_obj;

    if ((s32) gm_8018F634()->cur_option >= 0x1F &&
        (s32) gm_8018F634()->cur_option <= 0x27)
    {
        in_range = 1;
    } else {
        in_range = 0;
    }

    if (in_range == 0) {
        HSD_JObjSetTranslateZ(jobj, 10000.0f);
    } else {
        HSD_JObjSetTranslateZ(jobj, 0.0f);

        if (lbl_804D667C != 0) {
            HSD_JObjSetTranslateZ(jobj, 10000.0f);
        } else {
            u32* frame_ctr;
            u32 min_frame;

            {
                u32* frame_ctr_ptr = &d8->x4;
                frame_ctr = frame_ctr_ptr;
            }
            min_frame = (u32) d8->x8;
            if (*frame_ctr < min_frame) {
                *frame_ctr = min_frame;
            }
            if (*frame_ctr < (u32) d8->xC) {
                *frame_ctr = *frame_ctr + 1;
            }

            HSD_JObjReqAnimAll(jobj, (f32) *frame_ctr);
            HSD_JObjAnimAll(jobj);

            HSD_JObjSetTranslate(jobj, &d8->x64);
            HSD_JObjSetScale(jobj, &d8->x70);
        }
    }
}

/// Initializes tournament mode match data.
/// Initializes tournament mode match data structures.
/// Type casts used to match target instruction patterns (stw/sth vs stb).
#pragma push
#pragma auto_inline off
void fn_80198BA0(void)
{
    TmData* td;
    u8* ptr;
    u8* ptr7;
    u8* ptr8;
    s32 i;

    ptr = (u8*) &lbl_804799D8;
    td = gm_8018F634();

    /* Clear first 4 bytes as word (stw instruction) */
    *(u32*) &ptr[0x00] = 0;
    if (td && td) {
        /* FAKE MATCH: Empty block affects register allocation */
    }
    /* Clear 2 bytes at offset 0x10 as halfword (sth instruction) */
    *(u16*) &ptr[0x10] = 0;

    if (td->x2C != 0) {
        ptr[0x1A] = 0x50;
    } else {
        ptr[0x1A] = 0x5A;
    }

    ptr[0x1C] = 0;
    ptr7 = ptr;
    ptr8 = ptr;

    for (i = 0; i < td->x30; i++) {
        ptr[0x25] = 0;
        /* Clear 2 bytes as halfword (sth instruction) */
        *(u16*) &ptr7[0x12] = 0;
        ptr7 += 2;
        ptr[0x1D] = 0;
        ptr8[0x2A] = 0;
        ptr8[0x2B] = 0;
        ptr8[0x2C] = 0x1E;
        ptr8[0x2E] = 0;
        ptr8[0x2F] = 0;
        ptr8[0x2D] = 0;
        ptr8 += 6;
        ptr[0x44] = 6;
        ptr++;
    }
}
#pragma pop

/// @todo Currently 99.63% match - permuter couldn't improve (instruction
/// scheduling)
/// Initializes tournament mode text displays.
#pragma push
#pragma auto_inline off
void fn_80198C60(void)
{
    TmData* td;
    HSD_Text* text;

    PAD_STACK(24);

    td = gm_8018F634();
    td->x524[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = td->x524[2];
    text->font_size.x = 0.054945F;
    text->font_size.y = 0.08F;
    td->x524[2]->default_alignment = 1;
    td->x524[2]->default_kerning = 1;

    td->x524[3] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    td->x524[3]->default_alignment = 1;
    td->x524[3]->default_kerning = 1;
    HSD_SisLib_803A6B98(td->x524[3], 320.0F, 250.0F, "    ");
    HSD_SisLib_803A7548(td->x524[3], 0, 1.5F, 1.5F);
}
#pragma pop

extern SceneDesc* lbl_804D666C;
extern f32 lbl_804DA808; // 0.0f
extern f32 lbl_804DA82C; // 0.054945f
extern f32 lbl_804DA830; // 0.08f
extern f32 lbl_804DA834; // (float)
extern f32 lbl_804DA838; // 250.0f
extern f32 lbl_804DA83C; // 1.5f
extern f32 lbl_804DA840; // (float)

/// Initializes the scene rendering components for the gm_18A5 game mode.
void fn_80198D18(void)
{
    TmData* td;
    HSD_Text* text;
    HSD_GObj* gobj;
    PAD_STACK(24);

    gm_8018F634();
    gobj = fn_80190174(lbl_804D666C->cameras->desc);
    fn_801901F8(lbl_804D666C->cameras->desc);
    fn_801902F0((int) gobj);
    fn_8019027C(lbl_804D666C->lights);
    fn_8019035C(0, lbl_804D666C->models[5], 0, 0x1A, 2, 1, fn_80196DBC, 0.0f);
    fn_8019035C(0, lbl_804D666C->models[4], 0, 0x1A, 2, 1, fn_80196E30, 80.0f);

    td = gm_8018F634();
    td->x524[2] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    text = td->x524[2];
    text->font_size.x = lbl_804DA82C;
    text->font_size.y = lbl_804DA830;
    td->x524[2]->default_alignment = 1;
    td->x524[2]->default_kerning = 1;

    td->x524[3] = HSD_SisLib_803A6754(0, (s32) lbl_804D663C);
    td->x524[3]->default_alignment = 1;
    td->x524[3]->default_kerning = 1;
    HSD_SisLib_803A6B98(td->x524[3], lbl_804DA834, lbl_804DA838, "    ");
    HSD_SisLib_803A7548(td->x524[3], 0, lbl_804DA83C, lbl_804DA83C);

    gobj = GObj_Create(0xE, 0x1A, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                            (0, HSD_FogLoadDesc(lbl_804D666C->fogs[0].desc)));
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    fn_80198BA0();
}

extern SceneDesc* lbl_804D6674;
extern f32 lbl_804DA828;
extern f32 lbl_804DA844;
extern f32 lbl_804DA848;
extern f32 lbl_804DA84C;
extern f32 lbl_804DA850;
extern f32 lbl_804DA854;
extern f32 lbl_804DA858;
extern f32 lbl_804DA85C;
extern f32 lbl_804DA860;
extern f32 lbl_804DA864;
extern f32 lbl_804DA868;
extern f32 lbl_804DA86C;
extern f32 lbl_804DA870;
extern f32 lbl_804DA874;

/// Matched bar data relocations
void fn_80198EBC(void)
{
    TmData* td;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_JObj* c;
    f32 pos;
    s32 i, j;
    HSD_JObj* jobj2;
    HSD_JObj* j16;

    td = gm_8018F634();
    gm_8018F634();

    gobj = fn_80190174(lbl_804D666C->cameras->desc);
    fn_801901F8(lbl_804D666C->cameras->desc);
    fn_801902F0((int) gobj);
    fn_8019027C(lbl_804D666C->lights);

    fn_8019035C(0, lbl_804D666C->models[5], 0, 0x1A, 2, 1, fn_80196DBC, 0.0f);
    fn_8019035C(0, lbl_804D666C->models[4], 0, 0x1A, 2, 1, fn_80196E30, 80.0f);
    fn_80198C60();

    gobj = GObj_Create(0xE, 0x1A, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                            (0, HSD_FogLoadDesc(lbl_804D666C->fogs[0].desc)));
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    fn_80198BA0();

    for (i = 0; i < td->x30; i++) {
        f32 anim_rate;
        if (td->x4B8[i].x0 == 0) {
            anim_rate = (f32) i;
        } else if (td->x4B8[i].x0 == 1) {
            anim_rate = 4.0f;
        } else {
            anim_rate = (f32) i;
            td->x4B8[i].x0 = 0;
            lbl_804799D8.x44[i] = 6;
            lbl_804799D8.x2A[i].state = 4;
        }

        gobj = fn_8019035C(0, lbl_804D6674->models[12], 0, 0x1A, 2, 1,
                           fn_80196FFC, anim_rate);
        jobj = gobj->hsd_obj;
        fn_8018FBD8(gobj, i);
        c = HSD_JObjGetChild(jobj);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);
        c = HSD_JObjGetChild(jobj);
        c = HSD_JObjGetNext(c);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);
        c = HSD_JObjGetChild(jobj);
        c = HSD_JObjGetNext(c);
        c = HSD_JObjGetNext(c);
        HSD_MObjRemoveAnimByFlags(c->u.dobj->mobj, 4);

        if (td->x30 == 4) {
            pos = 73.0f + (240.0f * (f32) i + 152.0f);
        } else if (td->x30 == 3) {
            pos = 73.0f + (240.0f * (f32) i + 270.0f);
        } else {
            pos = 73.0f + (240.0f * (2.0f * (f32) i) + 270.0f);
        }
        fn_8018ECA8(td->x4B8[i].x6, td->x4B8[i].x0, 5,
                    0.99f * (pos - 320.0f) - 261.0f, -42.0f, 5);

        td->x524[2]->hidden = true;

        gobj = fn_8019035C(0, lbl_804D6674->models[10], 0, 0x1A, 2, 1,
                           fn_801973F8, anim_rate);
        jobj = gobj->hsd_obj;
        fn_8018FBD8(gobj, i);

        c = HSD_JObjGetChild(jobj);
        jobj2 = c;

        HSD_JObjSetTranslateZ(jobj2, 10000.0f);

        if (lbl_803DA0D0.icon_model_map[td->x4B8[i].x1] == 0) {
            HSD_JObjSetTranslateZ(jobj2, 0.0f);

            for (j = 1; j <= 12; j++) {
                jobj2 = HSD_JObjGetNext(jobj2);
                HSD_JObjSetTranslateZ(jobj2, 10000.0f);
            }
        } else {
            for (j = 1; j <= 12; j++) {
                jobj2 = HSD_JObjGetNext(jobj2);
                HSD_JObjSetTranslateZ(jobj2, 10000.0f);

                if (lbl_803DA0D0.icon_model_map[td->x4B8[i].x1] == j) {
                    HSD_JObjSetTranslateZ(jobj2, 0.0f);

                    for (j++; j <= 12; j++) {
                        jobj2 = HSD_JObjGetNext(jobj2);
                        HSD_JObjSetTranslateZ(jobj2, 10000.0f);
                    }
                    break;
                }
            }
        }

        gobj = fn_8019035C(0, lbl_804D6674->models[4], 0, 0x1A, 2, 1,
                           fn_801975C8, anim_rate);
        jobj = GET_JOBJ(gobj);
        fn_8018FBD8(gobj, i);

        if ((s32) td->x30 == 4) {
            pos = 13.0f * (f32) i + -19.5f;
        } else if ((s32) td->x30 == 3) {
            pos = 6.5f + (13.0f * (f32) i - 19.5f);
        } else {
            pos = 6.5f + (13.0f * (2.0f * (f32) i) - 19.5f);
        }
        /* 2.8f - 1 ulp (0x4033332F) */
        fn_8018FDC4(jobj, pos - 2.7999989986419678f, 6.8f, 0.001f);

        c = HSD_JObjGetChild(jobj);
        jobj = HSD_JObjGetNext(c);
        fn_8019044C(jobj, fn_8018F71C(td->x4B8[i].x1, td->x4B8[i].x3));

        gobj = fn_8019035C(0, lbl_804D6674->models[9], 0, 0x1A, 2, 1,
                           fn_801977AC, anim_rate);
        jobj = GET_JOBJ(gobj);
        fn_8018FBD8(gobj, i);
        fn_8019044C(jobj, anim_rate);

        gobj = fn_8019035C(0, lbl_804D6674->models[8], 0, 0x1A, 2, 1,
                           fn_80197AF0, lbl_804DA808);
        fn_8018FBD8(gobj, i);

        gobj = fn_8019035C(0, lbl_804D6674->models[13], 0, 0x1A, 2, 1,
                           fn_80197E18, anim_rate);
        jobj = GET_JOBJ(gobj);
        fn_8018FBD8(gobj, i);

        if (td->x4B8[i].x0 == 1) {
            fn_8019044C(jobj, td->x4B8[i].x4);
        } else {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
        }

        if (td->x31 != 0) {
            gobj = fn_8019035C(0, lbl_804D6674->models[11], 0, 0x1A, 2, 1,
                               fn_80197FD8, anim_rate);
            jobj = GET_JOBJ(gobj);
            fn_8018FBD8(gobj, i);
            fn_8019044C(jobj, td->x4B8[i].x5);
        }

        gobj = fn_8019035C(0, lbl_804D6674->models[7], 0, 0x1A, 2, 1,
                           fn_801981A0, anim_rate);
        jobj = GET_JOBJ(gobj);
        fn_8018FBD8(gobj, i);
        fn_8018FDC4(jobj, lbl_804DA870, lbl_804DA818, lbl_804DA874);

        gobj = fn_8019035C(0, lbl_804D6674->models[14], 0, 0x1A, 2, 1,
                           fn_801983E4, anim_rate);
        fn_8018FBD8(gobj, i);
    }

    fn_8019035C(0, lbl_804D6674->models[5], 0, 0x1A, 2, 1, fn_801976D4,
                lbl_804DA808);

    gobj = fn_8019035C(0, lbl_804D6674->models[0], 0, 0x1A, 2, 1, NULL,
                       lbl_804DA808);
    j16 = GET_JOBJ(gobj);

    j16 = HSD_JObjGetChild(j16);
    j16 = HSD_JObjGetNext(j16);
    j16 = HSD_JObjGetNext(j16);
    j16 = HSD_JObjGetNext(j16);
    j16 = HSD_JObjGetNext(j16);
    j16 = HSD_JObjGetNext(j16);
    for (j = 0; j <= 40; j++) {
        fn_8019044C(j16, (f32) (j + 10));
        lbl_803DA0D0.bounce_y[j] = HSD_JObjGetTranslationY(j16);
    }

    fn_8019035C(0, lbl_804D6674->models[6], 0, 0x1A, 2, 1, fn_80197D4C,
                lbl_804DA808);
    fn_8019035C(0, lbl_804D6674->models[2], 0, 0x1A, 3, 1,
                (void (*)(HSD_GObj*)) fn_80198584, lbl_804DA808);
}

void fn_80199AF0(void)
{
    TmData* td1;
    TmData* td2;
    HSD_JObj* jobj;
    HSD_JObj* next;
    HSD_GObj* gobj;
    s32 mode;
    s32 slot;
    s32 bracket_idx;
    s32 result;
    s32 i;
    s32 local1;
    s32 local2;
    PAD_STACK(16);

    td1 = gm_8018F634();
    td2 = gm_8018F634();

    result = fn_8018F508(&local1);
    if (result == 1) {
        result = 1;
    } else if (td2->x33 == 5) {
        result = 2;
    } else {
        result = 0;
    }
    mode = result;

    result = fn_8018F508(&local2);
    if (result == 1) {
        slot = local2;
    } else {
        u8* p = (u8*) &gm_80477738;
        if (p[0x58] != 3 && p[0x5E] == 0) {
            slot = 0;
        } else {
            p += 0xA8;
            if (p[0x58] != 3 && p[0x5E] == 0) {
                slot = 1;
            } else {
                p += 0xA8;
                if (p[0x58] != 3 && p[0x5E] == 0) {
                    slot = 2;
                } else {
                    p += 0xA8;
                    if (p[0x58] != 3 && p[0x5E] == 0) {
                        slot = 3;
                    } else {
                        slot = -1;
                    }
                }
            }
        }
    }

    bracket_idx = fn_8018F74C();
    gm_8018F634();

    gobj = fn_80190174(lbl_804D666C->cameras->desc);
    fn_801901F8(lbl_804D666C->cameras->desc);
    fn_801902F0((int) gobj);
    fn_8019027C(lbl_804D666C->lights);
    fn_8019035C(0, lbl_804D666C->models[5], 0, 0x1A, 2, 1, fn_80196DBC,
                lbl_804DA808);
    fn_8019035C(0, lbl_804D666C->models[4], 0, 0x1A, 2, 1, fn_80196E30,
                lbl_804DA840);

    fn_80198C60();

    gobj = GObj_Create(0xE, 0x1A, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848,
                            (0, HSD_FogLoadDesc(lbl_804D666C->fogs[0].desc)));
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    fn_80198BA0();

    if (td1->x33 == 5) {
        mode = 2;
    }

    if (mode != 2) {
        if (lbl_80473AB8[bracket_idx].x18 == 0) {
            return;
        }
    }

    fn_8019035C(0, lbl_804D6670->models[0], mode, 0x1A, 3, 1, fn_801985D4,
                lbl_804DA808);
    gobj = fn_8019035C(0, lbl_804D6670->models[2], 0, 0x1A, 3, 1, fn_80198824,
                       lbl_804DA808);

    if (gobj->hsd_obj == NULL) {
        jobj = NULL;
    } else {
        jobj = ((HSD_JObj*) gobj->hsd_obj)->child;
    }

    lbl_804799D8.x8 = mode * 0x14;
    if (mode == 2) {
        lbl_804799D8.xC = 0x96;
    } else {
        lbl_804799D8.xC = mode * 0x14 + 0x13;
    }

    HSD_JObjSetTranslateZ(jobj, 10000.0f);

    if (lbl_803DA0D0.icon_model_map[td1->x4B8[slot].x1] == 0) {
        HSD_JObjSetTranslateZ(jobj, 0.0f);
        for (i = 1; i <= 12; i++) {
            if (jobj == NULL) {
                next = NULL;
            } else {
                next = jobj->next;
            }
            jobj = next;
            HSD_JObjSetTranslateZ(next, 10000.0f);
        }
    } else {
        for (i = 1; i <= 12; i++) {
            if (jobj == NULL) {
                next = NULL;
            } else {
                next = jobj->next;
            }
            jobj = next;
            HSD_JObjSetTranslateZ(next, 10000.0f);

            if ((s32) lbl_803DA0D0.icon_model_map[td1->x4B8[slot].x1] == i) {
                HSD_JObjSetTranslateZ(next, 0.0f);
                for (slot = i + 1; slot <= 12; slot++) {
                    if (jobj == NULL) {
                        next = NULL;
                    } else {
                        next = jobj->next;
                    }
                    jobj = next;
                    HSD_JObjSetTranslateZ(next, 10000.0f);
                }
                break;
            }
        }
    }
}

void fn_8019A158(void)
{
    TmData* td1;
    TmData* td2;
    s32 mode;
    s32 slot;
    s32 bracket_idx;
    s32 result;
    s32 local1, local2;
    s32 i;
    s32 counter;
    u8* me;
    u8* cursor;
    PAD_STACK(16);

    td1 = gm_8018F634();
    lbl_804799D8.x48 = (u8*) &gm_80477738;
    mode = 0;
    lbl_804799D8.x0 = 0;

    td2 = gm_8018F634();

    result = fn_8018F508(&local1);
    if (result == 1) {
        mode = 1;
    } else if (td2->x33 == 5) {
        mode = 2;
    }

    me = lbl_804799D8.x48;
    result = fn_8018F508(&local2);
    if (result == 1) {
        slot = local2;
    } else if (me[0x58] != 3 && me[0x5E] == 0) {
        slot = 0;
    } else {
        cursor = me + 0xA8;
        if (me[0x100] != 3 && cursor[0x5E] == 0) {
            slot = 1;
        } else {
            me = cursor + 0xA8;
            if (cursor[0x100] != 3 && me[0x5E] == 0) {
                slot = 2;
            } else {
                cursor = me + 0xA8;
                if (me[0x100] != 3 && cursor[0x5E] == 0) {
                    slot = 3;
                } else {
                    slot = -1;
                }
            }
        }
    }

    bracket_idx = fn_8018F74C();

    for (i = 0; 20 > i; i++) {
        lbl_804799D8.x4E[i] = 0;
    }

    if (mode == 1) {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        u8* bp = (u8*) bracket;
        u8* matched = bp + slot * 0x2C;

        for (i = 0; i < 4; i++) {
            if (i == slot) {
                matched[0x4C] = 0;
            } else {
                bp[0x4C] = 3;
            }
            bp += 0x2C;
        }
    } else if (td1->x2D == 1) {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        cursor = (u8*) bracket;

        if (bracket->x4E == 3) {
            bracket->x4C = 3;
        } else {
            me = lbl_804799D8.x48;
            {
                u8 v = me[0x5E];
                me[0x5D] = v;
                bracket->x4C = v;
            }
            me = lbl_804799D8.x48;
            if (me[0x5E] == 0) {
                slot = 0;
            }
        }

        {
            u8 check = bracket->x7A;
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0xA8;
                {
                    u8 v = me[0x5E];
                    me[0x5D] = v;
                    cursor[0x4C] = v;
                }
                me = lbl_804799D8.x48;
                if (me[0x106] == 0) {
                    slot = 1;
                }
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0x150;
                {
                    u8 v = me[0x5E];
                    me[0x5D] = v;
                    cursor[0x4C] = v;
                }
                me = lbl_804799D8.x48;
                if (me[0x1AE] == 0) {
                    slot = 2;
                }
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 3;
            } else {
                me = lbl_804799D8.x48;
                me += 0x1F8;
                {
                    u8 v = me[0x5E];
                    me[0x5D] = v;
                    cursor[0x4C] = v;
                }
                me = lbl_804799D8.x48;
                if (me[0x256] == 0) {
                    slot = 3;
                }
            }
        }
    } else {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        counter = 0;

        if (bracket->x4E == 3) {
            bracket->x4C = 4;
        } else {
            bracket->x4C = 0;
            counter = 1;
        }

        cursor = (u8*) bracket + 0x2C;
        if (bracket->x7A == 3) {
            cursor[0x4C] = 4;
        } else {
            cursor[0x4C] = counter;
            counter++;
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 4;
            } else {
                cursor[0x4C] = counter;
                counter++;
            }
        }

        {
            u8 check = cursor[0x7A];
            cursor += 0x2C;
            if (check == 3) {
                cursor[0x4C] = 4;
            } else {
                cursor[0x4C] = counter;
                counter++;
            }
        }

        switch (counter) {
        case 2: {
            s32 rand_val = HSD_Randi(bracket->x51 + bracket->x7D);
            if (rand_val < bracket->x51) {
                bracket->x4C = 0;
                bracket->x78 = 1;
            } else {
                bracket->x4C = 1;
                bracket->x78 = 0;
            }
            break;
        }
        case 3:
            fn_80196684(bracket_idx);
            break;
        case 4:
            fn_801967E0(bracket_idx);
            break;
        }

        me = lbl_804799D8.x48;
        cursor = (u8*) &lbl_80473AB8[bracket_idx];
        {
            u8 v = cursor[0x4C];
            me[0x5D] = v;
            me = lbl_804799D8.x48;
            me[0x5E] = v;
            v = cursor[0x78];
            me[0x105] = v;
            me = lbl_804799D8.x48;
            me[0x106] = v;
            v = cursor[0xA4];
            me[0x1AD] = v;
            me = lbl_804799D8.x48;
            me[0x1AE] = v;
            v = cursor[0xD0];
            me[0x255] = v;
            me = lbl_804799D8.x48;
            me[0x256] = v;
        }

        if (bracket->x4C == 0) {
            slot = 0;
        }
        if (bracket->x78 == 0) {
            slot = 1;
        }
        cursor = (u8*) bracket + 0x2C;
        if (cursor[0x78] == 0) {
            cursor += 0x2C;
            slot = 2;
        } else {
            cursor += 0x2C;
        }
        if (cursor[0x78] == 0) {
            slot = 3;
        }
    }

    {
        BracketEntry* bracket = &lbl_80473AB8[bracket_idx];
        lbl_804799D8.x4C = slot;
        cursor = (u8*) bracket + slot * 0x2C;
        lbl_804799D8.x4D = cursor[0x4E];

        if (lbl_804799D8.x4D == 0 && bracket->x18 != 0) {
            u8 s = lbl_804799D8.x4C;
            u16 val = td1->x4B8[s].x6;
            if (val <= 0x78) {
                gm_80167858(s, (s32) val, 0x1F, 0x78);
            } else {
                gm_80167858(s, 0x78, 0x1F, 0x78);
            }
        }

        cursor = (u8*) &lbl_80473AB8[bracket_idx] + slot * 0x2C;
        {
            u8 model_idx = cursor[0x50];
            struct TmUnkMenuData* entries = td1->x37;
            fn_8018F00C((char*) lbl_804799D8.x4E, entries[model_idx].x9);
        }
    }
}

/// #fn_8019A158_end

void fn_8019A71C(s32* state, u32 unused1, u32 unused2)
{
    u32* counter = &lbl_804799D8.x0;

    switch (*state) {
    case 0x13:
        fn_8019B458(state);
        break;
    }

    if (*state > 0x14) {
        *counter = *counter + 1;
    }

    if (*counter >= 0x14U) {
        *state = 0x15;
    }

    if (*counter == 0x1EU) {
        *state = 0x16;
    }

    if (*counter > 0x1EU) {
        *state = 0x17;
    }

    if (*counter >= 0x3CU) {
        *state = 0x18;
    }

    if (*counter >= 0x46U) {
        *state = 0x19;
    }

    if (*counter >= 0x5AU) {
        fn_8018EC48();
        *state = 0x1A;
        fn_8018EC7C();
        if (fn_8018F508(0) == 1) {
            *state = 0x1F;
            return;
        }
        *state = 0x1B;
    }
}
extern s32 lbl_804D6678;

void gm_8019A828(void)
{
    gm_8018F634()->x32 = 0;
    lbl_804D6678 = 1;
    gm_8018F634()->cur_option = 0x1B;
}

/// @todo 99.86%: all instruction shapes and callee-saved registers match;
/// two scratch-register tie-breaks remain (the ready loop's err/state temps
/// trade r7/r3, and the bracket-entry fill's address/value temps trade
/// r0/r4). Decl orders, block-scope promotion, split counters, and comma
/// expressions all compile to identical instructions with the same colors.
void fn_8019A86C(TmData* tm, u32 arg1, u32 arg2)
{
    s32 ready_count = 0;
    s32 pad_err = 0;
    s32 i;
    PAD_STACK(0x28);

    switch (tm->cur_option) {
    case 0x1B:
        fn_8019B81C((s32*) tm);
        break;
    }

    if (tm->cur_option == 0x1D) {
        lbl_804799D8.x0 += 1;
        if ((arg2 & 0x600) || (lbl_804799D8.x0 >= 0x12CU)) {
            lbAudioAx_80024030(0);
            fn_8018EC48();
            tm->x2D = 0;
            tm->cur_option = 0x1F;
        }
        if (arg2 & 0x1100) {
            TmData* t;
            s32 stype;
            s32 cond;

            lbAudioAx_80024030(1);
            t = gm_8018F634();
            t->x2D = 1;
            stype = t->stage_selection_type;
            if ((stype == 2 && (u8) t->x32 == 0) || stype == 3) {
                cond = 1;
            } else {
                cond = 0;
            }
            if (cond != 0) {
                t->x32 = 1;
                gm_SetPendingScene(3U);
                gm_801A4B60();
                return;
            }
            if ((stype == 0 && (u8) t->x32 == 0) || stype == 1) {
                cond = 1;
            } else {
                cond = 0;
            }
            if (cond != 0) {
                t->x32 = 1;
                t->x28 = (u32) lbl_804D4190;
            }
            gm_SetPendingScene(4U);
            gm_801A4B60();
        }
    } else {
        for (i = 0; i < (s32) tm->x30; i++) {
            if (tm->x4B8[i].x0 == 1) {
                ready_count += 1;
            } else {
                u8 err = (u8) HSD_PadMasterStatus[(u8) i].err;
                if ((s8) err != 0) {
                    pad_err = 1;
                }
                {
                    u8 state = lbl_804799D8.x2A[i].state;
                    if (((state == 2 &&
                          (u8) lbl_804799D8.x2A[i].cur >= 0x3CU) ||
                         (state == 4 &&
                          (u8) lbl_804799D8.x2A[i].cur == 0x82)) &&
                        (s8) err == 0)
                    {
                        ready_count += 1;
                    }
                }
            }
        }

        {
            s32 cond3;
            if ((fn_8018F640(4) & 0x1160) &&
                ((u32) (fn_8018F6A8(4) & 0x1160) == 0x1160))
            {
                cond3 = 1;
            } else {
                cond3 = 0;
            }
            if (cond3 != 0 && pad_err != 0) {
                lbAudioAx_80024030(0);
                HSD_SisLib_803A5E70();
                mn_8022F138(0x19, 0x1C);
                mn_8022F138(0x12, 0x15);
                mn_8022F268();
                gm_801A4B60();
                gm_801A42F8(1);
                return;
            }
        }

        if (ready_count == (s32) tm->x30) {
            lbl_804799D8.x0 += 1;
            if (lbl_804799D8.x0 >= 0x1EU) {
                for (i = 0; i < (s32) tm->x30; i++) {
                    if (tm->x4B8[i].x0 == 0 && lbl_804799D8.x2A[i].state == 4)
                    {
                        tm->x4B8[i].x0 = 3;
                    }
                }

                {
                    TmData* t2 = gm_8018F634();
                    BracketEntry* ent = &lbl_80473AB8[fn_8018F74C()];
                    s32 hmn_count = 0;
                    s32 active_count = 0;

                    ent->x4E = t2->x4B8[0].x0;
                    ent->x7A = t2->x4B8[1].x0;
                    ent->xA6 = t2->x4B8[2].x0;
                    ent->xD2 = t2->x4B8[3].x0;

                    for (i = 0; i < 4; i++) {
                        u8 st = tm->x4B8[i].x0;
                        if (st == 0) {
                            hmn_count += 1;
                        }
                        if (st != 3) {
                            active_count += 1;
                        }
                    }

                    if (active_count <= 1) {
                        fn_8018EC48();
                        tm->x2D = 0;
                        tm->cur_option = 0x1F;
                        return;
                    }
                    if (hmn_count == 0) {
                        tm->cur_option = 0x1D;
                        return;
                    }

                    {
                        TmData* t3 = gm_8018F634();
                        s32 stype2;
                        s32 cond2;

                        t3->x2D = 1;
                        stype2 = t3->stage_selection_type;
                        if ((stype2 == 2 && (u8) t3->x32 == 0) || stype2 == 3)
                        {
                            cond2 = 1;
                        } else {
                            cond2 = 0;
                        }
                        if (cond2 != 0) {
                            t3->x32 = 1;
                            gm_SetPendingScene(3U);
                            gm_801A4B60();
                            return;
                        }
                        if ((stype2 == 0 && (u8) t3->x32 == 0) || stype2 == 1)
                        {
                            cond2 = 1;
                        } else {
                            cond2 = 0;
                        }
                        if (cond2 != 0) {
                            t3->x32 = 1;
                            t3->x28 = (u32) lbl_804D4190;
                        }
                        gm_SetPendingScene(4U);
                        gm_801A4B60();
                    }
                }
            }
        } else {
            lbl_804799D8.x0 = 0;

            for (i = 0; i < (s32) tm->x30; i++) {
                if ((s8) (u8) HSD_PadMasterStatus[(u8) i].err == 0 &&
                    tm->x4B8[i].x0 == 0)
                {
                    u32 buttons = fn_8018F640(i);

                    if (buttons & 0x1100) {
                        lbAudioAx_80024030(1);
                        if (lbl_804799D8.x44[i] == 7) {
                            lbl_804799D8.x44[i] = 6;
                        } else if (lbl_804799D8.x44[i] == 8) {
                            u8 np = gm_8018F634()->x30;
                            s32 count4 = 0;
                            s32 j;

                            for (j = 0; j < (s32) np; j++) {
                                if (lbl_804799D8.x2A[j].state == 4) {
                                    count4 += 1;
                                }
                            }
                            if (count4 < (s32) (tm->x30 - 1)) {
                                lbl_804799D8.x44[i] = 6;
                                lbl_804799D8.x2A[i].state = 4;
                            }
                        } else {
                            u8 pstate = lbl_804799D8.x2A[i].state;
                            if (pstate == 4) {
                                lbl_804799D8.x2A[i].state = 5;
                            } else if (pstate == 0 || pstate == 3 ||
                                       pstate == 5)
                            {
                                u16 val = tm->x4B8[i].x6;
                                if (val <= 0x78U) {
                                    gm_80167858(i, (s32) val, 0xB, 0x14);
                                } else {
                                    gm_80167858(i, 0x78, 0xB, 0x14);
                                }
                                lbl_804799D8.x2A[i].state = 1;
                            }
                        }
                    } else if (buttons & 0x400) {
                        if (lbl_804799D8.x44[i] != 6) {
                            lbAudioAx_80024030(0);
                            lbl_804799D8.x44[i] = 6;
                        } else {
                            u8 pstate2 = lbl_804799D8.x2A[i].state;
                            if (pstate2 == 0 || pstate2 == 3 || pstate2 == 5) {
                                u8 np2 = gm_8018F634()->x30;
                                s32 count5 = 0;
                                s32 k;

                                for (k = 0; k < (s32) np2; k++) {
                                    if (lbl_804799D8.x2A[k].state == 4) {
                                        count5 += 1;
                                    }
                                }
                                if (count5 < (s32) (tm->x30 - 1)) {
                                    lbAudioAx_80024030(0);
                                    lbl_804799D8.x44[i] = 7;
                                }
                            } else if (pstate2 == 2) {
                                lbAudioAx_80024030(0);
                                lbl_804799D8.x2A[i].state = 3;
                                lbl_804799D8.x2A[i].done = 0;
                            }
                        }
                    } else if ((buttons & 0x10000) || (buttons & 8)) {
                        if (lbl_804799D8.x44[i] == 8) {
                            lbAudioAx_80024030(2);
                            lbl_804799D8.x44[i] = 7;
                        }
                    } else if (((buttons & 0x20000) || (buttons & 4)) &&
                               lbl_804799D8.x44[i] == 7)
                    {
                        lbAudioAx_80024030(2);
                        lbl_804799D8.x44[i] = 8;
                    }
                }
            }
        }
    }
}

extern u8 lbl_804D6680[8];
extern u8 lbl_803B7D04[20];

/// Tournament match timer display/audio state machine.
/// Handles match countdown, audio transitions, and end conditions.
void fn_8019AF50(s32* arg0, u32 arg1, u32 arg2)
{
    typedef struct {
        s32 d[5];
    } TimerFmt;
    TimerFmt sp_buf;
    u32 buttons;
    TmData* tm = (TmData*) arg0;
    s32 bracketIdx;

    sp_buf = *(TimerFmt*) lbl_803B7D04;
    bracketIdx = fn_8018F74C();

    switch (*arg0) {
    case 0x1F:
        fn_8019B860(tm);
        break;
    }

    if (tm->x33 == 6) {
        if (lbl_804D6680[0] == 2) {
            if (lbAudioAx_80023730() == 0) {
                lbAudioAx_80023F28(
                    lbAudioAx_8002305C(fn_8018F6FC(lbl_804D6680[1]), 0));
                lbl_804D6680[0] = 3;
            }
        } else if (lbl_804D6680[0] == 0) {
            u8* bp = (u8*) &lbl_80473AB8[bracketIdx];
            s32 j = 0;
            s32 n;

            for (n = 4; n != 0; n--) {
                if (bp[0x30] != 0 && bp[0x4C] == 0) {
                    lbl_804D6680[1] =
                        (&lbl_80473AB8[bracketIdx].x4D)[j * 0x2C];
                    break;
                }
                bp += 0x2C;
                j++;
            }

            lbAudioAx_80023F28(fn_80160400(fn_8018F6FC(lbl_804D6680[1])));
            lbl_804D6680[0] = 1;
        } else if (lbl_804D6680[0] == 1) {
            u8* timer_ptr = &lbl_804D6680[2];
            if (*timer_ptr > 0x3C) {
                lbl_804D6680[0] = 2;
            }
            (*timer_ptr)++;
        }
    }

    if (lbl_804799D8.x4D != 1) {
        buttons = (u32) gm_801A36A0(lbl_804799D8.x4C);
    } else {
        buttons = (u32) gm_801A36A0(4);
    }

    if (lbl_80473AB8[bracketIdx].x18 != 0) {
        if (lbl_804799D8.x0 < 0xFAU) {
            lbl_804799D8.x0++;
            if (lbl_804799D8.x0 >= 0x64U) {
                int i;
                u32 count = (u32) (lbl_804799D8.x0 - 0x64) / 15;
                u8* base = (u8*) &lbl_804799D8;
                u8* dest = (u8*) &sp_buf;
                for (i = 0; i < count; i++) {
                    dest[0] = base[0x4E];
                    dest[1] = base[0x4F];
                    base += 2;
                    dest += 2;
                }
            }
            HSD_SisLib_803A70A0(tm->x524[3], 0, (char*) &sp_buf);
        } else {
            lbl_804799D8.x0 += 2;
            if (lbl_804799D8.x4D != 1) {
                if (lbl_804799D8.x0 > 0xFAU) {
                    lbl_804799D8.x0 = 0xFA;
                }
            }
            HSD_SisLib_803A70A0(tm->x524[3], 0, (char*) &lbl_804799D8 + 0x4E);
        }
    } else {
        if (lbl_804799D8.x0 < 0xFAU) {
            lbl_804799D8.x0 = 0xFA;
        }
    }

    if (*arg0 == 0x27) {
        if (lbl_804799D8.x0 >= 0xFAU) {
            if (tm->x33 == 6) {
                if (lbl_804799D8.x0 >= 0x1C20U || (buttons & 0x1100)) {
                    gm_801A42F8(1);
                    gm_801A4B60();
                }
            } else {
                fn_8018EC48();
                *arg0 = 0x13;
            }
        }
    }
}

/// @todo Currently 89.97% match - permuter couldn't improve
/// Per-frame update for tournament mode menu.
void gm_8019B2DC_OnFrame(void)
{
    s32 sp[13];
    u32 arg1;
    TmData* data;
    u32 arg2;
    s32 cond;
    s32 val;
    s32 i;
    s32* dest;
    TmData* ptr;
    s32 stage;
    PAD_STACK(4);

    data = gm_8018F634();
    arg1 = fn_8018F674(4);
    arg2 = fn_8018F640(4);

    if (gm_8018F634()->cur_option >= 0x13 && gm_8018F634()->cur_option <= 0x1A)
    {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        fn_8019A71C((s32*) data, arg1, arg2);
    } else {
        if (gm_8018F634()->cur_option >= 0x1B &&
            gm_8018F634()->cur_option <= 0x1E)
        {
            cond = 1;
        } else {
            cond = 0;
        }
        if (cond != 0) {
            fn_8019A86C(data, arg1, arg2);
        } else {
            fn_8019AF50((s32*) data, arg1, arg2);
        }
    }

    val = data->stage_selection_type;
    if ((val == 0 && data->x32 == 0) || val == 1) {
        cond = 1;
    } else {
        cond = 0;
    }
    if (cond != 0) {
        stage = lbl_804D4190;
    } else {
        stage = data->x28;
    }
    sp[0] = stage;

    ptr = data;
    dest = sp;
    i = 0;
    do {
        dest[1] = ptr->x4B8[0].x0;
        dest[5] = fn_8018F6FC(ptr->x4B8[0].x1);
        i += 1;
        dest[9] = ptr->x4B8[0].x3;
        ptr = (TmData*) ((u8*) ptr + 0xA);
        dest += 1;
    } while (i < 4);

    fn_8019BA04(sp);
}

/// Transitions to results screen after a tournament match.
/// Ranks players, preloads stage/character data, and starts audio.
void fn_8019B458(s32* arg0)
{
    TmData* tm = (TmData*) arg0;
    struct Lbl804799D8_t* d8 = &lbl_804799D8;
    s32 i;
    s32 rank;
    s32 x24;
    TmData* td;

    s32 costumes[4];
    s32 charIDs[4];
    PAD_STACK(0x10);

    rank = 0;
    tm->x24++;
    d8->x0 = rank;
    tm->pad_x34[0] = tm->x33;

    td = gm_8018F634();
    x24 = td->x24;

    if (x24 > (s32) lbl_803DA0D0.rank_thresholds[td->entrants][5]) {
        rank = 6;
    } else {
        for (i = 5; i >= 0; i--) {
            if (x24 <= (s32) lbl_803DA0D0.rank_thresholds[td->entrants][i]) {
                rank = i;
            }
        }
    }

    tm->x33 = rank;

    {
        s32 match = fn_80196CF8();
        TmData* td2 = gm_8018F634();
        fn_80198D18();

        {
            HSD_GObj* gobj = fn_8019035C(0, lbl_804D6670->models[3], match,
                                         0x1A, 3, 1, fn_80196EEC, 0.0f);

            if ((s32) td2->pad_x34[0] == match) {
                HSD_JObjSetFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
            }
        }

        if (match < 4) {
            d8->x1B = 0x50;
        } else if (match == 4) {
            d8->x1B = 0x5F;
        } else {
            d8->x1B = 0x61;
        }

        fn_80198BA0();
        fn_8018E618(tm->entrants, 4.5f, tm->x2C);
        fn_8018E85C(lbl_804D6670->models[4], tm->x2C);
        fn_8018FA24();

        tm->cur_option = 0x14;
        tm->x2C = 0;

        for (i = 0; i < 4; i++) {
            if (tm->x4B8[i].x0 != 3) {
                charIDs[i] = fn_8018F6FC(tm->x4B8[i].x1);
                costumes[i] = tm->x4B8[i].x3;
            }
        }

        {
            volatile InternalStageId stageID;
            s32 use_random_stage;

            if ((tm->stage_selection_type == 0 && tm->x32 == 0) ||
                tm->stage_selection_type == 1)
            {
                use_random_stage = 1;
            } else {
                use_random_stage = 0;
            }

            if (use_random_stage != 0) {
                gm_8018F634();
                do {
                    lbl_804D4190 = fn_8018F4A0();
                    if (lbl_804D4194 == lbl_804D4190) {
                        if (fn_801642A0() != 0) {
                            break;
                        }
                    } else {
                        break;
                    }
                } while (true);
                lbl_804D4194 = lbl_804D4190;
                stageID = lbl_804D4190;
            } else {
                stageID = tm->x28;
            }

            {
                PreloadCacheScene* scene = lbDvd_8001822C();
                struct GameCache* gc = &scene->game_cache;
                lbDvd_800174BC();

                if (tm->x4B8[0].x0 != 3) {
                    gc->entries[0].char_id = charIDs[0];
                    gc->entries[0].color = costumes[0];
                }

                if (tm->x4B8[1].x0 != 3) {
                    gc->entries[1].char_id = charIDs[1];
                    gc->entries[1].color = costumes[1];
                }

                if (tm->x4B8[2].x0 != 3) {
                    gc->entries[2].char_id = charIDs[2];
                    gc->entries[2].color = costumes[2];
                }

                if (tm->x4B8[3].x0 != 3) {
                    gc->entries[3].char_id = charIDs[3];
                    gc->entries[3].color = costumes[3];
                }

                {
                    s32 skip_stage_cache;
                    if ((tm->stage_selection_type == 2 && tm->x32 == 0) ||
                        tm->stage_selection_type == 3)
                    {
                        skip_stage_cache = 1;
                    } else {
                        skip_stage_cache = 0;
                    }
                    if (skip_stage_cache == 0) {
                        gc->stage_id = stageID;
                    }
                }

                lbDvd_80018254();
            }

            {
                u64 audio_mask = 0;
                for (i = 0; i < 4; i++) {
                    if (tm->x4B8[i].x0 != 3) {
                        audio_mask |= lbAudioAx_80026E84(charIDs[i]);
                    }
                }
                audio_mask |= lbAudioAx_80026EBC(stageID);
                lbAudioAx_80026F2C(0x1C);
                lbAudioAx_8002702C(0xC, audio_mask);
                lbAudioAx_80027168();
            }
        }
    }
}

/// Initializes match data and transitions to next state.
/// Type cast used to match target stw instruction pattern.
void fn_8019B81C(s32* state)
{
    fn_80198BA0();
    fn_80198EBC();
    *state = 0x1C;
    lbl_804799D8.x0 = 0;
}

extern SceneDesc* lbl_804D6670;

void fn_8019B860(TmData* tm)
{
    fn_8019A158();
    fn_80199AF0();
    fn_80198BA0();
    fn_8018F888();
    fn_8018E618(tm->entrants, 4.5f, tm->x2C);
    fn_8018E85C(lbl_804D6670->models[4], tm->x2C);
    tm->cur_option = 0x20;
}

void gm_8019B8C4_OnEnter(void* arg0)
{
    lbl_804D6668 = NULL;
    lbl_804D6664 = NULL;
    lbl_804D6680[0] = 0;
    lbl_804D6680[2] = 0;
    gm_8018F634();
    lbl_804D6660 = lbArchive_80016DBC("GmTou1p", &lbl_804D666C,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6638 = lbArchive_80016DBC(
        "TmBox.dat", &lbl_804771B8.box2, "tournament_box2_array",
        &lbl_804771B8.box3, "tournament_box3_array", &lbl_804771B8.box4,
        "tournament_box4_array", 0);
    lbl_804D6664 = lbArchive_80016DBC("GmTou3p", &lbl_804D6670,
                                      "ScGamTour_scene_data", 0);
    lbl_804D6668 = lbArchive_80016DBC("GmTou4p", &lbl_804D6674,
                                      "ScGamTour_scene_data", 0);
    HSD_SisLib_803A62A0(0, fn_8018F5F0(), "SIS_TournamentData");
    if (HSD_Randi(2) != 0) {
        lbAudioAx_80023F28(0x5D);
        return;
    }
    lbAudioAx_80023F28(0x5E);
}

void gm_8019B9C8_OnLeave(void* arg0)
{
    lbArchive_80016EFC(lbl_804D6660);
    lbArchive_80016EFC(lbl_804D6638);
    lbArchive_80016EFC(lbl_804D6664);
    lbArchive_80016EFC(lbl_804D6668);
}

void fn_8019BA04(s32* state) {}
