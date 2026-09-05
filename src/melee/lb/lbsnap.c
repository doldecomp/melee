#include "lbarchive.h"
#include "lbcardnew.h"
#include "lblanguage.h"

#include "lbsnap.static.h"

#include <melee/it/itspawn.h>

#define _p(x) (lbSnap_80433380.x)
#include <placeholder.h>

#include <melee/ft/ft_0877.h>
#include <melee/gm/gm_unsplit.h>

#include <stdio.h>
#include <dolphin/card.h>
#include <dolphin/os.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/hsd_3B34.h>

void lbSnap_8001D2BC(void)
{
    int i;
    for (i = 0; i < (signed) ARRAY_SIZE(_p(x4C_cardState)); i++) {
        int prev = _p(x4C_cardState)[i];
        _p(x4C_cardState)[i] = CARDProbe(i);
        if (_p(x4C_cardState)[i] != prev) {
            _p(x54_stateChanged)[i] = true;
        }
    }
}

int lbSnap_8001D338(int arg0)
{
    return _p(x54_stateChanged)[arg0];
}

int lbSnap_8001D350(int chan)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    if (ptr->card_result == 0 && _p(x54_stateChanged)[chan]) {
        ptr->card_result = 8;
    }
    return ptr->card_result;
}

int lbSnap_8001D394(int chan)
{
    return _p(slot)[chan].num;
}

int lbSnap_8001D3B0(int chan)
{
    return _p(slot)[chan].free_blocks;
}

int lbSnap_8001D3CC(int chan)
{
    return _p(slot)[chan].free_files;
}

int lbSnap_8001D3E8(int chan, int index)
{
    return _p(slot)[chan].entries[index].blocks;
}

int lbSnap_8001D40C(int chan)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    _p(x54_stateChanged)[chan] = 0;
    ptr->card_result =
        lb_8001BFD8(chan, ptr->entries, &ptr->free_blocks, &ptr->free_files);
    if (ptr->card_result == 0) {
        int i;
        for (i = 0; i < 0x7F; i++) {
            if (ptr->entries[i].file_no == -1) {
                break;
            }
        }
        ptr->num = i;
    }
    return ptr->card_result;
}

void lbSnap_8001D4A4(int chan, char* arg1)
{
    int new_var;
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    OSTime time2 = OSGetTime();
    unsigned int time = OSTicksToSeconds(time2);
    int i;
    new_var = ptr->num;

    do {
        for (i = 0; i < new_var; i++) {
            if (time == ptr->entries[i].time) {
                time++;
                break;
            }
        }
    } while (i != ptr->num);

    for (i = 0; i < 0x21; i++) {
        arg1[i] = '\0';
    }
    sprintf(arg1, "%u", time);
}

static inline void lbSnap_ClearText(char* text)
{
    int i;

    for (i = 0; i < 0x21; i++) {
        text[i] = '\0';
    }
}

static inline void lbSnap_FormatTime(int chan, int index, char* text)
{
    HSD_ASSERT(410, index < _p(slot)[chan].num);
    lbSnap_ClearText(text);
    sprintf(text, "%u", _p(slot)[chan].entries[index].time);
}

int lbSnap_8001D5FC(int chan, int index)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    char text[0x21];
    int ret;
    PAD_STACK(8);

    if (ptr->card_result == 0 && _p(x54_stateChanged)[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        lbSnap_FormatTime(chan, index, text);
        _p(slot)[chan].card_result = 8;
        ret = lb_8001B99C(chan, text, 0);
    }
    return ret;
}

int lbSnap_8001D7B0(int chan, int index, int jndex)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    char text1[0x21];
    char text2[0x21];
    char text3[0x21];
    int ret;
    PAD_STACK(8);

    if (ptr->card_result == 0 && _p(x54_stateChanged)[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        lbSnap_FormatTime(chan, index, text1);
        lbSnap_FormatTime(chan, jndex, text2);
        lbSnap_8001D4A4(chan, text3);
        _p(slot)[chan].card_result = 8;
        ret = lb_8001C0F4(chan, text1, text2, text3, 0);
    }
    return ret;
}

/// RGB5A3:  A RRRRR GGGGG BBBBB
/// RGB565:   RRRRR GGGGGG BBBBB

#define RGB5A3_MASK_A (0x8000)
#define RGB5A3_MASK_R (0x7C00)
#define RGB5A3_MASK_G (0x03E0)
#define RGB5A3_MASK_B (0x001F)

#define RGB565_MASK_R (0xF800)
#define RGB565_MASK_G (0x07E0)
#define RGB565_MASK_B (0x001F)

static inline u16 RGB565_TO_RGB5A3(u16 pixel)
{
    u16 result = (pixel >> 1) & (RGB5A3_MASK_R | RGB5A3_MASK_G);
    result |= pixel & RGB5A3_MASK_B;
    return result | RGB5A3_MASK_A;
}

static inline u8* lbSnap_GetMemSnapIconData(void)
{
    return _p(x44_LbMcSnap_MemSnapIconData)[0].ptr;
}

static inline int lbSnap_GetTiledColumn(int x)
{
    return (x / 4) * 24;
}

#ifdef MUST_MATCH
#pragma push
#pragma global_optimizer off
#endif
// Scale the 448x204 snapshot region to 64x32, centered in the 96x32 banner.
void lbSnap_8001DA5C(const u8* src)
{
    u8* banner;        // must be r4
    int src_row_accum; // must be r7
    int row;           // must be r10
    PAD_STACK(24); // temporary in case we need more variables on the stack.

    row = 0;
    src_row_accum = 0;
    banner = lbSnap_GetMemSnapIconData();
    do {
        int src_row_base = src_row_accum / 32; // somehow also needs to be r4
        u8* dst_row = banner + ((row % 4) * 8);
        int dst_tile_row = lbSnap_GetTiledColumn(row);
        int column = 0; // must be r9
        int pair;
        int src_column_accum = 0; // must be r4
        for (pair = 0; pair < 32; pair++) {
            int src_row = src_row_base + 138;
            int src_column_in_tile;
            int src_row_in_tile;
            int src_tile;
            int src_tile_row = (src_row / 4) * 160;
            int pixel_column; // must be r26
            int offset_base;
            u16 rgb565;
            u16 rgb5a3;
            int offset;
            src_tile = src_column_accum / 64;
            pixel_column = src_tile + 96;
            src_tile = pixel_column / 4;
            src_tile += src_tile_row;
            offset_base =
                (src_tile << 5) + ((src_row_in_tile = src_row % 4) << 3);
            offset =
                offset_base + ((src_column_in_tile = pixel_column % 4) << 1);
            pixel_column = column + 16;
            rgb565 = *(u16*) &src[offset];
            offset_base = pixel_column / 4;
            offset = pixel_column % 4;
            src_column_accum += 448; // xd8
            src_tile = src_column_accum / 64;
            pixel_column = src_tile + 96;
            src_tile = pixel_column / 4; // xe8

            src_row_in_tile = src_row % 4;
            src_column_in_tile = pixel_column % 4; // x100 and x114
            offset_base += dst_tile_row;

            rgb5a3 = RGB565_TO_RGB5A3(rgb565);
            src_tile += src_tile_row;
            offset = (offset_base << 5) + (offset << 1);
            *(u16*) &dst_row[offset] = rgb5a3;
            pixel_column = column + 17;
            offset_base = (
#ifdef MUST_MATCH
                              offset_base =
#endif
                                  src_tile << 5) +
                          (offset = src_row_in_tile << 3);
            offset = (src_column_in_tile << 1) + offset_base;
            rgb565 = *(u16*) &src[offset];
            offset_base = pixel_column / 4; // x14c
            offset_base += dst_tile_row;
            rgb5a3 = RGB565_TO_RGB5A3(rgb565);
            offset = (offset_base << 5) + ((pixel_column % 4) << 1);
            *(u16*) &dst_row[offset] = rgb5a3;
            src_column_accum += 448;
            column += 2;
        }

        row++;
        src_row_accum += 204;
    } while (row < 32);
}
#ifdef MUST_MATCH
#pragma pop
#endif

int lbSnap_8001DC0C(u8* arg0)
{
    OSTime ticks;
    u32 seconds;
    OSCalendarTime time;
    u32 i;
    char* text;
    int ret = 0;

    _p(x0)->x0 = 4;
    _p(x0)->x4 = 0x280;
    _p(x0)->x6 = 0x1E0;
    _p(x0)->x10 = gm_8016B004();
    it_8026C47C(&_p(x0)->x14);
    _p(x0)->x34 = ft_80087C1C();
    _p(x0)->x8 = 3;
    hsd_803B5C2C(_p(x0)->x8);
    _p(x0)->xC =
        hsd_803B51C8((int) arg0, _p(x0)->x4, _p(x0)->x6, _p(x0)->x38, 256000);
    if (_p(x0)->xC != 0) {
        ret = 1;
    }
    lbSnap_8001DA5C(arg0);
    ticks = OSGetTime();
    seconds = OSTicksToSeconds(ticks);
    OSTicksToCalendarTime(OSSecondsToTicks((u64) seconds), &time);
    for (i = 0; i < sizeof(_p(x4_string)); i++) {
        _p(x4_string)[i] = 0;
    }
    if (lbLang_IsSettingJP()) {
        text = "大乱闘スマッシュブラザーズＤＸ  写真データ";
    } else {
        text = "Super Smash Bros. Melee         Snapshot";
    }
    sprintf(_p(x4_string), "%s %02d/%02d %02d:%02d:%02d", text, time.mon + 1,
            time.mday, time.hour, time.min, time.sec);
    return ret;
}

int lbSnap_8001DE8C(void* arg0)
{
    int ret = 0;
    if (_p(x0)->x0 == 4) {
        int temp = hsd_803B6BE4(_p(x0)->x38, _p(x0)->xC, arg0);
        DCFlushRange(arg0, _p(x0)->x4 * _p(x0)->x6 * 2);
        if (temp != 0) {
            ret = 1;
        }
    }
    return ret;
}

static inline int lbSnap_GetSaveDataOffset(struct Unk80433380_0* snap)
{
    return snap->xC + ((int) &snap->x38 - (int) snap);
}

#ifdef MUST_MATCH
#pragma push
#pragma global_optimizer off
#endif
int lbSnap_8001DF20(void)
{
    struct Unk80433380_0* snap = _p(x0);
    struct Unk803BACC8* tmp;
    lbSnap_803BACC8.entries[0].file_size = lbSnap_GetSaveDataOffset(snap);
    tmp = &lbSnap_803BACC8;
    lbSnap_803BACC8.entries[0].data = (u8*) snap;
    return lb_8001C4A8(tmp->entries, &lbSnap_803BACC8);
}
#ifdef MUST_MATCH
#pragma pop
#endif

int lbSnap_8001DF6C(int chan)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    char text[0x21];
    int ret;

    if (ptr->card_result == 0 && _p(x54_stateChanged)[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        struct Unk803BACC8* desc = &lbSnap_803BACC8;
        int chan_arg = chan;
        _p(slot)[chan].card_result = 8;
        lbSnap_8001D4A4(chan_arg, text);
        desc->entries[0].file_size = lbSnap_GetSaveDataOffset(_p(x0));
        desc->entries[0].data = (u8*) _p(x0);
        ret = lb_8001BB48(chan, text, desc->entries, desc, _p(x4_string),
                          _p(x44_LbMcSnap_MemSnapIconData)[0].offset,
                          _p(x44_LbMcSnap_MemSnapIconData)[1].size, 0);
    }
    return ret;
}

int lbSnap_8001E058(int chan, int index)
{
    struct Unk80433380_48* ptr = &_p(slot)[chan];
    int ret;
    char text[0x21];
    PAD_STACK(8);

    if (ptr->card_result == 0 && _p(x54_stateChanged)[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        lbSnap_FormatTime(chan, index, text);
        lbSnap_803BACC8.entries[0].data = (u8*) _p(x0);
        ret = lb_8001BF04(chan, text, lbSnap_803BACC8.entries, _p(x4_string),
                          _p(x44_LbMcSnap_MemSnapIconData)[0].offset,
                          _p(x44_LbMcSnap_MemSnapIconData)[1].size, 0);
    }
    return ret;
}

int lbSnap_8001E204(void)
{
    return 0x3E840;
}

int lbSnap_8001E210(void)
{
    return 0x840;
}

void lbSnap_8001E218(void* arg0, struct Unk80433380_48* arg1)
{
    _p(x0) = arg0;
    _p(slot) = arg1;
    _p(slot)->card_result = 8;
    _p(slot)[1].card_result = 8;
    lbArchive_80016DBC("LbMcSnap.", (void**) &_p(x44_LbMcSnap_MemSnapIconData),
                       "MemSnapIconData", 0);
}

void lbSnap_8001E27C(void)
{
    _p(x0) = 0;
    _p(slot) = NULL;
}

void lbSnap_8001E290(void)
{
    int chan; // EXIChannel doesn't optimize the loop properly
    _p(x44_LbMcSnap_MemSnapIconData) = NULL;
    for (chan = 0; chan < 2; chan++) {
        _p(x4C_cardState)[chan] = CARDProbe(chan);
        _p(x54_stateChanged)[chan] = 0;
    }
}
