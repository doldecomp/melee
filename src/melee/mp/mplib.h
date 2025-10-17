#ifndef GALE01_04D164
#define GALE01_04D164

#include <placeholder.h>
#include <platform.h>

#include "dolphin/gx/GXStruct.h"

#include "ft/forward.h"
#include "gr/forward.h"
#include "lb/forward.h"
#include "mp/forward.h"
#include <baselib/forward.h>

#include <common_structs.h>
#include <dolphin/mtx.h>

/* 04D164 */ mp_CollData* mpLib_8004D164(void);
/* 04D16C */ CollVtx* mpLib_8004D16C(void);
/* 04D174 */ CollLine* mpLib_8004D174(void);
/* 04D17C */ CollJoint* mpLib_8004D17C(void);
/* 04D184 */ void mpLib_8004D184(mp_CollData* coll_data);
/* 04D288 */ void mpLib_8004D288(mp_CollData* coll_data);
/* 04DB78 */ int mpLib_8004DB78(int line_id);
/* 04DC04 */ int mpLib_8004DC04(int line_id);
/* 04DD90 */ int mpLib_8004DD90(int line_id, Vec3*, float* y_out,
                                u32* flags_out, Vec3* normal_out);
/* 04E090 */ int mpLib_8004E090(int line_id, Vec3*, float* y_out,
                                u32* flags_out, Vec3* normal_out);
/* 04E398 */ int mpLib_8004E398(int line_id, Vec3*, float* x_out,
                                u32* flags_out, Vec3* normal_out);
/* 04E684 */ int mpLib_8004E684(int line_id, Vec3*, float* x_out,
                                u32* flags_out, Vec3* normal_out);
/* 04EBF8 */ bool mpLib_8004EBF8(float*, float*, float, float, float, float,
                                 float, float, float);
/* 04ED5C */ void mpLib_8004ED5C(int, float*, float*, float*, float*);
/* 04F008 */ bool mpLib_8004F008(Vec3*, int*, int*, Vec3*, float, float, float,
                                 float, float, int, int, int,
                                 bool (*)(Fighter_GObj*, int), Fighter_GObj*);
/* 04F400 */ bool mpLib_8004F400(Vec3*, int*, int*, Vec3*, float, float, float,
                                 float, float, int, int, int,
                                 bool (*)(Fighter_GObj*, int), Fighter_GObj*);
/* 04F8A4 */ bool mpLib_8004F8A4(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 04FC2C */ bool mpLib_8004FC2C(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 050068 */ bool mpLib_80050068(float*, float*, float, float, float, float,
                                 float, float, float);
/* 0501CC */ bool mpLib_800501CC(Vec3*, int*, int*, Vec3*, int, int,
                                 float normal_x, float normal_y, float right_x,
                                 float right_y);
/* 05057C */ bool mpLib_8005057C(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 0509B8 */ bool mpLib_800509B8(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float left_x, float left_y);
/* 050D68 */ bool mpLib_80050D68(Vec3*, int*, int*, Vec3*, int, int, float,
                                 float, float, float);
/* 0511A4 */ bool mpLib_800511A4(int*, int, int, float, float, float, float,
                                 float, float, float, float);
/* 0515A0 */ bool mpLib_800515A0(int* line_id, int, int, float, float, float,
                                 float, float, float, float, float);
/* 05199C */ int mpLib_8005199C(Vec3*, int, int);
/* 051BA8 */ int mpLib_80051BA8(Vec3*, int, int, int, int, float, float, float,
                                float);
/* 051EC8 */ bool mpLib_80051EC8(Vec3*, int*, int*, Vec3*, u32, s32, s32,
                                 float, float, float, float);
/* 0524DC */ bool mpLib_800524DC(Vec3*, int*, int*, Vec3*, int, int, float x,
                                 float y, float z, float);
/* 052508 */ bool mpLib_80052508(Vec3*, int*, int*, Vec3*, u32, u32, f32, f32,
                                 f32, f32);
/* 052534 */ int mpLib_80052534(int);
/* 052700 */ int mpLib_80052700(int);
/* 0528CC */ int mpLib_800528CC(int line_id);
/* 052A98 */ int mpLib_80052A98(int line_id);
/* 052C64 */ int mpLib_80052C64(int line_id);
/* 052E30 */ int mpLib_80052E30(int line_id);
/* 052FFC */ int mpLib_80052FFC(int line_id);
/* 0531C8 */ int mpLib_800531C8(int line_id);
/* 053394 */ int mpLib_80053394(int line_id);
/* 053448 */ int mpLib_80053448(int line_id);
/* 0534FC */ int mpLib_800534FC(int line_id);
/* 0536CC */ int mpLib_800536CC(int line_id);
/* 05389C */ int mpLib_8005389C(int line_id);
/* 053950 */ int mpLib_80053950(int line_id);
/* 053A04 */ int mpLib_80053A04(int line_id);
/* 053BD4 */ int mpLib_80053BD4(int line_id);
/* 053DA4 */ void mpLib_80053DA4(int ledge_id, Vec3*);
/* 053ECC */ void mpLib_80053ECC(int ledge_id, Vec3*);
/* 053FF4 */ void mpLib_80053FF4(int line_id, Vec3*);
/* 054158 */ void mpLib_80054158(int line_id, Vec3*);
/* 0542BC */ void mpLib_800542BC(int line_id, Vec3*);
/* 054420 */ void mpLib_80054420(int line_id, Vec3*);
/* 054584 */ CollVtx* mpLib_80054584(int line_id, Vec3*);
/* 0546E8 */ void mpLib_800546E8(int line_id, Vec3*);
/* 05484C */ void mpLib_8005484C(int line_id, Vec3*);
/* 0549B0 */ void mpLib_800549B0(int line_id, Vec3*);
/* 054B14 */ void mpLib_80054B14(int, Vec3*);
/* 054BC0 */ void mpLib_80054BC0(int, Vec3*);
/* 054C6C */ u32 mpLib_80054C6C(int);
/* 054CEC */ u32 mpLib_80054CEC(int);
/* 054D68 */ void mpLib_80054D68(int, u32);
/* 054DFC */ Vec3* mpLib_80054DFC(int, Vec3*);
/* 054ED8 */ bool mpLib_80054ED8(int);
/* 054F68 */ bool mpLib_80054F68(int floor_id, int);
/* 0552B0 */ void mpLib_800552B0(int x, HSD_JObj*, int z);
/* 05541C */ void mpLib_8005541C(int joint_id);
/* 0557D0 */ void mpLib_800557D0(int joint_id);
/* 055C5C */ UNK_RET mpLib_80055C5C(int index);
/* 055E24 */ UNK_RET mpLib_80055E24(int index);
/* 055E9C */ void mpLib_80055E9C(int x);
/* 0565DC */ UNK_RET mpLib_800565DC(int index);
/* 05667C */ void mpLib_8005667C(int index);
/* 0566D8 */ UNK_RET mpLib_800566D8(int index, float*, float*);
/* 0566F8 */ void mpLib_800566F8(int index, float, float);
/* 056710 */ void mpLib_80056710(int index, float, float, float, float);
/* 056758 */ UNK_RET mpLib_80056758(int index, float, float, float, float);
/* 0567C0 */ bool mpGetSpeed(int wall_id, Vec3* ecb_side_vtx, Vec3* speed);
/* 0569EC */ float mpLib_800569EC(u32);
/* 056A1C */ int* mpLib_80056A1C(int, int*);
/* 056A54 */ int mpLib_80056A54(int, int*);
/* 056A8C */ int* mpLib_80056A8C(int, int*);
/* 056AC4 */ int mpLib_80056AC4(int, int*);
/* 056AFC */ int* mpLib_80056AFC(int, int*);
/* 056B34 */ int mpLib_80056B34(int, int*);
/* 056B6C */ int mpLib_80056B6C(int);
/* 056C54 */ bool mpLib_80056C54(int line_id, Vec3* pos, int* id_out, Vec3*,
                                 int*, Vec3*, float, float, float, float);
/* 057424 */ void mpLib_80057424(int idx);
/* 057528 */ void mpLib_80057528(int index);
/* 0575B0 */ void mpLib_800575B0(int);
/* 057638 */ void mpLib_80057638(int);
/* 057B4C */ void mpLib_80057B4C(CollJoint*);
/* 057BC0 */ void mpLib_80057BC0(int);
/* 057FDC */ void mpLib_80057FDC(int index);
/* 058044 */ void mpLib_80058044(int index);
/* 0580AC */ void mpLib_800580AC(int index);
/* 0580C8 */ void mpLib_800580C8(int, Ground*, mpLib_Callback);
/* 0580E0 */ void mpLib_800580E0(int index);
/* 0580FC */ void mpLib_800580FC(int, mpLib_Callback*, Ground**);
/* 05811C */ void mpLib_8005811C(CollData*, int ledge_id);
/* 0581A4 */ void mpLib_800581A4(int index, Ground*, mpLib_Callback);
/* 0581BC */ void mpLib_800581BC(int, mpLib_Callback*, Ground**);
/* 0581DC */ void mpLib_800581DC(int, int);
/* 058560 */ void mpLib_80058560(void);
/* 058614 */ UNK_RET mpLib_80058614(UNK_PARAMS);
/* 0587FC */ void fn_800587FC(HSD_GObj*);
/* 058820 */ void mpLib_80058820(void);
/* 0588C8 */ bool mpLib_800588C8(void);
/* 0588D0 */ void mpLib_800588D0(float left, float bottom, float right,
                                 float top);
/* 058970 */ void mpLib_80058970(float x1, float y1, float x2, float y2);
/* 0589D0 */ void mpLib_800589D0(float x0, float y0, float x1, float y1,
                                 float x2, float y2, float x3, float y3);
/* 058AA0 */ void mpLib_80058AA0(void);
/* 058ACC */ void mpLib_SetupDraw(GXColor);
/* 058B5C */ void mpLib_DrawEcbs(CollData*);
/* 0590F4 */ void mpLib_DrawSnapping(UNK_PARAMS);
/* 059404 */ void mpLib_DrawMatchingLines(int, int, GXColor);
/* 059554 */ void mpLib_80059554(UNK_PARAMS);
/* 059E60 */ void mpLib_80059E60(void);
/* 059FE0 */ void mpLib_DrawCrosses(s16* idx, int len, GXColor);
/* 05A220 */ UNK_RET mpLib_DrawSpecialPoints(UNK_PARAMS);
/* 05A2DC */ void mpLib_8005A2DC(void);
/* 05A340 */ UNK_RET mpLib_DrawZones(UNK_PARAMS);

#endif
