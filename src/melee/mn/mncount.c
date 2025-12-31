#include "mncount.h"

#include <melee/gm/gmmain_lib.h>

s32 mnCount_802502CC(s32 idx) {
    void* data = GetPersistentFighterData(idx);
    return *(s32*)((u8*)data + 0x54);
}