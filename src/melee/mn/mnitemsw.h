#ifndef MELEE_MN_ITEMSW_H
#define MELEE_MN_ITEMSW_H

#include <platform.h>

#include <sysdolphin/baselib/forward.h>

typedef struct {
    char pad[0x78];
    f32 vals[];
} ItemSwTable;

/* 233A98 */ s32 mnItemSw_80233A98(s32 arg0);
/* 23405C */ void* mnItemSw_8023405C(void* arg0, u8 idx);
/* 2358C0 */ void mnItemSw_802358C0(void);

/* 3ED340 */ extern ItemSwTable mnItemSw_803ED340;
/* 4D6BEC */ extern u8 mnItemSw_804D6BEC;

#endif
