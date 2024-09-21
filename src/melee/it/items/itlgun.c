#include "itlgun.h"

#include "it/it_266F.h"
#include "it/it_26B1.h"
#include "it/types.h"

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <melee/it/item.h>

// void it_80298168(s32);                              /* extern */
void it_80298168(HSD_GObj*); /* extern */
int it_8028E828(HSD_GObj*);  /* static */
void it_8028E830(HSD_GObj*); /* static */
int it_8028E834(HSD_GObj*);  /* static */
// void it_8028E860(s32 arg0, Item*);                  /* static */
void it_8028E860(HSD_GObj*); /* static */
int it_8028E888(HSD_GObj*);  /* static */
void it_8028E890(HSD_GObj*); /* static */
int it_8028E8C0(HSD_GObj*);  /* static */
int it_8028E92C(HSD_GObj*);  /* static */
void it_8028E934(HSD_GObj*); /* static */
int it_8028E96C(HSD_GObj*);  /* static */
void it_8028E9B4(HSD_GObj*); /* static */
void it_8028EA08(HSD_GObj*); /* static */
int it_8028EB28(HSD_GObj*);  /* static */
void it_8028EB30(HSD_GObj*); /* static */
int it_8028EB34(HSD_GObj*);  /* static */

ItemStateTable it_803F5CC8[] = {
    { -1, it_8028E828, it_8028E830, it_8028E834 },
    { -1, it_8028E888, it_8028E890, it_8028E8C0 },
    { -1, it_8028E92C, it_8028E934, NULL },
    { 0, it_8028E96C, it_8028E9B4, NULL },
    { 1, it_8028E888, it_8028EA08, it_8028E8C0 },
    { -1, it_8028EB28, it_8028EB30, it_8028EB34 },
};

void it_8028E738(Item_GObj* item_gobj)
{
    Item* item;
    ItLGunAttr* item_spec_attr;

    item = item_gobj->user_data;
    item_spec_attr = item->xC4_article_data->x4_specialAttributes;
    item->xD4C = item_spec_attr->x0;
    item->xDD4_itemVar.capsule.x0 = 0;
    // it_8028E860(item_spec_attr->x0_float, item);
    it_8028E860((HSD_GObj*) item_gobj);
}

// void it_8028E774(void* item_gobj, void* arg1) {
// void it_8028E774(Item_GObj* item_gobj, itUnkAttributes* arg1) {
void it_8028E774(Item_GObj* item_gobj, Vec3* arg1)
{
    ItLGunAttr* item_spec_attr;

    item_spec_attr =
        ((Item*) item_gobj->user_data)->xC4_article_data->x4_specialAttributes;
    // arg1->unk0 = (f32) item_spec_attr->x4_float;
    // arg1->x0_float = item_spec_attr->x4;
    arg1->x = item_spec_attr->x4;
    // arg1->unk4 = (f32) item_spec_attr->x8;
    // arg1->x4_float = item_spec_attr->x8;
    arg1->y = item_spec_attr->x8;
    // arg1->unk8 = (f32) item_spec_attr->xC;
    // arg1->x8 = item_spec_attr->xC;
    arg1->z = item_spec_attr->xC;
}

// void it_8028E79C(void* item_gobj) {
// void it_8028E79C(Item_GObj* item_gobj) {
void it_8028E79C(Item_GObj* item_gobj, f32 dir)
{
    Item* item;

    item = item_gobj->user_data;
    if (item->xD4C > 0) {
        item->xD4C -= 1;
    }
    it_80298168(item->owner);
}

void it_8028E7D8(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.z = 0.0f;
    item->x40_vel.y = 0.0f;
    item->x40_vel.x = 0.0f;
    it_8026B390((Item_GObj*) item_gobj);
    Item_80268E5C((Item_GObj*) item_gobj, 0, ITEM_ANIM_UPDATE);
}

int it_8028E828(HSD_GObj* item_gobj)
{
    return 0;
}

void it_8028E830(HSD_GObj* item_gobj) {}

int it_8028E834(HSD_GObj* item_gobj)
{
    it_8026D62C((Item_GObj*) item_gobj, it_8028E860);
    return 0;
}

// void it_8028E860(s32 arg0, Item* item) {
void it_8028E860(HSD_GObj* item_gobj)
{
    Item_80268E5C((Item_GObj*) item_gobj, 1, ITEM_ANIM_UPDATE);
}

int it_8028E888(HSD_GObj* item_gobj)
{
    return 0;
}

void it_8028E890(HSD_GObj* item_gobj)
{
    ItemAttr* item_comm_attr;

    item_comm_attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860((Item_GObj*) item_gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
}

int it_8028E8C0(HSD_GObj* item_gobj)
{
    if (((Item*) item_gobj->user_data)->xD4C != 0) {
        it_8026E15C((Item_GObj*) item_gobj, it_8028E7D8);
        return 0;
    }
    return it_8026DF34((Item_GObj*) item_gobj);
}

void it_8028E904(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 2, ITEM_ANIM_UPDATE);
}

int it_8028E92C(HSD_GObj* item_gobj)
{
    return 0;
}

void it_8028E934(HSD_GObj* item_gobj) {}

// void it_8028E938(HSD_GObj* item_gobj) {
void it_8028E938(Item_GObj* item_gobj)
{
    ((Item*) item_gobj->user_data)->xDD4_itemVar.lgun.x0 = 0x28;
    Item_80268E5C(item_gobj, 3, ITEM_ANIM_UPDATE);
}

// s32 it_8028E96C(HSD_GObj* item_gobj) {
int it_8028E96C(HSD_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.lgun.x0 -= 1;
    if ((int) item->xDD4_itemVar.lgun.x0 <= 0) {
        Item_80268E5C((Item_GObj*) item_gobj, 2, ITEM_ANIM_UPDATE);
    }
    return 0;
}

void it_8028E9B4(HSD_GObj* item_gobj) {}

void it_8028E9B8(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 4, 6);
}

void it_8028E9E0(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 4, 6);
}

void it_8028EA08(HSD_GObj* item_gobj)
{
    ItemAttr* item_comm_attr;

    item_comm_attr = ((Item*) item_gobj->user_data)->xCC_item_attr;
    it_80272860((Item_GObj*) item_gobj, item_comm_attr->x10_fall_speed,
                item_comm_attr->x14_fall_speed_max);
    it_80274658((HSD_GObj*) item_gobj, it_804D6D28->x68_float);
}

int it_8028EA54(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return 0;
}

int it_8028EA78(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim((Item_GObj*) item_gobj);
    return 0;
}

int it_8028EA9C(Item_GObj* item_gobj)
{
    itColl_BounceOffVictim(item_gobj);
    return 0;
}

int it_8028EAC0(Item_GObj* item_gobj)
{
    return it_80273030(item_gobj);
}

int it_8028EAE0(Item_GObj* item_gobj)
{
    return itColl_BounceOffShield(item_gobj);
}

void it_8028EB00(Item_GObj* item_gobj)
{
    Item_80268E5C(item_gobj, 5, ITEM_ANIM_UPDATE);
}

int it_8028EB28(HSD_GObj* item_gobj)
{
    return 0;
}

void it_8028EB30(HSD_GObj* item_gobj) {}

int it_8028EB34(HSD_GObj* item_gobj)
{
    it_8026E8C4((Item_GObj*) item_gobj, (void (*)(HSD_GObj*)) it_8028E7D8,
                it_8028E860);
    return 0;
}

// void it_8028EB68(Item_GObj* item_gobj_1, Item_GObj* item_gobj_2) {
void it_8028EB68(Item_GObj* item_gobj, HSD_GObj* ref_gobj)
{
    it_8026B894(item_gobj, ref_gobj);
}