.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global exit
exit:
/* 80322F9C 0031FB7C  7C 08 02 A6 */	mflr r0
/* 80322FA0 0031FB80  90 01 00 04 */	stw r0, 4(r1)
/* 80322FA4 0031FB84  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80322FA8 0031FB88  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80322FAC 0031FB8C  80 0D B9 C0 */	lwz r0, lbl_804D7060@sda21(r13)
/* 80322FB0 0031FB90  2C 00 00 00 */	cmpwi r0, 0
/* 80322FB4 0031FB94  40 82 00 84 */	bne lbl_80323038
/* 80322FB8 0031FB98  3C 60 80 4A */	lis r3, lbl_804A2F48@ha
/* 80322FBC 0031FB9C  3B E3 2F 48 */	addi r31, r3, lbl_804A2F48@l
/* 80322FC0 0031FBA0  48 00 00 24 */	b lbl_80322FE4
lbl_80322FC4:
/* 80322FC4 0031FBA4  80 6D B9 C4 */	lwz r3, lbl_804D7064@sda21(r13)
/* 80322FC8 0031FBA8  38 63 FF FF */	addi r3, r3, -1
/* 80322FCC 0031FBAC  54 60 10 3A */	slwi r0, r3, 2
/* 80322FD0 0031FBB0  90 6D B9 C4 */	stw r3, lbl_804D7064@sda21(r13)
/* 80322FD4 0031FBB4  7C 7F 02 14 */	add r3, r31, r0
/* 80322FD8 0031FBB8  81 83 00 00 */	lwz r12, 0(r3)
/* 80322FDC 0031FBBC  7D 88 03 A6 */	mtlr r12
/* 80322FE0 0031FBC0  4E 80 00 21 */	blrl 
lbl_80322FE4:
/* 80322FE4 0031FBC4  80 0D B9 C4 */	lwz r0, lbl_804D7064@sda21(r13)
/* 80322FE8 0031FBC8  2C 00 00 00 */	cmpwi r0, 0
/* 80322FEC 0031FBCC  41 81 FF D8 */	bgt lbl_80322FC4
/* 80322FF0 0031FBD0  4B FF F7 25 */	bl __destroy_global_chain
/* 80322FF4 0031FBD4  3C 60 80 3B */	lis r3, lbl_803B7260@ha
/* 80322FF8 0031FBD8  38 03 72 60 */	addi r0, r3, lbl_803B7260@l
/* 80322FFC 0031FBDC  7C 1F 03 78 */	mr r31, r0
/* 80323000 0031FBE0  48 00 00 10 */	b lbl_80323010
lbl_80323004:
/* 80323004 0031FBE4  7D 88 03 A6 */	mtlr r12
/* 80323008 0031FBE8  4E 80 00 21 */	blrl 
/* 8032300C 0031FBEC  3B FF 00 04 */	addi r31, r31, 4
lbl_80323010:
/* 80323010 0031FBF0  81 9F 00 00 */	lwz r12, 0(r31)
/* 80323014 0031FBF4  28 0C 00 00 */	cmplwi r12, 0
/* 80323018 0031FBF8  40 82 FF EC */	bne lbl_80323004
/* 8032301C 0031FBFC  81 8D B9 CC */	lwz r12, lbl_804D706C@sda21(r13)
/* 80323020 0031FC00  28 0C 00 00 */	cmplwi r12, 0
/* 80323024 0031FC04  41 82 00 14 */	beq lbl_80323038
/* 80323028 0031FC08  7D 88 03 A6 */	mtlr r12
/* 8032302C 0031FC0C  4E 80 00 21 */	blrl 
/* 80323030 0031FC10  38 00 00 00 */	li r0, 0
/* 80323034 0031FC14  90 0D B9 CC */	stw r0, lbl_804D706C@sda21(r13)
lbl_80323038:
/* 80323038 0031FC18  3C 60 80 4A */	lis r3, lbl_804A3048@ha
/* 8032303C 0031FC1C  3B E3 30 48 */	addi r31, r3, lbl_804A3048@l
/* 80323040 0031FC20  48 00 00 24 */	b lbl_80323064
lbl_80323044:
/* 80323044 0031FC24  80 6D B9 C8 */	lwz r3, lbl_804D7068@sda21(r13)
/* 80323048 0031FC28  38 63 FF FF */	addi r3, r3, -1
/* 8032304C 0031FC2C  54 60 10 3A */	slwi r0, r3, 2
/* 80323050 0031FC30  90 6D B9 C8 */	stw r3, lbl_804D7068@sda21(r13)
/* 80323054 0031FC34  7C 7F 02 14 */	add r3, r31, r0
/* 80323058 0031FC38  81 83 00 00 */	lwz r12, 0(r3)
/* 8032305C 0031FC3C  7D 88 03 A6 */	mtlr r12
/* 80323060 0031FC40  4E 80 00 21 */	blrl 
lbl_80323064:
/* 80323064 0031FC44  80 0D B9 C8 */	lwz r0, lbl_804D7068@sda21(r13)
/* 80323068 0031FC48  2C 00 00 00 */	cmpwi r0, 0
/* 8032306C 0031FC4C  41 81 FF D8 */	bgt lbl_80323044
/* 80323070 0031FC50  48 00 04 ED */	bl __kill_critical_regions
/* 80323074 0031FC54  81 8D B9 D0 */	lwz r12, lbl_804D7070@sda21(r13)
/* 80323078 0031FC58  28 0C 00 00 */	cmplwi r12, 0
/* 8032307C 0031FC5C  41 82 00 14 */	beq lbl_80323090
/* 80323080 0031FC60  7D 88 03 A6 */	mtlr r12
/* 80323084 0031FC64  4E 80 00 21 */	blrl 
/* 80323088 0031FC68  38 00 00 00 */	li r0, 0
/* 8032308C 0031FC6C  90 0D B9 D0 */	stw r0, lbl_804D7070@sda21(r13)
lbl_80323090:
/* 80323090 0031FC70  48 02 9A A1 */	bl _ExitProcess
/* 80323094 0031FC74  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80323098 0031FC78  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8032309C 0031FC7C  38 21 00 18 */	addi r1, r1, 0x18
/* 803230A0 0031FC80  7C 08 03 A6 */	mtlr r0
/* 803230A4 0031FC84  4E 80 00 20 */	blr 

.section .dtors, "wa"  # 0x803B7260 - 0x803B7280

.global lbl_803B7260
lbl_803B7260:
	.4byte __destroy_global_chain
    .4byte __fini_cpp_exceptions
    .4byte __destroy_global_chain
    .4byte NULL


.section .bss, "wa"

.global lbl_804A2F48
lbl_804A2F48:
	.skip 0x100
.global lbl_804A3048
lbl_804A3048:
	.skip 0x100


.section .sbss

.global lbl_804D7060
lbl_804D7060:
	.skip 0x4
.global lbl_804D7064
lbl_804D7064:
	.skip 0x4
.global lbl_804D7068
lbl_804D7068:
	.skip 0x4
.global lbl_804D706C
lbl_804D706C:
	.skip 0x4
.global lbl_804D7070
lbl_804D7070:
	.skip 0x8
