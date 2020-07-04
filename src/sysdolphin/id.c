#include "id.h"

extern HSD_ObjAllocData lbl_804C23C0; // alloc_data

extern struct _HSD_IDTable lbl_804C23EC; // default_table 

#pragma push
#pragma force_active on // Unused function until it's loaded into a GetAllocData function table, so force_active required to match for now
HSD_ObjAllocData* HSD_IDGetAllocData(void)
{
    return &lbl_804C23C0;
}
#pragma pop

void HSD_IDInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C23C0, sizeof(IDEntry), 4);
}

void HSD_IDSetup(void)
{
    memset(&lbl_804C23EC, 0, 0x194); // The partial memset doesn't quite make sense, but it matches
}