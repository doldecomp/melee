/**
 * @file ftdevice.h
 * @brief Fighter stage device interaction and color overlay interface declarations.
 * @details Declares routines for registering and executing stage-specific hazard callbacks,
 * environmental wind generators (e.g. Whispy Woods), capture/barrel cannon devices (e.g. Kongo Jungle),
 * and querying active fighter color animation overlay structures.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_0C0658
#define GALE01_0C0658

#include <Runtime/platform.h>

#include <melee/ft/types.h>

/**
 * @brief Retrieves the active ColorOverlay structure for a fighter.
 * @details Returns primary color overlay (fp->x408) if an animation script pointer is set;
 * otherwise returns secondary color overlay (fp->x488).
 * @param fp Pointer to Fighter instance data
 * @return Pointer to active ColorOverlay structure
 */
/* 0C0658 */ ColorOverlay* ftCo_800C0658(Fighter* fp);

/**
 * @brief Retrieves the active ColorOverlay structure from a fighter GObj.
 * @param gobj Pointer to Fighter_GObj
 * @return Pointer to active ColorOverlay structure
 */
/* 0C0674 */ ColorOverlay* ftCo_800C0674(Fighter_GObj* gobj);

/**
 * @brief Gets the active color animation index / ID of the fighter's current ColorOverlay.
 * @details Used to detect active overlay states (e.g. checking if animation ID == 9 for damage flashing,
 * 106 for hammer flash, 8 for charge flash).
 * @param fp Pointer to Fighter instance data
 * @return Color animation index / identifier
 */
/* 0C0694 */ enum_t ftCo_800C0694(Fighter* fp);

/**
 * @brief Retrieves overlay flag offset from the tertiary color animation buffer (fp->x508).
 * @param fp Pointer to Fighter instance data
 * @return Integer cast of pointer to x7B offset in colanim data
 */
/* 0C06B4 */ int ftCo_800C06B4(Fighter* fp);

/**
 * @brief Resets and clears all registered stage device callbacks.
 * @details Clears wind devices, capture/barrel cannon devices, and stage hazard collision devices.
 * Invoked during stage loading and match initialization.
 */
/* 0C06C0 */ void ftCo_800C06C0(void);

/**
 * @brief Registers a stage wind generator callback (e.g. Whispy Woods, Pokemon Stadium fans).
 * @details Stores the wind generator ground GObj, type, and callback in ft_80459A68, and increments
 * the active wind device count in ft_804D6578.
 * @param gobj Stage ground entity generating wind
 * @param arg1 Wind type identifier
 * @param func Wind calculation callback (active_cb)
 */
/* 0C06E8 */ void ftCo_800C06E8(Ground_GObj*, int, void*);

/**
 * @brief Registers a stage capture / bury / barrel cannon device callback (e.g. Kongo Jungle Barrel Cannon).
 * @details Stores the ground GObj, capture type, and callback in ftDevice_BuryThings, and increments
 * ftDevice_BuryThingCount (maximum 2 devices).
 * @param gobj Stage ground entity providing the capture/bury mechanic
 * @param arg1 Capture / bury type identifier
 * @param func Device check and interaction callback
 */
/* 0C0764 */ void ftCo_800C0764(Ground_GObj*, u32, void*);

/**
 * @brief Registers a dynamic stage hazard collision callback (e.g. Great Bay turtle, Brinstar acid, F-Zero cars).
 * @details Stores the ground GObj, collision hazard type, and callback in ft_80459A8C, and increments
 * ft_804D6570.
 * @param gobj Stage ground entity presenting dynamic collision hazard
 * @param arg1 Collision hazard type identifier
 * @param func Hazard collision check and response callback
 */
/* 0C07F8 */ void ftCo_800C07F8(Ground_GObj*, u32, void*);

/* 459A68 */ extern struct ftDeviceUnk3 ft_80459A68[1];          ///< Table of registered stage wind generator devices (capacity: 1)
/* 459A74 */ extern struct ftDeviceUnk5 ftDevice_BuryThings[2]; ///< Table of registered stage capture/bury devices (capacity: 2)
/* 459A8C */ extern struct ftDeviceUnk3 ft_80459A8C[1];          ///< Table of registered stage hazard collision devices (capacity: 1)
/* 4D6570 */ extern int ft_804D6570;                             ///< Number of currently registered stage hazard collision devices
/* 4D6574 */ extern int ftDevice_BuryThingCount;                 ///< Number of currently registered stage capture/bury devices
/* 4D6578 */ extern struct ftDeviceUnk4 ft_804D6578;             ///< Stage wind device registration container (x0: count of active wind devices)

#endif
