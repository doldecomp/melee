#include "ftpikachu.h"

s32 func_801275CC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;

    s32 value = fighter->x2071_alt.b0_3;

    switch (value) {
        case 1: 
        case 2: 
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            return 1;
        default:
            return 0;

    }

}

void func_80127608(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80030E44(2, &fighter->xB0_pos);
    func_8007EBAC(fighter, 0xB, 0);
}