#include <platform.h>

#include <__mem.h>
#include <dolphin/ar/ar.h>
#include <dolphin/dsp/dsp.h>
#include <dolphin/os.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>
#include <dolphin/os/OSTime.h>

Event __AR_Callback;
u32 __AR_Size;
u32 __AR_StackPointer;
u32 __AR_FreeBlocks;
u32* __AR_BlockLength;
volatile bool __AR_init_flag;

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

    if (length != NULL) {
        *length = *__AR_BlockLength;
    }

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

    if (__AR_Callback != NULL) {
        __AR_Callback();
    }

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

static void __ARWaitForDMA(void)
{
    while (__DSPRegs[5] & 0x200)
        ;
}

static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
    // Main mem address
    __DSPRegs[DSP_ARAM_DMA_MM_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff) |
               (u16) (mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0) |
               (u16) (mmem_addr & 0xffff));

    // ARAM address
    __DSPRegs[DSP_ARAM_DMA_ARAM_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff) |
               (u16) (aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0) |
               (u16) (aram_addr & 0xffff));

    // DMA buffer size
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] =
        (u16) (__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff) |
               (u16) (length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0) |
               (u16) (length & 0xffff));

    __ARWaitForDMA();
}

static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length)
{
    // Main mem address
    __DSPRegs[DSP_ARAM_DMA_MM_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff) |
               (u16) (mmem_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_MM_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0) |
               (u16) (mmem_addr & 0xffff));

    // ARAM address
    __DSPRegs[DSP_ARAM_DMA_ARAM_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff) |
               (u16) (aram_addr >> 16));
    __DSPRegs[DSP_ARAM_DMA_ARAM_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0) |
               (u16) (aram_addr & 0xffff));

    // DMA buffer size
    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] =
        (u16) (__DSPRegs[DSP_ARAM_DMA_SIZE_HI] | 0x8000);

    __DSPRegs[DSP_ARAM_DMA_SIZE_HI] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff) |
               (u16) (length >> 16));
    __DSPRegs[DSP_ARAM_DMA_SIZE_LO] =
        (u16) ((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0) |
               (u16) (length & 0xffff));

    __ARWaitForDMA();
}

static void __ARChecksize(void)
{
    u8 test_data_pad[63];
    u8 dummy_data_pad[63];
    u8 buffer_pad[63];
    u32* test_data;
    u32* dummy_data;
    u32* buffer;
    u16 ARAM_mode;
    u32 ARAM_size;
    u32 i;

    ARAM_mode = 0;
    ARAM_size = 0;

    test_data = (void*) (((u32) &test_data_pad + 0x1F) & 0xFFFFFFE0);
    dummy_data = (void*) (((u32) &dummy_data_pad + 0x1F) & 0xFFFFFFE0);
    buffer = (void*) (((u32) &buffer_pad + 0x1F) & 0xFFFFFFE0);
    for (i = 0; i < 8; i++) {
        test_data[i] = 0xDEADBEEF;
        dummy_data[i] = 0xBAD0BAD0;
    }
    DCFlushRange(test_data, 0x20);
    DCFlushRange(dummy_data, 0x20);
    do {
    } while (!(__DSPRegs[11] & 1));
    __DSPRegs[9] = ((__DSPRegs[9] & 0xFFFFFFC0) | 4) | 0x20;
    __ARWriteDMA((u32) dummy_data, 0U, 0x20U);
    __ARWriteDMA((u32) dummy_data, 0x200000U, 0x20U);
    __ARWriteDMA((u32) dummy_data, 0x200U, 0x20U);
    __ARWriteDMA((u32) dummy_data, 0x01000000U, 0x20U);
    __ARWriteDMA((u32) dummy_data, 0x400000U, 0x20U);
    memset(buffer, 0, 0x20);
    DCFlushRange(buffer, 0x20);
    __ARWriteDMA((u32) test_data, 0U, 0x20U);
    __ARReadDMA((u32) buffer, 0U, 0x20U);
    DCInvalidateRange(buffer, 0x20);
    if (*buffer == *test_data) {
        memset(buffer, 0, 0x20);
        DCFlushRange(buffer, 0x20);
        __ARReadDMA((u32) buffer, 0x200000U, 0x20U);
        DCInvalidateRange(buffer, 0x20);
        if (*buffer == *test_data) {
            ARAM_mode = 0;
            ARAM_size = 0x200000;
        } else {
            memset(buffer, 0, 0x20);
            DCFlushRange(buffer, 0x20);
            __ARReadDMA((u32) buffer, 0x01000000U, 0x20U);
            DCInvalidateRange(buffer, 0x20);
            if (*buffer == *test_data) {
                ARAM_mode = 1;
                ARAM_size = 0x400000;
            } else {
                memset(buffer, 0, 0x20);
                DCFlushRange(buffer, 0x20);
                __ARReadDMA((u32) buffer, 0x200U, 0x20U);
                DCInvalidateRange(buffer, 0x20);
                if (*buffer == *test_data) {
                    ARAM_mode = 2;
                    ARAM_size = 0x800000;
                } else {
                    memset(buffer, 0, 0x20);
                    DCFlushRange(buffer, 0x20);
                    __ARReadDMA((u32) buffer, 0x400000U, 0x20U);
                    DCInvalidateRange(buffer, 0x20);
                    if (*buffer == *test_data) {
                        ARAM_mode = 3;
                        ARAM_size = 0x01000000;
                    } else {
                        ARAM_mode = 4;
                        ARAM_size = 0x02000000;
                    }
                }
            }
        }
    }
    __DSPRegs[9] = (u16) ((__DSPRegs[9] & 0xFFFFFFC0) | 0x20) | ARAM_mode;
    __ARWriteDMA((u32) dummy_data, ARAM_size, 0x20U);
    __ARWriteDMA((u32) dummy_data, ARAM_size + 0x200000, 0x20U);
    __ARWriteDMA((u32) dummy_data, ARAM_size + 0x01000000, 0x20U);
    __ARWriteDMA((u32) dummy_data, ARAM_size + 0x200, 0x20U);
    __ARWriteDMA((u32) dummy_data, ARAM_size + 0x400000, 0x20U);
    memset(buffer, 0, 0x20);
    DCFlushRange(buffer, 0x20);
    __ARWriteDMA((u32) test_data, ARAM_size, 0x20U);
    __ARReadDMA((u32) buffer, ARAM_size, 0x20U);
    DCInvalidateRange(buffer, 0x20);
    if (*buffer == *test_data) {
        memset(buffer, 0, 0x20);
        DCFlushRange(buffer, 0x20);
        __ARReadDMA((u32) buffer, ARAM_size + 0x200000, 0x20U);
        DCInvalidateRange(buffer, 0x20);
        if (*buffer == *test_data) {
            ARAM_size += 0x200000;
        } else {
            memset(buffer, 0, 0x20);
            DCFlushRange(buffer, 0x20);
            __ARReadDMA((u32) buffer, ARAM_size + 0x01000000, 0x20U);
            DCInvalidateRange(buffer, 0x20);
            if (*buffer == *test_data) {
                ARAM_mode |= 8;
                ARAM_size += 0x400000;
            } else {
                memset(buffer, 0, 0x20);
                DCFlushRange(buffer, 0x20);
                __ARReadDMA((u32) buffer, ARAM_size + 0x200, 0x20U);
                DCInvalidateRange(buffer, 0x20);
                if (*buffer == *test_data) {
                    ARAM_mode |= 0x10;
                    ARAM_size += 0x800000;
                } else {
                    memset(buffer, 0, 0x20);
                    DCFlushRange(buffer, 0x20);
                    __ARReadDMA((u32) buffer, ARAM_size + 0x400000, 0x20U);
                    DCInvalidateRange(buffer, 0x20);
                    if (*buffer == *test_data) {
                        ARAM_mode |= 0x18;
                        ARAM_size += 0x01000000;
                    } else {
                        ARAM_mode |= 0x20;
                        ARAM_size += 0x02000000;
                    }
                }
            }
        }
        __DSPRegs[9] = ((u16) (__DSPRegs[9] & 0xFFFFFFC0) | ARAM_mode);
    }
    *(u32*) OSPhysicalToUncached(0xD0) = ARAM_size;
    __AR_Size = ARAM_size;
}
