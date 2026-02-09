#include "hsd_3AA7.h"

#include "hsd_3A94.h"

/* 4D7984 */ static volatile s32 hsd_804D7984;
/* 4D7998 */ static s32 hsd_804D7998;

/// #fn_803AA790

/// #hsd_803AAA48

/// #fn_803AC168

void fn_803AC258(s32 arg0, s32 arg1)
{
    s32 buf[9];
    buf[0] = 13;
    buf[1] = arg0;
    buf[4] = arg1;
    buf[5] = 0;
    buf[6] = 0;
    buf[8] = 0;
    buf[7] = fn_803ACBE8((CardState*) arg0, arg1);
    fn_803AC168(buf);
}

void fn_803AC2A4(s32 arg0)
{
    s32 buf[9];
    buf[0] = 14;
    buf[1] = arg0;
    fn_803AC168(buf);
}

void fn_803AC2D4(void)
{
    hsd_804D7998 = hsd_804D7984;
}

void fn_803AC2E0(void)
{
    s32 saved;

    if (hsd_804D7998 < 0) {
        return;
    }
    saved = hsd_804D7998;
    while (saved != hsd_804D7984) {
        hsd_804D1148[saved][0] = 0;
        saved = (saved + 1) % 128;
    }
    hsd_804D7984 = hsd_804D7998;
}

void fn_803AC334(void)
{
    hsd_804D7998 = -1;
}

/// #hsd_803AC340

void hsd_803AC3E0(struct hsd_803AC3E0_arg0_t* arg0, int arg1, int arg2,
                  int arg3, int arg4)
{
    arg0->x28[arg1] = arg3;
    arg0->x4C[arg1] = arg2;
    arg0->x70[arg1] = arg4;
}

/// #fn_803AC3F8

/// #hsd_803AC558

/// #fn_803AC634

/// #fn_803AC6B8

/// #fn_803AC7DC

s32 fn_803ACB74(s32 arg0, s32 arg1)
{
    s32 diff;

    if (arg0 < 0) {
        return -1;
    }
    if (arg1 < 0) {
        return 1;
    }
    if (arg0 == 0 && arg1 == 0xFF) {
        return 1;
    }
    if (arg0 == 0xFF && arg1 == 0) {
        return -1;
    }
    diff = arg0 - arg1;
    if (diff > 0x80) {
        return -1;
    }
    if (diff < -0x80) {
        return 1;
    }
    return diff;
}

// @TODO: Currently 75.56% match - needs register allocation fix
s32 fn_803ACBE8(CardState* arg0, s32 arg1)
{
    u32 hdr = arg0->x24;
    u32 size = arg0->x8;
    return (s32) (size * (arg1 + (hdr + size + 0x2F) / size - 1));
}

/// #fn_803ACC0C

/// #fn_803ACD58

/// #fn_803ACF30

/// #fn_803ACFC0

/// #fn_803AD16C

/// #fn_803ADE4C

/// #fn_803ADF90

/// #fn_803AE7F8

/// #fn_803AF3F0

/// #fn_803B0120

/// #fn_803B0E9C

/// #fn_803B1338

/// #fn_803B1F78

/// #fn_803B21E8

/// #hsd_803B2374

void hsd_803B24E4(s32* arg0, int arg1, int arg2, void* arg3)
{
    memset(arg0, 0, 0x464);
    arg0[8] = -1;
    arg0[1] = arg1;
    arg0[2] = arg2;
    arg0[0] = (s32) arg3;
}

/// #hsd_803B2550

// @TODO: Currently 85.23% match - same regalloc issue as fn_803ACBE8
s32 hsd_803B2674(CardState* arg0)
{
    u32 blocks;

    arg0->x24 = hsd_803AC340((u8*) arg0 + 0x3B0);
    blocks = (arg0->x24 + arg0->x8 + 0x2F) / arg0->x8;
    return blocks + fn_803AC7DC(arg0);
}

/// #fn_803B26CC
