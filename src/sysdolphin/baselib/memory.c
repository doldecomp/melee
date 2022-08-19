#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/debug.h>

void HSD_Free(void* ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

void* HSD_MemAlloc(s32 size)
{
    void* adr;

    if (size <= 0)
        return NULL;

    adr = OSAllocFromHeap(HSD_GetHeap(), size);
    assert_line(52, adr);

    return adr;
}
