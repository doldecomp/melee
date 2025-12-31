#ifndef GALE01_028B9C
#define GALE01_028B9C

#include <placeholder.h>
#include <platform.h>

#include "cm/forward.h"

#include "dolphin/gx/GXStruct.h"

#include <baselib/forward.h>

#include <dolphin/mtx.h>
#include <baselib/cobj.h>

/* 028B9C */ void Camera_80028B9C(int);
/* 028F5C */ void Camera_80028F5C(CmSubject*, s32);
/* 029020 */ CmSubject* Camera_80029020(void);
/* 029044 */ CmSubject* Camera_80029044(int);
/* 0290D4 */ void Camera_800290D4(CmSubject*);
/* 029124 */ s32 Camera_80029124(Vec3*, s32);
/* 02928C */ bool Camera_8002928C(CmSubject*);
/* 0293E0 */ void Camera_800293E0(void);
/* 02958C */ void Camera_8002958C(CameraBounds*, CameraTransformState*);
/* 029AAC */ void Camera_80028F5C(CmSubject*, s32);
/* 029BC4 */ void Camera_80029BC4(CameraBounds*, CameraTransformState*);
/* 029C88 */ void Camera_80029C88(CameraBounds*, CameraTransformState*, f32);
/* 029CF8 */ void Camera_80029CF8(CameraBounds*, CameraTransformState*);
/* 02A0C0 */ void Camera_8002A0C0(CameraBounds*, CameraTransformState*);
/* 02A278 */ void Camera_8002A278(float x, float y);
/* 02A28C */ void Camera_8002A28C(CameraBounds*);
/* 02A4AC */ void Camera_8002A4AC(HSD_GObj*);
/* 02A768 */ void Camera_8002A768(CameraTransformState*, s32);
/* 02AF68 */ void Camera_8002AF68(HSD_CObj*, CameraTransformState*);
/* 02B0E0 */ void Camera_8002B0E0(void);
/* 02B1F8 */ void Camera_8002B1F8(CameraTransformState*);
/* 02B3D4 */ void Camera_8002B3D4(void*);
/* 02B694 */ void Camera_8002B694(CameraInputs*, s32);
/* 02BA00 */ s32 Camera_8002BA00(s32, s32);
/* 02BAA8 */ void Camera_8002BAA8(f32);
/* 02BC78 */ s32 Camera_8002BC78(Vec3*, Vec3*, Vec3*);
/* 02BD88 */ void Camera_8002BD88(f32, f32);
/* 02C010 */ void Camera_8002C010(f32, f32);
/* 02C1A8 */ UNK_RET Camera_8002C1A8(UNK_PARAMS);
/* 02C5B4 */ UNK_RET Camera_8002C5B4(UNK_PARAMS);
/* 02C908 */ void Camera_8002C908(void*);
/* 02CB0C */ void Camera_8002CB0C(void);
/* 02CDDC */ void Camera_8002CDDC(void*);
/* 02D318 */ void Camera_8002D318(void* unused);
/* 02D85C */ void Camera_8002D85C(void* unused);
/* 02DDC4 */ void Camera_8002DDC4(void*);
/* 02DFE4 */ s32 Camera_8002DFE4(Vec3*, Vec3*, CameraTransformState*);
/* 02E158 */ s32 Camera_8002E158(f32*, f32, f32, f32);
/* 02E234 */ UNK_RET Camera_8002E234(UNK_PARAMS);
/* 02E490 */ void Camera_8002E490(void*);
/* 02E6FC */ void Camera_8002E6FC(int);
/* 02E818 */ void Camera_8002E818(Vec*);
/* 02E948 */ void Camera_8002E948(bool (*)(Vec*));
/* 02EA64 */ void Camera_8002EA64(Vec*);
/* 02EB5C */ void Camera_8002EB5C(float arg0);
/* 02EC7C */ void Camera_8002EC7C(float arg0);
/* 02ED9C */ void Camera_8002ED9C(float arg0);
/* 02EEC8 */ void Camera_8002EEC8(float);
/* 02EF14 */ void Camera_8002EF14(void);
/* 02F0E4 */ void Camera_8002F0E4(s32);
/* 02F260 */ bool Camera_8002F260(void);
/* 02F274 */ void Camera_8002F274(void);
/* 02F360 */ void fn_8002F360(HSD_GObj*);
/* 02F3AC */ void Camera_8002F3AC(void);
/* 02F474 */ void Camera_8002F474(void);
/* 02F488 */ s32 fn_8002F488(Vec4*);
/* 02F4D4 */ void Camera_8002F4D4(s8, s8, s32);
/* 02F73C */ void Camera_8002F73C(s8, s8);
/* 02F760 */ void Camera_8002F760(s8, s8);
/* 02F784 */ void Camera_8002F784(s8, s8);
/* 02F7AC */ void Camera_8002F7AC(s8);
/* 02F8F4 */ void Camera_8002F8F4(void);
/* 02F908 */ s32 fn_8002F908(HSD_RectF32* arg0);
/* 02F9E4 */ void Camera_8002F9E4(s8 arg0, s8 arg1);
/* 02FBA0 */ s32 fn_8002FBA0(HSD_RectF32* arg0);
/* 02FC7C */ void Camera_8002FC7C(s8, s8);
/* 02FE38 */ void Camera_8002FE38(void);
/* 02FEEC */ void Camera_8002FEEC(s32);
/* 03006C */ void Camera_8003006C(void);
/* 0300F0 */ void Camera_800300F0(void);
/* 03010C */ bool Camera_8003010C(void);
/* 030130 */ bool Camera_80030130(void);
/* 030154 */ bool Camera_80030154(void);
/* 030178 */ bool Camera_80030178(void);
/* 03019C */ Vec3* Camera_8003019C(void);
/* 0301D0 */ void fn_800301D0(HSD_GObj*, int);
/* 0304E0 */ UNK_RET Camera_800304E0(UNK_PARAMS);
/* 030688 */ void Camera_80030688(void);
/* 030730 */ void Camera_80030730(f32);
/* 030740 */ void Camera_SetBackgroundColor(u8, u8, u8);
/* 030758 */ GXColor Camera_80030758(void);
/* 030788 */ void Camera_80030788(Vec*);
/* 0307AC */ void Camera_800307AC(Vec*);
/* 0307D0 */ bool Camera_800307D0(f32*, f32*, f32*);
/* 030A50 */ HSD_GObj* Camera_80030A50(void);
/* 030A60 */ void Camera_80030A60(bool);
/* 030A78 */ bool Camera_80030A78(void);
/* 030A8C */ void Camera_80030A8C(bool);
/* 030AA4 */ void Camera_SetStageVisible(int);
/* 030AC4 */ bool Camera_80030AC4(void);
/* 030AE0 */ void Camera_80030AE0(bool);
/* 030AF8 */ bool Camera_80030AF8(void);
/* 030B0C */ void Camera_80030B0C(bool);
/* 030B24 */ bool Camera_80030B24(void);
/* 030B38 */ void Camera_80030B38(bool);
/* 030B50 */ bool Camera_80030B50(void);
/* 030B64 */ void Camera_80030B64(bool);
/* 030B7C */ bool Camera_80030B7C(void);
/* 030B90 */ void Camera_80030B90(bool);
/* 030BA8 */ bool Camera_80030BA8(void);
/* 030BBC */ bool Camera_80030BBC(Point3d*, S32Vec2*);
/* 030CD8 */ bool Camera_80030CD8(CmSubject*, S32Vec2*);
/* 030CFC */ bool Camera_80030CFC(CmSubject*, float);
/* 030DE4 */ void Camera_80030DE4(f32, f32);
/* 030DF8 */ void Camera_80030DF8(void);
/* 030E10 */ float Camera_80030E10(void);
/* 030E34 */ void Camera_80030E34(f32);
/* 030E44 */ void Camera_80030E44(enum_t, Vec*);
/* 031044 */ void Camera_80031044(s32);
/* 031060 */ enum_t Camera_80031060(void);
/* 031074 */ void Camera_80031074(u8);
/* 03108C */ enum_t Camera_8003108C(void);
/* 0310A0 */ void Camera_800310A0(u8);
/* 0310B8 */ HSD_CObj* Camera_800310B8(void);
/* 0310E8 */ void Camera_800310E8(void);
/* 031144 */ float Camera_80031144(void);
/* 031154 */ bool Camera_80031154(Vec3*);
/* 03118C */ bool Camera_8003118C(Vec3*, float);
/* 0311CC */ void Camera_800311CC(f32);
/* 0311DC */ void Camera_800311DC(f32);
/* 0311EC */ UNK_RET Camera_800311EC(UNK_PARAMS);
/* 031328 */ void Camera_80031328(HSD_GObj*, s32, s32);
/* 0313E0 */ void Camera_800313E0(HSD_GObj*, u64);

extern CmSubject* cm_804D6468;

#endif
