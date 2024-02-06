#include "lbgx.h"

#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLight.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXVert.h>
#include <baselib/cobj.h>

bool lbGx_8001E2F8(f32* arg0, f32* arg1, u8* arg2, u32 arg3, f32 argf1)
{
    HSD_CObj* cobj;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f3;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 temp_f5;
    u8 r0, r5, r6, r7;
    u8 _[16];

    if (arg3 == 2) {
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetBlendMode(1, 4, 5, 5);
        GXSetAlphaCompare(4, 0, 0, 4, 0);
        GXSetZMode(1, 3, 0);
        GXSetZCompLoc(0);
        GXSetNumTexGens(0);
        GXSetTevClampMode(0, 0);
        GXSetNumTevStages(1);
        GXSetTevOrder(0, 0xff, 0xff, 4);
        GXSetTevOp(0, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
        GXSetCullMode(0);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(0xb, 1);
        cobj = HSD_CObjGetCurrent();
        GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtrDirect(cobj), 0);
        GXSetCurrentMtx(0);
        GXBegin(0x98, 0, 5);
        temp_f4 = arg0[0] * argf1 + arg1[0];
        temp_f2 = arg0[2];
        temp_f1 = arg1[1] + arg0[1];
        temp_f3 = arg0[3];
        temp_f5 = temp_f4 + temp_f2;
        temp_f2_2 = temp_f4 - temp_f2;
        temp_f4_2 = temp_f3 + temp_f1;
        temp_f1_2 = temp_f1 - temp_f3;
        GXPosition3f32(temp_f5, temp_f4_2, 0.0f);
        r7 = arg2[3];
        r6 = arg2[2];
        r5 = arg2[1];
        r0 = arg2[0];
        GXPosition2u8(r0, r5);
        GXPosition2u8(r6, r7);
        GXPosition3f32(temp_f2_2, temp_f4_2, 0.0f);
        GXPosition2u8(r0, r5);
        GXPosition2u8(r6, r7);
        GXPosition3f32(temp_f5, temp_f1_2, 0.0f);
        GXPosition2u8(r0, r5);
        GXPosition2u8(r6, r7);
        GXPosition3f32(temp_f2_2, temp_f4_2, 0.0f);
        GXPosition2u8(r0, r5);
        GXPosition2u8(r6, r7);
        GXPosition3f32(temp_f2_2, temp_f1_2, 0.0f);
        GXPosition2u8(r0, r5);
        GXPosition2u8(r6, r7);
        GXEnd();
        return 1;
    }

    return 0;
}
