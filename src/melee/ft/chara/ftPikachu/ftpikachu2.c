#include "ftpikachu.h"

void ftPikachu_SpecialN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighterObj);
}

void ftPikachu_ActionChange_8012489C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0, 0, 0.0f, 1.0f, 0.0f);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    func_8006EBA4(fighterObj);
}

void ftPikachu_80124908(HSD_GObj* fighterObj) {

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
            sp14.z = 0.0f;
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
    
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }    
}

void ftPikachu_80124A20(HSD_GObj* fighterObj) {
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
            sp14.z = 0.0f;
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
    
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        if (0.0f == pika_attr->x10) {
            func_800CC730(fighterObj);
            return;
        }
        func_80096900(fighterObj, 1, 0, 1, 1.0f, pika_attr->x10);
    }  
}

void ftPikachu_Stub_80124B6C() {}

void ftPikachu_Stub_80124B70() {}

void ftPikachu_80124B74(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_80124B94(HSD_GObj* fighterObj) {
    func_80084DB0(fighterObj);
}

void ftPikachu_ActionChange_80124BB4(HSD_GObj* fighterObj) {
    Fighter* fighter;
    if (!func_80082708(fighterObj)) {
        fighter = fighterObj->user_data;
        func_8007D5D4(fighter);
        Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0xc4c5082, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}


void ftPikachu_ActionChange_80124C20(HSD_GObj* fighterObj) {
    Fighter* fighter;
    if (func_80081D0C(fighterObj) == 1) {
        fighter = fighterObj->user_data;
        func_8007D7FC(fighter);
        fighter->x80_self_vel.y = 0.0f;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0xc4c5082, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
    }
}

void ftPikachu_EfSpawn_80124C90(HSD_GObj* fighterObj) {
    Fighter *fighter = fighterObj->user_data;
    
    HSD_GObj *tempObj;
    HSD_GObj *tempObj2;
    
    if (!fighter->x2219_flag.bits.b0)
    {
        s32 index = func_8007500C(fighter, 4);
        tempObj = fighterObj;
        ef_Spawn(0x4BE, tempObj2 = tempObj, fighter->x5E8_fighterBones[index].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }
    fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

void ftPikachu_EfSpawn_80124D2C(HSD_GObj* fighterObj) {
    Fighter *fighter = fighterObj->user_data;
    
    HSD_GObj *tempObj;
    HSD_GObj *tempObj2;
    
    if (!fighter->x2219_flag.bits.b0)
    {
        s32 index = func_8007500C(fighter, 4);
        tempObj = fighterObj;
        ef_Spawn(0x4BF, tempObj2 = tempObj, fighter->x5E8_fighterBones[index].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }
    fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

void ftPikachu_80124DC8(HSD_GObj* fighterObj) {
    u8 fighter_x673_byte;
    Fighter *fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    f32 pika_attr_1C;
    
    fighter->x2200_ftcmd_var0 = 0;
    fighter_x673_byte = fighter->x673;

    pika_attr_1C = pika_attr->x1C;
    if (fighter_x673_byte < pika_attr_1C) {
        fighter->x2340_stateVar1 = pika_attr->x20;
        fighter->x2072_b4 = 1;
    } else {
        fighter->x2340_stateVar1 = 0;
    }    
}
