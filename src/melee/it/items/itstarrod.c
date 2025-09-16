#include "itstarrod.h"

#include <placeholder.h>
#include <platform.h>

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itstarrodstar.h"

typedef struct StarRodAttributes {
    int x0;
    Vec x4;
} StarRodAttributes;

ItemStateTable it_803F5F90[] = {
    { -1, itStarrod_UnkMotion0_Anim, itStarrod_UnkMotion0_Phys,
      itStarrod_UnkMotion0_Coll },
    { -1, itStarrod_UnkMotion4_Anim, itStarrod_UnkMotion1_Phys,
      itStarrod_UnkMotion1_Coll },
    { -1, itStarrod_UnkMotion2_Anim, itStarrod_UnkMotion2_Phys, 0 },
    { 0, itStarrod_UnkMotion4_Anim, itStarrod_UnkMotion4_Phys,
      itStarrod_UnkMotion3_Coll },
    { 0, itStarrod_UnkMotion4_Anim, itStarrod_UnkMotion4_Phys,
      itStarrod_UnkMotion4_Coll },
    { -1, itStarrod_UnkMotion5_Anim, itStarrod_UnkMotion5_Phys,
      itStarrod_UnkMotion5_Coll }
};

void it_3F14_Logic22_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    StarRodAttributes* x = ip->xC4_article_data->x4_specialAttributes;
    ip->xD4C = x->x0;
    it_80292488(gobj);
}

void it_80292394(Item_GObj* gobj, Vec* arg1)
{
    Item* ip = GET_ITEM(gobj);
    StarRodAttributes* x = ip->xC4_article_data->x4_specialAttributes;
    *arg1 = x->x4;
}

void it_802923BC(Item_GObj* gobj, Vec* arg1, float arg2, int arg3)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C > 0) {
        ip->xD4C -= 1;
    }
    it_802988E4(ip->owner, arg1, arg3);
}

void it_802923F8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B390(gobj);
    ip->x40_vel.x = ip->x40_vel.y = ip->x40_vel.z = 0.0f;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itStarrod_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itStarrod_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itStarrod_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80292488);
    return false;
}

void it_80292488(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itStarrod_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itStarrod_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* x = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, x->x10_fall_speed, x->x14_fall_speed_max);
}

bool itStarrod_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802923F8);
    return false;
}

void it_3F14_Logic22_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itStarrod_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itStarrod_UnkMotion2_Phys(Item_GObj* gobj)
{
    return;
}

void it_3F14_Logic22_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

bool itStarrod_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_802923F8);
        return false;
    }
    return it_8026DF34(gobj);
}

void it_3F14_Logic22_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE | ITEM_DROP_UPDATE);
}

void itStarrod_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* x = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, x->x10_fall_speed, x->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

bool itStarrod_UnkMotion3_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_802923F8);
        return false;
    }
    return it_8026DF34(gobj);
}

bool it_3F14_Logic22_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

void it_3F14_Logic22_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itStarrod_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itStarrod_UnkMotion5_Phys(Item_GObj* gobj)
{
    return;
}

bool itStarrod_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802923F8, it_80292488);
    return false;
}

bool it_3F14_Logic22_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

bool it_3F14_Logic22_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic22_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

bool it_3F14_Logic22_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic22_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
