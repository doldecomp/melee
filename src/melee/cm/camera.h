#ifndef GALE01_028B9C
#define GALE01_028B9C

#include <platform.h>
#include <placeholder.h>

#include "cm/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "cm/types.h"

#include <dolphin/mtx/types.h>
#include <baselib/cobj.h>

/* 028B9C */ void Camera_80028B9C(int);
/* 028F5C */ void Camera_80028F5C(CameraBox* subject, s32 arg1);
/* 029020 */ CameraBox* Camera_80029020(void);
/* 029044 */ CameraBox* Camera_80029044(int);
/* 0290D4 */ void Camera_800290D4(CameraBox*);
/* 029124 */ u32 Camera_80029124(Vec3*, s32);
/* 02928C */ s32 Camera_8002928C(CameraBox*);
/* 0293E0 */ UNK_RET Camera_800293E0(UNK_PARAMS);
/* 02958C */ UNK_RET Camera_8002958C(UNK_PARAMS);
/* 029AAC */ void Camera_80028F5C(CameraBox*, s32);
/* 029BC4 */ void Camera_80029BC4(CameraBounds* bounds,
                                  CameraMovement* movement);
/* 029C88 */ void Camera_80029C88(CameraMovement* movement, f32);
/* 029CF8 */ UNK_RET Camera_80029CF8(UNK_PARAMS);
/* 02A0C0 */ UNK_RET Camera_8002A0C0(UNK_PARAMS);
/* 02A278 */ void Camera_8002A278(float x, float y);
/* 02A28C */ UNK_RET Camera_8002A28C(UNK_PARAMS);
/* 02A4AC */ void Camera_8002A4AC(HSD_GObj*);
/* 02A768 */ void Camera_8002A768(CameraMovement* movement, int arg1);
/* 02AF68 */ UNK_RET Camera_8002AF68(UNK_PARAMS);
/* 02B0E0 */ UNK_RET Camera_8002B0E0(UNK_PARAMS);
/* 02B1F8 */ void Camera_8002B1F8(CameraMovement* movement);
/* 02B3D4 */ UNK_RET Camera_8002B3D4(UNK_PARAMS);
/* 02B694 */ UNK_RET Camera_8002B694(UNK_PARAMS);
/* 02BA00 */ UNK_RET Camera_8002BA00(UNK_PARAMS);
/* 02BAA8 */ UNK_RET Camera_8002BAA8(UNK_PARAMS);
/* 02BC78 */ UNK_RET Camera_8002BC78(UNK_PARAMS);
/* 02BD88 */ UNK_RET Camera_8002BD88(UNK_PARAMS);
/* 02C010 */ UNK_RET Camera_8002C010(UNK_PARAMS);
/* 02C1A8 */ UNK_RET Camera_8002C1A8(UNK_PARAMS);
/* 02C5B4 */ UNK_RET Camera_8002C5B4(UNK_PARAMS);
/* 02C908 */ UNK_RET Camera_8002C908(UNK_PARAMS);
/* 02CB0C */ UNK_RET Camera_8002CB0C(UNK_PARAMS);
/* 02CDDC */ UNK_RET Camera_8002CDDC(UNK_PARAMS);
/* 02D318 */ UNK_RET Camera_8002D318(UNK_PARAMS);
/* 02D85C */ UNK_RET Camera_8002D85C(UNK_PARAMS);
/* 02DDC4 */ UNK_RET Camera_8002DDC4(UNK_PARAMS);
/* 02DFE4 */ UNK_RET Camera_8002DFE4(UNK_PARAMS);
/* 02E158 */ UNK_RET Camera_8002E158(UNK_PARAMS);
/* 02E234 */ UNK_RET Camera_8002E234(UNK_PARAMS);
/* 02E490 */ UNK_RET Camera_8002E490(UNK_PARAMS);
/* 02E6FC */ void Camera_8002E6FC(u8);
/* 02E818 */ void Camera_8002E818(Vec3*);
/* 02E948 */ void Camera_8002E948(bool (*)(Vec3*));
/* 02EA64 */ void Camera_8002EA64(Vec3*);
/* 02EB5C */ void Camera_8002EB5C(float);
/* 02EC7C */ void Camera_8002EC7C(float);
/* 02ED9C */ void Camera_8002ED9C(float);
/* 02EEC8 */ void Camera_8002EEC8(float);
/* 02EF14 */ void Camera_8002EF14(void);
/* 02F0E4 */ void Camera_8002F0E4(s32);
/* 02F260 */ bool Camera_8002F260(void);
/* 02F274 */ void Camera_8002F274(void);
/* 02F360 */ UNK_RET fn_8002F360(UNK_PARAMS);
/* 02F3AC */ UNK_RET Camera_8002F3AC(UNK_PARAMS);
/* 02F474 */ void Camera_8002F474(void);
/* 02F488 */ UNK_RET fn_8002F488(UNK_PARAMS);
/* 02F4D4 */ UNK_RET Camera_8002F4D4(UNK_PARAMS);
/* 02F73C */ UNK_RET Camera_8002F73C(UNK_PARAMS);
/* 02F760 */ UNK_RET Camera_8002F760(UNK_PARAMS);
/* 02F784 */ UNK_RET Camera_8002F784(UNK_PARAMS);
/* 02F7AC */ UNK_RET Camera_8002F7AC(UNK_PARAMS);
/* 02F8F4 */ void Camera_8002F8F4(void);
/* 02F908 */ UNK_RET fn_8002F908(UNK_PARAMS);
/* 02F9E4 */ UNK_RET Camera_8002F9E4(UNK_PARAMS);
/* 02FBA0 */ UNK_RET fn_8002FBA0(UNK_PARAMS);
/* 02FC7C */ UNK_RET Camera_8002FC7C(UNK_PARAMS);
/* 02FE38 */ UNK_RET Camera_8002FE38(UNK_PARAMS);
/* 02FEEC */ UNK_RET Camera_8002FEEC(UNK_PARAMS);
/* 03006C */ UNK_RET Camera_8003006C(UNK_PARAMS);
/* 0300F0 */ UNK_RET Camera_800300F0(UNK_PARAMS);
/* 03010C */ UNK_RET Camera_8003010C(UNK_PARAMS);
/* 030130 */ UNK_RET Camera_80030130(UNK_PARAMS);
/* 030154 */ UNK_RET Camera_80030154(UNK_PARAMS);
/* 030178 */ UNK_RET Camera_80030178(UNK_PARAMS);
/* 03019C */ UNK_RET Camera_8003019C(UNK_PARAMS);
/* 0301D0 */ UNK_RET fn_800301D0(UNK_PARAMS);
/* 0304E0 */ UNK_RET Camera_800304E0(UNK_PARAMS);
/* 030688 */ UNK_RET Camera_80030688(UNK_PARAMS);
/* 030730 */ void Camera_80030730(f32 arg8);
/* 030740 */ void Camera_80030740(u8 r, u8 g, u8 b);
/* 030758 */ UNK_RET Camera_80030758(UNK_PARAMS);
/* 030788 */ void Camera_80030788(Vec3*);
/* 0307AC */ UNK_RET Camera_800307AC(UNK_PARAMS);
/* 0307D0 */ UNK_RET Camera_800307D0(UNK_PARAMS);
/* 030A50 */ HSD_GObj* Camera_80030A50(void);
/* 030A60 */ void Camera_80030A60(bool arg0);
/* 030A78 */ bool Camera_80030A78(void);
/* 030A8C */ void Camera_80030A8C(bool arg0);
/* 030AA4 */ UNK_RET Camera_80030AA4(UNK_PARAMS);
/* 030AC4 */ UNK_RET Camera_80030AC4(UNK_PARAMS);
/* 030AE0 */ void Camera_80030AE0(bool arg0);
/* 030AF8 */ bool Camera_80030AF8(void);
/* 030B0C */ void Camera_80030B0C(bool arg0);
/* 030B24 */ bool Camera_80030B24(void);
/* 030B38 */ void Camera_80030B38(bool arg0);
/* 030B50 */ bool Camera_80030B50(void);
/* 030B64 */ void Camera_80030B64(bool arg0);
/* 030B7C */ bool Camera_80030B7C(void);
/* 030B90 */ void Camera_80030B90(bool arg0);
/* 030BA8 */ bool Camera_80030BA8(void);
/* 030BBC */ UNK_RET Camera_80030BBC(UNK_PARAMS);
/* 030CD8 */ bool Camera_80030CD8(CameraBox*, S32Vec2*);
/* 030CFC */ bool Camera_80030CFC(CameraBox*, float);
/* 030DE4 */ void Camera_80030DE4(f32 arg8, f32 arg9);
/* 030DF8 */ UNK_RET Camera_80030DF8(UNK_PARAMS);
/* 030E10 */ UNK_RET Camera_80030E10(UNK_PARAMS);
/* 030E34 */ void Camera_80030E34(f32 arg8);
/* 030E44 */ void Camera_80030E44(enum_t, Vec3*);
/* 031044 */ UNK_RET Camera_80031044(UNK_PARAMS);
/* 031060 */ enum_t Camera_80031060(void);
/* 031074 */ void Camera_80031074(u8);
/* 03108C */ enum_t Camera_8003108C(void);
/* 0310A0 */ void Camera_800310A0(u8);
/* 0310B8 */ HSD_CObj* Camera_800310B8(void);
/* 0310E8 */ UNK_RET Camera_800310E8(UNK_PARAMS);
/* 031144 */ float Camera_80031144(void);
/* 031154 */ bool Camera_80031154(Vec3*);
/* 03118C */ bool Camera_8003118C(Vec3*, float);
/* 0311CC */ void Camera_800311CC(f32 arg8);
/* 0311DC */ void Camera_800311DC(f32 arg8);
/* 0311EC */ UNK_RET Camera_800311EC(UNK_PARAMS);
/* 031328 */ UNK_RET Camera_80031328(UNK_PARAMS);
/* 0313E0 */ void Camera_800313E0(HSD_GObj*, u64);

#endif
