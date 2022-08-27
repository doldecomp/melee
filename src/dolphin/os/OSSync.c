#include <dolphin/types.h>
#include <string.h>

void __OSSystemCallVectorEnd(void);

#pragma push
asm unk_t SystemCallVector()
{ // clang-format off
    nofralloc
/* 80092ACC 0008FA0C  7D 30 FA A6 */	mfspr r9, 0x3f0
/* 80092AD0 0008FA10  61 2A 00 08 */	ori r10, r9, 8
/* 80092AD4 0008FA14  7D 50 FB A6 */	mtspr 0x3f0, r10
/* 80092AD8 0008FA18  4C 00 01 2C */	isync
/* 80092ADC 0008FA1C  7C 00 04 AC */	sync
/* 80092AE0 0008FA20  7D 30 FB A6 */	mtspr 0x3f0, r9
/* 80092AE4 0008FA24  4C 00 00 64 */	rfi 
entry __OSSystemCallVectorEnd
/* 80092AE8 0008FA28  60 00 00 00 */	nop 
} // clang-format on
#pragma pop

extern unk_t ICInvalidateRange();
extern unk_t DCFlushRangeNoSync();

#pragma push
asm unk_t __OSInitSystemCall()
{ // clang-format off
    nofralloc
/* 80092AEC 0008FA2C  7C 08 02 A6 */	mflr r0
/* 80092AF0 0008FA30  90 01 00 04 */	stw r0, 4(r1)
/* 80092AF4 0008FA34  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80092AF8 0008FA38  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80092AFC 0008FA3C  3C A0 80 00 */	lis r5, 0x80000C00@ha
/* 80092B00 0008FA40  3C 80 80 09 */	lis r4, SystemCallVector@ha
/* 80092B04 0008FA44  3C 60 80 09 */	lis r3, __OSSystemCallVectorEnd@ha
/* 80092B08 0008FA48  3B E5 0C 00 */	addi r31, r5, 0x80000C00@l
/* 80092B0C 0008FA4C  38 03 2A E8 */	addi r0, r3, __OSSystemCallVectorEnd@l
/* 80092B10 0008FA50  38 84 2A CC */	addi r4, r4, SystemCallVector@l
/* 80092B14 0008FA54  7F E3 FB 78 */	mr r3, r31
/* 80092B18 0008FA58  7C A4 00 50 */	subf r5, r4, r0
/* 80092B1C 0008FA5C  4B F7 06 D9 */	bl memcpy
/* 80092B20 0008FA60  7F E3 FB 78 */	mr r3, r31
/* 80092B24 0008FA64  38 80 01 00 */	li r4, 0x100
/* 80092B28 0008FA68  4B FF B4 ED */	bl DCFlushRangeNoSync
/* 80092B2C 0008FA6C  7C 00 04 AC */	sync
/* 80092B30 0008FA70  7F E3 FB 78 */	mr r3, r31
/* 80092B34 0008FA74  38 80 01 00 */	li r4, 0x100
/* 80092B38 0008FA78  4B FF B5 3D */	bl ICInvalidateRange
/* 80092B3C 0008FA7C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80092B40 0008FA80  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80092B44 0008FA84  38 21 00 10 */	addi r1, r1, 0x10
/* 80092B48 0008FA88  7C 08 03 A6 */	mtlr r0
/* 80092B4C 0008FA8C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
