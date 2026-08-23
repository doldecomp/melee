#ifndef __GALE01_0158D0
#define __GALE01_0158D0

#include "lbheap.h" // IWYU pragma: export
#include "lbmemory.h"

struct Heap {
    /* 10 */ s32 id;
    /* 14 */ Handle* handle;
    /// The heap's base *address*. `s32` would sign-extend when it is cast
    /// back to a pointer; the same four bytes on GameCube.
    /* 18 */ uintptr_t start;
    /* 1C */ u32 size;
    /* 20 */ s32 type;
    /* 24 */ s32 transient;
    /* 28 */ LbHeapStatus status;
};
ASSERT_SIZE(struct Heap, 0x1C);

struct lbHeap_HeapState {
    /* 0x00 */ void* arena_lo;    /* inferred */
    /* 0x04 */ void* arena_hi;    /* inferred */
    /* 0x08 */ uintptr_t aram_lo; /* inferred */
    /* 0x0C */ uintptr_t aram_hi; /* inferred */
    /* 0x10 */ struct Heap heap_array[6];
}; /* size = 0xB8 */
ASSERT_SIZE(struct lbHeap_HeapState, 0xB8);

/* 431FA0 */ static struct lbHeap_HeapState lbHeap_80431FA0;

#endif
