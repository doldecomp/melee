#include "forward.h"
#include "ftgamewatch.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

// 0x8014BDB0
// https://decomp.me/scratch/7BADg // Create Insecticide Spray Item
void ftGameWatch_ItemGreenhouseSetup(HSD_GObj* gobj)
{
    Vec3 sp10;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        ftGameWatch_Attack11_DecideAction(gobj);
    } else {
        func_8000B1CC(fp->x5E8_fighterBones[0x20].x0_jobj, NULL, &sp10);
        fp->fv.gw.x224C_greenhouseGObj =
            func_802C61F4(gobj, &sp10, 0x20, fp->facing_dir);
        if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
            if (fp->cb.x21E4_callback_OnDeath2 == NULL) {
                fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
            }
            if (fp->cb.x21DC_callback_OnTakeDamage == NULL) {
                fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
            }
            fp->cb.x21D4_callback_EnterHitlag =
                ftGameWatch_ItemGreenhouseEnterHitlag;
            fp->cb.x21D8_callback_ExitHitlag =
                ftGameWatch_ItemGreenhouseExitHitlag;
        }
    }
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014BE84
// https://decomp.me/scratch/H3n4O // Decide Jab attack
void ftGameWatch_Attack11_DecideAction(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid;

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        msid = fp->motion_id;
        if (msid == ftGw_MS_Attack11) {
            func_802C6430(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100Start) {
            func_802C6458(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100Loop) {
            func_802C6480(fp->fv.gw.x224C_greenhouseGObj);
        } else if (msid == ftGw_MS_Attack100End) {
            func_802C64A8(fp->fv.gw.x224C_greenhouseGObj);
        }

        if (fp->cb.x21E4_callback_OnDeath2 == NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        }
        if (fp->cb.x21DC_callback_OnTakeDamage == NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
        fp->cb.x21D4_callback_EnterHitlag =
            ftGameWatch_ItemGreenhouseEnterHitlag;
        fp->cb.x21D8_callback_ExitHitlag =
            ftGameWatch_ItemGreenhouseExitHitlag;
        fp->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x8014BF48
// https://decomp.me/scratch/zLba7 // Set flags on Mr. Game & Watch's
// Insecticide Sprayer
void ftGameWatch_ItemGreenhouseSetFlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_ItemGreenhouseExitHitlag(gobj);
    fp->fv.gw.x224C_greenhouseGObj = NULL;
}

// 0x8014BF7C
// https://decomp.me/scratch/2RDRo // Remove Mr. Game & Watch's Insecticide
// Sprayer
void ftGameWatch_ItemGreenhouseRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        func_802C6328(fp->fv.gw.x224C_greenhouseGObj);
        ftGameWatch_ItemGreenhouseSetFlag(gobj);
    }
}

// 0x8014BFD4
// https://decomp.me/scratch/zVtUN // Apply hitlag to Mr. Game & Watch's
// Insecticide Sprayer
void ftGameWatch_ItemGreenhouseEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        func_802C6374(fp->fv.gw.x224C_greenhouseGObj);
    }
}

// 0x8014C004 - Remove hitlag for Mr. Game & Watch's Insecticide Sprayer
void ftGameWatch_ItemGreenhouseExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x224C_greenhouseGObj != NULL) {
        func_802C6394(fp->fv.gw.x224C_greenhouseGObj);
    }
}

// 0x8014C034
// https://decomp.me/scratch/Nkgz4 // Check if Mr. Game & Watch is in any of
// his jab action states
bool ftGameWatch_ItemGreenhouse_CheckAll(HSD_GObj* gobj)
{
    s32 msid = GET_FIGHTER(gobj)->motion_id;
    if ((msid >= ftGw_MS_Attack11) && (msid <= ftGw_MS_Attack100End)) {
        return false;
    }
    return true;
}

// 0x8014C05C - Check if Mr. Game & Watch is performing Jab 1 (Attack11)
bool ftGameWatch_ItemGreenhouse_CheckAttack11(HSD_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->motion_id != ftGw_MS_Attack11) {
        return true;
    }
    return false;
}

// 0x8014C07C
// https://decomp.me/scratch/OYf9U // Mr. Game & Watch's Jab Motion State
// handler
void ftGameWatch_Attack11_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    if (func_80094790(gobj) == false) {
        fp->x2218_flag.bits.b0 = 0;
        fp->x2218_flag.bits.b1 = 0;
        Fighter_ChangeMotionState(gobj, ftGw_MS_Attack11, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        func_8006EBA4(gobj);
        fp->x196C_hitlag_mult = (f32) fp->x110_attr.x18C_Jab_2InputWindow;
        fp->x1970 = 44;
        fp->x2218_flag.bits.b2 = 0;
        fp->mv.gw.Attack11.unk = 0;
        fp->x1A54 = 0;
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemGreenhouseSetup;
    }
}

// 0x8014C138
// https://decomp.me/scratch/BKUIu // Mr. Game & Watch's Jab Animation callback
void ftGameWatch_Attack11_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj)) {
        func_8008A2BC(gobj);
    }
}

// 0x8014C174 - Mr. Game & Watch's Jab IASA callback
void ftGameWatch_Attack11_IASA(HSD_GObj* gobj)
{
    func_8008ACD8(gobj);
}

// 0x8014C194 - Mr. Game & Watch's Jab Physics callback
void ftGameWatch_Attack11_Phys(HSD_GObj* gobj)
{
    func_80084FA8(gobj);
}

// 0x8014C1B4 - Mr. Game & Watch's Jab Collision callback
void ftGameWatch_Attack11_Coll(HSD_GObj* gobj)
{
    func_80084104(gobj);
    ftGameWatch_8014A538(gobj);
}
