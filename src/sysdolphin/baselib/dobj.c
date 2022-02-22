#include "sysdolphin/baselib/dobj.h"

#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/pobj.h"

static void DObjInfoInit(void);
HSD_DObjInfo hsdDObj = { DObjInfoInit };

static HSD_DObjInfo* default_class = NULL;

static HSD_DObj* current_dobj = NULL;

static char lbl_804D5C78[7] = "dobj.c\0";

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

void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, u32 flags)
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

void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim, HSD_ShapeAnimDObj* sh_anim)
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

void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, f32 startframe, u32 flags)
{
    if (dobj == NULL)
        return;

    HSD_PObjReqAnimAllByFlags(dobj->pobj, startframe, flags);
    HSD_MObjReqAnimByFlags(dobj->mobj, startframe, flags);
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, f32 startframe, u32 flags)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;
        
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe, flags);
    }
}

void HSD_DObjReqAnimAll(HSD_DObj* dobj, f32 startframe)
{
    HSD_DObj* dp;

    if (dobj == NULL)
        return;
    
    for (dp = dobj; dp != NULL; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe,  0x7FF);
    }
}

void HSD_DObjAnim(HSD_DObj* dobj)
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

static int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    dobj->next = HSD_DObjLoadDesc(desc->next);
    dobj->mobj = HSD_MObjLoadDesc(desc->mobjdesc);
    dobj->pobj = HSD_PObjLoadDesc(desc->pobjdesc);

    if (dobj->mobj != NULL) {
        switch (dobj->mobj->rendermode & 0x60000000) {
            case 0:
                HSD_DObjModifyFlags(dobj, 2, 0xE);
                break;
            case 0x40000000:
                HSD_DObjModifyFlags(dobj, 8, 0xE);
                break;
            case 0x60000000:
                HSD_DObjModifyFlags(dobj, 4, 0xE);
                break;
            default:
                OSReport("mobj has unexpected blending flags (0x%x).", dobj->mobj->rendermode);
                HSD_Panic(lbl_804D5C78, 312, "\0");
        }
    }
    return 0;
}

static char lbl_804D5C84[5] = "dobj\0";

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

void HSD_DObjRemove(HSD_DObj* dobj)
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

void HSD_DObjSetDefaultClass(HSD_DObjInfo* info)
{
    if (info) {
        if (!hsdIsDescendantOf(info, &hsdDObj)) {
            __assert(lbl_804D5C78, 498, "hsdIsDescendantOf(info, &hsdDObj)"); // The line number here is totally made up, this function is removed in practice but the string isn't
        }
    }
    default_class = info;
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
void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc)
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

void forceStringAllocation(HSD_DObj* dobj, HSD_MObj* mobj) // This function exists for the sole purpose of causing strings to end up in data by the compiler despite not being used
{
    if (dobj->pobj == NULL) 
    {
        __assert(lbl_804D5C78, 700, "can not find specified pobj in link.\n");
    }
    if (dobj->pobj == NULL) 
    {
        __assert(lbl_804D5C78, 702, "can not find specified pobj in link.");
    }
    if (dobj->mobj != mobj) 
    {
        __assert(lbl_804D5C78, 704, "dobj->mobj == mobj");
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

static void DObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass), "sysdolphin_base_library", "hsd_dobj", sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

    HSD_CLASS_INFO(&hsdDObj)->release = DObjRelease;
    HSD_CLASS_INFO(&hsdDObj)->amnesia = DObjAmnesia;
    HSD_DOBJ_INFO(&hsdDObj)->disp = HSD_DObjDisp;
    HSD_DOBJ_INFO(&hsdDObj)->load = DObjLoad;
}
#pragma pop
