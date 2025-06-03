#include <dolphin/axfx/axfx.h>
#include <dolphin/os/OSAlloc.h>

void* AXFXAllocFunction(size_t);
void AXFXFreeFunction(void*);

void* (*__AXFXAlloc)(size_t) = AXFXAllocFunction;
void (*__AXFXFree)(void*) = AXFXFreeFunction;

void* AXFXAllocFunction(size_t size)
{
    return OSAllocFromHeap(__OSCurrHeap, size);
}

void AXFXFreeFunction(void* ptr)
{
    OSFreeToHeap(__OSCurrHeap, ptr);
}

void AXFXSetHooks(void* (*alloc_hook)(size_t), void (*free_hook)(void*))
{
    __AXFXAlloc = alloc_hook;
    __AXFXFree = free_hook;
}
