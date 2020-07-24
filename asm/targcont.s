.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global TRKTargetContinue
TRKTargetContinue:
/* 8032AF80 00327B60  7C 08 02 A6 */	mflr r0
/* 8032AF84 00327B64  38 60 00 00 */	li r3, 0
/* 8032AF88 00327B68  90 01 00 04 */	stw r0, 4(r1)
/* 8032AF8C 00327B6C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8032AF90 00327B70  4B FF F3 41 */	bl TRKTargetSetStopped
/* 8032AF94 00327B74  4B FF FF 99 */	bl UnreserveEXI2Port
/* 8032AF98 00327B78  4B FF ED 35 */	bl TRKInterruptHandlerEnableInterrupts
/* 8032AF9C 00327B7C  4B FF FF 61 */	bl ReserveEXI2Port
/* 8032AFA0 00327B80  38 60 00 00 */	li r3, 0
/* 8032AFA4 00327B84  38 21 00 08 */	addi r1, r1, 8
/* 8032AFA8 00327B88  80 01 00 04 */	lwz r0, 4(r1)
/* 8032AFAC 00327B8C  7C 08 03 A6 */	mtlr r0
/* 8032AFB0 00327B90  4E 80 00 20 */	blr
