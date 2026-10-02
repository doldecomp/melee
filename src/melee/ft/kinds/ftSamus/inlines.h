/**
 * @file inlines.h
 * @brief Inline helper functions for Samus
 * @details Provides inline utilities for setting damage/death callbacks to
 * clean up Samus-specific entities (such as active Charge Shots) and managing
 * visual effects. Module prefix: ftSs
 */

#ifndef MELEE_FT_CHARA_FTSAMUS_INLINES_H
#define MELEE_FT_CHARA_FTSAMUS_INLINES_H

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <stddef.h>

#include <melee/ef/eflib.h>
#include <melee/ft/inlines.h>
#include <melee/ft/kinds/ftSamus/ftsamus.h>
#include <melee/ft/kinds/ftSamus/types.h>
#include <melee/ft/types.h>
#include <melee/it/kinds/itsamuschargeshot.h>
#include <sysdolphin/baselib/gobj.h>

/**
 * @brief Sets damage and death callbacks to ftSs_Init_80128428 to clean up
 *        Charge Shot and missile effects upon taking damage or dying.
 * @param gobj Samus fighter game object pointer
 */
static inline void ftSamus_updateDamageDeathCBs(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->take_dmg_cb = ftSs_Init_80128428;
    fp->death2_cb = ftSs_Init_80128428;
}

/**
 * @brief Clears effect tracking flag x2234.
 * @param gobj Samus fighter game object pointer
 */
static inline void ftSamus_SetAttrx2334(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->u.ss.x2234 = 0;
}

/**
 * @brief Destroys all active special move effects if the tracking flag is set.
 * @param gobj Samus fighter game object pointer
 */
static inline void ftSamus_destroyAllEF(HSD_GObj* gobj)
{
    if (gobj) {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->u.ss.x2234) {
            efLib_DestroyAll(gobj);
            fp->u.ss.x2234 = 0;
        }
    }
}

/**
 * @brief Destroys active Charge Shot projectile entity and cleans up visual
 * effects.
 * @param gobj Samus fighter game object pointer
 */
static inline void ftSamus_UnkAndDestroyAllEF(HSD_GObj* gobj)
{
    if (gobj != NULL) {
        Fighter* fp = gobj->user_data;
        Item_GObj* charge_gobj = fp->u.ss.x222C;
        if (charge_gobj != NULL) {
            it_802B5974(charge_gobj);
            fp->u.ss.x222C = NULL;
        }
        ftSamus_destroyAllEF(gobj);
    }
}

#endif
