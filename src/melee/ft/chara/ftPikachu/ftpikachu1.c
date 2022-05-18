#include "ftpikachu.h"

void func_801243AC(Fighter* fighter) {
    ftPikachuAttributes* pika_attr = fighter->x2D8_specialAttributes2;
    ftPikachuAttributes* ext_attr = fighter->x10C_ftData->ext_attr;
    *pika_attr = *ext_attr;
    fighter->x2D4_specialAttributes = pika_attr;
}


void ftPikachu_OnLoad(HSD_GObj* fighterObj) {
  void **item_list;
  ftData *fighter_data;
  ftPikachuAttributes *ext_attr;
  ftPikachuAttributes *pika_attr_;

  s32 unused[2];

  ftPikachuAttributes *pika_attr;

  Fighter *fighter = fighterObj->user_data;
    
  fighter_data = fighter->x10C_ftData;
  pika_attr_ = fighter->x2D8_specialAttributes2;
    
  item_list = fighter_data->x48_items;
  ext_attr = fighter_data->ext_attr;

  *pika_attr_ = *ext_attr;

  fighter->x2D4_specialAttributes = pika_attr_;
  pika_attr = fighter->x2D4_specialAttributes;
    
  func_8026B3F8(item_list[0], pika_attr->xDC);
  func_8026B3F8(item_list[1], pika_attr->x14);
  func_8026B3F8(item_list[2], pika_attr->x18);

}

void ftPikachu_OnDeath(HSD_GObj* arg0, s32 arg1, s32 arg2) {
    func_80074A4C(arg0, 0, 0);
    func_80074A4C(arg0, 1, 0);
}

void func_801244B8(HSD_GObj* fighterObj, s32 arg1) {
    s32 temp_r3;
    s32 unused;
    Fighter *fighter;

    fighter = fighterObj->user_data;
    if (func_8026B2B4(fighter->x1974_heldItem) == 0) {
        temp_r3 = func_8026B320(fighter->x1974_heldItem);

        switch (temp_r3) {
 
            case 1:
                func_80070FB4(fighterObj, 0, 1);
                break;
            case 2:
                func_80070FB4(fighterObj, 0, 0);
                break;
            case 3:
                func_80070FB4(fighterObj, 0, 2);
                break;
            case 4:
                func_80070FB4(fighterObj, 0, 3);
                break;
                
        }
        
        if (arg1 != 0) {
            func_80070C48(fighterObj, 0);
        }
    }
}

void func_80124598(HSD_GObj *fighterObj, s32 arg1) {
    Fighter* fighter = fighterObj->user_data;
    if (func_8026B2B4(fighter->x1974_heldItem) == 0) {
        func_80070CC4(fighterObj, 0);
    }
}

void func_801245E0(HSD_GObj *fighterObj, s32 arg1) {
    Fighter* fighter = fighterObj->user_data;
    if (func_8026B2B4(fighter->x1974_heldItem) == 0) {
        func_80070C48(fighterObj, 0);
    }
}

void func_80124628(HSD_GObj* gobj, s32 arg1) {
    func_80070FB4(gobj, 0, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 0);
    }
}

void func_8012467C(HSD_GObj* arg0, s32 arg1, s32 arg2) {
    func_80074A4C(arg0, 1, -1);
    func_80074B0C(arg0, 1, 0);
}

void func_801246C0(HSD_GObj* arg0, s32 arg1, s32 arg2) {
    func_80074A4C(arg0, 1, 0);
    func_80074B0C(arg0, 1, 0);
}


void func_80124704(HSD_GObj* fighterObj) {

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

void func_801247A8(HSD_GObj* arg0) {
    func_800704F0(arg0, 1, 3.0f);
    func_800704F0(arg0, 0, 3.0f);
}


void func_801247EC(HSD_GObj* arg0) {
    func_800704F0(arg0, 1, 0.0f);
    func_800704F0(arg0, 0, 0.0f);
}