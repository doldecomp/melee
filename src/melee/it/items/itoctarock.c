#include "itoctarock.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/// #it_802E4A44

/// #it_802E4B00

/// #it_802E4C08

/// #itOctarock_UnkMotion0_Anim

/// #itOctarock_UnkMotion0_Phys

/// #itOctarock_UnkMotion0_Coll

/// #it_802E4DB4

bool itOctarock_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itOctarock_UnkMotion2_Phys

/// #itOctarock_UnkMotion2_Coll

/// #it_802E4E6C

/// #itOctarock_UnkMotion3_Anim

/// #itOctarock_UnkMotion3_Phys

/// #itOctarock_UnkMotion3_Coll

/// #it_802E503C

/// #itOctarock_UnkMotion4_Anim

/// #itOctarock_UnkMotion4_Phys

/// #itOctarock_UnkMotion4_Coll

/// #it_802E52E0

/// #it_802E53C8

/// #itOctarock_UnkMotion1_Anim

/// #itOctarock_UnkMotion1_Phys

/// #itOctarock_UnkMotion1_Coll

/// #it_2725_Logic2_PickedUp

/// #itOctarock_UnkMotion5_Anim

void itOctarock_UnkMotion5_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic2_Dropped

/// #it_2725_Logic2_Thrown

/// #itOctarock_UnkMotion6_Anim

/// #itOctarock_UnkMotion6_Phys

/// #itOctarock_UnkMotion6_Coll

/// #it_802E57D4

/// #itOctarock_UnkMotion7_Anim

void itOctarock_UnkMotion7_Phys(Item_GObj* gobj) {}

/// #itOctarock_UnkMotion7_Coll

/// #it_802E58A0

bool itOctarock_UnkMotion8_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itOctarock_UnkMotion8_Phys

/// #itOctarock_UnkMotion8_Coll

void it_802E5944(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.octarock.x20.x = 0.0f;
    ip->xDD4_itemVar.octarock.x20.y = 0.0f;
    ip->xDD4_itemVar.octarock.x20.z = 0.0f;
}

/// #it_802E595C

void it_802E5AA4(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
