.include "macros.inc"

.section .data
    .balign 8
.global lbl_803D4070
lbl_803D4070:
    .asciz "PlMh.dat"
    .balign 4
.global lbl_803D407C
lbl_803D407C:
    .asciz "ftDataMasterhand"
    .balign 4
.global lbl_803D4090
lbl_803D4090:
    .asciz "PlMhNr.dat"
    .balign 4
.global lbl_803D409C
lbl_803D409C:
    .asciz "PlyMasterhand_Share_joint"
    .balign 4
.global lbl_803D40B8
lbl_803D40B8:
    .asciz "PlMhAJ.dat"
    .balign 4
.global lbl_803D40C4
lbl_803D40C4:
    .4byte lbl_803D4090
    .4byte lbl_803D409C
    .4byte NULL
