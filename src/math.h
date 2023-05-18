#ifndef __MATH_H__
#define __MATH_H__

#include <platform.h>

#include <MetroTRK/intrinsics.h>

#define M_PI 3.14159265358979323846
#define M_PI_2 (M_PI / 2)
#define M_PI_3 (M_PI / 3)

static float const deg_to_rad ATTRIBUTE_USED = M_PI / 180;
static float const rad_to_deg ATTRIBUTE_USED = 180 / M_PI;

#ifdef __MWERKS__
#pragma push
#pragma cplusplus on
#endif

#define FLT_EPSILON 1.00000001335e-10F

extern inline float sqrtf(float x)
{
    static const double _half = .5;
    static const double _three = 3.0;
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double) x); // returns an approximation to
        guess = _half * guess *
                (_three - guess * guess * x); // now have 12 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 24 sig bits
        guess = _half * guess *
                (_three - guess * guess * x); // now have 32 sig bits
        y = (float) (x * guess);
        return y;
    }
    return x;
}

#ifdef __MWERKS__
#pragma pop
#endif

enum FloatType {
    FP_NAN = 1,
    FP_INFINITE = 2,
    FP_ZERO = 3,
    FP_NORMAL = 4,
    FP_SUBNORMAL = 5
};

static inline s32 __fpclassifyf(float x)
{
    const s32 exp_mask = 0b01111111100000000000000000000000; // = 0x7F800000
    const s32 mantissa_mask =
        0b00000000011111111111111111111111; // = 0x007fffff
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

/// @todo Is #fabs_inline fake? See #ftCo_AttackS3_CheckInput.
#define ABS(x) ((x) < 0 ? -(x) : (x))

static inline f32 fabs_inline(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

#endif
