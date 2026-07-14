#ifndef MELEE_MN_VIBRATION_H
#define MELEE_MN_VIBRATION_H

#include <placeholder.h>
#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

extern f32 mnVibration_804DC020;
extern f32 mnVibration_804DC030;
extern SDATA char mnVibration_804D4FF4[];
extern SDATA char mnVibration_804D4FFC[];

/* 2474C4 */ HSD_JObj* mnVibration_GetNameRowJObj(s32 count);
/* 247510 */ void mnVibration_HandleInput(HSD_GObj*);
/* 248084 */ void mnVibration_CursorThink(HSD_GObj* gobj);
/* 2480B4 */ void mnVibration_UpdatePortPanel(HSD_JObj* arg0, u8 arg1,
                                              u8 arg2);
/* 24829C */ void mnVibration_CreatePortPanels(HSD_GObj* arg0);
/* 248444 */ void mnVibration_CreateNameRow(HSD_GObj* arg0, u8 arg1, u8 arg2);
/* 248644 */ void mnVibration_RefreshNameRows(HSD_GObj* arg0);
/* 248748 */ void mnVibration_OnAnimComplete(HSD_GObj* gobj);
/* 2487A8 */ void mnVibration_Think(HSD_GObj* gobj);
/* 248A78 */ void mnVibration_IntroProc(HSD_GObj*);
/* 248ED4 */ void mnVibration_CreateScreen(s32 arg0);
/* 249174 */ void mnVibration_Init(int arg0);

#endif
