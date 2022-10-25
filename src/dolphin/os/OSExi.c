#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>
#include <dolphin/os/OSTime.h>

extern unk_t lbl_804A7C80;

#pragma push
asm unk_t SetExiInterruptMask()
{ // clang-format off
    nofralloc
/* 80345A70 00342650  7C 08 02 A6 */	mflr r0
/* 80345A74 00342654  3C A0 80 4A */	lis r5, lbl_804A7C80@ha
/* 80345A78 00342658  90 01 00 04 */	stw r0, 4(r1)
/* 80345A7C 0034265C  2C 03 00 01 */	cmpwi r3, 1
/* 80345A80 00342660  38 A5 7C 80 */	addi r5, r5, lbl_804A7C80@l
/* 80345A84 00342664  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80345A88 00342668  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80345A8C 0034266C  3B E4 00 00 */	addi r31, r4, 0
/* 80345A90 00342670  38 85 00 80 */	addi r4, r5, 0x80
/* 80345A94 00342674  41 82 00 5C */	beq lbl_80345AF0
/* 80345A98 00342678  40 80 00 10 */	bge lbl_80345AA8
/* 80345A9C 0034267C  2C 03 00 00 */	cmpwi r3, 0
/* 80345AA0 00342680  40 80 00 14 */	bge lbl_80345AB4
/* 80345AA4 00342684  48 00 00 AC */	b lbl_80345B50
lbl_80345AA8:
/* 80345AA8 00342688  2C 03 00 03 */	cmpwi r3, 3
/* 80345AAC 0034268C  40 80 00 A4 */	bge lbl_80345B50
/* 80345AB0 00342690  48 00 00 70 */	b lbl_80345B20
lbl_80345AB4:
/* 80345AB4 00342694  80 1F 00 00 */	lwz r0, 0(r31)
/* 80345AB8 00342698  28 00 00 00 */	cmplwi r0, 0
/* 80345ABC 0034269C  40 82 00 10 */	bne lbl_80345ACC
/* 80345AC0 003426A0  80 04 00 00 */	lwz r0, 0(r4)
/* 80345AC4 003426A4  28 00 00 00 */	cmplwi r0, 0
/* 80345AC8 003426A8  41 82 00 10 */	beq lbl_80345AD8
lbl_80345ACC:
/* 80345ACC 003426AC  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345AD0 003426B0  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80345AD4 003426B4  41 82 00 10 */	beq lbl_80345AE4
lbl_80345AD8:
/* 80345AD8 003426B8  3C 60 00 41 */	lis r3, 0x41
/* 80345ADC 003426BC  48 00 1C 51 */	bl __OSMaskInterrupts
/* 80345AE0 003426C0  48 00 00 70 */	b lbl_80345B50
lbl_80345AE4:
/* 80345AE4 003426C4  3C 60 00 41 */	lis r3, 0x41
/* 80345AE8 003426C8  48 00 1C CD */	bl __OSUnmaskInterrupts
/* 80345AEC 003426CC  48 00 00 64 */	b lbl_80345B50
lbl_80345AF0:
/* 80345AF0 003426D0  80 1F 00 00 */	lwz r0, 0(r31)
/* 80345AF4 003426D4  28 00 00 00 */	cmplwi r0, 0
/* 80345AF8 003426D8  41 82 00 10 */	beq lbl_80345B08
/* 80345AFC 003426DC  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345B00 003426E0  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80345B04 003426E4  41 82 00 10 */	beq lbl_80345B14
lbl_80345B08:
/* 80345B08 003426E8  3C 60 00 08 */	lis r3, 8
/* 80345B0C 003426EC  48 00 1C 21 */	bl __OSMaskInterrupts
/* 80345B10 003426F0  48 00 00 40 */	b lbl_80345B50
lbl_80345B14:
/* 80345B14 003426F4  3C 60 00 08 */	lis r3, 8
/* 80345B18 003426F8  48 00 1C 9D */	bl __OSUnmaskInterrupts
/* 80345B1C 003426FC  48 00 00 34 */	b lbl_80345B50
lbl_80345B20:
/* 80345B20 00342700  38 60 00 19 */	li r3, 0x19
/* 80345B24 00342704  48 00 18 A9 */	bl __OSGetInterruptHandler
/* 80345B28 00342708  28 03 00 00 */	cmplwi r3, 0
/* 80345B2C 0034270C  41 82 00 10 */	beq lbl_80345B3C
/* 80345B30 00342710  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345B34 00342714  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80345B38 00342718  41 82 00 10 */	beq lbl_80345B48
lbl_80345B3C:
/* 80345B3C 0034271C  38 60 00 40 */	li r3, 0x40
/* 80345B40 00342720  48 00 1B ED */	bl __OSMaskInterrupts
/* 80345B44 00342724  48 00 00 0C */	b lbl_80345B50
lbl_80345B48:
/* 80345B48 00342728  38 60 00 40 */	li r3, 0x40
/* 80345B4C 0034272C  48 00 1C 69 */	bl __OSUnmaskInterrupts
lbl_80345B50:
/* 80345B50 00342730  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80345B54 00342734  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80345B58 00342738  38 21 00 18 */	addi r1, r1, 0x18
/* 80345B5C 0034273C  7C 08 03 A6 */	mtlr r0
/* 80345B60 00342740  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t EXIClearInterrupts();

#pragma push
asm unk_t EXIImm()
{ // clang-format off
    nofralloc
/* 80345B64 00342744  7C 08 02 A6 */	mflr r0
/* 80345B68 00342748  90 01 00 04 */	stw r0, 4(r1)
/* 80345B6C 0034274C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80345B70 00342750  BE 61 00 24 */	stmw r19, 0x24(r1)
/* 80345B74 00342754  3B 83 00 00 */	addi r28, r3, 0
/* 80345B78 00342758  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80345B7C 0034275C  57 88 30 32 */	slwi r8, r28, 6
/* 80345B80 00342760  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80345B84 00342764  3B A4 00 00 */	addi r29, r4, 0
/* 80345B88 00342768  3B C5 00 00 */	addi r30, r5, 0
/* 80345B8C 0034276C  3B E6 00 00 */	addi r31, r6, 0
/* 80345B90 00342770  3A 67 00 00 */	addi r19, r7, 0
/* 80345B94 00342774  7F 60 42 14 */	add r27, r0, r8
/* 80345B98 00342778  48 00 17 CD */	bl OSDisableInterrupts
/* 80345B9C 0034277C  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80345BA0 00342780  3B 43 00 00 */	addi r26, r3, 0
/* 80345BA4 00342784  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 80345BA8 00342788  40 82 00 10 */	bne lbl_80345BB8
/* 80345BAC 0034278C  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80345BB0 00342790  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80345BB4 00342794  40 82 00 14 */	bne lbl_80345BC8
lbl_80345BB8:
/* 80345BB8 00342798  7F 43 D3 78 */	mr r3, r26
/* 80345BBC 0034279C  48 00 17 D1 */	bl OSRestoreInterrupts
/* 80345BC0 003427A0  38 60 00 00 */	li r3, 0
/* 80345BC4 003427A4  48 00 01 E8 */	b lbl_80345DAC
lbl_80345BC8:
/* 80345BC8 003427A8  92 7B 00 04 */	stw r19, 4(r27)
/* 80345BCC 003427AC  80 1B 00 04 */	lwz r0, 4(r27)
/* 80345BD0 003427B0  28 00 00 00 */	cmplwi r0, 0
/* 80345BD4 003427B4  41 82 00 28 */	beq lbl_80345BFC
/* 80345BD8 003427B8  38 7C 00 00 */	addi r3, r28, 0
/* 80345BDC 003427BC  38 80 00 00 */	li r4, 0
/* 80345BE0 003427C0  38 A0 00 01 */	li r5, 1
/* 80345BE4 003427C4  38 C0 00 00 */	li r6, 0
/* 80345BE8 003427C8  48 00 05 6D */	bl EXIClearInterrupts
/* 80345BEC 003427CC  1C 1C 00 03 */	mulli r0, r28, 3
/* 80345BF0 003427D0  3C 60 00 20 */	lis r3, 0x20
/* 80345BF4 003427D4  7C 63 04 30 */	srw r3, r3, r0
/* 80345BF8 003427D8  48 00 1B BD */	bl __OSUnmaskInterrupts
lbl_80345BFC:
/* 80345BFC 003427DC  80 1B 00 0C */	lwz r0, 0xc(r27)
/* 80345C00 003427E0  28 1F 00 00 */	cmplwi r31, 0
/* 80345C04 003427E4  60 00 00 02 */	ori r0, r0, 2
/* 80345C08 003427E8  90 1B 00 0C */	stw r0, 0xc(r27)
/* 80345C0C 003427EC  41 82 01 44 */	beq lbl_80345D50
/* 80345C10 003427F0  3B 00 00 00 */	li r24, 0
/* 80345C14 003427F4  7C 18 F0 00 */	cmpw r24, r30
/* 80345C18 003427F8  3B 20 00 00 */	li r25, 0
/* 80345C1C 003427FC  40 80 01 20 */	bge lbl_80345D3C
/* 80345C20 00342800  2C 1E 00 08 */	cmpwi r30, 8
/* 80345C24 00342804  38 7E FF F8 */	addi r3, r30, -8
/* 80345C28 00342808  40 81 01 7C */	ble lbl_80345DA4
/* 80345C2C 0034280C  38 03 00 07 */	addi r0, r3, 7
/* 80345C30 00342810  54 00 E8 FE */	srwi r0, r0, 3
/* 80345C34 00342814  2C 03 00 00 */	cmpwi r3, 0
/* 80345C38 00342818  7C 09 03 A6 */	mtctr r0
/* 80345C3C 0034281C  39 9D 00 00 */	addi r12, r29, 0
/* 80345C40 00342820  40 81 01 64 */	ble lbl_80345DA4
lbl_80345C44:
/* 80345C44 00342824  20 78 00 03 */	subfic r3, r24, 3
/* 80345C48 00342828  89 2C 00 00 */	lbz r9, 0(r12)
/* 80345C4C 0034282C  38 18 00 01 */	addi r0, r24, 1
/* 80345C50 00342830  89 4C 00 01 */	lbz r10, 1(r12)
/* 80345C54 00342834  54 67 18 38 */	slwi r7, r3, 3
/* 80345C58 00342838  89 0C 00 02 */	lbz r8, 2(r12)
/* 80345C5C 0034283C  20 A0 00 03 */	subfic r5, r0, 3
/* 80345C60 00342840  88 CC 00 03 */	lbz r6, 3(r12)
/* 80345C64 00342844  38 78 00 02 */	addi r3, r24, 2
/* 80345C68 00342848  88 8C 00 04 */	lbz r4, 4(r12)
/* 80345C6C 0034284C  7D 2B 38 30 */	slw r11, r9, r7
/* 80345C70 00342850  88 0C 00 05 */	lbz r0, 5(r12)
/* 80345C74 00342854  54 A9 18 38 */	slwi r9, r5, 3
/* 80345C78 00342858  8A 8C 00 06 */	lbz r20, 6(r12)
/* 80345C7C 0034285C  20 63 00 03 */	subfic r3, r3, 3
/* 80345C80 00342860  8A CC 00 07 */	lbz r22, 7(r12)
/* 80345C84 00342864  54 67 18 38 */	slwi r7, r3, 3
/* 80345C88 00342868  7C B8 00 D0 */	neg r5, r24
/* 80345C8C 0034286C  38 78 00 04 */	addi r3, r24, 4
/* 80345C90 00342870  54 A5 18 38 */	slwi r5, r5, 3
/* 80345C94 00342874  20 63 00 03 */	subfic r3, r3, 3
/* 80345C98 00342878  3A 78 00 05 */	addi r19, r24, 5
/* 80345C9C 0034287C  54 63 18 38 */	slwi r3, r3, 3
/* 80345CA0 00342880  22 73 00 03 */	subfic r19, r19, 3
/* 80345CA4 00342884  3A B8 00 06 */	addi r21, r24, 6
/* 80345CA8 00342888  56 73 18 38 */	slwi r19, r19, 3
/* 80345CAC 0034288C  22 B5 00 03 */	subfic r21, r21, 3
/* 80345CB0 00342890  3A F8 00 07 */	addi r23, r24, 7
/* 80345CB4 00342894  56 B5 18 38 */	slwi r21, r21, 3
/* 80345CB8 00342898  22 F7 00 03 */	subfic r23, r23, 3
/* 80345CBC 0034289C  56 F7 18 38 */	slwi r23, r23, 3
/* 80345CC0 003428A0  7F 39 5B 78 */	or r25, r25, r11
/* 80345CC4 003428A4  7D 49 48 30 */	slw r9, r10, r9
/* 80345CC8 003428A8  7F 39 4B 78 */	or r25, r25, r9
/* 80345CCC 003428AC  7D 07 38 30 */	slw r7, r8, r7
/* 80345CD0 003428B0  7F 39 3B 78 */	or r25, r25, r7
/* 80345CD4 003428B4  7C C5 28 30 */	slw r5, r6, r5
/* 80345CD8 003428B8  7F 39 2B 78 */	or r25, r25, r5
/* 80345CDC 003428BC  7C 83 18 30 */	slw r3, r4, r3
/* 80345CE0 003428C0  7F 39 1B 78 */	or r25, r25, r3
/* 80345CE4 003428C4  7C 00 98 30 */	slw r0, r0, r19
/* 80345CE8 003428C8  7F 39 03 78 */	or r25, r25, r0
/* 80345CEC 003428CC  7E 80 A8 30 */	slw r0, r20, r21
/* 80345CF0 003428D0  7F 39 03 78 */	or r25, r25, r0
/* 80345CF4 003428D4  7E C0 B8 30 */	slw r0, r22, r23
/* 80345CF8 003428D8  7F 39 03 78 */	or r25, r25, r0
/* 80345CFC 003428DC  39 8C 00 08 */	addi r12, r12, 8
/* 80345D00 003428E0  3B 18 00 08 */	addi r24, r24, 8
/* 80345D04 003428E4  42 00 FF 40 */	bdnz lbl_80345C44
/* 80345D08 003428E8  48 00 00 9C */	b lbl_80345DA4
lbl_80345D0C:
/* 80345D0C 003428EC  7C 18 F0 50 */	subf r0, r24, r30
/* 80345D10 003428F0  7C 18 F0 00 */	cmpw r24, r30
/* 80345D14 003428F4  7C 09 03 A6 */	mtctr r0
/* 80345D18 003428F8  40 80 00 24 */	bge lbl_80345D3C
lbl_80345D1C:
/* 80345D1C 003428FC  20 18 00 03 */	subfic r0, r24, 3
/* 80345D20 00342900  88 64 00 00 */	lbz r3, 0(r4)
/* 80345D24 00342904  54 00 18 38 */	slwi r0, r0, 3
/* 80345D28 00342908  7C 60 00 30 */	slw r0, r3, r0
/* 80345D2C 0034290C  7F 39 03 78 */	or r25, r25, r0
/* 80345D30 00342910  38 84 00 01 */	addi r4, r4, 1
/* 80345D34 00342914  3B 18 00 01 */	addi r24, r24, 1
/* 80345D38 00342918  42 00 FF E4 */	bdnz lbl_80345D1C
lbl_80345D3C:
/* 80345D3C 0034291C  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80345D40 00342920  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80345D44 00342924  38 63 68 00 */	addi r3, r3, 0xCC006800@l
/* 80345D48 00342928  7C 63 02 14 */	add r3, r3, r0
/* 80345D4C 0034292C  93 23 00 10 */	stw r25, 0x10(r3)
lbl_80345D50:
/* 80345D50 00342930  28 1F 00 01 */	cmplwi r31, 1
/* 80345D54 00342934  93 BB 00 14 */	stw r29, 0x14(r27)
/* 80345D58 00342938  41 82 00 0C */	beq lbl_80345D64
/* 80345D5C 0034293C  7F C3 F3 78 */	mr r3, r30
/* 80345D60 00342940  48 00 00 08 */	b lbl_80345D68
lbl_80345D64:
/* 80345D64 00342944  38 60 00 00 */	li r3, 0
lbl_80345D68:
/* 80345D68 00342948  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80345D6C 0034294C  90 7B 00 10 */	stw r3, 0x10(r27)
/* 80345D70 00342950  57 E5 10 3A */	slwi r5, r31, 2
/* 80345D74 00342954  38 9E FF FF */	addi r4, r30, -1
/* 80345D78 00342958  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80345D7C 0034295C  38 63 68 00 */	addi r3, r3, 0xCC006800@l
/* 80345D80 00342960  60 A5 00 01 */	ori r5, r5, 1
/* 80345D84 00342964  54 84 20 36 */	slwi r4, r4, 4
/* 80345D88 00342968  7C A4 23 78 */	or r4, r5, r4
/* 80345D8C 0034296C  7C 63 02 14 */	add r3, r3, r0
/* 80345D90 00342970  90 83 00 0C */	stw r4, 0xc(r3)
/* 80345D94 00342974  7F 43 D3 78 */	mr r3, r26
/* 80345D98 00342978  48 00 15 F5 */	bl OSRestoreInterrupts
/* 80345D9C 0034297C  38 60 00 01 */	li r3, 1
/* 80345DA0 00342980  48 00 00 0C */	b lbl_80345DAC
lbl_80345DA4:
/* 80345DA4 00342984  7C 9D C2 14 */	add r4, r29, r24
/* 80345DA8 00342988  4B FF FF 64 */	b lbl_80345D0C
lbl_80345DAC:
/* 80345DAC 0034298C  BA 61 00 24 */	lmw r19, 0x24(r1)
/* 80345DB0 00342990  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80345DB4 00342994  38 21 00 58 */	addi r1, r1, 0x58
/* 80345DB8 00342998  7C 08 03 A6 */	mtlr r0
/* 80345DBC 0034299C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t EXISync();

#pragma push
asm unk_t EXIImmEx()
{ // clang-format off
    nofralloc
/* 80345DC0 003429A0  7C 08 02 A6 */	mflr r0
/* 80345DC4 003429A4  90 01 00 04 */	stw r0, 4(r1)
/* 80345DC8 003429A8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80345DCC 003429AC  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80345DD0 003429B0  3B 63 00 00 */	addi r27, r3, 0
/* 80345DD4 003429B4  3B 84 00 00 */	addi r28, r4, 0
/* 80345DD8 003429B8  3B A5 00 00 */	addi r29, r5, 0
/* 80345DDC 003429BC  3B C6 00 00 */	addi r30, r6, 0
/* 80345DE0 003429C0  48 00 00 60 */	b lbl_80345E40
lbl_80345DE4:
/* 80345DE4 003429C4  2C 1D 00 04 */	cmpwi r29, 4
/* 80345DE8 003429C8  40 80 00 0C */	bge lbl_80345DF4
/* 80345DEC 003429CC  7F BF EB 78 */	mr r31, r29
/* 80345DF0 003429D0  48 00 00 08 */	b lbl_80345DF8
lbl_80345DF4:
/* 80345DF4 003429D4  3B E0 00 04 */	li r31, 4
lbl_80345DF8:
/* 80345DF8 003429D8  38 BF 00 00 */	addi r5, r31, 0
/* 80345DFC 003429DC  38 7B 00 00 */	addi r3, r27, 0
/* 80345E00 003429E0  38 9C 00 00 */	addi r4, r28, 0
/* 80345E04 003429E4  38 DE 00 00 */	addi r6, r30, 0
/* 80345E08 003429E8  38 E0 00 00 */	li r7, 0
/* 80345E0C 003429EC  4B FF FD 59 */	bl EXIImm
/* 80345E10 003429F0  2C 03 00 00 */	cmpwi r3, 0
/* 80345E14 003429F4  40 82 00 0C */	bne lbl_80345E20
/* 80345E18 003429F8  38 60 00 00 */	li r3, 0
/* 80345E1C 003429FC  48 00 00 30 */	b lbl_80345E4C
lbl_80345E20:
/* 80345E20 00342A00  7F 63 DB 78 */	mr r3, r27
/* 80345E24 00342A04  48 00 01 29 */	bl EXISync
/* 80345E28 00342A08  2C 03 00 00 */	cmpwi r3, 0
/* 80345E2C 00342A0C  40 82 00 0C */	bne lbl_80345E38
/* 80345E30 00342A10  38 60 00 00 */	li r3, 0
/* 80345E34 00342A14  48 00 00 18 */	b lbl_80345E4C
lbl_80345E38:
/* 80345E38 00342A18  7F 9C FA 14 */	add r28, r28, r31
/* 80345E3C 00342A1C  7F BF E8 50 */	subf r29, r31, r29
lbl_80345E40:
/* 80345E40 00342A20  2C 1D 00 00 */	cmpwi r29, 0
/* 80345E44 00342A24  40 82 FF A0 */	bne lbl_80345DE4
/* 80345E48 00342A28  38 60 00 01 */	li r3, 1
lbl_80345E4C:
/* 80345E4C 00342A2C  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80345E50 00342A30  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80345E54 00342A34  38 21 00 30 */	addi r1, r1, 0x30
/* 80345E58 00342A38  7C 08 03 A6 */	mtlr r0
/* 80345E5C 00342A3C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t EXIDma()
{ // clang-format off
    nofralloc
/* 80345E60 00342A40  7C 08 02 A6 */	mflr r0
/* 80345E64 00342A44  90 01 00 04 */	stw r0, 4(r1)
/* 80345E68 00342A48  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80345E6C 00342A4C  BF 21 00 24 */	stmw r25, 0x24(r1)
/* 80345E70 00342A50  3B 63 00 00 */	addi r27, r3, 0
/* 80345E74 00342A54  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80345E78 00342A58  57 68 30 32 */	slwi r8, r27, 6
/* 80345E7C 00342A5C  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80345E80 00342A60  3B 84 00 00 */	addi r28, r4, 0
/* 80345E84 00342A64  3B A5 00 00 */	addi r29, r5, 0
/* 80345E88 00342A68  3B C6 00 00 */	addi r30, r6, 0
/* 80345E8C 00342A6C  3B 27 00 00 */	addi r25, r7, 0
/* 80345E90 00342A70  7F 40 42 14 */	add r26, r0, r8
/* 80345E94 00342A74  48 00 14 D1 */	bl OSDisableInterrupts
/* 80345E98 00342A78  80 1A 00 0C */	lwz r0, 0xc(r26)
/* 80345E9C 00342A7C  3B E3 00 00 */	addi r31, r3, 0
/* 80345EA0 00342A80  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 80345EA4 00342A84  40 82 00 10 */	bne lbl_80345EB4
/* 80345EA8 00342A88  80 1A 00 0C */	lwz r0, 0xc(r26)
/* 80345EAC 00342A8C  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80345EB0 00342A90  40 82 00 14 */	bne lbl_80345EC4
lbl_80345EB4:
/* 80345EB4 00342A94  7F E3 FB 78 */	mr r3, r31
/* 80345EB8 00342A98  48 00 14 D5 */	bl OSRestoreInterrupts
/* 80345EBC 00342A9C  38 60 00 00 */	li r3, 0
/* 80345EC0 00342AA0  48 00 00 78 */	b lbl_80345F38
lbl_80345EC4:
/* 80345EC4 00342AA4  93 3A 00 04 */	stw r25, 4(r26)
/* 80345EC8 00342AA8  80 1A 00 04 */	lwz r0, 4(r26)
/* 80345ECC 00342AAC  28 00 00 00 */	cmplwi r0, 0
/* 80345ED0 00342AB0  41 82 00 28 */	beq lbl_80345EF8
/* 80345ED4 00342AB4  38 7B 00 00 */	addi r3, r27, 0
/* 80345ED8 00342AB8  38 80 00 00 */	li r4, 0
/* 80345EDC 00342ABC  38 A0 00 01 */	li r5, 1
/* 80345EE0 00342AC0  38 C0 00 00 */	li r6, 0
/* 80345EE4 00342AC4  48 00 02 71 */	bl EXIClearInterrupts
/* 80345EE8 00342AC8  1C 1B 00 03 */	mulli r0, r27, 3
/* 80345EEC 00342ACC  3C 60 00 20 */	lis r3, 0x20
/* 80345EF0 00342AD0  7C 63 04 30 */	srw r3, r3, r0
/* 80345EF4 00342AD4  48 00 18 C1 */	bl __OSUnmaskInterrupts
lbl_80345EF8:
/* 80345EF8 00342AD8  80 1A 00 0C */	lwz r0, 0xc(r26)
/* 80345EFC 00342ADC  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80345F00 00342AE0  1C BB 00 14 */	mulli r5, r27, 0x14
/* 80345F04 00342AE4  60 04 00 01 */	ori r4, r0, 1
/* 80345F08 00342AE8  38 03 68 00 */	addi r0, r3, 0xCC006800@l
/* 80345F0C 00342AEC  90 9A 00 0C */	stw r4, 0xc(r26)
/* 80345F10 00342AF0  57 83 01 B4 */	rlwinm r3, r28, 0, 6, 0x1a
/* 80345F14 00342AF4  7C 80 2A 14 */	add r4, r0, r5
/* 80345F18 00342AF8  90 64 00 04 */	stw r3, 4(r4)
/* 80345F1C 00342AFC  57 C0 10 3A */	slwi r0, r30, 2
/* 80345F20 00342B00  60 00 00 03 */	ori r0, r0, 3
/* 80345F24 00342B04  93 A4 00 08 */	stw r29, 8(r4)
/* 80345F28 00342B08  7F E3 FB 78 */	mr r3, r31
/* 80345F2C 00342B0C  90 04 00 0C */	stw r0, 0xc(r4)
/* 80345F30 00342B10  48 00 14 5D */	bl OSRestoreInterrupts
/* 80345F34 00342B14  38 60 00 01 */	li r3, 1
lbl_80345F38:
/* 80345F38 00342B18  BB 21 00 24 */	lmw r25, 0x24(r1)
/* 80345F3C 00342B1C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80345F40 00342B20  38 21 00 40 */	addi r1, r1, 0x40
/* 80345F44 00342B24  7C 08 03 A6 */	mtlr r0
/* 80345F48 00342B28  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t __OSGetDIConfig();

#pragma push
asm unk_t EXISync()
{ // clang-format off
    nofralloc
/* 80345F4C 00342B2C  7C 08 02 A6 */	mflr r0
/* 80345F50 00342B30  3C A0 80 4A */	lis r5, lbl_804A7C80@ha
/* 80345F54 00342B34  90 01 00 04 */	stw r0, 4(r1)
/* 80345F58 00342B38  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 80345F5C 00342B3C  38 05 7C 80 */	addi r0, r5, lbl_804A7C80@l
/* 80345F60 00342B40  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80345F64 00342B44  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80345F68 00342B48  1F C3 00 14 */	mulli r30, r3, 0x14
/* 80345F6C 00342B4C  3B A4 68 00 */	addi r29, r4, 0xCC006800@l
/* 80345F70 00342B50  54 63 30 32 */	slwi r3, r3, 6
/* 80345F74 00342B54  7F E0 1A 14 */	add r31, r0, r3
/* 80345F78 00342B58  7F BD F2 14 */	add r29, r29, r30
/* 80345F7C 00342B5C  3B 80 00 00 */	li r28, 0
/* 80345F80 00342B60  48 00 01 B0 */	b lbl_80346130
lbl_80345F84:
/* 80345F84 00342B64  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80345F88 00342B68  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80345F8C 00342B6C  40 82 01 A4 */	bne lbl_80346130
/* 80345F90 00342B70  48 00 13 D5 */	bl OSDisableInterrupts
/* 80345F94 00342B74  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345F98 00342B78  3B 63 00 00 */	addi r27, r3, 0
/* 80345F9C 00342B7C  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80345FA0 00342B80  41 82 01 84 */	beq lbl_80346124
/* 80345FA4 00342B84  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345FA8 00342B88  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 80345FAC 00342B8C  41 82 01 34 */	beq lbl_803460E0
/* 80345FB0 00342B90  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80345FB4 00342B94  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80345FB8 00342B98  41 82 01 1C */	beq lbl_803460D4
/* 80345FBC 00342B9C  80 9F 00 10 */	lwz r4, 0x10(r31)
/* 80345FC0 00342BA0  2C 04 00 00 */	cmpwi r4, 0
/* 80345FC4 00342BA4  41 82 01 10 */	beq lbl_803460D4
/* 80345FC8 00342BA8  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80345FCC 00342BAC  80 FF 00 14 */	lwz r7, 0x14(r31)
/* 80345FD0 00342BB0  38 03 68 00 */	addi r0, r3, 0xCC006800@l
/* 80345FD4 00342BB4  7C 60 F2 14 */	add r3, r0, r30
/* 80345FD8 00342BB8  80 C3 00 10 */	lwz r6, 0x10(r3)
/* 80345FDC 00342BBC  38 A0 00 00 */	li r5, 0
/* 80345FE0 00342BC0  40 81 00 F4 */	ble lbl_803460D4
/* 80345FE4 00342BC4  2C 04 00 08 */	cmpwi r4, 8
/* 80345FE8 00342BC8  38 64 FF F8 */	addi r3, r4, -8
/* 80345FEC 00342BCC  40 81 00 BC */	ble lbl_803460A8
/* 80345FF0 00342BD0  38 03 00 07 */	addi r0, r3, 7
/* 80345FF4 00342BD4  54 00 E8 FE */	srwi r0, r0, 3
/* 80345FF8 00342BD8  2C 03 00 00 */	cmpwi r3, 0
/* 80345FFC 00342BDC  7C 09 03 A6 */	mtctr r0
/* 80346000 00342BE0  40 81 00 A8 */	ble lbl_803460A8
lbl_80346004:
/* 80346004 00342BE4  20 05 00 03 */	subfic r0, r5, 3
/* 80346008 00342BE8  54 03 18 38 */	slwi r3, r0, 3
/* 8034600C 00342BEC  38 05 00 01 */	addi r0, r5, 1
/* 80346010 00342BF0  7C C8 1C 30 */	srw r8, r6, r3
/* 80346014 00342BF4  20 00 00 03 */	subfic r0, r0, 3
/* 80346018 00342BF8  99 07 00 00 */	stb r8, 0(r7)
/* 8034601C 00342BFC  54 03 18 38 */	slwi r3, r0, 3
/* 80346020 00342C00  38 05 00 02 */	addi r0, r5, 2
/* 80346024 00342C04  7C C3 1C 30 */	srw r3, r6, r3
/* 80346028 00342C08  20 00 00 03 */	subfic r0, r0, 3
/* 8034602C 00342C0C  98 67 00 01 */	stb r3, 1(r7)
/* 80346030 00342C10  54 00 18 38 */	slwi r0, r0, 3
/* 80346034 00342C14  7C C0 04 30 */	srw r0, r6, r0
/* 80346038 00342C18  7D 05 00 D0 */	neg r8, r5
/* 8034603C 00342C1C  98 07 00 02 */	stb r0, 2(r7)
/* 80346040 00342C20  55 09 18 38 */	slwi r9, r8, 3
/* 80346044 00342C24  39 05 00 04 */	addi r8, r5, 4
/* 80346048 00342C28  7C CC 4C 30 */	srw r12, r6, r9
/* 8034604C 00342C2C  21 08 00 03 */	subfic r8, r8, 3
/* 80346050 00342C30  99 87 00 03 */	stb r12, 3(r7)
/* 80346054 00342C34  55 09 18 38 */	slwi r9, r8, 3
/* 80346058 00342C38  39 05 00 05 */	addi r8, r5, 5
/* 8034605C 00342C3C  7C CB 4C 30 */	srw r11, r6, r9
/* 80346060 00342C40  21 08 00 03 */	subfic r8, r8, 3
/* 80346064 00342C44  99 67 00 04 */	stb r11, 4(r7)
/* 80346068 00342C48  55 09 18 38 */	slwi r9, r8, 3
/* 8034606C 00342C4C  7C CA 4C 30 */	srw r10, r6, r9
/* 80346070 00342C50  39 05 00 06 */	addi r8, r5, 6
/* 80346074 00342C54  99 47 00 05 */	stb r10, 5(r7)
/* 80346078 00342C58  21 28 00 03 */	subfic r9, r8, 3
/* 8034607C 00342C5C  39 05 00 07 */	addi r8, r5, 7
/* 80346080 00342C60  55 29 18 38 */	slwi r9, r9, 3
/* 80346084 00342C64  7C C9 4C 30 */	srw r9, r6, r9
/* 80346088 00342C68  21 08 00 03 */	subfic r8, r8, 3
/* 8034608C 00342C6C  99 27 00 06 */	stb r9, 6(r7)
/* 80346090 00342C70  55 08 18 38 */	slwi r8, r8, 3
/* 80346094 00342C74  7C C8 44 30 */	srw r8, r6, r8
/* 80346098 00342C78  99 07 00 07 */	stb r8, 7(r7)
/* 8034609C 00342C7C  38 E7 00 08 */	addi r7, r7, 8
/* 803460A0 00342C80  38 A5 00 08 */	addi r5, r5, 8
/* 803460A4 00342C84  42 00 FF 60 */	bdnz lbl_80346004
lbl_803460A8:
/* 803460A8 00342C88  7C 05 20 50 */	subf r0, r5, r4
/* 803460AC 00342C8C  7C 05 20 00 */	cmpw r5, r4
/* 803460B0 00342C90  7C 09 03 A6 */	mtctr r0
/* 803460B4 00342C94  40 80 00 20 */	bge lbl_803460D4
lbl_803460B8:
/* 803460B8 00342C98  20 05 00 03 */	subfic r0, r5, 3
/* 803460BC 00342C9C  54 00 18 38 */	slwi r0, r0, 3
/* 803460C0 00342CA0  7C C0 04 30 */	srw r0, r6, r0
/* 803460C4 00342CA4  98 07 00 00 */	stb r0, 0(r7)
/* 803460C8 00342CA8  38 E7 00 01 */	addi r7, r7, 1
/* 803460CC 00342CAC  38 A5 00 01 */	addi r5, r5, 1
/* 803460D0 00342CB0  42 00 FF E8 */	bdnz lbl_803460B8
lbl_803460D4:
/* 803460D4 00342CB4  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 803460D8 00342CB8  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 803460DC 00342CBC  90 1F 00 0C */	stw r0, 0xc(r31)
lbl_803460E0:
/* 803460E0 00342CC0  4B FF D6 2D */	bl __OSGetDIConfig
/* 803460E4 00342CC4  28 03 00 FF */	cmplwi r3, 0xff
/* 803460E8 00342CC8  40 82 00 38 */	bne lbl_80346120
/* 803460EC 00342CCC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 803460F0 00342CD0  2C 00 00 04 */	cmpwi r0, 4
/* 803460F4 00342CD4  40 82 00 2C */	bne lbl_80346120
/* 803460F8 00342CD8  80 1D 00 00 */	lwz r0, 0(r29)
/* 803460FC 00342CDC  54 00 06 77 */	rlwinm. r0, r0, 0, 0x19, 0x1b
/* 80346100 00342CE0  40 82 00 20 */	bne lbl_80346120
/* 80346104 00342CE4  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 80346108 00342CE8  38 03 68 00 */	addi r0, r3, 0xCC006800@l
/* 8034610C 00342CEC  7C 60 F2 14 */	add r3, r0, r30
/* 80346110 00342CF0  80 63 00 10 */	lwz r3, 0x10(r3)
/* 80346114 00342CF4  3C 03 FE FF */	addis r0, r3, 0xfeff
/* 80346118 00342CF8  28 00 00 00 */	cmplwi r0, 0
/* 8034611C 00342CFC  41 82 00 08 */	beq lbl_80346124
lbl_80346120:
/* 80346120 00342D00  3B 80 00 01 */	li r28, 1
lbl_80346124:
/* 80346124 00342D04  7F 63 DB 78 */	mr r3, r27
/* 80346128 00342D08  48 00 12 65 */	bl OSRestoreInterrupts
/* 8034612C 00342D0C  48 00 00 10 */	b lbl_8034613C
lbl_80346130:
/* 80346130 00342D10  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346134 00342D14  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 80346138 00342D18  40 82 FE 4C */	bne lbl_80345F84
lbl_8034613C:
/* 8034613C 00342D1C  7F 83 E3 78 */	mr r3, r28
/* 80346140 00342D20  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80346144 00342D24  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80346148 00342D28  38 21 00 30 */	addi r1, r1, 0x30
/* 8034614C 00342D2C  7C 08 03 A6 */	mtlr r0
/* 80346150 00342D30  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t EXIClearInterrupts()
{ // clang-format off
    nofralloc
/* 80346154 00342D34  1C 03 00 14 */	mulli r0, r3, 0x14
/* 80346158 00342D38  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 8034615C 00342D3C  38 E3 68 00 */	addi r7, r3, 0xCC006800@l
/* 80346160 00342D40  7C E7 02 14 */	add r7, r7, r0
/* 80346164 00342D44  80 07 00 00 */	lwz r0, 0(r7)
/* 80346168 00342D48  7C 03 03 78 */	mr r3, r0
/* 8034616C 00342D4C  70 00 07 F5 */	andi. r0, r0, 0x7f5
/* 80346170 00342D50  2C 04 00 00 */	cmpwi r4, 0
/* 80346174 00342D54  41 82 00 08 */	beq lbl_8034617C
/* 80346178 00342D58  60 00 00 02 */	ori r0, r0, 2
lbl_8034617C:
/* 8034617C 00342D5C  2C 05 00 00 */	cmpwi r5, 0
/* 80346180 00342D60  41 82 00 08 */	beq lbl_80346188
/* 80346184 00342D64  60 00 00 08 */	ori r0, r0, 8
lbl_80346188:
/* 80346188 00342D68  2C 06 00 00 */	cmpwi r6, 0
/* 8034618C 00342D6C  41 82 00 08 */	beq lbl_80346194
/* 80346190 00342D70  60 00 08 00 */	ori r0, r0, 0x800
lbl_80346194:
/* 80346194 00342D74  90 07 00 00 */	stw r0, 0(r7)
/* 80346198 00342D78  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t EXISetExiCallback()
{ // clang-format off
    nofralloc
/* 8034619C 00342D7C  7C 08 02 A6 */	mflr r0
/* 803461A0 00342D80  90 01 00 04 */	stw r0, 4(r1)
/* 803461A4 00342D84  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 803461A8 00342D88  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 803461AC 00342D8C  3B 63 00 00 */	addi r27, r3, 0
/* 803461B0 00342D90  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 803461B4 00342D94  57 60 30 32 */	slwi r0, r27, 6
/* 803461B8 00342D98  3B E3 7C 80 */	addi r31, r3, lbl_804A7C80@l
/* 803461BC 00342D9C  7F DF 02 14 */	add r30, r31, r0
/* 803461C0 00342DA0  3B 84 00 00 */	addi r28, r4, 0
/* 803461C4 00342DA4  48 00 11 A1 */	bl OSDisableInterrupts
/* 803461C8 00342DA8  83 BE 00 00 */	lwz r29, 0(r30)
/* 803461CC 00342DAC  2C 1B 00 02 */	cmpwi r27, 2
/* 803461D0 00342DB0  93 9E 00 00 */	stw r28, 0(r30)
/* 803461D4 00342DB4  7C 7C 1B 78 */	mr r28, r3
/* 803461D8 00342DB8  41 82 00 14 */	beq lbl_803461EC
/* 803461DC 00342DBC  38 7B 00 00 */	addi r3, r27, 0
/* 803461E0 00342DC0  38 9E 00 00 */	addi r4, r30, 0
/* 803461E4 00342DC4  4B FF F8 8D */	bl SetExiInterruptMask
/* 803461E8 00342DC8  48 00 00 10 */	b lbl_803461F8
lbl_803461EC:
/* 803461EC 00342DCC  38 9F 00 00 */	addi r4, r31, 0
/* 803461F0 00342DD0  38 60 00 00 */	li r3, 0
/* 803461F4 00342DD4  4B FF F8 7D */	bl SetExiInterruptMask
lbl_803461F8:
/* 803461F8 00342DD8  7F 83 E3 78 */	mr r3, r28
/* 803461FC 00342DDC  48 00 11 91 */	bl OSRestoreInterrupts
/* 80346200 00342DE0  7F A3 EB 78 */	mr r3, r29
/* 80346204 00342DE4  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80346208 00342DE8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8034620C 00342DEC  38 21 00 28 */	addi r1, r1, 0x28
/* 80346210 00342DF0  7C 08 03 A6 */	mtlr r0
/* 80346214 00342DF4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t __div2i();


#pragma push
asm unk_t __EXIProbe()
{ // clang-format off
    nofralloc
/* 80346218 00342DF8  7C 08 02 A6 */	mflr r0
/* 8034621C 00342DFC  90 01 00 04 */	stw r0, 4(r1)
/* 80346220 00342E00  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80346224 00342E04  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80346228 00342E08  3B 83 00 00 */	addi r28, r3, 0
/* 8034622C 00342E0C  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346230 00342E10  2C 1C 00 02 */	cmpwi r28, 2
/* 80346234 00342E14  57 84 30 32 */	slwi r4, r28, 6
/* 80346238 00342E18  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 8034623C 00342E1C  7F E0 22 14 */	add r31, r0, r4
/* 80346240 00342E20  40 82 00 0C */	bne lbl_8034624C
/* 80346244 00342E24  38 60 00 01 */	li r3, 1
/* 80346248 00342E28  48 00 01 30 */	b lbl_80346378
lbl_8034624C:
/* 8034624C 00342E2C  3B A0 00 01 */	li r29, 1
/* 80346250 00342E30  48 00 11 15 */	bl OSDisableInterrupts
/* 80346254 00342E34  1C BC 00 14 */	mulli r5, r28, 0x14
/* 80346258 00342E38  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 8034625C 00342E3C  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 80346260 00342E40  38 C4 68 00 */	addi r6, r4, 0xCC006800@l
/* 80346264 00342E44  7C C6 2A 14 */	add r6, r6, r5
/* 80346268 00342E48  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 8034626C 00342E4C  80 E6 00 00 */	lwz r7, 0(r6)
/* 80346270 00342E50  7C 7E 1B 78 */	mr r30, r3
/* 80346274 00342E54  40 82 00 CC */	bne lbl_80346340
/* 80346278 00342E58  54 E0 05 29 */	rlwinm. r0, r7, 0, 0x14, 0x14
/* 8034627C 00342E5C  41 82 00 2C */	beq lbl_803462A8
/* 80346280 00342E60  80 A6 00 00 */	lwz r5, 0(r6)
/* 80346284 00342E64  3C 60 80 00 */	lis r3, 0x800030C0@ha
/* 80346288 00342E68  38 80 00 00 */	li r4, 0
/* 8034628C 00342E6C  70 A5 07 F5 */	andi. r5, r5, 0x7f5
/* 80346290 00342E70  57 80 10 3A */	slwi r0, r28, 2
/* 80346294 00342E74  38 63 30 C0 */	addi r3, r3, 0x800030C0@l
/* 80346298 00342E78  60 A5 08 00 */	ori r5, r5, 0x800
/* 8034629C 00342E7C  90 A6 00 00 */	stw r5, 0(r6)
/* 803462A0 00342E80  90 9F 00 20 */	stw r4, 0x20(r31)
/* 803462A4 00342E84  7C 83 01 2E */	stwx r4, r3, r0
lbl_803462A8:
/* 803462A8 00342E88  54 E0 04 E7 */	rlwinm. r0, r7, 0, 0x13, 0x13
/* 803462AC 00342E8C  41 82 00 74 */	beq lbl_80346320
/* 803462B0 00342E90  3F E0 80 00 */	lis r31, 0x800000F8@ha
/* 803462B4 00342E94  80 1F 00 F8 */	lwz r0, 0x800000F8@l(r31)
/* 803462B8 00342E98  3C 60 10 62 */	lis r3, 0x10624DD3@ha
/* 803462BC 00342E9C  38 63 4D D3 */	addi r3, r3, 0x10624DD3@l
/* 803462C0 00342EA0  54 00 F0 BE */	srwi r0, r0, 2
/* 803462C4 00342EA4  7C 03 00 16 */	mulhwu r0, r3, r0
/* 803462C8 00342EA8  54 1B D1 BE */	srwi r27, r0, 6
/* 803462CC 00342EAC  48 00 61 25 */	bl OSGetTime
/* 803462D0 00342EB0  38 DB 00 00 */	addi r6, r27, 0
/* 803462D4 00342EB4  38 A0 00 00 */	li r5, 0
/* 803462D8 00342EB8  4B FD C7 31 */	bl __div2i
/* 803462DC 00342EBC  38 A0 00 00 */	li r5, 0
/* 803462E0 00342EC0  38 C0 00 64 */	li r6, 0x64
/* 803462E4 00342EC4  4B FD C7 25 */	bl __div2i
/* 803462E8 00342EC8  57 80 10 3A */	slwi r0, r28, 2
/* 803462EC 00342ECC  38 7F 30 C0 */	addi r3, r31, 0x30c0
/* 803462F0 00342ED0  7C 63 02 14 */	add r3, r3, r0
/* 803462F4 00342ED4  80 03 00 00 */	lwz r0, 0(r3)
/* 803462F8 00342ED8  38 84 00 01 */	addi r4, r4, 1
/* 803462FC 00342EDC  2C 00 00 00 */	cmpwi r0, 0
/* 80346300 00342EE0  40 82 00 08 */	bne lbl_80346308
/* 80346304 00342EE4  90 83 00 00 */	stw r4, 0(r3)
lbl_80346308:
/* 80346308 00342EE8  80 03 00 00 */	lwz r0, 0(r3)
/* 8034630C 00342EEC  7C 00 20 50 */	subf r0, r0, r4
/* 80346310 00342EF0  2C 00 00 03 */	cmpwi r0, 3
/* 80346314 00342EF4  40 80 00 58 */	bge lbl_8034636C
/* 80346318 00342EF8  3B A0 00 00 */	li r29, 0
/* 8034631C 00342EFC  48 00 00 50 */	b lbl_8034636C
lbl_80346320:
/* 80346320 00342F00  38 80 00 00 */	li r4, 0
/* 80346324 00342F04  3C 60 80 00 */	lis r3, 0x800030C0@ha
/* 80346328 00342F08  90 9F 00 20 */	stw r4, 0x20(r31)
/* 8034632C 00342F0C  57 80 10 3A */	slwi r0, r28, 2
/* 80346330 00342F10  38 63 30 C0 */	addi r3, r3, 0x800030C0@l
/* 80346334 00342F14  7C 83 01 2E */	stwx r4, r3, r0
/* 80346338 00342F18  3B A0 00 00 */	li r29, 0
/* 8034633C 00342F1C  48 00 00 30 */	b lbl_8034636C
lbl_80346340:
/* 80346340 00342F20  54 E0 04 E7 */	rlwinm. r0, r7, 0, 0x13, 0x13
/* 80346344 00342F24  41 82 00 0C */	beq lbl_80346350
/* 80346348 00342F28  54 E0 05 29 */	rlwinm. r0, r7, 0, 0x14, 0x14
/* 8034634C 00342F2C  41 82 00 20 */	beq lbl_8034636C
lbl_80346350:
/* 80346350 00342F30  38 80 00 00 */	li r4, 0
/* 80346354 00342F34  3C 60 80 00 */	lis r3, 0x800030C0@ha
/* 80346358 00342F38  90 9F 00 20 */	stw r4, 0x20(r31)
/* 8034635C 00342F3C  57 80 10 3A */	slwi r0, r28, 2
/* 80346360 00342F40  38 63 30 C0 */	addi r3, r3, 0x800030C0@l
/* 80346364 00342F44  7C 83 01 2E */	stwx r4, r3, r0
/* 80346368 00342F48  3B A0 00 00 */	li r29, 0
lbl_8034636C:
/* 8034636C 00342F4C  7F C3 F3 78 */	mr r3, r30
/* 80346370 00342F50  48 00 10 1D */	bl OSRestoreInterrupts
/* 80346374 00342F54  7F A3 EB 78 */	mr r3, r29
lbl_80346378:
/* 80346378 00342F58  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 8034637C 00342F5C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80346380 00342F60  38 21 00 28 */	addi r1, r1, 0x28
/* 80346384 00342F64  7C 08 03 A6 */	mtlr r0
/* 80346388 00342F68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

