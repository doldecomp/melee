#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include <dolphin/types.h>

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splArcLengthPoint(Vec*, struct _HSD_Spline*, f32);

#endif
