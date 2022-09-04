#include <melee/ft/fighter.h>
#include <melee/ft/code_80081B38.h>

s32 ftWalkCommon_GetWalkType_800DFBF8(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    f32 ground_vel = fp->xEC_ground_vel;
    f32 walking_velocity = fabs_inline(ground_vel);
    if (walking_velocity >= (fp->x2360_f32 * (p_ftCommonData->x2C * fp->x110_attr.x118_WalkMaximumVelocity))) {
        return 2;
    } else if (walking_velocity >= (fp->x2360_f32 * (p_ftCommonData->x28 * fp->x110_attr.x118_WalkMaximumVelocity))) {
        return 1;
    } else {
        return 0;
    }
}

inline s32 ftWalkCommon_GetWalkType_800DFBF8_fake(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    f32 walking_velocity = fabs_inline(fp->xEC_ground_vel);
    f32 tempf = fp->x2360_f32;
    if (walking_velocity >= (tempf * (p_ftCommonData->x2C * fp->x110_attr.x118_WalkMaximumVelocity))) {
        return 2;
    } else if (walking_velocity >= (tempf * (p_ftCommonData->x28 * fp->x110_attr.x118_WalkMaximumVelocity))) {
        return 1;
    } else {
        return 0;
    }
}  

s32 ftWalkCommon_800DFC70(HSD_GObj* fighter_gobj) {
    Fighter* fp = fighter_gobj->user_data;
    if ((fp->input.x620_lstick_x * fp->x2C_facing_direction) >= p_ftCommonData->x24) {
        return 1;
    }
    return 0;
} 

void ftWalkCommon_800DFCA4(HSD_GObj *fighter_gobj, s32 arg1, s32 arg2, f32 arg8, f32 arg9, f32 argA, f32 argB, f32 argC, f32 argD, f32 argE, f32 argF)
{
    s32 unused[3];
    s32 new_action_state;
    s32 walking_state;
    Fighter *fp;
    fp = getFighterPlus(fighter_gobj);
    fp->x2360_f32 = argF;
    walking_state = ftWalkCommon_GetWalkType_800DFBF8_fake(fighter_gobj);
    new_action_state = arg1 + walking_state;
    Fighter_ActionStateChange_800693AC(fighter_gobj, new_action_state, arg2, 0, arg8, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->x2340_f32 = fp->xEC_ground_vel;
    fp->x2344_stateVar2_s32 = arg1;
    fp->x2348_stateVar3_f32 = arg9;
    fp->x234C_stateVar4_f32 = argA;
    fp->x2350_stateVar5_f32 = argB;
    fp->x2354_stateVar6_f32 = argC;
    fp->x2358_stateVar7 = argD;
    fp->x235C_f32 = argE;
}

void ftWalkCommon_800DFDDC(HSD_GObj* fighter_gobj) {
    f32 velocity_f2;
    f32 anim_rate;
    
    Fighter* fp = getFighter(fighter_gobj);
    
    if (Stage_GetGroundFrictionMultiplier(fp) < 1.0f) {
        velocity_f2 = fp->x2340_f32;
    } else {
        velocity_f2 = fp->xEC_ground_vel;
    }
    if ((velocity_f2 * fp->x2C_facing_direction) <= 0.0f) {
        anim_rate = 0.0f;
    } else {

        velocity_f2 = fabs_inline(velocity_f2);
        switch (fp->x10_action_state_index - fp->x2344_stateVar2) {  
            case 0:
                anim_rate = velocity_f2 / fp->x234C_pos.z;
                break;
            case 1:
                anim_rate = velocity_f2 / fp->x2358_stateVar7;
                break;
            case 2:
                anim_rate = velocity_f2 / fp->x235C;
                break;
        }
    }
    ftAnim_SetAnimRate(fighter_gobj, anim_rate);
}

void ftWalkCommon_800DFEC8(HSD_GObj* fighter_gobj, void (*arg_cb)(HSD_GObj*, f32)) {
    s32 action_state_sum;
    s32 action_state_base;
    Fighter* fp = getFighter(fighter_gobj);
    s32 walk_action_type = ftWalkCommon_GetWalkType_800DFBF8_fake(fighter_gobj);


    action_state_base = fp->x2344_stateVar2_s32;
    action_state_sum = action_state_base + walk_action_type;
    if (action_state_sum != fp->x10_action_state_index) { 
        f32 float_result;
        f32 var_f31;
        f32 init_animFrame;
        f32 adjusted_animFrame;
        s32 final_animFrame;
        s32 quotient;
        
        switch (action_state_sum - action_state_base) {                   
            case 0:
                var_f31 = fp->x2348_stateVar3_f32;
                break;
            case 1:
                var_f31 = fp->x234C_stateVar4_f32;
                break;
            case 2:
                var_f31 = fp->x2350_stateVar5_f32;
                break;
            default:
                OSReport("couldn't get walk frame\n");
                __assert("ftwalkcommon.c", 0x47U, "0");
                break;
        }
        float_result = func_8006F484(fighter_gobj);
        init_animFrame = fp->x894_currentAnimFrame;
        quotient = init_animFrame / float_result;
        adjusted_animFrame = fp->x894_currentAnimFrame - (float_result * quotient);
        final_animFrame = var_f31 * (adjusted_animFrame / float_result);
        arg_cb(fighter_gobj, final_animFrame);
    }
}

inline f32 getFtWalkAcceleration(Fighter* fp, f32 multiplier) {
    if (fp->input.x620_lstick_x > 0.0f) { 
        return multiplier * fp->x110_attr.x114_WalkAcceleration;
    } else {
        return multiplier * -fp->x110_attr.x114_WalkAcceleration;
    }
} 
 
void ftWalkCommon_800E0060(HSD_GObj* fighter_gobj) {
    s32 unused[5];
    Fighter* fp;
    f32 temp_f0;
    f32 temp_f4;
    f32 ftx2360_f5;
    f32 velocity_f1; 
    f32 unused_float;
 
    fp = fighter_gobj->user_data;
    unused_float = ftx2360_f5 = fp->x2360_f32;
    velocity_f1 = fp->input.x620_lstick_x * fp->x110_attr.x110_WalkInitialVelocity * ftx2360_f5;
    velocity_f1 += getFtWalkAcceleration(fp, ftx2360_f5); 
    temp_f0 = (fp->input.x620_lstick_x * fp->x110_attr.x118_WalkMaximumVelocity) * ftx2360_f5;
    if (temp_f0) {
        temp_f4 = fp->xEC_ground_vel / temp_f0;
        if (temp_f4 > 0.0f && temp_f4 < 1.0f) {
            velocity_f1 *= (1.0f - temp_f4) * p_ftCommonData->x30;
        }
    }
    fp->x2340_f32 = temp_f0 * p_ftCommonData->x440;
    func_8007C98C(fp, velocity_f1, temp_f0, fp->x110_attr.x128_GroundFriction);
    func_8007CB74(fighter_gobj);
}
