#ifndef GALE01_288C88
#define GALE01_288C88

#include "it/forward.h"

#include "it/items/types.h"

#include <dolphin/mtx.h>

/* 288C88 */ Item_GObj* it_80288C88(HSD_GObj* arg_gobj, Vec3* pos, Vec3* vel,
                                    float dir);
/* 288D98 */ void itEgg_Logic3_Spawned(Item_GObj*);
/* 288F88 */ void itEgg_Logic3_PickedUp(Item_GObj*);
/* 288FBC */ void itEgg_Logic3_Dropped(Item_GObj*);
/* 288FDC */ void itEgg_Logic3_Thrown(Item_GObj*);
/* 289218 */ bool itEgg_Logic3_DmgDealt(Item_GObj*);
/* 2893D4 */ bool itEgg_Logic3_Clanked(Item_GObj*);
/* 289470 */ bool itEgg_Logic3_HitShield(Item_GObj*);
/* 28950C */ bool itEgg_Logic3_Reflected(Item_GObj*);
/* 2895A8 */ bool itEgg_Logic3_DmgReceived(Item_GObj*);
/* 289644 */ void itEgg_Logic3_EnteredAir(Item_GObj*);
/* 2896AC */ void itEgg_Logic3_EvtUnk(Item_GObj*, Item_GObj*);
/* 3F5988 */ extern ItemStateTable it_803F5988[];

#endif
