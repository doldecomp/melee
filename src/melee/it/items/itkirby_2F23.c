#include "itkirby_2F23.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "ft/chara/ftKirby/ftKb_Init.h"

/// #it_802F23AC

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

/// #it_802F2810

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
