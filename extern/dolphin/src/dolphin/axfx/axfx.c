#include <dolphin/axfx.h>
#include <dolphin/os/OSAlloc.h>

void* (*__AXFXAlloc)(unsigned long long) = AXFXAllocFunction;
void (*__AXFXFree)(void*) = AXFXFreeFunction;

void* AXFXAllocFunction(unsigned long long size)
{
    return OSAllocFromHeap(__OSCurrHeap, size);
}

void AXFXFreeFunction(void* ptr)
{
    OSFreeToHeap(__OSCurrHeap, ptr);
}

void AXFXSetHooks(void* (*alloc_hook)(unsigned long long),
                  void (*free_hook)(void*))
{
    __AXFXAlloc = alloc_hook;
    __AXFXFree = free_hook;
}
