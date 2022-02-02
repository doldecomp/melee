#include "sysdolphin/baselib/mobj.h"

/*extern void MObjInfoInit(void);

HSD_MObjInfo hsdMObj = { MObjInfoInit };*/

extern void* jtbl_80405E78;
extern f32 lbl_804DE428;
extern f32 lbl_804DE430;

extern HSD_MObj* current_mobj;

void HSD_MObjSetCurrent(HSD_MObj* mobj)
{
    current_mobj = mobj;
}

void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) 
        mobj->rendermode |= flags;
}

void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) 
        mobj->rendermode &= ~flags;
}

void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj == NULL)
        return;

    if (flags & MOBJ_ANIM) {
        HSD_AObjRemove(mobj->aobj);
        mobj->aobj = NULL;
    }
    if (flags & TOBJ_ANIM) {
        HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}

void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL)
        return;

    if (matanim != NULL) {
        if (mobj->aobj != NULL) {
            HSD_AObjRemove(mobj->aobj);
        }
        mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
    }
}

void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL)
        return;
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

void HSD_MObjReqAnim(HSD_MObj *mobj, f32 startframe)
{
    HSD_MObjReqAnimByFlags(mobj, startframe, ALL_ANIM);
}

// Non-matching due to data ordering preventing the jump table from being inserted right now
#ifdef NON_MATCHING
static void MObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    HSD_MObj* mobj = obj;

    if (mobj == NULL)
        return;

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        mobj->mat->ambient.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_AMBIENT_G:
        mobj->mat->ambient.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_AMBIENT_B:
        mobj->mat->ambient.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_R:
        mobj->mat->diffuse.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_G:
        mobj->mat->diffuse.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_DIFFUSE_B:
        mobj->mat->diffuse.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_ALPHA:
        mobj->mat->alpha = 1.0F - val->fv;
        break;
    case HSD_A_M_SPECULAR_R:
        mobj->mat->specular.r = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_SPECULAR_G:
        mobj->mat->specular.g = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_SPECULAR_B:
        mobj->mat->specular.b = (u8)(255.0 * val->fv);
        break;
    case HSD_A_M_PE_REF0:
        if (mobj->pe) {
            mobj->pe->ref0 = (u8)(255.0 * val->fv);
        }
        break;
    case HSD_A_M_PE_REF1:
        if (mobj->pe) {
            mobj->pe->ref1 = (u8)(255.0 * val->fv);
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        if (mobj->pe) {
            mobj->pe->dst_alpha = (u8)(255.0 * val->fv);
        }
        break;
    }
}
#else
asm void MObjUpdateFunc(void* obj, u32 type, FObjData* val)
{
    nofralloc
/* 80362EEC 0035FACC  28 03 00 00 */	cmplwi r3, 0
/* 80362EF0 0035FAD0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80362EF4 0035FAD4  41 82 02 00 */	beq lbl_803630F4
/* 80362EF8 0035FAD8  28 04 00 0D */	cmplwi r4, 0xd
/* 80362EFC 0035FADC  41 81 01 F8 */	bgt lbl_803630F4
/* 80362F00 0035FAE0  3C C0 80 40 */	lis r6, jtbl_80405E78@ha
/* 80362F04 0035FAE4  38 C6 5E 78 */	addi r6, r6, jtbl_80405E78@l
/* 80362F08 0035FAE8  54 80 10 3A */	slwi r0, r4, 2
/* 80362F0C 0035FAEC  7C 06 00 2E */	lwzx r0, r6, r0
/* 80362F10 0035FAF0  7C 09 03 A6 */	mtctr r0
/* 80362F14 0035FAF4  4E 80 04 20 */	bctr 
lbl_80362F18:
/* 80362F18 0035FAF8  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362F1C 0035FAFC  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362F20 0035FB00  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362F24 0035FB04  FC 01 00 32 */	fmul f0, f1, f0
/* 80362F28 0035FB08  FC 00 00 1E */	fctiwz f0, f0
/* 80362F2C 0035FB0C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362F30 0035FB10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362F34 0035FB14  98 03 00 00 */	stb r0, 0(r3)
/* 80362F38 0035FB18  48 00 01 BC */	b lbl_803630F4
lbl_80362F3C:
/* 80362F3C 0035FB1C  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362F40 0035FB20  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362F44 0035FB24  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362F48 0035FB28  FC 01 00 32 */	fmul f0, f1, f0
/* 80362F4C 0035FB2C  FC 00 00 1E */	fctiwz f0, f0
/* 80362F50 0035FB30  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362F54 0035FB34  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362F58 0035FB38  98 03 00 01 */	stb r0, 1(r3)
/* 80362F5C 0035FB3C  48 00 01 98 */	b lbl_803630F4
lbl_80362F60:
/* 80362F60 0035FB40  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362F64 0035FB44  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362F68 0035FB48  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362F6C 0035FB4C  FC 01 00 32 */	fmul f0, f1, f0
/* 80362F70 0035FB50  FC 00 00 1E */	fctiwz f0, f0
/* 80362F74 0035FB54  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362F78 0035FB58  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362F7C 0035FB5C  98 03 00 02 */	stb r0, 2(r3)
/* 80362F80 0035FB60  48 00 01 74 */	b lbl_803630F4
lbl_80362F84:
/* 80362F84 0035FB64  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362F88 0035FB68  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362F8C 0035FB6C  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362F90 0035FB70  FC 01 00 32 */	fmul f0, f1, f0
/* 80362F94 0035FB74  FC 00 00 1E */	fctiwz f0, f0
/* 80362F98 0035FB78  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362F9C 0035FB7C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362FA0 0035FB80  98 03 00 04 */	stb r0, 4(r3)
/* 80362FA4 0035FB84  48 00 01 50 */	b lbl_803630F4
lbl_80362FA8:
/* 80362FA8 0035FB88  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362FAC 0035FB8C  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362FB0 0035FB90  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362FB4 0035FB94  FC 01 00 32 */	fmul f0, f1, f0
/* 80362FB8 0035FB98  FC 00 00 1E */	fctiwz f0, f0
/* 80362FBC 0035FB9C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362FC0 0035FBA0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362FC4 0035FBA4  98 03 00 05 */	stb r0, 5(r3)
/* 80362FC8 0035FBA8  48 00 01 2C */	b lbl_803630F4
lbl_80362FCC:
/* 80362FCC 0035FBAC  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80362FD0 0035FBB0  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362FD4 0035FBB4  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362FD8 0035FBB8  FC 01 00 32 */	fmul f0, f1, f0
/* 80362FDC 0035FBBC  FC 00 00 1E */	fctiwz f0, f0
/* 80362FE0 0035FBC0  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80362FE4 0035FBC4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80362FE8 0035FBC8  98 03 00 06 */	stb r0, 6(r3)
/* 80362FEC 0035FBCC  48 00 01 08 */	b lbl_803630F4
lbl_80362FF0:
/* 80362FF0 0035FBD0  C0 22 EA 50 */	lfs f1, lbl_804DE430(r2)
/* 80362FF4 0035FBD4  C0 05 00 00 */	lfs f0, 0(r5)
/* 80362FF8 0035FBD8  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80362FFC 0035FBDC  EC 01 00 28 */	fsubs f0, f1, f0
/* 80363000 0035FBE0  D0 03 00 0C */	stfs f0, 0xc(r3)
/* 80363004 0035FBE4  48 00 00 F0 */	b lbl_803630F4
lbl_80363008:
/* 80363008 0035FBE8  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 8036300C 0035FBEC  C0 05 00 00 */	lfs f0, 0(r5)
/* 80363010 0035FBF0  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80363014 0035FBF4  FC 01 00 32 */	fmul f0, f1, f0
/* 80363018 0035FBF8  FC 00 00 1E */	fctiwz f0, f0
/* 8036301C 0035FBFC  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80363020 0035FC00  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80363024 0035FC04  98 03 00 08 */	stb r0, 8(r3)
/* 80363028 0035FC08  48 00 00 CC */	b lbl_803630F4
lbl_8036302C:
/* 8036302C 0035FC0C  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80363030 0035FC10  C0 05 00 00 */	lfs f0, 0(r5)
/* 80363034 0035FC14  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80363038 0035FC18  FC 01 00 32 */	fmul f0, f1, f0
/* 8036303C 0035FC1C  FC 00 00 1E */	fctiwz f0, f0
/* 80363040 0035FC20  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80363044 0035FC24  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80363048 0035FC28  98 03 00 09 */	stb r0, 9(r3)
/* 8036304C 0035FC2C  48 00 00 A8 */	b lbl_803630F4
lbl_80363050:
/* 80363050 0035FC30  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80363054 0035FC34  C0 05 00 00 */	lfs f0, 0(r5)
/* 80363058 0035FC38  80 63 00 0C */	lwz r3, 0xc(r3)
/* 8036305C 0035FC3C  FC 01 00 32 */	fmul f0, f1, f0
/* 80363060 0035FC40  FC 00 00 1E */	fctiwz f0, f0
/* 80363064 0035FC44  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80363068 0035FC48  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8036306C 0035FC4C  98 03 00 0A */	stb r0, 0xa(r3)
/* 80363070 0035FC50  48 00 00 84 */	b lbl_803630F4
lbl_80363074:
/* 80363074 0035FC54  80 63 00 10 */	lwz r3, 0x10(r3)
/* 80363078 0035FC58  28 03 00 00 */	cmplwi r3, 0
/* 8036307C 0035FC5C  41 82 00 78 */	beq lbl_803630F4
/* 80363080 0035FC60  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 80363084 0035FC64  C0 05 00 00 */	lfs f0, 0(r5)
/* 80363088 0035FC68  FC 01 00 32 */	fmul f0, f1, f0
/* 8036308C 0035FC6C  FC 00 00 1E */	fctiwz f0, f0
/* 80363090 0035FC70  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80363094 0035FC74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80363098 0035FC78  98 03 00 01 */	stb r0, 1(r3)
/* 8036309C 0035FC7C  48 00 00 58 */	b lbl_803630F4
lbl_803630A0:
/* 803630A0 0035FC80  80 63 00 10 */	lwz r3, 0x10(r3)
/* 803630A4 0035FC84  28 03 00 00 */	cmplwi r3, 0
/* 803630A8 0035FC88  41 82 00 4C */	beq lbl_803630F4
/* 803630AC 0035FC8C  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 803630B0 0035FC90  C0 05 00 00 */	lfs f0, 0(r5)
/* 803630B4 0035FC94  FC 01 00 32 */	fmul f0, f1, f0
/* 803630B8 0035FC98  FC 00 00 1E */	fctiwz f0, f0
/* 803630BC 0035FC9C  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 803630C0 0035FCA0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803630C4 0035FCA4  98 03 00 02 */	stb r0, 2(r3)
/* 803630C8 0035FCA8  48 00 00 2C */	b lbl_803630F4
lbl_803630CC:
/* 803630CC 0035FCAC  80 63 00 10 */	lwz r3, 0x10(r3)
/* 803630D0 0035FCB0  28 03 00 00 */	cmplwi r3, 0
/* 803630D4 0035FCB4  41 82 00 20 */	beq lbl_803630F4
/* 803630D8 0035FCB8  C8 22 EA 48 */	lfd f1, lbl_804DE428(r2)
/* 803630DC 0035FCBC  C0 05 00 00 */	lfs f0, 0(r5)
/* 803630E0 0035FCC0  FC 01 00 32 */	fmul f0, f1, f0
/* 803630E4 0035FCC4  FC 00 00 1E */	fctiwz f0, f0
/* 803630E8 0035FCC8  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 803630EC 0035FCCC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803630F0 0035FCD0  98 03 00 03 */	stb r0, 3(r3)
lbl_803630F4:
/* 803630F4 0035FCD4  38 21 00 20 */	addi r1, r1, 0x20
/* 803630F8 0035FCD8  4E 80 00 20 */	blr 
}
#endif
