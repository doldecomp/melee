#include "ftzelda.h"

// 8013ADB4 - 8013AE30 (0x7C bytes)
// https://decomp.me/scratch/LbMVE
void ftZelda_8013ADB4(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if ((u8) fighter->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4FC, fighterObj, fighter->x5E8_fighterBones[0x68].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }

    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 8013AE30 - 8013AEAC (0x7C bytes)
// https://decomp.me/scratch/iojLO
void ftZelda_8013AE30(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if ((u8) fighter->x2219_flag.bits.b0 == 0) {
        ef_Spawn(0x4FD, fighterObj, fighter->x5E8_fighterBones[4].x0_jobj);
        fighter->x2219_flag.bits.b0 = 1;
    }

    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// Zelda_TransformToSubcharacter
// 8013AEAC - 8013AEE0 (0x34 bytes)
// https://decomp.me/scratch/iINH1
void func_80114758(HSD_GObj*);                      /* extern */
void ftZelda_8013AEAC(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    fighter->cb.x21BC_callback_Accessory4 = 0;

    func_8007EFC8(fighterObj, func_80114758);
}

// Helper function for both ftZelda_SpecialLw_StartAction / ftZelda_SpecialAirLw_StartAction
void ftZelda_SpecialLw_StartAction_Helper(HSD_GObj* fighterObj) {
    Point3d sp20;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r3
    
    fighter = getFighterPlus(fighterObj);
    attributes = getFtSpecialAttrs(fighter);
    
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.x = (f32) (fighter->x80_self_vel.x / attributes->x70);
    fighter->x80_self_vel.y = (f32) (fighter->x80_self_vel.y / attributes->x74);
    fighter->xEC_ground_vel = (f32) (fighter->xEC_ground_vel / attributes->x70);
    
    func_8000B1CC(fighter->x5E8_fighterBones[0].x0_jobj, NULL, &sp20);
    func_800119DC(&sp20, 0x78, 0.4000000059604645, 0.003000000026077032, 1.0471975803375244);
    
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013ADB4;
}

// Zelda_AS_355_Transform_Grounded
// 8013AEE0 - 8013AFA4 (0xC4 bytes)
// https://decomp.me/scratch/jZJgg (with helper)
// https://decomp.me/scratch/Lw6fO (single function)
void ftZelda_SpecialLw_StartAction(HSD_GObj* fighterObj) {
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0, NULL, 0.0f, 1.0, 0.0f);
    
    func_8006EBA4(fighterObj);
    
    ftZelda_SpecialLw_StartAction_Helper(fighterObj);
}

// Zelda_AS_357_Transform_Aerial
// 8013AFA4 - 8013B068 (0xC4 bytes)
// For a scratch using helper function, see the above function.
// https://decomp.me/scratch/8W7ZF (single function)
void ftZelda_SpecialAirLw_StartAction(HSD_GObj* fighterObj) {
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0, NULL, 0.0f, 1.0, 0.0f);
    
    func_8006EBA4(fighterObj);
    
    ftZelda_SpecialLw_StartAction_Helper(fighterObj);
}

// 8013B068 - 8013B0A8 (0x40 bytes)
// https://decomp.me/scratch/DrRr5
void ftZelda_8013B068(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013AEAC;
    }
}

// 8013B0A8 - 8013B0E8 (0x40 bytes)
// https://decomp.me/scratch/DrRr5
void ftZelda_8013B0A8(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013AEAC;
    }
}

void ftZelda_8013B0E8(HSD_GObj* fighterObj) {return;}
void ftZelda_8013B0EC(HSD_GObj* fighterObj) {return;}

// 8013B0F0 - 8013B110 (0x20 bytes)
void ftZelda_8013B0F0(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

// 8013B110 - 8013B154 (0x44 bytes)
// https://decomp.me/scratch/Nm958
void ftZelda_8013B110(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* attributes;
    f32 unused[3];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;

    func_8007D494(fighter, attributes->x78, attributes->x7C);
    func_8007CEF4(fighter);
}

// 8013B154 - 8013B190 (0x3C bytes)
// https://decomp.me/scratch/8ceOO
void ftZelda_8013B154(HSD_GObj* fighterObj) {
    if (func_80082708(fighterObj) == 0) {
        ftZelda_8013B1CC(fighterObj);
    }
}

// 8013B190 - 8013B1CC (0x3C bytes)
// https://decomp.me/scratch/8ceOO
void ftZelda_8013B190(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj) != 0) {
        ftZelda_8013B238(fighterObj);
    }
}

// 8013B1CC - 8013B238 (0x6C bytes)
// https://decomp.me/scratch/w04qW
void ftZelda_8013B1CC(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013ADB4;
}

// 8013B238 - 8013B2A4 (0x6C bytes)
void ftZelda_8013B238(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013ADB4;
}

// 8013B2A4 - 8013B2E0 (0x3C bytes)
void ftZelda_8013B2A4(HSD_GObj* fighterObj) {
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        func_8008A2BC(fighterObj);
    }
}

// 8013B2E0 - 8013B31C (0x3C bytes)
void ftZelda_8013B2E0(HSD_GObj* fighterObj) {
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        func_800CC730(fighterObj);
    }
}

void ftZelda_8013B31C(HSD_GObj* fighterObj) {return;}
void ftZelda_8013B320(HSD_GObj* fighterObj) {return;}

// 8013B324 - 8013B344 (0x20 bytes)
void ftZelda_8013B324(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

// 8013B344 - 8013B388 (0x44 bytes)
// https://decomp.me/scratch/r3T6y
void ftZelda_8013B344(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* attributes;
    f32 unused[3];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;

    func_8007D494(fighter, attributes->x78, attributes->x7C);
    func_8007CEF4(fighter);
}

// 8013B388 - 8013B3C4 (0x3C bytes)
// https://decomp.me/scratch/t8hrY
void ftZelda_8013B388(HSD_GObj* fighterObj) {
    if (func_80082708(fighterObj) == 0) {
        ftZelda_8013B400(fighterObj);
    }
}

// 8013B3C4 - 8013B400 (0x3C bytes)
// https://decomp.me/scratch/t8hrY
void ftZelda_8013B3C4(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj) != 0) {
        ftZelda_8013B46C(fighterObj);
    }
}

// 8013B400 - 8013B46C (0x6C bytes)
// https://decomp.me/scratch/EZlpO
void ftZelda_8013B400(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x166, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013AE30;
}

// 8013B46C - 8013B4D8 (0x6C bytes)
// https://decomp.me/scratch/EZlpO
void ftZelda_8013B46C(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013AE30;
}

// AS_ZeldaFinishTransformation
// 8013B4D8 - 8013B540 (0x68 bytes)
// https://decomp.me/scratch/wpEbJ
void ftZelda_8013B4D8(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* attributes;
    s32 var_r4;
    s32 unused[1];

    fighter = getFighter(fighterObj);
    attributes = fighter->x2D4_specialAttributes;
    
    if (fighter->xE0_ground_or_air == 0) {
        var_r4 = 0x164;
    } else {
        var_r4 = 0x166;
    }

    Fighter_ActionStateChange_800693AC(fighterObj, var_r4, 0, NULL, attributes->x80, 1.0, 0);
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_8013AE30;
}

// 8013B540 - 8013B574 (0x34 bytes)
// https://decomp.me/scratch/L6UUI
s32 ftZelda_8013B540(HSD_GObj* fighterObj) {
    s32 actionStateIndex;
    Fighter* fighter;

    fighter = fighterObj->user_data;
    actionStateIndex = fighter->x10_action_state_index;

    if (((actionStateIndex == 0x158) || (actionStateIndex == 0x15B)) && (fighter->sa.zelda.x222C != 0U)) {
        return 1;
    }
    return 0;
}

// 8013B574 - 8013B5C4 (0x50 bytes)
// https://decomp.me/scratch/tgIRc (fork of below)
// https://decomp.me/scratch/pTAiQ
s32 ftZelda_8013B574(HSD_GObj* fighterObj) {
    s32 temp_r0;
    Fighter* fighter; // r3

    fighter = fighterObj->user_data;
    
    if ((u32) fighter->sa.zelda.x222C != 0U) {
        switch(fighter->x10_action_state_index) {
            case 0x15C:
            case 0x159:
                if (fighter->x2204_ftcmd_var1 == 1) {
                    fighter->x2204_ftcmd_var1 = 0;
                    return 1;
                }
            break;
        }
    }
    
    return 0;
}

// 8013B5C4 - 8013B5EC ( bytes)
// https://decomp.me/scratch/VdBYJ
void ftZelda_8013B5C4(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if ((u32) fighter->sa.zelda.x222C != 0U) {
        fighter->sa.zelda.x222C = 0U;
    }

    fighter->cb.x21E4_callback_OnDeath2 = 0;
    fighter->cb.x21DC_callback_OnTakeDamage = 0;
}

// 8013B5EC - 8013B638 (0x4C bytes)
// https://decomp.me/scratch/8QoCa
void ftZelda_8013B5EC(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if ((u32) fighter->sa.zelda.x222C != 0) {
        func_802C3D44(fighter->sa.zelda.x222C);
        fighter->sa.zelda.x222C = 0;
    }

    fighter->cb.x21E4_callback_OnDeath2 = 0;
    fighter->cb.x21DC_callback_OnTakeDamage = 0;
}