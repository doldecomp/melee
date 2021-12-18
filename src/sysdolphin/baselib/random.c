#include "sysdolphin/baselib/random.h"

u32 seed = 1;
u32* seed_ptr = &seed;
extern const f32 lbl_804DE790;
extern const f32 lbl_804DE798; // USHRT_MAX

s32 HSD_Rand(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return *seed_ptr >> 0x10;
}

inline s32 HSD_Rand_inline(void)
{
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return *seed_ptr >> 0x10;
}

#ifdef NON_MATCHING
f32 HSD_Randf(void) {
    *seed_ptr = *seed_ptr * 214013 + 2531011;
    return (f32)(*seed_ptr >> 0x10) / lbl_804DE790;
}
#else
asm f32 HSD_Randf(void)
{
    nofralloc
/* 80380528 0037D108  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8038052C 0037D10C  3C 60 00 03 */	lis r3, 0x000343FD@ha
/* 80380530 0037D110  38 63 43 FD */	addi r3, r3, 0x000343FD@l
/* 80380534 0037D114  80 AD A8 F4 */	lwz r5, seed_ptr(r13)
/* 80380538 0037D118  3C 00 43 30 */	lis r0, 0x4330
/* 8038053C 0037D11C  80 85 00 00 */	lwz r4, 0(r5)
/* 80380540 0037D120  7C 64 19 D6 */	mullw r3, r4, r3
/* 80380544 0037D124  3C 63 00 27 */	addis r3, r3, 0x27
/* 80380548 0037D128  38 63 9E C3 */	addi r3, r3, -24893
/* 8038054C 0037D12C  90 65 00 00 */	stw r3, 0(r5)
/* 80380550 0037D130  80 6D A8 F4 */	lwz r3, seed_ptr(r13)
/* 80380554 0037D134  C8 42 ED B8 */	lfd f2, lbl_804DE798(r2)
/* 80380558 0037D138  80 63 00 00 */	lwz r3, 0(r3)
/* 8038055C 0037D13C  C0 02 ED B0 */	lfs f0, lbl_804DE790(r2)
/* 80380560 0037D140  54 63 84 3E */	srwi r3, r3, 0x10
/* 80380564 0037D144  90 61 00 0C */	stw r3, 0xc(r1)
/* 80380568 0037D148  90 01 00 08 */	stw r0, 8(r1)
/* 8038056C 0037D14C  C8 21 00 08 */	lfd f1, 8(r1)
/* 80380570 0037D150  EC 21 10 28 */	fsubs f1, f1, f2
/* 80380574 0037D154  EC 21 00 24 */	fdivs f1, f1, f0
/* 80380578 0037D158  38 21 00 10 */	addi r1, r1, 0x10
/* 8038057C 0037D15C  4E 80 00 20 */	blr 
}
#endif

#pragma push 
#pragma peephole on
s32 HSD_Randi(s32 max_val) {
    return (max_val * HSD_Rand_inline()) / 0x10000;
}

void _HSD_RandForgetMemory(u32* low, u32* high)
{
    if (low <= seed_ptr && seed_ptr < high){
        seed_ptr = &seed;
    }
    return;
}
#pragma pop
