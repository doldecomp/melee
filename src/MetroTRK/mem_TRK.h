#ifndef __MEM_TRK_H__
#define __MEM_TRK_H__

#ifndef M2CTX
__declspec(section ".init")
#endif
    void *TRK_memcpy(void *dst, const void *src, unsigned long n);

#ifndef M2CTX
__declspec(section ".init")
#endif
    void *TRK_memset(void *dst, int val, unsigned long n);

#endif
