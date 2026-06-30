#include "leak.h"

#include <dolphin/os.h>

#define HEAP_MAGIC 0x01234567

typedef struct HSD_LeakChecker {
    u32* table;   /* 0x00 */
    u32 x04;      /* 0x04 */
    u32 used;     /* 0x08 */
    u32 capacity; /* 0x0C */
    u32 x10;      /* 0x10 */
    u32 x14;      /* 0x14 */
    u32 peak;     /* 0x18 */
    s32 x1C;      /* 0x1C */
} HSD_LeakChecker;

/// @todo Cannot access melee/lb from here
/* 3B9840 */ extern u32 lbCommand_803B9840[16];

/* 407B58 */ HSD_LeakChecker HSD_Leak_80407B58 = {
    NULL, 0, 0, 0, 0, 0, 0, -1
};

/// @todo .data order hack
static void order_data(void)
{
    (void) "now registering suspecting memory ...\n";
    (void) "WARNING!!\n";
    (void) "Too many memory blocks are registerd to memory checker.\n";
    (void) "Please increase a capacity of checker.\n";
    (void) "Non-registered memory block is specified (%p).\n";
    (void) "leak unregister range %p %p\n";
}

/* @todo Currently ~98.4% match - register allocation differences
 * remain: r28/r29 swap (scan/cap_ptr) and loop/local register swaps
 * in the allocation table scan and report indentation loops. */
static inline u32* HSD_LeakGetCapacityPtr(HSD_LeakChecker* lc)
{
    return &lc->capacity;
}

static inline void HSD_LeakReportSpaces(u32 count)
{
    u32 i;

    for (i = 0; i < count; i++) {
        OSReport(" ");
    }
}

int HSD_Leak_80387DF8(int indent)
{
    u32 val;
    HSD_LeakChecker* lc;
    u32* scan;
    u32* heap_start_phys;
    u32* cap_ptr;
    u32 heap_start_align;
    int leak_count;
    u32 i;
    u32 j;
    u32 ofs;

    scan = (u32*) lbCommand_803B9840;
    lc = &HSD_Leak_80407B58;

    heap_start_phys =
        (u32*) ((u32) OSGetConsoleSimulatedMemSize() + 0x80000000);
    heap_start_align = ((u32) scan + 32) & 0x0FFFFFE0;
    val = OSGetPhysicalMemSize();

    leak_count = 0;

    if (lc->table == NULL) {
        HSD_LeakReportSpaces(indent);
        OSReport("Leak checker is not initialized.\n");
        return 0;
    }

    HSD_LeakReportSpaces(indent);
    OSReport("Begin memory leak check ...\n");

    HSD_LeakReportSpaces(indent + 2);
    cap_ptr = HSD_LeakGetCapacityPtr(lc);
    OSReport("number of registered ptr: %d / %d (peak %d)\n", lc->used,
             *cap_ptr, lc->peak);

    /* Scan memory for heap references */
    {
        s32 ctr = (s32) (((u32) heap_start_phys + 3 - (u32) scan) >> 2);
        for (; scan < heap_start_phys; ctr--) {
            u32 word = *scan;
            if ((word & 3) == 0) {
                u32 top = word >> 28;
                if (top == 8 || top == 0xC) {
                    if ((word & 0x0FFFFFFF) >= heap_start_align &&
                        val > (word & 0x0FFFFFFF))
                    {
                        u32* hdr = (u32*) ((word | 0x80000000) - 0x20);
                        if (*hdr == HEAP_MAGIC) {
                            u32 reg_idx = hdr[1];
                            if ((u32) (reg_idx + 0x10000) != 0xFFFF &&
                                reg_idx < *cap_ptr)
                            {
                                u32 entry = lc->table[reg_idx];
                                if (hdr == (u32*) (entry & ~1u)) {
                                    lc->table[reg_idx] = entry | 1;
                                }
                            }
                        }
                    }
                }
            }
            scan++;
        }
    }

    /* Check allocation table for leaks */
    i = indent;
    i += 2;
    scan = lc->table;
    val = (u32) (scan + *cap_ptr);
    heap_start_align = 0;
    for (ofs = 0; ofs < *cap_ptr; ofs++)
    {
        u32* ep = (u32*) ((u32) lc->table + heap_start_align);
        heap_start_phys = (u32*) *ep;
        if ((u32) heap_start_phys & 1) {
            *ep = (u32) heap_start_phys & ~1u;
        } else if (scan <= heap_start_phys && heap_start_phys < (u32*) val) {
        } else if (heap_start_phys != NULL) {
            u32* block = (u32*) heap_start_phys;
            if (block[0] == HEAP_MAGIC) {
                u32 reg_idx = block[1];
                if ((u32) (reg_idx + 0x10000) != 0xFFFF && reg_idx < *cap_ptr)
                {
                    if ((u32) heap_start_phys ==
                        *(u32*) ((u32) lc->table + (reg_idx << 2)))
                    {
                        for (j = 0; j < i; j++) {
                            OSReport(" ");
                        }
                        OSReport(
                            "leak detected (%p) nb_reg (%d) mark (%08x)\n",
                            (u32*) ((u32) heap_start_phys + 0x20), block[2],
                            block[3]);
                        goto next_leak;
                    }
                }
            }
            for (j = 0; j < i; j++) {
                OSReport(" ");
            }
            OSReport("leak detected (%p) [destroyed header]\n",
                     (u32*) ((u32) heap_start_phys + 0x20));
        next_leak:
            leak_count++;
        }
        heap_start_align += 4;
    }

    if (leak_count > 0) {
        for (j = 0; j < (u32) (indent + 2); j++) {
            OSReport(" ");
        }
        OSReport("number of leaked memory: %d.\n", leak_count);
    } else {
        for (j = 0; j < (u32) (indent + 2); j++) {
            OSReport(" ");
        }
        OSReport("leak is not detected.\n");
    }

    for (j = 0; j < (u32) indent; j++) {
        OSReport(" ");
    }
    OSReport("done.\n");

    return leak_count;
}
