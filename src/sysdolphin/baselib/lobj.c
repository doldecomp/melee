#include <sysdolphin/baselib/lobj.h>
#include <dolphin/mtx.h>

void LObjInfoInit(void);

HSD_LObjInfo hsdLObj = {LObjInfoInit};

extern s32 lightmask_diffuse;
extern s32 lightmask_attnfunc;
extern s32 lightmask_alpha;
extern s32 lightmask_specular;

extern s32 nb_active_lights;

HSD_LObj *active_lights[GX_MAX_LIGHT];

u32 HSD_LObjGetFlags(HSD_LObj *lobj)
{
    return (lobj) ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj *lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj *lobj, u32 flags)
{
    if (lobj == NULL)
        return;
    lobj->flags &= ~flags;
}

s32 HSD_LObjGetLightMaskDiffuse(void)
{
    return lightmask_diffuse;
}

s32 HSD_LObjGetLightMaskAttnFunc(void)
{
    return lightmask_attnfunc;
}

s32 HSD_LObjGetLightMaskAlpha(void)
{
    return lightmask_alpha;
}

s32 HSD_LObjGetLightMaskSpecular(void)
{
    return lightmask_specular;
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj *HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < GX_MAX_LIGHT)
    {
        return active_lights[idx];
    }
    else
    {
        return NULL;
    }
}

HSD_LObj *HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < GX_MAX_LIGHT - 1)
    {
        return active_lights[idx];
    }
    else
    {
        return NULL;
    }
}

/*static*/ void LObjUpdateFunc(void *obj, u32 type, FObjData *val)
{
    HSD_LObj *lobj = obj;

    if (lobj == NULL)
        return;

    switch (type)
    {
    case HSD_A_L_VIS:
        if (val->fv < 0.5)
        {
            lobj->flags &= ~LOBJ_HIDDEN;
        }
        else
        {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.a0 = val->fv;
        }
        else
        {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.a1 = val->fv;
        }
        else
        {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.a2 = val->fv;
        }
        else
        {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM)
        {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = (u8)(255.0 * val->fv);
        break;
    }
}

void HSD_LObjAnim(HSD_LObj *lobj)
{
    if (lobj != NULL)
    {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, &LObjUpdateFunc);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

void HSD_LObjAnimAll(HSD_LObj *lobj)
{
    HSD_LObj *lp;

    if (lobj == NULL)
    {
        return;
    }

    for (lp = lobj; lp; lp = lp->next)
    {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjReqAnim(HSD_LObj *lobj, f32 startframe)
{
    if (lobj == NULL)
    {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjReqAnimAll(HSD_LObj *lobj, f32 startframe)
{
    HSD_LObj *lp;

    if (lobj == NULL)
    {
        return;
    }

    for (lp = lobj; lp; lp = lp->next)
    {
        HSD_LObjReqAnim(lp, startframe);
    }
}

Vec const position = {0.0F, 0.0F, 0.0F};
Vec const interest = {0.0F, 0.0F, 0.0F};

#ifdef NON_MATCHING

void HSD_LObjGetLightVector(HSD_LObj *lobj, VecPtr dir)
{
    if (lobj == NULL)
        return;

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    PSVECNormalize(dir, dir);
}

#else

#pragma push
asm void HSD_LObjGetLightVector()
{ // clang-format off
    nofralloc
/* 80365778 00362358  7C 08 02 A6 */	mflr r0
/* 8036577C 0036235C  3C A0 80 3C */	lis r5, position@ha
/* 80365780 00362360  90 01 00 04 */	stw r0, 4(r1)
/* 80365784 00362364  38 E5 94 A0 */	addi r7, r5, position@l
/* 80365788 00362368  3C A0 80 3C */	lis r5, interest@ha
/* 8036578C 0036236C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80365790 00362370  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80365794 00362374  7C 9F 23 78 */	mr r31, r4
/* 80365798 00362378  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8036579C 0036237C  7C 7E 1B 79 */	or. r30, r3, r3
/* 803657A0 00362380  80 C7 00 00 */	lwz r6, 0(r7)
/* 803657A4 00362384  80 07 00 04 */	lwz r0, 4(r7)
/* 803657A8 00362388  90 C1 00 1C */	stw r6, 0x1c(r1)
/* 803657AC 0036238C  90 01 00 20 */	stw r0, 0x20(r1)
/* 803657B0 00362390  80 07 00 08 */	lwz r0, 8(r7)
/* 803657B4 00362394  90 01 00 24 */	stw r0, 0x24(r1)
/* 803657B8 00362398  84 65 94 AC */	lwzu r3, interest@l(r5)
/* 803657BC 0036239C  80 05 00 04 */	lwz r0, 0x4(r5)
/* 803657C0 003623A0  90 61 00 10 */	stw r3, 0x10(r1)
/* 803657C4 003623A4  90 01 00 14 */	stw r0, 0x14(r1)
/* 803657C8 003623A8  80 05 00 08 */	lwz r0, 8(r5)
/* 803657CC 003623AC  90 01 00 18 */	stw r0, 0x18(r1)
/* 803657D0 003623B0  41 82 00 38 */	beq lbl_80365808
/* 803657D4 003623B4  38 7E 00 00 */	addi r3, r30, 0
/* 803657D8 003623B8  38 81 00 1C */	addi r4, r1, 0x1c
/* 803657DC 003623BC  48 00 15 95 */	bl HSD_LObjGetPosition
/* 803657E0 003623C0  38 7E 00 00 */	addi r3, r30, 0
/* 803657E4 003623C4  38 81 00 10 */	addi r4, r1, 0x10
/* 803657E8 003623C8  48 00 16 51 */	bl HSD_LObjGetInterest
/* 803657EC 003623CC  38 BF 00 00 */	addi r5, r31, 0
/* 803657F0 003623D0  38 61 00 10 */	addi r3, r1, 0x10
/* 803657F4 003623D4  38 81 00 1C */	addi r4, r1, 0x1c
/* 803657F8 003623D8  4B FD D5 81 */	bl PSVECSubtract
/* 803657FC 003623DC  38 7F 00 00 */	addi r3, r31, 0
/* 80365800 003623E0  38 9F 00 00 */	addi r4, r31, 0
/* 80365804 003623E4  4B FD D5 B5 */	bl PSVECNormalize
lbl_80365808:
/* 80365808 003623E8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8036580C 003623EC  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80365810 003623F0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80365814 003623F4  38 21 00 30 */	addi r1, r1, 0x30
/* 80365818 003623F8  7C 08 03 A6 */	mtlr r0
/* 8036581C 003623FC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

f32 const lbl_804DE450 = 0.5F;
f32 const lbl_804DE454 = 0.0F;
f32 const lbl_804DE458 = 1.0F;

#ifdef NON_MATCHING

void HSD_LObjSetup(HSD_LObj *lobj, GXColor color, f32 shininess, u32 unused)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT)
    {
        return;
    }

    if ((lobj->flags & LOBJ_DIFFUSE) != 0)
    {
        if (lobj->hw_color.r != color.r || lobj->hw_color.g != color.g || lobj->hw_color.b != color.b || lobj->hw_color.a != color.a)
        {

            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY)
        {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL)
    {
        if (lobj->shininess != shininess)
        {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F, 1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY)
        {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

#else

#pragma push
asm void HSD_LObjSetup(HSD_LObj *lobj, GXColor color, f32 shininess, u32 unused)
{ // clang-format off
    nofralloc
/* 80365820 00362400  7C 08 02 A6 */	mflr r0
/* 80365824 00362404  90 01 00 04 */	stw r0, 4(r1)
/* 80365828 00362408  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8036582C 0036240C  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 80365830 00362410  FF E0 08 90 */	fmr f31, f1
/* 80365834 00362414  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80365838 00362418  7C 7F 1B 78 */	mr r31, r3
/* 8036583C 0036241C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80365840 00362420  3B C4 00 00 */	addi r30, r4, 0
/* 80365844 00362424  A0 63 00 08 */	lhz r3, 8(r3)
/* 80365848 00362428  54 60 06 B5 */	rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 8036584C 0036242C  40 82 01 14 */	bne lbl_80365960
/* 80365850 00362430  54 60 07 BF */	clrlwi. r0, r3, 0x1e
/* 80365854 00362434  40 82 00 08 */	bne lbl_8036585C
/* 80365858 00362438  48 00 01 08 */	b lbl_80365960
lbl_8036585C:
/* 8036585C 0036243C  54 60 07 7B */	rlwinm. r0, r3, 0, 0x1d, 0x1d
/* 80365860 00362440  41 82 00 90 */	beq lbl_803658F0
/* 80365864 00362444  88 7F 00 14 */	lbz r3, 0x14(r31)
/* 80365868 00362448  88 1E 00 00 */	lbz r0, 0(r30)
/* 8036586C 0036244C  7C 03 00 40 */	cmplw r3, r0
/* 80365870 00362450  40 82 00 34 */	bne lbl_803658A4
/* 80365874 00362454  88 7F 00 15 */	lbz r3, 0x15(r31)
/* 80365878 00362458  88 1E 00 01 */	lbz r0, 1(r30)
/* 8036587C 0036245C  7C 03 00 40 */	cmplw r3, r0
/* 80365880 00362460  40 82 00 24 */	bne lbl_803658A4
/* 80365884 00362464  88 7F 00 16 */	lbz r3, 0x16(r31)
/* 80365888 00362468  88 1E 00 02 */	lbz r0, 2(r30)
/* 8036588C 0036246C  7C 03 00 40 */	cmplw r3, r0
/* 80365890 00362470  40 82 00 14 */	bne lbl_803658A4
/* 80365894 00362474  88 7F 00 17 */	lbz r3, 0x17(r31)
/* 80365898 00362478  88 1E 00 03 */	lbz r0, 3(r30)
/* 8036589C 0036247C  7C 03 00 40 */	cmplw r3, r0
/* 803658A0 00362480  41 82 00 2C */	beq lbl_803658CC
lbl_803658A4:
/* 803658A4 00362484  80 1E 00 00 */	lwz r0, 0(r30)
/* 803658A8 00362488  38 81 00 18 */	addi r4, r1, 0x18
/* 803658AC 0036248C  38 7F 00 50 */	addi r3, r31, 0x50
/* 803658B0 00362490  90 01 00 18 */	stw r0, 0x18(r1)
/* 803658B4 00362494  4B FD 88 69 */	bl GXInitLightColor
/* 803658B8 00362498  80 1E 00 00 */	lwz r0, 0(r30)
/* 803658BC 0036249C  90 1F 00 14 */	stw r0, 0x14(r31)
/* 803658C0 003624A0  A0 1F 00 08 */	lhz r0, 8(r31)
/* 803658C4 003624A4  60 00 00 80 */	ori r0, r0, 0x80
/* 803658C8 003624A8  B0 1F 00 08 */	sth r0, 8(r31)
lbl_803658CC:
/* 803658CC 003624AC  A0 1F 00 08 */	lhz r0, 8(r31)
/* 803658D0 003624B0  54 00 06 31 */	rlwinm. r0, r0, 0, 0x18, 0x18
/* 803658D4 003624B4  41 82 00 1C */	beq lbl_803658F0
/* 803658D8 003624B8  38 7F 00 50 */	addi r3, r31, 0x50
/* 803658DC 003624BC  80 9F 00 4C */	lwz r4, 0x4c(r31)
/* 803658E0 003624C0  4B FD 88 65 */	bl GXLoadLightObjImm
/* 803658E4 003624C4  A0 1F 00 08 */	lhz r0, 8(r31)
/* 803658E8 003624C8  54 00 06 6E */	rlwinm r0, r0, 0, 0x19, 0x17
/* 803658EC 003624CC  B0 1F 00 08 */	sth r0, 8(r31)
lbl_803658F0:
/* 803658F0 003624D0  80 1F 00 90 */	lwz r0, 0x90(r31)
/* 803658F4 003624D4  2C 00 00 00 */	cmpwi r0, 0
/* 803658F8 003624D8  41 82 00 68 */	beq lbl_80365960
/* 803658FC 003624DC  C0 1F 00 38 */	lfs f0, 0x38(r31)
/* 80365900 003624E0  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 80365904 003624E4  41 82 00 38 */	beq lbl_8036593C
/* 80365908 003624E8  D3 FF 00 38 */	stfs f31, 0x38(r31)
/* 8036590C 003624EC  38 7F 00 94 */	addi r3, r31, 0x94
/* 80365910 003624F0  C0 02 EA 70 */	lfs f0, lbl_804DE450(r2)
/* 80365914 003624F4  C0 22 EA 74 */	lfs f1, lbl_804DE454(r2)
/* 80365918 003624F8  EC 9F 00 32 */	fmuls f4, f31, f0
/* 8036591C 003624FC  C0 62 EA 78 */	lfs f3, lbl_804DE458(r2)
/* 80365920 00362500  FC 40 08 90 */	fmr f2, f1
/* 80365924 00362504  FC A0 08 90 */	fmr f5, f1
/* 80365928 00362508  EC C3 20 28 */	fsubs f6, f3, f4
/* 8036592C 0036250C  4B FD 85 59 */	bl GXInitLightAttn
/* 80365930 00362510  A0 1F 00 08 */	lhz r0, 8(r31)
/* 80365934 00362514  60 00 01 00 */	ori r0, r0, 0x100
/* 80365938 00362518  B0 1F 00 08 */	sth r0, 8(r31)
lbl_8036593C:
/* 8036593C 0036251C  A0 1F 00 08 */	lhz r0, 8(r31)
/* 80365940 00362520  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 80365944 00362524  41 82 00 1C */	beq lbl_80365960
/* 80365948 00362528  38 7F 00 94 */	addi r3, r31, 0x94
/* 8036594C 0036252C  80 9F 00 90 */	lwz r4, 0x90(r31)
/* 80365950 00362530  4B FD 87 F5 */	bl GXLoadLightObjImm
/* 80365954 00362534  A0 1F 00 08 */	lhz r0, 8(r31)
/* 80365958 00362538  54 00 06 2C */	rlwinm r0, r0, 0, 0x18, 0x16
/* 8036595C 0036253C  B0 1F 00 08 */	sth r0, 8(r31)
lbl_80365960:
/* 80365960 00362540  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80365964 00362544  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 80365968 00362548  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8036596C 0036254C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80365970 00362550  38 21 00 30 */	addi r1, r1, 0x30
/* 80365974 00362554  7C 08 03 A6 */	mtlr r0
/* 80365978 00362558  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif
