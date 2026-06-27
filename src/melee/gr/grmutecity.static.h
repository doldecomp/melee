#ifndef __GALE01_1EFC68
#define __GALE01_1EFC68

#include "platform.h"

#include <placeholder.h>

#include <dolphin/mtx.h>

typedef struct grMc_CarEntry {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
    /* 0x18 */ f32 x18;
    /* 0x1C */ f32 x1C;
    /* 0x20 */ u16 x20;
    struct {
        u8 b0 : 1;
        u8 b1 : 1;
    } x22_flags;
    /* 0x23 */ u8 x23;
    /* 0x24 */ s32 x24;
    /* 0x28 */ s32 x28;
} grMc_CarEntry;

STATIC_ASSERT(sizeof(grMc_CarEntry) == 0x2C);

static grMc_CarEntry grMc_8049F4B8[30];

#endif
