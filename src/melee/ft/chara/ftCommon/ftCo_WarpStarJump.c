#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>

#include "ftCo_WarpStarJump.h"

#include "ft/ft_0C31.h"
#include "ft/ftanim.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "it/item.h"
#include "it/items/itwstar.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <placeholder.h>
#include <dolphin/mtx.h>

#ifdef WIP
#pragma force_active on
#endif

/* 0C4858 */ static void ftCo_800C4858(ftCo_GObj* gobj);
/* 0C48AC */ static void ftCo_800C48AC(ftCo_GObj* gobj);
/* 0C4A38 */ static void ftCo_800C4A38(ftCo_GObj* gobj);

/* literal */ float const ftCo_804D8D48 = 0;
/* literal */ float const ftCo_804D8D4C = 1;
/* literal */ float const ftCo_804D8D50 = M_PI_2;
/* literal */ SDATA char ftCo_804D3C58[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3C60[] = "jobj";

ASM void ftCo_800C4724(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    it_80294430(fp->item_gobj, fp->co_attrs.x14C, fp->x2C4.y);
    fp->mv.co.warpstarjump.facing_dir = fp->facing_dir;
    fp->facing_dir = 0;
    fp->mv.co.warpstarjump.x1C = 120;
    fp->mv.co.warpstarjump.cur_pos = fp->cur_pos;
    fp->mv.co.warpstarjump.self_vel.x = fp->mv.co.warpstarjump.self_vel.y =
        fp->mv.co.warpstarjump.self_vel.z = 0;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_WarpStarJump, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftColl_8007B6A0(gobj);
    fp->take_dmg_cb = ftCo_800C4858;
    fp->death2_cb = ftCo_800C48AC;
    fp->x2219_b2 = true;
    fp->x2222_b7 = true;
    fp->x221E_b2 = true;
    ftCommon_8007E2FC(gobj);
    HSD_JObjAddAnim(jobj, it_80294364(fp->item_gobj), NULL, NULL);
    ftAnim_80070734(jobj, 0);
    HSD_JObjAnim(jobj);
}

#else /* clang-format off */
{ nofralloc
/* 800C4724 000C1304  7C 08 02 A6 */	mflr r0
/* 800C4728 000C1308  90 01 00 04 */	stw r0, 4(r1)
/* 800C472C 000C130C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C4730 000C1310  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C4734 000C1314  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800C4738 000C1318  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800C473C 000C131C  7C 7D 1B 78 */	mr r29, r3
/* 800C4740 000C1320  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C4744 000C1324  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 800C4748 000C1328  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C474C 000C132C  C0 5F 02 74 */	lfs f2, 0x274(r31)
/* 800C4750 000C1330  C0 3F 02 C8 */	lfs f1, 0x2c8(r31)
/* 800C4754 000C1334  48 1C FC DD */	bl it_80294430
/* 800C4758 000C1338  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C475C 000C133C  38 00 00 78 */	li r0, 0x78
/* 800C4760 000C1340  38 7F 00 00 */	addi r3, r31, 0
/* 800C4764 000C1344  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 800C4768 000C1348  C0 02 93 68 */	lfs f0, ftCo_804D8D48
/* 800C476C 000C134C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C4770 000C1350  90 1F 23 5C */	stw r0, 0x235c(r31)
/* 800C4774 000C1354  80 9F 00 B0 */	lwz r4, 0xb0(r31)
/* 800C4778 000C1358  80 1F 00 B4 */	lwz r0, 0xb4(r31)
/* 800C477C 000C135C  90 9F 23 40 */	stw r4, 0x2340(r31)
/* 800C4780 000C1360  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 800C4784 000C1364  80 1F 00 B8 */	lwz r0, 0xb8(r31)
/* 800C4788 000C1368  90 1F 23 48 */	stw r0, 0x2348(r31)
/* 800C478C 000C136C  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 800C4790 000C1370  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 800C4794 000C1374  D0 1F 23 4C */	stfs f0, 0x234c(r31)
/* 800C4798 000C1378  4B FB 8E 3D */	bl ftCommon_8007D5D4
/* 800C479C 000C137C  C0 22 93 68 */	lfs f1, ftCo_804D8D48
/* 800C47A0 000C1380  7F A3 EB 78 */	mr r3, r29
/* 800C47A4 000C1384  C0 42 93 6C */	lfs f2, ftCo_804D8D4C
/* 800C47A8 000C1388  38 80 01 31 */	li r4, 0x131
/* 800C47AC 000C138C  FC 60 08 90 */	fmr f3, f1
/* 800C47B0 000C1390  38 A0 00 00 */	li r5, 0
/* 800C47B4 000C1394  38 C0 00 00 */	li r6, 0
/* 800C47B8 000C1398  4B FA 4B F5 */	bl Fighter_ChangeMotionState
/* 800C47BC 000C139C  7F A3 EB 78 */	mr r3, r29
/* 800C47C0 000C13A0  4B FB 6E E1 */	bl ftColl_8007B6A0
/* 800C47C4 000C13A4  3C 60 80 0C */	lis r3, ftCo_800C4858@ha
/* 800C47C8 000C13A8  38 03 48 58 */	addi r0, r3, ftCo_800C4858@l
/* 800C47CC 000C13AC  3C 60 80 0C */	lis r3, ftCo_800C48AC@ha
/* 800C47D0 000C13B0  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800C47D4 000C13B4  38 03 48 AC */	addi r0, r3, ftCo_800C48AC@l
/* 800C47D8 000C13B8  90 1F 21 E4 */	stw r0, 0x21e4(r31)
/* 800C47DC 000C13BC  38 80 00 01 */	li r4, 1
/* 800C47E0 000C13C0  38 7D 00 00 */	addi r3, r29, 0
/* 800C47E4 000C13C4  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800C47E8 000C13C8  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800C47EC 000C13CC  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800C47F0 000C13D0  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 800C47F4 000C13D4  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 800C47F8 000C13D8  98 1F 22 22 */	stb r0, 0x2222(r31)
/* 800C47FC 000C13DC  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800C4800 000C13E0  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800C4804 000C13E4  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800C4808 000C13E8  4B FB 9A F5 */	bl ftCommon_8007E2FC
/* 800C480C 000C13EC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C4810 000C13F0  48 1C FB 55 */	bl it_80294364
/* 800C4814 000C13F4  38 83 00 00 */	addi r4, r3, 0
/* 800C4818 000C13F8  38 7E 00 00 */	addi r3, r30, 0
/* 800C481C 000C13FC  38 A0 00 00 */	li r5, 0
/* 800C4820 000C1400  38 C0 00 00 */	li r6, 0
/* 800C4824 000C1404  48 2A B1 ED */	bl HSD_JObjAddAnim
/* 800C4828 000C1408  7F C3 F3 78 */	mr r3, r30
/* 800C482C 000C140C  C0 22 93 68 */	lfs f1, ftCo_804D8D48
/* 800C4830 000C1410  4B FA BF 05 */	bl ftAnim_80070734
/* 800C4834 000C1414  7F C3 F3 78 */	mr r3, r30
/* 800C4838 000C1418  48 2A BF 49 */	bl HSD_JObjAnim
/* 800C483C 000C141C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C4840 000C1420  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C4844 000C1424  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800C4848 000C1428  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800C484C 000C142C  38 21 00 28 */	addi r1, r1, 0x28
/* 800C4850 000C1430  7C 08 03 A6 */	mtlr r0
/* 800C4854 000C1434  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline void inlineA0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 pos;
    ftColl_8007B6EC(gobj);
    fp->facing_dir = fp->mv.co.warpstarjump.facing_dir;
    pos.x = pos.y = pos.z = 0;
    Item_8026ABD8(fp->item_gobj, &pos, 1);
}

ASM void ftCo_800C4858(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineA0(gobj);
}
#else /* clang-format off */
{ nofralloc
/* 800C4858 000C1438  7C 08 02 A6 */	mflr r0
/* 800C485C 000C143C  90 01 00 04 */	stw r0, 4(r1)
/* 800C4860 000C1440  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C4864 000C1444  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C4868 000C1448  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C486C 000C144C  4B FB 6E 81 */	bl ftColl_8007B6EC
/* 800C4870 000C1450  C0 1F 23 58 */	lfs f0, 0x2358(r31)
/* 800C4874 000C1454  38 81 00 10 */	addi r4, r1, 0x10
/* 800C4878 000C1458  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C487C 000C145C  C0 02 93 68 */	lfs f0, ftCo_804D8D48
/* 800C4880 000C1460  C0 22 93 6C */	lfs f1, ftCo_804D8D4C
/* 800C4884 000C1464  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800C4888 000C1468  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800C488C 000C146C  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 800C4890 000C1470  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C4894 000C1474  48 1A 63 45 */	bl Item_8026ABD8
/* 800C4898 000C1478  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C489C 000C147C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C48A0 000C1480  38 21 00 28 */	addi r1, r1, 0x28
/* 800C48A4 000C1484  7C 08 03 A6 */	mtlr r0
/* 800C48A8 000C1488  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C48AC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    inlineA0(gobj);
}

#else /* clang-format off */
{ nofralloc
/* 800C48AC 000C148C  7C 08 02 A6 */	mflr r0
/* 800C48B0 000C1490  90 01 00 04 */	stw r0, 4(r1)
/* 800C48B4 000C1494  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C48B8 000C1498  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C48BC 000C149C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C48C0 000C14A0  4B FB 6E 2D */	bl ftColl_8007B6EC
/* 800C48C4 000C14A4  C0 1F 23 58 */	lfs f0, 0x2358(r31)
/* 800C48C8 000C14A8  38 81 00 10 */	addi r4, r1, 0x10
/* 800C48CC 000C14AC  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800C48D0 000C14B0  C0 02 93 68 */	lfs f0, ftCo_804D8D48
/* 800C48D4 000C14B4  C0 22 93 6C */	lfs f1, ftCo_804D8D4C
/* 800C48D8 000C14B8  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800C48DC 000C14BC  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800C48E0 000C14C0  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 800C48E4 000C14C4  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C48E8 000C14C8  48 1A 62 F1 */	bl Item_8026ABD8
/* 800C48EC 000C14CC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C48F0 000C14D0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C48F4 000C14D4  38 21 00 28 */	addi r1, r1, 0x28
/* 800C48F8 000C14D8  7C 08 03 A6 */	mtlr r0
/* 800C48FC 000C14DC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_WarpStarJump_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    --fp->mv.co.warpstarjump.x1C;
    if (fp->cur_pos.y > Stage_GetBlastZoneTopOffset() ||
        fp->mv.co.warpstarjump.x1C == 0)
    {
        ftCo_800C4A38(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C4900 000C14E0  7C 08 02 A6 */	mflr r0
/* 800C4904 000C14E4  90 01 00 04 */	stw r0, 4(r1)
/* 800C4908 000C14E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C490C 000C14EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C4910 000C14F0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800C4914 000C14F4  7C 7E 1B 78 */	mr r30, r3
/* 800C4918 000C14F8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C491C 000C14FC  80 7F 23 5C */	lwz r3, 0x235c(r31)
/* 800C4920 000C1500  38 03 FF FF */	addi r0, r3, -1
/* 800C4924 000C1504  90 1F 23 5C */	stw r0, 0x235c(r31)
/* 800C4928 000C1508  48 16 02 41 */	bl Stage_GetBlastZoneTopOffset
/* 800C492C 000C150C  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 800C4930 000C1510  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800C4934 000C1514  41 81 00 10 */	bgt lbl_800C4944
/* 800C4938 000C1518  80 1F 23 5C */	lwz r0, 0x235c(r31)
/* 800C493C 000C151C  2C 00 00 00 */	cmpwi r0, 0
/* 800C4940 000C1520  40 82 00 0C */	bne lbl_800C494C
lbl_800C4944:
/* 800C4944 000C1524  7F C3 F3 78 */	mr r3, r30
/* 800C4948 000C1528  48 00 00 F1 */	bl ftCo_800C4A38
lbl_800C494C:
/* 800C494C 000C152C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C4950 000C1530  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C4954 000C1534  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 800C4958 000C1538  38 21 00 18 */	addi r1, r1, 0x18
/* 800C495C 000C153C  7C 08 03 A6 */	mtlr r0
/* 800C4960 000C1540  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_WarpStarJump_IASA(ftCo_GObj* gobj) {}

ASM void ftCo_WarpStarJump_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 self_vel;
    HSD_JObjGetTranslation(jobj, &self_vel);
    fp->self_vel.x = self_vel.x - fp->mv.co.warpstarjump.self_vel.x;
    fp->self_vel.y = self_vel.y - fp->mv.co.warpstarjump.self_vel.y;
    fp->self_vel.z = self_vel.z - fp->mv.co.warpstarjump.self_vel.z;
    fp->mv.co.warpstarjump.self_vel = self_vel;
}

#else /* clang-format off */
{ nofralloc
/* 800C4968 000C1548  7C 08 02 A6 */	mflr r0
/* 800C496C 000C154C  90 01 00 04 */	stw r0, 4(r1)
/* 800C4970 000C1550  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C4974 000C1554  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C4978 000C1558  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800C497C 000C155C  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 800C4980 000C1560  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800C4984 000C1564  28 1F 00 00 */	cmplwi r31, 0
/* 800C4988 000C1568  40 82 00 14 */	bne lbl_800C499C
/* 800C498C 000C156C  38 6D 85 B8 */	addi r3, r13, ftCo_804D3C58
/* 800C4990 000C1570  38 80 03 D3 */	li r4, 0x3d3
/* 800C4994 000C1574  38 AD 85 C0 */	addi r5, r13, ftCo_804D3C60
/* 800C4998 000C1578  48 2C 38 89 */	bl __assert
lbl_800C499C:
/* 800C499C 000C157C  80 7F 00 38 */	lwz r3, 0x38(r31)
/* 800C49A0 000C1580  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 800C49A4 000C1584  90 61 00 14 */	stw r3, 0x14(r1)
/* 800C49A8 000C1588  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C49AC 000C158C  80 1F 00 40 */	lwz r0, 0x40(r31)
/* 800C49B0 000C1590  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800C49B4 000C1594  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800C49B8 000C1598  C0 1E 23 4C */	lfs f0, 0x234c(r30)
/* 800C49BC 000C159C  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C49C0 000C15A0  D0 1E 00 80 */	stfs f0, 0x80(r30)
/* 800C49C4 000C15A4  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 800C49C8 000C15A8  C0 1E 23 50 */	lfs f0, 0x2350(r30)
/* 800C49CC 000C15AC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C49D0 000C15B0  D0 1E 00 84 */	stfs f0, 0x84(r30)
/* 800C49D4 000C15B4  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800C49D8 000C15B8  C0 1E 23 54 */	lfs f0, 0x2354(r30)
/* 800C49DC 000C15BC  EC 01 00 28 */	fsubs f0, f1, f0
/* 800C49E0 000C15C0  D0 1E 00 88 */	stfs f0, 0x88(r30)
/* 800C49E4 000C15C4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800C49E8 000C15C8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 800C49EC 000C15CC  90 7E 23 4C */	stw r3, 0x234c(r30)
/* 800C49F0 000C15D0  90 1E 23 50 */	stw r0, 0x2350(r30)
/* 800C49F4 000C15D4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C49F8 000C15D8  90 1E 23 54 */	stw r0, 0x2354(r30)
/* 800C49FC 000C15DC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C4A00 000C15E0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C4A04 000C15E4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800C4A08 000C15E8  38 21 00 28 */	addi r1, r1, 0x28
/* 800C4A0C 000C15EC  7C 08 03 A6 */	mtlr r0
/* 800C4A10 000C15F0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_WarpStarJump_Coll(ftCo_GObj* gobj) {}

void ftCo_WarpStarJump_Cam(ftCo_GObj* gobj)
{
    ftCamera_800762F4(gobj);
}

ASM void ftCo_800C4A38(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Quaternion rot;
    it_802944AC(fp->item_gobj, &fp->mv.co.warpstarjump.x20);
    Fighter_ChangeMotionState(gobj, ftCo_MS_WarpStarFall, Ft_MF_None, 0, 1, 0,
                              NULL);
    fp->x2222_b7 = true;
    fp->take_dmg_cb = ftCo_800C4858;
    fp->death2_cb = ftCo_800C48AC;
    fp->x221E_b2 = true;
    ftCommon_8007E2FC(gobj);
    fp->cur_pos.x = fp->mv.co.warpstarjump.cur_pos.x;
    fp->cur_pos.y = Stage_GetBlastZoneTopOffset();
    fp->cur_pos.z = 0;
    rot.x = M_PI_2;
    rot.w = 0;
    rot.z = 0;
    rot.y = 0;
    HSD_JObjSetRotation(GET_JOBJ(gobj), &rot);
    it_802946B0(fp->item_gobj);
    mpColl_80043680(&fp->coll_data, &fp->cur_pos);
}

#else /* clang-format off */
{ nofralloc
/* 800C4A38 000C1618  7C 08 02 A6 */	mflr r0
/* 800C4A3C 000C161C  90 01 00 04 */	stw r0, 4(r1)
/* 800C4A40 000C1620  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800C4A44 000C1624  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800C4A48 000C1628  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800C4A4C 000C162C  7C 7E 1B 78 */	mr r30, r3
/* 800C4A50 000C1630  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C4A54 000C1634  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C4A58 000C1638  38 9F 23 60 */	addi r4, r31, 0x2360
/* 800C4A5C 000C163C  48 1C FA 51 */	bl it_802944AC
/* 800C4A60 000C1640  C0 22 93 68 */	lfs f1, ftCo_804D8D48
/* 800C4A64 000C1644  7F C3 F3 78 */	mr r3, r30
/* 800C4A68 000C1648  C0 42 93 6C */	lfs f2, ftCo_804D8D4C
/* 800C4A6C 000C164C  38 80 01 32 */	li r4, 0x132
/* 800C4A70 000C1650  FC 60 08 90 */	fmr f3, f1
/* 800C4A74 000C1654  38 A0 00 00 */	li r5, 0
/* 800C4A78 000C1658  38 C0 00 00 */	li r6, 0
/* 800C4A7C 000C165C  4B FA 49 31 */	bl Fighter_ChangeMotionState
/* 800C4A80 000C1660  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 800C4A84 000C1664  38 80 00 01 */	li r4, 1
/* 800C4A88 000C1668  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 800C4A8C 000C166C  3C 60 80 0C */	lis r3, ftCo_800C4858@ha
/* 800C4A90 000C1670  98 1F 22 22 */	stb r0, 0x2222(r31)
/* 800C4A94 000C1674  38 03 48 58 */	addi r0, r3, ftCo_800C4858@l
/* 800C4A98 000C1678  3C 60 80 0C */	lis r3, ftCo_800C48AC@ha
/* 800C4A9C 000C167C  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800C4AA0 000C1680  38 03 48 AC */	addi r0, r3, ftCo_800C48AC@l
/* 800C4AA4 000C1684  90 1F 21 E4 */	stw r0, 0x21e4(r31)
/* 800C4AA8 000C1688  7F C3 F3 78 */	mr r3, r30
/* 800C4AAC 000C168C  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800C4AB0 000C1690  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800C4AB4 000C1694  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800C4AB8 000C1698  4B FB 98 45 */	bl ftCommon_8007E2FC
/* 800C4ABC 000C169C  C0 1F 23 40 */	lfs f0, 0x2340(r31)
/* 800C4AC0 000C16A0  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 800C4AC4 000C16A4  48 16 00 A5 */	bl Stage_GetBlastZoneTopOffset
/* 800C4AC8 000C16A8  D0 3F 00 B4 */	stfs f1, 0xb4(r31)
/* 800C4ACC 000C16AC  C0 22 93 68 */	lfs f1, ftCo_804D8D48
/* 800C4AD0 000C16B0  D0 3F 00 B8 */	stfs f1, 0xb8(r31)
/* 800C4AD4 000C16B4  C0 02 93 70 */	lfs f0, ftCo_804D8D50
/* 800C4AD8 000C16B8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800C4ADC 000C16BC  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 800C4AE0 000C16C0  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 800C4AE4 000C16C4  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 800C4AE8 000C16C8  83 DE 00 28 */	lwz r30, 0x28(r30)
/* 800C4AEC 000C16CC  28 1E 00 00 */	cmplwi r30, 0
/* 800C4AF0 000C16D0  40 82 00 14 */	bne lbl_800C4B04
/* 800C4AF4 000C16D4  38 6D 85 B8 */	addi r3, r13, ftCo_804D3C58
/* 800C4AF8 000C16D8  38 80 02 6A */	li r4, 0x26a
/* 800C4AFC 000C16DC  38 AD 85 C0 */	addi r5, r13, ftCo_804D3C60
/* 800C4B00 000C16E0  48 2C 37 21 */	bl __assert
lbl_800C4B04:
/* 800C4B04 000C16E4  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800C4B08 000C16E8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 800C4B0C 000C16EC  90 7E 00 1C */	stw r3, 0x1c(r30)
/* 800C4B10 000C16F0  90 1E 00 20 */	stw r0, 0x20(r30)
/* 800C4B14 000C16F4  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 800C4B18 000C16F8  80 01 00 20 */	lwz r0, 0x20(r1)
/* 800C4B1C 000C16FC  90 7E 00 24 */	stw r3, 0x24(r30)
/* 800C4B20 000C1700  90 1E 00 28 */	stw r0, 0x28(r30)
/* 800C4B24 000C1704  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800C4B28 000C1708  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800C4B2C 000C170C  40 82 00 4C */	bne lbl_800C4B78
/* 800C4B30 000C1710  28 1E 00 00 */	cmplwi r30, 0
/* 800C4B34 000C1714  41 82 00 44 */	beq lbl_800C4B78
/* 800C4B38 000C1718  40 82 00 14 */	bne lbl_800C4B4C
/* 800C4B3C 000C171C  38 6D 85 B8 */	addi r3, r13, ftCo_804D3C58
/* 800C4B40 000C1720  38 80 02 34 */	li r4, 0x234
/* 800C4B44 000C1724  38 AD 85 C0 */	addi r5, r13, ftCo_804D3C60
/* 800C4B48 000C1728  48 2C 36 D9 */	bl __assert
lbl_800C4B4C:
/* 800C4B4C 000C172C  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800C4B50 000C1730  38 60 00 00 */	li r3, 0
/* 800C4B54 000C1734  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C4B58 000C1738  40 82 00 10 */	bne lbl_800C4B68
/* 800C4B5C 000C173C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C4B60 000C1740  41 82 00 08 */	beq lbl_800C4B68
/* 800C4B64 000C1744  38 60 00 01 */	li r3, 1
lbl_800C4B68:
/* 800C4B68 000C1748  2C 03 00 00 */	cmpwi r3, 0
/* 800C4B6C 000C174C  40 82 00 0C */	bne lbl_800C4B78
/* 800C4B70 000C1750  7F C3 F3 78 */	mr r3, r30
/* 800C4B74 000C1754  48 2A E7 75 */	bl HSD_JObjSetMtxDirtySub
lbl_800C4B78:
/* 800C4B78 000C1758  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 800C4B7C 000C175C  48 1C FB 35 */	bl it_802946B0
/* 800C4B80 000C1760  38 7F 06 F0 */	addi r3, r31, 0x6f0
/* 800C4B84 000C1764  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 800C4B88 000C1768  4B F7 EA F9 */	bl mpColl_80043680
/* 800C4B8C 000C176C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800C4B90 000C1770  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800C4B94 000C1774  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800C4B98 000C1778  38 21 00 30 */	addi r1, r1, 0x30
/* 800C4B9C 000C177C  7C 08 03 A6 */	mtlr r0
/* 800C4BA0 000C1780  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
