#include "mncount.h"

#include <melee/gm/gmmain_lib.h>

s32 mnCount_802502CC(s32 idx) {
    void* data = GetPersistentFighterData(idx);
    return *(s32*)((u8*)data + 0x54);
}

void mnCount_802517E0(void* data) {
    s32 i;

    *(u8*)data = 0;
    *(s32*)((u8*)data + 4) = 10;

    for (i = 0; i < 10; i++) {
        *(s32*)((u8*)data + 8 + i * 4) = 0;
        *(s32*)((u8*)data + 0x30 + i * 4) = 0;
    }
}