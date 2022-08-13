#include <sysdolphin/baselib/cobj.h>

extern f64 lbl_804DE468; // 0.5
extern f32 lbl_804DE470; // 0.5f
extern f32 lbl_804DE474; // 0.01745329252f

#define DegToRad(a)   ( (a) *  0.01745329252f )

// Only NON_MATCHING because there's a swapped lfs operation if using extern on the float constants
#ifdef NON_MATCHING
void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha, s32 enable_depth)
{
    f32 m_val, z_val, left_res, right_res, top_res, bottom_res;

    if (cobj != NULL && ((enable_color != 0 || enable_alpha != 0 || enable_depth == 0))){
        z_val = (0.5 * (HSD_CObjGetNear(cobj) + HSD_CObjGetFar(cobj)));

        switch (HSD_CObjGetProjectionType(cobj))
        {
            case PROJ_PERSPECTIVE:
                top_res = (z_val * tanf(0.5f * DegToRad(cobj->projection_param.perspective.fov)));
                bottom_res = -top_res;
                right_res = top_res * cobj->projection_param.perspective.aspect;
                left_res = -right_res;
                break;
            case PROJ_FRUSTRUM:
                m_val = z_val / HSD_CObjGetNear(cobj);
                right_res = m_val * cobj->projection_param.frustrum.right;
                left_res = m_val * cobj->projection_param.frustrum.left;
                top_res = m_val * cobj->projection_param.frustrum.top;
                bottom_res = m_val * cobj->projection_param.frustrum.bottom;
                break;
            case PROJ_ORTHO:
                right_res = cobj->projection_param.ortho.right;
                left_res = cobj->projection_param.ortho.left;
                top_res = cobj->projection_param.ortho.top;
                bottom_res = cobj->projection_param.ortho.bottom;
                break;
        }

        HSD_EraseRect(top_res, bottom_res, left_res, right_res, -z_val, enable_color, enable_alpha, enable_depth);
    }
}
#else
asm void HSD_CObjEraseScreen(HSD_CObj* cobj, s32 enable_color, s32 enable_alpha, s32 enable_depth)
{
    nofralloc
/* 803676F8 003642D8  7C 08 02 A6 */	mflr r0
/* 803676FC 003642DC  90 01 00 04 */	stw r0, 4(r1)
/* 80367700 003642E0  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 80367704 003642E4  DB E1 00 48 */	stfd f31, 0x48(r1)
/* 80367708 003642E8  DB C1 00 40 */	stfd f30, 0x40(r1)
/* 8036770C 003642EC  DB A1 00 38 */	stfd f29, 0x38(r1)
/* 80367710 003642F0  DB 81 00 30 */	stfd f28, 0x30(r1)
/* 80367714 003642F4  DB 61 00 28 */	stfd f27, 0x28(r1)
/* 80367718 003642F8  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8036771C 003642FC  3B E6 00 00 */	addi r31, r6, 0
/* 80367720 00364300  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80367724 00364304  3B C5 00 00 */	addi r30, r5, 0
/* 80367728 00364308  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 8036772C 0036430C  3B A4 00 00 */	addi r29, r4, 0
/* 80367730 00364310  93 81 00 18 */	stw r28, 0x18(r1)
/* 80367734 00364314  7C 7C 1B 79 */	or. r28, r3, r3
/* 80367738 00364318  41 82 01 08 */	beq lbl_80367840
/* 8036773C 0036431C  2C 1D 00 00 */	cmpwi r29, 0
/* 80367740 00364320  40 82 00 18 */	bne lbl_80367758
/* 80367744 00364324  2C 1E 00 00 */	cmpwi r30, 0
/* 80367748 00364328  40 82 00 10 */	bne lbl_80367758
/* 8036774C 0036432C  2C 1F 00 00 */	cmpwi r31, 0
/* 80367750 00364330  40 82 00 08 */	bne lbl_80367758
/* 80367754 00364334  48 00 00 EC */	b lbl_80367840
lbl_80367758:
/* 80367758 00364338  7F 83 E3 78 */	mr r3, r28
/* 8036775C 0036433C  48 00 28 55 */	bl HSD_CObjGetFar
/* 80367760 00364340  FF E0 08 90 */	fmr f31, f1
/* 80367764 00364344  7F 83 E3 78 */	mr r3, r28
/* 80367768 00364348  48 00 28 21 */	bl HSD_CObjGetNear
/* 8036776C 0036434C  EC 21 F8 2A */	fadds f1, f1, f31
/* 80367770 00364350  C8 02 EA 88 */	lfd f0, lbl_804DE468(r2)
/* 80367774 00364354  7F 83 E3 78 */	mr r3, r28
/* 80367778 00364358  FF E0 00 72 */	fmul f31, f0, f1
/* 8036777C 0036435C  FF E0 F8 18 */	frsp f31, f31
/* 80367780 00364360  48 00 29 AD */	bl HSD_CObjGetProjectionType
/* 80367784 00364364  2C 03 00 02 */	cmpwi r3, 2
/* 80367788 00364368  41 82 00 54 */	beq lbl_803677DC
/* 8036778C 0036436C  40 80 00 10 */	bge lbl_8036779C
/* 80367790 00364370  2C 03 00 01 */	cmpwi r3, 1
/* 80367794 00364374  40 80 00 14 */	bge lbl_803677A8
/* 80367798 00364378  48 00 00 84 */	b lbl_8036781C
lbl_8036779C:
/* 8036779C 0036437C  2C 03 00 04 */	cmpwi r3, 4
/* 803677A0 00364380  40 80 00 7C */	bge lbl_8036781C
/* 803677A4 00364384  48 00 00 68 */	b lbl_8036780C
lbl_803677A8:
/* 803677A8 00364388  C0 22 EA 94 */	lfs f1, lbl_804DE474(r2)
/* 803677AC 0036438C  C0 1C 00 40 */	lfs f0, 0x40(r28)
/* 803677B0 00364390  C0 42 EA 90 */	lfs f2, lbl_804DE470(r2)
/* 803677B4 00364394  EC 01 00 32 */	fmuls f0, f1, f0
/* 803677B8 00364398  EC 22 00 32 */	fmuls f1, f2, f0
/* 803677BC 0036439C  4B FB EA 01 */	bl tanf
/* 803677C0 003643A0  EF 9F 00 72 */	fmuls f28, f31, f1
/* 803677C4 003643A4  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 803677C8 003643A8  EC 1C 00 32 */	fmuls f0, f28, f0
/* 803677CC 003643AC  FF 60 E0 50 */	fneg f27, f28
/* 803677D0 003643B0  FF A0 00 90 */	fmr f29, f0
/* 803677D4 003643B4  FF C0 00 50 */	fneg f30, f0
/* 803677D8 003643B8  48 00 00 44 */	b lbl_8036781C
lbl_803677DC:
/* 803677DC 003643BC  7F 83 E3 78 */	mr r3, r28
/* 803677E0 003643C0  48 00 27 A9 */	bl HSD_CObjGetNear
/* 803677E4 003643C4  EC 9F 08 24 */	fdivs f4, f31, f1
/* 803677E8 003643C8  C0 7C 00 4C */	lfs f3, 0x4c(r28)
/* 803677EC 003643CC  C0 5C 00 48 */	lfs f2, 0x48(r28)
/* 803677F0 003643D0  C0 3C 00 40 */	lfs f1, 0x40(r28)
/* 803677F4 003643D4  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 803677F8 003643D8  EF A4 00 F2 */	fmuls f29, f4, f3
/* 803677FC 003643DC  EF C4 00 B2 */	fmuls f30, f4, f2
/* 80367800 003643E0  EF 84 00 72 */	fmuls f28, f4, f1
/* 80367804 003643E4  EF 64 00 32 */	fmuls f27, f4, f0
/* 80367808 003643E8  48 00 00 14 */	b lbl_8036781C
lbl_8036780C:
/* 8036780C 003643EC  C3 BC 00 4C */	lfs f29, 0x4c(r28)
/* 80367810 003643F0  C3 DC 00 48 */	lfs f30, 0x48(r28)
/* 80367814 003643F4  C3 9C 00 40 */	lfs f28, 0x40(r28)
/* 80367818 003643F8  C3 7C 00 44 */	lfs f27, 0x44(r28)
lbl_8036781C:
/* 8036781C 003643FC  FC 20 E0 90 */	fmr f1, f28
/* 80367820 00364400  7F A3 EB 78 */	mr r3, r29
/* 80367824 00364404  FC 40 D8 90 */	fmr f2, f27
/* 80367828 00364408  7F C4 F3 78 */	mr r4, r30
/* 8036782C 0036440C  FC 60 F0 90 */	fmr f3, f30
/* 80367830 00364410  FC 80 E8 90 */	fmr f4, f29
/* 80367834 00364414  7F E5 FB 78 */	mr r5, r31
/* 80367838 00364418  FC A0 F8 50 */	fneg f5, f31
/* 8036783C 0036441C  48 00 D2 65 */	bl HSD_EraseRect
lbl_80367840:
/* 80367840 00364420  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80367844 00364424  CB E1 00 48 */	lfd f31, 0x48(r1)
/* 80367848 00364428  CB C1 00 40 */	lfd f30, 0x40(r1)
/* 8036784C 0036442C  CB A1 00 38 */	lfd f29, 0x38(r1)
/* 80367850 00364430  CB 81 00 30 */	lfd f28, 0x30(r1)
/* 80367854 00364434  CB 61 00 28 */	lfd f27, 0x28(r1)
/* 80367858 00364438  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8036785C 0036443C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80367860 00364440  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80367864 00364444  83 81 00 18 */	lwz r28, 0x18(r1)
/* 80367868 00364448  38 21 00 50 */	addi r1, r1, 0x50
/* 8036786C 0036444C  7C 08 03 A6 */	mtlr r0
/* 80367870 00364450  4E 80 00 20 */	blr 
}
#endif

#pragma push 
#pragma peephole on
void HSD_CObjRemoveAnimByFlags(HSD_CObj* cobj, u32 flags)
{
    HSD_WObj* wobj;
    
    if (cobj == NULL) {
        return;
    }

    HSD_AObjRemove(cobj->aobj);
    cobj->aobj = NULL;
    wobj = HSD_CObjGetEyePositionWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
    wobj = HSD_CObjGetInterestWObj(cobj);
    HSD_WObjRemoveAnim(wobj);
}

void HSD_CObjRemoveAnim(HSD_CObj* cobj) 
{    
    if (cobj == NULL) {
        return;
    }

    HSD_CObjRemoveAnimByFlags(cobj, 0x7FF);
}
#pragma pop
