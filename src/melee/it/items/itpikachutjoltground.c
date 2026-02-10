#include "itpikachutjoltground.h"

#include "ef/eflib.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCharItems.h"
#include "it/item.h"
#include "it/items/itpikachutjoltair.h"
#include "lb/lbvector.h"
#include "MSL/trigf.h"

#include <math.h>

/* 2B37F0 */ static void itPikachutjoltground_UnkMotion1_Phys(Item_GObj*);

void* it_802B3368(Item_GObj* gobj)
{
    Item* ip;

    if (gobj != NULL) {
        ip = GET_ITEM(gobj);
        if (ip != NULL) {
            return ip->xDD4_itemVar.pikachujoltground.xDDC;
        }
    }
    return NULL;
}

/// #it_802B338C

void it_2725_Logic106_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
}

void it_802B3544(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.pikachujoltground.xDDC = 0;
}

/// #it_802B3554

bool itPikachutjoltground_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE8 = ip->pos;
    return it_80273130(gobj);
}

bool itPikachutjoltground_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_GObj* air_gobj = ip->xDD4_itemVar.pikachujoltground.xDDC;
    bool flag;

    if (air_gobj == NULL) {
        return true;
    }

    if (gobj != NULL && ip != NULL) {
        if (air_gobj == NULL) {
            flag = true;
        } else if (it_802B3EFC(air_gobj) != (u32) gobj) {
            flag = true;
        } else {
            flag = false;
        }
    } else {
        flag = false;
    }

    if (flag == true) {
        return true;
    }

    ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE8 = ip->pos;
    if (it_80273130(gobj) == true) {
        return true;
    }

    it_802B3F20(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos);
    return false;
}

void itPikachutjoltground_UnkMotion0_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itPikachutJoltGroundAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attr->x8 * cosf(ip->xDD4_itemVar.pikachujoltground.xDD4);
    ip->x40_vel.y = attr->x8 * sinf(ip->xDD4_itemVar.pikachujoltground.xDD4);
}

void itPikachutjoltground_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itPikachutjoltground_UnkMotion0_Coll(Item_GObj* gobj)
{
    f32 ground_angle;
    f32 angle_diff;
    f32 facing_dir;
    Item* ip = GET_ITEM(gobj);
    Item* ip2;
    PAD_STACK(8);

    ip->xDD4_itemVar.pikachujoltground.xE00 =
        ip->xDD4_itemVar.pikachujoltground.xDF4;
    if (it_8026E9A4(gobj, &ip->xDD4_itemVar.pikachujoltground.xDE8, &ip->pos,
                    &ip->xDD4_itemVar.pikachujoltground.xDF4) != 0)
    {
        ip2 = GET_ITEM(gobj);
        efLib_DestroyAll(gobj);
        ip2->xDD4_itemVar.pikachujoltground.xDE0 = 0;
        Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
        ip2 = GET_ITEM(gobj);
        ground_angle = atan2f(ip2->xDD4_itemVar.pikachujoltground.xDF4.y,
                              ip2->xDD4_itemVar.pikachujoltground.xDF4.x);
        angle_diff = atan2f(ip2->x40_vel.y, ip2->x40_vel.x) - ground_angle;

        while (angle_diff < 0.0f) {
            angle_diff += 2 * M_PI;
        }
        while (angle_diff > 2 * M_PI) {
            angle_diff -= 2 * M_PI;
        }
        if (angle_diff < M_PI) {
            facing_dir = -1.0f;
        } else {
            facing_dir = 1.0f;
        }
        ip2->xDD4_itemVar.pikachujoltground.xDDC = it_802B4224(
            ip2->owner, gobj, &ip2->pos, ip2->kind + 1, facing_dir);
        ip->xDD4_itemVar.pikachujoltground.xE00 =
            ip->xDD4_itemVar.pikachujoltground.xDF4;
        if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
            return true;
        }
        it_802B3F88(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos,
                    &ip->x378_itemColl,
                    &ip->xDD4_itemVar.pikachujoltground.xDF4);
        ip->xDD4_itemVar.pikachujoltground.xDE4 = 0;
        it_802725D4(gobj);
    }
    return false;
}

bool itPikachutjoltground_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);

    if (ip->xDD4_itemVar.pikachujoltground.xDE4 >= 0) {
        ip->xDD4_itemVar.pikachujoltground.xE00 =
            ip->xDD4_itemVar.pikachujoltground.xDF4;
        if (it_8026E9A4(gobj, &ip->xDD4_itemVar.pikachujoltground.xDE8,
                        &ip->pos,
                        &ip->xDD4_itemVar.pikachujoltground.xDF4) != 0)
        {
            Item* ip2 = GET_ITEM(gobj);
            itPikachutJoltGroundAttributes* attr =
                ip2->xC4_article_data->x4_specialAttributes;
            bool flag;

            if (0.0f == attr->xC) {
                flag = false;
            } else {
                f32 angle =
                    lbVector_Angle(&ip2->xDD4_itemVar.pikachujoltground.xDF4,
                                   &ip2->xDD4_itemVar.pikachujoltground.xE00);
                f32 limit = attr->xC;
                if (limit < 0.0f) {
                    limit = -limit;
                }
                if (angle > limit) {
                    flag = true;
                } else {
                    flag = false;
                }
            }

            if (flag == true) {
                return true;
            }

            if (ip->xDD4_itemVar.pikachujoltground.xDDC == NULL) {
                return true;
            }
            it_802B3F88(ip->xDD4_itemVar.pikachujoltground.xDDC, &ip->pos,
                        &ip->x378_itemColl,
                        &ip->xDD4_itemVar.pikachujoltground.xDF4);
            ip->xDD4_itemVar.pikachujoltground.xDE4 = 0;
        }
    }
    ip->xDD4_itemVar.pikachujoltground.xDE4++;
    return false;
}

bool it_2725_Logic106_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

/// #it_2725_Logic106_Reflected

bool it_2725_Logic106_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_Absorbed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

bool it_2725_Logic106_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.pikachujoltground.xDDC != NULL) {
        it_802B43B0(ip->xDD4_itemVar.pikachujoltground.xDDC);
        ip->xDD4_itemVar.pikachujoltground.xDDC = NULL;
    }
    ip = GET_ITEM(gobj);
    efLib_DestroyAll(gobj);
    ip->xDD4_itemVar.pikachujoltground.xDE0 = 0;
    return true;
}

/// #it_2725_Logic106_ShieldBounced

void itPikachuTJoltGround_Logic106_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
