#ifndef GALE01_04D164
#define GALE01_04D164

#include <dolphin/mtx/forward.h>

#include "ft/fighter.h"

#include <common_structs.h>

typedef void (*mpLib_Callback)(s32, s32, CollData*, s32, s32, f32);

bool mpLib_80054ED8(s32);
unk_t mpLib_80056B34(void);
unk_t mpLib_80056AC4(void);
unk_t mpLib_80056A54(void);
unk_t mpLib_80056AFC(void);

bool mpLib_800501CC(f32 surface_normal_y, f32 surface_normal_x, f32 right_x,
                    f32 right_y, Vec3* coll_vec, unk_t, unk_t, unk_t, u32,
                    u32);

unk_t mpLib_80056A8C(void);
unk_t mpLib_80056A1C(void);

bool mpLib_800509B8(f32 surface_normal_y, f32 surface_normal_x, f32 left_x,
                    f32 left_y, Vec3* coll_vec, unk_t, unk_t, unk_t, u32, u32);

u32 mpLib_80054CEC(enum_t);

s32 mpLib_80051EC8(Vec3*, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
void mpLib_80053DA4(int ledge_id, Vec3*);
void mpLib_80053ECC(int ledge_id, Vec3*);
void mpLib_80053FF4(s32, Vec3*);
void mpLib_80054158(s32, Vec3*);

/// @todo Params not confirmed.
bool mpLib_800567C0(s32 wall_id, Vec3* ecb_side_vtx, Vec3* result);

bool mpLib_80056C54(s32 idx, Vec3* pos, bool, Vec3*, bool, bool, f32, f32, f32,
                    f32);

void mpLib_8005811C(CollData*, s32 ledge_id);

/// @returns A ground index.
s32 mpLib_8004DB78(s32 gr_idx);

/// @returns A ground index.
s32 mpLib_8004DC04(s32 gr_idx);

void mpLib_8004D288(unk_t);
void mpLib_80058820(void);
void mpLib_800552B0(s16 x, HSD_JObj*, s16 z);
void mpLib_80055E9C(s16 x);
void mpLib_8004D17C(void);
void mpLib_80057424(s16);
void mpLib_80057638(s16);
void mpLib_80057BC0(s16);
bool mpLib_80054F68(s32, s32);
s32 mpLib_80052700(int idx);
s32 mpLib_8004F008(void);
s32 mpLib_80054584(void);
s32 mpLib_8004DD90(void);
s32 mpLib_8004E398(void);
void mpLib_800588D0(f32 left, f32 bottom, f32 right, f32 top);
enum_t mpLib_80056B6C(enum_t);
void mpLib_800580FC(int, mpLib_Callback*, unk_t);
void mpLib_800581BC(int, mpLib_Callback*, unk_t);
enum_t mpLib_80054C6C(int);
void mpLib_80058AA0(void);
enum_t mpLib_8004E090(int idx, Vec3*, f32*, u32*, Vec3* normal);
void mpLib_800569EC(void);
/* 04F8A4 */ /* static */ UNK_RET mpLib_8004F8A4(UNK_PARAMS);

#endif
