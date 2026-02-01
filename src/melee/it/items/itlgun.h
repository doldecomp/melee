#ifndef GALE01_28E738
#define GALE01_28E738

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 28E738 */ void itLGun_Logic16_Spawned(Item_GObj*);
/* 28E904 */ void itLGun_Logic16_PickedUp(Item_GObj*);
/* 28E9B8 */ void itLGun_Logic16_Dropped(Item_GObj*);
/* 28E9E0 */ void itLGun_Logic16_Thrown(Item_GObj*);
/* 28EA54 */ bool itLGun_Logic16_DmgDealt(Item_GObj*);
/* 28EA78 */ bool itLGun_Logic16_Clanked(Item_GObj*);
/* 28EA9C */ bool itLGun_Logic16_HitShield(Item_GObj*);
/* 28EAC0 */ bool itLGun_Logic16_Reflected(Item_GObj*);
/* 28EAE0 */ bool itLGun_Logic16_ShieldBounced(Item_GObj*);
/* 28EB00 */ void itLGun_Logic16_EnteredAir(Item_GObj*);
/* 28EB68 */ void itLGun_Logic16_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F5CC8 */ extern ItemStateTable it_803F5CC8[];

void it_8028E938(Item_GObj*);
void it_8028E774(Item_GObj*, Vec3*);
void it_8028E79C(Item_GObj* gobj, Vec3* pos, f32 facing_dir);

#endif
