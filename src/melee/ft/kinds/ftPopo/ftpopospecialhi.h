#ifndef GALE01_1211B4
#define GALE01_1211B4

/**
 * @file ftpopospecialhi.h
 * @brief Up-B: Belay (Tether recovery & partner throw) declarations
 * @details Declarations for grounded and aerial Belay move logic for Ice
 * Climbers (Popo/Nana). Covers partnered belay throw, solo failure, and Popo
 * rising states. Module prefix: ftPp
 */

#include <melee/ft/forward.h>

/**
 * @brief Enter grounded Up-B: Belay
 * @param gobj Fighter game object
 */
/* 1211B4 */ void ftPp_SpecialHi_Enter(Fighter_GObj* gobj);

/**
 * @brief Enter aerial Up-B: Belay
 * @param gobj Fighter game object
 */
/* 12122C */ void ftPp_SpecialAirHi_Enter(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded partnered Belay start
 * @details Verifies partner Nana is alive and within range; branches to solo
 * fail if missing.
 * @param gobj Fighter game object
 */
/* 1212C4 */ void ftPp_SpecialHiStart_0_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
/* 1213CC */ void ftPp_SpecialAirHiStart_0_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA turnaround callback for grounded partnered Belay start
 * @param gobj Fighter game object
 */
/* 1214D4 */ void ftPp_SpecialHiStart_0_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA turnaround callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
/* 121558 */ void ftPp_SpecialAirHiStart_0_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded partnered Belay start
 * @param gobj Fighter game object
 */
/* 1215DC */ void ftPp_SpecialHiStart_0_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
/* 121680 */ void ftPp_SpecialAirHiStart_0_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded partnered Belay start
 * @param gobj Fighter game object
 */
/* 121740 */ void ftPp_SpecialHiStart_0_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial partnered Belay start
 * @param gobj Fighter game object
 */
/* 12177C */ void ftPp_SpecialAirHiStart_0_Coll(Fighter_GObj* gobj);

/**
 * @brief Ground-to-air transition for partnered Belay start
 * @param gobj Fighter game object
 */
/* 1217EC */ void ftPp_SpecialHi_801217EC(Fighter_GObj* gobj);

/**
 * @brief Air-to-ground transition for partnered Belay start
 * @param gobj Fighter game object
 */
/* 12184C */ void ftPp_SpecialHi_8012184C(Fighter_GObj* gobj);

/**
 * @brief Initialize grounded partnered Belay start motion state
 * @param gobj Fighter game object
 */
/* 1218AC */ void ftPp_SpecialHi_801218AC(Fighter_GObj* gobj);

/**
 * @brief Initialize aerial partnered Belay start motion state
 * @param gobj Fighter game object
 */
/* 1218F8 */ void ftPp_SpecialHi_801218F8(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded partnered Belay throw
 * @details Checks if Nana reached peak and initiated the upward pull.
 * @param gobj Fighter game object
 */
/* 121944 */ void ftPp_SpecialHiThrow_0_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
/* 1219F4 */ void ftPp_SpecialAirHiThrow_0_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121AC8 */ void ftPp_SpecialHiThrow_0_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121ACC */ void ftPp_SpecialAirHiThrow_0_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121AD0 */ void ftPp_SpecialHiThrow_0_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121B74 */ void ftPp_SpecialAirHiThrow_0_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121C34 */ void ftPp_SpecialHiThrow_0_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121C70 */ void ftPp_SpecialAirHiThrow_0_Coll(Fighter_GObj* gobj);

/**
 * @brief Ground-to-air transition for partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121CE0 */ void ftPp_SpecialHi_80121CE0(Fighter_GObj* gobj);

/**
 * @brief Air-to-ground transition for partnered Belay throw
 * @param gobj Fighter game object
 */
/* 121D40 */ void ftPp_SpecialHi_80121D40(Fighter_GObj* gobj);

/**
 * @brief Transition to grounded partnered Belay throw state
 * @param gobj Fighter game object
 */
/* 121DA0 */ void ftPp_SpecialHi_80121DA0(Fighter_GObj* gobj);

/**
 * @brief Transition to aerial partnered Belay throw state
 * @param gobj Fighter game object
 */
/* 121DD8 */ void ftPp_SpecialHi_80121DD8(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded solo Belay start (failure)
 * @param gobj Fighter game object
 */
/* 121E10 */ void ftPp_SpecialHiStart_1_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial solo Belay start (failure)
 * @param gobj Fighter game object
 */
/* 121E4C */ void ftPp_SpecialAirHiStart_1_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
/* 121EB0 */ void ftPp_SpecialHiStart_1_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA callback for aerial solo Belay start
 * @param gobj Fighter game object
 */
/* 121EB4 */ void ftPp_SpecialAirHiStart_1_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
/* 121EB8 */ void ftPp_SpecialHiStart_1_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial solo Belay start
 * @param gobj Fighter game object
 */
/* 121ED8 */ void ftPp_SpecialAirHiStart_1_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded solo Belay start
 * @param gobj Fighter game object
 */
/* 121F2C */ void ftPp_SpecialHiStart_1_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial solo Belay start
 * @param gobj Fighter game object
 */
/* 121F68 */ void ftPp_SpecialAirHiStart_1_Coll(Fighter_GObj* gobj);

/**
 * @brief Ground-to-air transition for solo Belay start
 * @param gobj Fighter game object
 */
/* 121FD8 */ void ftPp_SpecialHi_80121FD8(Fighter_GObj* gobj);

/**
 * @brief Air-to-ground transition for solo Belay start
 * @param gobj Fighter game object
 */
/* 122038 */ void ftPp_SpecialHi_80122038(Fighter_GObj* gobj);

/**
 * @brief Transition to grounded solo Belay fail state
 * @param gobj Fighter game object
 */
/* 122098 */ void ftPp_SpecialHi_80122098(Fighter_GObj* gobj);

/**
 * @brief Transition to aerial solo Belay fail state
 * @param gobj Fighter game object
 */
/* 1220D4 */ void ftPp_SpecialHi_801220D4(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
/* 122110 */ void ftPp_SpecialHiThrow_1_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
/* 12214C */ void ftPp_SpecialAirHiThrow_1_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
/* 1221AC */ void ftPp_SpecialHiThrow_1_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
/* 1221B0 */ void ftPp_SpecialAirHiThrow_1_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
/* 1221B4 */ void ftPp_SpecialHiThrow_1_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
/* 1221D4 */ void ftPp_SpecialAirHiThrow_1_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded solo Belay throw
 * @param gobj Fighter game object
 */
/* 122228 */ void ftPp_SpecialHiThrow_1_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial solo Belay throw
 * @param gobj Fighter game object
 */
/* 122264 */ void ftPp_SpecialAirHiThrow_1_Coll(Fighter_GObj* gobj);

/**
 * @brief Ground-to-air transition for solo Belay throw
 * @param gobj Fighter game object
 */
/* 1222E8 */ void ftPp_SpecialHi_801222E8(Fighter_GObj* gobj);

/**
 * @brief Transition to grounded solo Belay throw state
 * @param gobj Fighter game object
 */
/* 122348 */ void ftPp_SpecialHi_80122348(Fighter_GObj* gobj);

/**
 * @brief Transition to aerial solo Belay throw state
 * @param gobj Fighter game object
 */
/* 122380 */ void ftPp_SpecialHi_80122380(Fighter_GObj* gobj);

/**
 * @brief Animation callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 1223B8 */ void ftPp_SpecialHiThrow2_Anim(Fighter_GObj* gobj);

/**
 * @brief Animation callback for aerial Popo rising Belay state
 * @details High upward yank into the air, ending in Special Fall (helpless).
 * @param gobj Fighter game object
 */
/* 122410 */ void ftPp_SpecialAirHiThrow2_Anim(Fighter_GObj* gobj);

/**
 * @brief IASA callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 12248C */ void ftPp_SpecialHiThrow2_IASA(Fighter_GObj* gobj);

/**
 * @brief IASA callback for aerial Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 122490 */ void ftPp_SpecialAirHiThrow2_IASA(Fighter_GObj* gobj);

/**
 * @brief Physics callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 122494 */ void ftPp_SpecialHiThrow2_Phys(Fighter_GObj* gobj);

/**
 * @brief Physics callback for aerial Popo rising Belay state
 * @details Applies air drift control and updates rope tether anchor position.
 * @param gobj Fighter game object
 */
/* 122538 */ void ftPp_SpecialAirHiThrow2_Phys(Fighter_GObj* gobj);

/**
 * @brief Collision callback for grounded Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 122664 */ void ftPp_SpecialHiThrow2_Coll(Fighter_GObj* gobj);

/**
 * @brief Collision callback for aerial Popo rising Belay state
 * @details Handles ceiling clank, wall contact, and landing into
 * LandingFallSpecial.
 * @param gobj Fighter game object
 */
/* 1226A0 */ void ftPp_SpecialAirHiThrow2_Coll(Fighter_GObj* gobj);

/**
 * @brief Ground-to-air transition for Popo rising Belay state
 * @param gobj Fighter game object
 */
/* 1227AC */ void ftPp_SpecialHi_801227AC(Fighter_GObj* gobj);

/**
 * @brief Transition Popo to rising upward Belay state when yanked by Nana
 * @param gobj Fighter game object
 */
/* 12280C */ void ftPp_SpecialHi_8012280C(Fighter_GObj* gobj);

/**
 * @brief Clean up Blizzard particle effects and model tilt rotation
 * @param gobj Fighter game object
 */
/* 122898 */ void ftPp_SpecialHi_80122898(Fighter_GObj* gobj);

#endif
