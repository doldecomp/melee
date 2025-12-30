#include "lbrefract.h"

#include "lb/types.h"

#include <math.h>
#include <dolphin/gx/GXTexture.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/state.h>
#include <MetroTRK/intrinsics.h>

extern HSD_DObjInfo hsdDObj;

/* 021F34 */ static void fn_80021F34(lbRefract_CallbackData* arg0, s32 arg1,
                                     u32 arg2, u32 arg3, u8 arg4, u8 arg5,
                                     u8 arg6);
/* 021F70 */ static UNK_RET fn_80021F70(UNK_PARAMS);
/* 021FB4 */ static UNK_RET fn_80021FB4(UNK_PARAMS);
/* 021FF8 */ static UNK_RET fn_80021FF8(UNK_PARAMS);
/* 02206C */ static UNK_RET fn_8002206C(UNK_PARAMS);
/* 022608 */ static void fn_80022608(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode);
/* 022120 */ static void fn_80022120(lbRefract_CallbackData* arg0, s32 arg1,
                                     u32 arg2, u32* arg3, u32* arg4, u8* arg5,
                                     u8* arg6);
/* 022DF8 */ static inline float lbRefract_80022DF8(float x);
/* 02219C */ s32 lbRefract_8002219C(lbRefract_CallbackData*, s32, s32, u16,
                                    u16);

static int lbl_804336D0[0x10];

extern float MSL_TrigF_80400770[], MSL_TrigF_80400774[];

#define SIGN_BIT (1 << 31)
#define BITWISE(f) (*(u32*) &f)
#define SIGNED_BITWISE(f) ((s32) BITWISE(f))
#define GET_SIGN_BIT(f) (SIGNED_BITWISE(f) & SIGN_BIT)
#define BITWISE_PI_2 0x3FC90FDB

#define NAN MSL_TrigF_80400770[0]
#define INF MSL_TrigF_80400774[0]

static void fn_80021F34(lbRefract_CallbackData* arg0, s32 arg1, u32 arg2,
                        u32 arg3, u8 arg4, u8 arg5, u8 arg6)
{
    s32 t0, t1, t2;
    u8* ptr;

    t0 = arg0->unk4;
    t1 = arg2 >> 2;
    t2 = arg0->unk0;
    ptr = (u8*)(t2 + t1 * t0 + ((arg1 << 3) & 0xFFFFFFE0));
    t0 = ((arg1 & 3) + ((arg2 << 2) & 0xC)) << 1;
    ptr[t0] = arg6;
    ptr[t0 + 1] = arg5;
}

void fn_80022120(lbRefract_CallbackData* arg0, s32 arg1, u32 arg2, u32* arg3,
                 u32* arg4, u8* arg5, u8* arg6)
{
    s32 temp_r10;
    s32 temp_r4;

    temp_r10 = arg0->unk0 +
               (((arg2 >> 2U) * arg0->unk4) + ((arg1 * 0x10) & 0xFFFFFFC0));
    temp_r4 = ((arg1 & 3) + ((arg2 * 4) & 0xC)) * 2;
    if (arg6 != NULL) {
        *arg6 = temp_r10 + temp_r4;
    }
    if (arg3 != NULL) {
        *arg3 = temp_r10 + temp_r4 + 0x01;
    }
    if (arg4 != NULL) {
        *arg4 = temp_r10 + temp_r4 + 0x20;
    }
    if (arg5 != NULL) {
        *arg5 = (s32) (temp_r10 + temp_r4 + 0x21);
    }
}

s32 lbRefract_8002219C(lbRefract_CallbackData* arg0, s32 arg1, s32 arg2,
                       u16 arg3, u16 arg4)
{
    arg0->unk0 = arg1;
    arg0->unk1 = arg2;
    arg0->unk2 = (s32) arg3;
    arg0->unk3 = (s32) arg4;
    arg0->unk5 = GXGetTexBufferSize(arg3, arg4, arg2, 0U, 0U);
    switch (arg2) { /* irregular */
    case 3:
        arg0->callback0 = fn_80021F34;
        arg0->callback1 = fn_80021FF8;
        arg0->unk4 = (arg3 * 8) & 0xFFFFFFE0;
    block_11:
        return 0;
    case 4:
        arg0->callback0 = fn_80021F70;
        arg0->callback1 = fn_8002206C;
        arg0->unk4 = (arg3 * 8) & 0xFFFFFFE0;
        goto block_11;
    case 6:
        arg0->callback0 = fn_80021FB4;
        arg0->callback1 = fn_80022120;
        arg0->unk4 = (arg3 * 0x10) & 0xFFFFFFC0;
        goto block_11;
    case 5:
        /* fallthrough */
    default:
        return -1;
    }
}

void lbRefract_80022560(void)
{
    if (lbl_804336D0[0] != 0) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x140, 0xF0, 4, 1);
        GXCopyTex((void*)lbl_804336D0[1], 0);
        GXPixModeSync();
        GXInvalidateTexAll();
    }
}


void lbRefract_800225D4(void)
{
    GXSetTevDirect(0);
    GXSetNumIndStages(0);
    HSD_StateInvalidate(-1);
}

void fn_80022608(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    hsdDObj.disp(dobj, vmtx, pmtx, rendermode);
    GXSetTevDirect(0);
    GXSetNumIndStages(0);
    HSD_StateInvalidate(-1);
}

void lbRefract_80022BB8(void)
{
    lbl_804336D0[0] += 1;
}

void lbRefract_80022BD0(void)
{
    lbl_804336D0[0] -= 1;
    if (lbl_804336D0[0] < 0) {
        OSReport("lbRefSetUnuse error!\n");
        __assert("lbrefract.c", 0x31c, "0");
    }
}

float atan2f(float y, float x)
{
    if (GET_SIGN_BIT(x) == GET_SIGN_BIT(y)) {
        if (GET_SIGN_BIT(x) != 0) {
            return x == -0.0f ? (float) -M_PI_2 : atanf(y / x) - (float) M_PI;
        }

        return x ? atanf(y / x) : (float) M_PI_2;
    }

    if (x < 0.0f) {
        return (float) M_PI + atanf(y / x);
    }

    if (x) {
        return atanf(y / x);
    }

    *(u32*) &y = GET_SIGN_BIT(y) + BITWISE_PI_2;

    return y;
}

float acosf(float x)
{
    float result = 1.0F - x * x;
    if (result > 0) {
        float guess;
        guess = __frsqrte(result);
        guess = 0.5f * guess * (3.0f - guess * guess * result);
        guess = 0.5f * guess * (3.0f - guess * guess * result);
        guess = 0.5f * guess * (3.0f - guess * guess * result);
        result = guess;
    } else if (result) {
        result = NAN;
    } else {
        result = INF;
    }
    return (float) M_PI_2 - atanf(x * result);
}

float asinf(float x)
{
    return atanf(x * lbRefract_80022DF8(-(x * x - 1.0f)));
}

static inline float lbRefract_80022DF8(float x)
{
    if (x > 0.0f) {
        float guess;
        guess = __frsqrte(x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        guess = 0.5f * guess * (3.0f - guess * guess * x);
        return guess;
    }

    if (x) {
        return NAN;
    }

    return INF;
}

#define SILVER_RATIO_1_CONJUGATE lbRefract3_804D7DD4

#define BITWISE_INF 0x7F800000 /* = +Infinity */
#define BITWISE_0_5 0x3F000000 /* = 0.5f */
#define BITWISE_1_0 0x3F800000 /* = 1.0f */
#define BITWISE_2_0 0x40000000 /* = 2.0f */

#define BITWISE_THRESHOLD_0 0x3F08D5B9 /* = 0.534511148929596f */
#define BITWISE_THRESHOLD_1 0x3F521801 /* = 0.8206787705421448f */
#define BITWISE_THRESHOLD_2 0x3F9BF7EC /* = 1.218503475189209f */
#define BITWISE_THRESHOLD_3 0x3FEF789E /* = 1.870868444442749f */

static const float atanf_lookup[] = {
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

float atanf(float x)
{
    float const silver_ratio = 2.4142136573791504f;
    float const silver_ratio_conjugate = 0.4142135679721832f;

    float result;
    const float* lookup_ptr;
    s32 lookup_index = -1;
    bool x_ge_ratio = false;
    s32 sign_bit_x = BITWISE(x) & SIGN_BIT;

    BITWISE(x) &= ~SIGN_BIT;

    if (x >= silver_ratio) {
        x_ge_ratio = true;
        result = 1.0f / x;
    } else if (silver_ratio_conjugate < x) {
        lookup_index = 0;
        switch (BITWISE(x) & BITWISE_INF) {
        case BITWISE_0_5: {
            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_0)) {
                lookup_index = 1;
            }

            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_1)) {
                lookup_index += 1;
            }

            break;
        }
        case BITWISE_1_0: {
            lookup_index = 2;
            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_2)) {
                lookup_index = 3;
            }

            if (!(SIGNED_BITWISE(x) < BITWISE_THRESHOLD_3)) {
                lookup_index += 1;
            }

            break;
        }
        case BITWISE_2_0: {
            lookup_index = 4;
            break;
        }
        }
        {
            float offset_39;
            float offset_33;
            lookup_ptr = &atanf_lookup[lookup_index];
            offset_39 = lookup_ptr[39];
            offset_33 = lookup_ptr[33];

            result = 1.0f / (offset_33 + (x + offset_39));
            result = __fnmsubs(result, lookup_ptr[7], offset_33) +
                     __fnmsubs(result, lookup_ptr[13], offset_39);
        }
    } else {
        result = x;
    }

    {
        float result_squared = result * result;
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
        result -= (float) M_PI_2;
        return sign_bit_x ? result : -result;
    }

    BITWISE(result) |= sign_bit_x;
    return result;
}
