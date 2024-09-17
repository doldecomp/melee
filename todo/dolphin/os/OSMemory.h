#ifndef __DOLPHIN_OSMEMORY_H_
#define __DOLPHIN_OSMEMORY_H_

#include <platform.h>

extern volatile u16 __MEMRegs[64] AT_ADDRESS(0xCC004000);

u32 OSGetPhysicalMemSize(void);
u32 OSGetConsoleSimulatedMemSize(void);
void Config48MB(void);
void RealMode(Event);
void __OSInitMemoryProtection(void);
void Config24MB(void);

#endif
