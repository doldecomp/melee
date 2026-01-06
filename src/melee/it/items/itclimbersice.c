#include "itclimbersice.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2C23D4 */ static bool itClimbersblizzard_UnkMotion0_Coll(Item_GObj* gobj);

/// #it_802C1590

/// #it_802C16F8

void it_802C17DC(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

/// #it_2725_Logic90_Destroyed

/// #it_802C1854

/// #it_802C1950

/// #itClimbersice_UnkMotion0_Anim

void itClimbersice_UnkMotion0_Phys(Item_GObj* gobj) {}

/// #itClimbersice_UnkMotion0_Coll

void it_802C1A58(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itClimbersice_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itClimbersice_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itClimbersice_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802C1950);
    return false;
}

/// #it_802C1AE4

bool itClimbersice_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #itClimbersice_UnkMotion2_Phys

/// #itClimbersice_UnkMotion2_Coll

/// #fn_802C1D44

bool itClimbersice_UnkMotion3_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    ip->xD44_lifeTimer -= 1.0f;
    return false;
}

/// #itClimbersice_UnkMotion3_Phys

/// #itClimbersice_UnkMotion3_Coll

bool it_2725_Logic90_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic90_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_2725_Logic90_Clanked(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic90_HitShield

bool it_2725_Logic90_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic90_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

/// #it_2725_Logic90_EvtUnk
