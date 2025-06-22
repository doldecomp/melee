#ifndef MELEE_PL_PLBONUSLIB_INLINE_H
#define MELEE_PL_PLBONUSLIB_INLINE_H

#include <sysdolphin/baselib/debug.h>

inline void plCheckTotal(float total)
{
    HSD_ASSERT(0x10, total != 0.0F);
}

#endif
