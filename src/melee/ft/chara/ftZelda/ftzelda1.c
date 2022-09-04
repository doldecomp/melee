#include <melee/ft/chara/ftZelda/ftzelda.h>

void ftZelda_OnDeath(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    func_80074A4C(fighter_gobj, 0, 0);
    func_80074A4C(fighter_gobj, 1, 0);
    fp->sa.zelda.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;
    
    PUSH_ATTRS(fp, ftZeldaAttributes);
    
    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* fighter_gobj) {
    ftZelda_8013B5EC(fighter_gobj);
}

void ftZelda_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftZelda_OnItemInvisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftZelda_OnItemVisible(HSD_GObj *fighter_gobj) {
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftZelda_OnItemDrop(HSD_GObj* fighter_gobj, BOOL bool1) {
    Fighter_OnItemDrop(fighter_gobj, bool1, 1, 1);
}

void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftZeldaAttributes);
}

void ftZelda_801395C8(HSD_GObj* fighter_gobj) { // Zelda_RemoveDress
    s32 unused[2];
    s32 result = func_80074A74(fighter_gobj, 1);
    if (result == -1) {
        func_80074A4C(fighter_gobj, 1, 0);
    } else {
        func_80074A4C(fighter_gobj, 1, -1);
    }
}

void ftZelda_OnKnockbackEnter(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackEnter(fighter_gobj, 1);
}

void ftZelda_OnKnockbackExit(HSD_GObj* fighter_gobj) {
    Fighter_OnKnockbackExit(fighter_gobj, 1);
}
