#include "itgreatfoxlaser.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

UNK_T it_802EAF28(Item_GObj* item_gobj)
{
    return M2C_FIELD(&GET_ITEM(item_gobj)->xDD4_itemVar._, UNK_T*, 0x38);
}

/// #it_802EAF34

/// #it_802EB1EC

/// #it_802EB268

/// #itGreatfoxlaser_UnkMotion1_Anim

/// #itGreatfoxlaser_UnkMotion1_Phys

bool it_2725_Logic27_DmgDealt(Item_GObj* item_gobj)
{
    return false;
}

bool it_2725_Logic27_Clanked(Item_GObj* item_gobj)
{
    return false;
}

bool it_2725_Logic27_Absorbed(Item_GObj* item_gobj)
{
    return false;
}

/// #it_2725_Logic27_Reflected

void it_802EB5A8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, (HSD_GObj*) ref_gobj);
}
