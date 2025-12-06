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

/* 04D164 */ MapCollData* mpLib_8004D164(void);
/* 04D16C */ CollVtx* mpGetGroundCollVtx(void);
/* 04D174 */ CollLine* mpGetGroundCollLine(void);
/* 04D17C */ CollJoint* mpGetGroundCollJoint(void);
/* 04D184 */ void mpPruneEmptyLines(MapCollData* coll_data);
/* 04D288 */ void mpLibLoad(MapCollData* coll_data);
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
/* 04EBF8 */ bool mpLineIntersectionH(float* int_x, float* int_y, float a0x,
                                      float a0y, float a1x, float b0x,
                                      float b0y, float b1x, float b1y);
/* 04ED5C */ void mpLib_8004ED5C(int, float*, float*, float*, float*);
/* 04F008 */ bool mpCheckFloor(float ax, float ay, float bx, float by,
                               float y_offset, Vec3* vec_out, int* line_id_out,
                               u32* flags_out, Vec3* normal_out,
                               int line_id_skip, int joint_id_skip,
                               int joint_id_only, bool (*)(Fighter_GObj*, int),
                               Fighter_GObj*);
/* 04F400 */ bool mpCheckFloorRemap(float ax, float ay, float bx, float by,
                                    float y_offset, Vec3* vec_out,
                                    int* line_id_out, u32* flags_out,
                                    Vec3* normal_out, int line_id_skip,
                                    int joint_id_skip, int joint_id_only,
                                    bool (*)(Fighter_GObj*, int),
                                    Fighter_GObj*);
/* 04F8A4 */ bool mpCheckCeiling(float ax, float ay, float bx, float by,
                                 Vec3* vec_out, int* line_id_out,
                                 u32* flags_out, Vec3* normal_out,
                                 int joint_id_skip, int joint_id_only);
/* 04FC2C */ bool mpCheckCeilingRemap(float ax, float ay, float bx, float by,
                                      Vec3* vec_out, int* line_id_out,
                                      u32* flags_out, Vec3* normal_out,
                                      int joint_id_skip, int joint_id_only);
/* 050068 */ bool mpLineIntersectionV(float* int_x, float* int_y, float a0x,
                                      float a0y, float a1y, float b0x,
                                      float b0y, float b1x, float b1y);
/* 0501CC */ bool mpCheckLeftWall(float ax, float ay, float bx, float by,
                                  Vec3* vec_out, int* line_id_out,
                                  u32* flags_out, Vec3* normal_out,
                                  int joint_id_skip, int joint_id_only);
/* 05057C */ bool mpCheckLeftWallRemap(float ax, float ay, float bx, float by,
                                       Vec3* vec_out, int* line_id_out,
                                       u32* flags_out, Vec3* normal_out,
                                       int joint_id_skip, int joint_id_only);
/* 0509B8 */ bool mpCheckRightWall(float ax, float ay, float bx, float by,
                                   Vec3* vec_out, int* line_id_out,
                                   u32* flags_out, Vec3* normal_out,
                                   int joint_id_skip, int joint_id_only);
/* 050D68 */ bool mpCheckRightWallRemap(float ax, float ay, float bx, float by,
                                        Vec3* vec_out, int* line_id_out,
                                        u32* flags_out, Vec3* normal_out,
                                        int joint_id_skip, int joint_id_only);
/* 0511A4 */ bool mpLib_800511A4_RightWall(float ax, float ay, float bx,
                                           float by, float cx, float cy,
                                           float dx, float dy,
                                           int* line_id_out, int joint_id_skip,
                                           int joint_id_only);
/* 0515A0 */ bool mpLib_800515A0_LeftWall(float a0x, float a0y, float a1x,
                                          float a1y, float b0x, float b0y,
                                          float b1x, float b1y,
                                          int* line_id_out, int joint_id_skip,
                                          int joint_id_only);
/* 05199C */ int mpLib_8005199C_Floor(Vec3*, int joint_id_skip,
                                      int joint_id_only);
/* 051BA8 */ int mpLib_80051BA8_Floor(Vec3* out_vec, int line_id_skip,
                                      int joint_id_skip, int joint_id_only,
                                      int dir, float left, float bottom,
                                      float right, float top);
/* 051EC8 */ bool mpCheckMultiple(float x0, float y0, float x1, float y1,
                                  Vec3* pos_out, int* line_id_out,
                                  u32* flags_out, Vec3* normal_out, u32 checks,
                                  int joint_id_skip, int joint_id_only);
/* 0524DC */ bool mpCheckAllRemap(Vec3* pos_out, int* line_id_out,
                                  u32* flags_out, Vec3* normal_out,
                                  int joint_id_skip, int joint_id_only,
                                  float x0, float y0, float x1, float y1);
/* 052508 */ bool mpCheckAll(Vec3* pos_out, int* line_id_out, u32* flags_out,
                             Vec3* normal_out, int joint_id_skip,
                             int joint_id_only, float x0, float y0, float x1,
                             float y1);
/* 052534 */ int mpLineNextNonFloor(int line_id);
/* 052700 */ int mpLinePrevNonFloor(int line_id);
/* 0528CC */ int mpLinePrevNonCeiling(int line_id);
/* 052A98 */ int mpLineNextNonCeiling(int line_id);
/* 052C64 */ int mpLineNextNonLeftWall(int line_id);
/* 052E30 */ int mpLinePrevNonLeftWall(int line_id);
/* 052FFC */ int mpLinePrevNonRightWall(int line_id);
/* 0531C8 */ int mpLineNextNonRightWall(int line_id);
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
/* 053FF4 */ void mpFloorGetRight(int line_id, Vec3*);
/* 054158 */ void mpFloorGetLeft(int line_id, Vec3*);
/* 0542BC */ void mpCeilingGetRight(int line_id, Vec3*);
/* 054420 */ void mpCeilingGetLeft(int line_id, Vec3*);
/* 054584 */ void mpLeftWallGetTop(int line_id, Vec3*);
/* 0546E8 */ void mpLeftWallGetBottom(int line_id, Vec3*);
/* 05484C */ void mpRightWallGetTop(int line_id, Vec3*);
/* 0549B0 */ void mpRightWallGetBottom(int line_id, Vec3*);
/* 054B14 */ void mpLineGetV1Pos(int line_id, Vec3* pos_out);
/* 054BC0 */ void mpLineGetV0Pos(int line_id, Vec3* pos_out);
/* 054C6C */ enum_t mpLineGetKind(int line_id);
/* 054CEC */ u32 mpLineGetFlags(int line_id);
/* 054D68 */ void mpLib_80054D68(int line_id, u32 flags);
/* 054DFC */ Vec3* mpLineGetNormal(int line_id, Vec3* normal_out);
/* 054ED8 */ bool mpLib_80054ED8(int line_id);
/* 054F68 */ bool mpLinesConnected(int start_id, int target_id);
/* 0552B0 */ void mpLib_800552B0(int joint_id, HSD_JObj*, int z);
/* 05541C */ void mpJointHide(int joint_id);
/* 0557D0 */ void mpJointUnhide(int joint_id);
/* 055C5C */ void mpJointUpdateDynamics(int joint_id);
/* 055E24 */ void mpLib_80055E24(int joint_id);
/* 055E9C */ void mpLib_80055E9C(int joint_id);
/* 0565DC */ void mpJointUpdateBounding(int joint_id);
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
/* 057638 */ void mpJointListAdd(int joint_id);
/* 057B4C */ void mpJointListUnlink(CollJoint*);
/* 057BC0 */ void mpLib_80057BC0(int joint_id);
/* 057FDC */ void mpLib_80057FDC(int joint_id);
/* 058044 */ void mpLib_80058044(int joint_id);
/* 0580AC */ void mpJointSetB10(int joint_id);
/* 0580C8 */ void mpJointSetCb1(int joint_id, Ground*, mpLib_Callback);
/* 0580E0 */ void mpJointClearCb1(int joint_id);
/* 0580FC */ void mpJointGetCb1(int joint_id, mpLib_Callback*, Ground**);
/* 05811C */ void mpLib_8005811C(CollData*, int ledge_id);
/* 0581A4 */ void mpJointSetCb2(int joint_id, Ground*, mpLib_Callback);
/* 0581BC */ void mpJointGetCb2(int joint_id, mpLib_Callback*, Ground**);
/* 0581DC */ void mpLib_800581DC(int joint_id0, int joint_id1);
/* 058560 */ void mpLib_80058560(void);
/* 058614 */ void mpLib_80058614_Floor(void);
/* 0587FC */ void mpLib_800587FC(HSD_GObj*);
/* 058820 */ void mpLib_80058820(void);
/* 0588C8 */ bool mpCheckedBounding(void);
/* 0588D0 */ void mpBoundingCheck(float left, float bottom, float right,
                                  float top);
/* 058970 */ void mpBoundingCheck2(float x1, float y1, float x2, float y2);
/* 0589D0 */ void mpBoundingCheck3(float x0, float y0, float x1, float y1,
                                   float x2, float y2, float x3, float y3);
/* 058AA0 */ void mpUncheckBounding(void);
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
