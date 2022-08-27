#include <sysdolphin/baselib/pobj.h>

u32 HSD_PObjGetFlags(HSD_PObj* pobj)
{
    if (pobj != NULL) {
        return pobj->flags;
    }
    return 0;
}

void HSD_PObjRemoveAnimByFlags(HSD_PObj *pobj, u32 flags)
{
    if (pobj == NULL)
        return;
    
    if (flags & POBJ_ANIM && pobj_type(pobj) == POBJ_SHAPEANIM){
        struct _unk_struct_pobj* unk_struct = pobj->u.x14_unk;
        HSD_AObjRemove(unk_struct->aobj);
        unk_struct->aobj = NULL;
    }
}

void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, u32 flags) 
{
    HSD_PObj* pp;

    if (pobj == NULL)
        return;
    
    for (pp = pobj; pp != NULL; pp = pp->next) {
        HSD_PObjRemoveAnimByFlags(pp, flags);
    }
}
