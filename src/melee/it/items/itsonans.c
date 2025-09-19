#include "itsonans.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802CD44C

void it_802CD4D8(void) {}

void it_802CD4DC(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802CD4FC

bool it_2725_Logic9_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.sonans.x60 *= -1.0f;
    return false;
}

/// #it_802CD7D4

/// #itSonans_UnkMotion0_Anim

void itSonans_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_802CD4FC(gobj);
}

/// #itSonans_UnkMotion0_Coll

/// #it_802CD9C0

/// #itSonans_UnkMotion1_Anim

void itSonans_UnkMotion1_Phys(Item_GObj* gobj)
{
    it_802CD4FC(gobj);
}

/// #itSonans_UnkMotion1_Coll

/// #it_802CDAA8

bool itSonans_UnkMotion2_Anim(Item_GObj* gobj)
{
    it_80279FF8(gobj);
    return false;
}

void itSonans_UnkMotion2_Phys(Item_GObj* gobj) {}

bool itSonans_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}
