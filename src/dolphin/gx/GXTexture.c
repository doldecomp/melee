#include <Runtime/__mem.h>
#include <common_structs.h>
#include <dolphin/gx/__GXBump.h>
#include <dolphin/gx/__GXInit.h>

static Vec2 const lbl_804DE268 = { 16.0F, 0.0F };
static f64 const lbl_804DE270 = 4503599627370496.0L;
static f32 const lbl_804DE278 = -4.0F;
static f32 const lbl_804DE27C = 4.0F;
static f32 const lbl_804DE280 = 3.990000009536743F;
static f32 const lbl_804DE284 = 32.0F;
static f32 const lbl_804DE288 = 0.0F;
static f32 const lbl_804DE28C = 10.0F;

typedef struct {
    u32 x0;
    u32 x4;
} GXTexture_Unk0;

static GXTexture_Unk0 GXTexMode0Ids = { 0x80818283, 0xA0A1A2A3 };
static GXTexture_Unk0 GXTexMode1Ids = { 0x84858687, 0xA4A5A6A7 };
static GXTexture_Unk0 GXTexImage0Ids = { 0x88898A8B, 0xA8A9AAAB };
static GXTexture_Unk0 GXTexImage1Ids = { 0x8C8D8E8F, 0xACADAEAF };
static GXTexture_Unk0 GXTexImage2Ids = { 0x90919293, 0xB0B1B2B3 };
static GXTexture_Unk0 GXTexImage3Ids = { 0x94959697, 0xB4B5B6B7 };
static GXTexture_Unk0 GXTexTlutIds = { 0x98999A9B, 0xB8B9BABB };
static GXTexture_Unk0 GX2HWFiltConv = { 0x00040105, 0x02060000 };

void lbl_8033E7B4(void);
void lbl_8033E7C0(void);
void lbl_8033E7C0(void);
void lbl_8033E7CC(void);
void lbl_8033E7CC(void);
void lbl_8033E7CC(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7B4(void);
void lbl_8033E7C0(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7B4(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7C0(void);
void lbl_8033E7D8(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7B4(void);
void lbl_8033E7D8(void);
void lbl_8033E7C0(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7C0(void);
void lbl_8033E7C0(void);
void lbl_8033E7C0(void);
void lbl_8033E7C0(void);
void lbl_8033E7CC(void);
void lbl_8033E7CC(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7B4(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7D8(void);
void lbl_8033E7C0(void);
void lbl_8033E7C0(void);
void lbl_8033E7D8(void);
void lbl_8033E7CC(void);
void lbl_8033E908(void);
void lbl_8033E914(void);
void lbl_8033E914(void);
void lbl_8033E920(void);
void lbl_8033E920(void);
void lbl_8033E920(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E908(void);
void lbl_8033E914(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E908(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E914(void);
void lbl_8033E92C(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E908(void);
void lbl_8033E92C(void);
void lbl_8033E914(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E914(void);
void lbl_8033E914(void);
void lbl_8033E914(void);
void lbl_8033E914(void);
void lbl_8033E920(void);
void lbl_8033E920(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E908(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E92C(void);
void lbl_8033E914(void);
void lbl_8033E914(void);
void lbl_8033E92C(void);
void lbl_8033E920(void);
void lbl_8033EB58(void);
void lbl_8033EB6C(void);
void lbl_8033EB6C(void);
void lbl_8033EB80(void);
void lbl_8033EB80(void);
void lbl_8033EB80(void);
void lbl_8033EB94(void);
void lbl_8033EBBC(void);
void lbl_8033EB58(void);
void lbl_8033EB6C(void);
void lbl_8033EB80(void);
void lbl_8033EBBC(void);
void lbl_8033EBBC(void);
void lbl_8033EBBC(void);
void lbl_8033EBA8(void);

static jtbl_t jtbl_804012B8 = {
    &lbl_8033E7B4, &lbl_8033E7C0, &lbl_8033E7C0, &lbl_8033E7CC,
    &lbl_8033E7CC, &lbl_8033E7CC, &lbl_8033E7CC, &lbl_8033E7D8,
    &lbl_8033E7B4, &lbl_8033E7C0, &lbl_8033E7CC, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7B4, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7C0, &lbl_8033E7D8, &lbl_8033E7CC,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7CC, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8,
    &lbl_8033E7B4, &lbl_8033E7D8, &lbl_8033E7C0, &lbl_8033E7CC,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7C0,
    &lbl_8033E7C0, &lbl_8033E7C0, &lbl_8033E7C0, &lbl_8033E7CC,
    &lbl_8033E7CC, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8,
    &lbl_8033E7B4, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8, &lbl_8033E7D8,
    &lbl_8033E7D8, &lbl_8033E7C0, &lbl_8033E7C0, &lbl_8033E7D8,
    &lbl_8033E7CC
};

static jtbl_t jtbl_804013AC = {
    &lbl_8033E908, &lbl_8033E914, &lbl_8033E914, &lbl_8033E920,
    &lbl_8033E920, &lbl_8033E920, &lbl_8033E920, &lbl_8033E92C,
    &lbl_8033E908, &lbl_8033E914, &lbl_8033E920, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E908, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E914, &lbl_8033E92C, &lbl_8033E920,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E920, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C,
    &lbl_8033E908, &lbl_8033E92C, &lbl_8033E914, &lbl_8033E920,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E914,
    &lbl_8033E914, &lbl_8033E914, &lbl_8033E914, &lbl_8033E920,
    &lbl_8033E920, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C,
    &lbl_8033E908, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C, &lbl_8033E92C,
    &lbl_8033E92C, &lbl_8033E914, &lbl_8033E914, &lbl_8033E92C,
    &lbl_8033E920
};

static jtbl_t jtbl_804014A0 = {
    &lbl_8033EB58, &lbl_8033EB6C, &lbl_8033EB6C, &lbl_8033EB80,
    &lbl_8033EB80, &lbl_8033EB80, &lbl_8033EB94, &lbl_8033EBBC,
    &lbl_8033EB58, &lbl_8033EB6C, &lbl_8033EB80, &lbl_8033EBBC,
    &lbl_8033EBBC, &lbl_8033EBBC, &lbl_8033EBA8, NULL
};

// https://decomp.me/scratch/FgNqV // 2963 (65.94%)
#pragma push
asm unk_t GXGetTexBufferSize()
{ // clang-format off
    nofralloc
/* 8033E78C 0033B36C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033E790 0033B370  28 05 00 3C */	cmplwi r5, 0x3c
/* 8033E794 0033B374  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8033E798 0033B378  41 81 00 40 */	bgt lbl_8033E7D8
/* 8033E79C 0033B37C  3D 00 80 40 */	lis r8, jtbl_804012B8@ha
/* 8033E7A0 0033B380  39 08 12 B8 */	addi r8, r8, jtbl_804012B8@l
/* 8033E7A4 0033B384  54 A0 10 3A */	slwi r0, r5, 2
/* 8033E7A8 0033B388  7C 08 00 2E */	lwzx r0, r8, r0
/* 8033E7AC 0033B38C  7C 09 03 A6 */	mtctr r0
/* 8033E7B0 0033B390  4E 80 04 20 */	bctr 
entry lbl_8033E7B4
/* 8033E7B4 0033B394  38 00 00 03 */	li r0, 3
/* 8033E7B8 0033B398  39 00 00 03 */	li r8, 3
/* 8033E7BC 0033B39C  48 00 00 24 */	b lbl_8033E7E0
entry lbl_8033E7C0
/* 8033E7C0 0033B3A0  38 00 00 03 */	li r0, 3
/* 8033E7C4 0033B3A4  39 00 00 02 */	li r8, 2
/* 8033E7C8 0033B3A8  48 00 00 18 */	b lbl_8033E7E0
entry lbl_8033E7CC
/* 8033E7CC 0033B3AC  38 00 00 02 */	li r0, 2
/* 8033E7D0 0033B3B0  39 00 00 02 */	li r8, 2
/* 8033E7D4 0033B3B4  48 00 00 0C */	b lbl_8033E7E0
entry lbl_8033E7D8
/* 8033E7D8 0033B3B8  39 00 00 00 */	li r8, 0
/* 8033E7DC 0033B3BC  38 00 00 00 */	li r0, 0
lbl_8033E7E0:
/* 8033E7E0 0033B3C0  28 05 00 06 */	cmplwi r5, 6
/* 8033E7E4 0033B3C4  41 82 00 0C */	beq lbl_8033E7F0
/* 8033E7E8 0033B3C8  28 05 00 16 */	cmplwi r5, 0x16
/* 8033E7EC 0033B3CC  40 82 00 0C */	bne lbl_8033E7F8
lbl_8033E7F0:
/* 8033E7F0 0033B3D0  38 A0 00 40 */	li r5, 0x40
/* 8033E7F4 0033B3D4  48 00 00 08 */	b lbl_8033E7FC
lbl_8033E7F8:
/* 8033E7F8 0033B3D8  38 A0 00 20 */	li r5, 0x20
lbl_8033E7FC:
/* 8033E7FC 0033B3DC  54 C6 06 3E */	clrlwi r6, r6, 0x18
/* 8033E800 0033B3E0  28 06 00 01 */	cmplwi r6, 1
/* 8033E804 0033B3E4  40 82 00 A0 */	bne lbl_8033E8A4
/* 8033E808 0033B3E8  54 E9 06 3E */	clrlwi r9, r7, 0x18
/* 8033E80C 0033B3EC  38 C0 00 01 */	li r6, 1
/* 8033E810 0033B3F0  7D 29 03 A6 */	mtctr r9
/* 8033E814 0033B3F4  7C C7 40 30 */	slw r7, r6, r8
/* 8033E818 0033B3F8  7C C6 00 30 */	slw r6, r6, r0
/* 8033E81C 0033B3FC  28 09 00 00 */	cmplwi r9, 0
/* 8033E820 0033B400  39 46 FF FF */	addi r10, r6, -1
/* 8033E824 0033B404  38 E7 FF FF */	addi r7, r7, -1
/* 8033E828 0033B408  3B E0 00 00 */	li r31, 0
/* 8033E82C 0033B40C  40 81 00 AC */	ble lbl_8033E8D8
lbl_8033E830:
/* 8033E830 0033B410  54 6B 04 3E */	clrlwi r11, r3, 0x10
/* 8033E834 0033B414  7C CB 52 14 */	add r6, r11, r10
/* 8033E838 0033B418  54 8C 04 3E */	clrlwi r12, r4, 0x10
/* 8033E83C 0033B41C  7C C9 06 30 */	sraw r9, r6, r0
/* 8033E840 0033B420  7C CC 3A 14 */	add r6, r12, r7
/* 8033E844 0033B424  7C C6 46 30 */	sraw r6, r6, r8
/* 8033E848 0033B428  7C C9 31 D6 */	mullw r6, r9, r6
/* 8033E84C 0033B42C  7C C5 31 D6 */	mullw r6, r5, r6
/* 8033E850 0033B430  28 0B 00 01 */	cmplwi r11, 1
/* 8033E854 0033B434  7F FF 32 14 */	add r31, r31, r6
/* 8033E858 0033B438  40 82 00 0C */	bne lbl_8033E864
/* 8033E85C 0033B43C  28 0C 00 01 */	cmplwi r12, 1
/* 8033E860 0033B440  41 82 00 78 */	beq lbl_8033E8D8
lbl_8033E864:
/* 8033E864 0033B444  54 63 04 3E */	clrlwi r3, r3, 0x10
/* 8033E868 0033B448  28 03 00 01 */	cmplwi r3, 1
/* 8033E86C 0033B44C  40 81 00 0C */	ble lbl_8033E878
/* 8033E870 0033B450  7D 66 0E 70 */	srawi r6, r11, 1
/* 8033E874 0033B454  48 00 00 08 */	b lbl_8033E87C
lbl_8033E878:
/* 8033E878 0033B458  38 C0 00 01 */	li r6, 1
lbl_8033E87C:
/* 8033E87C 0033B45C  54 83 04 3E */	clrlwi r3, r4, 0x10
/* 8033E880 0033B460  28 03 00 01 */	cmplwi r3, 1
/* 8033E884 0033B464  54 C3 04 3E */	clrlwi r3, r6, 0x10
/* 8033E888 0033B468  40 81 00 0C */	ble lbl_8033E894
/* 8033E88C 0033B46C  7D 84 0E 70 */	srawi r4, r12, 1
/* 8033E890 0033B470  48 00 00 08 */	b lbl_8033E898
lbl_8033E894:
/* 8033E894 0033B474  38 80 00 01 */	li r4, 1
lbl_8033E898:
/* 8033E898 0033B478  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 8033E89C 0033B47C  42 00 FF 94 */	bdnz lbl_8033E830
/* 8033E8A0 0033B480  48 00 00 38 */	b lbl_8033E8D8
lbl_8033E8A4:
/* 8033E8A4 0033B484  38 C0 00 01 */	li r6, 1
/* 8033E8A8 0033B488  7C C7 00 30 */	slw r7, r6, r0
/* 8033E8AC 0033B48C  7C C6 40 30 */	slw r6, r6, r8
/* 8033E8B0 0033B490  54 69 04 3E */	clrlwi r9, r3, 0x10
/* 8033E8B4 0033B494  38 67 FF FF */	addi r3, r7, -1
/* 8033E8B8 0033B498  7C E9 1A 14 */	add r7, r9, r3
/* 8033E8BC 0033B49C  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 8033E8C0 0033B4A0  38 66 FF FF */	addi r3, r6, -1
/* 8033E8C4 0033B4A4  7C E6 06 30 */	sraw r6, r7, r0
/* 8033E8C8 0033B4A8  7C 04 1A 14 */	add r0, r4, r3
/* 8033E8CC 0033B4AC  7C 00 46 30 */	sraw r0, r0, r8
/* 8033E8D0 0033B4B0  7C 06 01 D6 */	mullw r0, r6, r0
/* 8033E8D4 0033B4B4  7F E5 01 D6 */	mullw r31, r5, r0
lbl_8033E8D8:
/* 8033E8D8 0033B4B8  7F E3 FB 78 */	mr r3, r31
/* 8033E8DC 0033B4BC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8033E8E0 0033B4C0  38 21 00 28 */	addi r1, r1, 0x28
/* 8033E8E4 0033B4C4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/efvey // 1665 (66.70%)
#pragma push
asm unk_t __GetImageTileCount()
{ // clang-format off
    nofralloc
/* 8033E8E8 0033B4C8  28 03 00 3C */	cmplwi r3, 0x3c
/* 8033E8EC 0033B4CC  41 81 00 40 */	bgt lbl_8033E92C
/* 8033E8F0 0033B4D0  3D 20 80 40 */	lis r9, jtbl_804013AC@ha
/* 8033E8F4 0033B4D4  39 29 13 AC */	addi r9, r9, jtbl_804013AC@l
/* 8033E8F8 0033B4D8  54 60 10 3A */	slwi r0, r3, 2
/* 8033E8FC 0033B4DC  7C 09 00 2E */	lwzx r0, r9, r0
/* 8033E900 0033B4E0  7C 09 03 A6 */	mtctr r0
/* 8033E904 0033B4E4  4E 80 04 20 */	bctr 
entry lbl_8033E908
/* 8033E908 0033B4E8  39 60 00 03 */	li r11, 3
/* 8033E90C 0033B4EC  39 80 00 03 */	li r12, 3
/* 8033E910 0033B4F0  48 00 00 24 */	b lbl_8033E934
entry lbl_8033E914
/* 8033E914 0033B4F4  39 60 00 03 */	li r11, 3
/* 8033E918 0033B4F8  39 80 00 02 */	li r12, 2
/* 8033E91C 0033B4FC  48 00 00 18 */	b lbl_8033E934
entry lbl_8033E920
/* 8033E920 0033B500  39 60 00 02 */	li r11, 2
/* 8033E924 0033B504  39 80 00 02 */	li r12, 2
/* 8033E928 0033B508  48 00 00 0C */	b lbl_8033E934
entry lbl_8033E92C
/* 8033E92C 0033B50C  39 80 00 00 */	li r12, 0
/* 8033E930 0033B510  39 60 00 00 */	li r11, 0
lbl_8033E934:
/* 8033E934 0033B514  54 80 04 3F */	clrlwi. r0, r4, 0x10
/* 8033E938 0033B518  40 82 00 08 */	bne lbl_8033E940
/* 8033E93C 0033B51C  38 80 00 01 */	li r4, 1
lbl_8033E940:
/* 8033E940 0033B520  54 A0 04 3F */	clrlwi. r0, r5, 0x10
/* 8033E944 0033B524  40 82 00 08 */	bne lbl_8033E94C
/* 8033E948 0033B528  38 A0 00 01 */	li r5, 1
lbl_8033E94C:
/* 8033E94C 0033B52C  39 40 00 01 */	li r10, 1
/* 8033E950 0033B530  7D 49 58 30 */	slw r9, r10, r11
/* 8033E954 0033B534  54 84 04 3E */	clrlwi r4, r4, 0x10
/* 8033E958 0033B538  38 09 FF FF */	addi r0, r9, -1
/* 8033E95C 0033B53C  7C 04 02 14 */	add r0, r4, r0
/* 8033E960 0033B540  7C 00 5E 30 */	sraw r0, r0, r11
/* 8033E964 0033B544  7D 44 60 30 */	slw r4, r10, r12
/* 8033E968 0033B548  90 06 00 00 */	stw r0, 0(r6)
/* 8033E96C 0033B54C  54 A5 04 3E */	clrlwi r5, r5, 0x10
/* 8033E970 0033B550  38 04 FF FF */	addi r0, r4, -1
/* 8033E974 0033B554  7C 05 02 14 */	add r0, r5, r0
/* 8033E978 0033B558  7C 00 66 30 */	sraw r0, r0, r12
/* 8033E97C 0033B55C  2C 03 00 06 */	cmpwi r3, 6
/* 8033E980 0033B560  90 07 00 00 */	stw r0, 0(r7)
/* 8033E984 0033B564  41 82 00 10 */	beq lbl_8033E994
/* 8033E988 0033B568  2C 03 00 16 */	cmpwi r3, 0x16
/* 8033E98C 0033B56C  41 82 00 08 */	beq lbl_8033E994
/* 8033E990 0033B570  39 40 00 00 */	li r10, 0
lbl_8033E994:
/* 8033E994 0033B574  2C 0A 00 00 */	cmpwi r10, 0
/* 8033E998 0033B578  41 82 00 0C */	beq lbl_8033E9A4
/* 8033E99C 0033B57C  38 00 00 02 */	li r0, 2
/* 8033E9A0 0033B580  48 00 00 08 */	b lbl_8033E9A8
lbl_8033E9A4:
/* 8033E9A4 0033B584  38 00 00 01 */	li r0, 1
lbl_8033E9A8:
/* 8033E9A8 0033B588  90 08 00 00 */	stw r0, 0(r8)
/* 8033E9AC 0033B58C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/YiUMp
#pragma push
asm unk_t GXInitTexObj()
{ // clang-format off
    nofralloc
/* 8033E9B0 0033B590  7C 08 02 A6 */	mflr r0
/* 8033E9B4 0033B594  90 01 00 04 */	stw r0, 4(r1)
/* 8033E9B8 0033B598  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8033E9BC 0033B59C  BF 01 00 40 */	stmw r24, 0x40(r1)
/* 8033E9C0 0033B5A0  3B 64 00 00 */	addi r27, r4, 0
/* 8033E9C4 0033B5A4  3B 85 00 00 */	addi r28, r5, 0
/* 8033E9C8 0033B5A8  3B E3 00 00 */	addi r31, r3, 0
/* 8033E9CC 0033B5AC  3B A6 00 00 */	addi r29, r6, 0
/* 8033E9D0 0033B5B0  3B C7 00 00 */	addi r30, r7, 0
/* 8033E9D4 0033B5B4  3B 08 00 00 */	addi r24, r8, 0
/* 8033E9D8 0033B5B8  3B 29 00 00 */	addi r25, r9, 0
/* 8033E9DC 0033B5BC  3B 4A 00 00 */	addi r26, r10, 0
/* 8033E9E0 0033B5C0  38 80 00 00 */	li r4, 0
/* 8033E9E4 0033B5C4  38 A0 00 20 */	li r5, 0x20
/* 8033E9E8 0033B5C8  4B CC 47 19 */	bl memset
/* 8033E9EC 0033B5CC  80 9F 00 00 */	lwz r4, 0(r31)
/* 8033E9F0 0033B5D0  57 40 06 3F */	clrlwi. r0, r26, 0x18
/* 8033E9F4 0033B5D4  57 23 10 3A */	slwi r3, r25, 2
/* 8033E9F8 0033B5D8  54 84 00 3A */	rlwinm r4, r4, 0, 0, 0x1d
/* 8033E9FC 0033B5DC  7C 84 C3 78 */	or r4, r4, r24
/* 8033EA00 0033B5E0  90 9F 00 00 */	stw r4, 0(r31)
/* 8033EA04 0033B5E4  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033EA08 0033B5E8  54 00 07 B6 */	rlwinm r0, r0, 0, 0x1e, 0x1b
/* 8033EA0C 0033B5EC  7C 00 1B 78 */	or r0, r0, r3
/* 8033EA10 0033B5F0  90 1F 00 00 */	stw r0, 0(r31)
/* 8033EA14 0033B5F4  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033EA18 0033B5F8  54 00 07 34 */	rlwinm r0, r0, 0, 0x1c, 0x1a
/* 8033EA1C 0033B5FC  60 00 00 10 */	ori r0, r0, 0x10
/* 8033EA20 0033B600  90 1F 00 00 */	stw r0, 0(r31)
/* 8033EA24 0033B604  41 82 00 A4 */	beq lbl_8033EAC8
/* 8033EA28 0033B608  88 7F 00 1F */	lbz r3, 0x1f(r31)
/* 8033EA2C 0033B60C  38 1E FF F8 */	addi r0, r30, -8
/* 8033EA30 0033B610  28 00 00 02 */	cmplwi r0, 2
/* 8033EA34 0033B614  60 60 00 01 */	ori r0, r3, 1
/* 8033EA38 0033B618  98 1F 00 1F */	stb r0, 0x1f(r31)
/* 8033EA3C 0033B61C  41 81 00 18 */	bgt lbl_8033EA54
/* 8033EA40 0033B620  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033EA44 0033B624  54 00 06 EE */	rlwinm r0, r0, 0, 0x1b, 0x17
/* 8033EA48 0033B628  60 00 00 A0 */	ori r0, r0, 0xa0
/* 8033EA4C 0033B62C  90 1F 00 00 */	stw r0, 0(r31)
/* 8033EA50 0033B630  48 00 00 14 */	b lbl_8033EA64
lbl_8033EA54:
/* 8033EA54 0033B634  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033EA58 0033B638  54 00 06 EE */	rlwinm r0, r0, 0, 0x1b, 0x17
/* 8033EA5C 0033B63C  60 00 00 C0 */	ori r0, r0, 0xc0
/* 8033EA60 0033B640  90 1F 00 00 */	stw r0, 0(r31)
lbl_8033EA64:
/* 8033EA64 0033B644  57 83 04 3E */	clrlwi r3, r28, 0x10
/* 8033EA68 0033B648  57 A0 04 3E */	clrlwi r0, r29, 0x10
/* 8033EA6C 0033B64C  7C 03 00 40 */	cmplw r3, r0
/* 8033EA70 0033B650  40 81 00 10 */	ble lbl_8033EA80
/* 8033EA74 0033B654  7C 60 00 34 */	cntlzw r0, r3
/* 8033EA78 0033B658  20 00 00 1F */	subfic r0, r0, 0x1f
/* 8033EA7C 0033B65C  48 00 00 0C */	b lbl_8033EA88
lbl_8033EA80:
/* 8033EA80 0033B660  7C 00 00 34 */	cntlzw r0, r0
/* 8033EA84 0033B664  20 00 00 1F */	subfic r0, r0, 0x1f
lbl_8033EA88:
/* 8033EA88 0033B668  90 01 00 3C */	stw r0, 0x3c(r1)
/* 8033EA8C 0033B66C  3C 00 43 30 */	lis r0, 0x4330
/* 8033EA90 0033B670  80 7F 00 04 */	lwz r3, 4(r31)
/* 8033EA94 0033B674  90 01 00 38 */	stw r0, 0x38(r1)
/* 8033EA98 0033B678  C8 22 E8 90 */	lfd f1, lbl_804DE270(r2)
/* 8033EA9C 0033B67C  54 63 06 1E */	rlwinm r3, r3, 0, 0x18, 0xf
/* 8033EAA0 0033B680  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 8033EAA4 0033B684  C0 42 E8 88 */	lfs f2, lbl_804DE268(r2)
/* 8033EAA8 0033B688  EC 00 08 28 */	fsubs f0, f0, f1
/* 8033EAAC 0033B68C  EC 02 00 32 */	fmuls f0, f2, f0
/* 8033EAB0 0033B690  FC 00 00 1E */	fctiwz f0, f0
/* 8033EAB4 0033B694  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8033EAB8 0033B698  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8033EABC 0033B69C  50 03 44 2E */	rlwimi r3, r0, 8, 0x10, 0x17
/* 8033EAC0 0033B6A0  90 7F 00 04 */	stw r3, 4(r31)
/* 8033EAC4 0033B6A4  48 00 00 14 */	b lbl_8033EAD8
lbl_8033EAC8:
/* 8033EAC8 0033B6A8  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033EACC 0033B6AC  54 00 06 EE */	rlwinm r0, r0, 0, 0x1b, 0x17
/* 8033EAD0 0033B6B0  60 00 00 80 */	ori r0, r0, 0x80
/* 8033EAD4 0033B6B4  90 1F 00 00 */	stw r0, 0(r31)
lbl_8033EAD8:
/* 8033EAD8 0033B6B8  93 DF 00 14 */	stw r30, 0x14(r31)
/* 8033EADC 0033B6BC  57 A3 04 3E */	clrlwi r3, r29, 0x10
/* 8033EAE0 0033B6C0  57 C7 07 3E */	clrlwi r7, r30, 0x1c
/* 8033EAE4 0033B6C4  80 BF 00 08 */	lwz r5, 8(r31)
/* 8033EAE8 0033B6C8  57 84 04 3E */	clrlwi r4, r28, 0x10
/* 8033EAEC 0033B6CC  38 03 FF FF */	addi r0, r3, -1
/* 8033EAF0 0033B6D0  54 A6 00 2A */	rlwinm r6, r5, 0, 0, 0x15
/* 8033EAF4 0033B6D4  38 A4 FF FF */	addi r5, r4, -1
/* 8033EAF8 0033B6D8  7C C5 2B 78 */	or r5, r6, r5
/* 8033EAFC 0033B6DC  90 BF 00 08 */	stw r5, 8(r31)
/* 8033EB00 0033B6E0  54 05 50 2A */	slwi r5, r0, 0xa
/* 8033EB04 0033B6E4  57 60 D9 FE */	rlwinm r0, r27, 0x1b, 7, 0x1f
/* 8033EB08 0033B6E8  80 DF 00 08 */	lwz r6, 8(r31)
/* 8033EB0C 0033B6EC  28 07 00 0E */	cmplwi r7, 0xe
/* 8033EB10 0033B6F0  54 C6 05 96 */	rlwinm r6, r6, 0, 0x16, 0xb
/* 8033EB14 0033B6F4  7C C5 2B 78 */	or r5, r6, r5
/* 8033EB18 0033B6F8  90 BF 00 08 */	stw r5, 8(r31)
/* 8033EB1C 0033B6FC  80 BF 00 08 */	lwz r5, 8(r31)
/* 8033EB20 0033B700  54 A5 03 0E */	rlwinm r5, r5, 0, 0xc, 7
/* 8033EB24 0033B704  53 C5 A2 16 */	rlwimi r5, r30, 0x14, 8, 0xb
/* 8033EB28 0033B708  90 BF 00 08 */	stw r5, 8(r31)
/* 8033EB2C 0033B70C  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 8033EB30 0033B710  54 A5 00 14 */	rlwinm r5, r5, 0, 0, 0xa
/* 8033EB34 0033B714  7C A0 03 78 */	or r0, r5, r0
/* 8033EB38 0033B718  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8033EB3C 0033B71C  41 81 00 80 */	bgt lbl_8033EBBC
/* 8033EB40 0033B720  3C A0 80 40 */	lis r5, jtbl_804014A0@ha
/* 8033EB44 0033B724  38 A5 14 A0 */	addi r5, r5, jtbl_804014A0@l
/* 8033EB48 0033B728  54 E0 10 3A */	slwi r0, r7, 2
/* 8033EB4C 0033B72C  7C 05 00 2E */	lwzx r0, r5, r0
/* 8033EB50 0033B730  7C 09 03 A6 */	mtctr r0
/* 8033EB54 0033B734  4E 80 04 20 */	bctr 
entry lbl_8033EB58
/* 8033EB58 0033B738  38 00 00 01 */	li r0, 1
/* 8033EB5C 0033B73C  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EB60 0033B740  38 00 00 03 */	li r0, 3
/* 8033EB64 0033B744  38 E0 00 03 */	li r7, 3
/* 8033EB68 0033B748  48 00 00 64 */	b lbl_8033EBCC
entry lbl_8033EB6C
/* 8033EB6C 0033B74C  38 00 00 02 */	li r0, 2
/* 8033EB70 0033B750  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EB74 0033B754  38 00 00 03 */	li r0, 3
/* 8033EB78 0033B758  38 E0 00 02 */	li r7, 2
/* 8033EB7C 0033B75C  48 00 00 50 */	b lbl_8033EBCC
entry lbl_8033EB80
/* 8033EB80 0033B760  38 00 00 02 */	li r0, 2
/* 8033EB84 0033B764  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EB88 0033B768  38 00 00 02 */	li r0, 2
/* 8033EB8C 0033B76C  38 E0 00 02 */	li r7, 2
/* 8033EB90 0033B770  48 00 00 3C */	b lbl_8033EBCC
entry lbl_8033EB94
/* 8033EB94 0033B774  38 00 00 03 */	li r0, 3
/* 8033EB98 0033B778  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EB9C 0033B77C  38 00 00 02 */	li r0, 2
/* 8033EBA0 0033B780  38 E0 00 02 */	li r7, 2
/* 8033EBA4 0033B784  48 00 00 28 */	b lbl_8033EBCC
entry lbl_8033EBA8
/* 8033EBA8 0033B788  38 00 00 00 */	li r0, 0
/* 8033EBAC 0033B78C  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EBB0 0033B790  38 00 00 03 */	li r0, 3
/* 8033EBB4 0033B794  38 E0 00 03 */	li r7, 3
/* 8033EBB8 0033B798  48 00 00 14 */	b lbl_8033EBCC
entry lbl_8033EBBC
/* 8033EBBC 0033B79C  38 00 00 02 */	li r0, 2
/* 8033EBC0 0033B7A0  98 1F 00 1E */	stb r0, 0x1e(r31)
/* 8033EBC4 0033B7A4  38 00 00 02 */	li r0, 2
/* 8033EBC8 0033B7A8  38 E0 00 02 */	li r7, 2
lbl_8033EBCC:
/* 8033EBCC 0033B7AC  54 08 04 3E */	clrlwi r8, r0, 0x10
/* 8033EBD0 0033B7B0  38 C0 00 01 */	li r6, 1
/* 8033EBD4 0033B7B4  7C C5 40 30 */	slw r5, r6, r8
/* 8033EBD8 0033B7B8  54 E7 04 3E */	clrlwi r7, r7, 0x10
/* 8033EBDC 0033B7BC  38 05 FF FF */	addi r0, r5, -1
/* 8033EBE0 0033B7C0  7C C5 38 30 */	slw r5, r6, r7
/* 8033EBE4 0033B7C4  7C 84 02 14 */	add r4, r4, r0
/* 8033EBE8 0033B7C8  38 05 FF FF */	addi r0, r5, -1
/* 8033EBEC 0033B7CC  7C 84 46 30 */	sraw r4, r4, r8
/* 8033EBF0 0033B7D0  7C 03 02 14 */	add r0, r3, r0
/* 8033EBF4 0033B7D4  7C 00 3E 30 */	sraw r0, r0, r7
/* 8033EBF8 0033B7D8  7C 04 01 D6 */	mullw r0, r4, r0
/* 8033EBFC 0033B7DC  54 00 04 7E */	clrlwi r0, r0, 0x11
/* 8033EC00 0033B7E0  B0 1F 00 1C */	sth r0, 0x1c(r31)
/* 8033EC04 0033B7E4  88 1F 00 1F */	lbz r0, 0x1f(r31)
/* 8033EC08 0033B7E8  60 00 00 02 */	ori r0, r0, 2
/* 8033EC0C 0033B7EC  98 1F 00 1F */	stb r0, 0x1f(r31)
/* 8033EC10 0033B7F0  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8033EC14 0033B7F4  BB 01 00 40 */	lmw r24, 0x40(r1)
/* 8033EC18 0033B7F8  38 21 00 60 */	addi r1, r1, 0x60
/* 8033EC1C 0033B7FC  7C 08 03 A6 */	mtlr r0
/* 8033EC20 0033B800  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/YQyg4
#pragma push
asm unk_t GXInitTexObjCI()
{ // clang-format off
    nofralloc
/* 8033EC24 0033B804  7C 08 02 A6 */	mflr r0
/* 8033EC28 0033B808  90 01 00 04 */	stw r0, 4(r1)
/* 8033EC2C 0033B80C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8033EC30 0033B810  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8033EC34 0033B814  83 E1 00 38 */	lwz r31, 0x38(r1)
/* 8033EC38 0033B818  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8033EC3C 0033B81C  7C 7E 1B 78 */	mr r30, r3
/* 8033EC40 0033B820  4B FF FD 71 */	bl GXInitTexObj
/* 8033EC44 0033B824  88 1E 00 1F */	lbz r0, 0x1f(r30)
/* 8033EC48 0033B828  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 8033EC4C 0033B82C  98 1E 00 1F */	stb r0, 0x1f(r30)
/* 8033EC50 0033B830  93 FE 00 18 */	stw r31, 0x18(r30)
/* 8033EC54 0033B834  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8033EC58 0033B838  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8033EC5C 0033B83C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8033EC60 0033B840  38 21 00 30 */	addi r1, r1, 0x30
/* 8033EC64 0033B844  7C 08 03 A6 */	mtlr r0
/* 8033EC68 0033B848  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/K0q3K
#pragma push
asm unk_t GXInitTexObjLOD()
{ // clang-format off
    nofralloc
/* 8033EC6C 0033B84C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8033EC70 0033B850  C0 02 E8 98 */	lfs f0, lbl_804DE278(r2)
/* 8033EC74 0033B854  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8033EC78 0033B858  40 80 00 0C */	bge lbl_8033EC84
/* 8033EC7C 0033B85C  FC 60 00 90 */	fmr f3, f0
/* 8033EC80 0033B860  48 00 00 18 */	b lbl_8033EC98
lbl_8033EC84:
/* 8033EC84 0033B864  C0 02 E8 9C */	lfs f0, lbl_804DE27C(r2)
/* 8033EC88 0033B868  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8033EC8C 0033B86C  4C 41 13 82 */	cror 2, 1, 2
/* 8033EC90 0033B870  40 82 00 08 */	bne lbl_8033EC98
/* 8033EC94 0033B874  C0 62 E8 A0 */	lfs f3, lbl_804DE280(r2)
lbl_8033EC98:
/* 8033EC98 0033B878  C0 02 E8 A4 */	lfs f0, lbl_804DE284(r2)
/* 8033EC9C 0033B87C  2C 05 00 01 */	cmpwi r5, 1
/* 8033ECA0 0033B880  80 03 00 00 */	lwz r0, 0(r3)
/* 8033ECA4 0033B884  EC 00 00 F2 */	fmuls f0, f0, f3
/* 8033ECA8 0033B888  54 05 05 DC */	rlwinm r5, r0, 0, 0x17, 0xe
/* 8033ECAC 0033B88C  FC 00 00 1E */	fctiwz f0, f0
/* 8033ECB0 0033B890  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8033ECB4 0033B894  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8033ECB8 0033B898  50 05 4B EC */	rlwimi r5, r0, 9, 0xf, 0x16
/* 8033ECBC 0033B89C  90 A3 00 00 */	stw r5, 0(r3)
/* 8033ECC0 0033B8A0  40 82 00 0C */	bne lbl_8033ECCC
/* 8033ECC4 0033B8A4  38 A0 00 01 */	li r5, 1
/* 8033ECC8 0033B8A8  48 00 00 08 */	b lbl_8033ECD0
lbl_8033ECCC:
/* 8033ECCC 0033B8AC  38 A0 00 00 */	li r5, 0
lbl_8033ECD0:
/* 8033ECD0 0033B8B0  81 23 00 00 */	lwz r9, 0(r3)
/* 8033ECD4 0033B8B4  54 E0 06 3F */	clrlwi. r0, r7, 0x18
/* 8033ECD8 0033B8B8  54 A5 20 36 */	slwi r5, r5, 4
/* 8033ECDC 0033B8BC  55 27 07 34 */	rlwinm r7, r9, 0, 0x1c, 0x1a
/* 8033ECE0 0033B8C0  7C E5 2B 78 */	or r5, r7, r5
/* 8033ECE4 0033B8C4  90 A3 00 00 */	stw r5, 0(r3)
/* 8033ECE8 0033B8C8  38 AD A5 58 */	addi r5, r13, GX2HWFiltConv
/* 8033ECEC 0033B8CC  7C 05 20 AE */	lbzx r0, r5, r4
/* 8033ECF0 0033B8D0  80 E3 00 00 */	lwz r7, 0(r3)
/* 8033ECF4 0033B8D4  54 00 28 34 */	slwi r0, r0, 5
/* 8033ECF8 0033B8D8  54 E4 06 EE */	rlwinm r4, r7, 0, 0x1b, 0x17
/* 8033ECFC 0033B8DC  7C 80 03 78 */	or r0, r4, r0
/* 8033ED00 0033B8E0  90 03 00 00 */	stw r0, 0(r3)
/* 8033ED04 0033B8E4  41 82 00 0C */	beq lbl_8033ED10
/* 8033ED08 0033B8E8  38 00 00 00 */	li r0, 0
/* 8033ED0C 0033B8EC  48 00 00 08 */	b lbl_8033ED14
lbl_8033ED10:
/* 8033ED10 0033B8F0  38 00 00 01 */	li r0, 1
lbl_8033ED14:
/* 8033ED14 0033B8F4  80 83 00 00 */	lwz r4, 0(r3)
/* 8033ED18 0033B8F8  54 00 40 2E */	slwi r0, r0, 8
/* 8033ED1C 0033B8FC  54 84 06 2C */	rlwinm r4, r4, 0, 0x18, 0x16
/* 8033ED20 0033B900  7C 80 03 78 */	or r0, r4, r0
/* 8033ED24 0033B904  90 03 00 00 */	stw r0, 0(r3)
/* 8033ED28 0033B908  55 04 98 18 */	slwi r4, r8, 0x13
/* 8033ED2C 0033B90C  54 C0 A8 D4 */	rlwinm r0, r6, 0x15, 3, 0xa
/* 8033ED30 0033B910  80 A3 00 00 */	lwz r5, 0(r3)
/* 8033ED34 0033B914  54 A5 03 DA */	rlwinm r5, r5, 0, 0xf, 0xd
/* 8033ED38 0033B918  90 A3 00 00 */	stw r5, 0(r3)
/* 8033ED3C 0033B91C  80 A3 00 00 */	lwz r5, 0(r3)
/* 8033ED40 0033B920  54 A5 03 98 */	rlwinm r5, r5, 0, 0xe, 0xc
/* 8033ED44 0033B924  90 A3 00 00 */	stw r5, 0(r3)
/* 8033ED48 0033B928  80 A3 00 00 */	lwz r5, 0(r3)
/* 8033ED4C 0033B92C  54 A5 03 54 */	rlwinm r5, r5, 0, 0xd, 0xa
/* 8033ED50 0033B930  7C A4 23 78 */	or r4, r5, r4
/* 8033ED54 0033B934  90 83 00 00 */	stw r4, 0(r3)
/* 8033ED58 0033B938  80 83 00 00 */	lwz r4, 0(r3)
/* 8033ED5C 0033B93C  54 84 02 D2 */	rlwinm r4, r4, 0, 0xb, 9
/* 8033ED60 0033B940  7C 80 03 78 */	or r0, r4, r0
/* 8033ED64 0033B944  90 03 00 00 */	stw r0, 0(r3)
/* 8033ED68 0033B948  C0 02 E8 A8 */	lfs f0, lbl_804DE288(r2)
/* 8033ED6C 0033B94C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8033ED70 0033B950  40 80 00 0C */	bge lbl_8033ED7C
/* 8033ED74 0033B954  FC 20 00 90 */	fmr f1, f0
/* 8033ED78 0033B958  48 00 00 14 */	b lbl_8033ED8C
lbl_8033ED7C:
/* 8033ED7C 0033B95C  C0 02 E8 AC */	lfs f0, lbl_804DE28C(r2)
/* 8033ED80 0033B960  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8033ED84 0033B964  40 81 00 08 */	ble lbl_8033ED8C
/* 8033ED88 0033B968  FC 20 00 90 */	fmr f1, f0
lbl_8033ED8C:
/* 8033ED8C 0033B96C  C0 62 E8 88 */	lfs f3, lbl_804DE268(r2)
/* 8033ED90 0033B970  C0 02 E8 A8 */	lfs f0, lbl_804DE288(r2)
/* 8033ED94 0033B974  EC 23 00 72 */	fmuls f1, f3, f1
/* 8033ED98 0033B978  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8033ED9C 0033B97C  FC 20 08 1E */	fctiwz f1, f1
/* 8033EDA0 0033B980  D8 21 00 30 */	stfd f1, 0x30(r1)
/* 8033EDA4 0033B984  80 81 00 34 */	lwz r4, 0x34(r1)
/* 8033EDA8 0033B988  40 80 00 0C */	bge lbl_8033EDB4
/* 8033EDAC 0033B98C  FC 40 00 90 */	fmr f2, f0
/* 8033EDB0 0033B990  48 00 00 14 */	b lbl_8033EDC4
lbl_8033EDB4:
/* 8033EDB4 0033B994  C0 02 E8 AC */	lfs f0, lbl_804DE28C(r2)
/* 8033EDB8 0033B998  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8033EDBC 0033B99C  40 81 00 08 */	ble lbl_8033EDC4
/* 8033EDC0 0033B9A0  FC 40 00 90 */	fmr f2, f0
lbl_8033EDC4:
/* 8033EDC4 0033B9A4  80 03 00 04 */	lwz r0, 4(r3)
/* 8033EDC8 0033B9A8  54 00 00 2E */	rlwinm r0, r0, 0, 0, 0x17
/* 8033EDCC 0033B9AC  50 80 06 3E */	rlwimi r0, r4, 0, 0x18, 0x1f
/* 8033EDD0 0033B9B0  90 03 00 04 */	stw r0, 4(r3)
/* 8033EDD4 0033B9B4  C0 02 E8 88 */	lfs f0, lbl_804DE268(r2)
/* 8033EDD8 0033B9B8  80 03 00 04 */	lwz r0, 4(r3)
/* 8033EDDC 0033B9BC  EC 00 00 B2 */	fmuls f0, f0, f2
/* 8033EDE0 0033B9C0  54 04 06 1E */	rlwinm r4, r0, 0, 0x18, 0xf
/* 8033EDE4 0033B9C4  FC 00 00 1E */	fctiwz f0, f0
/* 8033EDE8 0033B9C8  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8033EDEC 0033B9CC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8033EDF0 0033B9D0  38 21 00 38 */	addi r1, r1, 0x38
/* 8033EDF4 0033B9D4  50 04 44 2E */	rlwimi r4, r0, 8, 0x10, 0x17
/* 8033EDF8 0033B9D8  90 83 00 04 */	stw r4, 4(r3)
/* 8033EDFC 0033B9DC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/7cs9I
#pragma push
asm unk_t GXGetTexObjWidth()
{ // clang-format off
    nofralloc
/* 8033EE00 0033B9E0  80 03 00 08 */	lwz r0, 8(r3)
/* 8033EE04 0033B9E4  54 03 05 BE */	clrlwi r3, r0, 0x16
/* 8033EE08 0033B9E8  38 63 00 01 */	addi r3, r3, 1
/* 8033EE0C 0033B9EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/RPxXA
#pragma push
asm unk_t GXGetTexObjHeight(){ // clang-format off
    nofralloc
/* 8033EE10 0033B9F0  80 03 00 08 */	lwz r0, 8(r3)
/* 8033EE14 0033B9F4  54 03 B5 BE */	rlwinm r3, r0, 0x16, 0x16, 0x1f
/* 8033EE18 0033B9F8  38 63 00 01 */	addi r3, r3, 1
/* 8033EE1C 0033B9FC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

GXTexFmt GXGetTexObjFmt(GXTexObj* tex_obj)
{
    return tex_obj->tex_fmt;
}

// https://decomp.me/scratch/ZnHCT
#pragma push
asm unk_t GXLoadTexObjPreLoaded()
{ // clang-format off
    nofralloc
/* 8033EE28 0033BA08  7C 08 02 A6 */	mflr r0
/* 8033EE2C 0033BA0C  38 ED A5 30 */	addi r7, r13, GXTexImage0Ids
/* 8033EE30 0033BA10  90 01 00 04 */	stw r0, 4(r1)
/* 8033EE34 0033BA14  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033EE38 0033BA18  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8033EE3C 0033BA1C  3F E0 CC 01 */	lis r31, 0xCC008000@ha
/* 8033EE40 0033BA20  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8033EE44 0033BA24  3B C0 00 61 */	li r30, 0x61
/* 8033EE48 0033BA28  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8033EE4C 0033BA2C  3B A5 00 00 */	addi r29, r5, 0
/* 8033EE50 0033BA30  38 AD A5 40 */	addi r5, r13, GXTexImage2Ids
/* 8033EE54 0033BA34  93 81 00 18 */	stw r28, 0x18(r1)
/* 8033EE58 0033BA38  7C 7C 1B 78 */	mr r28, r3
/* 8033EE5C 0033BA3C  80 C3 00 00 */	lwz r6, 0(r3)
/* 8033EE60 0033BA40  38 6D A5 20 */	addi r3, r13, GXTexMode0Ids
/* 8033EE64 0033BA44  7C 03 E8 AE */	lbzx r0, r3, r29
/* 8033EE68 0033BA48  38 6D A5 28 */	addi r3, r13, GXTexMode1Ids
/* 8033EE6C 0033BA4C  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EE70 0033BA50  50 C0 02 3E */	rlwimi r0, r6, 0, 8, 0x1f
/* 8033EE74 0033BA54  90 1C 00 00 */	stw r0, 0(r28)
/* 8033EE78 0033BA58  38 CD A5 38 */	addi r6, r13, GXTexImage1Ids
/* 8033EE7C 0033BA5C  7C 03 E8 AE */	lbzx r0, r3, r29
/* 8033EE80 0033BA60  38 6D A5 48 */	addi r3, r13, GXTexImage3Ids
/* 8033EE84 0033BA64  81 1C 00 04 */	lwz r8, 4(r28)
/* 8033EE88 0033BA68  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EE8C 0033BA6C  51 00 02 3E */	rlwimi r0, r8, 0, 8, 0x1f
/* 8033EE90 0033BA70  90 1C 00 04 */	stw r0, 4(r28)
/* 8033EE94 0033BA74  7C 07 E8 AE */	lbzx r0, r7, r29
/* 8033EE98 0033BA78  81 1C 00 08 */	lwz r8, 8(r28)
/* 8033EE9C 0033BA7C  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EEA0 0033BA80  51 00 02 3E */	rlwimi r0, r8, 0, 8, 0x1f
/* 8033EEA4 0033BA84  90 1C 00 08 */	stw r0, 8(r28)
/* 8033EEA8 0033BA88  7C 06 E8 AE */	lbzx r0, r6, r29
/* 8033EEAC 0033BA8C  80 E4 00 00 */	lwz r7, 0(r4)
/* 8033EEB0 0033BA90  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EEB4 0033BA94  50 E0 02 3E */	rlwimi r0, r7, 0, 8, 0x1f
/* 8033EEB8 0033BA98  90 04 00 00 */	stw r0, 0(r4)
/* 8033EEBC 0033BA9C  7C 05 E8 AE */	lbzx r0, r5, r29
/* 8033EEC0 0033BAA0  80 C4 00 04 */	lwz r6, 4(r4)
/* 8033EEC4 0033BAA4  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EEC8 0033BAA8  50 C0 02 3E */	rlwimi r0, r6, 0, 8, 0x1f
/* 8033EECC 0033BAAC  90 04 00 04 */	stw r0, 4(r4)
/* 8033EED0 0033BAB0  7C 03 E8 AE */	lbzx r0, r3, r29
/* 8033EED4 0033BAB4  80 BC 00 0C */	lwz r5, 0xc(r28)
/* 8033EED8 0033BAB8  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EEDC 0033BABC  50 A0 02 3E */	rlwimi r0, r5, 0, 8, 0x1f
/* 8033EEE0 0033BAC0  90 1C 00 0C */	stw r0, 0xc(r28)
/* 8033EEE4 0033BAC4  9B DF 80 00 */	stb r30, 0xCC008000@l(r31)
/* 8033EEE8 0033BAC8  80 1C 00 00 */	lwz r0, 0(r28)
/* 8033EEEC 0033BACC  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EEF0 0033BAD0  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EEF4 0033BAD4  80 1C 00 04 */	lwz r0, 4(r28)
/* 8033EEF8 0033BAD8  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EEFC 0033BADC  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EF00 0033BAE0  80 1C 00 08 */	lwz r0, 8(r28)
/* 8033EF04 0033BAE4  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EF08 0033BAE8  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EF0C 0033BAEC  80 04 00 00 */	lwz r0, 0(r4)
/* 8033EF10 0033BAF0  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EF14 0033BAF4  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EF18 0033BAF8  80 04 00 04 */	lwz r0, 4(r4)
/* 8033EF1C 0033BAFC  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EF20 0033BB00  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EF24 0033BB04  80 1C 00 0C */	lwz r0, 0xc(r28)
/* 8033EF28 0033BB08  90 1F 80 00 */	stw r0, -0x8000(r31)
/* 8033EF2C 0033BB0C  88 1C 00 1F */	lbz r0, 0x1f(r28)
/* 8033EF30 0033BB10  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 8033EF34 0033BB14  40 82 00 3C */	bne lbl_8033EF70
/* 8033EF38 0033BB18  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033EF3C 0033BB1C  80 7C 00 18 */	lwz r3, 0x18(r28)
/* 8033EF40 0033BB20  81 84 04 14 */	lwz r12, 0x414(r4)
/* 8033EF44 0033BB24  7D 88 03 A6 */	mtlr r12
/* 8033EF48 0033BB28  4E 80 00 21 */	blrl 
/* 8033EF4C 0033BB2C  38 8D A5 50 */	addi r4, r13, GXTexTlutIds
/* 8033EF50 0033BB30  80 A3 00 04 */	lwz r5, 4(r3)
/* 8033EF54 0033BB34  7C 04 E8 AE */	lbzx r0, r4, r29
/* 8033EF58 0033BB38  54 00 C0 0E */	slwi r0, r0, 0x18
/* 8033EF5C 0033BB3C  50 A0 02 3E */	rlwimi r0, r5, 0, 8, 0x1f
/* 8033EF60 0033BB40  90 03 00 04 */	stw r0, 4(r3)
/* 8033EF64 0033BB44  9B DF 80 00 */	stb r30, -0x8000(r31)
/* 8033EF68 0033BB48  80 03 00 04 */	lwz r0, 4(r3)
/* 8033EF6C 0033BB4C  90 1F 80 00 */	stw r0, -0x8000(r31)
lbl_8033EF70:
/* 8033EF70 0033BB50  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033EF74 0033BB54  57 A5 10 3A */	slwi r5, r29, 2
/* 8033EF78 0033BB58  80 9C 00 08 */	lwz r4, 8(r28)
/* 8033EF7C 0033BB5C  38 00 00 00 */	li r0, 0
/* 8033EF80 0033BB60  7C 63 2A 14 */	add r3, r3, r5
/* 8033EF84 0033BB64  90 83 04 5C */	stw r4, 0x45c(r3)
/* 8033EF88 0033BB68  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033EF8C 0033BB6C  80 9C 00 00 */	lwz r4, 0(r28)
/* 8033EF90 0033BB70  7C 63 2A 14 */	add r3, r3, r5
/* 8033EF94 0033BB74  90 83 04 7C */	stw r4, 0x47c(r3)
/* 8033EF98 0033BB78  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033EF9C 0033BB7C  80 64 04 F0 */	lwz r3, 0x4f0(r4)
/* 8033EFA0 0033BB80  60 63 00 01 */	ori r3, r3, 1
/* 8033EFA4 0033BB84  90 64 04 F0 */	stw r3, 0x4f0(r4)
/* 8033EFA8 0033BB88  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033EFAC 0033BB8C  B0 03 00 02 */	sth r0, 2(r3)
/* 8033EFB0 0033BB90  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8033EFB4 0033BB94  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8033EFB8 0033BB98  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8033EFBC 0033BB9C  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8033EFC0 0033BBA0  83 81 00 18 */	lwz r28, 0x18(r1)
/* 8033EFC4 0033BBA4  38 21 00 28 */	addi r1, r1, 0x28
/* 8033EFC8 0033BBA8  7C 08 03 A6 */	mtlr r0
/* 8033EFCC 0033BBAC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/es1CS
#pragma push
asm unk_t GXLoadTexObj()
{ // clang-format off
    nofralloc
/* 8033EFD0 0033BBB0  7C 08 02 A6 */	mflr r0
/* 8033EFD4 0033BBB4  90 01 00 04 */	stw r0, 4(r1)
/* 8033EFD8 0033BBB8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033EFDC 0033BBBC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033EFE0 0033BBC0  3B E4 00 00 */	addi r31, r4, 0
/* 8033EFE4 0033BBC4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033EFE8 0033BBC8  3B C3 00 00 */	addi r30, r3, 0
/* 8033EFEC 0033BBCC  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033EFF0 0033BBD0  81 85 04 10 */	lwz r12, 0x410(r5)
/* 8033EFF4 0033BBD4  7D 88 03 A6 */	mtlr r12
/* 8033EFF8 0033BBD8  4E 80 00 21 */	blrl 
/* 8033EFFC 0033BBDC  38 83 00 00 */	addi r4, r3, 0
/* 8033F000 0033BBE0  38 7E 00 00 */	addi r3, r30, 0
/* 8033F004 0033BBE4  38 BF 00 00 */	addi r5, r31, 0
/* 8033F008 0033BBE8  4B FF FE 21 */	bl GXLoadTexObjPreLoaded
/* 8033F00C 0033BBEC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033F010 0033BBF0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033F014 0033BBF4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033F018 0033BBF8  7C 08 03 A6 */	mtlr r0
/* 8033F01C 0033BBFC  38 21 00 18 */	addi r1, r1, 0x18
/* 8033F020 0033BC00  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/Y9lJO
#pragma push
asm unk_t GXInitTlutObj()
{ // clang-format off
    nofralloc
/* 8033F024 0033BC04  38 00 00 00 */	li r0, 0
/* 8033F028 0033BC08  90 03 00 00 */	stw r0, 0(r3)
/* 8033F02C 0033BC0C  54 A5 50 2A */	slwi r5, r5, 0xa
/* 8033F030 0033BC10  54 80 D9 FE */	rlwinm r0, r4, 0x1b, 7, 0x1f
/* 8033F034 0033BC14  80 E3 00 00 */	lwz r7, 0(r3)
/* 8033F038 0033BC18  54 E4 05 A6 */	rlwinm r4, r7, 0, 0x16, 0x13
/* 8033F03C 0033BC1C  7C 84 2B 78 */	or r4, r4, r5
/* 8033F040 0033BC20  90 83 00 00 */	stw r4, 0(r3)
/* 8033F044 0033BC24  80 83 00 04 */	lwz r4, 4(r3)
/* 8033F048 0033BC28  54 84 00 14 */	rlwinm r4, r4, 0, 0, 0xa
/* 8033F04C 0033BC2C  7C 80 03 78 */	or r0, r4, r0
/* 8033F050 0033BC30  90 03 00 04 */	stw r0, 4(r3)
/* 8033F054 0033BC34  80 03 00 04 */	lwz r0, 4(r3)
/* 8033F058 0033BC38  54 00 02 3E */	clrlwi r0, r0, 8
/* 8033F05C 0033BC3C  64 00 64 00 */	oris r0, r0, 0x6400
/* 8033F060 0033BC40  90 03 00 04 */	stw r0, 4(r3)
/* 8033F064 0033BC44  B0 C3 00 08 */	sth r6, 8(r3)
/* 8033F068 0033BC48  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/9AKJV
#pragma push
asm unk_t GXLoadTlut()
{ // clang-format off
    nofralloc
/* 8033F06C 0033BC4C  7C 08 02 A6 */	mflr r0
/* 8033F070 0033BC50  90 01 00 04 */	stw r0, 4(r1)
/* 8033F074 0033BC54  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8033F078 0033BC58  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8033F07C 0033BC5C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8033F080 0033BC60  7C 7E 1B 78 */	mr r30, r3
/* 8033F084 0033BC64  38 64 00 00 */	addi r3, r4, 0
/* 8033F088 0033BC68  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F08C 0033BC6C  81 85 04 14 */	lwz r12, 0x414(r5)
/* 8033F090 0033BC70  7D 88 03 A6 */	mtlr r12
/* 8033F094 0033BC74  4E 80 00 21 */	blrl 
/* 8033F098 0033BC78  7C 7F 1B 78 */	mr r31, r3
/* 8033F09C 0033BC7C  48 00 0D 05 */	bl __GXFlushTextureState
/* 8033F0A0 0033BC80  38 80 00 61 */	li r4, 0x61
/* 8033F0A4 0033BC84  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033F0A8 0033BC88  98 83 80 00 */	stb r4, 0xCC008000@l(r3)
/* 8033F0AC 0033BC8C  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033F0B0 0033BC90  90 03 80 00 */	stw r0, -0x8000(r3)
/* 8033F0B4 0033BC94  98 83 80 00 */	stb r4, -0x8000(r3)
/* 8033F0B8 0033BC98  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033F0BC 0033BC9C  90 03 80 00 */	stw r0, -0x8000(r3)
/* 8033F0C0 0033BCA0  48 00 0C E1 */	bl __GXFlushTextureState
/* 8033F0C4 0033BCA4  80 1F 00 00 */	lwz r0, 0(r31)
/* 8033F0C8 0033BCA8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8033F0CC 0033BCAC  54 00 05 BE */	clrlwi r0, r0, 0x16
/* 8033F0D0 0033BCB0  50 60 00 2A */	rlwimi r0, r3, 0, 0, 0x15
/* 8033F0D4 0033BCB4  90 1E 00 00 */	stw r0, 0(r30)
/* 8033F0D8 0033BCB8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8033F0DC 0033BCBC  80 1E 00 04 */	lwz r0, 4(r30)
/* 8033F0E0 0033BCC0  90 7F 00 04 */	stw r3, 4(r31)
/* 8033F0E4 0033BCC4  90 1F 00 08 */	stw r0, 8(r31)
/* 8033F0E8 0033BCC8  80 1E 00 08 */	lwz r0, 8(r30)
/* 8033F0EC 0033BCCC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 8033F0F0 0033BCD0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8033F0F4 0033BCD4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8033F0F8 0033BCD8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8033F0FC 0033BCDC  7C 08 03 A6 */	mtlr r0
/* 8033F100 0033BCE0  38 21 00 20 */	addi r1, r1, 0x20
/* 8033F104 0033BCE4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/GFUrl // 7200 (0%)
#pragma push
asm unk_t GXInitTexCacheRegion()
{ // clang-format off
    nofralloc
/* 8033F108 0033BCE8  2C 06 00 01 */	cmpwi r6, 1
/* 8033F10C 0033BCEC  41 82 00 28 */	beq lbl_8033F134
/* 8033F110 0033BCF0  40 80 00 10 */	bge lbl_8033F120
/* 8033F114 0033BCF4  2C 06 00 00 */	cmpwi r6, 0
/* 8033F118 0033BCF8  40 80 00 14 */	bge lbl_8033F12C
/* 8033F11C 0033BCFC  48 00 00 24 */	b lbl_8033F140
lbl_8033F120:
/* 8033F120 0033BD00  2C 06 00 03 */	cmpwi r6, 3
/* 8033F124 0033BD04  40 80 00 1C */	bge lbl_8033F140
/* 8033F128 0033BD08  48 00 00 14 */	b lbl_8033F13C
lbl_8033F12C:
/* 8033F12C 0033BD0C  39 40 00 03 */	li r10, 3
/* 8033F130 0033BD10  48 00 00 10 */	b lbl_8033F140
lbl_8033F134:
/* 8033F134 0033BD14  39 40 00 04 */	li r10, 4
/* 8033F138 0033BD18  48 00 00 08 */	b lbl_8033F140
lbl_8033F13C:
/* 8033F13C 0033BD1C  39 40 00 05 */	li r10, 5
lbl_8033F140:
/* 8033F140 0033BD20  38 00 00 00 */	li r0, 0
/* 8033F144 0033BD24  90 03 00 00 */	stw r0, 0(r3)
/* 8033F148 0033BD28  54 A6 D9 7E */	srwi r6, r5, 5
/* 8033F14C 0033BD2C  55 45 78 20 */	slwi r5, r10, 0xf
/* 8033F150 0033BD30  81 23 00 00 */	lwz r9, 0(r3)
/* 8033F154 0033BD34  55 40 90 1A */	slwi r0, r10, 0x12
/* 8033F158 0033BD38  2C 08 00 02 */	cmpwi r8, 2
/* 8033F15C 0033BD3C  55 29 00 20 */	rlwinm r9, r9, 0, 0, 0x10
/* 8033F160 0033BD40  7D 26 33 78 */	or r6, r9, r6
/* 8033F164 0033BD44  90 C3 00 00 */	stw r6, 0(r3)
/* 8033F168 0033BD48  80 C3 00 00 */	lwz r6, 0(r3)
/* 8033F16C 0033BD4C  54 C6 04 5A */	rlwinm r6, r6, 0, 0x11, 0xd
/* 8033F170 0033BD50  7C C5 2B 78 */	or r5, r6, r5
/* 8033F174 0033BD54  90 A3 00 00 */	stw r5, 0(r3)
/* 8033F178 0033BD58  80 A3 00 00 */	lwz r5, 0(r3)
/* 8033F17C 0033BD5C  54 A5 03 94 */	rlwinm r5, r5, 0, 0xe, 0xa
/* 8033F180 0033BD60  7C A0 03 78 */	or r0, r5, r0
/* 8033F184 0033BD64  90 03 00 00 */	stw r0, 0(r3)
/* 8033F188 0033BD68  80 03 00 00 */	lwz r0, 0(r3)
/* 8033F18C 0033BD6C  54 00 02 D2 */	rlwinm r0, r0, 0, 0xb, 9
/* 8033F190 0033BD70  90 03 00 00 */	stw r0, 0(r3)
/* 8033F194 0033BD74  41 82 00 34 */	beq lbl_8033F1C8
/* 8033F198 0033BD78  40 80 00 14 */	bge lbl_8033F1AC
/* 8033F19C 0033BD7C  2C 08 00 00 */	cmpwi r8, 0
/* 8033F1A0 0033BD80  41 82 00 18 */	beq lbl_8033F1B8
/* 8033F1A4 0033BD84  40 80 00 1C */	bge lbl_8033F1C0
/* 8033F1A8 0033BD88  48 00 00 2C */	b lbl_8033F1D4
lbl_8033F1AC:
/* 8033F1AC 0033BD8C  2C 08 00 04 */	cmpwi r8, 4
/* 8033F1B0 0033BD90  40 80 00 24 */	bge lbl_8033F1D4
/* 8033F1B4 0033BD94  48 00 00 1C */	b lbl_8033F1D0
lbl_8033F1B8:
/* 8033F1B8 0033BD98  39 40 00 03 */	li r10, 3
/* 8033F1BC 0033BD9C  48 00 00 18 */	b lbl_8033F1D4
lbl_8033F1C0:
/* 8033F1C0 0033BDA0  39 40 00 04 */	li r10, 4
/* 8033F1C4 0033BDA4  48 00 00 10 */	b lbl_8033F1D4
lbl_8033F1C8:
/* 8033F1C8 0033BDA8  39 40 00 05 */	li r10, 5
/* 8033F1CC 0033BDAC  48 00 00 08 */	b lbl_8033F1D4
lbl_8033F1D0:
/* 8033F1D0 0033BDB0  39 40 00 00 */	li r10, 0
lbl_8033F1D4:
/* 8033F1D4 0033BDB4  38 00 00 00 */	li r0, 0
/* 8033F1D8 0033BDB8  90 03 00 04 */	stw r0, 4(r3)
/* 8033F1DC 0033BDBC  54 E7 D9 7E */	srwi r7, r7, 5
/* 8033F1E0 0033BDC0  55 46 78 20 */	slwi r6, r10, 0xf
/* 8033F1E4 0033BDC4  81 03 00 04 */	lwz r8, 4(r3)
/* 8033F1E8 0033BDC8  55 45 90 1A */	slwi r5, r10, 0x12
/* 8033F1EC 0033BDCC  38 00 00 01 */	li r0, 1
/* 8033F1F0 0033BDD0  55 08 00 20 */	rlwinm r8, r8, 0, 0, 0x10
/* 8033F1F4 0033BDD4  7D 07 3B 78 */	or r7, r8, r7
/* 8033F1F8 0033BDD8  90 E3 00 04 */	stw r7, 4(r3)
/* 8033F1FC 0033BDDC  80 E3 00 04 */	lwz r7, 4(r3)
/* 8033F200 0033BDE0  54 E7 04 5A */	rlwinm r7, r7, 0, 0x11, 0xd
/* 8033F204 0033BDE4  7C E6 33 78 */	or r6, r7, r6
/* 8033F208 0033BDE8  90 C3 00 04 */	stw r6, 4(r3)
/* 8033F20C 0033BDEC  80 C3 00 04 */	lwz r6, 4(r3)
/* 8033F210 0033BDF0  54 C6 03 94 */	rlwinm r6, r6, 0, 0xe, 0xa
/* 8033F214 0033BDF4  7C C5 2B 78 */	or r5, r6, r5
/* 8033F218 0033BDF8  90 A3 00 04 */	stw r5, 4(r3)
/* 8033F21C 0033BDFC  98 83 00 0C */	stb r4, 0xc(r3)
/* 8033F220 0033BE00  98 03 00 0D */	stb r0, 0xd(r3)
/* 8033F224 0033BE04  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void GXInitTlutRegion(s32* arg0, s32 arg1, s32 arg2)
{
    *arg0 = 0;
    *arg0 = (*arg0 & 0xFFFFFC00) | ((u32) (arg1 + 0xFFF80000) >> 9U);
    *arg0 = (*arg0 & 0xFFE003FF) | (arg2 << 0xA);
    *arg0 = (*arg0 & 0xFFFFFF) | 0x65000000;
}

// https://decomp.me/scratch/uPSnJ // 1035 (42.50%)
#pragma push
asm unk_t GXInvalidateTexAll()
{ // clang-format off
    nofralloc
/* 8033F270 0033BE50  7C 08 02 A6 */	mflr r0
/* 8033F274 0033BE54  90 01 00 04 */	stw r0, 4(r1)
/* 8033F278 0033BE58  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033F27C 0033BE5C  48 00 0B 25 */	bl __GXFlushTextureState
/* 8033F280 0033BE60  38 C0 00 61 */	li r6, 0x61
/* 8033F284 0033BE64  3C 60 66 00 */	lis r3, 0x66001000@ha
/* 8033F288 0033BE68  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033F28C 0033BE6C  98 C5 80 00 */	stb r6, 0xCC008000@l(r5)
/* 8033F290 0033BE70  38 83 10 00 */	addi r4, r3, 0x66001000@l
/* 8033F294 0033BE74  38 03 11 00 */	addi r0, r3, 0x1100
/* 8033F298 0033BE78  90 85 80 00 */	stw r4, -0x8000(r5)
/* 8033F29C 0033BE7C  98 C5 80 00 */	stb r6, -0x8000(r5)
/* 8033F2A0 0033BE80  90 05 80 00 */	stw r0, -0x8000(r5)
/* 8033F2A4 0033BE84  48 00 0A FD */	bl __GXFlushTextureState
/* 8033F2A8 0033BE88  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033F2AC 0033BE8C  38 21 00 08 */	addi r1, r1, 8
/* 8033F2B0 0033BE90  7C 08 03 A6 */	mtlr r0
/* 8033F2B4 0033BE94  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/UXYXZ // 305 (39%)
#pragma push
asm unk_t GXSetTexRegionCallback()
{ // clang-format off
    nofralloc
/* 8033F2B8 0033BE98  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033F2BC 0033BE9C  84 04 04 10 */	lwzu r0, 0x410(r4)
/* 8033F2C0 0033BEA0  90 64 00 00 */	stw r3, 0(r4)
/* 8033F2C4 0033BEA4  7C 03 03 78 */	mr r3, r0
/* 8033F2C8 0033BEA8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/Xojw3 // 305 (39%)
#pragma push
asm unk_t GXSetTlutRegionCallback()
{ // clang-format off
    nofralloc
/* 8033F2CC 0033BEAC  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033F2D0 0033BEB0  84 04 04 14 */	lwzu r0, 0x414(r4)
/* 8033F2D4 0033BEB4  90 64 00 00 */	stw r3, 0(r4)
/* 8033F2D8 0033BEB8  7C 03 03 78 */	mr r3, r0
/* 8033F2DC 0033BEBC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/Npksb
#pragma push
asm unk_t __SetSURegs()
{ // clang-format off
    nofralloc
/* 8033F2E0 0033BEC0  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F2E4 0033BEC4  54 80 10 3A */	slwi r0, r4, 2
/* 8033F2E8 0033BEC8  54 69 10 3A */	slwi r9, r3, 2
/* 8033F2EC 0033BECC  7C 85 02 14 */	add r4, r5, r0
/* 8033F2F0 0033BED0  7C 65 4A 14 */	add r3, r5, r9
/* 8033F2F4 0033BED4  80 A3 04 5C */	lwz r5, 0x45c(r3)
/* 8033F2F8 0033BED8  38 E0 00 61 */	li r7, 0x61
/* 8033F2FC 0033BEDC  80 64 00 B8 */	lwz r3, 0xb8(r4)
/* 8033F300 0033BEE0  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033F304 0033BEE4  54 63 00 1E */	rlwinm r3, r3, 0, 0, 0xf
/* 8033F308 0033BEE8  50 A3 05 BE */	rlwimi r3, r5, 0, 0x16, 0x1f
/* 8033F30C 0033BEEC  90 64 00 B8 */	stw r3, 0xb8(r4)
/* 8033F310 0033BEF0  38 60 00 00 */	li r3, 0
/* 8033F314 0033BEF4  80 8D A5 08 */	lwz r4, __GXContexts(r13)
/* 8033F318 0033BEF8  7D 04 02 14 */	add r8, r4, r0
/* 8033F31C 0033BEFC  80 88 00 D8 */	lwz r4, 0xd8(r8)
/* 8033F320 0033BF00  54 84 00 1E */	rlwinm r4, r4, 0, 0, 0xf
/* 8033F324 0033BF04  50 A4 B5 BE */	rlwimi r4, r5, 0x16, 0x16, 0x1f
/* 8033F328 0033BF08  90 88 00 D8 */	stw r4, 0xd8(r8)
/* 8033F32C 0033BF0C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F330 0033BF10  7C 85 4A 14 */	add r4, r5, r9
/* 8033F334 0033BF14  81 24 04 7C */	lwz r9, 0x47c(r4)
/* 8033F338 0033BF18  7D 45 02 14 */	add r10, r5, r0
/* 8033F33C 0033BF1C  80 AA 00 B8 */	lwz r5, 0xb8(r10)
/* 8033F340 0033BF20  55 24 F7 BE */	rlwinm r4, r9, 0x1e, 0x1e, 0x1f
/* 8033F344 0033BF24  21 04 00 01 */	subfic r8, r4, 1
/* 8033F348 0033BF28  55 24 07 BE */	clrlwi r4, r9, 0x1e
/* 8033F34C 0033BF2C  20 84 00 01 */	subfic r4, r4, 1
/* 8033F350 0033BF30  7C 84 00 34 */	cntlzw r4, r4
/* 8033F354 0033BF34  54 A5 04 1C */	rlwinm r5, r5, 0, 0x10, 0xe
/* 8033F358 0033BF38  54 84 5A 1E */	rlwinm r4, r4, 0xb, 8, 0xf
/* 8033F35C 0033BF3C  7C A4 23 78 */	or r4, r5, r4
/* 8033F360 0033BF40  90 8A 00 B8 */	stw r4, 0xb8(r10)
/* 8033F364 0033BF44  7D 04 00 34 */	cntlzw r4, r8
/* 8033F368 0033BF48  54 84 5A 1E */	rlwinm r4, r4, 0xb, 8, 0xf
/* 8033F36C 0033BF4C  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F370 0033BF50  7D 05 02 14 */	add r8, r5, r0
/* 8033F374 0033BF54  80 A8 00 D8 */	lwz r5, 0xd8(r8)
/* 8033F378 0033BF58  54 A5 04 1C */	rlwinm r5, r5, 0, 0x10, 0xe
/* 8033F37C 0033BF5C  7C A4 23 78 */	or r4, r5, r4
/* 8033F380 0033BF60  90 88 00 D8 */	stw r4, 0xd8(r8)
/* 8033F384 0033BF64  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F388 0033BF68  98 E6 80 00 */	stb r7, 0xCC008000@l(r6)
/* 8033F38C 0033BF6C  7C 85 02 14 */	add r4, r5, r0
/* 8033F390 0033BF70  80 04 00 B8 */	lwz r0, 0xb8(r4)
/* 8033F394 0033BF74  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033F398 0033BF78  98 E6 80 00 */	stb r7, -0x8000(r6)
/* 8033F39C 0033BF7C  80 04 00 D8 */	lwz r0, 0xd8(r4)
/* 8033F3A0 0033BF80  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033F3A4 0033BF84  B0 65 00 02 */	sth r3, 2(r5)
/* 8033F3A8 0033BF88  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/QG7Ms // 9100 (0%)
#pragma push
asm unk_t __GXSetSUTexSize()
{ // clang-format off
    nofralloc
/* 8033F3AC 0033BF8C  7C 08 02 A6 */	mflr r0
/* 8033F3B0 0033BF90  90 01 00 04 */	stw r0, 4(r1)
/* 8033F3B4 0033BF94  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8033F3B8 0033BF98  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 8033F3BC 0033BF9C  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F3C0 0033BFA0  80 03 04 DC */	lwz r0, 0x4dc(r3)
/* 8033F3C4 0033BFA4  28 00 00 FF */	cmplwi r0, 0xff
/* 8033F3C8 0033BFA8  41 82 01 3C */	beq lbl_8033F504
/* 8033F3CC 0033BFAC  80 03 02 04 */	lwz r0, 0x204(r3)
/* 8033F3D0 0033BFB0  3B C0 00 00 */	li r30, 0
/* 8033F3D4 0033BFB4  54 03 B7 3E */	rlwinm r3, r0, 0x16, 0x1c, 0x1f
/* 8033F3D8 0033BFB8  3B E3 00 01 */	addi r31, r3, 1
/* 8033F3DC 0033BFBC  54 1B 87 7E */	rlwinm r27, r0, 0x10, 0x1d, 0x1f
/* 8033F3E0 0033BFC0  48 00 00 A0 */	b lbl_8033F480
lbl_8033F3E4:
/* 8033F3E4 0033BFC4  2C 1E 00 02 */	cmpwi r30, 2
/* 8033F3E8 0033BFC8  41 82 00 4C */	beq lbl_8033F434
/* 8033F3EC 0033BFCC  40 80 00 14 */	bge lbl_8033F400
/* 8033F3F0 0033BFD0  2C 1E 00 00 */	cmpwi r30, 0
/* 8033F3F4 0033BFD4  41 82 00 18 */	beq lbl_8033F40C
/* 8033F3F8 0033BFD8  40 80 00 28 */	bge lbl_8033F420
/* 8033F3FC 0033BFDC  48 00 00 5C */	b lbl_8033F458
lbl_8033F400:
/* 8033F400 0033BFE0  2C 1E 00 04 */	cmpwi r30, 4
/* 8033F404 0033BFE4  40 80 00 54 */	bge lbl_8033F458
/* 8033F408 0033BFE8  48 00 00 40 */	b lbl_8033F448
lbl_8033F40C:
/* 8033F40C 0033BFEC  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F410 0033BFF0  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033F414 0033BFF4  54 1D 07 7E */	clrlwi r29, r0, 0x1d
/* 8033F418 0033BFF8  54 1C EF 7E */	rlwinm r28, r0, 0x1d, 0x1d, 0x1f
/* 8033F41C 0033BFFC  48 00 00 3C */	b lbl_8033F458
lbl_8033F420:
/* 8033F420 0033C000  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F424 0033C004  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033F428 0033C008  54 1D D7 7E */	rlwinm r29, r0, 0x1a, 0x1d, 0x1f
/* 8033F42C 0033C00C  54 1C BF 7E */	rlwinm r28, r0, 0x17, 0x1d, 0x1f
/* 8033F430 0033C010  48 00 00 28 */	b lbl_8033F458
lbl_8033F434:
/* 8033F434 0033C014  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F438 0033C018  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033F43C 0033C01C  54 1D A7 7E */	rlwinm r29, r0, 0x14, 0x1d, 0x1f
/* 8033F440 0033C020  54 1C 8F 7E */	rlwinm r28, r0, 0x11, 0x1d, 0x1f
/* 8033F444 0033C024  48 00 00 14 */	b lbl_8033F458
lbl_8033F448:
/* 8033F448 0033C028  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F44C 0033C02C  80 03 01 20 */	lwz r0, 0x120(r3)
/* 8033F450 0033C030  54 1D 77 7E */	rlwinm r29, r0, 0xe, 0x1d, 0x1f
/* 8033F454 0033C034  54 1C 5F 7E */	rlwinm r28, r0, 0xb, 0x1d, 0x1f
lbl_8033F458:
/* 8033F458 0033C038  80 6D A5 08 */	lwz r3, __GXContexts(r13)
/* 8033F45C 0033C03C  38 00 00 01 */	li r0, 1
/* 8033F460 0033C040  7C 00 E0 30 */	slw r0, r0, r28
/* 8033F464 0033C044  80 63 04 DC */	lwz r3, 0x4dc(r3)
/* 8033F468 0033C048  7C 60 00 39 */	and. r0, r3, r0
/* 8033F46C 0033C04C  40 82 00 10 */	bne lbl_8033F47C
/* 8033F470 0033C050  38 7D 00 00 */	addi r3, r29, 0
/* 8033F474 0033C054  38 9C 00 00 */	addi r4, r28, 0
/* 8033F478 0033C058  4B FF FE 69 */	bl __SetSURegs
lbl_8033F47C:
/* 8033F47C 0033C05C  3B DE 00 01 */	addi r30, r30, 1
lbl_8033F480:
/* 8033F480 0033C060  7C 1E D8 40 */	cmplw r30, r27
/* 8033F484 0033C064  41 80 FF 60 */	blt lbl_8033F3E4
/* 8033F488 0033C068  3B 60 00 00 */	li r27, 0
/* 8033F48C 0033C06C  3B DB 00 00 */	addi r30, r27, 0
/* 8033F490 0033C070  48 00 00 6C */	b lbl_8033F4FC
lbl_8033F494:
/* 8033F494 0033C074  80 AD A5 08 */	lwz r5, __GXContexts(r13)
/* 8033F498 0033C078  38 7E 04 9C */	addi r3, r30, 0x49c
/* 8033F49C 0033C07C  57 64 08 3A */	rlwinm r4, r27, 1, 0, 0x1d
/* 8033F4A0 0033C080  7C 65 18 2E */	lwzx r3, r5, r3
/* 8033F4A4 0033C084  57 60 07 FF */	clrlwi. r0, r27, 0x1f
/* 8033F4A8 0033C088  38 84 01 00 */	addi r4, r4, 0x100
/* 8033F4AC 0033C08C  7C 85 22 14 */	add r4, r5, r4
/* 8033F4B0 0033C090  54 7D 06 2C */	rlwinm r29, r3, 0, 0x18, 0x16
/* 8033F4B4 0033C094  41 82 00 10 */	beq lbl_8033F4C4
/* 8033F4B8 0033C098  80 04 00 00 */	lwz r0, 0(r4)
/* 8033F4BC 0033C09C  54 1C 8F 7E */	rlwinm r28, r0, 0x11, 0x1d, 0x1f
/* 8033F4C0 0033C0A0  48 00 00 0C */	b lbl_8033F4CC
lbl_8033F4C4:
/* 8033F4C4 0033C0A4  80 04 00 00 */	lwz r0, 0(r4)
/* 8033F4C8 0033C0A8  54 1C EF 7E */	rlwinm r28, r0, 0x1d, 0x1d, 0x1f
lbl_8033F4CC:
/* 8033F4CC 0033C0AC  28 1D 00 FF */	cmplwi r29, 0xff
/* 8033F4D0 0033C0B0  41 82 00 24 */	beq lbl_8033F4F4
/* 8033F4D4 0033C0B4  38 00 00 01 */	li r0, 1
/* 8033F4D8 0033C0B8  80 65 04 DC */	lwz r3, 0x4dc(r5)
/* 8033F4DC 0033C0BC  7C 00 E0 30 */	slw r0, r0, r28
/* 8033F4E0 0033C0C0  7C 60 00 39 */	and. r0, r3, r0
/* 8033F4E4 0033C0C4  40 82 00 10 */	bne lbl_8033F4F4
/* 8033F4E8 0033C0C8  38 7D 00 00 */	addi r3, r29, 0
/* 8033F4EC 0033C0CC  38 9C 00 00 */	addi r4, r28, 0
/* 8033F4F0 0033C0D0  4B FF FD F1 */	bl __SetSURegs
lbl_8033F4F4:
/* 8033F4F4 0033C0D4  3B DE 00 04 */	addi r30, r30, 4
/* 8033F4F8 0033C0D8  3B 7B 00 01 */	addi r27, r27, 1
lbl_8033F4FC:
/* 8033F4FC 0033C0DC  7C 1B F8 40 */	cmplw r27, r31
/* 8033F500 0033C0E0  41 80 FF 94 */	blt lbl_8033F494
lbl_8033F504:
/* 8033F504 0033C0E4  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8033F508 0033C0E8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8033F50C 0033C0EC  38 21 00 28 */	addi r1, r1, 0x28
/* 8033F510 0033C0F0  7C 08 03 A6 */	mtlr r0
/* 8033F514 0033C0F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

// https://decomp.me/scratch/QfxT4 // 3865 (73.16%)
#pragma push
asm unk_t __GXSetTmemConfig()
{ // clang-format off
    nofralloc
/* 8033F518 0033C0F8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033F51C 0033C0FC  2C 03 00 01 */	cmpwi r3, 1
/* 8033F520 0033C100  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033F524 0033C104  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033F528 0033C108  41 82 00 0C */	beq lbl_8033F534
/* 8033F52C 0033C10C  40 80 01 14 */	bge lbl_8033F640
/* 8033F530 0033C110  48 00 01 10 */	b lbl_8033F640
lbl_8033F534:
/* 8033F534 0033C114  38 00 00 61 */	li r0, 0x61
/* 8033F538 0033C118  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033F53C 0033C11C  3C 80 8C 0E */	lis r4, 0x8C0D8000@ha
/* 8033F540 0033C120  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 8033F544 0033C124  38 84 80 00 */	addi r4, r4, 0x8C0D8000@l
/* 8033F548 0033C128  90 83 80 00 */	stw r4, -0x8000(r3)
/* 8033F54C 0033C12C  3C 80 90 0E */	lis r4, 0x900DC000@ha
/* 8033F550 0033C130  3C E0 8D 0E */	lis r7, 0x8D0D8800@ha
/* 8033F554 0033C134  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F558 0033C138  38 84 C0 00 */	addi r4, r4, 0x900DC000@l
/* 8033F55C 0033C13C  3C C0 91 0E */	lis r6, 0x910DC800@ha
/* 8033F560 0033C140  90 83 80 00 */	stw r4, -0x8000(r3)
/* 8033F564 0033C144  3C A0 8E 0E */	lis r5, 0x8E0D9000@ha
/* 8033F568 0033C148  3C 80 92 0E */	lis r4, 0x920DD000@ha
/* 8033F56C 0033C14C  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F570 0033C150  38 E7 88 00 */	addi r7, r7, 0x8D0D8800@l
/* 8033F574 0033C154  3F C0 8F 0E */	lis r30, 0x8F0D9800@ha
/* 8033F578 0033C158  90 E3 80 00 */	stw r7, -0x8000(r3)
/* 8033F57C 0033C15C  3D 80 93 0E */	lis r12, 0x930DD800@ha
/* 8033F580 0033C160  3D 60 AC 0E */	lis r11, 0xAC0DA000@ha
/* 8033F584 0033C164  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F588 0033C168  38 C6 C8 00 */	addi r6, r6, 0x910DC800@l
/* 8033F58C 0033C16C  3D 40 B0 0E */	lis r10, 0xB00DE000@ha
/* 8033F590 0033C170  90 C3 80 00 */	stw r6, -0x8000(r3)
/* 8033F594 0033C174  3D 20 AD 0E */	lis r9, 0xAD0DA800@ha
/* 8033F598 0033C178  3D 00 B1 0E */	lis r8, 0xB10DE800@ha
/* 8033F59C 0033C17C  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F5A0 0033C180  38 A5 90 00 */	addi r5, r5, 0x8E0D9000@l
/* 8033F5A4 0033C184  3C E0 AE 0E */	lis r7, 0xAE0DB000@ha
/* 8033F5A8 0033C188  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 8033F5AC 0033C18C  3C C0 B2 0E */	lis r6, 0xB20DF000@ha
/* 8033F5B0 0033C190  3C A0 AF 0E */	lis r5, 0xAF0DB800@ha
/* 8033F5B4 0033C194  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F5B8 0033C198  3B E4 D0 00 */	addi r31, r4, 0x920DD000@l
/* 8033F5BC 0033C19C  3C 80 B3 0E */	lis r4, 0xB30DF800@ha
/* 8033F5C0 0033C1A0  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033F5C4 0033C1A4  3B DE 98 00 */	addi r30, r30, 0x8F0D9800@l
/* 8033F5C8 0033C1A8  39 8C D8 00 */	addi r12, r12, 0x930DD800@l
/* 8033F5CC 0033C1AC  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F5D0 0033C1B0  39 6B A0 00 */	addi r11, r11, 0xAC0DA000@l
/* 8033F5D4 0033C1B4  39 4A E0 00 */	addi r10, r10, 0xB00DE000@l
/* 8033F5D8 0033C1B8  93 C3 80 00 */	stw r30, -0x8000(r3)
/* 8033F5DC 0033C1BC  39 29 A8 00 */	addi r9, r9, 0xAD0DA800@l
/* 8033F5E0 0033C1C0  39 08 E8 00 */	addi r8, r8, 0xB10DE800@l
/* 8033F5E4 0033C1C4  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F5E8 0033C1C8  38 E7 B0 00 */	addi r7, r7, 0xAE0DB000@l
/* 8033F5EC 0033C1CC  38 C6 F0 00 */	addi r6, r6, 0xB20DF000@l
/* 8033F5F0 0033C1D0  91 83 80 00 */	stw r12, -0x8000(r3)
/* 8033F5F4 0033C1D4  38 A5 B8 00 */	addi r5, r5, 0xAF0DB800@l
/* 8033F5F8 0033C1D8  38 84 F8 00 */	addi r4, r4, 0xB30DF800@l
/* 8033F5FC 0033C1DC  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F600 0033C1E0  91 63 80 00 */	stw r11, -0x8000(r3)
/* 8033F604 0033C1E4  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F608 0033C1E8  91 43 80 00 */	stw r10, -0x8000(r3)
/* 8033F60C 0033C1EC  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F610 0033C1F0  91 23 80 00 */	stw r9, -0x8000(r3)
/* 8033F614 0033C1F4  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F618 0033C1F8  91 03 80 00 */	stw r8, -0x8000(r3)
/* 8033F61C 0033C1FC  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F620 0033C200  90 E3 80 00 */	stw r7, -0x8000(r3)
/* 8033F624 0033C204  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F628 0033C208  90 C3 80 00 */	stw r6, -0x8000(r3)
/* 8033F62C 0033C20C  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F630 0033C210  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 8033F634 0033C214  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F638 0033C218  90 83 80 00 */	stw r4, -0x8000(r3)
/* 8033F63C 0033C21C  48 00 01 0C */	b lbl_8033F748
lbl_8033F640:
/* 8033F640 0033C220  38 00 00 61 */	li r0, 0x61
/* 8033F644 0033C224  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033F648 0033C228  3C 80 8C 0E */	lis r4, 0x8C0D8000@ha
/* 8033F64C 0033C22C  98 03 80 00 */	stb r0, 0xCC008000@l(r3)
/* 8033F650 0033C230  38 84 80 00 */	addi r4, r4, 0x8C0D8000@l
/* 8033F654 0033C234  90 83 80 00 */	stw r4, -0x8000(r3)
/* 8033F658 0033C238  3C 80 90 0E */	lis r4, 0x900DC000@ha
/* 8033F65C 0033C23C  3C E0 8D 0E */	lis r7, 0x8D0D8400@ha
/* 8033F660 0033C240  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F664 0033C244  38 84 C0 00 */	addi r4, r4, 0x900DC000@l
/* 8033F668 0033C248  3C C0 91 0E */	lis r6, 0x910DC400@ha
/* 8033F66C 0033C24C  90 83 80 00 */	stw r4, -0x8000(r3)
/* 8033F670 0033C250  3C A0 8E 0E */	lis r5, 0x8E0D8800@ha
/* 8033F674 0033C254  3C 80 92 0E */	lis r4, 0x920DC800@ha
/* 8033F678 0033C258  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F67C 0033C25C  38 E7 84 00 */	addi r7, r7, 0x8D0D8400@l
/* 8033F680 0033C260  3F E0 8F 0E */	lis r31, 0x8F0D8C00@ha
/* 8033F684 0033C264  90 E3 80 00 */	stw r7, -0x8000(r3)
/* 8033F688 0033C268  3D 80 93 0E */	lis r12, 0x930DCC00@ha
/* 8033F68C 0033C26C  3D 60 AC 0E */	lis r11, 0xAC0D9000@ha
/* 8033F690 0033C270  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F694 0033C274  38 C6 C4 00 */	addi r6, r6, 0x910DC400@l
/* 8033F698 0033C278  3D 40 B0 0E */	lis r10, 0xB00DD000@ha
/* 8033F69C 0033C27C  90 C3 80 00 */	stw r6, -0x8000(r3)
/* 8033F6A0 0033C280  3D 20 AD 0E */	lis r9, 0xAD0D9400@ha
/* 8033F6A4 0033C284  3D 00 B1 0E */	lis r8, 0xB10DD400@ha
/* 8033F6A8 0033C288  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F6AC 0033C28C  38 A5 88 00 */	addi r5, r5, 0x8E0D8800@l
/* 8033F6B0 0033C290  3C E0 AE 0E */	lis r7, 0xAE0D9800@ha
/* 8033F6B4 0033C294  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 8033F6B8 0033C298  3C C0 B2 0E */	lis r6, 0xB20DD800@ha
/* 8033F6BC 0033C29C  3C A0 AF 0E */	lis r5, 0xAF0D9C00@ha
/* 8033F6C0 0033C2A0  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F6C4 0033C2A4  3B C4 C8 00 */	addi r30, r4, 0x920DC800@l
/* 8033F6C8 0033C2A8  3C 80 B3 0E */	lis r4, 0xB30DDC00@ha
/* 8033F6CC 0033C2AC  93 C3 80 00 */	stw r30, -0x8000(r3)
/* 8033F6D0 0033C2B0  3B FF 8C 00 */	addi r31, r31, 0x8F0D8C00@l
/* 8033F6D4 0033C2B4  39 8C CC 00 */	addi r12, r12, 0x930DCC00@l
/* 8033F6D8 0033C2B8  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F6DC 0033C2BC  39 6B 90 00 */	addi r11, r11, 0xAC0D9000@l
/* 8033F6E0 0033C2C0  39 4A D0 00 */	addi r10, r10, 0xB00DD000@l
/* 8033F6E4 0033C2C4  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033F6E8 0033C2C8  39 29 94 00 */	addi r9, r9, 0xAD0D9400@l
/* 8033F6EC 0033C2CC  39 08 D4 00 */	addi r8, r8, 0xB10DD400@l
/* 8033F6F0 0033C2D0  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F6F4 0033C2D4  38 E7 98 00 */	addi r7, r7, 0xAE0D9800@l
/* 8033F6F8 0033C2D8  38 C6 D8 00 */	addi r6, r6, 0xB20DD800@l
/* 8033F6FC 0033C2DC  91 83 80 00 */	stw r12, -0x8000(r3)
/* 8033F700 0033C2E0  38 A5 9C 00 */	addi r5, r5, 0xAF0D9C00@l
/* 8033F704 0033C2E4  38 84 DC 00 */	addi r4, r4, 0xB30DDC00@l
/* 8033F708 0033C2E8  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F70C 0033C2EC  91 63 80 00 */	stw r11, -0x8000(r3)
/* 8033F710 0033C2F0  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F714 0033C2F4  91 43 80 00 */	stw r10, -0x8000(r3)
/* 8033F718 0033C2F8  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F71C 0033C2FC  91 23 80 00 */	stw r9, -0x8000(r3)
/* 8033F720 0033C300  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F724 0033C304  91 03 80 00 */	stw r8, -0x8000(r3)
/* 8033F728 0033C308  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F72C 0033C30C  90 E3 80 00 */	stw r7, -0x8000(r3)
/* 8033F730 0033C310  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F734 0033C314  90 C3 80 00 */	stw r6, -0x8000(r3)
/* 8033F738 0033C318  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F73C 0033C31C  90 A3 80 00 */	stw r5, -0x8000(r3)
/* 8033F740 0033C320  98 03 80 00 */	stb r0, -0x8000(r3)
/* 8033F744 0033C324  90 83 80 00 */	stw r4, -0x8000(r3)
lbl_8033F748:
/* 8033F748 0033C328  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033F74C 0033C32C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033F750 0033C330  38 21 00 18 */	addi r1, r1, 0x18
/* 8033F754 0033C334  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
