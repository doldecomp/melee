#ifndef MELEE_GM_GMTOU_STATIC_H
#define MELEE_GM_GMTOU_STATIC_H

#include "baselib/forward.h"
#include "dolphin/types.h"

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

typedef struct TmData {
    s32 x0;
    s32 x4;
    u8 pad_x8[0x4E0 - 0x8];
    HSD_Text* x4E0;
    HSD_Text* x4E4;
    HSD_Text* x4E8[6];
    HSD_Text* x500[6];
    HSD_Text* x518[3];
} TmData;

static TmData gm_804771C4;

#endif
