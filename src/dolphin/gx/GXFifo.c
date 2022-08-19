#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GXFifo.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/gx/GXFifo/GXFifo_001.h>

void GXCPInterruptHandler(__OSInterrupt unused, OSContext *ctx)
{
    OSContext sp10;

    __GXContexts.main->xC = __cpReg[0];
    if (((((u32)__GXContexts.main->x8) >> 3) & 1) && ((__GXContexts.main->xC >> 1) & 1))
    {
        OSResumeThread(__GXCurrentThread);
        GXOverflowSuspendInProgress = 0;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
    }
    if (((((u32)__GXContexts.main->x8) >> 2) & 1) && (__GXContexts.main->xC & 1))
    {
        __GXOverflowCount++;
        __GXWriteFifoIntEnable(0, 1);
        __GXWriteFifoIntReset(1, 0);
        GXOverflowSuspendInProgress = 1;
        OSSuspendThread(__GXCurrentThread);
    }
    if (((((u32)__GXContexts.main->x8) >> 5) & 1) && ((__GXContexts.main->xC >> 4) & 1))
    {
        __GXContexts.main->x8 = (OSContext *)(((u32)__GXContexts.main->x8) & ~(1 << 5));
        __cpReg[1] = (u16)__GXContexts.main->x8;
        if (BreakPointCB != NULL)
        {
            OSClearContext(&sp10);
            OSSetCurrentContext(&sp10);
            BreakPointCB();
            OSClearContext(&sp10);
            OSSetCurrentContext(ctx);
        }
    }
}
