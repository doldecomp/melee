#include <melee/ft/chara/ftZelda/ftzelda.h>

#define HALF_PI 1.5707963705062866f
#define DEG_TO_RAD 0.017453292f

// 801396AC - 801396E0 (0x34 bytes)
// https://decomp.me/scratch/UHxFc
void ftZelda_801396AC(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighter(fighter_gobj);
    ftZelda_801396E0(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = 0;
}

// 801396E0 - 8013979C (0xBC bytes)
// https://decomp.me/scratch/ZIrBS
void ftZelda_801396E0(HSD_GObj* fighter_gobj) {
    Point3d sp10;
    Fighter* fp = getFighter(fighter_gobj);
    u8 flag = fp->x2219_flag.bits.b0;
    
    if (flag == 0) {
        func_8000B1CC(fp->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);

        if ((s32) fp->xE0_ground_or_air == 0) {
            ef_Spawn(0x4F6, fighter_gobj, fp->x5E8_fighterBones->x0_jobj);
        } else {
            ef_Spawn(0x4F7, fighter_gobj, fp->x5E8_fighterBones->x0_jobj);
        }
        fp->x2219_flag.bits.b0 = 1L;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
}

// 8013979C - 80139834 (0x98 bytes)
// https://decomp.me/scratch/yRI2F
void ftZelda_8013979C(HSD_GObj* fighter_gobj) {
    Point3d sp10;
    u8 flag;
    Fighter* fp = getFighter(fighter_gobj);

    func_8000B1CC(fp->x5E8_fighterBones[4].x0_jobj, NULL, &sp10);

    flag = fp->x2219_flag.bits.b0;
    if (flag == 0) {
        ef_Spawn(0x505, fighter_gobj, &sp10);
        fp->x2219_flag.bits.b0 = 1;
    }

    fp->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fp->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fp->cb.x21BC_callback_Accessory4 = 0;
}

// AS_ZeldaUpBStartGround
// 80139834 - 801398E8 (0xB4 bytes)
// https://decomp.me/scratch/KUdnf (with helper)
// https://decomp.me/scratch/52XE3 (as single function)
void ftZelda_SpecialHi_StartAction_Helper(Fighter* fp) {
    HSD_JObj* jObj;
    s32 boneIndex;
    s32 unused[1];
    Vec sp24;

    unused[0] = 1.5; // Trick to use more stack space

    boneIndex = func_8007500C(fp, 4);
    jObj = fp->x5E8_fighterBones[boneIndex].x0_jobj;

    func_8000B1CC(jObj, NULL, &sp24);

    func_800119DC(&sp24, 0x78, 1.5, 0.019999999552965164, 1.0471975803375244);
}
void ftZelda_SpecialHi_StartAction(HSD_GObj* fighter_gobj) {
    Fighter* fp = getFighterPlus(fighter_gobj);

    fp->xEC_ground_vel = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    fp->x80_self_vel.x = 0.0f;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0, NULL, 0.0f, 1.0, 0.0f);
    func_8006EBA4(fighter_gobj);

    fp = getFighterPlus(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x234C_stateVar4 = 0;

    ftZelda_SpecialHi_StartAction_Helper(fp);

    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// AS_ZeldaUpBStartAir
// 801398E8 - 801399B4 (0xCC bytes)
// https://decomp.me/scratch/9NUks
void ftZelda_SpecialAirHi_StartAction(HSD_GObj* fighter_gobj) {
    Point3d sp28;
    s32 unused[7];
    s32 boneIndex;
    Fighter* fp = getFighter(fighter_gobj);
    HSD_JObj* jObj;
    ftZeldaAttributes* attributes = fp->x2D4_specialAttributes;

    fp->x80_self_vel.x = (f32) fp->x80_self_vel.x / attributes->x38;
    fp->x80_self_vel.y = (f32) fp->x80_self_vel.y / attributes->x3C;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0, NULL, 0, 1.0, 0); // lbl_804D9BA4, lbl_804D9BA8
    func_8006EBA4(fighter_gobj);

    fp = getFighter(fighter_gobj);
    fp->x2200_ftcmd_var0 = 0;
    fp->x234C_stateVar4 = 0;

    boneIndex = func_8007500C(fp, 4);
    jObj = fp->x5E8_fighterBones[boneIndex].x0_jobj;
    func_8000B1CC(jObj, NULL, &sp28);

    func_800119DC(&sp28, 0x78, 1.5, 0.019999999552965164, 1.0471975803375244); // lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 801399B4 - 801399F0 (0x3C bytes)
// https://decomp.me/scratch/wsgNa
void ftZelda_801399B4(HSD_GObj* fighter_gobj) {
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        ftZelda_8013A058(fighter_gobj);
    }
}

// Animation_ZeldaUpBStartAir
// 801399F0 - 80139A2C (0x3C bytes)
// https://decomp.me/scratch/3f62U
void ftZelda_801399F0(HSD_GObj* fighter_gobj) {
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        ftZelda_8013A244(fighter_gobj);
    }
}

void ftZelda_80139A2C(HSD_GObj* fighter_gobj) {return;}
void ftZelda_80139A30(HSD_GObj* fighter_gobj) {return;}

// 80139A34 - 80139A54 (0x20 bytes)
void ftZelda_80139A34(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

// 80139A54 - 80139A98 (0x44 bytes)
// https://decomp.me/scratch/dA7X6
void ftZelda_80139A54(HSD_GObj* fighter_gobj) {
    f32 attrs[2];
    Fighter* fp;
    ftZeldaAttributes* attributes;

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    attrs[0] = attributes->x40;
    attrs[1] = attributes->x44;
    
    func_8007D494(fp, attrs[0], attrs[1]);
    func_8007CEF4(fp);
}

// 80139A98 - 80139AD4 (0x3C bytes)
void ftZelda_80139A98(HSD_GObj* fighter_gobj) {
    if (func_80082708(fighter_gobj) == 0) {
        ftZelda_80139B44(fighter_gobj);
    }
}

// 80139AD4 - 80139B44 (0x70 bytes)
// https://decomp.me/scratch/btfXC
void ftZelda_80139AD4(HSD_GObj* fighter_gobj) {
    s32 result;
    f32 facingDirection;
    s32 ledgeGrabDir;

    Fighter* fp = fighter_gobj->user_data;
    facingDirection = fp->x2C_facing_direction;
    
    if (facingDirection < 0) { // lbl_804D9BA4
        ledgeGrabDir = -1;
    } else {
        ledgeGrabDir = 1;
    }

    if (EnvColl_CheckGroundAndLedge(fighter_gobj, ledgeGrabDir) != 0) {
        ftZelda_80139BB0(fighter_gobj);
    } else {
        result = func_80081298(fighter_gobj);
        if (result == 0) {
            return;
        }
    }
}

// 80139B44 - 80139BB0 (0x6C bytes)
// https://decomp.me/scratch/XI2m5
void ftZelda_80139B44(HSD_GObj* fighter_gobj) {
    Fighter* fp;

    fp = fighter_gobj->user_data;
    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x160, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 1.0, 0); // lbl_804D9BA8, lbl_804D9BA4
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 80139BB0 - 80139C1C (0x6C bytes)
// https://decomp.me/scratch/KOA33
void ftZelda_80139BB0(HSD_GObj* fighter_gobj) {
    Fighter* fp;

    fp = fighter_gobj->user_data;
    func_8007D7FC(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15D, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 1.0, 0); // lbl_804D9BA8, lbl_804D9BA4
    fp->cb.x21BC_callback_Accessory4 = &ftZelda_801396AC;
}

// 80139C1C - 80139C58 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C1C(HSD_GObj* fighter_gobj) {
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    fp->x2340_stateVar1 = (s32) (fp->x2340_stateVar1 - 1);
    if ((s32) fp->x2340_stateVar1 <= 0) {
        ftZelda_8013A6A8(fighter_gobj);
    }
}

// 80139C58 - 80139C94 (0x3C bytes)
// https://decomp.me/scratch/VCHRF
void ftZelda_80139C58(HSD_GObj* fighter_gobj) {
    Fighter* fp;

    fp = getFighter(fighter_gobj);
    fp->x2340_stateVar1 = (s32) (fp->x2340_stateVar1 - 1);
    if ((s32) fp->x2340_stateVar1 <= 0) {
        ftZelda_8013A764(fighter_gobj);
    }
}

void ftZelda_80139C94(HSD_GObj* fighter_gobj) {return;}
void ftZelda_80139C98(HSD_GObj* fighter_gobj) {return;}

// 80139C9C - 80139CBC (0x20 bytes)
void ftZelda_80139C9C(HSD_GObj* fighter_gobj) {
    func_8007CB74(fighter_gobj);
}

void ftZelda_80139CBC(HSD_GObj* fighter_gobj) {return;}

// 80139CC0 - 80139D60 (0xA0 bytes)
// https://decomp.me/scratch/UKBQL
void ftZelda_80139CC0(HSD_GObj* fighter_gobj) {
    Fighter* fp;
    s32 envFlags;
    CollData* collData;

    fp = fighter_gobj->user_data;
    collData = &fp->x6F0_collData;
    
    if (func_80082708(fighter_gobj) == 0) {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            func_8007D60C(fp);
            ftZelda_8013A764(fighter_gobj);
            return;
        }
        ftZelda_80139F6C(fighter_gobj);
    } else {
        envFlags = collData->x134_envFlags;
        if (((envFlags & 0x3F) != 0) || ((envFlags & 0xFC0) != 0)) {
            ftZelda_8013A6A8(fighter_gobj);
        }
    }
}


// 80139D60 - 80139F6C (0x20C bytes)
// https://decomp.me/scratch/LfvOU (with helper)
// https://decomp.me/scratch/OJ62l (single function)
BOOL ftZelda_80139D60_Helper(HSD_GObj* fighter_gobj) {
    BOOL var_r0;
    Fighter* fighter2;
    ftZeldaAttributes* attributes2;

    fighter2 = getFighter(fighter_gobj);
    attributes2 = fighter2->x2D4_specialAttributes;

    if (fighter2->x234C_stateVar4_s32 >= attributes2->x4C) {
        var_r0 = 1;
    } else if (func_8009A134(fighter_gobj) != 0) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }

    return var_r0;
}
void ftZelda_80139D60(HSD_GObj* fighter_gobj) {
    s32 ledgeGrabDir;
    BOOL returnVar;
    f32 angle1, angle2, angle3;
    Fighter* fp; // r31
    ftZeldaAttributes* attributes; // r30
    CollData* collData; // r29

    // Get the character, collision data, and character attributes
    fp = fighter_gobj->user_data;
    collData = &fp->x6F0_collData;
    attributes = fp->x2D4_specialAttributes;
    fp->x234C_stateVar4_s32++;

    // Determine facing direction
    if (fp->x2C_facing_direction < 0.0f) {
        ledgeGrabDir = -1;
    } else {
        ledgeGrabDir = 1;
    }
    
    if (EnvColl_CheckGroundAndLedge(fighter_gobj, ledgeGrabDir) != 0) {
        returnVar = ftZelda_80139D60_Helper(fighter_gobj);
        if (returnVar != 0) {
            ftZelda_80139FE8(fighter_gobj);
            return;
        }
    }
    
    if (func_80081298(fighter_gobj) == 0) {
        if ((collData->x134_envFlags & 0x6000) != 0) {
            f32 angle1 = lbvector_AngleXY(&collData->x188_ceiling.normal, &fp->x80_self_vel);
            if (angle1 > (DEG_TO_RAD * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighter_gobj);
            }
        }
        if ((collData->x134_envFlags & 0x3F) != 0) {
            f32 angle2 = lbvector_AngleXY(&collData->x160_rightwall.normal, &fp->x80_self_vel);
            if (angle2 > (DEG_TO_RAD * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighter_gobj);
            }
        }
        if ((collData->x134_envFlags & 0xFC0) != 0) {
            f32 angle3 = lbvector_AngleXY(&collData->x174_leftwall.normal, &fp->x80_self_vel);
            if (angle3 > (DEG_TO_RAD * (90.0f + attributes->x60))) {
                ftZelda_8013A764(fighter_gobj);
            }
        }
    }
}

// 80139F6C - 80139FE8 (0x7C bytes)
// https://decomp.me/scratch/HtMY4
void ftZelda_80139F6C(HSD_GObj* fighter_gobj) {
    Fighter* fp;
    f32 temp_f2;
    s32 unused;

    fp = getFighter(fighter_gobj);

    func_8007D60C(fp);
    
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 0.0f, 0.0f);
    
    fp->x2223_flag.bits.b4 = 1;
    fp->x221E_flag.bits.b0 = 1;
}

// AS_ZeldaUpBGround
// 80139FE8 - 8013A058 (0x70 bytes)
// https://decomp.me/scratch/Jcxch
void ftZelda_80139FE8(HSD_GObj* fighter_gobj) {
    Fighter* fp;
    f32 temp_f2;

    fp = fighter_gobj->user_data;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0x0C4C508E, NULL, fp->x894_currentAnimFrame, 0.0f, 0.0f);
    
    fp->x221E_flag.bits.b0 = 1;
}

// AS_ZeldaUpBTravelGround
// 8013A058 - 8013A244 (0x1EC bytes)
// https://decomp.me/scratch/ruApT
void ftZelda_8013A058(HSD_GObj* fighter_gobj) {
    Vec inputVector;
    Vec* groundVector;
    volatile float y;
    f64 _three;
    f64 _half;
    Fighter* fp; // r30
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

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    collData = &fp->x6F0_collData;
    temp_f2 = fp->input.x620_lstick_x;
    temp_f1 = fp->input.x624_lstick_y;
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
        groundVector = &collData->x14C_ground.normal;
        inputVector.x = fp->input.x620_lstick_x;
        inputVector.y = fp->input.x624_lstick_y;
        inputVector.z = 0;

        if (!(lbvector_AngleXY(groundVector, (Point3d* ) &inputVector.x) < HALF_PI)) {
            if (func_8009A134(fighter_gobj) == 0) {
                func_8007D9FC(fp);
                
                temp_f5 = atan2f(fp->input.x624_lstick_y, fp->input.x620_lstick_x * fp->x2C_facing_direction);
                
                fp->x2344_f32 = inputVector.x;
                fp->x2348_stateVar3_f32 = inputVector.y;

                // Update ground velocity
                temp_f6 = ((attributes->x54 * var_f31) + attributes->x58) * cosf(temp_f5);
                fp->xEC_ground_vel = fp->x2C_facing_direction * temp_f6;
                
                Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15E, 0, NULL, 35.0, 1.0, 0);
                func_8006EBA4(fighter_gobj);
                ftAnim_SetAnimRate(fighter_gobj, 0);
                
                fp = fighter_gobj->user_data;
                attributes = fp->x2D4_specialAttributes;
                fp->x2340_stateVar1 = attributes->x48;
                fp->x1968_jumpsUsed = (u8) fp->x110_attr.x168_MaxJumps;
                fp->x2223_flag.bits.b4 = 1;
                
                func_8007B62C(fighter_gobj, 2, attributes);
                fp->x221E_flag.bits.b0 = 1;
                return;
            }
        }
    }
    func_8007D60C(fp);
    ftZelda_8013A244(fighter_gobj);
}

// AS_ZeldaUpBTravelAir
// 8013A244 - 8013A448 (0x204 bytes)
// https://decomp.me/scratch/70TAa
void ftZelda_8013A244(HSD_GObj* fighter_gobj) {
    volatile float y;
    Fighter* fp; // r30
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
    
    fp = fighter_gobj->user_data;
    temp_f2 = fp->input.x620_lstick_x;
    temp_f1 = fp->input.x624_lstick_y;
    attributes = fp->x2D4_specialAttributes;
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
        temp_f1 = fp->input.x620_lstick_x;
        if (temp_f1 < 0) {
            temp_f1 = -temp_f1;
        }
        if (temp_f1 > 0.0010000000474974513f) {
            func_8007D9FC(fp);
        }
        var_f30 = atan2f(fp->input.x624_lstick_y, fp->input.x620_lstick_x * fp->x2C_facing_direction);
        fp->x2344_f32 = fp->input.x620_lstick_x;
        fp->x2348_stateVar3_f32 = fp->input.x624_lstick_y;
    } else {
        func_8007DA24(fp);
        var_f30 = HALF_PI;
        fp->x2344_f32 = 0;
        var_f31 = fp->x2348_stateVar3_f32 = 1.0;
    }

    fp->x80_self_vel.x = fp->x2C_facing_direction * (((attributes->x54 * var_f31) + attributes->x58) * cosf(var_f30));
    fp->x80_self_vel.y = ((attributes->x54 * var_f31) + attributes->x58) * sinf(var_f30);
    
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x161, 0, NULL, 35.0, 1.0, 0);
    func_8006EBA4(fighter_gobj);
    ftAnim_SetAnimRate(fighter_gobj, 0);
    
    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    fp->x2340_stateVar1 = (s32) attributes->x48;
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
    fp->x2223_flag.bits.b4 = 1;
    
    func_8007B62C(fighter_gobj, 2, attributes);
    
    fp->x221E_flag.bits.b0 = 1;
}

// 8013A448 - 8013A484 (0x3C bytes)
// https://decomp.me/scratch/iQFL9
void ftZelda_8013A448(HSD_GObj* fighter_gobj) {
    u32 unused[2];
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        func_8008A2BC(fighter_gobj);
    }
}

// 8013A484 - 8013A4E4 (0x60 bytes)
// https://decomp.me/scratch/8Hjri
void ftZelda_8013A484(HSD_GObj* fighter_gobj) {
    ftZeldaAttributes* attributes; // r31
    Fighter* fp; // r4
    f32 attr1, attr2; // f1, f2
    u32 unused;

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    
    if (ftAnim_IsFramesRemaining(fighter_gobj) == 0) {
        attr1 = attributes->x68;
        attr2 = attributes->x6C;
        func_80096900(fighter_gobj, 1, 0, 1, attr1, attr2);
    }
}

void ftZelda_8013A4E4(HSD_GObj* fighter_gobj) {return;}
void ftZelda_8013A4E8(HSD_GObj* fighter_gobj) {return;}

// 8013A4EC - 8013A50C (0x20 bytes)
void ftZelda_8013A4EC(HSD_GObj* fighter_gobj) {
    func_80084F3C(fighter_gobj);
}

// Physics_ZeldaUpBEndAir
// 8013A50C - 8013A588 (0x7C bytes)
// https://decomp.me/scratch/9VS7Q
void ftZelda_8013A50C(HSD_GObj* fighter_gobj) {
    Fighter* fp; // r31
    f32 temp_f1;
    ftZeldaAttributes* attributes; // r30
    u32 unused[2];

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;

    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        func_8007D4B8(fp);
        func_8007D440(fp, attributes->x5C * fp->x110_attr.x17C_AerialDriftMax);
        return;
    }

    temp_f1 = fp->x80_self_vel.y;
    fp->x80_self_vel.y = temp_f1 - (temp_f1 / 10.0f);

    func_8007CEF4(fp);
}

// Collision_ZeldaUpBEndGround
// 8013A588 - 8013A5C4 (0x3C bytes)
void ftZelda_8013A588(HSD_GObj* fighter_gobj) {
    if (func_800827A0(fighter_gobj) == 0) {
        ftZelda_8013A648(fighter_gobj);
    }
}

// 8013A5C4 - 8013A648 (0x84 bytes)
// https://decomp.me/scratch/nLZxP
void ftZelda_8013A5C4(HSD_GObj* fighter_gobj) {
    Fighter* fp; // r3
    ftZeldaAttributes* attributes; // r31
    s32 ledgeGrabDir;
    BOOL result;
    s32 unused[2];

    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;
    
    if (fp->x2C_facing_direction < 0) {
        ledgeGrabDir = -1;
    } else {
        ledgeGrabDir = 1;
    }

    if (EnvColl_CheckGroundAndLedge(fighter_gobj, ledgeGrabDir) != 0) {
        func_800D5CB0(fighter_gobj, 0, attributes->x6C);
        return;
    }

    result = func_80081298(fighter_gobj);
    if (result == 0) {
        return;
    }
}

// AS_ZeldaUpBEndAir?
// 8013A648 - 8013A6A8 (0x60 bytes)
void ftZelda_8013A648(HSD_GObj* fighter_gobj) {
    Fighter* fp;

    fp = fighter_gobj->user_data;
    func_8007D60C(fp);
    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0x0C4C508A, NULL, fp->x894_currentAnimFrame, 1.0, 0);
}

// AS_ZeldaUpBEndGround
// 8013A6A8 - 8013A764 (0xBC bytes)
// https://decomp.me/scratch/5iU4R
void ftZelda_8013A6A8(HSD_GObj* fighter_gobj) {
    f32 temp_f0;
    Fighter* fp; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2;
    s32 unused[3];

    temp_f0 = 0;
    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x15F, 0, NULL, temp_f0, 1.0f, temp_f0);
    func_8006EBA4(fighter_gobj);

    fighter2 = fighter_gobj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6_f32 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    fighter2->x80_self_vel.y = 0;
    fighter2->x80_self_vel.x = 0;
    fighter2->xEC_ground_vel = 0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fp->xEC_ground_vel = (f32) (fp->x2358_stateVar7 * attributes->x64);
}

// AS_ZeldaUpBEndAir?
// 8013A764 - 8013A830 (0xCC bytes)
// https://decomp.me/scratch/8Fjwf
void ftZelda_8013A764(HSD_GObj* fighter_gobj) {
    f32 temp_f0;
    Fighter* fp; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2; // r5
    f32 unused[3];

    temp_f0 = 0;
    fp = fighter_gobj->user_data;
    attributes = fp->x2D4_specialAttributes;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 0x162, 0, NULL, temp_f0, 1.0, temp_f0);
    func_8006EBA4(fighter_gobj);

    fighter2 = fighter_gobj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6_f32 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    fighter2->x80_self_vel.y = 0;
    fighter2->x80_self_vel.x = 0;
    fighter2->xEC_ground_vel = 0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fp->x80_self_vel.x = (f32) (fp->x2350_stateVar5_f32 * attributes->x64);
    fp->x80_self_vel.y = (f32) (fp->x2354_stateVar6_f32 * attributes->x64);
}
