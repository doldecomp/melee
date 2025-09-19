#include "itsscopebeam.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_80298DEC

/// #it_80298ED0

/// #itSscopebeam_UnkMotion9_Anim

void itSscopebeam_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itSscopebeam_UnkMotion9_Coll

bool it_3F14_Logic38_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic38_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic38_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic38_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_3F14_Logic38_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool it_3F14_Logic38_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

void it_3F14_Logic38_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
