#ifndef __DOLPHIN_DSP_H_
#define __DOLPHIN_DSP_H_

#include <global.h>

#include <dolphin/types.h>

#define HW_REG(reg, type) *(volatile type *)(uintptr_t)(reg)
volatile u16 __DSPRegs[] : 0xCC005000;

u32 DSPCheckMailToDSP(void);
u32 DSPCheckMailFromDSP(void);
u32 DSPReadMailFromDSP(void);
void DSPSendMailToDSP(u32 mail);
void DSPInit(void);
BOOL DSPCheckInit(void);

#endif
