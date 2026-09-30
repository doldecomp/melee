/**
 * @file itmaterial.h
 * @brief Item Material module
 * @details Handles custom material and TEV setup for items, including color overlays, toon shading, and flashing effects.
 * Module prefix: it
 */
#ifndef GALE01_ITMATERIAL
#define GALE01_ITMATERIAL

#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/gx.h>

struct it_MObjInfo;

/* 277D08 */ /**
 * @brief Initializes the HSD_MObjInfo structure for items.
 */
void it_80277D08(void);
/* 277D8C */ /**
 * @brief Custom setup function for item materials (shadows, toon shading, blending).
 * @param mobj The material object
 * @param rendermode Rendering mode flags
 * @param unused Unused parameter
 */
void fn_80277D8C(HSD_MObj*, u32 rendermode, u32 unused);
/* 277F90 */ /**
 * @brief Sets up TEV expression data to apply item color overlays (e.g., flashing).
 * @param item The Item instance
 * @param mobj The material object
 * @param texp Pointer to the expression struct to populate
 * @return Pointer to the expression, or NULL
 */
HSD_TExp* it_80277F90(Item*, HSD_MObj*, HSD_TExp* texp);
/* 278108 */ /**
 * @brief Applies complex color blending to the material based on item color overlays.
 * @param item The Item instance
 * @param mobj The material object
 * @param texp The TEV expression list
 */
void it_80278108(Item*, HSD_MObj*, HSD_TExp* texp);
/* 278574 */ /**
 * @brief Recursively sets the diffuse color for all materials in the item\'s JObj tree.
 * @param gobj The item GObj
 * @param diffuse_color The new diffuse color to apply
 */
void it_80278574(HSD_GObj*, GXColor* diffuse_color);
/* 3F1F90 */ extern struct it_MObjInfo it_mobj;

typedef void (*it_MObjSetupFunc)(HSD_MObj* mobj, u32 rendermode, u32 unused);

#endif
