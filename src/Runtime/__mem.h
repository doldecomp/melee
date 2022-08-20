#ifndef ___mem_
#define ___mem_


#ifndef M2CTX
__declspec(section ".init")
#endif
    void* memset(void* dst, int val, unsigned long n);


#ifndef M2CTX
__declspec(section ".init")
#endif
    void __fill_mem(void* dst, int val, unsigned long n);


#ifndef M2CTX
__declspec(section ".init")
#endif
    void* memcpy(void* dst, const void* src, unsigned long n);


#endif
