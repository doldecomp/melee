#include "itlipstick.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itlipstickspore.h"

#define GET_ATTRS(ip)                                                         \
    ((itLipstickAttributes*) (ip)->xC4_article_data->x4_specialAttributes)

/// #it_3F14_Logic23_Spawned

void it_80295748(Item_GObj* gobj, Vec* pos)
{
    Item* ip = GET_ITEM(gobj);
    *pos = GET_ATTRS(ip)->x4;
}

void it_80295770(Item_GObj* gobj, Vec* arg1, float arg2, int arg3)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xD4C > 0) {
        ip->xD4C -= 1;
    }
    it_8029A114(ip->owner, arg1, arg3, arg2);
}

/// #it_802957AC

bool itLipstick_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion0_Phys(Item_GObj* gobj) {}

bool itLipstick_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8029583C);
    return false;
}

void it_8029583C(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itLipstick_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itLipstick_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802957AC);
    return false;
}

void it_3F14_Logic23_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itLipstick_UnkMotion2_Anim(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDAC_itcmd_var0 = 1;
    return false;
}

void itLipstick_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic23_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, 6);
}

bool itLipstick_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (ip->xD4C != 0) {
        it_8026E15C(gobj, it_802957AC);
        return false;
    }
    return it_8026DF34(gobj);
}

void it_3F14_Logic23_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itLipstick_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* attr = ((Item*) gobj->user_data)->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

/// #itLipstick_UnkMotion3_Coll

bool it_3F14_Logic23_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->msid == 3 || ip->msid == 4) {
        itColl_BounceOffVictim(gobj);
    }
    return false;
}

void it_3F14_Logic23_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itLipstick_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itLipstick_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itLipstick_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802957AC, it_8029583C);
    return false;
}

bool it_3F14_Logic23_Clanked(Item_GObj* gobj)
{
    return it_3F14_Logic23_DmgDealt(gobj);
}

bool it_3F14_Logic23_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_3F14_Logic23_HitShield(Item_GObj* gobj)
{
    return it_3F14_Logic23_DmgDealt(gobj);
}

bool it_3F14_Logic23_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_3F14_Logic23_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
