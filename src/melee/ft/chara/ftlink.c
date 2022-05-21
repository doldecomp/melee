#include "ftlink.h"

s32 func_800EAD64(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->sa.link.x2234) {
        return 1;
    }
    return 0;
}

void ftLink_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    func_80074A4C(fighterObj, 2, 0);
    fighter->sa.link.x222C = 0;
    fighter->sa.link.x2234 = 0;
    fighter->sa.link.x2238 = 0;
    fighter->sa.link.x223C = 0;
    fighter->sa.link.x2240 = 0;
    fighter->sa.link.x2238 = 0;
    fighter->sa.link.x2244 = 0;
}

void ftLink_OnLoadForCLink(Fighter* fighter) {
    PUSH_ATTRS(fighter, ftLinkAttributes);
}

void ftLink_OnLoad(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    ftLinkAttributes* link_attr = fighter->x10C_ftData->ext_attr;
    void** item_list = fighter->x10C_ftData->x48_items;
    link_attr->x54 = func_8001E8F8(func_80085E50(fighter, 0x48U));
    PUSH_ATTRS(fighter, ftLinkAttributes);

    link_attr = fighter->x2D4_specialAttributes;
    func_8026B3F8(item_list[0], link_attr->x48);
    func_8026B3F8(item_list[1], link_attr->x2C);
    func_8026B3F8(item_list[2], link_attr->xBC);
    func_8026B3F8(item_list[3], link_attr->xC);
    func_8026B3F8(item_list[4], link_attr->x10);
    func_800753D4(fighter, *lbl_804D6540[fighter->x4_fighterKind], item_list[6]);
 
}