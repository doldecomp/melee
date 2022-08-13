#include <ftdonkey.h>

s32 ftDonkey_800DF938(HSD_GObj* fighterObj) {
    if (func_8008A1FC(fighterObj)) {
        ftDonkey_800DF980(fighterObj);
        return 1;
    }
    return 0;
}

void ftDonkey_800DF980(HSD_GObj* fighterObj) {
    s32 unused[2]; /// getFighter inlines not working
    Fighter* fp = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr;
    if (fp->xE0_ground_or_air == GA_Air) {
        func_8007D7FC(fp);
    }
    donkey_attr = getFtSpecialAttrs2CC(fp);
    Fighter_ActionStateChange_800693AC(fighterObj, donkey_attr->action_state, 0, NULL, 0.0f, 1.0f, 0.0f);
}

void ftDonkey_800DF9F0(HSD_GObj* fighterObj) {
    if ((!func_80094EA4(fighterObj)) && (!ftDonkey_800E0378(fighterObj)) && (!ftDonkey_800E0134(fighterObj))) {
        s32 result = ftDonkey_800DFA98(fighterObj);
        if (result) { return;  }
    }
}

void ftDonkey_800DFA50(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_800DFA70(HSD_GObj* fighterObj) {
    func_8008403C(fighterObj, &ftDonkey_800E0294);
}
