#ifndef _ITNESSPKFIREPILLAR_H_
#define _ITNESSPKFIREPILLAR_H_

#include "it/forward.h"
#include "it/items/types.h"

void itNesspkfirepillar_802AA494(HSD_GObj* parent1_gobj, HSD_GObj* parent2_gobj, Vec3* offset, f32 facing_dir);
void itNesspkfirepillar_802AA55C(Item_GObj* item_gobj);
bool itNesspkfirepillar_UnkMotion0_Anim(Item_GObj* item_gobj);
void itNesspkfirepillar_UnkMotion0_Phys(Item_GObj* item_gobj);
bool itNesspkfirepillar_UnkMotion0_Coll(Item_GObj* item_gobj);
bool itNesspkfirepillar_Logic24_DmgReceived(Item_GObj* item_gobj);
void itNesspkfirepillar_Logic24_EvtUnk(Item_GObj* item_gobj, HSD_GObj* parent_gobj);

extern ItemStateTable it_803F6B60[1];

#endif
