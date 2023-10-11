#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_ThrownKirbyStar.h"

#include "ft/ft_081B.h"
#include "ft/ft_08A4.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <runtime.h>
#include <baselib/jobj.h>

/* literal */ float const ftCo_804D8BD0 = 0;
/* literal */ double const ftCo_804D8BD8 = S32_TO_F32;
/* literal */ double const ftCo_804D8BE0 = 0.5;
/* literal */ double const ftCo_804D8BE8 = 3;
/* literal */ float const ftCo_804D8BF0 = -1;
/* literal */ float const ftCo_804D8BF4 = +1;
/* literal */ extern char* ftCo_804D3BE0;
/* literal */ extern char* ftCo_804D3BE8;
/* literal */ extern char* ftCo_804D3BF0;

FighterKind ftCo_800BD9E0(ftKb_GObj* gobj, Fighter_GObj* victim_gobj)
{
    ftKb_Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(victim_gobj);
    FighterKind victim_kind = victim_fp->kind;
    if (victim_kind == FTKIND_KIRBY) {
        ftCo_800BDA50(victim_gobj);
        return victim_fp->fv.kb.victim_kind;
    }
    if ((unsigned) (victim_kind - FTKIND_BOY) <= 1 ||
        victim_kind == FTKIND_SANDBAG)
    {
        return fp->fv.kb.victim_kind;
    }
    if (victim_kind == FTKIND_NANA) {
        victim_kind = FTKIND_POPO;
    }
    return victim_kind;
}

void ftCo_800BDA50(ftKb_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->fv.kb.victim_kind != FTKIND_KIRBY) {
        /// @todo Which @c mv is this?
        fp->mv.co.thrownkirbystar.x18_b1 = true;
    }
}

ASM void ftCo_800BDA74(ftCo_GObj* gobj, Vec3* normal)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_800824A0(gobj, &fp->mv.co.thrownkirbystar.coll_box)) {
        *normal = coll->floor.normal;
    } else if (coll->env_flags & MPCOLL_LEFTWALL) {
        *normal = coll->left_wall.normal;
    } else if (coll->env_flags & MPCOLL_RIGHTWALL) {
        *normal = coll->right_wall.normal;
    } else if (coll->env_flags & MPCOLL_CEIL) {
        *normal = coll->ceiling.normal;
    } else {
        normal->x = normal->y = normal->z = 0;
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BDA74 000BA654  7C 08 02 A6 */	mflr r0
/* 800BDA78 000BA658  90 01 00 04 */	stw r0, 4(r1)
/* 800BDA7C 000BA65C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800BDA80 000BA660  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800BDA84 000BA664  3B E4 00 00 */	addi r31, r4, 0
/* 800BDA88 000BA668  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800BDA8C 000BA66C  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800BDA90 000BA670  3B C5 06 F0 */	addi r30, r5, 0x6f0
/* 800BDA94 000BA674  38 85 23 68 */	addi r4, r5, 0x2368
/* 800BDA98 000BA678  4B FC 4A 09 */	bl ft_800824A0
/* 800BDA9C 000BA67C  2C 03 00 00 */	cmpwi r3, 0
/* 800BDAA0 000BA680  41 82 00 20 */	beq lbl_800BDAC0
/* 800BDAA4 000BA684  80 7E 01 54 */	lwz r3, 0x154(r30)
/* 800BDAA8 000BA688  80 1E 01 58 */	lwz r0, 0x158(r30)
/* 800BDAAC 000BA68C  90 7F 00 00 */	stw r3, 0(r31)
/* 800BDAB0 000BA690  90 1F 00 04 */	stw r0, 4(r31)
/* 800BDAB4 000BA694  80 1E 01 5C */	lwz r0, 0x15c(r30)
/* 800BDAB8 000BA698  90 1F 00 08 */	stw r0, 8(r31)
/* 800BDABC 000BA69C  48 00 00 84 */	b lbl_800BDB40
lbl_800BDAC0:
/* 800BDAC0 000BA6A0  80 7E 01 34 */	lwz r3, 0x134(r30)
/* 800BDAC4 000BA6A4  54 60 05 33 */	rlwinm. r0, r3, 0, 0x14, 0x19
/* 800BDAC8 000BA6A8  41 82 00 20 */	beq lbl_800BDAE8
/* 800BDACC 000BA6AC  80 7E 01 7C */	lwz r3, 0x17c(r30)
/* 800BDAD0 000BA6B0  80 1E 01 80 */	lwz r0, 0x180(r30)
/* 800BDAD4 000BA6B4  90 7F 00 00 */	stw r3, 0(r31)
/* 800BDAD8 000BA6B8  90 1F 00 04 */	stw r0, 4(r31)
/* 800BDADC 000BA6BC  80 1E 01 84 */	lwz r0, 0x184(r30)
/* 800BDAE0 000BA6C0  90 1F 00 08 */	stw r0, 8(r31)
/* 800BDAE4 000BA6C4  48 00 00 5C */	b lbl_800BDB40
lbl_800BDAE8:
/* 800BDAE8 000BA6C8  54 60 06 BF */	clrlwi. r0, r3, 0x1a
/* 800BDAEC 000BA6CC  41 82 00 20 */	beq lbl_800BDB0C
/* 800BDAF0 000BA6D0  80 7E 01 68 */	lwz r3, 0x168(r30)
/* 800BDAF4 000BA6D4  80 1E 01 6C */	lwz r0, 0x16c(r30)
/* 800BDAF8 000BA6D8  90 7F 00 00 */	stw r3, 0(r31)
/* 800BDAFC 000BA6DC  90 1F 00 04 */	stw r0, 4(r31)
/* 800BDB00 000BA6E0  80 1E 01 70 */	lwz r0, 0x170(r30)
/* 800BDB04 000BA6E4  90 1F 00 08 */	stw r0, 8(r31)
/* 800BDB08 000BA6E8  48 00 00 38 */	b lbl_800BDB40
lbl_800BDB0C:
/* 800BDB0C 000BA6EC  54 60 04 65 */	rlwinm. r0, r3, 0, 0x11, 0x12
/* 800BDB10 000BA6F0  41 82 00 20 */	beq lbl_800BDB30
/* 800BDB14 000BA6F4  80 7E 01 90 */	lwz r3, 0x190(r30)
/* 800BDB18 000BA6F8  80 1E 01 94 */	lwz r0, 0x194(r30)
/* 800BDB1C 000BA6FC  90 7F 00 00 */	stw r3, 0(r31)
/* 800BDB20 000BA700  90 1F 00 04 */	stw r0, 4(r31)
/* 800BDB24 000BA704  80 1E 01 98 */	lwz r0, 0x198(r30)
/* 800BDB28 000BA708  90 1F 00 08 */	stw r0, 8(r31)
/* 800BDB2C 000BA70C  48 00 00 14 */	b lbl_800BDB40
lbl_800BDB30:
/* 800BDB30 000BA710  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDB34 000BA714  D0 1F 00 08 */	stfs f0, 8(r31)
/* 800BDB38 000BA718  D0 1F 00 04 */	stfs f0, 4(r31)
/* 800BDB3C 000BA71C  D0 1F 00 00 */	stfs f0, 0(r31)
lbl_800BDB40:
/* 800BDB40 000BA720  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800BDB44 000BA724  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800BDB48 000BA728  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800BDB4C 000BA72C  38 21 00 20 */	addi r1, r1, 0x20
/* 800BDB50 000BA730  7C 08 03 A6 */	mtlr r0
/* 800BDB54 000BA734  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

static inline float inlineB0(ftCo_GObj* gobj)
{
    return GET_FIGHTER(gobj)->co_attrs.xDC;
}

static inline float inlineB1(ftCo_GObj* gobj)
{
    return GET_FIGHTER(gobj)->co_attrs.kirby_b_star_damage;
}

ASM void ftCo_800BDB58(ftCo_GObj* gobj, ftKb_GObj* thrower_gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 scale;
    fp->facing_dir = -GET_FIGHTER(thrower_gobj)->facing_dir;
    fp->mv.co.thrownkirbystar.thrower_gobj = thrower_gobj;
    fp->mv.co.thrownkirbystar.x8 = 0;
    fp->mv.co.thrownkirbystar.x4 =
        ftKb_SpecialN_800F58AC(thrower_gobj, &fp->self_vel, fp->facing_dir);
    Fighter_UpdateModelScale(gobj);
    HSD_JObjGetScale(jobj, &fp->mv.co.thrownkirbystar.scale);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ThrownKirbyStar,
                              Ft_MF_SkipThrowException, 0, 1, 0, thrower_gobj);
    fp->x21F0 = ftCo_800BE7C0;
    fp->take_dmg_cb = ftCo_800BE7C0;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
    ftCommon_8007EFC0(fp, 1);
    ftCommon_8007DBCC(fp, 0, ftKb_SpecialN_800F5A88(thrower_gobj));
    ftAnim_8006EBA4(gobj);
    ftCommon_8007D5D4(fp);
    fp->mv.co.thrownkirbystar.x18_b0 = false;
    fp->mv.co.thrownkirbystar.x18_b1 = false;
    ftCommon_SetAccessory(fp, ftKb_SpecialN_800F5898(thrower_gobj, 0));
    scale.x = scale.y = scale.z = inlineB0(gobj);
    HSD_JObjSetScale(fp->x20A0_accessory, &scale);
    lb_8000C2F8(fp->x20A0_accessory,
                fp->parts[ftParts_8007500C(fp, FtPart_YRotN)].joint);
    ftColl_8007ABD0(fp->x914, inlineB1(gobj), gobj);
    ftKb_SpecialN_800F5820(thrower_gobj, &fp->mv.co.thrownkirbystar.coll_box,
                           scale.x);
}

#else /* clang-format off */
{ nofralloc
/* 800BDB58 000BA738  7C 08 02 A6 */	mflr r0
/* 800BDB5C 000BA73C  90 01 00 04 */	stw r0, 4(r1)
/* 800BDB60 000BA740  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 800BDB64 000BA744  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 800BDB68 000BA748  93 C1 00 68 */	stw r30, 0x68(r1)
/* 800BDB6C 000BA74C  7C 9E 23 78 */	mr r30, r4
/* 800BDB70 000BA750  93 A1 00 64 */	stw r29, 0x64(r1)
/* 800BDB74 000BA754  7C 7D 1B 78 */	mr r29, r3
/* 800BDB78 000BA758  93 81 00 60 */	stw r28, 0x60(r1)
/* 800BDB7C 000BA75C  80 84 00 2C */	lwz r4, 0x2c(r4)
/* 800BDB80 000BA760  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BDB84 000BA764  7F C3 F3 78 */	mr r3, r30
/* 800BDB88 000BA768  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 800BDB8C 000BA76C  83 9D 00 28 */	lwz r28, 0x28(r29)
/* 800BDB90 000BA770  38 9F 00 80 */	addi r4, r31, 0x80
/* 800BDB94 000BA774  FC 00 00 50 */	fneg f0, f0
/* 800BDB98 000BA778  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BDB9C 000BA77C  93 DF 23 40 */	stw r30, 0x2340(r31)
/* 800BDBA0 000BA780  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDBA4 000BA784  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 800BDBA8 000BA788  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800BDBAC 000BA78C  48 03 7D 01 */	bl ftKb_SpecialN_800F58AC
/* 800BDBB0 000BA790  D0 3F 23 44 */	stfs f1, 0x2344(r31)
/* 800BDBB4 000BA794  7F A3 EB 78 */	mr r3, r29
/* 800BDBB8 000BA798  4B FA 9F FD */	bl Fighter_UpdateModelScale
/* 800BDBBC 000BA79C  28 1C 00 00 */	cmplwi r28, 0
/* 800BDBC0 000BA7A0  40 82 00 14 */	bne lbl_800BDBD4
/* 800BDBC4 000BA7A4  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BDBC8 000BA7A8  38 80 03 37 */	li r4, 0x337
/* 800BDBCC 000BA7AC  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BDBD0 000BA7B0  48 2C A6 51 */	bl __assert
lbl_800BDBD4:
/* 800BDBD4 000BA7B4  34 1F 23 5C */	addic. r0, r31, 0x235c
/* 800BDBD8 000BA7B8  40 82 00 14 */	bne lbl_800BDBEC
/* 800BDBDC 000BA7BC  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BDBE0 000BA7C0  38 80 03 38 */	li r4, 0x338
/* 800BDBE4 000BA7C4  38 AD 85 50 */	addi r5, r13, ftCo_804D3BF0
/* 800BDBE8 000BA7C8  48 2C A6 39 */	bl __assert
lbl_800BDBEC:
/* 800BDBEC 000BA7CC  80 BC 00 2C */	lwz r5, 0x2c(r28)
/* 800BDBF0 000BA7D0  7F A3 EB 78 */	mr r3, r29
/* 800BDBF4 000BA7D4  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 800BDBF8 000BA7D8  38 DE 00 00 */	addi r6, r30, 0
/* 800BDBFC 000BA7DC  38 80 01 22 */	li r4, 0x122
/* 800BDC00 000BA7E0  90 BF 23 5C */	stw r5, 0x235c(r31)
/* 800BDC04 000BA7E4  38 A0 01 00 */	li r5, 0x100
/* 800BDC08 000BA7E8  90 1F 23 60 */	stw r0, 0x2360(r31)
/* 800BDC0C 000BA7EC  80 1C 00 34 */	lwz r0, 0x34(r28)
/* 800BDC10 000BA7F0  90 1F 23 64 */	stw r0, 0x2364(r31)
/* 800BDC14 000BA7F4  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BDC18 000BA7F8  C0 42 92 14 */	lfs f2, ftCo_804D8BF4
/* 800BDC1C 000BA7FC  FC 60 08 90 */	fmr f3, f1
/* 800BDC20 000BA800  4B FA B7 8D */	bl Fighter_ChangeMotionState
/* 800BDC24 000BA804  3C 60 80 0C */	lis r3, ftCo_800BE7C0@ha
/* 800BDC28 000BA808  38 03 E7 C0 */	addi r0, r3, ftCo_800BE7C0@l
/* 800BDC2C 000BA80C  90 1F 21 F0 */	stw r0, 0x21f0(r31)
/* 800BDC30 000BA810  38 7F 00 00 */	addi r3, r31, 0
/* 800BDC34 000BA814  38 80 01 FF */	li r4, 0x1ff
/* 800BDC38 000BA818  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800BDC3C 000BA81C  4B FC 06 B9 */	bl ftCommon_8007E2F4
/* 800BDC40 000BA820  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800BDC44 000BA824  38 60 00 01 */	li r3, 1
/* 800BDC48 000BA828  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 800BDC4C 000BA82C  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800BDC50 000BA830  38 7D 00 00 */	addi r3, r29, 0
/* 800BDC54 000BA834  38 80 00 02 */	li r4, 2
/* 800BDC58 000BA838  4B FB D9 D5 */	bl ftColl_8007B62C
/* 800BDC5C 000BA83C  38 7F 00 00 */	addi r3, r31, 0
/* 800BDC60 000BA840  38 80 00 01 */	li r4, 1
/* 800BDC64 000BA844  4B FC 13 5D */	bl ftCommon_8007EFC0
/* 800BDC68 000BA848  7F C3 F3 78 */	mr r3, r30
/* 800BDC6C 000BA84C  48 03 7E 1D */	bl ftKb_SpecialN_800F5A88
/* 800BDC70 000BA850  38 7F 00 00 */	addi r3, r31, 0
/* 800BDC74 000BA854  38 80 00 00 */	li r4, 0
/* 800BDC78 000BA858  4B FB FF 55 */	bl ftCommon_8007DBCC
/* 800BDC7C 000BA85C  7F A3 EB 78 */	mr r3, r29
/* 800BDC80 000BA860  4B FB 0F 25 */	bl ftAnim_8006EBA4
/* 800BDC84 000BA864  7F E3 FB 78 */	mr r3, r31
/* 800BDC88 000BA868  4B FB F9 4D */	bl ftCommon_8007D5D4
/* 800BDC8C 000BA86C  88 1F 23 58 */	lbz r0, 0x2358(r31)
/* 800BDC90 000BA870  38 80 00 00 */	li r4, 0
/* 800BDC94 000BA874  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 800BDC98 000BA878  98 1F 23 58 */	stb r0, 0x2358(r31)
/* 800BDC9C 000BA87C  7F C3 F3 78 */	mr r3, r30
/* 800BDCA0 000BA880  88 1F 23 58 */	lbz r0, 0x2358(r31)
/* 800BDCA4 000BA884  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 800BDCA8 000BA888  98 1F 23 58 */	stb r0, 0x2358(r31)
/* 800BDCAC 000BA88C  48 03 7B ED */	bl ftKb_SpecialN_800F5898
/* 800BDCB0 000BA890  38 83 00 00 */	addi r4, r3, 0
/* 800BDCB4 000BA894  38 7F 00 00 */	addi r3, r31, 0
/* 800BDCB8 000BA898  4B FC 09 69 */	bl ftCommon_SetAccessory
/* 800BDCBC 000BA89C  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 800BDCC0 000BA8A0  C0 03 01 EC */	lfs f0, 0x1ec(r3)
/* 800BDCC4 000BA8A4  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800BDCC8 000BA8A8  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800BDCCC 000BA8AC  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 800BDCD0 000BA8B0  83 9F 20 A0 */	lwz r28, 0x20a0(r31)
/* 800BDCD4 000BA8B4  28 1C 00 00 */	cmplwi r28, 0
/* 800BDCD8 000BA8B8  40 82 00 14 */	bne lbl_800BDCEC
/* 800BDCDC 000BA8BC  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BDCE0 000BA8C0  38 80 02 F8 */	li r4, 0x2f8
/* 800BDCE4 000BA8C4  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BDCE8 000BA8C8  48 2C A5 39 */	bl __assert
lbl_800BDCEC:
/* 800BDCEC 000BA8CC  80 61 00 50 */	lwz r3, 0x50(r1)
/* 800BDCF0 000BA8D0  80 01 00 54 */	lwz r0, 0x54(r1)
/* 800BDCF4 000BA8D4  90 7C 00 2C */	stw r3, 0x2c(r28)
/* 800BDCF8 000BA8D8  90 1C 00 30 */	stw r0, 0x30(r28)
/* 800BDCFC 000BA8DC  80 01 00 58 */	lwz r0, 0x58(r1)
/* 800BDD00 000BA8E0  90 1C 00 34 */	stw r0, 0x34(r28)
/* 800BDD04 000BA8E4  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800BDD08 000BA8E8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BDD0C 000BA8EC  40 82 00 4C */	bne lbl_800BDD58
/* 800BDD10 000BA8F0  28 1C 00 00 */	cmplwi r28, 0
/* 800BDD14 000BA8F4  41 82 00 44 */	beq lbl_800BDD58
/* 800BDD18 000BA8F8  40 82 00 14 */	bne lbl_800BDD2C
/* 800BDD1C 000BA8FC  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BDD20 000BA900  38 80 02 34 */	li r4, 0x234
/* 800BDD24 000BA904  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BDD28 000BA908  48 2C A4 F9 */	bl __assert
lbl_800BDD2C:
/* 800BDD2C 000BA90C  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800BDD30 000BA910  38 60 00 00 */	li r3, 0
/* 800BDD34 000BA914  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BDD38 000BA918  40 82 00 10 */	bne lbl_800BDD48
/* 800BDD3C 000BA91C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BDD40 000BA920  41 82 00 08 */	beq lbl_800BDD48
/* 800BDD44 000BA924  38 60 00 01 */	li r3, 1
lbl_800BDD48:
/* 800BDD48 000BA928  2C 03 00 00 */	cmpwi r3, 0
/* 800BDD4C 000BA92C  40 82 00 0C */	bne lbl_800BDD58
/* 800BDD50 000BA930  7F 83 E3 78 */	mr r3, r28
/* 800BDD54 000BA934  48 2B 55 95 */	bl HSD_JObjSetMtxDirtySub
lbl_800BDD58:
/* 800BDD58 000BA938  38 7F 00 00 */	addi r3, r31, 0
/* 800BDD5C 000BA93C  38 80 00 03 */	li r4, 3
/* 800BDD60 000BA940  4B FB 72 AD */	bl ftParts_8007500C
/* 800BDD64 000BA944  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800BDD68 000BA948  54 60 20 36 */	slwi r0, r3, 4
/* 800BDD6C 000BA94C  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 800BDD70 000BA950  7C 84 00 2E */	lwzx r4, r4, r0
/* 800BDD74 000BA954  4B F4 E5 85 */	bl lb_8000C2F8
/* 800BDD78 000BA958  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 800BDD7C 000BA95C  C0 23 01 F0 */	lfs f1, 0x1f0(r3)
/* 800BDD80 000BA960  48 26 4B 41 */	bl __cvt_fp2unsigned
/* 800BDD84 000BA964  38 83 00 00 */	addi r4, r3, 0
/* 800BDD88 000BA968  38 BD 00 00 */	addi r5, r29, 0
/* 800BDD8C 000BA96C  38 7F 09 14 */	addi r3, r31, 0x914
/* 800BDD90 000BA970  4B FB CE 41 */	bl ftColl_8007ABD0
/* 800BDD94 000BA974  C0 21 00 50 */	lfs f1, 0x50(r1)
/* 800BDD98 000BA978  38 7E 00 00 */	addi r3, r30, 0
/* 800BDD9C 000BA97C  38 9F 23 68 */	addi r4, r31, 0x2368
/* 800BDDA0 000BA980  48 03 7A 81 */	bl ftKb_SpecialN_800F5820
/* 800BDDA4 000BA984  80 01 00 74 */	lwz r0, 0x74(r1)
/* 800BDDA8 000BA988  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 800BDDAC 000BA98C  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 800BDDB0 000BA990  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 800BDDB4 000BA994  83 81 00 60 */	lwz r28, 0x60(r1)
/* 800BDDB8 000BA998  38 21 00 70 */	addi r1, r1, 0x70
/* 800BDDBC 000BA99C  7C 08 03 A6 */	mtlr r0
/* 800BDDC0 000BA9A0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_ThrownKirbyStar_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKirbyStar_IASA(ftCo_GObj* gobj) {}

static inline void inlineA0(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    float vel_mag = sqrtf(SQ(fp->self_vel.x) + SQ(fp->self_vel.y));
    if (vel_mag > fp->mv.co.thrownkirbystar.x4) {
        fp->self_vel.x =
            (fp->self_vel.x * (vel_mag - fp->mv.co.thrownkirbystar.x4)) /
            vel_mag;
        fp->self_vel.y =
            (fp->self_vel.y * (vel_mag - fp->mv.ca.specialhi.vel.x)) / vel_mag;
        if (fp->self_vel.y < 0) {
            fp->facing_dir = -1;
        } else {
            fp->facing_dir = +1;
        }
    } else {
        fp->self_vel.x = 0;
    }
    fp->x1A4C -= ftKb_SpecialN_800F5AC0(gobj);
}

ASM void ftCo_ThrownKirbyStar_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->mv.co.thrownkirbystar.x14 =
        ftCommon_8007DC08(fp, ftKb_SpecialN_800F5AD8());
    if (fp->x1A4C <= 0) {
        ftCo_800BE494(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BDDCC 000BA9AC  7C 08 02 A6 */	mflr r0
/* 800BDDD0 000BA9B0  90 01 00 04 */	stw r0, 4(r1)
/* 800BDDD4 000BA9B4  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BDDD8 000BA9B8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BDDDC 000BA9BC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BDDE0 000BA9C0  7C 7E 1B 78 */	mr r30, r3
/* 800BDDE4 000BA9C4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BDDE8 000BA9C8  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDDEC 000BA9CC  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800BDDF0 000BA9D0  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BDDF4 000BA9D4  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800BDDF8 000BA9D8  EC 21 00 72 */	fmuls f1, f1, f1
/* 800BDDFC 000BA9DC  EC 82 08 2A */	fadds f4, f2, f1
/* 800BDE00 000BA9E0  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800BDE04 000BA9E4  40 81 00 50 */	ble lbl_800BDE54
/* 800BDE08 000BA9E8  FC 20 20 34 */	frsqrte f1, f4
/* 800BDE0C 000BA9EC  C8 62 92 00 */	lfd f3, ftCo_804D8BE0
/* 800BDE10 000BA9F0  C8 42 92 08 */	lfd f2, ftCo_804D8BE8
/* 800BDE14 000BA9F4  FC 01 00 72 */	fmul f0, f1, f1
/* 800BDE18 000BA9F8  FC 23 00 72 */	fmul f1, f3, f1
/* 800BDE1C 000BA9FC  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BDE20 000BAA00  FC 21 00 32 */	fmul f1, f1, f0
/* 800BDE24 000BAA04  FC 01 00 72 */	fmul f0, f1, f1
/* 800BDE28 000BAA08  FC 23 00 72 */	fmul f1, f3, f1
/* 800BDE2C 000BAA0C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BDE30 000BAA10  FC 21 00 32 */	fmul f1, f1, f0
/* 800BDE34 000BAA14  FC 01 00 72 */	fmul f0, f1, f1
/* 800BDE38 000BAA18  FC 23 00 72 */	fmul f1, f3, f1
/* 800BDE3C 000BAA1C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BDE40 000BAA20  FC 01 00 32 */	fmul f0, f1, f0
/* 800BDE44 000BAA24  FC 04 00 32 */	fmul f0, f4, f0
/* 800BDE48 000BAA28  FC 00 00 18 */	frsp f0, f0
/* 800BDE4C 000BAA2C  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800BDE50 000BAA30  C0 81 00 14 */	lfs f4, 0x14(r1)
lbl_800BDE54:
/* 800BDE54 000BAA34  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800BDE58 000BAA38  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800BDE5C 000BAA3C  40 81 00 58 */	ble lbl_800BDEB4
/* 800BDE60 000BAA40  EC 04 00 28 */	fsubs f0, f4, f0
/* 800BDE64 000BAA44  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 800BDE68 000BAA48  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BDE6C 000BAA4C  EC 00 20 24 */	fdivs f0, f0, f4
/* 800BDE70 000BAA50  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800BDE74 000BAA54  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800BDE78 000BAA58  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BDE7C 000BAA5C  EC 04 00 28 */	fsubs f0, f4, f0
/* 800BDE80 000BAA60  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BDE84 000BAA64  EC 00 20 24 */	fdivs f0, f0, f4
/* 800BDE88 000BAA68  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800BDE8C 000BAA6C  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BDE90 000BAA70  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDE94 000BAA74  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BDE98 000BAA78  40 80 00 10 */	bge lbl_800BDEA8
/* 800BDE9C 000BAA7C  C0 02 92 10 */	lfs f0, ftCo_804D8BF0
/* 800BDEA0 000BAA80  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BDEA4 000BAA84  48 00 00 18 */	b lbl_800BDEBC
lbl_800BDEA8:
/* 800BDEA8 000BAA88  C0 02 92 14 */	lfs f0, ftCo_804D8BF4
/* 800BDEAC 000BAA8C  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BDEB0 000BAA90  48 00 00 0C */	b lbl_800BDEBC
lbl_800BDEB4:
/* 800BDEB4 000BAA94  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDEB8 000BAA98  D0 1F 00 80 */	stfs f0, 0x80(r31)
lbl_800BDEBC:
/* 800BDEBC 000BAA9C  48 03 7C 05 */	bl ftKb_SpecialN_800F5AC0
/* 800BDEC0 000BAAA0  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BDEC4 000BAAA4  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BDEC8 000BAAA8  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800BDECC 000BAAAC  48 03 7C 0D */	bl ftKb_SpecialN_800F5AD8
/* 800BDED0 000BAAB0  7F E3 FB 78 */	mr r3, r31
/* 800BDED4 000BAAB4  4B FB FD 35 */	bl ftCommon_8007DC08
/* 800BDED8 000BAAB8  90 7F 23 54 */	stw r3, 0x2354(r31)
/* 800BDEDC 000BAABC  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800BDEE0 000BAAC0  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDEE4 000BAAC4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BDEE8 000BAAC8  4C 40 13 82 */	cror 2, 0, 2
/* 800BDEEC 000BAACC  40 82 00 0C */	bne lbl_800BDEF8
/* 800BDEF0 000BAAD0  7F C3 F3 78 */	mr r3, r30
/* 800BDEF4 000BAAD4  48 00 05 A1 */	bl ftCo_800BE494
lbl_800BDEF8:
/* 800BDEF8 000BAAD8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BDEFC 000BAADC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BDF00 000BAAE0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BDF04 000BAAE4  38 21 00 28 */	addi r1, r1, 0x28
/* 800BDF08 000BAAE8  7C 08 03 A6 */	mtlr r0
/* 800BDF0C 000BAAEC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_ThrownKirbyStar_Coll(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 self_vel;
    Vec3 normal;
    ftCo_800BDA74(gobj, &normal);
    if (normal.x || normal.y || normal.z) {
        self_vel = fp->self_vel;
        lbVector_Mirror(&fp->self_vel, &normal);
        if (self_vel.x * fp->self_vel.x + self_vel.y * fp->self_vel.y < 0) {
            ftCo_800BE494(gobj);
            fp->mv.co.thrownkirbystar.x8 = normal.x < 0 ? -1 : +1;
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BDF10 000BAAF0  7C 08 02 A6 */	mflr r0
/* 800BDF14 000BAAF4  90 01 00 04 */	stw r0, 4(r1)
/* 800BDF18 000BAAF8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800BDF1C 000BAAFC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800BDF20 000BAB00  38 81 00 10 */	addi r4, r1, 0x10
/* 800BDF24 000BAB04  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800BDF28 000BAB08  7C 7E 1B 78 */	mr r30, r3
/* 800BDF2C 000BAB0C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BDF30 000BAB10  4B FF FB 45 */	bl ftCo_800BDA74
/* 800BDF34 000BAB14  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800BDF38 000BAB18  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BDF3C 000BAB1C  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BDF40 000BAB20  40 82 00 1C */	bne lbl_800BDF5C
/* 800BDF44 000BAB24  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 800BDF48 000BAB28  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BDF4C 000BAB2C  40 82 00 10 */	bne lbl_800BDF5C
/* 800BDF50 000BAB30  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 800BDF54 000BAB34  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BDF58 000BAB38  41 82 00 90 */	beq lbl_800BDFE8
lbl_800BDF5C:
/* 800BDF5C 000BAB3C  80 BF 00 80 */	lwz r5, 0x80(r31)
/* 800BDF60 000BAB40  38 7F 00 80 */	addi r3, r31, 0x80
/* 800BDF64 000BAB44  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 800BDF68 000BAB48  38 81 00 10 */	addi r4, r1, 0x10
/* 800BDF6C 000BAB4C  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 800BDF70 000BAB50  90 01 00 20 */	stw r0, 0x20(r1)
/* 800BDF74 000BAB54  80 1F 00 88 */	lwz r0, 0x88(r31)
/* 800BDF78 000BAB58  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BDF7C 000BAB5C  4B F4 FC F1 */	bl lbVector_Mirror
/* 800BDF80 000BAB60  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800BDF84 000BAB64  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800BDF88 000BAB68  C0 61 00 1C */	lfs f3, 0x1c(r1)
/* 800BDF8C 000BAB6C  EC 21 00 32 */	fmuls f1, f1, f0
/* 800BDF90 000BAB70  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800BDF94 000BAB74  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDF98 000BAB78  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 800BDF9C 000BAB7C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BDFA0 000BAB80  40 80 00 48 */	bge lbl_800BDFE8
/* 800BDFA4 000BAB84  7F C3 F3 78 */	mr r3, r30
/* 800BDFA8 000BAB88  48 00 04 ED */	bl ftCo_800BE494
/* 800BDFAC 000BAB8C  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 800BDFB0 000BAB90  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BDFB4 000BAB94  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BDFB8 000BAB98  40 80 00 0C */	bge lbl_800BDFC4
/* 800BDFBC 000BAB9C  38 00 FF FF */	li r0, -1
/* 800BDFC0 000BABA0  48 00 00 08 */	b lbl_800BDFC8
lbl_800BDFC4:
/* 800BDFC4 000BABA4  38 00 00 01 */	li r0, 1
lbl_800BDFC8:
/* 800BDFC8 000BABA8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BDFCC 000BABAC  C8 22 91 F8 */	lfd f1, ftCo_804D8BD8
/* 800BDFD0 000BABB0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800BDFD4 000BABB4  3C 00 43 30 */	lis r0, 0x4330
/* 800BDFD8 000BABB8  90 01 00 28 */	stw r0, 0x28(r1)
/* 800BDFDC 000BABBC  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800BDFE0 000BABC0  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BDFE4 000BABC4  D0 1F 23 48 */	stfs f0, 0x2348(r31)
lbl_800BDFE8:
/* 800BDFE8 000BABC8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800BDFEC 000BABCC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800BDFF0 000BABD0  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800BDFF4 000BABD4  38 21 00 38 */	addi r1, r1, 0x38
/* 800BDFF8 000BABD8  7C 08 03 A6 */	mtlr r0
/* 800BDFFC 000BABDC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
