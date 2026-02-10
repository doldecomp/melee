#include "math.h"

#include <platform.h>

#define EXP_MASK 0x7F800000
#define EXP_ZERO 0x3F800000 // hex representation of (float)0.0f
#define MANT_MASK 0x007FFFFF
#define SIGN_BIT 0x80000000
#define F32_BIT_CAST(raw_x) (*(float*) &raw_x)

typedef union {
    float f;
    u32 u;
} FloatU32;
#define F32_UNBIASED_EXPONENT(raw_x)                                          \
    (((raw_x & 0xFF800000) >> 23) - /*exponent bias*/ 127)
#define F32_HIGH_MANTISSA_BITS(raw_x)                                         \
    ((raw_x >> 16) & 0x7F) // 7 most significant mantissa bits
#define F32_LOW_MANTISSA_BITS(raw_x)                                          \
    (raw_x & 0xFFFF)   // remaining 16 mantissa bits
#define LN2 0.6931472f // natural logarithm of 2

/// @todo: use standard library constants, because this definition seems to be
/// platform dependant
float float_nan = 0.0 / 0.0;
float float_inf = 1.0e100 * 1.0e100;

/// Math lookup tables - defined in math_data.c
/// Keeping them in a separate compilation unit prevents the compiler from
/// hoisting array base addresses, which is needed to match the original code.
extern const float __ln_F[];
extern const float __one_over_F[];
extern const float __sincos_on_quadrant[];
extern const float __sincos_poly[];

/// logf Taylor series coefficients - stored as u32 bit patterns in math_data.c
/// to get the right codegen (lwz load from global)
extern const u32 __logf_C0_bits; // 0xBF000030 = -0.500003F
extern const u32 __logf_C1_bits; // 0x3EAA9F44 = 0.333329856F

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
    u32 exp_bits = *(u32*) &x & EXP_MASK;

    switch (exp_bits) {
    default: /* x is normal */
    {
        u32 coef[2];
        u32 mant_bits;
        u32 raw_x;
        s32 E;
        s32 m;

        coef[0] = __logf_C0_bits;
        raw_x = *(u32*) &x;
        coef[1] = __logf_C1_bits;
        mant_bits = raw_x & MANT_MASK;
        E = F32_UNBIASED_EXPONENT(raw_x);
        m = F32_HIGH_MANTISSA_BITS(raw_x);

        if (F32_LOW_MANTISSA_BITS(raw_x)) {
            u32 raw_fm = (raw_x & 0x7F0000) | EXP_ZERO;
            u32 raw_fM = mant_bits | EXP_ZERO;
            float C1;
            float H;
            float C0;
            float new_var;
            float poly;
            float h2_poly;

            if (raw_x & 0x8000) {
                raw_fm += 0x10000;
                m += 1;
            }

            C1 = *(float*) &coef[1];
            H = F32_BIT_CAST(raw_fM) - F32_BIT_CAST(raw_fm);
            H = H * __one_over_F[m];
            C0 = *(float*) &coef[0];

            new_var = H * H;
            poly = H * C1 + C0;
            h2_poly = new_var * poly;
            return (LN2 * E + __ln_F[m]) + (H + h2_poly);
        }
        return LN2 * E + __ln_F[m];
    }
    case EXP_MASK: {
        u32 raw_x = *(u32*) &x;
        if (raw_x & MANT_MASK) {
            return x;
        } else {
            return (raw_x & SIGN_BIT) ? float_nan : float_inf;
        }
    }
    case 0:
        return -float_inf;
    }
}
/*
matching `__one_over_F[m]` (currently line 72 in the C code above)

target code:
r8 = array index
80: lis     r3,lbl_803B9154@ha // load array base pointer 0x803C0000-28848
8c: rlwinm  r4,r8,2,0,0x1d   // multiply index by 4 = sizeof(float)
90: addi    r0,r3,lbl_803B9154@l
98: add     r3,r0,r4         // r3 = base_pointer + 4*index
a4: lfs     f1,0(r3)         // deref the pointer

a8: lis     r3, 0x803C       // load array base pointer 0x803C0000-28848
c0: subi	r0, r3, 28848
cc: add     r3,r0,r4         // r3 = base_pointer + 4*index
e0: lfs     f1,0(r3)         // deref the pointer

my code:
r8 = array index
4:  lis     r3,...data.0@ha    // load array base pointer
10: addi    r5,r3,...data.0@l
80: rlwinm  r4,r8,2,0,0x1d     //  multiply index by 4 = sizeof(float)
90: add     r3,r5,r4           // r3 = base_pointer + 4*index
a0: lfs     f3, 0x204(r3)      // load __one_over_F[m]
ac: lfsx    f0,r5,r4           // load float32 from address r5+r4, = __ln_F[m]
*/
