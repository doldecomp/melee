#include "ftdonkey.h"

/// TODO remove these externs
// extern f32 lbl_804D9150;
// extern f32 lbl_804D9154;

inline s32 getWalkType(HSD_GObj* fighterObj) {
    Fighter* fighter = fighterObj->user_data;
    f32 walking_velocity = fabs_inline(fighter->xEC_ground_vel);
    f32 tempf = fighter->x2360_f32;
    if (walking_velocity >= (tempf * (p_ftCommonData->x2C * fighter->x110_attr.x118_WalkMaximumVelocity))) {
        return 2;
    } else if (walking_velocity >= (tempf * (p_ftCommonData->x28 * fighter->x110_attr.x118_WalkMaximumVelocity))) {
        return 1;
    } else {
        return 0;
    }
}  


void ftDonkey_800DFCA4(HSD_GObj *fighterObj, s32 arg1, s32 arg2, f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD, f32 argE, f32 argF)
{
    s32 unused[3];
    s32 new_action_state;
    s32 walking_state;
    Fighter *fighter;
    fighter = getFighterPlus(fighterObj);
    fighter->x2360_f32 = argF;
    walking_state = getWalkType(fighterObj);
    new_action_state = arg1 + walking_state;
    Fighter_ActionStateChange_800693AC(fighterObj, new_action_state, arg2, 0, arg8, 1.0f, 0.0f);
    func_8006EBA4(fighterObj);
    fighter->x2340_f32 = fighter->xEC_ground_vel;
    fighter->x2344_stateVar2_s32 = arg1;
    fighter->x2348_stateVar3_f32 = arg9;
    fighter->x234C_stateVar4_f32 = argA;
    fighter->x2350_stateVar5_f32 = argB;
    fighter->x2354_stateVar6_f32 = argC;
    fighter->x2358_stateVar7 = argD;
    fighter->x235C_f32 = argE;
}



void ftDonkey_800DFDDC(HSD_GObj* fighterObj) {
    f32 velocity_f2;
    f32 anim_rate;
    
    Fighter* fighter = getFighter(fighterObj);
    
    if (func_80084A40(fighter) < 1.0f) {
        velocity_f2 = fighter->x2340_f32;
    } else {
        velocity_f2 = fighter->xEC_ground_vel;
    }
    if ((velocity_f2 * fighter->x2C_facing_direction) <= 0.0f) {
        anim_rate = 0.0f;
    } else {

        velocity_f2 = fabs_inline(velocity_f2);
        switch (fighter->x10_action_state_index - fighter->x2344_stateVar2) {  
            case 0:
                anim_rate = velocity_f2 / fighter->x234C_pos.z;
                break;
            case 1:
                anim_rate = velocity_f2 / fighter->x2358_stateVar7;
                break;
            case 2:
                anim_rate = velocity_f2 / fighter->x235C;
                break;
        }
    }
    ftAnim_SetAnimRate(fighterObj, anim_rate);
}



void ftDonkey_800DFEC8(HSD_GObj* fighterObj, void (*arg_cb)(HSD_GObj*, f32)) {
    s32 action_state_sum;
    s32 action_state_base;
    Fighter* fighter = getFighter(fighterObj);
    s32 walk_action_type = getWalkType(fighterObj);


    action_state_base = fighter->x2344_stateVar2_s32;
    action_state_sum = action_state_base + walk_action_type;
    if (action_state_sum != fighter->x10_action_state_index) { 
        f32 float_result;
        f32 var_f31;
        f32 init_animFrame;
        f32 adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;
        
        switch (action_state_sum - action_state_base) {                   
            case 0:
                var_f31 = fighter->x2348_stateVar3_f32;
                break;
            case 1:
                var_f31 = fighter->x234C_stateVar4_f32;
                break;
            case 2:
                var_f31 = fighter->x2350_stateVar5_f32;
                break;
            default:
                OSReport("couldn't get walk frame\n");
                __assert("ftwalkcommon.c", 0x47U, "0");
                break;
        }
        float_result = func_8006F484(fighterObj);
        init_animFrame = fighter->x894_currentAnimFrame;
        quotient = init_animFrame / float_result;
        adjusted_animFrame = fighter->x894_currentAnimFrame - (float_result * quotient);
        final_animFrame = var_f31 * (adjusted_animFrame / float_result);
        arg_cb(fighterObj, final_animFrame);
    }
}

inline f32 getFtWalkAcceleration(Fighter* fighter, f32 multiplier) {
    if (fighter->input.x620_lstick_x > 0.0f) { 
        return multiplier * fighter->x110_attr.x114_WalkAcceleration;
    } else {
        return multiplier * -fighter->x110_attr.x114_WalkAcceleration;
    }
} 

void ftDonkey_800E0060(HSD_GObj* fighterObj) {
    s32 unused[5];
    Fighter* fighter;
    f32 temp_f0;
    f32 temp_f4;
    f32 ftx2360_f5;
    f32 velocity_f1; 
    f32 unused_float;
 
    fighter = fighterObj->user_data;
    unused_float = ftx2360_f5 = fighter->x2360_f32;
    velocity_f1 = fighter->input.x620_lstick_x * fighter->x110_attr.x110_WalkInitialVelocity * ftx2360_f5;
    velocity_f1 += getFtWalkAcceleration(fighter, ftx2360_f5); 
    temp_f0 = (fighter->input.x620_lstick_x * fighter->x110_attr.x118_WalkMaximumVelocity) * ftx2360_f5;
    if (temp_f0) {
        temp_f4 = fighter->xEC_ground_vel / temp_f0;
        if (temp_f4 > 0.0f && temp_f4 < 1.0f) {
            velocity_f1 *= (1.0f - temp_f4) * p_ftCommonData->x30;
        }
    }
    fighter->x2340_f32 = temp_f0 * p_ftCommonData->x440;
    func_8007C98C(fighter, velocity_f1, temp_f0, fighter->x110_attr.x128_GroundFriction);
    func_8007CB74(fighterObj);
}