#include "ftpikachu.h"


extern f32 lbl_804D9910;  /// DELETE ME - remove once the whole file is finished and data is moved over
extern f32 lbl_804D9914;  /// DELETE ME - remove once the whole file is finished and data is moved over

void func_80124E38(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->cb.x21EC_callback = func_80124DC8;

    fighter->xEC_ground_vel /= pika_attr->x30;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void func_80124EAC(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    fighter->cb.x21EC_callback = func_80124DC8;

    fighter->x80_self_vel.x /= pika_attr->x30;
    fighter->x80_self_vel.y = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void func_80124F24(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->x80_self_vel.x = 0.0f;
    if (fighter->x80_self_vel.y >= 0.0f) {
        fighter->x80_self_vel.y = 0.0f;
    }
    func_80125D28_file_end(fighterObj);
}

void func_80124F64(HSD_GObj* fighterObj) {
    if (!func_8006F238(fighterObj)) {
        func_801254D4(fighterObj);
    }
}

void func_80124FA0(HSD_GObj* fighterObj) {
    if (!func_8006F238(fighterObj)) {
        func_80125528(fighterObj);
    }
}

void func_80124FDC() {}

void func_80124FE0() {}

void func_80124FE4(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    f32 pika_attr_x34 = pika_attr->x34;
    func_8007C930(fighter, pika_attr_x34);
    func_8007CB74(fighterObj);
}

void func_80125024(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    struct attr* attr = &fighter->x110_attr;
    
    if (fighter->x2200_ftcmd_var0) {
        func_8007D494(fighter, pika_attr->x38, attr->x170_TerminalVelocity);
    }
    func_8007CE94(fighter, pika_attr->x34);
}

void func_80125084(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_801250FC(fighterObj);
    }
}

void func_801250C0(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj)) {
        func_8012515C(fighterObj);
    }
}

void func_801250FC(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0xc4c5284, 0, fighter->x894, 1.0f, 0.0f);
}

void func_8012515C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0xc4c5284, 0, fighter->x894, 1.0f, 0.0f);
}

void func_801251BC(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (!func_8006F238(fighterObj)) {
        func_8007DB24(fighterObj);
        fighter->cb.x21BC_callback_Accessory4 = &func_80124C90;
    }
    fighter->x2340_stateVar1++;
    if (fighter->x2340_stateVar1 > pika_attr->x24) {
        func_80125834(fighterObj);
    }
}

/////  Match from samer
// void func_8012764C(HSD_GObj* fighterObj) {
//     Fighter* fighter = fighterObj->user_data;
//     fighter->x2344_stateVar2 = 3;
// }