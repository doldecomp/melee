.include "macros.inc"

.section .text  # 0x0 - 0x100

.global compute__FR7Derivedi
compute__FR7Derivedi:
/* 00000000 00000000  7C 08 02 A6 */	mflr r0
/* 00000004 00000004  90 01 00 04 */	stw r0, 4(r1)
/* 00000008 00000008  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 0000000C 0000000C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 00000010 00000010  7C 7F 1B 78 */	mr r31, r3
/* 00000014 00000014  90 83 00 00 */	stw r4, 0(r3)
/* 00000018 00000018  81 9F 00 04 */	lwz r12, 4(r31)
/* 0000001C 0000001C  81 8C 00 08 */	lwz r12, 8(r12)
/* 00000020 00000020  7D 88 03 A6 */	mtlr r12
/* 00000024 00000024  4E 80 00 21 */	blrl 
/* 00000028 00000028  48 00 00 01 */	bl static_method__4BaseFi
/* 0000002C 0000002C  38 83 00 00 */	addi r4, r3, 0
/* 00000030 00000030  38 7F 00 00 */	addi r3, r31, 0
/* 00000034 00000034  48 00 00 01 */	bl method__4BaseFi
/* 00000038 00000038  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 0000003C 0000003C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 00000040 00000040  38 21 00 18 */	addi r1, r1, 0x18
/* 00000044 00000044  7C 08 03 A6 */	mtlr r0
/* 00000048 00000048  4E 80 00 20 */	blr 

.global method__4BaseFi
method__4BaseFi:
/* 0000004C 0000004C  1C 64 00 03 */	mulli r3, r4, 3
/* 00000050 00000050  4E 80 00 20 */	blr 

.global static_method__4BaseFi
static_method__4BaseFi:
/* 00000054 00000054  54 63 08 3C */	slwi r3, r3, 1
/* 00000058 00000058  4E 80 00 20 */	blr 

.global virtual_method__7DerivedFi
virtual_method__7DerivedFi:
/* 0000005C 0000005C  54 83 10 3A */	slwi r3, r4, 2
/* 00000060 00000060  4E 80 00 20 */	blr 

.global test
test:
/* 00000064 00000064  7C 08 02 A6 */	mflr r0
/* 00000068 00000068  90 01 00 04 */	stw r0, 4(r1)
/* 0000006C 0000006C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 00000070 00000070  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 00000074 00000074  3B E3 00 00 */	addi r31, r3, 0
/* 00000078 00000078  38 9F 00 00 */	addi r4, r31, 0
/* 0000007C 0000007C  38 61 00 0C */	addi r3, r1, 0xc
/* 00000080 00000080  48 00 00 01 */	bl __ct__7DerivedFi
/* 00000084 00000084  38 61 00 0C */	addi r3, r1, 0xc
/* 00000088 00000088  38 9F 00 00 */	addi r4, r31, 0
/* 0000008C 0000008C  48 00 00 01 */	bl compute__FR7Derivedi
/* 00000090 00000090  80 01 00 24 */	lwz r0, 0x24(r1)
/* 00000094 00000094  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 00000098 00000098  38 21 00 20 */	addi r1, r1, 0x20
/* 0000009C 0000009C  7C 08 03 A6 */	mtlr r0
/* 000000A0 000000A0  4E 80 00 20 */	blr 

.global __ct__7DerivedFi
__ct__7DerivedFi:
/* 000000A4 000000A4  7C 08 02 A6 */	mflr r0
/* 000000A8 000000A8  90 01 00 04 */	stw r0, 4(r1)
/* 000000AC 000000AC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 000000B0 000000B0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 000000B4 000000B4  3B E4 00 00 */	addi r31, r4, 0
/* 000000B8 000000B8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 000000BC 000000BC  3B C3 00 00 */	addi r30, r3, 0
/* 000000C0 000000C0  48 00 00 01 */	bl __ct__4BaseFv
/* 000000C4 000000C4  3C 60 00 00 */	lis r3, __vt__7Derived@ha
/* 000000C8 000000C8  38 03 00 00 */	addi r0, r3, __vt__7Derived@l
/* 000000CC 000000CC  90 1E 00 04 */	stw r0, 4(r30)
/* 000000D0 000000D0  7F C3 F3 78 */	mr r3, r30
/* 000000D4 000000D4  93 FE 00 00 */	stw r31, 0(r30)
/* 000000D8 000000D8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 000000DC 000000DC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 000000E0 000000E0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 000000E4 000000E4  38 21 00 18 */	addi r1, r1, 0x18
/* 000000E8 000000E8  7C 08 03 A6 */	mtlr r0
/* 000000EC 000000EC  4E 80 00 20 */	blr 

.global __ct__4BaseFv
__ct__4BaseFv:
/* 000000F0 000000F0  3C 80 00 00 */	lis r4, __vt__4Base@ha
/* 000000F4 000000F4  38 04 00 00 */	addi r0, r4, __vt__4Base@l
/* 000000F8 000000F8  90 03 00 04 */	stw r0, 4(r3)
/* 000000FC 000000FC  4E 80 00 20 */	blr 

.section .data  # 0x0 - 0x18

.global $$211
$$211:
	.word __RTTI__4Base
	.word 0x00000000
	.word 0x00000000

.global __vt__7Derived
__vt__7Derived:
	.word __RTTI__7Derived
	.word 0x00000000
	.word virtual_method__7DerivedFi

.section .sdata  # 0x0 - 0x20

.global $$210
$$210:
	.word 0x44657269  # "Deri"
	.word 0x76656400  # "ved\0"

.global $$212
$$212:
	.word 0x42617365  # "Base"
	.word 0x00000000  # "\0\0\0\0"

.global __RTTI__4Base
__RTTI__4Base:
	.word $$212
	.word 0x00000000

.global __RTTI__7Derived
__RTTI__7Derived:
	.word $$210
	.word $$211

