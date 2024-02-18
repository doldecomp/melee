#include "controller.h"

#include "placeholder.h"

#include "baselib/rumble.h"

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/pad/pad.h>

PadLibData HSD_PadLibData;
HSD_PadStatus HSD_PadMasterStatus[4];
HSD_PadStatus HSD_PadCopyStatus[4];

u8 HSD_PadGetRawQueueCount(void)
{
    u8 queue_count;
    u32 intr;
    PadLibData* p;

    p = &HSD_PadLibData;
    intr = OSDisableInterrupts();
    queue_count = p->qcount;
    OSRestoreInterrupts(intr);

    return queue_count;
}

s32 HSD_PadGetResetSwitch(void)
{
    PadLibData* p = &HSD_PadLibData;

    return (p->reset_switch != 0) ? true : false;
}

static void HSD_PadRawQueueShift(u32 qnum, u8* qpos)
{
    *qpos = (*qpos + 1) - ((*qpos + 1) / qnum) * qnum;
}

static void HSD_PadRawMerge(PADStatus* src1, PADStatus* src2, PADStatus* dst)
{
    dst[0].button = src1[0].button | src2[0].button;
    dst[1].button = src1[1].button | src2[1].button;
    dst[2].button = src1[2].button | src2[2].button;
    dst[3].button = src1[3].button | src2[3].button;
}

void HSD_PadClampCheck1(u8* val, u8 shift, u8 min, u8 max)
{
    if (*val < min) {
        *val = 0;
        return;
    }
    if (*val > max) {
        *val = max;
    }
    if (shift != 1) {
        return;
    }
    *val = *val - min;
}

static void HSD_PadCrossDir(HSD_PadStatus* mp)
{
    switch (HSD_PadLibData.cross_dir) {
    case 0:
        break;

    case 1:
        if ((mp->button & 0xC) == 0) {
            return;
        }
        mp->button = mp->button & 0xFFFFFFFC;
        return;

    case 2:
        if ((mp->button & 0x3) == 0) {
            return;
        }
        mp->button = mp->button & 0xFFFFFFF3;
        return;

    case 3:
        if ((mp->button & 0xC) != 0) {
            if ((mp->button & 3) != 0) {
                if (mp->cross_dir == 1) {
                    mp->button = mp->button & 0xFFFFFFFC;
                    return;
                }
                mp->button = mp->button & 0xFFFFFFF3;
                return;
            } else {
                mp->cross_dir = 1;
                return;
            }
        }
        if ((mp->button & 3) != 0) {
            mp->cross_dir = 2;
            return;
        }
    }
}

void HSD_PadRenewMasterStatus(void)
{
    NOT_IMPLEMENTED;
}

void HSD_PadRenewCopyStatus(void)
{
    NOT_IMPLEMENTED;
}

void HSD_PadZeroQueue(void)
{
    NOT_IMPLEMENTED;
}

void HSD_PadRenewStatus(void)
{
    HSD_PadRenewRawStatus(0);
    HSD_PadRenewMasterStatus();
    HSD_PadRenewCopyStatus();
    HSD_PadZeroQueue();
}

void HSD_PadReset(void)
{
    PadLibData* p;
    bool intr;
    int i;

    p = &HSD_PadLibData;
    intr = OSDisableInterrupts();

    HSD_PadRumbleRemoveAll();

    for (i = 0; i < 4; ++i) {
        HSD_PadRumbleOffN(i);
    }

    HSD_PadFlushQueue(HSD_PAD_FLUSH_QUEUE_THROWAWAY);
    PADRecalibrate(0xF0000000);
    p->reset_switch = 0;

    OSRestoreInterrupts(intr);
}
