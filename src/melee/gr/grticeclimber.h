#ifndef GALE01_220F10
#define GALE01_220F10

#include <platform.h>
#include <placeholder.h>

#include <melee/it/forward.h>
#include <melee/gr/forward.h>
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 220F10 */ void grTIceClimber_80220F10(bool);
/* 220F14 */ void grTIceClimber_80220F14(void);
/* 220F84 */ void grTiceclimber_UnkStage0_OnLoad(void);
/* 220F88 */ void grTiceclimber_UnkStage0_OnStart(void);
/* 220FAC */ bool grTIceClimber_80220FAC(void);
/* 220FB4 */ HSD_GObj* grTIceClimber_80220FB4(int);
/* 22109C */ void grTIceClimber_8022109C(Ground_GObj*);
/* 2210C8 */ bool grTIceClimber_802210C8(Ground_GObj*);
/* 2210D0 */ void grTIceClimber_802210D0(Ground_GObj*);
/* 2210D4 */ void grTIceClimber_802210D4(Ground_GObj*);
/* 2210D8 */ void grTIceClimber_802210D8(Ground_GObj*);
/* 22114C */ bool grTIceClimber_8022114C(Ground_GObj*);
/* 221154 */ void grTIceClimber_80221154(Ground_GObj*);
/* 221188 */ void grTIceClimber_80221188(Ground_GObj*);
/* 22118C */ void grTIceClimber_8022118C(Ground_GObj*);
/* 2211DC */ bool grTIceClimber_802211DC(Ground_GObj*);
/* 2211E4 */ void grTIceClimber_802211E4(Ground_GObj*);
/* 221204 */ void grTIceClimber_80221204(Ground_GObj*);
/* 221208 */ void grTIceClimber_80221208(Item_GObj*, Ground*, Vec3*, HSD_GObj*, f32);
/* 221288 */ void grTIceClimber_80221288(HSD_GObj*);
/* 221354 */ DynamicsDesc* grTIceClimber_80221354(enum_t);
/* 22135C */ bool grTIceClimber_8022135C(Vec3*, int, HSD_JObj*);
/* 3E8B5C */ extern s16 grTIc_803E8B5C[];

#endif
