#include <platform.h>

#define EXP_MASK 0x7F800000
#define EXP_ZERO 0x3F800000 // hex representation of (float)0.0f
#define MANT_MASK 0x007FFFFF
#define SIGN_BIT 0x80000000
#define F32_BIT_CAST(raw_x) (*(float*) &raw_x)
#define F32_UNBIASED_EXPONENT(raw_x)                                          \
    (((raw_x & 0xFF800000) >> 23) - /*exponent bias*/ 127)
#define F32_HIGH_MANTISSA_BITS(raw_x)                                         \
    ((raw_x >> 16) & 0x7F) // 7 most significant mantissa bits
#define F32_LOW_MANTISSA_BITS(raw_x)                                          \
    (raw_x & 0xFFFF)   // remaining 16 mantissa bits
#define LN2 0.6931472f // natural logarithm of 2

// TODO: use standard library constants, because this definition seems to be
// platform dependant
float float_nan = 0.0 / 0.0;
float float_inf = 1.0e100 * 1.0e100;

// __ln_F[n] = ln(1.0 + n/128) for n = 0 .. 128
const float __ln_F[0x81] = {
    0.0f,         0.0077821403f, 0.015504186f, 0.023167059f, 0.030771658f,
    0.038318865f, 0.045809537f,  0.053244516f, 0.06062462f,  0.06795066f,
    0.07522342f,  0.08244367f,   0.089612156f, 0.09672963f,  0.103796795f,
    0.11081436f,  0.11778303f,   0.12470348f,  0.13157636f,  0.13840233f,
    0.14518201f,  0.15191604f,   0.15860502f,  0.16524957f,  0.17185026f,
    0.17840765f,  0.18492234f,   0.19139485f,  0.19782574f,  0.20421554f,
    0.21056476f,  0.21687394f,   0.22314355f,  0.2293741f,   0.23556606f,
    0.24171993f,  0.24783616f,   0.25391522f,  0.25995752f,  0.26596355f,
    0.2719337f,   0.27786845f,   0.28376818f,  0.2896333f,   0.29546422f,
    0.30126134f,  0.30702505f,   0.3127557f,   0.31845373f,  0.32411948f,
    0.32975328f,  0.33535555f,   0.3409266f,   0.34646678f,  0.35197642f,
    0.35745588f,  0.3629055f,    0.36832556f,  0.3737164f,   0.37907836f,
    0.3844117f,   0.38971674f,   0.3949938f,   0.40024316f,  0.4054651f,
    0.41065994f,  0.4158279f,    0.4209693f,   0.4260844f,   0.43117347f,
    0.43623677f,  0.44127455f,   0.4462871f,   0.45127463f,  0.45623744f,
    0.4611757f,   0.46608973f,   0.47097972f,  0.4758459f,   0.48068854f,
    0.48550782f,  0.490304f,     0.49507725f,  0.49982786f,  0.504556f,
    0.5092619f,   0.51394576f,   0.51860774f,  0.52324814f,  0.5278671f,
    0.5324648f,   0.5370415f,    0.5415973f,   0.54613245f,  0.55064714f,
    0.5551415f,   0.5596158f,    0.56407017f,  0.56850475f,  0.5729197f,
    0.5773154f,   0.58169174f,   0.586049f,    0.59038746f,  0.59470713f,
    0.5990082f,   0.60329086f,   0.60755527f,  0.61180156f,  0.61602986f,
    0.6202404f,   0.6244333f,    0.62860864f,  0.63276666f,  0.63690746f,
    0.6410312f,   0.64513797f,   0.649228f,    0.6533013f,   0.65735805f,
    0.6613985f,   0.6654226f,    0.6694307f,   0.6734227f,   0.6773988f,
    0.68135923f,  0.685304f,     0.6892333f,   0.6931472f,
}; /* const */

// __one_over_F[n] = 1.0 / (1.0 + n/128) for n = 0..128
const float __one_over_F[0x81] = {
    1.0f,        0.99224806f, 0.9846154f,  0.97709924f, 0.969697f,
    0.96240604f, 0.95522386f, 0.94814813f, 0.9411765f,  0.93430656f,
    0.92753625f, 0.92086333f, 0.9142857f,  0.9078014f,  0.90140843f,
    0.8951049f,  0.8888889f,  0.8827586f,  0.8767123f,  0.8707483f,
    0.8648649f,  0.8590604f,  0.85333335f, 0.8476821f,  0.84210527f,
    0.8366013f,  0.83116883f, 0.82580644f, 0.82051283f, 0.81528664f,
    0.8101266f,  0.8050314f,  0.8f,        0.7950311f,  0.79012346f,
    0.78527606f, 0.7804878f,  0.77575755f, 0.7710843f,  0.7664671f,
    0.7619048f,  0.75739646f, 0.7529412f,  0.748538f,   0.74418604f,
    0.7398844f,  0.7356322f,  0.73142856f, 0.72727275f, 0.72316384f,
    0.71910113f, 0.7150838f,  0.7111111f,  0.70718235f, 0.7032967f,
    0.69945353f, 0.6956522f,  0.6918919f,  0.68817204f, 0.684492f,
    0.68085104f, 0.67724866f, 0.67368424f, 0.6701571f,  0.6666667f,
    0.6632124f,  0.6597938f,  0.6564103f,  0.6530612f,  0.6497462f,
    0.64646465f, 0.6432161f,  0.64f,       0.6368159f,  0.63366336f,
    0.63054186f, 0.627451f,   0.62439024f, 0.6213592f,  0.6183575f,
    0.61538464f, 0.61244017f, 0.60952383f, 0.6066351f,  0.6037736f,
    0.600939f,   0.5981308f,  0.59534883f, 0.5925926f,  0.58986175f,
    0.58715594f, 0.58447486f, 0.58181816f, 0.57918555f, 0.5765766f,
    0.57399106f, 0.5714286f,  0.5688889f,  0.5663717f,  0.5638766f,
    0.5614035f,  0.558952f,   0.5565217f,  0.55411255f, 0.55172414f,
    0.5493562f,  0.5470086f,  0.54468083f, 0.5423729f,  0.54008436f,
    0.53781515f, 0.53556484f, 0.53333336f, 0.53112036f, 0.5289256f,
    0.52674896f, 0.52459013f, 0.52244896f, 0.5203252f,  0.51821864f,
    0.516129f,   0.5140562f,  0.512f,      0.5099602f,  0.50793654f,
    0.5059289f,  0.503937f,   0.50196075f, 0.5f,
}; /* const */

const float __sincos_on_quadrant[] = { 0, 1, 1, 0, 0, -1, -1, 0 };

const float __sincos_poly[] = {
    0.0000035287617,
    0.0000003089747,
    -0.0003259365,
    -0.00003657235,
    0.015854323,
    0.0024903931,
    -0.30842513,
    -0.08074551,
    1,
    0.7853982,
};

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
float logf(float x /*@f1*/)
{
    u32 raw_x /*@r4*/ =
        *(u32*) &x; // @8 implemented via: x@sp8 = x@f1; x@r4 = x@sp8
    // @14  4:r0=0x7f80_0000; 10:r3=x@r4 & EXP_MASK; 14:cmpw r3,0x7f80_0000@r0
    switch (raw_x & EXP_MASK) {
    default: /*x is normal*/
    {
        float C[2] = { -0.500003, 0.000005086 }; //@28
        // C[0] = 0xbf000030@(r2-0x1830=0x804DE1B0), stored in sp10 @28,30
        // C[1] = 0x3eaaaa36@(r2-0x182C=0x804DE1B4), stored in sp14 @34,40

        // decompose x = 2^E * 1.M in exponent E and mantissa M
        s32 E = F32_UNBIASED_EXPONENT(raw_x);
        s32 m = F32_HIGH_MANTISSA_BITS(
            raw_x); // @4c the 7 most significant mantissa bits
        float H;
        if (F32_LOW_MANTISSA_BITS(raw_x)) // condition @28, if @50
        {
            //@54
            u32 raw_fm = (raw_x & 0x7F0000) | EXP_ZERO;  // = 1.m
            u32 raw_fM = (raw_x & MANT_MASK) | EXP_ZERO; // = 1.M
                                                         // float fm, fM, h;

            // is the 8'th most significant mantissa bit set?
            if (raw_x & 0x8000) // condition @34, if @6c
            {
                //@70
                raw_fm += 0x10000; // @74
                m += 1;            // @70,@78,@7c
            }
            //@80

            // fM = F32_BIT_CAST(raw_fM); // @84 result fM@f2
            // fm = F32_BIT_CAST(raw_fm); // @88 result fm@f0
            // h = fM - fm; // @a0 result h@f6

            // reciprocal_table_803B9154e1 base pointer: @80,90
            // load table item into f0 with index m@r8: @8c,98,a4, result in f0
            // H = h * reciprocal_table_803B9154[m]; // = h / 1.m  code @b4,
            // result in H@f6

            H = (F32_BIT_CAST(raw_fM) - F32_BIT_CAST(raw_fm)) *
                __one_over_F[m];

            // return ln(2)*E + ln(1.m) + H * H*H * (H * (-0.500003) +
            // 0.000005086), this is an approximation of the Taylor series.
            // code positions:
            // convert the E@r7 integer to float@f3: @9c,ac,b0,bc,c4,c8,dc
            // lookup __ln_F[m@r4{index already multiplied by 4}]:
            // @a8,c0,cc,e0, result in f1 load 0.6931472f =
            // 0x3f317218@(r2-0x1820=0x804DE1C0) into f5: @d4 compute
            // 0.6931472f*exp + __ln_F[m]: @e8
            return LN2 * E + __ln_F[m] + H + H * H * (H * C[1] + C[0]);
        }
        return LN2 * E + __ln_F[m]; //@f8
    }
    case EXP_MASK: //@134
    {
        if (raw_x & MANT_MASK) {
            // @13c
            return x; // x is nan
        } else {
            // @144
            return (raw_x & SIGN_BIT) ? /*x=-inf*/ float_nan
                                      : /*x=inf*/ float_inf;
        }
    }
    case 0: /* @15c x is subnormal or zero*/
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
