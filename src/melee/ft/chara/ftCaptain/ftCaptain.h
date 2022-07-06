#ifndef _ftcaptain_h_
#define _ftcaptain_h_

#include <global.h>
#include <dolphin/types.h>
#include "sysdolphin/baselib/gobj.h"
#include "melee/ft/fighter.h"

typedef struct _CaptainAttr
{
    f32 DOWNWARD_NEUTRALB_RANGE;
    f32 UPWARD_NEUTRALB_RANGE;
    f32 NEUTRALB_ANGLE_DIFFERENCE;
    f32 NEUTRALB_FORWARD_MOMENTUM;
    f32 NEUTRALB_ADDITIONAL_MOMENTUM_FROM_ANGLE_AIR;

    f32 SIDEB_SUCCESS_GRAVITY;
    f32 SIDEB_WHIFF_GRAVITY;
    f32 SIDEB_WHIFF_GRAVITY_UNK;
    f32 SIDEB_UNK1;
    f32 SIDEB_UNK2;
    f32 SIDEB_UNK3;
    f32 SIDEB_UNK4;
    f32 SIDEB_UNK5;
    f32 SIDEB_UNK6;
    f32 SIDEB_WHIFF_FREEFALL_TOGGLE;
    f32 SIDEB_SUCCESS_FREEFALL_TOGGLE;

    f32 UPB_AIR_FRICTION_MULTIPLIER;
    f32 UPB_HORIZONTAL_MOMENTUM;
    f32 UPB_FREEFALL_AIR_SPEED_MULTIPLIER;
    f32 UPB_LANDING_LAG;
    f32 UPB_UNK1;
    f32 UPB_UNK2;
    f32 UPB_INPUT_VAR;
    f32 UPB_UNK3;
    f32 UPB_GRAVITY_DURING_AIR_CATCH;
    f32 UPB_AERIAL_VAR;

    f32 COMPLETELY_UNKNOWN;

    u32 DOWNB_UNK1;
    f32 DOWNB_FLAME_PARTICLE_ANGLE;
    f32 DOWNB_ON_HIT_SPEED_MODIFIER;
    u32 DOWNB_UNK2;
    f32 DOWNB_GROUND_LAG_MULTIPLIER;
    f32 DOWNB_LANDING_LAG_MULTIPLIER;
    f32 DOWNB_GROUND_TRACTION;
    f32 DOWNB_AIR_LANDING_TRACTION;
}CaptainAttr;

void func_800E2AEC(HSD_GObj* fighter_gobj);
void func_800E2888(HSD_GObj* fighter_gobj);
void ftCFalcon_OnItemPickup(HSD_GObj* fighter_gobj, BOOL unk_var);
void ftCFalcon_OnItemInvisible(HSD_GObj* fighter_gobj) ;
void ftCFalcon_OnItemVisible(HSD_GObj* fighter_gobj);
void ftCFalcon_OnItemDrop(HSD_GObj* fighter_gobj, BOOL unk1);
void func_800E2B40(HSD_GObj* fighter_gobj);

#endif