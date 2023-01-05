#ifndef MELEE_MP_MPLIB_H
#define MELEE_MP_MPLIB_H

#include <dolphin/types.h>

unk_t func_80054F68();
unk_t func_80054ED8();
unk_t func_80054ED8();
unk_t func_80056B34();
unk_t func_80056AC4();
unk_t func_80056A54();
unk_t func_80056AFC();
BOOL func_800501CC(f32 surface_normal_y, f32 surface_normal_x, f32 right_x,
                   f32 right_y, VecPtr coll_vec, unk_t, unk_t, unk_t, u32, u32);
unk_t func_80056A8C();
unk_t func_80056A1C();
func_800509B8(f32 surface_normal_y, f32 surface_normal_x, f32 left_x,
              f32 left_y, VecPtr coll_vec, unk_t, unk_t, unk_t, u32, u32);
unk_t func_80054CEC();

s32 func_80051EC8(Vec*, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32);
void func_80053DA4(u32, f32*);
void func_80053ECC(u32, f32*);
void func_80053FF4(s32, Vec*);
void func_80054158(s32, Vec*);
s32 func_800567C0(s32 /*wallID?*/, Vec* /*ecb_side_vertex?*/, Vec* result);

#endif
