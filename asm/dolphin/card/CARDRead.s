.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global __CARDSeek
__CARDSeek:
/* 80357A58 00354638  7C 08 02 A6 */	mflr r0
/* 80357A5C 0035463C  90 01 00 04 */	stw r0, 4(r1)
/* 80357A60 00354640  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80357A64 00354644  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80357A68 00354648  3B E6 00 00 */	addi r31, r6, 0
/* 80357A6C 0035464C  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80357A70 00354650  3B C5 00 00 */	addi r30, r5, 0
/* 80357A74 00354654  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80357A78 00354658  3B A4 00 00 */	addi r29, r4, 0
/* 80357A7C 0035465C  38 81 00 18 */	addi r4, r1, 0x18
/* 80357A80 00354660  93 81 00 20 */	stw r28, 0x20(r1)
/* 80357A84 00354664  7C 7C 1B 78 */	mr r28, r3
/* 80357A88 00354668  80 63 00 00 */	lwz r3, 0(r3)
/* 80357A8C 0035466C  4B FF B7 2D */	bl __CARDGetControlBlock
/* 80357A90 00354670  2C 03 00 00 */	cmpwi r3, 0
/* 80357A94 00354674  40 80 00 08 */	bge lbl_80357A9C
/* 80357A98 00354678  48 00 01 58 */	b lbl_80357BF0
lbl_80357A9C:
/* 80357A9C 0035467C  A0 1C 00 10 */	lhz r0, 0x10(r28)
/* 80357AA0 00354680  28 00 00 05 */	cmplwi r0, 5
/* 80357AA4 00354684  41 80 00 28 */	blt lbl_80357ACC
/* 80357AA8 00354688  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357AAC 0035468C  A0 A3 00 10 */	lhz r5, 0x10(r3)
/* 80357AB0 00354690  7C 00 28 40 */	cmplw r0, r5
/* 80357AB4 00354694  40 80 00 18 */	bge lbl_80357ACC
/* 80357AB8 00354698  80 83 00 0C */	lwz r4, 0xc(r3)
/* 80357ABC 0035469C  80 1C 00 08 */	lwz r0, 8(r28)
/* 80357AC0 003546A0  7C 85 21 D6 */	mullw r4, r5, r4
/* 80357AC4 003546A4  7C 04 00 00 */	cmpw r4, r0
/* 80357AC8 003546A8  41 81 00 14 */	bgt lbl_80357ADC
lbl_80357ACC:
/* 80357ACC 003546AC  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357AD0 003546B0  38 80 FF 80 */	li r4, -128
/* 80357AD4 003546B4  4B FF B7 9D */	bl __CARDPutControlBlock
/* 80357AD8 003546B8  48 00 01 18 */	b lbl_80357BF0
lbl_80357ADC:
/* 80357ADC 003546BC  4B FF D2 E1 */	bl __CARDGetDirBlock
/* 80357AE0 003546C0  80 1C 00 04 */	lwz r0, 4(r28)
/* 80357AE4 003546C4  80 A1 00 18 */	lwz r5, 0x18(r1)
/* 80357AE8 003546C8  54 00 30 32 */	slwi r0, r0, 6
/* 80357AEC 003546CC  7C 83 02 14 */	add r4, r3, r0
/* 80357AF0 003546D0  80 65 00 0C */	lwz r3, 0xc(r5)
/* 80357AF4 003546D4  A0 04 00 38 */	lhz r0, 0x38(r4)
/* 80357AF8 003546D8  7C 60 19 D6 */	mullw r3, r0, r3
/* 80357AFC 003546DC  7C 03 F0 00 */	cmpw r3, r30
/* 80357B00 003546E0  40 81 00 10 */	ble lbl_80357B10
/* 80357B04 003546E4  7C 1E EA 14 */	add r0, r30, r29
/* 80357B08 003546E8  7C 03 00 00 */	cmpw r3, r0
/* 80357B0C 003546EC  40 80 00 14 */	bge lbl_80357B20
lbl_80357B10:
/* 80357B10 003546F0  38 65 00 00 */	addi r3, r5, 0
/* 80357B14 003546F4  38 80 FF F5 */	li r4, -11
/* 80357B18 003546F8  4B FF B7 59 */	bl __CARDPutControlBlock
/* 80357B1C 003546FC  48 00 00 D4 */	b lbl_80357BF0
lbl_80357B20:
/* 80357B20 00354700  93 85 00 C0 */	stw r28, 0xc0(r5)
/* 80357B24 00354704  93 BC 00 0C */	stw r29, 0xc(r28)
/* 80357B28 00354708  80 1C 00 08 */	lwz r0, 8(r28)
/* 80357B2C 0035470C  7C 1E 00 00 */	cmpw r30, r0
/* 80357B30 00354710  40 80 00 40 */	bge lbl_80357B70
/* 80357B34 00354714  38 00 00 00 */	li r0, 0
/* 80357B38 00354718  90 1C 00 08 */	stw r0, 8(r28)
/* 80357B3C 0035471C  A0 04 00 36 */	lhz r0, 0x36(r4)
/* 80357B40 00354720  B0 1C 00 10 */	sth r0, 0x10(r28)
/* 80357B44 00354724  A0 9C 00 10 */	lhz r4, 0x10(r28)
/* 80357B48 00354728  28 04 00 05 */	cmplwi r4, 5
/* 80357B4C 0035472C  41 80 00 14 */	blt lbl_80357B60
/* 80357B50 00354730  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357B54 00354734  A0 03 00 10 */	lhz r0, 0x10(r3)
/* 80357B58 00354738  7C 04 00 40 */	cmplw r4, r0
/* 80357B5C 0035473C  41 80 00 14 */	blt lbl_80357B70
lbl_80357B60:
/* 80357B60 00354740  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357B64 00354744  38 80 FF FA */	li r4, -6
/* 80357B68 00354748  4B FF B7 09 */	bl __CARDPutControlBlock
/* 80357B6C 0035474C  48 00 00 84 */	b lbl_80357BF0
lbl_80357B70:
/* 80357B70 00354750  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357B74 00354754  4B FF CE 45 */	bl __CARDGetFatBlock
/* 80357B78 00354758  48 00 00 4C */	b lbl_80357BC4
lbl_80357B7C:
/* 80357B7C 0035475C  80 1C 00 08 */	lwz r0, 8(r28)
/* 80357B80 00354760  7C 00 22 14 */	add r0, r0, r4
/* 80357B84 00354764  90 1C 00 08 */	stw r0, 8(r28)
/* 80357B88 00354768  A0 1C 00 10 */	lhz r0, 0x10(r28)
/* 80357B8C 0035476C  54 00 08 3C */	slwi r0, r0, 1
/* 80357B90 00354770  7C 03 02 2E */	lhzx r0, r3, r0
/* 80357B94 00354774  B0 1C 00 10 */	sth r0, 0x10(r28)
/* 80357B98 00354778  A0 BC 00 10 */	lhz r5, 0x10(r28)
/* 80357B9C 0035477C  28 05 00 05 */	cmplwi r5, 5
/* 80357BA0 00354780  41 80 00 14 */	blt lbl_80357BB4
/* 80357BA4 00354784  80 81 00 18 */	lwz r4, 0x18(r1)
/* 80357BA8 00354788  A0 04 00 10 */	lhz r0, 0x10(r4)
/* 80357BAC 0035478C  7C 05 00 40 */	cmplw r5, r0
/* 80357BB0 00354790  41 80 00 14 */	blt lbl_80357BC4
lbl_80357BB4:
/* 80357BB4 00354794  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80357BB8 00354798  38 80 FF FA */	li r4, -6
/* 80357BBC 0035479C  4B FF B6 B5 */	bl __CARDPutControlBlock
/* 80357BC0 003547A0  48 00 00 30 */	b lbl_80357BF0
lbl_80357BC4:
/* 80357BC4 003547A4  80 81 00 18 */	lwz r4, 0x18(r1)
/* 80357BC8 003547A8  80 BC 00 08 */	lwz r5, 8(r28)
/* 80357BCC 003547AC  80 84 00 0C */	lwz r4, 0xc(r4)
/* 80357BD0 003547B0  38 04 FF FF */	addi r0, r4, -1
/* 80357BD4 003547B4  7F C0 00 78 */	andc r0, r30, r0
/* 80357BD8 003547B8  7C 05 00 40 */	cmplw r5, r0
/* 80357BDC 003547BC  41 80 FF A0 */	blt lbl_80357B7C
/* 80357BE0 003547C0  93 DC 00 08 */	stw r30, 8(r28)
/* 80357BE4 003547C4  38 60 00 00 */	li r3, 0
/* 80357BE8 003547C8  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80357BEC 003547CC  90 1F 00 00 */	stw r0, 0(r31)
lbl_80357BF0:
/* 80357BF0 003547D0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80357BF4 003547D4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80357BF8 003547D8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80357BFC 003547DC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80357C00 003547E0  83 81 00 20 */	lwz r28, 0x20(r1)
/* 80357C04 003547E4  38 21 00 30 */	addi r1, r1, 0x30
/* 80357C08 003547E8  7C 08 03 A6 */	mtlr r0
/* 80357C0C 003547EC  4E 80 00 20 */	blr 

ReadCallback:
/* 80357C10 003547F0  7C 08 02 A6 */	mflr r0
/* 80357C14 003547F4  90 01 00 04 */	stw r0, 4(r1)
/* 80357C18 003547F8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80357C1C 003547FC  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 80357C20 00354800  3B A3 00 00 */	addi r29, r3, 0
/* 80357C24 00354804  3C 60 80 4B */	lis r3, __CARDBlock@ha
/* 80357C28 00354808  1C BD 01 10 */	mulli r5, r29, 0x110
/* 80357C2C 0035480C  38 03 8B 38 */	addi r0, r3, __CARDBlock@l
/* 80357C30 00354810  7C 9E 23 79 */	or. r30, r4, r4
/* 80357C34 00354814  7F E0 2A 14 */	add r31, r0, r5
/* 80357C38 00354818  41 80 00 C8 */	blt lbl_80357D00
/* 80357C3C 0035481C  83 9F 00 C0 */	lwz r28, 0xc0(r31)
/* 80357C40 00354820  80 9C 00 0C */	lwz r4, 0xc(r28)
/* 80357C44 00354824  2C 04 00 00 */	cmpwi r4, 0
/* 80357C48 00354828  40 80 00 0C */	bge lbl_80357C54
/* 80357C4C 0035482C  3B C0 FF F2 */	li r30, -14
/* 80357C50 00354830  48 00 00 B0 */	b lbl_80357D00
lbl_80357C54:
/* 80357C54 00354834  80 BF 00 0C */	lwz r5, 0xc(r31)
/* 80357C58 00354838  80 DC 00 08 */	lwz r6, 8(r28)
/* 80357C5C 0035483C  38 05 FF FF */	addi r0, r5, -1
/* 80357C60 00354840  7C 03 00 F8 */	nor r3, r0, r0
/* 80357C64 00354844  7C 06 2A 14 */	add r0, r6, r5
/* 80357C68 00354848  7C 60 00 38 */	and r0, r3, r0
/* 80357C6C 0035484C  7F 66 00 50 */	subf r27, r6, r0
/* 80357C70 00354850  7C 1B 20 50 */	subf r0, r27, r4
/* 80357C74 00354854  90 1C 00 0C */	stw r0, 0xc(r28)
/* 80357C78 00354858  80 1C 00 0C */	lwz r0, 0xc(r28)
/* 80357C7C 0035485C  2C 00 00 00 */	cmpwi r0, 0
/* 80357C80 00354860  40 81 00 80 */	ble lbl_80357D00
/* 80357C84 00354864  7F E3 FB 78 */	mr r3, r31
/* 80357C88 00354868  4B FF CD 31 */	bl __CARDGetFatBlock
/* 80357C8C 0035486C  80 1C 00 08 */	lwz r0, 8(r28)
/* 80357C90 00354870  7C 00 DA 14 */	add r0, r0, r27
/* 80357C94 00354874  90 1C 00 08 */	stw r0, 8(r28)
/* 80357C98 00354878  A0 1C 00 10 */	lhz r0, 0x10(r28)
/* 80357C9C 0035487C  54 00 08 3C */	slwi r0, r0, 1
/* 80357CA0 00354880  7C 03 02 2E */	lhzx r0, r3, r0
/* 80357CA4 00354884  B0 1C 00 10 */	sth r0, 0x10(r28)
/* 80357CA8 00354888  A0 7C 00 10 */	lhz r3, 0x10(r28)
/* 80357CAC 0035488C  28 03 00 05 */	cmplwi r3, 5
/* 80357CB0 00354890  41 80 00 10 */	blt lbl_80357CC0
/* 80357CB4 00354894  A0 1F 00 10 */	lhz r0, 0x10(r31)
/* 80357CB8 00354898  7C 03 00 40 */	cmplw r3, r0
/* 80357CBC 0035489C  41 80 00 0C */	blt lbl_80357CC8
lbl_80357CC0:
/* 80357CC0 003548A0  3B C0 FF FA */	li r30, -6
/* 80357CC4 003548A4  48 00 00 3C */	b lbl_80357D00
lbl_80357CC8:
/* 80357CC8 003548A8  80 BC 00 0C */	lwz r5, 0xc(r28)
/* 80357CCC 003548AC  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80357CD0 003548B0  7C 05 00 00 */	cmpw r5, r0
/* 80357CD4 003548B4  40 80 00 08 */	bge lbl_80357CDC
/* 80357CD8 003548B8  48 00 00 08 */	b lbl_80357CE0
lbl_80357CDC:
/* 80357CDC 003548BC  7C 05 03 78 */	mr r5, r0
lbl_80357CE0:
/* 80357CE0 003548C0  7C 80 19 D6 */	mullw r4, r0, r3
/* 80357CE4 003548C4  80 DF 00 B4 */	lwz r6, 0xb4(r31)
/* 80357CE8 003548C8  3C 60 80 35 */	lis r3, ReadCallback@ha
/* 80357CEC 003548CC  38 E3 7C 10 */	addi r7, r3, ReadCallback@l
/* 80357CF0 003548D0  38 7D 00 00 */	addi r3, r29, 0
/* 80357CF4 003548D4  4B FF CB 09 */	bl __CARDRead
/* 80357CF8 003548D8  7C 7E 1B 79 */	or. r30, r3, r3
/* 80357CFC 003548DC  40 80 00 30 */	bge lbl_80357D2C
lbl_80357D00:
/* 80357D00 003548E0  83 7F 00 D0 */	lwz r27, 0xd0(r31)
/* 80357D04 003548E4  38 00 00 00 */	li r0, 0
/* 80357D08 003548E8  38 7F 00 00 */	addi r3, r31, 0
/* 80357D0C 003548EC  90 1F 00 D0 */	stw r0, 0xd0(r31)
/* 80357D10 003548F0  7F C4 F3 78 */	mr r4, r30
/* 80357D14 003548F4  4B FF B5 5D */	bl __CARDPutControlBlock
/* 80357D18 003548F8  39 9B 00 00 */	addi r12, r27, 0
/* 80357D1C 003548FC  7D 88 03 A6 */	mtlr r12
/* 80357D20 00354900  38 7D 00 00 */	addi r3, r29, 0
/* 80357D24 00354904  38 9E 00 00 */	addi r4, r30, 0
/* 80357D28 00354908  4E 80 00 21 */	blrl 
lbl_80357D2C:
/* 80357D2C 0035490C  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80357D30 00354910  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80357D34 00354914  38 21 00 28 */	addi r1, r1, 0x28
/* 80357D38 00354918  7C 08 03 A6 */	mtlr r0
/* 80357D3C 0035491C  4E 80 00 20 */	blr 

.global CARDReadAsync
CARDReadAsync:
/* 80357D40 00354920  7C 08 02 A6 */	mflr r0
/* 80357D44 00354924  90 01 00 04 */	stw r0, 4(r1)
/* 80357D48 00354928  54 C0 05 FF */	clrlwi. r0, r6, 0x17
/* 80357D4C 0035492C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80357D50 00354930  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 80357D54 00354934  3B A3 00 00 */	addi r29, r3, 0
/* 80357D58 00354938  3B C4 00 00 */	addi r30, r4, 0
/* 80357D5C 0035493C  3B E5 00 00 */	addi r31, r5, 0
/* 80357D60 00354940  3B 67 00 00 */	addi r27, r7, 0
/* 80357D64 00354944  40 82 00 0C */	bne lbl_80357D70
/* 80357D68 00354948  57 E0 05 FF */	clrlwi. r0, r31, 0x17
/* 80357D6C 0035494C  41 82 00 0C */	beq lbl_80357D78
lbl_80357D70:
/* 80357D70 00354950  38 60 FF 80 */	li r3, -128
/* 80357D74 00354954  48 00 01 00 */	b lbl_80357E74
lbl_80357D78:
/* 80357D78 00354958  38 7D 00 00 */	addi r3, r29, 0
/* 80357D7C 0035495C  38 9F 00 00 */	addi r4, r31, 0
/* 80357D80 00354960  38 A6 00 00 */	addi r5, r6, 0
/* 80357D84 00354964  38 C1 00 1C */	addi r6, r1, 0x1c
/* 80357D88 00354968  4B FF FC D1 */	bl __CARDSeek
/* 80357D8C 0035496C  2C 03 00 00 */	cmpwi r3, 0
/* 80357D90 00354970  40 80 00 08 */	bge lbl_80357D98
/* 80357D94 00354974  48 00 00 E0 */	b lbl_80357E74
lbl_80357D98:
/* 80357D98 00354978  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357D9C 0035497C  4B FF D0 21 */	bl __CARDGetDirBlock
/* 80357DA0 00354980  80 1D 00 04 */	lwz r0, 4(r29)
/* 80357DA4 00354984  54 00 30 32 */	slwi r0, r0, 6
/* 80357DA8 00354988  7F 83 02 14 */	add r28, r3, r0
/* 80357DAC 0035498C  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357DB0 00354990  7F 84 E3 78 */	mr r4, r28
/* 80357DB4 00354994  4B FF F4 09 */	bl __CARDAccess
/* 80357DB8 00354998  38 83 00 00 */	addi r4, r3, 0
/* 80357DBC 0035499C  2C 04 FF F6 */	cmpwi r4, -10
/* 80357DC0 003549A0  40 82 00 10 */	bne lbl_80357DD0
/* 80357DC4 003549A4  7F 83 E3 78 */	mr r3, r28
/* 80357DC8 003549A8  4B FF F4 8D */	bl __CARDIsPublic
/* 80357DCC 003549AC  7C 64 1B 78 */	mr r4, r3
lbl_80357DD0:
/* 80357DD0 003549B0  2C 04 00 00 */	cmpwi r4, 0
/* 80357DD4 003549B4  40 80 00 10 */	bge lbl_80357DE4
/* 80357DD8 003549B8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357DDC 003549BC  4B FF B4 95 */	bl __CARDPutControlBlock
/* 80357DE0 003549C0  48 00 00 94 */	b lbl_80357E74
lbl_80357DE4:
/* 80357DE4 003549C4  38 7E 00 00 */	addi r3, r30, 0
/* 80357DE8 003549C8  38 9F 00 00 */	addi r4, r31, 0
/* 80357DEC 003549CC  4B FE C9 F1 */	bl DCInvalidateRange
/* 80357DF0 003549D0  28 1B 00 00 */	cmplwi r27, 0
/* 80357DF4 003549D4  41 82 00 0C */	beq lbl_80357E00
/* 80357DF8 003549D8  7F 60 DB 78 */	mr r0, r27
/* 80357DFC 003549DC  48 00 00 0C */	b lbl_80357E08
lbl_80357E00:
/* 80357E00 003549E0  3C 60 80 35 */	lis r3, __CARDDefaultApiCallback@ha
/* 80357E04 003549E4  38 03 22 70 */	addi r0, r3, __CARDDefaultApiCallback@l
lbl_80357E08:
/* 80357E08 003549E8  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357E0C 003549EC  90 03 00 D0 */	stw r0, 0xd0(r3)
/* 80357E10 003549F0  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357E14 003549F4  80 9D 00 08 */	lwz r4, 8(r29)
/* 80357E18 003549F8  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 80357E1C 003549FC  38 05 FF FF */	addi r0, r5, -1
/* 80357E20 00354A00  7C 88 00 38 */	and r8, r4, r0
/* 80357E24 00354A04  7C 68 28 50 */	subf r3, r8, r5
/* 80357E28 00354A08  7C 1F 18 00 */	cmpw r31, r3
/* 80357E2C 00354A0C  40 80 00 08 */	bge lbl_80357E34
/* 80357E30 00354A10  7F E3 FB 78 */	mr r3, r31
lbl_80357E34:
/* 80357E34 00354A14  A0 1D 00 10 */	lhz r0, 0x10(r29)
/* 80357E38 00354A18  3C 80 80 35 */	lis r4, ReadCallback@ha
/* 80357E3C 00354A1C  3B E3 00 00 */	addi r31, r3, 0
/* 80357E40 00354A20  80 7D 00 00 */	lwz r3, 0(r29)
/* 80357E44 00354A24  7C 05 01 D6 */	mullw r0, r5, r0
/* 80357E48 00354A28  38 E4 7C 10 */	addi r7, r4, ReadCallback@l
/* 80357E4C 00354A2C  38 BF 00 00 */	addi r5, r31, 0
/* 80357E50 00354A30  38 DE 00 00 */	addi r6, r30, 0
/* 80357E54 00354A34  7C 88 02 14 */	add r4, r8, r0
/* 80357E58 00354A38  4B FF C9 A5 */	bl __CARDRead
/* 80357E5C 00354A3C  7C 7D 1B 79 */	or. r29, r3, r3
/* 80357E60 00354A40  40 80 00 10 */	bge lbl_80357E70
/* 80357E64 00354A44  80 61 00 1C */	lwz r3, 0x1c(r1)
/* 80357E68 00354A48  7F A4 EB 78 */	mr r4, r29
/* 80357E6C 00354A4C  4B FF B4 05 */	bl __CARDPutControlBlock
lbl_80357E70:
/* 80357E70 00354A50  7F A3 EB 78 */	mr r3, r29
lbl_80357E74:
/* 80357E74 00354A54  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 80357E78 00354A58  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80357E7C 00354A5C  38 21 00 38 */	addi r1, r1, 0x38
/* 80357E80 00354A60  7C 08 03 A6 */	mtlr r0
/* 80357E84 00354A64  4E 80 00 20 */	blr 

.global CARDRead
CARDRead:
/* 80357E88 00354A68  7C 08 02 A6 */	mflr r0
/* 80357E8C 00354A6C  3C E0 80 35 */	lis r7, __CARDSyncCallback@ha
/* 80357E90 00354A70  90 01 00 04 */	stw r0, 4(r1)
/* 80357E94 00354A74  38 E7 22 74 */	addi r7, r7, __CARDSyncCallback@l
/* 80357E98 00354A78  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80357E9C 00354A7C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80357EA0 00354A80  3B E3 00 00 */	addi r31, r3, 0
/* 80357EA4 00354A84  4B FF FE 9D */	bl CARDReadAsync
/* 80357EA8 00354A88  2C 03 00 00 */	cmpwi r3, 0
/* 80357EAC 00354A8C  40 80 00 08 */	bge lbl_80357EB4
/* 80357EB0 00354A90  48 00 00 0C */	b lbl_80357EBC
lbl_80357EB4:
/* 80357EB4 00354A94  80 7F 00 00 */	lwz r3, 0(r31)
/* 80357EB8 00354A98  4B FF B5 6D */	bl __CARDSync
lbl_80357EBC:
/* 80357EBC 00354A9C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80357EC0 00354AA0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80357EC4 00354AA4  38 21 00 20 */	addi r1, r1, 0x20
/* 80357EC8 00354AA8  7C 08 03 A6 */	mtlr r0
/* 80357ECC 00354AAC  4E 80 00 20 */	blr 
