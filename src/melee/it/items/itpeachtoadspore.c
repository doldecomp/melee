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
    itPeachtoadspore_UnkMotion0_Anim,
    itPeachtoadspore_UnkMotion0_Phys,
    NULL,
} };

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
    HSD_JObj *item_jobj, *hsd_jobj;
    Item *item_1, *item_2;
    itPeachToadSporeAttributes* attr;
    f32 rand, speed, angle_offset, double_angle, angle;

    item_1 = GET_ITEM(item_gobj);
    item_jobj = item_gobj->hsd_obj;
    attr = item_1->xC4_article_data->x4_specialAttributes;
    item_1->owner = arg1;
    it_80275158(item_gobj, 60.0F);
    item_1->xDAC_itcmd_var0 = 0;

    rand = HSD_Randf();
    speed = attr->x0_min_speed + attr->x4_max_speed_offset * rand;

    rand = HSD_Randf();
    double_angle = ((f32) M_PI) - attr->xc_angle;
    angle_offset = attr->xc_angle * rand;
    angle = 0.5F * double_angle + angle_offset;

    item_1->x40_vel.x = item_1->facing_dir * (speed * sinf(angle));
    item_1->x40_vel.y = speed * cosf(angle);

    it_80272A3C(item_jobj);
    it_8026B3A8(item_gobj);

    item_2 = GET_ITEM(item_gobj);
    hsd_jobj = item_gobj->hsd_obj;
    if (item_2->kind == It_Kind_Peach_ToadSpore) {
        efSync_Spawn(0x4D3, item_gobj, hsd_jobj);
    } else {
        efSync_Spawn(0x4D3, item_gobj, hsd_jobj);
    }
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itPeachtoadspore_UnkMotion0_Anim(Item_GObj* item_gobj)
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

void itPeachtoadspore_UnkMotion0_Phys(Item_GObj* item_gobj)
{
    itPeachToadSporeAttributes* attr;
    Item* item;

    item = GET_ITEM(item_gobj);
    attr = item->xC4_article_data->x4_specialAttributes;
    item->x40_vel.x *= attr->x8_speed_decay_rate;
    item->x40_vel.y *= attr->x8_speed_decay_rate;
}

bool it_2725_Logic92_DmgDealt(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_2725_Logic68_Clanked(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_2725_Logic68_HitShield(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_2725_Logic68_Absorbed(Item_GObj* item_gobj)
{
    efLib_DestroyAll(item_gobj);
    return true;
}

bool it_2725_Logic68_ShieldBounced(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

bool it_2725_Logic68_Reflected(Item_GObj* item_gobj)
{
    Item* item;
    f32 lifeTimer;

    item = GET_ITEM(item_gobj);
    lifeTimer = item->xD44_lifeTimer;
    it_80273030(item_gobj);
    item->xD44_lifeTimer = lifeTimer;
    return false;
}

void it_2725_Logic92_EvtUnk(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
