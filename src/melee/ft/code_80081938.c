#include <melee/ft/code_80081938.h>

#include <melee/ft/ft_unknown_006.h>
#include <melee/it/item.h>
#include <melee/it/item2.h>
#include <melee/lb/lbunknown_003.h>
#include <placeholder.h>
#include <sysdolphin/baselib/gobj.h>

#ifdef MWERKS_GEKKO

static f32 const lbl_804D83A0 = -1.0F;
static f32 const lbl_804D83A4 = 1.0F;

#pragma push
asm void func_80081938(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 80081938 0007E518  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 8008193C 0007E51C  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80081940 0007E520  80 65 06 F4 */	lwz r3, 0x6f4(r5)
/* 80081944 0007E524  80 05 06 F8 */	lwz r0, 0x6f8(r5)
/* 80081948 0007E528  90 61 00 44 */	stw r3, 0x44(r1)
/* 8008194C 0007E52C  90 01 00 48 */	stw r0, 0x48(r1)
/* 80081950 0007E530  80 05 06 FC */	lwz r0, 0x6fc(r5)
/* 80081954 0007E534  90 01 00 4C */	stw r0, 0x4c(r1)
/* 80081958 0007E538  C0 25 07 AC */	lfs f1, 0x7ac(r5)
/* 8008195C 0007E53C  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 80081960 0007E540  C0 45 07 A4 */	lfs f2, 0x7a4(r5)
/* 80081964 0007E544  EC 01 00 2A */	fadds f0, f1, f0
/* 80081968 0007E548  D0 05 19 3C */	stfs f0, 0x193c(r5)
/* 8008196C 0007E54C  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 80081970 0007E550  EC 02 00 2A */	fadds f0, f2, f0
/* 80081974 0007E554  D0 05 19 40 */	stfs f0, 0x1940(r5)
/* 80081978 0007E558  C0 25 00 B4 */	lfs f1, 0xb4(r5)
/* 8008197C 0007E55C  C0 05 02 8C */	lfs f0, 0x28c(r5)
/* 80081980 0007E560  EC 01 00 2A */	fadds f0, f1, f0
/* 80081984 0007E564  D0 05 19 44 */	stfs f0, 0x1944(r5)
/* 80081988 0007E568  80 65 19 3C */	lwz r3, 0x193c(r5)
/* 8008198C 0007E56C  80 05 19 40 */	lwz r0, 0x1940(r5)
/* 80081990 0007E570  90 65 19 30 */	stw r3, 0x1930(r5)
/* 80081994 0007E574  90 05 19 34 */	stw r0, 0x1934(r5)
/* 80081998 0007E578  80 05 19 44 */	lwz r0, 0x1944(r5)
/* 8008199C 0007E57C  90 05 19 38 */	stw r0, 0x1938(r5)
/* 800819A0 0007E580  38 21 00 78 */	addi r1, r1, 0x78
/* 800819A4 0007E584  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_80081938(HSD_GObj* fighter_gobj)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void func_800819A8(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 800819A8 0007E588  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 800819AC 0007E58C  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800819B0 0007E590  80 65 06 F4 */	lwz r3, 0x6f4(r5)
/* 800819B4 0007E594  80 05 06 F8 */	lwz r0, 0x6f8(r5)
/* 800819B8 0007E598  90 61 00 44 */	stw r3, 0x44(r1)
/* 800819BC 0007E59C  90 01 00 48 */	stw r0, 0x48(r1)
/* 800819C0 0007E5A0  80 05 06 FC */	lwz r0, 0x6fc(r5)
/* 800819C4 0007E5A4  90 01 00 4C */	stw r0, 0x4c(r1)
/* 800819C8 0007E5A8  C0 25 07 AC */	lfs f1, 0x7ac(r5)
/* 800819CC 0007E5AC  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 800819D0 0007E5B0  C0 45 07 A4 */	lfs f2, 0x7a4(r5)
/* 800819D4 0007E5B4  EC 01 00 2A */	fadds f0, f1, f0
/* 800819D8 0007E5B8  D0 05 19 30 */	stfs f0, 0x1930(r5)
/* 800819DC 0007E5BC  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 800819E0 0007E5C0  EC 02 00 2A */	fadds f0, f2, f0
/* 800819E4 0007E5C4  D0 05 19 34 */	stfs f0, 0x1934(r5)
/* 800819E8 0007E5C8  C0 25 00 B4 */	lfs f1, 0xb4(r5)
/* 800819EC 0007E5CC  C0 05 02 8C */	lfs f0, 0x28c(r5)
/* 800819F0 0007E5D0  EC 01 00 2A */	fadds f0, f1, f0
/* 800819F4 0007E5D4  D0 05 19 38 */	stfs f0, 0x1938(r5)
/* 800819F8 0007E5D8  38 21 00 78 */	addi r1, r1, 0x78
/* 800819FC 0007E5DC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_800819A8(HSD_GObj* fighter_gobj)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void func_80081A00(void)
{ // clang-format off
    nofralloc
/* 80081A00 0007E5E0  7C 08 02 A6 */	mflr r0
/* 80081A04 0007E5E4  90 01 00 04 */	stw r0, 4(r1)
/* 80081A08 0007E5E8  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 80081A0C 0007E5EC  BF 61 00 9C */	stmw r27, 0x9c(r1)
/* 80081A10 0007E5F0  7C 7E 1B 78 */	mr r30, r3
/* 80081A14 0007E5F4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80081A18 0007E5F8  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 80081A1C 0007E5FC  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80081A20 0007E600  40 82 01 00 */	bne lbl_80081B20
/* 80081A24 0007E604  88 7F 22 23 */	lbz r3, 0x2223(r31)
/* 80081A28 0007E608  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 80081A2C 0007E60C  40 82 00 F4 */	bne lbl_80081B20
/* 80081A30 0007E610  38 00 00 01 */	li r0, 1
/* 80081A34 0007E614  50 03 17 7A */	rlwimi r3, r0, 2, 0x1d, 0x1d
/* 80081A38 0007E618  98 7F 22 23 */	stb r3, 0x2223(r31)
/* 80081A3C 0007E61C  80 7F 06 F4 */	lwz r3, 0x6f4(r31)
/* 80081A40 0007E620  80 1F 06 F8 */	lwz r0, 0x6f8(r31)
/* 80081A44 0007E624  90 61 00 64 */	stw r3, 0x64(r1)
/* 80081A48 0007E628  90 01 00 68 */	stw r0, 0x68(r1)
/* 80081A4C 0007E62C  80 1F 06 FC */	lwz r0, 0x6fc(r31)
/* 80081A50 0007E630  90 01 00 6C */	stw r0, 0x6c(r1)
/* 80081A54 0007E634  C0 3F 07 AC */	lfs f1, 0x7ac(r31)
/* 80081A58 0007E638  C0 01 00 64 */	lfs f0, 0x64(r1)
/* 80081A5C 0007E63C  C0 5F 07 A4 */	lfs f2, 0x7a4(r31)
/* 80081A60 0007E640  EC 01 00 2A */	fadds f0, f1, f0
/* 80081A64 0007E644  D0 1F 19 3C */	stfs f0, 0x193c(r31)
/* 80081A68 0007E648  C0 01 00 64 */	lfs f0, 0x64(r1)
/* 80081A6C 0007E64C  EC 02 00 2A */	fadds f0, f2, f0
/* 80081A70 0007E650  D0 1F 19 40 */	stfs f0, 0x1940(r31)
/* 80081A74 0007E654  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 80081A78 0007E658  C0 1F 02 8C */	lfs f0, 0x28c(r31)
/* 80081A7C 0007E65C  EC 01 00 2A */	fadds f0, f1, f0
/* 80081A80 0007E660  D0 1F 19 44 */	stfs f0, 0x1944(r31)
/* 80081A84 0007E664  80 6D C1 8C */	lwz r3, lbl_804D782C(r13)
/* 80081A88 0007E668  83 7E 00 2C */	lwz r27, 0x2c(r30)
/* 80081A8C 0007E66C  83 83 00 24 */	lwz r28, 0x24(r3)
/* 80081A90 0007E670  48 00 00 64 */	b lbl_80081AF4
lbl_80081A94:
/* 80081A94 0007E674  7F 83 E3 78 */	mr r3, r28
/* 80081A98 0007E678  48 1E A1 D1 */	bl func_8026BC68
/* 80081A9C 0007E67C  2C 03 00 00 */	cmpwi r3, 0
/* 80081AA0 0007E680  41 82 00 50 */	beq lbl_80081AF0
/* 80081AA4 0007E684  83 BC 00 2C */	lwz r29, 0x2c(r28)
/* 80081AA8 0007E688  38 7B 19 30 */	addi r3, r27, 0x1930
/* 80081AAC 0007E68C  38 9D 0B 54 */	addi r4, r29, 0xb54
/* 80081AB0 0007E690  4B F9 2B 89 */	bl func_80014638
/* 80081AB4 0007E694  2C 03 00 00 */	cmpwi r3, 0
/* 80081AB8 0007E698  41 82 00 38 */	beq lbl_80081AF0
/* 80081ABC 0007E69C  C0 3D 00 4C */	lfs f1, 0x4c(r29)
/* 80081AC0 0007E6A0  C0 1B 00 B0 */	lfs f0, 0xb0(r27)
/* 80081AC4 0007E6A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80081AC8 0007E6A8  40 81 00 0C */	ble lbl_80081AD4
/* 80081ACC 0007E6AC  C0 02 89 C0 */	lfs f0, lbl_804D83A0(r2)
/* 80081AD0 0007E6B0  48 00 00 08 */	b lbl_80081AD8
lbl_80081AD4:
/* 80081AD4 0007E6B4  C0 02 89 C4 */	lfs f0, lbl_804D83A4(r2)
lbl_80081AD8:
/* 80081AD8 0007E6B8  D0 1D 0C D0 */	stfs f0, 0xcd0(r29)
/* 80081ADC 0007E6BC  38 00 00 01 */	li r0, 1
/* 80081AE0 0007E6C0  93 DD 0C FC */	stw r30, 0xcfc(r29)
/* 80081AE4 0007E6C4  88 7B 00 0C */	lbz r3, 0xc(r27)
/* 80081AE8 0007E6C8  90 7D 0C B0 */	stw r3, 0xcb0(r29)
/* 80081AEC 0007E6CC  90 1B 19 50 */	stw r0, 0x1950(r27)
lbl_80081AF0:
/* 80081AF0 0007E6D0  83 9C 00 08 */	lwz r28, 8(r28)
lbl_80081AF4:
/* 80081AF4 0007E6D4  28 1C 00 00 */	cmplwi r28, 0
/* 80081AF8 0007E6D8  40 82 FF 9C */	bne lbl_80081A94
/* 80081AFC 0007E6DC  80 1F 19 50 */	lwz r0, 0x1950(r31)
/* 80081B00 0007E6E0  2C 00 00 00 */	cmpwi r0, 0
/* 80081B04 0007E6E4  41 82 00 1C */	beq lbl_80081B20
/* 80081B08 0007E6E8  7F C3 F3 78 */	mr r3, r30
/* 80081B0C 0007E6EC  48 04 55 31 */	bl func_800C703C
/* 80081B10 0007E6F0  38 00 00 00 */	li r0, 0
/* 80081B14 0007E6F4  90 1F 19 50 */	stw r0, 0x1950(r31)
/* 80081B18 0007E6F8  38 60 00 01 */	li r3, 1
/* 80081B1C 0007E6FC  48 00 00 08 */	b lbl_80081B24
lbl_80081B20:
/* 80081B20 0007E700  38 60 00 00 */	li r3, 0
lbl_80081B24:
/* 80081B24 0007E704  BB 61 00 9C */	lmw r27, 0x9c(r1)
/* 80081B28 0007E708  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 80081B2C 0007E70C  38 21 00 B0 */	addi r1, r1, 0xb0
/* 80081B30 0007E710  7C 08 03 A6 */	mtlr r0
/* 80081B34 0007E714  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void func_80081A00(void)
{
    NOT_IMPLEMENTED;
}

#endif
