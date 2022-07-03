#include "ftzelda.h"

void ftZelda_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    fighter->sa.zelda.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;
    
    PUSH_ATTRS(fighter, ftZeldaAttributes);
    
    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* fighterObj) {
    func_8013B5EC(fighterObj);
}

void ftZelda_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
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