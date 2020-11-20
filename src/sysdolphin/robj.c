#include "robj.h"

extern HSD_ObjAllocData lbl_804C2368; // robj_alloc_data
extern HSD_ObjAllocData lbl_804C2394; // rvalue_alloc_data

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
