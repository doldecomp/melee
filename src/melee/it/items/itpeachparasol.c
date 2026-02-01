#include "itpeachparasol.h"

#include "it/inlines.h"

#include <common_structs.h>
#include <melee/db/db.h>
#include <melee/ft/chara/ftPeach/ftPe_SpecialHi.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

ItemStateTable it_803F74F8[] = {
    {
        -1,
        itPeachparasol_UnkMotion2_Anim,
        NULL,
        NULL,
    },
    {
        0,
        itPeachparasol_UnkMotion2_Anim,
        NULL,
        NULL,
    },
    {
        1,
        itPeachparasol_UnkMotion2_Anim,
        NULL,
        NULL,
    },
};

int it_802BDA40(Item_GObj* item_gobj, int i)
{
    static int it_804D5518[] = { 15, 16 };
    return it_804D5518[it_803F74F8[i].anim_id];
}

Item_GObj* it_802BDA64(HSD_GObj* parent, Vec3* pos, Fighter_Part arg2, f32 dir)
{
    SpawnItem spawn;
    Item_GObj* item_gobj;

    spawn.kind = 0x67;
    spawn.prev_pos = *pos;
    spawn.pos = spawn.prev_pos;
    spawn.facing_dir = dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x0_parent_gobj = parent;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;
    item_gobj = Item_80268B18(&spawn);
    if (item_gobj != NULL) {
        Item_8026AB54(item_gobj, parent, arg2);
        db_80225DD8(item_gobj, parent);
        return item_gobj;
    }
    return NULL;
}

void itPeachParasol_Logic60_Destroyed(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->owner != NULL && ftPe_8011D518(item->owner)) {
        item->owner = NULL;
    }
}

void it_802BDB94(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item != NULL) {
        itPeachParasol_Logic60_Destroyed(item_gobj);
        Item_8026A8EC(item_gobj);
    }
}

void it_802BDBF8(Item_GObj* item_gobj)
{
    it_8026B724(item_gobj);
}

void it_802BDC18(Item_GObj* item_gobj)
{
    it_8026B73C(item_gobj);
}

bool it_802BDC38(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    if (item->msid != 2) {
        return false;
    }
    if (item->x5CC_currentAnimFrame >= 16.0F) {
        return true;
    }
    return false;
}

void itPeachParasol_Logic60_PickedUp(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    it_802BDDB4(item_gobj, 16.0F);
    Item_802694CC(item_gobj);
    item->x5D0_animFrameSpeed = 1.0F;
}

bool itPeachparasol_UnkMotion2_Anim(Item_GObj* item_gobj)
{
    bool var_r3;

    Item* item = GET_ITEM(item_gobj);

    if (item->owner != NULL) {
        var_r3 = ftPe_SpecialHi_NotActive(item->owner);
    } else {
        var_r3 = true;
    }
    if (var_r3) {
        itPeachParasol_Logic60_Destroyed(item_gobj);
        return 1;
    }
    return false;
}

void it_802BDD3C(Item_GObj* item_gobj) {}

void it_802BDD40(Item_GObj* item_gobj, f32 arg8)
{
    Item* item = GET_ITEM(item_gobj);
    Item_8026AE84(item, 0xF7, 0x7F, 0x40);
    item->x5D0_animFrameSpeed = arg8;
    Item_80268E5C(item_gobj, 1, ITEM_ANIM_UPDATE);
    item->on_accessory = it_802BDD3C;
}

void it_802BDDB4(Item_GObj* item_gobj, f32 arg8)
{
    Item* item = GET_ITEM(item_gobj);
    item->x5D0_animFrameSpeed = arg8;
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
    item->on_accessory = it_802BDD3C;
}

void itPeachParasol_Logic60_EvtUnk(Item_GObj* item_gobj, HSD_GObj* arg1)
{
    it_8026B894(item_gobj, arg1);
}
