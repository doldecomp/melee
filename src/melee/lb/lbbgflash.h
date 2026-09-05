/**
 * @file lbbgflash.h
 * @brief Background flash effects for dramatic game events.
 */

#ifndef GALE01_01FC08
#define GALE01_01FC08

#include <dolphin/gx/GXStruct.h>
#include <sysdolphin/baselib/gobj.h>
#include <Runtime/platform.h>

/* 01FC08 */ void fn_8001FC08(void);
/* 01FEC4 */ void fn_8001FEC4(HSD_GObj* gobj, s32 code);
/* 0204C8 */ void fn_800204C8(void);
/* 0205F0 */ void lbBgFlash_800205F0(s32 duration);
/* 02063C */ void lbBgFlash_8002063C(int count);
/* 020688 */ void lbBgFlash_80020688(int);
/* 0206D4 */ void lbBgFlash_800206D4(GXColor*, GXColor*, int);
/* 02087C */ void lbBgFlash_InitState(GXColor*);
/* 0208B0 */ void fn_800208B0(u8 arg0);
/* 0208EC */ void lbBgFlash_800208EC(int);
/* 0209F4 */ void lbBgFlash_800209F4(void);

#endif
