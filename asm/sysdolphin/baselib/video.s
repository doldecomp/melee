.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global HSD_Video_803764A8
HSD_Video_803764A8:
/* 803764A8 00373088  7C 08 02 A6 */	mflr r0
/* 803764AC 0037308C  3C 60 80 4C */	lis r3, HSD_VIData@ha
/* 803764B0 00373090  90 01 00 04 */	stw r0, 4(r1)
/* 803764B4 00373094  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803764B8 00373098  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803764BC 0037309C  3B E3 1D 80 */	addi r31, r3, HSD_VIData@l
/* 803764C0 003730A0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803764C4 003730A4  93 A1 00 14 */	stw r29, 0x14(r1)
/* 803764C8 003730A8  93 81 00 10 */	stw r28, 0x10(r1)
/* 803764CC 003730AC  80 1F 01 D4 */	lwz r0, 0x1d4(r31)
/* 803764D0 003730B0  2C 00 00 02 */	cmpwi r0, 2
/* 803764D4 003730B4  41 80 00 B4 */	blt .L_80376588
.L_803764D8:
/* 803764D8 003730B8  4B FD 0E 8D */	bl OSDisableInterrupts
/* 803764DC 003730BC  80 1F 00 5C */	lwz r0, 0x5c(r31)
/* 803764E0 003730C0  3B C3 00 00 */	addi r30, r3, 0
/* 803764E4 003730C4  2C 00 00 04 */	cmpwi r0, 4
/* 803764E8 003730C8  40 82 00 0C */	bne .L_803764F4
/* 803764EC 003730CC  38 00 00 00 */	li r0, 0
/* 803764F0 003730D0  48 00 00 34 */	b .L_80376524
.L_803764F4:
/* 803764F4 003730D4  38 7F 00 60 */	addi r3, r31, 0x60
/* 803764F8 003730D8  80 1F 00 BC */	lwz r0, 0xbc(r31)
/* 803764FC 003730DC  2C 00 00 04 */	cmpwi r0, 4
/* 80376500 003730E0  40 82 00 0C */	bne .L_8037650C
/* 80376504 003730E4  38 00 00 01 */	li r0, 1
/* 80376508 003730E8  48 00 00 1C */	b .L_80376524
.L_8037650C:
/* 8037650C 003730EC  80 03 00 BC */	lwz r0, 0xbc(r3)
/* 80376510 003730F0  2C 00 00 04 */	cmpwi r0, 4
/* 80376514 003730F4  40 82 00 0C */	bne .L_80376520
/* 80376518 003730F8  38 00 00 02 */	li r0, 2
/* 8037651C 003730FC  48 00 00 08 */	b .L_80376524
.L_80376520:
/* 80376520 00373100  38 00 FF FF */	li r0, -1
.L_80376524:
/* 80376524 00373104  2C 00 FF FF */	cmpwi r0, -1
/* 80376528 00373108  3B A0 00 01 */	li r29, 1
/* 8037652C 0037310C  3B 9D 00 00 */	addi r28, r29, 0
/* 80376530 00373110  40 82 00 18 */	bne .L_80376548
/* 80376534 00373114  38 60 00 05 */	li r3, 5
/* 80376538 00373118  4B FF F3 55 */	bl HSD_VISearchXFBByStatus
/* 8037653C 0037311C  2C 03 FF FF */	cmpwi r3, -1
/* 80376540 00373120  40 82 00 08 */	bne .L_80376548
/* 80376544 00373124  3B 80 00 00 */	li r28, 0
.L_80376548:
/* 80376548 00373128  2C 1C 00 00 */	cmpwi r28, 0
/* 8037654C 0037312C  40 82 00 18 */	bne .L_80376564
/* 80376550 00373130  38 60 00 06 */	li r3, 6
/* 80376554 00373134  4B FF F3 39 */	bl HSD_VISearchXFBByStatus
/* 80376558 00373138  2C 03 FF FF */	cmpwi r3, -1
/* 8037655C 0037313C  40 82 00 08 */	bne .L_80376564
/* 80376560 00373140  3B A0 00 00 */	li r29, 0
.L_80376564:
/* 80376564 00373144  2C 1D 00 00 */	cmpwi r29, 0
/* 80376568 00373148  41 82 00 0C */	beq .L_80376574
/* 8037656C 0037314C  3B 80 00 01 */	li r28, 1
/* 80376570 00373150  48 00 00 08 */	b .L_80376578
.L_80376574:
/* 80376574 00373154  3B 80 00 00 */	li r28, 0
.L_80376578:
/* 80376578 00373158  7F C3 F3 78 */	mr r3, r30
/* 8037657C 0037315C  4B FD 0E 11 */	bl OSRestoreInterrupts
/* 80376580 00373160  2C 1C 00 00 */	cmpwi r28, 0
/* 80376584 00373164  40 82 FF 54 */	bne .L_803764D8
.L_80376588:
/* 80376588 00373168  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8037658C 0037316C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80376590 00373170  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80376594 00373174  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80376598 00373178  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8037659C 0037317C  38 21 00 20 */	addi r1, r1, 0x20
/* 803765A0 00373180  7C 08 03 A6 */	mtlr r0
/* 803765A4 00373184  4E 80 00 20 */	blr

.global HSD_Video_803765A8
HSD_Video_803765A8:
/* 803765A8 00373188  7C 08 02 A6 */	mflr r0
/* 803765AC 0037318C  90 01 00 04 */	stw r0, 4(r1)
/* 803765B0 00373190  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803765B4 00373194  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803765B8 00373198  4B FD 0D AD */	bl OSDisableInterrupts
/* 803765BC 0037319C  3C 80 80 4C */	lis r4, HSD_VIData@ha
/* 803765C0 003731A0  38 84 1D 80 */	addi r4, r4, HSD_VIData@l
/* 803765C4 003731A4  80 04 00 5C */	lwz r0, 0x5c(r4)
/* 803765C8 003731A8  2C 00 00 04 */	cmpwi r0, 4
/* 803765CC 003731AC  40 82 00 0C */	bne .L_803765D8
/* 803765D0 003731B0  38 00 00 00 */	li r0, 0
/* 803765D4 003731B4  48 00 00 34 */	b .L_80376608
.L_803765D8:
/* 803765D8 003731B8  38 A4 00 60 */	addi r5, r4, 0x60
/* 803765DC 003731BC  80 04 00 BC */	lwz r0, 0xbc(r4)
/* 803765E0 003731C0  2C 00 00 04 */	cmpwi r0, 4
/* 803765E4 003731C4  40 82 00 0C */	bne .L_803765F0
/* 803765E8 003731C8  38 00 00 01 */	li r0, 1
/* 803765EC 003731CC  48 00 00 1C */	b .L_80376608
.L_803765F0:
/* 803765F0 003731D0  80 05 00 BC */	lwz r0, 0xbc(r5)
/* 803765F4 003731D4  2C 00 00 04 */	cmpwi r0, 4
/* 803765F8 003731D8  40 82 00 0C */	bne .L_80376604
/* 803765FC 003731DC  38 00 00 02 */	li r0, 2
/* 80376600 003731E0  48 00 00 08 */	b .L_80376608
.L_80376604:
/* 80376604 003731E4  38 00 FF FF */	li r0, -1
.L_80376608:
/* 80376608 003731E8  7C 1F 03 78 */	mr r31, r0
/* 8037660C 003731EC  2C 1F FF FF */	cmpwi r31, -1
/* 80376610 003731F0  40 82 00 EC */	bne .L_803766FC
/* 80376614 003731F4  80 04 00 5C */	lwz r0, 0x5c(r4)
/* 80376618 003731F8  2C 00 00 05 */	cmpwi r0, 5
/* 8037661C 003731FC  40 82 00 0C */	bne .L_80376628
/* 80376620 00373200  38 00 00 00 */	li r0, 0
/* 80376624 00373204  48 00 00 34 */	b .L_80376658
.L_80376628:
/* 80376628 00373208  38 A4 00 60 */	addi r5, r4, 0x60
/* 8037662C 0037320C  80 04 00 BC */	lwz r0, 0xbc(r4)
/* 80376630 00373210  2C 00 00 05 */	cmpwi r0, 5
/* 80376634 00373214  40 82 00 0C */	bne .L_80376640
/* 80376638 00373218  38 00 00 01 */	li r0, 1
/* 8037663C 0037321C  48 00 00 1C */	b .L_80376658
.L_80376640:
/* 80376640 00373220  80 05 00 BC */	lwz r0, 0xbc(r5)
/* 80376644 00373224  2C 00 00 05 */	cmpwi r0, 5
/* 80376648 00373228  40 82 00 0C */	bne .L_80376654
/* 8037664C 0037322C  38 00 00 02 */	li r0, 2
/* 80376650 00373230  48 00 00 08 */	b .L_80376658
.L_80376654:
/* 80376654 00373234  38 00 FF FF */	li r0, -1
.L_80376658:
/* 80376658 00373238  7C 1F 03 78 */	mr r31, r0
/* 8037665C 0037323C  2C 1F FF FF */	cmpwi r31, -1
/* 80376660 00373240  40 82 00 9C */	bne .L_803766FC
/* 80376664 00373244  80 04 00 5C */	lwz r0, 0x5c(r4)
/* 80376668 00373248  2C 00 00 06 */	cmpwi r0, 6
/* 8037666C 0037324C  40 82 00 0C */	bne .L_80376678
/* 80376670 00373250  38 00 00 00 */	li r0, 0
/* 80376674 00373254  48 00 00 34 */	b .L_803766A8
.L_80376678:
/* 80376678 00373258  38 A4 00 60 */	addi r5, r4, 0x60
/* 8037667C 0037325C  80 04 00 BC */	lwz r0, 0xbc(r4)
/* 80376680 00373260  2C 00 00 06 */	cmpwi r0, 6
/* 80376684 00373264  40 82 00 0C */	bne .L_80376690
/* 80376688 00373268  38 00 00 01 */	li r0, 1
/* 8037668C 0037326C  48 00 00 1C */	b .L_803766A8
.L_80376690:
/* 80376690 00373270  80 05 00 BC */	lwz r0, 0xbc(r5)
/* 80376694 00373274  2C 00 00 06 */	cmpwi r0, 6
/* 80376698 00373278  40 82 00 0C */	bne .L_803766A4
/* 8037669C 0037327C  38 00 00 02 */	li r0, 2
/* 803766A0 00373280  48 00 00 08 */	b .L_803766A8
.L_803766A4:
/* 803766A4 00373284  38 00 FF FF */	li r0, -1
.L_803766A8:
/* 803766A8 00373288  7C 1F 03 78 */	mr r31, r0
/* 803766AC 0037328C  2C 1F FF FF */	cmpwi r31, -1
/* 803766B0 00373290  40 82 00 4C */	bne .L_803766FC
/* 803766B4 00373294  80 04 00 5C */	lwz r0, 0x5c(r4)
/* 803766B8 00373298  2C 00 00 07 */	cmpwi r0, 7
/* 803766BC 0037329C  40 82 00 0C */	bne .L_803766C8
/* 803766C0 003732A0  38 00 00 00 */	li r0, 0
/* 803766C4 003732A4  48 00 00 34 */	b .L_803766F8
.L_803766C8:
/* 803766C8 003732A8  38 84 00 60 */	addi r4, r4, 0x60
/* 803766CC 003732AC  80 04 00 5C */	lwz r0, 0x5c(r4)
/* 803766D0 003732B0  2C 00 00 07 */	cmpwi r0, 7
/* 803766D4 003732B4  40 82 00 0C */	bne .L_803766E0
/* 803766D8 003732B8  38 00 00 01 */	li r0, 1
/* 803766DC 003732BC  48 00 00 1C */	b .L_803766F8
.L_803766E0:
/* 803766E0 003732C0  80 04 00 BC */	lwz r0, 0xbc(r4)
/* 803766E4 003732C4  2C 00 00 07 */	cmpwi r0, 7
/* 803766E8 003732C8  40 82 00 0C */	bne .L_803766F4
/* 803766EC 003732CC  38 00 00 02 */	li r0, 2
/* 803766F0 003732D0  48 00 00 08 */	b .L_803766F8
.L_803766F4:
/* 803766F4 003732D4  38 00 FF FF */	li r0, -1
.L_803766F8:
/* 803766F8 003732D8  7C 1F 03 78 */	mr r31, r0
.L_803766FC:
/* 803766FC 003732DC  4B FD 0C 91 */	bl OSRestoreInterrupts
/* 80376700 003732E0  7F E3 FB 78 */	mr r3, r31
/* 80376704 003732E4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80376708 003732E8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8037670C 003732EC  38 21 00 10 */	addi r1, r1, 0x10
/* 80376710 003732F0  7C 08 03 A6 */	mtlr r0
/* 80376714 003732F4  4E 80 00 20 */	blr

.global HSD_VISetConfigure
HSD_VISetConfigure:
/* 80376718 003732F8  80 A3 00 00 */	lwz r5, 0(r3)
/* 8037671C 003732FC  3C C0 80 4C */	lis r6, HSD_VIData@ha
/* 80376720 00373300  80 83 00 04 */	lwz r4, 4(r3)
/* 80376724 00373304  38 00 00 01 */	li r0, 1
/* 80376728 00373308  94 A6 1D 80 */	stwu r5, HSD_VIData@l(r6)
/* 8037672C 0037330C  90 86 00 04 */	stw r4, 4(r6)
/* 80376730 00373310  80 A3 00 08 */	lwz r5, 8(r3)
/* 80376734 00373314  80 83 00 0C */	lwz r4, 0xc(r3)
/* 80376738 00373318  90 A6 00 08 */	stw r5, 8(r6)
/* 8037673C 0037331C  90 86 00 0C */	stw r4, 0xc(r6)
/* 80376740 00373320  80 A3 00 10 */	lwz r5, 0x10(r3)
/* 80376744 00373324  80 83 00 14 */	lwz r4, 0x14(r3)
/* 80376748 00373328  90 A6 00 10 */	stw r5, 0x10(r6)
/* 8037674C 0037332C  90 86 00 14 */	stw r4, 0x14(r6)
/* 80376750 00373330  80 A3 00 18 */	lwz r5, 0x18(r3)
/* 80376754 00373334  80 83 00 1C */	lwz r4, 0x1c(r3)
/* 80376758 00373338  90 A6 00 18 */	stw r5, 0x18(r6)
/* 8037675C 0037333C  90 86 00 1C */	stw r4, 0x1c(r6)
/* 80376760 00373340  80 A3 00 20 */	lwz r5, 0x20(r3)
/* 80376764 00373344  80 83 00 24 */	lwz r4, 0x24(r3)
/* 80376768 00373348  90 A6 00 20 */	stw r5, 0x20(r6)
/* 8037676C 0037334C  90 86 00 24 */	stw r4, 0x24(r6)
/* 80376770 00373350  80 A3 00 28 */	lwz r5, 0x28(r3)
/* 80376774 00373354  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80376778 00373358  90 A6 00 28 */	stw r5, 0x28(r6)
/* 8037677C 0037335C  90 86 00 2C */	stw r4, 0x2c(r6)
/* 80376780 00373360  80 A3 00 30 */	lwz r5, 0x30(r3)
/* 80376784 00373364  80 83 00 34 */	lwz r4, 0x34(r3)
/* 80376788 00373368  90 A6 00 30 */	stw r5, 0x30(r6)
/* 8037678C 0037336C  90 86 00 34 */	stw r4, 0x34(r6)
/* 80376790 00373370  80 63 00 38 */	lwz r3, 0x38(r3)
/* 80376794 00373374  90 66 00 38 */	stw r3, 0x38(r6)
/* 80376798 00373378  98 06 00 54 */	stb r0, 0x54(r6)
/* 8037679C 0037337C  4E 80 00 20 */	blr

.global HSD_VISetBlack
HSD_VISetBlack:
/* 803767A0 00373380  3C 80 80 4C */	lis r4, HSD_VIData@ha
/* 803767A4 00373384  38 84 1D 80 */	addi r4, r4, HSD_VIData@l
/* 803767A8 00373388  90 64 00 3C */	stw r3, 0x3c(r4)
/* 803767AC 0037338C  38 00 00 01 */	li r0, 1
/* 803767B0 00373390  98 04 00 54 */	stb r0, 0x54(r4)
/* 803767B4 00373394  4E 80 00 20 */	blr

.global HSD_VIInit
HSD_VIInit:
/* 803767B8 00373398  7C 08 02 A6 */	mflr r0
/* 803767BC 0037339C  3C E0 80 4C */	lis r7, garbage@ha
/* 803767C0 003733A0  90 01 00 04 */	stw r0, 4(r1)
/* 803767C4 003733A4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 803767C8 003733A8  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 803767CC 003733AC  3B C3 00 00 */	addi r30, r3, 0
/* 803767D0 003733B0  3B 64 00 00 */	addi r27, r4, 0
/* 803767D4 003733B4  3B 85 00 00 */	addi r28, r5, 0
/* 803767D8 003733B8  3B A6 00 00 */	addi r29, r6, 0
/* 803767DC 003733BC  3B E7 09 80 */	addi r31, r7, garbage@l
/* 803767E0 003733C0  4B FD 86 BD */	bl VIInit
/* 803767E4 003733C4  38 00 00 0A */	li r0, 0xa
/* 803767E8 003733C8  7C 09 03 A6 */	mtctr r0
/* 803767EC 003733CC  38 BF 13 F8 */	addi r5, r31, 0x13f8
/* 803767F0 003733D0  38 9E FF F8 */	addi r4, r30, -8
.L_803767F4:
/* 803767F4 003733D4  84 64 00 08 */	lwzu r3, 8(r4)
/* 803767F8 003733D8  80 04 00 04 */	lwz r0, 4(r4)
/* 803767FC 003733DC  94 65 00 08 */	stwu r3, 8(r5)
/* 80376800 003733E0  90 05 00 04 */	stw r0, 4(r5)
/* 80376804 003733E4  42 00 FF F0 */	bdnz .L_803767F4
/* 80376808 003733E8  80 04 00 08 */	lwz r0, 8(r4)
/* 8037680C 003733EC  3B DF 14 00 */	addi r30, r31, 0x1400
/* 80376810 003733F0  39 00 00 00 */	li r8, 0
/* 80376814 003733F4  90 05 00 08 */	stw r0, 8(r5)
/* 80376818 003733F8  39 3E 00 00 */	addi r9, r30, 0
/* 8037681C 003733FC  39 40 00 00 */	li r10, 0
/* 80376820 00373400  99 1F 14 54 */	stb r8, 0x1454(r31)
/* 80376824 00373404  39 60 00 00 */	li r11, 0
/* 80376828 00373408  38 A0 00 0B */	li r5, 0xb
/* 8037682C 0037340C  93 7F 14 58 */	stw r27, 0x1458(r31)
/* 80376830 00373410  38 00 00 02 */	li r0, 2
/* 80376834 00373414  93 9F 14 B8 */	stw r28, 0x14b8(r31)
/* 80376838 00373418  93 BF 15 18 */	stw r29, 0x1518(r31)
.L_8037683C:
/* 8037683C 0037341C  7C A9 03 A6 */	mtctr r5
/* 80376840 00373420  38 E9 00 58 */	addi r7, r9, 0x58
/* 80376844 00373424  38 DF 13 F8 */	addi r6, r31, 0x13f8
.L_80376848:
/* 80376848 00373428  84 86 00 08 */	lwzu r4, 8(r6)
/* 8037684C 0037342C  80 66 00 04 */	lwz r3, 4(r6)
/* 80376850 00373430  94 87 00 08 */	stwu r4, 8(r7)
/* 80376854 00373434  90 67 00 04 */	stw r3, 4(r7)
/* 80376858 00373438  42 00 FF F0 */	bdnz .L_80376848
/* 8037685C 0037343C  80 69 00 58 */	lwz r3, 0x58(r9)
/* 80376860 00373440  28 03 00 00 */	cmplwi r3, 0
/* 80376864 00373444  41 82 00 10 */	beq .L_80376874
/* 80376868 00373448  90 09 00 5C */	stw r0, 0x5c(r9)
/* 8037686C 0037344C  39 6B 00 01 */	addi r11, r11, 1
/* 80376870 00373450  48 00 00 08 */	b .L_80376878
.L_80376874:
/* 80376874 00373454  91 09 00 5C */	stw r8, 0x5c(r9)
.L_80376878:
/* 80376878 00373458  39 4A 00 01 */	addi r10, r10, 1
/* 8037687C 0037345C  2C 0A 00 03 */	cmpwi r10, 3
/* 80376880 00373460  39 29 00 60 */	addi r9, r9, 0x60
/* 80376884 00373464  41 80 FF B8 */	blt .L_8037683C
/* 80376888 00373468  91 7F 15 D4 */	stw r11, 0x15d4(r31)
/* 8037688C 0037346C  38 60 00 00 */	li r3, 0
/* 80376890 00373470  38 00 00 0B */	li r0, 0xb
/* 80376894 00373474  90 7F 15 78 */	stw r3, 0x1578(r31)
/* 80376898 00373478  7C 09 03 A6 */	mtctr r0
/* 8037689C 0037347C  38 BF 15 74 */	addi r5, r31, 0x1574
/* 803768A0 00373480  38 9F 13 F8 */	addi r4, r31, 0x13f8
.L_803768A4:
/* 803768A4 00373484  84 64 00 08 */	lwzu r3, 8(r4)
/* 803768A8 00373488  80 04 00 04 */	lwz r0, 4(r4)
/* 803768AC 0037348C  94 65 00 08 */	stwu r3, 8(r5)
/* 803768B0 00373490  90 05 00 04 */	stw r0, 4(r5)
/* 803768B4 00373494  42 00 FF F0 */	bdnz .L_803768A4
/* 803768B8 00373498  3C 60 80 37 */	lis r3, HSD_VIPreRetraceCB@ha
/* 803768BC 0037349C  38 63 59 E4 */	addi r3, r3, HSD_VIPreRetraceCB@l
/* 803768C0 003734A0  4B FD 82 CD */	bl VISetPreRetraceCallback
/* 803768C4 003734A4  3C 60 80 37 */	lis r3, HSD_VIPostRetraceCB@ha
/* 803768C8 003734A8  38 63 5C 34 */	addi r3, r3, HSD_VIPostRetraceCB@l
/* 803768CC 003734AC  4B FD 83 05 */	bl VISetPostRetraceCallback
/* 803768D0 003734B0  3B A0 00 00 */	li r29, 0
/* 803768D4 003734B4  93 BF 15 D8 */	stw r29, 0x15d8(r31)
/* 803768D8 003734B8  3C 60 80 37 */	lis r3, HSD_VIGXDrawDoneCB@ha
/* 803768DC 003734BC  38 63 5E 1C */	addi r3, r3, HSD_VIGXDrawDoneCB@l
/* 803768E0 003734C0  93 BF 15 DC */	stw r29, 0x15dc(r31)
/* 803768E4 003734C4  93 BF 15 E0 */	stw r29, 0x15e0(r31)
/* 803768E8 003734C8  93 BF 15 E4 */	stw r29, 0x15e4(r31)
/* 803768EC 003734CC  4B FC 66 1D */	bl GXSetDrawDoneCallback
/* 803768F0 003734D0  93 BF 15 E8 */	stw r29, 0x15e8(r31)
/* 803768F4 003734D4  4B FD 9A 39 */	bl VIGetTvFormat
/* 803768F8 003734D8  28 03 00 00 */	cmplwi r3, 0
/* 803768FC 003734DC  40 82 00 0C */	bne .L_80376908
/* 80376900 003734E0  38 00 00 3C */	li r0, 0x3c
/* 80376904 003734E4  48 00 00 08 */	b .L_8037690C
.L_80376908:
/* 80376908 003734E8  38 00 00 32 */	li r0, 0x32
.L_8037690C:
/* 8037690C 003734EC  90 1F 15 EC */	stw r0, 0x15ec(r31)
/* 80376910 003734F0  38 00 00 00 */	li r0, 0
/* 80376914 003734F4  38 7F 14 00 */	addi r3, r31, 0x1400
/* 80376918 003734F8  90 1F 15 F0 */	stw r0, 0x15f0(r31)
/* 8037691C 003734FC  4B FD 8E C1 */	bl VIConfigure
/* 80376920 00373500  80 7F 14 3C */	lwz r3, 0x143c(r31)
/* 80376924 00373504  4B FD 97 DD */	bl VISetBlack
/* 80376928 00373508  4B FD 96 51 */	bl VIFlush
/* 8037692C 0037350C  80 1E 00 5C */	lwz r0, 0x5c(r30)
/* 80376930 00373510  2C 00 00 02 */	cmpwi r0, 2
/* 80376934 00373514  40 82 00 0C */	bne .L_80376940
/* 80376938 00373518  38 00 00 00 */	li r0, 0
/* 8037693C 0037351C  48 00 00 34 */	b .L_80376970
.L_80376940:
/* 80376940 00373520  38 7E 00 60 */	addi r3, r30, 0x60
/* 80376944 00373524  80 1E 00 BC */	lwz r0, 0xbc(r30)
/* 80376948 00373528  2C 00 00 02 */	cmpwi r0, 2
/* 8037694C 0037352C  40 82 00 0C */	bne .L_80376958
/* 80376950 00373530  38 00 00 01 */	li r0, 1
/* 80376954 00373534  48 00 00 1C */	b .L_80376970
.L_80376958:
/* 80376958 00373538  80 03 00 BC */	lwz r0, 0xbc(r3)
/* 8037695C 0037353C  2C 00 00 02 */	cmpwi r0, 2
/* 80376960 00373540  40 82 00 0C */	bne .L_8037696C
/* 80376964 00373544  38 00 00 02 */	li r0, 2
/* 80376968 00373548  48 00 00 08 */	b .L_80376970
.L_8037696C:
/* 8037696C 0037354C  38 00 FF FF */	li r0, -1
.L_80376970:
/* 80376970 00373550  1C 00 00 60 */	mulli r0, r0, 0x60
/* 80376974 00373554  7C 7F 02 14 */	add r3, r31, r0
/* 80376978 00373558  80 83 14 58 */	lwz r4, 0x1458(r3)
/* 8037697C 0037355C  38 7F 14 00 */	addi r3, r31, 0x1400
/* 80376980 00373560  38 A0 00 00 */	li r5, 0
/* 80376984 00373564  4B FF F5 F1 */	bl HSD_VICopyEFB2XFBPtr
/* 80376988 00373568  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8037698C 0037356C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80376990 00373570  38 21 00 38 */	addi r1, r1, 0x38
/* 80376994 00373574  7C 08 03 A6 */	mtlr r0
/* 80376998 00373578  4E 80 00 20 */	blr


.section .data
    .balign 8
.global HSD_Video_80406CEC
HSD_Video_80406CEC:
    .asciz "unexpected type of render pass.\n"
    .balign 4
.global HSD_Video_80406D10
HSD_Video_80406D10:
    .asciz "_p->xfb[idx].status == HSD_VI_XFB_DRAWING"
    .balign 4
.global HSD_Video_80406D3C
HSD_Video_80406D3C:
    .asciz "_p->xfb[idx].status == HSD_VI_XFB_WAITDONE"
    .balign 4


.section .bss, "wa"
    .balign 8
.global garbage
garbage:
    .skip 0x1400
.global HSD_VIData
HSD_VIData:
    .skip 0x1F8


.section .sdata
    .balign 8
.global HSD_Video_804D5E88
HSD_Video_804D5E88:
    .asciz "video.c"
    .balign 4


.section .sbss
    .balign 8
.global vr_count
vr_count:
    .skip 0x4
.global renew_count
renew_count:
    .skip 0x4


.section .sdata2
    .balign 8
.global HSD_Video_804DE5A0
HSD_Video_804DE5A0:
    .4byte 0x3F800000
    .4byte 0x00000000
.global HSD_Video_804DE5A8
HSD_Video_804DE5A8:
    .4byte 0x43300000
    .4byte 0x00000000
