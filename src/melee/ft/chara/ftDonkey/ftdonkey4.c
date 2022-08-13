#include <ftdonkey.h>

s32 ftDonkey_800E0134(HSD_GObj* fighterObj) {
    if (func_800C97A8(fighterObj)) {
        ftDonkey_800E017C(fighterObj);
        return 1;
    }
    return 0;
}

void ftDonkey_800E017C(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    func_800C9840(fighterObj, donkey_attr->action_state + 4, 0, 0.0f, donkey_attr->cargo_hold.x20_TURN_SPEED, 0.0f);
}