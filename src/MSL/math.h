#ifndef MSL_MATH_H
#define MSL_MATH_H

#include <platform.h>

#ifdef MWERKS_GEKKO
#include <math_ppc.h>
#include <MetroTRK/intrinsics.h>
#endif

#define MSL_HI(x) *(int*) &x
#define MSL_LO(x) *(1 + (int*) &x)

#define M_PI 3.14159265358979323846
#define M_PI_2 (M_PI / 2)

enum FloatType {
    FP_NAN = 1,
    FP_INFINITE = 2,
    FP_ZERO = 3,
    FP_NORMAL = 4,
    FP_SUBNORMAL = 5
};

static inline s32 __fpclassifyf(float x)
{
    const s32 exp_mask = 0x7F800000;
    const s32 mantissa_mask = 0x007FFFFF;
    switch ((*(s32*) &x) & exp_mask) {
    case exp_mask:
        return ((*(s32*) &x) & mantissa_mask) ? FP_NAN : FP_INFINITE;
    case 0:
        return ((*(s32*) &x) & mantissa_mask) ? FP_SUBNORMAL : FP_ZERO;
    default:
        return FP_NORMAL;
    }
}

extern int __HI(double);
extern int __LO(double);

static inline s32 __fpclassifyd(double x)
{
    switch (__HI(x) & 0x7ff00000) {
    case 0x7ff00000:
        return ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
                   ? FP_NAN
                   : FP_INFINITE;
    case 0:
        return ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff))
                   ? FP_SUBNORMAL
                   : FP_ZERO;
    default:
        return FP_NORMAL;
    }
}

#define fpclassify(x)                                                         \
    ((sizeof(x) == sizeof(float)) ? __fpclassifyf((float) (x))                \
                                  : __fpclassifyd((double) (x)))

#ifdef MWERKS_GEKKO
#define fabsf __fabsf
static inline double fabs(double f)
{
    return __fabs(f);
}
#endif

float fabsf(float);
float sqrtf(float);
float acosf(float);
float asinf(float);
float atan2f(float y, float x);
float atanf(float);
float cosf(float);
float sinf(float);
double frexp(double x, int* exponent);
float fabsf__Ff(float);
float cos__Ff(float x);
float sin__Ff(float x);
void __sinit_trigf_c(void);
float logf(float);
float expf(float);
double fabs(double);

static inline float fmodf(float a, float b)
{
    long long quotient;

    if (fabsf(b) > fabsf(a)) {
        return a;
    }
    quotient = a / b;
    return a - b * quotient;
}

#endif
