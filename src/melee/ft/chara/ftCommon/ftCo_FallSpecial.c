#include <platform.h>
#include "ft/forward.h"

#include "ftCo_FallSpecial.h"

#include "ftCo_DamageFall.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "mp/mplib.h"
#include "un/un_2FC9.h"

#include <common_structs.h>
#include <placeholder.h>

void ftCo_800968C8(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_80096900(gobj, 1, 0, true, 1, fp->x2EC);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_80096900(ftCo_GObj* gobj, int, int, bool allow_interrupt, float,
                       float)
{
    // clang-format off
    nofralloc
/* 80096900 000934E0  7C 08 02 A6 */	mflr r0
/* 80096904 000934E4  90 01 00 04 */	stw r0, 4(r1)
/* 80096908 000934E8  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8009690C 000934EC  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80096910 000934F0  FF E0 10 90 */	fmr f31, f2
/* 80096914 000934F4  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 80096918 000934F8  FF C0 08 90 */	fmr f30, f1
/* 8009691C 000934FC  BF 61 00 2C */	stmw r27, 0x2c(r1)
/* 80096920 00093500  7C 9B 23 78 */	mr r27, r4
/* 80096924 00093504  3B 85 00 00 */	addi r28, r5, 0
/* 80096928 00093508  3B A6 00 00 */	addi r29, r6, 0
/* 8009692C 0009350C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80096930 00093510  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 80096934 00093514  3B FE 01 10 */	addi r31, r30, 0x110
/* 80096938 00093518  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8009693C 0009351C  41 82 00 0C */	beq lbl_80096948
/* 80096940 00093520  4B FF 9E 41 */	bl ftCo_80090780
/* 80096944 00093524  48 00 00 78 */	b lbl_800969BC
lbl_80096948:
/* 80096948 00093528  C0 22 8B F4 */	lfs f1, 0.0f
/* 8009694C 0009352C  38 80 00 23 */	li r4, 0x23
/* 80096950 00093530  C0 42 8B F0 */	lfs f2, 1.0f
/* 80096954 00093534  38 A0 00 01 */	li r5, 1
/* 80096958 00093538  FC 60 08 90 */	fmr f3, f1
/* 8009695C 0009353C  38 C0 00 00 */	li r6, 0
/* 80096960 00093540  4B FD 2A 4D */	bl Fighter_ChangeMotionState
/* 80096964 00093544  C0 1F 00 6C */	lfs f0, 0x6c(r31)
/* 80096968 00093548  38 00 00 1A */	li r0, 0x1a
/* 8009696C 0009354C  EC 00 07 B2 */	fmuls f0, f0, f30
/* 80096970 00093550  D0 1E 23 48 */	stfs f0, 0x2348(r30)
/* 80096974 00093554  93 7E 23 4C */	stw r27, 0x234c(r30)
/* 80096978 00093558  93 9E 23 50 */	stw r28, 0x2350(r30)
/* 8009697C 0009355C  D3 FE 23 54 */	stfs f31, 0x2354(r30)
/* 80096980 00093560  93 BE 23 58 */	stw r29, 0x2358(r30)
/* 80096984 00093564  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 80096988 00093568  C0 02 8B F4 */	lfs f0, 0.0f
/* 8009698C 0009356C  D0 1E 23 44 */	stfs f0, 0x2344(r30)
/* 80096990 00093570  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80096994 00093574  2C 00 00 00 */	cmpwi r0, 0
/* 80096998 00093578  40 82 00 10 */	bne lbl_800969A8
/* 8009699C 0009357C  7F C3 F3 78 */	mr r3, r30
/* 800969A0 00093580  4B FE 6C 6D */	bl ftCommon_8007D60C
/* 800969A4 00093584  48 00 00 0C */	b lbl_800969B0
lbl_800969A8:
/* 800969A8 00093588  7F C3 F3 78 */	mr r3, r30
/* 800969AC 0009358C  4B FE 6C ED */	bl ftCommon_8007D698
lbl_800969B0:
/* 800969B0 00093590  80 7E 00 08 */	lwz r3, 8(r30)
/* 800969B4 00093594  C0 3E 00 B4 */	lfs f1, 0xb4(r30)
/* 800969B8 00093598  48 28 BB E1 */	bl un_80322598
lbl_800969BC:
/* 800969BC 0009359C  BB 61 00 2C */	lmw r27, 0x2c(r1)
/* 800969C0 000935A0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800969C4 000935A4  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 800969C8 000935A8  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 800969CC 000935AC  38 21 00 50 */	addi r1, r1, 0x50
/* 800969D0 000935B0  7C 08 03 A6 */	mtlr r0
/* 800969D4 000935B4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

/// @todo Real solution is @c 0. Inline needs to be fixed.
#define SOLUTION 1
void ftCo_80096900(ftCo_GObj* gobj, int arg1, int arg2, bool allow_interrupt,
                   float arg4, float arg5)
{
#if SOLUTION == 0
    ftCo_800969D8(gobj, arg1, arg2, allow_interrupt, arg4, arg5, 0);
#elif SOLUTION == 1

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallSpecial, Ft_MF_KeepFastFall,
                              NULL, 0, 1, 0);
    fp->mv.co.fallspecial.x8 = ca->air_drift_max * arg4;
    fp->mv.co.fallspecial.xC = arg1;
    fp->mv.co.fallspecial.x10 = arg2;
    fp->mv.co.fallspecial.x14 = arg5;
    fp->mv.co.fallspecial.allow_interrupt = allow_interrupt;
    fp->mv.co.fallspecial.x0 = 26;
    fp->mv.co.fallspecial.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    } else {
        ftCommon_8007D698(fp);
    }
    un_80322598(fp->x8_spawnNum, fp->cur_pos.y);
#endif
}
#undef SOLUTION
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_800969D8(ftCo_GObj* gobj, int, int, int, float, float, float)
{ // clang-format off
    nofralloc
/* 800969D8 000935B8  7C 08 02 A6 */	mflr r0
/* 800969DC 000935BC  90 01 00 04 */	stw r0, 4(r1)
/* 800969E0 000935C0  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800969E4 000935C4  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 800969E8 000935C8  FF E0 10 90 */	fmr f31, f2
/* 800969EC 000935CC  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 800969F0 000935D0  FF C0 08 90 */	fmr f30, f1
/* 800969F4 000935D4  BF 61 00 34 */	stmw r27, 0x34(r1)
/* 800969F8 000935D8  7C 9B 23 78 */	mr r27, r4
/* 800969FC 000935DC  3B 85 00 00 */	addi r28, r5, 0
/* 80096A00 000935E0  3B A6 00 00 */	addi r29, r6, 0
/* 80096A04 000935E4  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80096A08 000935E8  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 80096A0C 000935EC  3B FE 01 10 */	addi r31, r30, 0x110
/* 80096A10 000935F0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80096A14 000935F4  41 82 00 0C */	beq lbl_80096A20
/* 80096A18 000935F8  4B FF 9D 69 */	bl ftCo_80090780
/* 80096A1C 000935FC  48 00 00 68 */	b lbl_80096A84
lbl_80096A20:
/* 80096A20 00093600  C0 22 8B F4 */	lfs f1, 0.0f
/* 80096A24 00093604  38 80 00 23 */	li r4, 0x23
/* 80096A28 00093608  C0 42 8B F0 */	lfs f2, 1.0f
/* 80096A2C 0009360C  38 A0 00 01 */	li r5, 1
/* 80096A30 00093610  38 C0 00 00 */	li r6, 0
/* 80096A34 00093614  4B FD 29 79 */	bl Fighter_ChangeMotionState
/* 80096A38 00093618  C0 1F 00 6C */	lfs f0, 0x6c(r31)
/* 80096A3C 0009361C  38 00 00 1A */	li r0, 0x1a
/* 80096A40 00093620  EC 00 07 B2 */	fmuls f0, f0, f30
/* 80096A44 00093624  D0 1E 23 48 */	stfs f0, 0x2348(r30)
/* 80096A48 00093628  93 7E 23 4C */	stw r27, 0x234c(r30)
/* 80096A4C 0009362C  93 9E 23 50 */	stw r28, 0x2350(r30)
/* 80096A50 00093630  D3 FE 23 54 */	stfs f31, 0x2354(r30)
/* 80096A54 00093634  93 BE 23 58 */	stw r29, 0x2358(r30)
/* 80096A58 00093638  90 1E 23 40 */	stw r0, 0x2340(r30)
/* 80096A5C 0009363C  C0 02 8B F4 */	lfs f0, 0.0f
/* 80096A60 00093640  D0 1E 23 44 */	stfs f0, 0x2344(r30)
/* 80096A64 00093644  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80096A68 00093648  2C 00 00 00 */	cmpwi r0, 0
/* 80096A6C 0009364C  40 82 00 0C */	bne lbl_80096A78
/* 80096A70 00093650  7F C3 F3 78 */	mr r3, r30
/* 80096A74 00093654  4B FE 6B 99 */	bl ftCommon_8007D60C
lbl_80096A78:
/* 80096A78 00093658  80 7E 00 08 */	lwz r3, 8(r30)
/* 80096A7C 0009365C  C0 3E 00 B4 */	lfs f1, 0xb4(r30)
/* 80096A80 00093660  48 28 BB 19 */	bl un_80322598
lbl_80096A84:
/* 80096A84 00093664  BB 61 00 34 */	lmw r27, 0x34(r1)
/* 80096A88 00093668  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80096A8C 0009366C  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 80096A90 00093670  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 80096A94 00093674  38 21 00 58 */	addi r1, r1, 0x58
/* 80096A98 00093678  7C 08 03 A6 */	mtlr r0
/* 80096A9C 0009367C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_800969D8(ftCo_GObj* gobj, int arg1, int arg2, int allow_interrupt,
                   float arg4, float arg5, float arg6)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    if (fp->x2224_b2) {
        ftCo_80090780(gobj);
        return;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_FallSpecial, Ft_MF_KeepFastFall,
                              NULL, 0, 1, arg6);
    fp->mv.co.fallspecial.x8 = ca->air_drift_max * arg4;
    fp->mv.co.fallspecial.xC = arg1;
    fp->mv.co.fallspecial.x10 = arg2;
    fp->mv.co.fallspecial.x14 = arg5;
    fp->mv.co.fallspecial.allow_interrupt = allow_interrupt;
    fp->mv.co.fallspecial.x0 = 26;
    fp->mv.co.fallspecial.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D60C(fp);
    }
    un_80322598(fp->x8_spawnNum, fp->cur_pos.y);
}
#endif

void ftCo_FallSpecial_Anim(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_800CCBE0(gobj, &fp->mv.co.fallspecial.x4, ftCo_MS_JumpB,
                  ftCo_MS_JumpAerialF, ftCo_MS_JumpAerialB);
    ftCo_800CC988(gobj, fp->mv.co.fallspecial.x4);
}

void ftCo_FallSpecial_IASA(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_800CEE70(gobj))
    RETURN_IF(ftCo_800D705C(gobj))
    RETURN_IF(ftCo_800CB870(gobj));
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftCo_FallSpecial_Phys(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80096B44 00093724  7C 08 02 A6 */	mflr r0
/* 80096B48 00093728  90 01 00 04 */	stw r0, 4(r1)
/* 80096B4C 0009372C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80096B50 00093730  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80096B54 00093734  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80096B58 00093738  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80096B5C 0009373C  38 7E 00 00 */	addi r3, r30, 0
/* 80096B60 00093740  3B FE 01 10 */	addi r31, r30, 0x110
/* 80096B64 00093744  4B FE 69 C5 */	bl ftCommon_8007D528
/* 80096B68 00093748  80 1E 23 4C */	lwz r0, 0x234c(r30)
/* 80096B6C 0009374C  2C 00 00 00 */	cmpwi r0, 0
/* 80096B70 00093750  41 82 00 70 */	beq lbl_80096BE0
/* 80096B74 00093754  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 80096B78 00093758  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80096B7C 0009375C  41 82 00 10 */	beq lbl_80096B8C
/* 80096B80 00093760  7F C3 F3 78 */	mr r3, r30
/* 80096B84 00093764  4B FE 69 61 */	bl ftCommon_8007D4E4
/* 80096B88 00093768  48 00 00 14 */	b lbl_80096B9C
lbl_80096B8C:
/* 80096B8C 0009376C  C0 3F 00 5C */	lfs f1, 0x5c(r31)
/* 80096B90 00093770  7F C3 F3 78 */	mr r3, r30
/* 80096B94 00093774  C0 5F 00 60 */	lfs f2, 0x60(r31)
/* 80096B98 00093778  4B FE 68 FD */	bl ftCommon_8007D494
lbl_80096B9C:
/* 80096B9C 0009377C  C0 9E 06 20 */	lfs f4, 0x620(r30)
/* 80096BA0 00093780  C0 02 8B F4 */	lfs f0, 0.0f
/* 80096BA4 00093784  C0 3F 00 64 */	lfs f1, 0x64(r31)
/* 80096BA8 00093788  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80096BAC 0009378C  EC 24 00 72 */	fmuls f1, f4, f1
/* 80096BB0 00093790  40 81 00 0C */	ble lbl_80096BBC
/* 80096BB4 00093794  C0 5F 00 68 */	lfs f2, 0x68(r31)
/* 80096BB8 00093798  48 00 00 0C */	b lbl_80096BC4
lbl_80096BBC:
/* 80096BBC 0009379C  C0 1F 00 68 */	lfs f0, 0x68(r31)
/* 80096BC0 000937A0  FC 40 00 50 */	fneg f2, f0
lbl_80096BC4:
/* 80096BC4 000937A4  C0 1F 00 6C */	lfs f0, 0x6c(r31)
/* 80096BC8 000937A8  EC 21 10 2A */	fadds f1, f1, f2
/* 80096BCC 000937AC  C0 7F 00 70 */	lfs f3, 0x70(r31)
/* 80096BD0 000937B0  7F C3 F3 78 */	mr r3, r30
/* 80096BD4 000937B4  EC 44 00 32 */	fmuls f2, f4, f0
/* 80096BD8 000937B8  4B FE 65 69 */	bl ftCommon_8007D140
/* 80096BDC 000937BC  48 00 00 A4 */	b lbl_80096C80
lbl_80096BE0:
/* 80096BE0 000937C0  88 1E 22 1A */	lbz r0, 0x221a(r30)
/* 80096BE4 000937C4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80096BE8 000937C8  41 82 00 10 */	beq lbl_80096BF8
/* 80096BEC 000937CC  7F C3 F3 78 */	mr r3, r30
/* 80096BF0 000937D0  4B FE 68 F5 */	bl ftCommon_8007D4E4
/* 80096BF4 000937D4  48 00 00 14 */	b lbl_80096C08
lbl_80096BF8:
/* 80096BF8 000937D8  C0 3F 00 5C */	lfs f1, 0x5c(r31)
/* 80096BFC 000937DC  7F C3 F3 78 */	mr r3, r30
/* 80096C00 000937E0  C0 5F 00 74 */	lfs f2, 0x74(r31)
/* 80096C04 000937E4  4B FE 68 91 */	bl ftCommon_8007D494
lbl_80096C08:
/* 80096C08 000937E8  C0 7E 06 20 */	lfs f3, 0x620(r30)
/* 80096C0C 000937EC  C0 02 8B F4 */	lfs f0, 0.0f
/* 80096C10 000937F0  C0 3F 00 64 */	lfs f1, 0x64(r31)
/* 80096C14 000937F4  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80096C18 000937F8  EC 23 00 72 */	fmuls f1, f3, f1
/* 80096C1C 000937FC  40 81 00 0C */	ble lbl_80096C28
/* 80096C20 00093800  C0 1F 00 68 */	lfs f0, 0x68(r31)
/* 80096C24 00093804  48 00 00 0C */	b lbl_80096C30
lbl_80096C28:
/* 80096C28 00093808  C0 1F 00 68 */	lfs f0, 0x68(r31)
/* 80096C2C 0009380C  FC 00 00 50 */	fneg f0, f0
lbl_80096C30:
/* 80096C30 00093810  C0 5F 00 6C */	lfs f2, 0x6c(r31)
/* 80096C34 00093814  EC 21 00 2A */	fadds f1, f1, f0
/* 80096C38 00093818  C0 02 8B F4 */	lfs f0, 0.0f
/* 80096C3C 0009381C  EC 43 00 B2 */	fmuls f2, f3, f2
/* 80096C40 00093820  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80096C44 00093824  40 80 00 0C */	bge lbl_80096C50
/* 80096C48 00093828  FC 00 10 50 */	fneg f0, f2
/* 80096C4C 0009382C  48 00 00 08 */	b lbl_80096C54
lbl_80096C50:
/* 80096C50 00093830  FC 00 10 90 */	fmr f0, f2
lbl_80096C54:
/* 80096C54 00093834  C0 7E 23 48 */	lfs f3, 0x2348(r30)
/* 80096C58 00093838  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 80096C5C 0009383C  40 81 00 18 */	ble lbl_80096C74
/* 80096C60 00093840  C0 02 8B F4 */	lfs f0, 0.0f
/* 80096C64 00093844  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80096C68 00093848  40 80 00 08 */	bge lbl_80096C70
/* 80096C6C 0009384C  FC 60 18 50 */	fneg f3, f3
lbl_80096C70:
/* 80096C70 00093850  FC 40 18 90 */	fmr f2, f3
lbl_80096C74:
/* 80096C74 00093854  C0 7F 00 70 */	lfs f3, 0x70(r31)
/* 80096C78 00093858  7F C3 F3 78 */	mr r3, r30
/* 80096C7C 0009385C  4B FE 64 C5 */	bl ftCommon_8007D140
lbl_80096C80:
/* 80096C80 00093860  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80096C84 00093864  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80096C88 00093868  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80096C8C 0009386C  38 21 00 18 */	addi r1, r1, 0x18
/* 80096C90 00093870  7C 08 03 A6 */	mtlr r0
/* 80096C94 00093874  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_FallSpecial_Phys(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* ca = &fp->co_attrs;
    ftCommon_8007D528(fp);
    if (fp->mv.co.fallspecial.xC != 0) {
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, ca->grav, ca->terminal_vel);
        }
        {
            float lstick_x = fp->input.lstick.x;
            float base =
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;
            ftCommon_8007D140(fp, lstick_x * ca->air_drift_stick_mul + base,
                              lstick_x * ca->air_drift_max,
                              ca->aerial_friction);
        }
    } else {
        if (fp->x221A_b4) {
            ftCommon_8007D4E4(fp);
        } else {
            ftCommon_8007D494(fp, ca->grav, ca->fast_fall_velocity);
        }
        {
            float lstick_x = fp->input.lstick.x;
            float base =
                lstick_x > 0 ? ca->aerial_drift_base : -ca->aerial_drift_base;
            {
                float drift_max = lstick_x * ca->air_drift_max;
                float mv_x8 = fp->mv.co.fallspecial.x8;
                if (ABS(drift_max) > mv_x8) {
                    if (drift_max < 0) {
                        mv_x8 = -mv_x8;
                    }
                    drift_max = mv_x8;
                }
                ftCommon_8007D140(fp,
                                  lstick_x * ca->air_drift_stick_mul + base,
                                  drift_max, ca->aerial_friction);
            }
        }
    }
}
#endif

void ftCo_FallSpecial_Coll(ftCo_GObj* gobj)
{
    ft_80083090(gobj, ftCo_80096CC8, ftCo_80096D28);
}

bool ftCo_80096CC8(ftCo_GObj* gobj, enum_t arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    if (arg1 != -1 && (!(mpLib_80054CEC(arg1) & (1 << 8)) ||
                       fp->input.lstick.y > p_ftCommonData->x25C))
    {
        return true;
    }
    return false;
}

void ftCo_80096D28(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.fallspecial.x10 || fp->self_vel.y < ftCo_800D0EC8(fp)) {
        ftCo_800D5CB0(gobj, fp->mv.co.fallspecial.allow_interrupt,
                      fp->mv.co.fallspecial.x14);
    } else {
        ft_8008A2BC(gobj);
    }
}
