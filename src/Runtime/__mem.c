#include <string.h>

#include "platform.h"

SECTION_INIT void* memcpy(void* dst, const void* src, size_t n)
{
    const u8* s = src;
    u8* d = dst;

    if ((uintptr_t) src >= (uintptr_t) dst) {
        s--;
        d--;
        n++;
        while (--n != 0) {
            *++d = *++s;
        }
    } else {
        s += n;
        d += n;
        n++;
        while (--n != 0) {
            *--d = *--s;
        }
    }
    return dst;
}

SECTION_INIT static void __fill_mem(void* dst, int val, size_t n)
{
    u8* cp = dst;
    u32 v = (u8) val;
    size_t i;
    u32* wp;

    cp--;

    if (n >= 32) {
        i = ~(uintptr_t) cp & 3;

        if (i) {
            n -= i;

            do {
                *++cp = v;
            } while (--i);
        }

        if (v) {
            v |= v << 24 | v << 16 | v << 8;
        }

        wp = (u32*) (cp + 1) - 1;

        i = n >> 5;

        if (i) {
            do {
                int j;
                for (j = 0; j < 8; j++) {
                    *++wp = v;
                }
            } while (--i);
        }

        i = (n & 31) >> 2;

        if (i) {
            do {
                *++wp = v;
            } while (--i);
        }

        cp = (u8*) (wp + 1) - 1;
        n &= 3;
    }

    if (n) {
        do {
            *++cp = v;
        } while (--n);
    }
}

SECTION_INIT void* memset(void* dst, int val, size_t n)
{
    __fill_mem(dst, val, n);

    return dst;
}
