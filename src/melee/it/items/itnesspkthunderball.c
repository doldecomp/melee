#include "itnesspkthunderball.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "lb/lbvector.h"
#include "MSL/math.h"
#include "MSL/trigf.h"

static inline void normalizeAngle(f32* angle)
{
    while (*angle < 0.0F) {
        *angle += 2 * M_PI;
    }
    while (*angle > 2 * M_PI) {
        *angle -= 2 * M_PI;
    }
}

/// #it_802AB3F0

/// #it_802AB468

bool it_802AB4B8(Item_GObj* gobj, CollData* cd)
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

HSD_GObj* it_802AB568(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->owner;
        }
    }
    return NULL;
}

/// #it_802AB58C

/// #it_802AB90C

/// #it_802AB9C0

/// #it_802ABA4C

/// #itNesspkthunderball_UnkMotion0_Anim

/// #itNesspkthunderball_UnkMotion0_Phys

/// #itNesspkthunderball_UnkMotion0_Coll

bool it_2725_Logic26_DmgDealt(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC074(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

/// #it_802AC098

bool it_802AC338(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

bool it_802AC35C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);
    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.pkthunder.xEAC = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    normalizeAngle(&ip->xDD4_itemVar.pkthunder.xEAC);
    return false;
}

bool it_802AC3F8(Item_GObj* gobj)
{
    it_802AB90C(gobj);
    return true;
}

void it_802AC41C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
