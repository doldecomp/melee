.include "macros.inc"

.section .data
    .balign 8
.global lbl_803E9030
lbl_803E9030:
    .4byte GrTNess_8022275C
    .4byte GrTNess_80222788
    .4byte GrTNess_80222790
    .4byte GrTNess_80222794
    .4byte NULL
    .4byte GrTNess_80222828
    .4byte GrTNess_80222878
    .4byte GrTNess_80222880
    .4byte GrTNess_802228A0
    .4byte NULL
    .4byte GrTNess_80222798
    .4byte GrTNess_802227E8
    .4byte GrTNess_802227F0
    .4byte GrTNess_80222824
    .4byte 0xC0000000
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E9080
lbl_803E9080:
    .asciz "/GrTNs.dat"
    .balign 4
.global lbl_803E908C
lbl_803E908C:
    .4byte 0x00000036
    .4byte lbl_803E9030
    .4byte lbl_803E9080
    .4byte GrTNess_802225D4
    .4byte GrTNess_802225D0
    .4byte GrTNess_80222644
    .4byte GrTNess_80222648
    .4byte GrTNess_8022266C
    .4byte GrTNess_802228A4
    .4byte GrTNess_802228AC
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .asciz "grtness.c"
