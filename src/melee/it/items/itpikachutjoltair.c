#include "itpikachutjoltair.h"

#include <placeholder.h>
#include <platform.h>

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

/// #it_2725_Logic107_DmgDealt

/// #it_2725_Logic107_Clanked

/// #it_2725_Logic107_Absorbed

/// #it_2725_Logic107_Reflected

/// #it_2725_Logic107_HitShield

/// #it_2725_Logic107_ShieldBounced

void it_2725_Logic107_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
