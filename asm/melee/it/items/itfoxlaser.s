.include "macros.inc"

.section .text

.global it_8029C4D4
it_8029C4D4:
/* 8029C4D4 002990B4  7C 08 02 A6 */	mflr r0
/* 8029C4D8 002990B8  38 C0 00 00 */	li r6, 0
/* 8029C4DC 002990BC  90 01 00 04 */	stw r0, 4(r1)
/* 8029C4E0 002990C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029C4E4 002990C4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8029C4E8 002990C8  38 85 0D E0 */	addi r4, r5, 0xde0
/* 8029C4EC 002990CC  38 A5 00 4C */	addi r5, r5, 0x4c
/* 8029C4F0 002990D0  4B FD 24 B5 */	bl it_8026E9A4
/* 8029C4F4 002990D4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029C4F8 002990D8  38 21 00 08 */	addi r1, r1, 8
/* 8029C4FC 002990DC  7C 08 03 A6 */	mtlr r0
/* 8029C500 002990E0  4E 80 00 20 */	blr

.global it_8029C504
it_8029C504:
/* 8029C504 002990E4  7C 08 02 A6 */	mflr r0
/* 8029C508 002990E8  90 01 00 04 */	stw r0, 4(r1)
/* 8029C50C 002990EC  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 8029C510 002990F0  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 8029C514 002990F4  FF E0 10 90 */	fmr f31, f2
/* 8029C518 002990F8  DB C1 00 80 */	stfd f30, 0x80(r1)
/* 8029C51C 002990FC  FF C0 08 90 */	fmr f30, f1
/* 8029C520 00299100  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 8029C524 00299104  93 C1 00 78 */	stw r30, 0x78(r1)
/* 8029C528 00299108  93 A1 00 74 */	stw r29, 0x74(r1)
/* 8029C52C 0029910C  3B A5 00 00 */	addi r29, r5, 0
/* 8029C530 00299110  93 81 00 70 */	stw r28, 0x70(r1)
/* 8029C534 00299114  3B 83 00 00 */	addi r28, r3, 0
/* 8029C538 00299118  C8 22 D3 10 */	lfd f1, it_804DCCF0@sda21(r2)
/* 8029C53C 0029911C  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029C540 00299120  48 00 00 0C */	b .L_8029C54C
.L_8029C544:
/* 8029C544 00299124  FF DE 08 2A */	fadd f30, f30, f1
/* 8029C548 00299128  FF C0 F0 18 */	frsp f30, f30
.L_8029C54C:
/* 8029C54C 0029912C  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8029C550 00299130  41 80 FF F4 */	blt .L_8029C544
/* 8029C554 00299134  C8 02 D3 10 */	lfd f0, it_804DCCF0@sda21(r2)
/* 8029C558 00299138  48 00 00 0C */	b .L_8029C564
.L_8029C55C:
/* 8029C55C 0029913C  FF DE 00 28 */	fsub f30, f30, f0
/* 8029C560 00299140  FF C0 F0 18 */	frsp f30, f30
.L_8029C564:
/* 8029C564 00299144  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8029C568 00299148  41 81 FF F4 */	bgt .L_8029C55C
/* 8029C56C 0029914C  90 C1 00 2C */	stw r6, 0x2c(r1)
/* 8029C570 00299150  38 C1 00 38 */	addi r6, r1, 0x38
/* 8029C574 00299154  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029C578 00299158  7F 83 E3 78 */	mr r3, r28
/* 8029C57C 0029915C  80 A4 00 00 */	lwz r5, 0(r4)
/* 8029C580 00299160  80 04 00 04 */	lwz r0, 4(r4)
/* 8029C584 00299164  90 A1 00 44 */	stw r5, 0x44(r1)
/* 8029C588 00299168  90 01 00 48 */	stw r0, 0x48(r1)
/* 8029C58C 0029916C  80 04 00 08 */	lwz r0, 8(r4)
/* 8029C590 00299170  7C C4 33 78 */	mr r4, r6
/* 8029C594 00299174  90 01 00 4C */	stw r0, 0x4c(r1)
/* 8029C598 00299178  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8029C59C 0029917C  4B FC F5 CD */	bl it_8026BB68
/* 8029C5A0 00299180  C8 02 D3 20 */	lfd f0, it_804DCD00@sda21(r2)
/* 8029C5A4 00299184  38 00 00 01 */	li r0, 1
/* 8029C5A8 00299188  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8029C5AC 0029918C  41 80 00 14 */	blt .L_8029C5C0
/* 8029C5B0 00299190  C8 02 D3 28 */	lfd f0, it_804DCD08@sda21(r2)
/* 8029C5B4 00299194  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8029C5B8 00299198  41 81 00 08 */	bgt .L_8029C5C0
/* 8029C5BC 0029919C  38 00 00 00 */	li r0, 0
.L_8029C5C0:
/* 8029C5C0 002991A0  2C 00 00 00 */	cmpwi r0, 0
/* 8029C5C4 002991A4  41 82 00 0C */	beq .L_8029C5D0
/* 8029C5C8 002991A8  C0 02 D3 30 */	lfs f0, it_804DCD10@sda21(r2)
/* 8029C5CC 002991AC  48 00 00 08 */	b .L_8029C5D4
.L_8029C5D0:
/* 8029C5D0 002991B0  C0 02 D3 34 */	lfs f0, it_804DCD14@sda21(r2)
.L_8029C5D4:
/* 8029C5D4 002991B4  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 8029C5D8 002991B8  38 A0 00 00 */	li r5, 0
/* 8029C5DC 002991BC  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029C5E0 002991C0  38 80 00 01 */	li r4, 1
/* 8029C5E4 002991C4  B0 A1 00 60 */	sth r5, 0x60(r1)
/* 8029C5E8 002991C8  38 61 00 24 */	addi r3, r1, 0x24
/* 8029C5EC 002991CC  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 8029C5F0 002991D0  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 8029C5F4 002991D4  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 8029C5F8 002991D8  93 81 00 24 */	stw r28, 0x24(r1)
/* 8029C5FC 002991DC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8029C600 002991E0  90 01 00 28 */	stw r0, 0x28(r1)
/* 8029C604 002991E4  88 01 00 68 */	lbz r0, 0x68(r1)
/* 8029C608 002991E8  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8029C60C 002991EC  98 01 00 68 */	stb r0, 0x68(r1)
/* 8029C610 002991F0  90 A1 00 64 */	stw r5, 0x64(r1)
/* 8029C614 002991F4  4B FC C5 05 */	bl Item_80268B18
/* 8029C618 002991F8  7C 7F 1B 79 */	or. r31, r3, r3
/* 8029C61C 002991FC  41 82 00 60 */	beq .L_8029C67C
/* 8029C620 00299200  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 8029C624 00299204  38 7F 00 00 */	addi r3, r31, 0
/* 8029C628 00299208  38 9D 00 00 */	addi r4, r29, 0
/* 8029C62C 0029920C  80 DE 00 C4 */	lwz r6, 0xc4(r30)
/* 8029C630 00299210  38 A0 00 02 */	li r5, 2
/* 8029C634 00299214  83 A6 00 04 */	lwz r29, 4(r6)
/* 8029C638 00299218  4B FC C8 25 */	bl Item_80268E5C
/* 8029C63C 0029921C  7F E3 FB 78 */	mr r3, r31
/* 8029C640 00299220  C0 3D 00 00 */	lfs f1, 0(r29)
/* 8029C644 00299224  4B FD 8B 15 */	bl it_80275158
/* 8029C648 00299228  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029C64C 0029922C  38 7F 00 00 */	addi r3, r31, 0
/* 8029C650 00299230  38 9C 00 00 */	addi r4, r28, 0
/* 8029C654 00299234  D0 1E 0D D4 */	stfs f0, 0xdd4(r30)
/* 8029C658 00299238  D3 DE 0D D8 */	stfs f30, 0xdd8(r30)
/* 8029C65C 0029923C  D3 FE 0D DC */	stfs f31, 0xddc(r30)
/* 8029C660 00299240  80 A1 00 38 */	lwz r5, 0x38(r1)
/* 8029C664 00299244  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8029C668 00299248  90 BE 0D E0 */	stw r5, 0xde0(r30)
/* 8029C66C 0029924C  90 1E 0D E4 */	stw r0, 0xde4(r30)
/* 8029C670 00299250  80 01 00 40 */	lwz r0, 0x40(r1)
/* 8029C674 00299254  90 1E 0D E8 */	stw r0, 0xde8(r30)
/* 8029C678 00299258  4B F8 97 61 */	bl db_80225DD8
.L_8029C67C:
/* 8029C67C 0029925C  80 01 00 94 */	lwz r0, 0x94(r1)
/* 8029C680 00299260  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 8029C684 00299264  CB C1 00 80 */	lfd f30, 0x80(r1)
/* 8029C688 00299268  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 8029C68C 0029926C  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 8029C690 00299270  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 8029C694 00299274  83 81 00 70 */	lwz r28, 0x70(r1)
/* 8029C698 00299278  38 21 00 90 */	addi r1, r1, 0x90
/* 8029C69C 0029927C  7C 08 03 A6 */	mtlr r0
/* 8029C6A0 00299280  4E 80 00 20 */	blr

.global it_8029C6A4
it_8029C6A4:
/* 8029C6A4 00299284  7C 08 02 A6 */	mflr r0
/* 8029C6A8 00299288  38 C5 00 00 */	addi r6, r5, 0
/* 8029C6AC 0029928C  90 01 00 04 */	stw r0, 4(r1)
/* 8029C6B0 00299290  38 A0 00 00 */	li r5, 0
/* 8029C6B4 00299294  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029C6B8 00299298  4B FF FE 4D */	bl it_8029C504
/* 8029C6BC 0029929C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029C6C0 002992A0  38 21 00 08 */	addi r1, r1, 8
/* 8029C6C4 002992A4  7C 08 03 A6 */	mtlr r0
/* 8029C6C8 002992A8  4E 80 00 20 */	blr

.global it_8029C6CC
it_8029C6CC:
/* 8029C6CC 002992AC  7C 08 02 A6 */	mflr r0
/* 8029C6D0 002992B0  38 C5 00 00 */	addi r6, r5, 0
/* 8029C6D4 002992B4  90 01 00 04 */	stw r0, 4(r1)
/* 8029C6D8 002992B8  38 A0 00 01 */	li r5, 1
/* 8029C6DC 002992BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029C6E0 002992C0  4B FF FE 25 */	bl it_8029C504
/* 8029C6E4 002992C4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029C6E8 002992C8  38 21 00 08 */	addi r1, r1, 8
/* 8029C6EC 002992CC  7C 08 03 A6 */	mtlr r0
/* 8029C6F0 002992D0  4E 80 00 20 */	blr

.global it_8029C6F4
it_8029C6F4:
/* 8029C6F4 002992D4  7C 08 02 A6 */	mflr r0
/* 8029C6F8 002992D8  90 01 00 04 */	stw r0, 4(r1)
/* 8029C6FC 002992DC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8029C700 002992E0  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8029C704 002992E4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8029C708 002992E8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8029C70C 002992EC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8029C710 002992F0  93 81 00 18 */	stw r28, 0x18(r1)
/* 8029C714 002992F4  7C 7C 1B 78 */	mr r28, r3
/* 8029C718 002992F8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029C71C 002992FC  83 A3 00 28 */	lwz r29, 0x28(r3)
/* 8029C720 00299300  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 8029C724 00299304  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029C728 00299308  83 C3 00 04 */	lwz r30, 4(r3)
/* 8029C72C 0029930C  48 08 9B 15 */	bl cosf
/* 8029C730 00299310  C0 1F 0D DC */	lfs f0, 0xddc(r31)
/* 8029C734 00299314  EC 00 00 72 */	fmuls f0, f0, f1
/* 8029C738 00299318  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 8029C73C 0029931C  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029C740 00299320  48 08 9C 95 */	bl sinf
/* 8029C744 00299324  C0 1F 0D DC */	lfs f0, 0xddc(r31)
/* 8029C748 00299328  EC 00 00 72 */	fmuls f0, f0, f1
/* 8029C74C 0029932C  D0 1F 00 44 */	stfs f0, 0x44(r31)
/* 8029C750 00299330  C0 22 D3 18 */	lfs f1, it_804DCCF8@sda21(r2)
/* 8029C754 00299334  D0 3F 00 48 */	stfs f1, 0x48(r31)
/* 8029C758 00299338  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 8029C75C 0029933C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8029C760 00299340  40 81 00 0C */	ble .L_8029C76C
/* 8029C764 00299344  C0 02 D3 30 */	lfs f0, it_804DCD10@sda21(r2)
/* 8029C768 00299348  48 00 00 08 */	b .L_8029C770
.L_8029C76C:
/* 8029C76C 0029934C  C0 02 D3 34 */	lfs f0, it_804DCD14@sda21(r2)
.L_8029C770:
/* 8029C770 00299350  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 8029C774 00299354  28 1D 00 00 */	cmplwi r29, 0
/* 8029C778 00299358  C8 22 D3 20 */	lfd f1, it_804DCD00@sda21(r2)
/* 8029C77C 0029935C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029C780 00299360  FF E1 00 32 */	fmul f31, f1, f0
/* 8029C784 00299364  FF E0 F8 18 */	frsp f31, f31
/* 8029C788 00299368  40 82 00 14 */	bne .L_8029C79C
/* 8029C78C 0029936C  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C790 00299370  38 80 02 94 */	li r4, 0x294
/* 8029C794 00299374  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C798 00299378  48 0E BA 89 */	bl __assert
.L_8029C79C:
/* 8029C79C 0029937C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029C7A0 00299380  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8029C7A4 00299384  41 82 00 18 */	beq .L_8029C7BC
/* 8029C7A8 00299388  3C 60 80 3F */	lis r3, it_803F67F0@ha
/* 8029C7AC 0029938C  38 A3 67 F0 */	addi r5, r3, it_803F67F0@l
/* 8029C7B0 00299390  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C7B4 00299394  38 80 02 95 */	li r4, 0x295
/* 8029C7B8 00299398  48 0E BA 69 */	bl __assert
.L_8029C7BC:
/* 8029C7BC 0029939C  D3 FD 00 20 */	stfs f31, 0x20(r29)
/* 8029C7C0 002993A0  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029C7C4 002993A4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029C7C8 002993A8  40 82 00 4C */	bne .L_8029C814
/* 8029C7CC 002993AC  28 1D 00 00 */	cmplwi r29, 0
/* 8029C7D0 002993B0  41 82 00 44 */	beq .L_8029C814
/* 8029C7D4 002993B4  40 82 00 14 */	bne .L_8029C7E8
/* 8029C7D8 002993B8  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C7DC 002993BC  38 80 02 34 */	li r4, 0x234
/* 8029C7E0 002993C0  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C7E4 002993C4  48 0E BA 3D */	bl __assert
.L_8029C7E8:
/* 8029C7E8 002993C8  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8029C7EC 002993CC  38 60 00 00 */	li r3, 0
/* 8029C7F0 002993D0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029C7F4 002993D4  40 82 00 10 */	bne .L_8029C804
/* 8029C7F8 002993D8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029C7FC 002993DC  41 82 00 08 */	beq .L_8029C804
/* 8029C800 002993E0  38 60 00 01 */	li r3, 1
.L_8029C804:
/* 8029C804 002993E4  2C 03 00 00 */	cmpwi r3, 0
/* 8029C808 002993E8  40 82 00 0C */	bne .L_8029C814
/* 8029C80C 002993EC  7F A3 EB 78 */	mr r3, r29
/* 8029C810 002993F0  48 0D 6A D9 */	bl HSD_JObjSetMtxDirtySub
.L_8029C814:
/* 8029C814 002993F4  C0 22 D3 30 */	lfs f1, it_804DCD10@sda21(r2)
/* 8029C818 002993F8  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029C81C 002993FC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8029C820 00299400  40 82 00 10 */	bne .L_8029C830
/* 8029C824 00299404  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 8029C828 00299408  FC 40 00 50 */	fneg f2, f0
/* 8029C82C 0029940C  48 00 00 08 */	b .L_8029C834
.L_8029C830:
/* 8029C830 00299410  C0 5F 00 40 */	lfs f2, 0x40(r31)
.L_8029C834:
/* 8029C834 00299414  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 8029C838 00299418  4B D8 63 F9 */	bl atan2f
/* 8029C83C 0029941C  C8 02 D3 38 */	lfd f0, it_804DCD18@sda21(r2)
/* 8029C840 00299420  28 1D 00 00 */	cmplwi r29, 0
/* 8029C844 00299424  FF E0 08 2A */	fadd f31, f0, f1
/* 8029C848 00299428  FF E0 F8 18 */	frsp f31, f31
/* 8029C84C 0029942C  40 82 00 14 */	bne .L_8029C860
/* 8029C850 00299430  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C854 00299434  38 80 02 7F */	li r4, 0x27f
/* 8029C858 00299438  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C85C 0029943C  48 0E B9 C5 */	bl __assert
.L_8029C860:
/* 8029C860 00299440  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029C864 00299444  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8029C868 00299448  41 82 00 18 */	beq .L_8029C880
/* 8029C86C 0029944C  3C 60 80 3F */	lis r3, it_803F67F0@ha
/* 8029C870 00299450  38 A3 67 F0 */	addi r5, r3, it_803F67F0@l
/* 8029C874 00299454  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C878 00299458  38 80 02 80 */	li r4, 0x280
/* 8029C87C 0029945C  48 0E B9 A5 */	bl __assert
.L_8029C880:
/* 8029C880 00299460  D3 FD 00 1C */	stfs f31, 0x1c(r29)
/* 8029C884 00299464  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029C888 00299468  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029C88C 0029946C  40 82 00 4C */	bne .L_8029C8D8
/* 8029C890 00299470  28 1D 00 00 */	cmplwi r29, 0
/* 8029C894 00299474  41 82 00 44 */	beq .L_8029C8D8
/* 8029C898 00299478  40 82 00 14 */	bne .L_8029C8AC
/* 8029C89C 0029947C  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C8A0 00299480  38 80 02 34 */	li r4, 0x234
/* 8029C8A4 00299484  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C8A8 00299488  48 0E B9 79 */	bl __assert
.L_8029C8AC:
/* 8029C8AC 0029948C  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8029C8B0 00299490  38 60 00 00 */	li r3, 0
/* 8029C8B4 00299494  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029C8B8 00299498  40 82 00 10 */	bne .L_8029C8C8
/* 8029C8BC 0029949C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029C8C0 002994A0  41 82 00 08 */	beq .L_8029C8C8
/* 8029C8C4 002994A4  38 60 00 01 */	li r3, 1
.L_8029C8C8:
/* 8029C8C8 002994A8  2C 03 00 00 */	cmpwi r3, 0
/* 8029C8CC 002994AC  40 82 00 0C */	bne .L_8029C8D8
/* 8029C8D0 002994B0  7F A3 EB 78 */	mr r3, r29
/* 8029C8D4 002994B4  48 0D 6A 15 */	bl HSD_JObjSetMtxDirtySub
.L_8029C8D8:
/* 8029C8D8 002994B8  C0 5F 0D DC */	lfs f2, 0xddc(r31)
/* 8029C8DC 002994BC  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029C8E0 002994C0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8029C8E4 002994C4  40 80 00 08 */	bge .L_8029C8EC
/* 8029C8E8 002994C8  FC 40 10 50 */	fneg f2, f2
.L_8029C8EC:
/* 8029C8EC 002994CC  C0 02 D3 40 */	lfs f0, it_804DCD20@sda21(r2)
/* 8029C8F0 002994D0  C0 3F 0D D4 */	lfs f1, 0xdd4(r31)
/* 8029C8F4 002994D4  EC 02 00 24 */	fdivs f0, f2, f0
/* 8029C8F8 002994D8  EC 01 00 2A */	fadds f0, f1, f0
/* 8029C8FC 002994DC  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
/* 8029C900 002994E0  C0 1F 0D D4 */	lfs f0, 0xdd4(r31)
/* 8029C904 002994E4  C0 3E 00 04 */	lfs f1, 4(r30)
/* 8029C908 002994E8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8029C90C 002994EC  40 81 00 08 */	ble .L_8029C914
/* 8029C910 002994F0  D0 3F 0D D4 */	stfs f1, 0xdd4(r31)
.L_8029C914:
/* 8029C914 002994F4  C0 3F 0D D4 */	lfs f1, 0xdd4(r31)
/* 8029C918 002994F8  C0 02 D3 44 */	lfs f0, it_804DCD24@sda21(r2)
/* 8029C91C 002994FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8029C920 00299500  40 80 00 0C */	bge .L_8029C92C
/* 8029C924 00299504  C0 02 D3 48 */	lfs f0, it_804DCD28@sda21(r2)
/* 8029C928 00299508  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
.L_8029C92C:
/* 8029C92C 0029950C  28 1D 00 00 */	cmplwi r29, 0
/* 8029C930 00299510  C3 FF 0D D4 */	lfs f31, 0xdd4(r31)
/* 8029C934 00299514  40 82 00 14 */	bne .L_8029C948
/* 8029C938 00299518  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C93C 0029951C  38 80 03 26 */	li r4, 0x326
/* 8029C940 00299520  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C944 00299524  48 0E B8 DD */	bl __assert
.L_8029C948:
/* 8029C948 00299528  D3 FD 00 34 */	stfs f31, 0x34(r29)
/* 8029C94C 0029952C  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 8029C950 00299530  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029C954 00299534  40 82 00 4C */	bne .L_8029C9A0
/* 8029C958 00299538  28 1D 00 00 */	cmplwi r29, 0
/* 8029C95C 0029953C  41 82 00 44 */	beq .L_8029C9A0
/* 8029C960 00299540  40 82 00 14 */	bne .L_8029C974
/* 8029C964 00299544  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029C968 00299548  38 80 02 34 */	li r4, 0x234
/* 8029C96C 0029954C  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029C970 00299550  48 0E B8 B1 */	bl __assert
.L_8029C974:
/* 8029C974 00299554  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 8029C978 00299558  38 60 00 00 */	li r3, 0
/* 8029C97C 0029955C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029C980 00299560  40 82 00 10 */	bne .L_8029C990
/* 8029C984 00299564  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029C988 00299568  41 82 00 08 */	beq .L_8029C990
/* 8029C98C 0029956C  38 60 00 01 */	li r3, 1
.L_8029C990:
/* 8029C990 00299570  2C 03 00 00 */	cmpwi r3, 0
/* 8029C994 00299574  40 82 00 0C */	bne .L_8029C9A0
/* 8029C998 00299578  7F A3 EB 78 */	mr r3, r29
/* 8029C99C 0029957C  48 0D 69 4D */	bl HSD_JObjSetMtxDirtySub
.L_8029C9A0:
/* 8029C9A0 00299580  7F 83 E3 78 */	mr r3, r28
/* 8029C9A4 00299584  4B FD 67 8D */	bl it_80273130
/* 8029C9A8 00299588  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8029C9AC 0029958C  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8029C9B0 00299590  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8029C9B4 00299594  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8029C9B8 00299598  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8029C9BC 0029959C  83 81 00 18 */	lwz r28, 0x18(r1)
/* 8029C9C0 002995A0  38 21 00 30 */	addi r1, r1, 0x30
/* 8029C9C4 002995A4  7C 08 03 A6 */	mtlr r0
/* 8029C9C8 002995A8  4E 80 00 20 */	blr

.global it_8029C9CC
it_8029C9CC:
/* 8029C9CC 002995AC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8029C9D0 002995B0  80 64 00 4C */	lwz r3, 0x4c(r4)
/* 8029C9D4 002995B4  80 04 00 50 */	lwz r0, 0x50(r4)
/* 8029C9D8 002995B8  90 64 0D E0 */	stw r3, 0xde0(r4)
/* 8029C9DC 002995BC  90 04 0D E4 */	stw r0, 0xde4(r4)
/* 8029C9E0 002995C0  80 04 00 54 */	lwz r0, 0x54(r4)
/* 8029C9E4 002995C4  90 04 0D E8 */	stw r0, 0xde8(r4)
/* 8029C9E8 002995C8  4E 80 00 20 */	blr

.global it_8029C9EC
it_8029C9EC:
/* 8029C9EC 002995CC  7C 08 02 A6 */	mflr r0
/* 8029C9F0 002995D0  38 C0 00 00 */	li r6, 0
/* 8029C9F4 002995D4  90 01 00 04 */	stw r0, 4(r1)
/* 8029C9F8 002995D8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8029C9FC 002995DC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8029CA00 002995E0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8029CA04 002995E4  7C 7E 1B 78 */	mr r30, r3
/* 8029CA08 002995E8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029CA0C 002995EC  80 FF 00 4C */	lwz r7, 0x4c(r31)
/* 8029CA10 002995F0  38 9F 0D E0 */	addi r4, r31, 0xde0
/* 8029CA14 002995F4  80 1F 00 50 */	lwz r0, 0x50(r31)
/* 8029CA18 002995F8  38 BF 00 4C */	addi r5, r31, 0x4c
/* 8029CA1C 002995FC  90 E1 00 18 */	stw r7, 0x18(r1)
/* 8029CA20 00299600  90 01 00 1C */	stw r0, 0x1c(r1)
/* 8029CA24 00299604  80 1F 00 54 */	lwz r0, 0x54(r31)
/* 8029CA28 00299608  90 01 00 20 */	stw r0, 0x20(r1)
/* 8029CA2C 0029960C  4B FD 1F 79 */	bl it_8026E9A4
/* 8029CA30 00299610  2C 03 00 00 */	cmpwi r3, 0
/* 8029CA34 00299614  41 82 00 28 */	beq .L_8029CA5C
/* 8029CA38 00299618  7F C3 F3 78 */	mr r3, r30
/* 8029CA3C 0029961C  C0 22 D3 30 */	lfs f1, it_804DCD10@sda21(r2)
/* 8029CA40 00299620  4B FD 87 19 */	bl it_80275158
/* 8029CA44 00299624  80 61 00 18 */	lwz r3, 0x18(r1)
/* 8029CA48 00299628  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8029CA4C 0029962C  90 7F 00 4C */	stw r3, 0x4c(r31)
/* 8029CA50 00299630  90 1F 00 50 */	stw r0, 0x50(r31)
/* 8029CA54 00299634  80 01 00 20 */	lwz r0, 0x20(r1)
/* 8029CA58 00299638  90 1F 00 54 */	stw r0, 0x54(r31)
.L_8029CA5C:
/* 8029CA5C 0029963C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8029CA60 00299640  38 60 00 00 */	li r3, 0
/* 8029CA64 00299644  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8029CA68 00299648  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8029CA6C 0029964C  38 21 00 30 */	addi r1, r1, 0x30
/* 8029CA70 00299650  7C 08 03 A6 */	mtlr r0
/* 8029CA74 00299654  4E 80 00 20 */	blr

.global it_8029CA78
it_8029CA78:
/* 8029CA78 00299658  38 60 00 01 */	li r3, 1
/* 8029CA7C 0029965C  4E 80 00 20 */	blr

.global it_8029CA80
it_8029CA80:
/* 8029CA80 00299660  7C 08 02 A6 */	mflr r0
/* 8029CA84 00299664  90 01 00 04 */	stw r0, 4(r1)
/* 8029CA88 00299668  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8029CA8C 0029966C  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8029CA90 00299670  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8029CA94 00299674  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8029CA98 00299678  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029CA9C 0029967C  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 8029CAA0 00299680  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029CAA4 00299684  C0 3F 0C 68 */	lfs f1, 0xc68(r31)
/* 8029CAA8 00299688  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8029CAAC 0029968C  41 82 00 A8 */	beq .L_8029CB54
/* 8029CAB0 00299690  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 8029CAB4 00299694  28 1E 00 00 */	cmplwi r30, 0
/* 8029CAB8 00299698  C8 22 D3 20 */	lfd f1, it_804DCD00@sda21(r2)
/* 8029CABC 0029969C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8029CAC0 002996A0  FF E1 00 32 */	fmul f31, f1, f0
/* 8029CAC4 002996A4  FF E0 F8 18 */	frsp f31, f31
/* 8029CAC8 002996A8  40 82 00 14 */	bne .L_8029CADC
/* 8029CACC 002996AC  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029CAD0 002996B0  38 80 02 94 */	li r4, 0x294
/* 8029CAD4 002996B4  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029CAD8 002996B8  48 0E B7 49 */	bl __assert
.L_8029CADC:
/* 8029CADC 002996BC  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8029CAE0 002996C0  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 8029CAE4 002996C4  41 82 00 18 */	beq .L_8029CAFC
/* 8029CAE8 002996C8  3C 60 80 3F */	lis r3, it_803F67F0@ha
/* 8029CAEC 002996CC  38 A3 67 F0 */	addi r5, r3, it_803F67F0@l
/* 8029CAF0 002996D0  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029CAF4 002996D4  38 80 02 95 */	li r4, 0x295
/* 8029CAF8 002996D8  48 0E B7 29 */	bl __assert
.L_8029CAFC:
/* 8029CAFC 002996DC  D3 FE 00 20 */	stfs f31, 0x20(r30)
/* 8029CB00 002996E0  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8029CB04 002996E4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029CB08 002996E8  40 82 00 4C */	bne .L_8029CB54
/* 8029CB0C 002996EC  28 1E 00 00 */	cmplwi r30, 0
/* 8029CB10 002996F0  41 82 00 44 */	beq .L_8029CB54
/* 8029CB14 002996F4  40 82 00 14 */	bne .L_8029CB28
/* 8029CB18 002996F8  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029CB1C 002996FC  38 80 02 34 */	li r4, 0x234
/* 8029CB20 00299700  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029CB24 00299704  48 0E B6 FD */	bl __assert
.L_8029CB28:
/* 8029CB28 00299708  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8029CB2C 0029970C  38 60 00 00 */	li r3, 0
/* 8029CB30 00299710  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029CB34 00299714  40 82 00 10 */	bne .L_8029CB44
/* 8029CB38 00299718  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029CB3C 0029971C  41 82 00 08 */	beq .L_8029CB44
/* 8029CB40 00299720  38 60 00 01 */	li r3, 1
.L_8029CB44:
/* 8029CB44 00299724  2C 03 00 00 */	cmpwi r3, 0
/* 8029CB48 00299728  40 82 00 0C */	bne .L_8029CB54
/* 8029CB4C 0029972C  7F C3 F3 78 */	mr r3, r30
/* 8029CB50 00299730  48 0D 67 99 */	bl HSD_JObjSetMtxDirtySub
.L_8029CB54:
/* 8029CB54 00299734  C3 E2 D3 48 */	lfs f31, it_804DCD28@sda21(r2)
/* 8029CB58 00299738  28 1E 00 00 */	cmplwi r30, 0
/* 8029CB5C 0029973C  D3 FF 0D D4 */	stfs f31, 0xdd4(r31)
/* 8029CB60 00299740  40 82 00 14 */	bne .L_8029CB74
/* 8029CB64 00299744  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029CB68 00299748  38 80 03 26 */	li r4, 0x326
/* 8029CB6C 0029974C  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029CB70 00299750  48 0E B6 B1 */	bl __assert
.L_8029CB74:
/* 8029CB74 00299754  D3 FE 00 34 */	stfs f31, 0x34(r30)
/* 8029CB78 00299758  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8029CB7C 0029975C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8029CB80 00299760  40 82 00 4C */	bne .L_8029CBCC
/* 8029CB84 00299764  28 1E 00 00 */	cmplwi r30, 0
/* 8029CB88 00299768  41 82 00 44 */	beq .L_8029CBCC
/* 8029CB8C 0029976C  40 82 00 14 */	bne .L_8029CBA0
/* 8029CB90 00299770  38 6D 9C C0 */	addi r3, r13, it_804D5360@sda21
/* 8029CB94 00299774  38 80 02 34 */	li r4, 0x234
/* 8029CB98 00299778  38 AD 9C C8 */	addi r5, r13, it_804D5368@sda21
/* 8029CB9C 0029977C  48 0E B6 85 */	bl __assert
.L_8029CBA0:
/* 8029CBA0 00299780  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 8029CBA4 00299784  38 60 00 00 */	li r3, 0
/* 8029CBA8 00299788  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8029CBAC 0029978C  40 82 00 10 */	bne .L_8029CBBC
/* 8029CBB0 00299790  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8029CBB4 00299794  41 82 00 08 */	beq .L_8029CBBC
/* 8029CBB8 00299798  38 60 00 01 */	li r3, 1
.L_8029CBBC:
/* 8029CBBC 0029979C  2C 03 00 00 */	cmpwi r3, 0
/* 8029CBC0 002997A0  40 82 00 0C */	bne .L_8029CBCC
/* 8029CBC4 002997A4  7F C3 F3 78 */	mr r3, r30
/* 8029CBC8 002997A8  48 0D 67 21 */	bl HSD_JObjSetMtxDirtySub
.L_8029CBCC:
/* 8029CBCC 002997AC  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029CBD0 002997B0  C8 02 D3 38 */	lfd f0, it_804DCD18@sda21(r2)
/* 8029CBD4 002997B4  FC 01 00 2A */	fadd f0, f1, f0
/* 8029CBD8 002997B8  FC 00 00 18 */	frsp f0, f0
/* 8029CBDC 002997BC  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
/* 8029CBE0 002997C0  C8 42 D3 10 */	lfd f2, it_804DCCF0@sda21(r2)
/* 8029CBE4 002997C4  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029CBE8 002997C8  48 00 00 14 */	b .L_8029CBFC
.L_8029CBEC:
/* 8029CBEC 002997CC  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029CBF0 002997D0  FC 21 10 2A */	fadd f1, f1, f2
/* 8029CBF4 002997D4  FC 20 08 18 */	frsp f1, f1
/* 8029CBF8 002997D8  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
.L_8029CBFC:
/* 8029CBFC 002997DC  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029CC00 002997E0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8029CC04 002997E4  41 80 FF E8 */	blt .L_8029CBEC
/* 8029CC08 002997E8  C8 22 D3 10 */	lfd f1, it_804DCCF0@sda21(r2)
/* 8029CC0C 002997EC  48 00 00 14 */	b .L_8029CC20
.L_8029CC10:
/* 8029CC10 002997F0  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 8029CC14 002997F4  FC 00 08 28 */	fsub f0, f0, f1
/* 8029CC18 002997F8  FC 00 00 18 */	frsp f0, f0
/* 8029CC1C 002997FC  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
.L_8029CC20:
/* 8029CC20 00299800  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 8029CC24 00299804  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8029CC28 00299808  41 81 FF E8 */	bgt .L_8029CC10
/* 8029CC2C 0029980C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8029CC30 00299810  38 60 00 00 */	li r3, 0
/* 8029CC34 00299814  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8029CC38 00299818  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8029CC3C 0029981C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8029CC40 00299820  38 21 00 28 */	addi r1, r1, 0x28
/* 8029CC44 00299824  7C 08 03 A6 */	mtlr r0
/* 8029CC48 00299828  4E 80 00 20 */	blr

.global it_8029CC4C
it_8029CC4C:
/* 8029CC4C 0029982C  38 60 00 01 */	li r3, 1
/* 8029CC50 00299830  4E 80 00 20 */	blr

.global it_8029CC54
it_8029CC54:
/* 8029CC54 00299834  7C 08 02 A6 */	mflr r0
/* 8029CC58 00299838  90 01 00 04 */	stw r0, 4(r1)
/* 8029CC5C 0029983C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8029CC60 00299840  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8029CC64 00299844  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8029CC68 00299848  38 7F 00 40 */	addi r3, r31, 0x40
/* 8029CC6C 0029984C  38 9F 0C 58 */	addi r4, r31, 0xc58
/* 8029CC70 00299850  4B D7 0F FD */	bl lbVector_Mirror
/* 8029CC74 00299854  C0 02 D3 48 */	lfs f0, it_804DCD28@sda21(r2)
/* 8029CC78 00299858  D0 1F 0D D4 */	stfs f0, 0xdd4(r31)
/* 8029CC7C 0029985C  C0 3F 00 44 */	lfs f1, 0x44(r31)
/* 8029CC80 00299860  C0 5F 00 40 */	lfs f2, 0x40(r31)
/* 8029CC84 00299864  4B D8 5F AD */	bl atan2f
/* 8029CC88 00299868  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
/* 8029CC8C 0029986C  C8 42 D3 10 */	lfd f2, it_804DCCF0@sda21(r2)
/* 8029CC90 00299870  C0 02 D3 18 */	lfs f0, it_804DCCF8@sda21(r2)
/* 8029CC94 00299874  48 00 00 14 */	b .L_8029CCA8
.L_8029CC98:
/* 8029CC98 00299878  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029CC9C 0029987C  FC 21 10 2A */	fadd f1, f1, f2
/* 8029CCA0 00299880  FC 20 08 18 */	frsp f1, f1
/* 8029CCA4 00299884  D0 3F 0D D8 */	stfs f1, 0xdd8(r31)
.L_8029CCA8:
/* 8029CCA8 00299888  C0 3F 0D D8 */	lfs f1, 0xdd8(r31)
/* 8029CCAC 0029988C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8029CCB0 00299890  41 80 FF E8 */	blt .L_8029CC98
/* 8029CCB4 00299894  C8 22 D3 10 */	lfd f1, it_804DCCF0@sda21(r2)
/* 8029CCB8 00299898  48 00 00 14 */	b .L_8029CCCC
.L_8029CCBC:
/* 8029CCBC 0029989C  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 8029CCC0 002998A0  FC 00 08 28 */	fsub f0, f0, f1
/* 8029CCC4 002998A4  FC 00 00 18 */	frsp f0, f0
/* 8029CCC8 002998A8  D0 1F 0D D8 */	stfs f0, 0xdd8(r31)
.L_8029CCCC:
/* 8029CCCC 002998AC  C0 1F 0D D8 */	lfs f0, 0xdd8(r31)
/* 8029CCD0 002998B0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8029CCD4 002998B4  41 81 FF E8 */	bgt .L_8029CCBC
/* 8029CCD8 002998B8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8029CCDC 002998BC  38 60 00 00 */	li r3, 0
/* 8029CCE0 002998C0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8029CCE4 002998C4  38 21 00 20 */	addi r1, r1, 0x20
/* 8029CCE8 002998C8  7C 08 03 A6 */	mtlr r0
/* 8029CCEC 002998CC  4E 80 00 20 */	blr

.global it_8029CCF0
it_8029CCF0:
/* 8029CCF0 002998D0  38 60 00 01 */	li r3, 1
/* 8029CCF4 002998D4  4E 80 00 20 */	blr

.global it_8029CCF8
it_8029CCF8:
/* 8029CCF8 002998D8  7C 08 02 A6 */	mflr r0
/* 8029CCFC 002998DC  90 01 00 04 */	stw r0, 4(r1)
/* 8029CD00 002998E0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8029CD04 002998E4  4B FC EB 91 */	bl it_8026B894
/* 8029CD08 002998E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8029CD0C 002998EC  38 21 00 08 */	addi r1, r1, 8
/* 8029CD10 002998F0  7C 08 03 A6 */	mtlr r0
/* 8029CD14 002998F4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F67D0
it_803F67D0:
    .4byte 0
    .4byte it_8029C6F4
    .4byte it_8029C9CC
    .4byte it_8029C9EC
    .4byte 1
    .4byte it_8029C6F4
    .4byte it_8029C9CC
    .4byte it_8029C9EC
.global it_803F67F0
it_803F67F0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"


.section .sdata
    .balign 8
.global it_804D5360
it_804D5360:
    .asciz "jobj.h"
    .balign 4
.global it_804D5368
it_804D5368:
    .asciz "jobj"


.section .sdata2
    .balign 8
.global it_804DCCF0
it_804DCCF0:
    .4byte 0x401921FB
    .4byte 0x54442D18
.global it_804DCCF8
it_804DCCF8:
    .4byte 0x00000000
    .4byte 0x00000000
.global it_804DCD00
it_804DCD00:
    .4byte 0x3FF921FB
    .4byte 0x54442D18
.global it_804DCD08
it_804DCD08:
    .4byte 0x4012D97C
    .4byte 0x7F3321D2
.global it_804DCD10
it_804DCD10:
    .4byte 0x3F800000
.global it_804DCD14
it_804DCD14:
    .4byte 0xBF800000
.global it_804DCD18
it_804DCD18:
    .4byte 0x400921FB
    .4byte 0x54442D18
.global it_804DCD20
it_804DCD20:
    .4byte 0x41340000
.global it_804DCD24
it_804DCD24:
    .4byte 0x3727C5AC
.global it_804DCD28
it_804DCD28:
    .4byte 0x3A83126F
