#include "itseakneedlethrown.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"

/// #it_802AFD8C

/// #it_802AFEA8

void itSeakNeedleThrown_Logic109_Destroyed(Item_GObj* gobj)
{
    GET_ITEM(gobj)->owner = NULL;
}

/// #it_802AFF08

/// #it_802B00F4

/// #itSeakneedlethrown_UnkMotion0_Anim

/// #itSeakneedlethrown_UnkMotion1_Anim

/// #itSeakneedlethrown_UnkMotion2_Anim

bool itSeakneedlethrown_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

/// #itSeakneedlethrown_UnkMotion4_Anim

void itSeakneedlethrown_UnkMotion0_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

void itSeakneedlethrown_UnkMotion2_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

void itSeakneedlethrown_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

/// #itSeakneedlethrown_UnkMotion0_Coll

/// #itSeakneedlethrown_UnkMotion1_Coll

/// #itSeakneedlethrown_UnkMotion2_Coll

bool itSeakneedlethrown_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #itSeakneedlethrown_UnkMotion4_Coll

/// #it_2725_Logic109_DmgDealt

/// #it_2725_Logic109_Clanked

/// #it_2725_Logic109_DmgReceived

/// #it_2725_Logic109_Reflected

/// #it_2725_Logic109_ShieldBounced

/// #it_2725_Logic109_HitShield

void itSeakNeedleThrown_Logic109_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
