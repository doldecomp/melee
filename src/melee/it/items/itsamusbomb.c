#include "itsamusbomb.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_2725.h"

/// #it_802B4AC8

/// #it_802B4BA0

/// #it_802B4C10

/// #itSamusbomb_UnkMotion0_Anim

void itSamusbomb_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itSamusbomb_UnkMotion0_Coll

/// #it_802B4CF4

/// #itSamusbomb_UnkMotion1_Anim

/// #itSamusbomb_UnkMotion1_Phys

/// #itSamusbomb_UnkMotion1_Coll

/// #it_2725_Logic50_EnteredAir

/// #itSamusbomb_UnkMotion2_Anim

/// #itSamusbomb_UnkMotion2_Phys

/// #itSamusbomb_UnkMotion2_Coll

/// #it_2725_Logic50_DmgDealt

/// #it_2725_Logic50_Clanked

/// #it_2725_Logic50_HitShield

bool it_2725_Logic50_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_2725_Logic50_Reflected

/// #it_802B53CC

bool itSamusbomb_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_802751D8(gobj);
}

/// #it_802B5478

/// #it_2725_Logic50_EvtUnk
