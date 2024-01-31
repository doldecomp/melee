#include <platform.h>

#include <placeholder.h>
#include <MSL/math.h>

float cos__Ff(float);
float sin__Ff(float);
float cosf(float);
float sinf(float);

float tanf(float x)
{
    return sin__Ff(x) / cos__Ff(x);
}

float cos__Ff(float x)
{
    return cosf(x);
}

float sin__Ff(float x)
{
    return sinf(x);
}

const float tmp_float[] = { 0.25F, 0.023239374F, 0.00000017055572F,
                            1.867365e-11F };

int MSL_TrigF_80400770[] = { 0x7FFFFFFF };
int MSL_TrigF_80400774[] = { 0x7F800000 };

float __four_over_pi_m1[4] = { 0 };

const float __two_over_pi = 0.63661975F;
const float MSL_TrigF_804DE19C = 0.5F;
const float __SQRT_FLT_EPSILON__ = 3.4526698300e-4F;

const double MSL_TrigF_804DE1A8 = 4503601774854144.0L;

extern const float __sincos_poly[];
extern const float __sincos_on_quadrant[];

float cosf(float x)
{
    NOT_IMPLEMENTED;
}

float sinf(float x)
{
    NOT_IMPLEMENTED;
}

void __sinit_trigf_c(void)
{
    NOT_IMPLEMENTED;
}
