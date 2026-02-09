#include "leak.h"

#include <dolphin/os.h>

#define HEAP_MAGIC 0x01234567

typedef struct HSD_LeakChecker {
    u32* table;      /* 0x00 */
    u32 x04;         /* 0x04 */
    u32 used;        /* 0x08 */
    u32 capacity;    /* 0x0C */
    u32 x10;         /* 0x10 */
    u32 x14;         /* 0x14 */
    u32 peak;        /* 0x18 */
    u32 x1C;         /* 0x1C */
    char str_now_registering[0x108 - 0x20]; /* 0x20 */
    char str_not_init[0x12C - 0x108]; /* 0x108 */
    char str_begin[0x14C - 0x12C]; /* 0x12C */
    char str_numreg[0x17C - 0x14C]; /* 0x14C */
    char str_leak_detected[0x1A8 - 0x17C]; /* 0x17C */
    char str_leak_destroyed[0x1D0 - 0x1A8]; /* 0x1A8 */
    char str_num_leaked[0x1F0 - 0x1D0]; /* 0x1D0 */
    char str_no_leak[0x208 - 0x1F0]; /* 0x1F0 */
} HSD_LeakChecker;

extern u32 lbCommand_803B9840[16];
extern HSD_LeakChecker HSD_Leak_80407B58;
static char HSD_Leak_804D6000[] = " ";
static char HSD_Leak_804D6004[] = "done.\n";

/* @TODO: Currently ~97.2% match - register allocation differences
 * remain: r28/r29 swap (scan_copy/cap_ptr), r21/r23 swap (heap_start_phys),
 * and r22/r27 swap (ofs/loop counter) in second half. */
int HSD_Leak_80387DF8(int indent)
{
    u32 val;
    HSD_LeakChecker* lc;
    u32* cap_ptr;
    u32* scan;
    u32 heap_start_align;
    int leak_count;
    u32 i;
    u32 j;
    u32 ofs;
    u32* heap_start_phys;

    scan = (u32*) lbCommand_803B9840;
    lc = &HSD_Leak_80407B58;

    heap_start_phys = (u32*) ((u32) OSGetConsoleSimulatedMemSize() + 0x80000000);
    heap_start_align = ((u32) scan + 32) & 0x0FFFFFE0;
    val = OSGetPhysicalMemSize();

    leak_count = 0;

    if (lc->table == NULL) {
        for (i = 0; i < (u32) indent; i++) {
            OSReport(HSD_Leak_804D6000);
        }
        OSReport(lc->str_not_init);
        return 0;
    }

    for (i = 0; i < (u32) indent; i++) {
        OSReport(HSD_Leak_804D6000);
    }
    OSReport(lc->str_begin);

    for (j = 0; j < (u32)(indent + 2); j++) {
        OSReport(HSD_Leak_804D6000);
    }
    cap_ptr = &lc->capacity;
    OSReport(lc->str_numreg, lc->used, lc->capacity, lc->peak);

    /* Scan memory for heap references */
    {
        s32 ctr = (s32)(((u32) heap_start_phys + 3 - (u32) scan) >> 2);
        for (; scan < heap_start_phys; ctr--) {
            u32 word = *scan;
            if ((word & 3) == 0) {
                u32 top = word >> 28;
                if (top == 8 || top == 0xC) {
                    u32 phys_addr = word & 0x0FFFFFFF;
                    if (phys_addr >= heap_start_align &&
                        val > phys_addr)
                    {
                        u32 virt = phys_addr | 0x80000000;
                        u32* hdr = (u32*) (virt - 0x20);
                        if ((u32) (*hdr + 0xFEDD0000) == 0x4567) {
                            u32 reg_idx = hdr[1];
                            if ((u32)(reg_idx + 0x10000) != 0xFFFF &&
                                reg_idx < *cap_ptr)
                            {
                                u32* ep = (u32*) ((u32) lc->table +
                                                  (reg_idx << 2));
                                u32 entry = *ep;
                                if (hdr == (u32*) (entry & ~1u)) {
                                    *ep = entry | 1;
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
    val = (u32) lc->table;
    scan = (u32*) (val + (*cap_ptr << 2));
    ofs = 0;
    for (heap_start_align = 0; heap_start_align < *cap_ptr;
         heap_start_align++)
    {
        u32* ep = (u32*) ((u32) lc->table + ofs);
        heap_start_phys = (u32*) *ep;
        if ((u32) heap_start_phys & 1) {
            *ep = (u32) heap_start_phys & ~1u;
        } else if ((u32*) val <= heap_start_phys &&
                   heap_start_phys < scan)
        {
        } else if (heap_start_phys != NULL) {
            u32* block = (u32*) heap_start_phys;
            if ((u32)(block[0] + 0xFEDD0000) == 0x4567) {
                u32 reg_idx = block[1];
                if ((u32)(reg_idx + 0x10000) != 0xFFFF &&
                    reg_idx < *cap_ptr)
                {
                    if ((u32) heap_start_phys ==
                        *(u32*)((u32)lc->table + (reg_idx << 2)))
                    {
                        for (j = 0; j < i; j++) {
                            OSReport(HSD_Leak_804D6000);
                        }
                        OSReport(lc->str_leak_detected,
                                 (u32*)((u32) heap_start_phys + 0x20),
                                 block[2], block[3]);
                        goto next_leak;
                    }
                }
            }
            for (j = 0; j < i; j++) {
                OSReport(HSD_Leak_804D6000);
            }
            OSReport(lc->str_leak_destroyed,
                     (u32*)((u32) heap_start_phys + 0x20));
next_leak:
            leak_count++;
        }
        ofs += 4;
    }

    if (leak_count > 0) {
        for (j = 0; j < (u32)(indent + 2); j++) {
            OSReport(HSD_Leak_804D6000);
        }
        OSReport(lc->str_num_leaked, leak_count);
    } else {
        for (j = 0; j < (u32)(indent + 2); j++) {
            OSReport(HSD_Leak_804D6000);
        }
        OSReport(lc->str_no_leak);
    }

    for (j = 0; j < (u32) indent; j++) {
        OSReport(HSD_Leak_804D6000);
    }
    OSReport(HSD_Leak_804D6004);

    return leak_count;
}
