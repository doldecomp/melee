#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include <dolphin/types.h>

typedef struct _HSD_Spline HSD_Spline;

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splArcLengthPoint(Vec*, HSD_Spline*, f32);

#endif
