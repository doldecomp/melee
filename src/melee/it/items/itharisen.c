#include "itharisen.h"

#include <placeholder.h>
#include <platform.h>

#include "it/it_26B1.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

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

bool itHarisen_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029290C);
    return false;
}

void it_8029290C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itHarisen_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itHarisen_UnkMotion1_Phys

bool itHarisen_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029287C);
    return false;
}

/// #it_80292998

/// #it_802929C8

/// #it_802929F8

/// #it_80292A28

void it_3F14_Logic24_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itHarisen_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itHarisen_UnkMotion6_Phys(Item_GObj* gobj) {}

/// #it_3F14_Logic24_Dropped

/// #itHarisen_UnkMotion8_Coll

void it_3F14_Logic24_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 7, 6);
}

/// #itHarisen_UnkMotion8_Phys

bool itHarisen_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029287C);
    return false;
}

/// #it_3F14_Logic24_DmgDealt

void it_3F14_Logic24_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
}

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
