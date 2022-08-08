#include <dolphin/os/init/__ppc_eabi_init.h>

typedef void (*voidfunc) (void);

extern voidfunc lbl_803B7240[]; // _ctors

static void __init_cpp(void);

extern void PPCHalt(void);

void __init_user(void)
{
   __init_cpp();
}

#ifdef NON_MATCHING
static void __init_cpp(void)
{
    voidfunc *constructor;

    for (constructor = lbl_803B7240; *constructor; constructor++) {
        (*constructor)();
    }
}
#else
asm static void __init_cpp(void)
{
    nofralloc
/* 8034CADC 003496BC  7C 08 02 A6 */	mflr r0
/* 8034CAE0 003496C0  90 01 00 04 */	stw r0, 4(r1)
/* 8034CAE4 003496C4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8034CAE8 003496C8  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8034CAEC 003496CC  3C 60 80 3B */	lis r3, lbl_803B7240@ha
/* 8034CAF0 003496D0  38 03 72 40 */	addi r0, r3, lbl_803B7240@l
/* 8034CAF4 003496D4  7C 1F 03 78 */	mr r31, r0
/* 8034CAF8 003496D8  48 00 00 04 */	b lbl_8034CAFC
lbl_8034CAFC:
/* 8034CAFC 003496DC  48 00 00 04 */	b lbl_8034CB00
lbl_8034CB00:
/* 8034CB00 003496E0  48 00 00 10 */	b lbl_8034CB10
lbl_8034CB04:
/* 8034CB04 003496E4  7D 88 03 A6 */	mtlr r12
/* 8034CB08 003496E8  4E 80 00 21 */	blrl 
/* 8034CB0C 003496EC  3B FF 00 04 */	addi r31, r31, 4
lbl_8034CB10:
/* 8034CB10 003496F0  81 9F 00 00 */	lwz r12, 0(r31)
/* 8034CB14 003496F4  28 0C 00 00 */	cmplwi r12, 0
/* 8034CB18 003496F8  40 82 FF EC */	bne lbl_8034CB04
/* 8034CB1C 003496FC  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8034CB20 00349700  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8034CB24 00349704  38 21 00 10 */	addi r1, r1, 0x10
/* 8034CB28 00349708  7C 08 03 A6 */	mtlr r0
/* 8034CB2C 0034970C  4E 80 00 20 */	blr 
}
#endif

void _ExitProcess(void)
{
    PPCHalt();
}
