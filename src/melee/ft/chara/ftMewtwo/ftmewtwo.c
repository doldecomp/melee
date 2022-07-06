#include "ftmewtwo.h"

void ftMewtwo_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = (Fighter*)gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.mewtwo.x222C = 0;
    ft->sa.mewtwo.x2230 = 0;
    ft->sa.mewtwo.x2234 = 0;
    ft->sa.mewtwo.x2238 = 0;
    ft->sa.mewtwo.x223C = 0;
}

void ftMewtwo_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    ftMewTwoAttributes* attr = fighter->x10C_ftData->ext_attr;
    void** item_list = fighter->x10C_ftData->x48_items;
    PUSH_ATTRS(fighter, ftMewTwoAttributes);

    {
        fighter->x5E8_fighterBones[1].flags.bits.b4 = 1;
        fighter->x2221_flag.bits.b2 = 1;
    }
    func_8026B3F8(item_list[0], 0x6E);
    func_8026B3F8(item_list[1], 0x70);
}

void ftMewTwo_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewTwo_80144EE4(HSD_GObj* fighterObj) {
    func_801461A8(fighterObj);
    func_80146E30(fighterObj);
}

void ftMewTwo_80144F18(HSD_GObj* fighterObj) {
    func_801461A8(fighterObj);
    func_80146ED0(fighterObj);
}

void ftMewTwo_OnItemDrop(HSD_GObj* fighterObj, BOOL bool) {}

void ftMewTwo_OnItemInvisible(HSD_GObj* fighterObj) {}

void ftMewTwo_OnItemVisible(HSD_GObj* fighterObj) {}
