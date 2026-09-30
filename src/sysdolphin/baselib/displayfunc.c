/**
 * @file displayfunc.c
 * @brief Scene graph and JObj rendering dispatch functions
 * @details Manages the rendering pipeline, Z-sorting (translucent objects), and GX state setup for drawing.
 */
#include "displayfunc.h"

#include <string.h>

#include "cobj.h"
#include "dobj.h"
#include "lobj.h"
#include "mobj.h"
#include "mtx.h"
#include "objalloc.h"
#include "pobj.h"
#include "state.h"
#include "tev.h"
#include "util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#define FLT_EPSILON 1.00000001335e-10F

typedef struct _HSD_ZList {
    Mtx pmtx;
    MtxPtr vmtx;
    HSD_JObj* jobj;
    u32 rendermode;

    struct _HSD_ZList_sort {
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

/**
 * @brief Initializes the allocator data for Z-List entries.
 */
void HSD_ZListInitAllocData(void)
{
    HSD_ObjAllocInit(&zlist_alloc_data, sizeof(HSD_ZList), 4);
}

/**
 * @brief Allocates a new Z-List entry.
 */
static HSD_ZList* HSD_ZListAlloc(void)
{
    HSD_ZList* list;

    list = HSD_ObjAlloc(&zlist_alloc_data);
    memset(&list->vmtx, 0, sizeof(HSD_ZList) - sizeof(Mtx));

    return list;
}

/**
 * @brief Frees a Z-List entry.
 */
static void HSD_ZListFree(HSD_ZList* ptr)
{
    HSD_ObjFree(&zlist_alloc_data, ptr);
}

/**
 * @brief Initializes the GX hardware state for direct rendering.
 */
void HSD_StateInitDirect(int vtxfmt, u32 rendermode)
{
    HSD_ClearVtxDesc();
    GXSetVtxAttrFmt(vtxfmt, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(vtxfmt, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    HSD_StateInitTev();
    HSD_SetupRenderMode(rendermode | 0x28000000);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetCurrentMtx(GX_PNMTX0);
}

Vec3 zOne = { 0, 0, 1 };
Vec3 yOne = { 0, 1, 0 };
Vec3 zOne2 = { 0, 0, 1 };

/**
 * @brief Calculates a vertical billboard matrix.
 */
static void mkVBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 pos, ax, ay, az;
    float sx, sz;

    HSD_MtxColVec(src, 3, &pos);
    HSD_MtxColVec(src, 1, &ay);

    sx = HSD_MtxColMag(src, 0);
    sz = HSD_MtxColMag(src, 2);

    if (jobj->flags & JOBJ_PBILLBOARD) {
        VECCrossProduct(&pos, &ay, &ax);
    } else {
        VECCrossProduct(&ay, &zOne, &ax);
    }
    VECCrossProduct(&ax, &ay, &az);
    sx /= VECMag(&ax);
    sz /= VECMag(&az);

    dst[0][0] = sx * ax.x;
    dst[1][0] = sx * ax.y;
    dst[2][0] = sx * ax.z;

    HSD_MtxSetColVec(dst, 1, &ay);

    dst[0][2] = sz * az.x;
    dst[1][2] = sz * az.y;
    dst[2][2] = sz * az.z;

    HSD_MtxSetColVec(dst, 3, &pos);
}

/**
 * @brief Calculates a horizontal billboard matrix.
 */
static void mkHBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 pos, ax, ay, az;
    Vec3 uy;
    float sy, sz;

    HSD_MtxColVec(src, 3, &pos);
    HSD_MtxColVec(src, 0, &ax);

    sy = HSD_MtxColMag(src, 1);
    sz = HSD_MtxColMag(src, 2);

    if (jobj->flags & JOBJ_PBILLBOARD) {
        uy.y = sqrtf(pos.x * pos.x + pos.z * pos.z);
        uy.x = -pos.y / uy.y * pos.x;
        uy.z = -pos.y / uy.y * pos.z;
        VECCrossProduct(&ax, &uy, &az);
    } else {
        VECCrossProduct(&ax, &yOne, &az);
    }
    VECCrossProduct(&az, &ax, &ay);
    sy /= VECMag(&ay);
    sz /= VECMag(&az);

    HSD_MtxSetColVec(dst, 0, &ax);

    dst[0][1] = sy * ay.x;
    dst[1][1] = sy * ay.y;
    dst[2][1] = sy * ay.z;

    dst[0][2] = sz * az.x;
    dst[1][2] = sz * az.y;
    dst[2][2] = sz * az.z;

    HSD_MtxSetColVec(dst, 3, &pos);
}

/**
 * @brief Calculates a standard billboard matrix.
 */
static void mkBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Vec3 ax, ay, *az, pos;
    float sx, sy, sz;

    sx = HSD_MtxColMag(src, 0);
    sz = HSD_MtxColMag(src, 2);

    HSD_MtxColVec(src, 1, &ay);
    sy = VECMag(&ay);
    HSD_MtxColVec(src, 3, &pos);

    if (jobj->flags & JOBJ_PBILLBOARD) {
        VECCrossProduct(&pos, &ay, &ax);
        VECCrossProduct(&ax, &pos, &ay);
        az = &pos;
        sz /= -VECMag(az);
    } else {
        VECCrossProduct(&ay, &zOne2, &ax);
        VECCrossProduct(&zOne2, &ax, &ay);
        az = &zOne2;
        sz /= VECMag(&zOne2);
    }
    sx /= VECMag(&ax);
    sy /= VECMag(&ay);

    dst[0][0] = sx * ax.x;
    dst[1][0] = sx * ax.y;
    dst[2][0] = sx * ax.z;

    dst[0][1] = sy * ay.x;
    dst[1][1] = sy * ay.y;
    dst[2][1] = sy * ay.z;

    dst[0][2] = sz * az->x;
    dst[1][2] = sz * az->y;
    dst[2][2] = sz * az->z;

    HSD_MtxSetColVec(dst, 3, &pos);
}

/**
 * @brief Calculates a rotation billboard matrix.
 */
static void mkRBillBoardMtx(HSD_JObj* jobj, MtxPtr src, MtxPtr dst)
{
    Mtx rot, scl;
    f32 sx, sy, sz;
    sx = HSD_MtxColMag(src, 0);
    sy = HSD_MtxColMag(src, 1);
    sz = HSD_MtxColMag(src, 2);
    MTXScale(scl, sx, sy, sz);
    MTXRotRad(rot, 'z', jobj->rotate.z);
    rot[0][3] = src[0][3];
    rot[1][3] = src[1][3];
    rot[2][3] = src[2][3];
    MTXConcat(rot, scl, dst);
}

/**
 * @brief Calculates and assigns the final position matrix for a JObj, applying billboard logic if necessary.
 */
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

/**
 * @brief Walks up the JObj hierarchy to find the root skeleton node.
 */
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

/**
 * @brief Computes the node matrix for an envelope skinning JObj relative to its skeleton root.
 */
MtxPtr _HSD_mkEnvelopeModelNodeMtx(HSD_JObj* m, MtxPtr mtx)
{
    if (m->flags & JOBJ_SKELETON_ROOT) {
        return NULL;
    } else {
        HSD_JObj* root_skeleton = HSD_JObjFindSkeleton(m);
        HSD_ASSERT(422, root_skeleton);

        if (root_skeleton == m) {
            MTXInverse(root_skeleton->envelopemtx, mtx);
        } else if (root_skeleton->flags & JOBJ_SKELETON_ROOT) {
            HSD_MtxInverseConcat(root_skeleton->mtx, m->mtx, mtx);
        } else {
            Mtx n;
            MTXConcat(root_skeleton->mtx, root_skeleton->envelopemtx, n);
            HSD_MtxInverseConcat(n, m->mtx, mtx);
        }

        return mtx;
    }
}

/**
 * @brief Directly renders the DObjs associated with a JObj.
 */
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

/**
 * @brief Displays the DObjs attached to a JObj, routing them to the direct pass or Z-List based on transparency.
 */
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

/**
 * @brief Recursively merge sorts a Z-List by depth (Z-value).
 */
static HSD_ZList* zlist_sort(HSD_ZList* list, s32 total_count, s32 offset)
{
    HSD_ZList *left_list, *right_list, **ptr;
    int count_left, count_right;
    int i;

    if (total_count <= 1) {
        if (list != NULL) {
            ZLIST_NEXT(list, offset) = NULL;
        }
        return list;
    }

    count_left = total_count / 2;
    count_right = total_count - count_left;

    right_list = list;
    for (i = 0; i < count_left; i++) {
        right_list = ZLIST_NEXT(right_list, offset);
    }

    left_list = zlist_sort(list, count_left, offset);
    right_list = zlist_sort(right_list, count_right, offset);

    list = NULL;
    ptr = &list;

    while (left_list != NULL && right_list != NULL) {
        if (left_list->pmtx[2][3] <= right_list->pmtx[2][3]) {
            *ptr = left_list;
            left_list = ZLIST_NEXT(left_list, offset);
        } else {
            *ptr = right_list;
            right_list = ZLIST_NEXT(right_list, offset);
        }
        ptr = &ZLIST_NEXT(*ptr, offset);
    }

    if (left_list != NULL) {
        *ptr = left_list;
    } else if (right_list != NULL) {
        *ptr = right_list;
    }

    return list;
}

/**
 * @brief Sorts the queued Z-List objects by depth.
 */
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

/**
 * @brief Dispatches rendering for all objects currently in the sorted Z-List.
 */
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

/**
 * @brief Clears the Z-List and frees associated allocations.
 */
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

/**
 * @brief Main dispatch function to render a JObj (DObjs or particle nodes) with the specified transparency pass.
 */
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

/**
 * @brief Sets the global callback used for rendering particle JObjs.
 */
void HSD_JObjSetSPtclCallback(void (*func)(s32, s32, s32, HSD_JObj*))
{
    sptcl_callback = func;
}

/**
 * @brief Sets the erase color used by HSD_EraseRect.
 */
void HSD_SetEraseColor(u8 r, u8 g, u8 b, u8 a)
{
    erase_color.r = r;
    erase_color.g = g;
    erase_color.b = b;
    erase_color.a = a;
}

/**
 * @brief Draws a full-screen quad to manually clear the frame/depth buffer.
 */
void HSD_EraseRect(f32 top, f32 bottom, f32 left, f32 right, f32 z,
                   int enable_color, int enable_alpha, int enable_depth)
{
    GXTexObj texobj;
    static u8 depth_image[] ATTRIBUTE_ALIGN(32) = {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    };
    GXColor color;
    u8 _[4];

    if (!enable_color && !enable_alpha && !enable_depth) {
        return;
    }

    if (enable_depth) {
        GXInitTexObj(&texobj, depth_image, 4, 4, GX_TF_Z8, GX_REPEAT,
                     GX_REPEAT, GX_DISABLE);
        GXLoadTexObj(&texobj, GX_TEXMAP0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY,
                          GX_NONE, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z8, 0);
    } else {
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    }

    GXSetCullMode(GX_CULL_NONE);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_ENABLE, GX_ALWAYS, enable_depth ? GX_ENABLE : GX_DISABLE);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GXSetColorUpdate(enable_color ? GX_ENABLE : GX_DISABLE);
    GXSetAlphaUpdate(enable_alpha ? GX_ENABLE : GX_DISABLE);

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX,
                  GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    color = erase_color;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(left, top, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2u8(0, 0);
    GXPosition3f32(right, top, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2u8(1, 0);
    GXPosition3f32(right, bottom, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2u8(1, 1);
    GXPosition3f32(left, bottom, z);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2u8(0, 1);
    GXEnd();

    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);

    HSD_StateInvalidate(HSD_STATE_ALL);
}

/**
 * @brief Clears the internal Z-List memory and pointers.
 */
void _HSD_DispForgetMemory(void* lo, void* hi)
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
