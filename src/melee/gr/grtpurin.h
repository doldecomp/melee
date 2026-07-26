
#ifndef _grtpurin_h_
#define _grtpurin_h_

#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 223160 */ void grTPurin_80223160(bool);
/* 223164 */ void grTPurin_80223164(void);
/* 2231DC */ void grTpurin_UnkStage0_OnLoad(void);
/* 2231E0 */ void grTpurin_UnkStage0_OnStart(void);
/* 223204 */ bool grTPurin_80223204(void);
/* 22320C */ HSD_GObj* grTPurin_8022320C(int);
/* 2232F4 */ void grTPurin_802232F4(Ground_GObj*);
/* 223320 */ bool grTPurin_80223320(Ground_GObj*);
/* 223328 */ void grTPurin_80223328(Ground_GObj*);
/* 22332C */ void grTPurin_8022332C(Ground_GObj*);
/* 223330 */ void grTPurin_80223330(Ground_GObj*);
/* 223380 */ bool grTPurin_80223380(Ground_GObj*);
/* 223388 */ void grTPurin_80223388(Ground_GObj*);
/* 223478 */ void grTPurin_80223478(Ground_GObj*);
/* 22347C */ void grTPurin_8022347C(Ground_GObj*);
/* 2234CC */ bool grTPurin_802234CC(Ground_GObj*);
/* 2234D4 */ void grTPurin_802234D4(Ground_GObj*);
/* 2234F4 */ void grTPurin_802234F4(Ground_GObj*);
/* 2234F8 */ DynamicsDesc* grTPurin_802234F8(enum_t);
/* 223578 */ bool grTPurin_80223578(Vec3*, int, HSD_JObj*);
/* 3E9394 */ extern StageData grTPr_StageData;

#endif
