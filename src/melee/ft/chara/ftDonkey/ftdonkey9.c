#include <melee/ft/chara/ftDonkey/ftdonkey.h>

void ftDonkey_800E0698(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

void ftDonkey_800E06B8(HSD_GObj* fighter_gobj) {
    ftDonkey_800DFA70(fighter_gobj);
}

void ftDonkey_800E06D8(HSD_GObj* fighter_gobj) {
    Vec vec;
    Fighter* fp = getFighter(fighter_gobj);
    if (ftDonkey_800E0750(fighter_gobj)) {
        ftDonkey_800E07B0(fighter_gobj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        func_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        func_8008E908(fighter_gobj, 0.0f);  
    }
}

BOOL ftDonkey_800E0750(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    
    if (func_8008E984(fp)) {
        return 1;
    }
    if (func_8008D8E8(scaleBy154_8008D8D8(fp->dmg.x1850_forceApplied)) < 3) {
        return 1;
    }
    return 0;
}

void ftDonkey_800E07B0(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    func_8008DCE0(fighter_gobj, donkey_attr->action_state + 9, 0.0f);
}
 
void ftDonkey_800E07E4(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_8008F744(fighter_gobj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->xE0_ground_or_air == GA_Air) {
            ftDonkey_800E0294(fighter_gobj);
        } else {
            ftDonkey_800DF980(fighter_gobj); 
        }
    }
}

void ftDonkey_800E0848(HSD_GObj* fighter_gobj) {
    func_8008FB18(fighter_gobj);
}

void ftDonkey_800E0868(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->xE0_ground_or_air == GA_Ground) {
        if (!func_80082708(fighter_gobj)) {
            func_8007D5D4(fp);
        }
    } else if (func_80081D0C(fighter_gobj)) {
        func_8007D7FC(fp);
    }
}
