#include "ftzelda.h"

void ftZelda_OnDeath(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_80074A4C(fighterObj, 0, 0);
    func_80074A4C(fighterObj, 1, 0);
    fighter->sa.zelda.x222C = 0;
}

void ftZelda_OnLoad(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    void** item_list = fighter->x10C_ftData->x48_items;
    
    PUSH_ATTRS(fighter, ftZeldaAttributes);
    
    func_8026B3F8(item_list[0], 0x6CU);
    func_8026B3F8(item_list[1], 0x6DU);
}

void ftZelda_801393AC(HSD_GObj* fighterObj) {
    ftZelda_8013B5EC(fighterObj);
}

void ftZelda_OnItemPickup(HSD_GObj* fighterObj, BOOL bool) {
    Fighter_OnItemPickup(fighterObj, bool, 1, 1);
}

void ftZelda_OnItemInvisible(HSD_GObj *fighterObj) {
    Fighter_OnItemInvisible(fighterObj, 1);
}

void ftZelda_OnItemVisible(HSD_GObj *fighterObj) {
    Fighter_OnItemVisible(fighterObj, 1);
}

void ftZelda_OnItemDrop(HSD_GObj* fighterObj, BOOL bool1) {
    Fighter_OnItemDrop(fighterObj, bool1, 1, 1);
}

void ftZelda_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftZeldaAttributes);
}

void ftZelda_801395C8(HSD_GObj* fighterObj) {
    s32 unused[2];
    s32 result = func_80074A74(fighterObj, 1);
    if (result == -1) {
        func_80074A4C(fighterObj, 1, 0);
    } else {
        func_80074A4C(fighterObj, 1, -1);
    }
}

void ftZelda_OnKnockbackEnter(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackEnter(fighterObj, 1);
}

void ftZelda_OnKnockbackExit(HSD_GObj* fighterObj) {
    Fighter_OnKnockbackExit(fighterObj, 1);
}

// 801396AC - 801396E0 (0x34 bytes)
// https://decomp.me/scratch/UHxFc
void ftZelda_801396AC(HSD_GObj* fighterObj) {
    Fighter* fighter = getFighter(fighterObj);
    ftZelda_801396E0(fighterObj);
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

// 801396E0 - 8013979C (0xBC bytes)
// https://decomp.me/scratch/ZIrBS
void func_801396E0(HSD_GObj* fighterObj) {
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
        fighter->x2219_flag.bits.b0 = 1L;
    }
    fighter->cb.x21D4_callback_EnterHitlag = efLib_PauseAll;
    fighter->cb.x21D8_callback_ExitHitlag = efLib_ResumeAll;
    fighter->cb.x21BC_callback_Accessory4 = 0;
}

//void ftZelda_801396AC(HSD_GObj*);
extern f32 lbl_804D9B98; // 1.5
extern f32 lbl_804D9B9C; // 0.019999999552965164
extern f32 lbl_804D9BA0; // 1.0471975803375244
extern f32 lbl_804D9BA4; // 0
extern f32 lbl_804D9BA8; // 1.0

extern f32 lbl_804D9BB8; // 0.01745329238474369
extern f32 lbl_804D9BBC; // 90.0

extern f64 lbl_804D9BC0; // .5
extern f64 lbl_804D9BC8; // 3.0
extern f32 lbl_804D9BD0; // 1.5707963705062866
extern f32 lbl_804D9BD4; // 35.0

extern f32 lbl_804D9BD8; // 0.0010000000474974513


extern f32 lbl_804D9BE0; // 0
extern f32 lbl_804D9BE4; // 1.0

// 80139834 - 801398E8 (0xB4 bytes)
// https://decomp.me/scratch/Ie9jz
// https://decomp.me/scratch/52XE3
void ftZelda_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    Vec sp24;
    HSD_JObj* jObj;
    s32 arg1; // this is unused
    HSD_GObj* gObj;  // this is unused
    Fighter* fighter = getFighterPlus(fighterObj);

    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    fighter = getFighterPlus(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;
    
    jObj = fighter->x5E8_fighterBones[func_8007500C(fighter, 4)].x0_jobj;
    
    func_8000B1CC(jObj, NULL, &sp24); 
    
    func_800119DC(&sp24, 0x78, lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0);
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
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0, NULL, lbl_804D9BA4, lbl_804D9BA8, lbl_804D9BA4);
    func_8006EBA4(fighterObj);
    
    fighter = getFighter(fighterObj);
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x234C_stateVar4 = 0;
    
    boneIndex = func_8007500C(fighter, 4);
    jObj = fighter->x5E8_fighterBones[boneIndex].x0_jobj;
    func_8000B1CC(jObj, NULL, &sp28);
    
    func_800119DC(&sp28, 0x78, lbl_804D9B98, lbl_804D9B9C, lbl_804D9BA0);
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
void lbl_801399F0(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_8013A244(arg0);
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

//extern f32 lbl_804D9BA4;

// 80139AD4 - 80139B44 (0x70 bytes)
// https://decomp.me/scratch/btfXC
void ftZelda_80139AD4(HSD_GObj* fighterObj) {
    s32 result;
    f32 facingDirection;
    s32 ledgeGrabDir;
    Fighter* fighter = fighterObj->user_data;
    facingDirection = fighter->x2C_facing_direction;
    
    if (facingDirection < lbl_804D9BA4) {
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
    Fighter_ActionStateChange_800693AC(fighterObj, 0x160, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BA8, lbl_804D9BA4);
    fighter->cb.x21BC_callback_Accessory4 = ftZelda_801396AC;
}

// 80139BB0 - 80139C1C (0x6C bytes)
// https://decomp.me/scratch/KOA33
void ftZelda_80139BB0(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15D, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BA8, lbl_804D9BA4);
    fighter->cb.x21BC_callback_Accessory4 = ftZelda_801396AC;
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
// https://decomp.me/scratch/OJ62l
void ftZelda_80139D60(HSD_GObj* fighterObj) {
    s32 ledgeGrabDir;
    s32 var_r0;
    s32 unused[2];
    f32 angle1, angle2, angle3;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2;
    ftZeldaAttributes* attributes2;
    CollData* collData; // r29

    // Get the character, collision data, and character attributes
    fighter = fighterObj->user_data;
    collData = &fighter->x6F0_collData;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x234C_stateVar4 = (s32) (fighter->x234C_stateVar4 + 1);

    // Determine facing direction
    if (fighter->x2C_facing_direction < lbl_804D9BA4) {
        ledgeGrabDir = -1;
    }
    else {
        ledgeGrabDir = 1;
    }
    
    if (EnvColl_CheckGroundAndLedge(fighterObj, ledgeGrabDir) != 0) {
        fighter2 = getFighter(fighterObj);
        attributes2 = fighter2->x2D4_specialAttributes;
        if ((f32) (fighter2->x234C_stateVar4 ^ 0x80000000) >= attributes2->x4C) {
            var_r0 = 1;
        } else if (func_8009A134(fighterObj) != 0) {
            var_r0 = 0;
        } else {
            var_r0 = 1;
        }
        if (var_r0 != 0) {
            ftZelda_80139FE8(fighterObj);
            return;
        }
    }
    if (func_80081298(fighterObj) == 0) {
        if ((collData->x134_envFlags & 0x6000) != 0) {
            f32 angle1 = lbvector_AngleXY(&collData->x190_vec, &fighter->x80_self_vel);
            if (angle1 > (lbl_804D9BB8 * (lbl_804D9BBC + attributes->x60))) {
                ftZelda_8013A764(fighterObj);
            }
        }
        if ((collData->x134_envFlags & 0x3F) != 0) {
            f32 angle2 = lbvector_AngleXY(&collData->x168_vec, &fighter->x80_self_vel);
            if (angle2 > (lbl_804D9BB8 * (lbl_804D9BBC + attributes->x60))) {
                ftZelda_8013A764(fighterObj);
            }
        }
        if ((collData->x134_envFlags & 0xFC0) != 0) {
            f32 angle3 = lbvector_AngleXY(&collData->x17C_vec, &fighter->x80_self_vel);
            if (angle3 > (lbl_804D9BB8 * (lbl_804D9BBC + attributes->x60))) {
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
// void ftZelda_8013A244(HSD_GObj* arg0);                      /* extern */
// s32 func_8009A134(HSD_GObj* arg0);                       /* extern */
// extern f32 lbl_804D9BA4; // 0
// extern f32 lbl_804D9BA8; // 1.0
// extern f64 lbl_804D9BC0; // .5
// extern f64 lbl_804D9BC8; // 3.0
// extern f32 lbl_804D9BD0; // 1.5707963705062866
// extern f32 lbl_804D9BD4; // 35.0
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
        _half = lbl_804D9BC0;
        _three = lbl_804D9BC8;
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        y=(float)(var_f4*guess);
        temp_f5 = y;
    }
    
    temp_f0 = lbl_804D9BA8;
    var_f31 = temp_f5;
    if (temp_f5 > temp_f0) {
        var_f31 = temp_f0;
    }
    if (!(var_f31 < attributes->x50)) {
        groundVector = &collData->x154_groundNormal;
        inputVector.x = fighter->input.x620_lstick_x;
        inputVector.y = fighter->input.x624_lstick_y;
        inputVector.z = lbl_804D9BA4;
        if (!(lbvector_AngleXY(groundVector, (Point3d* ) &inputVector.x) < lbl_804D9BD0)) {
            if (func_8009A134(fighterObj) == 0) {
                func_8007D9FC(fighter);
                
                temp_f5 = func_someCalcAngle_80022C30(fighter->input.x624_lstick_y, fighter->input.x620_lstick_x * fighter->x2C_facing_direction);
                
                fighter->x2344_f32 = inputVector.x;
                fighter->x2348_stateVar3_f32 = inputVector.y;
                temp_f6 = ((attributes->x54 * var_f31) + attributes->x58) * cosf(temp_f5);
                fighter->xEC_ground_vel = fighter->x2C_facing_direction * temp_f6;
                
                Fighter_ActionStateChange_800693AC(fighterObj, 0x15E, 0, NULL, lbl_804D9BD4, lbl_804D9BA8, lbl_804D9BA4);
                func_8006EBA4(fighterObj);
                ftAnim_SetAnimRate(fighterObj, lbl_804D9BA4);
                
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
// https://decomp.me/scratch/3mJb0
extern f32 lbl_804D9BD8;
void ftZelda_8013A244(HSD_GObj* fighterObj) {
    Fighter* fighter; // r30
    ftZeldaAttributes* attributes; // r31
    volatile float y;
    f32 unused[6];
    f32 temp_f1;
    f32 temp_f2;
    f32 var_f4;
    f32 var_f5;
    f32 var_f30;
    f32 var_f31;
    f32 temp_f0;
    f64 _half=.5;
    f64 _three=3.0;
    
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
    if (var_f4 > 0.0f) {
        f64 guess = __frsqrte(var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        guess = _half*guess*(_three - guess*guess*var_f4);
        y=(float)(var_f4*guess);
        var_f5 = y;
    }
    
    temp_f0 = lbl_804D9BA8;
    var_f31 = var_f5;
    if (var_f5 > temp_f0) {
        var_f31 = temp_f0;
    }
    if (var_f31 > attributes->x50) {
        temp_f1 = fighter->input.x620_lstick_x;
        if (temp_f1 < lbl_804D9BA4) {
            temp_f1 = -temp_f1;
        }
        if (temp_f1 > lbl_804D9BD8) {
            func_8007D9FC(fighter);
        }
        var_f30 = func_someCalcAngle_80022C30(fighter->input.x624_lstick_y, fighter->input.x620_lstick_x * fighter->x2C_facing_direction);
        fighter->x2344_f32 = fighter->input.x620_lstick_x;
        fighter->x2348_stateVar3_f32 = fighter->input.x624_lstick_y;
    } else {
        func_8007DA24(fighter);
        var_f30 = lbl_804D9BD0;
        fighter->x2344_f32 = lbl_804D9BA4; // 0
        temp_f0 = lbl_804D9BA8; // 1.0
        var_f31 = temp_f0;
        fighter->x2348_stateVar3_f32 = temp_f0;
    }
    fighter->x80_self_vel.x = fighter->x2C_facing_direction * (((attributes->x54 * var_f31) + attributes->x58) * cosf(var_f30));
    fighter->x80_self_vel.y = ((attributes->x54 * var_f31) + attributes->x58) * sinf(var_f30);
    
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, NULL, lbl_804D9BD4, lbl_804D9BA8, lbl_804D9BA4);
    func_8006EBA4(fighterObj);
    ftAnim_SetAnimRate(fighterObj, lbl_804D9BA4);
    
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


// 8013A50C - 8013A588
// https://decomp.me/scratch/9VS7Q
extern f32 lbl_804D9BDC;
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
    fighter->x80_self_vel.y = temp_f1 - (temp_f1 / lbl_804D9BDC);
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
    
    if (fighter->x2C_facing_direction < lbl_804D9BA4) {
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
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0x0C4C508A, NULL, fighter->x894_currentAnimFrame, lbl_804D9BA8, lbl_804D9BA4);
}

// 8013A6A8 - 8013A764 (0xBC bytes)
// https://decomp.me/scratch/rs281
void ftZelda_8013A6A8(HSD_GObj* fighterObj) {
    f32 temp_f0;
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2;
    Vec unused;

    temp_f1 = lbl_804D9BA4;
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15F, 0, NULL, temp_f1, lbl_804D9BA8, temp_f1);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    temp_f0 = lbl_804D9BA4;
    fighter2->x80_self_vel.y = temp_f0;
    fighter2->x80_self_vel.x = temp_f0;
    fighter2->xEC_ground_vel = temp_f0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fighter->xEC_ground_vel = (f32) (fighter->x2358_stateVar7 * attributes->x64);
}

// 8013A764 - 8013A830 (0xCC bytes)
// https://decomp.me/scratch/xHOLa
void ftZelda_8013A764(HSD_GObj* fighterObj) {
    f32 temp_f0;
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r30
    Fighter* fighter2; // r5
    f32 unused[3];

    temp_f1 = lbl_804D9BA4;
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0, NULL, temp_f1, lbl_804D9BA8, temp_f1);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    fighter2->x2350_stateVar5_f32 = (f32) fighter2->x80_self_vel.x;
    fighter2->x2354_stateVar6 = (f32) fighter2->x80_self_vel.y;
    fighter2->x2358_stateVar7 = (f32) fighter2->xEC_ground_vel;
    temp_f0 = lbl_804D9BA4;
    fighter2->x80_self_vel.y = temp_f0;
    fighter2->x80_self_vel.x = temp_f0;
    fighter2->xEC_ground_vel = temp_f0;
    fighter2->x221E_flag.bits.b0 = 0;
    fighter2->cb.x21BC_callback_Accessory4 = &ftZelda_8013979C;
    fighter->x80_self_vel.x = (f32) (fighter->x2350_stateVar5_f32 * attributes->x64);
    fighter->x80_self_vel.y = (f32) (fighter->x2354_stateVar6 * attributes->x64);
}

// 8013A830 - 8013A8AC (0x7C bytes)
// https://decomp.me/scratch/6v90P
void lbl_8013A830(HSD_GObj* fighterObj) {
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
void lbl_8013A8AC(HSD_GObj* fighterObj) {
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

    temp_f1 = lbl_804D9BE0;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0, NULL, temp_f1, lbl_804D9BE4, temp_f1);
    func_8006EBA4(fighterObj);
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2200_ftcmd_var0 = 0;
    fighter2->x2340_stateVar1 = attributes->x4;
    fighter->cb.x21BC_callback_Accessory4 = &lbl_8013A830;
}


// ------------------
// Start of new file?
// ------------------


// 8013A9A4 - 8013AA38 (0x94 bytes)
// https://decomp.me/scratch/DgO7D
// extern void lbl_8013A8AC();
// extern f32 lbl_804D9BE0;
// extern f32 lbl_804D9BE4;
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
    fighter->cb.x21BC_callback_Accessory4 = &lbl_8013A8AC;
}

// 8013AA38 - 8013AACC (0x94 bytes)
// https://decomp.me/scratch/XcH4E
void lbl_8013ADB0(HSD_GObj* fighter_gobj);
void ftZelda_8013AA38(HSD_GObj* fighterObj) {
    Fighter* fighter;
    s32 attributes;
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = ((u32)fighter->x2D4_specialAttributes);
    
    if ((u32) fighter->x2200_ftcmd_var0 == 1) {
        fighter->x2200_ftcmd_var0 = 2;
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &lbl_8013ADB0);
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
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &lbl_8013ADB0);
    }
    if ((u32) fighter->x2200_ftcmd_var0 == 0U) {
        fighter->x2218_flag.bits.b3 = 0; //(u8) (fighter->unk2218 & ~0x10);
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
// https://decomp.me/scratch/9CdyE
void ftZelda_8013AC88(HSD_GObj* fighterObj) {
    s32 attributes;
    Fighter* fighter;
    Fighter* fighter2;
    s32 unused[5];

    fighter = fighterObj->user_data;
    
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x156, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BE4, lbl_804D9BE0);
    fighter2 = fighterObj->user_data;
    attributes = ((u32)fighter2->x2D4_specialAttributes);
    if ((u32) fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &lbl_8013ADB0);
    }
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013A8AC;
}

// 8013AD1C - 8013ADB0 (0x94 bytes)
// https://decomp.me/scratch/e5IGN
void ftZelda_8013AD1C(HSD_GObj* fighterObj) {
    s32 attributes;
    Fighter* fighter;
    Fighter* fighter2;
    s32 unused[5];

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x155, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BE4, lbl_804D9BE0);
    fighter2 = fighterObj->user_data;
    attributes = ((u32)fighter2->x2D4_specialAttributes);
    if ((u32) fighter2->x2200_ftcmd_var0 == 2U) {
        ftColl_CreateReflectHit(fighterObj, attributes + 0x84, &lbl_8013ADB0);
    }
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013A830;
}

void lbl_8013ADB0(HSD_GObj* fighterObj) {}

// 8013ADB4 - 8013AE30 (0x7C bytes)
// https://decomp.me/scratch/LbMVE
void lbl_8013ADB4(HSD_GObj* fighterObj) {
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
void lbl_8013AE30(HSD_GObj* fighterObj) {
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

// 8013AEAC - 8013AEE0 (0x34 bytes)
// https://decomp.me/scratch/iINH1
void func_80114758(HSD_GObj*);                      /* extern */
void lbl_8013AEAC(HSD_GObj* fighterObj) {
    Fighter* fighter;
    fighter = fighterObj->user_data;
    fighter->cb.x21BC_callback_Accessory4 = 0;
    func_8007EFC8(fighterObj, func_80114758);
}








// 8013AEE0 - 8013AFA4 (0xC4 bytes)
// https://decomp.me/scratch/Lw6fO
extern f32 lbl_804D9BE8; // 0.4000000059604645
extern f32 lbl_804D9BEC; // 0.003000000026077032
extern f32 lbl_804D9BF0; // 1.0471975803375244
extern f32 lbl_804D9BF4; // 0
extern f32 lbl_804D9BF8; // 1.0
void ftZelda_SpecialLw_StartAction(HSD_GObj* fighterObj) {
    Point3d sp20;
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r3
    f32 unused[5];

    temp_f1 = lbl_804D9BF4;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0, NULL, temp_f1, lbl_804D9BF8, temp_f1);
    func_8006EBA4(fighterObj);
    
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.x = (f32) (fighter->x80_self_vel.x / attributes->x70);
    fighter->x80_self_vel.y = (f32) (fighter->x80_self_vel.y / attributes->x74);
    fighter->xEC_ground_vel = (f32) (fighter->xEC_ground_vel / attributes->x70);
    
    func_8000B1CC(fighter->x5E8_fighterBones[0].x0_jobj, NULL, &sp20);
    func_800119DC(&sp20, 0x78, lbl_804D9BE8, lbl_804D9BEC, lbl_804D9BF0);
    
    fighter->cb.x21BC_callback_Accessory4 = &lbl_8013ADB4;
}

// 8013AFA4 - 8013B068 (0xC4 bytes)
// https://decomp.me/scratch/8W7ZF
void ftZelda_SpecialAirLw_StartAction(HSD_GObj* fighterObj) {
    Point3d sp20;
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes; // r3
    f32 unused[5];

    temp_f1 = lbl_804D9BF4;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0, NULL, temp_f1, lbl_804D9BF8, temp_f1);
    func_8006EBA4(fighterObj);
    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.x = (f32) (fighter->x80_self_vel.x / attributes->x70);
    fighter->x80_self_vel.y = (f32) (fighter->x80_self_vel.y / attributes->x74);
    fighter->xEC_ground_vel = (f32) (fighter->xEC_ground_vel / attributes->x70);
    
    func_8000B1CC(fighter->x5E8_fighterBones[0].x0_jobj, NULL, &sp20);
    func_800119DC(&sp20, 0x78, lbl_804D9BE8, lbl_804D9BEC, lbl_804D9BF0);
    fighter->cb.x21BC_callback_Accessory4 = &lbl_8013ADB4;
}

// 8013B068 - 8013B0A8 (0x40 bytes)
// https://decomp.me/scratch/DrRr5
extern void lbl_8013AEAC();
void ftZelda_8013B068(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter->cb.x21BC_callback_Accessory4 = &lbl_8013AEAC;
    }
}

// 8013B0A8 - 8013B0E8 (0x40 bytes)
// https://decomp.me/scratch/DrRr5
void ftZelda_8013B0A8(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter->cb.x21BC_callback_Accessory4 = &lbl_8013AEAC;
    }
}

void ftZelda_8013B0E8(HSD_GObj* arg0) {}
void ftZelda_8013B0EC(HSD_GObj* arg0) {}

// 8013B0F0 - 8013B110 (0x20 bytes)
void ftZelda_8013B0F0(HSD_GObj* arg0) {
    func_80084F3C(arg0);
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
void ftZelda_8013B1CC(HSD_GObj*);                      /* extern */
void ftZelda_8013B154(HSD_GObj* fighterObj) {
    if (func_80082708(fighterObj) == 0) {
        ftZelda_8013B1CC(fighterObj);
    }
}

// 8013B190 - 8013B1CC (0x3C bytes)
// https://decomp.me/scratch/8ceOO
void ftZelda_8013B238(HSD_GObj*);                      /* extern */
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
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BF8, lbl_804D9BF4);
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013ADB4;
}

// 8013B238 - 8013B2A4 (0x6C bytes)
void ftZelda_8013B238(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BF8, lbl_804D9BF4);
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013ADB4;
}

// 8013B2A4 - 8013B2E0 (0x3C bytes)
void ftZelda_8013B2A4(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_8008A2BC(arg0);
    }
}

// 8013B2E0 - 8013B31C (0x3C bytes)
void ftZelda_8013B2E0(HSD_GObj* arg0) {
    if (ftAnim_IsFramesRemaining(arg0) == 0) {
        func_800CC730(arg0);
    }
}

void ftZelda_8013B31C(HSD_GObj* arg0) {}
void ftZelda_8013B320(HSD_GObj* arg0) {}

// 8013B324 - 8013B344 (0x20 bytes)
void ftZelda_8013B324(HSD_GObj* arg0) {
    func_80084F3C(arg0);
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
void ftZelda_8013B400(HSD_GObj*);                      /* extern */
void ftZelda_8013B388(HSD_GObj* fighterObj) {
    if (func_80082708(fighterObj) == 0) {
        ftZelda_8013B400(fighterObj);
    }
}

// 8013B3C4 - 8013B400 (0x3C bytes)
// https://decomp.me/scratch/t8hrY
void ftZelda_8013B46C(HSD_GObj*);                      /* extern */
void ftZelda_8013B3C4(HSD_GObj* fighterObj) {
    if (func_80081D0C(fighterObj) != 0) {
        ftZelda_8013B46C(fighterObj);
    }
}

// 8013B400 - 8013B46C (0x6C bytes)
// https://decomp.me/scratch/EZlpO
void lbl_8013AE30(HSD_GObj* fighter);               /* extern */
extern f32 lbl_804D9BF4;
extern f32 lbl_804D9BF8;
void ftZelda_8013B400(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D5D4(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x166, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BF8, lbl_804D9BF4);
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013AE30;
}

// 8013B46C - 8013B4D8 (0x6C bytes)
// https://decomp.me/scratch/EZlpO
void ftZelda_8013B46C(HSD_GObj* fighterObj) {
    Fighter* fighter;

    fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0x0C4C508E, NULL, fighter->x894_currentAnimFrame, lbl_804D9BF8, lbl_804D9BF4);
    fighter->cb.x21BC_callback_Accessory4 = lbl_8013AE30;
}

// 8013B4D8 - 8013B540 (0x68 bytes)
// https://decomp.me/scratch/wpEbJ
extern void lbl_8013AE30();
extern f32 lbl_804D9BF4;
extern f32 lbl_804D9BF8;

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
    Fighter_ActionStateChange_800693AC(fighterObj, var_r4, 0, NULL, attributes->x80, lbl_804D9BF8, lbl_804D9BF4);
    fighter->cb.x21BC_callback_Accessory4 = &lbl_8013AE30;
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

// 8013B638 - 8013B6D8 (0xA0 bytes)
// https://decomp.me/scratch/QnXK1
extern f32 lbl_804D9C00;
extern f32 lbl_804D9C04;
void ftZelda_SpecialS_StartAction(HSD_GObj* fighterObj) {
    f32 temp_f1;
    Fighter* fighter; // r31
    ftZeldaAttributes* attributes;
    Fighter* fighter2;
    s32 unused[7];

    temp_f1 = lbl_804D9C00;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x157, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2340_stateVar1 = (s32) attributes->x10;
    fighter2->x2344_stateVar2_s32 = (s32) attributes->x14;
    fighter2->x2348_stateVar3_s32 = (s32) attributes->x18;
    fighter2->sa.zelda.x222C = 0;
    fighter2->x234C_stateVar4_s32 = (s32) attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighterObj);
}

// 8013B6D8 - 8013B780 (0xA8 bytes)
// https://decomp.me/scratch/F0dW9
void ftZelda_SpecialAirS_StartAction(HSD_GObj* fighterObj) {
    f32 temp_f1;
    Fighter* fighter;
    ftZeldaAttributes* attributes;
    Fighter* fighter2;
    s32 unused[7];

    temp_f1 = lbl_804D9C00;
    fighter = fighterObj->user_data;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x15A, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
    fighter->x220C_ftcmd_var3 = 0;
    fighter->x2208_ftcmd_var2 = 0;
    fighter->x2204_ftcmd_var1 = 0;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x80_self_vel.y = (f32) lbl_804D9C00;
    fighter2 = fighterObj->user_data;
    attributes = fighter2->x2D4_specialAttributes;
    fighter2->x2340_stateVar1 = (s32) attributes->x10;
    fighter2->x2344_stateVar2_s32 = (s32) attributes->x14;
    fighter2->x2348_stateVar3_s32 = (s32) attributes->x18;
    fighter2->sa.zelda.x222C = 0;
    fighter2->x234C_stateVar4_s32 = (s32) attributes->x1C;
    fighter2->cb.x21E4_callback_OnDeath2 = 0;
    fighter2->cb.x21DC_callback_OnTakeDamage = 0;
    func_8006EBA4(fighterObj);
}

// 8013B780 - 8013B89C (0x11C bytes)
// https://decomp.me/scratch/g2bK5
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
// extern void ftZelda_801393AC();
// extern f32 lbl_804D9C00;
// extern f32 lbl_804D9C04;
void ftZelda_8013B780(HSD_GObj* fighterObj) {
    Point3d sp24;
    f32 temp_f1;
    f32 temp_f2;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    f32 unused[6];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);
        sp24.z = lbl_804D9C00;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fighter->x2C_facing_direction) + sp24.x;
        sp24.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp24, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        temp_f1 = lbl_804D9C00;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x158, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
        fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    }
}

// 8013B89C - 8013BA04 (0x168 bytes)
// https://decomp.me/scratch/uGOsz
// extern void ftZelda_801393AC();
// extern f32 lbl_804D9C00;
// extern f32 lbl_804D9C04;
void ftZelda_8013B89C(HSD_GObj* fighterObj) {
    Point3d sp20;
    ftZeldaAttributes* attributes;
    Fighter* fighter; // r30
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r3;
    u32 temp_r3_u32;
    f32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if ((fighter->x2200_ftcmd_var0 == 1U) && (fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);
        sp20.z = lbl_804D9C00;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fighter->x2C_facing_direction) + sp20.x;
        sp20.y += attributes->x24;
        temp_r3_u32 = func_802C3BAC(fighterObj, &sp20, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3_u32;
        if (temp_r3_u32 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    temp_r3 = fighter->x2340_stateVar1;
    if (temp_r3 != 0) {
        fighter->x2340_stateVar1 = (s32) (temp_r3 - 1);
    }
    temp_r3 = fighter->x2344_stateVar2_s32;
    if (temp_r3 != 0) {
        fighter->x2344_stateVar2_s32 = (s32) (temp_r3 - 1);
    }
    temp_r3_u32 = fighter->sa.zelda.x222C;
    if (temp_r3_u32 == 0) {
        if ((fighter->x2340_stateVar1 <= 0) && (fighter->x2344_stateVar2_s32 <= 0)) {
            temp_f1 = lbl_804D9C00;
            Fighter_ActionStateChange_800693AC(fighterObj, 0x159, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
        }
    } else {
        temp_r3 = func_802C3AF0(fighter->sa.zelda.x222C);
        if (temp_r3 != (u32) fighterObj) {
            fighter->sa.zelda.x222C = 0;
        }
    }
}

// 8013BA04 - 8013BA8C (0x88 bytes)
// https://decomp.me/scratch/TSoo9
//extern f32 lbl_804D9C00;
void ftZelda_8013BA04(HSD_GObj* fighterObj) {
    Fighter* fighter;
    ftZeldaAttributes* attributes;

    fighter = getFighter(fighterObj);

    func_8007592C(fighter, 0, lbl_804D9C00);
    
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        fighter = getFighter(fighterObj);
        attributes = getFtSpecialAttrs(fighter);
        
        fighter->x2340_stateVar1 = (s32) attributes->x10;
        fighter->x2344_stateVar2_s32 = (s32) attributes->x14;
        fighter->x2348_stateVar3_s32 = (s32) attributes->x18;
        fighter->sa.zelda.x222C = 0;
        fighter->x234C_stateVar4_s32 = (s32) attributes->x1C;
        fighter->cb.x21E4_callback_OnDeath2 = 0;
        fighter->cb.x21DC_callback_OnTakeDamage = 0;
        
        func_8008A2BC(fighterObj);
    }
}

// 8013BA8C - 8013BBA8 (0x11C bytes)
// https://decomp.me/scratch/9hYY3
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
// extern void ftZelda_801393AC();
// extern f32 lbl_804D9C00;
// extern f32 lbl_804D9C04;
void ftZelda_8013BA8C(HSD_GObj* fighterObj) {
    Point3d sp24;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_cr0_eq;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp24);
        sp24.z = lbl_804D9C00;
        temp_f2 = attributes->x20;
        sp24.x = (temp_f2 * fighter->x2C_facing_direction) + sp24.x;
        sp24.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp24, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    if (ftAnim_IsFramesRemaining(fighterObj) == 0) {
        temp_f1 = lbl_804D9C00;
        Fighter_ActionStateChange_800693AC(fighterObj, 0x15B, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
        fighter->x1968_jumpsUsed = fighter->x110_attr.x168_MaxJumps;
    }
}

// 8013BBA8 - 8013BD10 (0x168 bytes)
// https://decomp.me/scratch/llKUS
// u32 func_802C3AF0();                                /* extern */
// u32 func_802C3BAC(HSD_GObj*, Point3d*, f32, f32);   /* extern */
// extern void ftZelda_801393AC();
// extern f32 lbl_804D9C00;
// extern f32 lbl_804D9C04;
void ftZelda_8013BBA8(HSD_GObj* fighterObj) {
    Point3d sp20;
    f32 temp_f1;
    f32 temp_f2;
    s32 temp_r3_s32;
    u32 temp_r3;
    ftZeldaAttributes* attributes; // r31
    Fighter* fighter; // r30
    s32 unused[5];

    fighter = fighterObj->user_data;
    attributes = fighter->x2D4_specialAttributes;
    
    if (((u32) fighter->x2200_ftcmd_var0 == 1U) && ((u32) fighter->sa.zelda.x222C == 0U)) {
        fighter->x2200_ftcmd_var0 = 0U;
        func_8000B1CC(fighter->x5E8_fighterBones[0x59].x0_jobj, NULL, &sp20);
        sp20.z = lbl_804D9C00;
        temp_f2 = attributes->x20;
        sp20.x = (temp_f2 * fighter->x2C_facing_direction) + sp20.x;
        sp20.y += attributes->x24;
        temp_r3 = func_802C3BAC(fighterObj, &sp20, fighter->x2C_facing_direction, temp_f2);
        fighter->sa.zelda.x222C = temp_r3;
        if (temp_r3 != 0) {
            fighter->cb.x21E4_callback_OnDeath2 = &ftZelda_801393AC;
            fighter->cb.x21DC_callback_OnTakeDamage = &ftZelda_801393AC;
        }
        ef_Spawn(0x4FB, fighterObj, fighter->x5E8_fighterBones[0x4C].x0_jobj);
    }
    temp_r3_s32 = fighter->x2340_stateVar1;
    if (temp_r3_s32 != 0) {
        fighter->x2340_stateVar1 = (s32) (temp_r3_s32 - 1);
    }
    temp_r3_s32 = fighter->x2344_stateVar2_s32;
    if (temp_r3_s32 != 0) {
        fighter->x2344_stateVar2_s32 = (s32) (temp_r3_s32 - 1);
    }
    if ((u32) fighter->sa.zelda.x222C == 0U) {
        if (((s32) fighter->x2340_stateVar1 <= 0) && ((s32) fighter->x2344_stateVar2_s32 <= 0)) {
            temp_f1 = lbl_804D9C00;
            Fighter_ActionStateChange_800693AC(fighterObj, 0x15C, 0, NULL, temp_f1, lbl_804D9C04, temp_f1);
        }
    } else {
        temp_r3 = func_802C3AF0(fighter->sa.zelda.x222C);
        if (temp_r3 != (u32) fighterObj) {
            fighter->sa.zelda.x222C = 0;
        }
    }
}

// 8013BD10 -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 

//  -  ( bytes)
// 