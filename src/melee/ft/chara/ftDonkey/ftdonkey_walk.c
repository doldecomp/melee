#include <ftdonkey.h>


s32 ftDonkey_800DFA98(HSD_GObj* fighterObj) {
    if (ftWalkCommon_800DFC70(fighterObj)) {
        ftDonkey_800DFAE4(fighterObj, 0.0f);
        return 1;
    }
    return 0;
}

void ftDonkey_800DFAE4(HSD_GObj* fighterObj, f32 argf) {
    Fighter* fp = getFighter(fighterObj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftWalkCommon_800DFCA4(
        fighterObj, donkey_attr->action_state + 1, 0, 
        argf, 
        donkey_attr->x8, donkey_attr->xC,  donkey_attr->x10, donkey_attr->x14, donkey_attr->x18, donkey_attr->x1C, 
        1.0f
    ); 
}

void ftDonkey_800DFB34(HSD_GObj* fighterObj) {
    ftWalkCommon_800DFDDC(fighterObj);
}

void ftDonkey_800DFB54(HSD_GObj* fighterObj) {
    if ((!func_80094EA4(fighterObj)) && (!ftDonkey_800E0378(fighterObj)) && (!ftDonkey_800DF938(fighterObj))) {
        ftWalkCommon_800DFEC8(fighterObj, &ftDonkey_800DFAE4);
    }
}


void ftDonkey_800DFBB8(HSD_GObj* fighterObj) {
    ftWalkCommon_800E0060(fighterObj);
}

void ftDonkey_800DFBD8(HSD_GObj* fighterObj) {
    ftDonkey_800DFA70(fighterObj);
}
