#ifndef MELEE_GR_GRIZUMI_H
#define MELEE_GR_GRIZUMI_H

#include <platform.h>
#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx/types.h>
#include <baselib/tobj.h>

void grIzumi_801CBB84(int);
void grIzumi_801CBB88(void);
void grIzumi_801CBC0C(void);
void grIzumi_801CBCBC(void);
bool grIzumi_801CBCE0(void);
HSD_GObj* grIzumi_801CBCE8(int gobj_id);
void grIzumi_801CBDD4(HSD_GObj* gobj);
bool grIzumi_801CBE00(HSD_GObj* gobj);
void grIzumi_801CBE08(HSD_GObj* gobj);
void grIzumi_801CBE0C(HSD_GObj* gobj);
void grIzumi_801CBE10(HSD_GObj* gobj);
bool grIzumi_801CBE54(HSD_GObj* gobj);
void grIzumi_801CBE5C(HSD_GObj* gobj);
void grIzumi_801CBE60(HSD_GObj* gobj);
void grIzumi_801CBE64(HSD_GObj* gobj);
bool grIzumi_801CC0CC(HSD_GObj* gobj);
void grIzumi_801CC0D4(HSD_GObj* gobj);
void grIzumi_801CC338(HSD_GObj* gobj);
void grIzumi_801CC33C(HSD_GObj* gobj);
bool grIzumi_801CC350(HSD_GObj* gobj);
void grIzumi_801CC358(HSD_GObj* gobj);
void grIzumi_801CCA10(HSD_GObj* gobj);
void grIzumi_801CCA14(HSD_GObj* gobj);
bool grIzumi_801CCA54(HSD_GObj* gobj);
void grIzumi_801CCA5C(HSD_GObj* gobj);
void grIzumi_801CCA60(HSD_GObj* gobj);
void grIzumi_801CCA64(HSD_GObj* gobj);
bool grIzumi_801CCB08(HSD_GObj* gobj);
void grIzumi_801CCB10(HSD_GObj* gobj);
void grIzumi_801CCB14(HSD_GObj* gobj);
void grIzumi_801CCB18(HSD_GObj* gobj);
void grIzumi_801CCB90(HSD_GObj* gobj, int renderpass);
HSD_GObj* grIzumi_801CCBDC(float height, Vec3* a, int b, HSD_JObj* jobj);
HSD_GObj* grIzumi_801CCD98(void);
void grIzumi_801CCEA0(HSD_GObj* gobj, int renderpass);
HSD_TObj* grIzumi_801CD090(HSD_GObj* gobj, HSD_ImageDesc* image);
void grIzumi_801CD220(HSD_GObj* gobj, int);
lb_UnkAnimStruct* grIzumi_801CD278(enum_t);
bool grIzumi_801CD280(Vec3*, int, HSD_JObj*);
void grIzumi_801CD2D4(void);

#endif
