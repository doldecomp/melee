#include "lbmthp.static.h"

#include "baselib/memory.h"
#include "baselib/video.h"
#include "lb/lbfile.h"

#include <dolphin/dvd.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/os/OSCache.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/sobjlib.h>
#include <melee/lb/lbanim.h>
#include <melee/lb/types.h>
#include <MSL/string.h>
#include <Runtime/runtime.h>

#define LBMTHP_ASSERT(line, cond, msg)                                        \
    ((cond) ? ((void) 0) : __assert(lbl_803BADB0, line, msg))
#define LBMTHP_ASSERTREPORT(line, cond, msg, ...)                             \
    ((cond) ? ((void) 0)                                                      \
            : (OSReport(__VA_ARGS__), __assert(lbl_803BADB0, line, msg)))

void fn_8001E910(int arg0, int arg1, void* arg2, int cancelflag)
{
    struct lbl_804333E0_t* streamPlayer = &Movieplayer;
    s32 tick_diff;
    s32 var_r0;
    s32 did_request;
    unsigned int var_r3;
    BOOL intr;

    LBMTHP_ASSERT(0x148, !cancelflag, lbl_803BADBC);

    tick_diff = OSGetTick() - streamPlayer->unk_13C;
    streamPlayer->unk_134 = tick_diff;
    streamPlayer->unk_130 = tick_diff >> 0x1F;
    streamPlayer->unk_108 += 1;
    if ((u32) streamPlayer->unk_74 != 0U) {
        streamPlayer->curr_file_offset += streamPlayer->currPackedSize;
    } else {
        streamPlayer->curr_file_offset = streamPlayer->unk_20;
    }
    if ((u32) streamPlayer->unk_8C == 0) {
        var_r0 = streamPlayer->unk_104 - 1;
    } else {
        var_r0 = streamPlayer->unk_8C - 1;
    }
    streamPlayer->currPackedSize = *(u32*) streamPlayer->frame_buffers[var_r0];
    if (((u32) streamPlayer->unk_90 != (u32) streamPlayer->unk_8C) &&
        ((s32) streamPlayer->unk_70 != 0))
    {
        intr = OSDisableInterrupts();
        streamPlayer->unk_13C = OSGetTick();
        streamPlayer->unk_138 = (did_request = 0);
        if (((u32) streamPlayer->unk_74 != (u32) streamPlayer->unk_40) ||
            (((u32) streamPlayer->unk_74 == (u32) streamPlayer->unk_40) &&
             did_request))
        {
            LBMTHP_ASSERTREPORT(0x121, (u32) streamPlayer->currPackedSize != 0,
                                lbl_803BADEC, lbl_803BADC8,
                                streamPlayer->file_entrynum,
                                streamPlayer->curr_file_offset);

            HSD_DevComRequest(
                streamPlayer->file_entrynum, streamPlayer->curr_file_offset,
                (uintptr_t) streamPlayer->frame_buffers[streamPlayer->unk_8C],
                (streamPlayer->currPackedSize + 0x1F) & 0xFFFFFFE0, 0x21, 1,
                fn_8001E910, NULL);
            streamPlayer->unk_74 += 1;
            if (((u32) streamPlayer->unk_74 == (u32) streamPlayer->unk_40) &&
                ((s32) streamPlayer->unk_68 != 0))
            {
                streamPlayer->unk_74 = 0U;
            }
            {
                var_r3 = streamPlayer->unk_8C + 1;
                if (var_r3 >= (u32) streamPlayer->unk_104) {
                    var_r3 = 0;
                }
                streamPlayer->unk_8C = var_r3;
            }
            streamPlayer->unk_110 = (did_request = 1);
        }
        if (did_request == 0) {
            streamPlayer->unk_110 = 0;
        }
        OSRestoreInterrupts(intr);
        return;
    }
    streamPlayer->unk_110 = 0;
}

s32 fn_8001EB14(THPDecComp* data, const char* path)
{
    THPInit();
    data->file_entrynum = DVDConvertPathToEntrynum(path);
    lbFile_800161C4(data->file_entrynum, 0, (u32) data, 0x40, 0x21, 1);

    data->unk_40 = data->num_frames;
    data->width = data->x_size;
    data->height = data->y_size;
    data->unk_100 = data->buf_size;

    if (data->frame_offsets != 0) {
        OSReport(str_Warning_frame_offsets_not_supported);
    }

    if (data->version > 2) {
        OSReport(lbl_803BAE3C);
    }

    data->unk_11C = 1;
    data->unk_6C = 1;
    data->unk_110 = 0;
    data->unk_70 = 1;
    data->unk_134 = 0;
    data->unk_130 = 0;

    return 1;
}

#define ALIGN_32(x) (((x) + 0x1F) & ~0x1F)

s32 fn_8001EBF0(THPDecComp* data)
{
    s32 size = 0;
    u32 unk_104_val;
    u32 aligned_100;
    u32 width;
    u32 height;
    u32 wh;
    u32 wh_div4;
    PAD_STACK(16);

    data->unk_104 = 0x20;

    width = data->width;
    aligned_100 = ALIGN_32(data->unk_100);
    height = data->height;
    unk_104_val = data->unk_104;

    data->unk_9C.val1 = (u16) width;

    wh = width * height;

    height = data->height;
    data->unk_9C._pad = (u16) height;

    size = aligned_100 * unk_104_val;

    data->unk_9C.val2 = 4;

    data->unk_9C.val0 = 0;

    size += wh;

    wh_div4 = wh >> 2;
    size += wh_div4;
    size += wh_div4;

    size += THPDec_8032FD40(&data->unk_9C, (u16) data->height);

    data->unk_7C = 0;
    data->unk_78 = 0;
    data->unk_84 = 0;
    data->unk_80 = 0;
    data->unk_90 = 0;
    data->unk_88 = 0;
    data->unk_94 = -1;
    data->unk_68 = 0;

    data->unk_A8 = (u16) data->width;
    data->unk_AA = (u16) data->height;
    data->unk_AC = 0;

    size += ALIGN_32(data->unk_104 * 4);
    size += ALIGN_32(data->unk_40 * 4);

    return size;
}

void fn_8001ECF4(THPDecComp* data, void* buf)
{
    u32 height;
    u32 width;
    u32 count;
    u8* var_r29;
    u32 y_size;
    u32 uv_size;
    u32 var_r25;
    u32 var_r24;
    u8* csizep;
    PAD_STACK(8);
    width = data->width;
    height = data->height;
    data->frame_buffers = (u32*) buf;
    y_size = width * height;
    count = data->unk_104;
    data->unk_64 = 0;
    uv_size = y_size >> 2U;
    var_r29 = (u8*) buf + (((count * 4) + 0x1F) & 0xFFFFFFE0);
    if (((s32) data->unk_6C != 0) && ((s32) data->unk_11C != 0)) {
        var_r24 = data->first_frame_size;
        csizep = (u8*) &data->first_frame_size;
        var_r25 = 0;
        data->curr_file_offset = data->first_frame;
        for (; var_r25 < (u32) data->unk_104; var_r25++) {
            data->frame_buffers[var_r25] = (u32) var_r29;
            if (var_r24 == 0) {
                OSReport(lbl_803BAE68);
                OSReport(lbl_803BAE80, var_r29);
                OSReport(lbl_803BAE8C, var_r24);
                OSReport(lbl_803BAE98, var_r25);
                OSReport(lbl_803BAEA4, csizep);
                OSReport(lbl_803BAEB0, data);
                OSReport(lbl_803BAEC8, data->version);
                OSReport(lbl_803BAEE0, data->buf_size);
                OSReport(lbl_803BAEF8, data->x_size);
                OSReport(lbl_803BAF10, data->y_size);
                OSReport(lbl_803BAF28, data->frame_rate);
                OSReport(lbl_803BAF44, data->num_frames);
                OSReport(lbl_803BAF60, data->first_frame);
                OSReport(lbl_803BAF7C, data->frame_offsets);
                OSReport(lbl_803BAF98, data->first_frame_size);
                __assert(file, 0x10A, str_0);
            }
            lbFile_800161C4(data->file_entrynum, data->curr_file_offset,
                            (u32) var_r29, (var_r24 + 0x1F) & 0xFFFFFFE0, 0x21,
                            1);
            csizep = var_r29;
            data->curr_file_offset += var_r24;
            var_r24 = *(u32*) var_r29;
            var_r29 = var_r29 + data->unk_100;
        }
        data->unk_74 = var_r25;
        data->currPackedSize = var_r24;
        if ((u32) data->unk_74 >= (u32) data->unk_40) {
            data->unk_74 = 0;
        }
        data->unk_8C = 0;
        {
            s32 temp = data->unk_104 - 1;
            data->unk_108 = temp;
            data->unk_10C = temp;
        }
    }
    data->unk_50 = var_r29;
    DCInvalidateRange(var_r29, y_size);
    var_r29 = var_r29 + y_size;
    data->unk_54 = var_r29;
    DCInvalidateRange(var_r29, uv_size);
    var_r29 = var_r29 + uv_size;
    data->unk_58 = var_r29;
    DCInvalidateRange(var_r29, uv_size);
    var_r29 = var_r29 + uv_size;
    data->unk_98 = (s32) var_r29;
}

s32 fn_8001EF5C(THPDecComp* data)
{
    s32 spC;
    BOOL intr;

    if ((u32) data->unk_94 != data->unk_90) {
        intr = OSDisableInterrupts();
        data->unk_98 = THPVideoDecode(
            &data->unk_A8, &spC, (void*) data->unk_98,
            (void*) (data->frame_buffers[data->unk_90] + 4), &data->unk_9C);
        OSRestoreInterrupts(intr);

        if (data->width == 0x280) {
            THPDec_80331340(data->unk_98, data->unk_50, data->unk_54,
                            data->unk_58);
            DCStoreRange(data->unk_50, data->width * data->height);
            DCStoreRange(data->unk_54, (data->width * data->height) >> 2);
            DCStoreRange(data->unk_58, (data->width * data->height) >> 2);
        } else {
            THPDec_803313D0(data->unk_98, data->unk_50, data->unk_54,
                            data->unk_58, data->width);
        }

        intr = OSDisableInterrupts();
        data->unk_94 = data->unk_90;
        OSRestoreInterrupts(intr);
        return fn_8001F13C(data);
    }

    return data->unk_94;
}

s32 fn_8001F06C(THPDecComp* data)
{
    BOOL intr;

    intr = OSDisableInterrupts();

    if (data->unk_108 > 0 || data->unk_6C == 0) {
        data->unk_78++;

        if (data->unk_78 == data->unk_40) {
            if (data->unk_68 != 0) {
                data->unk_78 = 0;
            } else {
                data->unk_78--;
                goto end;
            }
        }

        data->unk_88++;
        data->unk_108--;

        if (data->unk_88 >= data->unk_104) {
            data->unk_88 = 0;
        }
    }

    if (data->unk_108 < data->unk_10C) {
        data->unk_10C = data->unk_108;
    }

end:
    OSRestoreInterrupts(intr);
    return 1;
}

s32 fn_8001F13C(THPDecComp* streamPlayer)
{
    BOOL intr;

    intr = OSDisableInterrupts();
    if ((streamPlayer->unk_90 != streamPlayer->unk_8C) &&
        (streamPlayer->unk_110 == 0) && (streamPlayer->unk_70 != 0))
    {
        streamPlayer->unk_13C = OSGetTick();
        streamPlayer->unk_138 = 0;
        if (streamPlayer->unk_74 != streamPlayer->unk_40) {
            LBMTHP_ASSERTREPORT(0x121, (u32) streamPlayer->currPackedSize != 0,
                                lbl_803BADEC, lbl_803BADC8,
                                streamPlayer->file_entrynum,
                                streamPlayer->curr_file_offset);
            HSD_DevComRequest(
                streamPlayer->file_entrynum, streamPlayer->curr_file_offset,
                streamPlayer->frame_buffers[streamPlayer->unk_8C],
                ALIGN_32(streamPlayer->currPackedSize), 0x21, 1, fn_8001E910,
                NULL);
            streamPlayer->unk_74++;
            if ((streamPlayer->unk_74 == streamPlayer->unk_40) &&
                (streamPlayer->unk_68 != 0))
            {
                streamPlayer->unk_74 = 0;
            }
            {
                unsigned int next = streamPlayer->unk_8C + 1;
                if (next >= streamPlayer->unk_104) {
                    next = 0;
                }
                streamPlayer->unk_8C = next;
            }
            streamPlayer->unk_110 = 1;
        }
    }
    return OSRestoreInterrupts(intr);
}

s32 fn_8001F294(void);

static inline u32 lbMthp_GetFrame(u32** rate_table, u32 counter)
{
    u32* rate_ptr = *rate_table;
    u32 frame = 0;
    u32 count;
    u32 ticks;
    u32 total;

    if (rate_ptr != NULL) {
        for (;; rate_ptr += 2) {
            count = rate_ptr[0];
            ticks = rate_ptr[1];
            total = ticks * count;
            if (counter >= total) {
                frame += count;
                counter -= total;
                continue;
            } else {
                frame += counter / ticks;
                break;
            }
        }
    } else {
        frame = counter;
    }

    return frame;
}

s32 fn_8001F2A4(void)
{
    struct lbl_804333E0_t* streamPlayer;
    u32** rate_table;
    u32 frame;

    streamPlayer = &Movieplayer;
    rate_table = &streamPlayer->rate_table;

    frame = lbMthp_GetFrame(rate_table, streamPlayer->unk_80);

    if ((u32) streamPlayer->unk_78 == frame) {
        streamPlayer->unk_80 += 1;

        frame = lbMthp_GetFrame(rate_table, streamPlayer->unk_80);

        if ((u32) streamPlayer->unk_40 == frame) {
            if (streamPlayer->unk_68 != 0) {
                streamPlayer->unk_80 = 0;
            } else {
                streamPlayer->unk_80 -= 1;
                streamPlayer->unk_144 = 1;
            }
        }
    }

    frame = lbMthp_GetFrame(rate_table, streamPlayer->unk_80);

    if ((u32) streamPlayer->unk_78 != frame) {
        return fn_8001F06C((THPDecComp*) streamPlayer);
    }
    return (s32) streamPlayer;
}

void lbMthp_8001F410(const char* filename, void* rate_table, int buf,
                     int heap_size, int loop)
{
    s32 memoryRequired;
    struct lbl_804333E0_t* streamPlayer;
    s32* power;

    streamPlayer = &Movieplayer;
    power = &streamPlayer->power;
    LBMTHP_ASSERT(0x341, !streamPlayer->power, lbl_803BAFB8);

    *power = 1;
    fn_8001EB14((THPDecComp*) streamPlayer, filename);
    streamPlayer->rate_table = rate_table;
    memoryRequired = fn_8001EBF0((THPDecComp*) streamPlayer);
    if ((u32) buf != 0U) {
        LBMTHP_ASSERT(0x350, (u32) heap_size >= (u32) memoryRequired,
                      lbl_803BAFCC);
        streamPlayer->unk_140 = NULL;
    } else {
        buf = (int) HSD_MemAlloc(memoryRequired);
        streamPlayer->unk_140 = (void*) buf;
    }
    streamPlayer->unk_68 = loop;
    fn_8001ECF4((THPDecComp*) streamPlayer, (void*) buf);
    streamPlayer->unk_144 = 0;
    streamPlayer->unk_148 = 1;
    OSCreateAlarm(&streamPlayer->unk_150);
    OSSetPeriodicAlarm(
        &streamPlayer->unk_150,
        __cvt_dbl_usll((f64) (lbl_804D7CC8 * (f32) (*(u32*) 0x800000F8 >> 2))),
        __cvt_dbl_usll((f64) (lbl_804D7CC8 * (f32) (*(u32*) 0x800000F8 >> 2))),
        (OSAlarmHandler) (Event) fn_8001F2A4);
}

void lbMthp_8001F578(void)
{
    BOOL intr;
    PAD_STACK(8);
    intr = OSDisableInterrupts();
    Movieplayer.unk_90 = Movieplayer.unk_88;
    Movieplayer.unk_7C = Movieplayer.unk_78;
    Movieplayer.unk_84 = Movieplayer.unk_80;
    OSRestoreInterrupts(intr);
}

s32 lbMthp_8001F5C4(void)
{
    return Movieplayer.unk_84;
}

s32 lbMthp_8001F5D4(void)
{
    return Movieplayer.unk_134;
}

s32 lbMthp_8001F5E4(void)
{
    return Movieplayer.unk_108;
}

s32 lbMthp_8001F5F4(void)
{
    return Movieplayer.unk_10C;
}

s32 lbMthp_8001F604(void)
{
    return Movieplayer.unk_144;
}

void lbMthp_8001F614(s32 arg0)
{
    Movieplayer.unk_148 = arg0;
}

HSD_SObj* lbMthp_8001F624(HSD_GObj* gobj, int width, int height)
{
    HSD_SObj* sobj;
    lbl_803BAFE8.x0 = 0;
    lbl_803BAFE8.x4 = (u16) width;
    lbl_803BAFE8.x6 = (u16) height;
    sobj = HSD_SObjLib_803A477C(gobj, (int) &lbl_804D3834, 0, 0, 0x80, 0);
    sobj->x40 |= 0x10;
    return sobj;
}

void lbMthp_8001F67C(HSD_GObj* gobj, int arg1)
{
    struct lbl_804333E0_t* streamPlayer = &Movieplayer;
    PAD_STACK(8);

    fn_8001EF5C((THPDecComp*) streamPlayer);
    if ((s32) streamPlayer->unk_148 != 0) {
        GXInitTexObj(&streamPlayer->unk_178, streamPlayer->unk_50,
                     (u16) streamPlayer->unk_44, (u16) streamPlayer->unk_48,
                     GX_TF_I8, GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_178, GX_NEAR, GX_NEAR, lbl_804D7CD8,
                        lbl_804D7CD8, lbl_804D7CD8, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_178, GX_TEXMAP0);

        GXInitTexObj(&streamPlayer->unk_198, streamPlayer->unk_54,
                     (u16) ((u32) streamPlayer->unk_44 >> 1U),
                     (u16) ((u32) streamPlayer->unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_198, GX_NEAR, GX_NEAR, lbl_804D7CD8,
                        lbl_804D7CD8, lbl_804D7CD8, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_198, GX_TEXMAP1);

        GXInitTexObj(&streamPlayer->unk_1B8, streamPlayer->unk_58,
                     (u16) ((u32) streamPlayer->unk_44 >> 1U),
                     (u16) ((u32) streamPlayer->unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_1B8, GX_NEAR, GX_NEAR, lbl_804D7CD8,
                        lbl_804D7CD8, lbl_804D7CD8, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_1B8, GX_TEXMAP2);

        HSD_SObjLib_803A49E0(gobj, arg1);
    }
}

void lbMthp_8001F800(void)
{
    if (Movieplayer.power != 0) {
        Movieplayer.unk_70 = 0;

        while (fn_8001F294()) {
        }

        OSCancelAlarm(&Movieplayer.unk_150);
        HSD_VIWaitXFBFlush();

        if (Movieplayer.unk_140 != NULL) {
            HSD_Free(Movieplayer.unk_140);
        }

        Movieplayer.power = 0;
    }
}

s32 fn_8001F294(void)
{
    return Movieplayer.unk_110;
}

void lbMthp_8001F87C(void)
{
    Movieplayer.power = 0;
}
