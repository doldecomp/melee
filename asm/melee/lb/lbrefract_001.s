.include "macros.inc"

.section .sdata2
    .balign 4

lbl_804D7D70:
	.float 2.0

lbl_804D7D74:
	.float -1.0

lbl_804D7D78:
	.double 0.0

lbl_804D7D80:
	.double 0.5

lbl_804D7D88:
	.double 3.0

lbl_804D7D90:
	.float 1.0

lbl_804D7D94:
	.float 128.0

lbl_804D7D98:
	.double 527765581332480.0

lbl_804D7DA0:
	.double 4503599627370496.0

.section .text

# https://decomp.me/scratch/CWwOc
.global local_80021CE8
local_80021CE8:
/* 80021CE8 0001E8C8  7C 08 02 A6 */	mflr r0
/* 80021CEC 0001E8CC  3C A0 43 30 */	lis r5, 0x4330
/* 80021CF0 0001E8D0  90 01 00 04 */	stw r0, 4(r1)
/* 80021CF4 0001E8D4  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 80021CF8 0001E8D8  DB E1 00 B8 */	stfd f31, 0xb8(r1)
/* 80021CFC 0001E8DC  DB C1 00 B0 */	stfd f30, 0xb0(r1)
/* 80021D00 0001E8E0  DB A1 00 A8 */	stfd f29, 0xa8(r1)
/* 80021D04 0001E8E4  DB 81 00 A0 */	stfd f28, 0xa0(r1)
/* 80021D08 0001E8E8  DB 61 00 98 */	stfd f27, 0x98(r1)
/* 80021D0C 0001E8EC  DB 41 00 90 */	stfd f26, 0x90(r1)
/* 80021D10 0001E8F0  DB 21 00 88 */	stfd f25, 0x88(r1)
/* 80021D14 0001E8F4  DB 01 00 80 */	stfd f24, 0x80(r1)
/* 80021D18 0001E8F8  DA E1 00 78 */	stfd f23, 0x78(r1)
/* 80021D1C 0001E8FC  DA C1 00 70 */	stfd f22, 0x70(r1)
/* 80021D20 0001E900  DA A1 00 68 */	stfd f21, 0x68(r1)
/* 80021D24 0001E904  DA 81 00 60 */	stfd f20, 0x60(r1)
/* 80021D28 0001E908  DA 61 00 58 */	stfd f19, 0x58(r1)
/* 80021D2C 0001E90C  BF 61 00 44 */	stmw r27, 0x44(r1)
/* 80021D30 0001E910  7C 7F 1B 78 */	mr r31, r3
/* 80021D34 0001E914  54 9D 18 38 */	slwi r29, r4, 3
/* 80021D38 0001E918  3B 80 00 00 */	li r28, 0
/* 80021D3C 0001E91C  80 C3 00 08 */	lwz r6, 8(r3)
/* 80021D40 0001E920  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80021D44 0001E924  38 C6 FF FF */	addi r6, r6, -1
/* 80021D48 0001E928  C8 42 83 C0 */	lfd f2, lbl_804D7DA0@sda21(r2)
/* 80021D4C 0001E92C  38 03 FF FF */	addi r0, r3, -1
/* 80021D50 0001E930  90 C1 00 3C */	stw r6, 0x3c(r1)
/* 80021D54 0001E934  C0 62 83 90 */	lfs f3, lbl_804D7D70@sda21(r2)
/* 80021D58 0001E938  90 01 00 34 */	stw r0, 0x34(r1)
/* 80021D5C 0001E93C  C2 A2 83 B0 */	lfs f21, lbl_804D7D90@sda21(r2)
/* 80021D60 0001E940  90 A1 00 38 */	stw r5, 0x38(r1)
/* 80021D64 0001E944  C3 42 83 94 */	lfs f26, lbl_804D7D74@sda21(r2)
/* 80021D68 0001E948  90 A1 00 30 */	stw r5, 0x30(r1)
/* 80021D6C 0001E94C  C8 21 00 38 */	lfd f1, 0x38(r1)
/* 80021D70 0001E950  C8 01 00 30 */	lfd f0, 0x30(r1)
/* 80021D74 0001E954  EC 21 10 28 */	fsubs f1, f1, f2
/* 80021D78 0001E958  C3 A2 83 98 */	lfs f29, lbl_804D7D78@sda21(r2)
/* 80021D7C 0001E95C  EC 00 10 28 */	fsubs f0, f0, f2
/* 80021D80 0001E960  CB C2 83 A0 */	lfd f30, lbl_804D7D80@sda21(r2)
/* 80021D84 0001E964  CB E2 83 A8 */	lfd f31, lbl_804D7D88@sda21(r2)
/* 80021D88 0001E968  EF 83 08 24 */	fdivs f28, f3, f1
/* 80021D8C 0001E96C  C2 C2 83 B8 */	lfs f22, lbl_804D7D98@sda21(r2)
/* 80021D90 0001E970  C2 E2 83 B4 */	lfs f23, lbl_804D7D94@sda21(r2)
/* 80021D94 0001E974  EF 63 00 24 */	fdivs f27, f3, f0
/* 80021D98 0001E978  48 00 01 3C */	b lbl_80021ED4
lbl_80021D9C:
/* 80021D9C 0001E97C  EF 1A 06 B2 */	fmuls f24, f26, f26
/* 80021DA0 0001E980  C3 22 83 94 */	lfs f25, lbl_804D7D74@sda21(r2)
/* 80021DA4 0001E984  3B 60 00 00 */	li r27, 0
/* 80021DA8 0001E988  48 00 01 18 */	b lbl_80021EC0
lbl_80021DAC:
/* 80021DAC 0001E98C  EC 59 C6 7A */	fmadds f2, f25, f25, f24
/* 80021DB0 0001E990  FC 02 E8 40 */	fcmpo cr0, f2, f29
/* 80021DB4 0001E994  40 81 00 48 */	ble lbl_80021DFC
/* 80021DB8 0001E998  FC 20 10 34 */	frsqrte f1, f2
/* 80021DBC 0001E99C  FC 01 00 72 */	fmul f0, f1, f1
/* 80021DC0 0001E9A0  FC 3E 00 72 */	fmul f1, f30, f1
/* 80021DC4 0001E9A4  FC 02 F8 3C */	fnmsub f0, f2, f0, f31
/* 80021DC8 0001E9A8  FC 21 00 32 */	fmul f1, f1, f0
/* 80021DCC 0001E9AC  FC 01 00 72 */	fmul f0, f1, f1
/* 80021DD0 0001E9B0  FC 3E 00 72 */	fmul f1, f30, f1
/* 80021DD4 0001E9B4  FC 02 F8 3C */	fnmsub f0, f2, f0, f31
/* 80021DD8 0001E9B8  FC 21 00 32 */	fmul f1, f1, f0
/* 80021DDC 0001E9BC  FC 01 00 72 */	fmul f0, f1, f1
/* 80021DE0 0001E9C0  FC 3E 00 72 */	fmul f1, f30, f1
/* 80021DE4 0001E9C4  FC 02 F8 3C */	fnmsub f0, f2, f0, f31
/* 80021DE8 0001E9C8  FC 01 00 32 */	fmul f0, f1, f0
/* 80021DEC 0001E9CC  FC 02 00 32 */	fmul f0, f2, f0
/* 80021DF0 0001E9D0  FC 00 00 18 */	frsp f0, f0
/* 80021DF4 0001E9D4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80021DF8 0001E9D8  C0 41 00 18 */	lfs f2, 0x18(r1)
lbl_80021DFC:
/* 80021DFC 0001E9DC  FC 02 A8 40 */	fcmpo cr0, f2, f21
/* 80021E00 0001E9E0  FE 60 10 90 */	fmr f19, f2
/* 80021E04 0001E9E4  40 81 00 08 */	ble lbl_80021E0C
/* 80021E08 0001E9E8  FE 60 A8 90 */	fmr f19, f21
lbl_80021E0C:
/* 80021E0C 0001E9EC  80 6D AD 48 */	lwz r3, skip8_804D63E8@sda21(r13)
/* 80021E10 0001E9F0  80 03 00 04 */	lwz r0, 4(r3)
/* 80021E14 0001E9F4  7E 9D 04 2E */	lfsx f20, r29, r0
/* 80021E18 0001E9F8  FC 14 E8 00 */	fcmpu cr0, f20, f29
/* 80021E1C 0001E9FC  41 82 00 34 */	beq lbl_80021E50
/* 80021E20 0001EA00  FC 00 9A 10 */	fabs f0, f19
/* 80021E24 0001EA04  FC 20 A2 10 */	fabs f1, f20
/* 80021E28 0001EA08  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80021E2C 0001EA0C  40 81 00 0C */	ble lbl_80021E38
/* 80021E30 0001EA10  FC 00 98 90 */	fmr f0, f19
/* 80021E34 0001EA14  48 00 00 14 */	b lbl_80021E48
lbl_80021E38:
/* 80021E38 0001EA18  EC 33 A0 24 */	fdivs f1, f19, f20
/* 80021E3C 0001EA1C  48 30 10 19 */	bl __cvt_dbl_usll
/* 80021E40 0001EA20  48 30 0F 61 */	bl __cvt_sll_flt
/* 80021E44 0001EA24  EC 14 98 7C */	fnmsubs f0, f20, f1, f19
lbl_80021E48:
/* 80021E48 0001EA28  EE 93 00 32 */	fmuls f20, f19, f0
/* 80021E4C 0001EA2C  48 00 00 08 */	b lbl_80021E54
lbl_80021E50:
/* 80021E50 0001EA30  FE 80 98 90 */	fmr f20, f19
lbl_80021E54:
/* 80021E54 0001EA34  80 6D AD 48 */	lwz r3, skip8_804D63E8@sda21(r13)
/* 80021E58 0001EA38  80 63 00 04 */	lwz r3, 4(r3)
/* 80021E5C 0001EA3C  38 03 00 04 */	addi r0, r3, 4
/* 80021E60 0001EA40  7C 1D 04 2E */	lfsx f0, r29, r0
/* 80021E64 0001EA44  EE 94 00 32 */	fmuls f20, f20, f0
/* 80021E68 0001EA48  FC 14 A8 40 */	fcmpo cr0, f20, f21
/* 80021E6C 0001EA4C  40 81 00 08 */	ble lbl_80021E74
/* 80021E70 0001EA50  FE 80 A8 90 */	fmr f20, f21
lbl_80021E74:
/* 80021E74 0001EA54  EC 1A 05 32 */	fmuls f0, f26, f20
/* 80021E78 0001EA58  EC 36 B8 3A */	fmadds f1, f22, f0, f23
/* 80021E7C 0001EA5C  48 30 0A 45 */	bl __cvt_fp2unsigned
/* 80021E80 0001EA60  EC 19 05 32 */	fmuls f0, f25, f20
/* 80021E84 0001EA64  7C 7E 1B 78 */	mr r30, r3
/* 80021E88 0001EA68  EC 36 B8 3A */	fmadds f1, f22, f0, f23
/* 80021E8C 0001EA6C  48 30 0A 35 */	bl __cvt_fp2unsigned
/* 80021E90 0001EA70  81 9F 00 18 */	lwz r12, 0x18(r31)
/* 80021E94 0001EA74  39 23 00 00 */	addi r9, r3, 0
/* 80021E98 0001EA78  38 7F 00 00 */	addi r3, r31, 0
/* 80021E9C 0001EA7C  7D 88 03 A6 */	mtlr r12
/* 80021EA0 0001EA80  38 9B 00 00 */	addi r4, r27, 0
/* 80021EA4 0001EA84  38 BC 00 00 */	addi r5, r28, 0
/* 80021EA8 0001EA88  39 1E 00 00 */	addi r8, r30, 0
/* 80021EAC 0001EA8C  38 C0 00 00 */	li r6, 0
/* 80021EB0 0001EA90  38 E0 00 00 */	li r7, 0
/* 80021EB4 0001EA94  4E 80 00 21 */	blrl 
/* 80021EB8 0001EA98  EF 39 E0 2A */	fadds f25, f25, f28
/* 80021EBC 0001EA9C  3B 7B 00 01 */	addi r27, r27, 1
lbl_80021EC0:
/* 80021EC0 0001EAA0  80 1F 00 08 */	lwz r0, 8(r31)
/* 80021EC4 0001EAA4  7C 1B 00 40 */	cmplw r27, r0
/* 80021EC8 0001EAA8  41 80 FE E4 */	blt lbl_80021DAC
/* 80021ECC 0001EAAC  EF 5A D8 2A */	fadds f26, f26, f27
/* 80021ED0 0001EAB0  3B 9C 00 01 */	addi r28, r28, 1
lbl_80021ED4:
/* 80021ED4 0001EAB4  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80021ED8 0001EAB8  7C 1C 00 40 */	cmplw r28, r0
/* 80021EDC 0001EABC  41 80 FE C0 */	blt lbl_80021D9C
/* 80021EE0 0001EAC0  80 7F 00 00 */	lwz r3, 0(r31)
/* 80021EE4 0001EAC4  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80021EE8 0001EAC8  48 32 29 25 */	bl DCFlushRange
/* 80021EEC 0001EACC  BB 61 00 44 */	lmw r27, 0x44(r1)
/* 80021EF0 0001EAD0  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 80021EF4 0001EAD4  CB E1 00 B8 */	lfd f31, 0xb8(r1)
/* 80021EF8 0001EAD8  CB C1 00 B0 */	lfd f30, 0xb0(r1)
/* 80021EFC 0001EADC  CB A1 00 A8 */	lfd f29, 0xa8(r1)
/* 80021F00 0001EAE0  CB 81 00 A0 */	lfd f28, 0xa0(r1)
/* 80021F04 0001EAE4  CB 61 00 98 */	lfd f27, 0x98(r1)
/* 80021F08 0001EAE8  CB 41 00 90 */	lfd f26, 0x90(r1)
/* 80021F0C 0001EAEC  CB 21 00 88 */	lfd f25, 0x88(r1)
/* 80021F10 0001EAF0  CB 01 00 80 */	lfd f24, 0x80(r1)
/* 80021F14 0001EAF4  CA E1 00 78 */	lfd f23, 0x78(r1)
/* 80021F18 0001EAF8  CA C1 00 70 */	lfd f22, 0x70(r1)
/* 80021F1C 0001EAFC  CA A1 00 68 */	lfd f21, 0x68(r1)
/* 80021F20 0001EB00  CA 81 00 60 */	lfd f20, 0x60(r1)
/* 80021F24 0001EB04  CA 61 00 58 */	lfd f19, 0x58(r1)
/* 80021F28 0001EB08  38 21 00 C0 */	addi r1, r1, 0xc0
/* 80021F2C 0001EB0C  7C 08 03 A6 */	mtlr r0
/* 80021F30 0001EB10  4E 80 00 20 */	blr 

# https://decomp.me/scratch/VElQJ
callback_80021F34:
/* 80021F34 0001EB14  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80021F38 0001EB18  54 A6 F0 BE */	srwi r6, r5, 2
/* 80021F3C 0001EB1C  80 E3 00 00 */	lwz r7, 0(r3)
/* 80021F40 0001EB20  7C 66 01 D6 */	mullw r3, r6, r0
/* 80021F44 0001EB24  54 80 18 34 */	rlwinm r0, r4, 3, 0, 0x1a
/* 80021F48 0001EB28  7C 63 02 14 */	add r3, r3, r0
/* 80021F4C 0001EB2C  54 84 07 BE */	clrlwi r4, r4, 0x1e
/* 80021F50 0001EB30  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 80021F54 0001EB34  7C 04 02 14 */	add r0, r4, r0
/* 80021F58 0001EB38  7C 67 1A 14 */	add r3, r7, r3
/* 80021F5C 0001EB3C  54 00 08 3C */	slwi r0, r0, 1
/* 80021F60 0001EB40  7D 23 01 AE */	stbx r9, r3, r0
/* 80021F64 0001EB44  7C 63 02 14 */	add r3, r3, r0
/* 80021F68 0001EB48  99 03 00 01 */	stb r8, 1(r3)
/* 80021F6C 0001EB4C  4E 80 00 20 */	blr

# https://decomp.me/scratch/xCKEK
callback_80021F70:
/* 80021F70 0001EB50  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80021F74 0001EB54  54 A9 F0 BE */	srwi r9, r5, 2
/* 80021F78 0001EB58  81 43 00 00 */	lwz r10, 0(r3)
/* 80021F7C 0001EB5C  7C 69 01 D6 */	mullw r3, r9, r0
/* 80021F80 0001EB60  54 80 18 34 */	rlwinm r0, r4, 3, 0, 0x1a
/* 80021F84 0001EB64  7D 23 02 14 */	add r9, r3, r0
/* 80021F88 0001EB68  54 83 07 BE */	clrlwi r3, r4, 0x1e
/* 80021F8C 0001EB6C  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 80021F90 0001EB70  7C 03 02 14 */	add r0, r3, r0
/* 80021F94 0001EB74  54 E3 1D 74 */	rlwinm r3, r7, 3, 0x15, 0x1a
/* 80021F98 0001EB78  55 04 E8 FE */	srwi r4, r8, 3
/* 80021F9C 0001EB7C  50 C3 44 28 */	rlwimi r3, r6, 8, 0x10, 0x14
/* 80021FA0 0001EB80  7D 2A 4A 14 */	add r9, r10, r9
/* 80021FA4 0001EB84  7C 83 1B 78 */	or r3, r4, r3
/* 80021FA8 0001EB88  54 00 08 3C */	slwi r0, r0, 1
/* 80021FAC 0001EB8C  7C 69 03 2E */	sthx r3, r9, r0
/* 80021FB0 0001EB90  4E 80 00 20 */	blr 

# https://decomp.me/scratch/sveP4
callback_80021FB4:
/* 80021FB4 0001EB94  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80021FB8 0001EB98  54 AA F0 BE */	srwi r10, r5, 2
/* 80021FBC 0001EB9C  81 63 00 00 */	lwz r11, 0(r3)
/* 80021FC0 0001EBA0  7C 6A 01 D6 */	mullw r3, r10, r0
/* 80021FC4 0001EBA4  54 80 20 32 */	rlwinm r0, r4, 4, 0, 0x19
/* 80021FC8 0001EBA8  7C 63 02 14 */	add r3, r3, r0
/* 80021FCC 0001EBAC  54 84 07 BE */	clrlwi r4, r4, 0x1e
/* 80021FD0 0001EBB0  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 80021FD4 0001EBB4  7C 04 02 14 */	add r0, r4, r0
/* 80021FD8 0001EBB8  7C 6B 1A 14 */	add r3, r11, r3
/* 80021FDC 0001EBBC  54 00 08 3C */	slwi r0, r0, 1
/* 80021FE0 0001EBC0  7D 23 01 AE */	stbx r9, r3, r0
/* 80021FE4 0001EBC4  7C 63 02 14 */	add r3, r3, r0
/* 80021FE8 0001EBC8  98 C3 00 01 */	stb r6, 1(r3)
/* 80021FEC 0001EBCC  98 E3 00 20 */	stb r7, 0x20(r3)
/* 80021FF0 0001EBD0  99 03 00 21 */	stb r8, 0x21(r3)
/* 80021FF4 0001EBD4  4E 80 00 20 */	blr 

# https://decomp.me/scratch/kcNXw
callback_80021FF8:
/* 80021FF8 0001EBD8  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80021FFC 0001EBDC  54 AA F0 BE */	srwi r10, r5, 2
/* 80022000 0001EBE0  81 63 00 00 */	lwz r11, 0(r3)
/* 80022004 0001EBE4  28 06 00 00 */	cmplwi r6, 0
/* 80022008 0001EBE8  7C 6A 01 D6 */	mullw r3, r10, r0
/* 8002200C 0001EBEC  54 80 18 34 */	rlwinm r0, r4, 3, 0, 0x1a
/* 80022010 0001EBF0  7D 43 02 14 */	add r10, r3, r0
/* 80022014 0001EBF4  54 83 07 BE */	clrlwi r3, r4, 0x1e
/* 80022018 0001EBF8  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 8002201C 0001EBFC  7C 03 02 14 */	add r0, r3, r0
/* 80022020 0001EC00  7D 4B 52 14 */	add r10, r11, r10
/* 80022024 0001EC04  54 04 08 3C */	slwi r4, r0, 1
/* 80022028 0001EC08  41 82 00 0C */	beq lbl_80022034
/* 8002202C 0001EC0C  38 00 00 FF */	li r0, 0xff
/* 80022030 0001EC10  90 06 00 00 */	stw r0, 0(r6)
lbl_80022034:
/* 80022034 0001EC14  28 07 00 00 */	cmplwi r7, 0
/* 80022038 0001EC18  41 82 00 0C */	beq lbl_80022044
/* 8002203C 0001EC1C  38 00 00 FF */	li r0, 0xff
/* 80022040 0001EC20  90 07 00 00 */	stw r0, 0(r7)
lbl_80022044:
/* 80022044 0001EC24  28 08 00 00 */	cmplwi r8, 0
/* 80022048 0001EC28  41 82 00 10 */	beq lbl_80022058
/* 8002204C 0001EC2C  7C 6A 22 14 */	add r3, r10, r4
/* 80022050 0001EC30  88 03 00 01 */	lbz r0, 1(r3)
/* 80022054 0001EC34  90 08 00 00 */	stw r0, 0(r8)
lbl_80022058:
/* 80022058 0001EC38  28 09 00 00 */	cmplwi r9, 0
/* 8002205C 0001EC3C  4D 82 00 20 */	beqlr 
/* 80022060 0001EC40  7C 0A 20 AE */	lbzx r0, r10, r4
/* 80022064 0001EC44  90 09 00 00 */	stw r0, 0(r9)
/* 80022068 0001EC48  4E 80 00 20 */	blr 

# https://decomp.me/scratch/ZzShG
callback_8002206C:
/* 8002206C 0001EC4C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80022070 0001EC50  54 AA F0 BE */	srwi r10, r5, 2
/* 80022074 0001EC54  81 63 00 00 */	lwz r11, 0(r3)
/* 80022078 0001EC58  28 09 00 00 */	cmplwi r9, 0
/* 8002207C 0001EC5C  7C 6A 01 D6 */	mullw r3, r10, r0
/* 80022080 0001EC60  54 80 18 34 */	rlwinm r0, r4, 3, 0, 0x1a
/* 80022084 0001EC64  7C 63 02 14 */	add r3, r3, r0
/* 80022088 0001EC68  54 84 07 BE */	clrlwi r4, r4, 0x1e
/* 8002208C 0001EC6C  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 80022090 0001EC70  7C 04 02 14 */	add r0, r4, r0
/* 80022094 0001EC74  7C 6B 1A 14 */	add r3, r11, r3
/* 80022098 0001EC78  54 00 08 3C */	slwi r0, r0, 1
/* 8002209C 0001EC7C  7C 83 02 2E */	lhzx r4, r3, r0
/* 800220A0 0001EC80  41 82 00 0C */	beq lbl_800220AC
/* 800220A4 0001EC84  38 00 00 FF */	li r0, 0xff
/* 800220A8 0001EC88  90 09 00 00 */	stw r0, 0(r9)
lbl_800220AC:
/* 800220AC 0001EC8C  28 06 00 00 */	cmplwi r6, 0
/* 800220B0 0001EC90  41 82 00 24 */	beq lbl_800220D4
/* 800220B4 0001EC94  54 83 C6 38 */	rlwinm r3, r4, 0x18, 0x18, 0x1c
/* 800220B8 0001EC98  54 80 04 20 */	rlwinm r0, r4, 0, 0x10, 0x10
/* 800220BC 0001EC9C  7C 60 03 79 */	or. r0, r3, r0
/* 800220C0 0001ECA0  41 82 00 0C */	beq lbl_800220CC
/* 800220C4 0001ECA4  38 00 00 07 */	li r0, 7
/* 800220C8 0001ECA8  48 00 00 08 */	b lbl_800220D0
lbl_800220CC:
/* 800220CC 0001ECAC  38 00 00 00 */	li r0, 0
lbl_800220D0:
/* 800220D0 0001ECB0  90 06 00 00 */	stw r0, 0(r6)
lbl_800220D4:
/* 800220D4 0001ECB4  28 07 00 00 */	cmplwi r7, 0
/* 800220D8 0001ECB8  41 82 00 24 */	beq lbl_800220FC
/* 800220DC 0001ECBC  54 83 EE 3A */	rlwinm r3, r4, 0x1d, 0x18, 0x1d
/* 800220E0 0001ECC0  54 80 05 6A */	rlwinm r0, r4, 0, 0x15, 0x15
/* 800220E4 0001ECC4  7C 60 03 79 */	or. r0, r3, r0
/* 800220E8 0001ECC8  41 82 00 0C */	beq lbl_800220F4
/* 800220EC 0001ECCC  38 00 00 03 */	li r0, 3
/* 800220F0 0001ECD0  48 00 00 08 */	b lbl_800220F8
lbl_800220F4:
/* 800220F4 0001ECD4  38 00 00 00 */	li r0, 0
lbl_800220F8:
/* 800220F8 0001ECD8  90 07 00 00 */	stw r0, 0(r7)
lbl_800220FC:
/* 800220FC 0001ECDC  28 08 00 00 */	cmplwi r8, 0
/* 80022100 0001ECE0  4D 82 00 20 */	beqlr 
/* 80022104 0001ECE4  54 80 06 39 */	rlwinm. r0, r4, 0, 0x18, 0x1c
/* 80022108 0001ECE8  41 82 00 0C */	beq lbl_80022114
/* 8002210C 0001ECEC  38 00 00 07 */	li r0, 7
/* 80022110 0001ECF0  48 00 00 08 */	b lbl_80022118
lbl_80022114:
/* 80022114 0001ECF4  38 00 00 00 */	li r0, 0
lbl_80022118:
/* 80022118 0001ECF8  90 08 00 00 */	stw r0, 0(r8)
/* 8002211C 0001ECFC  4E 80 00 20 */	blr

# https://decomp.me/scratch/K9xQ4
callback_80022120:
/* 80022120 0001ED00  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80022124 0001ED04  54 AA F0 BE */	srwi r10, r5, 2
/* 80022128 0001ED08  81 63 00 00 */	lwz r11, 0(r3)
/* 8002212C 0001ED0C  28 09 00 00 */	cmplwi r9, 0
/* 80022130 0001ED10  7C 6A 01 D6 */	mullw r3, r10, r0
/* 80022134 0001ED14  54 80 20 32 */	rlwinm r0, r4, 4, 0, 0x19
/* 80022138 0001ED18  7D 43 02 14 */	add r10, r3, r0
/* 8002213C 0001ED1C  54 83 07 BE */	clrlwi r3, r4, 0x1e
/* 80022140 0001ED20  54 A0 17 3A */	rlwinm r0, r5, 2, 0x1c, 0x1d
/* 80022144 0001ED24  7C 03 02 14 */	add r0, r3, r0
/* 80022148 0001ED28  7D 4B 52 14 */	add r10, r11, r10
/* 8002214C 0001ED2C  54 04 08 3C */	slwi r4, r0, 1
/* 80022150 0001ED30  41 82 00 0C */	beq lbl_8002215C
/* 80022154 0001ED34  7C 0A 20 AE */	lbzx r0, r10, r4
/* 80022158 0001ED38  90 09 00 00 */	stw r0, 0(r9)
lbl_8002215C:
/* 8002215C 0001ED3C  28 06 00 00 */	cmplwi r6, 0
/* 80022160 0001ED40  41 82 00 10 */	beq lbl_80022170
/* 80022164 0001ED44  7C 6A 22 14 */	add r3, r10, r4
/* 80022168 0001ED48  88 03 00 01 */	lbz r0, 1(r3)
/* 8002216C 0001ED4C  90 06 00 00 */	stw r0, 0(r6)
lbl_80022170:
/* 80022170 0001ED50  28 07 00 00 */	cmplwi r7, 0
/* 80022174 0001ED54  41 82 00 10 */	beq lbl_80022184
/* 80022178 0001ED58  7C 6A 22 14 */	add r3, r10, r4
/* 8002217C 0001ED5C  88 03 00 20 */	lbz r0, 0x20(r3)
/* 80022180 0001ED60  90 07 00 00 */	stw r0, 0(r7)
lbl_80022184:
/* 80022184 0001ED64  28 08 00 00 */	cmplwi r8, 0
/* 80022188 0001ED68  4D 82 00 20 */	beqlr 
/* 8002218C 0001ED6C  7C 6A 22 14 */	add r3, r10, r4
/* 80022190 0001ED70  88 03 00 21 */	lbz r0, 0x21(r3)
/* 80022194 0001ED74  90 08 00 00 */	stw r0, 0(r8)
/* 80022198 0001ED78  4E 80 00 20 */	blr 

# https://decomp.me/scratch/MxVsy
.global local_8002219C
local_8002219C:
/* 8002219C 0001ED7C  7C 08 02 A6 */	mflr r0
/* 800221A0 0001ED80  90 01 00 04 */	stw r0, 4(r1)
/* 800221A4 0001ED84  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800221A8 0001ED88  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800221AC 0001ED8C  3B E6 00 00 */	addi r31, r6, 0
/* 800221B0 0001ED90  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800221B4 0001ED94  3B C5 00 00 */	addi r30, r5, 0
/* 800221B8 0001ED98  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800221BC 0001ED9C  7C 7D 1B 78 */	mr r29, r3
/* 800221C0 0001EDA0  90 83 00 00 */	stw r4, 0(r3)
/* 800221C4 0001EDA4  54 E4 04 3E */	clrlwi r4, r7, 0x10
/* 800221C8 0001EDA8  93 C3 00 04 */	stw r30, 4(r3)
/* 800221CC 0001EDAC  54 C3 04 3E */	clrlwi r3, r6, 0x10
/* 800221D0 0001EDB0  38 C0 00 00 */	li r6, 0
/* 800221D4 0001EDB4  93 FD 00 08 */	stw r31, 8(r29)
/* 800221D8 0001EDB8  90 FD 00 0C */	stw r7, 0xc(r29)
/* 800221DC 0001EDBC  38 E0 00 00 */	li r7, 0
/* 800221E0 0001EDC0  48 31 C5 AD */	bl GXGetTexBufferSize
/* 800221E4 0001EDC4  2C 1E 00 05 */	cmpwi r30, 5
/* 800221E8 0001EDC8  90 7D 00 14 */	stw r3, 0x14(r29)
/* 800221EC 0001EDCC  41 82 00 90 */	beq lbl_8002227C
/* 800221F0 0001EDD0  40 80 00 14 */	bge lbl_80022204
/* 800221F4 0001EDD4  2C 1E 00 03 */	cmpwi r30, 3
/* 800221F8 0001EDD8  41 82 00 18 */	beq lbl_80022210
/* 800221FC 0001EDDC  40 80 00 38 */	bge lbl_80022234
/* 80022200 0001EDE0  48 00 00 7C */	b lbl_8002227C
lbl_80022204:
/* 80022204 0001EDE4  2C 1E 00 07 */	cmpwi r30, 7
/* 80022208 0001EDE8  40 80 00 74 */	bge lbl_8002227C
/* 8002220C 0001EDEC  48 00 00 4C */	b lbl_80022258
lbl_80022210:
/* 80022210 0001EDF0  3C 60 80 02 */	lis r3, callback_80021F34@ha
/* 80022214 0001EDF4  38 03 1F 34 */	addi r0, r3, callback_80021F34@l
/* 80022218 0001EDF8  3C 60 80 02 */	lis r3, callback_80021FF8@ha
/* 8002221C 0001EDFC  90 1D 00 18 */	stw r0, 0x18(r29)
/* 80022220 0001EE00  38 03 1F F8 */	addi r0, r3, callback_80021FF8@l
/* 80022224 0001EE04  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 80022228 0001EE08  57 E0 18 34 */	rlwinm r0, r31, 3, 0, 0x1a
/* 8002222C 0001EE0C  90 1D 00 10 */	stw r0, 0x10(r29)
/* 80022230 0001EE10  48 00 00 54 */	b lbl_80022284
lbl_80022234:
/* 80022234 0001EE14  3C 60 80 02 */	lis r3, callback_80021F70@ha
/* 80022238 0001EE18  38 03 1F 70 */	addi r0, r3, callback_80021F70@l
/* 8002223C 0001EE1C  3C 60 80 02 */	lis r3, callback_8002206C@ha
/* 80022240 0001EE20  90 1D 00 18 */	stw r0, 0x18(r29)
/* 80022244 0001EE24  38 03 20 6C */	addi r0, r3, callback_8002206C@l
/* 80022248 0001EE28  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 8002224C 0001EE2C  57 E0 18 34 */	rlwinm r0, r31, 3, 0, 0x1a
/* 80022250 0001EE30  90 1D 00 10 */	stw r0, 0x10(r29)
/* 80022254 0001EE34  48 00 00 30 */	b lbl_80022284
lbl_80022258:
/* 80022258 0001EE38  3C 60 80 02 */	lis r3, callback_80021FB4@ha
/* 8002225C 0001EE3C  38 03 1F B4 */	addi r0, r3, callback_80021FB4@l
/* 80022260 0001EE40  3C 60 80 02 */	lis r3, callback_80022120@ha
/* 80022264 0001EE44  90 1D 00 18 */	stw r0, 0x18(r29)
/* 80022268 0001EE48  38 03 21 20 */	addi r0, r3, callback_80022120@l
/* 8002226C 0001EE4C  90 1D 00 1C */	stw r0, 0x1c(r29)
/* 80022270 0001EE50  57 E0 20 32 */	rlwinm r0, r31, 4, 0, 0x19
/* 80022274 0001EE54  90 1D 00 10 */	stw r0, 0x10(r29)
/* 80022278 0001EE58  48 00 00 0C */	b lbl_80022284
lbl_8002227C:
/* 8002227C 0001EE5C  38 60 FF FF */	li r3, -1
/* 80022280 0001EE60  48 00 00 08 */	b lbl_80022288
lbl_80022284:
/* 80022284 0001EE64  38 60 00 00 */	li r3, 0
lbl_80022288:
/* 80022288 0001EE68  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8002228C 0001EE6C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80022290 0001EE70  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80022294 0001EE74  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80022298 0001EE78  38 21 00 30 */	addi r1, r1, 0x30
/* 8002229C 0001EE7C  7C 08 03 A6 */	mtlr r0
/* 800222A0 0001EE80  4E 80 00 20 */	blr 
