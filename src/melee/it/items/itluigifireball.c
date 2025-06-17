#include <platform.h>

#include "itluigifireball.h"

#include "db/db.h"
#include "ef/efasync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <common_structs.h>
#include <math_ppc.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/mtx.h>

/* 2C027C */ static void it_802C027C(Item_GObj* gobj);
/* 2C02E4 */ static bool it_802C02E4(Item_GObj* gobj);
/* 2C031C */ static void it_802C031C(Item_GObj* gobj);
/* 2C0368 */ static bool it_802C0368(Item_GObj* gobj);

ItemStateTable it_803F75C0[] = {
    { 0, it_802C02E4, it_802C031C, it_802C0368 },
};

void it_802C01AC(Item_GObj* gobj, Vec3* pos, ItemKind kind, float facing_dir)
{
    SpawnItem spawn_item;
    spawn_item.kind = kind;
    spawn_item.prev_pos = *pos;
    spawn_item.prev_pos.z = 0;
    it_8026BB68(gobj, &spawn_item.pos);
    spawn_item.facing_dir = facing_dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0;
    spawn_item.x0_parent_gobj = gobj;
    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.b0 = true;
    spawn_item.x40 = 0;
    {
        u8 _[8] = { 0 };
        Item_GObj* spawned_gobj = Item_80268B18(&spawn_item);
        if (spawned_gobj != NULL) {
            it_802C027C(spawned_gobj);
            db_80225DD8(spawned_gobj, gobj);
            it_802750F8(spawned_gobj);
        }
    }
}

void it_802C027C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    itUnkAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
    ip->x40_vel.x = attrs->x0_float * ip->facing_dir;
    ip->x40_vel.y = ip->x40_vel.z = 0;
    it_80275158(gobj, attrs->x4_float);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802C02E4(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    --item->xD44_lifeTimer;
    return item->xD44_lifeTimer <= 0 ? true : false;
}

void it_802C031C(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static double calc_dist_2d_accurate(Vec3* v)
{
    return sqrtf_accurate(VEC2_SQ_LEN(*v));
}

bool it_802C0368(Item_GObj* gobj)
{
    it_8026D9A0(gobj);
    if (it_8027781C(gobj)) {
        Item* ip = GET_ITEM(gobj);
        HSD_JObj* jobj = GET_JOBJ(gobj);
        itUnkAttributes* attrs = ip->xC4_article_data->x4_specialAttributes;
        if (calc_dist_2d_accurate(&ip->x40_vel) < attrs->xC) {
            return true;
        }
        if (ip->kind == It_Kind_Luigi_Fire) {
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1288, jobj);
        } else {
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1202, jobj);
        }
    }
    return false;
}

bool it_802C0490(Item_GObj* gobj)
{
    return true;
}

bool it_802C0498(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_802C04B8(Item_GObj* gobj)
{
    return true;
}

bool it_802C04C0(Item_GObj* gobj)
{
    return true;
}

bool it_802C04C8(Item_GObj* gobj)
{
    return true;
}

bool it_802C04D0(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_802C04F0(Item_GObj* gobj, HSD_GObj* referenced_gobj)
{
    it_8026B894(gobj, referenced_gobj);
}
