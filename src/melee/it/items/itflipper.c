#include "itflipper.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_80290938

/// #it_3F14_Logic20_Spawned

/// #it_80290A7C

/// #it_80290C38

/// #it_80290CE8

/// #it_80290DD4

/// #it_80290E78

bool itFlipper_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itFlipper_UnkMotion0_Coll

/// #it_80290F00

bool itFlipper_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itFlipper_UnkMotion1_Phys

/// #itFlipper_UnkMotion1_Coll

/// #it_3F14_Logic20_PickedUp

bool itFlipper_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic20_Dropped

/// #it_3F14_Logic20_Thrown

void it_3F14_Logic20_Dropped(Item_GObj* gobj)
{
    it_3F14_Logic20_Thrown(gobj);
}

/// #itFlipper_UnkMotion3_Anim

/// #itFlipper_UnkMotion3_Phys

/// #itFlipper_UnkMotion3_Coll

/// #it_80291254

/// #it_8029131C

/// #it_80291344

/// #itFlipper_UnkMotion5_Anim

/// #itFlipper_UnkMotion6_Anim

/// #itFlipper_UnkMotion6_Phys

/// #itFlipper_UnkMotion6_Coll

/// #it_3F14_Logic20_DmgDealt

/// #it_3F14_Logic20_Clanked

/// #it_3F14_Logic20_HitShield

bool it_3F14_Logic20_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic20_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_3F14_Logic20_DmgReceived

/// #it_3F14_Logic20_EnteredAir

bool itFlipper_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itFlipper_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itFlipper_UnkMotion4_Coll

void it_3F14_Logic20_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
