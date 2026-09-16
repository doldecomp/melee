#ifndef __GALE01_1EFC68
#define __GALE01_1EFC68

#include <Runtime/platform.h>

typedef struct grMc_CarEntry {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ Vec3 pos;
    /* 0x20 */ u16 x20;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
    } x22_flags;
    /* 0x23 */ u8 x23;
    /* 0x24 */ Item_GObj* x24;
    /* 0x28 */ HSD_Generator* gen;
} grMc_CarEntry;

ASSERT_SIZE(grMc_CarEntry, 0x2C);

static grMc_CarEntry grMc_8049F4B8[30];

#endif
