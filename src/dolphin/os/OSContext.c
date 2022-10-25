#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSInterrupt.h>

#pragma push
asm unk_t __OSLoadFPUContext()
{ // clang-format off
    nofralloc
/* 80344E30 00341A10  A0 A4 01 A2 */	lhz r5, 0x1a2(r4)
/* 80344E34 00341A14  54 A5 07 FF */	clrlwi. r5, r5, 0x1f
/* 80344E38 00341A18  41 82 01 18 */	beq lbl_80344F50
/* 80344E3C 00341A1C  C8 04 01 90 */	lfd f0, 0x190(r4)
/* 80344E40 00341A20  FD FE 05 8E */	mtfsf 0xff, f0
/* 80344E44 00341A24  7C B8 E2 A6 */	mfspr r5, 0x398
/* 80344E48 00341A28  54 A5 1F FF */	rlwinm. r5, r5, 3, 0x1f, 0x1f
/* 80344E4C 00341A2C  41 82 00 84 */	beq lbl_80344ED0
/* 80344E50 00341A30  E0 04 01 C8 */	psq_l f0, 456(r4), 0, qr0
/* 80344E54 00341A34  E0 24 01 D0 */	psq_l f1, 464(r4), 0, qr0
/* 80344E58 00341A38  E0 44 01 D8 */	psq_l f2, 472(r4), 0, qr0
/* 80344E5C 00341A3C  E0 64 01 E0 */	psq_l f3, 480(r4), 0, qr0
/* 80344E60 00341A40  E0 84 01 E8 */	psq_l f4, 488(r4), 0, qr0
/* 80344E64 00341A44  E0 A4 01 F0 */	psq_l f5, 496(r4), 0, qr0
/* 80344E68 00341A48  E0 C4 01 F8 */	psq_l f6, 504(r4), 0, qr0
/* 80344E6C 00341A4C  E0 E4 02 00 */	psq_l f7, 512(r4), 0, qr0
/* 80344E70 00341A50  E1 04 02 08 */	psq_l f8, 520(r4), 0, qr0
/* 80344E74 00341A54  E1 24 02 10 */	psq_l f9, 528(r4), 0, qr0
/* 80344E78 00341A58  E1 44 02 18 */	psq_l f10, 536(r4), 0, qr0
/* 80344E7C 00341A5C  E1 64 02 20 */	psq_l f11, 544(r4), 0, qr0
/* 80344E80 00341A60  E1 84 02 28 */	psq_l f12, 552(r4), 0, qr0
/* 80344E84 00341A64  E1 A4 02 30 */	psq_l f13, 560(r4), 0, qr0
/* 80344E88 00341A68  E1 C4 02 38 */	psq_l f14, 568(r4), 0, qr0
/* 80344E8C 00341A6C  E1 E4 02 40 */	psq_l f15, 576(r4), 0, qr0
/* 80344E90 00341A70  E2 04 02 48 */	psq_l f16, 584(r4), 0, qr0
/* 80344E94 00341A74  E2 24 02 50 */	psq_l f17, 592(r4), 0, qr0
/* 80344E98 00341A78  E2 44 02 58 */	psq_l f18, 600(r4), 0, qr0
/* 80344E9C 00341A7C  E2 64 02 60 */	psq_l f19, 608(r4), 0, qr0
/* 80344EA0 00341A80  E2 84 02 68 */	psq_l f20, 616(r4), 0, qr0
/* 80344EA4 00341A84  E2 A4 02 70 */	psq_l f21, 624(r4), 0, qr0
/* 80344EA8 00341A88  E2 C4 02 78 */	psq_l f22, 632(r4), 0, qr0
/* 80344EAC 00341A8C  E2 E4 02 80 */	psq_l f23, 640(r4), 0, qr0
/* 80344EB0 00341A90  E3 04 02 88 */	psq_l f24, 648(r4), 0, qr0
/* 80344EB4 00341A94  E3 24 02 90 */	psq_l f25, 656(r4), 0, qr0
/* 80344EB8 00341A98  E3 44 02 98 */	psq_l f26, 664(r4), 0, qr0
/* 80344EBC 00341A9C  E3 64 02 A0 */	psq_l f27, 672(r4), 0, qr0
/* 80344EC0 00341AA0  E3 84 02 A8 */	psq_l f28, 680(r4), 0, qr0
/* 80344EC4 00341AA4  E3 A4 02 B0 */	psq_l f29, 688(r4), 0, qr0
/* 80344EC8 00341AA8  E3 C4 02 B8 */	psq_l f30, 696(r4), 0, qr0
/* 80344ECC 00341AAC  E3 E4 02 C0 */	psq_l f31, 704(r4), 0, qr0
lbl_80344ED0:
/* 80344ED0 00341AB0  C8 04 00 90 */	lfd f0, 0x90(r4)
/* 80344ED4 00341AB4  C8 24 00 98 */	lfd f1, 0x98(r4)
/* 80344ED8 00341AB8  C8 44 00 A0 */	lfd f2, 0xa0(r4)
/* 80344EDC 00341ABC  C8 64 00 A8 */	lfd f3, 0xa8(r4)
/* 80344EE0 00341AC0  C8 84 00 B0 */	lfd f4, 0xb0(r4)
/* 80344EE4 00341AC4  C8 A4 00 B8 */	lfd f5, 0xb8(r4)
/* 80344EE8 00341AC8  C8 C4 00 C0 */	lfd f6, 0xc0(r4)
/* 80344EEC 00341ACC  C8 E4 00 C8 */	lfd f7, 0xc8(r4)
/* 80344EF0 00341AD0  C9 04 00 D0 */	lfd f8, 0xd0(r4)
/* 80344EF4 00341AD4  C9 24 00 D8 */	lfd f9, 0xd8(r4)
/* 80344EF8 00341AD8  C9 44 00 E0 */	lfd f10, 0xe0(r4)
/* 80344EFC 00341ADC  C9 64 00 E8 */	lfd f11, 0xe8(r4)
/* 80344F00 00341AE0  C9 84 00 F0 */	lfd f12, 0xf0(r4)
/* 80344F04 00341AE4  C9 A4 00 F8 */	lfd f13, 0xf8(r4)
/* 80344F08 00341AE8  C9 C4 01 00 */	lfd f14, 0x100(r4)
/* 80344F0C 00341AEC  C9 E4 01 08 */	lfd f15, 0x108(r4)
/* 80344F10 00341AF0  CA 04 01 10 */	lfd f16, 0x110(r4)
/* 80344F14 00341AF4  CA 24 01 18 */	lfd f17, 0x118(r4)
/* 80344F18 00341AF8  CA 44 01 20 */	lfd f18, 0x120(r4)
/* 80344F1C 00341AFC  CA 64 01 28 */	lfd f19, 0x128(r4)
/* 80344F20 00341B00  CA 84 01 30 */	lfd f20, 0x130(r4)
/* 80344F24 00341B04  CA A4 01 38 */	lfd f21, 0x138(r4)
/* 80344F28 00341B08  CA C4 01 40 */	lfd f22, 0x140(r4)
/* 80344F2C 00341B0C  CA E4 01 48 */	lfd f23, 0x148(r4)
/* 80344F30 00341B10  CB 04 01 50 */	lfd f24, 0x150(r4)
/* 80344F34 00341B14  CB 24 01 58 */	lfd f25, 0x158(r4)
/* 80344F38 00341B18  CB 44 01 60 */	lfd f26, 0x160(r4)
/* 80344F3C 00341B1C  CB 64 01 68 */	lfd f27, 0x168(r4)
/* 80344F40 00341B20  CB 84 01 70 */	lfd f28, 0x170(r4)
/* 80344F44 00341B24  CB A4 01 78 */	lfd f29, 0x178(r4)
/* 80344F48 00341B28  CB C4 01 80 */	lfd f30, 0x180(r4)
/* 80344F4C 00341B2C  CB E4 01 88 */	lfd f31, 0x188(r4)
lbl_80344F50:
/* 80344F50 00341B30  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSSaveFPUContext()
{ // clang-format off
    nofralloc
/* 80344F54 00341B34  A0 65 01 A2 */	lhz r3, 0x1a2(r5)
/* 80344F58 00341B38  60 63 00 01 */	ori r3, r3, 1
/* 80344F5C 00341B3C  B0 65 01 A2 */	sth r3, 0x1a2(r5)
/* 80344F60 00341B40  D8 05 00 90 */	stfd f0, 0x90(r5)
/* 80344F64 00341B44  D8 25 00 98 */	stfd f1, 0x98(r5)
/* 80344F68 00341B48  D8 45 00 A0 */	stfd f2, 0xa0(r5)
/* 80344F6C 00341B4C  D8 65 00 A8 */	stfd f3, 0xa8(r5)
/* 80344F70 00341B50  D8 85 00 B0 */	stfd f4, 0xb0(r5)
/* 80344F74 00341B54  D8 A5 00 B8 */	stfd f5, 0xb8(r5)
/* 80344F78 00341B58  D8 C5 00 C0 */	stfd f6, 0xc0(r5)
/* 80344F7C 00341B5C  D8 E5 00 C8 */	stfd f7, 0xc8(r5)
/* 80344F80 00341B60  D9 05 00 D0 */	stfd f8, 0xd0(r5)
/* 80344F84 00341B64  D9 25 00 D8 */	stfd f9, 0xd8(r5)
/* 80344F88 00341B68  D9 45 00 E0 */	stfd f10, 0xe0(r5)
/* 80344F8C 00341B6C  D9 65 00 E8 */	stfd f11, 0xe8(r5)
/* 80344F90 00341B70  D9 85 00 F0 */	stfd f12, 0xf0(r5)
/* 80344F94 00341B74  D9 A5 00 F8 */	stfd f13, 0xf8(r5)
/* 80344F98 00341B78  D9 C5 01 00 */	stfd f14, 0x100(r5)
/* 80344F9C 00341B7C  D9 E5 01 08 */	stfd f15, 0x108(r5)
/* 80344FA0 00341B80  DA 05 01 10 */	stfd f16, 0x110(r5)
/* 80344FA4 00341B84  DA 25 01 18 */	stfd f17, 0x118(r5)
/* 80344FA8 00341B88  DA 45 01 20 */	stfd f18, 0x120(r5)
/* 80344FAC 00341B8C  DA 65 01 28 */	stfd f19, 0x128(r5)
/* 80344FB0 00341B90  DA 85 01 30 */	stfd f20, 0x130(r5)
/* 80344FB4 00341B94  DA A5 01 38 */	stfd f21, 0x138(r5)
/* 80344FB8 00341B98  DA C5 01 40 */	stfd f22, 0x140(r5)
/* 80344FBC 00341B9C  DA E5 01 48 */	stfd f23, 0x148(r5)
/* 80344FC0 00341BA0  DB 05 01 50 */	stfd f24, 0x150(r5)
/* 80344FC4 00341BA4  DB 25 01 58 */	stfd f25, 0x158(r5)
/* 80344FC8 00341BA8  DB 45 01 60 */	stfd f26, 0x160(r5)
/* 80344FCC 00341BAC  DB 65 01 68 */	stfd f27, 0x168(r5)
/* 80344FD0 00341BB0  DB 85 01 70 */	stfd f28, 0x170(r5)
/* 80344FD4 00341BB4  DB A5 01 78 */	stfd f29, 0x178(r5)
/* 80344FD8 00341BB8  DB C5 01 80 */	stfd f30, 0x180(r5)
/* 80344FDC 00341BBC  DB E5 01 88 */	stfd f31, 0x188(r5)
/* 80344FE0 00341BC0  FC 00 04 8E */	mffs f0
/* 80344FE4 00341BC4  D8 05 01 90 */	stfd f0, 0x190(r5)
/* 80344FE8 00341BC8  C8 05 00 90 */	lfd f0, 0x90(r5)
/* 80344FEC 00341BCC  7C 78 E2 A6 */	mfspr r3, 0x398
/* 80344FF0 00341BD0  54 63 1F FF */	rlwinm. r3, r3, 3, 0x1f, 0x1f
/* 80344FF4 00341BD4  41 82 00 84 */	beq lbl_80345078
/* 80344FF8 00341BD8  F0 05 01 C8 */	psq_st f0, 456(r5), 0, qr0
/* 80344FFC 00341BDC  F0 25 01 D0 */	psq_st f1, 464(r5), 0, qr0
/* 80345000 00341BE0  F0 45 01 D8 */	psq_st f2, 472(r5), 0, qr0
/* 80345004 00341BE4  F0 65 01 E0 */	psq_st f3, 480(r5), 0, qr0
/* 80345008 00341BE8  F0 85 01 E8 */	psq_st f4, 488(r5), 0, qr0
/* 8034500C 00341BEC  F0 A5 01 F0 */	psq_st f5, 496(r5), 0, qr0
/* 80345010 00341BF0  F0 C5 01 F8 */	psq_st f6, 504(r5), 0, qr0
/* 80345014 00341BF4  F0 E5 02 00 */	psq_st f7, 512(r5), 0, qr0
/* 80345018 00341BF8  F1 05 02 08 */	psq_st f8, 520(r5), 0, qr0
/* 8034501C 00341BFC  F1 25 02 10 */	psq_st f9, 528(r5), 0, qr0
/* 80345020 00341C00  F1 45 02 18 */	psq_st f10, 536(r5), 0, qr0
/* 80345024 00341C04  F1 65 02 20 */	psq_st f11, 544(r5), 0, qr0
/* 80345028 00341C08  F1 85 02 28 */	psq_st f12, 552(r5), 0, qr0
/* 8034502C 00341C0C  F1 A5 02 30 */	psq_st f13, 560(r5), 0, qr0
/* 80345030 00341C10  F1 C5 02 38 */	psq_st f14, 568(r5), 0, qr0
/* 80345034 00341C14  F1 E5 02 40 */	psq_st f15, 576(r5), 0, qr0
/* 80345038 00341C18  F2 05 02 48 */	psq_st f16, 584(r5), 0, qr0
/* 8034503C 00341C1C  F2 25 02 50 */	psq_st f17, 592(r5), 0, qr0
/* 80345040 00341C20  F2 45 02 58 */	psq_st f18, 600(r5), 0, qr0
/* 80345044 00341C24  F2 65 02 60 */	psq_st f19, 608(r5), 0, qr0
/* 80345048 00341C28  F2 85 02 68 */	psq_st f20, 616(r5), 0, qr0
/* 8034504C 00341C2C  F2 A5 02 70 */	psq_st f21, 624(r5), 0, qr0
/* 80345050 00341C30  F2 C5 02 78 */	psq_st f22, 632(r5), 0, qr0
/* 80345054 00341C34  F2 E5 02 80 */	psq_st f23, 640(r5), 0, qr0
/* 80345058 00341C38  F3 05 02 88 */	psq_st f24, 648(r5), 0, qr0
/* 8034505C 00341C3C  F3 25 02 90 */	psq_st f25, 656(r5), 0, qr0
/* 80345060 00341C40  F3 45 02 98 */	psq_st f26, 664(r5), 0, qr0
/* 80345064 00341C44  F3 65 02 A0 */	psq_st f27, 672(r5), 0, qr0
/* 80345068 00341C48  F3 85 02 A8 */	psq_st f28, 680(r5), 0, qr0
/* 8034506C 00341C4C  F3 A5 02 B0 */	psq_st f29, 688(r5), 0, qr0
/* 80345070 00341C50  F3 C5 02 B8 */	psq_st f30, 696(r5), 0, qr0
/* 80345074 00341C54  F3 E5 02 C0 */	psq_st f31, 704(r5), 0, qr0
lbl_80345078:
/* 80345078 00341C58  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t OSLoadFPUContext()
{ // clang-format off
    nofralloc
/* 8034507C 00341C5C  38 83 00 00 */	addi r4, r3, 0
/* 80345080 00341C60  4B FF FD B0 */	b __OSLoadFPUContext
} // clang-format on
#pragma pop

#pragma push
asm void OSSaveFPUContext(OSContext *)
{ // clang-format off
    nofralloc
/* 80345084 00341C64  38 A3 00 00 */	addi r5, r3, 0
/* 80345088 00341C68  4B FF FE CC */	b __OSSaveFPUContext
} // clang-format on
#pragma pop

#pragma push
asm void OSSetCurrentContext(OSContext *)
{ // clang-format off
    nofralloc
/* 8034508C 00341C6C  3C 80 80 00 */	lis r4, 0x800000D4@ha
/* 80345090 00341C70  90 64 00 D4 */	stw r3, 0x800000D4@l(r4)
/* 80345094 00341C74  54 65 00 BE */	clrlwi r5, r3, 2
/* 80345098 00341C78  90 A4 00 C0 */	stw r5, 0xc0(r4)
/* 8034509C 00341C7C  80 A4 00 D8 */	lwz r5, 0xd8(r4)
/* 803450A0 00341C80  7C 05 18 00 */	cmpw r5, r3
/* 803450A4 00341C84  40 82 00 20 */	bne lbl_803450C4
/* 803450A8 00341C88  80 C3 01 9C */	lwz r6, 0x19c(r3)
/* 803450AC 00341C8C  60 C6 20 00 */	ori r6, r6, 0x2000
/* 803450B0 00341C90  90 C3 01 9C */	stw r6, 0x19c(r3)
/* 803450B4 00341C94  7C C0 00 A6 */	mfmsr r6
/* 803450B8 00341C98  60 C6 00 02 */	ori r6, r6, 2
/* 803450BC 00341C9C  7C C0 01 24 */	mtmsr r6
/* 803450C0 00341CA0  4E 80 00 20 */	blr 
lbl_803450C4:
/* 803450C4 00341CA4  80 C3 01 9C */	lwz r6, 0x19c(r3)
/* 803450C8 00341CA8  54 C6 04 E2 */	rlwinm r6, r6, 0, 0x13, 0x11
/* 803450CC 00341CAC  90 C3 01 9C */	stw r6, 0x19c(r3)
/* 803450D0 00341CB0  7C C0 00 A6 */	mfmsr r6
/* 803450D4 00341CB4  54 C6 04 E2 */	rlwinm r6, r6, 0, 0x13, 0x11
/* 803450D8 00341CB8  60 C6 00 02 */	ori r6, r6, 2
/* 803450DC 00341CBC  7C C0 01 24 */	mtmsr r6
/* 803450E0 00341CC0  4C 00 01 2C */	isync 
/* 803450E4 00341CC4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm OSContext *OSGetCurrentContext(void)
{ // clang-format off
    nofralloc
/* 803450E8 00341CC8  3C 60 80 00 */	lis r3, 0x800000D4@ha
/* 803450EC 00341CCC  80 63 00 D4 */	lwz r3, 0x800000D4@l(r3)
/* 803450F0 00341CD0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/bNK5a // 0 (100%)
#pragma push
asm BOOL OSSaveContext(OSContext *)
{ // clang-format off
    nofralloc
/* 803450F4 00341CD4  BD A3 00 34 */	stmw r13, 0x34(r3)
/* 803450F8 00341CD8  7C 11 E2 A6 */	mfspr r0, 0x391
/* 803450FC 00341CDC  90 03 01 A8 */	stw r0, 0x1a8(r3)
/* 80345100 00341CE0  7C 12 E2 A6 */	mfspr r0, 0x392
/* 80345104 00341CE4  90 03 01 AC */	stw r0, 0x1ac(r3)
/* 80345108 00341CE8  7C 13 E2 A6 */	mfspr r0, 0x393
/* 8034510C 00341CEC  90 03 01 B0 */	stw r0, 0x1b0(r3)
/* 80345110 00341CF0  7C 14 E2 A6 */	mfspr r0, 0x394
/* 80345114 00341CF4  90 03 01 B4 */	stw r0, 0x1b4(r3)
/* 80345118 00341CF8  7C 15 E2 A6 */	mfspr r0, 0x395
/* 8034511C 00341CFC  90 03 01 B8 */	stw r0, 0x1b8(r3)
/* 80345120 00341D00  7C 16 E2 A6 */	mfspr r0, 0x396
/* 80345124 00341D04  90 03 01 BC */	stw r0, 0x1bc(r3)
/* 80345128 00341D08  7C 17 E2 A6 */	mfspr r0, 0x397
/* 8034512C 00341D0C  90 03 01 C0 */	stw r0, 0x1c0(r3)
/* 80345130 00341D10  7C 00 00 26 */	mfcr r0
/* 80345134 00341D14  90 03 00 80 */	stw r0, 0x80(r3)
/* 80345138 00341D18  7C 08 02 A6 */	mflr r0
/* 8034513C 00341D1C  90 03 00 84 */	stw r0, 0x84(r3)
/* 80345140 00341D20  90 03 01 98 */	stw r0, 0x198(r3)
/* 80345144 00341D24  7C 00 00 A6 */	mfmsr r0
/* 80345148 00341D28  90 03 01 9C */	stw r0, 0x19c(r3)
/* 8034514C 00341D2C  7C 09 02 A6 */	mfctr r0
/* 80345150 00341D30  90 03 00 88 */	stw r0, 0x88(r3)
/* 80345154 00341D34  7C 01 02 A6 */	mfxer r0
/* 80345158 00341D38  90 03 00 8C */	stw r0, 0x8c(r3)
/* 8034515C 00341D3C  90 23 00 04 */	stw r1, 4(r3)
/* 80345160 00341D40  90 43 00 08 */	stw r2, 8(r3)
/* 80345164 00341D44  38 00 00 01 */	li r0, 1
/* 80345168 00341D48  90 03 00 0C */	stw r0, 0xc(r3)
/* 8034516C 00341D4C  38 60 00 00 */	li r3, 0
/* 80345170 00341D50  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern void lbl_80347374(void);


#pragma push
asm void OSLoadContext(OSContext *)
{ // clang-format off
    nofralloc
/* 80345174 00341D54  3C 80 80 34 */	lis r4, OSDisableInterrupts@ha
/* 80345178 00341D58  80 C3 01 98 */	lwz r6, 0x198(r3)
/* 8034517C 00341D5C  38 A4 73 64 */	addi r5, r4, OSDisableInterrupts@l
/* 80345180 00341D60  7C 06 28 40 */	cmplw r6, r5
/* 80345184 00341D64  41 80 00 18 */	blt lbl_8034519C
/* 80345188 00341D68  3C 80 80 34 */	lis r4, lbl_80347374@ha
/* 8034518C 00341D6C  38 04 73 74 */	addi r0, r4, lbl_80347374@l
/* 80345190 00341D70  7C 06 00 40 */	cmplw r6, r0
/* 80345194 00341D74  41 81 00 08 */	bgt lbl_8034519C
/* 80345198 00341D78  90 A3 01 98 */	stw r5, 0x198(r3)
lbl_8034519C:
/* 8034519C 00341D7C  80 03 00 00 */	lwz r0, 0(r3)
/* 803451A0 00341D80  80 23 00 04 */	lwz r1, 4(r3)
/* 803451A4 00341D84  80 43 00 08 */	lwz r2, 8(r3)
/* 803451A8 00341D88  A0 83 01 A2 */	lhz r4, 0x1a2(r3)
/* 803451AC 00341D8C  54 85 07 BD */	rlwinm. r5, r4, 0, 0x1e, 0x1e
/* 803451B0 00341D90  41 82 00 14 */	beq lbl_803451C4
/* 803451B4 00341D94  54 84 07 FA */	rlwinm r4, r4, 0, 0x1f, 0x1d
/* 803451B8 00341D98  B0 83 01 A2 */	sth r4, 0x1a2(r3)
/* 803451BC 00341D9C  B8 A3 00 14 */	lmw r5, 0x14(r3)
/* 803451C0 00341DA0  48 00 00 08 */	b lbl_803451C8
lbl_803451C4:
/* 803451C4 00341DA4  B9 A3 00 34 */	lmw r13, 0x34(r3)
lbl_803451C8:
/* 803451C8 00341DA8  80 83 01 A8 */	lwz r4, 0x1a8(r3)
/* 803451CC 00341DAC  7C 91 E3 A6 */	mtspr 0x391, r4
/* 803451D0 00341DB0  80 83 01 AC */	lwz r4, 0x1ac(r3)
/* 803451D4 00341DB4  7C 92 E3 A6 */	mtspr 0x392, r4
/* 803451D8 00341DB8  80 83 01 B0 */	lwz r4, 0x1b0(r3)
/* 803451DC 00341DBC  7C 93 E3 A6 */	mtspr 0x393, r4
/* 803451E0 00341DC0  80 83 01 B4 */	lwz r4, 0x1b4(r3)
/* 803451E4 00341DC4  7C 94 E3 A6 */	mtspr 0x394, r4
/* 803451E8 00341DC8  80 83 01 B8 */	lwz r4, 0x1b8(r3)
/* 803451EC 00341DCC  7C 95 E3 A6 */	mtspr 0x395, r4
/* 803451F0 00341DD0  80 83 01 BC */	lwz r4, 0x1bc(r3)
/* 803451F4 00341DD4  7C 96 E3 A6 */	mtspr 0x396, r4
/* 803451F8 00341DD8  80 83 01 C0 */	lwz r4, 0x1c0(r3)
/* 803451FC 00341DDC  7C 97 E3 A6 */	mtspr 0x397, r4
/* 80345200 00341DE0  80 83 00 80 */	lwz r4, 0x80(r3)
/* 80345204 00341DE4  7C 8F F1 20 */	mtcrf 0xff, r4
/* 80345208 00341DE8  80 83 00 84 */	lwz r4, 0x84(r3)
/* 8034520C 00341DEC  7C 88 03 A6 */	mtlr r4
/* 80345210 00341DF0  80 83 00 88 */	lwz r4, 0x88(r3)
/* 80345214 00341DF4  7C 89 03 A6 */	mtctr r4
/* 80345218 00341DF8  80 83 00 8C */	lwz r4, 0x8c(r3)
/* 8034521C 00341DFC  7C 81 03 A6 */	mtxer r4
/* 80345220 00341E00  7C 80 00 A6 */	mfmsr r4
/* 80345224 00341E04  54 84 04 5E */	rlwinm r4, r4, 0, 0x11, 0xf
/* 80345228 00341E08  54 84 07 FA */	rlwinm r4, r4, 0, 0x1f, 0x1d
/* 8034522C 00341E0C  7C 80 01 24 */	mtmsr r4
/* 80345230 00341E10  80 83 01 98 */	lwz r4, 0x198(r3)
/* 80345234 00341E14  7C 9A 03 A6 */	mtspr 0x1a, r4
/* 80345238 00341E18  80 83 01 9C */	lwz r4, 0x19c(r3)
/* 8034523C 00341E1C  7C 9B 03 A6 */	mtspr 0x1b, r4
/* 80345240 00341E20  80 83 00 10 */	lwz r4, 0x10(r3)
/* 80345244 00341E24  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80345248 00341E28  4C 00 00 64 */	rfi 
} // clang-format on
#pragma pop

