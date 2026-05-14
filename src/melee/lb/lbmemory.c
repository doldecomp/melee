#include "lbmemory.h"

#include <platform.h>

#include <baselib/debug.h>
#include <baselib/devcom.h>
#include <dolphin/ar.h>

struct Allocator {
    void* x0_arenaLo;
    void* x4_arenaHi;
    u8 x8[0x62C - 0x8];
    Handle* x62C_free_mem;
    s32 x630_num_allocs;
    s32 x634_max_num_allocs;
    u8 x638[0x698 - 0x638];
    Handle* x698_free_heap;
    Handle* x69C;
    u8 x6A0[0x6E0 - 0x6A0];
    u32 x6E0;
    void* x6E4;
    void* x6E8;
    u8 x6EC[0x6F0 - 0x6EC];
};
static s8 lbl_803BA2C0[0xB] = "lbmemory.c";
static struct Allocator g_alloc;
STATIC_ASSERT(sizeof(g_alloc) == 0x6F0);

struct LBMgr {
    OSAlarm alarm;                  // 0x00
    u8* src;                        // 0x28
    u8* dst;                        // 0x2C
    u32 size;                       // 0x30
    u32 offset;                     // 0x34
    u32 cb_arg;                     // 0x38
    void (*cb)(u32, u32, u32, u32); // 0x3C
};

void lbMemory_80015320(s32 arg0, Handle* arg1, void* arg2, s32 cancelflag)
{
    struct LBMgr* temp_r30;
    s32 temp_r28;
    char* temp_r3;
    u32 temp_r26;
    u32 temp_r29;
    u32 temp_r31;
    void* temp_r25;

    temp_r3 = "lbmemory.c";
    temp_r29 = (u32) g_alloc.x6E4;
    if (cancelflag != 0) {
        __assert(temp_r3, 0x188U, temp_r3 + 0xB4);
    }
    if (arg1 != NULL) {
        temp_r31 = (u32) arg1->x4_lo;
        if (temp_r31 != temp_r29) {
            arg1->x4_lo = (void*) temp_r29;
            g_alloc.x6E4 = (void*) ((u32) arg1->x4_lo + (u32) arg1->x8_hi);
            if (arg1->x4_lo < (u8*) 0x80000000) {
                HSD_DevComRequest(0, (u32) arg1->x4_lo, (u32) temp_r29, ((u32) arg1->x8_hi + 0x1F) & ~0x1F, 0x1B, 1, (void*)lbMemory_80015320, arg1->x0_next);
                return;
            }
            temp_r30 = (struct LBMgr*) ((u8*) &g_alloc + 0x6A0);
            temp_r25 = arg1->x0_next;
            temp_r26 = ((u32) arg1->x8_hi + 0x1F) & ~0x1F;
            temp_r28 = OSDisableInterrupts();
            if ((u32) temp_r30->size != 0) {
                __assert(temp_r3, 0x14FU, temp_r3 + 0xA8);
            }
            temp_r30->src = arg1->x4_lo;
            temp_r30->dst = (u8*) temp_r29;
            temp_r30->size = temp_r26;
            temp_r30->offset = 0;
            temp_r30->cb_arg = (u32) arg1->x8_hi;
            temp_r30->cb = (void*)lbMemory_80015320;
            OSRestoreInterrupts(temp_r28);
            OSCreateAlarm(&temp_r30->alarm);
            OSSetAlarm(&temp_r30->alarm, OS_MSEC_TO_TICKS(3), fn_80015184);
            return;
        }
        g_alloc.x6E4 = (void*) (temp_r31 + (u32) arg1->x8_hi);
        lbMemory_80015320(0, (Handle*) arg1->x0_next, NULL, 0);
        return;
    }
    ((void (*)(u32)) g_alloc.x6E8)(g_alloc.x6E0);
}


/// might need to change to take lvalue instead of pointer if codegen is bad
#define PUSH_HANDLE(list, handle)                                             \
    do {                                                                      \
        handle->x0_next = *list;                                              \
        *list = handle;                                                       \
    } while (0)
#define POP_HANDLE(list, handle)                                              \
    do {                                                                      \
        handle = *list;                                                       \
        *list = handle->x0_next;                                              \
    } while (0)

/// pops handle from freelist and sets the popped regions's bounds
static inline Handle* new_handle(void* arenaLo, void* arenaHi)
{
    Handle* h;
    if (g_alloc.x698_free_heap == NULL) {
        __assert(__FILE__, 0x7BU, "_p(free_heap)");
    }
    // assert_arena_in_bounds(arenaLo, arenaHi);

    if (((u32) arenaLo < 0x80000000U) && ((u32) arenaHi < 0x80000000U)) {
        int ok = 0;
        if (((u32) arenaLo >= (u32) g_alloc.x0_arenaLo) &&
            ((u32) arenaHi <= (u32) g_alloc.x4_arenaHi))
        {
            ok = 1;
        }
        if (ok == 0) {
            __assert(__FILE__, 0x80U,
                     "(u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= "
                     "(u32)_p(a_arenaHi)");
        }
    }

    POP_HANDLE(&g_alloc.x698_free_heap, h);
    h->x0_next = NULL;
    h->x4_lo = arenaLo;
    h->x8_hi = arenaHi;
    h->xC_prev = NULL;
    return h;
}

Handle* lbMemory_80014E24(void* arenaLo, void* arenaHi)
{
    return new_handle(arenaLo, arenaHi);
}

/// moves a list of handles into x62C
/// then pushes the head to free_heap
/// why does it start at handle->xC_prev?
void lbMemory_80014EEC(Handle* handle)
{
    Handle* iter;
    Handle* tmp_next;
    if (handle == NULL) {
        __assert(__FILE__, 0x95U, "handle");
    }
    for (iter = handle->xC_prev; iter != NULL;) {
        tmp_next = iter->x0_next;
        PUSH_HANDLE(&g_alloc.x62C_free_mem, iter);
        iter = tmp_next;
        g_alloc.x630_num_allocs -= 1;
    }
    PUSH_HANDLE(&g_alloc.x698_free_heap, handle);
}

u32 lbMemory_80014F7C(Handle* h)
{
    u32 r0;
    u32 r4 = (u32) h->x4_lo;
    // this is weird.. i'm missing something
    // &h->xC_prev should be a Handle**,
    // and h->x0_prev looks the same as *h
    Handle* iter = (Handle*) &h->xC_prev;
    u32 sum = 0;

loop:
    iter = iter->x0_next;
    r0 = (u32) ((iter != NULL) ? iter->x4_lo : h->x8_hi);
    sum += r0 - r4;
    if (iter != NULL) {
        r4 = (u32) iter->x4_lo + (u32) iter->x8_hi;
        goto loop;
    }
    return sum;
}

/// malloc
Handle* lbMemory_80014FC8(Handle* arg0, u32 size)
{
    void* lo;
    Handle* memp_candidate;
    void* end;
    u32 least_leftover;
    u32 aligned_size;
    u32 leftover;
    u32 available_space;
    void* start;
    Handle* iter;

    least_leftover = 0x40000000U;
    if (g_alloc.x62C_free_mem == NULL) {
        __assert(__FILE__, 0xCCU, "_p(free_mem)");
    }
    start = arg0->x4_lo;
    // 32 byte alignment
    aligned_size = ((size + 0x1F) & 0xFFFFFFE0);
    iter = (Handle*) &arg0->xC_prev;
    memp_candidate = NULL;

    while (1) {
        // iter = var_r5->x0_next;
        // we look at iter each iteration,
        // until the last iteration, we check arg0
        end = (iter->x0_next != NULL) ? iter->x0_next->x4_lo : arg0->x8_hi;
        available_space = (u32) end - (u32) start;
        if (available_space >= aligned_size) {
            leftover = available_space - aligned_size;
            if (leftover <= least_leftover) {
                least_leftover = leftover;
                lo = start;
                memp_candidate = iter;
            }
        }
        if (iter->x0_next == NULL) {
            break;
        } else {
            iter = iter->x0_next;
            start = (void*) ((u32) iter->x4_lo + (u32) iter->x8_hi);
        }
    }
    if (memp_candidate == NULL) {
        // oom
        __assert(__FILE__, 0xE9U, "memp_kouho");
    }
    {
        Handle* result;
        POP_HANDLE(&g_alloc.x62C_free_mem, result);

        result->x8_hi = (void*) aligned_size;
        result->x4_lo = lo;
        result->x0_next = memp_candidate->x0_next;
        memp_candidate->x0_next = result;

        g_alloc.x630_num_allocs += 1;
        if (g_alloc.x630_num_allocs > g_alloc.x634_max_num_allocs) {
            g_alloc.x634_max_num_allocs = g_alloc.x630_num_allocs;
        }
        return result;
    }
}

void lbMemory_800150F0(Handle* h, void* arg1)
{
    Handle* handle = h->xC_prev;
    Handle* r6 = (Handle*) &h->xC_prev;

    while (handle != NULL) {
        if (handle->x4_lo == arg1) {
            r6->x0_next = handle->x0_next;
            PUSH_HANDLE(&g_alloc.x62C_free_mem, handle);
            g_alloc.x630_num_allocs -= 1;
            return;
        }
        r6 = handle;
        handle = handle->x0_next;
    }
    OSReport("[LbMem] Error: lbMemFreeToHeap %x.\n", arg1);
    __assert("lbmemory.c", 283, "0");
}

static s8 lbMemory_804D3794[8] = "p->size";

void fn_80015184(OSAlarm* alarm, OSContext* context)
{
    struct LBMgr* temp_r3;
    u32 temp_r3_2;
    u32 temp_r6;
    u32 var_r30;

    temp_r3 = (struct LBMgr*) ((u8*) &g_alloc + 0x6A0);
    if ((u32) temp_r3->size == 0U) {
        __assert("lbmemory.c", 0x127U, "p->size");
    }
    temp_r6 = temp_r3->offset;
    temp_r3_2 = temp_r3->size - temp_r6;
    var_r30 = temp_r3_2;
    if (temp_r3_2 > 0x19000U) {
        var_r30 = 0x19000;
    }
    memcpy(temp_r3->dst + temp_r6, temp_r3->src + temp_r6, var_r30);
    temp_r3->offset = temp_r3->offset + var_r30;
    if (temp_r3->offset == temp_r3->size) {
        temp_r3->size = 0U;
        temp_r3->cb(0, temp_r3->cb_arg, 0, 0);
        return;
    }
    OSCreateAlarm(&temp_r3->alarm);
    OSSetAlarm(&temp_r3->alarm, OS_MSEC_TO_TICKS(3), fn_80015184);
}

u32 lbMemory_8001529C(Handle* h, void* arg1, u32 arg2)
{
    void* lo;
    Handle* iter;
    void** r7;

    g_alloc.x6E8 = arg1;
    g_alloc.x6E0 = arg2;
    g_alloc.x6E4 = h->x4_lo;

    r7 = &g_alloc.x6E4;

    for (iter = h->xC_prev; iter != NULL; iter = iter->x0_next) {
        lo = iter->x4_lo;
        if (lo != *r7) {
            lbMemory_80015320(0, iter, 0, 0);
            return 1;
        }
        *r7 = (void*) ((u32) lo + (u32) iter->x8_hi);
    }
    return 0;
}

/// getArenaBounds
void lbMemory_800154BC(uintptr_t* arenaLo, uintptr_t* arenaHi)
{
    *arenaLo = (uintptr_t) g_alloc.x0_arenaLo;
    *arenaHi = (uintptr_t) g_alloc.x4_arenaHi;
}

/// same as lbMemory_80014E24, but sets to x69C to the popped handle
Handle* lbMemory_800154D4(void* arenaLo, void* arenaHi)
{
    g_alloc.x69C = new_handle(arenaLo, arenaHi);
    return g_alloc.x69C;
}

void lbMemory_800155A4(void)
{
    Handle* handle = g_alloc.x69C;
    Handle* iter;

    Handle** r5;

    HSD_ASSERT(149, handle);
    r5 = &g_alloc.x62C_free_mem;
    for (iter = handle->xC_prev; iter != NULL;) {
        Handle* tmp_next = iter->x0_next;
        PUSH_HANDLE(r5, iter);
        iter = tmp_next;
        g_alloc.x630_num_allocs -= 1;
    }
    PUSH_HANDLE(&g_alloc.x698_free_heap, handle);
    g_alloc.x69C = NULL;
}


void lbMemory_8001564C(void)
{
    u32 sp14;
    u32 var_r0;
    int i;

    g_alloc.x0_arenaLo = (void*) ARAlloc(0x20U);
    ARFree(&sp14);
    var_r0 = 0x01000000;
    if (ARGetSize() > 0x01000000U) {

    } else {
        var_r0 = ARGetSize();
    }
    g_alloc.x4_arenaHi = (void*) var_r0;
    
    g_alloc.x62C_free_mem = (Handle*) &g_alloc.x8[0];
    
    for (i = 0; i < 0x81; i++) {
        ((Handle*)&g_alloc.x8[i * 0xC])->x0_next = (Handle*)&g_alloc.x8[(i + 1) * 0xC];
    }
    ((Handle*)&g_alloc.x8[0x81 * 0xC])->x0_next = NULL;

    
    g_alloc.x698_free_heap = (Handle*)g_alloc.x638;
    for (i = 0; i < 7; i++) {
        ((Handle*)&g_alloc.x638[i * 0xC])->x0_next = (Handle*)&g_alloc.x638[(i + 1) * 0xC];
    }
    ((Handle*)&g_alloc.x638[7 * 0xC])->x0_next = NULL;

    g_alloc.x69C = lbMemory_80014E24(g_alloc.x0_arenaLo, g_alloc.x4_arenaHi);
}
