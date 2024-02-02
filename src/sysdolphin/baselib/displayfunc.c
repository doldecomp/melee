#include "displayfunc.h"

#include "objalloc.h"
#include "pobj.h"
#include "state.h"
#include "tev.h"

#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXTransform.h>

#define FLT_EPSILON 1.00000001335e-10F

typedef struct _HSD_ZList {
    Mtx pmtx;
    MtxPtr vmtx;
    HSD_JObj* jobj;
    u32 rendermode;

    struct {
        struct _HSD_ZList* texedge;
        struct _HSD_ZList* xlu;
    } sort;

    struct _HSD_ZList* next;
} HSD_ZList;

HSD_ObjAllocData zlist_alloc_data;

void HSD_ZListInitAllocData(void)
{
    HSD_ObjAllocInit(&zlist_alloc_data, sizeof(HSD_ZList), 4);
}

void HSD_StateInitDirect(int vtxfmt, u32 param_2)
{
    HSD_ClearVtxDesc();
    GXSetVtxAttrFmt(vtxfmt, 9, 1, 4, 0);
    GXSetVtxAttrFmt(vtxfmt, 0xB, 1, 5, 0);
    HSD_StateInitTev();
    HSD_SetupRenderMode(param_2 | 0x28000000);
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetCurrentMtx(0);
}

void HSD_JObjMakePositionMtx(HSD_JObj* jobj, Mtx vmtx, Mtx pmtx)
{
    Mtx mtx;

    if (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        MTXConcat(vmtx, jobj->mtx, mtx);
        switch (jobj->flags & JOBJ_BILLBOARD_FIELD) {
        case JOBJ_BILLBOARD:
            mkBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_VBILLBOARD:
            mkVBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_HBILLBOARD:
            mkHBillBoardMtx(jobj, mtx, pmtx);
            break;
        case JOBJ_RBILLBOARD:
            mkRBillBoardMtx(jobj, mtx, pmtx);
            break;
        default:
            HSD_Panic(__FILE__, 322, "unkown type of billboard.\n");
        }
    } else {
        MTXConcat(vmtx, jobj->mtx, pmtx);
    }
}

HSD_JObj* HSD_JObjFindSkeleton(HSD_JObj* jobj)
{
    HSD_ASSERT(342, jobj);
    for (; jobj; jobj = jobj->parent) {
        if (jobj->flags & (JOBJ_SKELETON | JOBJ_SKELETON_ROOT)) {
            return jobj;
        }
    }
    return NULL;
}

MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx)
{
    if (m->flags & JOBJ_SKELETON_ROOT) { /* r == x == m */
        return NULL;
    } else {
        HSD_JObj* x = HSD_JObjFindSkeleton(m);
        HSD_ASSERT(422, x);

        if (x == m) { /* r != x == m */
            MTXInverse(x->envelopemtx, mtx);
        } else if (x->flags & JOBJ_SKELETON_ROOT) { /* r == x != m */
            HSD_MtxInverseConcat(x->mtx, m->mtx, mtx);
        } else { /* r != x != m */
            Mtx n;
            MTXConcat(x->mtx, x->envelopemtx, n);
            HSD_MtxInverseConcat(n, m->mtx, mtx);
        }

        return mtx;
    }
}
