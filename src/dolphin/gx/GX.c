#include <dolphin/gx/GX.h>

#pragma region variables
extern f32 lbl_804DE2F8;
extern f32 lbl_804DE300;
extern f32 lbl_804DE308;
extern f32 lbl_804DE30C;
#pragma endregion

#pragma region unordered
extern void func_8033F3AC();
extern void func_8033FCD4(s32);
extern void local_8033D3E4();
extern s32 func_80341878(s32);
extern void GXSetCurrentMtx(s32);
extern void func_8033FDA0(__GXFifoLinkObj *, s32, u8 *);
extern void GXSetFieldMode(s8, s32);
extern void GXSetNumChans(s8);
extern void GXSetPixelFmt(s32, s32);
extern void func_8033D408(s16, s32, s16, s16);
extern void func_8033D588(s32);
extern void func_8033D73C(s32);
extern void func_8033D768(s32);
extern u32 func_8033D7E4(f32);
extern void func_8033D8A0(u8 *, s32);
extern void func_8033D908(s8, u8 *, s8, u8 *);
extern void func_8033DB30(s32);
extern void func_8033DE4C();
extern void func_8033F270(__GXFifoLinkObj *, s32, u8 *);

#pragma region inline
extern GXTexRegionCallback func_8033F2B8(GXTexRegionCallback);
extern GXTexRegionCallback func_8033F2CC(GXTexRegionCallback);
#pragma endregion

extern void func_8033F954(s32, s32, s32);
extern void func_8033FC60(s32);
extern void func_8033FC8C();
extern void func_8033F758(s32, s32, u8, s32, s32, s32, s32, s32);
extern void func_8033FDC4(s32, s32);

#pragma region inline
extern void func_8033FF68(s32, s32, s32, s32, s32);
extern void func_8033FFE8(s32, s32, s32, s32, s32);
#pragma endregion

#pragma region inline
extern void func_8034006C(s32, s32, s32, s32, s32, s32);
extern void func_8034012C(s32, s32, s32, s32, s32, s32);
#pragma endregion

#pragma region inline
extern void func_80340348(s32, s32);
extern void func_803403B4(s32, s32);
#pragma endregion

extern void func_80340420(s32, s32, s32);
extern void func_80340478(s32, s32, s32, s32, s32);
extern void func_8034051C(s32, s32, s32, s32, s32);
extern void func_8034056C(s32, s32, s32);
extern void func_803405F0(u32, s32, s32, s32);
extern void func_80340790(s8);
extern void func_803407C4(s32, u8 *, f32, f32, f32, f32);
extern void func_80340790(s8);
extern void func_80340B3C(s8, s16, s32 *);
extern void func_8033EE20(s32);
extern void func_80340C3C(s32, s32, s32, s32);

#pragma region inline
extern void func_80340D40(s32);
extern void func_80340D80(s32);
extern void func_80340E38(s32);
extern void func_80340F88(s32);

// very similar but 2 params
extern void func_80340FC8(s32, s32);
#pragma endregion

extern void func_80340DC0(s8, s32, s32);

extern void func_8034101C(s32, s8);
extern void func_8034154C(void *, u32, s8);

#pragma region inline
extern void func_80341494(void *, s32);
extern void func_803414D0(void *, s32);
#pragma endregion

s32 func_8033E78C(u16, u16, s32, u8, u8);
extern void func_803415D0(BOOL, f32, f32, f32, f32, f32, f32);
extern void func_803416EC(f32, f32, f32, f32, f32, f32);
extern void func_8034175C(s32, s32, s32, s32);
extern void func_8034180C(s32, s32);
extern void func_80341850(s32);
extern void func_803418FC(u32, u32);
extern void func_80342194();

#pragma region private
extern void func_803410D4(f32, f32);
extern void func_80341408(void *, s8 *, s8 *);
extern void func_80341470(void *, s8 *);
extern void func_8034143C(void *, s8 *, s8 *);
#pragma endregion

#pragma endregion

extern void __GXSetDirtyState();
extern void func_8033D0DC(s32, s32, s16); // calls __GXSetDirtyState inlined
extern void local_8033D1B8();
extern void func_8033D240(s32, s32);
extern void func_8033D298(s32, s32);
extern void func_8033D2EC(s32, s32, s32);
extern void func_8033D350(s32);
extern void func_8033D3A0(s32);
extern void func_8033D408(s16, s32, s16, s16);
