#include "controller.h"

#include <dolphin/os/OSInterrupt.h>
#include <dolphin/pad/pad.h>

extern PadLibData HSD_PadLibData;
extern HSD_PadStatus HSD_PadMasterStatus[4];
extern HSD_PadStatus HSD_PadCopyStatus[4];
extern HSD_RumbleData HSD_PadRumbleData[4];

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
