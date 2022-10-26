.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240 

# https://decomp.me/scratch/oYS6V
.global OSWakeupThread
OSWakeupThread:
/* 8034BB00 003486E0  7C 08 02 A6 */	mflr r0
/* 8034BB04 003486E4  90 01 00 04 */	stw r0, 4(r1)
/* 8034BB08 003486E8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8034BB0C 003486EC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8034BB10 003486F0  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8034BB14 003486F4  7C 7E 1B 78 */	mr r30, r3
/* 8034BB18 003486F8  4B FF B8 4D */	bl OSDisableInterrupts
/* 8034BB1C 003486FC  3C 80 80 4A */	lis r4, lbl_804A7FB8@ha
/* 8034BB20 00348700  3B E3 00 00 */	addi r31, r3, 0
/* 8034BB24 00348704  38 A4 7F B8 */	addi r5, r4, lbl_804A7FB8@l
/* 8034BB28 00348708  48 00 00 9C */	b lbl_8034BBC4
lbl_8034BB2C:
/* 8034BB2C 0034870C  80 66 02 E0 */	lwz r3, 0x2e0(r6)
/* 8034BB30 00348710  28 03 00 00 */	cmplwi r3, 0
/* 8034BB34 00348714  40 82 00 10 */	bne lbl_8034BB44
/* 8034BB38 00348718  38 00 00 00 */	li r0, 0
/* 8034BB3C 0034871C  90 1E 00 04 */	stw r0, 4(r30)
/* 8034BB40 00348720  48 00 00 0C */	b lbl_8034BB4C
lbl_8034BB44:
/* 8034BB44 00348724  38 00 00 00 */	li r0, 0
/* 8034BB48 00348728  90 03 02 E4 */	stw r0, 0x2e4(r3)
lbl_8034BB4C:
/* 8034BB4C 0034872C  90 7E 00 00 */	stw r3, 0(r30)
/* 8034BB50 00348730  38 00 00 01 */	li r0, 1
/* 8034BB54 00348734  B0 06 02 C8 */	sth r0, 0x2c8(r6)
/* 8034BB58 00348738  80 06 02 CC */	lwz r0, 0x2cc(r6)
/* 8034BB5C 0034873C  2C 00 00 00 */	cmpwi r0, 0
/* 8034BB60 00348740  41 81 00 64 */	bgt lbl_8034BBC4
/* 8034BB64 00348744  80 06 02 D0 */	lwz r0, 0x2d0(r6)
/* 8034BB68 00348748  54 00 18 38 */	slwi r0, r0, 3
/* 8034BB6C 0034874C  7C 05 02 14 */	add r0, r5, r0
/* 8034BB70 00348750  90 06 02 DC */	stw r0, 0x2dc(r6)
/* 8034BB74 00348754  80 86 02 DC */	lwz r4, 0x2dc(r6)
/* 8034BB78 00348758  80 64 00 04 */	lwz r3, 4(r4)
/* 8034BB7C 0034875C  28 03 00 00 */	cmplwi r3, 0
/* 8034BB80 00348760  40 82 00 0C */	bne lbl_8034BB8C
/* 8034BB84 00348764  90 C4 00 00 */	stw r6, 0(r4)
/* 8034BB88 00348768  48 00 00 08 */	b lbl_8034BB90
lbl_8034BB8C:
/* 8034BB8C 0034876C  90 C3 02 E0 */	stw r6, 0x2e0(r3)
lbl_8034BB90:
/* 8034BB90 00348770  90 66 02 E4 */	stw r3, 0x2e4(r6)
/* 8034BB94 00348774  38 00 00 00 */	li r0, 0
/* 8034BB98 00348778  38 60 00 01 */	li r3, 1
/* 8034BB9C 0034877C  90 06 02 E0 */	stw r0, 0x2e0(r6)
/* 8034BBA0 00348780  80 86 02 DC */	lwz r4, 0x2dc(r6)
/* 8034BBA4 00348784  90 C4 00 04 */	stw r6, 4(r4)
/* 8034BBA8 00348788  80 06 02 D0 */	lwz r0, 0x2d0(r6)
/* 8034BBAC 0034878C  80 8D BD 38 */	lwz r4, lbl_804D73D8@sda21(r13)
/* 8034BBB0 00348790  20 00 00 1F */	subfic r0, r0, 0x1f
/* 8034BBB4 00348794  7C 60 00 30 */	slw r0, r3, r0
/* 8034BBB8 00348798  7C 80 03 78 */	or r0, r4, r0
/* 8034BBBC 0034879C  90 0D BD 38 */	stw r0, lbl_804D73D8@sda21(r13)
/* 8034BBC0 003487A0  90 6D BD 3C */	stw r3, lbl_804D73DC@sda21(r13)
lbl_8034BBC4:
/* 8034BBC4 003487A4  80 DE 00 00 */	lwz r6, 0(r30)
/* 8034BBC8 003487A8  28 06 00 00 */	cmplwi r6, 0
/* 8034BBCC 003487AC  40 82 FF 60 */	bne lbl_8034BB2C
/* 8034BBD0 003487B0  80 0D BD 3C */	lwz r0, lbl_804D73DC@sda21(r13)
/* 8034BBD4 003487B4  2C 00 00 00 */	cmpwi r0, 0
/* 8034BBD8 003487B8  41 82 00 0C */	beq lbl_8034BBE4
/* 8034BBDC 003487BC  38 60 00 00 */	li r3, 0
/* 8034BBE0 003487C0  4B FF F4 4D */	bl SelectThread
lbl_8034BBE4:
/* 8034BBE4 003487C4  7F E3 FB 78 */	mr r3, r31
/* 8034BBE8 003487C8  4B FF B7 A5 */	bl OSRestoreInterrupts
/* 8034BBEC 003487CC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8034BBF0 003487D0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8034BBF4 003487D4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8034BBF8 003487D8  7C 08 03 A6 */	mtlr r0
/* 8034BBFC 003487DC  38 21 00 18 */	addi r1, r1, 0x18
/* 8034BC00 003487E0  4E 80 00 20 */	blr 

.global CheckThreadQueue
CheckThreadQueue:
/* 8034BC04 003487E4  80 83 00 00 */	lwz r4, 0(r3)
/* 8034BC08 003487E8  28 04 00 00 */	cmplwi r4, 0
/* 8034BC0C 003487EC  41 82 00 18 */	beq lbl_8034BC24
/* 8034BC10 003487F0  80 04 02 E4 */	lwz r0, 0x2e4(r4)
/* 8034BC14 003487F4  28 00 00 00 */	cmplwi r0, 0
/* 8034BC18 003487F8  41 82 00 0C */	beq lbl_8034BC24
/* 8034BC1C 003487FC  38 60 00 00 */	li r3, 0
/* 8034BC20 00348800  4E 80 00 20 */	blr 
lbl_8034BC24:
/* 8034BC24 00348804  80 63 00 04 */	lwz r3, 4(r3)
/* 8034BC28 00348808  28 03 00 00 */	cmplwi r3, 0
/* 8034BC2C 0034880C  41 82 00 18 */	beq lbl_8034BC44
/* 8034BC30 00348810  80 03 02 E0 */	lwz r0, 0x2e0(r3)
/* 8034BC34 00348814  28 00 00 00 */	cmplwi r0, 0
/* 8034BC38 00348818  41 82 00 0C */	beq lbl_8034BC44
/* 8034BC3C 0034881C  38 60 00 00 */	li r3, 0
/* 8034BC40 00348820  4E 80 00 20 */	blr 
lbl_8034BC44:
/* 8034BC44 00348824  7C 85 23 78 */	mr r5, r4
/* 8034BC48 00348828  48 00 00 48 */	b lbl_8034BC90
lbl_8034BC4C:
/* 8034BC4C 0034882C  80 65 02 E0 */	lwz r3, 0x2e0(r5)
/* 8034BC50 00348830  28 03 00 00 */	cmplwi r3, 0
/* 8034BC54 00348834  41 82 00 18 */	beq lbl_8034BC6C
/* 8034BC58 00348838  80 03 02 E4 */	lwz r0, 0x2e4(r3)
/* 8034BC5C 0034883C  7C 05 00 40 */	cmplw r5, r0
/* 8034BC60 00348840  41 82 00 0C */	beq lbl_8034BC6C
/* 8034BC64 00348844  38 60 00 00 */	li r3, 0
/* 8034BC68 00348848  4E 80 00 20 */	blr 
lbl_8034BC6C:
/* 8034BC6C 0034884C  80 85 02 E4 */	lwz r4, 0x2e4(r5)
/* 8034BC70 00348850  28 04 00 00 */	cmplwi r4, 0
/* 8034BC74 00348854  41 82 00 18 */	beq lbl_8034BC8C
/* 8034BC78 00348858  80 04 02 E0 */	lwz r0, 0x2e0(r4)
/* 8034BC7C 0034885C  7C 05 00 40 */	cmplw r5, r0
/* 8034BC80 00348860  41 82 00 0C */	beq lbl_8034BC8C
/* 8034BC84 00348864  38 60 00 00 */	li r3, 0
/* 8034BC88 00348868  4E 80 00 20 */	blr 
lbl_8034BC8C:
/* 8034BC8C 0034886C  7C 65 1B 78 */	mr r5, r3
lbl_8034BC90:
/* 8034BC90 00348870  28 05 00 00 */	cmplwi r5, 0
/* 8034BC94 00348874  40 82 FF B8 */	bne lbl_8034BC4C
/* 8034BC98 00348878  38 60 00 01 */	li r3, 1
/* 8034BC9C 0034887C  4E 80 00 20 */	blr 

.global OSCheckActiveThreads
OSCheckActiveThreads:
/* 8034BCA0 00348880  7C 08 02 A6 */	mflr r0
/* 8034BCA4 00348884  3C 80 80 40 */	lis r4, lbl_80402420@ha
/* 8034BCA8 00348888  90 01 00 04 */	stw r0, 4(r1)
/* 8034BCAC 0034888C  3C 60 80 4A */	lis r3, lbl_804A7FB8@ha
/* 8034BCB0 00348890  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8034BCB4 00348894  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 8034BCB8 00348898  3B C4 24 20 */	addi r30, r4, lbl_80402420@l
/* 8034BCBC 0034889C  3B E3 7F B8 */	addi r31, r3, lbl_804A7FB8@l
/* 8034BCC0 003488A0  3B 80 00 00 */	li r28, 0
/* 8034BCC4 003488A4  4B FF B6 A1 */	bl OSDisableInterrupts
/* 8034BCC8 003488A8  3B 63 00 00 */	addi r27, r3, 0
/* 8034BCCC 003488AC  3B BF 00 00 */	addi r29, r31, 0
/* 8034BCD0 003488B0  3B 40 00 00 */	li r26, 0
lbl_8034BCD4:
/* 8034BCD4 003488B4  20 1A 00 1F */	subfic r0, r26, 0x1f
/* 8034BCD8 003488B8  80 8D BD 38 */	lwz r4, lbl_804D73D8@sda21(r13)
/* 8034BCDC 003488BC  38 60 00 01 */	li r3, 1
/* 8034BCE0 003488C0  7C 60 00 30 */	slw r0, r3, r0
/* 8034BCE4 003488C4  7C 80 00 39 */	and. r0, r4, r0
/* 8034BCE8 003488C8  41 82 00 44 */	beq lbl_8034BD2C
/* 8034BCEC 003488CC  80 1D 00 00 */	lwz r0, 0(r29)
/* 8034BCF0 003488D0  28 00 00 00 */	cmplwi r0, 0
/* 8034BCF4 003488D4  41 82 00 10 */	beq lbl_8034BD04
/* 8034BCF8 003488D8  80 1D 00 04 */	lwz r0, 4(r29)
/* 8034BCFC 003488DC  28 00 00 00 */	cmplwi r0, 0
/* 8034BD00 003488E0  40 82 00 68 */	bne lbl_8034BD68
lbl_8034BD04:
/* 8034BD04 003488E4  38 7E 00 00 */	addi r3, r30, 0
/* 8034BD08 003488E8  4C C6 31 82 */	crclr 6
/* 8034BD0C 003488EC  38 80 05 66 */	li r4, 0x566
/* 8034BD10 003488F0  4B FF 99 99 */	bl OSReport
/* 8034BD14 003488F4  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BD18 003488F8  4C C6 31 82 */	crclr 6
/* 8034BD1C 003488FC  38 80 05 66 */	li r4, 0x566
/* 8034BD20 00348900  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BD24 00348904  4B FF 9A 05 */	bl OSPanic
/* 8034BD28 00348908  48 00 00 40 */	b lbl_8034BD68
lbl_8034BD2C:
/* 8034BD2C 0034890C  80 1D 00 00 */	lwz r0, 0(r29)
/* 8034BD30 00348910  28 00 00 00 */	cmplwi r0, 0
/* 8034BD34 00348914  40 82 00 10 */	bne lbl_8034BD44
/* 8034BD38 00348918  80 1D 00 04 */	lwz r0, 4(r29)
/* 8034BD3C 0034891C  28 00 00 00 */	cmplwi r0, 0
/* 8034BD40 00348920  41 82 00 28 */	beq lbl_8034BD68
lbl_8034BD44:
/* 8034BD44 00348924  38 7E 00 6C */	addi r3, r30, 0x6c
/* 8034BD48 00348928  4C C6 31 82 */	crclr 6
/* 8034BD4C 0034892C  38 80 05 6B */	li r4, 0x56b
/* 8034BD50 00348930  4B FF 99 59 */	bl OSReport
/* 8034BD54 00348934  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BD58 00348938  4C C6 31 82 */	crclr 6
/* 8034BD5C 0034893C  38 80 05 6B */	li r4, 0x56b
/* 8034BD60 00348940  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BD64 00348944  4B FF 99 C5 */	bl OSPanic
lbl_8034BD68:
/* 8034BD68 00348948  7F A3 EB 78 */	mr r3, r29
/* 8034BD6C 0034894C  4B FF FE 99 */	bl CheckThreadQueue
/* 8034BD70 00348950  2C 03 00 00 */	cmpwi r3, 0
/* 8034BD74 00348954  40 82 00 28 */	bne lbl_8034BD9C
/* 8034BD78 00348958  38 7E 00 CC */	addi r3, r30, 0xcc
/* 8034BD7C 0034895C  4C C6 31 82 */	crclr 6
/* 8034BD80 00348960  38 80 05 6D */	li r4, 0x56d
/* 8034BD84 00348964  4B FF 99 25 */	bl OSReport
/* 8034BD88 00348968  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BD8C 0034896C  4C C6 31 82 */	crclr 6
/* 8034BD90 00348970  38 80 05 6D */	li r4, 0x56d
/* 8034BD94 00348974  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BD98 00348978  4B FF 99 91 */	bl OSPanic
lbl_8034BD9C:
/* 8034BD9C 0034897C  3B 5A 00 01 */	addi r26, r26, 1
/* 8034BDA0 00348980  2C 1A 00 1F */	cmpwi r26, 0x1f
/* 8034BDA4 00348984  3B BD 00 08 */	addi r29, r29, 8
/* 8034BDA8 00348988  40 81 FF 2C */	ble lbl_8034BCD4
/* 8034BDAC 0034898C  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 8034BDB0 00348990  80 63 00 DC */	lwz r3, 0x800000DC@l(r3)
/* 8034BDB4 00348994  28 03 00 00 */	cmplwi r3, 0
/* 8034BDB8 00348998  41 82 00 34 */	beq lbl_8034BDEC
/* 8034BDBC 0034899C  80 03 03 00 */	lwz r0, 0x300(r3)
/* 8034BDC0 003489A0  28 00 00 00 */	cmplwi r0, 0
/* 8034BDC4 003489A4  41 82 00 28 */	beq lbl_8034BDEC
/* 8034BDC8 003489A8  38 7E 01 14 */	addi r3, r30, 0x114
/* 8034BDCC 003489AC  4C C6 31 82 */	crclr 6
/* 8034BDD0 003489B0  38 80 05 72 */	li r4, 0x572
/* 8034BDD4 003489B4  4B FF 98 D5 */	bl OSReport
/* 8034BDD8 003489B8  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BDDC 003489BC  4C C6 31 82 */	crclr 6
/* 8034BDE0 003489C0  38 80 05 72 */	li r4, 0x572
/* 8034BDE4 003489C4  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BDE8 003489C8  4B FF 99 41 */	bl OSPanic
lbl_8034BDEC:
/* 8034BDEC 003489CC  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 8034BDF0 003489D0  38 63 00 DC */	addi r3, r3, 0x800000DC@l
/* 8034BDF4 003489D4  80 63 00 04 */	lwz r3, 4(r3)
/* 8034BDF8 003489D8  28 03 00 00 */	cmplwi r3, 0
/* 8034BDFC 003489DC  41 82 00 34 */	beq lbl_8034BE30
/* 8034BE00 003489E0  80 03 02 FC */	lwz r0, 0x2fc(r3)
/* 8034BE04 003489E4  28 00 00 00 */	cmplwi r0, 0
/* 8034BE08 003489E8  41 82 00 28 */	beq lbl_8034BE30
/* 8034BE0C 003489EC  38 7E 01 94 */	addi r3, r30, 0x194
/* 8034BE10 003489F0  4C C6 31 82 */	crclr 6
/* 8034BE14 003489F4  38 80 05 74 */	li r4, 0x574
/* 8034BE18 003489F8  4B FF 98 91 */	bl OSReport
/* 8034BE1C 003489FC  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BE20 00348A00  4C C6 31 82 */	crclr 6
/* 8034BE24 00348A04  38 80 05 74 */	li r4, 0x574
/* 8034BE28 00348A08  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BE2C 00348A0C  4B FF 98 FD */	bl OSPanic
lbl_8034BE30:
/* 8034BE30 00348A10  3C 60 80 00 */	lis r3, 0x800000DC@ha
/* 8034BE34 00348A14  83 A3 00 DC */	lwz r29, 0x800000DC@l(r3)
/* 8034BE38 00348A18  48 00 05 90 */	b lbl_8034C3C8
lbl_8034BE3C:
/* 8034BE3C 00348A1C  80 7D 02 FC */	lwz r3, 0x2fc(r29)
/* 8034BE40 00348A20  3B 9C 00 01 */	addi r28, r28, 1
/* 8034BE44 00348A24  28 03 00 00 */	cmplwi r3, 0
/* 8034BE48 00348A28  41 82 00 34 */	beq lbl_8034BE7C
/* 8034BE4C 00348A2C  80 03 03 00 */	lwz r0, 0x300(r3)
/* 8034BE50 00348A30  7C 1D 00 40 */	cmplw r29, r0
/* 8034BE54 00348A34  41 82 00 28 */	beq lbl_8034BE7C
/* 8034BE58 00348A38  38 7E 02 14 */	addi r3, r30, 0x214
/* 8034BE5C 00348A3C  4C C6 31 82 */	crclr 6
/* 8034BE60 00348A40  38 80 05 7C */	li r4, 0x57c
/* 8034BE64 00348A44  4B FF 98 45 */	bl OSReport
/* 8034BE68 00348A48  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BE6C 00348A4C  4C C6 31 82 */	crclr 6
/* 8034BE70 00348A50  38 80 05 7C */	li r4, 0x57c
/* 8034BE74 00348A54  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BE78 00348A58  4B FF 98 B1 */	bl OSPanic
lbl_8034BE7C:
/* 8034BE7C 00348A5C  80 7D 03 00 */	lwz r3, 0x300(r29)
/* 8034BE80 00348A60  28 03 00 00 */	cmplwi r3, 0
/* 8034BE84 00348A64  41 82 00 34 */	beq lbl_8034BEB8
/* 8034BE88 00348A68  80 03 02 FC */	lwz r0, 0x2fc(r3)
/* 8034BE8C 00348A6C  7C 1D 00 40 */	cmplw r29, r0
/* 8034BE90 00348A70  41 82 00 28 */	beq lbl_8034BEB8
/* 8034BE94 00348A74  38 7E 02 90 */	addi r3, r30, 0x290
/* 8034BE98 00348A78  4C C6 31 82 */	crclr 6
/* 8034BE9C 00348A7C  38 80 05 7E */	li r4, 0x57e
/* 8034BEA0 00348A80  4B FF 98 09 */	bl OSReport
/* 8034BEA4 00348A84  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BEA8 00348A88  4C C6 31 82 */	crclr 6
/* 8034BEAC 00348A8C  38 80 05 7E */	li r4, 0x57e
/* 8034BEB0 00348A90  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BEB4 00348A94  4B FF 98 75 */	bl OSPanic
lbl_8034BEB8:
/* 8034BEB8 00348A98  80 7D 03 08 */	lwz r3, 0x308(r29)
/* 8034BEBC 00348A9C  80 63 00 00 */	lwz r3, 0(r3)
/* 8034BEC0 00348AA0  3C 03 21 53 */	addis r0, r3, 0x2153
/* 8034BEC4 00348AA4  28 00 BA BE */	cmplwi r0, 0xbabe
/* 8034BEC8 00348AA8  41 82 00 28 */	beq lbl_8034BEF0
/* 8034BECC 00348AAC  38 7E 03 0C */	addi r3, r30, 0x30c
/* 8034BED0 00348AB0  4C C6 31 82 */	crclr 6
/* 8034BED4 00348AB4  38 80 05 81 */	li r4, 0x581
/* 8034BED8 00348AB8  4B FF 97 D1 */	bl OSReport
/* 8034BEDC 00348ABC  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BEE0 00348AC0  4C C6 31 82 */	crclr 6
/* 8034BEE4 00348AC4  38 80 05 81 */	li r4, 0x581
/* 8034BEE8 00348AC8  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BEEC 00348ACC  4B FF 98 3D */	bl OSPanic
lbl_8034BEF0:
/* 8034BEF0 00348AD0  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034BEF4 00348AD4  2C 00 00 00 */	cmpwi r0, 0
/* 8034BEF8 00348AD8  41 80 00 0C */	blt lbl_8034BF04
/* 8034BEFC 00348ADC  2C 00 00 20 */	cmpwi r0, 0x20
/* 8034BF00 00348AE0  40 81 00 28 */	ble lbl_8034BF28
lbl_8034BF04:
/* 8034BF04 00348AE4  38 7E 03 60 */	addi r3, r30, 0x360
/* 8034BF08 00348AE8  4C C6 31 82 */	crclr 6
/* 8034BF0C 00348AEC  38 80 05 84 */	li r4, 0x584
/* 8034BF10 00348AF0  4B FF 97 99 */	bl OSReport
/* 8034BF14 00348AF4  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BF18 00348AF8  4C C6 31 82 */	crclr 6
/* 8034BF1C 00348AFC  38 80 05 84 */	li r4, 0x584
/* 8034BF20 00348B00  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BF24 00348B04  4B FF 98 05 */	bl OSPanic
lbl_8034BF28:
/* 8034BF28 00348B08  80 1D 02 CC */	lwz r0, 0x2cc(r29)
/* 8034BF2C 00348B0C  2C 00 00 00 */	cmpwi r0, 0
/* 8034BF30 00348B10  40 80 00 28 */	bge lbl_8034BF58
/* 8034BF34 00348B14  38 7E 03 D4 */	addi r3, r30, 0x3d4
/* 8034BF38 00348B18  4C C6 31 82 */	crclr 6
/* 8034BF3C 00348B1C  38 80 05 85 */	li r4, 0x585
/* 8034BF40 00348B20  4B FF 97 69 */	bl OSReport
/* 8034BF44 00348B24  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BF48 00348B28  4C C6 31 82 */	crclr 6
/* 8034BF4C 00348B2C  38 80 05 85 */	li r4, 0x585
/* 8034BF50 00348B30  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BF54 00348B34  4B FF 97 D5 */	bl OSPanic
lbl_8034BF58:
/* 8034BF58 00348B38  38 7D 02 E8 */	addi r3, r29, 0x2e8
/* 8034BF5C 00348B3C  4B FF FC A9 */	bl CheckThreadQueue
/* 8034BF60 00348B40  2C 03 00 00 */	cmpwi r3, 0
/* 8034BF64 00348B44  40 82 00 28 */	bne lbl_8034BF8C
/* 8034BF68 00348B48  38 7E 04 10 */	addi r3, r30, 0x410
/* 8034BF6C 00348B4C  4C C6 31 82 */	crclr 6
/* 8034BF70 00348B50  38 80 05 86 */	li r4, 0x586
/* 8034BF74 00348B54  4B FF 97 35 */	bl OSReport
/* 8034BF78 00348B58  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BF7C 00348B5C  4C C6 31 82 */	crclr 6
/* 8034BF80 00348B60  38 80 05 86 */	li r4, 0x586
/* 8034BF84 00348B64  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034BF88 00348B68  4B FF 97 A1 */	bl OSPanic
lbl_8034BF8C:
/* 8034BF8C 00348B6C  A0 9D 02 C8 */	lhz r4, 0x2c8(r29)
/* 8034BF90 00348B70  2C 04 00 04 */	cmpwi r4, 4
/* 8034BF94 00348B74  41 82 02 00 */	beq lbl_8034C194
/* 8034BF98 00348B78  40 80 00 1C */	bge lbl_8034BFB4
/* 8034BF9C 00348B7C  2C 04 00 02 */	cmpwi r4, 2
/* 8034BFA0 00348B80  41 82 01 2C */	beq lbl_8034C0CC
/* 8034BFA4 00348B84  40 80 03 C8 */	bge lbl_8034C36C
/* 8034BFA8 00348B88  2C 04 00 01 */	cmpwi r4, 1
/* 8034BFAC 00348B8C  40 80 00 14 */	bge lbl_8034BFC0
/* 8034BFB0 00348B90  48 00 03 BC */	b lbl_8034C36C
lbl_8034BFB4:
/* 8034BFB4 00348B94  2C 04 00 08 */	cmpwi r4, 8
/* 8034BFB8 00348B98  41 82 03 74 */	beq lbl_8034C32C
/* 8034BFBC 00348B9C  48 00 03 B0 */	b lbl_8034C36C
lbl_8034BFC0:
/* 8034BFC0 00348BA0  80 1D 02 CC */	lwz r0, 0x2cc(r29)
/* 8034BFC4 00348BA4  2C 00 00 00 */	cmpwi r0, 0
/* 8034BFC8 00348BA8  41 81 03 C8 */	bgt lbl_8034C390
/* 8034BFCC 00348BAC  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034BFD0 00348BB0  80 7D 02 DC */	lwz r3, 0x2dc(r29)
/* 8034BFD4 00348BB4  54 00 18 38 */	slwi r0, r0, 3
/* 8034BFD8 00348BB8  7C 1F 02 14 */	add r0, r31, r0
/* 8034BFDC 00348BBC  7C 03 00 40 */	cmplw r3, r0
/* 8034BFE0 00348BC0  41 82 00 28 */	beq lbl_8034C008
/* 8034BFE4 00348BC4  38 7E 04 5C */	addi r3, r30, 0x45c
/* 8034BFE8 00348BC8  4C C6 31 82 */	crclr 6
/* 8034BFEC 00348BCC  38 80 05 8C */	li r4, 0x58c
/* 8034BFF0 00348BD0  4B FF 96 B9 */	bl OSReport
/* 8034BFF4 00348BD4  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034BFF8 00348BD8  4C C6 31 82 */	crclr 6
/* 8034BFFC 00348BDC  38 80 05 8C */	li r4, 0x58c
/* 8034C000 00348BE0  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C004 00348BE4  4B FF 97 25 */	bl OSPanic
lbl_8034C008:
/* 8034C008 00348BE8  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034C00C 00348BEC  54 00 18 38 */	slwi r0, r0, 3
/* 8034C010 00348BF0  7C 7F 00 2E */	lwzx r3, r31, r0
/* 8034C014 00348BF4  48 00 00 18 */	b lbl_8034C02C
lbl_8034C018:
/* 8034C018 00348BF8  7C 1D 18 40 */	cmplw r29, r3
/* 8034C01C 00348BFC  40 82 00 0C */	bne lbl_8034C028
/* 8034C020 00348C00  38 00 00 01 */	li r0, 1
/* 8034C024 00348C04  48 00 00 14 */	b lbl_8034C038
lbl_8034C028:
/* 8034C028 00348C08  80 63 02 E0 */	lwz r3, 0x2e0(r3)
lbl_8034C02C:
/* 8034C02C 00348C0C  28 03 00 00 */	cmplwi r3, 0
/* 8034C030 00348C10  40 82 FF E8 */	bne lbl_8034C018
/* 8034C034 00348C14  38 00 00 00 */	li r0, 0
lbl_8034C038:
/* 8034C038 00348C18  2C 00 00 00 */	cmpwi r0, 0
/* 8034C03C 00348C1C  40 82 00 28 */	bne lbl_8034C064
/* 8034C040 00348C20  38 7E 04 B0 */	addi r3, r30, 0x4b0
/* 8034C044 00348C24  4C C6 31 82 */	crclr 6
/* 8034C048 00348C28  38 80 05 8D */	li r4, 0x58d
/* 8034C04C 00348C2C  4B FF 96 5D */	bl OSReport
/* 8034C050 00348C30  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C054 00348C34  4C C6 31 82 */	crclr 6
/* 8034C058 00348C38  38 80 05 8D */	li r4, 0x58d
/* 8034C05C 00348C3C  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C060 00348C40  4B FF 96 C9 */	bl OSPanic
lbl_8034C064:
/* 8034C064 00348C44  80 9D 02 D4 */	lwz r4, 0x2d4(r29)
/* 8034C068 00348C48  80 7D 02 F4 */	lwz r3, 0x2f4(r29)
/* 8034C06C 00348C4C  48 00 00 24 */	b lbl_8034C090
lbl_8034C070:
/* 8034C070 00348C50  80 A3 00 00 */	lwz r5, 0(r3)
/* 8034C074 00348C54  28 05 00 00 */	cmplwi r5, 0
/* 8034C078 00348C58  41 82 00 14 */	beq lbl_8034C08C
/* 8034C07C 00348C5C  80 05 02 D0 */	lwz r0, 0x2d0(r5)
/* 8034C080 00348C60  7C 00 20 00 */	cmpw r0, r4
/* 8034C084 00348C64  40 80 00 08 */	bge lbl_8034C08C
/* 8034C088 00348C68  7C 04 03 78 */	mr r4, r0
lbl_8034C08C:
/* 8034C08C 00348C6C  80 63 00 10 */	lwz r3, 0x10(r3)
lbl_8034C090:
/* 8034C090 00348C70  28 03 00 00 */	cmplwi r3, 0
/* 8034C094 00348C74  40 82 FF DC */	bne lbl_8034C070
/* 8034C098 00348C78  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034C09C 00348C7C  7C 00 20 00 */	cmpw r0, r4
/* 8034C0A0 00348C80  41 82 02 F0 */	beq lbl_8034C390
/* 8034C0A4 00348C84  38 7E 05 04 */	addi r3, r30, 0x504
/* 8034C0A8 00348C88  4C C6 31 82 */	crclr 6
/* 8034C0AC 00348C8C  38 80 05 8E */	li r4, 0x58e
/* 8034C0B0 00348C90  4B FF 95 F9 */	bl OSReport
/* 8034C0B4 00348C94  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C0B8 00348C98  4C C6 31 82 */	crclr 6
/* 8034C0BC 00348C9C  38 80 05 8E */	li r4, 0x58e
/* 8034C0C0 00348CA0  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C0C4 00348CA4  4B FF 96 65 */	bl OSPanic
/* 8034C0C8 00348CA8  48 00 02 C8 */	b lbl_8034C390
lbl_8034C0CC:
/* 8034C0CC 00348CAC  80 1D 02 CC */	lwz r0, 0x2cc(r29)
/* 8034C0D0 00348CB0  2C 00 00 00 */	cmpwi r0, 0
/* 8034C0D4 00348CB4  40 81 00 28 */	ble lbl_8034C0FC
/* 8034C0D8 00348CB8  38 7E 05 60 */	addi r3, r30, 0x560
/* 8034C0DC 00348CBC  4C C6 31 82 */	crclr 6
/* 8034C0E0 00348CC0  38 80 05 92 */	li r4, 0x592
/* 8034C0E4 00348CC4  4B FF 95 C5 */	bl OSReport
/* 8034C0E8 00348CC8  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C0EC 00348CCC  4C C6 31 82 */	crclr 6
/* 8034C0F0 00348CD0  38 80 05 92 */	li r4, 0x592
/* 8034C0F4 00348CD4  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C0F8 00348CD8  4B FF 96 31 */	bl OSPanic
lbl_8034C0FC:
/* 8034C0FC 00348CDC  80 1D 02 DC */	lwz r0, 0x2dc(r29)
/* 8034C100 00348CE0  28 00 00 00 */	cmplwi r0, 0
/* 8034C104 00348CE4  41 82 00 28 */	beq lbl_8034C12C
/* 8034C108 00348CE8  38 7E 05 A4 */	addi r3, r30, 0x5a4
/* 8034C10C 00348CEC  4C C6 31 82 */	crclr 6
/* 8034C110 00348CF0  38 80 05 93 */	li r4, 0x593
/* 8034C114 00348CF4  4B FF 95 95 */	bl OSReport
/* 8034C118 00348CF8  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C11C 00348CFC  4C C6 31 82 */	crclr 6
/* 8034C120 00348D00  38 80 05 93 */	li r4, 0x593
/* 8034C124 00348D04  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C128 00348D08  4B FF 96 01 */	bl OSPanic
lbl_8034C12C:
/* 8034C12C 00348D0C  80 9D 02 D4 */	lwz r4, 0x2d4(r29)
/* 8034C130 00348D10  80 7D 02 F4 */	lwz r3, 0x2f4(r29)
/* 8034C134 00348D14  48 00 00 24 */	b lbl_8034C158
lbl_8034C138:
/* 8034C138 00348D18  80 A3 00 00 */	lwz r5, 0(r3)
/* 8034C13C 00348D1C  28 05 00 00 */	cmplwi r5, 0
/* 8034C140 00348D20  41 82 00 14 */	beq lbl_8034C154
/* 8034C144 00348D24  80 05 02 D0 */	lwz r0, 0x2d0(r5)
/* 8034C148 00348D28  7C 00 20 00 */	cmpw r0, r4
/* 8034C14C 00348D2C  40 80 00 08 */	bge lbl_8034C154
/* 8034C150 00348D30  7C 04 03 78 */	mr r4, r0
lbl_8034C154:
/* 8034C154 00348D34  80 63 00 10 */	lwz r3, 0x10(r3)
lbl_8034C158:
/* 8034C158 00348D38  28 03 00 00 */	cmplwi r3, 0
/* 8034C15C 00348D3C  40 82 FF DC */	bne lbl_8034C138
/* 8034C160 00348D40  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034C164 00348D44  7C 00 20 00 */	cmpw r0, r4
/* 8034C168 00348D48  41 82 02 28 */	beq lbl_8034C390
/* 8034C16C 00348D4C  38 7E 05 04 */	addi r3, r30, 0x504
/* 8034C170 00348D50  4C C6 31 82 */	crclr 6
/* 8034C174 00348D54  38 80 05 94 */	li r4, 0x594
/* 8034C178 00348D58  4B FF 95 31 */	bl OSReport
/* 8034C17C 00348D5C  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C180 00348D60  4C C6 31 82 */	crclr 6
/* 8034C184 00348D64  38 80 05 94 */	li r4, 0x594
/* 8034C188 00348D68  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C18C 00348D6C  4B FF 95 9D */	bl OSPanic
/* 8034C190 00348D70  48 00 02 00 */	b lbl_8034C390
lbl_8034C194:
/* 8034C194 00348D74  80 1D 02 DC */	lwz r0, 0x2dc(r29)
/* 8034C198 00348D78  28 00 00 00 */	cmplwi r0, 0
/* 8034C19C 00348D7C  40 82 00 28 */	bne lbl_8034C1C4
/* 8034C1A0 00348D80  38 7E 05 E0 */	addi r3, r30, 0x5e0
/* 8034C1A4 00348D84  4C C6 31 82 */	crclr 6
/* 8034C1A8 00348D88  38 80 05 97 */	li r4, 0x597
/* 8034C1AC 00348D8C  4B FF 94 FD */	bl OSReport
/* 8034C1B0 00348D90  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C1B4 00348D94  4C C6 31 82 */	crclr 6
/* 8034C1B8 00348D98  38 80 05 97 */	li r4, 0x597
/* 8034C1BC 00348D9C  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C1C0 00348DA0  4B FF 95 69 */	bl OSPanic
lbl_8034C1C4:
/* 8034C1C4 00348DA4  80 7D 02 DC */	lwz r3, 0x2dc(r29)
/* 8034C1C8 00348DA8  4B FF FA 3D */	bl CheckThreadQueue
/* 8034C1CC 00348DAC  2C 03 00 00 */	cmpwi r3, 0
/* 8034C1D0 00348DB0  40 82 00 28 */	bne lbl_8034C1F8
/* 8034C1D4 00348DB4  38 7E 06 1C */	addi r3, r30, 0x61c
/* 8034C1D8 00348DB8  4C C6 31 82 */	crclr 6
/* 8034C1DC 00348DBC  38 80 05 98 */	li r4, 0x598
/* 8034C1E0 00348DC0  4B FF 94 C9 */	bl OSReport
/* 8034C1E4 00348DC4  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C1E8 00348DC8  4C C6 31 82 */	crclr 6
/* 8034C1EC 00348DCC  38 80 05 98 */	li r4, 0x598
/* 8034C1F0 00348DD0  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C1F4 00348DD4  4B FF 95 35 */	bl OSPanic
lbl_8034C1F8:
/* 8034C1F8 00348DD8  80 7D 02 DC */	lwz r3, 0x2dc(r29)
/* 8034C1FC 00348DDC  80 63 00 00 */	lwz r3, 0(r3)
/* 8034C200 00348DE0  48 00 00 18 */	b lbl_8034C218
lbl_8034C204:
/* 8034C204 00348DE4  7C 1D 18 40 */	cmplw r29, r3
/* 8034C208 00348DE8  40 82 00 0C */	bne lbl_8034C214
/* 8034C20C 00348DEC  38 00 00 01 */	li r0, 1
/* 8034C210 00348DF0  48 00 00 14 */	b lbl_8034C224
lbl_8034C214:
/* 8034C214 00348DF4  80 63 02 E0 */	lwz r3, 0x2e0(r3)
lbl_8034C218:
/* 8034C218 00348DF8  28 03 00 00 */	cmplwi r3, 0
/* 8034C21C 00348DFC  40 82 FF E8 */	bne lbl_8034C204
/* 8034C220 00348E00  38 00 00 00 */	li r0, 0
lbl_8034C224:
/* 8034C224 00348E04  2C 00 00 00 */	cmpwi r0, 0
/* 8034C228 00348E08  40 82 00 28 */	bne lbl_8034C250
/* 8034C22C 00348E0C  38 7E 06 60 */	addi r3, r30, 0x660
/* 8034C230 00348E10  4C C6 31 82 */	crclr 6
/* 8034C234 00348E14  38 80 05 99 */	li r4, 0x599
/* 8034C238 00348E18  4B FF 94 71 */	bl OSReport
/* 8034C23C 00348E1C  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C240 00348E20  4C C6 31 82 */	crclr 6
/* 8034C244 00348E24  38 80 05 99 */	li r4, 0x599
/* 8034C248 00348E28  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C24C 00348E2C  4B FF 94 DD */	bl OSPanic
lbl_8034C250:
/* 8034C250 00348E30  80 1D 02 CC */	lwz r0, 0x2cc(r29)
/* 8034C254 00348E34  2C 00 00 00 */	cmpwi r0, 0
/* 8034C258 00348E38  41 81 00 6C */	bgt lbl_8034C2C4
/* 8034C25C 00348E3C  80 9D 02 D4 */	lwz r4, 0x2d4(r29)
/* 8034C260 00348E40  80 7D 02 F4 */	lwz r3, 0x2f4(r29)
/* 8034C264 00348E44  48 00 00 24 */	b lbl_8034C288
lbl_8034C268:
/* 8034C268 00348E48  80 A3 00 00 */	lwz r5, 0(r3)
/* 8034C26C 00348E4C  28 05 00 00 */	cmplwi r5, 0
/* 8034C270 00348E50  41 82 00 14 */	beq lbl_8034C284
/* 8034C274 00348E54  80 05 02 D0 */	lwz r0, 0x2d0(r5)
/* 8034C278 00348E58  7C 00 20 00 */	cmpw r0, r4
/* 8034C27C 00348E5C  40 80 00 08 */	bge lbl_8034C284
/* 8034C280 00348E60  7C 04 03 78 */	mr r4, r0
lbl_8034C284:
/* 8034C284 00348E64  80 63 00 10 */	lwz r3, 0x10(r3)
lbl_8034C288:
/* 8034C288 00348E68  28 03 00 00 */	cmplwi r3, 0
/* 8034C28C 00348E6C  40 82 FF DC */	bne lbl_8034C268
/* 8034C290 00348E70  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034C294 00348E74  7C 00 20 00 */	cmpw r0, r4
/* 8034C298 00348E78  41 82 00 5C */	beq lbl_8034C2F4
/* 8034C29C 00348E7C  38 7E 05 04 */	addi r3, r30, 0x504
/* 8034C2A0 00348E80  4C C6 31 82 */	crclr 6
/* 8034C2A4 00348E84  38 80 05 9C */	li r4, 0x59c
/* 8034C2A8 00348E88  4B FF 94 01 */	bl OSReport
/* 8034C2AC 00348E8C  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C2B0 00348E90  4C C6 31 82 */	crclr 6
/* 8034C2B4 00348E94  38 80 05 9C */	li r4, 0x59c
/* 8034C2B8 00348E98  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C2BC 00348E9C  4B FF 94 6D */	bl OSPanic
/* 8034C2C0 00348EA0  48 00 00 34 */	b lbl_8034C2F4
lbl_8034C2C4:
/* 8034C2C4 00348EA4  80 1D 02 D0 */	lwz r0, 0x2d0(r29)
/* 8034C2C8 00348EA8  2C 00 00 20 */	cmpwi r0, 0x20
/* 8034C2CC 00348EAC  41 82 00 28 */	beq lbl_8034C2F4
/* 8034C2D0 00348EB0  38 7E 06 A4 */	addi r3, r30, 0x6a4
/* 8034C2D4 00348EB4  4C C6 31 82 */	crclr 6
/* 8034C2D8 00348EB8  38 80 05 A0 */	li r4, 0x5a0
/* 8034C2DC 00348EBC  4B FF 93 CD */	bl OSReport
/* 8034C2E0 00348EC0  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C2E4 00348EC4  4C C6 31 82 */	crclr 6
/* 8034C2E8 00348EC8  38 80 05 A0 */	li r4, 0x5a0
/* 8034C2EC 00348ECC  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C2F0 00348ED0  4B FF 94 39 */	bl OSPanic
lbl_8034C2F4:
/* 8034C2F4 00348ED4  7F A3 EB 78 */	mr r3, r29
/* 8034C2F8 00348ED8  4B FF BD 55 */	bl __OSCheckDeadLock
/* 8034C2FC 00348EDC  2C 03 00 00 */	cmpwi r3, 0
/* 8034C300 00348EE0  41 82 00 90 */	beq lbl_8034C390
/* 8034C304 00348EE4  38 7E 06 E0 */	addi r3, r30, 0x6e0
/* 8034C308 00348EE8  4C C6 31 82 */	crclr 6
/* 8034C30C 00348EEC  38 80 05 A2 */	li r4, 0x5a2
/* 8034C310 00348EF0  4B FF 93 99 */	bl OSReport
/* 8034C314 00348EF4  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C318 00348EF8  4C C6 31 82 */	crclr 6
/* 8034C31C 00348EFC  38 80 05 A2 */	li r4, 0x5a2
/* 8034C320 00348F00  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C324 00348F04  4B FF 94 05 */	bl OSPanic
/* 8034C328 00348F08  48 00 00 68 */	b lbl_8034C390
lbl_8034C32C:
/* 8034C32C 00348F0C  80 1D 02 F4 */	lwz r0, 0x2f4(r29)
/* 8034C330 00348F10  28 00 00 00 */	cmplwi r0, 0
/* 8034C334 00348F14  40 82 00 10 */	bne lbl_8034C344
/* 8034C338 00348F18  80 1D 02 F8 */	lwz r0, 0x2f8(r29)
/* 8034C33C 00348F1C  28 00 00 00 */	cmplwi r0, 0
/* 8034C340 00348F20  41 82 00 50 */	beq lbl_8034C390
lbl_8034C344:
/* 8034C344 00348F24  38 7E 07 20 */	addi r3, r30, 0x720
/* 8034C348 00348F28  4C C6 31 82 */	crclr 6
/* 8034C34C 00348F2C  38 80 05 A6 */	li r4, 0x5a6
/* 8034C350 00348F30  4B FF 93 59 */	bl OSReport
/* 8034C354 00348F34  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C358 00348F38  4C C6 31 82 */	crclr 6
/* 8034C35C 00348F3C  38 80 05 A6 */	li r4, 0x5a6
/* 8034C360 00348F40  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C364 00348F44  4B FF 93 C5 */	bl OSPanic
/* 8034C368 00348F48  48 00 00 28 */	b lbl_8034C390
lbl_8034C36C:
/* 8034C36C 00348F4C  4C C6 31 82 */	crclr 6
/* 8034C370 00348F50  38 BD 00 00 */	addi r5, r29, 0
/* 8034C374 00348F54  38 7E 07 88 */	addi r3, r30, 0x788
/* 8034C378 00348F58  4B FF 93 31 */	bl OSReport
/* 8034C37C 00348F5C  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C380 00348F60  4C C6 31 82 */	crclr 6
/* 8034C384 00348F64  38 80 05 AC */	li r4, 0x5ac
/* 8034C388 00348F68  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C38C 00348F6C  4B FF 93 9D */	bl OSPanic
lbl_8034C390:
/* 8034C390 00348F70  7F A3 EB 78 */	mr r3, r29
/* 8034C394 00348F74  4B FF BC F1 */	bl __OSCheckMutexes
/* 8034C398 00348F78  2C 03 00 00 */	cmpwi r3, 0
/* 8034C39C 00348F7C  40 82 00 28 */	bne lbl_8034C3C4
/* 8034C3A0 00348F80  38 7E 07 D0 */	addi r3, r30, 0x7d0
/* 8034C3A4 00348F84  4C C6 31 82 */	crclr 6
/* 8034C3A8 00348F88  38 80 05 B1 */	li r4, 0x5b1
/* 8034C3AC 00348F8C  4B FF 92 FD */	bl OSReport
/* 8034C3B0 00348F90  38 7E 00 60 */	addi r3, r30, 0x60
/* 8034C3B4 00348F94  4C C6 31 82 */	crclr 6
/* 8034C3B8 00348F98  38 80 05 B1 */	li r4, 0x5b1
/* 8034C3BC 00348F9C  38 AD A5 88 */	addi r5, r13, lbl_804D5C28@sda21
/* 8034C3C0 00348FA0  4B FF 93 69 */	bl OSPanic
lbl_8034C3C4:
/* 8034C3C4 00348FA4  83 BD 02 FC */	lwz r29, 0x2fc(r29)
lbl_8034C3C8:
/* 8034C3C8 00348FA8  28 1D 00 00 */	cmplwi r29, 0
/* 8034C3CC 00348FAC  40 82 FA 70 */	bne lbl_8034BE3C
/* 8034C3D0 00348FB0  7F 63 DB 78 */	mr r3, r27
/* 8034C3D4 00348FB4  4B FF AF B9 */	bl OSRestoreInterrupts
/* 8034C3D8 00348FB8  7F 83 E3 78 */	mr r3, r28
/* 8034C3DC 00348FBC  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 8034C3E0 00348FC0  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8034C3E4 00348FC4  38 21 00 38 */	addi r1, r1, 0x38
/* 8034C3E8 00348FC8  7C 08 03 A6 */	mtlr r0
/* 8034C3EC 00348FCC  4E 80 00 20 */	blr 

.section .data
    .balign 8
.global lbl_80402420
lbl_80402420:
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head != NULL && RunQueue[prio].tail != NULL in %d\n"
    .balign 4
    .asciz "OSThread.c"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed RunQueue[prio].head == NULL && RunQueue[prio].tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&RunQueue[prio]) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.head == NULL || __OSActiveThreadQueue.head->linkActive.prev == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSActiveThreadQueue.tail == NULL || __OSActiveThreadQueue.tail->linkActive.next == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.next == NULL || thread == thread->linkActive.next->linkActive.prev in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->linkActive.prev == NULL || thread == thread->linkActive.prev->linkActive.next in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed *(thread->stackEnd) == OS_THREAD_STACK_MAGIC in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed OS_PRIORITY_MIN <= thread->priority && thread->priority <= OS_PRIORITY_MAX+1 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed 0 <= thread->suspend in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(&thread->queueJoin) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == &RunQueue[thread->priority] in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(&RunQueue[thread->priority], thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == __OSGetEffectivePriority(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !IsSuspended(thread->suspend) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queue != NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed CheckThreadQueue(thread->queue) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed IsMember(thread->queue, thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->priority == 32 in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed !__OSCheckDeadLock(thread) in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed thread->queueMutex.head == NULL && thread->queueMutex.tail == NULL in %d\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed. unkown thread state (%d) of thread %p\n"
    .balign 4
    .asciz "OSCheckActiveThreads: Failed __OSCheckMutexes(thread) in %d\n"
    .balign 4


.section .bss, "wa"
    .balign 8
.global lbl_804A7FB8
lbl_804A7FB8:
	.skip 0x9E8


.section .sdata
    .balign 8
.global lbl_804D5C28
lbl_804D5C28:
    .4byte 0x00000000
    .4byte 0x00000000


.section .sbss
    .balign 8
.global lbl_804D73D8
lbl_804D73D8:
	.skip 0x4
.global lbl_804D73DC
lbl_804D73DC:
	.skip 0x4
.global lbl_804D73E0
lbl_804D73E0:
	.skip 0x8
