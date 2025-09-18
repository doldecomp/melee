#include "itoctarockstone.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"

#include "it/inlines.h"
#include "it/it_2725.h"

/// #it_802E878C

bool it_2725_Logic4_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic4_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic4_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic4_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic4_Reflected

bool it_2725_Logic4_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_802E883C

/// #itOctarockstone_UnkMotion0_Anim

void itOctarockstone_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itOctarockstone_UnkMotion0_Coll

/// #it_802E890C

bool itOctarockstone_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itOctarockstone_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itOctarockstone_UnkMotion1_Coll(Item_GObj* gobj)
{
    return it_8026DFB0(gobj);
}

void it_802E89B0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

/// #it_802E89D0

/// #it_802E8ADC
