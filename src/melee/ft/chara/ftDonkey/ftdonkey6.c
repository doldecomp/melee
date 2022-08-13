#include <ftdonkey.h>

void ftDonkey_800E030C(HSD_GObj* fighterObj) {
    s32 result = func_80094EA4(fighterObj);
    if (result) return; 
}

void ftDonkey_800E0330(HSD_GObj* fighterObj) {
    func_80084DB0(fighterObj);
}

void ftDonkey_800E0350(HSD_GObj* fighterObj) {
    func_80082C74(fighterObj, &ftDonkey_800E05E4);
}

s32 ftDonkey_800E0378(HSD_GObj* fighterObj) {
    s32 result = func_800CAE80(fighterObj);
    if (result) {
        ftDonkey_800E04A4(fighterObj, result);
        return 1;
    }
    return 0;
}

void ftDonkey_800E03C0(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr;
    func_8007D5D4(fp);
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighterObj, donkey_attr->action_state + 7, 0, NULL, 0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(fighterObj, 0.0f);
    func_800CB110(fighterObj, 1, 1.0f);
}