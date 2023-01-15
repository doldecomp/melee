#ifndef MELEE_MP_MPLIB_H
#define MELEE_MP_MPLIB_H

#include <dolphin/mtx/types.h>
#include <melee/ft/fighter.h>

bool func_80054ED8(s32);
unk_t func_80056B34(void);
unk_t func_80056AC4(void);
unk_t func_80056A54(void);
unk_t func_80056AFC(void);

bool func_800501CC(f32 surface_normal_y, f32 surface_normal_x, f32 right_x,
                   f32 right_y, Vec3* coll_vec, unk_t, unk_t, unk_t, u32, u32);

unk_t func_80056A8C(void);
unk_t func_80056A1C(void);

bool func_800509B8(f32 surface_normal_y, f32 surface_normal_x, f32 left_x,
                   f32 left_y, Vec3* coll_vec, unk_t, unk_t, unk_t, u32, u32);

unk_t func_80054CEC(void);

s32 func_80051EC8(Vec3*, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_80053DA4(u32, f32*);
void func_80053ECC(u32, f32*);
void func_80053FF4(s32, Vec3*);
void func_80054158(s32, Vec3*);

/// @todo Params not confirmed.
bool func_800567C0(s32 wall_id, Vec3* ecb_side_vtx, Vec3* result);

bool func_80056C54(s32 idx, Vec3* pos, bool, Vec3*, bool, bool, f32, f32, f32,
                   f32);

void func_8005811C(CollData*, s32 ledge_id);

/// @returns A ground index.
s32 func_8004DB78(s32 gr_idx);

/// @returns A ground index.
s32 func_8004DC04(s32 gr_idx);

void func_8004D288(unk_t);
void func_80058820(void);
void func_800552B0(s16 x, HSD_JObj*, s16 z);
void func_80055E9C(s16 x);
void func_8004D17C(void);
void func_80057424(s16);
void func_80057638(s16);
void func_80057BC0(s16);
bool func_80054F68(s32, s32);

#endif
