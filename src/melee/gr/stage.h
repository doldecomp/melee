#ifndef GALE01_224A54
#define GALE01_224A54

#include <platform.h>

#include "gr/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

/* 224A54 */ float Stage_GetCamBoundsLeftOffset(void);
/* 224A68 */ float Stage_GetCamBoundsRightOffset(void);
/* 224A80 */ float Stage_GetCamBoundsTopOffset(void);
/* 224A98 */ float Stage_GetCamBoundsBottomOffset(void);
/* 224AB0 */ float Stage_GetCamPanAngleRadians(void);
/* 224AC8 */ float Stage_GetCamMaxDepth(void);
/* 224AD8 */ float Stage_GetCamZoomRate(void);
/* 224AE8 */ float Stage_GetCamInfoX20(void);
/* 224AF8 */ float Stage_GetCamInfoX24(void);
/* 224B08 */ float Stage_GetCamFixedZoom(void);
/* 224B18 */ float Stage_GetCamTrackRatio(void);
/* 224B28 */ float Stage_GetCamTrackSmooth(void);
/* 224B38 */ float Stage_GetBlastZoneRightOffset(void);
/* 224B50 */ float Stage_GetBlastZoneLeftOffset(void);
/* 224B68 */ float Stage_GetBlastZoneTopOffset(void);
/* 224B80 */ float Stage_GetBlastZoneBottomOffset(void);
/* 224B98 */ float Stage_CalcUnkCamY(void);
/* 224BC4 */ float Stage_CalcUnkCamYBounds(void);
/* 224BF8 */ void Stage_UnkSetVec3TCam_Offset(Vec3*);
/* 224C1C */ float Stage_GetPauseCamZPosMin(void);
/* 224C2C */ float Stage_GetPauseCamZPosInit(void);
/* 224C3C */ float Stage_GetPauseCamZPosMax(void);
/* 224C4C */ float Stage_GetCamAngleRadiansUp(void);
/* 224C64 */ float Stage_GetCamAngleRadiansDown(void);
/* 224C7C */ float Stage_GetCamAngleRadiansLeft(void);
/* 224C94 */ float Stage_GetCamAngleRadiansRight(void);
/* 224CAC */ void Stage_80224CAC(Vec3*);
/* 224D94 */ void Stage_SetVecToFixedCamPos(Vec3*);
/* 224DB8 */ float Stage_GetCamFixedFov(void);
/* 224DC8 */ bool Stage_80224DC8(s32);
/* 224E38 */ void Stage_80224E38(Vec3*, s32);
/* 224E64 */ void Stage_80224E64(enum_t, Vec3*);
/* 224FDC */ s32 Stage_80224FDC(Vec3*);
/* 225074 */ s32 Stage_80225074(s32);
/* 225194 */ enum_t Stage_80225194(void);
/* 22519C */ s32 Stage_8022519C(InternalStageId idx);
/* 2251B4 */ void Stage_802251B4(InternalStageId idx, s32);
/* 2251E8 */ void Stage_802251E8(InternalStageId idx, s32*);
/* 22524C */ void Stage_8022524C(void);
/* 225298 */ void Stage_80225298(void);
/* 2252E4 */ void Stage_802252E4(InternalStageId idx, HSD_GObj*);
/* 22532C */ void Stage_8022532C(InternalStageId idx, s32);

#endif
