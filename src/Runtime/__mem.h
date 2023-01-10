#ifndef ___mem_
#define ___mem_

#include <Runtime/platform.h>

#ifdef MWERKS_GEKKO
__declspec(section ".init")
#endif
    void* memset(void* dst, int val, unsigned long n);

#ifdef MWERKS_GEKKO
__declspec(section ".init")
#endif
    void __fill_mem(void* dst, int val, unsigned long n);

#ifdef MWERKS_GEKKO
__declspec(section ".init")
#endif
    void* memcpy(void* dst, const void* src, unsigned long n);

#endif
