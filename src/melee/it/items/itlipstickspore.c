#include "itlipstickspore.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

#include <trigf.h>
#include <baselib/gobj.h>
#include "db/db.h"
#include "ef/efsync.h"

/* 29A5F8 */ static bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj);

/// #it_8029A114

/// #it_8029A218

/// #it_8029A31C

void it_8029A498(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(16);

    it_8026B3A8(gobj);
    it_80274740(gobj);
    it_80275158(gobj, 1.0f);
    Item_80268E5C(gobj, 1, 2);

    ip->xDCE_flag.b7 = false;
}

bool itLipstickspore_UnkMotion0_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itLipstickspore_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->x40_vel.x == 0.0f) {
        return;
    }

    if (ip->xDD4_itemVar.lipstickspore.xDD8 == 0.0f) {
        return;
    }

    if (ip->x40_vel.x > 0.0f) {
        ip->x40_vel.x -= ip->xDD4_itemVar.lipstickspore.xDD8;
    } else {
        ip->x40_vel.x += ip->xDD4_itemVar.lipstickspore.xDD8;
    }

    {
        f32 abs_vel = ip->x40_vel.x;
        if (abs_vel < 0.0f) {
            abs_vel = -abs_vel;
        }
        if (abs_vel < ip->xDD4_itemVar.lipstickspore.xDD8) {
            ip->x40_vel.x = 0.0f;
        }
    }
}

bool itLipstickspore_UnkMotion0_Coll(Item_GObj* gobj)
{
    if (it_8026DFB0(gobj)) {
        return true;
    }
    return false;
}

bool itLipstickspore_UnkMotion1_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itLipstickspore_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itLipstickspore_UnkMotion1_Coll(Item_GObj* gobj)
{
    return false;
}

bool itLipstickSpore_Logic37_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itLipstickSpore_Logic37_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    it_80273030(gobj);
    HSD_JObjSetRotationZ(jobj, atan2f(ip->x40_vel.y, ip->x40_vel.x));
    return false;
}

bool itLipstickSpore_Logic37_ShieldBounced(Item_GObj* gobj)
{
    itColl_BounceOffShield(gobj);
    return false;
}

void itLipstickSpore_Logic37_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
