#include "itkirby_2F23.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/chara/ftKirby/ftKb_Init.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

f64 it_802F23AC(Item_GObj* gobj, Vec3* pos)
{
    Item* ip = GET_ITEM(gobj);
    return SQ(ip->pos.x - pos->x) + SQ(ip->pos.y - pos->y) +
           SQ(ip->pos.z - pos->z);
}

/// #it_802F23EC

bool itKirby_2F23_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802F258C

void it_802F2810(HSD_GObj* gobj)
{
    Item* ip = gobj->user_data;
    Item_80268E5C(gobj, 1, 0);
    ip->on_accessory = it_802F289C;
    it_8026BB44((Item_GObj*) gobj);
    it_802756D0((Item_GObj*) gobj);
    it_802762BC(ip);
    it_80274ECC((Item_GObj*) gobj, 1);
    it_80273408((Item_GObj*) gobj);
}

bool itKirby_2F23_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itKirby_2F23_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itKirby_2F23_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802F289C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ftKb_SpecialN_800F5800(ip->grab_victim, &ip->pos);
}
