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

MACRO_OnItemPickup(ftDonkey, 1);

void func_8010D888(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!func_8026B2B4(fighter->x1974_heldItem)) {
        func_80070CC4(fighterObj, 1);
    }
}

void func_8010D8D0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!func_8026B2B4(fighter->x1974_heldItem)) {
        func_80070C48(fighterObj, 1);
    }
}

void func_8010D918(HSD_GObj* fighterObj, s32 arg1) {
    func_80070FB4(fighterObj, 1, -1);
    if (arg1) {
        func_80070CC4(fighterObj, 1);
    }
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