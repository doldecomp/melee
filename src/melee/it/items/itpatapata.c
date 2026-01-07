#include "itpatapata.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802E05A0

/// #it_802E0678

bool itPatapata_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itPatapata_UnkMotion1_Phys

/// #itPatapata_UnkMotion1_Coll

/// #it_802E0734

/// #itPatapata_UnkMotion2_Anim

/// #itPatapata_UnkMotion3_Phys

/// #itPatapata_UnkMotion3_Coll

/// #it_802E0D9C

/// #itPatapata_UnkMotion3_Anim

/// #it_2725_Logic4_DmgReceived

/// #it_802E0F1C

void it_2725_Logic4_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

/// #itPatapata_UnkMotion5_Anim

void itPatapata_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic4_Dropped

/// #itPatapata_UnkMotion7_Anim

void itPatapata_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itPatapata_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

/// #it_2725_Logic4_Thrown

/// #itPatapata_UnkMotion6_Anim

void itPatapata_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itPatapata_UnkMotion6_Coll

/// #it_802E11E0

/// #itPatapata_UnkMotion4_Anim

/// #itPatapata_UnkMotion4_Phys

/// #itPatapata_UnkMotion4_Coll

/// #it_802E15B0

/// #it_802E1648

/// #it_802E1694

void it_802E16D8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802E16F8
