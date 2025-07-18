#include "lbheap.static.h"

#include <melee/lb/lbmemory.h>
#include <dolphin/os/OSInterrupt.h>
#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/initialize.h>
#include <baselib/memory.h>

struct {
    u32 unk0;
    u32 unk4;
    u32 unk8;
    u32 unkC;
} lbHeap_803BA380[5] = {
    { 2, 1, 6, 0x800 },
    { 3, 1, 2, 0x4F8800 },
    { 4, 2, 6, 0x64B400 },
    { 5, 4, 6, 0x96C800 },
    { 6, 0, 0, 0 },
};

void lbHeap_800158D0(int arg0, int arg1)
{
    lbHeap_80431FA0.unk_10[arg0].unk_24 = arg1;
}

int lbHeap_800158E8(int arg0)
{
    return lbHeap_80431FA0.unk_10[arg0].unk_24;
}

/// #lbHeap_80015900

int lbHeap_80015BB8(int arg0)
{
    return lbHeap_80431FA0.unk_10[arg0].status;
}

void* lbHeap_80015BD0(int arg0, int arg1)
{
    Handle* result;
    int enabled = OSDisableInterrupts();
    struct lbHeap_80431FA0_x10_t* p = &lbHeap_80431FA0.unk_10[arg0];

    if (p->status == 0) {
        if (p->unk_20 == 0) {
            int cur_heap = HSD_GetHeap();
            HSD_SetHeap(p->unk_10);
            result = HSD_MemAlloc(arg1);
            HSD_SetHeap(cur_heap);
        } else {
            result = lbMemory_80014FC8(p->unk_14, arg1);
            if (p->unk_20 == 3) {
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
    struct lbHeap_80431FA0_x10_t* p = &lbHeap_80431FA0.unk_10[arg0];

    if (p->status != 0) {
        __assert("lbheap.c", 0x143, "p->status == LbHeapStatus_Create");
    }
    if (p->unk_20 == 0) {
        int cur_heap = HSD_GetHeap();
        HSD_SetHeap(p->unk_10);
        HSD_Free(arg1);
        HSD_SetHeap(cur_heap);
    } else {
        lbMemory_800150F0(p->unk_14, arg1);
    }
    OSRestoreInterrupts(enabled);
}

int lbHeap_80015D6C(u32 heap0, UNK_T cb, u32 heap1)
{
    int enabled = OSDisableInterrupts();
    struct lbHeap_80431FA0_x10_t* p = &lbHeap_80431FA0.unk_10[heap0];
    int var_r30;

    if (heap0 <= 1) {
        var_r30 = 0;
    } else {
        var_r30 = lbMemory_8001529C(p->unk_14, cb, heap1);
    }
    OSRestoreInterrupts(enabled);
    return var_r30;
}

char* lbHeap_803BA448[] = {
    "     Hsd",
    "    ARAM",
    "     Seq",
    "    Stay",
    "    AllM",
    "    AllA",
};

void lbHeap_80015DF8(void)
{
    ssize_t bytes;
    struct lbHeap_80431FA0_x10_t* p;
    int i;
    int var_r25;

    OSReport("[lbHeap] -- Report --\n");

    for (i = 0; i < 6; i++) {
        OSReport("%s :", lbHeap_803BA448[i]);
        p = &lbHeap_80431FA0.unk_10[i];
        if (p->status == 0) {
            if (p->unk_20 == 0) {
                var_r25 = OSCheckHeap(p->unk_10);
            } else {
                var_r25 = lbMemory_80014F7C(p->unk_14);
            }
            OSReport(" %5d KB + ", (p->unk_1C - var_r25) / 1024);
            OSReport(" %5d KB( %8d)", var_r25 / 1024, var_r25);
        } else {
            OSReport("                         destroy");
        }
        OSReport(" / %5d KB\n", p->unk_1C / 1024);
    }

    bytes = (u32) lbHeap_80431FA0.unk_4 - (u32) lbHeap_80431FA0.unk_0;
    OSReport("MainRAM Total : %5d KB( %8d)\n", bytes / 1024, bytes);
    bytes = lbHeap_80431FA0.unk_C - lbHeap_80431FA0.unk_8;
    OSReport("   ARAM Total : %5d KB( %8d)\n", bytes / 1024, bytes);
}

void lbHeap_80015F3C(void)
{
    int temp_r0;
    int temp_r0_2;
    struct lbHeap_80431FA0_x10_t* temp_r5;
    struct lbHeap_80431FA0_x10_t* temp_r6;
    int i;

    HSD_GetNextArena(&lbHeap_80431FA0.unk_0, &lbHeap_80431FA0.unk_4);
    lbMemory_800154BC(&lbHeap_80431FA0.unk_8, &lbHeap_80431FA0.unk_C);

    for (i = 0; i < 6; i++) {
        lbHeap_80431FA0.unk_10[i].unk_10 = -1;
        lbHeap_80431FA0.unk_10[i].unk_14 = (Handle*) -1;
        lbHeap_80431FA0.unk_10[i].unk_18 = 0;
        lbHeap_80431FA0.unk_10[i].unk_1C = 0;
        lbHeap_80431FA0.unk_10[i].unk_20 = 1;
        lbHeap_80431FA0.unk_10[i].unk_24 = 1;
        lbHeap_80431FA0.unk_10[i].status = 1;
    }

    while ((temp_r0 = lbHeap_803BA380[i].unk0) != 6) {
        temp_r5 = &lbHeap_80431FA0.unk_10[temp_r0];

        temp_r5->unk_20 = lbHeap_803BA380[i].unk4;
        temp_r5->unk_1C = lbHeap_803BA380[i].unkC;
        temp_r0_2 = lbHeap_803BA380[i].unk8;
        if (temp_r0_2 == 6) {
            switch (temp_r5->unk_20) {
            case 3:
                break;
            case 1:
                temp_r5->unk_18 = (s32) lbHeap_80431FA0.unk_0;
                break;
            case 2:
                temp_r5->unk_18 = (u32) lbHeap_80431FA0.unk_4 - temp_r5->unk_1C;
                break;
            case 4:
                temp_r5->unk_18 = (s32) lbHeap_80431FA0.unk_8;
                break;
            }
        } else {
            temp_r6 = &lbHeap_80431FA0.unk_10[temp_r0_2];
            switch (temp_r5->unk_20) {
            case 3:
                break;
            case 1:
                temp_r5->unk_18 = temp_r6->unk_18 + temp_r6->unk_1C;
                break;
            case 2:
                temp_r5->unk_18 = temp_r6->unk_18 - temp_r5->unk_1C;
                break;
            case 4:
                temp_r5->unk_18 = temp_r6->unk_18 + temp_r6->unk_1C;
                break;
            }
        }
    }
}
