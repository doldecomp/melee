#include "sysdolphin/baselib/robj.h"

extern HSD_ObjAllocData lbl_804C2368; // robj_alloc_data
extern HSD_ObjAllocData lbl_804C2394; // rvalue_alloc_data

extern const f64 lbl_804DE6A0; // 1.75

void HSD_RObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C2368, sizeof(HSD_RObj), 4);
    HSD_ObjAllocInit(&lbl_804C2394, sizeof(HSD_Rvalue), 4);
}

HSD_ObjAllocData* HSD_RObjGetAllocData(void)
{
    return &lbl_804C2368;
}

HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void)
{
    return &lbl_804C2394;
}

void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags)
{
    if (robj != NULL) {
        robj->flags |= flags;
    }
}

HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype)
{
    BOOL has_type;
    HSD_RObj* curr;

    if (robj == NULL)
        return NULL;

    for (curr = robj; curr != NULL; curr = curr->next) {
        if (curr->flags & 0x80000000)
        {
            has_type = TRUE;
        } else {
            has_type = FALSE;
        }

        if (has_type) {
            if ((curr->flags & TYPE_MASK) == type && (!subtype || subtype == (curr->flags & 0xFFFFFFF))) {
                return curr;
            }
        }
    }

    return NULL;
}

static void RObjUpdateFunc(void* obj, s32 type, FObjData val)
{
    HSD_RObj* robj;

    if (obj == NULL)
        return;

    if (type != TYPE_ROBJ)
        return;

    robj = (HSD_RObj*)obj;
    if (val.fv >= lbl_804DE6A0) {
        robj->flags = robj->flags | 0x80000000;
        return;
    }
    robj->flags = robj->flags & 0x7fffffff;
}

inline void HSD_RObjAnim(HSD_RObj* robj)
{
    if (robj == NULL)
        return;
    
    HSD_AObjInterpretAnim(robj->aobj, robj, RObjUpdateFunc);
}

void HSD_RObjAnimAll(HSD_RObj* robj)
{
    HSD_RObj* curr;

    if (robj == NULL)
        return;

    for (curr = robj; curr != NULL; curr = curr->next) {
        HSD_RObjAnim(curr);
    }
}
