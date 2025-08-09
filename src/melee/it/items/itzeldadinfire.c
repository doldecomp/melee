#include "itzeldadinfire.h"

#include "it/inlines.h"
#include "it/it_26B1.h"

/* 2C4434 */ static bool itZeldadinfire_UnkMotion1_Coll(Item_GObj* gobj);

Fighter_GObj* it_802C3AF0(Item_GObj* arg0)
{
    return GET_ITEM(arg0)->owner;
}

/// #it_802C3AFC

/// #it_802C3BAC

/// #it_802C3CBC

/// #it_802C3D44

/// #it_802C3D74

/// #itZeldadinfire_UnkMotion0_Anim

/// #itZeldadinfire_UnkMotion1_Anim

/// #itZeldadinfire_UnkMotion0_Phys

void itZeldadinfire_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itZeldadinfire_UnkMotion0_Coll

bool itZeldadinfire_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802C443C

bool it_802C4550(Item_GObj* arg0)
{
    return true;
}

bool it_802C4558(Item_GObj* arg0)
{
    return true;
}

void it_802C4560(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
