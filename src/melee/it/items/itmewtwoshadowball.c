#include "itmewtwoshadowball.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <math.h>

/// #it_802C4D10

bool it_802C4F50(Item_GObj* gobj, CollData* cd)
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

/// #it_802C5000

/// #it_802C519C

/// #it_802C53F0

/// #it_2725_Logic101_Destroyed

void it_802C573C(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = gobj->user_data;
        efLib_DestroyAll(gobj);
        ip->xDD4_itemVar.mewtwoshadowball.x28 = 0;
        Item_8026A8EC(gobj);
    }
}

void it_2725_Logic101_PickedUp(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    PAD_STACK(0x18);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    ip->xDD4_itemVar.mewtwoshadowball.x50 = 0.0F;
}

/// #itMewtwoshadowball_UnkMotion0_Anim

void itMewtwoshadowball_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802C5B18

/// #itMewtwoshadowball_UnkMotion8_Anim

void itMewtwoshadowball_UnkMotion8_Phys(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    if (ip->xDD4_itemVar.mewtwoshadowball.x4C > 0) {
        ip->x40_vel.x =
            ip->xDD4_itemVar.mewtwoshadowball.x4.y * cosf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
        ip->x40_vel.y =
            ip->xDD4_itemVar.mewtwoshadowball.x4.y * sinf(ip->xDD4_itemVar.mewtwoshadowball.x4.x);
    }
    it_802C4D10(gobj);
}

bool itMewtwoshadowball_UnkMotion8_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    if (it_802C4F50(gobj, &ip->x378_itemColl)) {
        it_802C5E5C(gobj);
    }
    return false;
}

bool itMewtwoshadowball_UnkMotion9_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

void itMewtwoshadowball_UnkMotion9_Phys(Item_GObj* gobj) {}

bool itMewtwoshadowball_UnkMotion9_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (it_802C4F50(gobj, &ip->x378_itemColl)) {
        it_802C5E5C(gobj);
    }
    return false;
}

void fn_802C5E18(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.mewtwoshadowball.x20++;
    ip->xDD4_itemVar.mewtwoshadowball.x20 =
        ip->xDD4_itemVar.mewtwoshadowball.x20 % 3;
}

/// #it_802C5E5C

/// #itMewtwoshadowball_UnkMotion17_Anim

void itMewtwoshadowball_UnkMotion17_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itMewtwoshadowball_UnkMotion17_Coll(Item_GObj* gobj)
{
    return false;
}

bool itMewtwoShadowball_Logic101_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itMewtwoShadowball_Logic101_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itMewtwoShadowball_Logic101_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool it_2725_Logic101_Reflected(Item_GObj* gobj)
{
    Item* ip = gobj->user_data;
    ip->xDD4_itemVar.mewtwoshadowball.x4.x += M_PI;
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x < 0.0f) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x += M_TAU;
    }
    while (ip->xDD4_itemVar.mewtwoshadowball.x4.x > M_TAU) {
        ip->xDD4_itemVar.mewtwoshadowball.x4.x -= M_TAU;
    }
    return false;
}

bool itMewtwoShadowball_Logic101_HitShield(Item_GObj* arg0)
{
    return true;
}

/// #it_2725_Logic101_ShieldBounced

void itMewtwoShadowball_Logic101_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
