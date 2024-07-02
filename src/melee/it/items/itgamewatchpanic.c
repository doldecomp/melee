#include "itgamewatchpanic.h"

#include "db/db_2253.h"
#include "ft/chara/ftGameWatch/ftGw_SpecialLw.h"
#include "ft/ftLib.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 2C7FAC */ static bool it_802C7FAC(Item_GObj*);

HSD_GObj* it_802C7D60(Item_GObj* parent, Vec3* pos, u8 arg2, f32 dir)
{
    SpawnItem spawn_item;
    HSD_GObj* item_gobj;
    int* attr;

    spawn_item.kind = It_Kind_GameWatch_Panic;
    spawn_item.prev_pos = *pos;
    spawn_item.pos = spawn_item.prev_pos;
    spawn_item.facing_dir = dir;
    spawn_item.x3C_damage = 0;
    spawn_item.vel.x = spawn_item.vel.y = spawn_item.vel.z = 0.0f;
    spawn_item.x0_parent_gobj = parent;

    spawn_item.x4_parent_gobj2 = spawn_item.x0_parent_gobj;
    spawn_item.x44_flag.bits.b0 = true;
    spawn_item.x40 = 0;
    item_gobj = Item_80268B18(&spawn_item);
    if (item_gobj != NULL) {
        Item* it = GET_ITEM(item_gobj);
        attr = it->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(item_gobj, parent, arg2);
        db_80225DD8(item_gobj, parent);
        it_8027CE64(item_gobj, parent, *attr);
        return item_gobj;
    }
    return NULL;
}

void it_802C7E64(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    if (it->owner != NULL) {
        ftGw_SpecialLw_ItemPanicSetFlag(it->owner);
    }
}

void it_802C7E94(Item_GObj* arg0)
{
    HSD_GObj* gobj;
    Item* item;

    item = arg0->user_data;
    if (item != NULL) {
        it_802C7E64(arg0);
        Item_8026A8EC(arg0);
    }
}

void it_802C7EE0(Item_GObj* arg0)
{
    it_8026B724(arg0);
}

void it_802C7F00(Item_GObj* arg0)
{
    it_8026B73C(arg0);
}

void it_802C7F20(Item_GObj* arg0)
{
    Item* item;

    item = GET_ITEM((HSD_GObj*) arg0);
    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    if (item->owner != NULL) {
        item->ground_or_air = ftLib_800865CC(item->owner);
        if ((enum GroundOrAir) item->ground_or_air == GA_Ground) {
            Item_80268E5C((HSD_GObj*) arg0, 0, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C((HSD_GObj*) arg0, 1, ITEM_ANIM_UPDATE);
        }
        Item_802694CC((HSD_GObj*) arg0);
    }
}

bool it_802C7FAC(Item_GObj* item_gobj)
{
    Item* it = GET_ITEM(item_gobj);
    u32 unused[2];
    if (it->owner != NULL ? ftGw_SpecialLw_ItemCheckPanicRemove(it->owner)
                          : true)
    {
        Item* it = GET_ITEM(item_gobj);
        if (it->owner != NULL) {
            ftGw_SpecialLw_ItemPanicSetFlag(it->owner);
        }
        return true;
    }
    return false;
}

void it_802C8018(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, (HSD_GObj*) arg1);
}
