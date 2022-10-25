.include "macros.inc"

.section .data
    .balign 8
.global lbl_80401E20
lbl_80401E20:
    .asciz "------------------------- Context 0x%08x -------------------------\n"
    .balign 4
    .asciz "r%-2d  = 0x%08x (%14d)  r%-2d  = 0x%08x (%14d)\n"
    .balign 4
    .asciz "LR   = 0x%08x                   CR   = 0x%08x\n"
    .balign 4
    .asciz "SRR0 = 0x%08x                   SRR1 = 0x%08x\n"
    .balign 4
    .asciz "\nGQRs----------\n"
    .balign 4
    .asciz "gqr%d = 0x%08x \t gqr%d = 0x%08x\n"
    .balign 4
    .asciz "\n\nFPRs----------\n"
    .balign 4
    .asciz "fr%d \t= %d \t fr%d \t= %d\n"
    .balign 4
    .asciz "\n\nPSFs----------\n"
    .balign 4
    .asciz "ps%d \t= 0x%x \t ps%d \t= 0x%x\n"
    .balign 4
    .asciz "\nAddress:      Back Chain    LR Save\n"
    .balign 4
    .asciz "0x%08x:   0x%08x    0x%08x\n"
    .balign 4
.global lbl_80401FD4
lbl_80401FD4:
    .asciz "FPU-unavailable handler installed\n"
    .balign 4
