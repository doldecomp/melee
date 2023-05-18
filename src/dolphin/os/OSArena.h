#ifndef __DOLPHIN_OSARENA_H_
#define __DOLPHIN_OSARENA_H_

#include <platform.h>

void* OSGetArenaHi(void);
void* OSGetArenaLo(void);
void OSSetArenaHi(void* addr);
void OSSetArenaLo(void* addr);
void* OSAllocFromArenaLo(u32 size, u32 align);
void* OSAllocFromArenaHi(u32 size, u32 align);

#endif
