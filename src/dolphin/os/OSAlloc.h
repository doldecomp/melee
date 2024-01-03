#ifndef __DOLPHIN_OSALLOC_H_
#define __DOLPHIN_OSALLOC_H_

#include <platform.h>

typedef struct _HeapCell {
    struct _HeapCell* prev;
    struct _HeapCell* next;
    size_t size;
} HeapCell;

typedef struct _Heap {
    s32 size;
    struct _HeapCell* free;      // linked list of free cells
    struct _HeapCell* allocated; // linked list of allocated cells
} Heap;

typedef int OSHeapHandle;

extern volatile OSHeapHandle __OSCurrHeap;

void* OSInitAlloc(void*, void*, int);
OSHeapHandle OSCreateHeap(void*, void*);
void OSDestroyHeap(size_t idx);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle);
void* OSAllocFromHeap(OSHeapHandle heap, size_t size);
size_t OSCheckHeap(OSHeapHandle);
void OSFreeToHeap(OSHeapHandle heap, void* ptr);

#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr) OSFreeToHeap(__OSCurrHeap, (ptr))

#endif
