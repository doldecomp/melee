#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_ThrownKirby.h"

#include "ft/ft_081B.h"
#include "ft/ft_0C88.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <math.h>
#include <runtime.h>
#include <baselib/jobj.h>

typedef float (*KirbyVelocityFunc)(ftKb_GObj* gobj, Vec3* victim_self_vel,
                                   float victim_facing_dir);
typedef float (*GetFloatFunc)(ftKb_GObj* gobj);

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
        fp->mv.co.thrownkirby.x18_b1 = true;
    }
}

ASM void ftCo_800BDA74(ftCo_GObj* gobj, Vec3* normal)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    if (ft_800824A0(gobj, &fp->mv.co.thrownkirby.coll_box)) {
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

static inline void inlineB2(ftCo_GObj* gobj, ftKb_GObj* thrower_gobj,
                            Vec3* scale, ftCommon_MotionState msid,
                            KirbyVelocityFunc vel_func, GetFloatFunc get_float)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    fp->facing_dir = -GET_FIGHTER(thrower_gobj)->facing_dir;
    fp->mv.co.thrownkirby.thrower_gobj = thrower_gobj;
    fp->mv.co.thrownkirby.x8 = 0;
    fp->mv.co.thrownkirby.x4 =
        vel_func(thrower_gobj, &fp->self_vel, fp->facing_dir);
    Fighter_UpdateModelScale(gobj);
    HSD_JObjGetScale(jobj, &fp->mv.co.thrownkirby.scale);
    Fighter_ChangeMotionState(gobj, msid, Ft_MF_SkipThrowException, 0, 1, 0,
                              thrower_gobj);
    fp->x21F0 = ftCo_800BE7C0;
    fp->take_dmg_cb = ftCo_800BE7C0;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
    ftCommon_8007EFC0(fp, 1);
    ftCommon_8007DBCC(fp, 0, get_float(thrower_gobj));
    ftAnim_8006EBA4(gobj);
    ftCommon_8007D5D4(fp);
    fp->mv.co.thrownkirby.x18_b0 = false;
    fp->mv.co.thrownkirby.x18_b1 = false;
    ftCommon_SetAccessory(fp, ftKb_SpecialN_800F5898(thrower_gobj, 0));
    scale->x = scale->y = scale->z = inlineB0(gobj);
    HSD_JObjSetScale(fp->x20A0_accessory, scale);
    lb_8000C2F8(fp->x20A0_accessory,
                fp->parts[ftParts_8007500C(fp, FtPart_YRotN)].joint);
}

ASM void ftCo_800BDB58(ftCo_GObj* gobj, ftKb_GObj* thrower_gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    Vec3 scale;
    inlineB2(gobj, thrower_gobj, &scale, ftCo_MS_ThrownKirbyStar,
             ftKb_SpecialN_800F58AC, ftKb_SpecialN_800F5A88);

    /// @todo Possibly another callback in #inlineB2
    ftColl_8007ABD0(fp->x914, inlineB1(gobj), gobj);

    ftKb_SpecialN_800F5820(thrower_gobj, &fp->mv.co.thrownkirby.coll_box,
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
    if (vel_mag > fp->mv.co.thrownkirby.x4) {
        fp->self_vel.x =
            (fp->self_vel.x * (vel_mag - fp->mv.co.thrownkirby.x4)) / vel_mag;
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
    fp->x1A4C -= ftKb_SpecialN_800F5AC0();
}

ASM void ftCo_ThrownKirbyStar_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    inlineA0(gobj);
    fp->mv.co.thrownkirby.x14 =
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

/// @todo Shared code with #ftCo_ThrownCopyStar_Coll but an inline uses too
///       much stack.
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
            fp->mv.co.thrownkirby.x8 = normal.x < 0 ? -1 : +1;
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

ASM void ftCo_800BE000(ftCo_GObj* gobj, ftKb_GObj* thrower_gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Vec3 scale;
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    inlineB2(gobj, thrower_gobj, &scale, ftCo_MS_ThrownCopyStar,
             ftKb_SpecialN_800F58D8, ftKb_SpecialN_800F5AB0);

    /// @todo Possibly another callback in #inlineB2
    ftColl_8007AFF8(gobj);

    ftKb_SpecialN_800F5820(thrower_gobj, &fp->mv.co.thrownkirby.coll_box,
                           scale.x);
}

#else /* clang-format off */
{ nofralloc
/* 800BE000 000BABE0  7C 08 02 A6 */	mflr r0
/* 800BE004 000BABE4  90 01 00 04 */	stw r0, 4(r1)
/* 800BE008 000BABE8  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 800BE00C 000BABEC  93 E1 00 54 */	stw r31, 0x54(r1)
/* 800BE010 000BABF0  93 C1 00 50 */	stw r30, 0x50(r1)
/* 800BE014 000BABF4  7C 9E 23 78 */	mr r30, r4
/* 800BE018 000BABF8  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 800BE01C 000BABFC  7C 7D 1B 78 */	mr r29, r3
/* 800BE020 000BAC00  93 81 00 48 */	stw r28, 0x48(r1)
/* 800BE024 000BAC04  80 84 00 2C */	lwz r4, 0x2c(r4)
/* 800BE028 000BAC08  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BE02C 000BAC0C  7F C3 F3 78 */	mr r3, r30
/* 800BE030 000BAC10  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 800BE034 000BAC14  83 9D 00 28 */	lwz r28, 0x28(r29)
/* 800BE038 000BAC18  38 9F 00 80 */	addi r4, r31, 0x80
/* 800BE03C 000BAC1C  FC 00 00 50 */	fneg f0, f0
/* 800BE040 000BAC20  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BE044 000BAC24  93 DF 23 40 */	stw r30, 0x2340(r31)
/* 800BE048 000BAC28  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE04C 000BAC2C  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 800BE050 000BAC30  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800BE054 000BAC34  48 03 78 85 */	bl ftKb_SpecialN_800F58D8
/* 800BE058 000BAC38  D0 3F 23 44 */	stfs f1, 0x2344(r31)
/* 800BE05C 000BAC3C  7F A3 EB 78 */	mr r3, r29
/* 800BE060 000BAC40  4B FA 9B 55 */	bl Fighter_UpdateModelScale
/* 800BE064 000BAC44  28 1C 00 00 */	cmplwi r28, 0
/* 800BE068 000BAC48  40 82 00 14 */	bne lbl_800BE07C
/* 800BE06C 000BAC4C  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE070 000BAC50  38 80 03 37 */	li r4, 0x337
/* 800BE074 000BAC54  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BE078 000BAC58  48 2C A1 A9 */	bl __assert
lbl_800BE07C:
/* 800BE07C 000BAC5C  34 1F 23 5C */	addic. r0, r31, 0x235c
/* 800BE080 000BAC60  40 82 00 14 */	bne lbl_800BE094
/* 800BE084 000BAC64  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE088 000BAC68  38 80 03 38 */	li r4, 0x338
/* 800BE08C 000BAC6C  38 AD 85 50 */	addi r5, r13, ftCo_804D3BF0
/* 800BE090 000BAC70  48 2C A1 91 */	bl __assert
lbl_800BE094:
/* 800BE094 000BAC74  80 BC 00 2C */	lwz r5, 0x2c(r28)
/* 800BE098 000BAC78  7F A3 EB 78 */	mr r3, r29
/* 800BE09C 000BAC7C  80 1C 00 30 */	lwz r0, 0x30(r28)
/* 800BE0A0 000BAC80  38 DE 00 00 */	addi r6, r30, 0
/* 800BE0A4 000BAC84  38 80 01 23 */	li r4, 0x123
/* 800BE0A8 000BAC88  90 BF 23 5C */	stw r5, 0x235c(r31)
/* 800BE0AC 000BAC8C  38 A0 01 00 */	li r5, 0x100
/* 800BE0B0 000BAC90  90 1F 23 60 */	stw r0, 0x2360(r31)
/* 800BE0B4 000BAC94  80 1C 00 34 */	lwz r0, 0x34(r28)
/* 800BE0B8 000BAC98  90 1F 23 64 */	stw r0, 0x2364(r31)
/* 800BE0BC 000BAC9C  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BE0C0 000BACA0  C0 42 92 14 */	lfs f2, ftCo_804D8BF4
/* 800BE0C4 000BACA4  FC 60 08 90 */	fmr f3, f1
/* 800BE0C8 000BACA8  4B FA B2 E5 */	bl Fighter_ChangeMotionState
/* 800BE0CC 000BACAC  3C 60 80 0C */	lis r3, ftCo_800BE7C0@ha
/* 800BE0D0 000BACB0  38 03 E7 C0 */	addi r0, r3, ftCo_800BE7C0@l
/* 800BE0D4 000BACB4  90 1F 21 F0 */	stw r0, 0x21f0(r31)
/* 800BE0D8 000BACB8  38 7F 00 00 */	addi r3, r31, 0
/* 800BE0DC 000BACBC  38 80 01 FF */	li r4, 0x1ff
/* 800BE0E0 000BACC0  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800BE0E4 000BACC4  4B FC 02 11 */	bl ftCommon_8007E2F4
/* 800BE0E8 000BACC8  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800BE0EC 000BACCC  3B 80 00 01 */	li r28, 1
/* 800BE0F0 000BACD0  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 800BE0F4 000BACD4  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800BE0F8 000BACD8  38 7D 00 00 */	addi r3, r29, 0
/* 800BE0FC 000BACDC  38 80 00 02 */	li r4, 2
/* 800BE100 000BACE0  4B FB D5 2D */	bl ftColl_8007B62C
/* 800BE104 000BACE4  38 7F 00 00 */	addi r3, r31, 0
/* 800BE108 000BACE8  38 80 00 01 */	li r4, 1
/* 800BE10C 000BACEC  4B FC 0E B5 */	bl ftCommon_8007EFC0
/* 800BE110 000BACF0  7F C3 F3 78 */	mr r3, r30
/* 800BE114 000BACF4  48 03 79 9D */	bl ftKb_SpecialN_800F5AB0
/* 800BE118 000BACF8  38 7F 00 00 */	addi r3, r31, 0
/* 800BE11C 000BACFC  38 80 00 00 */	li r4, 0
/* 800BE120 000BAD00  4B FB FA AD */	bl ftCommon_8007DBCC
/* 800BE124 000BAD04  7F A3 EB 78 */	mr r3, r29
/* 800BE128 000BAD08  4B FB 0A 7D */	bl ftAnim_8006EBA4
/* 800BE12C 000BAD0C  7F E3 FB 78 */	mr r3, r31
/* 800BE130 000BAD10  4B FB F4 A5 */	bl ftCommon_8007D5D4
/* 800BE134 000BAD14  88 1F 23 58 */	lbz r0, 0x2358(r31)
/* 800BE138 000BAD18  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 800BE13C 000BAD1C  38 80 00 00 */	li r4, 0
/* 800BE140 000BAD20  98 1F 23 58 */	stb r0, 0x2358(r31)
/* 800BE144 000BAD24  7F C3 F3 78 */	mr r3, r30
/* 800BE148 000BAD28  88 1F 23 58 */	lbz r0, 0x2358(r31)
/* 800BE14C 000BAD2C  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 800BE150 000BAD30  98 1F 23 58 */	stb r0, 0x2358(r31)
/* 800BE154 000BAD34  48 03 77 45 */	bl ftKb_SpecialN_800F5898
/* 800BE158 000BAD38  38 83 00 00 */	addi r4, r3, 0
/* 800BE15C 000BAD3C  38 7F 00 00 */	addi r3, r31, 0
/* 800BE160 000BAD40  4B FC 04 C1 */	bl ftCommon_SetAccessory
/* 800BE164 000BAD44  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 800BE168 000BAD48  C0 03 01 EC */	lfs f0, 0x1ec(r3)
/* 800BE16C 000BAD4C  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800BE170 000BAD50  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800BE174 000BAD54  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800BE178 000BAD58  83 9F 20 A0 */	lwz r28, 0x20a0(r31)
/* 800BE17C 000BAD5C  28 1C 00 00 */	cmplwi r28, 0
/* 800BE180 000BAD60  40 82 00 14 */	bne lbl_800BE194
/* 800BE184 000BAD64  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE188 000BAD68  38 80 02 F8 */	li r4, 0x2f8
/* 800BE18C 000BAD6C  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BE190 000BAD70  48 2C A0 91 */	bl __assert
lbl_800BE194:
/* 800BE194 000BAD74  80 61 00 34 */	lwz r3, 0x34(r1)
/* 800BE198 000BAD78  80 01 00 38 */	lwz r0, 0x38(r1)
/* 800BE19C 000BAD7C  90 7C 00 2C */	stw r3, 0x2c(r28)
/* 800BE1A0 000BAD80  90 1C 00 30 */	stw r0, 0x30(r28)
/* 800BE1A4 000BAD84  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800BE1A8 000BAD88  90 1C 00 34 */	stw r0, 0x34(r28)
/* 800BE1AC 000BAD8C  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800BE1B0 000BAD90  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BE1B4 000BAD94  40 82 00 4C */	bne lbl_800BE200
/* 800BE1B8 000BAD98  28 1C 00 00 */	cmplwi r28, 0
/* 800BE1BC 000BAD9C  41 82 00 44 */	beq lbl_800BE200
/* 800BE1C0 000BADA0  40 82 00 14 */	bne lbl_800BE1D4
/* 800BE1C4 000BADA4  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE1C8 000BADA8  38 80 02 34 */	li r4, 0x234
/* 800BE1CC 000BADAC  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BE1D0 000BADB0  48 2C A0 51 */	bl __assert
lbl_800BE1D4:
/* 800BE1D4 000BADB4  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800BE1D8 000BADB8  38 60 00 00 */	li r3, 0
/* 800BE1DC 000BADBC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BE1E0 000BADC0  40 82 00 10 */	bne lbl_800BE1F0
/* 800BE1E4 000BADC4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BE1E8 000BADC8  41 82 00 08 */	beq lbl_800BE1F0
/* 800BE1EC 000BADCC  38 60 00 01 */	li r3, 1
lbl_800BE1F0:
/* 800BE1F0 000BADD0  2C 03 00 00 */	cmpwi r3, 0
/* 800BE1F4 000BADD4  40 82 00 0C */	bne lbl_800BE200
/* 800BE1F8 000BADD8  7F 83 E3 78 */	mr r3, r28
/* 800BE1FC 000BADDC  48 2B 50 ED */	bl HSD_JObjSetMtxDirtySub
lbl_800BE200:
/* 800BE200 000BADE0  38 7F 00 00 */	addi r3, r31, 0
/* 800BE204 000BADE4  38 80 00 03 */	li r4, 3
/* 800BE208 000BADE8  4B FB 6E 05 */	bl ftParts_8007500C
/* 800BE20C 000BADEC  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800BE210 000BADF0  54 60 20 36 */	slwi r0, r3, 4
/* 800BE214 000BADF4  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 800BE218 000BADF8  7C 84 00 2E */	lwzx r4, r4, r0
/* 800BE21C 000BADFC  4B F4 E0 DD */	bl lb_8000C2F8
/* 800BE220 000BAE00  7F A3 EB 78 */	mr r3, r29
/* 800BE224 000BAE04  4B FB CD D5 */	bl ftColl_8007AFF8
/* 800BE228 000BAE08  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 800BE22C 000BAE0C  38 7E 00 00 */	addi r3, r30, 0
/* 800BE230 000BAE10  38 9F 23 68 */	addi r4, r31, 0x2368
/* 800BE234 000BAE14  48 03 75 ED */	bl ftKb_SpecialN_800F5820
/* 800BE238 000BAE18  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800BE23C 000BAE1C  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 800BE240 000BAE20  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 800BE244 000BAE24  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 800BE248 000BAE28  83 81 00 48 */	lwz r28, 0x48(r1)
/* 800BE24C 000BAE2C  38 21 00 58 */	addi r1, r1, 0x58
/* 800BE250 000BAE30  7C 08 03 A6 */	mtlr r0
/* 800BE254 000BAE34  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_ThrownCopyStar_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownCopyStar_IASA(ftCo_GObj* gobj) {}

ASM void ftCo_ThrownCopyStar_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    float dist = sqrtf(SQ(fp->self_vel.x) + SQ(fp->self_vel.y));
    if (dist > fp->mv.co.thrownkirby.x4) {
        fp->self_vel.x =
            fp->self_vel.x * (dist - fp->mv.co.thrownkirby.x4) / dist;
        fp->self_vel.y =
            fp->self_vel.y * (dist - fp->mv.co.thrownkirby.x4) / dist;
        if (fp->self_vel.y < 0) {
            fp->facing_dir = -1;
        } else {
            fp->facing_dir = +1;
        }
    } else {
        fp->self_vel.x = 0;
    }
    fp->x1A4C -= ftKb_SpecialN_800F5AC0();
    fp->mv.co.thrownkirby.x14 =
        ftCommon_8007DC08(fp, ftKb_SpecialN_800F5AD8());
    if (fp->x1A4C <= 0) {
        ftCo_800BE494(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BE260 000BAE40  7C 08 02 A6 */	mflr r0
/* 800BE264 000BAE44  90 01 00 04 */	stw r0, 4(r1)
/* 800BE268 000BAE48  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BE26C 000BAE4C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BE270 000BAE50  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BE274 000BAE54  7C 7E 1B 78 */	mr r30, r3
/* 800BE278 000BAE58  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BE27C 000BAE5C  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE280 000BAE60  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800BE284 000BAE64  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BE288 000BAE68  EC 42 00 B2 */	fmuls f2, f2, f2
/* 800BE28C 000BAE6C  EC 21 00 72 */	fmuls f1, f1, f1
/* 800BE290 000BAE70  EC 82 08 2A */	fadds f4, f2, f1
/* 800BE294 000BAE74  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800BE298 000BAE78  40 81 00 50 */	ble lbl_800BE2E8
/* 800BE29C 000BAE7C  FC 20 20 34 */	frsqrte f1, f4
/* 800BE2A0 000BAE80  C8 62 92 00 */	lfd f3, ftCo_804D8BE0
/* 800BE2A4 000BAE84  C8 42 92 08 */	lfd f2, ftCo_804D8BE8
/* 800BE2A8 000BAE88  FC 01 00 72 */	fmul f0, f1, f1
/* 800BE2AC 000BAE8C  FC 23 00 72 */	fmul f1, f3, f1
/* 800BE2B0 000BAE90  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BE2B4 000BAE94  FC 21 00 32 */	fmul f1, f1, f0
/* 800BE2B8 000BAE98  FC 01 00 72 */	fmul f0, f1, f1
/* 800BE2BC 000BAE9C  FC 23 00 72 */	fmul f1, f3, f1
/* 800BE2C0 000BAEA0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BE2C4 000BAEA4  FC 21 00 32 */	fmul f1, f1, f0
/* 800BE2C8 000BAEA8  FC 01 00 72 */	fmul f0, f1, f1
/* 800BE2CC 000BAEAC  FC 23 00 72 */	fmul f1, f3, f1
/* 800BE2D0 000BAEB0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800BE2D4 000BAEB4  FC 01 00 32 */	fmul f0, f1, f0
/* 800BE2D8 000BAEB8  FC 04 00 32 */	fmul f0, f4, f0
/* 800BE2DC 000BAEBC  FC 00 00 18 */	frsp f0, f0
/* 800BE2E0 000BAEC0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800BE2E4 000BAEC4  C0 81 00 14 */	lfs f4, 0x14(r1)
lbl_800BE2E8:
/* 800BE2E8 000BAEC8  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800BE2EC 000BAECC  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800BE2F0 000BAED0  40 81 00 58 */	ble lbl_800BE348
/* 800BE2F4 000BAED4  EC 04 00 28 */	fsubs f0, f4, f0
/* 800BE2F8 000BAED8  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 800BE2FC 000BAEDC  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BE300 000BAEE0  EC 00 20 24 */	fdivs f0, f0, f4
/* 800BE304 000BAEE4  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800BE308 000BAEE8  C0 1F 23 44 */	lfs f0, 0x2344(r31)
/* 800BE30C 000BAEEC  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BE310 000BAEF0  EC 04 00 28 */	fsubs f0, f4, f0
/* 800BE314 000BAEF4  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BE318 000BAEF8  EC 00 20 24 */	fdivs f0, f0, f4
/* 800BE31C 000BAEFC  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800BE320 000BAF00  C0 3F 00 84 */	lfs f1, 0x84(r31)
/* 800BE324 000BAF04  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE328 000BAF08  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BE32C 000BAF0C  40 80 00 10 */	bge lbl_800BE33C
/* 800BE330 000BAF10  C0 02 92 10 */	lfs f0, ftCo_804D8BF0
/* 800BE334 000BAF14  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BE338 000BAF18  48 00 00 18 */	b lbl_800BE350
lbl_800BE33C:
/* 800BE33C 000BAF1C  C0 02 92 14 */	lfs f0, ftCo_804D8BF4
/* 800BE340 000BAF20  D0 1F 00 2C */	stfs f0, 0x2c(r31)
/* 800BE344 000BAF24  48 00 00 0C */	b lbl_800BE350
lbl_800BE348:
/* 800BE348 000BAF28  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE34C 000BAF2C  D0 1F 00 80 */	stfs f0, 0x80(r31)
lbl_800BE350:
/* 800BE350 000BAF30  48 03 77 71 */	bl ftKb_SpecialN_800F5AC0
/* 800BE354 000BAF34  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BE358 000BAF38  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BE35C 000BAF3C  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800BE360 000BAF40  48 03 77 79 */	bl ftKb_SpecialN_800F5AD8
/* 800BE364 000BAF44  7F E3 FB 78 */	mr r3, r31
/* 800BE368 000BAF48  4B FB F8 A1 */	bl ftCommon_8007DC08
/* 800BE36C 000BAF4C  90 7F 23 54 */	stw r3, 0x2354(r31)
/* 800BE370 000BAF50  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800BE374 000BAF54  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE378 000BAF58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BE37C 000BAF5C  4C 40 13 82 */	cror 2, 0, 2
/* 800BE380 000BAF60  40 82 00 0C */	bne lbl_800BE38C
/* 800BE384 000BAF64  7F C3 F3 78 */	mr r3, r30
/* 800BE388 000BAF68  48 00 01 0D */	bl ftCo_800BE494
lbl_800BE38C:
/* 800BE38C 000BAF6C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BE390 000BAF70  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BE394 000BAF74  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BE398 000BAF78  38 21 00 28 */	addi r1, r1, 0x28
/* 800BE39C 000BAF7C  7C 08 03 A6 */	mtlr r0
/* 800BE3A0 000BAF80  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

/// @todo Shared code with #ftCo_ThrownKirbyStar_Coll but an inline uses too
///       much stack.
ASM void ftCo_ThrownCopyStar_Coll(ftCo_GObj* gobj)
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
            fp->mv.co.thrownkirby.x8 = normal.x < 0 ? -1 : +1;
        }
    }
}
#else /* clang-format off */
{ nofralloc
/* 800BE3A4 000BAF84  7C 08 02 A6 */	mflr r0
/* 800BE3A8 000BAF88  90 01 00 04 */	stw r0, 4(r1)
/* 800BE3AC 000BAF8C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800BE3B0 000BAF90  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800BE3B4 000BAF94  38 81 00 10 */	addi r4, r1, 0x10
/* 800BE3B8 000BAF98  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800BE3BC 000BAF9C  7C 7E 1B 78 */	mr r30, r3
/* 800BE3C0 000BAFA0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BE3C4 000BAFA4  4B FF F6 B1 */	bl ftCo_800BDA74
/* 800BE3C8 000BAFA8  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800BE3CC 000BAFAC  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BE3D0 000BAFB0  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BE3D4 000BAFB4  40 82 00 1C */	bne lbl_800BE3F0
/* 800BE3D8 000BAFB8  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 800BE3DC 000BAFBC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BE3E0 000BAFC0  40 82 00 10 */	bne lbl_800BE3F0
/* 800BE3E4 000BAFC4  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 800BE3E8 000BAFC8  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 800BE3EC 000BAFCC  41 82 00 90 */	beq lbl_800BE47C
lbl_800BE3F0:
/* 800BE3F0 000BAFD0  80 BF 00 80 */	lwz r5, 0x80(r31)
/* 800BE3F4 000BAFD4  38 7F 00 80 */	addi r3, r31, 0x80
/* 800BE3F8 000BAFD8  80 1F 00 84 */	lwz r0, 0x84(r31)
/* 800BE3FC 000BAFDC  38 81 00 10 */	addi r4, r1, 0x10
/* 800BE400 000BAFE0  90 A1 00 1C */	stw r5, 0x1c(r1)
/* 800BE404 000BAFE4  90 01 00 20 */	stw r0, 0x20(r1)
/* 800BE408 000BAFE8  80 1F 00 88 */	lwz r0, 0x88(r31)
/* 800BE40C 000BAFEC  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BE410 000BAFF0  4B F4 F8 5D */	bl lbVector_Mirror
/* 800BE414 000BAFF4  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800BE418 000BAFF8  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800BE41C 000BAFFC  C0 61 00 1C */	lfs f3, 0x1c(r1)
/* 800BE420 000BB000  EC 21 00 32 */	fmuls f1, f1, f0
/* 800BE424 000BB004  C0 5F 00 80 */	lfs f2, 0x80(r31)
/* 800BE428 000BB008  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE42C 000BB00C  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 800BE430 000BB010  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BE434 000BB014  40 80 00 48 */	bge lbl_800BE47C
/* 800BE438 000BB018  7F C3 F3 78 */	mr r3, r30
/* 800BE43C 000BB01C  48 00 00 59 */	bl ftCo_800BE494
/* 800BE440 000BB020  C0 21 00 10 */	lfs f1, 0x10(r1)
/* 800BE444 000BB024  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE448 000BB028  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BE44C 000BB02C  40 80 00 0C */	bge lbl_800BE458
/* 800BE450 000BB030  38 00 FF FF */	li r0, -1
/* 800BE454 000BB034  48 00 00 08 */	b lbl_800BE45C
lbl_800BE458:
/* 800BE458 000BB038  38 00 00 01 */	li r0, 1
lbl_800BE45C:
/* 800BE45C 000BB03C  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BE460 000BB040  C8 22 91 F8 */	lfd f1, ftCo_804D8BD8
/* 800BE464 000BB044  90 01 00 2C */	stw r0, 0x2c(r1)
/* 800BE468 000BB048  3C 00 43 30 */	lis r0, 0x4330
/* 800BE46C 000BB04C  90 01 00 28 */	stw r0, 0x28(r1)
/* 800BE470 000BB050  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 800BE474 000BB054  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BE478 000BB058  D0 1F 23 48 */	stfs f0, 0x2348(r31)
lbl_800BE47C:
/* 800BE47C 000BB05C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800BE480 000BB060  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800BE484 000BB064  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800BE488 000BB068  38 21 00 38 */	addi r1, r1, 0x38
/* 800BE48C 000BB06C  7C 08 03 A6 */	mtlr r0
/* 800BE490 000BB070  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800BE494(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
/// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_ThrownKirby, Ft_MF_Unk06, 0, 1, 0,
                              NULL);
    fp->x21F0 = ftCo_800BE7C0;
    fp->take_dmg_cb = ftCo_800BE7C0;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221E_b0 = false;
    ftColl_8007B62C(gobj, 0);
    if (!fp->mv.co.thrownkirby.x18_b0) {
        Vec2 self_vel;
        ftKb_SpecialN_800F5874(&self_vel);
        fp->self_vel.y = self_vel.y;
        if (fp->mv.ca.specialhi.vel.y) {
            fp->self_vel.x = fp->mv.ca.specialhi.vel.y * self_vel.x;
        } else {
            fp->self_vel.x = self_vel.x * (fp->self_vel.x < 0 ? -1 : +1);
        }
    } else if (fp->kind == FTKIND_KIRBY && fp->mv.co.thrownkirby.x18_b1 &&
               !fp->fv.kb.x8_b0)
    {
        ftKb_SpecialN_800F190C(gobj, fp->fv.kb.victim_kind);
        ftKb_SpecialN_800EEEC4(gobj, fp->fv.kb.victim_kind);
        fp->fv.kb.victim_kind = FTKIND_KIRBY;
    }
    fp->mv.co.thrownkirby.x10 = ftKb_SpecialN_800F5A98();
    ftCommon_8007DBCC(fp, 0, fp->mv.co.thrownkirby.x10);
    fp->mv.co.thrownkirby.xC = ftKb_SpecialN_800F5A70();
    ftAnim_8006EBA4(gobj);
    ftCommon_8007D5D4(fp);
    fp->accessory4_cb = ftCo_800BE6AC;
}

#else /* clang-format off */
{ nofralloc
/* 800BE494 000BB074  7C 08 02 A6 */	mflr r0
/* 800BE498 000BB078  38 80 01 24 */	li r4, 0x124
/* 800BE49C 000BB07C  90 01 00 04 */	stw r0, 4(r1)
/* 800BE4A0 000BB080  38 A0 00 40 */	li r5, 0x40
/* 800BE4A4 000BB084  38 C0 00 00 */	li r6, 0
/* 800BE4A8 000BB088  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800BE4AC 000BB08C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800BE4B0 000BB090  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800BE4B4 000BB094  7C 7E 1B 78 */	mr r30, r3
/* 800BE4B8 000BB098  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BE4BC 000BB09C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BE4C0 000BB0A0  FC 60 08 90 */	fmr f3, f1
/* 800BE4C4 000BB0A4  C0 42 92 14 */	lfs f2, ftCo_804D8BF4
/* 800BE4C8 000BB0A8  4B FA AE E5 */	bl Fighter_ChangeMotionState
/* 800BE4CC 000BB0AC  3C 60 80 0C */	lis r3, ftCo_800BE7C0@ha
/* 800BE4D0 000BB0B0  38 03 E7 C0 */	addi r0, r3, ftCo_800BE7C0@l
/* 800BE4D4 000BB0B4  90 1F 21 F0 */	stw r0, 0x21f0(r31)
/* 800BE4D8 000BB0B8  38 7F 00 00 */	addi r3, r31, 0
/* 800BE4DC 000BB0BC  38 80 01 FF */	li r4, 0x1ff
/* 800BE4E0 000BB0C0  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800BE4E4 000BB0C4  4B FB FE 11 */	bl ftCommon_8007E2F4
/* 800BE4E8 000BB0C8  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800BE4EC 000BB0CC  38 60 00 00 */	li r3, 0
/* 800BE4F0 000BB0D0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 800BE4F4 000BB0D4  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800BE4F8 000BB0D8  38 7E 00 00 */	addi r3, r30, 0
/* 800BE4FC 000BB0DC  38 80 00 00 */	li r4, 0
/* 800BE500 000BB0E0  4B FB D1 2D */	bl ftColl_8007B62C
/* 800BE504 000BB0E4  88 7F 23 58 */	lbz r3, 0x2358(r31)
/* 800BE508 000BB0E8  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 800BE50C 000BB0EC  40 82 00 78 */	bne lbl_800BE584
/* 800BE510 000BB0F0  38 61 00 10 */	addi r3, r1, 0x10
/* 800BE514 000BB0F4  48 03 73 61 */	bl ftKb_SpecialN_800F5874
/* 800BE518 000BB0F8  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 800BE51C 000BB0FC  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800BE520 000BB100  C0 5F 23 48 */	lfs f2, 0x2348(r31)
/* 800BE524 000BB104  C0 22 91 F0 */	lfs f1, ftCo_804D8BD0
/* 800BE528 000BB108  FC 02 08 00 */	fcmpu cr0, f2, f1
/* 800BE52C 000BB10C  41 82 00 14 */	beq lbl_800BE540
/* 800BE530 000BB110  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 800BE534 000BB114  EC 02 00 32 */	fmuls f0, f2, f0
/* 800BE538 000BB118  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800BE53C 000BB11C  48 00 00 88 */	b lbl_800BE5C4
lbl_800BE540:
/* 800BE540 000BB120  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 800BE544 000BB124  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800BE548 000BB128  40 80 00 0C */	bge lbl_800BE554
/* 800BE54C 000BB12C  38 00 FF FF */	li r0, -1
/* 800BE550 000BB130  48 00 00 08 */	b lbl_800BE558
lbl_800BE554:
/* 800BE554 000BB134  38 00 00 01 */	li r0, 1
lbl_800BE558:
/* 800BE558 000BB138  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800BE55C 000BB13C  C8 22 91 F8 */	lfd f1, ftCo_804D8BD8
/* 800BE560 000BB140  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BE564 000BB144  3C 00 43 30 */	lis r0, 0x4330
/* 800BE568 000BB148  C0 41 00 10 */	lfs f2, 0x10(r1)
/* 800BE56C 000BB14C  90 01 00 20 */	stw r0, 0x20(r1)
/* 800BE570 000BB150  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 800BE574 000BB154  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BE578 000BB158  EC 02 00 32 */	fmuls f0, f2, f0
/* 800BE57C 000BB15C  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800BE580 000BB160  48 00 00 44 */	b lbl_800BE5C4
lbl_800BE584:
/* 800BE584 000BB164  80 1F 00 04 */	lwz r0, 4(r31)
/* 800BE588 000BB168  2C 00 00 04 */	cmpwi r0, 4
/* 800BE58C 000BB16C  40 82 00 38 */	bne lbl_800BE5C4
/* 800BE590 000BB170  54 60 D7 FF */	rlwinm. r0, r3, 0x1a, 0x1f, 0x1f
/* 800BE594 000BB174  41 82 00 30 */	beq lbl_800BE5C4
/* 800BE598 000BB178  88 1F 22 34 */	lbz r0, 0x2234(r31)
/* 800BE59C 000BB17C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BE5A0 000BB180  40 82 00 24 */	bne lbl_800BE5C4
/* 800BE5A4 000BB184  7F C3 F3 78 */	mr r3, r30
/* 800BE5A8 000BB188  80 9F 22 38 */	lwz r4, 0x2238(r31)
/* 800BE5AC 000BB18C  48 03 33 61 */	bl ftKb_SpecialN_800F190C
/* 800BE5B0 000BB190  7F C3 F3 78 */	mr r3, r30
/* 800BE5B4 000BB194  80 9F 22 38 */	lwz r4, 0x2238(r31)
/* 800BE5B8 000BB198  48 03 09 0D */	bl ftKb_SpecialN_800EEEC4
/* 800BE5BC 000BB19C  38 00 00 04 */	li r0, 4
/* 800BE5C0 000BB1A0  90 1F 22 38 */	stw r0, 0x2238(r31)
lbl_800BE5C4:
/* 800BE5C4 000BB1A4  48 03 74 D5 */	bl ftKb_SpecialN_800F5A98
/* 800BE5C8 000BB1A8  D0 3F 23 50 */	stfs f1, 0x2350(r31)
/* 800BE5CC 000BB1AC  38 7F 00 00 */	addi r3, r31, 0
/* 800BE5D0 000BB1B0  38 80 00 00 */	li r4, 0
/* 800BE5D4 000BB1B4  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 800BE5D8 000BB1B8  4B FB F5 F5 */	bl ftCommon_8007DBCC
/* 800BE5DC 000BB1BC  48 03 74 95 */	bl ftKb_SpecialN_800F5A70
/* 800BE5E0 000BB1C0  D0 3F 23 4C */	stfs f1, 0x234c(r31)
/* 800BE5E4 000BB1C4  7F C3 F3 78 */	mr r3, r30
/* 800BE5E8 000BB1C8  4B FB 05 BD */	bl ftAnim_8006EBA4
/* 800BE5EC 000BB1CC  7F E3 FB 78 */	mr r3, r31
/* 800BE5F0 000BB1D0  4B FB EF E5 */	bl ftCommon_8007D5D4
/* 800BE5F4 000BB1D4  3C 60 80 0C */	lis r3, ftCo_800BE6AC@ha
/* 800BE5F8 000BB1D8  38 03 E6 AC */	addi r0, r3, ftCo_800BE6AC@l
/* 800BE5FC 000BB1DC  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800BE600 000BB1E0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800BE604 000BB1E4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800BE608 000BB1E8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800BE60C 000BB1EC  38 21 00 30 */	addi r1, r1, 0x30
/* 800BE610 000BB1F0  7C 08 03 A6 */	mtlr r0
/* 800BE614 000BB1F4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_ThrownKirby_Anim(ftCo_GObj* gobj) {}

void ftCo_ThrownKirby_IASA(ftCo_GObj* gobj) {}

static inline void inlineC0(ftCo_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
    ftCo_800CC730(gobj);
}

ASM void ftCo_ThrownKirby_Phys(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[28] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= ftKb_SpecialN_800F5AC0();
    if (!fp->mv.co.thrownkirby.x18_b0) {
        if (fp->x1A4C <= 0) {
            inlineC0(gobj);
        }
    } else {
        inlineC0(gobj);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BE620 000BB200  7C 08 02 A6 */	mflr r0
/* 800BE624 000BB204  90 01 00 04 */	stw r0, 4(r1)
/* 800BE628 000BB208  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800BE62C 000BB20C  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800BE630 000BB210  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800BE634 000BB214  7C 7E 1B 78 */	mr r30, r3
/* 800BE638 000BB218  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BE63C 000BB21C  48 03 74 85 */	bl ftKb_SpecialN_800F5AC0
/* 800BE640 000BB220  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BE644 000BB224  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BE648 000BB228  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800BE64C 000BB22C  88 1F 23 58 */	lbz r0, 0x2358(r31)
/* 800BE650 000BB230  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BE654 000BB234  40 82 00 2C */	bne lbl_800BE680
/* 800BE658 000BB238  C0 3F 1A 4C */	lfs f1, 0x1a4c(r31)
/* 800BE65C 000BB23C  C0 02 91 F0 */	lfs f0, ftCo_804D8BD0
/* 800BE660 000BB240  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BE664 000BB244  4C 40 13 82 */	cror 2, 0, 2
/* 800BE668 000BB248  40 82 00 28 */	bne lbl_800BE690
/* 800BE66C 000BB24C  7F C3 F3 78 */	mr r3, r30
/* 800BE670 000BB250  4B FA 95 45 */	bl Fighter_UpdateModelScale
/* 800BE674 000BB254  7F C3 F3 78 */	mr r3, r30
/* 800BE678 000BB258  48 00 E0 B9 */	bl ftCo_800CC730
/* 800BE67C 000BB25C  48 00 00 14 */	b lbl_800BE690
lbl_800BE680:
/* 800BE680 000BB260  7F C3 F3 78 */	mr r3, r30
/* 800BE684 000BB264  4B FA 95 31 */	bl Fighter_UpdateModelScale
/* 800BE688 000BB268  7F C3 F3 78 */	mr r3, r30
/* 800BE68C 000BB26C  48 00 E0 A5 */	bl ftCo_800CC730
lbl_800BE690:
/* 800BE690 000BB270  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800BE694 000BB274  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800BE698 000BB278  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800BE69C 000BB27C  38 21 00 38 */	addi r1, r1, 0x38
/* 800BE6A0 000BB280  7C 08 03 A6 */	mtlr r0
/* 800BE6A4 000BB284  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_ThrownKirby_Coll(ftCo_GObj* gobj) {}

ASM void ftCo_800BE6AC(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 scale;
    scale.x = scale.y = scale.z = (1 - fp->mv.co.thrownkirby.xC) +
                                  (((fp->mv.co.thrownkirby.x10 - fp->x1A4C) /
                                    fp->mv.co.thrownkirby.x10) *
                                   fp->mv.co.thrownkirby.xC);
    scale.x *= fp->mv.co.thrownkirby.scale.x;
    scale.y *= fp->mv.co.thrownkirby.scale.y;
    scale.z *= fp->mv.co.thrownkirby.scale.z;
    HSD_JObjSetScale(jobj, &scale);
}

#else /* clang-format off */
{ nofralloc
/* 800BE6AC 000BB28C  7C 08 02 A6 */	mflr r0
/* 800BE6B0 000BB290  90 01 00 04 */	stw r0, 4(r1)
/* 800BE6B4 000BB294  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BE6B8 000BB298  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BE6BC 000BB29C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800BE6C0 000BB2A0  80 03 00 28 */	lwz r0, 0x28(r3)
/* 800BE6C4 000BB2A4  C0 44 23 50 */	lfs f2, 0x2350(r4)
/* 800BE6C8 000BB2A8  C0 04 1A 4C */	lfs f0, 0x1a4c(r4)
/* 800BE6CC 000BB2AC  28 00 00 00 */	cmplwi r0, 0
/* 800BE6D0 000BB2B0  C0 64 23 4C */	lfs f3, 0x234c(r4)
/* 800BE6D4 000BB2B4  7C 1F 03 78 */	mr r31, r0
/* 800BE6D8 000BB2B8  EC 22 00 28 */	fsubs f1, f2, f0
/* 800BE6DC 000BB2BC  C0 02 92 14 */	lfs f0, ftCo_804D8BF4
/* 800BE6E0 000BB2C0  EC 21 10 24 */	fdivs f1, f1, f2
/* 800BE6E4 000BB2C4  EC 21 00 F2 */	fmuls f1, f1, f3
/* 800BE6E8 000BB2C8  EC 00 18 28 */	fsubs f0, f0, f3
/* 800BE6EC 000BB2CC  EC 00 08 2A */	fadds f0, f0, f1
/* 800BE6F0 000BB2D0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800BE6F4 000BB2D4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800BE6F8 000BB2D8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800BE6FC 000BB2DC  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800BE700 000BB2E0  C0 04 23 5C */	lfs f0, 0x235c(r4)
/* 800BE704 000BB2E4  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BE708 000BB2E8  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800BE70C 000BB2EC  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 800BE710 000BB2F0  C0 04 23 60 */	lfs f0, 0x2360(r4)
/* 800BE714 000BB2F4  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BE718 000BB2F8  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800BE71C 000BB2FC  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800BE720 000BB300  C0 04 23 64 */	lfs f0, 0x2364(r4)
/* 800BE724 000BB304  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BE728 000BB308  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800BE72C 000BB30C  40 82 00 14 */	bne lbl_800BE740
/* 800BE730 000BB310  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE734 000BB314  38 80 02 F8 */	li r4, 0x2f8
/* 800BE738 000BB318  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BE73C 000BB31C  48 2C 9A E5 */	bl __assert
lbl_800BE740:
/* 800BE740 000BB320  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800BE744 000BB324  80 01 00 18 */	lwz r0, 0x18(r1)
/* 800BE748 000BB328  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 800BE74C 000BB32C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 800BE750 000BB330  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BE754 000BB334  90 1F 00 34 */	stw r0, 0x34(r31)
/* 800BE758 000BB338  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 800BE75C 000BB33C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BE760 000BB340  40 82 00 4C */	bne lbl_800BE7AC
/* 800BE764 000BB344  28 1F 00 00 */	cmplwi r31, 0
/* 800BE768 000BB348  41 82 00 44 */	beq lbl_800BE7AC
/* 800BE76C 000BB34C  40 82 00 14 */	bne lbl_800BE780
/* 800BE770 000BB350  38 6D 85 40 */	addi r3, r13, ftCo_804D3BE0
/* 800BE774 000BB354  38 80 02 34 */	li r4, 0x234
/* 800BE778 000BB358  38 AD 85 48 */	addi r5, r13, ftCo_804D3BE8
/* 800BE77C 000BB35C  48 2C 9A A5 */	bl __assert
lbl_800BE780:
/* 800BE780 000BB360  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 800BE784 000BB364  38 60 00 00 */	li r3, 0
/* 800BE788 000BB368  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BE78C 000BB36C  40 82 00 10 */	bne lbl_800BE79C
/* 800BE790 000BB370  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BE794 000BB374  41 82 00 08 */	beq lbl_800BE79C
/* 800BE798 000BB378  38 60 00 01 */	li r3, 1
lbl_800BE79C:
/* 800BE79C 000BB37C  2C 03 00 00 */	cmpwi r3, 0
/* 800BE7A0 000BB380  40 82 00 0C */	bne lbl_800BE7AC
/* 800BE7A4 000BB384  7F E3 FB 78 */	mr r3, r31
/* 800BE7A8 000BB388  48 2B 4B 41 */	bl HSD_JObjSetMtxDirtySub
lbl_800BE7AC:
/* 800BE7AC 000BB38C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BE7B0 000BB390  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BE7B4 000BB394  38 21 00 28 */	addi r1, r1, 0x28
/* 800BE7B8 000BB398  7C 08 03 A6 */	mtlr r0
/* 800BE7BC 000BB39C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_800BE7C0(ftCo_GObj* gobj)
{
    Fighter_UpdateModelScale(gobj);
}
