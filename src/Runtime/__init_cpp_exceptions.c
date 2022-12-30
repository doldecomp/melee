#include <dolphin/types.h>

extern const void* lbl_80005918; // info
s32 fragmentID = -2;

extern s32 __register_fragment(struct __eti_init_info*, char*);
extern void __unregister_fragment(s32);

extern asm char* GetR2(void)
{ // clang-format off
    nofralloc
    mr r3, r2
    blr
} // clang-format on

extern void __fini_cpp_exceptions(void)
{
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

// Left as asm due to lbl_80005918 being in extabindex, which throws an error
// about an incompatible section
extern asm void __init_cpp_exceptions(void)
{ // clang-format off
    nofralloc
/* 80322F5C 0031FB3C  7C 08 02 A6 */	mflr r0
/* 80322F60 0031FB40  90 01 00 04 */	stw r0, 4(r1)
/* 80322F64 0031FB44  94 21 FF F8 */	stwu r1, -8(r1)
/* 80322F68 0031FB48  80 0D A4 A0 */	lwz r0, fragmentID(r13)
/* 80322F6C 0031FB4C  2C 00 FF FE */	cmpwi r0, -2
/* 80322F70 0031FB50  40 82 00 1C */	bne lbl_80322F8C
/* 80322F74 0031FB54  4B FF FF AD */	bl GetR2
/* 80322F78 0031FB58  3C A0 80 00 */	lis r5, lbl_80005918@ha
/* 80322F7C 0031FB5C  7C 64 1B 78 */	mr r4, r3
/* 80322F80 0031FB60  38 65 59 18 */	addi r3, r5, lbl_80005918@l
/* 80322F84 0031FB64  4B FF F8 0D */	bl __register_fragment
/* 80322F88 0031FB68  90 6D A4 A0 */	stw r3, fragmentID(r13)
lbl_80322F8C:
/* 80322F8C 0031FB6C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80322F90 0031FB70  38 21 00 08 */	addi r1, r1, 8
/* 80322F94 0031FB74  7C 08 03 A6 */	mtlr r0
/* 80322F98 0031FB78  4E 80 00 20 */	blr
} // clang-format on
