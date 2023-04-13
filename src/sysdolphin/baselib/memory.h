#ifndef _memory_h_
#define _memory_h_

#include <platform.h>

void HSD_Free(any_t ptr);
void* HSD_MemAlloc(ssize_t size);

#endif
