.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240

.global LCQueueWait
LCQueueWait:
/* 80344B2C 0034170C  38 63 00 01 */	addi r3, r3, 1
lbl_80344B30:
/* 80344B30 00341710  7C 98 E2 A6 */	mfspr r4, 0x398
/* 80344B34 00341714  54 84 47 3E */	rlwinm r4, r4, 8, 0x1c, 0x1f
/* 80344B38 00341718  7D 04 18 00 */	cmpw cr2, r4, r3
/* 80344B3C 0034171C  40 88 FF F4 */	bge cr2, lbl_80344B30
/* 80344B40 00341720  4E 80 00 20 */	blr 

.global L2GlobalInvalidate
L2GlobalInvalidate:
/* 80344B44 00341724  7C 08 02 A6 */	mflr r0
/* 80344B48 00341728  90 01 00 04 */	stw r0, 4(r1)
/* 80344B4C 0034172C  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80344B50 00341730  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80344B54 00341734  7C 00 04 AC */	sync 0
/* 80344B58 00341738  4B FF 13 1D */	bl PPCMfl2cr
/* 80344B5C 0034173C  54 63 00 7E */	clrlwi r3, r3, 1
/* 80344B60 00341740  4B FF 13 1D */	bl PPCMtl2cr
/* 80344B64 00341744  7C 00 04 AC */	sync 0
/* 80344B68 00341748  4B FF 13 0D */	bl PPCMfl2cr
/* 80344B6C 0034174C  64 63 00 20 */	oris r3, r3, 0x20
/* 80344B70 00341750  4B FF 13 0D */	bl PPCMtl2cr
/* 80344B74 00341754  48 00 00 04 */	b lbl_80344B78
lbl_80344B78:
/* 80344B78 00341758  48 00 00 04 */	b lbl_80344B7C
lbl_80344B7C:
/* 80344B7C 0034175C  4B FF 12 F9 */	bl PPCMfl2cr
/* 80344B80 00341760  54 60 07 FE */	clrlwi r0, r3, 0x1f
/* 80344B84 00341764  28 00 00 00 */	cmplwi r0, 0
/* 80344B88 00341768  40 82 FF F4 */	bne lbl_80344B7C
/* 80344B8C 0034176C  4B FF 12 E9 */	bl PPCMfl2cr
/* 80344B90 00341770  54 63 02 D2 */	rlwinm r3, r3, 0, 0xb, 9
/* 80344B94 00341774  4B FF 12 E9 */	bl PPCMtl2cr
/* 80344B98 00341778  48 00 00 04 */	b lbl_80344B9C
lbl_80344B9C:
/* 80344B9C 0034177C  3C 60 80 40 */	lis r3, lbl_80401BF0@ha
/* 80344BA0 00341780  3B E3 1B F0 */	addi r31, r3, lbl_80401BF0@l
/* 80344BA4 00341784  48 00 00 04 */	b lbl_80344BA8
lbl_80344BA8:
/* 80344BA8 00341788  48 00 00 10 */	b lbl_80344BB8
lbl_80344BAC:
/* 80344BAC 0034178C  7F E3 FB 78 */	mr r3, r31
/* 80344BB0 00341790  4C C6 31 82 */	crclr 6
/* 80344BB4 00341794  4B FF 13 C5 */	bl DBPrintf
lbl_80344BB8:
/* 80344BB8 00341798  4B FF 12 BD */	bl PPCMfl2cr
/* 80344BBC 0034179C  54 60 07 FE */	clrlwi r0, r3, 0x1f
/* 80344BC0 003417A0  28 00 00 00 */	cmplwi r0, 0
/* 80344BC4 003417A4  40 82 FF E8 */	bne lbl_80344BAC
/* 80344BC8 003417A8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80344BCC 003417AC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80344BD0 003417B0  38 21 00 10 */	addi r1, r1, 0x10
/* 80344BD4 003417B4  7C 08 03 A6 */	mtlr r0
/* 80344BD8 003417B8  4E 80 00 20 */	blr 

.global DMAErrorHandler
DMAErrorHandler:
/* 80344BDC 003417BC  7C 08 02 A6 */	mflr r0
/* 80344BE0 003417C0  90 01 00 04 */	stw r0, 4(r1)
/* 80344BE4 003417C4  94 21 FF 80 */	stwu r1, -0x80(r1)
/* 80344BE8 003417C8  93 E1 00 7C */	stw r31, 0x7c(r1)
/* 80344BEC 003417CC  93 C1 00 78 */	stw r30, 0x78(r1)
/* 80344BF0 003417D0  93 A1 00 74 */	stw r29, 0x74(r1)
/* 80344BF4 003417D4  40 86 00 24 */	bne cr1, lbl_80344C18
/* 80344BF8 003417D8  D8 21 00 28 */	stfd f1, 0x28(r1)
/* 80344BFC 003417DC  D8 41 00 30 */	stfd f2, 0x30(r1)
/* 80344C00 003417E0  D8 61 00 38 */	stfd f3, 0x38(r1)
/* 80344C04 003417E4  D8 81 00 40 */	stfd f4, 0x40(r1)
/* 80344C08 003417E8  D8 A1 00 48 */	stfd f5, 0x48(r1)
/* 80344C0C 003417EC  D8 C1 00 50 */	stfd f6, 0x50(r1)
/* 80344C10 003417F0  D8 E1 00 58 */	stfd f7, 0x58(r1)
/* 80344C14 003417F4  D9 01 00 60 */	stfd f8, 0x60(r1)
lbl_80344C18:
/* 80344C18 003417F8  90 61 00 08 */	stw r3, 8(r1)
/* 80344C1C 003417FC  90 81 00 0C */	stw r4, 0xc(r1)
/* 80344C20 00341800  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80344C24 00341804  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80344C28 00341808  90 E1 00 18 */	stw r7, 0x18(r1)
/* 80344C2C 0034180C  91 01 00 1C */	stw r8, 0x1c(r1)
/* 80344C30 00341810  91 21 00 20 */	stw r9, 0x20(r1)
/* 80344C34 00341814  91 41 00 24 */	stw r10, 0x24(r1)
/* 80344C38 00341818  7C 9D 23 78 */	mr r29, r4
/* 80344C3C 0034181C  3C 60 80 40 */	lis r3, lbl_80401BF0@ha
/* 80344C40 00341820  3B E3 1B F0 */	addi r31, r3, lbl_80401BF0@l
/* 80344C44 00341824  4B FF 12 65 */	bl PPCMfhid2
/* 80344C48 00341828  7C 7E 1B 78 */	mr r30, r3
/* 80344C4C 0034182C  4C C6 31 82 */	crclr 6
/* 80344C50 00341830  38 7F 00 2C */	addi r3, r31, 0x2c
/* 80344C54 00341834  48 00 0A 55 */	bl OSReport
/* 80344C58 00341838  80 BD 01 9C */	lwz r5, 0x19c(r29)
/* 80344C5C 0034183C  7F C4 F3 78 */	mr r4, r30
/* 80344C60 00341840  38 7F 00 44 */	addi r3, r31, 0x44
/* 80344C64 00341844  4C C6 31 82 */	crclr 6
/* 80344C68 00341848  48 00 0A 41 */	bl OSReport
/* 80344C6C 0034184C  57 C0 02 16 */	rlwinm r0, r30, 0, 8, 0xb
/* 80344C70 00341850  28 00 00 00 */	cmplwi r0, 0
/* 80344C74 00341854  41 82 00 14 */	beq lbl_80344C88
/* 80344C78 00341858  80 1D 01 9C */	lwz r0, 0x19c(r29)
/* 80344C7C 0034185C  54 00 02 94 */	rlwinm r0, r0, 0, 0xa, 0xa
/* 80344C80 00341860  28 00 00 00 */	cmplwi r0, 0
/* 80344C84 00341864  40 82 00 1C */	bne lbl_80344CA0
lbl_80344C88:
/* 80344C88 00341868  38 7F 00 60 */	addi r3, r31, 0x60
/* 80344C8C 0034186C  4C C6 31 82 */	crclr 6
/* 80344C90 00341870  48 00 0A 19 */	bl OSReport
/* 80344C94 00341874  7F A3 EB 78 */	mr r3, r29
/* 80344C98 00341878  48 00 06 9D */	bl OSDumpContext
/* 80344C9C 0034187C  4B FF 11 F9 */	bl PPCHalt
lbl_80344CA0:
/* 80344CA0 00341880  38 7F 00 90 */	addi r3, r31, 0x90
/* 80344CA4 00341884  4C C6 31 82 */	crclr 6
/* 80344CA8 00341888  48 00 0A 01 */	bl OSReport
/* 80344CAC 0034188C  38 7F 00 CC */	addi r3, r31, 0xcc
/* 80344CB0 00341890  4C C6 31 82 */	crclr 6
/* 80344CB4 00341894  48 00 09 F5 */	bl OSReport
/* 80344CB8 00341898  57 C0 02 10 */	rlwinm r0, r30, 0, 8, 8
/* 80344CBC 0034189C  28 00 00 00 */	cmplwi r0, 0
/* 80344CC0 003418A0  41 82 00 10 */	beq lbl_80344CD0
/* 80344CC4 003418A4  38 7F 01 04 */	addi r3, r31, 0x104
/* 80344CC8 003418A8  4C C6 31 82 */	crclr 6
/* 80344CCC 003418AC  48 00 09 DD */	bl OSReport
lbl_80344CD0:
/* 80344CD0 003418B0  57 C0 02 52 */	rlwinm r0, r30, 0, 9, 9
/* 80344CD4 003418B4  28 00 00 00 */	cmplwi r0, 0
/* 80344CD8 003418B8  41 82 00 10 */	beq lbl_80344CE8
/* 80344CDC 003418BC  38 7F 01 44 */	addi r3, r31, 0x144
/* 80344CE0 003418C0  4C C6 31 82 */	crclr 6
/* 80344CE4 003418C4  48 00 09 C5 */	bl OSReport
lbl_80344CE8:
/* 80344CE8 003418C8  57 C0 02 94 */	rlwinm r0, r30, 0, 0xa, 0xa
/* 80344CEC 003418CC  28 00 00 00 */	cmplwi r0, 0
/* 80344CF0 003418D0  41 82 00 10 */	beq lbl_80344D00
/* 80344CF4 003418D4  38 7F 01 70 */	addi r3, r31, 0x170
/* 80344CF8 003418D8  4C C6 31 82 */	crclr 6
/* 80344CFC 003418DC  48 00 09 AD */	bl OSReport
lbl_80344D00:
/* 80344D00 003418E0  57 C0 02 D6 */	rlwinm r0, r30, 0, 0xb, 0xb
/* 80344D04 003418E4  28 00 00 00 */	cmplwi r0, 0
/* 80344D08 003418E8  41 82 00 10 */	beq lbl_80344D18
/* 80344D0C 003418EC  38 7F 01 90 */	addi r3, r31, 0x190
/* 80344D10 003418F0  4C C6 31 82 */	crclr 6
/* 80344D14 003418F4  48 00 09 95 */	bl OSReport
lbl_80344D18:
/* 80344D18 003418F8  7F C3 F3 78 */	mr r3, r30
/* 80344D1C 003418FC  4B FF 11 95 */	bl PPCMthid2
/* 80344D20 00341900  80 01 00 84 */	lwz r0, 0x84(r1)
/* 80344D24 00341904  83 E1 00 7C */	lwz r31, 0x7c(r1)
/* 80344D28 00341908  83 C1 00 78 */	lwz r30, 0x78(r1)
/* 80344D2C 0034190C  7C 08 03 A6 */	mtlr r0
/* 80344D30 00341910  83 A1 00 74 */	lwz r29, 0x74(r1)
/* 80344D34 00341914  38 21 00 80 */	addi r1, r1, 0x80
/* 80344D38 00341918  4E 80 00 20 */	blr 

.global __OSCacheInit
__OSCacheInit:
/* 80344D3C 0034191C  7C 08 02 A6 */	mflr r0
/* 80344D40 00341920  90 01 00 04 */	stw r0, 4(r1)
/* 80344D44 00341924  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 80344D48 00341928  93 E1 00 0C */	stw r31, 0xc(r1)
/* 80344D4C 0034192C  93 C1 00 08 */	stw r30, 8(r1)
/* 80344D50 00341930  3C 60 80 40 */	lis r3, lbl_80401BF0@ha
/* 80344D54 00341934  3B E3 1B F0 */	addi r31, r3, lbl_80401BF0@l
/* 80344D58 00341938  4B FF 11 15 */	bl PPCMfhid0
/* 80344D5C 0034193C  54 60 04 20 */	rlwinm r0, r3, 0, 0x10, 0x10
/* 80344D60 00341940  28 00 00 00 */	cmplwi r0, 0
/* 80344D64 00341944  40 82 00 14 */	bne lbl_80344D78
/* 80344D68 00341948  4B FF FB B5 */	bl ICEnable
/* 80344D6C 0034194C  38 7F 01 AC */	addi r3, r31, 0x1ac
/* 80344D70 00341950  4C C6 31 82 */	crclr 6
/* 80344D74 00341954  4B FF 12 05 */	bl DBPrintf
lbl_80344D78:
/* 80344D78 00341958  4B FF 10 F5 */	bl PPCMfhid0
/* 80344D7C 0034195C  54 60 04 62 */	rlwinm r0, r3, 0, 0x11, 0x11
/* 80344D80 00341960  28 00 00 00 */	cmplwi r0, 0
/* 80344D84 00341964  40 82 00 14 */	bne lbl_80344D98
/* 80344D88 00341968  4B FF FA 41 */	bl DCEnable
/* 80344D8C 0034196C  38 7F 01 C8 */	addi r3, r31, 0x1c8
/* 80344D90 00341970  4C C6 31 82 */	crclr 6
/* 80344D94 00341974  4B FF 11 E5 */	bl DBPrintf
lbl_80344D98:
/* 80344D98 00341978  4B FF 10 DD */	bl PPCMfl2cr
/* 80344D9C 0034197C  54 60 00 00 */	rlwinm r0, r3, 0, 0, 0
/* 80344DA0 00341980  28 00 00 00 */	cmplwi r0, 0
/* 80344DA4 00341984  40 82 00 58 */	bne lbl_80344DFC
/* 80344DA8 00341988  4B FF 10 B5 */	bl PPCMfmsr
/* 80344DAC 0034198C  7C 7E 1B 78 */	mr r30, r3
/* 80344DB0 00341990  7C 00 04 AC */	sync 0
/* 80344DB4 00341994  38 60 00 30 */	li r3, 0x30
/* 80344DB8 00341998  4B FF 10 AD */	bl PPCMtmsr
/* 80344DBC 0034199C  7C 00 04 AC */	sync 0
/* 80344DC0 003419A0  7C 00 04 AC */	sync 0
/* 80344DC4 003419A4  4B FF 10 B1 */	bl PPCMfl2cr
/* 80344DC8 003419A8  54 63 00 7E */	clrlwi r3, r3, 1
/* 80344DCC 003419AC  4B FF 10 B1 */	bl PPCMtl2cr
/* 80344DD0 003419B0  7C 00 04 AC */	sync 0
/* 80344DD4 003419B4  4B FF FD 71 */	bl L2GlobalInvalidate
/* 80344DD8 003419B8  7F C3 F3 78 */	mr r3, r30
/* 80344DDC 003419BC  4B FF 10 89 */	bl PPCMtmsr
/* 80344DE0 003419C0  4B FF 10 95 */	bl PPCMfl2cr
/* 80344DE4 003419C4  64 60 80 00 */	oris r0, r3, 0x8000
/* 80344DE8 003419C8  54 03 02 D2 */	rlwinm r3, r0, 0, 0xb, 9
/* 80344DEC 003419CC  4B FF 10 91 */	bl PPCMtl2cr
/* 80344DF0 003419D0  38 7F 01 E4 */	addi r3, r31, 0x1e4
/* 80344DF4 003419D4  4C C6 31 82 */	crclr 6
/* 80344DF8 003419D8  4B FF 11 81 */	bl DBPrintf
lbl_80344DFC:
/* 80344DFC 003419DC  3C 60 80 34 */	lis r3, DMAErrorHandler@ha
/* 80344E00 003419E0  38 83 4B DC */	addi r4, r3, DMAErrorHandler@l
/* 80344E04 003419E4  38 60 00 01 */	li r3, 1
/* 80344E08 003419E8  48 00 0A 4D */	bl OSSetErrorHandler
/* 80344E0C 003419EC  38 7F 01 FC */	addi r3, r31, 0x1fc
/* 80344E10 003419F0  4C C6 31 82 */	crclr 6
/* 80344E14 003419F4  4B FF 11 65 */	bl DBPrintf
/* 80344E18 003419F8  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80344E1C 003419FC  83 E1 00 0C */	lwz r31, 0xc(r1)
/* 80344E20 00341A00  83 C1 00 08 */	lwz r30, 8(r1)
/* 80344E24 00341A04  7C 08 03 A6 */	mtlr r0
/* 80344E28 00341A08  38 21 00 10 */	addi r1, r1, 0x10
/* 80344E2C 00341A0C  4E 80 00 20 */	blr 

.section .data
    .balign 8
lbl_80401BF0:
    .asciz ">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n"
    .balign 4
    .asciz "Machine check received\n"
    .balign 4
    .asciz "HID2 = 0x%x   SRR1 = 0x%x\n"
    .balign 4
    .asciz "Machine check was not DMA/locked cache related\n"
    .balign 4
    .asciz "DMAErrorHandler(): An error occurred while processing DMA.\n"
    .balign 4
    .asciz "The following errors have been detected and cleared :\n"
    .balign 4
    .asciz "\t- Requested a locked cache tag that was already in the cache\n"
    .balign 4
    .asciz "\t- DMA attempted to access normal cache\n"
    .balign 4
    .asciz "\t- DMA missed in data cache\n"
    .balign 4
    .asciz "\t- DMA queue overflowed\n"
    .balign 4
    .asciz "L1 i-caches initialized\n"
    .balign 4
    .asciz "L1 d-caches initialized\n"
    .balign 4
    .asciz "L2 cache initialized\n"
    .balign 4
    .asciz "Locked cache machine check handler installed\n"
    .balign 4
    .4byte NULL
