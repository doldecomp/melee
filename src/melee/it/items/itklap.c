#include "itklap.h"

#include "gr/grkongo.h"
#include "gr/ground.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itcoll.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"

#include <math.h>
#include <baselib/random.h>

ItemStateTable it_803F8940[] = {
    { 0, itKlap_UnkMotion1_Anim, itKlap_UnkMotion1_Phys,
      itKlap_UnkMotion1_Coll },
    { 1, itKlap_UnkMotion1_Anim, itKlap_UnkMotion1_Phys,
      itKlap_UnkMotion1_Coll },
    { 2, itKlap_UnkMotion2_Anim, itKlap_UnkMotion2_Phys,
      itKlap_UnkMotion2_Coll },
    { 3, itKlap_UnkMotion3_Anim, itKlap_UnkMotion3_Phys,
      itKlap_UnkMotion3_Coll },
    { 2, itKlap_UnkMotion4_Anim, itKlap_UnkMotion4_Phys,
      itKlap_UnkMotion4_Coll },
};

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

bool itKlap_UnkMotion1_Coll(Item_GObj* gobj)
{
    Vec3 pos;
    Quaternion quat;
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* child;

    if (ip->xDD4_itemVar.klap.x20 != NULL) {
        HSD_JObj* ref_jobj = GET_JOBJ(ip->xDD4_itemVar.klap.x20);
        HSD_JObjGetTranslation2(ref_jobj, &pos);
        HSD_JObjGetRotation(ref_jobj, &quat);
        pos.y -= 5.0;
        ip->pos = pos;
        HSD_JObjSetTranslate(jobj, &pos);
        HSD_JObjSetRotation(jobj, &quat);
    } else {
        it_802E1C84(gobj);
    }

    if ((child = HSD_JObjGetChild(jobj))) {
        lb_8000B1CC(child, NULL, &pos);
        if (pos.z >= 0.0f) {
            it_802E1C84(gobj);
        }
    }
    return false;
}

void it_802E1C4C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

void it_802E1C84(Item_GObj* gobj)
{
    Vec3 pos;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child;

    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    ip->xDCC_flag.b3 = true;

    child = HSD_JObjGetChild(jobj);
    lb_8000B1CC(child, NULL, &pos);
    ip->pos = pos;
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itKlap_UnkMotion2_Anim(Item_GObj* gobj)
{
    return false;
}

void itKlap_UnkMotion2_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 rot;
    f32 diff;

    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    rot = HSD_JObjGetRotationX(jobj);
    diff = 1.5707964f - rot;
    if (diff > 0.034906585f) {
        rot += 0.034906585f;
    } else if (diff < -0.034906585f) {
        rot -= 0.034906585f;
    } else {
        rot = 1.5707964f;
    }
    HSD_JObjSetRotationX(jobj, rot);
}

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

void it_802E1E94(Item_GObj* gobj)
{
    f32 rand_val;
    Item* ip = GET_ITEM(gobj);
    it_802762BC(ip);
    if (it_8027B798(gobj, &ip->x40_vel)) {
        it_802762BC(ip);
    }
    rand_val = HSD_Randf();
    ip->xDD4_itemVar.klap.x24 = (rand_val - 0.5f) * 0.17453292f;
    rand_val = HSD_Randf();
    ip->xDD4_itemVar.klap.x28 = (rand_val - 0.5f) * 0.17453292f;
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

bool itKlap_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itKlap_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    Quaternion quat;
    PAD_STACK(4);

    ip->x40_vel.y -= ip->xCC_item_attr->x10_fall_speed;
    HSD_JObjGetRotation(jobj, &quat);
    quat.y += ip->xDD4_itemVar.klap.x24;
    if (quat.y > (2 * M_PI)) {
        quat.y -= (2 * M_PI);
    } else if (quat.y < -(2 * M_PI)) {
        quat.y += (2 * M_PI);
    }
    quat.z += ip->xDD4_itemVar.klap.x28;
    if (quat.z > (2 * M_PI)) {
        quat.z -= (2 * M_PI);
    } else if (quat.z < -(2 * M_PI)) {
        quat.z += (2 * M_PI);
    }
    HSD_JObjSetRotation(jobj, &quat);
}

bool itKlap_UnkMotion4_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802E20D8(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.z = 0.0f;
    ip->x40_vel.y = 0.0f;
    ip->x40_vel.x = 0.0f;
    it_802762BC(ip);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
    it_802756D0(gobj);
    ip->on_accessory = it_802E215C;
}

bool itKlap_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itKlap_UnkMotion3_Phys(Item_GObj* gobj) {}

bool itKlap_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

void it_802E215C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 angle;
    Vec3 pos;
    Quaternion quat;

    Ground_801C4DA0(&pos, &angle);
    pos.x += 6.0f * -sinf(angle);
    pos.y += 6.0f * cosf(angle);
    ip->pos = pos;
    HSD_JObjSetTranslate(jobj, &ip->pos);
    quat.x = 1.5707964f;
    quat.z = angle;
    quat.w = 0.0f;
    quat.y = 0.0f;
    HSD_JObjSetRotation(jobj, &quat);
}

static inline void it_802E2330_inline(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    f32 rand;
    it_802762BC(ip);
    if (it_8027B798(gobj, &ip->x40_vel)) {
        it_802762BC(ip);
    }
    rand = HSD_Randf();
    ip->xDD4_itemVar.klap.x24 = 0.17453292f * (rand - 0.5f);
    rand = HSD_Randf();
    ip->xDD4_itemVar.klap.x28 = 0.17453292f * (rand - 0.5f);
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
}

void it_802E2330(Item_GObj* gobj, Vec3* pos, lbColl_80008D30_arg1* arg2,
                 f32 angle)
{
    struct SmallerHitCapsule hit;
    Item* ip = GET_ITEM(gobj);
    PAD_STACK(4);

    ip->pos = *pos;
    lbColl_80008D30((HitCapsule*) &hit, arg2);
    Item_80269CA0(ip, hit.damage);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    ip->xCC8_knockback = it_80270CD8(ip, (HitCapsule*) &hit);
    ip->xCAC_angle = angle;
    ip->xCCC_incDamageDirection = ip->facing_dir;
    it_802E2330_inline(gobj);
}

void it_802E2450(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
