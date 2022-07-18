#include "ftdonkey.h"

/// TODO remove these float externs once they are moved over
extern f32 lbl_804D9188;

BOOL ftDonkey_800E0750(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    
    if (func_8008E984(fighter)) {
        return 1;
    }
    func_8008D8D8(fighter->dmg.x1850_forceApplied);
    if (func_8008D8E8() < 3) {
        return 1;
    }
    return 0;
}

void ftDonkey_800E07B0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = fighter->x2CC;
    func_8008DCE0(fighterObj, &donkey_attr->x0_arr[9], lbl_804D9188);
}
 
void ftDonkey_800E07E4(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8008F744(fighterObj);
    if (!fighter->x221C_flag.bits.b6) {
        if (fighter->xE0_ground_or_air == GA_Air) {
            func_800E0294(fighterObj);
        } else {
            func_800DF980(fighterObj); 
        }
    }
}

void ftDonkey_800E0848(HSD_GObj* fighterObj) {
    func_8008FB18(fighterObj);
}

void ftDonkey_800E0868(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    if (fighter->xE0_ground_or_air == GA_Ground) {
        if (!func_80082708(fighterObj)) {
            func_8007D5D4(fighter);
        }
    } else if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fighter);
    }
}