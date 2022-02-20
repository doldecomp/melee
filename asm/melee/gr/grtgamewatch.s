.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80224110
func_80224110:
/* 80224110 00220CF0  4E 80 00 20 */	blr 
.global lbl_80224114
lbl_80224114:
/* 80224114 00220CF4  7C 08 02 A6 */	mflr r0
/* 80224118 00220CF8  3C 60 80 4A */	lis r3, stage_info@ha
/* 8022411C 00220CFC  90 01 00 04 */	stw r0, 4(r1)
/* 80224120 00220D00  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 80224124 00220D04  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80224128 00220D08  94 21 FF F8 */	stwu r1, -8(r1)
/* 8022412C 00220D0C  38 80 00 01 */	li r4, 1
/* 80224130 00220D10  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80224134 00220D14  38 60 00 00 */	li r3, 0
/* 80224138 00220D18  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8022413C 00220D1C  98 05 00 00 */	stb r0, 0(r5)
/* 80224140 00220D20  38 60 00 00 */	li r3, 0
/* 80224144 00220D24  88 05 00 00 */	lbz r0, 0(r5)
/* 80224148 00220D28  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 8022414C 00220D2C  98 05 00 00 */	stb r0, 0(r5)
/* 80224150 00220D30  48 00 00 65 */	bl func_802241B4
/* 80224154 00220D34  38 60 00 01 */	li r3, 1
/* 80224158 00220D38  48 00 00 5D */	bl func_802241B4
/* 8022415C 00220D3C  38 60 00 02 */	li r3, 2
/* 80224160 00220D40  48 00 00 55 */	bl func_802241B4
/* 80224164 00220D44  4B F9 F8 5D */	bl func_801C39C0
/* 80224168 00220D48  4B F9 FA 4D */	bl func_801C3BB4
/* 8022416C 00220D4C  4B FA 00 A5 */	bl func_801C4210
/* 80224170 00220D50  4B FA 01 3D */	bl func_801C42AC
/* 80224174 00220D54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80224178 00220D58  38 21 00 08 */	addi r1, r1, 8
/* 8022417C 00220D5C  7C 08 03 A6 */	mtlr r0
/* 80224180 00220D60  4E 80 00 20 */	blr 
.global lbl_80224184
lbl_80224184:
/* 80224184 00220D64  4E 80 00 20 */	blr 
.global lbl_80224188
lbl_80224188:
/* 80224188 00220D68  7C 08 02 A6 */	mflr r0
/* 8022418C 00220D6C  38 60 00 00 */	li r3, 0
/* 80224190 00220D70  90 01 00 04 */	stw r0, 4(r1)
/* 80224194 00220D74  94 21 FF F8 */	stwu r1, -8(r1)
/* 80224198 00220D78  4B FA 6C 6D */	bl func_801CAE04
/* 8022419C 00220D7C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802241A0 00220D80  38 21 00 08 */	addi r1, r1, 8
/* 802241A4 00220D84  7C 08 03 A6 */	mtlr r0
/* 802241A8 00220D88  4E 80 00 20 */	blr 
.global lbl_802241AC
lbl_802241AC:
/* 802241AC 00220D8C  38 60 00 00 */	li r3, 0
/* 802241B0 00220D90  4E 80 00 20 */	blr 

.global func_802241B4
func_802241B4:
/* 802241B4 00220D94  7C 08 02 A6 */	mflr r0
/* 802241B8 00220D98  90 01 00 04 */	stw r0, 4(r1)
/* 802241BC 00220D9C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802241C0 00220DA0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802241C4 00220DA4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802241C8 00220DA8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 802241CC 00220DAC  93 81 00 10 */	stw r28, 0x10(r1)
/* 802241D0 00220DB0  3B 83 00 00 */	addi r28, r3, 0
/* 802241D4 00220DB4  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 802241D8 00220DB8  3C 60 80 3F */	lis r3, lbl_803E96F8@ha
/* 802241DC 00220DBC  3B E3 96 F8 */	addi r31, r3, lbl_803E96F8@l
/* 802241E0 00220DC0  38 7C 00 00 */	addi r3, r28, 0
/* 802241E4 00220DC4  7F BF 02 14 */	add r29, r31, r0
/* 802241E8 00220DC8  4B F9 D2 E9 */	bl func_801C14D0
/* 802241EC 00220DCC  7C 7E 1B 79 */	or. r30, r3, r3
/* 802241F0 00220DD0  41 82 00 70 */	beq lbl_80224260
/* 802241F4 00220DD4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 802241F8 00220DD8  38 00 00 00 */	li r0, 0
/* 802241FC 00220DDC  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80224200 00220DE0  90 1F 00 08 */	stw r0, 8(r31)
/* 80224204 00220DE4  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80224208 00220DE8  38 7E 00 00 */	addi r3, r30, 0
/* 8022420C 00220DEC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80224210 00220DF0  38 A0 00 03 */	li r5, 3
/* 80224214 00220DF4  38 C0 00 00 */	li r6, 0
/* 80224218 00220DF8  48 16 C4 85 */	bl GObj_SetupGXLink
/* 8022421C 00220DFC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80224220 00220E00  28 00 00 00 */	cmplwi r0, 0
/* 80224224 00220E04  41 82 00 08 */	beq lbl_8022422C
/* 80224228 00220E08  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_8022422C:
/* 8022422C 00220E0C  81 9D 00 00 */	lwz r12, 0(r29)
/* 80224230 00220E10  28 0C 00 00 */	cmplwi r12, 0
/* 80224234 00220E14  41 82 00 10 */	beq lbl_80224244
/* 80224238 00220E18  7D 88 03 A6 */	mtlr r12
/* 8022423C 00220E1C  38 7E 00 00 */	addi r3, r30, 0
/* 80224240 00220E20  4E 80 00 21 */	blrl 
lbl_80224244:
/* 80224244 00220E24  80 9D 00 08 */	lwz r4, 8(r29)
/* 80224248 00220E28  28 04 00 00 */	cmplwi r4, 0
/* 8022424C 00220E2C  41 82 00 2C */	beq lbl_80224278
/* 80224250 00220E30  38 7E 00 00 */	addi r3, r30, 0
/* 80224254 00220E34  38 A0 00 04 */	li r5, 4
/* 80224258 00220E38  48 16 BA FD */	bl func_8038FD54
/* 8022425C 00220E3C  48 00 00 1C */	b lbl_80224278
lbl_80224260:
/* 80224260 00220E40  38 DC 00 00 */	addi r6, r28, 0
/* 80224264 00220E44  4C C6 31 82 */	crclr 6
/* 80224268 00220E48  38 7F 00 90 */	addi r3, r31, 0x90
/* 8022426C 00220E4C  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80224270 00220E50  38 A0 00 C3 */	li r5, 0xc3
/* 80224274 00220E54  48 12 14 35 */	bl OSReport
lbl_80224278:
/* 80224278 00220E58  7F C3 F3 78 */	mr r3, r30
/* 8022427C 00220E5C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224280 00220E60  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224284 00220E64  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80224288 00220E68  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8022428C 00220E6C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80224290 00220E70  38 21 00 20 */	addi r1, r1, 0x20
/* 80224294 00220E74  7C 08 03 A6 */	mtlr r0
/* 80224298 00220E78  4E 80 00 20 */	blr 
.global lbl_8022429C
lbl_8022429C:
/* 8022429C 00220E7C  7C 08 02 A6 */	mflr r0
/* 802242A0 00220E80  38 A0 00 00 */	li r5, 0
/* 802242A4 00220E84  90 01 00 04 */	stw r0, 4(r1)
/* 802242A8 00220E88  94 21 FF F8 */	stwu r1, -8(r1)
/* 802242AC 00220E8C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802242B0 00220E90  80 84 00 14 */	lwz r4, 0x14(r4)
/* 802242B4 00220E94  4B FA 3E 85 */	bl func_801C8138
/* 802242B8 00220E98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802242BC 00220E9C  38 21 00 08 */	addi r1, r1, 8
/* 802242C0 00220EA0  7C 08 03 A6 */	mtlr r0
/* 802242C4 00220EA4  4E 80 00 20 */	blr 
.global lbl_802242C8
lbl_802242C8:
/* 802242C8 00220EA8  38 60 00 00 */	li r3, 0
/* 802242CC 00220EAC  4E 80 00 20 */	blr 
.global lbl_802242D0
lbl_802242D0:
/* 802242D0 00220EB0  4E 80 00 20 */	blr 
.global lbl_802242D4
lbl_802242D4:
/* 802242D4 00220EB4  4E 80 00 20 */	blr 
.global lbl_802242D8
lbl_802242D8:
/* 802242D8 00220EB8  7C 08 02 A6 */	mflr r0
/* 802242DC 00220EBC  90 01 00 04 */	stw r0, 4(r1)
/* 802242E0 00220EC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802242E4 00220EC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802242E8 00220EC8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802242EC 00220ECC  7C 7E 1B 78 */	mr r30, r3
/* 802242F0 00220ED0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802242F4 00220ED4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802242F8 00220ED8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802242FC 00220EDC  4B F9 EB D5 */	bl func_801C2ED0
/* 80224300 00220EE0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224304 00220EE4  38 7E 00 00 */	addi r3, r30, 0
/* 80224308 00220EE8  38 A0 00 00 */	li r5, 0
/* 8022430C 00220EEC  4B FA 3E 2D */	bl func_801C8138
/* 80224310 00220EF0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80224314 00220EF4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80224318 00220EF8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8022431C 00220EFC  38 21 00 20 */	addi r1, r1, 0x20
/* 80224320 00220F00  7C 08 03 A6 */	mtlr r0
/* 80224324 00220F04  4E 80 00 20 */	blr 
.global lbl_80224328
lbl_80224328:
/* 80224328 00220F08  38 60 00 00 */	li r3, 0
/* 8022432C 00220F0C  4E 80 00 20 */	blr 
.global lbl_80224330
lbl_80224330:
/* 80224330 00220F10  7C 08 02 A6 */	mflr r0
/* 80224334 00220F14  90 01 00 04 */	stw r0, 4(r1)
/* 80224338 00220F18  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8022433C 00220F1C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80224340 00220F20  7C 7F 1B 78 */	mr r31, r3
/* 80224344 00220F24  4B DE D2 B1 */	bl func_800115F4
/* 80224348 00220F28  7F E3 FB 78 */	mr r3, r31
/* 8022434C 00220F2C  4B F9 EC 95 */	bl func_801C2FE0
/* 80224350 00220F30  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80224354 00220F34  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80224358 00220F38  38 21 00 18 */	addi r1, r1, 0x18
/* 8022435C 00220F3C  7C 08 03 A6 */	mtlr r0
/* 80224360 00220F40  4E 80 00 20 */	blr 
.global lbl_80224364
lbl_80224364:
/* 80224364 00220F44  4E 80 00 20 */	blr 
.global lbl_80224368
lbl_80224368:
/* 80224368 00220F48  7C 08 02 A6 */	mflr r0
/* 8022436C 00220F4C  90 01 00 04 */	stw r0, 4(r1)
/* 80224370 00220F50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80224374 00220F54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80224378 00220F58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8022437C 00220F5C  7C 7E 1B 78 */	mr r30, r3
/* 80224380 00220F60  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80224384 00220F64  80 63 00 28 */	lwz r3, 0x28(r3)
/* 80224388 00220F68  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 8022438C 00220F6C  4B F9 EB 45 */	bl func_801C2ED0
/* 80224390 00220F70  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80224394 00220F74  38 7E 00 00 */	addi r3, r30, 0
/* 80224398 00220F78  38 A0 00 00 */	li r5, 0
/* 8022439C 00220F7C  4B FA 3D 9D */	bl func_801C8138
/* 802243A0 00220F80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802243A4 00220F84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802243A8 00220F88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802243AC 00220F8C  38 21 00 20 */	addi r1, r1, 0x20
/* 802243B0 00220F90  7C 08 03 A6 */	mtlr r0
/* 802243B4 00220F94  4E 80 00 20 */	blr 
.global lbl_802243B8
lbl_802243B8:
/* 802243B8 00220F98  38 60 00 00 */	li r3, 0
/* 802243BC 00220F9C  4E 80 00 20 */	blr 
.global lbl_802243C0
lbl_802243C0:
/* 802243C0 00220FA0  7C 08 02 A6 */	mflr r0
/* 802243C4 00220FA4  90 01 00 04 */	stw r0, 4(r1)
/* 802243C8 00220FA8  94 21 FF F8 */	stwu r1, -8(r1)
/* 802243CC 00220FAC  4B F9 EC 15 */	bl func_801C2FE0
/* 802243D0 00220FB0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802243D4 00220FB4  38 21 00 08 */	addi r1, r1, 8
/* 802243D8 00220FB8  7C 08 03 A6 */	mtlr r0
/* 802243DC 00220FBC  4E 80 00 20 */	blr 
.global lbl_802243E0
lbl_802243E0:
/* 802243E0 00220FC0  4E 80 00 20 */	blr 
.global lbl_802243E4
lbl_802243E4:
/* 802243E4 00220FC4  38 60 00 00 */	li r3, 0
/* 802243E8 00220FC8  4E 80 00 20 */	blr 
.global lbl_802243EC
lbl_802243EC:
/* 802243EC 00220FCC  38 60 00 01 */	li r3, 1
/* 802243F0 00220FD0  4E 80 00 20 */	blr 


.section .data
    .balign 8
.global lbl_803E96F8
lbl_803E96F8:
	.4byte lbl_8022429C
	.4byte lbl_802242C8
	.4byte lbl_802242D0
	.4byte lbl_802242D4
    .4byte NULL
	.4byte lbl_80224368
	.4byte lbl_802243B8
	.4byte lbl_802243C0
	.4byte lbl_802243E0
    .4byte NULL
	.4byte lbl_802242D8
	.4byte lbl_80224328
	.4byte lbl_80224330
	.4byte lbl_80224364
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9748
lbl_803E9748:
    .4byte 0x2F477254
    .4byte 0x47772E64
    .4byte 0x61740000
.global lbl_803E9754
lbl_803E9754:
    .4byte 0x0000003F
    .4byte lbl_803E96F8
    .4byte lbl_803E9748
	.4byte lbl_80224114
	.4byte func_80224110
	.4byte lbl_80224184
	.4byte lbl_80224188
	.4byte lbl_802241AC
	.4byte lbl_802243E4
	.4byte lbl_802243EC
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte 0x25733A25
    .4byte 0x643A2063
    .4byte 0x6F756C64
    .4byte 0x6E207420
    .4byte 0x67657420
    .4byte 0x676F626A
    .4byte 0x2869643D
    .4byte 0x2564290A
    .4byte NULL
    .4byte 0x67727467
    .4byte 0x616D6577
    .4byte 0x61746368
    .4byte 0x2E630000
    .4byte NULL
