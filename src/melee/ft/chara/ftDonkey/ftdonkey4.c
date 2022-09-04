#include <melee/ft/chara/ftDonkey/ftdonkey.h>

s32 ftDonkey_800E0134(HSD_GObj* fighter_gobj) {
    if (func_800C97A8(fighter_gobj)) {
        ftDonkey_800E017C(fighter_gobj);
        return 1;
    }
    return 0;
}

void ftDonkey_800E017C(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    func_800C9840(fighter_gobj, donkey_attr->action_state + 4, 0, 0.0f, donkey_attr->cargo_hold.x20_TURN_SPEED, 0.0f);
}
