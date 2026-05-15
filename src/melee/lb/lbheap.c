#include "lbheap.static.h"

#include "placeholder.h"

#include <dolphin/os/OSInterrupt.h>
#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/initialize.h>
#include <baselib/memory.h>
#include <melee/lb/lbmemory.h>

struct lbHeap_HeapDesc {
    u32 idx;
    u32 type;
    u32 prev_idx;
    u32 size;
};

struct lbHeap_HeapOffsetView {
    u8 pad[0x10];
    struct Heap heap;
};

struct lbHeap_HeapDesc lbHeap_803BA380[5] = {
    { 2, 1, 6, 0x800 },    { 3, 1, 2, 0x4F8800 }, { 4, 2, 6, 0x64B400 },
    { 5, 4, 6, 0x96C800 }, { 6, 0, 0, 0 },
};

#define lbHeap_GetHeapOffsetView(offset)                                      \
    ((struct lbHeap_HeapOffsetView*) ((u32) (&lbHeap_80431FA0) + (offset)))

static inline void lbHeap_ResetHeap(struct Heap* heap)
{
    heap->id = -1;
    heap->handle = (Handle*) -1;
    heap->start = 0;
    heap->size = 0;
    heap->type = 1;
    heap->transient = 1;
    heap->status = 1;
}

static inline void
lbHeap_DestroyOffsetViewIfCreated(struct lbHeap_HeapOffsetView* view)
{
    struct Heap* heap = &view->heap;

    if (view->heap.status == 0) {
        if (heap->type == 0) {
            OSDestroyHeap(heap->id);
            heap->id = -1;
        } else {
            lbMemory_80014EEC(heap->handle);
            heap->handle = (Handle*) -1;
        }
        heap->status = 1;
    }
}

static inline void
lbHeap_CreateOffsetViewIfDestroyed(struct lbHeap_HeapOffsetView* view)
{
    struct Heap* heap = &view->heap;

    if (view->heap.status == 1) {
        if (heap->type == 0) {
            heap->id = OSCreateHeap((void*) heap->start,
                                    (void*) (heap->start + heap->size));
        } else {
            heap->handle = lbMemory_80014E24(
                (void*) heap->start, (void*) (heap->start + heap->size));
        }
        heap->status = 0;
    }
}

void lbHeap_800158D0(int arg0, int arg1)
{
    lbHeap_80431FA0.heap_array[arg0].transient = arg1;
}

int lbHeap_800158E8(int arg0)
{
    return lbHeap_80431FA0.heap_array[arg0].transient;
}

void lbHeap_80015900(void)
{
    s32 temp_r0;
    struct lbHeap_HeapOffsetView* destroy_view;
    struct Heap* bounds_heap;
    struct lbHeap_HeapOffsetView* create_view;
    s32 destroy_i;
    s32 heap_offset;
    s32 bounds_i;
    s32 create_i;
    u32 arena_lo;
    u32 aram_lo;
    u32 aram_hi;
    u32 arena_hi;
    struct Heap* main_heap;
    struct Heap* aram_heap;

    /// @remarks 0 and 1 are reserved for HSD and ARAM
    for (destroy_i = 2, heap_offset = 0x38; destroy_i < 6;
         destroy_i++, heap_offset += sizeof(struct Heap))
    {
        if (lbHeap_80431FA0.heap_array[destroy_i].transient == 1) {
            destroy_view = lbHeap_GetHeapOffsetView(heap_offset);
            lbHeap_DestroyOffsetViewIfCreated(destroy_view);
        }
    }

    arena_lo = (u32) lbHeap_80431FA0.arena_lo;
    arena_hi = (u32) lbHeap_80431FA0.arena_hi;
    aram_lo = lbHeap_80431FA0.aram_lo;
    aram_hi = lbHeap_80431FA0.aram_hi;

    for (bounds_i = 2; bounds_i < 4; bounds_i++) {
        bounds_heap = &lbHeap_80431FA0.heap_array[bounds_i * 2 - 2];
        if (bounds_heap->transient == 0) {
            switch (bounds_heap->type) {
            case 1:
                temp_r0 = bounds_heap->start + bounds_heap->size;
                if (arena_lo < temp_r0) {
                    arena_lo = temp_r0;
                }
                break;

            case 2:
                if (arena_hi > bounds_heap->start) {
                    arena_hi = bounds_heap->start;
                }
                break;

            case 4:
                temp_r0 = bounds_heap->start + bounds_heap->size;
                if (aram_lo < temp_r0) {
                    aram_lo = temp_r0;
                }
                break;
            }
        }

        bounds_heap++;
        if (bounds_heap->transient == 0) {
            switch (bounds_heap->type) {
            case 1:
                temp_r0 = bounds_heap->start + bounds_heap->size;
                if (arena_lo < temp_r0) {
                    arena_lo = temp_r0;
                }
                break;

            case 2:
                if (arena_hi > bounds_heap->start) {
                    arena_hi = bounds_heap->start;
                }
                break;

            case 4:
                temp_r0 = bounds_heap->start + bounds_heap->size;
                if (aram_lo < temp_r0) {
                    aram_lo = temp_r0;
                }
                break;
            }
        }
    }

    main_heap = &lbHeap_80431FA0.heap_array[0];
    main_heap->id = HSD_CreateMainHeap((void*) arena_lo, (void*) arena_hi);
    main_heap->start = arena_lo;
    aram_heap = &lbHeap_80431FA0.heap_array[1];
    main_heap->size = arena_hi - arena_lo;
    main_heap->status = 0;
    main_heap->type = 0;

    lbMemory_800155A4();

    aram_heap->handle = lbMemory_800154D4((void*) aram_lo, (void*) aram_hi);
    aram_heap->start = aram_lo;
    aram_heap->size = aram_hi - aram_lo;
    aram_heap->status = 0;
    aram_heap->type = 3;

    for (create_i = 2, heap_offset = 0x38; create_i < 6;
         create_i++, heap_offset += sizeof(struct Heap))
    {
        if (lbHeap_80431FA0.heap_array[create_i].transient == 0) {
            create_view = lbHeap_GetHeapOffsetView(heap_offset);
            lbHeap_CreateOffsetViewIfDestroyed(create_view);
        }
    }
}

int lbHeap_80015BB8(int arg0)
{
    return lbHeap_80431FA0.heap_array[arg0].status;
}

void* lbHeap_80015BD0(int arg0, int arg1)
{
    Handle* result;
    int enabled = OSDisableInterrupts();
    struct Heap* p = &lbHeap_80431FA0.heap_array[arg0];

    if (p->status == 0) {
        if (p->type == 0) {
            int cur_heap = HSD_GetHeap();
            HSD_SetHeap(p->id);
            result = HSD_MemAlloc(arg1);
            HSD_SetHeap(cur_heap);
        } else {
            result = lbMemory_80014FC8(p->handle, arg1);
            if (p->type == 3) {
                result = result->x4_lo;
            }
        }
    } else {
        result = NULL;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

void lbHeap_80015CA8(int arg0, void* arg1)
{
    int enabled = OSDisableInterrupts();
    struct Heap* p = &lbHeap_80431FA0.heap_array[arg0];

    if (p->status != 0) {
        __assert("lbheap.c", 0x143, "p->status == LbHeapStatus_Create");
    }
    if (p->type == 0) {
        int cur_heap = HSD_GetHeap();
        HSD_SetHeap(p->id);
        HSD_Free(arg1);
        HSD_SetHeap(cur_heap);
    } else {
        lbMemory_800150F0(p->handle, arg1);
    }
    OSRestoreInterrupts(enabled);
}

int lbHeap_80015D6C(u32 heap0, UNK_T cb, u32 heap1)
{
    int enabled = OSDisableInterrupts();
    struct Heap* p = &lbHeap_80431FA0.heap_array[heap0];
    int var_r30;

    if (heap0 <= 1) {
        var_r30 = 0;
    } else {
        var_r30 = lbMemory_8001529C(p->handle, cb, heap1);
    }
    OSRestoreInterrupts(enabled);
    return var_r30;
}

char* lbHeap_803BA448[] = {
    "     Hsd", "    ARAM", "     Seq", "    Stay", "    AllM", "    AllA",
};

void lbHeap_80015DF8(void)
{
    ssize_t bytes;
    struct Heap* p;
    int i;
    int var_r25;

    OSReport("[lbHeap] -- Report --\n");

    for (i = 0; i < 6; i++) {
        OSReport("%s :", lbHeap_803BA448[i]);
        p = &lbHeap_80431FA0.heap_array[i];
        if (p->status == 0) {
            if (p->type == 0) {
                var_r25 = OSCheckHeap(p->id);
            } else {
                var_r25 = lbMemory_80014F7C(p->handle);
            }
            OSReport(" %5d KB + ", (p->size - var_r25) / 1024);
            OSReport(" %5d KB( %8d)", var_r25 / 1024, var_r25);
        } else {
            OSReport("                         destroy");
        }
        OSReport(" / %5d KB\n", p->size / 1024, p->size);
    }

    bytes = (u32) lbHeap_80431FA0.arena_hi - (u32) lbHeap_80431FA0.arena_lo;
    OSReport("MainRAM Total : %5d KB( %8d)\n", bytes / 1024, bytes);
    bytes = lbHeap_80431FA0.aram_hi - lbHeap_80431FA0.aram_lo;
    OSReport("   ARAM Total : %5d KB( %8d)\n", bytes / 1024, bytes);
}

void lbHeap_80015F3C(void)
{
    int curr_idx;
    int prev_idx;
    struct Heap* curr_heap;
    struct Heap* prev_heap;
    struct lbHeap_HeapDesc* desc;

    HSD_GetNextArena(&lbHeap_80431FA0.arena_lo, &lbHeap_80431FA0.arena_hi);
    lbMemory_800154BC(&lbHeap_80431FA0.aram_lo, &lbHeap_80431FA0.aram_hi);

    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[0]);
    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[1]);
    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[2]);
    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[3]);
    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[4]);
    lbHeap_ResetHeap(&lbHeap_80431FA0.heap_array[5]);

    desc = lbHeap_803BA380;
    while ((curr_idx = desc->idx) != 6) {
        curr_heap = &lbHeap_80431FA0.heap_array[curr_idx];

        curr_heap->type = desc->type;
        curr_heap->size = desc->size;
        prev_idx = desc->prev_idx;
        if (prev_idx == 6) {
            switch (curr_heap->type) {
            case 3:
                break;
            case 1:
                curr_heap->start = (s32) lbHeap_80431FA0.arena_lo;
                break;
            case 2:
                curr_heap->start =
                    (u32) lbHeap_80431FA0.arena_hi - curr_heap->size;
                break;
            case 4:
                curr_heap->start = (s32) lbHeap_80431FA0.aram_lo;
                break;
            }
        } else {
            prev_heap = &lbHeap_80431FA0.heap_array[prev_idx];
            switch (curr_heap->type) {
            case 3:
                break;
            case 1:
                curr_heap->start = prev_heap->start + prev_heap->size;
                break;
            case 2:
                curr_heap->start = prev_heap->start - curr_heap->size;
                break;
            case 4:
                curr_heap->start = prev_heap->start + prev_heap->size;
                break;
            }
        }
        desc++;
    }
}
