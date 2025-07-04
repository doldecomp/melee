#include <platform.h>

#include "ftGw_SpecialHi.h"

#include "ftGw_Init.h"
#include "math.h"
#include "types.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcliffcommon.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_FallSpecial.h"
#include "it/items/itgamewatchrescue.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

static void ftGw_SpecialHi_ItemRescueEnterHitlag(HSD_GObj* gobj);
static void ftGw_SpecialHi_ItemRescueExitHitlag(HSD_GObj* gobj);

// 0x8014DEF0
// https://decomp.me/scratch/6Vtu9 // Create Fire Rescue item
void ftGw_SpecialHi_ItemRescueSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp;
    HSD_GObj* rescueGObj;

    fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x226C_rescueGObj == NULL) {
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &sp10);
        sp10.y = -((2.5f * ftCommon_GetModelScale(fp)) - sp10.y);
        rescueGObj = it_802C8038(gobj, &sp10, FtPart_TopN,
                                 fp->motion_id - ftGw_MS_SpecialHi,
                                 fp->facing_dir, 2.5f);
        fp->fv.gw.x226C_rescueGObj = rescueGObj;
        if (rescueGObj != NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
            fp->take_dmg_cb = ftGw_Init_OnDamage;
        }
        fp->pre_hitlag_cb = ftGw_SpecialHi_ItemRescueEnterHitlag;
        fp->post_hitlag_cb = ftGw_SpecialHi_ItemRescueExitHitlag;
        fp->accessory4_cb = NULL;
    }
}

// 0x8014DFB8
// https://decomp.me/scratch/Wu4WV // Check if Mr. Game & Watch is performing
// Fire Rescue
bool ftGw_SpecialHi_ItemCheckRescueRemove(HSD_GObj* gobj)
{
    enum_t msid = GET_FIGHTER(gobj)->motion_id;

    switch (msid) {
    case ftGw_MS_SpecialHi:
    case ftGw_MS_SpecialAirHi:
        return false;
    default:
        return true;
    }
}

// 0x8014DFE4 - Set Fire Rescue GObj pointer and callbacks to NULL
void ftGw_SpecialHi_ItemRescueSetNULL(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->fv.gw.x226C_rescueGObj = NULL;
    fp->death2_cb = NULL;
    fp->take_dmg_cb = NULL;
}

// 0x8014DFFC - Remove Fire Rescue item
void ftGw_SpecialHi_ItemRescueRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        it_802C8158(fp->fv.gw.x226C_rescueGObj);
        ftGw_SpecialHi_ItemRescueSetNULL(gobj);
    }
}

// 0x8014E04C - Apply hitlag to Fire Rescue item
static void ftGw_SpecialHi_ItemRescueEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        it_802C81C8(fp->fv.gw.x226C_rescueGObj);
    }
}

// 0x8014E06C - Remove hitlag for Fire Rescue item
static void ftGw_SpecialHi_ItemRescueExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->fv.gw.x226C_rescueGObj != NULL) {
        it_802C81E8(fp->fv.gw.x226C_rescueGObj);
    }
}

static inline void ftGameWatch_SpecialHi_SetVars(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->cmd_vars[3] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[0] = 0;
    fp->accessory4_cb = ftGw_SpecialHi_ItemRescueSetup;
}

// 0x8014E0AC
// https://decomp.me/scratch/4Dc4b // Mr. Game & Watch's grounded Fire Rescue
// Motion State handler
void ftGw_SpecialHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[16];

    fp->x74_anim_vel.y = 0.0f;
    fp->self_vel.y = 0.0f;
    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftGameWatch_SpecialHi_SetVars(gobj);
    ftAnim_8006EBA4(gobj);
    ft_80088510(fp, 290066, 127, 64);
}

// 0x8014E158 - Mr. Game & Watch's aerial Fire Rescue Motion State handler
void ftGw_SpecialAirHi_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[24];

    ftCommon_8007D60C(fp);
    Fighter_ChangeMotionState(gobj, ftGw_MS_SpecialAirHi, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftGameWatch_SpecialHi_SetVars(gobj);
    ftAnim_8006EBA4(gobj);
    ft_80088510(fp, 290066, 127, 64);
}

// 0x8014E1F8 - Mr. Game & Watch's grounded Fire Rescue Animation callback
void ftGw_SpecialHi_Anim(HSD_GObj* gobj)
{
    ftGw_SpecialAirHi_Anim(gobj);
}

// 0x8014E218
// https://decomp.me/scratch/QRkS8 // Mr. Game & Watch's aerial Fire Rescue
// Animation callback
void ftGw_SpecialAirHi_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    ftGameWatchAttributes* gawAttrs;

    gawAttrs = (GET_FIGHTER(gobj))->dat_attrs;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (0.0f == gawAttrs->x60_GAMEWATCH_RESCUE_LANDING) {
            ftCo_800CC730(gobj);
            return;
        }
        ftCo_80096900(gobj, 1, 0, 1, 1.0f,
                      gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
    }
}

// 0x8014E290 - Mr. Game & Watch's grounded Fire Rescue IASA callback
void ftGw_SpecialHi_IASA(HSD_GObj* gobj)
{
    ftGw_SpecialAirHi_IASA(gobj);
}

// 0x8014E2B0
// https://decomp.me/scratch/2aEQN // Mr. Game & Watch's aerial Fire Rescue
// IASA callback
void ftGw_SpecialAirHi_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftGameWatchAttributes* gawAttrs = fp->dat_attrs;
    float stick_x;
    float temp;
    float angle;
    float facing_dir;
    float stick_range_threshold;

    if ((u32) fp->cmd_vars[0] == 0) {
        stick_x = stickGetDir(fp->input.lstick.x, 0.0f);
        if (stick_x > gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE) {
            stick_range_threshold =
                stick_x - gawAttrs->x58_GAMEWATCH_RESCUE_STICK_RANGE;
            if (fp->input.lstick.x > 0.0f) {
                facing_dir = 1.0f;
            } else {
                facing_dir = -1.0f;
            }

            temp = stick_range_threshold * facing_dir;
            angle = temp * gawAttrs->x5C_GAMEWATCH_RESCUE_ANGLE_UNK;
            ftCommon_8007D9FC(fp);
            ftParts_80075AF0(fp, 0, (M_PI / 2) * fp->facing_dir);
            fp->lstick_angle = -angle;
            fp->cmd_vars[0] = 1;
        }
    }
}

// 0x8014E374 - Mr. Game & Watch's grounded Fire Rescue Physics callback
void ftGw_SpecialHi_Phys(HSD_GObj* gobj)
{
    ftGw_SpecialAirHi_Phys(gobj);
}

// 0x8014E394 - Mr. Game & Watch's aerial Fire Rescue Physics callback
void ftGw_SpecialAirHi_Phys(HSD_GObj* gobj)
{
    ft_80085154(gobj);
}

// 0x8014E3B4 - Mr. Game & Watch's grounded Fire Rescue Collision callback
void ftGw_SpecialHi_Coll(HSD_GObj* gobj)
{
    ftGw_SpecialAirHi_Coll(gobj);
}

// 0x8014E3D4
// https://decomp.me/scratch/4IC4C // Mr. Game & Watch's aerial Fire Rescue
// Collision callback
void ftGw_SpecialAirHi_Coll(HSD_GObj* gobj)
{
    Fighter* fp;
    ftGameWatchAttributes* gawAttrs;
    int ledgeGrabDir;

    u8 _[8];

    fp = GET_FIGHTER(gobj);
    gawAttrs = fp->dat_attrs;

    if (fp->cur_anim_frame > 4.0f) {
        if (fp->self_vel.y >= 0.0f) {
            if (ft_80081D0C(gobj) != false) {
                ftGw_SpecialHi_ItemRescueRemove(gobj);
                ftCommon_8007D7FC(fp);
                ftCo_800D5CB0(gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
                fp->death2_cb = NULL;
                fp->take_dmg_cb = NULL;
            }
        } else {
            if (1.0f == fp->facing_dir) {
                ledgeGrabDir = 1;
            } else {
                ledgeGrabDir = -1;
            }
            if (ft_CheckGroundAndLedge(gobj, ledgeGrabDir) != false) {
                ftCo_800D5CB0(gobj, 0, gawAttrs->x60_GAMEWATCH_RESCUE_LANDING);
            } else if (ftCliffCommon_80081298(gobj) != false) {
                ftCliffCommon_80081370(gobj);
            }
        }
    }
}
