#include "itpikachutjoltair.h"

#include <placeholder.h>
#include <platform.h>

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/itpikachutjoltground.h"
#include "lb/lb_00B0.h"

#include <baselib/jobj.h>
#include <MSL/math.h>
#include <MSL/trigf.h>

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

void it_802B3F88(Item_GObj* gobj, Vec3* pos, CollData* coll, Vec3* vel)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);

    if (gobj != NULL && ip != NULL) {
        ip->pos = *pos;
        ip->x378_itemColl = *coll;
        ip->xDD4_itemVar.pikachujoltair.xDE8 = *vel;
        ip->xDD4_itemVar.pikachujoltair.xDF4 = 0;
        HSD_JObjSetTranslate(jobj, &ip->pos);
        {
            f32 angle = atan2f(ip->xDD4_itemVar.pikachujoltair.xDE8.x,
                               ip->xDD4_itemVar.pikachujoltair.xDE8.y);
            HSD_JObjSetRotationX(jobj,
                                 (ip->facing_dir == 1.0f) ? angle : -angle);
        }
        Item_80268E5C(gobj, 0, 0x12);
        Item_802694CC(gobj);
        switch (ip->kind) {
        case It_Kind_Kirby_PikachuTJolt_Air:
        case It_Kind_Pikachu_TJolt_Air:
            Item_8026AF0C(ip, 0x3A9CF, 127, 64);
            break;
        case It_Kind_Kirby_PichuTJolt_Air:
        case It_Kind_Pichu_TJolt_Air:
            Item_8026AF0C(ip, 0x382B6, 127, 64);
            break;
        }
    }
}

Item_GObj* it_802B4224(HSD_GObj* owner, Item_GObj* gobj, Vec3* pos, s32 kind,
                       f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    PAD_STACK(8);

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0f;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0f;
    spawn.x0_parent_gobj = owner;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* ip = GET_ITEM(item_gobj);
        HSD_JObj* jobj = item_gobj->hsd_obj;
        ip->xDB8_itcmd_var3 = 0;
        ip->xDB4_itcmd_var2 = 0;
        ip->xDB0_itcmd_var1 = 0;
        ip->xDAC_itcmd_var0 = 0;
        ip->xDD4_itemVar.pikachujoltair.xDD8 = gobj;
        ip->xDD4_itemVar.pikachujoltair.xDF4 = 0;
        HSD_JObjSetRotationY(jobj, (f32) (M_PI_2 * (f64) ip->facing_dir));
        it_802B43D0(item_gobj, owner);
        ip->xDD4_itemVar.pikachujoltair.xDD4 = owner;
    }
    return item_gobj;
}

void it_802B43B0(Item_GObj* gobj)
{
    if (gobj != NULL) {
        Item* ip = GET_ITEM(gobj);
        if (ip != NULL) {
            ip->xDD4_itemVar.pikachujoltair.xDD8 = 0;
        }
    }
}

void it_802B43D0(Item_GObj* gobj, HSD_GObj* arg1)
{
    Item* ip = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    ip->xDC8_word.flags.x13 = 0;
    it_80272940(gobj);
    Item_80268E5C((HSD_GObj*) gobj, 0, 2);
    Item_802694CC((HSD_GObj*) gobj);
    db_80225DD8(gobj, arg1);
}

static inline void itPikachuTJoltAir_Destroy(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_GObj* linked = ip->xDD4_itemVar.pikachujoltair.xDD8;

    it_802725D4(gobj);
    if (linked != NULL) {
        it_802B3544(linked);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = NULL;
    }
}

static inline void itPikachuTJoltAir_Anim_Destroy(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    Item_GObj* linked;

    it_802725D4(gobj);
    linked = ip->xDD4_itemVar.pikachujoltair.xDD8;
    if (linked != NULL) {
        it_802B3544(linked);
        ip->xDD4_itemVar.pikachujoltair.xDD8 = NULL;
    }
}

static inline bool itPikachutjoltair_UnkMotion0_Anim_inline(Item_GObj* gobj)
{
    Item_GObj* linked = GET_ITEM(gobj)->xDD4_itemVar.pikachujoltair.xDD8;
    if (linked == NULL) {
        return true;
    }
    if (it_802B3368(linked) != gobj) {
        return true;
    }
    return false;
}

bool itPikachutjoltair_UnkMotion0_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 angle;
    PAD_STACK(8);

    angle = atan2f(ip->xDD4_itemVar.pikachujoltair.xDE8.x,
                   ip->xDD4_itemVar.pikachujoltair.xDE8.y);
    HSD_JObjSetRotationX(jobj, (ip->facing_dir == 1.0f) ? angle : -angle);
    ip->xDD4_itemVar.pikachujoltair.xDF4++;
    if (!((ip->xDD4_itemVar.pikachujoltair.xDF4 <= 24) &&
          (itPikachutjoltair_UnkMotion0_Anim_inline(gobj) != true)))
    {
        itPikachuTJoltAir_Anim_Destroy(gobj);
        return true;
    }
    return false;
}

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

bool it_2725_Logic107_Reflected(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    f32 rot;
    f32 angle;
    PAD_STACK(16);

    lb_8000B1CC(ip->xBBC_dynamicBoneTable->bones[6], NULL, &ip->pos);
    ip->facing_dir = -ip->facing_dir;

    if (ip->facing_dir == 1.0f) {
        rot = HSD_JObjGetRotationX(jobj);
    } else {
        rot = -HSD_JObjGetRotationX(jobj);
    }

    angle = rot +
            (M_PI - HSD_JObjGetRotationX(ip->xBBC_dynamicBoneTable->bones[4]));

    while (angle < 0.0f) {
        angle += M_TAU;
    }
    while (angle > M_TAU) {
        angle -= M_TAU;
    }

    HSD_JObjSetRotationX(jobj, angle);
    HSD_JObjSetRotationY(jobj, (M_PI_2 * ip->facing_dir));
    HSD_JObjSetTranslate(jobj, &ip->pos);

    if (ip->facing_dir == 1.0f) {
        ip->xDD4_itemVar.pikachujoltair.xDE8.x = sinf(angle);
        ip->xDD4_itemVar.pikachujoltair.xDE8.y = cosf(angle);
    } else {
        ip->xDD4_itemVar.pikachujoltair.xDE8.x = sinf(-angle);
        ip->xDD4_itemVar.pikachujoltair.xDE8.y = cosf(-angle);
    }
    ip->xDD4_itemVar.pikachujoltair.xDE8.z = 0.0f;
    ip->xDD4_itemVar.pikachujoltair.xDF4 = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    return false;
}

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
