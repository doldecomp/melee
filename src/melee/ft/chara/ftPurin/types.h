#ifndef MELEE_FT_CHARA_FTPURIN_TYPES_H
#define MELEE_FT_CHARA_FTPURIN_TYPES_H

#include <platform.h>

struct ftPurin_FighterVars {
    /* 0x222C */ u32 x222C;
    /* 0x2230 */ u32 x2230;
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ HSD_JObj* x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ void* x2244;
    /* 0x2248 */ u32 x2248;
};

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
