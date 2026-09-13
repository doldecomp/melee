/**
 * @file
 * @brief Refraction visual effects using GX indirect textures.
 *
 * Uses reference counting to track active effect users.
 * Supports IA4, IA8, and RGBA8 texture formats.
 */

#ifndef GALE01_021CE8
#define GALE01_021CE8

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

/* 0222A4 */ void lbRefract_800222A4(void);

/* 02247C */ void lbRefract_8002247C(HSD_CObj*);

/// @brief Copy framebuffer to refraction source texture.
/* 022560 */ void lbRefract_80022560(void);

/// @brief Reset TEV and indirect texture stages.
/* 0225D4 */ void lbRefract_800225D4(void);

/* 0226A8 */ s32 lbRefract_PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc);
/* 022998 */ void lbRefract_80022998(HSD_MObj*, u32 rendermode, s32);

/// @brief Increment refraction effect user count.
/* 022BB8 */ void lbRefract_80022BB8(void);

/// @brief Decrement refraction effect user count.
/* 022BD0 */ void lbRefSetUnuse(void);

#endif
