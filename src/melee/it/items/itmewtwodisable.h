#ifndef GALE01_2C49E0
#define GALE01_2C49E0

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 2C49E0 */ void itMewtwoDisable_Logic67_Destroy(Item_GObj*);
/* 2C4A00 */ void itMewtwoDisable_Logic67_Destroyed(Item_GObj*);
/* 2C4A40 */ Item_GObj*
itMewtwoDisable_Logic67_SpawnMewtwoDisable(Fighter_GObj*, Vec3*, float);
/* 2C4B38 */ void it_802C4B38(Item_GObj* item_gobj);
/* 2C4BB8 */ void it_802C4BB8(Item_GObj* item_gobj);
/* 2C4C08 */ bool itMewtwodisable_UnkMotion0_Anim(Item_GObj* gobj);
/* 2C4C3C */ void itMewtwodisable_UnkMotion0_Phys(Item_GObj* gobj);
/* 2C4C40 */ bool itMewtwodisable_UnkMotion0_Coll(Item_GObj* gobj);
/* 2C4C90 */ bool itMewtwoDisable_Logic67_DmgDealt(Item_GObj*);
/* 2C4C98 */ bool itMewtwoDisable_Logic67_Reflected(Item_GObj*);
/* 2C4CB8 */ bool itMewtwoDisable_Logic67_Clanked(Item_GObj*);
/* 2C4CC0 */ bool itMewtwoDisable_Logic67_HitShield(Item_GObj*);
/* 2C4CC8 */ bool itMewtwoDisable_Logic67_Absorbed(Item_GObj*);
/* 2C4CD0 */ bool itMewtwoDisable_Logic67_ShieldBounced(Item_GObj*);
/* 2C4CD8 */ void itMewtwoDisable_Logic67_EvtUnk(Item_GObj*, Fighter_GObj*);
/* 3F7750 */ extern ItemStateTable it_803F7750[];

#endif
