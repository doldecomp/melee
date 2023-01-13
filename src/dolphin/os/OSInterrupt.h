// https://github.com/kiwi515/open_rvl/blob/605e2a99ad053441f0ebb9b322a18433f92025e2/include/OS/OSInterrupt.h

#ifndef _OS_INTERRUPT_H_
#define _OS_INTERRUPT_H_
#include <dolphin/os/OSContext.h>
#include <Runtime/platform.h>

typedef s16 __OSInterrupt;

typedef enum {
    OS_INTR_MEM_0,
    OS_INTR_MEM_1,
    OS_INTR_MEM_2,
    OS_INTR_MEM_3,
    OS_INTR_MEM_ADDRESS,
    OS_INTR_DSP_AI,
    OS_INTR_DSP_ARAM,
    OS_INTR_DSP_DSP,
    OS_INTR_AI_AI,
    OS_INTR_EXI_0_EXI,
    OS_INTR_EXI_0_TC,
    OS_INTR_EXI_0_EXT,
    OS_INTR_EXI_1_EXI,
    OS_INTR_EXI_1_TC,
    OS_INTR_EXI_1_EXT,
    OS_INTR_EXI_2_EXI,
    OS_INTR_EXI_2_TC,
    OS_INTR_PI_CP,
    OS_INTR_PI_PE_TOKEN,
    OS_INTR_PI_PE_FINISH,
    OS_INTR_PI_SI,
    OS_INTR_PI_DI,
    OS_INTR_PI_RSW,
    OS_INTR_PI_ERROR,
    OS_INTR_PI_VI,
    OS_INTR_PI_DEBUG,
    OS_INTR_PI_HSP,
    OS_INTR_PI_ACR,
    OS_INTR_28,
    OS_INTR_29,
    OS_INTR_30,
    OS_INTR_31,

    OS_INTR_MAX
} OSInterruptType;

#define OS_INTRMASK_EXI_0_EXI (0x80000000U >> OS_INTR_EXI_0_EXI)
#define OS_INTRMASK_EXI_0_TC (0x80000000U >> OS_INTR_EXI_0_TC)
#define OS_INTRMASK_EXI_0_EXT (0x80000000U >> OS_INTR_EXI_0_EXT)
#define OS_INTRMASK_EXI_1_EXI (0x80000000U >> OS_INTR_EXI_1_EXI)
#define OS_INTRMASK_EXI_1_TC (0x80000000U >> OS_INTR_EXI_1_TC)
#define OS_INTRMASK_EXI_1_EXT (0x80000000U >> OS_INTR_EXI_1_EXT)
#define OS_INTRMASK_EXI_2_EXI (0x80000000U >> OS_INTR_EXI_2_EXI)
#define OS_INTRMASK_EXI_2_TC (0x80000000U >> OS_INTR_EXI_2_TC)
#define OS_INTRMASK_PI_DEBUG (0x80000000U >> OS_INTR_PI_DEBUG)

typedef void (*OSInterruptHandler)(__OSInterrupt, OSContext*);

extern u32 __OSLastInterruptSrr0;
extern s16 __OSLastInterrupt;
extern s64 __OSLastInterruptTime;

/// @sz{4}
extern unk_t lbl_804D738C;

bool OSDisableInterrupts(void);
bool OSEnableInterrupts(void);
bool OSRestoreInterrupts(bool);

OSInterruptHandler __OSSetInterruptHandler(__OSInterrupt, OSInterruptHandler);
OSInterruptHandler __OSGetInterruptHandler(__OSInterrupt);

void __OSInterruptInit(void);

u32 __OSMaskInterrupts(u32);
u32 __OSUnmaskInterrupts(u32);

#endif
