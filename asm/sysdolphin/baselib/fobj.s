.include "macros.inc"

.section .data
    .balign 8
.global HSD_FObj_80406350
HSD_FObj_80406350:
    .asciz "st == FOBJ_LOAD_WAIT"
    .balign 4
    .asciz "st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA"
