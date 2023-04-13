#ifndef ___mem_
#define ___mem_

#include <platform.h>

SECTION_INIT void* memset(void* dst, int val, unsigned long n);
SECTION_INIT void __fill_mem(void* dst, int val, unsigned long n);
SECTION_INIT void* memcpy(void* dst, const void* src, unsigned long n);

#endif
