#include <melee/if/ifstatus.h>

#ifdef NON_MATCHING

inline HSD_GObj* nth_node(HSD_GObj* node, s32 n)
{
    s32 i;
    HSD_GObj* cur = node;
    for (i = 0; i < n && node; i++) {
        if (cur == NULL) { // if (node == NULL)
            cur = NULL;
        } else {
            cur = node->next;
        }
        node = cur;
    }
    return node;
}

// 99.81% match
// https://decomp.me/scratch/XGFpw
HSD_GObj* func_802F6194(HSD_GObj* node, s32 n)
{
    HSD_GObj* gx;

    if ((node == NULL) || (n < 0)) {
        return NULL;
    }
    if (node == NULL) {
        gx = NULL;
    } else {
        gx = node->next_gx;
    }
    gx = nth_node(gx, n);
    return gx;
}

#else

#pragma push

asm HSD_GObj* func_802F6194(HSD_GObj*, s32)
{ // clang-format off
    nofralloc
/* 802F6194 002F2D74  28 03 00 00 */	cmplwi r3, 0
/* 802F6198 002F2D78  41 82 00 0C */	beq lbl_802F61A4
/* 802F619C 002F2D7C  2C 04 00 00 */	cmpwi r4, 0
/* 802F61A0 002F2D80  40 80 00 0C */	bge lbl_802F61AC
lbl_802F61A4:
/* 802F61A4 002F2D84  38 60 00 00 */	li r3, 0
/* 802F61A8 002F2D88  4E 80 00 20 */	blr 
lbl_802F61AC:
/* 802F61AC 002F2D8C  28 03 00 00 */	cmplwi r3, 0
/* 802F61B0 002F2D90  40 82 00 0C */	bne lbl_802F61BC
/* 802F61B4 002F2D94  38 00 00 00 */	li r0, 0
/* 802F61B8 002F2D98  48 00 00 08 */	b lbl_802F61C0
lbl_802F61BC:
/* 802F61BC 002F2D9C  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_802F61C0:
/* 802F61C0 002F2DA0  7C 03 03 78 */	mr r3, r0
/* 802F61C4 002F2DA4  38 A0 00 00 */	li r5, 0
/* 802F61C8 002F2DA8  48 00 00 20 */	b lbl_802F61E8
lbl_802F61CC:
/* 802F61CC 002F2DAC  28 03 00 00 */	cmplwi r3, 0
/* 802F61D0 002F2DB0  40 82 00 0C */	bne lbl_802F61DC
/* 802F61D4 002F2DB4  38 00 00 00 */	li r0, 0
/* 802F61D8 002F2DB8  48 00 00 08 */	b lbl_802F61E0
lbl_802F61DC:
/* 802F61DC 002F2DBC  80 03 00 08 */	lwz r0, 8(r3)
lbl_802F61E0:
/* 802F61E0 002F2DC0  7C 03 03 78 */	mr r3, r0
/* 802F61E4 002F2DC4  38 A5 00 01 */	addi r5, r5, 1
lbl_802F61E8:
/* 802F61E8 002F2DC8  7C 05 20 00 */	cmpw r5, r4
/* 802F61EC 002F2DCC  4C 80 00 20 */	bgelr 
/* 802F61F0 002F2DD0  28 03 00 00 */	cmplwi r3, 0
/* 802F61F4 002F2DD4  40 82 FF D8 */	bne lbl_802F61CC
/* 802F61F8 002F2DD8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif
