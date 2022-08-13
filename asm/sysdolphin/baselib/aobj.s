.include "macros.inc"

.section .data  # 0x803B9840 - 0x804316C0

.global lbl_8040601C
lbl_8040601C:
    .asciz "unexpected argument format.\n"
    .balign 4
.global lbl_8040603C
lbl_8040603C:
    .asciz "unexpected type of object.\n"
    .balign 4
.global jtbl_80406058
jtbl_80406058:
    .4byte HSD_ForeachAnim + 0x6DC
    .4byte HSD_ForeachAnim + 0x6DC
    .4byte HSD_ForeachAnim + 0x50C
    .4byte HSD_ForeachAnim + 0x224
    .4byte HSD_ForeachAnim + 0x6DC
    .4byte HSD_ForeachAnim + 0x6A4
    .4byte HSD_ForeachAnim + 0x124
    .4byte HSD_ForeachAnim + 0x424
    .4byte HSD_ForeachAnim + 0x310
    .4byte HSD_ForeachAnim + 0x38C
    .4byte HSD_ForeachAnim + 0x5E4
    .4byte HSD_ForeachAnim + 0x3E0
    .4byte HSD_ForeachAnim + 0x628
.global jtbl_8040608C
jtbl_8040608C:
    .4byte HSD_ForeachAnim + 0x104
    .4byte HSD_ForeachAnim + 0xA4
    .4byte HSD_ForeachAnim + 0xC0
    .4byte HSD_ForeachAnim + 0xD8
    .4byte HSD_ForeachAnim + 0x104
    .4byte HSD_ForeachAnim + 0xA4
    .4byte HSD_ForeachAnim + 0xC0
    .4byte HSD_ForeachAnim + 0xD8
    .4byte HSD_ForeachAnim + 0x104
    .4byte HSD_ForeachAnim + 0xA4
    .4byte HSD_ForeachAnim + 0xC0
    .4byte HSD_ForeachAnim + 0xD8
