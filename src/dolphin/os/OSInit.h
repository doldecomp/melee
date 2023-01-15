/** @file
 * @todo Should be called @c OS.h.
 */
#ifndef DOLPHIN_OS_OS_H
#define DOLPHIN_OS_OS_H

#include <dolphin/os/OSContext.h>
#include <Runtime/platform.h>

typedef u8 __OSException;
typedef void (*__OSExceptionHandler)(__OSException exception,
                                     struct OSContext* context);

__OSExceptionHandler __OSGetExceptionHandler(__OSException);
void __OSSetExceptionHandler(s32, __OSExceptionHandler);
u32 OSGetConsoleType(void);
void OSInit(void);
void __OSPSInit(void);

#endif
