.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240 

.global SIGetResponse
SIGetResponse:
/* 8034A32C 00346F0C  7C 08 02 A6 */	mflr r0
/* 8034A330 00346F10  3C A0 80 4A */	lis r5, Packet@ha
/* 8034A334 00346F14  90 01 00 04 */	stw r0, 4(r1)
/* 8034A338 00346F18  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8034A33C 00346F1C  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8034A340 00346F20  3B A3 00 00 */	addi r29, r3, 0
/* 8034A344 00346F24  3B C4 00 00 */	addi r30, r4, 0
/* 8034A348 00346F28  3B 85 7D B8 */	addi r28, r5, Packet@l
/* 8034A34C 00346F2C  4B FF D0 19 */	bl OSDisableInterrupts
/* 8034A350 00346F30  3B E3 00 00 */	addi r31, r3, 0
/* 8034A354 00346F34  38 7D 00 00 */	addi r3, r29, 0
/* 8034A358 00346F38  4B FF FC F9 */	bl SIGetStatus
/* 8034A35C 00346F3C  54 60 06 B5 */	rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 8034A360 00346F40  41 82 00 3C */	beq lbl_8034A39C
/* 8034A364 00346F44  1C 9D 00 0C */	mulli r4, r29, 0xc
/* 8034A368 00346F48  3C 60 CC 00 */	lis r3, 0xCC006400@ha
/* 8034A36C 00346F4C  38 03 64 00 */	addi r0, r3, 0xCC006400@l
/* 8034A370 00346F50  7C 80 22 14 */	add r4, r0, r4
/* 8034A374 00346F54  57 A3 18 38 */	slwi r3, r29, 3
/* 8034A378 00346F58  80 04 00 04 */	lwz r0, 4(r4)
/* 8034A37C 00346F5C  7C BC 1A 14 */	add r5, r28, r3
/* 8034A380 00346F60  90 05 01 C0 */	stw r0, 0x1c0(r5)
/* 8034A384 00346F64  57 A0 10 3A */	slwi r0, r29, 2
/* 8034A388 00346F68  7C 7C 02 14 */	add r3, r28, r0
/* 8034A38C 00346F6C  80 84 00 08 */	lwz r4, 8(r4)
/* 8034A390 00346F70  38 00 00 01 */	li r0, 1
/* 8034A394 00346F74  90 85 01 C4 */	stw r4, 0x1c4(r5)
/* 8034A398 00346F78  90 03 01 B0 */	stw r0, 0x1b0(r3)
lbl_8034A39C:
/* 8034A39C 00346F7C  57 A0 10 3A */	slwi r0, r29, 2
/* 8034A3A0 00346F80  7C 7C 02 14 */	add r3, r28, r0
/* 8034A3A4 00346F84  83 63 01 B0 */	lwz r27, 0x1b0(r3)
/* 8034A3A8 00346F88  38 00 00 00 */	li r0, 0
/* 8034A3AC 00346F8C  2C 1B 00 00 */	cmpwi r27, 0
/* 8034A3B0 00346F90  90 03 01 B0 */	stw r0, 0x1b0(r3)
/* 8034A3B4 00346F94  41 82 00 1C */	beq lbl_8034A3D0
/* 8034A3B8 00346F98  57 A0 18 38 */	slwi r0, r29, 3
/* 8034A3BC 00346F9C  7C 7C 02 14 */	add r3, r28, r0
/* 8034A3C0 00346FA0  80 03 01 C0 */	lwz r0, 0x1c0(r3)
/* 8034A3C4 00346FA4  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A3C8 00346FA8  80 03 01 C4 */	lwz r0, 0x1c4(r3)
/* 8034A3CC 00346FAC  90 1E 00 04 */	stw r0, 4(r30)
lbl_8034A3D0:
/* 8034A3D0 00346FB0  7F E3 FB 78 */	mr r3, r31
/* 8034A3D4 00346FB4  4B FF CF B9 */	bl OSRestoreInterrupts
/* 8034A3D8 00346FB8  7F 63 DB 78 */	mr r3, r27
/* 8034A3DC 00346FBC  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8034A3E0 00346FC0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8034A3E4 00346FC4  38 21 00 28 */	addi r1, r1, 0x28
/* 8034A3E8 00346FC8  7C 08 03 A6 */	mtlr r0
/* 8034A3EC 00346FCC  4E 80 00 20 */	blr 

.global AlarmHandler
AlarmHandler:
/* 8034A3F0 00346FD0  7C 08 02 A6 */	mflr r0
/* 8034A3F4 00346FD4  3C 80 80 4A */	lis r4, Alarm@ha
/* 8034A3F8 00346FD8  90 01 00 04 */	stw r0, 4(r1)
/* 8034A3FC 00346FDC  38 04 7E 38 */	addi r0, r4, Alarm@l
/* 8034A400 00346FE0  3C 80 66 66 */	lis r4, 0x66666667@ha
/* 8034A404 00346FE4  7C 00 18 50 */	subf r0, r0, r3
/* 8034A408 00346FE8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034A40C 00346FEC  38 64 66 67 */	addi r3, r4, 0x66666667@l
/* 8034A410 00346FF0  7C 03 00 96 */	mulhw r0, r3, r0
/* 8034A414 00346FF4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8034A418 00346FF8  7C 00 26 70 */	srawi r0, r0, 4
/* 8034A41C 00346FFC  54 03 0F FE */	srwi r3, r0, 0x1f
/* 8034A420 00347000  7C 00 1A 14 */	add r0, r0, r3
/* 8034A424 00347004  3C 60 80 4A */	lis r3, Packet@ha
/* 8034A428 00347008  54 04 28 34 */	slwi r4, r0, 5
/* 8034A42C 0034700C  38 03 7D B8 */	addi r0, r3, Packet@l
/* 8034A430 00347010  7F E0 22 14 */	add r31, r0, r4
/* 8034A434 00347014  80 7F 00 00 */	lwz r3, 0(r31)
/* 8034A438 00347018  2C 03 FF FF */	cmpwi r3, -1
/* 8034A43C 0034701C  41 82 00 2C */	beq lbl_8034A468
/* 8034A440 00347020  80 9F 00 04 */	lwz r4, 4(r31)
/* 8034A444 00347024  80 BF 00 08 */	lwz r5, 8(r31)
/* 8034A448 00347028  80 DF 00 0C */	lwz r6, 0xc(r31)
/* 8034A44C 0034702C  80 FF 00 10 */	lwz r7, 0x10(r31)
/* 8034A450 00347030  81 1F 00 14 */	lwz r8, 0x14(r31)
/* 8034A454 00347034  4B FF F9 F1 */	bl __SITransfer
/* 8034A458 00347038  2C 03 00 00 */	cmpwi r3, 0
/* 8034A45C 0034703C  41 82 00 0C */	beq lbl_8034A468
/* 8034A460 00347040  38 00 FF FF */	li r0, -1
/* 8034A464 00347044  90 1F 00 00 */	stw r0, 0(r31)
lbl_8034A468:
/* 8034A468 00347048  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034A46C 0034704C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8034A470 00347050  38 21 00 20 */	addi r1, r1, 0x20
/* 8034A474 00347054  7C 08 03 A6 */	mtlr r0
/* 8034A478 00347058  4E 80 00 20 */	blr 

.global SITransfer
SITransfer:
/* 8034A47C 0034705C  7C 08 02 A6 */	mflr r0
/* 8034A480 00347060  90 01 00 04 */	stw r0, 4(r1)
/* 8034A484 00347064  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8034A488 00347068  BE 61 00 2C */	stmw r19, 0x2c(r1)
/* 8034A48C 0034706C  3B 03 00 00 */	addi r24, r3, 0
/* 8034A490 00347070  3C 60 80 4A */	lis r3, Packet@ha
/* 8034A494 00347074  3A E3 7D B8 */	addi r23, r3, Packet@l
/* 8034A498 00347078  57 00 28 34 */	slwi r0, r24, 5
/* 8034A49C 0034707C  3B 24 00 00 */	addi r25, r4, 0
/* 8034A4A0 00347080  3B 45 00 00 */	addi r26, r5, 0
/* 8034A4A4 00347084  3B 66 00 00 */	addi r27, r6, 0
/* 8034A4A8 00347088  3B 87 00 00 */	addi r28, r7, 0
/* 8034A4AC 0034708C  3B A8 00 00 */	addi r29, r8, 0
/* 8034A4B0 00347090  3B E9 00 00 */	addi r31, r9, 0
/* 8034A4B4 00347094  3B CA 00 00 */	addi r30, r10, 0
/* 8034A4B8 00347098  7E D7 02 14 */	add r22, r23, r0
/* 8034A4BC 0034709C  4B FF CE A9 */	bl OSDisableInterrupts
/* 8034A4C0 003470A0  80 16 00 00 */	lwz r0, 0(r22)
/* 8034A4C4 003470A4  3A A3 00 00 */	addi r21, r3, 0
/* 8034A4C8 003470A8  2C 00 FF FF */	cmpwi r0, -1
/* 8034A4CC 003470AC  40 82 00 14 */	bne lbl_8034A4E0
/* 8034A4D0 003470B0  3C 60 80 40 */	lis r3, lbl_80402358@ha
/* 8034A4D4 003470B4  80 03 23 58 */	lwz r0, lbl_80402358@l(r3)
/* 8034A4D8 003470B8  7C 00 C0 00 */	cmpw r0, r24
/* 8034A4DC 003470BC  40 82 00 14 */	bne lbl_8034A4F0
lbl_8034A4E0:
/* 8034A4E0 003470C0  7E A3 AB 78 */	mr r3, r21
/* 8034A4E4 003470C4  4B FF CE A9 */	bl OSRestoreInterrupts
/* 8034A4E8 003470C8  38 60 00 00 */	li r3, 0
/* 8034A4EC 003470CC  48 00 00 E8 */	b lbl_8034A5D4
lbl_8034A4F0:
/* 8034A4F0 003470D0  48 00 1F 21 */	bl __OSGetSystemTime
/* 8034A4F4 003470D4  38 00 00 00 */	li r0, 0
/* 8034A4F8 003470D8  7F C5 02 78 */	xor r5, r30, r0
/* 8034A4FC 003470DC  7F E0 02 78 */	xor r0, r31, r0
/* 8034A500 003470E0  7C A0 03 79 */	or. r0, r5, r0
/* 8034A504 003470E4  40 82 00 10 */	bne lbl_8034A514
/* 8034A508 003470E8  3A 64 00 00 */	addi r19, r4, 0
/* 8034A50C 003470EC  3A 83 00 00 */	addi r20, r3, 0
/* 8034A510 003470F0  48 00 00 1C */	b lbl_8034A52C
lbl_8034A514:
/* 8034A514 003470F4  57 00 18 38 */	slwi r0, r24, 3
/* 8034A518 003470F8  7C D7 02 14 */	add r6, r23, r0
/* 8034A51C 003470FC  80 A6 01 44 */	lwz r5, 0x144(r6)
/* 8034A520 00347100  80 06 01 40 */	lwz r0, 0x140(r6)
/* 8034A524 00347104  7E 7E 28 14 */	addc r19, r30, r5
/* 8034A528 00347108  7E 9F 01 14 */	adde r20, r31, r0
lbl_8034A52C:
/* 8034A52C 0034710C  6C 66 80 00 */	xoris r6, r3, 0x8000
/* 8034A530 00347110  6E 85 80 00 */	xoris r5, r20, 0x8000
/* 8034A534 00347114  7C 13 20 10 */	subfc r0, r19, r4
/* 8034A538 00347118  7C A5 31 10 */	subfe r5, r5, r6
/* 8034A53C 0034711C  7C A6 31 10 */	subfe r5, r6, r6
/* 8034A540 00347120  7C A5 00 D1 */	neg. r5, r5
/* 8034A544 00347124  41 82 00 30 */	beq lbl_8034A574
/* 8034A548 00347128  1C 18 00 28 */	mulli r0, r24, 0x28
/* 8034A54C 0034712C  7F C4 98 10 */	subfc r30, r4, r19
/* 8034A550 00347130  7F E3 A1 10 */	subfe r31, r3, r20
/* 8034A554 00347134  3C 80 80 35 */	lis r4, AlarmHandler@ha
/* 8034A558 00347138  7C 77 02 14 */	add r3, r23, r0
/* 8034A55C 0034713C  38 E4 A3 F0 */	addi r7, r4, AlarmHandler@l
/* 8034A560 00347140  38 DE 00 00 */	addi r6, r30, 0
/* 8034A564 00347144  38 BF 00 00 */	addi r5, r31, 0
/* 8034A568 00347148  38 63 00 80 */	addi r3, r3, 0x80
/* 8034A56C 0034714C  4B FF 94 5D */	bl OSSetAlarm
/* 8034A570 00347150  48 00 00 38 */	b lbl_8034A5A8
lbl_8034A574:
/* 8034A574 00347154  38 78 00 00 */	addi r3, r24, 0
/* 8034A578 00347158  38 99 00 00 */	addi r4, r25, 0
/* 8034A57C 0034715C  38 BA 00 00 */	addi r5, r26, 0
/* 8034A580 00347160  38 DB 00 00 */	addi r6, r27, 0
/* 8034A584 00347164  38 FC 00 00 */	addi r7, r28, 0
/* 8034A588 00347168  39 1D 00 00 */	addi r8, r29, 0
/* 8034A58C 0034716C  4B FF F8 B9 */	bl __SITransfer
/* 8034A590 00347170  2C 03 00 00 */	cmpwi r3, 0
/* 8034A594 00347174  41 82 00 14 */	beq lbl_8034A5A8
/* 8034A598 00347178  7E A3 AB 78 */	mr r3, r21
/* 8034A59C 0034717C  4B FF CD F1 */	bl OSRestoreInterrupts
/* 8034A5A0 00347180  38 60 00 01 */	li r3, 1
/* 8034A5A4 00347184  48 00 00 30 */	b lbl_8034A5D4
lbl_8034A5A8:
/* 8034A5A8 00347188  93 16 00 00 */	stw r24, 0(r22)
/* 8034A5AC 0034718C  7E A3 AB 78 */	mr r3, r21
/* 8034A5B0 00347190  93 36 00 04 */	stw r25, 4(r22)
/* 8034A5B4 00347194  93 56 00 08 */	stw r26, 8(r22)
/* 8034A5B8 00347198  93 76 00 0C */	stw r27, 0xc(r22)
/* 8034A5BC 0034719C  93 96 00 10 */	stw r28, 0x10(r22)
/* 8034A5C0 003471A0  93 B6 00 14 */	stw r29, 0x14(r22)
/* 8034A5C4 003471A4  92 76 00 1C */	stw r19, 0x1c(r22)
/* 8034A5C8 003471A8  92 96 00 18 */	stw r20, 0x18(r22)
/* 8034A5CC 003471AC  4B FF CD C1 */	bl OSRestoreInterrupts
/* 8034A5D0 003471B0  38 60 00 01 */	li r3, 1
lbl_8034A5D4:
/* 8034A5D4 003471B4  BA 61 00 2C */	lmw r19, 0x2c(r1)
/* 8034A5D8 003471B8  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8034A5DC 003471BC  38 21 00 60 */	addi r1, r1, 0x60
/* 8034A5E0 003471C0  7C 08 03 A6 */	mtlr r0
/* 8034A5E4 003471C4  4E 80 00 20 */	blr 

.global GetTypeCallback
GetTypeCallback:
/* 8034A5E8 003471C8  7C 08 02 A6 */	mflr r0
/* 8034A5EC 003471CC  90 01 00 04 */	stw r0, 4(r1)
/* 8034A5F0 003471D0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8034A5F4 003471D4  BF 41 00 18 */	stmw r26, 0x18(r1)
/* 8034A5F8 003471D8  3B 63 00 00 */	addi r27, r3, 0
/* 8034A5FC 003471DC  3C 60 80 40 */	lis r3, lbl_8040236C@ha
/* 8034A600 003471E0  38 03 23 6C */	addi r0, r3, lbl_8040236C@l
/* 8034A604 003471E4  57 7D 10 3A */	slwi r29, r27, 2
/* 8034A608 003471E8  7F C0 EA 14 */	add r30, r0, r29
/* 8034A60C 003471EC  3C 60 80 4A */	lis r3, Packet@ha
/* 8034A610 003471F0  3B 44 00 00 */	addi r26, r4, 0
/* 8034A614 003471F4  3B E3 7D B8 */	addi r31, r3, Packet@l
/* 8034A618 003471F8  80 1E 00 00 */	lwz r0, 0(r30)
/* 8034A61C 003471FC  54 00 06 6E */	rlwinm r0, r0, 0, 0x19, 0x17
/* 8034A620 00347200  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A624 00347204  80 1E 00 00 */	lwz r0, 0(r30)
/* 8034A628 00347208  7C 00 D3 78 */	or r0, r0, r26
/* 8034A62C 0034720C  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A630 00347210  48 00 1D E1 */	bl __OSGetSystemTime
/* 8034A634 00347214  57 60 18 38 */	slwi r0, r27, 3
/* 8034A638 00347218  7C BF 02 14 */	add r5, r31, r0
/* 8034A63C 0034721C  90 85 01 24 */	stw r4, 0x124(r5)
/* 8034A640 00347220  3C 80 80 00 */	lis r4, 0x8000
/* 8034A644 00347224  57 40 07 3F */	clrlwi. r0, r26, 0x1c
/* 8034A648 00347228  90 65 01 20 */	stw r3, 0x120(r5)
/* 8034A64C 0034722C  7C 84 DC 30 */	srw r4, r4, r27
/* 8034A650 00347230  80 6D BD 30 */	lwz r3, lbl_804D73D0@sda21(r13)
/* 8034A654 00347234  83 9E 00 00 */	lwz r28, 0(r30)
/* 8034A658 00347238  7C 60 20 78 */	andc r0, r3, r4
/* 8034A65C 0034723C  90 0D BD 30 */	stw r0, lbl_804D73D0@sda21(r13)
/* 8034A660 00347240  7C 7A 20 38 */	and r26, r3, r4
/* 8034A664 00347244  40 82 00 24 */	bne lbl_8034A688
/* 8034A668 00347248  57 83 00 C8 */	rlwinm r3, r28, 0, 3, 4
/* 8034A66C 0034724C  3C 03 F8 00 */	addis r0, r3, 0xf800
/* 8034A670 00347250  28 00 00 00 */	cmplwi r0, 0
/* 8034A674 00347254  40 82 00 14 */	bne lbl_8034A688
/* 8034A678 00347258  57 80 00 01 */	rlwinm. r0, r28, 0, 0, 0
/* 8034A67C 0034725C  41 82 00 0C */	beq lbl_8034A688
/* 8034A680 00347260  57 80 01 4B */	rlwinm. r0, r28, 0, 5, 5
/* 8034A684 00347264  41 82 00 5C */	beq lbl_8034A6E0
lbl_8034A688:
/* 8034A688 00347268  38 7B 00 00 */	addi r3, r27, 0
/* 8034A68C 0034726C  38 80 00 00 */	li r4, 0
/* 8034A690 00347270  4B FF ED 81 */	bl OSSetWirelessID
/* 8034A694 00347274  57 60 20 36 */	slwi r0, r27, 4
/* 8034A698 00347278  83 DE 00 00 */	lwz r30, 0(r30)
/* 8034A69C 0034727C  7F FF 02 14 */	add r31, r31, r0
/* 8034A6A0 00347280  3B A0 00 00 */	li r29, 0
/* 8034A6A4 00347284  3B 9D 00 00 */	addi r28, r29, 0
/* 8034A6A8 00347288  3B FF 01 60 */	addi r31, r31, 0x160
lbl_8034A6AC:
/* 8034A6AC 0034728C  81 9F 00 00 */	lwz r12, 0(r31)
/* 8034A6B0 00347290  28 0C 00 00 */	cmplwi r12, 0
/* 8034A6B4 00347294  41 82 00 18 */	beq lbl_8034A6CC
/* 8034A6B8 00347298  93 9F 00 00 */	stw r28, 0(r31)
/* 8034A6BC 0034729C  7D 88 03 A6 */	mtlr r12
/* 8034A6C0 003472A0  38 7B 00 00 */	addi r3, r27, 0
/* 8034A6C4 003472A4  38 9E 00 00 */	addi r4, r30, 0
/* 8034A6C8 003472A8  4E 80 00 21 */	blrl 
lbl_8034A6CC:
/* 8034A6CC 003472AC  3B BD 00 01 */	addi r29, r29, 1
/* 8034A6D0 003472B0  2C 1D 00 04 */	cmpwi r29, 4
/* 8034A6D4 003472B4  3B FF 00 04 */	addi r31, r31, 4
/* 8034A6D8 003472B8  41 80 FF D4 */	blt lbl_8034A6AC
/* 8034A6DC 003472BC  48 00 01 90 */	b lbl_8034A86C
lbl_8034A6E0:
/* 8034A6E0 003472C0  7F 63 DB 78 */	mr r3, r27
/* 8034A6E4 003472C4  4B FF EC A9 */	bl OSGetWirelessID
/* 8034A6E8 003472C8  2C 1A 00 00 */	cmpwi r26, 0
/* 8034A6EC 003472CC  54 7A 42 2E */	rlwinm r26, r3, 8, 8, 0x17
/* 8034A6F0 003472D0  41 82 00 54 */	beq lbl_8034A744
/* 8034A6F4 003472D4  57 40 02 D7 */	rlwinm. r0, r26, 0, 0xb, 0xb
/* 8034A6F8 003472D8  41 82 00 4C */	beq lbl_8034A744
/* 8034A6FC 003472DC  3C 60 00 D0 */	lis r3, 0x00CFFF00@ha
/* 8034A700 003472E0  38 03 FF 00 */	addi r0, r3, 0x00CFFF00@l
/* 8034A704 003472E4  7F 40 00 38 */	and r0, r26, r0
/* 8034A708 003472E8  64 00 4E 10 */	oris r0, r0, 0x4e10
/* 8034A70C 003472EC  7C 9F EA 14 */	add r4, r31, r29
/* 8034A710 003472F0  94 04 01 F0 */	stwu r0, 0x1f0(r4)
/* 8034A714 003472F4  38 00 00 80 */	li r0, 0x80
/* 8034A718 003472F8  3C 60 80 35 */	lis r3, GetTypeCallback@ha
/* 8034A71C 003472FC  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A720 00347300  39 03 A5 E8 */	addi r8, r3, GetTypeCallback@l
/* 8034A724 00347304  38 7B 00 00 */	addi r3, r27, 0
/* 8034A728 00347308  38 DE 00 00 */	addi r6, r30, 0
/* 8034A72C 0034730C  38 A0 00 03 */	li r5, 3
/* 8034A730 00347310  38 E0 00 03 */	li r7, 3
/* 8034A734 00347314  39 40 00 00 */	li r10, 0
/* 8034A738 00347318  39 20 00 00 */	li r9, 0
/* 8034A73C 0034731C  4B FF FD 41 */	bl SITransfer
/* 8034A740 00347320  48 00 01 2C */	b lbl_8034A86C
lbl_8034A744:
/* 8034A744 00347324  57 80 02 D7 */	rlwinm. r0, r28, 0, 0xb, 0xb
/* 8034A748 00347328  41 82 00 70 */	beq lbl_8034A7B8
/* 8034A74C 0034732C  3C 60 00 D0 */	lis r3, 0x00CFFF00@ha
/* 8034A750 00347330  38 63 FF 00 */	addi r3, r3, 0x00CFFF00@l
/* 8034A754 00347334  7F 40 18 38 */	and r0, r26, r3
/* 8034A758 00347338  7F 83 18 38 */	and r3, r28, r3
/* 8034A75C 0034733C  7C 00 18 40 */	cmplw r0, r3
/* 8034A760 00347340  41 82 00 C4 */	beq lbl_8034A824
/* 8034A764 00347344  57 40 02 D7 */	rlwinm. r0, r26, 0, 0xb, 0xb
/* 8034A768 00347348  40 82 00 14 */	bne lbl_8034A77C
/* 8034A76C 0034734C  64 7A 00 10 */	oris r26, r3, 0x10
/* 8034A770 00347350  38 7B 00 00 */	addi r3, r27, 0
/* 8034A774 00347354  57 44 C4 3E */	rlwinm r4, r26, 0x18, 0x10, 0x1f
/* 8034A778 00347358  4B FF EC 99 */	bl OSSetWirelessID
lbl_8034A77C:
/* 8034A77C 0034735C  67 40 4E 00 */	oris r0, r26, 0x4e00
/* 8034A780 00347360  7C 9F EA 14 */	add r4, r31, r29
/* 8034A784 00347364  94 04 01 F0 */	stwu r0, 0x1f0(r4)
/* 8034A788 00347368  38 00 00 80 */	li r0, 0x80
/* 8034A78C 0034736C  3C 60 80 35 */	lis r3, GetTypeCallback@ha
/* 8034A790 00347370  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A794 00347374  39 03 A5 E8 */	addi r8, r3, GetTypeCallback@l
/* 8034A798 00347378  38 7B 00 00 */	addi r3, r27, 0
/* 8034A79C 0034737C  38 DE 00 00 */	addi r6, r30, 0
/* 8034A7A0 00347380  38 A0 00 03 */	li r5, 3
/* 8034A7A4 00347384  38 E0 00 03 */	li r7, 3
/* 8034A7A8 00347388  39 40 00 00 */	li r10, 0
/* 8034A7AC 0034738C  39 20 00 00 */	li r9, 0
/* 8034A7B0 00347390  4B FF FC CD */	bl SITransfer
/* 8034A7B4 00347394  48 00 00 B8 */	b lbl_8034A86C
lbl_8034A7B8:
/* 8034A7B8 00347398  57 80 00 43 */	rlwinm. r0, r28, 0, 1, 1
/* 8034A7BC 0034739C  41 82 00 5C */	beq lbl_8034A818
/* 8034A7C0 003473A0  3C 60 00 D0 */	lis r3, 0x00CFFF00@ha
/* 8034A7C4 003473A4  38 03 FF 00 */	addi r0, r3, 0x00CFFF00@l
/* 8034A7C8 003473A8  7F 9C 00 38 */	and r28, r28, r0
/* 8034A7CC 003473AC  67 9C 00 10 */	oris r28, r28, 0x10
/* 8034A7D0 003473B0  38 7B 00 00 */	addi r3, r27, 0
/* 8034A7D4 003473B4  57 84 C4 3E */	rlwinm r4, r28, 0x18, 0x10, 0x1f
/* 8034A7D8 003473B8  4B FF EC 39 */	bl OSSetWirelessID
/* 8034A7DC 003473BC  67 80 4E 00 */	oris r0, r28, 0x4e00
/* 8034A7E0 003473C0  7C 9F EA 14 */	add r4, r31, r29
/* 8034A7E4 003473C4  94 04 01 F0 */	stwu r0, 0x1f0(r4)
/* 8034A7E8 003473C8  38 00 00 80 */	li r0, 0x80
/* 8034A7EC 003473CC  3C 60 80 35 */	lis r3, GetTypeCallback@ha
/* 8034A7F0 003473D0  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A7F4 003473D4  39 03 A5 E8 */	addi r8, r3, GetTypeCallback@l
/* 8034A7F8 003473D8  38 7B 00 00 */	addi r3, r27, 0
/* 8034A7FC 003473DC  38 DE 00 00 */	addi r6, r30, 0
/* 8034A800 003473E0  38 A0 00 03 */	li r5, 3
/* 8034A804 003473E4  38 E0 00 03 */	li r7, 3
/* 8034A808 003473E8  39 40 00 00 */	li r10, 0
/* 8034A80C 003473EC  39 20 00 00 */	li r9, 0
/* 8034A810 003473F0  4B FF FC 6D */	bl SITransfer
/* 8034A814 003473F4  48 00 00 58 */	b lbl_8034A86C
lbl_8034A818:
/* 8034A818 003473F8  38 7B 00 00 */	addi r3, r27, 0
/* 8034A81C 003473FC  38 80 00 00 */	li r4, 0
/* 8034A820 00347400  4B FF EB F1 */	bl OSSetWirelessID
lbl_8034A824:
/* 8034A824 00347404  57 60 20 36 */	slwi r0, r27, 4
/* 8034A828 00347408  83 DE 00 00 */	lwz r30, 0(r30)
/* 8034A82C 0034740C  7F FF 02 14 */	add r31, r31, r0
/* 8034A830 00347410  3B A0 00 00 */	li r29, 0
/* 8034A834 00347414  3B 9D 00 00 */	addi r28, r29, 0
/* 8034A838 00347418  3B FF 01 60 */	addi r31, r31, 0x160
lbl_8034A83C:
/* 8034A83C 0034741C  81 9F 00 00 */	lwz r12, 0(r31)
/* 8034A840 00347420  28 0C 00 00 */	cmplwi r12, 0
/* 8034A844 00347424  41 82 00 18 */	beq lbl_8034A85C
/* 8034A848 00347428  93 9F 00 00 */	stw r28, 0(r31)
/* 8034A84C 0034742C  7D 88 03 A6 */	mtlr r12
/* 8034A850 00347430  38 7B 00 00 */	addi r3, r27, 0
/* 8034A854 00347434  38 9E 00 00 */	addi r4, r30, 0
/* 8034A858 00347438  4E 80 00 21 */	blrl 
lbl_8034A85C:
/* 8034A85C 0034743C  3B BD 00 01 */	addi r29, r29, 1
/* 8034A860 00347440  2C 1D 00 04 */	cmpwi r29, 4
/* 8034A864 00347444  3B FF 00 04 */	addi r31, r31, 4
/* 8034A868 00347448  41 80 FF D4 */	blt lbl_8034A83C
lbl_8034A86C:
/* 8034A86C 0034744C  BB 41 00 18 */	lmw r26, 0x18(r1)
/* 8034A870 00347450  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8034A874 00347454  38 21 00 30 */	addi r1, r1, 0x30
/* 8034A878 00347458  7C 08 03 A6 */	mtlr r0
/* 8034A87C 0034745C  4E 80 00 20 */	blr 

.global SIGetType
SIGetType:
/* 8034A880 00347460  7C 08 02 A6 */	mflr r0
/* 8034A884 00347464  90 01 00 04 */	stw r0, 4(r1)
/* 8034A888 00347468  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8034A88C 0034746C  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8034A890 00347470  7C 7B 1B 78 */	mr r27, r3
/* 8034A894 00347474  4B FF CA D1 */	bl OSDisableInterrupts
/* 8034A898 00347478  3C 80 80 40 */	lis r4, lbl_8040236C@ha
/* 8034A89C 0034747C  57 65 10 3A */	slwi r5, r27, 2
/* 8034A8A0 00347480  38 04 23 6C */	addi r0, r4, lbl_8040236C@l
/* 8034A8A4 00347484  7F C0 2A 14 */	add r30, r0, r5
/* 8034A8A8 00347488  83 9E 00 00 */	lwz r28, 0(r30)
/* 8034A8AC 0034748C  7C 7D 1B 78 */	mr r29, r3
/* 8034A8B0 00347490  48 00 1B 61 */	bl __OSGetSystemTime
/* 8034A8B4 00347494  3C A0 80 4A */	lis r5, lbl_804A7ED8@ha
/* 8034A8B8 00347498  57 66 18 38 */	slwi r6, r27, 3
/* 8034A8BC 0034749C  38 05 7E D8 */	addi r0, r5, lbl_804A7ED8@l
/* 8034A8C0 003474A0  7F E0 32 14 */	add r31, r0, r6
/* 8034A8C4 003474A4  80 DF 00 04 */	lwz r6, 4(r31)
/* 8034A8C8 003474A8  3C A0 80 40 */	lis r5, lbl_80402358@ha
/* 8034A8CC 003474AC  38 A5 23 58 */	addi r5, r5, lbl_80402358@l
/* 8034A8D0 003474B0  80 1F 00 00 */	lwz r0, 0(r31)
/* 8034A8D4 003474B4  7C 86 20 10 */	subfc r4, r6, r4
/* 8034A8D8 003474B8  7C 00 19 10 */	subfe r0, r0, r3
/* 8034A8DC 003474BC  80 C5 00 04 */	lwz r6, 4(r5)
/* 8034A8E0 003474C0  38 A0 00 80 */	li r5, 0x80
/* 8034A8E4 003474C4  7C A3 DE 30 */	sraw r3, r5, r27
/* 8034A8E8 003474C8  7C C3 18 39 */	and. r3, r6, r3
/* 8034A8EC 003474CC  41 82 00 34 */	beq lbl_8034A920
/* 8034A8F0 003474D0  28 1C 00 08 */	cmplwi r28, 8
/* 8034A8F4 003474D4  41 82 00 20 */	beq lbl_8034A914
/* 8034A8F8 003474D8  48 00 1B 19 */	bl __OSGetSystemTime
/* 8034A8FC 003474DC  90 9F 00 04 */	stw r4, 4(r31)
/* 8034A900 003474E0  90 7F 00 00 */	stw r3, 0(r31)
/* 8034A904 003474E4  7F A3 EB 78 */	mr r3, r29
/* 8034A908 003474E8  4B FF CA 85 */	bl OSRestoreInterrupts
/* 8034A90C 003474EC  7F 83 E3 78 */	mr r3, r28
/* 8034A910 003474F0  48 00 01 20 */	b lbl_8034AA30
lbl_8034A914:
/* 8034A914 003474F4  90 BE 00 00 */	stw r5, 0(r30)
/* 8034A918 003474F8  3B 80 00 80 */	li r28, 0x80
/* 8034A91C 003474FC  48 00 00 B4 */	b lbl_8034A9D0
lbl_8034A920:
/* 8034A920 00347500  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8034A924 00347504  80 C3 00 F8 */	lwz r6, 0x800000F8@l(r3)
/* 8034A928 00347508  3C A0 10 62 */	lis r5, 0x10624DD3@ha
/* 8034A92C 0034750C  38 A5 4D D3 */	addi r5, r5, 0x10624DD3@l
/* 8034A930 00347510  54 C6 F0 BE */	srwi r6, r6, 2
/* 8034A934 00347514  7C A5 30 16 */	mulhwu r5, r5, r6
/* 8034A938 00347518  54 A5 D1 BE */	srwi r5, r5, 6
/* 8034A93C 0034751C  1C E5 00 32 */	mulli r7, r5, 0x32
/* 8034A940 00347520  38 60 00 00 */	li r3, 0
/* 8034A944 00347524  6C 66 80 00 */	xoris r6, r3, 0x8000
/* 8034A948 00347528  6C 05 80 00 */	xoris r5, r0, 0x8000
/* 8034A94C 0034752C  7C 64 38 10 */	subfc r3, r4, r7
/* 8034A950 00347530  7C A5 31 10 */	subfe r5, r5, r6
/* 8034A954 00347534  7C A6 31 10 */	subfe r5, r6, r6
/* 8034A958 00347538  7C A5 00 D1 */	neg. r5, r5
/* 8034A95C 0034753C  40 82 00 1C */	bne lbl_8034A978
/* 8034A960 00347540  28 1C 00 08 */	cmplwi r28, 8
/* 8034A964 00347544  41 82 00 14 */	beq lbl_8034A978
/* 8034A968 00347548  7F A3 EB 78 */	mr r3, r29
/* 8034A96C 0034754C  4B FF CA 21 */	bl OSRestoreInterrupts
/* 8034A970 00347550  7F 83 E3 78 */	mr r3, r28
/* 8034A974 00347554  48 00 00 BC */	b lbl_8034AA30
lbl_8034A978:
/* 8034A978 00347558  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8034A97C 0034755C  80 C3 00 F8 */	lwz r6, 0x800000F8@l(r3)
/* 8034A980 00347560  3C A0 10 62 */	lis r5, 0x10624DD3@ha
/* 8034A984 00347564  38 A5 4D D3 */	addi r5, r5, 0x10624DD3@l
/* 8034A988 00347568  54 C6 F0 BE */	srwi r6, r6, 2
/* 8034A98C 0034756C  7C A5 30 16 */	mulhwu r5, r5, r6
/* 8034A990 00347570  54 A5 D1 BE */	srwi r5, r5, 6
/* 8034A994 00347574  1C C5 00 4B */	mulli r6, r5, 0x4b
/* 8034A998 00347578  38 60 00 00 */	li r3, 0
/* 8034A99C 0034757C  6C 65 80 00 */	xoris r5, r3, 0x8000
/* 8034A9A0 00347580  6C 03 80 00 */	xoris r3, r0, 0x8000
/* 8034A9A4 00347584  7C 04 30 10 */	subfc r0, r4, r6
/* 8034A9A8 00347588  7C 63 29 10 */	subfe r3, r3, r5
/* 8034A9AC 0034758C  7C 65 29 10 */	subfe r3, r5, r5
/* 8034A9B0 00347590  7C 63 00 D1 */	neg. r3, r3
/* 8034A9B4 00347594  40 82 00 10 */	bne lbl_8034A9C4
/* 8034A9B8 00347598  38 00 00 80 */	li r0, 0x80
/* 8034A9BC 0034759C  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A9C0 003475A0  48 00 00 10 */	b lbl_8034A9D0
lbl_8034A9C4:
/* 8034A9C4 003475A4  38 00 00 80 */	li r0, 0x80
/* 8034A9C8 003475A8  90 1E 00 00 */	stw r0, 0(r30)
/* 8034A9CC 003475AC  3B 80 00 80 */	li r28, 0x80
lbl_8034A9D0:
/* 8034A9D0 003475B0  48 00 1A 41 */	bl __OSGetSystemTime
/* 8034A9D4 003475B4  90 9F 00 04 */	stw r4, 4(r31)
/* 8034A9D8 003475B8  3C 80 43 1C */	lis r4, 0x431BDE83@ha
/* 8034A9DC 003475BC  3C A0 80 35 */	lis r5, GetTypeCallback@ha
/* 8034A9E0 003475C0  90 7F 00 00 */	stw r3, 0(r31)
/* 8034A9E4 003475C4  3C 60 80 00 */	lis r3, 0x800000F8@ha
/* 8034A9E8 003475C8  39 05 A5 E8 */	addi r8, r5, GetTypeCallback@l
/* 8034A9EC 003475CC  80 03 00 F8 */	lwz r0, 0x800000F8@l(r3)
/* 8034A9F0 003475D0  38 84 DE 83 */	addi r4, r4, 0x431BDE83@l
/* 8034A9F4 003475D4  38 7B 00 00 */	addi r3, r27, 0
/* 8034A9F8 003475D8  54 00 F0 BE */	srwi r0, r0, 2
/* 8034A9FC 003475DC  7C 04 00 16 */	mulhwu r0, r4, r0
/* 8034AA00 003475E0  54 00 8B FE */	srwi r0, r0, 0xf
/* 8034AA04 003475E4  1C 00 00 41 */	mulli r0, r0, 0x41
/* 8034AA08 003475E8  54 0A E8 FE */	srwi r10, r0, 3
/* 8034AA0C 003475EC  38 DE 00 00 */	addi r6, r30, 0
/* 8034AA10 003475F0  38 8D BD 2C */	addi r4, r13, lbl_804D73CC@sda21
/* 8034AA14 003475F4  38 A0 00 01 */	li r5, 1
/* 8034AA18 003475F8  38 E0 00 03 */	li r7, 3
/* 8034AA1C 003475FC  39 20 00 00 */	li r9, 0
/* 8034AA20 00347600  4B FF FA 5D */	bl SITransfer
/* 8034AA24 00347604  7F A3 EB 78 */	mr r3, r29
/* 8034AA28 00347608  4B FF C9 65 */	bl OSRestoreInterrupts
/* 8034AA2C 0034760C  7F 83 E3 78 */	mr r3, r28
lbl_8034AA30:
/* 8034AA30 00347610  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8034AA34 00347614  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8034AA38 00347618  38 21 00 28 */	addi r1, r1, 0x28
/* 8034AA3C 0034761C  7C 08 03 A6 */	mtlr r0
/* 8034AA40 00347620  4E 80 00 20 */	blr 

.global SIGetTypeAsync
SIGetTypeAsync:
/* 8034AA44 00347624  7C 08 02 A6 */	mflr r0
/* 8034AA48 00347628  90 01 00 04 */	stw r0, 4(r1)
/* 8034AA4C 0034762C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8034AA50 00347630  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8034AA54 00347634  3B E4 00 00 */	addi r31, r4, 0
/* 8034AA58 00347638  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8034AA5C 0034763C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8034AA60 00347640  93 81 00 10 */	stw r28, 0x10(r1)
/* 8034AA64 00347644  3B 83 00 00 */	addi r28, r3, 0
/* 8034AA68 00347648  4B FF C8 FD */	bl OSDisableInterrupts
/* 8034AA6C 0034764C  3B C3 00 00 */	addi r30, r3, 0
/* 8034AA70 00347650  38 7C 00 00 */	addi r3, r28, 0
/* 8034AA74 00347654  4B FF FE 0D */	bl SIGetType
/* 8034AA78 00347658  3C 80 80 40 */	lis r4, lbl_8040236C@ha
/* 8034AA7C 0034765C  57 85 10 3A */	slwi r5, r28, 2
/* 8034AA80 00347660  38 04 23 6C */	addi r0, r4, lbl_8040236C@l
/* 8034AA84 00347664  7C 80 2A 14 */	add r4, r0, r5
/* 8034AA88 00347668  80 04 00 00 */	lwz r0, 0(r4)
/* 8034AA8C 0034766C  3B A3 00 00 */	addi r29, r3, 0
/* 8034AA90 00347670  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 8034AA94 00347674  41 82 00 AC */	beq lbl_8034AB40
/* 8034AA98 00347678  3C 60 80 4A */	lis r3, lbl_804A7F18@ha
/* 8034AA9C 0034767C  57 84 20 36 */	slwi r4, r28, 4
/* 8034AAA0 00347680  38 03 7F 18 */	addi r0, r3, lbl_804A7F18@l
/* 8034AAA4 00347684  7C 80 22 14 */	add r4, r0, r4
/* 8034AAA8 00347688  80 04 00 00 */	lwz r0, 0(r4)
/* 8034AAAC 0034768C  38 A0 00 00 */	li r5, 0
/* 8034AAB0 00347690  7C 00 F8 40 */	cmplw r0, r31
/* 8034AAB4 00347694  41 82 00 A0 */	beq lbl_8034AB54
/* 8034AAB8 00347698  28 00 00 00 */	cmplwi r0, 0
/* 8034AABC 0034769C  40 82 00 10 */	bne lbl_8034AACC
/* 8034AAC0 003476A0  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AAC4 003476A4  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AAC8 003476A8  48 00 00 8C */	b lbl_8034AB54
lbl_8034AACC:
/* 8034AACC 003476AC  38 64 00 04 */	addi r3, r4, 4
/* 8034AAD0 003476B0  80 04 00 04 */	lwz r0, 4(r4)
/* 8034AAD4 003476B4  38 A0 00 01 */	li r5, 1
/* 8034AAD8 003476B8  7C 00 F8 40 */	cmplw r0, r31
/* 8034AADC 003476BC  41 82 00 78 */	beq lbl_8034AB54
/* 8034AAE0 003476C0  28 00 00 00 */	cmplwi r0, 0
/* 8034AAE4 003476C4  40 82 00 10 */	bne lbl_8034AAF4
/* 8034AAE8 003476C8  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AAEC 003476CC  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AAF0 003476D0  48 00 00 64 */	b lbl_8034AB54
lbl_8034AAF4:
/* 8034AAF4 003476D4  84 03 00 04 */	lwzu r0, 4(r3)
/* 8034AAF8 003476D8  38 A0 00 02 */	li r5, 2
/* 8034AAFC 003476DC  7C 00 F8 40 */	cmplw r0, r31
/* 8034AB00 003476E0  41 82 00 54 */	beq lbl_8034AB54
/* 8034AB04 003476E4  28 00 00 00 */	cmplwi r0, 0
/* 8034AB08 003476E8  40 82 00 10 */	bne lbl_8034AB18
/* 8034AB0C 003476EC  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AB10 003476F0  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AB14 003476F4  48 00 00 40 */	b lbl_8034AB54
lbl_8034AB18:
/* 8034AB18 003476F8  80 03 00 04 */	lwz r0, 4(r3)
/* 8034AB1C 003476FC  38 A0 00 03 */	li r5, 3
/* 8034AB20 00347700  7C 00 F8 40 */	cmplw r0, r31
/* 8034AB24 00347704  41 82 00 30 */	beq lbl_8034AB54
/* 8034AB28 00347708  28 00 00 00 */	cmplwi r0, 0
/* 8034AB2C 0034770C  40 82 00 28 */	bne lbl_8034AB54
/* 8034AB30 00347710  54 A0 10 3A */	slwi r0, r5, 2
/* 8034AB34 00347714  7F E4 01 2E */	stwx r31, r4, r0
/* 8034AB38 00347718  48 00 00 1C */	b lbl_8034AB54
/* 8034AB3C 0034771C  48 00 00 18 */	b lbl_8034AB54
lbl_8034AB40:
/* 8034AB40 00347720  39 9F 00 00 */	addi r12, r31, 0
/* 8034AB44 00347724  7D 88 03 A6 */	mtlr r12
/* 8034AB48 00347728  38 7C 00 00 */	addi r3, r28, 0
/* 8034AB4C 0034772C  38 9D 00 00 */	addi r4, r29, 0
/* 8034AB50 00347730  4E 80 00 21 */	blrl 
lbl_8034AB54:
/* 8034AB54 00347734  7F C3 F3 78 */	mr r3, r30
/* 8034AB58 00347738  4B FF C8 35 */	bl OSRestoreInterrupts
/* 8034AB5C 0034773C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8034AB60 00347740  7F A3 EB 78 */	mr r3, r29
/* 8034AB64 00347744  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8034AB68 00347748  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8034AB6C 0034774C  7C 08 03 A6 */	mtlr r0
/* 8034AB70 00347750  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8034AB74 00347754  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8034AB78 00347758  38 21 00 20 */	addi r1, r1, 0x20
/* 8034AB7C 0034775C  4E 80 00 20 */	blr 

.section .data
    .balign 8
.global lbl_80402358
lbl_80402358:
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_8040236C
lbl_8040236C:
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x00000008
    .4byte 0x4E6F2072
    .4byte 0x6573706F
    .4byte 0x6E736500
    .4byte 0x4E363420
    .4byte 0x636F6E74
    .4byte 0x726F6C6C
    .4byte 0x65720000
    .4byte 0x4E363420
    .4byte 0x6D696372
    .4byte 0x6F70686F
    .4byte 0x6E650000
    .4byte 0x4E363420
    .4byte 0x6B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte 0x4E363420
    .4byte 0x6D6F7573
    .4byte 0x65000000
    .4byte 0x47616D65
    .4byte 0x426F7920
    .4byte 0x41647661
    .4byte 0x6E636500
    .4byte 0x5374616E
    .4byte 0x64617264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x57697265
    .4byte 0x6C657373
    .4byte 0x20726563
    .4byte 0x65697665
    .4byte 0x72000000
    .4byte 0x57617665
    .4byte 0x42697264
    .4byte 0x20636F6E
    .4byte 0x74726F6C
    .4byte 0x6C657200
    .4byte 0x4B657962
    .4byte 0x6F617264
    .4byte NULL
    .4byte NULL

.section .bss, "wa"
    .balign 8
.global Packet
Packet:
	.skip 0x80
.global Alarm
Alarm:
	.skip 0xA0
.global lbl_804A7ED8
lbl_804A7ED8:
	.skip 0x20
.global lbl_804A7EF8
lbl_804A7EF8:
	.skip 0x20
.global lbl_804A7F18
lbl_804A7F18:
	.skip 0x40
.global lbl_804A7F58
lbl_804A7F58:
	.skip 0x60

.section .sbss
    .balign 8
.global lbl_804D73C8
lbl_804D73C8:
	.skip 0x4
.global lbl_804D73CC
lbl_804D73CC:
	.skip 0x4
.global lbl_804D73D0
lbl_804D73D0:
	.skip 0x8
