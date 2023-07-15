#include "lobj.h"

#include <placeholder.h>
#include <dolphin/mtx.h>
#include <dolphin/mtx/mtxvec.h>
#include <dolphin/mtx/types.h>
#include <dolphin/mtx/vec.h>

void LObjInfoInit(void);

HSD_LObjInfo hsdLObj = { LObjInfoInit };

extern s32 lightmask_diffuse;
extern s32 lightmask_attnfunc;
extern s32 lightmask_alpha;
extern s32 lightmask_specular;
extern s32 nb_active_lights;
extern HSD_SList* current_lights;

HSD_LObj* active_lights[GX_MAX_LIGHT];

u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return (lobj) ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
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

u32 HSD_LObjGetType(HSD_LObj* lobj)
{
    return lobj->flags & 0x3;
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < GX_MAX_LIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < GX_MAX_LIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

/// @private
void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv < 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a0 = val->fv;
        } else {
            lobj->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a1 = val->fv;
        } else {
            lobj->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.a2 = val->fv;
        } else {
            lobj->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            lobj->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        lobj->color.r = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_G:
        lobj->color.g = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_B:
        lobj->color.b = 255.0 * val->fv;
        break;
    case HSD_A_L_LITC_A:
        lobj->color.a = 255.0 * val->fv;
        break;
    }
}

void HSD_LObjAnim(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, &LObjUpdateFunc);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

void HSD_LObjAnimAll(HSD_LObj* lobj)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe)
{
    if (lobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjReqAnim(lp, startframe);
    }
}

Vec3 const HSD_LObj_803B94A0 = { 0.0F, 0.0F, 0.0F };
Vec3 const HSD_LObj_803B94AC = { 0.0F, 0.0F, 0.0F };

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = HSD_LObj_803B94A0;
    Vec3 interest = HSD_LObj_803B94AC;

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    PSVECNormalize(dir, dir);
}

f32 const lbl_804DE450 = 0.5F;
f32 const lbl_804DE454 = 0.0F;
f32 const lbl_804DE458 = 1.0F;

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & LOBJ_DIFFUSE) != 0) {
        if (lobj->hw_color.r != color.r || lobj->hw_color.g != color.g ||
            lobj->hw_color.b != color.b || lobj->hw_color.a != color.a)
        {
            GXInitLightColor(&lobj->lightobj, color);
            lobj->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&lobj->lightobj, lobj->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (lobj->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F,
                            1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&lobj->spec_lightobj, lobj->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

extern char HSD_LObj_804D5D18[8];
extern char HSD_LObj_804D5D20[8];

void HSD_LObjSetupSpecularInit(Mtx pmtx)
{
    int i;
    s32 num;
    Vec3 cdir;
    Vec3 jpos;

    jpos.x = pmtx[0][3];
    jpos.y = pmtx[1][3];
    jpos.z = pmtx[2][3];
    PSVECNormalize(&jpos, &cdir);

    num = HSD_LObjGetNbActive();
    for (i = 0; i < num; i++) {
        Vec3 half, ldir;
        HSD_LObj* lobj = HSD_LObjGetActiveByIndex(i);

        if (lobj->spec_id == GX_LIGHT_NULL) {
            continue;
        }

        switch (HSD_LObjGetType(lobj)) {
        case LOBJ_POINT:
        case LOBJ_SPOT:
            PSVECSubtract(&jpos, &lobj->lvec, &ldir);
            PSVECNormalize(&ldir, &ldir);
            PSVECAdd(&ldir, &cdir, &half);
            break;

        case LOBJ_INFINITE:
            PSVECAdd(&lobj->lvec, &cdir, &half);
            break;

        default:
            __assert(HSD_LObj_804D5D18, 0x269, HSD_LObj_804D5D20);
        }
        PSVECNormalize(&half, &half);
        GXInitLightDir(&lobj->spec_lightobj, half.x, half.y, half.z);
        lobj->flags |= LOBJ_SPEC_DIRTY;
    }
}

void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;
    lobj->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&lobj->spec_lightobj, lobj->color);
        lobj->shininess = 50.0F;

        /// @todo Duplicate assignment
#ifdef MUST_MATCH
        x = x = lobj->shininess;
#else
        x = lobj->shininess;
#endif

        x *= 0.5F;
        GXInitLightAttn(&lobj->spec_lightobj, 0.0F, 0.0F, 1.0F, x, 0.0F,
                        1.0F - x);
        switch (HSD_LObjGetType(lobj)) {
        case 2:
        case 3:
            HSD_LObjGetPosition(lobj, &lobj->lvec);
            PSMTXMUltiVec(mtx, &lobj->lvec, &lobj->lvec);
            break;
        case 1:
            HSD_LObjGetLightVector(lobj, &lobj->lvec);
            PSMTXMultVecSR(mtx, &lobj->lvec, &lobj->lvec);
            PSVECNormalize(&lobj->lvec, &lobj->lvec);
            break;
        default:
            __assert(HSD_LObj_804D5D18, 0x2A8, HSD_LObj_804D5D20);
        }
        lobj->flags |= 0x100;
        lightmask_specular |= spec_id;
    }
}

void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    GXInitLightColor(&lobj->lightobj, lobj->color);
    lobj->hw_color = lobj->color;
    HSD_LObjGetPosition(lobj, &lpos);
    PSMTXMUltiVec(mtx, &lpos, &lpos);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, 1.0F, 0.0F, 0.0F, lobj->u.attn.k0,
                        lobj->u.attn.k1, lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.spot.ref_br;
        f32 ref_dist = lobj->u.spot.ref_dist;
        s32 dist_func = lobj->u.spot.dist_func;
        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, 0.0F, 0);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
    }
}

void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    Vec3 ldir;
    HSD_LObjGetPosition(lobj, &lpos);
    PSMTXMUltiVec(mtx, &lpos, &lpos);
    HSD_LObjGetLightVector(lobj, &ldir);
    PSMTXMultVecSR(mtx, &ldir, &ldir);
    PSVECNormalize(&ldir, &ldir);
    GXInitLightPos(&lobj->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&lobj->spec_lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightDir(&lobj->lightobj, ldir.x, ldir.y, ldir.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&lobj->lightobj, lobj->u.attn.a0, lobj->u.attn.a1,
                        lobj->u.attn.a2, lobj->u.attn.k0, lobj->u.attn.k1,
                        lobj->u.attn.k2);
    } else {
        f32 ref_br = lobj->u.point.ref_br;
        f32 ref_dist = lobj->u.point.ref_dist;
        f32 cutoff = lobj->u.point.cutoff;
        s32 spot_func = lobj->u.spot.spot_func;
        s32 dist_func = lobj->u.spot.dist_func;

        GXInitLightDistAttn(&lobj->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightDistAttn(&lobj->spec_lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&lobj->lightobj, cutoff, spot_func);
    }
}

extern char HSD_LObj_804D5D24[4];

#ifdef MWERKS_GEKKO

#pragma push
asm void HSD_LObjSetupInit(HSD_CObj* arg0)
{ // clang-format off
    nofralloc
/* 80365F28 00362B08  7C 08 02 A6 */	mflr r0
/* 80365F2C 00362B0C  38 80 00 00 */	li r4, 0
/* 80365F30 00362B10  90 01 00 04 */	stw r0, 4(r1)
/* 80365F34 00362B14  3C A0 80 4C */	lis r5, active_lights@ha
/* 80365F38 00362B18  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 80365F3C 00362B1C  DB E1 00 68 */	stfd f31, 0x68(r1)
/* 80365F40 00362B20  BE E1 00 44 */	stmw r23, 0x44(r1)
/* 80365F44 00362B24  3B 83 00 54 */	addi r28, r3, 0x54
/* 80365F48 00362B28  3B C5 08 B0 */	addi r30, r5, active_lights@l
/* 80365F4C 00362B2C  3B 40 00 00 */	li r26, 0
/* 80365F50 00362B30  3B 60 00 00 */	li r27, 0
/* 80365F54 00362B34  38 60 00 08 */	li r3, 8
/* 80365F58 00362B38  90 8D BF A4 */	stw r4, lightmask_diffuse(r13)
/* 80365F5C 00362B3C  90 8D BF A8 */	stw r4, lightmask_specular(r13)
/* 80365F60 00362B40  90 8D BF AC */	stw r4, lightmask_attnfunc(r13)
/* 80365F64 00362B44  90 8D BF B0 */	stw r4, lightmask_alpha(r13)
/* 80365F68 00362B48  90 9E 00 00 */	stw r4, 0(r30)
/* 80365F6C 00362B4C  90 9E 00 04 */	stw r4, 4(r30)
/* 80365F70 00362B50  90 9E 00 08 */	stw r4, 8(r30)
/* 80365F74 00362B54  90 9E 00 0C */	stw r4, 0xc(r30)
/* 80365F78 00362B58  90 9E 00 10 */	stw r4, 0x10(r30)
/* 80365F7C 00362B5C  90 9E 00 14 */	stw r4, 0x14(r30)
/* 80365F80 00362B60  90 9E 00 18 */	stw r4, 0x18(r30)
/* 80365F84 00362B64  90 9E 00 1C */	stw r4, 0x1c(r30)
/* 80365F88 00362B68  48 00 04 08 */	b lbl_80366390
lbl_80365F8C:
/* 80365F8C 00362B6C  20 03 00 09 */	subfic r0, r3, 9
/* 80365F90 00362B70  2C 03 00 09 */	cmpwi r3, 9
/* 80365F94 00362B74  7C 09 03 A6 */	mtctr r0
/* 80365F98 00362B78  40 80 00 10 */	bge lbl_80365FA8
lbl_80365F9C:
/* 80365F9C 00362B7C  90 85 00 00 */	stw r4, 0(r5)
/* 80365FA0 00362B80  38 A5 00 04 */	addi r5, r5, 4
/* 80365FA4 00362B84  42 00 FF F8 */	bdnz lbl_80365F9C
lbl_80365FA8:
/* 80365FA8 00362B88  38 00 00 00 */	li r0, 0
/* 80365FAC 00362B8C  83 2D BF 9C */	lwz r25, current_lights(r13)
/* 80365FB0 00362B90  90 0D BF A0 */	stw r0, nb_active_lights(r13)
/* 80365FB4 00362B94  3B E1 00 24 */	addi r31, r1, 0x24
/* 80365FB8 00362B98  C3 E2 EA 80 */	lfs f31, 1048576.0F
/* 80365FBC 00362B9C  48 00 02 68 */	b lbl_80366224
lbl_80365FC0:
/* 80365FC0 00362BA0  80 19 00 04 */	lwz r0, 4(r25)
/* 80365FC4 00362BA4  28 00 00 00 */	cmplwi r0, 0
/* 80365FC8 00362BA8  7C 18 03 78 */	mr r24, r0
/* 80365FCC 00362BAC  40 82 00 14 */	bne lbl_80365FE0
/* 80365FD0 00362BB0  38 6D A6 78 */	addi r3, r13, HSD_LObj_804D5D18
/* 80365FD4 00362BB4  38 80 03 34 */	li r4, 0x334
/* 80365FD8 00362BB8  38 AD A6 84 */	addi r5, r13, HSD_LObj_804D5D24
/* 80365FDC 00362BBC  48 02 22 45 */	bl __assert
lbl_80365FE0:
/* 80365FE0 00362BC0  A0 78 00 08 */	lhz r3, 8(r24)
/* 80365FE4 00362BC4  54 60 06 B5 */	rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 80365FE8 00362BC8  40 82 02 38 */	bne lbl_80366220
/* 80365FEC 00362BCC  54 7D 07 BF */	clrlwi. r29, r3, 0x1e
/* 80365FF0 00362BD0  54 77 07 3A */	rlwinm r23, r3, 0, 0x1c, 0x1d
/* 80365FF4 00362BD4  41 82 00 30 */	beq lbl_80366024
/* 80365FF8 00362BD8  2C 17 00 08 */	cmpwi r23, 8
/* 80365FFC 00362BDC  41 82 00 20 */	beq lbl_8036601C
/* 80366000 00362BE0  40 80 00 10 */	bge lbl_80366010
/* 80366004 00362BE4  2C 17 00 04 */	cmpwi r23, 4
/* 80366008 00362BE8  41 82 00 1C */	beq lbl_80366024
/* 8036600C 00362BEC  48 00 02 14 */	b lbl_80366220
lbl_80366010:
/* 80366010 00362BF0  2C 17 00 0C */	cmpwi r23, 0xc
/* 80366014 00362BF4  41 82 00 10 */	beq lbl_80366024
/* 80366018 00362BF8  48 00 02 08 */	b lbl_80366220
lbl_8036601C:
/* 8036601C 00362BFC  2C 1B 00 08 */	cmpwi r27, 8
/* 80366020 00362C00  40 80 02 00 */	bge lbl_80366220
lbl_80366024:
/* 80366024 00362C04  28 1D 00 00 */	cmplwi r29, 0
/* 80366028 00362C08  40 82 00 18 */	bne lbl_80366040
/* 8036602C 00362C0C  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 80366030 00362C10  38 60 00 08 */	li r3, 8
/* 80366034 00362C14  28 00 00 00 */	cmplwi r0, 0
/* 80366038 00362C18  41 82 00 14 */	beq lbl_8036604C
/* 8036603C 00362C1C  48 00 00 20 */	b lbl_8036605C
lbl_80366040:
/* 80366040 00362C20  80 6D BF A0 */	lwz r3, nb_active_lights(r13)
/* 80366044 00362C24  38 03 00 01 */	addi r0, r3, 1
/* 80366048 00362C28  90 0D BF A0 */	stw r0, nb_active_lights(r13)
lbl_8036604C:
/* 8036604C 00362C2C  54 60 10 3A */	slwi r0, r3, 2
/* 80366050 00362C30  7F 1E 01 2E */	stwx r24, r30, r0
/* 80366054 00362C34  48 00 0B 11 */	bl HSD_Index2LightID
/* 80366058 00362C38  90 78 00 4C */	stw r3, 0x4c(r24)
lbl_8036605C:
/* 8036605C 00362C3C  83 4D BF A0 */	lwz r26, nb_active_lights(r13)
/* 80366060 00362C40  38 00 00 00 */	li r0, 0
/* 80366064 00362C44  2C 1D 00 02 */	cmpwi r29, 2
/* 80366068 00362C48  90 18 00 90 */	stw r0, 0x90(r24)
/* 8036606C 00362C4C  41 82 00 C8 */	beq lbl_80366134
/* 80366070 00362C50  40 80 00 14 */	bge lbl_80366084
/* 80366074 00362C54  2C 1D 00 00 */	cmpwi r29, 0
/* 80366078 00362C58  41 82 01 A8 */	beq lbl_80366220
/* 8036607C 00362C5C  40 80 00 14 */	bge lbl_80366090
/* 80366080 00362C60  48 00 00 D0 */	b lbl_80366150
lbl_80366084:
/* 80366084 00362C64  2C 1D 00 04 */	cmpwi r29, 4
/* 80366088 00362C68  40 80 00 C8 */	bge lbl_80366150
/* 8036608C 00362C6C  48 00 00 B8 */	b lbl_80366144
lbl_80366090:
/* 80366090 00362C70  38 78 00 00 */	addi r3, r24, 0
/* 80366094 00362C74  38 81 00 28 */	addi r4, r1, 0x28
/* 80366098 00362C78  48 00 0C D9 */	bl HSD_LObjGetPosition
/* 8036609C 00362C7C  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 803660A0 00362C80  38 81 00 28 */	addi r4, r1, 0x28
/* 803660A4 00362C84  38 7C 00 00 */	addi r3, r28, 0
/* 803660A8 00362C88  EC 00 07 F2 */	fmuls f0, f0, f31
/* 803660AC 00362C8C  7C 85 23 78 */	mr r5, r4
/* 803660B0 00362C90  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 803660B4 00362C94  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 803660B8 00362C98  EC 00 07 F2 */	fmuls f0, f0, f31
/* 803660BC 00362C9C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 803660C0 00362CA0  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 803660C4 00362CA4  EC 00 07 F2 */	fmuls f0, f0, f31
/* 803660C8 00362CA8  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 803660CC 00362CAC  4B FD C9 DD */	bl PSMTXMUltiVec
/* 803660D0 00362CB0  A0 18 00 08 */	lhz r0, 8(r24)
/* 803660D4 00362CB4  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 803660D8 00362CB8  41 82 00 38 */	beq lbl_80366110
/* 803660DC 00362CBC  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 803660E0 00362CC0  38 78 00 50 */	addi r3, r24, 0x50
/* 803660E4 00362CC4  C0 41 00 2C */	lfs f2, 0x2c(r1)
/* 803660E8 00362CC8  C0 61 00 30 */	lfs f3, 0x30(r1)
/* 803660EC 00362CCC  4B FD 80 05 */	bl GXInitLightPos
/* 803660F0 00362CD0  C0 42 EA 74 */	lfs f2, 0.0F
/* 803660F4 00362CD4  38 78 00 50 */	addi r3, r24, 0x50
/* 803660F8 00362CD8  C0 22 EA 78 */	lfs f1, 1.0F
/* 803660FC 00362CDC  FC 60 10 90 */	fmr f3, f2
/* 80366100 00362CE0  FC 80 08 90 */	fmr f4, f1
/* 80366104 00362CE4  FC A0 10 90 */	fmr f5, f2
/* 80366108 00362CE8  FC C0 10 90 */	fmr f6, f2
/* 8036610C 00362CEC  4B FD 7D 79 */	bl GXInitLightAttn
lbl_80366110:
/* 80366110 00362CF0  A0 18 00 08 */	lhz r0, 8(r24)
/* 80366114 00362CF4  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80366118 00362CF8  41 82 00 38 */	beq lbl_80366150
/* 8036611C 00362CFC  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 80366120 00362D00  38 78 00 94 */	addi r3, r24, 0x94
/* 80366124 00362D04  C0 41 00 2C */	lfs f2, 0x2c(r1)
/* 80366128 00362D08  C0 61 00 30 */	lfs f3, 0x30(r1)
/* 8036612C 00362D0C  4B FD 7F C5 */	bl GXInitLightPos
/* 80366130 00362D10  48 00 00 20 */	b lbl_80366150
lbl_80366134:
/* 80366134 00362D14  38 78 00 00 */	addi r3, r24, 0
/* 80366138 00362D18  38 9C 00 00 */	addi r4, r28, 0
/* 8036613C 00362D1C  4B FF FB 15 */	bl setup_point_lightobj
/* 80366140 00362D20  48 00 00 10 */	b lbl_80366150
lbl_80366144:
/* 80366144 00362D24  38 78 00 00 */	addi r3, r24, 0
/* 80366148 00362D28  38 9C 00 00 */	addi r4, r28, 0
/* 8036614C 00362D2C  4B FF FC 21 */	bl setup_spot_lightobj
lbl_80366150:
/* 80366150 00362D30  2C 17 00 08 */	cmpwi r23, 8
/* 80366154 00362D34  41 82 00 B8 */	beq lbl_8036620C
/* 80366158 00362D38  40 80 00 10 */	bge lbl_80366168
/* 8036615C 00362D3C  2C 17 00 04 */	cmpwi r23, 4
/* 80366160 00362D40  41 82 00 14 */	beq lbl_80366174
/* 80366164 00362D44  48 00 00 BC */	b lbl_80366220
lbl_80366168:
/* 80366168 00362D48  2C 17 00 0C */	cmpwi r23, 0xc
/* 8036616C 00362D4C  41 82 00 08 */	beq lbl_80366174
/* 80366170 00362D50  48 00 00 B0 */	b lbl_80366220
lbl_80366174:
/* 80366174 00362D54  80 18 00 10 */	lwz r0, 0x10(r24)
/* 80366178 00362D58  38 9F 00 00 */	addi r4, r31, 0
/* 8036617C 00362D5C  38 78 00 50 */	addi r3, r24, 0x50
/* 80366180 00362D60  90 01 00 24 */	stw r0, 0x24(r1)
/* 80366184 00362D64  4B FD 7F 99 */	bl GXInitLightColor
/* 80366188 00362D68  80 18 00 10 */	lwz r0, 0x10(r24)
/* 8036618C 00362D6C  90 18 00 14 */	stw r0, 0x14(r24)
/* 80366190 00362D70  A0 18 00 08 */	lhz r0, 8(r24)
/* 80366194 00362D74  60 00 00 80 */	ori r0, r0, 0x80
/* 80366198 00362D78  B0 18 00 08 */	sth r0, 8(r24)
/* 8036619C 00362D7C  80 6D BF A4 */	lwz r3, lightmask_diffuse(r13)
/* 803661A0 00362D80  80 18 00 4C */	lwz r0, 0x4c(r24)
/* 803661A4 00362D84  7C 60 03 78 */	or r0, r3, r0
/* 803661A8 00362D88  90 0D BF A4 */	stw r0, lightmask_diffuse(r13)
/* 803661AC 00362D8C  A0 18 00 08 */	lhz r0, 8(r24)
/* 803661B0 00362D90  54 00 07 BE */	clrlwi r0, r0, 0x1e
/* 803661B4 00362D94  2C 00 00 01 */	cmpwi r0, 1
/* 803661B8 00362D98  41 82 00 34 */	beq lbl_803661EC
/* 803661BC 00362D9C  41 80 00 20 */	blt lbl_803661DC
/* 803661C0 00362DA0  2C 00 00 04 */	cmpwi r0, 4
/* 803661C4 00362DA4  40 80 00 18 */	bge lbl_803661DC
/* 803661C8 00362DA8  80 6D BF AC */	lwz r3, lightmask_attnfunc(r13)
/* 803661CC 00362DAC  80 18 00 4C */	lwz r0, 0x4c(r24)
/* 803661D0 00362DB0  7C 60 03 78 */	or r0, r3, r0
/* 803661D4 00362DB4  90 0D BF AC */	stw r0, lightmask_attnfunc(r13)
/* 803661D8 00362DB8  48 00 00 14 */	b lbl_803661EC
lbl_803661DC:
/* 803661DC 00362DBC  38 6D A6 78 */	addi r3, r13, HSD_LObj_804D5D18
/* 803661E0 00362DC0  38 80 02 82 */	li r4, 0x282
/* 803661E4 00362DC4  38 AD A6 80 */	addi r5, r13, HSD_LObj_804D5D20
/* 803661E8 00362DC8  48 02 20 39 */	bl __assert
lbl_803661EC:
/* 803661EC 00362DCC  A0 18 00 08 */	lhz r0, 8(r24)
/* 803661F0 00362DD0  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 803661F4 00362DD4  41 82 00 2C */	beq lbl_80366220
/* 803661F8 00362DD8  80 6D BF B0 */	lwz r3, lightmask_alpha(r13)
/* 803661FC 00362DDC  80 18 00 4C */	lwz r0, 0x4c(r24)
/* 80366200 00362DE0  7C 60 03 78 */	or r0, r3, r0
/* 80366204 00362DE4  90 0D BF B0 */	stw r0, lightmask_alpha(r13)
/* 80366208 00362DE8  48 00 00 18 */	b lbl_80366220
lbl_8036620C:
/* 8036620C 00362DEC  80 B8 00 4C */	lwz r5, 0x4c(r24)
/* 80366210 00362DF0  38 78 00 00 */	addi r3, r24, 0
/* 80366214 00362DF4  38 9C 00 00 */	addi r4, r28, 0
/* 80366218 00362DF8  4B FF F8 AD */	bl setup_spec_lightobj
/* 8036621C 00362DFC  3B 7B 00 01 */	addi r27, r27, 1
lbl_80366220:
/* 80366220 00362E00  83 39 00 00 */	lwz r25, 0(r25)
lbl_80366224:
/* 80366224 00362E04  2C 1A 00 08 */	cmpwi r26, 8
/* 80366228 00362E08  40 80 00 0C */	bge lbl_80366234
/* 8036622C 00362E0C  28 19 00 00 */	cmplwi r25, 0
/* 80366230 00362E10  40 82 FD 90 */	bne lbl_80365FC0
lbl_80366234:
/* 80366234 00362E14  38 60 01 00 */	li r3, 0x100
/* 80366238 00362E18  48 00 08 41 */	bl HSD_LightID2Index
/* 8036623C 00362E1C  2C 03 00 00 */	cmpwi r3, 0
/* 80366240 00362E20  41 80 00 18 */	blt lbl_80366258
/* 80366244 00362E24  2C 03 00 09 */	cmpwi r3, 9
/* 80366248 00362E28  40 80 00 10 */	bge lbl_80366258
/* 8036624C 00362E2C  54 60 10 3A */	slwi r0, r3, 2
/* 80366250 00362E30  7C 1E 00 2E */	lwzx r0, r30, r0
/* 80366254 00362E34  48 00 00 08 */	b lbl_8036625C
lbl_80366258:
/* 80366258 00362E38  38 00 00 00 */	li r0, 0
lbl_8036625C:
/* 8036625C 00362E3C  28 00 00 00 */	cmplwi r0, 0
/* 80366260 00362E40  40 82 00 80 */	bne lbl_803662E0
/* 80366264 00362E44  48 00 00 74 */	b lbl_803662D8
lbl_80366268:
/* 80366268 00362E48  82 F9 00 04 */	lwz r23, 4(r25)
/* 8036626C 00362E4C  28 17 00 00 */	cmplwi r23, 0
/* 80366270 00362E50  40 82 00 14 */	bne lbl_80366284
/* 80366274 00362E54  38 6D A6 78 */	addi r3, r13, HSD_LObj_804D5D18
/* 80366278 00362E58  38 80 03 72 */	li r4, 0x372
/* 8036627C 00362E5C  38 AD A6 84 */	addi r5, r13, HSD_LObj_804D5D24
/* 80366280 00362E60  48 02 1F A1 */	bl __assert
lbl_80366284:
/* 80366284 00362E64  A0 17 00 08 */	lhz r0, 8(r23)
/* 80366288 00362E68  54 03 07 BF */	clrlwi. r3, r0, 0x1e
/* 8036628C 00362E6C  40 82 00 48 */	bne lbl_803662D4
/* 80366290 00362E70  54 00 06 B5 */	rlwinm. r0, r0, 0, 0x1a, 0x1a
/* 80366294 00362E74  40 82 00 40 */	bne lbl_803662D4
/* 80366298 00362E78  28 03 00 00 */	cmplwi r3, 0
/* 8036629C 00362E7C  40 82 00 18 */	bne lbl_803662B4
/* 803662A0 00362E80  80 1E 00 20 */	lwz r0, 0x20(r30)
/* 803662A4 00362E84  38 60 00 08 */	li r3, 8
/* 803662A8 00362E88  28 00 00 00 */	cmplwi r0, 0
/* 803662AC 00362E8C  41 82 00 14 */	beq lbl_803662C0
/* 803662B0 00362E90  48 00 00 30 */	b lbl_803662E0
lbl_803662B4:
/* 803662B4 00362E94  80 6D BF A0 */	lwz r3, nb_active_lights(r13)
/* 803662B8 00362E98  38 03 00 01 */	addi r0, r3, 1
/* 803662BC 00362E9C  90 0D BF A0 */	stw r0, nb_active_lights(r13)
lbl_803662C0:
/* 803662C0 00362EA0  54 60 10 3A */	slwi r0, r3, 2
/* 803662C4 00362EA4  7E FE 01 2E */	stwx r23, r30, r0
/* 803662C8 00362EA8  48 00 08 9D */	bl HSD_Index2LightID
/* 803662CC 00362EAC  90 77 00 4C */	stw r3, 0x4c(r23)
/* 803662D0 00362EB0  48 00 00 10 */	b lbl_803662E0
lbl_803662D4:
/* 803662D4 00362EB4  83 39 00 00 */	lwz r25, 0(r25)
lbl_803662D8:
/* 803662D8 00362EB8  28 19 00 00 */	cmplwi r25, 0
/* 803662DC 00362EBC  40 82 FF 8C */	bne lbl_80366268
lbl_803662E0:
/* 803662E0 00362EC0  82 ED BF 9C */	lwz r23, current_lights(r13)
/* 803662E4 00362EC4  48 00 00 40 */	b lbl_80366324
lbl_803662E8:
/* 803662E8 00362EC8  80 77 00 04 */	lwz r3, 4(r23)
/* 803662EC 00362ECC  A0 03 00 08 */	lhz r0, 8(r3)
/* 803662F0 00362ED0  3B 03 00 00 */	addi r24, r3, 0
/* 803662F4 00362ED4  70 00 00 2C */	andi. r0, r0, 0x2c
/* 803662F8 00362ED8  28 00 00 0C */	cmplwi r0, 0xc
/* 803662FC 00362EDC  40 82 00 24 */	bne lbl_80366320
/* 80366300 00362EE0  38 7A 00 00 */	addi r3, r26, 0
/* 80366304 00362EE4  3B 5A 00 01 */	addi r26, r26, 1
/* 80366308 00362EE8  48 00 08 5D */	bl HSD_Index2LightID
/* 8036630C 00362EEC  38 A3 00 00 */	addi r5, r3, 0
/* 80366310 00362EF0  38 78 00 00 */	addi r3, r24, 0
/* 80366314 00362EF4  38 9C 00 00 */	addi r4, r28, 0
/* 80366318 00362EF8  4B FF F7 AD */	bl setup_spec_lightobj
/* 8036631C 00362EFC  3B 7B 00 01 */	addi r27, r27, 1
lbl_80366320:
/* 80366320 00362F00  82 F7 00 00 */	lwz r23, 0(r23)
lbl_80366324:
/* 80366324 00362F04  28 17 00 00 */	cmplwi r23, 0
/* 80366328 00362F08  41 82 00 14 */	beq lbl_8036633C
/* 8036632C 00362F0C  2C 1B 00 08 */	cmpwi r27, 8
/* 80366330 00362F10  40 80 00 0C */	bge lbl_8036633C
/* 80366334 00362F14  2C 1A 00 08 */	cmpwi r26, 8
/* 80366338 00362F18  41 80 FF B0 */	blt lbl_803662E8
lbl_8036633C:
/* 8036633C 00362F1C  3A E1 00 34 */	addi r23, r1, 0x34
/* 80366340 00362F20  3B 00 00 00 */	li r24, 0
lbl_80366344:
/* 80366344 00362F24  2C 18 00 00 */	cmpwi r24, 0
/* 80366348 00362F28  41 80 00 14 */	blt lbl_8036635C
/* 8036634C 00362F2C  2C 18 00 08 */	cmpwi r24, 8
/* 80366350 00362F30  40 80 00 0C */	bge lbl_8036635C
/* 80366354 00362F34  80 7E 00 00 */	lwz r3, 0(r30)
/* 80366358 00362F38  48 00 00 08 */	b lbl_80366360
lbl_8036635C:
/* 8036635C 00362F3C  38 60 00 00 */	li r3, 0
lbl_80366360:
/* 80366360 00362F40  28 03 00 00 */	cmplwi r3, 0
/* 80366364 00362F44  41 82 00 38 */	beq lbl_8036639C
/* 80366368 00362F48  80 03 00 10 */	lwz r0, 0x10(r3)
/* 8036636C 00362F4C  7E E4 BB 78 */	mr r4, r23
/* 80366370 00362F50  90 01 00 34 */	stw r0, 0x34(r1)
/* 80366374 00362F54  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 80366378 00362F58  4B FF F4 A9 */	bl HSD_LObjSetup
/* 8036637C 00362F5C  3B 18 00 01 */	addi r24, r24, 1
/* 80366380 00362F60  2C 18 00 08 */	cmpwi r24, 8
/* 80366384 00362F64  3B DE 00 04 */	addi r30, r30, 4
/* 80366388 00362F68  41 80 FF BC */	blt lbl_80366344
/* 8036638C 00362F6C  48 00 00 10 */	b lbl_8036639C
lbl_80366390:
/* 80366390 00362F70  54 60 10 3A */	slwi r0, r3, 2
/* 80366394 00362F74  7C BE 02 14 */	add r5, r30, r0
/* 80366398 00362F78  4B FF FB F4 */	b lbl_80365F8C
lbl_8036639C:
/* 8036639C 00362F7C  BA E1 00 44 */	lmw r23, 0x44(r1)
/* 803663A0 00362F80  80 01 00 74 */	lwz r0, 0x74(r1)
/* 803663A4 00362F84  CB E1 00 68 */	lfd f31, 0x68(r1)
/* 803663A8 00362F88  38 21 00 70 */	addi r1, r1, 0x70
/* 803663AC 00362F8C  7C 08 03 A6 */	mtlr r0
/* 803663B0 00362F90  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void HSD_LObjSetupInit(HSD_CObj* arg0)
{
    NOT_IMPLEMENTED;
}

#endif

extern char HSD_LObj_804D5D2C[8];
inline u8 HSD_LObjGetPriority(HSD_LObj* lobj)
{
    if (lobj == NULL) {
        __assert(HSD_LObj_804D5D2C, 0x16F, HSD_LObj_804D5D24);
    }
    return lobj->priority;
}

void HSD_LObjAddCurrent(HSD_LObj* lobj)
{
    HSD_SList* node;
    HSD_SList** p;

    if (lobj != NULL) {
        node = current_lights;
        while (node != NULL) {
            if (node->data == lobj) {
                HSD_LObjDeleteCurrent(lobj);
                break;
            }
            node = node->next;
        }
        ref_INC(lobj);
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            u8 priority1 = HSD_LObjGetPriority(lobj);
            u8 priority2 = HSD_LObjGetPriority((*p)->data);
            if (priority2 > priority1) {
                break;
            }
        }
        *p = HSD_SListAllocAndPrepend(*p, lobj);
    }
}

void HSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        if (lobj != NULL) {
            HSD_OBJECT_METHOD(lobj)->release((HSD_Class*) lobj);
            HSD_OBJECT_METHOD(lobj)->destroy((HSD_Class*) lobj);
        }
    }
}

void HSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < GX_MAX_LIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                HSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

inline void LObjRemoveAll(void)
{
    int i;
    for (i = 0; i < GX_MAX_LIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
}

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        while (lobj != NULL) {
            HSD_LObjDeleteCurrent(lobj);
            lobj = lobj->next;
        }
        return;
    }
    LObjRemoveAll();
}

void HSD_LObjSetCurrentAll(HSD_LObj* lobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u32 _;
#endif

    LObjRemoveAll();
    HSD_LObjAddCurrent(lobj);
}

inline void LObjReplaceAll(HSD_LObj* lobj)
{
    int i;
    HSD_LObj* cur;
    for (i = 0; i < GX_MAX_LIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
    for (cur = lobj; cur != NULL; cur = cur->next) {
        HSD_LObjAddCurrent(cur);
    }
}

void HSD_LObj_803668EC(HSD_LObj* lobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[4];
#endif

    LObjReplaceAll(lobj);
}

HSD_LObj* HSD_LObjGetCurrentByType(u16 flags)
{
    HSD_SList* cur = current_lights;
    u32 type = flags & LOBJ_TYPE_MASK;
    while (cur != NULL) {
        HSD_LObj* lobj = cur->data;
        if (type == (lobj->flags & LOBJ_TYPE_MASK)) {
            return lobj;
        }
        cur = cur->next;
    }
    return NULL;
}

s32 HSD_LightID2Index(GXLightID arg0)
{
    s32 var_r31;
    switch (arg0) {
    case GX_LIGHT0:
        var_r31 = 0;
        break;
    case GX_LIGHT1:
        var_r31 = 1;
        break;
    case GX_LIGHT2:
        var_r31 = 2;
        break;
    case GX_LIGHT3:
        var_r31 = 3;
        break;
    case GX_LIGHT4:
        var_r31 = 4;
        break;
    case GX_LIGHT5:
        var_r31 = 5;
        break;
    case GX_LIGHT6:
        var_r31 = 6;
        break;
    case GX_LIGHT7:
        var_r31 = 7;
        break;
    case 0x100:
        var_r31 = 8;
        break;
    default:
        __assert(HSD_LObj_804D5D18, 0x492U, HSD_LObj_804D5D20);

        /// @todo Find a better fix for uninitialized @c var_r31
#ifndef MUST_MATCH
        var_r31 = 0;
        break;
#endif
    }
    return var_r31;
}

s32 HSD_Index2LightID(u32 arg0)
{
    switch (arg0) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 4;
    case 3:
        return 8;
    case 4:
        return 0x10;
    case 5:
        return 0x20;
    case 6:
        return 0x40;
    case 7:
        return 0x80;
    case 8:
        return 0x100;
    default:
        return 0;
    }
}

void HSD_LObjRemoveAll(HSD_LObj* lobj)
{
    HSD_LObj* next;
    HSD_LObj* cur;

    cur = lobj;
    while (cur != NULL) {
        next = cur->next;
        HSD_LObjDeleteCurrent(cur);
        HSD_LObjUnrefThis(cur);
        cur = next;
    }
}

void HSD_LObj_80366CA4(HSD_LObj* lobj, GXColor* color)
{
    lobj->color = *color;
}

void HSD_LObj_80366CB0(HSD_LObj* lobj, GXColor* color)
{
    *color = lobj->color;
}

void HSD_LObj_80366CBC(HSD_LObj* lobj, f32 cutoff, s32 point_func)
{
    if (lobj != NULL) {
        lobj->u.point.cutoff = cutoff;
        lobj->u.point.point_func = point_func;
    }
}

void HSD_LObj_80366CD0(HSD_LObj* lobj, f32 ref_dist, f32 ref_br, s32 dist_func)
{
    if (lobj != NULL) {
        lobj->u.point.ref_dist = ref_dist;
        lobj->u.point.ref_br = ref_br;
        lobj->u.point.dist_func = dist_func;
    }
}

extern char lbl_80406190[10];

void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj == NULL) {
        __assert(HSD_LObj_804D5D18, 0x559, HSD_LObj_804D5D24);
    }
    if (lobj->position == NULL) {
        lobj->position = HSD_WObjAlloc();
        if (lobj->position == NULL) {
            __assert(HSD_LObj_804D5D18, 0x55C, "lobj->position");
        }
    }
    HSD_WObjSetPosition(lobj->position, position);
}

bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj == NULL) {
        __assert(HSD_LObj_804D5D18, 0x57D, HSD_LObj_804D5D24);
    }
    if (lobj->interest == NULL) {
        lobj->interest = HSD_WObjAlloc();
        if (lobj->interest == NULL) {
            __assert(HSD_LObj_804D5D18, 0x580, "lobj->interest");
        }
    }
    HSD_WObjSetPosition(lobj->interest, interest);
}

bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}

HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->position;
    }
    return NULL;
}

HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->interest;
    }
    return NULL;
}

#ifdef MWERKS_GEKKO
#pragma push
#pragma force_active on
static char unused1[] = "hsdIsDescendantOf(info, &hsdLObj)";
char HSD_LObj_804061D4[] = "unexpected lightdesc flags (%x)\n";
static char unused2[] = "sysdolphin_base_library";
static char unused3[] = "hsd_lobj";
#pragma pop
#endif
