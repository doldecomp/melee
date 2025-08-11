#include "itlipstick.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_3F14_Logic23_Spawned

/// #it_80295748

/// #it_80295770

/// #it_802957AC

bool itLipstick_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itLipstick_UnkMotion0_Coll

/// #it_8029583C

bool itLipstick_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLipstick_UnkMotion1_Phys

/// #itLipstick_UnkMotion1_Coll

/// #it_3F14_Logic23_PickedUp

bool itLipstick_UnkMotion2_Anim(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDAC_itcmd_var0 = 1;
    return false;
}

void itLipstick_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic23_Dropped

/// #itLipstick_UnkMotion4_Coll

/// #it_3F14_Logic23_Thrown

/// #itLipstick_UnkMotion4_Phys

/// #itLipstick_UnkMotion3_Coll

/// #it_3F14_Logic23_DmgDealt

/// #it_3F14_Logic23_EnteredAir

bool itLipstick_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #itLipstick_UnkMotion5_Coll

/// #it_3F14_Logic23_Clanked

/// #it_3F14_Logic23_Reflected

/// #it_3F14_Logic23_HitShield

/// #it_3F14_Logic23_ShieldBounced

void it_3F14_Logic23_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
