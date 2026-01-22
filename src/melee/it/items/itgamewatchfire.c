#include "itgamewatchfire.h"

#include "baselib/gobj.h"

#include "it/forward.h"

#include <melee/db/db.h>
#include <melee/ft/ftlib.h>
#include <melee/it/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/it_2725.h>
#include <melee/it/item.h>
#include <melee/it/types.h>
#include <melee/lb/lb_00B0.h>

/* 2C6B20 */ static bool itGamewatchFire_Motion0_Anim(Item_GObj* item_gobj);

HSD_GObj* itGamewatchFire_Spawn(HSD_GObj* parent, Vec3* pos, Fighter_Part part,
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

void itGamewatchFire_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL) {
        ftGw_AttackS4_ItemTorchSetFlag(item->owner);
    }
}

void itGamewatchFire_802C6A2C(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);

    if (item != NULL) {
        itGamewatchFire_Destroyed(item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

void itGamewatchFire_802C6A78(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void itGamewatchFire_802C6A98(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

void itGamewatchFire_PickedUp(Item_GObj* item_gobj)
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

static inline bool torchRemoveCheck(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    if (item->owner != NULL) {
        return ftGw_AttackS4_ItemCheckTorchRemove(item->owner);
    }
    return true;
}

bool itGamewatchFire_Motion0_Anim(Item_GObj* item_gobj)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM(item_gobj);

    jobj = GET_JOBJ(item_gobj);
    if (item->x5CC_currentAnimFrame == 3.0f) {
        it_8026BB20(item_gobj);
    }
    if (torchRemoveCheck(item_gobj)) {
        itGamewatchFire_Destroyed(item_gobj);
        return true;
    }
    if (item->owner != NULL) {
        if (ftLib_800876D4(item->owner) != 0) {
            if (item->x5D0_animFrameSpeed != 0.0f) {
                item->x5D0_animFrameSpeed = 0.0f;
                lb_8000BA0C(jobj, item->x5D0_animFrameSpeed);
            }
        } else if (item->x5D0_animFrameSpeed != 1.0f) {
            item->x5D0_animFrameSpeed = 1.0f;
            lb_8000BA0C(jobj, item->x5D0_animFrameSpeed);
        }
    }
    return false;
}

void itGamewatchFire_EvtUnk(Item_GObj* item_gobj, Item_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}
