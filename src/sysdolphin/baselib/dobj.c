#include "sysdolphin/baselib/dobj.h"

#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/pobj.h"

HSD_DObjInfo hsdDObj = { DObjInfoInit };

static HSD_DObjInfo* default_class = NULL;

static HSD_DObj* current_dobj = NULL;

static char lbl_804D5C78[7] = "dobj.c\0";
static char lbl_804D5C80[1] = "\0";
static char lbl_804D5C84[5] = "dobj\0";

extern char lbl_80405494[]; // "mobj has unexpected blending flags (0x%x)."
extern char lbl_80405548[]; // "sysdolphin_base_library"
extern char lbl_80405560[]; // "hsd_dobj"

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
                HSD_DObjModifyFlags_inline(dobj, 8, 0xE);
                break;
            case 0x60000000:
                HSD_DObjModifyFlags_inline(dobj, 4, 0xE);
                break;
            default:
                OSReport(lbl_80405494, dobj->mobj->rendermode);
                HSD_Panic(lbl_804D5C78, 312, lbl_804D5C80);
        }
    }
    return 0;
}

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
            __assert(lbl_804D5C78, 378, lbl_804D5C84);
        }
    }
    HSD_DOBJ_METHOD(dobj)->load(dobj, desc);

    return dobj;
}

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

// This really does match, Frank is just breaking it.
#ifdef NON_MATCHING
HSD_DObj* HSD_DObjAlloc(void)
{
    HSD_DObj* dobj = (HSD_DObj*)hsdNew((HSD_ClassInfo*)(default_class ? default_class : &hsdDObj));
    if (dobj == NULL){
        __assert(lbl_804D5C78, 525, lbl_804D5C84);
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
/* 8035E2D0 0035AEB0  80 6D BF 00 */	lwz r3, default_class
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
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass), lbl_80405548, lbl_80405560, sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

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
