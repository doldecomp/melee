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

extern gm_803DEBE8_t gm_803DEBE8[25];
extern gm_80490940_t gm_80490940[5];

#endif
