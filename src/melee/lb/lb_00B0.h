#ifndef GALE01_00B074
#define GALE01_00B074

#include <placeholder.h>
#include <platform.h>

#include "sc/forward.h"
#include <baselib/forward.h>

#include <stddef.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <baselib/texp.h>

/* 00B074 */ bool lb_8000B074(HSD_JObj*);
/* 00B09C */ bool lb_8000B09C(HSD_JObj*);
/* 00B134 */ bool lb_8000B134(HSD_JObj*);
/* 00B1CC */ void lb_8000B1CC(HSD_JObj*, Vec3*, Vec3*);
/* 00B4FC */ void lb_8000B4FC(HSD_JObj*, HSD_Joint*);
/* 00B5DC */ void lb_8000B5DC(HSD_JObj*, HSD_Joint*);
/* 00B6A4 */ void lb_8000B6A4(HSD_JObj*, HSD_Joint*);
/* 00B760 */ void lb_8000B760(HSD_JObj*, HSD_Joint*);
/* 00B804 */ void lb_8000B804(HSD_JObj*, HSD_Joint*);
/* 00BA0C */ void lb_8000BA0C(HSD_JObj*, float);
/* 00BA44 */ void lbDObjSetRateAll(HSD_DObj*, float);
/* 00BB24 */ void lbDObjReqAnimAll(HSD_DObj*, float);
/* 00BD28 */ float lbGetJObjFramerate(HSD_JObj*);
/* 00BDB4 */ float lbGetJObjCurrFrame(HSD_JObj*);
/* 00BE40 */ float lbGetJObjEndFrame(HSD_JObj*);
/* 00BFF0 */ float lb_8000BFF0(HSD_AnimJoint* animjoint);
/* 00C07C */ void lb_8000C07C(HSD_JObj*, s32 i, HSD_AnimJoint**,
                              HSD_MatAnimJoint**, HSD_ShapeAnimJoint**);
/* 00C0E8 */ void lb_8000C0E8(HSD_JObj* jobj, s32 i, DynamicModelDesc*);
/* 00C160 */ void memzero(void* mem, ssize_t size);
/* 00C1C0 */ void lb_8000C1C0(HSD_JObj*, HSD_JObj* constraint);
/* 00C228 */ void lb_8000C228(HSD_JObj*, HSD_JObj* constraint);
/* 00C290 */ void lb_8000C290(HSD_JObj*, HSD_JObj* constraint);
/* 00C2F8 */ void lb_8000C2F8(HSD_JObj*, HSD_JObj* constraint);
/* 00C390 */ void lb_8000C390(HSD_JObj*);
/* 00C420 */ void lb_8000C420(HSD_JObj*, u32 flags, float limit);
/* 00C490 */ void lb_8000C490(HSD_JObj* jobj1, HSD_JObj* jobj2, HSD_JObj*,
                              float, float);
/* 00C7BC */ void lbCopyJObjSRT(HSD_JObj* src, HSD_JObj* dst);
/* 00C868 */ void lb_8000C868(HSD_Joint*, HSD_JObj*, HSD_JObj*, float, float);
/* 00CC5C */ s32 lbGetFreeColorRegister(s32 i0, HSD_MObj*, HSD_TExp*);
/* 00CC8C */ s32 lb_8000CC8C(s32 i); // return type GXTevColorArg?
/* 00CCA4 */ s32 lb_8000CCA4(s32 i);
/* 00CD60 */ s32 lbGetFreeAlphaRegister(s32 i0, HSD_MObj*, HSD_TExp*);
/* 00CD90 */ s32 lb_8000CD90(s32 i);
/* 00CDA8 */ s32 lb_8000CDA8(s32 i);
/* 00CDC0 */ HSD_LObj* lb_8000CDC0(HSD_LObj*);
/* 00CE30 */ void lb_8000CE30(HSD_DObj*, HSD_DObj*);
/* 00CE40 */ void lb_8000CE40(HSD_JObj*, HSD_DObj*);

#endif
