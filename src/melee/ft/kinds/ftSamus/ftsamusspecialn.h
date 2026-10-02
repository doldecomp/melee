/**
 * @file ftsamusspecialn.h
 * @brief Neutral-B: Charge Shot declarations for Samus
 * @details Function declarations for Samus's Neutral-B special move (Charge
 * Shot), including charging loop, cancel, firing, air recoil, and missile
 * helper callbacks. Module prefix: ftSs
 */

#ifndef GALE01_1122D8
#define GALE01_1122D8

#include <melee/ft/forward.h>

/**
 * @brief Neutral-B (Charge Shot): Clears Charge Shot item reference and
 * destroys visual effects.
 * @param gobj Samus fighter game object pointer
 */
/* 1291F0 */ void ftSs_SpecialN_801291F0(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Resets charge level to 0 and clears visual
 * effects.
 * @param gobj Samus fighter game object pointer
 */
/* 129258 */ void ftSs_SpecialN_80129258(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 12954C */ void ftSs_SpecialN_Enter(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial action state entry callback.
 * @param gobj Samus fighter game object pointer
 */
/* 1295F0 */ void ftSs_SpecialAirN_Enter(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded startup animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129684 */ void ftSs_SpecialNStart_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129774 */ void ftSs_SpecialNHold_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129940 */ void ftSs_SpecialNCancel_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded firing animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 1299D0 */ void ftSs_SpecialN_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial startup animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129A14 */ void ftSs_SpecialAirNStart_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial firing animation callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129A98 */ void ftSs_SpecialAirN_Anim(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded startup IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129B18 */ void ftSs_SpecialNStart_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop IASA callback (checks
 * shield cancel / B-fire).
 * @param gobj Samus fighter game object pointer
 */
/* 129B1C */ void ftSs_SpecialNHold_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129C78 */ void ftSs_SpecialNCancel_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded firing IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129C7C */ void ftSs_SpecialN_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial startup IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129C80 */ void ftSs_SpecialAirNStart_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial firing IASA callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129C84 */ void ftSs_SpecialAirN_IASA(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded startup physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129C88 */ void ftSs_SpecialNStart_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129CA8 */ void ftSs_SpecialNHold_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129CC8 */ void ftSs_SpecialNCancel_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded firing physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129CE8 */ void ftSs_SpecialN_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial startup physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129D08 */ void ftSs_SpecialAirNStart_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial firing physics callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129D28 */ void ftSs_SpecialAirN_Phys(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded startup collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129D48 */ void ftSs_SpecialNStart_Coll(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charging loop collision callback
 * (ledge-fall auto-fire).
 * @param gobj Samus fighter game object pointer
 */
/* 129DC8 */ void ftSs_SpecialNHold_Coll(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded charge cancel collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129E68 */ void ftSs_SpecialNCancel_Coll(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Grounded firing collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129EE8 */ void ftSs_SpecialN_Coll(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial startup collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129F68 */ void ftSs_SpecialAirNStart_Coll(Fighter_GObj* gobj);

/**
 * @brief Neutral-B (Charge Shot): Aerial firing collision callback.
 * @param gobj Samus fighter game object pointer
 */
/* 129FE8 */ void ftSs_SpecialAirN_Coll(Fighter_GObj* gobj);

/**
 * @brief Side-B (Missile): Returns current missile count / identifier.
 * @param gobj Samus fighter game object pointer
 * @return Missile count value
 */
/* 12A068 */ int ftSs_SpecialS_8012A068(Fighter_GObj* gobj);

/**
 * @brief Side-B (Missile): Accessory callback that instantiates and fires a
 * missile item.
 * @param gobj Samus fighter game object pointer
 */
/* 12A074 */ void ftSs_SpecialS_8012A074(Fighter_GObj* gobj);

#endif
