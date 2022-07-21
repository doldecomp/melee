#include "ftdonkey.h"


void ftDonkey_800E0568(HSD_GObj* fighterObj) {
    if (!func_80094EA4(fighterObj)) {
        func_800CB59C(fighterObj);
    }
}

void ftDonkey_800E05A4(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}


void ftDonkey_800E05C4(HSD_GObj* fighterObj) {
    func_800DFA70(fighterObj);
}

void ftDonkey_800E05E4(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fighter);
    fighter->x2344_f32 = donkey_attr->x28;
    donkey_attr = getFtSpecialAttrs2CC(fighter);
    func_800D5AEC(fighterObj, donkey_attr->x0 + 8, 1, 0, fighter, 0.0f, 1.0f);
    ftAnim_SetAnimRate(fighterObj, 0.0f);
}

void ftDonkey_800E0648(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->x2344_f32 <= 0.0f) {
        func_800DF980(fighterObj);
    }
    fighter->x2344_f32 -= 1.0f;
}