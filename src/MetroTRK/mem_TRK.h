#ifndef __MEM_TRK_H__
#define __MEM_TRK_H__

__declspec(section ".init") void *TRK_memcpy(void *dst, const void *src, unsigned long n);
__declspec(section ".init") void *TRK_memset(void *dst, int val, unsigned long n);

#endif
