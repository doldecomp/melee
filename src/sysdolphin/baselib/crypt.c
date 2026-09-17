#include "crypt.h"

#include <string.h>

void HSD_Checksum(u8* src, int len, void* dest)
{
    int i;
    const int md5_bytes = 16;

    // bytes are reversed for big-endian
    u8 md5_init[md5_bytes];

    // A = 0x67452301
    md5_init[0] = 0x01;
    md5_init[1] = 0x23;
    md5_init[2] = 0x45;
    md5_init[3] = 0x67;

    // B = 0xEFCDAB89
    md5_init[4] = 0x89;
    md5_init[5] = 0xAB;
    md5_init[6] = 0xCD;
    md5_init[7] = 0xEF;

    // C = 0x98BADCFE
    md5_init[8] = 0xFE;
    md5_init[9] = 0xDC;
    md5_init[10] = 0xBA;
    md5_init[11] = 0x98;

    // D = 0x10325476
    md5_init[12] = 0x76;
    md5_init[13] = 0x54;
    md5_init[14] = 0x32;
    md5_init[15] = 0x10;

    for (i = 0; i < len; i++) {
        md5_init[i % md5_bytes] += *src++;
    }

    for (i = 1; i < md5_bytes; i++) {
        if (md5_init[i - 1] == md5_init[i]) {
            md5_init[i] = md5_init[i] ^ U8_MAX;
        }
    }

    memcpy(dest, md5_init, sizeof(md5_init));
}

static s32 keys[] = {
    0x26, 0xFF, 0xE8, 0xEF, 0x42, 0xD6, 0x01,
    0x54, 0x14, 0xA3, 0x80, 0xFD, 0x6E,
};
const u8 n_keys = ARRAY_SIZE(keys);

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
static int encryptByte(u8 prev, s32 cur)
{
    u32 key = keys[prev % n_keys];
    u32 val = prev ^ cur;
    val ^= key;

    switch (prev % 7) {
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
#ifdef MUST_MATCH
#pragma pop
#endif

int HSD_Encrypt(u8* data, int len)
{
    u8* ptr;
    int i;

    if (data == NULL) {
        return -1;
    }

    HSD_Checksum(data + 16, len - 16, data);

    for (i = 16; i < len; i++) {
        ptr = data + i;
        *ptr = encryptByte(ptr[-1], *ptr);
    }

    return 0;
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
static int decryptByte(u32 prev, u32 cur)
{
    u32 mod7;

    mod7 = (u8) prev % 7;

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

    cur ^= keys[(u8) prev % n_keys];
    cur ^= prev;
    return cur;
}

#ifdef MUST_MATCH
#pragma pop
#endif

int HSD_Decrypt(u8* data, int len)
{
    u32 prev;
    u8* ptr;
    int i;
    u32 cur;
    u8 check[16];
    int k;

    if (data == NULL) {
        return -1;
    }

    prev = data[15];

    for (i = 16; i < len; i++) {
        ptr = data + i;
        cur = *ptr;
        *ptr = decryptByte(prev, *ptr);
        prev = cur;
    }

    HSD_Checksum(data + 16, len - 16, check);

    for (k = 0; k < 16; k++) {
        if (check[k] != data[k]) {
            return -1;
        }
    }

    return 0;
}
