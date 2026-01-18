#include "itgamewatchgreenhouse.h"

#include <melee/db/db.h>
#include <melee/ft/chara/ftGameWatch/ftGw_Attack11.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>

/* 2C61F4 */ static HSD_GObj* it_802C61F4(HSD_GObj* parent, Vec3* pos,
                                          Fighter_Part part, float dir);
/* 2C6328 */ static void it_802C6328(Item_GObj* item_gobj);
/* 2C6374 */ static void it_802C6374(Item_GObj* item_gobj);
/* 2C6394 */ static void it_802C6394(Item_GObj* item_gobj);
/* 2C6430 */ static void it_802C6430(Item_GObj* item_gobj);
/* 2C6458 */ static void it_802C6458(Item_GObj* item_gobj);
/* 2C6480 */ static void it_802C6480(Item_GObj* item_gobj);
/* 2C64A8 */ static void it_802C64A8(Item_GObj* item_gobj);
/* 2C653C */ static bool
itGamewatchgreenhouse_UnkMotion2_Anim(Item_GObj* item_gobj);

HSD_GObj* it_802C61F4(HSD_GObj* parent, Vec3* pos, Fighter_Part part,
                      float dir)
{
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_GameWatch_Greenhouse;
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

void it_2725_Logic71_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    if (item->owner != NULL) {
        ftGw_Attack11_ItemGreenhouseSetFlag(item->owner);
    }
}

void it_802C6328(Item_GObj* item_gobj)
{
    int pad[1];
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        if (item->owner != NULL) {
            ftGw_Attack11_ItemGreenhouseSetFlag(item->owner);
        }
        Item_8026A8EC(item_gobj);
    }
}

void it_802C6374(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802C6394(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void it_2725_Logic71_PickedUp(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    item->xDB0_itcmd_var1 = 0;
    item->xDAC_itcmd_var0 = 0;
    if (item->owner != NULL) {
        if (ftGw_Attack11_ItemGreenhouse_CheckAttack11(item->owner) != 0) {
            Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
        } else {
            Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
        }
        Item_802694CC(item_gobj);
    }
}

void it_802C6430(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

void it_802C6458(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
}

void it_802C6480(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
}

void it_802C64A8(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 3, ITEM_ANIM_UPDATE);
}

bool itGamewatchgreenhouse_UnkMotion3_Anim(Item_GObj* item_gobj)
{
    int pad[3];
    Item* item;
    bool var_r3;

    item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        var_r3 = ftGw_Attack11_ItemGreenhouse_CheckAll(item->owner);
    } else {
        var_r3 = true;
    }
    if (var_r3) {
        item = GET_ITEM(item_gobj);
        if (item->owner != NULL) {
            ftGw_Attack11_ItemGreenhouseSetFlag(item->owner);
        }
        return true;
    }
    return false;
}

bool itGamewatchgreenhouse_UnkMotion2_Anim(Item_GObj* item_gobj)
{
    Item* item;
    bool var_r3;

    if (it_80272C6C(item_gobj) == 0) {
        Item_80268E5C((HSD_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
    }
    item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        var_r3 = ftGw_Attack11_ItemGreenhouse_CheckAll(item->owner);
    } else {
        var_r3 = true;
    }
    if (var_r3) {
        if (item->owner != NULL) {
            ftGw_Attack11_ItemGreenhouseSetFlag(item->owner);
        }
        return true;
    }
    return false;
}

void it_2725_Logic71_EvtUnk(Item_GObj* item_gobj, Item_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
