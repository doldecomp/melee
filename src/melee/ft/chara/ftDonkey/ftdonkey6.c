#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_800E030C(HSD_GObj* fighter_gobj) {
    s32 result = func_80094EA4(fighter_gobj);
    if (result) return; 
}

void ftDonkey_800E0330(HSD_GObj* fighter_gobj) {
    func_80084DB0(fighter_gobj);
}

void ftDonkey_800E0350(HSD_GObj* fighter_gobj) {
    func_80082C74(fighter_gobj, &ftDonkey_800E05E4);
}

s32 ftDonkey_800E0378(HSD_GObj* fighter_gobj) {
    s32 result = func_800CAE80(fighter_gobj);
    if (result) {
        ftDonkey_800E04A4(fighter_gobj, result);
        return 1;
    }
    return 0;
}

void ftDonkey_800E03C0(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr;
    func_8007D5D4(fp);
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, donkey_attr->action_state + 7, 0, NULL, 0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    func_800CB110(fighter_gobj, 1, 1.0f);
}
