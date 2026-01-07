#include "itwhitebea.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

/// #it_802E31F8

/// #itOldottosea_UnkMotion8_Anim

void itOldottosea_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_802E32B4

/// #it_802E3314

/// #itOldottosea_UnkMotion9_Anim

void itOldottosea_UnkMotion9_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOldottosea_UnkMotion9_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

/// #it_802E3400

/// #itOldottosea_UnkMotion10_Anim

void itOldottosea_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itOldottosea_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_2725_Logic3_Destroyed

/// #it_802E3528

bool itOldottosea_UnkMotion11_Anim(Item_GObj* gobj)
{
    return false;
}

void itOldottosea_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itOldottosea_UnkMotion11_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

/// #it_802E35CC

void it_802E3784(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

// This function only called by it_3F14_Logic17_PickedUp from itfreeze, so
// using those item vars
void it_802E37A4(Item_GObj* gobj)
{
    if (gobj != NULL) {
        GET_ITEM(gobj)->xDD4_itemVar.freeze.x20 = NULL;
    }
}

/// #it_802E37BC

/// #it_802E3884

/// #fn_802E398C

/// #itWhitebea_UnkMotion0_Anim

/// #itWhitebea_UnkMotion0_Phys

/// #itWhitebea_UnkMotion0_Coll

/// #it_802E3AC8

/// #itWhitebea_UnkMotion1_Anim

/// #itWhitebea_UnkMotion1_Phys

/// #itWhitebea_UnkMotion1_Coll

/// #it_802E3DA0

bool itWhitebea_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itWhitebea_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itWhitebea_UnkMotion3_Coll

/// #it_802E3ED0

/// #itWhitebea_UnkMotion4_Anim

void itWhitebea_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

/// #itWhitebea_UnkMotion4_Coll

/// #it_802E40A4

/// #it_802E4190

/// #itWhitebea_UnkMotion2_Anim

void itWhitebea_UnkMotion2_Phys(Item_GObj* gobj) {}

/// #itWhitebea_UnkMotion2_Coll

/// #it_802E436C

/// #itWhitebea_UnkMotion5_Anim

void itWhitebea_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #itWhitebea_UnkMotion5_Coll

/// #it_802E4464

bool itWhitebea_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

void itWhitebea_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itWhitebea_UnkMotion6_Coll

/// #it_802E4558

/// #itWhitebea_UnkMotion7_Anim

void itWhitebea_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itWhitebea_UnkMotion7_Coll

void it_2725_Logic9_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

/// #itWhitebea_UnkMotion8_Anim

void itWhitebea_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic9_Dropped

/// #it_2725_Logic9_Thrown

/// #itWhitebea_UnkMotion9_Anim

void itWhitebea_UnkMotion9_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itWhitebea_UnkMotion9_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

/// #it_802E48B4

/// #itWhitebea_UnkMotion10_Anim

void itWhitebea_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itWhitebea_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802E4980

bool itWhitebea_UnkMotion11_Anim(Item_GObj* gobj)
{
    return false;
}

void itWhitebea_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itWhitebea_UnkMotion11_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

void it_802E4A24(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
