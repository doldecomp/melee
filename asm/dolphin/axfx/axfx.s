.include "macros.inc"

.section .text

.global AXFXAllocFunction
AXFXAllocFunction:
/* 8035DD3C 0035A91C  7C 08 02 A6 */	mflr r0
/* 8035DD40 0035A920  7C 64 1B 78 */	mr r4, r3
/* 8035DD44 0035A924  90 01 00 04 */	stw r0, 4(r1)
/* 8035DD48 0035A928  94 21 FF F8 */	stwu r1, -8(r1)
/* 8035DD4C 0035A92C  80 6D A5 68 */	lwz r3, __OSCurrHeap@sda21(r13)
/* 8035DD50 0035A930  4B FE 61 A1 */	bl OSAllocFromHeap
/* 8035DD54 0035A934  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8035DD58 0035A938  38 21 00 08 */	addi r1, r1, 8
/* 8035DD5C 0035A93C  7C 08 03 A6 */	mtlr r0
/* 8035DD60 0035A940  4E 80 00 20 */	blr 

.global AXFXFreeFunction
AXFXFreeFunction:
/* 8035DD64 0035A944  7C 08 02 A6 */	mflr r0
/* 8035DD68 0035A948  7C 64 1B 78 */	mr r4, r3
/* 8035DD6C 0035A94C  90 01 00 04 */	stw r0, 4(r1)
/* 8035DD70 0035A950  94 21 FF F8 */	stwu r1, -8(r1)
/* 8035DD74 0035A954  80 6D A5 68 */	lwz r3, __OSCurrHeap@sda21(r13)
/* 8035DD78 0035A958  4B FE 62 75 */	bl OSFreeToHeap
/* 8035DD7C 0035A95C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8035DD80 0035A960  38 21 00 08 */	addi r1, r1, 8
/* 8035DD84 0035A964  7C 08 03 A6 */	mtlr r0
/* 8035DD88 0035A968  4E 80 00 20 */	blr 

.global AXFXSetHooks
AXFXSetHooks:
/* 8035DD8C 0035A96C  90 6D A5 D0 */	stw r3, __AXFXAlloc@sda21(r13)
/* 8035DD90 0035A970  90 8D A5 D4 */	stw r4, __AXFXFree@sda21(r13)
/* 8035DD94 0035A974  4E 80 00 20 */	blr 


.section .sdata
    .balign 8
.global __AXFXAlloc
__AXFXAlloc:
    .4byte AXFXAllocFunction
.global __AXFXFree
__AXFXFree:
    .4byte AXFXFreeFunction
