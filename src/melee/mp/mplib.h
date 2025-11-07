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

/* 04D164 */ mpCollData* mpLib_8004D164(void);
/* 04D16C */ CollVtx* mpGetGroundCollVtx(void);
/* 04D174 */ CollLine* mpGetGroundCollLine(void);
/* 04D17C */ CollJoint* mpGetGroundCollJoint(void);
/* 04D184 */ void mpPruneEmptyLines(mpCollData* coll_data);
/* 04D288 */ void mpLibLoad(mpCollData* coll_data);
/* 04DB78 */ int mpLineGetNext(int line_id);
/* 04DC04 */ int mpLineGetPrev(int line_id);
/* 04DD90 */ int mpLib_8004DD90_Floor(int line_id, Vec3*, float* y_out,
                                      u32* flags_out, Vec3* normal_out);
/* 04E090 */ int mpLib_8004E090_Ceiling(int line_id, Vec3*, float* y_out,
                                        u32* flags_out, Vec3* normal_out);
/* 04E398 */ int mpLib_8004E398_LeftWall(int line_id, Vec3*, float* x_out,
                                         u32* flags_out, Vec3* normal_out);
/* 04E684 */ int mpLib_8004E684_RightWall(int line_id, Vec3*, float* x_out,
                                          u32* flags_out, Vec3* normal_out);
/* 04EBF8 */ bool mpLib_8004EBF8(float*, float*, float, float, float, float,
                                 float, float, float);
/* 04ED5C */ void mpLib_8004ED5C(int, float*, float*, float*, float*);
/* 04F008 */ bool mpLib_8004F008_Floor(
    float ax, float ay, float bx, float by, float y_offset, Vec3* vec_out,
    int* line_id_out, u32* flags_out, Vec3* normal_out, int line_id,
    int joint_id0, int joint_id1, bool (*)(Fighter_GObj*, int), Fighter_GObj*);
/* 04F400 */ bool mpLib_8004F400_Floor(
    float ax, float ay, float bx, float by, float y_offset, Vec3* vec_out,
    int* line_id_out, u32* flags_out, Vec3* normal_out, int line_id,
    int joint_id0, int joint_id1, bool (*)(Fighter_GObj*, int), Fighter_GObj*);
/* 04F8A4 */ bool mpLib_8004F8A4_Ceiling(float ax, float ay, float bx,
                                         float by, Vec3* vec_out,
                                         int* line_id_out, u32* flags_out,
                                         Vec3* normal_out, int joint_id0,
                                         int joint_id1);
/* 04FC2C */ bool mpLib_8004FC2C_Ceiling(float ax, float ay, float bx,
                                         float by, Vec3* vec_out,
                                         int* line_id_out, u32* flags_out,
                                         Vec3* normal_out, int joint_id0,
                                         int joint_id1);
/* 050068 */ bool mpLib_80050068(float*, float*, float, float, float, float,
                                 float, float, float);
/* 0501CC */ bool mpLib_800501CC_LeftWall(float ax, float ay, float bx,
                                          float by, Vec3* vec_out,
                                          int* line_id_out, u32* flags_out,
                                          Vec3* normal_out, int joint_id0,
                                          int joint_id1);
/* 05057C */ bool mpLib_8005057C_LeftWall(float ax, float ay, float bx,
                                          float by, Vec3* vec_out,
                                          int* line_id_out, u32* flags_out,
                                          Vec3* normal_out, int joint_id0,
                                          int joint_id1);
/* 0509B8 */ bool mpLib_800509B8_RightWall(float ax, float ay, float bx,
                                           float by, Vec3* vec_out,
                                           int* line_id_out, u32* flags_out,
                                           Vec3* normal_out, int joint_id0,
                                           int joint_id1);
/* 050D68 */ bool mpLib_80050D68_RightWall(float ax, float ay, float bx,
                                           float by, Vec3* vec_out,
                                           int* line_id_out, u32* flags_out,
                                           Vec3* normal_out, int joint_id0,
                                           int joint_id1);
/* 0511A4 */ bool mpLib_800511A4_RightWall(float ax, float ay, float bx,
                                           float by, float cx, float cy,
                                           float dx, float dy,
                                           int* line_id_out, int joint_id0,
                                           int joint_id1);
/* 0515A0 */ bool mpLib_800515A0_LeftWall(float ax, float ay, float bx,
                                          float by, float cx, float cy,
                                          float dx, float dy, int* line_id_out,
                                          int joint_id0, int joint_id1);
/* 05199C */ int mpLib_8005199C_Floor(Vec3*, int joint_id0, int joint_id1);
/* 051BA8 */ int mpLib_80051BA8_Floor(Vec3* out_vec, int line_id,
                                      int joint_id0, int joint_id1, int dir,
                                      float left, float bottom, float right,
                                      float top);
/* 051EC8 */ bool mpLib_80051EC8(float x0, float y0, float x1, float y1,
                                 Vec3* pos_out, int* line_id_out,
                                 u32* flags_out, Vec3* normal_out, u32 arg4,
                                 int joint_id0, int joint_id1);
/* 0524DC */ bool mpLib_800524DC(Vec3* pos_out, int* line_id_out,
                                 u32* flags_out, Vec3* normal_out,
                                 int joint_id0, int joint_id1, float x0,
                                 float y0, float x1, float y1);
/* 052508 */ bool mpLib_80052508(Vec3* pos_out, int* line_id_out,
                                 u32* flags_out, Vec3* normal_out,
                                 int joint_id0, int joint_id1, float x0,
                                 float y0, float x1, float y1);
/* 052534 */ int mpLib_80052534_Floor(int line_id);
/* 052700 */ int mpLib_80052700_Floor(int line_id);
/* 0528CC */ int mpLib_800528CC_Ceiling(int line_id);
/* 052A98 */ int mpLib_80052A98_Ceiling(int line_id);
/* 052C64 */ int mpLib_80052C64_LeftWall(int line_id);
/* 052E30 */ int mpLib_80052E30_LeftWall(int line_id);
/* 052FFC */ int mpLib_80052FFC_RightWall(int line_id);
/* 0531C8 */ int mpLib_800531C8_RightWall(int line_id);
/* 053394 */ int mpLib_80053394_Floor(int line_id);
/* 053448 */ int mpLib_80053448_Floor(int line_id);
/* 0534FC */ int mpLib_800534FC_Floor(int line_id);
/* 0536CC */ int mpLib_800536CC_Floor(int line_id);
/* 05389C */ int mpLib_8005389C_Ceiling(int line_id);
/* 053950 */ int mpLib_80053950_Ceiling(int line_id);
/* 053A04 */ int mpLib_80053A04_Ceiling(int line_id);
/* 053BD4 */ int mpLib_80053BD4_Ceiling(int line_id);
/* 053DA4 */ void mpLib_80053DA4_Floor(int line_id, Vec3*);
/* 053ECC */ void mpLib_80053ECC_Floor(int line_id, Vec3*);
/* 053FF4 */ void mpLib_80053FF4(int line_id, Vec3*);
/* 054158 */ void mpLib_80054158(int line_id, Vec3*);
/* 0542BC */ void mpLib_800542BC(int line_id, Vec3*);
/* 054420 */ void mpLib_80054420(int line_id, Vec3*);
/* 054584 */ CollVtx* mpLib_80054584(int line_id, Vec3*);
/* 0546E8 */ void mpLib_800546E8(int line_id, Vec3*);
/* 05484C */ void mpLib_8005484C(int line_id, Vec3*);
/* 0549B0 */ void mpLib_800549B0(int line_id, Vec3*);
/* 054B14 */ void mpLineGetV1Pos(int line_id, Vec3* pos_out);
/* 054BC0 */ void mpLineGetV0Pos(int line_id, Vec3* pos_out);
/* 054C6C */ enum_t mpLineGetKind(int line_id);
/* 054CEC */ u32 mpLineGetFlags(int line_id);
/* 054D68 */ void mpLib_80054D68(int line_id, u32 flags);
/* 054DFC */ Vec3* mpLineGetNormal(int line_id, Vec3* normal_out);
/* 054ED8 */ bool mpLib_80054ED8(int line_id);
/* 054F68 */ bool mpLib_80054F68(int start_id, int target_id);
/* 0552B0 */ void mpLib_800552B0(int joint_id, HSD_JObj*, int z);
/* 05541C */ void mpLib_8005541C(int joint_id);
/* 0557D0 */ void mpLib_800557D0(int joint_id);
/* 055C5C */ void mpUpdateDynamics(int joint_id);
/* 055E24 */ void mpLib_80055E24(int joint_id);
/* 055E9C */ void mpLib_80055E9C(int joint_id);
/* 0565DC */ void mpLib_800565DC(int joint_id);
/* 05667C */ void mpLib_8005667C(int joint_id);
/* 0566D8 */ void mpVtxGetPos(int vtx_id, float* x_out, float* y_out);
/* 0566F8 */ void mpVtxSetPos(int vtx_id, float x, float y);
/* 056710 */ void mpLineSetPos(int line_id, float x0, float y0, float x1,
                               float y1);
/* 056758 */ void mpLib_80056758(int line_id, float x0, float y0, float x1,
                                 float y1);
/* 0567C0 */ bool mpGetSpeed(int line_id, Vec3* pos, Vec3* speed);
/* 0569EC */ float mpLib_800569EC(u32);
/* 056A1C */ int* mpLib_80056A1C(int, int*);
/* 056A54 */ int mpLib_80056A54(int, int*);
/* 056A8C */ int* mpLib_80056A8C(int, int*);
/* 056AC4 */ int mpLib_80056AC4(int, int*);
/* 056AFC */ int* mpLib_80056AFC(int, int*);
/* 056B34 */ int mpLib_80056B34(int, int*);
/* 056B6C */ int mpJointFromLine(int line_id);
/* 056C54 */ bool mpLib_80056C54(int line_id, Vec3* pos, int* line_id_out,
                                 Vec3* vec_out, u32* flags_out,
                                 Vec3* normal_out, float, float, float, float);
/* 057424 */ void mpLib_80057424(int joint_id);
/* 057528 */ void mpLib_80057528(int line_id);
/* 0575B0 */ void mpLib_800575B0(int line_id);
/* 057638 */ void mpLib_80057638(int joint_id);
/* 057B4C */ void mpLib_80057B4C(CollJoint*);
/* 057BC0 */ void mpLib_80057BC0(int joint_id);
/* 057FDC */ void mpLib_80057FDC(int joint_id);
/* 058044 */ void mpLib_80058044(int joint_id);
/* 0580AC */ void mpLib_800580AC(int joint_id);
/* 0580C8 */ void mpJointSetCb1(int joint_id, Ground*, mpLib_Callback);
/* 0580E0 */ void mpJointClearCb1(int joint_id);
/* 0580FC */ void mpJointGetCb1(int joint_id, mpLib_Callback*, Ground**);
/* 05811C */ void mpLib_8005811C(CollData*, int ledge_id);
/* 0581A4 */ void mpJointSetCb2(int joint_id, Ground*, mpLib_Callback);
/* 0581BC */ void mpJointGetCb2(int joint_id, mpLib_Callback*, Ground**);
/* 0581DC */ void mpLib_800581DC(int joint_id0, int joint_id1);
/* 058560 */ void mpLib_80058560(void);
/* 058614 */ void mpLib_80058614_Floor(void);
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
/* 0590F4 */ void mpLib_DrawSnapping(void);
/* 059404 */ void mpLib_DrawMatchingLines(int, int, GXColor);
/* 059554 */ void mpLib_80059554(void);
/* 059E60 */ void mpLib_80059E60(void);
/* 059FE0 */ void mpLib_DrawCrosses(s16* idx, int len, GXColor);
/* 05A220 */ void mpLib_DrawSpecialPoints(void);
/* 05A2DC */ void mpLib_8005A2DC(void);
/* 05A340 */ void mpLib_DrawZones(void);

#endif
