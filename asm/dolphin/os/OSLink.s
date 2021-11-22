.include "macros.inc"

.section .text  # 0x80347BCC - 0x80347BE0

.global __OSModuleInit
__OSModuleInit:
/* 80347BCC 003447AC  3C 80 80 00 */	lis r4, 0x800030CC@ha
/* 80347BD0 003447B0  38 00 00 00 */	li r0, 0
/* 80347BD4 003447B4  90 04 30 CC */	stw r0, 0x800030CC@l(r4)
/* 80347BD8 003447B8  90 04 30 C8 */	stw r0, 0x30c8(r4)
/* 80347BDC 003447BC  90 04 30 D0 */	stw r0, 0x30d0(r4)
/* 80347BE0 003447C0  4E 80 00 20 */	blr 
