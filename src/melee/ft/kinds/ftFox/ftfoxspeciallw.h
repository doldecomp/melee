/**
 * @file ftfoxspeciallw.h
 * @brief Header for Down-B (Reflector / Shine)
 * @details Declarations for Fox and Falco's Down-B special move
 * (Reflector/Shine), including start, active loop, reflection hits,
 * turnaround, and release lag. Module prefix: ftFx
 */

#ifndef GALE01_0E83E0
#define GALE01_0E83E0

#include <sysdolphin/baselib/forward.h>

/**
 * @brief Spawns looping hexagonal Reflector shield effect
 * @param gobj The fighter's game object
 */
/* 0E83E0 */ void ftFx_SpecialLw_CreateLoopGFX(HSD_GObj* gobj);

/**
 * @brief Spawns initial activation flash effect for Reflector
 * @param gobj The fighter's game object
 */
/* 0E845C */ void ftFx_SpecialLw_CreateStartGFX(HSD_GObj* gobj);

/**
 * @brief Spawns projectile deflection sparkle effect for Reflector
 * @param gobj The fighter's game object
 */
/* 0E84D8 */ void ftFx_SpecialLw_CreateReflectGFX(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Down-B (Reflector / Shine)
 * @details Active on frame 1; sets up reflection attributes.
 * @param gobj The fighter's game object
 */
/* 0E8560 */ void ftFx_SpecialLw_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Down-B (Reflector / Shine)
 * @details Active on frame 1; stalls vertical momentum (self_vel.y = 0).
 * @param gobj The fighter's game object
 */
/* 0E85EC */ void ftFx_SpecialAirLw_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Down-B (Reflector) startup
 * @param gobj The fighter's game object
 */
/* 0E8694 */ void ftFx_SpecialLwStart_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Down-B (Reflector) startup
 * @param gobj The fighter's game object
 */
/* 0E8720 */ void ftFx_SpecialAirLwStart_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Down-B (Reflector) startup
 * @param gobj The fighter's game object
 */
/* 0E87AC */ void ftFx_SpecialLwStart_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Down-B (Reflector) startup
 * @param gobj The fighter's game object
 */
/* 0E87D0 */ void ftFx_SpecialAirLwStart_IASA(HSD_GObj* gobj);

/**
 * @brief Checks for platform drop-through input while in Down-B startup
 * @param gobj The fighter's game object
 * @return True if platform drop initiated, false otherwise
 */
/* 0E87D4 */ bool ftFx_SpecialLwStart_CheckPass(HSD_GObj* gobj);

/**
 * @brief Drops through platform during Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E881C */ void ftFx_SpecialLwStart_Pass(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E8864 */ void ftFx_SpecialLwStart_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E8884 */ void ftFx_SpecialAirLwStart_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E88E4 */ void ftFx_SpecialLwStart_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E8920 */ void ftFx_SpecialAirLwStart_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E895C */ void ftFx_SpecialLwStart_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Down-B startup
 * @param gobj The fighter's game object
 */
/* 0E89BC */ void ftFx_SpecialAirLwStart_AirToGround(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8A24 */ void ftFx_SpecialLwLoop_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8A9C */ void ftFx_SpecialAirLwLoop_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Down-B active loop
 * @details Implements Jump-Cancel Shine (ftCo_Jump_CheckInput), turnaround,
 * and platform drop.
 * @param gobj The fighter's game object
 */
/* 0E8B14 */ void ftFx_SpecialLwLoop_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8B64 */ void ftFx_SpecialAirLwLoop_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8C34 */ void ftFx_SpecialLwLoop_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8C68 */ void ftFx_SpecialAirLwLoop_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8CDC */ void ftFx_SpecialLwLoop_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Down-B active loop
 * @param gobj The fighter's game object
 */
/* 0E8D18 */ void ftFx_SpecialAirLwLoop_Coll(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E8FDC */ void ftFx_SpecialLwTurn_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E90EC */ void ftFx_SpecialAirLwTurn_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Down-B turnaround (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E91FC */ void ftFx_SpecialLwTurn_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Down-B turnaround (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E9200 */ void ftFx_SpecialAirLwTurn_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E9204 */ void ftFx_SpecialLwTurn_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E9238 */ void ftFx_SpecialAirLwTurn_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E92AC */ void ftFx_SpecialLwTurn_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E92E8 */ void ftFx_SpecialAirLwTurn_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E9324 */ void ftFx_SpecialLwTurn_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Down-B turnaround
 * @param gobj The fighter's game object
 */
/* 0E93A4 */ void ftFx_SpecialAirLwTurn_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Checks for stick turnaround input during Reflector loop
 * @param gobj The fighter's game object
 * @return True if turnaround initiated, false otherwise
 */
/* 0E942C */ bool ftFx_SpecialLwTurn_Check(HSD_GObj* gobj);

/**
 * @brief Checks transition conditions exiting Reflector hit (to End or Loop)
 * @param gobj The fighter's game object
 * @return True if returning to loop, false if entering end lag
 */
/* 0E9564 */ bool ftFx_SpecialLwHit_Check(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded projectile reflection hit
 * @param gobj The fighter's game object
 */
/* 0E965C */ void ftFx_SpecialLwHit_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial projectile reflection hit
 * @param gobj The fighter's game object
 */
/* 0E97B4 */ void ftFx_SpecialAirLwHit_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Reflector hit (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E9844 */ void ftFx_SpecialLwHit_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Reflector hit (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E9848 */ void ftFx_SpecialAirLwHit_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E984C */ void ftFx_SpecialLwHit_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E9880 */ void ftFx_SpecialAirLwHit_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E98F4 */ void ftFx_SpecialLwHit_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E9930 */ void ftFx_SpecialAirLwHit_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E996C */ void ftFx_SpecialLwHit_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Reflector hit
 * @param gobj The fighter's game object
 */
/* 0E99D4 */ void ftFx_SpecialAirLwHit_AirToGround(HSD_GObj* gobj);

/**
 * @brief Sets reflection active flag and hit callback
 * @param gobj The fighter's game object
 */
/* 0E9A44 */ void ftFx_SpecialLwHit_SetCall(HSD_GObj* gobj);

/**
 * @brief Action State initialization when Reflector reflects a projectile
 * @param gobj The fighter's game object
 */
/* 0E9A68 */ void ftFx_SpecialLwHit_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Down-B release end lag
 * @param gobj The fighter's game object
 */
/* 0E9B40 */ void ftFx_SpecialLwEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Down-B release end lag
 * @param gobj The fighter's game object
 */
/* 0E9B84 */ void ftFx_SpecialAirLwEnd_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Down-B end lag (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E9BC8 */ void ftFx_SpecialLwEnd_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Down-B end lag (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E9BCC */ void ftFx_SpecialAirLwEnd_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9BD0 */ void ftFx_SpecialLwEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9BF0 */ void ftFx_SpecialAirLwEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9C50 */ void ftFx_SpecialLwEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9C8C */ void ftFx_SpecialAirLwEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9CC8 */ void ftFx_SpecialLwEnd_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9D24 */ void ftFx_SpecialAirLwEnd_AirToGround(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9D88 */ void ftFx_SpecialLwEnd_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Down-B end lag
 * @param gobj The fighter's game object
 */
/* 0E9DC0 */ void ftFx_SpecialAirLwEnd_Enter(HSD_GObj* gobj);

#endif
