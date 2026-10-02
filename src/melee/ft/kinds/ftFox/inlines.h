/**
 * @file inlines.h
 * @brief Inline helper functions for Fox
 * @details Contains inline functions used across Fox's special moves, such as
 * Blaster repeat-input detection (Neutral-B).
 * Module prefix: ftFx
 */

#ifndef MELEE_FT_CHARA_FTFOX_INLINES_H
#define MELEE_FT_CHARA_FTFOX_INLINES_H

#include <melee/ft/inlines.h>
#include <melee/ft/types.h>

/**
 * @brief Checks for repeat B button input during Neutral-B (Blaster)
 * @details If B is pressed while the animation script allows firing loops
 * (cmd_vars[0] != 0), enables continuous firing (Short Hop Double Laser).
 * @param gobj The fighter's game object
 */
static inline void ftFox_SpecialN_CheckLoopInput(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0 && (fp->input.pressed_buttons & HSD_PAD_B)) {
        fp->mv.fx.SpecialN.isBlasterLoop = true;
    }
}

#endif
