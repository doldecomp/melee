#ifndef __GALE01_0158D0
#define __GALE01_0158D0

#include "lbheap.h" // IWYU pragma: export
#include "lbmemory.h"

#include <placeholder.h>

struct Heap {
    /* 10 */ s32 id;
    /* 14 */ Handle* handle;
    /* 18 */ s32 start;
    /* 1C */ u32 size;
    /* 20 */ s32 type;
    /* 24 */ s32 transient;
    /* 28 */ int status;
};
STATIC_ASSERT(sizeof(struct Heap) == 0x1C);

struct lbHeap_HeapState {
    /* 0x00 */ void* arena_lo;        /* inferred */
    /* 0x04 */ void* arena_hi;        /* inferred */
    /* 0x08 */ unsigned int aram_lo; /* inferred */
    /* 0x0C */ unsigned int aram_hi; /* inferred */
    /* 0x10 */ struct Heap heap_array[6];
}; /* size = 0xB8 */
STATIC_ASSERT(sizeof(struct lbHeap_HeapState) == 0xB8);

/* 431FA0 */ static struct lbHeap_HeapState lbHeap_80431FA0;

#endif
