#ifndef GALE01_04D164
#define GALE01_04D164

#include <platform.h>
#include <placeholder.h>

#include "gr/forward.h"
#include "mp/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include <common_structs.h>

/* 04D164 */ int mpLib_8004D164(void);
/* 04D16C */ mpLib_804D64B8_t* mpLib_8004D16C(void);
/* 04D174 */ mp_UnkStruct2* mpLib_8004D174(void);
/* 04D17C */ mpLib_804D64C0_t* mpLib_8004D17C(void);
/* 04D184 */ UNK_RET mpLib_8004D184(UNK_PARAMS);
/* 04D288 */ void mpLib_8004D288(UNK_T);
/* 04DB78 */ s32 mpLib_8004DB78(s32 gr_idx);
/* 04DC04 */ s32 mpLib_8004DC04(s32 gr_idx);
/* 04DD90 */ bool mpLib_8004DD90(int idx, float*, float*, UNK_T, Vec3* normal);
/* 04E090 */ enum_t mpLib_8004E090(int idx, Vec3*, float*, u32*, Vec3* normal);
/* 04E398 */ bool mpLib_8004E398(int, float*, int, int, int, float);
/* 04E684 */ UNK_RET mpLib_8004E684(UNK_PARAMS);
/* 04EBF8 */ UNK_RET mpLib_8004EBF8(UNK_PARAMS);
/* 04ED5C */ UNK_RET mpLib_8004ED5C(UNK_PARAMS);
/* 04F008 */ bool mpLib_8004F008(Vec3*, int*, int, int, int, int, int, int,
                                 float, float, float, float, float);
/* 04F400 */ UNK_RET mpLib_8004F400(UNK_PARAMS);
/* 04F8A4 */ UNK_RET mpLib_8004F8A4(UNK_PARAMS);
/* 04FC2C */ UNK_RET mpLib_8004FC2C(UNK_PARAMS);
/* 050068 */ UNK_RET mpLib_80050068(UNK_PARAMS);
/* 0501CC */ bool mpLib_800501CC(float surface_normal_y,
                                 float surface_normal_x, float right_x,
                                 float right_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 UNK_T, u32, u32);
/* 05057C */ UNK_RET mpLib_8005057C(UNK_PARAMS);
/* 0509B8 */ bool mpLib_800509B8(float surface_normal_y,
                                 float surface_normal_x, float left_x,
                                 float left_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 UNK_T, u32, u32);
/* 050D68 */ UNK_RET mpLib_80050D68(UNK_PARAMS);
/* 0511A4 */ UNK_RET mpLib_800511A4(UNK_PARAMS);
/* 0515A0 */ UNK_RET mpLib_800515A0(UNK_PARAMS);
/* 05199C */ s32 mpLib_8005199C(Vec3*, s32, s32);
/* 051BA8 */ UNK_RET mpLib_80051BA8(UNK_PARAMS);
/* 051EC8 */ s32 mpLib_80051EC8(Vec3*, s32*, s32*, Vec3*, s32, s32, s32, float,
                                float, float, float);
/* 0524DC */ bool mpLib_800524DC(Vec3*, int, Vec3*, Vec3*, int, int, float x,
                                 float y, float z, float);
/* 052508 */ UNK_RET mpLib_80052508(UNK_PARAMS);
/* 052534 */ UNK_RET mpLib_80052534(UNK_PARAMS);
/* 052700 */ s32 mpLib_80052700(int idx);
/* 0528CC */ UNK_RET mpLib_800528CC(UNK_PARAMS);
/* 052A98 */ UNK_RET mpLib_80052A98(UNK_PARAMS);
/* 052C64 */ UNK_RET mpLib_80052C64(UNK_PARAMS);
/* 052E30 */ UNK_RET mpLib_80052E30(UNK_PARAMS);
/* 052FFC */ UNK_RET mpLib_80052FFC(UNK_PARAMS);
/* 0531C8 */ UNK_RET mpLib_800531C8(UNK_PARAMS);
/* 053394 */ UNK_RET mpLib_80053394(UNK_PARAMS);
/* 053448 */ UNK_RET mpLib_80053448(UNK_PARAMS);
/* 0534FC */ UNK_RET mpLib_800534FC(UNK_PARAMS);
/* 0536CC */ UNK_RET mpLib_800536CC(UNK_PARAMS);
/* 05389C */ UNK_RET mpLib_8005389C(UNK_PARAMS);
/* 053950 */ UNK_RET mpLib_80053950(UNK_PARAMS);
/* 053A04 */ UNK_RET mpLib_80053A04(UNK_PARAMS);
/* 053BD4 */ UNK_RET mpLib_80053BD4(UNK_PARAMS);
/* 053DA4 */ void mpLib_80053DA4(int ledge_id, Vec3*);
/* 053ECC */ void mpLib_80053ECC(int ledge_id, Vec3*);
/* 053FF4 */ void mpLib_80053FF4(s32, Vec3*);
/* 054158 */ void mpLib_80054158(s32, Vec3*);
/* 0542BC */ UNK_RET mpLib_800542BC(UNK_PARAMS);
/* 054420 */ UNK_RET mpLib_80054420(UNK_PARAMS);
/* 054584 */ s32 mpLib_80054584(int, float*);
/* 0546E8 */ UNK_RET mpLib_800546E8(UNK_PARAMS);
/* 05484C */ UNK_RET mpLib_8005484C(UNK_PARAMS);
/* 0549B0 */ UNK_RET mpLib_800549B0(UNK_PARAMS);
/* 054B14 */ UNK_RET mpLib_80054B14(UNK_PARAMS);
/* 054BC0 */ UNK_RET mpLib_80054BC0(UNK_PARAMS);
/* 054C6C */ enum_t mpLib_80054C6C(int);
/* 054CEC */ u32 mpLib_80054CEC(enum_t);
/* 054D68 */ UNK_RET mpLib_80054D68(UNK_PARAMS);
/* 054DFC */ void mpLib_80054DFC(enum_t, Vec3*);
/* 054ED8 */ bool mpLib_80054ED8(int);
/* 054F68 */ bool mpLib_80054F68(s32, s32);
/* 0552B0 */ void mpLib_800552B0(s16 x, HSD_JObj*, s16 z);
/* 05541C */ UNK_RET mpLib_8005541C(UNK_PARAMS);
/* 0557D0 */ UNK_RET mpLib_800557D0(UNK_PARAMS);
/* 055C5C */ UNK_RET mpLib_80055C5C(UNK_PARAMS);
/* 055E24 */ UNK_RET mpLib_80055E24(UNK_PARAMS);
/* 055E9C */ void mpLib_80055E9C(s16 x);
/* 0565DC */ UNK_RET mpLib_800565DC(UNK_PARAMS);
/* 05667C */ void mpLib_8005667C(s16);
/* 0566D8 */ UNK_RET mpLib_800566D8(UNK_PARAMS);
/* 0566F8 */ void mpLib_800566F8(ssize_t, f32, f32);
/* 056710 */ UNK_RET mpLib_80056710(UNK_PARAMS);
/* 056758 */ UNK_RET mpLib_80056758(UNK_PARAMS);
/* 0567C0 */ bool mpLib_800567C0(s32 wall_id, Vec3* ecb_side_vtx,
                                 Vec3* result);
/* 0569EC */ void mpLib_800569EC(void);
/* 056A1C */ UNK_T mpLib_80056A1C(void);
/* 056A54 */ UNK_T mpLib_80056A54(void);
/* 056A8C */ UNK_T mpLib_80056A8C(void);
/* 056AC4 */ UNK_T mpLib_80056AC4(void);
/* 056AFC */ UNK_T mpLib_80056AFC(void);
/* 056B34 */ UNK_T mpLib_80056B34(void);
/* 056B6C */ enum_t mpLib_80056B6C(enum_t);
/* 056C54 */ bool mpLib_80056C54(s32 idx, Vec3* pos, bool, Vec3*, bool, bool,
                                 float, float, float, float);
/* 057424 */ void mpLib_80057424(s32);
/* 057528 */ UNK_RET mpLib_80057528(UNK_PARAMS);
/* 0575B0 */ UNK_RET mpLib_800575B0(UNK_PARAMS);
/* 057638 */ void mpLib_80057638(s32);
/* 057B4C */ UNK_RET mpLib_80057B4C(UNK_PARAMS);
/* 057BC0 */ void mpLib_80057BC0(s32);
/* 057FDC */ UNK_RET mpLib_80057FDC(UNK_PARAMS);
/* 058044 */ UNK_RET mpLib_80058044(UNK_PARAMS);
/* 0580AC */ void mpLib_800580AC(s32);
/* 0580C8 */ void mpLib_800580C8(int, Ground*, mpLib_GroundCallback);
/* 0580E0 */ void mpLib_800580E0(s32);
/* 0580FC */ void mpLib_800580FC(int, mpLib_Callback*, UNK_T);
/* 05811C */ void mpLib_8005811C(CollData*, s32 ledge_id);
/* 0581A4 */ void mpLib_800581A4(int arg0, int arg1, int arg2);
/* 0581BC */ void mpLib_800581BC(int, mpLib_Callback*, UNK_T);
/* 0581DC */ UNK_RET mpLib_800581DC(UNK_PARAMS);
/* 058560 */ UNK_RET mpLib_80058560(UNK_PARAMS);
/* 058614 */ UNK_RET mpLib_80058614(UNK_PARAMS);
/* 0587FC */ UNK_RET fn_800587FC(UNK_PARAMS);
/* 058820 */ void mpLib_80058820(void);
/* 0588C8 */ int mpLib_800588C8(void);
/* 0588D0 */ void mpLib_800588D0(float left, float bottom, float right,
                                 float top);
/* 058970 */ void mpLib_80058970(f32 arg8, f32 arg9, f32 argA, f32 argB);
/* 0589D0 */ void mpLib_800589D0(f32 arg8, f32 arg9, f32 argA, f32 argB,
                                 f32 argC, f32 argD, f32 argE, f32 argF);
/* 058AA0 */ void mpLib_80058AA0(void);
/* 058ACC */ UNK_RET mpLib_80058ACC(UNK_PARAMS);
/* 058B5C */ UNK_RET mpLib_80058B5C(UNK_PARAMS);
/* 0590F4 */ UNK_RET mpLib_800590F4(UNK_PARAMS);
/* 059404 */ UNK_RET mpLib_80059404(UNK_PARAMS);
/* 059554 */ UNK_RET mpLib_80059554(UNK_PARAMS);
/* 059E60 */ float mpLib_80059E60(UNK_PARAMS);
/* 059FE0 */ UNK_RET mpLib_80059FE0(UNK_PARAMS);
/* 05A220 */ UNK_RET mpLib_8005A220(UNK_PARAMS);
/* 05A2DC */ UNK_RET mpLib_8005A2DC(UNK_PARAMS);
/* 05A340 */ UNK_RET mpLib_8005A340(UNK_PARAMS);

#endif
