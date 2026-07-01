/**
 * @file lbrefract.c
 * @brief Refraction visual effects using GX indirect textures.
 *
 * Uses reference counting to track active effect users.
 * Supports IA4, IA8, and RGBA8 texture formats.
 */

#include "lbrefract.h"

#include <placeholder.h>

#include "dolphin/gx/GXEnum.h"
#include "lb/lbarchive.h"
#include "lb/types.h"

#include <math.h>
#include <string.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/os/OSCache.h>
#include <baselib/class.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/dobj.h>
#include <baselib/memory.h>
#include <baselib/pobj.h>
#include <baselib/state.h>
#include <MetroTRK/intrinsics.h>

extern HSD_DObjInfo hsdDObj;
extern HSD_PObjInfo hsdPObj;
extern f32 lbl_803BB0E0[6];

/// @brief Write IA4 texture coordinate to refraction buffer.
/* 021F34 */ static void
lbRefract_WriteTexCoordIA4(lbRefract_CallbackData* data, s32 row, u32 col,
                           u32 arg3, u8 arg4, u8 intensity, u8 alpha);
/* 021F70 */ static void fn_80021F70(lbRefract_CallbackData* data, s32 row,
                                     u32 col, s32 r, s32 g, u32 b);
/* 021FB4 */ static void fn_80021FB4(lbRefract_CallbackData* data, s32 row,
                                     u32 col, u8 arg3, u8 arg4, u8 arg5,
                                     u8 arg6);
/* 021FF8 */ static void fn_80021FF8(lbRefract_CallbackData*, s32, u32, s32*,
                                     s32*, s32*, s32*);
/* 02206C */ static void fn_8002206C(lbRefract_CallbackData*, s32, u32, s32*,
                                     s32*, s32*, s32*);
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
                                    s32 format, s32 width, s32 height);

static void fn_80022650(void);
static void fn_80022940(void);

struct lbRefract_DataLayout {
    /* 0x000 */ Mtx texture_mtx;
    /* 0x030 */ f32 half_mtx[6];
    /* 0x048 */ HSD_ImageDesc imagedesc0;
    /* 0x060 */ HSD_TexLODDesc lod0;
    /* 0x070 */ HSD_TObjDesc tobj0;
    /* 0x0CC */ HSD_ImageDesc imagedesc1;
    /* 0x0E4 */ HSD_TexLODDesc lod1;
    /* 0x0F4 */ HSD_TObjDesc tobj1;
    /* 0x150 */ char filename[12];
    /* 0x15C */ char symbol[12];
    /* 0x168 */ HSD_DObjInfo dobj_info;
    /* 0x1AC */ HSD_PObjInfo pobj_info;
    /* 0x1F4 */ char lib_name[24];
    /* 0x20C */ char dobj_name[16];
    /* 0x21C */ char pobj_name[16];
};

extern struct lbRefract_DataLayout lbl_803BB0B0;

struct lbl_804336D0_t {
    int refractionUserCount;
    void* image_ptr;
    HSD_ImageDesc* unk_8;
    HSD_TObj** unk_C;
    Mtx texture_mtx;
};
STATIC_ASSERT(sizeof(struct lbl_804336D0_t) == 0x40);

static struct lbl_804336D0_t lbl_804336D0;
static u8* skip8_804D63E8;

extern float MSL_TrigF_80400770[], MSL_TrigF_80400774[];

#define SIGN_BIT (1 << 31)
#define BITWISE(f) (*(u32*) &f)
#define SIGNED_BITWISE(f) ((s32) BITWISE(f))
#define GET_SIGN_BIT(f) (SIGNED_BITWISE(f) & SIGN_BIT)
#define BITWISE_PI_2 0x3FC90FDB

#define NAN MSL_TrigF_80400770[0]
#define INF MSL_TrigF_80400774[0]

void lbRefract_80021CE8(void* arg0, s32 arg1)
{
    lbRefract_CallbackData* cb = arg0;
    u32 param_idx;
    u32 col, row;
    f32 x_step, y_step;
    f32 y, x, y_sq;
    f32 dist_sq;
    f32 dist;
    f32 param0;
    f32* params;

    PAD_STACK(16);

    param_idx = arg1 * 2;
    x_step = 2.0f / (f32) (u32) (cb->width - 1);
    y_step = 2.0f / (f32) (u32) (cb->height - 1);
    y = -1.0f;

    for (col = 0; col < (u32) cb->height; col++) {
        y_sq = y * y;
        x = -1.0f;
        for (row = 0; row < (u32) cb->width; row++) {
            if ((dist_sq = x * x + y_sq) > 0.0f) {
                f32 sqrt_dist;
                f32* sqrt_dist_ptr = &sqrt_dist;
                f64 est = __frsqrte((f64) dist_sq);
                est = 0.5 * est * -(((f64) dist_sq * (est * est)) - 3.0);
                est = 0.5 * est * -(((f64) dist_sq * (est * est)) - 3.0);
                *sqrt_dist_ptr =
                    (f32) ((f64) dist_sq *
                           (0.5 * est *
                            -(((f64) dist_sq * (est * est)) - 3.0)));
                dist_sq = *sqrt_dist_ptr;
            }
            dist = dist_sq;
            if (dist_sq > 1.0f) {
                dist = 1.0f;
            }
            params = *(f32**) (skip8_804D63E8 + 4);
            param0 = params[param_idx];
            if (param0) {
                f32 rem;
                {
                    f32 abs_dist = __fabsf(dist);
                    f32 abs_param0 = __fabsf(param0);
                    if (abs_param0 > abs_dist) {
                        rem = dist;
                    } else {
                        rem = -(param0 * (f32) (s64) (u64) (dist / param0) -
                                dist);
                    }
                }
                param0 = dist * rem;
            } else {
                param0 = dist;
            }
            params = *(f32**) (skip8_804D63E8 + 4);
            param0 *= params[param_idx + 1];
            if (param0 > 1.0f) {
                param0 = 1.0f;
            }
            ((void (*)(lbRefract_CallbackData*, s32, s32, s32, s32, u32,
                       u32)) cb->callback0)(
                cb, row, col, 0, 0, (u32) (127.0f * (x * param0) + 128.0f),
                (u32) (127.0f * (y * param0) + 128.0f));
            x += x_step;
        }
        y += y_step;
    }
    DCFlushRange((void*) cb->buffer, cb->buffer_size);
}

static void lbRefract_WriteTexCoordIA4(lbRefract_CallbackData* data, s32 row,
                                       u32 col, u32 arg3, u8 arg4,
                                       u8 intensity, u8 alpha)
{
    u8* base;
    s32 offset;

    (void) arg3;
    (void) arg4;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row * 8) & 0xFFFFFFE0);
    row &= 3;
    offset = (row + ((col * 4) & 0xC)) * 2;
    base[offset] = alpha;
    base += offset;
    base[1] = intensity;
}

static void fn_80021F70(lbRefract_CallbackData* data, s32 row, u32 col, s32 r,
                        s32 g, u32 b)
{
    u8* base;
    s32 offset;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row * 8) & 0xFFFFFFE0);
    row &= 3;
    offset = (row + ((col * 4) & 0xC)) * 2;
    *(u16*) (base + offset) =
        (b >> 3) | ((g * 8 & 0x7E0 & ~0xF800) | ((r << 8) & 0xF800));
}

static void fn_80021FF8(lbRefract_CallbackData* data, s32 row, u32 col,
                        s32* arg3, s32* arg4, s32* arg5, s32* arg6)
{
    u8* base;
    s32 offset;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row * 8) & 0xFFFFFFE0);
    row &= 3;
    offset = (row + ((col * 4) & 0xC)) * 2;
    if (arg3 != NULL) {
        *arg3 = 0xFF;
    }
    if (arg4 != NULL) {
        *arg4 = 0xFF;
    }
    if (arg5 != NULL) {
        *arg5 = base[offset + 1];
    }
    if (arg6 != NULL) {
        *arg6 = base[offset];
    }
}

static void fn_8002206C(lbRefract_CallbackData* data, s32 row, u32 col,
                        s32* arg3, s32* arg4, s32* arg5, s32* arg6)
{
    u8* base;
    s32 offset;
    u16 pixel;
    s32 val;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row * 8) & 0xFFFFFFE0);
    row &= 3;
    offset = (row + ((col * 4) & 0xC)) * 2;
    pixel = *(u16*) (base + offset);
    if (arg6 != NULL) {
        *arg6 = 0xFF;
    }
    if (arg3 != NULL) {
        if (((pixel >> 8) & 0xF8) | (pixel & 0x8000)) {
            val = 7;
        } else {
            val = 0;
        }
        *arg3 = val;
    }
    if (arg4 != NULL) {
        if (((pixel >> 3) & 0xFC) | (pixel & 0x400)) {
            val = 3;
        } else {
            val = 0;
        }
        *arg4 = val;
    }
    if (arg5 != NULL) {
        if (pixel & 0xF8) {
            val = 7;
        } else {
            val = 0;
        }
        *arg5 = val;
    }
}

static void fn_80021FB4(lbRefract_CallbackData* data, s32 row, u32 col,
                        u8 arg6, u8 arg7, u8 arg8, u8 arg9)
{
    u8* base;
    s32 offset;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row << 4) & 0xFFFFFFC0);
    row &= 3;
    offset = (row + ((col << 2) & 0xC)) * 2;
    base[offset] = arg9;
    base += offset;
    base[1] = arg6;
    base[0x20] = arg7;
    base[0x21] = arg8;
}

static void lbRefract_ReadTexCoordRGBA8(lbRefract_CallbackData* data, s32 row,
                                        u32 col, u32* out_r, u32* out_g,
                                        u8* out_b, u8* out_a)
{
    s32 offset;
    u8* base;

    base = (u8*) data->buffer + ((col >> 2) * data->row_stride) +
           ((row << 4) & 0xFFFFFFC0);
    offset = ((row & 3) + ((col & 3) << 2)) << 1;

    if (out_a != NULL) {
        *(u32*) out_a = base[offset];
    }
    if (out_r != NULL) {
        *(u32*) out_r = (base + offset)[1];
    }
    if (out_g != NULL) {
        *(u32*) out_g = (base + offset)[0x20];
    }
    if (out_b != NULL) {
        *(u32*) out_b = (base + offset)[0x21];
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
                       s32 width, s32 height)
{
    data->buffer = buffer;
    data->format = format;
    data->width = width;
    data->height = height;
    data->buffer_size =
        GXGetTexBufferSize((u16) width, (u16) height, format, 0, 0);
    switch (format) {
    case 3:
        data->callback0 = lbRefract_WriteTexCoordIA4;
        data->callback1 = fn_80021FF8;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
        break;
    case 4:
        data->callback0 = fn_80021F70;
        data->callback1 = fn_8002206C;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
        break;
    case 6:
        data->callback0 = fn_80021FB4;
        data->callback1 = lbRefract_ReadTexCoordRGBA8;
        data->row_stride = (width * 0x10) & 0xFFFFFFC0;
        break;
    case 5:
    default:
        return -1;
    }
    return 0;
}

void lbRefract_800222A4(void)
{
    lbRefract_CallbackData cb;
    void* buf;
    u32 i;

    lbl_804336D0.refractionUserCount = 0;
    lbArchive_LoadSymbols(lbl_803BB0B0.filename, &skip8_804D63E8,
                          lbl_803BB0B0.symbol, 0);
    {
        s32 buf_size = GXGetTexBufferSize(0x140, 0xF0, 4, 0, 0);
        lbl_804336D0.image_ptr = HSD_MemAlloc(buf_size);
        memset((void*) lbl_804336D0.image_ptr, 0, (u32) buf_size);
    }
    lbl_804336D0.unk_C = HSD_MemAlloc(*skip8_804D63E8 * 4);
    lbl_804336D0.unk_8 = HSD_MemAlloc(*skip8_804D63E8 * 0x18);

    for (i = 0; i < *skip8_804D63E8; i++) {
        buf = HSD_MemAlloc(GXGetTexBufferSize(0x20, 0x20, 3, 0, 0));
        lbRefract_8002219C(&cb, (s32) buf, 3, 0x20, 0x20);
        lbRefract_80021CE8(&cb, (s32) i);

        {
            HSD_ImageDesc* dst = &lbl_804336D0.unk_8[i];
            *dst = lbl_803BB0B0.imagedesc0;
        }

        lbl_803BB0B0.tobj1.imagedesc = &lbl_804336D0.unk_8[i];

        lbl_804336D0.unk_C[i] = HSD_TObjLoadDesc(&lbl_803BB0B0.tobj1);

        lbl_803BB0B0.imagedesc0.image_ptr = (void*) lbl_804336D0.image_ptr;
        lbl_803BB0B0.imagedesc0.format = 4;
        lbl_803BB0B0.imagedesc0.width = 0x140;
        lbl_803BB0B0.imagedesc0.height = 0xF0;

        lbl_804336D0.unk_8[i].image_ptr = buf;
        lbl_804336D0.unk_8[i].format = 3;
        lbl_804336D0.unk_8[i].width = 0x20;
        lbl_804336D0.unk_8[i].height = 0x20;
    }
}

/// @brief Copy framebuffer to refraction source texture.
void lbRefract_8002247C(HSD_CObj* cobj)
{
    if (lbl_804336D0.refractionUserCount == 0) {
        return;
    }

    switch (HSD_CObjGetProjectionType(cobj)) {
    case 1:
        MTXLightPerspective(lbl_804336D0.texture_mtx,
                            cobj->projection_param.perspective.fov,
                            cobj->projection_param.perspective.aspect, 0.5F,
                            -0.5F, 0.5F, 0.5F);
        break;
    case 2:
        MTXLightFrustum(lbl_804336D0.texture_mtx,
                        cobj->projection_param.frustum.top,
                        cobj->projection_param.frustum.bottom,
                        cobj->projection_param.frustum.left,
                        cobj->projection_param.frustum.right, cobj->near, 0.5F,
                        -0.5F, 0.5F, 0.5F);
        break;
    case 3:
    default:
        MTXLightOrtho(
            lbl_804336D0.texture_mtx, cobj->projection_param.ortho.top,
            cobj->projection_param.ortho.bottom,
            cobj->projection_param.ortho.left,
            cobj->projection_param.ortho.right, 0.5F, -0.5F, 0.5F, 0.5F);
        break;
    }
}

void lbRefract_80022560(void)
{
    if (lbl_804336D0.refractionUserCount != 0) {
        GXSetTexCopySrc(0, 0, 0x280, 0x1E0);
        GXSetTexCopyDst(0x140, 0xF0, 4, 1);
        GXCopyTex((void*) lbl_804336D0.image_ptr, 0);
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

struct lbRefract_DataLayout lbl_803BB0B0 = {
    { { 0 } },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    { 0 },
    "",
    "",
    { fn_80022650 },
    { fn_80022940 },
    "refract_class_library",
    "refract_dobj",
    "refract_pobj",
};

static void fn_80022650(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&lbl_803BB0B0.dobj_info),
                     HSD_CLASS_INFO(&hsdDObj), lbl_803BB0B0.lib_name,
                     lbl_803BB0B0.dobj_name, sizeof(HSD_DObjInfo),
                     sizeof(HSD_DObj));
    lbl_803BB0B0.dobj_info.disp = lbRefract_DObjDispReset;
}

s32 lbRefract_PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc)
{
    s32 ret;
    HSD_VtxDescList* verts;
    s32 last_offset;
    s32 pnmtx_offset;
    s32 stride;
    GXAttr attr;

    ret = hsdPObj.load(pobj, desc);
    if (ret != 0) {
        return ret;
    }

    if (!(HSD_PObjGetFlags(pobj) & 0x2000)) {
        return 0;
    }

    verts = pobj->verts;
    last_offset = -1;
    pnmtx_offset = -1;
    stride = 0;

    while (verts != NULL && (attr = verts->attr) != GX_VA_NULL) {
        if (attr < GX_VA_CLR0) {
            if (attr != GX_VA_PNMTXIDX) {
                if (attr >= GX_VA_PNMTXIDX) {
                    if (attr >= GX_VA_POS) {
                        goto indexed_attr;
                    }
                    goto last_attr;
                }
            } else {
                goto pnmtx_attr;
            }
        } else if (attr < GX_POS_MTX_ARRAY) {
            if (attr >= GX_VA_TEX0) {
                goto indexed_attr;
            }
            goto color_attr;
        }
        goto next_attr;

    last_attr:
        last_offset = stride;
        stride++;
        goto next_attr;

    pnmtx_attr:
        pnmtx_offset = stride;
        stride++;
        goto next_attr;

    indexed_attr:
        if (verts->attr_type == GX_INDEX16) {
            stride += 2;
        } else {
            stride++;
        }
        goto next_attr;

    color_attr:
        switch (verts->attr_type) {
        case GX_INDEX16:
            stride += 2;
            break;
        case GX_INDEX8:
            stride++;
            break;
        default:
            switch (verts->comp_type) {
            case GX_RGB565:
            case GX_RGBA4:
                stride += 2;
                break;
            case GX_RGB8:
            case GX_RGBA6:
                stride += 3;
                break;
            case GX_RGBX8:
                stride += 4;
                break;
            }
            break;
        }

    next_attr:
        verts++;
    }

    if (pnmtx_offset == -1 || last_offset < 2) {
        return 0;
    }

    {
        u8* display = pobj->display;
        s32 offset = 0;
        s32 total_bytes = pobj->n_display << 5;
        u8* src = display + pnmtx_offset;
        u8* dst = display + last_offset;

        while (offset < total_bytes) {
            u8* ptr;
            s32 hi;
            s32 count;
            s32 copied;
            s32 n;
            u32 iters;
            s32 remaining;
            if ((display[offset++] & 0xF8) == 0) {
                break;
            }

            ptr = display + offset;
            hi = ptr[0];
            copied = 0;
            count = (hi << 8) | ptr[1];
            offset += 2;

            if (count > 0) {
                n = count - 8;

                if (count > 8) {
                    iters = (u32) (n + 7) >> 3U;

                    if (n > 0) {
                        do {
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            dst[offset] = src[offset];
                            offset += stride;
                            copied += 8;
                        } while (--iters != 0);
                    }
                }

                remaining = count - copied;
                if (copied < count) {
                    do {
                        dst[offset] = src[offset];
                        offset += stride;
                    } while (--remaining != 0);
                }
            }
        }

        DCFlushRange(display, total_bytes);
    }

    return 0;
}

static void fn_80022940(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&lbl_803BB0B0.pobj_info),
                     HSD_CLASS_INFO(&hsdPObj), lbl_803BB0B0.lib_name,
                     lbl_803BB0B0.pobj_name, sizeof(HSD_PObjInfo),
                     sizeof(HSD_PObj));
    lbl_803BB0B0.pobj_info.load = lbRefract_PObjLoad;
}

void lbRefract_80022998(HSD_MObj* mobj, u32 rendermode, s32 arg2)
{
    unsigned long long write_z;
    enum _GXCompare compare;

    HSD_TObjSetup(lbl_804336D0.unk_C[arg2]);

    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                      GX_TRUE, GX_PTTEXMTX0);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX3x4, GX_TG_POS, 0, GX_FALSE,
                      GX_PTTEXMTX1);

    GXLoadTexMtxImm(lbl_803BB0B0.texture_mtx, GX_PTTEXMTX0, GX_MTX3x4);
    GXLoadTexMtxImm(lbl_804336D0.texture_mtx, GX_PTTEXMTX1, GX_MTX3x4);

    GXSetNumChans(0);
    GXSetNumTevStages(1);
    write_z = GX_ITF_8;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                    GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                    GX_CA_TEXA);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                    GX_FALSE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3]) lbl_803BB0E0, 1);

    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, write_z, GX_ITB_ST,
                     GX_ITM_0, GX_ITW_OFF, GX_ITW_OFF, (GXBool) 0, (GXBool) 0,
                     GX_ITBA_OFF);

    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);

    write_z = (rendermode & 0x20000000) ? 0 : 1;

    if (rendermode & 0x08000000) {
        compare = GX_ALWAYS;
    } else {
        compare = GX_LEQUAL;
    }

    GXSetZMode(GX_TRUE, compare, write_z);
    GXSetZCompLoc(GX_TRUE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_SET);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetDither(GX_FALSE);
}

/// @brief Increment refraction effect user count.
void lbRefract_80022BB8(void)
{
    lbl_804336D0.refractionUserCount += 1;
}

/// @brief Decrement refraction effect user count.
void lbRefract_80022BD0(void)
{
    lbl_804336D0.refractionUserCount -= 1;
    if (lbl_804336D0.refractionUserCount < 0) {
        HSD_ASSERTREPORT(0x31c, 0, "lbRefSetUnuse error!\n");
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
