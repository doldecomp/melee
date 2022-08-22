#include <ftseak.h>

void ftSeak_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    fp->sa.seak.x222C = 0;
    fp->sa.seak.x2230 = 0;
    fp->sa.seak.x2234 = 0;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, -1);
}

void ftSeak_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;
    
    PUSH_ATTRS(fp, ftSeakAttributes);
    
    func_8026B3F8(item_list[0], 0x4FU);
    func_8026B3F8(item_list[1], 0x50U);
    func_8026B3F8(item_list[2], 0x55U);
    func_8026B3F8(item_list[3], 0x61U);
}

void ftSeak_80110198(HSD_GObj* fighterObj) {
    func_80111FBC(fighterObj);
    func_80110E88(fighterObj);
}

void ftSeak_801101CC(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    if (fp->sa.seak.x222C == 6) {
        func_800BFFD0(fp, 0x56, 0);
    }
}

void ftSeak_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftSeak_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftSeak_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftSeak_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftSeak_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftSeakAttributes);
} 

void ftSeak_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftSeak_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}


// 8011412C - 80114160
// https://decomp.me/scratch/b1oIZ
// void lbl_8011412C(HSD_GObj* fighterObj) {
//     Fighter* fp = fighterObj->user_data;
//     fp->cb.x21BC_callback_Accessory4 = 0;
//     func_8007EFC8(fighterObj, &ftZelda_8013B4D8);
// }