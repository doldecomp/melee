.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global func_8038FAA8
func_8038FAA8:
/* 8038FAA8 0038C688  3C 80 80 4D */	lis r4, HSD_GObjLibInitData@ha
/* 8038FAAC 0038C68C  80 C3 00 10 */	lwz r6, 0x10(r3)
/* 8038FAB0 0038C690  88 A4 E3 80 */	lbz r5, HSD_GObjLibInitData@l(r4)
/* 8038FAB4 0038C694  88 03 00 0C */	lbz r0, 0xc(r3)
/* 8038FAB8 0038C698  7C C4 33 78 */	mr r4, r6
/* 8038FABC 0038C69C  39 05 00 01 */	addi r8, r5, 1
/* 8038FAC0 0038C6A0  88 E6 00 02 */	lbz r7, 2(r6)
/* 8038FAC4 0038C6A4  7C A0 41 D6 */	mullw r5, r0, r8
/* 8038FAC8 0038C6A8  81 2D C1 A4 */	lwz r9, lbl_804D7844@sda21(r13)
/* 8038FACC 0038C6AC  7C A7 2A 14 */	add r5, r7, r5
/* 8038FAD0 0038C6B0  54 A6 10 3A */	slwi r6, r5, 2
/* 8038FAD4 0038C6B4  7C A9 30 2E */	lwzx r5, r9, r6
/* 8038FAD8 0038C6B8  39 47 00 00 */	addi r10, r7, 0
/* 8038FADC 0038C6BC  28 05 00 00 */	cmplwi r5, 0
/* 8038FAE0 0038C6C0  41 82 00 60 */	beq lbl_8038FB40
/* 8038FAE4 0038C6C4  7C 86 23 78 */	mr r6, r4
/* 8038FAE8 0038C6C8  48 00 00 4C */	b lbl_8038FB34
lbl_8038FAEC:
/* 8038FAEC 0038C6CC  80 E6 00 18 */	lwz r7, 0x18(r6)
/* 8038FAF0 0038C6D0  48 00 00 38 */	b lbl_8038FB28
lbl_8038FAF4:
/* 8038FAF4 0038C6D4  88 A7 00 0C */	lbz r5, 0xc(r7)
/* 8038FAF8 0038C6D8  7C 05 00 40 */	cmplw r5, r0
/* 8038FAFC 0038C6DC  40 82 00 28 */	bne lbl_8038FB24
/* 8038FB00 0038C6E0  7C A0 41 D6 */	mullw r5, r0, r8
/* 8038FB04 0038C6E4  7C AA 2A 14 */	add r5, r10, r5
/* 8038FB08 0038C6E8  54 A5 10 3A */	slwi r5, r5, 2
/* 8038FB0C 0038C6EC  7C C9 2A 14 */	add r6, r9, r5
/* 8038FB10 0038C6F0  80 A6 00 00 */	lwz r5, 0(r6)
/* 8038FB14 0038C6F4  7C 05 38 40 */	cmplw r5, r7
/* 8038FB18 0038C6F8  40 82 00 90 */	bne lbl_8038FBA8
/* 8038FB1C 0038C6FC  90 66 00 00 */	stw r3, 0(r6)
/* 8038FB20 0038C700  48 00 00 88 */	b lbl_8038FBA8
lbl_8038FB24:
/* 8038FB24 0038C704  80 E7 00 00 */	lwz r7, 0(r7)
lbl_8038FB28:
/* 8038FB28 0038C708  28 07 00 00 */	cmplwi r7, 0
/* 8038FB2C 0038C70C  40 82 FF C8 */	bne lbl_8038FAF4
/* 8038FB30 0038C710  80 C6 00 0C */	lwz r6, 0xc(r6)
lbl_8038FB34:
/* 8038FB34 0038C714  28 06 00 00 */	cmplwi r6, 0
/* 8038FB38 0038C718  40 82 FF B4 */	bne lbl_8038FAEC
/* 8038FB3C 0038C71C  48 00 00 08 */	b lbl_8038FB44
lbl_8038FB40:
/* 8038FB40 0038C720  7C 69 31 2E */	stwx r3, r9, r6
lbl_8038FB44:
/* 8038FB44 0038C724  3C A0 80 4D */	lis r5, HSD_GObjLibInitData@ha
/* 8038FB48 0038C728  80 CD C1 A4 */	lwz r6, lbl_804D7844@sda21(r13)
/* 8038FB4C 0038C72C  38 A5 E3 80 */	addi r5, r5, HSD_GObjLibInitData@l
/* 8038FB50 0038C730  88 A5 00 00 */	lbz r5, 0(r5)
/* 8038FB54 0038C734  38 A5 00 01 */	addi r5, r5, 1
/* 8038FB58 0038C738  7C A0 29 D6 */	mullw r5, r0, r5
/* 8038FB5C 0038C73C  7C AA 2A 14 */	add r5, r10, r5
/* 8038FB60 0038C740  54 A5 10 3A */	slwi r5, r5, 2
/* 8038FB64 0038C744  48 00 00 10 */	b lbl_8038FB74
lbl_8038FB68:
/* 8038FB68 0038C748  7C E6 28 2E */	lwzx r7, r6, r5
/* 8038FB6C 0038C74C  28 07 00 00 */	cmplwi r7, 0
/* 8038FB70 0038C750  40 82 00 38 */	bne lbl_8038FBA8
lbl_8038FB74:
/* 8038FB74 0038C754  2C 0A 00 00 */	cmpwi r10, 0
/* 8038FB78 0038C758  38 A5 FF FC */	addi r5, r5, -4
/* 8038FB7C 0038C75C  39 4A FF FF */	addi r10, r10, -1
/* 8038FB80 0038C760  40 82 FF E8 */	bne lbl_8038FB68
/* 8038FB84 0038C764  80 CD C1 A0 */	lwz r6, lbl_804D7840@sda21(r13)
/* 8038FB88 0038C768  54 07 10 3A */	slwi r7, r0, 2
/* 8038FB8C 0038C76C  38 A0 00 00 */	li r5, 0
/* 8038FB90 0038C770  7C C6 38 2E */	lwzx r6, r6, r7
/* 8038FB94 0038C774  90 C3 00 04 */	stw r6, 4(r3)
/* 8038FB98 0038C778  80 CD C1 A0 */	lwz r6, lbl_804D7840@sda21(r13)
/* 8038FB9C 0038C77C  7C 66 39 2E */	stwx r3, r6, r7
/* 8038FBA0 0038C780  90 A3 00 08 */	stw r5, 8(r3)
/* 8038FBA4 0038C784  48 00 00 14 */	b lbl_8038FBB8
lbl_8038FBA8:
/* 8038FBA8 0038C788  80 A7 00 04 */	lwz r5, 4(r7)
/* 8038FBAC 0038C78C  90 A3 00 04 */	stw r5, 4(r3)
/* 8038FBB0 0038C790  90 67 00 04 */	stw r3, 4(r7)
/* 8038FBB4 0038C794  90 E3 00 08 */	stw r7, 8(r3)
lbl_8038FBB8:
/* 8038FBB8 0038C798  80 A3 00 04 */	lwz r5, 4(r3)
/* 8038FBBC 0038C79C  28 05 00 00 */	cmplwi r5, 0
/* 8038FBC0 0038C7A0  41 82 00 08 */	beq lbl_8038FBC8
/* 8038FBC4 0038C7A4  90 65 00 08 */	stw r3, 8(r5)
lbl_8038FBC8:
/* 8038FBC8 0038C7A8  80 C4 00 18 */	lwz r6, 0x18(r4)
/* 8038FBCC 0038C7AC  3C A0 80 4D */	lis r5, lbl_804CE3E4@ha
/* 8038FBD0 0038C7B0  90 C3 00 00 */	stw r6, 0(r3)
/* 8038FBD4 0038C7B4  90 64 00 18 */	stw r3, 0x18(r4)
/* 8038FBD8 0038C7B8  88 85 E3 E4 */	lbz r4, lbl_804CE3E4@l(r5)
/* 8038FBDC 0038C7BC  54 84 CF FF */	rlwinm. r4, r4, 0x19, 0x1f, 0x1f
/* 8038FBE0 0038C7C0  4D 82 00 20 */	beqlr
/* 8038FBE4 0038C7C4  80 A3 00 08 */	lwz r5, 8(r3)
/* 8038FBE8 0038C7C8  80 8D C1 98 */	lwz r4, lbl_804D7838@sda21(r13)
/* 8038FBEC 0038C7CC  7C 05 20 40 */	cmplw r5, r4
/* 8038FBF0 0038C7D0  4C 82 00 20 */	bnelr
/* 8038FBF4 0038C7D4  80 A3 00 04 */	lwz r5, 4(r3)
/* 8038FBF8 0038C7D8  80 8D C1 90 */	lwz r4, lbl_804D7830@sda21(r13)
/* 8038FBFC 0038C7DC  7C 05 20 40 */	cmplw r5, r4
/* 8038FC00 0038C7E0  4C 82 00 20 */	bnelr
/* 8038FC04 0038C7E4  80 8D C1 94 */	lwz r4, lbl_804D7834@sda21(r13)
/* 8038FC08 0038C7E8  7C 00 20 00 */	cmpw r0, r4
/* 8038FC0C 0038C7EC  4C 82 00 20 */	bnelr
/* 8038FC10 0038C7F0  90 6D C1 90 */	stw r3, lbl_804D7830@sda21(r13)
/* 8038FC14 0038C7F4  4E 80 00 20 */	blr
