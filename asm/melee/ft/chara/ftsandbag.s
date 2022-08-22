.include "macros.inc"

.section .data
    .balign 8
.global as_table_sandbag
as_table_sandbag:
    .4byte 0x00000127
    .4byte NULL
    .4byte 0x01400000
    .4byte func_8014FC20
    .4byte func_8014FC24
    .4byte func_8014FC28
    .4byte func_8014FC48
    .4byte func_800761C8
.global lbl_803D39B8
lbl_803D39B8:
    .asciz "PlSb.dat"
    .balign 4
.global lbl_803D39C4
lbl_803D39C4:
    .asciz "ftDataSandbag"
    .balign 4
.global lbl_803D39D4
lbl_803D39D4:
    .asciz "PlSbNr.dat"
    .balign 4
.global lbl_803D39E0
lbl_803D39E0:
    .asciz "PlySandbag_Share_joint"
    .balign 4
.global lbl_803D39F8
lbl_803D39F8:
    .asciz "PlySandbag_Share_matanim_joint"
    .balign 4
.global lbl_803D3A18
lbl_803D3A18:
    .asciz "PlSbAJ.dat"
    .balign 4
.global lbl_803D3A24
lbl_803D3A24:
    .4byte lbl_803D39D4
    .4byte lbl_803D39E0
    .4byte lbl_803D39F8
