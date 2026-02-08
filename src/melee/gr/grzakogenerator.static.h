#ifndef __GALE01_1CA394
#define __GALE01_1CA394

#include <platform.h>

struct grZakoGenerator_Data {
    /* +0x000 */ s16 x0;
    /* +0x002 */ s16 x2;
    /* +0x004 */ s32 x4;
    /* +0x008 */ char pad_8[0x3B8];
    /* +0x3C0 */ s16 x3C0;
    /* +0x3C2 */ s16 x3C2;
    /* +0x3C4 */ s32 x3C4;
    /* +0x3C8 */ s32 x3C8;
};

struct lbl_8049F030_t {
    /* +0 */ void* x0;
    /* +4 */ struct grZakoGenerator_Data* x4;
    /* +8 */ s16 x8;
    /* +A:0 */ u8 xA_b0 : 1;
    /* +A:1 */ u8 xA_b1 : 1;
    /* +A:2 */ u8 xA_b2 : 1;
    /* +A:3 */ u8 xA_b3 : 1;
    /* +A:4 */ u8 xA_b4 : 1;
    /* +A:5 */ u8 xA_b5 : 1;
    /* +A:6 */ u8 xA_b6 : 1;
    /* +A:7 */ u8 xA_b7 : 1;
};

static struct lbl_8049F030_t lbl_8049F030;

#endif
