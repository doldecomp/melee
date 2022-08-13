#include <ftdonkey.h>

void ftDonkey_800E01BC(HSD_GObj* fighterObj) {
    func_800C9924(fighterObj);
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftDonkey_800DF980(fighterObj);
    }
}

void ftDonkey_800E0200(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    if (fp->x2340_stateVar1 && !func_80094EA4(fighterObj)) {
        s32 result = ftDonkey_800E0378(fighterObj);
        if (result) return;
    }
}

void ftDonkey_800E0254(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_800E0274(HSD_GObj* fighterObj) {
    ftDonkey_800DFA70(fighterObj);
}

void ftDonkey_800E0294(HSD_GObj* fighterObj) {
    Fighter* fp = getFighterPlus(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighterObj, donkey_attr->action_state + 6, 1, NULL, 0.0f, 1.0, 0.0f);
    ftAnim_SetAnimRate(fighterObj, 0.0f);
    if (fp->xE0_ground_or_air == GA_Ground) {
        func_8007D5D4(fp);
    }
}