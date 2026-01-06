#include "itharisen.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802927E8

void it_8029282C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->scl = ip->xCC_item_attr->x60_scale;
    Item_8026849C(gobj);
}

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

void itHarisen_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itHarisen_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_8029287C);
    return false;
}

void it_80292998(Item_GObj* gobj, f32 frameSpeed)
{
    Item* ip = GET_ITEM(gobj);
    ip->x5D0_animFrameSpeed = frameSpeed;
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

void it_802929C8(Item_GObj* gobj, f32 frameSpeed)
{
    Item* ip = GET_ITEM(gobj);
    ip->x5D0_animFrameSpeed = frameSpeed;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

void it_802929F8(Item_GObj* gobj, f32 frameSpeed)
{
    Item* ip = GET_ITEM(gobj);
    ip->x5D0_animFrameSpeed = frameSpeed;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

void it_80292A28(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x5D0_animFrameSpeed = 1.0f;
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

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

bool itHarisen_UnkMotion9_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029287C, it_8029290C);
    return false;
}

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
