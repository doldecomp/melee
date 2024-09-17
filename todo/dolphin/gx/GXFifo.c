#include <platform.h>

#include <dolphin/gx/forward.h>

#include <dolphin/gx/__GXFifo.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__types.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>
#include <MetroTRK/intrinsics.h>

static GXFifoObj* CPUFifo;
static GXFifoObj* GPFifo;
static OSThread* __GXCurrentThread;
static GXBool CPGPLinked;
static bool GXOverflowSuspendInProgress;
static void (*BreakPointCB)(void);
static s32 __GXOverflowCount;

static void __GXWriteFifoIntReset(u8 arg0, u8 arg1);
static void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr);
static void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark,
                             u32 loWaterMark);
static void __GXWriteFifoIntEnable(GXBool flag0, GXBool flag1);
static void __GXFifoLink(GXBool flag);
static void __GXFifoReadEnable(void);
static void __GXFifoReadDisable(void);

static void GXCPInterruptHandler(__OSInterrupt _, OSContext* ctx)
{
    OSContext sp10;
    __GXContexts.main->xC = __cpReg[0];

    if ((uintptr_t) __GXContexts.main->x8 >> 3 & 1 &&
        __GXContexts.main->xC >> 1 & 1)
    {
        OSResumeThread(__GXCurrentThread);
        GXOverflowSuspendInProgress = 0;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
    }
    if ((uintptr_t) __GXContexts.main->x8 >> 2 & 1 &&
        __GXContexts.main->xC & 1)
    {
        __GXOverflowCount++;
        __GXWriteFifoIntEnable(0, 1);
        __GXWriteFifoIntReset(1, 0);
        GXOverflowSuspendInProgress = 1;
        OSSuspendThread(__GXCurrentThread);
    }

    if ((uintptr_t) __GXContexts.main->x8 >> 5 & 1 &&
        __GXContexts.main->xC >> 4 & 1)
    {
        __GXContexts.main->x8 =
            (OSContext*) ((uintptr_t) __GXContexts.main->x8 & ~(1 << 5));
        __cpReg[1] = (u16) (uintptr_t) __GXContexts.main->x8;
        if (BreakPointCB != NULL) {
            OSClearContext(&sp10);
            OSSetCurrentContext(&sp10);
            BreakPointCB();
            OSClearContext(&sp10);
            OSSetCurrentContext(ctx);
        }
    }
}

void GXInitFifoBase(GXFifoObj* fifo, void* base, u32 size)
{
    __GXFifoObj* __fifo = (__GXFifoObj*) fifo;

    __fifo->base = base;
    __fifo->end = (u8*) base + size - 4;
    __fifo->size = size;
    __fifo->x1C = 0;
    GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj* fifo, void* readPtr, void* writePtr)
{
    __GXFifoObj* __fifo = (__GXFifoObj*) fifo;
    bool intrEnabled = OSDisableInterrupts();

    __fifo->readPtr = readPtr;
    __fifo->writePtr = writePtr;
    __fifo->x1C = (u8*) writePtr - (u8*) readPtr;
    if (__fifo->x1C < 0) {
        __fifo->x1C += __fifo->size;
    }
    OSRestoreInterrupts(intrEnabled);
}

void GXInitFifoLimits(GXFifoObj* fifo, u32 hiWaterMark, u32 loWaterMark)
{
    __GXFifoObj* __fifo = (__GXFifoObj*) fifo;

    __fifo->hiWaterMark = hiWaterMark;
    __fifo->loWaterMark = loWaterMark;
}

void GXSetCPUFifo(GXFifoObj* fifo)
{
    __GXFifoObj* __fifo = (__GXFifoObj*) fifo;
    bool intrEnabled = OSDisableInterrupts();

    CPUFifo = fifo;
    if (fifo == GPFifo) {
        u32 temp_r6;

        __piReg[3] = (u32) __fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32) __fifo->end & 0x3FFFFFFF;
        temp_r6 = (u32) __fifo->writePtr & ~0xC000001F;
        __piReg[5] = temp_r6 & 0xFBFFFFFF;

        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        u32 temp_r0;

        if (CPGPLinked) {
            __GXFifoLink(0);
            CPGPLinked = false;
        }
        __GXWriteFifoIntEnable(0, 0);

        __piReg[3] = (u32) __fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32) __fifo->end & 0x3FFFFFFF;
        temp_r0 = (u32) __fifo->writePtr & ~0xC000001F;
        __piReg[5] = temp_r0 & 0xFBFFFFFF;
    }

    __sync();

    OSRestoreInterrupts(intrEnabled);
    return;

// Despite this obviously being dead code, it still is needed to match the
// function.
/// @todo: This is weird; try to match without it.
#ifndef BUGFIX
#pragma push
    asm {nop}
#pragma pop
#endif
}

void GXSetGPFifo(GXFifoObj* fifo)
{
    __GXFifoObj* __fifo = (__GXFifoObj*) fifo;
    bool intrEnabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;

    __cpReg[16] = (u32) __fifo->base & 0xFFFF;
    __cpReg[18] = (u32) __fifo->end & 0xFFFF;
    __cpReg[24] = __fifo->x1C & 0xFFFF;
    __cpReg[26] = (u32) __fifo->writePtr & 0xFFFF;
    __cpReg[28] = (u32) __fifo->readPtr & 0xFFFF;
    __cpReg[20] = (u32) __fifo->hiWaterMark & 0xFFFF;
    __cpReg[22] = (u32) __fifo->loWaterMark & 0xFFFF;
    __cpReg[17] = ((u32) __fifo->base >> 16) & 0x3FFF;
    __cpReg[19] = ((u32) __fifo->end >> 16) & 0x3FFF;
    __cpReg[25] = __fifo->x1C >> 16;
    __cpReg[27] = ((u32) __fifo->writePtr >> 16) & 0x3FFF;
    __cpReg[29] = ((u32) __fifo->readPtr >> 16) & 0x3FFF;
    __cpReg[21] = (u32) __fifo->hiWaterMark >> 16;
    __cpReg[23] = (u32) __fifo->loWaterMark >> 16;

    __sync();

    if (CPUFifo == GPFifo) {
        CPGPLinked = true;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    } else {
        CPGPLinked = false;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(intrEnabled);
}

void __GXFifoInit(void)
{
    __OSSetInterruptHandler(OS_INTR_PI_CP, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = false;
    CPUFifo = NULL;
    GPFifo = NULL;
}

static void __GXFifoReadEnable(void)
{
    u32* x8 = (u32*) &__GXContexts.main->x8;
    INSERT_FIELD(*x8, 1, 1, 0);
    x8 = (u32*) &__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXFifoReadDisable(void)
{
    u32* x8 = (u32*) &__GXContexts.main->x8;
    INSERT_FIELD(*x8, 0, 1, 0);
    x8 = (u32*) &__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXFifoLink(GXBool flag)
{
    bool flag32 = flag ? true : false;
    u32* x8 = (u32*) &__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag32, 1, 4);
    x8 = (u32*) &__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXWriteFifoIntEnable(GXBool flag0, GXBool flag1)
{
    u32* x8 = (u32*) &__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag0, 1, 2);
    x8 = (u32*) &__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag1, 1, 3);
    x8 = (u32*) &__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXWriteFifoIntReset(GXBool flag0, GXBool flag1)
{
    INSERT_FIELD(__GXContexts.main->x10, flag0, 1, 0);
    INSERT_FIELD(__GXContexts.main->x10, flag1, 1, 1);
    __cpReg[2] = __GXContexts.main->x10;
}
