.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240 

.global func_80219530
func_80219530:
/* 80219530 00216110  4E 80 00 20 */	blr 
.global lbl_80219534
lbl_80219534:
/* 80219534 00216114  7C 08 02 A6 */	mflr r0
/* 80219538 00216118  90 01 00 04 */	stw r0, 4(r1)
/* 8021953C 0021611C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80219540 00216120  4B FA B4 B9 */	bl func_801C49F8
/* 80219544 00216124  3C 80 80 4A */	lis r4, stage_info@ha
/* 80219548 00216128  90 6D B4 20 */	stw r3, lbl_804D6AC0@sda21(r13)
/* 8021954C 0021612C  38 64 E6 C8 */	addi r3, r4, stage_info@l
/* 80219550 00216130  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80219554 00216134  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80219558 00216138  38 60 00 00 */	li r3, 0
/* 8021955C 0021613C  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80219560 00216140  98 05 00 00 */	stb r0, 0(r5)
/* 80219564 00216144  38 80 00 01 */	li r4, 1
/* 80219568 00216148  38 60 00 00 */	li r3, 0
/* 8021956C 0021614C  88 05 00 00 */	lbz r0, 0(r5)
/* 80219570 00216150  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80219574 00216154  98 05 00 00 */	stb r0, 0(r5)
/* 80219578 00216158  48 00 00 55 */	bl func_802195CC
/* 8021957C 0021615C  38 60 00 01 */	li r3, 1
/* 80219580 00216160  48 00 00 4D */	bl func_802195CC
/* 80219584 00216164  4B FA A4 3D */	bl func_801C39C0
/* 80219588 00216168  4B FA A6 2D */	bl func_801C3BB4
/* 8021958C 0021616C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80219590 00216170  38 21 00 08 */	addi r1, r1, 8
/* 80219594 00216174  7C 08 03 A6 */	mtlr r0
/* 80219598 00216178  4E 80 00 20 */	blr 
.global lbl_8021959C
lbl_8021959C:
/* 8021959C 0021617C  4E 80 00 20 */	blr 
.global lbl_802195A0
lbl_802195A0:
/* 802195A0 00216180  7C 08 02 A6 */	mflr r0
/* 802195A4 00216184  38 60 00 00 */	li r3, 0
/* 802195A8 00216188  90 01 00 04 */	stw r0, 4(r1)
/* 802195AC 0021618C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802195B0 00216190  4B FB 18 55 */	bl func_801CAE04
/* 802195B4 00216194  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802195B8 00216198  38 21 00 08 */	addi r1, r1, 8
/* 802195BC 0021619C  7C 08 03 A6 */	mtlr r0
/* 802195C0 002161A0  4E 80 00 20 */	blr 
.global lbl_802195C4
lbl_802195C4:
/* 802195C4 002161A4  38 60 00 00 */	li r3, 0
/* 802195C8 002161A8  4E 80 00 20 */	blr 

.global func_802195CC
func_802195CC:
/* 802195CC 002161AC  7C 08 02 A6 */	mflr r0
/* 802195D0 002161B0  90 01 00 04 */	stw r0, 4(r1)
/* 802195D4 002161B4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802195D8 002161B8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802195DC 002161BC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802195E0 002161C0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802195E4 002161C4  93 81 00 10 */	stw r28, 0x10(r1)
/* 802195E8 002161C8  3B 83 00 00 */	addi r28, r3, 0
/* 802195EC 002161CC  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802195F0 002161D0  3C 60 80 3E */	lis r3, lbl_803E7D00@ha
/* 802195F4 002161D4  3B E3 7D 00 */	addi r31, r3, lbl_803E7D00@l
/* 802195F8 002161D8  38 7C 00 00 */	addi r3, r28, 0
/* 802195FC 002161DC  7F BF 02 14 */	add r29, r31, r0
/* 80219600 002161E0  4B FA 7E D1 */	bl func_801C14D0
/* 80219604 002161E4  7C 7E 1B 79 */	or. r30, r3, r3
/* 80219608 002161E8  41 82 00 70 */	beq lbl_80219678
/* 8021960C 002161EC  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80219610 002161F0  38 00 00 00 */	li r0, 0
/* 80219614 002161F4  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80219618 002161F8  90 1F 00 08 */	stw r0, 8(r31)
/* 8021961C 002161FC  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80219620 00216200  38 7E 00 00 */	addi r3, r30, 0
/* 80219624 00216204  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80219628 00216208  38 A0 00 03 */	li r5, 3
/* 8021962C 0021620C  38 C0 00 00 */	li r6, 0
/* 80219630 00216210  48 17 70 6D */	bl func_8039069C
/* 80219634 00216214  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80219638 00216218  28 00 00 00 */	cmplwi r0, 0
/* 8021963C 0021621C  41 82 00 08 */	beq lbl_80219644
/* 80219640 00216220  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_80219644:
/* 80219644 00216224  81 9D 00 00 */	lwz r12, 0(r29)
/* 80219648 00216228  28 0C 00 00 */	cmplwi r12, 0
/* 8021964C 0021622C  41 82 00 10 */	beq lbl_8021965C
/* 80219650 00216230  7D 88 03 A6 */	mtlr r12
/* 80219654 00216234  38 7E 00 00 */	addi r3, r30, 0
/* 80219658 00216238  4E 80 00 21 */	blrl 
lbl_8021965C:
/* 8021965C 0021623C  80 9D 00 08 */	lwz r4, 8(r29)
/* 80219660 00216240  28 04 00 00 */	cmplwi r4, 0
/* 80219664 00216244  41 82 00 2C */	beq lbl_80219690
/* 80219668 00216248  38 7E 00 00 */	addi r3, r30, 0
/* 8021966C 0021624C  38 A0 00 04 */	li r5, 4
/* 80219670 00216250  48 17 66 E5 */	bl func_8038FD54
/* 80219674 00216254  48 00 00 1C */	b lbl_80219690
lbl_80219678:
/* 80219678 00216258  38 DC 00 00 */	addi r6, r28, 0
/* 8021967C 0021625C  4C C6 31 82 */	crclr 6
/* 80219680 00216260  38 7F 00 68 */	addi r3, r31, 0x68
/* 80219684 00216264  38 9F 00 8C */	addi r4, r31, 0x8c
/* 80219688 00216268  38 A0 00 BB */	li r5, 0xbb
/* 8021968C 0021626C  48 12 C0 1D */	bl OSReport
lbl_80219690:
/* 80219690 00216270  7F C3 F3 78 */	mr r3, r30
/* 80219694 00216274  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80219698 00216278  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8021969C 0021627C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802196A0 00216280  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 802196A4 00216284  83 81 00 10 */	lwz r28, 0x10(r1)
/* 802196A8 00216288  38 21 00 20 */	addi r1, r1, 0x20
/* 802196AC 0021628C  7C 08 03 A6 */	mtlr r0
/* 802196B0 00216290  4E 80 00 20 */	blr 
.global lbl_802196B4
lbl_802196B4:
/* 802196B4 00216294  7C 08 02 A6 */	mflr r0
/* 802196B8 00216298  38 A0 00 00 */	li r5, 0
/* 802196BC 0021629C  90 01 00 04 */	stw r0, 4(r1)
/* 802196C0 002162A0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802196C4 002162A4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802196C8 002162A8  80 84 00 14 */	lwz r4, 0x14(r4)
/* 802196CC 002162AC  4B FA EA 6D */	bl func_801C8138
/* 802196D0 002162B0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802196D4 002162B4  38 21 00 08 */	addi r1, r1, 8
/* 802196D8 002162B8  7C 08 03 A6 */	mtlr r0
/* 802196DC 002162BC  4E 80 00 20 */	blr 
.global lbl_802196E0
lbl_802196E0:
/* 802196E0 002162C0  38 60 00 00 */	li r3, 0
/* 802196E4 002162C4  4E 80 00 20 */	blr 
.global lbl_802196E8
lbl_802196E8:
/* 802196E8 002162C8  4E 80 00 20 */	blr 
.global lbl_802196EC
lbl_802196EC:
/* 802196EC 002162CC  4E 80 00 20 */	blr 
.global lbl_802196F0
lbl_802196F0:
/* 802196F0 002162D0  7C 08 02 A6 */	mflr r0
/* 802196F4 002162D4  38 A0 00 00 */	li r5, 0
/* 802196F8 002162D8  90 01 00 04 */	stw r0, 4(r1)
/* 802196FC 002162DC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80219700 002162E0  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80219704 002162E4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80219708 002162E8  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8021970C 002162EC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80219710 002162F0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80219714 002162F4  4B FA EA 25 */	bl func_801C8138
/* 80219718 002162F8  38 00 00 00 */	li r0, 0
/* 8021971C 002162FC  90 1F 00 08 */	stw r0, 8(r31)
/* 80219720 00216300  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80219724 00216304  48 10 2B A9 */	bl func_8031C2CC
/* 80219728 00216308  38 60 00 03 */	li r3, 3
/* 8021972C 0021630C  48 16 6E 55 */	bl HSD_Randi
/* 80219730 00216310  C0 22 C1 60 */	lfs f1, lbl_804DBB40@sda21(r2)
/* 80219734 00216314  3B C3 00 00 */	addi r30, r3, 0
/* 80219738 00216318  38 60 00 00 */	li r3, 0
/* 8021973C 0021631C  38 80 00 63 */	li r4, 0x63
/* 80219740 00216320  38 A0 00 00 */	li r5, 0
/* 80219744 00216324  48 0E B9 15 */	bl func_80305058
/* 80219748 00216328  57 C0 10 3A */	slwi r0, r30, 2
/* 8021974C 0021632C  3B BE 00 01 */	addi r29, r30, 1
/* 80219750 00216330  7C 9F 02 14 */	add r4, r31, r0
/* 80219754 00216334  2C 1D 00 03 */	cmpwi r29, 3
/* 80219758 00216338  90 64 00 D4 */	stw r3, 0xd4(r4)
/* 8021975C 0021633C  41 80 00 08 */	blt lbl_80219764
/* 80219760 00216340  3B A0 00 00 */	li r29, 0
lbl_80219764:
/* 80219764 00216344  4B FA C0 DD */	bl func_801C5840
/* 80219768 00216348  57 BE 10 3A */	slwi r30, r29, 2
/* 8021976C 0021634C  7C DF F2 14 */	add r6, r31, r30
/* 80219770 00216350  90 66 00 D4 */	stw r3, 0xd4(r6)
/* 80219774 00216354  38 81 00 14 */	addi r4, r1, 0x14
/* 80219778 00216358  38 A0 00 01 */	li r5, 1
/* 8021977C 0021635C  80 66 00 D4 */	lwz r3, 0xd4(r6)
/* 80219780 00216360  38 C0 00 02 */	li r6, 2
/* 80219784 00216364  48 10 2B D1 */	bl func_8031C354
/* 80219788 00216368  2C 03 00 00 */	cmpwi r3, 0
/* 8021978C 0021636C  40 82 00 2C */	bne lbl_802197B8
/* 80219790 00216370  7F DF F2 14 */	add r30, r31, r30
lbl_80219794:
/* 80219794 00216374  C0 22 C1 64 */	lfs f1, lbl_804DBB44@sda21(r2)
/* 80219798 00216378  38 60 00 02 */	li r3, 2
/* 8021979C 0021637C  38 80 00 63 */	li r4, 0x63
/* 802197A0 00216380  38 A0 00 01 */	li r5, 1
/* 802197A4 00216384  48 0E B8 B5 */	bl func_80305058
/* 802197A8 00216388  90 61 00 14 */	stw r3, 0x14(r1)
/* 802197AC 0021638C  80 1E 00 D4 */	lwz r0, 0xd4(r30)
/* 802197B0 00216390  7C 00 18 00 */	cmpw r0, r3
/* 802197B4 00216394  41 82 FF E0 */	beq lbl_80219794
lbl_802197B8:
/* 802197B8 00216398  3B BD 00 01 */	addi r29, r29, 1
/* 802197BC 0021639C  2C 1D 00 03 */	cmpwi r29, 3
/* 802197C0 002163A0  41 80 00 08 */	blt lbl_802197C8
/* 802197C4 002163A4  3B A0 00 00 */	li r29, 0
lbl_802197C8:
/* 802197C8 002163A8  57 A0 10 3A */	slwi r0, r29, 2
/* 802197CC 002163AC  80 81 00 14 */	lwz r4, 0x14(r1)
/* 802197D0 002163B0  7C 7F 02 14 */	add r3, r31, r0
/* 802197D4 002163B4  3B A0 00 00 */	li r29, 0
/* 802197D8 002163B8  90 83 00 D4 */	stw r4, 0xd4(r3)
/* 802197DC 002163BC  57 A0 10 3A */	slwi r0, r29, 2
/* 802197E0 002163C0  7F DF 02 14 */	add r30, r31, r0
lbl_802197E4:
/* 802197E4 002163C4  80 7E 00 D4 */	lwz r3, 0xd4(r30)
/* 802197E8 002163C8  48 10 2C 6D */	bl func_8031C454
/* 802197EC 002163CC  3B BD 00 01 */	addi r29, r29, 1
/* 802197F0 002163D0  2C 1D 00 03 */	cmpwi r29, 3
/* 802197F4 002163D4  3B DE 00 04 */	addi r30, r30, 4
/* 802197F8 002163D8  41 80 FF EC */	blt lbl_802197E4
/* 802197FC 002163DC  80 6D B4 20 */	lwz r3, lbl_804D6AC0@sda21(r13)
/* 80219800 002163E0  80 63 00 04 */	lwz r3, 4(r3)
/* 80219804 002163E4  2C 03 00 00 */	cmpwi r3, 0
/* 80219808 002163E8  41 82 00 10 */	beq lbl_80219818
/* 8021980C 002163EC  48 16 6D 75 */	bl HSD_Randi
/* 80219810 002163F0  7C 66 1B 78 */	mr r6, r3
/* 80219814 002163F4  48 00 00 08 */	b lbl_8021981C
lbl_80219818:
/* 80219818 002163F8  38 C0 00 00 */	li r6, 0
lbl_8021981C:
/* 8021981C 002163FC  80 8D B4 20 */	lwz r4, lbl_804D6AC0@sda21(r13)
/* 80219820 00216400  38 00 00 00 */	li r0, 0
/* 80219824 00216404  38 7F 00 E0 */	addi r3, r31, 0xe0
/* 80219828 00216408  80 A4 00 00 */	lwz r5, 0(r4)
/* 8021982C 0021640C  38 80 00 0C */	li r4, 0xc
/* 80219830 00216410  7C A5 32 14 */	add r5, r5, r6
/* 80219834 00216414  90 BF 00 C4 */	stw r5, 0xc4(r31)
/* 80219838 00216418  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 8021983C 0021641C  90 1F 00 CC */	stw r0, 0xcc(r31)
/* 80219840 00216420  90 1F 00 D0 */	stw r0, 0xd0(r31)
/* 80219844 00216424  4B DF 29 1D */	bl func_8000C160
/* 80219848 00216428  38 7F 00 EC */	addi r3, r31, 0xec
/* 8021984C 0021642C  38 80 00 0C */	li r4, 0xc
/* 80219850 00216430  4B DF 29 11 */	bl func_8000C160
/* 80219854 00216434  38 7F 00 F8 */	addi r3, r31, 0xf8
/* 80219858 00216438  38 80 00 0C */	li r4, 0xc
/* 8021985C 0021643C  4B DF 29 05 */	bl func_8000C160
/* 80219860 00216440  3C 60 80 22 */	lis r3, lbl_80219B10@ha
/* 80219864 00216444  38 A3 9B 10 */	addi r5, r3, lbl_80219B10@l
/* 80219868 00216448  38 9F 00 00 */	addi r4, r31, 0
/* 8021986C 0021644C  38 60 00 00 */	li r3, 0
/* 80219870 00216450  4B E3 E8 59 */	bl func_800580C8
/* 80219874 00216454  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80219878 00216458  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8021987C 0021645C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80219880 00216460  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80219884 00216464  38 21 00 30 */	addi r1, r1, 0x30
/* 80219888 00216468  7C 08 03 A6 */	mtlr r0
/* 8021988C 0021646C  4E 80 00 20 */	blr 
.global lbl_80219890
lbl_80219890:
/* 80219890 00216470  38 60 00 00 */	li r3, 0
/* 80219894 00216474  4E 80 00 20 */	blr 
.global lbl_80219898
lbl_80219898:
/* 80219898 00216478  7C 08 02 A6 */	mflr r0
/* 8021989C 0021647C  90 01 00 04 */	stw r0, 4(r1)
/* 802198A0 00216480  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 802198A4 00216484  93 E1 00 44 */	stw r31, 0x44(r1)
/* 802198A8 00216488  93 C1 00 40 */	stw r30, 0x40(r1)
/* 802198AC 0021648C  7C 7E 1B 78 */	mr r30, r3
/* 802198B0 00216490  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 802198B4 00216494  3B A0 00 00 */	li r29, 0
/* 802198B8 00216498  93 81 00 38 */	stw r28, 0x38(r1)
/* 802198BC 0021649C  80 8D C1 8C */	lwz r4, lbl_804D782C@sda21(r13)
/* 802198C0 002164A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802198C4 002164A4  83 84 00 20 */	lwz r28, 0x20(r4)
/* 802198C8 002164A8  48 00 00 14 */	b lbl_802198DC
lbl_802198CC:
/* 802198CC 002164AC  7F 83 E3 78 */	mr r3, r28
/* 802198D0 002164B0  4B E6 D0 B5 */	bl func_80086984
/* 802198D4 002164B4  93 A3 00 48 */	stw r29, 0x48(r3)
/* 802198D8 002164B8  83 9C 00 08 */	lwz r28, 8(r28)
lbl_802198DC:
/* 802198DC 002164BC  28 1C 00 00 */	cmplwi r28, 0
/* 802198E0 002164C0  40 82 FF EC */	bne lbl_802198CC
/* 802198E4 002164C4  80 6D B4 20 */	lwz r3, lbl_804D6AC0@sda21(r13)
/* 802198E8 002164C8  80 9F 00 C8 */	lwz r4, 0xc8(r31)
/* 802198EC 002164CC  80 03 00 08 */	lwz r0, 8(r3)
/* 802198F0 002164D0  7C 04 00 00 */	cmpw r4, r0
/* 802198F4 002164D4  40 80 01 60 */	bge lbl_80219A54
/* 802198F8 002164D8  80 7F 00 C4 */	lwz r3, 0xc4(r31)
/* 802198FC 002164DC  2C 03 00 00 */	cmpwi r3, 0
/* 80219900 002164E0  40 82 01 48 */	bne lbl_80219A48
/* 80219904 002164E4  3C 60 80 3C */	lis r3, lbl_803B8470@ha
/* 80219908 002164E8  38 83 84 70 */	addi r4, r3, lbl_803B8470@l
/* 8021990C 002164EC  80 64 00 00 */	lwz r3, 0(r4)
/* 80219910 002164F0  80 04 00 04 */	lwz r0, 4(r4)
/* 80219914 002164F4  90 61 00 1C */	stw r3, 0x1c(r1)
/* 80219918 002164F8  90 01 00 20 */	stw r0, 0x20(r1)
/* 8021991C 002164FC  80 04 00 08 */	lwz r0, 8(r4)
/* 80219920 00216500  90 01 00 24 */	stw r0, 0x24(r1)
/* 80219924 00216504  80 7F 00 C8 */	lwz r3, 0xc8(r31)
/* 80219928 00216508  38 03 00 01 */	addi r0, r3, 1
/* 8021992C 0021650C  90 1F 00 C8 */	stw r0, 0xc8(r31)
/* 80219930 00216510  80 6D B4 20 */	lwz r3, lbl_804D6AC0@sda21(r13)
/* 80219934 00216514  C0 02 C1 68 */	lfs f0, lbl_804DBB48@sda21(r2)
/* 80219938 00216518  C0 43 00 10 */	lfs f2, 0x10(r3)
/* 8021993C 0021651C  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 80219940 00216520  EC 42 08 28 */	fsubs f2, f2, f1
/* 80219944 00216524  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80219948 00216528  40 80 00 08 */	bge lbl_80219950
/* 8021994C 0021652C  FC 40 10 50 */	fneg f2, f2
lbl_80219950:
/* 80219950 00216530  C0 22 C1 6C */	lfs f1, lbl_804DBB4C@sda21(r2)
/* 80219954 00216534  C0 02 C1 70 */	lfs f0, lbl_804DBB50@sda21(r2)
/* 80219958 00216538  EC 22 00 72 */	fmuls f1, f2, f1
/* 8021995C 0021653C  EC 21 00 28 */	fsubs f1, f1, f0
/* 80219960 00216540  FC 00 08 1E */	fctiwz f0, f1
/* 80219964 00216544  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 80219968 00216548  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8021996C 0021654C  2C 00 00 00 */	cmpwi r0, 0
/* 80219970 00216550  41 82 00 14 */	beq lbl_80219984
/* 80219974 00216554  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 80219978 00216558  80 61 00 34 */	lwz r3, 0x34(r1)
/* 8021997C 0021655C  48 16 6C 05 */	bl HSD_Randi
/* 80219980 00216560  48 00 00 08 */	b lbl_80219988
lbl_80219984:
/* 80219984 00216564  38 60 00 00 */	li r3, 0
lbl_80219988:
/* 80219988 00216568  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 8021998C 0021656C  C8 22 C1 78 */	lfd f1, lbl_804DBB58@sda21(r2)
/* 80219990 00216570  90 01 00 34 */	stw r0, 0x34(r1)
/* 80219994 00216574  3C 00 43 30 */	lis r0, 0x4330
/* 80219998 00216578  C0 42 C1 70 */	lfs f2, lbl_804DBB50@sda21(r2)
/* 8021999C 0021657C  38 60 00 02 */	li r3, 2
/* 802199A0 00216580  90 01 00 30 */	stw r0, 0x30(r1)
/* 802199A4 00216584  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 802199A8 00216588  EC 00 08 28 */	fsubs f0, f0, f1
/* 802199AC 0021658C  EC 02 00 2A */	fadds f0, f2, f0
/* 802199B0 00216590  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 802199B4 00216594  48 16 6B CD */	bl HSD_Randi
/* 802199B8 00216598  2C 03 00 00 */	cmpwi r3, 0
/* 802199BC 0021659C  40 82 00 14 */	bne lbl_802199D0
/* 802199C0 002165A0  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 802199C4 002165A4  C0 02 C1 74 */	lfs f0, lbl_804DBB54@sda21(r2)
/* 802199C8 002165A8  EC 01 00 32 */	fmuls f0, f1, f0
/* 802199CC 002165AC  D0 01 00 1C */	stfs f0, 0x1c(r1)
lbl_802199D0:
/* 802199D0 002165B0  48 00 B0 B1 */	bl func_80224A80
/* 802199D4 002165B4  80 AD B4 20 */	lwz r5, lbl_804D6AC0@sda21(r13)
/* 802199D8 002165B8  38 7E 00 00 */	addi r3, r30, 0
/* 802199DC 002165BC  38 81 00 1C */	addi r4, r1, 0x1c
/* 802199E0 002165C0  C0 05 00 14 */	lfs f0, 0x14(r5)
/* 802199E4 002165C4  EC 00 08 2A */	fadds f0, f0, f1
/* 802199E8 002165C8  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 802199EC 002165CC  80 DF 00 C8 */	lwz r6, 0xc8(r31)
/* 802199F0 002165D0  54 C0 10 3A */	slwi r0, r6, 2
/* 802199F4 002165D4  7C BF 02 14 */	add r5, r31, r0
/* 802199F8 002165D8  80 A5 00 D0 */	lwz r5, 0xd0(r5)
/* 802199FC 002165DC  48 0D 86 99 */	bl func_802F2094
/* 80219A00 002165E0  80 1F 00 C8 */	lwz r0, 0xc8(r31)
/* 80219A04 002165E4  54 00 10 3A */	slwi r0, r0, 2
/* 80219A08 002165E8  7C 9F 02 14 */	add r4, r31, r0
/* 80219A0C 002165EC  90 64 00 F4 */	stw r3, 0xf4(r4)
/* 80219A10 002165F0  38 80 00 00 */	li r4, 0
/* 80219A14 002165F4  48 0D 86 01 */	bl func_802F2014
/* 80219A18 002165F8  80 6D B4 20 */	lwz r3, lbl_804D6AC0@sda21(r13)
/* 80219A1C 002165FC  80 63 00 04 */	lwz r3, 4(r3)
/* 80219A20 00216600  2C 03 00 00 */	cmpwi r3, 0
/* 80219A24 00216604  41 82 00 0C */	beq lbl_80219A30
/* 80219A28 00216608  48 16 6B 59 */	bl HSD_Randi
/* 80219A2C 0021660C  48 00 00 08 */	b lbl_80219A34
lbl_80219A30:
/* 80219A30 00216610  38 60 00 00 */	li r3, 0
lbl_80219A34:
/* 80219A34 00216614  80 8D B4 20 */	lwz r4, lbl_804D6AC0@sda21(r13)
/* 80219A38 00216618  80 04 00 00 */	lwz r0, 0(r4)
/* 80219A3C 0021661C  7C 00 1A 14 */	add r0, r0, r3
/* 80219A40 00216620  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 80219A44 00216624  48 00 00 A4 */	b lbl_80219AE8
lbl_80219A48:
/* 80219A48 00216628  38 03 FF FF */	addi r0, r3, -1
/* 80219A4C 0021662C  90 1F 00 C4 */	stw r0, 0xc4(r31)
/* 80219A50 00216630  48 00 00 98 */	b lbl_80219AE8
lbl_80219A54:
/* 80219A54 00216634  7F C3 F3 78 */	mr r3, r30
/* 80219A58 00216638  48 00 01 F9 */	bl func_80219C50
/* 80219A5C 0021663C  2C 03 00 00 */	cmpwi r3, 0
/* 80219A60 00216640  41 82 00 88 */	beq lbl_80219AE8
/* 80219A64 00216644  3B C0 00 00 */	li r30, 0
/* 80219A68 00216648  57 C0 10 3A */	slwi r0, r30, 2
/* 80219A6C 0021664C  7F BF 02 14 */	add r29, r31, r0
/* 80219A70 00216650  48 00 00 1C */	b lbl_80219A8C
lbl_80219A74:
/* 80219A74 00216654  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 80219A78 00216658  38 80 00 01 */	li r4, 1
/* 80219A7C 0021665C  54 03 04 3E */	clrlwi r3, r0, 0x10
/* 80219A80 00216660  4B F6 48 01 */	bl func_8017E280
/* 80219A84 00216664  3B BD 00 04 */	addi r29, r29, 4
/* 80219A88 00216668  3B DE 00 01 */	addi r30, r30, 1
lbl_80219A8C:
/* 80219A8C 0021666C  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 80219A90 00216670  7C 1E 00 00 */	cmpw r30, r0
/* 80219A94 00216674  41 80 FF E0 */	blt lbl_80219A74
/* 80219A98 00216678  2C 00 00 00 */	cmpwi r0, 0
/* 80219A9C 0021667C  41 82 00 38 */	beq lbl_80219AD4
/* 80219AA0 00216680  2C 00 00 03 */	cmpwi r0, 3
/* 80219AA4 00216684  40 82 00 18 */	bne lbl_80219ABC
/* 80219AA8 00216688  3C 60 80 4A */	lis r3, stage_info@ha
/* 80219AAC 0021668C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80219AB0 00216690  80 03 00 84 */	lwz r0, 0x84(r3)
/* 80219AB4 00216694  60 00 00 20 */	ori r0, r0, 0x20
/* 80219AB8 00216698  90 03 00 84 */	stw r0, 0x84(r3)
lbl_80219ABC:
/* 80219ABC 0021669C  3C 60 80 4A */	lis r3, stage_info@ha
/* 80219AC0 002166A0  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80219AC4 002166A4  80 03 00 84 */	lwz r0, 0x84(r3)
/* 80219AC8 002166A8  60 00 01 00 */	ori r0, r0, 0x100
/* 80219ACC 002166AC  90 03 00 84 */	stw r0, 0x84(r3)
/* 80219AD0 002166B0  48 00 00 18 */	b lbl_80219AE8
lbl_80219AD4:
/* 80219AD4 002166B4  3C 60 80 4A */	lis r3, stage_info@ha
/* 80219AD8 002166B8  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80219ADC 002166BC  80 03 00 84 */	lwz r0, 0x84(r3)
/* 80219AE0 002166C0  60 00 02 00 */	ori r0, r0, 0x200
/* 80219AE4 002166C4  90 03 00 84 */	stw r0, 0x84(r3)
lbl_80219AE8:
/* 80219AE8 002166C8  4B DF 7B 0D */	bl func_800115F4
/* 80219AEC 002166CC  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80219AF0 002166D0  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80219AF4 002166D4  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80219AF8 002166D8  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80219AFC 002166DC  83 81 00 38 */	lwz r28, 0x38(r1)
/* 80219B00 002166E0  38 21 00 48 */	addi r1, r1, 0x48
/* 80219B04 002166E4  7C 08 03 A6 */	mtlr r0
/* 80219B08 002166E8  4E 80 00 20 */	blr 
.global lbl_80219B0C
lbl_80219B0C:
/* 80219B0C 002166EC  4E 80 00 20 */	blr 
lbl_80219B10:
/* 80219B10 002166F0  7C 08 02 A6 */	mflr r0
/* 80219B14 002166F4  90 01 00 04 */	stw r0, 4(r1)
/* 80219B18 002166F8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80219B1C 002166FC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80219B20 00216700  3B E3 00 00 */	addi r31, r3, 0
/* 80219B24 00216704  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80219B28 00216708  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80219B2C 0021670C  7C BD 2B 78 */	mr r29, r5
/* 80219B30 00216710  88 05 00 34 */	lbz r0, 0x34(r5)
/* 80219B34 00216714  80 85 00 00 */	lwz r4, 0(r5)
/* 80219B38 00216718  54 00 EF 3E */	rlwinm r0, r0, 0x1d, 0x1c, 0x1f
/* 80219B3C 0021671C  2C 00 00 05 */	cmpwi r0, 5
/* 80219B40 00216720  40 82 00 D8 */	bne lbl_80219C18
/* 80219B44 00216724  28 04 00 00 */	cmplwi r4, 0
/* 80219B48 00216728  41 82 00 D0 */	beq lbl_80219C18
/* 80219B4C 0021672C  A0 04 00 00 */	lhz r0, 0(r4)
/* 80219B50 00216730  28 00 00 06 */	cmplwi r0, 6
/* 80219B54 00216734  40 82 00 C4 */	bne lbl_80219C18
/* 80219B58 00216738  80 64 00 2C */	lwz r3, 0x2c(r4)
/* 80219B5C 0021673C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80219B60 00216740  2C 00 00 9F */	cmpwi r0, 0x9f
/* 80219B64 00216744  40 82 00 B4 */	bne lbl_80219C18
/* 80219B68 00216748  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 80219B6C 0021674C  2C 00 00 03 */	cmpwi r0, 3
/* 80219B70 00216750  40 80 00 A8 */	bge lbl_80219C18
/* 80219B74 00216754  7C 83 23 78 */	mr r3, r4
/* 80219B78 00216758  48 0D 84 A9 */	bl func_802F2020
/* 80219B7C 0021675C  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 80219B80 00216760  3B C3 00 00 */	addi r30, r3, 0
/* 80219B84 00216764  38 9F 00 00 */	addi r4, r31, 0
/* 80219B88 00216768  2C 00 00 00 */	cmpwi r0, 0
/* 80219B8C 0021676C  7C 09 03 A6 */	mtctr r0
/* 80219B90 00216770  38 A0 00 00 */	li r5, 0
/* 80219B94 00216774  40 81 00 20 */	ble lbl_80219BB4
lbl_80219B98:
/* 80219B98 00216778  80 64 00 EC */	lwz r3, 0xec(r4)
/* 80219B9C 0021677C  80 1D 00 00 */	lwz r0, 0(r29)
/* 80219BA0 00216780  7C 03 00 40 */	cmplw r3, r0
/* 80219BA4 00216784  40 82 00 08 */	bne lbl_80219BAC
/* 80219BA8 00216788  38 A5 00 01 */	addi r5, r5, 1
lbl_80219BAC:
/* 80219BAC 0021678C  38 84 00 04 */	addi r4, r4, 4
/* 80219BB0 00216790  42 00 FF E8 */	bdnz lbl_80219B98
lbl_80219BB4:
/* 80219BB4 00216794  2C 05 00 00 */	cmpwi r5, 0
/* 80219BB8 00216798  40 82 00 60 */	bne lbl_80219C18
/* 80219BBC 0021679C  C0 3D 00 04 */	lfs f1, 4(r29)
/* 80219BC0 002167A0  C0 02 C1 80 */	lfs f0, lbl_804DBB60@sda21(r2)
/* 80219BC4 002167A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80219BC8 002167A8  4C 40 13 82 */	cror 2, 0, 2
/* 80219BCC 002167AC  40 82 00 4C */	bne lbl_80219C18
/* 80219BD0 002167B0  C0 02 C1 84 */	lfs f0, lbl_804DBB64@sda21(r2)
/* 80219BD4 002167B4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80219BD8 002167B8  4C 41 13 82 */	cror 2, 1, 2
/* 80219BDC 002167BC  40 82 00 3C */	bne lbl_80219C18
/* 80219BE0 002167C0  80 7D 00 00 */	lwz r3, 0(r29)
/* 80219BE4 002167C4  48 0D 84 49 */	bl func_802F202C
/* 80219BE8 002167C8  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 80219BEC 002167CC  80 9D 00 00 */	lwz r4, 0(r29)
/* 80219BF0 002167D0  54 00 10 3A */	slwi r0, r0, 2
/* 80219BF4 002167D4  7C 7F 02 14 */	add r3, r31, r0
/* 80219BF8 002167D8  90 83 00 EC */	stw r4, 0xec(r3)
/* 80219BFC 002167DC  80 1F 00 CC */	lwz r0, 0xcc(r31)
/* 80219C00 002167E0  54 00 10 3A */	slwi r0, r0, 2
/* 80219C04 002167E4  7C 7F 02 14 */	add r3, r31, r0
/* 80219C08 002167E8  93 C3 00 E0 */	stw r30, 0xe0(r3)
/* 80219C0C 002167EC  80 7F 00 CC */	lwz r3, 0xcc(r31)
/* 80219C10 002167F0  38 03 00 01 */	addi r0, r3, 1
/* 80219C14 002167F4  90 1F 00 CC */	stw r0, 0xcc(r31)
lbl_80219C18:
/* 80219C18 002167F8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80219C1C 002167FC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80219C20 00216800  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80219C24 00216804  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80219C28 00216808  38 21 00 40 */	addi r1, r1, 0x40
/* 80219C2C 0021680C  7C 08 03 A6 */	mtlr r0
/* 80219C30 00216810  4E 80 00 20 */	blr 

.global func_80219C34
func_80219C34:
/* 80219C34 00216814  28 03 00 00 */	cmplwi r3, 0
/* 80219C38 00216818  4D 82 00 20 */	beqlr 
/* 80219C3C 0021681C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80219C40 00216820  80 64 00 D0 */	lwz r3, 0xd0(r4)
/* 80219C44 00216824  38 03 00 01 */	addi r0, r3, 1
/* 80219C48 00216828  90 04 00 D0 */	stw r0, 0xd0(r4)
/* 80219C4C 0021682C  4E 80 00 20 */	blr 

.global func_80219C50
func_80219C50:
/* 80219C50 00216830  28 03 00 00 */	cmplwi r3, 0
/* 80219C54 00216834  40 82 00 0C */	bne lbl_80219C60
/* 80219C58 00216838  38 60 00 00 */	li r3, 0
/* 80219C5C 0021683C  4E 80 00 20 */	blr 
lbl_80219C60:
/* 80219C60 00216840  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80219C64 00216844  80 64 00 CC */	lwz r3, 0xcc(r4)
/* 80219C68 00216848  80 04 00 D0 */	lwz r0, 0xd0(r4)
/* 80219C6C 0021684C  7C 03 02 14 */	add r0, r3, r0
/* 80219C70 00216850  2C 00 00 03 */	cmpwi r0, 3
/* 80219C74 00216854  41 80 00 0C */	blt lbl_80219C80
/* 80219C78 00216858  38 60 00 01 */	li r3, 1
/* 80219C7C 0021685C  4E 80 00 20 */	blr 
lbl_80219C80:
/* 80219C80 00216860  38 60 00 00 */	li r3, 0
/* 80219C84 00216864  4E 80 00 20 */	blr 
.global lbl_80219C88
lbl_80219C88:
/* 80219C88 00216868  38 60 00 00 */	li r3, 0
/* 80219C8C 0021686C  4E 80 00 20 */	blr 
.global lbl_80219C90
lbl_80219C90:
/* 80219C90 00216870  38 60 00 01 */	li r3, 1
/* 80219C94 00216874  4E 80 00 20 */	blr 


.section .rodata

.global lbl_803B8470
lbl_803B8470:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000


.section .data

.global lbl_803E7D00
lbl_803E7D00:
	.4byte lbl_802196B4
	.4byte lbl_802196E0
	.4byte lbl_802196E8
	.4byte lbl_802196EC
    .4byte NULL
	.4byte lbl_802196F0
	.4byte lbl_80219890
	.4byte lbl_80219898
	.4byte lbl_80219B0C
    .4byte 0xC0000000
.global lbl_803E7D28
lbl_803E7D28:
    .4byte 0x2F47724E
    .4byte 0x46672E64
    .4byte 0x61740000
.global lbl_803E7D34
lbl_803E7D34:
    .4byte 0x00000026
    .4byte lbl_803E7D00
    .4byte lbl_803E7D28
	.4byte lbl_80219534
	.4byte func_80219530
	.4byte lbl_8021959C
	.4byte lbl_802195A0
	.4byte lbl_802195C4
	.4byte lbl_80219C88
	.4byte lbl_80219C90
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
    .4byte 0x67726669
    .4byte 0x67757265
    .4byte 0x6765742E
    .4byte 0x63000000
    .4byte NULL
