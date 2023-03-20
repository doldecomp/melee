#include "ftgamewatch.h"

#include "ft/code_80081B38.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcommon.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

static void ftGameWatch_ItemManholeExitHitlag(HSD_GObj*);
static void ftGameWatch_ItemManholeEnterHitlag(HSD_GObj*);

// 0x8014AB48
// https://decomp.me/scratch/x73Hx // Create Manhole Item
void ftGameWatch_ItemManholeSetup(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    HSD_GObj* manholeGObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = getFighter(fighter_gobj);

    if (fp->ev.gw.x2250_manholeGObj2 == NULL) {
        func_8000B1CC(fp->x5E8_fighterBones[0x20].x0_jobj, NULL, &sp10);
        manholeGObj = fp->x1974_heldItem;
        if (manholeGObj != NULL) {
            fp->ev.gw.x2248_manholeGObj = manholeGObj;
            func_8026BB44(fp->x1974_heldItem);
            func_8026B724(fp->x1974_heldItem);
            func_8007E6DC(fighter_gobj, fp->x1974_heldItem, 1);
        }
        fp->ev.gw.x2250_manholeGObj2 =
            func_802C65E4(fighter_gobj, &sp10, 0x20, fp->facing_dir);
    }
    if (fp->ev.gw.x2250_manholeGObj2 != NULL) {
        if (fp->cb.x21E4_callback_OnDeath2 == NULL) {
            fp->cb.x21E4_callback_OnDeath2 = ftGameWatch_OnDamage;
        }
        if (fp->cb.x21DC_callback_OnTakeDamage == NULL) {
            fp->cb.x21DC_callback_OnTakeDamage = ftGameWatch_OnDamage;
        }
    }
    fp->cb.x21D4_callback_EnterHitlag = ftGameWatch_ItemManholeEnterHitlag;
    fp->cb.x21D8_callback_ExitHitlag = ftGameWatch_ItemManholeExitHitlag;
    fp->cb.x21BC_callback_Accessory4 = NULL;
}

// 0x8014AC40
// https://decomp.me/scratch/JEvaL // Swap item GObj pointers
void ftGameWatch_ItemManholeRemove(HSD_GObj* fighter_gobj)
{
    HSD_GObj* manholeGObj;
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    ftGameWatch_ItemManholeExitHitlag(fighter_gobj);
    fp->ev.gw.x2250_manholeGObj2 = NULL;
    manholeGObj = fp->ev.gw.x2248_manholeGObj;
    if (manholeGObj != NULL) {
        fp->x1974_heldItem = manholeGObj;
        fp->ev.gw.x2248_manholeGObj = NULL;
        func_8026BB20(fp->x1974_heldItem);
        func_8026B73C(fp->x1974_heldItem);
        func_80094818(fighter_gobj, 1);
    }
}

// 0x8014ACB0
// https://decomp.me/scratch/09CUB // Remove Manhole on damage
void ftGameWatch_ItemManholeOnDamage(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(fighter_gobj);

    if (fp->ev.gw.x2250_manholeGObj2 != NULL) {
        func_802C6718(fp->ev.gw.x2250_manholeGObj2);
        ftGameWatch_ItemManholeRemove(fighter_gobj);
    }
}

// 0x8014AD38
// https://decomp.me/scratch/Kw1d3 // Apply hitlag to Manhole item
static void ftGameWatch_ItemManholeEnterHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->ev.gw.x2250_manholeGObj2 != NULL) {
        func_802C6764(fp->ev.gw.x2250_manholeGObj2);
    }
}

// 0x8014AD68 - Remove hitlag from Manhole item
static void ftGameWatch_ItemManholeExitHitlag(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->ev.gw.x2250_manholeGObj2 != NULL) {
        func_802C6784(fp->ev.gw.x2250_manholeGObj2);
    }
}

// 0x8014AD98
// https://decomp.me/scratch/IERdX // Check if Mr. Game & Watch is performing
// Down Tilt - remove if returns true
bool ftGameWatch_ItemCheckManholeRemove(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->action_id == AS_GAMEWATCH_ATTACKLW3) {
        return false;
    }
    return true;
}

// 0x8014ADB8
// https://decomp.me/scratch/rGgyM // Mr. Game & Watch's Down Tilt Action State
// Handler
void ftGameWatch_AttackLw3_Action(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (func_80094790(fighter_gobj) == false) {
        fp->x2218_flag.bits.b0 = 0;
        Fighter_ActionStateChange_800693AC(
            fighter_gobj, AS_GAMEWATCH_ATTACKLW3, 0, NULL, 0.0f, 1.0f, 0.0f);
        func_8006EBA4(fighter_gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemManholeSetup;
    }
}

// 0x8014AE3C
// https://decomp.me/scratch/h03Ja // Mr. Game & Watch's Down Tilt Animation
// callback
void ftGameWatch_AttackLw3_Anim(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(fighter_gobj))
        func_800D638C(fighter_gobj);
}

// 0x8014AE78
// https://decomp.me/scratch/qzCi0 // Mr. Game & Watch's Down Tilt IASA
// callback
void ftGameWatch_AttackLw3_IASA(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->x2218_flag.bits.b0 == 0)
        return;
    if (func_8008BFC4(fighter_gobj) != false)
        return;
    if (func_8008C830(fighter_gobj) != false)
        return;
    if (func_8008CB44(fighter_gobj) != false)
        return;
    if (func_8008B658(fighter_gobj) != false)
        return;
    if (func_8008B980(fighter_gobj) != false)
        return;
    if (func_8008BB44(fighter_gobj) != false)
        return;
    if (func_8008A9F8(fighter_gobj) != false)
        return;
    if (func_800CAED0(fighter_gobj) != false)
        return;
    if (func_800CA094(fighter_gobj) != false)
        return;
    if (func_800D5F58(fighter_gobj) != false)
        return;
    if (func_800C97DC(fighter_gobj) != false)
        return;
    if (func_800C9468(fighter_gobj) != false)
        return;
}

// 0x8014AF6C
// https://decomp.me/scratch/Xp4C5 // Mr. Game & Watch's Down Tilt Physics
// callback
void ftGameWatch_AttackLw3_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x8014AF8C
// https://decomp.me/scratch/0stMN // Mr. Game & Watch's Down Tilt Collision
// callback
void ftGameWatch_AttackLw3_Coll(HSD_GObj* fighter_gobj)
{
    func_80084104(fighter_gobj);
    ftGameWatch_8014A538(fighter_gobj);
}
