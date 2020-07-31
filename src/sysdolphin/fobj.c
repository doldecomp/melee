#include "fobj.h"

extern HSD_ObjAllocData lbl_804C08D8;

#pragma push
#pragma force_active on // Unused function until it's loaded into a GetAllocData function table, so force_active required to match for now
HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &lbl_804C08D8;
}
#pragma pop

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C08D8, sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (fobj == NULL)
        return;

    HSD_FObjFree(fobj);
}
