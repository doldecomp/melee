#include "ft/forward.h"

#include "ftmaterial.h"

#include "ft/fighter.h"
#include "ft/ft_0C31.h"
#include "ft/ft_0D14.h"
#include "ft/types.h"
#include "ftCommon/ftCo_09F4.h"
#include "gm/gm_1601.h"
#include "lb/lbrefract.h"
#include "pl/player.h"

#include <m2c_macros.h>
#include <placeholder.h>
#include <baselib/class.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/mobj.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <baselib/texp.h>
#include <baselib/tobj.h>

#ifdef MUST_MATCH
#include "melee/ft/ftdevice.h"
#include "melee/lb/lb_00B0.h"
#endif

/* literal */ extern char* ftCo_804D3C00;
/* literal */ extern char* ftCo_804D3C08;
/* literal */ float const ftCo_804D8C20 = 0;
/* literal */ float const ftCo_804D8C24 = 1;

#ifdef WIP
#pragma force_active on
#endif

ASM void ftMaterial_800BF260(void)
#ifndef MUST_MATCH
{
    hsdInitClassInfo(&ftMObj.parent, &hsdMObj.parent,
                     "sysdolphin_base_library", "ft_mobj", 80, 32);
    ftMObj.setup = ftMaterial_800BF2B8;
}

#else /* clang-format off */
{ nofralloc
/* 800BF260 000BBE40  7C 08 02 A6 */	mflr r0
/* 800BF264 000BBE44  3C 60 80 3C */	lis r3, ftMObj@ha
/* 800BF268 000BBE48  90 01 00 04 */	stw r0, 4(r1)
/* 800BF26C 000BBE4C  38 CD 85 60 */	addi r6, r13, ftCo_804D3C00
/* 800BF270 000BBE50  38 E0 00 50 */	li r7, 0x50
/* 800BF274 000BBE54  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800BF278 000BBE58  39 00 00 20 */	li r8, 0x20
/* 800BF27C 000BBE5C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 800BF280 000BBE60  3B E3 69 80 */	addi r31, r3, ftMObj@l
/* 800BF284 000BBE64  3C 60 80 40 */	lis r3, hsdMObj@ha
/* 800BF288 000BBE68  38 83 5E 28 */	addi r4, r3, hsdMObj@l
/* 800BF28C 000BBE6C  38 7F 00 00 */	addi r3, r31, 0
/* 800BF290 000BBE70  38 BF 00 DC */	addi r5, r31, 0xdc
/* 800BF294 000BBE74  48 2C 29 85 */	bl hsdInitClassInfo
/* 800BF298 000BBE78  3C 60 80 0C */	lis r3, ftMaterial_800BF2B8@ha
/* 800BF29C 000BBE7C  38 03 F2 B8 */	addi r0, r3, ftMaterial_800BF2B8@l
/* 800BF2A0 000BBE80  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 800BF2A4 000BBE84  80 01 00 14 */	lwz r0, 0x14(r1)
/* 800BF2A8 000BBE88  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 800BF2AC 000BBE8C  38 21 00 10 */	addi r1, r1, 0x10
/* 800BF2B0 000BBE90  7C 08 03 A6 */	mtlr r0
/* 800BF2B4 000BBE94  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftMaterial_800BF2B8(HSD_MObj* mobj, u32 rendermode)
#ifndef MUST_MATCH
{
    HSD_TExp texp;
    HSD_PEDesc pe;
    Fighter* fp = GET_FIGHTER(HSD_GObj_804D7814);

    if (fp->x2226_b5) {
        lbRefract_80022998(mobj, rendermode);
        return;
    }

    if (!fp->x2223_b7 && (!fp->x2228_b0 || !fp->x2224_b0)) {
        if (M2C_FIELD(fp, u8*, 0x2223) & 1) {
            mobj = ft_804D6580;
        } else if (fp->x2227_b3) {
            mobj = ft_804D6588;
        }
    }

    HSD_StateInitTev();

    {
        u32 mobj_rendermode = mobj->rendermode;
        HSD_SetMaterialColor(mobj->mat->ambient, mobj->mat->diffuse,
                             mobj->mat->specular, mobj->mat->alpha);
        if (mobj_rendermode & RENDER_SPECULAR) {
            HSD_SetMaterialShininess(mobj->mat->shininess);
        }
        {
            HSD_TObj** cur_tobj = NULL;
            {
                HSD_TObj* tobj = mobj->tobj;
                if (mobj_rendermode & RENDER_SHADOW && tobj_shadows != NULL) {
                    cur_tobj = &tobj;
                    while (*cur_tobj != NULL) {
                        cur_tobj = &(*cur_tobj)->next;
                    }
                    *cur_tobj = tobj_shadows;
                }
                if ((mobj_rendermode & RENDER_TOON) && tobj_toon != NULL &&
                    tobj_toon->imagedesc != NULL)
                {
                    tobj_toon->next = tobj;
                    tobj = tobj_toon;
                }
                HSD_TObjSetup(tobj);
                HSD_TObjSetupTextureCoordGen(tobj);
                {
                    M2C_FIELD(
                        mobj->parent.class_info,
                        M2C_UNK(**)(HSD_MObj*, HSD_TObj*, u32, HSD_ClassInfo*),
                        0x48)
                    (mobj, tobj, mobj_rendermode, mobj->parent.class_info);
                }
            }
            if (fp->x61D != 0xFF) {
                mobj_rendermode |= RENDER_NO_ZUPDATE | RENDER_XLU;
            }
            {
                HSD_TExp* texp1 = ftMaterial_800BF534(fp, mobj, &texp);
                ftMaterial_800BF6BC(fp, mobj, texp1);
                if (fp->x2223_b2 && !fp->x2223_b3) {
                    mobj_rendermode |= RENDER_NO_ZUPDATE;
                }
                {
                    HSD_PEDesc* pe_p;
                    if (fp->x2223_b4 && fp->x61D == 0xFF) {
                        pe.flags = (1 << 3) | (1 << 4) | (1 << 5);
                        pe.dst_alpha = 0;
                        pe.type = 0;
                        pe.src_factor = 4;
                        pe_p = &pe;
                        pe.dst_factor = 5;
                        pe.logic_op = 15;
                        pe.z_comp = 3;
                        pe.alpha_comp0 = 7;
                        pe.ref0 = 0;
                        pe.alpha_op = 0;
                        pe.alpha_comp1 = 7;
                        pe.ref1 = 0;
                    } else {
                        pe_p = mobj->pe;
                    }
                    HSD_SetupRenderModeWithCustomPE(mobj_rendermode, pe_p);
                }
                if (texp1 == NULL) {
                    ftCo_8009F75C(fp, true);
                }
            }
            if (cur_tobj != NULL) {
                *cur_tobj = NULL;
            }
        }
    }
}

#else /* clang-format off */
{ nofralloc
/* 800BF2B8 000BBE98  7C 08 02 A6 */	mflr r0
/* 800BF2BC 000BBE9C  90 01 00 04 */	stw r0, 4(r1)
/* 800BF2C0 000BBEA0  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 800BF2C4 000BBEA4  BF 61 00 AC */	stmw r27, 0xac(r1)
/* 800BF2C8 000BBEA8  3B 63 00 00 */	addi r27, r3, 0
/* 800BF2CC 000BBEAC  3B 84 00 00 */	addi r28, r4, 0
/* 800BF2D0 000BBEB0  80 AD C1 74 */	lwz r5, HSD_GObj_804D7814
/* 800BF2D4 000BBEB4  80 65 00 2C */	lwz r3, 0x2c(r5)
/* 800BF2D8 000BBEB8  88 03 22 26 */	lbz r0, 0x2226(r3)
/* 800BF2DC 000BBEBC  3B E3 00 00 */	addi r31, r3, 0
/* 800BF2E0 000BBEC0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800BF2E4 000BBEC4  41 82 00 18 */	beq lbl_800BF2FC
/* 800BF2E8 000BBEC8  88 BF 21 34 */	lbz r5, 0x2134(r31)
/* 800BF2EC 000BBECC  38 7B 00 00 */	addi r3, r27, 0
/* 800BF2F0 000BBED0  38 9C 00 00 */	addi r4, r28, 0
/* 800BF2F4 000BBED4  4B F6 36 A5 */	bl lbRefract_80022998
/* 800BF2F8 000BBED8  48 00 02 28 */	b lbl_800BF520
lbl_800BF2FC:
/* 800BF2FC 000BBEDC  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 800BF300 000BBEE0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800BF304 000BBEE4  40 82 00 40 */	bne lbl_800BF344
/* 800BF308 000BBEE8  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 800BF30C 000BBEEC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF310 000BBEF0  41 82 00 10 */	beq lbl_800BF320
/* 800BF314 000BBEF4  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 800BF318 000BBEF8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF31C 000BBEFC  40 82 00 28 */	bne lbl_800BF344
lbl_800BF320:
/* 800BF320 000BBF00  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 800BF324 000BBF04  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800BF328 000BBF08  41 82 00 0C */	beq lbl_800BF334
/* 800BF32C 000BBF0C  83 6D AE E0 */	lwz r27, ft_804D6580
/* 800BF330 000BBF10  48 00 00 14 */	b lbl_800BF344
lbl_800BF334:
/* 800BF334 000BBF14  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 800BF338 000BBF18  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800BF33C 000BBF1C  41 82 00 08 */	beq lbl_800BF344
/* 800BF340 000BBF20  83 6D AE E8 */	lwz r27, ft_804D6588
lbl_800BF344:
/* 800BF344 000BBF24  48 2A 31 95 */	bl HSD_StateInitTev
/* 800BF348 000BBF28  80 7B 00 0C */	lwz r3, 0xc(r27)
/* 800BF34C 000BBF2C  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800BF350 000BBF30  83 9B 00 04 */	lwz r28, 4(r27)
/* 800BF354 000BBF34  38 81 00 20 */	addi r4, r1, 0x20
/* 800BF358 000BBF38  80 03 00 08 */	lwz r0, 8(r3)
/* 800BF35C 000BBF3C  38 61 00 24 */	addi r3, r1, 0x24
/* 800BF360 000BBF40  90 01 00 1C */	stw r0, 0x1c(r1)
/* 800BF364 000BBF44  80 DB 00 0C */	lwz r6, 0xc(r27)
/* 800BF368 000BBF48  80 06 00 04 */	lwz r0, 4(r6)
/* 800BF36C 000BBF4C  90 01 00 20 */	stw r0, 0x20(r1)
/* 800BF370 000BBF50  80 DB 00 0C */	lwz r6, 0xc(r27)
/* 800BF374 000BBF54  80 06 00 00 */	lwz r0, 0(r6)
/* 800BF378 000BBF58  90 01 00 24 */	stw r0, 0x24(r1)
/* 800BF37C 000BBF5C  80 DB 00 0C */	lwz r6, 0xc(r27)
/* 800BF380 000BBF60  C0 26 00 0C */	lfs f1, 0xc(r6)
/* 800BF384 000BBF64  48 2A 26 9D */	bl HSD_SetMaterialColor
/* 800BF388 000BBF68  57 80 07 39 */	rlwinm. r0, r28, 0, 0x1c, 0x1c
/* 800BF38C 000BBF6C  41 82 00 10 */	beq lbl_800BF39C
/* 800BF390 000BBF70  80 7B 00 0C */	lwz r3, 0xc(r27)
/* 800BF394 000BBF74  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 800BF398 000BBF78  48 2A 26 CD */	bl HSD_SetMaterialShininess
lbl_800BF39C:
/* 800BF39C 000BBF7C  80 7B 00 08 */	lwz r3, 8(r27)
/* 800BF3A0 000BBF80  57 80 01 4B */	rlwinm. r0, r28, 0, 5, 5
/* 800BF3A4 000BBF84  3B C0 00 00 */	li r30, 0
/* 800BF3A8 000BBF88  90 61 00 A0 */	stw r3, 0xa0(r1)
/* 800BF3AC 000BBF8C  41 82 00 2C */	beq lbl_800BF3D8
/* 800BF3B0 000BBF90  80 0D BF 84 */	lwz r0, tobj_shadows
/* 800BF3B4 000BBF94  28 00 00 00 */	cmplwi r0, 0
/* 800BF3B8 000BBF98  41 82 00 20 */	beq lbl_800BF3D8
/* 800BF3BC 000BBF9C  3B C1 00 A0 */	addi r30, r1, 0xa0
/* 800BF3C0 000BBFA0  48 00 00 08 */	b lbl_800BF3C8
lbl_800BF3C4:
/* 800BF3C4 000BBFA4  3B C3 00 08 */	addi r30, r3, 8
lbl_800BF3C8:
/* 800BF3C8 000BBFA8  80 7E 00 00 */	lwz r3, 0(r30)
/* 800BF3CC 000BBFAC  28 03 00 00 */	cmplwi r3, 0
/* 800BF3D0 000BBFB0  40 82 FF F4 */	bne lbl_800BF3C4
/* 800BF3D4 000BBFB4  90 1E 00 00 */	stw r0, 0(r30)
lbl_800BF3D8:
/* 800BF3D8 000BBFB8  57 80 04 E7 */	rlwinm. r0, r28, 0, 0x13, 0x13
/* 800BF3DC 000BBFBC  41 82 00 2C */	beq lbl_800BF408
/* 800BF3E0 000BBFC0  80 6D BF 80 */	lwz r3, tobj_toon
/* 800BF3E4 000BBFC4  28 03 00 00 */	cmplwi r3, 0
/* 800BF3E8 000BBFC8  41 82 00 20 */	beq lbl_800BF408
/* 800BF3EC 000BBFCC  80 03 00 58 */	lwz r0, 0x58(r3)
/* 800BF3F0 000BBFD0  28 00 00 00 */	cmplwi r0, 0
/* 800BF3F4 000BBFD4  41 82 00 14 */	beq lbl_800BF408
/* 800BF3F8 000BBFD8  80 01 00 A0 */	lwz r0, 0xa0(r1)
/* 800BF3FC 000BBFDC  90 03 00 08 */	stw r0, 8(r3)
/* 800BF400 000BBFE0  80 0D BF 80 */	lwz r0, tobj_toon
/* 800BF404 000BBFE4  90 01 00 A0 */	stw r0, 0xa0(r1)
lbl_800BF408:
/* 800BF408 000BBFE8  80 61 00 A0 */	lwz r3, 0xa0(r1)
/* 800BF40C 000BBFEC  48 2A 15 45 */	bl HSD_TObjSetup
/* 800BF410 000BBFF0  80 61 00 A0 */	lwz r3, 0xa0(r1)
/* 800BF414 000BBFF4  48 2A 00 05 */	bl HSD_TObjSetupTextureCoordGen
/* 800BF418 000BBFF8  80 DB 00 00 */	lwz r6, 0(r27)
/* 800BF41C 000BBFFC  7F 63 DB 78 */	mr r3, r27
/* 800BF420 000BC000  80 81 00 A0 */	lwz r4, 0xa0(r1)
/* 800BF424 000BC004  7F 85 E3 78 */	mr r5, r28
/* 800BF428 000BC008  81 86 00 48 */	lwz r12, 0x48(r6)
/* 800BF42C 000BC00C  7D 88 03 A6 */	mtlr r12
/* 800BF430 000BC010  4E 80 00 21 */	blrl
/* 800BF434 000BC014  88 1F 06 1D */	lbz r0, 0x61d(r31)
/* 800BF438 000BC018  28 00 00 FF */	cmplwi r0, 0xff
/* 800BF43C 000BC01C  41 82 00 08 */	beq lbl_800BF444
/* 800BF440 000BC020  67 9C 60 00 */	oris r28, r28, 0x6000
lbl_800BF444:
/* 800BF444 000BC024  38 7F 00 00 */	addi r3, r31, 0
/* 800BF448 000BC028  38 9B 00 00 */	addi r4, r27, 0
/* 800BF44C 000BC02C  38 DC 00 00 */	addi r6, r28, 0
/* 800BF450 000BC030  38 A1 00 34 */	addi r5, r1, 0x34
/* 800BF454 000BC034  48 00 00 E1 */	bl ftMaterial_800BF534
/* 800BF458 000BC038  3B A3 00 00 */	addi r29, r3, 0
/* 800BF45C 000BC03C  38 BD 00 00 */	addi r5, r29, 0
/* 800BF460 000BC040  38 7F 00 00 */	addi r3, r31, 0
/* 800BF464 000BC044  38 9B 00 00 */	addi r4, r27, 0
/* 800BF468 000BC048  48 00 02 55 */	bl ftMaterial_800BF6BC
/* 800BF46C 000BC04C  88 7F 22 23 */	lbz r3, 0x2223(r31)
/* 800BF470 000BC050  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 800BF474 000BC054  41 82 00 10 */	beq lbl_800BF484
/* 800BF478 000BC058  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 800BF47C 000BC05C  40 82 00 08 */	bne lbl_800BF484
/* 800BF480 000BC060  67 9C 20 00 */	oris r28, r28, 0x2000
lbl_800BF484:
/* 800BF484 000BC064  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 800BF488 000BC068  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800BF48C 000BC06C  41 82 00 64 */	beq lbl_800BF4F0
/* 800BF490 000BC070  88 1F 06 1D */	lbz r0, 0x61d(r31)
/* 800BF494 000BC074  28 00 00 FF */	cmplwi r0, 0xff
/* 800BF498 000BC078  40 82 00 58 */	bne lbl_800BF4F0
/* 800BF49C 000BC07C  38 00 00 38 */	li r0, 0x38
/* 800BF4A0 000BC080  98 01 00 28 */	stb r0, 0x28(r1)
/* 800BF4A4 000BC084  38 E0 00 00 */	li r7, 0
/* 800BF4A8 000BC088  38 80 00 04 */	li r4, 4
/* 800BF4AC 000BC08C  98 E1 00 2B */	stb r7, 0x2b(r1)
/* 800BF4B0 000BC090  38 C0 00 05 */	li r6, 5
/* 800BF4B4 000BC094  38 A0 00 0F */	li r5, 0xf
/* 800BF4B8 000BC098  98 E1 00 2C */	stb r7, 0x2c(r1)
/* 800BF4BC 000BC09C  38 60 00 03 */	li r3, 3
/* 800BF4C0 000BC0A0  38 00 00 07 */	li r0, 7
/* 800BF4C4 000BC0A4  98 81 00 2D */	stb r4, 0x2d(r1)
/* 800BF4C8 000BC0A8  38 81 00 28 */	addi r4, r1, 0x28
/* 800BF4CC 000BC0AC  98 C1 00 2E */	stb r6, 0x2e(r1)
/* 800BF4D0 000BC0B0  98 A1 00 2F */	stb r5, 0x2f(r1)
/* 800BF4D4 000BC0B4  98 61 00 30 */	stb r3, 0x30(r1)
/* 800BF4D8 000BC0B8  98 01 00 31 */	stb r0, 0x31(r1)
/* 800BF4DC 000BC0BC  98 E1 00 29 */	stb r7, 0x29(r1)
/* 800BF4E0 000BC0C0  98 E1 00 32 */	stb r7, 0x32(r1)
/* 800BF4E4 000BC0C4  98 01 00 33 */	stb r0, 0x33(r1)
/* 800BF4E8 000BC0C8  98 E1 00 2A */	stb r7, 0x2a(r1)
/* 800BF4EC 000BC0CC  48 00 00 08 */	b lbl_800BF4F4
lbl_800BF4F0:
/* 800BF4F0 000BC0D0  80 9B 00 10 */	lwz r4, 0x10(r27)
lbl_800BF4F4:
/* 800BF4F4 000BC0D4  7F 83 E3 78 */	mr r3, r28
/* 800BF4F8 000BC0D8  48 2A 24 15 */	bl HSD_SetupRenderModeWithCustomPE
/* 800BF4FC 000BC0DC  28 1D 00 00 */	cmplwi r29, 0
/* 800BF500 000BC0E0  40 82 00 10 */	bne lbl_800BF510
/* 800BF504 000BC0E4  38 7F 00 00 */	addi r3, r31, 0
/* 800BF508 000BC0E8  38 80 00 01 */	li r4, 1
/* 800BF50C 000BC0EC  4B FE 02 51 */	bl ftCo_8009F75C
lbl_800BF510:
/* 800BF510 000BC0F0  28 1E 00 00 */	cmplwi r30, 0
/* 800BF514 000BC0F4  41 82 00 0C */	beq lbl_800BF520
/* 800BF518 000BC0F8  38 00 00 00 */	li r0, 0
/* 800BF51C 000BC0FC  90 1E 00 00 */	stw r0, 0(r30)
lbl_800BF520:
/* 800BF520 000BC100  BB 61 00 AC */	lmw r27, 0xac(r1)
/* 800BF524 000BC104  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 800BF528 000BC108  38 21 00 C0 */	addi r1, r1, 0xc0
/* 800BF52C 000BC10C  7C 08 03 A6 */	mtlr r0
/* 800BF530 000BC110  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM HSD_TExp* ftMaterial_800BF534(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp)
#ifndef MUST_MATCH
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 800BF534 000BC114  7C 08 02 A6 */	mflr r0
/* 800BF538 000BC118  3C E0 80 3C */	lis r7, ftMObj@ha
/* 800BF53C 000BC11C  90 01 00 04 */	stw r0, 4(r1)
/* 800BF540 000BC120  94 21 FF 58 */	stwu r1, -0xa8(r1)
/* 800BF544 000BC124  BF 41 00 90 */	stmw r26, 0x90(r1)
/* 800BF548 000BC128  3B 43 00 00 */	addi r26, r3, 0
/* 800BF54C 000BC12C  3B 64 00 00 */	addi r27, r4, 0
/* 800BF550 000BC130  3B C5 00 00 */	addi r30, r5, 0
/* 800BF554 000BC134  3B 86 00 00 */	addi r28, r6, 0
/* 800BF558 000BC138  3B E7 69 80 */	addi r31, r7, ftMObj@l
/* 800BF55C 000BC13C  48 00 10 FD */	bl ftCo_800C0658
/* 800BF560 000BC140  7C 7D 1B 78 */	mr r29, r3
/* 800BF564 000BC144  88 63 00 7C */	lbz r3, 0x7c(r3)
/* 800BF568 000BC148  54 60 D7 FF */	rlwinm. r0, r3, 0x1a, 0x1f, 0x1f
/* 800BF56C 000BC14C  41 82 01 38 */	beq lbl_800BF6A4
/* 800BF570 000BC150  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 800BF574 000BC154  41 82 01 30 */	beq lbl_800BF6A4
/* 800BF578 000BC158  57 80 00 43 */	rlwinm. r0, r28, 0, 1, 1
/* 800BF57C 000BC15C  40 82 01 1C */	bne lbl_800BF698
/* 800BF580 000BC160  88 1A 22 23 */	lbz r0, 0x2223(r26)
/* 800BF584 000BC164  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800BF588 000BC168  40 82 01 10 */	bne lbl_800BF698
/* 800BF58C 000BC16C  80 DF 00 C4 */	lwz r6, 0xc4(r31)
/* 800BF590 000BC170  7F 64 DB 78 */	mr r4, r27
/* 800BF594 000BC174  80 1F 00 C8 */	lwz r0, 0xc8(r31)
/* 800BF598 000BC178  38 60 00 00 */	li r3, 0
/* 800BF59C 000BC17C  38 A0 00 00 */	li r5, 0
/* 800BF5A0 000BC180  90 DE 00 00 */	stw r6, 0(r30)
/* 800BF5A4 000BC184  90 1E 00 04 */	stw r0, 4(r30)
/* 800BF5A8 000BC188  80 DF 00 CC */	lwz r6, 0xcc(r31)
/* 800BF5AC 000BC18C  80 1F 00 D0 */	lwz r0, 0xd0(r31)
/* 800BF5B0 000BC190  90 DE 00 08 */	stw r6, 8(r30)
/* 800BF5B4 000BC194  90 1E 00 0C */	stw r0, 0xc(r30)
/* 800BF5B8 000BC198  80 DF 00 D4 */	lwz r6, 0xd4(r31)
/* 800BF5BC 000BC19C  80 1F 00 D8 */	lwz r0, 0xd8(r31)
/* 800BF5C0 000BC1A0  90 DE 00 10 */	stw r6, 0x10(r30)
/* 800BF5C4 000BC1A4  90 1E 00 14 */	stw r0, 0x14(r30)
/* 800BF5C8 000BC1A8  4B F4 D6 95 */	bl lb_8000CC5C
/* 800BF5CC 000BC1AC  3B 83 00 00 */	addi r28, r3, 0
/* 800BF5D0 000BC1B0  2C 1C FF FF */	cmpwi r28, -1
/* 800BF5D4 000BC1B4  40 82 00 20 */	bne lbl_800BF5F4
/* 800BF5D8 000BC1B8  38 7F 00 F4 */	addi r3, r31, 0xf4
/* 800BF5DC 000BC1BC  4C C6 31 82 */	crclr 6
/* 800BF5E0 000BC1C0  48 28 60 C9 */	bl OSReport
/* 800BF5E4 000BC1C4  38 7F 01 18 */	addi r3, r31, 0x118
/* 800BF5E8 000BC1C8  38 80 00 F0 */	li r4, 0xf0
/* 800BF5EC 000BC1CC  38 AD 85 68 */	addi r5, r13, ftCo_804D3C08
/* 800BF5F0 000BC1D0  48 2C 8C 31 */	bl __assert
lbl_800BF5F4:
/* 800BF5F4 000BC1D4  9B 9E 00 14 */	stb r28, 0x14(r30)
/* 800BF5F8 000BC1D8  38 1D 00 50 */	addi r0, r29, 0x50
/* 800BF5FC 000BC1DC  38 7E 00 00 */	addi r3, r30, 0
/* 800BF600 000BC1E0  90 1E 00 08 */	stw r0, 8(r30)
/* 800BF604 000BC1E4  48 2C 59 25 */	bl HSD_TExpSetReg
/* 800BF608 000BC1E8  38 00 00 0E */	li r0, 0xe
/* 800BF60C 000BC1EC  7C 09 03 A6 */	mtctr r0
/* 800BF610 000BC1F0  38 A1 00 10 */	addi r5, r1, 0x10
/* 800BF614 000BC1F4  38 9F 00 48 */	addi r4, r31, 0x48
lbl_800BF618:
/* 800BF618 000BC1F8  84 64 00 08 */	lwzu r3, 8(r4)
/* 800BF61C 000BC1FC  80 04 00 04 */	lwz r0, 4(r4)
/* 800BF620 000BC200  94 65 00 08 */	stwu r3, 8(r5)
/* 800BF624 000BC204  90 05 00 04 */	stw r0, 4(r5)
/* 800BF628 000BC208  42 00 FF F0 */	bdnz lbl_800BF618
/* 800BF62C 000BC20C  80 04 00 08 */	lwz r0, 8(r4)
/* 800BF630 000BC210  90 05 00 08 */	stw r0, 8(r5)
/* 800BF634 000BC214  48 2A 2E B9 */	bl HSD_StateAssignTev
/* 800BF638 000BC218  90 61 00 20 */	stw r3, 0x20(r1)
/* 800BF63C 000BC21C  38 60 00 02 */	li r3, 2
/* 800BF640 000BC220  38 00 00 0F */	li r0, 0xf
/* 800BF644 000BC224  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800BF648 000BC228  7F 83 E3 78 */	mr r3, r28
/* 800BF64C 000BC22C  90 01 00 34 */	stw r0, 0x34(r1)
/* 800BF650 000BC230  4B F4 D6 3D */	bl lb_8000CC8C
/* 800BF654 000BC234  90 61 00 38 */	stw r3, 0x38(r1)
/* 800BF658 000BC238  38 00 00 0B */	li r0, 0xb
/* 800BF65C 000BC23C  2C 1C 00 04 */	cmpwi r28, 4
/* 800BF660 000BC240  90 01 00 3C */	stw r0, 0x3c(r1)
/* 800BF664 000BC244  38 00 00 00 */	li r0, 0
/* 800BF668 000BC248  90 01 00 40 */	stw r0, 0x40(r1)
/* 800BF66C 000BC24C  40 80 00 08 */	bge lbl_800BF674
/* 800BF670 000BC250  38 00 00 01 */	li r0, 1
lbl_800BF674:
/* 800BF674 000BC254  2C 00 00 00 */	cmpwi r0, 0
/* 800BF678 000BC258  41 82 00 10 */	beq lbl_800BF688
/* 800BF67C 000BC25C  7F 83 E3 78 */	mr r3, r28
/* 800BF680 000BC260  4B F4 D6 25 */	bl lb_8000CCA4
/* 800BF684 000BC264  90 61 00 84 */	stw r3, 0x84(r1)
lbl_800BF688:
/* 800BF688 000BC268  38 61 00 18 */	addi r3, r1, 0x18
/* 800BF68C 000BC26C  48 2A 2E BD */	bl HSD_SetupTevStage
/* 800BF690 000BC270  7F C3 F3 78 */	mr r3, r30
/* 800BF694 000BC274  48 00 00 14 */	b lbl_800BF6A8
lbl_800BF698:
/* 800BF698 000BC278  38 7A 00 00 */	addi r3, r26, 0
/* 800BF69C 000BC27C  38 80 00 00 */	li r4, 0
/* 800BF6A0 000BC280  4B FE 00 BD */	bl ftCo_8009F75C
lbl_800BF6A4:
/* 800BF6A4 000BC284  38 60 00 00 */	li r3, 0
lbl_800BF6A8:
/* 800BF6A8 000BC288  BB 41 00 90 */	lmw r26, 0x90(r1)
/* 800BF6AC 000BC28C  80 01 00 AC */	lwz r0, 0xac(r1)
/* 800BF6B0 000BC290  38 21 00 A8 */	addi r1, r1, 0xa8
/* 800BF6B4 000BC294  7C 08 03 A6 */	mtlr r0
/* 800BF6B8 000BC298  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftMaterial_800BF6BC(Fighter* fp, HSD_MObj* mobj, HSD_TExp* texp)
#ifndef MUST_MATCH
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 800BF6BC 000BC29C  7C 08 02 A6 */	mflr r0
/* 800BF6C0 000BC2A0  90 01 00 04 */	stw r0, 4(r1)
/* 800BF6C4 000BC2A4  94 21 FE 78 */	stwu r1, -0x188(r1)
/* 800BF6C8 000BC2A8  BF 61 01 74 */	stmw r27, 0x174(r1)
/* 800BF6CC 000BC2AC  7C 7B 1B 78 */	mr r27, r3
/* 800BF6D0 000BC2B0  3B 84 00 00 */	addi r28, r4, 0
/* 800BF6D4 000BC2B4  3B A5 00 00 */	addi r29, r5, 0
/* 800BF6D8 000BC2B8  88 03 22 23 */	lbz r0, 0x2223(r3)
/* 800BF6DC 000BC2BC  3C 60 80 3C */	lis r3, ftMObj@ha
/* 800BF6E0 000BC2C0  3B E3 69 80 */	addi r31, r3, ftMObj@l
/* 800BF6E4 000BC2C4  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800BF6E8 000BC2C8  40 82 04 50 */	bne lbl_800BFB38
/* 800BF6EC 000BC2CC  7F 63 DB 78 */	mr r3, r27
/* 800BF6F0 000BC2D0  48 00 0F 69 */	bl ftCo_800C0658
/* 800BF6F4 000BC2D4  88 1B 22 28 */	lbz r0, 0x2228(r27)
/* 800BF6F8 000BC2D8  38 80 00 00 */	li r4, 0
/* 800BF6FC 000BC2DC  88 BB 06 1A */	lbz r5, 0x61a(r27)
/* 800BF700 000BC2E0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF704 000BC2E4  41 82 00 34 */	beq lbl_800BF738
/* 800BF708 000BC2E8  88 1B 22 24 */	lbz r0, 0x2224(r27)
/* 800BF70C 000BC2EC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF710 000BC2F0  41 82 00 28 */	beq lbl_800BF738
/* 800BF714 000BC2F4  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 800BF718 000BC2F8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800BF71C 000BC2FC  41 82 00 0C */	beq lbl_800BF728
/* 800BF720 000BC300  38 A0 00 04 */	li r5, 4
/* 800BF724 000BC304  48 00 00 14 */	b lbl_800BF738
lbl_800BF728:
/* 800BF728 000BC308  88 1B 22 27 */	lbz r0, 0x2227(r27)
/* 800BF72C 000BC30C  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800BF730 000BC310  41 82 00 08 */	beq lbl_800BF738
/* 800BF734 000BC314  38 A0 00 05 */	li r5, 5
lbl_800BF738:
/* 800BF738 000BC318  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 800BF73C 000BC31C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800BF740 000BC320  41 82 00 14 */	beq lbl_800BF754
/* 800BF744 000BC324  80 1B 06 14 */	lwz r0, 0x614(r27)
/* 800BF748 000BC328  38 80 00 01 */	li r4, 1
/* 800BF74C 000BC32C  90 01 01 68 */	stw r0, 0x168(r1)
/* 800BF750 000BC330  48 00 01 8C */	b lbl_800BF8DC
lbl_800BF754:
/* 800BF754 000BC334  2C 05 00 00 */	cmpwi r5, 0
/* 800BF758 000BC338  41 82 01 6C */	beq lbl_800BF8C4
/* 800BF75C 000BC33C  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 800BF760 000BC340  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF764 000BC344  41 82 01 44 */	beq lbl_800BF8A8
/* 800BF768 000BC348  88 DB 06 13 */	lbz r6, 0x613(r27)
/* 800BF76C 000BC34C  3C 80 80 81 */	lis r4, 0x80808081@ha
/* 800BF770 000BC350  88 A3 00 2F */	lbz r5, 0x2f(r3)
/* 800BF774 000BC354  38 04 80 81 */	addi r0, r4, 0x80808081@l
/* 800BF778 000BC358  20 C6 00 FF */	subfic r6, r6, 0xff
/* 800BF77C 000BC35C  20 85 00 FF */	subfic r4, r5, 0xff
/* 800BF780 000BC360  7C 86 21 D6 */	mullw r4, r6, r4
/* 800BF784 000BC364  7C A0 20 96 */	mulhw r5, r0, r4
/* 800BF788 000BC368  7C 85 22 14 */	add r4, r5, r4
/* 800BF78C 000BC36C  7C 84 3E 70 */	srawi r4, r4, 7
/* 800BF790 000BC370  54 85 0F FE */	srwi r5, r4, 0x1f
/* 800BF794 000BC374  7C C4 2A 14 */	add r6, r4, r5
/* 800BF798 000BC378  2C 06 00 FF */	cmpwi r6, 0xff
/* 800BF79C 000BC37C  38 9B 06 10 */	addi r4, r27, 0x610
/* 800BF7A0 000BC380  38 A3 00 2C */	addi r5, r3, 0x2c
/* 800BF7A4 000BC384  40 82 00 10 */	bne lbl_800BF7B4
/* 800BF7A8 000BC388  80 03 00 2C */	lwz r0, 0x2c(r3)
/* 800BF7AC 000BC38C  90 01 01 68 */	stw r0, 0x168(r1)
/* 800BF7B0 000BC390  48 00 00 F0 */	b lbl_800BF8A0
lbl_800BF7B4:
/* 800BF7B4 000BC394  20 66 00 FF */	subfic r3, r6, 0xff
/* 800BF7B8 000BC398  89 04 00 00 */	lbz r8, 0(r4)
/* 800BF7BC 000BC39C  88 C5 00 00 */	lbz r6, 0(r5)
/* 800BF7C0 000BC3A0  88 E5 00 03 */	lbz r7, 3(r5)
/* 800BF7C4 000BC3A4  7C C8 30 50 */	subf r6, r8, r6
/* 800BF7C8 000BC3A8  7C C7 31 D6 */	mullw r6, r7, r6
/* 800BF7CC 000BC3AC  7C E0 30 96 */	mulhw r7, r0, r6
/* 800BF7D0 000BC3B0  7C C7 32 14 */	add r6, r7, r6
/* 800BF7D4 000BC3B4  7C C6 3E 70 */	srawi r6, r6, 7
/* 800BF7D8 000BC3B8  54 C7 0F FE */	srwi r7, r6, 0x1f
/* 800BF7DC 000BC3BC  7C C6 3A 14 */	add r6, r6, r7
/* 800BF7E0 000BC3C0  7D 08 32 14 */	add r8, r8, r6
/* 800BF7E4 000BC3C4  1C E8 00 FF */	mulli r7, r8, 0xff
/* 800BF7E8 000BC3C8  7C C7 1B D6 */	divw r6, r7, r3
/* 800BF7EC 000BC3CC  98 C1 01 68 */	stb r6, 0x168(r1)
/* 800BF7F0 000BC3D0  88 C1 01 68 */	lbz r6, 0x168(r1)
/* 800BF7F4 000BC3D4  28 06 00 00 */	cmplwi r6, 0
/* 800BF7F8 000BC3D8  41 82 00 10 */	beq lbl_800BF808
/* 800BF7FC 000BC3DC  7C 07 33 D6 */	divw r0, r7, r6
/* 800BF800 000BC3E0  98 01 01 6B */	stb r0, 0x16b(r1)
/* 800BF804 000BC3E4  48 00 00 24 */	b lbl_800BF828
lbl_800BF808:
/* 800BF808 000BC3E8  7C C8 18 50 */	subf r6, r8, r3
/* 800BF80C 000BC3EC  1C C6 00 FF */	mulli r6, r6, 0xff
/* 800BF810 000BC3F0  7C 00 30 96 */	mulhw r0, r0, r6
/* 800BF814 000BC3F4  7C 00 32 14 */	add r0, r0, r6
/* 800BF818 000BC3F8  7C 00 3E 70 */	srawi r0, r0, 7
/* 800BF81C 000BC3FC  54 06 0F FE */	srwi r6, r0, 0x1f
/* 800BF820 000BC400  7C 00 32 14 */	add r0, r0, r6
/* 800BF824 000BC404  98 01 01 6B */	stb r0, 0x16b(r1)
lbl_800BF828:
/* 800BF828 000BC408  3C C0 80 81 */	lis r6, 0x80808081@ha
/* 800BF82C 000BC40C  89 04 00 01 */	lbz r8, 1(r4)
/* 800BF830 000BC410  88 05 00 01 */	lbz r0, 1(r5)
/* 800BF834 000BC414  38 E6 80 81 */	addi r7, r6, 0x80808081@l
/* 800BF838 000BC418  88 C5 00 03 */	lbz r6, 3(r5)
/* 800BF83C 000BC41C  7C 08 00 50 */	subf r0, r8, r0
/* 800BF840 000BC420  7C 06 01 D6 */	mullw r0, r6, r0
/* 800BF844 000BC424  7C C7 00 96 */	mulhw r6, r7, r0
/* 800BF848 000BC428  7C 06 02 14 */	add r0, r6, r0
/* 800BF84C 000BC42C  7C 00 3E 70 */	srawi r0, r0, 7
/* 800BF850 000BC430  54 06 0F FE */	srwi r6, r0, 0x1f
/* 800BF854 000BC434  7C 00 32 14 */	add r0, r0, r6
/* 800BF858 000BC438  7C 08 02 14 */	add r0, r8, r0
/* 800BF85C 000BC43C  1C 00 00 FF */	mulli r0, r0, 0xff
/* 800BF860 000BC440  7C 00 1B D6 */	divw r0, r0, r3
/* 800BF864 000BC444  98 01 01 69 */	stb r0, 0x169(r1)
/* 800BF868 000BC448  88 C4 00 02 */	lbz r6, 2(r4)
/* 800BF86C 000BC44C  88 05 00 02 */	lbz r0, 2(r5)
/* 800BF870 000BC450  88 85 00 03 */	lbz r4, 3(r5)
/* 800BF874 000BC454  7C 06 00 50 */	subf r0, r6, r0
/* 800BF878 000BC458  7C 04 01 D6 */	mullw r0, r4, r0
/* 800BF87C 000BC45C  7C 87 00 96 */	mulhw r4, r7, r0
/* 800BF880 000BC460  7C 04 02 14 */	add r0, r4, r0
/* 800BF884 000BC464  7C 00 3E 70 */	srawi r0, r0, 7
/* 800BF888 000BC468  54 04 0F FE */	srwi r4, r0, 0x1f
/* 800BF88C 000BC46C  7C 00 22 14 */	add r0, r0, r4
/* 800BF890 000BC470  7C 06 02 14 */	add r0, r6, r0
/* 800BF894 000BC474  1C 00 00 FF */	mulli r0, r0, 0xff
/* 800BF898 000BC478  7C 00 1B D6 */	divw r0, r0, r3
/* 800BF89C 000BC47C  98 01 01 6A */	stb r0, 0x16a(r1)
lbl_800BF8A0:
/* 800BF8A0 000BC480  38 80 00 01 */	li r4, 1
/* 800BF8A4 000BC484  48 00 00 38 */	b lbl_800BF8DC
lbl_800BF8A8:
/* 800BF8A8 000BC488  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 800BF8AC 000BC48C  54 A0 10 3A */	slwi r0, r5, 2
/* 800BF8B0 000BC490  38 80 00 01 */	li r4, 1
/* 800BF8B4 000BC494  7C 63 02 14 */	add r3, r3, r0
/* 800BF8B8 000BC498  80 03 06 D8 */	lwz r0, 0x6d8(r3)
/* 800BF8BC 000BC49C  90 01 01 68 */	stw r0, 0x168(r1)
/* 800BF8C0 000BC4A0  48 00 00 1C */	b lbl_800BF8DC
lbl_800BF8C4:
/* 800BF8C4 000BC4A4  88 03 00 7C */	lbz r0, 0x7c(r3)
/* 800BF8C8 000BC4A8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800BF8CC 000BC4AC  41 82 00 10 */	beq lbl_800BF8DC
/* 800BF8D0 000BC4B0  80 03 00 2C */	lwz r0, 0x2c(r3)
/* 800BF8D4 000BC4B4  38 80 00 01 */	li r4, 1
/* 800BF8D8 000BC4B8  90 01 01 68 */	stw r0, 0x168(r1)
lbl_800BF8DC:
/* 800BF8DC 000BC4BC  2C 04 00 00 */	cmpwi r4, 0
/* 800BF8E0 000BC4C0  41 82 02 58 */	beq lbl_800BFB38
/* 800BF8E4 000BC4C4  80 DF 00 C4 */	lwz r6, 0xc4(r31)
/* 800BF8E8 000BC4C8  7F 84 E3 78 */	mr r4, r28
/* 800BF8EC 000BC4CC  80 1F 00 C8 */	lwz r0, 0xc8(r31)
/* 800BF8F0 000BC4D0  38 BD 00 00 */	addi r5, r29, 0
/* 800BF8F4 000BC4D4  38 60 00 00 */	li r3, 0
/* 800BF8F8 000BC4D8  90 C1 00 FC */	stw r6, 0xfc(r1)
/* 800BF8FC 000BC4DC  90 01 01 00 */	stw r0, 0x100(r1)
/* 800BF900 000BC4E0  80 DF 00 CC */	lwz r6, 0xcc(r31)
/* 800BF904 000BC4E4  80 1F 00 D0 */	lwz r0, 0xd0(r31)
/* 800BF908 000BC4E8  90 C1 01 04 */	stw r6, 0x104(r1)
/* 800BF90C 000BC4EC  90 01 01 08 */	stw r0, 0x108(r1)
/* 800BF910 000BC4F0  80 DF 00 D4 */	lwz r6, 0xd4(r31)
/* 800BF914 000BC4F4  80 1F 00 D8 */	lwz r0, 0xd8(r31)
/* 800BF918 000BC4F8  90 C1 01 0C */	stw r6, 0x10c(r1)
/* 800BF91C 000BC4FC  90 01 01 10 */	stw r0, 0x110(r1)
/* 800BF920 000BC500  4B F4 D3 3D */	bl lb_8000CC5C
/* 800BF924 000BC504  3B C3 00 00 */	addi r30, r3, 0
/* 800BF928 000BC508  2C 1E FF FF */	cmpwi r30, -1
/* 800BF92C 000BC50C  40 82 00 20 */	bne lbl_800BF94C
/* 800BF930 000BC510  38 7F 00 F4 */	addi r3, r31, 0xf4
/* 800BF934 000BC514  4C C6 31 82 */	crclr 6
/* 800BF938 000BC518  48 28 5D 71 */	bl OSReport
/* 800BF93C 000BC51C  38 7F 01 18 */	addi r3, r31, 0x118
/* 800BF940 000BC520  38 80 01 60 */	li r4, 0x160
/* 800BF944 000BC524  38 AD 85 68 */	addi r5, r13, ftCo_804D3C08
/* 800BF948 000BC528  48 2C 88 D9 */	bl __assert
lbl_800BF94C:
/* 800BF94C 000BC52C  9B C1 01 10 */	stb r30, 0x110(r1)
/* 800BF950 000BC530  38 01 01 68 */	addi r0, r1, 0x168
/* 800BF954 000BC534  38 61 00 FC */	addi r3, r1, 0xfc
/* 800BF958 000BC538  90 01 01 04 */	stw r0, 0x104(r1)
/* 800BF95C 000BC53C  48 2C 55 CD */	bl HSD_TExpSetReg
/* 800BF960 000BC540  2C 1E 00 04 */	cmpwi r30, 4
/* 800BF964 000BC544  93 A1 01 00 */	stw r29, 0x100(r1)
/* 800BF968 000BC548  40 80 00 0C */	bge lbl_800BF974
/* 800BF96C 000BC54C  38 00 00 01 */	li r0, 1
/* 800BF970 000BC550  48 00 00 08 */	b lbl_800BF978
lbl_800BF974:
/* 800BF974 000BC554  38 00 00 00 */	li r0, 0
lbl_800BF978:
/* 800BF978 000BC558  2C 00 00 00 */	cmpwi r0, 0
/* 800BF97C 000BC55C  41 82 00 0C */	beq lbl_800BF988
/* 800BF980 000BC560  38 60 00 04 */	li r3, 4
/* 800BF984 000BC564  48 00 00 08 */	b lbl_800BF98C
lbl_800BF988:
/* 800BF988 000BC568  38 60 00 00 */	li r3, 0
lbl_800BF98C:
/* 800BF98C 000BC56C  38 9C 00 00 */	addi r4, r28, 0
/* 800BF990 000BC570  38 A1 00 FC */	addi r5, r1, 0xfc
/* 800BF994 000BC574  4B F4 D2 C9 */	bl lb_8000CC5C
/* 800BF998 000BC578  3B A3 00 00 */	addi r29, r3, 0
/* 800BF99C 000BC57C  2C 1D FF FF */	cmpwi r29, -1
/* 800BF9A0 000BC580  40 82 00 20 */	bne lbl_800BF9C0
/* 800BF9A4 000BC584  38 7F 01 28 */	addi r3, r31, 0x128
/* 800BF9A8 000BC588  4C C6 31 82 */	crclr 6
/* 800BF9AC 000BC58C  48 28 5C FD */	bl OSReport
/* 800BF9B0 000BC590  38 7F 01 18 */	addi r3, r31, 0x118
/* 800BF9B4 000BC594  38 80 01 6E */	li r4, 0x16e
/* 800BF9B8 000BC598  38 AD 85 68 */	addi r5, r13, ftCo_804D3C08
/* 800BF9BC 000BC59C  48 2C 88 65 */	bl __assert
lbl_800BF9C0:
/* 800BF9C0 000BC5A0  88 1B 06 1D */	lbz r0, 0x61d(r27)
/* 800BF9C4 000BC5A4  28 00 00 FF */	cmplwi r0, 0xff
/* 800BF9C8 000BC5A8  41 82 00 5C */	beq lbl_800BFA24
/* 800BF9CC 000BC5AC  80 1F 00 C4 */	lwz r0, 0xc4(r31)
/* 800BF9D0 000BC5B0  38 A0 00 05 */	li r5, 5
/* 800BF9D4 000BC5B4  80 DF 00 C8 */	lwz r6, 0xc8(r31)
/* 800BF9D8 000BC5B8  38 80 00 03 */	li r4, 3
/* 800BF9DC 000BC5BC  38 7B 06 1D */	addi r3, r27, 0x61d
/* 800BF9E0 000BC5C0  90 01 00 90 */	stw r0, 0x90(r1)
/* 800BF9E4 000BC5C4  38 01 00 90 */	addi r0, r1, 0x90
/* 800BF9E8 000BC5C8  90 C1 00 94 */	stw r6, 0x94(r1)
/* 800BF9EC 000BC5CC  80 FF 00 CC */	lwz r7, 0xcc(r31)
/* 800BF9F0 000BC5D0  80 DF 00 D0 */	lwz r6, 0xd0(r31)
/* 800BF9F4 000BC5D4  90 E1 00 98 */	stw r7, 0x98(r1)
/* 800BF9F8 000BC5D8  90 C1 00 9C */	stw r6, 0x9c(r1)
/* 800BF9FC 000BC5DC  80 FF 00 D4 */	lwz r7, 0xd4(r31)
/* 800BFA00 000BC5E0  80 DF 00 D8 */	lwz r6, 0xd8(r31)
/* 800BFA04 000BC5E4  90 E1 00 A0 */	stw r7, 0xa0(r1)
/* 800BFA08 000BC5E8  90 C1 00 A4 */	stw r6, 0xa4(r1)
/* 800BFA0C 000BC5EC  9B A1 00 A4 */	stb r29, 0xa4(r1)
/* 800BFA10 000BC5F0  90 A1 00 9C */	stw r5, 0x9c(r1)
/* 800BFA14 000BC5F4  98 81 00 A5 */	stb r4, 0xa5(r1)
/* 800BFA18 000BC5F8  90 61 00 98 */	stw r3, 0x98(r1)
/* 800BFA1C 000BC5FC  90 01 01 00 */	stw r0, 0x100(r1)
/* 800BFA20 000BC600  48 00 00 0C */	b lbl_800BFA2C
lbl_800BFA24:
/* 800BFA24 000BC604  38 00 00 00 */	li r0, 0
/* 800BFA28 000BC608  90 01 01 00 */	stw r0, 0x100(r1)
lbl_800BFA2C:
/* 800BFA2C 000BC60C  9B A1 01 10 */	stb r29, 0x110(r1)
/* 800BFA30 000BC610  38 01 00 18 */	addi r0, r1, 0x18
/* 800BFA34 000BC614  38 61 00 FC */	addi r3, r1, 0xfc
/* 800BFA38 000BC618  88 81 01 6B */	lbz r4, 0x16b(r1)
/* 800BFA3C 000BC61C  98 81 00 18 */	stb r4, 0x18(r1)
/* 800BFA40 000BC620  98 81 00 19 */	stb r4, 0x19(r1)
/* 800BFA44 000BC624  98 81 00 1A */	stb r4, 0x1a(r1)
/* 800BFA48 000BC628  90 01 01 04 */	stw r0, 0x104(r1)
/* 800BFA4C 000BC62C  48 2C 54 DD */	bl HSD_TExpSetReg
/* 800BFA50 000BC630  38 00 00 0E */	li r0, 0xe
/* 800BFA54 000BC634  7C 09 03 A6 */	mtctr r0
/* 800BFA58 000BC638  38 A1 00 14 */	addi r5, r1, 0x14
/* 800BFA5C 000BC63C  38 9F 00 48 */	addi r4, r31, 0x48
lbl_800BFA60:
/* 800BFA60 000BC640  84 64 00 08 */	lwzu r3, 8(r4)
/* 800BFA64 000BC644  80 04 00 04 */	lwz r0, 4(r4)
/* 800BFA68 000BC648  94 65 00 08 */	stwu r3, 8(r5)
/* 800BFA6C 000BC64C  90 05 00 04 */	stw r0, 4(r5)
/* 800BFA70 000BC650  42 00 FF F0 */	bdnz lbl_800BFA60
/* 800BFA74 000BC654  80 04 00 08 */	lwz r0, 8(r4)
/* 800BFA78 000BC658  90 05 00 08 */	stw r0, 8(r5)
/* 800BFA7C 000BC65C  48 2A 2A 71 */	bl HSD_StateAssignTev
/* 800BFA80 000BC660  90 61 00 24 */	stw r3, 0x24(r1)
/* 800BFA84 000BC664  7F C3 F3 78 */	mr r3, r30
/* 800BFA88 000BC668  4B F4 D2 05 */	bl lb_8000CC8C
/* 800BFA8C 000BC66C  90 61 00 3C */	stw r3, 0x3c(r1)
/* 800BFA90 000BC670  7F A3 EB 78 */	mr r3, r29
/* 800BFA94 000BC674  4B F4 D1 F9 */	bl lb_8000CC8C
/* 800BFA98 000BC678  2C 1E 00 04 */	cmpwi r30, 4
/* 800BFA9C 000BC67C  90 61 00 40 */	stw r3, 0x40(r1)
/* 800BFAA0 000BC680  40 80 00 0C */	bge lbl_800BFAAC
/* 800BFAA4 000BC684  38 00 00 01 */	li r0, 1
/* 800BFAA8 000BC688  48 00 00 08 */	b lbl_800BFAB0
lbl_800BFAAC:
/* 800BFAAC 000BC68C  38 00 00 00 */	li r0, 0
lbl_800BFAB0:
/* 800BFAB0 000BC690  2C 00 00 00 */	cmpwi r0, 0
/* 800BFAB4 000BC694  41 82 00 14 */	beq lbl_800BFAC8
/* 800BFAB8 000BC698  7F C3 F3 78 */	mr r3, r30
/* 800BFABC 000BC69C  4B F4 D1 E9 */	bl lb_8000CCA4
/* 800BFAC0 000BC6A0  90 61 00 88 */	stw r3, 0x88(r1)
/* 800BFAC4 000BC6A4  48 00 00 2C */	b lbl_800BFAF0
lbl_800BFAC8:
/* 800BFAC8 000BC6A8  2C 1D 00 04 */	cmpwi r29, 4
/* 800BFACC 000BC6AC  40 80 00 0C */	bge lbl_800BFAD8
/* 800BFAD0 000BC6B0  38 00 00 01 */	li r0, 1
/* 800BFAD4 000BC6B4  48 00 00 08 */	b lbl_800BFADC
lbl_800BFAD8:
/* 800BFAD8 000BC6B8  38 00 00 00 */	li r0, 0
lbl_800BFADC:
/* 800BFADC 000BC6BC  2C 00 00 00 */	cmpwi r0, 0
/* 800BFAE0 000BC6C0  41 82 00 10 */	beq lbl_800BFAF0
/* 800BFAE4 000BC6C4  7F A3 EB 78 */	mr r3, r29
/* 800BFAE8 000BC6C8  4B F4 D1 BD */	bl lb_8000CCA4
/* 800BFAEC 000BC6CC  90 61 00 88 */	stw r3, 0x88(r1)
lbl_800BFAF0:
/* 800BFAF0 000BC6D0  88 1B 06 1D */	lbz r0, 0x61d(r27)
/* 800BFAF4 000BC6D4  28 00 00 FF */	cmplwi r0, 0xff
/* 800BFAF8 000BC6D8  41 82 00 38 */	beq lbl_800BFB30
/* 800BFAFC 000BC6DC  7F A3 EB 78 */	mr r3, r29
/* 800BFB00 000BC6E0  4B F4 D2 91 */	bl lb_8000CD90
/* 800BFB04 000BC6E4  2C 1D 00 04 */	cmpwi r29, 4
/* 800BFB08 000BC6E8  90 61 00 68 */	stw r3, 0x68(r1)
/* 800BFB0C 000BC6EC  40 80 00 0C */	bge lbl_800BFB18
/* 800BFB10 000BC6F0  38 00 00 01 */	li r0, 1
/* 800BFB14 000BC6F4  48 00 00 08 */	b lbl_800BFB1C
lbl_800BFB18:
/* 800BFB18 000BC6F8  38 00 00 00 */	li r0, 0
lbl_800BFB1C:
/* 800BFB1C 000BC6FC  2C 00 00 00 */	cmpwi r0, 0
/* 800BFB20 000BC700  41 82 00 10 */	beq lbl_800BFB30
/* 800BFB24 000BC704  7F A3 EB 78 */	mr r3, r29
/* 800BFB28 000BC708  4B F4 D2 81 */	bl lb_8000CDA8
/* 800BFB2C 000BC70C  90 61 00 8C */	stw r3, 0x8c(r1)
lbl_800BFB30:
/* 800BFB30 000BC710  38 61 00 1C */	addi r3, r1, 0x1c
/* 800BFB34 000BC714  48 2A 2A 15 */	bl HSD_SetupTevStage
lbl_800BFB38:
/* 800BFB38 000BC718  BB 61 01 74 */	lmw r27, 0x174(r1)
/* 800BFB3C 000BC71C  80 01 01 8C */	lwz r0, 0x18c(r1)
/* 800BFB40 000BC720  38 21 01 88 */	addi r1, r1, 0x188
/* 800BFB44 000BC724  7C 08 03 A6 */	mtlr r0
/* 800BFB48 000BC728  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftMaterial_800BFB4C(ftCo_GObj* gobj, GXColor* diffuse)
{
    HSD_JObj* cur = GET_JOBJ(gobj);

    while (cur != NULL) {
        HSD_DObj* dobj = HSD_JObjGetDObj(cur);
        while (dobj != NULL) {
            HSD_MObj* mobj = dobj != NULL ? dobj->mobj : NULL;
            if (mobj != NULL) {
                if (mobj->mat != NULL) {
                    HSD_Material* mat = mobj->mat;
                    mat->diffuse = *diffuse;
                }
            }
            dobj = dobj != NULL ? dobj->next : NULL;
        }
        if (!(HSD_JObjGetFlags(cur) & JOBJ_INSTANCE)) {
            HSD_JObj* child;
            if (cur == NULL) {
                child = NULL;
            } else {
                child = cur->child;
            }
            if (child != NULL) {
                HSD_JObj* child;
                if (cur == NULL) {
                    child = NULL;
                } else {
                    child = cur->child;
                }
                cur = child;
                continue;
            }
        }
        {
            HSD_JObj* next;
            if (cur == NULL) {
                next = NULL;
            } else {
                next = cur->next;
            }
            if (next != NULL) {
                HSD_JObj* next;
                if (cur == NULL) {
                    next = NULL;
                } else {
                    next = cur->next;
                }
                cur = next;
            } else {
                while (true) {
                    HSD_JObj* parent;
                    if (cur == NULL) {
                        parent = NULL;
                    } else {
                        parent = cur->parent;
                    }
                    if (parent == NULL) {
                        cur = NULL;
                    } else {
                        HSD_JObj* parent;
                        if (cur == NULL) {
                            parent = NULL;
                        } else {
                            parent = cur->parent;
                        }
                        {
                            HSD_JObj* next;
                            if (parent == NULL) {
                                next = NULL;
                            } else {
                                next = parent->next;
                            }
                            if (next != NULL) {
                                HSD_JObj* parent;
                                if (cur == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = cur->parent;
                                }
                                {
                                    HSD_JObj* next;
                                    if (parent == NULL) {
                                        next = NULL;
                                    } else {
                                        next = parent->next;
                                    }
                                    cur = next;
                                }
                            } else {
                                HSD_JObj* parent;
                                if (cur == NULL) {
                                    parent = NULL;
                                } else {
                                    parent = cur->parent;
                                }
                                cur = parent;
                                continue;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
}

void ftMaterial_800BFD04(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Sleep, Ft_MF_None, 0, 1, 0, NULL);
    fp->x221E_b0 = true;
    fp->x221E_b1 = true;
    fp->x221E_b2 = true;
    fp->x2219_b1 = true;
    fp->x890_cameraBox->x8 = true;
    fp->x221F_b3 = true;
    fp->x221F_b1 = true;
}

void ftMaterial_800BFD9C(ftCo_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMaterial_800BFD04(gobj);
    if (fp->x2222_b5) {
        HSD_GObj* pl_gobj = Player_GetEntityAtIndex(fp->player_id, 1);
        if (pl_gobj != NULL) {
            ftCo_800D4F24(pl_gobj, 1);
        }
    }
    gm_80167320(fp->player_id, fp->x221F_b4);
}
