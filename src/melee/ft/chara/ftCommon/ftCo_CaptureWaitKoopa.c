#include <platform.h>

#include "ftCo_CaptureWaitKoopa.h"

#include "ft/fighter.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

#include <placeholder.h>

float const ftCo_804D8B88 = 0;
float const ftCo_804D8B8C = 1;

ASM void ftCo_800BCC20(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 800BCC20 000B9800  7C 08 02 A6 */	mflr r0
/* 800BCC24 000B9804  38 80 01 18 */	li r4, 0x118
/* 800BCC28 000B9808  90 01 00 04 */	stw r0, 4(r1)
/* 800BCC2C 000B980C  38 A0 00 00 */	li r5, 0
/* 800BCC30 000B9810  38 C0 00 00 */	li r6, 0
/* 800BCC34 000B9814  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800BCC38 000B9818  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800BCC3C 000B981C  C0 22 91 A8 */	lfs f1, ftCo_804D8B88
/* 800BCC40 000B9820  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800BCC44 000B9824  FC 60 08 90 */	fmr f3, f1
/* 800BCC48 000B9828  C0 42 91 AC */	lfs f2, ftCo_804D8B8C
/* 800BCC4C 000B982C  4B FA C7 61 */	bl Fighter_ChangeMotionState
/* 800BCC50 000B9830  3C 60 80 0E */	lis r3, ftCo_800DB464@ha
/* 800BCC54 000B9834  38 03 B4 64 */	addi r0, r3, ftCo_800DB464@l
/* 800BCC58 000B9838  90 1F 21 B0 */	stw r0, 0x21b0(r31)
/* 800BCC5C 000B983C  38 7F 00 00 */	addi r3, r31, 0
/* 800BCC60 000B9840  38 80 01 FF */	li r4, 0x1ff
/* 800BCC64 000B9844  4B FC 16 91 */	bl ftCommon_8007E2F4
/* 800BCC68 000B9848  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800BCC6C 000B984C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800BCC70 000B9850  38 21 00 18 */	addi r1, r1, 0x18
/* 800BCC74 000B9854  7C 08 03 A6 */	mtlr r0
/* 800BCC78 000B9858  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
