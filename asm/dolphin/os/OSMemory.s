.include "macros.inc"

.section .text  # 0x80347BE4 - 0x80347ED8

.global OSGetPhysicalMemSize
OSGetPhysicalMemSize:
/* 80347BE4 003447C4  3C 60 80 00 */	lis r3, 0x80000028@ha
/* 80347BE8 003447C8  80 63 00 28 */	lwz r3, 0x80000028@l(r3)
/* 80347BEC 003447CC  4E 80 00 20 */	blr 

.global OSGetConsoleSimulatedMemSize
OSGetConsoleSimulatedMemSize:
/* 80347BF0 003447D0  3C 60 80 00 */	lis r3, 0x800000F0@ha
/* 80347BF4 003447D4  80 63 00 F0 */	lwz r3, 0x800000F0@l(r3)
/* 80347BF8 003447D8  4E 80 00 20 */	blr 

.global OSOnReset
OSOnReset:
/* 80347BFC 003447DC  7C 08 02 A6 */	mflr r0
/* 80347C00 003447E0  2C 03 00 00 */	cmpwi r3, 0
/* 80347C04 003447E4  90 01 00 04 */	stw r0, 4(r1)
/* 80347C08 003447E8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80347C0C 003447EC  41 82 00 18 */	beq lbl_80347C24
/* 80347C10 003447F0  3C 60 CC 00 */	lis r3, 0xCC004010@ha
/* 80347C14 003447F4  38 00 00 FF */	li r0, 0xff
/* 80347C18 003447F8  B0 03 40 10 */	sth r0, 0xCC004010@l(r3)
/* 80347C1C 003447FC  3C 60 F0 00 */	lis r3, 0xf000
/* 80347C20 00344800  4B FF FB 0D */	bl __OSMaskInterrupts
lbl_80347C24:
/* 80347C24 00344804  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80347C28 00344808  38 60 00 01 */	li r3, 1
/* 80347C2C 0034480C  38 21 00 08 */	addi r1, r1, 8
/* 80347C30 00344810  7C 08 03 A6 */	mtlr r0
/* 80347C34 00344814  4E 80 00 20 */	blr 

.global MEMIntrruptHandler
MEMIntrruptHandler:
/* 80347C38 00344818  7C 08 02 A6 */	mflr r0
/* 80347C3C 0034481C  3C 60 CC 00 */	lis r3, 0xCC004000@ha
/* 80347C40 00344820  90 01 00 04 */	stw r0, 4(r1)
/* 80347C44 00344824  39 03 40 00 */	addi r8, r3, 0xCC004000@l
/* 80347C48 00344828  38 00 00 00 */	li r0, 0
/* 80347C4C 0034482C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80347C50 00344830  A0 E3 40 24 */	lhz r7, 0x4024(r3)
/* 80347C54 00344834  3C 60 80 4A */	lis r3, __OSErrorTable@ha
/* 80347C58 00344838  A0 C8 00 22 */	lhz r6, 0x22(r8)
/* 80347C5C 0034483C  38 63 7C 40 */	addi r3, r3, __OSErrorTable@l
/* 80347C60 00344840  A0 A8 00 1E */	lhz r5, 0x1e(r8)
/* 80347C64 00344844  50 E6 81 9E */	rlwimi r6, r7, 0x10, 6, 0xf
/* 80347C68 00344848  B0 08 00 20 */	sth r0, 0x20(r8)
/* 80347C6C 0034484C  81 83 00 3C */	lwz r12, 0x3c(r3)
/* 80347C70 00344850  28 0C 00 00 */	cmplwi r12, 0
/* 80347C74 00344854  41 82 00 18 */	beq lbl_80347C8C
/* 80347C78 00344858  7D 88 03 A6 */	mtlr r12
/* 80347C7C 0034485C  38 60 00 0F */	li r3, 0xf
/* 80347C80 00344860  4C C6 31 82 */	crclr 6
/* 80347C84 00344864  4E 80 00 21 */	blrl 
/* 80347C88 00344868  48 00 00 0C */	b lbl_80347C94
lbl_80347C8C:
/* 80347C8C 0034486C  38 60 00 0F */	li r3, 0xf
/* 80347C90 00344870  4B FF DB E1 */	bl __OSUnhandledException
lbl_80347C94:
/* 80347C94 00344874  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80347C98 00344878  38 21 00 08 */	addi r1, r1, 8
/* 80347C9C 0034487C  7C 08 03 A6 */	mtlr r0
/* 80347CA0 00344880  4E 80 00 20 */	blr 

.global Config24MB
Config24MB:
/* 80347CA4 00344884  38 E0 00 00 */	li r7, 0
/* 80347CA8 00344888  3C 80 00 00 */	lis r4, 0x00000002@ha
/* 80347CAC 0034488C  38 84 00 02 */	addi r4, r4, 0x00000002@l
/* 80347CB0 00344890  3C 60 80 00 */	lis r3, 0x800001FF@ha
/* 80347CB4 00344894  38 63 01 FF */	addi r3, r3, 0x800001FF@l
/* 80347CB8 00344898  3C C0 01 00 */	lis r6, 0x01000002@ha
/* 80347CBC 0034489C  38 C6 00 02 */	addi r6, r6, 0x01000002@l
/* 80347CC0 003448A0  3C A0 81 00 */	lis r5, 0x810000FF@ha
/* 80347CC4 003448A4  38 A5 00 FF */	addi r5, r5, 0x810000FF@l
/* 80347CC8 003448A8  4C 00 01 2C */	isync 
/* 80347CCC 003448AC  7C F8 83 A6 */	mtdbatu 0, r7
/* 80347CD0 003448B0  7C 99 83 A6 */	mtdbatl 0, r4
/* 80347CD4 003448B4  7C 78 83 A6 */	mtdbatu 0, r3
/* 80347CD8 003448B8  4C 00 01 2C */	isync 
/* 80347CDC 003448BC  7C F0 83 A6 */	mtibatu 0, r7
/* 80347CE0 003448C0  7C 91 83 A6 */	mtibatl 0, r4
/* 80347CE4 003448C4  7C 70 83 A6 */	mtibatu 0, r3
/* 80347CE8 003448C8  4C 00 01 2C */	isync 
/* 80347CEC 003448CC  7C FC 83 A6 */	mtdbatu 2, r7
/* 80347CF0 003448D0  7C DD 83 A6 */	mtdbatl 2, r6
/* 80347CF4 003448D4  7C BC 83 A6 */	mtdbatu 2, r5
/* 80347CF8 003448D8  4C 00 01 2C */	isync 
/* 80347CFC 003448DC  7C F4 83 A6 */	mtibatu 2, r7
/* 80347D00 003448E0  7C D5 83 A6 */	mtibatl 2, r6
/* 80347D04 003448E4  7C B4 83 A6 */	mtibatu 2, r5
/* 80347D08 003448E8  4C 00 01 2C */	isync 
/* 80347D0C 003448EC  7C 60 00 A6 */	mfmsr r3
/* 80347D10 003448F0  60 63 00 30 */	ori r3, r3, 0x30
/* 80347D14 003448F4  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347D18 003448F8  7C 68 02 A6 */	mflr r3
/* 80347D1C 003448FC  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347D20 00344900  4C 00 00 64 */	rfi 

.global Config48MB
Config48MB:
/* 80347D24 00344904  38 E0 00 00 */	li r7, 0
/* 80347D28 00344908  3C 80 00 00 */	lis r4, 0x00000002@ha
/* 80347D2C 0034490C  38 84 00 02 */	addi r4, r4, 0x00000002@l
/* 80347D30 00344910  3C 60 80 00 */	lis r3, 0x800003FF@ha
/* 80347D34 00344914  38 63 03 FF */	addi r3, r3, 0x800003FF@l
/* 80347D38 00344918  3C C0 02 00 */	lis r6, 0x02000002@ha
/* 80347D3C 0034491C  38 C6 00 02 */	addi r6, r6, 0x02000002@l
/* 80347D40 00344920  3C A0 82 00 */	lis r5, 0x820001FF@ha
/* 80347D44 00344924  38 A5 01 FF */	addi r5, r5, 0x820001FF@l
/* 80347D48 00344928  4C 00 01 2C */	isync 
/* 80347D4C 0034492C  7C F8 83 A6 */	mtdbatu 0, r7
/* 80347D50 00344930  7C 99 83 A6 */	mtdbatl 0, r4
/* 80347D54 00344934  7C 78 83 A6 */	mtdbatu 0, r3
/* 80347D58 00344938  4C 00 01 2C */	isync 
/* 80347D5C 0034493C  7C F0 83 A6 */	mtibatu 0, r7
/* 80347D60 00344940  7C 91 83 A6 */	mtibatl 0, r4
/* 80347D64 00344944  7C 70 83 A6 */	mtibatu 0, r3
/* 80347D68 00344948  4C 00 01 2C */	isync 
/* 80347D6C 0034494C  7C FC 83 A6 */	mtdbatu 2, r7
/* 80347D70 00344950  7C DD 83 A6 */	mtdbatl 2, r6
/* 80347D74 00344954  7C BC 83 A6 */	mtdbatu 2, r5
/* 80347D78 00344958  4C 00 01 2C */	isync 
/* 80347D7C 0034495C  7C F4 83 A6 */	mtibatu 2, r7
/* 80347D80 00344960  7C D5 83 A6 */	mtibatl 2, r6
/* 80347D84 00344964  7C B4 83 A6 */	mtibatu 2, r5
/* 80347D88 00344968  4C 00 01 2C */	isync 
/* 80347D8C 0034496C  7C 60 00 A6 */	mfmsr r3
/* 80347D90 00344970  60 63 00 30 */	ori r3, r3, 0x30
/* 80347D94 00344974  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347D98 00344978  7C 68 02 A6 */	mflr r3
/* 80347D9C 0034497C  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347DA0 00344980  4C 00 00 64 */	rfi 

.global RealMode
RealMode:
/* 80347DA4 00344984  54 63 00 BE */	clrlwi r3, r3, 2
/* 80347DA8 00344988  7C 7A 03 A6 */	mtspr 0x1a, r3
/* 80347DAC 0034498C  7C 60 00 A6 */	mfmsr r3
/* 80347DB0 00344990  54 63 07 32 */	rlwinm r3, r3, 0, 0x1c, 0x19
/* 80347DB4 00344994  7C 7B 03 A6 */	mtspr 0x1b, r3
/* 80347DB8 00344998  4C 00 00 64 */	rfi 

.global __OSInitMemoryProtection
__OSInitMemoryProtection:
/* 80347DBC 0034499C  7C 08 02 A6 */	mflr r0
/* 80347DC0 003449A0  90 01 00 04 */	stw r0, 4(r1)
/* 80347DC4 003449A4  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 80347DC8 003449A8  93 E1 00 44 */	stw r31, 0x44(r1)
/* 80347DCC 003449AC  93 C1 00 40 */	stw r30, 0x40(r1)
/* 80347DD0 003449B0  93 A1 00 3C */	stw r29, 0x3c(r1)
/* 80347DD4 003449B4  3C 60 80 00 */	lis r3, 0x800000F0@ha
/* 80347DD8 003449B8  83 A3 00 F0 */	lwz r29, 0x800000F0@l(r3)
/* 80347DDC 003449BC  4B FF F5 89 */	bl OSDisableInterrupts
/* 80347DE0 003449C0  3C 00 01 80 */	lis r0, 0x180
/* 80347DE4 003449C4  7C 1D 00 40 */	cmplw r29, r0
/* 80347DE8 003449C8  7C 7F 1B 78 */	mr r31, r3
/* 80347DEC 003449CC  41 81 00 14 */	bgt lbl_80347E00
/* 80347DF0 003449D0  3C 60 80 34 */	lis r3, Config24MB@ha
/* 80347DF4 003449D4  38 63 7C A4 */	addi r3, r3, Config24MB@l
/* 80347DF8 003449D8  4B FF FF AD */	bl RealMode
/* 80347DFC 003449DC  48 00 00 1C */	b lbl_80347E18
lbl_80347E00:
/* 80347E00 003449E0  3C 00 03 00 */	lis r0, 0x300
/* 80347E04 003449E4  7C 1D 00 40 */	cmplw r29, r0
/* 80347E08 003449E8  41 81 00 10 */	bgt lbl_80347E18
/* 80347E0C 003449EC  3C 60 80 34 */	lis r3, Config48MB@ha
/* 80347E10 003449F0  38 63 7D 24 */	addi r3, r3, Config48MB@l
/* 80347E14 003449F4  4B FF FF 91 */	bl RealMode
lbl_80347E18:
/* 80347E18 003449F8  3C 60 CC 00 */	lis r3, 0xCC004000@ha
/* 80347E1C 003449FC  3B A3 40 00 */	addi r29, r3, 0xCC004000@l
/* 80347E20 00344A00  38 00 00 00 */	li r0, 0
/* 80347E24 00344A04  B0 1D 00 20 */	sth r0, 0x20(r29)
/* 80347E28 00344A08  38 00 00 FF */	li r0, 0xff
/* 80347E2C 00344A0C  3C 60 F0 00 */	lis r3, 0xf000
/* 80347E30 00344A10  B0 1D 00 10 */	sth r0, 0x10(r29)
/* 80347E34 00344A14  4B FF F8 F9 */	bl __OSMaskInterrupts
/* 80347E38 00344A18  3C 60 80 34 */	lis r3, MEMIntrruptHandler@ha
/* 80347E3C 00344A1C  3B C3 7C 38 */	addi r30, r3, MEMIntrruptHandler@l
/* 80347E40 00344A20  7F C4 F3 78 */	mr r4, r30
/* 80347E44 00344A24  38 60 00 00 */	li r3, 0
/* 80347E48 00344A28  4B FF F5 69 */	bl __OSSetInterruptHandler
/* 80347E4C 00344A2C  7F C4 F3 78 */	mr r4, r30
/* 80347E50 00344A30  38 60 00 01 */	li r3, 1
/* 80347E54 00344A34  4B FF F5 5D */	bl __OSSetInterruptHandler
/* 80347E58 00344A38  7F C4 F3 78 */	mr r4, r30
/* 80347E5C 00344A3C  38 60 00 02 */	li r3, 2
/* 80347E60 00344A40  4B FF F5 51 */	bl __OSSetInterruptHandler
/* 80347E64 00344A44  7F C4 F3 78 */	mr r4, r30
/* 80347E68 00344A48  38 60 00 03 */	li r3, 3
/* 80347E6C 00344A4C  4B FF F5 45 */	bl __OSSetInterruptHandler
/* 80347E70 00344A50  7F C4 F3 78 */	mr r4, r30
/* 80347E74 00344A54  38 60 00 04 */	li r3, 4
/* 80347E78 00344A58  4B FF F5 39 */	bl __OSSetInterruptHandler
/* 80347E7C 00344A5C  3C 60 80 40 */	lis r3, lbl_80402348@ha
/* 80347E80 00344A60  38 63 23 48 */	addi r3, r3, lbl_80402348@l
/* 80347E84 00344A64  48 00 04 8D */	bl OSRegisterResetFunction
/* 80347E88 00344A68  3C 60 80 00 */	lis r3, 0x800000F0@ha
/* 80347E8C 00344A6C  80 83 00 F0 */	lwz r4, 0x800000F0@l(r3)
/* 80347E90 00344A70  80 03 00 28 */	lwz r0, 0x28(r3)
/* 80347E94 00344A74  7C 04 00 40 */	cmplw r4, r0
/* 80347E98 00344A78  40 80 00 18 */	bge lbl_80347EB0
/* 80347E9C 00344A7C  3C 04 FE 80 */	addis r0, r4, 0xfe80
/* 80347EA0 00344A80  28 00 00 00 */	cmplwi r0, 0
/* 80347EA4 00344A84  40 82 00 0C */	bne lbl_80347EB0
/* 80347EA8 00344A88  38 00 00 02 */	li r0, 2
/* 80347EAC 00344A8C  B0 1D 00 28 */	sth r0, 0x28(r29)
lbl_80347EB0:
/* 80347EB0 00344A90  3C 60 08 00 */	lis r3, 0x800
/* 80347EB4 00344A94  4B FF F9 01 */	bl __OSUnmaskInterrupts
/* 80347EB8 00344A98  7F E3 FB 78 */	mr r3, r31
/* 80347EBC 00344A9C  4B FF F4 D1 */	bl OSRestoreInterrupts
/* 80347EC0 00344AA0  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 80347EC4 00344AA4  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 80347EC8 00344AA8  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 80347ECC 00344AAC  7C 08 03 A6 */	mtlr r0
/* 80347ED0 00344AB0  83 A1 00 3C */	lwz r29, 0x3c(r1)
/* 80347ED4 00344AB4  38 21 00 48 */	addi r1, r1, 0x48
/* 80347ED8 00344AB8  4E 80 00 20 */	blr 


.section .data

.global lbl_80402348
lbl_80402348:
    .4byte OSOnReset
    .4byte 0x0000007F
    .4byte NULL
    .4byte NULL
