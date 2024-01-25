#include "ftCommon/forward.h"

#include "ftCo_DamageBind.h"

#include "ftCo_DamageFall.h"
#include "ftCo_Lift.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ft_0D14.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <placeholder.h>
#include <stddef.h>

#ifdef WIP
#pragma force_active on
#endif

/* literal */ double const ftCo_804D8D38 = S32_TO_F32;
/* literal */ float const ftCo_804D8D40 = 0;
/* literal */ float const ftCo_804D8D44 = 1;

bool ftCo_800C44CC(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860 == 12 && !fp->x2228_b2) {
        switch (fp->x2070.x2071_b0_3) {
        case 5:
        case 9:
        case 11:
        case 12:
            return false;
        default:
            ftCo_800C4550(gobj);
            return true;
        }
    }
    return false;
}

ASM void ftCo_800C4550(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    if (fp->ground_or_air == GA_Air) {
        ftCo_80090780(gobj);
    } else {
        Fighter_ChangeMotionState(gobj, ftCo_MS_DamageBind, Ft_MF_None, 0, 1,
                                  0, NULL);
        ftCommon_8007DBCC(
            fp, 0,
            fp->dmg.x1830_percent * p_ftCommonData->x66C +
                (p_ftCommonData->x65C * (p_ftCommonData->x660 -
                                         Player_GetHandicap(fp->player_id)) +
                 p_ftCommonData->x658 +
                 p_ftCommonData->x664 *
                     (p_ftCommonData->x668 -
                      (Player_80033BB8(fp->player_id) + 1))));
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C4550 000C1130  7C 08 02 A6 */	mflr r0
/* 800C4554 000C1134  90 01 00 04 */	stw r0, 4(r1)
/* 800C4558 000C1138  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800C455C 000C113C  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 800C4560 000C1140  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800C4564 000C1144  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800C4568 000C1148  7C 7E 1B 78 */	mr r30, r3
/* 800C456C 000C114C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 800C4570 000C1150  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 800C4574 000C1154  4B FB 95 E5 */	bl ftCommon_8007DB58
/* 800C4578 000C1158  7F C3 F3 78 */	mr r3, r30
/* 800C457C 000C115C  4B FD 2F 91 */	bl ftCo_8009750C
/* 800C4580 000C1160  7F C3 F3 78 */	mr r3, r30
/* 800C4584 000C1164  48 01 8B E5 */	bl ftCo_800DD168
/* 800C4588 000C1168  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 800C458C 000C116C  2C 00 00 01 */	cmpwi r0, 1
/* 800C4590 000C1170  40 82 00 10 */	bne lbl_800C45A0
/* 800C4594 000C1174  7F C3 F3 78 */	mr r3, r30
/* 800C4598 000C1178  4B FC C1 E9 */	bl ftCo_80090780
/* 800C459C 000C117C  48 00 00 B0 */	b lbl_800C464C
lbl_800C45A0:
/* 800C45A0 000C1180  C0 22 93 60 */	lfs f1, ftCo_804D8D40
/* 800C45A4 000C1184  7F C3 F3 78 */	mr r3, r30
/* 800C45A8 000C1188  C0 42 93 64 */	lfs f2, ftCo_804D8D44
/* 800C45AC 000C118C  38 80 01 2C */	li r4, 0x12c
/* 800C45B0 000C1190  FC 60 08 90 */	fmr f3, f1
/* 800C45B4 000C1194  38 A0 00 00 */	li r5, 0
/* 800C45B8 000C1198  38 C0 00 00 */	li r6, 0
/* 800C45BC 000C119C  4B FA 4D F1 */	bl Fighter_ChangeMotionState
/* 800C45C0 000C11A0  83 CD AE B4 */	lwz r30, p_ftCommonData
/* 800C45C4 000C11A4  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800C45C8 000C11A8  4B F6 F5 F1 */	bl Player_80033BB8
/* 800C45CC 000C11AC  38 03 00 01 */	addi r0, r3, 1
/* 800C45D0 000C11B0  C8 62 93 58 */	lfd f3, ftCo_804D8D38
/* 800C45D4 000C11B4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C45D8 000C11B8  C0 3E 06 68 */	lfs f1, 0x668(r30)
/* 800C45DC 000C11BC  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C45E0 000C11C0  3F E0 43 30 */	lis r31, 0x4330
/* 800C45E4 000C11C4  C0 1E 06 64 */	lfs f0, 0x664(r30)
/* 800C45E8 000C11C8  93 E1 00 18 */	stw r31, 0x18(r1)
/* 800C45EC 000C11CC  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800C45F0 000C11D0  C8 41 00 18 */	lfd f2, 0x18(r1)
/* 800C45F4 000C11D4  EC 42 18 28 */	fsubs f2, f2, f3
/* 800C45F8 000C11D8  EC 21 10 28 */	fsubs f1, f1, f2
/* 800C45FC 000C11DC  EF E0 00 72 */	fmuls f31, f0, f1
/* 800C4600 000C11E0  4B F6 F1 99 */	bl Player_GetHandicap
/* 800C4604 000C11E4  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 800C4608 000C11E8  C8 22 93 58 */	lfd f1, ftCo_804D8D38
/* 800C460C 000C11EC  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C4610 000C11F0  7F A3 EB 78 */	mr r3, r29
/* 800C4614 000C11F4  C0 9E 06 60 */	lfs f4, 0x660(r30)
/* 800C4618 000C11F8  38 80 00 00 */	li r4, 0
/* 800C461C 000C11FC  93 E1 00 10 */	stw r31, 0x10(r1)
/* 800C4620 000C1200  C0 7E 06 5C */	lfs f3, 0x65c(r30)
/* 800C4624 000C1204  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800C4628 000C1208  C0 5E 06 58 */	lfs f2, 0x658(r30)
/* 800C462C 000C120C  EC A0 08 28 */	fsubs f5, f0, f1
/* 800C4630 000C1210  C0 3D 18 30 */	lfs f1, 0x1830(r29)
/* 800C4634 000C1214  C0 1E 06 6C */	lfs f0, 0x66c(r30)
/* 800C4638 000C1218  EC 84 28 28 */	fsubs f4, f4, f5
/* 800C463C 000C121C  EC 43 11 3A */	fmadds f2, f3, f4, f2
/* 800C4640 000C1220  EC 42 F8 2A */	fadds f2, f2, f31
/* 800C4644 000C1224  EC 21 10 3A */	fmadds f1, f1, f0, f2
/* 800C4648 000C1228  4B FB 95 85 */	bl ftCommon_8007DBCC
lbl_800C464C:
/* 800C464C 000C122C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800C4650 000C1230  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800C4654 000C1234  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800C4658 000C1238  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800C465C 000C123C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800C4660 000C1240  38 21 00 38 */	addi r1, r1, 0x38
/* 800C4664 000C1244  7C 08 03 A6 */	mtlr r0
/* 800C4668 000C1248  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_DamageBind_Anim(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= p_ftCommonData->x670;
    ftCommon_8007DC08(fp, p_ftCommonData->x674);
    if (fp->x1A4C <= 0) {
        ft_8008A2BC(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C466C 000C124C  7C 08 02 A6 */	mflr r0
/* 800C4670 000C1250  90 01 00 04 */	stw r0, 4(r1)
/* 800C4674 000C1254  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C4678 000C1258  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C467C 000C125C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C4680 000C1260  7C 7E 1B 78 */	mr r30, r3
/* 800C4684 000C1264  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800C4688 000C1268  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800C468C 000C126C  C0 03 06 70 */	lfs f0, 0x670(r3)
/* 800C4690 000C1270  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C4694 000C1274  7F E3 FB 78 */	mr r3, r31
/* 800C4698 000C1278  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C469C 000C127C  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800C46A0 000C1280  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800C46A4 000C1284  C0 24 06 74 */	lfs f1, 0x674(r4)
/* 800C46A8 000C1288  4B FB 95 61 */	bl ftCommon_8007DC08
/* 800C46AC 000C128C  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800C46B0 000C1290  C0 02 93 60 */	lfs f0, ftCo_804D8D40
/* 800C46B4 000C1294  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C46B8 000C1298  4C 40 13 82 */	cror 2, 0, 2
/* 800C46BC 000C129C  40 82 00 0C */	bne lbl_800C46C8
/* 800C46C0 000C12A0  7F C3 F3 78 */	mr r3, r30
/* 800C46C4 000C12A4  4B FC 5B F9 */	bl ft_8008A2BC
lbl_800C46C8:
/* 800C46C8 000C12A8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C46CC 000C12AC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C46D0 000C12B0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C46D4 000C12B4  38 21 00 18 */	addi r1, r1, 0x18
/* 800C46D8 000C12B8  7C 08 03 A6 */	mtlr r0
/* 800C46DC 000C12BC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_DamageBind_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageBind_Phys(ftCo_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftCo_DamageBind_Coll(ftCo_GObj* gobj)
{
    ft_80084280(gobj);
}
