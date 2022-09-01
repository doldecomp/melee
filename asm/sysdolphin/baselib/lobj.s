.include "macros.inc"

.section .text

LObjLoad:
/* 80366EA8 00363A88  7C 08 02 A6 */	mflr r0
/* 80366EAC 00363A8C  90 01 00 04 */	stw r0, 4(r1)
/* 80366EB0 00363A90  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80366EB4 00363A94  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80366EB8 00363A98  7C 9F 23 78 */	mr r31, r4
/* 80366EBC 00363A9C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80366EC0 00363AA0  7C 7E 1B 79 */	or. r30, r3, r3
/* 80366EC4 00363AA4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80366EC8 00363AA8  93 81 00 18 */	stw r28, 0x18(r1)
/* 80366ECC 00363AAC  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80366ED0 00363AB0  90 03 00 10 */	stw r0, 0x10(r3)
/* 80366ED4 00363AB4  A0 64 00 08 */	lhz r3, 8(r4)
/* 80366ED8 00363AB8  41 82 00 10 */	beq lbl_80366EE8
/* 80366EDC 00363ABC  A0 1E 00 08 */	lhz r0, 8(r30)
/* 80366EE0 00363AC0  7C 00 1B 78 */	or r0, r0, r3
/* 80366EE4 00363AC4  B0 1E 00 08 */	sth r0, 8(r30)
lbl_80366EE8:
/* 80366EE8 00363AC8  A0 9F 00 08 */	lhz r4, 8(r31)
/* 80366EEC 00363ACC  54 80 07 BE */	clrlwi r0, r4, 0x1e
/* 80366EF0 00363AD0  2C 00 00 02 */	cmpwi r0, 2
/* 80366EF4 00363AD4  41 82 00 C0 */	beq lbl_80366FB4
/* 80366EF8 00363AD8  40 80 00 14 */	bge lbl_80366F0C
/* 80366EFC 00363ADC  2C 00 00 00 */	cmpwi r0, 0
/* 80366F00 00363AE0  41 82 03 B8 */	beq lbl_803672B8
/* 80366F04 00363AE4  40 80 00 14 */	bge lbl_80366F18
/* 80366F08 00363AE8  48 00 03 90 */	b lbl_80367298
lbl_80366F0C:
/* 80366F0C 00363AEC  2C 00 00 04 */	cmpwi r0, 4
/* 80366F10 00363AF0  40 80 03 88 */	bge lbl_80367298
/* 80366F14 00363AF4  48 00 01 A8 */	b lbl_803670BC
lbl_80366F18:
/* 80366F18 00363AF8  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 80366F1C 00363AFC  48 01 64 A9 */	bl HSD_WObjLoadDesc
/* 80366F20 00363B00  28 1E 00 00 */	cmplwi r30, 0
/* 80366F24 00363B04  3B A3 00 00 */	addi r29, r3, 0
/* 80366F28 00363B08  41 82 03 90 */	beq lbl_803672B8
/* 80366F2C 00363B0C  83 FE 00 18 */	lwz r31, 0x18(r30)
/* 80366F30 00363B10  28 1F 00 00 */	cmplwi r31, 0
/* 80366F34 00363B14  41 82 00 78 */	beq lbl_80366FAC
/* 80366F38 00363B18  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 80366F3C 00363B1C  A0 9F 00 04 */	lhz r4, 4(r31)
/* 80366F40 00363B20  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 80366F44 00363B24  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 80366F48 00363B28  7C 04 00 50 */	subf r0, r4, r0
/* 80366F4C 00363B2C  7C 00 00 34 */	cntlzw r0, r0
/* 80366F50 00363B30  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 80366F54 00363B34  38 BF 00 04 */	addi r5, r31, 4
/* 80366F58 00363B38  41 82 00 08 */	beq lbl_80366F60
/* 80366F5C 00363B3C  48 00 00 18 */	b lbl_80366F74
lbl_80366F60:
/* 80366F60 00363B40  38 64 FF FF */	addi r3, r4, -1
/* 80366F64 00363B44  7C 04 00 D0 */	neg r0, r4
/* 80366F68 00363B48  B0 65 00 00 */	sth r3, 0(r5)
/* 80366F6C 00363B4C  7C 00 00 34 */	cntlzw r0, r0
/* 80366F70 00363B50  54 00 D9 7E */	srwi r0, r0, 5
lbl_80366F74:
/* 80366F74 00363B54  2C 00 00 00 */	cmpwi r0, 0
/* 80366F78 00363B58  41 82 00 34 */	beq lbl_80366FAC
/* 80366F7C 00363B5C  28 1F 00 00 */	cmplwi r31, 0
/* 80366F80 00363B60  41 82 00 2C */	beq lbl_80366FAC
/* 80366F84 00363B64  80 9F 00 00 */	lwz r4, 0(r31)
/* 80366F88 00363B68  7F E3 FB 78 */	mr r3, r31
/* 80366F8C 00363B6C  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80366F90 00363B70  7D 88 03 A6 */	mtlr r12
/* 80366F94 00363B74  4E 80 00 21 */	blrl 
/* 80366F98 00363B78  80 9F 00 00 */	lwz r4, 0(r31)
/* 80366F9C 00363B7C  7F E3 FB 78 */	mr r3, r31
/* 80366FA0 00363B80  81 84 00 34 */	lwz r12, 0x34(r4)
/* 80366FA4 00363B84  7D 88 03 A6 */	mtlr r12
/* 80366FA8 00363B88  4E 80 00 21 */	blrl 
lbl_80366FAC:
/* 80366FAC 00363B8C  93 BE 00 18 */	stw r29, 0x18(r30)
/* 80366FB0 00363B90  48 00 03 08 */	b lbl_803672B8
lbl_80366FB4:
/* 80366FB4 00363B94  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 80366FB8 00363B98  48 01 64 0D */	bl HSD_WObjLoadDesc
/* 80366FBC 00363B9C  28 1E 00 00 */	cmplwi r30, 0
/* 80366FC0 00363BA0  3B A3 00 00 */	addi r29, r3, 0
/* 80366FC4 00363BA4  41 82 00 88 */	beq lbl_8036704C
/* 80366FC8 00363BA8  83 9E 00 18 */	lwz r28, 0x18(r30)
/* 80366FCC 00363BAC  28 1C 00 00 */	cmplwi r28, 0
/* 80366FD0 00363BB0  41 82 00 78 */	beq lbl_80367048
/* 80366FD4 00363BB4  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 80366FD8 00363BB8  A0 9C 00 04 */	lhz r4, 4(r28)
/* 80366FDC 00363BBC  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 80366FE0 00363BC0  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 80366FE4 00363BC4  7C 04 00 50 */	subf r0, r4, r0
/* 80366FE8 00363BC8  7C 00 00 34 */	cntlzw r0, r0
/* 80366FEC 00363BCC  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 80366FF0 00363BD0  38 BC 00 04 */	addi r5, r28, 4
/* 80366FF4 00363BD4  41 82 00 08 */	beq lbl_80366FFC
/* 80366FF8 00363BD8  48 00 00 18 */	b lbl_80367010
lbl_80366FFC:
/* 80366FFC 00363BDC  38 64 FF FF */	addi r3, r4, -1
/* 80367000 00363BE0  7C 04 00 D0 */	neg r0, r4
/* 80367004 00363BE4  B0 65 00 00 */	sth r3, 0(r5)
/* 80367008 00363BE8  7C 00 00 34 */	cntlzw r0, r0
/* 8036700C 00363BEC  54 00 D9 7E */	srwi r0, r0, 5
lbl_80367010:
/* 80367010 00363BF0  2C 00 00 00 */	cmpwi r0, 0
/* 80367014 00363BF4  41 82 00 34 */	beq lbl_80367048
/* 80367018 00363BF8  28 1C 00 00 */	cmplwi r28, 0
/* 8036701C 00363BFC  41 82 00 2C */	beq lbl_80367048
/* 80367020 00363C00  80 9C 00 00 */	lwz r4, 0(r28)
/* 80367024 00363C04  7F 83 E3 78 */	mr r3, r28
/* 80367028 00363C08  81 84 00 30 */	lwz r12, 0x30(r4)
/* 8036702C 00363C0C  7D 88 03 A6 */	mtlr r12
/* 80367030 00363C10  4E 80 00 21 */	blrl 
/* 80367034 00363C14  80 9C 00 00 */	lwz r4, 0(r28)
/* 80367038 00363C18  7F 83 E3 78 */	mr r3, r28
/* 8036703C 00363C1C  81 84 00 34 */	lwz r12, 0x34(r4)
/* 80367040 00363C20  7D 88 03 A6 */	mtlr r12
/* 80367044 00363C24  4E 80 00 21 */	blrl 
lbl_80367048:
/* 80367048 00363C28  93 BE 00 18 */	stw r29, 0x18(r30)
lbl_8036704C:
/* 8036704C 00363C2C  A0 1F 00 0A */	lhz r0, 0xa(r31)
/* 80367050 00363C30  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80367054 00363C34  41 82 00 40 */	beq lbl_80367094
/* 80367058 00363C38  28 1E 00 00 */	cmplwi r30, 0
/* 8036705C 00363C3C  41 82 00 10 */	beq lbl_8036706C
/* 80367060 00363C40  A0 1E 00 08 */	lhz r0, 8(r30)
/* 80367064 00363C44  60 00 00 40 */	ori r0, r0, 0x40
/* 80367068 00363C48  B0 1E 00 08 */	sth r0, 8(r30)
lbl_8036706C:
/* 8036706C 00363C4C  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80367070 00363C50  28 1E 00 00 */	cmplwi r30, 0
/* 80367074 00363C54  C0 43 00 14 */	lfs f2, 0x14(r3)
/* 80367078 00363C58  C0 23 00 10 */	lfs f1, 0x10(r3)
/* 8036707C 00363C5C  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 80367080 00363C60  41 82 02 38 */	beq lbl_803672B8
/* 80367084 00363C64  D0 1E 00 2C */	stfs f0, 0x2c(r30)
/* 80367088 00363C68  D0 3E 00 30 */	stfs f1, 0x30(r30)
/* 8036708C 00363C6C  D0 5E 00 34 */	stfs f2, 0x34(r30)
/* 80367090 00363C70  48 00 02 28 */	b lbl_803672B8
lbl_80367094:
/* 80367094 00363C74  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80367098 00363C78  28 1E 00 00 */	cmplwi r30, 0
/* 8036709C 00363C7C  80 03 00 08 */	lwz r0, 8(r3)
/* 803670A0 00363C80  C0 23 00 00 */	lfs f1, 0(r3)
/* 803670A4 00363C84  C0 03 00 04 */	lfs f0, 4(r3)
/* 803670A8 00363C88  41 82 02 10 */	beq lbl_803672B8
/* 803670AC 00363C8C  D0 1E 00 2C */	stfs f0, 0x2c(r30)
/* 803670B0 00363C90  D0 3E 00 28 */	stfs f1, 0x28(r30)
/* 803670B4 00363C94  90 1E 00 30 */	stw r0, 0x30(r30)
/* 803670B8 00363C98  48 00 02 00 */	b lbl_803672B8
lbl_803670BC:
/* 803670BC 00363C9C  80 7F 00 10 */	lwz r3, 0x10(r31)
/* 803670C0 00363CA0  48 01 63 05 */	bl HSD_WObjLoadDesc
/* 803670C4 00363CA4  28 1E 00 00 */	cmplwi r30, 0
/* 803670C8 00363CA8  3B A3 00 00 */	addi r29, r3, 0
/* 803670CC 00363CAC  41 82 00 88 */	beq lbl_80367154
/* 803670D0 00363CB0  83 9E 00 18 */	lwz r28, 0x18(r30)
/* 803670D4 00363CB4  28 1C 00 00 */	cmplwi r28, 0
/* 803670D8 00363CB8  41 82 00 78 */	beq lbl_80367150
/* 803670DC 00363CBC  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 803670E0 00363CC0  A0 9C 00 04 */	lhz r4, 4(r28)
/* 803670E4 00363CC4  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 803670E8 00363CC8  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 803670EC 00363CCC  7C 04 00 50 */	subf r0, r4, r0
/* 803670F0 00363CD0  7C 00 00 34 */	cntlzw r0, r0
/* 803670F4 00363CD4  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 803670F8 00363CD8  38 BC 00 04 */	addi r5, r28, 4
/* 803670FC 00363CDC  41 82 00 08 */	beq lbl_80367104
/* 80367100 00363CE0  48 00 00 18 */	b lbl_80367118
lbl_80367104:
/* 80367104 00363CE4  38 64 FF FF */	addi r3, r4, -1
/* 80367108 00363CE8  7C 04 00 D0 */	neg r0, r4
/* 8036710C 00363CEC  B0 65 00 00 */	sth r3, 0(r5)
/* 80367110 00363CF0  7C 00 00 34 */	cntlzw r0, r0
/* 80367114 00363CF4  54 00 D9 7E */	srwi r0, r0, 5
lbl_80367118:
/* 80367118 00363CF8  2C 00 00 00 */	cmpwi r0, 0
/* 8036711C 00363CFC  41 82 00 34 */	beq lbl_80367150
/* 80367120 00363D00  28 1C 00 00 */	cmplwi r28, 0
/* 80367124 00363D04  41 82 00 2C */	beq lbl_80367150
/* 80367128 00363D08  80 9C 00 00 */	lwz r4, 0(r28)
/* 8036712C 00363D0C  7F 83 E3 78 */	mr r3, r28
/* 80367130 00363D10  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80367134 00363D14  7D 88 03 A6 */	mtlr r12
/* 80367138 00363D18  4E 80 00 21 */	blrl 
/* 8036713C 00363D1C  80 9C 00 00 */	lwz r4, 0(r28)
/* 80367140 00363D20  7F 83 E3 78 */	mr r3, r28
/* 80367144 00363D24  81 84 00 34 */	lwz r12, 0x34(r4)
/* 80367148 00363D28  7D 88 03 A6 */	mtlr r12
/* 8036714C 00363D2C  4E 80 00 21 */	blrl 
lbl_80367150:
/* 80367150 00363D30  93 BE 00 18 */	stw r29, 0x18(r30)
lbl_80367154:
/* 80367154 00363D34  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 80367158 00363D38  48 01 62 6D */	bl HSD_WObjLoadDesc
/* 8036715C 00363D3C  28 1E 00 00 */	cmplwi r30, 0
/* 80367160 00363D40  3B A3 00 00 */	addi r29, r3, 0
/* 80367164 00363D44  41 82 00 88 */	beq lbl_803671EC
/* 80367168 00363D48  83 9E 00 1C */	lwz r28, 0x1c(r30)
/* 8036716C 00363D4C  28 1C 00 00 */	cmplwi r28, 0
/* 80367170 00363D50  41 82 00 78 */	beq lbl_803671E8
/* 80367174 00363D54  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 80367178 00363D58  A0 9C 00 04 */	lhz r4, 4(r28)
/* 8036717C 00363D5C  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 80367180 00363D60  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 80367184 00363D64  7C 04 00 50 */	subf r0, r4, r0
/* 80367188 00363D68  7C 00 00 34 */	cntlzw r0, r0
/* 8036718C 00363D6C  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 80367190 00363D70  38 BC 00 04 */	addi r5, r28, 4
/* 80367194 00363D74  41 82 00 08 */	beq lbl_8036719C
/* 80367198 00363D78  48 00 00 18 */	b lbl_803671B0
lbl_8036719C:
/* 8036719C 00363D7C  38 64 FF FF */	addi r3, r4, -1
/* 803671A0 00363D80  7C 04 00 D0 */	neg r0, r4
/* 803671A4 00363D84  B0 65 00 00 */	sth r3, 0(r5)
/* 803671A8 00363D88  7C 00 00 34 */	cntlzw r0, r0
/* 803671AC 00363D8C  54 00 D9 7E */	srwi r0, r0, 5
lbl_803671B0:
/* 803671B0 00363D90  2C 00 00 00 */	cmpwi r0, 0
/* 803671B4 00363D94  41 82 00 34 */	beq lbl_803671E8
/* 803671B8 00363D98  28 1C 00 00 */	cmplwi r28, 0
/* 803671BC 00363D9C  41 82 00 2C */	beq lbl_803671E8
/* 803671C0 00363DA0  80 9C 00 00 */	lwz r4, 0(r28)
/* 803671C4 00363DA4  7F 83 E3 78 */	mr r3, r28
/* 803671C8 00363DA8  81 84 00 30 */	lwz r12, 0x30(r4)
/* 803671CC 00363DAC  7D 88 03 A6 */	mtlr r12
/* 803671D0 00363DB0  4E 80 00 21 */	blrl 
/* 803671D4 00363DB4  80 9C 00 00 */	lwz r4, 0(r28)
/* 803671D8 00363DB8  7F 83 E3 78 */	mr r3, r28
/* 803671DC 00363DBC  81 84 00 34 */	lwz r12, 0x34(r4)
/* 803671E0 00363DC0  7D 88 03 A6 */	mtlr r12
/* 803671E4 00363DC4  4E 80 00 21 */	blrl 
lbl_803671E8:
/* 803671E8 00363DC8  93 BE 00 1C */	stw r29, 0x1c(r30)
lbl_803671EC:
/* 803671EC 00363DCC  A0 1F 00 0A */	lhz r0, 0xa(r31)
/* 803671F0 00363DD0  28 00 00 00 */	cmplwi r0, 0
/* 803671F4 00363DD4  41 82 00 60 */	beq lbl_80367254
/* 803671F8 00363DD8  28 1E 00 00 */	cmplwi r30, 0
/* 803671FC 00363DDC  41 82 00 10 */	beq lbl_8036720C
/* 80367200 00363DE0  A0 1E 00 08 */	lhz r0, 8(r30)
/* 80367204 00363DE4  60 00 00 40 */	ori r0, r0, 0x40
/* 80367208 00363DE8  B0 1E 00 08 */	sth r0, 8(r30)
lbl_8036720C:
/* 8036720C 00363DEC  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80367210 00363DF0  28 1E 00 00 */	cmplwi r30, 0
/* 80367214 00363DF4  C0 A3 00 14 */	lfs f5, 0x14(r3)
/* 80367218 00363DF8  C0 83 00 10 */	lfs f4, 0x10(r3)
/* 8036721C 00363DFC  C0 63 00 0C */	lfs f3, 0xc(r3)
/* 80367220 00363E00  C0 43 00 08 */	lfs f2, 8(r3)
/* 80367224 00363E04  C0 23 00 04 */	lfs f1, 4(r3)
/* 80367228 00363E08  C0 03 00 00 */	lfs f0, 0(r3)
/* 8036722C 00363E0C  41 82 00 10 */	beq lbl_8036723C
/* 80367230 00363E10  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 80367234 00363E14  D0 3E 00 24 */	stfs f1, 0x24(r30)
/* 80367238 00363E18  D0 5E 00 28 */	stfs f2, 0x28(r30)
lbl_8036723C:
/* 8036723C 00363E1C  28 1E 00 00 */	cmplwi r30, 0
/* 80367240 00363E20  41 82 00 78 */	beq lbl_803672B8
/* 80367244 00363E24  D0 7E 00 2C */	stfs f3, 0x2c(r30)
/* 80367248 00363E28  D0 9E 00 30 */	stfs f4, 0x30(r30)
/* 8036724C 00363E2C  D0 BE 00 34 */	stfs f5, 0x34(r30)
/* 80367250 00363E30  48 00 00 68 */	b lbl_803672B8
lbl_80367254:
/* 80367254 00363E34  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80367258 00363E38  28 1E 00 00 */	cmplwi r30, 0
/* 8036725C 00363E3C  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80367260 00363E40  C0 23 00 08 */	lfs f1, 8(r3)
/* 80367264 00363E44  C0 03 00 0C */	lfs f0, 0xc(r3)
/* 80367268 00363E48  41 82 00 10 */	beq lbl_80367278
/* 8036726C 00363E4C  D0 1E 00 2C */	stfs f0, 0x2c(r30)
/* 80367270 00363E50  D0 3E 00 28 */	stfs f1, 0x28(r30)
/* 80367274 00363E54  90 1E 00 30 */	stw r0, 0x30(r30)
lbl_80367278:
/* 80367278 00363E58  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 8036727C 00363E5C  28 1E 00 00 */	cmplwi r30, 0
/* 80367280 00363E60  80 03 00 04 */	lwz r0, 4(r3)
/* 80367284 00363E64  C0 03 00 00 */	lfs f0, 0(r3)
/* 80367288 00363E68  41 82 00 30 */	beq lbl_803672B8
/* 8036728C 00363E6C  D0 1E 00 20 */	stfs f0, 0x20(r30)
/* 80367290 00363E70  90 1E 00 24 */	stw r0, 0x24(r30)
/* 80367294 00363E74  48 00 00 24 */	b lbl_803672B8
lbl_80367298:
/* 80367298 00363E78  3C 60 80 40 */	lis r3, lbl_804061D4@ha
/* 8036729C 00363E7C  4C C6 31 82 */	crclr 6
/* 803672A0 00363E80  38 63 61 D4 */	addi r3, r3, lbl_804061D4@l
/* 803672A4 00363E84  4B FD E4 05 */	bl OSReport
/* 803672A8 00363E88  38 6D A6 78 */	addi r3, r13, lbl_804D5D18@sda21
/* 803672AC 00363E8C  38 80 06 4A */	li r4, 0x64a
/* 803672B0 00363E90  38 AD A6 98 */	addi r5, r13, lbl_804D5D38@sda21
/* 803672B4 00363E94  48 02 0F C5 */	bl HSD_Panic
lbl_803672B8:
/* 803672B8 00363E98  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 803672BC 00363E9C  38 60 00 00 */	li r3, 0
/* 803672C0 00363EA0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 803672C4 00363EA4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 803672C8 00363EA8  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 803672CC 00363EAC  83 81 00 18 */	lwz r28, 0x18(r1)
/* 803672D0 00363EB0  38 21 00 28 */	addi r1, r1, 0x28
/* 803672D4 00363EB4  7C 08 03 A6 */	mtlr r0
/* 803672D8 00363EB8  4E 80 00 20 */	blr 

.global func_803672DC
func_803672DC:
/* 803672DC 00363EBC  7C 08 02 A6 */	mflr r0
/* 803672E0 00363EC0  3C 80 80 40 */	lis r4, hsdLObj@ha
/* 803672E4 00363EC4  90 01 00 04 */	stw r0, 4(r1)
/* 803672E8 00363EC8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 803672EC 00363ECC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 803672F0 00363ED0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 803672F4 00363ED4  3B C4 60 C0 */	addi r30, r4, hsdLObj@l
/* 803672F8 00363ED8  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 803672FC 00363EDC  3B A1 00 14 */	addi r29, r1, 0x14
/* 80367300 00363EE0  93 81 00 18 */	stw r28, 0x18(r1)
/* 80367304 00363EE4  3B 83 00 00 */	addi r28, r3, 0
/* 80367308 00363EE8  48 00 00 9C */	b lbl_803673A4
lbl_8036730C:
/* 8036730C 00363EEC  80 7C 00 00 */	lwz r3, 0(r28)
/* 80367310 00363EF0  28 03 00 00 */	cmplwi r3, 0
/* 80367314 00363EF4  41 82 00 10 */	beq lbl_80367324
/* 80367318 00363EF8  48 01 B4 FD */	bl hsdSearchClassInfo
/* 8036731C 00363EFC  28 03 00 00 */	cmplwi r3, 0
/* 80367320 00363F00  40 82 00 3C */	bne lbl_8036735C
lbl_80367324:
/* 80367324 00363F04  80 6D BF 98 */	lwz r3, lbl_804D7638@sda21(r13)
/* 80367328 00363F08  28 03 00 00 */	cmplwi r3, 0
/* 8036732C 00363F0C  41 82 00 08 */	beq lbl_80367334
/* 80367330 00363F10  48 00 00 08 */	b lbl_80367338
lbl_80367334:
/* 80367334 00363F14  7F C3 F3 78 */	mr r3, r30
lbl_80367338:
/* 80367338 00363F18  48 01 B0 0D */	bl hsdNew
/* 8036733C 00363F1C  7C 7F 1B 79 */	or. r31, r3, r3
/* 80367340 00363F20  40 82 00 14 */	bne lbl_80367354
/* 80367344 00363F24  38 6D A6 78 */	addi r3, r13, lbl_804D5D18@sda21
/* 80367348 00363F28  38 80 05 C6 */	li r4, 0x5c6
/* 8036734C 00363F2C  38 AD A6 94 */	addi r5, r13, lbl_804D5D34@sda21
/* 80367350 00363F30  48 02 0E D1 */	bl __assert
lbl_80367354:
/* 80367354 00363F34  93 FD 00 00 */	stw r31, 0(r29)
/* 80367358 00363F38  48 00 00 28 */	b lbl_80367380
lbl_8036735C:
/* 8036735C 00363F3C  48 01 AF E9 */	bl hsdNew
/* 80367360 00363F40  90 7D 00 00 */	stw r3, 0(r29)
/* 80367364 00363F44  80 1D 00 00 */	lwz r0, 0(r29)
/* 80367368 00363F48  28 00 00 00 */	cmplwi r0, 0
/* 8036736C 00363F4C  40 82 00 14 */	bne lbl_80367380
/* 80367370 00363F50  38 6D A6 78 */	addi r3, r13, lbl_804D5D18@sda21
/* 80367374 00363F54  38 80 06 6C */	li r4, 0x66c
/* 80367378 00363F58  38 AD A6 9C */	addi r5, r13, lbl_804D5D3C@sda21
/* 8036737C 00363F5C  48 02 0E A5 */	bl __assert
lbl_80367380:
/* 80367380 00363F60  80 7D 00 00 */	lwz r3, 0(r29)
/* 80367384 00363F64  7F 84 E3 78 */	mr r4, r28
/* 80367388 00363F68  80 A3 00 00 */	lwz r5, 0(r3)
/* 8036738C 00363F6C  81 85 00 3C */	lwz r12, 0x3c(r5)
/* 80367390 00363F70  7D 88 03 A6 */	mtlr r12
/* 80367394 00363F74  4E 80 00 21 */	blrl 
/* 80367398 00363F78  80 7D 00 00 */	lwz r3, 0(r29)
/* 8036739C 00363F7C  83 9C 00 04 */	lwz r28, 4(r28)
/* 803673A0 00363F80  3B A3 00 0C */	addi r29, r3, 0xc
lbl_803673A4:
/* 803673A4 00363F84  28 1C 00 00 */	cmplwi r28, 0
/* 803673A8 00363F88  40 82 FF 64 */	bne lbl_8036730C
/* 803673AC 00363F8C  38 00 00 00 */	li r0, 0
/* 803673B0 00363F90  90 1D 00 00 */	stw r0, 0(r29)
/* 803673B4 00363F94  80 61 00 14 */	lwz r3, 0x14(r1)
/* 803673B8 00363F98  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 803673BC 00363F9C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 803673C0 00363FA0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 803673C4 00363FA4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 803673C8 00363FA8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 803673CC 00363FAC  38 21 00 28 */	addi r1, r1, 0x28
/* 803673D0 00363FB0  7C 08 03 A6 */	mtlr r0
/* 803673D4 00363FB4  4E 80 00 20 */	blr 

.global func_803673D8
func_803673D8:
/* 803673D8 00363FB8  7C 08 02 A6 */	mflr r0
/* 803673DC 00363FBC  28 03 00 00 */	cmplwi r3, 0
/* 803673E0 00363FC0  90 01 00 04 */	stw r0, 4(r1)
/* 803673E4 00363FC4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 803673E8 00363FC8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 803673EC 00363FCC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 803673F0 00363FD0  41 82 00 AC */	beq lbl_8036749C
/* 803673F4 00363FD4  3B E3 00 00 */	addi r31, r3, 0
/* 803673F8 00363FD8  3B C4 00 00 */	addi r30, r4, 0
/* 803673FC 00363FDC  48 00 00 98 */	b lbl_80367494
lbl_80367400:
/* 80367400 00363FE0  28 1F 00 00 */	cmplwi r31, 0
/* 80367404 00363FE4  41 82 00 60 */	beq lbl_80367464
/* 80367408 00363FE8  28 1E 00 00 */	cmplwi r30, 0
/* 8036740C 00363FEC  41 82 00 58 */	beq lbl_80367464
/* 80367410 00363FF0  80 7F 00 48 */	lwz r3, 0x48(r31)
/* 80367414 00363FF4  28 03 00 00 */	cmplwi r3, 0
/* 80367418 00363FF8  41 82 00 08 */	beq lbl_80367420
/* 8036741C 00363FFC  4B FF D0 B1 */	bl HSD_AObjRemove
lbl_80367420:
/* 80367420 00364000  80 7E 00 04 */	lwz r3, 4(r30)
/* 80367424 00364004  4B FF CF 79 */	bl HSD_AObjLoadDesc
/* 80367428 00364008  28 1F 00 00 */	cmplwi r31, 0
/* 8036742C 0036400C  90 7F 00 48 */	stw r3, 0x48(r31)
/* 80367430 00364010  41 82 00 0C */	beq lbl_8036743C
/* 80367434 00364014  80 7F 00 18 */	lwz r3, 0x18(r31)
/* 80367438 00364018  48 00 00 08 */	b lbl_80367440
lbl_8036743C:
/* 8036743C 0036401C  38 60 00 00 */	li r3, 0
lbl_80367440:
/* 80367440 00364020  80 9E 00 08 */	lwz r4, 8(r30)
/* 80367444 00364024  48 01 5C A1 */	bl HSD_WObjAddAnim
/* 80367448 00364028  28 1F 00 00 */	cmplwi r31, 0
/* 8036744C 0036402C  41 82 00 0C */	beq lbl_80367458
/* 80367450 00364030  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80367454 00364034  48 00 00 08 */	b lbl_8036745C
lbl_80367458:
/* 80367458 00364038  38 60 00 00 */	li r3, 0
lbl_8036745C:
/* 8036745C 0036403C  80 9E 00 0C */	lwz r4, 0xc(r30)
/* 80367460 00364040  48 01 5C 85 */	bl HSD_WObjAddAnim
lbl_80367464:
/* 80367464 00364044  28 1F 00 00 */	cmplwi r31, 0
/* 80367468 00364048  41 82 00 0C */	beq lbl_80367474
/* 8036746C 0036404C  80 1F 00 0C */	lwz r0, 0xc(r31)
/* 80367470 00364050  48 00 00 08 */	b lbl_80367478
lbl_80367474:
/* 80367474 00364054  38 00 00 00 */	li r0, 0
lbl_80367478:
/* 80367478 00364058  28 1E 00 00 */	cmplwi r30, 0
/* 8036747C 0036405C  7C 1F 03 78 */	mr r31, r0
/* 80367480 00364060  41 82 00 0C */	beq lbl_8036748C
/* 80367484 00364064  80 1E 00 00 */	lwz r0, 0(r30)
/* 80367488 00364068  48 00 00 08 */	b lbl_80367490
lbl_8036748C:
/* 8036748C 0036406C  38 00 00 00 */	li r0, 0
lbl_80367490:
/* 80367490 00364070  7C 1E 03 78 */	mr r30, r0
lbl_80367494:
/* 80367494 00364074  28 1F 00 00 */	cmplwi r31, 0
/* 80367498 00364078  40 82 FF 68 */	bne lbl_80367400
lbl_8036749C:
/* 8036749C 0036407C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803674A0 00364080  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 803674A4 00364084  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 803674A8 00364088  38 21 00 18 */	addi r1, r1, 0x18
/* 803674AC 0036408C  7C 08 03 A6 */	mtlr r0
/* 803674B0 00364090  4E 80 00 20 */	blr 
LObjRelease:
/* 803674B4 00364094  7C 08 02 A6 */	mflr r0
/* 803674B8 00364098  90 01 00 04 */	stw r0, 4(r1)
/* 803674BC 0036409C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 803674C0 003640A0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 803674C4 003640A4  7C 7F 1B 78 */	mr r31, r3
/* 803674C8 003640A8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 803674CC 003640AC  80 63 00 48 */	lwz r3, 0x48(r3)
/* 803674D0 003640B0  4B FF CF FD */	bl HSD_AObjRemove
/* 803674D4 003640B4  28 1F 00 00 */	cmplwi r31, 0
/* 803674D8 003640B8  41 82 00 0C */	beq lbl_803674E4
/* 803674DC 003640BC  83 DF 00 18 */	lwz r30, 0x18(r31)
/* 803674E0 003640C0  48 00 00 08 */	b lbl_803674E8
lbl_803674E4:
/* 803674E4 003640C4  3B C0 00 00 */	li r30, 0
lbl_803674E8:
/* 803674E8 003640C8  28 1E 00 00 */	cmplwi r30, 0
/* 803674EC 003640CC  41 82 00 78 */	beq lbl_80367564
/* 803674F0 003640D0  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 803674F4 003640D4  A0 9E 00 04 */	lhz r4, 4(r30)
/* 803674F8 003640D8  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 803674FC 003640DC  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 80367500 003640E0  7C 04 00 50 */	subf r0, r4, r0
/* 80367504 003640E4  7C 00 00 34 */	cntlzw r0, r0
/* 80367508 003640E8  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 8036750C 003640EC  38 BE 00 04 */	addi r5, r30, 4
/* 80367510 003640F0  41 82 00 08 */	beq lbl_80367518
/* 80367514 003640F4  48 00 00 18 */	b lbl_8036752C
lbl_80367518:
/* 80367518 003640F8  38 64 FF FF */	addi r3, r4, -1
/* 8036751C 003640FC  7C 04 00 D0 */	neg r0, r4
/* 80367520 00364100  B0 65 00 00 */	sth r3, 0(r5)
/* 80367524 00364104  7C 00 00 34 */	cntlzw r0, r0
/* 80367528 00364108  54 00 D9 7E */	srwi r0, r0, 5
lbl_8036752C:
/* 8036752C 0036410C  2C 00 00 00 */	cmpwi r0, 0
/* 80367530 00364110  41 82 00 34 */	beq lbl_80367564
/* 80367534 00364114  28 1E 00 00 */	cmplwi r30, 0
/* 80367538 00364118  41 82 00 2C */	beq lbl_80367564
/* 8036753C 0036411C  80 9E 00 00 */	lwz r4, 0(r30)
/* 80367540 00364120  7F C3 F3 78 */	mr r3, r30
/* 80367544 00364124  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80367548 00364128  7D 88 03 A6 */	mtlr r12
/* 8036754C 0036412C  4E 80 00 21 */	blrl 
/* 80367550 00364130  80 9E 00 00 */	lwz r4, 0(r30)
/* 80367554 00364134  7F C3 F3 78 */	mr r3, r30
/* 80367558 00364138  81 84 00 34 */	lwz r12, 0x34(r4)
/* 8036755C 0036413C  7D 88 03 A6 */	mtlr r12
/* 80367560 00364140  4E 80 00 21 */	blrl 
lbl_80367564:
/* 80367564 00364144  28 1F 00 00 */	cmplwi r31, 0
/* 80367568 00364148  41 82 00 0C */	beq lbl_80367574
/* 8036756C 0036414C  83 DF 00 1C */	lwz r30, 0x1c(r31)
/* 80367570 00364150  48 00 00 08 */	b lbl_80367578
lbl_80367574:
/* 80367574 00364154  3B C0 00 00 */	li r30, 0
lbl_80367578:
/* 80367578 00364158  28 1E 00 00 */	cmplwi r30, 0
/* 8036757C 0036415C  41 82 00 78 */	beq lbl_803675F4
/* 80367580 00364160  3C 60 00 01 */	lis r3, 0x0000FFFF@ha
/* 80367584 00364164  A0 9E 00 04 */	lhz r4, 4(r30)
/* 80367588 00364168  38 03 FF FF */	addi r0, r3, 0x0000FFFF@l
/* 8036758C 0036416C  54 00 04 3E */	clrlwi r0, r0, 0x10
/* 80367590 00364170  7C 04 00 50 */	subf r0, r4, r0
/* 80367594 00364174  7C 00 00 34 */	cntlzw r0, r0
/* 80367598 00364178  54 00 D9 7F */	rlwinm. r0, r0, 0x1b, 5, 0x1f
/* 8036759C 0036417C  38 BE 00 04 */	addi r5, r30, 4
/* 803675A0 00364180  41 82 00 08 */	beq lbl_803675A8
/* 803675A4 00364184  48 00 00 18 */	b lbl_803675BC
lbl_803675A8:
/* 803675A8 00364188  38 64 FF FF */	addi r3, r4, -1
/* 803675AC 0036418C  7C 04 00 D0 */	neg r0, r4
/* 803675B0 00364190  B0 65 00 00 */	sth r3, 0(r5)
/* 803675B4 00364194  7C 00 00 34 */	cntlzw r0, r0
/* 803675B8 00364198  54 00 D9 7E */	srwi r0, r0, 5
lbl_803675BC:
/* 803675BC 0036419C  2C 00 00 00 */	cmpwi r0, 0
/* 803675C0 003641A0  41 82 00 34 */	beq lbl_803675F4
/* 803675C4 003641A4  28 1E 00 00 */	cmplwi r30, 0
/* 803675C8 003641A8  41 82 00 2C */	beq lbl_803675F4
/* 803675CC 003641AC  80 9E 00 00 */	lwz r4, 0(r30)
/* 803675D0 003641B0  7F C3 F3 78 */	mr r3, r30
/* 803675D4 003641B4  81 84 00 30 */	lwz r12, 0x30(r4)
/* 803675D8 003641B8  7D 88 03 A6 */	mtlr r12
/* 803675DC 003641BC  4E 80 00 21 */	blrl 
/* 803675E0 003641C0  80 9E 00 00 */	lwz r4, 0(r30)
/* 803675E4 003641C4  7F C3 F3 78 */	mr r3, r30
/* 803675E8 003641C8  81 84 00 34 */	lwz r12, 0x34(r4)
/* 803675EC 003641CC  7D 88 03 A6 */	mtlr r12
/* 803675F0 003641D0  4E 80 00 21 */	blrl 
lbl_803675F4:
/* 803675F4 003641D4  3C 60 80 40 */	lis r3, hsdLObj@ha
/* 803675F8 003641D8  38 63 60 C0 */	addi r3, r3, hsdLObj@l
/* 803675FC 003641DC  80 83 00 14 */	lwz r4, 0x14(r3)
/* 80367600 003641E0  7F E3 FB 78 */	mr r3, r31
/* 80367604 003641E4  81 84 00 30 */	lwz r12, 0x30(r4)
/* 80367608 003641E8  7D 88 03 A6 */	mtlr r12
/* 8036760C 003641EC  4E 80 00 21 */	blrl 
/* 80367610 003641F0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80367614 003641F4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80367618 003641F8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8036761C 003641FC  38 21 00 20 */	addi r1, r1, 0x20
/* 80367620 00364200  7C 08 03 A6 */	mtlr r0
/* 80367624 00364204  4E 80 00 20 */	blr 
LObjAmnesia:
/* 80367628 00364208  7C 08 02 A6 */	mflr r0
/* 8036762C 0036420C  90 01 00 04 */	stw r0, 4(r1)
/* 80367630 00364210  94 21 FF F8 */	stwu r1, -8(r1)
/* 80367634 00364214  80 0D BF 98 */	lwz r0, lbl_804D7638@sda21(r13)
/* 80367638 00364218  7C 03 00 40 */	cmplw r3, r0
/* 8036763C 0036421C  40 82 00 0C */	bne lbl_80367648
/* 80367640 00364220  38 00 00 00 */	li r0, 0
/* 80367644 00364224  90 0D BF 98 */	stw r0, lbl_804D7638@sda21(r13)
lbl_80367648:
/* 80367648 00364228  3C 80 80 40 */	lis r4, hsdLObj@ha
/* 8036764C 0036422C  38 04 60 C0 */	addi r0, r4, hsdLObj@l
/* 80367650 00364230  7C 03 00 40 */	cmplw r3, r0
/* 80367654 00364234  40 82 00 0C */	bne lbl_80367660
/* 80367658 00364238  38 00 00 00 */	li r0, 0
/* 8036765C 0036423C  90 0D BF 9C */	stw r0, lbl_804D763C@sda21(r13)
lbl_80367660:
/* 80367660 00364240  3C 80 80 40 */	lis r4, hsdLObj@ha
/* 80367664 00364244  38 84 60 C0 */	addi r4, r4, hsdLObj@l
/* 80367668 00364248  80 84 00 14 */	lwz r4, 0x14(r4)
/* 8036766C 0036424C  81 84 00 38 */	lwz r12, 0x38(r4)
/* 80367670 00364250  7D 88 03 A6 */	mtlr r12
/* 80367674 00364254  4E 80 00 21 */	blrl 
/* 80367678 00364258  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8036767C 0036425C  38 21 00 08 */	addi r1, r1, 8
/* 80367680 00364260  7C 08 03 A6 */	mtlr r0
/* 80367684 00364264  4E 80 00 20 */	blr 

.global LObjInfoInit
LObjInfoInit:
/* 80367688 00364268  7C 08 02 A6 */	mflr r0
/* 8036768C 0036426C  3C 60 80 40 */	lis r3, hsdLObj@ha
/* 80367690 00364270  90 01 00 04 */	stw r0, 4(r1)
/* 80367694 00364274  38 E0 00 40 */	li r7, 0x40
/* 80367698 00364278  39 00 00 D4 */	li r8, 0xd4
/* 8036769C 0036427C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 803676A0 00364280  93 E1 00 0C */	stw r31, 0xc(r1)
/* 803676A4 00364284  3B E3 60 C0 */	addi r31, r3, hsdLObj@l
/* 803676A8 00364288  3C 60 80 40 */	lis r3, hsdObj@ha
/* 803676AC 0036428C  38 83 72 A8 */	addi r4, r3, hsdObj@l
/* 803676B0 00364290  38 7F 00 00 */	addi r3, r31, 0
/* 803676B4 00364294  38 BF 01 38 */	addi r5, r31, 0x138
/* 803676B8 00364298  38 DF 01 50 */	addi r6, r31, 0x150
/* 803676BC 0036429C  48 01 A5 5D */	bl hsdInitClassInfo
/* 803676C0 003642A0  3C 60 80 36 */	lis r3, LObjRelease@ha
/* 803676C4 003642A4  38 03 74 B4 */	addi r0, r3, LObjRelease@l
/* 803676C8 003642A8  3C 60 80 36 */	lis r3, LObjAmnesia@ha
/* 803676CC 003642AC  90 1F 00 30 */	stw r0, 0x30(r31)
/* 803676D0 003642B0  38 03 76 28 */	addi r0, r3, LObjAmnesia@l
/* 803676D4 003642B4  3C 60 80 36 */	lis r3, LObjLoad@ha
/* 803676D8 003642B8  90 1F 00 38 */	stw r0, 0x38(r31)
/* 803676DC 003642BC  38 03 6E A8 */	addi r0, r3, LObjLoad@l
/* 803676E0 003642C0  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 803676E4 003642C4  80 01 00 14 */	lwz r0, 0x14(r1)
/* 803676E8 003642C8  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 803676EC 003642CC  38 21 00 10 */	addi r1, r1, 0x10
/* 803676F0 003642D0  7C 08 03 A6 */	mtlr r0
/* 803676F4 003642D4  4E 80 00 20 */	blr 


.section .data
    .balign 4
    .asciz "hsdIsDescendantOf(info, &hsdLObj)"
    .balign 4
.global lbl_804061D4
lbl_804061D4:
    .asciz "unexpected lightdesc flags (%x)\n"
    .balign 4
    .asciz "sysdolphin_base_library"
    .balign 4
    .asciz "hsd_lobj"
    .balign 4


.section .sdata
    .balign 8
.global lbl_804D5D18
lbl_804D5D18:
    .asciz "lobj.c"
    .balign 4
.global lbl_804D5D20
lbl_804D5D20:
    .asciz "0"
    .balign 4
.global lbl_804D5D24
lbl_804D5D24:
    .asciz "lobj"
    .balign 4
.global lbl_804D5D2C
lbl_804D5D2C:
    .asciz "lobj.h"
    .balign 4
.global lbl_804D5D34
lbl_804D5D34:
    .asciz "new"
    .balign 4
.global lbl_804D5D38
lbl_804D5D38:
	.4byte NULL
.global lbl_804D5D3C
lbl_804D5D3C:
    .asciz "*p"
    .balign 4


.section .sbss
    .balign 8
.global lbl_804D7638
lbl_804D7638:
	.skip 0x4
.global lbl_804D763C
lbl_804D763C:
	.skip 0x4
.global nb_active_lights
nb_active_lights:
	.skip 0x4
.global lightmask_diffuse
lightmask_diffuse:
	.skip 0x4
.global lightmask_specular
lightmask_specular:
	.skip 0x4
.global lightmask_attnfunc
lightmask_attnfunc:
	.skip 0x4
.global lightmask_alpha
lightmask_alpha:
	.skip 0x4
