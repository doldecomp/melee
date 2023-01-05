.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global TRKMessageSend
TRKMessageSend:
/* 80326C6C 0032384C  7C 08 02 A6 */	mflr r0
/* 80326C70 00323850  90 01 00 04 */	stw r0, 4(r1)
/* 80326C74 00323854  94 21 FF F8 */	stwu r1, -8(r1)
/* 80326C78 00323858  80 83 00 08 */	lwz r4, 8(r3)
/* 80326C7C 0032385C  38 63 00 10 */	addi r3, r3, 0x10
/* 80326C80 00323860  48 00 42 39 */	bl TRK_WriteUARTN
/* 80326C84 00323864  38 21 00 08 */	addi r1, r1, 8
/* 80326C88 00323868  80 01 00 04 */	lwz r0, 4(r1)
/* 80326C8C 0032386C  7C 08 03 A6 */	mtlr r0
/* 80326C90 00323870  4E 80 00 20 */	blr
