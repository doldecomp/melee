#include <platform.h>
#include "ft/forward.h"

#include "ftCo_Down.h"

#include "ftCo_DownAttack.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm bool ftCo_Down_CheckInput(ftCo_GObj* gobj)
{ // clang-format off
    nofralloc
/* 80098214 00094DF4  7C 08 02 A6 */	mflr r0
/* 80098218 00094DF8  90 01 00 04 */	stw r0, 4(r1)
/* 8009821C 00094DFC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80098220 00094E00  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80098224 00094E04  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80098228 00094E08  7C 7E 1B 78 */	mr r30, r3
/* 8009822C 00094E0C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80098230 00094E10  7F E3 FB 78 */	mr r3, r31
/* 80098234 00094E14  48 04 74 45 */	bl ftCo_800DF678
/* 80098238 00094E18  2C 03 00 00 */	cmpwi r3, 0
/* 8009823C 00094E1C  41 82 00 0C */	beq lbl_80098248
/* 80098240 00094E20  C0 5F 06 38 */	lfs f2, 0x638(r31)
/* 80098244 00094E24  48 00 00 68 */	b lbl_800982AC
lbl_80098248:
/* 80098248 00094E28  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8009824C 00094E2C  C0 02 8C 40 */	lfs f0, 0.0f
/* 80098250 00094E30  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80098254 00094E34  40 80 00 08 */	bge lbl_8009825C
/* 80098258 00094E38  FC 20 08 50 */	fneg f1, f1
lbl_8009825C:
/* 8009825C 00094E3C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80098260 00094E40  C0 03 02 48 */	lfs f0, 0x248(r3)
/* 80098264 00094E44  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80098268 00094E48  4C 41 13 82 */	cror 2, 1, 2
/* 8009826C 00094E4C  40 82 00 24 */	bne lbl_80098290
/* 80098270 00094E50  7F E3 FB 78 */	mr r3, r31
/* 80098274 00094E54  4B FE 56 F1 */	bl ftCo_GetLStickAngle
/* 80098278 00094E58  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009827C 00094E5C  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 80098280 00094E60  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80098284 00094E64  40 80 00 0C */	bge lbl_80098290
/* 80098288 00094E68  38 00 00 01 */	li r0, 1
/* 8009828C 00094E6C  48 00 00 08 */	b lbl_80098294
lbl_80098290:
/* 80098290 00094E70  38 00 00 00 */	li r0, 0
lbl_80098294:
/* 80098294 00094E74  2C 00 00 00 */	cmpwi r0, 0
/* 80098298 00094E78  41 82 00 0C */	beq lbl_800982A4
/* 8009829C 00094E7C  C0 5F 06 20 */	lfs f2, 0x620(r31)
/* 800982A0 00094E80  48 00 00 0C */	b lbl_800982AC
lbl_800982A4:
/* 800982A4 00094E84  38 60 00 00 */	li r3, 0
/* 800982A8 00094E88  48 00 00 64 */	b lbl_8009830C
lbl_800982AC:
/* 800982AC 00094E8C  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800982B0 00094E90  C0 02 8C 40 */	lfs f0, 0.0f
/* 800982B4 00094E94  EC 22 00 72 */	fmuls f1, f2, f1
/* 800982B8 00094E98  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800982BC 00094E9C  4C 41 13 82 */	cror 2, 1, 2
/* 800982C0 00094EA0  40 82 00 24 */	bne lbl_800982E4
/* 800982C4 00094EA4  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800982C8 00094EA8  2C 00 00 B8 */	cmpwi r0, 0xb8
/* 800982CC 00094EAC  40 82 00 0C */	bne lbl_800982D8
/* 800982D0 00094EB0  38 00 00 BC */	li r0, 0xbc
/* 800982D4 00094EB4  48 00 00 08 */	b lbl_800982DC
lbl_800982D8:
/* 800982D8 00094EB8  38 00 00 C4 */	li r0, 0xc4
lbl_800982DC:
/* 800982DC 00094EBC  7C 04 03 78 */	mr r4, r0
/* 800982E0 00094EC0  48 00 00 20 */	b lbl_80098300
lbl_800982E4:
/* 800982E4 00094EC4  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800982E8 00094EC8  2C 00 00 B8 */	cmpwi r0, 0xb8
/* 800982EC 00094ECC  40 82 00 0C */	bne lbl_800982F8
/* 800982F0 00094ED0  38 00 00 BD */	li r0, 0xbd
/* 800982F4 00094ED4  48 00 00 08 */	b lbl_800982FC
lbl_800982F8:
/* 800982F8 00094ED8  38 00 00 C5 */	li r0, 0xc5
lbl_800982FC:
/* 800982FC 00094EDC  7C 04 03 78 */	mr r4, r0
lbl_80098300:
/* 80098300 00094EE0  7F C3 F3 78 */	mr r3, r30
/* 80098304 00094EE4  48 00 00 21 */	bl ftCo_80098324
/* 80098308 00094EE8  38 60 00 01 */	li r3, 1
lbl_8009830C:
/* 8009830C 00094EEC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80098310 00094EF0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80098314 00094EF4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80098318 00094EF8  38 21 00 18 */	addi r1, r1, 0x18
/* 8009831C 00094EFC  7C 08 03 A6 */	mtlr r0
/* 80098320 00094F00  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

static inline bool inlineA0(ftCo_Fighter* fp)
{
    if (ABS(fp->input.lstick.x) >= p_ftCommonData->x248 &&
        ftCo_GetLStickAngle(fp) < p_ftCommonData->x20)
    {
        return true;
    } else {
        return false;
    }
}

bool ftCo_Down_CheckInput(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    float stick_x;
    if (ftCo_800DF678(fp)) {
        stick_x = fp->input.cstick.x;
    } else if (inlineA0(fp)) {
        stick_x = fp->input.lstick.x;
    } else {
        return false;
    }
    {
        FtMotionId msid;
        if (stick_x * fp->facing_dir >= 0) {
            msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownFowardU
                                                      : ftCo_MS_DownFowardD;
        } else {
            msid = fp->motion_id == ftCo_MS_DownWaitU ? ftCo_MS_DownBackU
                                                      : ftCo_MS_DownBackD;
        }
        ftCo_80098324(gobj, msid);
    }
    return true;
}
#endif

#ifdef MWERKS_GEKKO
#pragma push
asm void ftCo_80098324(ftCo_GObj* gobj, FtMotionId msid)
{ // clang-format off
    nofralloc
/* 80098324 00094F04  7C 08 02 A6 */	mflr r0
/* 80098328 00094F08  38 A0 00 00 */	li r5, 0
/* 8009832C 00094F0C  90 01 00 04 */	stw r0, 4(r1)
/* 80098330 00094F10  38 C0 00 00 */	li r6, 0
/* 80098334 00094F14  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80098338 00094F18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8009833C 00094F1C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80098340 00094F20  7C 7E 1B 78 */	mr r30, r3
/* 80098344 00094F24  C0 22 8C 40 */	lfs f1, 0.0f
/* 80098348 00094F28  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009834C 00094F2C  FC 60 08 90 */	fmr f3, f1
/* 80098350 00094F30  C0 42 8C 44 */	lfs f2, 1.0f
/* 80098354 00094F34  4B FD 10 59 */	bl Fighter_ChangeMotionState
/* 80098358 00094F38  7F C3 F3 78 */	mr r3, r30
/* 8009835C 00094F3C  4B FD 68 49 */	bl ftAnim_8006EBA4
/* 80098360 00094F40  7F E3 FB 78 */	mr r3, r31
/* 80098364 00094F44  4B FE 49 85 */	bl ftCommon_8007CCE8
/* 80098368 00094F48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8009836C 00094F4C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80098370 00094F50  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80098374 00094F54  38 21 00 20 */	addi r1, r1, 0x20
/* 80098378 00094F58  7C 08 03 A6 */	mtlr r0
/* 8009837C 00094F5C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ftCo_80098324(ftCo_GObj* gobj, FtMotionId msid)
{
    ftCo_Fighter* fp = gobj->user_data;
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_None, 0, 1, 0, NULL);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007CCE8(fp);
}
#endif

void ftCo_Down_Anim(ftCo_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftCo_Down_IASA(ftCo_GObj* gobj) {}

void ftCo_Down_Phys(ftCo_GObj* gobj)
{
    ft_80084FA8(gobj);
}

void ftCo_Down_Coll(ftCo_GObj* gobj)
{
    ft_80084104(gobj);
}

static inline bool inlineB0(ftCo_Fighter* fp)
{
    if (fp->x67C < p_ftCommonData->x24C || fp->x67D < p_ftCommonData->x24C) {
        return true;
    }
    return false;
}

bool ftCo_80098400(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (inlineB0(fp) || ftCo_800DF644(fp)) {
        FtMotionId msid = fp->motion_id == ftCo_MS_DownBoundU
                              ? ftCo_MS_DownAttackU
                              : ftCo_MS_DownAttackD;
        ftCo_8009856C(gobj, msid);
        return true;
    }
    return false;
}
