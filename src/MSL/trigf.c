#include "math.h"

#define __epsilon 3.45266983e-4f

extern f32 __sincos_on_quadrant[];
extern f32 __sincos_poly[];

const f32 tmp_float[] = { 0.25f, 0.0232393741608f, 1.70555722434e-7f,
                          1.86736494323e-11f };
f32 __four_over_pi_m1[] = { 0.0f, 0.0f, 0.0f, 0.0f };

void __sinit_trigf_c(void)
{
    __four_over_pi_m1[0] = tmp_float[0];
    __four_over_pi_m1[1] = tmp_float[1];
    __four_over_pi_m1[2] = tmp_float[2];
    __four_over_pi_m1[3] = tmp_float[3];
}

SECTION_CTORS void* const __sinit_trigf_c_reference = __sinit_trigf_c;

f32 sinf(f32 x)
{
    int n;
    f32 y;
    f32 ysq;
    f32 z;

    z = (2.0f / (f32) M_PI) * x;
    n = (__HI(x) & 0x80000000) ? (int) (z - 0.5f) : (int) (z + 0.5f);

    y = x - n * 2 + __four_over_pi_m1[0] * x + __four_over_pi_m1[1] * x +
        __four_over_pi_m1[2] * x + __four_over_pi_m1[3] * x;
    n &= 3;

    if (fabsf__Ff(y) < __epsilon) {
        n <<= 1;
        return __sincos_on_quadrant[n] +
               (__sincos_on_quadrant[n + 1] * y * __sincos_poly[9]);
    }

    ysq = y * y;
    if (n & 1) {
        n <<= 1;
        z = (((__sincos_poly[0] * ysq + __sincos_poly[2]) * ysq +
              __sincos_poly[4]) *
                 ysq +
             __sincos_poly[6]) *
                ysq +
            __sincos_poly[8];

        return z * __sincos_on_quadrant[n];
    } else {
        n <<= 1;
        z = ((((__sincos_poly[1] * ysq + __sincos_poly[3]) * ysq +
               __sincos_poly[5]) *
                  ysq +
              __sincos_poly[7]) *
                 ysq +
             __sincos_poly[9]) *
            y;
        return z * __sincos_on_quadrant[n + 1];
    }
}

f32 cosf(f32 x)
{
    int n;
    f32 y;
    f32 ysq;
    f32 z;

    z = (2.0f / (f32) M_PI) * x;
    n = (__HI(x) & 0x80000000) ? (int) (z - 0.5f) : (int) (z + 0.5f);

    y = x - n * 2 + __four_over_pi_m1[0] * x + __four_over_pi_m1[1] * x +
        __four_over_pi_m1[2] * x + __four_over_pi_m1[3] * x;
    n &= 3;
    if (fabsf__Ff(y) < __epsilon) {
        n <<= 1;
        return __sincos_on_quadrant[n + 1] - y * __sincos_on_quadrant[n];
    }

    ysq = y * y;
    if (n & 1) {
        n <<= 1;
        z = -((((__sincos_poly[1] * ysq + __sincos_poly[3]) * ysq +
                __sincos_poly[5]) *
                   ysq +
               __sincos_poly[7]) *
                  ysq +
              __sincos_poly[9]) *
            y;
        return z * __sincos_on_quadrant[n];
    } else {
        n <<= 1;
        z = (((__sincos_poly[0] * ysq + __sincos_poly[2]) * ysq +
              __sincos_poly[4]) *
                 ysq +
             __sincos_poly[6]) *
                ysq +
            __sincos_poly[8];
        return z * __sincos_on_quadrant[n + 1];
    }
}

#pragma dont_inline on

f32 sin__Ff(f32 x)
{
    return sinf(x);
}

f32 cos__Ff(f32 x)
{
    return cosf(x);
}

#pragma dont_inline reset

f32 tanf(f32 x)
{
    return sin__Ff(x) / cos__Ff(x);
}
