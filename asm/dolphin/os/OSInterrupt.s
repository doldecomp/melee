.include "macros.inc"

.section .text  # 0x80347364 - 0x80347BC8

.global lbl_80347B80
lbl_80347B80:
/* 80347B80 00344760  90 04 00 00 */	stw r0, 0(r4)
/* 80347B84 00344764  90 24 00 04 */	stw r1, 4(r4)
/* 80347B88 00344768  90 44 00 08 */	stw r2, 8(r4)
/* 80347B8C 0034476C  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 80347B90 00344770  7C 11 E2 A6 */	mfspr r0, 0x391
/* 80347B94 00344774  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 80347B98 00344778  7C 12 E2 A6 */	mfspr r0, 0x392
/* 80347B9C 0034477C  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 80347BA0 00344780  7C 13 E2 A6 */	mfspr r0, 0x393
/* 80347BA4 00344784  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 80347BA8 00344788  7C 14 E2 A6 */	mfspr r0, 0x394
/* 80347BAC 0034478C  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 80347BB0 00344790  7C 15 E2 A6 */	mfspr r0, 0x395
/* 80347BB4 00344794  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 80347BB8 00344798  7C 16 E2 A6 */	mfspr r0, 0x396
/* 80347BBC 0034479C  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 80347BC0 003447A0  7C 17 E2 A6 */	mfspr r0, 0x397
/* 80347BC4 003447A4  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 80347BC8 003447A8  4B FF FC 74 */	b lbl_8034783C


.section .data
    .balign 8
.global lbl_80402318
lbl_80402318:
    .4byte 0x00000100
    .4byte 0x00000040
    .4byte 0xF8000000
    .4byte 0x00000200
    .4byte 0x00000080
    .4byte 0x00003000
    .4byte 0x00000020
    .4byte 0x03FF8C00
    .4byte 0x04000000
    .4byte 0x00004000
    .4byte 0xFFFFFFFF
    .4byte NULL


.section .sbss
    .4byte NULL
.global lbl_804D7378
lbl_804D7378:
	.skip 0x4
.global __OSLastInterruptSrr0
__OSLastInterruptSrr0:
	.skip 0x4
.global __OSLastInterrupt
__OSLastInterrupt:
	.skip 0x8
.global __OSLastInterruptTime
__OSLastInterruptTime:
	.skip 0x4
.global lbl_804D738C
lbl_804D738C:
	.skip 0x4
