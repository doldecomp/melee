#include <ftdonkey.h>

void ftDonkey_800E0698(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftDonkey_800E06B8(HSD_GObj* fighterObj) {
    ftDonkey_800DFA70(fighterObj);
}

void ftDonkey_800E06D8(HSD_GObj* fighterObj) {
    Vec vec;
    Fighter* fp = getFighter(fighterObj);
    if (ftDonkey_800E0750(fighterObj)) {
        ftDonkey_800E07B0(fighterObj);
    } else {
        vec.x = vec.y = vec.z = 0.0f;
        func_8026ABD8(fp->x1974_heldItem, &vec, 1.0f);
        func_8008E908(fighterObj, 0.0f);  
    }
}

BOOL ftDonkey_800E0750(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    
    if (func_8008E984(fp)) {
        return 1;
    }
    if (func_8008D8E8(scaleBy154_8008D8D8(fp->dmg.x1850_forceApplied)) < 3) {
        return 1;
    }
    return 0;
}

void ftDonkey_800E07B0(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    ftDonkeyAttributes* donkey_attr = fp->x2CC;
    func_8008DCE0(fighterObj, donkey_attr->action_state + 9, 0.0f);
}
 
void ftDonkey_800E07E4(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    func_8008F744(fighterObj);
    if (!fp->x221C_flag.bits.b6) {
        if (fp->xE0_ground_or_air == GA_Air) {
            ftDonkey_800E0294(fighterObj);
        } else {
            ftDonkey_800DF980(fighterObj); 
        }
    }
}

void ftDonkey_800E0848(HSD_GObj* fighterObj) {
    func_8008FB18(fighterObj);
}

void ftDonkey_800E0868(HSD_GObj* fighterObj) {
    Fighter* fp = getFighter(fighterObj);
    if (fp->xE0_ground_or_air == GA_Ground) {
        if (!func_80082708(fighterObj)) {
            func_8007D5D4(fp);
        }
    } else if (func_80081D0C(fighterObj)) {
        func_8007D7FC(fp);
    }
}