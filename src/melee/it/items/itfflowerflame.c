#include "itfflowerflame.h"

#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/it_266F.h"
#include "it/item.h"

/* 29AA1C */ static void it_8029AA1C(HSD_GObj*);
/* 29AA6C */ static int it_8029AA6C(Item_GObj*);
/* 29AB60 */ static void it_8029AB60(HSD_GObj*);
/* 29AB64 */ static int it_8029AB64(Item_GObj*);
/* 29AB90 */ static void it_8029AB90(HSD_GObj*);
/* 29ABCC */ static int it_8029ABCC(Item_GObj*);
/* 29ACCC */ static void it_8029ACCC(Item_GObj*);
/* 29ACFC */ static int it_8029ACFC(HSD_GObj*);
/* 29AD58 */ static int it_8029AD58(Item_GObj*);
/* 29ADD0 */ static int it_8029ADD0(Item_GObj*);
/* 29AED0 */ static void it_8029AED0(Item_GObj*);
/* 29AF00 */ static int it_8029AF00(Item_GObj*);
/* 29AF70 */ static int it_8029AF70(Item_GObj*);
/* 29B070 */ static void it_8029B070(HSD_GObj*);
/* 29B074 */ static int it_8029B074(Item_GObj*);

ItemStateTable it_803F66C8[] = {
    { 0, it_8029AA6C, it_8029AB60, it_8029AB64 },
    { 0, it_8029ABCC, it_8029ACCC, it_8029ACFC },
    { 0, it_8029AD58, NULL, NULL },
    { 0, it_8029ADD0, it_8029AED0, it_8029AF00 },
    { 0, it_8029AF70, it_8029B070, it_8029B074 },
};

HSD_GObj* it_8029A748(Item_GObj* arg0, Vec3* arg1, u8 arg2, f32 arg3)
{
    SpawnItem spawn;
    Item_GObj* gobj;

    spawn.kind = It_Kind_F_Flower_Flame;
    spawn.prev_pos = *arg1;
    spawn.prev_pos.z = 0.0F;
    it_8026BB68(arg0, &spawn.pos);
    spawn.facing_dir = arg3;
    spawn.x3C_damage = 0;
    spawn.vel.z = 0.0F;
    spawn.vel.y = 0.0F;
    spawn.vel.x = 0.0F;
    spawn.x0_parent_gobj = (HSD_GObj*) arg0;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.bits.b0 = true;
    spawn.x40 = 0;

    gobj = Item_80268B18(&spawn);
    if (gobj != NULL) {
        Vec3 temp_pos;
        HSD_JObj* jobj;
        Item* item = GET_ITEM((HSD_GObj*) gobj);
        f32 lifetime = *(f32*) item->xC4_article_data->x4_specialAttributes;
        it_80275158((HSD_GObj*) gobj, lifetime);
        Item_8026AB54((HSD_GObj*) gobj, (HSD_GObj*) arg0, arg2);
        it_8026B3A8(gobj);
        jobj = it_80272CC0(gobj, 2);
        HSD_JObjGetTranslation(jobj, &temp_pos);
        item->xDD4_itemVar.fflowerflame.pos.x = temp_pos.x;
        item->xDD4_itemVar.fflowerflame.pos.y = temp_pos.y;
        item->xDD4_itemVar.fflowerflame.pos.z = temp_pos.z;
    }
    return (HSD_GObj*) gobj;
}

void it_8029A89C(Item_GObj* arg0, f32 arg1)
{
    HSD_JObj* temp_r3;
    f32 pad;

    if (arg0 != NULL) {
        Item* item = GET_ITEM((HSD_GObj*) arg0);
        if (item != NULL) {
            temp_r3 = it_80272CC0(arg0, 1);
            item->xDD4_itemVar.fflowerflame.unk = arg1;
            it_80272F7C(temp_r3, item->xDD4_itemVar.fflowerflame.unk);
        }
    }
}

void it_8029A8F4(Item_GObj* arg0, Vec3* arg1)
{
    HSD_JObj* jobj;
    Vec3 temp_pos;

    if (arg0 != NULL) {
        Item* item = GET_ITEM((HSD_GObj*) arg0);
        if (item != NULL) {
            jobj = it_80272CC0(arg0, 2);
            temp_pos.x = item->xDD4_itemVar.fflowerflame.pos.x + arg1->x;
            temp_pos.y = item->xDD4_itemVar.fflowerflame.pos.y + arg1->y;
            temp_pos.z = item->xDD4_itemVar.fflowerflame.pos.z + arg1->z;
            HSD_JObjSetTranslate(jobj, &temp_pos);
        }
    }
}

void it_8029A9FC(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
}

void it_8029AA1C(HSD_GObj* arg0)
{
    Item* item = GET_ITEM(arg0);
    item->x40_vel.z = 0.0F;
    item->x40_vel.y = 0.0F;
    item->x40_vel.x = 0.0F;
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
    it_8026B3A8((Item_GObj*) arg0);
}

int it_8029AA6C(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_80272F7C(it_80272CC0(arg0, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(arg0, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return 0;
}

void it_8029AB60(HSD_GObj* arg0)
{
    return;
}

int it_8029AB64(Item_GObj* arg0)
{
    it_8026D62C(arg0, it_8029AB90);
    return 0;
}

void it_8029AB90(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026B3A8((Item_GObj*) gobj);
}

int it_8029ABCC(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_80272F7C(it_80272CC0(arg0, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(arg0, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(arg0);
}

void it_8029ACCC(Item_GObj* arg0)
{
    ItemAttr* temp_r4;

    Item* item = GET_ITEM((HSD_GObj*) arg0);
    temp_r4 = item->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8029ACFC(HSD_GObj* arg0)
{
    return it_8026DF34();
}

void it_8029AD1C(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 2, ITEM_ANIM_UPDATE);
    it_8026B3A8(arg0);
}

int it_8029AD58(Item_GObj* arg0)
{
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_80272F7C(it_80272CC0(arg0, 1), item->xDD4_itemVar.fflowerflame.unk);
    return 0;
}

void it_8029AD94(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 1, 6);
    it_8026B3A8(arg0);
}

int it_8029ADD0(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_80272F7C(it_80272CC0(arg0, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(arg0, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(arg0);
}

void it_8029AED0(Item_GObj* arg0)
{
    ItemAttr* temp_r4;

    Item* item = GET_ITEM((HSD_GObj*) arg0);
    temp_r4 = item->xCC_item_attr;
    it_80272860(arg0, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

int it_8029AF00(Item_GObj* arg0)
{
    if (it_8026DA08(arg0) != 0) {
        return 1;
    }
    return 0;
}

void it_8029AF34(Item_GObj* arg0)
{
    Item_80268E5C((HSD_GObj*) arg0, 4, ITEM_ANIM_UPDATE);
    it_8026B3A8(arg0);
}

int it_8029AF70(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM((HSD_GObj*) arg0);
    it_80272F7C(it_80272CC0(arg0, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(arg0, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(arg0);
}

void it_8029B070(HSD_GObj* arg0)
{
    return;
}

int it_8029B074(Item_GObj* arg0)
{
    it_8026E8C4(arg0, it_8029AA1C, it_8029AB90);
    return 0;
}

void it_8029B0A8(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, (HSD_GObj*) arg1);
}
