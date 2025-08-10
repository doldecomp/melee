#ifndef ITPEACHEXPLODE_H
#define ITPEACHEXPLODE_H

#include <melee/it/forward.h>
#include <melee/it/items/types.h>

extern struct ItemStateTable it_803F7488[];

/* 2BD158 */ Item_GObj* it_802BD158(Item_GObj*, Vec3* pos, bool, float dir);
/* 2BD240 */ bool it_802BD240(Item_GObj*);
/* 2BD248 */ void it_802BD248(Item_GObj*, Item_GObj* owner, bool);
/* 2BD2EC */ bool itPeachexplode_UnkMotion1_Anim(Item_GObj*);
/* 2BD30C */ void it_802BD30C(Item_GObj*, Item_GObj* ref_gobj);

#endif
