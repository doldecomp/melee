#include "aobj.h"

extern HSD_ObjAllocData lbl_804C0880; //aobj_alloc_data

extern s32 lbl_804D7630;
extern s32 lbl_804D762C;

extern HSD_SList* lbl_804D7628;

void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C0880, sizeof(HSD_AObj), 4);
}

#pragma push
#pragma force_active on // Unused function until it's loaded into a GetAllocData function table, so force_active required to match for now
HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &lbl_804C0880;
}
#pragma pop

u32 HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return (aobj) ? aobj->flags : 0;
}

void HSD_AObjSetFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags |= flags;
    }
}

void HSD_AObjClearFlags(HSD_AObj* aobj, u32 flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE);
        aobj->flags &= ~flags;
    }
}

#ifdef NON_MATCHING
void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (aobj == NULL)
        return;
    if (aobj->fobj) {
            HSD_FObjRemoveAll(aobj->fobj);
    }
    aobj->fobj = fobj;
}
#else
asm void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    nofralloc
    /* 80364054 00360C34  7C 08 02 A6 */    mflr r0
    /* 80364058 00360C38  90 01 00 04 */    stw r0, 4(r1)
    /* 8036405C 00360C3C  94 21 FF E8 */    stwu r1, -0x18(r1)
    /* 80364060 00360C40  93 E1 00 14 */    stw r31, 0x14(r1)
    /* 80364064 00360C44  3B E4 00 00 */    addi r31, r4, 0
    /* 80364068 00360C48  93 C1 00 10 */    stw r30, 0x10(r1)
    /* 8036406C 00360C4C  7C 7E 1B 79 */    or. r30, r3, r3
    /* 80364070 00360C50  41 82 00 18 */    beq lbl_80364088
    /* 80364074 00360C54  80 7E 00 14 */    lwz r3, 0x14(r30)
    /* 80364078 00360C58  28 03 00 00 */    cmplwi r3, 0
    /* 8036407C 00360C5C  41 82 00 08 */    beq lbl_80364084
    /* 80364080 00360C60  48 00 69 1D */    bl HSD_FObjRemoveAll
lbl_80364084:
    /* 80364084 00360C64  93 FE 00 14 */    stw r31, 0x14(r30)
lbl_80364088:
    /* 80364088 00360C68  80 01 00 1C */    lwz r0, 0x1c(r1)
    /* 8036408C 00360C6C  83 E1 00 14 */    lwz r31, 0x14(r1)
    /* 80364090 00360C70  83 C1 00 10 */    lwz r30, 0x10(r1)
    /* 80364094 00360C74  38 21 00 18 */    addi r1, r1, 0x18
    /* 80364098 00360C78  7C 08 03 A6 */    mtlr r0
    /* 8036409C 00360C7C  4E 80 00 20 */    blr 
}
#endif

void HSD_AObjInitEndCallBack(void)
{
    lbl_804D762C = 0;
    lbl_804D7630 = 0;
}

#pragma push
#pragma optimization_level 2
void HSD_AObjInvokeCallBacks(void)
{
    u32 junk1;
    u32 junk2;
    HSD_SList* list;

    if (lbl_804D762C != 0 && lbl_804D7630 == 0) {
        list = lbl_804D7628;
        while (list) {
            void (*func)(void) = list->data;
            (*func)();
            list = list->next;
        }
    }
}
#pragma pop

#ifdef NON_MATCHING
void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    u32 flags;

    if (aobj == NULL)
        return;

    aobj->curr_frame = frame;

    aobj->flags = aobj->flags & 0xBFFFFFFF;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}
#else
asm void HSD_AObjReqAnim(HSD_AObj* aobj, f32 frame)
{
    nofralloc
    /* 8036410C 00360CEC  7C 08 02 A6 */	mflr r0
    /* 80364110 00360CF0  28 03 00 00 */	cmplwi r3, 0
    /* 80364114 00360CF4  90 01 00 04 */	stw r0, 4(r1)
    /* 80364118 00360CF8  94 21 FF F8 */	stwu r1, -8(r1)
    /* 8036411C 00360CFC  41 82 00 20 */	beq lbl_8036413C
    /* 80364120 00360D00  D0 23 00 04 */	stfs f1, 4(r3)
    /* 80364124 00360D04  80 03 00 00 */	lwz r0, 0(r3)
    /* 80364128 00360D08  54 00 00 80 */	rlwinm r0, r0, 0, 2, 0
    /* 8036412C 00360D0C  64 00 08 00 */	oris r0, r0, 0x800
    /* 80364130 00360D10  90 03 00 00 */	stw r0, 0(r3)
    /* 80364134 00360D14  80 63 00 14 */	lwz r3, 0x14(r3)
    /* 80364138 00360D18  48 00 69 49 */	bl HSD_FObjReqAnimAll
lbl_8036413C:
    /* 8036413C 00360D1C  80 01 00 0C */	lwz r0, 0xc(r1)
    /* 80364140 00360D20  38 21 00 08 */	addi r1, r1, 8
    /* 80364144 00360D24  7C 08 03 A6 */	mtlr r0
    /* 80364148 00360D28  4E 80 00 20 */	blr 
}
#endif
