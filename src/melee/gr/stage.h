#ifndef _stage_h_
#define _stage_h_

#include <dolphin/gx/types.h>
#include <dolphin/mtx/types.h>
#include <melee/gr/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobjproc.h>

f32 Stage_GetCamBoundsLeftOffset(void);
f32 Stage_GetCamBoundsRightOffset(void);
f32 Stage_GetCamBoundsTopOffset(void);
f32 Stage_GetCamBoundsBottomOffset(void);
f32 Stage_GetCamPanAngleRadians(void);
f32 Stage_GetCamMaxDepth(void);
f32 Stage_GetCamZoomRate(void);
f32 Stage_GetCamInfoX20(void);
f32 Stage_GetCamInfoX24(void);
f32 Stage_GetCamFixedZoom(void);
f32 Stage_GetCamTrackRatio(void);
f32 Stage_GetCamTrackSmooth(void);
f32 Stage_GetBlastZoneRightOffset(void);
f32 Stage_GetBlastZoneLeftOffset(void);
f32 Stage_GetBlastZoneTopOffset(void);
f32 Stage_GetBlastZoneBottomOffset(void);
f32 Stage_CalcUnkCamY(void);
f32 Stage_CalcUnkCamYBounds(void);
void Stage_UnkSetVec3TCam_Offset(Vec3* vec3);
f32 Stage_GetPauseCamZPosMin(void);
f32 Stage_GetPauseCamZPosInit(void);
f32 Stage_GetPauseCamZPosMax(void);
f32 Stage_GetCamAngleRadiansUp(void);
f32 Stage_GetCamAngleRadiansDown(void);
f32 Stage_GetCamAngleRadiansLeft(void);
f32 Stage_GetCamAngleRadiansRight(void);
void Stage_80224CAC(Vec3* arg0);
void Stage_SetVecToFixedCamPos(Vec3* arg0);
f32 Stage_GetCamFixedFov(void);
bool Stage_80224DC8(s32 arg);
void Stage_80224E38(Vec3* arg0, s32 arg1);
void Stage_80224E64(enum_t arg0, Vec3* arg_vec);
s32 Stage_80224FDC(Vec3* arg0);
s32 Stage_80225074(s32 arg0);
s32 Stage_80225194(void);
s32 Stage_8022519C(InternalStageId idx);
void Stage_802251B4(InternalStageId idx, s32 arg1);
void Stage_802251E8(InternalStageId idx, s32* _);
void Stage_8022524C(void);
void Stage_80225298(void);
void Stage_802252E4(InternalStageId idx, HSD_GObj* _);
void Stage_8022532C(InternalStageId idx, s32 arg1);
s32 Stage_80225194(void);

#endif
