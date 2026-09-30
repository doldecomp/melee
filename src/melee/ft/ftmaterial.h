/**
 * @file ftmaterial.h
 * @brief Fighter material and texture state system
 * @details Handles the material and texture state for fighters, including color overlays, visibility, and rendering modes like metal or shadows.
 * Module prefix: ft
 */
#ifndef GALE01_0BF260
#define GALE01_0BF260

#include <Runtime/platform.h>

#include <melee/ft/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/gx.h>

/**
 * @brief Initializes the fighter MObj info struct with custom setup callbacks.
 */
/* 0BF260 */ void ftMaterial_800BF260(void);
/**
 * @brief Main material setup callback for fighter meshes. Configures rendering flags for metal, shadow, toon, and custom overlays.
 * @param mobj The material object being set up
 * @param rendermode The current render mode flags
 * @param unused Unused parameter
 */
/* 0BF2B8 */ void ftMaterial_800BF2B8(HSD_MObj* mobj, u32 rendermode,
                                      u32 unused);
/**
 * @brief Configures TEV registers for fighter lighting overlays.
 * @param fp Fighter instance
 * @param mobj Material object
 * @param texp Texture expression struct
 * @param rendermode Render mode flags
 * @return Updated texture expression pointer, or NULL
 */
/* 0BF534 */ HSD_TExp* ftMaterial_800BF534(Fighter* fp, HSD_MObj* mobj,
                                           HSD_TExp* texp, u32 rendermode);
/**
 * @brief Configures TEV registers for fighter coloring and opacity states (e.g. damage flash, invisible).
 * @param fp Fighter instance
 * @param mobj Material object
 * @param texp Texture expression struct
 */
/* 0BF6BC */ void ftMaterial_800BF6BC(Fighter* fp, HSD_MObj* mobj,
                                      HSD_TExp* texp);
/**
 * @brief Iterates through all JObjs and DObjs of the fighter and forcefully overrides their diffuse color.
 * @param gobj Fighter GObj
 * @param diffuse The diffuse color to apply
 */
/* 0BFB4C */ void ftMaterial_800BFB4C(Fighter_GObj* gobj, GXColor* diffuse);
/* 3C6980 */ extern HSD_MObjInfo ftMObj;

#endif
