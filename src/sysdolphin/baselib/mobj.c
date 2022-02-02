#include "sysdolphin/baselib/mobj.h"

#include "sysdolphin/baselib/memory.h"

extern void MObjInfoInit(void);

HSD_MObjInfo hsdMObj = { MObjInfoInit };

extern HSD_MObjInfo* default_class;

extern HSD_MObj* current_mobj;

extern char* lbl_804D5CE0;
extern char* lbl_804D5CE8;

extern const f32 lbl_804DE430; // 1.0F

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
        mobj->mat->alpha = lbl_804DE430 - val->fv;
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

void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj == NULL)
        return;
    HSD_AObjInterpretAnim(mobj->aobj, mobj, MObjUpdateFunc);
    HSD_TObjAnimAll(mobj->tobj);
}

/*static*/ int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

// Non-matching due to extern'd assert strings
#ifdef NON_MATCHING
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name || !(info = hsdSearchClassInfo(mobjdesc->class_name))) {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            if (mobj == NULL) {
                __assert(lbl_804D5CE0, 353, lbl_804D5CE8);
            }
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}
#else
asm HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    nofralloc
/* 803631E4 0035FDC4  7C 08 02 A6 */	mflr r0
/* 803631E8 0035FDC8  90 01 00 04 */	stw r0, 4(r1)
/* 803631EC 0035FDCC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803631F0 0035FDD0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803631F4 0035FDD4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803631F8 0035FDD8  7C 7E 1B 79 */	or. r30, r3, r3
/* 803631FC 0035FDDC  41 82 00 6C */	beq lbl_80363268
/* 80363200 0035FDE0  80 7E 00 00 */	lwz r3, 0(r30)
/* 80363204 0035FDE4  28 03 00 00 */	cmplwi r3, 0
/* 80363208 0035FDE8  41 82 00 10 */	beq lbl_80363218
/* 8036320C 0035FDEC  48 01 F6 09 */	bl hsdSearchClassInfo
/* 80363210 0035FDF0  28 03 00 00 */	cmplwi r3, 0
/* 80363214 0035FDF4  40 82 00 10 */	bne lbl_80363224
lbl_80363218:
/* 80363218 0035FDF8  48 00 0A 8D */	bl HSD_MObjAlloc
/* 8036321C 0035FDFC  7C 7F 1B 78 */	mr r31, r3
/* 80363220 0035FE00  48 00 00 20 */	b lbl_80363240
lbl_80363224:
/* 80363224 0035FE04  48 01 F1 21 */	bl hsdNew
/* 80363228 0035FE08  7C 7F 1B 79 */	or. r31, r3, r3
/* 8036322C 0035FE0C  40 82 00 14 */	bne lbl_80363240
/* 80363230 0035FE10  38 6D A6 40 */	addi r3, r13, lbl_804D5CE0
/* 80363234 0035FE14  38 80 01 61 */	li r4, 0x161
/* 80363238 0035FE18  38 AD A6 48 */	addi r5, r13, lbl_804D5CE8
/* 8036323C 0035FE1C  48 02 4F E5 */	bl __assert
lbl_80363240:
/* 80363240 0035FE20  80 BF 00 00 */	lwz r5, 0(r31)
/* 80363244 0035FE24  38 7F 00 00 */	addi r3, r31, 0
/* 80363248 0035FE28  38 9E 00 00 */	addi r4, r30, 0
/* 8036324C 0035FE2C  81 85 00 40 */	lwz r12, 0x40(r5)
/* 80363250 0035FE30  7D 88 03 A6 */	mtlr r12
/* 80363254 0035FE34  4E 80 00 21 */	blrl 
/* 80363258 0035FE38  7F E3 FB 78 */	mr r3, r31
/* 8036325C 0035FE3C  48 00 06 31 */	bl HSD_MObjCompileTev
/* 80363260 0035FE40  7F E3 FB 78 */	mr r3, r31
/* 80363264 0035FE44  48 00 00 08 */	b lbl_8036326C
lbl_80363268:
/* 80363268 0035FE48  38 60 00 00 */	li r3, 0
lbl_8036326C:
/* 8036326C 0035FE4C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80363270 0035FE50  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80363274 0035FE54  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80363278 0035FE58  38 21 00 18 */	addi r1, r1, 0x18
/* 8036327C 0035FE5C  7C 08 03 A6 */	mtlr r0
/* 80363280 0035FE60  4E 80 00 20 */	blr 
}
#endif
