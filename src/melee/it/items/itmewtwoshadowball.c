#include "itmewtwoshadowball.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802C4D10

/// #it_802C4F50

/// #it_802C5000

/// #it_802C519C

/// #it_802C53F0

/// #it_2725_Logic101_Destroyed

/// #it_802C573C

/// #it_2725_Logic101_PickedUp

/// #itMewtwoshadowball_UnkMotion0_Anim

void itMewtwoshadowball_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802C5B18

/// #itMewtwoshadowball_UnkMotion8_Anim

/// #itMewtwoshadowball_UnkMotion8_Phys

/// #itMewtwoshadowball_UnkMotion8_Coll

/// #itMewtwoshadowball_UnkMotion9_Anim

void itMewtwoshadowball_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itMewtwoshadowball_UnkMotion9_Coll

/// #fn_802C5E18

/// #it_802C5E5C

/// #itMewtwoshadowball_UnkMotion17_Anim

void itMewtwoshadowball_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itMewtwoshadowball_UnkMotion17_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic101_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic101_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic101_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic101_Reflected

bool it_2725_Logic101_HitShield(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic101_ShieldBounced

void it_2725_Logic101_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
