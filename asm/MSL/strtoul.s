.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_80325B24
func_80325B24:
/* 80325B24 00322704  7C 08 02 A6 */	mflr r0
/* 80325B28 00322708  3C C0 80 00 */	lis r6, 0x7FFFFFFF@ha
/* 80325B2C 0032270C  90 01 00 04 */	stw r0, 4(r1)
/* 80325B30 00322710  38 00 00 00 */	li r0, 0
/* 80325B34 00322714  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80325B38 00322718  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80325B3C 0032271C  3B E4 00 00 */	addi r31, r4, 0
/* 80325B40 00322720  38 86 FF FF */	addi r4, r6, 0x7FFFFFFF@l
/* 80325B44 00322724  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80325B48 00322728  7C 7E 1B 78 */	mr r30, r3
/* 80325B4C 0032272C  3C 60 80 32 */	lis r3, __StringRead@ha
/* 80325B50 00322730  93 C1 00 14 */	stw r30, 0x14(r1)
/* 80325B54 00322734  38 C1 00 14 */	addi r6, r1, 0x14
/* 80325B58 00322738  38 E1 00 24 */	addi r7, r1, 0x24
/* 80325B5C 0032273C  90 01 00 18 */	stw r0, 0x18(r1)
/* 80325B60 00322740  38 03 57 E8 */	addi r0, r3, __StringRead@l
/* 80325B64 00322744  38 65 00 00 */	addi r3, r5, 0
/* 80325B68 00322748  7C 05 03 78 */	mr r5, r0
/* 80325B6C 0032274C  39 01 00 20 */	addi r8, r1, 0x20
/* 80325B70 00322750  39 21 00 1C */	addi r9, r1, 0x1c
/* 80325B74 00322754  48 00 00 5D */	bl func_80325BD0
/* 80325B78 00322758  28 1F 00 00 */	cmplwi r31, 0
/* 80325B7C 0032275C  41 82 00 10 */	beq lbl_80325B8C
/* 80325B80 00322760  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80325B84 00322764  7C 1E 02 14 */	add r0, r30, r0
/* 80325B88 00322768  90 1F 00 00 */	stw r0, 0(r31)
lbl_80325B8C:
/* 80325B8C 0032276C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80325B90 00322770  2C 00 00 00 */	cmpwi r0, 0
/* 80325B94 00322774  41 82 00 14 */	beq lbl_80325BA8
/* 80325B98 00322778  38 00 00 22 */	li r0, 0x22
/* 80325B9C 0032277C  90 0D B9 D8 */	stw r0, lbl_804D7078@sda21(r13)
/* 80325BA0 00322780  38 60 FF FF */	li r3, -1
/* 80325BA4 00322784  48 00 00 14 */	b lbl_80325BB8
lbl_80325BA8:
/* 80325BA8 00322788  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80325BAC 0032278C  2C 00 00 00 */	cmpwi r0, 0
/* 80325BB0 00322790  41 82 00 08 */	beq lbl_80325BB8
/* 80325BB4 00322794  7C 63 00 D0 */	neg r3, r3
lbl_80325BB8:
/* 80325BB8 00322798  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80325BBC 0032279C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80325BC0 003227A0  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80325BC4 003227A4  7C 08 03 A6 */	mtlr r0
/* 80325BC8 003227A8  38 21 00 30 */	addi r1, r1, 0x30
/* 80325BCC 003227AC  4E 80 00 20 */	blr

.global func_80325BD0
func_80325BD0:
/* 80325BD0 003227B0  7C 08 02 A6 */	mflr r0
/* 80325BD4 003227B4  90 01 00 04 */	stw r0, 4(r1)
/* 80325BD8 003227B8  38 00 00 00 */	li r0, 0
/* 80325BDC 003227BC  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80325BE0 003227C0  BE 41 00 28 */	stmw r18, 0x28(r1)
/* 80325BE4 003227C4  7C 7C 1B 79 */	or. r28, r3, r3
/* 80325BE8 003227C8  3A E9 00 00 */	addi r23, r9, 0
/* 80325BEC 003227CC  7D 15 43 78 */	mr r21, r8
/* 80325BF0 003227D0  3A C4 00 00 */	addi r22, r4, 0
/* 80325BF4 003227D4  3B A5 00 00 */	addi r29, r5, 0
/* 80325BF8 003227D8  3B C6 00 00 */	addi r30, r6, 0
/* 80325BFC 003227DC  3A 67 00 00 */	addi r19, r7, 0
/* 80325C00 003227E0  3B 00 00 01 */	li r24, 1
/* 80325C04 003227E4  3B E0 00 00 */	li r31, 0
/* 80325C08 003227E8  3B 60 00 00 */	li r27, 0
/* 80325C0C 003227EC  3B 40 00 00 */	li r26, 0
/* 80325C10 003227F0  90 09 00 00 */	stw r0, 0(r9)
/* 80325C14 003227F4  90 08 00 00 */	stw r0, 0(r8)
/* 80325C18 003227F8  41 80 00 1C */	blt lbl_80325C34
/* 80325C1C 003227FC  2C 1C 00 01 */	cmpwi r28, 1
/* 80325C20 00322800  41 82 00 14 */	beq lbl_80325C34
/* 80325C24 00322804  2C 1C 00 24 */	cmpwi r28, 0x24
/* 80325C28 00322808  41 81 00 0C */	bgt lbl_80325C34
/* 80325C2C 0032280C  2C 16 00 01 */	cmpwi r22, 1
/* 80325C30 00322810  40 80 00 0C */	bge lbl_80325C3C
lbl_80325C34:
/* 80325C34 00322814  3B 00 00 40 */	li r24, 0x40
/* 80325C38 00322818  48 00 00 24 */	b lbl_80325C5C
lbl_80325C3C:
/* 80325C3C 0032281C  39 9D 00 00 */	addi r12, r29, 0
/* 80325C40 00322820  7D 88 03 A6 */	mtlr r12
/* 80325C44 00322824  38 7E 00 00 */	addi r3, r30, 0
/* 80325C48 00322828  3B E0 00 01 */	li r31, 1
/* 80325C4C 0032282C  38 80 00 00 */	li r4, 0
/* 80325C50 00322830  38 A0 00 00 */	li r5, 0
/* 80325C54 00322834  4E 80 00 21 */	blrl
/* 80325C58 00322838  7C 72 1B 78 */	mr r18, r3
lbl_80325C5C:
/* 80325C5C 0032283C  2C 1C 00 00 */	cmpwi r28, 0
/* 80325C60 00322840  41 82 00 0C */	beq lbl_80325C6C
/* 80325C64 00322844  38 00 FF FF */	li r0, -1
/* 80325C68 00322848  7F 40 E3 96 */	divwu r26, r0, r28
lbl_80325C6C:
/* 80325C6C 0032284C  3C 60 80 3C */	lis r3, lbl_803B8C30@ha
/* 80325C70 00322850  3C 80 80 40 */	lis r4, lbl_80400728@ha
/* 80325C74 00322854  3B 23 8C 30 */	addi r25, r3, lbl_803B8C30@l
/* 80325C78 00322858  3A 84 07 28 */	addi r20, r4, lbl_80400728@l
/* 80325C7C 0032285C  48 00 02 38 */	b lbl_80325EB4
lbl_80325C80:
/* 80325C80 00322860  28 18 00 10 */	cmplwi r24, 0x10
/* 80325C84 00322864  41 81 02 30 */	bgt lbl_80325EB4
/* 80325C88 00322868  57 00 10 3A */	slwi r0, r24, 2
/* 80325C8C 0032286C  7C 14 00 2E */	lwzx r0, r20, r0
/* 80325C90 00322870  7C 09 03 A6 */	mtctr r0
/* 80325C94 00322874  4E 80 04 20 */	bctr
.global lbl_80325C98
lbl_80325C98:
/* 80325C98 00322878  56 40 06 3E */	clrlwi r0, r18, 0x18
/* 80325C9C 0032287C  7C 79 02 14 */	add r3, r25, r0
/* 80325CA0 00322880  88 03 00 00 */	lbz r0, 0(r3)
/* 80325CA4 00322884  54 00 07 7D */	rlwinm. r0, r0, 0, 0x1d, 0x1e
/* 80325CA8 00322888  41 82 00 28 */	beq lbl_80325CD0
/* 80325CAC 0032288C  39 9D 00 00 */	addi r12, r29, 0
/* 80325CB0 00322890  7D 88 03 A6 */	mtlr r12
/* 80325CB4 00322894  38 7E 00 00 */	addi r3, r30, 0
/* 80325CB8 00322898  38 80 00 00 */	li r4, 0
/* 80325CBC 0032289C  38 A0 00 00 */	li r5, 0
/* 80325CC0 003228A0  3B FF 00 01 */	addi r31, r31, 1
/* 80325CC4 003228A4  4E 80 00 21 */	blrl
/* 80325CC8 003228A8  7C 72 1B 78 */	mr r18, r3
/* 80325CCC 003228AC  48 00 01 E8 */	b lbl_80325EB4
lbl_80325CD0:
/* 80325CD0 003228B0  2C 12 00 2B */	cmpwi r18, 0x2b
/* 80325CD4 003228B4  40 82 00 28 */	bne lbl_80325CFC
/* 80325CD8 003228B8  39 9D 00 00 */	addi r12, r29, 0
/* 80325CDC 003228BC  7D 88 03 A6 */	mtlr r12
/* 80325CE0 003228C0  38 7E 00 00 */	addi r3, r30, 0
/* 80325CE4 003228C4  38 80 00 00 */	li r4, 0
/* 80325CE8 003228C8  38 A0 00 00 */	li r5, 0
/* 80325CEC 003228CC  3B FF 00 01 */	addi r31, r31, 1
/* 80325CF0 003228D0  4E 80 00 21 */	blrl
/* 80325CF4 003228D4  7C 72 1B 78 */	mr r18, r3
/* 80325CF8 003228D8  48 00 00 34 */	b lbl_80325D2C
lbl_80325CFC:
/* 80325CFC 003228DC  2C 12 00 2D */	cmpwi r18, 0x2d
/* 80325D00 003228E0  40 82 00 2C */	bne lbl_80325D2C
/* 80325D04 003228E4  39 9D 00 00 */	addi r12, r29, 0
/* 80325D08 003228E8  7D 88 03 A6 */	mtlr r12
/* 80325D0C 003228EC  38 7E 00 00 */	addi r3, r30, 0
/* 80325D10 003228F0  38 80 00 00 */	li r4, 0
/* 80325D14 003228F4  38 A0 00 00 */	li r5, 0
/* 80325D18 003228F8  3B FF 00 01 */	addi r31, r31, 1
/* 80325D1C 003228FC  4E 80 00 21 */	blrl
/* 80325D20 00322900  38 00 00 01 */	li r0, 1
/* 80325D24 00322904  90 15 00 00 */	stw r0, 0(r21)
/* 80325D28 00322908  7C 72 1B 78 */	mr r18, r3
lbl_80325D2C:
/* 80325D2C 0032290C  3B 00 00 02 */	li r24, 2
/* 80325D30 00322910  48 00 01 84 */	b lbl_80325EB4
.global lbl_80325D34
lbl_80325D34:
/* 80325D34 00322914  2C 1C 00 00 */	cmpwi r28, 0
/* 80325D38 00322918  41 82 00 0C */	beq lbl_80325D44
/* 80325D3C 0032291C  2C 1C 00 10 */	cmpwi r28, 0x10
/* 80325D40 00322920  40 82 00 34 */	bne lbl_80325D74
lbl_80325D44:
/* 80325D44 00322924  2C 12 00 30 */	cmpwi r18, 0x30
/* 80325D48 00322928  40 82 00 2C */	bne lbl_80325D74
/* 80325D4C 0032292C  39 9D 00 00 */	addi r12, r29, 0
/* 80325D50 00322930  7D 88 03 A6 */	mtlr r12
/* 80325D54 00322934  38 7E 00 00 */	addi r3, r30, 0
/* 80325D58 00322938  3B 00 00 04 */	li r24, 4
/* 80325D5C 0032293C  38 80 00 00 */	li r4, 0
/* 80325D60 00322940  38 A0 00 00 */	li r5, 0
/* 80325D64 00322944  3B FF 00 01 */	addi r31, r31, 1
/* 80325D68 00322948  4E 80 00 21 */	blrl
/* 80325D6C 0032294C  7C 72 1B 78 */	mr r18, r3
/* 80325D70 00322950  48 00 01 44 */	b lbl_80325EB4
lbl_80325D74:
/* 80325D74 00322954  3B 00 00 08 */	li r24, 8
/* 80325D78 00322958  48 00 01 3C */	b lbl_80325EB4
.global lbl_80325D7C
lbl_80325D7C:
/* 80325D7C 0032295C  2C 12 00 58 */	cmpwi r18, 0x58
/* 80325D80 00322960  41 82 00 0C */	beq lbl_80325D8C
/* 80325D84 00322964  2C 12 00 78 */	cmpwi r18, 0x78
/* 80325D88 00322968  40 82 00 30 */	bne lbl_80325DB8
lbl_80325D8C:
/* 80325D8C 0032296C  39 9D 00 00 */	addi r12, r29, 0
/* 80325D90 00322970  7D 88 03 A6 */	mtlr r12
/* 80325D94 00322974  38 7E 00 00 */	addi r3, r30, 0
/* 80325D98 00322978  3B 80 00 10 */	li r28, 0x10
/* 80325D9C 0032297C  3B 00 00 08 */	li r24, 8
/* 80325DA0 00322980  38 80 00 00 */	li r4, 0
/* 80325DA4 00322984  38 A0 00 00 */	li r5, 0
/* 80325DA8 00322988  3B FF 00 01 */	addi r31, r31, 1
/* 80325DAC 0032298C  4E 80 00 21 */	blrl
/* 80325DB0 00322990  7C 72 1B 78 */	mr r18, r3
/* 80325DB4 00322994  48 00 01 00 */	b lbl_80325EB4
lbl_80325DB8:
/* 80325DB8 00322998  2C 1C 00 00 */	cmpwi r28, 0
/* 80325DBC 0032299C  40 82 00 08 */	bne lbl_80325DC4
/* 80325DC0 003229A0  3B 80 00 08 */	li r28, 8
lbl_80325DC4:
/* 80325DC4 003229A4  3B 00 00 10 */	li r24, 0x10
/* 80325DC8 003229A8  48 00 00 EC */	b lbl_80325EB4
.global lbl_80325DCC
lbl_80325DCC:
/* 80325DCC 003229AC  2C 1C 00 00 */	cmpwi r28, 0
/* 80325DD0 003229B0  40 82 00 08 */	bne lbl_80325DD8
/* 80325DD4 003229B4  3B 80 00 0A */	li r28, 0xa
lbl_80325DD8:
/* 80325DD8 003229B8  28 1A 00 00 */	cmplwi r26, 0
/* 80325DDC 003229BC  40 82 00 0C */	bne lbl_80325DE8
/* 80325DE0 003229C0  38 00 FF FF */	li r0, -1
/* 80325DE4 003229C4  7F 40 E3 96 */	divwu r26, r0, r28
lbl_80325DE8:
/* 80325DE8 003229C8  56 40 06 3E */	clrlwi r0, r18, 0x18
/* 80325DEC 003229CC  7C 79 02 14 */	add r3, r25, r0
/* 80325DF0 003229D0  88 63 00 00 */	lbz r3, 0(r3)
/* 80325DF4 003229D4  54 60 06 F7 */	rlwinm. r0, r3, 0, 0x1b, 0x1b
/* 80325DF8 003229D8  41 82 00 2C */	beq lbl_80325E24
/* 80325DFC 003229DC  3A 52 FF D0 */	addi r18, r18, -48
/* 80325E00 003229E0  7C 12 E0 00 */	cmpw r18, r28
/* 80325E04 003229E4  41 80 00 60 */	blt lbl_80325E64
/* 80325E08 003229E8  2C 18 00 10 */	cmpwi r24, 0x10
/* 80325E0C 003229EC  40 82 00 0C */	bne lbl_80325E18
/* 80325E10 003229F0  3B 00 00 20 */	li r24, 0x20
/* 80325E14 003229F4  48 00 00 08 */	b lbl_80325E1C
lbl_80325E18:
/* 80325E18 003229F8  3B 00 00 40 */	li r24, 0x40
lbl_80325E1C:
/* 80325E1C 003229FC  3A 52 00 30 */	addi r18, r18, 0x30
/* 80325E20 00322A00  48 00 00 94 */	b lbl_80325EB4
lbl_80325E24:
/* 80325E24 00322A04  54 60 06 33 */	rlwinm. r0, r3, 0, 0x18, 0x19
/* 80325E28 00322A08  41 82 00 18 */	beq lbl_80325E40
/* 80325E2C 00322A0C  7E 43 93 78 */	mr r3, r18
/* 80325E30 00322A10  4B FF D7 31 */	bl toupper
/* 80325E34 00322A14  38 03 FF C9 */	addi r0, r3, -55
/* 80325E38 00322A18  7C 00 E0 00 */	cmpw r0, r28
/* 80325E3C 00322A1C  41 80 00 1C */	blt lbl_80325E58
lbl_80325E40:
/* 80325E40 00322A20  2C 18 00 10 */	cmpwi r24, 0x10
/* 80325E44 00322A24  40 82 00 0C */	bne lbl_80325E50
/* 80325E48 00322A28  3B 00 00 20 */	li r24, 0x20
/* 80325E4C 00322A2C  48 00 00 68 */	b lbl_80325EB4
lbl_80325E50:
/* 80325E50 00322A30  3B 00 00 40 */	li r24, 0x40
/* 80325E54 00322A34  48 00 00 60 */	b lbl_80325EB4
lbl_80325E58:
/* 80325E58 00322A38  7E 43 93 78 */	mr r3, r18
/* 80325E5C 00322A3C  4B FF D7 05 */	bl toupper
/* 80325E60 00322A40  3A 43 FF C9 */	addi r18, r3, -55
lbl_80325E64:
/* 80325E64 00322A44  7C 1B D0 40 */	cmplw r27, r26
/* 80325E68 00322A48  40 81 00 0C */	ble lbl_80325E74
/* 80325E6C 00322A4C  38 00 00 01 */	li r0, 1
/* 80325E70 00322A50  90 17 00 00 */	stw r0, 0(r23)
lbl_80325E74:
/* 80325E74 00322A54  7F 7B E1 D6 */	mullw r27, r27, r28
/* 80325E78 00322A58  20 1B FF FF */	subfic r0, r27, -1
/* 80325E7C 00322A5C  7C 12 00 40 */	cmplw r18, r0
/* 80325E80 00322A60  40 81 00 0C */	ble lbl_80325E8C
/* 80325E84 00322A64  38 00 00 01 */	li r0, 1
/* 80325E88 00322A68  90 17 00 00 */	stw r0, 0(r23)
lbl_80325E8C:
/* 80325E8C 00322A6C  39 9D 00 00 */	addi r12, r29, 0
/* 80325E90 00322A70  7D 88 03 A6 */	mtlr r12
/* 80325E94 00322A74  38 7E 00 00 */	addi r3, r30, 0
/* 80325E98 00322A78  7F 7B 92 14 */	add r27, r27, r18
/* 80325E9C 00322A7C  3B 00 00 10 */	li r24, 0x10
/* 80325EA0 00322A80  38 80 00 00 */	li r4, 0
/* 80325EA4 00322A84  38 A0 00 00 */	li r5, 0
/* 80325EA8 00322A88  3B FF 00 01 */	addi r31, r31, 1
/* 80325EAC 00322A8C  4E 80 00 21 */	blrl
/* 80325EB0 00322A90  7C 72 1B 78 */	mr r18, r3
.global lbl_80325EB4
lbl_80325EB4:
/* 80325EB4 00322A94  7C 1F B0 00 */	cmpw r31, r22
/* 80325EB8 00322A98  41 81 00 14 */	bgt lbl_80325ECC
/* 80325EBC 00322A9C  2C 12 FF FF */	cmpwi r18, -1
/* 80325EC0 00322AA0  41 82 00 0C */	beq lbl_80325ECC
/* 80325EC4 00322AA4  57 00 06 75 */	rlwinm. r0, r24, 0, 0x19, 0x1a
/* 80325EC8 00322AA8  41 82 FD B8 */	beq lbl_80325C80
lbl_80325ECC:
/* 80325ECC 00322AAC  73 00 00 34 */	andi. r0, r24, 0x34
/* 80325ED0 00322AB0  40 82 00 10 */	bne lbl_80325EE0
/* 80325ED4 00322AB4  3B 60 00 00 */	li r27, 0
/* 80325ED8 00322AB8  3B E0 00 00 */	li r31, 0
/* 80325EDC 00322ABC  48 00 00 08 */	b lbl_80325EE4
lbl_80325EE0:
/* 80325EE0 00322AC0  3B FF FF FF */	addi r31, r31, -1
lbl_80325EE4:
/* 80325EE4 00322AC4  7F AC EB 78 */	mr r12, r29
/* 80325EE8 00322AC8  93 F3 00 00 */	stw r31, 0(r19)
/* 80325EEC 00322ACC  7D 88 03 A6 */	mtlr r12
/* 80325EF0 00322AD0  38 7E 00 00 */	addi r3, r30, 0
/* 80325EF4 00322AD4  38 92 00 00 */	addi r4, r18, 0
/* 80325EF8 00322AD8  38 A0 00 01 */	li r5, 1
/* 80325EFC 00322ADC  4E 80 00 21 */	blrl
/* 80325F00 00322AE0  7F 63 DB 78 */	mr r3, r27
/* 80325F04 00322AE4  BA 41 00 28 */	lmw r18, 0x28(r1)
/* 80325F08 00322AE8  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80325F0C 00322AEC  38 21 00 60 */	addi r1, r1, 0x60
/* 80325F10 00322AF0  7C 08 03 A6 */	mtlr r0
/* 80325F14 00322AF4  4E 80 00 20 */	blr


.section .data
    .balign 8
.global lbl_80400728
lbl_80400728:
    .4byte lbl_80325EB4
    .4byte lbl_80325C98
    .4byte lbl_80325D34
    .4byte lbl_80325EB4
    .4byte lbl_80325D7C
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325DCC
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325EB4
    .4byte lbl_80325DCC
    .4byte NULL


.section .sbss
    .balign 8
.global lbl_804D7078
lbl_804D7078:
    .skip 0x8
