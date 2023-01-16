#ifndef __DOLPHIN_OSMEMORY_H_
#define __DOLPHIN_OSMEMORY_H_

#include <Runtime/platform.h>

extern volatile u16 __MEMRegs[64] AT_ADDRESS(0xCC004000);

u32 OSGetPhysicalMemSize(void);
u32 OSGetConsoleSimulatedMemSize(void);

#endif
