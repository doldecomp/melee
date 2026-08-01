#ifndef _grtclink_h_
#define _grtclink_h_

#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 21FF44 */ void grTCLink_8021FF44(bool);
/* 21FF48 */ void grTCLink_8021FF48(void);
/* 21FFB8 */ void grTclink_UnkStage0_OnLoad(void);
/* 21FFBC */ void grTclink_UnkStage0_OnStart(void);
/* 21FFE0 */ bool grTCLink_8021FFE0(void);
/* 21FFE8 */ HSD_GObj* grTCLink_8021FFE8(int);
/* 2200D0 */ void grTCLink_802200D0(Ground_GObj*);
/* 2200FC */ bool grTCLink_802200FC(Ground_GObj*);
/* 220104 */ void grTCLink_80220104(Ground_GObj*);
/* 220108 */ void grTCLink_80220108(Ground_GObj*);
/* 22010C */ void grTCLink_8022010C(Ground_GObj*);
/* 22015C */ bool grTCLink_8022015C(Ground_GObj*);
/* 220164 */ void grTCLink_80220164(Ground_GObj*);
/* 220198 */ void grTCLink_80220198(Ground_GObj*);
/* 22019C */ void grTCLink_8022019C(Ground_GObj*);
/* 2201EC */ bool grTCLink_802201EC(Ground_GObj*);
/* 2201F4 */ void grTCLink_802201F4(Ground_GObj*);
/* 220214 */ void grTCLink_80220214(Ground_GObj*);
/* 220218 */ DynamicsDesc* grTCLink_80220218(enum_t unused);
/* 220220 */ bool grTCLink_80220220(Vec3*, int, HSD_JObj*);
/* 3E872C */ extern StageData grTCLink_StageData;

#endif
