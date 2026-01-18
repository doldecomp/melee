#include "itlikelike.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/it_26B1.h"

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

bool itLikelike_UnkMotion0_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itLikelike_UnkMotion0_Phys

/// #itLikelike_UnkMotion0_Coll

bool itLikelike_UnkMotion7_Anim(Item_GObj* gobj)
{
    if (it_80272C6C(gobj) == 0) {
        it_802DA104(gobj);
    }
    return false;
}

/// #itLikelike_UnkMotion7_Phys

/// #itLikelike_UnkMotion7_Coll

/// #it_802DA104

bool itLikelike_UnkMotion1_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE | ITEM_HIT_PRESERVE);
    }
    return false;
}

/// #itLikelike_UnkMotion1_Phys

/// #itLikelike_UnkMotion1_Coll

/// #it_802DA4C0

bool itLikelike_UnkMotion2_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE | ITEM_HIT_PRESERVE);
    }
    return false;
}

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

bool itLikelike_UnkMotion4_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802D9DDC);
    return it_8027C794(gobj);
}

bool itLikelike_UnkMotion5_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E414(gobj, it_802DABC0);
    return it_8027C794(gobj);
}

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

bool itLikelike_UnkMotion3_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026E71C(gobj, it_802DA8D8);
    return it_8027C794(gobj);
}

void it_802DAE6C(Item_GObj* gobj)
{
    PAD_STACK(16);
    it_80273454(gobj);
    Item_80268E5C(gobj, 0x10, ITEM_ANIM_UPDATE);
}

/// #itLikelike_UnkMotion16_Anim

void itLikelike_UnkMotion16_Phys(Item_GObj* gobj) {}

/// #itLikelike_UnkMotion16_Coll

/// #it_802DB074

bool itLikelike_UnkMotion8_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 8, ITEM_ANIM_UPDATE);
    }
    return false;
}

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

bool itLikelike_UnkMotion9_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

/// #it_802DB74C

/// #itLikelike_UnkMotion10_Anim

void itLikelike_UnkMotion10_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion10_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

/// #it_802DB8A8

bool itLikelike_UnkMotion13_Anim(Item_GObj* gobj)
{
    PAD_STACK(8);
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0xD, ITEM_ANIM_UPDATE);
    }
    return false;
}

/// #itLikelike_UnkMotion13_Phys

bool itLikelike_UnkMotion13_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

/// #it_802DB9F4

/// #it_802DBA68

/// #it_802DBAF0

/// #itLikelike_UnkMotion14_Anim

void itLikelike_UnkMotion14_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion14_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

/// #itLikelike_UnkMotion15_Anim

void itLikelike_UnkMotion15_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion15_Coll(Item_GObj* gobj)
{
    PAD_STACK(8);
    it_8026D6F4(gobj, it_802DAA10);
    return it_8027C794(gobj);
}

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

void it_802DC310(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027B964(gobj, 0);
    ip->xDD4_itemVar.likelike.x18 = 0;
    Item_80268E5C(gobj, 0x14, ITEM_ANIM_UPDATE);
}

bool itLikelike_UnkMotion20_Anim(Item_GObj* gobj)
{
    if (!it_80272C6C(gobj)) {
        Item_80268E5C(gobj, 0x14, ITEM_ANIM_UPDATE);
    }
    return false;
}

void itLikelike_UnkMotion20_Phys(Item_GObj* gobj) {}

bool itLikelike_UnkMotion20_Coll(Item_GObj* gobj)
{
    return it_8027C79C(gobj);
}

void it_802DC3DC(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    it_8027BA54(gobj, &ip->x40_vel);
    it_802762BC(ip);
    Item_80268E5C(gobj, 0x15, 3);
}

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

void it_2725_Logic5_Destroyed(Item_GObj* gobj)
{
    it_802DBAF0(gobj, 0, 1);
    it_2725_Logic9_Destroyed(gobj);
}

/// #it_802DC4BC
