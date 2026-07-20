#include "hsd_3933.h"

#include <dolphin/mcc.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/hsd_3915.h>
#include <sysdolphin/baselib/hsd_392C.h>
#include <sysdolphin/baselib/random.h>

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

/* 4D78C0 */ int hsd_804D78C0;
/* 4D78BC */ s32 hsd_804D78BC;
/* 4D78B8 */ s32 hsd_804D78B8;
/* 4D78B4 */ s32 hsd_804D78B4;
/* 4D78B0 */ s32 hsd_804D78B0;
s32 hsd_804D78AC;
s32 hsd_804D78A8;

static ParticleLogEntry hsd_804CEB40[0x100];
s32 hsd_804CF740[42];

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

/* 40A9D0 */ static struct ParticleUsbMessages
    psUsbMessages ATTRIBUTE_ALIGN(8) = {
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
