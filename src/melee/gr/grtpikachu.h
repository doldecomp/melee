#ifndef _grtpikachu_h_
#define _grtpikachu_h_

#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 222E7C */ void grTPikachu_80222E7C(bool);
/* 222E80 */ void grTPikachu_80222E80(void);
/* 222EF0 */ void grTpikachu_UnkStage0_OnLoad(void);
/* 222EF4 */ void grTpikachu_UnkStage0_OnStart(void);
/* 222F18 */ bool grTPikachu_80222F18(void);
/* 222F20 */ HSD_GObj* grTPikachu_80222F20(int);
/* 223008 */ void grTPikachu_80223008(Ground_GObj*);
/* 223034 */ bool grTPikachu_80223034(Ground_GObj*);
/* 22303C */ void grTPikachu_8022303C(Ground_GObj*);
/* 223040 */ void grTPikachu_80223040(Ground_GObj*);
/* 223044 */ void grTPikachu_80223044(Ground_GObj*);
/* 223094 */ bool grTPikachu_80223094(Ground_GObj*);
/* 22309C */ void grTPikachu_8022309C(Ground_GObj*);
/* 2230D0 */ void grTPikachu_802230D0(Ground_GObj*);
/* 2230D4 */ void grTPikachu_802230D4(Ground_GObj*);
/* 223124 */ bool grTPikachu_80223124(Ground_GObj*);
/* 22312C */ void grTPikachu_8022312C(Ground_GObj*);
/* 22314C */ void grTPikachu_8022314C(Ground_GObj*);
/* 223150 */ DynamicsDesc* grTPikachu_80223150(enum_t);
/* 223158 */ bool grTPikachu_80223158(Vec3*, int, HSD_JObj*);
/* 3E92CC */ extern StageData grTPk_StageData;

#endif
