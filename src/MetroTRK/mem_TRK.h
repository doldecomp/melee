#ifndef __MEM_TRK_H__
#define __MEM_TRK_H__

#include <platform.h>

SECTION_INIT void* TRK_memcpy(void* dst, const void* src, unsigned long n);
SECTION_INIT void* TRK_memset(void* dst, int val, unsigned long n);
void TRK_fill_mem(void* dest, int val, size_t count);

#endif
