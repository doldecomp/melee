#include <ftzelda.h>

void ftZelda_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    fp->sa.zelda.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fp = fighterObj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;
    
    PUSH_ATTRS(fp, ftZeldaAttributes);
    
    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* fighterObj) {
    ftZelda_8013B5EC(fighterObj);
}

void ftZelda_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftZelda_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftZelda_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftZelda_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftZeldaAttributes);
}

void ftZelda_801395C8(HSD_GObj* fighterObj) { // Zelda_RemoveDress
    s32 unused[2];
    s32 result = func_80074A74(fighterObj, 1);
    if (result == -1) {
        func_80074A4C(fighterObj, 1, 0);
    } else {
        func_80074A4C(fighterObj, 1, -1);
    }
}

void ftZelda_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftZelda_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}
