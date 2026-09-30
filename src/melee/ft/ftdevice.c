/**
 * @file ftdevice.c
 * @brief Fighter stage device interaction and color overlay implementation.
 * @details Manages fighter interactions with stage-specific devices (e.g. Whispy Woods wind,
 * Kongo Jungle barrel cannons, Brinstar acid, Great Bay turtle, F-Zero cars) and provides
 * accessors for active fighter color overlays and material flash animations.
 * Module prefix: ft (Fighter)
 */

#include "ftdevice.h"

#include "inlines.h"
#include <sysdolphin/baselib/debug.h>

/// @remarks MWCC lays out unreferenced .bss objects in reverse declaration
/// order after referenced objects, so ft_80459A8C must be declared
/// before ftDevice_BuryThings to place these tables at their retail addresses.
struct ftDeviceUnk3 ft_80459A68[1];          ///< Registered stage wind generator table (e.g. Whispy Woods)
struct ftDeviceUnk3 ft_80459A8C[1];          ///< Registered stage hazard collision table (e.g. Brinstar acid, Great Bay turtle)
struct ftDeviceUnk5 ftDevice_BuryThings[2]; ///< Registered stage capture/bury table (e.g. Kongo Jungle barrel cannon)
struct ftDeviceUnk4 ft_804D6578;             ///< Active wind device counter container (x0 = count)
int ftDevice_BuryThingCount;                 ///< Active capture/bury device count
int ft_804D6570;                             ///< Active stage hazard collision device count

/**
 * @brief Retrieves the active ColorOverlay structure for a fighter.
 * @details Returns primary color overlay (fp->x408) if an animation script pointer is set;
 * otherwise returns secondary color overlay (fp->x488).
 * @param fp Pointer to Fighter instance data
 * @return Pointer to active ColorOverlay structure
 */
ColorOverlay* ftCo_800C0658(Fighter* fp)
{
    return (int) fp->x408.x28_colanim.ptr != 0 ? &fp->x408 : &fp->x488;
}

/**
 * @brief Retrieves the active ColorOverlay structure from a fighter GObj.
 * @param gobj Pointer to Fighter_GObj
 * @return Pointer to active ColorOverlay structure
 */
ColorOverlay* ftCo_800C0674(Fighter_GObj* gobj)
{
    return ftCo_800C0658(GET_FIGHTER(gobj));
}

/// @todo Wrong return type. Union?
/**
 * @brief Gets the active color animation index / ID of the fighter's current ColorOverlay.
 * @details Used to detect active overlay states (e.g. checking if animation ID == 9 for damage flashing,
 * 106 for hammer flash, 8 for charge flash).
 * @param fp Pointer to Fighter instance data
 * @return Color animation index / identifier
 */
enum_t ftCo_800C0694(Fighter* fp)
{
    return ftCo_800C0658(fp)->x28_colanim.i;
}

/**
 * @brief Retrieves overlay flag offset from the tertiary color animation buffer (fp->x508).
 * @param fp Pointer to Fighter instance data
 * @return Integer cast of pointer to x7B offset in colanim data
 */
int ftCo_800C06B4(Fighter* fp)
{
    return (int) &fp->x508.x28_colanim.ptr->x7B;
}

/**
 * @brief Resets and clears all registered stage device callbacks.
 * @details Clears wind devices, capture/barrel cannon devices, and stage hazard collision devices.
 * Invoked during stage loading and match initialization.
 */
void ftCo_800C06C0(void)
{
    int i;

    ft_804D6570 = 0;
    ftDevice_BuryThingCount = 0;
    ft_804D6578.x0 = 0;
    ft_80459A68[0].ground = NULL;
    for (i = 0; i < 2; i++) {
        ftDevice_BuryThings[i].x0 = NULL;
    }
    ft_80459A8C[0].ground = NULL;
}

/**
 * @brief Registers a stage wind generator callback (e.g. Whispy Woods, Pokemon Stadium fans).
 * @details Stores the wind generator ground GObj, type, and callback in ft_80459A68, and increments
 * the active wind device count in ft_804D6578. Asserts if capacity (1) is exceeded.
 * @param gobj Stage ground entity generating wind
 * @param arg1 Wind type identifier
 * @param func Wind calculation callback (active_cb)
 */
void ftCo_800C06E8(Ground_GObj* gobj, int arg1, void* func)
{
    int slot_idx;

    // Search for an empty slot in the wind device table
    for (slot_idx = 0; slot_idx < 1; slot_idx++) {
        if (ft_80459A68[slot_idx].ground == NULL) {
            ft_80459A68[slot_idx].ground = gobj;
            ft_80459A68[slot_idx].type = arg1;
            ft_80459A68[slot_idx].active_cb = func;
            ft_804D6578.x0++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x49, 0, "fighter chk device wind func num over!\n");
}

/**
 * @brief Registers a stage capture / bury / barrel cannon device callback (e.g. Kongo Jungle Barrel Cannon).
 * @details Stores the ground GObj, capture type, and callback in ftDevice_BuryThings, and increments
 * ftDevice_BuryThingCount. Asserts if capacity (2) is exceeded.
 * @param arg0 Stage ground entity providing the capture/bury mechanic
 * @param arg1 Capture / bury type identifier
 * @param arg2 Device check and interaction callback
 */
void ftCo_800C0764(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    int slot_idx;

    // Search for an empty slot in the capture/bury device table
    for (slot_idx = 0; slot_idx < 2; slot_idx++) {
        if (ftDevice_BuryThings[slot_idx].x0 == NULL) {
            ftDevice_BuryThings[slot_idx].x0 = arg0;
            ftDevice_BuryThings[slot_idx].x4 = arg1;
            ftDevice_BuryThings[slot_idx].cb = arg2;
            ftDevice_BuryThingCount++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x6FU, 0, "fighter chk device catch func num over!\n");
}

/// @todo pretty sure arg2 is a ftDevice callback, but unsure if its
/// always of type ftDevice_Callback0.
/**
 * @brief Registers a dynamic stage hazard collision callback (e.g. Great Bay turtle, Brinstar acid, F-Zero cars).
 * @details Stores the ground GObj, collision hazard type, and callback in ft_80459A8C, and increments
 * ft_804D6570. Asserts if capacity (1) is exceeded.
 * @param arg0 Stage ground entity presenting dynamic collision hazard
 * @param arg1 Collision hazard type identifier
 * @param arg2 Hazard collision check and response callback
 */
void ftCo_800C07F8(Ground_GObj* arg0, u32 arg1, void* arg2)
{
    int slot_idx;

    // Search for an empty slot in the stage hazard collision table
    for (slot_idx = 0; slot_idx < 1; slot_idx++) {
        if (ft_80459A8C[slot_idx].ground == NULL) {
            ft_80459A8C[slot_idx].ground = arg0;
            ft_80459A8C[slot_idx].type = arg1;
            ft_80459A8C[slot_idx].active_cb = arg2;
            ft_804D6570++;
            return;
        }
    }
    HSD_ASSERTREPORT(0x95, 0, "fighter chk device coll func num over!\n");
}
