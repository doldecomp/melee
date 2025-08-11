#include "ithammerhead.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/it_26B1.h"

/// #it_80299C48

/// #it_3F14_Logic40_Spawned

/// #it_80299D7C

/// #it_3F14_Logic40_PickedUp

bool itHammerhead_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itHammerhead_UnkMotion1_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic40_Dropped

/// #it_3F14_Logic40_Thrown

/// #itHammerhead_UnkMotion2_Anim

/// #itHammerhead_UnkMotion2_Phys

/// #itHammerhead_UnkMotion2_Coll

/// #it_80299F94

/// #it_80299FB4

/// #itHammerhead_UnkMotion3_Anim

void itHammerhead_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itHammerhead_UnkMotion3_Coll

bool it_3F14_Logic40_DmgDealt(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic40_Clanked(Item_GObj* arg0)
{
    return false;
}

bool it_3F14_Logic40_HitShield(Item_GObj* arg0)
{
    return false;
}

/// #it_3F14_Logic40_Reflected

bool it_3F14_Logic40_DmgReceived(Item_GObj* arg0)
{
    return false;
}

void it_3F14_Logic40_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
