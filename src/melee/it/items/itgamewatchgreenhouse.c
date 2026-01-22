#include "itgamewatchgreenhouse.h"

#include "it/forward.h"
#include "it/items/forward.h"

#include <string.h>
#include <melee/db/db.h>
#include <melee/ft/chara/ftGameWatch/ftGw_Attack11.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>

ItemStateTable it_803F7898[] = {
    { 0, itGamewatchGreenhouse_Motion3_Anim, NULL, NULL },
    { 1, itGamewatchGreenhouse_Motion3_Anim, NULL, NULL },
    { 2, itGamewatchGreenhouse_Motion2_Anim, NULL, NULL },
    { 3, itGamewatchGreenhouse_Motion3_Anim, NULL, NULL }
};

HSD_GObj* itGamewatchGreenhouse_Spawn(HSD_GObj* parent, Vec3* pos,
                                      Fighter_Part part, float dir)
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

void itGamewatchGreenhouse_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    if (item->owner != NULL) {
        ftGw_Attack11_ItemGreenhouseSetFlag(item->owner);
    }
}

void itGamewatchGreenhouse_802C6328(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        itGamewatchGreenhouse_Destroyed(item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

void itGamewatchGreenhouse_802C6374(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void itGamewatchGreenhouse_802C6394(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void itGamewatchGreenhouse_PickedUp(Item_GObj* item_gobj)
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

void itGamewatchGreenhouse_802C6430(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

void itGamewatchGreenhouse_802C6458(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
}

void itGamewatchGreenhouse_802C6480(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
}

void itGamewatchGreenhouse_802C64A8(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 3, ITEM_ANIM_UPDATE);
}

static inline bool greenhouse_Check(Item_GObj* item_gobj)
{
    Item* item;
    item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        return ftGw_Attack11_ItemGreenhouse_CheckAll(item->owner);
    }
    return true;
}

bool itGamewatchGreenhouse_Motion3_Anim(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(8);

    if (greenhouse_Check(item_gobj)) {
        itGamewatchGreenhouse_Destroyed(item_gobj);
        return true;
    }
    return false;
}

bool itGamewatchGreenhouse_Motion2_Anim(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(0x10);

    if (it_80272C6C(item_gobj) == 0) {
        Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
    }
    if (greenhouse_Check(item_gobj)) {
        itGamewatchGreenhouse_Destroyed(item_gobj);
        return true;
    }
    return false;
}

void itGamewatchGreenhouse_EvtUnk(Item_GObj* item_gobj, Item_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
