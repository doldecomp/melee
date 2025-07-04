#ifndef GALE01_014E24
#define GALE01_014E24

#include <platform.h>

#include <baselib/forward.h>

typedef struct _Handle {
    struct _Handle* x0_next;
    void* x4_lo;
    // is this hi or size?
    void* x8_hi;
    struct _Handle* xC_prev;
} Handle;

/* 014E24 */ Handle* lbMemory_80014E24(void* lo, void* hi);
/* 014EEC */ void lbMemory_80014EEC(Handle*);
/* 014F7C */ u32 lbMemory_80014F7C(Handle*);
/* 014FC8 */ Handle* lbMemory_80014FC8(Handle*, u32);
/* 0150F0 */ void lbMemory_800150F0(Handle*, void*);
/* 01529C */ u32 lbMemory_8001529C(Handle*, void*, u32);
/* 0154BC */ void lbMemory_800154BC(uintptr_t*, uintptr_t*);
/* 0154D4 */ Handle* lbMemory_800154D4(void* lo, void* hi);
/* 0155A4 */ void lbMemory_800155A4(void);
/* 01564C */ void lbMemory_8001564C(void);

#endif
