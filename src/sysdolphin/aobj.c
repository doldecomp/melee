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

#ifdef NON_MATCHING
void HSD_AObjInvokeCallBacks(void)
{
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
#else
asm void HSD_AObjInvokeCallBacks(void)
{
    nofralloc
    /* 803640B0 00360C90  7C 08 02 A6 */	mflr r0
    /* 803640B4 00360C94  90 01 00 04 */	stw r0, 4(r1)
    /* 803640B8 00360C98  94 21 FF E8 */	stwu r1, -0x18(r1)
    /* 803640BC 00360C9C  93 E1 00 14 */	stw r31, 0x14(r1)
    /* 803640C0 00360CA0  80 0D BF 8C */	lwz r0, lbl_804D762C
    /* 803640C4 00360CA4  2C 00 00 00 */	cmpwi r0, 0
    /* 803640C8 00360CA8  41 82 00 30 */	beq lbl_803640F8
    /* 803640CC 00360CAC  80 0D BF 90 */	lwz r0, lbl_804D7630
    /* 803640D0 00360CB0  2C 00 00 00 */	cmpwi r0, 0
    /* 803640D4 00360CB4  40 82 00 24 */	bne lbl_803640F8
    /* 803640D8 00360CB8  83 ED BF 88 */	lwz r31, lbl_804D7628
    /* 803640DC 00360CBC  48 00 00 14 */	b lbl_803640F0
lbl_803640E0:
    /* 803640E0 00360CC0  81 9F 00 04 */	lwz r12, 4(r31)
    /* 803640E4 00360CC4  7D 88 03 A6 */	mtlr r12
    /* 803640E8 00360CC8  4E 80 00 21 */	blrl 
    /* 803640EC 00360CCC  83 FF 00 00 */	lwz r31, 0(r31)
lbl_803640F0:
    /* 803640F0 00360CD0  28 1F 00 00 */	cmplwi r31, 0
    /* 803640F4 00360CD4  40 82 FF EC */	bne lbl_803640E0
lbl_803640F8:
    /* 803640F8 00360CD8  80 01 00 1C */	lwz r0, 0x1c(r1)
    /* 803640FC 00360CDC  83 E1 00 14 */	lwz r31, 0x14(r1)
    /* 80364100 00360CE0  38 21 00 18 */	addi r1, r1, 0x18
    /* 80364104 00360CE4  7C 08 03 A6 */	mtlr r0
    /* 80364108 00360CE8  4E 80 00 20 */	blr 
}
#endif