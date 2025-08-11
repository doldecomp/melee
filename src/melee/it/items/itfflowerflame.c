#include <placeholder.h>

#include "itfflowerflame.h"

#include "it/inlines.h"
#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/it_2725.h"
#include "it/item.h"

/* 29AA1C */ static void it_8029AA1C(HSD_GObj*);
/* 29AA6C */ static bool itFflowerflame_UnkMotion0_Anim(Item_GObj*);
/* 29AB60 */ static void itFflowerflame_UnkMotion0_Phys(HSD_GObj*);
/* 29AB64 */ static bool itFflowerflame_UnkMotion0_Coll(Item_GObj*);
/* 29AB90 */ static void it_8029AB90(HSD_GObj*);
/* 29ABCC */ static bool itFflowerflame_UnkMotion1_Anim(Item_GObj*);
/* 29ACCC */ static void itFflowerflame_UnkMotion1_Phys(Item_GObj*);
/* 29ACFC */ static bool itFflowerflame_UnkMotion1_Coll(HSD_GObj*);
/* 29AD58 */ static bool itFflowerflame_UnkMotion2_Anim(Item_GObj*);
/* 29ADD0 */ static bool itFflowerflame_UnkMotion3_Anim(Item_GObj*);
/* 29AED0 */ static void itFflowerflame_UnkMotion3_Phys(Item_GObj*);
/* 29AF00 */ static bool itFflowerflame_UnkMotion3_Coll(Item_GObj*);
/* 29AF70 */ static bool itFflowerflame_UnkMotion4_Anim(Item_GObj*);
/* 29B070 */ static void itFflowerflame_UnkMotion4_Phys(HSD_GObj*);
/* 29B074 */ static bool itFflowerflame_UnkMotion4_Coll(Item_GObj*);

ItemStateTable it_803F66C8[] = {
    { 0, itFflowerflame_UnkMotion0_Anim, itFflowerflame_UnkMotion0_Phys, itFflowerflame_UnkMotion0_Coll },
    { 0, itFflowerflame_UnkMotion1_Anim, itFflowerflame_UnkMotion1_Phys, itFflowerflame_UnkMotion1_Coll },
    { 0, itFflowerflame_UnkMotion2_Anim, NULL, NULL },
    { 0, itFflowerflame_UnkMotion3_Anim, itFflowerflame_UnkMotion3_Phys, itFflowerflame_UnkMotion3_Coll },
    { 0, itFflowerflame_UnkMotion4_Anim, itFflowerflame_UnkMotion4_Phys, itFflowerflame_UnkMotion4_Coll },
};

HSD_GObj* it_8029A748(Item_GObj* arg0, Vec3* arg1, Fighter_Part arg2, f32 arg3)
{
    SpawnItem spawn;

    spawn.kind = It_Kind_F_Flower_Flame;
    spawn.prev_pos = *arg1;
    spawn.prev_pos.z = 0.0F;
    it_8026BB68(arg0, &spawn.pos);
    spawn.facing_dir = arg3;
    spawn.x3C_damage = 0;
    spawn.vel.x = spawn.vel.y = spawn.vel.z = 0;
    spawn.x0_parent_gobj = arg0;
    spawn.x4_parent_gobj2 = spawn.x0_parent_gobj;
    spawn.x44_flag.b0 = true;
    spawn.x40 = 0;

    {
        Item_GObj* gobj = Item_80268B18(&spawn);
        if (gobj != NULL) {
            Vec3 temp_pos;
            HSD_JObj* jobj;
            Item* item = GET_ITEM(gobj);
            f32 lifetime =
                *(f32*) item->xC4_article_data->x4_specialAttributes;
            it_80275158(gobj, lifetime);
            Item_8026AB54(gobj, arg0, arg2);
            it_8026B3A8(gobj);
            jobj = it_80272CC0(gobj, 2);
            HSD_JObjGetTranslation(jobj, &temp_pos);
            item->xDD4_itemVar.fflowerflame.pos.x = temp_pos.x;
            item->xDD4_itemVar.fflowerflame.pos.y = temp_pos.y;
            item->xDD4_itemVar.fflowerflame.pos.z = temp_pos.z;
        }
        return gobj;
    }
}

void it_8029A89C(Item_GObj* arg0, f32 arg1)
{
    HSD_JObj* temp_r3;
    PAD_STACK(4);

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

void it_3F14_Logic41_Spawned(Item_GObj* arg0)
{
    it_8026B3A8(arg0);
}

void it_8029AA1C(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = 0;
    Item_80268E5C(gobj, 0, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool itFflowerflame_UnkMotion0_Anim(Item_GObj* arg0)
{
    HSD_JObj* jobj;
    Item* ip = GET_ITEM(arg0);
    it_80272F7C(it_80272CC0(arg0, 1), ip->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(arg0, 2);
    HSD_JObjSetTranslate(jobj, &ip->xDD4_itemVar.fflowerflame.pos);
    return false;
}

void itFflowerflame_UnkMotion0_Phys(HSD_GObj* arg0) {}

bool itFflowerflame_UnkMotion0_Coll(Item_GObj* arg0)
{
    it_8026D62C(arg0, it_8029AB90);
    return false;
}

void it_8029AB90(HSD_GObj* gobj)
{
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool itFflowerflame_UnkMotion1_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM((HSD_GObj*) gobj);
    it_80272F7C(it_80272CC0(gobj, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(gobj, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(gobj);
}

void itFflowerflame_UnkMotion1_Phys(Item_GObj* gobj)
{
    ItemAttr* temp_r4;

    Item* item = GET_ITEM(gobj);
    temp_r4 = item->xCC_item_attr;
    it_80272860(gobj, temp_r4->x10_fall_speed, temp_r4->x14_fall_speed_max);
}

bool itFflowerflame_UnkMotion1_Coll(HSD_GObj* gobj)
{
    return it_8026DF34(gobj);
}

void it_3F14_Logic41_PickedUp(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 2, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool itFflowerflame_UnkMotion2_Anim(Item_GObj* gobj)
{
    Item* ip = GET_ITEM(gobj);
    it_80272F7C(it_80272CC0(gobj, 1), ip->xDD4_itemVar.fflowerflame.unk);
    return false;
}

void it_3F14_Logic41_Dropped(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 1, 6);
    it_8026B3A8(gobj);
}

bool itFflowerflame_UnkMotion3_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM(gobj);
    it_80272F7C(it_80272CC0(gobj, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(gobj, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(gobj);
}

void itFflowerflame_UnkMotion3_Phys(Item_GObj* gobj)
{
    Item* item = GET_ITEM(gobj);
    ItemAttr* attrs = item->xCC_item_attr;
    it_80272860(gobj, attrs->x10_fall_speed, attrs->x14_fall_speed_max);
}

bool itFflowerflame_UnkMotion3_Coll(Item_GObj* gobj)
{
    if (it_8026DA08(gobj)) {
        return true;
    }
    return false;
}

void it_3F14_Logic41_EnteredAir(Item_GObj* gobj)
{
    Item_80268E5C(gobj, 4, ITEM_ANIM_UPDATE);
    it_8026B3A8(gobj);
}

bool itFflowerflame_UnkMotion4_Anim(Item_GObj* gobj)
{
    HSD_JObj* jobj;
    Item* item = GET_ITEM(gobj);
    it_80272F7C(it_80272CC0(gobj, 1), item->xDD4_itemVar.fflowerflame.unk);
    jobj = it_80272CC0(gobj, 2);
    HSD_JObjSetTranslate(jobj, &item->xDD4_itemVar.fflowerflame.pos);
    return it_80273130(gobj);
}

void itFflowerflame_UnkMotion4_Phys(Item_GObj* gobj) {}

bool itFflowerflame_UnkMotion4_Coll(Item_GObj* gobj)
{
    it_8026E8C4(gobj, it_8029AA1C, it_8029AB90);
    return false;
}

void it_3F14_Logic41_EvtUnk(Item_GObj* arg0, Item_GObj* arg1)
{
    it_8026B894(arg0, arg1);
}
