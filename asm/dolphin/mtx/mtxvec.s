.include "macros.inc"

.section .text  # 0x80342AA8 - 0x80342B4C

.global PSMTXMultVec
PSMTXMultVec:
/* 80342AA8 0033F688  E0 04 00 00 */	psq_l f0, 0(r4), 0, qr0
/* 80342AAC 0033F68C  E0 43 00 00 */	psq_l f2, 0(r3), 0, qr0
/* 80342AB0 0033F690  E0 24 80 08 */	psq_l f1, 8(r4), 1, qr0
/* 80342AB4 0033F694  10 82 00 32 */	ps_mul f4, f2, f0
/* 80342AB8 0033F698  E0 63 00 08 */	psq_l f3, 8(r3), 0, qr0
/* 80342ABC 0033F69C  10 A3 20 7A */	ps_madd f5, f3, f1, f4
/* 80342AC0 0033F6A0  E1 03 00 10 */	psq_l f8, 16(r3), 0, qr0
/* 80342AC4 0033F6A4  10 C5 29 94 */	ps_sum0 f6, f5, f6, f5
/* 80342AC8 0033F6A8  E1 23 00 18 */	psq_l f9, 24(r3), 0, qr0
/* 80342ACC 0033F6AC  11 48 00 32 */	ps_mul f10, f8, f0
/* 80342AD0 0033F6B0  F0 C5 80 00 */	psq_st f6, 0(r5), 1, qr0
/* 80342AD4 0033F6B4  11 69 50 7A */	ps_madd f11, f9, f1, f10
/* 80342AD8 0033F6B8  E0 43 00 20 */	psq_l f2, 32(r3), 0, qr0
/* 80342ADC 0033F6BC  11 8B 5B 14 */	ps_sum0 f12, f11, f12, f11
/* 80342AE0 0033F6C0  E0 63 00 28 */	psq_l f3, 40(r3), 0, qr0
/* 80342AE4 0033F6C4  10 82 00 32 */	ps_mul f4, f2, f0
/* 80342AE8 0033F6C8  F1 85 80 04 */	psq_st f12, 4(r5), 1, qr0
/* 80342AEC 0033F6CC  10 A3 20 7A */	ps_madd f5, f3, f1, f4
/* 80342AF0 0033F6D0  10 C5 29 94 */	ps_sum0 f6, f5, f6, f5
/* 80342AF4 0033F6D4  F0 C5 80 08 */	psq_st f6, 8(r5), 1, qr0
/* 80342AF8 0033F6D8  4E 80 00 20 */	blr

.global PSMTXMultVecSR
PSMTXMultVecSR:
/* 80342AFC 0033F6DC  E0 03 00 00 */	psq_l f0, 0(r3), 0, qr0
/* 80342B00 0033F6E0  E0 C4 00 00 */	psq_l f6, 0(r4), 0, qr0
/* 80342B04 0033F6E4  E0 43 00 10 */	psq_l f2, 16(r3), 0, qr0
/* 80342B08 0033F6E8  11 00 01 B2 */	ps_mul f8, f0, f6
/* 80342B0C 0033F6EC  E0 83 00 20 */	psq_l f4, 32(r3), 0, qr0
/* 80342B10 0033F6F0  11 42 01 B2 */	ps_mul f10, f2, f6
/* 80342B14 0033F6F4  E0 E4 80 08 */	psq_l f7, 8(r4), 1, qr0
/* 80342B18 0033F6F8  11 84 01 B2 */	ps_mul f12, f4, f6
/* 80342B1C 0033F6FC  E0 63 00 18 */	psq_l f3, 24(r3), 0, qr0
/* 80342B20 0033F700  11 08 42 14 */	ps_sum0 f8, f8, f8, f8
/* 80342B24 0033F704  E0 A3 00 28 */	psq_l f5, 40(r3), 0, qr0
/* 80342B28 0033F708  11 4A 52 94 */	ps_sum0 f10, f10, f10, f10
/* 80342B2C 0033F70C  E0 23 00 08 */	psq_l f1, 8(r3), 0, qr0
/* 80342B30 0033F710  11 8C 63 14 */	ps_sum0 f12, f12, f12, f12
/* 80342B34 0033F714  11 21 41 FA */	ps_madd f9, f1, f7, f8
/* 80342B38 0033F718  F1 25 80 00 */	psq_st f9, 0(r5), 1, qr0
/* 80342B3C 0033F71C  11 63 51 FA */	ps_madd f11, f3, f7, f10
/* 80342B40 0033F720  F1 65 80 04 */	psq_st f11, 4(r5), 1, qr0
/* 80342B44 0033F724  11 A5 61 FA */	ps_madd f13, f5, f7, f12
/* 80342B48 0033F728  F1 A5 80 08 */	psq_st f13, 8(r5), 1, qr0
/* 80342B4C 0033F72C  4E 80 00 20 */	blr
