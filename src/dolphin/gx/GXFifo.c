#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/__GXFifo.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSThread.h>

/* 004D3EF8 */ extern s32 __GXOverflowCount;
/* 004D3EF4 */ extern void (*BreakPointCB)();
/* 004D3EF0 */ extern BOOL GXOverflowSuspendInProgress;
/* 004D3EEC */ extern GXBool CPGPLinked;
/* 004D3EE8 */ extern OSThread *__GXCurrentThread;

// todo: order is swapped from SMB. Confirm they are assigned correctly.
/* 004D3EE4 */ extern GXFifoObj *GPFifo;
/* 004D3EE0 */ extern GXFifoObj *CPUFifo;

void __GXWriteFifoIntReset(u8 arg0, u8 arg1);
void GXInitFifoPtrs(GXFifoObj *fifo, void *readPtr, void *writePtr);
void GXInitFifoLimits(GXFifoObj *fifo, u32 hiWaterMark, u32 loWaterMark);
void __GXWriteFifoIntEnable(u8 arg0, u8 arg1);
void __GXFifoLink(u8 arg0);
void __GXFifoReadEnable(void);
void __GXFifoReadDisable(void);

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

#ifdef NON_MATCHING

#else

#endif

static asm void __GXFifoReadEnable(void)
{ // clang-format off
    nofralloc
/* 8033BC80 00338860  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BC84 00338864  84 03 00 08 */	lwzu r0, 8(r3)
/* 8033BC88 00338868  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033BC8C 0033886C  60 00 00 01 */	ori r0, r0, 1
/* 8033BC90 00338870  90 03 00 00 */	stw r0, 0(r3)
/* 8033BC94 00338874  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033BC98 00338878  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BC9C 0033887C  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BCA0 00338880  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BCA4 00338884  4E 80 00 20 */	blr 
} // clang-format on 
#pragma peephole on

static asm void __GXFifoReadDisable(void)
{ // clang-format off 
    nofralloc
/* 8033BCA8 00338888  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BCAC 0033888C  84 03 00 08 */	lwzu r0, 8(r3)
/* 8033BCB0 00338890  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033BCB4 00338894  90 03 00 00 */	stw r0, 0(r3)
/* 8033BCB8 00338898  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033BCBC 0033889C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BCC0 003388A0  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BCC4 003388A4  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BCC8 003388A8  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

static asm void __GXFifoLink(u8 arg0)
{ // clang-format off
    nofralloc
/* 8033BCCC 003388AC  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8033BCD0 003388B0  41 82 00 0C */	beq lbl_8033BCDC
/* 8033BCD4 003388B4  38 00 00 01 */	li r0, 1
/* 8033BCD8 003388B8  48 00 00 08 */	b lbl_8033BCE0
lbl_8033BCDC:
/* 8033BCDC 003388BC  38 00 00 00 */	li r0, 0
lbl_8033BCE0:
/* 8033BCE0 003388C0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BCE4 003388C4  54 00 20 36 */	slwi r0, r0, 4
/* 8033BCE8 003388C8  38 83 00 08 */	addi r4, r3, 8
/* 8033BCEC 003388CC  80 63 00 08 */	lwz r3, 8(r3)
/* 8033BCF0 003388D0  54 63 07 34 */	rlwinm r3, r3, 0, 0x1c, 0x1a
/* 8033BCF4 003388D4  7C 60 03 78 */	or r0, r3, r0
/* 8033BCF8 003388D8  90 04 00 00 */	stw r0, 0(r4)
/* 8033BCFC 003388DC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033BD00 003388E0  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BD04 003388E4  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BD08 003388E8  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BD0C 003388EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

static asm void __GXWriteFifoIntEnable(u8 arg0, u8 arg1)
{ // clang-format off
    nofralloc
/* 8033BD10 003388F0  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033BD14 003388F4  54 63 15 BA */	rlwinm r3, r3, 2, 0x16, 0x1d
/* 8033BD18 003388F8  54 80 1D 78 */	rlwinm r0, r4, 3, 0x15, 0x1c
/* 8033BD1C 003388FC  38 C5 00 08 */	addi r6, r5, 8
/* 8033BD20 00338900  80 A5 00 08 */	lwz r5, 8(r5)
/* 8033BD24 00338904  54 A4 07 B8 */	rlwinm r4, r5, 0, 0x1e, 0x1c
/* 8033BD28 00338908  7C 83 1B 78 */	or r3, r4, r3
/* 8033BD2C 0033890C  90 66 00 00 */	stw r3, 0(r6)
/* 8033BD30 00338910  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033BD34 00338914  38 83 00 08 */	addi r4, r3, 8
/* 8033BD38 00338918  80 63 00 08 */	lwz r3, 8(r3)
/* 8033BD3C 0033891C  54 63 07 76 */	rlwinm r3, r3, 0, 0x1d, 0x1b
/* 8033BD40 00338920  7C 60 03 78 */	or r0, r3, r0
/* 8033BD44 00338924  90 04 00 00 */	stw r0, 0(r4)
/* 8033BD48 00338928  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033BD4C 0033892C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BD50 00338930  80 04 00 08 */	lwz r0, 8(r4)
/* 8033BD54 00338934  B0 03 00 02 */	sth r0, 2(r3)
/* 8033BD58 00338938  4E 80 00 20 */	blr 
} // clang-format on 
#pragma peephole on

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
