#include <melee/ft/chara/ftSeak/ftseak.h>

void ftSeak_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    fp->sa.seak.x222C = 0;
    fp->sa.seak.x2230 = 0;
    fp->sa.seak.x2234 = 0;
    func_80074A4C(fighter_gobj, 0, 0);
    func_80074A4C(fighter_gobj, 1, -1);
}

void ftSeak_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;

    fp->x2224_flag.bits.b7 = 1;
    
    PUSH_ATTRS(fp, ftSeakAttributes);
    
    func_8026B3F8(item_list[0], 0x4FU);
    func_8026B3F8(item_list[1], 0x50U);
    func_8026B3F8(item_list[2], 0x55U);
    func_8026B3F8(item_list[3], 0x61U);
}

void ftSeak_80110198(HSD_GObj* fighter_gobj) {
    func_80111FBC(fighter_gobj);
    func_80110E88(fighter_gobj);
}

void ftSeak_801101CC(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if (fp->sa.seak.x222C == 6) {
        func_800BFFD0(fp, 0x56, 0);
    }
}

void ftSeak_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftSeak_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftSeak_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftSeak_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftSeak_LoadSpecialAttrs(HSD_GObj* fighter_gobj) {
    COPY_ATTRS(fighter_gobj, ftSeakAttributes);
} 

void ftSeak_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftSeak_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}


// 8011412C - 80114160
// https://decomp.me/scratch/b1oIZ
// void lbl_8011412C(HSD_GObj* fighter_gobj) {
//     Fighter* fp = fighter_gobj->user_data;
//     fp->cb.x21BC_callback_Accessory4 = 0;
//     func_8007EFC8(fighter_gobj, &ftZelda_8013B4D8);
// }
