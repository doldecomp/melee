#include "itharisen.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802927E8

/// #it_8029282C

void it_3F14_Logic24_Spawned(Item_GObj* gobj)
{
    it_8029290C(gobj);
}

/// #it_8029287C

bool itHarisen_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itHarisen_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itHarisen_UnkMotion0_Coll

/// #it_8029290C

bool itHarisen_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itHarisen_UnkMotion1_Phys

/// #itHarisen_UnkMotion1_Coll

/// #it_80292998

/// #it_802929C8

/// #it_802929F8

/// #it_80292A28

/// #it_3F14_Logic24_PickedUp

bool itHarisen_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itHarisen_UnkMotion6_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic24_Dropped

/// #itHarisen_UnkMotion8_Coll

/// #it_3F14_Logic24_Thrown

/// #itHarisen_UnkMotion8_Phys

/// #itHarisen_UnkMotion7_Coll

/// #it_3F14_Logic24_DmgDealt

/// #it_3F14_Logic24_EnteredAir

bool itHarisen_UnkMotion9_Anim(Item_GObj* gobj)
{
    return false;
}

void itHarisen_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itHarisen_UnkMotion9_Coll

/// #it_3F14_Logic24_Clanked

bool it_3F14_Logic24_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

/// #it_3F14_Logic24_HitShield

bool it_3F14_Logic24_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic24_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
