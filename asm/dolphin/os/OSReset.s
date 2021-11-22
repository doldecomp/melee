.include "macros.inc"

.section .text  # 0x80348310 - 0x803486E0

.global OSRegisterResetFunction
OSRegisterResetFunction:
/* 80348310 00344EF0  80 AD BD 00 */	lwz r5, ResetFunctionQueue@sda21(r13)
/* 80348314 00344EF4  48 00 00 08 */	b lbl_8034831C
lbl_80348318:
/* 80348318 00344EF8  80 A5 00 08 */	lwz r5, 8(r5)
lbl_8034831C:
/* 8034831C 00344EFC  28 05 00 00 */	cmplwi r5, 0
/* 80348320 00344F00  41 82 00 14 */	beq lbl_80348334
/* 80348324 00344F04  80 85 00 04 */	lwz r4, 4(r5)
/* 80348328 00344F08  80 03 00 04 */	lwz r0, 4(r3)
/* 8034832C 00344F0C  7C 04 00 40 */	cmplw r4, r0
/* 80348330 00344F10  40 81 FF E8 */	ble lbl_80348318
lbl_80348334:
/* 80348334 00344F14  28 05 00 00 */	cmplwi r5, 0
/* 80348338 00344F18  40 82 00 34 */	bne lbl_8034836C
/* 8034833C 00344F1C  38 AD BD 00 */	addi r5, r13, ResetFunctionQueue@sda21
/* 80348340 00344F20  84 85 00 04 */	lwzu r4, 4(r5)
/* 80348344 00344F24  28 04 00 00 */	cmplwi r4, 0
/* 80348348 00344F28  40 82 00 0C */	bne lbl_80348354
/* 8034834C 00344F2C  90 6D BD 00 */	stw r3, ResetFunctionQueue@sda21(r13)
/* 80348350 00344F30  48 00 00 08 */	b lbl_80348358
lbl_80348354:
/* 80348354 00344F34  90 64 00 08 */	stw r3, 8(r4)
lbl_80348358:
/* 80348358 00344F38  90 83 00 0C */	stw r4, 0xc(r3)
/* 8034835C 00344F3C  38 00 00 00 */	li r0, 0
/* 80348360 00344F40  90 03 00 08 */	stw r0, 8(r3)
/* 80348364 00344F44  90 65 00 00 */	stw r3, 0(r5)
/* 80348368 00344F48  4E 80 00 20 */	blr 
lbl_8034836C:
/* 8034836C 00344F4C  90 A3 00 08 */	stw r5, 8(r3)
/* 80348370 00344F50  80 85 00 0C */	lwz r4, 0xc(r5)
/* 80348374 00344F54  90 65 00 0C */	stw r3, 0xc(r5)
/* 80348378 00344F58  28 04 00 00 */	cmplwi r4, 0
/* 8034837C 00344F5C  90 83 00 0C */	stw r4, 0xc(r3)
/* 80348380 00344F60  40 82 00 0C */	bne lbl_8034838C
/* 80348384 00344F64  90 6D BD 00 */	stw r3, ResetFunctionQueue@sda21(r13)
/* 80348388 00344F68  4E 80 00 20 */	blr 
lbl_8034838C:
/* 8034838C 00344F6C  90 64 00 08 */	stw r3, 8(r4)
/* 80348390 00344F70  4E 80 00 20 */	blr 

.global Reset
Reset:
/* 80348394 00344F74  48 00 00 20 */	b lbl_803483B4
lbl_80348398:
/* 80348398 00344F78  7D 10 FA A6 */	mfspr r8, 0x3f0
/* 8034839C 00344F7C  61 08 00 08 */	ori r8, r8, 8
/* 803483A0 00344F80  7D 10 FB A6 */	mtspr 0x3f0, r8
/* 803483A4 00344F84  4C 00 01 2C */	isync 
/* 803483A8 00344F88  7C 00 04 AC */	sync 0
/* 803483AC 00344F8C  60 00 00 00 */	nop 
/* 803483B0 00344F90  48 00 00 08 */	b lbl_803483B8
lbl_803483B4:
/* 803483B4 00344F94  48 00 00 20 */	b lbl_803483D4
lbl_803483B8:
/* 803483B8 00344F98  7C AC 42 E6 */	mftb r5, 0x10c
lbl_803483BC:
/* 803483BC 00344F9C  7C CC 42 E6 */	mftb r6, 0x10c
/* 803483C0 00344FA0  7C E5 30 50 */	subf r7, r5, r6
/* 803483C4 00344FA4  28 07 11 24 */	cmplwi r7, 0x1124
/* 803483C8 00344FA8  41 80 FF F4 */	blt lbl_803483BC
/* 803483CC 00344FAC  60 00 00 00 */	nop 
/* 803483D0 00344FB0  48 00 00 08 */	b lbl_803483D8
lbl_803483D4:
/* 803483D4 00344FB4  48 00 00 20 */	b lbl_803483F4
lbl_803483D8:
/* 803483D8 00344FB8  3D 00 CC 00 */	lis r8, 0xCC003000@h
/* 803483DC 00344FBC  61 08 30 00 */	ori r8, r8, 0xCC003000@l
/* 803483E0 00344FC0  38 80 00 03 */	li r4, 3
/* 803483E4 00344FC4  90 88 00 24 */	stw r4, 0x24(r8)
/* 803483E8 00344FC8  90 68 00 24 */	stw r3, 0x24(r8)
/* 803483EC 00344FCC  60 00 00 00 */	nop 
/* 803483F0 00344FD0  48 00 00 08 */	b lbl_803483F8
lbl_803483F4:
/* 803483F4 00344FD4  48 00 00 0C */	b lbl_80348400
lbl_803483F8:
/* 803483F8 00344FD8  60 00 00 00 */	nop 
/* 803483FC 00344FDC  4B FF FF FC */	b lbl_803483F8
lbl_80348400:
/* 80348400 00344FE0  4B FF FF 98 */	b lbl_80348398

.global __OSDoHotReset
__OSDoHotReset:
/* 80348404 00344FE4  7C 08 02 A6 */	mflr r0
/* 80348408 00344FE8  90 01 00 04 */	stw r0, 4(r1)
/* 8034840C 00344FEC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348410 00344FF0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348414 00344FF4  7C 7F 1B 78 */	mr r31, r3
/* 80348418 00344FF8  4B FF EF 4D */	bl OSDisableInterrupts
/* 8034841C 00344FFC  3C 60 CC 00 */	lis r3, 0xCC002000@ha
/* 80348420 00345000  38 63 20 00 */	addi r3, r3, 0xCC002000@l
/* 80348424 00345004  38 00 00 00 */	li r0, 0
/* 80348428 00345008  B0 03 00 02 */	sth r0, 2(r3)
/* 8034842C 0034500C  4B FF C4 E1 */	bl ICFlashInvalidate
/* 80348430 00345010  57 E3 18 38 */	slwi r3, r31, 3
/* 80348434 00345014  4B FF FF 61 */	bl Reset
/* 80348438 00345018  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8034843C 0034501C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80348440 00345020  38 21 00 18 */	addi r1, r1, 0x18
/* 80348444 00345024  7C 08 03 A6 */	mtlr r0
/* 80348448 00345028  4E 80 00 20 */	blr 

.global func_8034844C
func_8034844C:
/* 8034844C 0034502C  7C 08 02 A6 */	mflr r0
/* 80348450 00345030  90 01 00 04 */	stw r0, 4(r1)
/* 80348454 00345034  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80348458 00345038  BF 41 00 28 */	stmw r26, 0x28(r1)
/* 8034845C 0034503C  7C 7A 1B 78 */	mr r26, r3
/* 80348460 00345040  7C 9D 23 78 */	mr r29, r4
/* 80348464 00345044  7C BE 2B 78 */	mr r30, r5
/* 80348468 00345048  48 00 28 E1 */	bl OSDisableScheduler
/* 8034846C 0034504C  4B FF C2 85 */	bl __OSStopAudioSystem
/* 80348470 00345050  2C 1A 00 02 */	cmpwi r26, 2
/* 80348474 00345054  40 82 00 10 */	bne lbl_80348484
/* 80348478 00345058  38 60 00 01 */	li r3, 1
/* 8034847C 0034505C  48 00 64 6D */	bl __PADDisableRecalibration
/* 80348480 00345060  7C 7F 1B 78 */	mr r31, r3
lbl_80348484:
/* 80348484 00345064  48 00 00 04 */	b lbl_80348488
lbl_80348488:
/* 80348488 00345068  48 00 00 04 */	b lbl_8034848C
lbl_8034848C:
/* 8034848C 0034506C  83 6D BD 00 */	lwz r27, ResetFunctionQueue@sda21(r13)
/* 80348490 00345070  3B 80 00 00 */	li r28, 0
/* 80348494 00345074  48 00 00 04 */	b lbl_80348498
lbl_80348498:
/* 80348498 00345078  48 00 00 04 */	b lbl_8034849C
lbl_8034849C:
/* 8034849C 0034507C  48 00 00 24 */	b lbl_803484C0
lbl_803484A0:
/* 803484A0 00345080  38 60 00 00 */	li r3, 0
/* 803484A4 00345084  81 9B 00 00 */	lwz r12, 0(r27)
/* 803484A8 00345088  7D 88 03 A6 */	mtlr r12
/* 803484AC 0034508C  4E 80 00 21 */	blrl 
/* 803484B0 00345090  7C 60 00 34 */	cntlzw r0, r3
/* 803484B4 00345094  83 7B 00 08 */	lwz r27, 8(r27)
/* 803484B8 00345098  54 00 D9 7E */	srwi r0, r0, 5
/* 803484BC 0034509C  7F 9C 03 78 */	or r28, r28, r0
lbl_803484C0:
/* 803484C0 003450A0  28 1B 00 00 */	cmplwi r27, 0
/* 803484C4 003450A4  40 82 FF DC */	bne lbl_803484A0
/* 803484C8 003450A8  48 00 0C 7D */	bl __OSSyncSram
/* 803484CC 003450AC  7C 60 00 34 */	cntlzw r0, r3
/* 803484D0 003450B0  54 00 D9 7E */	srwi r0, r0, 5
/* 803484D4 003450B4  7F 9C 03 78 */	or r28, r28, r0
/* 803484D8 003450B8  2C 1C 00 00 */	cmpwi r28, 0
/* 803484DC 003450BC  41 82 00 0C */	beq lbl_803484E8
/* 803484E0 003450C0  38 00 00 00 */	li r0, 0
/* 803484E4 003450C4  48 00 00 08 */	b lbl_803484EC
lbl_803484E8:
/* 803484E8 003450C8  38 00 00 01 */	li r0, 1
lbl_803484EC:
/* 803484EC 003450CC  2C 00 00 00 */	cmpwi r0, 0
/* 803484F0 003450D0  41 82 FF 9C */	beq lbl_8034848C
/* 803484F4 003450D4  2C 1A 00 01 */	cmpwi r26, 1
/* 803484F8 003450D8  40 82 00 38 */	bne lbl_80348530
/* 803484FC 003450DC  2C 1E 00 00 */	cmpwi r30, 0
/* 80348500 003450E0  41 82 00 30 */	beq lbl_80348530
/* 80348504 003450E4  48 00 08 39 */	bl __OSLockSram
/* 80348508 003450E8  88 03 00 13 */	lbz r0, 0x13(r3)
/* 8034850C 003450EC  60 00 00 40 */	ori r0, r0, 0x40
/* 80348510 003450F0  98 03 00 13 */	stb r0, 0x13(r3)
/* 80348514 003450F4  38 60 00 01 */	li r3, 1
/* 80348518 003450F8  48 00 0B E5 */	bl __OSUnlockSram
/* 8034851C 003450FC  48 00 00 04 */	b lbl_80348520
lbl_80348520:
/* 80348520 00345100  48 00 00 04 */	b lbl_80348524
lbl_80348524:
/* 80348524 00345104  48 00 0C 21 */	bl __OSSyncSram
/* 80348528 00345108  2C 03 00 00 */	cmpwi r3, 0
/* 8034852C 0034510C  41 82 FF F8 */	beq lbl_80348524
lbl_80348530:
/* 80348530 00345110  4B FF EE 35 */	bl OSDisableInterrupts
/* 80348534 00345114  83 8D BD 00 */	lwz r28, ResetFunctionQueue@sda21(r13)
/* 80348538 00345118  3B 60 00 00 */	li r27, 0
/* 8034853C 0034511C  48 00 00 04 */	b lbl_80348540
lbl_80348540:
/* 80348540 00345120  48 00 00 04 */	b lbl_80348544
lbl_80348544:
/* 80348544 00345124  48 00 00 24 */	b lbl_80348568
lbl_80348548:
/* 80348548 00345128  38 60 00 01 */	li r3, 1
/* 8034854C 0034512C  81 9C 00 00 */	lwz r12, 0(r28)
/* 80348550 00345130  7D 88 03 A6 */	mtlr r12
/* 80348554 00345134  4E 80 00 21 */	blrl 
/* 80348558 00345138  7C 60 00 34 */	cntlzw r0, r3
/* 8034855C 0034513C  83 9C 00 08 */	lwz r28, 8(r28)
/* 80348560 00345140  54 00 D9 7E */	srwi r0, r0, 5
/* 80348564 00345144  7F 7B 03 78 */	or r27, r27, r0
lbl_80348568:
/* 80348568 00345148  28 1C 00 00 */	cmplwi r28, 0
/* 8034856C 0034514C  40 82 FF DC */	bne lbl_80348548
/* 80348570 00345150  48 00 0B D5 */	bl __OSSyncSram
/* 80348574 00345154  4B FF C4 C1 */	bl LCDisable
/* 80348578 00345158  2C 1A 00 01 */	cmpwi r26, 1
/* 8034857C 0034515C  40 82 00 28 */	bne lbl_803485A4
/* 80348580 00345160  4B FF ED E5 */	bl OSDisableInterrupts
/* 80348584 00345164  3C 60 CC 00 */	lis r3, 0xCC002000@ha
/* 80348588 00345168  38 63 20 00 */	addi r3, r3, 0xCC002000@l
/* 8034858C 0034516C  38 00 00 00 */	li r0, 0
/* 80348590 00345170  B0 03 00 02 */	sth r0, 2(r3)
/* 80348594 00345174  4B FF C3 79 */	bl ICFlashInvalidate
/* 80348598 00345178  57 A3 18 38 */	slwi r3, r29, 3
/* 8034859C 0034517C  4B FF FD F9 */	bl Reset
/* 803485A0 00345180  48 00 00 60 */	b lbl_80348600
lbl_803485A4:
/* 803485A4 00345184  2C 1A 00 00 */	cmpwi r26, 0
/* 803485A8 00345188  40 82 00 58 */	bne lbl_80348600
/* 803485AC 0034518C  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 803485B0 00345190  80 63 00 DC */	lwz r3, 0x800000DC@l(r3)
/* 803485B4 00345194  48 00 00 04 */	b lbl_803485B8
lbl_803485B8:
/* 803485B8 00345198  48 00 00 04 */	b lbl_803485BC
lbl_803485BC:
/* 803485BC 0034519C  48 00 00 2C */	b lbl_803485E8
lbl_803485C0:
/* 803485C0 003451A0  A0 03 02 C8 */	lhz r0, 0x2c8(r3)
/* 803485C4 003451A4  83 63 02 FC */	lwz r27, 0x2fc(r3)
/* 803485C8 003451A8  2C 00 00 04 */	cmpwi r0, 4
/* 803485CC 003451AC  41 82 00 14 */	beq lbl_803485E0
/* 803485D0 003451B0  40 80 00 14 */	bge lbl_803485E4
/* 803485D4 003451B4  2C 00 00 01 */	cmpwi r0, 1
/* 803485D8 003451B8  41 82 00 08 */	beq lbl_803485E0
/* 803485DC 003451BC  48 00 00 08 */	b lbl_803485E4
lbl_803485E0:
/* 803485E0 003451C0  48 00 2E 81 */	bl func_8034B460
lbl_803485E4:
/* 803485E4 003451C4  7F 63 DB 78 */	mr r3, r27
lbl_803485E8:
/* 803485E8 003451C8  28 03 00 00 */	cmplwi r3, 0
/* 803485EC 003451CC  40 82 FF D4 */	bne lbl_803485C0
/* 803485F0 003451D0  48 00 27 99 */	bl OSEnableScheduler
/* 803485F4 003451D4  7F A3 EB 78 */	mr r3, r29
/* 803485F8 003451D8  7F C4 F3 78 */	mr r4, r30
/* 803485FC 003451DC  4B FF FB 49 */	bl __OSReboot
lbl_80348600:
/* 80348600 003451E0  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 80348604 003451E4  80 63 00 DC */	lwz r3, 0x800000DC@l(r3)
/* 80348608 003451E8  48 00 00 04 */	b lbl_8034860C
lbl_8034860C:
/* 8034860C 003451EC  48 00 00 04 */	b lbl_80348610
lbl_80348610:
/* 80348610 003451F0  48 00 00 2C */	b lbl_8034863C
lbl_80348614:
/* 80348614 003451F4  A0 03 02 C8 */	lhz r0, 0x2c8(r3)
/* 80348618 003451F8  83 63 02 FC */	lwz r27, 0x2fc(r3)
/* 8034861C 003451FC  2C 00 00 04 */	cmpwi r0, 4
/* 80348620 00345200  41 82 00 14 */	beq lbl_80348634
/* 80348624 00345204  40 80 00 14 */	bge lbl_80348638
/* 80348628 00345208  2C 00 00 01 */	cmpwi r0, 1
/* 8034862C 0034520C  41 82 00 08 */	beq lbl_80348634
/* 80348630 00345210  48 00 00 08 */	b lbl_80348638
lbl_80348634:
/* 80348634 00345214  48 00 2E 2D */	bl func_8034B460
lbl_80348638:
/* 80348638 00345218  7F 63 DB 78 */	mr r3, r27
lbl_8034863C:
/* 8034863C 0034521C  28 03 00 00 */	cmplwi r3, 0
/* 80348640 00345220  40 82 FF D4 */	bne lbl_80348614
/* 80348644 00345224  3F A0 80 00 */	lis r29, 0x80000040@ha
/* 80348648 00345228  38 7D 00 40 */	addi r3, r29, 0x80000040@l
/* 8034864C 0034522C  38 80 00 00 */	li r4, 0
/* 80348650 00345230  38 A0 00 8C */	li r5, 0x8c
/* 80348654 00345234  4B CB AA AD */	bl memset
/* 80348658 00345238  38 7D 00 D4 */	addi r3, r29, 0xd4
/* 8034865C 0034523C  38 80 00 00 */	li r4, 0
/* 80348660 00345240  38 A0 00 14 */	li r5, 0x14
/* 80348664 00345244  4B CB AA 9D */	bl memset
/* 80348668 00345248  38 7D 00 F4 */	addi r3, r29, 0xf4
/* 8034866C 0034524C  38 80 00 00 */	li r4, 0
/* 80348670 00345250  38 A0 00 04 */	li r5, 4
/* 80348674 00345254  4B CB AA 8D */	bl memset
/* 80348678 00345258  38 7D 30 00 */	addi r3, r29, 0x3000
/* 8034867C 0034525C  38 80 00 00 */	li r4, 0
/* 80348680 00345260  38 A0 00 C0 */	li r5, 0xc0
/* 80348684 00345264  4B CB AA 7D */	bl memset
/* 80348688 00345268  38 7D 30 C8 */	addi r3, r29, 0x30c8
/* 8034868C 0034526C  38 80 00 00 */	li r4, 0
/* 80348690 00345270  38 A0 00 0C */	li r5, 0xc
/* 80348694 00345274  4B CB AA 6D */	bl memset
/* 80348698 00345278  7F E3 FB 78 */	mr r3, r31
/* 8034869C 0034527C  48 00 62 4D */	bl __PADDisableRecalibration
/* 803486A0 00345280  BB 41 00 28 */	lmw r26, 0x28(r1)
/* 803486A4 00345284  80 01 00 44 */	lwz r0, 0x44(r1)
/* 803486A8 00345288  38 21 00 40 */	addi r1, r1, 0x40
/* 803486AC 0034528C  7C 08 03 A6 */	mtlr r0
/* 803486B0 00345290  4E 80 00 20 */	blr 

.global OSGetResetCode
OSGetResetCode:
/* 803486B4 00345294  3C 60 80 00 */	lis r3, 0x800030E2@ha
/* 803486B8 00345298  88 03 30 E2 */	lbz r0, 0x800030E2@l(r3)
/* 803486BC 0034529C  28 00 00 00 */	cmplwi r0, 0
/* 803486C0 003452A0  41 82 00 0C */	beq lbl_803486CC
/* 803486C4 003452A4  3C 60 80 00 */	lis r3, 0x8000
/* 803486C8 003452A8  48 00 00 18 */	b lbl_803486E0
lbl_803486CC:
/* 803486CC 003452AC  3C 60 CC 00 */	lis r3, 0xCC003000@ha
/* 803486D0 003452B0  38 63 30 00 */	addi r3, r3, 0xCC003000@l
/* 803486D4 003452B4  80 03 00 24 */	lwz r0, 0x24(r3)
/* 803486D8 003452B8  54 00 00 38 */	rlwinm r0, r0, 0, 0, 0x1c
/* 803486DC 003452BC  54 03 E8 FE */	srwi r3, r0, 3
lbl_803486E0:
/* 803486E0 003452C0  4E 80 00 20 */	blr 
