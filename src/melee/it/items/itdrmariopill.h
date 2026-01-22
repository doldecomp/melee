#ifndef GALE01_2C0510
#define GALE01_2C0510

#include <platform.h>

#include "ft/forward.h"
#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C0510 */ void itDrMarioPill_Spawn(Item_GObj*, Vec3*, s32, ItemKind, f32);
/* 2C0850 */ Item_GObj* itDrMarioPill_Appeal_Spawn(Item_GObj*, Vec3*, s32,
                                                   ItemKind, f32);
/* 2C0B5C */ void itDrMarioPill_802C0B5C(Item_GObj*);
/* 2C09C4 */ Item_GObj* itDrMarioPill_802C09C4(Fighter_GObj*, Vec3*, s32,
                                               ItemKind, s32, Fighter_Part,
                                               f32);
/* 2C0DBC */ void itDrMarioPill_802C0DBC(Item_GObj*);
/* 2C0DF8 */ void itDrMarioPill_802C0DF8(Item_GObj*);
/* 2C1180 */ void itDrMarioPill_802C1180(Item_GObj*, enum_t);
/* 2C11E0 */ void itDrMarioPill_PickedUp(Item_GObj*);
/* 2C1384 */ bool itDrMarioPill_DmgDealt(Item_GObj*);
/* 2C13CC */ bool itDrMarioPill_Reflected(Item_GObj*);
/* 2C1400 */ bool itDrMarioPill_Clanked(Item_GObj*);
/* 2C145C */ bool itDrMarioPill_HitShield(Item_GObj*);
/* 2C14B8 */ bool itDrMarioPill_Absorbed(Item_GObj*);
/* 2C1514 */ bool itDrMarioPill_ShieldBounced(Item_GObj*);
/* 2C1570 */ void itDrMarioPill_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F75D0 */ extern ItemStateTable it_803F75D0[];

#endif
