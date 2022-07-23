#include "ftdonkey.h"

s32 ftDonkey_800DF938(HSD_GObj* fighterObj) {
    if (func_8008A1FC(fighterObj)) {
        ftDonkey_800DF980(fighterObj);
        return 1;
    }
    return 0;
}

void ftDonkey_800DF980(HSD_GObj* fighterObj) {
    s32 unused[2]; /// getFighter inlines not working
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr;
    if (fighter->xE0_ground_or_air == GA_Air) {
        func_8007D7FC(fighter);
    }
    donkey_attr = getFtSpecialAttrs2CC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, donkey_attr->x0, 0, NULL, 0.0f, 1.0f, 0.0f);
}