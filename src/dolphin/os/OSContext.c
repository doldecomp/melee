#include <dolphin/os/OSContext.h>

#include <dolphin/os/os.h>
#include <dolphin/os/OSInterrupt.h>
#include <placeholder.h>

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSLoadFPUContext(void)
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

#else

void __OSLoadFPUContext(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSSaveFPUContext(void)
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

#else

void __OSSaveFPUContext(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSLoadFPUContext(void)
{ // clang-format off
    nofralloc
/* 8034507C 00341C5C  38 83 00 00 */	addi r4, r3, 0
/* 80345080 00341C60  4B FF FD B0 */	b __OSLoadFPUContext
} // clang-format on
#pragma pop

#else

void OSLoadFPUContext(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSSaveFPUContext(OSContext*)
{ // clang-format off
    nofralloc
/* 80345084 00341C64  38 A3 00 00 */	addi r5, r3, 0
/* 80345088 00341C68  4B FF FE CC */	b __OSSaveFPUContext
} // clang-format on
#pragma pop

#else

void OSSaveFPUContext(OSContext* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSSetCurrentContext(OSContext*)
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

#else

void OSSetCurrentContext(OSContext* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

OSContext* OSGetCurrentContext(void)
{
    return OS_CURRENT_CONTEXT;
}

#ifdef MWERKS_GEKKO

#pragma push
asm bool OSSaveContext(register OSContext* ctx)
{ // clang-format off
    // disable automatic stack save generated by storing r1
    nofralloc

    stmw r13,0x34(ctx)
    mfspr r0,GQR1
    stw r0,0x1A8(ctx)
    mfspr r0,GQR2
    stw r0,0x1AC(ctx)
    mfspr r0,GQR3
    stw r0,0x1B0(ctx)
    mfspr r0,GQR4
    stw r0,0x1B4(ctx)
    mfspr r0,GQR5
    stw r0,0x1B8(ctx)
    mfspr r0,GQR6
    stw r0,0x1BC(ctx)
    mfspr r0,GQR7
    stw r0,0x1C0(ctx)
    mfcr r0
    stw r0,0x80(ctx)
    mflr r0
    stw r0,0x84(ctx)
    stw r0,0x198(ctx)
    mfmsr r0
    stw r0,0x19C(ctx)
    mfctr r0
    stw r0,0x88(ctx)
    mfxer r0
    stw r0,0x8C(ctx)
    stw r1,0x4(ctx)
    stw r2,0x8(ctx)
    li r0,1
    stw r0,0xC(ctx)
    li ctx,0
    blr
} // clang-format on
#pragma pop

#else

bool OSSaveContext(OSContext* ctx)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

extern void lbl_80347374(void);

#pragma push
asm void OSLoadContext(OSContext*)
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

#else

void OSLoadContext(OSContext* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm any_t OSGetStackPointer(void){
    // clang-format off
    nofralloc
/* 8034524C 00341E2C  7C 23 0B 78 */	mr r3, r1
/* 80345250 00341E30  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

any_t OSGetStackPointer(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSClearContext(OSContext*)
{ // clang-format off
    nofralloc
/* 80345254 00341E34  38 A0 00 00 */	li r5, 0
/* 80345258 00341E38  B0 A3 01 A0 */	sth r5, 0x1a0(r3)
/* 8034525C 00341E3C  3C 80 80 00 */	lis r4, 0x800000D8@ha
/* 80345260 00341E40  B0 A3 01 A2 */	sth r5, 0x1a2(r3)
/* 80345264 00341E44  80 04 00 D8 */	lwz r0, 0x800000D8@l(r4)
/* 80345268 00341E48  7C 03 00 40 */	cmplw r3, r0
/* 8034526C 00341E4C  40 82 00 08 */	bne lbl_80345274
/* 80345270 00341E50  90 A4 00 D8 */	stw r5, 0xd8(r4)
lbl_80345274:
/* 80345274 00341E54  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void OSClearContext(OSContext* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSInitContext(OSContext* ctx, unk_t arg1, unk_t arg2)
{ // clang-format off
    nofralloc
/* 80345278 00341E58  90 83 01 98 */	stw r4, 0x198(r3)
/* 8034527C 00341E5C  90 A3 00 04 */	stw r5, 4(r3)
/* 80345280 00341E60  39 60 00 00 */	li r11, 0
/* 80345284 00341E64  61 6B 90 32 */	ori r11, r11, 0x9032
/* 80345288 00341E68  91 63 01 9C */	stw r11, 0x19c(r3)
/* 8034528C 00341E6C  38 00 00 00 */	li r0, 0
/* 80345290 00341E70  90 03 00 80 */	stw r0, 0x80(r3)
/* 80345294 00341E74  90 03 00 8C */	stw r0, 0x8c(r3)
/* 80345298 00341E78  90 43 00 08 */	stw r2, 8(r3)
/* 8034529C 00341E7C  91 A3 00 34 */	stw r13, 0x34(r3)
/* 803452A0 00341E80  90 03 00 0C */	stw r0, 0xc(r3)
/* 803452A4 00341E84  90 03 00 10 */	stw r0, 0x10(r3)
/* 803452A8 00341E88  90 03 00 14 */	stw r0, 0x14(r3)
/* 803452AC 00341E8C  90 03 00 18 */	stw r0, 0x18(r3)
/* 803452B0 00341E90  90 03 00 1C */	stw r0, 0x1c(r3)
/* 803452B4 00341E94  90 03 00 20 */	stw r0, 0x20(r3)
/* 803452B8 00341E98  90 03 00 24 */	stw r0, 0x24(r3)
/* 803452BC 00341E9C  90 03 00 28 */	stw r0, 0x28(r3)
/* 803452C0 00341EA0  90 03 00 2C */	stw r0, 0x2c(r3)
/* 803452C4 00341EA4  90 03 00 30 */	stw r0, 0x30(r3)
/* 803452C8 00341EA8  90 03 00 38 */	stw r0, 0x38(r3)
/* 803452CC 00341EAC  90 03 00 3C */	stw r0, 0x3c(r3)
/* 803452D0 00341EB0  90 03 00 40 */	stw r0, 0x40(r3)
/* 803452D4 00341EB4  90 03 00 44 */	stw r0, 0x44(r3)
/* 803452D8 00341EB8  90 03 00 48 */	stw r0, 0x48(r3)
/* 803452DC 00341EBC  90 03 00 4C */	stw r0, 0x4c(r3)
/* 803452E0 00341EC0  90 03 00 50 */	stw r0, 0x50(r3)
/* 803452E4 00341EC4  90 03 00 54 */	stw r0, 0x54(r3)
/* 803452E8 00341EC8  90 03 00 58 */	stw r0, 0x58(r3)
/* 803452EC 00341ECC  90 03 00 5C */	stw r0, 0x5c(r3)
/* 803452F0 00341ED0  90 03 00 60 */	stw r0, 0x60(r3)
/* 803452F4 00341ED4  90 03 00 64 */	stw r0, 0x64(r3)
/* 803452F8 00341ED8  90 03 00 68 */	stw r0, 0x68(r3)
/* 803452FC 00341EDC  90 03 00 6C */	stw r0, 0x6c(r3)
/* 80345300 00341EE0  90 03 00 70 */	stw r0, 0x70(r3)
/* 80345304 00341EE4  90 03 00 74 */	stw r0, 0x74(r3)
/* 80345308 00341EE8  90 03 00 78 */	stw r0, 0x78(r3)
/* 8034530C 00341EEC  90 03 00 7C */	stw r0, 0x7c(r3)
/* 80345310 00341EF0  90 03 01 A4 */	stw r0, 0x1a4(r3)
/* 80345314 00341EF4  90 03 01 A8 */	stw r0, 0x1a8(r3)
/* 80345318 00341EF8  90 03 01 AC */	stw r0, 0x1ac(r3)
/* 8034531C 00341EFC  90 03 01 B0 */	stw r0, 0x1b0(r3)
/* 80345320 00341F00  90 03 01 B4 */	stw r0, 0x1b4(r3)
/* 80345324 00341F04  90 03 01 B8 */	stw r0, 0x1b8(r3)
/* 80345328 00341F08  90 03 01 BC */	stw r0, 0x1bc(r3)
/* 8034532C 00341F0C  90 03 01 C0 */	stw r0, 0x1c0(r3)
/* 80345330 00341F10  4B FF FF 24 */	b OSClearContext
} // clang-format on
#pragma pop

#else

void OSInitContext(OSContext* ctx, unk_t arg1, unk_t arg2)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

extern char* lbl_80401E20[];
extern unk_t __cvt_fp2unsigned();

#pragma push
asm void OSDumpContext(const OSContext*)
{ // clang-format off
    nofralloc
/* 80345334 00341F14  7C 08 02 A6 */	mflr r0
/* 80345338 00341F18  90 01 00 04 */	stw r0, 4(r1)
/* 8034533C 00341F1C  94 21 FD 08 */	stwu r1, -0x2f8(r1)
/* 80345340 00341F20  BF 21 02 DC */	stmw r25, 0x2dc(r1)
/* 80345344 00341F24  7C 7C 1B 78 */	mr r28, r3
/* 80345348 00341F28  3C 60 80 40 */	lis r3, lbl_80401E20@ha
/* 8034534C 00341F2C  4C C6 31 82 */	crclr 6
/* 80345350 00341F30  3B E3 1E 20 */	addi r31, r3, lbl_80401E20@l
/* 80345354 00341F34  7F E3 FB 78 */	mr r3, r31
/* 80345358 00341F38  7F 84 E3 78 */	mr r4, r28
/* 8034535C 00341F3C  48 00 03 4D */	bl OSReport
/* 80345360 00341F40  3B 20 00 00 */	li r25, 0
/* 80345364 00341F44  57 20 10 3A */	slwi r0, r25, 2
/* 80345368 00341F48  7F 7C 02 14 */	add r27, r28, r0
/* 8034536C 00341F4C  48 00 00 04 */	b lbl_80345370
lbl_80345370:
/* 80345370 00341F50  48 00 00 04 */	b lbl_80345374
lbl_80345374:
/* 80345374 00341F54  48 00 00 04 */	b lbl_80345378
lbl_80345378:
/* 80345378 00341F58  81 1B 00 40 */	lwz r8, 0x40(r27)
/* 8034537C 00341F5C  7F 24 CB 78 */	mr r4, r25
/* 80345380 00341F60  80 BB 00 00 */	lwz r5, 0(r27)
/* 80345384 00341F64  38 7F 00 44 */	addi r3, r31, 0x44
/* 80345388 00341F68  4C C6 31 82 */	crclr 6
/* 8034538C 00341F6C  7C A6 2B 78 */	mr r6, r5
/* 80345390 00341F70  7D 09 43 78 */	mr r9, r8
/* 80345394 00341F74  38 F9 00 10 */	addi r7, r25, 0x10
/* 80345398 00341F78  48 00 03 11 */	bl OSReport
/* 8034539C 00341F7C  3B 7B 00 04 */	addi r27, r27, 4
/* 803453A0 00341F80  3B 39 00 01 */	addi r25, r25, 1
/* 803453A4 00341F84  28 19 00 10 */	cmplwi r25, 0x10
/* 803453A8 00341F88  41 80 FF D0 */	blt lbl_80345378
/* 803453AC 00341F8C  80 9C 00 84 */	lwz r4, 0x84(r28)
/* 803453B0 00341F90  38 7F 00 74 */	addi r3, r31, 0x74
/* 803453B4 00341F94  80 BC 00 80 */	lwz r5, 0x80(r28)
/* 803453B8 00341F98  4C C6 31 82 */	crclr 6
/* 803453BC 00341F9C  48 00 02 ED */	bl OSReport
/* 803453C0 00341FA0  80 9C 01 98 */	lwz r4, 0x198(r28)
/* 803453C4 00341FA4  38 7F 00 A4 */	addi r3, r31, 0xa4
/* 803453C8 00341FA8  80 BC 01 9C */	lwz r5, 0x19c(r28)
/* 803453CC 00341FAC  4C C6 31 82 */	crclr 6
/* 803453D0 00341FB0  48 00 02 D9 */	bl OSReport
/* 803453D4 00341FB4  38 7F 00 D4 */	addi r3, r31, 0xd4
/* 803453D8 00341FB8  4C C6 31 82 */	crclr 6
/* 803453DC 00341FBC  48 00 02 CD */	bl OSReport
/* 803453E0 00341FC0  3B 20 00 00 */	li r25, 0
/* 803453E4 00341FC4  57 20 10 3A */	slwi r0, r25, 2
/* 803453E8 00341FC8  7F 7C 02 14 */	add r27, r28, r0
/* 803453EC 00341FCC  48 00 00 04 */	b lbl_803453F0
lbl_803453F0:
/* 803453F0 00341FD0  48 00 00 04 */	b lbl_803453F4
lbl_803453F4:
/* 803453F4 00341FD4  48 00 00 04 */	b lbl_803453F8
lbl_803453F8:
/* 803453F8 00341FD8  80 BB 01 A4 */	lwz r5, 0x1a4(r27)
/* 803453FC 00341FDC  7F 24 CB 78 */	mr r4, r25
/* 80345400 00341FE0  80 FB 01 B4 */	lwz r7, 0x1b4(r27)
/* 80345404 00341FE4  38 7F 00 E8 */	addi r3, r31, 0xe8
/* 80345408 00341FE8  38 D9 00 04 */	addi r6, r25, 4
/* 8034540C 00341FEC  4C C6 31 82 */	crclr 6
/* 80345410 00341FF0  48 00 02 99 */	bl OSReport
/* 80345414 00341FF4  3B 7B 00 04 */	addi r27, r27, 4
/* 80345418 00341FF8  3B 39 00 01 */	addi r25, r25, 1
/* 8034541C 00341FFC  28 19 00 04 */	cmplwi r25, 4
/* 80345420 00342000  41 80 FF D8 */	blt lbl_803453F8
/* 80345424 00342004  A0 1C 01 A2 */	lhz r0, 0x1a2(r28)
/* 80345428 00342008  54 00 07 FE */	clrlwi r0, r0, 0x1f
/* 8034542C 0034200C  28 00 00 00 */	cmplwi r0, 0
/* 80345430 00342010  41 82 01 3C */	beq lbl_8034556C
/* 80345434 00342014  48 00 1F 31 */	bl OSDisableInterrupts
/* 80345438 00342018  3C C0 80 00 */	lis r6, 0x800000D4@ha
/* 8034543C 0034201C  80 06 00 D4 */	lwz r0, 0x800000D4@l(r6)
/* 80345440 00342020  38 A0 00 00 */	li r5, 0
/* 80345444 00342024  38 81 00 10 */	addi r4, r1, 0x10
/* 80345448 00342028  B0 A1 01 B0 */	sth r5, 0x1b0(r1)
/* 8034544C 0034202C  7C 1E 03 78 */	mr r30, r0
/* 80345450 00342030  7C 7D 1B 78 */	mr r29, r3
/* 80345454 00342034  B0 A1 01 B2 */	sth r5, 0x1b2(r1)
/* 80345458 00342038  80 06 00 D8 */	lwz r0, 0xd8(r6)
/* 8034545C 0034203C  7C 04 00 40 */	cmplw r4, r0
/* 80345460 00342040  40 82 00 08 */	bne lbl_80345468
/* 80345464 00342044  90 A6 00 D8 */	stw r5, 0xd8(r6)
lbl_80345468:
/* 80345468 00342048  38 61 00 10 */	addi r3, r1, 0x10
/* 8034546C 0034204C  4B FF FC 21 */	bl OSSetCurrentContext
/* 80345470 00342050  38 7F 01 0C */	addi r3, r31, 0x10c
/* 80345474 00342054  4C C6 31 82 */	crclr 6
/* 80345478 00342058  48 00 02 31 */	bl OSReport
/* 8034547C 0034205C  3B 20 00 00 */	li r25, 0
/* 80345480 00342060  57 20 18 38 */	slwi r0, r25, 3
/* 80345484 00342064  7F 5C 02 14 */	add r26, r28, r0
/* 80345488 00342068  48 00 00 04 */	b lbl_8034548C
lbl_8034548C:
/* 8034548C 0034206C  48 00 00 04 */	b lbl_80345490
lbl_80345490:
/* 80345490 00342070  48 00 00 04 */	b lbl_80345494
lbl_80345494:
/* 80345494 00342074  C8 3A 00 98 */	lfd f1, 0x98(r26)
/* 80345498 00342078  4B FD D4 29 */	bl __cvt_fp2unsigned
/* 8034549C 0034207C  7C 7B 1B 78 */	mr r27, r3
/* 803454A0 00342080  C8 3A 00 90 */	lfd f1, 0x90(r26)
/* 803454A4 00342084  4B FD D4 1D */	bl __cvt_fp2unsigned
/* 803454A8 00342088  7C 65 1B 78 */	mr r5, r3
/* 803454AC 0034208C  4C C6 31 82 */	crclr 6
/* 803454B0 00342090  7F 24 CB 78 */	mr r4, r25
/* 803454B4 00342094  7F 67 DB 78 */	mr r7, r27
/* 803454B8 00342098  38 7F 01 20 */	addi r3, r31, 0x120
/* 803454BC 0034209C  38 D9 00 01 */	addi r6, r25, 1
/* 803454C0 003420A0  48 00 01 E9 */	bl OSReport
/* 803454C4 003420A4  3B 5A 00 10 */	addi r26, r26, 0x10
/* 803454C8 003420A8  3B 39 00 02 */	addi r25, r25, 2
/* 803454CC 003420AC  28 19 00 20 */	cmplwi r25, 0x20
/* 803454D0 003420B0  41 80 FF C4 */	blt lbl_80345494
/* 803454D4 003420B4  38 7F 01 3C */	addi r3, r31, 0x13c
/* 803454D8 003420B8  4C C6 31 82 */	crclr 6
/* 803454DC 003420BC  48 00 01 CD */	bl OSReport
/* 803454E0 003420C0  3B 20 00 00 */	li r25, 0
/* 803454E4 003420C4  57 20 18 38 */	slwi r0, r25, 3
/* 803454E8 003420C8  7F 5C 02 14 */	add r26, r28, r0
/* 803454EC 003420CC  48 00 00 04 */	b lbl_803454F0
lbl_803454F0:
/* 803454F0 003420D0  48 00 00 04 */	b lbl_803454F4
lbl_803454F4:
/* 803454F4 003420D4  48 00 00 04 */	b lbl_803454F8
lbl_803454F8:
/* 803454F8 003420D8  C8 3A 01 D0 */	lfd f1, 0x1d0(r26)
/* 803454FC 003420DC  4B FD D3 C5 */	bl __cvt_fp2unsigned
/* 80345500 003420E0  7C 7B 1B 78 */	mr r27, r3
/* 80345504 003420E4  C8 3A 01 C8 */	lfd f1, 0x1c8(r26)
/* 80345508 003420E8  4B FD D3 B9 */	bl __cvt_fp2unsigned
/* 8034550C 003420EC  7C 65 1B 78 */	mr r5, r3
/* 80345510 003420F0  4C C6 31 82 */	crclr 6
/* 80345514 003420F4  7F 24 CB 78 */	mr r4, r25
/* 80345518 003420F8  7F 67 DB 78 */	mr r7, r27
/* 8034551C 003420FC  38 7F 01 50 */	addi r3, r31, 0x150
/* 80345520 00342100  38 D9 00 01 */	addi r6, r25, 1
/* 80345524 00342104  48 00 01 85 */	bl OSReport
/* 80345528 00342108  3B 5A 00 10 */	addi r26, r26, 0x10
/* 8034552C 0034210C  3B 39 00 02 */	addi r25, r25, 2
/* 80345530 00342110  28 19 00 20 */	cmplwi r25, 0x20
/* 80345534 00342114  41 80 FF C4 */	blt lbl_803454F8
/* 80345538 00342118  38 A0 00 00 */	li r5, 0
/* 8034553C 0034211C  B0 A1 01 B0 */	sth r5, 0x1b0(r1)
/* 80345540 00342120  3C 60 80 00 */	lis r3, 0x800000D8@ha
/* 80345544 00342124  38 81 00 10 */	addi r4, r1, 0x10
/* 80345548 00342128  B0 A1 01 B2 */	sth r5, 0x1b2(r1)
/* 8034554C 0034212C  80 03 00 D8 */	lwz r0, 0x800000D8@l(r3)
/* 80345550 00342130  7C 04 00 40 */	cmplw r4, r0
/* 80345554 00342134  40 82 00 08 */	bne lbl_8034555C
/* 80345558 00342138  90 A3 00 D8 */	stw r5, 0xd8(r3)
lbl_8034555C:
/* 8034555C 0034213C  7F C3 F3 78 */	mr r3, r30
/* 80345560 00342140  4B FF FB 2D */	bl OSSetCurrentContext
/* 80345564 00342144  7F A3 EB 78 */	mr r3, r29
/* 80345568 00342148  48 00 1E 25 */	bl OSRestoreInterrupts
lbl_8034556C:
/* 8034556C 0034214C  38 7F 01 70 */	addi r3, r31, 0x170
/* 80345570 00342150  4C C6 31 82 */	crclr 6
/* 80345574 00342154  48 00 01 35 */	bl OSReport
/* 80345578 00342158  83 3C 00 04 */	lwz r25, 4(r28)
/* 8034557C 0034215C  3B 40 00 00 */	li r26, 0
/* 80345580 00342160  48 00 00 04 */	b lbl_80345584
lbl_80345584:
/* 80345584 00342164  48 00 00 04 */	b lbl_80345588
lbl_80345588:
/* 80345588 00342168  48 00 00 20 */	b lbl_803455A8
lbl_8034558C:
/* 8034558C 0034216C  80 B9 00 00 */	lwz r5, 0(r25)
/* 80345590 00342170  7F 24 CB 78 */	mr r4, r25
/* 80345594 00342174  80 D9 00 04 */	lwz r6, 4(r25)
/* 80345598 00342178  38 7F 01 98 */	addi r3, r31, 0x198
/* 8034559C 0034217C  4C C6 31 82 */	crclr 6
/* 803455A0 00342180  48 00 01 09 */	bl OSReport
/* 803455A4 00342184  83 39 00 00 */	lwz r25, 0(r25)
lbl_803455A8:
/* 803455A8 00342188  28 19 00 00 */	cmplwi r25, 0
/* 803455AC 0034218C  41 82 00 1C */	beq lbl_803455C8
/* 803455B0 00342190  3C 19 00 01 */	addis r0, r25, 1
/* 803455B4 00342194  28 00 FF FF */	cmplwi r0, 0xffff
/* 803455B8 00342198  41 82 00 10 */	beq lbl_803455C8
/* 803455BC 0034219C  28 1A 00 10 */	cmplwi r26, 0x10
/* 803455C0 003421A0  3B 5A 00 01 */	addi r26, r26, 1
/* 803455C4 003421A4  41 80 FF C8 */	blt lbl_8034558C
lbl_803455C8:
/* 803455C8 003421A8  BB 21 02 DC */	lmw r25, 0x2dc(r1)
/* 803455CC 003421AC  80 01 02 FC */	lwz r0, 0x2fc(r1)
/* 803455D0 003421B0  38 21 02 F8 */	addi r1, r1, 0x2f8
/* 803455D4 003421B4  7C 08 03 A6 */	mtlr r0
/* 803455D8 003421B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void OSDumpContext(const OSContext* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void OSSwitchFPUContext(void)
{ // clang-format off
    nofralloc
/* 803455DC 003421BC  7C A0 00 A6 */	mfmsr r5
/* 803455E0 003421C0  60 A5 20 00 */	ori r5, r5, 0x2000
/* 803455E4 003421C4  7C A0 01 24 */	mtmsr r5
/* 803455E8 003421C8  4C 00 01 2C */	isync
/* 803455EC 003421CC  80 A4 01 9C */	lwz r5, 0x19c(r4)
/* 803455F0 003421D0  60 A5 20 00 */	ori r5, r5, 0x2000
/* 803455F4 003421D4  7C BB 03 A6 */	mtspr 0x1b, r5
/* 803455F8 003421D8  3C 60 80 00 */	lis r3, 0x800000D8@ha
/* 803455FC 003421DC  80 A3 00 D8 */	lwz r5, 0x800000D8@l(r3)
/* 80345600 003421E0  90 83 00 D8 */	stw r4, 0xd8(r3)
/* 80345604 003421E4  7C 05 20 00 */	cmpw r5, r4
/* 80345608 003421E8  41 82 00 14 */	beq lbl_8034561C
/* 8034560C 003421EC  2C 05 00 00 */	cmpwi r5, 0
/* 80345610 003421F0  41 82 00 08 */	beq lbl_80345618
/* 80345614 003421F4  4B FF F9 41 */	bl __OSSaveFPUContext
lbl_80345618:
/* 80345618 003421F8  4B FF F8 19 */	bl __OSLoadFPUContext
lbl_8034561C:
/* 8034561C 003421FC  80 64 00 80 */	lwz r3, 0x80(r4)
/* 80345620 00342200  7C 6F F1 20 */	mtcrf 0xff, r3
/* 80345624 00342204  80 64 00 84 */	lwz r3, 0x84(r4)
/* 80345628 00342208  7C 68 03 A6 */	mtlr r3
/* 8034562C 0034220C  80 64 01 98 */	lwz r3, 0x198(r4)
/* 80345630 00342210  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80345634 00342214  80 64 00 88 */	lwz r3, 0x88(r4)
/* 80345638 00342218  7C 69 03 A6 */	mtctr r3
/* 8034563C 0034221C  80 64 00 8C */	lwz r3, 0x8c(r4)
/* 80345640 00342220  7C 61 03 A6 */	mtxer r3
/* 80345644 00342224  A0 64 01 A2 */	lhz r3, 0x1a2(r4)
/* 80345648 00342228  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8034564C 0034222C  B0 64 01 A2 */	sth r3, 0x1a2(r4)
/* 80345650 00342230  80 A4 00 14 */	lwz r5, 0x14(r4)
/* 80345654 00342234  80 64 00 0C */	lwz r3, 0xc(r4)
/* 80345658 00342238  80 84 00 10 */	lwz r4, 0x10(r4)
/* 8034565C 0034223C  4C 00 00 64 */	rfi
} // clang-format on
#pragma pop

#else

void OSSwitchFPUContext(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

extern char* lbl_80401FD4;
extern unk_t DBPrintf();
extern unk_t __OSSetExceptionHandler();

#pragma push
asm void __OSContextInit(void)
{ // clang-format off
    nofralloc
/* 80345660 00342240  7C 08 02 A6 */	mflr r0
/* 80345664 00342244  90 01 00 04 */	stw r0, 4(r1)
/* 80345668 00342248  94 21 FF F8 */	stwu r1, -8(r1)
/* 8034566C 0034224C  3C 60 80 34 */	lis r3, OSSwitchFPUContext@ha
/* 80345670 00342250  38 83 55 DC */	addi r4, r3, OSSwitchFPUContext@l
/* 80345674 00342254  38 60 00 07 */	li r3, 7
/* 80345678 00342258  4B FF DF 3D */	bl __OSSetExceptionHandler
/* 8034567C 0034225C  38 00 00 00 */	li r0, 0
/* 80345680 00342260  4C C6 31 82 */	crclr 6
/* 80345684 00342264  3C 80 80 00 */	lis r4, 0x800000D8@ha
/* 80345688 00342268  3C 60 80 40 */	lis r3, lbl_80401FD4@ha
/* 8034568C 0034226C  90 04 00 D8 */	stw r0, 0x800000D8@l(r4)
/* 80345690 00342270  38 63 1F D4 */	addi r3, r3, lbl_80401FD4@l
/* 80345694 00342274  4B FF 08 E5 */	bl DBPrintf
/* 80345698 00342278  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8034569C 0034227C  38 21 00 08 */	addi r1, r1, 8
/* 803456A0 00342280  7C 08 03 A6 */	mtlr r0
/* 803456A4 00342284  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSContextInit(void)
{
    NOT_IMPLEMENTED;
}

#endif
