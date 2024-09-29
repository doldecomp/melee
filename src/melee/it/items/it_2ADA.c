#include <platform.h>

#include "it_2ADA.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

#include <common_structs.h>

/* 2ADAF0 */ static void it_802ADAF0(Item_GObj* gobj);
/* 2ADB48 */ static bool it_802ADB48(Item_GObj* gobj);
/* 2ADB80 */ static void it_802ADB80(Item_GObj* gobj);
/* 2ADBB0 */ static bool it_802ADBB0(Item_GObj* gobj);

ItemStateTable it_803F6C88[] = {
    {
        0,
        it_802ADB48,
        it_802ADB80,
        it_802ADBB0,
    },
};

void it_802ADA1C(Vec3* pos, Vec3* vel, float facing_dir)
{
    SpawnItem spawnitem;
    spawnitem.kind = It_Kind_Unk1;
    spawnitem.prev_pos = *pos;
    spawnitem.prev_pos.z = 0;
    spawnitem.pos = spawnitem.prev_pos;
    spawnitem.facing_dir = facing_dir;
    spawnitem.x3C_damage = 0;
    spawnitem.vel = *vel;
    spawnitem.x0_parent_gobj = NULL;
    spawnitem.x4_parent_gobj2 = NULL;
    spawnitem.x44_flag.b0 = true;
    spawnitem.x40 = 0;
    {
        Item_GObj* gobj = Item_80268B18(&spawnitem);
        if (gobj != NULL) {
            Item* ip = GET_ITEM(gobj);
            itUnkAttributes* attrs =
                ip->xC4_article_data->x4_specialAttributes;
            it_80275158(gobj, attrs->x0_float);
            it_802ADAF0(gobj);
        }
    }
}

void it_802ADAF0(Item_GObj* gobj)
{
    u8 _[4] = { 0 };
    Item* item = GET_ITEM(gobj);
    it_8026B3A8(gobj);
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    item->xDCE_flag.b7 = false;
}

bool it_802ADB48(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->xD44_lifeTimer -= 1;
    if (item->xD44_lifeTimer <= 0) {
        return true;
    }
    return false;
}

void it_802ADB80(Item_GObj* gobj)
{
    ItemAttr* attrs = GET_ITEM(gobj)->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool it_802ADBB0(Item_GObj* gobj)
{
    return it_8026DFB0(gobj) ? true : false;
}

void it_802ADBE4(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, arg1);
}
