#include <placeholder.h>

#include <__mem.h>
#include <dolphin/ai/ai.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os.h>
#include <dolphin/os/OSExi.h>
#include <dolphin/os/OSInit.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSMemory.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSTime.h>
#include <MetroTRK/intrinsics.h>

static __OSInterruptHandler* InterruptHandlerTable;

static OSInterruptMask InterruptPrioTable[] = {
    OS_INTRMASK_PI_ERROR,
    OS_INTRMASK_PI_DEBUG,
    OS_INTRMASK_MEM,
    OS_INTRMASK_PI_RSW,
    OS_INTRMASK_PI_VI,
    OS_INTRMASK_PI_PE,
    OS_INTRMASK_PI_HSP,
    OS_INTRMASK_DSP_ARAM | OS_INTRMASK_DSP_DSP | OS_INTRMASK_AI |
        OS_INTRMASK_EXI | OS_INTRMASK_PI_SI | OS_INTRMASK_PI_DI,
    OS_INTRMASK_DSP_AI,
    OS_INTRMASK_PI_CP,
    0xFFFFFFFF,
};

#ifdef MWERKS_GEKKO
asm bool OSDisableInterrupts(void)
{ // clang-format off
    nofralloc
entry __RAS_OSDisableInterrupts_begin
    mfmsr r3
    rlwinm r4, r3, 0, 0x11, 0xf
    mtmsr r4
    rlwinm r3, r3, 0x11, 0x1f, 0x1f
entry __RAS_OSDisableInterrupts_end
    blr
} // clang-format on
#else
bool OSDisableInterrupts(void)
{
    NOT_IMPLEMENTED;
}
#endif

volatile OSTime __OSLastInterruptTime;
volatile s16 __OSLastInterrupt;
volatile u32 __OSLastInterruptSrr0;

#ifdef MWERKS_GEKKO
asm bool OSEnableInterrupts(void)
{ // clang-format off
    nofralloc
    mfmsr r3
    ori r4, r3, 0x8000
    mtmsr r4
    rlwinm r3, r3, 17, 31, 31
    blr
} // clang-format on
#else
bool OSEnableInterrupts(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm bool OSRestoreInterrupts(register bool level)
{ // clang-format off
    nofralloc
    cmpwi level, 0
    mfmsr r4
    beq _disable
    ori r5, r4, 0x8000
    b _restore
_disable:
    rlwinm r5, r4, 0, 17, 15
_restore:
    mtmsr r5
    rlwinm r4, r4, 17, 31, 31
    blr
} // clang-format on
#else
bool OSRestoreInterrupts(bool level)
{
    NOT_IMPLEMENTED;
}
#endif

extern __OSInterruptHandler* InterruptHandlerTable;

__OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt id,
                                             __OSInterruptHandler handler)
{
    __OSInterruptHandler old_handler = InterruptHandlerTable[id];
    InterruptHandlerTable[id] = handler;
    return old_handler;
}

__OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt id)
{
    return InterruptHandlerTable[id];
}

static void ExternalInterruptHandler(__OSException exception,
                                     OSContext* context);

extern volatile struct {
    u32 x0;
    u32 intr;
} OS_PI AT_ADDRESS(0xCC003000);

extern volatile u32 OS_INTR_OLD AT_ADDRESS(0x800000C4);
extern volatile u32 OS_INTR_CUR AT_ADDRESS(0x800000C8);

void __OSInterruptInit(void)
{
    InterruptHandlerTable = (void*) 0x80003040;
    memset(InterruptHandlerTable, 0, 128);
    OS_INTR_OLD = 0;
    OS_INTR_CUR = 0;
    OS_PI.intr = 0xF0;
    __OSMaskInterrupts(~0x1F);
    __OSSetExceptionHandler(4, ExternalInterruptHandler);
}

u32 SetInterruptMask(OSInterruptMask mask, OSInterruptMask current)
{
    u32 reg;

    switch (__cntlzw(mask)) {
    case OS_INTR_MEM_0:
    case OS_INTR_MEM_1:
    case OS_INTR_MEM_2:
    case OS_INTR_MEM_3:
    case OS_INTR_MEM_ADDRESS:
        reg = 0;
        if (!(current & OS_INTRMASK_MEM_0)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTRMASK_MEM_1)) {
            reg |= 0x2;
        }
        if (!(current & OS_INTRMASK_MEM_2)) {
            reg |= 0x4;
        }
        if (!(current & OS_INTRMASK_MEM_3)) {
            reg |= 0x8;
        }
        if (!(current & OS_INTRMASK_MEM_ADDRESS)) {
            reg |= 0x10;
        }
        __MEMRegs[0x0000000e] = (u16) reg;
        mask &= ~OS_INTRMASK_MEM;
        break;
    case OS_INTR_DSP_AI:
    case OS_INTR_DSP_ARAM:
    case OS_INTR_DSP_DSP:
        reg = __DSPRegs[0x00000005];
        reg &= ~0x1F8;
        if (!(current & OS_INTRMASK_DSP_AI)) {
            reg |= 0x10;
        }
        if (!(current & OS_INTRMASK_DSP_ARAM)) {
            reg |= 0x40;
        }
        if (!(current & OS_INTRMASK_DSP_DSP)) {
            reg |= 0x100;
        }
        __DSPRegs[0x00000005] = (u16) reg;
        mask &= ~OS_INTRMASK_DSP;
        break;
    case OS_INTR_AI_AI:
        reg = __AIRegs[0];
        reg &= ~0x2C;
        if (!(current & OS_INTRMASK_AI_AI)) {
            reg |= 0x4;
        }
        __AIRegs[0] = reg;
        mask &= ~OS_INTRMASK_AI;
        break;
    case OS_INTR_EXI_0_EXI:
    case OS_INTR_EXI_0_TC:
    case OS_INTR_EXI_0_EXT:
        reg = __EXIRegs[0][0];
        reg &= ~0x2C0F;
        if (!(current & OS_INTRMASK_EXI_0_EXI)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTRMASK_EXI_0_TC)) {
            reg |= 0x4;
        }
        if (!(current & OS_INTRMASK_EXI_0_EXT)) {
            reg |= 0x400;
        }
        __EXIRegs[0][0] = reg;
        mask &= ~OS_INTRMASK_EXI_0;
        break;
    case OS_INTR_EXI_1_EXI:
    case OS_INTR_EXI_1_TC:
    case OS_INTR_EXI_1_EXT:
        reg = __EXIRegs[1][0];
        reg &= ~0xC0F;
        if (!(current & OS_INTRMASK_EXI_1_EXI)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTRMASK_EXI_1_TC)) {
            reg |= 0x4;
        }
        if (!(current & OS_INTRMASK_EXI_1_EXT)) {
            reg |= 0x400;
        }
        __EXIRegs[1][0] = reg;
        mask &= ~OS_INTRMASK_EXI_1;
        break;
    case OS_INTR_EXI_2_EXI:
    case OS_INTR_EXI_2_TC:
        reg = __EXIRegs[2][0];
        reg &= ~0xF;
        if (!(current & OS_INTRMASK_EXI_2_EXI)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTRMASK_EXI_2_TC)) {
            reg |= 0x4;
        }
        __EXIRegs[2][0] = reg;
        mask &= ~OS_INTRMASK_EXI_2;
        break;
    case OS_INTR_PI_CP:
    case OS_INTR_PI_SI:
    case OS_INTR_PI_DI:
    case OS_INTR_PI_RSW:
    case OS_INTR_PI_ERROR:
    case OS_INTR_PI_VI:
    case OS_INTR_PI_DEBUG:
    case OS_INTR_PI_PE_TOKEN:
    case OS_INTR_PI_PE_FINISH:
    case OS_INTR_PI_HSP:
        reg = 0xF0;

        if (!(current & OS_INTRMASK_PI_CP)) {
            reg |= 0x800;
        }
        if (!(current & OS_INTRMASK_PI_SI)) {
            reg |= 0x8;
        }
        if (!(current & OS_INTRMASK_PI_DI)) {
            reg |= 0x4;
        }
        if (!(current & OS_INTRMASK_PI_RSW)) {
            reg |= 0x2;
        }
        if (!(current & OS_INTRMASK_PI_ERROR)) {
            reg |= 0x1;
        }
        if (!(current & OS_INTRMASK_PI_VI)) {
            reg |= 0x100;
        }
        if (!(current & OS_INTRMASK_PI_DEBUG)) {
            reg |= 0x1000;
        }
        if (!(current & OS_INTRMASK_PI_PE_TOKEN)) {
            reg |= 0x200;
        }
        if (!(current & OS_INTRMASK_PI_PE_FINISH)) {
            reg |= 0x400;
        }
        if (!(current & OS_INTRMASK_PI_HSP)) {
            reg |= 0x2000;
        }
        __PIRegs[1] = reg;
        mask &= ~OS_INTRMASK_PI;
        break;
    default:
        break;
    }
    return mask;
}

OSInterruptMask __OSMaskInterrupts(OSInterruptMask global)
{
    bool enabled = OSDisableInterrupts();
    OSInterruptMask prev = *(OSInterruptMask*) OSPhysicalToCached(0xC4);
    OSInterruptMask local = *(OSInterruptMask*) OSPhysicalToCached(0xC8);
    OSInterruptMask mask = ~(prev | local) & global;
    global |= prev;
    *(OSInterruptMask*) OSPhysicalToCached(0xC4) = global;
    while (mask) {
        mask = SetInterruptMask(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

OSInterruptMask __OSUnmaskInterrupts(OSInterruptMask global)
{
    bool enabled = OSDisableInterrupts();
    OSInterruptMask prev = *(OSInterruptMask*) OSPhysicalToCached(0xC4);
    OSInterruptMask local = *(OSInterruptMask*) OSPhysicalToCached(0xC8);
    OSInterruptMask mask = (prev | local) & global;
    global = prev & ~global;
    *(OSInterruptMask*) OSPhysicalToCached(0xC4) = global;
    while (mask) {
        mask = SetInterruptMask(mask, global | local);
    }
    OSRestoreInterrupts(enabled);
    return prev;
}

void __OSDispatchInterrupt(__OSException exception, OSContext* context)
{
    u32 intsr;
    u32 reg;
    OSInterruptMask cause;
    OSInterruptMask unmasked;
    OSInterruptMask* prio;
    __OSInterrupt interrupt;
    __OSInterruptHandler handler;
    intsr = __PIRegs[0];
    intsr &= ~0x00010000;

    if (intsr == 0 || (intsr & __PIRegs[1]) == 0) {
        OSLoadContext(context);
    }

    cause = 0;

    if (intsr & 0x00000080) {
        reg = __MEMRegs[15];
        if (reg & 0x1) {
            cause |= OS_INTRMASK_MEM_0;
        }
        if (reg & 0x2) {
            cause |= OS_INTRMASK_MEM_1;
        }
        if (reg & 0x4) {
            cause |= OS_INTRMASK_MEM_2;
        }
        if (reg & 0x8) {
            cause |= OS_INTRMASK_MEM_3;
        }
        if (reg & 0x10) {
            cause |= OS_INTRMASK_MEM_ADDRESS;
        }
    }

    if (intsr & 0x00000040) {
        reg = __DSPRegs[5];
        if (reg & 0x8) {
            cause |= OS_INTRMASK_DSP_AI;
        }
        if (reg & 0x20) {
            cause |= OS_INTRMASK_DSP_ARAM;
        }
        if (reg & 0x80) {
            cause |= OS_INTRMASK_DSP_DSP;
        }
    }

    if (intsr & 0x00000020) {
        reg = __AIRegs[0];
        if (reg & 0x8) {
            cause |= OS_INTRMASK_AI_AI;
        }
    }

    if (intsr & 0x00000010) {
        reg = __EXIRegs[0][0];
        if (reg & 0x2) {
            cause |= OS_INTRMASK_EXI_0_EXI;
        }
        if (reg & 0x8) {
            cause |= OS_INTRMASK_EXI_0_TC;
        }
        if (reg & 0x800) {
            cause |= OS_INTRMASK_EXI_0_EXT;
        }
        reg = __EXIRegs[1][0];
        if (reg & 0x2) {
            cause |= OS_INTRMASK_EXI_1_EXI;
        }
        if (reg & 0x8) {
            cause |= OS_INTRMASK_EXI_1_TC;
        }
        if (reg & 0x800) {
            cause |= OS_INTRMASK_EXI_1_EXT;
        }
        reg = __EXIRegs[2][0];
        if (reg & 0x2) {
            cause |= OS_INTRMASK_EXI_2_EXI;
        }
        if (reg & 0x8) {
            cause |= OS_INTRMASK_EXI_2_TC;
        }
    }

    if (intsr & 0x00002000) {
        cause |= OS_INTRMASK_PI_HSP;
    }
    if (intsr & 0x00001000) {
        cause |= OS_INTRMASK_PI_DEBUG;
    }
    if (intsr & 0x00000400) {
        cause |= OS_INTRMASK_PI_PE_FINISH;
    }
    if (intsr & 0x00000200) {
        cause |= OS_INTRMASK_PI_PE_TOKEN;
    }
    if (intsr & 0x00000100) {
        cause |= OS_INTRMASK_PI_VI;
    }
    if (intsr & 0x00000008) {
        cause |= OS_INTRMASK_PI_SI;
    }
    if (intsr & 0x00000004) {
        cause |= OS_INTRMASK_PI_DI;
    }
    if (intsr & 0x00000002) {
        cause |= OS_INTRMASK_PI_RSW;
    }
    if (intsr & 0x00000800) {
        cause |= OS_INTRMASK_PI_CP;
    }
    if (intsr & 0x00000001) {
        cause |= OS_INTRMASK_PI_ERROR;
    }

    unmasked = cause & ~(*(OSInterruptMask*) OSPhysicalToCached(0x00C4) |
                         *(OSInterruptMask*) OSPhysicalToCached(0x00C8));
    if (unmasked) {
        for (prio = InterruptPrioTable;; ++prio) {
            if (unmasked & *prio) {
                interrupt = (__OSInterrupt) __cntlzw(unmasked & *prio);
                break;
            }
        }

        handler = __OSGetInterruptHandler(interrupt);
        if (handler) {
            if (OS_INTR_MEM_ADDRESS < interrupt) {
                __OSLastInterrupt = interrupt;
                __OSLastInterruptTime = OSGetTime();
                __OSLastInterruptSrr0 = context->srr0;
            }

            OSDisableScheduler();
            handler(interrupt, context);
            OSEnableScheduler();
            __OSReschedule();
            OSLoadContext(context);
        }
    }

    OSLoadContext(context);
}

#ifdef MWERKS_GEKKO
static asm void ExternalInterruptHandler(register __OSException exception,
                                         register OSContext* context)
{
#pragma unused(exception)
    // clang-format off
  nofralloc
  OS_EXCEPTION_SAVE_GPRS(context)
  b __OSDispatchInterrupt
    // clang-format on
}
#else
static void ExternalInterruptHandler(register __OSException exception,
                                     register OSContext* context)
{
    NOT_IMPLEMENTED;
}
#endif
