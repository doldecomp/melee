#include "itoldkuri.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

void it_2725_Logic29_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802D73F0

/// #it_802D747C

bool itOldkuri_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itOldkuri_UnkMotion0_Phys

/// #itOldkuri_UnkMotion0_Coll

/// #it_802D758C

/// #itOldkuri_UnkMotion1_Anim

/// #itOldkuri_UnkMotion1_Phys

/// #itOldkuri_UnkMotion1_Coll

/// #it_802D775C

/// #itOldkuri_UnkMotion2_Anim

/// #itOldkuri_UnkMotion2_Phys

/// #itOldkuri_UnkMotion2_Coll

/// #itOldkuri_UnkMotion3_Anim

void itOldkuri_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itOldkuri_UnkMotion3_Coll

/// #it_802D7AF0

/// #itOldkuri_UnkMotion4_Anim

void itOldkuri_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

/// #itOldkuri_UnkMotion4_Coll

/// #it_2725_Logic0_PickedUp

/// #itOldkuri_UnkMotion5_Anim

void itOldkuri_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic0_Dropped

/// #it_2725_Logic0_Thrown

/// #itOldkuri_UnkMotion6_Anim

void itOldkuri_UnkMotion6_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOldkuri_UnkMotion6_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

/// #itOldkuri_UnkMotion9_Anim

void itOldkuri_UnkMotion9_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->ground_or_air == GA_Air) {
        ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    }
}

/// #itOldkuri_UnkMotion9_Coll

/// #it_2725_Logic0_DmgReceived

/// #it_802D8098

/// #it_802D813C

/// #itOldkuri_UnkMotion7_Anim

void itOldkuri_UnkMotion7_Phys(Item_GObj* gobj) {}

bool itOldkuri_UnkMotion7_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

/// #it_802D81FC

bool itOldkuri_UnkMotion8_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        return true;
    }
    return false;
}

void itOldkuri_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itOldkuri_UnkMotion8_Coll(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}

/// #it_802D82C4

/// #itOldkuri_UnkMotion10_Anim

void itOldkuri_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itOldkuri_UnkMotion10_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802D839C

/// #itOldkuri_UnkMotion11_Anim

void itOldkuri_UnkMotion11_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itOldkuri_UnkMotion11_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

/// #it_802D848C

void it_802D84D8(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
