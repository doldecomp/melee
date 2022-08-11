#include <sysdolphin/baselib/wobj.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/robj.h>

void WObjInfoInit(void);

HSD_WObjInfo hsdWObj = { WObjInfoInit };

static HSD_WObjInfo* default_class = NULL;

static char lbl_804D5EF8[7] = "wobj.c\0";

void HSD_WObjRemoveAnim(HSD_WObj* wobj)
{
    if (wobj != NULL) {
        HSD_AObjRemove(wobj->aobj);
        wobj->aobj = NULL;
        HSD_RObjRemoveAnimAll(wobj->robj);
    }
}

void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame)
{
    if (wobj != NULL) {
        HSD_AObjReqAnim(wobj->aobj, frame);
        HSD_RObjReqAnimAll(wobj->robj, frame);
    }
}

void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim)
{
    if (wobj != NULL && anim != NULL) {
        if (wobj->aobj != NULL) {
            HSD_AObjRemove(wobj->aobj);
        }
        wobj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
        HSD_RObjAddAnimAll(wobj->robj, anim->robjanim);
    }
}

static void WObjUpdateFunc(void* obj, u32 type, f32* fval)
{
    HSD_WObj* wobj;
    Vec p;
    HSD_JObj* jp;

    wobj = obj;
    if (wobj != NULL) {
        switch (type) {
        case 4: {
            if (*fval < 0.0) {
                *fval = 0.0;
            }
            if (1.0 < *fval) {
                *fval = 1.0;
            }

            if (wobj->aobj == NULL) {
                __assert(lbl_804D5EF8, 148, "wobj->aobj");
            }

            jp = (HSD_JObj*)wobj->aobj->hsd_obj;
            if (jp == NULL) {
                __assert(lbl_804D5EF8, 150, "jp");
            }

            if (jp->u.spline == NULL) {
                __assert(lbl_804D5EF8, 151, "jp->u.spline");
            }

            splArcLengthPoint(&p, jp->u.spline, *fval);
            HSD_WObjSetPosition(wobj, &p);
            wobj->flags |= 1;
        } break;

        case 5:
            HSD_WObjSetPositionX(wobj, *fval);
            break;

        case 6:
            HSD_WObjSetPositionY(wobj, *fval);
            break;

        case 7:
            HSD_WObjSetPositionZ(wobj, *fval);
            break;
        }
    }
}

void HSD_WObjInterpretAnim(HSD_WObj* wobj) 
{
    if (wobj != NULL) {
        HSD_AObjInterpretAnim(wobj->aobj, wobj, &WObjUpdateFunc);
        HSD_RObjAnimAll(wobj->robj);
    }
}

static int WObjLoad(HSD_WObj* wobj, HSD_WObjDesc* desc) 
{
    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != NULL) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
    return 0;
}

void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc) 
{
    if (wobj == NULL || desc == NULL) {
        return;
    }

    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != NULL) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
}

void HSD_WObjSetDefaultClass(HSD_WObjInfo* info)
{
    if (info) {
        if (!hsdIsDescendantOf(info, &hsdWObj)) {
            __assert(lbl_804D5EF8, 221, "hsdIsDescendantOf(info, &hsdWObj)"); // The line number here is totally made up, this function is removed in practice but the string isn't
        }
    }
    default_class = info;
}

static char lbl_804D5F04[5] = "wobj\0";

HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc)
{
    if (desc != NULL) {
        HSD_WObj* wobj;
        HSD_ClassInfo* info;
        if (desc->class_name == NULL || !(info = hsdSearchClassInfo(desc->class_name))) {
            wobj = HSD_WObjAlloc();
        } else {
            wobj = hsdNew(info);
            if (wobj == NULL) {
                __assert(lbl_804D5EF8, 252, lbl_804D5F04);
            }
        }
        HSD_WOBJ_METHOD(wobj)->load(wobj, desc);
        return wobj;
    }
    return NULL;
}

void HSD_WObjSetPosition(HSD_WObj* wobj, Vec* pos)
{
    if (wobj == NULL || pos == NULL) {
        return;
    }

    wobj->pos = *pos;
    wobj->flags |= 0x2;
    wobj->flags &= 0xFFFFFFFE;
}

void HSD_WObjSetPositionX(HSD_WObj* wobj, f32 val)
{
    HSD_JObj* jp;

    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMUltiVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.x = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjSetPositionY(HSD_WObj* wobj, f32 val)
{
    HSD_JObj* jp;

    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMUltiVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.y = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjSetPositionZ(HSD_WObj* wobj, f32 val)
{
    HSD_JObj* jp;

    if (wobj != NULL) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
                jp = (HSD_JObj*)wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
                PSMTXMUltiVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.z = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjGetPosition(HSD_WObj* wobj, Vec* vec)
{
    HSD_JObj* jp;

    if (wobj == NULL || vec == NULL) {
        return;
    }
    if ((wobj->flags & 1) != 0) {
        if (wobj->aobj != NULL && wobj->aobj->hsd_obj != NULL) {
            jp = (HSD_JObj*)wobj->aobj->hsd_obj;
            HSD_JObjSetupMatrix((HSD_JObj*)wobj->aobj->hsd_obj);
            PSMTXMUltiVec(jp->mtx, &wobj->pos, &wobj->pos);
        }
        wobj->flags &= 0xFFFFFFFE;
    }
    *vec = wobj->pos;
}

// Fuck frank.py, all my homies hate frank.py
#ifdef NON_MATCHING
#pragma push
#pragma peephole on
HSD_WObj* HSD_WObjAlloc(void) {
    HSD_WObj* wobj = (HSD_WObj*)hsdNew((HSD_ClassInfo*)(default_class ? default_class : &hsdWObj));
    if (wobj == NULL){
        __assert("wobj.c", 591, "wobj");
    }
    return wobj;
}
#pragma pop
#else
asm HSD_WObj* HSD_WObjAlloc(void) {
    nofralloc
/* 8037D808 0037A3E8  7C 08 02 A6 */	mflr r0
/* 8037D80C 0037A3EC  90 01 00 04 */	stw r0, 4(r1)
/* 8037D810 0037A3F0  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8037D814 0037A3F4  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8037D818 0037A3F8  80 6D C0 50 */	lwz r3, default_class(r13)
/* 8037D81C 0037A3FC  28 03 00 00 */	cmplwi r3, 0
/* 8037D820 0037A400  41 82 00 08 */	beq lbl_8037D828
/* 8037D824 0037A404  48 00 00 0C */	b lbl_8037D830
lbl_8037D828:
/* 8037D828 0037A408  3C 60 80 40 */	lis r3, hsdWObj@ha
/* 8037D82C 0037A40C  38 63 6F D0 */	addi r3, r3, hsdWObj@l
lbl_8037D830:
/* 8037D830 0037A410  48 00 4B 15 */	bl hsdNew
/* 8037D834 0037A414  7C 7F 1B 79 */	or. r31, r3, r3
/* 8037D838 0037A418  40 82 00 14 */	bne lbl_8037D84C
/* 8037D83C 0037A41C  38 6D A8 58 */	addi r3, r13, lbl_804D5EF8
/* 8037D840 0037A420  38 80 02 4F */	li r4, 0x24f
/* 8037D844 0037A424  38 AD A8 64 */	addi r5, r13, lbl_804D5F04
/* 8037D848 0037A428  48 00 A9 D9 */	bl __assert
lbl_8037D84C:
/* 8037D84C 0037A42C  7F E3 FB 78 */	mr r3, r31
/* 8037D850 0037A430  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8037D854 0037A434  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8037D858 0037A438  38 21 00 10 */	addi r1, r1, 0x10
/* 8037D85C 0037A43C  7C 08 03 A6 */	mtlr r0
/* 8037D860 0037A440  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
static void WObjRelease(HSD_Class* o)
{
    HSD_WObj* wobj = (HSD_WObj*)o;
    HSD_RObjRemoveAll(wobj->robj);
    HSD_AObjRemove(wobj->aobj);
    HSD_OBJECT_PARENT_INFO(&hsdWObj)->release(o);
}

static void WObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdWObj)->amnesia(info);
}

static void WObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdWObj), HSD_CLASS_INFO(&hsdObj), "sysdolphin_base_library", "had_wobj", sizeof(HSD_WObjInfo), sizeof(HSD_WObj));
    HSD_CLASS_INFO(&hsdWObj)->release = WObjRelease;
    HSD_CLASS_INFO(&hsdWObj)->amnesia = WObjAmnesia;
    HSD_WOBJ_INFO(&hsdWObj)->load = WObjLoad;
}
#pragma pop
