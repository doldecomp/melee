#include "objalloc.h"

extern objheap lbl_80406E48;

void HSD_ObjSetHeap(u32 size, void* ptr)
{
    objheap* heap = &lbl_80406E48;
    heap->curr = (u32)ptr;
    heap->top = (u32)ptr;
    heap->remain = size;
    heap->size = size;
}
