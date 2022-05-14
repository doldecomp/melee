#include "ftpikachu.h"


///////DELETE THIS SECTION WHEN FILE FINISHED//////////
extern f32 lbl_804D9928; //0.0f
extern f32 lbl_804D992C; //1.0f
inline f32 fabs_inline_delete(f32 x) {
    if (x < lbl_804D9928) {
        return -x;
    } else {
        return x;
    }
}
////////////////END SECTION///////////////////


void func_80125D80(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->xEC_ground_vel = fighter->x2C_facing_direction * fabs_inline(fighter->xEC_ground_vel);
    fighter->x80_self_vel.x = fighter->x2C_facing_direction * fabs_inline(fighter->x80_self_vel.x);
    fighter->x234C_pos.y = fighter->x2C_facing_direction * fabs_inline(fighter->x234C_pos.y);
}

void func_80125DE8(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = pika_attr->x5C;
    fighter->x2348_stateVar3 = 0;
    fighter->x2358_stateVar7_u32 = 0;
    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void func_80125E60(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = pika_attr->x5C;
    fighter->x2348_stateVar3 = 0;
    fighter->x2358_stateVar7_u32 = 0;
    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void func_80125ED8(HSD_GObj* fighterObj) {
    if (!func_8006F238(fighterObj)) {
        func_80126C0C(fighterObj);
    }
}

void func_80125F14(HSD_GObj* fighterObj) {
    if (!func_8006F238(fighterObj)) {
        func_80126E1C(fighterObj);
    }
}

void func_80125F50() {}

void func_80125F54() {}

void func_80125F58(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void func_80125F78(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_att = fighter->x2D4_specialAttributes;
    struct attr* attr = &fighter->x110_attr;
    if (fighter->x2340_stateVar1 != 0) {
        fighter->x2340_stateVar1++;
    } else {
        func_8007D494(fighter, pika_att->x64, attr->x170_TerminalVelocity);
    }
    func_8007CF58(fighter);
}

void func_80125FD8(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        func_80126084(fighterObj);
    }
} 

void func_80126014(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;

    if (func_800822A4(fighterObj, fighter->x2C_facing_direction < 0.0f ? -1 : 1)) {
        func_801260E4(fighterObj);
    } else  {
        if (func_80081298(fighterObj) == 0) { return; };
    }
}

void func_80126084(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0xC4C5084, 0, fighter->x894, 1.0f, 0.0f);
}