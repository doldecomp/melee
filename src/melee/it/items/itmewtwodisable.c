#include "itmewtwodisable.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"
#include "it/inlines.h"
#include "it/item.h"
#include "it/it_2725.h"

void it_802C49E0(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

/// #it_2725_Logic67_Destroyed

/// #it_802C4A40

/// #it_802C4B38

/// #it_802C4BB8

bool itMewtwodisable_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

void itMewtwodisable_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itMewtwodisable_UnkMotion0_Coll

bool it_2725_Logic67_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic67_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic67_Clanked(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic67_HitShield(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic67_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic67_ShieldBounced(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic67_EvtUnk
