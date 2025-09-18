#include "itevyoshiegg.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_8029B0C8

/// #it_3F14_Logic42_Destroyed

void it_3F14_Logic42_Spawned(Item_GObj* gobj)
{
    Item* it = GET_ITEM((HSD_GObj*) gobj);
    // This should be EvYoshiEgg
    it->xDD4_itemVar.bombhei.xDD4 = 0;
    it_8029B268(gobj);
}

/// #it_8029B1D8

bool itEvyoshiegg_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itEvyoshiegg_UnkMotion0_Coll

/// #it_8029B268

bool itEvyoshiegg_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itEvyoshiegg_UnkMotion1_Phys

/// #itEvyoshiegg_UnkMotion1_Coll

/// #it_3F14_Logic42_PickedUp

bool itEvyoshiegg_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic42_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic42_Thrown(gobj);
}

/// #it_3F14_Logic42_Thrown

/// #itEvyoshiegg_UnkMotion3_Phys

/// #itEvyoshiegg_UnkMotion3_Coll

/// #itEvyoshiegg_UnkMotion5_Anim

void itEvyoshiegg_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itEvyoshiegg_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic42_DmgDealt

/// #it_3F14_Logic42_Clanked

/// #it_3F14_Logic42_HitShield

/// #it_3F14_Logic42_Reflected

/// #it_3F14_Logic42_DmgReceived

/// #it_3F14_Logic42_EnteredAir

bool itEvyoshiegg_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itEvyoshiegg_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itEvyoshiegg_UnkMotion4_Coll

void it_3F14_Logic42_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
