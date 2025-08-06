#ifndef _grtclink_h_
#define _grtclink_h_

#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

#include "gr/forward.h"

void grTCLink_8021FF44(bool);
void grTCLink_8021FF48(void);
void grTCLink_8021FFB8(void);
void grTCLink_8021FFBC(void);
bool grTCLink_8021FFE0(void);
HSD_GObj* grTCLink_8021FFE8(int);
void grTCLink_802200D0(Ground_GObj*);
bool grTCLink_802200FC(Ground_GObj*);
void grTCLink_80220104(Ground_GObj*);
void grTCLink_80220108(Ground_GObj*);
void grTCLink_8022010C(Ground_GObj*);
bool grTCLink_8022015C(Ground_GObj*);
void grTCLink_80220164(Ground_GObj*);
void grTCLink_80220198(Ground_GObj*);
void grTCLink_8022019C(Ground_GObj*);
bool grTCLink_802201EC(Ground_GObj*);
void grTCLink_802201F4(Ground_GObj*);
void grTCLink_80220214(Ground_GObj*);
DynamicsDesc* grTCLink_80220218(int unused);
bool grTCLink_80220220(Vec3*, int, HSD_JObj*);

#endif
