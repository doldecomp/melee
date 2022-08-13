.include "macros.inc"

.section .text  # 0x80342D54 - 0x80342E90

.global PSVECAdd
PSVECAdd:
/* 80342D54 0033F934  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 80342D58 0033F938  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 80342D5C 0033F93C  10 C2 20 2A */	ps_add f6, f2, f4
/* 80342D60 0033F940  F0 C5 00 00 */	psq_st f6, 0(r5), 0, qr0
/* 80342D64 0033F944  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 80342D68 0033F948  E0 A4 80 08 */	psq_l f5, 8(r4), 1, qr0
/* 80342D6C 0033F94C  10 E3 28 2A */	ps_add f7, f3, f5
/* 80342D70 0033F950  F0 E5 80 08 */	psq_st f7, 8(r5), 1, qr0
/* 80342D74 0033F954  4E 80 00 20 */	blr 

.global PSVECSubtract
PSVECSubtract:
/* 80342D78 0033F958  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 80342D7C 0033F95C  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 80342D80 0033F960  10 C2 20 28 */	ps_sub f6, f2, f4
/* 80342D84 0033F964  F0 C5 00 00 */	psq_st f6, 0(r5), 0, qr0
/* 80342D88 0033F968  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 80342D8C 0033F96C  E0 A4 80 08 */	psq_l f5, 8(r4), 1, qr0
/* 80342D90 0033F970  10 E3 28 28 */	ps_sub f7, f3, f5
/* 80342D94 0033F974  F0 E5 80 08 */	psq_st f7, 8(r5), 1, qr0
/* 80342D98 0033F978  4E 80 00 20 */	blr 

.global PSVECScale
PSVECScale:
/* 80342D9C 0033F97C  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80342DA0 0033F980  E0 43 80 08 */	psq_l f2, 8(r3), 1, qr0
/* 80342DA4 0033F984  10 00 00 58 */	ps_muls0 f0, f0, f1
/* 80342DA8 0033F988  F0 04 00 00 */	psq_st f0, 0(r4), 0, qr0
/* 80342DAC 0033F98C  10 02 00 58 */	ps_muls0 f0, f2, f1
/* 80342DB0 0033F990  F0 04 80 08 */	psq_st f0, 8(r4), 1, qr0
/* 80342DB4 0033F994  4E 80 00 20 */	blr 

.global PSVECNormalize
PSVECNormalize:
/* 80342DB8 0033F998  C0 02 E9 60 */	lfs f0, lbl_804DE340@sda21(r2)
/* 80342DBC 0033F99C  C0 22 E9 64 */	lfs f1, lbl_804DE344@sda21(r2)
/* 80342DC0 0033F9A0  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 80342DC4 0033F9A4  10 A2 00 B2 */	ps_mul f5, f2, f2
/* 80342DC8 0033F9A8  E0 63 80 08 */	psq_l f3, 8(r3), 1, qr0
/* 80342DCC 0033F9AC  10 83 28 FA */	ps_madd f4, f3, f3, f5
/* 80342DD0 0033F9B0  10 84 28 D4 */	ps_sum0 f4, f4, f3, f5
/* 80342DD4 0033F9B4  FC A0 20 34 */	frsqrte f5, f4
/* 80342DD8 0033F9B8  EC C5 01 72 */	fmuls f6, f5, f5
/* 80342DDC 0033F9BC  EC 05 00 32 */	fmuls f0, f5, f0
/* 80342DE0 0033F9C0  EC C6 09 3C */	fnmsubs f6, f6, f4, f1
/* 80342DE4 0033F9C4  EC A6 00 32 */	fmuls f5, f6, f0
/* 80342DE8 0033F9C8  10 42 01 58 */	ps_muls0 f2, f2, f5
/* 80342DEC 0033F9CC  F0 44 00 00 */	psq_st f2, 0(r4), 0, qr0
/* 80342DF0 0033F9D0  10 63 01 58 */	ps_muls0 f3, f3, f5
/* 80342DF4 0033F9D4  F0 64 80 08 */	psq_st f3, 8(r4), 1, qr0
/* 80342DF8 0033F9D8  4E 80 00 20 */	blr 

.global PSVECMag
PSVECMag:
/* 80342DFC 0033F9DC  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80342E00 0033F9E0  10 00 00 32 */	ps_mul f0, f0, f0
/* 80342E04 0033F9E4  C0 23 00 08 */	lfs f1, 8(r3)
/* 80342E08 0033F9E8  10 21 00 7A */	ps_madd f1, f1, f1, f0
/* 80342E0C 0033F9EC  C0 82 E9 60 */	lfs f4, lbl_804DE340@sda21(r2)
/* 80342E10 0033F9F0  10 21 00 14 */	ps_sum0 f1, f1, f0, f0
/* 80342E14 0033F9F4  FC 00 08 34 */	frsqrte f0, f1
/* 80342E18 0033F9F8  C0 62 E9 64 */	lfs f3, lbl_804DE344@sda21(r2)
/* 80342E1C 0033F9FC  EC 40 00 32 */	fmuls f2, f0, f0
/* 80342E20 0033FA00  EC 00 01 32 */	fmuls f0, f0, f4
/* 80342E24 0033FA04  EC 42 18 7C */	fnmsubs f2, f2, f1, f3
/* 80342E28 0033FA08  EC 02 00 32 */	fmuls f0, f2, f0
/* 80342E2C 0033FA0C  FC 00 08 2E */	fsel f0, f0, f0, f1
/* 80342E30 0033FA10  EC 21 00 32 */	fmuls f1, f1, f0
/* 80342E34 0033FA14  4E 80 00 20 */	blr 

.global PSVECDotProduct
PSVECDotProduct:
/* 80342E38 0033FA18  E0 43 00 04 */	psq_l f2, 4(r3), 0, qr0
/* 80342E3C 0033FA1C  E0 64 00 04 */	psq_l f3, 4(r4), 0, qr0
/* 80342E40 0033FA20  10 42 00 F2 */	ps_mul f2, f2, f3
/* 80342E44 0033FA24  E0 A3 00 00 */	psq_l f5, 0(r3), 0, qr0
/* 80342E48 0033FA28  E0 84 00 00 */	psq_l f4, 0(r4), 0, qr0
/* 80342E4C 0033FA2C  10 65 11 3A */	ps_madd f3, f5, f4, f2
/* 80342E50 0033FA30  10 23 10 94 */	ps_sum0 f1, f3, f2, f2
/* 80342E54 0033FA34  4E 80 00 20 */	blr 

.global PSVECCrossProduct
PSVECCrossProduct:
/* 80342E58 0033FA38  E0 24 00 00 */	psq_l f1, 0(r4), 0, qr0
/* 80342E5C 0033FA3C  C0 43 00 08 */	lfs f2, 8(r3)
/* 80342E60 0033FA40  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80342E64 0033FA44  10 C1 0C A0 */	ps_merge10 f6, f1, f1
/* 80342E68 0033FA48  C0 64 00 08 */	lfs f3, 8(r4)
/* 80342E6C 0033FA4C  10 81 00 B2 */	ps_mul f4, f1, f2
/* 80342E70 0033FA50  10 E1 00 18 */	ps_muls0 f7, f1, f0
/* 80342E74 0033FA54  10 A0 20 F8 */	ps_msub f5, f0, f3, f4
/* 80342E78 0033FA58  11 00 39 B8 */	ps_msub f8, f0, f6, f7
/* 80342E7C 0033FA5C  11 25 2C E0 */	ps_merge11 f9, f5, f5
/* 80342E80 0033FA60  11 45 44 60 */	ps_merge01 f10, f5, f8
/* 80342E84 0033FA64  F1 25 80 00 */	psq_st f9, 0(r5), 1, qr0
/* 80342E88 0033FA68  11 40 50 50 */	ps_neg f10, f10
/* 80342E8C 0033FA6C  F1 45 00 04 */	psq_st f10, 4(r5), 0, qr0
/* 80342E90 0033FA70  4E 80 00 20 */	blr 


.section .sdata2
    .balign 8
.global lbl_804DE340
lbl_804DE340:
	.4byte 0x3F000000
.global lbl_804DE344
lbl_804DE344:
	.4byte 0x40400000
