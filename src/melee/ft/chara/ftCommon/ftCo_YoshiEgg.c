#include <platform.h>
#include "ft/forward.h"

#include "ftCo_YoshiEgg.h"

#include "ftCo_CaptureCaptain.h"
#include "ftCo_CaptureKoopa.h"

#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0C08.h"
#include "ft/ft_0C88.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftYoshi/ftYs_Guard.h"
#include "ftYoshi/ftYs_SpecialN.h"
#include "lb/lb_00B0.h"

#include <placeholder.h>
#include <baselib/jobj.h>

#ifdef MWERKS_GEKKO
float const ftCo_804D8B68 = 0;
float const ftCo_804D8B6C = 1;
extern char* ftCo_804D3B88;
extern char* ftCo_804D3B90;
extern char* ftCo_804D3B98;
#endif

#ifdef WIP
#pragma force_active on
#endif

void ftCo_800BBC88(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221E_b0 = true;
    ftColl_8007B62C(gobj, 2);
}

ASM void ftCo_800BBCC0(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj1 = gobj->hsd_obj;
    if (fp->mv.co.yoshiegg.x14 <= 0) {
        Fighter_UpdateModelScale(gobj);
        fp->accessory4_cb = NULL;
        return;
    }
    fp->mv.co.yoshiegg.x14 -= 1;
    {
        Vec3 vec1, vec0;
        float temp0 = (fp->mv.co.yoshiegg.x10 - fp->mv.co.yoshiegg.x14) /
                      fp->mv.co.yoshiegg.x10;
        temp0 *= fp->mv.co.yoshiegg.xC;
        {
            float temp1 = (1 - fp->mv.co.yoshiegg.xC) + temp0;
            vec1.x = vec1.y = vec1.z = temp1;
            vec0 = vec1;
            vec1.x = vec1.x * fp->mv.co.yoshiegg.x18.x;
            vec1.y *= fp->mv.co.yoshiegg.x18.y;
            vec1.z *= fp->mv.co.yoshiegg.x18.z;
            HSD_JObjSetScale(jobj1, &vec1);
            vec0.x = vec0.x * fp->mv.co.yoshiegg.scale.x;
            vec0.y *= fp->mv.co.yoshiegg.scale.y;
            vec0.z *= fp->mv.co.yoshiegg.scale.z;
            HSD_JObjSetScale(fp->x20A0_accessory, &vec0);
        }
    }
}
#else /* clang-format off */
{ nofralloc
/* 800BBCC0 000B88A0  7C 08 02 A6 */	mflr r0
/* 800BBCC4 000B88A4  90 01 00 04 */	stw r0, 4(r1)
/* 800BBCC8 000B88A8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800BBCCC 000B88AC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800BBCD0 000B88B0  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800BBCD4 000B88B4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BBCD8 000B88B8  C0 02 91 88 */	lfs f0, ftCo_804D8B68
/* 800BBCDC 000B88BC  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 800BBCE0 000B88C0  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 800BBCE4 000B88C4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BBCE8 000B88C8  4C 40 13 82 */	cror 2, 0, 2
/* 800BBCEC 000B88CC  40 82 00 14 */	bne lbl_800BBD00
/* 800BBCF0 000B88D0  4B FA BE C5 */	bl Fighter_UpdateModelScale
/* 800BBCF4 000B88D4  38 00 00 00 */	li r0, 0
/* 800BBCF8 000B88D8  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800BBCFC 000B88DC  48 00 01 C0 */	b lbl_800BBEBC
lbl_800BBD00:
/* 800BBD00 000B88E0  C0 42 91 8C */	lfs f2, ftCo_804D8B6C
/* 800BBD04 000B88E4  28 1E 00 00 */	cmplwi r30, 0
/* 800BBD08 000B88E8  EC 01 10 28 */	fsubs f0, f1, f2
/* 800BBD0C 000B88EC  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 800BBD10 000B88F0  C0 7F 23 50 */	lfs f3, 0x2350(r31)
/* 800BBD14 000B88F4  C0 1F 23 54 */	lfs f0, 0x2354(r31)
/* 800BBD18 000B88F8  C0 9F 23 4C */	lfs f4, 0x234c(r31)
/* 800BBD1C 000B88FC  EC 23 00 28 */	fsubs f1, f3, f0
/* 800BBD20 000B8900  EC 02 20 28 */	fsubs f0, f2, f4
/* 800BBD24 000B8904  EC 21 18 24 */	fdivs f1, f1, f3
/* 800BBD28 000B8908  EC 21 01 32 */	fmuls f1, f1, f4
/* 800BBD2C 000B890C  EC 00 08 2A */	fadds f0, f0, f1
/* 800BBD30 000B8910  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800BBD34 000B8914  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800BBD38 000B8918  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800BBD3C 000B891C  80 01 00 20 */	lwz r0, 0x20(r1)
/* 800BBD40 000B8920  80 61 00 24 */	lwz r3, 0x24(r1)
/* 800BBD44 000B8924  90 01 00 14 */	stw r0, 0x14(r1)
/* 800BBD48 000B8928  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800BBD4C 000B892C  90 61 00 18 */	stw r3, 0x18(r1)
/* 800BBD50 000B8930  C0 21 00 20 */	lfs f1, 0x20(r1)
/* 800BBD54 000B8934  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800BBD58 000B8938  C0 1F 23 58 */	lfs f0, 0x2358(r31)
/* 800BBD5C 000B893C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBD60 000B8940  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800BBD64 000B8944  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 800BBD68 000B8948  C0 1F 23 5C */	lfs f0, 0x235c(r31)
/* 800BBD6C 000B894C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBD70 000B8950  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800BBD74 000B8954  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 800BBD78 000B8958  C0 1F 23 60 */	lfs f0, 0x2360(r31)
/* 800BBD7C 000B895C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBD80 000B8960  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 800BBD84 000B8964  40 82 00 14 */	bne lbl_800BBD98
/* 800BBD88 000B8968  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBD8C 000B896C  38 80 02 F8 */	li r4, 0x2f8
/* 800BBD90 000B8970  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBD94 000B8974  48 2C C4 8D */	bl __assert
lbl_800BBD98:
/* 800BBD98 000B8978  80 61 00 20 */	lwz r3, 0x20(r1)
/* 800BBD9C 000B897C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800BBDA0 000B8980  90 7E 00 2C */	stw r3, 0x2c(r30)
/* 800BBDA4 000B8984  90 1E 00 30 */	stw r0, 0x30(r30)
/* 800BBDA8 000B8988  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800BBDAC 000B898C  90 1E 00 34 */	stw r0, 0x34(r30)
/* 800BBDB0 000B8990  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 800BBDB4 000B8994  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BBDB8 000B8998  40 82 00 4C */	bne lbl_800BBE04
/* 800BBDBC 000B899C  28 1E 00 00 */	cmplwi r30, 0
/* 800BBDC0 000B89A0  41 82 00 44 */	beq lbl_800BBE04
/* 800BBDC4 000B89A4  40 82 00 14 */	bne lbl_800BBDD8
/* 800BBDC8 000B89A8  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBDCC 000B89AC  38 80 02 34 */	li r4, 0x234
/* 800BBDD0 000B89B0  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBDD4 000B89B4  48 2C C4 4D */	bl __assert
lbl_800BBDD8:
/* 800BBDD8 000B89B8  80 9E 00 14 */	lwz r4, 0x14(r30)
/* 800BBDDC 000B89BC  38 60 00 00 */	li r3, 0
/* 800BBDE0 000B89C0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BBDE4 000B89C4  40 82 00 10 */	bne lbl_800BBDF4
/* 800BBDE8 000B89C8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BBDEC 000B89CC  41 82 00 08 */	beq lbl_800BBDF4
/* 800BBDF0 000B89D0  38 60 00 01 */	li r3, 1
lbl_800BBDF4:
/* 800BBDF4 000B89D4  2C 03 00 00 */	cmpwi r3, 0
/* 800BBDF8 000B89D8  40 82 00 0C */	bne lbl_800BBE04
/* 800BBDFC 000B89DC  7F C3 F3 78 */	mr r3, r30
/* 800BBE00 000B89E0  48 2B 74 E9 */	bl HSD_JObjSetMtxDirtySub
lbl_800BBE04:
/* 800BBE04 000B89E4  C0 21 00 14 */	lfs f1, 0x14(r1)
/* 800BBE08 000B89E8  C0 1F 23 64 */	lfs f0, 0x2364(r31)
/* 800BBE0C 000B89EC  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBE10 000B89F0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 800BBE14 000B89F4  C0 21 00 18 */	lfs f1, 0x18(r1)
/* 800BBE18 000B89F8  C0 1F 23 68 */	lfs f0, 0x2368(r31)
/* 800BBE1C 000B89FC  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBE20 000B8A00  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800BBE24 000B8A04  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 800BBE28 000B8A08  C0 1F 23 6C */	lfs f0, 0x236c(r31)
/* 800BBE2C 000B8A0C  EC 01 00 32 */	fmuls f0, f1, f0
/* 800BBE30 000B8A10  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800BBE34 000B8A14  83 FF 20 A0 */	lwz r31, 0x20a0(r31)
/* 800BBE38 000B8A18  28 1F 00 00 */	cmplwi r31, 0
/* 800BBE3C 000B8A1C  40 82 00 14 */	bne lbl_800BBE50
/* 800BBE40 000B8A20  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBE44 000B8A24  38 80 02 F8 */	li r4, 0x2f8
/* 800BBE48 000B8A28  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBE4C 000B8A2C  48 2C C3 D5 */	bl __assert
lbl_800BBE50:
/* 800BBE50 000B8A30  80 61 00 14 */	lwz r3, 0x14(r1)
/* 800BBE54 000B8A34  80 01 00 18 */	lwz r0, 0x18(r1)
/* 800BBE58 000B8A38  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 800BBE5C 000B8A3C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 800BBE60 000B8A40  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BBE64 000B8A44  90 1F 00 34 */	stw r0, 0x34(r31)
/* 800BBE68 000B8A48  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 800BBE6C 000B8A4C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BBE70 000B8A50  40 82 00 4C */	bne lbl_800BBEBC
/* 800BBE74 000B8A54  28 1F 00 00 */	cmplwi r31, 0
/* 800BBE78 000B8A58  41 82 00 44 */	beq lbl_800BBEBC
/* 800BBE7C 000B8A5C  40 82 00 14 */	bne lbl_800BBE90
/* 800BBE80 000B8A60  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBE84 000B8A64  38 80 02 34 */	li r4, 0x234
/* 800BBE88 000B8A68  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBE8C 000B8A6C  48 2C C3 95 */	bl __assert
lbl_800BBE90:
/* 800BBE90 000B8A70  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 800BBE94 000B8A74  38 60 00 00 */	li r3, 0
/* 800BBE98 000B8A78  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BBE9C 000B8A7C  40 82 00 10 */	bne lbl_800BBEAC
/* 800BBEA0 000B8A80  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BBEA4 000B8A84  41 82 00 08 */	beq lbl_800BBEAC
/* 800BBEA8 000B8A88  38 60 00 01 */	li r3, 1
lbl_800BBEAC:
/* 800BBEAC 000B8A8C  2C 03 00 00 */	cmpwi r3, 0
/* 800BBEB0 000B8A90  40 82 00 0C */	bne lbl_800BBEBC
/* 800BBEB4 000B8A94  7F E3 FB 78 */	mr r3, r31
/* 800BBEB8 000B8A98  48 2B 74 31 */	bl HSD_JObjSetMtxDirtySub
lbl_800BBEBC:
/* 800BBEBC 000B8A9C  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800BBEC0 000B8AA0  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800BBEC4 000B8AA4  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800BBEC8 000B8AA8  38 21 00 38 */	addi r1, r1, 0x38
/* 800BBECC 000B8AAC  7C 08 03 A6 */	mtlr r0
/* 800BBED0 000B8AB0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800BBED4(Fighter_GObj* gobj, Fighter_GObj* arg1)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_YoshiEgg, Ft_MF_Unk06, 0, 1, 0,
                              arg1);
    fp->take_dmg_cb = ftCo_800BC438;
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221E_b0 = true;
    {
        Vec3 scale;
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4] = { 0 };
#endif
        float size = fp->co_attrs.xBC.size;
        scale.x = scale.y = scale.z = size;
        ftCommon_SetAccessory(fp, ftYs_SpecialN_8012CDD4(arg1));
        {
            HSD_JObj* jobj = fp->x20A0_accessory;
            HSD_JObjSetScale(jobj, &scale);
        }
        fp->mv.co.yoshiegg.scale = scale;
    }
    lb_8000C2F8(fp->x20A0_accessory == NULL ? NULL
                                            : fp->x20A0_accessory->child,
                fp->parts[ftParts_8007500C(fp, FtPart_TransN)].joint);
    {
        ftCo_DatAttrs_xBC_t* temp_r27;
        Fighter* fp = GET_FIGHTER(gobj);
        struct UNK_SAMUS_S2 unk_struct;
        ftColl_8007B0C0(gobj, Intangible);
        temp_r27 = &fp->co_attrs.xBC;
        unk_struct.parts[0] = ftParts_8007500C(fp, FtPart_TransN);
        unk_struct.parts[1] = FtPart_TransN;
        unk_struct.parts[2] = FtPart_TopN;
        unk_struct.vec1 = temp_r27->x4;
        unk_struct.vec2 = temp_r27->x10;
        unk_struct.single_float = temp_r27->x1C;
        ftColl_8007B5AC(fp, fp->x11A0_fighterHurtbox, &unk_struct);
    }
    ftYs_Shield_8012CC94(arg1, &fp->self_vel);
    fp->facing_dir = ftYs_Shield_8012CCC4(arg1);
    fp->dmg.x182c_behavior = ftYs_Shield_8012CCD0(arg1);
    fp->mv.ca.specialhi.vel.y = 0;
    fp->mv.co.yoshiegg.x0 = arg1;
    fp->x21F0 = ftCo_800BC3D0;
    ftCommon_8007EFC0(fp, 1);
    fp->mv.co.yoshiegg.x10 = ftYs_Shield_8012CCF0(arg1);
    fp->mv.co.yoshiegg.x14 = fp->mv.co.walk.fast_anim_frame;
    fp->mv.co.yoshiegg.xC = ftYs_Shield_8012CCE0(arg1);
    ftCommon_8007DBCC(fp, 0, ftYs_Shield_8012CD00(arg1));
    {
        /// @todo Line numbers what.
        if (jobj == NULL) {
            __assert("jobj.h", 823, "jobj");
        }
        HSD_JObjGetScale(jobj, &fp->mv.co.yoshiegg.x18);
    }
    fp->accessory4_cb = ftCo_800BBCC0;
}
#else /* clang-format off */
{ nofralloc
/* 800BBED4 000B8AB4  7C 08 02 A6 */	mflr r0
/* 800BBED8 000B8AB8  90 01 00 04 */	stw r0, 4(r1)
/* 800BBEDC 000B8ABC  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 800BBEE0 000B8AC0  BF 41 00 60 */	stmw r26, 0x60(r1)
/* 800BBEE4 000B8AC4  7C 7C 1B 78 */	mr r28, r3
/* 800BBEE8 000B8AC8  7C 9D 23 78 */	mr r29, r4
/* 800BBEEC 000B8ACC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800BBEF0 000B8AD0  83 DC 00 28 */	lwz r30, 0x28(r28)
/* 800BBEF4 000B8AD4  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800BBEF8 000B8AD8  3B E3 00 00 */	addi r31, r3, 0
/* 800BBEFC 000B8ADC  2C 00 00 00 */	cmpwi r0, 0
/* 800BBF00 000B8AE0  40 82 00 0C */	bne lbl_800BBF0C
/* 800BBF04 000B8AE4  7F E3 FB 78 */	mr r3, r31
/* 800BBF08 000B8AE8  4B FC 16 CD */	bl ftCommon_8007D5D4
lbl_800BBF0C:
/* 800BBF0C 000B8AEC  C0 22 91 88 */	lfs f1, ftCo_804D8B68
/* 800BBF10 000B8AF0  7F 83 E3 78 */	mr r3, r28
/* 800BBF14 000B8AF4  C0 42 91 8C */	lfs f2, ftCo_804D8B6C
/* 800BBF18 000B8AF8  7F A6 EB 78 */	mr r6, r29
/* 800BBF1C 000B8AFC  FC 60 08 90 */	fmr f3, f1
/* 800BBF20 000B8B00  38 80 01 15 */	li r4, 0x115
/* 800BBF24 000B8B04  38 A0 00 40 */	li r5, 0x40
/* 800BBF28 000B8B08  4B FA D4 85 */	bl Fighter_ChangeMotionState
/* 800BBF2C 000B8B0C  3C 60 80 0C */	lis r3, ftCo_800BC438@ha
/* 800BBF30 000B8B10  38 03 C4 38 */	addi r0, r3, ftCo_800BC438@l
/* 800BBF34 000B8B14  90 1F 21 DC */	stw r0, 0x21dc(r31)
/* 800BBF38 000B8B18  38 7F 00 00 */	addi r3, r31, 0
/* 800BBF3C 000B8B1C  38 80 01 FF */	li r4, 0x1ff
/* 800BBF40 000B8B20  4B FC 23 B5 */	bl ftCommon_8007E2F4
/* 800BBF44 000B8B24  88 1F 22 1E */	lbz r0, 0x221e(r31)
/* 800BBF48 000B8B28  38 60 00 01 */	li r3, 1
/* 800BBF4C 000B8B2C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 800BBF50 000B8B30  98 1F 22 1E */	stb r0, 0x221e(r31)
/* 800BBF54 000B8B34  7F A3 EB 78 */	mr r3, r29
/* 800BBF58 000B8B38  C0 1F 01 CC */	lfs f0, 0x1cc(r31)
/* 800BBF5C 000B8B3C  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 800BBF60 000B8B40  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 800BBF64 000B8B44  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800BBF68 000B8B48  48 07 0E 6D */	bl ftYs_SpecialN_8012CDD4
/* 800BBF6C 000B8B4C  38 83 00 00 */	addi r4, r3, 0
/* 800BBF70 000B8B50  38 7F 00 00 */	addi r3, r31, 0
/* 800BBF74 000B8B54  4B FC 26 AD */	bl ftCommon_SetAccessory
/* 800BBF78 000B8B58  83 5F 20 A0 */	lwz r26, 0x20a0(r31)
/* 800BBF7C 000B8B5C  28 1A 00 00 */	cmplwi r26, 0
/* 800BBF80 000B8B60  40 82 00 14 */	bne lbl_800BBF94
/* 800BBF84 000B8B64  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBF88 000B8B68  38 80 02 F8 */	li r4, 0x2f8
/* 800BBF8C 000B8B6C  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBF90 000B8B70  48 2C C2 91 */	bl __assert
lbl_800BBF94:
/* 800BBF94 000B8B74  80 61 00 54 */	lwz r3, 0x54(r1)
/* 800BBF98 000B8B78  80 01 00 58 */	lwz r0, 0x58(r1)
/* 800BBF9C 000B8B7C  90 7A 00 2C */	stw r3, 0x2c(r26)
/* 800BBFA0 000B8B80  90 1A 00 30 */	stw r0, 0x30(r26)
/* 800BBFA4 000B8B84  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800BBFA8 000B8B88  90 1A 00 34 */	stw r0, 0x34(r26)
/* 800BBFAC 000B8B8C  80 1A 00 14 */	lwz r0, 0x14(r26)
/* 800BBFB0 000B8B90  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800BBFB4 000B8B94  40 82 00 4C */	bne lbl_800BC000
/* 800BBFB8 000B8B98  28 1A 00 00 */	cmplwi r26, 0
/* 800BBFBC 000B8B9C  41 82 00 44 */	beq lbl_800BC000
/* 800BBFC0 000B8BA0  40 82 00 14 */	bne lbl_800BBFD4
/* 800BBFC4 000B8BA4  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BBFC8 000B8BA8  38 80 02 34 */	li r4, 0x234
/* 800BBFCC 000B8BAC  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BBFD0 000B8BB0  48 2C C2 51 */	bl __assert
lbl_800BBFD4:
/* 800BBFD4 000B8BB4  80 9A 00 14 */	lwz r4, 0x14(r26)
/* 800BBFD8 000B8BB8  38 60 00 00 */	li r3, 0
/* 800BBFDC 000B8BBC  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800BBFE0 000B8BC0  40 82 00 10 */	bne lbl_800BBFF0
/* 800BBFE4 000B8BC4  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800BBFE8 000B8BC8  41 82 00 08 */	beq lbl_800BBFF0
/* 800BBFEC 000B8BCC  38 60 00 01 */	li r3, 1
lbl_800BBFF0:
/* 800BBFF0 000B8BD0  2C 03 00 00 */	cmpwi r3, 0
/* 800BBFF4 000B8BD4  40 82 00 0C */	bne lbl_800BC000
/* 800BBFF8 000B8BD8  7F 43 D3 78 */	mr r3, r26
/* 800BBFFC 000B8BDC  48 2B 72 ED */	bl HSD_JObjSetMtxDirtySub
lbl_800BC000:
/* 800BC000 000B8BE0  80 61 00 54 */	lwz r3, 0x54(r1)
/* 800BC004 000B8BE4  80 01 00 58 */	lwz r0, 0x58(r1)
/* 800BC008 000B8BE8  90 7F 23 64 */	stw r3, 0x2364(r31)
/* 800BC00C 000B8BEC  90 1F 23 68 */	stw r0, 0x2368(r31)
/* 800BC010 000B8BF0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 800BC014 000B8BF4  90 1F 23 6C */	stw r0, 0x236c(r31)
/* 800BC018 000B8BF8  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 800BC01C 000B8BFC  28 03 00 00 */	cmplwi r3, 0
/* 800BC020 000B8C00  40 82 00 0C */	bne lbl_800BC02C
/* 800BC024 000B8C04  3B 60 00 00 */	li r27, 0
/* 800BC028 000B8C08  48 00 00 08 */	b lbl_800BC030
lbl_800BC02C:
/* 800BC02C 000B8C0C  83 63 00 10 */	lwz r27, 0x10(r3)
lbl_800BC030:
/* 800BC030 000B8C10  38 7F 00 00 */	addi r3, r31, 0
/* 800BC034 000B8C14  38 80 00 01 */	li r4, 1
/* 800BC038 000B8C18  4B FB 8F D5 */	bl ftParts_8007500C
/* 800BC03C 000B8C1C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800BC040 000B8C20  54 60 20 36 */	slwi r0, r3, 4
/* 800BC044 000B8C24  38 7B 00 00 */	addi r3, r27, 0
/* 800BC048 000B8C28  7C 84 00 2E */	lwzx r4, r4, r0
/* 800BC04C 000B8C2C  4B F5 02 AD */	bl lb_8000C2F8
/* 800BC050 000B8C30  83 5C 00 2C */	lwz r26, 0x2c(r28)
/* 800BC054 000B8C34  38 7C 00 00 */	addi r3, r28, 0
/* 800BC058 000B8C38  38 80 00 02 */	li r4, 2
/* 800BC05C 000B8C3C  4B FB F0 65 */	bl ftColl_8007B0C0
/* 800BC060 000B8C40  38 7A 00 00 */	addi r3, r26, 0
/* 800BC064 000B8C44  3B 7A 01 CC */	addi r27, r26, 0x1cc
/* 800BC068 000B8C48  38 80 00 01 */	li r4, 1
/* 800BC06C 000B8C4C  4B FB 8F A1 */	bl ftParts_8007500C
/* 800BC070 000B8C50  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800BC074 000B8C54  38 60 00 01 */	li r3, 1
/* 800BC078 000B8C58  38 00 00 00 */	li r0, 0
/* 800BC07C 000B8C5C  90 61 00 30 */	stw r3, 0x30(r1)
/* 800BC080 000B8C60  38 7A 00 00 */	addi r3, r26, 0
/* 800BC084 000B8C64  38 9A 11 A0 */	addi r4, r26, 0x11a0
/* 800BC088 000B8C68  90 01 00 34 */	stw r0, 0x34(r1)
/* 800BC08C 000B8C6C  38 A1 00 2C */	addi r5, r1, 0x2c
/* 800BC090 000B8C70  80 DB 00 04 */	lwz r6, 4(r27)
/* 800BC094 000B8C74  80 1B 00 08 */	lwz r0, 8(r27)
/* 800BC098 000B8C78  90 C1 00 38 */	stw r6, 0x38(r1)
/* 800BC09C 000B8C7C  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800BC0A0 000B8C80  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 800BC0A4 000B8C84  90 01 00 40 */	stw r0, 0x40(r1)
/* 800BC0A8 000B8C88  80 DB 00 10 */	lwz r6, 0x10(r27)
/* 800BC0AC 000B8C8C  80 1B 00 14 */	lwz r0, 0x14(r27)
/* 800BC0B0 000B8C90  90 C1 00 44 */	stw r6, 0x44(r1)
/* 800BC0B4 000B8C94  90 01 00 48 */	stw r0, 0x48(r1)
/* 800BC0B8 000B8C98  80 1B 00 18 */	lwz r0, 0x18(r27)
/* 800BC0BC 000B8C9C  90 01 00 4C */	stw r0, 0x4c(r1)
/* 800BC0C0 000B8CA0  C0 1B 00 1C */	lfs f0, 0x1c(r27)
/* 800BC0C4 000B8CA4  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 800BC0C8 000B8CA8  4B FB F4 E5 */	bl ftColl_8007B5AC
/* 800BC0CC 000B8CAC  38 7D 00 00 */	addi r3, r29, 0
/* 800BC0D0 000B8CB0  38 9F 00 80 */	addi r4, r31, 0x80
/* 800BC0D4 000B8CB4  48 07 0B C1 */	bl ftYs_Shield_8012CC94
/* 800BC0D8 000B8CB8  7F A3 EB 78 */	mr r3, r29
/* 800BC0DC 000B8CBC  48 07 0B E9 */	bl ftYs_Shield_8012CCC4
/* 800BC0E0 000B8CC0  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 800BC0E4 000B8CC4  7F A3 EB 78 */	mr r3, r29
/* 800BC0E8 000B8CC8  48 07 0B E9 */	bl ftYs_Shield_8012CCD0
/* 800BC0EC 000B8CCC  D0 3F 18 2C */	stfs f1, 0x182c(r31)
/* 800BC0F0 000B8CD0  3C 60 80 0C */	lis r3, ftCo_800BC3D0@ha
/* 800BC0F4 000B8CD4  38 03 C3 D0 */	addi r0, r3, ftCo_800BC3D0@l
/* 800BC0F8 000B8CD8  C0 02 91 88 */	lfs f0, ftCo_804D8B68
/* 800BC0FC 000B8CDC  38 7F 00 00 */	addi r3, r31, 0
/* 800BC100 000B8CE0  38 80 00 01 */	li r4, 1
/* 800BC104 000B8CE4  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 800BC108 000B8CE8  93 BF 23 40 */	stw r29, 0x2340(r31)
/* 800BC10C 000B8CEC  90 1F 21 F0 */	stw r0, 0x21f0(r31)
/* 800BC110 000B8CF0  4B FC 2E B1 */	bl ftCommon_8007EFC0
/* 800BC114 000B8CF4  7F A3 EB 78 */	mr r3, r29
/* 800BC118 000B8CF8  48 07 0B D9 */	bl ftYs_Shield_8012CCF0
/* 800BC11C 000B8CFC  D0 3F 23 50 */	stfs f1, 0x2350(r31)
/* 800BC120 000B8D00  7F A3 EB 78 */	mr r3, r29
/* 800BC124 000B8D04  C0 1F 23 50 */	lfs f0, 0x2350(r31)
/* 800BC128 000B8D08  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 800BC12C 000B8D0C  48 07 0B B5 */	bl ftYs_Shield_8012CCE0
/* 800BC130 000B8D10  D0 3F 23 4C */	stfs f1, 0x234c(r31)
/* 800BC134 000B8D14  7F A3 EB 78 */	mr r3, r29
/* 800BC138 000B8D18  48 07 0B C9 */	bl ftYs_Shield_8012CD00
/* 800BC13C 000B8D1C  38 7F 00 00 */	addi r3, r31, 0
/* 800BC140 000B8D20  38 80 00 00 */	li r4, 0
/* 800BC144 000B8D24  4B FC 1A 89 */	bl ftCommon_8007DBCC
/* 800BC148 000B8D28  28 1E 00 00 */	cmplwi r30, 0
/* 800BC14C 000B8D2C  40 82 00 14 */	bne lbl_800BC160
/* 800BC150 000B8D30  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BC154 000B8D34  38 80 03 37 */	li r4, 0x337
/* 800BC158 000B8D38  38 AD 84 F0 */	addi r5, r13, ftCo_804D3B90
/* 800BC15C 000B8D3C  48 2C C0 C5 */	bl __assert
lbl_800BC160:
/* 800BC160 000B8D40  34 1F 23 58 */	addic. r0, r31, 0x2358
/* 800BC164 000B8D44  40 82 00 14 */	bne lbl_800BC178
/* 800BC168 000B8D48  38 6D 84 E8 */	addi r3, r13, ftCo_804D3B88
/* 800BC16C 000B8D4C  38 80 03 38 */	li r4, 0x338
/* 800BC170 000B8D50  38 AD 84 F8 */	addi r5, r13, ftCo_804D3B98
/* 800BC174 000B8D54  48 2C C0 AD */	bl __assert
lbl_800BC178:
/* 800BC178 000B8D58  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800BC17C 000B8D5C  3C 60 80 0C */	lis r3, ftCo_800BBCC0@ha
/* 800BC180 000B8D60  80 9E 00 30 */	lwz r4, 0x30(r30)
/* 800BC184 000B8D64  38 03 BC C0 */	addi r0, r3, ftCo_800BBCC0@l
/* 800BC188 000B8D68  90 BF 23 58 */	stw r5, 0x2358(r31)
/* 800BC18C 000B8D6C  90 9F 23 5C */	stw r4, 0x235c(r31)
/* 800BC190 000B8D70  80 7E 00 34 */	lwz r3, 0x34(r30)
/* 800BC194 000B8D74  90 7F 23 60 */	stw r3, 0x2360(r31)
/* 800BC198 000B8D78  90 1F 21 BC */	stw r0, 0x21bc(r31)
/* 800BC19C 000B8D7C  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 800BC1A0 000B8D80  BB 41 00 60 */	lmw r26, 0x60(r1)
/* 800BC1A4 000B8D84  38 21 00 78 */	addi r1, r1, 0x78
/* 800BC1A8 000B8D88  7C 08 03 A6 */	mtlr r0
/* 800BC1AC 000B8D8C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_YoshiEgg_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C -= ftYs_SpecialN_8012CD10(gobj);
    fp->mv.co.yoshiegg.x4 = ftCommon_8007DC08(fp, ftYs_SpecialN_8012CD28());
    if (fp->x1A4C <= 0) {
        ft_80088148(fp, 280088, 127, 64);
        {
            HSD_JObj* jobj = fp->parts[FtPart_TopN].joint;
            ftCo_DatAttrs* ca = &fp->co_attrs;
            ftCo_DatAttrs_xBC_t* ca_xBC = &ca->xBC;
            efAsync_Spawn(gobj, &GET_FIGHTER(gobj)->x60C, 4, 1231, jobj,
                          ca_xBC);
            ftYs_SpecialN_8012CD88(&fp->self_vel);
        }
        ftCommon_8007D5D4(fp);
        Fighter_UpdateModelScale(gobj);
        ftColl_8007B760(gobj, ftYs_SpecialN_8012CD70());
        ftCo_800CC830(gobj);
        return;
    }
    if (fp->mv.co.yoshiegg.x8) {
        fp->mv.co.yoshiegg.x8 -= 1;
        if (fp->mv.co.yoshiegg.x8 <= 0 && !fp->mv.co.yoshiegg.x4) {
            ftAnim_SetAnimRate(gobj, 1);
            fp->mv.co.yoshiegg.x8 = 0;
        }
    }
    if (fp->mv.co.yoshiegg.x8 <= 0 && fp->mv.co.yoshiegg.x4) {
        fp->mv.co.yoshiegg.x8 = ftYs_SpecialN_8012CD40();
        ftAnim_SetAnimRate(gobj, ftYs_SpecialN_8012CD58());
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BC1B0 000B8D90  7C 08 02 A6 */	mflr r0
/* 800BC1B4 000B8D94  90 01 00 04 */	stw r0, 4(r1)
/* 800BC1B8 000B8D98  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800BC1BC 000B8D9C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800BC1C0 000B8DA0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800BC1C4 000B8DA4  7C 7E 1B 78 */	mr r30, r3
/* 800BC1C8 000B8DA8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BC1CC 000B8DAC  48 07 0B 45 */	bl ftYs_SpecialN_8012CD10
/* 800BC1D0 000B8DB0  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BC1D4 000B8DB4  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BC1D8 000B8DB8  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800BC1DC 000B8DBC  48 07 0B 4D */	bl ftYs_SpecialN_8012CD28
/* 800BC1E0 000B8DC0  7F E3 FB 78 */	mr r3, r31
/* 800BC1E4 000B8DC4  4B FC 1A 25 */	bl ftCommon_8007DC08
/* 800BC1E8 000B8DC8  90 7F 23 44 */	stw r3, 0x2344(r31)
/* 800BC1EC 000B8DCC  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BC1F0 000B8DD0  C0 42 91 88 */	lfs f2, ftCo_804D8B68
/* 800BC1F4 000B8DD4  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800BC1F8 000B8DD8  4C 40 13 82 */	cror 2, 0, 2
/* 800BC1FC 000B8DDC  40 82 00 78 */	bne lbl_800BC274
/* 800BC200 000B8DE0  3C 80 00 04 */	lis r4, 0x00044618@ha
/* 800BC204 000B8DE4  38 7F 00 00 */	addi r3, r31, 0
/* 800BC208 000B8DE8  38 84 46 18 */	addi r4, r4, 0x00044618@l
/* 800BC20C 000B8DEC  38 A0 00 7F */	li r5, 0x7f
/* 800BC210 000B8DF0  38 C0 00 40 */	li r6, 0x40
/* 800BC214 000B8DF4  4B FC BF 35 */	bl ft_80088148
/* 800BC218 000B8DF8  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800BC21C 000B8DFC  39 1F 01 CC */	addi r8, r31, 0x1cc
/* 800BC220 000B8E00  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800BC224 000B8E04  7F C3 F3 78 */	mr r3, r30
/* 800BC228 000B8E08  80 E4 00 00 */	lwz r7, 0(r4)
/* 800BC22C 000B8E0C  38 85 06 0C */	addi r4, r5, 0x60c
/* 800BC230 000B8E10  4C C6 31 82 */	crclr 6
/* 800BC234 000B8E14  38 A0 00 04 */	li r5, 4
/* 800BC238 000B8E18  38 C0 04 CF */	li r6, 0x4cf
/* 800BC23C 000B8E1C  4B FA B4 B5 */	bl efAsync_Spawn
/* 800BC240 000B8E20  38 7F 00 80 */	addi r3, r31, 0x80
/* 800BC244 000B8E24  48 07 0B 45 */	bl ftYs_SpecialN_8012CD88
/* 800BC248 000B8E28  7F E3 FB 78 */	mr r3, r31
/* 800BC24C 000B8E2C  4B FC 13 89 */	bl ftCommon_8007D5D4
/* 800BC250 000B8E30  7F C3 F3 78 */	mr r3, r30
/* 800BC254 000B8E34  4B FA B9 61 */	bl Fighter_UpdateModelScale
/* 800BC258 000B8E38  48 07 0B 19 */	bl ftYs_SpecialN_8012CD70
/* 800BC25C 000B8E3C  38 83 00 00 */	addi r4, r3, 0
/* 800BC260 000B8E40  38 7E 00 00 */	addi r3, r30, 0
/* 800BC264 000B8E44  4B FB F4 FD */	bl ftColl_8007B760
/* 800BC268 000B8E48  7F C3 F3 78 */	mr r3, r30
/* 800BC26C 000B8E4C  48 01 05 C5 */	bl ftCo_800CC830
/* 800BC270 000B8E50  48 00 00 7C */	b lbl_800BC2EC
lbl_800BC274:
/* 800BC274 000B8E54  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 800BC278 000B8E58  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 800BC27C 000B8E5C  41 82 00 3C */	beq lbl_800BC2B8
/* 800BC280 000B8E60  C0 22 91 8C */	lfs f1, ftCo_804D8B6C
/* 800BC284 000B8E64  EC 00 08 28 */	fsubs f0, f0, f1
/* 800BC288 000B8E68  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 800BC28C 000B8E6C  C0 1F 23 48 */	lfs f0, 0x2348(r31)
/* 800BC290 000B8E70  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800BC294 000B8E74  4C 40 13 82 */	cror 2, 0, 2
/* 800BC298 000B8E78  40 82 00 20 */	bne lbl_800BC2B8
/* 800BC29C 000B8E7C  80 1F 23 44 */	lwz r0, 0x2344(r31)
/* 800BC2A0 000B8E80  2C 00 00 00 */	cmpwi r0, 0
/* 800BC2A4 000B8E84  40 82 00 14 */	bne lbl_800BC2B8
/* 800BC2A8 000B8E88  7F C3 F3 78 */	mr r3, r30
/* 800BC2AC 000B8E8C  4B FB 2E E5 */	bl ftAnim_SetAnimRate
/* 800BC2B0 000B8E90  C0 02 91 88 */	lfs f0, ftCo_804D8B68
/* 800BC2B4 000B8E94  D0 1F 23 48 */	stfs f0, 0x2348(r31)
lbl_800BC2B8:
/* 800BC2B8 000B8E98  C0 3F 23 48 */	lfs f1, 0x2348(r31)
/* 800BC2BC 000B8E9C  C0 02 91 88 */	lfs f0, ftCo_804D8B68
/* 800BC2C0 000B8EA0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800BC2C4 000B8EA4  4C 40 13 82 */	cror 2, 0, 2
/* 800BC2C8 000B8EA8  40 82 00 24 */	bne lbl_800BC2EC
/* 800BC2CC 000B8EAC  80 1F 23 44 */	lwz r0, 0x2344(r31)
/* 800BC2D0 000B8EB0  2C 00 00 00 */	cmpwi r0, 0
/* 800BC2D4 000B8EB4  41 82 00 18 */	beq lbl_800BC2EC
/* 800BC2D8 000B8EB8  48 07 0A 69 */	bl ftYs_SpecialN_8012CD40
/* 800BC2DC 000B8EBC  D0 3F 23 48 */	stfs f1, 0x2348(r31)
/* 800BC2E0 000B8EC0  48 07 0A 79 */	bl ftYs_SpecialN_8012CD58
/* 800BC2E4 000B8EC4  7F C3 F3 78 */	mr r3, r30
/* 800BC2E8 000B8EC8  4B FB 2E A9 */	bl ftAnim_SetAnimRate
lbl_800BC2EC:
/* 800BC2EC 000B8ECC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800BC2F0 000B8ED0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800BC2F4 000B8ED4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800BC2F8 000B8ED8  38 21 00 28 */	addi r1, r1, 0x28
/* 800BC2FC 000B8EDC  7C 08 03 A6 */	mtlr r0
/* 800BC300 000B8EE0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_YoshiEgg_IASA(ftCo_GObj* gobj) {}

void ftCo_YoshiEgg_Phys(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ground_or_air == GA_Ground) {
        ft_80084F3C(gobj);
    } else {
        ft_80084DB0(gobj);
    }
}

void ftCo_YoshiEgg_Coll(ftCo_GObj* gobj)
{
    if (GET_FIGHTER(gobj)->ground_or_air == GA_Ground) {
        ft_8008403C(gobj, ftCo_800BC3AC);
    } else {
        ft_80082C74(gobj, ftCo_800BC388);
    }
}

void ftCo_800BC388(ftCo_GObj* gobj)
{
    ftCommon_8007D7FC(GET_FIGHTER(gobj));
}

void ftCo_800BC3AC(ftCo_GObj* gobj)
{
    ftCommon_8007D5D4(GET_FIGHTER(gobj));
}

ASM void ftCo_800BC3D0(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = GET_FIGHTER(gobj);
    fp->x1A4C = -(fp->dmg.x1838_percentTemp * ftYs_SpecialN_8012CDB4(gobj) -
                  fp->x1A4C);
    if (fp->dmg.x18CC == 3 && ftCo_800C0C88(fp->dmg.x18D0)) {
        fp->x1A4C = 0;
    }
    fp->x1828 = 4;
}

#else /* clang-format off */
{ nofralloc
/* 800BC3D0 000B8FB0  7C 08 02 A6 */	mflr r0
/* 800BC3D4 000B8FB4  90 01 00 04 */	stw r0, 4(r1)
/* 800BC3D8 000B8FB8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800BC3DC 000B8FBC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800BC3E0 000B8FC0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BC3E4 000B8FC4  48 07 09 D1 */	bl ftYs_SpecialN_8012CDB4
/* 800BC3E8 000B8FC8  C0 5F 18 38 */	lfs f2, 0x1838(r31)
/* 800BC3EC 000B8FCC  C0 1F 1A 4C */	lfs f0, 0x1a4c(r31)
/* 800BC3F0 000B8FD0  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 800BC3F4 000B8FD4  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
/* 800BC3F8 000B8FD8  80 1F 18 CC */	lwz r0, 0x18cc(r31)
/* 800BC3FC 000B8FDC  2C 00 00 03 */	cmpwi r0, 3
/* 800BC400 000B8FE0  40 82 00 1C */	bne lbl_800BC41C
/* 800BC404 000B8FE4  80 7F 18 D0 */	lwz r3, 0x18d0(r31)
/* 800BC408 000B8FE8  48 00 48 81 */	bl ftCo_800C0C88
/* 800BC40C 000B8FEC  2C 03 00 00 */	cmpwi r3, 0
/* 800BC410 000B8FF0  41 82 00 0C */	beq lbl_800BC41C
/* 800BC414 000B8FF4  C0 02 91 88 */	lfs f0, ftCo_804D8B68
/* 800BC418 000B8FF8  D0 1F 1A 4C */	stfs f0, 0x1a4c(r31)
lbl_800BC41C:
/* 800BC41C 000B8FFC  38 00 00 04 */	li r0, 4
/* 800BC420 000B9000  90 1F 18 28 */	stw r0, 0x1828(r31)
/* 800BC424 000B9004  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BC428 000B9008  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800BC42C 000B900C  38 21 00 18 */	addi r1, r1, 0x18
/* 800BC430 000B9010  7C 08 03 A6 */	mtlr r0
/* 800BC434 000B9014  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
