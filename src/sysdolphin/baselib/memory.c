#include <sysdolphin/baselib/memory.h>

#include <dolphin/os/OSAlloc.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/initialize.h>

void HSD_Free(any_t ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

any_t HSD_MemAlloc(ssize_t size)
{
    any_t adr;

    if (size <= 0)
        return NULL;

    adr = OSAllocFromHeap(HSD_GetHeap(), size);
    HSD_ASSERT(52, adr);

    return adr;
}
