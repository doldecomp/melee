#ifndef _memory_h_
#define _memory_h_

#include "Runtime/platform.h"
#include <dolphin/types.h>

void HSD_Free(any_t ptr);
void* HSD_MemAlloc(ptrdiff_t size);

#endif
