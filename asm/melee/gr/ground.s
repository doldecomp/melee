.include "macros.inc"

.section .data
    .balign 4
.global lbl_803E065C
lbl_803E065C:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E066C
lbl_803E066C:
    .4byte NULL
    .4byte 0x3F11EB85
    .4byte 0x3F11EB85
    .4byte 0x3F11EB85
    .4byte NULL
.global lbl_803E0680
lbl_803E0680:
    .4byte NULL
    .4byte NULL
    .4byte 0x000D0000
    .4byte 0xFFFFFFFF
    .4byte lbl_803E066C
    .4byte NULL
    .4byte lbl_804D4508
.global lbl_803E069C
lbl_803E069C:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E06AC
lbl_803E06AC:
    .4byte NULL
    .4byte NULL
    .4byte 0x00040000
    .4byte 0xFFFFFFFF
    .4byte NULL
    .4byte NULL
    .4byte NULL
.global lbl_803E06C8
lbl_803E06C8:
    .4byte lbl_804D451C
    .4byte lbl_804D450C
    .4byte NULL
    .balign 4
    .asciz "%s:%d: couldn t get gobj\n"
    .balign 4
    .asciz "%s:%d: couldn t get lobj\n"
    .balign 4
    .4byte 0x00000001
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte 0x000000B4
    .4byte NULL
    .4byte NULL
    .4byte NULL


.section .rodata
    .balign 4
.global lbl_803B7DEC
lbl_803B7DEC:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000006
    .4byte 0x00000000
    .4byte 0x00000000
.global lbl_803B7E0C
lbl_803B7E0C:
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x3F800000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000
    .4byte 0x00000000


.section .sdata
    .balign 4
lbl_804D4500:
    .4byte lbl_803E065C
    .4byte 0x00000000
lbl_804D4508:
    .4byte 0x41800000
lbl_804D450C:
    .4byte lbl_803E0680
    .4byte lbl_804D4500
lbl_804D4514:
    .4byte lbl_803E069C
    .4byte 0x00000000
lbl_804D451C:
    .4byte lbl_803E06AC
    .4byte lbl_804D4514
.global lbl_804D4524
lbl_804D4524:
    .asciz "fog.h"
    .balign 4
.global lbl_804D452C
lbl_804D452C:
    .asciz "fog"
    .balign 4
