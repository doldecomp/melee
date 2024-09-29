#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include <platform.h>
#include <placeholder.h>

#include "baselib/forward.h"
#include <dolphin/mtx/forward.h>

struct HSD_Spline {
    u8 x0 UNK_SIZE_ARRAY;
};

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splArcLengthPoint(Vec3*, HSD_Spline*, f32);
void splGetSplinePoint(s32, s32);

#endif
