/** @file
 * @todo This is temporary.
 */
#ifndef MELEE_FT_FTCOLLTYPES_H
#define MELEE_FT_FTCOLLTYPES_H

#include "ft/forward.h"

#include <dolphin/mtx/types.h>

struct ftCollisionBox {
    float top;
    float bottom;
    Vec2 left;
    Vec2 right;
};

struct UNK_SAMUS_S2 {
    Fighter_Part parts[3];
    Vec3 vec1;
    Vec3 vec2;
    float single_float;
};

#endif
