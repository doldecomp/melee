#include <__mem.h>

void* memset(void* dst, int val, unsigned long /*size_t*/ n)
{
    __fill_mem(dst, val, n);

    return (dst);
}

#ifdef __MWERKS__
#define INCREMENT_ASSIGN(ptr, type, value) (*++((type*) (ptr)) = (value))
#else
#define INCREMENT_ASSIGN(ptr, type, value)                                    \
    do {                                                                      \
        type* __INCREMENT_ASSIGN_tmp;                                         \
        (ptr) = ((type*) (ptr)) + 1;                                          \
        __INCREMENT_ASSIGN_tmp = ((type*) (ptr));                             \
        *__INCREMENT_ASSIGN_tmp = (value);                                    \
    } while (false);
#endif

void __fill_mem(void* dst, int val, unsigned long n)
{
    unsigned long v = (unsigned char) val;
    unsigned long i;

    dst = ((unsigned char*) dst) - 1;

    if (n >= 32) {
        i = (~(unsigned long) dst) & 3;

        if (i) {
            n -= i;

            do {
                INCREMENT_ASSIGN(dst, unsigned char, v);
            } while (--i);
        }

        if (v) {
            v |= v << 24 | v << 16 | v << 8;
        }

        dst = ((unsigned long*) (((unsigned char*) dst) + 1)) - 1;

        i = n >> 5;

        if (i) {
            do {
                int j;
                for (j = 0; j < 8; j++) {
                    INCREMENT_ASSIGN(dst, unsigned long, v);
                }
            } while (--i);
        }

        i = (n & 31) >> 2;

        if (i) {
            do {
                INCREMENT_ASSIGN(dst, unsigned long, v);
            } while (--i);
        }

        dst = ((unsigned char*) (((unsigned long*) dst) + 1)) - 1;
        n &= 3;
    }

    if (n) {
        do {
            INCREMENT_ASSIGN(dst, unsigned char, v);
        } while (--n);
    }

    return;
}

#undef INCREMENT_ASSIGN

void* memcpy(void* dst, const void* src, unsigned long /* size_t */ n)
{
    const unsigned char* s;
    unsigned char* d;

    if ((unsigned long) src >= (unsigned long) dst) {
        s = (const unsigned char*) src - 1;
        d = (unsigned char*) dst - 1;
        n++;
        while (--n != 0) {
            *++d = *++s;
        }
    } else {
        s = (const unsigned char*) src + n;
        d = (unsigned char*) dst + n;
        n++;
        while (--n != 0) {
            *--d = *--s;
        }
    }
    return dst;
}
