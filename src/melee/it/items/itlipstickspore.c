#include "itlipstickspore.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/types.h"

#include <baselib/gobj.h>

/* 29A5F8 */ static bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj);

/// #it_8029A114

/// #it_8029A218

/// #it_8029A31C

/// #it_8029A498

bool itLipstickspore_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

/// #itLipstickspore_UnkMotion0_Phys

/// #itLipstickspore_UnkMotion0_Coll

bool itLipstickspore_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

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

bool it_3F14_Logic37_ShieldBounced(Item_GObj* gobj)
{
    itColl_BounceOffShield(gobj);
    return false;
}

void it_3F14_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
