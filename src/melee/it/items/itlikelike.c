#include "itlikelike.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"

#define GET_ATTRS(ip)                                                         \
    ((itLikelikeAttributes*) ip->xC4_article_data->x4_specialAttributes)

/// #it_802D9A2C

void it_802D9B78(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itLikelikeAttributes* attrs = GET_ATTRS(ip);
    ip->facing_dir = -ip->facing_dir;
    ip->x40_vel.x = ip->facing_dir * attrs->x0->x4;
}

/// #it_802D9BA8

/// #it_2725_Logic5_DmgReceived

/// #it_802D9DDC

/// #itLikelike_UnkMotion0_Anim

/// #itLikelike_UnkMotion0_Phys

/// #itLikelike_UnkMotion0_Coll

/// #itLikelike_UnkMotion7_Anim

/// #itLikelike_UnkMotion7_Phys

/// #itLikelike_UnkMotion7_Coll

/// #it_802DA104

/// #itLikelike_UnkMotion1_Anim

/// #itLikelike_UnkMotion1_Phys

/// #itLikelike_UnkMotion1_Coll

/// #it_802DA4C0

/// #itLikelike_UnkMotion2_Anim

/// #itLikelike_UnkMotion2_Phys

/// #itLikelike_UnkMotion2_Coll

/// #it_802DA8D8

/// #it_802DA960

/// #it_802DAA10

bool itLikelike_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLikelike_UnkMotion5_Phys

/// #itLikelike_UnkMotion4_Coll

/// #itLikelike_UnkMotion5_Coll

/// #it_802DABC0

/// #itLikelike_UnkMotion17_Anim

/// #itLikelike_UnkMotion17_Phys

bool itLikelike_UnkMotion17_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D564(gobj);
    return it_8027C794(gobj);
}

/// #it_802DAD18

bool itLikelike_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y += ip->xCC_item_attr->x10_fall_speed;
}

/// #itLikelike_UnkMotion3_Coll

/// #it_802DAE6C

/// #itLikelike_UnkMotion16_Anim

void itLikelike_UnkMotion16_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion16_Coll

/// #it_802DB074

/// #itLikelike_UnkMotion8_Anim

/// #itLikelike_UnkMotion8_Phys

/// #itLikelike_UnkMotion8_Coll

/// #it_802DB358

/// #it_802DB398

/// #itLikelike_UnkMotion12_Anim

/// #itLikelike_UnkMotion12_Phys

/// #itLikelike_UnkMotion12_Coll

/// #it_802DB5F0

/// #itLikelike_UnkMotion9_Anim

void itLikelike_UnkMotion9_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion9_Coll

/// #it_802DB74C

/// #itLikelike_UnkMotion10_Anim

void itLikelike_UnkMotion10_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion10_Coll

/// #it_802DB8A8

/// #itLikelike_UnkMotion13_Anim

/// #itLikelike_UnkMotion13_Phys

/// #itLikelike_UnkMotion13_Coll

/// #it_802DB9F4

/// #it_802DBA68

/// #it_802DBAF0

/// #itLikelike_UnkMotion14_Anim

void itLikelike_UnkMotion14_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion14_Coll

/// #itLikelike_UnkMotion15_Anim

void itLikelike_UnkMotion15_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion15_Coll

/// #it_2725_Logic5_PickedUp

/// #itLikelike_UnkMotion18_Anim

void itLikelike_UnkMotion18_Phys(Item_GObj* gobj) {}

/// #it_2725_Logic5_Dropped

/// #it_2725_Logic5_Thrown

bool itLikelike_UnkMotion19_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion19_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLikelike_UnkMotion19_Coll(Item_GObj* gobj)
{
    return it_8027C824(gobj, NULL);
}

/// #it_802DC0AC

bool itLikelike_UnkMotion6_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itLikelike_UnkMotion6_Phys

/// #itLikelike_UnkMotion6_Coll

/// #it_802DC310

/// #itLikelike_UnkMotion20_Anim

void itLikelike_UnkMotion20_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion20_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

/// #it_802DC3DC

bool itLikelike_UnkMotion21_Anim(Item_GObj* gobj)
{
    return false;
}

void itLikelike_UnkMotion21_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
}

bool itLikelike_UnkMotion21_Coll(Item_GObj* gobj)
{
    return it_8027C794(gobj);
}

/// #it_2725_Logic5_Destroyed

/// #it_802DC4BC
