#include <platform.h>
#include <dolphin/ar/ar.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os/os.h>

extern Event __AR_Callback;
extern u32 __AR_Size;
extern u32 __AR_StackPointer;
extern u32 __AR_FreeBlocks;
extern u32* __AR_BlockLength;
extern volatile bool __AR_init_flag;

void __ARHandler(__OSInterrupt interrupt, OSContext* context);

Event ARRegisterDMACallback(Event callback)
{
    Event oldCb = __AR_Callback;
    bool enabled = OSDisableInterrupts();
    __AR_Callback = callback;
    OSRestoreInterrupts(enabled);
    return oldCb;
}

u32 ARGetDMAStatus(void)
{
    bool enabled = OSDisableInterrupts();
    u32 val = __DSPRegs[5] & 0x0200;
    OSRestoreInterrupts(enabled);
    return val;
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length)
{
    bool enabled = OSDisableInterrupts();

    __DSPRegs[16] =
        (u16) (__DSPRegs[16] & ~0x3ff) | (u16) (mainmem_addr >> 16);
    __DSPRegs[17] =
        (u16) (__DSPRegs[17] & ~0xffe0) | (u16) (mainmem_addr & 0xffff);
    __DSPRegs[18] = (u16) (__DSPRegs[18] & ~0x3ff) | (u16) (aram_addr >> 16);
    __DSPRegs[19] =
        (u16) (__DSPRegs[19] & ~0xffe0) | (u16) (aram_addr & 0xffff);
    __DSPRegs[20] = (u16) ((__DSPRegs[20] & ~0x8000) | (type << 15));
    __DSPRegs[20] = (u16) (__DSPRegs[20] & ~0x3ff) | (u16) (length >> 16);
    __DSPRegs[21] = (u16) (__DSPRegs[21] & ~0xffe0) | (u16) (length & 0xffff);
    OSRestoreInterrupts(enabled);
}

u32 ARAlloc(u32 length)
{
    bool enabled = OSDisableInterrupts();
    u32 tmp = __AR_StackPointer;
    __AR_StackPointer += length;
    *__AR_BlockLength = length;
    __AR_BlockLength++;
    __AR_FreeBlocks--;
    OSRestoreInterrupts(enabled);

    return tmp;
}

u32 ARFree(u32* length)
{
    bool enabled = OSDisableInterrupts();

    __AR_BlockLength--;

    if (length != NULL)
        *length = *__AR_BlockLength;

    __AR_StackPointer -= *__AR_BlockLength;

    __AR_FreeBlocks++;

    OSRestoreInterrupts(enabled);

    return __AR_StackPointer;
}

bool ARCheckInit(void)
{
    return __AR_init_flag;
}

u32 ARInit(u32* stack_index_addr, u32 num_entries)
{
    bool enabled;
    u16 refresh;
    int tmp;

    if (__AR_init_flag == true) {
        return 0x4000;
    }

    enabled = OSDisableInterrupts();

    __AR_Callback = NULL;

    __OSSetInterruptHandler(OS_INTR_DSP_ARAM, __ARHandler);
    __OSUnmaskInterrupts(OS_INTRMASK_DSP_ARAM);

    __AR_StackPointer = 0x4000;
    __AR_FreeBlocks = num_entries;
    __AR_BlockLength = stack_index_addr;

    refresh = __DSPRegs[13] & 0xFF00;

    /// @todo Should be a call to one of the OS_TIMER_CLOCK macros
    tmp = 196.0F * (__OSBusClock / 202500000.0F);
    __DSPRegs[13] = (tmp & 0xFF) | refresh;

    __ARChecksize();

    __AR_init_flag = true;

    OSRestoreInterrupts(enabled);

    return __AR_StackPointer;
}

u32 ARGetBaseAddress(void)
{
    return 0x4000;
}

u32 ARGetSize(void)
{
    return __AR_Size;
}

void __ARHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext exceptionContext;

    u16 tmp = __DSPRegs[5];
    __DSPRegs[5] = (tmp & ~0x88) | 0x20;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (__AR_Callback != NULL)
        __AR_Callback();

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}
