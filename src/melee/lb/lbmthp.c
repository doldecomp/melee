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

void fn_8001E910(int arg0, int arg1, void* arg2, bool cancelflag)
{
    s32 tick_diff;
    s32 var_r0;
    s32 var_r4;
    u32 tick;
    BOOL intr;

    HSD_ASSERT(0x148, !cancelflag);

    tick_diff = OSGetTick() - Movieplayer.unk_13C;
    Movieplayer.unk_134 = tick_diff;
    Movieplayer.unk_130 = tick_diff >> 0x1F;
    Movieplayer.unk_108 += 1;
    if ((u32) Movieplayer.unk_74 != 0U) {
        Movieplayer.unk_120 += Movieplayer.currPackedSize;
    } else {
        Movieplayer.unk_120 = Movieplayer.unk_20;
    }
    if ((u32) Movieplayer.unk_8C == 0) {
        var_r0 = Movieplayer.unk_104 - 1;
    } else {
        var_r0 = Movieplayer.unk_8C - 1;
    }
    Movieplayer.currPackedSize = *(u32*) Movieplayer.unk_4C[var_r0];
    if (((u32) Movieplayer.unk_90 != (u32) Movieplayer.unk_8C) &&
        ((s32) Movieplayer.unk_70 != 0))
    {
        intr = OSDisableInterrupts();
        tick = OSGetTick();
        Movieplayer.unk_13C = tick;
        var_r4 = 0;
        Movieplayer.unk_138 = 0;
        if ((u32) Movieplayer.unk_74 != (u32) Movieplayer.unk_40) {
            struct lbl_804333E0_t* streamPlayer = &Movieplayer;
            HSD_ASSERTREPORT(0x121, (u32) streamPlayer->currPackedSize != 0,
                             "filnum = %d, ofs = %d, by sugano.",
                             Movieplayer.unk_128, Movieplayer.unk_120);

            HSD_DevComRequest(
                Movieplayer.unk_128, Movieplayer.unk_120,
                (uintptr_t) Movieplayer.unk_4C[Movieplayer.unk_8C],
                (Movieplayer.currPackedSize + 0x1F) & 0xFFFFFFE0, 0x21, 1,
                fn_8001E910, NULL);
            Movieplayer.unk_74 += 1;
            if (((u32) Movieplayer.unk_74 == (u32) Movieplayer.unk_40) &&
                ((s32) Movieplayer.unk_68 != 0))
            {
                Movieplayer.unk_74 = 0U;
            }
            {
                u32 var_r3 = Movieplayer.unk_8C + 1;
                if (var_r3 >= (u32) Movieplayer.unk_104) {
                    var_r3 = 0;
                }
                Movieplayer.unk_8C = var_r3;
            }
            var_r4 = 1;
            Movieplayer.unk_110 = 1;
        }
        if (var_r4 == 0) {
            Movieplayer.unk_110 = 0;
        }
        OSRestoreInterrupts(intr);
        return;
    }
    Movieplayer.unk_110 = 0;
}

s32 fn_8001EB14(THPDecComp* data, const char* path)
{
    THPInit();
    data->unk_128 = DVDConvertPathToEntrynum(path);
    lbFile_800161C4(data->unk_128, 0, (u32) data, 0x40, 0x21, 1);

    data->unk_40 = data->unk_1C;
    data->width = data->unk_10;
    data->height = data->unk_14;
    data->unk_100 = data->unk_0C;

    if (data->unk_24 != 0) {
        OSReport("Warning : frame offsets not supported\n");
    }

    if (data->unk_08 > 2) {
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

s32 fn_8001EBF0(THPDecComp* data)
{
    s32 size = 0;
    u32 width;
    u32 aligned_100;
    u32 height;
    u32 unk_104_val;
    u32 wh;
    u32 wh_div4;
    PAD_STACK(16);

    data->unk_104 = 0x20;

    /* Load width first */
    width = data->width;
    /* Load unk_100 */
    aligned_100 = data->unk_100;
    /* Load height */
    height = data->height;
    /* Load unk_104 */
    unk_104_val = data->unk_104;

    /* Align unk_100 */
    aligned_100 = ALIGN_32(aligned_100);

    /* Store width */
    data->unk_A0 = (u16) width;

    /* Multiply width * height */
    wh = width * height;

    /* Reload and store height */
    height = data->height;
    data->unk_A2 = (u16) height;

    /* size = aligned * unk_104 */
    size = aligned_100 * unk_104_val;

    /* Store 4 to unk_A4 */
    data->unk_A4 = 4;

    /* Zero unk_9C */
    data->unk_9C = 0;

    /* size += wh */
    size += wh;

    /* size += wh/4 twice */
    wh_div4 = wh >> 2;
    size += wh_div4;
    size += wh_div4;

    /* Call THPDec_8032FD40 with &unk_9C and height as u16 */
    size += THPDec_8032FD40(&data->unk_9C, (u16) data->height);

    /* Zero various fields */
    data->unk_7C = 0;
    data->unk_78 = 0;
    data->unk_84 = 0;
    data->unk_80 = 0;
    data->unk_90 = 0;
    data->unk_88 = 0;
    data->unk_94 = -1;
    data->unk_68 = 0;

    /* Copy width/height again */
    data->unk_A8 = (u16) data->width;
    data->unk_AA = (u16) data->height;
    data->unk_AC = 0;

    /* Add aligned sizes */
    size += ALIGN_32(data->unk_104 * 4);
    size += ALIGN_32(data->unk_40 * 4);

    return size;
}

void fn_8001ECF4(THPDecComp* data, void* buf)
{
    u32 y_size;
    u32 uv_size;
    u32 var_r24;
    u32 var_r25;
    u8* csizep;
    u8* var_r29;
    PAD_STACK(8);

    data->unk_4C = (u32*) buf;
    y_size = data->width * data->height;
    data->unk_64 = 0;
    uv_size = y_size >> 2U;
    var_r29 = (u8*) buf + (((data->unk_104 * 4) + 0x1F) & 0xFFFFFFE0);
    if (((s32) data->unk_6C != 0) && ((s32) data->unk_11C != 0)) {
        var_r24 = data->unk_28;
        csizep = (u8*) &data->unk_28;
        var_r25 = 0;
        data->unk_120 = data->unk_20;
        for (; var_r25 < (u32) data->unk_104; var_r25++) {
            data->unk_4C[var_r25] = (u32) var_r29;
            if (var_r24 == 0) {
                OSReport("by sugano & yoshiki.\n");
                OSReport("base %x\n", var_r29);
                OSReport("size %d\n", var_r24);
                OSReport("count %d\n", var_r25);
                OSReport("csizep %x\n", csizep);
                OSReport("[LbMthp] magic = %s\n", data);
                OSReport("[LbMthp] version = %d\n", data->unk_08);
                OSReport("[LbMthp] bufSize = %d\n", data->unk_0C);
                OSReport("[LbMthp] xSize = %d\n", data->unk_10);
                OSReport("[LbMthp] ySize = %d\n", data->unk_14);
                OSReport("[LbMthp] framerate = %d\n", data->unk_18);
                OSReport("[LbMthp] numFrames = %d\n", data->unk_1C);
                OSReport("[LbMthp] firstFrame = %d\n", data->unk_20);
                OSReport("[LbMthp] frameOffsets = %d\n", data->unk_24);
                OSReport("[LbMthp] firstFrameSize = %d\n", data->unk_28);
                HSD_ASSERT(0x10A, NULL);
            }
            lbFile_800161C4(data->unk_128, data->unk_120, (u32) var_r29,
                            (var_r24 + 0x1F) & 0xFFFFFFE0, 0x21, 1);
            csizep = var_r29;
            data->unk_120 += var_r24;
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
    data->unk_98 = (s32) (var_r29 + uv_size);
}

s32 fn_8001EF5C(THPDecComp* data)
{
    s32 spC;
    BOOL intr;

    if ((u32) data->unk_94 != data->unk_90) {
        intr = OSDisableInterrupts();
        data->unk_98 =
            THPVideoDecode(&data->unk_A8, &spC, (void*) data->unk_98,
                           data->unk_4C[data->unk_90] + 4, &data->unk_9C);
        OSRestoreInterrupts(intr);

        if (data->width == 0x280) {
            THPDec_80331340(data->unk_98, data->unk_50, data->unk_54,
                            data->unk_58, data->width);
            DCStoreRange(data->unk_50, data->width * data->height);
            DCStoreRange(data->unk_54, (data->width * data->height) >> 2);
            DCStoreRange(data->unk_58, (data->width * data->height) >> 2);
        } else {
            THPDec_803313D0(data->unk_98, data->unk_50, data->unk_54,
                            data->unk_58);
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
            HSD_ASSERTREPORT(0x121, (u32) streamPlayer->currPackedSize != 0,
                             "filnum = %d, ofs = %d, by sugano.",
                             streamPlayer->unk_128, streamPlayer->unk_120);
            HSD_DevComRequest(streamPlayer->unk_128, streamPlayer->unk_120,
                              streamPlayer->unk_4C[streamPlayer->unk_8C],
                              ALIGN_32(streamPlayer->currPackedSize), 0x21, 1,
                              fn_8001E910, NULL);
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

s32 fn_8001F2A4(void)
{
    s32 frame;
    s32* rate_ptr;
    s32 counter;
    s32 count, ticks, total;

    /* Convert unk_80 ticks to frame number using rate table */
    frame = 0;
    rate_ptr = (s32*) Movieplayer.unk_12C;
    counter = Movieplayer.unk_80;
    if ((u32) rate_ptr != 0U) {
        for (;; rate_ptr += 2) {
            count = rate_ptr[0];
            ticks = rate_ptr[1];
            total = count * ticks;
            if ((u32) counter >= (u32) total) {
                frame += count;
                counter -= total;
                continue;
            }
            frame += (u32) counter / (u32) ticks;
            break;
        }
    } else {
        frame = counter;
    }

    if ((u32) Movieplayer.unk_78 == (u32) frame) {
        Movieplayer.unk_80 += 1;

        /* Recompute frame after increment */
        frame = 0;
        rate_ptr = (s32*) Movieplayer.unk_12C;
        counter = Movieplayer.unk_80;
        if ((u32) rate_ptr != 0U) {
            for (;; rate_ptr += 2) {
                count = rate_ptr[0];
                ticks = rate_ptr[1];
                total = count * ticks;
                if ((u32) counter >= (u32) total) {
                    frame += count;
                    counter -= total;
                    continue;
                }
                frame += (u32) counter / (u32) ticks;
                break;
            }
        } else {
            frame = counter;
        }

        if ((u32) Movieplayer.unk_40 == (u32) frame) {
            if (Movieplayer.unk_68 != 0) {
                Movieplayer.unk_80 = 0;
            } else {
                Movieplayer.unk_80 -= 1;
                Movieplayer.unk_144 = 1;
            }
        }
    }

    /* Final conversion for frame change check */
    rate_ptr = (s32*) Movieplayer.unk_12C;
    frame = 0;
    counter = Movieplayer.unk_80;
    if ((u32) rate_ptr != 0U) {
        for (;; rate_ptr += 2) {
            count = rate_ptr[0];
            ticks = rate_ptr[1];
            total = count * ticks;
            if ((u32) counter >= (u32) total) {
                frame += count;
                counter -= total;
                continue;
            }
            frame += (u32) counter / (u32) ticks;
            break;
        }
    } else {
        frame = counter;
    }

    if ((u32) Movieplayer.unk_78 != (u32) frame) {
        return fn_8001F06C((THPDecComp*) &Movieplayer);
    }
    return (s32) &Movieplayer;
}

void lbMthp_8001F410(const char* filename, void* rate_table, int buf_arg,
                     int heap_size, int loop)
{
    s32 memoryRequired;
    void* buf = (void*) buf_arg;

    HSD_ASSERT(0x341, !Movieplayer.power);

    Movieplayer.power = 1;
    fn_8001EB14((THPDecComp*) &Movieplayer, filename);
    Movieplayer.unk_12C = (s32) rate_table;
    memoryRequired = fn_8001EBF0((THPDecComp*) &Movieplayer);
    if (buf != NULL) {
        HSD_ASSERT(0x350, heap_size >= memoryRequired);
        Movieplayer.unk_140 = NULL;
    } else {
        buf = HSD_MemAlloc(memoryRequired);
        Movieplayer.unk_140 = buf;
    }
    Movieplayer.unk_68 = loop;
    fn_8001ECF4((THPDecComp*) &Movieplayer, buf);
    Movieplayer.unk_144 = 0;
    Movieplayer.unk_148 = 1;
    OSCreateAlarm(&Movieplayer.unk_150);
    OSSetPeriodicAlarm(
        &Movieplayer.unk_150,
        __cvt_dbl_usll((f64) (0.016666668f * (f32) (*(u32*) 0x800000F8 >> 2))),
        __cvt_dbl_usll((f64) (0.016666668f * (f32) (*(u32*) 0x800000F8 >> 2))),
        (OSAlarmHandler) fn_8001F2A4);
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
    fn_8001EF5C((THPDecComp*) &Movieplayer);
    if ((s32) Movieplayer.unk_148 != 0) {
        GXInitTexObj(&Movieplayer.unk_178, Movieplayer.unk_50,
                     (u16) Movieplayer.unk_44, (u16) Movieplayer.unk_48,
                     GX_TF_I8, GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&Movieplayer.unk_178, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&Movieplayer.unk_178, GX_TEXMAP0);

        GXInitTexObj(&Movieplayer.unk_198, Movieplayer.unk_54,
                     (u16) ((u32) Movieplayer.unk_44 >> 1U),
                     (u16) ((u32) Movieplayer.unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&Movieplayer.unk_198, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&Movieplayer.unk_198, GX_TEXMAP1);

        GXInitTexObj(&Movieplayer.unk_1B8, Movieplayer.unk_58,
                     (u16) ((u32) Movieplayer.unk_44 >> 1U),
                     (u16) ((u32) Movieplayer.unk_48 >> 1U), GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, 0U);
        GXInitTexObjLOD(&Movieplayer.unk_1B8, GX_NEAR, GX_NEAR, 0.0f, 0.0f,
                        0.0f, 0U, 0U, GX_ANISO_1);
        GXLoadTexObj(&Movieplayer.unk_1B8, GX_TEXMAP2);

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
