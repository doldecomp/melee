#include "ftpikachu.h"

void ftPikachu_OnLoadForPichu(Fighter* fighter) {
    PUSH_ATTRS(fighter, ftPikachuAttributes);
}


void ftPikachu_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;

    PUSH_ATTRS(fighter, ftPikachuAttributes);

    {
        ftPikachuAttributes *pika_attr = fighter->x2D4_specialAttributes;
        func_8026B3F8(item_list[0], pika_attr->xDC);
        func_8026B3F8(item_list[1], pika_attr->x14);
        func_8026B3F8(item_list[2], pika_attr->x18);
    }

}

void ftPikachu_OnDeath(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
}

void ftPikachu_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 0, 0);
}

void ftPikachu_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!func_8026B2B4(fighter->x1974_heldItem)) {
        func_80070CC4(fighterObj, 0);
    }
}

void ftPikachu_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (!func_8026B2B4(fighter->x1974_heldItem)) {
        func_80070C48(fighterObj, 0);
    }
}

void ftPikachu_OnItemRelease(HSD_GObj* fighterObj, s32 arg1) {
    func_80070FB4(fighterObj, 0, -1);
    if (arg1) {
        func_80070CC4(fighterObj, 0);
    }
}

void ftPikachu_8012467C(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 1, -1);
    func_80074B0C(fighterObj, 1, 0);
}

void ftPikachu_801246C0(HSD_GObj* fighterObj) {
    s32 unused[2];
    func_80074A4C(fighterObj, 1, 0);
    func_80074B0C(fighterObj, 1, 0);
}


void ftPikachu_ScaleYAttributesArray_80124704(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    ftData *fighter_data = fighter->x10C_ftData;
    
    ftPikachuAttributes *pika_attr = fighter->x2D4_specialAttributes;
    ftPikachuAttributes *other_attr = fighter_data->ext_attr;

    *pika_attr = *other_attr;

    if (1.0f != fighter->x34_scale.y) {
        pika_attr->xE0_array_start *= fighter->x34_scale.y;
        pika_attr->xE4 *= fighter->x34_scale.y;
        pika_attr->xE8 *= fighter->x34_scale.y;
        pika_attr->xEC *= fighter->x34_scale.y;
        pika_attr->xF0 *= fighter->x34_scale.y;
        pika_attr->xF4 *= fighter->x34_scale.y;
    }
    
}

void ftPikachu_801247A8(HSD_GObj* fighterObj) {
    func_800704F0(fighterObj, 1, 3.0f);
    func_800704F0(fighterObj, 0, 3.0f);
}


void ftPikachu_801247EC(HSD_GObj* fighterObj) {
    func_800704F0(fighterObj, 1, 0.0f);
    func_800704F0(fighterObj, 0, 0.0f);
}