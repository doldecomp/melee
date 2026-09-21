#include "lbheap.static.h"
#include "lbmemory.h"
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/initialize.h>
#include <sysdolphin/baselib/memory.h>

struct lbHeap_HeapDesc {
    u32 idx;
    u32 type;
    u32 prev_idx;
    u32 size;
};

/// Placement of the heaps after the two reserved ones; @c LbHeapKind_Count
/// means no heap.
struct lbHeap_HeapDesc lbHeap_803BA380[5] = {
    { LbHeapKind_Seq, 1, LbHeapKind_Count, 0x800 },
    { LbHeapKind_Stay, 1, LbHeapKind_Seq, 0x4F8800 },
    { LbHeapKind_AllM, 2, LbHeapKind_Count, 0x64B400 },
    { LbHeapKind_AllA, 4, LbHeapKind_Count, 0x96C800 },
    { LbHeapKind_Count, 0, 0, 0 },
};

static inline void resetHeap(LbHeapKind kind)
{
    struct Heap* heap = &lbHeap_80431FA0.heap_array[kind];
    heap->id = -1;
    heap->handle = (Handle*) -1;
    heap->start = 0;
    heap->size = 0;
    heap->type = 1;
    heap->transient = 1;
    heap->status = LbHeapStatus_Destroy;
}

static inline void destroyHeap(LbHeapKind kind)
{
    struct Heap* heap = &lbHeap_80431FA0.heap_array[kind];
    if (heap->status == LbHeapStatus_Create) {
        if (heap->type == 0) {
            OSDestroyHeap(heap->id);
            heap->id = -1;
        } else {
            lbMemory_80014EEC(heap->handle);
            heap->handle = (Handle*) -1;
        }
        heap->status = LbHeapStatus_Destroy;
    }
}

static inline void createHeap(LbHeapKind kind)
{
    struct Heap* heap = &lbHeap_80431FA0.heap_array[kind];
    if (heap->status == LbHeapStatus_Destroy) {
        if (heap->type == 0) {
            heap->id = OSCreateHeap((void*) heap->start,
                                    (void*) (heap->start + heap->size));
        } else {
            heap->handle =
                lbMemory_80014E24(heap->start, heap->start + heap->size);
        }
        heap->status = LbHeapStatus_Create;
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
    uintptr_t arena_hi;
    uintptr_t arena_lo;
    s32 create_i;
    struct Heap* main_heap;
    s32 bounds_i;
    s32 end;
    struct Heap* bounds_heap;
    uintptr_t aram_lo;
    uintptr_t aram_hi;
    s32 destroy_i;
    struct Heap* aram_heap;

    for (destroy_i = LbHeapKind_Seq; destroy_i < LbHeapKind_Count; destroy_i++)
    {
        if (lbHeap_80431FA0.heap_array[destroy_i].transient == 1) {
            destroyHeap(destroy_i);
        }
    }

    arena_lo = (uintptr_t) lbHeap_80431FA0.arena_lo;
    arena_hi = (uintptr_t) lbHeap_80431FA0.arena_hi;
    aram_lo = lbHeap_80431FA0.aram_lo;
    aram_hi = lbHeap_80431FA0.aram_hi;

    for (bounds_i = LbHeapKind_Seq; bounds_i < LbHeapKind_Count; bounds_i++) {
        bounds_heap = &lbHeap_80431FA0.heap_array[bounds_i];
        if (lbHeap_80431FA0.heap_array[bounds_i].transient == 0) {
            switch (bounds_heap->type) {
            case 1:
                end = bounds_heap->start + bounds_heap->size;
                if (arena_lo < end) {
                    arena_lo = end;
                }
                break;

            case 2:
                if (arena_hi > bounds_heap->start) {
                    arena_hi = bounds_heap->start;
                }
                break;

            case 4:
                end = bounds_heap->start + bounds_heap->size;
                if (aram_lo < end) {
                    aram_lo = end;
                }
                break;
            }
        }
    }

    main_heap = &lbHeap_80431FA0.heap_array[LbHeapKind_Hsd];
    main_heap->id = HSD_CreateMainHeap((void*) arena_lo, (void*) arena_hi);
    main_heap->start = arena_lo;
    aram_heap = &lbHeap_80431FA0.heap_array[LbHeapKind_ARAM];
    main_heap->size = arena_hi - arena_lo;
    main_heap->status = LbHeapStatus_Create;
    main_heap->type = 0;

    lbMemory_800155A4();

    aram_heap->handle = lbMemory_800154D4(aram_lo, aram_hi);
    aram_heap->start = aram_lo;
    aram_heap->size = aram_hi - aram_lo;
    aram_heap->status = LbHeapStatus_Create;
    aram_heap->type = 3;

    for (create_i = LbHeapKind_Seq; create_i < LbHeapKind_Count; create_i++) {
        if (lbHeap_80431FA0.heap_array[create_i].transient == 0) {
            createHeap(create_i);
        }
    }
}

LbHeapStatus lbHeap_80015BB8(int arg0)
{
    return lbHeap_80431FA0.heap_array[arg0].status;
}

void* lbHeap_80015BD0(int heap_id, size_t size)
{
    void* result;
    int enabled = OSDisableInterrupts();
    struct Heap* p = &lbHeap_80431FA0.heap_array[heap_id];

    if (p->status == LbHeapStatus_Create) {
        if (p->type == 0) {
            int cur_heap = HSD_GetHeap();
            HSD_SetHeap(p->id);
            result = HSD_MemAlloc(size);
            HSD_SetHeap(cur_heap);
        } else {
            result = lbMemory_80014FC8(p->handle, size);
            if (p->type == 3) {
                // The ARAM heap hands out the block's address, not the block.
                result = (void*) ((HSD_AllocEntry*) result)->addr;
            }
        }
    } else {
        result = NULL;
    }
    OSRestoreInterrupts(enabled);
    return result;
}

void lbHeap_80015CA8(int arg0, uintptr_t addr)
{
    int enabled = OSDisableInterrupts();
    struct Heap* p = &lbHeap_80431FA0.heap_array[arg0];

    HSD_ASSERT(0x143, p->status == LbHeapStatus_Create);
    if (p->type == 0) {
        int cur_heap = HSD_GetHeap();
        HSD_SetHeap(p->id);
        HSD_Free((void*) addr);
        HSD_SetHeap(cur_heap);
    } else {
        lbMemFreeToHeap(p->handle, addr);
    }
    OSRestoreInterrupts(enabled);
}

int lbHeap_80015D6C(u32 heap0, void (*cb)(u32), u32 heap1)
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

    for (i = 0; i < LbHeapKind_Count; i++) {
        OSReport("%s :", lbHeap_803BA448[i]);
        p = &lbHeap_80431FA0.heap_array[i];
        if (p->status == LbHeapStatus_Create) {
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

    bytes = (uintptr_t) lbHeap_80431FA0.arena_hi -
            (uintptr_t) lbHeap_80431FA0.arena_lo;
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
    LbHeapKind kind;

    HSD_GetNextArena(&lbHeap_80431FA0.arena_lo, &lbHeap_80431FA0.arena_hi);
    lbMemory_800154BC(&lbHeap_80431FA0.aram_lo, &lbHeap_80431FA0.aram_hi);

    for (kind = 0; kind < LbHeapKind_Count; kind++) {
        resetHeap(kind);
    }

    desc = lbHeap_803BA380;
    while ((curr_idx = desc->idx) != LbHeapKind_Count) {
        curr_heap = &lbHeap_80431FA0.heap_array[curr_idx];

        curr_heap->type = desc->type;
        curr_heap->size = desc->size;
        prev_idx = desc->prev_idx;
        if (prev_idx == LbHeapKind_Count) {
            switch (curr_heap->type) {
            case 3:
                break;
            case 1:
                curr_heap->start = (uintptr_t) lbHeap_80431FA0.arena_lo;
                break;
            case 2:
                curr_heap->start =
                    (uintptr_t) lbHeap_80431FA0.arena_hi - curr_heap->size;
                break;
            case 4:
                curr_heap->start = lbHeap_80431FA0.aram_lo;
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
