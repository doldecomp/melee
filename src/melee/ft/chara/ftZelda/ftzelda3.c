#include "ftzelda.h"

// 8013A830 - 8013A8AC (0x7C bytes)
// https://decomp.me/scratch/6v90P
void ftZelda_8013A830(HSD_GObj* fighterObj) {
    Fighter* fighter; // r31

    fighter = fighterObj->user_data;
    if (fighter->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F4, fighterObj, fighter->x5E8_fighterBones[1].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 8013A8AC - 8013A928 (0x7C bytes)
// https://decomp.me/scratch/rfSO5
void ftZelda_8013A8AC(HSD_GObj* fighterObj) {
    Fighter* fighter; // r31

    fighter = fighterObj->user_data;
    if (fighter->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4F5, fighterObj, fighter->x5E8_fighterBones[1].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 8013A928 - 8013A9A4 (0x7C bytes)
// https://decomp.me/scratch/arJgt
void ftZelda_SpecialN_StartAction(HSD_GObj* fighterObj) {
    f32 temp_f1;
    Fighter* fighter; // r31
    Fighter* fighter2; // r5
    ftZeldaAttributes* attributes;
    f32 unused[5];

    temp_f1 = 0;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0, NULL, temp_f1, 1.0, temp_f1);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

// 8013A9A4 - 8013AA38 (0x94 bytes)
// https://decomp.me/scratch/DgO7D
void ftZelda_SpecialAirN_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter; // r31
    Fighter* fighter2;
    ftZeldaAttributes* attributes;
    f32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x80_self_vel.y = 0;
    fighter->x80_self_vel.x = fighter->x80_self_vel.x / attributes->x8;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0, NULL, 0, 1.0, 0);
    func_8006EBA4(fighterObj);
    fighter2 = getFighter(fighterObj);
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

// 8013AA38 - 8013AACC (0x94 bytes)
// https://decomp.me/scratch/XcH4E
void ftZelda_8013AA38(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 attributes;
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = ((u32)fighter->x2D4_specialAttributes);
    
    if ((u32) fighter->x2200_ftcmd_var0 == 1) {
        fighter->x2200_ftcmd_var0 = 2;
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &ftZelda_8013ADB0);
    }
    if ((u32) fighter->x2200_ftcmd_var0 == 0) {
        fighter->x2218_flag.bits.b3 = 0;
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        func_8008A2BC(fighterObj);
    }
}

// 8013AACC - 8013AB60 (0x94 bytes)
// https://decomp.me/scratch/ttWvN
void ftZelda_8013AACC(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 attributes;
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = ((u32)fighter->x2D4_specialAttributes);
    
    if ((u32) fighter->x2200_ftcmd_var0 == 1U) {
        fighter->x2200_ftcmd_var0 = 2U;
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &ftZelda_8013ADB0);
    }
    if ((u32) fighter->x2200_ftcmd_var0 == 0U) {
        fighter->x2218_flag.bits.b3 = 0;
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        func_800CC730(fighterObj);
    }
}

void ftZelda_8013AB60(HSD_GObj* fighterObj) {}
void ftZelda_8013AB64(HSD_GObj* fighterObj) {}

// 8013AB68 - 8013AB9C (0x34 bytes)
void ftZelda_8013AB68(HSD_GObj* arg0) {
    func_80084F3C(arg0);
    func_8007AEF8(arg0);
}

// 8013AB9C - 8013AC10 (0x74 bytes)
// https://decomp.me/scratch/RUgWL
void ftZelda_8013AB9C(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* charAttr;
    s32 stateVar1;
    f32 arg2, arg3;
    attr* fighterAttr;
    s32 unused[2];

    fighter = fighterObj->user_data;
    charAttr = fighter->x2D4_specialAttributes;
    stateVar1 = fighter->x2340_stateVar1;
    fighterAttr = &fighter->x110_attr;
    
    if (stateVar1 != 0) {
        fighter->x2340_stateVar1 = stateVar1 - 1;
    } else {
        arg2 = charAttr->xC;
        arg3 = fighterAttr->x170_TerminalVelocity;
        func_8007D494(fighter, arg2, arg3) ;
    }
    func_8007CF58(fighter);
    func_8007AEF8(fighterObj);
}

// 8013AC10 - 8013AC4C (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC10(HSD_GObj* fighterObj) {
    if (func_80082708(fighterObj) == 0) {
        ftZelda_8013AC88(fighterObj);
    }
}

// 8013AC4C - 8013AC88 (0x3C bytes)
// https://decomp.me/scratch/CT7dz
void ftZelda_8013AC4C(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj) != 0) {
        ftZelda_8013AD1C(fighterObj);
    }
}

// 8013AC88 - 8013AD1C (0x94 bytes)
// https://decomp.me/scratch/B9loR
void ftZelda_8013AC88(HSD_GObj* fighterObj) {
    s32 attributes;
    Fighter* fighter;
    Fighter* fighter2;
    s32 unused[5];

    fighter = fighterObj->user_data;
    
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter2 = fighterObj->user_data;
    attributes = ((u32)fighter2->x2D4_specialAttributes);
    if ((u32) fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &ftZelda_8013ADB0);
    }
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013A8AC;
}

// 8013AD1C - 8013ADB0 (0x94 bytes)
// https://decomp.me/scratch/pQ6Xn
void ftZelda_8013AD1C(HSD_GObj* fighterObj) {
    s32 attributes;
    Fighter* fighter;
    Fighter* fighter2;
    s32 unused[5];

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter2 = fighterObj->user_data;
    attributes = ((u32)fighter2->x2D4_specialAttributes);
    if ((u32) fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &ftZelda_8013ADB0);
    }
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013A830;
}

void ftZelda_8013ADB0(HSD_GObj* fighterObj) {}
