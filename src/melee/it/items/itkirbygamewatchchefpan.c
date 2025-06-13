#include "itkirbygamewatchchefpan.h"

#include <melee/db/db.h>
#include <melee/ft/chara/ftKirby/ftKb_Init.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>

ItemStateTable it_803F7958[] = {
    {
        -1,
        it_802C76E8,
        NULL,
        NULL,
    },
};

Item_GObj* it_802C74D8(HSD_GObj* parent, Vec3* pos, Fighter_Part part, float dir)
{
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_Kirby_GameWatchChefPan;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    result = Item_80268B18(&spawn);
    if (result != NULL) {
        Item* item = GET_ITEM(result);
        void** attr = item->xC4_article_data->x4_specialAttributes;
        Item_8026AB54(result, parent, part);
        db_80225DD8(result, parent);
        it_8027CE64(result, parent, attr[0]);
        return result;
    }
    return NULL;
}

void it_802C75DC(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        ftKb_SpecialNGw_8010D074(item->owner);
    }
}

void it_802C760C(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item != NULL) {
        it_802C75DC(item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

void it_802C7658(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802C7678(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_802C7698(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}

static inline bool it_802C76E8_inline(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        return ftKb_SpecialNGw_8010D160(item->owner);
    }
    return true;
}

bool it_802C76E8(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (it_802C76E8_inline(item_gobj)) {
        it_802C75DC(item_gobj);
        return true;
    }
    return false;
}

void it_802C7754(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}

