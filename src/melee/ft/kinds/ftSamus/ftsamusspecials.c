/**
 * @file ftsamusspecials.c
 * @brief Side-B: Missile implementation for Samus
 * @details Implements Samus's Side-B special move (Missile), branching between
 * normal Homing Missile (tilt input) and Super Missile (smash input) based on
 * stick X input, along with corresponding aerial drift/deceleration physics
 * and collision routines. Module prefix: ftSs
 */

#include "ftsamusspecials.h"

#include <melee/ft/forward.h>

#include "ftsamusspecialn.h"
#include "types.h"
#include <dolphin/mtx.h>
#include <melee/ef/eflib.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/kinds/ftCommon/ftCo_Fall.h>

/**
 * @brief Clears throw flags and sets missile launch accessory callback.
 * @param gobj Samus fighter game object pointer
 */
static void ftSamus_ClearThrowFlagsUnk(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x2210.throw_flags = 0;
    fp->accessory4_cb = &ftSs_SpecialS_8012A074; // Missile spawn callback
}

/**
 * @brief Side-B (Missile): Grounded action state entry callback.
 * @details Reduces horizontal speed by divisor samus_attr->x2C.
 * Checks analog stick X smash threshold (samus_attr->x28) to select:
 * - Super Missile (Smash input): ftSs_MS_SpecialSSmash (0x15E = 350)
 * - Homing Missile (Tilt input): ftSs_MS_SpecialS (0x15D = 349)
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->gr_vel /= samus_attr->x2C;
    fp->self_vel.y = 0.0f;
    // Check if analog stick X exceeds smash threshold for Super Missile
    if (fp->active_sticky.lstick.x < samus_attr->x28) {
        Fighter_ChangeMotionState(
            gobj, 0x15E, Ft_MF_None, 0.0f, 1.0f, 0.0f,
            NULL); // ftSs_MS_SpecialSSmash (Super Missile)
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, 0x15D, Ft_MF_None, 0.0f, 1.0f, 0.0f,
                                  NULL); // ftSs_MS_SpecialS (Homing Missile)
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

/**
 * @brief Side-B (Missile): Aerial action state entry callback.
 * @details Reduces horizontal speed by divisor samus_attr->x2C.
 * Checks analog stick X smash threshold (samus_attr->x28) to select:
 * - Aerial Super Missile (Smash input): ftSs_MS_SpecialAirSSmash (0x160 = 352)
 * - Aerial Homing Missile (Tilt input): ftSs_MS_SpecialAirS (0x15F = 351)
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirS_Enter(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    fp->self_vel.x /= samus_attr->x2C;
    // Check if analog stick X exceeds smash threshold for Super Missile
    if (fp->active_sticky.lstick.x < samus_attr->x28) {
        Fighter_ChangeMotionState(
            gobj, 0x160, Ft_MF_None, 0.0f, 1.0f, 0.0f,
            NULL); // ftSs_MS_SpecialAirSSmash (Super Missile)
        ftAnim_8006EBA4(gobj);
    } else {
        Fighter_ChangeMotionState(
            gobj, 0x15F, Ft_MF_None, 0.0f, 1.0f, 0.0f,
            NULL); // ftSs_MS_SpecialAirS (Homing Missile)
        ftAnim_8006EBA4(gobj);
    }
    ftSamus_ClearThrowFlagsUnk(gobj);
}

/**
 * @brief Side-B (Homing Missile): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Return to grounded wait
    }
}

/**
 * @brief Side-B (Homing Missile): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirS_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj); // Transition to aerial fall
    }
}

/**
 * @brief Side-B (Homing Missile): Grounded IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_IASA(HSD_GObj* gobj) {}

/**
 * @brief Side-B (Homing Missile): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirS_IASA(HSD_GObj* gobj) {}

/**
 * @brief Side-B (Homing Missile): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Side-B (Homing Missile): Aerial physics callback.
 * @details Applies basic gravity and horizontal deceleration
 * (samus_attr->x30).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirS_Phys(HSD_GObj* gobj)
{
    u8 _[24];

    Fighter* fp = GET_FIGHTER(gobj);
    ftSs_DatAttrs* samus_attr = getFtSpecialAttrs(fp);
    Fighter* fighter2;
    ftCommon_FallBasic(fp);
    fighter2 = fp;
    ftCommon_CalcSelfAccel_Deaccel(fighter2, samus_attr->x30);
}

/**
 * @brief Side-B (Homing Missile): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_Coll(HSD_GObj* gobj)
{
    if (!ft_800827A0(gobj)) {
        ftCo_Fall_Enter(gobj); // Slip off ledge into Fall
    }
}

/**
 * @brief Side-B (Homing Missile): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirS_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_80082B1C(gobj); // Handle landing
    }
}

/**
 * @brief Side-B (Super Missile): Grounded animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialSSmash_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj); // Return to grounded wait
    }
}

/**
 * @brief Side-B (Super Missile): Aerial animation callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirSSmash_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj); // Transition to aerial fall
    }
}

/**
 * @brief Side-B (Super Missile): Grounded IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialSSmash_IASA(HSD_GObj* gobj) {}

/**
 * @brief Side-B (Super Missile): Aerial IASA callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirSSmash_IASA(HSD_GObj* gobj) {}

/**
 * @brief Side-B (Super Missile): Grounded physics callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialSSmash_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Side-B (Super Missile): Aerial physics callback.
 * @details Applies basic gravity and horizontal deceleration
 * (samus_attr->x30).
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirSSmash_Phys(HSD_GObj* gobj)
{
    u8 _[40];

    Fighter* fighter2;
    Fighter* fp;
    ftSs_DatAttrs* samus_attr;
    ftSs_DatAttrs* samus_attr2;
    fp = fighter2 = GET_FIGHTER(gobj);
    samus_attr = getFtSpecialAttrs(fp);
    ftCommon_FallBasic(fp);
    samus_attr2 = samus_attr;
    ftCommon_CalcSelfAccel_Deaccel(fp, samus_attr2->x30);
}

/**
 * @brief Side-B (Super Missile): Grounded collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialSSmash_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_Fall_Enter(gobj); // Slip off ledge into Fall
    }
}

/**
 * @brief Side-B (Super Missile): Aerial collision callback.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialAirSSmash_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ft_80082B1C(gobj); // Handle landing
    }
}

/**
 * @brief Side-B (Missile): Cleans up visual effects and clears active flag.
 * @param gobj Samus fighter game object pointer
 */
void ftSs_SpecialS_8012A640(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    efLib_DestroyAll(gobj);
    fp->u.ss.x2244 = 0;
}
