.include "macros.inc"

.section .text

.global it_802C65E4
it_802C65E4:
/* 802C65E4 002C31C4  7C 08 02 A6 */	mflr r0
/* 802C65E8 002C31C8  38 E0 00 00 */	li r7, 0
/* 802C65EC 002C31CC  90 01 00 04 */	stw r0, 4(r1)
/* 802C65F0 002C31D0  38 00 00 73 */	li r0, 0x73
/* 802C65F4 002C31D4  38 C0 00 01 */	li r6, 1
/* 802C65F8 002C31D8  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 802C65FC 002C31DC  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 802C6600 002C31E0  93 C1 00 78 */	stw r30, 0x78(r1)
/* 802C6604 002C31E4  7C BE 2B 78 */	mr r30, r5
/* 802C6608 002C31E8  93 A1 00 74 */	stw r29, 0x74(r1)
/* 802C660C 002C31EC  3B A3 00 00 */	addi r29, r3, 0
/* 802C6610 002C31F0  90 01 00 28 */	stw r0, 0x28(r1)
/* 802C6614 002C31F4  80 64 00 00 */	lwz r3, 0(r4)
/* 802C6618 002C31F8  80 04 00 04 */	lwz r0, 4(r4)
/* 802C661C 002C31FC  90 61 00 40 */	stw r3, 0x40(r1)
/* 802C6620 002C3200  38 61 00 20 */	addi r3, r1, 0x20
/* 802C6624 002C3204  90 01 00 44 */	stw r0, 0x44(r1)
/* 802C6628 002C3208  80 04 00 08 */	lwz r0, 8(r4)
/* 802C662C 002C320C  90 01 00 48 */	stw r0, 0x48(r1)
/* 802C6630 002C3210  80 81 00 40 */	lwz r4, 0x40(r1)
/* 802C6634 002C3214  80 01 00 44 */	lwz r0, 0x44(r1)
/* 802C6638 002C3218  C0 02 D8 B8 */	lfs f0, it_804DD298@sda21(r2)
/* 802C663C 002C321C  90 81 00 34 */	stw r4, 0x34(r1)
/* 802C6640 002C3220  90 01 00 38 */	stw r0, 0x38(r1)
/* 802C6644 002C3224  80 01 00 48 */	lwz r0, 0x48(r1)
/* 802C6648 002C3228  90 01 00 3C */	stw r0, 0x3c(r1)
/* 802C664C 002C322C  D0 21 00 58 */	stfs f1, 0x58(r1)
/* 802C6650 002C3230  B0 E1 00 5C */	sth r7, 0x5c(r1)
/* 802C6654 002C3234  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 802C6658 002C3238  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 802C665C 002C323C  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 802C6660 002C3240  93 A1 00 20 */	stw r29, 0x20(r1)
/* 802C6664 002C3244  80 01 00 20 */	lwz r0, 0x20(r1)
/* 802C6668 002C3248  90 01 00 24 */	stw r0, 0x24(r1)
/* 802C666C 002C324C  88 01 00 64 */	lbz r0, 0x64(r1)
/* 802C6670 002C3250  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 802C6674 002C3254  98 01 00 64 */	stb r0, 0x64(r1)
/* 802C6678 002C3258  90 E1 00 60 */	stw r7, 0x60(r1)
/* 802C667C 002C325C  4B FA 24 9D */	bl Item_80268B18
/* 802C6680 002C3260  7C 7F 1B 79 */	or. r31, r3, r3
/* 802C6684 002C3264  41 82 00 44 */	beq .L_802C66C8
/* 802C6688 002C3268  80 BF 00 2C */	lwz r5, 0x2c(r31)
/* 802C668C 002C326C  38 7F 00 00 */	addi r3, r31, 0
/* 802C6690 002C3270  38 9D 00 00 */	addi r4, r29, 0
/* 802C6694 002C3274  80 C5 00 C4 */	lwz r6, 0xc4(r5)
/* 802C6698 002C3278  7F C5 F3 78 */	mr r5, r30
/* 802C669C 002C327C  83 C6 00 04 */	lwz r30, 4(r6)
/* 802C66A0 002C3280  4B FA 44 B5 */	bl Item_8026AB54
/* 802C66A4 002C3284  38 7F 00 00 */	addi r3, r31, 0
/* 802C66A8 002C3288  38 9D 00 00 */	addi r4, r29, 0
/* 802C66AC 002C328C  4B F5 F7 2D */	bl db_80225DD8
/* 802C66B0 002C3290  80 BE 00 00 */	lwz r5, 0(r30)
/* 802C66B4 002C3294  38 7F 00 00 */	addi r3, r31, 0
/* 802C66B8 002C3298  38 9D 00 00 */	addi r4, r29, 0
/* 802C66BC 002C329C  4B FB 67 A9 */	bl it_8027CE64
/* 802C66C0 002C32A0  7F E3 FB 78 */	mr r3, r31
/* 802C66C4 002C32A4  48 00 00 08 */	b .L_802C66CC
.L_802C66C8:
/* 802C66C8 002C32A8  38 60 00 00 */	li r3, 0
.L_802C66CC:
/* 802C66CC 002C32AC  80 01 00 84 */	lwz r0, 0x84(r1)
/* 802C66D0 002C32B0  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 802C66D4 002C32B4  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 802C66D8 002C32B8  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 802C66DC 002C32BC  38 21 00 80 */	addi r1, r1, 0x80
/* 802C66E0 002C32C0  7C 08 03 A6 */	mtlr r0
/* 802C66E4 002C32C4  4E 80 00 20 */	blr

.global it_802C66E8
it_802C66E8:
/* 802C66E8 002C32C8  7C 08 02 A6 */	mflr r0
/* 802C66EC 002C32CC  90 01 00 04 */	stw r0, 4(r1)
/* 802C66F0 002C32D0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C66F4 002C32D4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C66F8 002C32D8  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C66FC 002C32DC  28 03 00 00 */	cmplwi r3, 0
/* 802C6700 002C32E0  41 82 00 08 */	beq .L_802C6708
/* 802C6704 002C32E4  4B E8 45 3D */	bl ftGw_AttackLw3_ItemManholeRemove
.L_802C6708:
/* 802C6708 002C32E8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C670C 002C32EC  38 21 00 08 */	addi r1, r1, 8
/* 802C6710 002C32F0  7C 08 03 A6 */	mtlr r0
/* 802C6714 002C32F4  4E 80 00 20 */	blr

.global it_802C6718
it_802C6718:
/* 802C6718 002C32F8  7C 08 02 A6 */	mflr r0
/* 802C671C 002C32FC  90 01 00 04 */	stw r0, 4(r1)
/* 802C6720 002C3300  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802C6724 002C3304  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802C6728 002C3308  7C 7F 1B 78 */	mr r31, r3
/* 802C672C 002C330C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C6730 002C3310  28 03 00 00 */	cmplwi r3, 0
/* 802C6734 002C3314  41 82 00 1C */	beq .L_802C6750
/* 802C6738 002C3318  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C673C 002C331C  28 03 00 00 */	cmplwi r3, 0
/* 802C6740 002C3320  41 82 00 08 */	beq .L_802C6748
/* 802C6744 002C3324  4B E8 44 FD */	bl ftGw_AttackLw3_ItemManholeRemove
.L_802C6748:
/* 802C6748 002C3328  7F E3 FB 78 */	mr r3, r31
/* 802C674C 002C332C  4B FA 41 A1 */	bl Item_8026A8EC
.L_802C6750:
/* 802C6750 002C3330  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802C6754 002C3334  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802C6758 002C3338  38 21 00 20 */	addi r1, r1, 0x20
/* 802C675C 002C333C  7C 08 03 A6 */	mtlr r0
/* 802C6760 002C3340  4E 80 00 20 */	blr

.global it_802C6764
it_802C6764:
/* 802C6764 002C3344  7C 08 02 A6 */	mflr r0
/* 802C6768 002C3348  90 01 00 04 */	stw r0, 4(r1)
/* 802C676C 002C334C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C6770 002C3350  4B FA 4F B5 */	bl it_8026B724
/* 802C6774 002C3354  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C6778 002C3358  38 21 00 08 */	addi r1, r1, 8
/* 802C677C 002C335C  7C 08 03 A6 */	mtlr r0
/* 802C6780 002C3360  4E 80 00 20 */	blr

.global it_802C6784
it_802C6784:
/* 802C6784 002C3364  7C 08 02 A6 */	mflr r0
/* 802C6788 002C3368  90 01 00 04 */	stw r0, 4(r1)
/* 802C678C 002C336C  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C6790 002C3370  4B FA 4F AD */	bl it_8026B73C
/* 802C6794 002C3374  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C6798 002C3378  38 21 00 08 */	addi r1, r1, 8
/* 802C679C 002C337C  7C 08 03 A6 */	mtlr r0
/* 802C67A0 002C3380  4E 80 00 20 */	blr

.global it_802C67A4
it_802C67A4:
/* 802C67A4 002C3384  7C 08 02 A6 */	mflr r0
/* 802C67A8 002C3388  90 01 00 04 */	stw r0, 4(r1)
/* 802C67AC 002C338C  38 00 00 00 */	li r0, 0
/* 802C67B0 002C3390  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802C67B4 002C3394  93 E1 00 24 */	stw r31, 0x24(r1)
/* 802C67B8 002C3398  93 C1 00 20 */	stw r30, 0x20(r1)
/* 802C67BC 002C339C  7C 7E 1B 78 */	mr r30, r3
/* 802C67C0 002C33A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802C67C4 002C33A4  90 1F 0D AC */	stw r0, 0xdac(r31)
/* 802C67C8 002C33A8  4B FA 53 7D */	bl it_8026BB44
/* 802C67CC 002C33AC  80 1F 05 18 */	lwz r0, 0x518(r31)
/* 802C67D0 002C33B0  28 00 00 00 */	cmplwi r0, 0
/* 802C67D4 002C33B4  41 82 00 1C */	beq .L_802C67F0
/* 802C67D8 002C33B8  38 7E 00 00 */	addi r3, r30, 0
/* 802C67DC 002C33BC  38 80 00 00 */	li r4, 0
/* 802C67E0 002C33C0  38 A0 00 02 */	li r5, 2
/* 802C67E4 002C33C4  4B FA 26 79 */	bl Item_80268E5C
/* 802C67E8 002C33C8  7F C3 F3 78 */	mr r3, r30
/* 802C67EC 002C33CC  4B FA 2C E1 */	bl Item_802694CC
.L_802C67F0:
/* 802C67F0 002C33D0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 802C67F4 002C33D4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 802C67F8 002C33D8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 802C67FC 002C33DC  38 21 00 28 */	addi r1, r1, 0x28
/* 802C6800 002C33E0  7C 08 03 A6 */	mtlr r0
/* 802C6804 002C33E4  4E 80 00 20 */	blr
.global it_802C6808
it_802C6808:
/* 802C6808 002C33E8  7C 08 02 A6 */	mflr r0
/* 802C680C 002C33EC  90 01 00 04 */	stw r0, 4(r1)
/* 802C6810 002C33F0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 802C6814 002C33F4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 802C6818 002C33F8  93 C1 00 28 */	stw r30, 0x28(r1)
/* 802C681C 002C33FC  7C 7E 1B 78 */	mr r30, r3
/* 802C6820 002C3400  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 802C6824 002C3404  80 03 0D AC */	lwz r0, 0xdac(r3)
/* 802C6828 002C3408  28 00 00 00 */	cmplwi r0, 0
/* 802C682C 002C340C  41 82 00 50 */	beq .L_802C687C
/* 802C6830 002C3410  3B E0 00 00 */	li r31, 0
/* 802C6834 002C3414  93 E3 0D AC */	stw r31, 0xdac(r3)
/* 802C6838 002C3418  7F C3 F3 78 */	mr r3, r30
/* 802C683C 002C341C  4B FA 52 E5 */	bl it_8026BB20
/* 802C6840 002C3420  80 7E 00 28 */	lwz r3, 0x28(r30)
/* 802C6844 002C3424  28 03 00 00 */	cmplwi r3, 0
/* 802C6848 002C3428  40 82 00 08 */	bne .L_802C6850
/* 802C684C 002C342C  48 00 00 08 */	b .L_802C6854
.L_802C6850:
/* 802C6850 002C3430  83 E3 00 10 */	lwz r31, 0x10(r3)
.L_802C6854:
/* 802C6854 002C3434  38 7F 00 00 */	addi r3, r31, 0
/* 802C6858 002C3438  38 A1 00 1C */	addi r5, r1, 0x1c
/* 802C685C 002C343C  38 80 00 00 */	li r4, 0
/* 802C6860 002C3440  4B D4 49 6D */	bl lb_8000B1CC
/* 802C6864 002C3444  C0 22 D8 BC */	lfs f1, it_804DD29C@sda21(r2)
/* 802C6868 002C3448  38 61 00 1C */	addi r3, r1, 0x1c
/* 802C686C 002C344C  C0 42 D8 C0 */	lfs f2, it_804DD2A0@sda21(r2)
/* 802C6870 002C3450  38 80 00 78 */	li r4, 0x78
/* 802C6874 002C3454  C0 62 D8 C4 */	lfs f3, it_804DD2A4@sda21(r2)
/* 802C6878 002C3458  4B D4 B1 65 */	bl lb_800119DC
.L_802C687C:
/* 802C687C 002C345C  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 802C6880 002C3460  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C6884 002C3464  28 03 00 00 */	cmplwi r3, 0
/* 802C6888 002C3468  41 82 00 0C */	beq .L_802C6894
/* 802C688C 002C346C  4B E8 45 0D */	bl ftGw_AttackLw3_ItemCheckManholeRemove
/* 802C6890 002C3470  48 00 00 08 */	b .L_802C6898
.L_802C6894:
/* 802C6894 002C3474  38 60 00 01 */	li r3, 1
.L_802C6898:
/* 802C6898 002C3478  2C 03 00 00 */	cmpwi r3, 0
/* 802C689C 002C347C  41 82 00 20 */	beq .L_802C68BC
/* 802C68A0 002C3480  80 7E 00 2C */	lwz r3, 0x2c(r30)
/* 802C68A4 002C3484  80 63 05 18 */	lwz r3, 0x518(r3)
/* 802C68A8 002C3488  28 03 00 00 */	cmplwi r3, 0
/* 802C68AC 002C348C  41 82 00 08 */	beq .L_802C68B4
/* 802C68B0 002C3490  4B E8 43 91 */	bl ftGw_AttackLw3_ItemManholeRemove
.L_802C68B4:
/* 802C68B4 002C3494  38 60 00 01 */	li r3, 1
/* 802C68B8 002C3498  48 00 00 08 */	b .L_802C68C0
.L_802C68BC:
/* 802C68BC 002C349C  38 60 00 00 */	li r3, 0
.L_802C68C0:
/* 802C68C0 002C34A0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 802C68C4 002C34A4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 802C68C8 002C34A8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 802C68CC 002C34AC  38 21 00 30 */	addi r1, r1, 0x30
/* 802C68D0 002C34B0  7C 08 03 A6 */	mtlr r0
/* 802C68D4 002C34B4  4E 80 00 20 */	blr

.global it_802C68D8
it_802C68D8:
/* 802C68D8 002C34B8  7C 08 02 A6 */	mflr r0
/* 802C68DC 002C34BC  90 01 00 04 */	stw r0, 4(r1)
/* 802C68E0 002C34C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 802C68E4 002C34C4  4B FA 4F B1 */	bl it_8026B894
/* 802C68E8 002C34C8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802C68EC 002C34CC  38 21 00 08 */	addi r1, r1, 8
/* 802C68F0 002C34D0  7C 08 03 A6 */	mtlr r0
/* 802C68F4 002C34D4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global it_803F78D8
it_803F78D8:
    .4byte 0
    .4byte it_802C6808
    .4byte NULL
    .4byte NULL


.section .sdata2
    .balign 8
.global it_804DD298
it_804DD298:
    .4byte 0x00000000
.global it_804DD29C
it_804DD29C:
    .4byte 0x40400000
.global it_804DD2A0
it_804DD2A0:
    .4byte 0x3DCCCCCD
.global it_804DD2A4
it_804DD2A4:
    .4byte 0x3F860A92
