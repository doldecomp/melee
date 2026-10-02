/**
 * @file ftfoxappeals.h
 * @brief Header for Fox & Falco's Smash Taunt (Corneria/Venom Star Fox Comm)
 * @details Declares functions for triggering and executing Fox and Falco's
 * secret Smash Taunt conversation on Corneria and Venom stages. Module prefix:
 * ftFx
 */

#ifndef GALE01_0E5970
#define GALE01_0E5970

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

/**
 * @brief Check if Smash Taunt has already been performed in this match
 * @param fp Pointer to the Fighter data structure
 * @return True if Smash Taunt was already executed, false otherwise
 */
/* 0E5970 */ bool ftFx_AppealS_CheckIfUsed(Fighter* fp);

/**
 * @brief Check if Fox/Falco tapped D-Pad Down for 1 frame to trigger Smash
 * Taunt
 * @param gobj The fighter's game object
 * @return True if Smash Taunt condition met and initiated, false otherwise
 */
/* 0E59BC */ bool ftFx_AppealS_CheckInput(HSD_GObj* gobj);

/**
 * @brief Fox & Falco's Smash Taunt state initialization
 * @param gobj The fighter's game object
 */
/* 0E5A90 */ void ftFx_AppealS_Enter(HSD_GObj* gobj);

/**
 * @brief Fox & Falco's Smash Taunt Animation callback
 * @param gobj The fighter's game object
 */
/* 0E5B18 */ void ftFx_AppealS_Anim(HSD_GObj* gobj);

/**
 * @brief Fox & Falco's Smash Taunt IASA callback (interrupt check)
 * @param gobj The fighter's game object
 */
/* 0E5C38 */ void ftFx_AppealS_IASA(HSD_GObj* gobj);

/**
 * @brief Fox & Falco's Smash Taunt Physics callback
 * @param gobj The fighter's game object
 */
/* 0E5C3C */ void ftFx_AppealS_Phys(HSD_GObj* gobj);

/**
 * @brief Fox & Falco's Smash Taunt Collision callback
 * @param gobj The fighter's game object
 */
/* 0E5C5C */ void ftFx_AppealS_Coll(HSD_GObj* gobj);

#endif
