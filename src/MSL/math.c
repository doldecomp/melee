#include "math.h"

#include <platform.h>

#define EXP_MASK 0x7F800000
#define EXP_ZERO 0x3F800000 // hex representation of (float)0.0f
#define MANT_MASK 0x007FFFFF
#define SIGN_BIT 0x80000000
#define F32_BIT_CAST(raw_x) (*(float*) &raw_x)

typedef union {
    u32 u;
    float f;
} FloatU32;
#define F32_UNBIASED_EXPONENT(raw_x)                                          \
    (((raw_x & 0xFF800000) >> 23) - /*exponent bias*/ 127)
#define F32_HIGH_MANTISSA_BITS(raw_x)                                         \
    ((raw_x >> 16) & 0x7F) // 7 most significant mantissa bits
#define F32_LOW_MANTISSA_BITS(raw_x)                                          \
    (raw_x & 0xFFFF)   // remaining 16 mantissa bits
#define LN2 0.6931472f // natural logarithm of 2

#if defined(__MWERKS__) && !defined(M2CTX)
#define SECTION_SDATA2 __declspec(section ".sdata2")
#else
#define SECTION_SDATA2
#endif

SECTION_SDATA2 u32 MSL_Math_804DE1B0 = 0xBF000030;
SECTION_SDATA2 u32 MSL_Math_804DE1B4 = 0x3EAAAA36;
SECTION_SDATA2 const FloatU32 __float_nan = { 0x7FFFFFFF };
SECTION_SDATA2 const FloatU32 __float_huge = { 0x7F800000 };

/// Math lookup tables - defined in math_data.c
/// Keeping them in a separate compilation unit prevents the compiler from
/// hoisting array base addresses, which is needed to match the original code.
extern const float __ln_F[];
extern const float __one_over_F[];
extern const float __sincos_on_quadrant[];
extern const float __sincos_poly[];

/*
Computes the natural logarithm of x.

Algorithm:
- Decompose `x = 2^E * 1.M`, where `E` is the exponent, `M` are the mantissa
bits and `1.M` denotes the binary number with integer part 1 and fractional
bits `M`
- Observe that `ln(x) = ln(2)*E + ln(1.M)`. It remains to compute `ln(1.M)`.
- Choose a 7 bit mantissa `m` such that `1.m` best approximates `1.M`. Details:
  - Let `m` be the 7 most significant bits of `M`, then `1.m` already is a good
approximation. But when the 8'th most significant bit of `M` is set, we
increment `m` accordingly by 1 bit to get an equal or better approximation.
- Next approximate `ln(1.M) = ln(y + h)` with `y=1.m` and `h=1.M - 1.m` using a
Taylor expansion at `y`. Maths detour:
    - We have `ln(y + h) = ln(y) + h/y - (h/y)^2 / 2 + (h/y)^3 / 3 - ...`
    - So for `H := h/y` we have `ln(y + h) = ln(y) + H + H^2 * (-0.5 + H/3 -
...)`
    - I don't understand how this works, but the algorithm uses this
approximation formula: `ln(1.M) = ln(y + h) = ln(y) + H + H^2 * (H*0.000005086
- 0.500003)`
- In the formula above, the algorithm computes `ln(y) = ln(1.m)` using a lookup
table, then computes `H = h * 1/y = h * 1/1.m` using another lookup table for
`1/1.m`.
*/
float logf(float x)
{
    switch (*(u32*) &x & EXP_MASK) {
    default: /* x is normal */
    {
        u32 raw_fm;
        u32 raw_fM;
        u32 coef[2];
        u32 mant_bits;
        u32 raw_x;
        s32 E;
        s32 m;

        coef[0] = MSL_Math_804DE1B0;
        raw_x = *(u32*) &x;
        coef[1] = MSL_Math_804DE1B4;
        mant_bits = raw_x & MANT_MASK;
        E = F32_UNBIASED_EXPONENT(raw_x);
        m = F32_HIGH_MANTISSA_BITS(raw_x);

        if (F32_LOW_MANTISSA_BITS(raw_x)) {
            register float h2_poly;
            register float H;

            raw_fm = (raw_x & 0x7F0000) | EXP_ZERO;
            raw_fM = mant_bits | EXP_ZERO;

            if (raw_x & 0x8000) {
                raw_fm += 0x10000;
                m += 1;
            }

            H = F32_BIT_CAST(raw_fM) - F32_BIT_CAST(raw_fm);
            H = H * __one_over_F[m];
            h2_poly = H * H * (H * *(float*) &coef[1] + *(float*) &coef[0]);
            return (LN2 * (float) E + __ln_F[m]) + (H + h2_poly);
        }
        return LN2 * (float) E + __ln_F[m];
    }
    case EXP_MASK: {
        if (*(u32*) &x & MANT_MASK) {
            return x;
        } else {
            return (*(u32*) &x & SIGN_BIT) ? __float_nan.f : __float_huge.f;
        }
    }
    case 0:
        return -__float_huge.f;
    }
}
