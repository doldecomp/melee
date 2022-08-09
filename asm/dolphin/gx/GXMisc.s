.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

# https://decomp.me/scratch/N6RF9
.global GXSetMisc
GXSetMisc:
/* 8033CBC0 003397A0  2C 03 00 01 */	cmpwi r3, 1
/* 8033CBC4 003397A4  41 82 00 14 */	beq lbl_8033CBD8
/* 8033CBC8 003397A8  4D 80 00 20 */	bltlr 
/* 8033CBCC 003397AC  2C 03 00 03 */	cmpwi r3, 3
/* 8033CBD0 003397B0  4C 80 00 20 */	bgelr 
/* 8033CBD4 003397B4  48 00 00 4C */	b lbl_8033CC20
lbl_8033CBD8:
/* 8033CBD8 003397B8  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033CBDC 003397BC  38 00 00 01 */	li r0, 1
/* 8033CBE0 003397C0  B0 83 00 04 */	sth r4, 4(r3)
/* 8033CBE4 003397C4  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033CBE8 003397C8  A0 64 00 04 */	lhz r3, 4(r4)
/* 8033CBEC 003397CC  7C 63 00 34 */	cntlzw r3, r3
/* 8033CBF0 003397D0  54 63 DC 3E */	rlwinm r3, r3, 0x1b, 0x10, 0x1f
/* 8033CBF4 003397D4  B0 64 00 00 */	sth r3, 0(r4)
/* 8033CBF8 003397D8  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033CBFC 003397DC  B0 03 00 02 */	sth r0, 2(r3)
/* 8033CC00 003397E0  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033CC04 003397E4  A0 03 00 04 */	lhz r0, 4(r3)
/* 8033CC08 003397E8  28 00 00 00 */	cmplwi r0, 0
/* 8033CC0C 003397EC  4D 82 00 20 */	beqlr 
/* 8033CC10 003397F0  80 03 04 F0 */	lwz r0, 0x4f0(r3)
/* 8033CC14 003397F4  60 00 00 08 */	ori r0, r0, 8
/* 8033CC18 003397F8  90 03 04 F0 */	stw r0, 0x4f0(r3)
/* 8033CC1C 003397FC  4E 80 00 20 */	blr 
lbl_8033CC20:
/* 8033CC20 00339800  7C 84 00 D0 */	neg r4, r4
/* 8033CC24 00339804  80 6D A5 08 */	lwz r3, __GXContexts@sda21(r13)
/* 8033CC28 00339808  30 04 FF FF */	addic r0, r4, -1
/* 8033CC2C 0033980C  7C 00 21 10 */	subfe r0, r0, r4
/* 8033CC30 00339810  98 03 04 ED */	stb r0, 0x4ed(r3)
/* 8033CC34 00339814  4E 80 00 20 */	blr 

# https://decomp.me/scratch/rSXT0
.global GXSetDrawDone
GXSetDrawDone:
/* 8033CC38 00339818  7C 08 02 A6 */	mflr r0
/* 8033CC3C 0033981C  90 01 00 04 */	stw r0, 4(r1)
/* 8033CC40 00339820  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033CC44 00339824  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033CC48 00339828  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033CC4C 0033982C  48 00 A7 19 */	bl OSDisableInterrupts
/* 8033CC50 00339830  38 00 00 61 */	li r0, 0x61
/* 8033CC54 00339834  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033CC58 00339838  3C C0 CC 01 */	lis r6, 0xCC008000@ha
/* 8033CC5C 0033983C  3C A0 45 00 */	lis r5, 0x45000002@ha
/* 8033CC60 00339840  98 06 80 00 */	stb r0, 0xCC008000@l(r6)
/* 8033CC64 00339844  38 05 00 02 */	addi r0, r5, 0x45000002@l
/* 8033CC68 00339848  90 06 80 00 */	stw r0, -0x8000(r6)
/* 8033CC6C 0033984C  7C 7E 1B 78 */	mr r30, r3
/* 8033CC70 00339850  80 04 04 F0 */	lwz r0, 0x4f0(r4)
/* 8033CC74 00339854  28 00 00 00 */	cmplwi r0, 0
/* 8033CC78 00339858  41 82 00 08 */	beq lbl_8033CC80
/* 8033CC7C 0033985C  48 00 03 D5 */	bl __GXSetDirtyState
lbl_8033CC80:
/* 8033CC80 00339860  3B E0 00 00 */	li r31, 0
/* 8033CC84 00339864  3C 60 CC 01 */	lis r3, 0xCC008000@ha
/* 8033CC88 00339868  93 E3 80 00 */	stw r31, 0xCC008000@l(r3)
/* 8033CC8C 0033986C  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CC90 00339870  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CC94 00339874  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CC98 00339878  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CC9C 0033987C  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CCA0 00339880  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CCA4 00339884  93 E3 80 00 */	stw r31, -0x8000(r3)
/* 8033CCA8 00339888  4B FF 91 E5 */	bl PPCSync
/* 8033CCAC 0033988C  9B ED BC 88 */	stb r31, lbl_804D7328@sda21(r13)
/* 8033CCB0 00339890  7F C3 F3 78 */	mr r3, r30
/* 8033CCB4 00339894  48 00 A6 D9 */	bl OSRestoreInterrupts
/* 8033CCB8 00339898  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033CCBC 0033989C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033CCC0 003398A0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033CCC4 003398A4  7C 08 03 A6 */	mtlr r0
/* 8033CCC8 003398A8  38 21 00 18 */	addi r1, r1, 0x18
/* 8033CCCC 003398AC  4E 80 00 20 */	blr 

# https://decomp.me/scratch/B4djd
.global GXWaitDrawDone
GXWaitDrawDone:
/* 8033CCD0 003398B0  7C 08 02 A6 */	mflr r0
/* 8033CCD4 003398B4  90 01 00 04 */	stw r0, 4(r1)
/* 8033CCD8 003398B8  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 8033CCDC 003398BC  93 E1 00 0C */	stw r31, 0xc(r1)
/* 8033CCE0 003398C0  48 00 A6 85 */	bl OSDisableInterrupts
/* 8033CCE4 003398C4  7C 7F 1B 78 */	mr r31, r3
/* 8033CCE8 003398C8  48 00 00 0C */	b lbl_8033CCF4
lbl_8033CCEC:
/* 8033CCEC 003398CC  38 6D BC 8C */	addi r3, r13, lbl_804D732C@sda21
/* 8033CCF0 003398D0  48 00 ED 25 */	bl OSSleepThread
lbl_8033CCF4:
/* 8033CCF4 003398D4  88 0D BC 88 */	lbz r0, lbl_804D7328@sda21(r13)
/* 8033CCF8 003398D8  28 00 00 00 */	cmplwi r0, 0
/* 8033CCFC 003398DC  41 82 FF F0 */	beq lbl_8033CCEC
/* 8033CD00 003398E0  7F E3 FB 78 */	mr r3, r31
/* 8033CD04 003398E4  48 00 A6 89 */	bl OSRestoreInterrupts
/* 8033CD08 003398E8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8033CD0C 003398EC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 8033CD10 003398F0  38 21 00 10 */	addi r1, r1, 0x10
/* 8033CD14 003398F4  7C 08 03 A6 */	mtlr r0
/* 8033CD18 003398F8  4E 80 00 20 */	blr 

# https://decomp.me/scratch/cEfhC
.global GXPixModeSync
GXPixModeSync:
/* 8033CD1C 003398FC  38 00 00 61 */	li r0, 0x61
/* 8033CD20 00339900  80 8D A5 08 */	lwz r4, __GXContexts@sda21(r13)
/* 8033CD24 00339904  3C A0 CC 01 */	lis r5, 0xCC008000@ha
/* 8033CD28 00339908  98 05 80 00 */	stb r0, 0xCC008000@l(r5)
/* 8033CD2C 0033990C  38 00 00 00 */	li r0, 0
/* 8033CD30 00339910  80 64 01 DC */	lwz r3, 0x1dc(r4)
/* 8033CD34 00339914  90 65 80 00 */	stw r3, -0x8000(r5)
/* 8033CD38 00339918  B0 04 00 02 */	sth r0, 2(r4)
/* 8033CD3C 0033991C  4E 80 00 20 */	blr 

# https://decomp.me/scratch/lrkWr // 330 (34%)
.global GXPokeAlphaMode
GXPokeAlphaMode:
/* 8033CD40 00339920  80 AD BC 58 */	lwz r5, lbl_804D72F8@sda21(r13)
/* 8033CD44 00339924  54 80 06 3E */	clrlwi r0, r4, 0x18
/* 8033CD48 00339928  50 60 40 2E */	rlwimi r0, r3, 8, 0, 0x17
/* 8033CD4C 0033992C  B0 05 00 06 */	sth r0, 6(r5)
/* 8033CD50 00339930  4E 80 00 20 */	blr 

# https://decomp.me/scratch/G7Zqa // 0 (100%)
.global GXPokeAlphaRead
GXPokeAlphaRead:
/* 8033CD54 00339934  54 60 07 B8 */	rlwinm r0, r3, 0, 0x1e, 0x1c
/* 8033CD58 00339938  80 6D BC 58 */	lwz r3, lbl_804D72F8@sda21(r13)
/* 8033CD5C 0033993C  60 00 00 04 */	ori r0, r0, 4
/* 8033CD60 00339940  B0 03 00 08 */	sth r0, 8(r3)
/* 8033CD64 00339944  4E 80 00 20 */	blr 

# https://decomp.me/scratch/rzht5 // 0 (100%)
.global GXPokeAlphaUpdate
GXPokeAlphaUpdate:
/* 8033CD68 00339948  80 8D BC 58 */	lwz r4, lbl_804D72F8@sda21(r13)
/* 8033CD6C 0033994C  54 60 25 36 */	rlwinm r0, r3, 4, 0x14, 0x1b
/* 8033CD70 00339950  A4 64 00 02 */	lhzu r3, 2(r4)
/* 8033CD74 00339954  54 63 07 34 */	rlwinm r3, r3, 0, 0x1c, 0x1a
/* 8033CD78 00339958  7C 60 03 78 */	or r0, r3, r0
/* 8033CD7C 0033995C  B0 04 00 00 */	sth r0, 0(r4)
/* 8033CD80 00339960  4E 80 00 20 */	blr 

# https://decomp.me/scratch/uLvix // 3115 (8.38%)
.global GXPokeBlendMode
GXPokeBlendMode:
/* 8033CD84 00339964  80 ED BC 58 */	lwz r7, lbl_804D72F8@sda21(r13)
/* 8033CD88 00339968  2C 03 00 01 */	cmpwi r3, 1
/* 8033CD8C 0033996C  39 20 00 01 */	li r9, 1
/* 8033CD90 00339970  39 47 00 02 */	addi r10, r7, 2
/* 8033CD94 00339974  A0 E7 00 02 */	lhz r7, 2(r7)
/* 8033CD98 00339978  41 82 00 10 */	beq lbl_8033CDA8
/* 8033CD9C 0033997C  2C 03 00 03 */	cmpwi r3, 3
/* 8033CDA0 00339980  41 82 00 08 */	beq lbl_8033CDA8
/* 8033CDA4 00339984  39 20 00 00 */	li r9, 0
lbl_8033CDA8:
/* 8033CDA8 00339988  54 E8 00 3C */	rlwinm r8, r7, 0, 0, 0x1e
/* 8033CDAC 0033998C  20 03 00 03 */	subfic r0, r3, 3
/* 8033CDB0 00339990  7C 07 00 34 */	cntlzw r7, r0
/* 8033CDB4 00339994  20 03 00 02 */	subfic r0, r3, 2
/* 8033CDB8 00339998  7D 08 4B 78 */	or r8, r8, r9
/* 8033CDBC 0033999C  7C 00 00 34 */	cntlzw r0, r0
/* 8033CDC0 003399A0  55 08 05 66 */	rlwinm r8, r8, 0, 0x15, 0x13
/* 8033CDC4 003399A4  54 E3 30 28 */	rlwinm r3, r7, 6, 0, 0x14
/* 8033CDC8 003399A8  7D 03 1B 78 */	or r3, r8, r3
/* 8033CDCC 003399AC  54 63 07 FA */	rlwinm r3, r3, 0, 0x1f, 0x1d
/* 8033CDD0 003399B0  54 00 E1 3C */	rlwinm r0, r0, 0x1c, 4, 0x1e
/* 8033CDD4 003399B4  7C 60 03 78 */	or r0, r3, r0
/* 8033CDD8 003399B8  54 03 05 1E */	rlwinm r3, r0, 0, 0x14, 0xf
/* 8033CDDC 003399BC  54 C0 60 26 */	slwi r0, r6, 0xc
/* 8033CDE0 003399C0  7C 60 03 78 */	or r0, r3, r0
/* 8033CDE4 003399C4  54 03 06 28 */	rlwinm r3, r0, 0, 0x18, 0x14
/* 8033CDE8 003399C8  54 80 40 2E */	slwi r0, r4, 8
/* 8033CDEC 003399CC  7C 60 03 78 */	or r0, r3, r0
/* 8033CDF0 003399D0  54 03 06 EE */	rlwinm r3, r0, 0, 0x1b, 0x17
/* 8033CDF4 003399D4  54 A0 28 34 */	slwi r0, r5, 5
/* 8033CDF8 003399D8  7C 60 03 78 */	or r0, r3, r0
/* 8033CDFC 003399DC  54 00 02 3E */	clrlwi r0, r0, 8
/* 8033CE00 003399E0  64 00 41 00 */	oris r0, r0, 0x4100
/* 8033CE04 003399E4  B0 0A 00 00 */	sth r0, 0(r10)
/* 8033CE08 003399E8  4E 80 00 20 */	blr 

# https://decomp.me/scratch/G33Fb // 0 (100%)
.global GXPokeColorUpdate
GXPokeColorUpdate:
/* 8033CE0C 003399EC  80 8D BC 58 */	lwz r4, lbl_804D72F8@sda21(r13)
/* 8033CE10 003399F0  54 60 1D 78 */	rlwinm r0, r3, 3, 0x15, 0x1c
/* 8033CE14 003399F4  A4 64 00 02 */	lhzu r3, 2(r4)
/* 8033CE18 003399F8  54 63 07 76 */	rlwinm r3, r3, 0, 0x1d, 0x1b
/* 8033CE1C 003399FC  7C 60 03 78 */	or r0, r3, r0
/* 8033CE20 00339A00  B0 04 00 00 */	sth r0, 0(r4)
/* 8033CE24 00339A04  4E 80 00 20 */	blr 

# https://decomp.me/scratch/FHQSt // 220 (56%)
.global GXPokeDstAlpha
GXPokeDstAlpha:
/* 8033CE28 00339A08  80 AD BC 58 */	lwz r5, lbl_804D72F8@sda21(r13)
/* 8033CE2C 00339A0C  54 60 44 2E */	rlwinm r0, r3, 8, 0x10, 0x17
/* 8033CE30 00339A10  50 80 06 3E */	rlwimi r0, r4, 0, 0x18, 0x1f
/* 8033CE34 00339A14  B0 05 00 04 */	sth r0, 4(r5)
/* 8033CE38 00339A18  4E 80 00 20 */	blr 

# https://decomp.me/scratch/adZRo // 0 (100%)
.global GXPokeDither
GXPokeDither:
/* 8033CE3C 00339A1C  80 8D BC 58 */	lwz r4, lbl_804D72F8@sda21(r13)
/* 8033CE40 00339A20  54 60 15 BA */	rlwinm r0, r3, 2, 0x16, 0x1d
/* 8033CE44 00339A24  A4 64 00 02 */	lhzu r3, 2(r4)
/* 8033CE48 00339A28  54 63 07 B8 */	rlwinm r3, r3, 0, 0x1e, 0x1c
/* 8033CE4C 00339A2C  7C 60 03 78 */	or r0, r3, r0
/* 8033CE50 00339A30  B0 04 00 00 */	sth r0, 0(r4)
/* 8033CE54 00339A34  4E 80 00 20 */	blr 

# https://decomp.me/scratch/wi2b0 // 200 (80%)
.global GXPokeZMode
GXPokeZMode:
/* 8033CE58 00339A38  54 60 06 3E */	clrlwi r0, r3, 0x18
/* 8033CE5C 00339A3C  80 6D BC 58 */	lwz r3, lbl_804D72F8@sda21(r13)
/* 8033CE60 00339A40  54 06 07 F6 */	rlwinm r6, r0, 0, 0x1f, 0x1b
/* 8033CE64 00339A44  54 80 08 3C */	slwi r0, r4, 1
/* 8033CE68 00339A48  7C C0 03 78 */	or r0, r6, r0
/* 8033CE6C 00339A4C  54 04 07 34 */	rlwinm r4, r0, 0, 0x1c, 0x1a
/* 8033CE70 00339A50  54 A0 25 36 */	rlwinm r0, r5, 4, 0x14, 0x1b
/* 8033CE74 00339A54  7C 80 03 78 */	or r0, r4, r0
/* 8033CE78 00339A58  B0 03 00 00 */	sth r0, 0(r3)
/* 8033CE7C 00339A5C  4E 80 00 20 */	blr 

GXTokenInterruptHandler:
/* 8033CE80 00339A60  7C 08 02 A6 */	mflr r0
/* 8033CE84 00339A64  90 01 00 04 */	stw r0, 4(r1)
/* 8033CE88 00339A68  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 8033CE8C 00339A6C  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 8033CE90 00339A70  93 C1 02 D8 */	stw r30, 0x2d8(r1)
/* 8033CE94 00339A74  7C 9E 23 78 */	mr r30, r4
/* 8033CE98 00339A78  80 0D BC 80 */	lwz r0, lbl_804D7320@sda21(r13)
/* 8033CE9C 00339A7C  80 6D BC 58 */	lwz r3, lbl_804D72F8@sda21(r13)
/* 8033CEA0 00339A80  28 00 00 00 */	cmplwi r0, 0
/* 8033CEA4 00339A84  A3 E3 00 0E */	lhz r31, 0xe(r3)
/* 8033CEA8 00339A88  41 82 00 34 */	beq lbl_8033CEDC
/* 8033CEAC 00339A8C  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CEB0 00339A90  48 00 83 A5 */	bl OSClearContext
/* 8033CEB4 00339A94  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CEB8 00339A98  48 00 81 D5 */	bl OSSetCurrentContext
/* 8033CEBC 00339A9C  81 8D BC 80 */	lwz r12, lbl_804D7320@sda21(r13)
/* 8033CEC0 00339AA0  38 7F 00 00 */	addi r3, r31, 0
/* 8033CEC4 00339AA4  7D 88 03 A6 */	mtlr r12
/* 8033CEC8 00339AA8  4E 80 00 21 */	blrl 
/* 8033CECC 00339AAC  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CED0 00339AB0  48 00 83 85 */	bl OSClearContext
/* 8033CED4 00339AB4  7F C3 F3 78 */	mr r3, r30
/* 8033CED8 00339AB8  48 00 81 B5 */	bl OSSetCurrentContext
lbl_8033CEDC:
/* 8033CEDC 00339ABC  80 6D BC 58 */	lwz r3, lbl_804D72F8@sda21(r13)
/* 8033CEE0 00339AC0  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 8033CEE4 00339AC4  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 8033CEE8 00339AC8  60 00 00 04 */	ori r0, r0, 4
/* 8033CEEC 00339ACC  B0 03 00 00 */	sth r0, 0(r3)
/* 8033CEF0 00339AD0  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 8033CEF4 00339AD4  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 8033CEF8 00339AD8  83 C1 02 D8 */	lwz r30, 0x2d8(r1)
/* 8033CEFC 00339ADC  7C 08 03 A6 */	mtlr r0
/* 8033CF00 00339AE0  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 8033CF04 00339AE4  4E 80 00 20 */	blr 

.global GXSetDrawDoneCallback
GXSetDrawDoneCallback:
/* 8033CF08 00339AE8  7C 08 02 A6 */	mflr r0
/* 8033CF0C 00339AEC  90 01 00 04 */	stw r0, 4(r1)
/* 8033CF10 00339AF0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8033CF14 00339AF4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8033CF18 00339AF8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8033CF1C 00339AFC  7C 7E 1B 78 */	mr r30, r3
/* 8033CF20 00339B00  83 ED BC 84 */	lwz r31, lbl_804D7324@sda21(r13)
/* 8033CF24 00339B04  48 00 A4 41 */	bl OSDisableInterrupts
/* 8033CF28 00339B08  93 CD BC 84 */	stw r30, lbl_804D7324@sda21(r13)
/* 8033CF2C 00339B0C  48 00 A4 61 */	bl OSRestoreInterrupts
/* 8033CF30 00339B10  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8033CF34 00339B14  7F E3 FB 78 */	mr r3, r31
/* 8033CF38 00339B18  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8033CF3C 00339B1C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8033CF40 00339B20  7C 08 03 A6 */	mtlr r0
/* 8033CF44 00339B24  38 21 00 18 */	addi r1, r1, 0x18
/* 8033CF48 00339B28  4E 80 00 20 */	blr 

# https://decomp.me/scratch/PoUPM
GXFinishInterruptHandler:
/* 8033CF4C 00339B2C  7C 08 02 A6 */	mflr r0
/* 8033CF50 00339B30  38 60 00 01 */	li r3, 1
/* 8033CF54 00339B34  90 01 00 04 */	stw r0, 4(r1)
/* 8033CF58 00339B38  94 21 FD 20 */	stwu r1, -0x2e0(r1)
/* 8033CF5C 00339B3C  93 E1 02 DC */	stw r31, 0x2dc(r1)
/* 8033CF60 00339B40  3B E4 00 00 */	addi r31, r4, 0
/* 8033CF64 00339B44  80 AD BC 58 */	lwz r5, lbl_804D72F8@sda21(r13)
/* 8033CF68 00339B48  A0 05 00 0A */	lhz r0, 0xa(r5)
/* 8033CF6C 00339B4C  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8033CF70 00339B50  60 00 00 08 */	ori r0, r0, 8
/* 8033CF74 00339B54  B0 05 00 0A */	sth r0, 0xa(r5)
/* 8033CF78 00339B58  80 0D BC 84 */	lwz r0, lbl_804D7324@sda21(r13)
/* 8033CF7C 00339B5C  98 6D BC 88 */	stb r3, lbl_804D7328@sda21(r13)
/* 8033CF80 00339B60  28 00 00 00 */	cmplwi r0, 0
/* 8033CF84 00339B64  41 82 00 30 */	beq lbl_8033CFB4
/* 8033CF88 00339B68  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CF8C 00339B6C  48 00 82 C9 */	bl OSClearContext
/* 8033CF90 00339B70  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CF94 00339B74  48 00 80 F9 */	bl OSSetCurrentContext
/* 8033CF98 00339B78  81 8D BC 84 */	lwz r12, lbl_804D7324@sda21(r13)
/* 8033CF9C 00339B7C  7D 88 03 A6 */	mtlr r12
/* 8033CFA0 00339B80  4E 80 00 21 */	blrl 
/* 8033CFA4 00339B84  38 61 00 10 */	addi r3, r1, 0x10
/* 8033CFA8 00339B88  48 00 82 AD */	bl OSClearContext
/* 8033CFAC 00339B8C  7F E3 FB 78 */	mr r3, r31
/* 8033CFB0 00339B90  48 00 80 DD */	bl OSSetCurrentContext
lbl_8033CFB4:
/* 8033CFB4 00339B94  38 6D BC 8C */	addi r3, r13, lbl_804D732C@sda21
/* 8033CFB8 00339B98  48 00 EB 49 */	bl OSWakeupThread
/* 8033CFBC 00339B9C  80 01 02 E4 */	lwz r0, 0x2e4(r1)
/* 8033CFC0 00339BA0  83 E1 02 DC */	lwz r31, 0x2dc(r1)
/* 8033CFC4 00339BA4  38 21 02 E0 */	addi r1, r1, 0x2e0
/* 8033CFC8 00339BA8  7C 08 03 A6 */	mtlr r0
/* 8033CFCC 00339BAC  4E 80 00 20 */	blr 

.global __GXPEInit
__GXPEInit:
/* 8033CFD0 00339BB0  7C 08 02 A6 */	mflr r0
/* 8033CFD4 00339BB4  3C 60 80 34 */	lis r3, GXTokenInterruptHandler@ha
/* 8033CFD8 00339BB8  90 01 00 04 */	stw r0, 4(r1)
/* 8033CFDC 00339BBC  38 83 CE 80 */	addi r4, r3, GXTokenInterruptHandler@l
/* 8033CFE0 00339BC0  38 60 00 12 */	li r3, 0x12
/* 8033CFE4 00339BC4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8033CFE8 00339BC8  48 00 A3 C9 */	bl __OSSetInterruptHandler
/* 8033CFEC 00339BCC  3C 60 80 34 */	lis r3, GXFinishInterruptHandler@ha
/* 8033CFF0 00339BD0  38 83 CF 4C */	addi r4, r3, GXFinishInterruptHandler@l
/* 8033CFF4 00339BD4  38 60 00 13 */	li r3, 0x13
/* 8033CFF8 00339BD8  48 00 A3 B9 */	bl __OSSetInterruptHandler
/* 8033CFFC 00339BDC  38 6D BC 8C */	addi r3, r13, lbl_804D732C@sda21
/* 8033D000 00339BE0  48 00 DD 2D */	bl OSInitThreadQueue
/* 8033D004 00339BE4  38 60 20 00 */	li r3, 0x2000
/* 8033D008 00339BE8  48 00 A7 AD */	bl __OSUnmaskInterrupts
/* 8033D00C 00339BEC  38 60 10 00 */	li r3, 0x1000
/* 8033D010 00339BF0  48 00 A7 A5 */	bl __OSUnmaskInterrupts
/* 8033D014 00339BF4  80 6D BC 58 */	lwz r3, lbl_804D72F8@sda21(r13)
/* 8033D018 00339BF8  A4 03 00 0A */	lhzu r0, 0xa(r3)
/* 8033D01C 00339BFC  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 8033D020 00339C00  60 00 00 04 */	ori r0, r0, 4
/* 8033D024 00339C04  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 8033D028 00339C08  60 00 00 08 */	ori r0, r0, 8
/* 8033D02C 00339C0C  54 00 00 3C */	rlwinm r0, r0, 0, 0, 0x1e
/* 8033D030 00339C10  60 00 00 01 */	ori r0, r0, 1
/* 8033D034 00339C14  54 00 07 FA */	rlwinm r0, r0, 0, 0x1f, 0x1d
/* 8033D038 00339C18  60 00 00 02 */	ori r0, r0, 2
/* 8033D03C 00339C1C  B0 03 00 00 */	sth r0, 0(r3)
/* 8033D040 00339C20  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8033D044 00339C24  38 21 00 08 */	addi r1, r1, 8
/* 8033D048 00339C28  7C 08 03 A6 */	mtlr r0
/* 8033D04C 00339C2C  4E 80 00 20 */	blr 

.section .sbss
    .balign 8

# decl GXMisc.c
lbl_804D7320:
	.skip 0x4

# decl GXMisc.c
lbl_804D7324:
	.skip 0x4

# decl GXMisc.c
lbl_804D7328:
	.skip 0x4

# decl GXMisc.c
lbl_804D732C:
	.skip 0xC
