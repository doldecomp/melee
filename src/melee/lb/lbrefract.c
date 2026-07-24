#include "lbrefract.h"

#include "lbarchive.h"
#include "types.h"

#include <placeholder.h>

#include <string.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXEnum.h>
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

extern f32 lbl_803BB0E0[6];

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
/* 022120 */ static void
lbRefract_ReadTexCoordRGBA8(lbRefract_CallbackData* data, s32 row, u32 col,
                            u32* out_r, u32* out_g, u8* out_b, u8* out_a);
/* 02219C */ s32 lbRefract_8002219C(lbRefract_CallbackData* data, s32 buffer,
                                    s32 format, s32 width, s32 height);
/* 022608 */ static void lbRefract_DObjDispReset(HSD_DObj* dobj, Mtx vmtx,
                                                 Mtx pmtx, u32 rendermode);
/* 022650 */ static void fn_80022650(void);
/* 022940 */ static void fn_80022940(void);

struct lbl_804336D0_t {
    int refractionUserCount;
    void* image_ptr;
    HSD_ImageDesc* unk_8;
    HSD_TObj** unk_C;
    Mtx texture_mtx;
};
STATIC_ASSERT(sizeof(struct lbl_804336D0_t) == 0x40);

static struct lbl_804336D0_t lbl_804336D0;
static u8* refract_data;

static inline void lbRefract_WriteTexCoord(lbRefract_CallbackData* cb, s32 row,
                                           u32 col, f32 y, f32 x, f32 param0)
{
    u32 y_tex = (u32) (127.0f * (y * param0) + 128.0f);
    ((void (*)(lbRefract_CallbackData*, s32, s32, s32, s32, u32,
               u32)) cb->callback0)(cb, row, col, 0, 0, y_tex,
                                    (u32) (127.0f * (x * param0) + 128.0f));
}

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

    PAD_STACK(12);

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
                PAD_STACK(4);
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
            params = *(f32**) (refract_data + 4);
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
            params = *(f32**) (refract_data + 4);
            param0 *= params[param_idx + 1];
            if (param0 > 1.0f) {
                param0 = 1.0f;
            }
            lbRefract_WriteTexCoord(cb, row, col, y, x, param0);
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

Mtx texture_mtx = {
    { +0.5F, +0.0F, +0.0F, +0.5F },
    { +0.0F, -0.5F, +0.0F, +0.5F },
    { +0.0F, +0.0F, +0.0F, +1.0F },
};

float texture_offset[2][3] = {
    { -0.5F, +0.0F, +0.0F },
    { +0.0F, -0.5F, +0.0F },
};

HSD_ImageDesc imagedesc0 = { NULL, 0, 0, 4, 0, 0.0F, 0.0F };
HSD_TexLODDesc loddesc0 = { 1, 0.0F, 1, 1, 0 };

HSD_TObjDesc tobjdesc0 = {
    NULL,
    NULL,
    0,
    0,
    { 0.0F, 0.0F, 0.0F },
    { 1.0F, 1.0F, 1.0F },
    { 0.0F, 0.0F, 0.0F },
    0,
    0,
    1,
    1,
    0x83,
    1.0F,
    1,
    &imagedesc0,
    NULL,
    &loddesc0,
    NULL,
};

HSD_ImageDesc imagedesc1 = { NULL, 0, 0, 3, 0, 0.0F, 0.0F };
HSD_TexLODDesc loddesc1 = { 1, 0.0F, 1, 1, 0 };

HSD_TObjDesc tobjdesc1 = {
    NULL,
    &tobjdesc0,
    1,
    1,
    { 0.0F, 0.0F, 0.0F },
    { 1.0F, 1.0F, 1.0F },
    { 0.0F, 0.0F, 0.0F },
    0,
    0,
    1,
    1,
    0x81,
    1.0F,
    1,
    &imagedesc1,
    NULL,
    &loddesc1,
    NULL,
};

/// @todo Only differs by register allocation.
void lbRefract_800222A4(void)
{
    lbl_804336D0.refractionUserCount = 0;
    lbArchive_LoadSymbols("LbRf.dat", &refract_data, "lbRefData", 0);
    {
        s32 buf_size = GXGetTexBufferSize(0x140, 0xF0, 4, 0, 0);
        lbl_804336D0.image_ptr = HSD_MemAlloc(buf_size);
        memset(lbl_804336D0.image_ptr, 0, buf_size);
    }
    lbl_804336D0.unk_C = HSD_MemAlloc(*refract_data * 4);
    lbl_804336D0.unk_8 = HSD_MemAlloc(*refract_data * 0x18);

    {
        lbRefract_CallbackData cb;
        size_t i;
        size_t j;
        j = 0;
        for (i = 0; i < *refract_data; i++) {
            void* buf;
            buf = HSD_MemAlloc(GXGetTexBufferSize(0x20, 0x20, 3, 0, 0));
            lbRefract_8002219C(&cb, (s32) buf, 3, 0x20, 0x20);
            lbRefract_80021CE8(&cb, (s32) i);

            {
                HSD_ImageDesc* dst = &lbl_804336D0.unk_8[i];
                *dst = imagedesc0;
            }

            tobjdesc1.imagedesc = &lbl_804336D0.unk_8[i];

            lbl_804336D0.unk_C[i] = HSD_TObjLoadDesc(&tobjdesc1);

            imagedesc0.image_ptr = lbl_804336D0.image_ptr;
            imagedesc0.format = 4;
            imagedesc0.width = 320;
            imagedesc0.height = 240;

            lbl_804336D0.unk_8[j].image_ptr = buf;
            lbl_804336D0.unk_8[j].format = 3;
            lbl_804336D0.unk_8[j].width = 32;
            lbl_804336D0.unk_8[j].height = 32;
            j++;
        }
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

static HSD_DObjInfo dobj_info = { fn_80022650 };
static HSD_PObjInfo pobj_info = { fn_80022940 };

static void fn_80022650(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&dobj_info), HSD_CLASS_INFO(&hsdDObj),
                     "refract_class_library", "refract_dobj",
                     sizeof(HSD_DObjInfo), sizeof(HSD_DObj));
    dobj_info.disp = lbRefract_DObjDispReset;
}

s32 lbRefract_PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc)
{
    u8* display;
    s32 offset;
    s32 total_bytes;
    u8* ptr;
    s32 hi;
    s32 copied;
    s32 count;
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
    stride = 0;
    pnmtx_offset = -1;
    last_offset = -1;

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
            default:
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

    display = pobj->display;
    offset = 0;
    total_bytes = pobj->n_display << 5;
    while (offset < total_bytes) {
        if ((display[offset++] & 0xF8) == 0) {
            break;
        }

        ptr = display + offset;
        hi = ptr[0];
        count = hi << 8;
        count |= ptr[1];
        offset += 2;

        for (copied = 0; copied < count; copied++) {
            display[offset + last_offset] = display[offset + pnmtx_offset];
            offset += stride;
        }
    }

    DCFlushRange(display, total_bytes);

    return 0;
}

static void fn_80022940(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&pobj_info), HSD_CLASS_INFO(&hsdPObj),
                     "refract_class_library", "refract_pobj",
                     sizeof(HSD_PObjInfo), sizeof(HSD_PObj));
    pobj_info.load = lbRefract_PObjLoad;
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

    GXLoadTexMtxImm(texture_mtx, GX_PTTEXMTX0, GX_MTX3x4);
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
    GXSetIndTexMtx(GX_ITM_0, texture_offset, 1);

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
void lbRefSetUnuse(void)
{
    lbl_804336D0.refractionUserCount -= 1;
    if (lbl_804336D0.refractionUserCount < 0) {
        HSD_ASSERTREPORT(0x31c, 0, "lbRefSetUnuse error!\n");
    }
}
