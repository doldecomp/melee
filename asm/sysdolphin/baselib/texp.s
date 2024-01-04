.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global HSD_TExpSetReg
HSD_TExpSetReg:
/* 80384F28 00381B08  7C 08 02 A6 */	mflr r0
/* 80384F2C 00381B0C  3C 80 80 40 */	lis r4, HSD_TExp_80407738@ha
/* 80384F30 00381B10  90 01 00 04 */	stw r0, 4(r1)
/* 80384F34 00381B14  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80384F38 00381B18  DB E1 00 78 */	stfd f31, 0x78(r1)
/* 80384F3C 00381B1C  DB C1 00 70 */	stfd f30, 0x70(r1)
/* 80384F40 00381B20  BF 21 00 54 */	stmw r25, 0x54(r1)
/* 80384F44 00381B24  3B A3 00 00 */	addi r29, r3, 0
/* 80384F48 00381B28  3B 84 77 38 */	addi r28, r4, HSD_TExp_80407738@l
/* 80384F4C 00381B2C  3B E1 00 18 */	addi r31, r1, 0x18
/* 80384F50 00381B30  3B C0 00 00 */	li r30, 0
/* 80384F54 00381B34  CB E2 EE 00 */	lfd f31, HSD_TExp_804DE7E0@sda21(r2)
/* 80384F58 00381B38  C3 C2 ED F8 */	lfs f30, HSD_TExp_804DE7D8@sda21(r2)
/* 80384F5C 00381B3C  48 00 04 10 */	b .L_8038536C
.L_80384F60:
/* 80384F60 00381B40  80 1D 00 00 */	lwz r0, 0(r29)
/* 80384F64 00381B44  2C 00 00 04 */	cmpwi r0, 4
/* 80384F68 00381B48  41 82 00 14 */	beq .L_80384F7C
/* 80384F6C 00381B4C  38 BC 03 4C */	addi r5, r28, 0x34c
/* 80384F70 00381B50  38 6D A9 28 */	addi r3, r13, HSD_TExp_804D5FC8@sda21
/* 80384F74 00381B54  38 80 05 91 */	li r4, 0x591
/* 80384F78 00381B58  48 00 32 A9 */	bl __assert
.L_80384F7C:
/* 80384F7C 00381B5C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80384F80 00381B60  28 00 00 08 */	cmplwi r0, 8
/* 80384F84 00381B64  40 80 03 E4 */	bge .L_80385368
/* 80384F88 00381B68  80 7D 00 0C */	lwz r3, 0xc(r29)
/* 80384F8C 00381B6C  38 80 00 01 */	li r4, 1
/* 80384F90 00381B70  7C 84 00 30 */	slw r4, r4, r0
/* 80384F94 00381B74  2C 03 00 01 */	cmpwi r3, 1
/* 80384F98 00381B78  7F DE 23 78 */	or r30, r30, r4
/* 80384F9C 00381B7C  40 82 02 08 */	bne .L_803851A4
/* 80384FA0 00381B80  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 80384FA4 00381B84  2C 03 00 01 */	cmpwi r3, 1
/* 80384FA8 00381B88  41 82 00 B8 */	beq .L_80385060
/* 80384FAC 00381B8C  40 80 00 10 */	bge .L_80384FBC
/* 80384FB0 00381B90  2C 03 00 00 */	cmpwi r3, 0
/* 80384FB4 00381B94  40 80 00 14 */	bge .L_80384FC8
/* 80384FB8 00381B98  48 00 00 A8 */	b .L_80385060
.L_80384FBC:
/* 80384FBC 00381B9C  2C 03 00 03 */	cmpwi r3, 3
/* 80384FC0 00381BA0  40 80 00 A0 */	bge .L_80385060
/* 80384FC4 00381BA4  48 00 00 30 */	b .L_80384FF4
.L_80384FC8:
/* 80384FC8 00381BA8  80 7D 00 08 */	lwz r3, 8(r29)
/* 80384FCC 00381BAC  54 00 10 3A */	slwi r0, r0, 2
/* 80384FD0 00381BB0  38 81 00 18 */	addi r4, r1, 0x18
/* 80384FD4 00381BB4  80 63 00 00 */	lwz r3, 0(r3)
/* 80384FD8 00381BB8  7C 84 02 14 */	add r4, r4, r0
/* 80384FDC 00381BBC  90 61 00 14 */	stw r3, 0x14(r1)
/* 80384FE0 00381BC0  88 04 00 03 */	lbz r0, 3(r4)
/* 80384FE4 00381BC4  98 01 00 17 */	stb r0, 0x17(r1)
/* 80384FE8 00381BC8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80384FEC 00381BCC  90 04 00 00 */	stw r0, 0(r4)
/* 80384FF0 00381BD0  48 00 03 78 */	b .L_80385368
.L_80384FF4:
/* 80384FF4 00381BD4  80 9D 00 08 */	lwz r4, 8(r29)
/* 80384FF8 00381BD8  80 64 00 00 */	lwz r3, 0(r4)
/* 80384FFC 00381BDC  28 03 01 00 */	cmplwi r3, 0x100
/* 80385000 00381BE0  40 80 00 08 */	bge .L_80385008
/* 80385004 00381BE4  48 00 00 08 */	b .L_8038500C
.L_80385008:
/* 80385008 00381BE8  38 60 00 FF */	li r3, 0xff
.L_8038500C:
/* 8038500C 00381BEC  54 00 10 3A */	slwi r0, r0, 2
/* 80385010 00381BF0  7C 7F 01 AE */	stbx r3, r31, r0
/* 80385014 00381BF4  80 A4 00 04 */	lwz r5, 4(r4)
/* 80385018 00381BF8  28 05 01 00 */	cmplwi r5, 0x100
/* 8038501C 00381BFC  40 80 00 08 */	bge .L_80385024
/* 80385020 00381C00  48 00 00 08 */	b .L_80385028
.L_80385024:
/* 80385024 00381C04  38 A0 00 FF */	li r5, 0xff
.L_80385028:
/* 80385028 00381C08  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038502C 00381C0C  54 03 10 3A */	slwi r3, r0, 2
/* 80385030 00381C10  38 03 00 01 */	addi r0, r3, 1
/* 80385034 00381C14  7C BF 01 AE */	stbx r5, r31, r0
/* 80385038 00381C18  80 84 00 08 */	lwz r4, 8(r4)
/* 8038503C 00381C1C  28 04 01 00 */	cmplwi r4, 0x100
/* 80385040 00381C20  40 80 00 08 */	bge .L_80385048
/* 80385044 00381C24  48 00 00 08 */	b .L_8038504C
.L_80385048:
/* 80385048 00381C28  38 80 00 FF */	li r4, 0xff
.L_8038504C:
/* 8038504C 00381C2C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385050 00381C30  54 03 10 3A */	slwi r3, r0, 2
/* 80385054 00381C34  38 03 00 02 */	addi r0, r3, 2
/* 80385058 00381C38  7C 9F 01 AE */	stbx r4, r31, r0
/* 8038505C 00381C3C  48 00 03 0C */	b .L_80385368
.L_80385060:
/* 80385060 00381C40  2C 03 00 02 */	cmpwi r3, 2
/* 80385064 00381C44  41 82 00 78 */	beq .L_803850DC
/* 80385068 00381C48  40 80 00 10 */	bge .L_80385078
/* 8038506C 00381C4C  2C 03 00 01 */	cmpwi r3, 1
/* 80385070 00381C50  40 80 00 14 */	bge .L_80385084
/* 80385074 00381C54  48 00 00 68 */	b .L_803850DC
.L_80385078:
/* 80385078 00381C58  2C 03 00 04 */	cmpwi r3, 4
/* 8038507C 00381C5C  40 80 00 60 */	bge .L_803850DC
/* 80385080 00381C60  48 00 00 18 */	b .L_80385098
.L_80385084:
/* 80385084 00381C64  80 BD 00 08 */	lwz r5, 8(r29)
/* 80385088 00381C68  A0 65 00 00 */	lhz r3, 0(r5)
/* 8038508C 00381C6C  A0 85 00 02 */	lhz r4, 2(r5)
/* 80385090 00381C70  A0 A5 00 04 */	lhz r5, 4(r5)
/* 80385094 00381C74  48 00 00 88 */	b .L_8038511C
.L_80385098:
/* 80385098 00381C78  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038509C 00381C7C  C0 43 00 00 */	lfs f2, 0(r3)
/* 803850A0 00381C80  C0 23 00 04 */	lfs f1, 4(r3)
/* 803850A4 00381C84  C0 03 00 08 */	lfs f0, 8(r3)
/* 803850A8 00381C88  EC 5E 00 B2 */	fmuls f2, f30, f2
/* 803850AC 00381C8C  EC 3E 00 72 */	fmuls f1, f30, f1
/* 803850B0 00381C90  EC 1E 00 32 */	fmuls f0, f30, f0
/* 803850B4 00381C94  FC 40 10 1E */	fctiwz f2, f2
/* 803850B8 00381C98  FC 20 08 1E */	fctiwz f1, f1
/* 803850BC 00381C9C  FC 00 00 1E */	fctiwz f0, f0
/* 803850C0 00381CA0  D8 41 00 48 */	stfd f2, 0x48(r1)
/* 803850C4 00381CA4  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 803850C8 00381CA8  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 803850CC 00381CAC  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 803850D0 00381CB0  80 81 00 44 */	lwz r4, 0x44(r1)
/* 803850D4 00381CB4  80 A1 00 3C */	lwz r5, 0x3c(r1)
/* 803850D8 00381CB8  48 00 00 44 */	b .L_8038511C
.L_803850DC:
/* 803850DC 00381CBC  80 7D 00 08 */	lwz r3, 8(r29)
/* 803850E0 00381CC0  C8 43 00 00 */	lfd f2, 0(r3)
/* 803850E4 00381CC4  C8 23 00 08 */	lfd f1, 8(r3)
/* 803850E8 00381CC8  C8 03 00 10 */	lfd f0, 0x10(r3)
/* 803850EC 00381CCC  FC 5F 00 B2 */	fmul f2, f31, f2
/* 803850F0 00381CD0  FC 3F 00 72 */	fmul f1, f31, f1
/* 803850F4 00381CD4  FC 1F 00 32 */	fmul f0, f31, f0
/* 803850F8 00381CD8  FC 40 10 1E */	fctiwz f2, f2
/* 803850FC 00381CDC  FC 20 08 1E */	fctiwz f1, f1
/* 80385100 00381CE0  FC 00 00 1E */	fctiwz f0, f0
/* 80385104 00381CE4  D8 41 00 38 */	stfd f2, 0x38(r1)
/* 80385108 00381CE8  D8 21 00 40 */	stfd f1, 0x40(r1)
/* 8038510C 00381CEC  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 80385110 00381CF0  D8 01 00 48 */	stfd f0, 0x48(r1)
/* 80385114 00381CF4  80 81 00 44 */	lwz r4, 0x44(r1)
/* 80385118 00381CF8  80 A1 00 4C */	lwz r5, 0x4c(r1)
.L_8038511C:
/* 8038511C 00381CFC  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385120 00381D00  40 81 00 0C */	ble .L_8038512C
/* 80385124 00381D04  38 60 00 FF */	li r3, 0xff
/* 80385128 00381D08  48 00 00 10 */	b .L_80385138
.L_8038512C:
/* 8038512C 00381D0C  2C 03 00 00 */	cmpwi r3, 0
/* 80385130 00381D10  40 80 00 08 */	bge .L_80385138
/* 80385134 00381D14  38 60 00 00 */	li r3, 0
.L_80385138:
/* 80385138 00381D18  54 00 10 3A */	slwi r0, r0, 2
/* 8038513C 00381D1C  2C 04 00 FF */	cmpwi r4, 0xff
/* 80385140 00381D20  7C 7F 01 AE */	stbx r3, r31, r0
/* 80385144 00381D24  40 81 00 0C */	ble .L_80385150
/* 80385148 00381D28  38 80 00 FF */	li r4, 0xff
/* 8038514C 00381D2C  48 00 00 10 */	b .L_8038515C
.L_80385150:
/* 80385150 00381D30  2C 04 00 00 */	cmpwi r4, 0
/* 80385154 00381D34  40 80 00 08 */	bge .L_8038515C
/* 80385158 00381D38  38 80 00 00 */	li r4, 0
.L_8038515C:
/* 8038515C 00381D3C  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385160 00381D40  2C 05 00 FF */	cmpwi r5, 0xff
/* 80385164 00381D44  54 03 10 3A */	slwi r3, r0, 2
/* 80385168 00381D48  38 03 00 01 */	addi r0, r3, 1
/* 8038516C 00381D4C  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385170 00381D50  40 81 00 0C */	ble .L_8038517C
/* 80385174 00381D54  38 80 00 FF */	li r4, 0xff
/* 80385178 00381D58  48 00 00 18 */	b .L_80385190
.L_8038517C:
/* 8038517C 00381D5C  2C 05 00 00 */	cmpwi r5, 0
/* 80385180 00381D60  40 80 00 0C */	bge .L_8038518C
/* 80385184 00381D64  38 80 00 00 */	li r4, 0
/* 80385188 00381D68  48 00 00 08 */	b .L_80385190
.L_8038518C:
/* 8038518C 00381D6C  7C A4 2B 78 */	mr r4, r5
.L_80385190:
/* 80385190 00381D70  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 80385194 00381D74  54 03 10 3A */	slwi r3, r0, 2
/* 80385198 00381D78  38 03 00 02 */	addi r0, r3, 2
/* 8038519C 00381D7C  7C 9F 01 AE */	stbx r4, r31, r0
/* 803851A0 00381D80  48 00 01 C8 */	b .L_80385368
.L_803851A4:
/* 803851A4 00381D84  80 7D 00 10 */	lwz r3, 0x10(r29)
/* 803851A8 00381D88  2C 03 00 02 */	cmpwi r3, 2
/* 803851AC 00381D8C  41 82 00 5C */	beq .L_80385208
/* 803851B0 00381D90  40 80 00 14 */	bge .L_803851C4
/* 803851B4 00381D94  2C 03 00 00 */	cmpwi r3, 0
/* 803851B8 00381D98  41 82 00 18 */	beq .L_803851D0
/* 803851BC 00381D9C  40 80 00 20 */	bge .L_803851DC
/* 803851C0 00381DA0  48 00 00 B8 */	b .L_80385278
.L_803851C4:
/* 803851C4 00381DA4  2C 03 00 04 */	cmpwi r3, 4
/* 803851C8 00381DA8  40 80 00 B0 */	bge .L_80385278
/* 803851CC 00381DAC  48 00 00 68 */	b .L_80385234
.L_803851D0:
/* 803851D0 00381DB0  80 7D 00 08 */	lwz r3, 8(r29)
/* 803851D4 00381DB4  88 83 00 00 */	lbz r4, 0(r3)
/* 803851D8 00381DB8  48 00 00 E0 */	b .L_803852B8
.L_803851DC:
/* 803851DC 00381DBC  80 7D 00 08 */	lwz r3, 8(r29)
/* 803851E0 00381DC0  A0 63 00 00 */	lhz r3, 0(r3)
/* 803851E4 00381DC4  2C 03 00 FF */	cmpwi r3, 0xff
/* 803851E8 00381DC8  40 81 00 0C */	ble .L_803851F4
/* 803851EC 00381DCC  38 60 00 FF */	li r3, 0xff
/* 803851F0 00381DD0  48 00 00 10 */	b .L_80385200
.L_803851F4:
/* 803851F4 00381DD4  2C 03 00 00 */	cmpwi r3, 0
/* 803851F8 00381DD8  40 80 00 08 */	bge .L_80385200
/* 803851FC 00381DDC  38 60 00 00 */	li r3, 0
.L_80385200:
/* 80385200 00381DE0  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385204 00381DE4  48 00 00 B4 */	b .L_803852B8
.L_80385208:
/* 80385208 00381DE8  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038520C 00381DEC  80 63 00 00 */	lwz r3, 0(r3)
/* 80385210 00381DF0  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385214 00381DF4  40 81 00 0C */	ble .L_80385220
/* 80385218 00381DF8  38 60 00 FF */	li r3, 0xff
/* 8038521C 00381DFC  48 00 00 10 */	b .L_8038522C
.L_80385220:
/* 80385220 00381E00  2C 03 00 00 */	cmpwi r3, 0
/* 80385224 00381E04  40 80 00 08 */	bge .L_8038522C
/* 80385228 00381E08  38 60 00 00 */	li r3, 0
.L_8038522C:
/* 8038522C 00381E0C  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385230 00381E10  48 00 00 88 */	b .L_803852B8
.L_80385234:
/* 80385234 00381E14  80 7D 00 08 */	lwz r3, 8(r29)
/* 80385238 00381E18  C0 03 00 00 */	lfs f0, 0(r3)
/* 8038523C 00381E1C  EC 1E 00 32 */	fmuls f0, f30, f0
/* 80385240 00381E20  FC 00 00 1E */	fctiwz f0, f0
/* 80385244 00381E24  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80385248 00381E28  80 61 00 44 */	lwz r3, 0x44(r1)
/* 8038524C 00381E2C  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80385250 00381E30  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385254 00381E34  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 80385258 00381E38  40 81 00 0C */	ble .L_80385264
/* 8038525C 00381E3C  38 60 00 FF */	li r3, 0xff
/* 80385260 00381E40  48 00 00 10 */	b .L_80385270
.L_80385264:
/* 80385264 00381E44  2C 03 00 00 */	cmpwi r3, 0
/* 80385268 00381E48  40 80 00 08 */	bge .L_80385270
/* 8038526C 00381E4C  38 60 00 00 */	li r3, 0
.L_80385270:
/* 80385270 00381E50  54 64 06 3E */	clrlwi r4, r3, 0x18
/* 80385274 00381E54  48 00 00 44 */	b .L_803852B8
.L_80385278:
/* 80385278 00381E58  80 7D 00 08 */	lwz r3, 8(r29)
/* 8038527C 00381E5C  C8 03 00 00 */	lfd f0, 0(r3)
/* 80385280 00381E60  FC 1F 00 32 */	fmul f0, f31, f0
/* 80385284 00381E64  FC 00 00 1E */	fctiwz f0, f0
/* 80385288 00381E68  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 8038528C 00381E6C  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80385290 00381E70  D8 01 00 38 */	stfd f0, 0x38(r1)
/* 80385294 00381E74  2C 03 00 FF */	cmpwi r3, 0xff
/* 80385298 00381E78  80 61 00 3C */	lwz r3, 0x3c(r1)
/* 8038529C 00381E7C  40 81 00 0C */	ble .L_803852A8
/* 803852A0 00381E80  38 60 00 FF */	li r3, 0xff
/* 803852A4 00381E84  48 00 00 10 */	b .L_803852B4
.L_803852A8:
/* 803852A8 00381E88  2C 03 00 00 */	cmpwi r3, 0
/* 803852AC 00381E8C  40 80 00 08 */	bge .L_803852B4
/* 803852B0 00381E90  38 60 00 00 */	li r3, 0
.L_803852B4:
/* 803852B4 00381E94  54 64 06 3E */	clrlwi r4, r3, 0x18
.L_803852B8:
/* 803852B8 00381E98  28 00 00 04 */	cmplwi r0, 4
/* 803852BC 00381E9C  40 80 00 68 */	bge .L_80385324
/* 803852C0 00381EA0  88 7D 00 15 */	lbz r3, 0x15(r29)
/* 803852C4 00381EA4  2C 03 00 01 */	cmpwi r3, 1
/* 803852C8 00381EA8  41 82 00 2C */	beq .L_803852F4
/* 803852CC 00381EAC  40 80 00 10 */	bge .L_803852DC
/* 803852D0 00381EB0  2C 03 00 00 */	cmpwi r3, 0
/* 803852D4 00381EB4  40 80 00 14 */	bge .L_803852E8
/* 803852D8 00381EB8  48 00 00 3C */	b .L_80385314
.L_803852DC:
/* 803852DC 00381EBC  2C 03 00 03 */	cmpwi r3, 3
/* 803852E0 00381EC0  40 80 00 34 */	bge .L_80385314
/* 803852E4 00381EC4  48 00 00 20 */	b .L_80385304
.L_803852E8:
/* 803852E8 00381EC8  54 00 10 3A */	slwi r0, r0, 2
/* 803852EC 00381ECC  7C 9F 01 AE */	stbx r4, r31, r0
/* 803852F0 00381ED0  48 00 00 78 */	b .L_80385368
.L_803852F4:
/* 803852F4 00381ED4  54 03 10 3A */	slwi r3, r0, 2
/* 803852F8 00381ED8  38 03 00 01 */	addi r0, r3, 1
/* 803852FC 00381EDC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385300 00381EE0  48 00 00 68 */	b .L_80385368
.L_80385304:
/* 80385304 00381EE4  54 03 10 3A */	slwi r3, r0, 2
/* 80385308 00381EE8  38 03 00 02 */	addi r0, r3, 2
/* 8038530C 00381EEC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385310 00381EF0  48 00 00 58 */	b .L_80385368
.L_80385314:
/* 80385314 00381EF4  54 03 10 3A */	slwi r3, r0, 2
/* 80385318 00381EF8  38 03 00 03 */	addi r0, r3, 3
/* 8038531C 00381EFC  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385320 00381F00  48 00 00 48 */	b .L_80385368
.L_80385324:
/* 80385324 00381F04  88 7D 00 15 */	lbz r3, 0x15(r29)
/* 80385328 00381F08  28 03 00 03 */	cmplwi r3, 3
/* 8038532C 00381F0C  40 82 00 14 */	bne .L_80385340
/* 80385330 00381F10  54 03 10 3A */	slwi r3, r0, 2
/* 80385334 00381F14  38 03 00 03 */	addi r0, r3, 3
/* 80385338 00381F18  7C 9F 01 AE */	stbx r4, r31, r0
/* 8038533C 00381F1C  48 00 00 2C */	b .L_80385368
.L_80385340:
/* 80385340 00381F20  54 00 10 3A */	slwi r0, r0, 2
/* 80385344 00381F24  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385348 00381F28  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038534C 00381F2C  54 03 10 3A */	slwi r3, r0, 2
/* 80385350 00381F30  38 03 00 01 */	addi r0, r3, 1
/* 80385354 00381F34  7C 9F 01 AE */	stbx r4, r31, r0
/* 80385358 00381F38  88 1D 00 14 */	lbz r0, 0x14(r29)
/* 8038535C 00381F3C  54 03 10 3A */	slwi r3, r0, 2
/* 80385360 00381F40  38 03 00 02 */	addi r0, r3, 2
/* 80385364 00381F44  7C 9F 01 AE */	stbx r4, r31, r0
.L_80385368:
/* 80385368 00381F48  83 BD 00 04 */	lwz r29, 4(r29)
.L_8038536C:
/* 8038536C 00381F4C  28 1D 00 00 */	cmplwi r29, 0
/* 80385370 00381F50  40 82 FB F0 */	bne .L_80384F60
/* 80385374 00381F54  28 1E 00 00 */	cmplwi r30, 0
/* 80385378 00381F58  41 82 00 B4 */	beq .L_8038542C
/* 8038537C 00381F5C  4B FB 79 A1 */	bl GXPixModeSync
/* 80385380 00381F60  3B 20 00 00 */	li r25, 0
/* 80385384 00381F64  57 20 10 3A */	slwi r0, r25, 2
/* 80385388 00381F68  7F 5C 02 14 */	add r26, r28, r0
/* 8038538C 00381F6C  3B 61 00 18 */	addi r27, r1, 0x18
/* 80385390 00381F70  3B E1 00 10 */	addi r31, r1, 0x10
/* 80385394 00381F74  3B A0 00 01 */	li r29, 1
/* 80385398 00381F78  3B 5A 03 30 */	addi r26, r26, 0x330
.L_8038539C:
/* 8038539C 00381F7C  7F A0 C8 30 */	slw r0, r29, r25
/* 803853A0 00381F80  7F C0 00 39 */	and. r0, r30, r0
/* 803853A4 00381F84  41 82 00 18 */	beq .L_803853BC
/* 803853A8 00381F88  80 1B 00 00 */	lwz r0, 0(r27)
/* 803853AC 00381F8C  7F E4 FB 78 */	mr r4, r31
/* 803853B0 00381F90  90 01 00 10 */	stw r0, 0x10(r1)
/* 803853B4 00381F94  80 7A 00 00 */	lwz r3, 0(r26)
/* 803853B8 00381F98  4B FB AF 1D */	bl GXSetTevKColor
.L_803853BC:
/* 803853BC 00381F9C  3B 39 00 01 */	addi r25, r25, 1
/* 803853C0 00381FA0  2C 19 00 04 */	cmpwi r25, 4
/* 803853C4 00381FA4  3B 7B 00 04 */	addi r27, r27, 4
/* 803853C8 00381FA8  3B 5A 00 04 */	addi r26, r26, 4
/* 803853CC 00381FAC  41 80 FF D0 */	blt .L_8038539C
/* 803853D0 00381FB0  3B E0 00 04 */	li r31, 4
/* 803853D4 00381FB4  57 E0 10 3A */	slwi r0, r31, 2
/* 803853D8 00381FB8  7F 7C 02 14 */	add r27, r28, r0
/* 803853DC 00381FBC  3B 41 00 28 */	addi r26, r1, 0x28
/* 803853E0 00381FC0  3B A1 00 0C */	addi r29, r1, 0xc
/* 803853E4 00381FC4  3B 80 00 01 */	li r28, 1
/* 803853E8 00381FC8  3B 7B 03 40 */	addi r27, r27, 0x340
.L_803853EC:
/* 803853EC 00381FCC  7F 80 F8 30 */	slw r0, r28, r31
/* 803853F0 00381FD0  7F C0 00 39 */	and. r0, r30, r0
/* 803853F4 00381FD4  41 82 00 18 */	beq .L_8038540C
/* 803853F8 00381FD8  80 1A 00 00 */	lwz r0, 0(r26)
/* 803853FC 00381FDC  7F A4 EB 78 */	mr r4, r29
/* 80385400 00381FE0  90 01 00 0C */	stw r0, 0xc(r1)
/* 80385404 00381FE4  80 7B FF F0 */	lwz r3, -0x10(r27)
/* 80385408 00381FE8  4B FB AD E5 */	bl GXSetTevColor
.L_8038540C:
/* 8038540C 00381FEC  3B FF 00 01 */	addi r31, r31, 1
/* 80385410 00381FF0  2C 1F 00 07 */	cmpwi r31, 7
/* 80385414 00381FF4  3B 5A 00 04 */	addi r26, r26, 4
/* 80385418 00381FF8  3B 7B 00 04 */	addi r27, r27, 4
/* 8038541C 00381FFC  41 80 FF D0 */	blt .L_803853EC
/* 80385420 00382000  38 60 00 10 */	li r3, 0x10
/* 80385424 00382004  4B FD CB A1 */	bl HSD_StateInvalidate
/* 80385428 00382008  4B FB 78 F5 */	bl GXPixModeSync
.L_8038542C:
/* 8038542C 0038200C  BB 21 00 54 */	lmw r25, 0x54(r1)
/* 80385430 00382010  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80385434 00382014  CB E1 00 78 */	lfd f31, 0x78(r1)
/* 80385438 00382018  CB C1 00 70 */	lfd f30, 0x70(r1)
/* 8038543C 0038201C  38 21 00 80 */	addi r1, r1, 0x80
/* 80385440 00382020  7C 08 03 A6 */	mtlr r0
/* 80385444 00382024  4E 80 00 20 */	blr

.global HSD_TExpCompile
HSD_TExpCompile:
/* 803854B4 00382094  7C 08 02 A6 */	mflr r0
/* 803854B8 00382098  90 01 00 04 */	stw r0, 4(r1)
/* 803854BC 0038209C  38 00 00 01 */	li r0, 1
/* 803854C0 003820A0  94 21 FA 18 */	stwu r1, -0x5e8(r1)
/* 803854C4 003820A4  BF 21 05 CC */	stmw r25, 0x5cc(r1)
/* 803854C8 003820A8  7C 9E 23 79 */	or. r30, r4, r4
/* 803854CC 003820AC  7C 7D 1B 78 */	mr r29, r3
/* 803854D0 003820B0  7C BF 2B 78 */	mr r31, r5
/* 803854D4 003820B4  90 01 00 18 */	stw r0, 0x18(r1)
/* 803854D8 003820B8  90 01 00 14 */	stw r0, 0x14(r1)
/* 803854DC 003820BC  40 82 00 14 */	bne .L_803854F0
/* 803854E0 003820C0  38 6D A9 28 */	addi r3, r13, HSD_TExp_804D5FC8@sda21
/* 803854E4 003820C4  38 80 06 5B */	li r4, 0x65b
/* 803854E8 003820C8  38 AD A9 44 */	addi r5, r13, HSD_TExp_804D5FE4@sda21
/* 803854EC 003820CC  48 00 2D 35 */	bl __assert
.L_803854F0:
/* 803854F0 003820D0  28 1F 00 00 */	cmplwi r31, 0
/* 803854F4 003820D4  40 82 00 18 */	bne .L_8038550C
/* 803854F8 003820D8  3C 60 80 40 */	lis r3, HSD_TExp_80407738@ha
/* 803854FC 003820DC  38 A3 77 38 */	addi r5, r3, HSD_TExp_80407738@l
/* 80385500 003820E0  38 6D A9 28 */	addi r3, r13, HSD_TExp_804D5FC8@sda21
/* 80385504 003820E4  38 80 06 5C */	li r4, 0x65c
/* 80385508 003820E8  48 00 2D 19 */	bl __assert
.L_8038550C:
/* 8038550C 003820EC  38 61 05 9C */	addi r3, r1, 0x59c
/* 80385510 003820F0  38 80 00 00 */	li r4, 0
/* 80385514 003820F4  38 A0 00 2C */	li r5, 0x2c
/* 80385518 003820F8  4B C7 DB E9 */	bl memset
/* 8038551C 003820FC  28 1D 00 00 */	cmplwi r29, 0
/* 80385520 00382100  40 82 00 0C */	bne .L_8038552C
/* 80385524 00382104  38 00 00 00 */	li r0, 0
/* 80385528 00382108  48 00 00 2C */	b .L_80385554
.L_8038552C:
/* 8038552C 0038210C  3C 1D 00 01 */	addis r0, r29, 1
/* 80385530 00382110  28 00 FF FF */	cmplwi r0, 0xffff
/* 80385534 00382114  40 82 00 0C */	bne .L_80385540
/* 80385538 00382118  38 00 00 02 */	li r0, 2
/* 8038553C 0038211C  48 00 00 18 */	b .L_80385554
.L_80385540:
/* 80385540 00382120  28 00 FF FE */	cmplwi r0, 0xfffe
/* 80385544 00382124  40 82 00 0C */	bne .L_80385550
/* 80385548 00382128  38 00 00 03 */	li r0, 3
/* 8038554C 0038212C  48 00 00 08 */	b .L_80385554
.L_80385550:
/* 80385550 00382130  80 1D 00 00 */	lwz r0, 0(r29)
.L_80385554:
/* 80385554 00382134  2C 00 00 04 */	cmpwi r0, 4
/* 80385558 00382138  41 82 00 24 */	beq .L_8038557C
/* 8038555C 0038213C  40 80 00 2C */	bge .L_80385588
/* 80385560 00382140  2C 00 00 01 */	cmpwi r0, 1
/* 80385564 00382144  41 82 00 08 */	beq .L_8038556C
/* 80385568 00382148  48 00 00 20 */	b .L_80385588
.L_8038556C:
/* 8038556C 0038214C  80 7D 00 08 */	lwz r3, 8(r29)
/* 80385570 00382150  38 03 00 01 */	addi r0, r3, 1
/* 80385574 00382154  90 1D 00 08 */	stw r0, 8(r29)
/* 80385578 00382158  48 00 00 10 */	b .L_80385588
.L_8038557C:
/* 8038557C 0038215C  88 7D 00 16 */	lbz r3, 0x16(r29)
/* 80385580 00382160  38 03 00 01 */	addi r0, r3, 1
/* 80385584 00382164  98 1D 00 16 */	stb r0, 0x16(r29)
.L_80385588:
/* 80385588 00382168  28 1D 00 00 */	cmplwi r29, 0
/* 8038558C 0038216C  40 82 00 0C */	bne .L_80385598
/* 80385590 00382170  38 00 00 00 */	li r0, 0
/* 80385594 00382174  48 00 00 2C */	b .L_803855C0
.L_80385598:
/* 80385598 00382178  3C 1D 00 01 */	addis r0, r29, 1
/* 8038559C 0038217C  28 00 FF FF */	cmplwi r0, 0xffff
/* 803855A0 00382180  40 82 00 0C */	bne .L_803855AC
/* 803855A4 00382184  38 00 00 02 */	li r0, 2
/* 803855A8 00382188  48 00 00 18 */	b .L_803855C0
.L_803855AC:
/* 803855AC 0038218C  28 00 FF FE */	cmplwi r0, 0xfffe
/* 803855B0 00382190  40 82 00 0C */	bne .L_803855BC
/* 803855B4 00382194  38 00 00 03 */	li r0, 3
/* 803855B8 00382198  48 00 00 08 */	b .L_803855C0
.L_803855BC:
/* 803855BC 0038219C  80 1D 00 00 */	lwz r0, 0(r29)
.L_803855C0:
/* 803855C0 003821A0  2C 00 00 04 */	cmpwi r0, 4
/* 803855C4 003821A4  41 82 00 24 */	beq .L_803855E8
/* 803855C8 003821A8  40 80 00 2C */	bge .L_803855F4
/* 803855CC 003821AC  2C 00 00 01 */	cmpwi r0, 1
/* 803855D0 003821B0  41 82 00 08 */	beq .L_803855D8
/* 803855D4 003821B4  48 00 00 20 */	b .L_803855F4
.L_803855D8:
/* 803855D8 003821B8  80 7D 00 14 */	lwz r3, 0x14(r29)
/* 803855DC 003821BC  38 03 00 01 */	addi r0, r3, 1
/* 803855E0 003821C0  90 1D 00 14 */	stw r0, 0x14(r29)
/* 803855E4 003821C4  48 00 00 10 */	b .L_803855F4
.L_803855E8:
/* 803855E8 003821C8  88 7D 00 16 */	lbz r3, 0x16(r29)
/* 803855EC 003821CC  38 03 00 01 */	addi r0, r3, 1
/* 803855F0 003821D0  98 1D 00 16 */	stb r0, 0x16(r29)
.L_803855F4:
/* 803855F4 003821D4  7F A3 EB 78 */	mr r3, r29
/* 803855F8 003821D8  48 00 25 25 */	bl HSD_TExpSimplify
/* 803855FC 003821DC  38 7D 00 00 */	addi r3, r29, 0
/* 80385600 003821E0  38 81 00 1C */	addi r4, r1, 0x1c
/* 80385604 003821E4  48 00 06 5D */	bl HSD_TExpMakeDag
/* 80385608 003821E8  3B 43 00 00 */	addi r26, r3, 0
/* 8038560C 003821EC  38 81 00 1C */	addi r4, r1, 0x1c
/* 80385610 003821F0  38 A1 05 1C */	addi r5, r1, 0x51c
/* 80385614 003821F4  38 C1 05 9C */	addi r6, r1, 0x59c
/* 80385618 003821F8  48 00 0C 1D */	bl HSD_TExpSchedule
/* 8038561C 003821FC  3B 20 00 00 */	li r25, 0
/* 80385620 00382200  3C 60 80 40 */	lis r3, HSD_TExp_80407A14@ha
/* 80385624 00382204  57 20 10 3A */	slwi r0, r25, 2
/* 80385628 00382208  3B 61 05 1C */	addi r27, r1, 0x51c
/* 8038562C 0038220C  7F 7B 02 14 */	add r27, r27, r0
/* 80385630 00382210  3B 83 7A 14 */	addi r28, r3, HSD_TExp_80407A14@l
/* 80385634 00382214  48 00 00 30 */	b .L_80385664
.L_80385638:
/* 80385638 00382218  80 7B 00 00 */	lwz r3, 0(r27)
/* 8038563C 0038221C  38 81 05 9C */	addi r4, r1, 0x59c
/* 80385640 00382220  4B FF F0 81 */	bl TExpAssignReg
/* 80385644 00382224  2C 03 00 00 */	cmpwi r3, 0
/* 80385648 00382228  40 80 00 14 */	bge .L_8038565C
/* 8038564C 0038222C  38 BC 00 00 */	addi r5, r28, 0
/* 80385650 00382230  38 6D A9 28 */	addi r3, r13, HSD_TExp_804D5FC8@sda21
/* 80385654 00382234  38 80 06 7C */	li r4, 0x67c
/* 80385658 00382238  48 00 2B C9 */	bl __assert
.L_8038565C:
/* 8038565C 0038223C  3B 7B 00 04 */	addi r27, r27, 4
/* 80385660 00382240  3B 39 00 01 */	addi r25, r25, 1
.L_80385664:
/* 80385664 00382244  7C 19 D0 00 */	cmpw r25, r26
/* 80385668 00382248  41 80 FF D0 */	blt .L_80385638
/* 8038566C 0038224C  3B 9A FF FF */	addi r28, r26, -1
/* 80385670 00382250  57 80 10 3A */	slwi r0, r28, 2
/* 80385674 00382254  3B 61 05 1C */	addi r27, r1, 0x51c
/* 80385678 00382258  7F 7B 02 14 */	add r27, r27, r0
/* 8038567C 0038225C  48 00 00 14 */	b .L_80385690
.L_80385680:
/* 80385680 00382260  80 7B 00 00 */	lwz r3, 0(r27)
/* 80385684 00382264  48 00 25 21 */	bl HSD_TExpSimplify2
/* 80385688 00382268  3B 7B FF FC */	addi r27, r27, -4
/* 8038568C 0038226C  3B 9C FF FF */	addi r28, r28, -1
.L_80385690:
/* 80385690 00382270  2C 1C 00 00 */	cmpwi r28, 0
/* 80385694 00382274  40 80 FF EC */	bge .L_80385680
/* 80385698 00382278  38 7D 00 00 */	addi r3, r29, 0
/* 8038569C 0038227C  38 81 00 1C */	addi r4, r1, 0x1c
/* 803856A0 00382280  48 00 05 C1 */	bl HSD_TExpMakeDag
/* 803856A4 00382284  3B 63 00 00 */	addi r27, r3, 0
/* 803856A8 00382288  38 81 00 1C */	addi r4, r1, 0x1c
/* 803856AC 0038228C  38 A1 05 1C */	addi r5, r1, 0x51c
/* 803856B0 00382290  38 C1 05 9C */	addi r6, r1, 0x59c
/* 803856B4 00382294  48 00 0B 81 */	bl HSD_TExpSchedule
/* 803856B8 00382298  3B 80 00 00 */	li r28, 0
/* 803856BC 0038229C  93 9E 00 00 */	stw r28, 0(r30)
/* 803856C0 003822A0  3B A1 05 1C */	addi r29, r1, 0x51c
/* 803856C4 003822A4  48 00 00 4C */	b .L_80385710
.L_803856C8:
/* 803856C8 003822A8  38 60 00 78 */	li r3, 0x78
/* 803856CC 003822AC  4B FF C8 DD */	bl hsdAllocMemPiece
/* 803856D0 003822B0  3B 23 00 00 */	addi r25, r3, 0
/* 803856D4 003822B4  38 7C 00 00 */	addi r3, r28, 0
/* 803856D8 003822B8  4B FD D0 91 */	bl HSD_Index2TevStage
/* 803856DC 003822BC  7C 1C D8 50 */	subf r0, r28, r27
/* 803856E0 003822C0  90 79 00 08 */	stw r3, 8(r25)
/* 803856E4 003822C4  54 03 10 3A */	slwi r3, r0, 2
/* 803856E8 003822C8  38 03 FF FC */	addi r0, r3, -4
/* 803856EC 003822CC  7C 7D 00 2E */	lwzx r3, r29, r0
/* 803856F0 003822D0  38 99 00 00 */	addi r4, r25, 0
/* 803856F4 003822D4  38 A1 00 18 */	addi r5, r1, 0x18
/* 803856F8 003822D8  38 C1 00 14 */	addi r6, r1, 0x14
/* 803856FC 003822DC  4B FF F4 25 */	bl TExp2TevDesc
/* 80385700 003822E0  80 1E 00 00 */	lwz r0, 0(r30)
/* 80385704 003822E4  3B 9C 00 01 */	addi r28, r28, 1
/* 80385708 003822E8  90 19 00 00 */	stw r0, 0(r25)
/* 8038570C 003822EC  93 3E 00 00 */	stw r25, 0(r30)
.L_80385710:
/* 80385710 003822F0  7C 1C D8 00 */	cmpw r28, r27
/* 80385714 003822F4  41 80 FF B4 */	blt .L_803856C8
/* 80385718 003822F8  80 7F 00 00 */	lwz r3, 0(r31)
/* 8038571C 003822FC  38 80 00 01 */	li r4, 1
/* 80385720 00382300  38 A0 00 01 */	li r5, 1
/* 80385724 00382304  4B FF D6 B9 */	bl HSD_TExpFreeList
/* 80385728 00382308  90 7F 00 00 */	stw r3, 0(r31)
/* 8038572C 0038230C  38 80 00 04 */	li r4, 4
/* 80385730 00382310  38 A0 00 00 */	li r5, 0
/* 80385734 00382314  80 7F 00 00 */	lwz r3, 0(r31)
/* 80385738 00382318  4B FF D6 A5 */	bl HSD_TExpFreeList
/* 8038573C 0038231C  90 7F 00 00 */	stw r3, 0(r31)
/* 80385740 00382320  7F 63 DB 78 */	mr r3, r27
/* 80385744 00382324  BB 21 05 CC */	lmw r25, 0x5cc(r1)
/* 80385748 00382328  80 01 05 EC */	lwz r0, 0x5ec(r1)
/* 8038574C 0038232C  38 21 05 E8 */	addi r1, r1, 0x5e8
/* 80385750 00382330  7C 08 03 A6 */	mtlr r0
/* 80385754 00382334  4E 80 00 20 */	blr


.section .data
    .balign 8
.global HSD_TExp_80407738
HSD_TExp_80407738:
    .asciz "texp_list"
    .balign 4
.global HSD_TExp_80407A14
HSD_TExp_80407A14:
    .asciz "val >= 0"
    .balign 4
    .4byte 0x00000001
    .4byte 0x00000002
    .4byte 0x00000003
    .4byte NULL
    .asciz "tev->c_dst != HSD_TE_UNDEF"
    .balign 4
    .asciz "tev->a_dst != HSD_TE_UNDEF"
    .balign 4
    .4byte NULL
    .4byte 0x00000001
    .4byte 0x00000002
    .4byte 0x00000003
    .4byte 0x00000001
    .4byte 0x00000002
    .4byte 0x00000003
    .asciz "clist->type == HSD_TE_CNST"


.section .sdata
    .balign 8
.global HSD_TExp_804D5FC8
HSD_TExp_804D5FC8:
    .asciz "texp.c"
    .balign 4
.global HSD_TExp_804D5FD0
HSD_TExp_804D5FD0:
    .asciz "texp"
    .balign 4
.global HSD_TExp_804D5FD8
HSD_TExp_804D5FD8:
    .asciz "0"
    .balign 4
.global HSD_TExp_804D5FDC
HSD_TExp_804D5FDC:
    .asciz "desc"
    .balign 4
.global HSD_TExp_804D5FE4
HSD_TExp_804D5FE4:
    .asciz "tevdesc"
    .balign 4


.section .sdata2
    .balign 8
.global HSD_TExp_804DE7D8
HSD_TExp_804DE7D8:
    .float 255.0
    .balign 8
.global HSD_TExp_804DE7E0
HSD_TExp_804DE7E0:
    .double 255.0
