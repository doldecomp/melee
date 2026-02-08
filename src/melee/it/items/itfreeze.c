#include "itfreeze.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itwhitebea.h"

/// #it_8028EB88

void it_8028EC98(Item_GObj* gobj, f32 vel)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.freeze.x10 = vel;
    it_80275158(gobj, (f32) it_804D6D28->x30);
}

void it_8028ECE0(Item_GObj* gobj)
{
    GET_ITEM(gobj)->xDD4_itemVar.freeze.unk_1C = NULL;
}

Item* it_8028ECF0(Item_GObj* gobj, Vec3* v)
{
    Item* ip = GET_ITEM(gobj);
    v->x = ip->pos.x;
    v->y = ip->pos.y;
    v->z = ip->pos.z;
    return ip;
}

void itFreeze_Logic17_Destroyed(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->xDD4_itemVar.freeze.unk_1C != NULL) {
        it_802E37A4(ip->xDD4_itemVar.freeze.unk_1C);
        ip->xDD4_itemVar.freeze.unk_1C = NULL;
    }
}

void it_3F14_Logic17_Spawned(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    if (ip->pos.x > 0.0f) {
        ip->facing_dir = -1.0f;
    } else {
        ip->facing_dir = 1.0f;
    }
    ip->xD5C = 0;
    ip->xDD4_itemVar.freeze.x0 = 0.0f;
    ip->xDD4_itemVar.freeze.x4.x = 0.0f;
    ip->xDD4_itemVar.freeze.x4.y = 1.0f;
    ip->xDD4_itemVar.freeze.x4.z = 0.0f;
    ip->xDD4_itemVar.freeze.unk_1C = NULL;
    it_8028F1D8(gobj);
}

/// #it_8028EDBC

void it_8028EF34(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.x = ip->xDD4_itemVar.freeze.x0;
    ip->x40_vel.z = 0.0F;
    ip->x40_vel.y = 0.0F;
    it_8026B390(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion0_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion0_Phys(Item_GObj* gobj)
{
    it_8028EDBC(gobj);
}

/// #itFreeze_UnkMotion0_Coll

void it_8028F1D8(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ItemAttr* attrs = ip->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFreeze_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    CollData* cd = &it->x378_itemColl;

    it_8026E414(gobj, it_8028EF34);
    if (it->ground_or_air != GA_Air && (cd->env_flags & Collide_FloorMask)) {
        it_80276408(gobj, cd, &it->xDD4_itemVar.freeze.x4);
    }
    return false;
}

void itFreeze_Logic17_PickedUp(Item_GObj* gobj)
{
    Item* item = gobj->user_data;
    Item_GObj* linked;

    if ((linked = item->xDD4_itemVar.freeze.unk_1C) != NULL) {
        it_802E37A4(linked);
        item->xDD4_itemVar.freeze.unk_1C = NULL;
    }

    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_Logic17_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
}

void itFreeze_Logic17_Thrown(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 3, 6);
}

void itFreeze_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip;
    ItemAttr* it_attr;

    ip = gobj->user_data;
    it_attr = ip->xCC_item_attr;
    it_80272860(gobj, it_attr->x10_fall_speed, it_attr->x14_fall_speed_max);
}

bool itFreeze_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DAA8(gobj) != 0) {
        return 1;
    }
    return 0;
}

bool itFreeze_Logic17_DmgDealt(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Clanked(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_HitShield(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Absorbed(Item_GObj* arg0)
{
    return true;
}

bool itFreeze_Logic17_Reflected(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool itFreeze_Logic17_ShieldBounced(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

bool itFreeze_Logic17_DmgReceived(Item_GObj* arg0)
{
    return true;
}

void it_8028F434(Item_GObj* gobj, f32 vel, Item_GObj* ref_gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    if (vel < 0.0f) {
        vel = -vel;
    }
    ip->xDD4_itemVar.freeze.x14 = vel;
    ip->xDD4_itemVar.freeze.unk_1C = ref_gobj;
    it_8026B390(gobj);
    it_802762B0(ip);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 decel;
    f32 abs_decel;
    f32 vel;
    f32 abs_vel;

    if (ip->xDD4_itemVar.freeze.x10 != 0.0f) {
        ip->x40_vel.x = ip->xDD4_itemVar.freeze.x10;
        ip->xDD4_itemVar.freeze.x10 = 0.0f;
    }

    decel = ip->xDD4_itemVar.freeze.x14;

    if (decel < 0.0f) {
        abs_decel = -decel;
    } else {
        abs_decel = decel;
    }

    vel = ip->x40_vel.x;

    if (vel < 0.0f) {
        abs_vel = -vel;
    } else {
        abs_vel = vel;
    }

    if (abs_vel < abs_decel) {
        ip->x40_vel.x = 0.0f;
        return;
    }

    if (vel > 0.0f) {
        if (decel < 0.0f) {
            decel = -decel;
        }
        ip->x40_vel.x -= decel;
    } else {
        if (decel < 0.0f) {
            decel = -decel;
        }
        ip->x40_vel.x += decel;
    }
}

/// #itFreeze_UnkMotion4_Coll

void it_8028F7C8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_8026B390(gobj);
    ip->xDD4_itemVar.freeze.x18 = 90;
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itFreeze_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itFreeze_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itFreeze_UnkMotion5_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(8);
    it_8026D62C(gobj, it_8028F1D8);
    if (ip->xDD4_itemVar.freeze.x18 <= 0) {
        Item* ip2 = GET_ITEM(gobj);
        ip2->x40_vel.x = ip2->xDD4_itemVar.freeze.x0;
        ip2->x40_vel.z = 0.0f;
        ip2->x40_vel.y = 0.0f;
        it_8026B390(gobj);
        Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    } else {
        ip->xDD4_itemVar.freeze.x18--;
    }
    return false;
}

void itFreeze_Logic17_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}

void it_8028F8E4(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 pos;
    ip->xDCC_flag.b3 = true;
    it_8026B390(gobj);
    ip->x378_itemColl.cur_pos = ip->pos;
    pos = ip->pos;
    it_80276100(gobj, &pos);
}

void it_8028F968(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80273454(gobj);
    ip->xDCC_flag.b3 = 0;
    it_8026B3A8(gobj);
}

void it_8028F9B8(Item_GObj* gobj)
{
    Item_8026A8EC(gobj);
}
