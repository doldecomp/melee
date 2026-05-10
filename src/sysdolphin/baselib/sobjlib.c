#include "sobjlib.h"

#include "cobj.h"
#include "gobj.h"
#include "gobjgxlink.h"
#include "gobjobject.h"
#include "objalloc.h"
#include "state.h"
#include "tev.h"
#include "tobj.h"

#include "baselib/debug.h"
#include "baselib/pobj.h"
#include "dolphin/gx.h"

#include <dolphin/os.h>
#include <MSL/trigf.h>

static const GXColorS10 lbl_804DEA80 = { -90, 0, -114, 135 };
static const GXColor lbl_804DEA88 = { 0x00, 0x00, 0xE2, 0x58 };
static const GXColor lbl_804DEA8C = { 0xB3, 0x00, 0x00, 0xB6 };
static const GXColor lbl_804DEA90 = { 0xFF, 0x00, 0xFF, 0x80 };
/* 004D4540 */ extern u8 HSD_SObjLib_804D7960;
/* 004CDCC0 */ extern HSD_ObjAllocData HSD_SObjLib_804D10E0;
typedef struct SObjLibData {
    /* 0x00 */ UNK_T x0;
    /* 0x04 */ GObjFuncs x4_funcs;
    /* 0x10 */ s8 x10_filename[10];
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ char x1C_errmsg[32];
    /* 0x3C */ void* x3C_jumptable[15];
    /* 0x78 */ HSD_Chan x78_chan0;
    /* 0xA8 */ HSD_Chan xA8_chan1;
    /* 0xD8 */ char xD8_errmsg2[24];
} SObjLibData;

typedef struct SObjLibSObjDesc {
    /* 0x00 */ HSD_ImageDesc* x0;
    /* 0x04 */ HSD_TlutDesc* x4;
    /* 0x08 */ HSD_ImageDesc* x8;
} SObjLibSObjDesc;

HSD_ObjAllocData HSD_SObjLib_804D10E0;

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

HSD_SObj* HSD_SObjLib_803A477C(HSD_GObj* gobj, int desc_arg, int wrap_s,
                               int wrap_t, u8 priority, int use_x8)
{
    s32 tlut_name;
    f32 temp_f31;
    f32 temp_f30;
    HSD_ImageDesc* image;
    HSD_TlutDesc* tlut;
    HSD_ImageDesc* image2;
    HSD_SObj* sobj;
    SObjLibSObjDesc* desc = (SObjLibSObjDesc*) desc_arg;

    if ((u8) use_x8 != 0) {
        image = desc->x0;
        tlut = desc->x4;
        image2 = desc->x8;
    } else {
        image = desc->x0;
        image2 = NULL;
        tlut = desc->x4;
    }

    sobj = HSD_ObjAlloc(&HSD_SObjLib_804D10E0);
    HSD_ASSERT(0x11F, sobj);

    if (tlut != NULL) {
        GXInitTlutObj(&sobj->x70_tlutobj, tlut->lut, tlut->fmt,
                      tlut->n_entries);
        tlut_name = tlut->tlut_name;
        GXInitTexObjCI(&sobj->x50_texobj, image->image_ptr, image->width,
                       image->height, (GXCITexFmt) image->format, wrap_s,
                       wrap_t, (u8) image->mipmap, tlut_name);
    } else {
        GXInitTexObj(&sobj->x50_texobj, image->image_ptr, image->width,
                     image->height, image->format, wrap_s, wrap_t,
                     (u8) image->mipmap);
    }

    if ((u8) use_x8 != 0) {
        GXInitTexObj(&sobj->x7C_texobj, image2->image_ptr, image2->width,
                     image2->height, image2->format, wrap_s, wrap_t,
                     (u8) image2->mipmap);
    }

    sobj->x0 = NULL;
    sobj->prev = NULL;
    sobj->next = NULL;
    sobj->x14 = 0.0f;
    sobj->x10 = 0.0f;
    sobj->x18 = 0.0f;
    sobj->x20 = 1.0f;
    sobj->x1C = 1.0f;
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
    if ((u8) use_x8 != 0) {
        sobj->x40 |= 4;
    }
    sobj->x34 = image->width;
    sobj->x36 = image->height;
    temp_f31 = 1.0f / (f32) GXGetTexObjWidth(&sobj->x50_texobj);
    temp_f30 = 1.0f / (f32) GXGetTexObjHeight(&sobj->x50_texobj);
    sobj->x24 = 0.0f;
    sobj->x28 = 0.0f;
    sobj->x2C = (f32) sobj->x34 * temp_f31;
    sobj->x30 = (f32) sobj->x36 * temp_f30;
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

void HSD_SObjLib_803A4A68(HSD_SObj* sobj)
{
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    f32 temp_f0;
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f31;
    f32 temp_f5;
    f32 temp_f7;
    f32 temp_f8;
    f32 var_f29;
    f32 var_f30;
    u16 temp_r30;
    u16 temp_r31;
    u8 temp_r29;
    PAD_STACK(0x20);

    if (sobj->x40 & 1) {
        return;
    }

    temp_r31 = sobj->x34;
    temp_r30 = sobj->x36;
    temp_r29 = GXGetTexObjFmt(&sobj->x50_texobj);
    if (sobj->x40 & 2) {
        var_f30 = sobj->x10;
        var_f29 = sobj->x14;
    } else {
        var_f30 = ((f32) temp_r31 * sobj->x1C * 0.5F) + sobj->x10;
        var_f29 = ((f32) temp_r30 * sobj->x20 * 0.5F) + sobj->x14;
    }

    GXClearVtxDesc();
    if (sobj->x40 & 4) {
        GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0U);
        if (sobj->x40 & 8) {
            HSD_StateSetZMode(1, 1, 0);
        } else {
            HSD_StateSetZMode(1, 1, 1);
        }
        HSD_StateSetZCompLoc(0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTexGens(1U);
        GXSetNumTevStages(2U);
    } else {
        HSD_StateSetZMode(1, 7, 0);
        GXSetCullMode(GX_CULL_BACK);
        if (sobj->x40 & 0x10) {
            GXSetNumTexGens(2U);
            GXSetNumTevStages(4U);
        } else {
            GXSetNumTexGens(1U);
            GXSetNumTevStages(1U);
        }
    }

    if ((u8) (temp_r29 - 8) <= 1U) {
        GXLoadTlut(&sobj->x70_tlutobj, 0U);
    }
    if (!(sobj->x40 & 0x10)) {
        GXLoadTexObj(&sobj->x50_texobj, GX_TEXMAP0);
    }
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0U);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0U);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetColorUpdate(1U);
    GXSetAlphaUpdate(0U);
    if (sobj->x40 & 0x10) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_QUARTER,
                        GX_CC_C0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        0U, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ONE,
                        GX_CA_A0);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                        0U, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K0_A);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_QUARTER,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2,
                        0U, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_ONE,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                        0U, GX_TEVPREV);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K1_A);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        1U, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        1U, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR_NULL);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_APREV, GX_CC_CPREV, GX_CC_QUARTER,
                        GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        1U, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        1U, GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K2);
        GXSetAlphaCompare(GX_ALWAYS, 0U, GX_AOP_OR, GX_ALWAYS, 0U);
        GXSetTevColorS10(GX_TEVREG0, lbl_804DEA80);
        GXSetTevKColor(GX_KCOLOR0, lbl_804DEA88);
        GXSetTevKColor(GX_KCOLOR1, lbl_804DEA8C);
        GXSetTevKColor(GX_KCOLOR2, lbl_804DEA90);
        GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN,
                              GX_CH_BLUE, GX_CH_ALPHA);
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    } else {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        if (sobj->x40 & 4) {
            GXLoadTexObj(&sobj->x7C_texobj, GX_TEXMAP1);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1,
                          GX_COLOR0A0);
        }
        GXSetAlphaCompare(GX_ALWAYS, 0U, GX_AOP_OR, GX_ALWAYS, 0U);
        if (sobj->x40 & 4) {
            sp4C = *(s32*) &sobj->x3C;
            GXSetTevColor(GX_TEVREG0, *(GXColor*) &sp4C);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                            GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, 1U, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                            GX_CC_CPREV);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, 1U, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, 1U, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                            GX_CA_A0);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO,
                            GX_CS_SCALE_1, 1U, GX_TEVPREV);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
        } else {
            switch (temp_r29) {
            case 0:
            case 1:
                sp48 = *(s32*) &sobj->x38;
                GXSetTevColor(GX_TEVREG0, *(GXColor*) &sp48);
                sp44 = *(s32*) &sobj->x3C;
                GXSetTevColor(GX_TEVREG1, *(GXColor*) &sp44);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                break;
            case 2:
            case 3:
                sp40 = *(s32*) &sobj->x38;
                GXSetTevColor(GX_TEVREG0, *(GXColor*) &sp40);
                sp3C = *(s32*) &sobj->x3C;
                GXSetTevColor(GX_TEVREG1, *(GXColor*) &sp3C);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_C1, GX_CC_TEXC,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_TEXA);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                break;
            case 4:
                sp38 = *(s32*) &sobj->x3C;
                GXSetTevColor(GX_TEVREG0, *(GXColor*) &sp38);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO,
                                GX_CA_ZERO, GX_CA_A0);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                break;
            case 5:
            case 6:
            case 8:
            case 9:
            case 10:
            case 14:
                sp34 = *(s32*) &sobj->x3C;
                GXSetTevColor(GX_TEVREG0, *(GXColor*) &sp34);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0,
                                GX_CC_ZERO);
                GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0,
                                GX_CA_ZERO);
                GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO,
                                GX_CS_SCALE_1, 1U, GX_TEVPREV);
                break;
            }
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                           GX_LO_CLEAR);
        }
    }

    temp_f28 = 0.5F * sinf(sobj->x18);
    temp_f5 = 0.5F * -cosf(sobj->x18);
    temp_f0 = (f32) temp_r30 * sobj->x20;
    temp_f31 = temp_f5 * ((f32) temp_r31 * sobj->x1C);
    temp_f27 = temp_f28 * ((f32) temp_r31 * sobj->x1C);
    temp_f28_2 = temp_f28 * temp_f0;
    temp_f26 = temp_f5 * temp_f0;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4U);
    temp_f0 = var_f29 + temp_f26;
    temp_f5 = var_f30 + temp_f28_2;
    temp_f7 = var_f29 - temp_f26;
    *(volatile f32*) 0xCC008000 = temp_f31 + temp_f5;
    temp_f8 = var_f30 - temp_f28_2;
    *(volatile f32*) 0xCC008000 = -(temp_f0 - temp_f27);
    *(volatile f32*) 0xCC008000 = sobj->x24;
    *(volatile f32*) 0xCC008000 = sobj->x28;
    *(volatile f32*) 0xCC008000 = temp_f5 - temp_f31;
    *(volatile f32*) 0xCC008000 = -(temp_f27 + temp_f0);
    *(volatile f32*) 0xCC008000 = sobj->x2C;
    *(volatile f32*) 0xCC008000 = sobj->x28;
    *(volatile f32*) 0xCC008000 = temp_f8 - temp_f31;
    *(volatile f32*) 0xCC008000 = -(temp_f27 + temp_f7);
    *(volatile f32*) 0xCC008000 = sobj->x2C;
    *(volatile f32*) 0xCC008000 = sobj->x30;
    *(volatile f32*) 0xCC008000 = temp_f31 + temp_f8;
    *(volatile f32*) 0xCC008000 = -(temp_f7 - temp_f27);
    *(volatile f32*) 0xCC008000 = sobj->x24;
    *(volatile f32*) 0xCC008000 = sobj->x30;
    if (sobj->x40 & 4) {
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0U);
    }
    HSD_StateInvalidate(-1);
    HSD_StateInitTev();
    HSD_ClearVtxDesc();
    HSD_StateSetZMode(1, 3, 1);
}

static HSD_Chan lbl_8040C418 = {
    NULL,
    GX_COLOR0,
    0,
    { 0 },
    { 0xFF, 0xFF, 0xFF },
    false,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
};
static HSD_Chan lbl_8040C448 = {
    NULL,
    GX_ALPHA0,
    0,
    { 0, 0, 0, 0xFF },
    { 0, 0, 0, 0xFF },
    false,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
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

/* @todo 99.84% match - near_val variable forces 6 FPR saves but adds
 * 4 bytes to stack, shifting local offsets by 4 */
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
