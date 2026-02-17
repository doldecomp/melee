#include "itsamuschargeshot.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"

#include <math.h>

bool it_802B5518(Item_GObj* gobj, CollData* cd)
{
    Item* ip = GET_ITEM(gobj);
    bool ret = false;
    it_8026DA08(gobj);
    if (ip->x40_vel.y > 0.0f) {
        if (cd->env_flags & Collide_CeilingMask) {
            ret = true;
        }
    } else if (cd->env_flags & Collide_FloorMask) {
        ret = true;
    }
    if (ip->x40_vel.x > 0.0f) {
        if (cd->env_flags & Collide_LeftWallMask) {
            ret = true;
        }
    } else if (cd->env_flags & Collide_RightWallMask) {
        ret = true;
    }
    return ret;
}

/// #it_802B55C8

/// #it_802B56E4

/// #it_2725_Logic108_Destroyed

/// #it_802B5974

/// #it_2725_Logic108_PickedUp

/// #itSamuschargeshot_UnkMotion0_Anim

void itSamuschargeshot_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itSamuschargeshot_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802B5CBC

/// #itSamuschargeshot_UnkMotion8_Anim

void itSamuschargeshot_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.samuschargeshot.x8 *
                    cosf(ip->xDD4_itemVar.samuschargeshot.x4);
    ip->x40_vel.y = ip->xDD4_itemVar.samuschargeshot.x8 *
                    sinf(ip->xDD4_itemVar.samuschargeshot.x4);
}

bool itSamuschargeshot_UnkMotion8_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_802B5518(gobj, &ip->x378_itemColl)) {
        return true;
    }
    return false;
}

/// #it_802B5EDC

bool itSamusChargeshot_Logic108_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itSamusChargeshot_Logic108_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itSamusChargeshot_Logic108_Absorbed(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_Reflected

bool itSamusChargeshot_Logic108_HitShield(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic108_ShieldBounced

void itSamusChargeshot_Logic108_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
