#include <dolphin/types.h>

extern unk_t lbl_804D73E8;
extern unk_t OSGetConsoleType();

#pragma push
asm unk_t InitializeUART()
{ // clang-format off
    nofralloc
/* 8034C86C 0034944C  7C 08 02 A6 */	mflr r0
/* 8034C870 00349450  90 01 00 04 */	stw r0, 4(r1)
/* 8034C874 00349454  94 21 FF F8 */	stwu r1, -8(r1)
/* 8034C878 00349458  4B FF 66 1D */	bl OSGetConsoleType
/* 8034C87C 0034945C  54 60 00 C7 */	rlwinm. r0, r3, 0, 3, 3
/* 8034C880 00349460  40 82 00 14 */	bne lbl_8034C894
/* 8034C884 00349464  38 00 00 00 */	li r0, 0
/* 8034C888 00349468  90 0D BD 48 */	stw r0, lbl_804D73E8(r13)
/* 8034C88C 0034946C  38 60 00 02 */	li r3, 2
/* 8034C890 00349470  48 00 00 14 */	b lbl_8034C8A4
lbl_8034C894:
/* 8034C894 00349474  3C 60 A5 FF */	lis r3, 0xA5FF005A@ha
/* 8034C898 00349478  38 03 00 5A */	addi r0, r3, 0xA5FF005A@l
/* 8034C89C 0034947C  90 0D BD 48 */	stw r0, lbl_804D73E8(r13)
/* 8034C8A0 00349480  38 60 00 00 */	li r3, 0
lbl_8034C8A4:
/* 8034C8A4 00349484  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8034C8A8 00349488  38 21 00 08 */	addi r1, r1, 8
/* 8034C8AC 0034948C  7C 08 03 A6 */	mtlr r0
/* 8034C8B0 00349490  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t ReadUARTN()
{ // clang-format off
    nofralloc
/* 8034C8B4 00349494  38 60 00 04 */	li r3, 4
/* 8034C8B8 00349498  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
