#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_H

#include "forward.h"

#include "ft/fighter.h"

#include <baselib/gobj.h>
#include <platform.h>

typedef struct _ftCaptainAttributes {
    f32 x0_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_NEG; // Minimum control stick range
                                                  // required for downward angle
                                                  // (Negative Y)
    f32 x4_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_POS; // Minimum control stick range
                                                  // required for upward angle
                                                  // (Positive Y)
    f32 x8_CAPTAIN_FALCONPUNCH_ANGLE_DIFF; // Maximum angle change from control
                                           // stick input
    f32 xC_CAPTAIN_FALCONPUNCH_MOMENTUM_X; // Momentum gained from aerial
                                           // Falcon/Warlock Punch
    f32 x10_CAPTAIN_FALCONPUNCH_MOMENTUM_MUL; // Additional momentum from angled
                                              // Falcon/Warlock Punch

    f32 x14_CAPTAIN_RAPTORBOOST_GROUND_VEL_X;
    f32 x18_CAPTAIN_RAPTORBOOST_GRAVITY;
    f32 x1C_CAPTAIN_RAPTORBOOST_TERMINAL_VELOCITY;
    f32 x20_CAPTAIN_RAPTORBOOST_UNK1;
    f32 x24_CAPTAIN_RAPTORBOOST_UNK2;
    f32 x28_CAPTAIN_RAPTORBOOST_UNK3;
    f32 x2C_CAPTAIN_RAPTORBOOST_UNK4;
    f32 x30_CAPTAIN_RAPTORBOOST_UNK5;
    f32 x34_CAPTAIN_RAPTORBOOST_UNK6; // All of these Unk variables are unused
    f32 x38_CAPTAIN_RAPTORBOOST_MISS_LANDING_LAG;
    f32 x3C_CAPTAIN_RAPTORBOOST_HIT_LANDING_LAG;

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

} ftCaptainAttributes;

extern ActionState as_table_captain[];
extern char lbl_803C7598[];
extern char lbl_803C75A4[];
extern Fighter_CostumeStrings lbl_803C773C[];
extern char lbl_803C76A0[];
extern Fighter_DemoStrings lbl_803C772C;

// Captain Falcon & Ganondorf functions

void ftCaptain_OnLoad(HSD_GObj* fighter_gobj);
void ftCaptain_OnDeath(HSD_GObj* fighter_gobj);
void ftCaptain_800E28C8(HSD_GObj* fighter_gobj);
void ftCaptain_OnItemPickup(HSD_GObj* fighter_gobj, bool unk_var);
void ftCaptain_OnItemInvisible(HSD_GObj* fighter_gobj);
void ftCaptain_OnItemVisible(HSD_GObj* fighter_gobj);
void ftCaptain_OnItemDrop(HSD_GObj* fighter_gobj, bool unk1);
void ftCaptain_LoadSpecialAttrs(HSD_GObj* fighter_gobj);

void ftCaptain_LoadSpecialAttrs(HSD_GObj*);
void ftCaptain_SpecialAirHi_StartAction(HSD_GObj*);
void ftCaptain_SpecialAirLw_StartAction(HSD_GObj*);
void ftCaptain_SpecialLw_StartAction(HSD_GObj*);
void ftCaptain_SpecialHi_StartAction(HSD_GObj*);

#endif
