.include "macros.inc"

.section .text  # 0x80342E94 - 0x803B7240

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
.global lbl_80401BF0
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
