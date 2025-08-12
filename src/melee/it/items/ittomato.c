#include "ittomato.h"

#include "baselib/jobj.h"
#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/itCommonItems.h"
#include "it/item.h"

/* 2841B4 */ static Item_GObj* it_802841B4(Item_GObj* gobj, Vec3* arg1,
                                           s32 arg2);
/* 28428C */ static void it_8028428C(Item_GObj* gobj);
/* 284358 */ static void it_80284358(Item_GObj* gobj);
/* 284380 */ static bool itTomato_UnkMotion0_Anim(HSD_GObj* gobj);
/* 284388 */ static void itTomato_UnkMotion0_Phys(Item_GObj* gobj);
/* 2843B8 */ static bool itTomato_UnkMotion0_Coll(Item_GObj* gobj);
/* 2843E4 */ static void it_802843E4(HSD_GObj* gobj);
/* 284420 */ static bool itTomato_UnkMotion1_Anim(HSD_GObj* gobj);
/* 284428 */ static void itTomato_UnkMotion1_Phys(Item_GObj* gobj);
/* 28442C */ static bool itTomato_UnkMotion1_Coll(Item_GObj* gobj);
/* 284458 */ static void it_80284458(HSD_GObj* gobj);
/* 284480 */ static bool itTomato_UnkMotion4_Anim(Item_GObj* gobj);
/* 284488 */ static void itTomato_UnkMotion4_Phys(Item_GObj* gobj);
/* 2844B8 */ static bool itTomato_UnkMotion4_Coll(Item_GObj* gobj);
/* 284540 */ static bool itTomato_UnkMotion3_Anim(Item_GObj* gobj);
/* 284548 */ static void itTomato_UnkMotion3_Phys(Item_GObj* gobj);
/* 2845E4 */ static bool itTomato_UnkMotion5_Anim(Item_GObj* gobj);
/* 2845EC */ static void itTomato_UnkMotion5_Phys(Item_GObj* gobj);
/* 2845F0 */ static bool itTomato_UnkMotion5_Coll(Item_GObj* gobj);

ItemStateTable it_803F5740[] = {
    { -1, itTomato_UnkMotion0_Anim, itTomato_UnkMotion0_Phys,
      itTomato_UnkMotion0_Coll },
    { -1, itTomato_UnkMotion1_Anim, itTomato_UnkMotion1_Phys,
      itTomato_UnkMotion1_Coll },
    { -1, itTomato_UnkMotion4_Anim, itTomato_UnkMotion4_Phys,
      itTomato_UnkMotion4_Coll },
    { -1, itTomato_UnkMotion3_Anim, itTomato_UnkMotion3_Phys, NULL },
    { -1, itTomato_UnkMotion4_Anim, itTomato_UnkMotion4_Phys,
      itTomato_UnkMotion4_Coll },
    { -1, itTomato_UnkMotion5_Anim, itTomato_UnkMotion5_Phys,
      itTomato_UnkMotion5_Coll },
};

Item_GObj* it_802841B4(Item_GObj* gobj, Vec3* pos, s32 arg2)
{
    SpawnItem spawn;
    Item_GObj* item_gobj = NULL;

    if (gobj != NULL) {
        spawn.kind = It_Kind_Tomato;
        spawn.prev_pos = *pos;
        spawn.prev_pos.z = 0.0F;
        spawn.pos = spawn.prev_pos;
        spawn.facing_dir = -1.0F;
        spawn.x3C_damage = 0;
        spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
        spawn.x0_parent_gobj = NULL;
        spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
        spawn.x44_flag.b0 = true;
        spawn.x40 = 0;
        item_gobj = Item_80268B18(&spawn);
    }
    if (item_gobj != NULL) {
        Item* it = GET_ITEM(item_gobj);
        it->xDD4_itemVar.tomato.x4.b0 = true;
        it->xDD4_itemVar.tomato.x8 = arg2;
    }
    return item_gobj;
}

void it_8028428C(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    ip->xDD4_itemVar.tomato.heal_amount =
        M2C_FIELD(ip->xC4_article_data->x4_specialAttributes, s32*, 4);
}

void it_3F14_Logic9_Spawned(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    MaximTomatoSpecialAttr* sa = item->xC4_article_data->x4_specialAttributes;

    it_8026B390(gobj);
    item->x40_vel.x = 0.0F;
    item->x40_vel.y = sa->x14;
    item->x40_vel.z = 0.0F;

    item->xDD4_itemVar.tomato.heal_amount = sa->x0;
    item->xDD4_itemVar.tomato.x4.b0 = false;
    item->xDD4_itemVar.tomato.x8 = 0;

    it_80284358(gobj);
}

void it_3F14_Logic9_Destroyed(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    // if ((((temp_r4->xDD4_itemVar.Egg.filler[4] << 0x18) & 0xC0000000) >>
    //      0x1F) != 0)
    // {
    //     M2C_FIELD(
    //         (&gm_80473A18 + M2C_BITWISE(s32,
    //         temp_r4->xDD4_itemVar.star.x8)), s8*, 0x90) = 0;
    // }
}

void it_80284358(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
}

bool itTomato_UnkMotion0_Anim(HSD_GObj* gobj)
{
    return false;
}

void itTomato_UnkMotion0_Phys(Item_GObj* gobj)
{
    ItemAttr* attr;

    Item* item = GET_ITEM(gobj);
    attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itTomato_UnkMotion0_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802843E4);
    return false;
}

void it_802843E4(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.z = item->x40_vel.y = item->x40_vel.x = 0;
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itTomato_UnkMotion1_Anim(HSD_GObj* gobj)
{
    return false;
}

void itTomato_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itTomato_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_80284458);
    return false;
}

void it_80284458(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itTomato_UnkMotion4_Anim(Item_GObj* gobj)
{
    return false;
}

void itTomato_UnkMotion4_Phys(Item_GObj* gobj)
{
    ItemAttr* attr;

    Item* item = GET_ITEM(gobj);
    attr = item->xCC_item_attr;
    it_80272860(gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool itTomato_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E15C(gobj, it_802843E4);
    return false;
}

void it_3F14_Logic9_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj2 = HSD_JObjGetChild(jobj);

    HSD_JObjClearFlagsAll(jobj2, 0x10);
    Item_80268E5C(gobj, 3, ITEM_ANIM_UPDATE);
}

bool itTomato_UnkMotion3_Anim(Item_GObj* gobj)
{
    return false;
}

void itTomato_UnkMotion3_Phys(Item_GObj* gobj) {}

void it_3F14_Logic9_Dropped(Item_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    HSD_JObj* jobj2 = HSD_JObjGetChild(jobj);

    it_8026B390(gobj);
    HSD_JObjClearFlagsAll(jobj2, 0x10);
    Item_80268E5C(gobj, 4, 6);
}

void it_3F14_Logic9_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 5, ITEM_ANIM_UPDATE);
}

bool itTomato_UnkMotion5_Anim(Item_GObj* gobj)
{
    return false;
}

void itTomato_UnkMotion5_Phys(Item_GObj* gobj) {}

bool itTomato_UnkMotion5_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_802843E4, it_80284458);
    return false;
}

void it_3F14_Logic9_EvtUnk(Item_GObj* gobj, Item_GObj* gobj_ref)
{
    it_8026B894(gobj, gobj_ref);
}
