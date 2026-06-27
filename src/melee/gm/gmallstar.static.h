#ifndef MELEE_GM_ALLSTAR_STATIC_H
#define MELEE_GM_ALLSTAR_STATIC_H

#include "dolphin/types.h"

typedef struct gm_80490940_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 x2;
    /* +3 */ u8 x3;
    /* +4 */ u8 x4;
} gm_80490940_t;

typedef struct gm_803DEBE8_t {
    /* +0 */ u8 x0;
    /* +1 */ u8 x1;
    /* +2 */ u8 x2;
    /* +3 */ u8 x3;
} gm_803DEBE8_t;

typedef struct AllstarRoundInfo {
    /* +0 */ u32 start;
    /* +4 */ u32 count;
} AllstarRoundInfo;

#endif
