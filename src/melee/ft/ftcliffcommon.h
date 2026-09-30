/**
 * @file ftcliffcommon.h
 * @brief Common ledge grab (CliffCatch) logic
 * @details Handles determining if a fighter can grab a ledge, snapping to it, and the initial catch animation state.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_081298
#define GALE01_081298

#include <melee/ft/forward.h>

/**
 * @brief Checks if a fighter can grab a ledge and initiates the grab if so
 * @param gobj The Fighter's GObj
 * @return true if the fighter grabbed the ledge, false otherwise
 */
/* 081298 */ bool ftCliffCommon_80081298(Fighter_GObj* gobj);

/**
 * @brief Initiates the CliffCatch action state (grabbing the ledge)
 * @param gobj The Fighter's GObj
 */
/* 081370 */ void ftCliffCommon_80081370(Fighter_GObj* gobj);

/**
 * @brief Animation callback for CliffCatch (catching the ledge)
 * @param gobj The Fighter's GObj
 */
/* 081504 */ void ftCo_CliffCatch_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
/* 081540 */ void ftCo_CliffCatch_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
/* 081544 */ void ftCo_CliffCatch_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for CliffCatch
 * @param gobj The Fighter's GObj
 */
/* 0815E4 */ void ftCo_CliffCatch_Coll(Fighter_GObj* gobj);

/**
 * @brief Camera callback for ledge states
 * @param gobj The Fighter's GObj
 */
/* 081644 */ void ftCo_Cliff_Cam(Fighter_GObj* gobj);

#endif
