#include "itleadead.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

/// #it_802E8BCC

/// #it_802E8CD8

/// #it_802E8F24

bool itLeadead_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLeadead_UnkMotion1_Phys

/// #itLeadead_UnkMotion1_Coll

/// #it_802E9038

/// #itLeadead_UnkMotion2_Anim

/// #itLeadead_UnkMotion2_Phys

/// #itLeadead_UnkMotion2_Coll

/// #it_802E9308

bool itLeadead_UnkMotion10_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion10_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itLeadead_UnkMotion10_Coll

/// #it_802E93C8

/// #it_802E9494

/// #itLeadead_UnkMotion11_Anim

/// #itLeadead_UnkMotion12_Anim

void itLeadead_UnkMotion12_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

/// #itLeadead_UnkMotion12_Coll

/// #it_802E9738

/// #itLeadead_UnkMotion7_Anim

/// #itLeadead_UnkMotion7_Phys

/// #itLeadead_UnkMotion7_Coll

/// #it_802E98E0

bool itLeadead_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLeadead_UnkMotion8_Phys

/// #itLeadead_UnkMotion8_Coll

/// #it_802E9A00

/// #itLeadead_UnkMotion9_Anim

void itLeadead_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itLeadead_UnkMotion9_Coll

/// #it_802E9BA0

/// #itLeadead_UnkMotion3_Anim

void itLeadead_UnkMotion3_Phys(Item_GObj* gobj) {}

/// #itLeadead_UnkMotion3_Coll

/// #it_802E9D50

bool itLeadead_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLeadead_UnkMotion4_Phys

/// #itLeadead_UnkMotion4_Coll

/// #itLeadead_UnkMotion5_Anim

void itLeadead_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion5_Coll(Item_GObj* gobj)
{
    return false;
}

/// #itLeadead_UnkMotion6_Anim

void itLeadead_UnkMotion6_Phys(Item_GObj* gobj) {}

/// #itLeadead_UnkMotion6_Coll

void it_2725_Logic1_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0xD, ITEM_ANIM_UPDATE);
}

/// #itLeadead_UnkMotion13_Anim

void itLeadead_UnkMotion13_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic1_Dropped

/// #it_2725_Logic1_Thrown

/// #itLeadead_UnkMotion14_Anim

void itLeadead_UnkMotion14_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLeadead_UnkMotion14_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

/// #it_802EA2A0

bool itLeadead_UnkMotion15_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion15_Phys(Item_GObj* gobj) {}

bool itLeadead_UnkMotion15_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802EA334

bool itLeadead_UnkMotion16_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion16_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLeadead_UnkMotion16_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

bool itLeadead_UnkMotion17_Anim(Item_GObj* gobj)
{
    return false;
}

void itLeadead_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLeadead_UnkMotion17_Coll(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}

/// #it_2725_Logic1_Destroyed

/// #it_802EA478

/// #it_802EA674

/// #it_802EA6F4

/// #it_802EA804

/// #it_802EA988

/// #it_802EA9FC

/// #it_802EAAEC

/// #it_802EAC8C

/// #it_802EADD8

/// #it_802EAE80
