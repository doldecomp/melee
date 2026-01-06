/**
 * @file lbrefract.c
 * @brief Refraction visual effects using GX indirect textures.
 *
 * Uses reference counting to track active effect users.
 * Supports IA4, IA8, and RGBA8 texture formats.
 */

#include "lbrefract.h"

#include "lb/types.h"

#include <math.h>
#include <dolphin/gx/GXTexture.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/state.h>
#include <MetroTRK/intrinsics.h>

extern HSD_DObjInfo hsdDObj;

/// @brief Write IA4 texture coordinate to refraction buffer.
/* 021F34 */ static void
lbRefract_WriteTexCoordIA4(lbRefract_CallbackData* data, s32 row, u32 col,
                           u32 arg3, u8 arg4, u8 intensity, u8 alpha);
/* 021F70 */ static UNK_RET fn_80021F70(UNK_PARAMS);
/* 021FB4 */ static UNK_RET fn_80021FB4(UNK_PARAMS);
/* 021FF8 */ static UNK_RET fn_80021FF8(UNK_PARAMS);
/* 02206C */ static UNK_RET fn_8002206C(UNK_PARAMS);
/// @brief Display DObj then reset TEV/indirect stages for refraction cleanup.
/* 022608 */ static void lbRefract_DObjDispReset(HSD_DObj* dobj, Mtx vmtx,
                                                 Mtx pmtx, u32 rendermode);
/// @brief Read RGBA8 texture coordinate addresses from refraction buffer.
/* 022120 */ static void
lbRefract_ReadTexCoordRGBA8(lbRefract_CallbackData* data, s32 row, u32 col,
                            u32* out_r, u32* out_g, u8* out_b, u8* out_a);
/* 022DF8 */ static inline float lbRefract_80022DF8(float x);
/// @brief Initialize refraction callback data for a texture buffer.
/* 02219C */ s32 lbRefract_8002219C(lbRefract_CallbackData* data, s32 buffer,
                                    s32 format, u16 width, u16 height);

static int lbl_804336D0[0x10];

extern float MSL_TrigF_80400770[], MSL_TrigF_80400774[];

#define SIGN_BIT (1 << 31)
#define BITWISE(f) (*(u32*) &f)
#define SIGNED_BITWISE(f) ((s32) BITWISE(f))
#define GET_SIGN_BIT(f) (SIGNED_BITWISE(f) & SIGN_BIT)
#define BITWISE_PI_2 0x3FC90FDB

#define NAN MSL_TrigF_80400770[0]
#define INF MSL_TrigF_80400774[0]

static void lbRefract_WriteTexCoordIA4(lbRefract_CallbackData* data, s32 row,
                                       u32 col, u32 arg3, u8 arg4,
                                       u8 intensity, u8 alpha)
{
    struct {
        u8 alpha;
        u8 intensity;
    }* pixel;
    s32 row_stride = data->row_stride;
    s32 tile_col = col >> 2;
    s32 tile_base =
        data->buffer + tile_col * row_stride + ((row << 3) & 0xFFFFFFE0);
    s32 pixel_offset = ((row & 3) + ((col << 2) & 0xC)) << 1;

    pixel = (void*) (tile_base + pixel_offset);
    pixel->alpha = alpha;
    pixel->intensity = intensity;
}

static void lbRefract_ReadTexCoordRGBA8(lbRefract_CallbackData* data, s32 row,
                                        u32 col, u32* out_r, u32* out_g,
                                        u8* out_b, u8* out_a)
{
    s32 base_offset;
    s32 pixel_offset;

    base_offset = data->buffer + (((col >> 2U) * data->row_stride) +
                                  ((row * 0x10) & 0xFFFFFFC0));
    pixel_offset = ((row & 3) + ((col * 4) & 0xC)) * 2;
    if (out_a != NULL) {
        *out_a = base_offset + pixel_offset;
    }
    if (out_r != NULL) {
        *out_r = base_offset + pixel_offset + 0x01;
    }
    if (out_g != NULL) {
        *out_g = base_offset + pixel_offset + 0x20;
    }
    if (out_b != NULL) {
        *out_b = (s32) (base_offset + pixel_offset + 0x21);
    }
}

/// @brief Initialize refraction callback data for a texture buffer.
/// @param data Callback data to initialize.
/// @param buffer Base address of texture buffer.
/// @param format Texture format (3=IA4, 4=IA8, 6=RGBA8).
/// @param width Texture width in pixels.
/// @param height Texture height in pixels.
/// @return 0 on success, -1 if format is unsupported.
s32 lbRefract_8002219C(lbRefract_CallbackData* data, s32 buffer, s32 format,
                       u16 width, u16 height)
{
    data->buffer = buffer;
    data->format = format;
    data->width = (s32) width;
    data->height = (s32) height;
    data->buffer_size = GXGetTexBufferSize(width, height, format, 0U, 0U);
    switch (format) { /* irregular */
    case 3:
        data->callback0 = lbRefract_WriteTexCoordIA4;
        data->callback1 = fn_80021FF8;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
    block_11:
        return 0;
    case 4:
        data->callback0 = fn_80021F70;
        data->callback1 = fn_8002206C;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
        goto block_11;
    case 6:
        data->callback0 = fn_80021FB4;
        data->callback1 = lbRefract_ReadTexCoordRGBA8;
        data->row_stride = (width * 0x10) & 0xFFFFFFC0;
        goto block_11;
    case 5:
        /* fallthrough */
    default:
        return -1;
    }
}

/// @brief Copy framebuffer to refraction source texture.
void lbRefract_8002247C(HSD_CObj* cobj)
{
    s32 proj_type;

    if (lbl_804336D0[0] == 0) {
        return;
    }

    proj_type = HSD_CObjGetProjectionType(cobj);

    switch (proj_type) {
    case 1: {
        f32 scale = 0.5F;
        f32 trans = 0.5F;
        MTXLightPerspective((MtxPtr) ((char*) lbl_804336D0 + 0x10),
                            M2C_FIELD(cobj, f32*, 0x40),
                            M2C_FIELD(cobj, f32*, 0x44), scale, scale, scale,
                            trans);
        break;
    }
    case 2: {
        f32 scale = 0.5F;
        MTXLightFrustum(
            (MtxPtr) ((char*) lbl_804336D0 + 0x10),
            M2C_FIELD(cobj, f32*, 0x40), M2C_FIELD(cobj, f32*, 0x44),
            M2C_FIELD(cobj, f32*, 0x48), M2C_FIELD(cobj, f32*, 0x4c),
            M2C_FIELD(cobj, f32*, 0x38), scale, 0.5F, scale, scale);
        break;
    }
    default: {
        f32 scale = 0.5F;
        MTXLightOrtho((MtxPtr) ((char*) lbl_804336D0 + 0x10),
                      M2C_FIELD(cobj, f32*, 0x40), M2C_FIELD(cobj, f32*, 0x44),
                      M2C_FIELD(cobj, f32*, 0x48), M2C_FIELD(cobj, f32*, 0x4c),
                      scale, 0.5F, scale, scale);
        break;
    }
    }
}

void lbRefract_80022560(void)
{
    if (lbl_804336D0[0] != 0) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x140, 0xF0, 4, 1);
        GXCopyTex((void*) lbl_804336D0[1], 0);
        GXPixModeSync();
        GXInvalidateTexAll();
    }
}

/// @brief Reset TEV and indirect texture stages.
void lbRefract_800225D4(void)
{
    GXSetTevDirect(0);
    GXSetNumIndStages(0);
    HSD_StateInvalidate(-1);
}

static void lbRefract_DObjDispReset(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx,
                                    u32 rendermode)
{
    hsdDObj.disp(dobj, vmtx, pmtx, rendermode);
    GXSetTevDirect(0);
    GXSetNumIndStages(0);
    HSD_StateInvalidate(-1);
}

/// @brief Increment refraction effect user count.
void lbRefract_80022BB8(void)
{
    lbl_804336D0[0] += 1;
}

/// @brief Decrement refraction effect user count.
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
