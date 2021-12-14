#include "sysdolphin/baselib/controller.h"

extern PadLibData HSD_PadLibData;

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
