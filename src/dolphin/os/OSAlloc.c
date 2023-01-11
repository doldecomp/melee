#include "Runtime/platform.h"
#include <dolphin/os/OSAlloc.h>

#include <dolphin/os/os.h>

static Heap* HeapArray;
static int NumHeaps;
static void* ArenaStart;
static void* ArenaEnd;
volatile OSHeapHandle __OSCurrHeap = -1;

#define InRange(addr, start, end)                                              \
    ((u8*) (start) <= (u8*) (addr) && (u8*) (addr) < (u8*) (end))
#define OFFSET(addr, align) (((uintptr_t) (addr) & ((align) -1)))

#define ALIGNMENT (32)
#define MINOBJSIZE (64)

/* inserts 'cell' before 'neighbor' and returns 'cell' */
void* DLAddFront(HeapCell* neighbor, HeapCell* cell)
{
    cell->next = neighbor;
    cell->prev = NULL;
    if (neighbor != NULL)
        neighbor->prev = cell;
    return cell;
}

/* removes 'cell' from 'list' and returns 'list' */
HeapCell* DLExtract(HeapCell* list, HeapCell* cell)
{
    if (cell->next != NULL)
        cell->next->prev = cell->prev;
    if (cell->prev == NULL)
        list = cell->next;
    else
        cell->prev->next = cell->next;
    return list;
}

HeapCell* DLInsert(HeapCell* list, HeapCell* cell,
                   void* unused /* needed to match OSFreeToHeap */)
{
    HeapCell* before = NULL;
    HeapCell* after = list;

    while (after != NULL) {
        if (cell <= after)
            break;
        before = after;
        after = after->next;
    }
    cell->next = after;
    cell->prev = before;
    if (after != NULL) {
        after->prev = cell;
        if ((u8*) cell + cell->size == (u8*) after) {
            cell->size += after->size;
            after = after->next;
            cell->next = after;
            if (after != NULL)
                after->prev = cell;
        }
    }
    if (before != NULL) {
        before->next = cell;
        if ((u8*) before + before->size == (u8*) cell) {
            before->size += cell->size;
            before->next = after;
            if (after != NULL)
                after->prev = before;
        }
        return list;
    }
    return cell;
}

any_t OSAllocFromHeap(OSHeapHandle heap, size_t size)
{
    Heap* hd = &HeapArray[heap];
    size_t sizeAligned = OSRoundUp32B(ALIGNMENT + size);
    HeapCell* cell;
    size_t leftoverSpace;

    // find first cell with enough capacity
    for (cell = hd->free; cell != NULL; cell = cell->next)
        if ((signed) sizeAligned <= (signed) cell->size)
            break;

    if (cell == NULL)
        return NULL;

    leftoverSpace = cell->size - sizeAligned;
    if (leftoverSpace < MINOBJSIZE) {
        // remove this cell from the free list
        hd->free = DLExtract(hd->free, cell);
    } else {
        // remove this cell from the free list and make a new cell out of the
        // remaining space
        HeapCell* newcell = (any_t) ((u8*) cell + sizeAligned);
        cell->size = sizeAligned;
        newcell->size = leftoverSpace;
        newcell->prev = cell->prev;
        newcell->next = cell->next;
        if (newcell->next != NULL)
            newcell->next->prev = newcell;
        if (newcell->prev != NULL)
            newcell->prev->next = newcell;
        else
            hd->free = newcell;
    }

    // add the cell to the beginning of the allocated list
    hd->allocated = DLAddFront(hd->allocated, cell);

    return (u8*) cell + ALIGNMENT;
}

void OSFreeToHeap(OSHeapHandle heap, any_t ptr)
{
    HeapCell* cell = (any_t) ((u8*) ptr - ALIGNMENT);
    Heap* hd = &HeapArray[heap];
    HeapCell* list = hd->allocated;

    // remove cell from the allocated list
    // hd->allocated = DLExtract(hd->allocated, cell);
    if (cell->next != NULL)
        cell->next->prev = cell->prev;
    if (cell->prev == NULL)
        list = cell->next;
    else
        cell->prev->next = cell->next;

    hd->allocated = list;
    hd->free = DLInsert(hd->free, cell, list);
}

OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap)
{
    OSHeapHandle old = __OSCurrHeap;

    __OSCurrHeap = heap;
    return old;
}

void* OSInitAlloc(void* arenaStart, void* arenaEnd, int maxHeaps)
{
    u32 totalSize = maxHeaps * sizeof(Heap);
    int i;

    HeapArray = arenaStart;
    NumHeaps = maxHeaps;

    for (i = 0; i < NumHeaps; i++) {
        Heap* heap = &HeapArray[i];

        heap->size = -1;
        heap->free = heap->allocated = NULL;
    }

    __OSCurrHeap = -1;

    arenaStart = (u8*) HeapArray + totalSize;
    arenaStart = (void*) OSRoundUp32B(arenaStart);

    ArenaStart = arenaStart;
    ArenaEnd = (void*) OSRoundDown32B(arenaEnd);

    return arenaStart;
}

OSHeapHandle OSCreateHeap(void* start, void* end)
{
    int i;
    HeapCell* cell = (void*) OSRoundUp32B(start);

    end = (void*) OSRoundDown32B(end);
    for (i = 0; i < NumHeaps; i++) {
        Heap* hd = &HeapArray[i];

        if (hd->size < 0) {
            hd->size = (u8*) end - (u8*) cell;
            cell->prev = NULL;
            cell->next = NULL;
            cell->size = hd->size;
            hd->free = cell;
            hd->allocated = NULL;
            return i;
        }
    }
    return -1;
}

void OSDestroyHeap(size_t idx)
{
    *(s32*) &HeapArray[idx] = -1;
}

size_t OSCheckHeap(OSHeapHandle heap)
{
    Heap* hd;
    HeapCell* cell;
    int total = 0;
    int totalFree = 0;

    // clang-format off
#define CHECK(line, condition)                                      \
    if (!(condition)) {                                             \
        OSReport("OSCheckHeap: Failed " #condition " in %d", line); \
        return -1;                                                  \
    }

    CHECK(893, HeapArray)
    CHECK(894, 0 <= heap && heap < NumHeaps)
    hd = &HeapArray[heap];
    CHECK(897, 0 <= hd->size)
    CHECK(899, hd->allocated == NULL || hd->allocated->prev == NULL)

    for (cell = hd->allocated; cell != NULL; cell = cell->next) {
        CHECK(902, InRange(cell, ArenaStart, ArenaEnd))
        CHECK(903, OFFSET(cell, ALIGNMENT) == 0)
        CHECK(904, cell->next == NULL || cell->next->prev == cell)
        CHECK(905, MINOBJSIZE <= cell->size)
        CHECK(906, OFFSET(cell->size, ALIGNMENT) == 0)
        total += cell->size;
        CHECK(909, 0 < total && total <= hd->size)
    }

    CHECK(917, hd->free == NULL || hd->free->prev == NULL)
    for (cell = hd->free; cell != NULL; cell = cell->next) {
        CHECK(920, InRange(cell, ArenaStart, ArenaEnd))
        CHECK(921, OFFSET(cell, ALIGNMENT) == 0)
        CHECK(922, cell->next == NULL || cell->next->prev == cell)
        CHECK(923, MINOBJSIZE <= cell->size)
        CHECK(924, OFFSET(cell->size, ALIGNMENT) == 0)
        CHECK(925, cell->next == NULL || (char*) cell + cell->size < (char*) cell->next)
        total += cell->size;
        totalFree += cell->size - 32;
        CHECK(929, 0 < total && total <= hd->size)
    }

    CHECK(936, total == hd->size);

#undef CHECK
    // clang-format on

    return totalFree;
}

#pragma push
#pragma force_active on
static char string__nOSDumpHeap__d___n[] = "\nOSDumpHeap(%d):\n";
static char string_________Inactive_n[] = "--------Inactive\n";
static char string_addr_tsize_t_tend_tprev_tnext_n[] =
    "addr\tsize\t\tend\tprev\tnext\n";
static char string_________Allocated_n[] = "--------Allocated\n";
static char string__x_t_d_t_x_t_x_t_x_n[] = "%x\t%d\t%x\t%x\t%x\n";
static char string_________Free_n[] = "--------Free\n";
#pragma pop
