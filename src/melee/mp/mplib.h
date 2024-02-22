#ifndef GALE01_04D164
#define GALE01_04D164

#include <platform.h>
#include "mp/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ft/types.h"

#include <common_structs.h>
#include <placeholder.h>

/* 04D17C */ int mpLib_8004D17C(void);
/* 04D288 */ void mpLib_8004D288(UNK_T);
/* 04DB78 */ s32 mpLib_8004DB78(s32 gr_idx);
/* 04DC04 */ s32 mpLib_8004DC04(s32 gr_idx);
/* 04DD90 */ bool mpLib_8004DD90(int idx, float*, float*, UNK_T, Vec3* normal);
/* 04E090 */ enum_t mpLib_8004E090(int idx, Vec3*, float*, u32*, Vec3* normal);
/* 04E398 */ bool mpLib_8004E398(int, float*, int, int, int, float);
/* 04F008 */ bool mpLib_8004F008(Vec3*, int*, int, int, int, int, int, int,
                                 float, float, float, float, int, float);
/* 04F8A4 */ UNK_RET mpLib_8004F8A4(UNK_PARAMS);
/* 0501CC */ bool mpLib_800501CC(float surface_normal_y,
                                 float surface_normal_x, float right_x,
                                 float right_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 UNK_T, u32, u32);
/* 0509B8 */ bool mpLib_800509B8(float surface_normal_y,
                                 float surface_normal_x, float left_x,
                                 float left_y, Vec3* coll_vec, UNK_T, UNK_T,
                                 UNK_T, u32, u32);
/* 051EC8 */ s32 mpLib_80051EC8(Vec3*, s32, s32, s32, s32, s32, s32, float,
                                float, float, float);
/* 0524DC */ bool mpLib_800524DC(int, int, int, int, int, int, float x,
                                 float y, float z, float);
/* 052508 */ UNK_RET mpLib_80052508(UNK_PARAMS);
/* 052700 */ s32 mpLib_80052700(int idx);
/* 053DA4 */ void mpLib_80053DA4(int ledge_id, Vec3*);
/* 053ECC */ void mpLib_80053ECC(int ledge_id, Vec3*);
/* 053FF4 */ void mpLib_80053FF4(s32, Vec3*);
/* 054158 */ void mpLib_80054158(s32, Vec3*);
/* 054584 */ s32 mpLib_80054584(int, float*);
/* 054C6C */ enum_t mpLib_80054C6C(int);
/* 054CEC */ u32 mpLib_80054CEC(enum_t);
/* 054DFC */ void mpLib_80054DFC(enum_t, Vec3*);
/* 054ED8 */ bool mpLib_80054ED8(int);
/* 054F68 */ bool mpLib_80054F68(s32, s32);
/* 0552B0 */ void mpLib_800552B0(s16 x, HSD_JObj*, s16 z);
/* 055E9C */ void mpLib_80055E9C(s16 x);
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
/* 057638 */ void mpLib_80057638(s32);
/* 057BC0 */ void mpLib_80057BC0(s32);
/* 0580FC */ void mpLib_800580FC(int, mpLib_Callback*, UNK_T);
/* 05811C */ void mpLib_8005811C(CollData*, s32 ledge_id);
/* 0581BC */ void mpLib_800581BC(int, mpLib_Callback*, UNK_T);
/* 058820 */ void mpLib_80058820(void);
/* 0588D0 */ void mpLib_800588D0(float left, float bottom, float right,
                                 float top);
/* 058AA0 */ void mpLib_80058AA0(void);
/* 04D164 */ int mpLib_8004D164(void);
/* 04D16C */ int mpLib_8004D16C(void);
/* 04D174 */ mp_UnkStruct2* mpLib_8004D174(void);

#endif
