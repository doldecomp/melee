#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_800E0440(HSD_GObj* fighter_gobj) {
    s32 result = func_80094EA4(fighter_gobj);
    if (result) return; 
}

void ftDonkey_800E0464(HSD_GObj* fighter_gobj) {
    func_800CB438(fighter_gobj);
}

void ftDonkey_800E0484(HSD_GObj* fighter_gobj) {
    ftDonkey_800E0350(fighter_gobj);
}

void ftDonkey_800E04A4(HSD_GObj* fighter_gobj, s32 arg1) {
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftDonkeyAttributes* donkey_attr2;
    fp->x2344_stateVar2_s32 = arg1;
    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3_f32 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fp);
    
    Fighter_ActionStateChange_800693AC(fighter_gobj, donkey_attr2->action_state + 5, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
}

void ftDonkey_800E0518(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x2348_stateVar3_f32 <= 0.0f) {
        ftDonkey_800E03C0(fighter_gobj);
    }
    fp->x2348_stateVar3_f32 -= 1.0f;
}
