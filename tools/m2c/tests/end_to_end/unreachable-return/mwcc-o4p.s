.include "macros.inc"

.section .text  # 0x0 - 0x4

.global test
test:
/* 00000000 00000000  48 00 00 00 */	b test

.section .sbss  # 0x0 - 0x4

.global x
x:
	.word 0x00000000

