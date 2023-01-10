#ifndef __MEM_TRK_H__
#define __MEM_TRK_H__

#include <Runtime/platform.h>

#ifdef MWERKS_GEKKO
__declspec(section ".init")
#endif
    void* TRK_memcpy(void* dst, const void* src, unsigned long n);

#ifdef MWERKS_GEKKO
__declspec(section ".init")
#endif
    void* TRK_memset(void* dst, int val, unsigned long n);

#endif
