#include "fobj.h"

extern HSD_ObjAllocData lbl_804C08D8;

#pragma push
#pragma force_active on // Unused function until it's loaded into a GetAllocData function table, so force_active required to match for now
HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &lbl_804C08D8;
}
#pragma pop

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C08D8, sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj)
        return;

    HSD_FObjFree(fobj);
}

#ifdef NON_MATCHING
void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    HSD_FObj* t1;
    HSD_FObj* t2;
    HSD_FObj* t3;

    if (!fobj)
        return;

    t3 = fobj->next;
    if (!t3)
        return;

    t2 = t3->next;
    if (!t2)
        return;

    t1 = t2->next;
    if (!t1)
        return;
    HSD_FObjRemoveAll(t1->next);
    HSD_FObjRemove(t1);

    if (t2) {
        HSD_FObjFree(t2);
    }
    if (t3) {
        HSD_FObjFree(t3);
    }

    if (fobj) {
        HSD_FObjFree(fobj);
    }
}
#else
asm void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    nofralloc
/* 8036A99C 0036757C  7C 08 02 A6 */	mflr r0
/* 8036A9A0 00367580  90 01 00 04 */	stw r0, 4(r1)
/* 8036A9A4 00367584  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8036A9A8 00367588  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8036A9AC 0036758C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8036A9B0 00367590  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8036A9B4 00367594  93 81 00 10 */	stw r28, 0x10(r1)
/* 8036A9B8 00367598  7C 7C 1B 79 */	or. r28, r3, r3
/* 8036A9BC 0036759C  41 82 00 68 */	beq lbl_8036AA24
/* 8036A9C0 003675A0  83 FC 00 00 */	lwz r31, 0(r28)
/* 8036A9C4 003675A4  28 1F 00 00 */	cmplwi r31, 0
/* 8036A9C8 003675A8  41 82 00 4C */	beq lbl_8036AA14
/* 8036A9CC 003675AC  83 DF 00 00 */	lwz r30, 0(r31)
/* 8036A9D0 003675B0  28 1E 00 00 */	cmplwi r30, 0
/* 8036A9D4 003675B4  41 82 00 30 */	beq lbl_8036AA04
/* 8036A9D8 003675B8  83 BE 00 00 */	lwz r29, 0(r30)
/* 8036A9DC 003675BC  28 1D 00 00 */	cmplwi r29, 0
/* 8036A9E0 003675C0  41 82 00 14 */	beq lbl_8036A9F4
/* 8036A9E4 003675C4  80 7D 00 00 */	lwz r3, 0(r29)
/* 8036A9E8 003675C8  4B FF FF B5 */	bl HSD_FObjRemoveAll
/* 8036A9EC 003675CC  7F A3 EB 78 */	mr r3, r29
/* 8036A9F0 003675D0  4B FF FF 85 */	bl HSD_FObjRemove
lbl_8036A9F4:
/* 8036A9F4 003675D4  28 1E 00 00 */	cmplwi r30, 0
/* 8036A9F8 003675D8  41 82 00 0C */	beq lbl_8036AA04
/* 8036A9FC 003675DC  7F C3 F3 78 */	mr r3, r30
/* 8036AA00 003675E0  48 00 0E A5 */	bl HSD_FObjFree
lbl_8036AA04:
/* 8036AA04 003675E4  28 1F 00 00 */	cmplwi r31, 0
/* 8036AA08 003675E8  41 82 00 0C */	beq lbl_8036AA14
/* 8036AA0C 003675EC  7F E3 FB 78 */	mr r3, r31
/* 8036AA10 003675F0  48 00 0E 95 */	bl HSD_FObjFree
lbl_8036AA14:
/* 8036AA14 003675F4  28 1C 00 00 */	cmplwi r28, 0
/* 8036AA18 003675F8  41 82 00 0C */	beq lbl_8036AA24
/* 8036AA1C 003675FC  7F 83 E3 78 */	mr r3, r28
/* 8036AA20 00367600  48 00 0E 85 */	bl HSD_FObjFree
lbl_8036AA24:
/* 8036AA24 00367604  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8036AA28 00367608  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8036AA2C 0036760C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8036AA30 00367610  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8036AA34 00367614  83 81 00 10 */	lwz r28, 0x10(r1)
/* 8036AA38 00367618  38 21 00 20 */	addi r1, r1, 0x20
/* 8036AA3C 0036761C  7C 08 03 A6 */	mtlr r0
/* 8036AA40 00367620  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
u8 HSD_FObjSetState(HSD_FObj* fobj, u8 state)
{
    if (fobj)
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    return state;
}

u32 HSD_FObjGetState(HSD_FObj* fobj)
{
    if (!fobj)
        return 0;
    return fobj->flags & 0xF;
}
#pragma pop
