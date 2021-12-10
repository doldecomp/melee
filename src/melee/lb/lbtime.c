#include "lbtime.h"

#define UINT_MAX 0xFFFFFFFF

u32 func_8000AEC8(u32 a, u32 b) {
    return -1 - a > b ? a + b : -1;
}

u32 func_8000AEE4(u32 a, int b) {
    if (b > 0) {
        return -1 - a > b ? a + b : -1;
    } else {
        return a > -b ? a + b : 0;
    }
}

u32 func_8000AF24(u32 a, int b, int c) {
    if (b > 0) {
        unsigned int ab = a & 0x0000ffff;
        c = 0x0000ffff;
        if (c - ab > b)
            return a+b;
        else
            return c;
    } else {
        c = a & 0xffff;

        if (c > -b) {
            return a + b;
        } else {
            return 0;
        }
    }
}

u32 func_8000AF74(u32 a, int b, int c) {
    if (b > 0) {
        u32 r0 = a & 0xff;
        r0 = 0xff - r0;

        return (r0 > b) ? a + b : 0xff;
    } else {
        c = a & 0xff;

        return (c > -b) ? a + b : 0;
    }
}
// nonmatching for now due to scheduling silliness
/*
u32 func_8000AFBC(void) {
    u64 uVar3 = OSGetTime() / (*(u32 *)0x800000F8 / 4);
    if (uVar3 > UINT_MAX)
        uVar3 = UINT_MAX;
    return uVar3;
}
*/
asm u32 func_8000AFBC(void) {
    nofralloc
    mflr r0
    lis r3, 0x800000F8@ha
    stw r0, 4(r1)
    stwu r1, -0x10(r1)
    stw r31, 0xc(r1)
    stw r30, 8(r1)
    lwz r0, 0x800000F8@l(r3)
    srwi r30, r0, 2
    bl OSGetTime
    addi r6, r30, 0
    li r5, 0
    bl __div2i
    li r0, -1
    subfc r0, r4, r0
    li r0, 0
    subfe r0, r3, r0
    subfe r0, r31, r31
    neg. r0, r0
    beq lbl_8000B00C
    li r4, -1
lbl_8000B00C:
    lwz r0, 0x14(r1)
    mr r3, r4
    lwz r31, 0xc(r1)
    lwz r30, 8(r1)
    addi r1, r1, 0x10
    mtlr r0
    blr 
}

void func_8000B028(OSCalendarTime* td, unsigned int ticks) {
  OSTicksToCalendarTime(ticks * (long long)((*(unsigned int *)0x800000F8) >> 2), td);
}
