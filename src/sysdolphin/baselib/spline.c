#include "spline.h"

#include <math.h>
#include <placeholder.h>
#include <MetroTRK/intrinsics.h>

f32 splGetHelmite(f32 fterm, f32 time, f32 p0, f32 p1, f32 d0, f32 d1)
{
    f32 _3t2_T2;
    f32 _2t3_T3;
    f32 t3_T2;
    f32 t2_T;
    f32 t2;
    f32 _1_T2;

    _1_T2 = time * time;
    t2 = fterm * fterm;
    t2_T = _1_T2 * fterm;
    t3_T2 = t2 * (_1_T2 * time);
    _2t3_T3 = 2.0f * t3_T2 * fterm;
    _3t2_T2 = 3.0f * _1_T2 * t2;

    return (d1 * (t3_T2 - t2_T)) + ((d0 * (time + ((t3_T2 - t2_T) - t2_T))) +
                                    ((p0 * (1.0f + (_2t3_T3 - _3t2_T2))) +
                                     (p1 * (-_2t3_T3 + _3t2_T2))));
}

static inline void splGetSplinePoint_inline(Vec3* p, Vec3* m, f32 a, f32 b,
                                            f32 c, f32 d)
{
    p->x = (m[0].x * a) + (m[1].x * b) + (m[2].x * c) + (m[3].x * d);
    p->y = (m[0].y * a) + (m[1].y * b) + (m[2].y * c) + (m[3].y * d);
    p->z = (m[0].z * a) + (m[1].z * b) + (m[2].z * c) + (m[3].z * d);
}

static inline void splGetSplinePoint_inline2(Vec3* p, HSD_Spline* arg1,
                                             s16 idx, f32 t)
{
    switch (arg1->x0) {
    case 0: {
        // lerp
        Vec3* m = &arg1->x8[idx];
        p->x = (t * (m[1].x - m[0].x)) + m[0].x;
        p->y = (t * (m[1].y - m[0].y)) + m[0].y;
        p->z = (t * (m[1].z - m[0].z)) + m[0].z;
        return;
    }
    case 1: {
        Vec3* m = &arg1->x8[idx * 3];
        f32 t2 = t * t;
        f32 it = 1.0F - t;
        f32 it2 = it * it;
        f32 a = it2 * it;
        f32 b = 3.0F * t * it2;
        f32 c = 3.0F * t2 * it;
        f32 d = t2 * t;

        p->x = (m[0].x * a) + (m[1].x * b) + (m[2].x * c) + (m[3].x * d);
        p->y = (m[0].y * a) + (m[1].y * b) + (m[2].y * c) + (m[3].y * d);
        p->z = (m[0].z * a) + (m[1].z * b) + (m[2].z * c) + (m[3].z * d);
        return;
    }
    case 2: {
        Vec3* m = &arg1->x8[idx];
        f32 t2 = t * t;
        f32 it = 1.0F - t;
        f32 t3 = t2 * t;

        /* const */ f32 fac = (1.0F / 6.0F);
        f32 a = fac * it * it * it;
        f32 b = fac * (3.0F * t3 - 6.0F * t2 + 4.0F);
        f32 c = fac * (3.0F * (-t3 + t2 + t) + 1.0F);
        f32 d = fac * t3;

        p->x = (m[0].x * a) + (m[1].x * b) + (m[2].x * c) + (m[3].x * d);
        p->y = (m[0].y * a) + (m[1].y * b) + (m[2].y * c) + (m[3].y * d);
        p->z = (m[0].z * a) + (m[1].z * b) + (m[2].z * c) + (m[3].z * d);
        return;
    }
    case 3: {
        Vec3* m = &arg1->x8[idx];
        f32 x4 = arg1->x4;
        f32 t2 = t * t;
        f32 t3 = t2 * t;
        f32 a = x4 * (-t3 + 2.0F * t2 - t);
        f32 b = ((2.0F - x4) * t3) + ((x4 - 3.0F) * t2) + 1.0F;
        f32 c = ((x4 - 2.0F) * t3) + ((3.0F - (2.0F * x4)) * t2) + (x4 * t);
        f32 d = x4 * (t3 - t2);

        p->x = (m[0].x * a) + (m[1].x * b) + (m[2].x * c) + (m[3].x * d);
        p->y = (m[0].y * a) + (m[1].y * b) + (m[2].y * c) + (m[3].y * d);
        p->z = (m[0].z * a) + (m[1].z * b) + (m[2].z * c) + (m[3].z * d);
        return;
    }
    }
}

void splGetSplinePoint(Vec3* p, HSD_Spline* arg1, f32 arg2)
{
    PAD_STACK(8);
    if (arg2 < 0.0F || arg2 > 1.0F) {
        return;
    }

    if (arg2 < 1.0F) {
        f32 t = (arg2 * (arg1->x2 - 1));
        s16 idx = t;
        t = t - idx;
        splGetSplinePoint_inline2(p, arg1, idx, t);
    } else {
        s16 idx = arg1->x2 - 1;
        switch (arg1->x0) { /* irregular */
        case 0:
            *p = arg1->x8[idx];
            return;
        case 1:
            *p = arg1->x8[idx * 3];
            return;
        case 2: {
            Vec3* m = &arg1->x8[idx] - 1;
            f32 t = 1.0F;
            f32 it = 1.0F - t;
            f32 a = (1.0F / 6.0F) * it * it * it;
            f32 c = (1.0F / 6.0F) * (3.0F * (-(t * t * t) + t * t + t) + 1.0F);
            f32 b = (1.0F / 6.0F) * (3.0F * (t * t * t) - 6.0F * t * t + 4.0F);
            f32 d = (1.0F / 6.0F) * t * t * t;

            splGetSplinePoint_inline(p, m, a, b, c, d);
        }
            return;
        case 3: {
            Vec3* m = &arg1->x8[idx];
            *p = m[1];
        }
            return;
        }
    }
}

static inline f32 splArcLengthPolynomial(const f32 coeffs[5], f32 t)
{
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    f32 t4 = t3 * t;
    f32 result = (coeffs[0] * t4) + (coeffs[1] * t3) + (coeffs[2] * t2) +
                 (coeffs[3] * t) + coeffs[4];

    if ((result < 0.0F) && (result > -0.001F)) {
        result = 0.0F;
    }

    return sqrtf__Ff(result);
}

f32 splArcLengthGetParameter(HSD_Spline* spl, f32 arg1)
{
    s32 idx = 0;
    f32 result;
    f32 start = 0.0F;
    f32 end = 1.0F;
    PAD_STACK(8);

    if (arg1 <= 0.0F) {
        return start;
    }

    if (arg1 >= 1.0F) {
        return end;
    }

    while (spl->segments[idx + 1] < arg1) {
        idx++;
    }

    switch (spl->x0) {
    case 0:
        result = (arg1 - spl->segments[idx]) / (spl->segments[idx + 1] - spl->segments[idx]);
        break;
    case 1:
    case 2:
    case 3: {
        // i belive the bulk of this math is applying simpson's rule
        // https://en.wikipedia.org/wiki/Simpson%27s_rule
        f32 var_f22 = spl->xC * (arg1 - spl->segments[idx]);

        while (ABS(start - end) >= 0.00001F) {
            s32 i;
            f32 var_f24 = 0.0F;
            f32* coeffs = spl->coeffs[idx];
            f32 midpoint = (start + end) / 2.0F;
            f32 dx = (midpoint - start) / 8.0F;
            f32 t = start + dx;
            f32 simpsons;
            f32 midpoint_val;
            f32 start_val;
            result = midpoint;

            for (i = 2; i <= 8; i++) {
                if (!(i & 1)) {
                    var_f24 += 4.0F * splArcLengthPolynomial(coeffs, t);
                } else {
                    var_f24 += 2.0F * splArcLengthPolynomial(coeffs, t);
                }
                t += dx;
            }

            start_val = splArcLengthPolynomial(coeffs, start);
            midpoint_val = splArcLengthPolynomial(coeffs, midpoint);
            simpsons = dx * (var_f24 + start_val + midpoint_val) / 3.0F;
            if (var_f22 < (0.00001F + simpsons)) {
                end = midpoint;
            } else {
                start = midpoint;
                var_f22 -= simpsons;
            }
        }
    } break;
    }

    return (result + idx) / (spl->x2 - 1.0F);
}

void splArcLengthPoint(Vec3* vec3, HSD_Spline* spline, f32 farg0)
{
    splGetSplinePoint(vec3, spline, splArcLengthGetParameter(spline, farg0));
}
