#include "itseakneedleheld.h"

#include "it/it_26B1.h"
#include "it/item.h"

/// #it_802B18B0

/// #it_802B19AC

void itSeakNeedleHeld_Logic110_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #itSeakneedleheld_UnkMotion0_Anim

void itSeakneedleheld_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSeakneedleheld_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

void itSeakNeedleHeld_Logic110_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
