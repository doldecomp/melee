#include "lbmemory.h"

#include <dolphin/os/OSInterrupt.h>
#include <baselib/archive.h>
#include <baselib/initialize.h>
#include <baselib/memory.h>

int lbHeap_80431FA0[46];

void lbHeap_800158D0(int arg0, int arg1)
{
    lbHeap_80431FA0[arg0 * 7 + 9] = arg1;
}

int lbHeap_800158E8(int arg0)
{
    return lbHeap_80431FA0[arg0 * 7 + 9];
}

HSD_Archive* lbHeap_80015BD0(s32 arg0, s32 arg1)
{
    HSD_Archive* var_r31;
    s32 temp_r29;
    s32 temp_r30;
    s32* temp_r31;
    s32* temp_r4;

    temp_r4 = ((s32*) lbHeap_80431FA0) + (arg0 * 0x1C);
    temp_r31 = temp_r4 + 0x10;
    temp_r30 = OSDisableInterrupts();
    if (*(temp_r4 + 0x28) == 0) {
        if (*(temp_r31 + 0x10) == 0) {
            temp_r29 = HSD_GetHeap();
            HSD_SetHeap(*temp_r31);
            var_r31 = HSD_MemAlloc(arg1);
            HSD_SetHeap(temp_r29);
        } else {
            var_r31 = lbMemory_80014FC8(*(temp_r31 + 4), arg1);
            if (*(temp_r31 + 0x10) == 3) {
                var_r31 = (HSD_Archive*) var_r31->header.data_size;
            }
        }
    } else {
        var_r31 = NULL;
    }
    OSRestoreInterrupts(temp_r30);
    return var_r31;
}
