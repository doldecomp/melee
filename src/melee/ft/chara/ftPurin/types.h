#ifndef MELEE_FT_CHARA_FTPURIN_TYPES_H
#define MELEE_FT_CHARA_FTPURIN_TYPES_H

#include <platform.h>

union ftPurin_MotionVars {
    struct ftPurin_SpecialHiVars {
        bool x0;
    } specialhi;
};

typedef struct _ftPurinAttributes {
    f32 x0;
    f32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    s32 x14;
    f32 x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0x100 - 0x30];
} ftPurinAttributes;

#endif
