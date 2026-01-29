#ifndef GALE01_2C68F8
#define GALE01_2C68F8

#include "it/forward.h"

#include "it/items/types.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 2C68F8 */ HSD_GObj* itGamewatchFire_Spawn(HSD_GObj*, Vec3*, Fighter_Part,
                                             float);
/* 2C69FC */ void itGamewatchFire_Destroyed(Item_GObj*);
/* 2C6A2C */ void itGamewatchFire_802C6A2C(Item_GObj*);
/* 2C6A78 */ void itGamewatchFire_802C6A78(Item_GObj*);
/* 2C6A98 */ void itGamewatchFire_802C6A98(Item_GObj*);
/* 2C6AB8 */ void itGamewatchFire_PickedUp(Item_GObj*);
/* 2C6C18 */ void itGamewatchFire_EvtUnk(Item_GObj*, Item_GObj*);
/*        */ void ftGw_AttackS4_ItemTorchSetFlag(HSD_GObj*);
/*        */ bool ftGw_AttackS4_ItemCheckTorchRemove(HSD_GObj*);
/* 3F78E8 */ extern ItemStateTable it_803F78E8[];

#endif
