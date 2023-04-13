#include <cstring.h>
#include <mem_funcs.h>

// Widechar to multibyte string conversion,
// doesn't care about proper conversion though?
int wcstombs(void* dst, const void* src, size_t len)
{
    char c;
    uint i;

    char* cdst = (char*) dst;
    const wchar_t* wsrc = (const wchar_t*) src;

    for (i = 0; i < len; i++) {
        c = *wsrc++;
        *cdst++ = c;

        if (c == 0x00) {
            break;
        }
    }

    return i;
}

int memcmp(const void* str1, const void* str2, size_t len)
{
    const u8* s1 = ((const u8*) str1) - 1;
    const u8* s2 = ((const u8*) str2) - 1;
    len++;

    while (--len > 0) {
        if (*++s1 != *++s2) {
            if (*s1 < *s2) {
                return -1;
            } else {
                return 1;
            }
        }
    }

    return 0;
}

void* memchr(const void* str, int c, size_t len)
{
    u8 val = (u8) c;
    u8* p = ((u8*) str) - 1;
    len++;

    while (--len > 0) {
        if (*++p == val) {
            return p;
        }
    }

    return NULL;
}

void* memmove(void* dst, const void* src, size_t len)
{
    u8* csrc;
    u8* cdst;

    int reverse = (u32) src < (u32) dst;

    if (len >= 32) {
        if (((u32) dst ^ (u32) src) & 3) {
            if (!reverse) {
                __copy_longs_unaligned(dst, src, len);
            } else {
                __copy_longs_rev_unaligned(dst, src, len);
            }
        } else {
            if (!reverse) {
                __copy_longs_aligned(dst, src, len);
            } else {
                __copy_longs_rev_aligned(dst, src, len);
            }
        }

        return dst;
    } else {
        if (!reverse) {
            csrc = ((u8*) src) - 1;
            cdst = ((u8*) dst) - 1;
            len++;

            while (--len > 0) {
                *++cdst = *++csrc;
            }
        } else {
            csrc = (u8*) src + len;
            cdst = (u8*) dst + len;
            len++;

            while (--len > 0) {
                *--cdst = *--csrc;
            }
        }
    }

    return dst;
}
