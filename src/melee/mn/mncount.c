#include "mncount.h"

#include <melee/gm/gmmain_lib.h>

s32 GetFighterTotalKOs(s32 slot);

s32 mnCount_802502CC(s32 idx) {
    void* data = GetPersistentFighterData(idx);
    return *(s32*)((u8*)data + 0x54);
}

s32 fn_802502F0(u8 arg) {
    return GetFighterTotalKOs(arg);
}

s32 GetFighterTotalFalls(s32 slot);

s32 fn_80250314(u8 arg) {
    return GetFighterTotalFalls(arg);
}

u16 fn_80250338(u8 arg) {
    void* data = GetPersistentFighterData(arg);
    return *(u16*)((u8*)data + 0x34);
}

u16 fn_8025069C(u8 arg) {
    void* data = GetPersistentFighterData(arg);
    return *(u16*)((u8*)data + 0x50);
}

u16 fn_802506C0(u8 arg) {
    void* data = GetPersistentFighterData(arg);
    return *(u16*)((u8*)data + 0x52);
}

s32 fn_802506E4(u8 arg) {
    void* data = GetPersistentFighterData(arg);
    return *(s32*)((u8*)data + 0x40);
}

s32 fn_80250708(u8 arg) {
    void* data = GetPersistentFighterData(arg);
    return *(s32*)((u8*)data + 0x44);
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