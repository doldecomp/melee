#include "ftgamewatch.h"

void ftGameWatch_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0U, 0);
    func_80074A4C(fighterObj, 1U, -1);
    func_80074A4C(fighterObj, 2U, 0);
    func_80074A4C(fighterObj, 3U, 0);
    func_80074A4C(fighterObj, 4U, -1);
    func_80074A4C(fighterObj, 5U, -1);
    func_80074A4C(fighterObj, 6U, -1);
    func_80074A4C(fighterObj, 7U, -1);
    func_80074A4C(fighterObj, 8U, -1);
    func_80074A4C(fighterObj, 9U, -1);
    func_80074A4C(fighterObj, 0xAU, -1);
    fighter->sa.gaw.x222C = 1;
    fighter->sa.gaw.x2230 = 0;
    fighter->sa.gaw.x2234 = 0;
    fighter->sa.gaw.x223C = 0;
    fighter->sa.gaw.x2240 = 1;
    fighter->sa.gaw.x2244 = 3;
    fighter->sa.gaw.x2248 = 0;
    fighter->sa.gaw.x224C = 0;
    fighter->sa.gaw.x2250 = 0;
    fighter->sa.gaw.x2254 = 0;
    fighter->sa.gaw.x2258 = 0;
    fighter->sa.gaw.x225C = 0;
    fighter->sa.gaw.x2260 = 0;
    fighter->sa.gaw.x2264 = 0;
    fighter->sa.gaw.x2268 = 0;
    fighter->sa.gaw.x226C = 0;
}

void ftGameWatch_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** items = fighter->x10C_ftData->x48_items;

    fighter->x2222_flag.bits.b6 = 0;
    fighter->x2223_flag.bits.b1 = 1;
    fighter->x2224_flag.bits.b0 = 1;


    PUSH_ATTRS(fighter, ftGameWatchAttributes);
    fighter->sa.gaw.x2238 = 0;

    {
        
        ftGameWatchAttributes *attr = fighter->x2D4_specialAttributes;
        fighter->x34_scale.z = attr->x0;
        fighter->x614 = attr->x14;
        func_800BFB4C(fighterObj, &attr->x4[fighter->x619_costume_id]);
        fighter->x5C8 = items[10];
        
        func_8026B3F8(items[0], 0x72U);
        func_8026B3F8(items[1], 0x73U);
        func_8026B3F8(items[2], 0x74U);
        func_8026B3F8(items[3], 0x75U);
        func_8026B3F8(items[4], 0x76U);
        func_8026B3F8(items[5], 0x77U);
        func_8026B3F8(items[6], 0x78U);
        func_8026B3F8(items[7], 0x79U);
        func_8026B3F8(items[8], 0x7AU);
        func_8026B3F8(items[9], 0x7CU);
    }

}

void ftGameWatch_8014A4CC(HSD_GObj* fighterObj) {
    func_8014BF7C(fighterObj);
    func_8014ACB0(fighterObj);
    func_8014A938(fighterObj);
    func_8014B12C(fighterObj);
    func_8014B320(fighterObj);
    func_8014B514(fighterObj);
    func_8014C5CC(fighterObj);
    func_8014CCD8(fighterObj);
    func_8014DFFC(fighterObj);
}

void ftGameWatch_8014A538(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    if (fighter->xE0_ground_or_air == GA_Air) {
        func_8014BF7C(fighterObj);
        func_8014ACB0(fighterObj);
        func_8014A938(fighterObj);
        func_8014B12C(fighterObj);
        func_8014B320(fighterObj);
        func_8014B514(fighterObj);
        func_8014C5CC(fighterObj);
        func_8014CCD8(fighterObj);
        func_8014DFFC(fighterObj);
    }
}

void ftGameWatch_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftGameWatch_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

void ftGameWatch_OnItemVisible(HSD_GObj* gobj) {
    Fighter_OnItemVisible(gobj, 1);
}

void ftGameWatch_OnItemDrop(HSD_GObj* gobj, BOOL bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}
