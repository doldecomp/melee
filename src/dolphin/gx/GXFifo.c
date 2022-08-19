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

#ifdef NON_MATCHING

#else

#endif

asm void GXSetGPFifo()
{ // clang-format off
    nofralloc
/* 8033BABC 0033869C  7C 08 02 A6 */	mflr r0
/* 8033BAC0 003386A0  90 01 00 04 */	stw r0, 4(r1)
/* 8033BAC4 003386A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033BAC8 003386A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033BACC 003386AC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033BAD0 003386B0  7C 7E 1B 78 */	mr r30, r3
/* 8033BAD4 003386B4  48 00 B8 91 */	bl OSDisableInterrupts
/* 8033BAD8 003386B8  7C 7F 1B 78 */	mr r31, r3
/* 8033BADC 003386BC  48 00 01 CD */	bl __GXFifoReadDisable
/* 8033BAE0 003386C0  38 60 00 00 */	li r3, 0
/* 8033BAE4 003386C4  38 80 00 00 */	li r4, 0
/* 8033BAE8 003386C8  48 00 02 29 */	bl __GXWriteFifoIntEnable
/* 8033BAEC 003386CC  93 CD BC 64 */	stw r30, GPFifo(r13)
/* 8033BAF0 003386D0  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BAF4 003386D4  80 1E 00 00 */	lwz r0, 0(r30)
/* 8033BAF8 003386D8  B0 03 00 20 */	sth r0, 0x20(r3)
/* 8033BAFC 003386DC  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033BB00 003386E0  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB04 003386E4  B0 03 00 24 */	sth r0, 0x24(r3)
/* 8033BB08 003386E8  80 1E 00 1C */	lwz r0, 0x1c(r30)
/* 8033BB0C 003386EC  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB10 003386F0  B0 03 00 30 */	sth r0, 0x30(r3)
/* 8033BB14 003386F4  80 1E 00 18 */	lwz r0, 0x18(r30)
/* 8033BB18 003386F8  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB1C 003386FC  B0 03 00 34 */	sth r0, 0x34(r3)
/* 8033BB20 00338700  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8033BB24 00338704  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB28 00338708  B0 03 00 38 */	sth r0, 0x38(r3)
/* 8033BB2C 0033870C  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 8033BB30 00338710  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB34 00338714  B0 03 00 28 */	sth r0, 0x28(r3)
/* 8033BB38 00338718  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8033BB3C 0033871C  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB40 00338720  B0 03 00 2C */	sth r0, 0x2c(r3)
/* 8033BB44 00338724  80 1E 00 00 */	lwz r0, 0(r30)
/* 8033BB48 00338728  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB4C 0033872C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB50 00338730  B0 03 00 22 */	sth r0, 0x22(r3)
/* 8033BB54 00338734  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033BB58 00338738  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB5C 0033873C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB60 00338740  B0 03 00 26 */	sth r0, 0x26(r3)
/* 8033BB64 00338744  80 1E 00 1C */	lwz r0, 0x1c(r30)
/* 8033BB68 00338748  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB6C 0033874C  7C 00 86 70 */	srawi r0, r0, 0x10
/* 8033BB70 00338750  B0 03 00 32 */	sth r0, 0x32(r3)
/* 8033BB74 00338754  80 1E 00 18 */	lwz r0, 0x18(r30)
/* 8033BB78 00338758  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB7C 0033875C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB80 00338760  B0 03 00 36 */	sth r0, 0x36(r3)
/* 8033BB84 00338764  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8033BB88 00338768  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB8C 0033876C  54 00 84 BE */	rlwinm r0, r0, 0x10, 0x12, 0x1f
/* 8033BB90 00338770  B0 03 00 3A */	sth r0, 0x3a(r3)
/* 8033BB94 00338774  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 8033BB98 00338778  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BB9C 0033877C  54 00 84 3E */	srwi r0, r0, 0x10
/* 8033BBA0 00338780  B0 03 00 2A */	sth r0, 0x2a(r3)
/* 8033BBA4 00338784  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8033BBA8 00338788  80 6D BC 54 */	lwz r3, __cpReg(r13)
/* 8033BBAC 0033878C  54 00 84 3E */	srwi r0, r0, 0x10
/* 8033BBB0 00338790  B0 03 00 2E */	sth r0, 0x2e(r3)
/* 8033BBB4 00338794  7C 00 04 AC */	sync 
/* 8033BBB8 00338798  80 6D BC 60 */	lwz r3, CPUFifo(r13)
/* 8033BBBC 0033879C  80 0D BC 64 */	lwz r0, GPFifo(r13)
/* 8033BBC0 003387A0  7C 03 00 40 */	cmplw r3, r0
/* 8033BBC4 003387A4  40 82 00 24 */	bne lbl_8033BBE8
/* 8033BBC8 003387A8  38 00 00 01 */	li r0, 1
/* 8033BBCC 003387AC  98 0D BC 6C */	stb r0, CPGPLinked(r13)
/* 8033BBD0 003387B0  38 60 00 01 */	li r3, 1
/* 8033BBD4 003387B4  38 80 00 00 */	li r4, 0
/* 8033BBD8 003387B8  48 00 01 39 */	bl __GXWriteFifoIntEnable
/* 8033BBDC 003387BC  38 60 00 01 */	li r3, 1
/* 8033BBE0 003387C0  48 00 00 ED */	bl __GXFifoLink
/* 8033BBE4 003387C4  48 00 00 20 */	b lbl_8033BC04
lbl_8033BBE8:
/* 8033BBE8 003387C8  38 00 00 00 */	li r0, 0
/* 8033BBEC 003387CC  98 0D BC 6C */	stb r0, CPGPLinked(r13)
/* 8033BBF0 003387D0  38 60 00 00 */	li r3, 0
/* 8033BBF4 003387D4  38 80 00 00 */	li r4, 0
/* 8033BBF8 003387D8  48 00 01 19 */	bl __GXWriteFifoIntEnable
/* 8033BBFC 003387DC  38 60 00 00 */	li r3, 0
/* 8033BC00 003387E0  48 00 00 CD */	bl __GXFifoLink
lbl_8033BC04:
/* 8033BC04 003387E4  38 60 00 01 */	li r3, 1
/* 8033BC08 003387E8  38 80 00 01 */	li r4, 1
/* 8033BC0C 003387EC  48 00 01 51 */	bl __GXWriteFifoIntReset
/* 8033BC10 003387F0  48 00 00 71 */	bl __GXFifoReadEnable
/* 8033BC14 003387F4  7F E3 FB 78 */	mr r3, r31
/* 8033BC18 003387F8  48 00 B7 75 */	bl OSRestoreInterrupts
/* 8033BC1C 003387FC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033BC20 00338800  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033BC24 00338804  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033BC28 00338808  7C 08 03 A6 */	mtlr r0
/* 8033BC2C 0033880C  38 21 00 18 */	addi r1, r1, 0x18
/* 8033BC30 00338810  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

asm void __GXFifoInit()
{ // clang-format off
    nofralloc
/* 8033BC34 00338814  7C 08 02 A6 */	mflr r0
/* 8033BC38 00338818  3C 60 80 34 */	lis r3, GXCPInterruptHandler@ha
/* 8033BC3C 0033881C  90 01 00 04 */	stw r0, 4(r1)
/* 8033BC40 00338820  38 83 B7 88 */	addi r4, r3, GXCPInterruptHandler@l
/* 8033BC44 00338824  38 60 00 11 */	li r3, 0x11
/* 8033BC48 00338828  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033BC4C 0033882C  48 00 B7 65 */	bl __OSSetInterruptHandler
/* 8033BC50 00338830  38 60 40 00 */	li r3, 0x4000
/* 8033BC54 00338834  48 00 BB 61 */	bl __OSUnmaskInterrupts
/* 8033BC58 00338838  48 00 F0 E5 */	bl OSGetCurrentThread
/* 8033BC5C 0033883C  38 00 00 00 */	li r0, 0
/* 8033BC60 00338840  90 6D BC 68 */	stw r3, __GXCurrentThread(r13)
/* 8033BC64 00338844  90 0D BC 70 */	stw r0, GXOverflowSuspendInProgress(r13)
/* 8033BC68 00338848  90 0D BC 60 */	stw r0, CPUFifo(r13)
/* 8033BC6C 0033884C  90 0D BC 64 */	stw r0, GPFifo(r13)
/* 8033BC70 00338850  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033BC74 00338854  38 21 00 08 */	addi r1, r1, 8
/* 8033BC78 00338858  7C 08 03 A6 */	mtlr r0
/* 8033BC7C 0033885C  4E 80 00 20 */	blr 
} // clang-format on
#pragma peephole on

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
