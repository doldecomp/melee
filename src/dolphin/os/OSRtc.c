#include <dolphin/os/OSInterrupt.h>

extern unk_t lbl_804A7D60;
extern unk_t WriteSram();

#pragma push
asm unk_t WriteSramCallback()
{ // clang-format off
    nofralloc
/* 80348A90 00345670  7C 08 02 A6 */	mflr r0
/* 80348A94 00345674  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348A98 00345678  90 01 00 04 */	stw r0, 4(r1)
/* 80348A9C 0034567C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348AA0 00345680  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348AA4 00345684  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80348AA8 00345688  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80348AAC 0034568C  3B DF 00 40 */	addi r30, r31, 0x40
/* 80348AB0 00345690  80 9F 00 40 */	lwz r4, 0x40(r31)
/* 80348AB4 00345694  7C 7F 22 14 */	add r3, r31, r4
/* 80348AB8 00345698  20 A4 00 40 */	subfic r5, r4, 0x40
/* 80348ABC 0034569C  48 00 00 35 */	bl WriteSram
/* 80348AC0 003456A0  90 7F 00 4C */	stw r3, 0x4c(r31)
/* 80348AC4 003456A4  80 1F 00 4C */	lwz r0, 0x4c(r31)
/* 80348AC8 003456A8  2C 00 00 00 */	cmpwi r0, 0
/* 80348ACC 003456AC  41 82 00 0C */	beq lbl_80348AD8
/* 80348AD0 003456B0  38 00 00 40 */	li r0, 0x40
/* 80348AD4 003456B4  90 1E 00 00 */	stw r0, 0(r30)
lbl_80348AD8:
/* 80348AD8 003456B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80348ADC 003456BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80348AE0 003456C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80348AE4 003456C4  7C 08 03 A6 */	mtlr r0
/* 80348AE8 003456C8  38 21 00 18 */	addi r1, r1, 0x18
/* 80348AEC 003456CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t EXIDeselect();
extern unk_t EXIImmEx();
extern unk_t EXISync();
extern unk_t EXIImm();
extern unk_t EXIUnlock();
extern unk_t EXISelect();
extern unk_t EXILock();

#pragma push
asm unk_t WriteSram()
{ // clang-format off
    nofralloc
/* 80348AF0 003456D0  7C 08 02 A6 */	mflr r0
/* 80348AF4 003456D4  3C C0 80 35 */	lis r6, WriteSramCallback@ha
/* 80348AF8 003456D8  90 01 00 04 */	stw r0, 4(r1)
/* 80348AFC 003456DC  38 06 8A 90 */	addi r0, r6, WriteSramCallback@l
/* 80348B00 003456E0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80348B04 003456E4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80348B08 003456E8  3B E4 00 00 */	addi r31, r4, 0
/* 80348B0C 003456EC  38 80 00 01 */	li r4, 1
/* 80348B10 003456F0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80348B14 003456F4  3B C5 00 00 */	addi r30, r5, 0
/* 80348B18 003456F8  7C 05 03 78 */	mr r5, r0
/* 80348B1C 003456FC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80348B20 00345700  3B A3 00 00 */	addi r29, r3, 0
/* 80348B24 00345704  38 60 00 00 */	li r3, 0
/* 80348B28 00345708  4B FF E2 59 */	bl EXILock
/* 80348B2C 0034570C  2C 03 00 00 */	cmpwi r3, 0
/* 80348B30 00345710  40 82 00 0C */	bne lbl_80348B3C
/* 80348B34 00345714  38 60 00 00 */	li r3, 0
/* 80348B38 00345718  48 00 00 B4 */	b lbl_80348BEC
lbl_80348B3C:
/* 80348B3C 0034571C  38 60 00 00 */	li r3, 0
/* 80348B40 00345720  38 80 00 01 */	li r4, 1
/* 80348B44 00345724  38 A0 00 03 */	li r5, 3
/* 80348B48 00345728  4B FF DB 41 */	bl EXISelect
/* 80348B4C 0034572C  2C 03 00 00 */	cmpwi r3, 0
/* 80348B50 00345730  40 82 00 14 */	bne lbl_80348B64
/* 80348B54 00345734  38 60 00 00 */	li r3, 0
/* 80348B58 00345738  4B FF E3 1D */	bl EXIUnlock
/* 80348B5C 0034573C  38 60 00 00 */	li r3, 0
/* 80348B60 00345740  48 00 00 8C */	b lbl_80348BEC
lbl_80348B64:
/* 80348B64 00345744  57 FF 30 32 */	slwi r31, r31, 6
/* 80348B68 00345748  38 1F 01 00 */	addi r0, r31, 0x100
/* 80348B6C 0034574C  64 00 A0 00 */	oris r0, r0, 0xa000
/* 80348B70 00345750  90 01 00 14 */	stw r0, 0x14(r1)
/* 80348B74 00345754  38 81 00 14 */	addi r4, r1, 0x14
/* 80348B78 00345758  38 60 00 00 */	li r3, 0
/* 80348B7C 0034575C  38 A0 00 04 */	li r5, 4
/* 80348B80 00345760  38 C0 00 01 */	li r6, 1
/* 80348B84 00345764  38 E0 00 00 */	li r7, 0
/* 80348B88 00345768  4B FF CF DD */	bl EXIImm
/* 80348B8C 0034576C  7C 60 00 34 */	cntlzw r0, r3
/* 80348B90 00345770  54 1F D9 7E */	srwi r31, r0, 5
/* 80348B94 00345774  38 60 00 00 */	li r3, 0
/* 80348B98 00345778  4B FF D3 B5 */	bl EXISync
/* 80348B9C 0034577C  7C 60 00 34 */	cntlzw r0, r3
/* 80348BA0 00345780  54 00 D9 7E */	srwi r0, r0, 5
/* 80348BA4 00345784  38 9D 00 00 */	addi r4, r29, 0
/* 80348BA8 00345788  38 BE 00 00 */	addi r5, r30, 0
/* 80348BAC 0034578C  7F FF 03 78 */	or r31, r31, r0
/* 80348BB0 00345790  38 60 00 00 */	li r3, 0
/* 80348BB4 00345794  38 C0 00 01 */	li r6, 1
/* 80348BB8 00345798  4B FF D2 09 */	bl EXIImmEx
/* 80348BBC 0034579C  7C 60 00 34 */	cntlzw r0, r3
/* 80348BC0 003457A0  54 00 D9 7E */	srwi r0, r0, 5
/* 80348BC4 003457A4  7F FF 03 78 */	or r31, r31, r0
/* 80348BC8 003457A8  38 60 00 00 */	li r3, 0
/* 80348BCC 003457AC  4B FF DB E9 */	bl EXIDeselect
/* 80348BD0 003457B0  7C 60 00 34 */	cntlzw r0, r3
/* 80348BD4 003457B4  54 00 D9 7E */	srwi r0, r0, 5
/* 80348BD8 003457B8  7F FF 03 78 */	or r31, r31, r0
/* 80348BDC 003457BC  38 60 00 00 */	li r3, 0
/* 80348BE0 003457C0  4B FF E2 95 */	bl EXIUnlock
/* 80348BE4 003457C4  7F E0 00 34 */	cntlzw r0, r31
/* 80348BE8 003457C8  54 03 D9 7E */	srwi r3, r0, 5
lbl_80348BEC:
/* 80348BEC 003457CC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80348BF0 003457D0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80348BF4 003457D4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80348BF8 003457D8  7C 08 03 A6 */	mtlr r0
/* 80348BFC 003457DC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80348C00 003457E0  38 21 00 28 */	addi r1, r1, 0x28
/* 80348C04 003457E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t EXIDma();
extern unk_t DCInvalidateRange();

#pragma push
asm unk_t __OSInitSram()
{ // clang-format off
    nofralloc
/* 80348C08 003457E8  7C 08 02 A6 */	mflr r0
/* 80348C0C 003457EC  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348C10 003457F0  90 01 00 04 */	stw r0, 4(r1)
/* 80348C14 003457F4  38 80 00 40 */	li r4, 0x40
/* 80348C18 003457F8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348C1C 003457FC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348C20 00345800  3B E0 00 00 */	li r31, 0
/* 80348C24 00345804  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80348C28 00345808  3B C3 7D 60 */	addi r30, r3, lbl_804A7D60@l
/* 80348C2C 0034580C  38 7E 00 00 */	addi r3, r30, 0
/* 80348C30 00345810  93 FE 00 44 */	stw r31, 0x44(r30)
/* 80348C34 00345814  93 FE 00 48 */	stw r31, 0x48(r30)
/* 80348C38 00345818  4B FF BB A5 */	bl DCInvalidateRange
/* 80348C3C 0034581C  38 60 00 00 */	li r3, 0
/* 80348C40 00345820  38 80 00 01 */	li r4, 1
/* 80348C44 00345824  38 A0 00 00 */	li r5, 0
/* 80348C48 00345828  4B FF E1 39 */	bl EXILock
/* 80348C4C 0034582C  2C 03 00 00 */	cmpwi r3, 0
/* 80348C50 00345830  40 82 00 08 */	bne lbl_80348C58
/* 80348C54 00345834  48 00 00 C4 */	b lbl_80348D18
lbl_80348C58:
/* 80348C58 00345838  38 60 00 00 */	li r3, 0
/* 80348C5C 0034583C  38 80 00 01 */	li r4, 1
/* 80348C60 00345840  38 A0 00 03 */	li r5, 3
/* 80348C64 00345844  4B FF DA 25 */	bl EXISelect
/* 80348C68 00345848  2C 03 00 00 */	cmpwi r3, 0
/* 80348C6C 0034584C  40 82 00 10 */	bne lbl_80348C7C
/* 80348C70 00345850  38 60 00 00 */	li r3, 0
/* 80348C74 00345854  4B FF E2 01 */	bl EXIUnlock
/* 80348C78 00345858  48 00 00 A0 */	b lbl_80348D18
lbl_80348C7C:
/* 80348C7C 0034585C  3C 60 20 00 */	lis r3, 0x20000100@ha
/* 80348C80 00345860  38 03 01 00 */	addi r0, r3, 0x20000100@l
/* 80348C84 00345864  90 01 00 08 */	stw r0, 8(r1)
/* 80348C88 00345868  38 81 00 08 */	addi r4, r1, 8
/* 80348C8C 0034586C  38 60 00 00 */	li r3, 0
/* 80348C90 00345870  38 A0 00 04 */	li r5, 4
/* 80348C94 00345874  38 C0 00 01 */	li r6, 1
/* 80348C98 00345878  38 E0 00 00 */	li r7, 0
/* 80348C9C 0034587C  4B FF CE C9 */	bl EXIImm
/* 80348CA0 00345880  7C 60 00 34 */	cntlzw r0, r3
/* 80348CA4 00345884  54 1F D9 7E */	srwi r31, r0, 5
/* 80348CA8 00345888  38 60 00 00 */	li r3, 0
/* 80348CAC 0034588C  4B FF D2 A1 */	bl EXISync
/* 80348CB0 00345890  7C 60 00 34 */	cntlzw r0, r3
/* 80348CB4 00345894  54 00 D9 7E */	srwi r0, r0, 5
/* 80348CB8 00345898  38 9E 00 00 */	addi r4, r30, 0
/* 80348CBC 0034589C  7F FF 03 78 */	or r31, r31, r0
/* 80348CC0 003458A0  38 60 00 00 */	li r3, 0
/* 80348CC4 003458A4  38 A0 00 40 */	li r5, 0x40
/* 80348CC8 003458A8  38 C0 00 00 */	li r6, 0
/* 80348CCC 003458AC  38 E0 00 00 */	li r7, 0
/* 80348CD0 003458B0  4B FF D1 91 */	bl EXIDma
/* 80348CD4 003458B4  7C 60 00 34 */	cntlzw r0, r3
/* 80348CD8 003458B8  54 00 D9 7E */	srwi r0, r0, 5
/* 80348CDC 003458BC  7F FF 03 78 */	or r31, r31, r0
/* 80348CE0 003458C0  38 60 00 00 */	li r3, 0
/* 80348CE4 003458C4  4B FF D2 69 */	bl EXISync
/* 80348CE8 003458C8  7C 60 00 34 */	cntlzw r0, r3
/* 80348CEC 003458CC  54 00 D9 7E */	srwi r0, r0, 5
/* 80348CF0 003458D0  7F FF 03 78 */	or r31, r31, r0
/* 80348CF4 003458D4  38 60 00 00 */	li r3, 0
/* 80348CF8 003458D8  4B FF DA BD */	bl EXIDeselect
/* 80348CFC 003458DC  7C 60 00 34 */	cntlzw r0, r3
/* 80348D00 003458E0  54 00 D9 7E */	srwi r0, r0, 5
/* 80348D04 003458E4  7F FF 03 78 */	or r31, r31, r0
/* 80348D08 003458E8  38 60 00 00 */	li r3, 0
/* 80348D0C 003458EC  4B FF E1 69 */	bl EXIUnlock
/* 80348D10 003458F0  7F E0 00 34 */	cntlzw r0, r31
/* 80348D14 003458F4  54 1F D9 7E */	srwi r31, r0, 5
lbl_80348D18:
/* 80348D18 003458F8  93 FE 00 4C */	stw r31, 0x4c(r30)
/* 80348D1C 003458FC  38 00 00 40 */	li r0, 0x40
/* 80348D20 00345900  90 1E 00 40 */	stw r0, 0x40(r30)
/* 80348D24 00345904  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80348D28 00345908  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80348D2C 0034590C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80348D30 00345910  38 21 00 18 */	addi r1, r1, 0x18
/* 80348D34 00345914  7C 08 03 A6 */	mtlr r0
/* 80348D38 00345918  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSLockSram()
{ // clang-format off
    nofralloc
/* 80348D3C 0034591C  7C 08 02 A6 */	mflr r0
/* 80348D40 00345920  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348D44 00345924  90 01 00 04 */	stw r0, 4(r1)
/* 80348D48 00345928  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80348D4C 0034592C  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80348D50 00345930  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80348D54 00345934  4B FF E6 11 */	bl OSDisableInterrupts
/* 80348D58 00345938  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80348D5C 0034593C  38 9F 00 48 */	addi r4, r31, 0x48
/* 80348D60 00345940  2C 00 00 00 */	cmpwi r0, 0
/* 80348D64 00345944  41 82 00 10 */	beq lbl_80348D74
/* 80348D68 00345948  4B FF E6 25 */	bl OSRestoreInterrupts
/* 80348D6C 0034594C  3B E0 00 00 */	li r31, 0
/* 80348D70 00345950  48 00 00 10 */	b lbl_80348D80
lbl_80348D74:
/* 80348D74 00345954  90 7F 00 44 */	stw r3, 0x44(r31)
/* 80348D78 00345958  38 00 00 01 */	li r0, 1
/* 80348D7C 0034595C  90 04 00 00 */	stw r0, 0(r4)
lbl_80348D80:
/* 80348D80 00345960  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80348D84 00345964  7F E3 FB 78 */	mr r3, r31
/* 80348D88 00345968  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80348D8C 0034596C  38 21 00 10 */	addi r1, r1, 0x10
/* 80348D90 00345970  7C 08 03 A6 */	mtlr r0
/* 80348D94 00345974  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSLockSramEx()
{ // clang-format off
    nofralloc
/* 80348D98 00345978  7C 08 02 A6 */	mflr r0
/* 80348D9C 0034597C  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348DA0 00345980  90 01 00 04 */	stw r0, 4(r1)
/* 80348DA4 00345984  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80348DA8 00345988  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80348DAC 0034598C  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80348DB0 00345990  4B FF E5 B5 */	bl OSDisableInterrupts
/* 80348DB4 00345994  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80348DB8 00345998  38 9F 00 48 */	addi r4, r31, 0x48
/* 80348DBC 0034599C  2C 00 00 00 */	cmpwi r0, 0
/* 80348DC0 003459A0  41 82 00 10 */	beq lbl_80348DD0
/* 80348DC4 003459A4  4B FF E5 C9 */	bl OSRestoreInterrupts
/* 80348DC8 003459A8  38 60 00 00 */	li r3, 0
/* 80348DCC 003459AC  48 00 00 14 */	b lbl_80348DE0
lbl_80348DD0:
/* 80348DD0 003459B0  90 7F 00 44 */	stw r3, 0x44(r31)
/* 80348DD4 003459B4  38 00 00 01 */	li r0, 1
/* 80348DD8 003459B8  38 7F 00 14 */	addi r3, r31, 0x14
/* 80348DDC 003459BC  90 04 00 00 */	stw r0, 0(r4)
lbl_80348DE0:
/* 80348DE0 003459C0  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80348DE4 003459C4  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80348DE8 003459C8  38 21 00 10 */	addi r1, r1, 0x10
/* 80348DEC 003459CC  7C 08 03 A6 */	mtlr r0
/* 80348DF0 003459D0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t UnlockSram()
{ // clang-format off
    nofralloc
/* 80348DF4 003459D4  7C 08 02 A6 */	mflr r0
/* 80348DF8 003459D8  2C 03 00 00 */	cmpwi r3, 0
/* 80348DFC 003459DC  90 01 00 04 */	stw r0, 4(r1)
/* 80348E00 003459E0  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80348E04 003459E4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80348E08 003459E8  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80348E0C 003459EC  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 80348E10 003459F0  41 82 02 C4 */	beq lbl_803490D4
/* 80348E14 003459F4  28 04 00 00 */	cmplwi r4, 0
/* 80348E18 003459F8  40 82 01 B0 */	bne lbl_80348FC8
/* 80348E1C 003459FC  88 7F 00 13 */	lbz r3, 0x13(r31)
/* 80348E20 00345A00  54 60 07 BE */	clrlwi r0, r3, 0x1e
/* 80348E24 00345A04  28 00 00 02 */	cmplwi r0, 2
/* 80348E28 00345A08  40 81 00 0C */	ble lbl_80348E34
/* 80348E2C 00345A0C  54 60 00 3A */	rlwinm r0, r3, 0, 0, 0x1d
/* 80348E30 00345A10  98 1F 00 13 */	stb r0, 0x13(r31)
lbl_80348E34:
/* 80348E34 00345A14  38 00 00 00 */	li r0, 0
/* 80348E38 00345A18  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348E3C 00345A1C  38 BF 00 14 */	addi r5, r31, 0x14
/* 80348E40 00345A20  38 DF 00 0C */	addi r6, r31, 0xc
/* 80348E44 00345A24  38 65 00 01 */	addi r3, r5, 1
/* 80348E48 00345A28  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348E4C 00345A2C  7C 66 18 50 */	subf r3, r6, r3
/* 80348E50 00345A30  7C 06 28 40 */	cmplw r6, r5
/* 80348E54 00345A34  54 63 F8 7E */	srwi r3, r3, 1
/* 80348E58 00345A38  40 80 01 70 */	bge lbl_80348FC8
/* 80348E5C 00345A3C  54 60 E8 FF */	rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 80348E60 00345A40  7C 09 03 A6 */	mtctr r0
/* 80348E64 00345A44  41 82 01 34 */	beq lbl_80348F98
lbl_80348E68:
/* 80348E68 00345A48  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348E6C 00345A4C  A0 06 00 00 */	lhz r0, 0(r6)
/* 80348E70 00345A50  7C 05 02 14 */	add r0, r5, r0
/* 80348E74 00345A54  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348E78 00345A58  A0 06 00 00 */	lhz r0, 0(r6)
/* 80348E7C 00345A5C  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348E80 00345A60  7C 00 00 F8 */	nor r0, r0, r0
/* 80348E84 00345A64  7C 05 02 14 */	add r0, r5, r0
/* 80348E88 00345A68  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348E8C 00345A6C  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348E90 00345A70  A0 06 00 02 */	lhz r0, 2(r6)
/* 80348E94 00345A74  7C 05 02 14 */	add r0, r5, r0
/* 80348E98 00345A78  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348E9C 00345A7C  A0 06 00 02 */	lhz r0, 2(r6)
/* 80348EA0 00345A80  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348EA4 00345A84  7C 00 00 F8 */	nor r0, r0, r0
/* 80348EA8 00345A88  7C 05 02 14 */	add r0, r5, r0
/* 80348EAC 00345A8C  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348EB0 00345A90  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348EB4 00345A94  A0 06 00 04 */	lhz r0, 4(r6)
/* 80348EB8 00345A98  7C 05 02 14 */	add r0, r5, r0
/* 80348EBC 00345A9C  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348EC0 00345AA0  A0 06 00 04 */	lhz r0, 4(r6)
/* 80348EC4 00345AA4  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348EC8 00345AA8  7C 00 00 F8 */	nor r0, r0, r0
/* 80348ECC 00345AAC  7C 05 02 14 */	add r0, r5, r0
/* 80348ED0 00345AB0  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348ED4 00345AB4  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348ED8 00345AB8  A0 06 00 06 */	lhz r0, 6(r6)
/* 80348EDC 00345ABC  7C 05 02 14 */	add r0, r5, r0
/* 80348EE0 00345AC0  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348EE4 00345AC4  A0 06 00 06 */	lhz r0, 6(r6)
/* 80348EE8 00345AC8  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348EEC 00345ACC  7C 00 00 F8 */	nor r0, r0, r0
/* 80348EF0 00345AD0  7C 05 02 14 */	add r0, r5, r0
/* 80348EF4 00345AD4  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348EF8 00345AD8  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348EFC 00345ADC  A0 06 00 08 */	lhz r0, 8(r6)
/* 80348F00 00345AE0  7C 05 02 14 */	add r0, r5, r0
/* 80348F04 00345AE4  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348F08 00345AE8  A0 06 00 08 */	lhz r0, 8(r6)
/* 80348F0C 00345AEC  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348F10 00345AF0  7C 00 00 F8 */	nor r0, r0, r0
/* 80348F14 00345AF4  7C 05 02 14 */	add r0, r5, r0
/* 80348F18 00345AF8  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348F1C 00345AFC  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348F20 00345B00  A0 06 00 0A */	lhz r0, 0xa(r6)
/* 80348F24 00345B04  7C 05 02 14 */	add r0, r5, r0
/* 80348F28 00345B08  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348F2C 00345B0C  A0 06 00 0A */	lhz r0, 0xa(r6)
/* 80348F30 00345B10  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348F34 00345B14  7C 00 00 F8 */	nor r0, r0, r0
/* 80348F38 00345B18  7C 05 02 14 */	add r0, r5, r0
/* 80348F3C 00345B1C  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348F40 00345B20  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348F44 00345B24  A0 06 00 0C */	lhz r0, 0xc(r6)
/* 80348F48 00345B28  7C 05 02 14 */	add r0, r5, r0
/* 80348F4C 00345B2C  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348F50 00345B30  A0 06 00 0C */	lhz r0, 0xc(r6)
/* 80348F54 00345B34  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348F58 00345B38  7C 00 00 F8 */	nor r0, r0, r0
/* 80348F5C 00345B3C  7C 05 02 14 */	add r0, r5, r0
/* 80348F60 00345B40  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348F64 00345B44  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348F68 00345B48  A0 06 00 0E */	lhz r0, 0xe(r6)
/* 80348F6C 00345B4C  7C 05 02 14 */	add r0, r5, r0
/* 80348F70 00345B50  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348F74 00345B54  A0 06 00 0E */	lhz r0, 0xe(r6)
/* 80348F78 00345B58  38 C6 00 10 */	addi r6, r6, 0x10
/* 80348F7C 00345B5C  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348F80 00345B60  7C 00 00 F8 */	nor r0, r0, r0
/* 80348F84 00345B64  7C 05 02 14 */	add r0, r5, r0
/* 80348F88 00345B68  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348F8C 00345B6C  42 00 FE DC */	bdnz lbl_80348E68
/* 80348F90 00345B70  70 63 00 07 */	andi. r3, r3, 7
/* 80348F94 00345B74  41 82 00 34 */	beq lbl_80348FC8
lbl_80348F98:
/* 80348F98 00345B78  7C 69 03 A6 */	mtctr r3
lbl_80348F9C:
/* 80348F9C 00345B7C  A0 BF 00 00 */	lhz r5, 0(r31)
/* 80348FA0 00345B80  A0 06 00 00 */	lhz r0, 0(r6)
/* 80348FA4 00345B84  7C 05 02 14 */	add r0, r5, r0
/* 80348FA8 00345B88  B0 1F 00 00 */	sth r0, 0(r31)
/* 80348FAC 00345B8C  A0 06 00 00 */	lhz r0, 0(r6)
/* 80348FB0 00345B90  38 C6 00 02 */	addi r6, r6, 2
/* 80348FB4 00345B94  A0 BF 00 02 */	lhz r5, 2(r31)
/* 80348FB8 00345B98  7C 00 00 F8 */	nor r0, r0, r0
/* 80348FBC 00345B9C  7C 05 02 14 */	add r0, r5, r0
/* 80348FC0 00345BA0  B0 1F 00 02 */	sth r0, 2(r31)
/* 80348FC4 00345BA4  42 00 FF D8 */	bdnz lbl_80348F9C
lbl_80348FC8:
/* 80348FC8 00345BA8  3B DF 00 40 */	addi r30, r31, 0x40
/* 80348FCC 00345BAC  80 1F 00 40 */	lwz r0, 0x40(r31)
/* 80348FD0 00345BB0  7C 04 00 40 */	cmplw r4, r0
/* 80348FD4 00345BB4  40 80 00 08 */	bge lbl_80348FDC
/* 80348FD8 00345BB8  90 9E 00 00 */	stw r4, 0(r30)
lbl_80348FDC:
/* 80348FDC 00345BBC  83 BE 00 00 */	lwz r29, 0(r30)
/* 80348FE0 00345BC0  3C 60 80 35 */	lis r3, WriteSramCallback@ha
/* 80348FE4 00345BC4  38 A3 8A 90 */	addi r5, r3, WriteSramCallback@l
/* 80348FE8 00345BC8  23 7D 00 40 */	subfic r27, r29, 0x40
/* 80348FEC 00345BCC  7F 9F EA 14 */	add r28, r31, r29
/* 80348FF0 00345BD0  38 60 00 00 */	li r3, 0
/* 80348FF4 00345BD4  38 80 00 01 */	li r4, 1
/* 80348FF8 00345BD8  4B FF DD 89 */	bl EXILock
/* 80348FFC 00345BDC  2C 03 00 00 */	cmpwi r3, 0
/* 80349000 00345BE0  40 82 00 0C */	bne lbl_8034900C
/* 80349004 00345BE4  38 00 00 00 */	li r0, 0
/* 80349008 00345BE8  48 00 00 B4 */	b lbl_803490BC
lbl_8034900C:
/* 8034900C 00345BEC  38 60 00 00 */	li r3, 0
/* 80349010 00345BF0  38 80 00 01 */	li r4, 1
/* 80349014 00345BF4  38 A0 00 03 */	li r5, 3
/* 80349018 00345BF8  4B FF D6 71 */	bl EXISelect
/* 8034901C 00345BFC  2C 03 00 00 */	cmpwi r3, 0
/* 80349020 00345C00  40 82 00 14 */	bne lbl_80349034
/* 80349024 00345C04  38 60 00 00 */	li r3, 0
/* 80349028 00345C08  4B FF DE 4D */	bl EXIUnlock
/* 8034902C 00345C0C  38 00 00 00 */	li r0, 0
/* 80349030 00345C10  48 00 00 8C */	b lbl_803490BC
lbl_80349034:
/* 80349034 00345C14  57 A3 30 32 */	slwi r3, r29, 6
/* 80349038 00345C18  38 03 01 00 */	addi r0, r3, 0x100
/* 8034903C 00345C1C  64 00 A0 00 */	oris r0, r0, 0xa000
/* 80349040 00345C20  90 01 00 10 */	stw r0, 0x10(r1)
/* 80349044 00345C24  38 81 00 10 */	addi r4, r1, 0x10
/* 80349048 00345C28  38 60 00 00 */	li r3, 0
/* 8034904C 00345C2C  38 A0 00 04 */	li r5, 4
/* 80349050 00345C30  38 C0 00 01 */	li r6, 1
/* 80349054 00345C34  38 E0 00 00 */	li r7, 0
/* 80349058 00345C38  4B FF CB 0D */	bl EXIImm
/* 8034905C 00345C3C  7C 60 00 34 */	cntlzw r0, r3
/* 80349060 00345C40  54 1D D9 7E */	srwi r29, r0, 5
/* 80349064 00345C44  38 60 00 00 */	li r3, 0
/* 80349068 00345C48  4B FF CE E5 */	bl EXISync
/* 8034906C 00345C4C  7C 60 00 34 */	cntlzw r0, r3
/* 80349070 00345C50  54 00 D9 7E */	srwi r0, r0, 5
/* 80349074 00345C54  38 9C 00 00 */	addi r4, r28, 0
/* 80349078 00345C58  38 BB 00 00 */	addi r5, r27, 0
/* 8034907C 00345C5C  7F BD 03 78 */	or r29, r29, r0
/* 80349080 00345C60  38 60 00 00 */	li r3, 0
/* 80349084 00345C64  38 C0 00 01 */	li r6, 1
/* 80349088 00345C68  4B FF CD 39 */	bl EXIImmEx
/* 8034908C 00345C6C  7C 60 00 34 */	cntlzw r0, r3
/* 80349090 00345C70  54 00 D9 7E */	srwi r0, r0, 5
/* 80349094 00345C74  7F BD 03 78 */	or r29, r29, r0
/* 80349098 00345C78  38 60 00 00 */	li r3, 0
/* 8034909C 00345C7C  4B FF D7 19 */	bl EXIDeselect
/* 803490A0 00345C80  7C 60 00 34 */	cntlzw r0, r3
/* 803490A4 00345C84  54 00 D9 7E */	srwi r0, r0, 5
/* 803490A8 00345C88  7F BD 03 78 */	or r29, r29, r0
/* 803490AC 00345C8C  38 60 00 00 */	li r3, 0
/* 803490B0 00345C90  4B FF DD C5 */	bl EXIUnlock
/* 803490B4 00345C94  7F A0 00 34 */	cntlzw r0, r29
/* 803490B8 00345C98  54 00 D9 7E */	srwi r0, r0, 5
lbl_803490BC:
/* 803490BC 00345C9C  90 1F 00 4C */	stw r0, 0x4c(r31)
/* 803490C0 00345CA0  80 1F 00 4C */	lwz r0, 0x4c(r31)
/* 803490C4 00345CA4  2C 00 00 00 */	cmpwi r0, 0
/* 803490C8 00345CA8  41 82 00 0C */	beq lbl_803490D4
/* 803490CC 00345CAC  38 00 00 40 */	li r0, 0x40
/* 803490D0 00345CB0  90 1E 00 00 */	stw r0, 0(r30)
lbl_803490D4:
/* 803490D4 00345CB4  38 00 00 00 */	li r0, 0
/* 803490D8 00345CB8  90 1F 00 48 */	stw r0, 0x48(r31)
/* 803490DC 00345CBC  80 7F 00 44 */	lwz r3, 0x44(r31)
/* 803490E0 00345CC0  4B FF E2 AD */	bl OSRestoreInterrupts
/* 803490E4 00345CC4  80 7F 00 4C */	lwz r3, 0x4c(r31)
/* 803490E8 00345CC8  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 803490EC 00345CCC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803490F0 00345CD0  38 21 00 30 */	addi r1, r1, 0x30
/* 803490F4 00345CD4  7C 08 03 A6 */	mtlr r0
/* 803490F8 00345CD8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSUnlockSram()
{ // clang-format off
    nofralloc
/* 803490FC 00345CDC  7C 08 02 A6 */	mflr r0
/* 80349100 00345CE0  38 80 00 00 */	li r4, 0
/* 80349104 00345CE4  90 01 00 04 */	stw r0, 4(r1)
/* 80349108 00345CE8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8034910C 00345CEC  4B FF FC E9 */	bl UnlockSram
/* 80349110 00345CF0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80349114 00345CF4  38 21 00 08 */	addi r1, r1, 8
/* 80349118 00345CF8  7C 08 03 A6 */	mtlr r0
/* 8034911C 00345CFC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSUnlockSramEx()
{ // clang-format off
    nofralloc
/* 80349120 00345D00  7C 08 02 A6 */	mflr r0
/* 80349124 00345D04  38 80 00 14 */	li r4, 0x14
/* 80349128 00345D08  90 01 00 04 */	stw r0, 4(r1)
/* 8034912C 00345D0C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80349130 00345D10  4B FF FC C5 */	bl UnlockSram
/* 80349134 00345D14  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80349138 00345D18  38 21 00 08 */	addi r1, r1, 8
/* 8034913C 00345D1C  7C 08 03 A6 */	mtlr r0
/* 80349140 00345D20  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t __OSSyncSram()
{ // clang-format off
    nofralloc
/* 80349144 00345D24  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 80349148 00345D28  38 63 7D 60 */	addi r3, r3, lbl_804A7D60@l
/* 8034914C 00345D2C  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 80349150 00345D30  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t OSGetSoundMode()
{ // clang-format off
    nofralloc
/* 80349154 00345D34  7C 08 02 A6 */	mflr r0
/* 80349158 00345D38  3C 60 80 4A */	lis r3, lbl_804A7D60@ha
/* 8034915C 00345D3C  90 01 00 04 */	stw r0, 4(r1)
/* 80349160 00345D40  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80349164 00345D44  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80349168 00345D48  3B E3 7D 60 */	addi r31, r3, lbl_804A7D60@l
/* 8034916C 00345D4C  4B FF E1 F9 */	bl OSDisableInterrupts
/* 80349170 00345D50  80 1F 00 48 */	lwz r0, 0x48(r31)
/* 80349174 00345D54  38 9F 00 48 */	addi r4, r31, 0x48
/* 80349178 00345D58  2C 00 00 00 */	cmpwi r0, 0
/* 8034917C 00345D5C  41 82 00 10 */	beq lbl_8034918C
/* 80349180 00345D60  4B FF E2 0D */	bl OSRestoreInterrupts
/* 80349184 00345D64  3B E0 00 00 */	li r31, 0
/* 80349188 00345D68  48 00 00 10 */	b lbl_80349198
lbl_8034918C:
/* 8034918C 00345D6C  90 7F 00 44 */	stw r3, 0x44(r31)
/* 80349190 00345D70  38 00 00 01 */	li r0, 1
/* 80349194 00345D74  90 04 00 00 */	stw r0, 0(r4)
lbl_80349198:
/* 80349198 00345D78  88 1F 00 13 */	lbz r0, 0x13(r31)
/* 8034919C 00345D7C  54 00 07 7B */	rlwinm. r0, r0, 0, 0x1d, 0x1d
/* 803491A0 00345D80  41 82 00 0C */	beq lbl_803491AC
/* 803491A4 00345D84  3B E0 00 01 */	li r31, 1
/* 803491A8 00345D88  48 00 00 08 */	b lbl_803491B0
lbl_803491AC:
/* 803491AC 00345D8C  3B E0 00 00 */	li r31, 0
lbl_803491B0:
/* 803491B0 00345D90  38 60 00 00 */	li r3, 0
/* 803491B4 00345D94  38 80 00 00 */	li r4, 0
/* 803491B8 00345D98  4B FF FC 3D */	bl UnlockSram
/* 803491BC 00345D9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 803491C0 00345DA0  7F E3 FB 78 */	mr r3, r31
/* 803491C4 00345DA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 803491C8 00345DA8  38 21 00 20 */	addi r1, r1, 0x20
/* 803491CC 00345DAC  7C 08 03 A6 */	mtlr r0
/* 803491D0 00345DB0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
