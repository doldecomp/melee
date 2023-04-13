.include "macros.inc"

.section .text

.global __AXGetCommandListCycles
__AXGetCommandListCycles:
/* 803592B4 00355E94  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 803592B8 00355E98  4E 80 00 20 */	blr

.global __AXGetCommandListAddress
__AXGetCommandListAddress:
/* 803592BC 00355E9C  80 AD BE 88 */	lwz r5, __AXCommandListPosition@sda21(r13)
/* 803592C0 00355EA0  3C 60 80 4B */	lis r3, __AXCommandList@ha
/* 803592C4 00355EA4  38 83 BB 80 */	addi r4, r3, __AXCommandList@l
/* 803592C8 00355EA8  38 05 00 01 */	addi r0, r5, 1
/* 803592CC 00355EAC  90 0D BE 88 */	stw r0, __AXCommandListPosition@sda21(r13)
/* 803592D0 00355EB0  1C 65 03 00 */	mulli r3, r5, 0x300
/* 803592D4 00355EB4  80 0D BE 88 */	lwz r0, __AXCommandListPosition@sda21(r13)
/* 803592D8 00355EB8  7C 64 1A 14 */	add r3, r4, r3
/* 803592DC 00355EBC  54 00 07 FE */	clrlwi r0, r0, 0x1f
/* 803592E0 00355EC0  90 0D BE 88 */	stw r0, __AXCommandListPosition@sda21(r13)
/* 803592E4 00355EC4  80 0D BE 88 */	lwz r0, __AXCommandListPosition@sda21(r13)
/* 803592E8 00355EC8  1C 00 03 00 */	mulli r0, r0, 0x300
/* 803592EC 00355ECC  7C 04 02 14 */	add r0, r4, r0
/* 803592F0 00355ED0  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 803592F4 00355ED4  4E 80 00 20 */	blr

.global __AXNextFrame
__AXNextFrame:
/* 803592F8 00355ED8  7C 08 02 A6 */	mflr r0
/* 803592FC 00355EDC  90 01 00 04 */	stw r0, 4(r1)
/* 80359300 00355EE0  38 00 01 A9 */	li r0, 0x1a9
/* 80359304 00355EE4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80359308 00355EE8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8035930C 00355EEC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80359310 00355EF0  3B C4 00 00 */	addi r30, r4, 0
/* 80359314 00355EF4  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80359318 00355EF8  3B A3 00 00 */	addi r29, r3, 0
/* 8035931C 00355EFC  83 ED BE 8C */	lwz r31, __AXClWrite@sda21(r13)
/* 80359320 00355F00  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
/* 80359324 00355F04  48 00 0A 69 */	bl __AXGetStudio
/* 80359328 00355F08  90 61 00 28 */	stw r3, 0x28(r1)
/* 8035932C 00355F0C  38 00 00 00 */	li r0, 0
/* 80359330 00355F10  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359334 00355F14  B0 03 00 00 */	sth r0, 0(r3)
/* 80359338 00355F18  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 8035933C 00355F1C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359340 00355F20  38 63 00 02 */	addi r3, r3, 2
/* 80359344 00355F24  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 80359348 00355F28  54 00 84 3E */	srwi r0, r0, 0x10
/* 8035934C 00355F2C  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359350 00355F30  B0 03 00 00 */	sth r0, 0(r3)
/* 80359354 00355F34  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359358 00355F38  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8035935C 00355F3C  38 63 00 02 */	addi r3, r3, 2
/* 80359360 00355F40  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 80359364 00355F44  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359368 00355F48  B0 03 00 00 */	sth r0, 0(r3)
/* 8035936C 00355F4C  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359370 00355F50  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 80359374 00355F54  80 0D BE 94 */	lwz r0, __AXClMode@sda21(r13)
/* 80359378 00355F58  38 84 00 02 */	addi r4, r4, 2
/* 8035937C 00355F5C  38 63 2E 44 */	addi r3, r3, 0x2e44
/* 80359380 00355F60  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 80359384 00355F64  2C 00 00 01 */	cmpwi r0, 1
/* 80359388 00355F68  90 6D BE 90 */	stw r3, __AXCommandListCycles@sda21(r13)
/* 8035938C 00355F6C  41 82 00 74 */	beq .L_80359400
/* 80359390 00355F70  40 80 00 10 */	bge .L_803593A0
/* 80359394 00355F74  2C 00 00 00 */	cmpwi r0, 0
/* 80359398 00355F78  40 80 00 14 */	bge .L_803593AC
/* 8035939C 00355F7C  48 00 00 B4 */	b .L_80359450
.L_803593A0:
/* 803593A0 00355F80  2C 00 00 04 */	cmpwi r0, 4
/* 803593A4 00355F84  41 82 00 5C */	beq .L_80359400
/* 803593A8 00355F88  48 00 00 A8 */	b .L_80359450
.L_803593AC:
/* 803593AC 00355F8C  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803593B0 00355F90  38 80 00 07 */	li r4, 7
/* 803593B4 00355F94  57 A0 84 3E */	srwi r0, r29, 0x10
/* 803593B8 00355F98  B0 83 00 00 */	sth r4, 0(r3)
/* 803593BC 00355F9C  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803593C0 00355FA0  38 63 00 02 */	addi r3, r3, 2
/* 803593C4 00355FA4  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 803593C8 00355FA8  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803593CC 00355FAC  B0 03 00 00 */	sth r0, 0(r3)
/* 803593D0 00355FB0  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803593D4 00355FB4  38 03 00 02 */	addi r0, r3, 2
/* 803593D8 00355FB8  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 803593DC 00355FBC  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803593E0 00355FC0  B3 A3 00 00 */	sth r29, 0(r3)
/* 803593E4 00355FC4  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803593E8 00355FC8  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 803593EC 00355FCC  38 84 00 02 */	addi r4, r4, 2
/* 803593F0 00355FD0  38 03 05 46 */	addi r0, r3, 0x546
/* 803593F4 00355FD4  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803593F8 00355FD8  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
/* 803593FC 00355FDC  48 00 00 54 */	b .L_80359450
.L_80359400:
/* 80359400 00355FE0  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359404 00355FE4  38 80 00 11 */	li r4, 0x11
/* 80359408 00355FE8  57 A0 84 3E */	srwi r0, r29, 0x10
/* 8035940C 00355FEC  B0 83 00 00 */	sth r4, 0(r3)
/* 80359410 00355FF0  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359414 00355FF4  38 63 00 02 */	addi r3, r3, 2
/* 80359418 00355FF8  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 8035941C 00355FFC  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359420 00356000  B0 03 00 00 */	sth r0, 0(r3)
/* 80359424 00356004  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359428 00356008  38 03 00 02 */	addi r0, r3, 2
/* 8035942C 0035600C  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 80359430 00356010  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359434 00356014  B3 A3 00 00 */	sth r29, 0(r3)
/* 80359438 00356018  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 8035943C 0035601C  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 80359440 00356020  38 84 00 02 */	addi r4, r4, 2
/* 80359444 00356024  38 03 05 E6 */	addi r0, r3, 0x5e6
/* 80359448 00356028  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 8035944C 0035602C  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
.L_80359450:
/* 80359450 00356030  48 00 17 2D */	bl __AXGetPBs
/* 80359454 00356034  90 61 00 28 */	stw r3, 0x28(r1)
/* 80359458 00356038  38 A0 00 02 */	li r5, 2
/* 8035945C 0035603C  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359460 00356040  38 00 00 03 */	li r0, 3
/* 80359464 00356044  38 61 00 28 */	addi r3, r1, 0x28
/* 80359468 00356048  B0 A4 00 00 */	sth r5, 0(r4)
/* 8035946C 0035604C  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 80359470 00356050  80 81 00 28 */	lwz r4, 0x28(r1)
/* 80359474 00356054  38 A5 00 02 */	addi r5, r5, 2
/* 80359478 00356058  90 AD BE 8C */	stw r5, __AXClWrite@sda21(r13)
/* 8035947C 0035605C  54 85 84 3E */	srwi r5, r4, 0x10
/* 80359480 00356060  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359484 00356064  B0 A4 00 00 */	sth r5, 0(r4)
/* 80359488 00356068  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 8035948C 0035606C  80 A1 00 28 */	lwz r5, 0x28(r1)
/* 80359490 00356070  38 84 00 02 */	addi r4, r4, 2
/* 80359494 00356074  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 80359498 00356078  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 8035949C 0035607C  B0 A4 00 00 */	sth r5, 0(r4)
/* 803594A0 00356080  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594A4 00356084  38 84 00 02 */	addi r4, r4, 2
/* 803594A8 00356088  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803594AC 0035608C  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594B0 00356090  B0 04 00 00 */	sth r0, 0(r4)
/* 803594B4 00356094  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594B8 00356098  38 04 00 02 */	addi r0, r4, 2
/* 803594BC 0035609C  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 803594C0 003560A0  4B FF FB AD */	bl __AXGetAuxAInput
/* 803594C4 003560A4  80 01 00 28 */	lwz r0, 0x28(r1)
/* 803594C8 003560A8  28 00 00 00 */	cmplwi r0, 0
/* 803594CC 003560AC  41 82 00 98 */	beq .L_80359564
/* 803594D0 003560B0  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594D4 003560B4  38 00 00 04 */	li r0, 4
/* 803594D8 003560B8  38 61 00 28 */	addi r3, r1, 0x28
/* 803594DC 003560BC  B0 04 00 00 */	sth r0, 0(r4)
/* 803594E0 003560C0  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594E4 003560C4  80 01 00 28 */	lwz r0, 0x28(r1)
/* 803594E8 003560C8  38 84 00 02 */	addi r4, r4, 2
/* 803594EC 003560CC  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803594F0 003560D0  54 00 84 3E */	srwi r0, r0, 0x10
/* 803594F4 003560D4  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803594F8 003560D8  B0 04 00 00 */	sth r0, 0(r4)
/* 803594FC 003560DC  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359500 003560E0  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359504 003560E4  38 84 00 02 */	addi r4, r4, 2
/* 80359508 003560E8  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 8035950C 003560EC  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359510 003560F0  B0 04 00 00 */	sth r0, 0(r4)
/* 80359514 003560F4  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359518 003560F8  38 04 00 02 */	addi r0, r4, 2
/* 8035951C 003560FC  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 80359520 00356100  4B FF FB 81 */	bl __AXGetAuxAOutput
/* 80359524 00356104  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359528 00356108  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 8035952C 0035610C  54 00 84 3E */	srwi r0, r0, 0x10
/* 80359530 00356110  B0 03 00 00 */	sth r0, 0(r3)
/* 80359534 00356114  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359538 00356118  80 01 00 28 */	lwz r0, 0x28(r1)
/* 8035953C 0035611C  38 63 00 02 */	addi r3, r3, 2
/* 80359540 00356120  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 80359544 00356124  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359548 00356128  B0 03 00 00 */	sth r0, 0(r3)
/* 8035954C 0035612C  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359550 00356130  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 80359554 00356134  38 84 00 02 */	addi r4, r4, 2
/* 80359558 00356138  38 03 0D ED */	addi r0, r3, 0xded
/* 8035955C 0035613C  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 80359560 00356140  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
.L_80359564:
/* 80359564 00356144  38 61 00 28 */	addi r3, r1, 0x28
/* 80359568 00356148  4B FF FB 55 */	bl __AXGetAuxBInput
/* 8035956C 0035614C  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359570 00356150  28 00 00 00 */	cmplwi r0, 0
/* 80359574 00356154  41 82 00 CC */	beq .L_80359640
/* 80359578 00356158  80 0D BE 94 */	lwz r0, __AXClMode@sda21(r13)
/* 8035957C 0035615C  28 00 00 04 */	cmplwi r0, 4
/* 80359580 00356160  40 82 00 2C */	bne .L_803595AC
/* 80359584 00356164  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359588 00356168  38 00 00 10 */	li r0, 0x10
/* 8035958C 0035616C  B0 03 00 00 */	sth r0, 0(r3)
/* 80359590 00356170  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359594 00356174  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 80359598 00356178  38 84 00 02 */	addi r4, r4, 2
/* 8035959C 0035617C  38 03 0D ED */	addi r0, r3, 0xded
/* 803595A0 00356180  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803595A4 00356184  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
/* 803595A8 00356188  48 00 00 28 */	b .L_803595D0
.L_803595AC:
/* 803595AC 0035618C  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 803595B0 00356190  38 00 00 05 */	li r0, 5
/* 803595B4 00356194  B0 03 00 00 */	sth r0, 0(r3)
/* 803595B8 00356198  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803595BC 0035619C  80 6D BE 90 */	lwz r3, __AXCommandListCycles@sda21(r13)
/* 803595C0 003561A0  38 84 00 02 */	addi r4, r4, 2
/* 803595C4 003561A4  38 03 0D ED */	addi r0, r3, 0xded
/* 803595C8 003561A8  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803595CC 003561AC  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
.L_803595D0:
/* 803595D0 003561B0  80 01 00 28 */	lwz r0, 0x28(r1)
/* 803595D4 003561B4  38 61 00 28 */	addi r3, r1, 0x28
/* 803595D8 003561B8  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803595DC 003561BC  54 00 84 3E */	srwi r0, r0, 0x10
/* 803595E0 003561C0  B0 04 00 00 */	sth r0, 0(r4)
/* 803595E4 003561C4  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803595E8 003561C8  80 01 00 28 */	lwz r0, 0x28(r1)
/* 803595EC 003561CC  38 84 00 02 */	addi r4, r4, 2
/* 803595F0 003561D0  90 8D BE 8C */	stw r4, __AXClWrite@sda21(r13)
/* 803595F4 003561D4  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 803595F8 003561D8  B0 04 00 00 */	sth r0, 0(r4)
/* 803595FC 003561DC  80 8D BE 8C */	lwz r4, __AXClWrite@sda21(r13)
/* 80359600 003561E0  38 04 00 02 */	addi r0, r4, 2
/* 80359604 003561E4  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 80359608 003561E8  4B FF FA E9 */	bl __AXGetAuxBOutput
/* 8035960C 003561EC  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359610 003561F0  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359614 003561F4  54 00 84 3E */	srwi r0, r0, 0x10
/* 80359618 003561F8  B0 03 00 00 */	sth r0, 0(r3)
/* 8035961C 003561FC  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359620 00356200  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80359624 00356204  38 63 00 02 */	addi r3, r3, 2
/* 80359628 00356208  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 8035962C 0035620C  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359630 00356210  B0 03 00 00 */	sth r0, 0(r3)
/* 80359634 00356214  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359638 00356218  38 03 00 02 */	addi r0, r3, 2
/* 8035963C 0035621C  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
.L_80359640:
/* 80359640 00356220  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 80359644 00356224  38 00 00 0E */	li r0, 0xe
/* 80359648 00356228  57 A7 84 3E */	srwi r7, r29, 0x10
/* 8035964C 0035622C  B0 03 00 00 */	sth r0, 0(r3)
/* 80359650 00356230  57 C6 84 3E */	srwi r6, r30, 0x10
/* 80359654 00356234  38 00 00 0F */	li r0, 0xf
/* 80359658 00356238  80 6D BE 8C */	lwz r3, __AXClWrite@sda21(r13)
/* 8035965C 0035623C  38 80 03 00 */	li r4, 0x300
/* 80359660 00356240  38 63 00 02 */	addi r3, r3, 2
/* 80359664 00356244  90 6D BE 8C */	stw r3, __AXClWrite@sda21(r13)
/* 80359668 00356248  38 7F 00 00 */	addi r3, r31, 0
/* 8035966C 0035624C  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 80359670 00356250  B0 E5 00 00 */	sth r7, 0(r5)
/* 80359674 00356254  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 80359678 00356258  38 A5 00 02 */	addi r5, r5, 2
/* 8035967C 0035625C  90 AD BE 8C */	stw r5, __AXClWrite@sda21(r13)
/* 80359680 00356260  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 80359684 00356264  B3 A5 00 00 */	sth r29, 0(r5)
/* 80359688 00356268  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 8035968C 0035626C  38 A5 00 02 */	addi r5, r5, 2
/* 80359690 00356270  90 AD BE 8C */	stw r5, __AXClWrite@sda21(r13)
/* 80359694 00356274  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 80359698 00356278  B0 C5 00 00 */	sth r6, 0(r5)
/* 8035969C 0035627C  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 803596A0 00356280  38 A5 00 02 */	addi r5, r5, 2
/* 803596A4 00356284  90 AD BE 8C */	stw r5, __AXClWrite@sda21(r13)
/* 803596A8 00356288  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 803596AC 0035628C  B3 C5 00 00 */	sth r30, 0(r5)
/* 803596B0 00356290  80 CD BE 8C */	lwz r6, __AXClWrite@sda21(r13)
/* 803596B4 00356294  80 AD BE 90 */	lwz r5, __AXCommandListCycles@sda21(r13)
/* 803596B8 00356298  38 C6 00 02 */	addi r6, r6, 2
/* 803596BC 0035629C  90 CD BE 8C */	stw r6, __AXClWrite@sda21(r13)
/* 803596C0 003562A0  38 A5 27 10 */	addi r5, r5, 0x2710
/* 803596C4 003562A4  90 AD BE 90 */	stw r5, __AXCommandListCycles@sda21(r13)
/* 803596C8 003562A8  80 AD BE 8C */	lwz r5, __AXClWrite@sda21(r13)
/* 803596CC 003562AC  B0 05 00 00 */	sth r0, 0(r5)
/* 803596D0 003562B0  80 CD BE 8C */	lwz r6, __AXClWrite@sda21(r13)
/* 803596D4 003562B4  80 AD BE 90 */	lwz r5, __AXCommandListCycles@sda21(r13)
/* 803596D8 003562B8  38 C6 00 02 */	addi r6, r6, 2
/* 803596DC 003562BC  38 05 00 02 */	addi r0, r5, 2
/* 803596E0 003562C0  90 CD BE 8C */	stw r6, __AXClWrite@sda21(r13)
/* 803596E4 003562C4  90 0D BE 90 */	stw r0, __AXCommandListCycles@sda21(r13)
/* 803596E8 003562C8  4B FE B1 25 */	bl DCFlushRange
/* 803596EC 003562CC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 803596F0 003562D0  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 803596F4 003562D4  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 803596F8 003562D8  7C 08 03 A6 */	mtlr r0
/* 803596FC 003562DC  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80359700 003562E0  38 21 00 40 */	addi r1, r1, 0x40
/* 80359704 003562E4  4E 80 00 20 */	blr

.global __AXClInit
__AXClInit:
/* 80359708 003562E8  3C 60 80 4B */	lis r3, __AXCommandList@ha
/* 8035970C 003562EC  38 80 00 00 */	li r4, 0
/* 80359710 003562F0  38 03 BB 80 */	addi r0, r3, __AXCommandList@l
/* 80359714 003562F4  90 8D BE 94 */	stw r4, __AXClMode@sda21(r13)
/* 80359718 003562F8  90 8D BE 88 */	stw r4, __AXCommandListPosition@sda21(r13)
/* 8035971C 003562FC  90 0D BE 8C */	stw r0, __AXClWrite@sda21(r13)
/* 80359720 00356300  4E 80 00 20 */	blr


.section .bss, "wa"
    .balign 8

    .balign 32
.global __AXCommandList
__AXCommandList:
    .skip 0x600


.section .sbss
    .balign 8
.global __AXCommandListPosition
__AXCommandListPosition:
    .skip 0x4
.global __AXClWrite
__AXClWrite:
    .skip 0x4
.global __AXCommandListCycles
__AXCommandListCycles:
    .skip 0x4
.global __AXClMode
__AXClMode:
    .skip 0x4
