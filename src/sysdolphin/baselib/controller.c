#include <sysdolphin/baselib/controller.h>

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

    return (p->reset_switch != 0) ? TRUE : FALSE;
}
