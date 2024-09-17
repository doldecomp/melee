#include <placeholder.h>

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSError.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSReset.h>

extern volatile u32 Mem_Size AT_ADDRESS(0x80000028);
extern volatile u32 Simulated_Mem AT_ADDRESS(0x800000F0);
extern OSErrorHandler __OSErrorTable[];

static bool OnReset(bool);

static OSResetFunctionInfo OSMemory_80402348 = { OnReset, 127, NULL, NULL };

u32 OSGetPhysicalMemSize(void)
{
    return Mem_Size;
}

u32 OSGetConsoleSimulatedMemSize(void)
{
    return Simulated_Mem;
}

static bool OnReset(bool final)
{
    if (final) {
        __MEMRegs[8] = 0xFF;
        __OSMaskInterrupts(0xF0000000);
    }
    return true;
}

static void MEMIntrruptHandler(__OSInterrupt interrupt, OSContext* context)
{
    u32 cause = __MEMRegs[0xf];
    u32 addr = (((u32) __MEMRegs[0x12] & 0x3ff) << 16) | __MEMRegs[0x11];
    __MEMRegs[0x10] = 0;

    if (__OSErrorTable[OS_ERROR_PROTECTION]) {
        __OSErrorTable[OS_ERROR_PROTECTION](OS_ERROR_PROTECTION, context,
                                            cause, addr);
        return;
    }

    __OSUnhandledException(OS_ERROR_PROTECTION, context, cause, addr);
}

#ifdef MWERKS_GEKKO
asm void Config24MB(void)
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
#else

void Config24MB(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void Config48MB(void)
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
#else

void Config48MB(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void RealMode(register Event)
{ // clang-format off
    nofralloc
    clrlwi r3, r3, 2
    mtsrr0 r3
    mfmsr r3
    rlwinm r3, r3, 0, 0x1c, 0x19
    mtsrr1 r3
    rfi
} // clang-format on
#else

void RealMode(Event arg0)
{
    NOT_IMPLEMENTED;
}
#endif

void __OSInitMemoryProtection(void)
{
    u8 _[40];

    u32 simulated_mem = OSGetConsoleSimulatedMemSize();
    bool intr = OSDisableInterrupts();
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
    OSRegisterResetFunction(&OSMemory_80402348);
    simulated_mem = OSGetConsoleSimulatedMemSize();
    if (simulated_mem < Mem_Size && simulated_mem == 24 * 1024 * 1024) {
        __MEMRegs[20] = 2;
    }
    __OSUnmaskInterrupts(0x08000000);
    OSRestoreInterrupts(intr);
}
