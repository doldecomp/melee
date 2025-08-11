#include "itsamuschargeshot.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/it_26B1.h"

/// #it_802B5518

/// #it_802B55C8

/// #it_802B56E4

/// #it_2725_Logic108_Destroyed

/// #it_802B5974

/// #it_2725_Logic108_PickedUp

/// #itSamuschargeshot_UnkMotion0_Anim

void itSamuschargeshot_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSamuschargeshot_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802B5CBC

/// #itSamuschargeshot_UnkMotion8_Anim

/// #itSamuschargeshot_UnkMotion8_Phys

/// #itSamuschargeshot_UnkMotion8_Coll

/// #it_802B5EDC

bool it_2725_Logic108_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic108_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic108_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_Reflected

bool it_2725_Logic108_HitShield(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_ShieldBounced

void it_2725_Logic108_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
