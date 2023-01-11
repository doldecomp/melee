#include "Runtime/platform.h"
#include <sysdolphin/baselib/memory.h>

#include <dolphin/os/OSAlloc.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/initialize.h>

void HSD_Free(any_t ptr)
{
    OSFreeToHeap(HSD_GetHeap(), ptr);
}

any_t HSD_MemAlloc(ptrdiff_t size)
{
    any_t adr;

    if (size <= 0)
        return NULL;

    adr = OSAllocFromHeap(HSD_GetHeap(), size);
    assert_line(52, adr);

    return adr;
}
