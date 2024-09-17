/** @file
 * @todo Should be called @c OS.h.
 */
#ifndef DOLPHIN_OS_OS_H
#define DOLPHIN_OS_OS_H

#include <platform.h>

#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSException.h>

extern vu32 __PIRegs[12] AT_ADDRESS(0xCC003000);
extern vu32 __DIRegs[16] AT_ADDRESS(0xCC006000);

__OSExceptionHandler __OSGetExceptionHandler(u8);
__OSExceptionHandler __OSSetExceptionHandler(u8, __OSExceptionHandler);
u32 OSGetConsoleType(void);
void OSInit(void);
void __OSPSInit(void);
void OSExceptionInit(void);
void __OSDBIntegrator(void);
void __OSDBJump(void);
void __DBVECTOR(void);
void __OSEVSetNumber(void);
void __OSEVEnd(void);
void OSExceptionVector(void);
void OSDefaultExceptionHandler(void);

void ClearArena(void);
u32 __OSGetDIConfig(void);

#endif
