#include "itunknown.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802CE710

void it_802CE7CC(void) {}

void it_802CE7D0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #itUnknown_UnkMotion0_Anim

/// #itUnknown_UnkMotion0_Phys

bool itUnknown_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CE8D0

/// #itUnknown_UnkMotion1_Anim

void itUnknown_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itUnknown_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CEC24

bool itUnknown_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itUnknown_UnkMotion2_Phys(Item_GObj* gobj) {}

bool itUnknown_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802CED54

/// #it_2725_Logic38_Spawned

void it_2725_Logic38_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802CF0D4

bool it_802CF120(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (--ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    return false;
}

/// #it_802CF154

bool it_802CF3D8(Item_GObj* gobj)
{
    return false;
}
