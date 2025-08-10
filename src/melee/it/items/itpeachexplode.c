#include "itpeachexplode.h"

#include "db/db.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/types.h"

ItemStateTable it_803F7488[] = {
    {
        0,
        itPeachexplode_UnkMotion1_Anim,
        NULL,
        NULL,
    },
    {
        1,
        itPeachexplode_UnkMotion1_Anim,
        NULL,
        NULL,
    },
};

Item_GObj* it_802BD158(Item_GObj* gobj, Vec3* pos, bool arg2, float dir)
{
    SpawnItem spawn;
    Item_GObj* result;

    spawn.kind = It_Kind_Peach_Explode;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = gobj;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    result = Item_80268B18(&spawn);
    if (result != NULL) {
        it_802BD248(result, gobj, arg2);
        db_80225DD8(result, gobj);
        return result;
    }
    return NULL;
}

bool it_802BD240(Item_GObj* arg0)
{
    return false;
}

void it_802BD248(Item_GObj* item_gobj, Item_GObj* owner, bool arg2)
{
    Item* ip = GET_ITEM(item_gobj);
    ip->owner = owner;
    ip->xD44_lifeTimer = 60.0F;
    ip->xDAC_itcmd_var0 = 0;
    it_8026BB44(item_gobj);
    it_80272C08(item_gobj);
    it_8026B3A8(item_gobj);
    it_8026BD24(item_gobj);
    it_8027518C(item_gobj);
    if (arg2) {
        Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    } else {
        Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
    }
    it_80274574(item_gobj);
}

bool itPeachexplode_UnkMotion1_Anim(Item_GObj* item_gobj)
{
    return it_802751D8(item_gobj);
}

void it_802BD30C(Item_GObj* gobj, Item_GObj* ref_gobj)
{
    it_8026B894(gobj, ref_gobj);
}
