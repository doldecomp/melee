#include "lbspdisplay.h"

#include "platform.h"
#include "stdarg.h"
#include "stddef.h"

#include <placeholder.h>

#include "baselib/debug.h"

#include "baselib/forward.h"

#include "baselib/psstructs.h"
#include "baselib/tobj.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GXVert.h"

#include "lb/forward.h"

#include "lb/lbdvd.h"
#include "lb/types.h"

#include <math_ppc.h>
#include <trigf.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <melee/sc/types.h>

struct CameraBlurData {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ u8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 x12;
    /* 0x13 */ char pad_13[0x18 - 0x13];
    /* 0x18 */ HSD_GObjEvent x18;
    /* 0x1C */ HSD_ImageDesc* x1C;
    /* 0x20 */ f32 x20;
};

/* 0103D8 */ static bool lb_800103D8(Vec3* vec, float x0, float x1, float x2,
                                     float x3, float offset);
/* 013BB8 */ static bool lb_80013BB8(ColorOverlay* arg);
/* 013BE4 */ static bool lb_80013BE4(ColorOverlay* arg);
/* 013FF0 */ static bool lb_80013FF0(ColorOverlay* arg);
/* 014234 */ static bool lb_80014234(ColorOverlay* arg);

HSD_LObj* lb_80011AC4(LightList** list)
{
    HSD_LObj* prev;
    HSD_LObj* curr;
    HSD_LObj* first;
    HSD_LightAnim** temp_r4;

    prev = NULL;
    while (*list != NULL) {
        curr = HSD_LObjLoadDesc((*list)->desc);
        temp_r4 = (*list)->anims;
        if (temp_r4 != NULL) {
            HSD_LObjAddAnimAll(curr, temp_r4[0]);
        }
        if (prev != NULL) {
            HSD_LObjSetNext(prev, curr);
        } else {
            first = curr;
        }
        prev = curr;
        list++;
    }
    return first;
}

void lb_80011B74(HSD_DObj* dobj, u32 flags)
{
    if (dobj->next != NULL) {
        lb_80011B74(dobj->next, flags);
    }
    dobj->mobj->rendermode |= flags;
}

/// @todo Duplicated in lb_00F9.c
static inline bool checkJObjFlags(HSD_JObj* jobj)
{
    return jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? false : true;
}

#pragma inline_depth(2)
void lb_80011C18(HSD_JObj* jobj, u32 flags)
{
    HSD_JObj* cur;
    PAD_STACK(8);

    cur = jobj->child;
    if (cur != NULL) {
        if (cur->child != NULL) {
            lb_80011C18(cur->child, flags);
        }
        if (cur->next != NULL) {
            lb_80011C18(cur->next, flags);
        }
        if (checkJObjFlags(cur)) {
            if (cur->u.dobj != NULL) {
                lb_80011B74(cur->u.dobj, flags);
            }
        }
    }

    cur = jobj->next;
    if (cur != NULL) {
        if (cur->child != NULL) {
            lb_80011C18(cur->child, flags);
        }
        if (cur->next != NULL) {
            lb_80011C18(cur->next, flags);
        }
        if (checkJObjFlags(cur)) {
            if (cur->u.dobj != NULL) {
                lb_80011B74(cur->u.dobj, flags);
            }
        }
    }

    if (checkJObjFlags(jobj)) {
        HSD_DObj* dobj = jobj->u.dobj;
        if (dobj != NULL) {
            HSD_DObj* next = dobj->next;
            dobj = jobj->u.dobj;
            if (next != NULL) {
                lb_80011B74(next, flags);
            }
            dobj->mobj->rendermode |= flags;
        }
    }
}

#pragma inline_depth(8)
/**
 * @note: The number of HSD_JObjs that get passed into arg1 is the number of
 * variable arguments passed until -1 is passed.
 */
int lb_80011E24(HSD_JObj* root, HSD_JObj** result, ...)
{
    va_list ap;
    int found;
    int prev;
    HSD_JObj* jobj;
    HSD_JObj* saved;
    HSD_JObj* next_node;
    int cur;
    s32 target;
    PAD_STACK(4);

    found = 0;
    prev = -1;

    if (root == NULL || result == NULL) {
        return 0;
    }

    va_start(ap, result);
    for (;;) {
        target = va_arg(ap, s32);
        if (target == -1) {
            break;
        }
        if (prev > target || prev == -1) {
            jobj = root;
            cur = 0;
        } else {
            cur = prev;
        }

        while (jobj != NULL) {
            if (cur == target) {
                break;
            }
            saved = jobj;
            if (!(jobj->flags & JOBJ_INSTANCE) &&
                HSD_JObjGetChild(jobj) != NULL)
            {
                next_node = HSD_JObjGetChild(jobj);
            } else if (HSD_JObjGetNext(jobj) != NULL) {
                next_node = HSD_JObjGetNext(jobj);
            } else {
                while (true) {
                    if (HSD_JObjGetParent(saved) == NULL) {
                        next_node = NULL;
                        break;
                    }
                    if (HSD_JObjGetNext(HSD_JObjGetParent(saved)) != NULL) {
                        next_node = saved =
                            HSD_JObjGetNext(HSD_JObjGetParent(saved));
                        break;
                    }
                    saved = HSD_JObjGetParent(saved);
                }
            }
            jobj = next_node;
            cur++;
        }

        *result = jobj;
        prev = cur;
        result++;
        if (jobj != NULL) {
            found++;
        }
    }
    va_end(ap);

    return found;
}

int lb_8001204C(HSD_JObj* root, HSD_JObj** result, u16* indices, int count)
{
    HSD_JObj** out;
    u16* idx;
    HSD_JObj* jobj;
    HSD_JObj* saved;
    HSD_JObj* next_node;
    int found;
    int prev;
    int cur;
    int i;
    u16 target;

    out = result;
    idx = indices;
    found = 0;
    prev = -1;

    if (root == NULL || out == NULL || idx == NULL || count == 0) {
        return 0;
    }

    for (i = count; i > 0; i--) {
        target = *idx;
        if (prev > (s32) target || prev == -1) {
            jobj = root;
            cur = 0;
        } else {
            cur = prev;
        }

        while (jobj != NULL) {
            if (cur == (s32) target) {
                break;
            }
            saved = jobj;
            if (!(jobj->flags & JOBJ_INSTANCE) &&
                HSD_JObjGetChild(jobj) != NULL)
            {
                next_node = HSD_JObjGetChild(jobj);
            } else if (HSD_JObjGetNext(jobj) != NULL) {
                next_node = HSD_JObjGetNext(jobj);
            } else {
                while (true) {
                    if (HSD_JObjGetParent(saved) == NULL) {
                        next_node = NULL;
                        break;
                    }
                    if (HSD_JObjGetNext(HSD_JObjGetParent(saved)) != NULL) {
                        next_node = (saved = HSD_JObjGetNext(
                                         HSD_JObjGetParent(saved)));
                        break;
                    }
                    saved = HSD_JObjGetParent(saved);
                }
            }
            jobj = next_node;
            cur++;
        }

        *out = jobj;
        prev = cur;
        out++;
        if (jobj != NULL) {
            found++;
        }
        idx++;
    }

    return found;
}

static void* setImageFromPreloadedArchive(HSD_ImageDesc* image_desc,
                                          s16 entry_num)
{
    void* image_ptr = lbDvd_GetPreloadedArchive(entry_num);
    image_desc->image_ptr = image_ptr;
    return image_ptr;
}

HSD_ImageDesc* lb_800121FC(HSD_ImageDesc* image_desc, int width, int height,
                           GXTexFmt format, s16 entry_num)
{
    image_desc->width = width;
    image_desc->height = height;
    image_desc->mipmap = 0;
    image_desc->minLOD = 0.0f;
    image_desc->maxLOD = 0.0f;
    image_desc->format = format;
    HSD_ASSERT(41, !image_desc->image_ptr);
    {
        size_t buffer_size = GXGetTexBufferSize(
            image_desc->width, image_desc->height, image_desc->format, 0, 0);
        if (entry_num == 0 ||
            !setImageFromPreloadedArchive(image_desc, entry_num))
        {
            image_desc->image_ptr = HSD_MemAlloc((buffer_size + 0x1F) & ~0x1F);
        }
    }
    return image_desc;
}

void lb_800122C8(HSD_ImageDesc* image_desc, u16 origx, u16 origy, bool clear)
{
    HSD_ImageDescCopyFromEFB(image_desc, origx, origy, clear, true);
}

void lb_800122F0(HSD_ImageDesc* img, GXTexObj* tex, f32 factor)
{
    GXColor color0, color1, color2;

    color0.r = (u8) (s8) (255.0f - (179.0f * factor));
    color0.g = (u8) (s8) (68.4f * factor);
    color0.b = (u8) (s8) (60.8f * factor);

    color1.r = (u8) (s8) (150.0f * factor);
    color1.g = (u8) (s8) (255.0f - (120.0f * factor));
    color1.b = (u8) (s8) (120.0f * factor);

    color2.r = (u8) (s8) (29.0f * factor);
    color2.g = (u8) (s8) (26.099998f * factor);
    color2.b = (u8) (s8) (255.0f - (231.8f * factor));

    GXInitTexObj(tex, img->image_ptr, img->width, img->height, img->format,
                 GX_CLAMP, GX_CLAMP, (u8) img->mipmap);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(1);
    GXSetZMode(0, GX_ALWAYS, 0);
    GXLoadTexObj(tex, GX_TEXMAP0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    if (factor != 0.0f) {
        GXSetNumTevStages(3);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevKColor(GX_KCOLOR0, color0);
        GXSetTevKColor(GX_KCOLOR1, color1);
        GXSetTevKColor(GX_KCOLOR2, color2);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
        GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K2);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP3, GX_TEV_SWAP3);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                        GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                   GX_LO_CLEAR);
    GXSetColorUpdate(1);
    GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_OR, GX_GEQUAL, 0);
}

void lb_8001271C(GXTexObj* arg0, float x0, float arg2, float tex_width,
                 float tex_height, float scale_x, float scale_y)
{
    f32 t;
    f32 new_var;
    f32 s;
    f32 new_var2;
    f32 w, h, y0, x1, y_sum, y1;
    PAD_STACK(8);

    t = tex_width / GXGetTexObjWidth(arg0);
    s = tex_height / GXGetTexObjHeight(arg0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    w = tex_width * scale_x;
    h = tex_height * scale_y;
    y0 = -arg2;
    GXPosition2f32(x0, y0);
    x1 = x0 + w;
    new_var = arg2;
    y_sum = new_var + h;
    GXTexCoord2f32(0.0f, new_var2 = 0.0f);
    GXPosition2f32(x1, y0);
    if ((!x1) && (!x1)) {
    }
    GXTexCoord2f32(s, 0.0f);
    y1 = -y_sum;
    GXPosition2f32(x1, y1);
    GXTexCoord2f32(s, t);
    GXPosition2f32(x0, y1);
    y1 = new_var2;
    GXTexCoord2f32(y1, t);
    GXEnd();
}

void lb_8001285C(HSD_ImageDesc* image_desc, GXTexObj* tex_obj)
{
    PAD_STACK(4);
    GXInitTexObj(tex_obj, image_desc->image_ptr, image_desc->width,
                 image_desc->height, image_desc->format, GX_CLAMP, GX_CLAMP,
                 image_desc->mipmap);
    GXGetTexObjFmt(tex_obj);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetZMode(0, GX_ALWAYS, 0);
    GXLoadTexObj(tex_obj, GX_TEXMAP0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE,
                    GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                   GX_LO_CLEAR);
}

/// @todo Fake function to consume a stack temporary.
static inline void consume_color(GXColor color) {}

/// @todo Fake function to consume stack temporaries.
static inline void consume_blur_colors(GXColor color0, GXColor color1,
                                       GXColor color2, GXColor color3)
{
}

void lb_80012994(HSD_ImageDesc* img, u8 alpha, u8 blur_size, f32 x, f32 y,
                 f32 scale_x, f32 scale_y, f32 color_factor)
{
    GXTexObj tex;
    u16 w = img->width;
    u16 h = img->height;
    f32 y_p1, x_p1, y_m1, x_m1;
    f32 x_p2, x_m2, y_p2, y_m2;
    f32 off1 = (f32) blur_size / 64.0f;
    f32 off2 = 2.0f * off1;

    lb_800122F0(img, &tex, color_factor);
    PAD_STACK(8);

    ((GXColor*) &tex)[-4].a = alpha;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-4]);
    consume_color(((GXColor*) &tex)[-4]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x, y, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-6].a = 0x7F;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-6]);
    consume_color(((GXColor*) &tex)[-6]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_p1 = x + off1;
    lb_8001271C(&tex, x_p1, y, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-8].a = 0xA9;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-8]);
    consume_color(((GXColor*) &tex)[-8]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_m1 = x - off1;
    lb_8001271C(&tex, x_m1, y, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-10].a = 0xBF;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-10]);
    consume_color(((GXColor*) &tex)[-10]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_p1 = y + off1;
    lb_8001271C(&tex, x, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-12].a = 0xCC;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-12]);
    consume_color(((GXColor*) &tex)[-12]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_m1 = y - off1;
    lb_8001271C(&tex, x, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-14].a = 0xD4;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-14]);
    consume_color(((GXColor*) &tex)[-14]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-16].a = 0xDA;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-16]);
    consume_color(((GXColor*) &tex)[-16]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-18].a = 0xDF;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-18]);
    consume_color(((GXColor*) &tex)[-18]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-20].a = 0xE2;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-20]);
    consume_color(((GXColor*) &tex)[-20]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-22].a = 0xE5;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-22]);
    consume_color(((GXColor*) &tex)[-22]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_p2 = x + off2;
    lb_8001271C(&tex, x_p2, y, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-24].a = 0xE7;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-24]);
    consume_color(((GXColor*) &tex)[-24]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_m2 = x - off2;
    lb_8001271C(&tex, x_m2, y, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-26].a = 0xE9;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-26]);
    consume_color(((GXColor*) &tex)[-26]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p2, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-28].a = 0xEB;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-28]);
    consume_color(((GXColor*) &tex)[-28]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m2, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-30].a = 0xEC;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-30]);
    consume_color(((GXColor*) &tex)[-30]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p2, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-32].a = 0xEE;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-32]);
    consume_color(((GXColor*) &tex)[-32]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m2, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-34].a = 0xEF;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-34]);
    consume_color(((GXColor*) &tex)[-34]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_p2 = y + off2;
    lb_8001271C(&tex, x, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-36].a = 0xF0;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-36]);
    consume_color(((GXColor*) &tex)[-36]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_m2 = y - off2;
    lb_8001271C(&tex, x, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-38].a = 0xF0;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-38]);
    consume_color(((GXColor*) &tex)[-38]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-40].a = 0xF1;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-40]);
    consume_color(((GXColor*) &tex)[-40]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-42].a = 0xF2;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-42]);
    consume_color(((GXColor*) &tex)[-42]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    ((GXColor*) &tex)[-44].a = 0xF2;
    GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex)[-44]);
    consume_color(((GXColor*) &tex)[-44]);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    HSD_StateInvalidate(2);
}

static HSD_Chan chan0 = {
    NULL,
    GX_COLOR0,
    0,
    { 0x00, 0x00, 0x00, 0x00 },
    { 0xFF, 0xFF, 0xFF, 0x00 },
    GX_FALSE,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
};

static HSD_Chan chan1 = {
    NULL,
    GX_ALPHA0,
    0,
    { 0x00, 0x00, 0x00, 0xFF },
    { 0x00, 0x00, 0x00, 0xFF },
    GX_FALSE,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
};

void fn_80013614(HSD_GObj* gobj)
{
    struct CameraBlurData* data = gobj->user_data;
    u8 pad8[8];
    Mtx view_mtx;
    Mtx view_mtx2;
    GXTexObj tex_obj;

    if (data->x18 != NULL) {
        data->x18(gobj);
    }

    if (data->x12 == 1) {
        HSD_CObj* cobj = (HSD_CObj*) gobj->hsd_obj;
        HSD_ImageDesc* image;
        f32 x0;
        f32 x4;
        f32 x8;
        f32 xC;
        u8 x10;
        u8 x11;
        f32 alpha;

        alpha = data->x20;
        x11 = data->x11;
        x10 = data->x10;
        xC = data->xC;
        x8 = data->x8;
        x4 = data->x4;
        x0 = data->x0;
        image = data->x1C;

        HSD_CObjSetCurrent(cobj);
        HSD_StateSetZMode(0, 7, 0);
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx);
        GXLoadPosMtxImm(view_mtx, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0,
                          0x7D);
        HSD_SetupChannel(&chan0);
        HSD_SetupChannel(&chan1);
        HSD_StateSetNumChans(1);

        if (alpha != 0.0f) {
            GXSetScissor(0, 0x6E, 0x280, 0x122);
        }

        lb_80012994(image, x10, x11, x0, x4, x8, xC, alpha);
    } else {
        HSD_CObj* cobj = (HSD_CObj*) gobj->hsd_obj;
        HSD_ImageDesc* image;
        f32 x0;
        f32 x4;
        f32 x8;
        f32 xC;
        u8 x10;
        u16 width;
        u16 height;

        x10 = data->x10;
        xC = data->xC;
        x8 = data->x8;
        x4 = data->x4;
        x0 = data->x0;
        image = data->x1C;

        HSD_CObjSetCurrent(cobj);
        HSD_StateSetZMode(0, 7, 0);
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx2);
        GXLoadPosMtxImm(view_mtx2, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0,
                          0x7D);
        HSD_SetupChannel(&chan0);
        HSD_SetupChannel(&chan1);
        HSD_StateSetNumChans(1);

        width = image->width;
        height = image->height;
        lb_8001285C(image, &tex_obj);

        {
            ((GXColor*) &tex_obj)[-2].a = x10;
            GXSetTevColor(GX_TEVREG0, ((GXColor*) &tex_obj)[-2]);
            consume_blur_colors(
                ((GXColor*) &tex_obj)[-2], ((GXColor*) &tex_obj)[-2],
                ((GXColor*) &tex_obj)[-2], ((GXColor*) &tex_obj)[-2]);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                            GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, 1, GX_TEVPREV);
            lb_8001271C(&tex_obj, x0, x4, (f32) width, (f32) height, x8, xC);
        }
        HSD_StateInvalidate(2);
    }
}

void fn_800138AC(void* ptr)
{
    HSD_Free(ptr);
}

void lb_800138CC(HSD_GObj* gobj, HSD_GObjEvent arg1)
{
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x18 = arg1;
}

void lb_800138D8(HSD_GObj* gobj, s8 arg1)
{
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x12 = 1;
    data->x11 = arg1;
}

static const Vec3 lb_803B72A8 = { 0.0F, 0.0F, 1.0F };
static const Vec3 lb_803B72B4 = { 0.0F, 0.0F, 0.0F };

void lb_800138EC(s32 arg0, GObj_RenderFunc render_func, u32 arg2, s8 arg3,
                 f32 x, f32 y, f32 w, f32 h)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    struct lb_800138D8_t* data;
    HSD_RectS16 viewport;
    Scissor scissor;
    Vec3 eye;
    Vec3 interest;
    f32 zero = 0.0F;
    f32 roll;
    f32 far = 2.0F;
    f32 ortho_top = zero;
    f32 ortho_bot = -480.0F;
    f32 ortho_left = zero;
    f32 ortho_right = 640.0F;

    eye = lb_803B72A8;
    roll = zero;
    interest = lb_803B72B4;

    gobj = GObj_Create(14, 15, 0);
    cobj = HSD_CObjAlloc();

    viewport.xmin = 0;
    scissor.left = 0;
    viewport.xmax = 640;
    scissor.right = 640;
    viewport.ymin = 0;
    scissor.top = 0;
    viewport.ymax = 480;
    scissor.bottom = 480;

    HSD_CObjSetProjectionType(cobj, 3);
    HSD_CObjSetViewport(cobj, &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, roll);
    HSD_CObjSetNear(cobj, zero);
    HSD_CObjSetFar(cobj, far);
    HSD_CObjSetOrtho(cobj, ortho_top, ortho_bot, ortho_left, ortho_right);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);

    data = HSD_MemAlloc(sizeof(struct lb_800138D8_t));
    data->x0 = x;
    data->x4 = y;
    data->x8 = w;
    data->xC = h;
    data->x10 = arg3;
    data->x12 = 0;
    data->x1C = arg0;
    data->x18 = 0;
    GObj_InitUserData(gobj, 0, fn_800138AC, data);

    if (render_func == NULL) {
        GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) (Event) fn_80013614, arg2);
    } else {
        GObj_SetupGXLinkMax(gobj, render_func, arg2);
    }
}

HSD_CObj* lb_80013B14(HSD_CameraDescPerspective* desc)
{
    HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) desc);
    Scissor scissor;

    if (HSD_CObjGetProjectionType(cobj) == 1 &&
        HSD_CObjGetAspect(cobj) == 1.18F)
    {
        HSD_CObjSetAspect(cobj, 1.2173333F);
    }
    HSD_CObjGetScissor(cobj, &scissor);
    if (scissor.right > 0x280) {
        scissor.right = 0x280;
    }
    if (scissor.bottom > 0x1E0) {
        scissor.bottom = 0x1E0;
    }
    HSD_CObjSetScissor(cobj, &scissor);
    return cobj;
}
