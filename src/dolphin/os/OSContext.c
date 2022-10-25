#include <dolphin/types.h>

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
asm unk_t OSSaveFPUContext()
{ // clang-format off
    nofralloc
/* 80345084 00341C64  38 A3 00 00 */	addi r5, r3, 0
/* 80345088 00341C68  4B FF FE CC */	b __OSSaveFPUContext
} // clang-format on
#pragma pop

