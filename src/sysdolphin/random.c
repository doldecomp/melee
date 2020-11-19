#include "random.h"

extern u32 lbl_804D5F90; // seed
extern u32* lbl_804D5F94; // seed_ptr
extern const f32 lbl_804DE790;
extern const f32 lbl_804DE798; // USHRT_MAX

s32 HSD_Rand(void)
{
    *lbl_804D5F94 = *lbl_804D5F94 * 214013 + 2531011;
    return *lbl_804D5F94 >> 0x10;
}

#ifdef NON_MATCHING
f32 HSD_Randf(void)
{
    s32 temp;
    *lbl_804D5F94 = *lbl_804D5F94 * 214013 + 2531011;
    temp = (f32)(*lbl_804D5F94 >> 0x10);
    return (f32)(*lbl_804D5F94 >> 0x10) / lbl_804DE798;
}
#else
asm f32 HSD_Randf(void)
{
    nofralloc
/* 80380528 0037D108  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8038052C 0037D10C  3C 60 00 03 */	lis r3, 0x000343FD@ha
/* 80380530 0037D110  38 63 43 FD */	addi r3, r3, 0x000343FD@l
/* 80380534 0037D114  80 AD A8 F4 */	lwz r5, lbl_804D5F94(r13)
/* 80380538 0037D118  3C 00 43 30 */	lis r0, 0x4330
/* 8038053C 0037D11C  80 85 00 00 */	lwz r4, 0(r5)
/* 80380540 0037D120  7C 64 19 D6 */	mullw r3, r4, r3
/* 80380544 0037D124  3C 63 00 27 */	addis r3, r3, 0x27
/* 80380548 0037D128  38 63 9E C3 */	addi r3, r3, -24893
/* 8038054C 0037D12C  90 65 00 00 */	stw r3, 0(r5)
/* 80380550 0037D130  80 6D A8 F4 */	lwz r3, lbl_804D5F94(r13)
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

#ifdef NON_MATCHING
s32 HSD_Randi(s32 max_val)
{
    s32 temp;
    *lbl_804D5F94 = *lbl_804D5F94 * 214013 + 2531011;
    temp = max_val * (*lbl_804D5F94 >> 0x10);
    return temp / lbl_804DE798;
}
#else
asm s32 HSD_Randi(s32 max_val)
{
    nofralloc
/* 80380580 0037D160  80 AD A8 F4 */	lwz r5, lbl_804D5F94(r13)
/* 80380584 0037D164  3C 80 00 03 */	lis r4, 0x000343FD@ha
/* 80380588 0037D168  38 04 43 FD */	addi r0, r4, 0x000343FD@l
/* 8038058C 0037D16C  80 85 00 00 */	lwz r4, 0(r5)
/* 80380590 0037D170  7C 84 01 D6 */	mullw r4, r4, r0
/* 80380594 0037D174  3C 84 00 27 */	addis r4, r4, 0x27
/* 80380598 0037D178  38 04 9E C3 */	addi r0, r4, -24893
/* 8038059C 0037D17C  90 05 00 00 */	stw r0, 0(r5)
/* 803805A0 0037D180  80 8D A8 F4 */	lwz r4, lbl_804D5F94(r13)
/* 803805A4 0037D184  80 04 00 00 */	lwz r0, 0(r4)
/* 803805A8 0037D188  54 00 84 3E */	srwi r0, r0, 0x10
/* 803805AC 0037D18C  7C 03 01 D6 */	mullw r0, r3, r0
/* 803805B0 0037D190  7C 03 86 70 */	srawi r3, r0, 0x10
/* 803805B4 0037D194  7C 63 01 94 */	addze r3, r3
/* 803805B8 0037D198  4E 80 00 20 */	blr 
}
#endif

#pragma push 
#pragma force_active on
#pragma peephole on
void _HSD_RandForgetMemory(u32* low, u32* high)
{
    if (low <= lbl_804D5F94 && lbl_804D5F94 < high){
        lbl_804D5F94 = &lbl_804D5F90;
    }
    return;
}
#pragma pop
