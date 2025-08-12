
#ifndef _grtganon_h_
#define _grtganon_h_

#include <platform.h>

#include "gr/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

void grTGanon_802246D8(bool);
void grTGanon_802246DC(void);
void grTganon_UnkStage0_OnLoad(void);
void grTganon_UnkStage0_OnStart(void);
bool grTGanon_8022477C(void);
HSD_GObj* grTGanon_80224784(int);
void grTGanon_8022486C(Ground_GObj*);
bool grTGanon_80224898(Ground_GObj*);
void grTGanon_802248A0(Ground_GObj*);
void grTGanon_802248A4(Ground_GObj*);
void grTGanon_802248A8(Ground_GObj*);
void grTGanon_802248A8(Ground_GObj*);
bool grTGanon_802248F8(Ground_GObj*);
void grTGanon_80224900(Ground_GObj*);
void grTGanon_80224934(Ground_GObj*);
void grTGanon_80224938(Ground_GObj*);
bool grTGanon_80224988(Ground_GObj*);
void grTGanon_80224990(Ground_GObj*);
void grTGanon_802249B0(Ground_GObj*);
DynamicsDesc* grTGanon_802249B4(enum_t);
bool grTGanon_80224A4C(Vec3*, int, HSD_JObj*);

#endif
