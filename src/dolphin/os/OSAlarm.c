#include <dolphin/types.h>

extern unk_t DecrementerExceptionHandler();
extern unk_t AlarmQueue;
extern unk_t __OSSetExceptionHandler();
extern unk_t __OSGetExceptionHandler();

#pragma push
asm unk_t OSInitAlarm()
{ // clang-format off
    nofralloc
/* 80343720 00340300  7C 08 02 A6 */	mflr r0
/* 80343724 00340304  38 60 00 08 */	li r3, 8
/* 80343728 00340308  90 01 00 04 */	stw r0, 4(r1)
/* 8034372C 0034030C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80343730 00340310  4B FF FE A1 */	bl __OSGetExceptionHandler
/* 80343734 00340314  3C 80 80 34 */	lis r4, DecrementerExceptionHandler@ha
/* 80343738 00340318  38 84 3D F8 */	addi r4, r4, DecrementerExceptionHandler@l
/* 8034373C 0034031C  7C 03 20 40 */	cmplw r3, r4
/* 80343740 00340320  41 82 00 1C */	beq lbl_8034375C
/* 80343744 00340324  38 00 00 00 */	li r0, 0
/* 80343748 00340328  38 6D BC B8 */	addi r3, r13, AlarmQueue
/* 8034374C 0034032C  90 03 00 04 */	stw r0, 4(r3)
/* 80343750 00340330  38 60 00 08 */	li r3, 8
/* 80343754 00340334  90 0D BC B8 */	stw r0, AlarmQueue(r13)
/* 80343758 00340338  4B FF FE 5D */	bl __OSSetExceptionHandler
lbl_8034375C:
/* 8034375C 0034033C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80343760 00340340  38 21 00 08 */	addi r1, r1, 8
/* 80343764 00340344  7C 08 03 A6 */	mtlr r0
/* 80343768 00340348  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop