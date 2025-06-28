#ifndef MELEE_PL_PLBONUSLIB_INLINE_H
#define MELEE_PL_PLBONUSLIB_INLINE_H

#include <sysdolphin/baselib/debug.h>

static inline float pl_CalculateAverage(float val, float total)
{
    HSD_ASSERT(16, total != 0.0F);
    return val / total;
}

#endif
