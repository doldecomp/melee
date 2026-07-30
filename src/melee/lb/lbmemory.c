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
    void* a_arenaLo;
    void* a_arenaHi;
    struct MemEntry x8_mem[0x83];
    Handle* free_mem;
    s32 x630_num_allocs;
    s32 x634_max_num_allocs;
    Handle x638_heap[6];
    Handle* free_heap;
    Handle* x69C;
    struct LBMgr x6A0_mgr;
    u32 x6E0;
    void* x6E4;
    void* x6E8;
    u8 x6EC[0x6F0 - 0x6EC];
};

/* 015320 */ void lbMemory_80015320(int, Handle*, int, int);

struct Allocator lbMemory_804318B0;
#define _p(x) (lbMemory_804318B0.x)
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

static inline Handle* new_handle(void* arenaLo, void* arenaHi)
{
    Handle* h;
    HSD_ASSERT(0x7B, _p(free_heap));

    if (((u32) arenaLo < 0x80000000U) && ((u32) arenaHi < 0x80000000U)) {
        HSD_ASSERT(0x80, (u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= (u32)_p(a_arenaHi));
    }

    POP_HANDLE(&_p(free_heap), h);
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
    HSD_ASSERT(149, handle);
    for (iter = handle->xC_prev; iter != NULL;) {
        tmp_next = iter->x0_next;
        PUSH_HANDLE(&_p(free_mem), iter);
        iter = tmp_next;
        _p(x630_num_allocs) -= 1;
    }
    PUSH_HANDLE(&_p(free_heap), handle);
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
    Handle* memp_kouho;
    void* end;
    u32 least_leftover;
    u32 aligned_size;
    u32 leftover;
    u32 available_space;
    void* start;
    Handle* iter;

    least_leftover = 0x40000000U;
    HSD_ASSERT(0xCC, _p(free_mem));
    aligned_size = ((size + 0x1F) & 0xFFFFFFE0);
    start = arg0->x4_lo;
    iter = (Handle*) &arg0->xC_prev;
    memp_kouho = NULL;

    while (1) {
        end = (iter->x0_next != NULL) ? iter->x0_next->x4_lo : arg0->x8_hi;
        available_space = (u32) end - (u32) start;
        if (available_space >= aligned_size) {
            leftover = available_space - aligned_size;
            if (leftover <= least_leftover) {
                least_leftover = leftover;
                lo = start;
                memp_kouho = iter;
            }
        }
        if (iter->x0_next == NULL) {
            break;
        } else {
            iter = iter->x0_next;
            start = (void*) ((u32) iter->x4_lo + (u32) iter->x8_hi);
        }
    }
    HSD_ASSERT(0xE9, memp_kouho);
    {
        Handle* result;
        POP_HANDLE(&_p(free_mem), result);

        result->x8_hi = (void*) aligned_size;
        result->x4_lo = lo;
        result->x0_next = memp_kouho->x0_next;
        memp_kouho->x0_next = result;

        _p(x630_num_allocs) += 1;
        if (_p(x630_num_allocs) > _p(x634_max_num_allocs)) {
            _p(x634_max_num_allocs) = _p(x630_num_allocs);
        }
        return result;
    }
}
void lbMemFreeToHeap(Handle* h, void* arg1)
{
    Handle* handle = h->xC_prev;
    Handle* r6 = (Handle*) &h->xC_prev;

    while (handle != NULL) {
        if (handle->x4_lo == arg1) {
            r6->x0_next = handle->x0_next;
            PUSH_HANDLE(&_p(free_mem), handle);
            _p(x630_num_allocs) -= 1;
            return;
        }
        r6 = handle;
        handle = handle->x0_next;
    }
    OSReport("[LbMem] Error: lbMemFreeToHeap %x.\n", arg1);
    HSD_ASSERT(283, 0);
}

void fn_80015184(OSAlarm* alarm, OSContext* context)
{
    struct LBMgr* p;
    u32 temp_r3_2;
    u32 temp_r6;
    u32 var_r30;

    p = &_p(x6A0_mgr);
    HSD_ASSERT(0x127, p->size);
    temp_r6 = p->offset;
    temp_r3_2 = p->size - temp_r6;
    var_r30 = temp_r3_2;
    if (temp_r3_2 > 0x19000U) {
        var_r30 = 0x19000;
    }
    memcpy(p->dst + temp_r6, p->src + temp_r6, var_r30);
    p->offset = p->offset + var_r30;
    if (p->offset == p->size) {
        p->size = 0U;
        p->cb(0, p->cb_arg, 0, 0);
        return;
    }
    OSCreateAlarm(&p->alarm);
    OSSetAlarm(&p->alarm, OSMillisecondsToTicks(3), fn_80015184);
}

u32 lbMemory_8001529C(Handle* h, void* arg1, u32 arg2)
{
    void* lo;
    Handle* iter;
    void** r7;

    _p(x6E8) = arg1;
    _p(x6E0) = arg2;
    _p(x6E4) = h->x4_lo;

    r7 = &_p(x6E4);

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

static void start_ram_copy(u32 old, u32 current, u32 size, Handle* next)
{
    struct LBMgr* p = &_p(x6A0_mgr);
    int enabled = OSDisableInterrupts();

    HSD_ASSERT(0x14F, !p->size);
    p->src = (u8*) old;
    p->dst = (u8*) current;
    p->size = size;
    p->offset = 0;
    p->cb_arg = (u32) next;
    p->cb = (void (*)(u32, u32, u32, u32))(Event) lbMemory_80015320;
    OSRestoreInterrupts(enabled);
    OSCreateAlarm(&p->alarm);
    OSSetAlarm(&p->alarm, OSMillisecondsToTicks(3), fn_80015184);
}

void lbMemory_80015320(int arg0, Handle* handle, int arg2, int cancelflag)
{
    void** currentp;
    u32 current;
    u32 old;

    currentp = &_p(x6E4);
    current = (u32) _p(x6E4);

    HSD_ASSERT(0x188, !cancelflag);

    if (handle != NULL) {
        if ((old = (u32) handle->x4_lo) != current) {
            handle->x4_lo = (void*) current;
            *currentp = (void*) ((u32) handle->x4_lo + (u32) handle->x8_hi);

            if ((u32) handle->x4_lo < 0x80000000U) {
                HSD_DevComRequest(
                    0, old, current, ((u32) handle->x8_hi + 0x1F) & 0xFFFFFFE0,
                    0x1B, 1, (HSD_DevComCallback) (Event) lbMemory_80015320,
                    handle->x0_next);
                return;
            } else {
                start_ram_copy(old, current,
                               ((u32) handle->x8_hi + 0x1F) & 0xFFFFFFE0,
                               handle->x0_next);
                return;
            }
        }

        *currentp = (void*) ((u32) old + (u32) handle->x8_hi);
        lbMemory_80015320(0, handle->x0_next, 0, 0);
        return;
    }

    ((void (*)(u32)) _p(x6E8))(_p(x6E0));
}

void lbMemory_800154BC(uintptr_t* arenaLo, uintptr_t* arenaHi)
{
    *arenaLo = (uintptr_t) _p(a_arenaLo);
    *arenaHi = (uintptr_t) _p(a_arenaHi);
}

Handle* lbMemory_800154D4(void* arenaLo, void* arenaHi)
{
    _p(x69C) = new_handle(arenaLo, arenaHi);
    return _p(x69C);
}

void lbMemory_800155A4(void)
{
    Handle* handle = _p(x69C);
    Handle* iter;

    Handle** r5;

    HSD_ASSERT(149, handle);
    r5 = &_p(free_mem);
    for (iter = handle->xC_prev; iter != NULL;) {
        Handle* tmp_next = iter->x0_next;
        PUSH_HANDLE(r5, iter);
        iter = tmp_next;
        _p(x630_num_allocs) -= 1;
    }
    PUSH_HANDLE(&_p(free_heap), handle);
    _p(x69C) = NULL;
}

#pragma push
#pragma dont_inline on
void lbMemory_8001564C(void)
{
    u32 size[3];
    int i;
    u8* base = (u8*) &lbMemory_804318B0;

    _p(a_arenaLo) = (void*) ARAlloc(0x20);
    ARFree(&size[2]);
    _p(a_arenaHi) =
        (void*) ((ARGetSize() > 0x01000000U) ? 0x01000000U : ARGetSize());

    _p(free_mem) = (Handle*) &_p(x8_mem)[0];
    for (i = 0; i < 0x82; i++) {
        _p(x8_mem)[i].x0_next = &_p(x8_mem)[i + 1];
    }
    _p(x8_mem)[i].x0_next = NULL;

    _p(x634_max_num_allocs) = 0;
    _p(x630_num_allocs) = 0;
    _p(free_heap) = (Handle*) (base + 0x638);
    *(void**) (base + 0x638) = base + 0x648;
    *(void**) (base + 0x648) = base + 0x658;
    *(void**) (base + 0x658) = base + 0x668;
    *(void**) (base + 0x668) = base + 0x678;
    *(void**) (base + 0x678) = base + 0x688;
    *(void**) (base + 0x688) = NULL;
    _p(x69C) = NULL;
    {
        void* hi = _p(a_arenaHi);
        void* lo = _p(a_arenaLo);
        _p(x69C) = lbMemory_80014E24(lo, hi);
    }
    *(u32*) (base + 0x6D0) = 0;
}
#pragma pop
