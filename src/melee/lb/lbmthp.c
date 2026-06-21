#include "lbmthp.h"

#include "lbmthp.static.h"

#include "baselib/forward.h"

#include "baselib/memory.h"
#include "baselib/tobj.h"
#include "baselib/video.h"
#include "dolphin/os.h"
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

struct lbl_803BAFE8_t {
    /* 0x00 */ s32 x0;
    /* 0x04 */ u16 x4;
    /* 0x06 */ u16 x6;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 xC;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
}; /* size = 0x18 */

/* 4333E0 */ static struct lbl_804333E0_t MoviePlayer;

void fn_8001E910(int arg0, int arg1, void* arg2, int cancelflag)
{
    struct lbl_804333E0_t* streamPlayer = &MoviePlayer;
    s32 tick_diff;
    s32 var_r0;
    s32 did_request;
    unsigned int var_r3;
    BOOL intr;

    HSD_ASSERT(328, !cancelflag);

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
            HSD_ASSERTREPORT(289, (u32)streamPlayer->currPackedSize != 0,
                             "filnum = %d, ofs = %d, by sugano.",
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
        OSReport("Warning : frame offsets not supported\n");
    }

    if (data->version > 2) {
        OSReport("Warning : file format is newer than player\n");
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

/// @returns memory required
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
                OSReport("by sugano & yoshiki.\n");
                OSReport("base %x\n", var_r29);
                OSReport("size %d\n", var_r24);
                OSReport("count %d\n", var_r25);
                OSReport("csizep %x\n", csizep);
                OSReport("[LbMthp] magic = %s\n", data);
                OSReport("[LbMthp] version = %d\n", data->version);
                OSReport("[LbMthp] bufSize = %d\n", data->buf_size);
                OSReport("[LbMthp] xSize = %d\n", data->x_size);
                OSReport("[LbMthp] ySize = %d\n", data->y_size);
                OSReport("[LbMthp] framerate = %d\n", data->frame_rate);
                OSReport("[LbMthp] numFrames = %d\n", data->num_frames);
                OSReport("[LbMthp] firstFrame = %d\n", data->first_frame);
                OSReport("[LbMthp] frameOffsets = %d\n", data->frame_offsets);
                OSReport("[LbMthp] firstFrameSize = %d\n",
                         data->first_frame_size);
                HSD_ASSERT(266, 0);
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
            HSD_ASSERTREPORT(289, (u32)streamPlayer->currPackedSize != 0,
                             "filnum = %d, ofs = %d, by sugano.",
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

void fn_8001F2A4(OSAlarm* alarm, OSContext* context)
{
    struct lbl_804333E0_t* streamPlayer;
    u32** rate_table;
    u32 frame;

    streamPlayer = &MoviePlayer;
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
        fn_8001F06C((THPDecComp*) streamPlayer);
    }
}

void lbMthp_8001F410(const char* filename, void* rate_table, int buf,
                     int heap_size, int loop)
{
    s32 memoryRequired;

    HSD_ASSERT(833, !MoviePlayer.power);
    MoviePlayer.power = 1;
    fn_8001EB14((THPDecComp*) &MoviePlayer, filename);
    MoviePlayer.rate_table = rate_table;
    memoryRequired = fn_8001EBF0((THPDecComp*) &MoviePlayer);
    if ((u32) buf != 0U) {
        HSD_ASSERT(848, heap_size >= memoryRequired);
        MoviePlayer.unk_140 = NULL;
    } else {
        buf = (int) HSD_MemAlloc(memoryRequired);
        MoviePlayer.unk_140 = (void*) buf;
    }
    MoviePlayer.unk_68 = loop;
    fn_8001ECF4((THPDecComp*) &MoviePlayer, (void*) buf);
    MoviePlayer.unk_144 = 0;
    MoviePlayer.unk_148 = 1;
    OSCreateAlarm(&MoviePlayer.alarm);
    OSSetPeriodicAlarm(
        &MoviePlayer.alarm, __cvt_dbl_usll(OSSecondsToTicks(1.0f / 60)),
        __cvt_dbl_usll(OSSecondsToTicks(1.0f / 60)), fn_8001F2A4);
}

void lbMthp_8001F578(void)
{
    BOOL intr;
    PAD_STACK(8);
    intr = OSDisableInterrupts();
    MoviePlayer.unk_90 = MoviePlayer.unk_88;
    MoviePlayer.unk_7C = MoviePlayer.unk_78;
    MoviePlayer.unk_84 = MoviePlayer.unk_80;
    OSRestoreInterrupts(intr);
}

s32 lbMthp_8001F5C4(void)
{
    return MoviePlayer.unk_84;
}

s32 lbMthp_8001F5D4(void)
{
    return MoviePlayer.unk_134;
}

s32 lbMthp_8001F5E4(void)
{
    return MoviePlayer.unk_108;
}

s32 lbMthp_8001F5F4(void)
{
    return MoviePlayer.unk_10C;
}

s32 lbMthp_8001F604(void)
{
    return MoviePlayer.unk_144;
}

void lbMthp_8001F614(s32 arg0)
{
    MoviePlayer.unk_148 = arg0;
}

/* 3BAFE8 */ static HSD_ImageDesc lbl_803BAFE8 = {
    0, 0x280, 0x1E0, 6, 0, 0, 0,
};
/* 4D3834 */ HSD_SObjDesc lbl_804D3834 = { &lbl_803BAFE8 };

HSD_SObj* lbMthp_8001F624(HSD_GObj* gobj, int width, int height)
{
    HSD_SObj* sobj;
    lbl_803BAFE8.image_ptr = NULL;
    lbl_803BAFE8.width = width;
    lbl_803BAFE8.height = height;
    sobj = HSD_SObjLib_803A477C(gobj, &lbl_804D3834, 0, 0, 0x80, 0);
    sobj->x40 |= 0x10;
    return sobj;
}

void lbMthp_8001F67C(HSD_GObj* gobj, int arg1)
{
    struct lbl_804333E0_t* streamPlayer = &MoviePlayer;
    PAD_STACK(8);

    fn_8001EF5C((THPDecComp*) streamPlayer);
    if ((s32) streamPlayer->unk_148 != 0) {
        GXInitTexObj(&streamPlayer->unk_178, streamPlayer->unk_50,
                     (u16) streamPlayer->unk_44, (u16) streamPlayer->unk_48,
                     GX_TF_I8, GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_178, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_178, GX_TEXMAP0);

        GXInitTexObj(&streamPlayer->unk_198, streamPlayer->unk_54,
                     (u16) ((u32) streamPlayer->unk_44 >> 1U),
                     (u16) ((u32) streamPlayer->unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_198, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_198, GX_TEXMAP1);

        GXInitTexObj(&streamPlayer->unk_1B8, streamPlayer->unk_58,
                     (u16) ((u32) streamPlayer->unk_44 >> 1U),
                     (u16) ((u32) streamPlayer->unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&streamPlayer->unk_1B8, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&streamPlayer->unk_1B8, GX_TEXMAP2);

        HSD_SObjLib_803A49E0(gobj, arg1);
    }
}

void lbMthp_8001F800(void)
{
    if (MoviePlayer.power != 0) {
        MoviePlayer.unk_70 = 0;

        while (fn_8001F294()) {
        }

        OSCancelAlarm(&MoviePlayer.alarm);
        HSD_VIWaitXFBFlush();

        if (MoviePlayer.unk_140 != NULL) {
            HSD_Free(MoviePlayer.unk_140);
        }

        MoviePlayer.power = 0;
    }
}

s32 fn_8001F294(void)
{
    return MoviePlayer.unk_110;
}

void lbMthp_8001F87C(void)
{
    MoviePlayer.power = 0;
}
