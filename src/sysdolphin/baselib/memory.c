#include "sysdolphin/baselib/memory.h"

extern char lbl_80407300[];

void HSD_Free(void* ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

void* HSD_MemAlloc(s32 size) {
    void* result;

    if (size <= 0)
        return NULL;
    
    result = OSAllocFromHeap(HSD_GetHeap(), size);
    if (result == NULL){
        __assert(lbl_80407300, 52, "adr");
    }
    return result;
}
