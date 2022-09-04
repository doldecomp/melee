#include <melee/ft/chara/ftDonkey/ftdonkey.h>


s32 ftDonkey_800DFA98(HSD_GObj* fighter_gobj) {
    if (ftWalkCommon_800DFC70(fighter_gobj)) {
        ftDonkey_800DFAE4(fighter_gobj, 0.0f);
        return 1;
    }
    return 0;
}

void ftDonkey_800DFAE4(HSD_GObj* fighter_gobj, f32 argf) {
    Fighter* fp = getFighter(fighter_gobj);
    ftDonkeyAttributes* donkey_attr = getFtSpecialAttrs2CC(fp);
    ftWalkCommon_800DFCA4(
        fighter_gobj, donkey_attr->action_state + 1, 0, 
        argf, 
        donkey_attr->x8, donkey_attr->xC,  donkey_attr->x10, donkey_attr->x14, donkey_attr->x18, donkey_attr->x1C, 
        1.0f
    ); 
}

void ftDonkey_800DFB34(HSD_GObj* fighter_gobj) {
    ftWalkCommon_800DFDDC(fighter_gobj);
}

void ftDonkey_800DFB54(HSD_GObj* fighter_gobj) {
    if ((!func_80094EA4(fighter_gobj)) && (!ftDonkey_800E0378(fighter_gobj)) && (!ftDonkey_800DF938(fighter_gobj))) {
        ftWalkCommon_800DFEC8(fighter_gobj, &ftDonkey_800DFAE4);
    }
}


void ftDonkey_800DFBB8(HSD_GObj* fighter_gobj) {
    ftWalkCommon_800E0060(fighter_gobj);
}

void ftDonkey_800DFBD8(HSD_GObj* fighter_gobj) {
    ftDonkey_800DFA70(fighter_gobj);
}
