/**
 * @file ftfoxspecialhi.h
 * @brief Header for Up-B (Fire Fox / Firebird)
 * @details Declarations for Fox's Up-B move (Fire Fox) and Falco's Firebird,
 * covering charge/hold, launch travel, collision bounces, and
 * landing/freefall. Module prefix: ftFx
 */

#ifndef GALE01_0E7100
#define GALE01_0E7100

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Spawns flame trail particle effect for Up-B (Fire Fox) launch
 * @param gobj The fighter's game object
 */
/* 0E7100 */ void ftFx_SpecialHi_CreateLaunchGFX(HSD_GObj* gobj);

/**
 * @brief Spawns charging flame aura effect for Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E719C */ void ftFx_SpecialHi_CreateChargeGFX(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E7238 */ void ftFx_SpecialHi_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E72C4 */ void ftFx_SpecialAirHiStart_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E7354 */ void ftFx_SpecialHiHold_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E73B4 */ void ftFx_SpecialHiHoldAir_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E7414 */ void ftFx_SpecialHiHold_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E7418 */ void ftFx_SpecialHiHoldAir_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E741C */ void ftFx_SpecialHiHold_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E743C */ void ftFx_SpecialHiHoldAir_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E74A8 */ void ftFx_SpecialHiHold_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E74E4 */ void ftFx_SpecialHiHoldAir_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E7554 */ void ftFx_SpecialHiHold_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Up-B (Fire Fox) charge
 * @param gobj The fighter's game object
 */
/* 0E75C0 */ void ftFx_SpecialHiHoldAir_AirToGround(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7634 */ void ftFx_SpecialHi_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7684 */ void ftFx_SpecialAirHi_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E76D4 */ void ftFx_SpecialHi_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E76D8 */ void ftFx_SpecialAirHi_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E76DC */ void ftFx_SpecialHi_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7758 */ void ftFx_SpecialAirHi_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7800 */ void ftFx_SpecialHi_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E78B4 */ void ftFx_SpecialAirHi_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7A78 */ void ftFx_SpecialHi_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7AF4 */ void ftFx_SpecialAirHi_AirToGround(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Up-B (Fire Fox) launch travel
 * @param gobj The fighter's game object
 */
/* 0E7C98 */ void ftFx_SpecialAirHi_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
/* 0E7E3C */ void ftFx_SpecialHiLanding_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
/* 0E7E78 */ void ftFx_SpecialHiFall_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
/* 0E7ED8 */ void ftFx_SpecialHiLanding_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
/* 0E7EDC */ void ftFx_SpecialHiFall_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
/* 0E7EE0 */ void ftFx_SpecialHiLanding_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
/* 0E7F20 */ void ftFx_SpecialHiFall_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Up-B (Fire Fox) landing
 * @param gobj The fighter's game object
 */
/* 0E7F40 */ void ftFx_SpecialHiLanding_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Up-B (Fire Fox) freefall
 * @param gobj The fighter's game object
 */
/* 0E7FA0 */ void ftFx_SpecialHiFall_Coll(HSD_GObj* gobj);

/**
 * @brief Transitions from aerial Up-B fall to grounded landing
 * @param gobj The fighter's game object
 */
/* 0E7FF0 */ void ftFx_SpecialHiFall_Enter(HSD_GObj* gobj);

/**
 * @brief Handles landing from Up-B (Fire Fox) onto ground
 * @param gobj The fighter's game object
 */
/* 0E8048 */ void ftFx_SpecialHiFall_AirToGround(HSD_GObj* gobj);

/**
 * @brief Handles transition from landing lag to air (sliding off ledge)
 * @param gobj The fighter's game object
 */
/* 0E80C0 */ void ftFx_SpecialHiLanding_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Animation callback for Up-B (Fire Fox) wall/floor rebound
 * @param gobj The fighter's game object
 */
/* 0E8124 */ void ftFx_SpecialHiBound_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for Up-B (Fire Fox) rebound
 * @param gobj The fighter's game object
 */
/* 0E81FC */ void ftFx_SpecialHiBound_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for Up-B (Fire Fox) rebound
 * @param gobj The fighter's game object
 */
/* 0E8200 */ void ftFx_SpecialHiBound_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for Up-B (Fire Fox) rebound
 * @param gobj The fighter's game object
 */
/* 0E824C */ void ftFx_SpecialHiBound_Coll(HSD_GObj* gobj);

/**
 * @brief Action State initialization for Up-B (Fire Fox) wall/floor rebound
 * @param gobj The fighter's game object
 */
/* 0E82E4 */ void ftFx_SpecialHiBound_Enter(HSD_GObj* gobj);

#endif
