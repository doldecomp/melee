/**
 * @file ftfoxappeals.c
 * @brief Fox & Falco's Smash Taunt (Corneria / Venom Star Fox Radio
 * Transmission)
 * @details Implements the secret Smash Taunt easter egg on Corneria and Venom
 * stages. When Fox or Falco taps D-Pad Down for exactly 1 frame, a special
 * 3-stage taunt sequence plays that initiates radio communication with the
 * Star Fox team. Module prefix: ftFx
 */

#include "ftfoxappeals.h"

#include <Runtime/platform.h>

#include <melee/ft/forward.h>

#include "types.h"
#include <melee/ft/fighter.h>
#include <melee/ft/ft_081B.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ft_0892.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/types.h>
#include <melee/gr/grcorneria.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/pltrick.h>

/// Action statistic ID for Fox/Falco's Smash Taunt
#define FTFOX_APPEALS_ATTACKID 0x72

/**
 * @brief Checks if this player has already triggered the Smash Taunt
 * @param fp Pointer to the Fighter data structure
 * @return True if Smash Taunt has been used and stage is active, false
 * otherwise
 */
bool ftFx_AppealS_CheckIfUsed(Fighter* fp)
{
    plActionStats* stats = Player_GetActionStats(fp->player_idx);
    if (pl_800386D8(stats, FTFOX_APPEALS_ATTACKID) != 0 &&
        grCorneria_801E2D14())
    {
        return true;
    }

    return false;
}

/**
 * @brief Checks if any player across all 6 slots has performed the Smash Taunt
 * @return True if any player has executed attack ID 0x72, false otherwise
 */
static inline bool ftFox_CheckAppealSCount(void)
{
    int i;
    plActionStats* stats;

    for (i = 0; i < 6; i++) {
        stats = Player_GetActionStats(i);

        if (pl_800386D8(stats, FTFOX_APPEALS_ATTACKID) != 0) {
            return true;
        }
    }

    return false;
}

/**
 * @brief Checks input conditions to initiate the Smash Taunt
 * @details Requires Fox or Falco on Corneria/Venom (`grCorneria_801E2CE8`),
 * with a precise 1-frame D-Pad Down press (`fp->x682 == 1` and D-Pad Down no
 * longer held), and has not been used yet in the match.
 * @param gobj The fighter's game object
 * @return True if Smash Taunt was successfully started, false otherwise
 */
bool ftFx_AppealS_CheckInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 ftKind = fp->kind;

    if ((ftKind == Ft_Kind_Fox || ftKind == Ft_Kind_Falco) &&
        grCorneria_801E2CE8() &&
        !(fp->input.held_buttons[0] & HSD_PAD_DPADDOWN) && fp->x682 == 1)
    {
        if (ftFox_CheckAppealSCount() == 0) {
            ftFx_AppealS_Enter(gobj);
            pl_80040120(fp->player_idx, fp->is_sub_fighter);
            return true;
        }
    }

    return false;
}

#ifdef MUST_MATCH
static float order_sdata2(void)
{
    (void) 0.0f;
    (void) 1.0f;
}
#endif

/**
 * @brief Determines facing direction index for Smash Taunt animation lookup
 * @param facing Standard positive facing direction (1.0f)
 * @param cur_facing Current fighter facing direction
 * @return 0 for facing right, 1 for facing left
 */
static inline bool ftFox_AppealS_GetLR(float facing, float cur_facing)
{
    return facing == cur_facing ? false : true;
}

/// Motion state table for Smash Taunt [facing_dir: 0=Right, 1=Left][stage:
/// 0=Start, 1=Hold, 2=End]
static s32 ASID_AppealS[2][3] = {
    { ftFx_MS_AppealSStartR, ftFx_MS_AppealSR, ftFx_MS_AppealSEndR },
    { ftFx_MS_AppealSStartL, ftFx_MS_AppealSL, ftFx_MS_AppealSEndL }
};

/**
 * @brief Action State initialization for Smash Taunt
 * @details Resets animation counter and enters Start motion state based on
 * facing direction.
 * @param gobj The fighter's game object
 */
void ftFx_AppealS_Enter(HSD_GObj* gobj)
{
    s32 facingDir;
    s32 actionDir;
    s32 animCount;
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.fx.AppealS.animCount = 0;
    facingDir = ftFox_AppealS_GetLR(1.0f, fp->facing_dir);

    fp->mv.fx.AppealS.facingDir = facingDir;
    fp->x2210.throw_flags = 0;

    actionDir = fp->mv.fx.AppealS.facingDir;
    animCount = fp->mv.fx.AppealS.animCount;

    Fighter_ChangeMotionState(gobj, ASID_AppealS[actionDir][animCount],
                              Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
}

/// Damage/death callback to abort Smash Taunt radio transmission
static void ftFx_AppealS_OnTakeDamage(HSD_GObj* gobj);

/**
 * @brief Animation callback for Smash Taunt
 * @details Triggers stage radio comm event on script flag
 * `ftCheckThrowB3(fp)`: `grCorneria_801E2B80()` for Fox,
 * `grCorneria_801E2C34()` for Falco. Cycles through Start -> Loop -> End, then
 * transitions to idle (`ft_8008A324`).
 * @param gobj The fighter's game object
 */
void ftFx_AppealS_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    PAD_STACK(4);

    if (ftCheckThrowB3(fp)) {
        switch (fp->kind) {
        case Ft_Kind_Fox:
            if (grCorneria_801E2B80()) {
                fp->death1_cb = ftFx_AppealS_OnTakeDamage;
            }
            break;

        case Ft_Kind_Falco:
            if (grCorneria_801E2C34()) {
                fp->death1_cb = ftFx_AppealS_OnTakeDamage;
            }
            break;

        default:
            break;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->mv.fx.AppealS.animCount++;
        if (fp->mv.fx.AppealS.animCount >= 3) {
            ft_8008A324(gobj);
            return;
        }

        Fighter_ChangeMotionState(gobj,
                                  ASID_AppealS[fp->mv.fx.AppealS.facingDir]
                                              [fp->mv.fx.AppealS.animCount],
                                  Ft_MF_None, 0.0f, 1.0f, 0.0f, NULL);
    }
}

/**
 * @brief IASA callback for Smash Taunt (no interrupts permitted)
 * @param gobj The fighter's game object
 */
void ftFx_AppealS_IASA(HSD_GObj* gobj)
{
    return;
}

/**
 * @brief Physics callback for Smash Taunt (standard ground physics)
 * @param gobj The fighter's game object
 */
void ftFx_AppealS_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

/**
 * @brief Collision callback for Smash Taunt (standard ground collision)
 * @param gobj The fighter's game object
 */
void ftFx_AppealS_Coll(HSD_GObj* gobj)
{
    ft_80084280(gobj);
}

/**
 * @brief Callback invoked if Fox/Falco takes damage or dies during Smash Taunt
 * @details Cancels the active Corneria/Venom radio message transmission.
 * @param gobj The fighter's game object
 */
static void ftFx_AppealS_OnTakeDamage(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    grCorneria_801E2AF4();
    fp->death1_cb = NULL;
}
