#ifndef _ftcaptain_h_
#define _ftcaptain_h_

#include <global.h>
#include <dolphin/types.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef enum ftCaptainAction {

    AS_FTCOMMON = 340,
    AS_CAPTAIN_SWING42_SWORD,
    AS_CAPTAIN_SWING42_2,
    AS_CAPTAIN_SWING42_3,
    AS_CAPTAIN_SWING42_4,
    AS_CAPTAIN_SWING42_5,
    AS_CAPTAIN_SWING42_6,
    AS_CAPTAIN_SPECIALN,
    AS_CAPTAIN_SPECIALAIRN,
    AS_CAPTAIN_SPECIALS_START,
    AS_CAPTAIN_SPECIALS,
    AS_CAPTAIN_SPECIALAIRS_START,
    AS_CAPTAIN_SPECIALAIRS,
    AS_CAPTAIN_SPECIALHI,
    AS_CAPTAIN_SPECIALAIRHI,
    AS_CAPTAIN_SPECIALHI_CATCH,
    AS_CAPTAIN_SPECIALHI_THROW,

} ftCaptainAction;

// Flags used by Captain Falcon and Ganondorf in ActionStateChange //

// SpecialN/SpecialAirN (Falcon / Warlock Punch)
#define FTCAPTAIN_SPECIALN_COLL_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_RUMBLE_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

// SpecialS/SpecialAirS (Raptor Boost / Gerudo Dragon)
#define FTCAPTAIN_SPECIALS_FLAG FIGHTER_GFX_PRESERVE | FIGHTER_MATANIM_NOUPDATE | FIGHTER_CMD_UPDATE | FIGHTER_COLANIM_NOUPDATE | FIGHTER_ITEMVIS_NOUPDATE | FIGHTER_SKIP_UNK_0x2222 | FIGHTER_MODELPART_VIS_NOUPDATE | FIGHTER_MODEL_FLAG_NOUPDATE | FIGHTER_UNK_0x2227

typedef struct _ftCaptainAttributes
{
    f32 x0_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_NEG;   // Minimum control stick range required for downward angle (Negative Y)
    f32 x4_CAPTAIN_FALCONPUNCH_STICK_RANGE_Y_POS;   // Minimum control stick range required for upward angle (Positive Y)
    f32 x8_CAPTAIN_FALCONPUNCH_ANGLE_DIFF;          // Maximum angle change from control stick input
    f32 xC_CAPTAIN_FALCONPUNCH_MOMENTUM_X;          // Momentum gained from aerial Falcon/Warlock Punch
    f32 x10_CAPTAIN_FALCONPUNCH_MOMENTUM_MUL;       // Additional momentum from angled Falcon/Warlock Punch

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

// Captain Falcon & Ganondorf functions //

void func_800E2AEC(HSD_GObj* fighter_gobj);
void func_800E2888(HSD_GObj* fighter_gobj);
void lbl_800E28C8(HSD_GObj* fighter_gobj);
void ftCFalcon_OnItemPickup(HSD_GObj* fighter_gobj, BOOL unk_var);
void ftCFalcon_OnItemInvisible(HSD_GObj* fighter_gobj) ;
void ftCFalcon_OnItemVisible(HSD_GObj* fighter_gobj);
void ftCFalcon_OnItemDrop(HSD_GObj* fighter_gobj, BOOL unk1);
void ftCFalcon_LoadSpecialAttrs(HSD_GObj* fighter_gobj);

// Neutral Special - Falcon/Warlock Punch (SpecialN) //

void ftCaptain_SpecialN_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialN_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirN_Coll(HSD_GObj* fighter_gobj);

// Side Special - Raptor Boost / Gerudo Dragon (SpecialS) //

void ftCaptain_SpecialS_RemoveGFX(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_StartAction(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_OnDetect(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Anim(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_IASA(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Phys(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialSStart_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialS_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirSStart_Coll(HSD_GObj* fighter_gobj);
void ftCaptain_SpecialAirS_Coll(HSD_GObj* fighter_gobj);

#endif