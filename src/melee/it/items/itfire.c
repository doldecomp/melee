#include "itfire.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_2725_Logic6_Spawned

void it_802CC740(void) {}

void it_2725_Logic6_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itFire_UnkMotion1_Anim

void itFire_UnkMotion1_Phys(Item_GObj* gobj) {}

/// #itFire_UnkMotion1_Coll

void it_802CC7D4(void) {}

/// #it_802CC7D8

/// #itFire_UnkMotion2_Anim

void itFire_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itFireAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.y += attrs->xC;
}

bool itFire_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CC944

bool itFire_UnkMotion0_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itFire_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itFire_UnkMotion0_Coll(Item_GObj* gobj)
{
    return it_8027A118(gobj, (void (*)(HSD_GObj*)) it_802CC740);
}
