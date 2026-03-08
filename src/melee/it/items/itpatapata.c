#include "itpatapata.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/ftlib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"
#include "mp/mpcoll.h"

void it_802E05A0(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 facing;

    it_8027B730(gobj);
    ip->facing_dir = it_8026B684(&ip->pos);
    if (ip->facing_dir == -1.0f) {
        facing = -1;
    } else {
        facing = 1;
    }
    mpCollSetFacingDir(&ip->x378_itemColl, facing);
    it_8027C56C(gobj, ip->facing_dir);
    ip->xD5C = 0;
    ip->xDC8_word.flags.x15 = 0;
    it_8027542C(gobj);
    it_80275270(gobj);
    ip->xDC8_word.flags.x19 = 1;
    ip->xDD4_itemVar.patapata.x28 = 0xA;
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    ip->xDD4_itemVar.patapata.x40 = 2;
    it_802762BC(ip);
    it_802E0678(gobj);
}

void it_802E0678(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8027CAD8(gobj);
    it_802E1648(gobj, 1, 2);
}

bool itPatapata_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itPatapata_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.patapata.x28 == 0) {
        it_802E0734(gobj);
        return;
    }
    ip->xDD4_itemVar.patapata.x28 = ip->xDD4_itemVar.patapata.x28 - 1;
}

bool itPatapata_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* it = gobj->user_data;
    if (it->ground_or_air == GA_Air) {
        it_8026DA08(gobj);
    } else {
        it_8026D564(gobj);
    }
    return false;
}

/// #it_802E0734

bool itPatapata_UnkMotion2_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        it_802E1648(gobj, 2, 2);
    }
    return false;
}

/// #itPatapata_UnkMotion3_Phys

/// #itPatapata_UnkMotion3_Coll

/// #it_802E0D9C

/// #itPatapata_UnkMotion3_Anim

bool it_2725_Logic4_DmgReceived(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->msid == 6) {
        it_802E1694(gobj);
    } else {
        it_802E11E0();
    }
    return false;
}

bool it_802E0F1C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_802E11E0();
    Item_8026AE84(ip, 0x12E, 0x7F, 0x40);
    ftLib_80086D40(ip->xCFC, 12, 0);
    return false;
}

void itPatapata_Logic4_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion5_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itPatapata_UnkMotion5_Phys(Item_GObj* gobj) {}

void it_2725_Logic4_Dropped(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    it_8027CBA4(gobj);
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    ip->xDD4_itemVar.patapata.x28 = 2;
    Item_80268E5C(gobj, 7, ITEM_ANIM_UPDATE);
}

/// #itPatapata_UnkMotion7_Anim

void itPatapata_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itPatapata_UnkMotion7_Coll(Item_GObj* gobj)
{
    it_8026DA08(gobj);
    return false;
}

void it_2725_Logic4_Thrown(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027CB3C(gobj);
    it_80274C88(gobj);
    ip->xDD4_itemVar.patapata.x28 = 0;
    ip->xDD4_itemVar.patapata.x24 = 0;
    ip->xDD4_itemVar.patapata.x20 = 0;
    Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
}

bool itPatapata_UnkMotion6_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 6, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itPatapata_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itPatapata_UnkMotion6_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) & 0xF) {
        it_802E1694(gobj);
    }
    return false;
}

/// #it_802E11E0

/// #itPatapata_UnkMotion4_Anim

/// #itPatapata_UnkMotion4_Phys

bool itPatapata_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.patapata.x20 == 0) {
        ip->xDCC_flag.b3 = true;
        return true;
    }
    ip->xDD4_itemVar.patapata.x20 -= 1;
    return false;
}

/// #it_802E15B0

void it_802E1648(Item_GObj* gobj, int arg1, int arg2)
{
    Item* ip = GET_ITEM(gobj);
    Item_80268E5C(gobj, arg1, arg2);
    it_80274CAC(gobj);
    ip->jumped_on = it_802E0F1C;
}

void it_802E1694(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8027327C(gobj, 0x444, 0x130);
    it_8027CE44(gobj);
    Item_8026A8EC(gobj);
}

void it_802E16D8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802E16F8
