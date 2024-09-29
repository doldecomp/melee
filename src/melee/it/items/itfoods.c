#include "it/items/itfoods.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"
#include "it/items/types.h"
#include "sysdolphin/baselib/random.h"

#include <baselib/gobj.h>

/* 28FC84 */ int it_8028FC84(Item_GObj* arg0);
/* 28FC8C */ void it_8028FC8C(Item_GObj* arg0);
/* 28FCBC */ int it_8028FCBC(Item_GObj* arg0);
/* 28FCE8 */ void it_8028FCE8(HSD_GObj* gobj);
/* 28FD44 */ int it_8028FD44(Item_GObj* arg0);
/* 28FD4C */ void it_8028FD4C(Item_GObj* arg0);
/* 28FD50 */ int it_8028FD50(Item_GObj* arg0);
/* 28FDD8 */ int it_8028FDD8(Item_GObj* arg0);
/* 28FDE0 */ void it_8028FDE0(Item_GObj* arg0);
/* 28FE0C */ int it_8028FE0C(Item_GObj* arg0);
/* 28FE14 */ void it_8028FE14(Item_GObj* arg0);
/* 28FE44 */ int it_8028FE44(Item_GObj* arg0);

ItemStateTable it_803F83F0[] = { { -1, it_8028FC84, it_8028FC8C, it_8028FCBC },
                                 { -1, it_8028FD44, it_8028FD4C, it_8028FD50 },
                                 { -1, it_8028FDD8, it_8028FDE0, NULL },
                                 { -1, it_8028FE0C, it_8028FE14,
                                   it_8028FE44 } };

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

void it_8028FBE4(Item_GObj* arg0)
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

int it_8028FC84(Item_GObj* arg0)
{
    return 0;
}

void it_8028FC8C(Item_GObj* arg0)
{
    ItemAttr* temp_r4;

    Item* item = GET_ITEM(arg0);
    temp_r4 = item->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8028FCBC(Item_GObj* arg0)
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

int it_8028FD44(Item_GObj* gobj)
{
    return 0;
}

void it_8028FD4C(Item_GObj* gobj) {}

int it_8028FD50(Item_GObj* gobj)
{
    it_8026D62C(gobj, it_8028FC5C);
    return 0;
}

void it_8028FD7C(Item_GObj* gobj)
{
    HSD_JObj* jobj = HSD_GObjGetHSDObj(gobj);
    HSD_JObj* child = HSD_JObjGetChild(jobj);
    HSD_JObjClearFlagsAll(child, 0x10U);
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
}

int it_8028FDD8(Item_GObj* gobj)
{
    return 0;
}

void it_8028FDE0(Item_GObj* gobj) {}

void it_8028FDE4(Item_GObj* gobj)
{
    Item_80268E5C((HSD_GObj*) gobj, 3, 6);
}

int it_8028FE0C(Item_GObj* gobj)
{
    return 0;
}

void it_8028FE14(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* temp_r4 = item->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8028FE44(Item_GObj* gobj)
{
    it_8026E414(gobj, it_8028FCE8);
    return 0;
}

void it_8028FE70(Item_GObj* gobj, Item_GObj* arg1)
{
    it_8026B894(gobj, (HSD_GObj*) arg1);
}
