#include "it/forward.h"

#include "itseakneedlethrown.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802AFD8C

/// #it_802AFEA8

void it_802AFEF8(Item_GObj* gobj)
{
    GET_ITEM(gobj)->owner = NULL;
}

/// #it_802AFF08

/// #it_802B00F4

/// #itSeakneedlethrown_UnkMotion0_Anim

/// #itSeakneedlethrown_UnkMotion1_Anim

/// #itSeakneedlethrown_UnkMotion2_Anim

/// #itSeakneedlethrown_UnkMotion3_Anim

/// #itSeakneedlethrown_UnkMotion4_Anim

void itSeakneedlethrown_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itSeakneedlethrown_UnkMotion1_Phys

void itSeakneedlethrown_UnkMotion2_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itSeakneedlethrown_UnkMotion4_Phys

/// #itSeakneedlethrown_UnkMotion0_Coll

/// #itSeakneedlethrown_UnkMotion1_Coll

/// #itSeakneedlethrown_UnkMotion2_Coll

bool itSeakneedlethrown_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #itSeakneedlethrown_UnkMotion4_Coll

/// #it_802B0D84

/// #it_802B0F34

/// #it_802B10E4

/// #it_802B1294

/// #it_802B14DC

/// #it_802B16E4

void it_802B1890(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
