#ifndef _grtpikachu_h_
#define _grtpikachu_h_

#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

#include "gr/forward.h"

void grTPikachu_80222E7C(bool);
void grTPikachu_80222E80(void);
void grTpikachu_UnkStage0_OnLoad(void);
void grTpikachu_UnkStage0_OnStart(void);
bool grTPikachu_80222F18(void);
HSD_GObj* grTPikachu_80222F20(int);
void grTPikachu_80223008(Ground_GObj*);
bool grTPikachu_80223034(Ground_GObj*);
void grTPikachu_8022303C(Ground_GObj*);
void grTPikachu_80223040(Ground_GObj*);
void grTPikachu_80223044(Ground_GObj*);
bool grTPikachu_80223094(Ground_GObj*);
void grTPikachu_8022309C(Ground_GObj*);
void grTPikachu_802230D0(Ground_GObj*);
void grTPikachu_802230D4(Ground_GObj*);
bool grTPikachu_80223124(Ground_GObj*);
void grTPikachu_8022312C(Ground_GObj*);
void grTPikachu_8022314C(Ground_GObj*);
DynamicsDesc* grTPikachu_80223150(enum_t);
bool grTPikachu_80223158(Vec3*, int, HSD_JObj*);

#endif
