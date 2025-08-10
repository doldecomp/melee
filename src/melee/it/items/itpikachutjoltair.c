#include <platform.h>
#include <placeholder.h>

#include "itpikachutjoltair.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2B45E8 */ static bool itPikachutjoltair_UnkMotion0_Coll(Item_GObj* gobj);

bool itPikachutjoltair_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802B3EFC

/// #it_802B3F20

/// #it_802B3F88

/// #it_802B4224

/// #it_802B43B0

/// #it_802B43D0

/// #itPikachutjoltair_UnkMotion0_Anim

void itPikachutjoltair_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itPikachutjoltair_UnkMotion0_Coll

/// #it_802B45F0

/// #it_802B4638

/// #it_802B4680

/// #it_802B46C8

/// #it_802B4A18

/// #it_802B4A60

void it_802B4AA8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
