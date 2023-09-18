#include <sysdolphin/baselib/axdriver.h>
#include <sysdolphin/baselib/debug.h>

extern u8* AXDriver_804D77D4;
extern u32 axfxallocsize;
extern u32 axfxmaxsize;
extern char AXDriver_80408140[]; // axdriver.c
extern char AXDriver_8040814C[]; // "axfxallocsize < axfxmaxsize"

u8* AXDriverAlloc(s32 size)
{
    u8* ptr = &AXDriver_804D77D4[axfxallocsize];

    // increment the size by the amount we will be indexing to.
    axfxallocsize += size;

    // size exceeds the max allowed; the pointer that we return would be
    // outside the heap. Raise an assert.
    if (axfxallocsize >= axfxmaxsize) {
        __assert(AXDriver_80408140, 78, AXDriver_8040814C);
    }
    return ptr;
}

void AXDriverFree(void* ptr) {}
