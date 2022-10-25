.include "macros.inc"

.section .text  # 0x80343720 - 0x80343E40

.global DecrementerExceptionHandler
DecrementerExceptionHandler:
/* 80343DF8 003409D8  90 04 00 00 */	stw r0, 0(r4)
/* 80343DFC 003409DC  90 24 00 04 */	stw r1, 4(r4)
/* 80343E00 003409E0  90 44 00 08 */	stw r2, 8(r4)
/* 80343E04 003409E4  BC C4 00 18 */	stmw r6, 0x18(r4)
/* 80343E08 003409E8  7C 11 E2 A6 */	mfspr r0, 0x391
/* 80343E0C 003409EC  90 04 01 A8 */	stw r0, 0x1a8(r4)
/* 80343E10 003409F0  7C 12 E2 A6 */	mfspr r0, 0x392
/* 80343E14 003409F4  90 04 01 AC */	stw r0, 0x1ac(r4)
/* 80343E18 003409F8  7C 13 E2 A6 */	mfspr r0, 0x393
/* 80343E1C 003409FC  90 04 01 B0 */	stw r0, 0x1b0(r4)
/* 80343E20 00340A00  7C 14 E2 A6 */	mfspr r0, 0x394
/* 80343E24 00340A04  90 04 01 B4 */	stw r0, 0x1b4(r4)
/* 80343E28 00340A08  7C 15 E2 A6 */	mfspr r0, 0x395
/* 80343E2C 00340A0C  90 04 01 B8 */	stw r0, 0x1b8(r4)
/* 80343E30 00340A10  7C 16 E2 A6 */	mfspr r0, 0x396
/* 80343E34 00340A14  90 04 01 BC */	stw r0, 0x1bc(r4)
/* 80343E38 00340A18  7C 17 E2 A6 */	mfspr r0, 0x397
/* 80343E3C 00340A1C  90 04 01 C0 */	stw r0, 0x1c0(r4)
/* 80343E40 00340A20  4B FF FD 88 */	b DecrementerExceptionCallback


.section .sbss

.global AlarmQueue
AlarmQueue:
	.skip 0x8
