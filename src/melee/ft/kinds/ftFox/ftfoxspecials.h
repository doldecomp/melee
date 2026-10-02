/**
 * @file ftfoxspecials.h
 * @brief Header for Side-B (Fox Illusion / Falco Phantasm)
 * @details Declarations for Fox's Side-B (Fox Illusion) and Falco's Side-B
 * (Phantasm), including startup, dash travel, shortening via B input, and
 * ending freefall. Module prefix: ftFx
 */

#ifndef GALE01_0E9DF8
#define GALE01_0E9DF8

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/**
 * @brief Spawns dash trail particle effects for Fox Illusion / Falco Phantasm
 * @param gobj The fighter's game object
 */
/* 0E9DF8 */ void ftFx_SpecialS_CreateGFX(HSD_GObj* gobj);

/**
 * @brief Checks if fighter has exited all Illusion motion states to remove
 * ghost
 * @param gobj The fighter's game object
 * @return True if ghost should be removed, false if in Illusion
 */
/* 0E9E78 */ bool ftFx_SpecialS_CheckGhostRemove(HSD_GObj* gobj);

/**
 * @brief Returns command variable 2 from fighter struct
 * @param gobj The fighter's game object
 * @return Value of cmd_vars[2]
 */
/* 0E9EA0 */ s32 ftFx_SpecialS_GetCmdVar2(HSD_GObj* gobj);

/**
 * @brief Copies historical ghost trail position at specified index
 * @param gobj The fighter's game object
 * @param index Index in ghost position ring buffer (0..3)
 * @param[out] ghostPos Destination vector
 */
/* 0E9EAC */ void ftFx_SpecialS_CopyGhostPosIndexed(HSD_GObj* gobj, s32 index,
                                                    Vec3* ghostPos);

/**
 * @brief Returns model rotation at specified index in ghost history buffer
 * @param gobj The fighter's game object
 * @param index Index in blend frames ring buffer (0..3)
 * @return Rotation float value
 */
/* 0E9ED4 */ float ftFx_SpecialS_ReturnFloatVarIndexed(HSD_GObj* gobj,
                                                       s32 index);

/**
 * @brief Action State initialization for grounded Side-B (Fox Illusion)
 * startup
 * @param gobj The fighter's game object
 */
/* 0E9EE8 */ void ftFx_SpecialSStart_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Side-B (Fox Illusion) startup
 * @param gobj The fighter's game object
 */
/* 0E9F6C */ void ftFx_SpecialAirSStart_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA004 */ void ftFx_SpecialSStart_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA040 */ void ftFx_SpecialAirSStart_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Side-B startup (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0EA07C */ void ftFx_SpecialSStart_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Side-B startup (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0EA080 */ void ftFx_SpecialAirSStart_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA084 */ void ftFx_SpecialSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA0BC */ void ftFx_SpecialAirSStart_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA128 */ void ftFx_SpecialSStart_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA164 */ void ftFx_SpecialAirSStart_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA1D4 */ void ftFx_SpecialSStart_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Side-B startup
 * @param gobj The fighter's game object
 */
/* 0EA234 */ void ftFx_SpecialAirSStart_AirToGround(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA294 */ void ftFx_SpecialS_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA344 */ void ftFx_SpecialAirS_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Side-B dash (Illusion Shorten via B press)
 * @param gobj The fighter's game object
 */
/* 0EA3F4 */ void ftFx_SpecialS_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Side-B dash (Illusion Shorten via B press)
 * @param gobj The fighter's game object
 */
/* 0EA438 */ void ftFx_SpecialAirS_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA47C */ void ftFx_SpecialS_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA534 */ void ftFx_SpecialAirS_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA5EC */ void ftFx_SpecialS_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA628 */ void ftFx_SpecialAirS_Coll(HSD_GObj* gobj);

/**
 * @brief Ground to air transition during Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA698 */ void ftFx_SpecialS_GroundToAir(HSD_GObj* gobj);

/**
 * @brief Air to ground transition during Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA700 */ void ftFx_SpecialAirS_AirToGround(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA768 */ void ftFx_SpecialS_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Side-B dash
 * @param gobj The fighter's game object
 */
/* 0EA838 */ void ftFx_SpecialAirS_Enter(HSD_GObj* gobj);

/**
 * @brief Animation callback for grounded Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EA908 */ void ftFx_SpecialSEnd_Anim(HSD_GObj* gobj);

/**
 * @brief Animation callback for aerial Side-B end lag / freefall
 * @param gobj The fighter's game object
 */
/* 0EA944 */ void ftFx_SpecialAirSEnd_Anim(HSD_GObj* gobj);

/**
 * @brief IASA callback for grounded Side-B end lag (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0EA9A4 */ void ftFx_SpecialSEnd_IASA(HSD_GObj* gobj);

/**
 * @brief IASA callback for aerial Side-B end lag (no interrupts)
 * @param gobj The fighter's game object
 */
/* 0EA9A8 */ void ftFx_SpecialAirSEnd_IASA(HSD_GObj* gobj);

/**
 * @brief Physics callback for grounded Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EA9AC */ void ftFx_SpecialSEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Physics callback for aerial Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EAA8C */ void ftFx_SpecialAirSEnd_Phys(HSD_GObj* gobj);

/**
 * @brief Collision callback for grounded Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EAB90 */ void ftFx_SpecialSEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Collision callback for aerial Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EABCC */ void ftFx_SpecialAirSEnd_Coll(HSD_GObj* gobj);

/**
 * @brief Action State initialization for grounded Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EAC50 */ void ftFx_SpecialSEnd_Enter(HSD_GObj* gobj);

/**
 * @brief Action State initialization for aerial Side-B end lag
 * @param gobj The fighter's game object
 */
/* 0EACD8 */ void ftFx_SpecialAirSEnd_Enter(HSD_GObj* gobj);

#endif
