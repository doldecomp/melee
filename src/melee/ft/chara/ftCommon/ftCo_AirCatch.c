#include <platform.h>
#include "ftSamus/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

#include "ftCo_AirCatch.h"

#include "ftCo_FallSpecial.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0D14.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ftCommon/types.h"
#include "ftLink/types.h"
#include "ftSamus/types.h"
#include "it/item.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itsamusgrapple.h"
#include "lb/lb_00B0.h"
#include "mp/mpcoll.h"
#include "mp/mplib.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/jobj.h>

#ifdef WIP
#pragma force_active on
#endif

/* literal */ double const ftCo_804D8CF0 = 5;
/* literal */ double const ftCo_804D8CF8 = 0;
/* literal */ float const ftCo_804D8D00 = 0;
/* literal */ float const ftCo_804D8D04 = 1;
/* literal */ double const ftCo_804D8D08 = 1;
/* literal */ double const ftCo_804D8D10 = 8;
/* literal */ double const ftCo_804D8D18 = 2;
/* literal */ double const ftCo_804D8D20 = S32_TO_F32;
/* literal */ float const ftCo_804D8D28 = 20;
/* literal */ double const ftCo_804D8D30 = 0.2;
/* literal */ Vec3 const lbl_803B74C8 = { 0 };
/* literal */ Vec3 const lbl_803B74D4 = { 1.8, 0, 0 };
/* literal */ Vec3 const lbl_803B74E0 = { 1.8, 0, 0 };
/* literal */ SDATA char ftCo_804D3C48[] = "jobj.h";
/* literal */ SDATA char ftCo_804D3C50[] = "jobj";

ASM bool ftCo_800C3A14(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    CollData coll = { 0 };
    IntVec3 sp14;
    int i = 51;
    IntVec3* var_r5 = &sp14;
    Fighter* fp = GET_FIGHTER(gobj);
    IntVec3* var_r4 = (IntVec3*) &fp->x6E4.y;
    do {
        var_r4 += 8;
        var_r5 += 8;
        var_r5->z = var_r4->z;
        var_r5->y = var_r4->y;
        --i;
    } while (i != 0);
    var_r5->z = var_r4->z;
    coll.x58 += 5.0;
    coll.x5C += 5.0;
    if (fp->facing_dir > 0.0f) {
        if (mpColl_80044164(&coll, &fp->coll_data.ledge_id_unk1)) {
            fp->coll_data.env_flags |= MPCOLL_FLAGS_B24;
            fp->self_vel.x = 0;
            fp->self_vel.y = 0;
            return true;
        }
        return false;
    }
    if (mpColl_800443C4(&coll, &fp->coll_data.ledge_id_unk0)) {
        fp->coll_data.env_flags |= MPCOLL_FLAGS_B25;
        fp->self_vel.x = 0;
        fp->self_vel.y = 0;
        return true;
    }
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 800C3A14 000C05F4  7C 08 02 A6 */	mflr r0
/* 800C3A18 000C05F8  90 01 00 04 */	stw r0, 4(r1)
/* 800C3A1C 000C05FC  38 00 00 33 */	li r0, 0x33
/* 800C3A20 000C0600  7C 09 03 A6 */	mtctr r0
/* 800C3A24 000C0604  94 21 FE 40 */	stwu r1, -0x1c0(r1)
/* 800C3A28 000C0608  93 E1 01 BC */	stw r31, 0x1bc(r1)
/* 800C3A2C 000C060C  38 A1 00 14 */	addi r5, r1, 0x14
/* 800C3A30 000C0610  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C3A34 000C0614  38 9F 06 E8 */	addi r4, r31, 0x6e8
lbl_800C3A38:
/* 800C3A38 000C0618  84 64 00 08 */	lwzu r3, 8(r4)
/* 800C3A3C 000C061C  80 04 00 04 */	lwz r0, 4(r4)
/* 800C3A40 000C0620  94 65 00 08 */	stwu r3, 8(r5)
/* 800C3A44 000C0624  90 05 00 04 */	stw r0, 4(r5)
/* 800C3A48 000C0628  42 00 FF F0 */	bdnz lbl_800C3A38
/* 800C3A4C 000C062C  80 04 00 08 */	lwz r0, 8(r4)
/* 800C3A50 000C0630  90 05 00 08 */	stw r0, 8(r5)
/* 800C3A54 000C0634  C0 21 00 74 */	lfs f1, 0x74(r1)
/* 800C3A58 000C0638  C8 42 93 10 */	lfd f2, ftCo_804D8CF0
/* 800C3A5C 000C063C  C8 02 93 18 */	lfd f0, ftCo_804D8CF8
/* 800C3A60 000C0640  FC 21 10 2A */	fadd f1, f1, f2
/* 800C3A64 000C0644  FC 20 08 18 */	frsp f1, f1
/* 800C3A68 000C0648  D0 21 00 74 */	stfs f1, 0x74(r1)
/* 800C3A6C 000C064C  C0 21 00 78 */	lfs f1, 0x78(r1)
/* 800C3A70 000C0650  FC 21 10 2A */	fadd f1, f1, f2
/* 800C3A74 000C0654  FC 20 08 18 */	frsp f1, f1
/* 800C3A78 000C0658  D0 21 00 78 */	stfs f1, 0x78(r1)
/* 800C3A7C 000C065C  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800C3A80 000C0660  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C3A84 000C0664  40 81 00 40 */	ble lbl_800C3AC4
/* 800C3A88 000C0668  38 61 00 1C */	addi r3, r1, 0x1c
/* 800C3A8C 000C066C  38 9F 07 34 */	addi r4, r31, 0x734
/* 800C3A90 000C0670  4B F8 06 D5 */	bl mpColl_80044164
/* 800C3A94 000C0674  2C 03 00 00 */	cmpwi r3, 0
/* 800C3A98 000C0678  41 82 00 24 */	beq lbl_800C3ABC
/* 800C3A9C 000C067C  80 1F 08 24 */	lwz r0, 0x824(r31)
/* 800C3AA0 000C0680  38 60 00 01 */	li r3, 1
/* 800C3AA4 000C0684  64 00 01 00 */	oris r0, r0, 0x100
/* 800C3AA8 000C0688  90 1F 08 24 */	stw r0, 0x824(r31)
/* 800C3AAC 000C068C  C0 02 93 20 */	lfs f0, ftCo_804D8D00
/* 800C3AB0 000C0690  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800C3AB4 000C0694  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800C3AB8 000C0698  48 00 00 44 */	b lbl_800C3AFC
lbl_800C3ABC:
/* 800C3ABC 000C069C  38 60 00 00 */	li r3, 0
/* 800C3AC0 000C06A0  48 00 00 3C */	b lbl_800C3AFC
lbl_800C3AC4:
/* 800C3AC4 000C06A4  38 61 00 1C */	addi r3, r1, 0x1c
/* 800C3AC8 000C06A8  38 9F 07 30 */	addi r4, r31, 0x730
/* 800C3ACC 000C06AC  4B F8 08 F9 */	bl mpColl_800443C4
/* 800C3AD0 000C06B0  2C 03 00 00 */	cmpwi r3, 0
/* 800C3AD4 000C06B4  41 82 00 24 */	beq lbl_800C3AF8
/* 800C3AD8 000C06B8  80 1F 08 24 */	lwz r0, 0x824(r31)
/* 800C3ADC 000C06BC  38 60 00 01 */	li r3, 1
/* 800C3AE0 000C06C0  64 00 02 00 */	oris r0, r0, 0x200
/* 800C3AE4 000C06C4  90 1F 08 24 */	stw r0, 0x824(r31)
/* 800C3AE8 000C06C8  C0 02 93 20 */	lfs f0, ftCo_804D8D00
/* 800C3AEC 000C06CC  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800C3AF0 000C06D0  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800C3AF4 000C06D4  48 00 00 08 */	b lbl_800C3AFC
lbl_800C3AF8:
/* 800C3AF8 000C06D8  38 60 00 00 */	li r3, 0
lbl_800C3AFC:
/* 800C3AFC 000C06DC  80 01 01 C4 */	lwz r0, 0x1c4(r1)
/* 800C3B00 000C06E0  83 E1 01 BC */	lwz r31, 0x1bc(r1)
/* 800C3B04 000C06E4  38 21 01 C0 */	addi r1, r1, 0x1c0
/* 800C3B08 000C06E8  7C 08 03 A6 */	mtlr r0
/* 800C3B0C 000C06EC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM bool ftCo_800C3B10(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2228_b6) {
        return false;
    }
    if (fp->kind != FTKIND_LINK && fp->kind != FTKIND_CLINK &&
        fp->kind != FTKIND_SAMUS)
    {
        return false;
    }
    if (fp->accessory2_cb != NULL || fp->death1_cb != NULL ||
        fp->accessory3_cb != NULL)
    {
        return false;
    }
    if (fp->item_gobj != NULL) {
        return false;
    }
    if (fp->input.held_inputs & HSD_PAD_LR && fp->input.x668 & HSD_PAD_A) {
        ftCo_800C3BE8(gobj);
        fp->x2228_b6 = true;
        return true;
    }
    return false;
}

#else /* clang-format off */
{ nofralloc
/* 800C3B10 000C06F0  7C 08 02 A6 */	mflr r0
/* 800C3B14 000C06F4  90 01 00 04 */	stw r0, 4(r1)
/* 800C3B18 000C06F8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C3B1C 000C06FC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C3B20 000C0700  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C3B24 000C0704  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 800C3B28 000C0708  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800C3B2C 000C070C  41 82 00 0C */	beq lbl_800C3B38
/* 800C3B30 000C0710  38 60 00 00 */	li r3, 0
/* 800C3B34 000C0714  48 00 00 A0 */	b lbl_800C3BD4
lbl_800C3B38:
/* 800C3B38 000C0718  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C3B3C 000C071C  2C 00 00 06 */	cmpwi r0, 6
/* 800C3B40 000C0720  41 82 00 1C */	beq lbl_800C3B5C
/* 800C3B44 000C0724  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C3B48 000C0728  41 82 00 14 */	beq lbl_800C3B5C
/* 800C3B4C 000C072C  2C 00 00 0D */	cmpwi r0, 0xd
/* 800C3B50 000C0730  41 82 00 0C */	beq lbl_800C3B5C
/* 800C3B54 000C0734  38 60 00 00 */	li r3, 0
/* 800C3B58 000C0738  48 00 00 7C */	b lbl_800C3BD4
lbl_800C3B5C:
/* 800C3B5C 000C073C  80 1F 21 B4 */	lwz r0, 0x21b4(r31)
/* 800C3B60 000C0740  28 00 00 00 */	cmplwi r0, 0
/* 800C3B64 000C0744  40 82 00 1C */	bne lbl_800C3B80
/* 800C3B68 000C0748  80 1F 21 E0 */	lwz r0, 0x21e0(r31)
/* 800C3B6C 000C074C  28 00 00 00 */	cmplwi r0, 0
/* 800C3B70 000C0750  40 82 00 10 */	bne lbl_800C3B80
/* 800C3B74 000C0754  80 1F 21 B8 */	lwz r0, 0x21b8(r31)
/* 800C3B78 000C0758  28 00 00 00 */	cmplwi r0, 0
/* 800C3B7C 000C075C  41 82 00 0C */	beq lbl_800C3B88
lbl_800C3B80:
/* 800C3B80 000C0760  38 60 00 00 */	li r3, 0
/* 800C3B84 000C0764  48 00 00 50 */	b lbl_800C3BD4
lbl_800C3B88:
/* 800C3B88 000C0768  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 800C3B8C 000C076C  28 00 00 00 */	cmplwi r0, 0
/* 800C3B90 000C0770  41 82 00 0C */	beq lbl_800C3B9C
/* 800C3B94 000C0774  38 60 00 00 */	li r3, 0
/* 800C3B98 000C0778  48 00 00 3C */	b lbl_800C3BD4
lbl_800C3B9C:
/* 800C3B9C 000C077C  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 800C3BA0 000C0780  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 800C3BA4 000C0784  41 82 00 2C */	beq lbl_800C3BD0
/* 800C3BA8 000C0788  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 800C3BAC 000C078C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 800C3BB0 000C0790  41 82 00 20 */	beq lbl_800C3BD0
/* 800C3BB4 000C0794  48 00 00 35 */	bl ftCo_800C3BE8
/* 800C3BB8 000C0798  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 800C3BBC 000C079C  38 60 00 01 */	li r3, 1
/* 800C3BC0 000C07A0  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 800C3BC4 000C07A4  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 800C3BC8 000C07A8  38 60 00 01 */	li r3, 1
/* 800C3BCC 000C07AC  48 00 00 08 */	b lbl_800C3BD4
lbl_800C3BD0:
/* 800C3BD0 000C07B0  38 60 00 00 */	li r3, 0
lbl_800C3BD4:
/* 800C3BD4 000C07B4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C3BD8 000C07B8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C3BDC 000C07BC  38 21 00 18 */	addi r1, r1, 0x18
/* 800C3BE0 000C07C0  7C 08 03 A6 */	mtlr r0
/* 800C3BE4 000C07C4  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C3BE8(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 anim_vel = { 0 };
    if (fp->ground_or_air == GA_Air) {
        fp->mv.co.aircatch.x0 = 0;
        fp->x74_anim_vel = anim_vel;

        if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
            Fighter_ChangeMotionState(gobj, ftLk_MS_AirCatch, Ft_MF_None, 0, 1,
                                      0, NULL);
        } else if (fp->kind == FTKIND_SAMUS) {
            Fighter_ChangeMotionState(gobj, ftSs_MS_AirCatch, Ft_MF_None, 0, 1,
                                      0, NULL);
        }
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C3BE8 000C07C8  7C 08 02 A6 */	mflr r0
/* 800C3BEC 000C07CC  3C 80 80 3B */	lis r4, lbl_803B74C8@ha
/* 800C3BF0 000C07D0  90 01 00 04 */	stw r0, 4(r1)
/* 800C3BF4 000C07D4  38 A4 74 C8 */	addi r5, r4, lbl_803B74C8@l
/* 800C3BF8 000C07D8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800C3BFC 000C07DC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800C3C00 000C07E0  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 800C3C04 000C07E4  80 85 00 00 */	lwz r4, 0(r5)
/* 800C3C08 000C07E8  80 05 00 04 */	lwz r0, 4(r5)
/* 800C3C0C 000C07EC  7C DF 33 78 */	mr r31, r6
/* 800C3C10 000C07F0  90 81 00 10 */	stw r4, 0x10(r1)
/* 800C3C14 000C07F4  90 01 00 14 */	stw r0, 0x14(r1)
/* 800C3C18 000C07F8  80 05 00 08 */	lwz r0, 8(r5)
/* 800C3C1C 000C07FC  90 01 00 18 */	stw r0, 0x18(r1)
/* 800C3C20 000C0800  80 06 00 E0 */	lwz r0, 0xe0(r6)
/* 800C3C24 000C0804  2C 00 00 01 */	cmpwi r0, 1
/* 800C3C28 000C0808  40 82 00 84 */	bne lbl_800C3CAC
/* 800C3C2C 000C080C  C0 22 93 20 */	lfs f1, ftCo_804D8D00
/* 800C3C30 000C0810  D0 3F 23 40 */	stfs f1, 0x2340(r31)
/* 800C3C34 000C0814  80 81 00 10 */	lwz r4, 0x10(r1)
/* 800C3C38 000C0818  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800C3C3C 000C081C  90 9F 00 74 */	stw r4, 0x74(r31)
/* 800C3C40 000C0820  90 1F 00 78 */	stw r0, 0x78(r31)
/* 800C3C44 000C0824  80 01 00 18 */	lwz r0, 0x18(r1)
/* 800C3C48 000C0828  90 1F 00 7C */	stw r0, 0x7c(r31)
/* 800C3C4C 000C082C  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C3C50 000C0830  2C 00 00 06 */	cmpwi r0, 6
/* 800C3C54 000C0834  41 82 00 0C */	beq lbl_800C3C60
/* 800C3C58 000C0838  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C3C5C 000C083C  40 82 00 24 */	bne lbl_800C3C80
lbl_800C3C60:
/* 800C3C60 000C0840  C0 22 93 20 */	lfs f1, ftCo_804D8D00
/* 800C3C64 000C0844  38 80 01 68 */	li r4, 0x168
/* 800C3C68 000C0848  C0 42 93 24 */	lfs f2, ftCo_804D8D04
/* 800C3C6C 000C084C  38 A0 00 00 */	li r5, 0
/* 800C3C70 000C0850  FC 60 08 90 */	fmr f3, f1
/* 800C3C74 000C0854  38 C0 00 00 */	li r6, 0
/* 800C3C78 000C0858  4B FA 57 35 */	bl Fighter_ChangeMotionState
/* 800C3C7C 000C085C  48 00 00 24 */	b lbl_800C3CA0
lbl_800C3C80:
/* 800C3C80 000C0860  2C 00 00 0D */	cmpwi r0, 0xd
/* 800C3C84 000C0864  40 82 00 1C */	bne lbl_800C3CA0
/* 800C3C88 000C0868  FC 60 08 90 */	fmr f3, f1
/* 800C3C8C 000C086C  C0 42 93 24 */	lfs f2, ftCo_804D8D04
/* 800C3C90 000C0870  38 80 01 65 */	li r4, 0x165
/* 800C3C94 000C0874  38 A0 00 00 */	li r5, 0
/* 800C3C98 000C0878  38 C0 00 00 */	li r6, 0
/* 800C3C9C 000C087C  4B FA 57 11 */	bl Fighter_ChangeMotionState
lbl_800C3CA0:
/* 800C3CA0 000C0880  38 7F 00 00 */	addi r3, r31, 0
/* 800C3CA4 000C0884  38 80 01 FF */	li r4, 0x1ff
/* 800C3CA8 000C0888  4B FB A6 4D */	bl ftCommon_8007E2F4
lbl_800C3CAC:
/* 800C3CAC 000C088C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800C3CB0 000C0890  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800C3CB4 000C0894  38 21 00 28 */	addi r1, r1, 0x28
/* 800C3CB8 000C0898  7C 08 03 A6 */	mtlr r0
/* 800C3CBC 000C089C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_800C3CC0(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        Fighter_ChangeMotionState(gobj, ftLk_MS_AirCatchHit,
                                  Ft_MF_KeepFastFall, 0, 1, 0, NULL);
    } else {
        Fighter_ChangeMotionState(gobj, ftSs_MS_AirCatchHit,
                                  Ft_MF_KeepFastFall, 0, 1, 0, NULL);
    }
    ftCommon_8007D440(fp, fp->co_attrs.air_drift_max);
    fp->mv.co.aircatchhit.x0 = 20;
    fp->mv.co.aircatchhit.x4 = 0;
    if (fp->ground_or_air == GA_Ground) {
        ftCommon_8007D5D4(fp);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C3CC0 000C08A0  7C 08 02 A6 */	mflr r0
/* 800C3CC4 000C08A4  90 01 00 04 */	stw r0, 4(r1)
/* 800C3CC8 000C08A8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800C3CCC 000C08AC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800C3CD0 000C08B0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800C3CD4 000C08B4  80 04 00 04 */	lwz r0, 4(r4)
/* 800C3CD8 000C08B8  3B E4 00 00 */	addi r31, r4, 0
/* 800C3CDC 000C08BC  2C 00 00 06 */	cmpwi r0, 6
/* 800C3CE0 000C08C0  41 82 00 0C */	beq lbl_800C3CEC
/* 800C3CE4 000C08C4  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C3CE8 000C08C8  40 82 00 24 */	bne lbl_800C3D0C
lbl_800C3CEC:
/* 800C3CEC 000C08CC  C0 22 93 20 */	lfs f1, ftCo_804D8D00
/* 800C3CF0 000C08D0  38 80 01 69 */	li r4, 0x169
/* 800C3CF4 000C08D4  C0 42 93 24 */	lfs f2, ftCo_804D8D04
/* 800C3CF8 000C08D8  38 A0 00 01 */	li r5, 1
/* 800C3CFC 000C08DC  FC 60 08 90 */	fmr f3, f1
/* 800C3D00 000C08E0  38 C0 00 00 */	li r6, 0
/* 800C3D04 000C08E4  4B FA 56 A9 */	bl Fighter_ChangeMotionState
/* 800C3D08 000C08E8  48 00 00 20 */	b lbl_800C3D28
lbl_800C3D0C:
/* 800C3D0C 000C08EC  C0 22 93 20 */	lfs f1, ftCo_804D8D00
/* 800C3D10 000C08F0  38 80 01 66 */	li r4, 0x166
/* 800C3D14 000C08F4  C0 42 93 24 */	lfs f2, ftCo_804D8D04
/* 800C3D18 000C08F8  38 A0 00 01 */	li r5, 1
/* 800C3D1C 000C08FC  FC 60 08 90 */	fmr f3, f1
/* 800C3D20 000C0900  38 C0 00 00 */	li r6, 0
/* 800C3D24 000C0904  4B FA 56 89 */	bl Fighter_ChangeMotionState
lbl_800C3D28:
/* 800C3D28 000C0908  C0 3F 01 7C */	lfs f1, 0x17c(r31)
/* 800C3D2C 000C090C  7F E3 FB 78 */	mr r3, r31
/* 800C3D30 000C0910  4B FB 97 11 */	bl ftCommon_8007D440
/* 800C3D34 000C0914  38 00 00 14 */	li r0, 0x14
/* 800C3D38 000C0918  90 1F 23 40 */	stw r0, 0x2340(r31)
/* 800C3D3C 000C091C  C0 02 93 20 */	lfs f0, ftCo_804D8D00
/* 800C3D40 000C0920  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 800C3D44 000C0924  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800C3D48 000C0928  2C 00 00 00 */	cmpwi r0, 0
/* 800C3D4C 000C092C  40 82 00 0C */	bne lbl_800C3D58
/* 800C3D50 000C0930  7F E3 FB 78 */	mr r3, r31
/* 800C3D54 000C0934  4B FB 98 81 */	bl ftCommon_8007D5D4
lbl_800C3D58:
/* 800C3D58 000C0938  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800C3D5C 000C093C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800C3D60 000C0940  38 21 00 18 */	addi r1, r1, 0x18
/* 800C3D64 000C0944  7C 08 03 A6 */	mtlr r0
/* 800C3D68 000C0948  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_AirCatch_Anim(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->kind == FTKIND_LINK || fp->kind == FTKIND_CLINK) {
        ftLk_DatAttrs* da = fp->dat_attrs;
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xA4) {
            Vec3 pos;
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[4] = { 0 };
#endif
            lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint,
                        NULL, &pos);
            fp->fv.lk.xC = it_802A2BA4(gobj, &pos, fp->facing_dir, da->xBC);
            if (fp->fv.lk.xC == NULL) {
                ftCo_800968C8(gobj);
            } else {
                fp->accessory2_cb = it_802A7AF0;
                fp->death1_cb = it_802A7AAC;
                fp->accessory3_cb = it_802A7B34;
            }
            goto exit;
        } else if (fp->mv.co.aircatch.x0 > da->xA4) {
            if (fp->mv.co.aircatch.x0 <= da->xB0) {
                Item_GObj* tether_gobj = fp->fv.lk.xC;
                Item* tether_ip = GET_ITEM(fp->fv.lk.xC);
                void* tether_data =
                    M2C_FIELD(tether_ip->xC4_article_data, void**, 4);
                if (fp->mv.co.aircatch.x0 == da->xA8) {
                    Vec3 pos = { 1.8, 0, 0 };
                    HSD_JObj* jobj =
                        fp->parts[ftParts_8007500C(fp, FtPart_RThumbNb)].joint;

                    HSD_JObjSetupMatrix(jobj);
                    {
                        float var_f3 =
                            fp->kind == FTKIND_LINK
                                ? 8.0 * fp->facing_dir * fp->x34_scale.y +
                                      jobj->mtx[0][3]
                                : 8.0 * fp->facing_dir * fp->x34_scale.y +
                                      jobj->mtx[0][3];
                        if (mpLib_800524DC(
                                0, 0, 0, 0, -1, -1, fp->coll_data.x4_vec.x,
                                jobj->mtx[1][3], var_f3, jobj->mtx[1][3]) != 0)
                        {
                            it_802A2B10(fp->fv.lk.xC);
                            ftCo_800968C8(gobj);
                            return;
                        }
                    }
                    pos.x = M2C_FIELD(tether_data, float*, 0x38);
                    pos.x *= fp->facing_dir;
                    {
                        float x = pos.x;
                        pos.x = x + fp->pos_delta.x;
                        it_802A78B8(tether_gobj, &pos, x);
                    }
                    if (fp->kind == FTKIND_CLINK) {
                        ft_80088148(fp, 0x111B9, 0x7F, 0x40);
                    } else {
                        ft_80088148(fp, 0x27149, 0x7F, 0x40);
                    }
                    goto exit;
                }
                if (fp->mv.co.aircatch.x0 == (float) M2C_FIELD(da, int*, 0xAC))
                {
                    it_802A77DC(tether_gobj);
                    if (fp->kind == FTKIND_CLINK) {
                        ft_80088148(fp, 0x111BC, 0x7F, 0x40);
                    } else {
                        ft_80088148(fp, 0x2714C, 0x7F, 0x40);
                    }
                } else if (fp->mv.co.aircatch.x0 == da->xB0) {
                    it_802A2B10(fp->fv.lk.xC);
                }
                goto exit;
            }
        }
    } else if (fp->kind == FTKIND_SAMUS) {
        ftSs_DatAttrs* da = fp->dat_attrs;
        fp->mv.co.aircatch.x0 += 1.0;
        if (fp->mv.co.aircatch.x0 == da->xBC) {
            Vec3 pos;
            /// @todo Unused stack.
#ifdef MUST_MATCH
            u8 _[4] = { 0 };
#endif
            lb_8000B1CC(fp->parts[FtPart_ThrowN].joint, NULL, &pos);
            fp->fv.ss.x223C = it_802B7C18(gobj, &pos, fp->facing_dir);
            if (fp->fv.ss.x223C == NULL) {
                ftCo_800968C8(gobj);
            } else {
                fp->accessory2_cb = it_802BAC80;
                fp->death1_cb = it_802BAC3C;
                fp->accessory3_cb = it_802BACC4;
            }
        } else if (fp->mv.co.aircatch.x0 > da->xBC) {
            if (fp->mv.co.aircatch.x0 <= da->xC8) {
                Item_GObj* temp_r29_2 = fp->fv.ss.x223C;
                Item* tether_ip = GET_ITEM(temp_r29_2);
                void* tether_data =
                    M2C_FIELD(tether_ip->xC4_article_data, void**, 4);
                if (fp->mv.co.aircatch.x0 == da->xC0) {
                    Vec3 pos = { 1.8, 0, 0 };
                    HSD_JObj* jobj = fp->parts[FtPart_ThrowN].joint;
                    HSD_JObjSetupMatrix(jobj);
                    if (mpLib_800524DC(
                            0, 0, 0, 0, -1, -1, fp->coll_data.x4_vec.x,
                            jobj->mtx[1][3],
                            (2.0 * fp->facing_dir * fp->x34_scale.y) +
                                jobj->mtx[0][3],
                            jobj->mtx[1][3]))
                    {
                        it_802B7B84(fp->fv.ss.x223C);
                        ftCo_800968C8(gobj);
                        return;
                    }
                    pos.x = M2C_FIELD(tether_data, float*, 0x40);
                    pos.x *= fp->facing_dir;
                    {
                        float x = pos.x;
                        pos.x = x + fp->pos_delta.x;
                        it_802BAAE4(temp_r29_2, &pos, x);
                    }
                    goto exit;
                } else {
                    if (fp->mv.co.aircatch.x0 == da->xC4) {
                        it_802BAA58(temp_r29_2);
                    } else if (fp->mv.co.aircatch.x0 == da->xC8) {
                        it_802B7B84(fp->fv.ss.x223C);
                    }
                }
            }
        }
    }
    {
    exit:
        if (!ftAnim_IsFramesRemaining(gobj)) {
            ftCo_800968C8(gobj);
        }
        return;
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C3D6C 000C094C  7C 08 02 A6 */	mflr r0
/* 800C3D70 000C0950  90 01 00 04 */	stw r0, 4(r1)
/* 800C3D74 000C0954  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 800C3D78 000C0958  BF 61 00 7C */	stmw r27, 0x7c(r1)
/* 800C3D7C 000C095C  7C 7C 1B 78 */	mr r28, r3
/* 800C3D80 000C0960  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800C3D84 000C0964  80 03 00 04 */	lwz r0, 4(r3)
/* 800C3D88 000C0968  3B E3 00 00 */	addi r31, r3, 0
/* 800C3D8C 000C096C  2C 00 00 06 */	cmpwi r0, 6
/* 800C3D90 000C0970  41 82 00 0C */	beq lbl_800C3D9C
/* 800C3D94 000C0974  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C3D98 000C0978  40 82 03 44 */	bne lbl_800C40DC
lbl_800C3D9C:
/* 800C3D9C 000C097C  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 800C3DA0 000C0980  3C C0 43 30 */	lis r6, 0x4330
/* 800C3DA4 000C0984  C8 02 93 28 */	lfd f0, ftCo_804D8D08
/* 800C3DA8 000C0988  83 7F 02 D4 */	lwz r27, 0x2d4(r31)
/* 800C3DAC 000C098C  FC 01 00 2A */	fadd f0, f1, f0
/* 800C3DB0 000C0990  FC 00 00 18 */	frsp f0, f0
/* 800C3DB4 000C0994  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 800C3DB8 000C0998  80 1B 00 A4 */	lwz r0, 0xa4(r27)
/* 800C3DBC 000C099C  C8 22 93 40 */	lfd f1, ftCo_804D8D20
/* 800C3DC0 000C09A0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C3DC4 000C09A4  C0 5F 23 40 */	lfs f2, 0x2340(r31)
/* 800C3DC8 000C09A8  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C3DCC 000C09AC  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C3DD0 000C09B0  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C3DD4 000C09B4  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C3DD8 000C09B8  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C3DDC 000C09BC  40 82 00 80 */	bne lbl_800C3E5C
/* 800C3DE0 000C09C0  38 7F 00 00 */	addi r3, r31, 0
/* 800C3DE4 000C09C4  38 80 00 31 */	li r4, 0x31
/* 800C3DE8 000C09C8  4B FB 12 25 */	bl ftParts_8007500C
/* 800C3DEC 000C09CC  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800C3DF0 000C09D0  54 60 20 36 */	slwi r0, r3, 4
/* 800C3DF4 000C09D4  38 A1 00 64 */	addi r5, r1, 0x64
/* 800C3DF8 000C09D8  7C 64 00 2E */	lwzx r3, r4, r0
/* 800C3DFC 000C09DC  38 80 00 00 */	li r4, 0
/* 800C3E00 000C09E0  4B F4 73 CD */	bl lb_8000B1CC
/* 800C3E04 000C09E4  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800C3E08 000C09E8  7F 83 E3 78 */	mr r3, r28
/* 800C3E0C 000C09EC  80 BB 00 BC */	lwz r5, 0xbc(r27)
/* 800C3E10 000C09F0  38 81 00 64 */	addi r4, r1, 0x64
/* 800C3E14 000C09F4  48 1D ED 91 */	bl it_802A2BA4
/* 800C3E18 000C09F8  90 7F 22 38 */	stw r3, 0x2238(r31)
/* 800C3E1C 000C09FC  80 1F 22 38 */	lwz r0, 0x2238(r31)
/* 800C3E20 000C0A00  28 00 00 00 */	cmplwi r0, 0
/* 800C3E24 000C0A04  40 82 00 10 */	bne lbl_800C3E34
/* 800C3E28 000C0A08  7F 83 E3 78 */	mr r3, r28
/* 800C3E2C 000C0A0C  4B FD 2A 9D */	bl ftCo_800968C8
/* 800C3E30 000C0A10  48 00 05 24 */	b lbl_800C4354
lbl_800C3E34:
/* 800C3E34 000C0A14  3C 60 80 2A */	lis r3, it_802A7AF0@ha
/* 800C3E38 000C0A18  38 03 7A F0 */	addi r0, r3, it_802A7AF0@l
/* 800C3E3C 000C0A1C  3C 60 80 2A */	lis r3, it_802A7AAC@ha
/* 800C3E40 000C0A20  90 1F 21 B4 */	stw r0, 0x21b4(r31)
/* 800C3E44 000C0A24  38 03 7A AC */	addi r0, r3, it_802A7AAC@l
/* 800C3E48 000C0A28  3C 60 80 2A */	lis r3, it_802A7B34@ha
/* 800C3E4C 000C0A2C  90 1F 21 E0 */	stw r0, 0x21e0(r31)
/* 800C3E50 000C0A30  38 03 7B 34 */	addi r0, r3, it_802A7B34@l
/* 800C3E54 000C0A34  90 1F 21 B8 */	stw r0, 0x21b8(r31)
/* 800C3E58 000C0A38  48 00 04 FC */	b lbl_800C4354
lbl_800C3E5C:
/* 800C3E5C 000C0A3C  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C3E60 000C0A40  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C3E64 000C0A44  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C3E68 000C0A48  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C3E6C 000C0A4C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C3E70 000C0A50  40 81 04 E4 */	ble lbl_800C4354
/* 800C3E74 000C0A54  80 1B 00 B0 */	lwz r0, 0xb0(r27)
/* 800C3E78 000C0A58  6C 05 80 00 */	xoris r5, r0, 0x8000
/* 800C3E7C 000C0A5C  90 A1 00 74 */	stw r5, 0x74(r1)
/* 800C3E80 000C0A60  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C3E84 000C0A64  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C3E88 000C0A68  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C3E8C 000C0A6C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C3E90 000C0A70  4C 40 13 82 */	cror 2, 0, 2
/* 800C3E94 000C0A74  40 82 04 C0 */	bne lbl_800C4354
/* 800C3E98 000C0A78  80 1B 00 A8 */	lwz r0, 0xa8(r27)
/* 800C3E9C 000C0A7C  80 7F 22 38 */	lwz r3, 0x2238(r31)
/* 800C3EA0 000C0A80  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C3EA4 000C0A84  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C3EA8 000C0A88  7C 7E 1B 78 */	mr r30, r3
/* 800C3EAC 000C0A8C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800C3EB0 000C0A90  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C3EB4 000C0A94  80 84 00 C4 */	lwz r4, 0xc4(r4)
/* 800C3EB8 000C0A98  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C3EBC 000C0A9C  83 A4 00 04 */	lwz r29, 4(r4)
/* 800C3EC0 000C0AA0  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C3EC4 000C0AA4  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C3EC8 000C0AA8  40 82 01 88 */	bne lbl_800C4050
/* 800C3ECC 000C0AAC  3C 60 80 3B */	lis r3, lbl_803B74D4@ha
/* 800C3ED0 000C0AB0  38 C3 74 D4 */	addi r6, r3, lbl_803B74D4@l
/* 800C3ED4 000C0AB4  80 A6 00 00 */	lwz r5, 0(r6)
/* 800C3ED8 000C0AB8  7F E3 FB 78 */	mr r3, r31
/* 800C3EDC 000C0ABC  80 06 00 04 */	lwz r0, 4(r6)
/* 800C3EE0 000C0AC0  38 80 00 31 */	li r4, 0x31
/* 800C3EE4 000C0AC4  90 A1 00 54 */	stw r5, 0x54(r1)
/* 800C3EE8 000C0AC8  90 01 00 58 */	stw r0, 0x58(r1)
/* 800C3EEC 000C0ACC  80 06 00 08 */	lwz r0, 8(r6)
/* 800C3EF0 000C0AD0  90 01 00 5C */	stw r0, 0x5c(r1)
/* 800C3EF4 000C0AD4  4B FB 11 19 */	bl ftParts_8007500C
/* 800C3EF8 000C0AD8  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800C3EFC 000C0ADC  54 60 20 36 */	slwi r0, r3, 4
/* 800C3F00 000C0AE0  7F 64 00 2E */	lwzx r27, r4, r0
/* 800C3F04 000C0AE4  28 1B 00 00 */	cmplwi r27, 0
/* 800C3F08 000C0AE8  41 82 00 44 */	beq lbl_800C3F4C
/* 800C3F0C 000C0AEC  40 82 00 14 */	bne lbl_800C3F20
/* 800C3F10 000C0AF0  38 6D 85 A8 */	addi r3, r13, ftCo_804D3C48
/* 800C3F14 000C0AF4  38 80 02 34 */	li r4, 0x234
/* 800C3F18 000C0AF8  38 AD 85 B0 */	addi r5, r13, ftCo_804D3C50
/* 800C3F1C 000C0AFC  48 2C 43 05 */	bl __assert
lbl_800C3F20:
/* 800C3F20 000C0B00  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 800C3F24 000C0B04  38 60 00 00 */	li r3, 0
/* 800C3F28 000C0B08  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C3F2C 000C0B0C  40 82 00 10 */	bne lbl_800C3F3C
/* 800C3F30 000C0B10  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C3F34 000C0B14  41 82 00 08 */	beq lbl_800C3F3C
/* 800C3F38 000C0B18  38 60 00 01 */	li r3, 1
lbl_800C3F3C:
/* 800C3F3C 000C0B1C  2C 03 00 00 */	cmpwi r3, 0
/* 800C3F40 000C0B20  41 82 00 0C */	beq lbl_800C3F4C
/* 800C3F44 000C0B24  7F 63 DB 78 */	mr r3, r27
/* 800C3F48 000C0B28  48 2A F1 31 */	bl HSD_JObjSetupMatrixSub
lbl_800C3F4C:
/* 800C3F4C 000C0B2C  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C3F50 000C0B30  2C 00 00 06 */	cmpwi r0, 6
/* 800C3F54 000C0B34  40 82 00 24 */	bne lbl_800C3F78
/* 800C3F58 000C0B38  C8 42 93 30 */	lfd f2, ftCo_804D8D10
/* 800C3F5C 000C0B3C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C3F60 000C0B40  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800C3F64 000C0B44  FC 42 00 32 */	fmul f2, f2, f0
/* 800C3F68 000C0B48  C0 1B 00 50 */	lfs f0, 0x50(r27)
/* 800C3F6C 000C0B4C  FC 62 00 7A */	fmadd f3, f2, f1, f0
/* 800C3F70 000C0B50  FC 60 18 18 */	frsp f3, f3
/* 800C3F74 000C0B54  48 00 00 20 */	b lbl_800C3F94
lbl_800C3F78:
/* 800C3F78 000C0B58  C8 42 93 30 */	lfd f2, ftCo_804D8D10
/* 800C3F7C 000C0B5C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C3F80 000C0B60  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800C3F84 000C0B64  FC 42 00 32 */	fmul f2, f2, f0
/* 800C3F88 000C0B68  C0 1B 00 50 */	lfs f0, 0x50(r27)
/* 800C3F8C 000C0B6C  FC 62 00 7A */	fmadd f3, f2, f1, f0
/* 800C3F90 000C0B70  FC 60 18 18 */	frsp f3, f3
lbl_800C3F94:
/* 800C3F94 000C0B74  C0 5B 00 60 */	lfs f2, 0x60(r27)
/* 800C3F98 000C0B78  38 60 00 00 */	li r3, 0
/* 800C3F9C 000C0B7C  C0 3F 06 F4 */	lfs f1, 0x6f4(r31)
/* 800C3FA0 000C0B80  38 80 00 00 */	li r4, 0
/* 800C3FA4 000C0B84  FC 80 10 90 */	fmr f4, f2
/* 800C3FA8 000C0B88  38 A0 00 00 */	li r5, 0
/* 800C3FAC 000C0B8C  38 C0 00 00 */	li r6, 0
/* 800C3FB0 000C0B90  38 E0 FF FF */	li r7, -1
/* 800C3FB4 000C0B94  39 00 FF FF */	li r8, -1
/* 800C3FB8 000C0B98  4B F8 E5 25 */	bl mpLib_800524DC
/* 800C3FBC 000C0B9C  2C 03 00 00 */	cmpwi r3, 0
/* 800C3FC0 000C0BA0  41 82 00 18 */	beq lbl_800C3FD8
/* 800C3FC4 000C0BA4  80 7F 22 38 */	lwz r3, 0x2238(r31)
/* 800C3FC8 000C0BA8  48 1D EB 49 */	bl it_802A2B10
/* 800C3FCC 000C0BAC  7F 83 E3 78 */	mr r3, r28
/* 800C3FD0 000C0BB0  4B FD 28 F9 */	bl ftCo_800968C8
/* 800C3FD4 000C0BB4  48 00 03 98 */	b lbl_800C436C
lbl_800C3FD8:
/* 800C3FD8 000C0BB8  C0 1D 00 38 */	lfs f0, 0x38(r29)
/* 800C3FDC 000C0BBC  38 7E 00 00 */	addi r3, r30, 0
/* 800C3FE0 000C0BC0  38 81 00 54 */	addi r4, r1, 0x54
/* 800C3FE4 000C0BC4  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800C3FE8 000C0BC8  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 800C3FEC 000C0BCC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C3FF0 000C0BD0  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C3FF4 000C0BD4  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800C3FF8 000C0BD8  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 800C3FFC 000C0BDC  C0 1F 00 C8 */	lfs f0, 0xc8(r31)
/* 800C4000 000C0BE0  EC 01 00 2A */	fadds f0, f1, f0
/* 800C4004 000C0BE4  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 800C4008 000C0BE8  48 1E 38 B1 */	bl it_802A78B8
/* 800C400C 000C0BEC  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C4010 000C0BF0  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C4014 000C0BF4  40 82 00 20 */	bne lbl_800C4034
/* 800C4018 000C0BF8  3C 80 00 01 */	lis r4, 0x000111B9@ha
/* 800C401C 000C0BFC  38 7F 00 00 */	addi r3, r31, 0
/* 800C4020 000C0C00  38 84 11 B9 */	addi r4, r4, 0x000111B9@l
/* 800C4024 000C0C04  38 A0 00 7F */	li r5, 0x7f
/* 800C4028 000C0C08  38 C0 00 40 */	li r6, 0x40
/* 800C402C 000C0C0C  4B FC 41 1D */	bl ft_80088148
/* 800C4030 000C0C10  48 00 03 24 */	b lbl_800C4354
lbl_800C4034:
/* 800C4034 000C0C14  3C 80 00 02 */	lis r4, 0x00027149@ha
/* 800C4038 000C0C18  38 7F 00 00 */	addi r3, r31, 0
/* 800C403C 000C0C1C  38 84 71 49 */	addi r4, r4, 0x00027149@l
/* 800C4040 000C0C20  38 A0 00 7F */	li r5, 0x7f
/* 800C4044 000C0C24  38 C0 00 40 */	li r6, 0x40
/* 800C4048 000C0C28  4B FC 41 01 */	bl ft_80088148
/* 800C404C 000C0C2C  48 00 03 08 */	b lbl_800C4354
lbl_800C4050:
/* 800C4050 000C0C30  80 1B 00 AC */	lwz r0, 0xac(r27)
/* 800C4054 000C0C34  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C4058 000C0C38  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C405C 000C0C3C  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C4060 000C0C40  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C4064 000C0C44  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C4068 000C0C48  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C406C 000C0C4C  40 82 00 50 */	bne lbl_800C40BC
/* 800C4070 000C0C50  7F C3 F3 78 */	mr r3, r30
/* 800C4074 000C0C54  48 1E 37 69 */	bl it_802A77DC
/* 800C4078 000C0C58  80 1F 00 04 */	lwz r0, 4(r31)
/* 800C407C 000C0C5C  2C 00 00 14 */	cmpwi r0, 0x14
/* 800C4080 000C0C60  40 82 00 20 */	bne lbl_800C40A0
/* 800C4084 000C0C64  3C 80 00 01 */	lis r4, 0x000111BC@ha
/* 800C4088 000C0C68  38 7F 00 00 */	addi r3, r31, 0
/* 800C408C 000C0C6C  38 84 11 BC */	addi r4, r4, 0x000111BC@l
/* 800C4090 000C0C70  38 A0 00 7F */	li r5, 0x7f
/* 800C4094 000C0C74  38 C0 00 40 */	li r6, 0x40
/* 800C4098 000C0C78  4B FC 40 B1 */	bl ft_80088148
/* 800C409C 000C0C7C  48 00 02 B8 */	b lbl_800C4354
lbl_800C40A0:
/* 800C40A0 000C0C80  3C 80 00 02 */	lis r4, 0x0002714C@ha
/* 800C40A4 000C0C84  38 7F 00 00 */	addi r3, r31, 0
/* 800C40A8 000C0C88  38 84 71 4C */	addi r4, r4, 0x0002714C@l
/* 800C40AC 000C0C8C  38 A0 00 7F */	li r5, 0x7f
/* 800C40B0 000C0C90  38 C0 00 40 */	li r6, 0x40
/* 800C40B4 000C0C94  4B FC 40 95 */	bl ft_80088148
/* 800C40B8 000C0C98  48 00 02 9C */	b lbl_800C4354
lbl_800C40BC:
/* 800C40BC 000C0C9C  90 A1 00 74 */	stw r5, 0x74(r1)
/* 800C40C0 000C0CA0  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C40C4 000C0CA4  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C40C8 000C0CA8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C40CC 000C0CAC  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C40D0 000C0CB0  40 82 02 84 */	bne lbl_800C4354
/* 800C40D4 000C0CB4  48 1D EA 3D */	bl it_802A2B10
/* 800C40D8 000C0CB8  48 00 02 7C */	b lbl_800C4354
lbl_800C40DC:
/* 800C40DC 000C0CBC  2C 00 00 0D */	cmpwi r0, 0xd
/* 800C40E0 000C0CC0  40 82 02 74 */	bne lbl_800C4354
/* 800C40E4 000C0CC4  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 800C40E8 000C0CC8  3C C0 43 30 */	lis r6, 0x4330
/* 800C40EC 000C0CCC  C8 02 93 28 */	lfd f0, ftCo_804D8D08
/* 800C40F0 000C0CD0  80 FF 02 D4 */	lwz r7, 0x2d4(r31)
/* 800C40F4 000C0CD4  FC 01 00 2A */	fadd f0, f1, f0
/* 800C40F8 000C0CD8  FC 00 00 18 */	frsp f0, f0
/* 800C40FC 000C0CDC  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 800C4100 000C0CE0  80 07 00 BC */	lwz r0, 0xbc(r7)
/* 800C4104 000C0CE4  C8 22 93 40 */	lfd f1, ftCo_804D8D20
/* 800C4108 000C0CE8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C410C 000C0CEC  C0 5F 23 40 */	lfs f2, 0x2340(r31)
/* 800C4110 000C0CF0  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C4114 000C0CF4  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C4118 000C0CF8  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C411C 000C0CFC  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C4120 000C0D00  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C4124 000C0D04  40 82 00 6C */	bne lbl_800C4190
/* 800C4128 000C0D08  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 800C412C 000C0D0C  38 A1 00 3C */	addi r5, r1, 0x3c
/* 800C4130 000C0D10  38 80 00 00 */	li r4, 0
/* 800C4134 000C0D14  80 63 03 30 */	lwz r3, 0x330(r3)
/* 800C4138 000C0D18  4B F4 70 95 */	bl lb_8000B1CC
/* 800C413C 000C0D1C  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 800C4140 000C0D20  38 7C 00 00 */	addi r3, r28, 0
/* 800C4144 000C0D24  38 81 00 3C */	addi r4, r1, 0x3c
/* 800C4148 000C0D28  48 1F 3A D1 */	bl it_802B7C18
/* 800C414C 000C0D2C  90 7F 22 3C */	stw r3, 0x223c(r31)
/* 800C4150 000C0D30  80 1F 22 3C */	lwz r0, 0x223c(r31)
/* 800C4154 000C0D34  28 00 00 00 */	cmplwi r0, 0
/* 800C4158 000C0D38  40 82 00 10 */	bne lbl_800C4168
/* 800C415C 000C0D3C  7F 83 E3 78 */	mr r3, r28
/* 800C4160 000C0D40  4B FD 27 69 */	bl ftCo_800968C8
/* 800C4164 000C0D44  48 00 01 F0 */	b lbl_800C4354
lbl_800C4168:
/* 800C4168 000C0D48  3C 60 80 2C */	lis r3, it_802BAC80@ha
/* 800C416C 000C0D4C  38 03 AC 80 */	addi r0, r3, it_802BAC80@l
/* 800C4170 000C0D50  3C 60 80 2C */	lis r3, it_802BAC3C@ha
/* 800C4174 000C0D54  90 1F 21 B4 */	stw r0, 0x21b4(r31)
/* 800C4178 000C0D58  38 03 AC 3C */	addi r0, r3, it_802BAC3C@l
/* 800C417C 000C0D5C  3C 60 80 2C */	lis r3, it_802BACC4@ha
/* 800C4180 000C0D60  90 1F 21 E0 */	stw r0, 0x21e0(r31)
/* 800C4184 000C0D64  38 03 AC C4 */	addi r0, r3, it_802BACC4@l
/* 800C4188 000C0D68  90 1F 21 B8 */	stw r0, 0x21b8(r31)
/* 800C418C 000C0D6C  48 00 01 C8 */	b lbl_800C4354
lbl_800C4190:
/* 800C4190 000C0D70  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C4194 000C0D74  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C4198 000C0D78  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C419C 000C0D7C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C41A0 000C0D80  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C41A4 000C0D84  40 81 01 B0 */	ble lbl_800C4354
/* 800C41A8 000C0D88  80 07 00 C8 */	lwz r0, 0xc8(r7)
/* 800C41AC 000C0D8C  6C 05 80 00 */	xoris r5, r0, 0x8000
/* 800C41B0 000C0D90  90 A1 00 74 */	stw r5, 0x74(r1)
/* 800C41B4 000C0D94  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C41B8 000C0D98  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C41BC 000C0D9C  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C41C0 000C0DA0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800C41C4 000C0DA4  4C 40 13 82 */	cror 2, 0, 2
/* 800C41C8 000C0DA8  40 82 01 8C */	bne lbl_800C4354
/* 800C41CC 000C0DAC  80 07 00 C0 */	lwz r0, 0xc0(r7)
/* 800C41D0 000C0DB0  80 7F 22 3C */	lwz r3, 0x223c(r31)
/* 800C41D4 000C0DB4  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C41D8 000C0DB8  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C41DC 000C0DBC  7C 7D 1B 78 */	mr r29, r3
/* 800C41E0 000C0DC0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800C41E4 000C0DC4  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C41E8 000C0DC8  80 84 00 C4 */	lwz r4, 0xc4(r4)
/* 800C41EC 000C0DCC  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C41F0 000C0DD0  83 C4 00 04 */	lwz r30, 4(r4)
/* 800C41F4 000C0DD4  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C41F8 000C0DD8  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C41FC 000C0DDC  40 82 01 10 */	bne lbl_800C430C
/* 800C4200 000C0DE0  3C 60 80 3B */	lis r3, lbl_803B74E0@ha
/* 800C4204 000C0DE4  38 83 74 E0 */	addi r4, r3, lbl_803B74E0@l
/* 800C4208 000C0DE8  80 64 00 00 */	lwz r3, 0(r4)
/* 800C420C 000C0DEC  80 04 00 04 */	lwz r0, 4(r4)
/* 800C4210 000C0DF0  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800C4214 000C0DF4  90 01 00 30 */	stw r0, 0x30(r1)
/* 800C4218 000C0DF8  80 04 00 08 */	lwz r0, 8(r4)
/* 800C421C 000C0DFC  90 01 00 34 */	stw r0, 0x34(r1)
/* 800C4220 000C0E00  80 7F 05 E8 */	lwz r3, 0x5e8(r31)
/* 800C4224 000C0E04  80 03 03 30 */	lwz r0, 0x330(r3)
/* 800C4228 000C0E08  28 00 00 00 */	cmplwi r0, 0
/* 800C422C 000C0E0C  7C 1B 03 78 */	mr r27, r0
/* 800C4230 000C0E10  41 82 00 44 */	beq lbl_800C4274
/* 800C4234 000C0E14  40 82 00 14 */	bne lbl_800C4248
/* 800C4238 000C0E18  38 6D 85 A8 */	addi r3, r13, ftCo_804D3C48
/* 800C423C 000C0E1C  38 80 02 34 */	li r4, 0x234
/* 800C4240 000C0E20  38 AD 85 B0 */	addi r5, r13, ftCo_804D3C50
/* 800C4244 000C0E24  48 2C 3F DD */	bl __assert
lbl_800C4248:
/* 800C4248 000C0E28  80 9B 00 14 */	lwz r4, 0x14(r27)
/* 800C424C 000C0E2C  38 60 00 00 */	li r3, 0
/* 800C4250 000C0E30  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800C4254 000C0E34  40 82 00 10 */	bne lbl_800C4264
/* 800C4258 000C0E38  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800C425C 000C0E3C  41 82 00 08 */	beq lbl_800C4264
/* 800C4260 000C0E40  38 60 00 01 */	li r3, 1
lbl_800C4264:
/* 800C4264 000C0E44  2C 03 00 00 */	cmpwi r3, 0
/* 800C4268 000C0E48  41 82 00 0C */	beq lbl_800C4274
/* 800C426C 000C0E4C  7F 63 DB 78 */	mr r3, r27
/* 800C4270 000C0E50  48 2A EE 09 */	bl HSD_JObjSetupMatrixSub
lbl_800C4274:
/* 800C4274 000C0E54  C8 22 93 38 */	lfd f1, ftCo_804D8D18
/* 800C4278 000C0E58  38 60 00 00 */	li r3, 0
/* 800C427C 000C0E5C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C4280 000C0E60  38 80 00 00 */	li r4, 0
/* 800C4284 000C0E64  C0 5B 00 60 */	lfs f2, 0x60(r27)
/* 800C4288 000C0E68  FC 61 00 32 */	fmul f3, f1, f0
/* 800C428C 000C0E6C  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800C4290 000C0E70  C0 1B 00 50 */	lfs f0, 0x50(r27)
/* 800C4294 000C0E74  38 A0 00 00 */	li r5, 0
/* 800C4298 000C0E78  FC 80 10 90 */	fmr f4, f2
/* 800C429C 000C0E7C  FC 63 00 7A */	fmadd f3, f3, f1, f0
/* 800C42A0 000C0E80  C0 3F 06 F4 */	lfs f1, 0x6f4(r31)
/* 800C42A4 000C0E84  38 C0 00 00 */	li r6, 0
/* 800C42A8 000C0E88  38 E0 FF FF */	li r7, -1
/* 800C42AC 000C0E8C  39 00 FF FF */	li r8, -1
/* 800C42B0 000C0E90  FC 60 18 18 */	frsp f3, f3
/* 800C42B4 000C0E94  4B F8 E2 29 */	bl mpLib_800524DC
/* 800C42B8 000C0E98  2C 03 00 00 */	cmpwi r3, 0
/* 800C42BC 000C0E9C  41 82 00 18 */	beq lbl_800C42D4
/* 800C42C0 000C0EA0  80 7F 22 3C */	lwz r3, 0x223c(r31)
/* 800C42C4 000C0EA4  48 1F 38 C1 */	bl it_802B7B84
/* 800C42C8 000C0EA8  7F 83 E3 78 */	mr r3, r28
/* 800C42CC 000C0EAC  4B FD 25 FD */	bl ftCo_800968C8
/* 800C42D0 000C0EB0  48 00 00 9C */	b lbl_800C436C
lbl_800C42D4:
/* 800C42D4 000C0EB4  C0 1E 00 40 */	lfs f0, 0x40(r30)
/* 800C42D8 000C0EB8  38 7D 00 00 */	addi r3, r29, 0
/* 800C42DC 000C0EBC  38 81 00 2C */	addi r4, r1, 0x2c
/* 800C42E0 000C0EC0  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C42E4 000C0EC4  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 800C42E8 000C0EC8  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800C42EC 000C0ECC  EC 01 00 32 */	fmuls f0, f1, f0
/* 800C42F0 000C0ED0  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C42F4 000C0ED4  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 800C42F8 000C0ED8  C0 1F 00 C8 */	lfs f0, 0xc8(r31)
/* 800C42FC 000C0EDC  EC 01 00 2A */	fadds f0, f1, f0
/* 800C4300 000C0EE0  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 800C4304 000C0EE4  48 1F 67 E1 */	bl it_802BAAE4
/* 800C4308 000C0EE8  48 00 00 4C */	b lbl_800C4354
lbl_800C430C:
/* 800C430C 000C0EEC  80 07 00 C4 */	lwz r0, 0xc4(r7)
/* 800C4310 000C0EF0  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 800C4314 000C0EF4  90 01 00 74 */	stw r0, 0x74(r1)
/* 800C4318 000C0EF8  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C431C 000C0EFC  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C4320 000C0F00  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C4324 000C0F04  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C4328 000C0F08  40 82 00 10 */	bne lbl_800C4338
/* 800C432C 000C0F0C  7F A3 EB 78 */	mr r3, r29
/* 800C4330 000C0F10  48 1F 67 29 */	bl it_802BAA58
/* 800C4334 000C0F14  48 00 00 20 */	b lbl_800C4354
lbl_800C4338:
/* 800C4338 000C0F18  90 A1 00 74 */	stw r5, 0x74(r1)
/* 800C433C 000C0F1C  90 C1 00 70 */	stw r6, 0x70(r1)
/* 800C4340 000C0F20  C8 01 00 70 */	lfd f0, 0x70(r1)
/* 800C4344 000C0F24  EC 00 08 28 */	fsubs f0, f0, f1
/* 800C4348 000C0F28  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 800C434C 000C0F2C  40 82 00 08 */	bne lbl_800C4354
/* 800C4350 000C0F30  48 1F 38 35 */	bl it_802B7B84
lbl_800C4354:
/* 800C4354 000C0F34  7F 83 E3 78 */	mr r3, r28
/* 800C4358 000C0F38  4B FA AE E1 */	bl ftAnim_IsFramesRemaining
/* 800C435C 000C0F3C  2C 03 00 00 */	cmpwi r3, 0
/* 800C4360 000C0F40  40 82 00 0C */	bne lbl_800C436C
/* 800C4364 000C0F44  7F 83 E3 78 */	mr r3, r28
/* 800C4368 000C0F48  4B FD 25 61 */	bl ftCo_800968C8
lbl_800C436C:
/* 800C436C 000C0F4C  BB 61 00 7C */	lmw r27, 0x7c(r1)
/* 800C4370 000C0F50  80 01 00 94 */	lwz r0, 0x94(r1)
/* 800C4374 000C0F54  38 21 00 90 */	addi r1, r1, 0x90
/* 800C4378 000C0F58  7C 08 03 A6 */	mtlr r0
/* 800C437C 000C0F5C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_AirCatchHit_Anim(ftCo_GObj* gobj) {}

void ftCo_AirCatch_IASA(ftCo_GObj* gobj) {}

void ftCo_AirCatchHit_IASA(ftCo_GObj* gobj) {}

ASM void ftCo_AirCatch_Phys(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* co = &fp->co_attrs;
    ftCommon_8007D528(fp);
    if (fp->x221A_b4) {
        ftCommon_8007D4E4(fp);
    } else if (fp->mv.co.aircatch.x0 < 20 && fp->pos_delta.y < 0.0) {
        ftCommon_8007D494(fp, co->grav * 0.2, co->terminal_vel);
    } else {
        ftCommon_8007D494(fp, co->grav, co->terminal_vel);
    }
    ftCommon_8007D268(fp);
}

#else /* clang-format off */
{ nofralloc
/* 800C438C 000C0F6C  7C 08 02 A6 */	mflr r0
/* 800C4390 000C0F70  90 01 00 04 */	stw r0, 4(r1)
/* 800C4394 000C0F74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C4398 000C0F78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C439C 000C0F7C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800C43A0 000C0F80  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800C43A4 000C0F84  38 7F 00 00 */	addi r3, r31, 0
/* 800C43A8 000C0F88  3B DF 01 10 */	addi r30, r31, 0x110
/* 800C43AC 000C0F8C  4B FB 91 7D */	bl ftCommon_8007D528
/* 800C43B0 000C0F90  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800C43B4 000C0F94  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800C43B8 000C0F98  41 82 00 10 */	beq lbl_800C43C8
/* 800C43BC 000C0F9C  7F E3 FB 78 */	mr r3, r31
/* 800C43C0 000C0FA0  4B FB 91 25 */	bl ftCommon_8007D4E4
/* 800C43C4 000C0FA4  48 00 00 54 */	b lbl_800C4418
lbl_800C43C8:
/* 800C43C8 000C0FA8  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 800C43CC 000C0FAC  C0 02 93 48 */	lfs f0, ftCo_804D8D28
/* 800C43D0 000C0FB0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C43D4 000C0FB4  40 80 00 34 */	bge lbl_800C4408
/* 800C43D8 000C0FB8  C0 3F 00 CC */	lfs f1, 0xcc(r31)
/* 800C43DC 000C0FBC  C8 02 93 18 */	lfd f0, ftCo_804D8CF8
/* 800C43E0 000C0FC0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800C43E4 000C0FC4  40 80 00 24 */	bge lbl_800C4408
/* 800C43E8 000C0FC8  C8 22 93 50 */	lfd f1, ftCo_804D8D30
/* 800C43EC 000C0FCC  7F E3 FB 78 */	mr r3, r31
/* 800C43F0 000C0FD0  C0 1E 00 5C */	lfs f0, 0x5c(r30)
/* 800C43F4 000C0FD4  C0 5E 00 60 */	lfs f2, 0x60(r30)
/* 800C43F8 000C0FD8  FC 21 00 32 */	fmul f1, f1, f0
/* 800C43FC 000C0FDC  FC 20 08 18 */	frsp f1, f1
/* 800C4400 000C0FE0  4B FB 90 95 */	bl ftCommon_8007D494
/* 800C4404 000C0FE4  48 00 00 14 */	b lbl_800C4418
lbl_800C4408:
/* 800C4408 000C0FE8  C0 3E 00 5C */	lfs f1, 0x5c(r30)
/* 800C440C 000C0FEC  7F E3 FB 78 */	mr r3, r31
/* 800C4410 000C0FF0  C0 5E 00 60 */	lfs f2, 0x60(r30)
/* 800C4414 000C0FF4  4B FB 90 81 */	bl ftCommon_8007D494
lbl_800C4418:
/* 800C4418 000C0FF8  7F E3 FB 78 */	mr r3, r31
/* 800C441C 000C0FFC  4B FB 8E 4D */	bl ftCommon_8007D268
/* 800C4420 000C1000  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C4424 000C1004  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C4428 000C1008  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800C442C 000C100C  38 21 00 20 */	addi r1, r1, 0x20
/* 800C4430 000C1010  7C 08 03 A6 */	mtlr r0
/* 800C4434 000C1014  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_AirCatchHit_Phys(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel = fp->pos_delta;
    ftCommon_8007D494(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
}

ASM void ftCo_AirCatch_Coll(ftCo_GObj* gobj)
#ifndef MUST_MATCH
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftCo_800D5AEC(gobj, 42, 0, 0, 0, 1);
    }
}

#else /* clang-format off */
{ nofralloc
/* 800C447C 000C105C  7C 08 02 A6 */	mflr r0
/* 800C4480 000C1060  90 01 00 04 */	stw r0, 4(r1)
/* 800C4484 000C1064  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800C4488 000C1068  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800C448C 000C106C  7C 7F 1B 78 */	mr r31, r3
/* 800C4490 000C1070  4B FB D8 7D */	bl ft_80081D0C
/* 800C4494 000C1074  2C 03 00 00 */	cmpwi r3, 0
/* 800C4498 000C1078  41 82 00 20 */	beq lbl_800C44B8
/* 800C449C 000C107C  C0 22 93 20 */	lfs f1, ftCo_804D8D00
/* 800C44A0 000C1080  7F E3 FB 78 */	mr r3, r31
/* 800C44A4 000C1084  C0 42 93 24 */	lfs f2, ftCo_804D8D04
/* 800C44A8 000C1088  38 80 00 2A */	li r4, 0x2a
/* 800C44AC 000C108C  38 A0 00 00 */	li r5, 0
/* 800C44B0 000C1090  38 C0 00 00 */	li r6, 0
/* 800C44B4 000C1094  48 01 16 39 */	bl ftCo_800D5AEC
lbl_800C44B8:
/* 800C44B8 000C1098  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800C44BC 000C109C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800C44C0 000C10A0  38 21 00 20 */	addi r1, r1, 0x20
/* 800C44C4 000C10A4  7C 08 03 A6 */	mtlr r0
/* 800C44C8 000C10A8  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
