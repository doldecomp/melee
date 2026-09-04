#include "lbrefract.h"

#include "lbarchive.h"
#include "types.h"

#include <placeholder.h>

#include <math.h>
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
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/state.h>

/* 022650 */ static void fn_80022650(void);
/* 022940 */ static void fn_80022940(void);

static struct {
    int refractionUserCount;
    void* image_ptr;
    HSD_ImageDesc* imagedesc;
    HSD_TObj** tobj_list;
    Mtx texture_mtx;
} lbl_804336D0;

static struct {
    u8 x0;
    f32* x4;
}* refract_data;

static inline void lbRefract_WriteTexCoord(lbRefract_CallbackData* cb, s32 row,
                                           u32 col, f32 y, f32 x, f32 param0)
{
    u32 y_tex = 127.0f * (y * param0) + 128.0f;
    ((void (*)(lbRefract_CallbackData*, s32, s32, s32, s32, u32,
               u32)) cb->callback0)(cb, row, col, 0, 0, y_tex,
                                    127.0f * (x * param0) + 128.0f);
}

/// @todo reconcile with MSL fmodf
static inline float my_fmodf(float a, float b)
{
    s64 quotient;
    float fb, fa;

    fa = fabsf(a);
    fb = fabsf(b);

    if (fb > fa) {
        return a;
    }
    quotient = a / b;
    return a - b * quotient;
}

static void lbRefract_80021CE8(lbRefract_CallbackData* cb, s32 arg1)
{
    int param_idx = arg1 * 2;
    float x_step = 2.0f / (cb->width - 1);
    float y_step = 2.0f / (cb->height - 1);
    int row, col;
    float y = -1.0f;
    f32 param0;

    PAD_STACK(12);

    for (row = 0; row < cb->height; row++) {
        float x = -1.0f;
        float y_sq = y * y;
        for (col = 0; col < cb->width; col++) {
            float dist = sqrtf(x * x + y_sq);
            if (dist > 1.0f) {
                dist = 1.0f;
            }
            param0 = refract_data->x4[param_idx];
            if (param0) {
                param0 = dist * my_fmodf(dist, param0);
            } else {
                param0 = dist;
            }
            param0 *= refract_data->x4[param_idx + 1];
            if (param0 > 1.0f) {
                param0 = 1.0f;
            }
            lbRefract_WriteTexCoord(cb, col, row, y, x, param0);
            x += x_step;
        }
        y += y_step;
    }
    DCFlushRange(cb->buffer, cb->buffer_size);
}

static void lbRefract_WriteTexCoordIA4(lbRefract_CallbackData* data, u32 row,
                                       u32 col, u32 arg3, u8 arg4,
                                       u8 intensity, u8 alpha)
{
    u32 r_ = row >> 2;
    u32 c_ = col >> 2;
    u8(*base)[2] =
        (void*) ((u8*) data->buffer + c_ * data->row_stride + r_ * 32);
    row &= 3;
    col &= 3;
    base[row + col * 4][0] = alpha;
    base[row + col * 4][1] = intensity;
}

static void fn_80021F70(lbRefract_CallbackData* data, u32 row, u32 col, u8 r,
                        u8 g, u32 b)
{
    u16* base;
    s32 offset;
    u32 r_ = row >> 2;
    u32 c_ = col >> 2;
    base = (u16*) ((u8*) data->buffer + c_ * data->row_stride + r_ * 32);
    row &= 3;
    col &= 3;
    offset = (row + col * 4);
    base[offset] = (b / 8) | ((g * 8 & 0x7E0 & ~0xF800) | ((r << 8) & 0xF800));
}

static void fn_80021FB4(lbRefract_CallbackData* data, u32 row, u32 col,
                        u8 arg6, u8 arg7, u8 arg8, u8 arg9)
{
    u32 r_ = row >> 2;
    u32 c_ = col >> 2;
    u8(*base)[2] =
        (void*) ((u8*) data->buffer + c_ * data->row_stride + r_ * 64);
    row &= 3;
    col &= 3;
    base[row + col * 4][0] = arg9;
    base[row + col * 4][1] = arg6;
    base[row + col * 4 + 16][0] = arg7;
    base[row + col * 4 + 16][1] = arg8;
}

static void fn_80021FF8(lbRefract_CallbackData* data, u32 row, u32 col,
                        s32* arg3, s32* arg4, s32* arg5, s32* arg6)
{
    u8* base;
    int offset;

    {
        u32 r = row >> 2;
        u32 c = col >> 2;
        base = (u8*) data->buffer + c * data->row_stride + r * 32;
    }
    row &= 3;
    col &= 3;
    offset = (row + col * 4) * 2;
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
    u16* base;
    s32 offset;
    u16 pixel;
    s32 val;

    {
        u32 r = row & ~3;
        u32 c = col & ~3;
        base = (u16*) ((u8*) data->buffer + c / 4 * data->row_stride + r * 8);
    }
    row &= 3;
    col &= 3;
    pixel = base[row + col * 4];
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

static void lbRefract_ReadTexCoordRGBA8(lbRefract_CallbackData* data, u32 row,
                                        u32 col, u32* out_r, u32* out_g,
                                        u32* out_b, u32* out_a)
{
    int offset;
    u8* base;

    {
        u32 r = row >> 2;
        u32 c = col >> 2;
        base = (u8*) data->buffer + c * data->row_stride + r * 64;
    }
    row &= 3;
    col &= 3;
    offset = (row + col * 4) * 2;

    if (out_a != NULL) {
        *out_a = base[offset];
    }
    if (out_r != NULL) {
        *out_r = base[offset + 1];
    }
    if (out_g != NULL) {
        *out_g = base[offset + 0x20];
    }
    if (out_b != NULL) {
        *out_b = base[offset + 0x21];
    }
}

/// @brief Initialize refraction callback data for a texture buffer.
/// @param data Callback data to initialize.
/// @param buffer Base address of texture buffer.
/// @param format Texture format (3=IA4, 4=IA8, 6=RGBA8).
/// @param width Texture width in pixels.
/// @param height Texture height in pixels.
/// @return 0 on success, -1 if format is unsupported.
static int lbRefract_8002219C(lbRefract_CallbackData* data, void* buffer,
                              s32 format, u32 width, u32 height)
{
    data->buffer = buffer;
    data->format = format;
    data->width = width;
    data->height = height;
    data->buffer_size = GXGetTexBufferSize(width, height, format, 0, 0);
    switch (format) {
    case GX_TF_IA8:
        data->callback0 = lbRefract_WriteTexCoordIA4;
        data->callback1 = fn_80021FF8;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
        break;
    case GX_TF_RGB565:
        data->callback0 = fn_80021F70;
        data->callback1 = fn_8002206C;
        data->row_stride = (width * 8) & 0xFFFFFFE0;
        break;
    case GX_TF_RGBA8:
        data->callback0 = fn_80021FB4;
        data->callback1 = lbRefract_ReadTexCoordRGBA8;
        data->row_stride = (width * 16) & 0xFFFFFFC0;
        break;
    case GX_TF_RGB5A3:
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

void lbRefract_800222A4(void)
{
    int const image_width = 320;
    int const image_height = 240;

    /// @todo Refactor data members into a struct
    struct lbRefract_DataLayout {
        Mtx texture_mtx;
        f32 texture_offset[6];
        HSD_ImageDesc imagedesc0;
    };

    lbRefract_CallbackData cb;
    struct lbRefract_DataLayout* data =
        (struct lbRefract_DataLayout*) &texture_mtx;
    size_t i;
    void* buf;
    PAD_STACK(4);

    lbl_804336D0.refractionUserCount = 0;
    lbArchive_LoadSymbols("LbRf.dat", &refract_data, "lbRefData", 0);
    {
        size_t buf_size =
            GXGetTexBufferSize(image_width, image_height, GX_TF_RGB565, 0, 0);
        lbl_804336D0.image_ptr = HSD_MemAlloc(buf_size);
        memset(lbl_804336D0.image_ptr, 0, buf_size);
    }
    lbl_804336D0.tobj_list =
        HSD_MemAlloc(refract_data->x0 * sizeof(HSD_TObj*));
    lbl_804336D0.imagedesc =
        HSD_MemAlloc(refract_data->x0 * sizeof(HSD_ImageDesc));

    for (i = 0; i < refract_data->x0; i++) {
        buf = HSD_MemAlloc(GXGetTexBufferSize(32, 32, GX_TF_IA8, 0, 0));
        lbRefract_8002219C(&cb, buf, GX_TF_IA8, 32, 32);
        lbRefract_80021CE8(&cb, i);

        lbl_804336D0.imagedesc[i] = data->imagedesc0;
        tobjdesc1.imagedesc = &lbl_804336D0.imagedesc[i];
        lbl_804336D0.tobj_list[i] = HSD_TObjLoadDesc(&tobjdesc1);

        imagedesc0.image_ptr = lbl_804336D0.image_ptr;
        imagedesc0.format = GX_TF_RGB565;
        imagedesc0.width = image_width;
        imagedesc0.height = image_height;

        lbl_804336D0.imagedesc[(s32) i].image_ptr = buf;
        lbl_804336D0.imagedesc[(s32) i].format = GX_TF_IA8;
        lbl_804336D0.imagedesc[(s32) i].width = 32;
        lbl_804336D0.imagedesc[(s32) i].height = 32;
    }
}

/// @brief Copy framebuffer to refraction source texture.
void lbRefract_8002247C(HSD_CObj* cobj)
{
    if (lbl_804336D0.refractionUserCount == 0) {
        return;
    }

    switch (HSD_CObjGetProjectionType(cobj)) {
    case PROJ_PERSPECTIVE:
        MTXLightPerspective(lbl_804336D0.texture_mtx,
                            cobj->projection_param.perspective.fov,
                            cobj->projection_param.perspective.aspect, 0.5F,
                            -0.5F, 0.5F, 0.5F);
        break;
    case PROJ_FRUSTUM:
        MTXLightFrustum(lbl_804336D0.texture_mtx,
                        cobj->projection_param.frustum.top,
                        cobj->projection_param.frustum.bottom,
                        cobj->projection_param.frustum.left,
                        cobj->projection_param.frustum.right, cobj->near, 0.5F,
                        -0.5F, 0.5F, 0.5F);
        break;
    case PROJ_ORTHO:
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
        GXCopyTex(lbl_804336D0.image_ptr, 0);
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
    HSD_StateInvalidate(HSD_STATE_ALL);
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

    while (verts != NULL && verts->attr != GX_VA_NULL) {
        switch (verts->attr) {
        case GX_VA_TEX0MTXIDX:
        case GX_VA_TEX1MTXIDX:
        case GX_VA_TEX2MTXIDX:
        case GX_VA_TEX3MTXIDX:
        case GX_VA_TEX4MTXIDX:
        case GX_VA_TEX5MTXIDX:
        case GX_VA_TEX6MTXIDX:
        case GX_VA_TEX7MTXIDX:
            last_offset = stride;
            stride++;
            break;
        case GX_VA_PNMTXIDX:
            pnmtx_offset = stride;
            stride++;
            break;
        case GX_VA_TEX0:
        case GX_VA_TEX1:
        case GX_VA_TEX2:
        case GX_VA_TEX3:
        case GX_VA_TEX4:
        case GX_VA_TEX5:
        case GX_VA_TEX6:
        case GX_VA_TEX7:
        case GX_VA_POS:
        case GX_VA_NRM:
            if (verts->attr_type == GX_INDEX16) {
                stride += 2;
            } else {
                stride++;
            }
            break;
        case GX_VA_CLR0:
        case GX_VA_CLR1:
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
            break;
        default:
            break;
        }
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
    u64 write_z;
    GXCompare compare;

    HSD_TObjSetup(lbl_804336D0.tobj_list[arg2]);

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

    write_z = (rendermode & RENDER_NO_ZUPDATE) ? 0 : 1;

    if (rendermode & RENDER_ZMODE_ALWAYS) {
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
