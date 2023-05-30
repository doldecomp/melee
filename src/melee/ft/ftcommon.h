#ifndef MELEE_FT_FTCOMMON_H
#define MELEE_FT_FTCOMMON_H

#include <platform.h>
#include "ft/forward.h"

#include <dolphin/mtx.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

void ftCommon_8007C930(Fighter*, float);
void ftCommon_8007C98C(Fighter*, float vel, float, float gr_friction);
void ftCommon_8007CA80(Fighter* fp, float result, float, float);
void ftCommon_8007CADC(Fighter*, float, float, float);
void ftCommon_8007CB74(HSD_GObj*);
HSD_GObj* ftCommon_8007CC1C(HSD_GObj*);
void ftCommon_8007CC78(Fighter*, float);
void ftCommon_8007CCA0(Fighter*, float);
void ftCommon_8007CCE8(Fighter*);
float ftCommon_8007CD6C(float, float decrement);
float ftCommon_8007CDA4(Fighter*);
float ftCommon_8007CDF8(Fighter*);
void ftCommon_8007CE4C(Fighter*, float);
void ftCommon_8007CE94(Fighter*, float);
void ftCommon_8007CEF4(Fighter*);
bool ftCommon_8007CF58(Fighter*);
bool ftCommon_8007D050(Fighter*, float);
void ftCommon_8007D140(Fighter*, float, float, float);
void ftCommon_8007D174(Fighter*, float, float, float, float);
void ftCommon_8007D268(Fighter*);
void ftCommon_8007D28C(Fighter*, float);
void ftCommon_8007D2E8(Fighter*, float, float);
void ftCommon_8007D344(Fighter*, float, float, float);
void ftCommon_8007D3A8(Fighter*, float, float, float);
void ftCommon_8007D440(Fighter*, float);
void ftCommon_8007D468(Fighter*);
void ftCommon_8007D494(Fighter*, float, float);
void ftCommon_8007D4B8(Fighter*);
void ftCommon_8007D4E4(Fighter*);
void ftCommon_ClampFallSpeed(Fighter*, float);
void ftCommon_8007D508(Fighter*, float, float);
bool ftCommon_8007D528(Fighter*);
void ftCommon_8007D5BC(Fighter*);
void ftCommon_8007D60C(Fighter*);
void ftCommon_8007D698(Fighter*);
void ftCommon_8007D6A4(Fighter*);
void ftCommon_8007D780(Fighter*);
void ftCommon_8007D7FC(Fighter*);
void ftCommon_8007D92C(HSD_GObj*);
float ftCo_GetLStickAngle(Fighter* fp);
float ftCo_GetCStickAngle(Fighter* fp);
float ftCommon_8007D9D4(Fighter*);
void ftCommon_8007D9FC(Fighter*);
void ftCommon_8007DA24(Fighter*);
float ftCommon_CalcHitlag(int dmg, FtMotionId msid, float mul);
void ftCommon_8007DB24(HSD_GObj*);
void ftCommon_8007DB58(HSD_GObj*);
void ftCommon_8007DBCC(Fighter*, bool, float);
bool ftCommon_8007DC08(Fighter*, float);
void ftCommon_8007DD7C(HSD_GObj*, Vec3*);
void ftCommon_8007DFD0(HSD_GObj* gobj, Vec3* arg1);
void ftCommon_8007E0E4(HSD_GObj*);
HSD_GObj* ftCommon_8007E2A4(HSD_GObj*);
void ftCommon_8007E2F4(Fighter*, s16 val);
void ftCommon_8007E2FC(HSD_GObj*);
void ftCommon_8007E358(HSD_GObj*);
void ftCommon_8007E3EC(HSD_GObj*);
void ftCommon_8007E5AC(Fighter*);
void ftCommon_SetAccessory(Fighter*, HSD_Joint*);
void ftCommon_8007E690(Fighter*, HSD_AnimJoint*);
void ftCommon_8007E6DC(HSD_GObj*, HSD_GObj* gobj, s32);
void ftCommon_8007E79C(HSD_GObj*, s32);
void ftCommon_8007E7E4(HSD_GObj*, s32);
void ftCommon_8007E82C(HSD_GObj*);
void ftCommon_8007E83C(HSD_GObj*, s32, float div);
s32 ftCo_GetParasolStatus(HSD_GObj*);
void ftCommon_8007EA90(Fighter*, s32);
void ftCommon_8007EBAC(Fighter*, u32, u32);
void ftCommon_8007EC30(u32, u32);
void ftCommon_8007ECD4(Fighter*, s32);
void ftCommon_8007ED2C(Fighter*);
void ftCommon_8007ED50(Fighter*, s32);
void ftCommon_8007EE0C(Fighter*, s32);
void ftCommon_8007EEC8(Fighter*, s32, s32);
void ftCommon_8007EF5C(Fighter*, s32);
void ftCommon_8007EFC0(Fighter*, u32 val);
void ftCommon_8007EFC8(HSD_GObj*, void (*)(HSD_GObj*));
void ftCommon_8007F578(HSD_GObj*);
void ftCommon_8007F5CC(HSD_GObj*, s32);
float ftCommon_GetModelScale(Fighter*);
void ftCommon_8007F6A4(Fighter*, HSD_JObj*);
void ftCommon_8007F76C(HSD_GObj*);
void ftCommon_8007F7B4(HSD_GObj*);
Mtx* ftCommon_8007F804(Fighter*);
void ftCommon_8007F824(HSD_GObj*);
void ftCommon_8007F86C(HSD_GObj*);
void ftCommon_8007F8B4(Fighter*, Vec3* v);
void ftCommon_8007F8E8(HSD_GObj*);
void ftCommon_8007F948(HSD_GObj*, HSD_GObj*, s32);
void ftCommon_8007F9B4(HSD_GObj*);
void ftCommon_8007FA00(HSD_GObj*);
void ftCommon_8007FA58(HSD_GObj*, HSD_GObj*);
void ftCommon_8007FC7C(HSD_GObj*, float);
void ftCommon_8007FDA0(HSD_GObj*);
void ftCommon_8007FE84(HSD_GObj*, HSD_GObj* gobj, s32, float);
void ftCommon_8007FF74(HSD_GObj*);
bool ftCommon_8007FFD8(Fighter*, float);
bool ftCommon_80080144(Fighter*);
void ftCommon_80080174(Fighter* fp);
void ftCommon_8008021C(HSD_GObj*);
void ftCommon_8008031C(HSD_GObj*);
void ftCommon_80080460(Fighter*);
void ftCommon_80080474(Fighter*);
void ftCommon_80080484(Fighter*);
void ftCommon_800804A0(Fighter*, float);
float ftCommon_800804EC(Fighter*);
void ftCommon_800804FC(Fighter*);

void ftCommon_8007CB74(HSD_GObj*);
void ftCommon_8007CC78(Fighter*, float);
void ftCommon_8007CCA0(Fighter*, float);
float ftCommon_8007CD6C(float value, float decrement);
float ftCommon_8007CDA4(Fighter*);
float ftCommon_8007CDF8(Fighter*);
void ftCommon_8007CE4C(Fighter*, float);
void ftCommon_8007CE94(Fighter*, float);
bool ftCommon_8007CF58(Fighter*);
void ftCommon_8007D344(Fighter*, float, float, float);
void ftCommon_8007D4B8(Fighter*);
void ftCommon_8007D5D4(Fighter*);
void ftCommon_8007D6A4(Fighter*);
void ftCommon_8007D780(Fighter*);
void ftCommon_8007D7FC(Fighter*);
void ftCommon_8007D92C(HSD_GObj*);
void ftCommon_8007D9FC(Fighter*);

void ftCommon_8007E2D0(Fighter*, s16, HSD_GObjEvent, HSD_GObjEvent,
                       void (*)(HSD_GObj*, HSD_GObj*));

void ftCommon_8007E2FC(HSD_GObj*);
void ftCommon_8007E83C(HSD_GObj*, s32, float div);
s32 ftCo_GetParasolStatus(HSD_GObj*);
void ftCommon_8007EA90(Fighter*, s32);
void ftCommon_8007ED50(Fighter*, s32);
void ftCommon_8007EFC0(Fighter*, u32);
float ftCommon_GetModelScale(Fighter*);
void ftCommon_8007FC7C(HSD_GObj*, float);

/// @todo static
void ftCommon_8007FE84(HSD_GObj*, HSD_GObj*, s32, float);

bool ftCommon_8007FFD8(Fighter*, float);

/// @todo @c DataOffset_PlayerScale_MultiplyBySomething
/// @returns <tt>fp->x40*fp->x34</tt>
float ftCommon_800804EC(Fighter*);

#endif
