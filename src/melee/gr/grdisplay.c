#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/ground.h"
#include "lb/lbshadow.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>

/* 1C5B90 */ static void grDisplay_801C5B90(HSD_JObj* jobj, void* arg1,
                                            u32 arg2, int arg3);
/* 1C5F60 */ static void grDisplay_801C5F60(HSD_GObj* gobj, int code);
/* 1C6620 */ static void grAnime_801C6620(HSD_PObj* arg0, HSD_ShapeAnim* arg1);

void grDisplay_801C5B90(HSD_JObj* jobj, void* arg1, u32 arg2, int arg3)
{
    Mtx sp3C;
    Vec3 sp30;
    HSD_CObj* cobj;
    HSD_JObj* cur;
    u32 unused[6];

    if (jobj == NULL) {
        return;
    }

    if (jobj->flags & 0x1000) {
        if (!(jobj->flags & 0x10)) {
            HSD_JObjSetupMatrix(jobj);
            {
                HSD_JObj* jtmp = jobj->child;
                HSD_JObjSetupMatrix(jtmp);
            }

            HSD_MtxInverseConcat(jobj->child->mtx, jobj->mtx, sp3C);
            cobj = HSD_CObjGetCurrent();
            HSD_ASSERT(82, cobj);
            {
                MtxPtr tmp = cobj->view_mtx;
                PSMTXConcat(tmp, sp3C, sp3C);
            }
            grDisplay_801C5B90(jobj->child, sp3C, arg2, arg3);
        }
    } else {
        if (jobj->flags & (arg2 << 18)) {
            HSD_GObj* cur;
            for (cur = HSD_GObj_Entities->fighters; cur != NULL;
                 cur = cur->next)
            {
                struct {
                    u8 b0 : 1;
                    u8 b1 : 1;
                    u8 b2 : 1;
                    u8 b3 : 1;
                    u8 b4 : 1;
                    u8 b5 : 1;
                    u8 b6 : 1;
                    u8 b7 : 1;
                }* temp_r26 = ftLib_800872B0(cur);
                ftLib_80086644(cur, &sp30);
                if (Camera_80030B24() || stage_info.x17C(&sp30, -1, jobj)) {
                    temp_r26->b4 = 0;
                } else {
                    temp_r26->b4 = 1;
                }
            }
            lbShadow_8000EFEC();
            HSD_JObjDisp(jobj, arg1, arg2, arg3);
        }
        if (jobj->flags & (arg2 << 28)) {
            for (jobj = jobj->child; jobj != NULL; jobj = jobj->next) {
                grDisplay_801C5B90(jobj, arg1, arg2, arg3);
            }
        }
    }
}

void grDisplay_801C5F60(HSD_GObj* gobj, int code)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        gobj->gxlink_prios = 8;
        Camera_800310A0(0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}
