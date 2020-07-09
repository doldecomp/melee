#include "wobj.h"

void HSD_WObjRemoveAnim(HSD_WObj* wobj)
{
    if (wobj != NULL) {
        HSD_AObjRemove(wobj->aobj);
        wobj->aobj = NULL;
        HSD_RObjRemoveAnimAll(wobj->robj);
    }
}

#ifdef NON_MATCHING
void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame)
{
    if (wobj != NULL) {
        HSD_AObjReqAnim(wobj->aobj, frame);
        HSD_RObjReqAnimAll(wobj->robj, frame);
    }
}
#else
asm void HSD_WObjReqAnim(HSD_WObj* wobj, f32 frame)
{
    nofralloc
    /* 8037D094 00379C74  7C 08 02 A6 */	mflr r0
    /* 8037D098 00379C78  90 01 00 04 */	stw r0, 4(r1)
    /* 8037D09C 00379C7C  94 21 FF E0 */	stwu r1, -0x20(r1)
    /* 8037D0A0 00379C80  DB E1 00 18 */	stfd f31, 0x18(r1)
    /* 8037D0A4 00379C84  FF E0 08 90 */	fmr f31, f1
    /* 8037D0A8 00379C88  93 E1 00 14 */	stw r31, 0x14(r1)
    /* 8037D0AC 00379C8C  7C 7F 1B 79 */	or. r31, r3, r3
    /* 8037D0B0 00379C90  41 82 00 1C */	beq lbl_8037D0CC
    /* 8037D0B4 00379C94  80 7F 00 18 */	lwz r3, 0x18(r31)
    /* 8037D0B8 00379C98  FC 20 F8 90 */	fmr f1, f31
    /* 8037D0BC 00379C9C  4B FE 70 51 */	bl HSD_AObjReqAnim
    /* 8037D0C0 00379CA0  80 7F 00 1C */	lwz r3, 0x1c(r31)
    /* 8037D0C4 00379CA4  FC 20 F8 90 */	fmr f1, f31
    /* 8037D0C8 00379CA8  4B FF E0 6D */	bl HSD_RObjReqAnimAll
lbl_8037D0CC:
    /* 8037D0CC 00379CAC  80 01 00 24 */	lwz r0, 0x24(r1)
    /* 8037D0D0 00379CB0  CB E1 00 18 */	lfd f31, 0x18(r1)
    /* 8037D0D4 00379CB4  83 E1 00 14 */	lwz r31, 0x14(r1)
    /* 8037D0D8 00379CB8  38 21 00 20 */	addi r1, r1, 0x20
    /* 8037D0DC 00379CBC  7C 08 03 A6 */	mtlr r0
    /* 8037D0E0 00379CC0  4E 80 00 20 */	blr 
}
#endif
