#include <ftdonkey.h>

void ftDonkey_800E0440(HSD_GObj* fighterObj) {
    s32 result = func_80094EA4(fighterObj);
    if (result) return; 
}

void ftDonkey_800E0464(HSD_GObj* fighterObj) {
    func_800CB438(fighterObj);
}

void ftDonkey_800E0484(HSD_GObj* fighterObj) {
    ftDonkey_800E0350(fighterObj);
}

void ftDonkey_800E04A4(HSD_GObj* fighterObj, s32 arg1) {
    Fighter* fighter = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fighter);
    ftDonkeyAttributes* donkey_attr2;
    fighter->x2344_stateVar2_s32 = arg1;
    fighter->x2340_stateVar1 = 0;
    fighter->x2348_stateVar3_f32 = donkey_attr->cargo_hold.x24_JUMP_STARTUP_LAG;
    donkey_attr2 = getFtSpecialAttrs2CC(fighter);
    
    Fighter_ActionStateChange_800693AC(fighterObj, donkey_attr2->action_state + 5, 0, NULL, 0.0f, 1.0f, 0.0f);
    ftAnim_SetAnimRate(fighterObj, 0.0f);
}

void ftDonkey_800E0518(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    if (fighter->x2348_stateVar3_f32 <= 0.0f) {
        ftDonkey_800E03C0(fighterObj);
    }
    fighter->x2348_stateVar3_f32 -= 1.0f;
}