#include "ftdonkey.h"

/// TODO remove these externs
// extern f32 lbl_804D9150;
// extern f32 lbl_804D9154;

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