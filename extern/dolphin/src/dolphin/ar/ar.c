#include <dolphin.h>
#include <dolphin/ar.h>
#include "fake_tgmath.h"

#include "__ar.h"

static void (* __AR_Callback)();
static u32 __AR_Size;
static u32 __AR_StackPointer;
static u32 __AR_FreeBlocks;
static u32 * __AR_BlockLength;
static int __AR_init_flag;

// functions
static void __ARHandler(short exception, struct OSContext * context);
static void __ARWaitForDMA(void);
static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length);
static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length);
static void __ARChecksize(void);

ARQCallback ARRegisterDMACallback(ARQCallback callback) {
    ARQCallback old_callback;
    int old;

    old_callback = __AR_Callback;
    old = OSDisableInterrupts();
    __AR_Callback = callback;
    OSRestoreInterrupts(old);
    return old_callback;
}

u32 ARGetDMAStatus(void) {
    int old;
    u32 val;
    
    old = OSDisableInterrupts();
    val = __DSPRegs[5] & 0x200;
    OSRestoreInterrupts(old);
    return val;
    
}

void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length) {
    int old;

    old = OSDisableInterrupts();
    ASSERTMSGLINE(0x148, !(__DSPRegs[5] & 0x200), "ARAM DMA already in progress\n");
    ASSERTMSGLINE(0x149, !(mainmem_addr & 0x1F), "AR: Main memory address is not a multiple of 32 bytes!\n");
    ASSERTMSGLINE(0x14A, !(length & 0x1F), "AR: DMA transfer length is not a multiple of 32 bytes!\n");
    __DSPRegs[16] = (__DSPRegs[16] & 0xFFFFFC00 | (mainmem_addr >> 0x10)); 
    __DSPRegs[17] = (__DSPRegs[17] & 0xFFFF001F | ((u16)mainmem_addr));
    __DSPRegs[18] = (__DSPRegs[18] & 0xFFFFFC00 | (aram_addr >> 0x10));
    __DSPRegs[19] = (__DSPRegs[19] & 0xFFFF001F | ((u16)aram_addr));
    __DSPRegs[20] = __DSPRegs[20] & ~0x8000 | ((type << 0xF) & ~0x7FFF);
    __DSPRegs[20] = (__DSPRegs[20] & 0xFFFFFC00) | (length >> 0x10);
    __DSPRegs[21] = (__DSPRegs[21] & 0xFFFF001F) | (length & 0x0000FFFF);
    OSRestoreInterrupts(old);
}

u32 ARAlloc(u32 length) {
    u32 tmp;
    int old;

    old = OSDisableInterrupts();
    ASSERTMSGLINE(0x17E, !(length & 0x1F), "ARAlloc(): length is not multiple of 32bytes!");
    ASSERTMSGLINE(0x182, length <= (__AR_Size - __AR_StackPointer), "ARAlloc(): Out of ARAM!");
    ASSERTMSGLINE(0x183, __AR_FreeBlocks, "ARAlloc(): No more free blocks!");
    tmp = __AR_StackPointer;
    __AR_StackPointer += length;
    *__AR_BlockLength = length;
    __AR_BlockLength += 1;
    __AR_FreeBlocks -= 1;
    OSRestoreInterrupts(old);
    return tmp;
}

u32 ARFree(u32 * length) {
    int old;

    old = OSDisableInterrupts();
    __AR_BlockLength -= 1;
    if (length) {
        *length = *__AR_BlockLength;
    }
    __AR_StackPointer -= *__AR_BlockLength;
    __AR_FreeBlocks += 1;
    OSRestoreInterrupts(old);
    return __AR_StackPointer;
}

int ARCheckInit(void) {
    return __AR_init_flag;
}

u32 ARInit(u32 * stack_index_addr, u32 num_entries) {
    int old;
    u16 refresh;

    if (__AR_init_flag == 1) {
        return 0x4000;
    }
    old = OSDisableInterrupts();
    __AR_Callback = NULL;
    __OSSetInterruptHandler(6, __ARHandler);
    __OSUnmaskInterrupts(0x02000000);
    __AR_StackPointer = 0x4000;
    __AR_FreeBlocks = num_entries;
    __AR_BlockLength = stack_index_addr;
    refresh = 196.0f * (OS_BUS_CLOCK / 202500000.0f);
    ASSERTMSGLINE(0x227, (refresh <= 196.0f), "ARInit(): ILLEGAL SDRAM REFRESH VALUE\n");
    __DSPRegs[13] = (__DSPRegs[13] & 0xFF00) | ((u8)refresh & ~0xFF00);
    __ARChecksize();
    __AR_init_flag = 1;
    OSRestoreInterrupts(old);
#ifdef DEBUG
    OSReport("ARInit(): ARAM size        : %d bytes\n", ARGetSize());
    OSReport("ARInit(): USER Base address: 0x%08X\n", __AR_StackPointer);
    OSReport("ARInit(): Refresh          : 0x%04X\n", refresh);
#endif
    return __AR_StackPointer;
}

void ARReset(void) {
    __AR_init_flag = 0;
}

void ARSetSize(void) {
#ifdef DEBUG
    OSReport("ARSetSize(): I don't do anything anymore!\n");
#endif
}

u32 ARGetBaseAddress(void) {
    return 0x4000;
}

u32 ARGetSize(void) {
    return __AR_Size;
}

static void __ARHandler(short exception, struct OSContext * context) {
    struct OSContext exceptionContext;
    u16 tmp;

    tmp = __DSPRegs[5];
    tmp = (tmp & ~0x88) | 0x20;
    __DSPRegs[5] = (tmp);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (__AR_Callback) {
        __AR_Callback();
    }
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

static void __ARWaitForDMA(void) {
    while (__DSPRegs[5] & 0x200) ;
}

static void __ARWriteDMA(u32 mmem_addr, u32 aram_addr, u32 length) {
	// Main mem address
	__DSPRegs[DSP_ARAM_DMA_MM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff) | (u16)(mmem_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_MM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

	// ARAM address
	__DSPRegs[DSP_ARAM_DMA_ARAM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff) | (u16)(aram_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_ARAM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0) | (u16)(aram_addr & 0xffff));

	// DMA buffer size
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x8000);

	__DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff) | (u16)(length >> 16));
	__DSPRegs[DSP_ARAM_DMA_SIZE_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0) | (u16)(length & 0xffff));

	__ARWaitForDMA();
}

static void __ARReadDMA(u32 mmem_addr, u32 aram_addr, u32 length) {
	// Main mem address
	__DSPRegs[DSP_ARAM_DMA_MM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_HI] & ~0x03ff) | (u16)(mmem_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_MM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_MM_LO] & ~0xffe0) | (u16)(mmem_addr & 0xffff));

	// ARAM address
	__DSPRegs[DSP_ARAM_DMA_ARAM_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_HI] & ~0x03ff) | (u16)(aram_addr >> 16));
	__DSPRegs[DSP_ARAM_DMA_ARAM_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_ARAM_LO] & ~0xffe0) | (u16)(aram_addr & 0xffff));

	// DMA buffer size
	__DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)(__DSPRegs[DSP_ARAM_DMA_SIZE_HI] | 0x8000);

	__DSPRegs[DSP_ARAM_DMA_SIZE_HI] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_HI] & ~0x03ff) | (u16)(length >> 16));
	__DSPRegs[DSP_ARAM_DMA_SIZE_LO] = (u16)((__DSPRegs[DSP_ARAM_DMA_SIZE_LO] & ~0xffe0) | (u16)(length & 0xffff));

	__ARWaitForDMA();
}

static void __ARChecksize(void) {
    u8 test_data_pad[63];
    u8 dummy_data_pad[63];
    u8 buffer_pad[63];
    u32 * test_data;
    u32 * dummy_data;
    u32 * buffer;
    u16 ARAM_mode;
    u32 ARAM_size;
    u32 i;

    ARAM_mode = 0;
    ARAM_size = 0;
#ifdef DEBUG
    OSReport("__ARChecksize(): Initializing for RevB+ SDRAM controller...\n");
#endif
    test_data = (void*)(((u32)&test_data_pad + 0x1F) & 0xFFFFFFE0);
    dummy_data = (void*)(((u32)&dummy_data_pad + 0x1F) & 0xFFFFFFE0);
    buffer = (void*)(((u32)&buffer_pad + 0x1F) & 0xFFFFFFE0);
    for(i = 0; i < 8; i++) {
        test_data[i] = 0xDEADBEEF;
        dummy_data[i] = 0xBAD0BAD0;
    }
    DCFlushRange(test_data, 0x20);
    DCFlushRange(dummy_data, 0x20);
    do {} while(!(__DSPRegs[11] & 1));
    __DSPRegs[9] = ((__DSPRegs[9] & 0xFFFFFFC0) | 4) | 0x20;
    __ARWriteDMA((u32)dummy_data, 0U, 0x20U);
    __ARWriteDMA((u32)dummy_data, 0x200000U, 0x20U);
    __ARWriteDMA((u32)dummy_data, 0x200U, 0x20U);
    __ARWriteDMA((u32)dummy_data, 0x01000000U, 0x20U);
    __ARWriteDMA((u32)dummy_data, 0x400000U, 0x20U);
    memset(buffer, 0, 0x20);
    DCFlushRange(buffer, 0x20);
    __ARWriteDMA((u32)test_data, 0U, 0x20U);
    __ARReadDMA((u32)buffer, 0U, 0x20U);
    DCInvalidateRange(buffer, 0x20);
    if (*buffer != *test_data) {
        ASSERTMSGLINE(0x3B2, 0, "__ARChecksize(): Internal ARAM not present!");
    } else {
        memset(buffer, 0, 0x20);
        DCFlushRange(buffer, 0x20);
        __ARReadDMA((u32)buffer, 0x200000U, 0x20U);
        DCInvalidateRange(buffer, 0x20);
        if (*buffer == *test_data) {
            ARAM_mode = 0;
            ARAM_size = 0x200000;
        } else {
            memset(buffer, 0, 0x20);
            DCFlushRange(buffer, 0x20);
            __ARReadDMA((u32)buffer, 0x01000000U, 0x20U);
            DCInvalidateRange(buffer, 0x20);        
            if (*buffer == *test_data) {
                ARAM_mode = 1;
                ARAM_size = 0x400000;
            } else {
                memset(buffer, 0, 0x20);
                DCFlushRange(buffer, 0x20);
                __ARReadDMA((u32)buffer, 0x200U, 0x20U);
                DCInvalidateRange(buffer, 0x20);
                if (*buffer == *test_data) {
                    ARAM_mode = 2;
                    ARAM_size = 0x800000;
                } else {
                    memset(buffer, 0, 0x20);
                    DCFlushRange(buffer, 0x20);
                    __ARReadDMA((u32)buffer, 0x400000U, 0x20U);
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
    __DSPRegs[9] = (u16)((__DSPRegs[9] & 0xFFFFFFC0) | 0x20) | ARAM_mode;
    __ARWriteDMA((u32)dummy_data, ARAM_size, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x01000000, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x200, 0x20U);
    __ARWriteDMA((u32)dummy_data, ARAM_size + 0x400000, 0x20U);
    memset(buffer, 0, 0x20);
    DCFlushRange(buffer, 0x20);
    __ARWriteDMA((u32)test_data, ARAM_size, 0x20U);
    __ARReadDMA((u32)buffer, ARAM_size, 0x20U);
    DCInvalidateRange(buffer, 0x20);
    if (*buffer == *test_data) {
        memset(buffer, 0, 0x20);
        DCFlushRange(buffer, 0x20);
        __ARReadDMA((u32)buffer, ARAM_size + 0x200000, 0x20U);
        DCInvalidateRange(buffer, 0x20);
        if (*buffer == *test_data) {
            ARAM_size += 0x200000;
        } else {
            memset(buffer, 0, 0x20);
            DCFlushRange(buffer, 0x20);
            __ARReadDMA((u32)buffer, ARAM_size + 0x01000000, 0x20U);
            DCInvalidateRange(buffer, 0x20);
            if (*buffer == *test_data) {
                ARAM_mode |= 8;
                ARAM_size += 0x400000;
            } else {
                memset(buffer, 0, 0x20);
                DCFlushRange(buffer, 0x20);
                __ARReadDMA((u32)buffer, ARAM_size + 0x200, 0x20U);
                DCInvalidateRange(buffer, 0x20);       
                if (*buffer == *test_data) {
                    ARAM_mode |= 0x10;
                    ARAM_size += 0x800000;
                } else {
                    memset(buffer, 0, 0x20);
                    DCFlushRange(buffer, 0x20);
                    __ARReadDMA((u32)buffer, ARAM_size + 0x400000, 0x20U);
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
#ifdef DEBUG
        OSReport("__ARChecksize(): ARAM Expansion present\n");
#endif
        __DSPRegs[9] = ((u16)(__DSPRegs[9] & 0xFFFFFFC0) | ARAM_mode);
    }
    *(u32*)OSPhysicalToUncached(0xD0) = ARAM_size;
    __AR_Size = ARAM_size;
}
