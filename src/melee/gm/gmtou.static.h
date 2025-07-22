#ifndef MELEE_GM_GMTOU_STATIC_H
#define MELEE_GM_GMTOU_STATIC_H

#include "baselib/forward.h"
#include "dolphin/types.h"
#include "gm/types.h"

typedef struct TmBoxArrays {
    void* box2;
    void* box3;
    void* box4;
} TmBoxArrays;

/// TODO :: this isnt exactly right
typedef struct TmAnimTimers {
    u16 x0;
    u16 x2;
    u16 x4;
    u16 x6;
    u16 x8;
    u16 xA;
    u16 xC;
    u8 xE;
    u8 xF;
    u8 pad_x10[0x1C - 0x10];
    u8 x1C;
    u8 x1D;
    u8 x1E;
    u8 x1F;
    u8 x20;
} TmAnimTimers;

extern TmData gm_804771C4;

#endif
