#include <placeholder.h>
#include <Runtime/Gecko_setjmp.h>
#include <Runtime/platform.h>

#ifdef MWERKS_GEKKO

#pragma push
asm int __setjmp(register unk_t env, unk_t, unk_t)
{ // clang-format off
    nofralloc
/* 803227CC 0031F3AC  7C A8 02 A6 */	mflr r5
/* 803227D0 0031F3B0  7C C0 00 26 */	mfcr r6
/* 803227D4 0031F3B4  90 A3 00 00 */	stw r5, 0(r3)
/* 803227D8 0031F3B8  90 C3 00 04 */	stw r6, 4(r3)
/* 803227DC 0031F3BC  90 23 00 08 */	stw r1, 8(r3)
/* 803227E0 0031F3C0  90 43 00 0C */	stw r2, 0xc(r3)
/* 803227E4 0031F3C4  BD A3 00 14 */	stmw r13, 0x14(r3)
/* 803227E8 0031F3C8  FC 00 04 8E */	mffs f0
/* 803227EC 0031F3CC  D9 C3 00 60 */	stfd f14, 0x60(r3)
/* 803227F0 0031F3D0  D9 E3 00 68 */	stfd f15, 0x68(r3)
/* 803227F4 0031F3D4  DA 03 00 70 */	stfd f16, 0x70(r3)
/* 803227F8 0031F3D8  DA 23 00 78 */	stfd f17, 0x78(r3)
/* 803227FC 0031F3DC  DA 43 00 80 */	stfd f18, 0x80(r3)
/* 80322800 0031F3E0  DA 63 00 88 */	stfd f19, 0x88(r3)
/* 80322804 0031F3E4  DA 83 00 90 */	stfd f20, 0x90(r3)
/* 80322808 0031F3E8  DA A3 00 98 */	stfd f21, 0x98(r3)
/* 8032280C 0031F3EC  DA C3 00 A0 */	stfd f22, 0xa0(r3)
/* 80322810 0031F3F0  DA E3 00 A8 */	stfd f23, 0xa8(r3)
/* 80322814 0031F3F4  DB 03 00 B0 */	stfd f24, 0xb0(r3)
/* 80322818 0031F3F8  DB 23 00 B8 */	stfd f25, 0xb8(r3)
/* 8032281C 0031F3FC  DB 43 00 C0 */	stfd f26, 0xc0(r3)
/* 80322820 0031F400  DB 63 00 C8 */	stfd f27, 0xc8(r3)
/* 80322824 0031F404  DB 83 00 D0 */	stfd f28, 0xd0(r3)
/* 80322828 0031F408  DB A3 00 D8 */	stfd f29, 0xd8(r3)
/* 8032282C 0031F40C  DB C3 00 E0 */	stfd f30, 0xe0(r3)
/* 80322830 0031F410  DB E3 00 E8 */	stfd f31, 0xe8(r3)
/* 80322834 0031F414  D8 03 00 F0 */	stfd f0, 0xf0(r3)
/* 80322838 0031F418  38 60 00 00 */	li r3, 0
/* 8032283C 0031F41C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

int __setjmp(unk_t env, unk_t arg1, unk_t arg2)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void longjmp(register unk_t env, register int val)
{ // clang-format off
    nofralloc
/* 80322840 0031F420  80 A3 00 00 */	lwz r5, 0(r3)
/* 80322844 0031F424  80 C3 00 04 */	lwz r6, 4(r3)
/* 80322848 0031F428  7C A8 03 A6 */	mtlr r5
/* 8032284C 0031F42C  7C CF F1 20 */	mtcrf 0xff, r6
/* 80322850 0031F430  80 23 00 08 */	lwz r1, 8(r3)
/* 80322854 0031F434  80 43 00 0C */	lwz r2, 0xc(r3)
/* 80322858 0031F438  B9 A3 00 14 */	lmw r13, 0x14(r3)
/* 8032285C 0031F43C  C9 C3 00 60 */	lfd f14, 0x60(r3)
/* 80322860 0031F440  C9 E3 00 68 */	lfd f15, 0x68(r3)
/* 80322864 0031F444  CA 03 00 70 */	lfd f16, 0x70(r3)
/* 80322868 0031F448  CA 23 00 78 */	lfd f17, 0x78(r3)
/* 8032286C 0031F44C  CA 43 00 80 */	lfd f18, 0x80(r3)
/* 80322870 0031F450  CA 63 00 88 */	lfd f19, 0x88(r3)
/* 80322874 0031F454  CA 83 00 90 */	lfd f20, 0x90(r3)
/* 80322878 0031F458  CA A3 00 98 */	lfd f21, 0x98(r3)
/* 8032287C 0031F45C  CA C3 00 A0 */	lfd f22, 0xa0(r3)
/* 80322880 0031F460  CA E3 00 A8 */	lfd f23, 0xa8(r3)
/* 80322884 0031F464  CB 03 00 B0 */	lfd f24, 0xb0(r3)
/* 80322888 0031F468  CB 23 00 B8 */	lfd f25, 0xb8(r3)
/* 8032288C 0031F46C  CB 43 00 C0 */	lfd f26, 0xc0(r3)
/* 80322890 0031F470  CB 63 00 C8 */	lfd f27, 0xc8(r3)
/* 80322894 0031F474  CB 83 00 D0 */	lfd f28, 0xd0(r3)
/* 80322898 0031F478  CB A3 00 D8 */	lfd f29, 0xd8(r3)
/* 8032289C 0031F47C  CB C3 00 E0 */	lfd f30, 0xe0(r3)
/* 803228A0 0031F480  C8 03 00 F0 */	lfd f0, 0xf0(r3)
/* 803228A4 0031F484  CB E3 00 E8 */	lfd f31, 0xe8(r3)
/* 803228A8 0031F488  2C 04 00 00 */	cmpwi r4, 0
/* 803228AC 0031F48C  7C 83 23 78 */	mr r3, r4
/* 803228B0 0031F490  FD FE 05 8E */	mtfsf 0xff, f0
/* 803228B4 0031F494  4C 82 00 20 */	bnelr
/* 803228B8 0031F498  38 60 00 01 */	li r3, 1
/* 803228BC 0031F49C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void longjmp(unk_t env, int val)
{
    NOT_IMPLEMENTED;
}

#endif
