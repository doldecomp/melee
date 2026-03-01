#ifndef MELEE_MN_VIBRATION_H
#define MELEE_MN_VIBRATION_H

#include <placeholder.h>
#include <platform.h>

#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct MnVibrationFloatData {
    u8 pad0[0x18];
    f32 x18;
    f32 x1C;
} MnVibrationFloatData;

extern MnVibrationFloatData mnVibration_803EECE0;
extern f32 mnVibration_804DC020;
extern Vec3 mnVibration_803EED04;
extern SDATA char mnVibration_804D4FF4[];
extern SDATA char mnVibration_804D4FFC[];

/* 2474C4 */ HSD_JObj* mnVibration_802474C4(s32 count);
/* 247510 */ void fn_80247510(HSD_GObj*);
/* 248084 */ void fn_80248084(HSD_GObj* gobj);
/* 2480B4 */ void mnVibration_802480B4(HSD_JObj* arg0, u8 arg1, u8 arg2);
/* 24829C */ void mnVibration_8024829C(HSD_GObj* arg0);
/* 248444 */ void mnVibration_80248444(HSD_GObj* arg0, u8 arg1, u8 arg2);
/* 248644 */ s32 mnVibration_80248644(HSD_GObj* arg0);
/* 248748 */ void fn_80248748(HSD_GObj* gobj);
/* 2487A8 */ void fn_802487A8(HSD_GObj* gobj);
/* 248A78 */ void fn_80248A78(HSD_GObj*);
/* 248ED4 */ void mnVibration_80248ED4(s32 arg0);
/* 249174 */ void mnVibration_80249174(int arg0);

#endif
