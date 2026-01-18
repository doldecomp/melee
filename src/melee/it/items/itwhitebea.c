#include "itwhitebea.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

/// #it_802E31F8

/// #itOldottosea_UnkMotion8_Anim

void itOldottosea_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_802E32B4

/// #it_802E3314

bool itOldottosea_UnkMotion9_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    }
    return false;
}

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

bool itOldottosea_UnkMotion10_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itOldottosea_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itOldottosea_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_2725_Logic3_Destroyed

void it_802E3528(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0xB, 3);
}

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

void fn_802E398C(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_8027CAD8(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itWhitebea_UnkMotion0_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itWhitebea_UnkMotion0_Phys

bool itWhitebea_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E3DA0);
    return it_8027C794(gobj);
}

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

bool itWhitebea_UnkMotion3_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, fn_802E398C);
    return it_8027C794(gobj);
}

/// #it_802E3ED0

/// #itWhitebea_UnkMotion4_Anim

void itWhitebea_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

bool itWhitebea_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        it_8026E414(gobj, it_802E40A4);
    } else {
        it_8026D62C(gobj, it_802E3DA0);
    }
    return it_8027C794(gobj);
}

void it_802E40A4(Item_GObj* gobj) {}

/// #it_802E4190

/// #itWhitebea_UnkMotion2_Anim

void itWhitebea_UnkMotion2_Phys(Item_GObj* gobj) {}

bool itWhitebea_UnkMotion2_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802E3DA0);
    return it_8027C794(gobj);
}

/// #it_802E436C

/// #itWhitebea_UnkMotion5_Anim

void itWhitebea_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itWhitebea_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026D6F4(gobj, it_802E3DA0);
    return it_8027C794(gobj);
}

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

bool itWhitebea_UnkMotion6_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802E4558);
    return it_8027C794(gobj);
}

/// #it_802E4558

/// #itWhitebea_UnkMotion7_Anim

void itWhitebea_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itWhitebea_UnkMotion7_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802E3DA0);
    return it_8027C794(gobj);
}

void it_2725_Logic9_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
}

bool itWhitebea_UnkMotion8_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itWhitebea_UnkMotion8_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic9_Dropped

/// #it_2725_Logic9_Thrown

bool itWhitebea_UnkMotion9_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 9, ITEM_ANIM_UPDATE);
    }
    return false;
}

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

void it_802E48B4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027B964(gobj, 0);
    ip->xDD4_itemVar.whitebea.x18 = 0;
    Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
}

bool itWhitebea_UnkMotion10_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0xA, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itWhitebea_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itWhitebea_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

void it_802E4980(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0xB, 3);
}

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
