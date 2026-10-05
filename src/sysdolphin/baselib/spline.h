#ifndef SYSDOLPHIN_BASELIB_SPLINE_H
#define SYSDOLPHIN_BASELIB_SPLINE_H

#include <dat_macros.h>

#include <dolphin/mtx.h>

typedef struct HSD_Spline {
    /*  +0 */ u8 type;
    /*  +2 */ s16 numcv;
    /*  +4 */ f32 tension;
    /// Types other than 0 have an extra control point at each end.
    /*  +8 */ Vec3* cv DAT_COUNT(numcv + 2 * (type != 0));
    /*  +C */ f32 totalLength;
    /* +10 */ f32* segLength DAT_COUNT(numcv);
    /* +14 */ f32 (*segPoly)[5] DAT_COUNT(numcv - 1);
} HSD_Spline;

f32 splGetHelmite(f32, f32, f32, f32, f32, f32);
void splGetSplinePoint(Vec3*, HSD_Spline*, f32);
f32 splArcLengthGetParameter(HSD_Spline*, f32);
void splArcLengthPoint(Vec3*, HSD_Spline*, f32);

#endif
