#include "itspycloak.h"
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

int it_80276CB8(Item_GObj*);                        /* extern */
void it_80295D04(HSD_GObj* gobj);                   /* extern */


void it_80295C48(Item_GObj* arg0) {
    it_80295D04(arg0);
}

void it_80295C68(Item_GObj* arg0) {
    Item* temp_r4 = arg0->user_data;
    temp_r4->x40_vel.x = temp_r4->x40_vel.y = temp_r4->x40_vel.z = it_804DCB70;
    it_8026B390(arg0);
    Item_80268E5C(arg0, 0, ITEM_ANIM_UPDATE);
}

bool it_80295CB8(void) {
    return false;
}

void it_80295CC0(void) {

}

bool it_80295CC4(Item_GObj* arg0) {
    it_8026D62C(arg0, it_80295D04);
    it_80276CB8(arg0);
    return false;
}

void it_80295D04(HSD_GObj* arg0) {
    Item_80268E5C(arg0, 1, ITEM_ANIM_UPDATE);
}

bool it_80295D2C(void) {
    return false;
}

void it_80295D34(Item_GObj* arg0) {
    Item* item = GET_ITEM(arg0);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(arg0, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80295D64(Item_GObj* arg0) {
    it_8026E15C(arg0, it_80295C68);
    return false;
}

void it_80295D90(Item_GObj* arg0) {
    Item_80268E5C((HSD_GObj* ) arg0, 2, ITEM_ANIM_UPDATE);
}

bool it_80295DB8(void) {
    return false;
}

void it_80295DC0(Item_GObj* arg0) {
    Item_80268E5C((HSD_GObj* ) arg0, 1, 6);
}


void it_80295DE8(Item_GObj* arg0) {
    Item* item = GET_ITEM(arg0);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(arg0, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80295E18(Item_GObj* arg0) {
    if (it_8026DA08(arg0)) {
        return true;
    }
    return false;
}

void it_80295E4C(Item_GObj* arg0) {
    Item_80268E5C((HSD_GObj* ) arg0, 4, ITEM_ANIM_UPDATE);
}

bool it_80295E74(void) {
    return false;
}

void it_80295E7C(void) {

}

bool it_80295E80(Item_GObj* arg0) {
    it_8026E8C4(arg0, it_80295C68, it_80295D04);
    return false;
}

void it_80295EB4(Item_GObj* arg0, Item_GObj* arg1) {
    it_8026B894(arg0, (HSD_GObj* ) arg1);
}


ItemStateTable it_803F6370[] = {
    {   // maybe
        0,
        it_80295CC4,
        it_80295D04,
        it_80276CB8,
    },
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

const float it_804DCB70 = 0x00000000;
