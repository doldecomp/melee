#include <platform.h>
#include "forward.h"
#include "ft/forward.h"

#include "ftPe_Float.h"

#include "ftPe_FloatAttack.h"
#include "ftPe_FloatFall.h"
#include "ftPe_Init.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/ftCo_0961.h"
#include "ftCommon/ftCo_SpecialAir.h"
#include "ftPeach/types.h"

#include <common_structs.h>
#include <baselib/gobj.h>

float const ftPe_Float_804D97C0 = 0;
float const ftPe_Float_804D97C4 = 1;

/* static */ bool ftPe_Float_CheckContinueInput(Fighter* fp)
{
    return fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
           fp->input.held_inputs & HSD_PAD_XY;
}

static bool checkStartFloatInput(HSD_GObj* gobj)
{
    Fighter* temp_r6 = GET_FIGHTER(gobj);
    return temp_r6->input.lstick.y <= -p_ftCommonData->x88 &&
           temp_r6->input.held_inputs & HSD_PAD_XY;
}

bool ftPe_8011BA54(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool float_input = checkStartFloatInput(gobj);
    if (fp->kind == FTKIND_PEACH && fp->fv.pe.has_float && float_input) {
        ftPe_8011BB6C(gobj, true);
        return true;
    }
    return false;
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftPe_8011BAD8(HSD_GObj*)
{
    // clang-format off
    nofralloc
/* 8011BAD8 001186B8  7C 08 02 A6 */	mflr r0
/* 8011BADC 001186BC  90 01 00 04 */	stw r0, 4(r1)
/* 8011BAE0 001186C0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8011BAE4 001186C4  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 8011BAE8 001186C8  80 06 00 04 */	lwz r0, 4(r6)
/* 8011BAEC 001186CC  2C 00 00 09 */	cmpwi r0, 9
/* 8011BAF0 001186D0  40 82 00 68 */	bne lbl_8011BB58
/* 8011BAF4 001186D4  C0 26 00 84 */	lfs f1, 0x84(r6)
/* 8011BAF8 001186D8  C0 02 9D E0 */	lfs f0, ftPe_Float_804D97C0
/* 8011BAFC 001186DC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BB00 001186E0  4C 40 13 82 */	cror 2, 0, 2
/* 8011BB04 001186E4  40 82 00 54 */	bne lbl_8011BB58
/* 8011BB08 001186E8  80 06 22 2C */	lwz r0, 0x222c(r6)
/* 8011BB0C 001186EC  2C 00 00 00 */	cmpwi r0, 0
/* 8011BB10 001186F0  41 82 00 48 */	beq lbl_8011BB58
/* 8011BB14 001186F4  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8011BB18 001186F8  38 A0 00 01 */	li r5, 1
/* 8011BB1C 001186FC  C0 26 06 24 */	lfs f1, 0x624(r6)
/* 8011BB20 00118700  C0 04 00 70 */	lfs f0, 0x70(r4)
/* 8011BB24 00118704  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BB28 00118708  4C 41 13 82 */	cror 2, 1, 2
/* 8011BB2C 0011870C  41 82 00 14 */	beq lbl_8011BB40
/* 8011BB30 00118710  80 06 06 5C */	lwz r0, 0x65c(r6)
/* 8011BB34 00118714  54 00 05 2B */	rlwinm. r0, r0, 0, 0x14, 0x15
/* 8011BB38 00118718  40 82 00 08 */	bne lbl_8011BB40
/* 8011BB3C 0011871C  38 A0 00 00 */	li r5, 0
lbl_8011BB40:
/* 8011BB40 00118720  2C 05 00 00 */	cmpwi r5, 0
/* 8011BB44 00118724  41 82 00 14 */	beq lbl_8011BB58
/* 8011BB48 00118728  38 80 00 01 */	li r4, 1
/* 8011BB4C 0011872C  48 00 00 21 */	bl ftPe_8011BB6C
/* 8011BB50 00118730  38 60 00 01 */	li r3, 1
/* 8011BB54 00118734  48 00 00 08 */	b lbl_8011BB5C
lbl_8011BB58:
/* 8011BB58 00118738  38 60 00 00 */	li r3, 0
lbl_8011BB5C:
/* 8011BB5C 0011873C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8011BB60 00118740  38 21 00 08 */	addi r1, r1, 8
/* 8011BB64 00118744  7C 08 03 A6 */	mtlr r0
/* 8011BB68 00118748  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

bool ftPe_8011BAD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_PEACH) {
        if (fp->self_vel.y <= 0 && fp->fv.pe.has_float) {
            if (ftPe_Float_CheckContinueInput(fp)) {
                ftPe_8011BB6C(gobj, true);
                return true;
            }
        }
    }
    return false;
}
#endif

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_8011BB6C(HSD_GObj*, bool)
{ // clang-format off
    nofralloc
/* 8011BB6C 0011874C  7C 08 02 A6 */	mflr r0
/* 8011BB70 00118750  38 A0 00 00 */	li r5, 0
/* 8011BB74 00118754  90 01 00 04 */	stw r0, 4(r1)
/* 8011BB78 00118758  38 C0 00 00 */	li r6, 0
/* 8011BB7C 0011875C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8011BB80 00118760  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8011BB84 00118764  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8011BB88 00118768  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8011BB8C 0011876C  7C 9D 23 78 */	mr r29, r4
/* 8011BB90 00118770  38 80 01 55 */	li r4, 0x155
/* 8011BB94 00118774  93 81 00 20 */	stw r28, 0x20(r1)
/* 8011BB98 00118778  7C 7C 1B 78 */	mr r28, r3
/* 8011BB9C 0011877C  C0 22 9D E0 */	lfs f1, ftPe_Float_804D97C0
/* 8011BBA0 00118780  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8011BBA4 00118784  FC 60 08 90 */	fmr f3, f1
/* 8011BBA8 00118788  C0 42 9D E4 */	lfs f2, ftPe_Float_804D97C4
/* 8011BBAC 0011878C  83 DF 02 D4 */	lwz r30, 0x2d4(r31)
/* 8011BBB0 00118790  4B F4 D7 FD */	bl Fighter_ChangeMotionState
/* 8011BBB4 00118794  38 00 00 00 */	li r0, 0
/* 8011BBB8 00118798  2C 1D 00 00 */	cmpwi r29, 0
/* 8011BBBC 0011879C  90 1F 22 2C */	stw r0, 0x222c(r31)
/* 8011BBC0 001187A0  41 82 00 0C */	beq lbl_8011BBCC
/* 8011BBC4 001187A4  C0 1E 00 0C */	lfs f0, 0xc(r30)
/* 8011BBC8 001187A8  D0 1F 22 30 */	stfs f0, 0x2230(r31)
lbl_8011BBCC:
/* 8011BBCC 001187AC  C0 02 9D E0 */	lfs f0, ftPe_Float_804D97C0
/* 8011BBD0 001187B0  38 A0 00 01 */	li r5, 1
/* 8011BBD4 001187B4  38 7F 00 00 */	addi r3, r31, 0
/* 8011BBD8 001187B8  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 8011BBDC 001187BC  38 80 00 01 */	li r4, 1
/* 8011BBE0 001187C0  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8011BBE4 001187C4  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 8011BBE8 001187C8  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 8011BBEC 001187CC  4B F5 94 21 */	bl ftParts_8007500C
/* 8011BBF0 001187D0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 8011BBF4 001187D4  54 60 20 36 */	slwi r0, r3, 4
/* 8011BBF8 001187D8  80 BC 00 2C */	lwz r5, 0x2c(r28)
/* 8011BBFC 001187DC  7F 83 E3 78 */	mr r3, r28
/* 8011BC00 001187E0  7C E4 00 2E */	lwzx r7, r4, r0
/* 8011BC04 001187E4  38 85 06 0C */	addi r4, r5, 0x60c
/* 8011BC08 001187E8  4C C6 31 82 */	crclr 6
/* 8011BC0C 001187EC  38 A0 00 00 */	li r5, 0
/* 8011BC10 001187F0  38 C0 04 D4 */	li r6, 0x4d4
/* 8011BC14 001187F4  4B F4 BA DD */	bl efAsync_Spawn
/* 8011BC18 001187F8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8011BC1C 001187FC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8011BC20 00118800  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8011BC24 00118804  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8011BC28 00118808  83 81 00 20 */	lwz r28, 0x20(r1)
/* 8011BC2C 0011880C  38 21 00 30 */	addi r1, r1, 0x30
/* 8011BC30 00118810  7C 08 03 A6 */	mtlr r0
/* 8011BC34 00118814  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_8011BB6C(HSD_GObj* gobj, bool arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    Fighter_ChangeMotionState(gobj, ftPe_MS_Float, 0, NULL, 0, 1, 0);
    fp->fv.pe.has_float = false;
    if (arg1) {
        fp->fv.pe.x4 = da->xC;
    }
    fp->self_vel.y = 0;
    fp->x2219_b0 = true;
    efAsync_Spawn(gobj, &fp->x60C, 0, 1236,
                  fp->parts[ftParts_8007500C(fp, FtPart_TransN)].joint);
}
#endif

static void updateFloatDir(HSD_GObj* gobj);

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ftPe_Float_Anim(HSD_GObj*)
{ // clang-format off
    nofralloc
/* 8011BC38 00118818  7C 08 02 A6 */	mflr r0
/* 8011BC3C 0011881C  90 01 00 04 */	stw r0, 4(r1)
/* 8011BC40 00118820  94 21 FF F8 */	stwu r1, -8(r1)
/* 8011BC44 00118824  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8011BC48 00118828  C0 02 9D E0 */	lfs f0, ftPe_Float_804D97C0
/* 8011BC4C 0011882C  C0 24 22 30 */	lfs f1, 0x2230(r4)
/* 8011BC50 00118830  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BC54 00118834  40 81 00 10 */	ble lbl_8011BC64
/* 8011BC58 00118838  C0 02 9D E4 */	lfs f0, ftPe_Float_804D97C4
/* 8011BC5C 0011883C  EC 01 00 28 */	fsubs f0, f1, f0
/* 8011BC60 00118840  D0 04 22 30 */	stfs f0, 0x2230(r4)
lbl_8011BC64:
/* 8011BC64 00118844  C0 24 22 30 */	lfs f1, 0x2230(r4)
/* 8011BC68 00118848  C0 02 9D E0 */	lfs f0, ftPe_Float_804D97C0
/* 8011BC6C 0011884C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BC70 00118850  4C 40 13 82 */	cror 2, 0, 2
/* 8011BC74 00118854  40 82 00 08 */	bne lbl_8011BC7C
/* 8011BC78 00118858  48 00 00 F5 */	bl updateFloatDir
lbl_8011BC7C:
/* 8011BC7C 0011885C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8011BC80 00118860  38 21 00 08 */	addi r1, r1, 8
/* 8011BC84 00118864  7C 08 03 A6 */	mtlr r0
/* 8011BC88 00118868  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftPe_Float_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.pe.x4 > 0) {
        fp->fv.pe.x4 -= 1;
    }
    if (fp->fv.pe.x4 <= 0) {
        updateFloatDir(gobj);
    }
}
#endif

void ftPe_Float_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!ftCo_SpecialAir_CheckInput(gobj) && !ftPe_8011BE80(gobj)) {
        /// @todo Call #checkContinueFloatInput
        bool float_input =
            fp->input.lstick.y >= p_ftCommonData->x70_someLStickYMax ||
            fp->input.held_inputs & HSD_PAD_XY;
        if (!float_input) {
            updateFloatDir(gobj);
        }
    }
}

void ftPe_Float_Phys(HSD_GObj* gobj)
{
    ftCommon_8007D268(GET_FIGHTER(gobj));
}

void ftPe_Float_Coll(HSD_GObj* gobj)
{
    ft_800831CC(gobj, ft_80096CC8, ft_80082B1C);
}

static float const lbl_804D97C8 = 1;
static float const lbl_804D97CC = 0;

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
static asm void updateFloatDir(HSD_GObj* gobj)
{
    // clang-format off
    nofralloc
/* 8011BD6C 0011894C  7C 08 02 A6 */	mflr r0
/* 8011BD70 00118950  90 01 00 04 */	stw r0, 4(r1)
/* 8011BD74 00118954  94 21 FF F8 */	stwu r1, -8(r1)
/* 8011BD78 00118958  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8011BD7C 0011895C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8011BD80 00118960  C0 45 06 20 */	lfs f2, 0x620(r5)
/* 8011BD84 00118964  C0 25 00 2C */	lfs f1, 0x2c(r5)
/* 8011BD88 00118968  C0 04 00 78 */	lfs f0, 0x78(r4)
/* 8011BD8C 0011896C  EC 22 00 72 */	fmuls f1, f2, f1
/* 8011BD90 00118970  80 A5 02 D4 */	lwz r5, 0x2d4(r5)
/* 8011BD94 00118974  FC 00 00 50 */	fneg f0, f0
/* 8011BD98 00118978  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8011BD9C 0011897C  40 81 00 0C */	ble lbl_8011BDA8
/* 8011BDA0 00118980  38 00 01 56 */	li r0, 0x156
/* 8011BDA4 00118984  48 00 00 08 */	b lbl_8011BDAC
lbl_8011BDA8:
/* 8011BDA8 00118988  38 00 01 57 */	li r0, 0x157
lbl_8011BDAC:
/* 8011BDAC 0011898C  7C 04 03 78 */	mr r4, r0
/* 8011BDB0 00118990  2C 04 01 56 */	cmpwi r4, 0x156
/* 8011BDB4 00118994  40 82 00 0C */	bne lbl_8011BDC0
/* 8011BDB8 00118998  C0 25 00 00 */	lfs f1, 0(r5)
/* 8011BDBC 0011899C  48 00 00 08 */	b lbl_8011BDC4
lbl_8011BDC0:
/* 8011BDC0 001189A0  C0 25 00 04 */	lfs f1, 4(r5)
lbl_8011BDC4:
/* 8011BDC4 001189A4  C0 05 00 08 */	lfs f0, 8(r5)
/* 8011BDC8 001189A8  38 A0 00 02 */	li r5, 2
/* 8011BDCC 001189AC  C0 42 9D E8 */	lfs f2, lbl_804D97C8
/* 8011BDD0 001189B0  38 C0 00 00 */	li r6, 0
/* 8011BDD4 001189B4  EC 21 00 28 */	fsubs f1, f1, f0
/* 8011BDD8 001189B8  C0 62 9D EC */	lfs f3, lbl_804D97CC
/* 8011BDDC 001189BC  4B F4 D5 D1 */	bl Fighter_ChangeMotionState
/* 8011BDE0 001189C0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8011BDE4 001189C4  38 21 00 08 */	addi r1, r1, 8
/* 8011BDE8 001189C8  7C 08 03 A6 */	mtlr r0
/* 8011BDEC 001189CC  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static ftPeach_MotionState getFloatDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->input.lstick.x * fp->facing_dir > -p_ftCommonData->x78
               ? ftPe_MS_FloatFallF
               : ftPe_MS_FloatFallB;
}

static void updateFloatDir(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPe_DatAttrs* da = fp->dat_attrs;
    ftPeach_MotionState msid = getFloatDir(gobj);
    float anim_start = msid == ftPe_MS_FloatFallF ? da->floatfallf_anim_start
                                                  : da->floatfallb_anim_start;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_KeepGfx, NULL,
                              anim_start - da->floatfall_anim_start_offset,
                              lbl_804D97C8, lbl_804D97CC);
}
#endif
