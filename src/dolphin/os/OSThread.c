#include <dolphin/os/OSThread.h>

extern unk_t _stack_end;
extern unk_t _db_stack_end;
extern unk_t lbl_804A7FB8;
extern unk_t lbl_804D73D8;
extern unk_t lbl_804D73DC;
extern unk_t lbl_804D73E0;

#pragma push
asm void __OSThreadInit(void)
{ // clang-format off
    nofralloc
/* 8034AC04 003477E4  7C 08 02 A6 */	mflr r0
/* 8034AC08 003477E8  3C 60 80 4A */	lis r3, lbl_804A7FB8@ha
/* 8034AC0C 003477EC  90 01 00 04 */	stw r0, 4(r1)
/* 8034AC10 003477F0  38 00 00 02 */	li r0, 2
/* 8034AC14 003477F4  38 80 00 10 */	li r4, 0x10
/* 8034AC18 003477F8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034AC1C 003477FC  BF 41 00 08 */	stmw r26, 8(r1)
/* 8034AC20 00347800  3B 83 7F B8 */	addi r28, r3, lbl_804A7FB8@l
/* 8034AC24 00347804  3B FC 04 10 */	addi r31, r28, 0x410
/* 8034AC28 00347808  3B A0 00 00 */	li r29, 0
/* 8034AC2C 0034780C  38 7F 02 E8 */	addi r3, r31, 0x2e8
/* 8034AC30 00347810  B0 1C 06 D8 */	sth r0, 0x6d8(r28)
/* 8034AC34 00347814  38 00 00 01 */	li r0, 1
/* 8034AC38 00347818  B0 1C 06 DA */	sth r0, 0x6da(r28)
/* 8034AC3C 0034781C  38 00 FF FF */	li r0, -1
/* 8034AC40 00347820  90 9C 06 E4 */	stw r4, 0x6e4(r28)
/* 8034AC44 00347824  90 9C 06 E0 */	stw r4, 0x6e0(r28)
/* 8034AC48 00347828  93 BC 06 DC */	stw r29, 0x6dc(r28)
/* 8034AC4C 0034782C  90 1C 06 E8 */	stw r0, 0x6e8(r28)
/* 8034AC50 00347830  93 BC 07 00 */	stw r29, 0x700(r28)
/* 8034AC54 00347834  48 00 00 D9 */	bl OSInitThreadQueue
/* 8034AC58 00347838  93 BC 07 08 */	stw r29, 0x708(r28)
/* 8034AC5C 0034783C  3F C0 80 00 */	lis r30, 0x800000D8@ha
/* 8034AC60 00347840  38 7F 00 00 */	addi r3, r31, 0
/* 8034AC64 00347844  93 BC 07 04 */	stw r29, 0x704(r28)
/* 8034AC68 00347848  93 FE 00 D8 */	stw r31, 0x800000D8@l(r30)
/* 8034AC6C 0034784C  4B FF A5 E9 */	bl OSClearContext
/* 8034AC70 00347850  7F E3 FB 78 */	mr r3, r31
/* 8034AC74 00347854  4B FF A4 19 */	bl OSSetCurrentContext
/* 8034AC78 00347858  3C 60 80 4F */	lis r3, _db_stack_end@ha
/* 8034AC7C 0034785C  38 03 EC 00 */	addi r0, r3, _db_stack_end@l
/* 8034AC80 00347860  3C 60 80 4E */	lis r3, _stack_end@ha
/* 8034AC84 00347864  90 1C 07 14 */	stw r0, 0x714(r28)
/* 8034AC88 00347868  38 03 EC 00 */	addi r0, r3, _stack_end@l
/* 8034AC8C 0034786C  38 7C 07 18 */	addi r3, r28, 0x718
/* 8034AC90 00347870  90 1C 07 18 */	stw r0, 0x718(r28)
/* 8034AC94 00347874  3C 80 DE AE */	lis r4, 0xDEADBABE@ha
/* 8034AC98 00347878  3B 40 00 00 */	li r26, 0
/* 8034AC9C 0034787C  80 63 00 00 */	lwz r3, 0(r3)
/* 8034ACA0 00347880  38 84 BA BE */	addi r4, r4, 0xDEADBABE@l
/* 8034ACA4 00347884  57 40 18 38 */	slwi r0, r26, 3
/* 8034ACA8 00347888  90 83 00 00 */	stw r4, 0(r3)
/* 8034ACAC 0034788C  7F 7C 02 14 */	add r27, r28, r0
/* 8034ACB0 00347890  93 AD BD 38 */	stw r29, lbl_804D73D8(r13)
/* 8034ACB4 00347894  93 FE 00 E4 */	stw r31, 0xe4(r30)
/* 8034ACB8 00347898  93 AD BD 3C */	stw r29, lbl_804D73DC(r13)
lbl_8034ACBC:
/* 8034ACBC 0034789C  7F 63 DB 78 */	mr r3, r27
/* 8034ACC0 003478A0  48 00 00 6D */	bl OSInitThreadQueue
/* 8034ACC4 003478A4  3B 5A 00 01 */	addi r26, r26, 1
/* 8034ACC8 003478A8  2C 1A 00 1F */	cmpwi r26, 0x1f
/* 8034ACCC 003478AC  3B 7B 00 08 */	addi r27, r27, 8
/* 8034ACD0 003478B0  40 81 FF EC */	ble lbl_8034ACBC
/* 8034ACD4 003478B4  3F C0 80 00 */	lis r30, 0x800000DC@ha
/* 8034ACD8 003478B8  38 7E 00 DC */	addi r3, r30, 0x800000DC@l
/* 8034ACDC 003478BC  48 00 00 51 */	bl OSInitThreadQueue
/* 8034ACE0 003478C0  38 9E 00 DC */	addi r4, r30, 0xdc
/* 8034ACE4 003478C4  84 64 00 04 */	lwzu r3, 4(r4)
/* 8034ACE8 003478C8  28 03 00 00 */	cmplwi r3, 0
/* 8034ACEC 003478CC  40 82 00 0C */	bne lbl_8034ACF8
/* 8034ACF0 003478D0  93 FE 00 DC */	stw r31, 0xdc(r30)
/* 8034ACF4 003478D4  48 00 00 08 */	b lbl_8034ACFC
lbl_8034ACF8:
/* 8034ACF8 003478D8  93 E3 02 FC */	stw r31, 0x2fc(r3)
lbl_8034ACFC:
/* 8034ACFC 003478DC  90 7F 03 00 */	stw r3, 0x300(r31)
/* 8034AD00 003478E0  3B C0 00 00 */	li r30, 0
/* 8034AD04 003478E4  38 7C 07 20 */	addi r3, r28, 0x720
/* 8034AD08 003478E8  93 DF 02 FC */	stw r30, 0x2fc(r31)
/* 8034AD0C 003478EC  93 E4 00 00 */	stw r31, 0(r4)
/* 8034AD10 003478F0  4B FF A5 45 */	bl OSClearContext
/* 8034AD14 003478F4  93 CD BD 40 */	stw r30, lbl_804D73E0(r13)
/* 8034AD18 003478F8  BB 41 00 08 */	lmw r26, 8(r1)
/* 8034AD1C 003478FC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034AD20 00347900  38 21 00 20 */	addi r1, r1, 0x20
/* 8034AD24 00347904  7C 08 03 A6 */	mtlr r0
/* 8034AD28 00347908  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void OSInitThreadQueue(OSThreadQueue*)
{ // clang-format off
    nofralloc
/* 8034AD2C 0034790C  38 00 00 00 */	li r0, 0
/* 8034AD30 00347910  90 03 00 04 */	stw r0, 4(r3)
/* 8034AD34 00347914  90 03 00 00 */	stw r0, 0(r3)
/* 8034AD38 00347918  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
