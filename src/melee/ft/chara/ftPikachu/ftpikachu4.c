#include "ftpikachu.h"

#define HALF_PI 1.5707963705062866f
#define DEG_TO_RAD 0.017453292f
#define MAX_STICK_MAG 0.999f

// points velocity toward facing direction
void ftPikachu_UpdateVel_80125D80(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    fighter->xEC_ground_vel = fighter->x2C_facing_direction * fabs_inline(fighter->xEC_ground_vel);
    fighter->x80_self_vel.x = fighter->x2C_facing_direction * fabs_inline(fighter->x80_self_vel.x);
    fighter->x234C_pos.y = fighter->x2C_facing_direction * fabs_inline(fighter->x234C_pos.y);
}

void ftPikachu_SpecialHi_StartAction(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = pika_attr->x5C;
    fighter->x2348_stateVar3 = 0;
    fighter->x2358_stateVar7_s32 = 0;
    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_SpecialHiAir_StartAction(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x2200_ftcmd_var0 = 0;
    fighter->x2340_stateVar1 = pika_attr->x5C;
    fighter->x2348_stateVar3 = 0;
    fighter->x2358_stateVar7_s32 = 0;
    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0, 0, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
}

void ftPikachu_80125ED8(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftPikachu_80126C0C(fighterObj);
    }
}

void ftPikachu_80125F14(HSD_GObj* fighterObj) {
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        ftPikachu_80126E1C(fighterObj);
    }
}

void ftPikachu_Stub_80125F50() {}

void ftPikachu_Stub_80125F54() {}

void ftPikachu_80125F58(HSD_GObj* fighterObj) {
    func_80084F3C(fighterObj);
}

void ftPikachu_80125F78(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    struct attr* attr = &fighter->x110_attr;
    if (fighter->x2340_stateVar1) {
        fighter->x2340_stateVar1--;
    } else {
        func_8007D494(fighter, pika_attr->x64, attr->x170_TerminalVelocity);
    }
    func_8007CF58(fighter);
}

void ftPikachu_80125FD8(HSD_GObj* fighterObj) {
    if (!func_80082708(fighterObj)) {
        ftPikachu_ActionChange_80126084(fighterObj);
    }
} 

void ftPikachu_80126014(HSD_GObj* fighterObj) {
    s32 unused;
    Fighter* fighter = fighterObj->user_data;

    if (EnvColl_CheckGroundAndLedge(fighterObj, fighter->x2C_facing_direction < 0.0f ? -1 : 1)) {
        ftPikachu_ActionChange_801260E4(fighterObj);
    } else  {
        if (func_80081298(fighterObj) == 0) { return; };
    }
}

void ftPikachu_ActionChange_80126084(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x164, 0xC4C5084, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChange_801260E4(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D7FC(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x161, 0xC4C5084, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_80126144(HSD_GObj* fighterObj) {
    Vec vec;
    Vec vec2;
    s32 unused[5];

    Fighter* fighter = fighterObj->user_data;
    
    fighter->x2344_stateVar2_s32--;
    if (fighter->x2344_stateVar2_s32 <= 0) { 
        ftPikachu_ActionChangeUpdateVel_801274AC(fighterObj);
        fighter = fighterObj->user_data;
        if (fighter->x4_fighterKind != FTKIND_PICHU) {
            func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj, 0, &vec);
            ef_Spawn(0x3F4, fighterObj, &vec);
            fighter->x2219_flag.bits.b0 = 1;
            fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    } else {
        fighter = fighterObj->user_data;
        if (fighter->x4_fighterKind != FTKIND_PICHU) { 
            f32 tempf;
            func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj, 0, &vec2);
            tempf = HSD_Randf();
            vec2.x += (6.0f * tempf) - 3.0f; 
            tempf = HSD_Randf();
            vec2.y += (6.0f * tempf) - 3.0f;
            ef_Spawn(0x3F4, fighterObj, &vec2);  
            fighter->x2219_flag.bits.b0 = 1;
            fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    }
}

void ftPikachu_801262B4(HSD_GObj* fighterObj) {
    Vec vec;
    Vec vec2;
    s32 unused[5];

    Fighter* fighter = fighterObj->user_data;
    
    fighter->x2344_stateVar2_s32--;
    if (fighter->x2344_stateVar2_s32 <= 0) { 
        ftPikachu_ActionChangeUpdateVel_80127534(fighterObj);
        fighter = fighterObj->user_data;
        if (fighter->x4_fighterKind != FTKIND_PICHU) {
            func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj, 0, &vec);
            ef_Spawn(0x3F4, fighterObj, &vec);
            fighter->x2219_flag.bits.b0 = 1;
            fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    } else {
        fighter = fighterObj->user_data;
        if (fighter->x4_fighterKind != FTKIND_PICHU) { 
            f32 tempf;
            func_8000B1CC(fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj, 0, &vec2);
            tempf = HSD_Randf();
            vec2.x += (10.0f * tempf) - 5.0f; 
            tempf = HSD_Randf();
            vec2.y += (10.0f * tempf) - 5.0f;
            ef_Spawn(0x3F4, fighterObj, &vec2);  
            fighter->x2219_flag.bits.b0 = 1;
            fighter->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            fighter->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        }
    }
}

void ftPikachu_Stub_80126424() {}

void ftPikachu_Stub_80126428() {}

void ftPikachu_8012642C(HSD_GObj* fighterObj) {
    Vec scale;
    Vec3 velocity_vec;
    s32 unused;

    HSD_JObj* jobj;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    
    f32 half_pi = HALF_PI;
    f32 tempf = (fighter->x2C_facing_direction * func_someCalcAngle_80022C30(fighter->x80_self_vel.x, fighter->x80_self_vel.y)) 
        + (pika_attr->x78 - half_pi);
    
    func_8007592C(fighter, func_8007500C(fighter, 2), tempf);
    scale.x = pika_attr->x7C_scale.x;
    scale.y = pika_attr->x7C_scale.y;
    scale.z = pika_attr->x7C_scale.z;
    jobj = fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj;
    HSD_JObjSetScale(jobj, &scale); 
    
    velocity_vec = fighter->x80_self_vel;
    func_8007E2FC(fighterObj);
    fighter->x80_self_vel = velocity_vec;
 
    
    fighter->x6D8.x = 
    fighter->x6D8.y = 
    fighter->x6D8.z = 
    fighter->x6C0.x = 
    fighter->x6C0.y = 
    fighter->x6C0.z = 
    fighter->x6BC_inputStickangle = 
    fighter->x6A4_transNOffset.x = 
    fighter->x6A4_transNOffset.y = 
    fighter->x6A4_transNOffset.z =  
    fighter->x68C_transNPos.x = 
    fighter->x68C_transNPos.y = 
    fighter->x68C_transNPos.z = 0.0f;
}

void ftPikachu_801265D4(HSD_GObj* fighterObj) {
    func_8007CB74(fighterObj);
}

#pragma dont_inline on
void ftPikachu_801265F4(HSD_GObj* fighterObj) {
    ftPikachu_8012642C(fighterObj);
}
#pragma dont_inline off

void ftPikachu_80126614(HSD_GObj* fighterObj) {
    Vec scale;
    s32 unused[7];

    Fighter *fighter2;

    HSD_JObj *jobj;

    Fighter* fighter = fighterObj->user_data;
    CollData* collData = &fighter->x6F0_collData;

    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    if (!func_80082888(fighterObj, &pika_attr->xE0_array_start)) {
        if ((collData->x134_envFlags & 0x3F) || (collData->x134_envFlags & 0xFC0)) {
            func_8007D60C(fighter);
            ftPikachu_ActionChangeUpdateVel_80127534(fighterObj);
            return;
        }
        ftPikachu_ActionChange_80126A2C(fighterObj);
        return;
    }

    {  /// could be an inline?
        CollData* collData;
        fighter2 = fighterObj->user_data;
        collData = &fighter2->x6F0_collData;
        pika_attr = fighter2->x2D4_specialAttributes;
        if (collData->x134_envFlags & 0x18000){
            f32 angle = func_someCalcAngle_80022C30(collData->x154_groundNormal.x, collData->x154_groundNormal.y);
            f32 angle2 = (fighter2->x2C_facing_direction * angle) + pika_attr->x68;
            func_8007592C(fighter2, func_8007500C(fighter2, 2), angle2);
        }
        scale.x = pika_attr->x6C_scale.x;
        scale.y = pika_attr->x6C_scale.y;
        scale.z = pika_attr->x6C_scale.z;
        jobj = fighter2->x5E8_fighterBones[func_8007500C(fighter2, 2)].x0_jobj;
        HSD_JObjSetScale(jobj, &scale);
    }

    if ((collData->x134_envFlags & 0x3F) || (collData->x134_envFlags & 0xFC0)) {
        ftPikachu_ActionChangeUpdateVel_801274AC(fighterObj);
    }


}

BOOL ftPikachu_GetBool(HSD_GObj* fighterObj) {
    Fighter* fighter2 = fighterObj->user_data;
    ftPikachuAttributes*pika_attr2 = fighter2->x2D4_specialAttributes;
    if (fighter2->x2358_stateVar7_s32 >= pika_attr2->x88) {
        return 1;
    } else if (func_8009A134(fighterObj)) {
        return 0;
    } else {
        return 1;
    }
}

void ftPikachu_801267C8(HSD_GObj* fighterObj) {
    s32 unused[5];
    BOOL bool0;
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    CollData* collData = &fighter->x6F0_collData;

    fighter->x2358_stateVar7_s32++;
    if (EnvColl_CheckGroundAndLedge(fighterObj, fighter->x2C_facing_direction < 0.0f ? -1 : 1)) {
        bool0 = ftPikachu_GetBool(fighterObj);


        if (bool0) {
            f32 tempf = lbvector_AngleXY(&collData->x154_groundNormal, &fighter->x80_self_vel);
            if (tempf > (DEG_TO_RAD * (90.0f + pika_attr->xA0))) {
                func_8007D7FC(fighter);
                ftPikachu_ActionChangeUpdateVel_801274AC(fighterObj);
                return; 
            }
            ftPikachu_ActionChange_80126AA4(fighterObj);
            return;
        }
    }

    if (!func_80081298(fighterObj)) {

        if (collData->x134_envFlags & 0x6000) {
            f32 angle = lbvector_AngleXY(&collData->x190_vec, &fighter->x80_self_vel);
            if (angle > (DEG_TO_RAD * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(fighterObj);
            }
        }

        if (collData->x134_envFlags & 0x3F) {
            f32 angle = lbvector_AngleXY(&collData->x168_vec, &fighter->x80_self_vel);
            if (angle > (DEG_TO_RAD * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(fighterObj);
            }
        }

        if (collData->x134_envFlags & 0xFC0) {
            f32 angle = lbvector_AngleXY(&collData->x17C_vec, &fighter->x80_self_vel);
            if (angle > (DEG_TO_RAD * (90.0f + pika_attr->xA0))) {
                ftPikachu_ActionChangeUpdateVel_80127534(fighterObj);
            }
        }
        
    }
}

#pragma dont_inline on
void ftPikachu_ActionChange_80126A2C(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0xC4C508A, 0, fighter->x894_currentAnimFrame, 0.0f, 0.0f);
    fighter->x2223_flag.bits.b4 = 1;
    ftPikachu_8012642C(fighterObj);
}
#pragma dont_inline off

void ftPikachu_ActionChange_80126AA4(HSD_GObj* fighterObj) {
    Vec scale;
    s32 unused[6];
    
    CollData* collData;
    ftPikachuAttributes* pika_attr;
    
    Fighter* fighter;
    Fighter* fighter2;
    
    HSD_JObj *jobj;

    fighter2 = fighterObj->user_data;
    func_8007D7FC(fighter2);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0xC4C508A, 0, fighter2->x894_currentAnimFrame, 0.0f, 0.0f);
    
    fighter = fighterObj->user_data;
    collData = &fighter->x6F0_collData;
    pika_attr = fighter->x2D4_specialAttributes;
    if (fighter->x6F0_collData.x134_envFlags & 0x18000) {
        f32 angle = (fighter->x2C_facing_direction * func_someCalcAngle_80022C30(collData->x154_groundNormal.x, collData->x154_groundNormal.y)) + pika_attr->x68;
        func_8007592C(fighter, func_8007500C(fighter, 2), angle);
    }
    
    scale.x = pika_attr->x6C_scale.x;
    scale.y = pika_attr->x6C_scale.y;
    scale.z = pika_attr->x6C_scale.z;
    jobj = fighter->x5E8_fighterBones[func_8007500C(fighter, 2)].x0_jobj;
    HSD_JObjSetScale(jobj, &scale);
}

inline float get_max_and_fill_stack() {
    float stack[9];
    stack[0] = MAX_STICK_MAG;
    return MAX_STICK_MAG;
}

// grounded up b zip
void ftPikachu_80126C0C(HSD_GObj* fighterObj) { 
    Fighter* fighter = fighterObj->user_data;

    CollData* collData = &fighter->x6F0_collData;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    // distance formula
    f32 stick_mag = sqrtf((fighter->input.x620_lstick_x * fighter->input.x620_lstick_x) + (fighter->input.x624_lstick_y * fighter->input.x624_lstick_y));

    // cap stick magnitude to MAX_STICK_MAG
    if (stick_mag > MAX_STICK_MAG) {
        stick_mag = get_max_and_fill_stack();;
    }

    if (!(stick_mag < pika_attr->x8C)) {
        Vec lstick_direction;
    
        lstick_direction.x = fighter->input.x620_lstick_x;
        lstick_direction.y = fighter->input.x624_lstick_y;
        lstick_direction.z = 0.0f;

        // if the angular difference between the ground normal and the stick < 90° and (some check on the fighter)
        if (!(lbvector_AngleXY(&collData->x154_groundNormal, &lstick_direction) < HALF_PI) && (!func_8009A134(fighterObj))) {
            Fighter* fighter2;
            func_8007D9FC(fighter);
            
            // store stick angle to compare during zip2 check
            fighter->x234C_pos.y = lstick_direction.x;
            fighter->x234C_pos.z = lstick_direction.y;

            fighter2 = fighterObj->user_data;

            // set zip duration
            fighter2->x2344_stateVar2_s32 = ((ftPikachuAttributes*)fighter2->x2D4_specialAttributes)->x60;
            
            // lose double jump(s)
            fighter2->x1968_jumpsUsed = fighter2->x110_attr.x168_MaxJumps;

            // set ground velocity to (zip_slope * stick_mag) + zip_intercept
            // and then flip based on facing direction
            fighter->xEC_ground_vel = (pika_attr->x90 * stick_mag) + pika_attr->x94;
            fighter->xEC_ground_vel *= fighter->x2C_facing_direction;

            // if second zip
            if (fighter->x2348_stateVar3_s32) {
                // multiply ground velocity by second_zip_decay
                fighter->xEC_ground_vel *= pika_attr->x98;
                
                Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 2, 0, 12.0f, 1.0f, 0.0f);
                func_8006EBA4(fighterObj);
            }
            Fighter_ActionStateChange_800693AC(fighterObj, 0x162, 0xA, 0, 13.0f, 1.0f, 0.0f);
            func_8006EBA4(fighterObj);
            ftAnim_SetAnimRate(fighterObj, 0.0f); 
            fighter->x2223_flag.bits.b4 = 1;
            fighter->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
            return;
        }
    }
    func_8007D60C(fighter);
    ftPikachu_80126E1C(fighterObj);
}

// aerial up b zip
void ftPikachu_80126E1C(HSD_GObj* fighterObj) {
    f32 temp_f2_2;
    f32 some_angle;
    f32 final_stick_mag;

    Fighter* fighter2;
    Fighter* fighter = fighterObj->user_data;

    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;

    // distance formula
    f32 temp_stick_mag = sqrtf((fighter->input.x620_lstick_x * fighter->input.x620_lstick_x) + (fighter->input.x624_lstick_y * fighter->input.x624_lstick_y));

    final_stick_mag = temp_stick_mag;

    // cap stick magnitude to MAX_STICK_MAG
    if (temp_stick_mag > MAX_STICK_MAG) {
        final_stick_mag = get_max_and_fill_stack();
    }

    if ((final_stick_mag > pika_attr->x8C)) {

        if (fabs_inline(fighter->input.x620_lstick_x) > 0.001f) {
            func_8007D9FC(fighter);
        }

        // zip angle = atan2(stick_y, stick_x * facing_direction)
        some_angle = func_someCalcAngle_80022C30(fighter->input.x624_lstick_y, fighter->input.x620_lstick_x * fighter->x2C_facing_direction);
        
        // store stick angle to compare during zip2 check
        fighter->x234C_pos.y = fighter->input.x620_lstick_x;
        fighter->x234C_pos.z = fighter->input.x624_lstick_y;
    } else {
        // set facing direction if stick x meets a threshold
        func_8007DA24(fighter);

        // use max stick_mag and 90°
        final_stick_mag = MAX_STICK_MAG;
        some_angle = HALF_PI;

        // store inputs as if x=0 and y=max
        fighter->x234C_pos.y = 0.0f;
        fighter->x234C_pos.z = MAX_STICK_MAG;
    }

    fighter2 = fighterObj->user_data;

    // set zip duration
    fighter2->x2344_stateVar2_s32 = ((ftPikachuAttributes*)fighter2->x2D4_specialAttributes)->x60;
    
    // lose double jump(s)
    fighter2->x1968_jumpsUsed = fighter2->x110_attr.x168_MaxJumps;

    // compute velocity as (zip slope * stick_mag) + zip intercept
    // x velocity is the same but flips based on facing direction
    temp_f2_2 = ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) * cosf(some_angle);
    fighter->x80_self_vel.x = fighter->x2C_facing_direction * temp_f2_2;
    fighter->x80_self_vel.y = ((pika_attr->x90 * final_stick_mag) + pika_attr->x94) * sinf(some_angle);


    // if second zip
    if (fighter->x2348_stateVar3_s32) {
        // multiply velocity by second-zip decay
        fighter->x80_self_vel.x *= pika_attr->x98;
        fighter->x80_self_vel.y *= pika_attr->x98;

        Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 2, 0, 12.0f, 1.0f, 0.0f);
        func_8006EBA4(fighterObj);
    }
    Fighter_ActionStateChange_800693AC(fighterObj, 0x165, 0xA, 0, 13.0f, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    ftAnim_SetAnimRate(fighterObj, 0.0f); 
    fighter->x2223_flag.bits.b4 = 1;

    // set velocity to move toward facing direction
    fighter->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
    
}

inline s32 return_and_fill_stack() {
    float stack[1];
    stack[0] = MAX_STICK_MAG;
    return 0;
}

// seems to check whether to perform a second up b zip
s32 ftPikachu_80127064(HSD_GObj* fighterObj) {
    
    Vec vec1;
    Vec vec2;

    Fighter* fighter = fighterObj->user_data;

    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;    

    // distance formula
    f32 stick_mag = sqrtf((fighter->input.x620_lstick_x * fighter->input.x620_lstick_x) + (fighter->input.x624_lstick_y * fighter->input.x624_lstick_y));

    // if stick_mag is less than the threshold, push the max stick magnitude onto the stack and return 0
    if (stick_mag < pika_attr->x8C) {
        return return_and_fill_stack();
    }

    if (!fighter->x2348_stateVar3_s32) {
        f32 tempf;

        // push current stick to temporary vector
        vec1.x = fighter->input.x620_lstick_x;
        vec1.y = fighter->input.x624_lstick_y;
        vec1.z = 0.0f;

        // push stick from zip1 to temporary vector
        vec2.x = fighter->x234C_pos.y;
        vec2.y = fighter->x234C_pos.z;
        vec2.z = 0.0f;
        
        // get the angular difference between them
        tempf = lbvector_AngleXY(&vec2, &vec1);

        // if the angular difference > the minimum difference, return 1
        if (tempf > (DEG_TO_RAD * (pika_attr->xA8))) {
            return 1;
        }
        return 0;
    }
    return 0;
}

void ftPikachu_80127198(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if ((u32) fighter->x2200_ftcmd_var0 == 1U) {
        if (ftPikachu_80127064(fighterObj)) {
            fighter->x2200_ftcmd_var0 = 0;
            fighter->x2348_stateVar3 = 1;
            ftPikachu_80126C0C(fighterObj);
            return;
        }
        fighter->x2200_ftcmd_var0 = 2;
        return;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_8008A2BC(fighterObj);
    }
}

void ftPikachu_80127228(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (fighter->x2200_ftcmd_var0 == 1) {
        if (ftPikachu_80127064(fighterObj)) {
            fighter->x2200_ftcmd_var0 = 0;
            fighter->x2348_stateVar3 = 1;
            ftPikachu_80126E1C(fighterObj);
            return;
        }
        fighter->x2200_ftcmd_var0 = 2;
        return;
    }
    if (!ftAnim_IsFramesRemaining(fighterObj)) {
        func_80096900(fighterObj, 1, 0, 1, pika_attr->xAC, pika_attr->xB0);
    }
}

void ftPikachu_Stub_801272D8() {}

void ftPikachu_Stub_801272DC() {}

void ftPikachu_801272E0(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    if (fighter->x2200_ftcmd_var0) {
        func_80084F3C(fighterObj);
    }
}

void ftPikachu_80127310(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (fighter->x2200_ftcmd_var0) {
        func_8007D4B8(fighter);
        func_8007D440(fighter, pika_attr->x9C * fighter->x110_attr.x17C_AerialDriftMax);
        return;
    }
    fighter->x80_self_vel.y -= (fighter->x80_self_vel.y / 9.0f);
    func_8007CEF4(fighter);
}

void ftPikachu_8012738C(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (!func_80082888(fighterObj, &pika_attr->xE0_array_start)) {
        ftPikachu_ActionChange_8012744C(fighterObj);
    }
}

void ftPikachu_801273D4(HSD_GObj* fighterObj) {
    s32 unused[2];
    Fighter* fighter = fighterObj->user_data;
    ftPikachuAttributes* pika_attr = fighter->x2D4_specialAttributes;
    if (func_8008239C(fighterObj, fighter->x2C_facing_direction, &pika_attr->xE0_array_start)) {
        func_800D5CB0(fighterObj, 0, pika_attr->xB0);
        return;
    }
    if (func_80081298(fighterObj) == 0) { return; };
}

void ftPikachu_ActionChange_8012744C(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    func_8007D60C(fighter);
    Fighter_ActionStateChange_800693AC(fighterObj, 0x166, 0xC4C508A, 0, fighter->x894_currentAnimFrame, 1.0f, 0.0f);
}

void ftPikachu_ActionChangeUpdateVel_801274AC(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x235C = fighter->x80_self_vel.x;
    fighter->x2360_f32 = fighter->x80_self_vel.y;
    fighter->x2364 = fighter->xEC_ground_vel;
    
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    fighter->xEC_ground_vel = 0.0f;
    fighter->xEC_ground_vel = fighter->x2364 * pika_attr->xA4;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x163, 2, 0, 0.0f, 1.0f, 0.0f);
    fighter->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
}

void ftPikachu_ActionChangeUpdateVel_80127534(HSD_GObj* fighterObj) {
    s32 unused[2]; 
    ftPikachuAttributes* pika_attr;
    Fighter* fighter = fighterObj->user_data;
    pika_attr = fighter->x2D4_specialAttributes;
    fighter->x235C = fighter->x80_self_vel.x;
    fighter->x2360_f32 = fighter->x80_self_vel.y;
    fighter->x2364 = fighter->xEC_ground_vel;
    
    fighter->x80_self_vel.y = 0.0f;
    fighter->x80_self_vel.x = 0.0f;
    fighter->xEC_ground_vel = 0.0f;
    fighter->x80_self_vel.x = fighter->x235C * pika_attr->xA4;
    fighter->x80_self_vel.y = fighter->x2360_f32 * pika_attr->xA4;
    Fighter_ActionStateChange_800693AC(fighterObj, 0x166, 2, 0, 0.0f, 1.0f, 0.0f);
    fighter->cb.x21F8_callback = &ftPikachu_UpdateVel_80125D80;
}