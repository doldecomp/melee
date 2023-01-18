#include <dolphin/gx/GXFrameBuf.h>

#include <common_structs.h>
#include <dolphin/gx/__GX_unknown_001.h>
#include <dolphin/gx/__GXInit.h>
#include <dolphin/gx/forward.h>
#include <placeholder.h>

Vec2 const lbl_804DE220 = { 256.0F, 0.0F };
Vec2 const lbl_804DE228 = { 176.0F, 0.0F };

GXRenderModeObj GXNtsc480IntDf = {
    0,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

GXRenderModeObj lbl_804011A4 = {
    0,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 0, 0, 21, 22, 21, 0, 0 },
};

GXRenderModeObj lbl_804011E0 = {
    2,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    0,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 0, 0, 21, 22, 21, 0, 0 },
};

GXRenderModeObj GXMpal480IntDf = {
    8,
    640,
    480,
    480,
    40,
    0,
    640,
    480,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

GXRenderModeObj GXPal528IntDf = {
    4,
    640,
    528,
    528,
    40,
    23,
    640,
    528,
    1,
    0,
    0,
    { { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 },
      { 6, 6 } },
    { 8, 8, 10, 12, 10, 8, 8 },
};

void GXSetDispCopySrc(u16 arg0, u32 arg1, u16 arg2, u16 arg3)
{
    __GXContexts.main->x1D0[4] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[4], arg0, 10, 0);
    __GXContexts.main->x1D0[4] = (__GXContexts.main->x1D0[4] & 0xFFF003FF) |
                                 ((u32) (arg1 << 10) & 0x03FFFC00);
    INSERT_FIELD(__GXContexts.main->x1D0[4], 73, 8, 24);
    __GXContexts.main->x1D0[5] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[5], arg2 - 1, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[5], arg3 - 1, 10, 10);
    INSERT_FIELD(__GXContexts.main->x1D0[5], 74, 8, 24);
}

void GXSetTexCopySrc(u16 arg0, u32 arg1, u16 arg2, u16 arg3)
{
    __GXContexts.main->x1D0[8] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[8], arg0, 10, 0);
    __GXContexts.main->x1D0[8] =
        (((u32) __GXContexts.main->x1D0[8] & 0xFFF003FF) |
         ((u32) (arg1 << 10) & 0x03FFFC00));
    INSERT_FIELD(__GXContexts.main->x1D0[8], 73, 8, 24);
    __GXContexts.main->x1D0[9] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[9], arg2 - 1, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[9], arg3 - 1, 10, 10);
    INSERT_FIELD(__GXContexts.main->x1D0[9], 74, 8, 24);
}

void GXSetDispCopyDst(s32 arg0)
{
    s32 val = (s32) ((u32) (arg0 << 1) & 0xFFFE) >> 5;
    __GXContexts.main->x1D0[6] = 0;
    INSERT_FIELD(__GXContexts.main->x1D0[6], val, 10, 0);
    INSERT_FIELD(__GXContexts.main->x1D0[6], 77, 8, 24);
}

extern unk_t __GetImageTileCount(void);
extern unk_t __cvt_fp2unsigned(void);

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetTexCopyDst(s32, s32, s32, s32)
{ // clang-format off
    nofralloc
/* 8033D5CC 0033A1AC  7C 08 02 A6 */	mflr r0
/* 8033D5D0 0033A1B0  2C 05 00 13 */	cmpwi r5, 0x13
/* 8033D5D4 0033A1B4  90 01 00 04 */	stw r0, 4(r1)
/* 8033D5D8 0033A1B8  38 00 00 00 */	li r0, 0
/* 8033D5DC 0033A1BC  39 03 00 00 */	addi r8, r3, 0
/* 8033D5E0 0033A1C0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8033D5E4 0033A1C4  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8033D5E8 0033A1C8  54 BF 07 3E */	clrlwi r31, r5, 0x1c
/* 8033D5EC 0033A1CC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8033D5F0 0033A1D0  3B C6 00 00 */	addi r30, r6, 0
/* 8033D5F4 0033A1D4  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033D5F8 0033A1D8  98 07 02 00 */	stb r0, 0x200(r7)
/* 8033D5FC 0033A1DC  38 E4 00 00 */	addi r7, r4, 0
/* 8033D600 0033A1E0  40 82 00 08 */	bne lbl_8033D608
/* 8033D604 0033A1E4  3B E0 00 0B */	li r31, 0xb
lbl_8033D608:
/* 8033D608 0033A1E8  2C 05 00 26 */	cmpwi r5, 0x26
/* 8033D60C 0033A1EC  41 82 00 1C */	beq lbl_8033D628
/* 8033D610 0033A1F0  40 80 00 34 */	bge lbl_8033D644
/* 8033D614 0033A1F4  2C 05 00 04 */	cmpwi r5, 4
/* 8033D618 0033A1F8  40 80 00 2C */	bge lbl_8033D644
/* 8033D61C 0033A1FC  2C 05 00 00 */	cmpwi r5, 0
/* 8033D620 0033A200  40 80 00 08 */	bge lbl_8033D628
/* 8033D624 0033A204  48 00 00 20 */	b lbl_8033D644
lbl_8033D628:
/* 8033D628 0033A208  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D62C 0033A20C  84 03 01 FC */	lwzu r0, 0x1fc(r3)
/* 8033D630 0033A210  54 00 04 5C */	rlwinm r0, r0, 0, 0x11, 0xe
/* 8033D634 0033A214  64 00 00 01 */	oris r0, r0, 1
/* 8033D638 0033A218  60 00 80 00 */	ori r0, r0, 0x8000
/* 8033D63C 0033A21C  90 03 00 00 */	stw r0, 0(r3)
/* 8033D640 0033A220  48 00 00 18 */	b lbl_8033D658
lbl_8033D644:
/* 8033D644 0033A224  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D648 0033A228  84 03 01 FC */	lwzu r0, 0x1fc(r3)
/* 8033D64C 0033A22C  54 00 04 5C */	rlwinm r0, r0, 0, 0x11, 0xe
/* 8033D650 0033A230  64 00 00 01 */	oris r0, r0, 1
/* 8033D654 0033A234  90 03 00 00 */	stw r0, 0(r3)
lbl_8033D658:
/* 8033D658 0033A238  54 A4 06 F6 */	rlwinm r4, r5, 0, 0x1b, 0x1b
/* 8033D65C 0033A23C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D660 0033A240  38 04 FF F0 */	addi r0, r4, -16
/* 8033D664 0033A244  7C 00 00 34 */	cntlzw r0, r0
/* 8033D668 0033A248  54 00 DE 3E */	rlwinm r0, r0, 0x1b, 0x18, 0x1f
/* 8033D66C 0033A24C  98 03 02 00 */	stb r0, 0x200(r3)
/* 8033D670 0033A250  38 65 00 00 */	addi r3, r5, 0
/* 8033D674 0033A254  38 A7 00 00 */	addi r5, r7, 0
/* 8033D678 0033A258  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D67C 0033A25C  38 E1 00 1C */	addi r7, r1, 0x1c
/* 8033D680 0033A260  80 04 01 FC */	lwz r0, 0x1fc(r4)
/* 8033D684 0033A264  38 C4 01 FC */	addi r6, r4, 0x1fc
/* 8033D688 0033A268  38 88 00 00 */	addi r4, r8, 0
/* 8033D68C 0033A26C  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8033D690 0033A270  53 E0 07 38 */	rlwimi r0, r31, 0, 0x1c, 0x1c
/* 8033D694 0033A274  90 06 00 00 */	stw r0, 0(r6)
/* 8033D698 0033A278  57 FF 07 7E */	clrlwi r31, r31, 0x1d
/* 8033D69C 0033A27C  38 C1 00 20 */	addi r6, r1, 0x20
/* 8033D6A0 0033A280  39 01 00 18 */	addi r8, r1, 0x18
/* 8033D6A4 0033A284  48 00 12 45 */	bl __GetImageTileCount
/* 8033D6A8 0033A288  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D6AC 0033A28C  38 00 00 00 */	li r0, 0
/* 8033D6B0 0033A290  90 03 01 F8 */	stw r0, 0x1f8(r3)
/* 8033D6B4 0033A294  57 C3 4B EC */	rlwinm r3, r30, 9, 0xf, 0x16
/* 8033D6B8 0033A298  57 E0 20 36 */	slwi r0, r31, 4
/* 8033D6BC 0033A29C  80 A1 00 20 */	lwz r5, 0x20(r1)
/* 8033D6C0 0033A2A0  80 81 00 18 */	lwz r4, 0x18(r1)
/* 8033D6C4 0033A2A4  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033D6C8 0033A2A8  7C 85 21 D6 */	mullw r4, r5, r4
/* 8033D6CC 0033A2AC  84 A6 01 F8 */	lwzu r5, 0x1f8(r6)
/* 8033D6D0 0033A2B0  54 A5 00 2A */	rlwinm r5, r5, 0, 0, 0x15
/* 8033D6D4 0033A2B4  7C A4 23 78 */	or r4, r5, r4
/* 8033D6D8 0033A2B8  90 86 00 00 */	stw r4, 0(r6)
/* 8033D6DC 0033A2BC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D6E0 0033A2C0  38 A4 01 F8 */	addi r5, r4, 0x1f8
/* 8033D6E4 0033A2C4  80 84 01 F8 */	lwz r4, 0x1f8(r4)
/* 8033D6E8 0033A2C8  54 84 02 3E */	clrlwi r4, r4, 8
/* 8033D6EC 0033A2CC  64 84 4D 00 */	oris r4, r4, 0x4d00
/* 8033D6F0 0033A2D0  90 85 00 00 */	stw r4, 0(r5)
/* 8033D6F4 0033A2D4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D6F8 0033A2D8  38 A4 01 FC */	addi r5, r4, 0x1fc
/* 8033D6FC 0033A2DC  80 84 01 FC */	lwz r4, 0x1fc(r4)
/* 8033D700 0033A2E0  54 84 05 EA */	rlwinm r4, r4, 0, 0x17, 0x15
/* 8033D704 0033A2E4  7C 83 1B 78 */	or r3, r4, r3
/* 8033D708 0033A2E8  90 65 00 00 */	stw r3, 0(r5)
/* 8033D70C 0033A2EC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D710 0033A2F0  38 83 01 FC */	addi r4, r3, 0x1fc
/* 8033D714 0033A2F4  80 63 01 FC */	lwz r3, 0x1fc(r3)
/* 8033D718 0033A2F8  54 63 07 30 */	rlwinm r3, r3, 0, 0x1c, 0x18
/* 8033D71C 0033A2FC  7C 60 03 78 */	or r0, r3, r0
/* 8033D720 0033A300  90 04 00 00 */	stw r0, 0(r4)
/* 8033D724 0033A304  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8033D728 0033A308  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8033D72C 0033A30C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8033D730 0033A310  7C 08 03 A6 */	mtlr r0
/* 8033D734 0033A314  38 21 00 30 */	addi r1, r1, 0x30
/* 8033D738 0033A318  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

void GXSetDispCopyFrame2Field(s32 arg0)
{
    INSERT_FIELD(__GXContexts.main->x1D0[7], arg0, 2, 12);
    INSERT_FIELD(__GXContexts.main->x1D0[11], 0, 2, 12);
}

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetCopyClamp(s32)
{ // clang-format off
    nofralloc
/* 8033D768 0033A348  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033D76C 0033A34C  54 64 07 FE */	clrlwi r4, r3, 0x1f
/* 8033D770 0033A350  38 04 FF FF */	addi r0, r4, -1
/* 8033D774 0033A354  80 85 01 EC */	lwz r4, 0x1ec(r5)
/* 8033D778 0033A358  38 C5 01 EC */	addi r6, r5, 0x1ec
/* 8033D77C 0033A35C  7C 00 00 34 */	cntlzw r0, r0
/* 8033D780 0033A360  54 85 00 3C */	rlwinm r5, r4, 0, 0, 0x1e
/* 8033D784 0033A364  54 04 DE 3E */	rlwinm r4, r0, 0x1b, 0x18, 0x1f
/* 8033D788 0033A368  7C A0 23 78 */	or r0, r5, r4
/* 8033D78C 0033A36C  90 06 00 00 */	stw r0, 0(r6)
/* 8033D790 0033A370  54 63 07 BC */	rlwinm r3, r3, 0, 0x1e, 0x1e
/* 8033D794 0033A374  38 03 FF FE */	addi r0, r3, -2
/* 8033D798 0033A378  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D79C 0033A37C  7C 00 00 34 */	cntlzw r0, r0
/* 8033D7A0 0033A380  54 06 E5 FC */	rlwinm r6, r0, 0x1c, 0x17, 0x1e
/* 8033D7A4 0033A384  38 A3 01 EC */	addi r5, r3, 0x1ec
/* 8033D7A8 0033A388  80 63 01 EC */	lwz r3, 0x1ec(r3)
/* 8033D7AC 0033A38C  54 60 07 FA */	rlwinm r0, r3, 0, 0x1f, 0x1d
/* 8033D7B0 0033A390  7C 00 33 78 */	or r0, r0, r6
/* 8033D7B4 0033A394  90 05 00 00 */	stw r0, 0(r5)
/* 8033D7B8 0033A398  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D7BC 0033A39C  84 03 01 FC */	lwzu r0, 0x1fc(r3)
/* 8033D7C0 0033A3A0  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033D7C4 0033A3A4  7C 00 23 78 */	or r0, r0, r4
/* 8033D7C8 0033A3A8  90 03 00 00 */	stw r0, 0(r3)
/* 8033D7CC 0033A3AC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D7D0 0033A3B0  84 03 01 FC */	lwzu r0, 0x1fc(r3)
/* 8033D7D4 0033A3B4  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 8033D7D8 0033A3B8  7C 00 33 78 */	or r0, r0, r6
/* 8033D7DC 0033A3BC  90 03 00 00 */	stw r0, 0(r3)
/* 8033D7E0 0033A3C0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

#ifdef MWERKS_GEKKO

// https://decomp.me/scratch/ZNlNl // 620 (86.81%)
#pragma push
asm u32 GXSetDispCopyYScale(f32)
{ // clang-format off
    nofralloc
/* 8033D7E4 0033A3C4  7C 08 02 A6 */	mflr r0
/* 8033D7E8 0033A3C8  90 01 00 04 */	stw r0, 4(r1)
/* 8033D7EC 0033A3CC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033D7F0 0033A3D0  C0 02 E8 40 */	lfs f0, lbl_804DE220(r2)
/* 8033D7F4 0033A3D4  EC 20 08 24 */	fdivs f1, f0, f1
/* 8033D7F8 0033A3D8  4B FE 50 C9 */	bl __cvt_fp2unsigned
/* 8033D7FC 0033A3DC  38 00 00 61 */	li r0, 0x61
/* 8033D800 0033A3E0  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D804 0033A3E4  54 63 05 FE */	clrlwi r3, r3, 0x17
/* 8033D808 0033A3E8  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033D80C 0033A3EC  90 61 00 1C */	stw r3, 0x1c(r1)
/* 8033D810 0033A3F0  64 67 4E 00 */	oris r7, r3, 0x4e00
/* 8033D814 0033A3F4  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 8033D818 0033A3F8  38 A0 00 00 */	li r5, 0
/* 8033D81C 0033A3FC  20 63 01 00 */	subfic r3, r3, 0x100
/* 8033D820 0033A400  90 E6 80 00 */	stw r7, -0x8000(r6)
/* 8033D824 0033A404  30 03 FF FF */	addic r0, r3, -1
/* 8033D828 0033A408  7C 60 19 10 */	subfe r3, r0, r3
/* 8033D82C 0033A40C  B0 A4 00 02 */	sth r5, 2(r4)
/* 8033D830 0033A410  3C 00 43 30 */	lis r0, 0x4330
/* 8033D834 0033A414  54 63 53 AA */	rlwinm r3, r3, 0xa, 0xe, 0x15
/* 8033D838 0033A418  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D83C 0033A41C  90 01 00 18 */	stw r0, 0x18(r1)
/* 8033D840 0033A420  38 A4 01 EC */	addi r5, r4, 0x1ec
/* 8033D844 0033A424  80 84 01 EC */	lwz r4, 0x1ec(r4)
/* 8033D848 0033A428  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8033D84C 0033A42C  54 84 05 A8 */	rlwinm r4, r4, 0, 0x16, 0x14
/* 8033D850 0033A430  7C 83 1B 78 */	or r3, r4, r3
/* 8033D854 0033A434  90 65 00 00 */	stw r3, 0(r5)
/* 8033D858 0033A438  C8 42 E8 48 */	lfd f2, lbl_804DE228(r2)
/* 8033D85C 0033A43C  C0 22 E8 40 */	lfs f1, lbl_804DE220(r2)
/* 8033D860 0033A440  EC 00 10 28 */	fsubs f0, f0, f2
/* 8033D864 0033A444  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033D868 0033A448  80 63 01 E4 */	lwz r3, 0x1e4(r3)
/* 8033D86C 0033A44C  EC 01 00 24 */	fdivs f0, f1, f0
/* 8033D870 0033A450  54 63 B5 BE */	rlwinm r3, r3, 0x16, 0x16, 0x1f
/* 8033D874 0033A454  38 63 00 01 */	addi r3, r3, 1
/* 8033D878 0033A458  90 61 00 24 */	stw r3, 0x24(r1)
/* 8033D87C 0033A45C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8033D880 0033A460  C8 21 00 20 */	lfd f1, 0x20(r1)
/* 8033D884 0033A464  EC 21 10 28 */	fsubs f1, f1, f2
/* 8033D888 0033A468  EC 21 00 32 */	fmuls f1, f1, f0
/* 8033D88C 0033A46C  4B FE 50 35 */	bl __cvt_fp2unsigned
/* 8033D890 0033A470  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8033D894 0033A474  38 21 00 28 */	addi r1, r1, 0x28
/* 8033D898 0033A478  7C 08 03 A6 */	mtlr r0
/* 8033D89C 0033A47C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetCopyClear(u8*, s32)
{ // clang-format off
    nofralloc
/* 8033D8A0 0033A480  54 80 02 3E */	clrlwi r0, r4, 8
/* 8033D8A4 0033A484  88 83 00 03 */	lbz r4, 3(r3)
/* 8033D8A8 0033A488  88 A3 00 00 */	lbz r5, 0(r3)
/* 8033D8AC 0033A48C  38 C0 00 61 */	li r6, 0x61
/* 8033D8B0 0033A490  54 87 40 2E */	slwi r7, r4, 8
/* 8033D8B4 0033A494  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033D8B8 0033A498  50 A7 06 3E */	rlwimi r7, r5, 0, 0x18, 0x1f
/* 8033D8BC 0033A49C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033D8C0 0033A4A0  54 E7 02 3E */	clrlwi r7, r7, 8
/* 8033D8C4 0033A4A4  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 8033D8C8 0033A4A8  64 E7 4F 00 */	oris r7, r7, 0x4f00
/* 8033D8CC 0033A4AC  90 E5 80 00 */	stw r7, -0x8000(r5)
/* 8033D8D0 0033A4B0  64 07 51 00 */	oris r7, r0, 0x5100
/* 8033D8D4 0033A4B4  38 00 00 00 */	li r0, 0
/* 8033D8D8 0033A4B8  89 03 00 02 */	lbz r8, 2(r3)
/* 8033D8DC 0033A4BC  88 63 00 01 */	lbz r3, 1(r3)
/* 8033D8E0 0033A4C0  54 63 40 2E */	slwi r3, r3, 8
/* 8033D8E4 0033A4C4  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033D8E8 0033A4C8  51 03 06 3E */	rlwimi r3, r8, 0, 0x18, 0x1f
/* 8033D8EC 0033A4CC  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033D8F0 0033A4D0  64 63 50 00 */	oris r3, r3, 0x5000
/* 8033D8F4 0033A4D4  90 65 80 00 */	stw r3, -0x8000(r5)
/* 8033D8F8 0033A4D8  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033D8FC 0033A4DC  90 E5 80 00 */	stw r7, -0x8000(r5)
/* 8033D900 0033A4E0  B0 04 00 02 */	sth r0, 2(r4)
/* 8033D904 0033A4E4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXSetCopyFilter(s8, u8*, s8, u8*)
{ // clang-format off
    nofralloc
/* 8033D908 0033A4E8  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8033D90C 0033A4EC  54 60 06 3F */	clrlwi. r0, r3, 0x18
/* 8033D910 0033A4F0  BE E1 00 2C */	stmw r23, 0x2c(r1)
/* 8033D914 0033A4F4  41 82 01 28 */	beq lbl_8033DA3C
/* 8033D918 0033A4F8  88 04 00 01 */	lbz r0, 1(r4)
/* 8033D91C 0033A4FC  88 64 00 07 */	lbz r3, 7(r4)
/* 8033D920 0033A500  54 1E 20 36 */	slwi r30, r0, 4
/* 8033D924 0033A504  89 04 00 00 */	lbz r8, 0(r4)
/* 8033D928 0033A508  88 04 00 13 */	lbz r0, 0x13(r4)
/* 8033D92C 0033A50C  54 79 20 36 */	slwi r25, r3, 4
/* 8033D930 0033A510  89 44 00 06 */	lbz r10, 6(r4)
/* 8033D934 0033A514  51 1E 07 3E */	rlwimi r30, r8, 0, 0x1c, 0x1f
/* 8033D938 0033A518  89 64 00 02 */	lbz r11, 2(r4)
/* 8033D93C 0033A51C  88 E4 00 0D */	lbz r7, 0xd(r4)
/* 8033D940 0033A520  51 59 07 3E */	rlwimi r25, r10, 0, 0x1c, 0x1f
/* 8033D944 0033A524  55 7B 40 2E */	slwi r27, r11, 8
/* 8033D948 0033A528  89 24 00 08 */	lbz r9, 8(r4)
/* 8033D94C 0033A52C  88 64 00 0E */	lbz r3, 0xe(r4)
/* 8033D950 0033A530  55 3A 40 2E */	slwi r26, r9, 8
/* 8033D954 0033A534  8B 84 00 03 */	lbz r28, 3(r4)
/* 8033D958 0033A538  53 DB 06 3E */	rlwimi r27, r30, 0, 0x18, 0x1f
/* 8033D95C 0033A53C  89 24 00 10 */	lbz r9, 0x10(r4)
/* 8033D960 0033A540  54 F7 20 36 */	slwi r23, r7, 4
/* 8033D964 0033A544  89 84 00 0C */	lbz r12, 0xc(r4)
/* 8033D968 0033A548  88 E4 00 15 */	lbz r7, 0x15(r4)
/* 8033D96C 0033A54C  54 78 40 2E */	slwi r24, r3, 8
/* 8033D970 0033A550  51 97 07 3E */	rlwimi r23, r12, 0, 0x1c, 0x1f
/* 8033D974 0033A554  8B A4 00 12 */	lbz r29, 0x12(r4)
/* 8033D978 0033A558  54 00 20 36 */	slwi r0, r0, 4
/* 8033D97C 0033A55C  53 A0 07 3E */	rlwimi r0, r29, 0, 0x1c, 0x1f
/* 8033D980 0033A560  89 04 00 14 */	lbz r8, 0x14(r4)
/* 8033D984 0033A564  57 9C 60 26 */	slwi r28, r28, 0xc
/* 8033D988 0033A568  8B E4 00 09 */	lbz r31, 9(r4)
/* 8033D98C 0033A56C  53 7C 05 3E */	rlwimi r28, r27, 0, 0x14, 0x1f
/* 8033D990 0033A570  8B A4 00 04 */	lbz r29, 4(r4)
/* 8033D994 0033A574  52 F8 06 3E */	rlwimi r24, r23, 0, 0x18, 0x1f
/* 8033D998 0033A578  89 44 00 0F */	lbz r10, 0xf(r4)
/* 8033D99C 0033A57C  55 17 40 2E */	slwi r23, r8, 8
/* 8033D9A0 0033A580  89 84 00 0A */	lbz r12, 0xa(r4)
/* 8033D9A4 0033A584  53 3A 06 3E */	rlwimi r26, r25, 0, 0x18, 0x1f
/* 8033D9A8 0033A588  88 64 00 16 */	lbz r3, 0x16(r4)
/* 8033D9AC 0033A58C  55 59 60 26 */	slwi r25, r10, 0xc
/* 8033D9B0 0033A590  8B C4 00 05 */	lbz r30, 5(r4)
/* 8033D9B4 0033A594  50 17 06 3E */	rlwimi r23, r0, 0, 0x18, 0x1f
/* 8033D9B8 0033A598  88 04 00 17 */	lbz r0, 0x17(r4)
/* 8033D9BC 0033A59C  57 FB 60 26 */	slwi r27, r31, 0xc
/* 8033D9C0 0033A5A0  89 64 00 0B */	lbz r11, 0xb(r4)
/* 8033D9C4 0033A5A4  89 04 00 11 */	lbz r8, 0x11(r4)
/* 8033D9C8 0033A5A8  57 A4 80 1E */	slwi r4, r29, 0x10
/* 8033D9CC 0033A5AC  54 E7 60 26 */	slwi r7, r7, 0xc
/* 8033D9D0 0033A5B0  55 8A 80 1E */	slwi r10, r12, 0x10
/* 8033D9D4 0033A5B4  53 5B 05 3E */	rlwimi r27, r26, 0, 0x14, 0x1f
/* 8033D9D8 0033A5B8  54 6C 80 1E */	slwi r12, r3, 0x10
/* 8033D9DC 0033A5BC  52 E7 05 3E */	rlwimi r7, r23, 0, 0x14, 0x1f
/* 8033D9E0 0033A5C0  53 84 04 3E */	rlwimi r4, r28, 0, 0x10, 0x1f
/* 8033D9E4 0033A5C4  57 C3 A0 16 */	slwi r3, r30, 0x14
/* 8033D9E8 0033A5C8  53 19 05 3E */	rlwimi r25, r24, 0, 0x14, 0x1f
/* 8033D9EC 0033A5CC  55 29 80 1E */	slwi r9, r9, 0x10
/* 8033D9F0 0033A5D0  53 6A 04 3E */	rlwimi r10, r27, 0, 0x10, 0x1f
/* 8033D9F4 0033A5D4  50 83 03 3E */	rlwimi r3, r4, 0, 0xc, 0x1f
/* 8033D9F8 0033A5D8  50 EC 04 3E */	rlwimi r12, r7, 0, 0x10, 0x1f
/* 8033D9FC 0033A5DC  54 67 02 3E */	clrlwi r7, r3, 8
/* 8033DA00 0033A5E0  55 63 A0 16 */	slwi r3, r11, 0x14
/* 8033DA04 0033A5E4  51 43 03 3E */	rlwimi r3, r10, 0, 0xc, 0x1f
/* 8033DA08 0033A5E8  54 64 02 3E */	clrlwi r4, r3, 8
/* 8033DA0C 0033A5EC  55 03 A0 16 */	slwi r3, r8, 0x14
/* 8033DA10 0033A5F0  53 29 04 3E */	rlwimi r9, r25, 0, 0x10, 0x1f
/* 8033DA14 0033A5F4  51 23 03 3E */	rlwimi r3, r9, 0, 0xc, 0x1f
/* 8033DA18 0033A5F8  54 00 A0 16 */	slwi r0, r0, 0x14
/* 8033DA1C 0033A5FC  51 80 03 3E */	rlwimi r0, r12, 0, 0xc, 0x1f
/* 8033DA20 0033A600  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033DA24 0033A604  54 00 02 3E */	clrlwi r0, r0, 8
/* 8033DA28 0033A608  64 E8 01 00 */	oris r8, r7, 0x100
/* 8033DA2C 0033A60C  64 87 02 00 */	oris r7, r4, 0x200
/* 8033DA30 0033A610  64 69 03 00 */	oris r9, r3, 0x300
/* 8033DA34 0033A614  64 0A 04 00 */	oris r10, r0, 0x400
/* 8033DA38 0033A618  48 00 00 24 */	b lbl_8033DA5C
lbl_8033DA3C:
/* 8033DA3C 0033A61C  3D 00 01 66 */	lis r8, 0x01666666@ha
/* 8033DA40 0033A620  3C E0 02 66 */	lis r7, 0x02666666@ha
/* 8033DA44 0033A624  3C 80 03 66 */	lis r4, 0x03666666@ha
/* 8033DA48 0033A628  3C 60 04 66 */	lis r3, 0x04666666@ha
/* 8033DA4C 0033A62C  39 08 66 66 */	addi r8, r8, 0x01666666@l
/* 8033DA50 0033A630  38 E7 66 66 */	addi r7, r7, 0x02666666@l
/* 8033DA54 0033A634  39 24 66 66 */	addi r9, r4, 0x03666666@l
/* 8033DA58 0033A638  39 43 66 66 */	addi r10, r3, 0x04666666@l
lbl_8033DA5C:
/* 8033DA5C 0033A63C  38 80 00 61 */	li r4, 0x61
/* 8033DA60 0033A640  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033DA64 0033A644  98 83 80 00 */	stb r4, 0xCC008000@l(r3)
/* 8033DA68 0033A648  54 A0 06 3F */	clrlwi. r0, r5, 0x18
/* 8033DA6C 0033A64C  91 03 80 00 */	stw r8, -0x8000(r3)
/* 8033DA70 0033A650  98 83 80 00 */	stb r4, -0x8000(r3)
/* 8033DA74 0033A654  90 E3 80 00 */	stw r7, -0x8000(r3)
/* 8033DA78 0033A658  98 83 80 00 */	stb r4, -0x8000(r3)
/* 8033DA7C 0033A65C  91 23 80 00 */	stw r9, -0x8000(r3)
/* 8033DA80 0033A660  98 83 80 00 */	stb r4, -0x8000(r3)
/* 8033DA84 0033A664  91 43 80 00 */	stw r10, -0x8000(r3)
/* 8033DA88 0033A668  41 82 00 68 */	beq lbl_8033DAF0
/* 8033DA8C 0033A66C  88 06 00 00 */	lbz r0, 0(r6)
/* 8033DA90 0033A670  88 66 00 01 */	lbz r3, 1(r6)
/* 8033DA94 0033A674  64 05 53 00 */	oris r5, r0, 0x5300
/* 8033DA98 0033A678  88 06 00 04 */	lbz r0, 4(r6)
/* 8033DA9C 0033A67C  88 86 00 02 */	lbz r4, 2(r6)
/* 8033DAA0 0033A680  54 A7 06 A6 */	rlwinm r7, r5, 0, 0x1a, 0x13
/* 8033DAA4 0033A684  54 65 30 32 */	slwi r5, r3, 6
/* 8033DAA8 0033A688  88 66 00 05 */	lbz r3, 5(r6)
/* 8033DAAC 0033A68C  7C E7 2B 78 */	or r7, r7, r5
/* 8033DAB0 0033A690  64 08 54 00 */	oris r8, r0, 0x5400
/* 8033DAB4 0033A694  88 A6 00 03 */	lbz r5, 3(r6)
/* 8033DAB8 0033A698  88 06 00 06 */	lbz r0, 6(r6)
/* 8033DABC 0033A69C  54 E6 05 1A */	rlwinm r6, r7, 0, 0x14, 0xd
/* 8033DAC0 0033A6A0  54 84 60 26 */	slwi r4, r4, 0xc
/* 8033DAC4 0033A6A4  7C C6 23 78 */	or r6, r6, r4
/* 8033DAC8 0033A6A8  55 04 06 A6 */	rlwinm r4, r8, 0, 0x1a, 0x13
/* 8033DACC 0033A6AC  54 63 30 32 */	slwi r3, r3, 6
/* 8033DAD0 0033A6B0  7C 83 1B 78 */	or r3, r4, r3
/* 8033DAD4 0033A6B4  54 C6 03 8E */	rlwinm r6, r6, 0, 0xe, 7
/* 8033DAD8 0033A6B8  54 A4 90 1A */	slwi r4, r5, 0x12
/* 8033DADC 0033A6BC  54 63 05 1A */	rlwinm r3, r3, 0, 0x14, 0xd
/* 8033DAE0 0033A6C0  54 00 60 26 */	slwi r0, r0, 0xc
/* 8033DAE4 0033A6C4  7C C6 23 78 */	or r6, r6, r4
/* 8033DAE8 0033A6C8  7C 67 03 78 */	or r7, r3, r0
/* 8033DAEC 0033A6CC  48 00 00 14 */	b lbl_8033DB00
lbl_8033DAF0:
/* 8033DAF0 0033A6D0  3C 80 53 59 */	lis r4, 0x53595000@ha
/* 8033DAF4 0033A6D4  3C 60 54 00 */	lis r3, 0x54000015@ha
/* 8033DAF8 0033A6D8  38 C4 50 00 */	addi r6, r4, 0x53595000@l
/* 8033DAFC 0033A6DC  38 E3 00 15 */	addi r7, r3, 0x54000015@l
lbl_8033DB00:
/* 8033DB00 0033A6E0  38 A0 00 61 */	li r5, 0x61
/* 8033DB04 0033A6E4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DB08 0033A6E8  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033DB0C 0033A6EC  98 A4 80 00 */	stb r5, 0xCC008000@l(r4)
/* 8033DB10 0033A6F0  38 00 00 00 */	li r0, 0
/* 8033DB14 0033A6F4  90 C4 80 00 */	stw r6, -0x8000(r4)
/* 8033DB18 0033A6F8  98 A4 80 00 */	stb r5, -0x8000(r4)
/* 8033DB1C 0033A6FC  90 E4 80 00 */	stw r7, -0x8000(r4)
/* 8033DB20 0033A700  B0 03 00 02 */	sth r0, 2(r3)
/* 8033DB24 0033A704  BA E1 00 2C */	lmw r23, 0x2c(r1)
/* 8033DB28 0033A708  38 21 00 50 */	addi r1, r1, 0x50
/* 8033DB2C 0033A70C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

void GXSetDispCopyGamma(s32 arg0)
{
    INSERT_FIELD(__GXContexts.main->x1D0[7], arg0, 2, 7);
}

#ifdef MWERKS_GEKKO

#pragma push
asm void GXCopyDisp(u32, s8)
{ // clang-format off
    nofralloc
/* 8033DB4C 0033A72C  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 8033DB50 0033A730  41 82 00 3C */	beq lbl_8033DB8C
/* 8033DB54 0033A734  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033DB58 0033A738  38 00 00 61 */	li r0, 0x61
/* 8033DB5C 0033A73C  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033DB60 0033A740  80 C7 01 D8 */	lwz r6, 0x1d8(r7)
/* 8033DB64 0033A744  54 C6 00 3C */	rlwinm r6, r6, 0, 0, 0x1e
/* 8033DB68 0033A748  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033DB6C 0033A74C  60 C6 00 01 */	ori r6, r6, 1
/* 8033DB70 0033A750  54 C6 07 F6 */	rlwinm r6, r6, 0, 0x1f, 0x1b
/* 8033DB74 0033A754  60 C6 00 0E */	ori r6, r6, 0xe
/* 8033DB78 0033A758  90 C5 80 00 */	stw r6, -0x8000(r5)
/* 8033DB7C 0033A75C  80 C7 01 D0 */	lwz r6, 0x1d0(r7)
/* 8033DB80 0033A760  98 05 80 00 */	stb r0, -0x8000(r5)
/* 8033DB84 0033A764  54 C0 00 3A */	rlwinm r0, r6, 0, 0, 0x1d
/* 8033DB88 0033A768  90 05 80 00 */	stw r0, -0x8000(r5)
lbl_8033DB8C:
/* 8033DB8C 0033A76C  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 8033DB90 0033A770  38 00 00 00 */	li r0, 0
/* 8033DB94 0033A774  40 82 00 18 */	bne lbl_8033DBAC
/* 8033DB98 0033A778  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033DB9C 0033A77C  80 A5 01 DC */	lwz r5, 0x1dc(r5)
/* 8033DBA0 0033A780  54 A5 07 7E */	clrlwi r5, r5, 0x1d
/* 8033DBA4 0033A784  28 05 00 03 */	cmplwi r5, 3
/* 8033DBA8 0033A788  40 82 00 30 */	bne lbl_8033DBD8
lbl_8033DBAC:
/* 8033DBAC 0033A78C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033DBB0 0033A790  80 E5 01 DC */	lwz r7, 0x1dc(r5)
/* 8033DBB4 0033A794  54 E5 D7 FE */	rlwinm r5, r7, 0x1a, 0x1f, 0x1f
/* 8033DBB8 0033A798  28 05 00 01 */	cmplwi r5, 1
/* 8033DBBC 0033A79C  40 82 00 1C */	bne lbl_8033DBD8
/* 8033DBC0 0033A7A0  38 00 00 61 */	li r0, 0x61
/* 8033DBC4 0033A7A4  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033DBC8 0033A7A8  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 8033DBCC 0033A7AC  54 E5 06 B0 */	rlwinm r5, r7, 0, 0x1a, 0x18
/* 8033DBD0 0033A7B0  38 00 00 01 */	li r0, 1
/* 8033DBD4 0033A7B4  90 A6 80 00 */	stw r5, -0x8000(r6)
lbl_8033DBD8:
/* 8033DBD8 0033A7B8  39 20 00 61 */	li r9, 0x61
/* 8033DBDC 0033A7BC  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033DBE0 0033A7C0  3D 00 CC 01 */	lis r8, 0xCC008000@ha
/* 8033DBE4 0033A7C4  99 28 80 00 */	stb r9, 0xCC008000@l(r8)
/* 8033DBE8 0033A7C8  54 63 DA 3E */	rlwinm r3, r3, 0x1b, 8, 0x1f
/* 8033DBEC 0033A7CC  64 6A 4B 00 */	oris r10, r3, 0x4b00
/* 8033DBF0 0033A7D0  80 C7 01 E0 */	lwz r6, 0x1e0(r7)
/* 8033DBF4 0033A7D4  54 85 06 3F */	clrlwi. r5, r4, 0x18
/* 8033DBF8 0033A7D8  54 83 5B 68 */	rlwinm r3, r4, 0xb, 0xd, 0x14
/* 8033DBFC 0033A7DC  90 C8 80 00 */	stw r6, -0x8000(r8)
/* 8033DC00 0033A7E0  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC04 0033A7E4  80 87 01 E4 */	lwz r4, 0x1e4(r7)
/* 8033DC08 0033A7E8  90 88 80 00 */	stw r4, -0x8000(r8)
/* 8033DC0C 0033A7EC  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC10 0033A7F0  80 87 01 E8 */	lwz r4, 0x1e8(r7)
/* 8033DC14 0033A7F4  90 88 80 00 */	stw r4, -0x8000(r8)
/* 8033DC18 0033A7F8  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC1C 0033A7FC  91 48 80 00 */	stw r10, -0x8000(r8)
/* 8033DC20 0033A800  80 87 01 EC */	lwz r4, 0x1ec(r7)
/* 8033DC24 0033A804  54 84 05 66 */	rlwinm r4, r4, 0, 0x15, 0x13
/* 8033DC28 0033A808  7C 83 1B 78 */	or r3, r4, r3
/* 8033DC2C 0033A80C  90 67 01 EC */	stw r3, 0x1ec(r7)
/* 8033DC30 0033A810  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DC34 0033A814  38 83 01 EC */	addi r4, r3, 0x1ec
/* 8033DC38 0033A818  80 63 01 EC */	lwz r3, 0x1ec(r3)
/* 8033DC3C 0033A81C  54 63 04 A0 */	rlwinm r3, r3, 0, 0x12, 0x10
/* 8033DC40 0033A820  60 63 40 00 */	ori r3, r3, 0x4000
/* 8033DC44 0033A824  90 64 00 00 */	stw r3, 0(r4)
/* 8033DC48 0033A828  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DC4C 0033A82C  38 83 01 EC */	addi r4, r3, 0x1ec
/* 8033DC50 0033A830  80 63 01 EC */	lwz r3, 0x1ec(r3)
/* 8033DC54 0033A834  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033DC58 0033A838  64 63 52 00 */	oris r3, r3, 0x5200
/* 8033DC5C 0033A83C  90 64 00 00 */	stw r3, 0(r4)
/* 8033DC60 0033A840  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC64 0033A844  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033DC68 0033A848  80 64 01 EC */	lwz r3, 0x1ec(r4)
/* 8033DC6C 0033A84C  90 68 80 00 */	stw r3, -0x8000(r8)
/* 8033DC70 0033A850  41 82 00 1C */	beq lbl_8033DC8C
/* 8033DC74 0033A854  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC78 0033A858  80 64 01 D8 */	lwz r3, 0x1d8(r4)
/* 8033DC7C 0033A85C  90 68 80 00 */	stw r3, -0x8000(r8)
/* 8033DC80 0033A860  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DC84 0033A864  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 8033DC88 0033A868  90 68 80 00 */	stw r3, -0x8000(r8)
lbl_8033DC8C:
/* 8033DC8C 0033A86C  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 8033DC90 0033A870  41 82 00 1C */	beq lbl_8033DCAC
/* 8033DC94 0033A874  38 00 00 61 */	li r0, 0x61
/* 8033DC98 0033A878  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DC9C 0033A87C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033DCA0 0033A880  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8033DCA4 0033A884  80 03 01 DC */	lwz r0, 0x1dc(r3)
/* 8033DCA8 0033A888  90 04 80 00 */	stw r0, -0x8000(r4)
lbl_8033DCAC:
/* 8033DCAC 0033A88C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DCB0 0033A890  38 00 00 00 */	li r0, 0
/* 8033DCB4 0033A894  B0 03 00 02 */	sth r0, 2(r3)
/* 8033DCB8 0033A898  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void GXCopyTex(u32, GXBool)
{ // clang-format off
    nofralloc
/* 8033DCBC 0033A89C  54 80 06 3F */	clrlwi. r0, r4, 0x18
/* 8033DCC0 0033A8A0  41 82 00 3C */	beq lbl_8033DCFC
/* 8033DCC4 0033A8A4  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033DCC8 0033A8A8  38 00 00 61 */	li r0, 0x61
/* 8033DCCC 0033A8AC  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033DCD0 0033A8B0  80 C7 01 D8 */	lwz r6, 0x1d8(r7)
/* 8033DCD4 0033A8B4  54 C6 00 3C */	rlwinm r6, r6, 0, 0, 0x1e
/* 8033DCD8 0033A8B8  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033DCDC 0033A8BC  60 C6 00 01 */	ori r6, r6, 1
/* 8033DCE0 0033A8C0  54 C6 07 F6 */	rlwinm r6, r6, 0, 0x1f, 0x1b
/* 8033DCE4 0033A8C4  60 C6 00 0E */	ori r6, r6, 0xe
/* 8033DCE8 0033A8C8  90 C5 80 00 */	stw r6, -0x8000(r5)
/* 8033DCEC 0033A8CC  80 C7 01 D0 */	lwz r6, 0x1d0(r7)
/* 8033DCF0 0033A8D0  98 05 80 00 */	stb r0, -0x8000(r5)
/* 8033DCF4 0033A8D4  54 C0 00 3A */	rlwinm r0, r6, 0, 0, 0x1d
/* 8033DCF8 0033A8D8  90 05 80 00 */	stw r0, -0x8000(r5)
lbl_8033DCFC:
/* 8033DCFC 0033A8DC  80 CD A5 08 */	lwz r6, __GXContexts(r13)
/* 8033DD00 0033A8E0  38 00 00 00 */	li r0, 0
/* 8033DD04 0033A8E4  88 A6 02 00 */	lbz r5, 0x200(r6)
/* 8033DD08 0033A8E8  80 E6 01 DC */	lwz r7, 0x1dc(r6)
/* 8033DD0C 0033A8EC  28 05 00 00 */	cmplwi r5, 0
/* 8033DD10 0033A8F0  41 82 00 1C */	beq lbl_8033DD2C
/* 8033DD14 0033A8F4  54 E5 07 7E */	clrlwi r5, r7, 0x1d
/* 8033DD18 0033A8F8  28 05 00 03 */	cmplwi r5, 3
/* 8033DD1C 0033A8FC  41 82 00 10 */	beq lbl_8033DD2C
/* 8033DD20 0033A900  54 E0 00 38 */	rlwinm r0, r7, 0, 0, 0x1c
/* 8033DD24 0033A904  60 07 00 03 */	ori r7, r0, 3
/* 8033DD28 0033A908  38 00 00 01 */	li r0, 1
lbl_8033DD2C:
/* 8033DD2C 0033A90C  54 85 06 3F */	clrlwi. r5, r4, 0x18
/* 8033DD30 0033A910  40 82 00 10 */	bne lbl_8033DD40
/* 8033DD34 0033A914  54 E5 07 7E */	clrlwi r5, r7, 0x1d
/* 8033DD38 0033A918  28 05 00 03 */	cmplwi r5, 3
/* 8033DD3C 0033A91C  40 82 00 18 */	bne lbl_8033DD54
lbl_8033DD40:
/* 8033DD40 0033A920  54 E5 D7 FE */	rlwinm r5, r7, 0x1a, 0x1f, 0x1f
/* 8033DD44 0033A924  28 05 00 01 */	cmplwi r5, 1
/* 8033DD48 0033A928  40 82 00 0C */	bne lbl_8033DD54
/* 8033DD4C 0033A92C  38 00 00 01 */	li r0, 1
/* 8033DD50 0033A930  54 E7 06 B0 */	rlwinm r7, r7, 0, 0x1a, 0x18
lbl_8033DD54:
/* 8033DD54 0033A934  54 05 06 3F */	clrlwi. r5, r0, 0x18
/* 8033DD58 0033A938  41 82 00 14 */	beq lbl_8033DD6C
/* 8033DD5C 0033A93C  38 C0 00 61 */	li r6, 0x61
/* 8033DD60 0033A940  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033DD64 0033A944  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 8033DD68 0033A948  90 E5 80 00 */	stw r7, -0x8000(r5)
lbl_8033DD6C:
/* 8033DD6C 0033A94C  39 20 00 61 */	li r9, 0x61
/* 8033DD70 0033A950  80 ED A5 08 */	lwz r7, __GXContexts(r13)
/* 8033DD74 0033A954  3D 00 CC 01 */	lis r8, 0xCC008000@ha
/* 8033DD78 0033A958  99 28 80 00 */	stb r9, 0xCC008000@l(r8)
/* 8033DD7C 0033A95C  54 63 DA 3E */	rlwinm r3, r3, 0x1b, 8, 0x1f
/* 8033DD80 0033A960  64 6A 4B 00 */	oris r10, r3, 0x4b00
/* 8033DD84 0033A964  80 C7 01 F0 */	lwz r6, 0x1f0(r7)
/* 8033DD88 0033A968  54 85 06 3F */	clrlwi. r5, r4, 0x18
/* 8033DD8C 0033A96C  54 83 5B 68 */	rlwinm r3, r4, 0xb, 0xd, 0x14
/* 8033DD90 0033A970  90 C8 80 00 */	stw r6, -0x8000(r8)
/* 8033DD94 0033A974  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DD98 0033A978  80 87 01 F4 */	lwz r4, 0x1f4(r7)
/* 8033DD9C 0033A97C  90 88 80 00 */	stw r4, -0x8000(r8)
/* 8033DDA0 0033A980  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DDA4 0033A984  80 87 01 F8 */	lwz r4, 0x1f8(r7)
/* 8033DDA8 0033A988  90 88 80 00 */	stw r4, -0x8000(r8)
/* 8033DDAC 0033A98C  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DDB0 0033A990  91 48 80 00 */	stw r10, -0x8000(r8)
/* 8033DDB4 0033A994  80 87 01 FC */	lwz r4, 0x1fc(r7)
/* 8033DDB8 0033A998  54 84 05 66 */	rlwinm r4, r4, 0, 0x15, 0x13
/* 8033DDBC 0033A99C  7C 83 1B 78 */	or r3, r4, r3
/* 8033DDC0 0033A9A0  90 67 01 FC */	stw r3, 0x1fc(r7)
/* 8033DDC4 0033A9A4  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DDC8 0033A9A8  38 83 01 FC */	addi r4, r3, 0x1fc
/* 8033DDCC 0033A9AC  80 63 01 FC */	lwz r3, 0x1fc(r3)
/* 8033DDD0 0033A9B0  54 63 04 A0 */	rlwinm r3, r3, 0, 0x12, 0x10
/* 8033DDD4 0033A9B4  90 64 00 00 */	stw r3, 0(r4)
/* 8033DDD8 0033A9B8  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DDDC 0033A9BC  38 83 01 FC */	addi r4, r3, 0x1fc
/* 8033DDE0 0033A9C0  80 63 01 FC */	lwz r3, 0x1fc(r3)
/* 8033DDE4 0033A9C4  54 63 02 3E */	clrlwi r3, r3, 8
/* 8033DDE8 0033A9C8  64 63 52 00 */	oris r3, r3, 0x5200
/* 8033DDEC 0033A9CC  90 64 00 00 */	stw r3, 0(r4)
/* 8033DDF0 0033A9D0  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DDF4 0033A9D4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033DDF8 0033A9D8  80 64 01 FC */	lwz r3, 0x1fc(r4)
/* 8033DDFC 0033A9DC  90 68 80 00 */	stw r3, -0x8000(r8)
/* 8033DE00 0033A9E0  41 82 00 1C */	beq lbl_8033DE1C
/* 8033DE04 0033A9E4  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DE08 0033A9E8  80 64 01 D8 */	lwz r3, 0x1d8(r4)
/* 8033DE0C 0033A9EC  90 68 80 00 */	stw r3, -0x8000(r8)
/* 8033DE10 0033A9F0  99 28 80 00 */	stb r9, -0x8000(r8)
/* 8033DE14 0033A9F4  80 64 01 D0 */	lwz r3, 0x1d0(r4)
/* 8033DE18 0033A9F8  90 68 80 00 */	stw r3, -0x8000(r8)
lbl_8033DE1C:
/* 8033DE1C 0033A9FC  54 00 06 3F */	clrlwi. r0, r0, 0x18
/* 8033DE20 0033AA00  41 82 00 1C */	beq lbl_8033DE3C
/* 8033DE24 0033AA04  38 00 00 61 */	li r0, 0x61
/* 8033DE28 0033AA08  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DE2C 0033AA0C  3C 80 CC 01 */	lis r4, 0xCC008000@ha
/* 8033DE30 0033AA10  98 04 80 00 */	stb r0, 0xCC008000@l(r4)
/* 8033DE34 0033AA14  80 03 01 DC */	lwz r0, 0x1dc(r3)
/* 8033DE38 0033AA18  90 04 80 00 */	stw r0, -0x8000(r4)
lbl_8033DE3C:
/* 8033DE3C 0033AA1C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033DE40 0033AA20  38 00 00 00 */	li r0, 0
/* 8033DE44 0033AA24  B0 03 00 02 */	sth r0, 2(r3)
/* 8033DE48 0033AA28  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#endif

void GXClearBoundingBox(void)
{
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x550003FF;
    WGPIPE.u8 = GX_LOAD_BP_REG;
    WGPIPE.u32 = 0x560003FF;
    set_x2(GX_FALSE);
}
