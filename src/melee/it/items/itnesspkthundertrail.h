#ifndef GALE01_2AC43C
#define GALE01_2AC43C

#include "it/forward.h"

#include "it/items/types.h"

/* 2AC43C */ Item_GObj* it_802AC43C(Fighter_GObj* gobj, Item_GObj* ball,
                                    Vec3* pos, s32 trail_idx, s32 arg4,
                                    f32 facing_dir);
/* 3F6C18 */ extern ItemKind it_803F6C18[];
/* 2AC58C */ void it_802AC58C(Item_GObj* gobj);
/* 2AC5D8 */ void it_802AC5D8(Item_GObj* gobj);
/* 2AC604 */ void it_802AC604(Item_GObj* gobj);
/* 2AC62C */ bool itNesspkthundertrail_UnkMotion0_Anim(Item_GObj* gobj);
/* 2AC6B0 */ void itNesspkthundertrail_UnkMotion0_Phys(Item_GObj* gobj);
/* 2AC8A0 */ bool itNesspkthundertrail_UnkMotion0_Coll(Item_GObj* gobj);
/* 3F6C08 */ extern ItemStateTable it_803F6C08[];

#endif
