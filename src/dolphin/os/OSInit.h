/** @file
 * @todo Should be called @c OS.h.
 */
#ifndef DOLPHIN_OS_OS_H
#define DOLPHIN_OS_OS_H

#include <dolphin/os/OSContext.h>
#include <Runtime/platform.h>

typedef enum OSException {
    OS_EXCEPTION_FLOATING_POINT = 7,
    OS_EXCEPTION_COUNT = 15,
} OSException;

typedef void (*__OSExceptionHandler)(OSException exception,
                                     struct OSContext* context);

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

#endif
