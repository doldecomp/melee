#include "itgreatfoxlaser.h"

#include "it/inlines.h"
#include "it/item.h"
#include "it/it_26B1.h"

UNK_T it_802EAF28(Item_GObj* item_gobj)
{
    return M2C_FIELD(&GET_ITEM(item_gobj)->xDD4_itemVar._, UNK_T*, 0x38);
}

/// #it_802EAF34

/// #it_802EB1EC

void it_802EB268(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    M2C_FIELD(&ip->xDD4_itemVar._, s16*, 0x36) = 60;
    M2C_FIELD(&ip->xDD4_itemVar._, s16*, 0x34) = 0;
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
