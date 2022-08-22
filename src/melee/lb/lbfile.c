#include <melee/lb/lbfile.h>

extern char lbl_803BA508[]; //"lbfile.c"
extern char lbl_803BA514[]; //"!cancelflag"

extern void func_800195D0();

extern BOOL cancel;

void lbFile_8001615C(s32 r3, s32 r4, s32 r5, BOOL cancelflag) {
    if (cancelflag != 0){
        __assert(lbl_803BA508, 71, lbl_803BA514);
    }
    cancel = 1;
}

#ifdef NON_MATCHING
BOOL lbFile_800161A0(){
    func_800195D0();
    return cancel;
}
#else
asm BOOL lbFile_800161A0()
{
    nofralloc
/* 800161A0 00012D80  7C 08 02 A6 */	mflr r0
/* 800161A4 00012D84  90 01 00 04 */	stw r0, 4(r1)
/* 800161A8 00012D88  94 21 FF F8 */	stwu r1, -8(r1)
/* 800161AC 00012D8C  48 00 34 25 */	bl func_800195D0
/* 800161B0 00012D90  80 6D AD 28 */	lwz r3, cancel(r13)
/* 800161B4 00012D94  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800161B8 00012D98  38 21 00 08 */	addi r1, r1, 8
/* 800161BC 00012D9C  7C 08 03 A6 */	mtlr r0
/* 800161C0 00012DA0  4E 80 00 20 */	blr 
}
#endif
