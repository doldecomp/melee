#include <melee/lb/lbrefract.h>

#include <math.h>
#include <MetroTRK/intrinsics.h>

#pragma region trigf
extern f32 lbl_80400770[], lbl_80400774[];
#pragma endregion

/* static */ extern const f32 lbl_804D7DB0; // = 0x80000000;
/* static */ extern const f32 lbl_804D7DB4; // = -1.5707963705062866;
/* static */ extern const f32 lbl_804D7DB8; // = 3.1415927410125732;
/* static */ extern const f32 lbl_804D7DBC; // = 0.0;
/* static */ extern const f32 lbl_804D7DC0; // = 1.5707963705062866;
/* static */ extern const f32 lbl_804D7DC4; // = 1.0;
/* static */ extern const f32 lbl_804D7DC8; // = 0.5;
/* static */ extern const f32 lbl_804D7DCC; // = 3.0;
/* static */ extern const f32 lbl_804D7DD0; // = 2.4142136573791504;
/* static */ extern const f32 lbl_804D7DD4; // = 0.4142135679721832;

#define SIGN_BIT (1 << 31)
#define BITWISE(f) (*(u32*) &f)
#define SIGNED_BITWISE(f) ((s32) BITWISE(f))
#define GET_SIGN_BIT(f) (SIGNED_BITWISE(f) & SIGN_BIT)
#define BITWISE_PI_2 0x3FC90FDB

#define NEGATIVE_ZERO lbl_804D7DB0
#define NEGATIVE_PI_2 lbl_804D7DB4
#define PI lbl_804D7DB8
#define ZERO lbl_804D7DBC
#define PI_2 lbl_804D7DC0
#define ONE lbl_804D7DC4
#define HALF lbl_804D7DC8
#define THREE lbl_804D7DCC
#define NAN lbl_80400770[0]
#define INF lbl_80400774[0]

f32 atan2f(f32 y, f32 x)
{
    if (GET_SIGN_BIT(x) == GET_SIGN_BIT(y)) {
        if (GET_SIGN_BIT(x) != 0)
            return NEGATIVE_ZERO == x ? NEGATIVE_PI_2 : atanf(y / x) - PI;

        return x != ZERO ? atanf(y / x) : PI_2;
    }

    if (x < ZERO)
        return PI + atanf(y / x);

    if (x != ZERO)
        return atanf(y / x);

    *(u32*) &y = GET_SIGN_BIT(y) + BITWISE_PI_2;

    return y;
}

static f32 local_80022DF8(f32);
f32 atanf(f32);

#if MUST_MATCH

#pragma push
/// @todo @frank
asm f32 acosf(f32)
{ // clang-format off
    nofralloc
/* 80022D1C 0001F8FC  7C 08 02 A6 */	mflr r0
/* 80022D20 0001F900  90 01 00 04 */	stw r0, 4(r1)
/* 80022D24 0001F904  94 21 FF F8 */	stwu r1, -8(r1)
/* 80022D28 0001F908  C0 42 83 E4 */	lfs f2, ONE(r2)
/* 80022D2C 0001F90C  C0 02 83 DC */	lfs f0, ZERO(r2)
/* 80022D30 0001F910  EC A1 10 7C */	fnmsubs f5, f1, f1, f2
/* 80022D34 0001F914  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 80022D38 0001F918  40 81 00 48 */	ble lbl_80022D80
/* 80022D3C 0001F91C  FC 40 28 34 */	frsqrte f2, f5
/* 80022D40 0001F920  C0 82 83 E8 */	lfs f4, HALF(r2)
/* 80022D44 0001F924  C0 62 83 EC */	lfs f3, THREE(r2)
/* 80022D48 0001F928  FC 40 10 18 */	frsp f2, f2
/* 80022D4C 0001F92C  EC 02 00 B2 */	fmuls f0, f2, f2
/* 80022D50 0001F930  EC 44 00 B2 */	fmuls f2, f4, f2
/* 80022D54 0001F934  EC 05 18 3C */	fnmsubs f0, f5, f0, f3
/* 80022D58 0001F938  EC 42 00 32 */	fmuls f2, f2, f0
/* 80022D5C 0001F93C  EC 02 00 B2 */	fmuls f0, f2, f2
/* 80022D60 0001F940  EC 44 00 B2 */	fmuls f2, f4, f2
/* 80022D64 0001F944  EC 05 18 3C */	fnmsubs f0, f5, f0, f3
/* 80022D68 0001F948  EC 42 00 32 */	fmuls f2, f2, f0
/* 80022D6C 0001F94C  EC 02 00 B2 */	fmuls f0, f2, f2
/* 80022D70 0001F950  EC 44 00 B2 */	fmuls f2, f4, f2
/* 80022D74 0001F954  EC 05 18 3C */	fnmsubs f0, f5, f0, f3
/* 80022D78 0001F958  EC 02 00 32 */	fmuls f0, f2, f0
/* 80022D7C 0001F95C  48 00 00 20 */	b lbl_80022D9C
lbl_80022D80:
/* 80022D80 0001F960  FC 05 00 00 */	fcmpu cr0, f5, f0
/* 80022D84 0001F964  41 82 00 10 */	beq lbl_80022D94
/* 80022D88 0001F968  3C 60 80 40 */	lis r3, lbl_80400770@ha
/* 80022D8C 0001F96C  C0 03 07 70 */	lfs f0, lbl_80400770@l(r3)
/* 80022D90 0001F970  48 00 00 0C */	b lbl_80022D9C
lbl_80022D94:
/* 80022D94 0001F974  3C 60 80 40 */	lis r3, lbl_80400774@ha
/* 80022D98 0001F978  C0 03 07 74 */	lfs f0, lbl_80400774@l(r3)
lbl_80022D9C:
/* 80022D9C 0001F97C  EC 21 00 32 */	fmuls f1, f1, f0
/* 80022DA0 0001F980  48 00 00 C9 */	bl atanf
/* 80022DA4 0001F984  C0 02 83 E0 */	lfs f0, PI_2(r2)
/* 80022DA8 0001F988  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80022DAC 0001F98C  EC 20 08 28 */	fsubs f1, f0, f1
/* 80022DB0 0001F990  38 21 00 08 */	addi r1, r1, 8
/* 80022DB4 0001F994  7C 08 03 A6 */	mtlr r0
/* 80022DB8 0001F998  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

f32 acosf(f32 x)
{
    f32 result = -(x * x - ONE);
    result = local_80022DF8(result) * x;
    result = atanf(result);
    result = PI_2 - result;
    return result;
}

#endif

f32 func_80022DBC(f32 x)
{
    return atanf(x * local_80022DF8(-(x * x - ONE)));
}

static inline f32 local_80022DF8(f32 x)
{
    if (x > ZERO) {
        f32 guess;
        guess = __frsqrte(x);
        guess = HALF * guess * (THREE - guess * guess * x);
        guess = HALF * guess * (THREE - guess * guess * x);
        guess = HALF * guess * (THREE - guess * guess * x);
        return guess;
    }

    if (x != ZERO)
        return NAN;

    return INF;
}

#define SILVER_RATIO_1 lbl_804D7DD0
#define SILVER_RATIO_1_CONJUGATE lbl_804D7DD4

#define BITWISE_INF 0x7F800000 /* = +Infinity */
#define BITWISE_0_5 0x3F000000 /* = 0.5f */
#define BITWISE_1_0 0x3F800000 /* = ONE */
#define BITWISE_2_0 0x40000000 /* = 2.0f */

#define BITWISE_THRESHOLD_0 0x3F08D5B9 /* = 0.534511148929596f */
#define BITWISE_THRESHOLD_1 0x3F521801 /* = 0.8206787705421448f */
#define BITWISE_THRESHOLD_2 0x3F9BF7EC /* = 1.218503475189209f */
#define BITWISE_THRESHOLD_3 0x3FEF789E /* = 1.870868444442749f */

static const f32 atanf_lookup[] = {
    1.0,
    -0.3333333134651184,
    0.1999988704919815,
    -0.14281649887561798,
    0.11041180044412613,
    -0.08459755778312683,
    0.04714243486523628,
    6.828420162200928,
    3.239828109741211,
    2.0,
    1.4464620351791382,
    1.1715729236602783,
    1.039566159248352,
    7.1350000325764995e-06,
    8.200000252145401e-07,
    0.0,
    6.299999881775875e-07,
    0.0,
    0.0,
    0.0,
    0.3926900029182434,
    0.5890486240386963,
    0.7853981256484985,
    0.9817469716072083,
    1.1780970096588135,
    1.3744460344314575,
    0.0,
    9.081698408408556e-06,
    2.3000000126671694e-08,
    6.30000016599297e-08,
    7.040000014058023e-07,
    2.499999993688107e-07,
    7.900000014160469e-07,
    2.414212942123413,
    1.4966057538986206,
    1.0,
    0.6681786179542542,
    0.4142135679721832,
    0.1989123672246933,
    5.620000251838064e-07,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
    0.0,
};

f32 atanf(f32 x)
{
    f32 result;
    const f32* lookup_ptr;
    s32 lookup_index = -1;
    bool x_ge_ratio = false;
    s32 sign_bit_x = BITWISE(x) & SIGN_BIT;

    BITWISE(x) &= ~SIGN_BIT;

    if (x >= SILVER_RATIO_1) {
        x_ge_ratio = true;
        result = ONE / x;
    } else if (SILVER_RATIO_1_CONJUGATE < x) {
        lookup_index = 0;
        switch (BITWISE(x) & BITWISE_INF) {
        case BITWISE_0_5: {
            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_0))
                lookup_index = 1;

            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_1))
                lookup_index += 1;

            break;
        }
        case BITWISE_1_0: {
            lookup_index = 2;
            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_2))
                lookup_index = 3;

            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_3))
                lookup_index += 1;

            break;
        }
        case BITWISE_2_0: {
            lookup_index = 4;
            break;
        }
        }
        {
            f32 offset_39;
            f32 offset_33;
            lookup_ptr = &atanf_lookup[lookup_index];
            offset_39 = lookup_ptr[39];
            offset_33 = lookup_ptr[33];

            result = ONE / (offset_33 + (x + offset_39));
            result = __fnmsubs(result, lookup_ptr[7], offset_33) +
                     __fnmsubs(result, lookup_ptr[13], offset_39);
        }
    } else {
        result = x;
    }

    {
        f32 result_squared = result * result;
        lookup_ptr = &atanf_lookup[lookup_index];

        // clang-format off
        result = result *
            result_squared * (
                result_squared * (
                    result_squared * (
                        result_squared * (
                            result_squared * (
                                result_squared * (
                                    atanf_lookup[6]
                                ) + atanf_lookup[5]
                            ) + atanf_lookup[4]
                        ) + atanf_lookup[3]
                    ) + atanf_lookup[2]
                ) + atanf_lookup[1]
            ) + result;
        // clang-format on

        result += lookup_ptr[27];
        result += lookup_ptr[20];
    }

    if (x_ge_ratio) {
        result -= PI_2;
        return sign_bit_x ? result : -result;
    }

    BITWISE(result) |= sign_bit_x;
    return result;
}
