#include "itklap.h"

#include "gr/grkongo.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "sysdolphin/baselib/random.h"

void it_802E1820(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_8027B730(gobj);
    ip->facing_dir = 0.0f;
    ip->xD5C = 0;
    ip->xDD4_itemVar.klap.x20 = NULL;
    it_802E1930(gobj);
}

void itKlap_Logic10_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.klap.x20 != NULL) {
        grKongo_801D8058(ip->xDD4_itemVar.klap.x20);
        ip->xDD4_itemVar.klap.x20 = NULL;
    }
}

static inline void it_802E18B4_inline(Item_GObj* gobj, Item_GObj* spawned_gobj)
{
    Item* ip = GET_ITEM(spawned_gobj);
    ip->xDD4_itemVar.klap.x20 = gobj;
    it_8026BDB4(spawned_gobj);
}

Item_GObj* it_802E18B4(Item_GObj* gobj)
{
    Vec3 v;
    Item_GObj* spawned_gobj = NULL;
    PAD_STACK(4);

    if (gobj != NULL) {
        lb_8000B1CC(GET_JOBJ(gobj), NULL, &v);
        spawned_gobj = it_8027B5B0(It_Kind_Klap, &v, NULL, NULL, 1);
        if (spawned_gobj != NULL) {
            it_802E18B4_inline(gobj, spawned_gobj);
        }
    }
    return spawned_gobj;
}

void it_802E1930(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y = 0.0F;
    ip->x40_vel.x = 0.0F;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itKlap_UnkMotion1_Anim(Item_GObj* gobj)
{
    return false;
}

void itKlap_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);

    if (lb_8000B134(GET_JOBJ(gobj)) != 0 && HSD_Randi(0x64) < 0x1E) {
        if (ip->msid == 0) {
            it_802E1C4C(gobj);
            return;
        }
        it_802E1930(gobj);
    }
}

/// #itKlap_UnkMotion1_Coll

void it_802E1C4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

/// #it_802E1C84

bool itKlap_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itKlap_UnkMotion2_Phys

bool itKlap_UnkMotion2_Coll(Item_GObj* gobj)
{
    return false;
}

bool it_2725_Logic10_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDCC_flag.b3 = true;
    it_802E1E94(gobj);
    return false;
}

/// #it_802E1E94

bool itKlap_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

/// #itKlap_UnkMotion4_Phys

bool itKlap_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802E20D8

bool itKlap_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itKlap_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itKlap_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

/// #it_802E215C

/// #it_802E2330

void it_802E2450(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
