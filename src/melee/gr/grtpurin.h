
#ifndef _grtpurin_h_
#define _grtpurin_h_

#include <platform.h>

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

#include "gr/forward.h"

void grTPurin_80223160(bool);
void grTPurin_80223164(void);
void grTPurin_802231DC(void);
void grTPurin_802231E0(void);
bool grTPurin_80223204(void);
HSD_GObj* grTPurin_8022320C(int);
void grTPurin_802232F4(Ground_GObj*);
bool grTPurin_80223320(Ground_GObj*);
void grTPurin_80223328(Ground_GObj*);
void grTPurin_8022332C(Ground_GObj*);
void grTPurin_80223330(Ground_GObj*);
bool grTPurin_80223380(Ground_GObj*);
void grTPurin_80223388(Ground_GObj*);
void grTPurin_80223478(Ground_GObj*);
void grTPurin_8022347C(Ground_GObj*);
bool grTPurin_802234CC(Ground_GObj*);
void grTPurin_802234D4(Ground_GObj*);
void grTPurin_802234F4(Ground_GObj*);
DynamicsDesc* grTPurin_802234F8(int);
bool grTPurin_80223578(Vec3*, int, HSD_JObj*);

#endif
