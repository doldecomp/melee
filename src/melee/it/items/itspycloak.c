#include "itspycloak.h"
#include <melee/it/it_266F.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>

int it_80276CB8(Item_GObj*);
void it_80295D04(HSD_GObj* gobj);
const float it_804DCB70;

void it_80295C48(Item_GObj* item_gobj) {
    it_80295D04(item_gobj);
}

void it_80295C68(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    item->x40_vel.x = item->x40_vel.y = item->x40_vel.z = it_804DCB70;
    it_8026B390(item_gobj);
    Item_80268E5C(item_gobj, 0, ITEM_ANIM_UPDATE);
}

bool it_80295CB8(void) {
    return false;
}

void it_80295CC0(void) {

}

bool it_80295CC4(Item_GObj* item_gobj) {
    it_8026D62C(item_gobj, it_80295D04);
    it_80276CB8(item_gobj);
    return false;
}

void it_80295D04(HSD_GObj* gobj) {
    Item_80268E5C(gobj, 1, ITEM_ANIM_UPDATE);
}

bool it_80295D2C(void) {
    return false;
}

void it_80295D34(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80295D64(Item_GObj* item_gobj) {
    it_8026E15C(item_gobj, it_80295C68);
    return false;
}

void it_80295D90(Item_GObj* item_gobj) {
    Item_80268E5C((HSD_GObj* ) item_gobj, 2, ITEM_ANIM_UPDATE);
}

bool it_80295DB8(void) {
    return false;
}

void it_80295DC0(Item_GObj* item_gobj) {
    Item_80268E5C((HSD_GObj* ) item_gobj, 1, 6);
}


void it_80295DE8(Item_GObj* item_gobj) {
    Item* item = GET_ITEM(item_gobj);
    ItemAttr* attr = item->xCC_item_attr;

    it_80272860(item_gobj, attr->x10_fall_speed, attr->x14_fall_speed_max);
}

bool it_80295E18(Item_GObj* item_gobj) {
    if (it_8026DA08(item_gobj)) {
        return true;
    }
    return false;
}

void it_80295E4C(Item_GObj* item_gobj) {
    Item_80268E5C((HSD_GObj* ) item_gobj, 4, ITEM_ANIM_UPDATE);
}

bool it_80295E74(void) {
    return false;
}

void it_80295E7C(void) {

}

bool it_80295E80(Item_GObj* item_gobj) {
    it_8026E8C4(item_gobj, it_80295C68, it_80295D04);
    return false;
}

void it_80295EB4(Item_GObj* item_gobj, HSD_GObj* ref) {
    it_8026B894(item_gobj, ref);
}


ItemStateTable it_803F6370[] = {      // Function pointers are an educated guess
    {                                 // based on the table in itstar.c.
        0,                            // Zeros were added to make the size of
        it_80295CC4,                  // .data match in objdiff.
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

const float it_804DCB70 = 0x00000000; // initialized here to get it into .sdata2
