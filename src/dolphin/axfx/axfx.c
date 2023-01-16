#include <dolphin/os/OSAlloc.h>

any_t AXFXAllocFunction(size_t);
void AXFXFreeFunction(any_t);

any_t (*__AXFXAlloc)(size_t) = AXFXAllocFunction;
void (*__AXFXFree)(any_t) = AXFXFreeFunction;

any_t AXFXAllocFunction(size_t size)
{
    return OSAllocFromHeap(__OSCurrHeap, size);
}

void AXFXFreeFunction(any_t ptr)
{
    OSFreeToHeap(__OSCurrHeap, ptr);
}

void AXFXSetHooks(any_t (*alloc_hook)(size_t), void (*free_hook)(any_t))
{
    __AXFXAlloc = alloc_hook;
    __AXFXFree = free_hook;
}
