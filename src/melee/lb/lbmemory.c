#include "lbmemory.h"

#include <platform.h>

#include <dolphin/ar.h>
#include <baselib/debug.h>
#include <baselib/devcom.h>

struct MemEntry {
    struct MemEntry* x0_next;
    void* x4_lo;
    void* x8_hi;
};

struct LBMgr {
    OSAlarm alarm;                  // 0x00
    u8* src;                        // 0x28
    u8* dst;                        // 0x2C
    u32 size;                       // 0x30
    u32 offset;                     // 0x34
    u32 cb_arg;                     // 0x38
    void (*cb)(u32, u32, u32, u32); // 0x3C
};

struct Allocator {
    void* x0_arenaLo;
    void* x4_arenaHi;
    struct MemEntry x8_mem[0x83];
    Handle* x62C_free_mem;
    s32 x630_num_allocs;
    s32 x634_max_num_allocs;
    Handle x638_heap[6];
    Handle* x698_free_heap;
    Handle* x69C;
    struct LBMgr x6A0_mgr;
    u32 x6E0;
    void* x6E4;
    void* x6E8;
    u8 x6EC[0x6F0 - 0x6EC];
};

/* 015320 */ void lbMemory_80015320(int, Handle*, int, int);

struct Allocator lbMemory_804318B0;
#define g_alloc lbMemory_804318B0
STATIC_ASSERT(sizeof(struct MemEntry) == 0xC);
STATIC_ASSERT(sizeof(lbMemory_804318B0) == 0x6F0);

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

static char lbl_803BA2C0[0xB] = "lbmemory.c";
static char lbl_803BA2CC[0xE] = "_p(free_heap)";
static char lbl_803BA2DC[0x49] =
    "(u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= "
    "(u32)_p(a_arenaHi)";
static char lbl_803BA328[0xD] = "_p(free_mem)";
static char lbl_803BA338[0xB] = "memp_kouho";
static char lbl_803BA344[0x24] = "[LbMem] Error: lbMemFreeToHeap %x.\n";
static char lbl_803BA368[0x18] = "!p->size\0\0\0\0!cancelflag";

SDATA char lbMemory_804D3788[7] = "handle";
SDATA char lbMemory_804D3790[2] = "0";
SDATA char lbMemory_804D3794[8] = "p->size";

static inline Handle* new_handle(void* arenaLo, void* arenaHi)
{
    Handle* h;
    if (g_alloc.x698_free_heap == NULL) {
        __assert(lbl_803BA2C0, 0x7BU, lbl_803BA2CC);
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
            __assert(lbl_803BA2C0, 0x80U, lbl_803BA2DC);
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

void lbMemory_80014EEC(Handle* handle)
{
    Handle* iter;
    Handle* tmp_next;
    if (handle == NULL) {
        __assert(lbl_803BA2C0, 0x95U, lbMemory_804D3788);
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
        __assert(lbl_803BA2C0, 0xCCU, lbl_803BA328);
    }
    aligned_size = ((size + 0x1F) & 0xFFFFFFE0);
    start = arg0->x4_lo;
    iter = (Handle*) &arg0->xC_prev;
    memp_candidate = NULL;

    while (1) {
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
        __assert(lbl_803BA2C0, 0xE9U, lbl_803BA338);
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
    OSReport(lbl_803BA344, arg1);
    __assert(lbl_803BA2C0, 283, lbMemory_804D3790);
}

void fn_80015184(OSAlarm* alarm, OSContext* context)
{
    struct LBMgr* temp_r3;
    u32 temp_r3_2;
    u32 temp_r6;
    u32 var_r30;

    temp_r3 = &g_alloc.x6A0_mgr;
    if ((u32) temp_r3->size == 0U) {
        __assert(lbl_803BA2C0, 0x127U, lbMemory_804D3794);
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
    OSSetAlarm(&temp_r3->alarm, OSMillisecondsToTicks(3), fn_80015184);
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

void lbMemory_80015320(int arg0, Handle* handle, int arg2, int cancelflag)
{
    struct Allocator* alloc;
    struct LBMgr* mgr;
    int enabled;
    void** currentp;
    u32 size;
    u32 old;
    u32 current;
    Handle* next;

    alloc = &g_alloc;
    currentp = &alloc->x6E4;
    current = (u32) alloc->x6E4;

    if (cancelflag != 0) {
        __assert(lbl_803BA2C0, 0x188U, &lbl_803BA368[0xC]);
    }

    if (handle != NULL) {
        if ((old = (u32) handle->x4_lo) != current) {
            handle->x4_lo = (void*) current;
            arg0 = old;
            *currentp = (void*) ((u32) handle->x4_lo + (u32) handle->x8_hi);

            if ((u32) handle->x4_lo < 0x80000000U) {
                HSD_DevComRequest(
                    0, arg0, current,
                    ((u32) handle->x8_hi + 0x1F) & 0xFFFFFFE0, 0x1B, 1,
                    (HSD_DevComCallback) (Event) lbMemory_80015320,
                    handle->x0_next);
                return;
            } else {
                mgr = &alloc->x6A0_mgr;
                next = handle->x0_next;
                size = ((u32) handle->x8_hi + 0x1F) & 0xFFFFFFE0;
                enabled = OSDisableInterrupts();

                if (mgr->size != 0) {
                    __assert(lbl_803BA2C0, 0x14FU, lbl_803BA368);
                }
                mgr->src = (u8*) old;
                mgr->dst = (u8*) current;
                mgr->size = size;
                mgr->offset = 0;
                mgr->cb_arg = (u32) next;
                mgr->cb =
                    (void (*)(u32, u32, u32, u32))(Event) lbMemory_80015320;
                OSRestoreInterrupts(enabled);
                OSCreateAlarm(&mgr->alarm);
                OSSetAlarm(&mgr->alarm, OSMillisecondsToTicks(3), fn_80015184);
                return;
            }
        }

        *currentp = (void*) ((u32) old + (u32) handle->x8_hi);
        lbMemory_80015320(0, handle->x0_next, 0, 0);
        return;
    }

    ((void (*)(u32)) alloc->x6E8)(alloc->x6E0);
}

void lbMemory_800154BC(uintptr_t* arenaLo, uintptr_t* arenaHi)
{
    *arenaLo = (uintptr_t) g_alloc.x0_arenaLo;
    *arenaHi = (uintptr_t) g_alloc.x4_arenaHi;
}

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

    if (handle == NULL) {
        __assert(lbl_803BA2C0, 149, lbMemory_804D3788);
    }
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

#pragma push
#pragma dont_inline on
void lbMemory_8001564C(void)
{
    u32 size[3];
    int i;
    u8* base = (u8*) &g_alloc;

    g_alloc.x0_arenaLo = (void*) ARAlloc(0x20);
    ARFree(&size[2]);
    g_alloc.x4_arenaHi =
        (void*) ((ARGetSize() > 0x01000000U) ? 0x01000000U : ARGetSize());

    g_alloc.x62C_free_mem = (Handle*) &g_alloc.x8_mem[0];
    for (i = 0; i < 0x82; i++) {
        g_alloc.x8_mem[i].x0_next = &g_alloc.x8_mem[i + 1];
    }
    g_alloc.x8_mem[i].x0_next = NULL;

    g_alloc.x634_max_num_allocs = 0;
    g_alloc.x630_num_allocs = 0;
    g_alloc.x698_free_heap = (Handle*) (base + 0x638);
    *(void**) (base + 0x638) = base + 0x648;
    *(void**) (base + 0x648) = base + 0x658;
    *(void**) (base + 0x658) = base + 0x668;
    *(void**) (base + 0x668) = base + 0x678;
    *(void**) (base + 0x678) = base + 0x688;
    *(void**) (base + 0x688) = NULL;
    g_alloc.x69C = NULL;
    {
        void* hi = g_alloc.x4_arenaHi;
        void* lo = g_alloc.x0_arenaLo;
        g_alloc.x69C = lbMemory_80014E24(lo, hi);
    }
    *(u32*) (base + 0x6D0) = 0;
}
#pragma pop
