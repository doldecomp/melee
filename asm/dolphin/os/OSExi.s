.include "macros.inc"

.section .text  # 0x80345A70 - 0x80347308

.global EXIIntrruptHandler
EXIIntrruptHandler:
/* 803468C4 003434A4  7C 08 02 A6 */	mflr r0
/* 803468C8 003434A8  7C 65 07 34 */	extsh r5, r3
/* 803468CC 003434AC  90 01 00 04 */	stw r0, 4(r1)
/* 803468D0 003434B0  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 803468D4 003434B4  38 05 FF F7 */	addi r0, r5, -9
/* 803468D8 003434B8  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 803468DC 003434BC  94 21 FD 08 */	stwu r1, -0x2f8(r1)
/* 803468E0 003434C0  7C 63 00 96 */	mulhw r3, r3, r0
/* 803468E4 003434C4  93 E1 02 F4 */	stw r31, 0x2f4(r1)
/* 803468E8 003434C8  93 C1 02 F0 */	stw r30, 0x2f0(r1)
/* 803468EC 003434CC  54 60 0F FE */	srwi r0, r3, 0x1f
/* 803468F0 003434D0  93 A1 02 EC */	stw r29, 0x2ec(r1)
/* 803468F4 003434D4  7F E3 02 14 */	add r31, r3, r0
/* 803468F8 003434D8  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 803468FC 003434DC  38 E3 68 00 */	addi r7, r3, 0xCC006800@l
/* 80346900 003434E0  1C 1F 00 14 */	mulli r0, r31, 0x14
/* 80346904 003434E4  7C E7 02 14 */	add r7, r7, r0
/* 80346908 003434E8  80 C7 00 00 */	lwz r6, 0(r7)
/* 8034690C 003434EC  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346910 003434F0  57 E5 30 32 */	slwi r5, r31, 6
/* 80346914 003434F4  70 C6 07 F5 */	andi. r6, r6, 0x7f5
/* 80346918 003434F8  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 8034691C 003434FC  7C 60 2A 14 */	add r3, r0, r5
/* 80346920 00343500  60 C6 00 02 */	ori r6, r6, 2
/* 80346924 00343504  90 C7 00 00 */	stw r6, 0(r7)
/* 80346928 00343508  7C 9D 23 78 */	mr r29, r4
/* 8034692C 0034350C  80 03 00 00 */	lwz r0, 0(r3)
/* 80346930 00343510  28 00 00 00 */	cmplwi r0, 0
/* 80346934 00343514  7C 1E 03 78 */	mr r30, r0
/* 80346938 00343518  41 82 00 38 */	beq lbl_80346970
/* 8034693C 0034351C  38 61 00 18 */	addi r3, r1, 0x18
/* 80346940 00343520  4B FF E9 15 */	bl OSClearContext
/* 80346944 00343524  38 61 00 18 */	addi r3, r1, 0x18
/* 80346948 00343528  4B FF E7 45 */	bl OSSetCurrentContext
/* 8034694C 0034352C  39 9E 00 00 */	addi r12, r30, 0
/* 80346950 00343530  7D 88 03 A6 */	mtlr r12
/* 80346954 00343534  38 7F 00 00 */	addi r3, r31, 0
/* 80346958 00343538  38 9D 00 00 */	addi r4, r29, 0
/* 8034695C 0034353C  4E 80 00 21 */	blrl 
/* 80346960 00343540  38 61 00 18 */	addi r3, r1, 0x18
/* 80346964 00343544  4B FF E8 F1 */	bl OSClearContext
/* 80346968 00343548  7F A3 EB 78 */	mr r3, r29
/* 8034696C 0034354C  4B FF E7 21 */	bl OSSetCurrentContext
lbl_80346970:
/* 80346970 00343550  80 01 02 FC */	lwz r0, 0x2fc(r1)
/* 80346974 00343554  83 E1 02 F4 */	lwz r31, 0x2f4(r1)
/* 80346978 00343558  83 C1 02 F0 */	lwz r30, 0x2f0(r1)
/* 8034697C 0034355C  7C 08 03 A6 */	mtlr r0
/* 80346980 00343560  83 A1 02 EC */	lwz r29, 0x2ec(r1)
/* 80346984 00343564  38 21 02 F8 */	addi r1, r1, 0x2f8
/* 80346988 00343568  4E 80 00 20 */	blr 

.global TCIntrruptHandler
TCIntrruptHandler:
/* 8034698C 0034356C  7C 08 02 A6 */	mflr r0
/* 80346990 00343570  7C 66 07 34 */	extsh r6, r3
/* 80346994 00343574  90 01 00 04 */	stw r0, 4(r1)
/* 80346998 00343578  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 8034699C 0034357C  38 06 FF F6 */	addi r0, r6, -10
/* 803469A0 00343580  94 21 FD 08 */	stwu r1, -0x2f8(r1)
/* 803469A4 00343584  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 803469A8 00343588  7C 63 00 96 */	mulhw r3, r3, r0
/* 803469AC 0034358C  93 E1 02 F4 */	stw r31, 0x2f4(r1)
/* 803469B0 00343590  93 C1 02 F0 */	stw r30, 0x2f0(r1)
/* 803469B4 00343594  93 A1 02 EC */	stw r29, 0x2ec(r1)
/* 803469B8 00343598  54 60 0F FE */	srwi r0, r3, 0x1f
/* 803469BC 0034359C  7F C3 02 14 */	add r30, r3, r0
/* 803469C0 003435A0  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 803469C4 003435A4  93 81 02 E8 */	stw r28, 0x2e8(r1)
/* 803469C8 003435A8  3C 00 80 00 */	lis r0, 0x8000
/* 803469CC 003435AC  57 C5 30 32 */	slwi r5, r30, 6
/* 803469D0 003435B0  38 63 7C 80 */	addi r3, r3, lbl_804A7C80@l
/* 803469D4 003435B4  7F E3 2A 14 */	add r31, r3, r5
/* 803469D8 003435B8  3B 84 00 00 */	addi r28, r4, 0
/* 803469DC 003435BC  7C 03 34 30 */	srw r3, r0, r6
/* 803469E0 003435C0  48 00 0D 4D */	bl __OSMaskInterrupts
/* 803469E4 003435C4  1C DE 00 14 */	mulli r6, r30, 0x14
/* 803469E8 003435C8  3C 60 CC 00 */	lis r3, 0xCC006800@ha
/* 803469EC 003435CC  38 83 68 00 */	addi r4, r3, 0xCC006800@l
/* 803469F0 003435D0  7C 84 32 14 */	add r4, r4, r6
/* 803469F4 003435D4  80 04 00 00 */	lwz r0, 0(r4)
/* 803469F8 003435D8  70 00 07 F5 */	andi. r0, r0, 0x7f5
/* 803469FC 003435DC  60 00 00 08 */	ori r0, r0, 8
/* 80346A00 003435E0  90 04 00 00 */	stw r0, 0(r4)
/* 80346A04 003435E4  80 1F 00 04 */	lwz r0, 4(r31)
/* 80346A08 003435E8  28 00 00 00 */	cmplwi r0, 0
/* 80346A0C 003435EC  7C 1D 03 78 */	mr r29, r0
/* 80346A10 003435F0  41 82 01 74 */	beq lbl_80346B84
/* 80346A14 003435F4  38 A0 00 00 */	li r5, 0
/* 80346A18 003435F8  90 BF 00 04 */	stw r5, 4(r31)
/* 80346A1C 003435FC  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346A20 00343600  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 80346A24 00343604  41 82 01 2C */	beq lbl_80346B50
/* 80346A28 00343608  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346A2C 0034360C  54 00 07 BD */	rlwinm. r0, r0, 0, 0x1e, 0x1e
/* 80346A30 00343610  41 82 01 14 */	beq lbl_80346B44
/* 80346A34 00343614  80 9F 00 10 */	lwz r4, 0x10(r31)
/* 80346A38 00343618  2C 04 00 00 */	cmpwi r4, 0
/* 80346A3C 0034361C  41 82 01 08 */	beq lbl_80346B44
/* 80346A40 00343620  38 03 68 00 */	addi r0, r3, 0x6800
/* 80346A44 00343624  80 FF 00 14 */	lwz r7, 0x14(r31)
/* 80346A48 00343628  7C 60 32 14 */	add r3, r0, r6
/* 80346A4C 0034362C  80 C3 00 10 */	lwz r6, 0x10(r3)
/* 80346A50 00343630  40 81 00 F4 */	ble lbl_80346B44
/* 80346A54 00343634  2C 04 00 08 */	cmpwi r4, 8
/* 80346A58 00343638  38 64 FF F8 */	addi r3, r4, -8
/* 80346A5C 0034363C  40 81 00 BC */	ble lbl_80346B18
/* 80346A60 00343640  38 03 00 07 */	addi r0, r3, 7
/* 80346A64 00343644  54 00 E8 FE */	srwi r0, r0, 3
/* 80346A68 00343648  2C 03 00 00 */	cmpwi r3, 0
/* 80346A6C 0034364C  7C 09 03 A6 */	mtctr r0
/* 80346A70 00343650  40 81 00 A8 */	ble lbl_80346B18
lbl_80346A74:
/* 80346A74 00343654  20 05 00 03 */	subfic r0, r5, 3
/* 80346A78 00343658  54 03 18 38 */	slwi r3, r0, 3
/* 80346A7C 0034365C  38 05 00 01 */	addi r0, r5, 1
/* 80346A80 00343660  7C C8 1C 30 */	srw r8, r6, r3
/* 80346A84 00343664  20 00 00 03 */	subfic r0, r0, 3
/* 80346A88 00343668  99 07 00 00 */	stb r8, 0(r7)
/* 80346A8C 0034366C  54 03 18 38 */	slwi r3, r0, 3
/* 80346A90 00343670  38 05 00 02 */	addi r0, r5, 2
/* 80346A94 00343674  7C C3 1C 30 */	srw r3, r6, r3
/* 80346A98 00343678  20 00 00 03 */	subfic r0, r0, 3
/* 80346A9C 0034367C  98 67 00 01 */	stb r3, 1(r7)
/* 80346AA0 00343680  54 00 18 38 */	slwi r0, r0, 3
/* 80346AA4 00343684  7C C0 04 30 */	srw r0, r6, r0
/* 80346AA8 00343688  7D 05 00 D0 */	neg r8, r5
/* 80346AAC 0034368C  98 07 00 02 */	stb r0, 2(r7)
/* 80346AB0 00343690  55 09 18 38 */	slwi r9, r8, 3
/* 80346AB4 00343694  39 05 00 04 */	addi r8, r5, 4
/* 80346AB8 00343698  7C CC 4C 30 */	srw r12, r6, r9
/* 80346ABC 0034369C  21 08 00 03 */	subfic r8, r8, 3
/* 80346AC0 003436A0  99 87 00 03 */	stb r12, 3(r7)
/* 80346AC4 003436A4  55 09 18 38 */	slwi r9, r8, 3
/* 80346AC8 003436A8  39 05 00 05 */	addi r8, r5, 5
/* 80346ACC 003436AC  7C CB 4C 30 */	srw r11, r6, r9
/* 80346AD0 003436B0  21 08 00 03 */	subfic r8, r8, 3
/* 80346AD4 003436B4  99 67 00 04 */	stb r11, 4(r7)
/* 80346AD8 003436B8  55 09 18 38 */	slwi r9, r8, 3
/* 80346ADC 003436BC  7C CA 4C 30 */	srw r10, r6, r9
/* 80346AE0 003436C0  39 05 00 06 */	addi r8, r5, 6
/* 80346AE4 003436C4  99 47 00 05 */	stb r10, 5(r7)
/* 80346AE8 003436C8  21 28 00 03 */	subfic r9, r8, 3
/* 80346AEC 003436CC  39 05 00 07 */	addi r8, r5, 7
/* 80346AF0 003436D0  55 29 18 38 */	slwi r9, r9, 3
/* 80346AF4 003436D4  7C C9 4C 30 */	srw r9, r6, r9
/* 80346AF8 003436D8  21 08 00 03 */	subfic r8, r8, 3
/* 80346AFC 003436DC  99 27 00 06 */	stb r9, 6(r7)
/* 80346B00 003436E0  55 08 18 38 */	slwi r8, r8, 3
/* 80346B04 003436E4  7C C8 44 30 */	srw r8, r6, r8
/* 80346B08 003436E8  99 07 00 07 */	stb r8, 7(r7)
/* 80346B0C 003436EC  38 E7 00 08 */	addi r7, r7, 8
/* 80346B10 003436F0  38 A5 00 08 */	addi r5, r5, 8
/* 80346B14 003436F4  42 00 FF 60 */	bdnz lbl_80346A74
lbl_80346B18:
/* 80346B18 003436F8  7C 05 20 50 */	subf r0, r5, r4
/* 80346B1C 003436FC  7C 05 20 00 */	cmpw r5, r4
/* 80346B20 00343700  7C 09 03 A6 */	mtctr r0
/* 80346B24 00343704  40 80 00 20 */	bge lbl_80346B44
lbl_80346B28:
/* 80346B28 00343708  20 05 00 03 */	subfic r0, r5, 3
/* 80346B2C 0034370C  54 00 18 38 */	slwi r0, r0, 3
/* 80346B30 00343710  7C C0 04 30 */	srw r0, r6, r0
/* 80346B34 00343714  98 07 00 00 */	stb r0, 0(r7)
/* 80346B38 00343718  38 E7 00 01 */	addi r7, r7, 1
/* 80346B3C 0034371C  38 A5 00 01 */	addi r5, r5, 1
/* 80346B40 00343720  42 00 FF E8 */	bdnz lbl_80346B28
lbl_80346B44:
/* 80346B44 00343724  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346B48 00343728  54 00 00 3A */	rlwinm r0, r0, 0, 0, 0x1d
/* 80346B4C 0034372C  90 1F 00 0C */	stw r0, 0xc(r31)
lbl_80346B50:
/* 80346B50 00343730  38 61 00 20 */	addi r3, r1, 0x20
/* 80346B54 00343734  4B FF E7 01 */	bl OSClearContext
/* 80346B58 00343738  38 61 00 20 */	addi r3, r1, 0x20
/* 80346B5C 0034373C  4B FF E5 31 */	bl OSSetCurrentContext
/* 80346B60 00343740  39 9D 00 00 */	addi r12, r29, 0
/* 80346B64 00343744  7D 88 03 A6 */	mtlr r12
/* 80346B68 00343748  38 7E 00 00 */	addi r3, r30, 0
/* 80346B6C 0034374C  38 9C 00 00 */	addi r4, r28, 0
/* 80346B70 00343750  4E 80 00 21 */	blrl 
/* 80346B74 00343754  38 61 00 20 */	addi r3, r1, 0x20
/* 80346B78 00343758  4B FF E6 DD */	bl OSClearContext
/* 80346B7C 0034375C  7F 83 E3 78 */	mr r3, r28
/* 80346B80 00343760  4B FF E5 0D */	bl OSSetCurrentContext
lbl_80346B84:
/* 80346B84 00343764  80 01 02 FC */	lwz r0, 0x2fc(r1)
/* 80346B88 00343768  83 E1 02 F4 */	lwz r31, 0x2f4(r1)
/* 80346B8C 0034376C  83 C1 02 F0 */	lwz r30, 0x2f0(r1)
/* 80346B90 00343770  7C 08 03 A6 */	mtlr r0
/* 80346B94 00343774  83 A1 02 EC */	lwz r29, 0x2ec(r1)
/* 80346B98 00343778  83 81 02 E8 */	lwz r28, 0x2e8(r1)
/* 80346B9C 0034377C  38 21 02 F8 */	addi r1, r1, 0x2f8
/* 80346BA0 00343780  4E 80 00 20 */	blr 

.global EXTIntrruptHandler
EXTIntrruptHandler:
/* 80346BA4 00343784  7C 08 02 A6 */	mflr r0
/* 80346BA8 00343788  7C 65 07 34 */	extsh r5, r3
/* 80346BAC 0034378C  90 01 00 04 */	stw r0, 4(r1)
/* 80346BB0 00343790  3C 60 55 55 */	lis r3, 0x55555556@ha
/* 80346BB4 00343794  38 05 FF F5 */	addi r0, r5, -11
/* 80346BB8 00343798  38 63 55 56 */	addi r3, r3, 0x55555556@l
/* 80346BBC 0034379C  94 21 FD 10 */	stwu r1, -0x2f0(r1)
/* 80346BC0 003437A0  7C 63 00 96 */	mulhw r3, r3, r0
/* 80346BC4 003437A4  BF 61 02 DC */	stmw r27, 0x2dc(r1)
/* 80346BC8 003437A8  54 60 0F FE */	srwi r0, r3, 0x1f
/* 80346BCC 003437AC  7F C3 02 14 */	add r30, r3, r0
/* 80346BD0 003437B0  1C 1E 00 03 */	mulli r0, r30, 3
/* 80346BD4 003437B4  3C 60 00 70 */	lis r3, 0x70
/* 80346BD8 003437B8  3B 64 00 00 */	addi r27, r4, 0
/* 80346BDC 003437BC  7C 63 04 30 */	srw r3, r3, r0
/* 80346BE0 003437C0  48 00 0B 4D */	bl __OSMaskInterrupts
/* 80346BE4 003437C4  1C 1E 00 14 */	mulli r0, r30, 0x14
/* 80346BE8 003437C8  3C 80 CC 00 */	lis r4, 0xCC006800@ha
/* 80346BEC 003437CC  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346BF0 003437D0  38 84 68 00 */	addi r4, r4, 0xCC006800@l
/* 80346BF4 003437D4  3B E0 00 00 */	li r31, 0
/* 80346BF8 003437D8  7F E4 01 2E */	stwx r31, r4, r0
/* 80346BFC 003437DC  57 C4 30 32 */	slwi r4, r30, 6
/* 80346C00 003437E0  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80346C04 003437E4  7F A0 22 14 */	add r29, r0, r4
/* 80346C08 003437E8  83 9D 00 08 */	lwz r28, 8(r29)
/* 80346C0C 003437EC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80346C10 003437F0  28 1C 00 00 */	cmplwi r28, 0
/* 80346C14 003437F4  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 80346C18 003437F8  90 1D 00 0C */	stw r0, 0xc(r29)
/* 80346C1C 003437FC  41 82 00 3C */	beq lbl_80346C58
/* 80346C20 00343800  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C24 00343804  4B FF E6 31 */	bl OSClearContext
/* 80346C28 00343808  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C2C 0034380C  4B FF E4 61 */	bl OSSetCurrentContext
/* 80346C30 00343810  7F 8C E3 78 */	mr r12, r28
/* 80346C34 00343814  93 FD 00 08 */	stw r31, 8(r29)
/* 80346C38 00343818  7D 88 03 A6 */	mtlr r12
/* 80346C3C 0034381C  38 7E 00 00 */	addi r3, r30, 0
/* 80346C40 00343820  38 9B 00 00 */	addi r4, r27, 0
/* 80346C44 00343824  4E 80 00 21 */	blrl 
/* 80346C48 00343828  38 61 00 10 */	addi r3, r1, 0x10
/* 80346C4C 0034382C  4B FF E6 09 */	bl OSClearContext
/* 80346C50 00343830  7F 63 DB 78 */	mr r3, r27
/* 80346C54 00343834  4B FF E4 39 */	bl OSSetCurrentContext
lbl_80346C58:
/* 80346C58 00343838  BB 61 02 DC */	lmw r27, 0x2dc(r1)
/* 80346C5C 0034383C  80 01 02 F4 */	lwz r0, 0x2f4(r1)
/* 80346C60 00343840  38 21 02 F0 */	addi r1, r1, 0x2f0
/* 80346C64 00343844  7C 08 03 A6 */	mtlr r0
/* 80346C68 00343848  4E 80 00 20 */	blr 

.global EXIInit
EXIInit:
/* 80346C6C 0034384C  7C 08 02 A6 */	mflr r0
/* 80346C70 00343850  3C 60 00 80 */	lis r3, 0x007F8000@ha
/* 80346C74 00343854  90 01 00 04 */	stw r0, 4(r1)
/* 80346C78 00343858  38 63 80 00 */	addi r3, r3, 0x007F8000@l
/* 80346C7C 0034385C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80346C80 00343860  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80346C84 00343864  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80346C88 00343868  93 A1 00 0C */	stw r29, 0xc(r1)
/* 80346C8C 0034386C  93 81 00 08 */	stw r28, 8(r1)
/* 80346C90 00343870  48 00 0A 9D */	bl __OSMaskInterrupts
/* 80346C94 00343874  3C A0 CC 00 */	lis r5, 0xCC006800@ha
/* 80346C98 00343878  3B E0 00 00 */	li r31, 0
/* 80346C9C 0034387C  93 E5 68 00 */	stw r31, 0xCC006800@l(r5)
/* 80346CA0 00343880  38 00 20 00 */	li r0, 0x2000
/* 80346CA4 00343884  3C 60 80 34 */	lis r3, EXIIntrruptHandler@ha
/* 80346CA8 00343888  93 E5 68 14 */	stw r31, 0x6814(r5)
/* 80346CAC 0034388C  3B 83 68 C4 */	addi r28, r3, EXIIntrruptHandler@l
/* 80346CB0 00343890  38 9C 00 00 */	addi r4, r28, 0
/* 80346CB4 00343894  93 E5 68 28 */	stw r31, 0x6828(r5)
/* 80346CB8 00343898  38 60 00 09 */	li r3, 9
/* 80346CBC 0034389C  90 05 68 00 */	stw r0, 0x6800(r5)
/* 80346CC0 003438A0  48 00 06 F1 */	bl __OSSetInterruptHandler
/* 80346CC4 003438A4  3C 60 80 34 */	lis r3, TCIntrruptHandler@ha
/* 80346CC8 003438A8  3B A3 69 8C */	addi r29, r3, TCIntrruptHandler@l
/* 80346CCC 003438AC  38 9D 00 00 */	addi r4, r29, 0
/* 80346CD0 003438B0  38 60 00 0A */	li r3, 0xa
/* 80346CD4 003438B4  48 00 06 DD */	bl __OSSetInterruptHandler
/* 80346CD8 003438B8  3C 60 80 34 */	lis r3, EXTIntrruptHandler@ha
/* 80346CDC 003438BC  3B C3 6B A4 */	addi r30, r3, EXTIntrruptHandler@l
/* 80346CE0 003438C0  38 9E 00 00 */	addi r4, r30, 0
/* 80346CE4 003438C4  38 60 00 0B */	li r3, 0xb
/* 80346CE8 003438C8  48 00 06 C9 */	bl __OSSetInterruptHandler
/* 80346CEC 003438CC  38 9C 00 00 */	addi r4, r28, 0
/* 80346CF0 003438D0  38 60 00 0C */	li r3, 0xc
/* 80346CF4 003438D4  48 00 06 BD */	bl __OSSetInterruptHandler
/* 80346CF8 003438D8  38 9D 00 00 */	addi r4, r29, 0
/* 80346CFC 003438DC  38 60 00 0D */	li r3, 0xd
/* 80346D00 003438E0  48 00 06 B1 */	bl __OSSetInterruptHandler
/* 80346D04 003438E4  38 9E 00 00 */	addi r4, r30, 0
/* 80346D08 003438E8  38 60 00 0E */	li r3, 0xe
/* 80346D0C 003438EC  48 00 06 A5 */	bl __OSSetInterruptHandler
/* 80346D10 003438F0  38 9C 00 00 */	addi r4, r28, 0
/* 80346D14 003438F4  38 60 00 0F */	li r3, 0xf
/* 80346D18 003438F8  48 00 06 99 */	bl __OSSetInterruptHandler
/* 80346D1C 003438FC  38 9D 00 00 */	addi r4, r29, 0
/* 80346D20 00343900  38 60 00 10 */	li r3, 0x10
/* 80346D24 00343904  48 00 06 8D */	bl __OSSetInterruptHandler
/* 80346D28 00343908  4B FF C1 6D */	bl OSGetConsoleType
/* 80346D2C 0034390C  54 60 00 C7 */	rlwinm. r0, r3, 0, 3, 3
/* 80346D30 00343910  41 82 00 30 */	beq lbl_80346D60
/* 80346D34 00343914  3C A0 80 00 */	lis r5, 0x800030C4@ha
/* 80346D38 00343918  93 E5 30 C4 */	stw r31, 0x800030C4@l(r5)
/* 80346D3C 0034391C  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346D40 00343920  38 83 7C 80 */	addi r4, r3, lbl_804A7C80@l
/* 80346D44 00343924  93 E5 30 C0 */	stw r31, 0x30c0(r5)
/* 80346D48 00343928  38 60 00 00 */	li r3, 0
/* 80346D4C 0034392C  93 E4 00 60 */	stw r31, 0x60(r4)
/* 80346D50 00343930  93 E4 00 20 */	stw r31, 0x20(r4)
/* 80346D54 00343934  4B FF F4 C5 */	bl __EXIProbe
/* 80346D58 00343938  38 60 00 01 */	li r3, 1
/* 80346D5C 0034393C  4B FF F4 BD */	bl __EXIProbe
lbl_80346D60:
/* 80346D60 00343940  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80346D64 00343944  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80346D68 00343948  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80346D6C 0034394C  7C 08 03 A6 */	mtlr r0
/* 80346D70 00343950  83 A1 00 0C */	lwz r29, 0xc(r1)
/* 80346D74 00343954  83 81 00 08 */	lwz r28, 8(r1)
/* 80346D78 00343958  38 21 00 18 */	addi r1, r1, 0x18
/* 80346D7C 0034395C  4E 80 00 20 */	blr 

.global EXILock
EXILock:
/* 80346D80 00343960  7C 08 02 A6 */	mflr r0
/* 80346D84 00343964  90 01 00 04 */	stw r0, 4(r1)
/* 80346D88 00343968  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80346D8C 0034396C  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 80346D90 00343970  3B 63 00 00 */	addi r27, r3, 0
/* 80346D94 00343974  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346D98 00343978  57 66 30 32 */	slwi r6, r27, 6
/* 80346D9C 0034397C  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80346DA0 00343980  7F E0 32 14 */	add r31, r0, r6
/* 80346DA4 00343984  3B 84 00 00 */	addi r28, r4, 0
/* 80346DA8 00343988  3B A5 00 00 */	addi r29, r5, 0
/* 80346DAC 0034398C  48 00 05 B9 */	bl OSDisableInterrupts
/* 80346DB0 00343990  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346DB4 00343994  3B C3 00 00 */	addi r30, r3, 0
/* 80346DB8 00343998  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80346DBC 0034399C  41 82 00 7C */	beq lbl_80346E38
/* 80346DC0 003439A0  28 1D 00 00 */	cmplwi r29, 0
/* 80346DC4 003439A4  41 82 00 64 */	beq lbl_80346E28
/* 80346DC8 003439A8  80 9F 00 24 */	lwz r4, 0x24(r31)
/* 80346DCC 003439AC  38 7F 00 00 */	addi r3, r31, 0
/* 80346DD0 003439B0  2C 04 00 00 */	cmpwi r4, 0
/* 80346DD4 003439B4  7C 89 03 A6 */	mtctr r4
/* 80346DD8 003439B8  40 81 00 28 */	ble lbl_80346E00
lbl_80346DDC:
/* 80346DDC 003439BC  80 03 00 28 */	lwz r0, 0x28(r3)
/* 80346DE0 003439C0  7C 00 E0 40 */	cmplw r0, r28
/* 80346DE4 003439C4  40 82 00 14 */	bne lbl_80346DF8
/* 80346DE8 003439C8  7F C3 F3 78 */	mr r3, r30
/* 80346DEC 003439CC  48 00 05 A1 */	bl OSRestoreInterrupts
/* 80346DF0 003439D0  38 60 00 00 */	li r3, 0
/* 80346DF4 003439D4  48 00 00 6C */	b lbl_80346E60
lbl_80346DF8:
/* 80346DF8 003439D8  38 63 00 08 */	addi r3, r3, 8
/* 80346DFC 003439DC  42 00 FF E0 */	bdnz lbl_80346DDC
lbl_80346E00:
/* 80346E00 003439E0  54 80 18 38 */	slwi r0, r4, 3
/* 80346E04 003439E4  7C 7F 02 14 */	add r3, r31, r0
/* 80346E08 003439E8  93 A3 00 2C */	stw r29, 0x2c(r3)
/* 80346E0C 003439EC  80 1F 00 24 */	lwz r0, 0x24(r31)
/* 80346E10 003439F0  54 00 18 38 */	slwi r0, r0, 3
/* 80346E14 003439F4  7C 7F 02 14 */	add r3, r31, r0
/* 80346E18 003439F8  93 83 00 28 */	stw r28, 0x28(r3)
/* 80346E1C 003439FC  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 80346E20 00343A00  38 03 00 01 */	addi r0, r3, 1
/* 80346E24 00343A04  90 1F 00 24 */	stw r0, 0x24(r31)
lbl_80346E28:
/* 80346E28 00343A08  7F C3 F3 78 */	mr r3, r30
/* 80346E2C 00343A0C  48 00 05 61 */	bl OSRestoreInterrupts
/* 80346E30 00343A10  38 60 00 00 */	li r3, 0
/* 80346E34 00343A14  48 00 00 2C */	b lbl_80346E60
lbl_80346E38:
/* 80346E38 00343A18  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346E3C 00343A1C  38 7B 00 00 */	addi r3, r27, 0
/* 80346E40 00343A20  38 9F 00 00 */	addi r4, r31, 0
/* 80346E44 00343A24  60 00 00 10 */	ori r0, r0, 0x10
/* 80346E48 00343A28  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80346E4C 00343A2C  93 9F 00 18 */	stw r28, 0x18(r31)
/* 80346E50 00343A30  4B FF EC 21 */	bl SetExiInterruptMask
/* 80346E54 00343A34  7F C3 F3 78 */	mr r3, r30
/* 80346E58 00343A38  48 00 05 35 */	bl OSRestoreInterrupts
/* 80346E5C 00343A3C  38 60 00 01 */	li r3, 1
lbl_80346E60:
/* 80346E60 00343A40  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 80346E64 00343A44  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80346E68 00343A48  38 21 00 30 */	addi r1, r1, 0x30
/* 80346E6C 00343A4C  7C 08 03 A6 */	mtlr r0
/* 80346E70 00343A50  4E 80 00 20 */	blr 

.global EXIUnlock
EXIUnlock:
/* 80346E74 00343A54  7C 08 02 A6 */	mflr r0
/* 80346E78 00343A58  90 01 00 04 */	stw r0, 4(r1)
/* 80346E7C 00343A5C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80346E80 00343A60  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80346E84 00343A64  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80346E88 00343A68  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80346E8C 00343A6C  93 81 00 10 */	stw r28, 0x10(r1)
/* 80346E90 00343A70  3B 83 00 00 */	addi r28, r3, 0
/* 80346E94 00343A74  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346E98 00343A78  57 84 30 32 */	slwi r4, r28, 6
/* 80346E9C 00343A7C  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80346EA0 00343A80  7F E0 22 14 */	add r31, r0, r4
/* 80346EA4 00343A84  48 00 04 C1 */	bl OSDisableInterrupts
/* 80346EA8 00343A88  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346EAC 00343A8C  3B C3 00 00 */	addi r30, r3, 0
/* 80346EB0 00343A90  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80346EB4 00343A94  40 82 00 14 */	bne lbl_80346EC8
/* 80346EB8 00343A98  7F C3 F3 78 */	mr r3, r30
/* 80346EBC 00343A9C  48 00 04 D1 */	bl OSRestoreInterrupts
/* 80346EC0 00343AA0  38 60 00 00 */	li r3, 0
/* 80346EC4 00343AA4  48 00 00 6C */	b lbl_80346F30
lbl_80346EC8:
/* 80346EC8 00343AA8  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80346ECC 00343AAC  38 7C 00 00 */	addi r3, r28, 0
/* 80346ED0 00343AB0  38 9F 00 00 */	addi r4, r31, 0
/* 80346ED4 00343AB4  54 00 07 34 */	rlwinm r0, r0, 0, 0x1c, 0x1a
/* 80346ED8 00343AB8  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80346EDC 00343ABC  4B FF EB 95 */	bl SetExiInterruptMask
/* 80346EE0 00343AC0  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 80346EE4 00343AC4  2C 03 00 00 */	cmpwi r3, 0
/* 80346EE8 00343AC8  40 81 00 3C */	ble lbl_80346F24
/* 80346EEC 00343ACC  34 03 FF FF */	addic. r0, r3, -1
/* 80346EF0 00343AD0  83 BF 00 2C */	lwz r29, 0x2c(r31)
/* 80346EF4 00343AD4  90 1F 00 24 */	stw r0, 0x24(r31)
/* 80346EF8 00343AD8  40 81 00 18 */	ble lbl_80346F10
/* 80346EFC 00343ADC  80 1F 00 24 */	lwz r0, 0x24(r31)
/* 80346F00 00343AE0  38 7F 00 28 */	addi r3, r31, 0x28
/* 80346F04 00343AE4  38 9F 00 30 */	addi r4, r31, 0x30
/* 80346F08 00343AE8  54 05 18 38 */	slwi r5, r0, 3
/* 80346F0C 00343AEC  4B FD CA 2D */	bl memmove
lbl_80346F10:
/* 80346F10 00343AF0  39 9D 00 00 */	addi r12, r29, 0
/* 80346F14 00343AF4  7D 88 03 A6 */	mtlr r12
/* 80346F18 00343AF8  38 7C 00 00 */	addi r3, r28, 0
/* 80346F1C 00343AFC  38 80 00 00 */	li r4, 0
/* 80346F20 00343B00  4E 80 00 21 */	blrl 
lbl_80346F24:
/* 80346F24 00343B04  7F C3 F3 78 */	mr r3, r30
/* 80346F28 00343B08  48 00 04 65 */	bl OSRestoreInterrupts
/* 80346F2C 00343B0C  38 60 00 01 */	li r3, 1
lbl_80346F30:
/* 80346F30 00343B10  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80346F34 00343B14  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80346F38 00343B18  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80346F3C 00343B1C  7C 08 03 A6 */	mtlr r0
/* 80346F40 00343B20  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80346F44 00343B24  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80346F48 00343B28  38 21 00 20 */	addi r1, r1, 0x20
/* 80346F4C 00343B2C  4E 80 00 20 */	blr 

.global EXIGetState
EXIGetState:
/* 80346F50 00343B30  3C 80 80 4A */	lis r4, lbl_804A7C80@ha
/* 80346F54 00343B34  54 63 30 32 */	slwi r3, r3, 6
/* 80346F58 00343B38  38 04 7C 80 */	addi r0, r4, lbl_804A7C80@l
/* 80346F5C 00343B3C  7C 60 1A 14 */	add r3, r0, r3
/* 80346F60 00343B40  80 63 00 0C */	lwz r3, 0xc(r3)
/* 80346F64 00343B44  4E 80 00 20 */	blr 

.global UnlockedHandler
UnlockedHandler:
/* 80346F68 00343B48  7C 08 02 A6 */	mflr r0
/* 80346F6C 00343B4C  38 80 00 00 */	li r4, 0
/* 80346F70 00343B50  90 01 00 04 */	stw r0, 4(r1)
/* 80346F74 00343B54  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80346F78 00343B58  38 A1 00 10 */	addi r5, r1, 0x10
/* 80346F7C 00343B5C  48 00 00 15 */	bl EXIGetID
/* 80346F80 00343B60  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80346F84 00343B64  38 21 00 18 */	addi r1, r1, 0x18
/* 80346F88 00343B68  7C 08 03 A6 */	mtlr r0
/* 80346F8C 00343B6C  4E 80 00 20 */	blr 

.global EXIGetID
EXIGetID:
/* 80346F90 00343B70  7C 08 02 A6 */	mflr r0
/* 80346F94 00343B74  90 01 00 04 */	stw r0, 4(r1)
/* 80346F98 00343B78  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80346F9C 00343B7C  BF 01 00 20 */	stmw r24, 0x20(r1)
/* 80346FA0 00343B80  3B 43 00 00 */	addi r26, r3, 0
/* 80346FA4 00343B84  3C 60 80 4A */	lis r3, lbl_804A7C80@ha
/* 80346FA8 00343B88  2C 1A 00 02 */	cmpwi r26, 2
/* 80346FAC 00343B8C  57 46 30 32 */	slwi r6, r26, 6
/* 80346FB0 00343B90  38 03 7C 80 */	addi r0, r3, lbl_804A7C80@l
/* 80346FB4 00343B94  7F E0 32 14 */	add r31, r0, r6
/* 80346FB8 00343B98  3B 64 00 00 */	addi r27, r4, 0
/* 80346FBC 00343B9C  3B 85 00 00 */	addi r28, r5, 0
/* 80346FC0 00343BA0  40 80 00 E0 */	bge lbl_803470A0
/* 80346FC4 00343BA4  28 1B 00 00 */	cmplwi r27, 0
/* 80346FC8 00343BA8  40 82 00 D8 */	bne lbl_803470A0
/* 80346FCC 00343BAC  7F 43 D3 78 */	mr r3, r26
/* 80346FD0 00343BB0  4B FF F2 49 */	bl __EXIProbe
/* 80346FD4 00343BB4  2C 03 00 00 */	cmpwi r3, 0
/* 80346FD8 00343BB8  40 82 00 0C */	bne lbl_80346FE4
/* 80346FDC 00343BBC  38 60 00 00 */	li r3, 0
/* 80346FE0 00343BC0  48 00 03 18 */	b lbl_803472F8
lbl_80346FE4:
/* 80346FE4 00343BC4  3C 60 80 00 */	lis r3, 0x800030C0@ha
/* 80346FE8 00343BC8  80 9F 00 20 */	lwz r4, 0x20(r31)
/* 80346FEC 00343BCC  57 40 10 3A */	slwi r0, r26, 2
/* 80346FF0 00343BD0  3B C3 30 C0 */	addi r30, r3, 0x800030C0@l
/* 80346FF4 00343BD4  7F DE 02 14 */	add r30, r30, r0
/* 80346FF8 00343BD8  80 1E 00 00 */	lwz r0, 0(r30)
/* 80346FFC 00343BDC  7C 04 00 00 */	cmpw r4, r0
/* 80347000 00343BE0  40 82 00 14 */	bne lbl_80347014
/* 80347004 00343BE4  80 1F 00 1C */	lwz r0, 0x1c(r31)
/* 80347008 00343BE8  90 1C 00 00 */	stw r0, 0(r28)
/* 8034700C 00343BEC  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 80347010 00343BF0  48 00 02 E8 */	b lbl_803472F8
lbl_80347014:
/* 80347014 00343BF4  48 00 03 51 */	bl OSDisableInterrupts
/* 80347018 00343BF8  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 8034701C 00343BFC  3B A3 00 00 */	addi r29, r3, 0
/* 80347020 00343C00  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 80347024 00343C04  40 82 00 14 */	bne lbl_80347038
/* 80347028 00343C08  7F 43 D3 78 */	mr r3, r26
/* 8034702C 00343C0C  4B FF F1 ED */	bl __EXIProbe
/* 80347030 00343C10  2C 03 00 00 */	cmpwi r3, 0
/* 80347034 00343C14  40 82 00 14 */	bne lbl_80347048
lbl_80347038:
/* 80347038 00343C18  7F A3 EB 78 */	mr r3, r29
/* 8034703C 00343C1C  48 00 03 51 */	bl OSRestoreInterrupts
/* 80347040 00343C20  38 00 00 00 */	li r0, 0
/* 80347044 00343C24  48 00 00 48 */	b lbl_8034708C
lbl_80347048:
/* 80347048 00343C28  38 7A 00 00 */	addi r3, r26, 0
/* 8034704C 00343C2C  38 80 00 01 */	li r4, 1
/* 80347050 00343C30  38 A0 00 00 */	li r5, 0
/* 80347054 00343C34  38 C0 00 00 */	li r6, 0
/* 80347058 00343C38  4B FF F0 FD */	bl EXIClearInterrupts
/* 8034705C 00343C3C  1C 1A 00 03 */	mulli r0, r26, 3
/* 80347060 00343C40  38 80 00 00 */	li r4, 0
/* 80347064 00343C44  3C 60 00 10 */	lis r3, 0x10
/* 80347068 00343C48  90 9F 00 08 */	stw r4, 8(r31)
/* 8034706C 00343C4C  7C 63 04 30 */	srw r3, r3, r0
/* 80347070 00343C50  48 00 07 45 */	bl __OSUnmaskInterrupts
/* 80347074 00343C54  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80347078 00343C58  38 7D 00 00 */	addi r3, r29, 0
/* 8034707C 00343C5C  60 00 00 08 */	ori r0, r0, 8
/* 80347080 00343C60  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80347084 00343C64  48 00 03 09 */	bl OSRestoreInterrupts
/* 80347088 00343C68  38 00 00 01 */	li r0, 1
lbl_8034708C:
/* 8034708C 00343C6C  2C 00 00 00 */	cmpwi r0, 0
/* 80347090 00343C70  40 82 00 0C */	bne lbl_8034709C
/* 80347094 00343C74  38 60 00 00 */	li r3, 0
/* 80347098 00343C78  48 00 02 60 */	b lbl_803472F8
lbl_8034709C:
/* 8034709C 00343C7C  83 BE 00 00 */	lwz r29, 0(r30)
lbl_803470A0:
/* 803470A0 00343C80  2C 1A 00 02 */	cmpwi r26, 2
/* 803470A4 00343C84  38 00 00 00 */	li r0, 0
/* 803470A8 00343C88  40 80 00 10 */	bge lbl_803470B8
/* 803470AC 00343C8C  28 1B 00 00 */	cmplwi r27, 0
/* 803470B0 00343C90  40 82 00 08 */	bne lbl_803470B8
/* 803470B4 00343C94  38 00 00 01 */	li r0, 1
lbl_803470B8:
/* 803470B8 00343C98  2C 00 00 00 */	cmpwi r0, 0
/* 803470BC 00343C9C  41 82 00 10 */	beq lbl_803470CC
/* 803470C0 00343CA0  3C 60 80 34 */	lis r3, UnlockedHandler@ha
/* 803470C4 00343CA4  38 A3 6F 68 */	addi r5, r3, UnlockedHandler@l
/* 803470C8 00343CA8  48 00 00 08 */	b lbl_803470D0
lbl_803470CC:
/* 803470CC 00343CAC  38 A0 00 00 */	li r5, 0
lbl_803470D0:
/* 803470D0 00343CB0  38 7A 00 00 */	addi r3, r26, 0
/* 803470D4 00343CB4  38 9B 00 00 */	addi r4, r27, 0
/* 803470D8 00343CB8  4B FF FC A9 */	bl EXILock
/* 803470DC 00343CBC  7C 60 00 34 */	cntlzw r0, r3
/* 803470E0 00343CC0  54 00 D9 7E */	srwi r0, r0, 5
/* 803470E4 00343CC4  7C 1E 03 79 */	or. r30, r0, r0
/* 803470E8 00343CC8  40 82 01 34 */	bne lbl_8034721C
/* 803470EC 00343CCC  38 7A 00 00 */	addi r3, r26, 0
/* 803470F0 00343CD0  38 9B 00 00 */	addi r4, r27, 0
/* 803470F4 00343CD4  38 A0 00 00 */	li r5, 0
/* 803470F8 00343CD8  4B FF F5 91 */	bl EXISelect
/* 803470FC 00343CDC  7C 60 00 34 */	cntlzw r0, r3
/* 80347100 00343CE0  54 00 D9 7E */	srwi r0, r0, 5
/* 80347104 00343CE4  7C 1E 03 79 */	or. r30, r0, r0
/* 80347108 00343CE8  40 82 00 90 */	bne lbl_80347198
/* 8034710C 00343CEC  38 00 00 00 */	li r0, 0
/* 80347110 00343CF0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80347114 00343CF4  38 7A 00 00 */	addi r3, r26, 0
/* 80347118 00343CF8  38 81 00 1C */	addi r4, r1, 0x1c
/* 8034711C 00343CFC  38 A0 00 02 */	li r5, 2
/* 80347120 00343D00  38 C0 00 01 */	li r6, 1
/* 80347124 00343D04  38 E0 00 00 */	li r7, 0
/* 80347128 00343D08  4B FF EA 3D */	bl EXIImm
/* 8034712C 00343D0C  7C 60 00 34 */	cntlzw r0, r3
/* 80347130 00343D10  54 00 D9 7E */	srwi r0, r0, 5
/* 80347134 00343D14  38 7A 00 00 */	addi r3, r26, 0
/* 80347138 00343D18  7F DE 03 78 */	or r30, r30, r0
/* 8034713C 00343D1C  4B FF EE 11 */	bl EXISync
/* 80347140 00343D20  7C 60 00 34 */	cntlzw r0, r3
/* 80347144 00343D24  54 00 D9 7E */	srwi r0, r0, 5
/* 80347148 00343D28  38 7A 00 00 */	addi r3, r26, 0
/* 8034714C 00343D2C  38 9C 00 00 */	addi r4, r28, 0
/* 80347150 00343D30  7F DE 03 78 */	or r30, r30, r0
/* 80347154 00343D34  38 A0 00 04 */	li r5, 4
/* 80347158 00343D38  38 C0 00 00 */	li r6, 0
/* 8034715C 00343D3C  38 E0 00 00 */	li r7, 0
/* 80347160 00343D40  4B FF EA 05 */	bl EXIImm
/* 80347164 00343D44  7C 60 00 34 */	cntlzw r0, r3
/* 80347168 00343D48  54 00 D9 7E */	srwi r0, r0, 5
/* 8034716C 00343D4C  38 7A 00 00 */	addi r3, r26, 0
/* 80347170 00343D50  7F DE 03 78 */	or r30, r30, r0
/* 80347174 00343D54  4B FF ED D9 */	bl EXISync
/* 80347178 00343D58  7C 60 00 34 */	cntlzw r0, r3
/* 8034717C 00343D5C  54 00 D9 7E */	srwi r0, r0, 5
/* 80347180 00343D60  38 7A 00 00 */	addi r3, r26, 0
/* 80347184 00343D64  7F DE 03 78 */	or r30, r30, r0
/* 80347188 00343D68  4B FF F6 2D */	bl EXIDeselect
/* 8034718C 00343D6C  7C 60 00 34 */	cntlzw r0, r3
/* 80347190 00343D70  54 00 D9 7E */	srwi r0, r0, 5
/* 80347194 00343D74  7F DE 03 78 */	or r30, r30, r0
lbl_80347198:
/* 80347198 00343D78  48 00 01 CD */	bl OSDisableInterrupts
/* 8034719C 00343D7C  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 803471A0 00343D80  3B 03 00 00 */	addi r24, r3, 0
/* 803471A4 00343D84  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 803471A8 00343D88  40 82 00 10 */	bne lbl_803471B8
/* 803471AC 00343D8C  7F 03 C3 78 */	mr r3, r24
/* 803471B0 00343D90  48 00 01 DD */	bl OSRestoreInterrupts
/* 803471B4 00343D94  48 00 00 68 */	b lbl_8034721C
lbl_803471B8:
/* 803471B8 00343D98  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 803471BC 00343D9C  38 7A 00 00 */	addi r3, r26, 0
/* 803471C0 00343DA0  38 9F 00 00 */	addi r4, r31, 0
/* 803471C4 00343DA4  54 00 07 34 */	rlwinm r0, r0, 0, 0x1c, 0x1a
/* 803471C8 00343DA8  90 1F 00 0C */	stw r0, 0xc(r31)
/* 803471CC 00343DAC  4B FF E8 A5 */	bl SetExiInterruptMask
/* 803471D0 00343DB0  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 803471D4 00343DB4  2C 03 00 00 */	cmpwi r3, 0
/* 803471D8 00343DB8  40 81 00 3C */	ble lbl_80347214
/* 803471DC 00343DBC  34 03 FF FF */	addic. r0, r3, -1
/* 803471E0 00343DC0  83 3F 00 2C */	lwz r25, 0x2c(r31)
/* 803471E4 00343DC4  90 1F 00 24 */	stw r0, 0x24(r31)
/* 803471E8 00343DC8  40 81 00 18 */	ble lbl_80347200
/* 803471EC 00343DCC  80 1F 00 24 */	lwz r0, 0x24(r31)
/* 803471F0 00343DD0  38 7F 00 28 */	addi r3, r31, 0x28
/* 803471F4 00343DD4  38 9F 00 30 */	addi r4, r31, 0x30
/* 803471F8 00343DD8  54 05 18 38 */	slwi r5, r0, 3
/* 803471FC 00343DDC  4B FD C7 3D */	bl memmove
lbl_80347200:
/* 80347200 00343DE0  39 99 00 00 */	addi r12, r25, 0
/* 80347204 00343DE4  7D 88 03 A6 */	mtlr r12
/* 80347208 00343DE8  38 7A 00 00 */	addi r3, r26, 0
/* 8034720C 00343DEC  38 80 00 00 */	li r4, 0
/* 80347210 00343DF0  4E 80 00 21 */	blrl 
lbl_80347214:
/* 80347214 00343DF4  7F 03 C3 78 */	mr r3, r24
/* 80347218 00343DF8  48 00 01 75 */	bl OSRestoreInterrupts
lbl_8034721C:
/* 8034721C 00343DFC  2C 1A 00 02 */	cmpwi r26, 2
/* 80347220 00343E00  40 80 00 C4 */	bge lbl_803472E4
/* 80347224 00343E04  28 1B 00 00 */	cmplwi r27, 0
/* 80347228 00343E08  40 82 00 BC */	bne lbl_803472E4
/* 8034722C 00343E0C  48 00 01 39 */	bl OSDisableInterrupts
/* 80347230 00343E10  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80347234 00343E14  3B 03 00 00 */	addi r24, r3, 0
/* 80347238 00343E18  54 00 07 39 */	rlwinm. r0, r0, 0, 0x1c, 0x1c
/* 8034723C 00343E1C  40 82 00 10 */	bne lbl_8034724C
/* 80347240 00343E20  7F 03 C3 78 */	mr r3, r24
/* 80347244 00343E24  48 00 01 49 */	bl OSRestoreInterrupts
/* 80347248 00343E28  48 00 00 4C */	b lbl_80347294
lbl_8034724C:
/* 8034724C 00343E2C  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80347250 00343E30  54 00 06 F7 */	rlwinm. r0, r0, 0, 0x1b, 0x1b
/* 80347254 00343E34  41 82 00 1C */	beq lbl_80347270
/* 80347258 00343E38  80 1F 00 18 */	lwz r0, 0x18(r31)
/* 8034725C 00343E3C  28 00 00 00 */	cmplwi r0, 0
/* 80347260 00343E40  40 82 00 10 */	bne lbl_80347270
/* 80347264 00343E44  7F 03 C3 78 */	mr r3, r24
/* 80347268 00343E48  48 00 01 25 */	bl OSRestoreInterrupts
/* 8034726C 00343E4C  48 00 00 28 */	b lbl_80347294
lbl_80347270:
/* 80347270 00343E50  80 7F 00 0C */	lwz r3, 0xc(r31)
/* 80347274 00343E54  1C 1A 00 03 */	mulli r0, r26, 3
/* 80347278 00343E58  54 64 07 76 */	rlwinm r4, r3, 0, 0x1d, 0x1b
/* 8034727C 00343E5C  3C 60 00 70 */	lis r3, 0x70
/* 80347280 00343E60  90 9F 00 0C */	stw r4, 0xc(r31)
/* 80347284 00343E64  7C 63 04 30 */	srw r3, r3, r0
/* 80347288 00343E68  48 00 04 A5 */	bl __OSMaskInterrupts
/* 8034728C 00343E6C  7F 03 C3 78 */	mr r3, r24
/* 80347290 00343E70  48 00 00 FD */	bl OSRestoreInterrupts
lbl_80347294:
/* 80347294 00343E74  48 00 00 D1 */	bl OSDisableInterrupts
/* 80347298 00343E78  3C 80 80 00 */	lis r4, 0x800030C0@ha
/* 8034729C 00343E7C  57 40 10 3A */	slwi r0, r26, 2
/* 803472A0 00343E80  38 84 30 C0 */	addi r4, r4, 0x800030C0@l
/* 803472A4 00343E84  7C 04 00 2E */	lwzx r0, r4, r0
/* 803472A8 00343E88  7C 9D 00 50 */	subf r4, r29, r0
/* 803472AC 00343E8C  30 04 FF FF */	addic r0, r4, -1
/* 803472B0 00343E90  7C 00 21 10 */	subfe r0, r0, r4
/* 803472B4 00343E94  7F DE 03 79 */	or. r30, r30, r0
/* 803472B8 00343E98  40 82 00 10 */	bne lbl_803472C8
/* 803472BC 00343E9C  80 1C 00 00 */	lwz r0, 0(r28)
/* 803472C0 00343EA0  90 1F 00 1C */	stw r0, 0x1c(r31)
/* 803472C4 00343EA4  93 BF 00 20 */	stw r29, 0x20(r31)
lbl_803472C8:
/* 803472C8 00343EA8  48 00 00 C5 */	bl OSRestoreInterrupts
/* 803472CC 00343EAC  2C 1E 00 00 */	cmpwi r30, 0
/* 803472D0 00343EB0  41 82 00 0C */	beq lbl_803472DC
/* 803472D4 00343EB4  38 60 00 00 */	li r3, 0
/* 803472D8 00343EB8  48 00 00 20 */	b lbl_803472F8
lbl_803472DC:
/* 803472DC 00343EBC  80 7F 00 20 */	lwz r3, 0x20(r31)
/* 803472E0 00343EC0  48 00 00 18 */	b lbl_803472F8
lbl_803472E4:
/* 803472E4 00343EC4  2C 1E 00 00 */	cmpwi r30, 0
/* 803472E8 00343EC8  41 82 00 0C */	beq lbl_803472F4
/* 803472EC 00343ECC  38 60 00 00 */	li r3, 0
/* 803472F0 00343ED0  48 00 00 08 */	b lbl_803472F8
lbl_803472F4:
/* 803472F4 00343ED4  38 60 00 01 */	li r3, 1
lbl_803472F8:
/* 803472F8 00343ED8  BB 01 00 20 */	lmw r24, 0x20(r1)
/* 803472FC 00343EDC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80347300 00343EE0  38 21 00 40 */	addi r1, r1, 0x40
/* 80347304 00343EE4  7C 08 03 A6 */	mtlr r0
/* 80347308 00343EE8  4E 80 00 20 */	blr 


.section .bss, "wa"
    .balign 8
.global lbl_804A7C80
lbl_804A7C80:
	.skip 0xC0
