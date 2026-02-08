#ifndef GALE01_1BFFA8
#define GALE01_1BFFA8

#include <placeholder.h>
#include <platform.h>

#include "gr/types.h"

#include "lb/forward.h"
#include <baselib/forward.h>

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

/* 1BFFB0 */ void Ground_801BFFB0(void);
/* 1C0378 */ void Ground_801C0378(int);
/* 1C0478 */ void Ground_801C0478(void* ptr);
/* 1C0498 */ f32 Ground_801C0498(void);
/* 1C04BC */ void Ground_801C04BC(f32);
/* 1C0508 */ s32 Ground_801C0508(void);
/* 1C052C */ void Ground_801C052C(GXColor*);
/* 1C0544 */ void Ground_801C0544(GXColor*);
/* 1C055C */ void Ground_801C055C(GXColor*);
/* 1C0574 */ void Ground_801C0574(GXColor*);
/* 1C058C */ void Ground_801C058C(GXColor*);
/* 1C05A4 */ void Ground_801C05A4(GXColor*);
/* 1C05BC */ void Ground_801C05BC(GXColor*);
/* 1C05D4 */ void Ground_801C05D4(GXColor*);
/* 1C05EC */ void Ground_801C05EC(GXColor*);
/* 1C0604 */ GXColor* Ground_801C0604(void);
/* 1C0618 */ GXColor* Ground_801C0618(void);
/* 1C062C */ GXColor* Ground_801C062C(void);
/* 1C0640 */ GXColor* Ground_801C0640(void);
/* 1C0654 */ GXColor* Ground_801C0654(void);
/* 1C0668 */ GXColor* Ground_801C0668(void);
/* 1C067C */ GXColor* Ground_801C067C(void);
/* 1C0690 */ GXColor* Ground_801C0690(void);
/* 1C06A4 */ GXColor* Ground_801C06A4(void);
/* 1C06B8 */ void Ground_801C06B8(InternalStageId);
/* 1C0754 */ void Ground_801C0754(StructPairWithStageID* pair);
/* 1C0800 */ void Ground_801C0800(StructPairWithStageID* pair);
/* 1C0F78 */ void Ground_801C0F78(StructPairWithStageID* pair);
/* 1C0FB8 */ void Ground_801C0FB8(StructPairWithStageID* pair);
/* 1C1074 */ void Ground_801C1074(StructPairWithStageID* pair, s32);
/* 1C10B8 */ void Ground_801C10B8(HSD_GObj*, HSD_GObjEvent);
/* 1C1154 */ void Ground_801C1154(void);
/* 1C1158 */ void Ground_801C1158(void);
/* 1C11AC */ void Ground_801C11AC(HSD_GObj* gobj);
/* 1C13D0 */ HSD_JObj* Ground_801C13D0(s32, s32 depth);
/* 1C14D0 */ Ground_GObj* Ground_801C14D0(int);
/* 1C1A20 */ HSD_GObj* Ground_801C1A20(HSD_Joint*, s32);
/* 1C1D6C */ void Ground_801C1D6C(u32);
/* 1C1D84 */ u32 Ground_801C1D84(void);
/* 1C1D98 */ u32 Ground_801C1D98(void);
/* 1C1DAC */ u32 Ground_801C1DAC(void);
/* 1C1DC0 */ u32 Ground_801C1DC0(void);
/* 1C1DD4 */ s16 Ground_801C1DD4(void);
/* 1C1DE4 */ void Ground_801C1DE4(s32*, s32*);
/* 1C1E00 */ void Ground_801C1E00(s32);
/* 1C1E18 */ s32 Ground_801C1E18(void);
/* 1C1E84 */ void* Ground_801C1E84(void);
/* 1C1FFC */ void Ground_ApplyStageBackgroundColor(void);
/* 1C205C */ void Ground_801C205C(GXColor* color);
/* 1C2090 */ bool Ground_801C2090(GXColor* color);
/* 1C20D0 */ f32 Ground_801C20D0(void);
/* 1C2374 */ void Ground_801C2374(HSD_LObj* lobj);
/* 1C247C */ HSD_Spline* Ground_801C247C(s32, s32);
/* 1C28AC */ bool Ground_801C28AC(s32, u32, s32*);
/* 1C2AD8 */ u8* Ground_801C2AD8(void);
/* 1C2AE8 */ f32 Ground_801C2AE8(s32);
/* 1C2BA4 */ HSD_GObj* Ground_801C2BA4(s32);
/* 1C2C8C */ bool Ground_801C2C8C(void*);
/* 1C2CF4 */ HSD_JObj* Ground_801C2CF4(s32);
/* 1C2D0C */ void Ground_801C2D0C(s32 i, HSD_JObj* jobj);
/* 1C2D24 */ bool Ground_801C2D24(enum_t, Vec3*);
/* 1C2ED0 */ bool Ground_801C2ED0(HSD_JObj*, s32);
/* 1C2FE0 */ bool Ground_801C2FE0(Ground_GObj*);
/* 1C3128 */ bool Ground_801C3128(s32, void (*)(int));
/* 1C3214 */ bool Ground_801C3214(int);
/* 1C3260 */ bool Ground_801C3260(s32);
/* 1C32AC */ void Ground_801C32AC(s32);
/* 1C32D4 */ s32 Ground_801C32D4(s32, s32);
/* 1C33C0 */ s32 Ground_801C33C0(s32, s32);
/* 1C36F4 */ void Ground_801C36F4(int map_id, HSD_JObj* jobj, UNK_T joint);
/* 1C3880 */ void Ground_801C3880(f32);
/* 1C3890 */ void Ground_801C3890(f32);
/* 1C38A0 */ void Ground_801C38A0(f32);
/* 1C38AC */ void Ground_801C38AC(f32);
/* 1C38BC */ void Ground_801C38BC(f32 x, f32 y);
/* 1C38D0 */ void Ground_801C38D0(f32 tilt, f32 pan, f32, f32);
/* 1C38EC */ void Ground_801C38EC(f32 depth, f32 zoom);
/* 1C3900 */ void Ground_801C3900(f32, f32, f32, f32, f32 up, f32 down,
                                  f32 left, f32 right);
/* 1C392C */ void Ground_801C392C(f32 x, f32 y, f32 z, f32 fov, f32 vert,
                                  f32 horz);
/* 1C3950 */ void Ground_801C3950(f32 zoom);
/* 1C3960 */ void Ground_801C3960(f32 ratio);
/* 1C3970 */ void Ground_801C3970(f32 smooth);
/* 1C3980 */ void Ground_801C3980(f32 top);
/* 1C3990 */ void Ground_801C3990(f32 bottom);
/* 1C39A0 */ void Ground_801C39A0(f32 left);
/* 1C39B0 */ void Ground_801C39B0(f32 right);
/* 1C39C0 */ void Ground_801C39C0(void);
/* 1C3BA8 */ void Ground_801C3BA8(HSD_GObj*, StageCallbacks*, int, int);
/* 1C3BB4 */ void Ground_801C3BB4(void);
/* 1C3D44 */ s32 Ground_801C3D44(void*, f32, f32);
/* 1C3DB4 */ s32 Ground_801C3DB4(void*, f32, f32);
/* 1C3F20 */ f32 Ground_801C3F20(HSD_JObj*);
/* 1C3FA4 */ HSD_JObj* Ground_801C3FA4(HSD_GObj* gobj, int depth);
/* 1C4100 */ HSD_JObj* Ground_801C4100(HSD_JObj* jobj);
/* 1C4210 */ s32 Ground_801C4210(void);
/* 1C42AC */ void Ground_801C42AC(void);
/* 1C4338 */ void Ground_801C4338(void);
/* 1C4368 */ void Ground_801C4368(float* slope, float* intercept);
/* 1C438C */ void Ground_801C438C(f32 val);
/* 1C43A4 */ void Ground_801C43A4(UNK_T);
/* 1C43C4 */ bool Ground_801C43C4(void*);
/* 1C445C */ void Ground_801C445C(HSD_LObj* lobj);
/* 1C498C */ HSD_GObj* Ground_801C498C(void);
/* 1C49B4 */ LightList** Ground_801C49B4(void);
/* 1C49F8 */ void* Ground_801C49F8(void);
/* 1C4A08 */ void Ground_801C4A08(HSD_GObj* gobj);
/* 1C4B50 */ void Ground_801C4B50(HSD_Spline*, Vec3*, Vec3*, f32);
/* 1C4D70 */ bool Ground_801C4D70(HSD_GObj*, Vec3*, f32);
/* 1C4DA0 */ bool Ground_801C4DA0(Vec3*, f32*);
/* 1C4DD0 */ bool Ground_801C4DD0(void);
/* 1C4E20 */ bool Ground_801C4E20(void);
/* 1C4E70 */ void Ground_801C4E70(HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*,
                                  HSD_JObj*, HSD_JObj*);
/* 1C4FAC */ void Ground_801C4FAC(HSD_CObj* cobj);
/* 1C53EC */ void Ground_801C53EC(u32);
/* 1C5414 */ void Ground_801C5414(int, int);
/* 1C5440 */ void Ground_801C5440(Ground* gp, s32 i, u32);
/* 1C54DC */ bool Ground_801C54DC(Ground* gp, s32 i);
/* 1C5544 */ void Ground_801C5544(Ground*, s32);
/* 1C5630 */ void Ground_801C5630(Ground* gp, s32 i, f32 val);
/* 1C5694 */ void Ground_801C5694(Ground* gp, s32 i, f32 val);
/* 1C5700 */ DynamicsDesc* Ground_801C5700(int i);
/* 1C5740 */ void Ground_801C5740(s32);
/* 1C5750 */ void Ground_801C5750(void);
/* 1C5764 */ s32 Ground_801C5764(void);
/* 1C5774 */ s16 Ground_801C5774(void);
/* 1C5784 */ void Ground_801C5784(s32);
/* 1C5794 */ s32 Ground_801C5794(void);
/* 1C57A4 */ HSD_GObj* Ground_801C57A4(void);
/* 1C57C8 */ HSD_GObj* Ground_801C57C8(void);
/* 1C57F0 */ f32 Ground_801C57F0(void);
/* 1C5800 */ void Ground_801C5800(void);
/* 1C5840 */ s32 Ground_801C5840(void);
/* 1C58E0 */ Item_GObj* Ground_801C58E0(s32, s32);
/* 1C5940 */ int Ground_801C5940(void);
/* 1C5A28 */ void Ground_801C5A28(void);
/* 1C5A60 */ void Ground_801C5A60(void);
/* 1C5A84 */ void Ground_801C5A84(s32);
/* 1C5A94 */ s32 Ground_801C5A94(void);
/* 1C5AA4 */ void Ground_801C5AA4(bool);
/* 1C5ABC */ bool Ground_801C5ABC(void);
/* 1C5AD0 */ u32 Ground_801C5AD0(s32 i);
/* 1C5AEC */ void Ground_801C5AEC(Vec3* v, Vec3*, Vec3*, Vec3*);
/* 49E6C8 */ extern StageInfo stage_info;

#endif
