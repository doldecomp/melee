#include "ftpikachu.h"


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