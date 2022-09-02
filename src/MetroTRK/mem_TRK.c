#include <MetroTRK/mem_TRK.h>

void* TRK_memcpy(void* dst, const void* src, unsigned long n)
{
    const unsigned char* s = (const unsigned char*)src - 1;
    unsigned char* d = (unsigned char*)dst - 1;

    n++;
    while (--n != 0)
        *++d = *++s;
    return dst;
}
