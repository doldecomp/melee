#include "itclimbersice.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/it_26B1.h"
#include "ef/eflib.h"

/* 2C23D4 */ static bool itClimbersblizzard_UnkMotion0_Coll(Item_GObj* gobj);

/// #it_802C1590

/// #it_802C16F8

void it_802C17DC(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}

/// #it_2725_Logic90_Destroyed

/// #it_802C1854

void it_802C1950(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

/// #itClimbersice_UnkMotion0_Anim

void itClimbersice_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itClimbersice_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, (HSD_GObjEvent) it_802C1A58);
    it_80276CB8(gobj);
    return false;
}

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

void fn_802C1D44(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    efLib_DestroyAll(gobj);
}

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

void it_2725_Logic90_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.climbersice.x0 == ref_gobj) {
        ip->xDD4_itemVar.climbersice.x0 = NULL;
    }
    it_8026B894(gobj, ref_gobj);
}
