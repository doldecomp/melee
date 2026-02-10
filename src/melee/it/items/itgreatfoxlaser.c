#include "itgreatfoxlaser.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/item.h"

UNK_T it_802EAF28(Item_GObj* item_gobj)
{
    return GET_ITEM(item_gobj)->xDD4_itemVar.greatfoxlaser.x38;
}

/// #it_802EAF34

/// #it_802EB1EC

void it_802EB268(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    ip->xDD4_itemVar.greatfoxlaser.x36 = 60;
    ip->xDD4_itemVar.greatfoxlaser.x34 = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #itGreatfoxlaser_UnkMotion1_Anim

/// #itGreatfoxlaser_UnkMotion1_Phys

bool itGreatFoxLaser_Logic27_DmgDealt(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Clanked(Item_GObj* item_gobj)
{
    return false;
}

bool itGreatFoxLaser_Logic27_Absorbed(Item_GObj* item_gobj)
{
    return false;
}

/// #it_2725_Logic27_Reflected

void it_802EB5A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
