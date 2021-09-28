.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80220F10
func_80220F10:
/* 80220F10 0021DAF0  4E 80 00 20 */	blr 
/* 80220F14 0021DAF4  7C 08 02 A6 */	mflr r0
/* 80220F18 0021DAF8  3C 60 80 4A */	lis r3, lbl_8049E6C8@ha
/* 80220F1C 0021DAFC  90 01 00 04 */	stw r0, 4(r1)
/* 80220F20 0021DB00  38 63 E6 C8 */	addi r3, r3, lbl_8049E6C8@l
/* 80220F24 0021DB04  38 A3 00 8C */	addi r5, r3, 0x8c
/* 80220F28 0021DB08  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220F2C 0021DB0C  38 80 00 01 */	li r4, 1
/* 80220F30 0021DB10  88 03 00 8C */	lbz r0, 0x8c(r3)
/* 80220F34 0021DB14  38 60 00 00 */	li r3, 0
/* 80220F38 0021DB18  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80220F3C 0021DB1C  98 05 00 00 */	stb r0, 0(r5)
/* 80220F40 0021DB20  38 60 00 00 */	li r3, 0
/* 80220F44 0021DB24  88 05 00 00 */	lbz r0, 0(r5)
/* 80220F48 0021DB28  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 80220F4C 0021DB2C  98 05 00 00 */	stb r0, 0(r5)
/* 80220F50 0021DB30  48 00 00 65 */	bl func_80220FB4
/* 80220F54 0021DB34  38 60 00 01 */	li r3, 1
/* 80220F58 0021DB38  48 00 00 5D */	bl func_80220FB4
/* 80220F5C 0021DB3C  38 60 00 02 */	li r3, 2
/* 80220F60 0021DB40  48 00 00 55 */	bl func_80220FB4
/* 80220F64 0021DB44  4B FA 2A 5D */	bl func_801C39C0
/* 80220F68 0021DB48  4B FA 2C 4D */	bl func_801C3BB4
/* 80220F6C 0021DB4C  4B FA 32 A5 */	bl func_801C4210
/* 80220F70 0021DB50  4B FA 33 3D */	bl func_801C42AC
/* 80220F74 0021DB54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220F78 0021DB58  38 21 00 08 */	addi r1, r1, 8
/* 80220F7C 0021DB5C  7C 08 03 A6 */	mtlr r0
/* 80220F80 0021DB60  4E 80 00 20 */	blr 
/* 80220F84 0021DB64  4E 80 00 20 */	blr 
/* 80220F88 0021DB68  7C 08 02 A6 */	mflr r0
/* 80220F8C 0021DB6C  38 60 00 00 */	li r3, 0
/* 80220F90 0021DB70  90 01 00 04 */	stw r0, 4(r1)
/* 80220F94 0021DB74  94 21 FF F8 */	stwu r1, -8(r1)
/* 80220F98 0021DB78  4B FA 9E 6D */	bl func_801CAE04
/* 80220F9C 0021DB7C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80220FA0 0021DB80  38 21 00 08 */	addi r1, r1, 8
/* 80220FA4 0021DB84  7C 08 03 A6 */	mtlr r0
/* 80220FA8 0021DB88  4E 80 00 20 */	blr 
/* 80220FAC 0021DB8C  38 60 00 00 */	li r3, 0
/* 80220FB0 0021DB90  4E 80 00 20 */	blr 

.global func_80220FB4
func_80220FB4:
/* 80220FB4 0021DB94  7C 08 02 A6 */	mflr r0
/* 80220FB8 0021DB98  90 01 00 04 */	stw r0, 4(r1)
/* 80220FBC 0021DB9C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80220FC0 0021DBA0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80220FC4 0021DBA4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80220FC8 0021DBA8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80220FCC 0021DBAC  93 81 00 10 */	stw r28, 0x10(r1)
/* 80220FD0 0021DBB0  3B 83 00 00 */	addi r28, r3, 0
/* 80220FD4 0021DBB4  1C 1C 00 14 */	mulli r0, r28, 0x14
/* 80220FD8 0021DBB8  3C 60 80 3F */	lis r3, lbl_803E8A98@ha
/* 80220FDC 0021DBBC  3B E3 8A 98 */	addi r31, r3, lbl_803E8A98@l
/* 80220FE0 0021DBC0  38 7C 00 00 */	addi r3, r28, 0
/* 80220FE4 0021DBC4  7F BF 02 14 */	add r29, r31, r0
/* 80220FE8 0021DBC8  4B FA 04 E9 */	bl func_801C14D0
/* 80220FEC 0021DBCC  7C 7E 1B 79 */	or. r30, r3, r3
/* 80220FF0 0021DBD0  41 82 00 70 */	beq lbl_80221060
/* 80220FF4 0021DBD4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80220FF8 0021DBD8  38 00 00 00 */	li r0, 0
/* 80220FFC 0021DBDC  3C 60 80 1C */	lis r3, func_801C5DB0@ha
/* 80221000 0021DBE0  90 1F 00 08 */	stw r0, 8(r31)
/* 80221004 0021DBE4  38 83 5D B0 */	addi r4, r3, func_801C5DB0@l
/* 80221008 0021DBE8  38 7E 00 00 */	addi r3, r30, 0
/* 8022100C 0021DBEC  90 1F 00 0C */	stw r0, 0xc(r31)
/* 80221010 0021DBF0  38 A0 00 03 */	li r5, 3
/* 80221014 0021DBF4  38 C0 00 00 */	li r6, 0
/* 80221018 0021DBF8  48 16 F6 85 */	bl func_8039069C
/* 8022101C 0021DBFC  80 1D 00 0C */	lwz r0, 0xc(r29)
/* 80221020 0021DC00  28 00 00 00 */	cmplwi r0, 0
/* 80221024 0021DC04  41 82 00 08 */	beq lbl_8022102C
/* 80221028 0021DC08  90 1F 00 1C */	stw r0, 0x1c(r31)
lbl_8022102C:
/* 8022102C 0021DC0C  81 9D 00 00 */	lwz r12, 0(r29)
/* 80221030 0021DC10  28 0C 00 00 */	cmplwi r12, 0
/* 80221034 0021DC14  41 82 00 10 */	beq lbl_80221044
/* 80221038 0021DC18  7D 88 03 A6 */	mtlr r12
/* 8022103C 0021DC1C  38 7E 00 00 */	addi r3, r30, 0
/* 80221040 0021DC20  4E 80 00 21 */	blrl 
lbl_80221044:
/* 80221044 0021DC24  80 9D 00 08 */	lwz r4, 8(r29)
/* 80221048 0021DC28  28 04 00 00 */	cmplwi r4, 0
/* 8022104C 0021DC2C  41 82 00 2C */	beq lbl_80221078
/* 80221050 0021DC30  38 7E 00 00 */	addi r3, r30, 0
/* 80221054 0021DC34  38 A0 00 04 */	li r5, 4
/* 80221058 0021DC38  48 16 EC FD */	bl func_8038FD54
/* 8022105C 0021DC3C  48 00 00 1C */	b lbl_80221078
lbl_80221060:
/* 80221060 0021DC40  38 DC 00 00 */	addi r6, r28, 0
/* 80221064 0021DC44  4C C6 31 82 */	crclr 6
/* 80221068 0021DC48  38 7F 00 90 */	addi r3, r31, 0x90
/* 8022106C 0021DC4C  38 9F 00 B4 */	addi r4, r31, 0xb4
/* 80221070 0021DC50  38 A0 00 CA */	li r5, 0xca
/* 80221074 0021DC54  48 12 46 35 */	bl OSReport
lbl_80221078:
/* 80221078 0021DC58  7F C3 F3 78 */	mr r3, r30
/* 8022107C 0021DC5C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221080 0021DC60  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80221084 0021DC64  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221088 0021DC68  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8022108C 0021DC6C  83 81 00 10 */	lwz r28, 0x10(r1)
/* 80221090 0021DC70  38 21 00 20 */	addi r1, r1, 0x20
/* 80221094 0021DC74  7C 08 03 A6 */	mtlr r0
/* 80221098 0021DC78  4E 80 00 20 */	blr 
/* 8022109C 0021DC7C  7C 08 02 A6 */	mflr r0
/* 802210A0 0021DC80  38 A0 00 00 */	li r5, 0
/* 802210A4 0021DC84  90 01 00 04 */	stw r0, 4(r1)
/* 802210A8 0021DC88  94 21 FF F8 */	stwu r1, -8(r1)
/* 802210AC 0021DC8C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 802210B0 0021DC90  80 84 00 14 */	lwz r4, 0x14(r4)
/* 802210B4 0021DC94  4B FA 70 85 */	bl func_801C8138
/* 802210B8 0021DC98  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802210BC 0021DC9C  38 21 00 08 */	addi r1, r1, 8
/* 802210C0 0021DCA0  7C 08 03 A6 */	mtlr r0
/* 802210C4 0021DCA4  4E 80 00 20 */	blr 
/* 802210C8 0021DCA8  38 60 00 00 */	li r3, 0
/* 802210CC 0021DCAC  4E 80 00 20 */	blr 
/* 802210D0 0021DCB0  4E 80 00 20 */	blr 
/* 802210D4 0021DCB4  4E 80 00 20 */	blr 
/* 802210D8 0021DCB8  7C 08 02 A6 */	mflr r0
/* 802210DC 0021DCBC  90 01 00 04 */	stw r0, 4(r1)
/* 802210E0 0021DCC0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 802210E4 0021DCC4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 802210E8 0021DCC8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802210EC 0021DCCC  7C 7E 1B 78 */	mr r30, r3
/* 802210F0 0021DCD0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802210F4 0021DCD4  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802210F8 0021DCD8  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802210FC 0021DCDC  4B FA 1D D5 */	bl func_801C2ED0
/* 80221100 0021DCE0  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80221104 0021DCE4  38 7E 00 00 */	addi r3, r30, 0
/* 80221108 0021DCE8  38 A0 00 00 */	li r5, 0
/* 8022110C 0021DCEC  4B FA 70 2D */	bl func_801C8138
/* 80221110 0021DCF0  C0 22 C2 D8 */	lfs f1, lbl_804DBCB8@sda21(r2)
/* 80221114 0021DCF4  7F C3 F3 78 */	mr r3, r30
/* 80221118 0021DCF8  C0 42 C2 DC */	lfs f2, lbl_804DBCBC@sda21(r2)
/* 8022111C 0021DCFC  38 80 00 45 */	li r4, 0x45
/* 80221120 0021DD00  38 A0 00 02 */	li r5, 2
/* 80221124 0021DD04  38 C0 00 01 */	li r6, 1
/* 80221128 0021DD08  4B FA 6E D1 */	bl func_801C7FF8
/* 8022112C 0021DD0C  7F C3 F3 78 */	mr r3, r30
/* 80221130 0021DD10  48 00 01 59 */	bl func_80221288
/* 80221134 0021DD14  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80221138 0021DD18  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8022113C 0021DD1C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80221140 0021DD20  38 21 00 20 */	addi r1, r1, 0x20
/* 80221144 0021DD24  7C 08 03 A6 */	mtlr r0
/* 80221148 0021DD28  4E 80 00 20 */	blr 
/* 8022114C 0021DD2C  38 60 00 00 */	li r3, 0
/* 80221150 0021DD30  4E 80 00 20 */	blr 
/* 80221154 0021DD34  7C 08 02 A6 */	mflr r0
/* 80221158 0021DD38  90 01 00 04 */	stw r0, 4(r1)
/* 8022115C 0021DD3C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80221160 0021DD40  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80221164 0021DD44  7C 7F 1B 78 */	mr r31, r3
/* 80221168 0021DD48  4B DF 04 8D */	bl func_800115F4
/* 8022116C 0021DD4C  7F E3 FB 78 */	mr r3, r31
/* 80221170 0021DD50  4B FA 1E 71 */	bl func_801C2FE0
/* 80221174 0021DD54  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80221178 0021DD58  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8022117C 0021DD5C  38 21 00 18 */	addi r1, r1, 0x18
/* 80221180 0021DD60  7C 08 03 A6 */	mtlr r0
/* 80221184 0021DD64  4E 80 00 20 */	blr 
/* 80221188 0021DD68  4E 80 00 20 */	blr 
/* 8022118C 0021DD6C  7C 08 02 A6 */	mflr r0
/* 80221190 0021DD70  90 01 00 04 */	stw r0, 4(r1)
/* 80221194 0021DD74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80221198 0021DD78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8022119C 0021DD7C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 802211A0 0021DD80  7C 7E 1B 78 */	mr r30, r3
/* 802211A4 0021DD84  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 802211A8 0021DD88  80 63 00 28 */	lwz r3, 0x28(r3)
/* 802211AC 0021DD8C  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802211B0 0021DD90  4B FA 1D 21 */	bl func_801C2ED0
/* 802211B4 0021DD94  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 802211B8 0021DD98  38 7E 00 00 */	addi r3, r30, 0
/* 802211BC 0021DD9C  38 A0 00 00 */	li r5, 0
/* 802211C0 0021DDA0  4B FA 6F 79 */	bl func_801C8138
/* 802211C4 0021DDA4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 802211C8 0021DDA8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 802211CC 0021DDAC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 802211D0 0021DDB0  38 21 00 20 */	addi r1, r1, 0x20
/* 802211D4 0021DDB4  7C 08 03 A6 */	mtlr r0
/* 802211D8 0021DDB8  4E 80 00 20 */	blr 
/* 802211DC 0021DDBC  38 60 00 00 */	li r3, 0
/* 802211E0 0021DDC0  4E 80 00 20 */	blr 
/* 802211E4 0021DDC4  7C 08 02 A6 */	mflr r0
/* 802211E8 0021DDC8  90 01 00 04 */	stw r0, 4(r1)
/* 802211EC 0021DDCC  94 21 FF F8 */	stwu r1, -8(r1)
/* 802211F0 0021DDD0  4B FA 1D F1 */	bl func_801C2FE0
/* 802211F4 0021DDD4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 802211F8 0021DDD8  38 21 00 08 */	addi r1, r1, 8
/* 802211FC 0021DDDC  7C 08 03 A6 */	mtlr r0
/* 80221200 0021DDE0  4E 80 00 20 */	blr 
/* 80221204 0021DDE4  4E 80 00 20 */	blr 
lbl_80221208:
/* 80221208 0021DDE8  7C 08 02 A6 */	mflr r0
/* 8022120C 0021DDEC  38 80 00 10 */	li r4, 0x10
/* 80221210 0021DDF0  90 01 00 04 */	stw r0, 4(r1)
/* 80221214 0021DDF4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80221218 0021DDF8  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8022121C 0021DDFC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 80221220 0021DE00  7C 7E 1B 78 */	mr r30, r3
/* 80221224 0021DE04  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80221228 0021DE08  80 7F 0D D8 */	lwz r3, 0xdd8(r31)
/* 8022122C 0021DE0C  48 15 0B 71 */	bl HSD_JObjSetFlagsAll
/* 80221230 0021DE10  80 7F 0D D8 */	lwz r3, 0xdd8(r31)
/* 80221234 0021DE14  38 A1 00 20 */	addi r5, r1, 0x20
/* 80221238 0021DE18  38 80 00 00 */	li r4, 0
/* 8022123C 0021DE1C  4B DE 9F 91 */	bl func_8000B1CC
/* 80221240 0021DE20  38 9E 00 00 */	addi r4, r30, 0
/* 80221244 0021DE24  4C C6 31 82 */	crclr 6
/* 80221248 0021DE28  38 A1 00 20 */	addi r5, r1, 0x20
/* 8022124C 0021DE2C  38 60 04 45 */	li r3, 0x445
/* 80221250 0021DE30  4B E3 EB 8D */	bl func_8005FDDC
/* 80221254 0021DE34  38 60 00 02 */	li r3, 2
/* 80221258 0021DE38  38 80 00 00 */	li r4, 0
/* 8022125C 0021DE3C  4B E0 FB E9 */	bl func_80030E44
/* 80221260 0021DE40  38 60 01 36 */	li r3, 0x136
/* 80221264 0021DE44  4B FA 41 89 */	bl func_801C53EC
/* 80221268 0021DE48  7F C3 F3 78 */	mr r3, r30
/* 8022126C 0021DE4C  4B FA 7A 71 */	bl func_801C8CDC
/* 80221270 0021DE50  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80221274 0021DE54  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80221278 0021DE58  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8022127C 0021DE5C  38 21 00 38 */	addi r1, r1, 0x38
/* 80221280 0021DE60  7C 08 03 A6 */	mtlr r0
/* 80221284 0021DE64  4E 80 00 20 */	blr 

.global func_80221288
func_80221288:
/* 80221288 0021DE68  7C 08 02 A6 */	mflr r0
/* 8022128C 0021DE6C  3C 80 80 3F */	lis r4, lbl_803E8B5C@ha
/* 80221290 0021DE70  90 01 00 04 */	stw r0, 4(r1)
/* 80221294 0021DE74  38 00 00 00 */	li r0, 0
/* 80221298 0021DE78  54 05 08 3C */	slwi r5, r0, 1
/* 8022129C 0021DE7C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 802212A0 0021DE80  38 04 8B 5C */	addi r0, r4, lbl_803E8B5C@l
/* 802212A4 0021DE84  BF 61 00 14 */	stmw r27, 0x14(r1)
/* 802212A8 0021DE88  3B 63 00 00 */	addi r27, r3, 0
/* 802212AC 0021DE8C  3C 60 80 22 */	lis r3, lbl_80221208@ha
/* 802212B0 0021DE90  7F C0 2A 14 */	add r30, r0, r5
/* 802212B4 0021DE94  3B E3 12 08 */	addi r31, r3, lbl_80221208@l
/* 802212B8 0021DE98  83 BB 00 2C */	lwz r29, 0x2c(r27)
/* 802212BC 0021DE9C  48 00 00 78 */	b lbl_80221334
lbl_802212C0:
/* 802212C0 0021DEA0  38 60 00 02 */	li r3, 2
/* 802212C4 0021DEA4  4B FA 20 FD */	bl func_801C33C0
/* 802212C8 0021DEA8  38 83 00 00 */	addi r4, r3, 0
/* 802212CC 0021DEAC  2C 04 FF FF */	cmpwi r4, -1
/* 802212D0 0021DEB0  41 82 00 60 */	beq lbl_80221330
/* 802212D4 0021DEB4  7F 63 DB 78 */	mr r3, r27
/* 802212D8 0021DEB8  4B FA 2C CD */	bl func_801C3FA4
/* 802212DC 0021DEBC  38 C3 00 00 */	addi r6, r3, 0
/* 802212E0 0021DEC0  38 BD 00 00 */	addi r5, r29, 0
/* 802212E4 0021DEC4  39 1F 00 00 */	addi r8, r31, 0
/* 802212E8 0021DEC8  38 60 00 00 */	li r3, 0
/* 802212EC 0021DECC  38 80 00 00 */	li r4, 0
/* 802212F0 0021DED0  38 E0 00 00 */	li r7, 0
/* 802212F4 0021DED4  39 20 00 00 */	li r9, 0
/* 802212F8 0021DED8  4B FA 7A 05 */	bl func_801C8CFC
/* 802212FC 0021DEDC  7C 7C 1B 79 */	or. r28, r3, r3
/* 80221300 0021DEE0  41 82 00 30 */	beq lbl_80221330
/* 80221304 0021DEE4  C0 42 C2 D8 */	lfs f2, lbl_804DBCB8@sda21(r2)
/* 80221308 0021DEE8  7F 83 E3 78 */	mr r3, r28
/* 8022130C 0021DEEC  C0 22 C2 E0 */	lfs f1, lbl_804DBCC0@sda21(r2)
/* 80221310 0021DEF0  FC 60 10 90 */	fmr f3, f2
/* 80221314 0021DEF4  C0 82 C2 DC */	lfs f4, lbl_804DBCBC@sda21(r2)
/* 80221318 0021DEF8  FC A0 10 90 */	fmr f5, f2
/* 8022131C 0021DEFC  C0 E2 C2 E4 */	lfs f7, lbl_804DBCC4@sda21(r2)
/* 80221320 0021DF00  FC C0 10 90 */	fmr f6, f2
/* 80221324 0021DF04  4B FA 7A BD */	bl func_801C8DE0
/* 80221328 0021DF08  7F 83 E3 78 */	mr r3, r28
/* 8022132C 0021DF0C  4B FA 7A DD */	bl func_801C8E08
lbl_80221330:
/* 80221330 0021DF10  3B DE 00 02 */	addi r30, r30, 2
lbl_80221334:
/* 80221334 0021DF14  A8 9E 00 00 */	lha r4, 0(r30)
/* 80221338 0021DF18  2C 04 FF FF */	cmpwi r4, -1
/* 8022133C 0021DF1C  40 82 FF 84 */	bne lbl_802212C0
/* 80221340 0021DF20  BB 61 00 14 */	lmw r27, 0x14(r1)
/* 80221344 0021DF24  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80221348 0021DF28  38 21 00 28 */	addi r1, r1, 0x28
/* 8022134C 0021DF2C  7C 08 03 A6 */	mtlr r0
/* 80221350 0021DF30  4E 80 00 20 */	blr 
/* 80221354 0021DF34  38 60 00 00 */	li r3, 0
/* 80221358 0021DF38  4E 80 00 20 */	blr 
/* 8022135C 0021DF3C  38 60 00 01 */	li r3, 1
/* 80221360 0021DF40  4E 80 00 20 */	blr 
