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

void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, float startframe, u32 flags)
{
    if (pobj == NULL) {
        return;
    }

    if (flags & POBJ_ANIM && pobj_type(pobj) == POBJ_SHAPEANIM) {
        HSD_AObjReqAnim(pobj->u.x14_unk->aobj, startframe);
    }
}

void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, float startframe, u32 flags)
{
    HSD_PObj* pp;

    if (pobj == NULL) {
        return;
    }

    for (pp = pobj; pp; pp = pp->next) {
        HSD_PObjReqAnimByFlags(pp, startframe, flags);
    }
}
