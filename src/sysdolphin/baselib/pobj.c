#include "pobj.h"

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "displayfunc.h"
#include "id.h"
#include "jobj.h"
#include "memory.h"
#include "mtx.h"
#include "perf.h"
#include "state.h"
#include "tobj.h"
#include "util.h"

#include "forward.h"

#include <__mem.h>
#include <math.h> // IWYU pragma: keep
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>

/// @todo Several differently-signed comparisons appear in asserts, likely
///       indicating the sign of one of the variables is declared incorrectly
#pragma clang diagnostic ignored "-Wsign-compare"

static void PObjInfoInit(void);

HSD_PObjInfo hsdPObj = { PObjInfoInit };

static HSD_PObjInfo* default_class = NULL;

static f32 (*vertex_buffer)[3] = NULL;
static f32 (*normal_buffer)[3] = NULL;
static u32 vertex_buffer_size = 0;
static u32 normal_buffer_size = 0;

static HSD_VtxDescList* prev_vtxdesclist_array = NULL;
static HSD_VtxDescList* prev_vtxdesc = NULL;

static struct {
    void* obj;
    u32 mark;
} mtx_mark[2];

u32 HSD_PObjGetFlags(HSD_PObj* pobj)
{
    if (pobj != NULL) {
        return pobj->flags;
    }
    return 0;
}

void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, u32 flags)
{
    if (pobj == NULL) {
        return;
    }

    if (flags & POBJ_ANIM && pobj_type(pobj) == POBJ_SHAPEANIM) {
        HSD_ShapeSet* shape_set = pobj->u.shape_set;
        HSD_AObjRemove(shape_set->aobj);
        shape_set->aobj = NULL;
    }
}

void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags)
{
    HSD_PObj* pp;

    if (pobj == NULL) {
        return;
    }

    for (pp = pobj; pp != NULL; pp = pp->next) {
        HSD_PObjRemoveAnimByFlags(pp, flags);
    }
}

void HSD_PObjAddAnim(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim)
{
    HSD_ShapeSet* st;
    if (pobj == NULL) {
        return;
    }
    HSD_ASSERT(247, pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.shape_set);
    if (shapeanim == NULL) {
        return;
    }

    st = pobj->u.shape_set;
    if (st->aobj) {
        HSD_AObjRemove(st->aobj);
    }
    st->aobj = HSD_AObjLoadDesc(shapeanim->aobjdesc);
}

void HSD_PObjAddAnimAll(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim)
{
    HSD_PObj* po;
    HSD_ShapeAnim* sa;

    if (pobj == NULL || shapeanim == NULL) {
        return;
    }

    for (po = pobj, sa = shapeanim; po != NULL; po = po->next, sa = next_p(sa))
    {
        HSD_PObjAddAnim(po, sa);
    }
}

void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, f32 startframe, u32 flags)
{
    if (pobj == NULL) {
        return;
    }

    if (flags & POBJ_ANIM && pobj_type(pobj) == POBJ_SHAPEANIM) {
        HSD_AObjReqAnim(pobj->u.shape_set->aobj, startframe);
    }
}

void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, f32 startframe, u32 flags)
{
    HSD_PObj* pp;

    if (pobj == NULL) {
        return;
    }

    for (pp = pobj; pp; pp = pp->next) {
        HSD_PObjReqAnimByFlags(pp, startframe, flags);
    }
}

static void ShapeSetSetAnimResult(HSD_ShapeSet* shape_set, u32 type,
                                  HSD_ObjData* val)
{
    if (shape_set->flags & SHAPESET_ADDITIVE) {
        shape_set->blend.bp[type - HSD_A_S_W0] = val->fv;
    } else {
        shape_set->blend.bl = val->fv;
    }
}

static void PObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_PObj* pobj = HSD_POBJ(obj);
    if (pobj == NULL) {
        return;
    }

    if (pobj_type(pobj) == POBJ_SHAPEANIM) {
        ShapeSetSetAnimResult(pobj->u.shape_set, type, val);
    }
}

void HSD_PObjAnim(HSD_PObj* pobj)
{
    if (pobj != NULL && pobj_type(pobj) == POBJ_SHAPEANIM) {
        HSD_AObjInterpretAnim(pobj->u.shape_set->aobj, pobj, PObjUpdateFunc);
    }
}

void HSD_PObjAnimAll(HSD_PObj* pobj)
{
    HSD_PObj* pp;

    if (pobj != NULL) {
        for (pp = pobj; pp != NULL; pp = pp->next) {
            HSD_PObjAnim(pp);
        }
    }
}

static HSD_Envelope* HSD_EnvelopeAlloc(void)
{
    HSD_Envelope* envelope = hsdAllocMemPiece(sizeof(HSD_Envelope));
    HSD_ASSERT(441, envelope);
    memset(envelope, 0, sizeof(HSD_Envelope));
    return envelope;
}

static void HSD_EnvelopeFree(HSD_Envelope* env)
{
    if (env != NULL) {
        hsdFreeMemPiece(env, sizeof(HSD_Envelope));
    }
}

static void HSD_EnvelopeListFree(HSD_SList* list)
{
    while (list) {
        HSD_Envelope* env = list->data;
        while (env) {
            HSD_Envelope* next = env->next;
            HSD_JObjUnrefThis(env->jobj);
            HSD_EnvelopeFree(env);
            env = next;
        }
        list = HSD_SListRemove(list);
    }
}

static HSD_SList* loadEnvelopeDesc(HSD_EnvelopeDesc** edesc_p)
{
    HSD_SList* list = NULL;
    HSD_SList** list_p = &list;

    if (edesc_p == NULL) {
        return NULL;
    }

    while (*edesc_p) {
        HSD_Envelope* envelope = NULL;
        HSD_Envelope** env_p = &envelope;
        HSD_EnvelopeDesc* edesc = *edesc_p;

        while (edesc->joint) {
            *env_p = HSD_EnvelopeAlloc();
            (*env_p)->weight = edesc->weight;
            env_p = &((*env_p)->next);
            edesc++;
        }

        (*list_p) = HSD_SListAlloc();
        (*list_p)->data = envelope;
        list_p = &((*list_p)->next);
        edesc_p++;
    }
    return list;
}

static void HSD_ShapeSetFree(HSD_ShapeSet* shape_set)
{
    if (!shape_set) {
        return;
    }
    hsdFreeMemPiece(shape_set, sizeof(HSD_ShapeSet));
}

static void HSD_ShapeSetRemove(HSD_ShapeSet* shape_set)
{
    if (shape_set == NULL) {
        return;
    }

    if (shape_set->flags & SHAPESET_ADDITIVE) {
        HSD_Free(shape_set->blend.bp);
    }

    HSD_AObjRemove(shape_set->aobj);
    HSD_ShapeSetFree(shape_set);
}

static HSD_ShapeSet* loadShapeSetDesc(HSD_ShapeSetDesc* sdesc)
{
    int i;

    HSD_ShapeSet* shape_set = hsdAllocMemPiece(sizeof(HSD_ShapeSet));
    HSD_ASSERT(498, shape_set);
    memset(shape_set, 0, sizeof(HSD_ShapeSet));
    shape_set->flags = sdesc->flags;
    shape_set->nb_shape = sdesc->nb_shape;
    shape_set->nb_vertex_index = sdesc->nb_vertex_index;
    shape_set->vertex_desc = sdesc->vertex_desc;
    shape_set->vertex_idx_list = sdesc->vertex_idx_list;
    shape_set->nb_normal_index = sdesc->nb_normal_index;
    shape_set->normal_desc = sdesc->normal_desc;
    shape_set->normal_idx_list = sdesc->normal_idx_list;
    if (shape_set->flags & SHAPESET_ADDITIVE) {
        shape_set->blend.bp =
            (f32*) HSD_MemAlloc(shape_set->nb_shape * sizeof(f32));
        for (i = 0; i < shape_set->nb_shape; i++) {
            shape_set->blend.bp[i] = 0.0f;
        }
    } else {
        shape_set->blend.bl = 0.0f;
    }
    shape_set->aobj = NULL;
    return shape_set;
}

static s32 PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc)
{
    pobj->next = HSD_PObjLoadDesc(desc->next);
    pobj->verts = desc->verts;
    pobj->flags = desc->flags;
    pobj->n_display = desc->n_display;
    pobj->display = desc->display;
    switch (pobj_type(pobj)) {
    case POBJ_SHAPEANIM:
        pobj->u.shape_set = loadShapeSetDesc(desc->u.shape_set);
        break;

    case POBJ_ENVELOPE:
        pobj->u.envelope_list = loadEnvelopeDesc(desc->u.envelope_p);
        break;

    case POBJ_SKIN:
        break;

    default:
        HSD_Panic(__FILE__, 580, "pobj: unexected type.\n");
    }

    // _HSD_NeedCacheInvalidate(HSD_CACHE_VTX); // NOTE: This does not exist in
    // Melee's sysdolphin, but is a potential optimization

    return 0;
}

HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc* pobjdesc)
{
    if (pobjdesc != NULL) {
        HSD_PObj* pobj;
        HSD_ClassInfo* info;

        if (!pobjdesc->class_name ||
            !(info = hsdSearchClassInfo(pobjdesc->class_name)))
        {
            pobj = HSD_PObjAlloc();
        } else {
            pobj = hsdNew(info);
            HSD_ASSERT(605, pobj);
        }
        HSD_POBJ_METHOD(pobj)->load(pobj, pobjdesc);
        return pobj;
    } else {
        return NULL;
    }
}

void HSD_PObjRemove(HSD_PObj* pobj)
{
    hsdDelete(pobj);
}

void HSD_PObjRemoveAll(HSD_PObj* pobj)
{
    HSD_PObj* next;

    while (pobj != NULL) {
        next = pobj->next;
        HSD_PObjRemove(pobj);
        pobj = next;
    }
}

HSD_PObjInfo* HSD_PObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdPObj;
}

void HSD_PObjSetDefaultClass(HSD_PObjInfo* info)
{
    if (info != NULL) {
        HSD_ASSERT(673, hsdIsDescendantOf(info, &hsdPObj));
    }
    default_class = info;
}

HSD_PObj* HSD_PObjAlloc(void)
{
    HSD_PObj* pobj = hsdNew((HSD_ClassInfo*) (HSD_PObjGetDefaultClass()));
    HSD_ASSERT(703, pobj);
    return pobj;
}

void HSD_PObjFree(HSD_PObj* pobj)
{
    if (pobj) {
        HSD_CLASS_METHOD(pobj)->destroy((HSD_Class*) (pobj));
    }
}

static void resolveEnvelope(HSD_SList* list, HSD_EnvelopeDesc** edesc_p)
{
    if (list == NULL || edesc_p == NULL) {
        return;
    }

    for (; list && *edesc_p; list = list->next, edesc_p++) {
        HSD_Envelope* env = list->data;
        HSD_EnvelopeDesc* edesc = *edesc_p;

        while (env && edesc->joint) {
            HSD_JObjUnrefThis(env->jobj);
            env->jobj = HSD_IDGetData((u32) edesc->joint, NULL);
            HSD_ASSERT(736, env->jobj);
            HSD_JObjRefThis(env->jobj);
            env = env->next;
            edesc++;
        }
    }
}

void HSD_PObjResolveRefs(HSD_PObj* pobj, HSD_PObjDesc* pdesc)
{
    if (!pobj || !pdesc) {
        return;
    }

    switch (pobj_type(pobj)) {
    case POBJ_ENVELOPE:
        resolveEnvelope(pobj->u.envelope_list, pdesc->u.envelope_p);
        break;

    case POBJ_SKIN:
        HSD_JObjUnrefThis(pobj->u.jobj);
        pobj->u.jobj = NULL;
        if (pdesc->u.joint != NULL) {
            pobj->u.jobj = HSD_IDGetData((u32) pdesc->u.joint, NULL);
            HSD_ASSERT(0x2FB, pobj->u.jobj);
            HSD_JObjRefThis(pobj->u.jobj);
        }
        break;

    default:
        break;
    }
}

void HSD_PObjResolveRefsAll(HSD_PObj* pobj, HSD_PObjDesc* pdesc)
{
    for (; pobj != NULL && pdesc != NULL;
         pobj = pobj->next, pdesc = pdesc->next)
    {
        HSD_PObjResolveRefs(pobj, pdesc);
    }
}

void HSD_ClearVtxDesc(void)
{
    GXClearVtxDesc();
    prev_vtxdesclist_array = 0;
    prev_vtxdesc = 0;
}

static void setupArrayDesc(HSD_VtxDescList* desc_list)
{
    HSD_VtxDescList* desc;

    if (prev_vtxdesclist_array != desc_list) {
        for (desc = desc_list; desc->attr != GX_VA_NULL; desc++) {
            if (desc->attr_type != GX_DIRECT) {
                GXSetArray(desc->attr, desc->vertex, desc->stride);
            }
        }
        prev_vtxdesclist_array = desc_list;
    }
}

static void setupVtxDesc(HSD_PObj* pobj)
{
    HSD_VtxDescList* desc;

    if (prev_vtxdesc != pobj->verts) {
        GXClearVtxDesc();
        for (desc = pobj->verts; desc->attr != GX_VA_NULL; desc++) {
            GXSetVtxDesc(desc->attr, desc->attr_type);
            switch (desc->attr) {
            case GX_VA_PNMTXIDX:
            case GX_VA_TEX0MTXIDX:
            case GX_VA_TEX1MTXIDX:
            case GX_VA_TEX2MTXIDX:
            case GX_VA_TEX3MTXIDX:
            case GX_VA_TEX4MTXIDX:
            case GX_VA_TEX5MTXIDX:
            case GX_VA_TEX6MTXIDX:
            case GX_VA_TEX7MTXIDX:
                break;
            default:
                GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt,
                                desc->comp_type, desc->frac);
            }
        }
        prev_vtxdesc = pobj->verts;
    }
}

static void setupShapeAnimArrayDesc(HSD_VtxDescList* desc_list)
{
    HSD_VtxDescList* desc;

    for (desc = desc_list; desc->attr != GX_VA_NULL; desc++) {
        if (desc->attr_type != GX_DIRECT) {
            switch (desc->attr) {
            case GX_VA_POS:
            case GX_VA_NRM:
            case GX_VA_NBT:
                break;
            default:
                GXSetArray(desc->attr, desc->vertex, desc->stride);
            }
        }
    }
    prev_vtxdesclist_array = NULL;
}

static void setupShapeAnimVtxDesc(HSD_PObj* pobj)
{
    HSD_VtxDescList* desc;

    GXClearVtxDesc();
    for (desc = pobj->verts; desc->attr != GX_VA_NULL; desc++) {
        switch (desc->attr) {
        case GX_VA_NRM:
        case GX_VA_POS:
        case GX_VA_NBT:
            GXSetVtxDesc(desc->attr, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt, GX_F32, 0);
            break;

        case GX_VA_PNMTXIDX:
        case GX_VA_TEX0MTXIDX:
        case GX_VA_TEX1MTXIDX:
        case GX_VA_TEX2MTXIDX:
        case GX_VA_TEX3MTXIDX:
        case GX_VA_TEX4MTXIDX:
        case GX_VA_TEX5MTXIDX:
        case GX_VA_TEX6MTXIDX:
        case GX_VA_TEX7MTXIDX:
            GXSetVtxDesc(desc->attr, desc->attr_type);
            break;

        default:
            GXSetVtxDesc(desc->attr, desc->attr_type);
            GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt,
                            desc->comp_type, desc->frac);
        }
    }
    prev_vtxdesc = NULL;
}

static void get_shape_vertex_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, f32 dst[3])
{
    u8* index_array = shape_set->vertex_idx_list[shape_id];
    int idx;
    void* src_base;

    if (shape_set->vertex_desc->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    HSD_ASSERT(1102, shape_set->vertex_desc->comp_cnt == GX_POS_XYZ);
    src_base = ((u8*) shape_set->vertex_desc->vertex) +
               idx * shape_set->vertex_desc->stride;

    if (shape_set->vertex_desc->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(f32[3]));
    } else {
        int decimal_point = 1 << shape_set->vertex_desc->frac;
        switch (shape_set->vertex_desc->comp_type) {
        case GX_U8: {
            u8* src = src_base;
            dst[0] = (f32) src[0] / decimal_point;
            dst[1] = (f32) src[1] / decimal_point;
            dst[2] = (f32) src[2] / decimal_point;
        } break;

        case GX_S8: {
            s8* src = src_base;
            dst[0] = (f32) src[0] / decimal_point;
            dst[1] = (f32) src[1] / decimal_point;
            dst[2] = (f32) src[2] / decimal_point;
        } break;

        case GX_U16: {
            u16* src = src_base;
            dst[0] = (f32) src[0] / decimal_point;
            dst[1] = (f32) src[1] / decimal_point;
            dst[2] = (f32) src[2] / decimal_point;
        } break;

        case GX_S16: {
            s16* src = src_base;
            dst[0] = (f32) src[0] / decimal_point;
            dst[1] = (f32) src[1] / decimal_point;
            dst[2] = (f32) src[2] / decimal_point;
        } break;

        default:
            HSD_Panic(__FILE__, 1145, "unexpected vertex type.\n");
        }
    }
}

static void get_shape_normal_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, float dst[3])
{
    u8* index_array = shape_set->normal_idx_list[shape_id];
    int idx;
    void* src_base;

    if (shape_set->normal_desc->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    HSD_ASSERT(1165, shape_set->normal_desc->comp_cnt == GX_NRM_XYZ);
    src_base = ((u8*) shape_set->normal_desc->vertex) +
               idx * shape_set->normal_desc->stride;

    if (shape_set->normal_desc->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(f32[3]));
    } else {
        int decimal_point = 1 << shape_set->normal_desc->frac;
        switch (shape_set->normal_desc->comp_type) {
        case GX_U8: {
            u8* src = src_base;
            dst[0] = (float) src[0] / decimal_point;
            dst[1] = (float) src[1] / decimal_point;
            dst[2] = (float) src[2] / decimal_point;
        } break;
        case GX_S8: {
            s8* src = src_base;
            dst[0] = (float) src[0] / decimal_point;
            dst[1] = (float) src[1] / decimal_point;
            dst[2] = (float) src[2] / decimal_point;
        } break;
        case GX_U16: {
            u16* src = src_base;
            dst[0] = (float) src[0] / decimal_point;
            dst[1] = (float) src[1] / decimal_point;
            dst[2] = (float) src[2] / decimal_point;
        } break;
        case GX_S16: {
            s16* src = src_base;
            dst[0] = (float) src[0] / decimal_point;
            dst[1] = (float) src[1] / decimal_point;
            dst[2] = (float) src[2] / decimal_point;
        } break;
        default:
            HSD_Panic(__FILE__, 1208, "unexpected normal type.");
        }
    }
}

// https://decomp.me/scratch/aleJ2
static void get_shape_nbt_xyz(HSD_ShapeSet* shape_set, int shape_id,
                              int arrayidx, float* dst)
{
    u8* index_array = shape_set->normal_idx_list[shape_id];
    int i, idx;
    void* src_base;

    HSD_ASSERT(1221, shape_set->normal_desc->attr == GX_VA_NBT);

    if (shape_set->normal_desc->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    HSD_ASSERT(1230, shape_set->normal_desc->comp_cnt == GX_NRM_XYZ);

    src_base = ((u8*) shape_set->normal_desc->vertex) +
               idx * shape_set->normal_desc->stride;

    if (shape_set->normal_desc->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(f32[9]));
    } else {
        int decimal_point = 1 << shape_set->normal_desc->frac;
        switch (shape_set->normal_desc->comp_type) {
        case GX_U8:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((u8*) src_base)[i] / decimal_point;
            }
            break;
        case GX_S8:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((s8*) src_base)[i] / decimal_point;
            }
            break;
        case GX_U16:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((u16*) src_base)[i] / decimal_point;
            }
            break;
        case GX_S16:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((s16*) src_base)[i] / decimal_point;
            }
            break;
        default:
            HSD_Panic(__FILE__, 1261, "unexpected normal type.");
        }
    }
}

static void interpretShapeAnimDisplayList(HSD_PObj* pobj, float (*vertex)[3],
                                          float (*normal)[3])
{
    u8* dl = pobj->display;
    int length = pobj->n_display << 5;
    int l;

    for (l = 0; l + 3 < length;) {
        int n = dl[1] << 8 | dl[2];
        int m = 3;
        int i, j;

        if ((dl[0] & GX_OPCODE_MASK) == GX_NOP) {
            break;
        }
        GXBegin((GXPrimitive) (dl[0] & GX_OPCODE_MASK),
                (GXVtxFmt) (dl[0] & GX_VAT_MASK), n);
        for (i = 0; i < n; i++) {
            for (j = 0;; j++) {
                HSD_VtxDescList* desc = &pobj->verts[j];
                if (desc->attr == GX_VA_NULL) {
                    break;
                } else {
                    u16 idx = dl[m++];
                    switch (desc->attr) {
                    case GX_VA_PNMTXIDX:
                    case GX_VA_TEX0MTXIDX:
                    case GX_VA_TEX1MTXIDX:
                    case GX_VA_TEX2MTXIDX:
                    case GX_VA_TEX3MTXIDX:
                    case GX_VA_TEX4MTXIDX:
                    case GX_VA_TEX5MTXIDX:
                    case GX_VA_TEX6MTXIDX:
                    case GX_VA_TEX7MTXIDX:
                        GXMatrixIndex1u8(idx);
                        break;

                    case GX_VA_POS:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        GXPosition3f32(vertex[idx][0], vertex[idx][1],
                                       vertex[idx][2]);
                        break;

                    case GX_VA_NRM:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        GXNormal3f32(normal[idx][0], normal[idx][1],
                                     normal[idx][2]);
                        break;

                    case GX_VA_NBT:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        idx *= 3;
                        GXNormal3f32(normal[idx + 0][0], normal[idx + 0][1],
                                     normal[idx + 0][2]);
                        GXNormal3f32(normal[idx + 1][0], normal[idx + 1][1],
                                     normal[idx + 1][2]);
                        GXNormal3f32(normal[idx + 2][0], normal[idx + 2][1],
                                     normal[idx + 2][2]);
                        break;

                    case GX_VA_TEX0:
                    case GX_VA_TEX1:
                    case GX_VA_TEX2:
                    case GX_VA_TEX3:
                    case GX_VA_TEX4:
                    case GX_VA_TEX5:
                    case GX_VA_TEX6:
                    case GX_VA_TEX7:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                            GXTexCoord1x16(idx);
                        } else {
                            GXTexCoord1x8(idx);
                        }
                        break;

                    case GX_VA_CLR0:
                    case GX_VA_CLR1:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                            GXColor1x16(idx);
                        } else if (desc->attr_type == GX_INDEX8) {
                            GXColor1x8(idx);
                        } else {
                            switch (desc->comp_type) {
                            case GX_RGB565:
                            case GX_RGBA4:
                                GXColor1u16((idx << 8) | dl[m++]);
                                break;
                            case GX_RGB8:
                            case GX_RGBA6:
                                GXColor3u8(idx, dl[m], dl[m + 1]);
                                m += 2;
                                break;
                            case GX_RGBA8:
                            case GX_RGBX8:
                                GXColor4u8(idx, dl[m], dl[m + 1], dl[m + 2]);
                                m += 3;
                                break;
                            }
                        }
                        break;
                    default:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        OSReport("attr(%d) is not supported by sysdolphin\n",
                                 desc->attr);
                        break;
                    }
                }
            }
        }
        GXEnd();
        l += m;
        dl += m;
    }
}

#define pobj_min(x, y) (x < y ? x : y)

static void drawShapeAnim(HSD_PObj* pobj)
{
    HSD_ShapeSet* shape_set = pobj->u.shape_set;
    f32 blend;
    int shape_id, i;
    int blend_nbt;

    if (vertex_buffer_size == 0) {
        vertex_buffer_size = HSD_DEFAULT_MAX_SHAPE_VERTICES;
        vertex_buffer = HSD_MemAlloc(vertex_buffer_size * sizeof(f32[3]));
    }
    HSD_ASSERT(1407, vertex_buffer_size >= shape_set->nb_vertex_index);
    if (shape_set->normal_desc && normal_buffer_size == 0) {
        normal_buffer_size = HSD_DEFAULT_MAX_SHAPE_NORMALS;
        normal_buffer = HSD_MemAlloc(normal_buffer_size * sizeof(f32[3]));
    }

    if (shape_set->normal_desc) {
        if (shape_set->normal_desc->attr == GX_VA_NRM) {
            HSD_ASSERT(1416, normal_buffer_size >= shape_set->nb_normal_index);
            blend_nbt = 0;
        } else {
            HSD_ASSERT(1419, normal_buffer_size >= shape_set->nb_normal_index * 3);
            blend_nbt = 1;
        }
    }

    if (shape_set->flags & SHAPESET_AVERAGE) {
        blend = shape_set->blend.bl;
        shape_id = pobj_min(MAX(0, (int) blend), shape_set->nb_shape - 1);
        blend = pobj_min(MAX(0.0, blend - (f32) shape_id), 1.0f);
        for (i = 0; i < shape_set->nb_vertex_index; i++) {
            f32 s0[3], s1[3];

            get_shape_vertex_xyz(shape_set, shape_id, i, s0);
            get_shape_vertex_xyz(
                shape_set, pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                s1);
            vertex_buffer[i][0] = (s1[0] - s0[0]) * blend + s0[0];
            vertex_buffer[i][1] = (s1[1] - s0[1]) * blend + s0[1];
            vertex_buffer[i][2] = (s1[2] - s0[2]) * blend + s0[2];
        }
        if (shape_set->nb_normal_index) {
            if (blend_nbt) {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    f32 s0[9], s1[9];
                    int j, idx = i * 3;

                    get_shape_nbt_xyz(shape_set, shape_id, i, s0);
                    get_shape_nbt_xyz(
                        shape_set,
                        pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                        s1);
                    for (j = 0; j < 9; j++) {
                        normal_buffer[idx][j] =
                            (s1[j] - s0[j]) * blend + s0[j];
                    }
                }
            } else {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    f32 s0[3], s1[3];

                    get_shape_normal_xyz(shape_set, shape_id, i, s0);
                    get_shape_normal_xyz(
                        shape_set,
                        pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                        s1);
                    normal_buffer[i][0] = (s1[0] - s0[0]) * blend + s0[0];
                    normal_buffer[i][1] = (s1[1] - s0[1]) * blend + s0[1];
                    normal_buffer[i][2] = (s1[2] - s0[2]) * blend + s0[2];
                }
            }
        }
    } else {
        int j;
        f32* blend_bp;
        blend_bp = shape_set->blend.bp;
        for (i = 0; i < shape_set->nb_vertex_index; i++) {
            get_shape_vertex_xyz(shape_set, 0, i, vertex_buffer[i]);
            for (j = 0; j < shape_set->nb_shape; j++) {
                f32 b = MAX(0.0, blend_bp[j]);
                f32 s[3];

                get_shape_vertex_xyz(shape_set, j + 1, i, s);
                vertex_buffer[i][0] += s[0] * b;
                vertex_buffer[i][1] += s[1] * b;
                vertex_buffer[i][2] += s[2] * b;
            }
        }
        if (shape_set->nb_normal_index) {
            if (blend_nbt) {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    s32 idx = i * 3;
                    get_shape_nbt_xyz(shape_set, 0, i, normal_buffer[idx]);
                    for (j = 0; j < shape_set->nb_shape; j++) {
                        f32 b = MAX(0.0, blend_bp[j]);
                        f32 s[9];
                        int k;

                        get_shape_nbt_xyz(shape_set, j + 1, i, s);
                        for (k = 0; k < 9; k++) {
                            normal_buffer[idx][k] += s[k] * b;
                        }
                    }
                }
            } else {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    get_shape_normal_xyz(shape_set, 0, i, normal_buffer[i]);
                    for (j = 0; j < shape_set->nb_shape; j++) {
                        f32 b = MAX(0.0, blend_bp[j]);
                        f32 s[3];

                        get_shape_normal_xyz(shape_set, j + 1, i, s);
                        normal_buffer[i][0] += s[0] * b;
                        normal_buffer[i][1] += s[1] * b;
                        normal_buffer[i][2] += s[2] * b;
                    }
                }
            }
        }
    }
    interpretShapeAnimDisplayList(pobj, vertex_buffer, normal_buffer);
}

void HSD_PObjClearMtxMark(void* obj, u32 mark)
{
    int i;

    for (i = 0; i < 2; i++) {
        mtx_mark[i].obj = obj;
        mtx_mark[i].mark = mark;
    }
}

void HSD_PObjSetMtxMark(int idx, void* obj, u32 mark)
{
    if (idx >= 2) {
        return;
    }

    if (0 <= idx && idx < 2) {
    } else {
        mtx_mark[idx].obj = obj;
        mtx_mark[idx].mark = mark;
    }
}

void HSD_PObjGetMtxMark(int idx, void** obj, u32* mark)
{
    HSD_ASSERT(1655, obj);
    HSD_ASSERT(1656, mark);

    if (idx < 0 || 2 <= idx) {
        *obj = NULL;
        *mark = 0;
    } else {
        *obj = mtx_mark[idx].obj;
        *mark = mtx_mark[idx].mark;
    }
}

static PObjSetupFlag GetSetupFlags(HSD_JObj* jobj, u32 rendermode)
{
    PObjSetupFlag flags = SETUP_NONE;
    if (!(rendermode & 0x4000000)) {
        if (jobj->flags & JOBJ_LIGHTING) {
            flags |= SETUP_NORMAL;
        }

        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_REFLECTION)) {
            flags |= SETUP_NORMAL | SETUP_REFLECTION;
        }

        if (_HSD_TObjGetCurrentByType(NULL, TEX_COORD_HILIGHT)) {
            flags |= SETUP_NORMAL | SETUP_HIGHLIGHT;
        }
    }

    return flags;
}

static void SetupRigidModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                               u32 rendermode)
{
    HSD_JObj* jobj;
    Mtx n;
    PObjSetupFlag flags;

    jobj = HSD_JObjGetCurrent();

    {
        void* obj;
        u32 mark;

        HSD_PObjGetMtxMark(0, &obj, &mark);
        if (obj == jobj && mark == HSD_MTX_RIGID) {
            return;
        }
        HSD_PObjSetMtxMark(0, jobj, HSD_MTX_RIGID);
    }

    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadPosMtxImm(pmtx, GX_PNMTX0);
    HSD_PerfCountMtxLoad();

    flags = GetSetupFlags(jobj, rendermode);

    if (flags & SETUP_NORMAL) {
        HSD_MtxInverseTranspose(pmtx, n);
        if (jobj->flags & JOBJ_LIGHTING) {
            GXLoadNrmMtxImm(n, GX_PNMTX0);
            HSD_PerfCountMtxLoad();
        }
        if (flags & SETUP_NORMAL_PROJECTION) {
            GXLoadTexMtxImm(n, GX_TEXMTX0, GX_MTX3x4);
            HSD_PerfCountMtxLoad();
        }
    }
}

static void SetupSharedVtxModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                   u32 rendermode)
{
    HSD_JObj* jobj;
    Mtx n0, n1, m;
    PObjSetupFlag flags = SETUP_NONE;

    jobj = HSD_JObjGetCurrent();
    {
        void* obj;
        u32 mark;

        HSD_PObjGetMtxMark(0, &obj, &mark);
        if (obj != jobj && mark != HSD_MTX_RIGID) {
            flags |= SETUP_JOINT0;
        }

        HSD_PObjGetMtxMark(1, &obj, &mark);
        if (obj != pobj->u.jobj && mark != HSD_MTX_RIGID) {
            flags |= SETUP_JOINT1;
        }
    }

    if (flags == SETUP_NONE) {
        return;
    }

    flags |= GetSetupFlags(jobj, rendermode);

    if (flags | SETUP_JOINT0) {
        GXSetCurrentMtx(GX_PNMTX0);
        GXLoadPosMtxImm(pmtx, GX_PNMTX0);
        HSD_PerfCountMtxLoad();

        if (flags & SETUP_NORMAL) {
            HSD_MtxInverseTranspose(pmtx, n0);
            if (jobj->flags & 0x80) {
                GXLoadNrmMtxImm(n0, GX_PNMTX0);
                HSD_PerfCountMtxLoad();
            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(n0, GX_TEXMTX0, GX_MTX3x4);
                HSD_PerfCountMtxLoad();
            }
        }
    }
    if (flags | SETUP_JOINT1) {
        ///@todo Unused stack
        u8 _[4];
        HSD_JObjSetupMatrix(pobj->u.jobj);
        PSMTXConcat(vmtx, pobj->u.jobj->mtx, m);
        GXLoadPosMtxImm(m, GX_PNMTX1);
        HSD_PerfCountMtxLoad();

        if (flags & SETUP_NORMAL) {
            HSD_MtxInverseTranspose(m, n1);
            if (jobj->flags & 0x80) {
                GXLoadNrmMtxImm(n1, GX_PNMTX1);
                HSD_PerfCountMtxLoad();
            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(n1, GX_TEXMTX1, GX_MTX3x4);
                HSD_PerfCountMtxLoad();
            }
        }
    }
}

static void SetupEnvelopeModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                  u32 rendermode)
{
    HSD_JObj* jobj;
    HSD_SList* list;
    int MtxIdx = 0;
    MtxPtr right;
    Mtx mtx;
    PObjSetupFlag flags = SETUP_NONE;

    jobj = HSD_JObjGetCurrent();
    HSD_PObjClearMtxMark(NULL, HSD_MTX_ENVELOPE);
    flags = GetSetupFlags(jobj, rendermode);
    right = _HSD_mkEnvelopeModelNodeMtx(jobj, mtx);

    for (MtxIdx = 0, list = pobj->u.envelope_list; MtxIdx < 10 && list;
         MtxIdx++, list = list->next)
    {
        Mtx mtx, tmp;
        MtxPtr mtxp;
        HSD_Envelope* envelope = list->data;
        s32 mtx_no = HSD_Index2PosNrmMtx(MtxIdx);
        int perf = 0;

        HSD_ASSERT(1872, envelope);
        if (envelope->weight >= (1.0f - FLT_EPSILON)) {
            HSD_JObjSetupMatrix(envelope->jobj);
            if (right) {
                MTXConcat(envelope->jobj->mtx, envelope->jobj->envelopemtx,
                          mtx);
                mtxp = mtx;
            } else {
                mtxp = envelope->jobj->mtx;
            }
        } else {
            mtx[0][0] = mtx[0][1] = mtx[0][2] = mtx[0][3] = mtx[1][0] =
                mtx[1][1] = mtx[1][2] = mtx[1][3] = mtx[2][0] = mtx[2][1] =
                    mtx[2][2] = mtx[2][3] = 0.0f;
            while (envelope) {
                HSD_JObj* jp;

                HSD_ASSERT(1892, envelope->jobj);
                jp = envelope->jobj;
                HSD_JObjSetupMatrix(jp);
                HSD_ASSERT(1895, jp->mtx);
                HSD_ASSERT(1896, jp->envelopemtx);

                MTXConcat(jp->mtx, jp->envelopemtx, tmp);
                HSD_MtxScaledAdd(tmp, mtx, mtx, envelope->weight);
                perf++;
                envelope = envelope->next;
            }
            mtxp = mtx;
        }
        HSD_PerfCountEnvelopeBlending(perf);
        if (right) {
            MTXConcat(mtxp, right, mtx);
        }
        MTXConcat(vmtx, mtxp, tmp);
        GXLoadPosMtxImm(tmp, mtx_no);
        HSD_PerfCountMtxLoad();

        if (flags & SETUP_NORMAL) {
            HSD_MtxInverseTranspose(tmp, mtx);
            if (jobj->flags & JOBJ_LIGHTING) {
                GXLoadNrmMtxImm(mtx, mtx_no);
                HSD_PerfCountMtxLoad();
            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(mtx, HSD_Index2TexMtx(MtxIdx), GX_MTX3x4);
                HSD_PerfCountMtxLoad();
            }
        }
    }
}

static void PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    switch (pobj_type(pobj)) {
    case POBJ_SKIN:
        if (!pobj->u.jobj) {
            SetupRigidModelMtx(pobj, vmtx, pmtx, rendermode);
        } else {
            SetupSharedVtxModelMtx(pobj, vmtx, pmtx, rendermode);
        }
        break;
    case POBJ_SHAPEANIM:
        SetupRigidModelMtx(pobj, vmtx, pmtx, rendermode);
        break;
    case POBJ_ENVELOPE:
        SetupEnvelopeModelMtx(pobj, vmtx, pmtx, rendermode);
        break;
    }
}

static void PObjDispSimplePrimitive(HSD_PObj* pobj, u32 rendermode)
{
    setupArrayDesc(pobj->verts);
    setupVtxDesc(pobj);

    GXCallDisplayList(pobj->display, pobj->n_display << 5);
}

static void PObjDispShapeAnim(HSD_PObj* pobj, u32 rendermode)
{
    setupShapeAnimArrayDesc(pobj->verts);
    setupShapeAnimVtxDesc(pobj);

    HSD_ASSERT(0x7B1, pobj->u.shape_set);
    drawShapeAnim(pobj);
}

void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    switch (pobj->flags & (POBJ_CULLFRONT | POBJ_CULLBACK)) {
    case 0x0:
        HSD_StateSetCullMode(GX_CULL_NONE);
        break;
    case POBJ_CULLFRONT:
        HSD_StateSetCullMode(GX_CULL_FRONT);
        break;
    case POBJ_CULLBACK:
        HSD_StateSetCullMode(GX_CULL_BACK);
        break;
    case POBJ_CULLFRONT | POBJ_CULLBACK:
        return;
    }

    HSD_POBJ_METHOD(pobj)->setup_mtx(pobj, vmtx, pmtx, rendermode);
    if (pobj_type(pobj) == POBJ_SHAPEANIM) {
        PObjDispShapeAnim(pobj, rendermode);
    } else {
        PObjDispSimplePrimitive(pobj, rendermode);
    }
}

static void PObjRelease(HSD_Class* o)
{
    HSD_PObj* pobj = HSD_POBJ(o);

    switch (pobj_type(pobj)) {
    case POBJ_SHAPEANIM:
        HSD_ShapeSetRemove(pobj->u.shape_set);
        break;
    case POBJ_ENVELOPE:
        HSD_EnvelopeListFree(pobj->u.envelope_list);
        break;
    case POBJ_SKIN:
        HSD_JObjUnrefThis(pobj->u.jobj);
        break;
    default:
        break;
    }
    HSD_PARENT_INFO(&hsdPObj)->release(o);
}

static void PObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdPObj)) {
        vertex_buffer = NULL;
        vertex_buffer_size = 0;
        normal_buffer = NULL;
        normal_buffer_size = 0;
        prev_vtxdesclist_array = NULL;
        prev_vtxdesc = NULL;
    }
    HSD_PARENT_INFO(&hsdPObj)->amnesia(info);
}

static void PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdPObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_pobj",
                     sizeof(HSD_PObjInfo), sizeof(HSD_PObj));
    HSD_CLASS_INFO(&hsdPObj)->release = PObjRelease;
    HSD_CLASS_INFO(&hsdPObj)->amnesia = PObjAmnesia;
    HSD_POBJ_INFO(&hsdPObj)->disp = HSD_PObjDisp;
    HSD_POBJ_INFO(&hsdPObj)->setup_mtx = PObjSetupMtx;
    HSD_POBJ_INFO(&hsdPObj)->load = PObjLoad;
}
