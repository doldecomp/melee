#include "ftpikachu.h"

void func_801243AC(Fighter* fighter) {
    ftPikachuAttributes* pika_attr = (ftPikachuAttributes*) fighter->x2D8_specialAttributes2;
    ftPikachuAttributes* ext_attr = (ftPikachuAttributes*) fighter->x10C_ftData->ext_attr;
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


extern f32 lbl_804D98F0;  /// DELETE ME - once file is matched

void func_80124704(HSD_GObj* fighterObj) {

    Fighter* fighter = fighterObj->user_data;
    ftData *fighter_data = fighter->x10C_ftData;
    
    ftPikachuAttributes *pika_attr = fighter->x2D4_specialAttributes;
    ftPikachuAttributes *other_attr = fighter_data->ext_attr;

    *pika_attr = *other_attr;

    if (lbl_804D98F0 != fighter->x34_scale.y) {
        pika_attr->xE0 *= fighter->x34_scale.y;
        pika_attr->xE4 *= fighter->x34_scale.y;
        pika_attr->xE8 *= fighter->x34_scale.y;
        pika_attr->xEC *= fighter->x34_scale.y;
        pika_attr->xF0 *= fighter->x34_scale.y;
        pika_attr->xF4 *= fighter->x34_scale.y;
    }
    
}


extern f32 lbl_804D98F4; /// DELETE ME - once file is matched

void func_801247A8(HSD_GObj* arg0) {
    func_800704F0(arg0, 1, lbl_804D98F4);
    func_800704F0(arg0, 0.0f, lbl_804D98F4);
}


extern f32 lbl_804D98F8; /// DELETE ME - once file is matched

void func_801247EC(HSD_GObj* arg0) {
    func_800704F0(arg0, 1, lbl_804D98F8);
    func_800704F0(arg0, 0, lbl_804D98F8);
}


extern f32 lbl_804D9900;
extern f32 lbl_804D9904;

void func_80124830(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0, 0, lbl_804D9900, lbl_804D9904, lbl_804D9900);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighterObj);
}

void func_8012489C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0, 0, lbl_804D9900, lbl_804D9904, lbl_804D9900);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighterObj);
}

void func_80124908(HSD_GObj* fighterObj) {

    Vec sp14;
    s32 stack_buffer[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (fighter->x2200_ftcmd_var0 == 1) {
        fighter->x2200_ftcmd_var0 = 0;

        if (!fighter->x2204_ftcmd_var1) {
            fighter->x2204_ftcmd_var1 = 1;
            sp14.x = (fighter->x34_scale.y * (pika_attr->x0 * fighter->x2C_facing_direction)) + fighter->xB0_pos.x;
            sp14.y = (pika_attr->x4 * fighter->x34_scale.y) + fighter->xB0_pos.y;
            sp14.z = lbl_804D9900;
            func_802B338C(fighterObj, &sp14, fighter->x2C_facing_direction, pika_attr->x14);
            switch (func_800872A4(fighterObj)) {
                case 12:
                    func_80088148(fighter, 0x3a9cc, 0x7F, 0x40);
                    break;
                case 23:
                    func_80088148(fighter, 0x382b3, 0x7F, 0x40);
                    break;
            }
        }
    }
    
    if (!func_8006F238(fighterObj)) {
        func_8008A2BC(fighterObj);
    }    
}

void func_80124A20(HSD_GObj* fighterObj) {
    Vec sp14;
    s32 stack_buffer[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (fighter->x2200_ftcmd_var0 == 1) {
        fighter->x2200_ftcmd_var0 = 0;

        if (!fighter->x2204_ftcmd_var1) {
            fighter->x2204_ftcmd_var1 = 1;
            sp14.x = (fighter->x34_scale.y * (pika_attr->x8 * fighter->x2C_facing_direction)) + fighter->xB0_pos.x;
            sp14.y = (pika_attr->xC * fighter->x34_scale.y) + fighter->xB0_pos.y;
            sp14.z = lbl_804D9900;
            func_802B338C(fighterObj, &sp14, fighter->x2C_facing_direction, pika_attr->x14);
            switch (func_800872A4(fighterObj)) {
                case 12:
                    func_80088148(fighter, 0x3a9cc, 0x7F, 0x40);
                    break;
                case 23:
                    func_80088148(fighter, 0x382b3, 0x7F, 0x40);
                    break;
            }
        }
    }
    
    if (func_8006F238(fighterObj) == 0) {
        if (lbl_804D9900 == pika_attr->x10) {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 0, 1, lbl_804D9904, pika_attr->x10);
    }  
}

void func_80124B6C() {}

void func_80124B70() {}

void func_80124B74(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

void func_80124B94(HSD_GObj* arg0) {
    func_80084DB0(arg0);
}

void func_80124BB4(HSD_GObj* fighterObj) {
    Fighter* fighter;
    if (!func_80082708(fighterObj)) {
        fighter = fighterObj->user_data;
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0xc4c5082, 0, fighter->x894, lbl_804D9904, lbl_804D9900);
    }
}


/// matches when data is moved over
// void func_80124C20(HSD_GObj* fighterObj) {
//     Fighter* fighter;
//     if (func_80081D0C(fighterObj) == 1) {
//         fighter = fighterObj->user_data;
//         func_8007D7FC(fighter);
//         fighter->x80_self_vel.y = 0.0f/*lbl_804D9900*/;
//         Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0xc4c5082, 0, fighter->x894, 1.0f/*lbl_804D9904*/, 0.0f/*lbl_804D9900*/);
//     }
// }

/////  Match from samer
// void func_8012764C(HSD_GObj* fighterObj) {
//     Fighter* fighter = fighterObj->user_data;
//     fighter->x2344_stateVar2 = 3;
// }