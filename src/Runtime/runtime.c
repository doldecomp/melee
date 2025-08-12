#include "runtime.h"

#include <placeholder.h>

static const unsigned long __constants[] = {
    0x00000000, 0x00000000, 0x41F00000, 0x00000000, 0x41E00000, 0x00000000,
};

ASM unsigned long __cvt_fp2unsigned(register double d)
{
#ifdef __MWERKS__ // clang-format off
    nofralloc
    stwu    r1,-16(r1)
    lis     r4, __constants@h
    ori     r4, r4, __constants@l
    li      r3,0
    lfd     fp0,0(r4)
    lfd     fp3,8(r4)
    lfd     fp4,16(r4)
    fcmpu   cr0,fp1,fp0
    fcmpu   cr6,fp1,fp3
    blt     cr0, @exit
    addi    r3,r3,-1
    bge     cr6,@exit
    fcmpu   cr7,fp1,fp4
    fmr     fp2,fp1
    blt     cr7,@1
    fsub    fp2,fp1,fp4
@1  fctiwz  fp2,fp2
    stfd    fp2,8(r1)
    lwz     r3,12(r1)
    blt     cr7,@exit
    addis   r3,r3,-0x8000
@exit:
    addi    r1,r1,16
    blr
#else
    return (unsigned long)d;
#endif // clang-format on
}

ASM void __div2u(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmpwi   cr0,r3,0
    cntlzw  r0,r3
    cntlzw  r9,r4
    bne     cr0,lab1
    addi    r0,r9,32
lab1:
    cmpwi   cr0,r5,0
    cntlzw  r9,r5
    cntlzw  r10,r6
    bne     cr0,lab2
    addi    r9,r10,32
lab2:
    cmpw    cr0,r0,r9
    subfic  r10,r0,64
    bgt     cr0,lab9
    addi    r9,r9,1
    subfic  r9,r9,64
    add     r0,r0,r9
    subf    r9,r9,r10
    mtctr   r9
    cmpwi   cr0,r9,32
    addi    r7,r9,-32
    blt     cr0,lab3
    srw     r8,r3,r7
    li      r7,0
    b       lab4
lab3:
    srw     r8,r4,r9
    subfic  r7,r9,32
    slw     r7,r3,r7
    or      r8,r8,r7
    srw     r7,r3,r9
lab4:
    cmpwi   cr0,r0,32
    addic   r9,r0,-32
    blt     cr0,lab5
    slw     r3,r4,r9
    li      r4,0
    b       lab6
lab5:
    slw     r3,r3,r0
    subfic  r9,r0,32
    srw     r9,r4,r9
    or      r3,r3,r9
    slw     r4,r4,r0
lab6:
    li      r10,-1
    addic   r7,r7,0
lab7:
    adde    r4,r4,r4
    adde    r3,r3,r3
    adde    r8,r8,r8
    adde    r7,r7,r7
    subfc   r0,r6,r8
    subfe.  r9,r5,r7
    blt     cr0,lab8
    mr      r8,r0
    mr      r7,r9
    addic   r0,r10,1
lab8:
    bdnz    lab7
    adde    r4,r4,r4
    adde    r3,r3,r3
    blr
lab9:
    li      r4,0
    li      r3,0
    blr
#endif // clang-format on
}

#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off

ASM void __div2i(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    stwu     r1,-16(r1)
    rlwinm.  r9,r3,0,0,0
    beq      cr0,positive1
    subfic   r4,r4,0
    subfze   r3,r3
positive1:
    stw      r9,8(r1)
    rlwinm.  r9,r5,0,0,0
    beq      cr0,positive2
    subfic   r6,r6,0
    subfze   r5,r5
positive2:
    stw      r9,12(r1)
    cmpwi    cr0,r3,0
    cntlzw   r0,r3
    cntlzw   r9,r4
    bne      cr0,lab1
    addi     r0,r9,32
lab1:
    cmpwi    cr0,r5,0
    cntlzw   r9,r5
    cntlzw   r10,r6
    bne      cr0,lab2
    addi     r9,r10,32
lab2:
    cmpw     cr0,r0,r9
    subfic   r10,r0,64
    bgt      cr0,lab9
    addi     r9,r9,1
    subfic   r9,r9,64
    add      r0,r0,r9
    subf     r9,r9,r10
    mtctr    r9
    cmpwi    cr0,r9,32
    addi     r7,r9,-32
    blt      cr0,lab3
    srw      r8,r3,r7
    li       r7,0
    b        lab4
lab3:
    srw      r8,r4,r9
    subfic   r7,r9,32
    slw      r7,r3,r7
    or       r8,r8,r7
    srw      r7,r3,r9
lab4:
    cmpwi    cr0,r0,32
    addic    r9,r0,-32
    blt      cr0,lab5
    slw      r3,r4,r9
    li       r4,0
    b        lab6
lab5:
    slw      r3,r3,r0
    subfic   r9,r0,32
    srw      r9,r4,r9
    or       r3,r3,r9
    slw      r4,r4,r0
lab6:
    li       r10,-1
    addic    r7,r7,0
lab7:
    adde     r4,r4,r4
    adde     r3,r3,r3
    adde     r8,r8,r8
    adde     r7,r7,r7
    subfc    r0,r6,r8
    subfe.   r9,r5,r7
    blt      cr0,lab8
    mr       r8,r0
    mr       r7,r9
    addic    r0,r10,1
lab8:
    bdnz     lab7
    adde     r4,r4,r4
    adde     r3,r3,r3
    lwz      r9,8(r1)
    lwz      r10,12(r1)
    xor.     r7,r9,r10
    beq      no_adjust
    cmpwi    cr0,r9,0
    subfic   r4,r4,0
    subfze   r3,r3

no_adjust:
    b        func_end

lab9:
    li        r4,0
    li        r3,0
func_end:
    addi      r1,r1,16
    blr
#endif // clang-format on
}

#pragma pop
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off

ASM void __mod2u(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    cmpwi    cr0,r3,0
    cntlzw   r0,r3
    cntlzw   r9,r4
    bne      cr0,lab1
    addi     r0,r9,32
lab1:
    cmpwi    cr0,r5,0
    cntlzw   r9,r5
    cntlzw   r10,r6
    bne      cr0,lab2
    addi     r9,r10,32
lab2:
    cmpw     cr0,r0,r9
    subfic   r10,r0,64
    bgt      cr0,lab9
    addi     r9,r9,1
    subfic   r9,r9,64
    add      r0,r0,r9
    subf     r9,r9,r10
    mtctr    r9
    cmpwi    cr0,r9,32
    addi     r7,r9,-32
    blt      cr0,lab3
    srw      r8,r3,r7
    li       r7,0
    b        lab4
lab3:
    srw      r8,r4,r9
    subfic   r7,r9,32
    slw      r7,r3,r7
    or       r8,r8,r7
    srw      r7,r3,r9
lab4:
    cmpwi    cr0,r0,32
    addic    r9,r0,-32
    blt      cr0,lab5
    slw      r3,r4,r9
    li       r4,0
    b        lab6
lab5:
    slw      r3,r3,r0
    subfic   r9,r0,32
    srw      r9,r4,r9
    or       r3,r3,r9
    slw      r4,r4,r0
lab6:
    li       r10,-1
    addic    r7,r7,0
lab7:
    adde     r4,r4,r4
    adde     r3,r3,r3
    adde     r8,r8,r8
    adde     r7,r7,r7
    subfc    r0,r6,r8
    subfe.   r9,r5,r7
    blt      cr0,lab8
    mr       r8,r0
    mr       r7,r9
    addic    r0,r10,1
lab8:
    bdnz     lab7
    mr       r4,r8
    mr       r3,r7
    blr
lab9:
    blr
#endif // clang-format on
}

#pragma pop
#pragma push
#pragma optimization_level 0
#pragma optimizewithasm off

ASM void __mod2i(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc

    cmpwi    cr7,r3,0
    bge      cr7,positive1
    subfic   r4,r4,0
    subfze   r3,r3
positive1:
    cmpwi    cr0,r5,0
    bge      cr0,positive2
    subfic   r6,r6,0
    subfze   r5,r5
positive2:
    cmpwi    cr0,r3,0
    cntlzw    r0,r3
    cntlzw    r9,r4
    bne    cr0,lab1
    addi    r0,r9,32
lab1:
    cmpwi    cr0,r5,0
    cntlzw    r9,r5
    cntlzw    r10,r6
    bne    cr0,lab2
    addi    r9,r10,32
lab2:
    cmpw    cr0,r0,r9
    subfic    r10,r0,64
    bgt    cr0,lab9
    addi    r9,r9,1
    subfic    r9,r9,64
    add    r0,r0,r9
    subf    r9,r9,r10
    mtctr    r9
    cmpwi    cr0,r9,32
    addi    r7,r9,-32
    blt    cr0,lab3
    srw    r8,r3,r7
    li    r7,0
    b    lab4
lab3:
    srw    r8,r4,r9
    subfic    r7,r9,32
    slw    r7,r3,r7
    or    r8,r8,r7
    srw    r7,r3,r9
lab4:
    cmpwi    cr0,r0,32
    addic    r9,r0,-32
    blt    cr0,lab5
    slw    r3,r4,r9
    li    r4,0
    b    lab6
lab5:
    slw    r3,r3,r0
    subfic    r9,r0,32
    srw    r9,r4,r9
    or    r3,r3,r9
    slw    r4,r4,r0
lab6:
    li    r10,-1
    addic    r7,r7,0
lab7:
    adde    r4,r4,r4
    adde    r3,r3,r3
    adde    r8,r8,r8
    adde    r7,r7,r7
    subfc    r0,r6,r8
    subfe.    r9,r5,r7
    blt    cr0,lab8
    mr    r8,r0
    mr    r7,r9
    addic    r0,r10,1
lab8:
    bdnz    lab7
    mr    r4,r8
    mr    r3,r7
lab9:
    bge    cr7,no_adjust
    subfic   r4,r4,0
    subfze   r3,r3
no_adjust:
    blr
#endif // clang-format on
}
#pragma pop

ASM void __shl2i(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    subfic  r8,r5,32
    subic   r9,r5,32
    slw     r3,r3,r5
    srw     r10,r4,r8
    or      r3,r3,r10
    slw     r10,r4,r9
    or      r3,r3,r10
    slw     r4,r4,r5
    blr
#endif // clang-format on
}

ASM void __shr2u(void){
#ifdef __MWERKS__ // clang-format off
    nofralloc
    subfic  r8,r5,32
    subic   r9,r5,32
    srw     r4,r4,r5
    slw     r10,r3,r8
    or      r4,r4,r10
    srw     r10,r3,r9
    or      r4,r4,r10
    srw     r3,r3,r5
    blr
#endif // clang-format on
}

ASM void __shr2i(void){
#ifdef __MWERKS__ // clang-format off
    subfic  r8, r5, 0x20
    addic.  r9, r5, -0x20
    srw     r4, r4, r5
    slw     r10, r3, r8
    or      r4, r4, r10
    sraw    r10, r3, r9
    ble     L_802BA610
    or      r4, r4, r10
L_802BA610:
    sraw    r3, r3, r5
#endif // clang-format on
}

ASM void __cvt_sll_dbl(void){
#ifdef __MWERKS__ // clang-format off
    stwu        r1, -0x10(r1)
    rlwinm.     r5, r3, 0, 0, 0
    beq-        lbl_802b2b1c
    subfic      r4, r4, 0x0
    subfze      r3, r3
lbl_802b2b1c:
    or.         r7, r3, r4
    li          r6, 0x0
    beq-        lbl_802b2ba4
    cntlzw      r7, r3
    cntlzw      r8, r4
    rlwinm      r9, r7, 0x1a, 0, 4
    srawi       r9, r9, 0x1f
    and         r9, r9, r8
    add         r7, r7, r9
    subfic      r8, r7, 0x20
    addic       r9, r7, -0x20
    slw         r3, r3, r7
    srw         r10, r4, r8
    or          r3, r3, r10
    slw         r10, r4, r9
    or          r3, r3, r10
    slw         r4, r4, r7
    subf        r6, r7, r6
    clrlwi      r7, r4, 0x15
    cmpwi       r7, 0x400
    addi        r6, r6, 0x43e
    blt-        lbl_802b2b8c
    bgt-        lbl_802b2b80
    rlwinm.     r7, r4, 0, 0x14, 0x14
    beq-        lbl_802b2b8c
lbl_802b2b80:
    addic       r4, r4, 0x800
    addze       r3, r3
    addze       r6, r6
lbl_802b2b8c:
    rotlwi      r4, r4, 0x15
    rlwimi      r4, r3, 0x15, 0, 0xa
    rlwinm      r3, r3, 0x15, 0xc, 0x1f
    slwi        r6, r6, 0x14
    or          r3, r6, r3
    or          r3, r5, r3
lbl_802b2ba4:
    stw         r3, 8(r1)
    stw         r4, 0xc(r1)
    lfd         f1, 8(r1)
    addi        r1, r1, 0x10
#endif // clang-format on
}

ASM void __cvt_sll_flt(void){
#ifdef __MWERKS__ // clang-format off
    stwu r1, -0x10(r1)
    clrrwi. r5, r3, 31
    beq L_802BA62C
    subfic r4, r4, 0x0
    subfze r3, r3
L_802BA62C:
    or. r7, r3, r4
    li r6, 0x0
    beq L_802BA6B4
    cntlzw r7, r3
    cntlzw r8, r4
    extlwi r9, r7, 5, 26
    srawi r9, r9, 31
    and r9, r9, r8
    add r7, r7, r9
    subfic r8, r7, 0x20
    addic r9, r7, -0x20
    slw r3, r3, r7
    srw r10, r4, r8
    or r3, r3, r10
    slw r10, r4, r9
    or r3, r3, r10
    slw r4, r4, r7
    subf r6, r7, r6
    clrlwi r7, r4, 21
    cmpwi r7, 0x400
    addi r6, r6, 0x43e
    blt L_802BA69C
    bgt L_802BA690
    rlwinm. r7, r4, 0, 20, 20
    beq L_802BA69C
L_802BA690:
    addic r4, r4, 0x800
    addze r3, r3
    addze r6, r6
L_802BA69C:
    rotrwi r4, r4, 11
    rlwimi r4, r3, 21, 0, 10
    extrwi r3, r3, 20, 1
    slwi r6, r6, 20
    or r3, r6, r3
    or r3, r5, r3
L_802BA6B4:
    stw r3, 0x8(r1)
    stw r4, 0xc(r1)
    lfd f1, 0x8(r1)
    frsp f1, f1
    addi r1, r1, 0x10
#endif // clang-format on
}

ASM u64 __cvt_dbl_usll(double x)
{
#ifdef __MWERKS__ // clang-format off
    nofralloc
    stwu    r1,-16(r1)
    stfd    f1,8(r1)
    lwz        r3,8(r1)
    lwz        r4,12(r1)
    rlwinm   r5,r3,12,21,31
    cmpli    cr0,0,r5,1023
    bge        cr0,not_fraction
    li        r3,0
    li        r4,0
    b        func_end
not_fraction:
    mr        r6,r3
    rlwinm    r3,r3,0,12,31
    oris    r3,r3,0x0010
    addi    r5,r5,-1075
    cmpwi    cr0,r5,0
    bge        cr0,left
    neg        r5,r5
    subfic    r8,r5,32
    subic    r9,r5,32
    srw        r4,r4,r5
    slw        r10,r3,r8
    or        r4,r4,r10
    srw        r10,r3,r9
    or        r4,r4,r10
    srw        r3,r3,r5
    b        around
left:
    cmpwi    cr0,r5,10
    ble+    no_overflow
    rlwinm.    r6,r6,0,0,0
    beq        cr0,max_positive
    lis        r3,0x8000
    li        r4,0
    b        func_end
max_positive:
    lis        r3,0x7FFF
    ori        r3,r3,0xFFFF
    li        r4,-1
    b        func_end
no_overflow:
    subfic    r8,r5,32
    subic    r9,r5,32
    slw        r3,r3,r5
    srw        r10,r4,r8
    or        r3,r3,r10
    slw        r10,r4,r9
    or        r3,r3,r10
    slw        r4,r4,r5
around:
    rlwinm.    r6,r6,0,0,0
    beq        cr0,positive
    subfic    r4,r4,0
    subfze    r3,r3
positive:
func_end:
    addi    r1,r1,16
    blr
#endif // clang-format on
}
