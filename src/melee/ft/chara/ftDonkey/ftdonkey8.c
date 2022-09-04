#include <melee/ft/chara/ftDonkey/ftdonkey.h>


void ftDonkey_800E0568(HSD_GObj* fighter_gobj) {
    if (!func_80094EA4(fighter_gobj)) {
        func_800CB59C(fighter_gobj);
    }
}

void ftDonkey_800E05A4(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}


void ftDonkey_800E05C4(HSD_GObj* fighter_gobj) {
    ftDonkey_800DFA70(fighter_gobj);
}

void ftDonkey_800E05E4(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    fp->x2344_f32 = donkey_attr->cargo_hold.x28_LANDING_LAG;
    donkey_attr = getFtSpecialAttrs2CC(fp);
    func_800D5AEC(fighter_gobj, donkey_attr->action_state + 8, 1, 0, fp, 0.0f, 1.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
}

void ftDonkey_800E0648(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (fp->x2344_f32 <= 0.0f) {
        ftDonkey_800DF980(fighter_gobj);
    }
    fp->x2344_f32 -= 1.0f;
}
