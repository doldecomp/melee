#include <platform.h>
#include <placeholder.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2AFD44 */ static bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj);

/// #it_802AF940

/// #it_802AFA2C

/// #it_802AFA70

/// #itNesspkflushexplode_UnkMotion0_Anim

void itNesspkflushexplode_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    it->x40_vel.z = it->x40_vel.y = it->x40_vel.z = 0;
}

bool itNesspkflushexplode_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_802AFD4C(Item_GObj* arg0)
{
    return true;
}

bool it_802AFD54(Item_GObj* arg0)
{
    return true;
}

bool it_802AFD5C(Item_GObj* arg0)
{
    return true;
}

bool it_802AFD64(Item_GObj* arg0)
{
    return true;
}

void it_802AFD6C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
