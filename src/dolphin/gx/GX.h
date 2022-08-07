#ifndef _GX_H_
#define _GX_H_

#include <dolphin/gx/GXFifo.h>

s32 func_80341878(s32);
void GXSetCurrentMtx(s32);
void func_8033FDA0(__GXFifoLinkObj *, s32, u8 *);
void GXSetFieldMode(s8, s32);
void GXSetNumChans(s8);
void GXSetPixelFmt(s32, s32);
void func_8033D240(s32, s32);
void func_8033D298(s32, s32);
void func_8033D2EC(s32, s32, s32);
void func_8033D350(s32);
void func_8033D3A0(s32);
void func_8033D408(s16, s32, s16, s16);
void func_8033D588(s32);
void func_8033D73C(s32);
void func_8033D768(s32);
u32 func_8033D7E4(f32);
void func_8033D8A0(u8 *, s32);
void func_8033D908(s8, u8 *, s8, u8 *);
void func_8033DB30(s32);
void func_8033DE4C();
void func_8033F270(__GXFifoLinkObj *, s32, u8 *);

#pragma region inline
GXTexRegionCallback func_8033F2B8(GXTexRegionCallback);
GXTexRegionCallback func_8033F2CC(GXTexRegionCallback);
#pragma endregion

void func_8033F954(s32, s32, s32);
void func_8033FC60(s32);
void func_8033FC8C();
void func_8033F758(s32, s32, u8, s32, s32, s32, s32, s32);
void func_8033FDC4(s32, s32);

#pragma region inline
void func_8033FF68(s32, s32, s32, s32, s32);
void func_8033FFE8(s32, s32, s32, s32, s32);
#pragma endregion

#pragma region inline
void func_8034006C(s32, s32, s32, s32, s32, s32);
void func_8034012C(s32, s32, s32, s32, s32, s32);
#pragma endregion

#pragma region inline
void func_80340348(s32, s32);
void func_803403B4(s32, s32);
#pragma endregion

void func_80340420(s32, s32, s32);
void func_80340478(s32, s32, s32, s32, s32);
void func_8034051C(s32, s32, s32, s32, s32);
void func_8034056C(s32, s32, s32);
void func_803405F0(u32, s32, s32, s32);
void func_80340790(s8);
void func_803407C4(s32, u8 *, f32, f32, f32, f32);
void func_80340790(s8);
void func_80340B3C(s8, s16, s32 *);
void func_8033EE20(s32);
void func_80340C3C(s32, s32, s32, s32);

#pragma region inline
void func_80340D40(s32);
void func_80340D80(s32);
void func_80340E38(s32);
void func_80340F88(s32);

// very similar but 2 params
void func_80340FC8(s32, s32);
#pragma endregion

void func_80340DC0(s8, s32, s32);

void func_8034101C(s32 arg0, s8 arg1);
void func_8034154C(void *arg0, u32 arg1, s8 arg2);
void func_80341494(void *arg0, s32 arg1);

#pragma region private
void func_803410D4();
void func_80341408(void *, s8 *, s8 *);
void func_80341470(void *, s8 *);
#pragma endregion

#endif
