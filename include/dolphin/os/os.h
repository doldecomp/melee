#ifndef _OS_H__
#define _OS_H_

#include <dolphin/os/OSAlloc.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>

void OSReport(char *, ...);
void OSPanic(char *file, int line, char *msg, ...);

#define OSRoundUp32B(x)   (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

#endif
