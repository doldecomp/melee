#include "baselib/forward.h"
#include "it/forward.h"

#include "itpeachtoadspore.h"

#include "common_structs.h"

#include "baselib/random.h"
#include "db/db.h"
#include "ef/eflib.h"
#include "ef/efsync.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

#include <math.h>

ItemStateTable it_803F7548[] = { {
    0,
    it_802BE408,
    it_802BE458,
    NULL,
} };

// TODO: check types of function calls and headers

Item_GObj* it_802BE214(Item_GObj* item_gobj, Vec3* pos, ItemKind kind,
                       f32 facing_dir)
{
    SpawnItem spawn;
    Item_GObj* spawn_gobj;

    spawn.kind = kind;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = item_gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;

    spawn_gobj = Item_80268B18(&spawn);
    if (spawn_gobj != NULL) {
        it_802BE2E8(spawn_gobj, item_gobj);
        db_80225DD8(spawn_gobj, item_gobj);
        return spawn_gobj;
    }
    return NULL;
}

void it_802BE2E8(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    // HSD_JObj* temp_r31;
    // u8 _[8];
    f32 trig1;
    f32 trig2;
    f32 temp_f0;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f4;
    f32 temp_f2;
    f32 rand;
    f32 temp_f1;
    HSD_JObj* hsd_jobj; // rename to item_jobj
    HSD_JObj* temp_r5;
    Item* item;
    itPeachToadSporeAttributes* attr;
    // void* temp_r29;

    item = GET_ITEM(item_gobj);
    hsd_jobj = item_gobj->hsd_obj;
    attr = item->xC4_article_data->x4_specialAttributes;
    item->owner = arg1;

    it_80275158(item_gobj, 60.0F);
    item->xDAC_itcmd_var0 = 0;

    // temp_f31 = (attr->x4 * HSD_Randf()) + attr->x0;

    rand = HSD_Randf();

    temp_f0 = attr->x0;
    temp_f31 = attr->x4 * rand + temp_f0;

    // temp_f4 = temp_r29->unkC;
    // temp_f30 = (0.5f * (3.1415927F - temp_f4)) * (temp_f4 * HSD_Randf());
    rand = HSD_Randf();
    temp_f2 = 3.1415927F;
    temp_f4 = attr->xc;
    temp_f1 = temp_f2 - temp_f4;
    temp_f0 = temp_f4 * rand;

    temp_f30 = 0.5F * temp_f1 + temp_f0;

    trig1 = sinf(temp_f30);
    temp_f2 = temp_f31 * trig1;
    // item->x40_vel.x = temp_f2 * item->facing_dir;
    item->x40_vel.x = item->facing_dir * temp_f2;

    trig2 = cosf(temp_f30);
    item->x40_vel.y = temp_f31 * trig2;

    it_80272A3C(hsd_jobj);
    it_8026B3A8(item_gobj);

    temp_r5 = item_gobj->hsd_obj;
    if (GET_ITEM(item_gobj)->kind == It_Kind_Peach_ToadSpore) {
        efSync_Spawn(0x4D3, item_gobj, temp_r5);
    } else {
        efSync_Spawn(0x4D3, item_gobj, temp_r5);
    }
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_802BE408(Item_GObj* item_gobj)
{
    Item* item;

    item = GET_ITEM(item_gobj);
    if (item->xDAC_itcmd_var0 != 0) {
        return true;
    }

    item->xD44_lifeTimer--;
    if (item->xD44_lifeTimer <= 0.0F) {
        item->xD44_lifeTimer = 0.0F;
        return true;
    }
    return false;
}

void it_802BE458(Item_GObj* item_gobj)
{
    itPeachToadSporeAttributes* temp_r3;
    Item* item;

    item = GET_ITEM(item_gobj);
    temp_r3 = item->xC4_article_data->x4_specialAttributes;
    item->x40_vel.x = item->x40_vel.x * temp_r3->x8;
    item->x40_vel.y = item->x40_vel.y * temp_r3->x8;
}

bool it_802BE488(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_802BE4AC(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_802BE4D0(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_802BE4F4(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_802BE518(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

bool it_802BE538(Item_GObj* item_gobj)
{
    Item* item;
    f32 lifeTimer;

    item = GET_ITEM(item_gobj);
    lifeTimer = item->xD44_lifeTimer;
    it_80273030(item_gobj);
    item->xD44_lifeTimer = lifeTimer;
    return false;
}

void it_802BE578(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
