#include "itpikachutjoltair.h"

#include "lb/lb_00B0.h"

#include <placeholder.h>
#include <platform.h>

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/items/itpikachutjoltground.h"

/* 2B45E8 */ static bool itPikachutjoltair_UnkMotion0_Coll(Item_GObj* gobj);

bool itPikachutjoltair_UnkMotion0_Coll(Item_GObj* gobj)
{
    return false;
}

Item_GObj* it_802B3EFC(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->xDD4_itemVar.pikachujoltair.xDD8;
        }
    }
    return 0;
}

void it_802B3F20(Item_GObj* gobj, Vec3* arg1)
{
    Item* ip = gobj->user_data;
    PAD_STACK(8);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != NULL) {
        lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[6], NULL, arg1);
        arg1->z = 0.0f;
        return;
    }
    arg1->z = 0.0f;
    arg1->y = 0.0f;
    arg1->x = 0.0f;
}

/// #it_802B3F88

/// #it_802B4224

void it_802B43B0(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
        }
    }
}

/// #it_802B43D0

/// #itPikachutjoltair_UnkMotion0_Anim

void itPikachutjoltair_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

/// #itPikachutjoltair_UnkMotion0_Coll

bool it_2725_Logic107_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != 0) {
        it_802B3544(ip->xDD4_itemVar.pikachujoltair.xDD8);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
    }
    return true;
}

bool it_2725_Logic107_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != 0) {
        it_802B3544((Item_GObj*) ip->xDD4_itemVar.pikachujoltair.xDD8);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
    }
    return true;
}

bool it_2725_Logic107_Absorbed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != 0) {
        it_802B3544((Item_GObj*) ip->xDD4_itemVar.pikachujoltair.xDD8);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
    }
    return true;
}

/// #it_2725_Logic107_Reflected

bool it_2725_Logic107_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != 0) {
        it_802B3544((Item_GObj*) ip->xDD4_itemVar.pikachujoltair.xDD8);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
    }
    return true;
}

bool it_2725_Logic107_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_802725D4(gobj);
    if (ip->xDD4_itemVar.pikachujoltair.xDD8 != 0) {
        it_802B3544((Item_GObj*) ip->xDD4_itemVar.pikachujoltair.xDD8);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
    }
    return true;
}

void itPikachuTJoltAir_Logic107_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
