#include "lbmemory.h"

#include <Runtime/platform.h>

#include <string.h>

#include <dolphin/ar.h>
#include <dolphin/os/OSAlarm.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

struct LBMgr {
    OSAlarm alarm;
    const u8* src;
    u8* dst;
    u32 size;
    u32 offset;
    uintptr_t cb_arg;
    HSD_DevComCallback cb;
};

struct Allocator {
    uintptr_t a_arenaLo;
    uintptr_t a_arenaHi;
    HSD_AllocEntry mem[0x83];
    HSD_AllocEntry* free_mem;
    s32 num_allocs;
    s32 max_num_allocs;
    Handle heap[6];
    Handle* free_heap;
    Handle* aram_heap;
    struct LBMgr mgr;
    u32 compact_arg;
    uintptr_t compact_cursor;
    void (*compact_cb)(u32);
};

/* 015320 */ static void lbMemory_80015320(int, uintptr_t, void*, bool);

struct Allocator lbMemory_804318B0;
#define _p(x) (lbMemory_804318B0.x)
ASSERT_SIZE(HSD_AllocEntry, 0xC);
ASSERT_SIZE(lbMemory_804318B0, 0x6F0);

Handle* lbMemory_80014E24(void* arenaLo, void* arenaHi)
{
    Handle* h;
    HSD_ASSERT(0x7B, _p(free_heap));

    if ((uintptr_t) arenaLo < 0x80000000U && (uintptr_t) arenaHi < 0x80000000U)
    {
#ifdef MUST_MATCH
        // The retail assert string spells the u32 casts.
        HSD_ASSERT(0x80, (u32)arenaLo >= (u32)_p(a_arenaLo) && (u32)arenaHi <= (u32)_p(a_arenaHi));
#else
        HSD_ASSERT(0x80, (uintptr_t) arenaLo >= _p(a_arenaLo) &&
                            (uintptr_t) arenaHi <= _p(a_arenaHi));
#endif
    }

    h = _p(free_heap);
    _p(free_heap) = h->next;
    h->next = NULL;
    h->lo = arenaLo;
    h->hi = arenaHi;
    h->blocks = NULL;
    return h;
}

void lbMemory_80014EEC(Handle* handle)
{
    HSD_AllocEntry* block;
    HSD_AllocEntry* next;
    HSD_ASSERT(149, handle);
    for (block = handle->blocks; block != NULL; block = next) {
        next = block->next;
        block->next = _p(free_mem);
        _p(free_mem) = block;
        _p(num_allocs) -= 1;
    }
    handle->next = _p(free_heap);
    _p(free_heap) = handle;
}

u32 lbMemory_80014F7C(Handle* h)
{
    uintptr_t start = (uintptr_t) h->lo;
    HSD_AllocEntry** link = &h->blocks;
    uintptr_t end;
    u32 sum = 0;

    for (;;) {
        end = (uintptr_t) ((*link != NULL) ? (*link)->addr : h->hi);
        sum += end - start;
        if (*link == NULL) {
            break;
        }
        start = (uintptr_t) (*link)->addr + (*link)->size;
        link = &(*link)->next;
    }
    return sum;
}

HSD_AllocEntry* lbMemory_80014FC8(Handle* h, size_t size)
{
    uintptr_t lo;
    HSD_AllocEntry** memp_kouho;
    uintptr_t end;
    u32 least_leftover;
    u32 leftover;
    u32 available_space;
    uintptr_t start;
    HSD_AllocEntry** link;

    least_leftover = 0x40000000U;
    HSD_ASSERT(0xCC, _p(free_mem));
    size = OSRoundUp32B(size);
    start = (uintptr_t) h->lo;
    link = &h->blocks;
    memp_kouho = NULL;

    for (;;) {
        end = (uintptr_t) ((*link != NULL) ? (*link)->addr : h->hi);
        available_space = end - start;
        if (available_space >= size) {
            leftover = available_space;
            leftover -= size;
            if (leftover <= least_leftover) {
                least_leftover = leftover;
                lo = start;
                memp_kouho = link;
            }
        }
        if (*link == NULL) {
            break;
        }
        start = (uintptr_t) (*link)->addr + (*link)->size;
        link = &(*link)->next;
    }
    HSD_ASSERT(0xE9, memp_kouho);
    {
        HSD_AllocEntry* result = _p(free_mem);
        _p(free_mem) = result->next;

        result->size = size;
        result->addr = (void*) lo;
        result->next = *memp_kouho;
        *memp_kouho = result;

        _p(num_allocs) += 1;
        if (_p(num_allocs) > _p(max_num_allocs)) {
            _p(max_num_allocs) = _p(num_allocs);
        }
        return result;
    }
}

void lbMemFreeToHeap(Handle* h, void* addr)
{
    HSD_AllocEntry* block = h->blocks;
    HSD_AllocEntry** link = &h->blocks;

    while (block != NULL) {
        if (block->addr == addr) {
            *link = block->next;
            block->next = _p(free_mem);
            _p(free_mem) = block;
            _p(num_allocs) -= 1;
            return;
        }
        link = &block->next;
        block = block->next;
    }
#ifdef MUST_MATCH
    OSReport("[LbMem] Error: lbMemFreeToHeap %x.\n", (unsigned) addr);
#else
    OSReport("[LbMem] Error: lbMemFreeToHeap %p.\n", addr);
#endif
    HSD_ASSERT(283, 0);
}

static void fn_80015184(OSAlarm* alarm, OSContext* context)
{
    struct LBMgr* p;
    u32 remaining;
    u32 offset;
    u32 slice;

    p = &_p(mgr);
    HSD_ASSERT(0x127, p->size);
    offset = p->offset;
    remaining = p->size - offset;
    slice = remaining;
    if (remaining > 0x19000U) {
        slice = 0x19000;
    }
    memcpy(p->dst + offset, p->src + offset, slice);
    p->offset = p->offset + slice;
    if (p->offset == p->size) {
        p->size = 0U;
        p->cb(0, p->cb_arg, 0, 0);
        return;
    }
    OSCreateAlarm(&p->alarm);
    OSSetAlarm(&p->alarm, OSMillisecondsToTicks(3), fn_80015184);
}

u32 lbMemory_8001529C(Handle* h, void (*cb)(u32), u32 arg)
{
    HSD_AllocEntry* block;

    _p(compact_cb) = cb;
    _p(compact_arg) = arg;
    _p(compact_cursor) = (uintptr_t) h->lo;

    for (block = h->blocks; block != NULL; block = block->next) {
        if ((uintptr_t) block->addr != _p(compact_cursor)) {
            lbMemory_80015320(0, (uintptr_t) block, NULL, false);
            return 1;
        }
        _p(compact_cursor) = (uintptr_t) block->addr + block->size;
    }
    return 0;
}

static void start_ram_copy(const void* src, void* dst, u32 size,
                           HSD_AllocEntry* next)
{
    struct LBMgr* p = &_p(mgr);
    int enabled = OSDisableInterrupts();

    HSD_ASSERT(0x14F, !p->size);
    p->src = src;
    p->dst = dst;
    p->size = size;
    p->offset = 0;
    p->cb_arg = (uintptr_t) next;
    p->cb = lbMemory_80015320;
    OSRestoreInterrupts(enabled);
    OSCreateAlarm(&p->alarm);
    OSSetAlarm(&p->alarm, OSMillisecondsToTicks(3), fn_80015184);
}

static void lbMemory_80015320(int arg0, uintptr_t arg1, void* arg2,
                              bool cancelflag)
{
    HSD_AllocEntry* block = (HSD_AllocEntry*) arg1;
    void* current = (void*) _p(compact_cursor);
    void* src;

    HSD_ASSERT(0x188, !cancelflag);

    if (block != NULL) {
        if (block->addr != current) {
            src = block->addr;
            block->addr = current;
            _p(compact_cursor) = (uintptr_t) block->addr + block->size;

            if ((uintptr_t) block->addr < 0x80000000U) {
                HSD_DevComRequest(0, (uintptr_t) src, (uintptr_t) current,
                                  OSRoundUp32B(block->size), 0x1B, 1,
                                  lbMemory_80015320, (uintptr_t) block->next);
            } else {
                start_ram_copy(src, current, OSRoundUp32B(block->size),
                               block->next);
            }
            return;
        }

        _p(compact_cursor) = (uintptr_t) block->addr + block->size;
        lbMemory_80015320(0, (uintptr_t) block->next, NULL, false);
        return;
    }

    _p(compact_cb)(_p(compact_arg));
}

void lbMemory_800154BC(uintptr_t* arenaLo, uintptr_t* arenaHi)
{
    *arenaLo = _p(a_arenaLo);
    *arenaHi = _p(a_arenaHi);
}

Handle* lbMemory_800154D4(void* arenaLo, void* arenaHi)
{
    _p(aram_heap) = lbMemory_80014E24(arenaLo, arenaHi);
    return _p(aram_heap);
}

void lbMemory_800155A4(void)
{
    lbMemory_80014EEC(_p(aram_heap));
    _p(aram_heap) = NULL;
}

void lbMemory_8001564C(void)
{
    u32 freed_size;
    int i;

    _p(a_arenaLo) = ARAlloc(0x20);
    ARFree(&freed_size);
    _p(a_arenaHi) = (ARGetSize() > 0x01000000U) ? 0x01000000U : ARGetSize();

    _p(free_mem) = &_p(mem)[0];
    for (i = 0; i < (int) ARRAY_SIZE(_p(mem)) - 1; i++) {
        _p(mem)[i].next = &_p(mem)[i + 1];
    }
    _p(mem)[i].next = NULL;

    _p(max_num_allocs) = 0;
    _p(num_allocs) = 0;
    _p(free_heap) = &_p(heap)[0];
    for (i = 0; i < (int) ARRAY_SIZE(_p(heap)) - 1; i++) {
        _p(heap)[i].next = &_p(heap)[i + 1];
    }
    _p(heap)[i].next = NULL;
    _p(aram_heap) = NULL;
    lbMemory_800154D4((void*) _p(a_arenaLo), (void*) _p(a_arenaHi));
    _p(mgr).size = 0;
}
