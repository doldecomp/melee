.include "macros.inc"

.section .text  # 0x8008521C - 0x80086194

.global func_8008549C
func_8008549C:
/* 8008549C 0008207C  3C 60 80 46 */	lis r3, lbl_8045996C@ha
/* 800854A0 00082080  38 83 99 6C */	addi r4, r3, lbl_8045996C@l
/* 800854A4 00082084  38 60 00 00 */	li r3, 0
/* 800854A8 00082088  90 64 00 00 */	stw r3, 0(r4)
/* 800854AC 0008208C  38 C0 00 20 */	li r6, 0x20
/* 800854B0 00082090  90 64 00 04 */	stw r3, 4(r4)
/* 800854B4 00082094  90 64 00 08 */	stw r3, 8(r4)
/* 800854B8 00082098  90 64 00 0C */	stw r3, 0xc(r4)
/* 800854BC 0008209C  90 64 00 10 */	stw r3, 0x10(r4)
/* 800854C0 000820A0  90 64 00 14 */	stw r3, 0x14(r4)
/* 800854C4 000820A4  90 64 00 18 */	stw r3, 0x18(r4)
/* 800854C8 000820A8  90 64 00 1C */	stw r3, 0x1c(r4)
/* 800854CC 000820AC  90 64 00 20 */	stw r3, 0x20(r4)
/* 800854D0 000820B0  90 64 00 24 */	stw r3, 0x24(r4)
/* 800854D4 000820B4  90 64 00 28 */	stw r3, 0x28(r4)
/* 800854D8 000820B8  90 64 00 2C */	stw r3, 0x2c(r4)
/* 800854DC 000820BC  90 64 00 30 */	stw r3, 0x30(r4)
/* 800854E0 000820C0  90 64 00 34 */	stw r3, 0x34(r4)
/* 800854E4 000820C4  90 64 00 38 */	stw r3, 0x38(r4)
/* 800854E8 000820C8  90 64 00 3C */	stw r3, 0x3c(r4)
/* 800854EC 000820CC  90 64 00 40 */	stw r3, 0x40(r4)
/* 800854F0 000820D0  90 64 00 44 */	stw r3, 0x44(r4)
/* 800854F4 000820D4  90 64 00 48 */	stw r3, 0x48(r4)
/* 800854F8 000820D8  90 64 00 4C */	stw r3, 0x4c(r4)
/* 800854FC 000820DC  90 64 00 50 */	stw r3, 0x50(r4)
/* 80085500 000820E0  90 64 00 54 */	stw r3, 0x54(r4)
/* 80085504 000820E4  90 64 00 58 */	stw r3, 0x58(r4)
/* 80085508 000820E8  90 64 00 5C */	stw r3, 0x5c(r4)
/* 8008550C 000820EC  90 64 00 60 */	stw r3, 0x60(r4)
/* 80085510 000820F0  90 64 00 64 */	stw r3, 0x64(r4)
/* 80085514 000820F4  90 64 00 68 */	stw r3, 0x68(r4)
/* 80085518 000820F8  90 64 00 6C */	stw r3, 0x6c(r4)
/* 8008551C 000820FC  90 64 00 70 */	stw r3, 0x70(r4)
/* 80085520 00082100  90 64 00 74 */	stw r3, 0x74(r4)
/* 80085524 00082104  90 64 00 78 */	stw r3, 0x78(r4)
/* 80085528 00082108  90 64 00 7C */	stw r3, 0x7c(r4)
/* 8008552C 0008210C  48 00 00 24 */	b lbl_80085550
lbl_80085530:
/* 80085530 00082110  20 06 00 21 */	subfic r0, r6, 0x21
/* 80085534 00082114  2C 06 00 21 */	cmpwi r6, 0x21
/* 80085538 00082118  7C 09 03 A6 */	mtctr r0
/* 8008553C 0008211C  4C 80 00 20 */	bgelr 
lbl_80085540:
/* 80085540 00082120  90 64 00 00 */	stw r3, 0(r4)
/* 80085544 00082124  38 84 00 04 */	addi r4, r4, 4
/* 80085548 00082128  42 00 FF F8 */	bdnz lbl_80085540
/* 8008554C 0008212C  4E 80 00 20 */	blr 
lbl_80085550:
/* 80085550 00082130  54 C0 10 3A */	slwi r0, r6, 2
/* 80085554 00082134  7C 84 02 14 */	add r4, r4, r0
/* 80085558 00082138  4B FF FF D8 */	b lbl_80085530
/* 8008555C 0008213C  4E 80 00 20 */	blr 


.section .bss, "wa"
    .balign 8
.global gFtDataList
gFtDataList:
    .skip 0x84
.global lbl_8045993C
lbl_8045993C:
    .skip 0x30
.global lbl_8045996C
lbl_8045996C:
    .skip 0x84
lbl_804599F0:
    .skip 0x78


.section .data
    .balign 8
.global CostumeListsForeachCharacter
CostumeListsForeachCharacter:
    .4byte lbl_804599F0
    .4byte 0x05000000
    .4byte lbl_80459B28
    .4byte 0x04000000
    .4byte lbl_80459A98
    .4byte 0x06000000
    .4byte lbl_80459CA0
    .4byte 0x05000000
    .4byte lbl_80459C10
    .4byte 0x06000000
    .4byte lbl_8045A090
    .4byte 0x04000000
    .4byte lbl_803C82EC
    .4byte 0x05000000
    .4byte lbl_80459D18
    .4byte 0x05000000
    .4byte lbl_80459D90
    .4byte 0x04000000
    .4byte lbl_80459DF0
    .4byte 0x05000000
    .4byte lbl_80459E68
    .4byte 0x04000000
    .4byte lbl_80459EC8
    .4byte 0x04000000
    .4byte lbl_80459F28
    .4byte 0x04000000
    .4byte lbl_80459F88
    .4byte 0x05000000
    .4byte lbl_8045A000
    .4byte 0x06000000
    .4byte lbl_8045A1F8
    .4byte 0x05000000
    .4byte lbl_8045A2D0
    .4byte 0x04000000
    .4byte lbl_8045A270
    .4byte 0x04000000
    .4byte lbl_8045A0F0
    .4byte 0x05000000
    .4byte lbl_8045A168
    .4byte 0x05000000
    .4byte lbl_8045A330
    .4byte 0x05000000
    .4byte lbl_8045A3A8
    .4byte 0x05000000
    .4byte lbl_8045A420
    .4byte 0x04000000
    .4byte lbl_8045A480
    .4byte 0x04000000
    .4byte lbl_8045A4E0
    .4byte 0x04000000
    .4byte lbl_8045A540
    .4byte 0x05000000
    .4byte lbl_8045A5B8
    .4byte 0x05000000
    .4byte lbl_8045A690
    .4byte 0x01000000
    .4byte lbl_8045A6A8
    .4byte 0x01000000
    .4byte lbl_8045A630
    .4byte 0x01000000
    .4byte lbl_8045A648
    .4byte 0x01000000
    .4byte lbl_8045A660
    .4byte 0x01000000
    .4byte lbl_8045A678
    .4byte 0x01000000

.section .sdata
    .balign 8
.global lbl_804D3AA8
lbl_804D3AA8:
    .asciz "jobj.h"
    .balign 4
.global lbl_804D3AB0
lbl_804D3AB0:
    .asciz "jobj"
    .balign 4
