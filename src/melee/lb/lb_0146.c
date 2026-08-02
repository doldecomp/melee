#include "lb/types.h"

#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/psstructs.h>
#include <baselib/tobj.h>

bool lb_80014638(struct lb_80014638_arg0_t* arg0,
                 struct lb_80014638_arg1_t* arg1)
{
    Vec3 sp30, sp24, sp18;
    PAD_STACK(8);

    sp30 = arg0->x0;
    sp24 = arg0->xC;
    sp18 = arg1->x8;
    sp30.x = sp30.x + arg1->unk_x;
    sp30.y += arg1->unk_x;
    sp30.z += arg1->unk_y;
    if (sp30.z < sp24.z) {
        return false;
    }
    if (sp30.z < sp18.z || sp24.z > sp18.z) {
        return false;
    }
    {
        float z = sp18.z;
        if (((sp24.z - sp30.z) < 0.0F ? -(sp24.z - sp30.z) : sp24.z - sp30.z) <
            0.01F)
        {
            z = 1.0F;
        } else {
            z = (z - sp30.z) / (sp24.z - sp30.z);
        }
        if (z * (sp24.x - sp30.x) + sp30.x > sp18.y) {
            return false;
        }
        if (z * (sp24.y - sp30.y) + sp30.y < sp18.x) {
            return false;
        }
    }
    return true;
}

/* 4D3760 */ GXColor lb_ColorWhite = { 255, 255, 255, 255 };
/* 4D3764 */ GXColor lb_ColorBlack = { 0, 0, 0, 255 };
/* 4D3768 */ static GXColor red = { 255, 0, 0, 255 };
/* 4D376C */ static GXColor translucent_red = { 255, 0, 0, 64 };
/* 4D3770 */ static GXColor yellow = { 255, 255, 0, 255 };

bool lb_80014770(Vec3* arg0, int arg1)
{
    if ((u32) arg1 == 2U) {
        Vec3* near_pt;
        Vec3* far_pt;
        GXColor* near_clr;
        GXColor* far_clr;

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                       GX_LO_NOOP);
        GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetZCompLoc(GX_FALSE);
        GXSetNumTexGens(0);
        GXSetTevClampMode(GX_TEVSTAGE0, 0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0,
                      GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_NONE);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        {
            MtxPtr mtx = HSD_CObjGetCurrent()->view_mtx;
            GXLoadPosMtxImm(mtx, 0);
        }
        GXSetCurrentMtx(0);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 5);

        if (arg0[1].z > arg0[0].z) {
            near_pt = &arg0[1];
            far_pt = &arg0[0];
            near_clr = &red;
            far_clr = &translucent_red;
        } else {
            near_pt = &arg0[0];
            far_pt = &arg0[1];
            near_clr = &translucent_red;
            far_clr = &red;
        }

        GXPosition3f32(near_pt->y, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(near_pt->x, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(far_pt->y, far_pt->z, 0.0f);
        GXColor4u8(far_clr->r, far_clr->g, far_clr->b, far_clr->a);

        GXPosition3f32(near_pt->x, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(far_pt->x, far_pt->z, 0.0f);
        GXColor4u8(far_clr->r, far_clr->g, far_clr->b, far_clr->a);

        GXEnd();
        PAD_STACK(8);
        return true;
    }
    return false;
}

bool lb_800149E0(Mtx arg0, u32 arg1)
{
    PAD_STACK(16);
    if (arg1 == 0) {
        HSD_StateInitDirect(0, 2);
        {
            MtxPtr mtx = HSD_CObjGetCurrent()->view_mtx;
            GXLoadPosMtxImm(mtx, 0);
            GXSetLineWidth(12, GX_TO_ONE);
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
            {
                float y = arg0[1][0];
                GXPosition3f32(arg0[0][2], y, 0.0f);
                GXColor4u8(yellow.r, yellow.g, yellow.b, yellow.a);

                GXPosition3f32(arg0[0][3], y, 0.0f);
                GXColor4u8(yellow.r, yellow.g, yellow.b, yellow.a);
            }
            GXEnd();
        }
        return true;
    }
    return false;
}
