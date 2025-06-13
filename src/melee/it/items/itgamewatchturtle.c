#include "itgamewatchturtle.h"

#include <sysdolphin/baselib/gobj.h>
#include <melee/db/db.h>
#include <melee/ft/chara/ftGameWatch/ftGw_AttackAir.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/items/types.h>

void it_8027CE64(HSD_GObj*, Item_GObj*, s32); /* extern */

ItemStateTable it_803F7918[] = {
    {
        0,
        it_802C7180,
        NULL,
        NULL,
    },
    {
        1,
        it_802C7180,
        NULL,
        NULL,
    },
};

Item_GObj* it_802C6F40(HSD_GObj* parent, Vec3* pos, Fighter_Part arg2, f32 dir)
{
    SpawnItem spawn_item;
    HSD_GObj* item_gobj;
    int* temp_r30;

    spawn_item.kind = It_Kind_GameWatch_Turtle;
    spawn_item.prev_pos = *pos;
    spawn_item.pos = spawn_item.prev_pos;
    spawn_item.facing_dir = dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0f;
    spawn_item.x0_parent_gobj = parent;

    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.b0 = true;
    spawn_item.x40 = 0;
    item_gobj = Item_80268B18(&spawn_item);
    if (item_gobj != NULL) {
        Item* it = GET_ITEM(item_gobj);
        temp_r30 = it->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(item_gobj, parent, arg2);
        db_80225DD8(item_gobj, parent);
        it_8027CE64(item_gobj, parent, *temp_r30);
        return item_gobj;
    }
    return NULL;
}

void it_802C7044(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (it->owner != NULL) {
        ftGw_AttackAirN_ItemTurtleSetFlag(it->owner);
    }
}

void it_802C7074(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    u32 unused;
    if (it != NULL) {
        if (it->owner != NULL) {
            ftGw_AttackAirN_ItemTurtleSetFlag(it->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void it_802C70C0(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802C70E0(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_802C7100(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    it->xDAC_itcmd_var0 = 0;
    if (it->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}

void it_802C7158(HSD_GObj* arg0)
{
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
}

bool it_802C7180(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    u32 unused[2];
    if (it->owner != NULL ? ftGw_AttackAirN_ItemCheckTurtleRemove(it->owner)
                          : true)
    {
        Item* it = GET_ITEM(item_gobj);
        if (it->owner != NULL) {
            ftGw_AttackAirN_ItemTurtleSetFlag(it->owner);
        }
        return true;
    }
    return false;
}

void it_802C71EC(HSD_GObj* arg0, HSD_GObj* arg1)
{
    it_8026B894(arg0, arg1);
}
