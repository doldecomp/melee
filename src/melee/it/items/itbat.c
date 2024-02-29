#include "itbat.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

Item_GObj* it_80284854(Vec3* pos)
{
    SpawnItem spawn;
    Item_GObj* item_gobj = NULL;

    pos->z = 0.0F;
    spawn.kind = It_Kind_Bat;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = -1.0F;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);

    if (item_gobj != NULL) {
        it_80284974(item_gobj);
    }

    return item_gobj;
}

void it_80284910(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    itBatAttributes* ap = item->xC4_article_data->x4_specialAttributes;

    it_8026B390(gobj);
    item->x40_vel.x = 0.0f;
    item->x40_vel.y = ap->xC_vel;
    item->x40_vel.z = 0.0f;
    it_802849F0(gobj);
}

void it_80284974(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    item->xD50_landNum = 0;

    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802849B8(Item_GObj* gobj)
{
    return 0;
}

void it_802849C0(Item_GObj* gobj)
{
    return;
}

bool it_802849C4(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_802849F0);
    return 0;
}

void it_802849F0(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    item->xD50_landNum = 0;
}
