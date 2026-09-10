/**
 * @file lb_0219.h
 * @brief Data-driven animated screen flashes.
 */

#ifndef GALE01_0219E4
#define GALE01_0219E4

#include <Runtime/platform.h>

#include <sysdolphin/baselib/forward.h>

/* 0219E4 */ void lbBgFlash_Free(void*);
/* 021A10 */ void lbBgFlash_SetFlashScale(f32);
/* 021A18 */ void lbBgFlash_Init(int);
/* 021B04 */ void lbBgFlash_Proc(HSD_GObj*);
/* 021C1C */ void fn_80021C1C(void);
/* 021C48 */ void lbBgFlash_80021C48(u32, u32);
/* 021C80 */ void fn_80021C80(HSD_GObj* gobj);

#endif
