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
s32 func_8033F2B8(s32);
s32 func_8033F2CC(s32);
void func_8033F954(s32, s32, s32);
void func_8033FC60(s32);
void func_8033FC8C();
void func_8033F758(s32, s32, u8, s32, s32, s32, s32, s32);

#endif
