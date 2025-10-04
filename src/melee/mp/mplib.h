#ifndef GALE01_04D164
#define GALE01_04D164

#include <placeholder.h>
#include <platform.h>

#include "gr/forward.h"
#include "mp/forward.h"
#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 04D164 */ UNK_T mpLib_8004D164(void);
/* 04D16C */ mpLib_Point* mpLib_8004D16C(void);
/* 04D174 */ mp_UnkStruct2* mpLib_8004D174(void);
/* 04D17C */ mpLib_804D64C0_t* mpLib_8004D17C(void);
/* 04D184 */ UNK_RET mpLib_8004D184(UNK_PARAMS);
/* 04D288 */ void mpLib_8004D288(UNK_T);
/* 04DB78 */ int mpLib_8004DB78(int gr_idx);
/* 04DC04 */ int mpLib_8004DC04(int gr_idx);
/* 04DD90 */ bool mpLib_8004DD90(int idx, Vec3*, float*, UNK_T, Vec3* normal);
/* 04E090 */ enum_t mpLib_8004E090(int idx, Vec3*, float*, u32*, Vec3* normal);
/* 04E398 */ bool mpLib_8004E398(int, Vec3*, int, int, int);
/* 04E684 */ bool mpLib_8004E684(int, Vec3*, f32*, u32*, Vec3*);
/* 04EBF8 */ bool mpLib_8004EBF8(float*, float*, float, float, float, float,
                                 float, float, float);
/* 04ED5C */ UNK_RET mpLib_8004ED5C(UNK_PARAMS);
/* 04F008 */ bool mpLib_8004F008(Vec3*, int*, int*, Vec3*, float, float, float,
                                 float, float, int, int, int, int, int);
/* 04F400 */ s32 mpLib_8004F400(Vec3*, int*, int*, Vec3*, s32, u32, u32, int,
                                int, f32, f32, f32, f32, f32);
/* 04F8A4 */ bool mpLib_8004F8A4(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 04FC2C */ bool mpLib_8004FC2C(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 050068 */ UNK_RET mpLib_80050068(UNK_PARAMS);
/* 0501CC */ bool mpLib_800501CC(float surface_normal_y,
                                 float surface_normal_x, float right_x,
                                 float right_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 UNK_T, u32, u32);
/* 05057C */ bool mpLib_8005057C(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 0509B8 */ bool mpLib_800509B8(float surface_normal_y,
                                 float surface_normal_x, float left_x,
                                 float left_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 Vec3*, u32, u32);
/* 050D68 */ bool mpLib_80050D68(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 0511A4 */ UNK_RET mpLib_800511A4(UNK_PARAMS);
/* 0515A0 */ UNK_RET mpLib_800515A0(UNK_PARAMS);
/* 05199C */ s32 mpLib_8005199C(Vec3*, s32, s32);
/* 051BA8 */ int mpLib_80051BA8(Vec3*, int, int, int, int, f32, f32, f32, f32);
/* 051EC8 */ bool mpLib_80051EC8(Vec3*, int*, int*, Vec3*, u32, s32, s32,
                                 float, float, float, float);
/* 0524DC */ bool mpLib_800524DC(Vec3*, int*, int*, Vec3*, int, int, float x,
                                 float y, float z, float);
/* 052508 */ bool mpLib_80052508(Vec3*, int*, int*, Vec3*, u32, u32, f32, f32,
                                 f32, f32);
/* 052534 */ int mpLib_80052534(int);
/* 052700 */ s32 mpLib_80052700(int idx);
/* 0528CC */ int mpLib_800528CC(int);
/* 052A98 */ int mpLib_80052A98(int);
/* 052C64 */ UNK_RET mpLib_80052C64(UNK_PARAMS);
/* 052E30 */ UNK_RET mpLib_80052E30(UNK_PARAMS);
/* 052FFC */ UNK_RET mpLib_80052FFC(UNK_PARAMS);
/* 0531C8 */ UNK_RET mpLib_800531C8(UNK_PARAMS);
/* 053394 */ UNK_RET mpLib_80053394(UNK_PARAMS);
/* 053448 */ UNK_RET mpLib_80053448(UNK_PARAMS);
/* 0534FC */ UNK_RET mpLib_800534FC(UNK_PARAMS);
/* 0536CC */ UNK_RET mpLib_800536CC(UNK_PARAMS);
/* 05389C */ int mpLib_8005389C(int line);
/* 053950 */ int mpLib_80053950(int line);
/* 053A04 */ UNK_RET mpLib_80053A04(UNK_PARAMS);
/* 053BD4 */ UNK_RET mpLib_80053BD4(UNK_PARAMS);
/* 053DA4 */ void mpLib_80053DA4(int ledge_id, Vec3*);
/* 053ECC */ void mpLib_80053ECC(int ledge_id, Vec3*);
/* 053FF4 */ void mpLib_80053FF4(s32, Vec3*);
/* 054158 */ void mpLib_80054158(s32, Vec3*);
/* 0542BC */ UNK_RET mpLib_800542BC(int, Vec3*);
/* 054420 */ UNK_RET mpLib_80054420(int, Vec3*);
/* 054584 */ s32 mpLib_80054584(int, Vec3*);
/* 0546E8 */ UNK_RET mpLib_800546E8(UNK_PARAMS);
/* 05484C */ UNK_RET mpLib_8005484C(int, Vec3*);
/* 0549B0 */ UNK_RET mpLib_800549B0(UNK_PARAMS);
/* 054B14 */ void mpLib_80054B14(int, Vec3*);
/* 054BC0 */ void mpLib_80054BC0(int, Vec3*);
/* 054C6C */ enum_t mpLib_80054C6C(int);
/* 054CEC */ u32 mpLib_80054CEC(enum_t);
/* 054D68 */ void mpLib_80054D68(int, u32);
/* 054DFC */ Vec3* mpLib_80054DFC(enum_t, Vec3*);
/* 054ED8 */ bool mpLib_80054ED8(int);
/* 054F68 */ bool mpLib_80054F68(int floor_id, s32);
/* 0552B0 */ void mpLib_800552B0(s16 x, HSD_JObj*, s16 z);
/* 05541C */ UNK_RET mpLib_8005541C(UNK_PARAMS);
/* 0557D0 */ UNK_RET mpLib_800557D0(UNK_PARAMS);
/* 055C5C */ UNK_RET mpLib_80055C5C(int index);
/* 055E24 */ UNK_RET mpLib_80055E24(int index);
/* 055E9C */ void mpLib_80055E9C(s16 x);
/* 0565DC */ UNK_RET mpLib_800565DC(int index);
/* 05667C */ void mpLib_8005667C(int index);
/* 0566D8 */ UNK_RET mpLib_800566D8(int index, float*, float*);
/* 0566F8 */ void mpLib_800566F8(int index, float, float);
/* 056710 */ void mpLib_80056710(int index, float, float, float, float);
/* 056758 */ UNK_RET mpLib_80056758(int index, float, float, float, float);
/* 0567C0 */ bool mpLib_800567C0(s32 wall_id, Vec3* ecb_side_vtx,
                                 Vec3* result);
/* 0569EC */ float mpLib_800569EC(u32);
/* 056A1C */ int* mpLib_80056A1C(int, int*);
/* 056A54 */ int mpLib_80056A54(int, int*);
/* 056A8C */ int* mpLib_80056A8C(int, int*);
/* 056AC4 */ int mpLib_80056AC4(int, int*);
/* 056AFC */ int* mpLib_80056AFC(int, int*);
/* 056B34 */ int mpLib_80056B34(int, int*);
/* 056B6C */ enum_t mpLib_80056B6C(enum_t);
/* 056C54 */ bool mpLib_80056C54(s32 idx, Vec3* pos, bool, Vec3*, bool, bool,
                                 float, float, float, float);
/* 057424 */ void mpLib_80057424(s32);
/* 057528 */ void mpLib_80057528(int index);
/* 0575B0 */ void mpLib_800575B0(int);
/* 057638 */ void mpLib_80057638(s32);
/* 057B4C */ void mpLib_80057B4C(mpLib_804D64C0_t*);
/* 057BC0 */ void mpLib_80057BC0(s32);
/* 057FDC */ void mpLib_80057FDC(int index);
/* 058044 */ void mpLib_80058044(int index);
/* 0580AC */ void mpLib_800580AC(int index);
/* 0580C8 */ void mpLib_800580C8(int, Ground*, mpLib_Callback);
/* 0580E0 */ void mpLib_800580E0(int index);
/* 0580FC */ void mpLib_800580FC(int, mpLib_Callback*, Ground**);
/* 05811C */ void mpLib_8005811C(CollData*, int ledge_id);
/* 0581A4 */ void mpLib_800581A4(int arg0, int arg1, int arg2);
/* 0581BC */ void mpLib_800581BC(int, mpLib_Callback*, UNK_T);
/* 0581DC */ void mpLib_800581DC(int, int);
/* 058560 */ void mpLib_80058560(void);
/* 058614 */ UNK_RET mpLib_80058614(UNK_PARAMS);
/* 0587FC */ void fn_800587FC(HSD_GObj*);
/* 058820 */ void mpLib_80058820(void);
/* 0588C8 */ bool mpLib_800588C8(void);
/* 0588D0 */ void mpLib_800588D0(float left, float bottom, float right,
                                 float top);
/* 058970 */ void mpLib_80058970(float x1, float y1, float x2, float y2);
/* 0589D0 */ void mpLib_800589D0(f32 arg8, f32 arg9, f32 argA, f32 argB,
                                 f32 argC, f32 argD, f32 argE, f32 argF);
/* 058AA0 */ void mpLib_80058AA0(void);
/* 058ACC */ void mpLib_80058ACC(GXColor);
/* 058B5C */ UNK_RET mpLib_80058B5C(UNK_PARAMS);
/* 0590F4 */ UNK_RET mpLib_800590F4(UNK_PARAMS);
/* 059404 */ UNK_RET mpLib_80059404(int, int, GXColor);
/* 059554 */ UNK_RET mpLib_80059554(UNK_PARAMS);
/* 059E60 */ float mpLib_80059E60(UNK_PARAMS);
/* 059FE0 */ UNK_RET mpLib_80059FE0(UNK_PARAMS);
/* 05A220 */ UNK_RET mpLib_8005A220(UNK_PARAMS);
/* 05A2DC */ UNK_RET mpLib_8005A2DC(UNK_PARAMS);
/* 05A340 */ UNK_RET mpLib_8005A340(UNK_PARAMS);

#endif
