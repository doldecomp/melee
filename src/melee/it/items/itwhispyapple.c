#include "itwhispyapple.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802EE200

/// #it_802EE374

/// #itWhispyapple_UnkMotion0_Anim

/// #itWhispyapple_UnkMotion0_Phys

/// #itWhispyapple_UnkMotion0_Coll

void it_802EE6A0(Item_GObj* gobj)
{
    Item* ip;
    f32 val;

    ip = GET_ITEM(gobj);
    val = 0;
    ip->x40_vel.x = val;
    ip->x40_vel.y = val;
    ip->x40_vel.z = val;
    Item_80268E5C((HSD_GObj*) gobj, 1, ITEM_ANIM_UPDATE);
}

/// #itWhispyapple_UnkMotion1_Anim

void itWhispyapple_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, fn_802EE7FC);
    return false;
}

void fn_802EE7FC(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

/// #itWhispyapple_UnkMotion5_Anim

void itWhispyapple_UnkMotion5_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itWhispyapple_UnkMotion5_Coll

/// #it_802EEA08

bool itWhispyapple_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itWhispyapple_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #it_802EEA70

/// #it_802EEB28

void it_2725_Logic18_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

/// #itWhispyapple_UnkMotion6_Anim

void itWhispyapple_UnkMotion6_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion6_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802EE6A0, fn_802EE7FC);
    return false;
}

/// #it_802EED00

/// #itWhispyapple_UnkMotion7_Anim

void itWhispyapple_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itWhispyapple_UnkMotion7_Coll(Item_GObj* item_gobj)
{
    return false;
}

bool it_802EEED0(Item_GObj* item_gobj)
{
    return true;
}

/// #it_802EEED8

bool it_802EEF10(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802EEF30(Item_GObj* gobj)
{
    it_802725D4(gobj);
    itColl_BounceOffVictim(gobj);
    return false;
}

bool it_802EEF68(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802EEF88(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
