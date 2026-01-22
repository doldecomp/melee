#ifndef GALE01_2C2144
#define GALE01_2C2144

#include <platform.h>

#include "it/forward.h"

#include "it/items/types.h"

/* 2C2144 */ Item_GObj* itClimbersBlizzard_Spawn(Item_GObj*, Vec3*, f32);
/* 2C2248 */ void itClimbersBlizzard_802C2248(Item_GObj*);
/* 2C2358 */ void itClimbersBlizzard_802C2358(Item_GObj* gobj);
/* 2C2424 */ bool itClimbersBlizzard_DmgDealt(Item_GObj*);
/* 2C242C */ bool itClimbersBlizzard_Reflected(Item_GObj*);
/* 2C244C */ bool itClimbersBlizzard_Clanked(Item_GObj*);
/* 2C2454 */ bool itClimbersBlizzard_HitShield(Item_GObj*);
/* 2C245C */ bool itClimbersBlizzard_Absorbed(Item_GObj*);
/* 2C2464 */ bool itClimbersBlizzard_ShieldBounced(Item_GObj*);
/* 2C246C */ void itClimbersBlizzard_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F76A8 */ extern ItemStateTable it_803F76A8[];

#endif
