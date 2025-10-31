#include "itgamewatchchef.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802C837C

bool it_2725_Logic112_DmgDealt(Item_GObj* gobj)
{
    it_802C875C(gobj);
    return false;
}

/// #it_802C84A0

/// #itGamewatchchef_UnkMotion0_Anim

/// #itGamewatchchef_UnkMotion0_Phys

/// #itGamewatchchef_UnkMotion0_Coll

/// #it_802C875C

/// #itGamewatchchef_UnkMotion1_Anim

void itGamewatchchef_UnkMotion1_Phys(Item_GObj* gobj) {}

/// #itGamewatchchef_UnkMotion1_Coll

/// #it_2725_Logic112_Clanked

/// #it_2725_Logic112_HitShield

/// #it_2725_Logic112_Absorbed

bool it_2725_Logic112_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_2725_Logic112_Reflected

void it_2725_Logic112_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
