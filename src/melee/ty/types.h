#ifndef MELEE_TY_TYPES_H
#define MELEE_TY_TYPES_H

#include <placeholder.h>

#include "baselib/forward.h"
#include "ty/forward.h" // IWYU pragma: export

#include "platform.h"

#include "mtx/types.h"

struct Toy {
    /*  +0 */ char pad_0[0x8];
    /*  +8 */ int x8;
    /*  +C */ char pad_C[0x40 - 0xC];
    /* +40 */ Vec3 translate;
    /* +4C */ Vec3 offset;
};
STATIC_ASSERT(sizeof(struct Toy) == 0x58);

#endif
