#include "itseakneedlethrown.h"

#include "placeholder.h"

#include "db/db.h"
#include "ft/ftlib.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "lb/lbvector.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <baselib/jobj.h>
#include <baselib/random.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

Item_GObj* it_802AFD8C(Item_GObj* parent, Vec3* pos, u32 kind,
                       float facing_dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        it_80275158(item_gobj, ((itSeakNeedleThrownAttributes*)
                                    ip->xC4_article_data->x4_specialAttributes)
                                   ->x0);
        ip->xDD4_itemVar.seakneedlethrown.xDF4 = -1;
        ip->xDD4_itemVar.seakneedlethrown.xDFC = 0.0f;
        ip->xDD4_itemVar.seakneedlethrown.xDF8 = 0.0f;
        ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
        it_8026BD6C(item_gobj);
    }
    return item_gobj;
}

void it_802AFEA8(Item_GObj* gobj, Fighter_GObj* owner_gobj, u32 arg2)
{
    if (gobj && owner_gobj) {
        switch (arg2) {
        case 0:
            it_802AFF08(gobj, owner_gobj);
            break;
        case 1:
            it_802B00F4(gobj, owner_gobj);
            break;
        }
    }
}

void itSeakNeedleThrown_Logic109_Destroyed(Item_GObj* gobj)
{
    GET_ITEM(gobj)->owner = NULL;
}

void it_802AFF08(Item_GObj* gobj, Fighter_GObj* owner)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    f32 angle;

    ip->owner = owner;
    it_8026B3A8(gobj);
    ip->xDCE_flag.b5 = false;
    it_80272940(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026BD6C(gobj);
    it_80275158(gobj, attr->x0);

    angle = (ftLib_800865CC(owner)) ? 2.3561945f : M_PI_2;
    ip->xDD4_itemVar.seakneedlethrown.xDF0 =
        (ip->facing_dir * angle) + (f32) M_PI_2;
    ip->x40_vel.x = -attr->x8 * cosf(ip->xDD4_itemVar.seakneedlethrown.xDF0);
    ip->x40_vel.y = attr->x8 * sinf(ip->xDD4_itemVar.seakneedlethrown.xDF0);
    ip->x40_vel.z = 0.0f;
    ip->xDD4_itemVar.seakneedlethrown.xDE4.x =
        -(3.0f * ip->x40_vel.x - ip->pos.x);
    ip->xDD4_itemVar.seakneedlethrown.xDE4.y =
        -(3.0f * ip->x40_vel.y - ip->pos.y);
    ip->xDD4_itemVar.seakneedlethrown.xDE4.z = 0.0f;
    {
        f32 rot = -ip->facing_dir *
                  atan2f(ip->pos.y - ip->xDD4_itemVar.seakneedlethrown.xDE4.y,
                         ip->pos.x - ip->xDD4_itemVar.seakneedlethrown.xDE4.x);
        HSD_JObjSetRotationX(child, rot);
    }
    db_80225DD8(gobj, owner);
}

static inline void itSeakNeedleThrown_SetupBounce(Item_GObj* gobj,
                                                  itSeakNeedleThrownData* data)
{
    Item* ip = GET_ITEM(gobj);
    f32 rand_sign = (HSD_Randi(2) == 0) ? 1.0f : -1.0f;
    ip->xDD4_itemVar.seakneedlethrown.xDD4 =
        data->x110[HSD_Randi(8)] * rand_sign;
    rand_sign = (HSD_Randi(2) == 0) ? 1.0f : -1.0f;
    ip->xDD4_itemVar.seakneedlethrown.xDD8 =
        data->xB0[HSD_Randi(8)] * rand_sign;
    ip->xDD4_itemVar.seakneedlethrown.xDDC = data->xD0[HSD_Randi(8)];
    ip->xDD4_itemVar.seakneedlethrown.xDE0 = data->xF0[HSD_Randi(8)];
}

static inline void itSeakNeedleThrown_SetupDrop(Item_GObj* gobj,
                                                itSeakNeedleThrownData* data)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.seakneedlethrown.xDD4 =
        data->x90[HSD_Randi(8)] * ((HSD_Randi(2) == 0) ? 1.0f : -1.0f);
    ip->xDD4_itemVar.seakneedlethrown.xDD8 = 0.0f;
    ip->xDD4_itemVar.seakneedlethrown.xDDC = data->x50[HSD_Randi(8)];
    ip->xDD4_itemVar.seakneedlethrown.xDE0 = data->x70[HSD_Randi(8)];
}

void it_802B00F4(Item_GObj* gobj, Fighter_GObj* owner)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;
    PAD_STACK(8);

    ip->owner = owner;
    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = false;
    it_80272940(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026BD6C(gobj);
    it_80275158(gobj, attr->x0);
    itResetVelocity(ip);

    itSeakNeedleThrown_SetupDrop(gobj, data);
    db_80225DD8(gobj, owner);
}

bool itSeakneedlethrown_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
    return it_80273130(gobj);
}

bool itSeakneedlethrown_UnkMotion1_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_JObjGetChild(GET_JOBJ(gobj));
    ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
    HSD_JObjAddRotationX(jobj, ip->xDD4_itemVar.seakneedlethrown.xDD4);
    return it_80273130(gobj);
}

bool itSeakneedlethrown_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    PAD_STACK(8);
    ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
    HSD_JObjSetRotationX(child, ip->xDD4_itemVar.seakneedlethrown.xDF0);
    return it_80273130(gobj);
}

bool itSeakneedlethrown_UnkMotion3_Anim(Item_GObj* gobj)
{
    return it_80273130(gobj);
}

bool itSeakneedlethrown_UnkMotion4_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = HSD_JObjGetChild(GET_JOBJ(gobj));
    ip->xDD4_itemVar.seakneedlethrown.xDE4 = ip->pos;
    HSD_JObjAddRotationX(jobj, ip->xDD4_itemVar.seakneedlethrown.xDD4);
    return false;
}

void itSeakneedlethrown_UnkMotion0_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion1_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

void itSeakneedlethrown_UnkMotion2_Phys(Item_GObj* gobj) {}

void itSeakneedlethrown_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itResetVelocity(ip);
}

bool itSeakneedlethrown_UnkMotion3_Coll(Item_GObj* gobj)
{
    return false;
}

void itSeakneedlethrown_UnkMotion4_Phys(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->x40_vel.x = ip->xDD4_itemVar.seakneedlethrown.xDD8;
    ip->x40_vel.y += ip->xDD4_itemVar.seakneedlethrown.xDE0;
    if (ip->x40_vel.y < ip->xDD4_itemVar.seakneedlethrown.xDDC) {
        ip->x40_vel.y = ip->xDD4_itemVar.seakneedlethrown.xDDC;
    }
}

static inline bool itSeakNeedleThrown_CheckGroundHit(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Vec3 hit_pos;
    u32 line_id;

    if (it_8026EA20(gobj, &ip->xDD4_itemVar.seakneedlethrown.xDE4, &ip->pos,
                    &hit_pos, &ip->xDD4_itemVar.seakneedlethrown.xDF4,
                    &line_id) &&
        mpLib_80054ED8(ip->xDD4_itemVar.seakneedlethrown.xDF4))
    {
        mpColl_80043558(&ip->x378_itemColl,
                        ip->xDD4_itemVar.seakneedlethrown.xDF4);
        mpGetSpeed(ip->xDD4_itemVar.seakneedlethrown.xDF4, &ip->pos,
                   &ip->x40_vel);
        {
            f32 angle = atan2f(hit_pos.y, hit_pos.x);
            ip->xDD4_itemVar.seakneedlethrown.xDFC = angle;
            ip->xDD4_itemVar.seakneedlethrown.xDF8 = angle;
        }
        return true;
    }
    return false;
}

bool itSeakneedlethrown_UnkMotion0_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    f32 rot = -ip->facing_dir *
              atan2f(ip->pos.y - ip->xDD4_itemVar.seakneedlethrown.xDE4.y,
                     ip->pos.x - ip->xDD4_itemVar.seakneedlethrown.xDE4.x);
    HSD_JObjSetRotationX(child, rot);
    if (itSeakNeedleThrown_CheckGroundHit(gobj)) {
        switch (HSD_Randi(5)) {
        case 0:
        case 1:
        case 2:
            it_802762BC(ip);
            itResetVelocity(ip);
            it_80275158(gobj, attr->x4);
            ip->xDD4_itemVar.seakneedlethrown.xDF0 = rot;
            Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
            Item_8026AE84(ip, 0x41F39, 127, 64);
            break;
        case 3:
        case 4:
            it_80275158(gobj, attr->x4);
            ip->x40_vel.y = ABS(data->xD0[HSD_Randi(8)]);
            it_802762BC(ip);
            itSeakNeedleThrown_SetupBounce(gobj, data);
            Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
            break;
        }
    }
    return false;
}

bool itSeakneedlethrown_UnkMotion1_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;
    if (itSeakNeedleThrown_CheckGroundHit(gobj)) {
        it_80275158(gobj, attr->x4);
        ip->x40_vel.y = ABS(ip->x40_vel.y);
        it_802762BC(ip);
        itSeakNeedleThrown_SetupBounce(gobj, data);
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        Item_8026AE84(ip, 0x41F39, 127, 64);
    }
    return false;
}

static inline void itSeakNeedleThrown_Coll2_Inline(Item_GObj* gobj,
                                                   HSD_JObj* child)
{
    Item* ip = GET_ITEM(gobj);
    CollData* coll = &ip->x378_itemColl;
    Vec3 normal;

    ip->xDD4_itemVar.seakneedlethrown.xDFC =
        ip->xDD4_itemVar.seakneedlethrown.xDF8;
    if (ip->xDD4_itemVar.seakneedlethrown.xDF4 != -1) {
        if (mpLib_80054ED8(ip->xDD4_itemVar.seakneedlethrown.xDF4)) {
            mpColl_80043558(coll, ip->xDD4_itemVar.seakneedlethrown.xDF4);
            mpGetSpeed(ip->xDD4_itemVar.seakneedlethrown.xDF4, &ip->pos,
                       &ip->x40_vel);
            mpLineGetNormal(ip->xDD4_itemVar.seakneedlethrown.xDF4, &normal);
            ip->xDD4_itemVar.seakneedlethrown.xDF8 =
                atan2f(normal.y, normal.x);
        }
    } else {
        itResetVelocity(ip);
    }
    if (ip->xDD4_itemVar.seakneedlethrown.xDF8 !=
        ip->xDD4_itemVar.seakneedlethrown.xDFC)
    {
        ip->xDD4_itemVar.seakneedlethrown.xDF0 +=
            ip->xDD4_itemVar.seakneedlethrown.xDF8 -
            ip->xDD4_itemVar.seakneedlethrown.xDFC;
        HSD_JObjSetRotationX(child, ip->xDD4_itemVar.seakneedlethrown.xDF0);
    }
}

bool itSeakneedlethrown_UnkMotion2_Coll(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    it_802762BC(ip);
    itResetVelocity(ip);
    itSeakNeedleThrown_Coll2_Inline(gobj, child);
    return false;
}

bool itSeakneedlethrown_UnkMotion4_Coll(Item_GObj* gobj)
{
    Item* ip = HSD_GObjGetUserData(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    HSD_JObj* child = HSD_JObjGetChild(gobj->hsd_obj);
    PAD_STACK(8);
    if (itSeakNeedleThrown_CheckGroundHit(gobj) != 0) {
        it_80275158(gobj, attr->x4);
        ip->xDD4_itemVar.seakneedlethrown.xDF0 = HSD_JObjGetRotationX(child);
        Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
        it_802762BC(ip);
        itResetVelocity(ip);
    }
    return false;
}

bool it_2725_Logic109_DmgDealt(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;

    if (HSD_Randi(3) == 0) {
        it_80272560(gobj, 0);
        it_80275158(gobj, attr->x4);
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = ABS(data->xD0[HSD_Randi(8)]);
        it_802762BC(ip);
        itSeakNeedleThrown_SetupBounce(gobj, data);
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        return false;
    }
    return true;
}

bool it_2725_Logic109_Clanked(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;

    if (HSD_Randi(3) == 0) {
        it_80272560(gobj, 0);
        it_80275158(gobj, attr->x4);
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = ABS(data->xD0[HSD_Randi(8)]);
        it_802762BC(ip);
        itSeakNeedleThrown_SetupBounce(gobj, data);
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        return false;
    }
    return true;
}

bool it_2725_Logic109_DmgReceived(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    itSeakNeedleThrownData* data = &it_803F6F50;

    if (HSD_Randi(3) == 0) {
        it_80272560(gobj, 0);
        it_80275158(gobj, attr->x4);
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = ABS(data->xD0[HSD_Randi(8)]);
        it_802762BC(ip);
        itSeakNeedleThrown_SetupBounce(gobj, data);
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        return false;
    }
    return true;
}

bool it_2725_Logic109_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;
    f32 dx, dy;
    f32 angle;
    PAD_STACK(16);

    ip->facing_dir = -ip->facing_dir;
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);

    dx = ip->pos.x - ip->xDD4_itemVar.seakneedlethrown.xDE4.x;
    dy = ip->pos.y - ip->xDD4_itemVar.seakneedlethrown.xDE4.y;
    ip->xDD4_itemVar.seakneedlethrown.xDE4.x = ip->pos.x + dx;
    ip->xDD4_itemVar.seakneedlethrown.xDE4.y = ip->pos.y + dy;
    ip->xDD4_itemVar.seakneedlethrown.xDE4.z = 0.0f;

    {
        f32 rot = -ip->facing_dir *
                  atan2f(ip->pos.y - ip->xDD4_itemVar.seakneedlethrown.xDE4.y,
                         ip->pos.x - ip->xDD4_itemVar.seakneedlethrown.xDE4.x);
        HSD_JObjSetRotationX(HSD_JObjGetChild(jobj), rot);
    }

    angle = atan2f(ip->pos.y - ip->xDD4_itemVar.seakneedlethrown.xDE4.y,
                   ip->pos.x - ip->xDD4_itemVar.seakneedlethrown.xDE4.x);
    ip->x40_vel.x = attr->x8 * cosf(angle);
    ip->x40_vel.y = attr->x8 * sinf(angle);
    ip->xD44_lifeTimer = ip->xD48_halfLifeTimer;

    return false;
}

bool it_2725_Logic109_ShieldBounced(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObj* child;
    f32 angle;
    f32 facing;

    lbVector_Mirror(&ip->x40_vel, &ip->xC58);
    angle = atan2f(ip->x40_vel.y, ip->x40_vel.x);
    while (angle < 0.0f) {
        angle += M_TAU;
    }
    while (angle > M_TAU) {
        angle -= M_TAU;
    }
    ip->facing_dir = (ip->x40_vel.x >= 0.0f) ? 1.0f : -1.0f;

    HSD_JObjSetRotationX(HSD_JObjGetChild(jobj), angle * -ip->facing_dir);
    HSD_JObjSetRotationY(jobj, M_PI_2 * ip->facing_dir);
    return false;
}

bool it_2725_Logic109_HitShield(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itSeakNeedleThrownData* data = &it_803F6F50;
    itSeakNeedleThrownAttributes* attr =
        ip->xC4_article_data->x4_specialAttributes;

    if (HSD_Randi(3) == 0) {
        it_80272560(gobj, 0);
        it_80275158(gobj, attr->x4);
        ip->x40_vel.z = 0.0f;
        ip->x40_vel.x = 0.0f;
        ip->x40_vel.y = ABS(data->xD0[HSD_Randi(8)]);
        it_802762BC(ip);
        itSeakNeedleThrown_SetupBounce(gobj, data);
        Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
        return false;
    }
    return true;
}

void itSeakNeedleThrown_Logic109_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
