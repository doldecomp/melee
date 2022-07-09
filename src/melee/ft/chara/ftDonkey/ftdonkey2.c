#include "ftdonkey.h"

void ftDonkey_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->sa.dk.x222C = 0;
    func_80074A4C(fighterObj, 0, 0);
}

void func_8010D774(HSD_GObj* fighterObj) {
    func_8010FAF0(fighterObj);
    func_80110074(fighterObj);
}

void ftDonkey_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftDonkey_OnItemInvisible(HSD_GObj* fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftDonkey_OnItemVisible(HSD_GObj* fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftDonkey_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void func_8010D96C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* attr = fighter->x2D4_specialAttributes;
    if (fighter->sa.dk.x222C == attr->x2C) {
        func_800BFFD0(fighter, 0x39, 0);
    }
}


void ftDonkey_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftData* ftdata = fighter->x10C_ftData;
    ftDonkeyAttributes* ftData_attr =  ftdata->ext_attr;
    
    ftData_attr->x8 = func_8001E8F8(func_80085E50(fighter, 0x128U));
    ftData_attr->xC = func_8001E8F8(func_80085E50(fighter, 0x129U));
    ftData_attr->x10 = func_8001E8F8(func_80085E50(fighter, 0x12AU));
    PUSH_ATTRS(fighter, ftDonkeyAttributes);
    
    fighter->x2222_flag.bits.b0 = 1;
    fighter->x2CC = fighter->x2D4_specialAttributes;
}