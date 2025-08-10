#include "itseakvanish.h"

#include "it/inlines.h"
#include "it/it_2725.h"

#include <common_structs.h>
#include <melee/db/db.h>
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

ItemStateTable it_803F70B8[] = {
    {
        0,
        itSeakvanish_UnkMotion0_Anim,
        NULL,
        NULL,
    },
};

Item_GObj* it_802B1C60(HSD_GObj* parent, Vec3* pos, f32 dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = It_Kind_Seak_Vanish;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = 1;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        it_802B1D40(item_gobj, parent);
        db_80225DD8(item_gobj, parent);
        return item_gobj;
    }
    return NULL;
}

bool it_802B1D38(Item_GObj* item_gobj)
{
    return false;
}

void it_802B1D40(Item_GObj* item_gobj, HSD_GObj* owner)
{
    Item* item = GET_ITEM(item_gobj);
    item->owner = owner;
    item->xD44_lifeTimer = 60.0F;
    item->xDAC_itcmd_var0 = 0;
    it_8026BB44(item_gobj);
    it_8026B3A8(item_gobj);
    it_8026BD24(item_gobj);
    it_8027518C(item_gobj);
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itSeakvanish_UnkMotion0_Anim(Item_GObj* item_gobj)
{
    return it_802751D8(item_gobj);
}

void it_802B1DCC(Item_GObj* item_gobj, HSD_GObj* gobj)
{
    it_8026B894(item_gobj, gobj);
}
