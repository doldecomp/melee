#include <platform.h>
#include <placeholder.h>

#include <dolphin/base/PPCArch.h>
#include <dolphin/os.h>
#include <dolphin/os/OSCache.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <MetroTRK/intrinsics.h>

#define MSR_IR 0x00000020
#define MSR_DR 0x00000010
#define L2CR_L2E 0x80000000
#define L2CR_L2I 0x00200000

#define SRR1_DMA_BIT 0x00200000
#define HID0_ICE 0x00008000
#define HID0_DCE 0x00004000
#define HID2_DCHERR 0x00800000
#define HID2_DNCERR 0x00400000
#define HID2_DCMERR 0x00200000
#define HID2_DQOERR 0x00100000

#ifdef MWERKS_GEKKO

asm void DCEnable(void)
{ // clang-format off
    sync
    mfspr r3, HID0
    ori   r3, r3, 0x4000
    mtspr HID0, r3
} // clang-format on

#else

void DCEnable(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void DCInvalidateRange(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    dcbi 0, addr
    addi addr, addr, 32
    bdnz @2
} // clang-format on

#else

void DCInvalidateRange(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void DCFlushRange(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @2
    sc
} // clang-format on

#else

void DCFlushRange(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void DCStoreRange(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    dcbst r0, addr
    addi addr, addr, 32
    bdnz @2
    sc
} // clang-format on

#else

void DCStoreRange(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void DCFlushRangeNoSync(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @2
} // clang-format on

#else

void DCFlushRangeNoSync(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void DCZeroRange(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    dcbz r0, addr
    addi addr, addr, 32
    bdnz @2
} // clang-format on

#else

void DCZeroRange(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void ICInvalidateRange(register void* addr, register size_t nbytes)
{ // clang-format off
    cmplwi nbytes, 0
    blelr
    clrlwi. r5, addr, 27
    beq @1
    addi nbytes, nbytes, 32
@1:
    addi nbytes, nbytes, 31
    srwi nbytes, nbytes, 5
    mtctr nbytes
@2:
    icbi r0, addr
    addi addr, addr, 32
    bdnz @2
    sync
    isync
} // clang-format on

#else

void ICInvalidateRange(void* addr, size_t nbytes)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void ICFlashInvalidate(void)
{ // clang-format off
    mfspr r3, 0x3f0
    ori r3, r3, 0x800
    mtspr 0x3f0, r3
} // clang-format on

#else

void ICFlashInvalidate(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void ICEnable(void)
{ // clang-format off
    isync
    mfspr r3, 0x3f0
    ori r3, r3, 0x8000
    mtspr 0x3f0, r3
} // clang-format on

#else

void ICEnable(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void __LCEnable(void)
{ // clang-format off
    mfmsr r5
    ori r5, r5, 0x1000
    mtmsr r5
    lis r3, 0x80000020@ha
    li r4, 0x400
    mtctr r4
touchloop:
    dcbt 0, r3
    dcbst 0, r3
    addi r3, r3, 0x80000020@l
    bdnz touchloop
    mfspr r4, 0x398
    oris r4, r4, 0x100f
    mtspr 0x398, r4
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    lis r3, 0xE0000002@h
    ori r3, r3, 0xE0000002@l
    mtdbatl 3, r3
    ori r3, r3, 0x1fe
    mtdbatu 3, r3
    isync
    lis r3, 0xE0000020@ha
    li r6, 0x200
    mtctr r6
    li r6, 0
lockloop:
    dcbz_l r6, r3
    addi r3, r3, 0xE0000020@l
    bdnz lockloop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
} // clang-format on

#else

void __LCEnable(void)
{
    NOT_IMPLEMENTED;
}

#endif

void LCEnable(void)
{
    bool enabled = OSDisableInterrupts();
    __LCEnable();
    OSRestoreInterrupts(enabled);
}

#ifdef MWERKS_GEKKO

asm void LCDisable(void)
{ // clang-format off
    lis r3, 0xE0000020@ha
    li r4, 0x200
    mtctr r4
@1:
    dcbi r0, r3
    addi r3, r3, 0xE0000020@l
    bdnz @1
    mfspr r4, 0x398
    rlwinm r4, r4, 0, 4, 2
    mtspr 0x398, r4
} // clang-format on

#else

void LCDisable(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void LCStoreBlocks(register void* dst, register void* src,
                       register u32 nblocks)
{ // clang-format off
    rlwinm r6, nblocks, 30, 27, 31
    clrlwi dst, dst, 4
    or r6, r6, dst
    mtspr 0x39a, r6
    rlwinm r6, nblocks, 2, 28, 29
    or r6, r6, src
    ori r6, r6, 2
    mtspr 0x39b, r6
} // clang-format on

#else

void LCStoreBlocks(void* dst, void* src, u32 nblocks)
{
    NOT_IMPLEMENTED;
}

#endif

u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes)
{
    u32 numBlocks = (nBytes + 31) / 32;
    u32 numTransactions = (numBlocks + 128 - 1) / 128;

    while (numBlocks > 0) {
        if (numBlocks < 128) {
            LCStoreBlocks(destAddr, srcAddr, numBlocks);
            numBlocks = 0;
        } else {
            LCStoreBlocks(destAddr, srcAddr, 0);
            numBlocks -= 128;
            destAddr = (void*) ((u32) destAddr + 4096);
            srcAddr = (void*) ((u32) srcAddr + 4096);
        }
    }

    return numTransactions;
}

#ifdef MWERKS_GEKKO

asm void LCQueueWait(register u32 len)
{ // clang-format off
    nofralloc
    addi len, len, 1
@1:
    mfspr r4, 0x398
    rlwinm r4, r4, 8, 28, 31
    cmpw cr2, r4, len
    bge cr2, @1
    blr
} // clang-format on

#else

void LCQueueWait(u32 len)
{
    NOT_IMPLEMENTED;
}

#endif

extern char lbl_80401BF0[];
void DBPrintf(const char* fmt, ...);

static void L2Disable(void)
{
    __sync();
    PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
    __sync();
}

void L2GlobalInvalidate(void)
{
    L2Disable();
    PPCMtl2cr(PPCMfl2cr() | 0x200000);
    while (PPCMfl2cr() & 1) {
    }
    PPCMtl2cr(PPCMfl2cr() & ~0x200000);
    while (PPCMfl2cr() & 1) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

static void L2Init(void)
{
    u32 oldMSR;
    oldMSR = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();
    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(oldMSR);
}

void L2Enable(void)
{
    PPCMtl2cr((PPCMfl2cr() | L2CR_L2E) & ~L2CR_L2I);
}

static void DMAErrorHandler(OSError error, OSContext* context, ...)
{
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);
    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) ||
        !(context->srr1 & SRR1_DMA_BIT))
    {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport("\t- Requested a locked cache tag that was already in the "
                 "cache\n");
    }

    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }

    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }

    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    // write hid2 back to clear the error bits
    PPCMthid2(hid2);
}

void __OSCacheInit(void)
{
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }
    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

    OSSetErrorHandler(OS_ERROR_MACHINE_CHECK, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
