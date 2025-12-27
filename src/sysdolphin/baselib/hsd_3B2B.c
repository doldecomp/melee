#include "hsd_3B2B.h"

void hsd_803B2B20(u8* src, int len, void* dest)
{
    int i;
    const int spCount = 16;
    u8 sp[spCount];
    sp[0x0] = 0x01;
    sp[0x1] = 0x23;
    sp[0x2] = 0x45;
    sp[0x3] = 0x67;
    sp[0x4] = 0x89;
    sp[0x5] = 0xab;
    sp[0x6] = 0xcd;
    sp[0x7] = 0xef;
    sp[0x8] = 0xfe;
    sp[0x9] = 0xdc;
    sp[0xa] = 0xba;
    sp[0xb] = 0x98;
    sp[0xc] = 0x76;
    sp[0xd] = 0x54;
    sp[0xe] = 0x32;
    sp[0xf] = 0x10;

    for (i = 0; i < len; i++) {
        sp[i % spCount] += *src++;
    }

    for (i = 1; i < spCount; i++) {
        if (sp[i - 1] == sp[i]) {
            sp[i] = sp[i] ^ 0xff;
        }
    }

    memcpy(dest, sp, sizeof(sp));
}
