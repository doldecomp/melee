#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <baselib/gobj.h>

/* 29A5F8 */ static bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj);

/// #it_8029A114

/// #it_8029A218

/// #it_8029A31C

/// #it_8029A498

/// #itLipstickspore_UnkMotion0_Anim

/// #itLipstickspore_UnkMotion0_Phys

/// #itLipstickspore_UnkMotion0_Coll

/// #itLipstickspore_UnkMotion1_Anim

void itLipstickspore_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_3F14_Logic37_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic37_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic37_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic37_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_3F14_Logic37_Reflected

/// #it_3F14_Logic37_ShieldBounced

void it_3F14_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
