.include "macros.inc"

.section .data
    .balign 8
.global HSD_RObj_80406E68
HSD_RObj_80406E68:
    .asciz "rp->u.jobj"
    .balign 4
.global HSD_RObj_80406E74
HSD_RObj_80406E74:
    .4byte 0x32
    .4byte 0x33
    .4byte 0x34
.global HSD_RObj_80406E80
HSD_RObj_80406E80:
    .4byte HSD_RObj_8037BF78
    .4byte HSD_RObj_8037BE58
    .4byte HSD_RObj_8037BE70
    .4byte HSD_RObj_8037BE88
    .4byte HSD_RObj_8037BEA0
    .4byte HSD_RObj_8037BEB8
    .4byte HSD_RObj_8037BED0
    .4byte HSD_RObj_8037BEE8
    .4byte HSD_RObj_8037BF00
    .4byte HSD_RObj_8037BF18
    .4byte HSD_RObj_8037BF30
    .4byte HSD_RObj_8037BF48
    .4byte HSD_RObj_8037BF60
    .4byte 0x726F626A
    .4byte 0x2D3E752E
    .4byte 0x6A6F626A
    .4byte NULL
    .4byte 0x6F626A65
    .4byte 0x63742E68
    .4byte NULL
    .4byte 0x4853445F
    .4byte 0x4F424A28
    .4byte 0x6F292D3E
    .4byte 0x7265665F
    .4byte 0x636F756E
    .4byte 0x745F696E
    .4byte 0x64697669
    .4byte 0x6475616C
    .4byte 0x20213D20
    .4byte 0x30000000
.global HSD_RObj_80406EF8
HSD_RObj_80406EF8:
    .asciz "unexpected type of robj.\n"
    .balign 4
    .asciz "(ptr && nitems) || !ptr"
    .balign 4
.global HSD_RObj_80406F2C
HSD_RObj_80406F2C:
    .asciz "Number of argment of expression exceeds the argument buffer\nsize. (requested num of arg %d, allocated %d)\n"
    .balign 4
    .asciz "rvalue->jobj"
    .balign 4
    .asciz "constraint only support jobj target.\n"
    .balign 4


.section .sdata
    .balign 8
.global HSD_RObj_804D5EB8
HSD_RObj_804D5EB8:
    .asciz "robj.c"
    .balign 4
.global HSD_RObj_804D5EC0
HSD_RObj_804D5EC0:
    .asciz "jobj.h"
    .balign 4
.global HSD_RObj_804D5EC8
HSD_RObj_804D5EC8:
    .asciz "jobj"
    .balign 4
.global HSD_RObj_804D5ED0
HSD_RObj_804D5ED0:
    .asciz "obj"
    .balign 4
.global HSD_RObj_804D5ED4
HSD_RObj_804D5ED4:
    .asciz "new"
    .balign 4
.global HSD_RObj_804D5ED8
HSD_RObj_804D5ED8:
    .4byte NULL
.global HSD_RObj_804D5EDC
HSD_RObj_804D5EDC:
    .asciz "rvalue"
    .balign 4
.global HSD_RObj_804D5EE4
HSD_RObj_804D5EE4:
    .asciz "0"
    .balign 4


.section .sdata2
    .balign 8
.global HSD_RObj_804DE6A0
HSD_RObj_804DE6A0:
    .4byte 0x3FE00000
    .4byte 0x00000000
.global HSD_RObj_804DE6A8
HSD_RObj_804DE6A8:
    .4byte 0x3F800000
    .4byte 0x00000000

.global HSD_RObj_804DE6B8
HSD_RObj_804DE6B8:
    .4byte 0x2EDBE6FF
.global HSD_RObj_804DE6BC
HSD_RObj_804DE6BC:
    .4byte 0x00000000
.global HSD_RObj_804DE6C0
HSD_RObj_804DE6C0:
    .4byte 0x40080000
    .4byte 0x00000000
.global HSD_RObj_804DE6C8
HSD_RObj_804DE6C8:
    .4byte 0x3C8EFA35
.global HSD_RObj_804DE6CC
HSD_RObj_804DE6CC:
    .4byte 0x42652EE1
