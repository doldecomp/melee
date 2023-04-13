#include <platform.h>

#include <dolphin/os/OSAlloc.h>
#include <baselib/debug.h>
#include <baselib/initialize.h>
#include <baselib/memory.h>

void HSD_Free(any_t ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

any_t HSD_MemAlloc(ssize_t size)
{
    any_t adr;

    if (size <= 0) {
        return NULL;
    }

    adr = OSAllocFromHeap(HSD_GetHeap(), size);
    HSD_ASSERT(52, adr);

    return adr;
}
