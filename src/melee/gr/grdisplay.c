#include "inlines.h"

#include "cm/camera.h"
#include "ft/ftlib.h"
#include "gr/ground.h"

#include "lb/forward.h"

#include "lb/lbshadow.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/state.h>

/* 1C5B90 */ static void grDisplay_801C5B90(HSD_JObj* jobj, Mtx vmtx, u32 arg2,
                                            u32 rendermode);
/* 1C5F60 */ static void grDisplay_801C5F60(HSD_GObj* gobj, int code);
/* 1C6620 */ static void grAnime_801C6620(HSD_PObj* arg0, HSD_ShapeAnim* arg1);

void grDisplay_801C5B90(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    HSD_GObj* cur;
    HSD_CObj* cobj;
    Mtx mtx;
    Vec3 vec;
    u32 unused[6];

    if (jobj != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            if (!(jobj->flags & JOBJ_HIDDEN)) {
                HSD_JObjSetupMatrix(jobj);
                HSD_JObjSetupMatrix(jobj->child);

                HSD_MtxInverseConcat(jobj->child->mtx, jobj->mtx, mtx);
                cobj = HSD_CObjGetCurrent();
                HSD_ASSERT(82, cobj);
                PSMTXConcat(HSD_CObjGetViewingMtxPtrDirect(cobj), mtx, mtx);
                grDisplay_801C5B90(jobj->child, mtx, flags, rendermode);
            }
        } else {
            if (jobj->flags & (flags << 18)) {
                for (cur = HSD_GObj_Entities->fighters; cur != NULL;
                     cur = cur->next)
                {
                    LbShadow* shadow = ftLib_800872B0(cur);
                    ftLib_80086644(cur, &vec);
                    if (Camera_80030B24() || stage_info.x17C(&vec, -1, jobj)) {
                        shadow->x0_b4 = 0;
                    } else {
                        shadow->x0_b4 = 1;
                    }
                }
                lbShadow_8000EFEC();
                HSD_JObjDisp(jobj, vmtx, flags, rendermode);
            }
            if (jobj->flags & (flags << 28)) {
                for (jobj = jobj->child; jobj != NULL; jobj = jobj->next) {
                    grDisplay_801C5B90(jobj, vmtx, flags, rendermode);
                }
            }
        }
    }
}

void grDisplay_801C5DB0(HSD_GObj* gobj, int code)
{
    Ground* gp;
    HSD_GObj* camgobj;
    HSD_CObj* cobj;
    HSD_JObj* jobj;
    int i;

    gp = GET_GROUND(gobj);
    if (gp->x11_flags.b012 == Camera_8003108C()) {
        if (gp->x18 != NULL) {
            if ((code & ~0x7FFFFFFF) == 0) {
                OSReport("oioi... %08x\n");
            }
            if (HSD_GObj_804D7818->hsd_obj != gp->x18->hsd_obj) {
                if (gp->x10_flags.b3 == 0) {
                    return;
                }
                camgobj = Camera_80030A50();
                if (camgobj == NULL) {
                    return;
                }
                cobj = GET_COBJ(camgobj);
                if (cobj == NULL) {
                    return;
                }

                if (cobj != HSD_CObjGetCurrent()) {
                    return;
                }

                if (Ground_801C2C8C(HSD_GObj_804D7818->hsd_obj) != false) {
                    return;
                }

                if (Camera_80030A78() != false) {
                    return;
                }

                if (Camera_80030AC4() == false) {
                    return;
                }

                if (gp->x10_flags.b2 == 0) {
                    HSD_FogSet(0);
                }
                HSD_StateInvalidate(-1);

                if (gp->x10_flags.b4 != 0) {
                    jobj = GET_JOBJ(gobj);
                    grDisplay_801C5B90(jobj, NULL, HSD_GObj_80390EB8(code), 0);
                } else {
                    HSD_GObj* fighter;
                    for (fighter = HSD_GObj_Entities->fighters;
                         fighter != NULL; fighter = fighter->next)
                    {
                        LbShadow* shadow = ftLib_800872B0(fighter);
                        HSD_GObj_JObjCallback(gobj, code);
                    }
                }
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
