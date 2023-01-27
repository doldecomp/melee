.include "macros.inc"

.section .text

.global __AXGetCurrentProfile
__AXGetCurrentProfile:
/* 8035B678 00358258  80 0D BE FC */	lwz r0, __AXProfileInitialized@sda21(r13)
/* 8035B67C 0035825C  28 00 00 00 */	cmplwi r0, 0
/* 8035B680 00358260  41 82 00 38 */	beq lbl_8035B6B8
/* 8035B684 00358264  80 6D BE F8 */	lwz r3, __AXCurrentProfile@sda21(r13)
/* 8035B688 00358268  80 8D BE F4 */	lwz r4, __AXMaxProfiles@sda21(r13)
/* 8035B68C 0035826C  38 03 00 01 */	addi r0, r3, 1
/* 8035B690 00358270  80 CD BE F0 */	lwz r6, __AXProfile@sda21(r13)
/* 8035B694 00358274  90 0D BE F8 */	stw r0, __AXCurrentProfile@sda21(r13)
/* 8035B698 00358278  1C 03 00 38 */	mulli r0, r3, 0x38
/* 8035B69C 0035827C  80 AD BE F8 */	lwz r5, __AXCurrentProfile@sda21(r13)
/* 8035B6A0 00358280  7C 66 02 14 */	add r3, r6, r0
/* 8035B6A4 00358284  7C 05 23 96 */	divwu r0, r5, r4
/* 8035B6A8 00358288  7C 00 21 D6 */	mullw r0, r0, r4
/* 8035B6AC 0035828C  7C 00 28 50 */	subf r0, r0, r5
/* 8035B6B0 00358290  90 0D BE F8 */	stw r0, __AXCurrentProfile@sda21(r13)
/* 8035B6B4 00358294  4E 80 00 20 */	blr
lbl_8035B6B8:
/* 8035B6B8 00358298  38 60 00 00 */	li r3, 0
/* 8035B6BC 0035829C  4E 80 00 20 */	blr


.section .sbss
    .balign 8
.global __AXProfile
__AXProfile:
    .skip 0x4
.global __AXMaxProfiles
__AXMaxProfiles:
    .skip 0x4
.global __AXCurrentProfile
__AXCurrentProfile:
    .skip 0x4
.global __AXProfileInitialized
__AXProfileInitialized:
    .skip 0x4
