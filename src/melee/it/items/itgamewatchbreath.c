#include "itgamewatchbreath.h"

#include <melee/db/db.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>

HSD_GObj* it_802C720C(HSD_GObj* parent, Vec3* pos, Fighter_Part part, float dir) {
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_GameWatch_Breath;
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

void it_802C7310(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        ftGw_AttackAirN_ItemSparkySetFlag(item->owner);
    }
}

void it_802C7340(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_AttackAirN_ItemSparkySetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void it_802C738C(Item_GObj* item_gobj) {
    it_8026B724(item_gobj);
}

void it_802C73AC(Item_GObj* item_gobj) {
    it_8026B73C(item_gobj);
}

void it_802C73CC(Item_GObj* item_gobj) {
    Item* temp_r3;

    temp_r3 = item_gobj->user_data;
    temp_r3->xDAC_itcmd_var0 = 0;
    if ((HSD_GObj* ) temp_r3->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}

void it_802C7424(Item_GObj* item_gobj) {
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_802C744C(void* item_gobj) {
    Item* item;
    bool var_r3;

    item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        var_r3 = ftGw_AttackAirN_ItemCheckSparkyRemove(item->owner);
    } else {
        var_r3 = true;
    }
    if (var_r3) {
        item = GET_ITEM(item_gobj);
        if (item->owner != NULL) {
            ftGw_AttackAirN_ItemSparkySetFlag(item->owner);
        }
        return true;
    }
    return false;
}

void it_802C74B8(Item_GObj* item_gobj, Item_GObj* ref_gobj) {
    it_8026B894(item_gobj, ref_gobj);
}
