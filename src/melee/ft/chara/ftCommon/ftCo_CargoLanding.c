#include <platform.h>

#include "ftCo_CargoLanding.h"

#include "ft/ft_08A4.h"
#include "ft/ftanim.h"

#include <placeholder.h>

float const ftCo_804D8738 = 0;
float const ftCo_804D873C = 1;

ASM void ftCo_8009BD4C(ftCo_GObj* gobj, float lag)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 8009BD4C 0009892C  7C 08 02 A6 */	mflr r0
/* 8009BD50 00098930  38 A0 00 01 */	li r5, 1
/* 8009BD54 00098934  90 01 00 04 */	stw r0, 4(r1)
/* 8009BD58 00098938  38 C0 00 00 */	li r6, 0
/* 8009BD5C 0009893C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8009BD60 00098940  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8009BD64 00098944  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8009BD68 00098948  7C 7E 1B 78 */	mr r30, r3
/* 8009BD6C 0009894C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009BD70 00098950  80 9F 02 CC */	lwz r4, 0x2cc(r31)
/* 8009BD74 00098954  C0 04 00 28 */	lfs f0, 0x28(r4)
/* 8009BD78 00098958  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 8009BD7C 0009895C  80 9F 02 CC */	lwz r4, 0x2cc(r31)
/* 8009BD80 00098960  C0 22 8D 58 */	lfs f1, ftCo_804D8738
/* 8009BD84 00098964  80 84 00 04 */	lwz r4, 4(r4)
/* 8009BD88 00098968  C0 42 8D 5C */	lfs f2, ftCo_804D873C
/* 8009BD8C 0009896C  38 84 00 08 */	addi r4, r4, 8
/* 8009BD90 00098970  48 03 9D 5D */	bl ftCo_800D5AEC
/* 8009BD94 00098974  7F C3 F3 78 */	mr r3, r30
/* 8009BD98 00098978  C0 22 8D 58 */	lfs f1, ftCo_804D8738
/* 8009BD9C 0009897C  4B FD 33 F5 */	bl ftAnim_SetAnimRate
/* 8009BDA0 00098980  80 7F 1A 58 */	lwz r3, 0x1a58(r31)
/* 8009BDA4 00098984  38 80 01 0A */	li r4, 0x10a
/* 8009BDA8 00098988  48 00 07 FD */	bl ftCo_8009C5A4
/* 8009BDAC 0009898C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8009BDB0 00098990  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8009BDB4 00098994  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8009BDB8 00098998  38 21 00 30 */	addi r1, r1, 0x30
/* 8009BDBC 0009899C  7C 08 03 A6 */	mtlr r0
/* 8009BDC0 000989A0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
