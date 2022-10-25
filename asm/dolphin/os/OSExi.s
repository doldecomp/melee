.include "macros.inc"

.section .text  # 0x80345A70 - 0x80347308

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
