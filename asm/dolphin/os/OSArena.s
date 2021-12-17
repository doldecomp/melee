.include "macros.inc"

.section .text  # 0x803444C8 - 0x80344530

.global OSGetArenaHi
OSGetArenaHi:
/* 803444C8 003410A8  80 6D BC D0 */	lwz r3, __OSArenaHi@sda21(r13)
/* 803444CC 003410AC  4E 80 00 20 */	blr 

.global OSGetArenaLo
OSGetArenaLo:
/* 803444D0 003410B0  80 6D A5 70 */	lwz r3, __OSArenaLo@sda21(r13)
/* 803444D4 003410B4  4E 80 00 20 */	blr 

.global OSSetArenaHi
OSSetArenaHi:
/* 803444D8 003410B8  90 6D BC D0 */	stw r3, __OSArenaHi@sda21(r13)
/* 803444DC 003410BC  4E 80 00 20 */	blr 

.global OSSetArenaLo
OSSetArenaLo:
/* 803444E0 003410C0  90 6D A5 70 */	stw r3, __OSArenaLo@sda21(r13)
/* 803444E4 003410C4  4E 80 00 20 */	blr 

.global func_803444E8
func_803444E8:
/* 803444E8 003410C8  80 0D A5 70 */	lwz r0, __OSArenaLo@sda21(r13)
/* 803444EC 003410CC  38 84 FF FF */	addi r4, r4, -1
/* 803444F0 003410D0  7C 85 20 F8 */	nor r5, r4, r4
/* 803444F4 003410D4  7C 00 22 14 */	add r0, r0, r4
/* 803444F8 003410D8  7C A6 00 38 */	and r6, r5, r0
/* 803444FC 003410DC  7C 06 1A 14 */	add r0, r6, r3
/* 80344500 003410E0  7C 00 22 14 */	add r0, r0, r4
/* 80344504 003410E4  7C A0 00 38 */	and r0, r5, r0
/* 80344508 003410E8  90 0D A5 70 */	stw r0, __OSArenaLo@sda21(r13)
/* 8034450C 003410EC  7C C3 33 78 */	mr r3, r6
/* 80344510 003410F0  4E 80 00 20 */	blr 

.global func_80344514
func_80344514:
/* 80344514 003410F4  38 04 FF FF */	addi r0, r4, -1
/* 80344518 003410F8  80 8D BC D0 */	lwz r4, __OSArenaHi@sda21(r13)
/* 8034451C 003410FC  7C 00 00 F8 */	nor r0, r0, r0
/* 80344520 00341100  7C 84 00 38 */	and r4, r4, r0
/* 80344524 00341104  7C 83 20 50 */	subf r4, r3, r4
/* 80344528 00341108  7C 83 00 38 */	and r3, r4, r0
/* 8034452C 0034110C  90 6D BC D0 */	stw r3, __OSArenaHi@sda21(r13)
/* 80344530 00341110  4E 80 00 20 */	blr 


.section .sdata

.global __OSArenaLo
__OSArenaLo:
    .4byte 0xFFFFFFFF
    .4byte 0x00000000


.section .sbss

.global __OSArenaHi
__OSArenaHi:
	.skip 0x8
