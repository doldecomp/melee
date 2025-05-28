#include "itzeldadinfireexplode.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2C4998 */ static bool it_802C4998(void);

/// #it_802C4580

/// #it_802C4670

/// #it_802C46C4

/// #it_802C4820

void it_802C4980(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
#ifndef BUGFIX
    ip->x40_vel.z = ip->x40_vel.y = ip->x40_vel.z = 0.0F;
#else
    itResetVelocity(ip);
#endif
}

bool it_802C4998(void)
{
    return false;
}

bool it_802C49A0(Item_GObj* arg0)
{
    return true;
}

bool it_802C49A8(Item_GObj* arg0)
{
    return true;
}

bool it_802C49B0(Item_GObj* arg0)
{
    return true;
}

bool it_802C49B8(Item_GObj* arg0)
{
    return true;
}

void it_802C49C0(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
