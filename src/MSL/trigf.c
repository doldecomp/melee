#include <dolphin/types.h>

f32 cos__Ff(f32);
f32 sin__Ff(f32);
f32 cosf(f32);
f32 sinf(f32);

f32 tanf(f32 x)
{
    return sin__Ff(x) / cos__Ff(x);
}

f32 cos__Ff(f32 x)
{
    return cosf(x);
}

f32 sin__Ff(f32 x)
{
    return sinf(x);
}

const float tmp_float[] = { 
    0.25f, 0.023239374f, 0.00000017055572f, 1.867365e-11f 
};

int lbl_80400770[] = { 0x7FFFFFFF };
int lbl_80400774[] = { 0x7F800000 };

int __four_over_pi_m1[4] = { };

const float __two_over_pi = 0.63661975F;
const float lbl_804DE19C = 0.5F;
const float __SQRT_FLT_EPSILON__ = 3.4526698300e-04f;

const double lbl_804DE1A8 = 4503601774854144.0;
