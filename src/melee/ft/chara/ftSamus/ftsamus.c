#include "ftsamus.h"

void ftSamus_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    fighter->sa.samus.x222C = 0;
    fighter->sa.samus.x2230 = 0;
    fighter->sa.samus.x2238 = 0;
    fighter->sa.samus.x2244 = 0;
    fighter->sa.samus.x223C = 0;
    fighter->sa.samus.x2240 = 0;
}

void ftSamus_OnLoad(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    fighter->x2224_flag.bits.b7 = 1;

    PUSH_ATTRS(fighter, ftSamusAttributes);
    
    func_8026B3F8(item_list[0], 0x5DU);
    func_8026B3F8(item_list[1], 0x5EU);
    func_8026B3F8(item_list[2], 0x5FU);
    func_8026B3F8(item_list[3], 0x60U);
}

void ftSamus_80128428(HSD_GObj* fighterObj) {
    func_80129258(fighterObj);
    func_8012A640(fighterObj);
    func_800D9C98(fighterObj);
}

void ftSamus_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftSamus_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 0);
}

void ftSamus_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 0);
}

void ftSamus_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 0, 0);
}

void ftSamus_80128628(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftSamusAttributes* attr = fighter->x2D4_specialAttributes;
    f32 attr_value_x18 = attr->x18;
    if (fighter->sa.samus.x2230 == attr_value_x18) {
        func_800BFFD0(fighter, 0x35, 0);
    }
}

void ftSamus_LoadSpecialAttrs(HSD_GObj* fighterObj) {
    COPY_ATTRS(fighterObj, ftSamusAttributes);
    if (ft->x34_scale.y != 1.0f) {                                        
        sA2->x8 *= ft->x34_scale.y;                                       
        sA2->x78 *= ft->x34_scale.y;    
        sA2->x54 *= ft->x34_scale.y;                                                                              
        sA2->x58 *= ft->x34_scale.y;    
        SCALE_HEIGHT_ATTRS(6);                                                                   
    }  
}
