#include "hsd_392A.h"

#include <stdio.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/psstructs.h> // IWYU pragma: keep

// types

// .bss

typedef struct {
    /* 0x00 */ void* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        u8 bytes[0x80];
        char text[0x80];
        struct {
            s32 count;
            u32 color;
        } bars[16];
        struct {
            f32 pos;
            u32 color;
        } gradient[16];
    } content;
} PerfDispItem;

static PerfDispItem hsd_804CE3F8[6];

/* 4D7858 */ static f32 hsd_804D7858;
/* 4D785C */ static f32 hsd_804D785C;
/* 4D7860 */ static f32 hsd_804D7860;
/* 4D7864 */ static f32 hsd_804D7864;
/* 4D7868 */ static f32 hsd_804D7868;
/* 4D786C */ static f32 hsd_804D786C;
/* 4D7870 */ static s32 hsd_804D7870;
/* 4D7874 */ static s32 hsd_804D7874;
/* 4D7878 */ static s32 hsd_804D7878;
/* 4D787C */ static f32 hsd_804D787C;
/* 4D7880 */ static f32 hsd_804D7880;
/* 4D7884 */ static f32 hsd_804D7884;
/* 4D7888 */ static s32 hsd_804D7888;

void fn_80392934(void)
{
    f32 cpu;
    f32 draw;
    f32 total;

    cpu = HSD_PerfLastStat.cpu_time;
    hsd_804D7858 = cpu;
    draw = HSD_PerfLastStat.draw_time;
    hsd_804D785C = draw;
    total = HSD_PerfLastStat.total_time;
    hsd_804D7860 = total;

    if (hsd_804D7864 < cpu || hsd_804D7870-- < 0) {
        hsd_804D7864 = cpu;
        hsd_804D7870 = 60;
    }
    if (hsd_804D7868 < draw || hsd_804D7874-- < 0) {
        hsd_804D7868 = draw;
        hsd_804D7874 = 60;
    }
    if (hsd_804D786C < total || hsd_804D7878-- < 0) {
        hsd_804D786C = total;
        hsd_804D7878 = 60;
    }
    if (hsd_804D787C < cpu) {
        hsd_804D787C = cpu;
    }
    if (hsd_804D7880 < draw) {
        hsd_804D7880 = draw;
    }
    if (hsd_804D7884 < total) {
        hsd_804D7884 = total;
    }
}

static s32 lbl_804D6088 = 4;
static s32 lbl_804D608C = 1;

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_80392A08(int mode, int scale, int enable)
{
    lbl_804D6088 = mode;
    lbl_804D608C = scale;
    if (hsd_804D7888 == 0 && enable != 0) {
        hsd_804D787C = 0.0F;
        hsd_804D7880 = 0.0F;
        hsd_804D7884 = 0.0F;
    }
    hsd_804D7888 = enable;
}
#ifdef MUST_MATCH
#pragma pop
#endif

static s32 lbl_804D6090 = -1;
static s32 lbl_804D6094 = (s32) 0xFF0000FF;
static s32 lbl_804D6098 = 0x00FF00FF;
static s32 lbl_804D609C = 0x00FFFFFF;
static s32 lbl_804D60A0 = 0x8080FF;
static s32 lbl_804D60A4 = (s32) 0xC0C000FF;

static inline PerfDispItem* get_perf_disp_item(s32 count)
{
    return &hsd_804CE3F8[count];
}

void* fn_80392A3C(void)
{
    volatile s32 green;
    s32 numFrames;
    s32 bar_count;
    s32 count;
    PerfDispItem* entry;
    PerfDispItem* entry2;

    count = 0;
    numFrames = lbl_804D6088;
    if (0 != numFrames) {
        u8* counts = &hsd_804CE3F8[0].content.bytes[0];
        u8* colors = &hsd_804CE3F8[0].content.bytes[4];
        // Self-assign forces colors into r5 and green's stack slot to 0x8.
#ifdef MUST_MATCH
        colors = colors;
#endif
        hsd_804CE3F8[0].type = 1;
        *(s32*) counts = 1;
        bar_count = count;
        bar_count++;
        green = lbl_804D6098;
        *(s32*) colors = green;
        if (numFrames > 1) {
            s32 val = numFrames - 1;
            if (val > 3) {
                val = 3;
            }
            *(s32*) (counts + bar_count * 8) = val;
            *(s32*) (colors + bar_count * 8) = lbl_804D60A4;
            bar_count = 2;
        }
        if (numFrames > 4) {
            *(s32*) (counts + bar_count * 8) = numFrames - 4;
            *(s32*) (colors + bar_count * 8) = lbl_804D6094;
            bar_count++;
        }
        *(s32*) (counts + bar_count * 8) = -1;
        hsd_804CE3F8[0].next = &hsd_804CE3F8[1];
        hsd_804CE3F8[1].type = 2;
        count = 4;
        hsd_804CE3F8[1].content.gradient[0].pos =
            hsd_804D7860 / (f32) numFrames;
        hsd_804CE3F8[1].content.gradient[0].color = lbl_804D609C;
        hsd_804CE3F8[1].content.gradient[1].pos =
            (f32) (s32) (0.9999F + hsd_804D7860) / (f32) numFrames;
        hsd_804CE3F8[1].content.gradient[1].color = lbl_804D60A0;
        hsd_804CE3F8[1].content.gradient[2].pos = -1.0F;
        hsd_804CE3F8[1].next = &hsd_804CE3F8[2];
        hsd_804CE3F8[2].type = 2;
        hsd_804CE3F8[2].content.gradient[0].pos =
            hsd_804D785C / (f32) numFrames;
        hsd_804CE3F8[2].content.gradient[0].color = lbl_804D6090;
        hsd_804CE3F8[2].content.gradient[1].pos = -1.0F;
        hsd_804CE3F8[2].next = &hsd_804CE3F8[3];
        hsd_804CE3F8[3].type = 2;
        hsd_804CE3F8[3].content.gradient[0].pos =
            hsd_804D7858 / (f32) numFrames;
        hsd_804CE3F8[3].content.gradient[0].color = green;
        hsd_804CE3F8[3].content.gradient[1].pos = -1.0F;
        hsd_804CE3F8[3].next = &hsd_804CE3F8[4];
    }
    if (lbl_804D608C != 0) {
        hsd_804CE3F8[count].type = 0;
        entry = get_perf_disp_item(count);
        sprintf(entry->content.text,
                "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f  "
                "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f",
                hsd_804D7858, hsd_804D785C, hsd_804D7860, hsd_804D7864,
                hsd_804D7868, hsd_804D786C);
        entry->next = &hsd_804CE3F8[count + 1];
        count++;
        if (hsd_804D7888 != 0) {
            hsd_804CE3F8[count].type = 0;
            entry2 = &hsd_804CE3F8[count];
            sprintf(entry2->content.text,
                    "\\c00ff00%2.3f \\cffffff%2.3f \\c00ffff%2.3f",
                    hsd_804D787C, hsd_804D7880, hsd_804D7884);
            entry2->next = &hsd_804CE3F8[count + 1];
            count++;
        }
    }
    if (count == 0) {
        return NULL;
    }
    hsd_804CE3F8[count - 1].next = NULL;
    return hsd_804CE3F8;
}
