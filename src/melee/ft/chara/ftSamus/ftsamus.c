#include "ftsamus.h"

void ftSamus_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    fighter->sa.samus.x222C = 0;
    fighter->sa.samus.x2230 = 0;
    fighter->sa.samus.x2238 = 0;
    fighter->sa.samus.x2244 = 0;
    fighter->sa.samus.x223C = 0;
    fighter->sa.samus.x2240 = 0;
}

void ftSamus_OnLoad(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    fighter->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fighter, ftSamusAttributes);
    
    func_8026B3F8(item_list[0], 0x5DU);
    func_8026B3F8(item_list[1], 0x5EU);
    func_8026B3F8(item_list[2], 0x5FU);
    func_8026B3F8(item_list[3], 0x60U);
}

void ftSamus_80128428(HSD_GObj* fighterObj) {
    func_80129258(fighterObj);
    func_8012A640(fighterObj);
    func_800D9C98(fighterObj);
}

void ftSamus_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
            case 1:
                func_80070FB4(gobj, 0, 1);
                break;
            case 2:
                func_80070FB4(gobj, 0, 0);
                break;
            case 3:
                func_80070FB4(gobj, 0, 2);
                break;
            case 4:
                func_80070FB4(gobj, 0, 3);
                break;
        }

        if (arg1 != 0) {
            func_80070C48(gobj, 0);
        }
    }
}
