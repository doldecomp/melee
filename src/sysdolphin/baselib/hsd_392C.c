#include "hsd_392C.h"

#include <placeholder.h>

#include <dolphin/mcc.h>
#include <sysdolphin/baselib/hsd_3933.h>

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

/* 4D7890 */ static s32 hsd_804D7890;
/* 4D7894 */ static int hsd_804D7894;
/* 4D7898 */ static s32 hsd_804D7898;
/* 4D789C */ static s32 hsd_804D789C;
/* 4D78B8 */ extern s32 hsd_804D78B8;
/* 4D78BC */ extern s32 hsd_804D78BC;

s32 fn_80392CCC(s32 channel)
{
    hsd_804D7894 = channel;
    return 0;
}

u8 fn_80392CD8(char* caller)
{
    char* msg;
    u8 err;

    err = MCCGetLastError();

    switch (err) {
    case 0:
        return err;
    case 1:
        msg = "MCC is no initialize";
        break;
    case 2:
        msg = "No responce";
        break;
    case 3:
        msg = "PING error";
        break;
    case 4:
        msg = "Could not initialize HIO";
        break;
    case 5:
        msg = "Could not read HIO mailbox";
        break;
    case 6:
        msg = "Could not write HIO mailbox";
        break;
    case 7:
        msg = "Could not read HIO memory";
        break;
    case 8:
        msg = "Could not write HIO memory";
        break;
    case 9:
        msg = "Could not read HIO status";
        break;
    case 10:
        msg = "Could not flush channelInfo";
        break;
    case 11:
        msg = "Could not load channelInfo";
        break;
    case 12:
        msg = "Not enough memory block";
        break;
    case 13:
        msg = "Invalid function parameter";
        break;
    case 14:
        msg = "Invalid channel parameter";
        break;
    case 15:
        msg = "Invalid data size";
        break;
    case 16:
        msg = "Invalid offset parameter";
        break;
    case 17:
        msg = "Channel was (already) opened";
        break;
    case 18:
        msg = "Channel was (already) closed";
        break;
    case 19:
        msg = "Channel was (already) locked";
        break;
    case 20:
        msg = "Channel was (already) unlocked";
        break;
    case 21:
        msg = "Channel (read/write) busy";
        break;
    default:
        msg = "Unknown error";
        break;
    }

    if (caller != NULL) {
        OSReport("%s: MCC Error, %s (%d)\n", caller, msg, err);
    } else {
        OSReport("MCC Error, %s (%d)\n", msg, err);
    }
    return err;
}

s32 hsd_804CE728[0x106];

void fn_80392E2C(s32 event_type)
{
    s32 idx;

    if (hsd_804D7898 <= 0x100 && (u32) (event_type - 1) <= 1U) {
        idx = hsd_804D789C + hsd_804D7898;
        hsd_804CE728[idx % 256] = event_type;
        hsd_804D7898 += 1;
    }
}

extern s32 hsd_804CF740[42];

extern int hsd_804D78A0;
extern s32 hsd_804D78A8;
extern s32 hsd_804D78AC;

// @TODO: Currently 92.84% match - needs minor register allocation fix
int hsd_80392E80(void)
{
    enum MCC_CONNECT status;
    s32 event;
    s32 head;
    s32 startTick;
    s32 waiting;
    s32 intr;
    s32* channel_flags;
    PAD_STACK(12);

    for (;;) {
        intr = OSDisableInterrupts();
        if (hsd_804D7898 == 0) {
            OSRestoreInterrupts(intr);
            break;
        }

        head = hsd_804D789C + 1;
        event = hsd_804CE728[hsd_804D789C];
        hsd_804D7898 -= 1;
        hsd_804D789C = head % 256;
        OSRestoreInterrupts(intr);

        switch (event) {
        case 2:
            OSReport("Connecting...\n");
            hsd_804D78AC = 0;
            hsd_804D78A8 = 0;
            OSReport("FIO Init...");
            if (FIOInit(hsd_804D7890, 1, 10) == 0) {
                OSReport("NG\n");
            } else {
                OSReport("OK\n");
                hsd_804D78A0 = 1;
            }
            OSReport("MCC Open...");
            if (MCCOpen(0xF, 1, (MCC_CBEvent) fn_803932D0) == 0) {
                OSReport("NG\n");
                OSReport("Reseting...\n");
                FIOExit();
                hsd_804D78A0 = 0;
                MCCExit();
                if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) ==
                    0)
                {
                    OSReport("MCCInit Failed.\n");
                }
            } else {
                OSReport("Waiting for connection...");
                waiting = 1;
                startTick = OSGetTick();
                for (;;) {
                    if (MCCGetConnectionStatus(0xF, &status) != 0 &&
                        status == 3)
                    {
                        waiting = 0;
                    } else if ((u32) ((u32) (OSGetTick() - startTick) /
                                      OS_TIMER_CLOCK) < 3U)
                    {
                        continue;
                    }
                    break;
                }
                if (waiting != 0) {
                    OSReport("NG\n");
                    OSReport("Reseting...\n");
                    FIOExit();
                    hsd_804D78A0 = 0;
                    MCCExit();
                    if (MCCInit(hsd_804D7890, 0,
                                (MCC_CBSysEvent) fn_80392E2C) == 0)
                    {
                        OSReport("MCCInit Failed.\n");
                    }
                } else {
                    OSReport("OK\n");
                    channel_flags = (s32*) hsd_804CF740;
                    channel_flags[0] = 0;
                    channel_flags[1] = 0;
                    channel_flags[2] = 0;
                    channel_flags[3] = 0;
                    channel_flags[4] = 0;
                    channel_flags[5] = 0;
                    channel_flags[6] = 0;
                    channel_flags[7] = 0;
                    channel_flags[8] = 0;
                    channel_flags[9] = 0;
                    channel_flags[10] = 0;
                    channel_flags[11] = 0;
                    channel_flags[12] = 0;
                    channel_flags[13] = 0;
                    channel_flags[14] = 0;
                    channel_flags[15] = 0;
                    channel_flags[0] = 1;
                    channel_flags[8] = 1;
                    channel_flags[15] = 1;
                }
            }
            break;
        case 1:
            OSReport("Disconnecting...\n");
            if (hsd_80393328() == 0) {
                OSReport("Disconnection failed.\n");
                OSReport("Reseting...\n");
                FIOExit();
                hsd_804D78A0 = 0;
                MCCExit();
                if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) ==
                    0)
                {
                    OSReport("MCCInit Failed.\n");
                }
            } else {
                OSReport("Disconnection OK.\n");
            }
            break;
        }
    }
    hsd_80393844();
    return 0;
}

bool hsd_803931A4(s32 exi_channel)
{
    s32 channel;
    s32* channel_flags;
    PAD_STACK(16);

    channel_flags = (s32*) hsd_804CF740;
    channel_flags[0] = 0;
    channel_flags[1] = 0;
    channel_flags[2] = 0;
    channel_flags[3] = 0;
    channel_flags[4] = 0;
    channel_flags[5] = 0;
    channel_flags[6] = 0;
    channel_flags[7] = 0;
    channel_flags[8] = 0;
    channel_flags[9] = 0;
    channel_flags[10] = 0;
    channel_flags[11] = 0;
    channel_flags[12] = 0;
    channel_flags[13] = 0;
    channel_flags[14] = 0;
    channel_flags[15] = 0;
    channel_flags[0] = 1;
    channel_flags[8] = 1;
    channel_flags[15] = 1;

    channel = exi_channel;

    if (channel < 0) {
        hsd_804D7894 = -1;
        MCCEnumDevices((MCC_CBEnumDevices) fn_80392CCC);
        channel = hsd_804D7894;
        if ((s32) hsd_804D7894 < 0) {
            channel = 0;
        }
    }

    hsd_804D7890 = channel;
    hsd_80393A54(1);
    hsd_804D78A0 = 0;
    hsd_804D7898 = 0;
    hsd_804D789C = 0;
    hsd_804D78BC = 0;
    hsd_804D78B8 = 0;

    if (MCCInit(hsd_804D7890, 0, (MCC_CBSysEvent) fn_80392E2C) == 0) {
        OSReport("EXI_%d:not support USB (Error=%d)\n", channel,
                 MCCGetLastError());
        return 0;
    }

    OSReport("EXI initialized (EXI_%d)\n", channel);
    return 1;
}
