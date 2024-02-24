#ifndef MELEE_FT_CHARA_FTPOPO_TYPES_H
#define MELEE_FT_CHARA_FTPOPO_TYPES_H

#include <platform.h>
#include "it/forward.h"

struct ftPopo_FighterVars {
    /* 0x222C */ Item_GObj* x222C;
    /* 0x2230:0 */ u8 x2230_b0 : 1;
    /* 0x2231 */ u8 filler_x2231[3];
    /* 0x2234 */ u32 x2234;
    /* 0x2238 */ u32 x2238;
    /* 0x223C */ u32 x223C;
    /* 0x2240 */ u32 x2240;
    /* 0x2244 */ u32 x2244;
    /* 0x2248 */ u32 x2248;
    /* 0x224C */ u32 x224C;
    /* 0x2250 */ float x2250;
};

typedef struct _ftIceClimberAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    s32 x1C;
    s32 x20;
    s32 x24;
    s32 x28;
    s32 x2C;
    u8 data_filler_1[0xC4 - 0x30];
    float xC4;
    float xC8;
    u8 data_filler_2[0x90];
} ftIceClimberAttributes;

#endif
