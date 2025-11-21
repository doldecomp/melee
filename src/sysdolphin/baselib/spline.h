#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include "forward.h"

#include <dolphin/mtx.h>

struct HSD_Spline {
    /*  +0 */ u8 type;
    /*  +2 */ s16 numcv;
    /*  +4 */ f32 tension;
    /*  +8 */ Vec3* cv;
    /*  +C */ f32 totalLength;
    /* +10 */ f32* segLength;
    /* +14 */ f32 (*segPoly)[5];
};

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splGetCardinalPoint(Vec3*, Vec3*, f32, f32);
void splGetBSplinePoint(Vec3*, Vec3*, f32);
void splGetBezierPoint(Vec3*, Vec3*, f32);
void splGetSplinePoint(Vec3*, HSD_Spline*, f32);
f32 splArcLengthGetParameter(HSD_Spline*, f32);
void splArcLengthPoint(Vec3*, HSD_Spline*, f32);

#endif
