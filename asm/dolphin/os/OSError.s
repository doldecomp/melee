.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240

.global OSReport
OSReport:
/* 803456A8 00342288  7C 08 02 A6 */	mflr r0
/* 803456AC 0034228C  90 01 00 04 */	stw r0, 4(r1)
/* 803456B0 00342290  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 803456B4 00342294  40 86 00 24 */	bne cr1, lbl_803456D8
/* 803456B8 00342298  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 803456BC 0034229C  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 803456C0 003422A0  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 803456C4 003422A4  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 803456C8 003422A8  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 803456CC 003422AC  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 803456D0 003422B0  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 803456D4 003422B4  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_803456D8:
/* 803456D8 003422B8  90 61 00 08 */	stw r3, 8(r1)
/* 803456DC 003422BC  3C 00 01 00 */	lis r0, 0x100
/* 803456E0 003422C0  90 81 00 0C */	stw r4, 0xc(r1)
/* 803456E4 003422C4  38 81 00 6C */	addi r4, r1, 0x6c
/* 803456E8 003422C8  90 A1 00 10 */	stw r5, 0x10(r1)
/* 803456EC 003422CC  90 C1 00 14 */	stw r6, 0x14(r1)
/* 803456F0 003422D0  90 E1 00 18 */	stw r7, 0x18(r1)
/* 803456F4 003422D4  91 01 00 1C */	stw r8, 0x1c(r1)
/* 803456F8 003422D8  91 21 00 20 */	stw r9, 0x20(r1)
/* 803456FC 003422DC  91 41 00 24 */	stw r10, 0x24(r1)
/* 80345700 003422E0  90 01 00 6C */	stw r0, 0x6c(r1)
/* 80345704 003422E4  38 01 00 80 */	addi r0, r1, 0x80
/* 80345708 003422E8  90 01 00 70 */	stw r0, 0x70(r1)
/* 8034570C 003422EC  38 01 00 08 */	addi r0, r1, 8
/* 80345710 003422F0  90 01 00 74 */	stw r0, 0x74(r1)
/* 80345714 003422F4  4B FD E7 25 */	bl func_80323E38
/* 80345718 003422F8  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 8034571C 003422FC  38 21 00 78 */	addi r1, r1, 0x78
/* 80345720 00342300  7C 08 03 A6 */	mtlr r0
/* 80345724 00342304  4E 80 00 20 */	blr 

.global OSPanic
OSPanic:
/* 80345728 00342308  7C 08 02 A6 */	mflr r0
/* 8034572C 0034230C  90 01 00 04 */	stw r0, 4(r1)
/* 80345730 00342310  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 80345734 00342314  93 E1 00 8C */	stw r31, 0x8c(r1)
/* 80345738 00342318  93 C1 00 88 */	stw r30, 0x88(r1)
/* 8034573C 0034231C  93 A1 00 84 */	stw r29, 0x84(r1)
/* 80345740 00342320  93 81 00 80 */	stw r28, 0x80(r1)
/* 80345744 00342324  40 86 00 24 */	bne cr1, lbl_80345768
/* 80345748 00342328  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 8034574C 0034232C  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80345750 00342330  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80345754 00342334  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80345758 00342338  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 8034575C 0034233C  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80345760 00342340  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80345764 00342344  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80345768:
/* 80345768 00342348  90 61 00 08 */	stw r3, 8(r1)
/* 8034576C 0034234C  3B 83 00 00 */	addi r28, r3, 0
/* 80345770 00342350  3B C4 00 00 */	addi r30, r4, 0
/* 80345774 00342354  90 81 00 0C */	stw r4, 0xc(r1)
/* 80345778 00342358  3B A5 00 00 */	addi r29, r5, 0
/* 8034577C 0034235C  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80345780 00342360  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80345784 00342364  3C C0 80 40 */	lis r6, lbl_80401FF8@ha
/* 80345788 00342368  3B E6 1F F8 */	addi r31, r6, lbl_80401FF8@l
/* 8034578C 0034236C  90 E1 00 18 */	stw r7, 0x18(r1)
/* 80345790 00342370  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80345794 00342374  91 21 00 20 */	stw r9, 0x20(r1)
/* 80345798 00342378  91 41 00 24 */	stw r10, 0x24(r1)
/* 8034579C 0034237C  48 00 1B C9 */	bl OSDisableInterrupts
/* 803457A0 00342380  3C 00 03 00 */	lis r0, 0x300
/* 803457A4 00342384  90 01 00 74 */	stw r0, 0x74(r1)
/* 803457A8 00342388  38 01 00 98 */	addi r0, r1, 0x98
/* 803457AC 0034238C  38 81 00 74 */	addi r4, r1, 0x74
/* 803457B0 00342390  90 01 00 78 */	stw r0, 0x78(r1)
/* 803457B4 00342394  38 01 00 08 */	addi r0, r1, 8
/* 803457B8 00342398  38 7D 00 00 */	addi r3, r29, 0
/* 803457BC 0034239C  90 01 00 7C */	stw r0, 0x7c(r1)
/* 803457C0 003423A0  4B FD E6 79 */	bl func_80323E38
/* 803457C4 003423A4  38 7F 00 00 */	addi r3, r31, 0
/* 803457C8 003423A8  4C C6 31 82 */	crclr 6
/* 803457CC 003423AC  38 9C 00 00 */	addi r4, r28, 0
/* 803457D0 003423B0  38 BE 00 00 */	addi r5, r30, 0
/* 803457D4 003423B4  4B FF FE D5 */	bl OSReport
/* 803457D8 003423B8  38 7F 00 18 */	addi r3, r31, 0x18
/* 803457DC 003423BC  4C C6 31 82 */	crclr 6
/* 803457E0 003423C0  4B FF FE C9 */	bl OSReport
/* 803457E4 003423C4  3B C0 00 00 */	li r30, 0
/* 803457E8 003423C8  4B FF FA 65 */	bl OSGetStackPointer
/* 803457EC 003423CC  7C 7D 1B 78 */	mr r29, r3
/* 803457F0 003423D0  48 00 00 20 */	b lbl_80345810
lbl_803457F4:
/* 803457F4 003423D4  80 BD 00 00 */	lwz r5, 0(r29)
/* 803457F8 003423D8  7F A4 EB 78 */	mr r4, r29
/* 803457FC 003423DC  80 DD 00 04 */	lwz r6, 4(r29)
/* 80345800 003423E0  38 7F 00 40 */	addi r3, r31, 0x40
/* 80345804 003423E4  4C C6 31 82 */	crclr 6
/* 80345808 003423E8  4B FF FE A1 */	bl OSReport
/* 8034580C 003423EC  83 BD 00 00 */	lwz r29, 0(r29)
lbl_80345810:
/* 80345810 003423F0  28 1D 00 00 */	cmplwi r29, 0
/* 80345814 003423F4  41 82 00 1C */	beq lbl_80345830
/* 80345818 003423F8  3C 1D 00 01 */	addis r0, r29, 1
/* 8034581C 003423FC  28 00 FF FF */	cmplwi r0, 0xffff
/* 80345820 00342400  41 82 00 10 */	beq lbl_80345830
/* 80345824 00342404  28 1E 00 10 */	cmplwi r30, 0x10
/* 80345828 00342408  3B DE 00 01 */	addi r30, r30, 1
/* 8034582C 0034240C  41 80 FF C8 */	blt lbl_803457F4
lbl_80345830:
/* 80345830 00342410  4B FF 06 65 */	bl PPCHalt
/* 80345834 00342414  80 01 00 94 */	lwz r0, 0x94(r1)
/* 80345838 00342418  83 E1 00 8C */	lwz r31, 0x8c(r1)
/* 8034583C 0034241C  83 C1 00 88 */	lwz r30, 0x88(r1)
/* 80345840 00342420  7C 08 03 A6 */	mtlr r0
/* 80345844 00342424  83 A1 00 84 */	lwz r29, 0x84(r1)
/* 80345848 00342428  83 81 00 80 */	lwz r28, 0x80(r1)
/* 8034584C 0034242C  38 21 00 90 */	addi r1, r1, 0x90
/* 80345850 00342430  4E 80 00 20 */	blr

.global OSSetErrorHandler
OSSetErrorHandler:
/* 80345854 00342434  3C A0 80 4A */	lis r5, __OSErrorTable@ha
/* 80345858 00342438  54 63 13 BA */	rlwinm r3, r3, 2, 0xe, 0x1d
/* 8034585C 0034243C  38 05 7C 40 */	addi r0, r5, __OSErrorTable@l
/* 80345860 00342440  7C A0 1A 14 */	add r5, r0, r3
/* 80345864 00342444  80 65 00 00 */	lwz r3, 0(r5)
/* 80345868 00342448  90 85 00 00 */	stw r4, 0(r5)
/* 8034586C 0034244C  4E 80 00 20 */	blr 

.global __OSUnhandledException
__OSUnhandledException:
/* 80345870 00342450  7C 08 02 A6 */	mflr r0
/* 80345874 00342454  90 01 00 04 */	stw r0, 4(r1)
/* 80345878 00342458  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8034587C 0034245C  BF 21 00 1C */	stmw r25, 0x1c(r1)
/* 80345880 00342460  7C 9F 23 78 */	mr r31, r4
/* 80345884 00342464  3B 23 00 00 */	addi r25, r3, 0
/* 80345888 00342468  3B 45 00 00 */	addi r26, r5, 0
/* 8034588C 0034246C  3B 66 00 00 */	addi r27, r6, 0
/* 80345890 00342470  80 04 01 9C */	lwz r0, 0x19c(r4)
/* 80345894 00342474  3C 80 80 40 */	lis r4, lbl_80401FF8@ha
/* 80345898 00342478  3B A4 1F F8 */	addi r29, r4, lbl_80401FF8@l
/* 8034589C 0034247C  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 803458A0 00342480  40 82 00 18 */	bne lbl_803458B8
/* 803458A4 00342484  38 7D 00 5C */	addi r3, r29, 0x5c
/* 803458A8 00342488  4C C6 31 82 */	crclr 6
/* 803458AC 0034248C  57 24 06 3E */	clrlwi r4, r25, 0x18
/* 803458B0 00342490  4B FF FD F9 */	bl OSReport
/* 803458B4 00342494  48 00 00 7C */	b lbl_80345930
lbl_803458B8:
/* 803458B8 00342498  57 3E 06 3E */	clrlwi r30, r25, 0x18
/* 803458BC 0034249C  3C 60 80 4A */	lis r3, __OSErrorTable@ha
/* 803458C0 003424A0  57 24 15 BA */	rlwinm r4, r25, 2, 0x16, 0x1d
/* 803458C4 003424A4  38 03 7C 40 */	addi r0, r3, __OSErrorTable@l
/* 803458C8 003424A8  7F 80 22 14 */	add r28, r0, r4
/* 803458CC 003424AC  80 1C 00 00 */	lwz r0, 0(r28)
/* 803458D0 003424B0  28 00 00 00 */	cmplwi r0, 0
/* 803458D4 003424B4  41 82 00 38 */	beq lbl_8034590C
/* 803458D8 003424B8  48 00 54 71 */	bl OSDisableScheduler
/* 803458DC 003424BC  81 9C 00 00 */	lwz r12, 0(r28)
/* 803458E0 003424C0  38 7E 00 00 */	addi r3, r30, 0
/* 803458E4 003424C4  38 9F 00 00 */	addi r4, r31, 0
/* 803458E8 003424C8  4C C6 31 82 */	crclr 6
/* 803458EC 003424CC  7D 88 03 A6 */	mtlr r12
/* 803458F0 003424D0  38 BA 00 00 */	addi r5, r26, 0
/* 803458F4 003424D4  38 DB 00 00 */	addi r6, r27, 0
/* 803458F8 003424D8  4E 80 00 21 */	blrl 
/* 803458FC 003424DC  48 00 54 8D */	bl OSEnableScheduler
/* 80345900 003424E0  48 00 59 2D */	bl __OSReschedule
/* 80345904 003424E4  7F E3 FB 78 */	mr r3, r31
/* 80345908 003424E8  4B FF F8 6D */	bl OSLoadContext
lbl_8034590C:
/* 8034590C 003424EC  57 20 06 3E */	clrlwi r0, r25, 0x18
/* 80345910 003424F0  28 00 00 08 */	cmplwi r0, 8
/* 80345914 003424F4  40 82 00 0C */	bne lbl_80345920
/* 80345918 003424F8  7F E3 FB 78 */	mr r3, r31
/* 8034591C 003424FC  4B FF F8 59 */	bl OSLoadContext
lbl_80345920:
/* 80345920 00342500  38 7D 00 7C */	addi r3, r29, 0x7c
/* 80345924 00342504  4C C6 31 82 */	crclr 6
/* 80345928 00342508  57 24 06 3E */	clrlwi r4, r25, 0x18
/* 8034592C 0034250C  4B FF FD 7D */	bl OSReport
lbl_80345930:
/* 80345930 00342510  38 6D A5 78 */	addi r3, r13, lbl_804D5C18@sda21
/* 80345934 00342514  4C C6 31 82 */	crclr 6
/* 80345938 00342518  4B FF FD 71 */	bl OSReport
/* 8034593C 0034251C  7F E3 FB 78 */	mr r3, r31
/* 80345940 00342520  4B FF F9 F5 */	bl OSDumpContext
/* 80345944 00342524  38 9A 00 00 */	addi r4, r26, 0
/* 80345948 00342528  4C C6 31 82 */	crclr 6
/* 8034594C 0034252C  38 BB 00 00 */	addi r5, r27, 0
/* 80345950 00342530  38 7D 00 94 */	addi r3, r29, 0x94
/* 80345954 00342534  4B FF FD 55 */	bl OSReport
/* 80345958 00342538  48 00 6A 99 */	bl OSGetTime
/* 8034595C 0034253C  38 A3 00 00 */	addi r5, r3, 0
/* 80345960 00342540  4C C6 31 82 */	crclr 6
/* 80345964 00342544  38 C4 00 00 */	addi r6, r4, 0
/* 80345968 00342548  38 7D 00 C8 */	addi r3, r29, 0xc8
/* 8034596C 0034254C  4B FF FD 3D */	bl OSReport
/* 80345970 00342550  57 20 06 3E */	clrlwi r0, r25, 0x18
/* 80345974 00342554  28 00 00 0F */	cmplwi r0, 0xf
/* 80345978 00342558  41 81 00 C4 */	bgt lbl_80345A3C
/* 8034597C 0034255C  3C 60 80 40 */	lis r3, jtbl_804022D4@ha
/* 80345980 00342560  38 63 22 D4 */	addi r3, r3, jtbl_804022D4@l
/* 80345984 00342564  54 00 10 3A */	slwi r0, r0, 2
/* 80345988 00342568  7C 03 00 2E */	lwzx r0, r3, r0
/* 8034598C 0034256C  7C 09 03 A6 */	mtctr r0
/* 80345990 00342570  4E 80 04 20 */	bctr 
.global lbl_80345994
lbl_80345994:
/* 80345994 00342574  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 80345998 00342578  38 BB 00 00 */	addi r5, r27, 0
/* 8034599C 0034257C  38 7D 00 D8 */	addi r3, r29, 0xd8
/* 803459A0 00342580  4C C6 31 82 */	crclr 6
/* 803459A4 00342584  4B FF FD 05 */	bl OSReport
/* 803459A8 00342588  48 00 00 94 */	b lbl_80345A3C
.global lbl_803459AC
lbl_803459AC:
/* 803459AC 0034258C  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459B0 00342590  38 7D 01 38 */	addi r3, r29, 0x138
/* 803459B4 00342594  4C C6 31 82 */	crclr 6
/* 803459B8 00342598  4B FF FC F1 */	bl OSReport
/* 803459BC 0034259C  48 00 00 80 */	b lbl_80345A3C
.global lbl_803459C0
lbl_803459C0:
/* 803459C0 003425A0  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459C4 003425A4  38 BB 00 00 */	addi r5, r27, 0
/* 803459C8 003425A8  38 7D 01 84 */	addi r3, r29, 0x184
/* 803459CC 003425AC  4C C6 31 82 */	crclr 6
/* 803459D0 003425B0  4B FF FC D9 */	bl OSReport
/* 803459D4 003425B4  48 00 00 68 */	b lbl_80345A3C
.global lbl_803459D8
lbl_803459D8:
/* 803459D8 003425B8  80 9F 01 98 */	lwz r4, 0x198(r31)
/* 803459DC 003425BC  38 BB 00 00 */	addi r5, r27, 0
/* 803459E0 003425C0  38 7D 01 E8 */	addi r3, r29, 0x1e8
/* 803459E4 003425C4  4C C6 31 82 */	crclr 6
/* 803459E8 003425C8  4B FF FC C1 */	bl OSReport
/* 803459EC 003425CC  48 00 00 50 */	b lbl_80345A3C
.global lbl_803459F0
lbl_803459F0:
/* 803459F0 003425D0  38 6D A5 78 */	addi r3, r13, lbl_804D5C18@sda21
/* 803459F4 003425D4  4C C6 31 82 */	crclr 6
/* 803459F8 003425D8  4B FF FC B1 */	bl OSReport
/* 803459FC 003425DC  3F C0 CC 00 */	lis r30, 0xCC005000@ha
/* 80345A00 003425E0  4C C6 31 82 */	crclr 6
/* 80345A04 003425E4  3B FE 50 00 */	addi r31, r30, 0xCC005000@l
/* 80345A08 003425E8  A0 9E 50 30 */	lhz r4, 0x5030(r30)
/* 80345A0C 003425EC  38 7D 02 48 */	addi r3, r29, 0x248
/* 80345A10 003425F0  A0 BE 50 32 */	lhz r5, 0x5032(r30)
/* 80345A14 003425F4  4B FF FC 95 */	bl OSReport
/* 80345A18 003425F8  A0 9F 00 20 */	lhz r4, 0x20(r31)
/* 80345A1C 003425FC  38 7D 02 68 */	addi r3, r29, 0x268
/* 80345A20 00342600  A0 BF 00 22 */	lhz r5, 0x22(r31)
/* 80345A24 00342604  4C C6 31 82 */	crclr 6
/* 80345A28 00342608  4B FF FC 81 */	bl OSReport
/* 80345A2C 0034260C  80 9E 60 14 */	lwz r4, 0x6014(r30)
/* 80345A30 00342610  4C C6 31 82 */	crclr 6
/* 80345A34 00342614  38 7D 02 88 */	addi r3, r29, 0x288
/* 80345A38 00342618  4B FF FC 71 */	bl OSReport
.global lbl_80345A3C
lbl_80345A3C:
/* 80345A3C 0034261C  A8 8D BC E0 */	lha r4, __OSLastInterrupt@sda21(r13)
/* 80345A40 00342620  38 7D 02 A4 */	addi r3, r29, 0x2a4
/* 80345A44 00342624  4C C6 31 82 */	crclr 6
/* 80345A48 00342628  80 AD BC DC */	lwz r5, __OSLastInterruptSrr0@sda21(r13)
/* 80345A4C 0034262C  80 ED BC E8 */	lwz r7, __OSLastInterruptTime@sda21(r13)
/* 80345A50 00342630  81 0D BC EC */	lwz r8, lbl_804D738C@sda21(r13)
/* 80345A54 00342634  4B FF FC 55 */	bl OSReport
/* 80345A58 00342638  4B FF 04 3D */	bl PPCHalt
/* 80345A5C 0034263C  BB 21 00 1C */	lmw r25, 0x1c(r1)
/* 80345A60 00342640  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80345A64 00342644  38 21 00 38 */	addi r1, r1, 0x38
/* 80345A68 00342648  7C 08 03 A6 */	mtlr r0
/* 80345A6C 0034264C  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_80401FF8
lbl_80401FF8:
    .asciz " in \"%s\" on line %d.\n"
    .balign 4
    .asciz "\nAddress:      Back Chain    LR Save\n"
    .balign 4
    .asciz "0x%08x:   0x%08x    0x%08x\n"
    .balign 4
    .asciz "Non-recoverable Exception %d"
    .balign 4
    .asciz "Unhandled Exception %d"
    .balign 4
    .asciz "\nDSISR = 0x%08x                   DAR  = 0x%08x\n"
    .balign 4
    .asciz "TB = 0x%016llx\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "AI DMA Address =   0x%04x%04x\n"
    .balign 4
    .asciz "ARAM DMA Address = 0x%04x%04x\n"
    .balign 4
    .asciz "DI DMA Address =   0x%08x\n"
    .balign 4
    .asciz "\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n"
    .balign 4
.global jtbl_804022D4
jtbl_804022D4:
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345994
	.4byte lbl_803459AC
	.4byte lbl_80345A3C
	.4byte lbl_803459C0
	.4byte lbl_803459D8
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_80345A3C
	.4byte lbl_803459F0


.section .bss, "wa"
    .balign 8
.global __OSErrorTable
__OSErrorTable:
	.skip 0x40


.section .sdata
    .balign 8
.global lbl_804D5C18
lbl_804D5C18:
    .4byte 0x0A000000
    .4byte 0x00000000
