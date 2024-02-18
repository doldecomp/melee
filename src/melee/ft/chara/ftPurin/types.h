#ifndef MELEE_FT_CHARA_FTPURIN_TYPES_H
#define MELEE_FT_CHARA_FTPURIN_TYPES_H

#include <platform.h>
#include <baselib/forward.h>

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

typedef union ftPurin_MotionVars {
    struct ftPurin_SpecialHiVars {
        bool x0;
    } specialhi;
    struct ftPurin_SpecialNVars {
        u8 fill[0x34];
        float x34;
    } specialn;
} ftPurin_MotionVars;

typedef struct _ftPurinAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    s32 x14;
    float x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    s32 x30;
    s32 x34;
    s32 x38;
    float x3C;
    float x40;
    u8 data_filler_1[0x100 - 0x44];
} ftPurinAttributes;

#endif
