#include "sysdolphin/baselib/memory.h"

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
        __assert("memory.c", 52, "adr");
    }
    return result;
}
