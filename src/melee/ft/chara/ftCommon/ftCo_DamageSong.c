#include "ft/forward.h"

#include "ftCo_DamageSong.h"

#include "ftCo_0C35.h"
#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_0819.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0892.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

/* 0C3390 */ static void ftCo_800C3390(ftCo_GObj* gobj);
/* 0C3480 */ static void ftCo_800C3480(ftCo_GObj* gobj);

/* literal */ double const ftCo_804D8CC0 = S32_TO_F32;
/* literal */ float const ftCo_804D8CC8 = 0;
/* literal */ float const ftCo_804D8CCC = 1;

static inline float inlineA0(ftCo_Fighter* fp, bool arg1)
{
    float result =
        (fp->dmg.x1830_percent * p_ftCommonData->x638) +
        ((p_ftCommonData->x628 *
          (p_ftCommonData->x62C - Player_GetHandicap(fp->player_id))) +
         p_ftCommonData->x624 +
         p_ftCommonData->x630 *
             (p_ftCommonData->x634 - ((Player_80033BB8(fp->player_id)) + 1)));
    if (arg1) {
        result *= p_ftCommonData->x644;
    }
    return result;
}

ASM void ftCo_800C318C(ftCo_GObj* gobj, bool arg1)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSong, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007DBCC(fp, 0, inlineA0(fp, arg1));
}

#else /* clang-format off */
{ nofralloc
/* 800C318C 000BFD6C  7C 08 02 A6 */	mflr r0
/* 800C3190 000BFD70  90 01 00 04 */	stw r0, 4(r1)
/* 800C3194 000BFD74  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800C3198 000BFD78  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 800C319C 000BFD7C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800C31A0 000BFD80  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800C31A4 000BFD84  7C 7E 1B 78 */	mr r30, r3
/* 800C31A8 000BFD88  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800C31AC 000BFD8C  93 81 00 28 */	stw r28, 0x28(r1)
/* 800C31B0 000BFD90  7C 9C 23 78 */	mr r28, r4
/* 800C31B4 000BFD94  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800C31B8 000BFD98  4B FB A9 A1 */	bl ftCommon_8007DB58
/* 800C31BC 000BFD9C  7F C3 F3 78 */	mr r3, r30
/* 800C31C0 000BFDA0  4B FD 43 4D */	bl ftCo_8009750C
/* 800C31C4 000BFDA4  7F C3 F3 78 */	mr r3, r30
/* 800C31C8 000BFDA8  48 01 9F A1 */	bl ftCo_800DD168
/* 800C31CC 000BFDAC  C0 22 92 E8 */	lfs f1, ftCo_804D8CC8
/* 800C31D0 000BFDB0  7F C3 F3 78 */	mr r3, r30
/* 800C31D4 000BFDB4  C0 42 92 EC */	lfs f2, ftCo_804D8CCC
/* 800C31D8 000BFDB8  38 80 01 29 */	li r4, 0x129
/* 800C31DC 000BFDBC  FC 60 08 90 */	fmr f3, f1
/* 800C31E0 000BFDC0  38 A0 00 00 */	li r5, 0
/* 800C31E4 000BFDC4  38 C0 00 00 */	li r6, 0
/* 800C31E8 000BFDC8  4B FA 61 C5 */	bl Fighter_ChangeMotionState
/* 800C31EC 000BFDCC  83 CD AE B4 */	lwz r30, p_ftCommonData
/* 800C31F0 000BFDD0  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800C31F4 000BFDD4  4B F7 09 C5 */	bl Player_80033BB8
/* 800C31F8 000BFDD8  38 03 00 01 */	addi r0, r3, 1
/* 800C31FC 000BFDDC  C8 62 92 E0 */	lfd f3, ftCo_804D8CC0
/* 800C3200 000BFDE0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C3204 000BFDE4  C0 3E 06 34 */	lfs f1, 0x634(r30)
/* 800C3208 000BFDE8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800C320C 000BFDEC  3F E0 43 30 */	lis r31, 0x4330
/* 800C3210 000BFDF0  C0 1E 06 30 */	lfs f0, 0x630(r30)
/* 800C3214 000BFDF4  93 E1 00 20 */	stw r31, 0x20(r1)
/* 800C3218 000BFDF8  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800C321C 000BFDFC  C8 41 00 20 */	lfd f2, 0x20(r1)
/* 800C3220 000BFE00  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C3224 000BFE04  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C3228 000BFE08  EF E0 00 72 */	fmuls f31, f0, f1
/* 800C322C 000BFE0C  4B F7 05 6D */	bl Player_GetHandicap
/* 800C3230 000BFE10  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 800C3234 000BFE14  C8 22 92 E0 */	lfd f1, ftCo_804D8CC0
/* 800C3238 000BFE18  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C323C 000BFE1C  2C 1C 00 00 */	cmpwi r28, 0
/* 800C3240 000BFE20  C0 9E 06 2C */	lfs f4, 0x62c(r30)
/* 800C3244 000BFE24  93 E1 00 18 */	stw r31, 0x18(r1)
/* 800C3248 000BFE28  C0 7E 06 28 */	lfs f3, 0x628(r30)
/* 800C324C 000BFE2C  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 800C3250 000BFE30  C0 5E 06 24 */	lfs f2, 0x624(r30)
/* 800C3254 000BFE34  EC A0 08 28 */	fsubs f5, f0, f1
/* 800C3258 000BFE38  C0 3D 18 30 */	lfs f1, 0x1830(r29)
/* 800C325C 000BFE3C  C0 1E 06 38 */	lfs f0, 0x638(r30)
/* 800C3260 000BFE40  EC 84 28 28 */	fsubs f4, f4, f5
/* 800C3264 000BFE44  EC 43 11 3A */	fmadds f2, f3, f4, f2
/* 800C3268 000BFE48  EC 42 F8 2A */	fadds f2, f2, f31
/* 800C326C 000BFE4C  EC 21 10 3A */	fmadds f1, f1, f0, f2
/* 800C3270 000BFE50  41 82 00 0C */	beq lbl_800C327C
/* 800C3274 000BFE54  C0 1E 06 44 */	lfs f0, 0x644(r30)
/* 800C3278 000BFE58  EC 21 00 32 */	fmuls f1, f1, f0
lbl_800C327C:
/* 800C327C 000BFE5C  38 7D 00 00 */	addi r3, r29, 0
/* 800C3280 000BFE60  38 80 00 00 */	li r4, 0
/* 800C3284 000BFE64  4B FB A9 49 */	bl ftCommon_8007DBCC
/* 800C3288 000BFE68  80 01 00 44 */	lwz r0, 0x44(r1)
/* 800C328C 000BFE6C  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 800C3290 000BFE70  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800C3294 000BFE74  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800C3298 000BFE78  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 800C329C 000BFE7C  83 81 00 28 */	lwz r28, 0x28(r1)
/* 800C32A0 000BFE80  38 21 00 40 */	addi r1, r1, 0x40
/* 800C32A4 000BFE84  7C 08 03 A6 */	mtlr r0
/* 800C32A8 000BFE88  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline bool inlineB0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= p_ftCommonData->x63C;
    ftCommon_8007DC08(fp, p_ftCommonData->x640);
    if (fp->x1A4C <= 0) {
        ftCo_800C3480(gobj);
        return true;
    } else {
        return false;
    }
}

ASM void ftCo_DamageSong_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    if (!inlineB0(gobj) && !ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800C3390(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C32AC 000BFE8C  7C 08 02 A6 */	mflr r0
/* 800C32B0 000BFE90  90 01 00 04 */	stw r0, 4(r1)
/* 800C32B4 000BFE94  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C32B8 000BFE98  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C32BC 000BFE9C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C32C0 000BFEA0  7C 7E 1B 78 */	mr r30, r3
/* 800C32C4 000BFEA4  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C32C8 000BFEA8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800C32CC 000BFEAC  C0 03 06 3C */	lfs f0, 0x63c(r3)
/* 800C32D0 000BFEB0  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C32D4 000BFEB4  7F E3 FB 78 */	mr r3, r31
/* 800C32D8 000BFEB8  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C32DC 000BFEBC  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800C32E0 000BFEC0  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C32E4 000BFEC4  C0 24 06 40 */	lfs f1, 0x640(r4)
/* 800C32E8 000BFEC8  4B FB A9 21 */	bl ftCommon_8007DC08
/* 800C32EC 000BFECC  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C32F0 000BFED0  C0 02 92 E8 */	lfs f0, ftCo_804D8CC8
/* 800C32F4 000BFED4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C32F8 000BFED8  4C 40 13 82 */	cror 2, 0, 2
/* 800C32FC 000BFEDC  40 82 00 14 */	bne lbl_800C3310
/* 800C3300 000BFEE0  7F C3 F3 78 */	mr r3, r30
/* 800C3304 000BFEE4  48 00 01 7D */	bl ftCo_800C3480
/* 800C3308 000BFEE8  38 00 00 01 */	li r0, 1
/* 800C330C 000BFEEC  48 00 00 08 */	b lbl_800C3314
lbl_800C3310:
/* 800C3310 000BFEF0  38 00 00 00 */	li r0, 0
lbl_800C3314:
/* 800C3314 000BFEF4  2C 00 00 00 */	cmpwi r0, 0
/* 800C3318 000BFEF8  40 82 00 1C */	bne lbl_800C3334
/* 800C331C 000BFEFC  7F C3 F3 78 */	mr r3, r30
/* 800C3320 000BFF00  4B FA BF 19 */	bl ftAnim_IsFramesRemaining
/* 800C3324 000BFF04  2C 03 00 00 */	cmpwi r3, 0
/* 800C3328 000BFF08  40 82 00 0C */	bne lbl_800C3334
/* 800C332C 000BFF0C  7F C3 F3 78 */	mr r3, r30
/* 800C3330 000BFF10  48 00 00 61 */	bl ftCo_800C3390
lbl_800C3334:
/* 800C3334 000BFF14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C3338 000BFF18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C333C 000BFF1C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C3340 000BFF20  38 21 00 18 */	addi r1, r1, 0x18
/* 800C3344 000BFF24  7C 08 03 A6 */	mtlr r0
/* 800C3348 000BFF28  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_DamageSong_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageSong_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSong_Coll(ftCo_GObj* gobj)
{
    ft_80084280(gobj);
}

ASM void ftCo_800C3390(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSongWait,
                              Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim, 0, 1, 0,
                              NULL);
}

#else /* clang-format off */
{ nofralloc
/* 800C3390 000BFF70  7C 08 02 A6 */	mflr r0
/* 800C3394 000BFF74  38 80 01 2A */	li r4, 0x12a
/* 800C3398 000BFF78  90 01 00 04 */	stw r0, 4(r1)
/* 800C339C 000BFF7C  38 A0 10 80 */	li r5, 0x1080
/* 800C33A0 000BFF80  38 C0 00 00 */	li r6, 0
/* 800C33A4 000BFF84  94 21 FF F8 */	stwu r1, -8(r1)
/* 800C33A8 000BFF88  C0 22 92 E8 */	lfs f1, ftCo_804D8CC8
/* 800C33AC 000BFF8C  C0 42 92 EC */	lfs f2, ftCo_804D8CCC
/* 800C33B0 000BFF90  FC 60 08 90 */	fmr f3, f1
/* 800C33B4 000BFF94  4B FA 5F F9 */	bl Fighter_ChangeMotionState
/* 800C33B8 000BFF98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C33BC 000BFF9C  38 21 00 08 */	addi r1, r1, 8
/* 800C33C0 000BFFA0  7C 08 03 A6 */	mtlr r0
/* 800C33C4 000BFFA4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_DamageSongWait_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineB0(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 800C33C8 000BFFA8  7C 08 02 A6 */	mflr r0
/* 800C33CC 000BFFAC  90 01 00 04 */	stw r0, 4(r1)
/* 800C33D0 000BFFB0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C33D4 000BFFB4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C33D8 000BFFB8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C33DC 000BFFBC  7C 7E 1B 78 */	mr r30, r3
/* 800C33E0 000BFFC0  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C33E4 000BFFC4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800C33E8 000BFFC8  C0 03 06 3C */	lfs f0, 0x63c(r3)
/* 800C33EC 000BFFCC  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C33F0 000BFFD0  7F E3 FB 78 */	mr r3, r31
/* 800C33F4 000BFFD4  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C33F8 000BFFD8  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800C33FC 000BFFDC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C3400 000BFFE0  C0 24 06 40 */	lfs f1, 0x640(r4)
/* 800C3404 000BFFE4  4B FB A8 05 */	bl ftCommon_8007DC08
/* 800C3408 000BFFE8  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C340C 000BFFEC  C0 02 92 E8 */	lfs f0, ftCo_804D8CC8
/* 800C3410 000BFFF0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C3414 000BFFF4  4C 40 13 82 */	cror 2, 0, 2
/* 800C3418 000BFFF8  40 82 00 0C */	bne lbl_800C3424
/* 800C341C 000BFFFC  7F C3 F3 78 */	mr r3, r30
/* 800C3420 000C0000  48 00 00 61 */	bl ftCo_800C3480
lbl_800C3424:
/* 800C3424 000C0004  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C3428 000C0008  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C342C 000C000C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C3430 000C0010  38 21 00 18 */	addi r1, r1, 0x18
/* 800C3434 000C0014  7C 08 03 A6 */	mtlr r0
/* 800C3438 000C0018  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_DamageSongWait_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageSongWait_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSongWait_Coll(ftCo_GObj* gobj)
{
    ft_80084280(gobj);
}

ASM void ftCo_800C3480(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageSongRv, Ft_MF_None, 0, 1, 0,
                              NULL);
}

#else /* clang-format off */
{ nofralloc
/* 800C3480 000C0060  7C 08 02 A6 */	mflr r0
/* 800C3484 000C0064  38 80 01 2B */	li r4, 0x12b
/* 800C3488 000C0068  90 01 00 04 */	stw r0, 4(r1)
/* 800C348C 000C006C  38 A0 00 00 */	li r5, 0
/* 800C3490 000C0070  38 C0 00 00 */	li r6, 0
/* 800C3494 000C0074  94 21 FF F8 */	stwu r1, -8(r1)
/* 800C3498 000C0078  C0 22 92 E8 */	lfs f1, ftCo_804D8CC8
/* 800C349C 000C007C  C0 42 92 EC */	lfs f2, ftCo_804D8CCC
/* 800C34A0 000C0080  FC 60 08 90 */	fmr f3, f1
/* 800C34A4 000C0084  4B FA 5F 09 */	bl Fighter_ChangeMotionState
/* 800C34A8 000C0088  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800C34AC 000C008C  38 21 00 08 */	addi r1, r1, 8
/* 800C34B0 000C0090  7C 08 03 A6 */	mtlr r0
/* 800C34B4 000C0094  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_DamageSongRv_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_DamageSongRv_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageSongRv_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageSongRv_Coll(ftCo_GObj* gobj)
{
    ft_80084280(gobj);
}

bool ftCo_800C3538(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2222_b2) {
        return false;
    }
    switch (fp->x2070.x2071_b0_3) {
    case 9:
    case 10:
    case 11:
        return false;
    default:
        ftCo_800C3598(gobj);
        return true;
    }
}
