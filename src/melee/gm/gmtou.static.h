#ifndef MELEE_GM_GMTOU_STATIC_H
#define MELEE_GM_GMTOU_STATIC_H

#include "baselib/forward.h"

#include "dolphin/types.h"
#include "gm/types.h"

#include "sc/forward.h"

typedef struct TmBoxArrays {
    void* box2;
    void* box3;
    void* box4;
} TmBoxArrays;

/// @todo :: this isnt exactly right
typedef struct TmAnimTimers {
    u32 x0;
    u16 x4;
    u16 x6[4];
    u8 xE;
    u8 xF;
    u8 x10[4];
    u8 pad_x14[0x18 - 0x14];
    u8 x18[4];
    u8 x1C;
    struct {
        u8 a;
        u8 b;
        u8 c;
        u8 x0;
        u8 x1;
        u8 x2;
    } x1D[4]; ///< per-player jobj/anim states
    u8 pad_x35[0x38 - 0x35];
    u8 x38[4];
    u8 pad_x3C[0x40 - 0x3C];
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
