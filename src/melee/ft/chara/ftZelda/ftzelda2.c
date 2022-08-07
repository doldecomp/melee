#include "ftzelda.h"

// 801396AC - 801396E0 (0x34 bytes)
// https://decomp.me/scratch/UHxFc
void ftZelda_801396AC(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftZelda_801396E0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 801396E0 - 8013979C (0xBC bytes)
// https://decomp.me/scratch/ZIrBS
void ftZelda_801396E0(HSD_GObj* fighterObj) {
    Point3d sp10;
    Fighter* fighter = getFighter(fighterObj);
    u8 flag = fighter->x2219_flag.bits.b0;
    
    if (flag == 0) {
        func_8000B1CC(fighter->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);
        
        if ((s32) fighter->xE0_ground_or_air == 0) {
            ef_Spawn(0x4F6, fighterObj, fighter->x5E8_fighterBones->x0_jobj);
        } else {
            ef_Spawn(0x4F7, fighterObj, fighter->x5E8_fighterBones->x0_jobj);
        }
        fighter->x2219_flag.bits.b0 = 1L;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 8013979C - 80139834 (0x98 bytes)
// https://decomp.me/scratch/yRI2F
void ftZelda_8013979C(HSD_GObj* fighterObj) {
    Point3d sp10;
    u8 flag;
    Fighter* fighter = getFighter(fighterObj);

    func_8000B1CC(fighter->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);

    flag = fighter->x2219_flag.bits.b0;
    if (flag == 0) {
        ef_Spawn(0x505, fighterObj, &sp10);
        fighter->x2219_flag.bits.b0 = 1;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 80139834 - 801398E8 (0xB4 bytes)
// https://decomp.me/scratch/TOq04 (with inline)
// https://decomp.me/scratch/52XE3 (as single function)
void ftZelda_SpecialHi_StartAction_Inline(Fighter* fighter) {
    HSD_JObj* jObj;
    s32 boneIndex;
    s32 unused[1];
    Vec sp24;

    unused[0] = 1.5; // Trick to use more stack space

    boneIndex = func_8007500C(fighter, 4);
    jObj = fighter->x5E8_fighterBones[boneIndex].x0_jobj;

    func_8000B1CC(jObj, NULL, &sp24);
    func_800119DC(&sp24, 0x78, 1.5, 0.019999999552965164, 1.0471975803375244);
}
void ftZelda_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighterPlus(fighterObj);

    fighter->xEC_ground_vel = 0.0;
    fighter->x80_self_vel.y = 0.0;
    fighter->x80_self_vel.x = 0.0;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0, NULL, 0.0, 1.0, 0.0);
    func_8006EBA4(fighterObj);
    
    fighter = getFighterPlus(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;

    ftZelda_SpecialHi_StartAction_Inline(fighter);

    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 801398E8 - 801399B4 (0xCC bytes)
// https://decomp.me/scratch/9NUks
void ftZelda_SpecialAirHi_StartAction(HSD_GObj* fighterObj) {
    Point3d sp28;
    s32 unused[7];
    s32 boneIndex;
    Fighter* fighter = getFighter(fighterObj);
    HSD_JObj* jObj;
    ftZeldaAttributes* attributes = fighter->x2D4_specialAttributes;
        
    fighter->x80_self_vel.x = (f32) fighter->x80_self_vel.x / attributes->x38;
    fighter->x80_self_vel.y = (f32) fighter->x80_self_vel.y / attributes->x3C;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0, NULL, 0, 1.0, 0); // lbl_804D9BA4, lbl_804D9BA8
    func_8006EBA4(fighterObj);
    
    fighter = getFighter(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;
    
    boneIndex = func_8007500C(fighter, 4);
    jObj = fighter->x5E8_fighterBones[boneIndex].x0_jobj;
    func_8000B1CC(jObj, NULL, &sp28);
    
    func_800119DC(&sp28, 0x78, 1.5, 0.019999999552965164, 1.0471975803375244); // lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 801399B4 - 801399F0 (0x3C bytes)
// https://decomp.me/scratch/wsgNa
void ftZelda_801399B4(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftZelda_8013A058(arg0);
    }
}

// 801399F0 - 80139A2C (0x3C bytes)
// https://decomp.me/scratch/3f62U
void ftZelda_801399F0(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        ftZelda_8013A244(arg0);
    }
}

void ftZelda_80139A2C(HSD_GObj* arg0) {}
void ftZelda_80139A30(HSD_GObj* arg0) {}

// 80139A34 - 80139A54 (0x20 bytes)
void ftZelda_80139A34(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

// 80139A54 - 80139A98 (0x44 bytes)
// https://decomp.me/scratch/dA7X6
void ftZelda_80139A54(HSD_GObj* fighterObj) {
    f32 attrs[2];
    Fighter* fighter;
    ftZeldaAttributes* attributes;

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    attrs[0] = attributes->x40;
    attrs[1] = attributes->x44;
    
    func_8007D494(fighter, attrs[0], attrs[1]);
    func_8007CEF4(fighter);
}

// 80139A98 - 80139AD4 (0x3C bytes)
void ftZelda_80139A98(HSD_GObj* arg0) {
    if (func_80082708(arg0) == 0) {
        ftZelda_80139B44(arg0);
    }
}

// 80139AD4 - 80139B44 (0x70 bytes)
// https://decomp.me/scratch/btfXC
void ftZelda_80139AD4(HSD_GObj* fighterObj) {
    s32 result;
    f32 facingDirection;
    s32 ledgeGrabDir;
    Fighter* fighter = fighterObj->user_data;
    facingDirection = fighter->x2C_facing_direction;
    
    if (facingDirection < 0) { // lbl_804D9BA4
        ledgeGrabDir = -1;
    }
    else {
        ledgeGrabDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighterObj, ledgeGrabDir) != 0) {
        ftZelda_80139BB0(fighterObj);
    } else {
        result = func_80081298(fighterObj);
        if (result == 0) {
            return;
        }
    }
}

// 80139B44 - 80139BB0 (0x6C bytes)
// https://decomp.me/scratch/XI2m5
void ftZelda_80139B44(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0); // lbl_804D9BA8, lbl_804D9BA4
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 80139BB0 - 80139C1C (0x6C bytes)
// https://decomp.me/scratch/KOA33
void ftZelda_80139BB0(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 1.0, 0); // lbl_804D9BA8, lbl_804D9BA4
    fighter->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 80139C1C - 80139C58 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C1C(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = getFighter(fighterObj);
    fighter->x2340_stateVar1 = (s32) (fighter->x2340_stateVar1 - 1);
    if ((s32) fighter->x2340_stateVar1 <= 0) {
        ftZelda_8013A6A8(fighterObj);
    }
}

// 80139C58 - 80139C94 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C58(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = getFighter(fighterObj);
    fighter->x2340_stateVar1 = (s32) (fighter->x2340_stateVar1 - 1);
    if ((s32) fighter->x2340_stateVar1 <= 0) {
        ftZelda_8013A764(fighterObj);
    }
}

void ftZelda_80139C94(HSD_GObj* arg0) {}
void ftZelda_80139C98(HSD_GObj* arg0) {}

// 80139C9C - 80139CBC (0x20 bytes)
void ftZelda_80139C9C(HSD_GObj* arg0) {
    func_8007CB74(arg0);
}

void ftZelda_80139CBC(HSD_GObj* arg0) {}

// 80139CC0 - 80139D60 (0xA0 bytes)
// https://decomp.me/scratch/UKBQL
void ftZelda_80139CC0(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 envFlags;
    CollData* collData;

    fighter = fighterObj->user_data;
    collData = &fighter->x6F0_collData;
    
    if (func_80082708(fighterObj) == 0) {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            func_8007D60C(fighter);
            ftZelda_8013A764(fighterObj);
            return;
        }
        ftZelda_80139F6C(fighterObj);
    } else {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            ftZelda_8013A6A8(fighterObj);
        }
    }
}

// 80139D60 - 80139F6C (0x20C bytes)
// https://decomp.me/scratch/LfvOU (with inline)
// https://decomp.me/scratch/OJ62l (single function)
s32 ftZelda_80139D60_Inline(HSD_GObj* fighterObj) {
    s32 var_r0;
    Fighter* fighter2;
    ftZeldaAttributes* attributes2;
    
    fighter2 = getFighter(fighterObj);
    attributes2 = fighter2->x2D4_specialAttributes;
    
    if ((f32) (fighter2->x234C_stateVar4 ^ 0x80000000) >= attributes2->x4C) {
        var_r0 = 1;
    } else if (func_8009A134(fighterObj) != 0) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }

    return var_r0;
}
void ftZelda_80139D60(HSD_GObj* fighterObj) {
    s32 ledgeGrabDir;
    s32 returnVar;
    f32 angle1, angle2, angle3;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    CollData* collData; // r29

    // Get the character, collision data, and character attributes
    fighter = fighterObj->user_data;
    collData = &fighter->x6F0_collData;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x234C_stateVar4 = (s32) (fighter->x234C_stateVar4 + 1);

    // Determine facing direction
    if (fighter->x2C_facing_direction < 0.0) {
        ledgeGrabDir = -1;
    }
    else {
        ledgeGrabDir = 1;
    }
    
    if (EnvColl_CheckGroundAndLedge(fighterObj, ledgeGrabDir) != 0) {
        returnVar = ftZelda_80139D60_Inline(fighterObj);
        if (returnVar != 0) {
            ftZelda_80139FE8(fighterObj);
            return;
        }
    }
    
    if (func_80081298(fighterObj) == 0) {
        if ((collData->x134_envFlags & 0x6000) != 0) {
            f32 angle1 = lbvector_AngleXY(&collData->x190_vec, &fighter->x80_self_vel);
            if (angle1 > (0.01745329238474369f * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighterObj);
            }
        }
        if ((collData->x134_envFlags & 0x3F) != 0) {
            f32 angle2 = lbvector_AngleXY(&collData->x168_vec, &fighter->x80_self_vel);
            if (angle2 > (0.01745329238474369f * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighterObj);
            }
        }
        if ((collData->x134_envFlags & 0xFC0) != 0) {
            f32 angle3 = lbvector_AngleXY(&collData->x17C_vec, &fighter->x80_self_vel);
            if (angle3 > (0.01745329238474369f * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighterObj);
            }
        }
    }
}

// 80139F6C - 80139FE8 (0x7C bytes)
// https://decomp.me/scratch/HtMY4
void ftZelda_80139F6C(HSD_GObj* fighterObj) {
    Fighter* fighter;
    f32 temp_f2;
    s32 unused;

    fighter = getFighter(fighterObj);
    func_8007D60C(fighter);
    
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 0.0f, 0.0f);
    
    fighter->x2223_flag.bits.b4 = 1;
    fighter->x221E_flag.bits.b0 = 1;
}

// 80139FE8 - 8013A058 (0x70 bytes)
// https://decomp.me/scratch/Jcxch
void ftZelda_80139FE8(HSD_GObj* fighterObj) {
    Fighter* fighter;
    f32 temp_f2;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);

    Fighter_ActionStateChange_800693AC(fighterObj, 0x15E, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, 0.0f, 0.0f);
    
    fighter->x221E_flag.bits.b0 = 1;
}

// 8013A058 - 8013A244 (0x1EC bytes)
// https://decomp.me/scratch/ruApT
void ftZelda_8013A058(HSD_GObj* fighterObj) {
    Vec inputVector;
    Vec* groundVector;
    volatile float y;
    f64 _three;
    f64 _half;
    Fighter* fighter; // r30
    ftZeldaAttributes* attributes; // r31
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f1_5;
    f32 temp_f2;
    f32 var_f31;
    f32 var_f4;
    f32 temp_f5;
    f32 temp_f6;
    f64 guess;
    CollData* collData;
    f32 unused[3];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    collData = &fighter->x6F0_collData;
    temp_f2 = fighter->input.x620_lstick_x;
    temp_f1 = fighter->input.x624_lstick_y;
    temp_f2 = temp_f2 * temp_f2;
    temp_f1 = temp_f1 * temp_f1;
    temp_f5 = temp_f2 + temp_f1;
    var_f4 = temp_f5;
    
    // Essentially performing a square root operation 
    // (Avoiding sqrtf to preserve stack alignment.)
    if (var_f4 > 0.0f) {
        f64 guess = __frsqrte(var_f4);
        _half = .5F;
        _three = 3.0F;
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        y=(float)(var_f4*guess);
        temp_f5 = y;
    }
    
    temp_f0 = 1.0;
    var_f31 = temp_f5;
    if (temp_f5 > temp_f0) {
        var_f31 = temp_f0;
    }
    if (!(var_f31 < attributes->x50)) {
        groundVector = &collData->x154_groundNormal;
        inputVector.x = fighter->input.x620_lstick_x;
        inputVector.y = fighter->input.x624_lstick_y;
        inputVector.z = 0;
        if (!(lbvector_AngleXY(groundVector, (Point3d* ) &inputVector.x) < 1.5707963705062866f)) {
            if (func_8009A134(fighterObj) == 0) {
                func_8007D9FC(fighter);
                
                temp_f5 = func_someCalcAngle_80022C30(fighter->input.x624_lstick_y, fighter->input.x620_lstick_x * fighter->x2C_facing_direction);
                
                fighter->x2344_f32 = inputVector.x;
                fighter->x2348_stateVar3_f32 = inputVector.y;

                // Update ground velocity
                temp_f6 = ((attributes->x54 * var_f31) + attributes->x58) * cosf(temp_f5);
                fighter->xEC_ground_vel = fighter->x2C_facing_direction * temp_f6;
                
                Fighter_ActionStateChange_800693AC(fighterObj, 0x15E, 0, NULL, 35.0, 1.0, 0);
                func_8006EBA4(fighterObj);
                ftAnim_SetAnimRate(fighterObj, 0);
                
                fighter = fighterObj->user_data;
                attributes = fighter->x2D4_specialAttributes;
                fighter->x2340_stateVar1 = attributes->x48;
                fighter->x1968_jumpsUsed = (u8) fighter->x110_attr.x168_MaxJumps;
                fighter->x2223_flag.bits.b4 = 1;
                
                func_8007B62C(fighterObj, 2, attributes);
                fighter->x221E_flag.bits.b0 = 1;
                return;
            }
        }
    }
    func_8007D60C(fighter);
    ftZelda_8013A244(fighterObj);
}

// 8013A244 - 8013A448 (0x204 bytes)
// https://decomp.me/scratch/70TAa
void ftZelda_8013A244(HSD_GObj* fighterObj) {
    volatile float y;
    Fighter* fighter; // r30
    ftZeldaAttributes* attributes; // r31
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f4;
    f32 var_f5;
    f32 var_f30;
    f32 var_f31;
    f32 temp_f0;
    f32 unused[5];
    f64 _half;
    f64 _three;
    f64 guess;
    
    fighter = fighterObj->user_data;
    temp_f2 = fighter->input.x620_lstick_x;
    temp_f1 = fighter->input.x624_lstick_y;
    attributes = fighter->x2D4_specialAttributes;
    temp_f1 = temp_f1 * temp_f1;
    temp_f2 = temp_f2 * temp_f2;
    var_f5 = temp_f2 + temp_f1;
    var_f4 = var_f5;
    
    // Essentially performing a square root operation 
    // (Avoiding sqrtf to preserve stack alignment.)
    if (var_f4 > 0) {
        guess = __frsqrte(var_f4);
        _half = .5F;
        _three = 3.0F;
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        y=(var_f4*guess);
        var_f5 = y;
    }
    
    temp_f0 = 1.0;
    var_f31 = var_f5;
    if (var_f5 > temp_f0) {
        var_f31 = temp_f0;
    }
    if (var_f31 > attributes->x50) {
        temp_f1 = fighter->input.x620_lstick_x;
        if (temp_f1 < 0) {
            temp_f1 = -temp_f1;
        }
        if (temp_f1 > 0.0010000000474974513f) {
            func_8007D9FC(fighter);
        }
        var_f30 = func_someCalcAngle_80022C30(fighter->input.x624_lstick_y, fighter->input.x620_lstick_x * fighter->x2C_facing_direction);
        fighter->x2344_f32 = fighter->input.x620_lstick_x;
        fighter->x2348_stateVar3_f32 = fighter->input.x624_lstick_y;
    } else {
        func_8007DA24(fighter);
        var_f30 = 1.5707963705062866f;
        fighter->x2344_f32 = 0;
        var_f31 = fighter->x2348_stateVar3_f32 = 1.0;
    }
    fighter->x80_self_vel.x = fighter->x2C_facing_direction * (((attributes->x54 * var_f31) + attributes->x58) * cosf(var_f30));
    fighter->x80_self_vel.y = ((attributes->x54 * var_f31) + attributes->x58) * sinf(var_f30);
    
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, NULL, 35.0, 1.0, 0);
    func_8006EBA4(fighterObj);
    ftAnim_SetAnimRate(fighterObj, 0);
    
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x2340_stateVar1 = (s32) attributes->x48;
    fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    fighter->x2223_flag.bits.b4 = 1;
    
    func_8007B62C(fighterObj, 2, attributes);
    
    fighter->x221E_flag.bits.b0 = 1;
}

// 8013A448 - 8013A484 (0x3C bytes)
// https://decomp.me/scratch/iQFL9
void ftZelda_8013A448(HSD_GObj* fighterObj) {
    u32 unused[2];
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        func_8008A2BC(fighterObj);
    }
}

// 8013A484 - 8013A4E4 (0x60 bytes)
// https://decomp.me/scratch/8Hjri
void ftZelda_8013A484(HSD_GObj* fighterObj) {
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r4
    f32 attr1, attr2; // f1, f2
    u32 unused;

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        attr1 = attributes->x68;
        attr2 = attributes->x6C;
        func_80096900(fighterObj, 1, 0, 1, attr1, attr2);
    }
}

void ftZelda_8013A4E4(HSD_GObj* arg0) {}
void ftZelda_8013A4E8(HSD_GObj* arg0) {}

// 8013A4EC - 8013A50C (0x20 bytes)
void ftZelda_8013A4EC(HSD_GObj* arg0) {
    func_80084F3C(arg0);
}

// 8013A50C - 8013A588 (0x7C bytes)
// https://decomp.me/scratch/9VS7Q
void ftZelda_8013A50C(HSD_GObj* fighterObj) {
    Fighter* fighter; // r31
    f32 temp_f1;
    ftZeldaAttributes* attributes; // r30
    u32 unused[2];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if ((u32) fighter->x2200_ftcmd_var0 != 0U) {
        func_8007D4B8(fighter);
        func_8007D440(fighter, attributes->x5C * fighter->x110_attr.x17C_AerialDriftMax);
        return;
    }
    temp_f1 = fighter->x80_self_vel.y;
    fighter->x80_self_vel.y = temp_f1 - (temp_f1 / 10.0f);
    func_8007CEF4(fighter);
}

// 8013A588 - 8013A5C4 (0x3C bytes)
void ftZelda_8013A588(HSD_GObj* arg0) {
    if (func_800827A0(arg0) == 0) {
        ftZelda_8013A648(arg0);
    }
}

// 8013A5C4 - 8013A648 (0x84 bytes)
// https://decomp.me/scratch/nLZxP
void ftZelda_8013A5C4(HSD_GObj* fighterObj) {
    Fighter* fighter; // r3
    ftZeldaAttributes* attributes; // r31
    s32 ledgeGrabDir;
    BOOL result;
    s32 unused[2];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    
    if (fighter->x2C_facing_direction < 0) {
        ledgeGrabDir = -1;
    } else {
        ledgeGrabDir = 1;
    }
    if (EnvColl_CheckGroundAndLedge(fighterObj, ledgeGrabDir) != 0) {
        func_800D5CB0(fighterObj, 0, attributes->x6C);
        return;
    }
    result = func_80081298(fighterObj);
    if (result == 0) {
        return;
    }
}

// 8013A648 - 8013A6A8 (0x60 bytes)
void ftZelda_8013A648(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0x0C4C508A, NULL, fighter->x894_currentAnimFrame, 1.0, 0);
}

// 8013A6A8 - 8013A764 (0xBC bytes)
// https://decomp.me/scratch/5iU4R
void ftZelda_8013A6A8(HSD_GObj* fighterObj) {
    f32 temp_f0;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2;
    s32 unused[3];

    temp_f0 = 0;
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15F, 0, NULL, temp_f0, 1.0f, temp_f0);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6_f32 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    fighter2->x80_self_vel.y = 0;
    fighter2->x80_self_vel.x = 0;
    fighter2->xEC_ground_vel = 0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fighter->xEC_ground_vel = (f32) (fighter->x2358_stateVar7 * attributes->x64);
}

// 8013A764 - 8013A830 (0xCC bytes)
// https://decomp.me/scratch/8Fjwf
void ftZelda_8013A764(HSD_GObj* fighterObj) {
    f32 temp_f0;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2; // r5
    f32 unused[3];

    temp_f0 = 0;
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0, NULL, temp_f0, 1.0, temp_f0);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6_f32 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    fighter2->x80_self_vel.y = 0;
    fighter2->x80_self_vel.x = 0;
    fighter2->xEC_ground_vel = 0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fighter->x80_self_vel.x = (f32) (fighter->x2350_stateVar5_f32 * attributes->x64);
    fighter->x80_self_vel.y = (f32) (fighter->x2354_stateVar6_f32 * attributes->x64);
}
