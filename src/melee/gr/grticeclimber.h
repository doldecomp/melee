#ifndef MELEE_GR_GRTICECLIMBER_H
#define MELEE_GR_GRTICECLIMBER_H

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/forward.h>

extern s16 lbl_803E8B5C[];

void grTIceClimber_8022109C(HSD_GObj*);
bool grTIceClimber_802210C8(HSD_GObj*);
void grTIceClimber_802210D0(HSD_GObj*);
void grTIceClimber_802210D4(HSD_GObj*);

void grTIceClimber_8022118C(HSD_GObj*);
bool grTIceClimber_802211DC(HSD_GObj*);
void grTIceClimber_802211E4(HSD_GObj*);
void grTIceClimber_80221204(HSD_GObj*);

void grTIceClimber_802210D8(HSD_GObj*);
bool grTIceClimber_8022114C(HSD_GObj*);
void grTIceClimber_80221154(HSD_GObj*);
void grTIceClimber_80221188(HSD_GObj*);

void grTIceClimber_80220F14(void);
void grTIceClimber_80220F10(int);
void grTIceClimber_80220F84(void);
void grTIceClimber_80220F88(void);
bool grTIceClimber_80220FAC(void);

bool grTIceClimber_80221354(int);
bool grTIceClimber_8022135C(Vec3*, int, HSD_JObj*);

HSD_GObj* grTIceClimber_80220FB4(int);
void grTIceClimber_80221288(HSD_GObj*);

void grTIceClimber_80221208(void);
void grMaterial_801C8DE0(s32, f32, f32, f32, f32, f32, f32, f32);

#endif
