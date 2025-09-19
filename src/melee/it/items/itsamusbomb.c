#include "itsamusbomb.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802B4AC8

/// #it_802B4BA0

void it_802B4C10(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, 0x11);
}

/// #itSamusbomb_UnkMotion0_Anim

void itSamusbomb_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSamusbomb_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802B4CF4);
    return false;
}

void it_802B4CF4(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 0x11);
}

/// #itSamusbomb_UnkMotion1_Anim

/// #itSamusbomb_UnkMotion1_Phys

bool itSamusbomb_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E248(gobj, it_802B4C10);
    return false;
}

void it_2725_Logic50_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, 0x11);
}

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
