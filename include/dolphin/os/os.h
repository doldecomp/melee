#ifndef _OS_H__
#define _OS_H_

#include <dolphin/os/OSAlloc.h>
#include <dolphin/os/OSArena.h>
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSTime.h>

#define OS_SOUND_MODE_MONO 0
#define OS_SOUND_MODE_STEREO 1

void OSReport(char*, ...);
void OSPanic(char* file, int line, char* msg, ...);

#define OSRoundUp32B(x) (((u32) (x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32) (x)) & ~(32 - 1))

#define OS_CACHED_REGION_PREFIX 0x8000
#define OS_BASE_CACHED (OS_CACHED_REGION_PREFIX << 16)
#define OSPhysicalToCached(paddr) ((void*) ((u32) (paddr) + OS_BASE_CACHED))

#endif
