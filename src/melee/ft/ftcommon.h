#ifndef GALE01_07C930
#define GALE01_07C930

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

/* 07C930 */ void ftCommon_8007C930(Fighter*, float);
/* 07C98C */ void ftCommon_8007C98C(Fighter*, float vel, float,
                                    float gr_friction);
/* 07CA80 */ void ftCommon_8007CA80(Fighter* fp, float result, float,
                                    float);
/* 07CADC */ void ftCommon_8007CADC(Fighter*, float, float, float);
/* 07CB74 */ void ftCommon_8007CB74(Fighter_GObj*);
/* 07CC1C */ Fighter_GObj* ftCommon_8007CC1C(Fighter_GObj*);
/* 07CC78 */ void ftCommon_8007CC78(Fighter*, float);
/* 07CCA0 */ void ftCommon_8007CCA0(Fighter*, float);
/* 07CCE8 */ void ftCommon_8007CCE8(Fighter*);
/* 07CD6C */ float ftCommon_8007CD6C(float, float decrement);
/* 07CDA4 */ float ftCommon_8007CDA4(Fighter*);
/* 07CDF8 */ float ftCommon_8007CDF8(Fighter*);
/* 07CE4C */ void ftCommon_8007CE4C(Fighter*, float);
/* 07CE94 */ void ftCommon_8007CE94(Fighter*, float);
/* 07CEF4 */ void ftCommon_8007CEF4(Fighter*);
/* 07CF58 */ bool ftCommon_8007CF58(Fighter*);
/* 07D050 */ bool ftCommon_8007D050(Fighter*, float);
/* 07D140 */ void ftCommon_8007D140(Fighter*, float, float, float);
/* 07D174 */ void ftCommon_8007D174(Fighter*, float, float, float, float);
/* 07D268 */ void ftCommon_8007D268(Fighter*);
/* 07D28C */ void ftCommon_8007D28C(Fighter*, float);
/* 07D2E8 */ void ftCommon_8007D2E8(Fighter*, float, float);
/* 07D344 */ void ftCommon_8007D344(Fighter*, float, float, float);
/* 07D3A8 */ void ftCommon_8007D3A8(Fighter*, float, float, float);
/* 07D440 */ void ftCommon_8007D440(Fighter*, float);
/* 07D468 */ void ftCommon_8007D468(Fighter*);
/* 07D494 */ void ftCommon_8007D494(Fighter*, float, float);
/* 07D4B8 */ void ftCommon_8007D4B8(Fighter*);
/* 07D4E4 */ void ftCommon_8007D4E4(Fighter*);
/* 07D4F4 */ void ftCommon_ClampFallSpeed(Fighter*, float);
/* 07D508 */ void ftCommon_8007D508(Fighter*, float, float);
/* 07D528 */ bool ftCommon_8007D528(Fighter*);
/* 07D5BC */ void ftCommon_8007D5BC(Fighter*);
/* 07D5D4 */ void ftCommon_8007D5D4(Fighter*);
/* 07D60C */ void ftCommon_8007D60C(Fighter*);
/* 07D698 */ void ftCommon_8007D698(Fighter*);
/* 07D6A4 */ void ftCommon_8007D6A4(Fighter*);
/* 07D780 */ void ftCommon_8007D780(Fighter*);
/* 07D7FC */ void ftCommon_8007D7FC(Fighter*);
/* 07D92C */ void ftCommon_8007D92C(Fighter_GObj*);
/* 07D964 */ float ftCo_GetLStickAngle(Fighter* fp);
/* 07D99C */ float ftCo_GetCStickAngle(Fighter* fp);
/* 07D9D4 */ float ftCommon_8007D9D4(Fighter*);
/* 07D9FC */ void ftCommon_8007D9FC(Fighter*);
/* 07DA24 */ void ftCommon_8007DA24(Fighter*);
/* 07DA74 */ float ftCommon_CalcHitlag(int dmg, FtMotionId msid, float mul);
/* 07DB24 */ void ftCommon_8007DB24(Fighter_GObj*);
/* 07DB58 */ void ftCommon_8007DB58(Fighter_GObj*);
/* 07DBCC */ void ftCommon_InitGrab(Fighter*, bool, float);
/* 07DC08 */ bool ftCommon_8007DC08(Fighter*, float);
/* 07DD7C */ void ftCommon_8007DD7C(Fighter_GObj*, Vec3*);
/* 07DFD0 */ void ftCommon_8007DFD0(Fighter_GObj* gobj, Vec3* arg1);
/* 07E0E4 */ void ftCommon_8007E0E4(Fighter_GObj*);
/* 07E2A4 */ Fighter_GObj* ftCommon_8007E2A4(Fighter_GObj*);
/* 07E2D0 */ void ftCommon_8007E2D0(Fighter*, s16, HSD_GObjEvent,
                                    HSD_GObjEvent,
                                    void (*)(Fighter_GObj*, Fighter_GObj*));
/* 07E2F4 */ void ftCommon_8007E2F4(Fighter*, s16 val);
/* 07E2FC */ void ftCommon_8007E2FC(Fighter_GObj*);
/* 07E358 */ void ftCommon_8007E358(Fighter_GObj*);
/* 07E3EC */ void ftCommon_8007E3EC(Fighter_GObj*);
/* 07E5AC */ void ftCommon_8007E5AC(Fighter*);
/* 07E620 */ void ftCommon_SetAccessory(Fighter*, HSD_Joint*);
/* 07E690 */ void ftCommon_8007E690(Fighter*, HSD_AnimJoint*);
/* 07E6DC */ void ftCommon_8007E6DC(Fighter_GObj*, Fighter_GObj* gobj, s32);
/* 07E79C */ void ftCommon_8007E79C(Fighter_GObj*, s32);
/* 07E7E4 */ void ftCommon_8007E7E4(Fighter_GObj*, s32);
/* 07E82C */ void ftCommon_8007E82C(Fighter_GObj*);
/* 07E83C */ void ftCommon_8007E83C(Fighter_GObj*, s32, float div);
/* 07E994 */ s32 ftGetParasolStatus(Fighter_GObj*);
/* 07EA90 */ void ftCommon_8007EA90(Fighter*, s32);
/* 07EBAC */ void ftCommon_8007EBAC(Fighter*, u32, u32);
/* 07EC30 */ void ftCommon_8007EC30(u32, u32);
/* 07ECD4 */ void ftCommon_8007ECD4(Fighter*, s32);
/* 07ED2C */ void ftCommon_8007ED2C(Fighter*);
/* 07ED50 */ void ftCommon_8007ED50(Fighter*, s32);
/* 07EE0C */ void ftCommon_8007EE0C(Fighter*, s32);
/* 07EEC8 */ void ftCommon_8007EEC8(Fighter*, s32, s32);
/* 07EF5C */ void ftCommon_8007EF5C(Fighter*, s32);
/* 07EFC0 */ void ftCommon_8007EFC0(Fighter*, u32 val);
/* 07EFC8 */ void ftCommon_8007EFC8(Fighter_GObj*, void (*)(Fighter_GObj*));
/* 07F578 */ void ftCommon_8007F578(Fighter_GObj*);
/* 07F5CC */ void ftCommon_8007F5CC(Fighter_GObj*, s32);
/* 07F694 */ float ftCommon_GetModelScale(Fighter*);
/* 07F6A4 */ void ftCommon_8007F6A4(Fighter*, HSD_JObj*);
/* 07F76C */ void ftCommon_8007F76C(Fighter_GObj*);
/* 07F7B4 */ void ftCommon_8007F7B4(Fighter_GObj*);
/* 07F804 */ MtxPtr ftCommon_8007F804(Fighter*);
/* 07F824 */ void ftCommon_8007F824(Fighter_GObj*);
/* 07F86C */ void ftCommon_8007F86C(Fighter_GObj*);
/* 07F8B4 */ void ftCommon_8007F8B4(Fighter*, Vec3* v);
/* 07F8E8 */ void ftCommon_8007F8E8(Fighter_GObj*);
/* 07F948 */ void ftCommon_8007F948(Fighter_GObj*, Fighter_GObj*, s32);
/* 07F9B4 */ void ftCommon_8007F9B4(Fighter_GObj*);
/* 07FA00 */ void ftCommon_8007FA00(Fighter_GObj*);
/* 07FA58 */ void ftCommon_8007FA58(Fighter_GObj*, Item_GObj*);
/* 07FC7C */ void ftCommon_8007FC7C(Fighter_GObj*, float);
/* 07FDA0 */ void ftCommon_8007FDA0(Fighter_GObj*);
/* 07FE84 */ void ftCommon_8007FE84(Fighter_GObj*, Fighter_GObj*, s32, float);
/* 07FF74 */ void ftCommon_8007FF74(Fighter_GObj*);
/* 07FFD8 */ bool ftCommon_8007FFD8(Fighter*, float);
/* 080144 */ bool ftCommon_80080144(Fighter*);
/* 080174 */ void ftCommon_80080174(Fighter* fp);
/* 08021C */ void ftCommon_8008021C(Fighter_GObj*);
/* 08031C */ void ftCommon_8008031C(Fighter_GObj*);
/* 080460 */ void ftCommon_80080460(Fighter*);
/* 080474 */ void ftCommon_80080474(Fighter*);
/* 080484 */ void ftCommon_80080484(Fighter*);
/* 0804A0 */ void ftCommon_800804A0(Fighter*, float);
/* 0804EC */ float ftCommon_800804EC(Fighter*);
/* 0804FC */ void ftCommon_800804FC(Fighter*);

#endif
