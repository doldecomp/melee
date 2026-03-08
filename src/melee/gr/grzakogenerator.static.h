#ifndef __GALE01_1CA394
#define __GALE01_1CA394

#include <platform.h>

struct ZakoElement {
    /* +0 */ s16 x0;
    /* +2 */ s16 x2;
    /* +4 */ HSD_GObj* x4;
    /* +8 */ s32 x8;
};

struct ZakoConfig {
    /* +0 */ void* x0;
    /* +4 */ void* x4;
    /* +8 */ s32 x8;
    /* +C */ void* xC;
    /* +10 */ f32 x10;
    /* +14 */ s32 x14;
    /* +18 */ s32 x18;
};

struct grZakoGenerator_Data {
    /* +0x000 */ struct ZakoElement elements[81];
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
