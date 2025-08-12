#include "lbgx.h"

#include <placeholder.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>

bool lbGx_8001E2F8(Vec4* arg0, Vec3* arg1, U8Vec4* arg2, u32 arg3, float argf1)
{
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
        GXSetTevOrder(0, 255, 255, 4);
        GXSetTevOp(0, 4);
        GXSetNumChans(1);
        GXSetChanCtrl(4, 0, 0, 1, 0, 0, 2);
        GXSetCullMode(0);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        GXSetVtxAttrFmt(0, 11, 1, 5, 0);
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(11, 1);
        {
            HSD_CObj* cobj = HSD_CObjGetCurrent();
            GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtrDirect(cobj), 0);
            GXSetCurrentMtx(0);
            GXBegin(152, 0, 5);
            {
                float temp_f1;
                float temp_f1_2;
                float temp_f2;
                float temp_f2_2;
                float temp_f3;
                float temp_f4;
                float temp_f4_2;
                float temp_f5;
                PAD_STACK(16);

                temp_f4 = arg0->x * argf1 + arg1->x;
                temp_f2 = arg0->z;
                temp_f1 = arg1->y + arg0->y;
                temp_f3 = arg0->w;
                temp_f5 = temp_f4 + temp_f2;
                temp_f2_2 = temp_f4 - temp_f2;
                temp_f4_2 = temp_f3 + temp_f1;
                temp_f1_2 = temp_f1 - temp_f3;
                GXPosition3f32(temp_f5, temp_f4_2, 0.0f);
                {
                    // Not a #U8Vec4 (or other struct)? Bitfields?
                    u8 v_x, v_y, v_z, v_w;
                    v_w = arg2->w;
                    v_z = arg2->z;
                    v_y = arg2->y;
                    v_x = arg2->x;
                    GXPosition2u8(v_x, v_y);
                    GXPosition2u8(v_z, v_w);
                    GXPosition3f32(temp_f2_2, temp_f4_2, 0.0f);
                    GXPosition2u8(v_x, v_y);
                    GXPosition2u8(v_z, v_w);
                    GXPosition3f32(temp_f5, temp_f1_2, 0.0f);
                    GXPosition2u8(v_x, v_y);
                    GXPosition2u8(v_z, v_w);
                    GXPosition3f32(temp_f2_2, temp_f4_2, 0.0f);
                    GXPosition2u8(v_x, v_y);
                    GXPosition2u8(v_z, v_w);
                    GXPosition3f32(temp_f2_2, temp_f1_2, 0.0f);
                    GXPosition2u8(v_x, v_y);
                    GXPosition2u8(v_z, v_w);
                    GXEnd();
                    return true;
                }
            }
        }
    }

    return false;
}
