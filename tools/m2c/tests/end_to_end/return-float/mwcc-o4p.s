.include "macros.inc"

.section .text  # 0x0 - 0x14

.global test
test:
/* 00000000 00000000  C0 00 00 00 */	lfs f0, $$25@sda21(r13)
/* 00000004 00000004  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 00000008 00000008  4D 82 00 20 */	beqlr 
/* 0000000C 0000000C  C0 20 00 00 */	lfs f1, $$26@sda21(r13)
/* 00000010 00000010  4E 80 00 20 */	blr 

.section .sdata2  # 0x0 - 0x8

.global $$25
$$25:
	.word 0x00000000

.global $$26
$$26:
	.word 0x41700000

