#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_800E01BC(HSD_GObj* fighter_gobj) {
    func_800C9924(fighter_gobj);
    if (!ftAnim_IsFramesRemaining(fighter_gobj)) {
        ftDonkey_800DF980(fighter_gobj);
    }
}

void ftDonkey_800E0200(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->x2340_stateVar1 && !func_80094EA4(fighter_gobj)) {
        s32 result = ftDonkey_800E0378(fighter_gobj);
        if (result) return;
    }
}

void ftDonkey_800E0254(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_800E0274(HSD_GObj* fighter_gobj) {
    ftDonkey_800DFA70(fighter_gobj);
}

void ftDonkey_800E0294(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, donkey_attr->action_state + 6, 1, NULL, 0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(fighter_gobj, 0.0f);
    if (fp->xE0_ground_or_air == GA_Ground) {
        func_8007D5D4(fp);
    }
}
