#ifndef __DOLPHIN_OSALLOC_H_
#define __DOLPHIN_OSALLOC_H_

#include <dolphin/types.h>

typedef struct _HeapCell
{
    struct _HeapCell *prev;
    struct _HeapCell *next;
    u32 size;
} HeapCell;

typedef struct _Heap
{
    s32 size;
    struct _HeapCell *free;  // linked list of free cells
    struct _HeapCell *allocated;  // linked list of allocated cells
} Heap;

typedef int OSHeapHandle;

//extern volatile OSHeapHandle __OSCurrHeap;

void *OSInitAlloc(void *, void *, int);
OSHeapHandle OSCreateHeap(void *, void *);
OSHeapHandle OSSetCurrentHeap(OSHeapHandle);
void *OSAllocFromHeap(OSHeapHandle, u32);
long OSCheckHeap(OSHeapHandle);
void OSFreeToHeap(OSHeapHandle heap, void *ptr);

#define OSAlloc(size) OSAllocFromHeap(__OSCurrHeap, (size))
#define OSFree(ptr)   OSFreeToHeap(__OSCurrHeap, (ptr))

#endif
