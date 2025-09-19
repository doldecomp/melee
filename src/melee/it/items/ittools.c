#include "ittools.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802EEFA8

bool it_2725_Logic22_DmgDealt(Item_GObj* gobj)
{
    it_802EF320(gobj);
    return false;
}

/// #it_802EF098

/// #itTools_UnkMotion4_Anim

/// #itTools_UnkMotion4_Phys

/// #itTools_UnkMotion4_Coll

/// #it_802EF320

/// #itTools_UnkMotion9_Anim

void itTools_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itTools_UnkMotion9_Coll

/// #it_802EF548

bool it_2725_Logic22_DmgReceived(Item_GObj* gobj)
{
    it_802EF548(gobj);
    return false;
}

/// #it_2725_Logic22_Clanked

/// #it_2725_Logic22_HitShield

/// #it_2725_Logic22_Absorbed

bool it_2725_Logic22_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_2725_Logic22_Reflected

void it_802EFA24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
