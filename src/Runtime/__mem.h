#ifndef ___mem_
#define ___mem_

__declspec(section ".init") void* memset(void* dst, int val, unsigned long n);
__declspec(section ".init") void __fill_mem(void* dst, int val, unsigned long n);
__declspec(section ".init") void* memcpy(void* dst, const void* src, unsigned long n);

#endif
