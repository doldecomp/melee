#include <dolphin/types.h>
#include <string.h>

#define OS_SYS_CALL_HANDLER ((void*) 0x80000C00)
#define OS_HANDLER_SLOT_SIZE 0x100

void __OSSystemCallVectorStart(void);
void __OSSystemCallVectorEnd(void);

#pragma push
asm void __OSSystemCallVector(void)
{ // clang-format off
    nofralloc
entry __OSSystemCallVectorStart
	mfspr r9, DBSR
	ori r10, r9, 8
	mtspr DBSR, r10
	isync
	sync
	mtspr DBSR, r9
	rfi
entry __OSSystemCallVectorEnd
	nop
} //clang-format on
#pragma pop

extern void ICInvalidateRange(void*, u32);
extern void DCFlushRangeNoSync(void*, u32);

#ifdef NON_MATCHING

void __OSInitSystemCall(void)
{
    memcpy(OS_SYS_CALL_HANDLER, __OSSystemCallVectorStart, (u8*) __OSSystemCallVectorEnd - (u8*) __OSSystemCallVectorStart);

    DCFlushRangeNoSync(OS_SYS_CALL_HANDLER, OS_HANDLER_SLOT_SIZE);
    __sync();
    ICInvalidateRange(OS_SYS_CALL_HANDLER, OS_HANDLER_SLOT_SIZE);
}

#else

#pragma push
asm void __OSInitSystemCall(void)
{ // clang-format off
    nofralloc
/* 8034ABA0 00347780  7C 08 02 A6 */	mflr r0
/* 8034ABA4 00347784  90 01 00 04 */	stw r0, 4(r1)
/* 8034ABA8 00347788  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8034ABAC 0034778C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8034ABB0 00347790  3C A0 80 00 */	lis r5, 0x80000C00@ha
/* 8034ABB4 00347794  3C 80 80 35 */	lis r4, __OSSystemCallVectorStart@ha
/* 8034ABB8 00347798  3C 60 80 35 */	lis r3, __OSSystemCallVectorEnd@ha
/* 8034ABBC 0034779C  3B E5 0C 00 */	addi r31, r5, 0x80000C00@l
/* 8034ABC0 003477A0  38 03 AB 9C */	addi r0, r3, __OSSystemCallVectorEnd@l
/* 8034ABC4 003477A4  38 84 AB 80 */	addi r4, r4, __OSSystemCallVectorStart@l
/* 8034ABC8 003477A8  7F E3 FB 78 */	mr r3, r31
/* 8034ABCC 003477AC  7C A4 00 50 */	subf r5, r4, r0
/* 8034ABD0 003477B0  4B CB 86 25 */	bl memcpy
/* 8034ABD4 003477B4  7F E3 FB 78 */	mr r3, r31
/* 8034ABD8 003477B8  38 80 01 00 */	li r4, 0x100
/* 8034ABDC 003477BC  4B FF 9C 99 */	bl DCFlushRangeNoSync
/* 8034ABE0 003477C0  7C 00 04 AC */	sync
/* 8034ABE4 003477C4  7F E3 FB 78 */	mr r3, r31
/* 8034ABE8 003477C8  38 80 01 00 */	li r4, 0x100
/* 8034ABEC 003477CC  4B FF 9C E9 */	bl ICInvalidateRange
/* 8034ABF0 003477D0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8034ABF4 003477D4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8034ABF8 003477D8  38 21 00 10 */	addi r1, r1, 0x10
/* 8034ABFC 003477DC  7C 08 03 A6 */	mtlr r0
/* 8034AC00 003477E0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif
