#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include "forward.h"

#include <dolphin/mtx.h>

struct HSD_Spline {
    /*  +0 */ u8 x0;
    /*  +1 */ u8 x1;
    /*  +2 */ s16 x2;
    /*  +4 */ f32 x4;
    /*  +8 */ Vec3* x8;
    /*  +C */ f32 xC;
    /* +10 */ f32* segments;
    /* +14 */ f32 (*coeffs)[5];
};

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splGetSplinePoint(Vec3*, HSD_Spline*, f32);
f32 splArcLengthGetParameter(HSD_Spline*, f32);
void splArcLengthPoint(Vec3*, HSD_Spline*, f32);

#endif
