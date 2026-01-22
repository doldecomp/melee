#include "itoctarockstone.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

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

bool it_2725_Logic4_Reflected(Item_GObj* gobj)
{
    it_80273030(gobj);
    return false;
}

bool it_2725_Logic4_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802E883C(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itOctarockstone_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    return false;
}

void itOctarockstone_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itOctarockstone_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    s32 coll;

    coll = it_8026DAA8(gobj);
    if (coll & 0xF) {
        it_8027781C(gobj);
        if (coll & 0x1) {
            it_802762B0(ip);
        }
        itOctarockstone_802E890C(gobj);
    }
    return false;
}

void itOctarockstone_802E890C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    Item_8026AE84(ip, 0x138, 0x7F, 0x40);
}

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
