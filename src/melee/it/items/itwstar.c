#include "itwstar.h"

#include "it/it_26B1.h"
#include "it/item.h"

/// #it_80294364

/// #it_80294430

/// #it_802944AC

/// #it_3F14_Logic29_Spawned

/// #it_8029455C

bool itWstar_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itWstar_UnkMotion0_Phys

/// #itWstar_UnkMotion0_Coll

void it_80294624(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itWstar_UnkMotion1_Phys

/// #itWstar_UnkMotion1_Coll

/// #it_802946B0

/// #it_3F14_Logic29_PickedUp

bool itWstar_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

/// #it_3F14_Logic29_Dropped

/// #it_802947CC

/// #itWstar_UnkMotion5_Anim

void itWstar_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itWstar_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

void it_3F14_Logic29_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itWstar_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itWstar_UnkMotion4_Phys(Item_GObj* gobj) {}

/// #itWstar_UnkMotion4_Coll

void it_3F14_Logic30_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
