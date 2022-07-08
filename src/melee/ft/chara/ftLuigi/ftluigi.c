#include "ftluigi.h"

void ftLuigi_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    fighter->sa.luigi.x2234 = 0;
}

void ftLuigi_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    PUSH_ATTRS(fighter, ftLuigiAttributes);
    
    func_8026B3F8(item_list[0], 0x69U);
}

void ftLuigi_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftLuigi_OnItemInvisible(HSD_GObj* fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftLuigi_OnItemVisible(HSD_GObj* fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftLuigi_OnItemDrop(HSD_GObj* gobj, BOOL bool1) {
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}