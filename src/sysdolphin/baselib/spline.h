#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include <dolphin/mtx/types.h>

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splArcLengthPoint(Vec3*, struct _HSD_Spline*, f32);
void splGetSplinePoint(s32, s32);

#endif
