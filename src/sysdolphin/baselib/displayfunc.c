#include "displayfunc.h"

#include "baselib/cobj.h"
#include "baselib/dobj.h"
#include "baselib/lobj.h"
#include "baselib/mobj.h"
#include "baselib/mtx.h"
#include "baselib/objalloc.h"
#include "baselib/pobj.h"
#include "baselib/state.h"
#include "baselib/tev.h"

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

static void (*sptcl_callback)(s32, s32, s32, HSD_JObj*) = NULL;

static GXColor erase_color = { 0, 0, 0, 0 };

static int zsort_listing = 0;
static int zsort_sorting = 0;

static HSD_ZList* zlist_top = NULL;
static HSD_ZList** zlist_bottom = &zlist_top;

static HSD_ZList* zlist_texedge_top = NULL;
static HSD_ZList** zlist_texedge_bottom = &zlist_texedge_top;
static int zlist_texedge_nb = 0;

static HSD_ZList* zlist_xlu_top = NULL;
static HSD_ZList** zlist_xlu_bottom = &zlist_xlu_top;
static int zlist_xlu_nb = 0;

#define ZLIST_NEXT(list, offset) (*(HSD_ZList**) (((u8*) (list)) + (offset)))

void HSD_ZListInitAllocData(void)
{
    HSD_ObjAllocInit(&zlist_alloc_data, sizeof(HSD_ZList), 4);
}

static HSD_ZList* HSD_ZListAlloc(void)
{
    HSD_ZList* list;

    list = HSD_ObjAlloc(&zlist_alloc_data);
    memset(&list->vmtx, 0, sizeof(HSD_ZList) - sizeof(Mtx));

    return list;
}

static void HSD_ZListFree(HSD_ZList* ptr)
{
    HSD_ObjFree(&zlist_alloc_data, ptr);
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

void HSD_JObjDispSub(HSD_JObj* jobj, MtxPtr vmtx, MtxPtr pmtx,
                     HSD_TrspMask trsp_mask, u32 rendermode)
{
    HSD_DObj* dobj;
    u32 dobj_trsp;

    HSD_JObjSetCurrent(jobj);

    dobj_trsp = trsp_mask << DOBJ_TRSP_SHIFT;

    if (!(rendermode & RENDER_SHADOW)) {
        if (jobj->flags & JOBJ_SPECULAR) {
            HSD_LObjSetupSpecularInit(pmtx);
        }
    }

    HSD_PObjClearMtxMark(NULL, 0);
    for (dobj = jobj->u.dobj; dobj; dobj = dobj->next) {
        if (dobj->flags & DOBJ_HIDDEN) {
            continue;
        }

        if (dobj->flags & dobj_trsp) {
            HSD_DObjSetCurrent(dobj);
            HSD_DOBJ_METHOD(dobj)->disp(dobj, vmtx, pmtx, rendermode);
        }
    }
    HSD_DObjSetCurrent(NULL);
    HSD_JObjSetCurrent(NULL);
}

void HSD_JObjDispDObj(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask,
                      u32 rendermode)
{
    HSD_CObj* cobj;
    Mtx mtx;

    if ((jobj->flags & JOBJ_HIDDEN) == 0) {
        u32 xlu_bits = jobj->flags & (trsp_mask << JOBJ_TRSP_SHIFT);
        if (xlu_bits != 0) {
            HSD_JObjSetupMatrix(jobj);

            if (vmtx == NULL) {
                cobj = HSD_CObjGetCurrent();
                vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);
            }

            HSD_JOBJ_METHOD(jobj)->make_pmtx(jobj, vmtx, mtx);
            if ((xlu_bits & JOBJ_OPA) != 0) {
                HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx, HSD_TRSP_OPA,
                                            rendermode);
            }
            if (zsort_listing == 0) {
                if ((xlu_bits & JOBJ_TEXEDGE) != 0) {
                    HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx,
                                                HSD_TRSP_TEXEDGE, rendermode);
                }
                if ((xlu_bits & JOBJ_XLU) != 0) {
                    HSD_JOBJ_METHOD(jobj)->disp(jobj, vmtx, mtx, HSD_TRSP_XLU,
                                                rendermode);
                }
            } else {
                if ((xlu_bits & (JOBJ_TEXEDGE | JOBJ_XLU)) != 0) {
                    HSD_ZList* zlist;

                    zlist = HSD_ZListAlloc();
                    MTXCopy(mtx, zlist->pmtx);
                    if (vmtx != NULL) {
                        zlist->vmtx = (MtxPtr) HSD_MtxAlloc();
                        MTXCopy(vmtx, zlist->vmtx);
                    }
                    zlist->jobj = jobj;
                    zlist->rendermode = rendermode;
                    *zlist_bottom = zlist;
                    zlist_bottom = &zlist->next;
                    if ((xlu_bits & JOBJ_TEXEDGE) != 0) {
                        *zlist_texedge_bottom = zlist;
                        zlist_texedge_bottom = &zlist->sort.texedge;
                        zlist_texedge_nb += 1;
                    }
                    if ((xlu_bits & JOBJ_XLU) != 0) {
                        *zlist_xlu_bottom = zlist;
                        zlist_xlu_bottom = &zlist->sort.xlu;
                        zlist_xlu_nb += 1;
                    }
                }
            }
        }
    }
}

static HSD_ZList* zlist_sort(HSD_ZList* list, s32 nb, s32 offset)
{
    HSD_ZList *fore, *hind, **ptr;
    int nb_fore, nb_hind;
    int i;

    if (nb <= 1) {
        if (list != NULL) {
            ZLIST_NEXT(list, offset) = NULL;
        }
        return list;
    }

    nb_fore = nb / 2;
    nb_hind = nb - nb_fore;

    hind = list;
    for (i = 0; i < nb_fore; i++) {
        hind = ZLIST_NEXT(hind, offset);
    }

    fore = zlist_sort(list, nb_fore, offset);
    hind = zlist_sort(hind, nb_hind, offset);

    list = NULL;
    ptr = &list;

    while (fore != NULL && hind != NULL) {
        if (fore->pmtx[2][3] <= hind->pmtx[2][3]) {
            *ptr = fore;
            fore = ZLIST_NEXT(fore, offset);
        } else {
            *ptr = hind;
            hind = ZLIST_NEXT(hind, offset);
        }
        ptr = &ZLIST_NEXT(*ptr, offset);
    }

    if (fore != NULL) {
        *ptr = fore;
    } else if (hind != NULL) {
        *ptr = hind;
    }

    return list;
}

void _HSD_ZListSort(void)
{
    if (zsort_sorting) {
        zlist_texedge_top =
            zlist_sort(zlist_texedge_top, zlist_texedge_nb,
                       0x3C); /// @todo Create and use an offsetof macro to get
                              /// ZList sort.texedge and sort.xlu
        zlist_xlu_top = zlist_sort(zlist_xlu_top, zlist_xlu_nb, 0x40);
    }
}

void _HSD_ZListDisp(void)
{
    HSD_ZList* list;
    MtxPtr vmtx;
    HSD_CObj* cobj;

    cobj = HSD_CObjGetCurrent();
    vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);

    list = zlist_texedge_top;
    while (list != NULL) {
        HSD_JOBJ_METHOD(list->jobj)
            ->disp(list->jobj, (list->vmtx) ? list->vmtx : vmtx, list->pmtx,
                   HSD_TRSP_TEXEDGE, list->rendermode);
        list = list->sort.texedge;
    }

    list = zlist_xlu_top;
    while (list != NULL) {
        HSD_JOBJ_METHOD(list->jobj)
            ->disp(list->jobj, (list->vmtx) ? list->vmtx : vmtx, list->pmtx,
                   HSD_TRSP_XLU, list->rendermode);
        list = list->sort.xlu;
    }

    _HSD_ZListClear();
}

void _HSD_ZListClear(void)
{
    HSD_ZList* list = zlist_top;

    while (list != NULL) {
        HSD_ZList* next = list->next;
        if (list->vmtx) {
            HSD_MtxFree(list->vmtx);
        }
        HSD_ZListFree(list);
        list = next;
    }
    zlist_top = NULL;
    zlist_bottom = &zlist_top;

    zlist_texedge_top = NULL;
    zlist_texedge_bottom = &zlist_texedge_top;
    zlist_texedge_nb = 0;

    zlist_xlu_top = NULL;
    zlist_xlu_bottom = &zlist_xlu_top;
    zlist_xlu_nb = 0;
}

void HSD_JObjDisp(HSD_JObj* jobj, MtxPtr vmtx, HSD_TrspMask trsp_mask,
                  u32 rendermode)
{
    if (jobj != NULL) {
        if (union_type_dobj(jobj)) {
            HSD_JObjDispDObj(jobj, vmtx, trsp_mask, rendermode);
        } else if (union_type_ptcl(jobj) && sptcl_callback != NULL) {
            HSD_SList* sp;
            for (sp = jobj->u.ptcl; sp != NULL; sp = sp->next) {
                if ((((u32) sp->data) & 0x80000000) != 0) {
                    u32 bank = JOBJ_PTCL_BANK_MASK & ((u32) sp->data);
                    u32 offset = (((u32) sp->data) >> JOBJ_PTCL_OFFSET_SHIFT) &
                                 JOBJ_PTCL_OFFSET_MASK;
                    (*sptcl_callback)(0, bank, offset, jobj);
                }
                sp->data = (void*) ((u32) sp->data & JOBJ_PTCL_ACTIVE);
            }
        }
    }
}

void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*))
{
    sptcl_callback = func;
}

void HSD_SetEraseColor(u8 r, u8 g, u8 b, u8 a)
{
    erase_color.r = r;
    erase_color.g = g;
    erase_color.b = b;
    erase_color.a = a;
}

void _HSD_DispForgetMemory(void)
{
    zlist_top = NULL;
    zlist_bottom = &zlist_top;

    zlist_texedge_top = NULL;
    zlist_texedge_bottom = &zlist_texedge_top;
    zlist_texedge_nb = 0;

    zlist_xlu_top = NULL;
    zlist_xlu_bottom = &zlist_xlu_top;
    zlist_xlu_nb = 0;
}
