#include "lbarchive.h"
#include "lbcardnew.h"
#include "lblanguage.h"

#include "lbsnap.static.h"
#include <placeholder.h>

#include "ft/ft_0877.h"
#include "gm/gm_unsplit.h"
#include "it/it_266F.h"

#include <stdio.h>
#include <dolphin/card.h>
#include <dolphin/os.h>
#include <dolphin/os/OSTime.h>
#include <baselib/debug.h>
#include <baselib/hsd_3B34.h>

void lbSnap_8001D2BC(void)
{
    int i;
    for (i = 0; i < (signed) ARRAY_SIZE(lbSnap_80433380.x4C_cardState); i++) {
        int prev = lbSnap_80433380.x4C_cardState[i];
        lbSnap_80433380.x4C_cardState[i] = CARDProbe(i);
        if (lbSnap_80433380.x4C_cardState[i] != prev) {
            lbSnap_80433380.x54_stateChanged[i] = true;
        }
    }
}

int lbSnap_8001D338(int arg0)
{
    return lbSnap_80433380.x54_stateChanged[arg0];
}

int lbSnap_8001D350(int chan)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    if (ptr->card_result == 0 && lbSnap_80433380.x54_stateChanged[chan]) {
        ptr->card_result = 8;
    }
    return ptr->card_result;
}

int lbSnap_8001D394(int chan)
{
    return lbSnap_80433380.x48[chan].num;
}

int lbSnap_8001D3B0(int chan)
{
    return lbSnap_80433380.x48[chan].free_blocks;
}

int lbSnap_8001D3CC(int chan)
{
    return lbSnap_80433380.x48[chan].free_files;
}

int lbSnap_8001D3E8(int chan, int index)
{
    return lbSnap_80433380.x48[chan].entries[index].blocks;
}

int lbSnap_8001D40C(int chan)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    lbSnap_80433380.x54_stateChanged[chan] = 0;
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
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
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

int lbSnap_8001D5FC(int chan, int index)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text[0x21];
    int ret;
    PAD_STACK(8);

    if (ptr->card_result == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        lbSnap_ClearText(text);
        sprintf(text, "%u", lbSnap_80433380.x48[chan].entries[index].time);
        lbSnap_80433380.x48[chan].card_result = 8;
        ret = lb_8001B99C(chan, text, 0);
    }
    return ret;
}

int lbSnap_8001D7B0(int chan, int index, int jndex)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text1[0x21];
    char text2[0x21];
    char text3[0x21];
    int ret;
    PAD_STACK(8);

    if (ptr->card_result == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        lbSnap_ClearText(text1);
        sprintf(text1, "%u", lbSnap_80433380.x48[chan].entries[index].time);
        HSD_ASSERTMSG(410, jndex < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        lbSnap_ClearText(text2);
        sprintf(text2, "%u", lbSnap_80433380.x48[chan].entries[jndex].time);
        lbSnap_8001D4A4(chan, text3);
        lbSnap_80433380.x48[chan].card_result = 8;
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

#define RGB565_TO_RGB5A3(x)                                                   \
    (((x) & RGB5A3_MASK_B) | (((x) >> 1) & (RGB5A3_MASK_R | RGB5A3_MASK_G)) | \
     RGB5A3_MASK_A)

static inline int lbSnap_GetTiledRGBOffset(int x, int y, int tile_stride)
{
    return ((((x / 4) * tile_stride) + (y / 4)) << 5) + ((x % 4) * 8) +
           ((y % 4) * 2);
}

static inline int lbSnap_GetTiledYOff(int tile_column, int y)
{
    return (((y / 4) + tile_column) << 5) + ((y % 4) * 2);
}

static inline u8* lbSnap_GetMemSnapIconData(void)
{
    return (u8*) lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[0];
}

static inline int lbSnap_GetTiledColumn(int x)
{
    return (x / 4) * 24;
}

void lbSnap_8001DA5C(int arg0)
{
    u8* dst = lbSnap_GetMemSnapIconData();
    int dst_x;
    int ctr;
    PAD_STACK(8);

    for (dst_x = 0; dst_x < 32; dst_x++) {
        int src_x = (dst_x * 204 / 32) + 138;
        u8* dst_col = dst + ((dst_x % 4) * 8);
        int tile_column = lbSnap_GetTiledColumn(dst_x);
        int dst_y = 0;
        int src_y_accum = 0;
        u16 pixel;
        for (ctr = 0; ctr < 32; ctr++) {
            pixel = *(u16*) &((u8*) arg0)[lbSnap_GetTiledRGBOffset(
                src_x, src_y_accum / 64 + 96, 160)];
            *(u16*) &dst_col[lbSnap_GetTiledYOff(tile_column, dst_y + 16)] =
                RGB565_TO_RGB5A3(pixel);
            src_y_accum += 448;

            pixel = *(u16*) &((u8*) arg0)[lbSnap_GetTiledRGBOffset(
                src_x, src_y_accum / 64 + 96, 160)];
            *(u16*) &dst_col[lbSnap_GetTiledYOff(tile_column, dst_y + 17)] =
                RGB565_TO_RGB5A3(pixel);
            src_y_accum += 448;

            dst_y += 2;
        }
    }
}

int lbSnap_8001DC0C(int arg0)
{
    OSTime ticks;
    u32 seconds;
    OSCalendarTime time;
    u32 i;
    char* text;
    int ret = 0;

    lbSnap_80433380.x0->x0 = 4;
    lbSnap_80433380.x0->x4 = 0x280;
    lbSnap_80433380.x0->x6 = 0x1E0;
    lbSnap_80433380.x0->x10 = gm_8016B004();
    it_8026C47C(&lbSnap_80433380.x0->x14);
    lbSnap_80433380.x0->x34 = ft_80087C1C();
    lbSnap_80433380.x0->x8 = 3;
    hsd_803B5C2C(lbSnap_80433380.x0->x8);
    lbSnap_80433380.x0->xC =
        hsd_803B51C8(arg0, lbSnap_80433380.x0->x4, lbSnap_80433380.x0->x6,
                     lbSnap_80433380.x0->x38, 256000);
    if (lbSnap_80433380.x0->xC != 0) {
        ret = 1;
    }
    lbSnap_8001DA5C(arg0);
    ticks = OSGetTime();
    seconds = OSTicksToSeconds(ticks);
    OSTicksToCalendarTime(OSSecondsToTicks((u64) seconds), &time);
    for (i = 0; i < sizeof(lbSnap_80433380.x4_string); i++) {
        lbSnap_80433380.x4_string[i] = 0;
    }
    if (lbLang_IsSettingJP()) {
        text = "大乱闘スマッシュブラザーズＤＸ  写真データ";
    } else {
        text = "Super Smash Bros. Melee         Snapshot";
    }
    sprintf(lbSnap_80433380.x4_string, "%s %02d/%02d %02d:%02d:%02d", text,
            time.mon + 1, time.mday, time.hour, time.min, time.sec);
    return ret;
}

int lbSnap_8001DE8C(void* arg0)
{
    int ret = 0;
    if (lbSnap_80433380.x0->x0 == 4) {
        int temp = hsd_803B6BE4(lbSnap_80433380.x0->x38,
                                lbSnap_80433380.x0->xC, arg0);
        DCFlushRange(arg0,
                     lbSnap_80433380.x0->x4 * lbSnap_80433380.x0->x6 * 2);
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

#pragma push
#pragma global_optimizer off
int lbSnap_8001DF20(void)
{
    struct Unk80433380_0* snap = lbSnap_80433380.x0;
    struct Unk803BACC8* tmp;
    lbSnap_803BACC8.x14 = lbSnap_GetSaveDataOffset(snap);
    tmp = &lbSnap_803BACC8;
    lbSnap_803BACC8.x1C = snap;
    return lb_8001C4A8(&tmp->x14, &lbSnap_803BACC8);
}
#pragma pop

int lbSnap_8001DF6C(int chan)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text[0x21];
    int ret;

    if (ptr->card_result == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        struct Unk803BACC8* desc = &lbSnap_803BACC8;
        int chan_arg = chan;
        lbSnap_80433380.x48[chan].card_result = 8;
        lbSnap_8001D4A4(chan_arg, text);
        desc->x14 = lbSnap_GetSaveDataOffset(lbSnap_80433380.x0);
        desc->x1C = lbSnap_80433380.x0;
        ret = lb_8001BB48(chan, text, &desc->x14, desc,
                          lbSnap_80433380.x4_string,
                          lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[0],
                          lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[1], 0);
    }
    return ret;
}

int lbSnap_8001E058(int chan, int index)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    int ret;
    char text[0x21];
    PAD_STACK(8);

    if (ptr->card_result == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->card_result = 8;
    }
    ret = ptr->card_result;
    if (ret == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        lbSnap_ClearText(text);
        sprintf(text, "%u", lbSnap_80433380.x48[chan].entries[index].time);
        lbSnap_803BACC8.x1C = lbSnap_80433380.x0;
        ret = lb_8001BF04(chan, text, &lbSnap_803BACC8.x14,
                          lbSnap_80433380.x4_string,
                          lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[0],
                          lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[1], 0);
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
    lbSnap_80433380.x0 = arg0;
    lbSnap_80433380.x48 = arg1;
    lbSnap_80433380.x48->card_result = 8;
    lbSnap_80433380.x48[1].card_result = 8;
    lbArchive_80016DBC("LbMcSnap.",
                       (void**) &lbSnap_80433380.x44_LbMcSnap_MemSnapIconData,
                       "MemSnapIconData", 0);
}

void lbSnap_8001E27C(void)
{
    lbSnap_80433380.x0 = 0;
    lbSnap_80433380.x48 = NULL;
}

void lbSnap_8001E290(void)
{
    int chan; // EXIChannel doesn't optimize the loop properly
    lbSnap_80433380.x44_LbMcSnap_MemSnapIconData = NULL;
    for (chan = 0; chan < 2; chan++) {
        lbSnap_80433380.x4C_cardState[chan] = CARDProbe(chan);
        lbSnap_80433380.x54_stateChanged[chan] = 0;
    }
}
