#include <common_structs.h>
#include <dolphin/gx/__GXInit.h>

static Vec2 const lbl_804DE290 = { 1024.0F, 0.0F };

// https://decomp.me/scratch/nTyRU // 1150 (70.51%)
#pragma push
asm unk_t GXSetTevIndirect()
{ // clang-format off
    nofralloc
/* 8033F758 0033C338  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033F75C 0033C33C  54 84 07 B6 */	rlwinm r4, r4, 0, 0x1e, 0x1b
/* 8033F760 0033C340  54 A0 10 3A */	slwi r0, r5, 2
/* 8033F764 0033C344  7C 80 03 78 */	or r0, r4, r0
/* 8033F768 0033C348  81 61 00 34 */	lwz r11, 0x34(r1)
/* 8033F76C 0033C34C  54 05 07 30 */	rlwinm r5, r0, 0, 0x1c, 0x18
/* 8033F770 0033C350  89 81 00 33 */	lbz r12, 0x33(r1)
/* 8033F774 0033C354  54 C0 20 36 */	slwi r0, r6, 4
/* 8033F778 0033C358  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033F77C 0033C35C  7C A0 03 78 */	or r0, r5, r0
/* 8033F780 0033C360  54 05 06 6C */	rlwinm r5, r0, 0, 0x19, 0x16
/* 8033F784 0033C364  55 60 38 30 */	slwi r0, r11, 7
/* 8033F788 0033C368  7C A0 03 78 */	or r0, r5, r0
/* 8033F78C 0033C36C  54 05 05 E4 */	rlwinm r5, r0, 0, 0x17, 0x12
/* 8033F790 0033C370  54 E0 48 2C */	slwi r0, r7, 9
/* 8033F794 0033C374  7C A0 03 78 */	or r0, r5, r0
/* 8033F798 0033C378  54 05 04 DE */	rlwinm r5, r0, 0, 0x13, 0xf
/* 8033F79C 0033C37C  55 00 68 24 */	slwi r0, r8, 0xd
/* 8033F7A0 0033C380  7C A0 03 78 */	or r0, r5, r0
/* 8033F7A4 0033C384  38 A3 00 10 */	addi r5, r3, 0x10
/* 8033F7A8 0033C388  54 03 04 18 */	rlwinm r3, r0, 0, 0x10, 0xc
/* 8033F7AC 0033C38C  55 20 80 1E */	slwi r0, r9, 0x10
/* 8033F7B0 0033C390  7C 60 03 78 */	or r0, r3, r0
/* 8033F7B4 0033C394  54 03 03 56 */	rlwinm r3, r0, 0, 0xd, 0xb
/* 8033F7B8 0033C398  55 80 98 18 */	slwi r0, r12, 0x13
/* 8033F7BC 0033C39C  7C 60 03 78 */	or r0, r3, r0
/* 8033F7C0 0033C3A0  54 03 03 14 */	rlwinm r3, r0, 0, 0xc, 0xa
/* 8033F7C4 0033C3A4  55 40 A1 16 */	rlwinm r0, r10, 0x14, 4, 0xb
/* 8033F7C8 0033C3A8  7C 66 03 78 */	or r6, r3, r0
/* 8033F7CC 0033C3AC  38 00 00 61 */	li r0, 0x61
/* 8033F7D0 0033C3B0  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033F7D4 0033C3B4  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 8033F7D8 0033C3B8  54 A0 C0 0E */	slwi r0, r5, 0x18
/* 8033F7DC 0033C3BC  50 C0 02 3E */	rlwimi r0, r6, 0, 8, 0x1f
/* 8033F7E0 0033C3C0  90 03 80 00 */	stw r0, -0x8000(r3)
/* 8033F7E4 0033C3C4  38 00 00 00 */	li r0, 0
/* 8033F7E8 0033C3C8  38 21 00 28 */	addi r1, r1, 0x28
/* 8033F7EC 0033C3CC  B0 04 00 02 */	sth r0, 2(r4)
/* 8033F7F0 0033C3D0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/ctXNh
#pragma push
asm unk_t GXSetIndTexMtx()
{ // clang-format off
    nofralloc
/* 8033F7F4 0033C3D4  2C 03 00 08 */	cmpwi r3, 8
/* 8033F7F8 0033C3D8  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 8033F7FC 0033C3DC  41 82 00 44 */	beq lbl_8033F840
/* 8033F800 0033C3E0  40 80 00 1C */	bge lbl_8033F81C
/* 8033F804 0033C3E4  2C 03 00 04 */	cmpwi r3, 4
/* 8033F808 0033C3E8  41 82 00 38 */	beq lbl_8033F840
/* 8033F80C 0033C3EC  40 80 00 24 */	bge lbl_8033F830
/* 8033F810 0033C3F0  2C 03 00 01 */	cmpwi r3, 1
/* 8033F814 0033C3F4  40 80 00 14 */	bge lbl_8033F828
/* 8033F818 0033C3F8  48 00 00 28 */	b lbl_8033F840
lbl_8033F81C:
/* 8033F81C 0033C3FC  2C 03 00 0C */	cmpwi r3, 0xc
/* 8033F820 0033C400  40 80 00 20 */	bge lbl_8033F840
/* 8033F824 0033C404  48 00 00 14 */	b lbl_8033F838
lbl_8033F828:
/* 8033F828 0033C408  38 03 FF FF */	addi r0, r3, -1
/* 8033F82C 0033C40C  48 00 00 18 */	b lbl_8033F844
lbl_8033F830:
/* 8033F830 0033C410  38 03 FF FB */	addi r0, r3, -5
/* 8033F834 0033C414  48 00 00 10 */	b lbl_8033F844
lbl_8033F838:
/* 8033F838 0033C418  38 03 FF F7 */	addi r0, r3, -9
/* 8033F83C 0033C41C  48 00 00 08 */	b lbl_8033F844
lbl_8033F840:
/* 8033F840 0033C420  38 00 00 00 */	li r0, 0
lbl_8033F844:
/* 8033F844 0033C424  C0 42 E8 B0 */	lfs f2, lbl_804DE290(r2)
/* 8033F848 0033C428  1C 60 00 03 */	mulli r3, r0, 3
/* 8033F84C 0033C42C  C0 24 00 00 */	lfs f1, 0(r4)
/* 8033F850 0033C430  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 8033F854 0033C434  EC 22 00 72 */	fmuls f1, f2, f1
/* 8033F858 0033C438  39 65 00 11 */	addi r11, r5, 0x11
/* 8033F85C 0033C43C  EC 02 00 32 */	fmuls f0, f2, f0
/* 8033F860 0033C440  38 03 00 06 */	addi r0, r3, 6
/* 8033F864 0033C444  7D 6B 07 74 */	extsb r11, r11
/* 8033F868 0033C448  FC 20 08 1E */	fctiwz f1, f1
/* 8033F86C 0033C44C  39 40 00 61 */	li r10, 0x61
/* 8033F870 0033C450  FC 00 00 1E */	fctiwz f0, f0
/* 8033F874 0033C454  3D 20 CC 01 */	lis r9, 0xCC008000@ha
/* 8033F878 0033C458  99 49 80 00 */	stb r10, 0xCC008000@l(r9)
/* 8033F87C 0033C45C  D8 21 00 70 */	stfd f1, 0x70(r1)
/* 8033F880 0033C460  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033F884 0033C464  38 C3 00 07 */	addi r6, r3, 7
/* 8033F888 0033C468  D8 01 00 68 */	stfd f0, 0x68(r1)
/* 8033F88C 0033C46C  38 A3 00 08 */	addi r5, r3, 8
/* 8033F890 0033C470  81 01 00 74 */	lwz r8, 0x74(r1)
/* 8033F894 0033C474  80 E1 00 6C */	lwz r7, 0x6c(r1)
/* 8033F898 0033C478  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F89C 0033C47C  54 E7 5A A8 */	rlwinm r7, r7, 0xb, 0xa, 0x14
/* 8033F8A0 0033C480  51 07 05 7E */	rlwimi r7, r8, 0, 0x15, 0x1f
/* 8033F8A4 0033C484  54 E7 02 8E */	rlwinm r7, r7, 0, 0xa, 7
/* 8033F8A8 0033C488  51 67 B2 12 */	rlwimi r7, r11, 0x16, 8, 9
/* 8033F8AC 0033C48C  50 E0 02 3E */	rlwimi r0, r7, 0, 8, 0x1f
/* 8033F8B0 0033C490  90 09 80 00 */	stw r0, -0x8000(r9)
/* 8033F8B4 0033C494  38 00 00 00 */	li r0, 0
/* 8033F8B8 0033C498  C0 24 00 04 */	lfs f1, 4(r4)
/* 8033F8BC 0033C49C  C0 04 00 10 */	lfs f0, 0x10(r4)
/* 8033F8C0 0033C4A0  EC 22 00 72 */	fmuls f1, f2, f1
/* 8033F8C4 0033C4A4  EC 02 00 32 */	fmuls f0, f2, f0
/* 8033F8C8 0033C4A8  99 49 80 00 */	stb r10, -0x8000(r9)
/* 8033F8CC 0033C4AC  FC 20 08 1E */	fctiwz f1, f1
/* 8033F8D0 0033C4B0  FC 00 00 1E */	fctiwz f0, f0
/* 8033F8D4 0033C4B4  D8 21 00 60 */	stfd f1, 0x60(r1)
/* 8033F8D8 0033C4B8  D8 01 00 58 */	stfd f0, 0x58(r1)
/* 8033F8DC 0033C4BC  81 01 00 64 */	lwz r8, 0x64(r1)
/* 8033F8E0 0033C4C0  80 E1 00 5C */	lwz r7, 0x5c(r1)
/* 8033F8E4 0033C4C4  54 E7 5A A8 */	rlwinm r7, r7, 0xb, 0xa, 0x14
/* 8033F8E8 0033C4C8  51 07 05 7E */	rlwimi r7, r8, 0, 0x15, 0x1f
/* 8033F8EC 0033C4CC  54 E7 02 8E */	rlwinm r7, r7, 0, 0xa, 7
/* 8033F8F0 0033C4D0  51 67 A2 12 */	rlwimi r7, r11, 0x14, 8, 9
/* 8033F8F4 0033C4D4  54 E7 02 3E */	clrlwi r7, r7, 8
/* 8033F8F8 0033C4D8  50 C7 C0 0E */	rlwimi r7, r6, 0x18, 0, 7
/* 8033F8FC 0033C4DC  90 E9 80 00 */	stw r7, -0x8000(r9)
/* 8033F900 0033C4E0  C0 24 00 08 */	lfs f1, 8(r4)
/* 8033F904 0033C4E4  C0 04 00 14 */	lfs f0, 0x14(r4)
/* 8033F908 0033C4E8  EC 22 00 72 */	fmuls f1, f2, f1
/* 8033F90C 0033C4EC  EC 02 00 32 */	fmuls f0, f2, f0
/* 8033F910 0033C4F0  99 49 80 00 */	stb r10, -0x8000(r9)
/* 8033F914 0033C4F4  FC 20 08 1E */	fctiwz f1, f1
/* 8033F918 0033C4F8  FC 00 00 1E */	fctiwz f0, f0
/* 8033F91C 0033C4FC  D8 21 00 50 */	stfd f1, 0x50(r1)
/* 8033F920 0033C500  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 8033F924 0033C504  80 C1 00 54 */	lwz r6, 0x54(r1)
/* 8033F928 0033C508  80 81 00 4C */	lwz r4, 0x4c(r1)
/* 8033F92C 0033C50C  38 21 00 78 */	addi r1, r1, 0x78
/* 8033F930 0033C510  54 84 5A A8 */	rlwinm r4, r4, 0xb, 0xa, 0x14
/* 8033F934 0033C514  50 C4 05 7E */	rlwimi r4, r6, 0, 0x15, 0x1f
/* 8033F938 0033C518  54 84 02 8E */	rlwinm r4, r4, 0, 0xa, 7
/* 8033F93C 0033C51C  51 64 92 12 */	rlwimi r4, r11, 0x12, 8, 9
/* 8033F940 0033C520  54 84 02 3E */	clrlwi r4, r4, 8
/* 8033F944 0033C524  50 A4 C0 0E */	rlwimi r4, r5, 0x18, 0, 7
/* 8033F948 0033C528  90 89 80 00 */	stw r4, -0x8000(r9)
/* 8033F94C 0033C52C  B0 03 00 02 */	sth r0, 2(r3)
/* 8033F950 0033C530  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/VEhb9 // 355 (96.97%)
#pragma push
asm unk_t GXSetIndTexCoordScale()
{ // clang-format off
    nofralloc
/* 8033F954 0033C534  2C 03 00 02 */	cmpwi r3, 2
/* 8033F958 0033C538  41 82 00 F4 */	beq lbl_8033FA4C
/* 8033F95C 0033C53C  40 80 00 14 */	bge lbl_8033F970
/* 8033F960 0033C540  2C 03 00 00 */	cmpwi r3, 0
/* 8033F964 0033C544  41 82 00 18 */	beq lbl_8033F97C
/* 8033F968 0033C548  40 80 00 7C */	bge lbl_8033F9E4
/* 8033F96C 0033C54C  48 00 01 AC */	b lbl_8033FB18
lbl_8033F970:
/* 8033F970 0033C550  2C 03 00 04 */	cmpwi r3, 4
/* 8033F974 0033C554  40 80 01 A4 */	bge lbl_8033FB18
/* 8033F978 0033C558  48 00 01 3C */	b lbl_8033FAB4
lbl_8033F97C:
/* 8033F97C 0033C55C  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033F980 0033C560  54 A3 20 36 */	slwi r3, r5, 4
/* 8033F984 0033C564  38 00 00 61 */	li r0, 0x61
/* 8033F988 0033C568  38 E6 01 28 */	addi r7, r6, 0x128
/* 8033F98C 0033C56C  80 C6 01 28 */	lwz r6, 0x128(r6)
/* 8033F990 0033C570  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033F994 0033C574  54 C6 00 36 */	rlwinm r6, r6, 0, 0, 0x1b
/* 8033F998 0033C578  7C C4 23 78 */	or r4, r6, r4
/* 8033F99C 0033C57C  90 87 00 00 */	stw r4, 0(r7)
/* 8033F9A0 0033C580  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033F9A4 0033C584  38 C4 01 28 */	addi r6, r4, 0x128
/* 8033F9A8 0033C588  80 84 01 28 */	lwz r4, 0x128(r4)
/* 8033F9AC 0033C58C  54 84 07 2E */	rlwinm r4, r4, 0, 0x1c, 0x17
/* 8033F9B0 0033C590  7C 83 1B 78 */	or r3, r4, r3
/* 8033F9B4 0033C594  90 66 00 00 */	stw r3, 0(r6)
/* 8033F9B8 0033C598  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F9BC 0033C59C  38 83 01 28 */	addi r4, r3, 0x128
/* 8033F9C0 0033C5A0  80 63 01 28 */	lwz r3, 0x128(r3)
/* 8033F9C4 0033C5A4  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033F9C8 0033C5A8  64 63 25 00 */	oris r3, r3, 0x2500
/* 8033F9CC 0033C5AC  90 64 00 00 */	stw r3, 0(r4)
/* 8033F9D0 0033C5B0  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033F9D4 0033C5B4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F9D8 0033C5B8  80 03 01 28 */	lwz r0, 0x128(r3)
/* 8033F9DC 0033C5BC  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033F9E0 0033C5C0  48 00 01 38 */	b lbl_8033FB18
lbl_8033F9E4:
/* 8033F9E4 0033C5C4  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033F9E8 0033C5C8  54 A3 60 26 */	slwi r3, r5, 0xc
/* 8033F9EC 0033C5CC  84 A7 01 28 */	lwzu r5, 0x128(r7)
/* 8033F9F0 0033C5D0  54 86 40 2E */	slwi r6, r4, 8
/* 8033F9F4 0033C5D4  38 00 00 61 */	li r0, 0x61
/* 8033F9F8 0033C5D8  54 A5 06 26 */	rlwinm r5, r5, 0, 0x18, 0x13
/* 8033F9FC 0033C5DC  7C A5 33 78 */	or r5, r5, r6
/* 8033FA00 0033C5E0  90 A7 00 00 */	stw r5, 0(r7)
/* 8033FA04 0033C5E4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033FA08 0033C5E8  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033FA0C 0033C5EC  38 C5 01 28 */	addi r6, r5, 0x128
/* 8033FA10 0033C5F0  80 A5 01 28 */	lwz r5, 0x128(r5)
/* 8033FA14 0033C5F4  54 A5 05 1E */	rlwinm r5, r5, 0, 0x14, 0xf
/* 8033FA18 0033C5F8  7C A3 1B 78 */	or r3, r5, r3
/* 8033FA1C 0033C5FC  90 66 00 00 */	stw r3, 0(r6)
/* 8033FA20 0033C600  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FA24 0033C604  38 A3 01 28 */	addi r5, r3, 0x128
/* 8033FA28 0033C608  80 63 01 28 */	lwz r3, 0x128(r3)
/* 8033FA2C 0033C60C  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033FA30 0033C610  64 63 25 00 */	oris r3, r3, 0x2500
/* 8033FA34 0033C614  90 65 00 00 */	stw r3, 0(r5)
/* 8033FA38 0033C618  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8033FA3C 0033C61C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FA40 0033C620  80 03 01 28 */	lwz r0, 0x128(r3)
/* 8033FA44 0033C624  90 04 80 00 */	stw r0, -0x8000(r4)
/* 8033FA48 0033C628  48 00 00 D0 */	b lbl_8033FB18
lbl_8033FA4C:
/* 8033FA4C 0033C62C  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033FA50 0033C630  54 A3 20 36 */	slwi r3, r5, 4
/* 8033FA54 0033C634  38 00 00 61 */	li r0, 0x61
/* 8033FA58 0033C638  38 E6 01 2C */	addi r7, r6, 0x12c
/* 8033FA5C 0033C63C  80 C6 01 2C */	lwz r6, 0x12c(r6)
/* 8033FA60 0033C640  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033FA64 0033C644  54 C6 00 36 */	rlwinm r6, r6, 0, 0, 0x1b
/* 8033FA68 0033C648  7C C4 23 78 */	or r4, r6, r4
/* 8033FA6C 0033C64C  90 87 00 00 */	stw r4, 0(r7)
/* 8033FA70 0033C650  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033FA74 0033C654  38 C4 01 2C */	addi r6, r4, 0x12c
/* 8033FA78 0033C658  80 84 01 2C */	lwz r4, 0x12c(r4)
/* 8033FA7C 0033C65C  54 84 07 2E */	rlwinm r4, r4, 0, 0x1c, 0x17
/* 8033FA80 0033C660  7C 83 1B 78 */	or r3, r4, r3
/* 8033FA84 0033C664  90 66 00 00 */	stw r3, 0(r6)
/* 8033FA88 0033C668  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FA8C 0033C66C  38 83 01 2C */	addi r4, r3, 0x12c
/* 8033FA90 0033C670  80 63 01 2C */	lwz r3, 0x12c(r3)
/* 8033FA94 0033C674  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033FA98 0033C678  64 63 26 00 */	oris r3, r3, 0x2600
/* 8033FA9C 0033C67C  90 64 00 00 */	stw r3, 0(r4)
/* 8033FAA0 0033C680  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033FAA4 0033C684  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FAA8 0033C688  80 03 01 2C */	lwz r0, 0x12c(r3)
/* 8033FAAC 0033C68C  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033FAB0 0033C690  48 00 00 68 */	b lbl_8033FB18
lbl_8033FAB4:
/* 8033FAB4 0033C694  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033FAB8 0033C698  54 A3 60 26 */	slwi r3, r5, 0xc
/* 8033FABC 0033C69C  84 A7 01 2C */	lwzu r5, 0x12c(r7)
/* 8033FAC0 0033C6A0  54 86 40 2E */	slwi r6, r4, 8
/* 8033FAC4 0033C6A4  38 00 00 61 */	li r0, 0x61
/* 8033FAC8 0033C6A8  54 A5 06 26 */	rlwinm r5, r5, 0, 0x18, 0x13
/* 8033FACC 0033C6AC  7C A5 33 78 */	or r5, r5, r6
/* 8033FAD0 0033C6B0  90 A7 00 00 */	stw r5, 0(r7)
/* 8033FAD4 0033C6B4  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033FAD8 0033C6B8  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033FADC 0033C6BC  38 C5 01 2C */	addi r6, r5, 0x12c
/* 8033FAE0 0033C6C0  80 A5 01 2C */	lwz r5, 0x12c(r5)
/* 8033FAE4 0033C6C4  54 A5 05 1E */	rlwinm r5, r5, 0, 0x14, 0xf
/* 8033FAE8 0033C6C8  7C A3 1B 78 */	or r3, r5, r3
/* 8033FAEC 0033C6CC  90 66 00 00 */	stw r3, 0(r6)
/* 8033FAF0 0033C6D0  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FAF4 0033C6D4  38 A3 01 2C */	addi r5, r3, 0x12c
/* 8033FAF8 0033C6D8  80 63 01 2C */	lwz r3, 0x12c(r3)
/* 8033FAFC 0033C6DC  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033FB00 0033C6E0  64 63 26 00 */	oris r3, r3, 0x2600
/* 8033FB04 0033C6E4  90 65 00 00 */	stw r3, 0(r5)
/* 8033FB08 0033C6E8  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8033FB0C 0033C6EC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FB10 0033C6F0  80 03 01 2C */	lwz r0, 0x12c(r3)
/* 8033FB14 0033C6F4  90 04 80 00 */	stw r0, -0x8000(r4)
lbl_8033FB18:
/* 8033FB18 0033C6F8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FB1C 0033C6FC  38 00 00 00 */	li r0, 0
/* 8033FB20 0033C700  B0 03 00 02 */	sth r0, 2(r3)
/* 8033FB24 0033C704  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/Zyr7j
#pragma push
asm unk_t GXSetIndTexOrder()
{ // clang-format off
    nofralloc
/* 8033FB28 0033C708  2C 03 00 02 */	cmpwi r3, 2
/* 8033FB2C 0033C70C  41 82 00 94 */	beq lbl_8033FBC0
/* 8033FB30 0033C710  40 80 00 14 */	bge lbl_8033FB44
/* 8033FB34 0033C714  2C 03 00 00 */	cmpwi r3, 0
/* 8033FB38 0033C718  41 82 00 18 */	beq lbl_8033FB50
/* 8033FB3C 0033C71C  40 80 00 4C */	bge lbl_8033FB88
/* 8033FB40 0033C720  48 00 00 EC */	b lbl_8033FC2C
lbl_8033FB44:
/* 8033FB44 0033C724  2C 03 00 04 */	cmpwi r3, 4
/* 8033FB48 0033C728  40 80 00 E4 */	bge lbl_8033FC2C
/* 8033FB4C 0033C72C  48 00 00 AC */	b lbl_8033FBF8
lbl_8033FB50:
/* 8033FB50 0033C730  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FB54 0033C734  54 80 18 38 */	slwi r0, r4, 3
/* 8033FB58 0033C738  38 83 01 20 */	addi r4, r3, 0x120
/* 8033FB5C 0033C73C  80 63 01 20 */	lwz r3, 0x120(r3)
/* 8033FB60 0033C740  54 63 00 38 */	rlwinm r3, r3, 0, 0, 0x1c
/* 8033FB64 0033C744  7C 63 2B 78 */	or r3, r3, r5
/* 8033FB68 0033C748  90 64 00 00 */	stw r3, 0(r4)
/* 8033FB6C 0033C74C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FB70 0033C750  38 83 01 20 */	addi r4, r3, 0x120
/* 8033FB74 0033C754  80 63 01 20 */	lwz r3, 0x120(r3)
/* 8033FB78 0033C758  54 63 07 72 */	rlwinm r3, r3, 0, 0x1d, 0x19
/* 8033FB7C 0033C75C  7C 60 03 78 */	or r0, r3, r0
/* 8033FB80 0033C760  90 04 00 00 */	stw r0, 0(r4)
/* 8033FB84 0033C764  48 00 00 A8 */	b lbl_8033FC2C
lbl_8033FB88:
/* 8033FB88 0033C768  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033FB8C 0033C76C  54 80 48 2C */	slwi r0, r4, 9
/* 8033FB90 0033C770  54 A3 30 32 */	slwi r3, r5, 6
/* 8033FB94 0033C774  80 86 01 20 */	lwz r4, 0x120(r6)
/* 8033FB98 0033C778  54 84 06 AC */	rlwinm r4, r4, 0, 0x1a, 0x16
/* 8033FB9C 0033C77C  7C 83 1B 78 */	or r3, r4, r3
/* 8033FBA0 0033C780  90 66 01 20 */	stw r3, 0x120(r6)
/* 8033FBA4 0033C784  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FBA8 0033C788  38 83 01 20 */	addi r4, r3, 0x120
/* 8033FBAC 0033C78C  80 63 01 20 */	lwz r3, 0x120(r3)
/* 8033FBB0 0033C790  54 63 05 E6 */	rlwinm r3, r3, 0, 0x17, 0x13
/* 8033FBB4 0033C794  7C 60 03 78 */	or r0, r3, r0
/* 8033FBB8 0033C798  90 04 00 00 */	stw r0, 0(r4)
/* 8033FBBC 0033C79C  48 00 00 70 */	b lbl_8033FC2C
lbl_8033FBC0:
/* 8033FBC0 0033C7A0  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033FBC4 0033C7A4  54 80 78 20 */	slwi r0, r4, 0xf
/* 8033FBC8 0033C7A8  54 A3 60 26 */	slwi r3, r5, 0xc
/* 8033FBCC 0033C7AC  80 86 01 20 */	lwz r4, 0x120(r6)
/* 8033FBD0 0033C7B0  54 84 05 20 */	rlwinm r4, r4, 0, 0x14, 0x10
/* 8033FBD4 0033C7B4  7C 83 1B 78 */	or r3, r4, r3
/* 8033FBD8 0033C7B8  90 66 01 20 */	stw r3, 0x120(r6)
/* 8033FBDC 0033C7BC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FBE0 0033C7C0  38 83 01 20 */	addi r4, r3, 0x120
/* 8033FBE4 0033C7C4  80 63 01 20 */	lwz r3, 0x120(r3)
/* 8033FBE8 0033C7C8  54 63 04 5A */	rlwinm r3, r3, 0, 0x11, 0xd
/* 8033FBEC 0033C7CC  7C 60 03 78 */	or r0, r3, r0
/* 8033FBF0 0033C7D0  90 04 00 00 */	stw r0, 0(r4)
/* 8033FBF4 0033C7D4  48 00 00 38 */	b lbl_8033FC2C
lbl_8033FBF8:
/* 8033FBF8 0033C7D8  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033FBFC 0033C7DC  54 80 A8 14 */	slwi r0, r4, 0x15
/* 8033FC00 0033C7E0  54 A3 90 1A */	slwi r3, r5, 0x12
/* 8033FC04 0033C7E4  80 86 01 20 */	lwz r4, 0x120(r6)
/* 8033FC08 0033C7E8  54 84 03 94 */	rlwinm r4, r4, 0, 0xe, 0xa
/* 8033FC0C 0033C7EC  7C 83 1B 78 */	or r3, r4, r3
/* 8033FC10 0033C7F0  90 66 01 20 */	stw r3, 0x120(r6)
/* 8033FC14 0033C7F4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FC18 0033C7F8  38 83 01 20 */	addi r4, r3, 0x120
/* 8033FC1C 0033C7FC  80 63 01 20 */	lwz r3, 0x120(r3)
/* 8033FC20 0033C800  54 63 02 CE */	rlwinm r3, r3, 0, 0xb, 7
/* 8033FC24 0033C804  7C 60 03 78 */	or r0, r3, r0
/* 8033FC28 0033C808  90 04 00 00 */	stw r0, 0(r4)
lbl_8033FC2C:
/* 8033FC2C 0033C80C  38 00 00 61 */	li r0, 0x61
/* 8033FC30 0033C810  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033FC34 0033C814  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033FC38 0033C818  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033FC3C 0033C81C  38 00 00 00 */	li r0, 0
/* 8033FC40 0033C820  80 64 01 20 */	lwz r3, 0x120(r4)
/* 8033FC44 0033C824  90 65 80 00 */	stw r3, -0x8000(r5)
/* 8033FC48 0033C828  80 64 04 F0 */	lwz r3, 0x4f0(r4)
/* 8033FC4C 0033C82C  60 63 00 03 */	ori r3, r3, 3
/* 8033FC50 0033C830  90 64 04 F0 */	stw r3, 0x4f0(r4)
/* 8033FC54 0033C834  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FC58 0033C838  B0 03 00 02 */	sth r0, 2(r3)
/* 8033FC5C 0033C83C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void GXSetNumIndStages(s32 arg0)
{
    GXContext* temp_r3;
    GXContext* temp_r4;

    temp_r4 = __GXContexts.main;
    temp_r4->x100_data[0x41] = (temp_r4->x100_data[0x41] & 0xFFF8FFFF) | ((arg0 << 0x10) & 0xFF0000);
    temp_r3 = __GXContexts.main;
    temp_r3->x4F0_flags |= 6;
}

// https://decomp.me/scratch/aRJcf // 362 (79.89%)
#pragma push
asm unk_t GXSetTevDirect()
{ // clang-format off
    nofralloc
/* 8033FC8C 0033C86C  7C 08 02 A6 */	mflr r0
/* 8033FC90 0033C870  38 80 00 00 */	li r4, 0
/* 8033FC94 0033C874  90 01 00 04 */	stw r0, 4(r1)
/* 8033FC98 0033C878  38 00 00 00 */	li r0, 0
/* 8033FC9C 0033C87C  38 A0 00 00 */	li r5, 0
/* 8033FCA0 0033C880  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033FCA4 0033C884  38 C0 00 00 */	li r6, 0
/* 8033FCA8 0033C888  38 E0 00 00 */	li r7, 0
/* 8033FCAC 0033C88C  90 01 00 08 */	stw r0, 8(r1)
/* 8033FCB0 0033C890  39 00 00 00 */	li r8, 0
/* 8033FCB4 0033C894  39 20 00 00 */	li r9, 0
/* 8033FCB8 0033C898  90 01 00 0C */	stw r0, 0xc(r1)
/* 8033FCBC 0033C89C  39 40 00 00 */	li r10, 0
/* 8033FCC0 0033C8A0  4B FF FA 99 */	bl GXSetTevIndirect
/* 8033FCC4 0033C8A4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033FCC8 0033C8A8  38 21 00 18 */	addi r1, r1, 0x18
/* 8033FCCC 0033C8AC  7C 08 03 A6 */	mtlr r0
/* 8033FCD0 0033C8B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __GXUpdateBPMask()
{ // clang-format off
    nofralloc
/* 8033FCD4 0033C8B4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033FCD8 0033C8B8  38 C0 00 00 */	li r6, 0
/* 8033FCDC 0033C8BC  38 80 00 00 */	li r4, 0
/* 8033FCE0 0033C8C0  80 03 02 04 */	lwz r0, 0x204(r3)
/* 8033FCE4 0033C8C4  54 00 87 7E */	rlwinm r0, r0, 0x10, 0x1d, 0x1f
/* 8033FCE8 0033C8C8  28 00 00 00 */	cmplwi r0, 0
/* 8033FCEC 0033C8CC  7C 09 03 A6 */	mtctr r0
/* 8033FCF0 0033C8D0  40 81 00 6C */	ble lbl_8033FD5C
lbl_8033FCF4:
/* 8033FCF4 0033C8D4  2C 04 00 02 */	cmpwi r4, 2
/* 8033FCF8 0033C8D8  41 82 00 3C */	beq lbl_8033FD34
/* 8033FCFC 0033C8DC  40 80 00 14 */	bge lbl_8033FD10
/* 8033FD00 0033C8E0  2C 04 00 00 */	cmpwi r4, 0
/* 8033FD04 0033C8E4  41 82 00 18 */	beq lbl_8033FD1C
/* 8033FD08 0033C8E8  40 80 00 20 */	bge lbl_8033FD28
/* 8033FD0C 0033C8EC  48 00 00 3C */	b lbl_8033FD48
lbl_8033FD10:
/* 8033FD10 0033C8F0  2C 04 00 04 */	cmpwi r4, 4
/* 8033FD14 0033C8F4  40 80 00 34 */	bge lbl_8033FD48
/* 8033FD18 0033C8F8  48 00 00 28 */	b lbl_8033FD40
lbl_8033FD1C:
/* 8033FD1C 0033C8FC  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033FD20 0033C900  54 05 07 7E */	clrlwi r5, r0, 0x1d
/* 8033FD24 0033C904  48 00 00 24 */	b lbl_8033FD48
lbl_8033FD28:
/* 8033FD28 0033C908  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033FD2C 0033C90C  54 05 D7 7E */	rlwinm r5, r0, 0x1a, 0x1d, 0x1f
/* 8033FD30 0033C910  48 00 00 18 */	b lbl_8033FD48
lbl_8033FD34:
/* 8033FD34 0033C914  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033FD38 0033C918  54 05 A7 7E */	rlwinm r5, r0, 0x14, 0x1d, 0x1f
/* 8033FD3C 0033C91C  48 00 00 0C */	b lbl_8033FD48
lbl_8033FD40:
/* 8033FD40 0033C920  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033FD44 0033C924  54 05 77 7E */	rlwinm r5, r0, 0xe, 0x1d, 0x1f
lbl_8033FD48:
/* 8033FD48 0033C928  38 00 00 01 */	li r0, 1
/* 8033FD4C 0033C92C  7C 00 28 30 */	slw r0, r0, r5
/* 8033FD50 0033C930  7C C6 03 78 */	or r6, r6, r0
/* 8033FD54 0033C934  38 84 00 01 */	addi r4, r4, 1
/* 8033FD58 0033C938  42 00 FF 9C */	bdnz lbl_8033FCF4
lbl_8033FD5C:
/* 8033FD5C 0033C93C  38 83 01 24 */	addi r4, r3, 0x124
/* 8033FD60 0033C940  80 63 01 24 */	lwz r3, 0x124(r3)
/* 8033FD64 0033C944  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 8033FD68 0033C948  7C 00 30 40 */	cmplw r0, r6
/* 8033FD6C 0033C94C  4D 82 00 20 */	beqlr 
/* 8033FD70 0033C950  54 60 00 2E */	rlwinm r0, r3, 0, 0, 0x17
/* 8033FD74 0033C954  7C 00 33 78 */	or r0, r0, r6
/* 8033FD78 0033C958  90 04 00 00 */	stw r0, 0(r4)
/* 8033FD7C 0033C95C  38 00 00 61 */	li r0, 0x61
/* 8033FD80 0033C960  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033FD84 0033C964  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033FD88 0033C968  38 00 00 00 */	li r0, 0
/* 8033FD8C 0033C96C  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033FD90 0033C970  80 64 01 24 */	lwz r3, 0x124(r4)
/* 8033FD94 0033C974  90 65 80 00 */	stw r3, -0x8000(r5)
/* 8033FD98 0033C978  B0 04 00 02 */	sth r0, 2(r4)
/* 8033FD9C 0033C97C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void __GXFlushTextureState(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = __GXContexts.main->x100_data[9];
    set_x2(GX_FALSE);
}
