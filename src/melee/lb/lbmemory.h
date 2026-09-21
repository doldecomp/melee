#ifndef MELEE_LB_MEMORY_H
#define MELEE_LB_MEMORY_H

#include <Runtime/platform.h>

#include <melee/lb/forward.h>

/// A RAM or ARAM allocation: the address range [addr, addr + size).
struct HSD_AllocEntry {
    struct HSD_AllocEntry* next;
    uintptr_t addr;
    size_t size;
};

/// A heap over the address range [lo, hi), in main RAM or in ARAM.
typedef struct Handle {
    struct Handle* next;
    uintptr_t lo;
    uintptr_t hi;
    HSD_AllocEntry* blocks; ///< Allocated blocks in ascending address order.
} Handle;

/* 014E24 */ Handle* lbMemory_80014E24(uintptr_t lo, uintptr_t hi);
/* 014EEC */ void lbMemory_80014EEC(Handle*);
/* 014F7C */ u32 lbMemory_80014F7C(Handle*);
/* 014FC8 */ HSD_AllocEntry* lbMemory_80014FC8(Handle*, size_t);
/* 0150F0 */ void lbMemFreeToHeap(Handle*, uintptr_t);
/* 01529C */ u32 lbMemory_8001529C(Handle*, void (*)(u32), u32);
/* 0154BC */ void lbMemory_800154BC(uintptr_t*, uintptr_t*);
/* 0154D4 */ Handle* lbMemory_800154D4(uintptr_t lo, uintptr_t hi);
/* 0155A4 */ void lbMemory_800155A4(void);
/* 01564C */ void lbMemory_8001564C(void);

#endif
