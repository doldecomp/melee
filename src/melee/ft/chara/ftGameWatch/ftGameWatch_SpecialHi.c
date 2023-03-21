#include "ftgamewatch.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

static void ftGameWatch_ItemRescueEnterHitlag(HSD_GObj* gobj);
static void ftGameWatch_ItemRescueExitHitlag(HSD_GObj* gobj);

// 0x8014DEF0
// https://decomp.me/scratch/6Vtu9 // Create Fire Rescue item
void ftGameWatch_ItemRescueSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp;
    HSD_GObj* rescueGObj;

    fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x226C_rescueGObj == NULL) {
        func_8000B1CC(fp->x5E8_fighterBones[0].x0_jobj, NULL, &sp10);
        sp10.y = -((2.5f * Fighter_GetModelScale(fp)) - sp10.y);
        rescueGObj = func_802C8038(gobj, &sp10, 0, fp->action_id - 0x175,
                                   fp->facing_dir, 2.5f);
        fp->fv.gw.x226C_rescueGObj = rescueGObj;
        if (rescueGObj != NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
        fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemRescueEnterHitlag;
        fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemRescueExitHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014DFB8
// https://decomp.me/scratch/Wu4WV // Check if Mr. Game & Watch is performing
// Fire Rescue
bool ftGameWatch_ItemCheckRescueRemove(HSD_GObj* gobj)
{
    enum_t ASID = GET_FIGHTER(gobj)->action_id;

    switch (ASID) {
    case MS_GAMEWATCH_SPECIALHI:
    case MS_GAMEWATCH_SPECIALAIRHI:
        return false;
    default:
        return true;
    }
}

// 0x8014DFE4 - Set Fire Rescue GObj pointer and callbacks to NULL
void ftGameWatch_ItemRescueSetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->fv.gw.x226C_rescueGObj = NULL;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x8014DFFC - Remove Fire Rescue item
void ftGameWatch_ItemRescueRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        func_802C8158(fp->fv.gw.x226C_rescueGObj);
        ftGameWatch_ItemRescueSetNULL(gobj);
    }
}

// 0x8014E04C - Apply hitlag to Fire Rescue item
static void ftGameWatch_ItemRescueEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        func_802C81C8(fp->fv.gw.x226C_rescueGObj);
    }
}

// 0x8014E06C - Remove hitlag for Fire Rescue item
static void ftGameWatch_ItemRescueExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        func_802C81E8(fp->fv.gw.x226C_rescueGObj);
    }
}

static inline void ftGameWatch_SpecialHi_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x220C_ftcmd_var3 = 0;
    fp->x2208_ftcmd_var2 = 0;
    fp->x2204_ftcmd_var1 = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemRescueSetup;
}

// 0x8014E0AC
// https://decomp.me/scratch/4Dc4b // Mr. Game & Watch's grounded Fire Rescue
// Action State handler
void ftGameWatch_SpecialHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    fp->x74_anim_vel.y = 0.0f;
    fp->x80_self_vel.y = 0.0f;
    func_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, MS_GAMEWATCH_SPECIALHI, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    ftGameWatch_SpecialHi_SetVars(gobj);
    func_8006EBA4(gobj);
    func_80088510(fp, 0x46D12, 0x7F, 0x40);
}

// 0x8014E158 - Mr. Game & Watch's aerial Fire Rescue Action State handler
void ftGameWatch_SpecialAirHi_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[24];
#endif

    func_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, MS_GAMEWATCH_SPECIALAIRHI, 0, NULL, 0.0f,
                              1.0f, 0.0f);
    ftGameWatch_SpecialHi_SetVars(gobj);
    func_8006EBA4(gobj);
    func_80088510(fp, 0x46D12, 0x7F, 0x40);
}

// 0x8014E1F8 - Mr. Game & Watch's grounded Fire Rescue Animation callback
void ftGameWatch_SpecialHi_Anim(HSD_GObj* gobj)
{
    ftGameWatch_SpecialAirHi_Anim(gobj);
}

// 0x8014E218
// https://decomp.me/scratch/QRkS8 // Mr. Game & Watch's aerial Fire Rescue
// Animation callback
void ftGameWatch_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    ftGameWatchAttributes* gawAttrs;

    gawAttrs = (GET_FIGHTER(gobj))->x2D4_specialAttributes;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == gawAttrs->x60_GAMEWATCH_RESCUE_LANDING) {
            func_800CC730(gobj);
            return;
        }
        func_80096900(gobj, 1, 0, 1, 1.0f,
                      gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
    }
}

// 0x8014E290 - Mr. Game & Watch's grounded Fire Rescue IASA callback
void ftGameWatch_SpecialHi_IASA(HSD_GObj* gobj)
{
    ftGameWatch_SpecialAirHi_IASA(gobj);
}

// 0x8014E2B0
// https://decomp.me/scratch/2aEQN // Mr. Game & Watch's aerial Fire Rescue
// IASA callback
void ftGameWatch_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = fp->x2D4_specialAttributes;
    f32 stick_x;
    f32 temp;
    f32 angle;
    f32 facing_dir;
    f32 stick_range_threshold;

    if ((u32) fp->x2200_ftcmd_var0 == 0) {
        stick_x = stickGetDir(fp->input.x620_lstick_x, 0.0f);
        if (stick_x > gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE) {
            stick_range_threshold =
                stick_x - gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE;
            if (fp->input.x620_lstick_x > 0.0f) {
                facing_dir = 1.0f;
            } else
                facing_dir = -1.0f;

            temp = stick_range_threshold * facing_dir;
            angle = temp * gawAttrs->x5C_GAMEWATCH_RESCUE_ANGLE_UNK;
            func_8007D9FC(fp);
            func_80075AF0(fp, 0, (M_PI / 2) * fp->facing_dir);
            fp->x6BC_inputStickangle = -angle;
            fp->x2200_ftcmd_var0 = 1;
        }
    }
}

// 0x8014E374 - Mr. Game & Watch's grounded Fire Rescue Physics callback
void ftGameWatch_SpecialHi_Phys(HSD_GObj* gobj)
{
    ftGameWatch_SpecialAirHi_Phys(gobj);
}

// 0x8014E394 - Mr. Game & Watch's aerial Fire Rescue Physics callback
void ftGameWatch_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    func_80085154(gobj);
}

// 0x8014E3B4 - Mr. Game & Watch's grounded Fire Rescue Collision callback
void ftGameWatch_SpecialHi_Coll(HSD_GObj* gobj)
{
    ftGameWatch_SpecialAirHi_Coll(gobj);
}

// 0x8014E3D4
// https://decomp.me/scratch/4IC4C // Mr. Game & Watch's aerial Fire Rescue
// Collision callback
void ftGameWatch_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp;
    ftGameWatchAttributes* gawAttrs;
    int ledgeGrabDir;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    fp = GET_FIGHTER(gobj);
    gawAttrs = fp->x2D4_specialAttributes;

    if (fp->x894_currentAnimFrame > 4.0f) {
        if (fp->x80_self_vel.y >= 0.0f) {
            if (func_80081D0C(gobj) != false) {
                ftGameWatch_ItemRescueRemove(gobj);
                func_8007D7FC(fp);
                func_800D5CB0(gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
                fp->cb.x21E4_callback_OnDeath2 = NULL;
                fp->cb.x21DC_callback_OnTakeDamage = NULL;
            }
        } else {
            if (1.0f == fp->facing_dir) {
                ledgeGrabDir = 1;
            } else
                ledgeGrabDir = -1;
            if (EnvColl_CheckGroundAndLedge(gobj, ledgeGrabDir) != false) {
                func_800D5CB0(gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
                return;
            }
            if (func_80081298(gobj) != false) {
                func_80081370(gobj);
            }
        }
    }
}
