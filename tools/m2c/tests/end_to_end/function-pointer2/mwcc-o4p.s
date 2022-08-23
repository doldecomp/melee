.include "macros.inc"

.section .text  # 0x0 - 0x34

.global test
test:
/* 00000000 00000000  3C 60 00 00 */	lis r3, foo@ha
/* 00000004 00000004  38 83 00 00 */	addi r4, r3, foo@l
/* 00000008 00000008  3C 60 00 00 */	lis r3, bar@ha
/* 0000000C 0000000C  90 80 00 00 */	stw r4, glob@sda21(r2)
/* 00000010 00000010  38 03 00 00 */	addi r0, r3, bar@l
/* 00000014 00000014  90 00 00 00 */	stw r0, glob@sda21(r2)
/* 00000018 00000018  90 80 00 00 */	stw r4, glob2@sda21(r2)
/* 0000001C 0000001C  90 00 00 00 */	stw r0, glob2@sda21(r2)
/* 00000020 00000020  4E 80 00 20 */	blr 

.global foo
foo:
/* 00000024 00000024  38 60 00 01 */	li r3, 1
/* 00000028 00000028  4E 80 00 20 */	blr 

.global bar
bar:
/* 0000002C 0000002C  38 60 00 02 */	li r3, 2
/* 00000030 00000030  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x8

.global glob2
glob2:
	.word 0x00000000

.global glob
glob:
	.word 0x00000000

