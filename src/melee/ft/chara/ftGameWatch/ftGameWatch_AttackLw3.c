#include "forward.h"

#include "ftgamewatch.h"

#include "ft/ft_81B.h"
#include "ft/ft_877.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "it/code_8027CF30.h"
#include "lb/lbunknown_001.h"

#include <dolphin/mtx/types.h>

static void ftGameWatch_ItemManholeExitHitlag(HSD_GObj*);
static void ftGameWatch_ItemManholeEnterHitlag(HSD_GObj*);

// 0x8014AB48
// https://decomp.me/scratch/x73Hx // Create Manhole Item
void ftGameWatch_ItemManholeSetup(HSD_GObj* gobj)
{
    Vec3 sp10;
    HSD_GObj* manholeGObj;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x2250_manholeGObj2 == NULL) {
        func_8000B1CC(fp->ft_bones[0x20].x0_jobj, NULL, &sp10);
        manholeGObj = fp->x1974_heldItem;
        if (manholeGObj != NULL) {
            fp->fv.gw.x2248_manholeGObj = manholeGObj;
            func_8026BB44(fp->x1974_heldItem);
            func_8026B724(fp->x1974_heldItem);
            ftCommon_8007E6DC(gobj, fp->x1974_heldItem, 1);
        }
        fp->fv.gw.x2250_manholeGObj2 =
            func_802C65E4(gobj, &sp10, 0x20, fp->facing_dir);
    }
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
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
void ftGameWatch_ItemManholeRemove(HSD_GObj* gobj)
{
    HSD_GObj* manholeGObj;
    Fighter* fp = GET_FIGHTER(gobj);

    ftGameWatch_ItemManholeExitHitlag(gobj);
    fp->fv.gw.x2250_manholeGObj2 = NULL;
    manholeGObj = fp->fv.gw.x2248_manholeGObj;
    if (manholeGObj != NULL) {
        fp->x1974_heldItem = manholeGObj;
        fp->fv.gw.x2248_manholeGObj = NULL;
        func_8026BB20(fp->x1974_heldItem);
        func_8026B73C(fp->x1974_heldItem);
        ft_80094818(gobj, 1);
    }
}

// 0x8014ACB0
// https://decomp.me/scratch/09CUB // Remove Manhole on damage
void ftGameWatch_ItemManholeOnDamage(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = getFighter(gobj);

    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        func_802C6718(fp->fv.gw.x2250_manholeGObj2);
        ftGameWatch_ItemManholeRemove(gobj);
    }
}

// 0x8014AD38
// https://decomp.me/scratch/Kw1d3 // Apply hitlag to Manhole item
static void ftGameWatch_ItemManholeEnterHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        func_802C6764(fp->fv.gw.x2250_manholeGObj2);
    }
}

// 0x8014AD68 - Remove hitlag from Manhole item
static void ftGameWatch_ItemManholeExitHitlag(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.gw.x2250_manholeGObj2 != NULL) {
        func_802C6784(fp->fv.gw.x2250_manholeGObj2);
    }
}

// 0x8014AD98
// https://decomp.me/scratch/IERdX // Check if Mr. Game & Watch is performing
// Down Tilt - remove if returns true
bool ftGameWatch_ItemCheckManholeRemove(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->motion_id == ftGw_MS_AttackLw3) {
        return false;
    }
    return true;
}

// 0x8014ADB8
// https://decomp.me/scratch/rGgyM // Mr. Game & Watch's Down Tilt Motion State
// Handler
void ftGameWatch_AttackLw3_Action(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ft_80094790(gobj) == false) {
        fp->x2218_flag.bits.b0 = 0;
        Fighter_ChangeMotionState(gobj, ftGw_MS_AttackLw3, 0, NULL, 0.0f, 1.0f,
                                  0.0f);
        ftAnim_8006EBA4(gobj);
        fp->cb.x21BC_callback_Accessory4 = ftGameWatch_ItemManholeSetup;
    }
}

// 0x8014AE3C
// https://decomp.me/scratch/h03Ja // Mr. Game & Watch's Down Tilt Animation
// callback
void ftGameWatch_AttackLw3_Anim(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (!ftAnim_IsFramesRemaining(gobj))
        ft_800D638C(gobj);
}

// 0x8014AE78
// https://decomp.me/scratch/qzCi0 // Mr. Game & Watch's Down Tilt IASA
// callback
void ftGameWatch_AttackLw3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2218_flag.bits.b0 == 0)
        return;
    if (ft_8008BFC4(gobj) != false)
        return;
    if (ft_8008C830(gobj) != false)
        return;
    if (ft_8008CB44(gobj) != false)
        return;
    if (ft_8008B658(gobj) != false)
        return;
    if (ft_8008B980(gobj) != false)
        return;
    if (ft_8008BB44(gobj) != false)
        return;
    if (ft_8008A9F8(gobj) != false)
        return;
    if (ft_800CAED0(gobj) != false)
        return;
    if (ft_800CA094(gobj) != false)
        return;
    if (ft_800D5F58(gobj) != false)
        return;
    if (ft_800C97DC(gobj) != false)
        return;
    if (ft_800C9468(gobj) != false)
        return;
}

// 0x8014AF6C
// https://decomp.me/scratch/Xp4C5 // Mr. Game & Watch's Down Tilt Physics
// callback
void ftGameWatch_AttackLw3_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

// 0x8014AF8C
// https://decomp.me/scratch/0stMN // Mr. Game & Watch's Down Tilt Collision
// callback
void ftGameWatch_AttackLw3_Coll(HSD_GObj* gobj)
{
    ft_80084104(gobj);
    ftGameWatch_8014A538(gobj);
}
