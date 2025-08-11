#include "itgamewatchfire.h"

#include <melee/db/db.h>
#include <melee/ft/ftlib.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>
#include <melee/lb/lb_00B0.h>

/* 2C68F8 */ static HSD_GObj* it_802C68F8(HSD_GObj* parent, Vec3* pos,
                                          Fighter_Part part, float dir);
/* 2C6A2C */ static void it_802C6A2C(Item_GObj* item_gobj);
/* 2C6A78 */ static void it_802C6A78(Item_GObj* item_gobj);
/* 2C6A98 */ static void it_802C6A98(Item_GObj* item_gobj);
/* 2C6B20 */ static bool itGamewatchfire_UnkMotion0_Anim(Item_GObj* item_gobj);

HSD_GObj* it_802C68F8(HSD_GObj* parent, Vec3* pos, Fighter_Part part,
                      float dir)
{
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_GameWatch_Fire;
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

void it_2725_Logic73_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        ftGw_AttackS4_ItemTorchSetFlag(item->owner);
    }
}

void it_802C6A2C(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_AttackS4_ItemTorchSetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void it_802C6A78(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802C6A98(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_2725_Logic73_PickedUp(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    it_8026BB44(item_gobj);
    if (item->owner != NULL) {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        Item_802694CC(item_gobj);
    }
}

bool itGamewatchfire_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    HSD_JObj* temp_r30;
    Item* item = GET_ITEM(item_gobj);
    bool var_r3;

    temp_r30 = item_gobj->hsd_obj;
    if (item->x5CC_currentAnimFrame == 3.0f) {
        it_8026BB20(item_gobj);
    }
    if (item->owner != NULL) {
        var_r3 = ftGw_AttackS4_ItemCheckTorchRemove(item->owner);
    } else {
        var_r3 = true;
    }
    if (var_r3) {
        if (item->owner != NULL) {
            ftGw_AttackS4_ItemTorchSetFlag(item->owner);
        }
        return true;
    }
    if (item->owner != NULL) {
        if (ftLib_800876D4(item->owner) != 0) {
            if (item->x5D0_animFrameSpeed != 0.0f) {
                item->x5D0_animFrameSpeed = 0.0f;
                lb_8000BA0C(temp_r30, item->x5D0_animFrameSpeed);
            }
        } else if (item->x5D0_animFrameSpeed != 1.0f) {
            item->x5D0_animFrameSpeed = 1.0f;
            lb_8000BA0C(temp_r30, item->x5D0_animFrameSpeed);
        }
    }
    return false;
}

void it_2725_Logic73_EvtUnk(Item_GObj* item_gobj, Item_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
