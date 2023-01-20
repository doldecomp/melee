
#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <dolphin/os/os.h>
#include <math.h>
#include <melee/ef/efsync.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/stage.h>
#include <melee/it/code_80266F3C.h>
#include <melee/it/item.h>
#include <melee/lb/forward.h>
#include <melee/pl/pl_unknown_001.h>
#include <melee/pl/player.h>
#include <MSL/trigf.h>
#include <Runtime/platform.h>
#include <Runtime/runtime.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/random.h>

f32 const lbl_804D82E0 = 0.0F;
f32 const lbl_804D82E4 = 500.0F;
f32 const lbl_804D82E8 = 0.5F;
f32 const lbl_804D82EC = 1.0F;
f32 const lbl_804D82F0 = -1.0F;
f64 const lbl_804D82F8 = 4503601774854144.0;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID)
{ // clang-format off
    nofralloc
/* 800763C0 00072FA0  7C 03 20 40 */	cmplw r3, r4
/* 800763C4 00072FA4  4D 82 00 20 */	beqlr
/* 800763C8 00072FA8  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 800763CC 00072FAC  80 06 20 94 */	lwz r0, 0x2094(r6)
/* 800763D0 00072FB0  28 00 00 00 */	cmplwi r0, 0
/* 800763D4 00072FB4  40 82 00 18 */	bne lbl_800763EC
/* 800763D8 00072FB8  90 A6 20 8C */	stw r5, 0x208c(r6)
/* 800763DC 00072FBC  38 00 00 01 */	li r0, 1
/* 800763E0 00072FC0  B0 06 20 90 */	sth r0, 0x2090(r6)
/* 800763E4 00072FC4  90 86 20 94 */	stw r4, 0x2094(r6)
/* 800763E8 00072FC8  4E 80 00 20 */	blr
lbl_800763EC:
/* 800763EC 00072FCC  7C 00 20 40 */	cmplw r0, r4
/* 800763F0 00072FD0  4C 82 00 20 */	bnelr
/* 800763F4 00072FD4  2C 05 00 01 */	cmpwi r5, 1
/* 800763F8 00072FD8  41 82 00 3C */	beq lbl_80076434
/* 800763FC 00072FDC  80 06 20 8C */	lwz r0, 0x208c(r6)
/* 80076400 00072FE0  7C 00 28 00 */	cmpw r0, r5
/* 80076404 00072FE4  40 82 00 30 */	bne lbl_80076434
/* 80076408 00072FE8  A0 66 20 90 */	lhz r3, 0x2090(r6)
/* 8007640C 00072FEC  38 03 00 01 */	addi r0, r3, 1
/* 80076410 00072FF0  B0 06 20 90 */	sth r0, 0x2090(r6)
/* 80076414 00072FF4  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80076418 00072FF8  A0 66 20 90 */	lhz r3, 0x2090(r6)
/* 8007641C 00072FFC  80 04 04 C4 */	lwz r0, 0x4c4(r4)
/* 80076420 00073000  7C 03 00 00 */	cmpw r3, r0
/* 80076424 00073004  4D 80 00 20 */	bltlr
/* 80076428 00073008  80 04 04 D8 */	lwz r0, 0x4d8(r4)
/* 8007642C 0007300C  B0 06 20 92 */	sth r0, 0x2092(r6)
/* 80076430 00073010  4E 80 00 20 */	blr
lbl_80076434:
/* 80076434 00073014  38 00 00 00 */	li r0, 0
/* 80076438 00073018  B0 06 20 90 */	sth r0, 0x2090(r6)
/* 8007643C 0007301C  90 A6 20 8C */	stw r5, 0x208c(r6)
/* 80076440 00073020  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076444(HSD_GObj* attacker, HSD_GObj* victim)
{ // clang-format off
    nofralloc
/* 80076444 00073024  7C 08 02 A6 */	mflr r0
/* 80076448 00073028  90 01 00 04 */	stw r0, 4(r1)
/* 8007644C 0007302C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80076450 00073030  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 80076454 00073034  80 A5 20 68 */	lwz r5, 0x2068(r5)
/* 80076458 00073038  4B FF FF 69 */	bl func_800763C0
/* 8007645C 0007303C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80076460 00073040  38 21 00 08 */	addi r1, r1, 8
/* 80076464 00073044  7C 08 03 A6 */	mtlr r0
/* 80076468 00073048  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim)
{ // clang-format off
    nofralloc
/* 8007646C 0007304C  7C 08 02 A6 */	mflr r0
/* 80076470 00073050  90 01 00 04 */	stw r0, 4(r1)
/* 80076474 00073054  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80076478 00073058  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8007647C 0007305C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80076480 00073060  3B C3 00 00 */	addi r30, r3, 0
/* 80076484 00073064  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80076488 00073068  3B A4 00 00 */	addi r29, r4, 0
/* 8007648C 0007306C  48 1F 57 ED */	bl func_8026BC78
/* 80076490 00073070  3B E3 00 00 */	addi r31, r3, 0
/* 80076494 00073074  38 7E 00 00 */	addi r3, r30, 0
/* 80076498 00073078  48 1F 57 ED */	bl func_8026BC84
/* 8007649C 0007307C  3B C3 00 00 */	addi r30, r3, 0
/* 800764A0 00073080  38 7F 00 00 */	addi r3, r31, 0
/* 800764A4 00073084  48 01 04 BD */	bl func_80086960
/* 800764A8 00073088  2C 03 00 00 */	cmpwi r3, 0
/* 800764AC 0007308C  41 82 00 14 */	beq lbl_800764C0
/* 800764B0 00073090  38 7F 00 00 */	addi r3, r31, 0
/* 800764B4 00073094  38 9D 00 00 */	addi r4, r29, 0
/* 800764B8 00073098  38 BE 00 00 */	addi r5, r30, 0
/* 800764BC 0007309C  4B FF FF 05 */	bl func_800763C0
lbl_800764C0:
/* 800764C0 000730A0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800764C4 000730A4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800764C8 000730A8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800764CC 000730AC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800764D0 000730B0  38 21 00 20 */	addi r1, r1, 0x20
/* 800764D4 000730B4  7C 08 03 A6 */	mtlr r0
/* 800764D8 000730B8  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800764DC(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 800764DC 000730BC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800764E0 000730C0  A0 64 20 98 */	lhz r3, 0x2098(r4)
/* 800764E4 000730C4  28 03 00 00 */	cmplwi r3, 0
/* 800764E8 000730C8  41 82 00 0C */	beq lbl_800764F4
/* 800764EC 000730CC  38 03 FF FF */	addi r0, r3, -1
/* 800764F0 000730D0  B0 04 20 98 */	sth r0, 0x2098(r4)
lbl_800764F4:
/* 800764F4 000730D4  80 64 20 94 */	lwz r3, 0x2094(r4)
/* 800764F8 000730D8  28 03 00 00 */	cmplwi r3, 0
/* 800764FC 000730DC  4D 82 00 20 */	beqlr
/* 80076500 000730E0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80076504 000730E4  88 03 22 1C */	lbz r0, 0x221c(r3)
/* 80076508 000730E8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8007650C 000730EC  4C 82 00 20 */	bnelr
/* 80076510 000730F0  A0 03 20 98 */	lhz r0, 0x2098(r3)
/* 80076514 000730F4  28 00 00 00 */	cmplwi r0, 0
/* 80076518 000730F8  4C 82 00 20 */	bnelr
/* 8007651C 000730FC  38 00 00 00 */	li r0, 0
/* 80076520 00073100  90 04 20 94 */	stw r0, 0x2094(r4)
/* 80076524 00073104  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076528(HSD_GObj*)
{
    // clang-format off
    nofralloc
/* 80076528 00073108  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8007652C 0007310C  A0 65 20 92 */	lhz r3, 0x2092(r5)
/* 80076530 00073110  28 03 00 00 */	cmplwi r3, 0
/* 80076534 00073114  4D 82 00 20 */	beqlr
/* 80076538 00073118  38 03 FF FF */	addi r0, r3, -1
/* 8007653C 0007311C  B0 05 20 92 */	sth r0, 0x2092(r5)
/* 80076540 00073120  80 05 1A 58 */	lwz r0, 0x1a58(r5)
/* 80076544 00073124  28 00 00 00 */	cmplwi r0, 0
/* 80076548 00073128  4C 82 00 20 */	bnelr
/* 8007654C 0007312C  80 05 00 E0 */	lwz r0, 0xe0(r5)
/* 80076550 00073130  2C 00 00 00 */	cmpwi r0, 0
/* 80076554 00073134  4C 82 00 20 */	bnelr
/* 80076558 00073138  80 CD AE B4 */	lwz r6, p_ftCommonData
/* 8007655C 0007313C  38 85 08 44 */	addi r4, r5, 0x844
/* 80076560 00073140  A0 65 20 90 */	lhz r3, 0x2090(r5)
/* 80076564 00073144  80 06 04 C8 */	lwz r0, 0x4c8(r6)
/* 80076568 00073148  7C 03 00 00 */	cmpw r3, r0
/* 8007656C 0007314C  40 80 00 0C */	bge lbl_80076578
/* 80076570 00073150  C0 46 04 D0 */	lfs f2, 0x4d0(r6)
/* 80076574 00073154  48 00 00 08 */	b lbl_8007657C
lbl_80076578:
/* 80076578 00073158  C0 46 04 D4 */	lfs f2, 0x4d4(r6)
lbl_8007657C:
/* 8007657C 0007315C  C0 05 00 2C */	lfs f0, 0x2c(r5)
/* 80076580 00073160  C0 24 00 04 */	lfs f1, 4(r4)
/* 80076584 00073164  EC 40 00 B2 */	fmuls f2, f0, f2
/* 80076588 00073168  C0 05 00 B0 */	lfs f0, 0xb0(r5)
/* 8007658C 0007316C  EC 01 00 BC */	fnmsubs f0, f1, f2, f0
/* 80076590 00073170  D0 05 00 B0 */	stfs f0, 0xb0(r5)
/* 80076594 00073174  C0 24 00 00 */	lfs f1, 0(r4)
/* 80076598 00073178  C0 05 00 B4 */	lfs f0, 0xb4(r5)
/* 8007659C 0007317C  FC 20 08 50 */	fneg f1, f1
/* 800765A0 00073180  EC 01 00 BC */	fnmsubs f0, f1, f2, f0
/* 800765A4 00073184  D0 05 00 B4 */	stfs f0, 0xb4(r5)
/* 800765A8 00073188  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800765AC(HSD_GObj*)
{
    // clang-format off
    nofralloc
/* 800765AC 0007318C  80 8D C1 8C */	lwz r4, lbl_804D782C
/* 800765B0 00073190  38 00 00 00 */	li r0, 0
/* 800765B4 00073194  80 C4 00 20 */	lwz r6, 0x20(r4)
/* 800765B8 00073198  48 00 00 1C */	b lbl_800765D4
lbl_800765BC:
/* 800765BC 0007319C  80 A6 00 2C */	lwz r5, 0x2c(r6)
/* 800765C0 000731A0  80 85 20 94 */	lwz r4, 0x2094(r5)
/* 800765C4 000731A4  7C 03 20 40 */	cmplw r3, r4
/* 800765C8 000731A8  40 82 00 08 */	bne lbl_800765D0
/* 800765CC 000731AC  90 05 20 94 */	stw r0, 0x2094(r5)
lbl_800765D0:
/* 800765D0 000731B0  80 C6 00 08 */	lwz r6, 8(r6)
lbl_800765D4:
/* 800765D4 000731B4  28 06 00 00 */	cmplwi r6, 0
/* 800765D8 000731B8  40 82 FF E4 */	bne lbl_800765BC
/* 800765DC 000731BC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_804D6558;
extern unk_t lbl_804D655C;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800765E0(void)
{ // clang-format off
    nofralloc
/* 800765E0 000731C0  38 00 00 00 */	li r0, 0
/* 800765E4 000731C4  90 0D AE B8 */	stw r0, lbl_804D6558
/* 800765E8 000731C8  90 0D AE BC */	stw r0, lbl_804D655C
/* 800765EC 000731CC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 unk_floatvar)
{ // clang-format off
    nofralloc
/* 800765F0 000731D0  80 A3 1A 58 */	lwz r5, 0x1a58(r3)
/* 800765F4 000731D4  28 05 00 00 */	cmplwi r5, 0
/* 800765F8 000731D8  41 82 00 24 */	beq lbl_8007661C
/* 800765FC 000731DC  88 03 22 1B */	lbz r0, 0x221b(r3)
/* 80076600 000731E0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80076604 000731E4  40 82 00 18 */	bne lbl_8007661C
/* 80076608 000731E8  7C 05 20 40 */	cmplw r5, r4
/* 8007660C 000731EC  41 82 00 10 */	beq lbl_8007661C
/* 80076610 000731F0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80076614 000731F4  C0 04 01 28 */	lfs f0, 0x128(r4)
/* 80076618 000731F8  EC 21 00 32 */	fmuls f1, f1, f0
lbl_8007661C:
/* 8007661C 000731FC  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80076620 00073200  2C 00 01 45 */	cmpwi r0, 0x145
/* 80076624 00073204  40 82 00 10 */	bne lbl_80076634
/* 80076628 00073208  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8007662C 0007320C  C0 04 07 14 */	lfs f0, 0x714(r4)
/* 80076630 00073210  EC 21 00 32 */	fmuls f1, f1, f0
lbl_80076634:
/* 80076634 00073214  C0 03 18 2C */	lfs f0, 0x182c(r3)
/* 80076638 00073218  EC 21 00 32 */	fmuls f1, f1, f0
/* 8007663C 0007321C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
