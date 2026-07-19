#include "hsd_3933.h"

#include <dolphin/mcc.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/hsd_3915.h>
#include <sysdolphin/baselib/hsd_392C.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/video.h>

typedef struct {
    s32 x0;
    u32 x4;
    s32 x8;
} ParticleLogEntry;

/// Host-IO USB file transfer messages, kept in one table (retail data object
/// at 0x8040A9D0, size 0x130): the code addresses individual messages as
/// field offsets from the table base (e.g. +0x20/+0x90/+0xB8 in
/// #hsd_80393A5C), which independent string literals cannot produce.
struct ParticleUsbMessages {
    /* 0x00 */ char loading[0x20];
    /* 0x20 */ char cannot_open[0x14];
    /* 0x34 */ char cannot_get_files_stat[0x18];
    /* 0x4C */ char file_too_large[0x18];
    /* 0x64 */ char cannot_allocate[0x18];
    /* 0x7C */ char cannot_load[0x14];
    /* 0x90 */ char done[0x28];
    /* 0xB8 */ char cannot_save[0x14];
    /* 0xCC */ char searching[0x20];
    /* 0xEC */ char cannot_get_dir_stat[0x18];
    /* 0x104 */ char dir_too_large[0x14];
    /* 0x118 */ char cannot_use_usb[0x18];
};
STATIC_ASSERT(sizeof(struct ParticleUsbMessages) == 0x130);

struct ParticleConsoleState {
    /* 00 */ u8 x0_b0 : 1;
    /* 00 */ u8 x0_b1 : 1;
    /* 04 */ u8* out_buf;
    /* 08 */ u32 buf_size;
    /* 0C */ int xC;
    /* 10 */ u8 x10;
    /* 11 */ u8 x11;
    /* 12 */ u8 x12;
    /* 13 */ u8 x13;
    /* 14 */ int x14;
    /* 18 */ int x18;
    /* 1C */ int x1C;
    /* 20 */ int x20;
    /* 20 */ UNK_T x24;
};
STATIC_ASSERT(sizeof(struct ParticleConsoleState) == 0x28);

/* 4D78B0 */ static s32 hsd_804D78B0;
/* 4D78B4 */ static s32 hsd_804D78B4;
/* 4D78B8 */ static s32 hsd_804D78B8;
/* 4D78BC */ static s32 hsd_804D78BC;
/* 4D78C0 */ static int hsd_804D78C0;
/* 4D78C8 */ static int hsd_804D78C8;
/* 4D78CC */ static u32 hsd_804D78CC;

/* 4CF7E8 */ static struct ParticleConsoleState hsd_804CF7E8;

/* 4CF810 */ extern struct ParticleScreenState hsd_804CF810;

ParticleLogEntry hsd_804CEB40[0x100];

void fn_803932D0(s32 type, u32 flags, s32 value)
{
    s32 count = hsd_804D78BC;
    ParticleLogEntry* base = hsd_804CEB40;
    s32 idx;
    ParticleLogEntry* entry;

    if (count <= 0x100 && flags == 0x100U) {
        idx = (hsd_804D78B8 + count) % 256;
        *(s32*) ((u8*) base + idx * (s32) sizeof(ParticleLogEntry)) = type;
        entry = &base[idx];
        entry->x4 = flags;
        entry->x8 = value;
        hsd_804D78BC += 1;
    }
}

s32 hsd_80393328(void)
{
    u32 ticksPerUnit;
    s32 startTick;
    s32 result;
    u8 err;

    if (hsd_804D78B4 != 0) {
        return 0;
    }
    hsd_804D78B4 = 1;
    hsd_804D78B0 = HSD_Rand() % 255;
    if (MCCNotify(0xF, hsd_804D78B0 + 256) == 0) {
        err = MCCGetLastError();
        OSReport("Error(0x%x) in MCCNotify.\n", err);
    }
    result = 1;
    startTick = OSGetTick();
    ticksPerUnit = (*(u32*) 0x800000F8 >> 2) & 0xFFFFFFFFFFFFFFFF;
    do {
        hsd_80392E80();
        if (hsd_804D78B0 == 0) {
            result = 0;
            break;
        }
    } while ((u32) (OSGetTick() - startTick) / ticksPerUnit < 3);

    if (result != 0) {
        hsd_804D78B4 = 0;
        return 0;
    }
    hsd_804D78B4 = 0;
    return 1;
}

static void (*lbl_8040A93C[32])(void*, void*) = {
    (void (*)(void*, void*)) hsd_80393440,
    (void (*)(void*, void*)) hsd_80393840,
};

// Evidence: retail hsd_80393A5C loads this table's base into a register
// (lis/addi 0x8040A9D0) and reads the messages at field displacements
// +0x20 ("cannot open"), +0x90 ("Done"), +0xB8 ("cannot save"); the
// remaining messages fill out the retail 0x130 object (see
// struct ParticleUsbMessages in particle.static.h).
/* 40A9D0 */ static struct ParticleUsbMessages psUsbMessages = {
    "loading file (%s) from USB ...",
    "cannot open file\n",
    "cannot get files stat\n",
    "too large file size\n",
    "cannot allocate memory\n",
    "cannot load file\n",
    "Done %s size:%d time:%f spped:%fkbps\n",
    "cannot save file\n",
    "Seaching files (%s) via USB ...",
    "cannot get dir stat\n",
    "too large dir size\n",
    "cannot use USB now.\n",
};

extern int hsd_804D78A0;
extern s32 hsd_804D78A8;
extern s32 hsd_804D78AC;

// @TODO: Currently 90.11% match - needs register allocation fix
void hsd_80393440(void* request, void* response)
{
    u16 cmd;
    s32 channel_mask;
    s32 streaming;
    s32 num_blocks;
    s32 channel;
    s32 i;
    u8 free_blocks;
    u8 err;
    ParticleLogEntry* base;

    cmd = ((u16*) request)[3];
    channel_mask = cmd & 0xFF00;
    base = hsd_804CEB40;

    switch (channel_mask) {
    case 0x100:
        if (cmd & 0x80) {
            streaming = 1;
        } else {
            streaming = 0;
        }
        num_blocks = cmd & 0xF;
        for (channel = 2; channel < 16; channel++) {
            if (((s32*) &base[0x100])[channel] == 0) {
                break;
            }
        }

        if (channel == 16) {
            ((u16*) response)[3] = (u16) 0x8001;
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }

        free_blocks = MCCGetFreeBlocks(1);
        if (free_blocks == 0) {
            err = MCCGetLastError();
            if (err != 0) {
                OSReport("MCCError: %d\n", err);
            }
        }

        if (num_blocks > (s32) free_blocks) {
            ((u16*) response)[3] = (u16) (free_blocks + 0x8010);
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }

        ((s32*) &base[0x100])[channel] = 1;
        ((u16*) response)[3] = channel;
        MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
        if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
            err = MCCGetLastError();
            OSReport("Error(0x%x) in MCCNotify.\n", err);
        }
        hsd_804D78AC = (hsd_804D78AC + 1) % 128;
        if (streaming != 0) {
            MCCStreamOpen(channel, num_blocks);
        } else {
            MCCOpen(channel, num_blocks, 0);
        }
        return;

    case 0x200:
        i = cmd & 0xF;
        if (((s32*) &base[0x100])[i] != 1) {
            ((u16*) response)[3] = (u16) 0x8002;
            MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
            if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
            hsd_804D78AC = (hsd_804D78AC + 1) % 128;
            return;
        }
        ((u16*) response)[3] = 0;
        MCCWrite(0xF, (hsd_804D78AC << 5) + 0x1000, response, 0x20, 0);
        if (MCCNotify(0xF, hsd_804D78AC + 0x80) == 0) {
            err = MCCGetLastError();
            OSReport("Error(0x%x) in MCCNotify.\n", err);
        }
        hsd_804D78AC = (hsd_804D78AC + 1) % 128;
        ((s32*) &base[0x100])[i] = 0;
        MCCClose(i);
        return;
    }
}

void hsd_80393840(void) {}

typedef struct _MCCPacket {
    /* 0x0 */ s32 x0;
    /* 0x4 */ u8 x4_b7 : 1;
    /* 0x4 */ u8 _x4_pad : 7;
    /* 0x5 */ u8 x5;
} MCCPacket;

void hsd_80393844(void)
{
    ParticleLogEntry* base = hsd_804CEB40;
    s32 type;
    u32 flags;
    s32 value;
    BOOL irq;
    u8 err;

    for (;;) {
        irq = OSDisableInterrupts();
        if (hsd_804D78BC == 0) {
            OSRestoreInterrupts(irq);
            return;
        }

        type = base[hsd_804D78B8].x0;
        flags = base[hsd_804D78B8].x4;
        value = base[hsd_804D78B8].x8;
        hsd_804D78BC -= 1;
        hsd_804D78B8 = (hsd_804D78B8 + 1) % 256;

        OSRestoreInterrupts(irq);

        if (flags != 0x100 || type != 0xF) {
            continue;
        }

        if ((value & 0xFFFFFF00) == 0x100) {
            if (MCCNotify(0xF, (u8) value | 0x200) == 0) {
                err = MCCGetLastError();
                OSReport("Error(0x%x) in MCCNotify.\n", err);
            }
        } else if ((value & 0xFFFFFF00) == 0x200) {
            if ((u32) hsd_804D78B0 == (u8) value) {
                hsd_804D78B0 = 0;
            }
        } else if ((value & 0xFFFFFF80) == 0x80) {
            memset((u8*) &base[0x10A].x8, 0, 0x20);
            hsd_804D78A8 = value & 0x7F;
            if (MCCRead(0xF, hsd_804D78A8 << 5, (u8*) &base[0x10A].x8, 0x20,
                        0) != 0 &&
                !((MCCPacket*) &base[0x10A].x8)->x4_b7)
            {
                u8 cmd;
                memset((u8*) &base[0x105].x4, 0, 0x20);
                ((MCCPacket*) &base[0x105].x4)->x4_b7 = 1;
                *(s32*) &base[0x105].x4 = *(s32*) &base[0x10A].x8;
                cmd = ((u8*) &base[0x10A].x8)[5];
                if (((u8*) &base[0x105].x4)[5] = cmd, cmd < 0x20U) {
                    if (lbl_8040A93C[cmd] != NULL) {
                        lbl_8040A93C[cmd]((u8*) &base[0x10A].x8,
                                          (u8*) &base[0x105].x4);
                    }
                }
            }
        }
    }
}

bool hsd_80393A04(void)
{
    if (hsd_804D78A0 == 0) {
        return 0;
    }
    if (FIOQuery() == 0) {
        hsd_804D78A0 = 0;
        return 0;
    }
    return 1;
}

void hsd_80393A54(int level)
{
    hsd_804D78C0 = level;
}

static inline f32 kbps_scale(void)
{
    return 1.0F / 1024.0F;
}

int hsd_80393A5C(char* filename, int data, int size)
{
    int ready;
    u32 start;
    int fd;
    // Evidence: retail materializes the fd argument (mr r3) before the
    // buffer argument (mr r4) at the FIOFwrite call; the fresh local copy
    // reproduces that argument scheduling.
    int fd_arg;
    f32 written_f;
    f32 elapsed;
    u32* data_p;
    struct ParticleUsbMessages* messages = &psUsbMessages;

    if (hsd_804D78A0 == 0) {
        ready = 0;
    } else if (FIOQuery() == 0) {
        hsd_804D78A0 = ready = 0;
    } else {
        ready = 1;
    }

    if (ready == 0) {
        return -5;
    }

    if (*filename == '/') {
        filename++;
    }

    start = OSGetTick();
    fd = FIOFopen(filename, 0xA02);

    if ((u32) (fd + 0x10000) == 0xFFFF) {
        OSReport(messages->cannot_open);
        return -1;
    }

    fd_arg = fd;
    data_p = (u32*) data;
    written_f = (f32) (u32) FIOFwrite(fd_arg, data_p, size);

    if ((f32) (s32) size != written_f) {
        OSReport(messages->cannot_save);
        FIOFclose(fd);
        return (s32) written_f;
    }

    FIOFclose(fd);
    elapsed = (f32) (OSGetTick() - start) / (f32) (*(u32*) 0x800000F8 >> 2);
    {
        f32 bits = 8.0F * (f32) size;
        OSReport(messages->done, filename, size, elapsed,
                 bits / elapsed * kbps_scale());
    }
    return size;
}

void fn_80393C14(const u8* buf, size_t size)
{
    int i;

    const u32 out_size = hsd_804CF7E8.buf_size;

    int write_pos = hsd_804CF7E8.xC;
    u8* out_buf = hsd_804CF7E8.out_buf;
    u8 line_len = hsd_804CF7E8.x11;

    for (i = 0; i < size; i++) {
        const u32 tmp = out_size - 1;
        switch (buf[i]) {
        case '\r':
            break;
        case '\n':
            if (line_len != 0 || out_buf[(write_pos + tmp) % out_size] != '\0')
            {
                out_buf[write_pos] = line_len;
                write_pos = (write_pos + 1) % out_size;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                line_len = 0;
            }
            break;
        default:
            out_buf[write_pos] = buf[i];
            if (++line_len == 0x36) {
                write_pos = (write_pos + 1) % out_size;
                out_buf[write_pos] = line_len;
                hsd_804CF7E8.x1C++;
                hsd_804CF7E8.x18++;
                line_len = 0;
            }
            write_pos = (write_pos + 1) % out_size;
            hsd_804CF7E8.x1C++;
            break;
        }
    }
    hsd_804CF7E8.xC = write_pos;
    hsd_804CF7E8.x11 = line_len;
}

#pragma push
#pragma dont_inline on
s32 hsd_80393D2C(s32 enable)
{
    struct ParticleConsoleState* sp = &hsd_804CF7E8;
    s32 old = sp->x0_b1;

    if (enable != 0) {
        sp->x0_b1 = 1;
        HSD_SetReportCallback(fn_80393C14);
    } else {
        sp->x0_b1 = 0;
        HSD_SetReportCallback(NULL);
    }
    return old;
}
#pragma pop

#pragma push
#pragma pool_data off
void hsd_80393DA0(u8* buf, size_t size)
{
    PAD_STACK(4);
    memset(&hsd_804CF7E8, 0, sizeof(hsd_804CF7E8) - sizeof(hsd_804CF7E8.x24));
    hsd_804CF7E8.out_buf = buf;
    hsd_804CF7E8.buf_size = size;
    memset(buf, 0, size);
    hsd_804CF7E8.x0_b0 = true;
    hsd_804CF7E8.x0_b1 = true;
    HSD_SetReportCallback(fn_80393C14);
}
#pragma pop

#pragma push
#pragma dont_inline on
void hsd_80393E34(s32* col_out, s32* row_out)
{
    if (col_out != NULL) {
        *col_out = hsd_804CF7E8.x14;
    }
    if (row_out != NULL) {
        *row_out = hsd_804CF7E8.x18;
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
void hsd_80393E68(u32 col, u32 row)
{
    struct ParticleConsoleState* sp = &hsd_804CF7E8;
    u32 byte_val;
    u32 buf_size;
    u8* out_buf;
    u32 sum;
    u32 pos;
    u32 counter;

    if (!sp->x0_b0) {
        return;
    }

    byte_val = sp->x11;
    counter = 0;
    buf_size = sp->buf_size;
    out_buf = sp->out_buf;
    sum = sp->xC + buf_size;
    pos = byte_val;

    while (counter < row && pos < buf_size) {
        pos++;
        byte_val = out_buf[(sum - pos) % buf_size];
        counter++;
        pos += byte_val;
    }

    sp->x18 = counter;
    sp->x1C = pos;
    sp->x20 = byte_val;

    if (col < byte_val) {
        sp->x14 = col;
    } else {
        sp->x14 = byte_val;
    }
}
#pragma pop

#pragma push
#pragma dont_inline on
void hsd_80393EF4(int col_delta, int row_delta)
{
    u32 byte_val;
    u32 buf_size;
    int* pos_ptr;
    u32 counter;
    u32 pos;
    u32 sum;
    u8* out_buf;
    struct ParticleConsoleState* sp = &hsd_804CF7E8;

    if (!sp->x0_b0) {
        return;
    }

    buf_size = sp->buf_size;

    if ((u32) * (pos_ptr = &sp->x1C) >= buf_size) {
        hsd_80393E68(sp->x14 + col_delta, sp->x18 + row_delta);
        return;
    }

    out_buf = sp->out_buf;
    pos = *pos_ptr;
    byte_val = sp->x20;
    sum = sp->xC + buf_size;

    if (row_delta > 0) {
        counter = 0;

        while (counter < (u32) row_delta && pos < buf_size) {
            pos++;
            byte_val = out_buf[(sum - pos) % buf_size];
            counter++;
            pos += byte_val;
        }

        sp->x18 += counter;
        *pos_ptr = pos;

        if (col_delta >= 0) {
            int* col_ptr = &sp->x14;
            *col_ptr += col_delta;
            if ((u32) *col_ptr > byte_val) {
                *col_ptr = byte_val;
            }
        } else {
            int* col_ptr;
            u32 col = *(col_ptr = &sp->x14);
            col_delta = -col_delta;
            if (col > (u32) col_delta) {
                *col_ptr = col - (u32) col_delta;
            } else {
                *col_ptr = 0;
            }
        }
    } else if (row_delta < 0) {
        if (col_delta < 0 && (u32) sp->x14 < (u32) -col_delta) {
            col_delta = 0;
        } else {
            col_delta = sp->x14 + col_delta;
        }

        if (row_delta < 0 && (u32) sp->x18 < (u32) -row_delta) {
            row_delta = 0;
        } else {
            row_delta = sp->x18 + row_delta;
        }

        hsd_80393E68(col_delta, row_delta);
    }
}
#pragma pop

#pragma push
#pragma pool_data off
#pragma dont_inline on
u8 hsd_80394068(void)
{
    u8 result;

    if (!hsd_804CF7E8.x0_b0) {
        return 0;
    }
    if ((u32) hsd_804CF7E8.x1C > hsd_804CF7E8.buf_size) {
        return 0;
    }
    if ((u32) hsd_804CF7E8.x14 < (u32) hsd_804CF7E8.x20) {
        result =
            hsd_804CF7E8.out_buf[(hsd_804CF7E8.x14 +
                                  (hsd_804CF7E8.xC + hsd_804CF7E8.buf_size -
                                   hsd_804CF7E8.x1C)) %
                                 hsd_804CF7E8.buf_size];
        hsd_804CF7E8.x14++;
    } else {
        result = 0;
        hsd_80393EF4(0, -1);
        hsd_804CF7E8.x14 = 0;
    }
    return result;
}
#pragma pop

#pragma push
#pragma dont_inline on
u8 hsd_80394128(s32 col, s32 row)
{
    struct {
        u8 value;
    } result;

    hsd_80393E68(col, row);
    if (!hsd_804CF7E8.x0_b0) {
        result.value = 0;
    } else if ((u32) hsd_804CF7E8.x1C > hsd_804CF7E8.buf_size) {
        result.value = 0;
    } else if ((u32) hsd_804CF7E8.x14 < (u32) hsd_804CF7E8.x20) {
        result.value =
            hsd_804CF7E8.out_buf[(hsd_804CF7E8.x14 +
                                  (hsd_804CF7E8.xC + hsd_804CF7E8.buf_size -
                                   hsd_804CF7E8.x1C)) %
                                 hsd_804CF7E8.buf_size];
        hsd_804CF7E8.x14++;
    } else {
        result.value = 0;
        hsd_80393EF4(0, -1);
        hsd_804CF7E8.x14 = result.value;
    }
    return result.value;
}
#pragma pop

s32 hsd_803941E8(void* xfb_out_ptr, void* xfb_cur_ptr)
{
    s32* xfb_out = xfb_out_ptr;
    u32* xfb_cur = xfb_cur_ptr;
    s32 last_draw;
    u8* vi_base;
    s32 nb_xfb;
    s32 i;
    u32 buf;
    PAD_STACK(8);

    HSD_VIWaitXFBFlushNoYield();
    last_draw = HSD_VIGetXFBLastDrawDone();

    if (last_draw != -1) {
        *xfb_cur = (u32) HSD_VIData.xfb[last_draw].buffer;
    }

    vi_base = (u8*) &HSD_VIData;
    nb_xfb = HSD_VIData.nb_xfb;
    for (i = 0; i < nb_xfb; i++) {
        if (i == last_draw) {
            goto next1;
        }
        buf = *(u32*) (vi_base + 0x58);
        xfb_out[0] = buf;
        if (buf != 0) {
            break;
        }
    next1:
        vi_base += 0x60;
    }

    i++;
    vi_base = (u8*) &HSD_VIData + i * 0x60;
    for (; i < nb_xfb; i++) {
        if (i == last_draw) {
            goto next2;
        }
        buf = *(u32*) (vi_base + 0x58);
        xfb_out[1] = buf;
        if (buf != 0) {
            break;
        }
    next2:
        vi_base += 0x60;
    }

    if ((u32) xfb_out[0] == 0) {
        if (xfb_cur != NULL) {
            xfb_out[0] = (s32) *xfb_cur;
            *xfb_cur = 0;
        } else {
            return 0;
        }
    }

    if ((u32) xfb_out[1] != 0) {
        return 2;
    }
    return 1;
}

/// @todo misnomer - moved from particle file, not particle-related
struct ParticleScreenState {
    /* 0x00 */ u8 x0_b7 : 1;
    /* 0x00 */ u8 x0_b6 : 1;
    /* 0x00 */ u8 x0_b5 : 1;
    /* 0x00 */ u8 x0_rest : 5;
    /* 0x01 */ u8 _pad0[0x3];
    /* 0x04 */ s32 x4;
    /* 0x08 */ s32 x8;
    /* 0x0C */ s32 x0C;
    /* 0x10 */ s32 x10;
    /* 0x14 */ s32 x14;
    /* 0x18 */ s32 x18;
    /* 0x1C */ s32 x1C;
    /* 0x20 */ s32 x20;
    /* 0x24 */ s32 x24;
    /* 0x28 */ u32 x28;
    /* 0x2C */ s32 x2C;
    /* 0x30 */ void* x30;
    /* 0x34 */ s32 x34;
    /* 0x38 */ s32 x38;
    /* 0x3C */ s32 x3C;
    /* 0x40 */ s32 x40;
    /* 0x44 */ s32 x44;
    /* 0x48 */ s32 x48;
    /* 0x4C */ void* x4C;
    /* 0x50 */ void* x50;
    /* 0x54 */ u8 _pad4[0x68];
    /* 0xBC */ u32 xBC;
    /* 0xC0 */ u32 xC0;
    /* 0xC4 */ s32 xC4;
    /* 0xC8 */ s32 xC8;
    /* 0xCC */ s32 xCC;
    /* 0xD0 */ void* xD0;
    /* 0xD4 */ OSContext* xD4;
};
extern u8 lbl_804088B8[];
