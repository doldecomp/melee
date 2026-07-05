#ifndef MELEE_GM_INLINES_H
#define MELEE_GM_INLINES_H

#include "gm/gmregtyfall.h"
#include "ty/toy.h"

/// @todo Figure out where this goes
inline s32 fn_801A7FB4_inline(void)
{
    s32 i;
    s32 count;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (Toy_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

inline s32 fn_801A7FB4_inline2(void)
{
    s32 count;
    s32 i;
    count = 0;
    for (i = count; i < 0x1A; i++) {
        if (Toy_803048C0(gm_801A659C(i)) ? true : false) {
            count++;
        }
    }
    return count;
}

#endif
