#include "dolphin/gx/GXStruct.h"
#define SOBJLIB_INTERNAL
#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "objalloc.h"
#include "pobj.h"
#include "sobjlib.h"
#include "state.h"
#include "tev.h"
#include "tobj.h"

#include "dolphin/gx.h"

#include <math.h>
#include <dolphin/os.h>

/* 4D4540 */ u8 HSD_SObjLib_804D7960;

GObjFunc HSD_SObjLib_8040C3A0[] = { (void*) HSD_SObjLib_803A4740 };

GObjFuncs HSD_SObjLib_8040C3A4 = {
    NULL,
    1,
    HSD_SObjLib_8040C3A0,
};

HSD_ObjAllocData HSD_SObjLib_804D10E0;

static void order_data(void)
{
    (void) __FILE__;
    (void) "BadOBJ for SOBJ-displayfunc\n";
}

void HSD_SObjLib_803A44A4(void)
{
    HSD_ObjAllocInit(&HSD_SObjLib_804D10E0, 0x9C, 4);
}

void HSD_SObjLib_803A44D4(HSD_GObj* gobj, HSD_SObj* sobj, u8 priority)
{
    HSD_SObj* cur;
    HSD_SObj* next;

    PAD_STACK(16);

    cur = sobj->prev;
    if (cur != NULL || sobj->next != NULL) {
        if (cur != NULL) {
            cur->next = sobj->next;
        } else {
            HSD_GObjObject_80390ADC(gobj);
            HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj->next);
            sobj->next->prev = NULL;
        }

        if (sobj->next != NULL) {
            sobj->next->prev = sobj->prev;
        } else {
            sobj->prev->next = NULL;
        }

        sobj->next = NULL;
        sobj->prev = NULL;
    } else {
        if (gobj->hsd_obj == sobj) {
            HSD_GObjObject_80390ADC(gobj);
        }
    }

    cur = gobj->hsd_obj;
    if (cur == NULL) {
        HSD_GObjObject_80390ADC(gobj);
        HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj);
    } else {
        cur = gobj->hsd_obj;
        next = cur;
        while (next->next != NULL && next->x44 <= (u8) priority) {
            next = next->next;
        }

        if (next->next == NULL && next->x44 <= (u8) priority) {
            next->next = sobj;
            sobj->prev = next;
        } else if (next == cur) {
            sobj->next = cur;
            ((HSD_SObj*) gobj->hsd_obj)->prev = sobj;
            HSD_GObjObject_80390ADC(gobj);
            HSD_GObjObject_80390A70(gobj, HSD_SObjLib_804D7960, sobj);
        } else {
            next->prev->next = sobj;
            sobj->prev = next->prev;
            next->prev = sobj;
            sobj->next = next;
        }
    }

    sobj->x44 = priority;
}

void HSD_SObjLib_803A466C(HSD_SObj* sobj)
{
    PAD_STACK(8);

    if (sobj == NULL) {
        return;
    }

    if (sobj->prev != NULL || sobj->next != NULL) {
        if (sobj->prev != NULL) {
            sobj->prev->next = sobj->next;
        } else {
            HSD_GObjObject_80390ADC(sobj->gobj);
            HSD_GObjObject_80390A70(sobj->gobj, HSD_SObjLib_804D7960,
                                    sobj->next);
            sobj->next->prev = NULL;
        }

        if (sobj->next != NULL) {
            sobj->next->prev = sobj->prev;
        } else {
            sobj->prev->next = NULL;
        }

        sobj->next = NULL;
        sobj->prev = NULL;
    } else {
        if (sobj->gobj->hsd_obj == sobj) {
            HSD_GObjObject_80390ADC(sobj->gobj);
        }
    }

    HSD_ObjFree(&HSD_SObjLib_804D10E0, sobj);
}

void HSD_SObjLib_803A4740(HSD_SObj* sobj)
{
    HSD_SObj* next;

    while (sobj != NULL) {
        next = sobj->next;
        HSD_SObjLib_803A466C(sobj);
        sobj = next;
    }
}

HSD_SObj* HSD_SObjLib_803A477C(HSD_GObj* gobj, HSD_SObjDesc* desc,
                               GXTexWrapMode wrap_s, GXTexWrapMode wrap_t,
                               u8 priority, u8 use_secondary)
{
    HSD_ImageDesc* image;
    HSD_Tlut* tlut;
    HSD_ImageDesc* image2;
    HSD_SObj* sobj;
    f32 inv_width;
    f32 inv_height;

    if (use_secondary) {
        image = desc->image;
        tlut = desc->tlut;
        image2 = desc->image2;
    } else {
        image = desc->image;
        image2 = NULL;
        tlut = desc->tlut;
    }

    sobj = HSD_ObjAlloc(&HSD_SObjLib_804D10E0);
    HSD_ASSERT(287, sobj);

    if (tlut != NULL) {
        GXInitTlutObj(&sobj->x70_tlutobj, tlut->lut, tlut->fmt,
                      tlut->n_entries);
        GXInitTexObjCI(&sobj->x50_texobj, image->image_ptr, image->width,
                       image->height, image->format, wrap_s, wrap_t,
                       (u8) image->mipmap, tlut->tlut_name);
    } else {
        GXInitTexObj(&sobj->x50_texobj, image->image_ptr, image->width,
                     image->height, image->format, wrap_s, wrap_t,
                     (u8) image->mipmap);
    }

    if (use_secondary) {
        GXInitTexObj(&sobj->x7C_texobj, image2->image_ptr, image2->width,
                     image2->height, image2->format, wrap_s, wrap_t,
                     (u8) image2->mipmap);
    }

    sobj->x0 = NULL;
    sobj->prev = NULL;
    sobj->next = NULL;
    sobj->x14 = 0.0F;
    sobj->x10 = 0.0F;
    sobj->x18 = 0.0F;
    sobj->x20 = 1.0F;
    sobj->x1C = 1.0F;
    sobj->x3F = 0xFF;
    sobj->x3E = 0xFF;
    sobj->x3D = 0xFF;
    sobj->x3C = 0xFF;
    sobj->x3B = 0xFF;
    sobj->x3A = 0xFF;
    sobj->x39 = 0xFF;
    sobj->x38 = 0xFF;
    sobj->x40 = 0;
    sobj->x48 = 0;
    sobj->x4C_callback = NULL;
    sobj->gobj = gobj;

    if (use_secondary) {
        sobj->x40 |= 4;
    }

    sobj->x34 = image->width;
    sobj->x36 = image->height;
    inv_width = 1.0F / (f32) GXGetTexObjWidth(&sobj->x50_texobj);
    inv_height = 1.0F / (f32) GXGetTexObjHeight(&sobj->x50_texobj);
    sobj->x24 = 0.0F;
    sobj->x28 = 0.0F;
    sobj->x2C = (f32) sobj->x34 * inv_width;
    sobj->x30 = (f32) sobj->x36 * inv_height;
    HSD_SObjLib_803A44D4(gobj, sobj, priority);
    return sobj;
}

void HSD_SObjLib_803A49E0(HSD_GObj* gobj, int unused)
{
    HSD_SObj* sobj;

    PAD_STACK(8);

    sobj = gobj->hsd_obj;
    while (sobj != NULL) {
        if (HSD_SObjLib_804D7960 != gobj->obj_kind) {
            OSReport("BadOBJ for SOBJ-displayfunc\n");
            return;
        }
        if (sobj->x4C_callback != NULL) {
            sobj->x4C_callback(sobj);
        }
        HSD_SObjLib_803A4A68(sobj);
        sobj = sobj->next;
    }
}

const GXColorS10 HSD_SObjLib_804DEA80 = { 0xFFA6, 0x0000, 0xFF8E, 0x0087 };
const GXColor HSD_SObjLib_804DEA88 = { 0x00, 0x00, 0xE2, 0x58 };
const GXColor HSD_SObjLib_804DEA8C = { 0xB3, 0x00, 0x00, 0xB6 };
const GXColor HSD_SObjLib_804DEA90 = { 0xFF, 0x00, 0xFF, 0x80 };

void HSD_SObjLib_803A4A68(HSD_SObj* sobj)
{
    f32 x_cos;
    f32 origin_x;
    f32 origin_y;
    f32 angle;
    f32 center_width;
    f32 center_height;
    f32 sin_half;
    f32 cos_val;
    f32 cos_half;
    f32 width;
    f32 height;
    f32 x_sin;
    f32 y_sin;
    f32 y_cos;
    f32 tex_s;
    f32 tex_t;
    f32 tex_s_max;
    f32 tex_t_max;
    f32 left_x;
    f32 left_y;
    f32 right_x;
    f32 right_y;
    u16 obj_width;
    u16 obj_height;
    u8 tex_fmt;
    GXColorS10 tev_color;
    GXColor k_color;

    PAD_STACK(0x20);

    if (sobj->x40 & 1) {
        return;
    }

    obj_width = sobj->x34;
    obj_height = sobj->x36;
    tex_fmt = GXGetTexObjFmt(&sobj->x50_texobj);

    if (sobj->x40 & 2) {
        origin_x = sobj->x10;
        origin_y = sobj->x14;
    } else {
        center_width = (f32) obj_width * sobj->x1C;
        center_height = (f32) obj_height * sobj->x20;
        origin_x = (center_width * 0.5f) + sobj->x10;
        origin_y = (center_height * 0.5f) + sobj->x14;
    }

    GXClearVtxDesc();
    if (sobj->x40 & 4) {
        GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
        if (sobj->x40 & 8) {
            HSD_StateSetZMode(1, GX_LESS, 0);
        } else {
            HSD_StateSetZMode(1, GX_LESS, 1);
        }
        HSD_StateSetZCompLoc(0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTexGens(1);
        GXSetNumTevStages(2);
    } else {
        HSD_StateSetZMode(1, GX_ALWAYS, 0);
        GXSetCullMode(GX_CULL_BACK);
        if (sobj->x40 & 0x10) {
            GXSetNumTexGens(2);
            GXSetNumTevStages(4);
        } else {
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);
        }
    }

    if ((u8) (tex_fmt - GX_TF_C4) <= 1U) {
        GXLoadTlut(&sobj->x70_tlutobj, GX_TLUT0);
    }
    if (!(sobj->x40 & 0x10)) {
        GXLoadTexObj(&sobj->x50_texobj, GX_TEXMAP0);
    }

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);

    if (sobj->x40 & 0x10) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_QUARTER,
                        GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ONE,
                        GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_QUARTER,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2,
                        GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ONE,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_FALSE, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K1_A);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);

        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_APREV, GX_CC_CPREV, GX_CC_QUARTER,
                        GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_TRUE, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K2);

        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

        tev_color = HSD_SObjLib_804DEA80;
        GXSetTevColorS10(GX_TEVREG0, tev_color);

        k_color = HSD_SObjLib_804DEA88;
        GXSetTevKColor(GX_KCOLOR0, k_color);
        k_color = HSD_SObjLib_804DEA8C;
        GXSetTevKColor(GX_KCOLOR1, k_color);
        k_color = HSD_SObjLib_804DEA90;
        GXSetTevKColor(GX_KCOLOR2, k_color);

        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE,
                              GX_CH_ALPHA);
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (sobj->x40 & 4) {
            GXLoadTexObj(&sobj->x7C_texobj, GX_TEXMAP1);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        }
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

        if (sobj->x40 & 4) {
            GXColor z_color = sobj->x3C_color;

            GXSetTevColor(GX_TEVREG0, z_color);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                            GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                            GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
        } else {
            switch (tex_fmt) {
            case GX_TF_I4:
            case GX_TF_I8:
                GXSetTevColor(GX_TEVREG0, sobj->x38_color);
                GXSetTevColor(GX_TEVREG1, sobj->x3C_color);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case GX_TF_IA4:
            case GX_TF_IA8:
                GXSetTevColor(GX_TEVREG0, sobj->x38_color);
                GXSetTevColor(GX_TEVREG1, sobj->x3C_color);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case GX_TF_RGB565:
                GXSetTevColor(GX_TEVREG0, sobj->x3C_color);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A0);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            case GX_TF_RGB5A3:
            case GX_TF_RGBA8:
            case GX_TF_C4:
            case GX_TF_C8:
            case GX_TF_C14X2:
            case GX_TF_CMPR:
                GXSetTevColor(GX_TEVREG0, sobj->x3C_color);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0,
                                GX_CA_ZERO);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                break;
            }
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
        }
    }

    sin_half = 0.5f * sinf(sobj->x18);
    angle = sobj->x18;
    cos_val = cosf(angle);
    cos_half = 0.5f * -cos_val;
    width = (f32) obj_width * sobj->x1C;
    height = (f32) obj_height * sobj->x20;
    x_sin = sin_half * width;
    x_cos = cos_half * width;
    y_sin = sin_half * height;
    y_cos = cos_half * height;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    left_y = origin_y + y_cos;
    right_x = origin_x + y_sin;
    right_y = origin_y - y_cos;
    GXPosition2f32(x_cos + right_x, -(left_y - x_sin));
    left_x = origin_x - y_sin;
    tex_t = sobj->x28;
    tex_s = sobj->x24;
    GXTexCoord2f32(tex_s, tex_t);

    GXPosition2f32(right_x - x_cos, -(x_sin + left_y));
    tex_s_max = sobj->x2C;
    GXTexCoord2f32(tex_s_max, tex_t);

    GXPosition2f32(left_x - x_cos, -(x_sin + right_y));
    tex_t_max = sobj->x30;
    GXTexCoord2f32(tex_s_max, tex_t_max);

    GXPosition2f32(x_cos + left_x, -(right_y - x_sin));
    GXTexCoord2f32(tex_s, tex_t_max);
    GXEnd();

    if (sobj->x40 & 4) {
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    HSD_ClearVtxDesc();
    HSD_StateSetZMode(1, GX_LEQUAL, 1);
}

static HSD_Chan lbl_8040C418 = {
    NULL,       GX_COLOR0,  0,          { 0 },         { 0xFF, 0xFF, 0xFF },
    false,      GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP,
    GX_AF_NONE,
};

static HSD_Chan lbl_8040C448 = {
    NULL,       GX_ALPHA0,  0,          { 0, 0, 0, 0xFF }, { 0, 0, 0, 0xFF },
    false,      GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL,     GX_DF_CLAMP,
    GX_AF_NONE,
};

void HSD_SObjLib_803A54EC(HSD_GObj* gobj, int unused)
{
    Mtx viewmtx;

    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), viewmtx);
        GXLoadPosMtxImm(viewmtx, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY,
                          GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY,
                          GX_FALSE, GX_PTIDENTITY);
        HSD_SetupChannel(&lbl_8040C418);
        HSD_SetupChannel(&lbl_8040C448);
        HSD_StateSetNumChans(1);
        HSD_GObj_80390ED0(gobj, 1);
        HSD_CObjEndCurrent();
    } else {
        OSReport("Out CameraDisp Range\n");
    }
    HSD_StateInvalidate(-1);
    HSD_StateSetZMode(1, 3, 1);
}

void HSD_SObjLib_803A55DC(HSD_GObj* gobj, u16 width, u16 height, int priority)
{
    HSD_CObj* cobj;
    Scissor viewport;
    Scissor scissor;
    Vec3 eye = { 0, 0, 1 };
    Vec3 interest = { 0, 0, 0 };

    f32 roll = 0.0F;
    f32 near_val = roll;
    f32 far_val = 2.0f;
    f32 top = roll;
    f32 bottom = -height;
    f32 left = roll;
    f32 right = width;

    viewport.left = 0;
    viewport.right = width;
    viewport.top = 0;
    viewport.bottom = height;

    scissor.left = 0;
    scissor.right = width;
    scissor.top = 0;
    scissor.bottom = height;

    cobj = HSD_CObjAlloc();
    HSD_CObjSetProjectionType(cobj, PROJ_ORTHO);
    HSD_CObjSetViewport(cobj, (HSD_RectS16*) &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, roll);
    HSD_CObjSetNear(cobj, near_val);
    HSD_CObjSetFar(cobj, far_val);
    HSD_CObjSetOrtho(cobj, top, bottom, left, right);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, HSD_SObjLib_803A54EC, priority);
}
