#include "ftGw_Attack11.h"

#include "ftGw_Init.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Attack1.h"
#include "ftCommon/ftpickupitem.h"
#include "ftGameWatch/types.h"
#include "it/items/itgamewatchgreenhouse.h"
#include "lb/lb_00B0.h"

#include <dolphin/mtx.h>

/// 0x8014BDB0
/// https://decomp.me/scratch/7BADg // Create Insecticide Spray Item
void ftGw_Attack11_ItemGreenhouseSetup(HSD_GObj* gobj)
{
    Vec3 sp10;

    u8 _[4];

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        ftGw_Attack11_DecideAction(gobj);
    } else {
        lb_8000B1CC(fp->parts[FtPart_LHandNb].joint, NULL, &sp10);
        fp->fv.gw.x224C_greenhouseGObj = itGamewatchGreenhouse_Spawn(
            gobj, &sp10, FtPart_LHandNb, fp->facing_dir);
        if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
            if (fp->death2_cb == NULL) {
                fp->death2_cb = ftGw_Init_OnDamage;
            }
            if (fp->take_dmg_cb == NULL) {
                fp->take_dmg_cb = ftGw_Init_OnDamage;
            }
            fp->pre_hitlag_cb = ftGw_Attack11_ItemGreenhouseEnterHitlag;
            fp->post_hitlag_cb = ftGw_Attack11_ItemGreenhouseExitHitlag;
        }
    }
    fp->accessory4_cb = NULL;
}

/// 0x8014BE84
/// https://decomp.me/scratch/H3n4O // Decide Jab attack
void ftGw_Attack11_DecideAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        msid = fp->motion_id;
        if (msid == ftGw_MS_Attack11) {
            itGamewatchGreenhouse_802C6430(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100Start) {
            itGamewatchGreenhouse_802C6458(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100Loop) {
            itGamewatchGreenhouse_802C6480(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100End) {
            itGamewatchGreenhouse_802C64A8(fp->fv.gw.x224C_greenhouseGObj);
        }

        if (fp->death2_cb == NULL) {
            fp->death2_cb = ftGw_Init_OnDamage;
        }
        if (fp->take_dmg_cb == NULL) {
            fp->take_dmg_cb = ftGw_Init_OnDamage;
        }
        fp->pre_hitlag_cb = ftGw_Attack11_ItemGreenhouseEnterHitlag;
        fp->post_hitlag_cb = ftGw_Attack11_ItemGreenhouseExitHitlag;
        fp->accessory4_cb = NULL;
    }
}

/// 0x8014BF48
/// https://decomp.me/scratch/zLba7 // Set flags on Mr. Game & Watch's
/// Insecticide Sprayer
void ftGw_Attack11_ItemGreenhouseSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGw_Attack11_ItemGreenhouseExitHitlag(gobj);
    fp->fv.gw.x224C_greenhouseGObj = NULL;
}

/// 0x8014BF7C
/// https://decomp.me/scratch/2RDRo // Remove Mr. Game & Watch's Insecticide
/// Sprayer
void ftGw_Attack11_ItemGreenhouseRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        itGamewatchGreenhouse_802C6328(fp->fv.gw.x224C_greenhouseGObj);
        ftGw_Attack11_ItemGreenhouseSetFlag(gobj);
    }
}

/// 0x8014BFD4
/// https://decomp.me/scratch/zVtUN // Apply hitlag to Mr. Game & Watch's
/// Insecticide Sprayer
void ftGw_Attack11_ItemGreenhouseEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        itGamewatchGreenhouse_802C6374(fp->fv.gw.x224C_greenhouseGObj);
    }
}

/// 0x8014C004 - Remove hitlag for Mr. Game & Watch's Insecticide Sprayer
void ftGw_Attack11_ItemGreenhouseExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        itGamewatchGreenhouse_802C6394(fp->fv.gw.x224C_greenhouseGObj);
    }
}

/// 0x8014C034
/// https://decomp.me/scratch/Nkgz4 // Check if Mr. Game & Watch is in any of
/// his jab action states
bool ftGw_Attack11_ItemGreenhouse_CheckAll(HSD_GObj* gobj)
{
    s32 msid = GET_FIGHTER(gobj)->motion_id;
    if ((msid >= ftGw_MS_Attack11) && (msid <= ftGw_MS_Attack100End)) {
        return false;
    }
    return true;
}

/// 0x8014C05C - Check if Mr. Game & Watch is performing Jab 1 (Attack11)
bool ftGw_Attack11_ItemGreenhouse_CheckAttack11(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->motion_id != ftGw_MS_Attack11) {
        return true;
    }
    return false;
}

/// 0x8014C07C
/// https://decomp.me/scratch/OYf9U // Mr. Game & Watch's Jab Motion State
/// handler
void ftGw_Attack11_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[4];

    if (ftpickupitem_80094790(gobj) == false) {
        fp->allow_interrupt = 0;
        fp->x2218_b1 = 0;
        Fighter_ChangeMotionState(gobj, ftGw_MS_Attack11, 0, 0.0f, 1.0f, 0.0f,
                                  NULL);
        ftAnim_8006EBA4(gobj);
        fp->hitlag_mul = (float) fp->co_attrs.jab_2_input_window;
        fp->unk_msid = 44;
        fp->x2218_b2 = 0;
        fp->mv.gw.Attack11.unk = 0;
        fp->x1A54 = 0;
        fp->accessory4_cb = ftGw_Attack11_ItemGreenhouseSetup;
    }
}

/// 0x8014C138
/// https://decomp.me/scratch/BKUIu // Mr. Game & Watch's Jab Animation callback
void ftGw_Attack11_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

/// 0x8014C174 - Mr. Game & Watch's Jab IASA callback
void ftGw_Attack11_IASA(HSD_GObj* gobj)
{
    ftCo_Attack11_IASA(gobj);
}

/// 0x8014C194 - Mr. Game & Watch's Jab Physics callback
void ftGw_Attack11_Phys(HSD_GObj* gobj)
{
    ft_80084FA8(gobj);
}

/// 0x8014C1B4 - Mr. Game & Watch's Jab Collision callback
void ftGw_Attack11_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGw_Init_8014A538(gobj);
}
