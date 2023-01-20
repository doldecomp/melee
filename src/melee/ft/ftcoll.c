
#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>

#include <common_structs.h>
#include <dolphin/os/os.h>
#include <math.h>
#include <melee/ef/efsync.h>
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

/// Combo Count Logic
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID)
{
    HSD_GObj* temp_GObj;
    Fighter* fp;

    if (attacker != victim) {
        fp = GET_FIGHTER(attacker);
        temp_GObj = fp->x2094;
        if (temp_GObj == NULL) {
            fp->x208C = attackID;
            fp->x2090 = 1U;
            fp->x2094 = victim;
            return;
        }
        if (temp_GObj == victim) {
            if ((attackID != 1) && ((s32) fp->x208C == attackID)) {
                fp->x2090 = (u16) (fp->x2090 + 1);
                if (fp->x2090 >= p_ftCommonData->x4C4) {
                    fp->x2092 = p_ftCommonData->x4D8;
                }
            } else {
                fp->x2090 = 0U;
                fp->x208C = attackID;
            }
        }
    }
}

/// Combo Count Logic + Get Attack ID
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim)
{
    Fighter* fp = GET_FIGHTER(attacker);
    func_800763C0(attacker, victim, fp->x2068_attackID);
}

/// Combo Count Logic w/ Item Owner
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim)
{
    HSD_GObj* owner = func_8026BC78(attackItem);
    enum_t asid = func_8026BC84(attackItem);

    if (func_80086960(owner))
        func_800763C0(owner, victim, asid);
}

/// Check to end combo for victim
void func_800764DC(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER adds an instruction
    Fighter* fp1 = gobj->user_data;

    if (fp1->x2098 != 0)
        fp1->x2098--;

    if (fp1->x2094 != NULL) {
        Fighter* fp2 = fp1->x2094->user_data;

        if (!fp2->x221C_flag.bits.b6 && fp2->x2098 == 0)
            fp1->x2094 = NULL;
    }
}

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

extern f32 const lbl_804D82E0;
extern f32 const lbl_804D82E4;
extern char* const lbl_803C0C58;
extern char* const lbl_803C0C74;
extern char* const lbl_804D3A68;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076640(void)
{ // clang-format off
    nofralloc
/* 80076640 00073220  7C 08 02 A6 */	mflr r0
/* 80076644 00073224  90 01 00 04 */	stw r0, 4(r1)
/* 80076648 00073228  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8007664C 0007322C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80076650 00073230  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80076654 00073234  7C 9E 23 78 */	mr r30, r4
/* 80076658 00073238  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8007665C 0007323C  7C 7D 1B 78 */	mr r29, r3
/* 80076660 00073240  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076664 00073244  C0 24 00 00 */	lfs f1, 0(r4)
/* 80076668 00073248  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8007666C 0007324C  41 82 00 2C */	beq lbl_80076698
/* 80076670 00073250  FC 00 08 1E */	fctiwz f0, f1
/* 80076674 00073254  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80076678 00073258  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007667C 0007325C  2C 00 00 00 */	cmpwi r0, 0
/* 80076680 00073260  41 82 00 10 */	beq lbl_80076690
/* 80076684 00073264  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80076688 00073268  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8007668C 0007326C  48 00 00 10 */	b lbl_8007669C
lbl_80076690:
/* 80076690 00073270  3B E0 00 01 */	li r31, 1
/* 80076694 00073274  48 00 00 08 */	b lbl_8007669C
lbl_80076698:
/* 80076698 00073278  3B E0 00 00 */	li r31, 0
lbl_8007669C:
/* 8007669C 0007327C  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766A0 00073280  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800766A4 00073284  41 82 00 38 */	beq lbl_800766DC
/* 800766A8 00073288  C0 1D 18 34 */	lfs f0, 0x1834(r29)
/* 800766AC 0007328C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800766B0 00073290  D0 1D 18 34 */	stfs f0, 0x1834(r29)
/* 800766B4 00073294  C0 3D 18 34 */	lfs f1, 0x1834(r29)
/* 800766B8 00073298  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 800766BC 0007329C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800766C0 000732A0  40 80 00 1C */	bge lbl_800766DC
/* 800766C4 000732A4  FC 00 08 50 */	fneg f0, f1
/* 800766C8 000732A8  38 60 00 00 */	li r3, 0
/* 800766CC 000732AC  D0 1E 00 00 */	stfs f0, 0(r30)
/* 800766D0 000732B0  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766D4 000732B4  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 800766D8 000732B8  98 1D 22 1C */	stb r0, 0x221c(r29)
lbl_800766DC:
/* 800766DC 000732BC  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 800766E0 000732C0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800766E4 000732C4  40 82 00 60 */	bne lbl_80076744
/* 800766E8 000732C8  C0 3E 00 00 */	lfs f1, 0(r30)
/* 800766EC 000732CC  C0 02 89 04 */	lfs f0, lbl_804D82E4
/* 800766F0 000732D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800766F4 000732D4  40 81 00 28 */	ble lbl_8007671C
/* 800766F8 000732D8  3C 60 80 3C */	lis r3, lbl_803C0C58@ha
/* 800766FC 000732DC  4C C6 32 42 */	crset 6
/* 80076700 000732E0  38 63 0C 58 */	addi r3, r3, lbl_803C0C58@l
/* 80076704 000732E4  48 2C EF A5 */	bl OSReport
/* 80076708 000732E8  3C 60 80 3C */	lis r3, lbl_803C0C74@ha
/* 8007670C 000732EC  38 63 0C 74 */	addi r3, r3, lbl_803C0C74@l
/* 80076710 000732F0  38 80 00 B7 */	li r4, 0xb7
/* 80076714 000732F4  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 80076718 000732F8  48 31 1B 09 */	bl __assert
lbl_8007671C:
/* 8007671C 000732FC  C0 3D 18 38 */	lfs f1, 0x1838(r29)
/* 80076720 00073300  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80076724 00073304  EC 01 00 2A */	fadds f0, f1, f0
/* 80076728 00073308  D0 1D 18 38 */	stfs f0, 0x1838(r29)
/* 8007672C 0007330C  80 1D 18 3C */	lwz r0, 0x183c(r29)
/* 80076730 00073310  7C 1F 00 00 */	cmpw r31, r0
/* 80076734 00073314  40 81 00 08 */	ble lbl_8007673C
/* 80076738 00073318  93 FD 18 3C */	stw r31, 0x183c(r29)
lbl_8007673C:
/* 8007673C 0007331C  38 60 00 01 */	li r3, 1
/* 80076740 00073320  48 00 00 08 */	b lbl_80076748
lbl_80076744:
/* 80076744 00073324  38 60 00 00 */	li r3, 0
lbl_80076748:
/* 80076748 00073328  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8007674C 0007332C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80076750 00073330  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80076754 00073334  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80076758 00073338  38 21 00 30 */	addi r1, r1, 0x30
/* 8007675C 0007333C  7C 08 03 A6 */	mtlr r0
/* 80076760 00073340  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_80459278;
extern char* const lbl_803C0C80;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076764(void)
{ // clang-format off
    nofralloc
/* 80076764 00073344  7C 08 02 A6 */	mflr r0
/* 80076768 00073348  90 01 00 04 */	stw r0, 4(r1)
/* 8007676C 0007334C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80076770 00073350  80 0D AE B8 */	lwz r0, lbl_804D6558
/* 80076774 00073354  28 00 00 14 */	cmplwi r0, 0x14
/* 80076778 00073358  40 80 00 58 */	bge lbl_800767D0
/* 8007677C 0007335C  1D 40 00 28 */	mulli r10, r0, 0x28
/* 80076780 00073360  3D 20 80 46 */	lis r9, lbl_80459278@ha
/* 80076784 00073364  38 09 92 78 */	addi r0, r9, lbl_80459278@l
/* 80076788 00073368  7D 20 52 14 */	add r9, r0, r10
/* 8007678C 0007336C  90 69 00 00 */	stw r3, 0(r9)
/* 80076790 00073370  90 89 00 04 */	stw r4, 4(r9)
/* 80076794 00073374  90 A9 00 08 */	stw r5, 8(r9)
/* 80076798 00073378  90 C9 00 0C */	stw r6, 0xc(r9)
/* 8007679C 0007337C  91 09 00 10 */	stw r8, 0x10(r9)
/* 800767A0 00073380  80 67 00 B0 */	lwz r3, 0xb0(r7)
/* 800767A4 00073384  80 07 00 B4 */	lwz r0, 0xb4(r7)
/* 800767A8 00073388  90 69 00 14 */	stw r3, 0x14(r9)
/* 800767AC 0007338C  90 09 00 18 */	stw r0, 0x18(r9)
/* 800767B0 00073390  80 07 00 B8 */	lwz r0, 0xb8(r7)
/* 800767B4 00073394  90 09 00 1C */	stw r0, 0x1c(r9)
/* 800767B8 00073398  80 06 00 04 */	lwz r0, 4(r6)
/* 800767BC 0007339C  90 09 00 24 */	stw r0, 0x24(r9)
/* 800767C0 000733A0  80 6D AE B8 */	lwz r3, lbl_804D6558
/* 800767C4 000733A4  38 03 00 01 */	addi r0, r3, 1
/* 800767C8 000733A8  90 0D AE B8 */	stw r0, lbl_804D6558
/* 800767CC 000733AC  48 00 00 2C */	b lbl_800767F8
lbl_800767D0:
/* 800767D0 000733B0  3C 60 80 3C */	lis r3, lbl_803C0C80@ha
/* 800767D4 000733B4  4C C6 31 82 */	crclr 6
/* 800767D8 000733B8  38 63 0C 80 */	addi r3, r3, lbl_803C0C80@l
/* 800767DC 000733BC  38 80 00 14 */	li r4, 0x14
/* 800767E0 000733C0  48 2C EE C9 */	bl OSReport
/* 800767E4 000733C4  3C 60 80 3C */	lis r3, lbl_803C0C74@ha
/* 800767E8 000733C8  38 63 0C 74 */	addi r3, r3, lbl_803C0C74@l
/* 800767EC 000733CC  38 80 00 F9 */	li r4, 0xf9
/* 800767F0 000733D0  38 AD 83 C8 */	addi r5, r13, lbl_804D3A68
/* 800767F4 000733D4  48 31 1A 2D */	bl __assert
lbl_800767F8:
/* 800767F8 000733D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800767FC 000733DC  38 21 00 08 */	addi r1, r1, 8
/* 80076800 000733E0  7C 08 03 A6 */	mtlr r0
/* 80076804 000733E4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

extern unk_t lbl_804D6560;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_80076808(void)
{ // clang-format off
    nofralloc
/* 80076808 000733E8  7C 08 02 A6 */	mflr r0
/* 8007680C 000733EC  90 01 00 04 */	stw r0, 4(r1)
/* 80076810 000733F0  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80076814 000733F4  BF 01 00 20 */	stmw r24, 0x20(r1)
/* 80076818 000733F8  3B 04 00 00 */	addi r24, r4, 0
/* 8007681C 000733FC  3B 25 00 00 */	addi r25, r5, 0
/* 80076820 00073400  3B 46 00 00 */	addi r26, r6, 0
/* 80076824 00073404  3B 67 00 00 */	addi r27, r7, 0
/* 80076828 00073408  3B C3 00 00 */	addi r30, r3, 0
/* 8007682C 0007340C  3B 80 00 00 */	li r28, 0
/* 80076830 00073410  3B AD AE C0 */	addi r29, r13, lbl_804D6560
/* 80076834 00073414  3B E0 00 00 */	li r31, 0
lbl_80076838:
/* 80076838 00073418  80 1E 09 14 */	lwz r0, 0x914(r30)
/* 8007683C 0007341C  38 7E 09 14 */	addi r3, r30, 0x914
/* 80076840 00073420  2C 00 00 00 */	cmpwi r0, 0
/* 80076844 00073424  41 82 00 34 */	beq lbl_80076878
/* 80076848 00073428  80 83 00 04 */	lwz r4, 4(r3)
/* 8007684C 0007342C  80 18 00 04 */	lwz r0, 4(r24)
/* 80076850 00073430  7C 04 00 40 */	cmplw r4, r0
/* 80076854 00073434  40 82 00 24 */	bne lbl_80076878
/* 80076858 00073438  38 99 00 00 */	addi r4, r25, 0
/* 8007685C 0007343C  38 BA 00 00 */	addi r5, r26, 0
/* 80076860 00073440  4B F9 1E 29 */	bl func_80008688
/* 80076864 00073444  2C 03 00 00 */	cmpwi r3, 0
/* 80076868 00073448  41 82 00 10 */	beq lbl_80076878
/* 8007686C 0007344C  2C 1B 00 00 */	cmpwi r27, 0
/* 80076870 00073450  41 82 00 08 */	beq lbl_80076878
/* 80076874 00073454  9B FD 00 00 */	stb r31, 0(r29)
lbl_80076878:
/* 80076878 00073458  3B 9C 00 01 */	addi r28, r28, 1
/* 8007687C 0007345C  28 1C 00 04 */	cmplwi r28, 4
/* 80076880 00073460  3B DE 01 38 */	addi r30, r30, 0x138
/* 80076884 00073464  3B BD 00 01 */	addi r29, r29, 1
/* 80076888 00073468  41 80 FF B0 */	blt lbl_80076838
/* 8007688C 0007346C  BB 01 00 20 */	lmw r24, 0x20(r1)
/* 80076890 00073470  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076894 00073474  38 21 00 40 */	addi r1, r1, 0x40
/* 80076898 00073478  7C 08 03 A6 */	mtlr r0
/* 8007689C 0007347C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void func_800768A0(void){
    // clang-format off
    nofralloc
/* 800768A0 00073480  7C 08 02 A6 */	mflr r0
/* 800768A4 00073484  38 C3 09 14 */	addi r6, r3, 0x914
/* 800768A8 00073488  90 01 00 04 */	stw r0, 4(r1)
/* 800768AC 0007348C  7C 06 20 40 */	cmplw r6, r4
/* 800768B0 00073490  94 21 FF F8 */	stwu r1, -8(r1)
/* 800768B4 00073494  41 82 00 2C */	beq lbl_800768E0
/* 800768B8 00073498  80 06 00 00 */	lwz r0, 0(r6)
/* 800768BC 0007349C  2C 00 00 00 */	cmpwi r0, 0
/* 800768C0 000734A0  41 82 00 20 */	beq lbl_800768E0
/* 800768C4 000734A4  80 A6 00 04 */	lwz r5, 4(r6)
/* 800768C8 000734A8  80 04 00 04 */	lwz r0, 4(r4)
/* 800768CC 000734AC  7C 05 00 40 */	cmplw r5, r0
/* 800768D0 000734B0  40 82 00 10 */	bne lbl_800768E0
/* 800768D4 000734B4  7C C3 33 78 */	mr r3, r6
/* 800768D8 000734B8  4B F9 1C 25 */	bl func_800084FC
/* 800768DC 000734BC  48 00 00 B0 */	b lbl_8007698C
lbl_800768E0:
/* 800768E0 000734C0  38 63 01 38 */	addi r3, r3, 0x138
/* 800768E4 000734C4  38 C3 09 14 */	addi r6, r3, 0x914
/* 800768E8 000734C8  7C 06 20 40 */	cmplw r6, r4
/* 800768EC 000734CC  41 82 00 2C */	beq lbl_80076918
/* 800768F0 000734D0  80 06 00 00 */	lwz r0, 0(r6)
/* 800768F4 000734D4  2C 00 00 00 */	cmpwi r0, 0
/* 800768F8 000734D8  41 82 00 20 */	beq lbl_80076918
/* 800768FC 000734DC  80 A6 00 04 */	lwz r5, 4(r6)
/* 80076900 000734E0  80 04 00 04 */	lwz r0, 4(r4)
/* 80076904 000734E4  7C 05 00 40 */	cmplw r5, r0
/* 80076908 000734E8  40 82 00 10 */	bne lbl_80076918
/* 8007690C 000734EC  7C C3 33 78 */	mr r3, r6
/* 80076910 000734F0  4B F9 1B ED */	bl func_800084FC
/* 80076914 000734F4  48 00 00 78 */	b lbl_8007698C
lbl_80076918:
/* 80076918 000734F8  38 C3 0A 4C */	addi r6, r3, 0xa4c
/* 8007691C 000734FC  7C 06 20 40 */	cmplw r6, r4
/* 80076920 00073500  38 63 01 38 */	addi r3, r3, 0x138
/* 80076924 00073504  41 82 00 2C */	beq lbl_80076950
/* 80076928 00073508  80 06 00 00 */	lwz r0, 0(r6)
/* 8007692C 0007350C  2C 00 00 00 */	cmpwi r0, 0
/* 80076930 00073510  41 82 00 20 */	beq lbl_80076950
/* 80076934 00073514  80 A6 00 04 */	lwz r5, 4(r6)
/* 80076938 00073518  80 04 00 04 */	lwz r0, 4(r4)
/* 8007693C 0007351C  7C 05 00 40 */	cmplw r5, r0
/* 80076940 00073520  40 82 00 10 */	bne lbl_80076950
/* 80076944 00073524  7C C3 33 78 */	mr r3, r6
/* 80076948 00073528  4B F9 1B B5 */	bl func_800084FC
/* 8007694C 0007352C  48 00 00 40 */	b lbl_8007698C
lbl_80076950:
/* 80076950 00073530  38 C3 0A 4C */	addi r6, r3, 0xa4c
/* 80076954 00073534  7C 06 20 40 */	cmplw r6, r4
/* 80076958 00073538  41 82 00 2C */	beq lbl_80076984
/* 8007695C 0007353C  80 06 00 00 */	lwz r0, 0(r6)
/* 80076960 00073540  2C 00 00 00 */	cmpwi r0, 0
/* 80076964 00073544  41 82 00 20 */	beq lbl_80076984
/* 80076968 00073548  80 A6 00 04 */	lwz r5, 4(r6)
/* 8007696C 0007354C  80 04 00 04 */	lwz r0, 4(r4)
/* 80076970 00073550  7C 05 00 40 */	cmplw r5, r0
/* 80076974 00073554  40 82 00 10 */	bne lbl_80076984
/* 80076978 00073558  7C C3 33 78 */	mr r3, r6
/* 8007697C 0007355C  4B F9 1B 81 */	bl func_800084FC
/* 80076980 00073560  48 00 00 0C */	b lbl_8007698C
lbl_80076984:
/* 80076984 00073564  7C 83 23 78 */	mr r3, r4
/* 80076988 00073568  4B F9 1A B9 */	bl func_80008440
lbl_8007698C:
/* 8007698C 0007356C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80076990 00073570  38 21 00 08 */	addi r1, r1, 8
/* 80076994 00073574  7C 08 03 A6 */	mtlr r0
/* 80076998 00073578  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif

f32 const lbl_804D82E0 = 0.0F;
f32 const lbl_804D82E4 = 500.0F;
f32 const lbl_804D82E8 = 0.5F;
f32 const lbl_804D82EC = 1.0F;
f32 const lbl_804D82F0 = -1.0F;
f64 const lbl_804D82F8 = 4503601774854144.0;

#ifdef MWERKS_GEKKO
#pragma push
asm void func_8007699C(void)
{ // clang-format off
    nofralloc
/* 8007699C 0007357C  7C 08 02 A6 */	mflr r0
/* 800769A0 00073580  90 01 00 04 */	stw r0, 4(r1)
/* 800769A4 00073584  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 800769A8 00073588  BE E1 00 54 */	stmw r23, 0x54(r1)
/* 800769AC 0007358C  7C 7C 1B 78 */	mr r28, r3
/* 800769B0 00073590  7C 9D 23 78 */	mr r29, r4
/* 800769B4 00073594  7C DF 33 78 */	mr r31, r6
/* 800769B8 00073598  7C BE 2B 78 */	mr r30, r5
/* 800769BC 0007359C  C0 24 00 64 */	lfs f1, 0x64(r4)
/* 800769C0 000735A0  C0 06 00 64 */	lfs f0, 0x64(r6)
/* 800769C4 000735A4  C0 42 89 08 */	lfs f2, lbl_804D82E8
/* 800769C8 000735A8  EC 01 00 2A */	fadds f0, f1, f0
/* 800769CC 000735AC  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800769D0 000735B0  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769D4 000735B4  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 800769D8 000735B8  C0 24 00 68 */	lfs f1, 0x68(r4)
/* 800769DC 000735BC  C0 06 00 68 */	lfs f0, 0x68(r6)
/* 800769E0 000735C0  EC 01 00 2A */	fadds f0, f1, f0
/* 800769E4 000735C4  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769E8 000735C8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800769EC 000735CC  C0 24 00 6C */	lfs f1, 0x6c(r4)
/* 800769F0 000735D0  C0 06 00 6C */	lfs f0, 0x6c(r6)
/* 800769F4 000735D4  EC 01 00 2A */	fadds f0, f1, f0
/* 800769F8 000735D8  EC 02 00 32 */	fmuls f0, f2, f0
/* 800769FC 000735DC  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 80076A00 000735E0  C0 04 00 0C */	lfs f0, 0xc(r4)
/* 80076A04 000735E4  C0 46 00 0C */	lfs f2, 0xc(r6)
/* 80076A08 000735E8  FC 00 00 1E */	fctiwz f0, f0
/* 80076A0C 000735EC  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80076A10 000735F0  FC 20 10 1E */	fctiwz f1, f2
/* 80076A14 000735F4  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80076A18 000735F8  D8 21 00 48 */	stfd f1, 0x48(r1)
/* 80076A1C 000735FC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076A20 00073600  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 80076A24 00073604  7C 64 18 50 */	subf r3, r4, r3
/* 80076A28 00073608  7C 03 00 00 */	cmpw r3, r0
/* 80076A2C 0007360C  40 80 01 24 */	bge lbl_80076B50
/* 80076A30 00073610  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076A34 00073614  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80076A38 00073618  41 82 00 28 */	beq lbl_80076A60
/* 80076A3C 0007361C  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076A40 00073620  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076A44 00073624  2C 00 00 00 */	cmpwi r0, 0
/* 80076A48 00073628  41 82 00 10 */	beq lbl_80076A58
/* 80076A4C 0007362C  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076A50 00073630  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80076A54 00073634  48 00 00 10 */	b lbl_80076A64
lbl_80076A58:
/* 80076A58 00073638  3B 20 00 01 */	li r25, 1
/* 80076A5C 0007363C  48 00 00 08 */	b lbl_80076A64
lbl_80076A60:
/* 80076A60 00073640  3B 20 00 00 */	li r25, 0
lbl_80076A64:
/* 80076A64 00073644  3B 40 00 00 */	li r26, 0
/* 80076A68 00073648  3B 1E 00 00 */	addi r24, r30, 0
/* 80076A6C 0007364C  3B 7A 00 00 */	addi r27, r26, 0
/* 80076A70 00073650  3A ED AE C0 */	addi r23, r13, lbl_804D6560
lbl_80076A74:
/* 80076A74 00073654  80 18 09 14 */	lwz r0, 0x914(r24)
/* 80076A78 00073658  38 78 09 14 */	addi r3, r24, 0x914
/* 80076A7C 0007365C  2C 00 00 00 */	cmpwi r0, 0
/* 80076A80 00073660  41 82 00 2C */	beq lbl_80076AAC
/* 80076A84 00073664  80 83 00 04 */	lwz r4, 4(r3)
/* 80076A88 00073668  80 1F 00 04 */	lwz r0, 4(r31)
/* 80076A8C 0007366C  7C 04 00 40 */	cmplw r4, r0
/* 80076A90 00073670  40 82 00 1C */	bne lbl_80076AAC
/* 80076A94 00073674  38 BC 00 00 */	addi r5, r28, 0
/* 80076A98 00073678  38 80 00 03 */	li r4, 3
/* 80076A9C 0007367C  4B F9 1B ED */	bl func_80008688
/* 80076AA0 00073680  2C 03 00 00 */	cmpwi r3, 0
/* 80076AA4 00073684  41 82 00 08 */	beq lbl_80076AAC
/* 80076AA8 00073688  9B 77 00 00 */	stb r27, 0(r23)
lbl_80076AAC:
/* 80076AAC 0007368C  3B 5A 00 01 */	addi r26, r26, 1
/* 80076AB0 00073690  28 1A 00 04 */	cmplwi r26, 4
/* 80076AB4 00073694  3B 18 01 38 */	addi r24, r24, 0x138
/* 80076AB8 00073698  3A F7 00 01 */	addi r23, r23, 1
/* 80076ABC 0007369C  41 80 FF B8 */	blt lbl_80076A74
/* 80076AC0 000736A0  80 1E 19 18 */	lwz r0, 0x1918(r30)
/* 80076AC4 000736A4  7C 19 00 00 */	cmpw r25, r0
/* 80076AC8 000736A8  40 81 00 74 */	ble lbl_80076B3C
/* 80076ACC 000736AC  93 3E 19 18 */	stw r25, 0x1918(r30)
/* 80076AD0 000736B0  88 1F 00 40 */	lbz r0, 0x40(r31)
/* 80076AD4 000736B4  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 80076AD8 000736B8  28 00 00 01 */	cmplwi r0, 1
/* 80076ADC 000736BC  40 82 00 60 */	bne lbl_80076B3C
/* 80076AE0 000736C0  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80076AE4 000736C4  2C 00 00 00 */	cmpwi r0, 0
/* 80076AE8 000736C8  40 82 00 54 */	bne lbl_80076B3C
/* 80076AEC 000736CC  6F 20 80 00 */	xoris r0, r25, 0x8000
/* 80076AF0 000736D0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076AF4 000736D4  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076AF8 000736D8  3C 00 43 30 */	lis r0, 0x4330
/* 80076AFC 000736DC  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80076B00 000736E0  90 01 00 40 */	stw r0, 0x40(r1)
/* 80076B04 000736E4  C0 23 03 D0 */	lfs f1, 0x3d0(r3)
/* 80076B08 000736E8  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80076B0C 000736EC  C0 03 03 D4 */	lfs f0, 0x3d4(r3)
/* 80076B10 000736F0  EC 42 18 28 */	fsubs f2, f2, f3
/* 80076B14 000736F4  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80076B18 000736F8  D0 1E 19 1C */	stfs f0, 0x191c(r30)
/* 80076B1C 000736FC  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 80076B20 00073700  C0 1C 00 B0 */	lfs f0, 0xb0(r28)
/* 80076B24 00073704  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076B28 00073708  40 80 00 0C */	bge lbl_80076B34
/* 80076B2C 0007370C  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80076B30 00073710  48 00 00 08 */	b lbl_80076B38
lbl_80076B34:
/* 80076B34 00073714  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80076B38:
/* 80076B38 00073718  D0 1E 19 20 */	stfs f0, 0x1920(r30)
lbl_80076B3C:
/* 80076B3C 0007371C  38 A1 00 30 */	addi r5, r1, 0x30
/* 80076B40 00073720  4C C6 31 82 */	crclr 6
/* 80076B44 00073724  38 60 04 1C */	li r3, 0x41c
/* 80076B48 00073728  38 80 00 00 */	li r4, 0
/* 80076B4C 0007372C  4B FE 92 91 */	bl ef_Spawn
lbl_80076B50:
/* 80076B50 00073730  C0 5D 00 0C */	lfs f2, 0xc(r29)
/* 80076B54 00073734  C0 1F 00 0C */	lfs f0, 0xc(r31)
/* 80076B58 00073738  FC 20 10 1E */	fctiwz f1, f2
/* 80076B5C 0007373C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076B60 00073740  FC 00 00 1E */	fctiwz f0, f0
/* 80076B64 00073744  80 83 03 CC */	lwz r4, 0x3cc(r3)
/* 80076B68 00073748  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076B6C 0007374C  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80076B70 00073750  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80076B74 00073754  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80076B78 00073758  7C 64 18 50 */	subf r3, r4, r3
/* 80076B7C 0007375C  7C 03 00 00 */	cmpw r3, r0
/* 80076B80 00073760  40 80 01 24 */	bge lbl_80076CA4
/* 80076B84 00073764  C0 02 89 00 */	lfs f0, lbl_804D82E0
/* 80076B88 00073768  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 80076B8C 0007376C  41 82 00 28 */	beq lbl_80076BB4
/* 80076B90 00073770  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076B94 00073774  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80076B98 00073778  2C 00 00 00 */	cmpwi r0, 0
/* 80076B9C 0007377C  41 82 00 10 */	beq lbl_80076BAC
/* 80076BA0 00073780  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 80076BA4 00073784  83 21 00 44 */	lwz r25, 0x44(r1)
/* 80076BA8 00073788  48 00 00 10 */	b lbl_80076BB8
lbl_80076BAC:
/* 80076BAC 0007378C  3B 20 00 01 */	li r25, 1
/* 80076BB0 00073790  48 00 00 08 */	b lbl_80076BB8
lbl_80076BB4:
/* 80076BB4 00073794  3B 20 00 00 */	li r25, 0
lbl_80076BB8:
/* 80076BB8 00073798  3B 40 00 00 */	li r26, 0
/* 80076BBC 0007379C  3A FC 00 00 */	addi r23, r28, 0
lbl_80076BC0:
/* 80076BC0 000737A0  80 17 09 14 */	lwz r0, 0x914(r23)
/* 80076BC4 000737A4  38 77 09 14 */	addi r3, r23, 0x914
/* 80076BC8 000737A8  2C 00 00 00 */	cmpwi r0, 0
/* 80076BCC 000737AC  41 82 00 20 */	beq lbl_80076BEC
/* 80076BD0 000737B0  80 83 00 04 */	lwz r4, 4(r3)
/* 80076BD4 000737B4  80 1D 00 04 */	lwz r0, 4(r29)
/* 80076BD8 000737B8  7C 04 00 40 */	cmplw r4, r0
/* 80076BDC 000737BC  40 82 00 10 */	bne lbl_80076BEC
/* 80076BE0 000737C0  38 BE 00 00 */	addi r5, r30, 0
/* 80076BE4 000737C4  38 80 00 03 */	li r4, 3
/* 80076BE8 000737C8  4B F9 1A A1 */	bl func_80008688
lbl_80076BEC:
/* 80076BEC 000737CC  3B 5A 00 01 */	addi r26, r26, 1
/* 80076BF0 000737D0  28 1A 00 04 */	cmplwi r26, 4
/* 80076BF4 000737D4  3A F7 01 38 */	addi r23, r23, 0x138
/* 80076BF8 000737D8  41 80 FF C8 */	blt lbl_80076BC0
/* 80076BFC 000737DC  80 1C 19 18 */	lwz r0, 0x1918(r28)
/* 80076C00 000737E0  7C 19 00 00 */	cmpw r25, r0
/* 80076C04 000737E4  40 81 00 74 */	ble lbl_80076C78
/* 80076C08 000737E8  93 3C 19 18 */	stw r25, 0x1918(r28)
/* 80076C0C 000737EC  88 1D 00 40 */	lbz r0, 0x40(r29)
/* 80076C10 000737F0  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 80076C14 000737F4  28 00 00 01 */	cmplwi r0, 1
/* 80076C18 000737F8  40 82 00 60 */	bne lbl_80076C78
/* 80076C1C 000737FC  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 80076C20 00073800  2C 00 00 00 */	cmpwi r0, 0
/* 80076C24 00073804  40 82 00 54 */	bne lbl_80076C78
/* 80076C28 00073808  6F 20 80 00 */	xoris r0, r25, 0x8000
/* 80076C2C 0007380C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80076C30 00073810  90 01 00 44 */	stw r0, 0x44(r1)
/* 80076C34 00073814  3C 00 43 30 */	lis r0, 0x4330
/* 80076C38 00073818  C8 62 89 18 */	lfd f3, lbl_804D82F8
/* 80076C3C 0007381C  90 01 00 40 */	stw r0, 0x40(r1)
/* 80076C40 00073820  C0 23 03 D0 */	lfs f1, 0x3d0(r3)
/* 80076C44 00073824  C8 41 00 40 */	lfd f2, 0x40(r1)
/* 80076C48 00073828  C0 03 03 D4 */	lfs f0, 0x3d4(r3)
/* 80076C4C 0007382C  EC 42 18 28 */	fsubs f2, f2, f3
/* 80076C50 00073830  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 80076C54 00073834  D0 1C 19 1C */	stfs f0, 0x191c(r28)
/* 80076C58 00073838  C0 3E 00 B0 */	lfs f1, 0xb0(r30)
/* 80076C5C 0007383C  C0 1C 00 B0 */	lfs f0, 0xb0(r28)
/* 80076C60 00073840  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80076C64 00073844  40 81 00 0C */	ble lbl_80076C70
/* 80076C68 00073848  C0 02 89 0C */	lfs f0, lbl_804D82EC
/* 80076C6C 0007384C  48 00 00 08 */	b lbl_80076C74
lbl_80076C70:
/* 80076C70 00073850  C0 02 89 10 */	lfs f0, lbl_804D82F0
lbl_80076C74:
/* 80076C74 00073854  D0 1C 19 20 */	stfs f0, 0x1920(r28)
lbl_80076C78:
/* 80076C78 00073858  38 A1 00 30 */	addi r5, r1, 0x30
/* 80076C7C 0007385C  4C C6 31 82 */	crclr 6
/* 80076C80 00073860  38 60 04 1C */	li r3, 0x41c
/* 80076C84 00073864  38 80 00 00 */	li r4, 0
/* 80076C88 00073868  4B FE 91 55 */	bl ef_Spawn
/* 80076C8C 0007386C  38 7E 00 00 */	addi r3, r30, 0
/* 80076C90 00073870  38 9D 00 00 */	addi r4, r29, 0
/* 80076C94 00073874  38 BF 00 00 */	addi r5, r31, 0
/* 80076C98 00073878  48 00 18 1D */	bl func_800784B4
/* 80076C9C 0007387C  38 60 00 01 */	li r3, 1
/* 80076CA0 00073880  48 00 00 08 */	b lbl_80076CA8
lbl_80076CA4:
/* 80076CA4 00073884  38 60 00 00 */	li r3, 0
lbl_80076CA8:
/* 80076CA8 00073888  BA E1 00 54 */	lmw r23, 0x54(r1)
/* 80076CAC 0007388C  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80076CB0 00073890  38 21 00 78 */	addi r1, r1, 0x78
/* 80076CB4 00073894  7C 08 03 A6 */	mtlr r0
/* 80076CB8 00073898  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#endif
