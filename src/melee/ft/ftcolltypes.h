/** @file
 * @todo This is temporary.
 */
#ifndef MELEE_FT_FTCOLLTYPES_H
#define MELEE_FT_FTCOLLTYPES_H

#include "ft/forward.h"

#include <dolphin/mtx/types.h>

struct ftCollisionBox {
    /*  +0 */ float top;
    /*  +4 */ float bottom;
    /*  +8 */ Vec2 left;
    /* +10 */ Vec2 right;
};

struct UNK_SAMUS_S2 {
    Fighter_Part parts[3];
    Vec3 vec1;
    Vec3 vec2;
    float single_float;
};

#endif
