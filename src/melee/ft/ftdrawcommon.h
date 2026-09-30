/**
 * @file ftdrawcommon.h
 * @brief Common fighter rendering and GX display list declarations.
 * @details Declares the primary GX drawing callbacks for fighters, including standard model
 * rendering, collision bubble overlay rendering, water reflection rendering (e.g. Fountain of Dreams),
 * camera shake matrix calculations, and shadow pass material switching.
 * Module prefix: ft (Fighter)
 */

#ifndef GALE01_08051C
#define GALE01_08051C

#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>

/**
 * @brief Computes a camera view matrix offset by active screen/hit shake translation.
 * @details Queries active shake translation for the fighter via ftLib_GetShakeOffset
 * (e.g. hitlag rumble, smash charge vibration, grab mashing). If shaking, concatenates
 * the shake translation with the active camera's view matrix and returns the result.
 * @param gobj Pointer to fighter HSD_GObj
 * @param out_mtx Output matrix buffer to store concatenated view matrix
 * @return Pointer to out_mtx if shaking; NULL if no shake offset
 */
/* 08051C */ MtxPtr ftDrawCommon_8008051C(HSD_GObj*, MtxPtr);

/**
 * @brief Main debug collision overlay and fighter model rendering routine.
 * @details Checks debug display flags (fp->x21FC_flag) to optionally draw hitboxes,
 * hurtboxes, shield bubbles, reflectors, absorbers, dynamic bone chains, ECB points,
 * and item pickup ranges. If model display flag b7 is active, renders fighter joint
 * hierarchy (HSD_JObjDispAll) with appropriate costume or metal materials, accessories,
 * and character-specific rendering callbacks (ftData_UnkMtxFunc0).
 * @param gobj Pointer to fighter HSD_GObj
 * @param render_flags GX display flags passed to HSD_GObj_80390EB8
 * @param draw_model Flag indicating whether to render the 3D model geometry
 */
/* 0805C8 */ void ftDrawCommon_800805C8(HSD_GObj*, s32, bool);

/**
 * @brief Alternate rendering callback for silhouettes, shadows, and reflections.
 * @details Configures material parts pass 1 and renders the fighter hierarchy with
 * alternate material passes. Used for stage reflection rendering (e.g. Fountain of Dreams)
 * and silhouette / offscreen magnifying glass passes.
 * @param gobj Pointer to fighter HSD_GObj
 * @param render_flags GX display flags
 */
/* 080C28 */ void ftDrawCommon_80080C28(HSD_GObj*, intptr_t);

/**
 * @brief Primary per-frame GX rendering callback for all fighters.
 * @details Registered on fighter GObjs during creation via GObj_SetupGXLink (priority 5).
 * Updates viewport visibility via ftLib_UpdateScreenVisibility and branches on camera mode:
 * - Camera mode 0: Standard rendering via ftDrawCommon_800805C8.
 * - Camera mode 1: Multi-pass rendering for offscreen magnifying glass viewports.
 * @param gobj Pointer to fighter HSD_GObj
 * @param render_flags GX display flags
 */
/* 080E18 */ void ftDrawCommon_80080E18(HSD_GObj*, intptr_t);

/**
 * @brief Restores the standard rendering callback (ftDrawCommon_80080E18) on all active fighters.
 * @details Iterates through the active fighter GObj list (HSD_GOBJ_PLINK_FIGHTER) and resets
 * render_cb to ftDrawCommon_80080E18. Called after stage reflection rendering passes.
 */
/* 081118 */ void ftDrawCommon_80081118(void);

/**
 * @brief Sets the reflection / silhouette rendering callback (ftDrawCommon_80080C28) on all active fighters.
 * @details Iterates through HSD_GOBJ_PLINK_FIGHTER and sets render_cb to ftDrawCommon_80080C28.
 * Used by stages with dynamic planar reflections such as Fountain of Dreams (grIzumi).
 */
/* 081140 */ void ftDrawCommon_80081140(void);

/**
 * @brief Configures material parts for standard texture rendering across all active fighters.
 * @details Sets material shader parts to texture pass 0 for normal gameplay rendering.
 */
/* 081168 */ void ftDrawCommon_80081168(void);

/**
 * @brief Configures material parts for silhouette / alternate rendering across all active fighters.
 * @details Sets material shader parts to pass 1 for planar shadow or silhouette rendering.
 */
/* 081200 */ void ftDrawCommon_80081200(void);

#endif
