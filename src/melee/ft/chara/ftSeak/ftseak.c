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

void ftSeak_80110198(HSD_GObj* fighterObj) {
    func_80111FBC(fighterObj);
    func_80110E88(fighterObj);
}

void ftSeak_801101CC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->sa.seak.x222C == 6) {
        func_800BFFD0(fighter, 0x56, 0);
    }
}

void ftSeak_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
            case 1:
                func_80070FB4(gobj, 1, 1);
                break;
            case 2:
                func_80070FB4(gobj, 1, 0);
                break;
            case 3:
                func_80070FB4(gobj, 1, 2);
                break;
            case 4:
                func_80070FB4(gobj, 1, 3);
                break;
        }

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}