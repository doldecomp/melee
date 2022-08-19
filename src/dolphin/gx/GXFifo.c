#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GXFifo.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>

/* 004D3EF8 */ extern s32 __GXOverflowCount;
/* 004D3EF4 */ extern void (*BreakPointCB)();
/* 004D3EF0 */ extern BOOL GXOverflowSuspendInProgress;
/* 004D3EEC */ extern GXBool CPGPLinked;
/* 004D3EE8 */ extern OSThread *__GXCurrentThread;

// todo: order is swapped from SMB. Confirm they are named correctly.
/* 004D3EE4 */ extern GXFifoObj *GPFifo;
/* 004D3EE0 */ extern GXFifoObj *CPUFifo;

void __GXWriteFifoIntReset(u8 arg0, u8 arg1);
void GXInitFifoPtrs(GXFifoObj *fifo, void *readPtr, void *writePtr);
void GXInitFifoLimits(GXFifoObj *fifo, u32 hiWaterMark, u32 loWaterMark);
void __GXWriteFifoIntEnable(GXBool flag0, GXBool flag1);
void __GXFifoLink(GXBool flag);
void __GXFifoReadEnable();
void __GXFifoReadDisable();

static void GXCPInterruptHandler(__OSInterrupt unused, OSContext *ctx)
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

void GXInitFifoBase(GXFifoObj *fifo, void *base, u32 size)
{
    __GXFifoObj *__fifo = (__GXFifoObj *)fifo;

    __fifo->base = base;
    __fifo->end = (u8 *)base + size - 4;
    __fifo->size = size;
    __fifo->x1C = 0;
    GXInitFifoLimits(fifo, size - 0x4000, (size >> 1) & ~0x1F);
    GXInitFifoPtrs(fifo, base, base);
}

void GXInitFifoPtrs(GXFifoObj *fifo, void *readPtr, void *writePtr)
{
    __GXFifoObj *__fifo = (__GXFifoObj *)fifo;
    BOOL intrEnabled = OSDisableInterrupts();

    __fifo->readPtr = readPtr;
    __fifo->writePtr = writePtr;
    __fifo->x1C = (u8 *)writePtr - (u8 *)readPtr;
    if (__fifo->x1C < 0)
        __fifo->x1C += __fifo->size;
    OSRestoreInterrupts(intrEnabled);
}

void GXInitFifoLimits(GXFifoObj *fifo, u32 hiWaterMark, u32 loWaterMark)
{
    __GXFifoObj *__fifo = (__GXFifoObj *)fifo;

    __fifo->hiWaterMark = hiWaterMark;
    __fifo->loWaterMark = loWaterMark;
}

void GXSetCPUFifo(GXFifoObj *fifo)
{
    __GXFifoObj *__fifo = (__GXFifoObj *)fifo;
    BOOL intrEnabled = OSDisableInterrupts();

    CPUFifo = fifo;
    if (fifo == GPFifo)
    {
        u32 temp_r6;

        __piReg[3] = (u32)__fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)__fifo->end & 0x3FFFFFFF;
        temp_r6 = (u32)__fifo->writePtr & ~0xC000001F;
        __piReg[5] = temp_r6 & 0xFBFFFFFF;

        CPGPLinked = GX_TRUE;
        __GXWriteFifoIntReset(1, 1);
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    }
    else
    {
        u32 temp_r0;

        if (CPGPLinked)
        {
            __GXFifoLink(0);
            CPGPLinked = FALSE;
        }
        __GXWriteFifoIntEnable(0, 0);

        __piReg[3] = (u32)__fifo->base & 0x3FFFFFFF;
        __piReg[4] = (u32)__fifo->end & 0x3FFFFFFF;
        temp_r0 = (u32)__fifo->writePtr & ~0xC000001F;
        __piReg[5] = temp_r0 & 0xFBFFFFFF;
    }

    __sync();

    OSRestoreInterrupts(intrEnabled);
    return;

// Despite this obviously being dead code, it still is needed to match the function.
// todo: This is weird; try to match without it.
#ifndef NON_MATCHING
    asm {nop}
#pragma peephole on
#endif
}

void GXSetGPFifo(GXFifoObj *fifo)
{
    __GXFifoObj *__fifo = (__GXFifoObj *)fifo;
    BOOL intrEnabled = OSDisableInterrupts();

    __GXFifoReadDisable();
    __GXWriteFifoIntEnable(0, 0);
    GPFifo = fifo;

    __cpReg[16] = (u32)__fifo->base & 0xFFFF;
    __cpReg[18] = (u32)__fifo->end & 0xFFFF;
    __cpReg[24] = __fifo->x1C & 0xFFFF;
    __cpReg[26] = (u32)__fifo->writePtr & 0xFFFF;
    __cpReg[28] = (u32)__fifo->readPtr & 0xFFFF;
    __cpReg[20] = (u32)__fifo->hiWaterMark & 0xFFFF;
    __cpReg[22] = (u32)__fifo->loWaterMark & 0xFFFF;
    __cpReg[17] = ((u32)__fifo->base >> 16) & 0x3FFF;
    __cpReg[19] = ((u32)__fifo->end >> 16) & 0x3FFF;
    __cpReg[25] = __fifo->x1C >> 16;
    __cpReg[27] = ((u32)__fifo->writePtr >> 16) & 0x3FFF;
    __cpReg[29] = ((u32)__fifo->readPtr >> 16) & 0x3FFF;
    __cpReg[21] = (u32)__fifo->hiWaterMark >> 16;
    __cpReg[23] = (u32)__fifo->loWaterMark >> 16;

    __sync();

    if (CPUFifo == GPFifo)
    {
        CPGPLinked = TRUE;
        __GXWriteFifoIntEnable(1, 0);
        __GXFifoLink(1);
    }
    else
    {
        CPGPLinked = FALSE;
        __GXWriteFifoIntEnable(0, 0);
        __GXFifoLink(0);
    }
    __GXWriteFifoIntReset(1, 1);
    __GXFifoReadEnable();
    OSRestoreInterrupts(intrEnabled);
}

void __GXFifoInit()
{
    __OSSetInterruptHandler(OS_INTR_PI_CP, GXCPInterruptHandler);
    __OSUnmaskInterrupts(0x4000);
    __GXCurrentThread = OSGetCurrentThread();
    GXOverflowSuspendInProgress = FALSE;
    CPUFifo = NULL;
    GPFifo = NULL;
}

static void __GXFifoReadEnable()
{
    u32 *x8 = (u32 *)&__GXContexts.main->x8;
    INSERT_FIELD(*x8, 1, 1, 0);
    x8 = (u32 *)&__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXFifoReadDisable()
{
    u32 *x8 = (u32 *)&__GXContexts.main->x8;
    INSERT_FIELD(*x8, 0, 1, 0);
    x8 = (u32 *)&__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXFifoLink(GXBool flag)
{
    BOOL flag32 = flag ? TRUE : FALSE;
    u32 *x8 = (u32 *)&__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag32, 1, 4);
    x8 = (u32 *)&__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

static void __GXWriteFifoIntEnable(GXBool flag0, GXBool flag1)
{
    u32 *x8 = (u32 *)&__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag0, 1, 2);
    x8 = (u32 *)&__GXContexts.main->x8;
    INSERT_FIELD(*x8, flag1, 1, 3);
    x8 = (u32 *)&__GXContexts.main->x8;
    __cpReg[1] = *x8;
}

#ifdef NON_MATCHING

#else

#endif

static asm void __GXWriteFifoIntReset(u8 arg0, u8 arg1)
{ // clang-format off
    nofralloc
/* 8033BD5C 0033893C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033BD60 00338940  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 8033BD64 00338944  54 80 0D FC */	rlwinm r0, r4, 1, 0x17, 0x1e
/* 8033BD68 00338948  38 C5 00 10 */	addi r6, r5, 0x10
/* 8033BD6C 0033894C  80 A5 00 10 */	lwz r5, 0x10(r5)
/* 8033BD70 00338950  54 A4 00 3C */	rlwinm r4, r5, 0, 0, 0x1e
/* 8033BD74 00338954  7C 83 1B 78 */	or r3, r4, r3
/* 8033BD78 00338958  90 66 00 00 */	stw r3, 0(r6)
/* 8033BD7C 0033895C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BD80 00338960  38 83 00 10 */	addi r4, r3, 0x10
/* 8033BD84 00338964  80 63 00 10 */	lwz r3, 0x10(r3)
/* 8033BD88 00338968  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8033BD8C 0033896C  7C 60 03 78 */	or r0, r3, r0
/* 8033BD90 00338970  90 04 00 00 */	stw r0, 0(r4)
/* 8033BD94 00338974  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033BD98 00338978  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BD9C 0033897C  80 04 00 10 */	lwz r0, 0x10(r4)
/* 8033BDA0 00338980  B0 03 00 04 */	sth r0, 4(r3)
/* 8033BDA4 00338984  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on
