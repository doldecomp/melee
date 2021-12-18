#include "sysdolphin/baselib/dobj.h"

#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/pobj.h"

extern HSD_DObjInfo hsdDObj; // hsdDObj

static HSD_DObjInfo* default_class = NULL;

static HSD_DObj* current_dobj = NULL;

extern char* lbl_80405494; // "mobj has unexpected blending flags (0x%x)."

static char lbl_804D5C78[7] = "dobj.c\0"; // "dobj.c"
static char lbl_804D5C80[1] = "";
static char lbl_804D5C84[8] = "dobj\0";

extern HSD_Class hsdClass;
extern char* lbl_80405548;

void HSD_DObjSetCurrent(HSD_DObj* dobj)
{
    current_dobj = dobj;
}

u32 HSD_DObjGetFlags(HSD_DObj* dobj)
{
    if (dobj != NULL) {
        return dobj->flags;
    }
    return 0;
}

void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj != NULL) {
        dobj->flags |= flags;
    }
}

void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj != NULL) {
        dobj->flags &= ~flags;
    }
}

void HSD_DObjModifyFlags(HSD_DObj* dobj, u32 flags, u32 mask)
{
    if (dobj == NULL)
        return;

    dobj->flags = dobj->flags & ~mask | flags & mask;
}

inline void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags)
{
    if (dobj == NULL)
        return;

    if ((flags & 2) != 0) {
        HSD_AObjRemove(dobj->aobj);
        dobj->aobj = NULL;
    }
    HSD_PObjRemoveAnimAllByFlags(dobj->pobj, flags);
    HSD_MObjRemoveAnimByFlags(dobj->mobj, flags);
}

void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, u32 flags)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;

    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjRemoveAnimByFlags(dp, flags);
    }
}

inline void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim, HSD_ShapeAnimDObj* sh_anim)
{
    HSD_ShapeAnim* shapeanim;

    if (dobj == NULL)
        return;

    if (sh_anim != NULL) {
        shapeanim = sh_anim->shapeanim;
    } else{
        shapeanim = NULL;
    }

    HSD_PObjAddAnimAll(dobj->pobj, shapeanim);
    HSD_MObjAddAnim(dobj->mobj, mat_anim);
}

void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim, HSD_ShapeAnimDObj* shapeanimdobj)
{
    HSD_DObj* dp;
    HSD_MatAnim* ma;
    HSD_ShapeAnimDObj* sd;

    if (dobj == NULL)
        return;
      
    for (dp = dobj, ma = matanim, sd = shapeanimdobj; dp != NULL; dp = dp->next, ma = next_p(ma), sd = next_p(sd)) {
        HSD_DObjAddAnim(dp, ma, sd);
    }
}

inline void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, u32 flags, f32 frame)
{
    if (dobj == NULL)
        return;

    HSD_PObjReqAnimAllByFlags(dobj->pobj, flags, frame);
    HSD_MObjReqAnimByFlags(dobj->mobj, flags, frame);
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, u32 flags, f32 frame)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;
        
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, flags, frame);
    }
}

void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 frame)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;
    
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, 0x7FF, frame);
    }
}

inline void HSD_DObjAnim(HSD_DObj* dobj)
{
    if (dobj == NULL)
        return;

    HSD_PObjAnimAll(dobj->pobj);
    HSD_MObjAnim(dobj->mobj);
}

void HSD_DObjAnimAll(HSD_DObj* dobj)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;
    
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjAnim(dp);
    }
}

inline void HSD_DObjModifyFlags_inline(HSD_DObj* dobj, u32 flags, u32 mask)
{
    if (dobj == NULL)
        return;

    dobj->flags = dobj->flags & ~mask | flags & mask;
}

// Non-matching due to section of the strings
#ifdef NON_MATCHING
static int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    dobj->next = HSD_DObjLoadDesc(desc->next);
    dobj->mobj = HSD_MObjLoadDesc(desc->mobjdesc);
    dobj->pobj = HSD_PObjLoadDesc(desc->pobjdesc);

    if (dobj->mobj != NULL) {
        switch (dobj->mobj->rendermode & 0x60000000) {
            case 0:
                HSD_DObjModifyFlags_inline(dobj, 2, 0xE);
                break;
            case 0x40000000:
                HSD_DObjModifyFlags_inline(dobj, 4, 0xE);
                break;
            case 0x60000000:
                HSD_DObjModifyFlags_inline(dobj, 8, 0xE);
                break;
            default:
                OSReport(lbl_80405494);
                HSD_Panic("dobj.c", 312, NULL);
        }
    }
    return 0;
}
#else
asm int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    nofralloc
/* 8035E0A4 0035AC84  7C 08 02 A6 */	mflr r0
/* 8035E0A8 0035AC88  90 01 00 04 */	stw r0, 4(r1)
/* 8035E0AC 0035AC8C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8035E0B0 0035AC90  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8035E0B4 0035AC94  3B E4 00 00 */	addi r31, r4, 0
/* 8035E0B8 0035AC98  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8035E0BC 0035AC9C  3B C3 00 00 */	addi r30, r3, 0
/* 8035E0C0 0035ACA0  80 64 00 04 */	lwz r3, 4(r4)
/* 8035E0C4 0035ACA4  48 00 00 F1 */	bl HSD_DObjLoadDesc
/* 8035E0C8 0035ACA8  90 7E 00 04 */	stw r3, 4(r30)
/* 8035E0CC 0035ACAC  80 7F 00 08 */	lwz r3, 8(r31)
/* 8035E0D0 0035ACB0  48 00 51 15 */	bl HSD_MObjLoadDesc
/* 8035E0D4 0035ACB4  90 7E 00 08 */	stw r3, 8(r30)
/* 8035E0D8 0035ACB8  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 8035E0DC 0035ACBC  48 00 DD 89 */	bl HSD_PObjLoadDesc
/* 8035E0E0 0035ACC0  90 7E 00 0C */	stw r3, 0xc(r30)
/* 8035E0E4 0035ACC4  80 7E 00 08 */	lwz r3, 8(r30)
/* 8035E0E8 0035ACC8  28 03 00 00 */	cmplwi r3, 0
/* 8035E0EC 0035ACCC  41 82 00 AC */	beq lbl_8035E198
/* 8035E0F0 0035ACD0  80 83 00 04 */	lwz r4, 4(r3)
/* 8035E0F4 0035ACD4  3C 00 40 00 */	lis r0, 0x4000
/* 8035E0F8 0035ACD8  54 83 00 44 */	rlwinm r3, r4, 0, 1, 2
/* 8035E0FC 0035ACDC  7C 03 00 00 */	cmpw r3, r0
/* 8035E100 0035ACE0  41 82 00 40 */	beq lbl_8035E140
/* 8035E104 0035ACE4  40 80 00 10 */	bge lbl_8035E114
/* 8035E108 0035ACE8  2C 03 00 00 */	cmpwi r3, 0
/* 8035E10C 0035ACEC  41 82 00 18 */	beq lbl_8035E124
/* 8035E110 0035ACF0  48 00 00 68 */	b lbl_8035E178
lbl_8035E114:
/* 8035E114 0035ACF4  3C 00 60 00 */	lis r0, 0x6000
/* 8035E118 0035ACF8  7C 03 00 00 */	cmpw r3, r0
/* 8035E11C 0035ACFC  41 82 00 40 */	beq lbl_8035E15C
/* 8035E120 0035AD00  48 00 00 58 */	b lbl_8035E178
lbl_8035E124:
/* 8035E124 0035AD04  28 1E 00 00 */	cmplwi r30, 0
/* 8035E128 0035AD08  41 82 00 70 */	beq lbl_8035E198
/* 8035E12C 0035AD0C  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8035E130 0035AD10  54 00 07 F6 */	rlwinm r0, r0, 0, 0x1f, 0x1b
/* 8035E134 0035AD14  60 00 00 02 */	ori r0, r0, 2
/* 8035E138 0035AD18  90 1E 00 14 */	stw r0, 0x14(r30)
/* 8035E13C 0035AD1C  48 00 00 5C */	b lbl_8035E198
lbl_8035E140:
/* 8035E140 0035AD20  28 1E 00 00 */	cmplwi r30, 0
/* 8035E144 0035AD24  41 82 00 54 */	beq lbl_8035E198
/* 8035E148 0035AD28  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8035E14C 0035AD2C  54 00 07 F6 */	rlwinm r0, r0, 0, 0x1f, 0x1b
/* 8035E150 0035AD30  60 00 00 08 */	ori r0, r0, 8
/* 8035E154 0035AD34  90 1E 00 14 */	stw r0, 0x14(r30)
/* 8035E158 0035AD38  48 00 00 40 */	b lbl_8035E198
lbl_8035E15C:
/* 8035E15C 0035AD3C  28 1E 00 00 */	cmplwi r30, 0
/* 8035E160 0035AD40  41 82 00 38 */	beq lbl_8035E198
/* 8035E164 0035AD44  80 1E 00 14 */	lwz r0, 0x14(r30)
/* 8035E168 0035AD48  54 00 07 F6 */	rlwinm r0, r0, 0, 0x1f, 0x1b
/* 8035E16C 0035AD4C  60 00 00 04 */	ori r0, r0, 4
/* 8035E170 0035AD50  90 1E 00 14 */	stw r0, 0x14(r30)
/* 8035E174 0035AD54  48 00 00 24 */	b lbl_8035E198
lbl_8035E178:
/* 8035E178 0035AD58  3C 60 80 40 */	lis r3, lbl_80405494@ha
/* 8035E17C 0035AD5C  4C C6 31 82 */	crclr 6
/* 8035E180 0035AD60  38 63 54 94 */	addi r3, r3, lbl_80405494@l
/* 8035E184 0035AD64  4B FE 75 25 */	bl OSReport
/* 8035E188 0035AD68  38 6D A5 D8 */	addi r3, r13, lbl_804D5C78
/* 8035E18C 0035AD6C  38 80 01 38 */	li r4, 0x138
/* 8035E190 0035AD70  38 AD A5 E0 */	addi r5, r13, lbl_804D5C80
/* 8035E194 0035AD74  48 02 A0 E5 */	bl HSD_Panic
lbl_8035E198:
/* 8035E198 0035AD78  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8035E19C 0035AD7C  38 60 00 00 */	li r3, 0
/* 8035E1A0 0035AD80  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8035E1A4 0035AD84  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8035E1A8 0035AD88  38 21 00 18 */	addi r1, r1, 0x18
/* 8035E1AC 0035AD8C  7C 08 03 A6 */	mtlr r0
/* 8035E1B0 0035AD90  4E 80 00 20 */	blr 
}
#endif

// Non-matching due to sections
#ifdef NON_MATCHING
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc)
{
    HSD_DObj* dobj;

    if (desc == NULL)
        return NULL;
    
    if (desc->class_name == NULL || hsdSearchClassInfo(desc->class_name) == NULL) {
        dobj = HSD_DObjAlloc();
    }else {
        dobj = HSD_DOBJ(hsdNew());
        if (dobj == NULL) {
            __assert("dobj.c", 378, lbl_804D5C84);
        }
    }
    HSD_DOBJ_METHOD(dobj)->load(dobj, desc);

    return dobj;
}
#else
asm HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc) 
{
    nofralloc
/* 8035E1B4 0035AD94  7C 08 02 A6 */	mflr r0
/* 8035E1B8 0035AD98  90 01 00 04 */	stw r0, 4(r1)
/* 8035E1BC 0035AD9C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8035E1C0 0035ADA0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8035E1C4 0035ADA4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8035E1C8 0035ADA8  7C 7E 1B 79 */	or. r30, r3, r3
/* 8035E1CC 0035ADAC  40 82 00 0C */	bne lbl_8035E1D8
/* 8035E1D0 0035ADB0  38 60 00 00 */	li r3, 0
/* 8035E1D4 0035ADB4  48 00 00 60 */	b lbl_8035E234
lbl_8035E1D8:
/* 8035E1D8 0035ADB8  80 7E 00 00 */	lwz r3, 0(r30)
/* 8035E1DC 0035ADBC  28 03 00 00 */	cmplwi r3, 0
/* 8035E1E0 0035ADC0  41 82 00 10 */	beq lbl_8035E1F0
/* 8035E1E4 0035ADC4  48 02 46 31 */	bl hsdSearchClassInfo
/* 8035E1E8 0035ADC8  28 03 00 00 */	cmplwi r3, 0
/* 8035E1EC 0035ADCC  40 82 00 10 */	bne lbl_8035E1FC
lbl_8035E1F0:
/* 8035E1F0 0035ADD0  48 00 00 D1 */	bl HSD_DObjAlloc
/* 8035E1F4 0035ADD4  7C 7F 1B 78 */	mr r31, r3
/* 8035E1F8 0035ADD8  48 00 00 20 */	b lbl_8035E218
lbl_8035E1FC:
/* 8035E1FC 0035ADDC  48 02 41 49 */	bl hsdNew
/* 8035E200 0035ADE0  7C 7F 1B 79 */	or. r31, r3, r3
/* 8035E204 0035ADE4  40 82 00 14 */	bne lbl_8035E218
/* 8035E208 0035ADE8  38 6D A5 D8 */	addi r3, r13, lbl_804D5C78
/* 8035E20C 0035ADEC  38 80 01 7A */	li r4, 0x17a
/* 8035E210 0035ADF0  38 AD A5 E4 */	addi r5, r13, lbl_804D5C84
/* 8035E214 0035ADF4  48 02 A0 0D */	bl __assert
lbl_8035E218:
/* 8035E218 0035ADF8  80 BF 00 00 */	lwz r5, 0(r31)
/* 8035E21C 0035ADFC  38 7F 00 00 */	addi r3, r31, 0
/* 8035E220 0035AE00  38 9E 00 00 */	addi r4, r30, 0
/* 8035E224 0035AE04  81 85 00 40 */	lwz r12, 0x40(r5)
/* 8035E228 0035AE08  7D 88 03 A6 */	mtlr r12
/* 8035E22C 0035AE0C  4E 80 00 21 */	blrl 
/* 8035E230 0035AE10  7F E3 FB 78 */	mr r3, r31
lbl_8035E234:
/* 8035E234 0035AE14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8035E238 0035AE18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8035E23C 0035AE1C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8035E240 0035AE20  38 21 00 18 */	addi r1, r1, 0x18
/* 8035E244 0035AE24  7C 08 03 A6 */	mtlr r0
/* 8035E248 0035AE28  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
inline void hsdDelete(void* object)
{
    if (object == NULL)
        return;

    HSD_CLASS_METHOD(object)->release((HSD_Class*)object);
    HSD_CLASS_METHOD(object)->destroy((HSD_Class*)object);
}

inline void HSD_DObjRemove(HSD_DObj* dobj)
{
    hsdDelete(dobj);
}

void HSD_DObjRemoveAll(HSD_DObj* dobj)
{
    HSD_DObj* next;
    
    for (; dobj != NULL; dobj = next) {
        next = dobj->next;
        HSD_DObjRemove(dobj);
    }
}
#pragma pop

#ifdef NON_MATCHING
HSD_DObj* HSD_DObjAlloc(void)
{
    HSD_DObj* dobj = (HSD_DObj*)hsdNew((HSD_ClassInfo*)(default_class ? default_class : &hsdDObj));
    if (dobj == NULL){
        __assert("dobj.c", 0x20D, lbl_804D5C84);
    }
    return dobj;
}
#else
asm HSD_DObj* HSD_DObjAlloc(void)
{
    nofralloc
/* 8035E2C0 0035AEA0  7C 08 02 A6 */	mflr r0
/* 8035E2C4 0035AEA4  90 01 00 04 */	stw r0, 4(r1)
/* 8035E2C8 0035AEA8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8035E2CC 0035AEAC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8035E2D0 0035AEB0  80 6D BF 00 */	lwz r3, default_class(r13)
/* 8035E2D4 0035AEB4  28 03 00 00 */	cmplwi r3, 0
/* 8035E2D8 0035AEB8  41 82 00 08 */	beq lbl_8035E2E0
/* 8035E2DC 0035AEBC  48 00 00 0C */	b lbl_8035E2E8
lbl_8035E2E0:
/* 8035E2E0 0035AEC0  3C 60 80 40 */	lis r3, hsdDObj@ha
/* 8035E2E4 0035AEC4  38 63 54 50 */	addi r3, r3, hsdDObj@l
lbl_8035E2E8:
/* 8035E2E8 0035AEC8  48 02 40 5D */	bl hsdNew
/* 8035E2EC 0035AECC  7C 7F 1B 79 */	or. r31, r3, r3
/* 8035E2F0 0035AED0  40 82 00 14 */	bne lbl_8035E304
/* 8035E2F4 0035AED4  38 6D A5 D8 */	addi r3, r13, lbl_804D5C78
/* 8035E2F8 0035AED8  38 80 02 0D */	li r4, 0x20d
/* 8035E2FC 0035AEDC  38 AD A5 E4 */	addi r5, r13, lbl_804D5C84
/* 8035E300 0035AEE0  48 02 9F 21 */	bl __assert
lbl_8035E304:
/* 8035E304 0035AEE4  7F E3 FB 78 */	mr r3, r31
/* 8035E308 0035AEE8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8035E30C 0035AEEC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8035E310 0035AEF0  38 21 00 10 */	addi r1, r1, 0x10
/* 8035E314 0035AEF4  7C 08 03 A6 */	mtlr r0
/* 8035E318 0035AEF8  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
inline void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    if (dobj == NULL || desc == NULL)
       return;
    HSD_PObjResolveRefsAll(dobj->pobj, desc->pobjdesc);
}

void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    for (; dobj != NULL && desc != NULL; dobj = dobj->next, desc = desc->next) {
        HSD_DObjResolveRefs(dobj, desc);
    }
}

void HSD_DObjDisp(HSD_DObj* dobj, Mtx vmtx, Mtx pmtx, u32 rendermode)
{
    HSD_PObj* p;

    HSD_MObjSetCurrent(dobj->mobj);
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->setup(dobj->mobj, rendermode);
    }
    for (p = dobj->pobj; p != NULL; p = p->next) {
        HSD_POBJ_METHOD(p)->disp(p, vmtx, pmtx, rendermode);
    }
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->unset(dobj->mobj, rendermode);
    }
    HSD_MObjSetCurrent(NULL);
}

static void DObjRelease(HSD_Class* o)
{
    HSD_DObj* dobj = HSD_DOBJ(o);

    HSD_MObjRemove(dobj->mobj);
    HSD_PObjRemoveAll(dobj->pobj);
    HSD_AObjRemove(dobj->aobj);

    HSD_PARENT_INFO(&hsdDObj)->release(o);
}

static void DObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    HSD_PARENT_INFO(&hsdDObj)->amnesia(info);
}
#pragma pop

// Non-matching because a mess of externs
#ifdef NON_MATCHING
static void DObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass), lbl_80405548, "hsd_dobj", sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

    HSD_PARENT_INFO(&hsdDObj)->release = DObjRelease;
    HSD_PARENT_INFO(&hsdDObj)->amnesia = DObjAmnesia;
    HSD_DOBJ_INFO(&hsdDObj)->disp = HSD_DObjDisp;
    HSD_DOBJ_INFO(&hsdDObj)->load = DObjLoad;
}
#else
asm void DObjInfoInit(void)
{
    nofralloc
/* 8035E4E4 0035B0C4  7C 08 02 A6 */	mflr r0
/* 8035E4E8 0035B0C8  3C 60 80 40 */	lis r3, hsdDObj@ha
/* 8035E4EC 0035B0CC  90 01 00 04 */	stw r0, 4(r1)
/* 8035E4F0 0035B0D0  38 E0 00 44 */	li r7, 0x44
/* 8035E4F4 0035B0D4  39 00 00 18 */	li r8, 0x18
/* 8035E4F8 0035B0D8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8035E4FC 0035B0DC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8035E500 0035B0E0  3B E3 54 50 */	addi r31, r3, hsdDObj@l
/* 8035E504 0035B0E4  3C 60 80 40 */	lis r3, hsdClass@ha
/* 8035E508 0035B0E8  38 83 75 90 */	addi r4, r3, hsdClass@l
/* 8035E50C 0035B0EC  38 7F 00 00 */	addi r3, r31, 0
/* 8035E510 0035B0F0  38 BF 00 F8 */	addi r5, r31, 0xf8
/* 8035E514 0035B0F4  38 DF 01 10 */	addi r6, r31, 0x110
/* 8035E518 0035B0F8  48 02 37 01 */	bl hsdInitClassInfo
/* 8035E51C 0035B0FC  3C 60 80 36 */	lis r3, DObjRelease@ha
/* 8035E520 0035B100  38 03 E4 40 */	addi r0, r3, DObjRelease@l
/* 8035E524 0035B104  3C 60 80 36 */	lis r3, DObjAmnesia@ha
/* 8035E528 0035B108  90 1F 00 30 */	stw r0, 0x30(r31)
/* 8035E52C 0035B10C  38 03 E4 9C */	addi r0, r3, DObjAmnesia@l
/* 8035E530 0035B110  3C 60 80 36 */	lis r3, HSD_DObjDisp@ha
/* 8035E534 0035B114  90 1F 00 38 */	stw r0, 0x38(r31)
/* 8035E538 0035B118  38 03 E3 88 */	addi r0, r3, HSD_DObjDisp@l
/* 8035E53C 0035B11C  3C 60 80 36 */	lis r3, DObjLoad@ha
/* 8035E540 0035B120  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 8035E544 0035B124  38 03 E0 A4 */	addi r0, r3, DObjLoad@l
/* 8035E548 0035B128  90 1F 00 40 */	stw r0, 0x40(r31)
/* 8035E54C 0035B12C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8035E550 0035B130  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8035E554 0035B134  38 21 00 10 */	addi r1, r1, 0x10
/* 8035E558 0035B138  7C 08 03 A6 */	mtlr r0
/* 8035E55C 0035B13C  4E 80 00 20 */	blr 
}
#endif
