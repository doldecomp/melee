#ifndef MELEE_FT_CHARA_FTPOPO_TYPES_H
#define MELEE_FT_CHARA_FTPOPO_TYPES_H

#include <platform.h>
#include <placeholder.h>

#include "ft/forward.h"
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

typedef struct ftIceClimberAttributes {
    float x0;
    float x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    int x1C;
    float x20;
    float x24;
    float x28;
    float x2C;
    u8 _30[0x68 - 0x30];
    int x68;
    u8 _6C[0xC4 - 0x6C];
    float xC4;
    float xC8;
    u8 _CC[0x90];
} ftIceClimberAttributes;
STATIC_ASSERT(sizeof(ftIceClimberAttributes) == 0x15C);

union ftPp_MotionVars {
    struct ftPp_SpecialSVars {
        /* fp+2340 */ float x0;
        /* fp+2344 */ int x4;
        /* fp+2348 */ int x8;
        /* fp+234C */ int xC;
        /* fp+2350 */ int x10;
        /* fp+2354 */ int x14;
        /* fp+2358 */ UNK_T x18;
        /* fp+235C */ float x1C;
    } specials;
};

#endif
