#include "lb/forward.h"

#include "itfoxlaser.h"

#include "it/inlines.h"
#include "it/itCharItems.h"
#include "it/types.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/db/db_2253.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/lb/lbrefract.h>
#include <melee/lb/lbvector.h>
#include <MSL/math.h>

ItemStateTable it_803F67D0[] = {
    { 0, it_8029C6F4, it_8029C9CC, it_8029C9EC },
    { 1, it_8029C6F4, it_8029C9CC, it_8029C9EC },
};

inline void* getFoxLaser(Item* item)
{
    return &item->xDD4_itemVar;
}

bool it_8029C4D4(Item_GObj* item_gobj, CollData* arg1)
{
    Item* item = GET_ITEM(item_gobj);
    return it_8026E9A4(item_gobj, &item->xDD4_itemVar.foxlaser.pos, &item->pos,
                       0);
}

static inline void normalizeAngle(f32* angle)
{
    while (*angle < 0.0F) {
        *angle += 2 * M_PI;
    }
    while (*angle > 2 * M_PI) {
        *angle -= 2 * M_PI;
    }
}

void it_8029C504(HSD_GObj* parent, Vec3* pos, enum_t msid, int kind, f32 angle,
                 f32 speed)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;
    bool right_facing;
    FoxLaserAttr* attr;

    normalizeAngle(&angle);
    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.prev_pos.z = 0.0F;
    it_8026BB68(parent, &spawn.pos);
    right_facing = true;
    if (!(angle < M_PI / 2) && !(angle > M_PI * 3 / 2)) {
        right_facing = false;
    }
    spawn.facing_dir = right_facing ? +1.0F : -1.0F;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item* item = GET_ITEM(item_gobj);
        attr = item->xC4_article_data->x4_specialAttributes;
        Item_80268E5C(item_gobj, msid, ITEM_ANIM_UPDATE);
        it_80275158(item_gobj, attr->lifetime);
        item->xDD4_itemVar.foxlaser.scale = 0.0F;
        item->xDD4_itemVar.foxlaser.angle = angle;
        item->xDD4_itemVar.foxlaser.speed = speed;
        item->xDD4_itemVar.foxlaser.pos = spawn.pos;
        db_80225DD8(item_gobj, parent);
    }
}

void it_8029C6A4(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind)
{
    it_8029C504(parent, vec, 0, kind, angle, vel);
}

void it_8029C6CC(f32 angle, f32 vel, HSD_GObj* parent, Vec3* vec, int kind)
{
    it_8029C504(parent, vec, 1, kind, angle, vel);
}

static inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return +x;
    }
}

bool it_8029C6F4(Item_GObj* item_gobj)
{
    Article* article;
    Item* item;
    FoxLaserAttr* attr;
    HSD_JObj* jobj;
    f32 dir;
    f32 vel_x;

    item = GET_ITEM(item_gobj);
    jobj = GET_JOBJ(item_gobj);
    article = item->xC4_article_data;
    attr = article->x4_specialAttributes;
    item->x40_vel.x = item->xDD4_itemVar.foxlaser.speed *
                      cosf(item->xDD4_itemVar.foxlaser.angle);
    item->x40_vel.y = item->xDD4_itemVar.foxlaser.speed *
                      sinf(item->xDD4_itemVar.foxlaser.angle);
    item->x40_vel.z = 0.0F;
    if (item->x40_vel.x > 0.0F) {
        dir = +1.0F;
    } else {
        dir = -1.0F;
    }
    item->facing_dir = dir;
    HSD_JObjSetRotationY(jobj, (M_PI / 2) * item->facing_dir);
    if (item->facing_dir == 1.0F) {
        vel_x = -item->x40_vel.x;
    } else {
        vel_x = +item->x40_vel.x;
    }
    HSD_JObjSetRotationX(jobj, M_PI + atan2f(item->x40_vel.y, vel_x));
    item->xDD4_itemVar.foxlaser.scale +=
        fabsf(item->xDD4_itemVar.foxlaser.speed) / 11.25F;
    if (item->xDD4_itemVar.foxlaser.scale > attr->scale) {
        item->xDD4_itemVar.foxlaser.scale = attr->scale;
    }
    if (item->xDD4_itemVar.foxlaser.scale < 1e-5F) {
        item->xDD4_itemVar.foxlaser.scale = 1e-3;
    }
    HSD_JObjSetScaleZ(jobj, item->xDD4_itemVar.foxlaser.scale);
    return it_80273130(item_gobj);
}

void it_8029C9CC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xDD4_itemVar.foxlaser.pos = item->pos;
}

bool it_8029C9EC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Vec3 pos = item->pos;
    PAD_STACK(4);
    if (it_8029C4D4(item_gobj, NULL)) {
        it_80275158(item_gobj, 1.0F);
        item->pos = pos;
    }
    return false;
}

bool it_8029CA78(Item_GObj* arg0)
{
    return true;
}

bool it_8029CA80(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    if (item->facing_dir != item->xC68) {
        item->facing_dir = item->xC68;
        HSD_JObjSetRotationY(jobj, (M_PI / 2) * item->facing_dir);
    }
    HSD_JObjSetScaleZ(jobj, item->xDD4_itemVar.foxlaser.scale = 1e-3);
    item->xDD4_itemVar.foxlaser.angle += M_PI;
    normalizeAngle(&item->xDD4_itemVar.foxlaser.angle);
    return false;
}

bool it_8029CC4C(Item_GObj* arg0)
{
    return true;
}

bool it_8029CC54(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    u8 _[4] = { 0 };
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    item->xDD4_itemVar.foxlaser.scale = 1e-3;
    item->xDD4_itemVar.foxlaser.angle =
        atan2f(item->x40_vel.y, item->x40_vel.x);
    normalizeAngle(&item->xDD4_itemVar.foxlaser.angle);
    return false;
}

bool it_8029CCF0(Item_GObj* arg0)
{
    return true;
}

void it_8029CCF8(Item_GObj* item_gobj, HSD_GObj* ref)
{
    it_8026B894(item_gobj, ref);
}
