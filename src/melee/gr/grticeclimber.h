#ifndef MELEE_GR_GRTICECLIMBER_H
#define MELEE_GR_GRTICECLIMBER_H

#include <dolphin/mtx/types.h>
#include <baselib/forward.h>
#include <Runtime/platform.h>

extern s16 lbl_803E8B5C[];

void lbl_8022109C(HSD_GObj*);
bool lbl_802210C8(HSD_GObj*);
void lbl_802210D0(HSD_GObj*);
void lbl_802210D4(HSD_GObj*);

void lbl_8022118C(HSD_GObj*);
bool lbl_802211DC(HSD_GObj*);
void lbl_802211E4(HSD_GObj*);
void lbl_80221204(HSD_GObj*);

void lbl_802210D8(HSD_GObj*);
bool lbl_8022114C(HSD_GObj*);
void lbl_80221154(HSD_GObj*);
void lbl_80221188(HSD_GObj*);

void lbl_80220F14(void);
void func_80220F10(int);
void lbl_80220F84(void);
void lbl_80220F88(void);
bool lbl_80220FAC(void);

bool lbl_80221354(int);
bool lbl_8022135C(Vec3*, int, HSD_JObj*);

HSD_GObj* func_80220FB4(int);
void func_80221288(HSD_GObj*);

void lbl_80221208(void);
void func_801C8DE0(s32, f32, f32, f32, f32, f32, f32, f32);

#endif
