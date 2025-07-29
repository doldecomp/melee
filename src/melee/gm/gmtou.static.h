#ifndef MELEE_GM_GMTOU_STATIC_H
#define MELEE_GM_GMTOU_STATIC_H

#include "baselib/forward.h"
#include "sc/forward.h"
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
    u16 x6[2];
    u16 xA;
    u16 xC;
    u8 xE;
    u8 xF;
    u8 pad_x10[0x1C - 0x10];
    u8 x1C;
    u8 x1D;
    u8 x1E;
    u8 x1F;
    struct {
        u8 x0;
        u8 x1;
        u8 x2;
        u8 x3;
        u8 x4;
        u8 x5;
    } x20[4]; ///< jobj states for each player?
} TmAnimTimers;

typedef struct gm_8019ECAC_OnEnter_t {
    u32 x0;
    s32 x4;
    u8 pad_x8[0x14 - 0x8];
    u32 x14;
} gm_8019ECAC_OnEnter_t;

extern TmData gm_804771C4;
extern SceneDesc* lbl_804D6690;
extern SceneDesc* lbl_804D6694;

#endif
