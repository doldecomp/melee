#ifndef MELEE_LB_MEMORY_H
#define MELEE_LB_MEMORY_H

#include <Runtime/platform.h>

#include <melee/lb/forward.h>

struct HSD_AllocEntry {
    struct HSD_AllocEntry* next;
    void* addr; ///< ARAM addresses are opaque.
    size_t size;
};

/// Heap spanning [lo, hi).
typedef struct Handle {
    struct Handle* next;
    void* lo;
    void* hi;
    HSD_AllocEntry* blocks; ///< Sorted by address.
} Handle;

/* 014E24 */ Handle* lbMemory_80014E24(void* lo, void* hi);
/* 014EEC */ void lbMemory_80014EEC(Handle*);
/* 014F7C */ u32 lbMemory_80014F7C(Handle*);
/* 014FC8 */ HSD_AllocEntry* lbMemory_80014FC8(Handle*, size_t);
/* 0150F0 */ void lbMemFreeToHeap(Handle*, void*);
/* 01529C */ u32 lbMemory_8001529C(Handle*, void (*)(u32), u32);
/* 0154BC */ void lbMemory_800154BC(uintptr_t*, uintptr_t*);
/* 0154D4 */ Handle* lbMemory_800154D4(void* lo, void* hi);
/* 0155A4 */ void lbMemory_800155A4(void);
/* 01564C */ void lbMemory_8001564C(void);

#endif
