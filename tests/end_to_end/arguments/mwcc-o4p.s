.include "macros.inc"

.section .text  # 0x0 - 0x1c

.global test
test:
/* 00000000 00000000  EC 01 10 2A */	fadds f0, f1, f2
/* 00000004 00000004  7C 04 2A 14 */	add r0, r4, r5
/* 00000008 00000008  7C 03 02 14 */	add r0, r3, r0
/* 0000000C 0000000C  90 00 00 00 */	stw r0, globali@sda21(r2)
/* 00000010 00000010  EC 03 00 2A */	fadds f0, f3, f0
/* 00000014 00000014  D0 00 00 00 */	stfs f0, globalf@sda21(r2)
/* 00000018 00000018  4E 80 00 20 */	blr 

.section .sbss  # 0x0 - 0x8

.global globalf
globalf:
	.word 0x00000000

.global globali
globali:
	.word 0x00000000

