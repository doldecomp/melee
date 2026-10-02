/**
 * @file ftfoxspecialn.h
 * @brief Header for Neutral-B (Blaster)
 * @details Declarations for Fox and Falco's Neutral-B special move (Blaster),
 * handling blaster gun spawning, laser shot generation, firing loops, and
 * throw lasers. Module prefix: ftFx
 */

#ifndef GALE01_0E5CB0
#define GALE01_0E5CB0

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/**
 * @brief Get Fox/Falco's right thumb bone position with fighter offset for
 * Blaster muzzle
 * @param gobj The fighter's game object
 * @param[out] pos Output vector for world joint position
 */
/* 0E5CB0 */ void ftFx_SpecialN_FtGetHoldJoint(HSD_GObj* gobj, Vec3* pos);

/**
 * @brief Get Fox/Falco's right thumb bone position with item offset for
 * Blaster muzzle
 * @param gobj The fighter's game object
 * @param[out] pos Output vector for world joint position
 */
/* 0E5D20 */ void ftFx_SpecialN_ItGetHoldJoint(HSD_GObj* gobj, Vec3* pos);

/**
 * @brief Callback when action changes during Blaster move
 * @param gobj The fighter's game object
 */
/* 0E5D90 */ void ftFx_SpecialN_OnChangeAction(HSD_GObj* gobj);

/**
 * @brief Checks if Blaster gun item GObj is NULL
 * @param gobj The fighter's game object
 * @return True if Blaster GObj is NULL, false otherwise
 */
/* 0E5DC4 */ bool ftFx_SpecialN_CheckRemoveBlaster(HSD_GObj* gobj);

/**
 * @brief Returns sub-action index (0..5 for SpecialN, 6..8 for throws)
 * @param gobj The fighter's game object
 * @return Sub-action index enum value
 */
/* 0E5DE4 */ s32 ftFx_SpecialN_GetBlasterAction(HSD_GObj* gobj);

/**
 * @brief Checks if current action is a Blaster action and item should persist
 * @param gobj The fighter's game object
 * @return True if valid Blaster action, false otherwise
 */
/* 0E5E38 */ bool ftFx_SpecialN_CheckBlasterAction(HSD_GObj* gobj);

/**
 * @brief Clears blaster pointer from fighter without destroying entity
 * @param gobj The fighter's game object
 */
/* 0E5E90 */ void ftFx_SpecialN_ClearBlaster(HSD_GObj* gobj);

/**
 * @brief Destroys Blaster item entity and clears pointer
 * @param gobj The fighter's game object
 */
/* 0E5EBC */ void ftFx_SpecialN_RemoveBlaster(HSD_GObj* gobj);

/**
 * @brief Animation script accessory callback to fire laser shot
 * @param gobj The fighter's game object
 */
/* 0E5F28 */ void ftFx_SpecialN_CreateBlasterShot(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Neutral-B (Blaster)
 * @param gobj The fighter's game object
 */
/* 0E608C */ void ftFx_SpecialN_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Neutral-B (Blaster)
 * @param gobj The fighter's game object
 */
/* 0E61A8 */ void ftFx_SpecialAirN_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E62A4 */ void ftFx_SpecialNStart_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6368 */ void ftFx_SpecialNLoop_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E65BC */ void ftFx_SpecialNEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E667C */ void ftFx_SpecialAirNStart_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6740 */ void ftFx_SpecialAirNLoop_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E69BC */ void ftFx_SpecialAirNEnd_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Neutral-B draw weapon (checks B input)
 * @param gobj The fighter's game object
 */
/* 0E6AB4 */ void ftFx_SpecialNStart_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Neutral-B firing loop (checks B input for
 * repeat fire)
 * @param gobj The fighter's game object
 */
/* 0E6ADC */ void ftFx_SpecialNLoop_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Neutral-B holster weapon (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E6B04 */ void ftFx_SpecialNEnd_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Neutral-B draw weapon (checks B input)
 * @param gobj The fighter's game object
 */
/* 0E6B08 */ void ftFx_SpecialAirNStart_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Neutral-B firing loop (checks B input for
 * repeat fire)
 * @param gobj The fighter's game object
 */
/* 0E6B30 */ void ftFx_SpecialAirNLoop_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Neutral-B holster weapon (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0E6B58 */ void ftFx_SpecialAirNEnd_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E6B5C */ void ftFx_SpecialNStart_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6B7C */ void ftFx_SpecialNLoop_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E6B9C */ void ftFx_SpecialNEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E6BBC */ void ftFx_SpecialAirNStart_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6BDC */ void ftFx_SpecialAirNLoop_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E6BFC */ void ftFx_SpecialAirNEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E6C1C */ void ftFx_SpecialNStart_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6C3C */ void ftFx_SpecialNLoop_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E6C5C */ void ftFx_SpecialNEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Neutral-B draw weapon
 * @param gobj The fighter's game object
 */
/* 0E6C7C */ void ftFx_SpecialAirNStart_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Neutral-B firing loop
 * @param gobj The fighter's game object
 */
/* 0E6C9C */ void ftFx_SpecialAirNLoop_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Neutral-B holster weapon
 * @param gobj The fighter's game object
 */
/* 0E6CBC */ void ftFx_SpecialAirNEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Animation callback for Fox and Falco's throws that fire Blaster
 * lasers
 * @details Fires blaster shots into opponents during Back Throw, Up Throw,
 * Down Throw.
 * @param gobj The fighter's game object
 */
/* 0E6CDC */ void ftFx_Throw_Anim(HSD_GObj* gobj);

#endif
