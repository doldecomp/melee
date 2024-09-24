#include "ityoshistar.h"

#include "math.h"

#include "it/inlines.h"
#include "it/it_2725.h"

#include <common_structs.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/db/db_2253.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

ItemStateTable it_803F7158[] = { {
    0,
    it_802B3294,
    it_802B32C8,
    it_802B3324,
} };

typedef struct {
    f32 speed;
    f32 accel;
} StarAttrs;

Item_GObj* it_802B2FC8(HSD_GObj* parent, Vec3* pos, f32 dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = It_Kind_Yoshi_Star;
    spawn.prev_pos = *pos;
    it_8026BB68(parent, &spawn.pos);
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        it_802B322C(item_gobj, parent);
        db_80225DD8(item_gobj, parent);
        return item_gobj;
    }
    return NULL;
}

bool it_802B309C(Item_GObj* item_gobj)
{
    it_80272BA4(item_gobj);
    return true;
}

bool it_802B30C0(Item_GObj* item_gobj)
{
    it_80272BA4(item_gobj);
    return true;
}

bool it_802B30E4(Item_GObj* item_gobj)
{
    it_80272BA4(item_gobj);
    return true;
}

bool it_802B3108(Item_GObj* item_gobj)
{
    it_80272BA4(item_gobj);
    return true;
}

bool it_802B312C(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

bool it_802B314C(Item_GObj* item_gobj)
{
    const f32 PI_2 = M_PI / 2;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* jobj = GET_JOBJ(item_gobj);
    it_80273030(item_gobj);
    HSD_JObjSetRotationY(jobj, PI_2 * item->facing_dir);
    return false;
}

void it_802B322C(Item_GObj* item_gobj, HSD_GObj* owner)
{
    Item* item = GET_ITEM(item_gobj);
    StarAttrs* star = item->xC4_article_data->x4_specialAttributes;
    item->owner = owner;
    item->x40_vel.x = star->speed * item->facing_dir;
    item->x40_vel.y = item->xCC_item_attr->x18;
    it_8026B3A8(item_gobj);
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802B3294(Item_GObj* item_gobj)
{
    if (!it_80272C6C(item_gobj)) {
        return true;
    }
    return false;
}

void it_802B32C8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;
    StarAttrs* star = item->xC4_article_data->x4_specialAttributes;
    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
    item->x40_vel.x += star->accel * item->facing_dir;
}

bool it_802B3324(Item_GObj* item_gobj)
{
    it_8026E0F4(item_gobj);
    return false;
}

void it_802B3348(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    it_8026B894(item_gobj, arg1);
}
