#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/dvd.h>

#include "__os.h"

u32 OSGetPhysicalMemSize(void) {
#if DEBUG
    OSBootInfo * BootInfo = (OSBootInfo *)OSPhysicalToCached(0);

    return BootInfo->memorySize;
#else
    return __OSPhysicalMemSize;
#endif
}

u32 OSGetConsoleSimulatedMemSize(void) {
#if DEBUG
    unsigned long * memSize = (unsigned long *)OSPhysicalToCached(0xF0);

    return *memSize;
#else
    return __OSSimulatedMemSize;
#endif
}

static BOOL OnReset(BOOL final)
{
    if (final != FALSE) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return TRUE;
}

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    u32 cause = __MEMRegs[0xF];
    u32 addr = ((__MEMRegs[0x12] & 0x3FF) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (OSErrorTable[0xF]) {
        OSErrorTable[0xF](0xF, context, cause, addr);
        return;
    }

    __OSUnhandledException(0xF, context, cause, addr);
}

#ifdef __MWERKS__

static asm void Config24MB(void)
{ // clang-format off
    nofralloc
    li r7, 0
    lis r4, 0x00000002@ha
    addi r4, r4, 0x00000002@l
    lis r3, 0x800001FF@ha
    addi r3, r3, 0x800001FF@l
    lis r6, 0x01000002@ha
    addi r6, r6, 0x01000002@l
    lis r5, 0x810000FF@ha
    addi r5, r5, 0x810000FF@l
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtspr 0x1b, r3
    mflr r3
    mtspr 0x1a, r3
    rfi
} // clang-format on

static asm void Config48MB(void)
{ // clang-format off
    nofralloc
    li r7, 0
    lis r4, 0x00000002@ha
    addi r4, r4, 0x00000002@l
    lis r3, 0x800003FF@ha
    addi r3, r3, 0x800003FF@l
    lis r6, 0x02000002@ha
    addi r6, r6, 0x02000002@l
    lis r5, 0x820001FF@ha
    addi r5, r5, 0x820001FF@l
    isync
    mtdbatu 0, r7
    mtdbatl 0, r4
    mtdbatu 0, r3
    isync
    mtibatu 0, r7
    mtibatl 0, r4
    mtibatu 0, r3
    isync
    mtdbatu 2, r7
    mtdbatl 2, r6
    mtdbatu 2, r5
    isync
    mtibatu 2, r7
    mtibatl 2, r6
    mtibatu 2, r5
    isync
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    mflr r3
    mtsrr0 r3
    rfi
} // clang-format on

static asm void RealMode(register void (*Event)(void))
{ // clang-format off
    nofralloc
    clrlwi r3, r3, 2
    mtsrr0 r3
    mfmsr r3
    rlwinm r3, r3, 0, 0x1C, 0x19
    mtsrr1 r3
    rfi
} // clang-format on

#endif

static OSResetFunctionInfo ResetFunctionInfo = {
    OnReset,
    0x7F,
};

void __OSInitMemoryProtection(void)
{
    u8 _[40];

    u32 simulated_mem = OSGetConsoleSimulatedMemSize();
    int enabled = OSDisableInterrupts();
    if (simulated_mem <= 24 * 1024 * 1024) {
        RealMode(Config24MB);
    } else if (simulated_mem <= 48 * 1024 * 1024) {
        RealMode(Config48MB);
    }
    __MEMRegs[16] = 0;
    __MEMRegs[8] = 0xFF;
    __OSMaskInterrupts(0xF0000000);
    __OSSetInterruptHandler(0, MEMIntrruptHandler);
    __OSSetInterruptHandler(1, MEMIntrruptHandler);
    __OSSetInterruptHandler(2, MEMIntrruptHandler);
    __OSSetInterruptHandler(3, MEMIntrruptHandler);
    __OSSetInterruptHandler(4, MEMIntrruptHandler);
    OSRegisterResetFunction(&ResetFunctionInfo);
    simulated_mem = OSGetConsoleSimulatedMemSize();
    if (simulated_mem < OSGetPhysicalMemSize() &&
        simulated_mem == 24 * 1024 * 1024) {
        __MEMRegs[20] = 2;
    }
    __OSUnmaskInterrupts(0x08000000);
    OSRestoreInterrupts(enabled);
}
