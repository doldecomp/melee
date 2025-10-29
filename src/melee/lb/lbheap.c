#include "lbheap.static.h"
#include "placeholder.h"

#include <dolphin/os/OSInterrupt.h>
#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/initialize.h>
#include <baselib/memory.h>
#include <melee/lb/lbmemory.h>

struct {
    u32 idx;
    u32 type;
    u32 prev_idx;
    u32 size;
} lbHeap_803BA380[5] = {
    { 2, 1, 6, 0x800 },    { 3, 1, 2, 0x4F8800 }, { 4, 2, 6, 0x64B400 },
    { 5, 4, 6, 0x96C800 }, { 6, 0, 0, 0 },
};

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
    s32 i;
    u32* aram_hi;
    u32* aram_lo;
    u32* arena_hi;
    u32* arena_lo;

    /// @remarks 0 and 1 are reserved for HSD and ARAM
    for (i = 2; i < 6; i++) {
        if (lbHeap_80431FA0.heap_array[i].transient == 1) {
            if (lbHeap_80431FA0.heap_array[i].status == 0) {
                if (lbHeap_80431FA0.heap_array[i].type == 0) {
                    OSDestroyHeap(lbHeap_80431FA0.heap_array[i].id);
                    lbHeap_80431FA0.heap_array[i].id = -1;
                }
                else {
                    lbMemory_80014EEC(lbHeap_80431FA0.heap_array[i].handle);
                    lbHeap_80431FA0.heap_array[i].handle = (Handle*)-1;
                }
            }
        }
    }

    arena_lo = lbHeap_80431FA0.arena_lo;
    arena_hi = lbHeap_80431FA0.arena_hi;
    aram_lo = (u32*)lbHeap_80431FA0.aram_lo;
    aram_hi = (u32*)lbHeap_80431FA0.aram_hi;

    /// @todo this loop isnt entirely right, its purpose is to calculate where
    // the main heap can be allocated. This currently checks heaps 2 and 3, then 2 and 1...
    // checking 2 twice.
    for (i = 2; i > 0; i--) {
        if (lbHeap_80431FA0.heap_array[i].transient == 0) {
            if (lbHeap_80431FA0.heap_array[i].type != 3) {
                switch (lbHeap_80431FA0.heap_array[i].type) {
                    case 1:
                        temp_r0 = lbHeap_80431FA0.heap_array[i].start + lbHeap_80431FA0.heap_array[i].size;
                        if (arena_lo < (u32*)temp_r0) {
                            arena_lo = (u32*)temp_r0;
                        }
                        break;

                    case 2:
                        if (arena_hi > (u32*)lbHeap_80431FA0.heap_array[i].start) {
                            arena_hi = (u32*)lbHeap_80431FA0.heap_array[i].start;
                        }
                        break;

                    case 4:
                        temp_r0 = lbHeap_80431FA0.heap_array[i].start + lbHeap_80431FA0.heap_array[i].size;
                        if (aram_lo < (u32*)temp_r0) {
                            aram_lo = (u32*)temp_r0;
                        }
                        break;
                }
            }
        }

        if (lbHeap_80431FA0.heap_array[i+1].transient == 0) {
            if (lbHeap_80431FA0.heap_array[i+1].type != 3) {
                switch (lbHeap_80431FA0.heap_array[i+1].type) {
                    case 1:
                        temp_r0 = lbHeap_80431FA0.heap_array[i+1].start + lbHeap_80431FA0.heap_array[i+1].size;
                        if (arena_lo < (u32*)temp_r0) {
                            arena_lo = (u32*)temp_r0;
                        }
                        break;

                    case 2:
                        if (arena_hi > (u32*)lbHeap_80431FA0.heap_array[i+1].start) {
                            arena_hi = (u32*)lbHeap_80431FA0.heap_array[i+1].start;
                        }
                        break;

                    case 4:
                        temp_r0 = lbHeap_80431FA0.heap_array[i+1].start + lbHeap_80431FA0.heap_array[i+1].size;
                        if (aram_lo < (u32*)temp_r0) {
                            aram_lo = (u32*)temp_r0;
                        }
                        break;
                }
            }
        }
    }

    lbHeap_80431FA0.heap_array[0].id = HSD_CreateMainHeap(arena_lo, arena_hi);
    lbHeap_80431FA0.heap_array[0].start = *arena_lo;
    lbHeap_80431FA0.heap_array[0].size = *arena_hi - *arena_lo;
    lbHeap_80431FA0.heap_array[0].status = 0;
    lbHeap_80431FA0.heap_array[0].type = 0;

    lbMemory_800155A4();

    lbHeap_80431FA0.heap_array[1].handle = lbMemory_800154D4(aram_lo, aram_hi);
    lbHeap_80431FA0.heap_array[1].start = *aram_lo;
    lbHeap_80431FA0.heap_array[1].size = *aram_hi - *aram_lo;
    lbHeap_80431FA0.heap_array[1].status = 0;
    lbHeap_80431FA0.heap_array[1].type = 3;

    for (i = 2; i < 6; i++) {
        if (lbHeap_80431FA0.heap_array[i].transient == 0) {
            if (lbHeap_80431FA0.heap_array[i].status == 1) {
                if (lbHeap_80431FA0.heap_array[i].type == 0) {
                    lbHeap_80431FA0.heap_array[i].id = OSCreateHeap(
                        (void*) lbHeap_80431FA0.heap_array[i].start,
                        (void*) (lbHeap_80431FA0.heap_array[i].start +
                                 lbHeap_80431FA0.heap_array[i].size));
                }
                else {
                    lbHeap_80431FA0.heap_array[i].handle = lbMemory_80014E24(
                        (void*) lbHeap_80431FA0.heap_array[i].start,
                        (void*) (lbHeap_80431FA0.heap_array[i].start +
                            lbHeap_80431FA0.heap_array[i].size));
                }
                lbHeap_80431FA0.heap_array[i].status = 0;
            }
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
        OSReport(" / %5d KB\n", p->size / 1024);
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
    int i;

    HSD_GetNextArena(&lbHeap_80431FA0.arena_lo, &lbHeap_80431FA0.arena_hi);
    lbMemory_800154BC(&lbHeap_80431FA0.aram_lo, &lbHeap_80431FA0.aram_hi);

    for (i = 0; i < 6; i++) {
        lbHeap_80431FA0.heap_array[i].id = -1;
        lbHeap_80431FA0.heap_array[i].handle = (Handle*) -1;
        lbHeap_80431FA0.heap_array[i].start = 0;
        lbHeap_80431FA0.heap_array[i].size = 0;
        lbHeap_80431FA0.heap_array[i].type = 1;
        lbHeap_80431FA0.heap_array[i].transient = 1;
        lbHeap_80431FA0.heap_array[i].status = 1;
    }

    i = 0;
    while ((curr_idx = lbHeap_803BA380[i].idx) != 6) {
        curr_heap = &lbHeap_80431FA0.heap_array[curr_idx];

        curr_heap->type = lbHeap_803BA380[i].type;
        curr_heap->size = lbHeap_803BA380[i].size;
        prev_idx = lbHeap_803BA380[i].prev_idx;
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
        i++;
    }
}
