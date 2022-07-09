#include "ftlink.h"

extern float lbl_804D92D8; // 1.0f
extern float lbl_804D92DC; // 3.0f
extern float lbl_804D92E0; // 0.0f

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

void func_800EAF38() {
    func_800EC06C();
}

void func_800EAF58(HSD_GObj* fighterObj) {
    func_800EC06C();
    func_800D94D8(fighterObj);
    func_800ECD04(fighterObj);
    func_800ECD58(fighterObj);
    func_80149268(fighterObj);
}

void ftLink_OnItemPickupExt(HSD_GObj* fighterObj, int arg1) {
    Fighter* link = getFighter(fighterObj);
    if (func_8026B2B4(link->x1974_heldItem) == 1) {
        func_80074A4C(fighterObj, 1, 1);
    }
    func_80074A4C(fighterObj, 2, 1);
    ftLink_OnItemPickup(fighterObj, arg1);
}

void ftLink_OnItemInvisible(HSD_GObj* fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftLink_OnItemVisible(HSD_GObj* fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftLink_OnItemDropExt(HSD_GObj* fighterObj, BOOL arg1) {
    Fighter* link = getFighter(fighterObj);
    if (func_8026B2B4(link->x1974_heldItem) == 1) {
        func_80074A4C(fighterObj, 1, 0);
    }
    func_80074A4C(fighterObj, 2, 0);
    ftLink_OnItemDrop(fighterObj, arg1);
}
 

void ftLink_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftLink_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter* link = getFighter(gobj);
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void func_800EB250(HSD_GObj* fighterObj) {
    Fighter* link = fighterObj->user_data;
    ftLinkAttributes* link_attr = link->x2D4_specialAttributes;
    ftLinkAttributes* other_attr = link->x10C_ftData->ext_attr;
    *link_attr = *other_attr;
    if (lbl_804D92D8 != link->x34_scale.y) {
        link_attr->x28 *= link->x34_scale.y;
    }
}

void ftLink_OnKnockbackEnter(HSD_GObj* fighterObj) {
    func_800704F0(fighterObj, 1, lbl_804D92DC);
    func_800704F0(fighterObj, 0, lbl_804D92DC);
}

void ftLink_OnKnockbackExit(HSD_GObj* fighterObj) {
    func_800704F0(fighterObj, 1, lbl_804D92E0);
    func_800704F0(fighterObj, 0, lbl_804D92E0);
}
