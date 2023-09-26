#include <baselib/pobj.h>

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
        struct unk_struct_pobj* unk_struct = pobj->u.x14_unk;
        HSD_AObjRemove(unk_struct->aobj);
        unk_struct->aobj = NULL;
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
    struct unk_struct_pobj* st;
    if (pobj == NULL) {
        return;
    }
    HSD_ASSERT(247, pobj_type(pobj) == POBJ_SHAPEANIM && pobj->u.shape_set);
    if (shapeanim == NULL) {
        return;
    }

    st = pobj->u.x14_unk;
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
        HSD_AObjReqAnim(pobj->u.x14_unk->aobj, startframe);
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
        *(f32*) (&shape_set->blend.bp) = val->fv;
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
        HSD_AObjInterpretAnim(pobj->u.x14_unk->aobj, pobj, PObjUpdateFunc);
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
    HSD_ASSERT(0x1B9, envelope);
    memset(envelope, 0, sizeof(HSD_Envelope));
    return envelope;
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
