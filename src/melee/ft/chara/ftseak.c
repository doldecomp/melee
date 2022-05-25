#include "ftseak.h"

void ftSeak_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->sa.seak.x222C = 0;
    fighter->sa.seak.x2230 = 0;
    fighter->sa.seak.x2234 = 0;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, -1);
}

void ftSeak_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    fighter->x2224_flag.bits.b7 = 1;
    
    PUSH_ATTRS(fighter, ftSeakAttributes);
    
    func_8026B3F8(item_list[0], 0x4FU);
    func_8026B3F8(item_list[1], 0x50U);
    func_8026B3F8(item_list[2], 0x55U);
    func_8026B3F8(item_list[3], 0x61U);
}
