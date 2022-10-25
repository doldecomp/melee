#include <dolphin/os/OSInterrupt.h>
#include <dolphin/types.h>

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

