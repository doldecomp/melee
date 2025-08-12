#include "itchicoritaleaf.h"

#include "it/forward.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

ItemStateTable it_803F7AC8[] = {
    { 0, itChicoritaleaf_UnkMotion0_Anim, itChicoritaleaf_UnkMotion0_Phys,
      itChicoritaleaf_UnkMotion0_Coll },
};

void it_802C9B20(Item_GObj* chicorita_gobj)
{
    SpawnItem spawn;
    Item* chicorita;
    itChicoritaLeafAttr* attr;

    chicorita = GET_ITEM((HSD_GObj*) chicorita_gobj);
    attr = chicorita->xC4_article_data->x4_specialAttributes;
    spawn.prev_pos = chicorita->pos;
    spawn.prev_pos.x += attr->x8 * chicorita->facing_dir;
    spawn.prev_pos.y += attr->xC;
    it_8026BB88(chicorita_gobj, &spawn.pos);
    spawn.facing_dir = chicorita->facing_dir;
    spawn.x3C_damage = 0;
    spawn.vel.x = attr->x10 * chicorita->facing_dir;
    spawn.vel.z = spawn.vel.y = 0.0f;
    spawn.x40 = 0;
    spawn.kind = Pokemon_Chicorita_Leaf;
    spawn.x0_parent_gobj = chicorita->owner;
    spawn.x4_parent_gobj2 = (HSD_GObj*) chicorita_gobj;
    spawn.x44_flag.b0 = 1;
    if (Item_80268B18(&spawn)) {
        Item_8026AE84(chicorita, 0x2710, 0x7F, 0x40);
    }
}

void it_2725_Logic30_Spawned(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(12);

    item = GET_ITEM((HSD_GObj*) item_gobj);
    item->xD44_lifeTimer =
        ((itChicoritaLeafAttr*) item->xC4_article_data->x4_specialAttributes)
            ->timer;
    it_80274740(item_gobj);
    it_802C9CC0(item_gobj);
    it_8026B3A8(item_gobj);
    it_80274C60(item_gobj);
}

bool it_2725_Logic30_HitShield(Item_GObj* item_gobj)
{
    return false;
}

void it_2725_Logic30_EvtUnk(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}

bool it_2725_Logic30_Reflected(Item_GObj* item_gobj)
{
    return it_80273030(item_gobj);
}

void it_802C9CC0(Item_GObj* item_gobj)
{
    Item_80268E5C((HSD_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool itChicoritaleaf_UnkMotion0_Anim(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    if (item->xD44_lifeTimer <= 0.0f) {
        return true;
    }
    item->xD44_lifeTimer--;
    return false;
}

void itChicoritaleaf_UnkMotion0_Phys(HSD_GObj* item_gobj) {}

bool itChicoritaleaf_UnkMotion0_Coll(HSD_GObj* item_gobj)
{
    return it_8026DFB0((Item_GObj*) item_gobj);
}
