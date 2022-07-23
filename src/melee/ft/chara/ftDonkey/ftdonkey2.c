#include "ftdonkey.h"


void ftDonkey_800DF9F0(HSD_GObj* fighterObj) {
    if ((!func_80094EA4(fighterObj)) && (!ftDonkey_800E0378(fighterObj)) && (!ftDonkey_800E0134(fighterObj))) {
        s32 result = ftDonkey_800DFA98(fighterObj);
        if (result) { return;  }
    }
}

void ftDonkey_800DFA50(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}


void ftDonkey_800DFA70(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftDonkey_800E0294);
}

s32 ftDonkey_800DFA98(HSD_GObj* fighterObj) {
    if (ftDonkey_800DFC70(fighterObj)) {
        ftDonkey_800DFAE4(fighterObj, 0.0f);
        return 1;
    }
    return 0;
}

void ftDonkey_800DFAE4(HSD_GObj* fighterObj, f32 argf) {
    Fighter* fighter = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fighter);
    ftDonkey_800DFCA4(
        fighterObj, donkey_attr->x0 + 1, 0, 
        argf, 
        donkey_attr->x8, donkey_attr->xC,  donkey_attr->x10, donkey_attr->x14, donkey_attr->x18, donkey_attr->x1C, 
        1.0f
    ); 
}