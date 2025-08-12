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
    if (ptr->unk0 == 0 && lbSnap_80433380.x54_stateChanged[chan]) {
        ptr->unk0 = 8;
    }
    return ptr->unk0;
}

int lbSnap_8001D394(int chan)
{
    return lbSnap_80433380.x48[chan].num;
}

int lbSnap_8001D3B0(int chan)
{
    return lbSnap_80433380.x48[chan].unk8;
}

int lbSnap_8001D3CC(int chan)
{
    return lbSnap_80433380.x48[chan].unkC;
}

int lbSnap_8001D3E8(int chan, int index)
{
    return lbSnap_80433380.x48[chan].unk10[index].unk6;
}

int lbSnap_8001D40C(int chan)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    lbSnap_80433380.x54_stateChanged[chan] = 0;
    ptr->unk0 = lb_8001BFD8(chan, &ptr->unk10, &ptr->unk8, &ptr->unkC);
    if (ptr->unk0 == 0) {
        int i;
        for (i = 0; i < 0x7F; i++) {
            if (ptr->unk10[i].unk4 == -1) {
                break;
            }
        }
        ptr->num = i;
    }
    return ptr->unk0;
}

void lbSnap_8001D4A4(int chan, char* arg1)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    OSTime time2 = OSGetTime();
    unsigned int time = OSTicksToSeconds(time2);
    int i;

    do {
        i = 0;
        while (i < ptr->num) {
            if (time == ptr->unk10[i].unk0) {
                time++;
                break;
            }
            i++;
        }
    } while (i != ptr->num);

    i = 0;
    while (i < 0x21) {
        arg1[i] = '\0';
        i++;
    }
    sprintf(arg1, "%u", time);
}

int lbSnap_8001D5FC(int chan, int index)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text[0x21];
    int i;
    PAD_STACK(8);

    if (ptr->unk0 == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->unk0 = 8;
    }
    if (ptr->unk0 == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        i = 0;
        while (i < 0x21) {
            text[i] = '\0';
            i++;
        }
        sprintf(text, "%u", lbSnap_80433380.x48[chan].unk10[index].unk0);
        lbSnap_80433380.x48[chan].unk0 = 8;
        return lb_8001B99C(chan, text, 0);
    } else {
        return ptr->unk0;
    }
}

int lbSnap_8001D7B0(int chan, int index, int jndex)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text1[0x21];
    char text2[0x21];
    char text3[0x21];
    int i;
    PAD_STACK(8);

    if (ptr->unk0 == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->unk0 = 8;
    }
    if (ptr->unk0 == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        i = 0;
        while (i < 0x21) {
            text1[i] = '\0';
            i++;
        }
        sprintf(text1, "%u", lbSnap_80433380.x48[chan].unk10[index].unk0);
        HSD_ASSERTMSG(410, jndex < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        i = 0;
        while (i < 0x21) {
            text2[i] = '\0';
            i++;
        }
        sprintf(text2, "%u", lbSnap_80433380.x48[chan].unk10[jndex].unk0);
        lbSnap_8001D4A4(chan, text3);
        lbSnap_80433380.x48[chan].unk0 = 8;
        return lb_8001C0F4(chan, text1, text2, text3, 0);
    } else {
        return ptr->unk0;
    }
}

// RGB5A3:  A RRRRR GGGGG BBBBB
// RGB565:   RRRRR GGGGGG BBBBB

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

void lbSnap_8001DA5C(int arg0)
{
    int r4, r5, r6, r7, r9, r10, r25, r27, r28, ctr;

    r7 = 0;
    for (r10 = 0; r10 < 32; r10++) {
        r4 = r7 / 32;
        r6 = r10 / 4 * 24;
        r27 = (r4 + 138) / 4 * 160;
        r5 = lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[(r10 % 4) * 2];
        r9 = 0;
        r4 = 0;
        for (ctr = 0; ctr < 32; ctr++) {
            // converting r25 from RGB565 to RGB5A3
            // keep B where it is
            // rightshift R and G, discarding the bottom bit of G
            // A is fixed fully opaque

            r28 = r4 / 64;
            r25 = *(unsigned short*) (arg0 + (((((r28 + 96) / 4) + r27) << 5) +
                                              (((r4 + 138) % 4) * 8) +
                                              (((r28 + 96) % 4) * 2)));
            *(unsigned short*) (r5 + (((((r9 + 16) / 4) + r6) << 5) +
                                      (((r9 + 16) % 4) * 2))) =
                RGB565_TO_RGB5A3(r25);
            r4 += 448; // height in pixels?

            r28 = r4 / 64;
            r25 = *(unsigned short*) (arg0 + (((((r28 + 96) / 4) + r27) << 5) +
                                              (((r4 + 138) % 4) * 8) +
                                              (((r28 + 96) % 4) * 2)));
            *(unsigned short*) (r5 + (((((r9 + 17) / 4) + r6) << 5) +
                                      (((r9 + 17) % 4) * 2))) =
                RGB565_TO_RGB5A3(r25);
            r4 += 448;

            r9 += 2;
        }
        r7 += 204;
    }
}

int lbSnap_8001DC0C(int arg0)
{
    OSTime ticks;
    OSTime seconds;
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
    ticks = OSSecondsToTicks(seconds);
    OSTicksToCalendarTime(ticks, &time);
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

void lbSnap_8001DF20(void)
{
    lbSnap_803BACC8.x14 =
        lbSnap_80433380.x0->xC +
        ((int) &lbSnap_80433380.x0->x38 - (int) &lbSnap_80433380.x0->x0);
    lbSnap_803BACC8.x1C = lbSnap_80433380.x0;
    lb_8001C4A8(&lbSnap_803BACC8.x14, &lbSnap_803BACC8);
}

int lbSnap_8001DF6C(int chan)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    char text[0x21];
    PAD_STACK(8);

    if (ptr->unk0 == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->unk0 = 8;
    }
    if (ptr->unk0 == 0) {
        lbSnap_80433380.x48[chan].unk0 = 8;
        lbSnap_8001D4A4(chan, text);
        lbSnap_803BACC8.x14 =
            lbSnap_80433380.x0->xC +
            ((int) &lbSnap_80433380.x0->x38 - (int) &lbSnap_80433380.x0->x0);
        lbSnap_803BACC8.x1C = lbSnap_80433380.x0;
        return lb_8001BB48(chan, text, &lbSnap_803BACC8.x14, &lbSnap_803BACC8,
                           lbSnap_80433380.x4_string,
                           lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[0],
                           lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[1], 0);
    } else {
        return ptr->unk0;
    }
}

int lbSnap_8001E058(int chan, int index)
{
    struct Unk80433380_48* ptr = &lbSnap_80433380.x48[chan];
    int i;
    char text[0x21];
    PAD_STACK(8);

    if (ptr->unk0 == 0 && lbSnap_80433380.x54_stateChanged[chan] != 0) {
        ptr->unk0 = 8;
    }
    if (ptr->unk0 == 0) {
        HSD_ASSERTMSG(410, index < lbSnap_80433380.x48[chan].num,
                      "index < _p(slot)[chan].num");
        i = 0;
        while (i < 0x21) {
            text[i] = '\0';
            i++;
        }
        sprintf(text, "%u", lbSnap_80433380.x48[chan].unk10[index].unk0);
        lbSnap_803BACC8.x1C = lbSnap_80433380.x0;
        return lb_8001BF04(chan, text, &lbSnap_803BACC8.x14,
                           lbSnap_80433380.x4_string,
                           lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[0],
                           lbSnap_80433380.x44_LbMcSnap_MemSnapIconData[1], 0);
    } else {
        return ptr->unk0;
    }
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
    lbSnap_80433380.x48->unk0 = 8;
    lbSnap_80433380.x48[1].unk0 = 8;
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
