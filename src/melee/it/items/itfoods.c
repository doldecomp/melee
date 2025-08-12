#include "it/items/itfoods.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/types.h"
#include "sysdolphin/baselib/random.h"

#include <baselib/gobj.h>

/* 28FC84 */ bool itFoods_UnkMotion0_Anim(Item_GObj* arg0);
/* 28FC8C */ void itFoods_UnkMotion0_Phys(Item_GObj* arg0);
/* 28FCBC */ bool itFoods_UnkMotion0_Coll(Item_GObj* arg0);
/* 28FCE8 */ void it_8028FCE8(HSD_GObj* gobj);
/* 28FD44 */ bool itFoods_UnkMotion1_Anim(Item_GObj* arg0);
/* 28FD4C */ void itFoods_UnkMotion1_Phys(Item_GObj* arg0);
/* 28FD50 */ bool itFoods_UnkMotion1_Coll(Item_GObj* arg0);
/* 28FDD8 */ bool itFoods_UnkMotion2_Anim(Item_GObj* arg0);
/* 28FDE0 */ void itFoods_UnkMotion2_Phys(Item_GObj* arg0);
/* 28FE0C */ bool itFoods_UnkMotion3_Anim(Item_GObj* arg0);
/* 28FE14 */ void itFoods_UnkMotion3_Phys(Item_GObj* arg0);
/* 28FE44 */ bool itFoods_UnkMotion3_Coll(Item_GObj* arg0);

ItemStateTable it_803F83F0[] = {
    { -1, itFoods_UnkMotion0_Anim, itFoods_UnkMotion0_Phys,
      itFoods_UnkMotion0_Coll },
    { -1, itFoods_UnkMotion1_Anim, itFoods_UnkMotion1_Phys,
      itFoods_UnkMotion1_Coll },
    { -1, itFoods_UnkMotion2_Anim, itFoods_UnkMotion2_Phys, NULL },
    { -1, itFoods_UnkMotion3_Anim, itFoods_UnkMotion3_Phys,
      itFoods_UnkMotion3_Coll }
};

void it_8028F9D8(Item_GObj* arg0, Vec3* arg1, f32 arg8)
{
    Item* temp_r30 = GET_ITEM(arg0);
    Vec4* temp_r6 = temp_r30->xC4_article_data->x4_specialAttributes;
    f32 var_2;
    temp_r30->pos.x =
        arg1->x + (arg8 * temp_r6[temp_r30->xDD4_itemVar.foods.x0].w);
    var_2 = temp_r6[temp_r30->xDD4_itemVar.foods.x0 + 1].x;
    temp_r30->pos.y = var_2 + arg1->y;
    temp_r30->pos.z = arg1->z;
    HSD_JObjSetTranslate(arg0->hsd_obj, &temp_r30->pos);
}

HSD_GObj* it_8028FAF4(Item_GObj* arg0, Vec3* arg1)
{
    SpawnItem spawn;
    HSD_GObj* gobj;
    if (it_8026D324(0x12) == 0) {
        return NULL;
    }
    spawn.kind = 0x12;
    spawn.prev_pos = *arg1;
    if (arg0 != NULL) {
        it_8026BB68(arg0, &spawn.pos);
    } else {
        spawn.pos = spawn.prev_pos;
    }
    spawn.facing_dir = -1.0F;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0.0F;
    spawn.x3C_damage = 0;
    spawn.x0_parent_gobj = NULL;
    spawn.x4_parent_gobj2 = NULL;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0.0F;
    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        it_80274ED8();
    }
    return gobj;
}

void it_3F14_Logic18_Spawned(Item_GObj* arg0)
{
    Item* ip = GET_ITEM(arg0);
    itFoodsAttributes* attr = ip->xC4_article_data->x4_specialAttributes;
    s32 rand = HSD_Randi(*(s32*) ip->xC4_article_data->x4_specialAttributes);
    PAD_STACK(12);
    ip->xDD4_itemVar.foods.heal_amount = attr[rand].x8;
    ip->xDD4_itemVar.foods.x0 = rand;
    it_80273318(arg0, attr[rand].x4, rand);
    it_8028FC5C((HSD_GObj*) arg0);
}

void it_8028FC5C(HSD_GObj* arg0)
{
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
}

bool itFoods_UnkMotion0_Anim(Item_GObj* arg0)
{
    return 0;
}

void itFoods_UnkMotion0_Phys(Item_GObj* arg0)
{
    ItemAttr* temp_r4;

    Item* item = GET_ITEM(arg0);
    temp_r4 = item->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

bool itFoods_UnkMotion0_Coll(Item_GObj* arg0)
{
    it_8026E414(arg0, it_8028FCE8);
    return 0;
}

void it_8028FCE8(HSD_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    PAD_STACK(12);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0.0F;
    Item_8026AE84(item, 0x107, 0x7F, 0x40);
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool itFoods_UnkMotion1_Anim(Item_GObj* gobj)
{
    return 0;
}

void itFoods_UnkMotion1_Phys(Item_GObj* gobj) {}

bool itFoods_UnkMotion1_Coll(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028FC5C);
    return 0;
}

void it_3F14_Logic18_PickedUp(Item_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObjClearFlagsAll(child, 0x10U);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

bool itFoods_UnkMotion2_Anim(Item_GObj* gobj)
{
    return 0;
}

void itFoods_UnkMotion2_Phys(Item_GObj* gobj) {}

void it_3F14_Logic18_Dropped(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

bool itFoods_UnkMotion3_Anim(Item_GObj* gobj)
{
    return 0;
}

void itFoods_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* temp_r4 = item->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

bool itFoods_UnkMotion3_Coll(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028FCE8);
    return 0;
}

void it_3F14_Logic18_EvtUnk(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, (HSD_GObj*) arg1);
}
