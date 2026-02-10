#include "hsd_3B2E.h"

#include "hsd_3B2B.h"

static s32 lbl_80430BD0[13] = {
    0x26, 0xFF, 0xE8, 0xEF, 0x42, 0xD6, 0x01,
    0x54, 0x14, 0xA3, 0x80, 0xFD, 0x6E,
};

#pragma dont_inline on

static u8 fn_803B2E04(u8 prev, s32 cur)
{
    u32 mod7;
    u8 val;

    mod7 = prev % 7;
    val = prev ^ cur ^ lbl_80430BD0[prev % 13];

    if (mod7 > 6) {
        return val;
    }

    switch (mod7) {
    case 0:
        return (u8) ((val & 1) | ((val << 3) & 0x10) | ((val >> 1U) & 2) |
                     ((val << 2) & 0x20) | ((val >> 2U) & 4) |
                     ((val << 1) & 0x40) | ((val >> 3U) & 8) | (val & 0x80));
    case 1:
        return (u8) (((val << 3) & 8) | ((val >> 1U) & 1) | (val & 4) |
                     ((val << 3) & 0x40) | ((val << 1) & 0x20) |
                     ((val >> 1U) & 0x10) | ((val << 1) & 0x80) |
                     ((val >> 6U) & 2));
    case 2:
        return (u8) (((val << 6) & 0x40) | ((val << 4) & 0x20) |
                     ((val >> 2U) & 1) | ((val >> 2U) & 2) |
                     ((val >> 1U) & 8) | ((val << 2) & 0x80) |
                     ((val >> 4U) & 4) | ((val >> 3U) & 0x10));
    case 3:
        return (u8) (((val << 1) & 2) | ((val << 2) & 8) |
                     ((val << 5) & 0x80) | ((val << 1) & 0x10) |
                     ((val >> 4U) & 1) | ((val >> 3U) & 4) |
                     ((val >> 1U) & 0x20) | ((val >> 1U) & 0x40));
    case 4:
        return (u8) (((val << 7) & 0x80) | ((val << 1) & 4) |
                     ((val << 3) & 0x20) | ((val >> 3U) & 1) |
                     ((val << 2) & 0x40) | ((val >> 4U) & 2) |
                     ((val >> 2U) & 0x10) | ((val >> 4U) & 8));
    case 5:
        return (u8) (((val & 1) << 5) | ((val << 5) & 0x40) |
                     ((val << 2) & 0x10) | (val & 8) | ((val << 3) & 0x80) |
                     ((val >> 5U) & 1) | ((val >> 5U) & 2) |
                     ((val >> 5U) & 4));
    case 6:
        return (u8) (((val << 2) & 4) | (val & 2) | ((val & 4) << 4) |
                     ((val << 4) & 0x80) | (val & 0x10) | ((val >> 2U) & 8) |
                     ((val >> 6U) & 1) | ((val >> 2U) & 0x20));
    }
    return val;
}

#pragma dont_inline reset

int hsd_803B2FA0(u8* data, int len)
{
    u8* ptr;
    int i;

    if (data == NULL) {
        return -1;
    }

    hsd_803B2B20(data + 16, len - 16, data);

    for (i = 16; i < len; i++) {
        ptr = data + i;
        *ptr = fn_803B2E04(ptr[-1], *ptr);
    }

    return 0;
}

#pragma dont_inline on

static u8 fn_803B302C(u8 prev, u8 cur)
{
    u32 mod7;

    mod7 = prev % 7;

    switch (mod7) {
    case 0:
        cur = (u8) ((cur & 1) | ((cur << 1) & 4) | ((cur << 2) & 0x10) |
                    ((cur << 3) & 0x40) | ((cur >> 3U) & 2) |
                    ((cur >> 2U) & 8) | ((cur >> 1U) & 0x20) | (cur & 0x80));
        break;
    case 1:
        cur = (u8) (((cur << 1) & 2) | ((cur << 6) & 0x80) | (cur & 4) |
                    ((cur >> 3U) & 1) | ((cur << 1) & 0x20) |
                    ((cur >> 1U) & 0x10) | ((cur >> 3U) & 8) |
                    ((cur >> 1U) & 0x40));
        break;
    case 2:
        cur = (u8) (((cur & 1) << 2) | ((cur << 2) & 8) | ((cur << 4) & 0x40) |
                    ((cur << 1) & 0x10) | ((cur << 3) & 0x80) |
                    ((cur >> 4U) & 2) | ((cur >> 6U) & 1) |
                    ((cur >> 2U) & 0x20));
        break;
    case 3:
        cur = (u8) (((cur << 4) & 0x10) | ((cur >> 1U) & 1) |
                    ((cur << 3) & 0x20) | ((cur >> 2U) & 2) |
                    ((cur >> 1U) & 8) | ((cur << 1) & 0x40) |
                    ((cur << 1) & 0x80) | ((cur >> 5U) & 4));
        break;
    case 4:
        cur = (u8) (((cur << 3) & 8) | ((cur << 4) & 0x20) |
                    ((cur >> 1U) & 2) | ((cur << 4) & 0x80) |
                    ((cur << 2) & 0x40) | ((cur >> 3U) & 4) |
                    ((cur >> 2U) & 0x10) | ((cur >> 7U) & 1));
        break;
    case 5:
        cur = (u8) (((cur & 1) << 5) | ((cur << 5) & 0x40) | ((cur & 4) << 5) |
                    (cur & 8) | ((cur >> 2U) & 4) | ((cur >> 5U) & 1) |
                    ((cur >> 5U) & 2) | ((cur >> 3U) & 0x10));
        break;
    case 6:
        cur = (u8) (((cur << 6) & 0x40) | (cur & 2) | ((cur >> 2U) & 1) |
                    ((cur << 2) & 0x20) | (cur & 0x10) | ((cur << 2) & 0x80) |
                    ((cur >> 4U) & 4) | ((cur >> 4U) & 8));
        break;
    }

    return cur ^ lbl_80430BD0[prev % 13] ^ prev;
}

#pragma dont_inline reset

int hsd_803B31CC(u8* data, int len)
{
    u8* ptr;
    int i;
    u8 cur;
    u8 check[16];
    u8* p;
    u8* q;
    int j;
    int k;
    u8 prev;

    if (data == NULL) {
        return -1;
    }

    prev = data[15];

    for (i = 16; i < len; i++) {
        ptr = data + i;
        cur = *ptr;
        *ptr = fn_803B302C(prev, *ptr);
        prev = cur;
    }

    hsd_803B2B20(data + 16, len - 16, check);

    p = data;
    q = check;
    k = 0;

    for (j = 2; j != 0; j--) {
        if (*q != *p) {
            return -1;
        }
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        k++;
        if (*++q != *++p) {
            return -1;
        }
        q++;
        k++;
        p++;
    }

    return 0;
}
