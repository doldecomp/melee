#include "itmariofireball.h"

#include "db/db_2253.h"
#include "ef/efasync.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <common_structs.h>
#include <math.h>
#include <math_ppc.h>
#include <dolphin/mtx/vec.h>
#include <baselib/gobj.h>

ItemStateTable it_803F6788[] = {
    { 0, it_8029B868, it_8029B8A0, it_8029B8EC },
};

void it_8029B6F8(Item_GObj* gobj, Vec3* pos, ItemKind kind, f32 facing_dir)
{
    Item_GObj* spawned_gobj;

    SpawnItem spawn_item;
    spawn_item.kind = kind;
    spawn_item.prev_pos = *pos;
    spawn_item.prev_pos.z = 0.0f;
    it_8026BB68(gobj, &spawn_item.pos);
    spawn_item.facing_dir = facing_dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0f;
    spawn_item.x0_parent_gobj = gobj;
    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.b0 = true;
    spawn_item.x40 = 0;

    spawned_gobj = Item_80268B18(&spawn_item);
    it_8029B7C0(spawned_gobj);
    db_80225DD8(spawned_gobj, gobj);
    it_802750F8(spawned_gobj);
}

void it_8029B7C0(Item_GObj* gobj)
{
    Item* it = GET_ITEM(gobj);
    itUnkAttributes* ap = it->xC4_article_data->x4_specialAttributes;
    f32 x0 = ap->x0_float;
    f32 x4 = ap->x4_float;

    it->x40_vel.x = it->facing_dir * (x0 * cosf(x4));
    it->x40_vel.y = x0 * sinf(x4);
    it->x40_vel.z = 0.0f;

    it_80275158(gobj, ap->x8);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_8029B868(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    --item->xD44_lifeTimer;
    return item->xD44_lifeTimer <= 0 ? true : false;
}

void it_8029B8A0(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
    it_80274658(gobj, it_804D6D28->x68_float);
}

static double calc_dist_2d_accurate(Vec3* v)
{
    return sqrtf_accurate(VEC2_SQ_LEN(*v));
}

bool it_8029B8EC(Item_GObj* gobj)
{
    it_8026D9A0(gobj);
    if (it_8027781C(gobj)) {
        Item* it = GET_ITEM(gobj);
        HSD_JObj* jobj = GET_JOBJ(gobj);
        itUnkAttributes* attrs = it->xC4_article_data->x4_specialAttributes;
        if (calc_dist_2d_accurate(&it->x40_vel) < attrs->x10) {
            return true;
        }
        if (it->kind == It_Kind_Mario_Fire) {
            Item_8026AE84(it, ~0xFFFD40C6, 0x7f,
                          0x40); // What the fuck is this ID?
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1147, jobj);
        } else {
            efAsync_Spawn(gobj, &(GET_ITEM(gobj)->xBC0), 1, 1184, jobj);
        }
    }
    return false;
}

bool it_8029BA38(Item_GObj* gobj)
{
    return true;
}

bool it_8029BA40(Item_GObj* gobj)
{
    return it_80273030(gobj);
}

bool it_8029BA60(Item_GObj* gobj)
{
    return true;
}

bool it_8029BA68(Item_GObj* gobj)
{
    return true;
}

bool it_8029BA70(Item_GObj* gobj)
{
    return true;
}

bool it_8029BA78(Item_GObj* gobj)
{
    return itColl_BounceOffShield(gobj);
}

void it_8029BA98(Item_GObj* gobj, HSD_GObj* referenced_gobj)
{
    it_8026B894(gobj, referenced_gobj);
}
