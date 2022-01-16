#ifndef _memory_h_
#define _memory_h_

#include <global.h>

#include <dolphin/types.h>

void HSD_Free(void* ptr);
void* HSD_MemAlloc(s32 size);

#endif
